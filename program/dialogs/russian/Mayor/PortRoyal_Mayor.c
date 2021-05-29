// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want? Ask away.", "I am listening to you, what's the question?"), "It is the second time you are trying to ask...", "It is the third time you are again trying to ask...",
                          "When is it going to end?! I am a busy man, working on the colony's matters and you are still trying to ask something!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...", "Not now. Wrong place and time."), "True... But later, not now...",
                      "I'll ask... But a bit later...", "I am sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_8")
			{
				link.l1 = "Your Excellence, I would like to report an illegal trading activity on this island.";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_12")
			{
				link.l1 = "I would like to hear a report on your mission regarding the silk sailcloth smuggling.";
                link.l1.go = "Mtraxx_4";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_10_continue" && !CheckAttribute(npchar, "quest.slaveships"))
			{
				link.l1 = "I arrived on the behalf of Governor-General Phillip de Poincy. My job is to bring to you the slaves captured from the Dutch, is that right?";
                link.l1.go = "patria_Sl";
			}
			if (CheckAttribute(npchar, "quest.slaveships.wait") && GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000)
			{
				link.l1 = "I brought you the slaves, as agreed.";
                link.l1.go = "patria_Sl_2";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_start" && CheckAttribute(pchar, "questTemp.Patria.Curacao.DoilyReady"))
			{
				link.l1 = "I arrived on the instructions of Governor-General Phillip de Poincy to participate in a joint expedition to Curacao against the Dutch.";
                link.l1.go = "patria_Sl_4";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_wait" && GetCompanionQuantity(pchar) < 3)
			{
				link.l1 = "My squardon was diminished, we can set off now.";
                link.l1.go = "patria_Sl_6";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "Interesting. I am all ears.";
			link.l1 = "I have it on good authority that a Dutch brigantine the 'Utrecht' under English colors has been unloading high quantities of silk sailcloth in Portland Bay for a long time. They've been operating for over a year, during night time, between 10th and 15th of each month.";
			link.l1.go = "Mtraxx_1";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Are you sure your source can be trusted?";
			link.l1 = "At times I don't trust even myself, however, a man who disclosed this information is reliable. Besides, he had no reason to lie.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
			string sTemp = "this";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
            dialog.text = "Very well, captain. This is a serious matter and I must act on the presented information, even if your informer lied or was simply wrong. I will send a coast patrol at the specified time, and if your information is confirmed, you will be generously rewarded, such illegal activities should be sternly suppressed.";
			link.l1 = "I will see you "+sTemp+" month on the 16th. The situation will surely resolve itself by that time.";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_11";
			int month = sti(pchar.questTemp.Mtraxx.month);
			pchar.quest.mtr_silk_smuggler.over = "yes";
			pchar.quest.mtr_silk_smuggler_over.over = "yes";
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1 = "Timer";
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.hour  = 6;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.day   = 16;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.function = "Mtraxx_SilkSmugglerPatrol";
			sTemp = "this";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
			AddQuestRecord("Roger_2", "19");
			AddQuestUserData("Roger_2", "sDate", sTemp);
		break;
		
		case "Mtraxx_4":
            dialog.text = "Your information turned out to be correct, captain. We ambushed the criminals during the transaction. The 'Utrecht' had tried to escape with fighting, but was sunk by our patrol corvette. Four buyers were resisting arrest. One was killed with a shot, and the other three fled to the jungle. The full load of 80 rolls of silk has been transferred to Port Royal's treasury. Though we failed to determine the head of this network, the dead man is unidentified, and the others have fled, I declare this operation a complete success. I doubt these scoundrels will dare to ever return here\nYou have done us a great service, captain, by being diligent and point out the swindlers. Here are 10 000 pesos as your reward.";
			link.l1 = "Much obliged, your Excellence. I am happy to see it went according to plan and the smugglers got what they deserved. With that, I leave you, have a nice day.";
			link.l1.go = "Mtraxx_5";
		break;
		
		case "Mtraxx_5":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_13";
			AddQuestRecord("Roger_2", "20");
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		// Jason НСО
		case "patria_Sl":
			if (GetSquadronGoods(pchar, GOOD_SLAVES) < 500)
			{
				dialog.text = "That's precise. How many slaves did you bring?";
				link.l1 = "I'm still working on it. I will soon return with the results.";
				link.l1.go = "patria_Sl_wait";
				break;
			}
			dialog.text = "That's precise. How many slaves did you bring?";
			link.l1 = ""+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SLAVES))+".";
			if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000) link.l1.go = "patria_Sl_2";
			else link.l1.go = "patria_Sl_1";
		break;
		
		case "patria_Sl_wait":
			DialogExit();
			npchar.quest.slaveships.wait = "true";
		break;
		
		case "patria_Sl_1":
			dialog.text = "Hmm, Chevalier promised that there would be no less than 3000 slaves";
			link.l1 = "That's right. This is my fault: some of the slaves were killed under cannon fire of an enemy ship, some died on the road. I will correct my mistake and return to you. Everything will be done according to the contract.";
			link.l1.go = "patria_Sl_wait";
		break;
		
		case "patria_Sl_2":
			DeleteAttribute(npchar, "quest.slaveships.wait");
			dialog.text = "Excellent! With Chevalier de Poincy can really do business. Tell the governor-general that my squadron for the Curacao attack will be ready in a month. One month, but no more, I will wait for his squadron. I'm sure, he will send you for this campaign to me, so I'll see you soon, Monsieur de Maure.";
			link.l1 = "I would be glad to meet you again, Colonel. And now let me say my farewells.";
			link.l1.go = "patria_Sl_3";
		break;
		
		case "patria_Sl_3":
			DialogExit();
			npchar.quest.slaveships = "true";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, GetSquadronGoods(pchar, GOOD_SLAVES));
			AddQuestRecord("Patria", "57");
			pchar.questTemp.Patria = "epizode_10_return";
			pchar.quest.Patria_SlaveShipsJamaicaTimeOver.over = "yes"; //снять таймер на доставку рабов
			SetFunctionTimerCondition("Patria_CuracaoDoilyReady", 0, 0, 30, false); // таймер на 1 месяц на готовность эскадры Дойли
			SetFunctionTimerCondition("Patria_CuracaoTimeOver", 0, 0, 62, false); // таймер на 2 месяца на туда-обратно к Пуанси
			SaveCurrentQuestDateParam("questTemp.Patria.Curacao.Date"); // запоминаем дату
			// меняем отношение наций
			pchar.questTemp.Patria.Friend = "true";
			LaunchNationLegend();
			DeleteAttribute(pchar, "questTemp.Patria.Friend");
			DoQuestCheckDelay("sea_victory", 0.2);
		break;
		
		case "patria_Sl_4":
			dialog.text = "I didn't doubt it would be you. Even better! Our squadron is ready. Battleship of 1st rank and two ships of 4th rank. The maximum size of the entire squadron must not exceed five ships.";
			if (GetCompanionQuantity(pchar) > 2)
			{
				link.l1 = "Then I will leave the extra ships in the docks and keep only two. We'll get five ships as a result.";
				link.l1.go = "patria_Sl_5";
			}
			else
			{
				link.l1 = "Yes, exactly five, and no more. We should head off.";
				link.l1.go = "patria_Sl_6";
			}
		break;
		
		case "patria_Sl_5":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_wait";
		break;
		
		case "patria_Sl_6":
			dialog.text = "Perfect. Now I will explain to you the plan by which we will act: perhaps you will want to change something or add something, then we will discuss it.";
			link.l1 = "I'm all ears, colonel.";
			link.l1.go = "patria_Sl_7";
		break;
		
		case "patria_Sl_7":
			dialog.text = "There is no point in capturing Curacao: it is the main Dutch colony in the archipelago, and even if we capture their flag in Willemstad's fort and hoist an English or French one, it will be very difficult to hold the island. The Dutch will do everything to get it back and target it with military squadrons. In general, there is no point in capturing it since it's not mandatory. More important for us is to force Steivesant to sign the treaty on terms that are beneficial for us, and in order to do this it will be sufficient to destroy the enemy's main defenses and put the Dutch under the threat of complete destruction of Willemstad colony.";
			link.l1 = "What will the treaty be about?";
			link.l1.go = "patria_Sl_8";
		break;
		
		case "patria_Sl_8":
			dialog.text = "The treaty was composed by me and Chevalier de Poincy. It is related to various aspects of trade, the end of the 'trade war' between the Company and England, the denial of Stuyvesant's claims to the island of Sint Maarten and other political points that are of little interest to you.";
			link.l1 = "Understood.";
			link.l1.go = "patria_Sl_9";
		break;
		
		case "patria_Sl_9":
			dialog.text = "Here's the plan: first, with all the forces we'll attack the fort and destroy it. The Dutch will expect a landing of troops, but we won't do that, the biggest casualties are usually suffered while taking a bastion from the sea. Instead, we will land assault teams at two points on the island: on Cape Santa Maria and at the lagoon of Blanca, and we will move overland to the city gate of Willemstad. I ordered to take field artillery with us to the ships - there are no hard-to-reach thickets in Curacao, and we will be able to roll the cannons on wheels along the ground without any difficulty.\nWhile the Dutch will be puzzled as to what is going on, we will take the town under the sight from the jungle and block any opportunity to send reinforcements from the fort by land. After that, we will put the town under cannon fire. Surely the garrison of the fort will try to attack, but they will do nothing against field cannons and our musketeers, and if their cannons held in the fort will still be functional, they won't be able to bring them to the jungle.\nIn addition, our ships will simulate preparations for landing troops from the sea to strike fear into the enemies and lower their morale. After some time, when the Dutch are fully aware of their desperate situation, we will call the parliamentarians for negotiations. What do you think, captain?";
			link.l1 = "Brilliant plan! And the best thing about it is that we won't lose any soldiers by the fort's walls.";
			link.l1.go = "patria_Sl_10";
		break;
		
		case "patria_Sl_10":
			dialog.text = "I'm glad that you liked my ideas. Let's move then!";
			link.l1 = "Let's go!";
			link.l1.go = "patria_Sl_11";
		break;
		
		case "patria_Sl_11":
			DialogExit();
			chrDisableReloadToLocation = true;
			pchar.questTemp.Patria = "epizode_11_continue";
			AddQuestRecord("Patria", "60");
			pchar.quest.Patria_CuracaoTimeOver.over = "yes"; // снять таймер 2 месяца
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "PortRoyal_townhall", "goto", "goto4");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 7.0);
			Patria_CuracaoSail();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

