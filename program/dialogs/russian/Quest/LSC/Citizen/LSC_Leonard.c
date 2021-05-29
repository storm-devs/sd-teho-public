// Леонард Маскетт - пьяница
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iPeso, iDubl;
	string sPeso, sDubl;

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
			// --> пей до дна
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_3") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.facio"))
			{
				dialog.text = "Pal, you are just in time... I want to talk with you... about a business. An important one.";
				link.l1 = "Really? It looks like you are not drunk. Has anything happened? It is unusual to see you sober.";
				link.l1.go = "facio";
				break;
			}
			// <-- пей до дна
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "A-a... hic! Hello, pal...";
				link.l1 = TimeGreeting()+". It looks like you had enough already, pal.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Аh, "+GetFullName(pchar)+"! Hic! What do you want?";
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
			dialog.text = "Yeah! Enough? N-ope! I am a crazy drunk, hi-hic! Yes, Leonard Musket is drunk and that is a right thing!";
			link.l1 = "Fond of drinks, huh? Yes, my name is "+GetFullName(pchar)+". Nice to meet you.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "If you say so. We all here... hic, meet each other.";
			link.l1 = "Fine, it looks like you are not in a mood to talk. See you!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Got anything interesting to say?", "Has anything new happened on the island?", "Will you tell me the last gossips?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// --> пей до дна
		case "facio":
			dialog.text = "Yes, pal, I am almost sober. And that's because I have got a business for you, am important one. And it seems that you can do that...";
			link.l1 = "What? What is on you mind? Speak and don't waste my time for nothing!";
			link.l1.go = "facio_1";
			npchar.quest.facio = "true";
		break;
		
		case "facio_1":
			dialog.text = "Pal, do you want to make some money? Silver pesos, golden doubloons? I will tell you how. But you will have to share with me - we will work together.";
			link.l1 = "I always want to. But it all depends on your proposal: I don't do any work even if it's a very profitable one.";
			link.l1.go = "facio_2";
		break;
		
		case "facio_2":
			dialog.text = "The business is not really legal, sure, but it is profitable... and we will be able to punish one man who has become to choosy. He won't get poor, he has too much money. Everyone shares with him, so it is his turn to do the same now. Tell me, can you handle rum? How much are you able to drink before going under table?";
			link.l1 = "It depends. I am not sure that I have a habit for crazy drinking... Are you going to tell me details at last?";
			link.l1.go = "facio_3";
		break;
		
		case "facio_3":
			dialog.text = "I am getting to the point, you just don't see it yet. Fine. I'll be specific. There is a fat ugly bastard on the Island - Giuseppe Fazio. A rare scum. He skins alive Narwhals, Rivados and the locals. I have been watching him for a while and finally I have something\nThere are two chests in his cabin in Carolina: first contains papers, second contains gold and silver. Both of them are locked with different keys. Fat man always keeps the keys with himself.";
			link.l1 = "Well, it seems, that you are going to rob Fazio? I will not participate in that. And you'd better be glad that I won't tell anyone about it. If you want to check the fat man's chest than you should find another partner.";
			link.l1.go = "facio_exit";
			link.l2 = "Ha! Interesting! Go on...";
			link.l2.go = "facio_4";
		break;
		
		case "facio_exit":
			dialog.text = "To bad, really bad... There are a lot of gold, enough for both of us. Fine, see you around...";
			link.l1 = "Farewell.";
			link.l1.go = "exit";
		break;
		
		case "facio_4":
			dialog.text = "Two doors lead in his cabin. One of them is always locked. But the key which opens the chest with gold also opens the door. I don't know what's the whole point of this, but it's a fact. You only need one key to open the cabin and to get the gold. A logical question comes next - how to acquire the key? So, I have got a plan\nAn excellent plan, if it goes right, Fazio will never realize what happened and who to be blamed. They will think that it was the mysterious thief. Problem is, that I need a partner with a head of iron in order to get it done. Do you follow?";
			link.l1 = "I am listening. Go on.";
			link.l1.go = "facio_5";
		break;
		
		case "facio_5":
			dialog.text = "Fazio loves to sit at Sancho's and have a good drink, but his bulk is too heavy for rum to do its job. So he came up with a drinking game - the game where people try to over drink him. If you propose him to play this game, he will doubtlessly agree\nAnd then comes the fun part. You make a bet with him, go to the tavern, grab rum and drink until one of you kisses a table. If you flake out then the whole plan is failed, I won't be able to do it alone\nThat's why I asked about your head. If you will make Fazio squeak and grunt like a pig then consider it's done. I'll be around all the time. When he is finished, I will take his keys\nThen we move the fat man to a bed upstairs and sneak into his cabin while he is asleep. I'll return the key right after we loot his chest, he won't even realize that he was robbed\nI'll do the acquiring and returning the key, you mission is to get Fazio drunk and to sneak inside his property. I will stay on guard in case someone shows up, so you will have enough time to run away through the back door\nWe will split the chest's insides half-and-half, that would be fair. So, are you in?";
			link.l1 = "Nice plan! Sure, let's try!";
			link.l1.go = "facio_6";
			link.l2 = "No, pal. I'll pass. I fear that I won't be able to drink that much to stay on feet and to over drink Fazio. Find another partner, a bit stronger than I am.";
			link.l2.go = "facio_exit";
		break;
		
		case "facio_6":
			dialog.text = "I am glad that I was right about you. Now go to Fazio and arrange a meeting at the tavern in the evening after nine o'clock. I hope that you will over drink that pig. Good luck and see you in the evening!";
			link.l1 = "I will try... Bye!";
			link.l1.go = "facio_7";
		break;
		
		case "facio_7":
			DialogExit();
			NextDiag.CurrentNode = "facio_wait";
			pchar.questTemp.LSC.Drink = "begin";
			pchar.questTemp.LSC.Drink.Chance = drand(100); // итог бухалова
			if (CheckAttribute(pchar, "questTemp.CanDrink")) pchar.questTemp.LSC.Drink.Chance = sti(pchar.questTemp.LSC.Drink.Chance)+50;
			SetFunctionTimerCondition("LSC_DrinkOver", 0, 0, 3, false); // 3 дня
			AddQuestRecord("LSC_Drink", "1");
		break;
		
		case "facio_wait":
			dialog.text = "Pal, I am counting on you. Over drink that fat man...";
			link.l1 = "Sure...";
			link.l1.go = "exit";
			NextDiag.TempNode = "facio_wait";
		break;
		
		case "result_0":
			dialog.text = "It's done, that fat pig is sleeping upstairs. I have got the key. You are doing good, you seem to be sober enough!";
			link.l1 = "Is that so? It is been a long time since I got that drunk. Feeling a bit dizzy... Let's go?";
			link.l1.go = "result_win";
		break;
		
		case "result_1":
			dialog.text = "It's done, that fat pig is sleeping upstairs. I have got the key. You are doing good, you have really managed to over drink that piggy...";
			link.l1 = "I have, but it is been a long time since I got that drunk. My head is in a whirl... Let's go then?";
			link.l1.go = "result_win";
		break;
		
		case "result_2":
			dialog.text = "Eh, pal, you have failed to over drink the fat man... To bad. Well, at least we have tried...";
			link.l1 = "D-damn it, he is like some... bot-t-tomless barrel. Argh, I need to r-rest... It's over, g-get lost! Hic!..";
			link.l1.go = "result_fail";
		break;
		
		case "result_win":
			dialog.text = "Yes. Let's go! Follow me to 'Carolina'! And don't be wandering, we don't have much time!";
			link.l1 = "Let's go!";
			link.l1.go = "result_win_1";
		break;
		
		case "result_win_1":
			DialogExit();
			NextDiag.CurrentNode = "result_win_2";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6", "LostShipsCity_town", "reload", "reload39", "LSC_DrinkGotoCarolina", -1);
			AddQuestRecord("LSC_Drink", "3");
		break;
		
		case "result_win_2":
			pchar.quest.LSC_Drink1.over = "yes"; //снять таймер
			dialog.text = "Here. Take the key. The chest you need is on the left from the entrance. Take as much as you can quickly. Don't forget to lock it back. If I will see something I will knock the door three times. Run away through the rear gallery in that case.";
			link.l1 = "Fine. Be on your guard!";
			link.l1.go = "result_win_3";
		break;
		
		case "result_win_3":
			DialogExit();
			GiveItem2Character(pchar, "key_facioQ");
			NextDiag.CurrentNode = "result_grabbing";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload25", "LSC_DrinkGotoCarolina_3", -1);
		break;
		
		case "result_grabbing":
			// считаем деньги и дублоны взятые из сундука
			iPeso = sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money);
			iDubl = GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon);
			if (iPeso <= 0) sPeso = "not a single peso";
			else sPeso = ""+FindRussianMoneyString(iPeso)+"";
			if (iDubl <= 0) sDubl = "not a single doubloon";
			else sDubl = ""+iDubl+" doubloons";
			if (iPeso <= 10000 && iDubl <= 10) sTotalTemp = "What a miserable loot... And were we risking for it? Eh... Fine, let's share what we have got.";
			else
			{
				if (iPeso <= 50000 && iDubl <= 100) sTotalTemp = "I thought that there will be much more... Risk wasn't worth it. Eh... Fine, let's share what we have got.";
				else
				{
					if (iPeso <= 100000 && iDubl <= 300) sTotalTemp = "Hm. Not bad. But I thought that we will get more. Fine, let's share it.";
					else 
					{
						if (iPeso <= 150000 && iDubl <= 500) sTotalTemp = "Excellent! We have done well, partner! This is a whole lot of coins! Let's share!";
						else
						{
							sTotalTemp = "Wow! I haven't ever thought that the fat man's stash is so huge. Well done, partner! Let's share!";
						}
					}
				}
			}
			dialog.text = "At last! What had you managed to take from the chest of that scoundrel? Show me, I am waiting with impatience!";
			if (iPeso <= 0 && iDubl <= 0)
			{
				link.l1 = "There were nothing at all. Just a few scraps, amulets and such stuff.";
				link.l1.go = "grabbing_0";
			}
			else
			{
				link.l1 = "I have taken from the chest "+sPeso+" и "+sDubl+"";
				link.l1.go = "grabbing_1";
			}
		break;
		
		case "grabbing_0":
			dialog.text = "Impossible! It seems that it all was for nothing... Perhaps that bastard has put his stash in another chest. Eh! Fine, give me the key and I will return it back to its owner until he won't miss it. Farewell, pal...";
			link.l1 = "...";
			link.l1.go = "grabbing_exit";
			AddQuestRecord("LSC_Drink", "6");
		break;
		
		case "grabbing_1":
			dialog.text = sTotalTemp;
			link.l1 = "Let's share...";
			link.l1.go = "grabbing_part";
		break;
		
		case "grabbing_part":
			iPeso = makeint((sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money))/2);
			iDubl = makeint((GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon))/2);
			AddMoneyToCharacter(pchar, -iPeso);
			RemoveItems(pchar, "gold_dublon", iDubl);
			Log_Info("You have given "+iDubl+" doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Fine, give me the key and I will return it back to its owner until he won't miss it. Farewell, pal...";
			link.l1 = "Good luck, pal...";
			link.l1.go = "grabbing_exit";
			AddSimpleRumourCityTip("Fazio was complaining that someone has cleaned out his chest. It seems that the mysterious thief did that.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("Have you heard? Fazio was robbed! He was robbed while being drunk after having a game with you.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("You have a strong head! To drink so much rum and stay on your own feet! That 's something...", "LostShipsCity", 3, 2, "LSC", "");
			AddQuestRecord("LSC_Drink", "5");
		break;
		
		case "grabbing_exit":
			DialogExit();
			RemoveItems(pchar, "key_facioQ", 1);
			int n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			LocatorReloadEnterDisable("CarolineBank", "reload1", false); // на галерею
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload38", "FleuronTavern", "goto", "goto2", "OpenTheDoors", 15.0);
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
		break;
		
		case "result_fail":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "LostShipsCity_town", "goto", "goto05_2", "", 10);
			chrDisableReloadToLocation = false;//открыть локацию
			n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "4");
		break;
		// <-- пей до дна
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Really?... hic! I am listening...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you end up here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Do you always drink? And where do you find coins for drinks?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "What can you tell me about locals?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Would you like to leave this place and go to the mainland?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Yeh! I swear, I don't remember. Yes, yes, I don't! It was long time ago. I was sailing somewhere somehow and finally ended up here. Hic!";
			link.l1 = "Hm... All right, all right.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Yes, I am a drunkard… Drinking, damn it, because I have nothing left to do… You see, pal, I am done. The bottle of rum is the only thing I want. So I will continue drinking. And money... he-he, rum doesn't cost much. Anyway, I don't even have to buy it\nThere is a place filled with rum, but you need to swim if you want to get it, that is why I buy rum only when I am too drunk to swim... hic! Jizjezezejizeze, no, I won't tell you where to swim, he-he, don't even ask...";
			link.l1 = "Wonderful.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "What can I say, hic... about them? Good people to talk and to drink. Giuseppe Fazio is such an important man, a local bigwig, his chests are filled with gold... and yet he respects old Leo, buys him drinks at the tavern. Though, sometimes he also asks something in return, but it's nothing, hic!\nHeh, don't you know how many doubloons Fazio owns, aha-ha-ha! Enough to spend the rest of your life in the best house of all the Caribbean not working and drinking the best rum in the world. But he stays here, on the Island. Still not enough money for him it seems...";
			link.l1 = "Got it...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_4":
			dialog.text = "To leave? Hic! Why? No, I don't want to go neither to the mainland nor to the poor island. Is there any free rum? No! There is no any free rum, hic! And it means that it is nothing to do for me there... Pal, I am feeling fine here. I will tell you more - ask people do they want to leave this place. No one does, except of two or three, hic!";
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