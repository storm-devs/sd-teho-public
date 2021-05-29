// брат Юлиан - священник
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;

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
				dialog.text = "I have no wish to talk with you. You attack peaceful locals with no reason and provoking them to fight. Get lost, atheist!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "I am not surprised that you have survived. Mysterious are the ways of the Lord. Life and death are in His hands.";
				link.l1 = "I completely agree with you, brother Julian.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Welcome to the saint church of our Island, my son. The doors are always opened for you. I am brother Julian and I am glad to see any servant of our great Lord.";
				link.l1 = TimeGreeting()+". . My name "+GetFullName(pchar)+". . Glad to meet you, brother Julian.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Аh, "+GetFullName(pchar)+"! "+TimeGreeting()+"! ! Want something?";
				link.l1 = "I want to ask you a few questions about the island.";
				link.l1.go = "int_quests"; //информационный блок
				link.l2 = "Can I buy some potions from you?";
				link.l2.go = "potion";
				link.l3 = "Do you have any saint items to sell?";
				link.l3.go = "amulet";
				link.l5 = "Just wanted to pray here and to know how you're doing. See you!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "I hope that you will visit our church more often. Take care of your soul, my son. I am also able to heal your body, I work here not only as a pastor, but also as a doctor.";
			link.l1 = "I want to ask you a few questions about the island.";
			link.l1.go = "int_quests"; //информационный блок
			link.l2 = "Can I buy some potions from you?";
			link.l2.go = "potion";
			link.l3 = "Do you have any holy items to sell?";
			link.l3.go = "amulet";
			link.l4 = "I have to go, brother Julian. See you!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "potion":
			dialog.text = "Sure, my son. What potion do you need?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "A simple healing potion.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "A healing elixir.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "An antidote.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "A herbal mixture.";
				link.l4.go = "potion4";
			}
			link.l5 = "I am sorry, brother Julian, I have changed my mind.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "A potion? 90 pesos, my son.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Take them, brother Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "I don't have enough coins now... I will back later.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "An elixir? 500 pesos, my son.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Take them, brother Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "I don't have enough coins now... I will back later.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "An antidote? 200 pesos, my son.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Take them, brother Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "I don't have enough coins now... I will back later.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "A mixture? 900 pesos, my son.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Take them, brother Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "I don't have enough coins now... I will back later.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "Here. Take your medicine. May the God guide you!";
			link.l1 = "Thank you, brother Julian.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
		break;
		
		case "amulet":
			bool bOK = (!CheckAttribute(npchar, "amulet_date")) || (GetNpcQuestPastDayParam(npchar, "amulet_date") >= 3)
			if (bOk && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > (10+drand(110)))
			{
				npchar.quest.amulet = SelectLSCChurchAmulet();
				dialog.text = "Yes, I can give you some holy amulets which protect people from wounds and illnesses. The price is same for any amulet - ten golden doubloons. I can offer you "+XI_ConvertString(npchar.quest.amulet)+" today.";
				if (GetCharacterItem(pchar, "gold_dublon") >= 10)
				{
					link.l1 = "Yes, I want buy this amulet. Here is your gold.";
					link.l1.go = "amulet_pay";
					link.l2 = "I have this amulet already, brother Julian. I will wait until you've got what I need.";
					link.l2.go = "exit";
					SaveCurrentNpcQuestDateParam(npchar, "amulet_date");
				}
				else
				{
					link.l1 = "I don't have enough coins now... I will be back later.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "No, my son, unfortunately I have nothing else. Come and see me in the other day, perhaps, I will find anything for you.";
				link.l1 = "Deal, brother Julian.";
				link.l1.go = "exit";
			}
		break;
		
		case "amulet_pay":
			RemoveItems(pchar, "gold_dublon", 10);
			GiveItem2Character(pchar, npchar.quest.amulet);
			Log_Info("You have received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Thank you, my son. Your money will serve well. Take your buy and may the God bless you!";
			link.l1 = "Gratitude, brother Julian.";
			link.l1.go = "exit";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "I am listening.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here, brother Julian?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "How many people are in your parish?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Who sells things here?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Is there any risk of destruction for the Island? Storms, perhaps?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. I am sorry...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "By the same way as many of locals, my son. My ship was sunk by a storm during my voyage from Havana to the New Spain. Thank God, I survived it and now I serve Him here, helping poor souls to find their true path.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Less than I want. Most of Narwhals prefer violence to mercy and Rivados are poor and lost sheep. They are blindly perform their pagan trials and putting their immortal souls at risk. There is one dangerous wizard among them and he must be purified by the Saint Inquisition.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Sancho Carpentero owns tavern on the Fleron, you can find there food, drinks and a warm bed. Axel Yost sells a big variety of goods on the 'Esmeralda'. Ask people on the streets, my son, a lot of them are finding interesting things at the outer ring.";
			link.l1 = "Thank you!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "It is all in the hand of our Lord, my son. We believe in Him and we trust Him. Serious troubles have always been staying away from our Island - storms often happen outside it, but it is always quiet here.";
			link.l1 = "Thanks. You have reassured me.";
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

string SelectLSCChurchAmulet();
{
	string sAmulet;
	switch (drand(3))
	{
		case 0: sAmulet = "amulet_2"; break;
		case 1: sAmulet = "amulet_3"; break;
		case 2: sAmulet = "amulet_6"; break;
		case 3: sAmulet = "amulet_7"; break;
	}
	return sAmulet;
}