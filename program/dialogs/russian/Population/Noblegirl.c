//Jason общий диалог дворянок
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//первая встреча
            if(NPChar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
				{
					dialog.text = "Hm. You are sailing under the flag of "+NationNameGenitive(sti(pchar.nation))+", captain. I have no wish to talk with the enemy of my country. Get lost!";
					link.l1 = "Ah, yes. A patriot...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = RandPhraseSimple("What do you want from me, "+GetAddress_Form(NPChar)+"? It doesn't appropriate for sailor to talk with a noble lady, but I am listening to you.", "Oh, and what does such a brave captain want from me?");
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". I won't take much of your time, just want to ask...";
					link.l1.go = "question";
					link.l2 = RandPhraseSimple("I need to know what is going on in your colony.", "I need some information.");
					link.l2.go = "quests";//(перессылка в файл города)
				}
				npchar.quest.meeting = "1";
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Should I repeat myself? I don't want to be suspected as a friend of "+NationNameAblative(sti(pchar.nation))+"! Leave or I will call the guards! They would be glad to talk with you.";
					link.l1 = "Fine, fine, calm down. I am leaving.";
					link.l1.go = "exit";
				}
				else
				{
				dialog.text = NPCStringReactionRepeat("What? You again? Look for someone else to talk. There are a lot of marginals walking around. I have to go now, there will be a banquet tonight in the governor's residence and my haircut is not ready yet!", 
					"No, now it is really annoying! Don't you just get it? Or are you a slow minded?", 
					"Sir, I am beginning to suspect that you are not an idiot but a hick and a boor. I warn you that I will call my husband if you don't stop bothering me with your stupid questions!",
					"One more word and I'll tell the commandant to do something with you!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("I see. Farewell.", 
					"Yes-yes, I remember, just forgot to ask...",
					"You got me wrong...", 
					"Calm down, my lady, I am leaving already...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				}
			}
			NextDiag.TempNode = "First time";
		break;

		//сюда вставляем любые проверки и направления на квесты
		case "question":
			dialog.text = LinkRandPhrase("Alright, let's listen.","Oh, fine. What do you want?","Questions? Fine, sailor, I am listening.");
			link.l1 = LinkRandPhrase("Can you tell me the last gossip of this town?","Have anything interesting happened here recently?","Any news from the archipelago, my lady?");
			link.l1.go = "rumours_noblegirl";
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Are you insane?! You scared me! Sheathe your weapon or I will tell the commendant to hang you in the fort!", "Are you insane?! You scared me! Sheathe your weapon or I will tell the commendant to hang you in the fort!");
			link.l1 = LinkRandPhrase("Fine.", "As you wish.", "Okay.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
