// Альваро Гомец - капитан
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
				dialog.text = "Oh, a new face! Greetings. And when did you get here? I don't remember any recent shipwreck.";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+". And my ship has sunk so quietly and quickly that nobody noticed. And I got to the Island quickly and quietly too. Just like that...";
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
			dialog.text = "I see, Oh, I forgot to introduce myself. Pardon me, senor. My name is Alvaro Gomez and I was once a captain of my own brig. Eh, now my fine brig is lying at the bottom right behind the outer ring... Much water has flowed under the bridge since then. Ah, whatever. Glad to meet you!";
			link.l1 = "Glad to meet you too, senor Gomez.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Got anything interesting to say?", "Has anything new happened on the island?", "Will you tell me the last gossips?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "I am listening, senor.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "You said that you had been a captain. How did you get the island?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "What can you tell me about life on the island?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Tell me, do locals live here in peace or they don't? I am not talking about clans, of course.";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "And where from do locals get provision?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Just as anyone else did. The storm caught me, I lost my mast and steering control. We were taken by the current and thrown to the reefs. My ship didn't even get to the outer ring and was destroyed. Only a few men survived.";
			link.l1 = "Sad story...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "What can I say? We have everything we need for proper living. Though sometimes it gets really dull here. And that melancholy... First year was the worst, but I got used to it later. I feel bad for my poor wife Sabrina, she must be sure that I died. I do hope she managed to marry again\nDon't be upset, you'll get used to it. Visit the tavern, the store, the church, meet other folks. Don't go to Narwhals or Rivados until you really have to, they are tricky bastards.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "True, quarrel and fights are secretly forbidden here. If you beat someone without a proper reason or, God forbid, kill, than you'll end up being isolated. You might been even throw overboard one night. There were a few brawlers before on the Island. First had just disappeared, second died in a cell of Tartarus after months spent inside\Sure, it doesn't mean that you can't protect yourself. But locals are quite peaceful actually. Abbott is a swanky, but not aggressive. Kassel is a real bastard, but he keeps his hands clean. Pratt is an ex convict, but he is harmless\nWe have two ex navy officers here - Loderdale and Solderra. They got here while having a battle not far away. Ironically, both of them survived to keep making bloodthirsty plans against each other.";
			link.l1 = "Got it...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "From holds, of course. All provision, gathered from other ships, were used to be stored in St. Augustin and shared between everyone until pirates showed up. Now they squeeze the Island in their fist because they own supplies\nSure, we have got our own stashes, so it's fine. We also shoot birds and do fishing... But the best hunt ends with killing a giant crab. They have a very tasty and nourishing meat. Though they can been seen only at the outer ring\nDiving to hunt them is too risky. There was the one who brave enough to hunt them underwater. One day he became a prey himself. No one wants to hunt crabs there since then.";
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
			link.l1 = LinkRandPhrase("Fine.", "Sure.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, I am the citizen of the city and I'd ask you to hold down your blade.", "Listen, I am the citizen of the city and I'd ask you to hold down your blade.");
				link.l1 = LinkRandPhrase("Fine.", "Whatever then.", "As you say...");
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