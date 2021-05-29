// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, tempQty, chComp, iShip, iBaseType;
    string tempStr;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad") && pchar.location == "villemstad_townhall")
			{
				dialog.text = RandPhraseSimple("What kind of questions?", "What would you like?");
				link.l1 = "I know that the Dutch West India Company has assigned a good price for the head of the famous pirate - Bartolomeo the Portuguese. I was able to capture him. He is currently in my ship's cargo and I am ready to hand him over to the authorities.";
				link.l1.go = "Portugal";
				break;
			}
            dialog.text = RandPhraseSimple("What kind of questions?", "What would you like?");
			link.l1 = "I have changed my mind...";
		    link.l1.go = "exit";
		break;
		
		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "Unfortunately, I can't offer you a job. You're not that type of people who I want to work with. Farewell.";
                link.l1 = "Seriously...";
                link.l1.go = "exit";
				break;
			}                   
		break;
		
		//Португалец
		case "Portugal":
			dialog.text = "Bart the Portuguese?! Do you have him? Alive?";
			link.l1 = "I know that you don't need him dead. He is alive. Damn! I had to make a lot of efforts to keep him that way!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Most excellent! Now he will tell us everything... Mynheer, prepare the prisoner for a transfer. We will send a military barque to your ship immediately. ";
			link.l1 = "I'd like to talk about my reward first, mynheer...If you don't mind.";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Don't worry about your reward, captain. You will get it. We have assigned a price for Bartolomeo the Portuguese's head - one thousand and five hundred doubloons. Lieutenant! Bring to the captain his reward!";
			link.l1 = "Hm... Seems that Hugo has lied to me about two thousand doubloons... Fine then.";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info("You have received 1500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "And now, captain, would you be so kindly to transfer the Portuguese to the Company. We just can't wait to have a talk with him.";
			link.l1 = "Sure, mynheer, send the barque to my ship.";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
