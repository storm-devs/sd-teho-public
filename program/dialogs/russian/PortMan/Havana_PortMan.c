// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "You've already tried to ask me a question " + GetAddress_Form(NPChar) + "...", "You have been talking about some question for the third time today...",
                          "Look, if you have nothing to tell me about the port's matters then don't bother me with your questions.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind.", "I've got nothing to talk about."), "Nevermind.", "Indeed, the third time already...", "Sorry, but I'm not interested in the port's matters for now.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Good day to you. I'd like to learn about a corvette named '" + pchar.questTemp.Slavetrader.ShipName + "' under the command of Francois Gontier.";
                link.l1.go = "Havana_ratP_1";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Excuse me, has a man by the name of Joachim Merriman arrived at your port? A middle-aged senor, Portuguese, with moustache, imperial beard and piercing eyes?";
				link.l1.go = "caleuche";
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && !CheckAttribute(npchar, "quest.Mtraxx"))
			{
				link.l1 = "I am interested in a ship named 'Cantavro'. I am looking for its captain - Esberdo Cabanas, on a private matter. Could you help me?";
				link.l1.go = "mtraxx";
			}
		break;
		
		case "Havana_ratP_1":
			dialog.text = NPCStringReactionRepeat("Yes, he was here. But he has gone already. Ask our tavern keeper about him, he has rented a room in the tavern.", "You have already asked about this and I've answered.", "I tell you that you have already asked about this Gontier..", "I ask you to don't bother me!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Thanks. I'll do that.", "Hm, well ...", "Yes, I have really asked ...", "Pardon, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Can't tell you anything about him. Even if he arrived there, he never registered anywhere.";
			link.l1 = "I see. Such a pity... Alright, I'll continue my search ...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
			dialog.text = "Let's see... Schooner 'Cantavro' set sail two days ago. Mission - patrolling... however, the location is not listed. It is a military vessel, so destination point is known only to its captain and the fort commandant. I would suggest you talking with the commandant directly, you can find him at the fort, if you wish to know more. Unfortunately, that is all I can do for you.";
			link.l1 = "I see. Well, thank you for your time...";
			link.l1.go = "exit";
			npchar.quest.Mtraxx = "true";
			AddQuestRecord("Roger_1", "5");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
