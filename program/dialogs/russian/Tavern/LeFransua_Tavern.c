// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?", "How can I help you, " + GetAddress_Form(NPChar) + "?"), "You tried to ask me some question not long ago, " + GetAddress_Form(NPChar) + "...", "Over this whole day, this is the third time you're talking about some question...",
                          "More questions, I presume?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Umph, where has my memory gone...",
                      "Yes, it really is the third time...", "No, what questions?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";						
			//Jason, Бремя гасконца
			if (CheckAttribute(PChar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "hire" && !CheckAttribute(npchar, "quest.storehelper"))
			{
				link.l1 = "Listen, " + npchar.name + ", I've come to you on an unusual matter. I need to find a man who would like a quiet, peaceful life on the bay as a merchant's assistant in a Saint-Pierre store. The salary is good and he'll have a roof over his head taken care of. Would you be able to suggest who I could turn to?";
				link.l1.go = "storehelper";
			}
			if (CheckAttribute(PChar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "seabattle" && !CheckAttribute(npchar, "quest.seabattle") && pchar.location.from_sea == "LeFransua_port")
			{
				link.l1 = "I'm here about the barrels of wine that you're about to load onto my ship for delivery to Guadeloupe...";
				link.l1.go = "seabattle";
			}
			//Бремя гасконца
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalLeFransua" && !CheckAttribute(npchar, "quest.portugal") && Pchar.location.from_sea == "LeFransua_port")
			{
				link.l1 = "You know, " + npchar.name + ", I'm looking for a friend of mine. He was supposed to arrive here and he was feeling off color. Perhaps his friends helped him out...";
				link.l1.go = "Portugal";
			}
			//Португалец
		break;
		
		case "storehelper":
			dialog.text = "Hm.. We have several people here who would like to switch from being a sailor to the life of a land rat. I could help you, but I'll tell you right now: it won't be for free.";
			link.l1 = "Heh! And how much do you want?";
			link.l1.go = "storehelper_1";
			npchar.quest.storehelper = "true";
		break;
		
		case "storehelper_1":
			dialog.text = "One thousand pesos. And there's nothing you'll have to do, in an hour your candidates for the job will be in my tavern, multiple candidates. You'll be able to talk with them and select the one that appeals more to you than the rest.";
			if (sti(Pchar.money) >= 1000)
			{
				link.l1 = "Ahh... Alright, here, take a thousand!";
				link.l1.go = "storehelper_2";
			}
			link.l2 = "I'm sorry, but I don't have that much money!";
			link.l2.go = "storehelper_exit";
		break;
		
		case "storehelper_2":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Don't worry, buddy. You'll get half of this amount back from the candidate. I'll tell him that that's the cost of your services, he he... They won't give any more than five hundred. Stop by my tavern in an hour by that time I'll have found the people you need here waiting for you.";
			link.l1 = "Okay. I'll be back in an hour, " + npchar.name + ".";
			link.l1.go = "storehelper_3";
		break;
		
		case "storehelper_3":
			DialogExit();
			pchar.quest.storehelper1.win_condition.l1 = "Timer";
			pchar.quest.storehelper1.win_condition.l1.date.hour  = sti(GetTime() + 1);
			pchar.quest.storehelper1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.storehelper1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.storehelper1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.storehelper1.win_condition.l2 = "location";
			pchar.quest.storehelper1.win_condition.l2.location = "lefransua_tavern";
			pchar.quest.storehelper1.function = "Storehelper_hire";
		break;
		
		case "storehelper_exit":
			dialog.text = "I'm sorry that you don't have that kind of money too. But you know yourself, matters like that don't get done just for a 'thank you'. So...";
			link.l1 = "I understand. But I really don't have the money. Alright, bye...";
			link.l1.go = "exit";
			pchar.quest.storehelper.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			CloseQuestHeader("SharlieA");
		break;
		
		case "seabattle":
			dialog.text = "What are you talking about, buddy? What wine do you speak of?";
			link.l1 = "I've been sent to you by a man named Walter Catcher. He said you needed a ship to transfer some wine cargo to Guadeloupe for ten thousand pesos. And that you need exactly my ship for this job...";
			link.l1.go = "seabattle_1";
			npchar.quest.seabattle = "true";
		break;
		
		case "seabattle_1":
			dialog.text = "Listen buddy, I don't deal with wine, I don't need your services, and I don't know any Walter Catcher.";
			link.l1 = "Fancy that! So, that Catcher wasn't sent from you at all... Then, what's this whole comedy about?";
			link.l1.go = "seabattle_2";
		break;
		
		case "seabattle_2":
			dialog.text = "Heh! Well, this is either some kind of mistake or a bad joke or...";
			link.l1 = "Or what?";
			link.l1.go = "seabattle_3";
		break;
		
		case "seabattle_3":
			dialog.text = "Don't you get it by yourself? Somebody needed to lure you over to Le Francois, for what I don't know. In your shoes, I'd hurry up and get out of here while being as careful as can be. This smells like dirty business, buddy...";
			link.l1 = "I suppose you're right. I didn't like that Catcher's mug. All right, I'll follow your advice. Bye, Cesar!";
			link.l1.go = "seabattle_4";
		break;
		
		case "seabattle_4":
			DialogExit();
			AddQuestRecord("Sharlie", "16");
			pchar.quest.seabattle.win_condition.l1 = "location";
			pchar.quest.seabattle.win_condition.l1.location = "Martinique";
			pchar.quest.seabattle.function = "SharlieSeabattle_ship";
		break;
		
		case "Portugal":
			dialog.text = "Yes, your friend's arrived here, captain. He got here yesterday and rented a room up above. His pals are here too, he-he... They're sitting over there. Ask them!";
			link.l1 = "...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			DialogExit();
			AddDialogExitQuestFunction("Portugal_enterPirates");
			npchar.quest.portugal = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

