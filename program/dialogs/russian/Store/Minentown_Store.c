void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("There's been an alarm raised in the town. Everyone's looking for you! I wouldn't wait around here for too long if I were you.", "The whole town guard is scouring the town trying to find you. I'm not an idiot and I'm not gonna to talk to you!", "Run, buddy, before the soldiers make mince meat out of you..."),
					LinkRandPhrase("What do you need, scoundrel?! The town guard is on your tail right now. You won't make it far, dirty pirate!", "Get out of my house, killer! Guards!!", "I'm not afraid of you, scamp! Soon they'll hang you, you won't get away..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, I'm not too worried about the alarm...", "They have no chance of catching me."),
					RandPhraseSimple("Shut your pie hole, " + GetWorkTypeOfMan(npchar, "") + ", or I will cut off your bloody tongue!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", you too want to hunt a pirate! Listen, pal, keep calm and you'll live..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting() + "! I've never seen you before, senior. Dare I assume, you're a captain... Did I guess right? My name is "+GetFullName(npchar)+", and my store is at your service. Gold, silver, and much more to peak the interest of a curious man.";
				Link.l1 = "I see. I'm " + GetFullName(pchar) + ". Pleased to meet you, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting() + ", senior! I'm glad to see you again in my store. Would you like to acquire some gold nuggets? Or possibly you'd be interested in minerals today?";
				link.l1 = "Show me your merchandise, "+npchar.name+".";
				link.l1.go = "trade";
				link.l4 = "No, I don't need anything, "+npchar.name+". I've just stopped by to say hello to you.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "As am I, senior. Will you have a look at my merchandise? I'm sure I have something that'll be of interest to you.";
			link.l1 = "This is my first time here and I'd like to find out a little bit more about this settlement.";
			link.l1.go = "info";
			link.l2 = "Then show me what you have for sale.";
			link.l2.go = "trade";
		break;
		
		case "info":
			dialog.text = "Our small town was built thanks to the golden mine. They mine there golden ore, silver and golden nuggets. Sometimes even gems. We used to have here only a garrison until friendly Indians and some white settlers joined us\nIgnacio Ortega has built a tavern and made our life a bit cheerier. All kinds of adventurers visit this place with a stupid intention to rob us. We don't have a court here, so their numbers went low after we had hanged several idiots right in the middle of the town\nGolden ore is being sent to the ships under protection of soldiers and friendly Indians, nuggets, however, you can buy right here, in this store\nBesides, I sometimes have very interesting minerals to offer, so visit me when you've got time, I always resupply my stock.";
			link.l1 = "Thank you for the interesting story! I'll keep it in mind.";			
			link.l1.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Robbery in broad daylight!!! What's going on here?! Wait, hold on, pal...", "Hey, what are doing there?! Trying to rob me? Now you are screwed...", "Wait, what the hell are you doing? Turns out that you are a thief! Consider this the end of the line, bastard...");
			link.l1 = LinkRandPhrase("Devil!!", "Caramba!!", "Ah, shit!");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
