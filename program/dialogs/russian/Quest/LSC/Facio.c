// посредник-дипломат кланов Джузеппе Фацио
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hello, hello... Are you a new one here? I don't recall your face. Allow me to introduce myself - I am Giuseppe Fazio, a specialist in solving problems on this small island.";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+". You are right, I am a new one here. Forgive my curiosity - but what kind of problems do you solve?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, you again, dear "+pchar.name+"! What brings you to my humble house?";
				if (CheckAttribute(pchar, "GenQuest.NarvalConflict") || CheckAttribute(pchar, "GenQuest.RivadosConflict") || CheckAttribute(pchar, "GenQuest.SharkConflict"))
				{
					link.l10 = "Fazio, I have a serious conflict with one clan. I need to solve this problem.";
					link.l10.go = "conflict";
				}
				// --> квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_3")
				{
					link.l4 = "Giuseppe, I am looking for a man by the name of Adolf Barbier. I've been told that you had been drinking with him at the tavern recently...";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && pchar.questTemp.LSC.Drink == "begin")
				{
					link.l5 = "Giuseppe, they say that you are completely resistant to drinks. No matter how much you drink, you still stand on your feet.";
					link.l5.go = "drink";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && GetCharacterItem(pchar, "gold_dublon") >= 100 && pchar.questTemp.LSC.Drink == "wait")
				{
					link.l5 = "I am ready to play your game. Here is my stake.";
					link.l5.go = "drink_4";
				}
				// <-- квестовые ветки
				if (CheckAttribute(npchar, "quest.parol"))
				{
					link.l1 = "I want to know the current password of the clans to enter their territories.";
					link.l1.go = "parol_choice";
				}
				link.l2 = LinkRandPhrase("Got anything interesting to say?", "Has anything new happened on the island?", "Will you tell me the latest gossips?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Nothing special, Giuseppe. Just wanted to see you.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "All sorts, my dear, all sorts. For example, I smooth things up between admiral and clans. As you might already know, Rivados, Narwhals and admiral are mutual enemies. I act as a mediator when things get tricky.\nBesides, I often play a role of a neutral side when admiral sells provision to the clans. But this is just a tiny part of my business. So if you have troubles with Rivados or Narwhals - don't hesitate to ask for my assistance, we'll see what can be done.";
			link.l1 = "Fine. I will consider that.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// пароли
		case "parol_choice":
			dialog.text = "What clan?";
			link.l1 = "Narwhals.";
			link.l1.go = "parol_nrv";
			link.l2 = "Rivados.";
			link.l2.go = "parol_rvd";
		break;
		
		case "parol_nrv":
			dialog.text = "Want to see Donald Greenspen, am I right?";
			link.l1 = "Correct. So do you know the password?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Narwals";
			sTotalTemp = sNrvParol;
		break;
		
		case "parol_rvd":
			dialog.text = "Want to see Black Eddie, am I right?";
			link.l1 = "Something like that. So do you know the password?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Rivados";
			sTotalTemp = sRvdParol;
		break;
		
		case "parol":
			if (!CheckAttribute(npchar, "quest.parolrules"))
			{
				dialog.text = "Sure! But let me give you some details first. Passwords contain only one word and change every week. Every seventh, fourteenth, twenty first and twenty eighth day of month\nSo watch the current date to avoid any mistakes. Finally, as you must understand, it's not a charity. Fifty doubloons for a password. Remember, doubloons only.";
				link.l1 = "Fifty doubloons? This is a huge sum!";
				link.l1.go = "parol_1";
			}
			else
			{
				dialog.text = "Sure, my boy. You know the price. Do you have fifty doubloons?";
				if (GetCharacterItem(pchar, "gold_dublon") >= 50)
				{
					link.l1 = "Yes. Take your coins.";
					link.l1.go = "parol_pay";
				}
				link.l2 = "Unfortunately, I don't. Perhaps later...";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "parol_1":
			dialog.text = "Well-well, my boy, calm down. Don't be greedy, trust me: I know the real price of my information. You aren't going just to walk around the ships of "+pchar.questTemp.LSC.parol+" right? Right. So you have to be ready to loose some coin... So, are you ready to pay fifty doubloons?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 50)
			{
				link.l1 = "Yes. Take your coins.";
				link.l1.go = "parol_pay";
			}
			link.l2 = "Unfortunately, I don't have such money. Perhaps later...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
			npchar.quest.parolrules = "true";
		break;
		
		case "parol_pay":
			RemoveItems(pchar, "gold_dublon", 50);
			dialog.text = "Great! Nice doing business with you. The current password for "+pchar.questTemp.LSC.parol+" is: '"+sTotalTemp+"'. Remember it well and don't make a mistake or I won't give a single coin for your life.";
			link.l1 = "I know, I know... Thanks!";
			link.l1.go = "exit";
			AddQuestRecord("LSC", "parol");
			AddQuestUserData("LSC", "sText", pchar.questTemp.LSC.parol);
			AddQuestUserData("LSC", "sParol", sTotalTemp);
			if (pchar.questTemp.LSC.parol == "Rivados") pchar.questTemp.LSC.RParol_bye = "true";
			else pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "adolf":
			dialog.text = "Ah, but of course, my good old Adolfo! Yes, I had a talk with him. See, my dear, I was glad to have my money back, the money I thought I would never see again! Adolfo borrowed a big sum on a collateral of his outstanding rifle and he had troubles with returning my money\nI lost any hope to get them back and was going to sell that stutzen to our beloved Axel Yost. But suddenly dear Adolfo brought me my gold! Turned out that he managed to get coins enough not only to redeem his stutzen, but also to buy a Sessile Gallard's cabin at the head of the 'Santa Florentina'!\nSure, this is much better than living in a half-watered hold\nTherefore, Adolfo has his rifle back, a new home and I have my money. Why could I refuse to have a drink with him, especially when he was buying?";
			link.l1 = "Ah, sure! You had a lot of things to drink to. And for free... Thanks, Giuseppe, you have helped me a lot. Now I know where to find Adolf.";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "It's always my pleasure, dear. But don't look for Adolfo in his cabin until evening comes, he is very busy, running around with some business... Yeah, and visit me more often, have a talk!";
			link.l1 = "I will invite you when I have my own cabin... Farewell and good luck!";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			DialogExit();
			LSC_CreateAdolfClone(); // заменяем Адольфа клоном
			pchar.questTemp.Saga.SharkHunt = "search_mush_4"; //флаг на Адольфа в каюте
			AddQuestRecord("SharkHunt", "14");
		break;
		
		case "whiskey":
			switch (sti(npchar.quest.poisonnode))
			{
				case 1: // у себя
					dialog.text = "Ah? Why are you invading my place like there is a fire? Who do you think you are??";
					link.l1 = "Your justice... poisoner!";
					link.l1.go = "whiskey_1";
				break;
				
				case 2: // на Эве
					dialog.text = "Spare me! I swear, they have forced me! They have put a gun against my...";
					link.l1 = "Shut up. I know that. Where is the last bastard? Where is Marcello Cyclops?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
				
				case 3: // у Акулы
					dialog.text = "I swear, they have forced me! I have already told the admiral everything! I couldn't resist them, they would...";
					link.l1 = "Shut up. I know that. Where is the last bastard? Where is Marcello Cyclops?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
			}
		break;
		
		case "whiskey_1":
			dialog.text = "What... what did you say?";
			link.l1 = "I know everything, bastard. You have been working with Chad Kapper. You have brought a barrel with poisoned rum to admiral. Now pray, you miserable fag...";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Wait! Stop! Spare me! I swear, they have forced me! They had a gun against my...";
			link.l1 = "Shut up. I know that. Where is the last bastard? Where is Marcello Cyclops?!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "I... I.... I don't know!";
			link.l1 = "You are lying, scum! I see that. Where is Cyclops?";
			if (pchar.questTemp.LSC.Mary == "die") link.l1.go = "whiskey_10"; // ушел на Флерон
			else link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "He... he received some order from Kapper and has gone. I don't know where he is!";
			link.l1 = "Lying again. You know everything. Don't be a coward, you filthy creature - Kapper is dead and he won't harm you. But if you don't tell me where Marcello is - I will slaughter you like a pig right now! What did Chad order to Cyclops?";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "He sent him to kill... Red Mary.";
			link.l1 = "What?! Speak now, how is he going to do that? It is impossible to get inside her cabin! How is he planning to kill her?!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			dialog.text = "He will get inside Jurgen's cabin while the blacksmith is out. Then he will move to the bottom of the hold, cross it and reach Mary's cabin\nThen the only thing he will need is to wait until the girl turns her back or falls asleep. That is what Chad told me. I know nothing more, I swear!";
			link.l1 = "That will be enough. When did he go? When, I ask you, did Cyclops go to the 'Ceres Smithy'?";
			link.l1.go = "whiskey_7";
		break;
		
		case "whiskey_7":
			dialog.text = "He must already be in Jurgen's cabin... or getting down inside the cargo hold...";
			link.l1 = "Fuck! I don't have time to swim around the Island! Tell me the password to Narwhals ships! Speak, and if you lie to me, I will stay alive anyway, but you will die for sure!";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "'"+sNrvParol+"'...";
			link.l1 = "Got it. Now pray that the girl will survive.";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "whiskey_repeat";
			pchar.quest.LSC_RescueMary.win_condition.l1 = "location";
			pchar.quest.LSC_RescueMary.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_RescueMary.function = "LSC_RescueMary";
			AddQuestRecord("SharkHunt", "46");
			AddQuestUserData("SharkHunt", "sParol", sNrvParol);
			pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "whiskey_repeat":
			dialog.text = "I have already told you everything I knew! I swear!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "whiskey_repeat";
		break;
		
		case "whiskey_10":
			dialog.text = "He... He is somewhere inside the 'Fleron'. Chad has ordered him to hide there and wait for his next orders.";
			link.l1 = "I see. It'd better be the truth...";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.LSC_FindCyclop.win_condition.l1 = "location";
			pchar.quest.LSC_FindCyclop.win_condition.l1.location = "FleuronTavern";
			pchar.quest.LSC_FindCyclop.function = "LSC_SetCyclop_Fl";
			NextDiag.CurrentNode = "whiskey_repeat";
			AddQuestRecord("SharkHunt", "51");
			
		break;
		
		// --> конфликты
		case "conflict":
			dialog.text = "Is that so? Well, my boy, what clan is troubling you?";
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				link.l1 = "Narwhals.";
				link.l1.go = "narval";
				npchar.quest.clan = "narval";
			}
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				link.l2 = "Rivados.";
				link.l2.go = "rivados";
				npchar.quest.clan = "rivados";
			}
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				link.l3 = "Admiral's pirates.";
				link.l3.go = "shark";
				npchar.quest.clan = "shark";
			}
			link.l4 = "No such thing. I was joking, Giuseppe, I am fine.";
			link.l4.go = "exit";
		break;
		
		case "narval":
			npchar.quest.price = sti(pchar.GenQuest.NarvalConflict)*50;
			if (sti(pchar.GenQuest.NarvalConflict) < 3) dialog.text = "Well, it's not actually a conflict, just a small misunderstanding, he-he. "+sti(npchar.quest.price)+"  doubloons and your problem will be solved in a day.";
			else
			{
				if (sti(pchar.GenQuest.NarvalConflict) >= 3 && sti(pchar.GenQuest.NarvalConflict) < 10) dialog.text = "Sure, I have heard about it. You made a big mess, my dear. But there is a way out. "+sti(npchar.quest.price)+" doubloons and your problem will be solved in a day.";
				else dialog.text = "The entire Island is aware of the slaughter you did. It won't be easy to help you, but there is a chance. "+sti(npchar.quest.price)+" doubloons and I will try to solve your problem.";
			}
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.price))
			{
				link.l1 = "Here, take your coins and deal with it.";
				link.l1.go = "pay";
			}
			link.l2 = "Unfortunately, I don't have enough doubloons with me right now. But I will bring them later, and we shall talk again.";
			link.l2.go = "exit";
		break;
		
		case "rivados":
			npchar.quest.price = sti(pchar.GenQuest.RivadosConflict)*50;
			if (sti(pchar.GenQuest.RivadosConflict) < 3) dialog.text = "Well, it's not actually a conflict, just a small misunderstanding, he-he. "+sti(npchar.quest.price)+"  doubloons and your problem will be solved in a day.";
			else
			{
				if (sti(pchar.GenQuest.RivadosConflict) >= 3 && sti(pchar.GenQuest.RivadosConflict) < 10) dialog.text = "Sure, I have heard about it. You made a big mess, my dear. But there is a way out. "+sti(npchar.quest.price)+"  doubloons and your problem will be solved in a day.";
				else dialog.text = "The entire Island is aware of the slaughter you did. It won't be easy to help you, but there is a chance. "+sti(npchar.quest.price)+" doubloons and I will try to solve your problem.";
			}
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.price))
			{
				link.l1 = "Here, take your coins and deal with it.";
				link.l1.go = "pay";
			}
			link.l2 = "Unfortunately, I don't have enough doubloons with me right now. But I will bring them later, and we will talk again.";
			link.l2.go = "exit";
		break;
		
		case "shark":
			npchar.quest.price = sti(pchar.GenQuest.SharkConflict)*50;
			if (sti(pchar.GenQuest.SharkConflict) < 3) dialog.text = "Well, it's not actually a conflict, just a small misunderstanding, he-he. "+sti(npchar.quest.price)+" doubloons and your problem will be solved in a day.";
			else
			{
				if (sti(pchar.GenQuest.SharkConflict) >= 3 && sti(pchar.GenQuest.SharkConflict) < 10) dialog.text = "Sure, I have heard about it. You made a big mess, my dear. But there is a way out. "+sti(npchar.quest.price)+" doubloons and your problem will be solved in a day.";
				else dialog.text = "The entire Island is aware of the slaughter you did. It won't be easy to help you, but there is a chance. "+sti(npchar.quest.price)+" doubloons and I will try to solve your problem.";
			}
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.price))
			{
				link.l1 = "Here, take your coins and deal with it.";
				link.l1.go = "pay";
			}
			link.l2 = "Unfortunately, I don't have enough doubloons with me right now. But I will bring them later, and we will talk again.";
			link.l2.go = "exit";
		break;
		
		case "pay":
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.price));
			PlaySound("interface\important_item.wav");
			Log_Info("You have given "+sti(npchar.quest.price)+" doubloons");
			dialog.text = "Splendid. Now take a seat and have a rest. You'd better stay in my cabin until I solve your problem. I don't want you to make it even worse, my dear.";
			link.l1 = "Fine...";
			link.l1.go = "peace";
		break;
		
		case "peace":
			DialogExit();
			GetCharacterPos(pchar, &locx, &locy, &locz);
			pchar.locx = locx;
			pchar.locy = locy;
			pchar.locz = locz;
			SetLaunchFrameFormParam("One day later..."+ NewStr() +"Fazio has dealt with the conflict", "Reload_To_Location", 0.1, 5.0);
			SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
			WaitDate("", 0, 0, 1, 3, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			switch (npchar.quest.clan)
			{
				case "narval":
					DeleteAttribute(pchar, "GenQuest.NarvalConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") || !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false);//открыть вход к Дональду
					LAi_group_SetRelation("LSC_NARVAL", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "rivados":
					DeleteAttribute(pchar, "GenQuest.RivadosConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend") || !CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload33", false);//открыть вход к Эдди
					LAi_group_SetRelation("LSC_RIVADOS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "shark":
					DeleteAttribute(pchar, "GenQuest.SharkConflict"); // мирим
					LSC_OpenSanAvgustinDoors(); // открыть сан-августин
					LSC_OpenTartarusDoors(); // открыть тартарус
					LAi_group_SetRelation("LSC_SHARK", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
			}
			DeleteAttribute(npchar, "quest.clan");
			DeleteAttribute(npchar, "quest.price");
		break;
		
		// --> пей до дна
		case "drink":
			dialog.text = "Come on, my boy! Lying, they are all lying, he-he. My head is just a bit tougher than an average head, but I am a human being just like you are, so I also get drunk with rum. People drink rum to get drunk, that is its only purpose. Have you ever thought about that, dear?";
			link.l1 = "Quite true.";
			link.l1.go = "drink_1";
		break;
		
		case "drink_1":
			dialog.text = "Do you want to play some funny game with me? It's called 'drink to the dregs!', ha-ha! I am sure, that you have already heard about it. Am I right?";
			link.l1 = "Yeah, there were some whispers about it... I'd call it 'face on the table'.";
			link.l1.go = "drink_2";
		break;
		
		case "drink_2":
			dialog.text = "Ha-ha-ha, my dear boy, you have made the old man laughing, what else can I say! 'Face on the table!' I'll remember it... So what do you say? Play for a hundred doubloons?";
			link.l1 = "Hundred doubloons?";
			link.l1.go = "drink_3";
		break;
		
		case "drink_3":
			dialog.text = "Yes, and the loser pays for the drinks. Deal?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 100)
			{
				link.l1 = "Yes, deal. Here is my stake.";
				link.l1.go = "drink_4";
			}
			link.l2 = "Hm. I don't have that many doubloons.";
			link.l2.go = "drink_wait";
		break;
		
		case "drink_wait":
			dialog.text = "Well, come and see me when you have them, and we'll play!";
			link.l1 = "Fine...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Drink = "wait";
		break;
		
		case "drink_4":
			RemoveItems(pchar, "gold_dublon", 100);
			Log_Info("You have given 100 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Excellent, my dear! Then see me at nine p.m. in Sancho's tavern! Yes, your stake will stay with me if you are late, this is one of the rules. But you won't be late, my boy, will you?";
			link.l1 = "Sure, Giuseppe. Prepare for a bottle fight!";
			link.l1.go = "drink_5";
		break;
		
		case "drink_5":
			dialog.text = "And you, and you, my dear! Face on the table! Ha-ha!";
			link.l1 = "See you at nine in the tavern!";
			link.l1.go = "drink_6";
		break;
		
		case "drink_6":
			DialogExit();
			pchar.questTemp.LSC.Drink = "start";
			pchar.quest.LSC_DrinkOver.over = "yes"; //снять таймер
			pchar.quest.LSC_Drink.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink.win_condition.l1.date.hour  = 21.0;
			pchar.quest.LSC_Drink.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink.function = "LSC_DrinkPrepare";
			pchar.quest.LSC_Drink_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.hour  = 23.0;
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink_Over.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "2");
		break;
		
		case "drink_8":
			dialog.text = "Well, my dear, are you ready to kiss a table, he-he? Good Sancho has already brought us rum. No need to tell you the rules I guess? They are pretty simple: we drink the same bottle until one of us is down.\nYes, we can talk, we should talk! Talking with decent people is great, isn't it? And if you win, you may get your prize from Sancho. Ready?";
			link.l1 = "I'd say yes. Let's start, Giuseppe!";
			link.l1.go = "drink_9";
		break;
		
		case "drink_9":
			DialogExit();
			pchar.questTemp.LSC.Drink = "go";
			pchar.quest.LSC_Drink_Over.over = "yes"; //снять таймер
			ChangeCharacterAddressGroup(pchar, "FleuronTavern", "quest", "sit1");
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);
			ChangeCharacterAddressGroup(npchar, "FleuronTavern", "quest", "sit2");
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			DoQuestFunctionDelay("LSC_DrinkGo", 0.6);
		break;
		
		case "drunk":
			dialog.text = "Fift-een me-eeen on th-the dead... hic! Aha! Yo-ho-ho-kha... And... bottle...";
			link.l1 = "Glorious...";
			link.l1.go = "exit";
			NextDiag.TempNode = "drunk";
		break;
		// <-- пей до дна
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}