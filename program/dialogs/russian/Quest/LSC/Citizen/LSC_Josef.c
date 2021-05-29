// Джозеф Лодердэйл - английский военный офицер
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
				dialog.text = "Good day, sir. I am glad to meet a noble man here.";
				link.l1 = TimeGreeting()+". Actually I have been so close to the common folks during my being at Archipelago so I have started to forget about my nobility...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetFullName(pchar)+"! Glad to meet you! What will you say?";
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
			dialog.text = "Oh, and you are even modest! A true gentleman! I think that we will be friends, you are not like that pompous Abbot... Let me introduce myself - Josef Loderdale, the former captain of English naval fleet.";
			link.l1 = "Glad to meet you. "+GetFullName(pchar)+" at your service!";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "It is quite boring to live here, so visit the tavern in the evening, we can have a glass of wine and an interesting conversation...";
			link.l1 = "I will keep that in mind, sir. See you!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Got anything interesting to say?", "Has anything new happened on the island?", "Will you tell me the last gossips?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "It would be my pleasure to answer your questions, mister...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "What kind of service I can get here?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Being a military officer, what's your opinion about pirates dominance here?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "I have seen a lot of locked chests here, on the Island. People don't trust each other, right?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Doing my military duties. I was fighting Spanish war sloop, we believed that it was the vessel responsible for plundering English traders. The fight was long, we almost got them, but the sudden storm ruined the game. As the result, both ships wrecked near the outer rings\nFortune has a sense of humor, me and Spanish captain survived. Perhaps, you have already met him here. His name is Lorenzo Solderra, a rare piece of scum. Be careful with him.";
			link.l1 = "Got it. I will consider your warning...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "If you need to rest - visit Sancho's tavern. He will always provide you with food, drinks and a bed. In case you want to get powder, ammo, weapons and other things - go to Axel Yost, he owns the local shop. Medicines can be bought from brother Julian, he also sells holy items in his church\nNarwhals have a very talented blacksmith, named Schmidt. They say that he crafts excellent blades. There is also another talented craftsman among the Narwhals, but I failed to learn more about him\n And if you are facing troubles with pirates or clans then see Giuseppe Fazio, he is the right specialist for such business.";
			link.l1 = "Thanks for the information!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "I can't say I like it, but there is nothing I can do about it. I admit, it took only a few day for the pirates to make peace and establish order on the Island. Before the pirates arrived, the clans were fighting each other on a regular basis and ordinary people suffered the most\nBesides, they sell food very neatly and fair - citizens get it for a very small price, can't say the same about the clans, pirates skin them alive as a revenge for starting a war\nI know a very smart man of pirates, his name is Layton Dexter. He is the one who does the trade. I had a talk with him once, I wonder how such a talented and well educated man, who knows tactics, cartography and trading, has joined the pirates\nIt took only a few days for him to make an excellent map of the Island. I saw it, it has almost everything. I believe he made it for a possible war against clans...";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "That's the right thing to do. They say that long before, a thievery was a normal thing on the Island until all chests got new locks. And yet, there is still someone who can lock pick chests. Though he only steals rum and cheap jewelry, never took any gold or money\nAll locks are unique, no same keys exist - Jurgen Schmidt made sure of that. He crafts not only blades but also locks and keys. I was told that outer chests don't contain valuables, serious items are always held inside the ships.";
			link.l1 = "Interesting...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("What are you doing there, ah? Thief!", "Just look at that! As soon as I was lost in contemplation, you decided to check my chest!", "Decided to check my chests? You won't get away with it!");
			link.l1 = "Shit!";
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