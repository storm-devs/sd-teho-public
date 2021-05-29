// Лайонел Маскетт - мещанин
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "I don't want to talk with you. You attack peaceful civilians with no reasons and provoke them to fight. Get lost!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Greeting, "+GetAddress_Form(NPChar)+". Are you a newcomer here?";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+". Yes, I am.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Аh, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Want something?";
				link.l1 = LinkRandPhrase("Got anything interesting to say?", "Has anything new happened on the island?", "Will you tell me the last gossips?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to know how you're doing. See you!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "My name is Lionell. Nice to meet you. How did you get here?";
			link.l1 = "On a barque... I heard that there is some smuggler's base and decided to explore it... Explored. The barque is sunk and I am here.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Do they really consider the Island as a smugglers' base?";
			link.l1 = "Well, not officially. The majority doesn't even believe in your existence.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Seriously... And why should they? We don't actually exist. You can't leave this place. Though they say that there were a connection with Cuba... But I don't remember that and I have been living here for almost eight years.";
			link.l1 = "I see. It was my pleasure to talk with you. See you!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Got anything interesting to say?", "Has anything new happened on the island?", "Will you tell me the last gossips?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "I am listening.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Would you like to return to the mainland?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "And what do people do here, on the Island?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "And where do you get all things here? Food, cloth, drinks?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "That is an odd story. This Island is the only place of all Caribs I saw. When things went bad for me, I sailed on a trade ship from old England. I was going to find a job in Belize, to be a clerk of harbor office. But we have never made it to Belize\nI am no sailor, so I don't know details. A storm happened and the next day our ship was destroyed with reefs. I will never forget that terrible blow, the screaming\nSomeone shouted that there was a hole in the hull, people started to jump overboard. Me... I can't swim. So I stayed. Ironically, that saved my life. The ship survived and the storm calmed down at dawn\nI did the only right decision before I left the ship. I took some food, built a raft and sailed through a peaceful sea to the outer ring. That's how I survived, the one of the whole crew.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "It was my only dream for the first two years here. But now… What makes the Island worse than any other place in the world? Yes, there are no green fields with sheep, but there is a magnificent sea and a night sky filled with beautiful stars. I am well fed, I wear a decent cloth, which I couldn't afford while living in England. I have a lot of friends\n No, sir, I don't want to leave this place. What is waiting for me out there? A desk job under clamorous boss for three hundred pesos per week? No way! I have found everything I was looking for here, I need nothing else.";
			link.l1 = "Got it. Glad for you!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "What they like the most. Clans play in war, pirates sell provision, Axel Yost buys and sells stuff, Sancho Carpentero serves drinks and entertains people, brother Julian prays, says Mass and sells medicines. Loderdale and Solderra are intriguing against each other, Abbot likes to be puffed up, Jillian and Tanneke dreams about true love...";
			link.l1 = "Interesting...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "From the ships, my friend, from the ships. The favorite activity of the majority is exploring vessels from the outer ring and getting stuff from them. You can find everything there, weapons, medicines, spices and rum. A lot of ships are still unexplored. The sea current often brings here an another victim...";
			link.l1 = "Interesting...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("What are you doing there, ah? Thief!", "Just look at that! As soon as I was lost in contemplation, you decided to check my chest!", "Decided to check my chests? You won't get away with it!");
			link.l1 = "Damn it!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "What?! Decided to check my chests? You won't get away with it!";
			link.l1 = "Foolish girl!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Listen, you'd better take your weapon away. It makes me nervous.", "You know, running with blade is not tolerated here. Take it away.", "Listen, don't play a medieval knight running with a sword around. Take it away, it doesn't suit you...");
			link.l1 = LinkRandPhrase("Fine.", "Alright.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, I am the citizen of the city and I'd ask you to hold down your blade.", "Listen, I am the citizen of the city and I'd ask you to hold down your blade.");
				link.l1 = LinkRandPhrase("Fine.", "Alright.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Be careful, pal, while running with a weapon. I can get nervous...", "I don't like when men are walking in front of me with their weapon ready. It scares me...");
				link.l1 = RandPhraseSimple("Got it.", "I am taking it away.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}