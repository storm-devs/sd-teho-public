// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//регата
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "What do you want? A-ha, you are the participant of the regatta! Am I right?";
				link.l1 = "Exactly, mister. I need to get registered here according to the rules.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "You've already tried to ask me a question " + GetAddress_Form(NPChar) + "...", "You have been talking about some question for the third time today...",
                          "Look, if you have nothing to tell me about the port's matters then don't bother me with your questions.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind.", "I've got nothing to talk about."), "Nevermind.", "Indeed, the third time already...", "Sorry, but I'm not interested in the port's matters for now.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "I am sailing to Blueweld, want to sell some paprika. Tell me, mister, do you have any passengers who are heading to Blueweld? Or to Port-Royale at least. It would be great to lift somebody, it could pay off the crew's wage. I have already reduced it to a minimum, but these lazy bastards still ask for money...";
                link.l1.go = "PortofficeDone";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados")
			{
				link.l1 = "There was a galleon named 'Admirable' freighted in Philipsburg under the command of Gaius Marchais. He had to deliver here a load of paprika. Can you help me to find this captain?";
                link.l1.go = "guardoftruth";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.garpiya"))
			{
				if (CheckAttribute(npchar, "questTemp.caleuche"))
				{
					link.l1 = "I wanted to ask about a xebec with a strange name.";
					link.l1.go = "caleuche_2";
				}
				else
				{
					link.l1 = "I heard that a xebec belonging to captain Jack… or Jackson often visits your port. Could you tell me where to look for him?";
					link.l1.go = "caleuche";
				}
			}
		break;

		//Голландский гамбит
		case "PortofficeDone":
			dialog.text = "Unfortunately, there is no passengers to Blueweld nor to Port-Royal. Come back tomorrow or the day after tomorrow.";
			link.l1 = "Too bad. Goodbye then.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-9");
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;

		//регата
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Sentjons") || GetCompanionQuantity(pchar) > 1 || sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_LUGGER || pchar.Ship.Name != "Santa Catherina")
			{
				dialog.text = "Hm... You have broken the rules of regatta and I have to disqualify you. I am sorry. You are not participating in the next voyage. I have already prepared a dispatch to Port-Royal.";
				link.l1 = "Eh... what a pity! But I can't do anything here, you were too vigilant. Farewell!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata");
			}
			else
			{
				pchar.questTemp.Regata.FourthTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1+2+3+4 переход
				dialog.text = "You might have noticed, captain, that the city is under the siege. We are expecting the Spanish to attack us and mobilizing our forces. But the regatta is going on\nLet's register: captain "+ GetFullName(pchar) +", ship is - "+pchar.Ship.Name+"... Regatta's time in hours is "+sti(pchar.questTemp.Regata.FourthTransitionTime)+". Done, your result is registered, you can continue your way.";
				link.l1 = "Tell me my rank.";
				link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "You are here but I don't see your ship. Where is it?";
			link.l1 = "I am sorry, sir. I will transfer my ship to the port immediately.";
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				if (pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FourthTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "Ah, yes... I am sorry I am too busy for that. You are the first.";
			link.l1 = "I see. Thanks for you information.";
			link.l1.go = "exit";
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Ah, yes... I am sorry I am too busy for that. You are the last.";
				link.l1 = "I see. Thanks for you information.";
				link.l1.go = "exit";
				}
				else
				{
					if (n==2)
					{
						dialog.text = "Ah, yes... I am sorry I am too busy for that. You are the second. There is only one captain outrunning you. His name is "+sName+" on the ship "+sShip+".";
						link.l1 = "I see. Thanks for you information.";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Ah, yes... I am sorry I am too busy for that. Your rank is "+n+" . Your closest opponent is "+sName+" on the ship "+sShip+".";
						link.l1 = "I see. Thanks for you information.";
						link.l1.go = "exit";
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 30);//защита
			AddCharacterExpToSkill(pchar, "Repair", 30);//починка
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 30);//скрытность
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Bridgetown = "true";//отметка Бриджтауна
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Caracas";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check3.win_condition.l1 = "location";
			pchar.quest.Regata_Check3.win_condition.l1.location = "PortoBello";
			pchar.quest.Regata_Check3.function = "RegataCheck";//проверка 3
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Jamaica";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 4
			pchar.questTemp.Regata.AttackIsland = "Curacao";
			pchar.questTemp.Regata.AttackNation = HOLLAND;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Attack.function = "RegataAttack_Brigantine";
			pchar.quest.Regata_Attack1.win_condition.l1 = "location";
			pchar.quest.Regata_Attack1.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Attack1.function = "RegataAttack_Corvette";//третья засада
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Barbados";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Барбадоса
			pchar.quest.Regata_Finish.win_condition.l1 = "location";
			pchar.quest.Regata_Finish.win_condition.l1.location = "Jamaica";
			pchar.quest.Regata_Finish.function = "RegataFinishSea";
			pchar.quest.Regata_Finish1.win_condition.l1 = "location";
			pchar.quest.Regata_Finish1.win_condition.l1.location = "Portroyal_town";
			pchar.quest.Regata_Finish1.function = "RegataFinishTown";//финиш регаты
			//ситуации
			pchar.quest.Regata_Siege.win_condition.l1 = "location";
			pchar.quest.Regata_Siege.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_Siege.function = "RegataSiegeOfficer";//на квест по вывозу жителей
		break;
		//регата
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "Yes, this galleon was here, got relieved of his goods and has left our port later. Information about its destination... hm... none, there is nothing. I am sorry but there is nothing I can do.";
			link.l1 = "I see. Too bad... I will continue looking for it.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			DialogExit();
			AddQuestRecord("Guardoftruth", "13");
			pchar.questTemp.Guardoftruth = "barbados1";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Sir, I need the exact name of the ship. We have tons of Jacks and Jacksons going through our port. So, what's the name?";
			link.l1 = "";
			Link.l1.edit = 2;
			link.l1.go = "caleuche_name";
			link.l2 = "Trouble is that I don't know the name of his old tub. It's strange, some bird woman, born...";
			link.l2.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Mister, go tell your stories and riddles at the tavern, we have a serious establishment here. Either you tell me the name of that xebec, or stop disturbing me from my work.";
			link.l1 = "Alright, I'll try to find out.";
			link.l1.go = "exit";
			npchar.questTemp.caleuche = "true";
		break;
		
		case "caleuche_2":
			dialog.text = "So? Do you have the name of the ship? I am listening.";
			link.l1 = "";
			Link.l1.edit = 2;
			link.l1.go = "caleuche_name";
		break;
		
		case "caleuche_name":
			if (GetStrSmallRegister(dialogEditStrings[2]) == "harpy")
			{
				dialog.text = "'Harpy'? Of course, I know that xebec. Its captain is Reginald Jackson. But he hadn't been to Bridgetown for long. I heard that he now works for the Dutch West India Company. So you should look for him in Willemstad.";
				link.l1 = "Thank you very much! You've helped me out a lot.";
				link.l1.go = "caleuche_3";
			}
			else
			{
				dialog.text = "I am sorry, but that doesn't ring a bell. Are you sure that your captain has ever been here, in Bridgetown?";
				link.l1 = "I am sure. Alright, perhaps I'll come up with something ...";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "18");
			pchar.questTemp.Caleuche.Garpiya = "gwik"; 
			npchar.quest.garpiya = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


