// Жаклин Тьюрам - торговый капитан
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
				dialog.text = "Good day, monsieur. You are new here, aren't you?";
				link.l1 = TimeGreeting()+". Yes, I suppose that I am the newest here. My name is "+GetFullName(pchar)+". And what is yours?";
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
			dialog.text = "Jacqueline Turam. Two years ago I was a decent and wealthy merchant, an owner and a captain of my own flute. Alas, now I am as poor as a church mouse and I can't hope that my situation will change somehow\nSome people get lucky here - they find jewels, gold, ships filled with treasures, but I am not one of them. I found only a chest with doubloons and few trinkets\nAt least that's enough to buy food, so I don't starve... Pleasure to meet you, sir, I don't mind chatting...";
			link.l1 = "I am glad to meet you too, Jacqueline. See you!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Got anything interesting to say?", "Has anything new happened on the island?", "Will you tell me the last gossips?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "I am all ears.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "What do you do here?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Tell me, I see that there are girls and women on the Island...";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Do you want to get back, to the big world?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "It's nothing.";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Do you want to hear my story? Fine. As you already know, I was a trade captain. One day I sailed from Tortuga to Belize on my good old flute. My holds were filled with black wood and cacao, I had spent all my coins on the cargo\nI arranged a very profitable deal with one man, he wanted to buy my cargo for an extremely high price. I could make a fortune on that deal. All was going well, not a single cloud in the skies, my ship was as fast as a bird. We didn't expect troubles\nI was sailing near Cuba, staying away from Spanish patrols, but suddenly we were attacked by a pirate galleon. What were they doing there - in the middle of Spanish territory? We tried to flee, but we failed, the galleon was surprisingly fast\nThe pirates chased us and attacked. Their coulevrines were loaded with grape shot, the first salvo damaged my crew badly and had it demoralized. I wanted to give them a good fight, but my own crewmen and officers stopped me. We surrendered\nThe pirates quickly took our cargo and threw away our cannons. I thought it was the end. Loosing the cargo was a heavy blow, but I still could make money on freights and one day stand on my feet again\nBut it turned out differently. The pirate bastards opened fire at my defenseless flute. We were a perfect shooting target\nI can still remember them laughing... The galleon sailed away and we were floundering, holding the wrecks. Then a strong gale with waves came and I have never ever seen anyone from my crew since then. I managed to tie myself to a mast's part and to stay afloat\nI'll save you from extra details about shark attack. After some eternal period time I was brought here by a sea current. That's how I survived.";
			link.l1 = "Yes, it is really a sad story.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "I live like the rest of locals - I just live. I search valuables at the outer ring and exchange them for food. I dream about finding an Indian king's chest filled with treasures... Or at least a galleon with Spanish gold, he-he. Don't pay much attention, it's just me\nI dream about eating something different from corned beef and fish. Eh, there was a man here, he was hunting those giant crabs. I used to pay five doubloons for a claw and feed on it for several days\nPity that the hunter died... though I can't say that it wasn't expected - hunting those things is a very dangerous activity.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "I see what you are implying at. Yes, love and intrigues exist here. And why wouldn't they? The man is made for the woman and so is the woman is made for the man. Nature. You may try with Gillian and Tanneke. They are young, pretty and don't mind courting\nI have found myself a woman - Natalia. She is a waitress in Sancho's tavern. A great girl, I tell you. I believe she is the only reason why I didn't lose my mind during the first months of living here. She has helped a lot and now we are together.";
			link.l1 = "Hm... I got it!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Good question. I'd like that, of course. But to think about it... I am broken. I have invested everything in the cargo and my ship is sunk. I have nothing left for living. The only way to earn money for me is working for Dutch West India Company if they hire me of course\nIf only I had enough money to buy a schooner and enough supplies... So I'd better stay on the Island. At least I don't have to work here from dawn to dawn for a piece of bread.";
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