// Орели Бертин - просто жительница
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
				dialog.text = "Good day, mister. What will you say?";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+", I am a newbie here so I am getting to know locals.";
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
			dialog.text = "I see. My name is Orelie Bertine. How did you get here?";
			link.l1 = "Let's say that I just wanted to see the mystic Island of Justice.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "So you must be one of those crazies who come here of their own will... Well, now you will have enough time to see the Island and to eat plenty of its 'justice'.";
			link.l1 = "And are there any problems with justice according to your sarcasm?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "No, everything is fine. But for some reason we have to pay pirates for our food, which used to be free for all not long ago. And when the clans start fighting on our part of the Island, we are supposed to sit inside the ships to avoid being shot or butchered\nI mean that they are allowed to do whatever they want on our territory but we can't do the same on theirs. But it's alright, no more troubles...";
			link.l1 = "I see. Fine, I am glad to meet you. See you!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "I am listening.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Have you been living here for a long time?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Is there anything interesting on the Island?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "How do you feel about clans?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Are pirates bothering you?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "For a very long time. I have lost in my count already. It must be seventeen years... no, perhaps, eighteen... or is it twenty? What is the current year?";
			link.l1 = "I see... So are you an old-timer here?";
			link.l1.go = "ansewer_1_1";
		break;
		
		case "ansewer_1_1":
			dialog.text = "Relatively. I still remember times when buccaneers were trading with us and the most reckless and smart Narwhals were sailing to the mainland to trade provision in exchange for goods from ships' cargo holds. But there are a lot of people who haven't ever seen any places but only the Island because they were born here. They are not just old-timers here but natives.";
			link.l1 = "Interesting...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Yes, it is. Everything is interesting here. Walk around and see for yourself. Swim around the center part of the Island. Visit a tavern, a shop and a church. The problem is that the interest will fall down in a week, I can promise you that.";
			link.l1 = "Got it...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "And how are we supposed to think about those bandits? I am trying to stay away from them, that's all. At least Narwhals do some good to the Island, they have very talented craftsmen among them, but Rivados are just savages and pagans\nThey still live by their African laws just like hundreds years ago. Animals. The only thing they learned is to use firearms. They say that they commit rituals of cannibalism!";
			link.l1 = "Such a nightmare...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "The part where they sell us our own food is a bit bothering, but they don't do any harm to citizens. Actually, on the contrary, they brought the clans to order and prevent any violence\nThere was a citizen who was making problems and waving his saber. He even wounded two other locals. Pirates took him to Tartarus for a few weeks. Now the man is quite and peaceful. We don't see him often, the outer ring is his new home...";
			link.l1 = "I see...";
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
			link.l1 = LinkRandPhrase("Fine.", "Okay.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, I am the citizen of the city and I'd ask you to hold down your blade.", "Listen, I am the citizen of the city and I'd ask you to hold down your blade.");
				link.l1 = LinkRandPhrase("Fine.", "Okay.", "As you say...");
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