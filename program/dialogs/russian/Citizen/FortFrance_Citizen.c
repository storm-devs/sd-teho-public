// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What kind of questions?", "What would you like?");
			link.l1 = RandPhraseSimple("I have changed my mind...", "I have got nothing to say now.");
		    link.l1.go = "exit";
			//Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && !CheckAttribute(npchar, "quest.Sharlie"))
			{
				link.l1 = "Excuse me, "+GetAddress_FormToNPC(NPChar)+" could you tell me where I can find Michel de Monper? He has to be somewhere in your town.";
                link.l1.go = "Sharlie";
			}	
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "findskiper" && !CheckAttribute(npchar, "quest.Sharlie1"))
			{
				link.l1 = "Listen, "+GetAddress_FormToNPC(NPChar)+", I want to ask something... I am looking for a navigator to serve on my ship, do you know anyone in your town?";
                link.l1.go = "Sharlie_1";
			}
			//Бремя гасконца
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Do you think I work for the secret service of "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Well... farewell then.";
			link.l1.go = "exit";
			link.l2 = "Another question then";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Am I the information bureau for you? Don't know. Don't know a thing.";
            link.l1 = "You're such a muddle-headed! Bye.";
			link.l1.go = "exit";
			link.l2 = "Another question then";
			link.l2.go = "new question";
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			if (sti(pchar.questTemp.Sharlie.Citcount) == 3)
			{
				dialog.text = "Hmm... I see that you've arrived here recently if you fearlessly ask such questions... I advice you to stop it or you'll get troubles otherwise. And about your question... Talk to the Abbot. You can find him at the church.";
				link.l1 = "Gratitude!";
				link.l1.go = "exit";
				AddDialogExitQuest("Sharlie_SetBenua");
			}
			else
			{
				dialog.text = LinkRandPhrase("No, I don't know this name.","Can't help you. I have to go, bye.","Sorry, I have never heard that name before. So..");
				link.l1 = "I see... Sorry for troubling you. ";
				link.l1.go = "exit";
				pchar.questTemp.Sharlie.Citcount = sti(pchar.questTemp.Sharlie.Citcount)+1;
				npchar.quest.Sharlie = "true";
			}
		break;
		
		case "Sharlie_1":
			dialog.text = LinkRandPhrase("No, I don't know any navigators, so...","I have no idea. I have to go, bye.","Unfortunately, I can't help you, sorry...");
			link.l1 = "I see. Pardon me...";
			link.l1.go = "exit";
			npchar.quest.Sharlie1 = "true";
			npchar.dialog.currentnode = "first time";
		break;
		//<-- Бремя Гасконца
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}