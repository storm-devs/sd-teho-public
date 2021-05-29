// Рамона Лоцано - горячая испанская сеньорита
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
				dialog.text = "Hello, hello! Newbie? Or were you hiding in cargo holds, since it is the first time I see your face around?";
				link.l1 = TimeGreeting()+". Hiding in cargo holds is not my type. I prefer the captain's place... Yes, I am a newcomer here.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Аh, "+pchar.name+"! "+TimeGreeting()+"! I am glad to see you! What say you";
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
			dialog.text = "Well, let's get to know each other then... captain. I am Ramona Lozano, but don't even try to call me senora Lozano, I hate it. What is your name?";
			link.l1 = ""+GetFullName(pchar)+". Pleasure to meet you, Ramona.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Are you really pleased or just being polite, "+GetFullName(pchar)+"? Tell me, are you really a captain or were you joking?";
			link.l1 = "Oho, so many questions at once! May I answer them in order? First, I am pleased for real, I don't meet pretty girls every day, second, I am a captain, it is true. But my ship is near the shores of Western Main now...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Funny! And how is that, captain? You are here, but your ship is near the shores of Main. Aren't you afraid that your crew will scatter around and your vessel will be taken from you?";
			link.l1 = "I have sailed here on a barque for... exploration, but all went wrong and I have found myself at your Island. Then we have bumped at some debris in the darkness, overturned and voila! Here I am. My ship will be waiting for me as long as I want. Dannie Hawk will be able to control my men.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Dannie Hawk? The Danielle Hawk? Do you wanna say that you float with her?";
			link.l1 = "Shit floats, Dannie serves me as my officer. She was left to command while I am missing... How do you know her?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Ha! Everyone in Spanish colonies knows pirate Danielle Hawk and her husband, Nathaniel. Yes, you, senor "+GetFullName(pchar)+", must be a tough guy... Are you a pirate then? Don't worry, I go along just fine with your kind. I like tough guys.";
			link.l1 = "Well, I am not really a pirate... I am just working at the moment with Jan Swanson and looking for Dannie's husband, Nathaniel.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "And are you going to tell me now that you aren't a pirate? Working for the Forest Devil, your first mate is Dannie Hawk and you are looking for Nathan Hawk... and I am sure that you have come here for admiral. Right?";
			link.l1 = "Ramona, you can call me pirate if you want, I am fine with that. You even may call me an anchor just don't throw me in water...";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "It seems that you are one of the really serious guys, "+pchar.name+". Fine, I have to go. See you! I have a feeling that we might be friends... a very close friends.";
			link.l1 = "Why not? Good luck!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Oh, really? Well, ask, I will answer if I can...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Surely, you haven't ever tried to get away from here...";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "How do you live here?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "What do you do here? I take it that the food is not for free, right?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "That's a long story... My stepfather is the one to be blamed. Four years ago I lived in Havana and I couldn't even imagine how things would turn out for me. My mother died and I was a heir at law. We were not rich, but we had plenty of money, more than enough for a decent living. My stepfather didn't like it and he decided to get rid of me\nOf course, I found it out only after two hired thugs attacked me right behind the city gates. Those fools told me themselves who hired them to kill me and why. Fortunately, they were not professionals, I would lay in the bushes with my throat cut if that was the case. The idiots decided to have some fun first\nThe fate has saved me that day, a captain like you was passing by to the gates. He saw the show and killed the scum immediately. They didn't stand a chance. I told him what happened to me and why. Cried a bit... He knew that I had nowhere to go, so he took me on his ship to live. First temporarily, and then\nI believe I would have stayed with him, but two months later he fought a patrol, lost a mast, was caught by a strong gale and found peace at the bottom of the outer ring. I survived despite everything and joined the community of the Island.";
			link.l1 = "Sad story, I have nothing to say...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Of course not. Because it's impossible. I saw a man who tried to leave this place on a longboat... he returned two days later. Tied to a wreck of a mast to save himself from drowning. He was blue and absolutely dead\nSo tell me, "+pchar.name+", what am I supposed to do as soon as I get away from here? Havana is too dangerous for me, the stepfather will try to kill me again. I have no house, no money. Where should I go? To the brothel?";
			link.l1 = "Still, do you want to get back to the archipelago?";
			link.l1.go = "ansewer_2_1";
		break;
		
		case "ansewer_2_1":
			dialog.text = "And how do you think? Sure, I want. But it is impossible and I've just told you why. Eh, if only someone could deal with my stepfather... with the sharp steel or bullet, then there would be some chance for me to get back to the normal life. But who would dare to do that if my stepfather is the best friend of Havana's alcalde? And why are we talking about that? There is no way out from here...";
			link.l1 = "We'll see. The time will come...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			// сюда направление на квест
		break;
		
		case "ansewer_3":
			dialog.text = "I live somehow. There is no other option. My friends are mostly the men because two of our marriageable beauties - Gillian and Tanneke don't like me because of my character and I feel sick of their decency for show. Natalie was a fine girl until she has started to spend a lot of time with these retards, stupidity is contagious.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "I work like other girls. Our primary goal is helping the men. There are a lot of work for women on the Island so I am quite busy. And I often get gifts it's a usual thing here. But don't think wrong about me, I am a not some wench. I was well educated in the proper family. I just don't play saint like someone does.";
			link.l1 = "I didn't think anything wrong about you...";
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
			link.l1 = LinkRandPhrase("Fine.", "Sure.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, I am the citizen of the city and I'd ask you to hold down your blade.", "Listen, I am the citizen of the city and I'd ask you to hold down your blade.");
				link.l1 = LinkRandPhrase("Fine.", "Sure.", "As you say...");
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