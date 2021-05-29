// Таннеке Эверс - просто девушка
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
				dialog.text = "Good day! Do I know you? I haven't seen you before, that's for sure...";
				link.l1 = TimeGreeting()+". It is true, I am a new... visitor here. My name is "+GetFullName(pchar)+" and I am a captain.";
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
			dialog.text = "Have you been a captain?";
			link.l1 = "Why have I been? I am still a captain...a-ah, I got it! You think that my ship is sunk or destroyed by the reefs. No. She is near the shores of Western Main. And I have reached this place on a barque, it ended bad though, the barque got a hole in her hull and sunk.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Have you come here on a barque? And how did you manage to survive the storm?";
			link.l1 = "What storm? I don't remember any storm...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "But how is that? There is always a storm around the Island. All people say that.";
			link.l1 = "Well, it is not or I was lucky enough to bypass it. The sea was absolutely calm... excuse me, may I know a name of such a pretty lady?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Oh! I am sorry, I forgot to introduce myself... My name is Tanneke. Nice to meet you.";
			link.l1 = "Nice to meet you too, Tanneke... It's my pleasure.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "And why have you decided to reach our Island on a barque? A-ah, I get it - you were driven by the current right to it. No one knows about the Island and people always get here by chance.";
			link.l1 = "It's not correct. There are quite true gossips about the Island including its location. So I have decided to see it with my own eyes...";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Now I see. You are just like Adolf Barbier, read too much of captain Alvarado and decided to search for admiral de Betancourt's gold. Alas, captain, if such a cunning rogue as Barbier has failed to find it, then I doubt that you will succeed either\nAnd I really think that there is no admiral's gold, Antonio must have just thought it up to show us what an important man his granddad was... Well, you will stay with us then. Getting here was easy, but leaving must be impossible. Leaving here in one piece, I mean.";
			link.l1 = "It's nothing. I think that I will be able to deal with that, I don't mean the gold of Betancourt you have mentioned - it's the first time I hear about it, I mean leaving the Island. Alive. It was my pleasure to talk with you, Tanneke. See you!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ask away, captain...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Have you ever tried to leave the Island?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "How do you live here?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Do girls need to buy food from admiral and do they get it for free?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "I am Dutch, but we had been living in Santiago. My parents sent me to work as a servant girl for the family of banker Geraldi. Have you heard of them? Three years ago one of them sailed to New Spain on a courier lugger. I was told to accompany him. On the second day of our voyage, we were caught by a brigantine under the Spanish flag\nTheir officer came aboard out ship and had a talk with our captain, the captain got mad and drove the officer away. We were attacked as soon as the guest reached his ship. We tried to flee, but they managed to board us. As far as I understood, they needed my master Geraldi, because they rushed inside a cabin, captured and took him away. Me and sailors were taken to the hold and left there.\n I though that they will sink us but they just sailed away. Sailors managed to leave the hold but our captain was killed in combat and no one of the survivors knew how to navigate a right course. We were sailing somewhere for sometime until the strong gale took us\n Few hours later our lugger was thrown at the outer ring. It is still there. I was lucky enough to survive the mess, after the dawn me and a few other 'lucky' people have reached the Island.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "No. And how do you imagine that? There are no ships ready to sail here and using a longboat is as good as signing a death sentence yourself. As I said, storms are often here. I remember only the one try to leave this place - five citizens had built a decent longboat with sails and oars\nThey fought the current for several hours and then finally reached the open sea. Few days later one of them returned to the outer ring... tied to a wreck of a mast and dead. This killed other's wishes to do such brave things.";
			link.l1 = "Got it...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "It's alright. It's not worse than to be a servant of that arrogant usurer's family. You just need to get used to this place and after that you may even love it. By the way, I am not the only one who think like that. And clans... they don't bother me.";
			link.l1 = "Interesting...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Of course we buy. Oh, captain, there is enough work for a girl: cleaning, cooking, helping others… we don't sit idle but no one break backs here. Pirates sell food cheap for the common citizens, as opposed to the clans. So we don't starve\nI help Gillian and Natalie and they help me if I need. We are friends. There is another girl on the Island, the Spanish. Her name is Ramona but she is mostly on her own and we are not really eager to be friends with her.";
			link.l1 = "And why is that?";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Well... let's say that we have got different points of view on the life. Talk to her and you'll understand.";
			link.l1 = "Interesting...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("What are you doing there, ah? Thief!", "Just look at that! As soon as I was lost in contemplation, you decided to check my chest!", "Decided to check my chests? You won't get away with it!");
			link.l1 = "Crap!";
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
			dialog.text = LinkRandPhrase("Listen, you'd better take your weapon away. It makes me nervous.", "You know, running with blade is not tolerated here. Take it away.", "Listen, don't play a medieval knight running with a sword around. Take it away it doesn't suit you...");
			link.l1 = LinkRandPhrase("Fine.", "As you wish...", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, I am the citizen of the city and I'd ask you to hold down your blade.", "Listen, I am the citizen of the city and I'd ask you to hold down your blade.");
				link.l1 = LinkRandPhrase("Fine.", "As you wish...", "As you say...");
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