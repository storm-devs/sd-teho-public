// диалог начальника шахты
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		location = &Locations[FindLocation(pchar.location)];
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("You dare to show your face here?! Don't know, you're brave or stupid...", "How did these lazybones let an enemy break into my residence? This is beyond me...", "Surely, my guards aren't worth a copper, if you, bastard, are running around here..."), 
					LinkRandPhrase("What do you need,"+ GetSexPhrase("scoundrel","stinker") +"?! My soldiers have already been set on your trail, "+ GetSexPhrase(", filthy pirate","") +"!", "Dirty murderer, leave my residence immediately! Guards!", "I am not afraid of you, "+ GetSexPhrase("rat","slut") +"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Soldiers aren't worth a single peso...", "They will never get me."), 
					RandPhraseSimple("Shut up your piehole, " + GetWorkTypeOfMan(npchar, "") + ", or I'll rip out that foul tongue of yours!", "I'd tell you, buddy: sit quietly, and maybe, you'll get through it alive..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Enemy in the mine! Alarm!";
				link.l1 = "Aaah, devil!";
				link.l1.go = "fight"; 
				break;
			}	
			dialog.text = LinkRandPhrase(""+TimeGreeting()+", senor. I am "+GetFullName(npchar)+", the mining engineer of the Los-Teques mine. What is it that you need here?","Hello, senor. What did you want?","Hmm... did you want anything from me, senor? I am listening.");
			if (!CheckAttribute(location, "quest.info"))
			{
				link.l9 = "I am a new one here, and I would like to learn more about this mine...";
				link.l9.go = "info";
			}
			if (GetSquadronGoods(pchar, GOOD_SLAVES) > 4)
			{
				link.l2 = "I have a cargo in my hold which might be interesting to you. Slaves for your mine, to be exact. Want to haggle?";
				if (!CheckAttribute(location, "quest.slaves")) link.l2.go = "slaves_0";
				else link.l2.go = "slaves";
			}
			link.l1 = "I just came in to say hi, and I am already leaving.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "Los-Teques  mine extracts gold for the Spanish Crown. Everything we extract belongs to Spain. We also find here not only gold but also silver nuggets and valuable precious stones. We don't sell gold here, everything we extract is delivered to the Old World under a reinforced convoy\nBut we have two exceptions for golden and silver nuggets. First, you can buy some amount of them in our local store from a quartermaster. Sometimes salary doesn't get here in time, so we have to keep some savings of coins here for such cases, that is why local trading is allowed\nSecond, we constantly experience a need of manpower, so we exchange nuggets for slaves. Therefore, talk to me if you have something to offer, we will do business\nI believe that rules of conduct of the mine are obvious: don't steal, don't distract convicts and don't bother soldiers otherwise you won't like the consequences.";
			link.l1 = "Okay, thank you!";			
			link.l1.go = "exit";
			location.quest.info = "true";
		break;
		
		// генератор купли-продажи рабов
		case "slaves_0":
			location.quest.slaves.qty = 200; // стартовая потребность
			dialog.text = "Of course, senor! How many do you have?";
			link.l1 = "I have "+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SLAVES))+".";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves":
			location.quest.slaves.qty = sti(location.quest.slaves.qty)+GetNpcQuestPastDayParam(location, "slave_date"); // каждый день дает +1 потребности
			if (sti(location.quest.slaves.qty) > 350) location.quest.slaves.qty = 350; // максимум потребности
			if (sti(location.quest.slaves.qty) < 5)
			{
				dialog.text = "Senor, unfortunately, right now we have no need in more slaves. But the situation can change anytime, so check back in a few weeks or some other time.";
				link.l1 = "Alright, senor, I understand. You don't need them now, but you might need them in some time.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Of course, senor! How many do you have?";
				link.l1 = "I have "+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SLAVES))+".";
				link.l1.go = "slaves_1";
			}
		break;
		
		case "slaves_1":
			dialog.text = "For every slave, I am willing to pay you either one gold ingot or two silver ingots. What do you choose?";
			link.l1 = "Gold ingots.";
			link.l1.go = "slaves_g";
			link.l2 = "Silver ingots.";
			link.l2.go = "slaves_s";
			link.l3 = "I am sorry, senor, but I've just changed my mind. Some other time.";
			link.l3.go = "slaves_exit";
		break;
		
		case "slaves_g":
			location.quest.slaves.type = "gold";
			dialog.text = "Fine. How many slaves are you going to sell me?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_s":
			location.quest.slaves.type = "silver";
			dialog.text = "Fine. How many slaves are you going to sell me?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_trade":
			iTotalTemp = sti(dialogEditStrings[6]);
			if (iTotalTemp < 1)
			{
				dialog.text = "Senor, I have no time for stupid jokes. If you're in a mood for jesting, go to the tavern!";
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > GetSquadronGoods(pchar, GOOD_SLAVES))
			{
				dialog.text = "Senor, I think that you need to rest. Perhaps you're very tired or got a heatstroke. Go to the tavern, have a good rest, and then we can continue our bargaining.";
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > sti(location.quest.slaves.qty))
			{
				dialog.text = "Unfortunately, senor, right now we don't need that many slaves. The mine currently requires "+FindRussianQtyString(sti(location.quest.slaves.qty))+". Are you going to sell that many?";
				link.l1 = "Yes, of course!";
				link.l1.go = "slaves_max";
				link.l2 = "Hmm... I guess, I am not.";
				link.l2.go = "slaves_exit";
				break;
			}
			dialog.text = ""+FindRussianQtyString(iTotalTemp)+"? Excellent. Please order to bring them to the town gates. I'll send my men for them.";
			link.l1 = "Don't worry, senor. Your slaves will be delivered to you in time. I will issue all relevant orders immediately.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_max":
			iTotalTemp = sti(location.quest.slaves.qty);
			dialog.text = "Excellent. Please order to bring them to the town gates. I'll send my men after them.";
			link.l1 = "Don't worry, senor. Your slaves will be delivered to you in time. I will issue all relevant orders immediately.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_calk":
			DialogExit();
			Log_Info("Exchange of slaves for ingots has been completed");
			PlaySound("interface\important_item.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,5,10);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, iTotalTemp);
			if (location.quest.slaves.type == "gold") TakeNItems(pchar, "jewelry5", iTotalTemp);
			else TakeNItems(pchar, "jewelry6", iTotalTemp*2);
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
			location.quest.slaves.qty = sti(location.quest.slaves.qty)-iTotalTemp;
		break;
		
		case "slaves_exit":
			DialogExit();
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		    LAi_group_Attack(NPChar, Pchar);
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
