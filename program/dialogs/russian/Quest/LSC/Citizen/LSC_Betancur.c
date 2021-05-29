// Антонио Бетанкур - потомок Франциско Бетанкура
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
				dialog.text = "Hello, Hello... What do you want, friend?";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+". And I just wanted to know who you are. See, I am newly arrived, walking around the city and talking with people.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Аh, "+GetFullName(pchar)+"! "+TimeGreeting()+"! What do you want this time?";
				if(CheckAttribute(pchar, "questTemp.LSC.Betancur"))
				{
					link.l4 = "Antonio, they say that you know the Island's history well. I have a question for you about it.";
					link.l4.go = "dolly";
				}
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
			dialog.text = "Splendid. And you will do well, because we are all a big family here. Except for Narwhals and filthy Rivados of course. My name is Antonio, Antonio Betancourt. I am the grandson of Francisco Betancourt in case this name means anything to you.";
			link.l1 = "Francisco Betancourt? I have heard this name before... Ah, sure! Dios told me about him and I read about him in the Alvarado's notes...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "I have no idea who is this Dios of yours, but captain Alvarado visited us long ago. I've seen him personally when I was a kid. He sailed away from the island and wrote about it in his manuscripts. And Francisco Betancourt was a Spanish admiral, a commander of military squadron\nHe started the history of this place due to a fact that all Rivados are offsprings of black slaves from Tartarus, the flagship of squadron. Narwhals are children of the first white settlers, crewmembers of Tartarus, San Augustine and San Geronimo.";
			link.l1 = "Incredible! So were you born here?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Exactly. I am a straight offspring of a man who basically occupied the Island.";
			link.l1 = "I see. Glad to meet you, Antonio. See you.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестовая часть
		case "dolly":
			dialog.text = "Hm... Sure, friend, ask me. I will answer your questions, of course but only if I know the answers.";
			link.l1 = "Tell me, do you remember the time when galleon San Geronimo was still here?";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Sure, I do. It was a very special ship. There was an interesting Indian statue and these filthy pagans Rivados were performing sacrificial offerings.";
			link.l1 = "And how were they doing that? Were they taking people's hearts away like the Maya? Or were they chopping off heads?";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = "No... It was a very special statue - it dragged victims into itself and they disappeared forever. The tool of the devil... Thank God it has sunk with the ship and will never do any harm. It's quite interesting that sacrifices were always made in the same time in the morning. The statue used to turn to gold under the light of rising sun\nThat was when the savages were bringing victims, mostly the Narwhals they captured.";
			link.l1 = "Interesting! And had somebody ever tried to explore how does the statue work?";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "Of course not! First, Rivados did not let anyone except their own to come close to San Geronimo and, secondly, an honest Catholic must keep a distance from devil's actions.";
			link.l1 = "Got it. I see that you don't like Rivados. Am I right?";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Do I? I hate those dirty pagans! In case you don't know, my granddad was a captain of the ship where Negros with their leader Rivados mutinied. Leaving their so called leader to rot inside the hold was a right thing to do. I also had a gorgeous key from St. Anna's treasury\nNo one knows where to find the treasury, perhaps it's at the bottom of the sea with crabs around, but the key was a sweet memento to me and yet it was stolen! I am sure that black ones did it. They must be trying to find the treasury. I doubt that they will succeed, it has been too long, ha-ha! Scum...";
			link.l1 = "I see. Thanks for your interesting story!";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "You are welcome, I am always glad to talk!";
			link.l1 = "Farewell!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Betancur");
			AddQuestRecord("LSC", "16");
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "I am listening, pal.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "So haven't you seen anything else but the Island in your life?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "You were born here... And why aren't you a member of Narwhal clan? I thought that all native white people were Narwhals...";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "And what do you do on the Island?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Tell me, have you ever wanted to leave the Island for while? To see the world...";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Seems so, yes. But don't think that I am an idiot or narrow-minded. I have inherited a fine library from my granddad and my father provided me with an excellent education. I know ancient history, geography, astronomy, I know English, French, Spanish and even Latin\nA lot of sailors who have been everywhere know less than I do. Even though I have not seen anything except these ship wrecks, I mentally visited Europe, China and India...";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "It is not true, though you are ninety percent correct. But I am not Narwhal and I don't want to become one of them. For what purpose? To stand guard for hours like a fool or to fight with Rivados? Not a chance, spare me from that. I am different. I prefer to live independently and read books.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Father left me a decent inheritance and I spend it carefully. So I don't need to lurk around old ship wrecks to find some jewels to trade for food. I don't believe in great treasures inside old ships\nThe only treasure I know is the St. Anna's treasury. It is a big iron chest. But no one has managed to find it yet\nAlso, I am going to write a detailed history of the Island based on local stories. How do you think - should I try?";
			link.l1 = "I am sure of it. I know at least one man at the Archipelago who would pay for such book a lot of gold. So it's your chance...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Sometimes I think about it. Perhaps if the ship which would be able to handle with the current and survive storms would have come here, I'd take a risk. I am really eager to see things which are so interestingly described in my books! But these are just dreams for now...";
			link.l1 = "Dreams come true. Just believe in them...";
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