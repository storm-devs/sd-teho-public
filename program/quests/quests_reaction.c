
void QuestComplete(string sQuestName, string qname)
{
	// boal -->
	ref sld, chr, npchar;
	aref arOldMapPos, arAll, arPass;
	int     iTemp, i, n, ShipType, Rank; // нужно для вычислений любых целых (нации)
    float locx, locy, locz, fTemp;
	string  attrName, Model, Blade, Gun, sTemp, sQuestTown, sQuestTitle; // любые строки для вычислений
	bool   bOk;
	int iChurchGenBanditsCount;
	if (bQuestLogShow)
    {
	    Log_Info("Quest completed : " + sQuestName + "  param = " + qname);
		trace("Quest completed : " + sQuestName + "  param = " + qname + " " + GetQuestBookDataDigit());
	}
	// boal <--
	if (CheckAttribute(pchar, "quest." + qname + ".function"))
	{
		string sFunction = pchar.quest.(qname).function;
		call sFunction(qname);
		return;
	}

	switch(sQuestName)
	{	
		// boal -->
		// смена отношений от времени
        // boal все теперь проверяется 15-25 день при расчете состояния мира = изменение в 5% - ранд(100) > 95
        case "Nation_Legend":
            SetTimerCondition("Nation_Legend", 0, 0, 15+rand(10), true);
			// тут чиним стророжевики -->
			if (!bSeaActive && !bAbordageStarted)
            {
              //  RepairAllDefenderFortShips();
            }
            // тут чиним стророжевики <--
            if (rand(100) > 93 && !bWorldAlivePause)
            {
                if(IsEntity(&worldMap))
                {
                    LaunchNationLegend();
                }else{
                    if (!bQuestCheckProcessFreeze) // можно показать
					{
					    DoQuestCheckDelay("Nation_Legend_Map", 1.5);
					}
					else
					{
	      				Pchar.quest.Nation_Legend_Map.win_condition.l1 = "MapEnter";
	                    Pchar.quest.Nation_Legend_Map.win_condition = "Nation_Legend_Map";
			        }
                }
        	}
        break;

        case "Nation_Legend_Map":
            if (!bQuestCheckProcessFreeze) // можно показать
			{
                LaunchNationLegend();
            }else{
                Pchar.quest.Nation_Legend_Map_TEST.win_condition.l1 = "MapEnter";
                Pchar.quest.Nation_Legend_Map_TEST.win_condition = "Nation_Legend_Map";
            }
        break;
		
		case "LocTeleport":
			TeleportCharacterToPos(pchar, stf(pchar.locx), stf(pchar.locy), stf(pchar.locz)); 
		break;
		
		// начало игры, туториал
		case "Tut_StartGame_CheckMinHP_1":
			if (!CheckAttribute(pchar, "HeroParam.Teach_beat"))
			{
				pchar.HeroParam.Teach_beat	= 0;
			}
			pchar.HeroParam.Teach_beat = sti(pchar.HeroParam.Teach_beat) + 1;
			sld = characterFromID("Sailor_1");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, pchar, true);
			bOk = false;
			if (sti(pchar.HeroParam.Teach_beat) == 1 && sti(pchar.HeroParam.Teach_battle) == 1)
			{
				bOk = true;
			}
			else
			{
				if (sti(pchar.HeroParam.Teach_beat) == 2 && sti(pchar.HeroParam.Teach_battle) == 2)
				{
					bOk = true;
					pchar.HeroParam.Teach_beat = 3; // признак, что выиграл
				}
			}
			if (bOk)
			{
				DoQuestCheckDelay("Tut_StartGame_CheckMinHP_Hero", 0.3);
			}
        break;
        
        case "Tut_StartGame_CheckMinHP_2":
        	if (!CheckAttribute(pchar, "HeroParam.Teach_beat"))
			{
				pchar.HeroParam.Teach_beat	= 0;
			}
			pchar.HeroParam.Teach_beat = sti(pchar.HeroParam.Teach_beat) + 1;
			sld = characterFromID("Sailor_2");
   			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, pchar, true);
			if (sti(pchar.HeroParam.Teach_beat) == 2 && sti(pchar.HeroParam.Teach_battle) == 2)
			{
				sld = characterFromID("Sailor_1");
				LAi_SetActorTypeNoGroup(sld);
				pchar.HeroParam.Teach_beat = 3; // признак, что выиграл
				DoQuestCheckDelay("Tut_StartGame_CheckMinHP_Hero", 0.3);
			}
        break;
        
        case "Tut_StartGame_CheckMinHP_Hero":
        	// запуск диалога
        	LAi_SetActorTypeNoGroup(pchar);
        	sld = characterFromID("Sailor_2");
			LAi_SetActorTypeNoGroup(sld);
			sld = characterFromID("Sailor_1");
			LAi_SetActorTypeNoGroup(sld);
            PChar.GenQuest.CallFunctionParam = "Tut_StartDialog";
			DoQuestCheckDelay("CallFunctionParam", 2.0);
        break;
		//  Карты сокровищ  ГЕНЕРАТОР -->
        case "SetTreasureFromMap":
            SetTreasureBoxFromMap();
        break;
        //  Карты сокровищ  ГЕНЕРАТОР <--
        
		case "ArestInResidenceEnd":
		    LAi_LockFightMode(Pchar, false); // ножками убежал
        break;
        // ОЗГи
        case "Battle_Hunters_Land":
            Lai_SetPlayerType(pchar);
            LAi_SetFightMode(Pchar, true);
			for (i=1; i<= sti(PChar.HunterCost.Qty); i++)
			{
	            sld = characterFromID(PChar.HunterCost.TempHunterType + "LandHunter0" + i);
				LAi_RemoveCheckMinHP(sld);
	            LAi_SetWarriorType(sld);
	            //LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	            LAi_group_MoveCharacter(sld, "LAND_HUNTER");
			}
            LAi_group_SetRelation("LAND_HUNTER", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("LAND_HUNTER", LAI_GROUP_PLAYER, true);
        break;
        
        case "GoAway_Hunters_Land":
            DoQuestCheckDelay("OpenTheDoors", 4.0);
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
            for (i=1; i<= sti(PChar.HunterCost.Qty); i++)
			{
	            sld = characterFromID(PChar.HunterCost.TempHunterType + "LandHunter0" + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "", 4.0);
			}
        break;
        
		// офицеры выживают!
        case "Survive_In_SeaOfficer":
			sld = GetCharacter(sti(Pchar.GenQuest.Survive_In_SeaOfficerIdx));
            iTemp = NPC_GeneratePhantomCharacter("citizen", sti(sld.Nation), MAN, -1);  // создать клон
			if (iTemp != -1)
			{
                npchar = &Characters[iTemp];
                if (CheckAttribute(sld, "PGGAi"))
	            {
	            	sTemp = npchar.id; // новый рандомный ИД
					DeleteAttribute(npchar, "");// все трем, а там и перки!
					CopyAttributes(npchar, sld);
	
					npchar.index = iTemp;
					// меняемся ИД, старый новому, новый трупу
					sld.id = sTemp; //navy (ПГГ fix) 26.12.06
					// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
					DeleteAttribute(npchar, "Ship");
					npchar.ship.type = SHIP_NOTUSED;
                    npchar.location = "none";
                    npchar.location.from_sea = "";
					
					DeleteAttribute(npchar, "Fellows"); // его офицеры
					// пгг в рядового НПС
					sld.LifeDay = 0;
                    DeleteAttribute(sld, "PGGAi");
	            }
	            else
	            {
	                ChangeAttributesFromCharacter(npchar, sld, true);
	                
	    			sld.location = "none";
	    			sld.location.from_sea = "";
    			}
    			PlaySound("interface\_EvShip1.wav");
    			LAi_SetCurHPMax(npchar);
    			AddPassenger(Pchar, npchar, false);
    			Log_Info("Офицер " + GetFullName(npchar) + " поднялся на борт.");
            }
        break;
		
		case "Get_TreasureBarrel":
			Set_TreasureBarrel();
		break;
		
        // враги спасшиеся на шлюпках homo
        case "Survive_In_SeaPrisoner":  //homo 22/06/07
            sld = GetCharacter(sti(Pchar.GenQuest.Survive_In_SeaPrisonerIdx));
            iTemp = SetCharToPrisoner(sld);
			if (iTemp != -1)
			{
                npchar = &Characters[iTemp];
                PlaySound("interface\_EvShip1.wav");
                // лишнее, помер ПГГ и все тут if (findsubstr(sld.id, "PsHero_" , 0) != -1) npchar = sld.id; //homo for navy (ПГГ fix)
                LAi_SetCurHPMax(npchar);
    			sld.location = "none";
    			sld.location.from_sea = "";
                Log_Info(GetFullName(npchar) + " сдался в плен.");
            }
        break;
        
		/////////////////////////Квест награда за голову//////////////////////////////////////
        case "SeaHunterCheck":
            SeaHunterCheck();
        break;

		case "CheckMaxHealthQuest":
            SetTimerCondition("CheckMaxHealthQuest", 0, 0, 5, true);
            SetNewDayHealthMax();
        break;
        
		case "My_Deck_Battle_End":  // запрет битв в трюме -после казни пленных
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], true);
            LAi_SetFightMode(Pchar, false);
        break;
		//  boal 290804 наказание битьем морды -->
        case "PunishmentAction":
            LAi_SetActorTypeNoGroup(PChar);
            sld = &Characters[makeint(Pchar.GenQuest.FreeRandomOfficerIdx)];
			LAi_SetActorTypeNoGroup(sld);
            LAi_ActorTurnToCharacter(pchar, sld);
            LAi_ActorAnimation(pchar, "attack_force_3", "", 0.9);
            DoQuestCheckDelay("PunishmentAction_1", 0.5);
         break;

         case "PunishmentAction_1":
            sld = &Characters[makeint(Pchar.GenQuest.FreeRandomOfficerIdx)];
            LAi_ActorAnimation(sld, "hit_attack_2", "PunishmentAction_2", 0.6);
         break;

         case "PunishmentAction_2":
            Lai_SetPlayerType(pchar);
            sld = &Characters[makeint(Pchar.GenQuest.FreeRandomOfficerIdx)];
            switch (pchar.GenQuest.PunishmentActionManType)
            {
                case "LAi_SetHuberStayType":
                    LAi_SetHuberStayTypeNoGroup(sld);
                    break;

                case "LAi_SetStayType":
                    LAi_SetCitizenTypeNoGroup(sld);
                    break;
            }
		break;
		//  boal 290804 наказание битьем морды <--
		// индульгенция -->
		case "donation":
			int iDonation = makeint(pchar.questTemp.donate);
			int iRep      = makeint(pchar.reputation.nobility);
			int iRepIncr;
			if (iRep <10)
			{
				if (iDonation >= 1000)
				{
					iRepIncr = iDonation / 1000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
			}
			if (iRep < 20 && iRep >= 10)
			{
				if (iDonation >= 2000)
				{
					iRepIncr = iDonation/2000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
			}
			if (iRep <30 && iRep >=20)
			{
				if (iDonation >= 3000)
				{
					iRepIncr = iDonation/3000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
			}
			if (iRep <40 && iRep >=30)
			{
				if (iDonation >= 4000)
				{
					iRepIncr = iDonation/4000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
			}
			if (iRep <50 && iRep >=40)
			{
				if (iDonation >= 5000)
				{
					iRepIncr = iDonation/5000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
			}
			if (iRep <60 && iRep >=50)
			{
				if (iDonation >= 6000)
				{
					iRepIncr = iDonation/6000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
			}
			if (iRep <70 && iRep >=60)
			{
				if (iDonation >= 7000)
				{
					iRepIncr = iDonation/7000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
			}
			if (iRep <80 && iRep >=70)
			{
				if (iDonation >= 8000)
				{
					iRepIncr = iDonation/8000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
			}
			if (iRep < REPUTATION_MAX && iRep >=80)
			{
				if (iDonation >= 10000)
				{
					iRepIncr = iDonation/10000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
				}
			pchar.questTemp.donate = 0; // mitrokosta фикс накопления пожертвований
		break;
	    // индульгенция <--
		case "SetNPCInShipDeck":  // народ внутри нашего корабля
            if (Pchar.location == Get_My_Cabin())//"My_Cabin" || Pchar.location == "My_Cabin_Small")
	        {
                SetOfficersInCabin();
            }
            else
            {
                if (Pchar.location == "My_Deck")// трюм
                {
                    SetPrisonerInHold();
                }
                else
                {
	                if (Pchar.location == "My_Campus")// кают-компания
	                {
	                    SetOfficersInCampus();
	                }
                }
            }
        break;
        
		case "SetQuestHoldBox":
			if (Pchar.location == "My_Deck")// трюм
            {
                FillQuestHoldBox(&Locations[FindLocation(Pchar.location)]);
            }
		break;
		
        case "Munity_on_Ship_Map":
            if (IsEntity(&worldMap) && GetCrewQuantity(pchar) > 0 && !IsCharacterEquippedArtefact(pchar, "totem_02"))
        	{
                MunityOnShip("ShipMunity");
            }
        break;

        case "Munity_on_Ship":
            pchar.quest.Munity = "";
            pchar.GenQuest.MunityStart = true;
            PlaySound("INTERFACE\_GTBoard2.wav");
            InterfaceStates.Buttons.Save.enable = 0;
            LAi_SetFightMode(Pchar, true);

            if (!CheckAttribute(pchar, "GenQuest.SlavesMunity"))
            {
                for (i=1; i<=9; i++)
                {
                    sld = SetFantomDefenceForts("goto", "", PIRATE, LAI_GROUP_TmpEnemy);
                    if (i >= (sti(PChar.Ship.Crew.Quantity)/((8-GetCharacterShipClass(PChar))*8))) break;
                    RemoveCharacterCrew(PChar, (8-GetCharacterShipClass(PChar))*8);
                }
                PChar.Ship.Crew.Morale = 25;
                ChangeCrewExp(PChar, "Soldiers", 2); // бонус на подавление
				// Addon-2016 Jason ФМК-Гваделупа
				if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "mutiny")
				{
					for (i=1; i<=3; i++)
					{
						sld = characterFromId("FMQG_pass_"+i);
						RemovePassenger(pchar, sld);
						GetCharacterPos(pchar, &locx, &locy, &locz);
						ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
						LAi_SetWarriorType(sld);
						LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
						sld = SetFantomDefenceForts("goto", "", PIRATE, LAI_GROUP_TmpEnemy); // добавим еще +3 тела
					}
				}
				if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "mutiny") // ФМК-Сент-Кристофер
				{
					for (i=1; i<=5; i++)
					{
						sld = characterFromId("FMQN_seafox_"+i);
						RemovePassenger(pchar, sld);
						GetCharacterPos(pchar, &locx, &locy, &locz);
						ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
						LAi_SetWarriorType(sld);
						LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
					}
				}
            }
            else
            {
                for (i=1; i<=9; i++)
                {
                    sld = SetFantomSlaves("goto", "", LAI_GROUP_TmpEnemy);
                    if (i >= (GetCargoGoods(PChar, GOOD_SLAVES)/((8-GetCharacterShipClass(PChar))*8))) break;
                    RemoveCharacterGoodsSelf(PChar, GOOD_SLAVES, (8-GetCharacterShipClass(PChar))*8);
                }
                DeleteAttribute(pchar, "GenQuest.SlavesMunity");
                ChangeCrewExp(PChar, "Soldiers", 3); // бонус на подавление
            }
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroups(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "Dead_Munity");
			DoQuestFunctionDelay("Terrapin_SetMusic", 1.5); // Addon-2016 Jason
        break;

        case "Dead_Munity":
		if (CheckAttribute(pchar, "questTemp.MutinyOfficerIDX")) // mitrokosta переписал без атрибута begin - нафиг он нужен? только глаза мозолит
		{
			Log_SetStringToLog("Бренные тела бунтовщиков отправлены в последнее морское путешествие");
			DeleteAttribute(pchar, "questTemp.MutinyOfficerIDX");
		}
		else Log_SetStringToLog("Восстание было подавлено");

            InterfaceStates.Buttons.Save.enable = 1;
            pchar.quest.Munity = "Deads";
            LAi_SetFightMode(Pchar, false);
            DeleteAttribute(pchar, "GenQuest.MunityStart");
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "mutiny")
			{
				AddQuestRecord("FMQ_Guadeloupe", "5");
				CloseQuestHeader("FMQ_Guadeloupe");
				pchar.questTemp.FMQG = "fail";
			}
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "mutiny")
			{
				AddQuestRecord("FMQ_Nevis", "2");
				CloseQuestHeader("FMQ_Nevis");
				pchar.questTemp.FMQN = "fail";
			}
        break;
        
		///  захват форта - город
        case "FreeCaptureForts": // уберем солдат, откроем входы (на всяк случай) при выходе на карту
            TWN_FreeCaptureForts();
        break;
        // захват с суши по диалогу мэра (телепорт)
        case "Town_Capture_Land":
            sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
            DeleteQuestAttribute("Union_with_Escadra");

            SetLocationCapturedState(sld.Default, true);

            DoQuestReloadToLocation(sld.Default.BoardLocation, sld.Default.BoardGroup, sld.Default.BoardLocator, "Capture_Forts");
        break;
        
        case "Capture_Town_Siege":
            PrepareTownBattle(); // тут только джунгли для этого случая

			if (!CheckAttribute(Pchar, "GenQuestFort.SoundOff"))
			{
            	PlaySound("INTERFACE\_GTTown2.wav");
            	AddCharacterExpToSkill(Pchar, "Leadership", 100);
			    AddCharacterExpToSkill(Pchar, "Sneak", 100);
            }
            else
            {
                DeleteAttribute(Pchar, "GenQuestFort.SoundOff");
            }
        break;
        // Возвращение губернаторам родные диалоги // boal переделал 251204
        case "Return_Gover_Dialog":
            Characters[sti(PChar.GenQuest.GoverIdx)].dialog.CurrentNode = "First time";
        break;

        case "Return_Gover_Dialog_Exit":
            DoQuestCheckDelay("Return_Gover_Dialog", 0.5);
        break;
        // после битвы в форте сюда
        case "Capture_Forts":
            TWN_Capture_Forts();
        break;

        case "FightInTown":
            TWN_FightInTown();
        break;

        case "FightInTown_OpenNext":
            TWN_FightInTown_OpenNext();
        break;

        case "FightInTown_Finish":
            LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
            LAi_SetFightMode(Pchar, false);
        break;

        //Два пути захвата форта
        // 1 уходим с добычей - в диалоге мэра

        // 2 Если оставляем форт себе
        case "Residence_Captured_Any":
            TWN_Residence_Captured_Any();
        break;

        case "Residence_Captured_Any_02":
   			TWN_Residence_Captured_Any_02();
        break;

        case "Back_Mayor_Type":
            TWN_Back_Mayor_Type();
        break;

        case "CapturedToOurCity":
			PlayStereoOGG("music_ship_victory");
			sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
            Log_Info("Город " + GetCityName(sld.City) + " теперь наш!");
			// убрать контрабандиста
			sTemp = sld.City + "_Smuggler";
			if (GetCharacterIndex(sTemp) >= 0) // не везде есть
			{
				ChangeCharacterAddress(characterFromID(sTemp), "None", ""); // вся логика теперь в рассидки таверны
			}
            SetCaptureTownByHero(sld.City);
            LaunchColonyInfoScreen(); // табличка   to_do дает вылет :(
			// отсчет для отбития
			sTemp = "Attack_Fort_" + sld.City;
            SetTimerCondition(sTemp, 0, 0, 25 + rand(70), false);
            PChar.Quest.(sTemp).CityId   = sld.City;
			PChar.Quest.(sTemp).function = "TWN_Siege_Any";
        break;
		///////////////////////////////// захват города <--
		//  системные фичи
		case "PostVideo_Start":
            bMainMenuLaunchAfterVideo = true;
			PostVideoAndQuest(PChar.GenQuest.VideoAVI, 100, "PostVideo_After");
        break;

        case "PostVideo_After":
            PostEvent("DoInfoShower",100,"s","");
			DoQuestCheckDelay(PChar.GenQuest.VideoAfterQuest, 0.1);
        break;
        
        case "SetTimerEvent":
        	attrName = PChar.Quest.(qname).Event;
        	sTemp = PChar.Quest.(qname).Event.Type;
        	Model = PChar.Quest.(qname).Event.Param;
        	SetEventHandler(attrName, attrName, 0);
        	Event(attrName, sTemp, Model);
        	break;

        case "CallFunctionParam":
            attrName = PChar.GenQuest.CallFunctionParam;
            call attrName();
        break;
        
		// Warship. CallFunctionParam не хочет работать с диалогами, поэтому испльзовать можно эту...
		case "NextFunction":
			DoQuestFunctionDelay(PChar.QuestTemp.NextFunction, 0.1);
		break;
        
        // вызов табличкм А в это время..
        case "LaunchFrameForm":
            PChar.GenQuest.CallFunctionParam = "LaunchFrameForm";
			DoQuestCheckDelay("CallFunctionParam", stf(pchar.AutoQuest.FrameDelay));
        break;
        
        case "Move_Govenour":  // переместим губернатора в другой город
            SetTimerCondition("Move_Govenour", 0, 0, 25+rand(10), true);
            Move_Govenour();
        break;
        
		// музыка виктори
		case "sea_victory":
			SetMusicOnce("music_ship_victory");
		break;
		
		// вижу парус
		case "see_sails":
			PlaySound("interface\_EvEnemy1.wav");
			PlaySound("interface\notebook.wav");
		break;
        
		case "pchar_back_to_player":
			Lai_SetPlayerType(pchar);
		break;

		case "WalkByFoot":
			bDisableFastReload = true;
		break;

        case "God_hit_us": // это такой прикол - задействовать в ловушки для сундуков(boal)
			iTemp = 10+rand(15);
			if ((MakeInt(pchar.chr_ai.hp)-iTemp) > 0)
            {
    			LAi_SetActorType(PChar);
                LAi_ActorAnimation(PChar, "hit_attack_2", "pchar_back_to_player", 1.0);
            }
			LAi_ApplyCharacterDamage(pchar, iTemp, "other");
			if(bDrawBars) SendMessage(pchar, "lfff", MSG_CHARACTER_VIEWDAMAGE, iTemp, MakeFloat(MakeInt(pchar.chr_ai.hp)), MakeFloat(MakeInt(pchar.chr_ai.hp_max)));
			LAi_CheckKillCharacter(pchar);
		break;
		// диалог с ГГ генератор
        case "TalkSelf_Start":
            StartActorSelfDialog("TalkSelf_Main");
        break;
        // диалог с ГГ квестовые реплики
        case "TalkSelf_Quest":
            StartActorSelfDialog("First time");
        break;
        /////  сидим за столом в таверне ->
        case "alc":
			LAi_Fade("alc_2_prepare", "alc2");
			if(CheckAttribute(pchar, "IsMushketer"))
			{
				SetMainCharacterToMushketer("", false);
			}
		break;

		case "alc_2_prepare":
			LAi_SetSitType(pchar);
			LAi_SetActorType(characterFromID(pchar.questTemp.friend_in_tavern));
			LAi_ActorSetSitMode(characterFromID(pchar.questTemp.friend_in_tavern));

            sld = characterFromID(pchar.questTemp.friend_in_tavern);
            FreeSitLocator(sld.Default, sld.Default.ToLocator);  // очистим стул
			ChangeCharacterAddressGroup(pchar, sld.Default, sld.Default.group, sld.Default.ToLocator);
		break;

		case "alc2":
			LAi_ActorDialogNow(characterFromID(pchar.questTemp.friend_in_tavern), pchar, "", -1);
		break;

		case "exit_sit":
			if (CheckQuestAttribute("fight_in_tavern", "fight"))
			{
				pchar.quest.fight_in_tavern = "0";
				LAi_SetSitType(characterFromID(pchar.questTemp.friend_in_tavern));
			}
			else
			{
				if (pchar.location.group == "sit")
				{
					LAi_Fade("exit_sit_2", "");
				}
			}
		break;

		case "exit_sit_2":
   			sld = characterFromID(pchar.questTemp.friend_in_tavern);
			LAi_SetSitType(sld);
			LAi_SetPlayerType(pchar);
			//ChangeCharacterAddress(pchar, sld.Default, sld.Default.ToGo);
			PlaceCharacter(pchar, "tables", pchar.location); // ближний к столу
		break;
		// реплика таверншика о запрете драк -->
		case "tavern_keeper":
			attrName = GetCharIDByParam("TavernMan", "location", pchar.location);
            sld = characterFromID(attrName);
			sld.dialog.currentnode = "tavern_keeper";
			LAi_ActorWaitDialog(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "tavern_keeper_2", -1);
		break;

		case "tavern_keeper_2":
            attrName = GetCharIDByParam("TavernMan", "location", pchar.location);
            sld = characterFromID(attrName);
			sld.dialog.currentnode = "First time";
			LAi_SetBarmanType(sld);
		break;
		// реплика таверншика о запрете драк <--
 		case "without_memory":
			LAi_Fade("exit_sit_2", "saved_by_off");
			bQuestCheckProcessFreeze = true;
			WaitDate("",0,0,0, 5, 30);
			bQuestCheckProcessFreeze = false;
			RefreshLandTime();
		break;

		case "saved_by_off":
			LAi_SetStayType(pchar);
			Log_Info("Кто-то порылся в карманах.");

			int oSum = 500 + rand(4500);
			if (makeint(Pchar.money) < oSum) oSum = makeint(Pchar.money);
			AddMoneyToCharacter(pchar, -oSum);
			if (sti(pchar.questTemp.stels.tavern) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, makeint(50+oSum/100));
				pchar.questTemp.stels.tavern = GetDataDay();
			}

   			sld = characterFromID(loadedLocation.fastreload + "_waitress");
   			pchar.questTemp.officiantLocator = sld.location.locator;
   			pchar.questTemp.officiantGroup   = sld.location.group;   // запомнить, где была
			PlaceCharacter(sld, "goto", pchar.location);
			if (CheckAttribute(pchar, "questTemp.Consumption") && pchar.location == "PortSpein_tavern") sld.dialog.currentnode = "without_moneysss";
			else sld.dialog.currentnode = "without_money"; // лесник ,выбор диалога если нажралдся в "цене чухотки"																																		 
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "officiant_back_to_citizen", 5.0, 1.0);
			DoQuestCheckDelay("pchar_back_to_player", 6.0);
		break;

		case "officiant_back_to_citizen":
			LAi_SetPlayerType(pchar);
            sld = characterFromID(loadedLocation.fastreload + "_waitress");
			LAi_SetWaitressType(sld);
			sld.location.locator = pchar.questTemp.officiantLocator;
			sld.location.group   = pchar.questTemp.officiantGroup;
		break;
		
		//  агенты стран в таверне -->
        case "NationUpdate":
            UpdateRelations();
            if(bSeaActive)
            {
                RefreshBattleInterface();
            }
		break;

        case "pir_flag_rise":
			Flag_PIRATE();
		break;
		// агенты в тавернах -->
        case "any_patent_take":
            AddMoneyToCharacter(pchar, -sti(pchar.PatentPrice));

            RemovePatent();

			GiveItem2Character(pchar, "patent_" + pchar.PatentNation);
            EquipCharacterbyItem(pchar, "patent_" + pchar.PatentNation);

            Items[sti(pchar.EquipedPatentId)].TitulCur = 1; // текущ звание сбросим
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0; // счетчик звание сбросим
		break;

        case "fra_flag_rise":
            Flag_FRANCE();
        break;

        case "eng_flag_rise":
            Flag_ENGLAND();
        break;

        case "spa_flag_rise":
            Flag_SPAIN();
        break;

        case "hol_flag_rise": 
            Flag_HOLLAND();
        break;

        case "QuestAboardCabinDialog":  // диалог в абордаже, в каюте при достижении минНР
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]; // фантом, тень отца капитана
			LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.5);
		break;
		
		case "LAi_ReloadBoarding": // задержка нужна
			LAi_EnableReload();
		    DelEventHandler("Control Activation", "LAi_ActivateReload");
			Log_SetActiveAction("Nothing");
			LAi_ReloadBoarding();
		break;
		// boal <---
		
		case "Map_SetNationHanters": // запустить перехватчиков на карте
			EnemyNationHunterOnMap(false);
        break;
		
		case "Map_SetNationCoolHanters": // запустить скоростных перехватчиков
			EnemyNationHunterOnMap(true);
        break;
		
        ////////////////////////////////////////////////////////////////////////
		//  Служебный квест контрабандистов - ограничение по времени
		////////////////////////////////////////////////////////////////////////
		case "Rand_Smuggling":
			//слишком падает ChangeContrabandRelation(pchar, -10); // boal
			pchar.quest.KillSmugglers_after.over = "yes";  
			RemoveSmugglersFromShore();
		break;

		//Постановка стражников в локацию передачи контрабандистов
		case "Rand_ContrabandInterruption":
			chrDisableReloadToLocation = true;
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться 130313
			// солдаты в начале
			iTemp = GetCityNation(GetCityNameByIsland(GiveArealByLocation(loadedLocation)));
			if(iTemp == -1) 
			{
				iTemp = sti(pchar.GenQuest.Contraband.GuardNation);// Нация патруля
			}	
			Pchar.quest.contraband.SoldierQty = makeint(2*GetOfficersQuantity(Pchar) + 3);
			for (i = 2; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
    			sld = SetFantomDefenceForts("", "", iTemp, "CoastalGuards");
    			attrName = "SoldierIDX"+i;
    			Pchar.quest.contraband.(attrName) = sld.index;
    			LAi_SetActorType(sld);
    			LAi_ActorFollow(sld, Pchar, "", 38);
    			sld.Dialog.Filename = "Smuggler_Guards_dialog.c";
				sld.Dialog.CurrentNode = "First time";
				sld.greeting = "patrol";
            }
			// вызовем независимо!!!! не тут :) SetCoastalGuardPursuit();

			// офицер в конце
            sld = SetFantomOfficer("", "", iTemp, "CoastalGuards");
			Pchar.quest.contraband.SoldierIDX1 = sld.index;
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Smuggler_Guards_dialog.c";
			sld.Dialog.CurrentNode = "First time";
			sld.greeting = "patrol";

			LAi_ActorDialog(&Characters[makeint(Pchar.quest.contraband.SoldierIDX1)], Pchar, "", 35, 1); // boal 120c - озвереть ждать!!!
			LAi_group_SetCheck("CoastalGuards", "CoastalGuardsAllDead");
		break;

		case "Rand_ContrabandInterruptionAtSeaEnded":
			StopCoastalGuardPursuit();
			
			AddSimpleRumourCity("А вот давеча баталия у маяка была. Какой-то капитан пытался продать крупную партию контрабанды, так его патрульная эскадра за энтим делом накрыла. С поличным, значит. "+ 
				"Грохоту было - весь город переполошился, а в местной лавке крышу ядром проломило! Да только без толку все. Местные-то - скупщики значит, в джунглях спрятались, а капитан морем ушел. Как есть, с носом нашу эскадру оставил! Так из бухты вырулил - любой лоцман позавидует!", Pchar.quest.contraband.City, 3, 5, "");	
		break;

		case "Rand_ContrabandAtSeaEnded":
			StopCoastalGuardPursuit();
			
			AddSimpleRumourCity("А вот давеча баталия у маяка была. Какой-то капитан пытался продать крупную партию контрабанды, так его патрульная эскадра за энтим делом накрыла. С поличным, значит. "+ 
				"Грохоту было - весь город переполошился, а в местной лавке крышу ядром проломило! Да только без толку все. Местные-то - скупщики значит, в джунглях спрятались, а капитан морем ушел. Как есть, с носом нашу эскадру оставил! Так из бухты вырулил - любой лоцман позавидует!", Pchar.quest.contraband.City, 3, 5, "");				
		break;

		case "CoastalGuardsAllDead":
			for (i=1; i<4; i++)
			{
				sTemp = "Rand_Smug0" + i;
				LAi_SetGuardianTypeNoGroup(CharacterFromID(sTemp));
			}
			LAi_grp_alarmactive = false; // конец тревоги
		break;
		//  контрабанды <--
		
		/////////////////////////////////////////////////////////////////////////////////
		// НАЧАЛО КВЕСТА - УДАЛЕНИЕ ТЕКУЩЕГО НАПРАВЛЕНИЯ И СИЛЫ ВЕТРА
		/////////////////////////////////////////////////////////////////////////////////
		case "EraseWind":
			DeleteAttribute(pchar, "wind");
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// КОНЕЦ КВЕСТА - УДАЛЕНИЕ ТЕКУЩЕГО НАПРАВЛЕНИЯ И СИЛЫ ВЕТРА
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		// СБРОС СЧЕТЧИКА ДУЭЛЕЙ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////		
		case "HabitueSpeakDisable_End":
			DeleteAttribute(pchar,"questTemp.HabitueSpeakDisable");
			DeleteAttribute(pchar,"questTemp.duelQty");
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// СБРОС СЧЕТЧИКА ДУЭЛЕЙ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////				
		
		/////////////////////////////////////////////////////////////////////////////////
		//	СЛУЖЕБНЫЕ ФИЧИ
		/////////////////////////////////////////////////////////////////////////////////
		case "hide_weapon":
			LAi_SetFightMode(pchar, false);
			break;

		case "AnyReloadToLocation":
			int iMonth, iDay, iHour, iMin;

			iMonth	= sti(PChar.AutoQuest.delayMonth);
			iDay	= sti(PChar.AutoQuest.delayDay);
			iHour	= sti(PChar.AutoQuest.delayHour);
			iMin	= sti(PChar.AutoQuest.delayMin);

			if(iMonth > 0 || iDay > 0 || iHour > 0 || iMin > 0)
			{
                bQuestCheckProcessFreeze = true;
				WaitDate("", 0, iMonth, iDay, iHour, iMin);
				bQuestCheckProcessFreeze = false;
			}
			DoQuestReloadToLocation(PChar.AutoQuest.idLocation, PChar.AutoQuest.idGroup, PChar.AutoQuest.idLocator, PChar.AutoQuest.questName);
			break;
		/////////////////////////////////////////////////////////////////////////////////
		//	СЛУЖЕБНЫЕ ФИЧИ
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		//	START OF ПГГ
		/////////////////////////////////////////////////////////////////////////////////
		case "PGG_Companion_Leave":
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.questTemp.PGG_Companion_Leave.index)];
			PlaceCharacter(sld, "goto", "random_must_be_near");

			sld.Dialog.CurrentNode = "companion_leave";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			break;

		case "RemoveCharacterFromLocation":
			sld = CharacterFromID(PChar.questTemp.Chr2Remove);
			ChangeCharacterAddressGroup(sld, "None", "", "");
			LAi_SetImmortal(sld, false);
			break;

		case "PGG_Q1AfterShoreFight":
			PGG_Q1AfterShoreFight();
			break;

		case "PGG_Q1AfterDeckFight":
			PGG_Q1AfterDeckFight();
			break;
		/////////////////////////////////////////////////////////////////////////////////
		//	END OF ПГГ
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		//	Корсарское метро
		/////////////////////////////////////////////////////////////////////////////////
		case "RemoveTravelSmugglers":
			if (!CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight")) ChangeContrabandRelation(PChar, -10);
			RemoveSmugglersFromShore();

			if (!CheckAttribute(PChar, "GenQuest.contraTravel.ship")) 
			{
				AddQuestRecord("Gen_ContrabandTravel", "3");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("","а"));
				DeleteAttribute(PChar, "GenQuest.contraTravel");
				CloseQuestHeader("Gen_ContrabandTravel");
			}

			sld = CharacterFromID("Abracham_Gray");
			sld.location.from_sea = "";
			break;

		case "Travel_talkOnDeck":
			//убираем контрабандистов
			RemoveSmugglersFromShore();
			//кинозвезда Абрахам Грей :)
			sld = CharacterFromID("Abracham_Gray");
			//параметры..
			sld.nation = PIRATE;
			Ship_FlagRefresh(PChar); //флаг на лету
			sld.location.from_sea = "";

			LAi_group_MoveCharacter(sld, "TmpEnemy");
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);

			SetActorDialogAny2Pchar("Abracham_Gray", "", 2.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(pchar, sld, "", 1.0);
			//компания....
			iTemp = 3 + rand(3);
			for(i = 0; i < iTemp; i++)
			{
				sTemp = "pirat" + (2 + rand(5));
				attrName = "goto" + (3 + i);
				sld = SetFantomDefenceForts("goto", attrName, PIRATE, "TmpEnemy");
			}
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_ClearAllTargets();
			LAi_SetFightModeForOfficers(false);
			break;

		case "Travel_AfterDeckFight":
			AddQuestRecord("Gen_ContrabandTravel", "5");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("","а"));
			StartActorSelfDialog("GenTravel_Main");
			break;
		/////////////////////////////////////////////////////////////////////////////////
		//	END OF Корсарское метро
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		// НАЧАЛО КВЕСТА - ДОСТАВКА ГРУЗА
		/////////////////////////////////////////////////////////////////////////////////
		case "trade_quest_open":
			int iTradeGoods    = sti(pchar.CargoQuest.iTradeGoods);
			int iQuantityGoods = sti(pchar.CargoQuest.iQuantityGoods);
			int iTradeNation   = sti(pchar.CargoQuest.iTradeNation);
			int iMoney         = sti(pchar.CargoQuest.iMoney);
            AddCharacterGoods(pchar, iTradeGoods, iQuantityGoods);
			//задаем квест
			SetTimerCondition("generate_trade_quest", 0, 0, sti(pchar.CargoQuest.iDaysExpired), false);

			pchar.quest.generate_trade_quest_progress = "begin";
			ReOpenQuestHeader("DELIVERY_TRADE_QUEST");
			AddQuestRecord("DELIVERY_TRADE_QUEST", "1");

			AddQuestUserDataForTitle("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			AddQuestUserDataForTitle("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));

			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sBaseColony", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.CargoQuest.GiveTraderID)].city+"Gen"));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            attrName = "";
            if (pchar.CargoQuest.iTradeIsland != pchar.CargoQuest.iTradeColony)
            {
                attrName = ", что находится на " + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Dat");
            }
            AddQuestUserData("DELIVERY_TRADE_QUEST", "island", attrName);
    		AddQuestUserData("DELIVERY_TRADE_QUEST", "sTermsDelivery", FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired)));
    		AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            // немного веселой жизни
            TraderHunterOnMap();
		break;
		
		case "generate_trade_quest":
			if (pchar.quest.generate_trade_quest_progress == "begin")
			{
				pchar.quest.generate_trade_quest_progress = "failed";
				Log_SetStringToLog("Время для поставки груза истекло.");
				ChangeCharacterComplexReputation(pchar,"nobility", -10);
				OfficersReaction("bad");
				ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) + "hunter", 15);
                AddQuestRecord("DELIVERY_TRADE_QUEST", "3");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(sti(pchar.CargoQuest.iTradeGoods)));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// КОНЕЦ КВЕСТА - ДОСТАВКА ГРУЗА
		/////////////////////////////////////////////////////////////////////////////////
		
		/////////////////////////////////////////////////////////////////////////////////
		// НАЧАЛО КВЕСТА - СПИМ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////
		case "sleep_in_tavern":
			Statistic_AddValue(pchar, "TavernSleep", 1);
			Achievment_SetStat(pchar, 24, 1);
			// Jason: сниманием штормление от пьянки
			if (CheckAttribute(pchar, "GenQuest.CamShuttle")) DeleteAttribute(pchar, "GenQuest.CamShuttle");
			// Jason: если Мэри или Элен в подругах и абордажниках - ночуем вместе
			if (GetCharacterIndex("Helena") != -1 && IsOfficer(characterFromId("Helena")) && CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = characterFromId("Helena");
				ChangeCharacterAddressGroup(sld, pchar.location + "_upstairs", "goto", "goto3");
			}
			if (GetCharacterIndex("Mary") != -1 && IsOfficer(characterFromId("Mary")))
			{
				sld = characterFromId("Mary");
				ChangeCharacterAddressGroup(sld, pchar.location + "_upstairs", "goto", "goto3");
			}
			if (CheckAttribute(pchar, "GenQuest.LigaAttack.Go")) DoQuestReloadToLocation(pchar.location + "_upstairs", "goto", "goto1", "LigaAttack_LoginKillers"); //лига ночных убийц атакует
			else DoQuestReloadToLocation(pchar.location + "_upstairs", "goto", "goto1", "restore_hp");
		break;
		
		case "restore_hp":
			int iOfficer;
			LAi_SetCurHPMax(pchar);
			for (i=1; i<4; i++)
			{
				if (GetOfficersIndex(Pchar, i) != -1)
				{
					iOfficer = GetOfficersIndex(Pchar, i);
					LAi_SetCurHPMax(&characters[iOfficer]);
				}
			}			
		break;
		
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//											Киллеры Лиги в таверне
//////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LigaAttack_LoginKillers":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
			if (iRank > 50) iRank = 50;
			int iScl = 30 + 3*sti(pchar.rank);
			if (iScl > 110) iScl = 110;
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("LigaHunter_"+i, "killer_"+(rand(4)+1), "man", "man", iRank, PIRATE, 0, true, "hunter")); // may-16
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_13", "pistol6", "bullet", iScl+50);
				LAi_SetActorType(sld);
				if (i == 1)
				{
					LAi_CharacterDisableDialog(sld);
					ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto2");
				}
				else
				{
					sld.dialog.Filename = "Quest\Other_quests_NPC.c";
					sld.dialog.currentnode = "LigaHunters";	
					sld.greeting = "hunter"; 
					ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto3");
					LAi_ActorDialog(sld, pchar, "", 2.0, 0); 
				}
				LAi_group_MoveCharacter(sld, "EnemyFight");
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
			}
		break;
		
		case "LigaHunters_Dead":
			chrDisableReloadToLocation = false;
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "GenQuest.LigaAttack.Go");
		break;		
		
 		////////////////////////////////////////////////////////////////////////
		//  Начало    LOAN - ОГРАНИЧЕНИЕ ПО ВРЕМЕНИ
		////////////////////////////////////////////////////////////////////////
		case "LoansForAll":			// Addon 2016-1 Jason Пиратская линейка
			sTemp = pchar.quest.(qname).CityId;
			LoansMoneyAvenger(&Characters[GetCharacterIndex(sTemp + "_usurer")]);
			Characters[GetCharacterIndex(sTemp + "_usurer")].Dialog.CurrentNode = "DeadMotherfucker";
		break;
 		////////////////////////////////////////////////////////////////////////
		//  Конец    LOAN - ОГРАНИЧЕНИЕ ПО ВРЕМЕНИ
		////////////////////////////////////////////////////////////////////////	
		
 		////////////////////////////////////////////////////////////////////////
		//  НАЧАЛО	ЦЕРКОВНЫЕ КВЕСТЫ
		////////////////////////////////////////////////////////////////////////
		
		// Остальное на функциях
		case "Church_GenQuest2_AskedBand":
			sQuestTown = PChar.GenQuest.ChurchQuest_2.QuestTown;
			PChar.GenQuest.ChurchQuest_2.AskContra_1 = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ёл","ла"));
			Log_TestInfo("ГГ думает, что на этом острове нужной банды нету.");
			break;
			
		case "Church_GenQuest2_BanditsIsEnemies":
			sQuestTown = PChar.GenQuest.ChurchQuest_2.QuestTown;
			iChurchGenBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iChurchGenBanditsCount; i++)
			{
				sld = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_Group_MoveCharacter(sld, "Church_GenQuest2_Bandits_Group");
			}
			LAi_SetFightMode(PChar, true);
			LAi_Group_SetRelation("Church_GenQuest2_Bandits_Group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("Church_GenQuest2_Bandits_Group", LAI_GROUP_PLAYER, true);
			SetFunctionExitFromLocationCondition("Church_GenQuest2_BanditsIsEnemies_2_Clear", PChar.location, false);
			LAi_Group_SetCheckFunction("Church_GenQuest2_Bandits_Group", "Church_GenQuest2_DeadBandits");
			break;
        
		////////////////////////////////////////////////////////////////////////
		//  КОНЕЦ	ЦЕРКОВНЫЕ КВЕСТЫ
		////////////////////////////////////////////////////////////////////////	
		
 		////////////////////////////////////////////////////////////////////////
		//  Начало    Сопровождение торговца
		////////////////////////////////////////////////////////////////////////
		case "prepare_for_convoy_quest":
			iTemp = sti(colonies[FindColony(pchar.quest.destination)].nation);
            sld = GetCharacter(NPC_GenerateCharacter("QuestTrader", "", "man", "man", makeint((sti(pchar.rank)+60)/4), iTemp, -1, true, "citizen"));
			SetCaptanModelByEncType(sld, "trade");
			sld.reputation.nobility = (1 + rand(44) + rand(44));
			sld.Dialog.Filename = "convoy_traider.c";
			sld.dialog.currentnode = "prepare_convoy_quest";
			sld.greeting = "Gr_ConvoyTrader";
			sld.BakNation = sld.nation;		
		    sld.Abordage.Enable = true;
			sld.CompanionEnemyEnable = true;
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");			
			pchar.quest.generate_convoy_quest_progress = "begin";
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
			chrDisableReloadToLocation = true;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "convoy_refused":
			pchar.quest.generate_convoy_quest_failed.over = "yes";
			pchar.quest.generate_convoy_quest_completed.over = "yes";
			pchar.quest.generate_convoy_quest_timer.over = "yes";
			if (checkquestattribute("generate_convoy_quest_progress", "completed"))
			{
				OfficersReaction("good");
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 5);
				AddQuestRecord("convoy_quest", "4");
				CloseQuestHeader("convoy_quest");
				AddMoneyToCharacter(pchar, sti(pchar.ConvoyQuest.convoymoney));
				ChangeCharacterComplexReputation(pchar,"nobility", 1);
				RemoveCharacterCompanion(Pchar, characterFromID("QuestTrader"));
				CloseQuestHeader("convoy_quest");
			}
			pchar.quest.generate_convoy_quest_progress = "";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(characterFromID("QuestTrader"));
			LAi_ActorGoToLocation(characterFromID("QuestTrader"), "reload", LAi_FindFarLocator("reload", locx, locy, locz), "none", "", "", "", 20.0);
		break;
		
		case "generate_convoy_quest_timer":
            AddQuestRecord("convoy_quest", "2");
			CloseQuestHeader("convoy_quest");            
            sld = characterFromID("QuestTrader");
            ChangeCharacterHunterScore(pchar, NationShortName(sti(sld.BakNation)) + "hunter", 5+rand(10));// награда
			RemoveCharacterCompanion(Pchar, sld);
			OfficersReaction("bad");
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			pchar.quest.generate_convoy_quest_progress = "";
			pchar.quest.generate_convoy_quest_failed.over = "yes";
			pchar.quest.generate_convoy_quest_completed.over = "yes";
		break;
		
		case "generate_convoy_quest_failed": // торговец умер
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			OfficersReaction("bad");
            RemoveCharacterCompanion(Pchar, characterFromID("QuestTrader"));
			pchar.quest.generate_convoy_quest_progress = "";
			pchar.quest.generate_convoy_quest_failed.over = "yes";
			pchar.quest.generate_convoy_quest_completed.over = "yes";
            pchar.quest.generate_convoy_quest_timer.over  = "yes";            
            AddQuestRecord("convoy_quest", "3");
			CloseQuestHeader("convoy_quest");
		break;
		
		case "generate_convoy_quest_completed":
			sld = characterFromID("QuestTrader");
			if (IsCompanion(sld))
			{
				sld.dialog.currentnode = "complete_convoy_quest";
				PlaceCharacter(sld, "goto", pchar.location);			
				Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.			
				chrDisableReloadToLocation = true;
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				ChangeCharacterComplexReputation(pchar,"nobility", -5);
				ChangeCharacterHunterScore(pchar, NationShortName(sti(sld.BakNation)) + "hunter", 10+rand(10));// награда
				OfficersReaction("bad");
				pchar.quest.generate_convoy_quest_progress = "";				
				pchar.quest.generate_convoy_quest_failed.over = "yes";
				pchar.quest.generate_convoy_quest_completed.over = "yes";
				pchar.quest.generate_convoy_quest_timer.over  = "yes";  
				AddQuestRecord("convoy_quest", "5");
				CloseQuestHeader("convoy_quest");
			}
		break;		

		case "convoy_agreeded":
			sld = characterFromID("QuestTrader");
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", "reload1_back", 3.0, false);
            ReOpenQuestHeader("convoy_quest");
			AddQuestRecord("convoy_quest", "1");
			AddQuestUserData("convoy_quest", "sSex", GetSexPhrase("ся","ась"));
			sTemp = XI_ConvertString("Colony" + pchar.quest.destination + "Gen") + ", что на " + XI_ConvertString(GetIslandByCityName(pchar.quest.destination) + "Dat") + ",";
			AddQuestUserData("convoy_quest", "sCity", sTemp);
			AddQuestUserData("convoy_quest", "sDay", FindRussianDaysString(sti(pchar.ConvoyQuest.iDay)));
            AddQuestUserData("convoy_quest", "sMoney", FindRussianMoneyString(sti(pchar.ConvoyQuest.convoymoney)));
			// по городу вернем его порт
            attrName = GetPortByCityName(pchar.quest.destination);            
			pchar.quest.generate_convoy_quest_completed.win_condition.l1 = "Location";
			pchar.quest.generate_convoy_quest_completed.win_condition.l1.location = attrName;
			pchar.quest.generate_convoy_quest_completed.win_condition = "generate_convoy_quest_completed";			
			if (rand(2) == 1) TraderHunterOnMap();
		break;
 		////////////////////////////////////////////////////////////////////////
		//  Конец    Сопровождение торговца
		////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  Начало    Доставка пассажира
		////////////////////////////////////////////////////////////////////////
		case "prepare_for_passenger_quest":
			iTemp = sti(colonies[FindColony(sGlobalTemp)].nation);
            Rank = NPC_GenerateCharacter("QuestPassanger", "", "man", "man", makeint((sti(pchar.rank)+60)/4), iTemp, -1, true, "citizen");
			sld = &characters[Rank];
			sld.id = sld.id + "_" + sld.index; //меняем ID на оригинальный
			sld.reputation = (1 + rand(44) + rand(44));
			SetCaptanModelByEncType(sld, "trade");
			SetRandomNameToCharacter(sld);
			sld.Dialog.Filename = "convoy_passenger.c";
			sld.dialog.currentnode = "prepare_convoy_quest";
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");			
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
			chrDisableReloadToLocation = true;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);            
		break;

		case "AllPassangersDead": // торговец умер
			sld = &characters[sti(pchar.quest.(qname).Idx)];
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
            RemovePassenger(PChar, sld);
			sTemp = sld.id + "_complited";
            pchar.quest.(sTemp).over = "yes";
			sTemp = sld.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + sld.id); //извлекаем из структуры недовольных
			//--> смотрим Deck
    		makearef(arAll, pchar.GenQuest.ConvoyPassenger);
			if (GetAttributesNum(arAll) == 0) pchar.quest.ConvoyMapPassenger.over = "yes";
			//<-- смотрим Deck
			attrName = sld.index + "convoy_passenger";
			AddQuestRecordEx(attrName, "Gen_convoy_passenger", "3");
            CloseQuestHeader(attrName);
		break;
		
		case "AllPassangersTimeOver":
			sld = &characters[sti(pchar.quest.(qname).Idx)];
			sTemp = sld.id;
			Pchar.GenQuest.ConvoyPassenger.(sTemp) = sld.index; //в структуру недовольных
			if (!CheckAttribute(Pchar, "quest.ConvoyMapPassenger"))
			{
				Pchar.quest.ConvoyMapPassenger.win_condition.l1 = "MapEnter";
        		Pchar.quest.ConvoyMapPassenger.win_condition = "AllPassengerDeck";
			}
		break;
		
		case "AllPassengerDeck": // разговор на палубе			
            MakeCloneShipDeck(pchar, true); // подмена палубы
			makearef(arAll, pchar.GenQuest.ConvoyPassenger);
    		iTemp = GetAttributesNum(arAll);
    		for (i=0; i<iTemp; i++)
    		{
    			arPass = GetAttributeN(arAll, i);
				sld = &characters[sti(arPass)];				
				ChangeCharacterAddress(sld, "Ship_deck", "goto4");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0); 
    		}
			makearef(arOldMapPos, worldMap.old);
			WdmPrepareMapForAbordage(arOldMapPos);
			DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto5");
			ReloadFromWMtoL_complete();
            pchar.quest.Munity = "";  // признак выхода с палубы
            LAi_LockFightMode(Pchar, true);
        break;
        
		case "AllPassangersComplited":
			sld = &characters[sti(pchar.quest.(qname).Idx)];
			sTemp = sld.id + "_TimeOver";
            pchar.quest.(sTemp).over = "yes";
			sTemp = sld.id + "_dead";
			pchar.quest.(sTemp).over = "yes";
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
			chrDisableReloadToLocation = true;
			sld.dialog.currentnode = "complete_convoy_quest";
			PlaceCharacter(sld, "goto", "random_must_be");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);     
		break;
 		////////////////////////////////////////////////////////////////////////
		//  Конец    Доставка пассажира
		////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  Начало   Ланд энкаунтеры
		//////////////////////////////////////////////////////////////////////// 
		//------------------- банда грабителей -------------------------
		case "LandEnc_RaidersBegin":
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
			iTemp = sti(pchar.quest.(qname).EncQty);
			sTemp = "Gang"+ pchar.quest.(qname).LocIdx + "_";
			sld = characterFromId(sTemp + "0");
			fTemp = (stf(locations[reload_location_index].locators_radius.encdetector)-3)/5;
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", fTemp, 0); 
			for(i = 1; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);				
				if (sld.id != "none")
				{
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorFollow(sld, pchar, "", -1);
				}
			}
		break;

		case "LandEnc_RaidersBeforeDialog": //если выстрел до диалога
			attrName = locations[reload_location_index].index;
			sTemp = "EncRaiders_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			Model = "RaidersGroup_" + attrName; //имя группы
			sTemp = "Gang"+ attrName + "_";
			for(i = 0; i < 4; i++)
			{				
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				sld = CharacterFromID(sTemp + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorTypeNoGroup(sld);
				//LAi_group_MoveCharacter(sld, Model);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(Model, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(Model, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(Model, "LandEnc_RaidersAfrer");
		break;

		case "LandEnc_RaidersAfrer": //чистим за собой		
			attrName = locations[reload_location_index].index;
			sTemp = "TimeRaiders_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			sTemp = "RaidersGroup_" + attrName;			
			Delay_DeleteGroup(sTemp);
			Gun = "Raiders_" + attrName; 			
			AddSimpleRumour(LinkRandPhrase("Вы слышали, капитан " + GetFullName(pchar) + " схватил"+ GetSexPhrase("ся","ась") +" с бандитом по имени " + pchar.GenQuest.(Gun).name + ". Е"+ GetSexPhrase("го","е") +" хотели ограбить, а он"+ GetSexPhrase("","а") +" не захотел"+ GetSexPhrase("","а") +" платить. Смел"+ GetSexPhrase("ый кэп","ая девушка") +" - он"+ GetSexPhrase("","а") +" просто его убил"+ GetSexPhrase("","а") +".", 
				"Вы знаете, недавно за городом была схватка - на капитана по имени " + GetFullName(pchar) + " напали бандиты, ограбить хотели... А-а, так вы же и есть "+ GetSexPhrase("тот капитан","та девушка") +", кто отправил"+ GetSexPhrase("","а") +" к праотцам этого мародера по имени " + pchar.GenQuest.(Gun).name + "! Прекрасная работа, скажу я вам...", 
				"Вы не слышали о том, что местная шайка бандитов под предводительством негодяя " + pchar.GenQuest.(Gun).name + " напала на капитана по имени " + GetFullName(pchar) + "? Т"+ GetSexPhrase("от","а") +" отказал"+ GetSexPhrase("ся","ась") +" платить и перебил"+ GetSexPhrase("","а") +" бандитов."), sti(pchar.GenQuest.(Gun).nation), 5, 1);				
			DeleteAttribute(pchar, "GenQuest." + Gun); //трем нацию и имя			
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.LandEnc.LocId)], "fire");
		break;

		case "LandEnc_RaidersOver": //чистим за собой
			sTemp = "EncRaiders_" + pchar.quest.(qname).LocIdx;
			iTemp = sti(pchar.quest.(sTemp).EncQty);
			sTemp = "Gang" + pchar.quest.(qname).LocIdx + "_";
			for(i = 0; i < iTemp; i++)
			{
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				LAi_RemoveCheckMinHP(CharacterFromID(sTemp + i));
			}
			sTemp = "RaidersGroup_" + pchar.quest.(qname).LocIdx;
			LAi_group_RemoveCheck(sTemp);
			LAi_group_Delete(sTemp);
			pchar.quest.(qname).over = "yes";
			sTemp = "EncRaiders_" + pchar.quest.(qname).LocIdx;
			pchar.quest.(sTemp).over = "yes";
			sTemp = pchar.quest.(qname).LocIdx;
			DeleteAttribute(pchar, "GenQuest." + sTemp); //трем нацию и имя
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.LandEnc.LocId)], "fire");
		break;
		
		//------------------- злые карибы -------------------------
		case "LandEnc_CaribBegin":
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
			iTemp = sti(pchar.quest.(qname).EncQty);
			sTemp = "Carib"+ pchar.quest.(qname).LocIdx + "_";
			sld = characterFromId(sTemp + "0");
			fTemp = (stf(locations[reload_location_index].locators_radius.encdetector)-3)/5;
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", fTemp, 0); 
			for(i = 1; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);				
				if (sld.id != "none")
				{
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorFollow(sld, pchar, "", -1);
				}
			}
		break;

		case "LandEnc_CaribBeforeDialog": //если выстрел до диалога - нападение
			attrName = locations[reload_location_index].index;
			sTemp = "EncCarib_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			Model = "CaribGroup_" + attrName; //имя группы
			sTemp = "Carib"+ attrName + "_";
			for(i = 0; i < 4; i++)
			{				
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				sld = CharacterFromID(sTemp + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorTypeNoGroup(sld);
				//LAi_group_MoveCharacter(sld, Model);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(Model, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(Model, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(Model, "LandEnc_CaribAfrer");
		break;
		
		case "LandEnc_MiskitoBeforeDialog": //если выстрел до диалога - бегство
			attrName = locations[reload_location_index].index;
			sTemp = "EncCarib_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			Model = "CaribGroup_" + attrName; //имя группы
			sTemp = "Carib"+ attrName + "_";
			for(i = 0; i < 4; i++)
			{				
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				sld = CharacterFromID(sTemp + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, false);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			}
			DoQuestCheckDelay("LandEnc_CaribAfrer", 10.0);
		break;

		case "LandEnc_CaribAfrer": //чистим за собой		
			attrName = locations[reload_location_index].index;
			sTemp = "TimeCarib_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			sTemp = "CaribGroup_" + attrName;			
			Delay_DeleteGroup(sTemp);
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.LandEnc.LocId)], "fire");
			ref rItm = ItemsFromID("fire");
			rItm.shown = false;
		break;

		case "LandEnc_CaribOver": //чистим за собой
			sTemp = "EncCarib_" + pchar.quest.(qname).LocIdx;
			iTemp = sti(pchar.quest.(sTemp).EncQty);
			sTemp = "Carib" + pchar.quest.(qname).LocIdx + "_";
			for(i = 0; i < iTemp; i++)
			{
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				LAi_RemoveCheckMinHP(CharacterFromID(sTemp + i));
			}
			sTemp = "CaribGroup_" + pchar.quest.(qname).LocIdx;
			LAi_group_RemoveCheck(sTemp);
			LAi_group_Delete(sTemp);
			pchar.quest.(qname).over = "yes";
			sTemp = "EncCarib_" + pchar.quest.(qname).LocIdx;
			pchar.quest.(sTemp).over = "yes";
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.LandEnc.LocId)], "fire");
			rItm = ItemsFromID("fire");
			rItm.shown = false;
		break;
		
		// пещерные энкаунтеры
		case "CaveEnc_RaidersBeforeDialog": //если выстрел до диалога
			attrName = locations[reload_location_index].index;
			sTemp = "TimeCaveRaiders_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			Model = "CaveGroup_" + attrName; //имя группы
			sTemp = "CaveBandos"+ attrName + "_";
			for(i=0; i<4; i++)
			{				
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				sld = CharacterFromID(sTemp + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, Model);
			}
			LAi_group_SetRelation(Model, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(Model, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(Model, "CaveEnc_RaidersAfrer");
		break;
		
		case "CaveEnc_RaidersAfrer": //чистим за собой	
			chrDisableReloadToLocation = false;
			attrName = locations[reload_location_index].index;
			sTemp = "CaveGroup_" + attrName;			
			Delay_DeleteGroup(sTemp);			
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.LandEnc.LocId)], "fire");
		break;
		
		case "CaveEnc_RaidersOver": //чистим за собой
			sTemp = "CaveBandos" + pchar.quest.(qname).LocIdx + "_";
			for(i=0; i<4; i++)
			{
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				LAi_RemoveCheckMinHP(CharacterFromID(sTemp + i));
			}
			sTemp = "CaveGroup_" + pchar.quest.(qname).LocIdx;
			LAi_group_RemoveCheck(sTemp);
			LAi_group_Delete(sTemp);
			pchar.quest.(qname).over = "yes";
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.LandEnc.LocId)], "fire");
		break;
		
		case "CaveEnc_SkeletDie":
			for(i=0; i<4; i++)
			{
				sld = characterFromId(sTotalTemp+i);
				LAi_KillCharacter(sld);
			}
		break;
		
		//------------------- девка в джунлях -------------------------
		case "LandEnc_RapersTalk":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0); 
			}
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
		break;

		case "LandEnc_RapersBeforeDialog": //если выстрел до диалога
			if (GetCharacterIndex("CangGirl") != -1) LAi_RemoveCheckMinHP(CharacterFromID("CangGirl"));			
			for(i = 1; i <= 3; i++)
			{				
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
//			LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");
			sld = CharacterFromID("CangGirl");			 
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, pchar, true);
		break;

		case "LandEnc_RapersAfrer": // грохнули бандюков
			sGlobalTemp = "Saved_CangGirl";
			sld = CharacterFromID("CangGirl");
			sld.greeting = "rapers_girl_2";
			sld.dialog.currentnode = "ThanksForHelp";
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "LandEnc_RapersBadExit":
			if (GetCharacterIndex("CangGirl") == -1) // если ГГ собственноручно прибил тетку
			{
				ChangeCharacterComplexReputation(pchar,"nobility", -3);
				AddSimpleRumour(LinkRandPhrase("Вы слышали, кто-то убил в джунглях несчастную девушку по имени " + pchar.GenQuest.EncGirl.name + ". Отловить бы мерзавца и вздернуть!", 
					"Вы знаете, капитан " + GetFullName(pchar) + ", кто-то убил несчастную девушку по имени " + pchar.GenQuest.EncGirl.name  + ", когда та по делам отправилась за город. Как жаль, она была такой хорошей...", 
					"Ее звали " + pchar.GenQuest.EncGirl.name  + ", и она погибла в джунглях. И ничего удивительного, скажу я вам, за городом так неспокойно..."), sti(pchar.GenQuest.EncGirl.nation), 5, 1);			
				for(i = 1; i <= 3; i++)
				{
					if (GetCharacterIndex("GangMan_" + i) == -1) continue;
					sld = CharacterFromID("GangMan_" + i);
					LAi_RemoveCheckMinHP(sld);
					sld.lifeDay = 0;
				}
             SetFunctionTimerCondition("EncGerl_deleteisjangly", 0, 0, 30, false);	// лесник 30 дней не давать квест.					
			}
			else
			{
				if (sGlobalTemp == "Saved_CangGirl") // спасли тетку
				{
					if(pchar.GenQuest.EncGirl == "close") // .. и послали ее куда подальше
					{
						characters[GetCharacterIndex("CangGirl")].lifeDay = 0;
						DeleteAttribute(pchar, "GenQuest.EncGirl");
					}
					else
					{		
						if(!CheckAttribute(pchar, "GenQuest.EncGirl.Ransom")) 
						{
							ChangeCharacterComplexReputation(pchar,"nobility", 5);
							AddSimpleRumour(LinkRandPhrase("Вы слышали, "+ GetSexPhrase("какой-то капитан","какая-то морячка") +" спас"+ GetSexPhrase("","ла") +" девушку по имени " + pchar.GenQuest.EncGirl.name + " от бандитов, буквально вытащил ее из их лап!"+ GetSexPhrase(" Какой прекрасный человек и настоящий мужчина.","") +"", 
								"Вы знаете, капитан " + GetFullName(pchar) + " спас"+ GetSexPhrase("","ла") +" девушку по имени " + pchar.GenQuest.EncGirl.name + " от насильников в джунглях... А-а, так это же вы!! Я вами восхищаюсь...", 
								"Девушке по имени " + pchar.GenQuest.EncGirl.name + " здорово повезло - недавно на нее напали бандиты в джунглях, хотели изнасиловать, видать. Но ничего у них не вышло, хе-хе, и благодарить она должна капитана " + GetMainCharacterNameGen() + "!"), sti(pchar.GenQuest.EncGirl.nation), 3, 1);	
						}		
					}	
				}
				else // оставил на растерзание бандитам
				{	
					for(i = 1; i <= 3; i++)
					{
						if (GetCharacterIndex("GangMan_" + i) == -1) continue;
						sld = CharacterFromID("GangMan_" + i);
						LAi_RemoveCheckMinHP(sld);
						sld.lifeDay = 0;
					}		
					characters[GetCharacterIndex("CangGirl")].lifeDay = 0;
					if(pchar.GenQuest.EncGirl == "Begin_11")
					{
						ChangeCharacterComplexReputation(pchar,"nobility", -8);
					}
					if(pchar.GenQuest.EncGirl == "Begin_22")
					{
						ChangeCharacterComplexReputation(pchar,"nobility", -8);
					}
					if(pchar.GenQuest.EncGirl == "Begin_33")
					{
						ChangeCharacterComplexReputation(pchar,"nobility", -5);
					}
					AddSimpleRumour(RandPhraseSimple("Да уж, капитан " + GetFullName(pchar) + ", никто не думал, что вы способны оставить беззащитную женщину на поругание бандитам. Бедная " + pchar.GenQuest.EncGirl.name + ", у меня нет слов...", 
						"Знаете, капитан, "+ GetSexPhrase("вы форменный мерзавец","не ожидал от вас такого") +". Как вы могли бросить беззащитную девушку в джунглях? Вы хоть представляете себе, что они с ней сделали? Бедная " + pchar.GenQuest.EncGirl.name + ", ее теперь никто не возьмет замуж..."), sti(pchar.GenQuest.EncGirl.nation), 5, 1);
					DeleteAttribute(pchar, "GenQuest.EncGirl"); //трем нацию и имя	
				}
			}			
		break;		
		//------------------- девка просит помочь подруге -------------------------
		case "Enc_FriendGirl_after": //если выстрел до диалога
			ChangeCharacterComplexReputation(pchar,"nobility", -(rand(4)+1));
			if (rand(1))
			{
				AddSimpleRumour(LinkRandPhrase("Вы слышали, какой-то капитан убил в джунглях несчастную девушку по имени " + pchar.GenQuest.EncGirlF.name + ". Отловить бы мерзавца и вздернуть!", 
					"Вы знаете, капитан " + GetFullName(pchar) + ", кто-то убил несчастную девушку по имени " + pchar.GenQuest.EncGirlF.name  + ", когда та по делам отправилась за город. Как жаль, она была такой хорошей...", 
					"Ее звали " + pchar.GenQuest.EncGirlF.name  + ", и она погибла в джунглях. И ничего удивительного, скажу я вам, за городом так неспокойно..."), sti(pchar.GenQuest.EncGirlF.nation), 5, 1);
			}
		break;
		//------------------- патруль в джунглях -------------------------
		case "LandEnc_PatrolBegin":
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
			iTemp = sti(pchar.quest.(qname).EncQty);
			sTemp = "Patrol"+ pchar.quest.(qname).LocIdx + "_";
			npchar = characterFromId(sTemp + "0");
			fTemp = (stf(locations[reload_location_index].locators_radius.encdetector)-3)/5;
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorDialog(npchar, pchar, "", fTemp, 0); 
			for(i = 1; i < iTemp; i++)
			{
				sld = characterFromId(sTemp + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1); 
			}
		break;

		case "LandEnc_PatrolBeforeDialog": //если выстрел до диалога
			attrName = locations[reload_location_index].index;
			sTemp = "EncPatrol_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			Model = "PatrolGroup_" + attrName; //имя группы
			sTemp = "Patrol"+ attrName + "_";
			for(i = 0; i < 4; i++)
			{				
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				sld = CharacterFromID(sTemp + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorTypeNoGroup(sld);
			}
			LAi_group_SetRelation(Model, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(Model, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(Model, "LandEnc_PatrolAfrer");
		break;

		case "LandEnc_PatrolAfrer": //чистим за собой
			attrName = locations[reload_location_index].index;
			sTemp = "TimePatrol_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			sTemp = "PatrolGroup_" + attrName;
			Delay_DeleteGroup(sTemp);
			//слухи
			AddSimpleRumour(LinkRandPhrase("Недавно за городом нашли мертвым нашего офицера и приданных ему солдат. Кто мог их убить? Зачем?..", 
				"Наш комендат постоянно отправляет за город патрули, но теперь даже не знаю, как будет дальше. Недавно солдат нашли метрвыми в джунглях...", 
				"Черт возьми, кто-то за городом перебил наши солдат, что патрулировали территорию..."), sti(pchar.GenQuest.(attrName).nation), 5, 1);
			AddSimpleRumour("Говорят, что капитан " + GetFullName(pchar) + " нарвался в джунглях на солдат " + NationNameGenitive(sti(pchar.GenQuest.(attrName).nation)) + " и всех их перебил. Хех, " + NationNamePeople(sti(pchar.GenQuest.(attrName).nation)) + " - никуда негодные вояки...", sti(pchar.GenQuest.(attrName).nation)+10, 5, 1);
			DeleteAttribute(pchar, "GenQuest." + attrName); //трем нацию патруля, если есть
		break;

		case "LandEnc_PatrolOver": //чистим за собой
			sTemp = pchar.quest.(qname).LocIdx;
			//слухи
			AddSimpleRumour(LinkRandPhrase("Вы слышали, капитана " + GetMainCharacterNameGen() + " проверял наш патруль за городом...", 
				"Хм, насколько я знаю, вас недавно проверил наш патруль за городом. Не знаю, насколько эта мера эффективна...", 
				"Наш комендант усилит патрулирование прилегающей к городу территории. Ну вы и сами об этом знаете, вас же недавно проверяли в джунглях..."), sti(pchar.GenQuest.(sTemp).nation), 5, 1);
			DeleteAttribute(pchar, "GenQuest." + sTemp); //трем нацию патруля, если есть
			sTemp = "PatrolGroup_" + pchar.quest.(qname).LocIdx;
			LAi_group_RemoveCheck(sTemp);
			LAi_group_Delete(sTemp);
			pchar.quest.(qname).over = "yes";
			sTemp = "EncPatrol_" + pchar.quest.(qname).LocIdx;
			pchar.quest.(sTemp).over = "yes";
		break;

		case "DeleteGroupOnExitLocation": //группу нулим
			sTemp = pchar.quest.DeleteGroupOnExitLocation.GroupName;
			LAi_group_Delete(sTemp);
		break;

 		////////////////////////////////////////////////////////////////////////
		//  Конец   Ланд энкаунтеры
		//////////////////////////////////////////////////////////////////////// 

 		////////////////////////////////////////////////////////////////////////
		//  Начало    Уничтожение банды
		////////////////////////////////////////////////////////////////////////  
		case "AllMayorsQuests_Late": //провальное прерывание на все квесты мэра
			sTemp = pchar.GenQuest.questName;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на квест
			pchar.GenQuest.(sTemp) = "Late"; //флаг опоздал
			npchar = characterFromId(pchar.GenQuest.(sTemp).MayorId);
			AddQuestRecord("MayorsQuestsList", "20");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));			
		break;

		case "DestroyGang_fight":
			if (rand(1))
			{
				chrDisableReloadToLocation = true;
				Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.			
				LAi_group_Delete("EnemyFight");
				sTemp = pchar.GenQuest.questName;
				pchar.quest.(sTemp).over = "yes"; //снимаем текущее многоразовое прерывание					
				ref location = &locations[reload_location_index];
				LAi_LocationFightDisable(location, true);      //лочим возможность начать драку до диалог, это лишнее
				string encGroup = LAi_FindRandomLocator("encdetector");
				sTemp = "locators." + encGroup;
				makearef(arAll, location.(sTemp));
				iTemp = GetAttributesNum(arAll); //кол-во человек в банде
				if (iTemp <= 0 ) iTemp = 1; //если локаторов меньше четырех
				//--> генерим ранг 
				if (sti(pchar.rank) > 6) 
				{
					if (sti(pchar.rank) > 20) Rank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*4/iTemp);
					else Rank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5/iTemp);
				}
				else  
				{	//казуалам зеленый свет на начало игры
					if (sti(pchar.rank) > 3) Rank = sti(pchar.rank);
					else 
					{
						Rank = 1;
						iTemp = 1;
					}
				}	
				//<-- генерим ранг 
				string iModel[10];
				iModel[0] = "citiz_41";
				iModel[1] = "citiz_42";
				iModel[2] = "citiz_43";
				iModel[3] = "citiz_44";
				iModel[4] = "citiz_45";
				iModel[5] = "citiz_46";
				iModel[6] = "citiz_47";
				iModel[7] = "citiz_48";
				iModel[8] = "citiz_49";
				iModel[9] = "citiz_50";
				i = 0;
				while(i < iTemp)
				{
					ShipType = rand(9);
					if (iModel[ShipType] != "")
					{
						if (i == 0) 
						{   //главарь банды
							int iMainGang = NPC_GenerateCharacter("MayorQuestGang_" + i, iModel[ShipType], "man", "man", Rank, PIRATE, 0, true, "hunter");
							sld = &characters[iMainGang];
							sld.name = pchar.GenQuest.DestroyGang.name;  //имя главаря
							sld.lastname = pchar.GenQuest.DestroyGang.lastname;
							sld.dialog.filename = "MayorQuests_dialog.c";
							sld.dialog.currentnode = "DestroyGang_begin";
							sld.greeting = "banditos"; 
							sld.SaveItemsForDead   = true; // сохранять на трупе вещи
							sld.DontClearDead = true;  // не убирать труп через 200с
						}
						else sld = GetCharacter(NPC_GenerateCharacter("MayorQuestGang_" + i, iModel[ShipType], "man", "man", Rank, PIRATE, 0, true, "marginal"));
						LAi_SetActorType(sld);
						SetFantomParamFromRank(sld, Rank, true);
						//Получим локатор для логина
						attrName = GetAttributeName(GetAttributeN(arAll, i));
						ChangeCharacterAddressGroup(sld, location.id, encGroup, attrName);					
						LAi_SetActorType(sld);
						if (i == 0) LAi_ActorDialog(sld, pchar, "", -1, 0); 
						else LAi_ActorFollow(sld, &characters[iMainGang], "", -1);
						i++;
						iModel[ShipType] = "";
					}
				} 				
			}
		break;

		case "DestroyGang_SuddenAttack":
			for(i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
		break;

		case "DestroyGang_Afrer":
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			Delay_DeleteGroup("EnemyFight");
			makearef(arAll, pchar.GenQuest.DestroyGang);
			pchar.GenQuest.DestroyGang = "Execute"; //флаг выполнил успешно
			sTemp = GetFullName(&characters[GetCharacterIndex(arAll.MayorId)]);
			// судовой журнал
			AddQuestRecord("MayorsQuestsList", "2");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", sTemp);
			AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arAll));
			// слухи
			AddSimpleRumour(LinkRandPhrase("Вы знаете, губернатор " + sTemp + " поручил неко"+ GetSexPhrase("ему капитану","й морячке") +" " + GetMainCharacterNameDat() + " уничтожить известного бандита по имени " + GetFullName(arAll) + ". И, кажется, что "+ GetSexPhrase("капитан выполнил","она выполнила") +" задание губернатора...", 
				""+ GetSexPhrase("Какой-то смелый капитан вызвался","Какая-то смелая девушка вызвалась") +" найти и уничтожить местного бандита по имени " + GetFullName(arAll) + ". И, похоже, он"+ GetSexPhrase("","а") +" сделал"+ GetSexPhrase("","а") +" это!", 
				"Ха, наконец-то наш губернатор взялся за наведение порядка в джунглях - он поручил капитану " + GetMainCharacterNameDat() + " разыскать в джунглях и убить наиболее известного бандита. И вы знате, этот бандит, " + GetFullName(arAll) + " - мертв!"), sti(characters[GetCharacterIndex(arAll.MayorId)].nation), 5, 1);
		break;
 		////////////////////////////////////////////////////////////////////////
		//  Конец    Уничтожение банды
		////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  ОЗГ - пассажир
		//////////////////////////////////////////////////////////////////////// 
		case "ContraPass_GivePrisoner":
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = GetCharacter(NPC_GenerateCharacter("ContraPassTempsailor", "citiz_36", "man", "man", 10, sti(pchar.Mation), 0, true, "quest"));
			sld.Dialog.Filename = "MayorQuests_dialog.c";
			sld.dialog.currentnode = "Tempsailor";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindNearestFreeLocator("rld", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddComplexSelfExpToScill(50, 50, 50, 50);
        break;
		
 		////////////////////////////////////////////////////////////////////////
		//  дезертир
		//////////////////////////////////////////////////////////////////////// 
		case "Fugitive_afterfight":
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.GenQuest.FindFugitive.City+"_tavern")], true);//запретить драться - для таверны, для остальных пройдет без последствий
			LAi_group_Delete("EnemyFight");
			sld = characterFromId("Fugitive");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
        break;
		
 		////////////////////////////////////////////////////////////////////////
		//  Начало    Повод для спешки
		//////////////////////////////////////////////////////////////////////// 		
		
		case "ReasonToFast_PatrolDied":
			sTemp = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_group_RemoveCheck(sTemp);
			LAi_group_Delete(sTemp);	
			if(pchar.questTemp.ReasonToFast == "PatrolAfterHunter") 
			{
				AddQuestRecord("ReasonToFast", "6");
				AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("","а"));
			}			
			if(pchar.questTemp.ReasonToFast == "PatrolAfter")
			{				
				AddQuestRecord("ReasonToFast", "8");
			}	
			if(pchar.questTemp.ReasonToFast == "PatrolAngry")
			{
				AddQuestRecord("ReasonToFast", "4");
			}
			DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther"); //можем говорить с губером	

			pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1 = "Timer";
			pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.ReasonToFast_SpeakMayor.function = "ReasonToFast_SpeakMayor";

			DeleteAttribute(Locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], "DisableEncounters");
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), sti(pchar.questTemp.ReasonToFast.relation));
			pchar.questTemp.ReasonToFast = "PatrolDied";
			pchar.questTemp.ReasonToFast.speakAfterPatrolDied = false;
			DeleteAttribute(pchar, "GenQuest.HunterScore2Pause"); //вертаем начисление нзг
			DeleteAttribute(pchar, "GenQuest.ReputationNotChange"); //вертаем смену репы 
		break;
				
		case "ReasonToFast_MeetHunter":
			ReasonToFast_GenerateHunter();
		break;
		
		case "ReasonToFast_PatrolAngry":
			sTemp = "Patrol"+ pchar.questTemp.ReasonToFast.LocIdx + "_";
			sld = CharacterFromID(sTemp + "0");
			sld.dialog.filename = "Enc_Patrol.c";				
			sld.dialog.currentnode = "Reason_To_Fast_AfterHunter3";			
			LAi_SetActorType(pchar); 
			LAi_ActorTurnToCharacter(pchar, sld);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 1.0);
			LAi_ActorFollow(sld, pchar,"ActorDialog_Any2Pchar", -1);
		break;
		
		case "ReasonToFast_HunterGoOut":
			sld = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetActorType(sld); 
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1); 
			sld.LifeDay = 0;
			pchar.questTemp.ReasonToFast = "MeetHunterSuccess";
	
			sTemp = "Patrol"+ pchar.questTemp.ReasonToFast.LocIdx + "_";
			sld = CharacterFromID(sTemp + "0");
			sld.dialog.filename = "Enc_Patrol.c";				
			sld.dialog.currentnode = "Reason_To_Fast_AfterHunter1";
			LAi_SetActorType(pchar); 
			LAi_ActorTurnToCharacter(pchar, sld);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 1.0);
			LAi_ActorFollow(sld, pchar,"ActorDialog_Any2Pchar", -1);
		break;
				
		case "ReasonToFast_MeetWithSailor":
			Sea_DeckBoatStartNow(pchar);
		break;
		
		case "ReasonToFast_ClearVictim":
			pchar.quest.ReasonToFast_SetShip_1.over = "yes";
			pchar.quest.ReasonToFast_SetShip_2.over = "yes";
			sld = characterFromId("VictimCap_1");
			sld.lifeDay = 0;
			Group_DeleteGroup("Sea_Victim_1");
			AddQuestRecord("ReasonToFast","19");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"questTemp.ReasonToFast");
		break;
		
		case "ReasonToFast_TrHuntersDied":
			LAi_group_RemoveCheck("LAND_HUNTER");
			LAi_group_Delete("LAND_HUNTER");
			bDisableLandEncounters = false;	
			if(pchar.questTemp.ReasonToFast == "GetMap")
			{
				AddQuestRecord("ReasonToFast", "21");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
				AddQuestUserData("ReasonToFast", "sText", "картой");
			}	
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				AddQuestRecord("ReasonToFast", "21");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
				AddQuestUserData("ReasonToFast", "sText", "ценностями");
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitFail")
			{
				AddQuestRecord("ReasonToFast", "21");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
				AddQuestUserData("ReasonToFast", "sText", "деньгами");
			}
			if(pchar.questTemp.ReasonToFast == "GetTreasure")
			{
				AddQuestRecord("ReasonToFast", "23");
				AddQuestUserData("ReasonToFast", "sName", GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN));
				CloseQuestHeader("ReasonToFast");
				DeleteAttribute(pchar, "questTemp.ReasonToFast");
			}
		break;
		
		case "ReasonToFast_LakeyGoOut":
			sld = CharacterFromID("ReasonToFastLakey_1");
			LAi_SetActorType(sld); 
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1); 
			sld.LifeDay = 0;		
		break;
		
		case "ReasonToFast_GoAway_Hunters_Land":
            DoQuestCheckDelay("OpenTheDoors", 4.0);
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
            for (i=1; i<= sti(pchar.HunterCost.Qty); i++)
			{
				sld = characterFromID("LandHunter0" + i);
				LAi_SetActorType(sld); 
				LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "", 4.0);
				iTemp = GetCharacterIndex("LandHunter0" + i);
				if (iTemp != -1)
				{
					characters[iTemp].lifeDay = 0;
				}
			}
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
			bDisableLandEncounters = false;	
			DeleteAttribute(pchar, "questTemp.ReasonToFast");
        break;

 		////////////////////////////////////////////////////////////////////////
		//  Конец    Повод для спешки
		//////////////////////////////////////////////////////////////////////// 		

 		////////////////////////////////////////////////////////////////////////
		//  Начало   Генератор - Поручение капитана "Операция 'Галеон'"
		//////////////////////////////////////////////////////////////////////// 

		case "CaptainComission_FightInDeck":
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			Rank = sti(pchar.rank) + 5 + rand(MOD_SKILL_ENEMY_RATE);
			LAi_group_Delete("EnemyFight");
			for (i=1; i < 5; i++) 
			{	
				sld = characterFromID("saylor_0" + i);
				sld.rank = Rank;
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "CaptainComission_TeamIsDead");
		break;
		
		case "CaptainComission_TeamIsDead":
      		pchar.quest.CaptainComission_CapIsOut.win_condition.l1 = "ExitFromSea";
			pchar.quest.CaptainComission_CapIsOut.function = "CaptainComission_CapIsOut";
			pchar.quest.CaptainComission_CapIsDead.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_CapIsDead.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapIsDead.function = "CaptainComission_CapIsDead";
			LAi_SetFightMode(pchar, false);
			LAi_LocationFightDisable(loadedLocation, true);
			//DoQuestCheckDelay("TalkSelf_Quest", 0.4); //диалог сам-на-сам лесник  лишнее
		break;

		case "CaptainComission_TalkCanoneer":
			LAi_Fade("CaptainComission_TalkCanoneer_prepare", "CaptainComission_TalkCanoneer2");
		break;
		
		case "CaptainComission_TalkCanoneer_prepare":
			LAi_SetSitType(pchar);
			sld = characterFromID("CapComission_Canoneer");
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);			
			ChangeCharacterAddressGroup(pchar, pchar.GenQuest.CaptainComission.City + "_tavern", "sit", "sit_front2");
		break;
		
		case "CaptainComission_TalkCanoneer2":
			LAi_ActorDialogNow(characterFromID("CapComission_Canoneer"), pchar, "", -1);
		break;
		
		case "CaptainComission_exit_sit":
			if (pchar.location.group == "sit")
			{
				LAi_Fade("CaptainComission_exit_sit_2", "");
			}
		break;

		case "CaptainComission_exit_sit_2":
   			sld = characterFromID("CapComission_Canoneer");
			LAi_SetSitType(sld);
			LAi_SetPlayerType(pchar);
			PlaceCharacter(pchar, "tables", pchar.location); // ближний к столу
		break;

		case "CaptainComission_GangDialog_1":
			sld = characterFromID("Gang_0");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
		break;
				
		case "CaptainComission_MapEnterAfterShoreBattle":
			for (i = 1; i <=3; i++)
			{
				iTemp = GetCharacterIndex("Pirate_Captain0" + i);
				if (iTemp != -1)
				{
					characters[iTemp].lifeDay = 0;
				}
			}
			Group_DeleteGroup("Pirate_Guards"); 
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
		break;
		
		case "CaptainComission_GenerateCapJail":
			sld = characterFromID("CapComission_1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.CaptainComission.City + "_prison", "goto", "goto9");
			LAi_group_MoveCharacter(sld, "Prisoner_Group"); 
			LAi_SetCitizenType(sld);// с этого места не было кода лесник
			LAi_SetStayType(sld);						
			sld.name = pchar.GenQuest.CaptainComission.Name;
	        sld.lastname = "";
	        sld.greeting = "Gr_prison";
	        sld.dialog.FileName = "GenQuests_Dialog.c";
	        sld.dialog.currentnode = "CaptainComission_370"; 											 
		break;
		
			
          case "CaptainComission_Capitan_Cdox":
             // добавлена проверка на смерть капитана по "поручению капитана" от руки игрока уже после тюрьмы. лесник
		    AddQuestRecord("CaptainComission2", "33");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_Capitan_Cdox.over = "yes"; // на сякий случай
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
		break;
		
		
		case "CaptainComission_PrisonFree_Death":			
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			AddQuestRecord("CaptainComission2", "55");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
		break;
		
		case "CaptainComission_DeletePrisonGroup":
			LAi_group_Delete("CapComission_Prison");
		break;

		case "CaptainComission_ExitFromPrison":
			iTemp = GetCharacterIndex("CapComission_1");
			if (iTemp != -1)
			{
				pchar.quest.CaptainComission_ExitFromTown.win_condition.l1 	= "EnterToSea";           	
				pchar.quest.CaptainComission_ExitFromTown.function    		= "CaptainComission_ExitFromTown";						
				pchar.GenQuest.CaptainComission.canSpeakCaptain = true;
				pchar.TownEscape = true;
			}
		break;
		
		case "CaptainComission_MeetWithCaptain":
			Sea_DeckBoatStartNow(pchar);
		break;

		case "CaptainComission_MapEnterCapDied":
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
		break;
		
		case "CaptainComission_ShoreGangDialog":
			SetMainCharacterIndex(1);
			pchar = GetMainCharacter();
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar)
			locCameraFollow();
			EndQuestMovie(); 	
			ChangeShowIntarface();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;			
			DoQuestFunctionDelay("CaptainComission_BattleInShore", 5.0); 
		break;
 		////////////////////////////////////////////////////////////////////////
		//  Конец   Генератор - Поручение капитана "Операция 'Галеон'"
		//////////////////////////////////////////////////////////////////////// 

		////////////////////////////////////////////////////////////////////////
		//  Начало   Генератор - "Кораблекрушенцы"
		//////////////////////////////////////////////////////////////////////// 		
		
		case "ShipWreck_RemoveSailorsFromShore":
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				iTemp = GetCharacterIndex("ShipWreck_" + i);		
				if(iTemp != -1)
				{
					Characters[iTemp].LifeDay = 0;
				}
			}	
			DeleteAttribute(pchar, "GenQuest.ShipWreck");		
		break;
		
		////////////////////////////////////////////////////////////////////////
		//  Конец   Генератор - "Кораблекрушенцы"
		//////////////////////////////////////////////////////////////////////// 				
		
   		////////////////////////////////////////////////////////////////////////
		//  Начало   Бордель
		//////////////////////////////////////////////////////////////////////// 
        case "Brothel_checkVisitTime":
			LocatorReloadEnterDisable(qname + "_Brothel", "reload2_back", true); //закрываем комнату
			sld = characterFromId(pchar.quest.(qname).HorseId);
			sld.location = qname+"_Brothel";
			sld.location.group = "goto";
			sld.location.locator = pchar.quest.(qname).locator;
			//ChangeCharacterAddressGroup(sld, qname+"_Brothel", "goto", pchar.quest.(qname).locator);
			DeleteAttribute(&characters[GetCharacterIndex(qname + "_Hostess")], "quest.selected"); //снимаем флаг у хозяйки
			//==> ноду девкам
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				makeref(sld, Characters[i]);
				if (sld.location == qname+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
				{
					sld.dialog.currentnode = "Horse_talk";
				}
			}
        break;	
		////////////////////////////////////////////////////////////////////////
		//  Конец    Бордель
		//////////////////////////////////////////////////////////////////////// 

		////////////////////////////////////////////////////////////////////////
		//  Начало Тюремные квесты
		//////////////////////////////////////////////////////////////////////// 
        case "GivePrisonFree":
			chrDisableReloadToLocation = true;
			LAi_LocationDisableMonstersGen(pchar.location, true);
			pchar.quest.GivePrisonFree_Death.over = "yes";
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			sld.dialog.currentnode = "PrisonerInPlace";
			LAi_SetActorTypeNoGroup(sld);
			GetCharacterPos(sld, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(sld, pchar.location, "monsters", LAi_FindFarLocator("monsters", locx, locy, locz));
			LAi_ActorDialog(sld, pchar, "", -1, 0);		
		break;

        case "GivePrisonFree_Death":
			AddQuestRecord("GivePrisonFree", "2");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			pchar.quest.GivePrisonFree.over = "yes";
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup"
		break;

        case "GivePrisonFree_Over":
			AddQuestRecord("GivePrisonFree", "6");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.prisonerId);
			if (iTemp > 0) 
			{
				characters[iTemp].lifeDay = 0;
				ChangeCharacterAddress(&characters[iTemp], "none", "");	
			}
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup"
		break;

        case "DeliverToBander":
			if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.City") && pchar.questTemp.jailCanMove.Deliver.City == locations[reload_location_index].fastreload)
			{
				LAi_group_Delete("EnemyFight");
				chrDisableReloadToLocation = true;
				pchar.quest.DeliverToBander.over = "yes";
				pchar.quest.DeliverToBander_over.over = "yes";
				if (sti(pchar.rank) > 6) Rank = 8+sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
				else Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
				GetCharacterPos(pchar, &locx, &locy, &locz);
				for (i=1; i<=2; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Bander_"+i, "citiz_"+(rand(9)+41), "man", "man", Rank, PIRATE, 0, true, "marginal"));
					sld.dialog.filename = "quest\Banders_dialog.c";
					sld.dialog.currentnode = "First time";
					sld.greeting = "marginal"; 
					SetFantomParamFromRank(sld, Rank, true);
					if (i == 1)
					{
						LAi_SetOwnerType(sld);
						sld.dialog.currentnode = "Second time";
         				ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindFarLocator("goto", locx, locy, locz));
					}
					else
					{
						LAi_SetActorType(sld);
						sld.dialog.currentnode = "First time";
         				ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
					}
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
				LAi_ActorDialog(sld, pchar, "", 1.0, 0); 
			}
		break;

        case "DeliverToBander_over":
			AddQuestRecord("GivePrisonFree", "9");
			CloseQuestHeader("GivePrisonFree");
			pchar.quest.DeliverToBander.over = "yes";
			iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.Deliver.Id);
			if (iTemp > 0) ChangeCharacterAddress(&characters[iTemp], "none", "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			TakeItemFromCharacter(pchar, "Malyava");
		break;

        case "DeliverToBander_Dead":
			AddQuestRecord("GivePrisonFree", "10");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			CloseQuestHeader("GivePrisonFree");
            chrDisableReloadToLocation = false;
			iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.Deliver.Id);
			if (iTemp > 0) ChangeCharacterAddress(&characters[iTemp], "none", "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			TakeItemFromCharacter(pchar, "Malyava");
		break;

        case "DeletePrisonGroup":
			LAi_group_Delete("DeliveQuest_Prison");
		break;
		////////////////////////////////////////////////////////////////////////
		//  Конец  Тюремные квесты
		//////////////////////////////////////////////////////////////////////// 

		// универсальный диалогостартер (см метод  SetActorDialogAny2Pchar)
        case "ActorDialog_Any2Pchar":
            LAi_SetActorType(PChar);
            LAi_ActorWaitDialog(Pchar, characterFromID(Pchar.AutoQuest.NPCharId));
            LAi_ActorDialog(characterFromID(Pchar.AutoQuest.NPCharId), Pchar, Pchar.AutoQuest.Quest, stf(Pchar.AutoQuest.Time1), stf(Pchar.AutoQuest.Time2));
        break;

        case "OpenTheDoors":
            chrDisableReloadToLocation = false;
			bDisableFastReload = false; 
        break;

        case "CanEnterToMap":
            bQuestDisableMapEnter = false;
        break;

		case "CanNotEnterToMap": // patch-4
            bQuestDisableMapEnter = true;
			DoQuestCheckDelay("CanEnterToMap", 80.0);
        break;

		case "DeleteEnemyFight":
            LAi_group_Delete("EnemyFight");
        break;

        case "CloseBermudesDungeonDoor":
            LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			sld = characterFromId("Pirates_shipyarder");
			DeleteAttribute(sld, "Step_Door");
        break;

        case "CanFightCurLocation":
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
        break;

        case "CannotFightCurLocation":
			LAi_LocationFightDisable(loadedLocation, true);
			chrDisableReloadToLocation = false;
        break;

        case "MainHeroFightModeOn":
			LAi_SetFightMode(pchar, true);
        break;

        case "MainHeroFightModeOff":
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
        break;

		case "ChurchNightGuard_timerInChurch_2":
			TavernWaitDate("wait_day");
		break;
		
		case "MayorSitBack": //посадить мэра обратно
			iTemp = GetCharacterIndex(Pchar.quest.MayorSitBack.mayorId)
			if (iTemp > 0)
			{
				sld = &characters[iTemp];
				sld.location = Pchar.quest.MayorSitBack.locationName;
				sld.location.group = "sit";
				sld.location.locator = Pchar.quest.MayorSitBack.locatorName;
				LAi_SetHuberTypeNoGroup(sld);
				RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
				RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			}
        break;

		case "PlaySex_1":
			ResetSound();
			iTemp = rand(13)+1;
			switch (iTemp)
			{
				case 1: fTemp = 18.2; break;
				case 2: fTemp = 5.1;  break;
				case 3: fTemp = 19.3; break;
				case 4: fTemp = 8.2;  break;
				case 5: fTemp = 11.3; break;
				case 6: fTemp = 18.2; break;
				case 7: fTemp = 18.2; break;
				case 8: fTemp = 9.3;  break;
				case 9: fTemp = 19.4; break;
				case 10:fTemp = 12.2; break;
				case 11:fTemp = 19.4; break;
				case 12:fTemp = 12.3; break;
				case 13:fTemp = 10.2; break;
				case 14:fTemp = 11.2; break;
			}
			sGlobalTemp = iTemp;
			//LAi_FadeDelay(fTemp, "loading\inside\censored1.tga");
			//StartPictureAsVideo( "loading\inside\censored1.tga", fTemp );
			SetLaunchFrameFormParam("", "", 0, fTemp);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
            LaunchFrameForm();
			DoQuestCheckDelay("PlaySex_2", 1.0);			
		break;

		case "PlaySex_2":
			PlayStereoSound("sex\sex" + sGlobalTemp + ".wav");
            AddTimeToCurrent(2, rand(30));
			if (pchar.location == "SanJuan_houseS1Bedroom")
			{
			    QuestSetCurrentNode("Isabella", "NewLife_afterSex");
			    LAi_SetStayType(CharacterFromID("Isabella"));
			}
			//квест официантки
			if (pchar.questTemp.different == "FackWaitress_facking")
			{
				sld = characterFromId("WairessQuest");
				ChangeCharacterAddress(sld, "none", "");
				AddCharacterExpToSkill(pchar, "Loyality", 20);
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	AddCharacterHealth(pchar, 6);
				else 												AddCharacterHealth(pchar, 3);
            	AddCharacterExpToSkill(pchar, "FencingS", -15);
            	AddCharacterExpToSkill(pchar, "Pistol", -15);
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
				if (sti(pchar.questTemp.different.FackWaitress.Kick) != 1) 
				{
					pchar.questTemp.different = "FackWaitress_fackNoMoney";
					AddCharacterExpToSkill(pchar, "Fortune", 100);
				}
				pchar.money = sti(pchar.money) / sti(pchar.questTemp.different.FackWaitress.Kick);
				chrDisableReloadToLocation = false;
			}
			//квест развода хозяйки борделя
			if (pchar.questTemp.different == "HostessSex" && CheckAttribute(pchar, "questTemp.different.HostessSex.city"))
			{
				sld = characterFromId(pchar.questTemp.different.HostessSex.city + "_Hostess");
				ChangeCharacterAddressGroup(sld, pchar.questTemp.different.HostessSex.city + "_SecBrRoom", "goto", "goto8");
				LAi_SetOwnerTypeNoGroup(sld);
				DeleteAttribute(pchar, "questTemp.different.HostessSex");
				pchar.questTemp.different = "free";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "EncGirl_facking")
			{
				sld = characterFromId("CangGirl");
				ChangeCharacterAddress(sld, "none", "");
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	AddCharacterHealth(pchar, 10);
				else 												AddCharacterHealth(pchar,  5);
				AddCharacterExpToSkill(pchar, "Loyality", 20);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
            	AddCharacterExpToSkill(pchar, "FencingS", -20);
            	AddCharacterExpToSkill(pchar, "Pistol", -20);
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
				pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/15);
				chrDisableReloadToLocation = false;
				SetFunctionTimerCondition("EncGirl_SpeakTavernKeeper", 0, 0, 1, false);
			}
			if (CheckAttribute(pchar, "questTemp.Consumption.Sex"))//Jason, цена чахотки
			{
				LocatorReloadEnterDisable("PortSpein_tavern", "reload1_back", false); //открыть таверну
				LocatorReloadEnterDisable("PortSpein_tavern", "reload2_back", true); //закрыть комнату
				bDisableFastReload = false;//открыть переход
				AddCharacterHealth(pchar, 7);
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				sld = characterFromId("PortSpein_waitress");
				ChangeCharacterAddressGroup(sld, "PortSpein_tavern", "goto", "goto1");
				LAi_SetWaitressType(sld);
				Consumption_Close();
			}
			if (pchar.location == "Minentown_tavern_upstairs")//Jason
			{
				LocatorReloadEnterDisable("Minentown_tavern", "reload1_back", false); //открыть таверну
				LocatorReloadEnterDisable("Minentown_tavern", "reload2_back", true); //закрыть комнату
				bDisableFastReload = false;//открыть переход
				DeleteAttribute(pchar, "GenQuest.CannotWait");
				DeleteAttribute(pchar, "GenQuest.MinentownSex");
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) AddCharacterHealth(pchar, 10);
				else AddCharacterHealth(pchar, 5);
				sld = characterFromId("MineFuckGirl");
				LAi_SetActorType(sld);
				ChangeCharacterAddress(sld, "none", "Minentown_waittime");
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 4.0);
				DoQuestCheckDelay("Minentown_waittime", 7.0);
			}
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.location == "CommonBedroom")// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
			{
				FMQT_FinalWithSex();
			}
			if (pchar.location == "SantoDomingo_Brothel_room" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_2")// Addon 2016-1 Jason пиратская линейка
			{
				AddQuestRecord("Roger_1", "3");
				pchar.questTemp.Mtraxx = "jewelry_3";
				SetFunctionTimerCondition("Mtraxx_JewelryHavanaOver", 0, 0, 7, false); // таймер
				sld = characterFromId(sTotalTemp);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				pchar.quest.mtr_jewelry_havana.win_condition.l1 = "location";
				pchar.quest.mtr_jewelry_havana.win_condition.l1.location = "Cuba2";
				pchar.quest.mtr_jewelry_havana.function = "Mtraxx_HavanaInfo";
				DeleteAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor");
			}
		break;
		
		case "Minentown_waittime":
			TavernWaitDate(sTotalTemp);
		break;

		//поисковый генератор
		case "CitizSeekCap_afterCabinFight":
			sld = GetCharacter(NPC_GenerateCharacter(pchar.GenQuest.CitizSeekCap.label + "_" + pchar.GenQuest.CitizSeekCap.WifeCity, pchar.GenQuest.CitizSeekCap.model, pchar.GenQuest.CitizSeekCap.sex, pchar.GenQuest.CitizSeekCap.ani, 5, pchar.GenQuest.CitizSeekCap.nation, -1, false, "citizen"));
			sld.name = pchar.GenQuest.CitizSeekCap.WifeName;
			sld.lastname = pchar.GenQuest.CitizSeekCap.WifeLastname;
			sld.dialog.filename   = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = pchar.GenQuest.CitizSeekCap.label + "_Board";
			sld.quest.SeekCap = pchar.GenQuest.CitizSeekCap.label;
			sld.quest.cribCity = pchar.GenQuest.CitizSeekCap.WifeCity;
			DeleteAttribute(pchar, "GenQuest.CitizSeekCap");
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		break;

		case "CitizSeekCap_GivePrisoner":
			sld = GetCharacter(NPC_GenerateCharacter(pchar.GenQuest.CitizSeekCap.label + "_" + pchar.GenQuest.CitizSeekCap.PrisonerCity, pchar.GenQuest.CitizSeekCap.model, pchar.GenQuest.CitizSeekCap.sex, pchar.GenQuest.CitizSeekCap.ani, 5, sti(pchar.GenQuest.CitizSeekCap.nation), -1, false, "citizen"));
			sld.name = pchar.GenQuest.CitizSeekCap.PrisonerName;
			sld.lastname = pchar.GenQuest.CitizSeekCap.PrisonerLastname;
			//pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
			//SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			log_info(sld.name+" помещен на ваш корабль под стражу"); // 170712
			PlaySound("interface\notebook.wav");
			DeleteAttribute(pchar, "GenQuest.CitizSeekCap");
		break;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//Jason----------------------------------------------работорговец---------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "Slavetrader_findTortugaRat"://охрана Гонтьера
            chrDisableReloadToLocation = true; // закрыть выход из локации.
			sld = GetCharacter(NPC_GenerateCharacter("Ratlover", "women_14", "woman", "towngirl", 10, FRANCE, -1, false, "citizen"));
            ChangeCharacterAddressGroup(sld, "Tortuga_HouseHut", "barmen",  "bar2");
           	sld.Dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Rat_lover"; // диалоговый узел
			sld.name 	= "Жанна";
			sld.lastname 	= "Мольери";            
			LAi_SetImmortal(sld, true);
            LAi_SetStayTypeNoGroup(sld);
			
            sld = GetCharacter(NPC_GenerateCharacter("SLBanditHead", "citiz_50", "man", "man", 25, PIRATE, 0, true, "quest"));
            FantomMakeCoolFighter(sld, 45, 100, 100, "blade_06", "pistol6", "bullet", 80);
			sld.cirassId = Items_FindItemIdx("cirass1");
        	LAi_SetStayType(sld);
        	sld.Dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Rat_bandos";
            LAi_group_MoveCharacter(sld, "EnemyFight");
           	ChangeCharacterAddressGroup(sld, "Tortuga_HouseHut", "goto",  "goto1");
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.3);
       break;

       case "Slavetrader_findTortugaRat1"://охрана Гонтьера
            for (i=3; i<=5; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("SVBandit"+i, "citiz_"+(40+i), "man", "man", 25, PIRATE, 0, true, "quest"));
                FantomMakeCoolFighter(sld, 35, 100, 100, "blade_10", "pistol6", "bullet", 80);
            	LAi_SetStayType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "Tortuga_HouseHut", "goto",  "goto"+i);
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat2");
       break;

       case "Slavetrader_findTortugaRat2":
            chrDisableReloadToLocation = false;
            LAi_SetActorType(pchar);
            sld = characterFromID("Ratlover");
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
       break;
	   
	   case "Slavetrader_EscapeSlaves_Win":
            chrDisableReloadToLocation = false;
			sld = GetCharacter(NPC_GenerateCharacter("Slavewoman", "Izaura", "woman", "towngirl", 10, PIRATE, -1, false, "citizen"));
            ChangeCharacterAddressGroup(sld, pchar.questTemp.Slavetrader.Island.Shore, "goto",  "goto31");
           	sld.Dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Slave_woman"; 
			sld.name 	= "Изаура";
			sld.lastname 	= "";            
			LAi_SetImmortal(sld, true);
            LAi_SetStayTypeNoGroup(sld);
			LAi_SetActorType(pchar);
            sld = characterFromID("Slavewoman");
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
			
        break;
//<--работорговец конец
		
//--> Jason ТТГ, почта 2 уровень, агент в таверне
		case "PostAgent_inTavern_Room":
			DoQuestReloadToLocation(pchar.questTemp.WPU.Postcureer.StartCity +"_tavern_upstairs", "goto", "goto4", "");			
			sld = characterFromID("PostAgent");        
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
        break;
		
		case "PostAgent_inTavern_Room_end":
			SetLaunchFrameFormParam("Прошел час...", "", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromID("PostAgent");        
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 4.5);
        break;
		// <-- почтовый генер 2 уровня, агент в таверне
		case "DisasterShipIndian_Win":
			chrDisableReloadToLocation = false;
			sld = characterFromId("WMCaptain");
			LAi_SetActorType(sld);
			sld.dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "DisasterCap_8";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;
//<-- ТТГ, почта 2 уровень, конец
		
//--> Jason, действия горожан по мини-квестам
		//отпускание рабов через монаха
		case "Monk_RemoveSlaves":
			RemoveCharacterGoods(pchar, GOOD_SLAVES, GetSquadronGoods(pchar, GOOD_SLAVES));
			OfficersReaction("good");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
        break;
		
		//освящение кораблей через монаха
		case "Monk_Shipshine":
			OfficersReaction("good");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			AddCrewMorale(pchar, 10);
			pchar.quest.Shipshine.win_condition.l1 = "Timer";
			pchar.quest.Shipshine.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Shipshine.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 15);
			pchar.quest.Shipshine.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 15);
			pchar.quest.Shipshine.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 15);
			pchar.quest.Shipshine.function = "Monkshipshine_Over";
        break;
		
		//установка капеллана в кают-компанию
		case "Monk_Capellan":
			chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId(pchar.questTemp.ShipCapellan.id);
			sld.dialog.currentnode = "capellan_4";
			LAi_SetStayType(sld);
        break;

		//установка дворянина с реликвией в таверну
		case "Nobleman_lombardTavern":
			chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId(pchar.GenQuest.Noblelombard.id);
			sld.dialog.currentnode = "lombard_4";
			LAi_SetSitType(sld);
        break;
		
		//установка дворянина в церковь
		case "Nobleslaves_Place":
			chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId(sGlobalTemp);
			sld.dialog.currentnode = "slaves_3";
			LAi_SetSitType(sld);
			LAi_SetLoginTime(sld, 11.0, 13.0);
        break;
		
		//выдача пассажира после абордажа
		case "Marginpassenger_GivePrisoner":
			sld = GetCharacter(NPC_GenerateCharacter("MarginPass", pchar.GenQuest.Marginpassenger.model, pchar.GenQuest.Marginpassenger.sex, pchar.GenQuest.Marginpassenger.ani, 2, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true, "quest"));
			sld.Dialog.Filename = "Quest\Marginpassenger.c";
			sld.dialog.currentnode = "MarginPass";
			sld.name = pchar.GenQuest.Marginpassenger.q1Name;
			sld.lastname = "";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.GenQuest.Marginpassenger.Boarding = "true";
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
			AddComplexSelfExpToScill(60, 60, 60, 60);
        break;
		
		//после боя в бухте
		case "Marginpassenger_Afterbattle":
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			AddCharacterGoods(pchar, sti(pchar.GenQuest.Marginpassenger.Goods), sti(pchar.GenQuest.Marginpassenger.GoodsQty));
			AddQuestRecord("Marginpassenger", "15");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddComplexSelfExpToScill(80, 80, 80, 80);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterNationReputation(pchar, SPAIN, -1);
        break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Jason----------------------------------------------Бесчестный конкурент-----------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "Shadow_inRoom":
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = characterFromID("ShadowAgent_1");   
			sld.LSC_clan = true; // 110912 fix
			LAi_SetImmortal(sld, false);
			iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5; // 240912
			sld = GetCharacter(NPC_GenerateCharacter("ShadowAgent_2", "citiz_"+(rand(9)+41), "man", "man", iRank, PIRATE, 2, true, "citizen"));
			SetFantomParamFromRank(sld, iRank, true);
			sld.LSC_clan = true; // 110912 fix
			GiveItem2Character(sld, "blade_05");
			EquipCharacterbyItem(sld, "blade_05");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "CommonFlamHouse", "goto", "goto3");
			sld = GetCharacter(NPC_GenerateCharacter("ShadowTrader", "trader_11", "man", "man", 10, PIRATE, 2, true, "quest"));
			SetFantomParamFromRank(sld, 10, true);
			RemoveAllCharacterItems(sld, true);
			GiveItem2Character(sld, "blade_03");
			EquipCharacterbyItem(sld, "blade_03"); // 240912
			sld.LSC_clan = true; // 110912 fix
			LAi_SetActorType(sld);
			sld.dialog.Filename = "Quest\LineMiniQuests\ShadowTrader.c";
			sld.dialog.currentnode = "ShadowTrader";	
			sld.greeting = "store_1";
			LAi_SetImmortal(sld, true);
			sld.SaveItemsForDead = true;
			sld.money = 20550;
			TakeNItems(sld, "jewelry1", rand(5));
			TakeNItems(sld, "jewelry2", rand(10));
			TakeNItems(sld, "jewelry5", rand(20));
			ChangeCharacterAddressGroup(sld, "CommonFlamHouse", "goto", "goto1");
			DoQuestReloadToLocation("CommonFlamHouse", "goto", "goto4", "");
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
        break;
		
		case "ShadowTrader_afterfight":
			LAi_group_Delete("EnemyFight");
			sld = characterFromID("ShadowTrader");        
			LAi_SetStayType(sld);
			DoQuestCheckDelay("hide_weapon", 1.3);
			sld = characterFromID("ShadowTrader"); 
			sld.greeting = "ransack"; // 240912
        break;
		
		case "ShadowTrader_killed_end"://убили Паскаля
		sld = characterFromID("ShadowTrader"); 
		LAi_SetActorType(sld);
		LAi_KillCharacter(sld);
		LAi_SetPlayerType(pchar);
			DoQuestFunctionDelay("ShadowTrader_final", 15.0);
		pchar.questTemp.Shadowtrader.End.Kill = "true";
		AddQuestRecord("Shadowtrader", "10");
		ChangeCharacterComplexReputation(pchar,"nobility", -3); 
		AddComplexSelfExpToScill(70, 70, 70, 70);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
//<-- Бесчестный конкурент конец
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Jason---------------------------------------Заносчивый аристократ------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "Badboy_capture":
			sld = characterFromId("Badboy");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Afraid", "Badboy_afraid", 3.0);
        break;
		
		case "Badboy_afraid":
			LAi_SetActorType(pchar);
			sld = characterFromID("Badboy");        
			LAi_SetActorType(sld);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
        break;
		
		case "Badboy_killed_end":
		sld = characterFromID("Badboy"); 
		LAi_SetActorType(sld);
		LAi_KillCharacter(sld);
		LAi_SetPlayerType(pchar);
		ChangeCharacterComplexReputation(pchar,"nobility", -15); 
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
		break;
		
		case "Badboy_die":
			if (CheckAttribute(PChar, "quest.BadboyPlace")) Pchar.quest.BadboyPlace.over = "yes";
			if (CheckAttribute(PChar, "quest.BadboyDuelTimer")) Pchar.quest.BadboyDuelTimer.over = "yes";
			DoQuestCheckDelay("hide_weapon", 1.0);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown", false); //офицеров пускать
			locations[FindLocation(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown")].DisableEncounters = false; //энкаутеры откроем
			pchar.GenQuest.Badboy.Complete = "true";
		break;
// <-- Заносчивый аристократ конец
		
///////////////////////////////////////////////////////////////////////////////////////////////////
///  Jason  								Бремя гасконца
//////////////////////////////////////////////////////////////////////////////////////////////////
	case "Sharlie_Start":
		LoadMainCharacterInFirstLocationGroup("My_Campus", "rld", "loc2");
		sld = GetCharacter(NPC_GenerateCharacter("Sh_startsailor", "citiz_39", "man", "man", 10, FRANCE, 0, false, "quest"));
		FantomMakeCoolFighter(sld, 10, 10, 10, "blade_10", "pistol1", "bullet", 10);
		sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
		sld.Dialog.currentnode = "Startsailor";
		sld.name = "Жерар";
		sld.lastname = "Артуа";
		sld.greeting = "start_sailor";
		ChangeCharacterAddressGroup(sld, "My_Campus", "rld", "aloc2");
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
		chrDisableReloadToLocation = true;//закрыть локацию на всякий
	break;
	
	case "Sharlie_onLand"://старт линейки
		LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", true);//закроем верфь
		LocatorReloadEnterDisable("Fortfrance_town", "basement1", true);//закроем подземелье
		LocatorReloadEnterDisable("Fortfrance_town", "reloadPr1", true);//закроем базу
		bDisableFastReload = true;//закрыть переход
		pchar.GenQuest.CannotWait = true;//запрет ожидания
		bQuestDisableMapEnter = true;//закрыть карту
		i = FindColony("Fortfrance");
		colonies[i].DontSetShipInPort = true;//не ставить в порту корабли
		AddQuestRecord("Sharlie", "1");
		AddQuestRecordInfo("Sharlie_Father", "1");
		AddQuestRecordInfo("Sharlie_Shevallie", "1");
		AddQuestRecordInfo("Sharlie_Lover", "1");
		pchar.questTemp.Sharlie = "Start";
		pchar.questTemp.Sharlie.Lock = "true";
		pchar.NoNavyPenalty = true; // не штрафовать за нехватку навигации
		pchar.questTemp.Sharlie.Citcount = 0;//туповато, но пусть хоть поспрашивает числом
		LocatorReloadEnterDisable("Charles_townhall", "reload3", true);//закроем вход к Пуанси
		// закрываем все острова, кроме Гваделупы и Мартиники
		for (i=0; i<MAX_ISLANDS; i++)
		{				
			if (Islands[i].id != "Guadeloupe" && Islands[i].id != "Martinique")
			{
				Island_SetReloadEnableGlobal(Islands[i].id, false);
			}
		}
		// 170712 закроем склад магазина
		LocatorReloadEnterDisable("FortFrance_store", "reload2", true);
		// ставим гида
		sld = GetCharacter(NPC_GenerateCharacter("Guide", "Guide_1", "man", "man", 10, FRANCE, -1, true, "officer"));
		SetFantomParamFromRank(sld, 10, true);
		RemoveAllCharacterItems(sld, true);
		GiveItem2Character(sld, "blade_12");
		EquipCharacterbyItem(sld, "blade_12");
		sld.name = "Грегуар";
		sld.lastname = "Валинье";
		sld.dialog.FileName = "Quest\Sharlie\Guide.c";
		sld.dialog.currentnode = "guide_0";
		sld.greeting = "noble_male";
		LAi_SetImmortal(sld, true);
		if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "Sliding");
		ChangeCharacterAddressGroup(sld, "Fortfrance_town", "quest", "quest1");
		sld.protector = true;
		LAi_SetGuardianType(sld);
		sld.protector.CheckAlways = true; 
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		// не ставить корабли на Тортуге
		i = FindColony("Tortuga");
		colonies[i].DontSetShipInPort = true;//не ставить в порту корабли
		pchar.GenQuest.MapClosedNoBattle = true;
	break;
	
	case "Sharlie_GoFromPrison"://выпускаем из тюрьмы и ставим Мишеля
		AddQuestRecord("Sharlie", "2");
		pchar.questTemp.jailCanMove = true; //разрешить пройти мимо стражи
		DoQuestReloadToLocation(pchar.location, "goto", "goto23", "");
		LocatorReloadEnterDisable("Fortfrance_town", "reloadPr1", false);//откроем базу
		sld = characterFromId("Mishelle");
		sld.dialog.currentnode = "Mishelle_prisoner";
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "FortFrance_Dungeon", "quest", "quest1");
		pchar.questTemp.Sharlie = "basement";
		pchar.questTemp.Sharlie.Pardon = "true";
		SetFunctionTimerCondition("Sharlie_PardonOver", 0, 0, 2, false);
		DeleteAttribute(pchar, "questTemp.Sharlie.Citcount");
	break;
	
	case "Sharlie_SetBenua": //ноду аббату Бенуа
		sld = characterFromId("Benua");
		sld.dialog.currentnode = "Benua_meeting";
		AddQuestRecord("Sharlie", "3");
		DeleteAttribute(pchar, "questTemp.Sharlie.Citcount");
	break;
	
	case "Maltie_GoTown"://
		chrDisableReloadToLocation = false;//открыть локацию
		LocatorReloadEnterDisable("FortFrance_town", "reload4_back", true);//таверну закрыть
		LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//ворота закрыть
		Pchar.quest.Sharlie_Maltie.win_condition.l1 = "location";
		Pchar.quest.Sharlie_Maltie.win_condition.l1.location = "FortFrance_town";
		Pchar.quest.Sharlie_Maltie.win_condition = "Maltie_GoBasement";
	break;
	
	case "Maltie_GoBasement"://идем по городу
		sld = characterFromId("Sh_Maltie");
		LAi_ActorGoToLocation(sld, "reload", "reloadPr1", "FortFrance_Dungeon", "reload", "reload1", "Maltie_OpenBasement", -1);
		Pchar.quest.Sharlie_Maltie1.win_condition.l1 = "location";
		Pchar.quest.Sharlie_Maltie1.win_condition.l1.location = "FortFrance_Dungeon";
		Pchar.quest.Sharlie_Maltie1.win_condition = "Maltie_InBasement";
	break;
	
	case "Maltie_OpenBasement"://ставим Мишеля
		LocatorReloadEnterDisable("Fortfrance_town", "reloadPr1", false);//откроем базу
		sld = characterFromId("Mishelle");
		sld.dialog.currentnode = "Mishelle_prisoner";
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "FortFrance_Dungeon", "quest", "quest1");
		pchar.questTemp.Sharlie = "basement";
	break;

	case "Maltie_InBasement"://идем по городу
		chrDisableReloadToLocation = true;//закрыть локацию
		LocatorReloadEnterDisable("FortFrance_town", "reload4_back", false);//таверну открыть
		LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);//ворота открыть
		sld = characterFromId("Sh_Maltie");
		sld.dialog.currentnode = "Sharlie_maltie_3";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 1.0, -1);
	break;
	
	//------------------------------------------ гид - знакомство с игрой ---------------------------------------
	case "Guide_tavern":
		sld = characterFromId("Guide");
		sld.dialog.currentnode = "guide_4";
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_SetPlayerType(pchar);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	break;
	
	case "Guide_store":
		sld = characterFromId("Guide");
		sld.dialog.currentnode = "guide_6";
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_SetPlayerType(pchar);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	break;
	
	case "Guide_prison":
		sld = characterFromId("Guide");
		sld.dialog.currentnode = "guide_8";
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_SetPlayerType(pchar);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	break;
	
	case "Guide_market":
		sld = characterFromId("Guide");
		sld.dialog.currentnode = "guide_10";
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_SetPlayerType(pchar);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	break;
	
	case "Guide_townhall":
		sld = characterFromId("Guide");
		sld.dialog.currentnode = "guide_12";
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_SetPlayerType(pchar);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	break;
	
	case "Guide_bank":
		sld = characterFromId("Guide");
		sld.dialog.currentnode = "guide_18";
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_SetPlayerType(pchar);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	break;
	
	case "Guide_brothel":
		sld = characterFromId("Guide");
		sld.dialog.currentnode = "guide_20";
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_SetPlayerType(pchar);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	break;
	
	case "Guide_next":
		sld = characterFromId("Guide");
		LAi_CharacterEnableDialog(sld);
		sld.dialog.currentnode = "guide_21";
		ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto4");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	break;
	
	case "Guide_shipyard":
		sld = characterFromId("Guide");
		sld.dialog.currentnode = "guide_27";
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_SetPlayerType(pchar);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	break;
	
	case "Guide_port":
		sld = characterFromId("Guide");
		sld.dialog.currentnode = "guide_29";
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_SetPlayerType(pchar);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	break;
	
	case "Guide_portoffice":
		sld = characterFromId("Guide");
		sld.dialog.currentnode = "guide_40";
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_SetPlayerType(pchar);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	break;
	
	case "Guide_gate":
		sld = characterFromId("Guide");
		sld.dialog.currentnode = "guide_44";
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_SetPlayerType(pchar);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	break;
	
	case "Guide_ExitTown":
		chrDisableReloadToLocation = true;//закрыть локацию
		sld = characterFromId("Guide");
		sld.dialog.currentnode = "guide_49";
		ChangeCharacterAddressGroup(sld, "FortFrance_ExitTown", "goto", "goto7");
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_SetPlayerType(pchar);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	break;
	
	case "Guide_HeroWin": // ГГ выиграл фехт
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 1.2);
		LAi_RemoveCheckMinHP(pchar); // вот где собака порылась 251116
		sld = characterFromId("Guide");
		if (sti(sld.quest.guide_win == 0)) sld.dialog.currentnode = "guide_57"; // с первого раза побил
		else sld.dialog.currentnode = "guide_58"; 
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	break;
	
	case "Guide_HeroFail": // ГГ проиграл фехт
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 0.5);
		sld = characterFromId("Guide");
		sld.quest.guide_win = sti(sld.quest.guide_win)+1;
		if (sti(sld.quest.guide_win == 1)) sld.dialog.currentnode = "guide_59"; // один раз побили
		else 
		{
			if (sti(sld.quest.guide_win == 2)) sld.dialog.currentnode = "guide_60"; // два раза побили
			else sld.dialog.currentnode = "guide_61"; //три раза побили
		}
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		LAi_SetImmortal(pchar, false);
	break;
	// <-- гид
	
	case "Rum_CapGoodbye":
		sld = characterFromId("Rum_Cap");
		sld.dialog.currentnode = "Rum_Cap_3";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 1.0, -1);
	break;
	
	case "Rum_RemoveBarkas":
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
		Island_SetReloadEnableGlobal("Martinique", true);
		i = FindIsland("Martinique");
		Islands[i].EffectRadius = 5000; // new
		Group_DeleteGroup("Rum_CapGroup");
		pchar.Ship.Type = SHIP_NOTUSED;
		DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
		AddQuestRecord("SharlieB", "6");
		CloseQuestHeader("SharlieB");
		i = FindLocation("Fortfrance_town");
		setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
	break;
	
	case "GigoloGirl_SetCitizen":
		sld = characterFromId("GigoloGirl");
		LAi_SetCitizenType(sld);
	break;
	
	case "GigoloGirl_Remove":
		sld = characterFromId("GigoloGirl");
		sld.lifeday = 0;
		AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
		DeleteAttribute(pchar, "questTemp.Sharlie.Gigolo");
		AddQuestRecord("SharlieC", "3");
		CloseQuestHeader("SharlieC");
	break;
	
	case "Captive_PiratesDead":
		LAi_group_Delete("EnemyFight");
		pchar.GenQuest.Notsearchbody = true; // 170712
		sld = characterFromId("CaptiveSpain");
		GiveItem2Character(sld, "blade_03");
		EquipCharacterbyItem(sld, "blade_03");
		LAi_CharacterEnableDialog(sld);
		sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
		sld.Dialog.currentnode = "CaptiveSpain";
		sld.greeting = "spa_engineer";
		LAi_SetActorType(pchar);
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		AddComplexSelfExpToScill(50, 50, 50, 50);
	break;
	
	case "CaptiveSpain_capture":
		LAi_group_Delete("EnemyFight");
		sld = characterFromId("CaptiveSpain");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	break;
	
	case "FolkeStay":
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Folke");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0); // 170712
	break;
	
	case "Seabattle_pirate_open":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
		chrDisableReloadToLocation = false;//открыть локацию
	break;
	
	case "TichingituFree":
		sld = characterFromId("Tichingitu");
		sld.dialog.currentnode = "Tichingitu_9";
		ChangeCharacterAddressGroup(sld, "BasTer_exittown", "rld", "aloc14"); // 170712
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		RemoveAllCharacterItems(sld, true);
		GiveItem2Character(sld, "topor_05");
		EquipCharacterbyItem(sld, "topor_05"); // 151012
	break;
	
	case "Newstorehelper_ready":
		chrDisableReloadToLocation = true;
		for (i=1; i<=3; i++)
		{
			sld = characterFromId("Newstorehelper_"+i);
			LAi_SetStayType(sld);
		}
	break;
	
	case "RescueDaughter_KillIndiansLand":
		LAi_group_Delete("EnemyFight");
		sld = characterFromId("RD_Prosper");
		if (LAi_GetCharacterHP(sld) > 0)
		{
			LAi_SetActorType(sld);
			sld.MusketerDistance = 20;
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else
		{
			AddQuestRecord("Sharlie", "F6");
			LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload1_back", false);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.location = "Martinique_Grot";
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CreateIndiansGrot";
			pchar.questTemp.Sharlie.RescueDaughter.KillProsper = "true";
		}
	break;
	
	case "RescueDaughter_IndFight":
		if (!CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter.KillProsper"))
		{
			sld = characterFromId("RD_Prosper");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		LAi_SetFightMode(pchar, true);
		for (i=1; i<=4; i++)
		{
			sld = characterFromId("RD_IndCave_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "RescueDaughter_KillIndiansGrot");
	break;
	
	case "RescueDaughter_KillIndiansGrot":
		LAi_group_Delete("EnemyFight");
		sld = characterFromId("RD_Selina");
		LAi_SetActorType(sld);
		if (!CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter.KillProsper"))
		{
			chr = characterFromId("RD_Prosper");
			if (LAi_GetCharacterHP(chr) > 0)
			{
				sld.dialog.currentnode = "Selina";
				chr.MusketerDistance = 20;
				LAi_SetActorType(chr);
				LAi_ActorFollow(sld, chr, "", -1);
				LAi_ActorDialog(chr, pchar, "", -1, 0);
			}
			else
			{
				sld.dialog.currentnode = "Selina_3";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
				pchar.questTemp.Sharlie.RescueDaughter.KillProsper = "true";
			}
		}
		else
		{
			sld.dialog.currentnode = "Selina_3";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	break;
	
	// выпивка с Фадеем
	case "Sharlie_DrinkWithFadey":
		LAi_SetActorType(pchar);
		LAi_ActorSetSitMode(pchar);
		InterfaceStates.Buttons.Save.enable = false;
		bDisableCharacterMenu = true;//лоченые интерфейсы
		DoQuestCheckDelay("Sharlie_DrinkWithFadey_music", 0.8);
		DoQuestCheckDelay("Sharlie_DrinkWithFadey_1", 33.0);
	break;
	
	case "Sharlie_DrinkWithFadey_music":
		SetMusic("hol_music_tavern");
	break;
	
	case "Sharlie_DrinkWithFadey_1":
		LAi_SetPlayerType(pchar);
		InterfaceStates.Buttons.Save.enable = true;
		bDisableCharacterMenu = false;//лоченые интерфейсы
		pchar.GenQuest.CamShuttle = 3;
		WaitDate("",0,0,0,5,5);
		DoQuestReloadToLocation("BasTer_houseSp1", "goto", "goto1", "Sharlie_DrinkWithFadey_2");
	break;
	
	case "Sharlie_DrinkWithFadey_2":
		sld = characterFromId("Fadey");
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	break;
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////	
///Jason------------------------------------- Карибские нравы ----------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "Trial_AfterTavernFight":
		chrDisableReloadToLocation = false;//открыть локацию
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
		AddQuestRecord("Trial", "13");
	break;
	
	case "Trial_ReturnPoormanNorm":
		chrDisableReloadToLocation = false;//открыть локацию
		sld = characterFromId("PortoBello_Poorman");
		sld.dialog.currentnode = "First time";
		LAi_SetLoginTime(sld, 9.0, 21.99);
		ChangeCharacterAddressGroup(sld, "Portobello_town", "goto", "goto15");
		LAi_SetPoorType(sld);
		LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	break;
///////////////////////////////////////////////////////////////////////////////////////////////////
///  Jason  								Голландский гамбит
//////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------общие функции-----------------------------------------------
		case "ReturnTalkerToOfficer":
			chrDisableReloadToLocation = false;
			pchar.quest.HWIC_ReturnOfficer.win_condition.l1 = "location";
			pchar.quest.HWIC_ReturnOfficer.win_condition.l1.location = "Villemstad_town";
			pchar.quest.HWIC_ReturnOfficer.function = "HWICofficerTalkReturn";
		break;
		
		case "PrepareToBoom":
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;//ба-бах!
			pchar.GenQuest.ShipSituation.Explosion.CapId = "Fleetwood";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "PrepareToBoom1":
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;//ба-бах!
			pchar.GenQuest.ShipSituation.Explosion.CapId = "Lucas";
			AddComplexSelfExpToScill(150, 150, 150, 150);
		break;
		
		case "PrepareToBoom2":
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;//ба-бах!
			pchar.GenQuest.ShipSituation.Explosion.CapId = "JacobBerg";
			AddComplexSelfExpToScill(200, 200, 200, 200);
		break;
		
		case "JoakimInRoom":
			pchar.quest.Joakim_InRoom.win_condition.l1 = "location";
			pchar.quest.Joakim_InRoom.win_condition.l1.location = "Villemstad_houseSp1_room";
			pchar.quest.Joakim_InRoom.function = "JoakimTalk";
		break;
		
//------------------------------------за Голландию-------------------------------------------
		case "SantiagoTripTalkToMC":
			sld = characterFromId("SantiagoEnemy1");
			sld.dialog.currentnode = "Santiago_Trip_2";
			sld.greeting = "hambit_other_2";
			ChangeCharacterAddressGroup(sld, "Santiago_HouseSp2_Room", "barmen", "stay");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 2.0);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "SantiagoTripExitFromRoom":
			LocatorReloadEnterDisable("Santiago_HouseSp2_Room", "reload1", false);//открыть выход
			LAi_LocationFightDisable(&Locations[FindLocation("Santiago_HouseSp2")], true);//запретить драться // patch-2
			pchar.quest.Santiago_Trip2.win_condition.l1 = "locator";
			pchar.quest.Santiago_Trip2.win_condition.l1.location = "Santiago_HouseSp2";
			pchar.quest.Santiago_Trip2.win_condition.l1.locator_group = "reload";
			pchar.quest.Santiago_Trip2.win_condition.l1.locator = "reload3";
			pchar.quest.Santiago_Trip2.function = "SantiagoTripSecondTalk";
		break;
		
		case "SantiagoTripExitHouse":
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "1-45");
			pchar.questTemp.HWIC.Holl = "SantiagoTripReturn";
			AddComplexSelfExpToScill(80, 80, 80, 80);
		break;
		
		case "HollJacob_dead":
			DoQuestCheckDelay("hide_weapon", 1.0);
			pchar.quest.Holl_Jacob.win_condition.l1 = "item";
			pchar.quest.Holl_Jacob.win_condition.l1.item = "JacobJournal";
			pchar.quest.Holl_Jacob.function = "Jacob_Journal";
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
		
		case "BekSitDown":
			sld = characterFromId("hol_guber");
			sld.Dialog.Filename = "Common_Governor.c";
			sld.dialog.currentnode = "First time";
			LAi_SetHuberType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "sit", "sit1");
		break;
		
		case "LucasReturnInCabinet":
			sld = characterFromId("Lucas");
			sld.Dialog.Filename = "Quest\HollandGambit\LucasRodenburg.c";
			sld.dialog.currentnode = "Second_time";
			LAi_SetHuberType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_houseS3_residence", "sit", "sit1");
			LAi_SetPlayerType(pchar);
			bDisableFastReload = false;
		break;
		
		case "Merdok_AfterBattle": 
			LAi_LocationDisableOfficersGen("SentJons_TownCave", false);//офицеров пускать
			pchar.quest.Merdok_Book.win_condition.l1 = "item";
			pchar.quest.Merdok_Book.win_condition.l1.item = "MerdokArchive";
			pchar.quest.Merdok_Book.function = "FindMerdokBook";//прерывание на архив
			pchar.quest.Merdok_Key.win_condition.l1 = "item";
			pchar.quest.Merdok_Key.win_condition.l1.item = "Drugstore_keys";
			pchar.quest.Merdok_Key.function = "FindMerdokKey";//прерывание на ключ
			pchar.questTemp.HWIC.Holl = "MerdokDie";
			//а теперь проверим китайца
			sld = characterFromId("Longway");
			sld.greeting = "";
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayFriend") && GetCharacterIndex("Longway") != -1)
			{
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
//-----------------------------------------за Англию--------------------------------------------
		case "OpenFleetwoodDoor":
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", false);
		break;
		
		case "SitInGrot":
			LAi_SetActorType(Pchar);
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 2.5);
			DoQuestFunctionDelay("StandUpInGrot", 2.5);
        break;
		
		case "MonsterStandUp":
			sld = characterFromId("Chavinavi");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "MonsterFight", 3.5);
			PlaySound("VOICE\Russian\hambit\Chavinavy.wav");
        break;
		
		case "MonsterFight":
			PlaySound("ambient\horror\horror2.wav");
			PlaySound("types\skel.wav");
			LAi_SetPlayerType(Pchar);
			sld = characterFromId("Chavinavi");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GrotAfterBattle");
        break;
		
		case "GrotAfterBattle":
			pchar.quest.Abby_IslandHeadBarmen.win_condition.l1 = "item";
			pchar.quest.Abby_IslandHeadBarmen.win_condition.l1.item = "GastonHead";
			pchar.quest.Abby_IslandHeadBarmen.function = "HeadBarmen_Find";//на нахождение бошки бармена
			AddComplexSelfExpToScill(200, 200, 200, 200);
		break;
		
		case "Merdok_AfterBattleEng":
			LocatorReloadEnterDisable("SentJons_TownCave", "reload2", false);//выход откроем
			LAi_LocationDisableOfficersGen("SentJons_TownCave", false);//офицеров пускать
			pchar.quest.Merdok_Book.win_condition.l1 = "item";
			pchar.quest.Merdok_Book.win_condition.l1.item = "MerdokArchive";
			pchar.quest.Merdok_Book.function = "FindMerdokBook";//прерывание на архив
			pchar.quest.Merdok_Map.win_condition.l1 = "item";
			pchar.quest.Merdok_Map.win_condition.l1.item = "NPC_Letter";
			pchar.quest.Merdok_Map.function = "CreateLucasBonanza";//прерывание на карту клада
			pchar.questTemp.HWIC.Eng = "MerdokDie";
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.GenQuest.NoDelBody = true;
		break;
		
//-------------------------------------------против всех-----------------------------------------------------
		case "Fernando_FightInPort":
			chrDisableReloadToLocation = true;//выходы закроем
			iTemp = GetCharacterIndex("HWICFernando");
			if (iTemp != -1)
			{			
				sld = &characters[iTemp];
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");			
				LAi_group_Attack(sld, Pchar);			
				SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			}
			pchar.quest.HWIC_Fernando.win_condition.l1 = "NPC_Death";
			pchar.quest.HWIC_Fernando.win_condition.l1.character = "HWICFernando";
			pchar.quest.HWIC_Fernando.function = "Fernando_died";
		break;
		
		case "PrepareToStreetFight":
			chrDisableReloadToLocation = false;
			pchar.quest.Fleetwood_deafenning.win_condition.l1 = "location";
			pchar.quest.Fleetwood_deafenning.win_condition.l1.location = "SentJons_town";
			pchar.quest.Fleetwood_deafenning.function = "SJ_StreetFight";
		break;
		
		case "MC_deafenning":
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("hide_weapon", 1.0);
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "death_citizen_1", "Without_consciousness", 5.0);
		break;
		
		case "Without_consciousness":
			SetLaunchFrameFormParam("Вы потеряли сознание от полученных ран...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 5, 9, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("InMerdokHouse", 5.0);
			if (2-sti(RealShips[sti(pchar.ship.type)].basetype) < 0) pchar.Ship.Type = SHIP_NOTUSED;
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);//дом Флитвуда закроем
		break;
		
		case "MerdokTalkToMC":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Merdok");
			sld.dialog.currentnode = "MC_InHouse";
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "barmen", "bar3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromId("Tonzag");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			AddComplexSelfExpToScill(100, 100, 100, 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
		
		case "Kill_Knippel":
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "Knippel_die", 1.0);
		break;
		
		case "Knippel_die":
			sld = characterFromId("KnippelClone");
			LAi_KillCharacter(sld);
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_2";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ReturnMCPlayer":
            LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
        break;
		
		case "Abigile_Stay":
			sld = characterFromId("Abigile");
			LAi_SetOwnerType(sld);
			LocatorReloadEnterDisable("Villemstad_houseSP2", "reload2", false);//откроем комнату Аби
		break;
		
		case "SetAbigileToCabin":
			int iShipType = GetCharacterShipType(pchar);
			ref rShip = GetRealShip(iShipType);
			sTemp = "My_" + rShip.CabinType;
			sld = characterFromId("Abigile");
			ChangeCharacterAddressGroup(sld, sTemp, "rld", "aloc0");
			LAi_SetCitizenType(sld);
			chrDisableReloadToLocation = false;
		break;
		
		case "ContinueWithMerdok":
			sld = characterFromId("Merdok");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "MC_writeLetter":
			LAi_SetActorType(pchar);
			LAi_SetSitType(pchar);
			DoQuestFunctionDelay("MC_writeLetterGo", 3.0);
		break;
		
		case "MC_TakeCloves":
			chrDisableReloadToLocation = false;
			sld = characterFromId("Merdok");
			LAi_SetOwnerType(sld);
		break;
		
		case "DrunkardGoTown":
			chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Drunkard");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "houseSP3", "SentJons_houseSP3", "reload", "reload1", "DrunkardInHouse", -1);	
			bDisableFastReload = true;//закроем быстрый переход
			pchar.GenQuest.CannotWait = true;//не мотать время
		break;
		
		case "DrunkardInHouse":
			DoQuestFunctionDelay("DrunkardReturnToTavern", 120.0);
		break;
		
		case "DrunkardSitInTavern":
			sld = characterFromId("Drunkard");
			sld.dialog.currentnode = "Drunkard_9";
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Sentjons_tavern", "sit", "sit_front1");
			bDisableFastReload = false;
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", false);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", false);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", false);
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			SetFunctionTimerCondition("Fleetwood_meetingOver", 0, 0, 15, false);//таймер сюда поставим
		break;
		
		case "FleetwoodDiedInShore":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-31");
			pchar.quest.Login_Val.win_condition.l1 = "location";
			pchar.quest.Login_Val.win_condition.l1.location = "Terks";
			pchar.quest.Login_Val.function = "CreateValkiriaBrig";
			AddComplexSelfExpToScill(100, 100, 100, 100);
			for (i=1; i<=7; i++)
	        {
			//log_info("чистим матросов");	// лесник удалил матросов после боя с флитвудом.
		     sld = characterFromId("OwrSailor_"+i);
		     sld.lifeday = 0;//убираем засаду
	        }
		break;
		
		case "ReturnShoreToNormal":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore31")], false);
			locations[FindLocation("Shore31")].DisableEncounters = false; //локацию в норму
		break;
		
		case "OpenVillemstadResidence":
			LocatorReloadEnterDisable("Villemstad_town", "reload3_back", false);//открыть вход в резиденцию
			LocatorReloadEnterDisable("Villemstad_town", "reloadR1", false);//открыть боковой вход в резиденцию
			for (i=1; i<=5; i++)
			{
			chr = characterFromId("StivesantGuard_"+i);
			ChangeCharacterAddressGroup(chr, "Villemstad_townhall", "goto", "goto5");
			}
			sld = characterFromId("Stivesant");
			LAi_ActorFollow(chr, sld, "", -1);
			pchar.quest.Piter_Go.win_condition.l1 = "location";
			pchar.quest.Piter_Go.win_condition.l1.location = "Villemstad_townhall";
			pchar.quest.Piter_Go.function = "InVillemstadResidense";
		break;
		
		case "PiterTalkWithLucas":
			StartQuestMovie(true, true, true);
			ChangeShowIntarface();
			LAi_ActorTurnToCharacter(pchar, characterFromID("Lucas"));
			SetMainCharacterIndex(GetCharacterIndex("Lucas"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Stivesant");
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Stivesant_2";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DoubleTalkWithLucas":	
			sld = characterFromId("hol_guber");
			LAi_ActorTurnToCharacter(sld, characterFromID("Lucas"));
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Bek";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "LucasGoToPrison":	
			sld = characterFromId("Lucas");
			sld.greeting = ""; // озвучка напрямую
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto9");
			sld = characterFromId("Merdok");
			sld.greeting = "merdok_5";
		break;
		
		case "TalkWithLucasPrisoner":	
			sld = characterFromId("Lucas");
			GiveItem2Character(sld, "unarmed");
			EquipCharacterbyItem(sld, "unarmed"); 
			sld.Dialog.Filename = "Quest\HollandGambit\LucasRodenburg.c";
			sld.dialog.currentnode = "LucasPrisoner";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
		break;
		
		case "StivesantSitDown":
			sld = characterFromId("Stivesant");
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Stivesant_18";
			LAi_SetHuberType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "sit", "sit1");
			pchar.quest.Piter_Remove.win_condition.l1 = "Timer";
			pchar.quest.Piter_Remove.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Piter_Remove.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.Piter_Remove.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.Piter_Remove.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.Piter_Remove.function = "PiterStivesantRemove";
		break;
		
		case "ReturnAbiNormal":	
			sld = characterFromId("Solomon");
			LAi_SetOwnerType(sld);
			sld = characterFromId("Abigile");
			LAi_SetOwnerType(sld);
		break;
		
		case "PrepareMassakraInShore":	
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-61");
			pchar.quest.vanberg_ShoreBattle.win_condition.l1 = "location";
			pchar.quest.vanberg_ShoreBattle.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.vanberg_ShoreBattle.function = "CreateVanbergSailors";
		break;
		
		case "PrepareVanbergInSea":	
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-62");
			pchar.quest.vanberg_SeaBattle.win_condition.l1 = "location";
			pchar.quest.vanberg_SeaBattle.win_condition.l1.location = "IslaDeCoche";
			pchar.quest.vanberg_SeaBattle.function = "CreateVanbergInSea";
			AddComplexSelfExpToScill(100, 100, 100, 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
//<--Голландский Гамбит конец
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////	
///Jason---------------------------------------Пиратская Сага--------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ---------------------------------поведение бандитов у рудника-----------------------------------------
		case "Saga_MineBanditsTalk": // инициализация разговора
			DoQuestCheckDelay("hide_weapon", 0.5);
			if (pchar.location == "mine_exit") sld = characterFromId("Mine_bandit_3");
			else sld = characterFromId("Mine_banditx_1");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Saga_MineBanditsFire": // стреляют из пушки
			CreateLocationParticles("blast_inv", "quest", "gun1", 1.15, 0, 0, "cannon_fire_1");
			CreateLocationParticles("blast_inv", "quest", "gun2", 1.15, 0, 0, "cannon_fire_1");
			LAi_KillCharacter(pchar);
		break;
		
		case "Saga_MineBanditsxFire": // стреляют из мушкетов // 250812
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Mine_banditx_"+i);
				LAi_SetActorType(sld);
				LAi_ActorAnimation(sld, "shot", "Saga_MineBanditsxFire_1", 1.0);
			}
		break;
		
		case "Saga_MineBanditsxFire_1":
			LAi_KillCharacter(pchar);
		break;
		
	// -------------------------------------штурм рудника----------------------------------------------------
		case "Saga_MineBanditxDie":
			n = Findlocation("mine_01");
			DeleteAttribute(&locations[n], "mine_bandits");
			sld = characterFromId("Mine_banditx_1");
			LAi_KillCharacter(sld);
			sld = characterFromId("Svensons_sold_12");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("Svensons_off_2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=2; i<=4; i++)
			{
				sld = characterFromId("Mine_banditx_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_BanditsxDestroyed");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Saga_BanditsxDestroyed":
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Svensons_sold_12");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_SetCurHPMax(sld);
			}
			sld = characterFromId("Svensons_off_2");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_SetCurHPMax(sld);
			}
			pchar.quest.Saga_MineAttack_04.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_04.win_condition.l1.location = "Mine_04";
			pchar.quest.Saga_MineAttack_04.function = "Saga_PrepareMineAttackTail";
			AddComplexSelfExpToScill(150, 150, 150, 150);
		break;
		
		case "Saga_MineBanditDie":
			sld = characterFromId("Mine_bandit_1");
			LAi_KillCharacter(sld);
			sld = characterFromId("Svensons_sold_12");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("Svensons_off_2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=2; i<=6; i++)
			{
				sld = characterFromId("Mine_bandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_BanditsDestroyed");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Saga_BanditsDestroyed":
			LAi_group_Delete("EnemyFight");
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "mine_attack_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
	// канонада
		case "Saga_MineSetMusic":
			SetMusic("music_military");
		break;
		
		case "Saga_Gunfire": // выстрел
			float ftime = 1.5;
			CreateLocationParticles("Ship_cannon_fire", "goto", "fire", 1.0, 40, 40, "cannon_fire_1");
			sld = characterFromId("Svensons_off_1");
			if (sld.quest.canonada == "1" || sld.quest.canonada == "2") ftime = 2.5;
			DoQuestCheckDelay("Saga_Gunexplode_0"+sld.quest.canonada, ftime);
		break;
		
		case "Saga_GunTalk": // базар
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Svensons_off_1");
			sld.dialog.currentnode = "gunner_"+sld.quest.canonada;
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Saga_Gunexplode_01": // взрыв первый
			CreateLocationParticles("ShipExplode", "goto", "burn11", 1.0, 0, 0, "boom");
			CreateLocationParticles("blast_dirt", "goto", "burn11", 1.0, 0, 0, "");
			CreateLocationParticles("blast_inv", "goto", "burn11", 1.0, 0, 0, "");
			DoQuestCheckDelay("Saga_GunTalk", 3.0);
		break;
		
		case "Saga_Gunexplode_02": // взрыв второй
			CreateLocationParticles("ShipExplode", "goto", "burn12", 1.0, 0, 0, "boom");
			CreateLocationParticles("blast_dirt", "goto", "burn12", 1.0, 0, 0, "");
			CreateLocationParticles("shipfire", "goto", "burn12", 0, 0, 0, "");
			CreateLocationParticles("large_smoke", "goto", "burn12", 1.0, 0, 0, "");
			CreateLocationParticles("shipfire", "goto", "burn12", 1.0, 0, 0, "");
			DoQuestCheckDelay("Saga_GunTalk", 6.0);
		break;
		
		case "Saga_LoginBandos_01": // бандюки-1
			for (i=1; i<=3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mine_Bandos_01_"+i, "citiz_"+(rand(9)+51), "man", "man", 30, PIRATE, 0, true, "soldier"));
				FantomMakeCoolFighter(sld, 30, 60, 60, "blade_10", "", "bullet", 100);
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "mine", "rld", "warrior");
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", "TMP_FRIEND", true);
			DoQuestCheckDelay("Saga_Gunfire", 5.5);
		break;
		
		case "Saga_Gunexplode_03": // взрыв третий
			CreateLocationParticles("ShipExplode", "goto", "boom2", 1.0, 0, 0, "boom");
			CreateLocationParticles("blast_dirt", "goto", "boom2", 1.0, 0, 0, "");
			CreateLocationParticles("blast_inv", "goto", "boom2", 1.0, 0, 0, "");
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Mine_Bandos_01_"+i);
				LAi_KillCharacter(sld);
			}
			DoQuestCheckDelay("Saga_GunTalk", 2.5);
		break;
		
		case "Saga_LoginBandos_02": // бандюки-2
			for (i=1; i<=3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mine_Bandos_02_"+i, "mush_ctz_"+(rand(2)+10), "man", "mushketer", 35, PIRATE, 0, true, "soldier"));
				FantomMakeCoolFighter(sld, 35, 70, 70, "", "mushket1", "cartridge", 100);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "mine", "rld", "warrior");
				LAi_ActorRunToLocator(sld, "rld", "detector1", "", -1);
			}
			DoQuestCheckDelay("Saga_Gunfire", 3.0);
		break;
		
		case "Saga_Gunexplode_04": // взрыв четвертый
			CreateLocationParticles("ShipExplode", "goto", "boom1", 1.0, 0, 0, "boom");
			CreateLocationParticles("blast_dirt", "goto", "boom1", 1.0, 0, 0, "");
			CreateLocationParticles("blast_inv", "goto", "boom1", 1.0, 0, 0, "");
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Mine_Bandos_02_"+i);
				LAi_KillCharacter(sld);
			}
			DoQuestCheckDelay("Saga_LoginBandos_03", 3.0);
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\_bombs_npc.wav");
		break;
		
		case "Saga_LoginBandos_03": // бандюки-3
			sld = characterFromId("Svensons_off_1");
			sld.quest.canonada = "5";
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mine_Bandos_03_"+i, "citiz_"+(rand(9)+51), "man", "man", 35, PIRATE, 0, true, "soldier"));
				FantomMakeCoolFighter(sld, 35, 70, 70, "blade_10", "", "bullet", 100);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "mine", "rld", "warrior");
				LAi_ActorRunToLocator(sld, "rld", "detector2", "", -1);
			}
			DoQuestCheckDelay("Saga_Gunfire", 3.5);
		break;
		
		case "Saga_Gunexplode_05": // взрыв пятый
			CreateLocationParticles("ShipExplode", "goto", "boom3", 1.0, 0, 0, "boom");
			CreateLocationParticles("blast_dirt", "goto", "boom3", 1.0, 0, 0, "");
			CreateLocationParticles("blast_inv", "goto", "boom3", 1.0, 0, 0, "");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Mine_Bandos_03_"+i);
				LAi_KillCharacter(sld);
			}
			DoQuestCheckDelay("Saga_LoginBandos_04", 0.5);
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\_grapes_npc.wav");
		break;
		
		case "Saga_LoginBandos_04": // бандюки-4
			for (i=1; i<=7; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mine_Bandos_04_"+i, "citiz_"+(rand(9)+51), "man", "man", 35, PIRATE, 0, true, "soldier"));
				FantomMakeCoolFighter(sld, 35, 70, 70, "blade_10", "", "bullet", 100);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "mine", "rld", "warrior");
				LAi_ActorRunToLocator(sld, "rld", "detector2", "", -1);
			}
			DoQuestCheckDelay("Saga_Bandos_04_Attack", 3.5);
		break;
		
		case "Saga_Bandos_04_Attack": // 
			for (i=1; i<=7; i++)
			{
				sld = characterFromId("Mine_Bandos_04_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", "TMP_FRIEND", true);
			DoQuestCheckDelay("Saga_GunfireGrape", 6.0);
		break;
		
		case "Saga_GunfireGrape": // выстрел
			CreateLocationParticles("Bombard", "goto", "fire", 1.0, 90, 90, "cannon_fire_2");
			CreateLocationParticles("blast_dirt", "goto", "fire", 1.0, 90, 90, "");
			CreateLocationParticles("blast_dirt", "goto", "fire", 1.0, 90, 90, "");
			DoQuestCheckDelay("Saga_Gunexplode_06", 0.5);
		break;
		
		case "Saga_Gunexplode_06": // выстрел картечью
			for (i=3; i<=7; i++)
			{
				sld = characterFromId("Mine_Bandos_04_"+i);
				LAi_KillCharacter(sld);
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Mine_Bandos_04_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "rld", "warrior", "none", "", "", "", 15.0);
			}
			DoQuestCheckDelay("Saga_GunTalk", 8.0);
			PlaySound("interface\abordage_wining.wav");
		break;
		
		// автоканонада
		case "Saga_GunAutoFire": // выстрел
			if (iTotalTemp <= 10)
			{
				CreateLocationParticles("Ship_cannon_fire", "goto", "fire", 1.0, 90, 90, "cannon_fire_1");
				DoQuestCheckDelay("Saga_GunAutoExplode", 2.5);
				iTotalTemp++;
			}
		break;
		
		case "Saga_GunAutoExplode": // взрыв
			CreateLocationParticles("ShipExplode", "goto", "burn"+iTotalTemp, 0, 0, 0, "boom");
			CreateLocationParticles("blast_dirt", "goto", "burn"+iTotalTemp, 0, 0, 0, "");
			CreateLocationParticles("blast_inv", "goto", "burn"+iTotalTemp, 0, 0, 0, "");
			if (iTotalTemp > 2 && iTotalTemp <= 7)
			{
				CreateLocationParticles("large_smoke", "goto", "burn"+iTotalTemp, 0, 0, 0, "");
				CreateLocationParticles("shipfire", "goto", "burn"+iTotalTemp, 0, 0, 0, "");
			}
			if (iTotalTemp > 7) CreateLocationParticles("smoke", "goto", "burn"+iTotalTemp, 0, 0, 0, "");
			if (iTotalTemp == 2)
			{
				for (i=5; i<=6; i++)
				{
					sld = characterFromId("Mine_Bandos_05_"+i);
					LAi_KillCharacter(sld);
				}
			}
			DoQuestCheckDelay("Saga_GunAutoFire", 4.0+iTotalTemp*2);
		break;
		
		case "Saga_MineBandos_05Die": // генерим партию бандюков в шесть рыл
			PlaySound("interface\abordage_wining.wav");
			iRank = 20+MOD_SKILL_ENEMY_RATE+5;
			iScl = 65;
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			for (i=1; i<=6; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mine_Bandos_06_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, 0, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl);
				ChangeCharacterAddressGroup(sld, "mine", "rld", "attack1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (MOD_SKILL_ENEMY_RATE > 4) sld.MultiFighter = 0.5+fMft; // мультифайтер
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_06Die");
			pchar.quest.Saga_MineFightLock1.win_condition.l1 = "locator";
			pchar.quest.Saga_MineFightLock1.win_condition.l1.location = "mine";
			pchar.quest.Saga_MineFightLock1.win_condition.l1.locator_group = "rld";
			pchar.quest.Saga_MineFightLock1.win_condition.l1.locator = "attack1"; // закрываем доступ в лагерь
			pchar.quest.Saga_MineFightLock1.function = "Saga_MineFightLock";
			pchar.quest.Saga_MineFightLock.win_condition.l1 = "locator";
			pchar.quest.Saga_MineFightLock.win_condition.l1.location = "mine";
			pchar.quest.Saga_MineFightLock.win_condition.l1.locator_group = "rld";
			pchar.quest.Saga_MineFightLock.win_condition.l1.locator = "warrior";
			pchar.quest.Saga_MineFightLock.function = "Saga_MineFightLock"; // закрываем доступ назад
		break;
		
		case "Saga_MineBandos_06Die": // генерим партию бандюков в восемь рыл
			PlaySound("interface\abordage_wining.wav");
			iRank = 20+MOD_SKILL_ENEMY_RATE+5;
			iScl = 70;
			for (i=1; i<=8; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mine_Bandos_07_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, 0, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol5", "bullet", iScl);
				ChangeCharacterAddressGroup(sld, "mine", "rld", "attack2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_07Die");
			DoQuestCheckDelay("Saga_MineBandos_SvensonHelp", 35.0);
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "Saga_MineBandos_SvensonHelp": // Свенсон идет на помощь
			PlaySound("interface\abordage_wining.wav");
			pchar.quest.Saga_MineFightLock.over = "yes"; //снять прерывание
			pchar.quest.Saga_MineFightLock1.over = "yes"; //снять прерывание
			sld = characterFromId("Svenson");
			ChangeCharacterAddressGroup(sld, "mine", "reload", "reload6");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			if (GetCharacterIndex("Svensons_off_2") != -1)
			{
				sld = characterFromId("Svensons_off_2");
				ChangeCharacterAddressGroup(sld, "mine", "reload", "reload6");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=11; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				ChangeCharacterAddressGroup(sld, "mine", "reload", "reload6");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		break;
		
		case "Saga_MineBandos_07Die": // 
			PlaySound("interface\abordage_wining.wav");
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "mine_attack_27";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddComplexSelfExpToScill(150, 150, 150, 150);
		break;
		
		case "Saga_MineAttackMinesLock": // 
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "mine_attack_32a";
			ChangeCharacterAddressGroup(sld, "mine_mines", "officers", "reload1_3");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_group_SetRelation("Mine_enemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheck("Mine_enemy", "Saga_MinesBanditsDestroyed");
		break;
		
		case "Saga_MinesBanditsDestroyed": // 
			LAi_group_Delete("Mine_enemy");
			LAi_group_SetHearRadius(LAI_GROUP_PLAYER, LAI_GROUP_PLA_HEAR);
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "mine_attack_32";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "Saga_MineWaitTime": // 
			//чистим всю солдатню
			for (i=1; i<=8; i++)
			{
				if (GetCharacterIndex("Ourmine_sold_"+i) != -1)
				{
					sld = characterFromId("Ourmine_sold_"+i);
					sld.lifeday = 0;
				}
			}
			for (i=1; i<=12; i++)
			{
				if (GetCharacterIndex("Svensons_sold_"+i) != -1)
				{
					sld = characterFromId("Svensons_sold_"+i);
					sld.lifeday = 0;
				}
			}
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					sld.lifeday = 0;
				}
			}
			GetCharacterPos(pchar, &locx, &locy, &locz);
			pchar.locx = locx;
			pchar.locy = locy;
			pchar.locz = locz;
			SetLaunchFrameFormParam("Прошли одни сутки..."+ NewStr() +"Серебро погружено на ваш корабль", "Reload_To_Location", 0.1, 5.0);
			SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
			WaitDate("", 0, 0, 0, iTemp, 0);
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			SetCharacterGoods(pchar, GOOD_SILVER, GetCargoGoods(pchar, GOOD_SILVER) + 2000+drand(100)); // кладем серебро
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "mine_attack_47";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
	// -----------------------начальная часть - пропавшая амазонка и наследница------------------------------
		case "Saga_KillJimmy":	
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_group_Delete("EnemyFight");
			pchar.questTemp.Saga = "jackman";
			if (CheckAttribute(pchar, "questTemp.Saga.Jimmysecret"))
			{
				AddQuestRecord("Saga", "4");
			}
			else AddQuestRecord("Saga", "3");
		break;
		
		case "Saga_AfterDonovanBoarding":
			sld = GetCharacter(NPC_GenerateCharacter("SagaTempsailor", "citiz_35", "man", "man", 10, sti(pchar.nation), 0, true, "quest"));
			sld.Dialog.Filename = "Quest\Saga\OtherNPC.c";
			sld.dialog.currentnode = "Tempsailor";
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc2");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddComplexSelfExpToScill(70, 70, 70, 70);
			AddComplexSeaExpToScill(100, 100, 100, 100, 100, 100, 0);
        break;
	
		case "Saga_KillGonsalesA":	
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("Saga", "16");
		break;
		
		case "Saga_KillGonsalesB":	
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("Saga", "18");
		break;
		
		case "Saga_HireHelena":	
			chrDisableReloadToLocation = false;//открыть локацию
			iTemp = 150+sti(pchar.rank)*5; // 14-add
			sld = characterFromId("Helena");
			LAi_SetHP(sld, iTemp, iTemp); 
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.CompanionDisable = true; //нельзя в компаньоны - чтобы не утонула
			sld.HalfImmortal = true; //чтобы не убили в сухопутном бою
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			sld.DontClearDead = true;
			sld.dialog.currentnode = "Helena_officer";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
		break;
	// <-- начальная часть
	
	//------------------------------------- возвращение барона ------------------------------------------
	
		case "Saga_ShowDolly":	// Даниэль показывает истукана
			sld = characterFromId("Danielle");
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "Dolly_2";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

	//--------------------------------------история Натана - видеоролики-----------------------
	case "Video_story": // 
		switch(pchar.questTemp.LSC.Natanstory)
		{
			case "idol": PChar.GenQuest.VideoAVI = "idol"; break;
			case "temple": PChar.GenQuest.VideoAVI = "temple"; break;
			case "blackpearl": PChar.GenQuest.VideoAVI = "blackpearl"; break;
			case "artefact": PChar.GenQuest.VideoAVI = "artefact"; break;
			case "ending": PChar.GenQuest.VideoAVI = "ending"; break;
			case "VDDrepair": PChar.GenQuest.VideoAVI = "VDDrepair"; break;
		}
		PChar.GenQuest.VideoAfterQuest = "Video_continueStory";
		DoQuestCheckDelay("PostVideo_Start", 0.2);
	break;
	
	case "Video_continueStory":
		sld = characterFromId("Nathaniel");
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	break;
	// <-- история Натана - видеоролики
	
	// прибытие на Доминику через телепорт
	case "Dominica_TeleportArrive":
		Dolly_TeleportConsequences();
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "Ground_sitting", "LSC_TeleportArrive_1", 3.0);
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false); // откроем дверь у Механика
		sld = characterFromId("Mechanic");
		sld.dialog.currentnode = "First time"; // patch-6
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
		LAi_LocationFightDisable(&Locations[FindLocation("Dominica_jungle_02")], true);//запретить драться
		chrDisableReloadToLocation = true;//закрыть локацию
		pchar.GenQuest.CirassExchangeDisable = true; // чтобы не снял скафандр
		LAi_LocationDisableOfficersGen("Indian_town", true); // не пускать офицеров в деревню
		LAi_LocationDisableOfficersGen("Dominica_jungle_02", true); // не пускать офицеров в локу телепорта
		for (i=1; i<=10; i++)
		{
			if (i == 1)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Dominica_Head", "canib", "man", "man", 30, PIRATE, 1, false, "native"));
				FantomMakeCoolFighter(sld, 30, 100, 100, "blade_02", "", "", 200);
				sld.dialog.Filename = "Quest\Saga\OtherNPC.c";
				sld.dialog.currentnode = "DominicaHead";	
				sld.name = "Монкитекуври";
				sld.lastname = "";
				sld.greeting = "urakan"; 
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{	
				sld = GetCharacter(NPC_GenerateCharacter("Dominica_ind_"+i, "canib_"+(rand(5)+1), "man", "man", 25, PIRATE, 1, false, "native"));
				FantomMakeCoolFighter(sld, 25, 80, 80, "blade_01", "", "", 100);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		}
		break;
		
		case "Saga_DominicaDollyReload":
			DoQuestReloadToLocation("Dominica_jungle_02", "reload", "reload2_back", "Saga_DominicaDollyGo");
		break;
		
		case "Saga_DominicaDollyGo":
			sld = characterFromId("Dominica_Head");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Dominica_jungle_02", "reload", "reload2_back");
			LAi_ActorGoToLocator(sld, "quest", "quest1", "Saga_DominicaDollyTalk", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, sld, "", -1);
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				GetCharacterPos(pchar, &locx, &locy, &locz);
				ChangeCharacterAddressGroup(sld, "Dominica_jungle_02", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
		break;
		
		case "Saga_DominicaDollyTalk":
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Dominica_Head");
			if (pchar.questTemp.Saga.BaronReturn == "third_teleport") sld.dialog.currentnode = "DominicaHead_6";
			else sld.dialog.currentnode = "DominicaHead_4";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Saga_DominicaDollyWait":
			iTemp = 8;
			if (stf(environment.time) > 9.0) iTemp = 7;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			pchar.locx = locx;
			pchar.locy = locy;
			pchar.locz = locz;
			SetLaunchFrameFormParam("Прошло "+iTemp+" часов...", "Reload_To_Location", 0.1, 5.0);
			SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
			WaitDate("", 0, 0, 0, iTemp, 0);
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			DoQuestCheckDelay("Saga_DominicaDollyTalk", 7.0);
			sld = characterFromId("Dominica_Head");
			ChangeCharacterAddressGroup(sld, "Dominica_jungle_02", "quest", "quest1");
		break;
		
		// прибытие назад к деревне мискито через телепорт
		case "Pearl_TeleportArrive":
			Dolly_TeleportConsequences();
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Ground_sitting", "LSC_TeleportArrive_1", 3.0);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			// снимаем старые запреты
			LAi_LocationDisableOfficersGen("Indian_town", false); // пускать офицеров в деревню
			LAi_LocationDisableOfficersGen("Dominica_jungle_02", false); // пускать офицеров в локу телепорта
			LAi_LocationFightDisable(&Locations[FindLocation("Indian_town")], false);//разрешить драться
			LAi_LocationFightDisable(&Locations[FindLocation("Dominica_jungle_02")], false);//разрешить драться
			// Даниэль бежит к нам
			sld = characterFromId("Danielle");
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "arrive";
			ChangeCharacterAddressGroup(sld, "Pearl_jungle_03", "item", "torch1");
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			pchar.questTemp.NotTeleportation = true; // нет телепортации более до поры
		break;
		
		case "Pearl_TeleportArrive_1":
			DeleteAttribute(pchar, "GenQuest.CannotWait");//снимаем перманентный запрет перемотки в LSC
			DeleteAttribute(pchar, "GenQuest.CirassExchangeDisable"); // кирасы можно одевать
			bDisableFastReload = false;//открыть переход
			sld = characterFromId("Danielle");
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "arrive_4";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	
//---------------------------------------нахождение в LSC--------------------------------------------------
		
		//--> прибытие через телепорт
		case "LSC_TeleportArrive":	
			Dolly_TeleportConsequences();
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;//закрыть переход
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Ground_sitting", "LSC_TeleportArrive_1", 3.0);
			if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "first_teleport")
			{
				pchar.questTemp.Saga.BaronReturn = "LSC";
				pchar.questTemp.LSC = "begin"; // флаг - мы в LSC
				bNoEatNoRats  = true; // отменяем еду и крыс
				LSC_CreateCrabGuard(); // ставим краба
				LSC_CreateStateCitizens(); // ставим горожан-статиков
				// определяем пароли кланов
				sNrvParol = UpdateLSCClanParol();
				sRvdParol = UpdateLSCClanParol(); 
				log_Testinfo(sNrvParol);
				log_Testinfo(sRvdParol);
				// ставим прерывание на вход в кладовку
				pchar.quest.LSC_entry_pantry.win_condition.l1 = "location";
				pchar.quest.LSC_entry_pantry.win_condition.l1.location = "SanAugustineResidence";
				pchar.quest.LSC_entry_pantry.function = "LSC_CreatePantryGuard";
				// ставим прерывание на вход к Мэри
				pchar.quest.LSC_findMary.win_condition.l1 = "location";
				pchar.quest.LSC_findMary.win_condition.l1.location = "CeresSmithy";
				pchar.quest.LSC_findMary.function = "LSC_FindMary";
				AddQuestRecord("BaronReturn", "5");
				//пускаем слухи
				AddSimpleRumourCityTip("Вы знаете, говорят, что наш адмирал прикончил главу нарвалов Алана Милроу. Нарвалы очень злы на пиратов после этого...", "LostShipsCity", 2, 2, "LSC", "");
				AddSimpleRumourCityTip("После трагической гибели Алана Милроу его подружка, Красная Мэри, совсем пала духом. Сидит целыми днями у себя в каюте и рыдает. Все глаза себе выплакала...", "LostShipsCity", 2, 2, "LSC", "");
				AddSimpleRumourCityTip("Недавно прикончили главу клана нарвал, прямо в тюрьме. Жуткое событие, скажу я вам. Расправа над беззащитным человеком...", "LostShipsCity", 2, 2, "LSC", "");
				AddSimpleRumourCityTip("Вот как бывает! Попал Алан адмиралу в плен, отсидел в казематах несколько месяцев - и расправились с ним без суда и следствия. А нашей чудачки Красной Мэри теперь не видно и не слышно - только целыми ночами свет в ее каюте на 'Церес Смити' горит - страдает, бедная. Совсем извелась девчонка, а такая веселая была!", "LostShipsCity", 2, 2, "LSC", "");
			}
		break;
		
		case "LSC_TeleportArrive_1":	
			LAi_ActorAnimation(Pchar, "Ground_StandUp", "pchar_back_to_player", 3.5);
		break;
		//<-- прибытие через телепорт
		
		case "LSC_CrabGuardDie": // прибили краба	
			//LAi_group_Delete("EnemyFight");
		break;
		
	// --> ---------------------здесь регистрируем обиды групп LSC на ГГ-------------------------------
		case "LSC_NarvalConflict": // конфликт с нарвалами
			if (!CheckAttribute(pchar, "GenQuest.NarvalConflict")) pchar.GenQuest.NarvalConflict = 1;
			else pchar.GenQuest.NarvalConflict = sti(pchar.GenQuest.NarvalConflict)+1;
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true);//закрыть вход к Дональду
			log_Testinfo("Конфликт с нарвалами достиг "+sti(pchar.GenQuest.NarvalConflict)+" ступени")
		break;
		
		case "LSC_RivadosConflict": // конфликт с ривадос
			if (!CheckAttribute(pchar, "GenQuest.RivadosConflict")) pchar.GenQuest.RivadosConflict = 1;
			else pchar.GenQuest.RivadosConflict = sti(pchar.GenQuest.RivadosConflict)+1;
			LocatorReloadEnterDisable("LostShipsCity_town", "reload33", true);//закрыть вход к Эдди
			log_Testinfo("Конфликт с ривадос достиг "+sti(pchar.GenQuest.RivadosConflict)+" ступени")
		break;
		
		case "LSC_SharkConflict": // конфликт с пиратами
			if (!CheckAttribute(pchar, "GenQuest.SharkConflict")) pchar.GenQuest.SharkConflict = 1;
			else pchar.GenQuest.SharkConflict = sti(pchar.GenQuest.SharkConflict)+1;
			LSC_CloseSanAvgustinDoors(); // закрыть сан-августин
			LSC_CloseTartarusDoors(); // закрыть Тартарус
			log_Testinfo("Конфликт с пиратами достиг "+sti(pchar.GenQuest.SharkConflict)+" ступени")
		break;
		
		case "LSC_CitizenConflict": // избиение горожан строго наказуемо, вплоть до геймовера
			if (!CheckAttribute(pchar, "GenQuest.CitizenConflict")) pchar.GenQuest.CitizenConflict = 1;
			else
			{
				pchar.GenQuest.CitizenConflict = sti(pchar.GenQuest.CitizenConflict)+1;
				if (sti(pchar.GenQuest.CitizenConflict) == 5)
				{
					log_Testinfo("Ты - не геймер, ты - отморозок, и место твоему ГГ в тюрьме!");
					pchar.quest.LSC_GameOverPrison.win_condition.l1 = "location";
					pchar.quest.LSC_GameOverPrison.win_condition.l1.location = "LostShipsCity_town";
					pchar.quest.LSC_GameOverPrison.function = "LSC_GameOverPrison";
				}
			}
			log_Testinfo("Конфликт с горожанами достиг "+sti(pchar.GenQuest.CitizenConflict)+" ступени");
		break;
		
		case "LSC_GameOverInPrison": // геймовер в тюрьме на Тартарусе
			RemoveAllCharacterItems(pchar, true);
			DoQuestCheckDelay("LSC_GameOverPrisonEnd", 7.0);
			log_Testinfo("Довыделывался?");
		break;
		
		case "LSC_GameOverPrisonEnd": // геймовер в тюрьме на Тартарусе
			GameOver("mutiny");
		break;
		// <-- обиды групп LSC на ГГ
		
	// ---------------------------- прочие функции, не относящиеся к квестам ---------------------------
		
		case "LSC_DrinkSit": // бухалово в одиночку в таверне
			LAi_SetSitType(pchar);
			DoQuestCheckDelay("LSC_DrinkSitGo", 0.6);
        break;
		
		case "LSC_DrinkSitGo": 
			SetMusic("spa_music_tavern");
			AddMoneyToCharacter(pchar, -300);
			DoQuestCheckDelay("LSC_DrinkSitExit", 16.0);
		break;
		
		case "LSC_DrinkSitExit": 
			int iAddTime = 20-sti(environment.time);
			StoreDayUpdate();
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			LAi_SetPlayerType(pchar);
			sld = ItemsFromID("potionrum");
			sld.shown = false;
			DoQuestReloadToLocation("FleuronTavern", "goto", "goto1", "");
		break;
		// <-- прочие функции, не относящиеся к квестам
		
	//-------------------------------- охота на Акулу - вариант R -----------------------------------
		case "LSC_ChadGuardAttack_Fail": //атака не по сюжету, либо если завалил колдуна
			for(i = 1; i <= 3; i++)
			{				
				sld = CharacterFromID("ChadGuard_"+i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetHP(sld, 3000, 3000);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, true); // ГГ - однозначный капут
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "goto", "goto8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		
		case "LSC_Chimiset_ActivateDialog":	// активация диалога при нападении на колдуна
			DoQuestCheckDelay("hide_weapon", 0.1);
			sld = characterFromId("Chimiset");
			LAi_RemoveCheckMinHP(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "LSC_ChadGuard_Die": // перебили охрану Чада и его самого
			InterfaceStates.Buttons.Save.enable = true; //разрешим сохраняться
			DoQuestCheckDelay("hide_weapon", 1.0);//убрать оружие
			LAi_group_Delete("EnemyFight");
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "Chad_die";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "LSC_EddyStay": // вертаем Эдди возможность разговора
			chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Eddy");
			sld.dialog.currentnode = "Total_info";
			LAi_SetOwnerType(sld);
		break;
		
		case "LSC_AdolfDie": // прибили Адольфа
			DoQuestCheckDelay("hide_weapon", 1.0);//убрать оружие
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			pchar.quest.LSC_AdolfDie.win_condition.l1 = "item";
			pchar.quest.LSC_AdolfDie.win_condition.l1.item = "letter_chad";
			pchar.quest.LSC_AdolfDie.function = "LSC_AdolfLetter";
			AddQuestRecord("SharkHunt", "15");
			AddSimpleRumourCityTip("Говорят, Адольф Барбье внезапно исчез. Да, не доводят людей до добра легкие деньги...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("А вы не знаете, куда подевался Адольф Барбье? Купил себе каюту, только-только деньгами разжился - и пропал...", "LostShipsCity", 5, 2, "LSC", "");
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LSC_CyclopNMaryDie": // убили Мэри и Циклопа
			DoQuestCheckDelay("hide_weapon", 1.0);//убрать оружие
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			LAi_group_Delete("EnemyFight");
			pchar.quest.LSC_MaryDie.win_condition.l1 = "item";
			pchar.quest.LSC_MaryDie.win_condition.l1.item = "letter_chad_1";
			pchar.quest.LSC_MaryDie.function = "LSC_MaryLetter";
			AddQuestRecord("SharkHunt", "17");
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
	
		case "LSC_EnterAevaWithMary": // следуем за Мэри на Эву
			DoQuestReloadToLocation("AvaShipInside3", "reload", "reload1", "LSC_AevaWithMary");
		break;
		
		case "LSC_AevaWithMary": // внутри Эвы
			iRank = 30+MOD_SKILL_ENEMY_RATE;
			iScl = 80;
			// нарвалы
			for (i=1; i<=3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("CyclopGuard_"+i, "citiz_58", "man", "man", iRank, PIRATE, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl*2+100);
				sld.cirassId = Items_FindItemIdx("cirass1");
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "AvaShipInside3", "quest", "quest"+i);
				LAi_CharacterDisableDialog(sld);
			}
			// Марчелло
			sld = characterFromId("Marchello");
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol6", "bullet", iScl*2+100);
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "AvaShipInside3", "quest", "quest4");
			LAi_SetActorType(sld);
			// идем в ловушку
			sld = characterFromId("Mary");
			ChangeCharacterAddressGroup(sld, "AvaShipInside3", "reload", "reload1");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "LSC_AevaMaryDialog", -1);
			LAi_ActorFollow(pchar, sld, "", -1);
		break;
		
		case "LSC_AevaMaryDialog": // пришли в трюм
			LAi_SetPlayerType(pchar);
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("CyclopGuard_"+i);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			sld = characterFromId("Marchello");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "Town_4";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	
	//--------------------------------охота на Акулу - вар N ---------------------------------------
		case "LSC_SharkDie": // убили Акулу - ставим Декстера
			sld = characterFromId("Dodson");
			sld.lifeday = 0;
			pchar.questTemp.Saga.DodsonDie = "true"; // атрибут Саге что Акула погиб
			sld = characterFromId("Dexter");
			sld.dialog.currentnode = "admiral";
			sld.greeting = "dexter_2";
			ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "sit", "sit1");
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, "LSC_SHARK");
			SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
			LocatorReloadEnterDisable("LostShipsCity_town", "reload25", true);
		break;
		
		case "LSC_CarolineOpen": // открываем Каролину
			LocatorReloadEnterDisable("LostShipsCity_town", "reload25", false);
			pchar.quest.LSC_CarolineEnter.win_condition.l1 = "location";
			pchar.quest.LSC_CarolineEnter.win_condition.l1.location = "CarolineBank";
			pchar.quest.LSC_CarolineEnter.function = "LSC_CarolineEnter";
		break;
		
		case "LSC_MarynChadDie": // прибили Мэри и Чада - ищем Акулу
			LAi_group_Delete("EnemyFight");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			sld = characterFromId("Dodson");
			if (LAi_GetCharacterHP(sld) > 0) // жив
			{
				LAi_SetActorType(sld);
				sld.dialog.currentnode = "caroline_5";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
				AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			}
			else
			{
				chrDisableReloadToLocation = false;//открыть локацию
				DoQuestCheckDelay("LSC_SharkDie", 1.0);
				AddQuestRecord("SharkHunt", "23");
			}
			AddComplexSelfExpToScill(150, 150, 150, 150);
		break;
		
		case "LSC_SharkReturnSit": // Акулу на свое место
			chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Dodson");
			LAi_SetHuberType(sld);
			sld.dialog.currentnode = "Total_wait";
			ref rloc = &Locations[FindLocation("CarolineBank")];
			rloc.private1.key = "key_facio";
			rloc.private1.key.delItem = true;
			// ставим прерывание на письмо Фацио
			pchar.quest.LSC_letterFacio.win_condition.l1 = "item";
			pchar.quest.LSC_letterFacio.win_condition.l1.item = "letter_chad_1";
			pchar.quest.LSC_letterFacio.function = "LSC_FindLetterFacio";
			AddSimpleRumourCityTip("Странные вещи у нас творятся. Вслед за Чадом Каппером исчезла эта сорвиголова Красная Мэри. Уверен, это происки ривадос, мстящих за своего колдуна...", "LostShipsCity", 2, 2, "LSC", "");
			AddSimpleRumourCityTip("Теперь еще и Красная Мэри пропала. Ни слуху, ни духу. Скорее всего, она уже мертва. Вот что значит - разозлить ривадос! Уверен, исчезновение Чада и Мэри - их рук дело.", "LostShipsCity", 2, 2, "LSC", "");
			AddSimpleRumourCityTip("Говорят, прошлой ночью на 'Каролине' слышали какой-то шум, словно шла отчаянная драка, и предсмертный женский вопль. Думаю, это объясняет исчезновение Мэри Каспер. Бедная девушка! Уверен, больше мы ее не увидим...", "LostShipsCity", 1, 2, "LSC", "");
		break;
		
	//-------------------------------- охота на Акулу - вариант M -----------------------------------
		case "LSC_EnemiesMaryDie": // перебили негодяев на церес смити - ищем Мэри
			DoQuestCheckDelay("hide_weapon", 1.0);//убрать оружие
			LAi_group_Delete("EnemyFight");
			PlayStereoOGG("music_LostShipsCity");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			sld = characterFromId("Mary");
			if (LAi_GetCharacterHP(sld) > 0) // жива
			{
				LAi_SetActorType(sld);
				sld.dialog.currentnode = "mary";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
				pchar.questTemp.LSC.Mary = "alive"; // Мэри найдена и жива - теперь она наша! Почти...
				AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
				AddCharacterExpToSkill(pchar, "Leadership", 100);
			}
			else
			{
				LAi_group_Delete("TMP_FRIEND"); // опаньки! если не потереть группу - то имеем вылет!
				pchar.quest.LSC_Maryletter.win_condition.l1 = "item";
				pchar.quest.LSC_Maryletter.win_condition.l1.item = "letter_chad_1";
				pchar.quest.LSC_Maryletter.function = "LSC_DieMaryletter";
				AddQuestRecord("SharkHunt", "29");
				pchar.questTemp.LSC.Mary = "die"; // Мэри мертва
			}
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LSC_ZikomoNearDoor": // Зикомо у дверей
			sld = CharacterFromID("Zikomo");
            LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "LSC_ZikomoTurn", -1);
			DoQuestCheckDelay("LSC_RivadosPrisonAttack", 12.0);
        break;
		
		case "LSC_ZikomoTurn": // поворот Зикомо
			sld = CharacterFromID("Zikomo");
            LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
        break;
		
		case "LSC_ChimisetSit": // усадка Чимисета
			sld = CharacterFromID("Chimiset");
            LAi_SetHuberType(sld);
			sld.dialog.currentnode = "freedom";
        break;
		
		case "LSC_RivadosPrisonAttack": // мотаем время
			SetLaunchFrameFormParam("Прошло три часа...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 3, 10); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("LSC_RivadosFreeChimiset", 5.0);
        break;
		
		case "LSC_RivadosFreeChimiset": // ривадос вернулись с Чимисетом
			sld = CharacterFromID("Zikomo"); // Зикомо на место
            LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto4", "LSC_ZikomoTurn", 10.0);
			sld = CharacterFromID("Chimiset"); // Чимисета на стул
            LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "ProtectorFisher", "reload", "reload1");
			LAi_ActorGoToLocator(sld, "sit", "sit1", "LSC_ChimisetSit", 10.0);
			sld = CharacterFromID("Eddy"); // Эдди к разговору
            LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "ProtectorFisher", "reload", "reload1");
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
        break;
		
		case "LSC_AdolfKillerDie": // прибили нарвала на Флорентине
			DoQuestCheckDelay("hide_weapon", 1.0);//убрать оружие
			LAi_group_Delete("EnemyFight");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			pchar.quest.LSC_letterAdolf.win_condition.l1 = "item";
			pchar.quest.LSC_letterAdolf.win_condition.l1.item = "letter_chad";
			pchar.quest.LSC_letterAdolf.function = "LSC_letterAdolf_SF";
			AddComplexSelfExpToScill(70, 70, 70, 70);
        break;
		
		case "LSC_CapperDieAeva": // Каппер капут на Эве
			DoQuestCheckDelay("hide_weapon", 1.0);//убрать оружие
			LAi_group_Delete("EnemyFight");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			pchar.questTemp.LSC.CapperDie_Aeva = "true"; // атрибут - Каппер уничтожен
			LSC_OpenTartarusDoors(); // открыть Тартарус
			if (!CheckAttribute(pchar, "questTemp.LSC.Dodson_poison")) // не было разговора
			{
				sld = CharacterFromID("Dodson");
				sld.dialog.currentnode = "poison";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Whiskey_clear")) // виски не отравлен
			{
				AddQuestRecord("SharkHunt", "44");
				sld = CharacterFromID("Dodson");
				sld.dialog.currentnode = "clear"; // ноду Акуле
			}
			else
			{
				chrDisableReloadToLocation = false;
				if (CheckAttribute(pchar, "questTemp.LSC.Dodson_poison"))
				{
					AddQuestRecord("SharkHunt", "39_1");
						sld = CharacterFromID("Facio");
					sld.greeting = "facio_2";
						sld.dialog.currentnode = "whiskey";
					sld.quest.poisonnode = 1;
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.LSC.Dodson_warning"))
					{ // Акула был предупрежден - снова к нему
						AddQuestRecord("SharkHunt", "39_2");
						sld = CharacterFromID("Facio");
						LAi_SetStayType(sld);
						sld.dialog.currentnode = "whiskey";
						sld.greeting = "facio_2";
						sld.quest.poisonnode = 3;
						LAi_CharacterDisableDialog(sld);//запрещаем диалог
						ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto10");
						sld = CharacterFromID("Dodson");
						sld.dialog.currentnode = "whiskey_7";
						LAi_CharacterEnableDialog(sld);
					}
					else AddQuestRecord("SharkHunt", "39");
				}
			}
			AddComplexSelfExpToScill(200, 200, 200, 200);
        break;
		
		case "LSC_CyclopInMaryCabin": // у Мэри - спасаем ее от Циклопа
			iRank = 25+MOD_SKILL_ENEMY_RATE*2;
			iScl = 80;
			DeleteAttribute(pchar, "questTemp.LSC.RescueMary");
			DeleteAttribute(pchar, "questTemp.NoFast"); // убираем запрет ускорения
			// Мэри
			sld = CharacterFromID("Mary");
			sld.greeting = "mary_2"; 
			if (!CheckAttribute(pchar, "questTemp.LSC.FailMary")) // успел
			{
				ChangeCharacterAddressGroup(sld, "CeresSmithy", "sit", "sit3");
				LAi_SetSitType(sld);
				LAi_CharacterDisableDialog(sld);//запрет диалога
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
			}
			else
			{
				LAi_KillCharacter(sld);
			}
			// ставим Циклопуса и утолщаем его
			sld = characterFromId("Marchello");
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl+100);
				sld.cirassId = Items_FindItemIdx("cirass1");
			sld.MultiFighter = 1.4;
			if (MOD_SKILL_ENEMY_RATE > 7) sld.MultiFighter = 1.8; // мультифайтер
			SetSelfSkill(sld, iScl, iScl, iScl, iScl, iScl);
			if (!CheckAttribute(pchar, "questTemp.LSC.FailMary")) // успел
			{
				sld.dialog.currentnode = "mary";
				ChangeCharacterAddressGroup(sld, "CeresSmithy", "quest", "quest2"); // затаился, гад
				LAi_SetCheckMinHP(sld, 100, true, "LSC_MaryRunHelp_CS");
				LAi_SetActorType(sld);
				LAi_SetActorType(pchar);
				LAi_ActorGoToLocator(pchar, "goto", "goto3", "LSC_CyclopDiag_CS", -1);
			}
			else
			{
				ChangeCharacterAddressGroup(sld, "CeresSmithy", "goto", "goto10");
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "LSC_KillCyclop_CS");
			}
        break;
		
		case "LSC_CyclopDiag_CS": // нашли Циклопа
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Marchello");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
        break;
		
		case "LSC_MaryRunHelp_CS": // Мэри вступает в драку - помогает
			sld = CharacterFromID("Mary");
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "CeresSmithy", "barmen", "stay");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER); // в нашу группу
			sld = CharacterFromID("Marchello");
			LAi_SetImmortal(sld, false);
        break;
		
		case "LSC_KillCyclop_CS": // одолели Циклопа
			DoQuestCheckDelay("hide_weapon", 1.0);//убрать оружие
			LAi_group_Delete("EnemyFight");
			PlayStereoOGG("music_LostShipsCity");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			pchar.questTemp.LSC.CyclopDie = "true";
			if (!CheckAttribute(pchar, "questTemp.LSC.FailMary")) // успел
			{
				sld = characterFromId("Mary");
				if (LAi_GetCharacterHP(sld) > 0) // жива
				{
					LAi_CharacterEnableDialog(sld);//разрешение диалога
					sld.dialog.currentnode = "happy";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0); // Мэри жива - теперь она наша! Совсем!
					AddCharacterExpToSkill(pchar, "Leadership", 500);
					AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
				}
				else
				{
					AddQuestRecord("SharkHunt", "48");
					pchar.questTemp.LSC.Mary = "die"; // Мэри мертва - но такое навряд ли получится
					pchar.quest.LSC_marydienextstage.win_condition.l1 = "location";
					pchar.quest.LSC_marydienextstage.win_condition.l1.location = "LostShipsCity_town";
					pchar.quest.LSC_marydienextstage.win_condition = "LSC_MarydieNextstage";
				}
			}
			else
			{
				AddQuestRecord("SharkHunt", "50");
				pchar.questTemp.LSC.Mary = "die"; // Мэри мертва 
				pchar.quest.LSC_marydienextstage.win_condition.l1 = "location";
				pchar.quest.LSC_marydienextstage.win_condition.l1.location = "LostShipsCity_town";
				pchar.quest.LSC_marydienextstage.win_condition = "LSC_MarydieNextstage";
			}
			AddComplexSelfExpToScill(150, 150, 150, 150);
        break;
		
		case "LSC_MarydieNextstage": 
			DoQuestCheckDelay("LSC_MarydieNextstageFrame", 2.0);
        break;
		
		case "LSC_MarydieNextstageFrame": 
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Следующим утром...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("LSC_MarydieNextstageReload", 4.0);
        break;
		
		case "LSC_MarydieNextstageReload": 
			LSC_ContinueAfterMaryCabin(); // завершающая функция
			DoQuestReloadToLocation("LostShipsCity_town", "goto", "goto09_4", "");
        break;
		
		case "LSC_MaryRomantic_1": // кино романтик-с...
			pchar.GenQuest.FrameLockEsc = true;
			pchar.GenQuest.MusicContinue = true;
			SetLaunchFrameFormParam("", "", 0, 7);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 3, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "CeresSmithy", "goto", "goto11");
			ChangeCharacterAddressGroup(pchar, "CeresSmithy", "goto", "goto10");
			DoQuestCheckDelay("LSC_MaryRomantic_2", 7.0);
        break;
		
		case "LSC_MaryRomantic_2": // второй эпизод...
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 700);
			DoQuestCheckDelay("LSC_MaryRomantic_3", 15.0);
        break;
		
		case "LSC_MaryRomantic_3": // третий... Теперь ГГ как честный человек обязан жениться
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("", "", 0, 14);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex6.wav");
            LaunchFrameForm();
			DoQuestCheckDelay("LSC_MaryRomantic_4", 14.0);
			AddCharacterHealth(pchar, 12); // Мэри восстанавливает здоровье лучше всех и без бальзама
			LAi_SetCurHPMax(pchar);
        break;
		
		case "LSC_MaryRomantic_4": // четвертый...
			locCameraResetState();
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "happy_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;
		
		case "LSC_MaryRomantic_5": // пятый - на улицы
			// здесь снять все установленные запреты
			bDisableCharacterMenu = false;//лоченые интерфейсы
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			LSC_ContinueAfterMaryCabin(); // завершающая функция
			DoQuestReloadToLocation("LostShipsCity_town", "goto", "goto09_4", "LSC_MaryReturnNormal");
			AddQuestRecord("SharkHunt", "47");
        break;
		
		case "LSC_MaryReturnNormal": // вертаем Мэри в норму
			sld = characterFromId("Mary");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) sld.dialog.currentnode = "LSC_love";
			else sld.dialog.currentnode = "LSC_love_3";
			LAi_SetOwnerType(sld);
			chrDisableReloadToLocation = false;//открыть локацию 
        break;
		
		case "LSC_MaryReturnNormal_1": // вертаем Мэри в норму
			sld = characterFromId("Mary");
			LAi_SetOwnerType(sld);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) LAi_SetOfficerType(sld); // patch-10
        break;
		
		case "LSC_CyclopDie_Fl": // одолели Циклопа на Флероне
			DoQuestCheckDelay("hide_weapon", 1.0);//убрать оружие
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			LAi_group_Delete("EnemyFight");
			PlayStereoOGG("music_LostShipsCity");
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("SharkHunt", "52");
			pchar.questTemp.LSC.CyclopDie = "true";
			if (!CheckAttribute(pchar, "questTemp.LSC.Whiskey_clear"))
			{
				pchar.quest.LSC_WhiskeyStoryFinal.win_condition.l1 = "Timer";
				pchar.quest.LSC_WhiskeyStoryFinal.win_condition.l1.date.hour  = 6;
				pchar.quest.LSC_WhiskeyStoryFinal.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
				pchar.quest.LSC_WhiskeyStoryFinal.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.LSC_WhiskeyStoryFinal.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
				pchar.quest.LSC_WhiskeyStoryFinal.win_condition.l2 = "location";
				pchar.quest.LSC_WhiskeyStoryFinal.win_condition.l2.location = "LostShipsCity_town";
				pchar.quest.LSC_WhiskeyStoryFinal.function = "LSC_WhiskeyStoryFinal";
			}
			AddComplexSelfExpToScill(150, 150, 150, 150);
			pchar.questTemp.Saga.SharkHunt = "whiskey_final"; // меняем флаг
			sld = CharacterFromID("Facio");
			sld.dialog.currentnode = "First time";
			sld.greeting = "facio_1";
		 break;
		
		case "LSC_MaryTavern":
			LAi_SetSitType(pchar);
			sld = characterFromId("Mary");
			ChangeCharacterAddressGroup(sld, "FleuronTavern", "quest", "sit1");
			LAi_SetSitType(sld);
			DoQuestFunctionDelay("LSC_MaryTavern", 0.6);
        break;
		
		case "LSC_MaryTavernReturn":
			LSC_MaryLoveWaitTime();
			DoQuestReloadToLocation("CeresSmithy", "goto", "goto10", "LSC_MaryTavernReturn_1");
        break;
		
		case "LSC_MaryTavernReturn_1":
			sld = characterFromId("Mary");
			LAi_SetOwnerType(sld);
			LAi_SetPlayerType(pchar);
			ChangeCharacterAddressGroup(sld, "CeresSmithy", "goto", "goto11");
			ChangeCharacterAddressGroup(pchar, "CeresSmithy", "goto", "goto10");
			AddCharacterHealth(pchar, 5); // ночь бухали - восстановление меньше
			LAi_SetCurHPMax(pchar);
			DoQuestFunctionDelay("LSC_MaryLoveMorning", 1.0);
			sld = ItemsFromID("potionrum");
			sld.shown = false;
        break;
		
		 case "LSC_EnterPresentMary": // входим с Мэри в каюту Юргену
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_3";
			ChangeCharacterAddressGroup(sld, "CeresSmithy", "goto", "goto12");
			DoQuestReloadToLocation("CeresSmithy", "reload", "reload1", "LSC_PresentMary");
        break;
		 
		 case "LSC_PresentMary": // в каюте Юргена
			StartQuestMovie(true, true, true);
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Schmidt");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromID("Mary"));
			sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
        break;
		
	// ---------------------------------- возвращение на Остров ------------------------------------
		case "LSC_SetOlePassenger": // Оле - в пассажиры
			sld = characterFromId("Ole");
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			pchar.GenQuest.Ole = true; // аналог крысобога
			SaveCurrentNpcQuestDateParam(sld, "pearl_date");
			sld.quest.pearlqty = 0; // счет жемчужин
			if (GetCharacterIndex("Mary") != -1) // Мэри
			{
				sld = characterFromId("Mary");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else // иначе завершение
			{
				chrDisableReloadToLocation = false;
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			}
        break;
		
		 case "LSC_MaryWaitInCabin": // Мэри ждет
			sld = characterFromId("Mary");
			LAi_SetOwnerType(sld);
			sld.dialog.currentnode = "adversary"; 
			// до сдачи Даниэль Натаниэлю - закрываем вход к Мэри
			for (i=0; i<=3; i++)
			{
				LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, true);
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
        break;
		
		case "LSC_DanielleRomantic": // Даниэль и Натаниэль
			pchar.GenQuest.FrameLockEsc = true;
			pchar.GenQuest.MusicContinue = true;
			SetLaunchFrameFormParam("", "", 0, 8);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("LSC_DanielleRomantic_1", 8.0);
        break;
		
		case "LSC_DanielleRomantic_1": // второй эпизод...
			LocCameraResetState();
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_8";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;
		
		case "LSC_LastNight_CS": // последняя ночь на Церес Смити
			LAi_SetPlayerType(pchar);
			LSC_MaryLove();
        break;
		
		case "LSC_Mary_hire": //найм Мэри: в отличие от всех прочих, ее HP будет подбираться автолевеллингом
			pchar.questTemp.LSC.Mary_officer = "true";
			iTemp = 250+sti(pchar.rank)*5;
			sld = characterFromId("Mary");
			LAi_SetHP(sld, iTemp, iTemp); 
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.CompanionDisable = true; //Мэри подруга, а не компаньон
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			DeleteAttribute(sld, "SaveItemsForDead"); // а вот сохранение вещей - фигушки, потеряете Мэри - нифига не получите
			sld.HoldEquip = true; //не отдавать оружие
			sld.location = "none";
			LAi_SetOfficerType(sld);
			sld.dialog.currentnode = "Mary_officer";
			sld.greeting = "mary_hire"; 
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			// Мэри упакована сама по-полной
			TakeNItems(sld, "potion2", 8);
			TakeNItems(sld, "potion3", 3);
			TakeNItems(sld, "potion4", 3);
			EquipOfficerByArtefact(sld, "indian_7");
			if (CheckAttribute(sld, "quest.blade31"))
			{
				EquipOfficerByArtefact(sld, "indian_3");
				EquipOfficerByArtefact(sld, "indian_4");
			}
			else
			{
				EquipOfficerByArtefact(sld, "indian_1");
				EquipOfficerByArtefact(sld, "amulet_4");
			}
			// активируем поведение Мэри
			// если две недели не заниматься с ней любовью - будет требовать
			pchar.quest.Mary_giveme_sex.win_condition.l1 = "Timer";
			pchar.quest.Mary_giveme_sex.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Mary_giveme_sex.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.Mary_giveme_sex.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.Mary_giveme_sex.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.Mary_giveme_sex.function = "Mary_GiveMeSex";
			pchar.GenQuest.BrothelCount = 0; // нулим бордельный счетчик
			RemoveItems(pchar, "key_mary", 1); // удалить ключ Мэри - он уже не нужен
        break;
		
		case "LSC_SetDodsonPassenger": // Акулу - в пассажиры
			sld = characterFromId("Dodson");
			sld.greeting = "dodson_2"; 
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_SetImmortal(sld, true);
			chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Svenson");
			sld.quest.shark = "true";
			pchar.quest.LSC_Dodson_SC.win_condition.l1 = "location";
			pchar.quest.LSC_Dodson_SC.win_condition.l1.location = "SantaCatalina_town";
			pchar.quest.LSC_Dodson_SC.function = "LSC_DodsonSC";
        break;
		
		case "LSC_FinalDiosStory": // Диос - завершение рассказа 270912
			sld = characterFromId("Dios");
			sld.dialog.currentnode = "LSC_4";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
        break;
		
	// --------------------------------------мини-квесты LSC -----------------------------------------
		// --> пей до дна
		case "LSC_DrinkLeonardTalk": // Леонард подходит
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = characterFromId("LSC_Leonard");
			LAi_RemoveLoginTime(sld);
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;
		
		case "LSC_DrinkGotoCarolina": // выводим на улицы
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload39", "LSC_DrinkGotoCarolina_1");
        break;
		
		case "LSC_DrinkGotoCarolina_1": // идем к 'Каролине'
			chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("LSC_Leonard");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload24", "LSC_DrinkGotoCarolina_2", -1);
			LAi_SetImmortal(sld, true);
			pchar.quest.LSC_Drink1.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink1.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.LSC_Drink1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink1.function = "LSC_DrinkDelete";
        break;
		
		case "LSC_DrinkGotoCarolina_2": // стоит, ждет
			sld = characterFromId("LSC_Leonard");
			LAi_SetStayType(sld);
        break;
		
		case "LSC_DrinkGotoCarolina_3": // телепорт внутрь каролины
			DoQuestReloadToLocation("CarolineBank", "reload", "reload3", "pchar_back_to_player");
			chrDisableReloadToLocation = true;
			// считаем деньги и дублоны ГГ
			pchar.questTemp.LSC.Drink.Money = sti(pchar.money);
			pchar.questTemp.LSC.Drink.Dublon = GetCharacterItem(pchar, "gold_dublon");
        break;
		
		case "LSC_DrinkInCarolina": // внутри каролины
			chrDisableReloadToLocation = false;
			pchar.questTemp.LSC.Drink = "grabbing";
			LocatorReloadEnterDisable("CarolineBank", "reload1", true); // на галерею
			pchar.quest.LSC_Drink2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_Drink2.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_Drink2.win_condition = "LSC_DrinkLeonardTalk";
        break;
		
		case "LSC_DrinkClear": // вертаем всех на места через три часа
			chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("LSC_Leonard");
			LAi_SetImmortal(sld, false);
			pchar.quest.LSC_Drink3.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink3.win_condition.l1.date.hour  = sti(GetTime()+3);
			pchar.quest.LSC_Drink3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink3.function = "LSC_DrinkDelete";
        break;
	// <-- пей до дна
	
	// --> тайна Санта-Люсии
		case "LSC_RingTalkLook": // смотрим на кольцо
			LAi_SetPlayerType(pchar);
			LSC_RingRishardTalk("ring_13");
        break;
		
		case "LSC_RingEnterInside": // входим в трюм разбитого корабля
			chrDisableReloadToLocation = true;//закрыть локацию
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			// ставим крабикусов
			iRank = 25+MOD_SKILL_ENEMY_RATE*2;
			iTemp = 150+MOD_SKILL_ENEMY_RATE*30+sti(pchar.rank)*5;
			LAi_group_Register("EnemyCrab");
			for (i=1; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("CrabInside_"+i, "crabBig", "crab", "crabBig", iRank, PIRATE, -1, false, "quest"));
				sld.name = "Гигантский краб";
				sld.lastname = "";
				GiveItem2Character(sld, "unarmed");
				EquipCharacterbyItem(sld, "unarmed");
				if (MOD_SKILL_ENEMY_RATE > 4) sld.MultiFighter = stf(MOD_SKILL_ENEMY_RATE/2.5);
				sld.SaveItemsForDead = true;
				sld.animal = true;
				LAi_SetHP(sld, iTemp, iTemp);
				SetCharacterPerk(sld, "BasicDefense");
				SetCharacterPerk(sld, "AdvancedDefense");
				SetCharacterPerk(sld, "CriticalHit");
				LAi_SetWarriorType(sld);
				if (bPincers()) TakeNItems(sld, "crab_pincers", 2); // клешни
				ChangeCharacterAddressGroup(sld, "ExternalRingInside", "goto", "goto"+i);
				LAi_warrior_SetStay(sld, true);
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyCrab");
			}
			LAi_group_SetRelation("EnemyCrab", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetLookRadius("EnemyCrab", 13.0);
			LAi_group_SetHearRadius("EnemyCrab", 5.0);
			LAi_group_SetSayRadius("EnemyCrab", 8.0);
			LAi_group_SetCheck("EnemyCrab", "LSC_RingInsideCrabsDead");
			LAi_SetFightMode(pchar, true);
        break;
		
		case "LSC_RingInsideCrabsDead": // перебили крабов
			PlayStereoOGG("music_LostShipsCity");
			LAi_group_Delete("EnemyCrab");
			sld = characterFromId("LSC_Rishard");
			ChangeCharacterAddressGroup(sld, "ExternalRingInside", "reload", "reload1");
			LSC_RingRishardTalk("ring_15");
			AddComplexSelfExpToScill(150, 150, 150, 150);
        break;
		
		case "LSC_RingDialog": // активатор диалогов
			sld = characterFromId("LSC_Rishard");
			LSC_RingRishardTalk(sld.quest.diagnode);
        break;
		
		case "LSC_RingEnterDeck": // входим на палубу разбитого корабля
			chrDisableReloadToLocation = true;//закрыть локацию
			// ставим крабикусов
			iRank = 25+MOD_SKILL_ENEMY_RATE*2;
			iTemp = 150+MOD_SKILL_ENEMY_RATE*30+sti(pchar.rank)*5;
			for (i=1; i<=6; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("CrabDeck_"+i, "crabBig", "crab", "crabBig", iRank, PIRATE, -1, false, "quest"));
				sld.name = "Гигантский краб";
				sld.lastname = "";
				GiveItem2Character(sld, "unarmed");
				EquipCharacterbyItem(sld, "unarmed");
				if (MOD_SKILL_ENEMY_RATE > 2) sld.MultiFighter = stf(MOD_SKILL_ENEMY_RATE/2.5);
				sld.SaveItemsForDead = true;
				sld.animal = true;
				LAi_SetHP(sld, iTemp, iTemp);
				SetCharacterPerk(sld, "BasicDefense");
				SetCharacterPerk(sld, "AdvancedDefense");
				SetCharacterPerk(sld, "CriticalHit");
				ChangeCharacterAddressGroup(sld, "ExternalRingDeck", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyCrab");
			}
			LAi_group_SetRelation("EnemyCrab", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetLookRadius("EnemyCrab", 15.0);
			LAi_group_SetHearRadius("EnemyCrab", 6.0);
			LAi_group_SetSayRadius("EnemyCrab", 12.0);
			LAi_group_SetCheck("EnemyCrab", "LSC_RingDeckCrabsDead");
			LSC_RingRishardTalk("ring_22");
        break;
		
		case "LSC_RingDeckCrabsDead": // перебили крабов
			PlayStereoOGG("music_LostShipsCity");
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", true);
			LAi_group_Delete("EnemyCrab");
			LSC_RingRishardTalk("ring_24");
			AddComplexSelfExpToScill(150, 150, 150, 150);
        break;
		
		case "LSC_RingEnterCabin": // вошли в каюту
			chrDisableReloadToLocation = true;
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_31";
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto1", "LSC_RingDialog", -1);
        break;
		
		case "LSC_RingSetToBarman": // 
			sld = characterFromId("LSC_Rishard");
			LAi_SetBarmanType(sld);
        break;
		
		case "LSC_RingFinalStage": // 
			sld = characterFromId("LSC_Rishard");
			sld.quest.ring_final = true;
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, false);
			LAi_ActorRunToLocator(sld, "reload", "reload1", "", 7.0);
			DoQuestFunctionDelay("LSC_RingOver", 7.0); // закрываем квест
			SetFunctionTimerCondition("LSC_RingDeleteItemsBoxes", 0, 0, 2, false); // через 2 дня боксы опустеют
        break;
		
		case "LSC_RingFindGold": // нашли золото 
			PlaySound("Ambient\LAND\door_001.wav");
			PlaySound("Ambient\LAND\door_004.wav");
			PlaySound("Types\warrior03.wav");
			PlaySound("Types\warrior04.wav");
			SetLaunchFrameFormParam("Вы отыскали нужный ящик"+ NewStr() +"Золото капитана 'Санта-Люсии' найдено!", "", 0, 6);//табличка
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_46";
			DoQuestCheckDelay("LSC_RingDialog", 6.0);
        break;
		// <-- тайна Санта-Люсии
		// <-- нахождение в LSC
	
	//-------------------------------------- искушение Барбазона--------------------------------------
		case "Saga_ValetDie": // прибили Валета
			LAi_group_Delete("EnemyFight");
			pchar.quest.Saga_Valet_letter.win_condition.l1 = "item";
			pchar.quest.Saga_Valet_letter.win_condition.l1.item = "letter_chad";
			pchar.quest.Saga_Valet_letter.function = "Saga_FindValetLetter";
			pchar.questTemp.Saga.BarbTemptation = "marlin";
			AddComplexSelfExpToScill(100, 100, 100, 100);
        break;
		
		case "Saga_VensanTrapDestroyed": // изничтожили засаду на Терксе
			chrDisableReloadToLocation = false;
			LAi_group_Delete("EnemyFight");
			pchar.questTemp.Saga.BarbTemptation.Vensan_canfree = "true"; // можно говорить с венсаном
			pchar.quest.Saga_Vensan_brigantine.win_condition.l1 = "location";
			pchar.quest.Saga_Vensan_brigantine.win_condition.l1.location = "Terks";
			pchar.quest.Saga_Vensan_brigantine.function = "Saga_CreateVensanEnemyes";
			AddQuestRecord("BarbTemptation", "13");
			AddComplexSelfExpToScill(100, 100, 100, 100);
        break;
		
		case "Saga_DannyHurryHelp": // Даниэль помогает
			sld = characterFromId("Danielle");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetHP(sld, 500, 500); // увеличиваем ей НР
			sld.cirassId = Items_FindItemIdx("cirass1");
			TakeNItems(sld, "potion2", 5);
			LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
			sld = characterFromId("Saga_JackmanCabinHelper");
			LAi_SetImmortal(sld, false);
        break;
		
		case "Saga_AfterJackmanBoarding": // прибили Джекмана
			pchar.questTemp.Saga.BarbTemptation = "after_boarding"; // меняем флаг
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "after_boarding";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindNearestFreeLocator("loc", locx, locy, locz));
			pchar.GenQuest.CannotReloadBoarding = true; // нельзя перегружаться
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			AddComplexSelfExpToScill(150, 150, 150, 150);
			AddComplexSeaExpToScill(220, 220, 220, 220, 220, 220, 0);
        break;
		
		case "Saga_StormingGroupTurn": // поворот матросов
			for (i=1; i<=5; i++)
			{
				sld = characterFromId("Saga_SGM_"+i);
				LAi_SetActorType(sld);
				LAi_ActorTurnToLocator(sld, "reload", "reload6");
			}
        break;
		// <-- искушение Барбазона
		
	//---------------------------------------Тени прошлого-------------------------------------------
		case "Saga_FinalLedbitterStory": // завершение рассказа
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sld = characterFromId("Dodson");
			else sld = characterFromId("Terrax");
			sld.dialog.currentnode = "shadows_6";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
        break;
		
		case "Return_HelenaOfficer":
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "helena_officer";
			LAi_SetOfficerType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        break;
		
		case "Return_MaryOfficer":
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "mary_officer";
			LAi_SetOfficerType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        break;
		
	// бой с Джессикой
		case "Saga_JessikaFirstKick": // фокус первый - хватка тяжести + 5 скелетов
			sld = characterFromId("Jessika");
			sld.dialog.currentnode = "stage_1";
			DoQuestCheckDelay("Saga_JessikaFirstKick_1", 0.5);
        break;
		
		case "Saga_JessikaFirstKick_1":
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			CreateLocationParticles("item", "quest", "top", 1.0, 0, 0, "");
			CreateLocationParticles("item", "quest", "top", 1.0, 0, 0, "");
			CreateLocationParticles("item", "quest", "top", 1.0, 0, 0, "");
			sld = characterFromId("Jessika");
			ChangeCharacterAddressGroup(sld, "shore67", "quest", "top");
			pchar.questTemp.Saga.Attack = true; // обработка в АИ
			pchar.questTemp.Saga.Jess_Fightstage = "next";
			sTotalTemp = "top";
			iTotalTemp = 12;
        break;
		
		case "Saga_JessikaFirstKick_2":
			LAi_SetActorType(Pchar);
			LAi_ActorAnimation(Pchar, "Ground_StandUp", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaFirstKick_3", 3.5);
			CreateLocationParticles("blast_inv", "quest", "top", 1.6, 0, 0, "");
			sTemp = pchar.location.locator;
			CreateLocationParticles("blast_inv", "goto", sTemp, 1.3, 0, 0, "");
			CreateLocationParticles("blood_big", "goto", sTemp, 1.0, 0, 0, "");
			CreateLocationParticles("blood_big", "goto", sTemp, 1.3, 0, 0, "");
			PlaySound("People Fight\Death_NPC_08.wav");
			PlaySound("Interface\boom.wav");
			Pchar.chr_ai.hp = stf(Pchar.chr_ai.hp)/1.5; // 1/3 жизни сносим 
			Log_Info("Джессика отняла у вас способность к бегу!");
			pchar.GenQuest.CantRun = true;
        break;
		
		case "Saga_JessikaFirstKick_3":
			LAi_SetPlayerType(Pchar);
			CheckAndSetOverloadMode(GetMainCharacter());
			PlaySound("Interface\boom.wav");
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Reef_skeleton_"+i);
				sld.monster = true; // признак нежити
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				PlaySound("types\skel.wav");
				CreateLocationParticles("blast_inv", "quest", "skeleton"+i, 1.3, 0, 0, "");
			}
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "Saga_JessikaFirstKick_4");
				LAi_SetFightMode(pchar, true);
			// поджигаем угол у скалы
			pchar.quest.Saga_JessFire3.win_condition.l1 = "locator";
			pchar.quest.Saga_JessFire3.win_condition.l1.location = "shore67";
			pchar.quest.Saga_JessFire3.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_JessFire3.win_condition.l1.locator = "fire3";
			pchar.quest.Saga_JessFire3.function = "Saga_JessFireStep";
			CreateLocationParticles("shipfire", "quest", "fire3", 0.5, 0, 0, "");
			// зажигаем огоньки
			chr = &Locations[FindLocation(pchar.location)];
			chr.hell_fire_1 = true;
			for (i=1; i<=25; i++)
			{
				CreateLocationParticles("torch", "item", "fire"+i, 0.1, 0, 0, "");
			}
        break;
		
		case "Saga_JessikaFirstKick_4":
			sld = characterFromId("Jessika");
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_SetCheckMinHP(sld, 10, true, "Saga_JessikaSecondKick"); // второй фокус
			CreateLocationParticles("blast_inv", "quest", "skeleton1", 1.3, 0, 0, "");
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			ChangeCharacterAddressGroup(sld, "shore67", "quest", "skeleton1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        break;
		
		case "Saga_JessikaSecondKick": // фокус второй - уменьшение владением ХО + 5 скелетов
			sld = characterFromId("Jessika");
			sld.dialog.currentnode = "stage_2";
			DoQuestCheckDelay("Saga_JessikaSecondKick_1", 0.5);
        break;
		
		case "Saga_JessikaSecondKick_1":
			CreateLocationParticles("item", "quest", "rock", 1.0, 0, 0, "");
			CreateLocationParticles("item", "quest", "rock", 1.0, 0, 0, "");
			CreateLocationParticles("item", "quest", "rock", 1.0, 0, 0, "");
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			sld = characterFromId("Jessika");
			ChangeCharacterAddressGroup(sld, "shore67", "quest", "rock");
			pchar.questTemp.Saga.Attack = true; // обработка в АИ
			sTotalTemp = "rock";
			iTotalTemp = 5;
        break;
		
		case "Saga_JessikaSecondKick_2":
			LAi_SetActorType(Pchar);
			LAi_ActorAnimation(Pchar, "Ground_StandUp", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaSecondKick_3", 3.5);
			CreateLocationParticles("blast_inv", "quest", "rock", 1.6, 0, 0, "");
			sTemp = pchar.location.locator;
			CreateLocationParticles("blast_inv", "goto", sTemp, 1.3, 0, 0, "");
			CreateLocationParticles("blood_big", "goto", sTemp, 1.0, 0, 0, "");
			CreateLocationParticles("blood_big", "goto", sTemp, 1.3, 0, 0, "");
			PlaySound("People Fight\Death_NPC_08.wav");
			PlaySound("Interface\boom.wav");
			Pchar.chr_ai.hp = stf(Pchar.chr_ai.hp)/2; // 1/2 жизни сносим 
			Log_Info("Джессика поглотила ваши силы - умения в оружии снизились на 30 единиц!");
        break;
		
		case "Saga_JessikaSecondKick_3":
			LAi_SetPlayerType(Pchar);
			PlaySound("Interface\boom.wav");
			// скелетоны
			iRank = 20+MOD_SKILL_ENEMY_RATE*2;
			iScl = 60;
			for (i=5; i<=9; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Reef_skeleton_add_"+i, "skel"+(rand(3)+1), "skeleton", "skeleton", iRank, PIRATE, -1, false, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_13", "", "", iScl*2);
				sld.cirassId = Items_FindItemIdx("cirass3");
				if (i > 5)
				{
					sld.cirassId = Items_FindItemIdx("cirass1");
					if (MOD_SKILL_ENEMY_RATE > 4)
					{
						fMft = MOD_SKILL_ENEMY_RATE/10;
						sld.MultiFighter = 0.8+fMft; // мультифайтер
					}
				}
				sld.monster = true; // признак нежити
				ChangeCharacterAddressGroup(sld, "shore67", "quest", "skeleton"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				PlaySound("types\skel.wav");
				CreateLocationParticles("blast_inv", "quest", "skeleton"+i, 1.3, 0, 0, "");
			}
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "Saga_JessikaSecondKick_4");
				LAi_SetFightMode(pchar, true);
			// закрываем доступ на крыльцо
			pchar.quest.Saga_JessFire.win_condition.l1 = "locator";
			pchar.quest.Saga_JessFire.win_condition.l1.location = "shore67";
			pchar.quest.Saga_JessFire.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_JessFire.win_condition.l1.locator = "entrance";
			pchar.quest.Saga_JessFire.function = "Saga_JessFireStep";
			CreateLocationParticles("shipfire", "quest", "entrance", 0.5, 0, 0, "");
			// зажигаем огоньки
			chr = &Locations[FindLocation(pchar.location)];
			chr.hell_fire_2 = true;
			for (i=26; i<=40; i++)
			{
				CreateLocationParticles("torch", "item", "fire"+i, 0.1, 0, 0, "");
			}
        break;
		
		case "Saga_JessikaSecondKick_4":
			sld = characterFromId("Jessika");
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_SetCheckMinHP(sld, 10, true, "Saga_JessikaThirdKick"); // третий фокус
			CreateLocationParticles("blast_inv", "quest", "skeleton8", 1.3, 0, 0, "");
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			ChangeCharacterAddressGroup(sld, "shore67", "quest", "skeleton8");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        break;
		
		case "Saga_JessikaThirdKick": // фокус третий - уменьшение энергии + отравленный клинок
			sld = characterFromId("Jessika");
			sld.dialog.currentnode = "stage_3";
			DoQuestCheckDelay("Saga_JessikaThirdKick_1", 0.5);
        break;
		
		case "Saga_JessikaThirdKick_1":
			CreateLocationParticles("item", "quest", "wall", 1.0, 0, 0, "");
			CreateLocationParticles("item", "quest", "wall", 1.0, 0, 0, "");
			CreateLocationParticles("item", "quest", "wall", 1.0, 0, 0, "");
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			sld = characterFromId("Jessika");
			ChangeCharacterAddressGroup(sld, "shore67", "quest", "wall");
			pchar.questTemp.Saga.Attack = true; // обработка в АИ
			sTotalTemp = "wall";
			iTotalTemp = 4;
        break;
		
		case "Saga_JessikaThirdKick_2":
			LAi_SetActorType(Pchar);
			LAi_ActorAnimation(Pchar, "Ground_StandUp", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaThirdKick_3", 3.5);
			CreateLocationParticles("Splash", "quest", "bridge2", 0, 0, 0, "");
			Pchar.chr_ai.hp = stf(Pchar.chr_ai.hp)/3; // 2/3 жизни сносим
			Log_Info("Джессика поглотила вашу ловкость - энергия снизились на 20 единиц!");
			PlaySound("People Fight\Death_NPC_08.wav");
			CreateLocationParticles("blood_big", "quest", "bridge2", 1.3, 0, 0, "");
			CreateLocationParticles("blood_big", "quest", "bridge2", 1.0, 0, 0, "");
			PlaySound("Sea Battles\bolshoy_vsplesk_001.wav");
        break;
		
		case "Saga_JessikaThirdKick_3":
			LAi_SetPlayerType(Pchar);
			SetMusic("music_teleport");
			CreateLocationParticles("blast_inv", "quest", "wall", 1.6, 0, 0, "");
			PlaySound("Interface\boom.wav");
			sld = characterFromId("Jessika");
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_SetCheckMinHP(sld, 10, true, "Saga_JessikaBattleTalk"); // разговор
			ChangeCharacterAddressGroup(sld, "shore67", "quest", "bridge1");
			CreateLocationParticles("blast_inv", "quest", "bridge1", 1.3, 0, 0, "");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetFightMode(pchar, true);
			// закрываем выход c моста
			pchar.quest.Saga_JessFire1.win_condition.l1 = "locator";
			pchar.quest.Saga_JessFire1.win_condition.l1.location = "shore67";
			pchar.quest.Saga_JessFire1.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_JessFire1.win_condition.l1.locator = "fire1";
			pchar.quest.Saga_JessFire1.function = "Saga_JessFireStep";
			pchar.quest.Saga_JessFire2.win_condition.l1 = "locator";
			pchar.quest.Saga_JessFire2.win_condition.l1.location = "shore67";
			pchar.quest.Saga_JessFire2.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_JessFire2.win_condition.l1.locator = "fire2";
			pchar.quest.Saga_JessFire2.function = "Saga_JessFireStep";
			CreateLocationParticles("shipfire", "quest", "fire1", 0.5, 0, 0, "");
			CreateLocationParticles("shipfire", "quest", "fire2", 0.5, 0, 0, "");
			chr = &Locations[FindLocation(pchar.location)];
			chr.hell_fire_3 = true;
        break;
		
		case "Saga_JessikaBattleTalk": // разговор после последней стадии боя
			DoQuestCheckDelay("hide_weapon", 0.5);//убрать оружие
			sld = characterFromId("Jessika");
			sld.dialog.currentnode = "stage_4";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			AddComplexSelfExpToScill(450, 450, 450, 450);
			LAi_group_Delete("EnemyFight");
        break;
		
		case "Saga_JessikaDie": // убили Джесс
			LAi_group_Delete("EnemyFight");
			pchar.quest.Saga_JessFire.over = "yes"; 
			pchar.quest.Saga_JessFire1.over = "yes"; 
			pchar.quest.Saga_JessFire2.over = "yes"; // снимаем реакцию на огонь
			chr = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(chr, "hell_fire_1");
			DeleteAttribute(chr, "hell_fire_2");
			DeleteAttribute(chr, "hell_fire_3");
			pchar.quest.Saga_FindBeatriss_Letter.win_condition.l1 = "item";
			pchar.quest.Saga_FindBeatriss_Letter.win_condition.l1.item = "letter_beatriss";
			pchar.quest.Saga_FindBeatriss_Letter.function = "Saga_FindBeatrissLetter";
        break;
		
		case "Video_Jess": // видео о Джесс
			PChar.GenQuest.VideoAVI = "Jessika";
			PChar.GenQuest.VideoAfterQuest = "Video_continueSvensonStory";
			DoQuestCheckDelay("PostVideo_Start", 0.2);
		break;
		
		case "Video_continueSvensonStory": // завершение рассказа
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "saga_66a";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
        break;
		
		case "Video_Reef": // видео о рифе
			PChar.GenQuest.VideoAVI = "Reef";
			PChar.GenQuest.VideoAfterQuest = "Video_continueJessStory";
			DoQuestCheckDelay("PostVideo_Start", 0.2);
		break;
	
		case "Video_continueJessStory":
			PlayStereoOGG("music_shore");
			sld = characterFromId("Jessika");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Saga_BarbadosTreatment": // начинаем молитвы
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "barmen", "bar1", "Saga_BarbadosBead", -1);
			bDisableCharacterMenu = true;//лоченые интерфейсы
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
        break;
		
		case "Saga_BarbadosBead": // молимся
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Bead", "OpenTheDoors", -1);
			DoQuestCheckDelay("Saga_BarbadosTreatmentStart", 10.0);
        break;
		
		case "Saga_BarbadosTreatmentStart": // рамка
			SetLaunchFrameFormParam("В молитвах прошли долгие часы..."+ NewStr() +"Свечи сгорели полностью...", "Saga_JessikaSoul", 0, 6);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 9, 10); //крутим время
			RecalculateJumpTable();
        break;
		
		case "Saga_JessikaSoul": // телепортируем в спецлокацию
			DoQuestReloadToLocation("Terrain", "reload", "reload2", "Saga_JessikaSoul_1");
        break;
		
		case "Saga_JessikaSoul_1":
			ChangeShowIntarface();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.Saga.JessSoul = "true";
			DoQuestCheckDelay("TalkSelf_Quest", 0.1);
        break;
		
		case "Saga_JessikaSoul_2":
			SetMusic("music_terrain");
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			DoQuestCheckDelay("Saga_JessikaSoul_2_1", 4.0);
			DeleteAttribute(pchar, "questTemp.Saga.JessSoul"); // 021012
        break;
		
		case "Saga_JessikaSoul_2_1":
			CreateLocationParticles("shadowstar", "reload", "reload1", 1.15, 0, 0, "");
			CreateLocationParticles("shadowstar", "reload", "reload1", 1.15, 0, 0, "");
			CreateLocationParticles("shadowstar", "reload", "reload1", 1.15, 0, 0, "");
			DoQuestCheckDelay("Saga_JessikaSoul_2_2", 3.0);
        break;
		
		case "Saga_JessikaSoul_2_2": // встреча с очищенной душой Джесс
			sld = GetCharacter(NPC_GenerateCharacter("Jessika_soul", "Jessika", "woman", "jess", 1, PIRATE, 0, false, "quest"));
			sld.name = "Джессика";
			sld.lastname = "Роуз";
			sld.greeting = "Jessika_soul";
			sld.Dialog.Filename = "Quest\Saga\Jessika.c";
			sld.dialog.currentnode = "soul";
			ChangeCharacterAddressGroup(sld, "Terrain", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload2", "", -1);
			DoQuestCheckDelay("Saga_JessikaSoul_3", 18.5);
        break;
		
		case "Saga_JessikaSoul_3": // Джесс начинает разговор
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Jessika_soul");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			SetMusic("music_romantic");
        break;
		
		case "Saga_JessikaSoul_4": // перекидываем назад в церковь
			DoQuestReloadToLocation("bridgetown_church", "barmen", "bar1", "Saga_JessikaSoul_5");
        break;
		
		case "Saga_JessikaSoul_5": // снимаем отрицательные атрибуты
			LAi_SetPlayerType(pchar);
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter());
			DeleteAttribute(pchar, "GenQuest.BladePenalty");
			DeleteAttribute(pchar, "GenQuest.EnergyPenalty");
			AddCharacterHealth(pchar, 50);
			AddCharacterMaxHealth(pchar, 5);
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			AddQuestRecord("Shadows", "12");
			CloseQuestHeader("Shadows");
			// вертаем в норму священника
			sld = characterFromId("Bridgetown_Priest");
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_SetPriestType(sld);
			ChangeCharacterAddressGroup(sld, "bridgetown_church", "barmen", "stay");
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
        break;
	//<-- Тени прошлого
		
	//---------------------------------------Завещание Шарпа-------------------------------------------
		case "Saga_CourtGo": // выводим на улицу
			DoQuestReloadToLocation("PortRoyal_town", "reload", "houseSp4", "Saga_CourtGo_1");
        break;
		
		case "Saga_CourtGo_1": // идем в резиденцию
			ChangeShowIntarface();
			sld = characterFromId("Helena");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_town", "reload", "houseSp4");
			chr = characterFromId("Loxly");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(chr, "PortRoyal_town", "reload", "houseSp4");
			LAi_ActorGoToLocator(chr, "reload", "reload3_back", "Saga_CourtGo_2", -1);
			LAi_ActorFollow(pchar, chr, "", -1);
			LAi_ActorFollow(sld, chr, "", -1);
        break;
		
		case "Saga_CourtGo_2": // входим в резиденцию
			DoQuestReloadToLocation("PortRoyal_townhall", "reload", "reload1", "Saga_CourtGo_3");
        break;
		
		case "Saga_CourtGo_3": // запускаем ролик суда
			PChar.GenQuest.VideoAVI = "court";
			PChar.GenQuest.VideoAfterQuest = "Saga_CourtGo_4";
			DoQuestCheckDelay("PostVideo_Start", 0.2);
		break;
		
		case "Saga_CourtGo_4": // суд прошел
			SetLaunchFrameFormParam("Суд состоялся!", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 5, 10); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_CourtReload", 4.5);
        break;
		
		case "Saga_CourtReload": // перекидываем в дом адвоката
			DoQuestReloadToLocation("PortRoyal_houseSp4", "quest", "quest1", "Saga_CourtFinish");
        break;
		
		case "Saga_CourtFinish": // расставим всех по локаторам
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Helena");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseSp4", "quest", "quest3");
			sld = characterFromId("Loxly");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseSp4", "quest", "quest2");
			LAi_ActorDialogNow(sld, pchar, "", -1);
        break;
		
		case "Saga_HelenaIslaTesoro": // Элен с ГГ на улице - подводим итоги Саги
			sld = characterFromId("Loxly");
			LAi_SetHuberType(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseSp4", "sit", "sit1");
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "result";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_town", "quest", "quest4");
			LAi_ActorDialogNow(sld, pchar, "", -1);
        break;
		
		case "Saga_HelenaBye": // расстаемся с Элен по собственному решению, не стираем
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = characterFromId("Helena");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload5_back", "none", "", "", "OpenTheDoors", 10.0);
			LAi_CharacterDisableDialog(sld);
			AddQuestRecord("Testament", "12");
			CloseQuestHeader("Testament");
			DoQuestCheckDelay("Saga_HelenaOnIsland", 12.0);
        break;
		
		case "Saga_HelenaOnIsland": // Элен на Исла Тесоро
			sld = characterFromId("Helena");
			ChangeCharacterAddressGroup(sld, "Pirates_townhall", "goto", "goto1");
			LAi_SetOwnerType(sld);
			sld.dialog.currentnode = "islatesoro";
        break;
		
		case "Saga_HelenaRomantic": // романтик-сцена
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("", "", 0, 10);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 3, 10); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaRomantic_1", 10.0);
        break;
		
		case "Saga_HelenaRomantic_1": // в таверне
			DoQuestReloadToLocation("PortRoyal_tavern_upstairs", "quest", "quest4", "");
			sld = characterFromId("Helena");
			ChangeCharacterAddressGroup(sld, "PortRoyal_tavern_upstairs", "quest", "quest3");
			DoQuestCheckDelay("Saga_HelenaRomantic_2", 1.3);
        break;
		
		case "Saga_HelenaRomantic_2": // акт второй
			SetMusic("music_romantic");
			ChangeShowIntarface();
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 850);
			DoQuestCheckDelay("Saga_HelenaRomantic_3", 14.0);
        break;
		
		case "Saga_HelenaRomantic_3": // третий... теперь ГГ как честный человек обязан жениться
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("", "", 0, 16);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex7.wav");
            LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_4", 16.0);
			AddCharacterHealth(pchar, 6);
			LAi_SetCurHPMax(pchar);
        break;
		
		case "Saga_HelenaRomantic_4": // четвертый...
			locCameraResetState();
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "happy";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;
		
		case "Saga_HelenaRomantic_5": // пятый - на улицы
			bDisableCharacterMenu = false;//лоченые интерфейсы
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			DeleteAttribute(pchar, "GenQuest.MusicContinue");
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "Helena_officer";
			DeleteAttribute(sld, "HalfImmortal"); // халява закончилась
			DeleteAttribute(sld, "CompanionDisable");
			LAi_SetOfficerType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			DoQuestReloadToLocation("PortRoyal_town", "reload", "reload1", "");
			AddQuestRecord("Testament", "13");
			CloseQuestHeader("Testament");
			// если выбрал не Мэри - закрываем к ней доступ
			if (pchar.questTemp.LSC.Mary == "alive")
			{
				for (i=0; i<=3; i++)
				{
					LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, true); // закрываем вход к Мэри
				}
				pchar.questTemp.LSC.Mary = "fail";
				RemoveItems(pchar, "key_mary", 1); // удалить ключ Мэри
				DeleteAttribute(pchar, "questTemp.LSC.MaryWait"); // стираем атрибут общения с Мэри
			}
        break;
		
	// ------------------------------------ провалы Саги -------------------------------------------------
		case "Saga_FailCenturion": // утопили Центурион - Данни и Натана в Марун-Таун
			chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
        break;
		
	//--------------------------- встроенный мини-квест Корабль главы братства ---------------------------
		case "AlexClock_BandosDie":
			LAi_group_Delete("EnemyFight");
			if (CheckCharacterItem(pchar, "alexs_chest")) DoQuestFunctionDelay("AlexClock_FindChest", 0.5);
			else
			{
				pchar.quest.AlexClock_Find.win_condition.l1 = "item";
				pchar.quest.AlexClock_Find.win_condition.l1.item = "alexs_chest";
				pchar.quest.AlexClock_Find.function = "AlexClock_FindChest";
			}
        break;
		
	// ------------------------------- отношения с девушками-героинями Саги ------------------------------
		// секс с Элен
		case "Helena_LoveSex":
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex"+(rand(9)+1)+".wav");
            LaunchFrameForm();
			WaitDate("", 0, 0, 0, 3, 10); //крутим время
			RecalculateJumpTable();
			AddCharacterHealth(pchar, 6); 
			LAi_SetCurHPMax(pchar);
        break;
		
	// --> поведение Мэри вне LSC
		case "Mary_LoveSex": // секс с Мэри
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex"+(rand(9)+1)+".wav");
            LaunchFrameForm();
			WaitDate("", 0, 0, 0, 3, 10); //крутим время
			RecalculateJumpTable();
			AddCharacterHealth(pchar, 12); 
			LAi_SetCurHPMax(pchar);
			pchar.quest.Mary_giveme_sex.over = "yes"; //снять прерывание
			pchar.quest.Mary_giveme_sex1.over = "yes"; //снять прерывание лесник. 																	 
        break;
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Jason------------------------------------ Суп из черепахи --------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "Terrapin_LevasserCaveDied":
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Terrapin", "10");
			pchar.questTemp.Terrapin = "done";
			sld = characterFromId("Tortuga_Mayor");
			LAi_NoRebirthEnable(sld); // респавнился, гад 
			pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeOfficersLoyality("good_all", 2);
			AddCrewMorale(pchar, 10);
			AddComplexSelfExpToScill(200, 200, 200, 200);
			AddCharacterExpToSkill(pchar, "Fortune", 400);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 500);//скрытность
			SetFunctionTimerCondition("Terrapin_ReturnFox", 0, 0, 3, false); // Фокса на место fix 160912
        break;
		
		case "Terrapin_LevasserRoomEnter":
			LAi_SetPlayerType(pchar);
			PlaySound("Ambient\LAND\door_001.wav");
			PlaySound("Ambient\LAND\door_004.wav");
			iRank = 25+MOD_SKILL_ENEMY_RATE*2;
			iScl = 65;
			// сам Левассер
			sld = characterFromId("Tortuga_Mayor");
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "levasser_room";
			sld.greeting = "Levasser";
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "reload", "reload1_back");
			LAi_SetImmortal(sld, false);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			// гарды
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("TerrapinGuard"+i, "sold_fra_"+i, "man", "man", iRank, FRANCE, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol6", "bullet", iScl*2);
				ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "quest", "quest"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_warrior_DialogEnable(sld, false);
			}
			// заполним сундук в гроте
			pchar.GenQuestBox.Tortuga_town = true;
			pchar.GenQuestBox.Tortuga_town.box1.items.totem_03 = 1;
			pchar.GenQuestBox.Tortuga_town.box1.items.cannabis7 = 1;
			pchar.GenQuestBox.Tortuga_town.box1.items.purse2 = 5; // Addon-2016 Jason
			pchar.GenQuestBox.Tortuga_town.box1.items.map_tortuga = 1;
			pchar.GenQuestBox.Tortuga_town.box1.items.indian_11 = 1;
			pchar.GenQuestBox.Tortuga_town.box1.items.potion2 = 20;
			pchar.GenQuestBox.Tortuga_town.box1.items.potion7 = 1;
			pchar.GenQuestBox.Tortuga_town.box1.items.potionwine = 10;
			pchar.GenQuestBox.Tortuga_town.box1.items.mineral2 = 1;
			pchar.GenQuestBox.Tortuga_town.box1.items.mineral3 = 20;
			pchar.GenQuestBox.Tortuga_town.box1.items.mineral5 = 1;
			pchar.GenQuestBox.Tortuga_town.box1.items.mineral6 = 1;
			pchar.GenQuestBox.Tortuga_town.box1.items.mineral9 = 1;
			pchar.GenQuestBox.Tortuga_town.box1.items.mineral11 = 1;
			pchar.GenQuestBox.Tortuga_town.box1.items.mineral17 = 10;
			pchar.GenQuestBox.Tortuga_town.box1.items.mineral19 = 1;
			pchar.GenQuestBox.Tortuga_town.box1.items.mineral35 = 1;
        break;
		
		case "Terrapin_LevasserRoomDied":
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", true); // закроем комнату снаружи
			LocatorReloadEnterDisable("Tortuga_tavern_upstairs", "reload1_back", true);//закрыть выход
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			n = Findlocation("Tortuga_town");
			locations[n].models.day.charactersPatch = "Margarita_patch_roof"; 
			locations[n].models.night.charactersPatch = "Margarita_patch_roof"; // подменяем патч для персонажа
			LAi_LocationDisableOfficersGen("Tortuga_Town", true);//офицеров не пускать
			pchar.questTemp.Terrapin = "roof";
			DoQuestCheckDelay("hide_weapon", 1.0);//убрать оружие
			DoQuestCheckDelay("TalkSelf_Quest", 1.0);
			sld = characterFromId("Tortuga_Mayor");
			LAi_NoRebirthEnable(sld); // респавнился, гад 
			pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeOfficersLoyality("good_all", 2);
			AddCrewMorale(pchar, 10);
			AddComplexSelfExpToScill(250, 250, 250, 250);
			AddCharacterExpToSkill(pchar, "Fortune", 500);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 400);//скрытность
        break;
		
		case "Terrapin_GoWindow":
			pchar.quest.Terrapin_window.win_condition.l1 = "locator";
			pchar.quest.Terrapin_window.win_condition.l1.location = "Tortuga_tavern_upstairs";
			pchar.quest.Terrapin_window.win_condition.l1.locator_group = "reload";
			pchar.quest.Terrapin_window.win_condition.l1.locator = "reload_window";
			pchar.quest.Terrapin_window.function = "Terrapin_GotoWindow";
			pchar.questTemp.Terrapin = "roofgo"; // 021012
        break;
		
		case "Terrapin_FirstShot": // мушкетер стреляет
			sld = CharacterFromID("TerrapinMush"+sTotalTemp);
            LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "shot", "Terrapin_FirstShot_1", 1.0);
        break;
		
		case "Terrapin_FirstShot_1": // мушкетер попал в ГГ
			sld = CharacterFromID("TerrapinMush1");
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "hit_fire", "pchar_back_to_player", 0.8);
			CreateLocationParticles("blood_big", "quest", "shot"+sTotalTemp, 2.0, 0, 0, "");
			LAi_ApplyCharacterDamage(pchar, 150, "fire");
			LAi_CheckKillCharacter(pchar);
        break;
		
		case "Terrapin_GirlShot": // застрелили девушку
			CreateLocationParticles("blood_big", "quest", "roof", 2.0, 0, 0, "");
			CreateLocationParticles("blood_big", "quest", "roof", 1.8, 0, 0, "");
			sld = CharacterFromID("TerrapinRoofGirl");
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Terrapin_GirlShot_1", 1.5);
        break;
		
		case "Terrapin_GirlShot_1": // 
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "quest", "mushketer2"); 
			sld = CharacterFromID("TerrapinMush2");
            LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "shot", "Terrapin_SecondShot", 1.0);
        break;
		
		case "Terrapin_SecondShot": // мушкетер попал в ГГ
			sld = CharacterFromID("TerrapinMush2");
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "hit_fire", "pchar_back_to_player", 1.0);
			CreateLocationParticles("blood_big", "quest", "roof", 2.0, 0, 0, "");
			LAi_ApplyCharacterDamage(pchar, 150, "fire");
			LAi_CheckKillCharacter(pchar);
			// ставим горожанина
			sld = GetCharacter(NPC_GenerateCharacter("TerrapinRoofMan", "citiz_15", "man", "man", 25, FRANCE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 65, 65, "blade_10", "pistol1", "bullet", 100);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, true);
			ChangeCharacterAddressGroup(sld, "Tortuga_town", "quest", "roof2");
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sTotalTemp = "3";
        break;
		
		case "Terrapin_TiboDied": // убили Тибо
			LAi_group_Delete("EnemyFight");
			pchar.GenQuest.Notsearchbody = true; // не обыскивать до разговора с Кати
			sld = characterFromId("Kathy");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			AddComplexSelfExpToScill(100, 100, 100, 100);
        break;
		
		case "LevasserDiedResidence": // убили Левассера в резиденции при штурме города
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Tortuga_Mayor");
			LAi_NoRebirthEnable(sld); // респавнился, гад 
			pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeOfficersLoyality("good_all", 1);
			AddCrewMorale(pchar, 5);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			pchar.questTemp.Sharlie.LevasserDied = "true";
			AddQuestRecord("Sharlie", "32");
        break;
		
		//----------------------------------------- защита Сен-Пьера -------------------------------------------
		case "DefendSP_VideoSiege": // ролик
			PChar.GenQuest.VideoAVI = "Siege";
			PChar.GenQuest.VideoAfterQuest = "DefendSP_continueSiege";
			DoQuestCheckDelay("PostVideo_Start", 0.2);
		 break;
		
		case "DefendSP_continueSiege": 
			DoQuestReloadToLocation("Shore38", "reload", "sea", "DefendSP_SetInJungle");
			setCharacterShipLocation(pchar, "Shore38"));
			setWDMPointXZ("Shore38"); // корабль в бухту Ламантен
        break;

		case "DefendSP_SetInJungle": // ставим ГГ и его солдат в бухту
			LocatorReloadEnterDisable("Shore38", "boat", true); // закрыть выход в море
			pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			// устанавливаем солдат ГГ, 12 рыл+офицер
			iRank = 25+MOD_SKILL_ENEMY_RATE*2;
			iScl = 60;
			for (i=0; i<=12; i++)
			{
				if (i == 0)
				{
					sld = GetCharacter(NPC_GenerateCharacter("DefendSP_soldier_"+i, "mercen_26", "man", "man", iRank+5, FRANCE, -1, true, "soldier"));
					FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_13", "pistol4", "bullet", iScl*2+100);
					sld.name = "Гаэтано";
					sld.lastname = "Розетти";
					sld.dialog.FileName = "Quest\Sharlie\OtherNPC.c";
					sld.dialog.currentnode = "rosetti";
				}
				else
				{
					if (i == 9 || i == 12)
					{
						sld = GetCharacter(NPC_GenerateCharacter("DefendSP_soldier_"+i, "mush_ctz_"+(4+rand(2)), "man", "mushketer", iRank, FRANCE, -1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket2", "cartridge", iScl*2);
					}
					else
					{
						sld = GetCharacter(NPC_GenerateCharacter("DefendSP_soldier_"+i, "citiz_"+(31+rand(9)), "man", "man", iRank, FRANCE, -1, true, "soldier"));
						FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_10","blade_11"), "pistol1", "bullet", iScl*2);
					}
					LAi_CharacterDisableDialog(sld);
				}
				LAi_SetStayType(sld);
				ChangeCharacterAddressGroup(sld, "Shore38", "rld", "loc"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
        break;
		
		case "DefendSP_GoJungle":
			sld = CharacterFromID("Blaze");
			sld.dialog.currentnode = "first time";
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("DefendSP_soldier_0");
			sld.dialog.currentnode = "rosetti_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
        break;
		
		case "DefendSP_GateAlarm": // тревога поднята
			pchar.questTemp.Sharlie.DefendSP.GateAlarm = true;
        break;
		
		case "DefendSP_SpaPatrolDie":
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_group_Delete("EnemyFight");
			// прерывание на выход из города
			pchar.quest.DefendSP_jungle2.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle2.win_condition.l1.location = "FortFrance_ExitTown";
			pchar.quest.DefendSP_jungle2.function = "DefendSP_SpainAvanpost";
			DefendSP_CatchOurSoldiers();
			AddComplexSelfExpToScill(100, 100, 100, 100);
        break;
		
		case "DefendSP_SpaAvanpostAttack":
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DefendSP_SpaAvanpostDie");
        break;
		
		case "DefendSP_SpaAvanpostDie":
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("FortFrance_ExitTown", "reload2_back", true); // закрыть форт
			locations[FindLocation("FortFrance_Town")].QuestCapture = true;
			locations[FindLocation("FortFrance_Town")].hidden_fire = true;
			locations[FindLocation("FortFrance_Town")].hidden_sound = true;
			LAi_group_Delete("EnemyFight");
			// прерывание на город
			pchar.quest.DefendSP_jungle3.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle3.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.DefendSP_jungle3.function = "DefendSP_TownBattle";
			AddQuestRecord("Sharlie", "33");
			DefendSP_CatchOurSoldiers();
			AddComplexSelfExpToScill(250, 250, 250, 250);
        break;
		
		case "DefendSP_SpaTownDie":
			LAi_group_Delete("EnemyFight");
			pchar.quest.DefendSP_town1.win_condition.l1 = "locator";
			pchar.quest.DefendSP_town1.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.DefendSP_town1.win_condition.l1.locator_group = "reload";
			pchar.quest.DefendSP_town1.win_condition.l1.locator = "reloadPr1";
			pchar.quest.DefendSP_town1.function = "DefendSP_GotoMatieBase";
			pchar.quest.DefendSP_town2.win_condition.l1 = "location";
			pchar.quest.DefendSP_town2.win_condition.l1.location = "FortFrance_Dungeon";
			pchar.quest.DefendSP_town2.function = "DefendSP_BaseBattle";
			AddQuestRecord("Sharlie", "34");
			locations[FindLocation("FortFrance_Dungeon")].QuestCapture = true;
			sld = ItemsFromID("MaltieBase_keys");
            sld.shown = true;
			sld.startLocation = "FortFrance_Dungeon";
			sld.startLocator = "item"+(rand(4)+1); // ключ от камеры Мишеля
			DefendSP_CatchOurSoldiers();
			AddComplexSelfExpToScill(400, 400, 400, 400);
        break;
		
		case "DefendSP_SpaBaseDie":
			LAi_group_Delete("EnemyFight");
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "Base_afterfight";
			AddQuestRecord("Sharlie", "35");
			DefendSP_CatchOurSoldiers();
			AddComplexSelfExpToScill(250, 250, 250, 250);
        break;
		
		case "DefendSP_PrepareFortAttack":
			// ставим мальтийцев
			iRank = 25+MOD_SKILL_ENEMY_RATE*2;
			iScl = 60;
			for (i=1; i<=7; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DefendSP_frafort_"+i, "sold_fra_"+(rand(7)+9), "man", "man", iRank, FRANCE, 1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_12","blade_14"), "pistol1", "bullet", iScl*2);
				LAi_CharacterDisableDialog(sld);
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, "FortFrance_Exittown", "rld", "aloc"+i);
			}
			// ставим Мишеля
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "Fort_attack";
			ChangeCharacterAddressGroup(sld, "FortFrance_Exittown", "rld", "aloc10");
			GiveItem2Character(sld, "blade_13");
			sld.equip.blade = "blade_13";
			GiveItem2Character(sld, "pistol4");
			EquipCharacterbyItem(sld, "pistol4");
			LAi_SetCharacterUseBullet(sld, "bullet");
			TakeNItems(sld, "bullet", 50);
			AddItems(sld, "gunpowder", 50);
			TakeNItems(sld, "potion2", 10);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;
		
		case "DefendSP_SpaFortDie":
			LAi_group_Delete("EnemyFight");
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "Fort_attack_2";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			DefendSP_CatchOurSoldiers();
			AddComplexSelfExpToScill(150, 150, 150, 150);
        break;
		
		case "DefendSP_OpenExit":
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "reload_gate", false);
			SetFunctionTimerCondition("DefendSP_AllClear", 0, 0, 1, false);
        break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//Jason--------------------------------------- В поисках Стража Истины ------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "GuardOT_MCthink":
			LAi_SetPlayerType(pchar);
			DoQuestCheckDelay("TalkSelf_Quest", 0.5);
        break;
		
		case "GuardOT_ArriveBeach":
			DoQuestCheckDelay("TalkSelf_Quest", 1.5);
			pchar.quest.GuardOT_gotobaster.win_condition.l1 = "location";
			pchar.quest.GuardOT_gotobaster.win_condition.l1.location = "Baster_town";
			pchar.quest.GuardOT_gotobaster.function = "GuardOT_EnterInTown";
        break;
		
		case "GuardOT_ArriveGaleon":
			// для умников :)
			if (sti(environment.time) < 21 && sti(environment.time) > 3)
			{
				int iTime = sti(environment.time);
				if (iTime >= 21) iAddTime = 24 - iTime + 21;
				if (iTime < 7) iAddTime = 21 - iTime;
				if (iTime >= 7 && iTime < 21) iAddTime = 24  + 21 - iTime;
				StoreDayUpdate();
				WaitDate("",0,0,0,iAddtime,5);
				RecalculateJumpTable();
				RefreshWeather();
				RefreshLandTime();
			}
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.GenQuest.CantRun = true;
			CheckAndSetOverloadMode(GetMainCharacter()); // бег запрещаем
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			pchar.questTemp.Guardoftruth = "galeon";
			pchar.questTemp.Guardoftruth.Attack = "true";
			pchar.GenQuest.Notsearchbody = true;
			LAi_LockFightMode(pchar, true);
			DoQuestCheckDelay("GuardOT_ArriveGaleonSetMusic", 1.0);
			// ставим Марше
			sld = characterFromId("GOT_Marshe");
			sld.dialog.currentnode = "marshe_lay";
			LAi_CharacterDisableDialog(sld);//запрет диалога
			LAi_SetImmortal(sld, false);
			ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "lay");
			LAi_SetLayType(sld);
			LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "GuardOT_MarsheEscape");
			RemoveAllCharacterItems(sld, true);
			// ставим вахтенных
			iRank = 25+MOD_SKILL_ENEMY_RATE*2;
			iScl = 65;
			for (i=1; i<=8; i++)
			{
				if (i == 5)
				{
					sld = GetCharacter(NPC_GenerateCharacter("GuardOT_galeonguard_"+i, "mercen_25", "man", "man", iRank+5, PIRATE, -1, true, "soldier"));
					FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_16", "pistol5", "bullet", iScl*2+50);
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("GuardOT_galeonguard_"+i, "citiz_"+(rand(9)+31), "man", "man", iRank, PIRATE, -1, true, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_12", "pistol1", "bullet", iScl*2);
				}
				sld.dialog.FileName = "Quest\Sharlie\Guardoftruth.c";
				sld.dialog.currentnode = "galeonguard";
				sld.DontClearDead = true;
				ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "quest"+i);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, "GaleonFight");
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "GuardOT_GaleonGuardFight");
				LAi_SetCheckMinHP(pchar, LAi_GetCharacterHP(pchar)-1, false, "GuardOT_GaleonGuardFight");
			}
			LAi_group_SetRelation("GaleonFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetLookRadius("GaleonFight", 8.2);
			LAi_group_SetHearRadius("GaleonFight", 0.1);
			LAi_group_SetSayRadius("GaleonFight", 7.0);
			LAi_group_SetCheck("GaleonFight", "GuardOT_GaleonGuardDelete");
        break;
		
		case "GuardOT_ArriveGaleonSetMusic":
			SetMusic("music_q_battle");
			DoQuestCheckDelay("TalkSelf_Quest", 0.5);
        break;
		
		case "GuardOT_GaleonGuardFight":
			PlaySound("VOICE\Russian\EvilPirates01.wav");
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter());
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
			GuardOT_GaleonGuardFightAdd();
			sld = characterFromId("GOT_Marshe");
			if (sld.location.locator == "lay") // если спит
			{
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "goto", "stand");
				LAi_ActorAfraid(sld, pchar, false);
			}
			LAi_RemoveCheckMinHP(pchar);
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_galeonguard_"+i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "GaleonFight");
			}
			LAi_group_FightGroups("GaleonFight", LAI_GROUP_PLAYER, true);
			LAi_SetFightMode(pchar, true);
        break;
		
		case "GuardOT_MarsheEscape":
			PlaySound("VOICE\Russian\EvilPirates02.wav");
			sld = characterFromId("GOT_Marshe");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "goto", "stand");
			LAi_ActorAfraid(sld, pchar, false);
			DoQuestCheckDelay("GuardOT_GaleonGuardFight", 1.8);
        break;
		
		case "GuardOT_GaleonGuardDelete":
			LAi_group_Delete("GaleonFight");
			DoQuestCheckDelay("hide_weapon", 1.0);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Attack")) // все тихо
			{
				DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
				DeleteAttribute(pchar, "GenQuest.CantRun");
				CheckAndSetOverloadMode(GetMainCharacter());
				LAi_RemoveCheckMinHP(pchar);
				sld = characterFromId("GOT_Marshe");
				LAi_CharacterEnableDialog(sld);
				LAi_RemoveCheckMinHP(sld);
				AddCharacterExpToSkill(pchar, "Sneak", 1000);
			}
			else
			{
				sld = characterFromId("GOT_Marshe");
				LAi_SetStayType(sld);
				LAi_CharacterEnableDialog(sld);
				sld.dialog.currentnode = "marshe_sitground";
			}
        break;
		
		case "GuardOT_HuntersDie":
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Guardoftruth", "26");
			AddComplexSelfExpToScill(180, 180, 180, 180);
        break;
		
		case "GuardOT_CumanaCaveBandosDie":
			LAi_group_Delete("EnemyFight");
			DoQuestCheckDelay("hide_weapon", 1.5);
			sld = characterFromId("GOT_Bart");
			sld.dialog.currentnode = "barty_5";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddComplexSelfExpToScill(100, 100, 100, 100);
        break;
		
		case "GuardOT_BartyEscape":
			n = 0;
			for(i=0; i<=4; i++)
			{
				sld = characterFromId("GOT_bandos_"+i);
				if (LAi_GetCharacterHP(sld) <= 0) n++;
			}
			sld = characterFromId("GOT_Bart");
			sld.dialog.currentnode = "barty_5";
			LAi_SetActorType(sld);
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			if (n < 5) // остались живые враги
			{
				LAi_ActorAnimation(sld, "afraid", "GuardOT_BartyEscape1", -1);
			}
			else
			{
				DoQuestCheckDelay("hide_weapon", 0.5);
				LAi_ActorDialogNow(sld, pchar, "", -1);
			}
        break;
		
		case "GuardOT_BartyEscape1":
			sld = characterFromId("GOT_Bart");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "afraid", "GuardOT_BartyEscape2", -1);
        break;
		
		case "GuardOT_BartyEscape2":
			sld = characterFromId("GOT_Bart");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "afraid", "GuardOT_BartyEscape1", -1);
        break;
		
		case "GuardOT_ClearMayakPatrol":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			Map_NationQuestHunter(SPAIN); // немного развлечений
			SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 4, false); // еще немного развлечений
        break;
		
		case "GuardOT_SpaOfficerInTavern":
			if(CheckAttribute(pchar, "IsMushketer"))
			{
				SetMainCharacterToMushketer("", false);
			}
			FreeSitLocator("Santiago_tavern", "sit_base4");
			DoQuestReloadToLocation("Santiago_tavern", "sit", "sit_base4", "");			
			sld = characterFromID("spa_baseprisoner");
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
        break;
		
		case "GuardOT_SpaOfficerOutTavern":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Santiago_town")], false);//разрешить драться
			LAI_SetPlayerType(pchar);           
            DoQuestReloadToLocation("Santiago_tavern", "tables", "stay5", "");
            sld = CharacterFromID("spa_baseprisoner");
            ChangeCharacterAddressGroup(sld, "none", "", "");
			AddQuestRecord("Guardoftruth", "44");
			pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
			// гопота, чтобы весело жилось
			pchar.quest.GuardOT_setbandos.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setbandos.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setbandos.function = "GuardOT_SetBandosInTown"; 
			// на Гавану
			pchar.quest.GuardOT_Cuba2.win_condition.l1 = "location";
			pchar.quest.GuardOT_Cuba2.win_condition.l1.location = "Cuba2";
			pchar.quest.GuardOT_Cuba2.function = "GuardOT_Cuba2Arrive";
        break;
		
		case "GuardOT_SantiagoBandDie":
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			AddQuestRecord("Guardoftruth", "45");
			AddComplexSelfExpToScill(180, 180, 180, 180);
			AddCharacterExpToSkill(pchar, GetEquipedBladeType(pchar), 50);
        break;
		
		case "GuardOT_DiegoShoreGuardReady":
			for(i=1; i<=13; i++)
			{
				sld = CharacterFromID("GOT_spashore_"+i);
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				if (i >= 2 && i < 6) sld.MusketerDistance = 0;
			}
			sld = CharacterFromID("spa_baseprisoner");
			LAi_SetImmortal(sld, false);
			ChangeCharacterAddressGroup(sld, "Shore15", "quest", "quest2");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "rld", "aloc1", "", -1);
			sld = CharacterFromID("Diego");
			sld.name = "Диего";
			sld.lastname = "де Монтойя";
			sld.greeting = "";
			ChangeCharacterAddressGroup(sld, "Shore15", "quest", "quest2");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "rld", "aloc2", "", -1);
			DoQuestCheckDelay("GuardOT_DiegoShoreTalkReady", 3.0);
        break;
		
		case "GuardOT_DiegoShoreTalkReady":
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("spa_baseprisoner");
			sld.dialog.currentnode = "spa_prisoner_53";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
        break;
		
		case "GuardOT_DiegoShoreGuardDie":
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			AddQuestRecord("Guardoftruth", "49");
			LocatorReloadEnterDisable("shore15", "reload1_back", true);
			pchar.quest.GuardOT_exitsanantonio.win_condition.l1 = "location";
			pchar.quest.GuardOT_exitsanantonio.win_condition.l1.location = "Cuba2";
			pchar.quest.GuardOT_exitsanantonio.function = "GuardOT_CreateDiegoShips";
			AddComplexSelfExpToScill(180, 180, 180, 180);
			AddCharacterExpToSkill(pchar, GetEquipedBladeType(pchar), 50);
        break;
		
		case "GuardOT_CoastalGuardDie":
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			GuardOT_CatchOurSoldiers();
			AddQuestRecord("Guardoftruth", "53");
			LocatorReloadEnterDisable("Beliz_jungle_04", "reload2_back", false);
			pchar.quest.GuardOT_junglefort.win_condition.l1 = "location";
			pchar.quest.GuardOT_junglefort.win_condition.l1.location = "Jungle_fort_exit";
			pchar.quest.GuardOT_junglefort.function = "GuardOT_CreateExitFortGuard";
			AddComplexSelfExpToScill(130, 130, 130, 130);
			AddCharacterExpToSkill(pchar, GetEquipedBladeType(pchar), 50);
        break;
		
		case "GuardOT_ExitfortGuardDie":
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			GuardOT_CatchOurSoldiers();
			AddQuestRecord("Guardoftruth", "54");
			pchar.quest.GuardOT_junglefort1.win_condition.l1 = "location";
			pchar.quest.GuardOT_junglefort1.win_condition.l1.location = "Jungle_fort";
			pchar.quest.GuardOT_junglefort1.function = "GuardOT_CreateFortGuard";
			AddComplexSelfExpToScill(150, 150, 150, 150);
			AddCharacterExpToSkill(pchar, GetEquipedBladeType(pchar), 50);
        break;
		
		case "GuardOT_FortGuardDie":
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			AddQuestRecord("Guardoftruth", "55");
			pchar.quest.GuardOT_junglefort2.win_condition.l1 = "location";
			pchar.quest.GuardOT_junglefort2.win_condition.l1.location = "Jungle_fort_ammo";
			pchar.quest.GuardOT_junglefort2.function = "GuardOT_SetDiegoFortInside";
			AddComplexSelfExpToScill(180, 180, 180, 180);
			AddCharacterExpToSkill(pchar, GetEquipedBladeType(pchar), 50);
        break;
		
		case "GuardOT_ResidenceGuardDie":
			LAi_group_Delete("EnemyFight");
			DoQuestCheckDelay("hide_weapon", 1.5);
			for (i=1; i<=15; i++)
			{
				if (GetCharacterIndex("GuardOT_soldier_"+i) != -1)
				{
					sld = CharacterFromID("GuardOT_soldier_"+i);
					sld.lifeday = 1;
				}
			}
			pchar.quest.GuardOT_DiegoDie.win_condition.l1 = "item";
			pchar.quest.GuardOT_DiegoDie.win_condition.l1.item = "skinmap";
			pchar.quest.GuardOT_DiegoDie.function = "GuardOT_FindSkinmap";
        break;
		
		case "GuardOT_OpenCatocheDoor":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LocatorReloadEnterDisable("Jungle_fort_exit", "reload1_back", true); // закроем форт
        break;
			
		case "GuardOT_CabinBandosDie":
			LAi_group_Delete("EnemyFight");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Bermudes", true);
			AddQuestRecord("Guardoftruth", "61");
			for(i=1; i<=2; i++)
			{
				sld = CharacterFromID("GOT_cabinband_"+i);
				LAi_NoRebirthEnable(sld);
			}
			AddComplexSelfExpToScill(50, 50, 50, 50);
        break;
			
		case "GuardOT_ArchyIntoStore":
			DoQuestReloadToLocation("PortRoyal_store", "reload", "reload1", "GuardOT_ArchyIntoStore_1");
        break;
			
		case "GuardOT_ArchyIntoStore_1":
			sld = characterFromId("Archy");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "PortRoyal_storeRoom", "sit", "sit1", "GuardOT_ArchyIntoStoreRoom", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, sld, "", -1);
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "PortRoyal_storeRoom";
			sld.startLocator = "sit1";
			sld = ItemsFromID("chest");
			sld.model = "lcheer";
			sld.shown = true;
			sld.startLocation = "PortRoyal_storeRoom";
			sld.startLocator = "sit2";
			if (CheckAttribute(pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
        break;
		
		case "GuardOT_ArchyIntoStoreRoom":
			DoQuestReloadToLocation("PortRoyal_storeRoom", "sit", "sit2", "");
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Archy");
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
        break;
		
		case "GuardOT_MCOutFromArchyRoom":
			pchar.GenQuest.CamShuttle = 3;
			WaitDate("",0,0,0,9,5);
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Portroyal_town")], false);//разрешить драться
			LAI_SetPlayerType(pchar);           
            DoQuestReloadToLocation("Portroyal_town", "reload", "reload6", "");
			sld = ItemsFromID("lcheer");
			sld.shown = false;
			sld = ItemsFromID("chest");
			sld.model = "";
			sld.shown = false;
            sld = characterFromId("Archy");
            ChangeCharacterAddressGroup(sld, "none", "", "");
			LocatorReloadEnterDisable("PortRoyal_store", "reload2", true);
			LocatorReloadEnterDisable("PortRoyal_town", "reload", true); // дом рядом закрываем
			AddQuestRecord("Guardoftruth", "64");
			pchar.quest.GuardOT_squadrongo.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_squadrongo.win_condition.l1.date.hour  = sti(GetTime()+rand(12));
			pchar.quest.GuardOT_squadrongo.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1+rand(2));
			pchar.quest.GuardOT_squadrongo.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1+rand(2));
			pchar.quest.GuardOT_squadrongo.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1+rand(2));
			pchar.quest.GuardOT_squadrongo.function = "GuardOT_WillySquadronGo";
		 break;
		
		case "GuardOT_FindWayToRoom":
			chrDisableReloadToLocation = false;
			pchar.quest.GuardOT_toroof.win_condition.l1 = "locator";
			pchar.quest.GuardOT_toroof.win_condition.l1.location = "PortRoyal_houseSp1Room";
			pchar.quest.GuardOT_toroof.win_condition.l1.locator_group = "reload";
			pchar.quest.GuardOT_toroof.win_condition.l1.locator = "reload1_quest";
			pchar.quest.GuardOT_toroof.win_condition.l2 = "Hour";
			pchar.quest.GuardOT_toroof.win_condition.l2.start.hour = 0.00;
			pchar.quest.GuardOT_toroof.win_condition.l2.finish.hour = 3.00;
			PChar.Quest.GuardOT_toroof.again = true;
			pchar.quest.GuardOT_toroof.function = "GuardOT_ReloadToRoof";
			DeleteAttribute(pchar, "questTemp.Guardoftruth_room"); // 021012
        break;
		
		case "GuardOT_SitInHouse":
			LAi_SetActorType(Pchar);
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 2.5);
			DoQuestFunctionDelay("GuardOT_StandUpInHouse", 2.5);
			CreateLocationParticles("blood_big", "goto", "goto5", 1.0, 0, 0, "");
        break;
		
		case "GuardOT_HouseMercenDie":
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter()); // бег разрешаем
			AddQuestRecord("Guardoftruth", "69");
			pchar.quest.GuardOT_setwillyjungle.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setwillyjungle.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setwillyjungle.function = "GuardOT_SetWillyOutHouse";
			AddComplexSelfExpToScill(70, 70, 70, 70);
			AddCharacterExpToSkill(pchar, GetEquipedBladeType(pchar), 50);
        break;
		
		case "GuardOT_CreateAddMercenInHouse":
			PlaySound("Ambient\LAND\door_002.wav");
			iRank = 25+MOD_SKILL_ENEMY_RATE*2;
			iScl = 70;
			sld = GetCharacter(NPC_GenerateCharacter("GOT_housemercen_2", "mercen_14", "man", "man", iRank, ENGLAND, -1, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "topor_04", "pistol5", "bullet", iScl*2+100);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "IslaDeVieques_House", "reload", "reload1");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetCheck("EnemyFight", "GuardOT_HouseMercenDie");
        break;
		
		case "GuardOT_WillyGetReady":
			sld = characterFromId("Willy");
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, false);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 10, true, "GuardOT_WillyEscape"); // скрытое бессмертие
			DoQuestFunctionDelay("GuardOT_WillyMushketerFree", 3.0);
        break;
		
		case "GuardOT_WillyEscape":
			iTemp = 0;
			sld = characterFromId("Willy");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "IslaDeVieques_HouseEntrance", "quest", "teleport");
			LAi_LockFightMode(sld, true);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "IslaDeVieques_Jungle_01", "rld", "loc1", "", -1);
			for(i=1; i<=5; i++)
			{
				sld = CharacterFromID("GuardOT_willymushketer_"+i);
				if (LAi_GetCharacterHP(sld) <= 0) iTemp++;
			}
			if (iTemp > 4) DoQuestCheckDelay("GuardOT_WillyMushketerDie", 5.0);
			else LAi_group_SetCheck("EnemyFight", "GuardOT_WillyMushketerDie");
        break;
		
		case "GuardOT_WillyMushketerDie":
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Guardoftruth", "70");
			pchar.quest.GuardOT_willyescape.win_condition.l1 = "location";
			pchar.quest.GuardOT_willyescape.win_condition.l1.location = "IslaDeVieques_Jungle_01";
			pchar.quest.GuardOT_willyescape.function = "GuardOT_WillyShootInJungle";
			AddComplexSelfExpToScill(100, 100, 100, 300);
        break;
		
		case "GuardOT_WillyReadyInJungle":
			sld = characterFromId("Willy");
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, false);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 10, true, "GuardOT_WillyEscapeNext"); // скрытое бессмертие
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        break;
		
		case "GuardOT_WillyEscapeNext":
			sld = characterFromId("Willy");
			LAi_SetActorType(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "IslaDeVieques_Jungle_01", "quest", "teleport");
			LAi_LockFightMode(sld, true);
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.GuardOT_crabShore.win_condition.l1 = "location";
			pchar.quest.GuardOT_crabShore.win_condition.l1.location = "shore74";
			pchar.quest.GuardOT_crabShore.function = "GuardOT_ArchyInCrabShore";
			// эскадру Патерсона - на Крабовый остров
			Group_SetAddress("Willy_group", "IslaDeVieques", "quest_ships", "quest_ship_1");
			AddCharacterExpToSkill(pchar, "Pistol", 200);
        break;
		
		case "GuardOT_CrabShoreGuardDie":
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("Guardoftruth", "71");
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			pchar.quest.GuardOT_seekarchykey.win_condition.l1 = "item";
			pchar.quest.GuardOT_seekarchykey.win_condition.l1.item = "key_archy";
			pchar.quest.GuardOT_seekarchykey.function = "GuardOT_FindArchyKey";
			AddComplexSelfExpToScill(170, 170, 170, 170);
			AddCharacterExpToSkill(pchar, GetEquipedBladeType(pchar), 100);
        break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//Jason-------------------------------------- Коварный остров Ксочитэм ------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "Ksochitam_SitTable":
			if(CheckAttribute(pchar, "IsMushketer"))
			{
				SetMainCharacterToMushketer("", false);
			}
			ChangeCharacterAddressGroup(pchar, "SentJons_HouseF3_room", "sit", "sit1");
			LAi_SetSitType(pchar);
			DoQuestCheckDelay("Ksochitam_SitTableWaitTime", 4.0);
        break;
		
		case "Ksochitam_SitTableWaitTime":
			SetLaunchFrameFormParam("Прошло полчаса..."+ NewStr() +"Пометки на карте сделаны", "Ksochitam_RoomStandUp", 0, 5);
			WaitDate("", 0, 0, 0, 0, 30); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
        break;
		
		case "Ksochitam_RoomStandUp":
			RemoveItems(pchar, "map_normal", 1);
			GiveItem2Character(pchar, "mark_map");
			ChangeCharacterAddressGroup(pchar, "SentJons_HouseF3_room", "goto", "goto1");
			LAi_SetActorType(pchar);
			sld = characterFromId("Jino");
			LAi_SetActorType(sld);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
        break;
		
		case "Ksochitam_FindFirstWay":
			sld = ItemsFromID("mark_map");
			sld.mark = 2;
			AddQuestRecord("Ksochitam", "3");
			sld = characterFromId("Jino");
			sld.dialog.currentnode = "ksochitam_25"
			pchar.quest.Ksochitam_jinotalk1.win_condition.l1 = "location";
			pchar.quest.Ksochitam_jinotalk1.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.Ksochitam_jinotalk1.function = "Ksochitam_JinoDollyTalk";
			locations[FindLocation(pchar.location.from_sea)].DisableEncounters = true; //энкаутеры закрыть
        break;
		
		case "Ksochitam_FindSecondWay":
			sld = ItemsFromID("mark_map");
			sld.mark = 3;
			AddQuestRecord("Ksochitam", "4");
			sld = characterFromId("Jino");
			sld.dialog.currentnode = "ksochitam_29";
			pchar.quest.Ksochitam_jinotalk2.win_condition.l1 = "location";
			pchar.quest.Ksochitam_jinotalk2.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.Ksochitam_jinotalk2.function = "Ksochitam_JinoDollyTalk";
			locations[FindLocation(pchar.location.from_sea)].DisableEncounters = true; //энкаутеры закрыть
        break;
		
		case "Ksochitam_FindFullWay":
			sld = ItemsFromID("mark_map");
			sld.mark = 4;
			AddQuestRecord("Ksochitam", "5");
			sld = characterFromId("Jino");
			sld.dialog.currentnode = "ksochitam_31"
			pchar.quest.Ksochitam_jinotalk3.win_condition.l1 = "location";
			pchar.quest.Ksochitam_jinotalk3.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.Ksochitam_jinotalk3.function = "Ksochitam_JinoDollyTalk";
			locations[FindLocation(pchar.location.from_sea)].DisableEncounters = true; //энкаутеры закрыть
			DeleteAttribute(pchar, "questTemp.Ksochitam_Dolly");
			pchar.questTemp.Ksochitam = "findway";
			// открываем Ксочитэм
			i = FindIsland("Ksochitam");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			Islands[i].alwaysStorm = true; //живем в штормах
			Islands[i].storm = true;
			Islands[i].tornado = true; 
			SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 2, false); // немного развлечений
			// прерывание на выход к Ксочитэму
			pchar.quest.Ksochitam_island.win_condition.l1 = "location";
			pchar.quest.Ksochitam_island.win_condition.l1.location = "Ksochitam";
			pchar.quest.Ksochitam_island.function = "Ksochitam_ArriveIsland";
			// прерывание на высадку на Ксочитэм
			pchar.quest.Ksochitam_rockshore.win_condition.l1 = "location";
			pchar.quest.Ksochitam_rockshore.win_condition.l1.location = "shore65";
			pchar.quest.Ksochitam_rockshore.function = "Ksochitam_ArriveRockshore";
        break;
		
		case "Ksochitam_JinoStay":
			sld = characterFromId("Jino");
			LAi_SetStayType(sld);
			// кладем Молот Тора в пещеру
			sld = ItemsFromID("talisman3");
			sld.model = "torus";
			pchar.GenQuestRandItem.Ksochitam_Cave = true;
			pchar.GenQuestRandItem.Ksochitam_Cave.randitem1 = "talisman3";
			// здесь ставим все прерывания на Ксочитэм, возможные на данный момент:
			// на первую локацию джунглей
			pchar.quest.Ksochitam_adversary1.win_condition.l1 = "location";
			pchar.quest.Ksochitam_adversary1.win_condition.l1.location = "Ksochitam_Jungle_01";
			pchar.quest.Ksochitam_adversary1.win_condition = "Ksochitam_adversary1";
			// на локацию пещеры к сокровищам
			pchar.quest.Ksochitam_adversary2.win_condition.l1 = "location";
			pchar.quest.Ksochitam_adversary2.win_condition.l1.location = "Ksochitam_Grot";
			pchar.quest.Ksochitam_adversary2.win_condition = "Ksochitam_adversary2";
			// на локацию затопленной пещеры к сокровищам
			pchar.quest.Ksochitam_adversary3.win_condition.l1 = "location";
			pchar.quest.Ksochitam_adversary3.win_condition.l1.location = "Ksochitam_WaterCave";
			pchar.quest.Ksochitam_adversary3.win_condition = "Ksochitam_adversary3";
			// на локацию пещеры к маске
			pchar.quest.Ksochitam_adversary4.win_condition.l1 = "location";
			pchar.quest.Ksochitam_adversary4.win_condition.l1.location = "Ksochitam_Cave";
			pchar.quest.Ksochitam_adversary4.win_condition = "Ksochitam_adversary4";
			// на локацию затопленной пещеры к маске
			pchar.quest.Ksochitam_adversary5.win_condition.l1 = "location";
			pchar.quest.Ksochitam_adversary5.win_condition.l1.location = "Ksochitam_FloodedCave";
			pchar.quest.Ksochitam_adversary5.win_condition = "Ksochitam_adversary5";
			// на локацию тупиковой затопленной пещеры к маске
			pchar.quest.Ksochitam_adversary5_1.win_condition.l1 = "location";
			pchar.quest.Ksochitam_adversary5_1.win_condition.l1.location = "Ksochitam_FloodedCaveLock";
			pchar.quest.Ksochitam_adversary5_1.win_condition = "Ksochitam_adversary5";
			// на локацию с разбитым кораблем
			pchar.quest.Ksochitam_shoreship.win_condition.l1 = "location";
			pchar.quest.Ksochitam_shoreship.win_condition.l1.location = "Shore_ship4";
			pchar.quest.Ksochitam_shoreship.function = "Ksochitam_shoreship";
			// на локацию с Санта-Квитерией
			pchar.quest.Ksochitam_SQ.win_condition.l1 = "location";
			pchar.quest.Ksochitam_SQ.win_condition.l1.location = "Shore66";
			pchar.quest.Ksochitam_SQ.function = "Ksochitam_SQOutside";
			// на локацию со Стражем маски
			pchar.quest.Ksochitam_MaskGuard.win_condition.l1 = "location";
			pchar.quest.Ksochitam_MaskGuard.win_condition.l1.location = "Shore_mask";
			pchar.quest.Ksochitam_MaskGuard.function = "Ksochitam_MaskGuard";
			// на фальшивую маску
			pchar.quest.Ksochitam_MaskFalse.win_condition.l1 = "item";
			pchar.quest.Ksochitam_MaskFalse.win_condition.l1.item = "mask_false";
			pchar.quest.Ksochitam_MaskFalse.win_condition = "Ksochitam_FindMaskFalse";
			// на настоящую маску
			pchar.quest.Ksochitam_MaskTrue.win_condition.l1 = "item";
			pchar.quest.Ksochitam_MaskTrue.win_condition.l1.item = "mask_true";
			pchar.quest.Ksochitam_MaskTrue.win_condition = "Ksochitam_FindMaskTrue";
        break;
		
		case "Ksochitam_adversary1":
			pchar.questTemp.Ksochitam.Adversary.L1 = "true";
        break;
		
		case "Ksochitam_adversary2":
			pchar.questTemp.Ksochitam.Adversary.L2 = "true";
        break;
		
		case "Ksochitam_adversary3":
			pchar.questTemp.Ksochitam.Adversary.L3 = "true";
        break;
		
		case "Ksochitam_adversary4":
			pchar.questTemp.Ksochitam.Adversary.L4 = "true";
        break;
		
		case "Ksochitam_adversary5":
			pchar.questTemp.Ksochitam.Adversary.L5 = "true";
        break;
		
		case "Ksochitam_SQMonstersDie":
			DeleteAttribute(pchar, "questTemp.Ksochitam.ShoreShip");
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Ksochitam", "8");
			LocatorReloadEnterDisable("shore66", "reload2_back", true);
			pchar.quest.Ksochitam_SQInside.win_condition.l1 = "location";
			pchar.quest.Ksochitam_SQInside.win_condition.l1.location = "SantaQuiteriaInside";
			pchar.quest.Ksochitam_SQInside.function = "Ksochitam_SQInside";
        break;
		
		case "Ksochitam_SQCskeletcaptalk":
			for(i=2; i<=3; i++)
			{
				sld = characterFromId("SQI_skelet_"+i);
				LAi_SetActorType(sld);
			}
			DoQuestCheckDelay("hide_weapon", 1.0);
			sld = characterFromId("SQC_skeletcap");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
        break;
		
		case "Ksochitam_SQCskeletcapdie":
			LAi_group_Delete("EnemyFight");
			pchar.questTemp.Ksochitam.SantaQuiteria = "true";
			AddQuestRecord("Ksochitam", "9");
			if (CheckCharacterItem(pchar, "mask_true"))
			{
				chrDisableReloadToLocation = false;//открыть локацию
				LocatorReloadEnterDisable("shore66", "reload2_back", false);
			}
			else
			{
				pchar.GenQuest.NoDelBody = true;
			}
			// на ключ
			ChangeItemDescribe("key_archy", "itmdescr_key_mask");
			pchar.quest.Ksochitam_MaskKey.win_condition.l1 = "item";
			pchar.quest.Ksochitam_MaskKey.win_condition.l1.item = "key_archy";
			pchar.quest.Ksochitam_MaskKey.win_condition = "Ksochitam_FindMaskKey";
			// на журнал
			pchar.quest.Ksochitam_SQBook.win_condition.l1 = "item";
			pchar.quest.Ksochitam_SQBook.win_condition.l1.item = "SQCapBook";
			pchar.quest.Ksochitam_SQBook.win_condition = "Ksochitam_FindSQCapBook";
			// на скалистую бухту
			pchar.quest.Ksochitam_ReturnShip.win_condition.l1 = "location";
			pchar.quest.Ksochitam_ReturnShip.win_condition.l1.location = "Shore65";
			pchar.quest.Ksochitam_ReturnShip.function = "Ksochitam_CreateDeMaldonado";
			// делаем бухту 66 доступной для причаливания
			Island_SetReloadEnableLocal("Ksochitam", "reload_1", true);
			i = Findlocation("Shore66");
			locations[i].models.day.charactersPatch = "sandshore_patch3";
			locations[i].models.night.charactersPatch = "sandshore_patch3";	
			n = FindIsland("Ksochitam");
			Islands[n].reload.l2.label = "Shore66";
			Islands[n].reload.l2.name = "reload_1";
			Islands[n].reload.l2.go = "Shore66";
			Islands[n].reload.l2.emerge = "sea";
			Islands[n].reload.l2.radius = 600.0;
			Islands[n].reload.l2.pic = 0;
			Islands[n].reload.l2.tex = "t1";
			LAi_LocationDisableOfficersGen("Shore66", false);
			// запрещаем генерацию скелетов в Скалистой бухте
			i = Findlocation("Shore65");
			DeleteAttribute(&locations[i], "KsochitamSkeletons");
        break;
		
		case "Ksochitam_FindMaskKey":
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "GenQuest.NoDelBody");
        break;
		
		case "Ksochitam_FindSQCapBook":
			AddQuestRecord("Ksochitam", "10");
        break;
		
		case "Ksochitam_FindMaskFalse":
			if (CheckCharacterItem(pchar, "mask_true"))
			{
				AddQuestRecord("Ksochitam", "11-1");
			}
			else
			{
				AddQuestRecord("Ksochitam", "11");
				LocatorReloadEnterDisable("shore66", "reload2_back", false);
			}
        break;
		
		case "Ksochitam_MaldonadoDie":
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Shore65", "reload2_back", true);
			AddQuestRecord("Ksochitam", "14");
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary");
			sld = characterFromId("Jino");
			sld.dialog.currentnode = "adversary_6";
			pchar.quest.Ksochitam_MaldonadoSquadron.win_condition.l1 = "location";
			pchar.quest.Ksochitam_MaldonadoSquadron.win_condition.l1.location = "Ksochitam";
			pchar.quest.Ksochitam_MaldonadoSquadron.function = "Ksochitam_CreateMaldonadoSquadron";
        break;
		
		case "Ksochitam_GuardCryptRotate":
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 1700);
			DoQuestCheckDelay("Ksochitam_GoGuardCryptMask", 9.5);
        break;
		
		case "Ksochitam_GoGuardCryptMask":
			locCameraResetState();
			LAi_ActorGoToLocator(pchar, "goto", "back", "Ksochitam_GuardCryptRotateNext", -1);
        break;
		
		case "Ksochitam_GuardCryptRotateNext":
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1700);
			DoQuestCheckDelay("Ksochitam_GuardCryptBack", 4.0);
        break;
		
		case "Ksochitam_GuardCryptBack":
			iRank = MOD_SKILL_ENEMY_RATE*3+30;
			iTemp = MOD_SKILL_ENEMY_RATE*250+500;
			fMft = 1.0+MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("GuardMask", "giant", "skeleton", "giant", iRank, PIRATE, -1, true, "quest"));
			SetSelfSkill(sld, 100, 100, 100, 100, 100);
			GiveItem2Character(sld, "blade_33");
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			sld.equip.blade = "blade_33";
			sld.name = "Страж Маски";
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Sharlie\Ksochitam.c";
			sld.dialog.currentnode = "guardmask";
			SetSPECIAL(sld, 10, 10, 10, 10, 10, 10, 10);
			SelAllPerksToChar(sld, false);
			LAi_SetHP(sld, iTemp, iTemp);
			sld.MultiFighter = fMft; // мультифайтер
			sld.GuardMask = true;
			sld.PoisonResistent = true; // Addon 2016-1 Jason пиратская линейка патч 17/1
			TakeNItems(sld, "icollection", 5);
			LAi_SetCheckMinHP(sld, sti(LAi_GetCharacterHP(sld)/2), true, "Ksochitam_GuardMaskAddSkeletonsFirst");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore_mask", "quest", "guardmask");
			DoQuestCheckDelay("Ksochitam_GuardMaskGo", 1.5);
        break;
		
		case "Ksochitam_GuardMaskGo":
			sld = characterFromId("GuardMask");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "detector", "Ksochitam_TurnToGuardMask", -1);
        break;
		
		case "Ksochitam_TurnToGuardMask":
			locCameraResetState();
			LAi_ActorTurnToLocator(pchar, "goto", "rotate"); 
			sld = characterFromId("GuardMask");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "rotate", "Ksochitam_GuardMaskTalk", -1);
        break;
		
		case "Ksochitam_GuardMaskTalk":
			LAi_SetPlayerType(pchar);
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;
			sld = characterFromId("GuardMask");
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
        break;
		
		case "Ksochitam_GuardMaskAddSkeletonsFirst":
			log_testinfo("Первый фокус!");
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			iTotalTemp = 2;
			iGlobalTemp = 0;
			DoQuestCheckDelay("Ksochitam_ShoreMaskAddSkeletons", 1.0);
			sld = characterFromId("GuardMask");
			LAi_SetImmortal(sld, false);
			LaunchIncasFire(sld, true);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			log_info("Страж полностью восстановился!");
			LAi_SetCheckMinHP(sld, sti(LAi_GetCharacterHP(sld)/3), true, "Ksochitam_GuardMaskAddSkeletonsSecond");
        break;
		
		case "Ksochitam_ShoreMaskAddSkeletons":
			if (CheckAttribute(pchar, "questTemp.Ksochitam.GuardMaskBeat")) break;
			log_testinfo("Скелеты создаются!!");
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			if (MOD_SKILL_ENEMY_RATE < 6) iTotalTemp = iTotalTemp-1;
			iRank = 25+MOD_SKILL_ENEMY_RATE*2;
			iScl = 70;
			log_testinfo("Число скелетов: "+iTotalTemp+"");
			for (i=1; i<=iTotalTemp; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("guardmask_skelet_"+i+iGlobalTemp, "skel"+i, "skeleton", "skeleton", iRank, PIRATE, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_13","blade_10"), "pistol5", "bullet", iScl*2+100);
				GetCharacterPos(pchar, &locx, &locy, &locz);
				string locator = LAi_FindNearestFreeLocator("monsters", locx, locy, locz);
				log_testinfo("Локатор: "+locator+"");
				ChangeCharacterAddressGroup(sld, "shore_mask", "monsters", locator);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "KSOCHITAM_MONSTERS");
				CreateLocationParticles("fire_incas_Simple", "monsters", locator, 0, 0, 0, "");
			}
			DoQuestCheckDelay("Ksochitam_ShoreMaskKillSkeletons", 30.0);
        break;
		
		case "Ksochitam_ShoreMaskKillSkeletons":
			for (i=1; i<=iTotalTemp; i++)
			{
				if (GetCharacterIndex("guardmask_skelet_"+i+iGlobalTemp) != -1)
				{
					sld = characterFromId("guardmask_skelet_"+i+iGlobalTemp);
					LaunchIncasFire(sld, true);
					LAi_KillCharacter(sld);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			iGlobalTemp++;
			DoQuestCheckDelay("Ksochitam_ShoreMaskAddSkeletons", 3.0);
        break;
		
		case "Ksochitam_GuardMaskAddSkeletonsSecond":
			log_testinfo("Второй фокус!");
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			if (MOD_SKILL_ENEMY_RATE > 2) iTotalTemp = 3;
			sld = characterFromId("GuardMask");
			LAi_SetImmortal(sld, false);
			LaunchIncasFire(sld, true);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			log_info("Страж полностью восстановился!");
			LAi_SetCheckMinHP(sld, 300, true, "Ksochitam_GuardMaskAddSkeletonsThird");
			DoQuestFunctionDelay("Ksochitam_GuardMaskFlash", 0.5);
        break;
		
		case "Ksochitam_GuardMaskAddSkeletonsThird":
			log_testinfo("Третий фокус!");
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			sld = characterFromId("GuardMask");
			LAi_SetImmortal(sld, false);
			RemoveItems(sld, "icollection", 5);
			CheckAndSetOverloadMode(sld);
			if (MOD_SKILL_ENEMY_RATE > 6) iTotalTemp = 4;
			LaunchIncasFire(sld, true);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			log_info("Страж полностью восстановился!");
			LAi_SetCheckMinHP(sld, 100, true, "Ksochitam_GuardMaskFinalBattle");
        break;
		
		case "Ksochitam_GuardMaskFinalBattle":
			DoQuestCheckDelay("Ksochitam_ShoreMaskKillSkeletons", 0.1);
			pchar.questTemp.Ksochitam.GuardMaskBeat = "true";
			DeleteAttribute(pchar, "questTemp.Ksochitam.GuardMaskFight");
			sld = characterFromId("GuardMask");
			LAi_SetImmortal(sld, false);
			sld.dialog.currentnode = "guardmask_4";
			LaunchIncasFire(sld, true);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			log_info("Страж полностью восстановился!");
			LAi_SetActorType(sld);
			DoQuestCheckDelay("hide_weapon", 1.0);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			LAi_ActorDialogDelay(sld, pchar, "", 2.0);
			DoQuestFunctionDelay("Ksochitam_SetMusic", 1.2);
        break;
		
		case "Ksochitam_GuardMaskGift":
			LaunchIncasFire(pchar, true);
			PlaySound("interface\notebook.wav");
			if (AddSPECIALValue(pchar, SPECIAL_S, 0) != SPECIAL_MAX)
			{
				log_info("Вы чувствуете себя сильнее");
				AddSPECIALValue(pchar, SPECIAL_S, 1);
			}
			if (AddSPECIALValue(pchar, SPECIAL_E, 0) != SPECIAL_MAX)
			{
				log_info("Вы чувствуете себя более выносливым");
				AddSPECIALValue(pchar, SPECIAL_E, 1);
			}
			if (AddSPECIALValue(pchar, SPECIAL_A, 0) != SPECIAL_MAX)
			{
				log_info("Вы чувствуете себя более ловким");
				AddSPECIALValue(pchar, SPECIAL_A, 1);
			}
			DoQuestCheckDelay("Ksochitam_GuardMaskGiftComplete", 3.0);
			DoQuestFunctionDelay("Ksochitam_SetMusic", 0.5);
			AddComplexSelfExpToScill(450, 450, 450, 450);
		break;
		
		case "Ksochitam_GuardMaskGiftComplete":
			LAi_SetPlayerType(pchar);
			sld = characterFromId("GuardMask");
			sld.dialog.currentnode = "guardmask_13";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;
		
		case "Ksochitam_GuardMaskGoAway":
			LAi_SetActorType(pchar);
			sld = characterFromId("GuardMask");
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_ActorGoToLocator(sld, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz), "Ksochitam_GuardMaskGoAway1", -1);
        break;
		
		case "Ksochitam_GuardMaskGoAway1":
			sld = characterFromId("GuardMask");
			LaunchIncasFire(sld, true);
			LAi_ActorTurnToCharacter(pchar, sld);
			DoQuestCheckDelay("Ksochitam_GuardMaskDisappear", 1.5);
        break;
		
		case "Ksochitam_GuardMaskDisappear":
			sld = characterFromId("GuardMask");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			// увеличиваем локатор с маской и вертаем тип локации
			n = Findlocation("Shore_mask");
			locations[n].type = "x_seashore";
			locations[n].locators_radius.item.item1 = 1.2;
			DoQuestCheckDelay("Ksochitam_ShoreMaskReload", 2.5);
			LAi_group_NotFightPlayerVSGroup("KSOCHITAM_MONSTERS");
        break;
		
		case "Ksochitam_ShoreMaskReload":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar);
			DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
			AddQuestRecord("Ksochitam", "12");
        break;
		
		case "Ksochitam_FindMaskTrue":
			if (CheckCharacterItem(pchar, "mask_false"))
			{
				AddQuestRecord("Ksochitam", "13-1");
			}
			else
			{
				AddQuestRecord("Ksochitam", "13");
			}
			chrDisableReloadToLocation = false;//открыть локацию
        break;
		
		case "Ksochitam_JinoNormal":
			sld = characterFromId("Jino");
			LAi_SetOwnerType(sld);
        break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//Jason----------------------------------- Древний город майя --------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "Tieyasal_VinsentoGo": // запускаем квест
			sld = characterFromId("Vincento");
			LAi_SetHuberType(sld);
			ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "sit", "armchair1");
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			chrDisableReloadToLocation = false;//открыть локацию
			SetFunctionTimerCondition("Tieyasal_TotalOver", 0, 0, 120, false); // глобальный таймер квеста - 120 дней на выполнение - потом геймовер
			SetFunctionTimerCondition("Tieyasal_SetAdrianInChapel", 0, 0, 5, false);
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", false); // пускать офицеров в локу телепорта
			pchar.questTemp.Tieyasal = "begin"; // далее - на Исла Тесоро
			AddQuestRecord("Tieyasal", "1");
        break;
		
		case "Tieyasal_MCSoldiersReset": // 160912
			chrDisableReloadToLocation = false;//открыть локацию
			for(i=1; i<=iTotalTemp; i++)
			{
				if (GetCharacterIndex("Tieyasal_Oursoldier_"+i) != -1)
				{
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			AddQuestRecord("Tieyasal", "9");
        break;
		
		case "Tieyasal_PrepareDichosoTrap":
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) AddQuestRecord("Tieyasal", "8");
			else AddQuestRecord("Tieyasal", "7");
			pchar.quest.Tieyasal_Dichososhore.win_condition.l1 = "location";
			pchar.quest.Tieyasal_Dichososhore.win_condition.l1.location = "Shore42";
			pchar.quest.Tieyasal_Dichososhore.function = "Tieyasal_ArriveToNevis";
			locations[FindLocation("Shore42")].DisableEncounters = true; //энкаутеры закрыть
        break;
		
		case "Tieyasal_CryptBattleComplete":
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) AddQuestRecord("Tieyasal", "11");
			else AddQuestRecord("Tieyasal", "10");
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			pchar.GenQuest.NoDelBody = true;
        break;
		
		case "Tieyasal_GraveyardBattleComplete":
			chrDisableReloadToLocation = false;//открыть локацию
			locations[FindLocation("Shore42")].DisableEncounters = false; 
			locations[FindLocation("Charles_exittown")].DisableEncounters = false; 
			locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = false; 
			for(i=2; i<=4; i++)
			{
				locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = false;
			}
			LocatorReloadEnterDisable("Shore42", "boat", false);
			for(i=1; i<=iTotalTemp; i++)
			{
				if (GetCharacterIndex("Tieyasal_Oursoldier_"+i) != -1)
				{
					sld = characterFromID("Tieyasal_Oursoldier_"+i);
					sld.lifeday = 0;
				}
			}
			pchar.quest.Tieyasal_Cabinthink.win_condition.l1 = "location";
			pchar.quest.Tieyasal_Cabinthink.win_condition.l1.location = "Nevis";
			pchar.quest.Tieyasal_Cabinthink.function = "Tieyasal_TalkSelfInCabin";
			AddQuestRecord("Tieyasal", "14");
        break;
		
		case "Tieyasal_PrepareCabinTalk":
			chrDisableReloadToLocation = true;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
        break;
		
		case "Tieyasal_AfterCabinTalk":
			// снимаем все запреты
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Nevis", true);
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			bDisableCharacterMenu = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			if (pchar.questTemp.Tieyasal_CabinTalk == "calendar")
			{
				pchar.questTemp.Tieyasal = "calendar";
				AddQuestRecord("Tieyasal", "15");
			}
			else
			{
				pchar.questTemp.Tieyasal = "trip";
				AddQuestRecord("Tieyasal", "16");
			}
			pchar.quest.Tieyasal_TripStart.win_condition.l1 = "location";
			pchar.quest.Tieyasal_TripStart.win_condition.l1.location = "Shore_ship2";
			pchar.quest.Tieyasal_TripStart.function = "Tieyasal_TripStartInShore";
			pchar.quest.Tieyasal_Landway.win_condition.l1 = "location";
			pchar.quest.Tieyasal_Landway.win_condition.l1.location = "Tenochtitlan";
			pchar.quest.Tieyasal_Landway.function = "Tieyasal_SetUrakanItzaWarrior";
			LocatorReloadEnterDisable("Tayasal_jungle_09", "reload3_back", false); // открываем проход в Тайясаль
			LocatorReloadEnterDisable("Tayasal_jungle_07", "reload2_back", false); // patch-5
			DeleteAttribute(pchar, "questTemp.Tieyasal_CabinTalk");
        break;
		
		case "Tieyasal_TeleportArrive":
			Dolly_TeleportConsequences(); // последствия
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Ground_sitting", "LSC_TeleportArrive_1", 3.0);
			pchar.questTemp.Tieyasal.Teleport = "true";
			// ставим офицеров, если такие были
			for(i=1; i<=3; i++)
			{
				int idx = GetOfficersIndex(pchar, i);
				if(idx < 0) continue;
				sld = &Characters[idx];
				if (CheckAttribute(sld, "quest.teleportation"))
				{
					ChangeCharacterAddressGroup(sld, "Tenochtitlan", "officers", "reload1_"+i);
					if (CheckCharacterItem(sld, "Ultimate_potion"))
					{
						sTemp = "";
						if (sld.sex == "woman") sTemp = "а";
						RemoveItems(sld, "Ultimate_potion", 1);
						Log_Info("Абордажник "+GetFullName(sld)+" использовал"+sTemp+" зелье команчей");
					}
					else
					{
						sTemp = "";
						if (sld.sex == "woman") sTemp = "ла";
						LAi_KillCharacter(sld);
						Log_Info("Абордажник "+GetFullName(sld)+" умер"+sTemp+" из-за отсутствия зелья команчей");
					}
				}
			}
        break;
		
		case "Tieyasal_ItzaWarriorPause":
			if (pchar.questTemp.Tieyasal.ItzaWarrior == "1") DoQuestCheckDelay("Tieyasal_CreateItzaWarriorSecondGroup", 7.0);
			else DoQuestCheckDelay("Tieyasal_CreateItzaWarriorThirdGroup", 9.0);
        break;
		
		case "Tieyasal_CreateItzaWarriorSecondGroup":
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromId("Itza_"+pchar.questTemp.Tieyasal.ItzaWarrior+"Group_"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			LAi_group_Delete("ITZA");
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			iRank = 25+MOD_SKILL_ENEMY_RATE*2;
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Itza_2Group_"+i, "itza_"+(rand(7)+1), "man", "man", iRank, PIRATE, -1, false, "native"));
				FantomMakeCoolFighter(sld, iRank, 80, 80, RandPhraseSimple("topor_01","blade_02"), "pistol1", "bullet", 70);
				GetCharacterPos(pchar, &locx, &locy, &locz);
				ChangeCharacterAddressGroup(sld, "Tenochtitlan", "rld", LAi_FindFarLocator("rld", locx, locy, locz));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "ITZA");
			}
			LAi_group_SetRelation("ITZA", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ITZA", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ITZA", "Tieyasal_ItzaWarriorPause");
			pchar.questTemp.Tieyasal.ItzaWarrior = "2";
        break;
		
		case "Tieyasal_CreateItzaWarriorThirdGroup":
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromId("Itza_"+pchar.questTemp.Tieyasal.ItzaWarrior+"Group_"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			LAi_group_Delete("ITZA");
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			iRank = 28+MOD_SKILL_ENEMY_RATE*2;
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Itza_3Group_"+i, "itza_"+(rand(7)+1), "man", "man", iRank, PIRATE, -1, false, "native"));
				FantomMakeCoolFighter(sld, iRank, 85, 85, RandPhraseSimple("topor_01","blade_02"), "pistol5", "bullet", 100);
				GetCharacterPos(pchar, &locx, &locy, &locz);
				ChangeCharacterAddressGroup(sld, "Tenochtitlan", "rld", LAi_FindFarLocator("rld", locx, locy, locz));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "ITZA");
			}
			LAi_group_SetRelation("ITZA", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ITZA", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ITZA", "Tieyasal_ItzaWarriorDie");
        break;
		
		case "Tieyasal_ItzaWarriorDie":
			pchar.quest.Tieyasal_mushketfire.over = "yes"; //снять прерывание
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			DoQuestCheckDelay("hide_weapon", 0.8);
			sld = characterFromId("Urakan");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "urakan", "Tieyasal_UrakanTalk", -1);
			AddComplexSelfExpToScill(50, 50, 50, 50);
        break;
		
		case "Tieyasal_UrakanTalk":
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromId("Itza_3Group_"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			// закрываем все храмовые локаторы кроме низа большого храма, чтобы не лез раньше времени
			for(i=1; i<=37; i++)
			{
				LocatorReloadEnterDisable("Tenochtitlan", "reloadTemple"+i, true);
			}
			LocatorReloadEnterDisable("Tenochtitlan", "reloadU1_back", true);
			LocatorReloadEnterDisable("Tenochtitlan", "reloadU2_back", true);
			sld = characterFromId("Urakan");
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			for(i=1; i<=2; i++)
			{
				sld = characterFromId("Bridge_itza_"+i);
				LAi_SetActorType(sld);
			}
			LAi_group_Delete("TMP_FRIEND");
			// ставим ица-горожан
			for(i=1; i<=12; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Itza_ctz_"+i, "itza_"+(rand(7)+1), "man", "man", 30, PIRATE, -1, false, "native"));
				FantomMakeCoolFighter(sld, 30, 100, 100, RandPhraseSimple("blade_01","blade_02"), "", "", 150);
				sld.name = GetIndianName(MAN);
				sld.lastname = "";
				sld.dialog.FileName = "Quest\Sharlie\Itza.c";
				sld.dialog.currentnode = "itza_ctz";
				sld.greeting = "indian_male";
				ChangeCharacterAddressGroup(sld, "Tenochtitlan", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
				LAi_group_SetRelation("TMP_FRIEND", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
			}
        break;
		
		case "Tieyasal_MishelleTalkActivation":
			sld = characterFromId("Mishelle");
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
        break;
		
		case "Tieyasal_TempleGuardDie":
			sld = characterFromId("Mishelle");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "ITZA");
			LAi_group_SetRelation("ITZA", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ITZA", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(sld, 200, true, "Tieyasal_RunSecondFloor");
        break;
		
		case "Tieyasal_RunSecondFloor":
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			pchar.GenQuest.CantRun = true;
			CheckAndSetOverloadMode(GetMainCharacter()); // бег запрещаем
			sld = characterFromId("Mishelle");
			LAi_SetFightMode(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "quest", "detector1", "none", "", "", "", 20);
			DoQuestCheckDelay("Tieyasal_RunSecondFloor1", 2.0);
			// прерывание
			pchar.quest.Tieyasal_2floor.win_condition.l1 = "locator";
			pchar.quest.Tieyasal_2floor.win_condition.l1.location = "Temple_great";
			pchar.quest.Tieyasal_2floor.win_condition.l1.locator_group = "quest";
			pchar.quest.Tieyasal_2floor.win_condition.l1.locator = "detector1";
			pchar.quest.Tieyasal_2floor.function = "Tieyasal_SecondFloorActivate";// patch-4
        break;
		
		case "Tieyasal_RunSecondFloor1":
			sld = characterFromId("Mishelle");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "quest", "detector1", "none", "", "", "Tieyasal_SecondFloorAttack", 20);
        break;
		
		case "Tieyasal_SecondFloorAttack":
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter()); // бег разрешаем
			DeleteAttribute(pchar, "questTemp.Tieyasal.LockLadder"); // открываем лестницу
			// ставим клона-мушкетера Мишеля
			sld = GetCharacter(NPC_GenerateCharacter("Mishelle_mushketer", "Migel_2_mush", "man", "mushketer", 60, PIRATE, -1, false, "quest"));
			FantomMakeCoolFighter(sld, 60, 100, 100, "", "mushket2x2", "cartridge", 150);
			LAi_SetHP(sld, 1000+MOD_SKILL_ENEMY_RATE*200, 1000+MOD_SKILL_ENEMY_RATE*200);
			SetSelfSkill(sld, 100, 100, 100, 100, 100);
			sld.name = "Мишель";
			sld.lastname = "де Монпе"; // патч 17/1
			LAi_SetImmortal(sld, false);
			ChangeCharacterAddressGroup(sld, "Temple_great", "quest", "mushketer");
			sld.MusketerDistance = 0;
			sld.PoisonResistent = true; // Addon 2016-1 Jason пиратская линейка патч 17/1
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, false);
			iTemp = MOD_SKILL_ENEMY_RATE;
			TakeNItems(sld, "potion2", iTemp);
			TakeNItems(sld, "cartridge", 50);
			TakeNItems(sld, "bullet", 50);
			TakeNItems(sld, "gunpowder", 50);
			LAi_SetCheckMinHP(sld, 150, true, "Tieyasal_RunThirdFloor");
			pchar.questTemp.Tieyasal.Shooter = "true"; // устанавливаем защиту
			// ставим мушкетеров ица
			iRank = 30+MOD_SKILL_ENEMY_RATE*2;
			for(i=5; i<=6; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Warrior_itza_mush_"+i, "mush_itza_"+(rand(2)+1), "man", "mushketer", iRank, PIRATE, -1, false, "quest"));
				FantomMakeCoolFighter(sld, iRank, 100, 100, "", "mushket1", "cartridge", 120);
				ChangeCharacterAddressGroup(sld, "Temple_great", "monsters", "mushketer"+i);
				sld.MusketerDistance = 0;
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_warrior_DialogEnable(sld, false);
			}
			// ставим воинов ица
			iTotalTemp = 5+makeint(MOD_SKILL_ENEMY_RATE/3);
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Warrior_itza_"+i, "itza_"+i, "man", "man", iRank, PIRATE, -1, false, "native"));
				FantomMakeCoolFighter(sld, iRank, 100, 100, RandPhraseSimple("topor_01","blade_02"), "", "", 120);
				ChangeCharacterAddressGroup(sld, "Temple_great", "monsters", "warrior"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_warrior_DialogEnable(sld, false);
			}
			// добавочная группа ица
			for(i=11; i<=14; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Warrior_itza_"+i, "itza_"+(i-7), "man", "man", iRank, PIRATE, -1, false, "native"));
				FantomMakeCoolFighter(sld, iRank, 90, 90, RandPhraseSimple("topor_01","blade_02"), "", "", 100);
				ChangeCharacterAddressGroup(sld, "Temple_great", "monsters", "warrior"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "Tieyasal_AddingGroupActivate"); // patch-4
			}
        break;
		
		case "Tieyasal_AddingGroupActivate": // 160912
			pchar.quest.Tieyasal_2floor_add.over = "yes"; //снять прерывание
			for(i=11; i<=14; i++)
			{
				sld = characterFromId("Warrior_itza_"+i);
				LAi_RemoveCheckMinHP(sld);
				LAi_group_MoveCharacter(sld, "ITZA");
			}
			LAi_group_SetRelation("ITZA", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			//LAi_group_FightGroups("ITZA", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ITZA", "Tieyasal_FloorWarriorDie");
        break;
		
		case "Tieyasal_RunThirdFloor":
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			sld = characterFromId("Mishelle_mushketer");
			sld.lifeday = 0;
			LAi_LockFightMode(sld, true);
			LAi_group_MoveCharacter(sld, "TMP_FRIEND");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("Mishelle");
			ChangeCharacterAddressGroup(sld, "Temple_great", "quest", "mushketer");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, "TMP_FRIEND");
			LAi_ActorRunToLocation(sld, "quest", "detector3", "none", "", "", "", -1);
			DeleteAttribute(pchar, "questTemp.Tieyasal.Shooter");
        break;
		
		case "Tieyasal_FloorWarriorDie":
			iRank = 30+MOD_SKILL_ENEMY_RATE*2;
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			n = 3+makeint(MOD_SKILL_ENEMY_RATE/5);
			n = n+14;
			for(i=15; i<=n; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Warrior_itza_"+i, "itza_"+(rand(7)+1), "man", "man", iRank, PIRATE, -1, false, "native"));
				FantomMakeCoolFighter(sld, iRank, 95, 95, "topor_01", "", "", 150);
				ChangeCharacterAddressGroup(sld, "Temple_great", "monsters", "warrior"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "ITZA");
			}
			LAi_group_SetRelation("ITZA", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ITZA", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ITZA", "Tieyasal_TempleWarriorDie");
        break;
		
		case "Tieyasal_TempleWarriorDie":
			DeleteAttribute(pchar, "questTemp.Tieyasal.LockGate");
			sld = characterFromId("Mishelle");
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			ChangeCharacterAddressGroup(sld, "Temple_great", "quest", "top");
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			iTemp = MOD_SKILL_ENEMY_RATE/2;
			TakeNItems(sld, "potion2", iTemp);
			LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)/2, false, "Tieyasal_TopAddWarrior");
			iRank = 32+MOD_SKILL_ENEMY_RATE*2;
			for(i=1; i<=5; i++)
			{
				if (i == 4)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Top_itza_"+i, "mush_itza_"+(rand(2)+1), "man", "mushketer", iRank, PIRATE, -1, false, "quest"));
					FantomMakeCoolFighter(sld, iRank, 100, 100, "", "mushket2x2", "cartridge", 150);
					sld.MusketerDistance = 0;
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("Top_itza_"+i, "itza_"+i, "man", "man", iRank, PIRATE, -1, false, "native"));
					FantomMakeCoolFighter(sld, iRank, 100, 100, "topor_01", "", "", 100);
				}
				ChangeCharacterAddressGroup(sld, "Temple_great", "monsters", "top"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_warrior_DialogEnable(sld, false);
			}
			// прерывание
			pchar.quest.Tieyasal_3floor.win_condition.l1 = "locator";
			pchar.quest.Tieyasal_3floor.win_condition.l1.location = "Temple_great";
			pchar.quest.Tieyasal_3floor.win_condition.l1.locator_group = "quest";
			pchar.quest.Tieyasal_3floor.win_condition.l1.locator = "detector3";
			pchar.quest.Tieyasal_3floor.function = "Tieyasal_ThirdFloorActivate";
        break;
		
		case "Tieyasal_TopAddWarrior":
			PlaySound("interface\abordage_wining.wav");
			// добавочная группа ица
			iRank = 32+MOD_SKILL_ENEMY_RATE*2;
			n = 2+makeint(MOD_SKILL_ENEMY_RATE/5);
			n = n+10;
			for(i=11; i<=n; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Top_itza_add_"+i, "itza_"+(rand(7)+1), "man", "man", iRank, PIRATE, -1, false, "native"));
				FantomMakeCoolFighter(sld, iRank, 100, 100, "topor_01", "", "", 150);
				ChangeCharacterAddressGroup(sld, "Temple_great", "monsters", "warrior"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "ITZA");
			}
			sld = characterFromId("Mishelle");
			LAi_SetCheckMinHP(sld, 100, true, "Tieyasal_TempleFinalTalk");
        break;
		
		case "Tieyasal_TempleFinalTalk":
			// деактивируем оставшихся в живых индеев
			for(i=1; i<=5; i++)
			{
				sld = characterFromId("Top_itza_"+i);
				if (LAi_GetCharacterHP(sld) > 0)
				{
					LAi_SetActorType(sld);
					LAi_ActorRunToLocation(sld, "quest", "detector3", "none", "", "", "", 5.0);
				}
			}
			n = 2+makeint(MOD_SKILL_ENEMY_RATE/5);
			n = n+10;
			for(i=11; i<=n; i++)
			{
				sld = characterFromId("Top_itza_add_"+i);
				if (LAi_GetCharacterHP(sld) > 0)
				{
					LAi_SetActorType(sld);
					LAi_ActorRunToLocation(sld, "quest", "detector3", "none", "", "", "", 5.0);
				}
			}
			DoQuestCheckDelay("hide_weapon", 0.5);
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_twice";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
//			LAi_group_Delete("ITZA");  // дает вылет в хардкор режиме
        break;
		
		case "Tieyasal_KukulkanKick":
			sld = characterFromId("Mishelle");
			LAi_SetActorType(sld);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LaunchBlast(sld);
			LaunchBlood(pchar, 1.8, true, "fire");
			Pchar.chr_ai.hp = stf(Pchar.chr_ai.hp)/5;
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "jump", "Tieyasal_SitInTemple", 0.5);
			PlaySound("People Fight\Death_NPC_08.wav");
        break;
		
		case "Tieyasal_SitInTemple":
			GetCharacterPos(pchar, &locx, &locy, &locz);
			locator = LAi_FindFarLocator("sit", locx, locy, locz);
			ChangeCharacterAddressGroup(pchar, "Temple_great", "sit", locator);
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Ground_sitting", "", 2.5);
			DoQuestFunctionDelay("Tieyasal_StandUpInTemple", 2.5);
			LaunchBlood(pchar, 1.0, true, "fight");
			// запрещаем сохранение и интерфейсы, снимаем оружие
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			// ставим Мишеля, Канека и Уракана
			sld = characterFromId("Mishelle");
			LAi_ActorGoToLocator(sld, "goto", "stay1", "", -1);
			sld = characterFromId("Urakan");
			ChangeCharacterAddressGroup(sld, "Temple_great", "reload", "reload1");
			LAi_ActorGoToLocator(sld, "goto", "stay2", "", -1);
			sld = characterFromId("Kanek");
			ChangeCharacterAddressGroup(sld, "Temple_great", "quest", "detector3");
			LAi_ActorRunToLocator(sld, "goto", "stay3", "", -1);
			// убираем офицеров
			i = Findlocation("Tenochtitlan");
			DeleteAttribute(&locations[i], "setquestofficers");
        break;
		
		case "Tieyasal_Fail_ReloadTown":
			DoQuestReloadToLocation("Tenochtitlan", "reload", "reloadTemple33", "Tieyasal_Fail_GoToTown");
        break;
		
		case "Tieyasal_Fail_GoToTown":
			chr = characterFromId("Mishelle");
			LAi_SetActorType(chr);
			ChangeCharacterAddressGroup(chr, "Tenochtitlan", "reload", "reloadTemple32");
			LAi_ActorGoToLocation(chr, "reload", "reloadTemple31", "Temple_round", "quest", "kukulkan", "Tieyasal_Fail_GoToRoundTemple", -1);
			sld = characterFromId("Urakan");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tenochtitlan", "reload", "reloadTemple34");
			LAi_ActorFollow(sld, chr, "", -1);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tenochtitlan", "reload", "reloadTemple32");
			LAi_ActorFollow(sld, chr, "", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, chr, "", -1);
        break;
		
		case "Tieyasal_Fail_GoToRoundTemple":
			DoQuestReloadToLocation("Temple_round", "quest", "hero", "Tieyasal_Fail_IntoRoundTemple");
        break;
		
		case "Tieyasal_Fail_IntoRoundTemple":
			LAi_SetActorType(pchar);
			sld = characterFromId("Urakan");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Temple_round", "quest", "urakan");
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Temple_round", "quest", "kanek");
			DoQuestCheckDelay("Tieyasal_Fail_RoundTempleRotate", 2.0);
        break;
		
		case "Tieyasal_Fail_RoundTempleRotate":
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 1700);
			DoQuestCheckDelay("Tieyasal_Fail_RoundTempleStop", 9.5);
        break;
		
		case "Tieyasal_Fail_RoundTempleStop":
			locCameraResetState();
			DoQuestCheckDelay("Tieyasal_Fail_KanekBead", 2.0);
        break;
		
		case "Tieyasal_Fail_KanekBead":
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "bead", "", 11.0);
			DoQuestCheckDelay("Tieyasal_Fail_DollyActivation", 11.0);
			PlaySound("Voice\Russian\sharlie\Kanek.wav");
			LAi_ActorTurnToCharacter(pchar, sld);
        break;
		
		case "Tieyasal_Fail_DollyActivation":
			CreateLocationParticles("fire_incas_Simple", "item", "dolly", 0.5, 0, 0, "");
			CreateLocationParticles("fire_incas_Simple", "item", "dolly", 1.0, 0, 0, "");
			CreateLocationParticles("fire_incas_Simple", "item", "dolly", 1.5, 0, 0, "");
			CreateLocationParticles("shadowstar", "shadowstar", "shadowstar1", 0, 0, 0, "");
			CreateLocationParticles("Firering", "item", "dolly", 1.0, 0, 0, "");
			DoQuestCheckDelay("Tieyasal_Fail_LastTalk", 4.0);
			LAi_ActorTurnToLocator(pchar, "item", "dolly");
        break;
		
		case "Tieyasal_Fail_KanekPlace":
			CreateLocationParticles("shadowstar", "shadowstar", "shadowstar1", 0, 0, 0, "");
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "kanek", "Tieyasal_Fail_LastTalk", -1);
        break;
		
		case "Tieyasal_Fail_LastTalk":
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_fail_8";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
        break;
		
		case "Tieyasal_Fail_TeleportStart":
			SetMusic("music_teleport");
			PlaySound("interface\notebook.wav");
			for (i=1; i<=6; i++)
			{
				CreateLocationParticles("shadowstar", "goto", "goto"+i, 1.0, 0, 0, "");
			}
			DoQuestCheckDelay("Tieyasal_Fail_TeleportContinue_1", 7.0);
        break;
		
		case "Tieyasal_Fail_TeleportContinue_1":
			PlaySound("Weather\Thunder_Q.wav");
			CreateLocationParticles("shadowstar", "shadowstar", "shadowstar1", 0, 0, 0, "");
			for (i=1; i<=6; i++)
			{
				CreateLocationParticles("fire_incas", "goto", "goto"+i, 1.0, 0, 0, "");
			}
			DoQuestCheckDelay("Tieyasal_Fail_TeleportContinue_2", 7.0);
        break;
		
		case "Tieyasal_Fail_TeleportContinue_2":
			CreateLocationParticles("Firering", "item", "dolly", 1.0, 0, 0, "");
			for (i=1; i<=6; i++)
			{
				CreateLocationParticles("shadowstar", "goto", "goto"+i, 1.0, 0, 0, "");
			}
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			DoQuestCheckDelay("Tieyasal_Fail_TeleportContinue_3", 6.0);
        break;
		
		case "Tieyasal_Fail_TeleportContinue_3":
			sld = characterFromId("Mishelle");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			DoQuestCheckDelay("Tieyasal_Fail_TeleportContinue_4", 3.0);
        break;
		
		case "Tieyasal_Fail_TeleportContinue_4":
			PlaySound("Weather\Thunder_Q.wav");
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			CreateLocationParticles("shipfire", "quest", "hero", 1.0, 0, 0, "");
			CreateLocationParticles("shipfire", "quest", "kukulkan", 1.0, 0, 0, "");
			CreateLocationParticles("shipfire", "quest", "urakan", 1.0, 0, 0, "");
			CreateLocationParticles("shipfire", "quest", "kanek", 1.0, 0, 0, "");
			PlaySound("Weather\koster_001.wav");
			for (i=1; i<=6; i++)
			{
				CreateLocationParticles("shipfire", "goto", "goto"+i, 1.0, 0, 0, "");
				for (n=1; n<=6; n++)
				{
					CreateLocationParticles("shadowstar", "goto", "goto"+i, 1.0, 0, 0, "");
				}
			}
			for (n=1; n<=10; n++)
			{
				CreateLocationParticles("shadowstar", "shadowstar", "shadowstar1", 0, 0, 0, "");
			}
			DoQuestCheckDelay("Tieyasal_Fail_TeleportContinue_5", 7.0);
        break;
		
		case "Tieyasal_Fail_TeleportContinue_5":
			sld = characterFromId("Kanek");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("Urakan");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			RemoveAllCharacterItems(pchar, true);
			GiveItem2Character(pchar, "blade_13");
			EquipCharacterbyItem(pchar, "blade_13");
			GiveItem2Character(pchar, "pistol5");
			EquipCharacterbyItem(pchar, "pistol5");
			TakeNItems(pchar, "grapeshot", 50);
			AddItems(pchar, "bullet", 50);
			TakeNItems(pchar, "potion2", 3);
			LAi_SetCharacterUseBullet(pchar, "bullet");
			ChangeCharacterAddressGroup(pchar, "none", "", "");
			CreateLocationParticles("shadowstar_Big", "item", "dolly", 1.5, 0, 0, "");
			DoQuestCheckDelay("Tieyasal_Fail_TeleportContinue_6", 8.0);
        break;
		
		case "Tieyasal_Fail_TeleportContinue_6":
			SetLaunchFrameFormParam("Кукулькан ушел в прошлое..."+ NewStr() +"Вы не смогли остановить его...", "", 0, 10);
			LaunchFrameForm();
			DoQuestCheckDelay("Tieyasal_Fail_TeleportContinue_7", 10.0);
			// меняем обличье Шарля
			ChangeShowIntarface();
			pchar.model = "Dragoon_1"; 
			pchar.model.animation = "man";
			Characters_RefreshModel(PChar);
			pchar.FaceId = 555; 
			pchar.name = "капитан";
			pchar.lastname = "Гобарт";
        break;
		
		case "Tieyasal_Fail_TeleportContinue_7":
			DoQuestReloadToLocation("Estate", "quest", "hero", "Europe_SharlieFinal");
        break;
		
		case "Europe_SharlieFinal": // фэйловый финал
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			LAi_SetPlayerType(pchar);
			LAi_SetCurHPMax(pchar);
			LAi_GetCharacterMaxEnergy(pchar);
			sld = GetCharacter(NPC_GenerateCharacter("Piter", "blad_0", "man", "man", 10, ENGLAND, -1, false, "quest"));
			FantomMakeCoolFighter(sld, 10, 50, 50, "blade_12", "pistol1", "bullet", 100);
			ChangeCharacterAddressGroup(sld, "Estate", "quest", "piter");
			LAi_SetActorType(sld);
			for(i=1; i<=6; i++)
			{
				if (i == 1)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Europe_eng_"+i, "off_eng_4", "man", "man", 20, ENGLAND, -1, false, "quest"));
					FantomMakeCoolFighter(sld, 20, 50, 50, "blade_13", "pistol5", "bullet", 100);
					sld.name = "полковник";
					sld.lastname = "Кирк";
					sld.dialog.FileName = "Quest\Sharlie\OtherNPC.c";
					sld.dialog.currentnode = "Europe";
					sld.greeting = "";
					
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("Europe_eng_"+i, "sold_eng_"+(rand(7)+1), "man", "man", 20, ENGLAND, -1, false, "quest"));
					FantomMakeCoolFighter(sld, 20, 50, 50, "blade_12", "pistol1", "bullet", 100);
					LAi_CharacterDisableDialog(sld);
				}
				ChangeCharacterAddressGroup(sld, "Estate", "goto", "stay"+i);
				LAi_SetActorType(sld);
				if (i == 1) LAi_ActorDialog(sld, pchar, "", -1, 0);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
        break;
		
		case "Europe_SharlieFinal_1":
			SetMusic("music_MainMenu");
			pchar.questTemp.NoFast = true; // запрет ускорения
			pchar.questTemp.Europe = true;
			pchar.questTemp.Tieyasal_FailEnd = true; // patch
			LAi_SetPlayerType(pchar);
			DoQuestCheckDelay("TalkSelf_Quest", 0.1);
        break;
		
		case "Europe_SharlieFinal_2":
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto8", "", -1);
			for(i=2; i<=6; i++)
			{
				sld = characterFromId("Europe_eng_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
			DoQuestCheckDelay("Europe_SharlieFinal_3", 0.5);
        break;
		
		case "Europe_SharlieFinal_3":
			SetMainCharacterIndex(GetCharacterIndex("Piter"));
			PChar = GetMainCharacter();
			locCameraFlyToPosition(-22.5, 9.0, 3.25, 0, 14.0, 0.2, 0.01, -1);
			DoQuestCheckDelay("Europe_FinalFrame", 36.0);
        break;
		
		case "Europe_FinalFrame":
			SetLaunchFrameFormParam("Мир изменился, и наш герой - вместе с ним."+ NewStr() +"Но это уже совсем другая история...", "", 0, 10);
			LaunchFrameForm();
			DoQuestCheckDelay("Final_Credits", 10.0);
        break;
		
		case "Tieyasal_MishelleDie":
			SetMusic("music_teleport");
			sld = characterFromId("Mishelle");
			LAi_SetImmortal(sld, false);
			LaunchIncasFire(sld, true);
			LaunchIncasFire(sld, true);
			LaunchIncasFire(sld, true);
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			LAi_KillCharacter(sld);
			sld = characterFromId("Kanek");
			if (LAi_GetCharacterHP(sld) > 0) LAi_KillCharacter(sld);
			DoQuestFunctionDelay("Tieyasal_MishelleDie", 2.0);
			DoQuestCheckDelay("hide_weapon", 1.5);
        break;
		
		case "Tieyasal_UrakanStay":
			sld = characterFromId("Urakan");
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
        break;
		
		case "Tieyasal_MaskTerminationTurn":
			LAi_ActorTurnToLocator(pchar, "item", "button04");
			DoQuestFunctionDelay("Tieyasal_MaskTerminationGo", 3.0);
        break;
		
		case "Tieyasal_UrakanLastTalk":
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Urakan");
			sld.dialog.currentnode = "urakan_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;
		
		case "Tieyasal_FinalChoise":
			LAi_SetPlayerType(pchar);
			DoQuestCheckDelay("TalkSelf_Quest", 0.1);
        break;
		
		case "Final_ReturnToEurope": // финал - во Францию
			EndQuestMovie();
			Achievment_SetStat(pchar, 48, 1);
			pchar.GenQuest.VideoAVI = "Outro_home";
			pchar.GenQuest.VideoAfterQuest = "Final_Credits";
			DoQuestCheckDelay("PostVideo_Start", 0.2);
        break;
		
		case "Final_StayInCarribean": // финал - остаемся
			DeleteAttribute(pchar, "questTemp.Tieyasal_final");
			DeleteAttribute(pchar, "questTemp.Dolly_Tieyasal"); // прогон 4
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;
			CloseQuestHeader("Tieyasal");
			AddQuestRecord("Sharlie", "43");
			CloseQuestHeader("Sharlie");
			Achievment_SetStat(pchar, 48, 1);
			pchar.GenQuest.VideoAVI = "Outro_stay";
			PChar.GenQuest.VideoAfterQuest = "Final_ReloadShore";
			DoQuestCheckDelay("PostVideo_Start", 0.2);
			pchar.questTemp.Tieyasal_WinEnd = "true"; // patch-9
        break;
		
		case "Final_Credits":
			GameOver("complete");
        break;
		
		case "Final_ReloadShore":
			DoQuestReloadToLocation("Shore_ship2", "reload", "boat", "");
        break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//Jason---------------------------------------Вождь краснокожих-------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "RedChieftainStay":
			sld = CharacterFromID("RedChieftain");
            LAi_SetStayType(sld);
			sld.dialog.currentnode = "RedChieftain_wait_2";
        break;
		
		case "RedChieftain_AfterFight":
			LAi_group_Delete("EnemyFight");
			DoQuestCheckDelay("hide_weapon", 1.3);
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			DoQuestCheckDelay("RedChieftain_EnterIndian", 20.0);//время на сбор жемчуга с трупа
			AddComplexSelfExpToScill(150, 150, 150, 150);
        break;
		
		case "RedChieftain_EnterIndian":
			n = sti(pchar.questTemp.RedChieftain.OurCrew);
			//считаем живых солдат
			iTemp = 0;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("RSOur_crew_"+i);
				if (LAi_GetCharacterHP(sld) > 0) iTemp++;
			}
			if (iTemp != n)//если есть потери - пересчитаем команду на корабле
			{
				iTemp = (n-iTemp)*10;
				SetCrewQuantityOverMax(pchar, sti(PChar.Ship.Crew.Quantity)-iTemp); 
			}
			//ставим индейцев по числу живых тартан
			n = sti(pchar.questTemp.RedChieftain.Tartane);
			ChangeIndianRelation(n+4.0);
			for (i=1; i <=n; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("RC_Indian_"+i, "miskito_"+(rand(5)+1), "man", "man", 5, sti(pchar.nation), 0, true, "quest"));
				sld.name = "аравак";
				sld.lastname = "рода Кайман";
				ChangeCharacterAddressGroup(sld, pchar.questTemp.RedChieftain.Shore, "goto", "goto1"));
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, false);
				LAi_SetImmortal(sld, true);
			}
			//ставим вождя
			sld = CharacterFromID("RedChieftain");
            LAi_SetActorType(sld);
			sld.dialog.currentnode = "RedChieftain_pearl";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.RedChieftain.Shore, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;
		
		case "RedChieftain_Pearl":
			i = sti(pchar.questTemp.RedChieftain.Ind);
			if (i <= sti(pchar.questTemp.RedChieftain.Tartane))
			{
			sld = characterFromId("RC_Indian_"+i);	
			LAi_SetActorType(sld);
				sld.Dialog.Filename = "Quest\LineMiniQuests\RedChieftain.c";
			sld.dialog.currentnode = "RedChieftain_pearl_give";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
			sld = CharacterFromID("RedChieftain");
            LAi_SetActorType(sld);
			sld.dialog.currentnode = "RedChieftain_final";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
        break;
//<-- Вождь краснокожих конец	
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Jason--------------------------------------------------Ложный след----------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "FalseTrace_AfterFight":
			sld = GetCharacter(NPC_GenerateCharacter("FalseTraceWife", "CatRainer", "woman", "towngirl", 2, sti(pchar.questTemp.FalseTrace.Mation), -1, true, "quest"));
			sld.name = "Катерина";
			sld.lastname = "Рейнер";
			sld.Dialog.Filename = "Quest\LineMiniQuests\FalseTrace.c";
			if (CheckAttribute(pchar, "questTemp.FalseTrace.CapPrisoner")) sld.dialog.currentnode = "FalseTrace_wife_4";
			else sld.dialog.currentnode = "FalseTrace_wife";
			RemoveAllCharacterItems(sld, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddComplexSeaExpToScill(150, 130, 130, 170, 150, 150, 0);
			pchar.GenQuest.DontSetCabinOfficer = true; // не пускать офицеров в каюту ГГ
        break;
		
		case "SetFalseTraceCharToCabin":
			iShipType = GetCharacterShipType(pchar);
			rShip = GetRealShip(iShipType);
			sTemp = "My_" + rShip.CabinType;
			sld = characterFromId(pchar.questTemp.FalseTrace.CharID);
			ChangeCharacterAddressGroup(sld, sTemp, "reload", "reload1");
			LAi_SetStayType(sld);
		break;
		
		case "FalseTraceWife_Remove":
			sld = characterFromId("FalseTraceWife");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
        break;
		
		case "FalseTrace_capture":
			sld = characterFromId("Mugger");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Afraid", "FalseTrace_afraid", 6.0);
        break;
		
		case "FalseTrace_afraid":
			LAi_SetActorType(pchar);
			sld = characterFromID("Mugger");        
			LAi_SetActorType(sld);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
        break;
		
		case "FalseTrace_SollyAfterFight":
			chrDisableReloadToLocation = false;
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("FalseTrace", "16");
			pchar.quest.False_Trace_5.win_condition.l1 = "location";
			pchar.quest.False_Trace_5.win_condition.l1.location = "SantaCatalina";
			pchar.quest.False_Trace_5.function = "FalseTrace_SollyShip";
			AddComplexSelfExpToScill(150, 150, 150, 150);
        break;
		
		case "FalseTraceDouble_Remove":
			sld = characterFromId("FalseTraceWife");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			chr = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerAdamIDX)];
			ChangeCharacterAddressGroup(chr, "none", "", "");
			chrDisableReloadToLocation = false;
        break;
		
		case "FalseTrace_AdamDead":
			LAi_group_Delete("EnemyFight");
			sld = characterFromId("FalseTraceWife");
			sld.dialog.currentnode = "FalseTrace_wife_25";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			locations[FindLocation(pchar.questTemp.FalseTrace.QuestShore)].DisableEncounters = false; //энкаутеры открыть
        break;
		
		case "FalseTrace_BanditsAfterFight":
			LAi_group_Delete("EnemyFight");
			sld = characterFromId("FalseTraceWife");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "FalseTrace_wife_31";
			LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
			pchar.quest.False_Trace_10.win_condition.l1 = "location";
			pchar.quest.False_Trace_10.win_condition.l1.location = "Hispaniola2";
			pchar.quest.False_Trace_10.function = "FalseTrace_BanditsShip";
			AddComplexSelfExpToScill(150, 150, 150, 150);
        break;
		
		case "FalseTrace_CaterinaKilled":
			sld = characterFromID("FalseTraceWife"); 
			LAi_KillCharacter(sld);
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("Mayak7", false);//офицеров пускать
			locations[FindLocation("Mayak7")].DisableEncounters = false;//энкаунтеры открыть
			AddQuestRecord("FalseTrace", "24");
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			OfficersReaction("bad");
        break;
//<-- Ложный след конец
		
///////////////////////////////////////////////////////////////////////////////////////////////////////////		
//Jason------------------------------------------------регата-------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "RegataCitPR_norm":	
			for (i=1; i <=9; i++)
			{
			sld = characterFromId("RegataCitPRMan_"+i);
			LAi_SetStayType(sld);
			}
			for (i=1; i <=5; i++)
			{
			sld = characterFromId("RegataCitPRWom_"+i);
			LAi_SetStayType(sld);
			}
			for (i=1; i <=2; i++)
			{
			sld = characterFromId("RegataCitPRHor_"+i);
			LAi_SetStayType(sld);
			}
		break;
		
		case "RegataCapTurn":	
			for (i=1; i <=5; i++)
			{
			sld = characterFromId("Regata_Cap_F"+i);
			LAi_ActorTurnToLocator(sld, "goto", "goto29");
			}
		break;
		
		case "ReturnRegataSYNorm":	
			sld = characterFromId("Beliz_shipyarder");
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_SetHuberType(sld);
			sld.Dialog.Filename = "Common_Shipyard.c";
			sld.dialog.currentnode = "First time";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "ReturnRegataPadreNorm":	
			sld = characterFromId("SentJons_Priest");
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_SetPriestType(sld);
			sld.Dialog.Filename = "Common_church.c";
			sld.dialog.currentnode = "First time";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "RegataSiegeHover":
			LocatorReloadEnterDisable("Bridgetown_town", "reload3_back", false);
			sld = characterFromId("Bridgetown_Mayor");
			sld.Dialog.Filename = "Quest\Regata_dialog.c";
			sld.dialog.currentnode = "Regata_Hovernor";
		break;
		
		case "RegataBridgWom_norm":	
			for (i=1; i <=9; i++)
			{
			sld = characterFromId("RegataBridgWom_"+i);
			LAi_SetStayType(sld);
			}
		break;
		
		case "RegataSiegeOpen":
			ref shTo;
			WaitDate("", 0, 0, 0, 2, 0);
			log_info("Пассажиры размещены у вас на корабле.");
			log_info("Корабль перегружен. Скорость и маневренность снизились.");
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
			bQuestDisableMapEnter = true;//глобу закрыть
			//установить радиус доплыть до на остров, чтобы ручками порулил корабликом
			n = FindIsland("Barbados");
			Islands[n].EffectRadius = 500;
			//запоминаем и снижаем скорость и маневренность
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			pchar.questTemp.Regata.Shipspeed = shTo.SpeedRate;
			pchar.questTemp.Regata.Shipturnrate = shTo.TurnRate;
			shTo.SpeedRate = (stf(shTo.SpeedRate)/1.2);
			shTo.TurnRate = (stf(shTo.TurnRate)/1.2);
			pchar.quest.Regata_Siege1.win_condition.l1 = "location";
			pchar.quest.Regata_Siege1.win_condition.l1.location = "Shore4";
			pchar.quest.Regata_Siege1.function = "RegataSiegeShore";
			pchar.quest.Regata_Siege2.win_condition.l1 = "location";
			pchar.quest.Regata_Siege2.win_condition.l1.location = "Barbados";
			pchar.quest.Regata_Siege2.function = "CreateSiegeSloop";
		break;
		
		case "RegataShoreAfterBattle":	
			//вертаем корабль и остров в норму
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.SpeedRate = (stf(pchar.questTemp.Regata.Shipspeed));
			shTo.TurnRate = (stf(pchar.questTemp.Regata.Shipturnrate));
			n = FindIsland("Barbados");	
			DeleteAttribute(Islands[n], "EffectRadius");
			DeleteAttribute(Islands[n], "DontSetShipInPort");
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Shore4", "boat", true);
			sld = characterFromId("SiegeOfficer");
			if (LAi_GetCharacterHP(sld) > 0)
			{
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
				for (i=1; i <=9; i++)
				{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			else
			{
				sld = characterFromId("RegataBridgWom_1");
				sld.dialog.currentnode = "Regata_BridgWom_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
//<-- Регата конец

///////////////////////////////////////////////////////////////////////////////////////////////////////////		
//Jason-------------------------------------------------Португалец---------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "PortugalOutResidence":	
			pchar.questTemp.Portugal = "Findcloves";
			LocatorReloadEnterDisable("Marigo_town", "reload1_back", false);
			LocatorReloadEnterDisable("Marigo_town", "reload2_back", false);
			LocatorReloadEnterDisable("Marigo_town", "reload_gate", false);
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_house_2";
			ChangeCharacterAddressGroup(sld, "Marigo_town", "goto", "goto15");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Portugal_JinoNorm":	
			sld = characterFromId("Jino");
			LAi_SetOwnerType(sld);
		break;
		
		case "PortugalHunterDied":
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("hide_weapon", 1.5);
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_street";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0) LAi_SetImmortal(sld, true);
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LeFransuaAfterFight":
			DoQuestCheckDelay("hide_weapon", 1.3);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("LeFransua_tavern", false);//офицеров пускать
			LocatorReloadEnterDisable("LeFransua_tavern", "reload2_back", false);
			pchar.quest.Portugal_Franz.win_condition.l1 = "location";
			pchar.quest.Portugal_Franz.win_condition.l1.location = "LeFransua_tavern_upstairs";
			pchar.quest.Portugal_Franz.function = "CreateFranzGarke";
			AddQuestRecord("Portugal", "14");
		break;
		
		case "LeFransua_PortugalTalk":
			DoQuestCheckDelay("hide_weapon", 1.3);
			chrDisableReloadToLocation = false;
			sld = characterFromId("Portugal");
			sld.dialog.currentnode = "Portugal_LFTalk";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 2.5);
		break;
		
		case "VaskezsPiratesDied":
			LAi_group_Delete("EnemyFight");
			DoQuestCheckDelay("hide_weapon", 1.3);
			chrDisableReloadToLocation = false;
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0) 
			{
				LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			AddQuestRecord("Portugal", "17");
			}
			else AddQuestRecord("Portugal", "36");
			sld = characterFromId("Avendel");
			RemovePassenger(Pchar, sld);
			pchar.quest.Portugal_LeFransuaAfterFight.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransuaAfterFight.win_condition.l1.location = "LeFransua_ExitTown";
			pchar.quest.Portugal_LeFransuaAfterFight.function = "AvendelSpeach";
			pchar.questTemp.Portugal = "LeFransuaAfterFight";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "Portugal_Final":
			sld = characterFromId("Portugal");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			AddQuestRecord("Portugal", "22");
			CloseQuestHeader("Portugal");
			pchar.questTemp.Portugal = "end";
		break;
		
		case "CheckPortHoll":
			sld = characterFromId("PortHol_4");
			LAi_SetImmortal(sld, false);
			LAi_group_SetCheck("PortHoll", "PortugalTerks_AfterFight");
		break;
		
		case "PortugalTerks_AfterFight":
			DoQuestCheckDelay("hide_weapon", 1.3);
			LAi_group_Delete("PortHoll");
			LAi_group_Delete("PortInd");
			pchar.quest.Portugal_Terks1.win_condition.l1 = "locator";
			pchar.quest.Portugal_Terks1.win_condition.l1.location = "Terks_Jungle_01";
			pchar.quest.Portugal_Terks1.win_condition.l1.locator_group = "rld";
			pchar.quest.Portugal_Terks1.win_condition.l1.locator = "aloc11";
			pchar.quest.Portugal_Terks1.function = "DigPortugalGems";
			pchar.questTemp.Portugal = "DigGems";
			AddQuestRecord("Portugal", "24");
			AddComplexSelfExpToScill(150, 150, 150, 150);
		break;
		
		case "FindPortugalGems":
			SetLaunchFrameFormParam("Прошло два часа...", "GivePortugalGems", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "GivePortugalGems":
			chrDisableReloadToLocation = false;
			Log_Info("Вы нашли клад Барта Португальца!");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry2", 510+drand(30));
			TakeNItems(pchar, "jewelry3", 530+drand(50));
			AddQuestRecord("Portugal", "25");
			pchar.quest.Portugal_Terks.win_condition.l1 = "location";
			pchar.quest.Portugal_Terks.win_condition.l1.location = "Terks";
			pchar.quest.Portugal_Terks.function = "CreatePortugalHollShip";
			pchar.questTemp.Portugal = "GiveGems"; // 021012
			AddCharacterExpToSkill(pchar, "Fortune", 500);//везение
		break;
		
		case "VaskezFight":
			Pchar.chr_ai.hp = stf(Pchar.chr_ai.hp)/2;
			sld = characterFromId("Vaskez");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "VaskezDied");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "VaskezDied":
			//LAi_group_Delete("EnemyFight");
			DoQuestCheckDelay("hide_weapon", 1.3);
			sld = characterFromId("Portugal");
			sld.dialog.currentnode = "Portugal_free_2";
		break;
		
		case "PortugalFree":
			sld = characterFromId("Portugal");
			sld.dialog.currentnode = "Portugal_free_5";
			LAi_SetActorType(sld);
         	ChangeCharacterAddressGroup(sld, "Villemstad_Exittown", "rld", "loc16");
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
//<-- Португалец конец
		
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Jason ----------------------------------------Цена чахотки--------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "Consumption_AfterHouseFight":
			LAi_group_Delete("EnemyFight");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			chrDisableReloadToLocation = false;
			pchar.questTemp.Consumption.Fight = "true";
		break;
		
		case "Conbandit_AfterFight":
			DoQuestCheckDelay("hide_weapon", 1.3);
			LAi_group_Delete("EnemyFight");
			locations[FindLocation("PortSpein_Exittown")].DisableEncounters = false; //энкаутеры открыть
			LAi_LocationDisableOfficersGen("PortSpein_Exittown", false);//офицеров пускать
			sld = characterFromId("Sergio");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				sld = characterFromId("Sergio");
				sld.dialog.currentnode = "Sergio_8";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				chrDisableReloadToLocation = false;
				sld = characterFromId("PortSpein_waitress");
				sld.dialog.filename = "Waitress_dialog.c";
				sld.dialog.currentnode = "First time";//вертаем ноду официантке
				AddQuestRecord("Consumption", "10");
				CloseQuestHeader("Consumption");
				DeleteAttribute(pchar, "questTemp.Consumption");
			}
		break;
		
		case "ConJuan_AfterFight_1":
			Log_Info("Корабль сейчас взорвется. Нужно немедленно уходить!");
			chrDisableReloadToLocation = false;
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;//ба-бах!
			pchar.GenQuest.ShipSituation.Explosion.CapId = "ConJuan";
			AddComplexSelfExpToScill(100, 100, 100, 100);
			pchar.questTemp.Consumption.Abordage = "true";
			DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
		break;

		case "ConJuan_AfterFight_2":
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_0;//ба-бах!
			pchar.GenQuest.ShipSituation.Explosion.CapId = "ConJuan";
			AddComplexSelfExpToScill(150, 150, 150, 150);
			pchar.questTemp.Consumption.Abordage = "true";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			OfficersReaction("good");//еще раз повысим репутацию
			Log_Info("До взрыва остались считаные минуты. Нужно немедленно уходить!");
		break;
		
		case "ConsumptionSexWaitress":
			sld = characterFromId("PortSpein_waitress");
			sld.dialog.currentnode = "Waitress_sex";
			LAi_SetStayType(sld);
		break;
//<-- Цена чахотки конец

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------ Калеуче ---------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////		
		case "Caleuche_Video": // ролик
			PChar.GenQuest.VideoAVI = "BlackPearl";
			PChar.GenQuest.VideoAfterQuest = "Caleuche_GhostAttack";
			DoQuestCheckDelay("PostVideo_Start", 0.2);
		break;
		 
		case "Caleuche_GhostAttack": // 
			log_info("Корабль-призрак на горизонте!");
			PlaySound("interface\_EvEnemy1.wav");
			SetMusicAlarm("music_storm");
		break;
		 
		case "Caleuche_GhostshipBoardingDeck": // расстановка абордажных групп
			PlaySound("interface\_GTBoard2.wav");
			PlaySound("interface\abordage_wining.wav");
			DoQuestFunctionDelay("Terrapin_SetMusic", 1.2);
			LAi_group_Delete("EnemyFight");
			bDisableCharacterMenu = true;//лочим F2
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			// делаем расчет сил
			int pCrew = sti(pchar.Ship.Crew.Quantity); 
			int eRank = 20+MOD_SKILL_ENEMY_RATE;
			int pRank = makeint(pCrew*30/666);
			if (pRank < 1) pRank = 1;
			int pScl = makeint(pCrew*70/666)+(20-MOD_SKILL_ENEMY_RATE*2);
			if (pScl < 10) pScl = 10;
			n = 20;
			if (pCrew < 20) n = pCrew;
			// наши 
			for (i=1; i<=n; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("caleuche_pcrew_"+i, "citiz_"+(rand(9)+31), "man", "man", pRank, FRANCE, 2, true, "soldier"));
				FantomMakeCoolFighter(sld, pRank, 20, 20, RandPhraseSimple("blade_10","blade_11"), "pistol1", "bullet", 120);
				SetSelfSkill(sld, pScl, pScl, pScl, pScl, pScl);
				LAi_SetWarriorType(sld);
				if (i < 8) ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "quest1");
				else ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "quest2");
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// враги
			for (i=1; i<=20; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("caleuche_ecrew_"+i, "skel"+(rand(3)+1), "man", "man", eRank, PIRATE, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, eRank, 20, 20, RandPhraseSimple("blade_10","blade_11"), "pistol1", "bullet", 120);
				SetSelfSkill(sld, 70, 70, 70, 70, 70);
				LAi_SetWarriorType(sld);
				if (i < 8) ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "quest3");
				else ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "quest4");
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_GhostshipSkelDie");
			LAi_SetFightMode(pchar, true);
			for(i=1; i<=3; i++)
			{
				idx = GetOfficersIndex(pchar, i);
				if(idx < 0) continue;
				sld = &Characters[idx];
				ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "reload", "reload2");
			}
		break;
		 
		case "Caleuche_GhostshipSkelDie": // перебили скелетов на палубе
			DoQuestCheckDelay("Caleuche_GhostshipCabinReload", 5.0);
			LAi_SetFightMode(pchar, false);
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		 
		case "Caleuche_GhostshipCabinReload": // в каюту
			SetLaunchFrameFormParam("", "", 0, 4);
			SetLaunchFrameFormPic("loading\Capdeck_1.tga");
			LaunchFrameForm();
			DoQuestCheckDelay("Caleuche_GhostshipCabinReloadGo", 4.0);
		break;
		
		case "Caleuche_GhostshipCabinReloadGo": // в каюту
			DoQuestReloadToLocation("CabineFDM", "rld", "loc0", "Caleuche_GhostshipBoardingCabin");
		break;
		
		case "Caleuche_GhostshipBoardingCabin": // в каюте
			LAi_group_Delete("EnemyFight");
			sld = characterFromId("Caleuche_seacap");
			ChangeCharacterAddressGroup(sld, "CabineFDM", "rld", "aloc2");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetFightMode(pchar, true);
			DoQuestCheckDelay("Caleuche_GhostshipCapitan", 15.0);
		break;
		 
		case "Caleuche_GhostshipCapitan": // разговор
			LAi_SetFightMode(pchar, false);
			sld = characterFromId("Caleuche_seacap");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		 
		case "Caleuche_GhostshipGetOut": // вырубили ГГ
			PlaySound("People Fight\Death_NPC_05.wav");
			SetLaunchFrameFormParam("Вы потеряли сознание от полученных ран...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 5, 10); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Caleuche_ReloadCoast", 5.0);
			RemoveItems(pchar, "kaleuche_amulet1", 1);
			locations[FindLocation("shore27")].DisableEncounters = true; //энкаутеры закрыть
		break;
		
		case "Caleuche_ReloadCoast": // на берег
			Group_DeleteGroup("Caleuche_Attack");
			// вычищаем все шторма и прочее
			for (i=0; i<MAX_ISLANDS;i++)
			{				
				if (Islands[i].id == "Dominica")
				{
					DeleteAttribute(&Islands[i], "alwaysStorm");
					DeleteAttribute(&Islands[i], "storm");
					DeleteAttribute(&Islands[i], "QuestlockWeather");
				}
			}
			for (i=0; i<MAX_LOCATIONS;i++)
			{				
				if (Locations[i].id == "Deck_Galeon_Ship")
				{
					DeleteAttribute(&locations[i], "alwaysStorm");
					DeleteAttribute(&locations[i], "storm");
					DeleteAttribute(&locations[i], "QuestlockWeather");
				}
			}
			sld = characterFromId("Caleuche_seacap");
			sld.lifeday = 0; // убираем ненужного НПС
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Galeon_Ship")], true);//запретить драться
			LAi_SetImmortal(pchar, false);
			Island_SetReloadEnableGlobal("Dominica", true);//на остров можно			
			bQuestDisableMapEnter = false;
			bDisableCharacterMenu = false;//разлочим F2
			InterfaceStates.Buttons.Save.enable = true;//разрешим сохраняться
			setCharacterShipLocation(pchar, "Shore27"));
			setWDMPointXZ("Shore27"); // корабль в бухту
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "Лодка";
			SetBaseShipData(pchar); // на баркас
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(pchar, 12);
			SetCharacterGoods(pchar, GOOD_FOOD, 20);
			AddCharacterGoods(pchar, GOOD_MEDICAMENT, 5);
			AddCharacterGoods(pchar, GOOD_RUM, 3);
			DoQuestReloadToLocation("Shore27", "goto", "goto1", "");
			LocatorReloadEnterDisable("Shore27", "boat", true); // в море не пускаем
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = characterFromId("Tuttuat");
			sld.dialog.currentnode = "Tuttuat_11"; // ноду шаману
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = characterFromId("Helena");
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("caleuche_oursailor", "citiz_35", "man", "man", 25, FRANCE, 1, false, "soldier"));
					sld.dialog.FileName = "Quest\Caleuche_dialog.c";
				}
			}
			sld.Dialog.currentnode = "on_coast";
			ChangeCharacterAddressGroup(sld, "shore27", "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			LAi_SetCurHPMax(pchar);
			AddCharacterHealth(pchar, -30);
			AddQuestRecord("Caleuche", "4");
		break;
		 
		case "Caleuche_BelizTownbandosDie": // прибили бандюка в доме
			AddQuestRecord("Caleuche", "11");
			LAi_LocationDisableOfficersGen("Beliz_ExitTown", true);
			LAi_LocationDisableOfficersGen("Beliz_Jungle_01", true);
			LAi_LocationDisableOfficersGen("Beliz_CaveEntrance_1", true);
			LAi_LocationDisableOfficersGen("Beliz_Cave", true);
			LAi_LocationDisableOfficersGen("Beliz_CaveEntrance_2", true);
			LAi_LocationDisableOfficersGen("Beliz_Cave_2", true);
			LAi_LocationDisableOfficersGen("Beliz_CaveEntrance_3", true);
			LAi_LocationDisableOfficersGen("Beliz_jungle_03", true);
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		 
		case "Caleuche_ForestMerchantDie": // перебили конвой купца
			// собираем бандюков
			for (i=2; i<=6; i++)
			{
				if (GetCharacterIndex("Beliz_forestbandos_"+i) != -1)
				{
					sld = characterFromId("Beliz_forestbandos_"+i);	
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
					sld.lifeday = 0;
				}
			}
			sld = characterFromId("Beliz_forestbandos_1");
			sld.lifeday = 0; // если будет дополнение - то это убрать
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld.dialog.currentnode = "Beliz_forestbandos_7";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddComplexSelfExpToScill(80, 80, 80, 80);
		break;
		
		case "Caleuche_HeadBandosEscape": // главнюк почти прибит
			sld = characterFromId("Beliz_forestbandos_1");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Beliz_ExitTown", "rld", "aloc10", "", -1);
		break;
		 
		case "Caleuche_CaveBandosDie": // перебили бандюков в пещере
			chrDisableReloadToLocation = false;
			AddQuestRecord("Caleuche", "14");
			AddComplexSelfExpToScill(70, 70, 70, 70);
		break;
		
		case "Caleuche_GhostshipGameOver": // калеуче настиг ГГ - геймовер
			GameOver("sea");
		break;
		 
		case "Caleuche_LandLedySkelDie": // прибили скелет хозяйки дома
			LAi_group_Delete("EnemyFight");
			SetMusicAlarm("");
			chrDisableReloadToLocation = false;
			PlaySound("People Fight\Peace_woman_death_07.wav");
			AddQuestRecord("Caleuche", "25");
			pchar.questTemp.Caleuche = "priest";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "Caleuche_CubaCaveEntSkelDie": // прибили скелетов у пещеры
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Cuba_CaveEntrance", "reload2_back", true);
			pchar.quest.Caleuche_cuba_grot.win_condition.l1 = "location";
			pchar.quest.Caleuche_cuba_grot.win_condition.l1.location = "Cuba_Grot";
			pchar.quest.Caleuche_cuba_grot.function = "Caleuche_CubaGrot";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		 
		case "Caleuche_CubaGrotSkel1Die": // прибили 1 партию
			iRank = 20+MOD_SKILL_ENEMY_RATE*2;
			sTemp = "pistol1";
			if (MOD_SKILL_ENEMY_RATE > 4) sTemp = "pistol5";
			if (MOD_SKILL_ENEMY_RATE > 6) sTemp = "pistol6";
			if (MOD_SKILL_ENEMY_RATE > 8) sTemp = "pistol4";
			for (i=1; i<=4; i++)
			{
				PlaySound("Types\skel.wav");
				CreateLocationParticles("fire_incas_Simple", "goto", "ass"+i, 0.5, 0, 0, "");
				sld = GetCharacter(NPC_GenerateCharacter("cubagrot_skel2_"+i, "skel"+(rand(3)+1), "skeleton", "skeleton", iRank, PIRATE, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, 70, 70, LinkRandPhrase("blade_18","blade_19","blade_21"), sTemp, "bullet", 150);
				sld.monster = true; 
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "Cuba_Grot", "goto", "ass"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_CubaGrotSkel2Die");
		break;
		
		case "Caleuche_CubaGrotSkel2Die": // прибили 2 партию
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "Caleuche_CubaGrotLook", -1);
			CreateLocationParticles("large_smoke", "item", "item2", 0.5, 0, 0, "");
		break;
		
		case "Caleuche_CubaGrotLook": // смотрим на дым
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "randitem", "randitem1");
			DoQuestFunctionDelay("Caleuche_CubaGrotChavinavy", 3.0);
		break;
		
		case "Caleuche_MonsterStandUp": // чавинави
			sld = characterFromId("CubaChavinavi");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "Caleuche_MonsterFight", 3.5);
			PlaySound("VOICE\Russian\hambit\Chavinavy.wav");
        break;
		
		case "Caleuche_MonsterFight": // чавинави атакует
			PlaySound("ambient\horror\horror2.wav");
			PlaySound("types\skel.wav");
			LAi_SetPlayerType(Pchar);
			sld = characterFromId("CubaChavinavi");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_CubaGrotAfterBattle");
			LAi_SetFightMode(pchar, true);
        break;
		
		case "Caleuche_CubaGrotAfterBattle": // прибили чавинави
			chrDisableReloadToLocation = false;
			if (GetCharacterIndex("cavehunter") != -1)
			{
				sld = characterFromId("cavehunter");
				sld.lifeday = 0;
				sld.dialog.currentnode = "cavehunter_11";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload1_back", false);
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload3_back", false);
			LocatorReloadEnterDisable("Cuba_CaveEntrance", "reload2_back", false);
			AddQuestRecord("Caleuche", "28");
			pchar.questTemp.Caleuche = "havana1";
			AddComplexSelfExpToScill(150, 150, 150, 150);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "Caleuche_MerrimanTeleport": // телепортируем Мерримана
			sld = characterFromId("Joakim");
			ChangeCharacterAddressGroup(sld, "Havana_CryptDungeon", "goto", "goto3");
			LAi_SetImmortal(sld, false);
			DoQuestFunctionDelay("Caleuche_MerrimanCallMonster", 1.0);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			if(GetOfficersQuantity(pchar) > 0)
			{
				pchar.OfficerAttRange = 7.0;
				OfficersFollow();
			}
			for (i=1; i<=11; i++)
			{
				if (GetCharacterIndex("merriman_skel_"+i) != -1)
				{
					sld = characterFromId("merriman_skel_"+i);
					if (LAi_GetCharacterHP(sld) > 0)
					{
						LAi_SetWarriorType(sld);
						LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
					}
				}
			}
			DoQuestFunctionDelay("Terrapin_SetMusic", 0.5);
		break;
		
		case "Caleuche_MerrimanRecallMonster": // повторные вызовы чавинави
			if (CheckAttribute(pchar, "questTemp.Caleuche.Merriman_hide"))
			{
				DeleteAttribute(pchar, "questTemp.Caleuche.Merriman_hide");
				sld = characterFromId("Joakim");
				GetCharacterPos(pchar, &locx, &locy, &locz);
				ChangeCharacterAddressGroup(sld, "Havana_CryptDungeon", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "Caleuche_MerrimanDie");
			}
			iGlobalTemp++;
			DoQuestFunctionDelay("Caleuche_MerrimanCallMonster", 5.0);
		break;
		
		case "Caleuche_MerrimanDie": // прибили Мерримана
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			for (i=1; i<=11; i++)
			{
				if (GetCharacterIndex("merriman_skel_"+i) != -1)
				{
					sld = characterFromId("merriman_skel_"+i);
					if (LAi_GetCharacterHP(sld) > 0) LAi_KillCharacter(sld); // прибьем скелетов
				}
			}
			sld = characterFromId("MerrimanChavinavi"+iGlobalTemp);
			if (LAi_GetCharacterHP(sld) > 0) LAi_KillCharacter(sld); // прибьем чавинави
			// на нефритовый череп
			pchar.GenQuest.NoDelBody = true;
			pchar.quest.Caleuche_find_skull.win_condition.l1 = "item";
			pchar.quest.Caleuche_find_skull.win_condition.l1.item = "SkullAztec";
			pchar.quest.Caleuche_find_skull.function = "Caleuche_FindSkull";
			AddQuestRecord("Caleuche", "32");
			AddComplexSelfExpToScill(200, 200, 200, 200);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "Caleuche_ThreeLeverAim": // 
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Barman_idle", "pchar_back_to_player", 2.0);
			DoQuestFunctionDelay("Caleuche_ThreeLeverTurn", 2.0);
		break;
		
		case "Caleuche_SixLeverAim": // 
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Barman_idle", "pchar_back_to_player", 2.0);
			DoQuestFunctionDelay("Caleuche_SixLeverTurn", 2.0);
		break;
		
		case "Video_Door": // открывается дверь в альков
			PChar.GenQuest.VideoAVI = "Door";
			PChar.GenQuest.VideoAfterQuest = "Caleuche_LabirintReload";
			DoQuestCheckDelay("PostVideo_Start", 0.2);
		break;
		
		case "Caleuche_LabirintReload": // перегрузка локации
			n = Findlocation("Labirint_3");
			DeleteAttribute(&locations[n], "models.always.door");
			Locations[n].reload.l28.name = "reload30_back";
			Locations[n].reload.l28.go = "Treasure_Alcove";
			Locations[n].reload.l28.emerge = "Reload1";
			Locations[n].reload.l28.autoreload = "1";
			DoQuestReloadToLocation("Labirint_3", "item", "step5", "");
			iGlobalTemp = 0;
		break;
		
		case "Caleuche_LeverFightOver": // прибили чавинави у рычагов
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			if (sti(pchar.questTemp.Caleuche.LeverType) == 0) pchar.questTemp.Caleuche.LeverL = "true";
			if (sti(pchar.questTemp.Caleuche.LeverType) == 1) pchar.questTemp.Caleuche.LeverR = "true";
			DeleteAttribute(pchar, "questTemp.Caleuche.LeverType");
			iGlobalTemp++;
		break;
		
		case "Caleuche_TeleportTrapOver": // прибили чавинави у телепорта-ловушки
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "questTemp.Caleuche.LockTeleport");
			iGlobalTemp++;
		break;
		
		case "Caleuche_TopChavinaviDie": // прибили чавинави в святилище
			LAi_group_Delete("EnemyFight");
			sld = ItemsFromID("SkullAztec");
			sld.shown = "0";
			sld.useLocation = "treasure_alcove";
			sld.useLocator = "button01";
		break;
		
		case "Caleuche_RotatePause": // крутим камеру
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1700);
			DoQuestCheckDelay("Caleuche_RotatePauseOver", 25.0);
		break;
		
		case "Caleuche_RotatePauseOver": // идем к вождю чавинави
			locCameraResetState();
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			Caleuche_PutSkull();
			sld = characterFromId("TopChavinavi_1");
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		break;
		
		case "Caleuche_ChangeShip": // меняем харки калеуче
			sld = characterFromId("Kaleuche_khaelroacap");
			shTo = &RealShips[sti(sld.Ship.Type)];
			shTo.SpeedRate = 15.2;
			shTo.TurnRate = 32.0;
		break;
	// <-- Калеуче
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Addon-2016 Jason, французские миниквесты (ФМК)
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ФМК-Гваделупа
		case "FMQG_OnBoard": // 
			sld = characterFromId("FMQG_pass_1");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				AddPassenger(pchar, sld, false);//добавить пассажира
				SetCharacterRemovable(sld, false);
			}
			chrDisableReloadToLocation = false;
		break;
		
		case "FMQG_KidnappingInfo": // 
			DeleteAttribute(pchar, "questTemp.FMQG.Info");
		break;
	
		case "FMQG_KidnappingAttack": // атака на Пинетта
			sld = characterFromId("FMQG_pass_1");
			LAi_RemoveCheckMinHP(sld);
			LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "TmpEnemy");
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
			for (i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromId("FMQG_pinett_guard_"+i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQG_KidnappingAfterFight");
			SetNationRelation2MainCharacter(ENGLAND, RELATION_ENEMY);
		break;
		
		case "FMQG_KidnappingAfterFight": // после боя
			LAi_group_Delete("EnemyFight");
			sld = characterFromId("FMQG_pass_1");
			sld.Dialog.currentnode = "citizen_23";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			if (pchar.questTemp.FMQG == "fail") LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			else LAi_ActorDialog(sld, pchar, "", -1, 0);
			LAi_group_Delete("TmpEnemy");
			AddComplexSelfExpToScill(30, 30, 30, 30);
		break;
		
		case "FMQG_KidnappingFail": // упустил
			chrDisableReloadToLocation = false;
			sld = characterFromId("FMQG_pass_1");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			for (i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromId("FMQG_pinett_guard_"+i);
				sld.lifeday = 0;
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			pchar.questTemp.FMQG = "fail";
			AddQuestRecord("FMQ_Guadeloupe", "21");
			CloseQuestHeader("FMQ_Guadeloupe");
			SetNationRelation2MainCharacter(ENGLAND, RELATION_ENEMY);
			ChangeCharacterNationReputation(pchar, ENGLAND, -5);
		break;
		
		case "FMQG_OnLighthouse": // на маяке
			LocatorReloadEnterDisable("Mayak2", "reload1_back", true);
			sld = characterFromId("FMQG_pass_1");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Mayak2", "goto", "goto2");
			LAi_ActorFollow(sld, pchar, "", -1);
			pchar.quest.FMQG_Mayak1.win_condition.l1 = "location";
			pchar.quest.FMQG_Mayak1.win_condition.l1.location = "Barbados";
			pchar.quest.FMQG_Mayak1.function = "FMQG_KidnappingSucsess";
		break;
		
		case "FMQG_KillersDestroy": // прибил наймитов
			chrDisableReloadToLocation = false;
			pchar.questTemp.FMQG = "killers";
			AddQuestRecord("FMQ_Guadeloupe", "26");
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		// ФМК-Мартиника
		case "FMQM_Looking": // ковыряется в ящике
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Barman_idle", "FMQM_Arest", 5.0);
		break;
		
		case "FMQM_Arest": // якобы арест
			iRank = MOD_SKILL_ENEMY_RATE+7;// Addon 2016-1 Jason пиратская линейка
			iScl = 25 + 2*sti(pchar.rank);
			LAi_SetPlayerType(pchar);
			sld = GetCharacter(NPC_GenerateCharacter("FMQM_officer", "off_fra_2", "man", "man", iRank, FRANCE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_13", "pistol1", "bullet", iScl*3);
			sld.name = "Фелисьен";
			sld.lastname = "Грони";
			sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Martinique.c";
			sld.Dialog.currentnode = "officer";
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			if (MOD_SKILL_ENEMY_RATE < 7)
			{
				GiveItem2Character(sld, "pistol6");
				EquipCharacterbyItem(sld, "pistol6");
			}
			else
			{
				GiveItem2Character(sld, "pistol4");
				EquipCharacterbyItem(sld, "pistol4");
				sld.cirassId = Items_FindItemIdx("cirass2");
			}
			ChangeCharacterAddressGroup(sld, "FortFrance_Shipyard", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "FMQM_ArestContinue": // 
			sld = characterFromId("FMQM_officer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "FortFrance_town", "officers", "reload5_1", "FMQM_ArestReload", 5);
			InterfaceStates.Buttons.Save.enable = false;
		break;
		
		case "FMQM_ArestReload": // в город
			LAi_SetPlayerType(pchar);
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload5", "FMQM_ArestFinal");
		break;
		
		case "FMQM_ArestFinal": // Грегуар Валинье подходит
			sld = characterFromId("FMQM_officer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload_jail", "none", "", "", "", 10);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload_jail", "none", "", "", "", 10);
			LocatorReloadEnterDisable("FortFrance_town", "reload5_back", true); // запираем верфь
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_Shipyard")], false);
			// гид
			sld = GetCharacter(NPC_GenerateCharacter("Guide_x", "Guide_1", "man", "man", 10, FRANCE, -1, true, "officer"));
			SetFantomParamFromRank(sld, 10, true);
			RemoveAllCharacterItems(sld, true);
			GiveItem2Character(sld, "blade_12");
			EquipCharacterbyItem(sld, "blade_12");
			sld.name = "Грегуар";
			sld.lastname = "Валинье";
			sld.dialog.FileName = "Quest\LineMiniQuests\FMQ_Martinique.c";
			sld.dialog.currentnode = "greguar";
			sld.greeting = "noble_male";
			sld.rank = 25;
			LAi_SetHP(sld, 350, 350);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto13");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "FMQM_InTavern": // в таверне
			if(CheckAttribute(pchar, "IsMushketer"))
			{
				SetMainCharacterToMushketer("", false);
			}
			FreeSitLocator("Fortfrance_tavern", "sit_base4");
			DoQuestReloadToLocation("Fortfrance_tavern", "sit", "sit_base4", "");			
			sld = characterFromID("Guide_x");
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
        break;
		
		case "FMQM_OutTavern":
			chrDisableReloadToLocation = false;
			LAI_SetPlayerType(pchar);           
            DoQuestReloadToLocation("Fortfrance_tavern", "tables", "stay4", "");
            sld = CharacterFromID("Guide_x");
            ChangeCharacterAddressGroup(sld, "none", "", "");
			AddQuestRecord("FMQ_Martinique", "10");
			InterfaceStates.Buttons.Save.enable = true;
			pchar.quest.FMQM_ShipyardOpen.win_condition.l1 = "Timer";
			pchar.quest.FMQM_ShipyardOpen.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQM_ShipyardOpen.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.FMQM_ShipyardOpen.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.FMQM_ShipyardOpen.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.FMQM_ShipyardOpen.function = "FMQM_ShipyardOpen";
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//закрыть выходы из города
			WaitDate("",0,0,0,2,5);
			RecalculateJumpTable();
			InterfaceStates.Buttons.Save.enable = true;
        break;
		
		case "FMQM_HurryToSea": // торопимся в море
			chrDisableReloadToLocation = false;
            sld = CharacterFromID("Guide_x");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload4_back", "none", "", "", "", 10.0);
			AddQuestRecord("FMQ_Martinique", "13");
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);
			pchar.quest.FMQM_hurry.win_condition.l1 = "location";
			pchar.quest.FMQM_hurry.win_condition.l1.location = "Guadeloupe";
			pchar.quest.FMQM_hurry.function = "FMQM_ArriveGuadeloupe";
			SetFunctionTimerCondition("FMQM_HurryLate", 0, 0, 5, false);
			pchar.worldmapencountersoff = "1"; // отключить энкаунтеры
		break;
		
		case "FMQM_ShoreAfterFight": // прибили контру
			LAi_group_Delete("EnemyFight");
			LAi_SetFightMode(pchar, false);
			LAi_LocationFightDisable(&Locations[FindLocation("Shore28")], true);//запретить драться
			DoQuestCheckDelay("FMQM_ShoreSetOfficer", 8.0);
		break;
		
		case "FMQM_ShoreSetOfficer": // явился француз
			pchar.questTemp.FMQ.Attack = true;// Addon 2016-1 Jason пиратская линейка
			iRank = MOD_SKILL_ENEMY_RATE+6;
			iScl = 25 + 2*sti(pchar.rank);
			string sModel, sModel_m, sPistol, sGroup, sLocator;
			if (MOD_SKILL_ENEMY_RATE < 7)
			{
				sModel = "citiz_2";
				sModel_m = "mush_ctz_"+(rand(2)+1);
				sPistol = "pistol6";
			}
			else
			{
				sModel = "citiz_5";
				sModel_m = "mush_ctz_"+(rand(2)+10);
				sPistol = "pistol4";
			}
			LAi_Fade("", "");
			AddQuestRecord("FMQ_Martinique", "18");
			sld = characterFromId("FMQM_officer");
			LAi_SetActorType(sld);
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			sld.dialog.currentnode = "officer_7";
			ChangeCharacterAddressGroup(sld, "Shore28", "reload", "sea");
			for (i=1; i<=5; i++)
			{
				if (i > 3)
				{
					sld = GetCharacter(NPC_GenerateCharacter("FMQM_mercenary_"+i, sModel_m, "man", "mushketer", iRank, PIRATE, 0, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
					LAi_SetCharacterUseBullet(sld, "cartridge");
					sld.MusketerDistance = 0;
					sGroup = "goto";
					sLocator = "goto"+(i+7);
					SetCharacterPerk(sld, "Gunman");
					SetCharacterPerk(sld, "GunProfessional");
					if (MOD_SKILL_ENEMY_RATE > 6) sld.cirassId = Items_FindItemIdx("cirass1");
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("FMQM_mercenary_"+i, sModel+i, "man", "man", iRank, PIRATE, 0, true, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_04","blade_06","blade_10"), sPistol, "bullet", iScl*2);
					sGroup = "officers";
					sLocator = "sea_"+i;
					SetCharacterPerk(sld, "GunProfessional");
					EquipCharacterbyItem(sld, sPistol);
					if (MOD_SKILL_ENEMY_RATE > 6) sld.cirassId = Items_FindItemIdx("cirass2");
				}
				ChangeCharacterAddressGroup(sld, "Shore28", "reload", "sea");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocator(sld, sGroup, sLocator, "", 7);
			}
		break;
		
		case "FMQM_AfterBattleExit": // прибили кодлу француза
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			AddQuestRecord("FMQ_Martinique", "20");
			pchar.quest.FMQM_seabattle.win_condition.l1 = "location";
			pchar.quest.FMQM_seabattle.win_condition.l1.location = "Guadeloupe";
			pchar.quest.FMQM_seabattle.function = "FMQM_SeaBattleTartane";
		break;
		
		// ФМК-Сент-Кристофер
		case "FMQN_SailMaarten": // англичане на борт
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("FMQN_seafox_1");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.FMQN_sailing.win_condition.l1 = "location";
			pchar.quest.FMQN_sailing.win_condition.l1.location = "Shore40";
			pchar.quest.FMQN_sailing.win_condition.l2 = "Ship_location";
			pchar.quest.FMQN_sailing.win_condition.l2.location = "Shore40";
			pchar.quest.FMQN_sailing.function = "FMQN_ArriveMaarten";
			SetFunctionTimerCondition("FMQN_SailingLate", 0, 0, 10, false);
			for(i = 0; i < MAX_LOCATIONS; i++)
			{	
				sld = &Locations[i];
				if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
				{
				sld.DisableEncounters = true;	
			}
			}
			sld = &Locations[FindLocation("Shore40")];
			sld.QuestlockWeather = "23 Hour";
		break;
		
		case "FMQN_HollandBattleRun": // ставим голландский отряд за городом
			iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
			iScl = 30 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("FMQN_holland_0", "off_hol_5", "man", "man", iRank+5, HOLLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank+7, iScl+7, iScl+7, "blade_15", "pistol5", "bullet", iScl*3+50);
			sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Nevis.c";
			sld.Dialog.currentnode = "hol_officer";
			sld.name = "Ханс";
			sld.lastname = "Шулте";
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			LAi_SetImmortal(sld, true);
			LAi_SetCheckMinHP(sld, 10, true, "");
			ChangeCharacterAddressGroup(sld, "Marigo_ExitTown", "reload", "reload2_back");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			for (i=1; i<=7; i++)
			{
				if (i > 6)
				{
					sld = GetCharacter(NPC_GenerateCharacter("FMQN_holland_"+i, "mush_hol_4", "man", "mushketer", iRank, HOLLAND, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*3);
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("FMQN_holland_"+i, "sold_hol_1"+i, "man", "man", iRank, HOLLAND, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_12","blade_09","blade_14"), "pistol1", "bullet", iScl*2);
				}
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_SetImmortal(sld, true);
				LAi_CharacterDisableDialog(sld);
				ChangeCharacterAddressGroup(sld, "Marigo_ExitTown", "reload", "reload2_back");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocator(sld, "goto", "goto6", "", 15);
			}
		break;
		
		case "FMQN_HollandBattleMarch": // 
			for (i=0; i<=7; i++)
			{
				sld = CharacterFromID("FMQN_holland_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			pchar.quest.FMQN_holl_cave.win_condition.l1 = "locator";
			pchar.quest.FMQN_holl_cave.win_condition.l1.location = "Marigo_jungle_01";
			pchar.quest.FMQN_holl_cave.win_condition.l1.locator_group = "reload";
			pchar.quest.FMQN_holl_cave.win_condition.l1.locator = "reload3_back";
			pchar.quest.FMQN_holl_cave.function = "FMQN_HollandBattlePlan";
		break;
		
		case "FMQN_HollandBattlePosition": // голландцы - к колодцу
			for (i=0; i<=7; i++)
			{
				sld = CharacterFromID("FMQN_holland_"+i);
				if (i == 6 || i == 7) 
				{
					sld.MusketerDistance = 0;
					LAi_SetStayType(sld);
					LAi_SetActorType(sld);

				}
				else
				{
					LAi_SetActorType(sld);
					LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "FMQN_HollandBattleToCave", 20.0);
				}
			}
		break;
		
		case "FMQN_HollandBattleToCave": // в пещеру
			LocatorReloadEnterDisable("Marigo_jungle_01", "reload3_back", false);
			sld = CharacterFromID("FMQN_seafox_1");
			sld.Dialog.currentnode = "seafox_20";
			LAi_CharacterEnableDialog(sld);
			sld.talker = 9;
		break;
		
		case "FMQN_HollandBattleFight": // бой в пещере - начало
			bDisableCharacterMenu = true;
			pchar.GenQuest.FrameLockEsc = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Marigo_Cave")], false);
			chrDisableReloadToLocation = true;
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("FMQN_seafox_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQN_HollandBattleAfterFight");
			LAi_SetFightMode(pchar, true);
			DoQuestCheckDelay("FMQN_HollandBattleFightAdd", 30.0);
		break;
		
		case "FMQN_HollandBattleFightAdd": // голландцы спешат на помощь
			bDisableCharacterMenu = false;
			DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
			for (i=0; i<=7; i++)
			{
				sld = CharacterFromID("FMQN_holland_"+i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				if (i == 6 || i == 7) ChangeCharacterAddressGroup(sld, "Marigo_Cave", "reload", "reload1");
				else Log_TestInfo(i+"-й солдат ждет");
			}
			DoQuestFunctionDelay("FMQN_HollandBattleAdding", 1.5);
			iTotalTemp = 0;
		break;
		
		case "FMQN_HollandBattleAdding2": // китайская рекурсия
			sld = CharacterFromID("FMQN_holland_"+iTotalTemp);
			ChangeCharacterAddressGroup(sld, "Marigo_Cave", "reload", "reload2");
			iTotalTemp++;
			if (iTotalTemp > 5) break;
			else DoQuestFunctionDelay("FMQN_HollandBattleAdding", 10.0);
		break;
		
		case "FMQN_HollandBattleAfterFight": // после боя
			LAi_group_Delete("EnemyFight");
			sld = CharacterFromID("FMQN_holland_0");
			sld.Dialog.currentnode = "hol_officer_5";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "FMQN_HollandBattleRest": // в город возвращаемся
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("FMQN_holland_0");
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			for (i=0; i<=7; i++)
			{
				if (GetCharacterIndex("FMQN_holland_"+i) != -1)
				{
					sld = CharacterFromID("FMQN_holland_"+i);
					sld.lifeday = 0; // Addon 2016-1 Jason пиратская линейка
				}
			}
			pchar.quest.FMQN_hol_complete.win_condition.l1 = "Timer";
			pchar.quest.FMQN_hol_complete.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_hol_complete.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_hol_complete.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_hol_complete.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_hol_complete.function = "FMQN_HollandBattleGovernor";
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false);
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("Marigo_jungle_01", "reload1_back", false);
			LocatorReloadEnterDisable("Marigo_jungle_01", "reload2_back", false);
			AddQuestRecord("FMQ_Nevis", "16");
		break;
		
		case "FMQN_GetRumoursDay": // узнали днем
			AddQuestRecord("FMQ_Nevis", "7");
		break;
		
		case "FMQN_GetRumoursNight": // узнали ночью
			DoQuestCheckDelay("sleep_in_tavern", 1.0);
			TavernWaitDate("wait_day");
			AddQuestRecord("FMQ_Nevis", "7");
		break;
		
		case "FMQN_EnglandSnake": // скрытное проникновение
			SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY);
			chrDisableReloadToLocation = true;
			pchar.GenQuest.CannotWait = true;
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("FMQN_seafox_"+i);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Marigo_Town", "reload", "gate_back");
				LAi_ActorFollow(sld, pchar, "", -1);
			}
			pchar.quest.FMQN_fail3.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail3.win_condition.l1.date.hour  = 4.0;
			pchar.quest.FMQN_fail3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_fail3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_fail3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_fail3.function = "FMQN_EnglandBattleFail"; // 4 часа на ходьбу к тюрьме и назад
			pchar.quest.FMQN_jail.win_condition.l1 = "locator";
			pchar.quest.FMQN_jail.win_condition.l1.location = "Marigo_town";
			pchar.quest.FMQN_jail.win_condition.l1.locator_group = "reload";
			pchar.quest.FMQN_jail.win_condition.l1.locator = "reload_jail";
			pchar.quest.FMQN_jail.function = "FMQN_EnglandJail";
			pchar.quest.FMQN_Alarm.win_condition.l1 = "Alarm";
			pchar.quest.FMQN_Alarm.win_condition.l1.value = 0;
			pchar.quest.FMQN_Alarm.win_condition.l1.operation = ">";
			pchar.quest.FMQN_Alarm.function = "FMQN_EnglandBattleFail";
			pchar.questTemp.FMQN = "way_eng_6";
		break;
		
		case "FMQN_EnglandInJail": // зашли в тюрьму
			SetNationRelation2MainCharacter(HOLLAND, RELATION_NEUTRAL);
			DoQuestCheckDelay("FMQN_EnglandOutJail", 45.0);
		break;
		
		case "FMQN_EnglandJailTurn": // поворот ГГ
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_jail");
		break;
		
		case "FMQN_EnglandOutJail": // вышли из тюрьмы
			LAi_SetPlayerType(pchar);
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("FMQN_seafox_"+i);
				LAi_SetActorType(sld);
				if (i == 1) 
				{
					sld.dialog.currentnode = "seafox_33";
					LAi_ActorDialogDelay(sld, pchar, "", 2.0);
				}
				ChangeCharacterAddressGroup(sld, "Marigo_Town", "reload", "reload_jail");
			}
			for (i=5; i<=6; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("FMQN_prisoner_"+i, "off_eng_"+i, "man", "man", 30, ENGLAND, -1, true, "quest"));
				SetFantomParamFromRank(sld, 30, true);
				RemoveAllCharacterItems(sld, true);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, true);
				ChangeCharacterAddressGroup(sld, "Marigo_Town", "reload", "reload_jail");
				LAi_ActorFollow(sld, pchar, "", -1);
			}
			pchar.questTemp.FMQN = "way_eng_7";
		break;
		
		case "FMQN_EnglandRunToJungle": // уходим в джунгли
			SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY);
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("FMQN_seafox_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
			pchar.quest.FMQN_jail1.win_condition.l1 = "locator";
			pchar.quest.FMQN_jail1.win_condition.l1.location = "Marigo_town";
			pchar.quest.FMQN_jail1.win_condition.l1.locator_group = "reload";
			pchar.quest.FMQN_jail1.win_condition.l1.locator = "gate_back";
			pchar.quest.FMQN_jail1.function = "FMQN_EnglandReloadJungle";
		break;
		
		case "FMQN_EnglandEscape": // за воротами
			pchar.quest.FMQN_fail3.over = "yes";
			pchar.quest.FMQN_Alarm.over = "yes";
			SetNationRelation2MainCharacter(HOLLAND, RELATION_NEUTRAL);
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("FMQN_seafox_"+i);
				ChangeCharacterAddressGroup(sld, "Marigo_exitTown", "goto", "goto6");
				if (i == 1)
				{
					LAi_CharacterEnableDialog(sld);
					sld.dialog.currentnode = "seafox_34";
				}
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			for (i=5; i<=6; i++)
			{
				sld = CharacterFromID("FMQN_prisoner_"+i);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Marigo_exitTown", "rld", "loc0");
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			pchar.questTemp.FMQN = "way_eng_8";
		break;
		
		case "FMQN_EnglandRunToShore": // идем к бухте
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("FMQN_seafox_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", true);
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload2_back", true);
			LocatorReloadEnterDisable("Marigo_jungle_01", "reload1_back", true);
			LocatorReloadEnterDisable("Marigo_jungle_01", "reload3_back", true);
			LocatorReloadEnterDisable("Marigo_jungle_02", "reload1_back", true);
			LocatorReloadEnterDisable("Marigo_jungle_02", "reload3_back", true);
			LocatorReloadEnterDisable("Marigo_jungle_02", "reloadW_back", true);
			pchar.quest.FMQN_ShoreAttack.win_condition.l1 = "location";
			pchar.quest.FMQN_ShoreAttack.win_condition.l1.location = "shore40";
			pchar.quest.FMQN_ShoreAttack.function = "FMQN_EnglandInShoreAttack";
			AddQuestRecord("FMQ_Nevis", "25");
			Group_DeleteGroup("FMQN_shipgroup"); // удаляем Зеепард
		break;
		
		case "FMQN_AfterShoreAttack": // после боя в бухте
			AddQuestRecord("FMQ_Nevis", "26");
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("shore40", "reload1_back", true);
			for (i=5; i<=6; i++)
			{
				sld = CharacterFromID("FMQN_prisoner_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				AddPassenger(pchar, sld, false);//добавить пассажира
				SetCharacterRemovable(sld, false);
			}
			sld = CharacterFromID("FMQN_seafox_1");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				pchar.questTemp.FMQN = "caspar_alive";
				AddPassenger(pchar, sld, false);//добавить пассажира
				SetCharacterRemovable(sld, false);
			}
			else pchar.questTemp.FMQN = "caspar_dead";
			for (i=2; i<=5; i++)
			{
				sld = CharacterFromID("FMQN_seafox_"+i);
				sld.lifeday = 0;
			}
			pchar.quest.FMQN_sea_attack.win_condition.l1 = "location";
			pchar.quest.FMQN_sea_attack.win_condition.l1.location = "SentMartin";
			pchar.quest.FMQN_sea_attack.function = "FMQN_EnglandSeaAttack";
		break;
		
		// --> ФМК-Тортуга
		case "FMQT_PirateInTavern": // пирата с ключом - в таверну
			chrDisableReloadToLocation = false;
			iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank);
			iScl = 15 + 2*sti(pchar.rank);// Addon 2016-1 Jason пиратская линейка
			sld = GetCharacter(NPC_GenerateCharacter("FMQT_pirate", "quest_pirat_2", "man", "man", iRank, FRANCE, 1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", "pistol1", "bullet", iScl*2);
			sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Tortuga.c";
			sld.Dialog.currentnode = "pirate";
			sld.name = "Сильвестр";
			sld.lastname = "Маккой";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			AddMoneyToCharacter(sld, 5000);
			GiveItem2Character(sld, "totem_03");
			GiveItem2Character(sld, "potionwine");
			FreeSitLocator("Tortuga_tavern", "sit_front2");
			FreeSitLocator("Tortuga_tavern", "sit_base2");
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "sit", "sit_front2");
			LAi_SetSitType(sld);
		break;
		
		case "FMQT_MercenTalk": // 
			DoQuestCheckDelay("hide_weapon", 1.0);
			sld = CharacterFromID("FMQT_mercen");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "FMQT_MercenHire": // 
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("FMQT_mercen");
			LAi_SetImmortal(sld, false);
			sld.quest.OfficerPrice = sti(pchar.rank)*2000;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.loyality = 30;
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.cirassId = Items_FindItemIdx("cirass8");
			DeleteAttribute(sld, "MultiFighter");
			DeleteAttribute(sld, "MultiShooter");
			LandEnc_OfficerHired();
			FMQT_WifeFinalTalk();
		break;
		
		case "FMQT_MercenDie": // 
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			AddQuestRecord("FMQ_Tortuga", "19");
			FMQT_WifeFinalTalk();
		break;
		
		case "FMQT_MercenDieInRoom": // 
			LAi_group_Delete("EnemyFight");
			sld = CharacterFromID("FMQT_wife");
			sld.Dialog.currentnode = "wife_22";
			ChangeCharacterAddressGroup(sld, "CommonBedroom", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			DeleteAttribute(pchar, "questTemp.FMQT.Roomfight");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
		break;
		
		case "FMQT_FinalFail": // 
			sld = CharacterFromID("FMQT_wife");
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			pchar.questTemp.FMQT = "fail";
			AddQuestRecord("FMQ_Tortuga", "23");
			CloseQuestHeader("FMQ_Tortuga");
		break;
		
		// --> ФМК-Порт Пренс
		case "FMQP_InRoom": // ставим дворянчика и двух балбесов
			iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank)-2;// Addon 2016-1 Jason пиратская линейка
			iScl = 20 + 2*sti(pchar.rank);
			LAi_group_Delete("EnemyFight");
			sld = GetCharacter(NPC_GenerateCharacter("FMQP_noble", "Spain_Major", "man", "man", 15, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 15, 50, 50, "blade_16", "pistol5", "bullet", 120); // may-16
			sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_PortPax.c";
			sld.Dialog.currentnode = "noble";
			sld.name = "Доминго";
			sld.lastname = "Альбалате";
			sld.rank = 15;
			LAi_SetHP(sld, 200, 200);
			SetSelfSkill(sld, 90, 50, 30, 90, 50);
			SetShipSkill(sld, 60, 5, 5, 5, 5, 5, 5, 5, 50);
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "Gunman");
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			ChangeCharacterAddressGroup(sld, "Portpax_tavern_upstairs", "reload", "reload_window");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("FMQP_marginal_"+i, "citiz_4"+i, "man", "man", iRank, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_05","blade_07"), "pistol1", "bullet", iScl*2);
				ChangeCharacterAddressGroup(sld, "Portpax_tavern_upstairs", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQP_AfterFightInRoom");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "FMQP_AfterFightInRoom": // 
			LAi_group_Delete("EnemyFight");
			LAi_SetFightMode(pchar, false);
			chr = CharacterFromID("FMQP_noble");
			sld = GetCharacter(NPC_GenerateCharacter("FMQP_off", "off_fra_1", "man", "man", 15, FRANCE, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, 15, 40, 40, "blade_13", "pistol1", "bullet", 120);
			sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_PortPax.c";
			if (LAi_GetCharacterHP(chr) > 0) sld.Dialog.currentnode = "officer";
			else sld.Dialog.currentnode = "officer_5";
			ChangeCharacterAddressGroup(sld, "Portpax_tavern_upstairs", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FMQP_AfterFightInTown": // 
			sld = CharacterFromID("FMQP_noble");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			LAi_SetImmortal(sld, true);
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("PortPax_waitress");
			LAi_SetWaitressType(sld);
			ChangeCharacterAddressGroup(sld, "Portpax_tavern", "waitress", "barmen");
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			pchar.questTemp.FMQP = "guest";
			AddQuestRecord("FMQ_Portpax", "1");
			pchar.quest.FMQP_sdm.win_condition.l1 = "location";
			pchar.quest.FMQP_sdm.win_condition.l1.location = "SantoDomingo_town";
			pchar.quest.FMQP_sdm.function = "FMQP_InSantoDomingo";
			SetFunctionTimerCondition("FMQP_SantoDomingoOver", 0, 0, 3, false);
		break;
		
		case "FMQP_SantoDomingoAfterFight": // 
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("FMQ_Portpax", "3");
			pchar.quest.FMQP_letter.win_condition.l1 = "item";
			pchar.quest.FMQP_letter.win_condition.l1.item = "letter_parol";
			pchar.quest.FMQP_letter.function = "FMQP_FindLetter";
		break;
		
		case "FMQP_InSantoDomingoTavern": // 
			if(CheckAttribute(pchar, "IsMushketer"))
			{
				SetMainCharacterToMushketer("", false);
			}
			FreeSitLocator("Santodomingo_tavern", "sit_front3");
			FreeSitLocator("Santodomingo_tavern", "sit_base3");
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_12";
			ChangeCharacterAddressGroup(sld, "Santodomingo_tavern", "sit", "sit_front2");
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FMQP_OnBoard": // 
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("FMQP_noble");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			SetFunctionTimerCondition("FMQP_PortobelloTimeOver", 0, 0, 20, false); 
			pchar.questTemp.FMQP = "sail";
			AddQuestRecord("FMQ_Portpax", "5");
			SetFunctionTimerCondition("FMQP_SetRaiders", 0, 0, 3, false);
			pchar.quest.FMQP_plantation.win_condition.l1 = "location";
			pchar.quest.FMQP_plantation.win_condition.l1.location = "PortoBello_Plantation";
			pchar.quest.FMQP_plantation.function = "FMQP_OnPlantation";
			rloc = &Locations[FindLocation("PortoBello_Plantation")];
			DeleteAttribute(rloc, "soldiers");
		break;
		
		case "FMQP_UncleExit": // 
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortoBello_Plantation")], false);
			LocatorReloadEnterDisable("Portobello_exittown", "reload2_back", true);
			sld = CharacterFromID("FMQP_noble");
			sld.lifeday = 0;
			sld = CharacterFromID("FMQP_Uncle");
			sld.lifeday = 0;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("FMQP_guard_"+i);
				sld.lifeday = 0;
			}
			pchar.questTemp.FMQP = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Portpax", "9");
			CloseQuestHeader("FMQ_Portpax");
			SetFunctionTimerCondition("FMQP_OpenPlantation", 0, 0, 10, false); 
			rloc = &Locations[FindLocation("PortoBello_Plantation")];
			rloc.soldiers = true;
		break;
		
		case "FMQP_UncleFight": // 
			LAi_LocationFightDisable(&Locations[FindLocation("PortoBello_Plantation")], false);
			sld = CharacterFromID("FMQP_noble");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_group_Delete("EnemyFight");
			sld = CharacterFromID("FMQP_Uncle");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("FMQP_guard_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQP_UncleAfterFight");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "FMQP_UncleAfterFight": // 
			LAi_group_Delete("EnemyFight");
			sld = CharacterFromID("FMQP_noble");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				sld.Dialog.currentnode = "noble_36";
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
				chrDisableReloadToLocation = false;
				pchar.questTemp.FMQP = "fail";
				AddQuestRecord("FMQ_Portpax", "10");
				CloseQuestHeader("FMQ_Portpax");
				rloc = &Locations[FindLocation("PortoBello_Plantation")];
				rloc.soldiers = true;
			}
		break;
		
		case "FMQP_SDMFail": // 
			sld = CharacterFromID("FMQP_noble");
			sld.lifeday = 0;
			pchar.questTemp.FMQP = "fail";
			AddQuestRecord("FMQ_Portpax", "14");
			CloseQuestHeader("FMQ_Portpax");
		break;
		
		// --> ФМК-Последний урок
		case "FMQL_FirstBattleEnd": // перебили 1 партию индеев
			sld = CharacterFromID("Guide_y");// Addon 2016-1 Jason пиратская линейка
			if (LAi_GetCharacterHP(sld) <= 0)
			{
				FMQL_FailInShore();
			}
			else
			{
				sld.dialog.currentnode = "greguar_3";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "FMQL_SecondBattleEnd": // перебили 2 партию индеев
			InterfaceStates.Buttons.Save.enable = true;// Addon 2016-1 Jason пиратская линейка
			sld = CharacterFromID("Guide_y");
			if (LAi_GetCharacterHP(sld) <= 0)
			{
				FMQL_FailInShore();
			}
			else
			{
				sld.dialog.currentnode = "greguar_4";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "FMQL_JungleExit": // 
			FMQL_ClearAllCharacters();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("shore18", "boat", false);
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			if (pchar.questTemp.FMQL == "shore") AddQuestRecord("FMQ_Lesson", "3");
			else 
			{
				if (pchar.questTemp.FMQL == "poor") AddQuestRecord("FMQ_Lesson", "6");
				else AddQuestRecord("FMQ_Lesson", "2");
			}
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "fail";
		break;
		
		case "FMQL_AfterCaribAttack": // после боя в джунглях
			LAi_group_Delete("EnemyFight");
			sld = CharacterFromID("Guide_y");
			if (LAi_GetCharacterHP(sld) <= 0) // гид дал дуба
			{
				DoQuestCheckDelay("FMQL_JungleExit", 0.5);
			}
			else
			{
				// считаем выживших вояк
				iTotalTemp = 0;
				for (i=1; i<=10; i++)
				{
					if (GetCharacterIndex("FMQL_sailor_"+i) != -1)
					{
						sld = CharacterFromID("FMQL_sailor_"+i);
						if (LAi_GetCharacterHP(sld) > 0) iTotalTemp++;
					}
				}
				sld = CharacterFromID("Guide_y");
				if (iTotalTemp < 3)
				{
					sld.dialog.currentnode = "greguar_11"; // проиграли
					pchar.questTemp.FMQL = "poor";
				}
				else sld.dialog.currentnode = "greguar_13";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "FMQL_RunToGrabbing": // бегут типа в деревню
			sld = CharacterFromID("Guide_y");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "quest", "quest1", "none", "", "", "", 5.0);
			if (GetCharacterIndex("FMQL_Prosper") != -1)
			{
				sld = CharacterFromID("FMQL_Prosper");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "quest1", "none", "", "", "", 5.0);
			}
			if (GetCharacterIndex("FMQL_mercen") != -1)
			{
				sld = CharacterFromID("FMQL_mercen");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "quest1", "none", "", "", "", 5.0);
			}
			for (i=1; i<=10; i++)
			{
				if (GetCharacterIndex("FMQL_sailor_"+i) != -1)
				{
					sld = CharacterFromID("FMQL_sailor_"+i);
					LAi_SetActorType(sld);
					LAi_ActorRunToLocation(sld, "quest", "quest1", "none", "", "", "", 7.0);
				}
			}
			pchar.quest.FMQL_goto_grabbing.win_condition.l1 = "locator";
			pchar.quest.FMQL_goto_grabbing.win_condition.l1.location = "Common_jungle_01";
			pchar.quest.FMQL_goto_grabbing.win_condition.l1.locator_group = "quest";
			pchar.quest.FMQL_goto_grabbing.win_condition.l1.locator = "quest1";
			pchar.quest.FMQL_goto_grabbing.win_condition = "FMQL_Grabbing";
		break;
		
		case "FMQL_Grabbing": // 
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Прошло несколько часов..."+ NewStr() +"Товары доставлены к берегу", "FMQL_GrabbingFinish", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 5, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "FMQL_GrabbingFinish": // 
			DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
			DoQuestReloadToLocation("shore18", "reload", "reload1", "FMQL_BattleAgainstNations");
			// укладываем товары
			int iSanl, iSilk, iRope, iOil;
			iSanl = iTotalTemp*(4+drand(MOD_SKILL_ENEMY_RATE));// Addon 2016-1 Jason пиратская линейка
			iSilk = iTotalTemp*(5+drand(MOD_SKILL_ENEMY_RATE));
			iRope = iTotalTemp*(6+drand(MOD_SKILL_ENEMY_RATE));
			iOil = iTotalTemp*(7+drand(MOD_SKILL_ENEMY_RATE));
			sld = CharacterFromID("Guide_y");
			sld.ShipHideImmortal = 500; // непотопляемый корабль // правки прогона 3
			SetCharacterGoods(sld, GOOD_SANDAL, GetCargoGoods(sld, GOOD_SANDAL) + iSanl);
			pchar.questTemp.FMQL.Sanl = iSanl;
			SetCharacterGoods(sld, GOOD_SHIPSILK, GetCargoGoods(sld, GOOD_SHIPSILK) + iSilk);
			pchar.questTemp.FMQL.Silk = iSilk;
			SetCharacterGoods(sld, GOOD_ROPES, GetCargoGoods(sld, GOOD_ROPES) + iRope);
			pchar.questTemp.FMQL.Rope = iRope;
			SetCharacterGoods(sld, GOOD_OIL, GetCargoGoods(sld, GOOD_OIL) + iOil);
			pchar.questTemp.FMQL.Oil = iOil;
		break;
		
		case "FMQL_BattleAgainstNations": // между англами и голландцами
			iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+2;// Addon 2016-1 Jason пиратская линейка
			iScl = 30 + 2*sti(pchar.rank);
			// наши
			sld = CharacterFromID("Guide_y");
			ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto1");
			LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			if (GetCharacterIndex("FMQL_Prosper") != -1)
			{
				sld = CharacterFromID("FMQL_Prosper");
				ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			if (GetCharacterIndex("FMQL_mercen") != -1)
			{
				sld = CharacterFromID("FMQL_mercen");
				ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=10; i++)
			{
				if (GetCharacterIndex("FMQL_sailor_"+i) != -1)
				{
					sld = CharacterFromID("FMQL_sailor_"+i);
					ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto3");
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			// англы
			sld = GetCharacter(NPC_GenerateCharacter("FMQL_england_6", "off_eng_1", "man", "man", iRank+3, ENGLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank+3, iScl+5, iScl+5, "blade_13", "pistol1", "bullet", iScl*2);
			ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto8");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "TmpEnemy");
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("FMQL_england_"+i, "sold_eng_"+i, "man", "man", iRank, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", iScl*2);
				ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto8");
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "TmpEnemy");
			}
			// голландцы
			sld = GetCharacter(NPC_GenerateCharacter("FMQL_holland_6", "off_hol_1", "man", "man", iRank+3, ENGLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank+3, iScl+5, iScl+5, "blade_10", "pistol1", "bullet", iScl*2);
			ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto7");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("FMQL_holland_"+i, "sold_hol_"+i, "man", "man", iRank, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_09","blade_11","blade_14"), "pistol1", "bullet", iScl*2);
				ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto7");
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
			LAi_group_SetRelation("TmpEnemy", "EnemyFight", LAI_GROUP_ENEMY);
			LAi_group_FightGroups("TmpEnemy", "EnemyFight", true);
			LAi_group_SetCheck("TmpEnemy", "FMQL_EngDestroy");
			LAi_group_SetCheck("EnemyFight", "FMQL_HolDestroy");
		break;
		
		case "FMQL_EngDestroy": // 
			pchar.questTemp.FMQL.EngDestroy = "true";
			if (CheckAttribute(pchar, "questTemp.FMQL.HolDestroy")) DoQuestCheckDelay("FMQL_CoastClear", 1.0);
		break;
		
		case "FMQL_HolDestroy": // 
			pchar.questTemp.FMQL.HolDestroy = "true";
			if (CheckAttribute(pchar, "questTemp.FMQL.EngDestroy")) DoQuestCheckDelay("FMQL_CoastClear", 1.0);
		break;
		
		case "FMQL_CoastClear": // всех перебили
      // --> mitrokosta чистим своих
      for (i=1; i<=10; i++)
      {
        if (GetCharacterIndex("FMQL_sailor_"+i) != -1)
        {
          sld = CharacterFromID("FMQL_sailor_"+i);
          sld.lifeday = 0;
        }
      }
      // <--
			LAi_group_Delete("EnemyFight");
			LAi_group_Delete("TmpEnemy");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			LocatorReloadEnterDisable("shore18", "boat", false);
			sld = CharacterFromID("Guide_y");
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, false);
			SetCharacterRemovable(sld, false);
			sld.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			pchar.quest.FMQL_shipfail_1.win_condition.l1 = "NPC_Death";//прерывание на потопление 
			pchar.quest.FMQL_shipfail_1.win_condition.l1.character = "Guide_y";
			pchar.quest.FMQL_shipfail_1.function = "FMQL_ShipFailReturn";
			if (GetCharacterIndex("FMQL_Prosper") != -1)
			{
				sld = CharacterFromID("FMQL_Prosper");
				AddPassenger(pchar, sld, false);//добавить пассажира
				SetCharacterRemovable(sld, false);
			}
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("FMQL_EngCap_"+i);
				sld.AlwaysEnemy = true;
			}
			Group_SetTaskAttack("FMQL_Enggroup", PLAYER_GROUP);
			Group_LockTask("FMQL_Enggroup");
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("FMQL_HolCap_"+i);
				sld.AlwaysEnemy = true;
			}
			Group_SetTaskAttack("FMQL_Holgroup", PLAYER_GROUP);
			Group_LockTask("FMQL_Holgroup");
			AddQuestRecord("FMQ_Lesson", "5");
			AddQuestUserData("FMQ_Lesson", "sSanl", FindRussianQtyString(sti(pchar.questTemp.FMQL.Sanl)));
			AddQuestUserData("FMQ_Lesson", "sSilk", FindRussianQtyString(sti(pchar.questTemp.FMQL.Silk)));
			AddQuestUserData("FMQ_Lesson", "sRope", FindRussianQtyString(sti(pchar.questTemp.FMQL.Rope)));
			AddQuestUserData("FMQ_Lesson", "sOil", FindRussianQtyString(sti(pchar.questTemp.FMQL.Oil)));
			pchar.quest.FMQL_return.win_condition.l1 = "location";
			pchar.quest.FMQL_return.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.FMQL_return.function = "FMQL_ReturnMartinique";
			SetFunctionTimerCondition("FMQL_ReturnTimeOver", 0, 0, 10, false);
			AddComplexSelfExpToScill(60, 60, 60, 60);
			AddCharacterExpToSkill(pchar, "Leadership", 200);// Addon 2016-1 Jason пиратская линейка
			AddCharacterExpToSkill(pchar, "Fortune", 150);
		break;
		
		case "FMQL_LookOnGuards": // смотрим на гарда
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("FMQL_guard_1"));
			DoQuestCheckDelay("FMQL_LookOnJohnny", 2.0);
		break;
		
		case "FMQL_LookOnJohnny": // смотрим на Джонни
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("FMQL_Johnny"));
			DoQuestCheckDelay("FMQL_JohnnyFire", 2.0);
		break;
		
		case "FMQL_JohnnyFire": // Джонни стреляет в контру
			sld = CharacterFromID("FMQL_Johnny");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "shot", "FMQL_KillSmugglers", 1.0);
			LAi_SetPlayerType(pchar);
		break;
		
		case "FMQL_KillSmugglers": // прибили контриков
			sld = CharacterFromID("FMQL_contra_2");
			LaunchBlastGrenade(sld);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("FMQL_contra_"+i);
				LAi_KillCharacter(sld);
			}
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_20";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 2.0);
		break;
		
		case "FMQL_PeaceFinal": // разошлись миром
			sld = CharacterFromID("Guide_y");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", 10.0);
			sld = CharacterFromID("FMQL_Johnny");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", 10.0);
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("FMQL_guard_"+i);
				sld.lifeday = 0;
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", 10.0);
			}
			i = makeint(iTotalTemp/4);
			AddMoneyToCharacter(pchar, i);
			DoQuestCheckDelay("FMQL_ClearBeach", 11.0);
		break;
		
		case "FMQL_ClearBeach": // чистка квеста
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], false);
			LAi_LocationDisableOfficersGen("Shore38", false);
			locations[FindLocation("Shore38")].DisableEncounters = false; // may-16
			RemoveGeometryFromLocation("Shore38", "smg"); // mitrokosta фикс опечатки
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			AddQuestRecord("FMQ_Lesson", "8");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
			Achievment_SetStat(pchar, 51, 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		// Addon 2016-1 Jason пиратская линейка - это отключаю
		case "FMQL_BattleOnBeach": // решили повоевать
			DoQuestFunctionDelay("Terrapin_SetMusic", 0.2);
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], false);
			LAi_group_Delete("EnemyFight");
			sld = CharacterFromID("Guide_y");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("FMQL_Johnny");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "rld", "loc8", "FMQL_JohnnyPosition", -1);
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("FMQL_guard_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQL_AfterBattleOnBeach");
			LAi_SetFightMode(pchar, true);
			if (GetCharacterIndex("FMQL_Prosper") != -1 && GetCharacterIndex("FMQT_mercen") != -1) 
			{
				DoQuestCheckDelay("FMQL_BattleOnBeachHelp", 120.0); // may-16
				pchar.GenQuest.FrameLockEsc = true;
				pchar.questTemp.FMQL.Cpy = "true";
			}
		break;
		
		case "FMQL_JohnnyPosition": // 
			sld = CharacterFromID("FMQL_Johnny");
			sld.MusketerDistance = 0;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			DoQuestCheckDelay("FMQL_JohnnyChangePosition", 15.0); // may-16
		break;
		
		case "FMQL_JohnnyChangePosition": // may-16
			if (pchar.questTemp.FMQL == "end") break; // патч 17/1
			sld = CharacterFromID("FMQL_Johnny");
			sld.MusketerDistance = 20;
			DoQuestCheckDelay("FMQL_JohnnyChangePosition1", 3.0);
		break;
		
		case "FMQL_JohnnyChangePosition1": // may-16
			sld = CharacterFromID("FMQL_Johnny");
			sld.MusketerDistance = 0;
			DoQuestCheckDelay("FMQL_JohnnyChangePosition", 25.0);
		break;
		
		case "FMQL_BattleOnBeachHelp": // прибежали Проспер и пиратус
			sld = CharacterFromID("FMQL_Prosper");
			sld.Dialog.currentnode = "prosper_11";
			LAi_SetCheckMinHP(sld, 10, true, "FMQL_ProsperDead");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore38", "reload", "reload1");
			LAi_ActorRunToLocator(sld, "goto", "goto8", "FMQL_BattleOnBeachMushketer", -1);
			sld = CharacterFromID("FMQT_mercen");
			LAi_SetCheckMinHP(sld, 10, true, "FMQL_PirateDead");
			ChangeCharacterAddressGroup(sld, "Shore38", "reload", "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			pchar.quest.FMQL_prosper_dead.win_condition.l1 = "NPC_Death";
			pchar.quest.FMQL_prosper_dead.win_condition.l1.character = "FMQL_Prosper";
			pchar.quest.FMQL_prosper_dead.function = "FMQL_ProsperDead";
			pchar.quest.FMQL_pirate_dead.win_condition.l1 = "NPC_Death";
			pchar.quest.FMQL_pirate_dead.win_condition.l1.character = "FMQT_mercen";
			pchar.quest.FMQL_pirate_dead.function = "FMQL_PirateDead";
		break;
		
		case "FMQL_PirateDead": // 
			sld = CharacterFromID("FMQT_mercen");
			LAi_KillCharacter(sld);
		break;
		
		case "FMQL_ProsperDead": // 
			sld = CharacterFromID("FMQL_Prosper");
			LAi_KillCharacter(sld);
		break;
		
		case "FMQL_BattleOnBeachMushketer": // 
			sld = CharacterFromID("FMQL_Prosper");
			sld.MusketerDistance = 0;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
		
		case "FMQL_AfterBattleOnBeach": // закончили бой с кодлой Валинье
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			RemoveGeometryFromLocation("Shore38", "smg");
			LAi_group_Delete("EnemyFight");
			SetCharacterGoods(pchar, GOOD_SANDAL, GetCargoGoods(sld, GOOD_SANDAL) + sti(pchar.questTemp.FMQL.Sanl));
			SetCharacterGoods(pchar, GOOD_SHIPSILK, GetCargoGoods(sld, GOOD_SHIPSILK) + sti(pchar.questTemp.FMQL.Silk));
			SetCharacterGoods(pchar, GOOD_ROPES, GetCargoGoods(sld, GOOD_ROPES) + sti(pchar.questTemp.FMQL.Rope));
			SetCharacterGoods(pchar, GOOD_OIL, GetCargoGoods(sld, GOOD_OIL) + sti(pchar.questTemp.FMQL.Oil));
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			LAi_LocationDisableOfficersGen("Shore38", false);
			locations[FindLocation("Shore38")].DisableEncounters = false;
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			if (CheckAttribute(pchar, "questTemp.FMQL.Cpy"))
			{
				DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
				DeleteAttribute(pchar, "questTemp.FMQL.Cpy");
				if (!CheckAttribute(pchar, "questTemp.FMQL.PirateDead")) // пират жив
				{
					sld = CharacterFromID("FMQT_mercen");
					sld.dialog.FileName = "Quest\LineMiniQuests\FMQ_Lesson.c";
					sld.Dialog.currentnode = "FMQL_beach";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0); 
				}
				else
				{
					if (!CheckAttribute(pchar, "questTemp.FMQL.ProsperDead")) // Проспер жив
					{
						sld = CharacterFromID("FMQL_Prosper");
						sld.Dialog.currentnode = "prosper_11";
						sld.MusketerDistance = 20;
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0); 
					}
					else // никого не осталось
					{
						if (sti(pchar.money) >= 20000) DoQuestFunctionDelay("FMQL_MoneyForSelina", 0.5);
						else
						{
							pchar.quest.FMQL_money_20k.win_condition.l1 = "Money";
							pchar.quest.FMQL_money_20k.win_condition.l1.value = 20000;
							pchar.quest.FMQL_money_20k.win_condition.l1.operation = ">=";
							pchar.quest.FMQL_money_20k.function = "FMQL_MoneyForSelina";
						}
						chrDisableReloadToLocation = false;
						AddQuestRecord("FMQ_Lesson", "10");
						CloseQuestHeader("FMQ_Lesson");
						pchar.questTemp.FMQL = "end";
					}
				}
			}
			else
			{
				chrDisableReloadToLocation = false;
				AddQuestRecord("FMQ_Lesson", "9");
				CloseQuestHeader("FMQ_Lesson");
				pchar.questTemp.FMQL = "end";
			}
			Achievment_SetStat(pchar, 51, 1);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 7);
		break;
		
		case "FMQL_PirateNormal": // 
			sld = CharacterFromID("FMQT_mercen");
			LAi_SetOfficerType(sld);
			sld.dialog.FileName = "Enc_Officer_dialog.c";
			sld.Dialog.currentnode = "hired";
		break;
		
		case "FMQL_CanibBossAmulet": // 
			sld = CharacterFromID("FMQL_canib_chief");
			RemoveAllCharacterItems(sld, true);
			sld.SaveItemsForDead = true; 
			sld.DontClearDead = true;
			GiveItem2Character(sld, "indian_1");
			GiveItem2Character(sld, "indian_7");
			GiveItem2Character(sld, "obereg_5");
			GiveItem2Character(sld, "obereg_6");
			GiveItem2Character(sld, "obereg_3");
			LAi_KillCharacter(sld);
		break;
		
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Addon 2016-1 Jason Пиратская линейка
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// эпизод 2
		case "Mtraxx_SilkWrongTalk": // неверный вариант диалога с приемщиками шелка
			chrDisableReloadToLocation = false;
			AddQuestRecord("Roger_2", "14");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Silkfail");
			Mtraxx_TerraxReset(2);
		break;
		
		// эпизод 3
		case "Mtraxx_PlantChestReady": // подготовить сундук
			DoQuestCheckDelay("TalkSelf_Quest", 1.5);
		break;
		
		case "Mtraxx_PlantChestReadyExit": // сундук готов
			DeleteAttribute(pchar, "questTemp.Mtraxx.Chest");
			pchar.questTemp.Mtraxx.Ammo = "true";
		break;
		
		case "Mtraxx_PlantWaitDay": // 
			DoQuestReloadToLocation("Maracaibo_Plantation", "goto", "goto18", "Mtraxx_PlantTrading");
		break;
		
		case "Mtraxx_PlantTrading": // торгуем - обмен товарами
			if (GetSquadronGoods(pchar, sti(pchar.questTemp.Mtraxx.PlantGood.Cargo)) < 500) // не хватило товара на торговлю - провал
			{
				chrDisableReloadToLocation = false;
				DeleteAttribute(pchar, "questTemp.Mtraxx.PlantGood");
				DeleteAttribute(pchar, "questTemp.Mtraxx.Weapon");
				sld = characterFromId("Mtr_plantation_boss");
				sld.lifeday = 0;
				sld = characterFromId("Mrt_Rocur");
				sld.lifeday = 0;
				sld = characterFromId("Mrt_Rocur_clone");
				sld.lifeday = 0;
				AddQuestRecord("Roger_3", "11");
				Mtraxx_PlantPellyClear();
				Mtraxx_TerraxReset(3);
			}
			else 
			{
				RemoveCharacterGoods(pchar, sti(pchar.questTemp.Mtraxx.PlantGood.Cargo), 500);
				SetCharacterGoods(pchar, GOOD_SUGAR, GetCargoGoods(pchar, GOOD_SUGAR) + sti(pchar.questTemp.Mtraxx.PlantGood.Sugar));
				SetCharacterGoods(pchar, GOOD_CHOCOLATE, GetCargoGoods(pchar, GOOD_CHOCOLATE) + sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa));
				DeleteAttribute(pchar, "questTemp.Mtraxx.PlantGood");
				sld = characterFromId("Mtr_plantation_boss");
				sld.dialog.currentnode = "mtraxx_9";
				ChangeCharacterAddressGroup(sld, "Maracaibo_Plantation", "goto", "goto17");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			n = Findlocation("Shore37");
			DeleteAttribute(&locations[n], "models.always.chest");
			Locations[n].models.always.locators = "shore03_locators";
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Sneak", 300);
		break;
		
		case "Mtraxx_PlantPrepareMarch": // готовим к ночному маршу
			DoQuestReloadToLocation("shore37", "goto", "goto3", "Mtraxx_PlantGotoMarch");
			sld = &Locations[FindLocation("shore37")];
			sld.DisableEncounters = false;
			chr = ItemsFromID("fire");
			chr.shown = false;
			DeleteAttribute(sld, "fire");
			for (i=1; i<=4; i++)
			{
				if (GetCharacterIndex("Pelly_sailor_"+i) != -1)
				{
					sld = characterFromId("Pelly_sailor_"+i);
					sld.lifeday = 0;
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
		break;
		
		case "Mtraxx_PlantGotoMarch": // собираем пиратов для похода к плантации
			// ставим наших пиратов
			chrDisableReloadToLocation = true;
			sld = characterFromId("Pelly");
			sld.dialog.currentnode = "Pelly_12";
			ChangeCharacterAddressGroup(sld, "shore37", "goto", "goto6");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			iRank = sti(pchar.rank)+5;
			iScl = 30 + 2*sti(pchar.rank);
			for (i=1; i<=7; i++)
			{
				if (i == 7)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Mtr_PellyPirate_"+i, "mush_ctz_7", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket3", "grapeshot", iScl*3);
					TakeNItems(pchar, "grapeshot", 40);
					TakeNItems(pchar, "gunpowder", 40);
					LAi_SetCharacterUseBullet(sld, "grapeshot");
					ChangeCharacterAddressGroup(sld, "shore37", "goto", "goto5");
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("Mtr_PellyPirate_"+i, "citiz_4"+i, "man", "man", iRank, PIRATE, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_08","blade_11","blade_14"), "pistol1", "bullet", iScl*2);
				}
				ChangeCharacterAddressGroup(sld, "shore37", "goto", "goto"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		break;
		
		case "Mtraxx_PlantJanReady": // снять бессмертие с Пикара
			sld = characterFromId("Mrt_Rocur");
			LAi_SetImmortal(sld, false);
		break;
		
		case "Mtraxx_PlantMutinyAfterFight": // перебили охрану на плантации
			pchar.quest.mtraxx_plant_exitopen.win_condition.l1 = "locator";
			pchar.quest.mtraxx_plant_exitopen.win_condition.l1.location = "Maracaibo_Plantation";
			pchar.quest.mtraxx_plant_exitopen.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_plant_exitopen.win_condition.l1.locator = "reload2_back";
			pchar.quest.mtraxx_plant_exitopen.function = "Mtraxx_PlantExitopen";
		break;
		
		case "Mtraxx_PlantEscape": // сбежали с плантации
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload2_back", true);
			LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload3_back", true);
			LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload4", true);
			// собираем всех, кто выжил, кроме пиратов Пикара - дают вылет
			sld = characterFromId("Pelly");
			LAi_SetImmortal(sld, false); 
			ChangeCharacterAddressGroup(sld, "Maracaibo_ExitTown", "rld", "loc17");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			if (GetCharacterIndex("Mrt_Rocur") != -1)
			{
				sld = characterFromId("Mrt_Rocur");
				ChangeCharacterAddressGroup(sld, "Maracaibo_ExitTown", "rld", "loc16");
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=7; i++)
			{
				if (GetCharacterIndex("Mtr_PellyPirate_"+i) != -1)
				{
					sld = CharacterFromID("Mtr_PellyPirate_"+i);
					ChangeCharacterAddressGroup(sld, "Maracaibo_ExitTown", "rld", "loc18");
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			pchar.quest.mtraxx_plant_escape.win_condition.l1 = "location";
			pchar.quest.mtraxx_plant_escape.win_condition.l1.location = "shore37";
			pchar.quest.mtraxx_plant_escape.function = "Mtraxx_PlantEscapeInShore";
			AddQuestRecord("Roger_3", "21");
			AddComplexSelfExpToScill(80, 80, 80, 80);
		break;
		
		case "Mtraxx_PlantMutinyAfterFortFight": // после боя с подкреплением
			DeleteAttribute(pchar, "questTemp.Mtraxx.PlantFort");
			pchar.quest.mtraxx_plant_exitopen1.win_condition.l1 = "locator";
			pchar.quest.mtraxx_plant_exitopen1.win_condition.l1.location = "Maracaibo_Plantation";
			pchar.quest.mtraxx_plant_exitopen1.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_plant_exitopen1.win_condition.l1.locator = "reload2_back";
			pchar.quest.mtraxx_plant_exitopen1.function = "Mtraxx_PlantExitopen";
		break;
		
		// эпизод 4
		case "Mtraxx_PasqualeNightTalk": // в заливе - старт похода в Ла Вегу
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_71";
			ChangeCharacterAddressGroup(sld, "Shore34", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Mtraxx_PasqualeNightToHouse": // релоад в дом
			DoQuestReloadToLocation("LaVega_TwoFloorHouse", "reload", "reload1", "Mtraxx_PasqualeNightInHouse");
		break;
		
		case "Mtraxx_PasqualeNightInHouse": // в доме
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_73";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 2.0);
		break;
		
		case "Mtraxx_PasqualeJanAni": // Жан ковыряется в сундуках
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Barman_idle", "", 90.0);
			DoQuestFunctionDelay("Mtraxx_PasqualeJanTreasure", 90.0);
		break;
		
		case "Mtraxx_PasqualeJanSeeGirl": // Жан видит Мирабель
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Mtraxx_PasqualeJanKillGirl": // Жан убивает Мирабель
			sld = characterFromId("Mirabella");
			LAi_KillCharacter(sld);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "Mtraxx_PasqualeJanGotcha", -1);
		break;
		
		case "Mtraxx_PasqualeJanGotcha": // Жан делится добычей
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_83";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Mtraxx_PasqualeNightOutHouse": // релоад из дома
			DoQuestReloadToLocation("LaVega_town", "reload", "reload10", "Mtraxx_PasqualeNightOutLaVega");
		break;
		
		case "Mtraxx_PasqualeNightOutLaVega": // релоад из Ла Веги
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "LaVega_Exittown", "reload", "reload3", "Mtraxx_PasqualeNightSuccess", -1);
		break;
		
		case "Mtraxx_PasqualeNightSuccess": // завершили поход к Паскуале
			DoQuestReloadToLocation("LaVega_Exittown", "reload", "reload3", "Mtraxx_PasqualeNightReturn");
		break;
		
		case "Mtraxx_PasqualeNightReturn": // идем назад в залив Гонаив
			LocatorReloadEnterDisable("LaVega_Exittown", "reload3", true);
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_89";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Mtraxx_MirabellaSex": // секс с Мирабель
			sld = characterFromId("Mirabella");
			ChangeCharacterAddressGroup(sld, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestFunctionDelay("Mtraxx_MirabellaSex", 1.5);
		break;
		
		// эпизод 5
		case "Mtraxx_MeridaAddPicar": // Пикара в пассажиры
			chrDisableReloadToLocation = false;
			sld = characterFromId("Mrt_Rocur");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
		break;
		
		case "Mtraxx_MeridaGotoRiver": // открываем путь к реке
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_merida_gotoriver.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_gotoriver.win_condition.l1.location = "Locono_village";
			pchar.quest.mtraxx_merida_gotoriver.win_condition = "Mtraxx_MeridaGotoRiver_1";
			n = Findlocation("Maracaibo_jungle_04");
			locations[n].locators_radius.reload.reload2_back = 2.0;
		break;
		
		case "Mtraxx_MeridaGotoRiver_1": // Тагофа ведет нас к реке
			chrDisableReloadToLocation = true;
			sld = characterFromId("Tagofa");
			ChangeCharacterAddressGroup(sld, "Locono_village", "quest", "teleport1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.mtraxx_merida_gotoriver1.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_gotoriver1.win_condition.l1.location = "Maracaibo_jungle_03";
			pchar.quest.mtraxx_merida_gotoriver1.win_condition = "Mtraxx_MeridaGotoRiver_2";
		break;
		
		case "Mtraxx_MeridaGotoRiver_2": // Тагофа ведет нас к реке
			chrDisableReloadToLocation = true;
			sld = characterFromId("Tagofa");
			ChangeCharacterAddressGroup(sld, "Maracaibo_jungle_03", "reload", "reload2_back");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorGoToLocation(sld, "reload", "reload3_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.mtraxx_merida_gotoriver2.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_gotoriver2.win_condition.l1.location = "Maracaibo_jungle_04";
			pchar.quest.mtraxx_merida_gotoriver2.win_condition = "Mtraxx_MeridaGotoRiver_3";
		break;
		
		case "Mtraxx_MeridaGotoRiver_3": // Тагофа ведет нас к реке
			chrDisableReloadToLocation = true;
			sld = characterFromId("Tagofa");
			ChangeCharacterAddressGroup(sld, "Maracaibo_jungle_04", "reload", "reload1_back");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorGoToLocation(sld, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.mtraxx_merida_gotoriver3.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_gotoriver3.win_condition.l1.location = "Maracaibo_river";
			pchar.quest.mtraxx_merida_gotoriver3.win_condition = "Mtraxx_MeridaGotoRiver_4";
		break;
		
		case "Mtraxx_MeridaGotoRiver_4": // Тагофа ведет нас к реке
			chrDisableReloadToLocation = true;
			sld = characterFromId("Tagofa");
			ChangeCharacterAddressGroup(sld, "Maracaibo_river", "reload", "reload1_back");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorGoToLocator(sld, "goto", "goto10", "Mtraxx_MeridaGotoRiver_5", -1);
		break;
		
		case "Mtraxx_MeridaGotoRiver_5": // Тагофа ведет нас к реке
			sld = characterFromId("Tagofa");
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
		
		case "Mtraxx_MeridaBuildBoats": // лодки построены
			bDisableCharacterMenu = false;
			DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
			n = makeint(sti(pchar.questTemp.Mtraxx.Merida.Antidote)/6);
			for (i=5; i<=9; i++) // ребята Леприкона
			{
				sld = characterFromId("Lepricons_pirate_"+i);
				ChangeCharacterAddressGroup(sld, "Maracaibo_river", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=8; i++) // наши красавцы
			{
				if (i > 6)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Merida_pirate_"+i, "mush_ctz_"+i, "man", "mushketer", 20, PIRATE, -1, false, "quest"));
					FantomMakeCoolFighter(sld, 20, 60, 60, "", "mushket3", "grapeshot", 150);
					LAi_SetCharacterUseBullet(sld, "grapeshot");
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("Merida_pirate_"+i, "citiz_4"+i, "man", "man", 18, PIRATE, -1, true, "quest"));
					FantomMakeCoolFighter(sld, 18, 50, 50, LinkRandPhrase("blade_07","blade_08","blade_11"), "pistol3", "grapeshot", 120);
				}
				TakeNItems(sld, "potion3", n);
				LAi_CharacterDisableDialog(sld);
				ChangeCharacterAddressGroup(sld, "Maracaibo_river", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			DoQuestReloadToLocation("Maracaibo_river", "goto", "goto3", "");
			AddQuestRecord("Roger_5", "14");
		break;
		
		case "Mtraxx_MeridaRiverTrip": // плывем по реке на лодках
			bDisableCharacterMenu = true;
			pchar.GenQuest.FrameLockEsc = true;
			SetMusic("music_map");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\River_1.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 2, 2, 20); //крутим время
			RecalculateJumpTable();
			StoreDayUpdate();
			RefreshWeather();
			RefreshLandTime();
			DoQuestCheckDelay("Mtraxx_MeridaRiverTripEnd", 15.0);
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Potion");
			LocatorReloadEnterDisable("Shore_ship3", "boat", false); // выпустим в море
		break;
		
		case "Mtraxx_MeridaRiverTripEnd": // приплыли
			n = Findlocation("Serpentine1");
			for (i=1; i<=6; i++)
			{
				sTemp = "Boat"+i;
				locations[n].models.always.(sTemp) = "Boat";
				Locations[n].models.always.(sTemp).locator.group = "quest";
				Locations[n].models.always.(sTemp).locator.name = "boat"+i;
				Locations[n].models.always.(sTemp).tech = "DLightModel";
			}
			n = Findlocation("Serpentine2");
			locations[n].models.always.sign = "StoneMap";
			Locations[n].models.always.sign.locator.group = "quest";
			Locations[n].models.always.sign.locator.name = "quest1";
			Locations[n].models.always.sign.tech = "DLightModel";
			DoQuestReloadToLocation("Serpentine1", "reload", "reload3", "Mtraxx_MeridaSerpentine");
		break;
		
		case "Mtraxx_MeridaSerpentine": // прибыли в точку высадки
			bDisableCharacterMenu = false;
			DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
			for (i=1; i<=3; i++)
			{
				idx = GetOfficersIndex(pchar, i);
				if (idx < 1) continue;
				sld = &Characters[idx];
				ChangeCharacterAddressGroup(sld, "Serpentine1", "officers", "reload2_"+i);
			}
			for (i=5; i<=9; i++) // ребята Леприкона
			{
				sld = characterFromId("Lepricons_pirate_"+i);
				ChangeCharacterAddressGroup(sld, "Serpentine1", "goto", "goto11");
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			for (i=1; i<=8; i++) // наши красавцы
			{
				sld = characterFromId("Merida_pirate_"+i);
				ChangeCharacterAddressGroup(sld, "Serpentine1", "goto", "goto12");
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			sld = characterFromId("Lepricon");
			ChangeCharacterAddressGroup(sld, "Serpentine1", "goto", "goto10");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = characterFromId("Tagofa");
			sld.dialog.currentnode = "tagofa_11";
			ChangeCharacterAddressGroup(sld, "Serpentine1", "goto", "goto10");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Mtraxx_MeridaWarning": // знак капонгов на тропе
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Tagofa");
			sld.dialog.currentnode = "tagofa_15";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		
		case "Mtraxx_MeridaCapongAfterFight": // после боя с капонгами
			LAi_group_Delete("EnemyFight");
			sld = characterFromId("Tagofa");
			sld.dialog.currentnode = "tagofa_18";
			ChangeCharacterAddressGroup(sld, "Merida_jungle_01", "reload", "reload1_back");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "Mtraxx_MeridaGateAfterBattle": // после боя у ворот
			LAi_group_Delete("EnemyFight");
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_38";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "Mtraxx_MeridaAfterBattle": // после боя в городе
			LAi_group_Delete("EnemyFight");
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_40";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddComplexSelfExpToScill(20, 20, 20, 20);
		break;
		
		case "Mtraxx_MeridaOpenChest": // губер открывает свой сундук
			PlaySound("interface\key.wav");
			sld = characterFromId("Merida_head");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto1", "Mtraxx_MeridaOpenChest1", -1);
		break;
		
		case "Mtraxx_MeridaOpenChest1": // губер открывает свой сундук
			sld = characterFromId("Merida_head");
			sld.dialog.currentnode = "merida_head_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Mtraxx_MeridaGiveJewelry": // Пикар забирает камни
			PlaySound("interface\important_item.wav");
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_42";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 2.0);
		break;
		
		case "Mtraxx_MeridaCaveAfterFight": // после боя в пещере с капонгами
			AddQuestRecord("Roger_5", "13");
			Mtraxx_MeridaCheckOurWarriors();
			chrDisableReloadToLocation = false;
			sld = characterFromId("Tagofa");
			ChangeCharacterAddressGroup(sld, "Serpentine_cave", "reload", "reload1_back");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.mtraxx_merida_return.win_condition.l1 = "locator";
			pchar.quest.mtraxx_merida_return.win_condition.l1.location = "Serpentine1";
			pchar.quest.mtraxx_merida_return.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_merida_return.win_condition.l1.locator = "reload3";
			pchar.quest.mtraxx_merida_return.function = "Mtraxx_MeridaReturn";
			AddComplexSelfExpToScill(30, 30, 30, 30);
		break;
		
		case "Mtraxx_MeridaReturnEnd": // вернулись к Маракайбо
			bDisableCharacterMenu = false;
			DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
			chrDisableReloadToLocation = true;
			sld = characterFromId("Tagofa");
			sld.dialog.currentnode = "tagofa_20";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// эпизод 6
		case "Mtraxx_IgnasioInTavern": // 
			if(CheckAttribute(pchar, "IsMushketer"))
			{
				SetMainCharacterToMushketer("", false);
			}
			FreeSitLocator("Bridgetown_tavern", "sit_base2");
			DoQuestReloadToLocation("Bridgetown_tavern", "sit", "sit_base2", "");			
			sld = characterFromID("Ignasio");
			sld.dialog.currentnode = "ignasio_4";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		
		case "Mtraxx_IgnasioEscape": // 
			sld = GetCharacter(NPC_GenerateCharacter("Ignasio_spy", "citiz_35", "man", "man", 25, FRANCE, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, 25, 30, 30, "blade_05", "pistol1", "bullet", 120);
			sld.Dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "spy_sailor";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
		
		// эпизод 7
		case "Mtraxx_WolfreekGrotAfterFight": // перебили карибов
			chrDisableReloadToLocation = false;
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("Roger_7", "3");
			pchar.questTemp.Mtraxx.Grotbox = "true";
			AddComplexSelfExpToScill(30, 30, 30, 30);
		break;
		
		case "Mtraxx_WolfreekCaveAfterFight": // перебили босяков
			chrDisableReloadToLocation = false;
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("Roger_7", "6");
			AddComplexSelfExpToScill(20, 20, 20, 20);
		break;
		
		case "Mtraxx_WolfreekPelly": // 
			AddQuestRecord("Roger_7", "11");
			LAi_SetPlayerType(pchar);
			DoQuestFunctionDelay("Mtraxx_WolfreekPelly", 30.0);
			InterfaceStates.Buttons.Save.enable = false;
			pchar.GenQuest.FrameLockEsc = true; 
		break;
		
		case "Mtraxx_WolfreekJewellerWait": // 
			SetLaunchFrameFormParam("Прошло три часа...", "", 0, 5);//табличка
			WaitDate("", 0, 0, 0, 3, 20); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			DoQuestFunctionDelay("Mtraxx_WolfreekSetPelly", 1.0);
		break;
		
		case "Mtraxx_WolfreekIslaMonaAfterFight": // 
			chrDisableReloadToLocation = false;
			AddQuestRecord("Roger_7", "17");
			AddComplexSelfExpToScill(30, 30, 30, 30);
			// ставим троих в форте
			sld = GetCharacter(NPC_GenerateCharacter("Islamona_carpenter", "mercen_30", "man", "man", 25, PIRATE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 60, 60, "topor_02", "pistol1", "bullet", 100);
			sld.Dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "carpenter";
			sld.name = "Родгар";
			sld.lastname = "Янссен";
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "IslaMona_fort", "goto", "character3");
			LAi_SetActorType(sld);
			for (i=1; i<=2; i++) // 
			{
				sld = GetCharacter(NPC_GenerateCharacter("Islamona_fort_pirate_"+i, "citiz_4"+(7+i), "man", "man", 18, PIRATE, -1, true, "quest"));
				FantomMakeCoolFighter(sld, 18, 50, 50, LinkRandPhrase("blade_07","blade_08","blade_11"), "pistol1", "bullet", 100);
				LAi_CharacterDisableDialog(sld);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "IslaMona_fort", "goto", "character"+i);
			}
			pchar.quest.mtraxx_wolfreek_cannon.win_condition.l1 = "locator";
			pchar.quest.mtraxx_wolfreek_cannon.win_condition.l1.location = "IslaMona_fort";
			pchar.quest.mtraxx_wolfreek_cannon.win_condition.l1.locator_group = "quest";
			pchar.quest.mtraxx_wolfreek_cannon.win_condition.l1.locator = "detector";
			pchar.quest.mtraxx_wolfreek_cannon.function = "Mtraxx_WolfreekCannon";
			pchar.quest.mtraxx_wolfreek_cpy.win_condition.l1 = "location";
			pchar.quest.mtraxx_wolfreek_cpy.win_condition.l1.location = "IslaMona";
			pchar.quest.mtraxx_wolfreek_cpy.function = "Mtraxx_WolfreekCpy";
		break;
		
		case "Mtraxx_WolfreekInFort": // 
			chrDisableReloadToLocation = false;
			AddQuestRecord("Roger_7", "18");
			pchar.questTemp.Mtraxx.WolfreekBox = "true";
		break;
		
		case "Mtraxx_WolfreekRepairShore": // // прогона 3
			DoQuestCheckDelay("Mtraxx_WolfreekRepairActivate", 2.0);
		break;
		
		case "Mtraxx_WolfreekRepairActivate": // 
			LaunchRepair(pchar);
			chrDisableReloadToLocation = false;
		break;
		
		// эпизод 8
		case "Mtraxx_CorridaSenPierre": // 
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			bDisableCharacterMenu = false; // разлочим F2
			bQuestDisableMapEnter = false;
			setCharacterShipLocation(pchar, "FortFrance_town");
			setWDMPointXZ("FortFrance_town");
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("LeFranua_town", "reload6", true);
			pchar.GenQuest.CannotWait = true;
			AddQuestRecord("Roger_8", "2");
			pchar.quest.mtraxx_corrida_lefransua.win_condition.l1 = "locator";
			pchar.quest.mtraxx_corrida_lefransua.win_condition.l1.location = "LeFransua_town";
			pchar.quest.mtraxx_corrida_lefransua.win_condition.l1.locator_group = "quest";
			pchar.quest.mtraxx_corrida_lefransua.win_condition.l1.locator = "detector1";
			pchar.quest.mtraxx_corrida_lefransua.function = "Mtraxx_CorridaSeeMarko";
			n = Findlocation("LeFransua_town");
			locations[n].locators_radius.quest.detector1 = 2.0;
		break;
		
		case "Mtraxx_CorridaSeeMarko": // 
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload6");
		break;
		
		case "Mtraxx_CorridaSeeMarko1": // 
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
		break;
		
		case "Mtraxx_CorridaWaitMarko": // 
			DoQuestCheckDelay("Mtraxx_CorridaWaitMarkoFrame", 5.0);
		break;
		
		case "Mtraxx_CorridaWaitMarkoFrame": // 
			SetLaunchFrameFormParam("Прошло два часа..."+ NewStr() +"", "Mtraxx_CorridaMarkoExit", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
			StoreDayUpdate();
			RefreshWeather();
			RefreshLandTime();
		break;
		
		case "Mtraxx_CorridaMarkoExit": // 
			sld = CharacterFromID("Ignasio");
			ChangeCharacterAddressGroup(sld, "LeFransua_town", "reload", "reload6");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Mtraxx_CorridaMarkoGone", -1);
			sld = CharacterFromID("Mtr_Vagrant");
			ChangeCharacterAddressGroup(sld, "LeFransua_town", "reload", "reload6");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			sld = CharacterFromID("Mtr_vampire");
			ChangeCharacterAddressGroup(sld, "LeFransua_town", "reload", "reload6");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			DoQuestCheckDelay("Mtraxx_CorridaSeeMarko1", 8.0);
		break;
		
		case "Mtraxx_CorridaMarkoGone": // 
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Roger_8", "3");
			Group_DelCharacter("IgnasioSeaGroup", "Ignasio");
			Group_DelCharacter("IgnasioSeaGroup", "Mtr_Vagrant");
			Group_DelCharacter("IgnasioSeaGroup", "Mtr_vampire");
			Group_DeleteGroup("IgnasioSeaGroup");
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("LeFranua_town", "reload6", false);
			setCharacterShipLocation(pchar, "FortFrance_town");
			setWDMPointXZ("FortFrance_town");
			pchar.quest.mtraxx_corrida_martinique1.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_martinique1.win_condition.l1.location = "Martinique";
			pchar.quest.mtraxx_corrida_martinique1.function = "Mtraxx_CorridaContinue";
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);
		break;
			
		// эпизод 9
		case "Mtraxx_CartahenaReloadInTavern": // телепорт в таверну
			iTime = sti(environment.time);
			if (iTime >= 21) iAddTime = 24 - iTime;
			if (iTime < 7) iAddTime = 21 - iTime;
			if (iTime >= 7 && iTime < 21) iAddTime = 21 - iTime;
			WaitDate("", 0, 0, 0, iAddTime, 5); //крутим время
			RefreshWeather();
			RefreshLandTime();
			pchar.questTemp.Mtraxx.InTavern = "true";
			// чистим все места, если уже был заход в таверну
			for (i=1; i<=4; i++)
			{
				FreeSitLocator("LaVega_tavern", "sit_front"+i);
				FreeSitLocator("LaVega_tavern", "sit_base"+i);
				FreeSitLocator("LaVega_tavern", "sit"+i);
			}
			LAi_LocationDisableOfficersGen("LaVega_tavern", true);
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "LaVega_tavern";
			sld.startLocator = "quest1";
			DoQuestReloadToLocation("LaVega_tavern", "reload", "reload1_back", "Mtraxx_CartahenaInTavern");
		break;
		
		case "Mtraxx_CartahenaInTavern": // братва в таверне
			pchar.questTemp.NoFast = true; // запрет ускорения
			// ГГ - пират на весь эпизод
	PChar.nation	= PIRATE;
			pchar.DisableChangeFlagMode = true;
			// установим клон Бернара Венсана
			sld = GetCharacter(NPC_GenerateCharacter("Mtr_Vensan", "Vensan", "man", "man", 20, PIRATE, -1, true, "quest"));
			FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, "Разлучница", CANNON_TYPE_CANNON_LBS16, 50, 50, 50);
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_16", "pistol5", "bullet", 100);
			sld.name = "Бернар";
			sld.lastname = "Венсан";
			sld.rank = 22;
			sld.reputation = 25;
			SetSelfSkill(sld, 80, 30, 30, 70, 50);
			SetShipSkill(sld, 45, 80, 50, 50, 50, 60, 50, 60, 50);
			SetCharacterGoods(sld, GOOD_BALLS, 400);
			SetCharacterGoods(sld, GOOD_GRAPES, 400);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 300);
			SetCharacterGoods(sld, GOOD_BOMBS, 500);
			SetCharacterGoods(sld, GOOD_POWDER, 1600);
			SetCharacterGoods(sld, GOOD_WEAPON, 200);
			SetCharacterGoods(sld, GOOD_FOOD, 400);
			SetCharacterGoods(sld, GOOD_MEDICAMENT, 200);
			SetCharacterGoods(sld, GOOD_RUM, 70);
			SetCharacterGoods(sld, GOOD_PLANKS, 20);
			SetCharacterGoods(sld, GOOD_SAILCLOTH, 10);
			ChangeCharacterAddressGroup(sld, "LaVega_tavern", "sit", "sit_base2");
			LAi_SetSitType(sld);
			sld = characterFromId("Jeffry");
			FantomMakeCoolSailor(sld, SHIP_EASTINDIAMAN, "Снэйк", CANNON_TYPE_CANNON_LBS24, 80, 80, 80);
			sld.nation = PIRATE;
			ChangeCharacterAddressGroup(sld, "LaVega_tavern", "sit", "sit_front1");
			LAi_SetSitType(sld);
			sld = characterFromId("Terrax");
			ChangeCharacterAddressGroup(sld, "LaVega_tavern", "sit", "sit_base1");
			LAi_SetSitType(sld);
			sld = characterFromId("Pelly");
			FantomMakeCoolSailor(sld, SHIP_CORVETTE, "Мурена", CANNON_TYPE_CULVERINE_LBS18, 70, 70, 70);
			sld.nation = PIRATE;
			ChangeCharacterAddressGroup(sld, "LaVega_tavern", "sit", "sit_base5");
			LAi_SetSitType(sld);
			sld = characterFromId("Lepricon");
			ChangeCharacterAddressGroup(sld, "LaVega_tavern", "sit", "sit_front2");
			LAi_SetSitType(sld);
			// девочки
			for (i=2; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_Taverngirl_"+i, "women_2"+i, "woman", "towngirl", 1, PIRATE, 1, true, "quest"));
				ChangeCharacterAddressGroup(sld, "LaVega_tavern", "goto", "goto"+i);
				LAi_SetCitizenType(sld);
			}
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "tables", "table1", "Mtraxx_CartahenaTavernTurn", -1);
		break;
		
		case "Mtraxx_CartahenaTavernTurn": // 
			LAi_ActorTurnToCharacter(pchar, characterFromID("Terrax"));
			DoQuestCheckDelay("Mtraxx_CartahenaTavernSit", 0.5);
		break;
		
		case "Mtraxx_CartahenaTavernSit": // как здорово, что все мы здесь сегодня собрались
			LAi_SetSitType(pchar);
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_97";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Mtraxx_CartahenaTavernSong": // а теперь... песня!
			ChangeShowIntarface();
			ResetSound();
			SetMusic("music_piratesong");
			InterfaceStates.Buttons.Save.enable = false;
			bDisableCharacterMenu = true;
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
			DoQuestCheckDelay("Mtraxx_CartahenaTavernExit", 60.0);
		break;
		
		case "Mtraxx_CartahenaTavernExit": // закончили пьянку
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			locCameraResetState();
			iTime = sti(environment.time);
			WaitDate("", 0, 0, 0, 8, 5); //крутим время
			RecalculateJumpTable();
			StoreDayUpdate();
			RefreshWeather();
			RefreshLandTime();
			LAi_SetPlayerType(pchar);
			setCharacterShipLocation(pchar, "Lavega_port");
			setWDMPointXZ("Lavega_port"); // на всякий
			DoQuestReloadToLocation("LaVega_port", "reload", "reload1", "Mtraxx_CartahenaToSea");
		break;
		
		case "Mtraxx_CartahenaToSea": // формируем эскадру // 3 прогона
			pchar.GenQuest.HunterLongPause = true;
			DeleteAttribute(pchar, "questTemp.NoFast");
			sld = ItemsFromID("lcheer");
			sld.shown = false;
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.Mtraxx.InTavern");
			LAi_LocationDisableOfficersGen("LaVega_tavern", false);
			LocatorReloadEnterDisable("LaVega_port", "reload1_back", true);
			// присоединяем эскадру к ГГ. Тиракс
			sld = characterFromId("Terrax");
			FantomMakeCoolSailor(sld, SHIP_LINESHIP, "Красный дракон", CANNON_TYPE_CULVERINE_LBS36, 110, 110, 110);
			Mtraxx_MarkusSetShipParameter();
			SetCharacterGoods(sld, GOOD_BALLS, 5000);
			SetCharacterGoods(sld, GOOD_GRAPES, 2000);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 1000);
			SetCharacterGoods(sld, GOOD_BOMBS, 3000);
			SetCharacterGoods(sld, GOOD_POWDER, 11000);
			SetCharacterGoods(sld, GOOD_WEAPON, 1000);
			SetCharacterGoods(sld, GOOD_FOOD, 2500);
			SetCharacterGoods(sld, GOOD_MEDICAMENT, 900);
			SetCharacterGoods(sld, GOOD_RUM, 300);
			SetCharacterGoods(sld, GOOD_PLANKS, 300);
			SetCharacterGoods(sld, GOOD_SAILCLOTH, 50);
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "Carpenter");
			SetCharacterPerk(sld, "Builder"); 
			LAi_SetImmortal(sld, false);
			sld.ShipHideImmortal = 1000; // непотопляемый корабль
			sld.SeaBoss = 0.8;
			Character_SetAbordageEnable(sld, false); // нельзя абордировать
			sld.Tasks.CanBoarding = false; // запрет идти на абордаж - дубль
			sld.Tasks.CanChangeShipAfterBoarding = false; // запрет меняться кораблями - дубль
			LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
			sld.DontDeskTalk = true;
			SetCharacterRemovable(sld, false);
			sld.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			pchar.quest.mtraxx_ship_fail1.win_condition.l1 = "NPC_Death";
			pchar.quest.mtraxx_ship_fail1.win_condition.l1.character = "Terrax";
			pchar.quest.mtraxx_ship_fail1.function = "Mtraxx_MarkusGameOver"; // для шибко грамотных
			// Лысый Джеффри
			sld = characterFromId("Jeffry");
			SetCharacterGoods(sld, GOOD_BALLS, 1000);
			SetCharacterGoods(sld, GOOD_GRAPES, 800);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 700);
			SetCharacterGoods(sld, GOOD_BOMBS, 1000);
			SetCharacterGoods(sld, GOOD_POWDER, 3500);
			SetCharacterGoods(sld, GOOD_WEAPON, 700);
			SetCharacterGoods(sld, GOOD_FOOD, 2000);
			SetCharacterGoods(sld, GOOD_MEDICAMENT, 600);
			SetCharacterGoods(sld, GOOD_RUM, 200);
			SetCharacterGoods(sld, GOOD_PLANKS, 100);
			SetCharacterGoods(sld, GOOD_SAILCLOTH, 50);
			RealShips[sti(sld.Ship.Type)].MaxCrew = 460;
			UpgradeShipParameter(sld, "MaxCrew");
			int hcrew = GetMaxCrewQuantity(sld);
			SetCrewQuantity(sld, hcrew);
			sld.Ship.Crew.Morale = 100;
			sld.Ship.Crew.Exp.Sailors = 90;
			sld.Ship.Crew.Exp.Cannoners = 90;
			sld.Ship.Crew.Exp.Soldiers = 90;
			LAi_SetImmortal(sld, false);
			sld.ShipHideImmortal = 800; // непотопляемый корабль
			sld.SeaBoss = 0.8;
			LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
			Character_SetAbordageEnable(sld, false); // нельзя абордировать
			sld.Tasks.CanBoarding = false; // запрет идти на абордаж - дубль
			sld.Tasks.CanChangeShipAfterBoarding = false; // запрет меняться кораблями - дубль
			sld.DontDeskTalk = true;
			SetCharacterRemovable(sld, false);
			sld.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			// Тесак Пелли
			sld = characterFromId("Pelly");
			SetCharacterGoods(sld, GOOD_BALLS, 500);
			SetCharacterGoods(sld, GOOD_GRAPES, 700);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 400);
			SetCharacterGoods(sld, GOOD_BOMBS, 700);
			SetCharacterGoods(sld, GOOD_POWDER, 2300);
			SetCharacterGoods(sld, GOOD_WEAPON, 400);
			SetCharacterGoods(sld, GOOD_FOOD, 800);
			SetCharacterGoods(sld, GOOD_MEDICAMENT, 300);
			SetCharacterGoods(sld, GOOD_RUM, 100);
			SetCharacterGoods(sld, GOOD_PLANKS, 50);
			SetCharacterGoods(sld, GOOD_SAILCLOTH, 20);
			RealShips[sti(sld.Ship.Type)].SpeedRate = 15.2;
			SetRandGeraldSail(sld, PIRATE);
			hcrew = GetMaxCrewQuantity(sld);
			SetCrewQuantity(sld, hcrew);
			sld.Ship.Crew.Morale = 100;
			sld.Ship.Crew.Exp.Sailors = 90;
			sld.Ship.Crew.Exp.Cannoners = 90;
			sld.Ship.Crew.Exp.Soldiers = 90;
			LAi_SetImmortal(sld, false);
			sld.ShipHideImmortal = 500; // непотопляемый корабль
			sld.SeaBoss = 0.8;
			LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
			Character_SetAbordageEnable(sld, false); // нельзя абордировать
			sld.Tasks.CanBoarding = false; // запрет идти на абордаж - дубль
			sld.Tasks.CanChangeShipAfterBoarding = false; // запрет меняться кораблями - дубль
			sld.DontDeskTalk = true;
			SetCharacterRemovable(sld, false);
			sld.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			// Бернар Венсан
			sld = characterFromId("Mtr_Vensan");
			sld.Ship.Crew.Morale = 100;
			sld.Ship.Crew.Exp.Sailors = 70;
			sld.Ship.Crew.Exp.Cannoners = 70;
			sld.Ship.Crew.Exp.Soldiers = 70;
			LAi_SetImmortal(sld, false);
			sld.ShipHideImmortal = 400; // непотопляемый корабль
			sld.SeaBoss = 0.8;
			LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
			Character_SetAbordageEnable(sld, false); // нельзя абордировать
			sld.Tasks.CanBoarding = false; // запрет идти на абордаж - дубль
			sld.Tasks.CanChangeShipAfterBoarding = false; // запрет меняться кораблями - дубль
			sld.DontDeskTalk = true;
			SetCharacterRemovable(sld, false);
			sld.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			sld = characterFromId("Lepricon");
			ChangeCharacterAddressGroup(sld, "none", "", ""); // прячем Леприкона
			// подготовим Картахену
			i = FindColony("Cartahena");
			colonies[i].DontSetShipInPort = true;
			// прерывания на доплыть и таймер 20 дней
			pchar.quest.mtraxx_cartahena_sail.win_condition.l1 = "location";
			pchar.quest.mtraxx_cartahena_sail.win_condition.l1.location = "Cartahena";
			pchar.quest.mtraxx_cartahena_sail.function = "Mtraxx_CartahenaArrive";
			SetFunctionTimerCondition("Mtraxx_CartahenaSailOver", 0, 0, 20, false); 
			AddQuestRecord("Roger_9", "1");
		break;
		
		case "Mtraxx_CartahenaAbandon": // в бухте Ковеньяс
			chrDisableReloadToLocation = true;
			LAi_LocationDisableOfficersGen("shore25", true);//офицеров не пускать
			LocatorReloadEnterDisable("shore25", "reload1_back", true);
			sld = CharacterFromID("Terrax");
			ChangeCharacterAddressGroup(sld, "shore25", "rld", "loc0");
			sld.dialog.currentnode = "mtraxx_99";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 2.0);
			sld = CharacterFromID("Jeffry");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "shore25", "rld", "loc12");
			sld = CharacterFromID("Pelly");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "shore25", "rld", "loc11");
			sld = CharacterFromID("Lepricon");
			LAi_SetActorType(sld);
			sld.viper = true;
			ChangeCharacterAddressGroup(sld, "shore25", "rld", "loc9");
			for (i=5; i<=10; i++) // буканьеры Леприкона
			{
				sld = GetCharacter(NPC_GenerateCharacter("Lepricons_bukaneers_"+i, "mercen_"+i, "man", "man", 25, PIRATE, -1, true, "quest"));
				FantomMakeCoolFighter(sld, 25, 65, 65, LinkRandPhrase("blade_04","blade_06","topor_04"), "pistol3", "grapeshot", 200);
				LAi_CharacterDisableDialog(sld);
				TakeNItems(sld, "potion2", 5);
				TakeNItems(sld, "potion3", 2);
				TakeNItems(sld, "potion4", 2);
				ChangeCharacterAddressGroup(sld, "shore25", "rld", "aloc2");
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
			}
			// выводим из компаньонов всех, кроме Тесака
			sld = CharacterFromID("Terrax");
			RemoveCharacterCompanion(pchar, sld);
			sld.AlwaysFriend = true;
			sld.ShipEnemyDisable = true; 
			sld = characterFromId("Jeffry");
			RemoveCharacterCompanion(pchar, sld);
			sld.AlwaysFriend = true;
			sld.ShipEnemyDisable = true; 
			sld = characterFromId("Mtr_Vensan");
			RemoveCharacterCompanion(pchar, sld);
			sld.AlwaysFriend = true;
			sld.ShipEnemyDisable = true; 
			// в группу пиратов
			Group_FindOrCreateGroup("Terrax_SeaGroup");
			Group_AddCharacter("Terrax_SeaGroup", "Terrax");
			Group_AddCharacter("Terrax_SeaGroup", "Jeffry");
			Group_AddCharacter("Terrax_SeaGroup", "Mtr_Vensan");
			Group_SetGroupCommander("Terrax_SeaGroup", "Terrax");
			Group_SetTaskNone("Terrax_SeaGroup");
			Group_SetAddress("Terrax_SeaGroup", "Cartahena", "quest_ships", "quest_ship_6");
			Group_LockTask("Terrax_SeaGroup");
		break;
		
		case "Mtraxx_CartahenaFortFirstBattle": // бой в цитадели форта // патч 17/1
			PlaySound("interface\_GTBoard2.wav");
			iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			bDisableCharacterMenu = true;//лочим F2
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			locations[FindLocation("Cartahena_Town")].QuestCapture = true;
			locations[FindLocation("Cartahena_Fort")].QuestCapture = true;
			// наши
			sld = CharacterFromID("Terrax"); // Тиракс
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(sld, "BOARDING_FORT", "rld", "loc0");
			for (i=1; i<=3; i++) // офицеры ГГ
			{
				idx = GetOfficersIndex(pchar, i);
				if (idx < 1) continue;
				sld = &Characters[idx];
				ChangeCharacterAddressGroup(sld, "BOARDING_FORT", "rld", "loc"+(i+3));
			}
			// расчет количества десанта, 45% от общего числа
			iTotalTemp = makeint((sti(pchar.questTemp.Mtraxx.Cartahena.Crew)/40)*0.45);
			if (iTotalTemp < 1) iTotalTemp = 1;
			if (iTotalTemp > 25) iTotalTemp = 25;
			log_Testinfo("Наших с оружием - "+iTotalTemp+" бойцов");
			for (i=1; i<=iTotalTemp; i++)
			{
				if (i < 3) // мушкетеры, 2 шт
				{
					sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort1Pirate_"+i, "mush_ctz_"+(i+6), "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket3", "grapeshot", 170);
					LAi_SetCharacterUseBullet(sld, "grapeshot");
					if (iTotalTemp > 15) sld.cirassId = Items_FindItemIdx("cirass1");
				}
				else
				{
						sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort1Pirate_"+i, "citiz_"+(rand(9)+41), "man", "man", iRank, PIRATE, -1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_03","blade_05","blade_07"), "pistol1", "bullet", 150);
						if (iTotalTemp > 15) sld.cirassId = Items_FindItemIdx("cirass2");
				}
				ChangeCharacterAddressGroup(sld, "BOARDING_FORT", "rld", "loc"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_CharacterDisableDialog(sld);
			}
			// испанцы
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=25; i++)
			{
				if (i == 1 || i == 5 || i == 8 || i == 9 || i == 11 || i == 12) // мушкетеры, 6 шт
				{
					sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort1Guard_"+i, "mush_spa_"+(rand(2)+1), "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
					if (i < 9) 
					{
						FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket1", "cartridge", 170);
						LAi_SetCharacterUseBullet(sld, "cartridge");
					}
					else 
					{
						FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket3", "grapeshot", 170);
						LAi_SetCharacterUseBullet(sld, "grapeshot");
					}
					if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass1");
					sld.MusketerDistance = 0;
				}
				else
				{
					if (i == 14) // офицер
					{
						sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort1Guard_"+i, "off_spa_4", "man", "man", iRank+5, SPAIN, -1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank+5, 70, 70, "topor_04", "pistol4", "cartridge", 200);
						SetCharacterPerk(sld, "SwordplayProfessional");
						SetCharacterPerk(sld, "Gunman");
						SetCharacterPerk(sld, "GunProfessional");
						sld.cirassId = Items_FindItemIdx("cirass1");
					}
					else
					{
						sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort1Guard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank, SPAIN, -1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 150);
						if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass2");
					}
				}
				ChangeCharacterAddressGroup(sld, "BOARDING_FORT", "rld", "aloc"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_CartahenaFortFirstBattleEnd");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Mtraxx_CartahenaFortFirstBattleEnd": // завершили бой в цитадели
			LAi_SetFightMode(pchar, false);
			PlaySound("interface\abordage_wining.wav");
			// считаем выживших
			n = 0;
			for (i=1; i<=iTotalTemp; i++)
			{
				sld = CharacterFromID("Mtr_CartahenaFort1Pirate_"+i);
				if (LAi_GetCharacterHP(sld) > 0) n++;
				sld.lifeday = 0; // патч 17/1
			}
			log_Testinfo("В бою выжило - "+n+" наших бойцов");
			pchar.questTemp.Mtraxx.Cartahena.Fort1Crew = n; // запоминаем
			DoQuestFunctionDelay("Mtraxx_CartahenaFortReloadNext", 5.0);
		break;
		
		case "Mtraxx_CartahenaFortSecondBattle": // бой в бастионе
			PlaySound("interface\_GTBoard2.wav");
			iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			// наши
			sld = CharacterFromID("Jeffry"); // Лысый
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(sld, "Boarding_bastion1", "rld", "loc8");
			for (i=1; i<=3; i++) // офицеры ГГ
			{
				idx = GetOfficersIndex(pchar, i);
				if (idx < 1) continue;
				sld = &Characters[idx];
				ChangeCharacterAddressGroup(sld, "Boarding_bastion1", "rld", "loc"+i);
			}
			// расчет количества десанта, 28% от общего числа
			iTotalTemp = makeint((sti(pchar.questTemp.Mtraxx.Cartahena.Crew)/40)*0.28);
			if (iTotalTemp < 1) iTotalTemp = 1;
			if (iTotalTemp > 15) iTotalTemp = 15;
			log_Testinfo("Наших с оружием - "+iTotalTemp+" бойцов");
			for (i=1; i<=iTotalTemp; i++)
			{
				if (i < 3) // мушкетеры, 2 шт
				{
					sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort2Pirate_"+i, "mush_ctz_"+(i+6), "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket3", "grapeshot", 170);
					LAi_SetCharacterUseBullet(sld, "grapeshot");
					if (iTotalTemp > 10) sld.cirassId = Items_FindItemIdx("cirass1");
				}
				else
				{
						sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort2Pirate_"+i, "citiz_"+(rand(9)+41), "man", "man", iRank, PIRATE, -1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_03","blade_05","blade_07"), "pistol1", "bullet", 150);
						if (iTotalTemp > 10) sld.cirassId = Items_FindItemIdx("cirass2");
				}
				ChangeCharacterAddressGroup(sld, "Boarding_bastion1", "rld", "loc"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_CharacterDisableDialog(sld);
			}
			// испанцы
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=15; i++)
			{
				if (i == 7 || i == 13 || i == 15) // мушкетеры, 3 шт
				{
					sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort2Guard_"+i, "mush_spa_"+(rand(2)+1), "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket3", "grapeshot", 170);
					LAi_SetCharacterUseBullet(sld, "grapeshot");
					if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass1");
					sld.MusketerDistance = 0;
				}
				else
				{
					if (i == 14) // офицер
					{
						sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort2Guard_"+i, "off_spa_5", "man", "man", iRank+5, SPAIN, -1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank+5, 70, 70, "topor_04", "pistol4", "cartridge", 200);
						SetCharacterPerk(sld, "SwordplayProfessional");
						SetCharacterPerk(sld, "Gunman");
						SetCharacterPerk(sld, "GunProfessional");
						sld.cirassId = Items_FindItemIdx("cirass1");
					}
					else
					{
						sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort2Guard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank, SPAIN, -1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 150);
						if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass2");
					}
				}
				ChangeCharacterAddressGroup(sld, "Boarding_bastion1", "rld", "aloc"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_CartahenaFortSecondBattleEnd");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Mtraxx_CartahenaFortSecondBattleEnd": // завершили бой в бастионе
			LAi_SetFightMode(pchar, false);
			PlaySound("interface\abordage_wining.wav");
			// считаем выживших
			n = 0;
			for (i=1; i<=iTotalTemp; i++)
			{
				sld = CharacterFromID("Mtr_CartahenaFort2Pirate_"+i);
				if (LAi_GetCharacterHP(sld) > 0) n++;
				sld.lifeday = 0; // патч 17/1
			}
			log_Testinfo("В бою выжило - "+n+" наших бойцов");
			pchar.questTemp.Mtraxx.Cartahena.Fort2Crew = n; // запоминаем
			DoQuestFunctionDelay("Mtraxx_CartahenaFortReloadEnd", 5.0);
		break;
		
		case "Mtraxx_CartahenaFortThirdBattle": // бой во дворе
			PlaySound("interface\_GTBoard2.wav");
			iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			// наши
			sld = CharacterFromID("Pelly"); // Тесак
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(sld, "Boarding_fortyard", "rld", "loc8");
			for (i=1; i<=3; i++) // офицеры ГГ
			{
				idx = GetOfficersIndex(pchar, i);
				if (idx < 1) continue;
				sld = &Characters[idx];
				ChangeCharacterAddressGroup(sld, "Boarding_fortyard", "rld", "loc"+i);
			}
			// расчет количества десанта, 27% от общего числа
			iTotalTemp = makeint((sti(pchar.questTemp.Mtraxx.Cartahena.Crew)/40)*0.27);
			if (iTotalTemp < 1) iTotalTemp = 1;
			if (iTotalTemp > 15) iTotalTemp = 15;
			log_Testinfo("Наших с оружием - "+iTotalTemp+" бойцов");
			for (i=1; i<=iTotalTemp; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort3Pirate_"+i, "citiz_"+(rand(9)+41), "man", "man", iRank, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_03","blade_05","blade_07"), "pistol1", "bullet", 150);
				if (iTotalTemp > 10) sld.cirassId = Items_FindItemIdx("cirass2");
				ChangeCharacterAddressGroup(sld, "Boarding_fortyard", "rld", "loc"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_CharacterDisableDialog(sld);
			}
			// испанцы
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=15; i++)
			{
					if (i == 14) // офицер
					{
						sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort3Guard_"+i, "off_spa_3", "man", "man", iRank+5, SPAIN, -1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank+5, 70, 70, "topor_04", "pistol4", "cartridge", 200);
						SetCharacterPerk(sld, "SwordplayProfessional");
						SetCharacterPerk(sld, "Gunman");
						SetCharacterPerk(sld, "GunProfessional");
						sld.cirassId = Items_FindItemIdx("cirass1");
					}
					else
					{
						sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort3Guard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank, SPAIN, -1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 150);
						if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass2");
					}
				ChangeCharacterAddressGroup(sld, "Boarding_fortyard", "rld", "aloc"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_CartahenaFortThirdBattleEnd");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Mtraxx_CartahenaFortThirdBattleEnd": // завершили бой во дворе
			LAi_SetFightMode(pchar, false);
			PlaySound("interface\abordage_wining.wav");
			// считаем выживших
			n = 0;
			for (i=1; i<=iTotalTemp; i++)
			{
				sld = CharacterFromID("Mtr_CartahenaFort3Pirate_"+i); // belamour: убрать пиратов Тесака из Бастиона
				if (LAi_GetCharacterHP(sld) > 0) n++;
				sld.lifeday = 0; // патч 17/1
			}
			log_Testinfo("В бою выжило - "+n+" наших бойцов");
			pchar.questTemp.Mtraxx.Cartahena.Fort3Crew = n; // запоминаем
			DoQuestFunctionDelay("Mtraxx_CartahenaExittownReload", 5.0);
		break;
		
		case "Mtraxx_CartahenaExittownBattle": // бой на выходе из города
			PlaySound("interface\_GTBoard2.wav");
			iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			chrDisableReloadToLocation = true;
			// наши
			for (i=1; i<=3; i++) // офицеры ГГ
			{
				idx = GetOfficersIndex(pchar, i);
				if (idx < 1) continue;
				sld = &Characters[idx];
				ChangeCharacterAddressGroup(sld, "Cartahena_ExitTown", "officers", "reload3_"+i);
			}
			sld = CharacterFromID("Lepricon"); // Леприкон
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(sld, "Cartahena_ExitTown", "rld", "aloc12");
			for (i=5; i<=10; i++) // буканьеры Леприкона
			{
				sld = CharacterFromID("Lepricons_bukaneers_"+i);
				if (i < 10) ChangeCharacterAddressGroup(sld, "Cartahena_ExitTown", "rld", "aloc"+(i-4));
				else ChangeCharacterAddressGroup(sld, "Cartahena_ExitTown", "rld", "aloc11");
				LAi_CharacterDisableDialog(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				sld.lifeday = 3;
			}
			// испанцы
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=12; i++)
			{
				if (i < 3) // мушкетеры, 2 шт
				{
					sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaExittownGuard_"+i, "mush_spa_"+(rand(2)+1), "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket1", "cartridge", 170);
					LAi_SetCharacterUseBullet(sld, "cartridge");
					if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass1");
					ChangeCharacterAddressGroup(sld, "Cartahena_ExitTown", "reload", "reload4");
				}
				else
				{
					if (i == 12) // офицер
					{
						sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaExittownGuard_"+i, "off_spa_5", "man", "man", iRank+5, SPAIN, -1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank+5, 70, 70, "topor_04", "pistol4", "cartridge", 200);
						SetCharacterPerk(sld, "SwordplayProfessional");
						SetCharacterPerk(sld, "Gunman");
						SetCharacterPerk(sld, "GunProfessional");
						sld.cirassId = Items_FindItemIdx("cirass1");
						ChangeCharacterAddressGroup(sld, "Cartahena_ExitTown", "rld", "aloc15");
					}
					else
					{
						sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaExittownGuard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank, SPAIN, -1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 150);
						if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass2");
						if (i > 5 && i < 11) ChangeCharacterAddressGroup(sld, "Cartahena_ExitTown", "rld", "aloc"+i);
						else ChangeCharacterAddressGroup(sld, "Cartahena_ExitTown", "rld", "aloc14");
					}
				}
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_CartahenaExittownBattleEnd");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Mtraxx_CartahenaExittownBattleEnd": // завершили бой у ворот
			LAi_SetFightMode(pchar, false);
			PlaySound("interface\abordage_wining.wav");
			setCharacterShipLocation(pchar, "Cartahena_Town");
			setWDMPointXZ("Cartahena_Town");
			locations[FindLocation("Cartahena_Town")].QuestCapture = true;
			locations[FindLocation("Cartahena_Townhall")].QuestCapture = true;
			DoQuestFunctionDelay("Mtraxx_CartahenaTownReload", 5.0);
			for (i=5; i<=10; i++) // патч 17/1
			{
				sld = CharacterFromID("Lepricons_bukaneers_"+i);
				sld.lifeday = 0; 
			}
			// суммируем всех оставшихся бойцов
			iTotalTemp = sti(pchar.questTemp.Mtraxx.Cartahena.Fort1Crew)+sti(pchar.questTemp.Mtraxx.Cartahena.Fort2Crew)+sti(pchar.questTemp.Mtraxx.Cartahena.Fort3Crew);
			pchar.questTemp.Mtraxx.Cartahena.FortAliveCrew = iTotalTemp; // выживший десант в форте, из него идут на город
		break;
		
		case "Mtraxx_CartahenaTownBattle": // бой в городе
			// прячем нищеброда
			sld = characterFromId("Cartahena_Poorman");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			PlaySound("interface\_GTBoard2.wav");
			iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			// считаем выживших бойцов. Участвует только 20 рыл. Их запоминаем.
			if (iTotalTemp > 20) n = 20;
			else n = iTotalTemp;
			iTotalTemp = n; // запомнили в глобальную переменную
			pchar.questTemp.Mtraxx.Cartahena.TownCrew = n;
			// наши
			for (i=1; i<=3; i++) // офицеры ГГ
			{
				idx = GetOfficersIndex(pchar, i);
				if (idx < 1) continue;
				sld = &Characters[idx];
				ChangeCharacterAddressGroup(sld, "Cartahena_Town", "officers", "gate_back_"+i);
			}
			sld = CharacterFromID("Terrax"); // Тиракс
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(sld, "Cartahena_Town", "reload", "houseSp2");
			sld = CharacterFromID("Jeffry"); // Лысый
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(sld, "Cartahena_Town", "reload", "houseSp1");
			sld = CharacterFromID("Pelly"); // Тесак
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(sld, "Cartahena_Town", "reload", "houseF2");
			sld = CharacterFromID("Lepricon"); // Леприкон
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(sld, "Cartahena_Town", "reload", "houseS2");
			log_Testinfo("Наших с оружием - "+iTotalTemp+" бойцов");
			for (i=1; i<=iTotalTemp; i++)
			{
				if (i < 3) // мушкетеры, 2 шт
				{
					sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaTownPirate_"+i, "mush_ctz_"+(i+6), "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket3", "grapeshot", 170);
					LAi_SetCharacterUseBullet(sld, "grapeshot");
					if (iTotalTemp > 17) sld.cirassId = Items_FindItemIdx("cirass1");
				}
				else
				{
						sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaTownPirate_"+i, "citiz_"+(rand(9)+41), "man", "man", iRank, PIRATE, -1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_03","blade_05","blade_07"), "pistol1", "bullet", 150);
						if (iTotalTemp > 17) sld.cirassId = Items_FindItemIdx("cirass2");
				}
				ChangeCharacterAddressGroup(sld, "Cartahena_Town", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_CharacterDisableDialog(sld);
			}
			// испанцы
			LAi_group_Delete("EnemyFight");
			// офицер
			sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaTownOfficer_"+i, "off_spa_5", "man", "man", iRank+7, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank+7, 75, 75, "topor_04", "pistol4", "cartridge", 220);
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			sld.cirassId = Items_FindItemIdx("cirass1");
			ChangeCharacterAddressGroup(sld, "Cartahena_Town", "quest", "quest1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			// мушкетеры
			for (i=3; i<=8; i++)
			{
				
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaTownMushketer_"+i, "mush_spa_"+(rand(2)+1), "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket1", "cartridge", 170);
				LAi_SetCharacterUseBullet(sld, "cartridge");
				if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass1");
				sld.MusketerDistance = 0;
				ChangeCharacterAddressGroup(sld, "Cartahena_Town", "reload", "reload"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
			}
			for (i=1; i<=20; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaTownGuard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank, SPAIN, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 150);
				if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass2");
				ChangeCharacterAddressGroup(sld, "Cartahena_Town", "patrol", "patrol"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_CartahenaTownBattleEnd");
			LAi_SetFightMode(pchar, true);
			// огонь и дым
			CreateLocationParticles("Bomb_Smoke", "reload", "houseF1", 3, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "houseF1", 0, 0, 0, "fortfire");
			CreateLocationParticles("Bomb_Smoke", "reload", "houseS4", 3, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "houseS4", 0, 0, 0, "fortfire");
			CreateLocationParticles("Bomb_Smoke", "reload", "houseH2", 3, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "houseH2", 0, 0, 0, "fortfire");
			CreateLocationParticles("Bomb_Smoke", "reload", "houseS3", 3, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "houseS3", 0, 0, 0, "fortfire");
			CreateLocationParticles("Bomb_Smoke", "reload", "houseH1", 3, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "houseH1", 0, 0, 0, "fortfire");
		break;
		
		case "Mtraxx_CartahenaTownBattleEnd": // закончили бой в городе
			LAi_SetFightMode(pchar, false);
			PlaySound("interface\abordage_wining.wav");
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			// считаем выживших
			n = 0;
			for (i=1; i<=iTotalTemp; i++)
			{
				sld = CharacterFromID("Mtr_CartahenaTownPirate_"+i);
				if (LAi_GetCharacterHP(sld) > 0) n++;
				sld.lifeday = 3;
			}
			log_Testinfo("В бою выжило - "+n+" наших бойцов");
			int DeadCrew = iTotalTemp - n; // погибшие в городской боевке
			// бои окончены, считаем всех выживших бойцов по итогу
			int AliveCrew = sti(pchar.questTemp.Mtraxx.Cartahena.FortAliveCrew)-DeadCrew; // выжившие
			pchar.questTemp.Mtraxx.Cartahena.AliveCrew1 = makeint(AliveCrew*40*sti(pchar.questTemp.Mtraxx.Cartahena.Crewpercent1)/100)+1; // команда ГГ
			pchar.questTemp.Mtraxx.Cartahena.AliveCrew2 = makeint(AliveCrew*40*sti(pchar.questTemp.Mtraxx.Cartahena.Crewpercent2)/100)+1; // команда Тиракса
			pchar.questTemp.Mtraxx.Cartahena.AliveCrew3 = makeint(AliveCrew*40*sti(pchar.questTemp.Mtraxx.Cartahena.Crewpercent3)/100)+1; // команда Лысого
			pchar.questTemp.Mtraxx.Cartahena.AliveCrew4 = makeint(AliveCrew*40*sti(pchar.questTemp.Mtraxx.Cartahena.Crewpercent4)/100)+1; // команда Тесака
			// главарей - в кучу, Тиракса позже, во избежание сбоя
			sld = CharacterFromID("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", 8.0);
			sld = CharacterFromID("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", 8.0);
			sld = CharacterFromID("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", 8.0);
			DoQuestCheckDelay("Mtraxx_CartahenaToGovernor", 8.0);
		break;
		
		case "Mtraxx_CartahenaToGovernor": // к губеру
			sld = CharacterFromID("Terrax");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "mtraxx_104";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
		break;
		
		case "Mtraxx_CartahenaResidence": // в резиденции Картахены
			// прячем настоящего губера и ставим его клон
			sld = CharacterFromID("Cartahena_Mayor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaMayorClone", "huber_22", "man", "man", 30, SPAIN, -1, false, "officer"));
			SetFantomParamFromRank(sld, 30, true);
			RemoveAllCharacterItems(sld, true);
			sld.name = "Дионисио";
			sld.lastname = "Перес";
			sld.dialog.FileName = "Quest\Roger.c";
			sld.dialog.currentnode = "CartahenaMayor";
			ChangeCharacterAddressGroup(sld, "Cartahena_townhall", "goto", "governor1");
			LAi_SetStayType(sld);
		break;
		
		case "Mtraxx_CartahenaResidenceWait": // ждем выкупа от губернатора
			DoQuestCheckDelay("Mtraxx_CartahenaResidenceWait1", 5.0);
		break;
		
		case "Mtraxx_CartahenaResidenceWait1": // ждем выкупа от губернатора
			SetLaunchFrameFormParam("Прошли одни сутки..."+ NewStr() +"Выкуп за Картахену был собран", "Mtraxx_CartahenaResidenceMayor", 0, 5);//табличка
			WaitDate("", 0, 0, 1, 1, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
		break;
		
		case "Mtraxx_CartahenaResidenceMayor": // 
			sld = CharacterFromID("Mtr_CartahenaMayorClone");
			sld.lifeday = 1;
			ChangeCharacterAddressGroup(sld, "Cartahena_Townhall", "reload", "reload1");
			sld.dialog.currentnode = "CartahenaMayor_12";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			OfficersReaction("bad");
		break;
		
		case "Mtraxx_CartahenaStreet": // антураж захваченной Картахены
			// огонь и дым
			for (i=4; i<=10; i++)
			{
				if (i == 9) continue;
				CreateLocationParticles("Bomb_Smoke", "reload", "reload"+i+"_back", 0, 0, 0, "torch_deck");
				CreateLocationParticles("shipfire", "reload", "reload"+i+"_back", 0, 0, 0, "fortfire");
			}
			CreateLocationParticles("Bomb_Smoke", "reload", "houseF1", 0, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "houseF1", 0, 0, 0, "fortfire");
			CreateLocationParticles("Bomb_Smoke", "reload", "houseS4", 0, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "houseS4", 0, 0, 0, "fortfire");
			CreateLocationParticles("Bomb_Smoke", "reload", "houseH2", 0, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "houseH2", 0, 0, 0, "fortfire");
			CreateLocationParticles("Bomb_Smoke", "reload", "houseS3", 0, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "houseS3", 0, 0, 0, "fortfire");
			CreateLocationParticles("Bomb_Smoke", "reload", "houseH1", 0, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "houseH1", 0, 0, 0, "fortfire");
			for (i=1; i<=19; i++) // жертвы нападения
			{
				if (i < 10)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Cartahena_victim_"+i, "citiz_1"+i, "man", "man", 1, SPAIN, 1, true, "quest"));
					SetFantomParamFromRank(sld, 1, true);
					ChangeCharacterAddressGroup(sld, "Cartahena_town", "patrol", "patrol"+i);
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("Cartahena_victim_"+i, "women_"+(i-3), "woman", "towngirl", 1, SPAIN, 1, true, "quest"));
					SetFantomParamFromRank(sld, 1, true);
					ChangeCharacterAddressGroup(sld, "Cartahena_town", "goto", "goto"+i);
				}
				RemoveAllCharacterItems(sld, true);
				sld.DontClearDead = true;
				LAi_SetStayType(sld);
				LAi_KillCharacter(sld);
			}
			OfficersReaction("bad");
		break;
		
		case "Mtraxx_CartahenaTerraxInFort": // пираты в форте
			sld = CharacterFromID("Terrax");
			sld.dialog.currentnode = "mtraxx_106";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Cartahena_fort", "goto", "goto11");
			sld = CharacterFromID("Jeffry");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Cartahena_fort", "goto", "goto21");
			sld = CharacterFromID("Lepricon");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Cartahena_fort", "goto", "goto01");
			sld = CharacterFromID("Mtr_Vensan");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Cartahena_fort", "goto", "goto31");
			// тут делаем расчет команд кораблей для дележа добычи. Тиракс забирает 50%, остальные 4 корабля - в пропорции от числа команд
			int iCrew1 = GetCrewQuantity(pchar);
			int iCrew2 = GetCrewQuantity(characterFromId("Jeffry"));
			int iCrew3 = GetCrewQuantity(characterFromId("Pelly"));
			int iCrew4 = GetCrewQuantity(characterFromId("Mtr_Vensan"));
			int iCrewT = iCrew1+iCrew2+iCrew3+iCrew4;
			pchar.questTemp.Mtraxx.Cartahena.Gold = makeint(iCrew1*100/iCrewT)*25; // золото ГГ
			pchar.questTemp.Mtraxx.Cartahena.Money = makeint(iCrew1*100/iCrewT)*1500; // деньги ГГ
		break;
		
		case "Mtraxx_CartahenaComplete": // в городе перед отплытием
			bDisableCharacterMenu = false;
			AddQuestRecord("Roger_9", "8");
			AddQuestUserData("Roger_9", "sGold", sti(pchar.questTemp.Mtraxx.Cartahena.Gold));
			AddQuestUserData("Roger_9", "sMoney", sti(pchar.questTemp.Mtraxx.Cartahena.Money));
			chrDisableReloadToLocation = false;
			for (i=3; i<=10; i++)
			{
				LocatorReloadEnterDisable("Cartahena_town", "reload"+i+"_back", true);
			}
			LocatorReloadEnterDisable("Cartahena_town", "gate_back", true);
			LocatorReloadEnterDisable("Cartahena_town", "reload_jail", true);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.Mtraxx.Cartahena.Money));
			SetCharacterGoods(pchar, GOOD_GOLD, GetCargoGoods(pchar, GOOD_GOLD) + sti(pchar.questTemp.Mtraxx.Cartahena.Gold));
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			for (i=4; i<=10; i++)
			{
				if (i == 9) continue;
				CreateLocationParticles("Bomb_Smoke", "reload", "reload"+i+"_back", 3, 0, 0, "torch_deck");
				CreateLocationParticles("shipfire", "reload", "reload"+i+"_back", 0, 0, 0, "fortfire");
			}
			CreateLocationParticles("Bomb_Smoke", "reload", "houseF1", 3, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "houseF1", 0, 0, 0, "fortfire");
			CreateLocationParticles("Bomb_Smoke", "reload", "houseS4", 3, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "houseS4", 0, 0, 0, "fortfire");
			CreateLocationParticles("Bomb_Smoke", "reload", "houseH2", 3, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "houseH2", 0, 0, 0, "fortfire");
			CreateLocationParticles("Bomb_Smoke", "reload", "houseS3", 3, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "houseS3", 0, 0, 0, "fortfire");
			CreateLocationParticles("Bomb_Smoke", "reload", "houseH1", 3, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "houseH1", 0, 0, 0, "fortfire");
			pchar.quest.mtraxx_cartahena_complete.win_condition.l1 = "location";
			pchar.quest.mtraxx_cartahena_complete.win_condition.l1.location = "Cartahena";
			pchar.quest.mtraxx_cartahena_complete.function = "Mtraxx_CartahenaShipsGoAway";
		break;
		
		// эпизод 10
		case "Mtraxx_RetributionStart": // телепорт к бордельмаман
			DoQuestReloadToLocation("Tortuga_SecBrRoom", "reload", "reload1", "");
			pchar.questTemp.Mtraxx.Retribution = "brothel";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			LAi_SetPlayerType(pchar);
		break;
		
		case "Mtraxx_RetributionInBrothel": // в комнате с девочками
			LAi_SetSitType(pchar);
			for (i=1; i<=6; i++)
			{
				if (i == 3 || i == 5) continue;
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_TortugaGirl_"+i, "women_"+(i+19), "woman", "towngirl", 1, FRANCE, 0, true, "quest"));
				SetFantomParamFromRank(sld, 1, true);
				if (i < 3) ChangeCharacterAddressGroup(sld, "Tortuga_Brothel_room", "goto", "goto"+i);
				else ChangeCharacterAddressGroup(sld, "Tortuga_Brothel_room", "reload", "reload1_back");
				LAi_SetCitizenType(sld);
			}
			DoQuestCheckDelay("Mtraxx_RetributionRestInBrothel", 1.3);
		break;
		
		case "Mtraxx_RetributionRestInBrothel": // отдых в борделе
			ChangeShowIntarface();
			ResetSound();
			SetMusic("music_piratemusic");
			InterfaceStates.Buttons.Save.enable = false;
			bDisableCharacterMenu = true;
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
			DoQuestCheckDelay("Mtraxx_RetributionFrameInBrothel", 30.0);
			for (i=1; i<=3; i++)
			{
				DoQuestCheckDelay("Mtraxx_RetributionVoiceInBrothel_"+i, 2+i*6);
			}
		break;
		
		case "Mtraxx_RetributionVoiceInBrothel_1": // голоса
			PlaySound("VOICE\Russian\brothel\Shluhi-11.wav");
			PlaySound("ambient\tavern\krujki_003.wav");
			PlaySound("ambient\tavern\naliv_001.wav");
		break;
		
		case "Mtraxx_RetributionVoiceInBrothel_2": // голоса
			PlaySound("VOICE\Russian\brothel\Shluhi-12.wav");
			PlaySound("ambient\tavern\krujki_004.wav");
			PlaySound("ambient\tavern\naliv_002.wav");
		break;
		
		case "Mtraxx_RetributionVoiceInBrothel_3": // голоса
			PlaySound("VOICE\Russian\brothel\Shluhi-13.wav");
			PlaySound("ambient\tavern\krujki_005.wav");
			PlaySound("ambient\tavern\naliv_003.wav");
		break;
		
		case "Mtraxx_RetributionFrameInBrothel": // нагулялся
			PlaySound("ambient\tavern\orijka_003.wav");
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			locCameraResetState();
			iTime = sti(environment.time);
			SetLaunchFrameFormParam("Два дня пролетели незаметно"+ NewStr() +"в кутеже и любовных утехах...", "Mtraxx_RetributionTortugaReload", 0, 5);
			WaitDate("", 0, 0, 2, 6, 5); //крутим время
			AddCharacterHealth(pchar, 8);
			LaunchFrameForm();
			RecalculateJumpTable();
			StoreDayUpdate();
			RefreshWeather();
			RefreshLandTime();
			LAi_SetPlayerType(pchar);
			pchar.GenQuest.CamShuttle = 2;
		break;
		
		case "Mtraxx_RetributionTortugaReload": // релоад на улицы
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload9", "Mtraxx_RetributionTortugaStreets");
		break;
		
		case "Mtraxx_RetributionTortugaStreets": // ставим Камиллу
			pchar.questTemp.Mtraxx.Retribution = "tavern";
			PlaySound("ambient\tavern\orijka_002.wav");
			sld = GetCharacter(NPC_GenerateCharacter("Kamilla", "women_16", "woman", "towngirl", 15, FRANCE, -1, true, "quest"));
			SetFantomParamFromRank(sld, 15, true);
			sld.name = "Камилла";
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Roger.c";
			sld.dialog.currentnode = "camilla";
			sld.greeting = "";
			ChangeCharacterAddressGroup(sld, "Tortuga_town", "goto", "goto25");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Mtraxx_RetributionToRoom": // в комнате таверны
			sld = characterFromId("Kamilla");
			sld.dialog.currentnode = "camilla_7";
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "quest", "quest3");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 2.0);
		break;
		
		case "Mtraxx_RetributionRoomSex": // после секса с Камиллой
			bDisableCharacterMenu = false;
			DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
			sld = characterFromId("Kamilla");
			sld.dialog.currentnode = "camilla_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Mtraxx_RetributionKamilla": // Камиллу - в церковь
			sld = characterFromId("Kamilla");
			LAi_SetStayType(sld);
			chrDisableReloadToLocation = false;
		break;
		
		case "Mtraxx_RetributionBarrels": // 
			DoQuestReloadToLocation("Carataska_jungle_02", "goto", "goto5", "Mtraxx_RetributionFire");
		break;
		
		case "Mtraxx_RetributionFire": // осталось только поджечь
			for (i=1; i<=3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_FirePirate_"+i, "citiz_4"+i, "man", "man", 10, PIRATE, 1, false, "soldier"));
				SetFantomParamFromRank(sld, 10, true);
				ChangeCharacterAddressGroup(sld, "Carataska_jungle_02", "quest", "detector1");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 20.0);
			}
			AddQuestRecord("Roger_10", "5");
			pchar.questTemp.Mtraxx.Retribution.Fire = "true";
		break;
		
		case "Mtraxx_RetributionRunAway": // 
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "quest", "detector1");
			DoQuestFunctionDelay("Mtraxx_RetributionJungleBoom", 5.0);
		break;
		
		case "Mtraxx_RetributionGotoRuins": // прерывание на вход в подземелья
			CreateLocationParticles("smoke", "quest", "deadfall", 0, 0, 0, "");
			CreateLocationParticles("smoke", "reload", "reload2_back", 0, 0, 0, "");
			AddQuestRecord("Roger_10", "5-1");
			pchar.quest.mtraxx_retribution_ruins.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_ruins.win_condition.l1.location = "Judgement_dungeon_01";
			pchar.quest.mtraxx_retribution_ruins.function = "Mtraxx_RetributionRuins";
		break;
		
		case "Mtraxx_RetributionPellyAfterFight": // окончили бой с Тесаком
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			AddQuestRecord("Roger_10", "7");
			pchar.quest.mtraxx_retribution_ruins1.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_ruins1.win_condition.l1.location = "Judgement_dungeon_03";
			pchar.quest.mtraxx_retribution_ruins1.function = "Mtraxx_RetributionSetJeffry";
		break;
		
		case "Mtraxx_RetributionJeffryTreasure": // с Джеффри у сокровищ - любуется
			sld = characterFromId("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "monster", "monster3");
			DoQuestCheckDelay("Mtraxx_RetributionJeffryTreasure1", 7.0);
			sld = characterFromId("Jeffry_PirateDung_4");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "quest", "quest4");
		break;
		
		case "Mtraxx_RetributionJeffryTreasure1": // с Джеффри у сокровищ - идет в позицию
			sld = characterFromId("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "quest5", "Mtraxx_RetributionJeffryTreasure2", -1);
		break;
		
		case "Mtraxx_RetributionJeffryTreasure2": // с Джеффри у сокровищ
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Mtraxx_RetributionJeffryMushketer": // выстрел в ГГ
			sld = characterFromId("Jeffry_PirateDung_4");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "shot", "Mtraxx_RetributionJeffryShot", 1.0);
		break;
		
		case "Mtraxx_RetributionJeffryShot": // выстрел в ГГ - реакция
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "hit_fire", "pchar_back_to_player", 0.8);
			CreateLocationParticles("blood_big", "quest", "quest4", 2.0, 0, 0, "");
			PlaySound("People Fight\Damage_NPC_03.wav");
			i = makeint(LAi_GetCharacterHP(pchar)/2); // 3 прогона
			LAi_ApplyCharacterDamage(pchar, i, "fire");
			n = MOD_SKILL_ENEMY_RATE; // 3 прогона
			AddCharacterHealth(pchar, -n);
			DoQuestCheckDelay("Mtraxx_RetributionJeffryAngry", 1.0);
		break;
		
		case "Mtraxx_RetributionJeffryAngry": // Джеффри перед боем
			sld = characterFromId("Jeffry");
			sld.dialog.currentnode = "Jeffry_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.2);
		break;
		
		case "Mtraxx_RetributionJeffryAfterFight": // окончили бой с Джеффри
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			AddQuestRecord("Roger_10", "8");
			pchar.quest.mtraxx_retribution_ruins2.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_ruins2.win_condition.l1.location = "Judgement_dungeon_04";
			pchar.quest.mtraxx_retribution_ruins2.function = "Mtraxx_RetributionMushketers";
			n = MOD_SKILL_ENEMY_RATE; // 3 прогона
			AddCharacterHealth(pchar, -n);
		break;
		
		case "Mtraxx_RetributionMushAfterFight": // окончили бой с 1-мушкетерами
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_retribution_ruins3.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_ruins3.win_condition.l1.location = "Judgement_dungeon_03";
			pchar.quest.mtraxx_retribution_ruins3.function = "Mtraxx_RetributionNextMushketers";
		break;
		
		case "Mtraxx_RetributionNextMushAfterFight": // окончили бой с 2-мушкетерами
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_retribution_ruins4.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_ruins4.win_condition.l1.location = "Judgement_dungeon_02";
			pchar.quest.mtraxx_retribution_ruins4.function = "Mtraxx_RetributionLastMushketers";
		break;
		
		case "Mtraxx_RetributionLastMushAfterFight": // окончили бой с 3-мушкетерами
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_retribution_ruins5.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_ruins5.win_condition.l1.location = "Judgement_dungeon_01";
			pchar.quest.mtraxx_retribution_ruins5.function = "Mtraxx_RetributionSetLepricon";
		break;
		
		case "Mtraxx_RetributionLepriconAfterFight": // окончили бой с Леприконом 3 прогона
			LAi_group_Delete("EnemyFight");
			bNoEatNoRats = true;
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Judgement_dungeon_01", "reload1", true);
			LocatorReloadEnterDisable("Ruins", "reload2_back", true);
			n = Findlocation("Ruins");
			locations[n].models.always.blockade = "ruins1_blockade";
			Locations[n].models.always.blockade.tech = "DLightModel";
			Locations[n].models.day.charactersPatch = "ruins1_qpatch";
			Locations[n].models.night.charactersPatch = "ruins1_qpatch";
			LAi_LocationDisableOfficersGen("Ruins", true);//офицеров не пускать
			LAi_LocationDisableOfficersGen("Carataska_jungle_03", true);
			LAi_LocationDisableOfficersGen("Carataska_jungle_02", true);
			LAi_LocationDisableOfficersGen("Carataska_Cave", true);
			LAi_LocationDisableOfficersGen("Carataska_CaveEntrance", true);
			LAi_LocationDisableOfficersGen("Carataska_jungle_01", true);
			LAi_LocationDisableOfficersGen("Shore10", true);
			pchar.quest.mtraxx_retribution_exit.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_exit.win_condition.l1.location = "Judgement_dungeon_01";
			pchar.quest.mtraxx_retribution_exit.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_exit.win_condition.l1.locator = "reload1";
			pchar.quest.mtraxx_retribution_exit.function = "Mtraxx_RetributionExitClosed";
			pchar.questTemp.Mtraxx.Retribution.ExitClosed = "true";
			AddQuestRecord("Roger_10", "9");
		break;
		
		case "Mtraxx_RetributionCreateEnrico": // ставим Энрико
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "quest", "door");
			sld = GetCharacter(NPC_GenerateCharacter("Zorro", "Enrique_1", "man", "man", 40, SPAIN, -1, false, "quest"));
			FantomMakeCoolFighter(sld, 40, 110, 110, "blade_17", "pistol5", "cartridge", 250);
			sld.Dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "enrico";
			sld.name = "дон Энрико";
			sld.lastname = "";
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Judgement_dungeon_01", "monsters", "monster5");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "zorro", "Mtraxx_RetributionEnrico", -1);
		break;
		
		case "Mtraxx_RetributionEnrico": // разговор с Энрико
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Zorro");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
			ResetSound();
			SetMusic("music_teleport");
		break;
		
		case "Mtraxx_RetributionEnricoGo": // Энрико ушел
			PlaySound("ambient\jail\jail_door2.wav");
			LAi_SetPlayerType(pchar);
			ResetSound();
			SetMusic("music_alcove");
			AddQuestRecord("Roger_10", "10");
			for (i=2; i<=7; i++)
			{
				sTemp = "mtraxx_retribution_time"+i;
				pchar.quest.(sTemp).win_condition.l1 = "location";
				pchar.quest.(sTemp).win_condition.l1.location = "Judgement_dungeon_0"+i;
				pchar.quest.(sTemp).function = "Mtraxx_RetributionTwoHoursTime";
			}
			pchar.quest.mtraxx_retribution_church.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_church.win_condition.l1.location = "Judgement_church";
			pchar.quest.mtraxx_retribution_church.function = "Mtraxx_RetributionInChurchRuins";
			pchar.questTemp.Mtraxx.Retribution.DoorOpen = "true";
		break;
		
		case "Mtraxx_RetributionDoorOpen": // открыли дверь вниз
			AddQuestRecord("Roger_10", "11");
		break;
		
		case "Mtraxx_RetributionChurchLock": // сцена закрытых дверей
			PlaySound("interface\knock.wav");
			LAi_ActorGoToLocator(pchar, "quest", "LLquest3", "Mtraxx_RetributionChurchLock1", -1);
		break;
		
		case "Mtraxx_RetributionChurchLock1": // сцена закрытых дверей
			PlaySound("interface\knock.wav");
			LAi_ActorGoToLocator(pchar, "quest", "LLquest1", "Mtraxx_RetributionChurchLock2", -1);
		break;
		
		case "Mtraxx_RetributionChurchLock2": // беседа самого с собой
			pchar.questTemp.Mtraxx.Retribution.Bead = "true";
			LAi_SetPlayerType(pchar);
			DoQuestCheckDelay("TalkSelf_Quest", 1.0);
		break;
		
		case "Mtraxx_RetributionBead": // молитва
			bDisableCharacterMenu = true;//лочим F2
			InterfaceStates.Buttons.Save.enable = false;
			pchar.questTemp.NoFast = true;
			ResetSound();
			SetMusic("music_terrain");
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Bead", "", -1);
			DoQuestCheckDelay("Mtraxx_RetributionGotoSleep", 45.0);
		break;
		
		case "Mtraxx_RetributionGotoSleep": // ложится спать
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Ground_SitDown", "Mtraxx_RetributionGotoSleep1", 3.0);
		break;
		
		case "Mtraxx_RetributionGotoSleep1": // ложится спать
			LAi_SetActorType(pchar);
			LAi_ActorSetLayMode(pchar);
			DoQuestFunctionDelay("Mtraxx_RetributionSleep", 5.0);
		break;
		
		case "Mtraxx_RetributionSleep": // снится Мерида
			LAi_SetActorType(pchar);
			PlaySound("ambient\church\zvon.wav");
			DoQuestFunctionDelay("Mtraxx_RetributionSetMusic", 1.2);
			for (i=1; i<=18; i++) // дым
			{
				if (i == 3) continue;
				CreateLocationParticles("Bomb_Smoke", "reload", "reload"+i, 0, 0, 0, "torch_deck");
			}
			for (i=1; i<=18; i++) // огонь
			{
				if (i == 3) continue;
				CreateLocationParticles("shipfire", "reload", "reload"+i, 0, 0, 0, "fortfire");
			}
			for (i=1; i<=15; i++) // дым
			{
				CreateLocationParticles("smoke", "goto", "goto"+i, 0, 0, 0, "");
			}
			for (i=1; i<=8; i++) // жертвы
			{
				if (i < 5) sld = GetCharacter(NPC_GenerateCharacter("Sleep_Meridavictim_"+i, "women_"+(9+i), "woman", "towngirl", 1, SPAIN, 1, true, "quest"));
				else sld = GetCharacter(NPC_GenerateCharacter("Sleep_Meridavictim_"+i, "citiz_1"+i, "man", "man", 1, SPAIN, 1, true, "quest"));
				ChangeCharacterAddressGroup(sld, "Merida_town", "quest", "quest"+i);
				LAi_SetActorType(sld);
				if (i < 8) LAi_ActorGoToLocation(sld, "merchant", "merchant3", "none", "", "", "", 40);
				else LAi_ActorGoToLocation(sld, "merchant", "merchant3", "none", "", "", "Mtraxx_RetributionSleep1", 40);
			}
		break;
		
		case "Mtraxx_RetributionSleep1": // 
			PlaySound("ambient\church\zvon.wav");
			sld = GetCharacter(NPC_GenerateCharacter("Sleep_Meridahead", "huber_spa", "man", "man", 1, SPAIN, 1, true, "quest"));
			sld.name = "Деметрио";
			sld.lastname = "Рохас";
			sld.dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "merida_head_sleep";
			ChangeCharacterAddressGroup(sld, "Merida_town", "reload", "reload3");
			LAi_SetActorType(sld);
			DoQuestCheckDelay("pchar_back_to_player", 2.0);
			LAi_ActorDialogDelay(sld, pchar, "", 2.5);
		break;
		
		case "Mtraxx_RetributionSleep2": // 
			PlaySound("ambient\church\zvon.wav");
			LAi_SetActorType(pchar);
			sld = characterFromId("Sleep_Meridahead");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CreateLocationParticles("Bomb_Smoke", "reload", "reload3", 3, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "reload3", 0, 0, 0, "fortfire");
			DoQuestCheckDelay("Mtraxx_RetributionSleep3", 2.0);
		break;
		
		case "Mtraxx_RetributionSleep3": // 
			PlaySound("ambient\church\zvon.wav");
			sld = GetCharacter(NPC_GenerateCharacter("Sleep_Camilla", "women_16", "man", "towngirl", 1, SPAIN, 1, true, "quest"));
			sld.name = "Камилла";
			sld.lastname = "";
			sld.dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "camilla_sleep";
			RemoveAllCharacterItems(sld, true);
			ChangeCharacterAddressGroup(sld, "Merida_town", "merchant", "merchant1");
			LAi_SetActorType(sld);
			DoQuestCheckDelay("pchar_back_to_player", 2.0);
			LAi_ActorDialogDelay(sld, pchar, "", 2.5);
		break;
		
		case "Mtraxx_RetributionSleep4": // 
			PlaySound("ambient\church\zvon.wav");
			LAi_SetActorType(pchar);
			sld = characterFromId("Sleep_Camilla");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = GetCharacter(NPC_GenerateCharacter("Sleep_Mishelle", "Migel_1", "man", "man", 1, FRANCE, 2, true, "quest"));
			sld.name = "Мишель";
			sld.lastname = "де Монпе";
			sld.dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "mishelle_sleep";
			RemoveAllCharacterItems(sld, true);
			ChangeCharacterAddressGroup(sld, "Merida_town", "quest", "stay2");
			LAi_SetActorType(sld);
			DoQuestCheckDelay("pchar_back_to_player", 2.0);
			LAi_ActorDialogDelay(sld, pchar, "", 2.5);
		break;
		
		case "Mtraxx_RetributionSleep5": // 
			PlaySound("ambient\church\zvon.wav");
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("pchar_back_to_player", 2.0);
			sld = characterFromId("Sleep_Mishelle");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = GetCharacter(NPC_GenerateCharacter("Sleep_Terrax", "Terrax", "man", "man", 1, PIRATE, 1, true, "quest"));
			FantomMakeCoolFighter(sld, 50, 110, 110, "blade_19", "pistol4", "bullet", 300);
			sld.name = "Маркус";
			sld.lastname = "Тиракс";
			sld.dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "terrax_sleep";
			ChangeCharacterAddressGroup(sld, "Merida_town", "goto", "goto25");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = GetCharacter(NPC_GenerateCharacter("Sleep_Jeffry", "Jeffry", "man", "man", 35, PIRATE, 1, true, "marginal"));
			sld.name = "Джеффри";
			sld.lastname = "Брук";
			ChangeCharacterAddressGroup(sld, "Merida_town", "goto", "goto15");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromId("Sleep_Terrax"), "", 8.0);
			sld = GetCharacter(NPC_GenerateCharacter("Sleep_Pelly", "Tesak", "man", "man", 35, PIRATE, 1, true, "marginal"));
			sld.name = "Пол";
			sld.lastname = "Чант";
			ChangeCharacterAddressGroup(sld, "Merida_town", "goto", "goto15");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromId("Sleep_Terrax"), "", 8.0);
			sld = GetCharacter(NPC_GenerateCharacter("Sleep_Lepricon", "Leprechaun", "man", "man", 35, PIRATE, 1, true, "marginal"));
			sld.name = "Люка";
			sld.lastname = "Байярд";
			ChangeCharacterAddressGroup(sld, "Merida_town", "goto", "goto15");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromId("Sleep_Terrax"), "", 8.0);
		break;
		
		case "Mtraxx_RetributionSleep6": // 
			PlaySound("ambient\church\zvon.wav");
			LAi_SetActorType(pchar);
			sld = characterFromId("Sleep_Terrax");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("Sleep_Jeffry");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("Sleep_Pelly");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("Sleep_Lepricon");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			if (GetCharacterIndex("Mirabella") != -1) // спасли Мирабель
			{
				sld = GetCharacter(NPC_GenerateCharacter("Sleep_Mirabella", "Mirabelle", "woman", "towngirl", 1, SPAIN, 1, true, "quest"));
				sld.name = "Мирабель";
				sld.lastname = "";
				sld.dialog.Filename = "Quest\Roger.c";
				sld.dialog.currentnode = "mirabelle_sleep";
				ChangeCharacterAddressGroup(sld, "Merida_town", "goto", "goto29");
				LAi_SetActorType(sld);
				DoQuestCheckDelay("pchar_back_to_player", 2.0);
				LAi_ActorDialogDelay(sld, pchar, "", 2.5);
			}
			else
			{
				sld = characterFromId("Sleep_Mishelle");	
				ChangeCharacterAddressGroup(sld, "Merida_town", "goto", "goto31");
				sld.dialog.currentnode = "mishelle_sleep_1";
				DoQuestCheckDelay("pchar_back_to_player", 2.0);
				LAi_ActorDialogDelay(sld, pchar, "", 2.5);
			}
		break;
		
		case "Mtraxx_RetributionSleep6_1": // 
			PlaySound("ambient\church\zvon.wav");
			sld = characterFromId("Sleep_Mirabella");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("Sleep_Mishelle");	
			ChangeCharacterAddressGroup(sld, "Merida_town", "goto", "goto31");
			sld.dialog.currentnode = "mishelle_sleep_1";
			DoQuestCheckDelay("pchar_back_to_player", 2.0);
			LAi_ActorDialogDelay(sld, pchar, "", 2.5);
		break;
		
		case "Mtraxx_RetributionSleep7": // 
			PlaySound("ambient\church\zvon.wav");
			LAi_SetActorType(pchar);
			sld = characterFromId("Sleep_Mishelle");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			DoQuestCheckDelay("Mtraxx_RetributionSleep8", 3.0);
		break;
		
		case "Mtraxx_RetributionSleep8": // 
			PlaySound("ambient\church\zvon.wav");
			WaitDate("", 0, 0, 0, 18, rand(30)); //крутим время
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			DoQuestReloadToLocation("Judgement_church", "quest", "LLquest9", "Mtraxx_RetributionAwake");
		break;
		
		case "Mtraxx_RetributionAwake": // просыпается
			chrDisableReloadToLocation = false;
			AddCharacterHealth(pchar, -10);
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			DeleteAttribute(pchar, "questTemp.NoFast");
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Roger_10", "12");
			sld = ItemsFromID("key_ruins");
			sld.shown = true;
			sld.startLocation = "Judgement_dungeon_07";
			sld.startLocator = "item"+(rand(4)+1);
		break;
		
		case "Mtraxx_RetributionFreedom": // молится за спасение
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Bead", "", -1);
			InterfaceStates.Buttons.Save.enable = false;
			bDisableCharacterMenu = true;
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
			DoQuestCheckDelay("Mtraxx_RetributionPromice", 5.0);
			PlaySound("ambient\church\zvon.wav");
		break;
		
		case "Mtraxx_RetributionPromice": // 
			PlaySound("ambient\church\zvon.wav");
			Log_Info("Я, Шарль де Мор, французский капитан и дворянин, клянусь перед собой и своей совестью:");
			DoQuestCheckDelay("Mtraxx_RetributionPromice1", 6.0);
		break;
		
		case "Mtraxx_RetributionPromice1": // 
			PlaySound("ambient\church\zvon.wav");
			Log_Info("... клянусь, что навсегда порываю со своим пиратским прошлым ...");
			DoQuestCheckDelay("Mtraxx_RetributionPromice2", 6.0);
		break;
		
		case "Mtraxx_RetributionPromice2": // 
			PlaySound("ambient\church\zvon.wav");
			Log_Info("... клянусь, что более ни один мирный гражданин не пострадает от моей руки ...");
			DoQuestCheckDelay("Mtraxx_RetributionPromice3", 6.0);
		break;
		
		case "Mtraxx_RetributionPromice3": // 
			PlaySound("ambient\church\zvon.wav");
			Log_Info("... клянусь защищать женщин, независимо от их положения и национальности ...");
			DoQuestCheckDelay("Mtraxx_RetributionPromice4", 6.0);
		break;
		
		case "Mtraxx_RetributionPromice4": // 
			PlaySound("ambient\church\zvon.wav");
			Log_Info("... клянусь, что блеск золота никогда более не затмит мой разум ...");
			DoQuestCheckDelay("Mtraxx_RetributionPromice5", 6.0);
		break;
		
		case "Mtraxx_RetributionPromice5": // 
			PlaySound("ambient\church\zvon.wav");
			Log_Info("... клянусь пресекать действия любых негодяев, повстречавшихся мне на пути ...");
			DoQuestCheckDelay("Mtraxx_RetributionPromice6", 6.0);
		break;
		
		case "Mtraxx_RetributionPromice6": // 
			PlaySound("ambient\church\zvon.wav");
			Log_Info("... клянусь, что между богатством и честью я выберу честь ...");
			DoQuestCheckDelay("Mtraxx_RetributionPromice7", 6.0);
		break;
		
		case "Mtraxx_RetributionPromice7": //
			PlaySound("ambient\church\zvon.wav");
			Log_Info("... клянусь, что в любых обстоятельствах и с любыми людьми я буду оставаться достойным человеком ...");
			DoQuestCheckDelay("Mtraxx_RetributionFinal", 6.0);
		break;
		
		case "Mtraxx_RetributionFinal": // завершение линейки квестов
			locCameraResetState();
			PlaySound("ambient\church\zvon.wav");
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;
			bNoEatNoRats = false;
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Roger_10", "17");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			if (GetCharacterIndex("Mirabella") != -1)
			{
				AddQuestUserData("Roger_10", "sText", "Мне почему-то внезапно вспомнилась Мирабель. Как она там, на острове? Скучает? Наверное, было жестоко заставить молодую девушку жить в одиночестве. Я исправлю это! Надо поскорее навестить ее.");
				sld = characterFromId("Mirabella");
				sld.dialog.currentnode = "mirabelle_29";
			}
			pchar.quest.mtraxx_line_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_line_complete.function = "Mtraxx_RetributionComplete";
		break;
		
/// Jason ----------------------------------------------------------- На службе Отечеству ------------------------------------------------------------------
		case "Patria_VisiterTortuga": //
			sld = characterFromId("Noel");
			RemovePassenger(pchar, sld);
			AddQuestRecord("Patria", "11");
			LocatorReloadEnterDisable("Tortuga_town", "reload3_back", true);
			pchar.quest.Patria_Visiter_TortugaBack.win_condition.l1 = "Timer";
			pchar.quest.Patria_Visiter_TortugaBack.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Patria_Visiter_TortugaBack.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Patria_Visiter_TortugaBack.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Patria_Visiter_TortugaBack.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Patria_Visiter_TortugaBack.function = "Patria_VisiterTortugaBack";
		break;
		
		case "Patria_VisiterPortPax": //
			sld = characterFromId("Noel");
			RemovePassenger(pchar, sld);
			AddQuestRecord("Patria", "13");
			LocatorReloadEnterDisable("Portpax_town", "reload3_back", true);
			pchar.quest.Patria_Visiter_PortpaxBack.win_condition.l1 = "Timer";
			pchar.quest.Patria_Visiter_PortpaxBack.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Patria_Visiter_PortpaxBack.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Patria_Visiter_PortpaxBack.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Patria_Visiter_PortpaxBack.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Patria_Visiter_PortpaxBack.function = "Patria_VisiterPortPaxBack";
		break;
		
		case "Patria_StivesantWait": //
			SetLaunchFrameFormParam("Прошло два часа..."+ NewStr() +"", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
			StoreDayUpdate();
			RefreshWeather();
			RefreshLandTime();
			DoQuestFunctionDelay("Patria_StivesantWait", 5.0);
		break;
		
		case "Patria_StivesantSit": //
			sld = characterFromId("Stivesant");
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		break;
		
		case "Patria_SanMartinSetBaron": //
			sld = characterFromId("Noel");
			LAi_SetStayType(sld);
		break;
		
		case "Patria_SanMartinBaron": //
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			AddQuestRecord("Patria", "26");
			SetFunctionTimerCondition("Patria_SanMartinBaronOver", 0, 0, 7, false); // таймер
			sld = characterFromId("Noel");
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			// атрибуты на Синт-Маартен
			pchar.questTemp.Patria.SanMartinFort = "true"; // атака
			n = FindIsland("SentMartin");
			Islands[n].reload.l1.radius = 0.0; // закрыть высадку в порту
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", true); // закрыть городские ворота
			sld = CharacterFromID("Marigo Fort Commander");
			LAi_SetImmortal(sld, true);
			Character_SetAbordageEnable(sld, false); // неабордируемый форт Синт-Маартена
		break;
		
		case "Patria_SanMartinBack": //
			pchar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			pchar.questTemp.Patria = "epizode_5_return";
			pchar.quest.Patria_SanMartin_Back.win_condition.l1 = "location";
			pchar.quest.Patria_SanMartin_Back.win_condition.l1.location = "Nevis";
			pchar.quest.Patria_SanMartin_Back.function = "Patria_SanMartinBack";
			SetFunctionTimerCondition("Patria_SanMartinBaronOver", 0, 0, 7, false); // таймер
		break;
		
		case "Patria_SanMartinBaronTurn": //
			sld = characterFromId("Noel");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromID("Puancie"));
		break;
		
		case "Patria_DiplomatGetOut": //
			LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true);
			pchar.quest.Patria_DiplomatSail.win_condition.l1 = "MapEnter";
			pchar.quest.Patria_DiplomatSail.function = "Patria_DiplomatSail";
			pchar.questTemp.Patria = "epizode_6_return";
			AddQuestRecord("Patria", "30");
		break;
		
		case "Patria_DiplomatAfterFight": //
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("hide_weapon", 0.2);
			LAi_group_Delete("EnemyFight");
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload4", "Patria_DiplomatEscape");
		break;
		
		case "Patria_DiplomatEscape": //
			LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true);
			pchar.quest.Patria_DiplomatSail.win_condition.l1 = "MapEnter";
			pchar.quest.Patria_DiplomatSail.function = "Patria_DiplomatSail";
			pchar.questTemp.Patria = "epizode_6_return";
			AddQuestRecord("Patria", "31");
			SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY);
		break;
		
		case "Patria_BastionMineAttackWin": //
			LAi_group_Delete("EnemyFight");
			DoQuestCheckDelay("hide_weapon", 1.3);
			DoQuestCheckDelay("sea_victory", 1.3);
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Location_reserve_01", "reload2_back", false); // открыть выход назад
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			sld = characterFromId("Marigo_Mayor");
			ChangeCharacterAddressGroup(sld, "none", "", ""); // прячем губера
			LocatorReloadEnterDisable("Marigo_town", "gate_back", false);//открыть выход из города
			SetFunctionTimerCondition("Patria_BastionNewHuber", 0, 0, 10, false); // через 10 дней обновим губера на нового и обновим рудник
			// меняем нацию Синт-Маартена
			i = FindColony("Marigo");
			colonies[i].nation = FRANCE;
			string sColony = "Marigo_town";
			worldMap.labels.(sColony).icon = FRANCE;
			// ручками пропишем смену нации статикам
			sld = characterFromId("Marigo_Priest");
			sld.nation = FRANCE;
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld = characterFromId("Marigo_waitress");
			sld.nation = FRANCE;
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld = characterFromId("Marigo_tavernkeeper");
			sld.nation = FRANCE;
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld = characterFromId("Marigo_trader");
			sld.nation = FRANCE;
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld = characterFromId("Marigo_Priest");
			sld.nation = FRANCE;
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld = characterFromId("Marigo_shipyarder");
			sld.nation = FRANCE;
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld = characterFromId("Marigo_usurer");
			sld.nation = FRANCE;
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld = characterFromId("Marigo_PortMan");
			sld.nation = FRANCE;
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld = characterFromId("Marigo_Hostess");
			sld.nation = FRANCE;
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld = CharacterFromID("Marigo Fort Commander"); // лесник . оживил форт после боя смены нации филипсбурга (для НИ)
			sld.nation = FRANCE;
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			// заставка форта
			n = Findlocation("Marigo_fort");
			Locations[n].image = "loading\fort_fra_" + rand(1) + ".tga";
			// чистим за собой
			DeleteAttribute(pchar, "TempPerks.QuestTroopers"); // убрать квестовый десант
			for (i=1; i<=15; i++)
			{
				sld = CharacterFromID("Bastion_soldier_"+i);
				sld.lifeday = 0;
			}
			// выводим фрегаты из эскадры, если таковые были и живы
			if (GetCharacterIndex("Patria_GlpCap") != -1)
			{
				sld = characterFromId("Patria_GlpCap");
				RemoveCharacterCompanion(pchar, sld);
			}
			if (GetCharacterIndex("Patria_MrtCap") != -1)
			{
				sld = characterFromId("Patria_MrtCap");
				RemoveCharacterCompanion(pchar, sld);
			}
			// начальника рудника - в пленники
			sld = GetCharacter(NPC_GenerateCharacter("Bastion_spanish_boss", "Boss_2", "man", "man", 15, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 15, 20, 20, LinkRandPhrase("blade_18","blade_19","blade_21"), "pistol5", "bullet", 50);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			pchar.questTemp.Patria.SpanishName = GetFullName(sld);
			sld = characterFromId(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)]);
			pchar.questTemp.Patria.SpanishID = sld.id;
			log_info("В одном из домов был обнаружен, схвачен и посажен в трюм распорядитель рудника");
			pchar.questTemp.Patria = "epizode_9_return";
			AddQuestRecord("Patria", "51");
		break;
		
		case "Patria_CuracaoTrooperLand": //
			Island_SetReloadEnableGlobal("Curacao", true); //открыть остров
			pchar.GenQuest.MapClosedNoBattle = true;
			DeleteAttribute(pchar, "DisableChangeFlagMode"); // разблокировать флаг
			chrDisableReloadToLocation = true;
			sld = characterFromId("Doily_land");
			LAi_SetImmortal(sld, true);
			sld.dialog.currentnode = "doily_18";
			ChangeCharacterAddressGroup(sld, "shore24", "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			// отряд Дойли с пушками
			for (i=1; i<=15; i++)
			{
				if (i < 7) // мушкетеры, 6 шт
				{
					sld = GetCharacter(NPC_GenerateCharacter("Curacao_eng_soldier_"+i, "mush_eng_"+i, "man", "mushketer", 35, ENGLAND, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, 35, 70, 70, "", "mushket2", "cartridge", 200);
					LAi_SetCharacterUseBullet(sld, "cartridge");
					sld.cirassId = Items_FindItemIdx("cirass1");
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("Curacao_eng_soldier_"+i, "sold_eng_"+(rand(7)+9), "man", "man", 35, ENGLAND, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, 35, 65, 65, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 170);
					sld.cirassId = Items_FindItemIdx("cirass2");
				}
				LAi_SetCheckMinHP(sld, 10, true, ""); 
				ChangeCharacterAddressGroup(sld, "shore24", "goto", "goto7");
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_ActorFollow(sld, characterFromID("Doily_land"), "", -1);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
			}
		break;
		
		case "Patria_CuracaoAfterJungleMushketer": //
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			pchar.quest.Patria_CuracaoMarch1.win_condition.l1 = "location";
			pchar.quest.Patria_CuracaoMarch1.win_condition.l1.location = "Curacao_jungle_01";
			pchar.quest.Patria_CuracaoMarch1.function = "Patria_CuracaoJungleBattle"; // второй отряд голландцев
		break;
		
		case "Patria_CuracaoAfterJungleBattle": //
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			pchar.quest.Patria_CuracaoMarch2.win_condition.l1 = "location";
			pchar.quest.Patria_CuracaoMarch2.win_condition.l1.location = "Villemstad_ExitTown";
			pchar.quest.Patria_CuracaoMarch2.function = "Patria_CuracaoGateBattle"; // у ворот
		break;
		
		case "Patria_CuracaoGateBattle1": //
			LAi_ActorTurnToLocator(pchar, "reload", "reload4");
			DoQuestFunctionDelay("Patria_CuracaoGateBattle2", 4.0);
		break;
		
		case "Patria_CuracaoGateBattleMush1": //
			for (i=5; i<=7; i++)
			{
				sld = characterFromId("Curacao_hol3_soldier_"+i);
				LAi_KillCharacter(sld);
			}
			DoQuestFunctionDelay("Patria_CuracaoGateBattle3", 5.0);
		break;
		
		case "Patria_CuracaoGateBattleEnd": //
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=15; i++)
			{
				sld = characterFromId("Curacao_eng_soldier_"+i);
				LAi_SetActorType(sld);
				if (i >= 7 && i < 14) 
				{
					LAi_ActorRunToLocator(sld, "quest", "sold"+i, "", -1);
				}
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// на всякий случай сброс шаблона, если вдруг где-то безобразничают
			for (i=1; i<=15; i++)
			{
				if (GetCharacterIndex("Curacao_fra_soldier_"+i) != -1)
				{
					sld = characterFromId("Curacao_fra_soldier_"+i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "quest", "hero", "Patria_CuracaoGateTalk", -1);
		break;
		
		case "Patria_CuracaoGateTalk": //
			SetMusic("music_military");
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_23";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Patria_CuracaoStivesantWait": //
			SetLaunchFrameFormParam("Прошло двадцать три часа..."+ NewStr() +"Питер Стайвесант выходит из ворот", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 23, 10); //крутим время
			RecalculateJumpTable();
			StoreDayUpdate();
			RefreshWeather();
			RefreshLandTime();
			DoQuestFunctionDelay("Patria_CuracaoStivesant", 5.0);
		break;
		
		case "Patria_CuracaoResult": //
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Patria_CondotierTavern": //
			if(CheckAttribute(pchar, "IsMushketer"))
			{
				SetMainCharacterToMushketer("", false);
			}
			FreeSitLocator("PortPax_tavern", "sit_front1");
			sld = CharacterFromID("Noel");
			sld.Dialog.currentnode = "noel_31";
			ChangeCharacterAddressGroup(sld, "PortPax_tavern", "sit", "sit_front1");
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Patria_CondotierToPirates": //
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Noel");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			SetFunctionTimerCondition("Patria_CondotierTimeOver", 0, 0, 15, false); // две недели на разговор с Акулой/Тираксом 
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "end" && colonies[FindColony("Pirates")].nation == PIRATE) // пройдена Сага до конца
			{
				if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) 
				{
					pchar.questTemp.Patria.Saga.Shark = "true"; // Додсон жив
					AddQuestRecord("Patria", "68_1");
				}
				else 
				{
					pchar.questTemp.Patria.Saga.Terrax = "true"; // Додсон погиб, вместо него Тиракс
					AddQuestRecord("Patria", "68_2");
				}
			}
			else 
			{
				pchar.questTemp.Patria.Pirate.Terrax = "true"; // Сага не пройдена, к Тираксу в Ла Вегу
				AddQuestRecord("Patria", "68_3");
			}
		break;
		
		case "Patria_CondotierDodsonNorm": //
			chrDisableReloadToLocation = false;
			Group_DeleteGroup("DodsonFrigate");
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Shark"))
			{
				sld = CharacterFromID("Dodson");
				sld.dialog.currentnode = "First time";
			}
			else
			{
				sld = CharacterFromID("Terrax");
				sld.dialog.currentnode = "I_know_you_good";
			}
			ChangeCharacterAddressGroup(sld, "Pirates_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
		break;
		
		case "Patria_CondotierTerraxNorm": //
			chrDisableReloadToLocation = false;
			Group_DeleteGroup("DodsonFrigate");
			sld = CharacterFromID("Terrax");
			sld.dialog.currentnode = "I_know_you_good";
			ChangeCharacterAddressGroup(sld, "Lavega_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			LocatorReloadEnterDisable("Lavega_town", "reload6", false);
		break;
		
		case "Patria_CondotierBaronDie": //
			sld = CharacterFromID("Noel");
			LAi_KillCharacter(sld);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Shark")) sld = CharacterFromID("Dodson");
			else sld = CharacterFromID("Terrax");
			sld.dialog.currentnode = "patria_24";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
		break;
		
		case "Patria_CondotierToCabin": //
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Noel");
			ChangeCharacterAddressGroup(sld, "Portpax_tavern", "tables", "stay2");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.quest.Patria_Condotier_inCabin.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_inCabin.win_condition.l1.location = Get_My_Cabin();
			pchar.quest.Patria_Condotier_inCabin.function = "Patria_CondotierInCabin";
		break;
		
		case "Patria_CondotierToSMartin": //
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			AddQuestRecord("Patria", "79");
			LocatorReloadEnterDisable("Shore40", "reload2_back", true);//закрыть локатор на рудник
			LAi_LocationDisableOfficersGen("shore40", true);
			LAi_LocationDisableOfficersGen("Location_reserve_01", true);
			LAi_LocationDisableOfficersGen("Location_reserve_03", true);
			pchar.quest.Patria_Condotier_sail.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_sail.win_condition.l1.location = "shore40";
			pchar.quest.Patria_Condotier_sail.win_condition.l2 = "Night";
			pchar.quest.Patria_Condotier_sail.function = "Patria_CondotierToMine";
			// 2 месяца до Стайвесанта, иначе барон даст дуба
			SetFunctionTimerCondition("Patria_CondotierBaronFail", 0, 0, 60, false); // таймер
		break;
		
		case "Patria_CondotierInMine": //
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Noel");
			sld.dialog.currentnode = "noel_76";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Patria_CondotierToBeach": //
			DoQuestReloadToLocation("Location_reserve_01", "reload", "reload1_back", "Patria_CondotierOnBeach");
		break;
		
		case "Patria_CondotierOnBeach": // охрана пришла
			pchar.GenQuest.Hunter2Pause = true;
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation("Location_reserve_01")], true);//запретить драться
			for (i=1; i<=5; i++)
			{
				if (i < 3) // мушкетеры, 2 шт
				{
					sld = GetCharacter(NPC_GenerateCharacter("Marigo_eng_soldier_"+i, "mush_eng_"+i, "man", "mushketer", 25, ENGLAND, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, 25, 50, 50, "", "mushket1", "cartridge", 150);
					LAi_SetCharacterUseBullet(sld, "cartridge");
					if (MOD_SKILL_ENEMY_RATE > 4) sld.cirassId = Items_FindItemIdx("cirass1");
				}
				else
				{
					if (i == 5) 
					{
						sld = GetCharacter(NPC_GenerateCharacter("Marigo_eng_soldier_"+i, "off_eng_1", "man", "man", 25, ENGLAND, -1, false, "soldier"));
						FantomMakeCoolFighter(sld, 25, 50, 50, LinkRandPhrase("blade_20","blade_21","blade_17"), "pistol5", "bullet", 150);
					}
					else 
					{
						sld = GetCharacter(NPC_GenerateCharacter("Marigo_eng_soldier_"+i, "sold_eng_"+(rand(7)+9), "man", "man", 20, ENGLAND, -1, false, "soldier"));
						FantomMakeCoolFighter(sld, 20, 40, 40, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 100);
					}
					if (MOD_SKILL_ENEMY_RATE > 4) sld.cirassId = Items_FindItemIdx("cirass2");
				}
				ChangeCharacterAddressGroup(sld, "Location_reserve_01", "rld", "loc0");
				LAi_SetActorType(sld);
				if (i == 5)
				{
					sld.Dialog.Filename = "Quest\Patria_NPC.c";
					sld.dialog.currentnode = "engofficer";
				}
				else LAi_CharacterDisableDialog(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "Patria_CondotierBeachAfterFight": //
			chrDisableReloadToLocation = false;
			LAi_group_Delete("EnemyFight");
			LocatorReloadEnterDisable("Location_reserve_01", "reload1_back", true);//закрыть локатор на рудник
			if (CheckAttribute(pchar, "questTemp.Patria.Condotier.BaronKilled")) // барон помер
			{
				pchar.quest.Patria_CondotierBaronFail.over = "yes"; //снять прерывание
				DeleteAttribute(pchar, "GenQuest.CannotWait");
				AddQuestRecord("Patria", "75");
				pchar.questTemp.Patria = "epizode_12_baronkilled";
				LocatorReloadEnterDisable("Shore40", "reload1_back", false);
				LocatorReloadEnterDisable("Shore40", "boat", false);
				LAi_LocationDisableOfficersGen("shore40", false);
				LAi_LocationDisableOfficersGen("Location_reserve_01", false);
				LAi_LocationDisableOfficersGen("Location_reserve_03", false);
			}
			else
			{
				pchar.quest.Patria_Baron_killed.over = "yes"; //снять прерывание
				sld = CharacterFromID("Noel");
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				AddQuestRecord("Patria", "80");
				pchar.quest.Patria_CondotierShore40.win_condition.l1 = "location";
				pchar.quest.Patria_CondotierShore40.win_condition.l1.location = "shore40";
				pchar.quest.Patria_CondotierShore40.function = "Patria_CondotierInShore40";
			}
		break;
		
		case "Patria_CondotierOnCuracaoWait": //
			SetLaunchFrameFormParam("Прошел один день..."+ NewStr() +"", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 0, 10); //крутим время
			RecalculateJumpTable();
			StoreDayUpdate();
			RefreshWeather();
			RefreshLandTime();
			DoQuestFunctionDelay("Patria_CondotierStivesant", 5.0);
		break;
		
		case "Patria_CondotierStivesantInHall": //
			chrDisableReloadToLocation = false; // 17-add
			sld = CharacterFromID("Stivesant");
			sld.dialog.currentnode = "Stivesant_49";
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "governor1");
			LAi_SetStayType(sld);
		break;
		
		case "Patria_EuropePuancieInPrison": //
			DoQuestFunctionDelay("Patria_EuropeMusic", 1.5); // 7-add
			pchar.questTemp.jailCanMove = true;
			chrDisableReloadToLocation = true;//закрыть локацию
			LocatorReloadEnterDisable("Charles_town", "reload_jail", false);
		break;
		
/// Jason ----------------------------------------------------------- Дороже золота ------------------------------------------------------------------
		case "GoldenGirl_GirlExit": // подруга убегает
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableFastReload = false;//открыть переход
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "GoldenGirl_10";
			LAi_SetOfficerType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
		
		case "GoldenGirl_PartyTalk": //
			sld = characterFromId("Julianna");
			ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "goto", "goto5");
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "GoldenGirl_JulianaPause": //
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_15";
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		break;
		
		case "GoldenGirl_JulianaAfterPause": //
			sld = characterFromId("Julianna");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "GoldenGirl_CreateColonel": //
			sld = GetCharacter(NPC_GenerateCharacter("GG_Colonel", "off_fra_5", "man", "man", 35, FRANCE, -1, false, "quest"));
			FantomMakeCoolFighter(sld, 35, 80, 80, "blade_20", "pistol5", "cartridge", 150);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			sld.Dialog.Filename = "Quest\GoldenGirl.c";
			sld.dialog.currentnode = "comendant";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "GoldenGirl_Game1Res": // результаты 1 игры
			sld = characterFromId("GG_Colonel");
			sld.dialog.currentnode = "comendant_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "GoldenGirl_Game2Res": // результаты 2 игры
			sld = characterFromId("GG_Moreno");
			sld.dialog.currentnode = "moreno_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "GoldenGirl_Talking": // 
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_23";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "GoldenGirl_AngerranCards": //
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_9";
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld = characterFromId("GG_statist1");
			ChangeCharacterAddressGroup(sld, "Location_reserve_02", "goto", "goto8");
			LAi_SetActorType(sld);
		break;
		
		case "GoldenGirl_Game3Res": // результаты 3 игры
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_13";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "GoldenGirl_Game4Res": // результаты 4 игры
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "GoldenGirl_AfterCardsGames": //
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_39";
			ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "barmen", "bar1");
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		break;
		
		case "GoldenGirl_GirlShip": //
			chrDisableReloadToLocation = true;//закрыть локацию
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "GoldenGirl_12";
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "GoldenGirl_GirlToFregat": //
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			DeleteAttribute(sld, "CompanionDisable");
			RemovePassenger(Pchar, sld);
			RemoveCharacterCompanion(pchar, sld);
			sld.Ship.Type = GenerateShipHand(sld, SHIP_FRIGATE, 24, 4500, 350, 5200, 70000, 15.5, 39.0, 0.4);
			sld.Ship.name = "Найяд";
			SetBaseShipData(sld);
			sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
			RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 3;
			SetCrewQuantityOverMax(sld, 10);
			SetCharacterRemovable(sld, false);
			sld.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(sld, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			pchar.questTemp.GoldenGirl = "duel";
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "7");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			pchar.quest.goldengirl_duel.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_duel.win_condition.l1.date.hour  = sti(GetTime() + 8);
			pchar.quest.goldengirl_duel.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.goldengirl_duel.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.goldengirl_duel.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.goldengirl_duel.function = "GoldenGirl_DuelPrepare";
		break;
		
		case "GoldenGirl_DuelPrepare": //
			sld = characterFromId("GG_SecundantGG_1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "GoldenGirl_Duel": //
			DoQuestCheckDelay("hide_weapon", 1.0);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_31";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "GoldenGirl_AfterDuel": //
			LAi_group_Delete("EnemyFight");
			LAi_LocationDisableOfficersGen("FortFrance_ExitTown", false);
			locations[FindLocation("FortFrance_ExitTown")].DisableEncounters = false;
			n = 0;
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantGG_"+i);
				sld.lifeday = 0;
				if (LAi_GetCharacterHP(sld) > 0) n++;
			}
			pchar.questTemp.GoldenGirl.Officer = n;
			DoQuestCheckDelay("hide_weapon", 1.0);
			DoQuestCheckDelay("GoldenGirl_AfterDuelToGovernor", 4.0);
		break;
		
		case "GoldenGirl_AfterDuelToGovernor": //
			sld = characterFromId("FortFrance_Mayor");
			sld.Dialog.Filename = "Quest\GoldenGirl.c";
			sld.dialog.currentnode = "governor_25";
			DoQuestReloadToLocation("FortFrance_Townhall", "reload", "reload1", "");
			AddQuestRecord("GoldenGirl", "8");
		break;
		
		case "GoldenGirl_ToJulianna": //
			sld = characterFromId("Julianna");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "GoldenGirl_WithoutJulianna": // 
			DoQuestCheckDelay("GoldenGirl_SleepInRoom", 1.8);
		break;
		
		case "GoldenGirl_WithJulianna": //
			DoQuestCheckDelay("GoldenGirl_SexJulianna", 2.0);
		break;
		
		case "GoldenGirl_SexJulianna": //
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("", "", 0, 14);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex6.wav");
            LaunchFrameForm();
			DoQuestCheckDelay("GoldenGirl_AfterSexJulianna", 14.0);
			AddCharacterHealth(pchar, 6);
		break;
		
		case "GoldenGirl_AfterSexJulianna": //
			DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
			sld = characterFromId("Julianna");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "GoldenGirl_SleepInRoom", 5.0);
		break;
		
		case "GoldenGirl_SleepInRoom": //
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Следующим утром...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("GoldenGirl_SleepInRoomMorning", 4.0);
			LAi_SetCurHPMax(pchar);
			AddCharacterHealth(pchar, 6);
			// убираем фрегат
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			RemovePassenger(pchar, sld);
			RemoveCharacterCompanion(pchar, sld);
		break;
		
		case "GoldenGirl_SleepInRoomMorning": //
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_54";
			ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "GoldenGirl_BadNews": //
			LocatorReloadEnterDisable("FortFrance_town", "reload3_back", false);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_58";
			ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "barmen", "stay");
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld = GetCharacter(NPC_GenerateCharacter("GG_sailor", "citiz_"+(rand(9)+31), "man", "man", 10, FRANCE, 1, true, "soldier"));
			SetFantomParamFromRank(sld, 10, true);
			sld.Dialog.Filename = "Quest\GoldenGirl.c";
			sld.dialog.currentnode = "sailor";
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "reload", "reload9");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "GoldenGirl_AngerranInResidence": //
			chrDisableReloadToLocation = true;
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_34";
			ChangeCharacterAddressGroup(sld, "CommonResidence_3", "reload", "reload2");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "GoldenGirl_AfterBaster": //
			chrDisableReloadToLocation = false;
			sld = characterFromId("Angerran");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			pchar.quest.goldengirl_AngerranCap_AfterBattle.over = "yes"; //снять прерывание
			pchar.quest.GoldenGirl_GirlPrisonerFail.over = "yes"; //снять таймер
			SetFunctionTimerCondition("GoldenGirl_GirlDominicaFail", 0, 0, 15, false); // новый таймер
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_72";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "13");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			pchar.questTemp.GoldenGirl = "dominica";
		break;
		
		case "GoldenGirl_BrothelAfterFight": //
			LAi_group_Delete("EnemyFight");
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_78";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "GoldenGirl_DominicaAlarmFinal": // завершение силового варианта
			pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
			chrDisableReloadToLocation = true;//закрыть локацию
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.goldengirl_AngerranCap_AfterBattle.over = "yes";
			Group_DeleteGroup("GG_AngerranGroup");
			sld = characterFromId("GG_AngerranCap");
			sld.lifeday = 0;
			sld = characterFromId("Julianna");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
			setCharacterShipLocation(pchar, "shore27"));
			setWDMPointXZ("shore27"); // корабль на рейд
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "GoldenGirl_24";
			ChangeCharacterAddressGroup(sld, "shore27", "goto", "goto14");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			pchar.questTemp.GoldenGirl = "alarm_fin";
			pchar.questTemp.GoldenGirl.Angerran = "true"; // Шиво еще вернется fix 02-04-20
		break;
		
		case "GoldenGirl_GirlGoOnBoard":
			GoldenGirl_GirlReturn();
			chrDisableReloadToLocation = false;//открыть локацию
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				AddQuestRecord("GoldenGirl", "16");
				AddQuestUserData("GoldenGirl", "sName", sld.name);
				CloseQuestHeader("GoldenGirl");
				pchar.questTemp.GoldenGirl = "end";
			}
			else 
			{
				AddQuestRecord("GoldenGirl", "21");
				AddQuestUserData("GoldenGirl", "sName", sld.name);
				SetFunctionTimerCondition("GoldenGirl_CortnySPFinal", 0, 0, 8, false);
				pchar.quest.goldengirl_cortny_sp.win_condition.l1 = "location";
				pchar.quest.goldengirl_cortny_sp.win_condition.l1.location = "FortFrance_SecBrRoom";
				pchar.quest.goldengirl_cortny_sp.function = "GoldenGirl_CortnySPFinalAdd";
			}
		break;
		
		case "GoldenGirl_BandosAfterFight": //
			sld = characterFromId("Cortny");
			if (LAi_GetCharacterHP(sld) < 1)
			{
				sld = characterFromId("Julianna");
				sld.dialog.currentnode = "Julianna_78";
				LAi_CharacterEnableDialog(sld);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				sTemp = sld.name;
				AddQuestRecord("GoldenGirl", "19");
				AddQuestUserData("GoldenGirl", "sName", sTemp);
			}
			else
			{
				sld.dialog.currentnode = "Cortny_19";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "GoldenGirl_MercenAfterFight": //
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			LAi_group_Delete("EnemyFight");
			sld = characterFromId("Cortny");
			if (LAi_GetCharacterHP(sld) < 1)
			{
				sld = characterFromId("Julianna");
				sld.dialog.currentnode = "Julianna_78";
				LAi_CharacterEnableDialog(sld);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				sTemp = sld.name;
				AddQuestRecord("GoldenGirl", "19");
				AddQuestUserData("GoldenGirl", "sName", sTemp);
			}
			else
			{
				sld = characterFromId("Julianna");
				sld.dialog.currentnode = "Julianna_115";
				LAi_CharacterEnableDialog(sld);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "GoldenGirl_CortnyPassenger": //
			sld = characterFromId("Cortny");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			chrDisableReloadToLocation = false;
			// перемещаем корабль Шиво на Доминику и даем ноду его кэпу
			Group_SetAddress("GG_AngerranGroup", "Dominica", "quest_ships", "quest_ship_1");
			sld = characterFromId("GG_AngerranCap");
			sld.Dialog.Filename = "Quest\GoldenGirl.c";
			sld.dialog.currentnode = "Cap_Nayad";
			sld.DeckDialogNode = "Cap_Nayad_3";
			LAi_SetImmortal(sld, true);
			sld.AlwaysFriend = true;
			sld.ShipEnemyDisable  = true;
			pchar.quest.goldengirl_dominica_cortny.win_condition.l1 = "location";
			pchar.quest.goldengirl_dominica_cortny.win_condition.l1.location = "Dominica";
			pchar.quest.goldengirl_dominica_cortny.function = "GoldenGirl_DominicaCortny";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "20");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
		break;
		
		case "GoldenGirl_DominicaCortnyFinal": // завершение варианта Кортни на Доминике
			pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
			chrDisableReloadToLocation = true;//закрыть локацию
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			Group_DeleteGroup("GG_AngerranGroup");
			sld = characterFromId("GG_AngerranCap");
			sld.lifeday = 0;
			sld = characterFromId("Cortny");
			RemovePassenger(pchar, sld);
			int iCrew = makeint(sti(pchar.Ship.Crew.Quantity)*0.67); 
			SetCrewQuantityOverMax(pchar, iCrew); // сносим треть команды
			setCharacterShipLocation(pchar, "shore27"));
			setWDMPointXZ("shore27"); // корабль на рейд
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "GoldenGirl_24";
			ChangeCharacterAddressGroup(sld, "shore27", "goto", "goto14");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			pchar.questTemp.GoldenGirl = "cortny_fin";
		break;	
		
		case "GoldenGirl_SPFinal": // завершение варианта Кортни в Сен-Пьер
			chrDisableReloadToLocation = false;
			sld = characterFromId("FortFrance_Hostess");
			ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "barmen", "stay");
			sld = characterFromId("Cortny");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("GoldenGirl");
			pchar.questTemp.GoldenGirl = "end";
			// черная жемчужина - установить картинку
			sld = ItemsFromID("Reserve_item_02");
			sld.picTexture = "ITEMS_40";
			sld.picIndex = 3;
			sld.Weight = 0.2;
			sld.price = 20000;
			sld.name = "itmname_blackpearl";
			ChangeItemDescribe("Reserve_item_02", "itmdescr_blackpearl");
			GiveItem2Character(pchar, "Reserve_item_02");
		break;
		
		case "GoldenGirl_ReloadToBaster": //
			pchar.quest.GoldenGirl_GirlDominicaFail.over = "yes"; //снять прерывание
			SetLaunchFrameFormParam("Прошло несколько дней..."+ NewStr() +"Вы с баронетом Кортни прибыли на Гваделупу", "", 0, 5);
			WaitDate("", 0, 0, 3, 2, 10); 
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			DoQuestCheckDelay("GoldenGirl_ReloadToBasterGo", 5.0);
		break;
		
		case "GoldenGirl_ReloadToBasterGo": //
			DoQuestReloadToLocation("Baster_Townhall", "goto", "goto1", "GoldenGirl_CortnyBaster");
		break;
		
		case "GoldenGirl_CortnyBaster": //
			setCharacterShipLocation(pchar, "Baster_town"));
			setWDMPointXZ("Baster_town"); // корабль на рейд
			sld = characterFromId("Cortny");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "GoldenGirl_BasterReloadJail": //
			pchar.questTemp.jailCanMove = true; //разрешить пройти мимо стражи
			DoQuestReloadToLocation(pchar.location, "goto", "goto23", "GoldenGirl_BasterFinal");
		break;
		
		case "GoldenGirl_BasterFinal": //
			bDisableCharacterMenu = false;
			chrDisableReloadToLocation = false;
			sld = characterFromId("FortFrance_Hostess");
			ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "barmen", "stay");
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Helper")) // belamour целый час бился, какого ... не видит условие
			{
				sld = characterFromID("Julianna");
				AddPassenger(pchar, sld, false);//добавить пассажира
				SetCharacterRemovable(npchar, false);
			}
			pchar.quest.goldengirl_martinique.win_condition.l1 = "location";
			pchar.quest.goldengirl_martinique.win_condition.l1.location = "FortFrance_town";
			pchar.quest.goldengirl_martinique.function = "GoldenGirl_OnMartinique";
			pchar.questTemp.GoldenGirl = "martinique";
		break;
		
		case "GoldenGirl_SPGirlReturn": //
			GoldenGirl_GirlReturn();
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("GoldenGirl", "25");
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			CloseQuestHeader("GoldenGirl");
			AddQuestRecordInfo("Letter_Portugal", "1");
			pchar.questTemp.GoldenGirl = "end";
			pchar.questTemp.GoldenGirl.Angerran = "true"; // Шиво еще вернется fix 02-04-20
		break;
		
		/// Jason ----------------------------------------------------------- Долго и счастливо ------------------------------------------------------------------
		
		case "LongHappy_GirlNorm": //
			chrDisableReloadToLocation = false;//открыть локацию
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = characterFromId("Helena");
				sld.dialog.currentnode = "Helena_officer";
			}
			else 
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "Mary_officer";
			}
			LAi_SetOfficerType(sld);
		break;	
		
		case "LongHappy_MarryInit": //
			chrDisableReloadToLocation = true;//закрыть локацию
			bDisableCharacterMenu = true;//лочим F2
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			pchar.GenQuest.CantRun = true;
			CheckAndSetOverloadMode(GetMainCharacter()); // бег запрещаем
			pchar.GenQuest.FrameLockEsc = true; // блокировать Esc
			// запустим музыку
			DoQuestFunctionDelay("LongHappy_MarryMusic", 1.2);
			// очистим церковь
			for(i=0; i<MAX_LOCATIONS; i++)
			{	
				sld = &characters[i];
				if (sld.location == "FortFrance_church" && CheckAttribute(sld, "CityType")) ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			// оденем ГГ в мундир, если он есть, либо снимем кирасу
                        if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
                        // <--- belamour всегда снимаем мушкет, если какие либо операции с кирасам
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			if (CheckCharacterItem(pchar, "suit1")) EquipCharacterbyItem(pchar, "suit1");
			LAi_SetActorType(pchar);
			// убираем попа и ставим Бенуа в центр
			sld = characterFromId("FortFrance_Priest");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_22";
			ChangeCharacterAddressGroup(sld, "FortFrance_church", "barmen", "bar1");
			// ставим невесту
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_20";
			ChangeCharacterAddressGroup(sld, "FortFrance_church", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "girl", "LongHappy_MarryContinue", -1);
			// ставим гостей
			// патер ГГ
			sld = characterFromId(pchar.questTemp.LongHappy.Pater2);
			sld.dialog.currentnode = "LongHappyPater2";
			ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "pater2");
			LAi_SetStayType(sld);
			// патер невесты
			sld = characterFromId(pchar.questTemp.LongHappy.Pater1);
			sld.dialog.currentnode = "LongHappyPater1";
			ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "pater1");
			LAi_SetStayType(sld);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) // фиксированные для Элен
			{
				// Свенсон
				sld = characterFromId("Svenson");
				sld.Dialog.Filename = "Quest\LongHappy.c";
				sld.dialog.currentnode = "Svenson";
				// Глэдис
				sld = characterFromId("Gladis");
				sld.Dialog.Filename = "Quest\LongHappy.c";
				sld.dialog.currentnode = "Gladis";
				ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "gladys");
				LAi_SetStayType(sld);
				if (pchar.questTemp.LongHappy.Pater2 == "Fadey") 
				{
					sld = characterFromId("Fadey"); // патер ГГ
					sld.Dialog.Filename = "Quest\LongHappy.c";
					sld.dialog.currentnode = "fadey";
					// Пуанси либо Форже
					if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) 
					{
						sld = characterFromId("Noel");
						sld.dialog.currentnode = "forge_5"; // гость
					}
					else 
					{
						sld = characterFromId("Puancie");
						sld.dialog.currentnode = "puancie_4"; // гость
					}
					sld.Dialog.Filename = "Quest\LongHappy.c";
					ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "governor");
					LAi_SetStayType(sld);
				}
				else
				{
					// Фадей гость
					sld = characterFromId("Fadey");
					sld.Dialog.Filename = "Quest\LongHappy.c";
					sld.dialog.currentnode = "fadey_3";
					ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "governor");
					LAi_SetStayType(sld);
					// Пуанси либо Форже
					if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) 
					{
						sld = characterFromId("Noel");
						sld.Dialog.Filename = "Quest\LongHappy.c"; // 28-03-20
						sld.dialog.currentnode = "forge_3"; // патер
					}
					else 
					{
						sld = characterFromId("Puancie");
						sld.Dialog.Filename = "Quest\LongHappy.c"; // 28-03-20
						sld.dialog.currentnode = "puancie_2"; // патер
					}
				}
			}
			else // фиксированные для Мэри
			{
				// Пуанси либо Форже
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) 
				{
					sld = characterFromId("Noel");
					sld.dialog.currentnode = "forge"; // патер
				}
				else 
				{
					sld = characterFromId("Puancie");
					sld.dialog.currentnode = "puancie"; // патер
				}
				sld.Dialog.Filename = "Quest\LongHappy.c";
				sld = characterFromId("Fadey"); // патер ГГ
				sld.Dialog.Filename = "Quest\LongHappy.c";
				sld.dialog.currentnode = "fadey";
				// при свадьбе в Сен-Пьер
				if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) 
				{
					sld = characterFromId("Jino");
					sld.Dialog.Filename = "Quest\LongHappy.c";
					sld.dialog.currentnode = "Jino_7";
					ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "gladys");
					LAi_SetStayType(sld);
				}
			}
			// общие для обоих
			// губернаторы
			sld = characterFromId("FortFrance_Mayor");
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "FortFrance_Mayor";
			ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "mayor1");
			LAi_SetStayType(sld);
			sld = characterFromId("BasTer_Mayor");
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "BasTer_Mayor";
			ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "mayor2");
			LAi_SetStayType(sld);
			sld = characterFromId("PortPax_Mayor");
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "PortPax_Mayor";
			ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "mayor4");
			LAi_SetStayType(sld);
			sld = characterFromId("Tortuga_Mayor");
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "Tortuga_Mayor";
			ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "mayor3");
			LAi_SetStayType(sld);
			// Дойли
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "end" && ChangeCharacterHunterScore(Pchar, "enghunter", 0) < 1)
			{
				sld = characterFromId("PortRoyal_Mayor");
				sld.Dialog.Filename = "Quest\LongHappy.c";
				sld.dialog.currentnode = "PortRoyal_Mayor";
				ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "mayor5");
				LAi_SetStayType(sld);
			}
			// Проспер
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql") && !CheckAttribute(pchar, "questTemp.FMQL.ProsperDead"))
			{
				sld = GetCharacter(NPC_GenerateCharacter("LH_Prosper", "Prospero_mush", "man", "man", 30, FRANCE, 1, false, "soldier"));
				sld.name = "Проспер";
				sld.lastname = "Трубаль";
				sld.Dialog.Filename = "Quest\LongHappy.c";
				sld.dialog.currentnode = "Prosper";
				ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "prosper");
				LAi_SetStayType(sld);
			}
			// Тичингиту
			if (GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu"); // fix 01-04-20 снятие мушкета убираем
				sld.Dialog.Filename = "Quest\LongHappy.c";
				sld.dialog.currentnode = "Tichingitu";
				ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "tich");
				LAi_SetStayType(sld);
			}
		break;
		
		case "LongHappy_MarryContinue": //
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "charles", "LongHappy_MarryContinue1", -1);
		break;
		
		case "LongHappy_MarryContinue1": //
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Benua");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		//--> -------- блок празднования в таверне Сен-Пьер -------------------
		case "LongHappy_InSPtavern": //
			pchar.questTemp.LongHappy.Count = 0; // не нужно, но чтобы не выводило ошибок
			// вычистим всех НПС
			for(i=0; i<MAX_LOCATIONS; i++)
			{	
				sld = &characters[i];
				if (sld.location == "FortFrance_tavern" && CheckAttribute(sld, "CityType"))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
					sld.lifeday = 0;
				}
				if (sld.location == "FortFrance_tavern" && sld.greeting == "officer_hire")
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
					sld.lifeday = 0;
				}
			}
			// рассадим матросню для антуражу
			for (i=1; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("LH_sailor_"+i, "citiz_"+(rand(9)+31), "man", "man", 20, FRANCE, 1, false, "soldier"));
				SetFantomParamFromRank(sld, 20, true);
				sld.Dialog.Filename = "Quest\LongHappy.c";
				sld.dialog.currentnode = "sailor";
				sld.greeting = "habitue";
				LAi_SetSitType(sld);
				sld.City = "FortFrance";
				sld.CityType = "citizen";
				sTemp = PlaceCharacter(sld, "sit", "random_free");
                ReSitCharacterOnFree(sld, "FortFrance_tavern", sTemp);
			}
			// меняем диалог тавернщику
			sld = characterFromId("FortFrance_tavernkeeper");
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "tavernkeeper";
			// Мэри
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_38";
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "waitress", "stay2");
			LAi_SetCitizenType(sld);
			// установим офицеров
				// офицер гамбита
				if (CheckAttribute(pchar, "questTemp.HWIC.Detector"))
				{
					if (pchar.questTemp.HWIC.Detector == "holl_win" && GetCharacterIndex("Longway") != -1) 
					{
						sld = characterFromId("Longway");
						sld.dialog.currentnode = "Longway";
					}
					if (pchar.questTemp.HWIC.Detector == "eng_win" && GetCharacterIndex("Knippel") != -1) 
					{
						sld = characterFromId("Knippel");
						sld.dialog.currentnode = "Knippel";
					}
					if (pchar.questTemp.HWIC.Detector == "self_win" && GetCharacterIndex("Tonzag") != -1)
					{
						sld = characterFromId("Tonzag");
						sld.dialog.currentnode = "Tonzag";
					}
					pchar.questTemp.LongHappy.HambitOfficer = sld.id;
					sld.Dialog.Filename = "Quest\LongHappy.c";
				ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "goto", "goto2");
				LAi_SetActorType(sld);
				}
				// Бейкер
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					sld.Dialog.Filename = "Quest\LongHappy.c";
					sld.dialog.currentnode = "Baker";
				ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "tables", "stay3");
				LAi_SetActorType(sld);
			}
			// Тичингиту
			if (GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu"); // fix 01-04-20 снятие мушкета убираем
				LAi_CharacterEnableDialog(sld);
				sld.Dialog.Filename = "Quest\LongHappy.c";
				sld.dialog.currentnode = "Tichingitu_18";
				ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "goto", "goto1");
				LAi_SetActorType(sld);
			}
			// Джино
			sld = characterFromId("Jino");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "Jino_9";
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "tables", "stay4");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); // запускаем с Джино
		break;
		
		case "LongHappy_InSPcabin": //
			// нормализуем таверну Сен-Пьер
			for (i=1; i<=10; i++)
			{
				sld = characterFromId("LH_sailor_"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			// тавернщик
			sld = characterFromId("FortFrance_tavernkeeper");
			sld.Dialog.Filename = "Common_Tavern.c";
			sld.dialog.currentnode = "First time";
			// Джино
			sld = characterFromId("Jino");
			sld.Dialog.Filename = "Quest\HollandGambit\Jino.c";
			sld.dialog.currentnode = "First time";
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room", "goto", "goto1");
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
			// Бейкер
			if (GetCharacterIndex("Baker") != -1)
			{
				sld = characterFromId("Baker");
				ChangeCharacterAddressGroup(sld, "none", "", "");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Saga\Baker.c";
				sld.dialog.currentnode = "Baker_officer";
			}
			// офицер Гамбита
			if (CheckAttribute(pchar, "questTemp.LongHappy.HambitOfficer"))
			{
				sld = characterFromId(pchar.questTemp.LongHappy.HambitOfficer);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				LAi_SetOfficerType(sld);
				if (pchar.questTemp.LongHappy.HambitOfficer == "Longway") sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
				if (pchar.questTemp.LongHappy.HambitOfficer == "Knippel") sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
				if (pchar.questTemp.LongHappy.HambitOfficer == "Tonzag") sld.Dialog.Filename = "Quest\HollandGambit\Tonzag.c";
				sld.dialog.currentnode = sld.id+"_officer";
			}
			// Тичингиту
			if (GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.dialog.currentnode = "Tichingitu_officer";
				ChangeCharacterAddressGroup(sld, "none", "", "");
				LAi_SetOfficerType(sld);
			}
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_59";
			ChangeCharacterAddressGroup(sld, "My_Cabin", "rld", "aloc1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "LongHappy_InSPComplete": //
			chrDisableReloadToLocation = false;
			iTime = sti(environment.time);
			if (iTime >= 21) iAddTime = 24 - iTime + 12;
			if (iTime < 7) iAddTime = 12 - iTime;
			if (iTime >= 7 && iTime < 21) iAddTime = 24  + 12 - iTime;
			StoreDayUpdate();
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			CloseQuestHeader("LongHappy");
			pchar.questTemp.LongHappy = "end";
		break;
		//<-- блок празднования в таверне Сен-Пьер
		
		case "LongHappy_IslaTesoroTavern": //
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			// вычистим всех НПС
			for(i=0; i<MAX_LOCATIONS; i++)
			{	
				sld = &characters[i];
				if (sld.location == "Pirates_tavern" && CheckAttribute(sld, "CityType"))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
					sld.lifeday = 0;
				}
				if (sld.location == "Pirates_tavern" && sld.greeting == "officer_hire")
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
					sld.lifeday = 0;
				}
			}
			// fix 25-03-20 уберем Элен из резиденции, если жена - Мэри
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (GetCharacterIndex("Helena") != -1)
				{
					sld = characterFromId("Helena");
					ChangeCharacterAddressGroup(sld, "Minentown_tavern", "waitress", "stay1"); // fix 01-04-20
				}
			}
			pchar.questTemp.LongHappy.Count = 0;
			pchar.questTemp.LongHappy.CountNeed = 6;
			if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry")) 
			// ставим жену ГГ
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_38";
			ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "waitress", "barmen");
			LAi_SetCitizenType(sld);
			RemovePassenger(pchar, sld); // выводим ее из офицеров
			// Даниэль Хоук встречает
			sld = characterFromId("Danielle");
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "Danielle";
			LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
			ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "tables", "stay1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			// Свенсон бармен
			sld = characterFromId("Svenson");
			sld.Dialog.Filename = "Quest\LongHappy.c";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld.dialog.currentnode = "Svenson_2";
			else sld.dialog.currentnode = "Svenson_7";
			ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "barmen", "stay");
			LAi_SetBarmanType(sld);
			// Тиракс
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "Terrax_3";
			ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit10"); // определить локаторы для всех гостей
			LAi_SetSitType(sld);
			// Натаниэль Хоук
			sld = characterFromId("Nathaniel");
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "Nathaniel";
			ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit_base1");
			LAi_SetSitType(sld);
			// Додсон или Венсан
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				sld = characterFromId("Dodson");
				sld.dialog.currentnode = "Dodson";
				LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
			}
			else
			{
				if (GetCharacterIndex("Vensan") == -1)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Vensan", "Vensan", "man", "man", 30, PIRATE, -1, true, "quest"));
					sld.name = "Бернар";
					sld.lastname = "Венсан";
				}
				else sld = characterFromId("Vensan");
				sld.dialog.currentnode = "Vensan";
					FantomMakeCoolFighter(sld, 35, 70, 70, "blade_21", "pistol5", "bullet", 250);
					LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
			}
			sld.Dialog.Filename = "Quest\LongHappy.c";
			ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit1");
			LAi_SetSitType(sld);
			// Джино
			sld = characterFromId("Jino");
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "Jino";
			ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit5");
			LAi_SetSitType(sld);
			// Тичингиту
			if (GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu"); // fix 01-04-20 снятие мушкета убираем
				sld.Dialog.Filename = "Quest\LongHappy.c";
				sld.dialog.currentnode = "Tichingitu_2";
				ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "tables", "stay3"); // fix 01-04-20
				LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
				LAi_SetStayType(sld); // fix 01-04-20
				pchar.questTemp.LongHappy.CountNeed = sti(pchar.questTemp.LongHappy.CountNeed)+1;
			} 
			// при большой свадьбе
			if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry"))
			{
				// офицер гамбита
				if (CheckAttribute(pchar, "questTemp.HWIC.Detector"))
				{
					if (pchar.questTemp.HWIC.Detector == "holl_win" && GetCharacterIndex("Longway") != -1) 
					{
						sld = characterFromId("Longway");
						sld.dialog.currentnode = "Longway";
						pchar.questTemp.LongHappy.HambitOfficer = sld.id;
						sld.Dialog.Filename = "Quest\LongHappy.c";
						ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit4");
						LAi_SetSitType(sld);
						pchar.questTemp.LongHappy.CountNeed = sti(pchar.questTemp.LongHappy.CountNeed)+1;
					}
					if (pchar.questTemp.HWIC.Detector == "eng_win" && GetCharacterIndex("Knippel") != -1) 
					{
						sld = characterFromId("Knippel");
						sld.dialog.currentnode = "Knippel";
						pchar.questTemp.LongHappy.HambitOfficer = sld.id;
						sld.Dialog.Filename = "Quest\LongHappy.c";
						ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit4");
						LAi_SetSitType(sld);
						pchar.questTemp.LongHappy.CountNeed = sti(pchar.questTemp.LongHappy.CountNeed)+1;
					}
					if (pchar.questTemp.HWIC.Detector == "self_win" && GetCharacterIndex("Tonzag") != -1)
					{
						sld = characterFromId("Tonzag");
						sld.dialog.currentnode = "Tonzag";
					pchar.questTemp.LongHappy.HambitOfficer = sld.id;
					sld.Dialog.Filename = "Quest\LongHappy.c";
					ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit4");
					LAi_SetSitType(sld);
					pchar.questTemp.LongHappy.CountNeed = sti(pchar.questTemp.LongHappy.CountNeed)+1;
				}
				}
				// Бейкер
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					sld.Dialog.Filename = "Quest\LongHappy.c";
					sld.dialog.currentnode = "Baker";
					LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
					ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit9");
					LAi_SetSitType(sld);
					pchar.questTemp.LongHappy.CountNeed = sti(pchar.questTemp.LongHappy.CountNeed)+1;
				}
				// Венсан при Додсоне
				if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
				{
					if (GetCharacterIndex("Vensan") == -1)
					{
						sld = GetCharacter(NPC_GenerateCharacter("Vensan", "Vensan", "man", "man", 30, PIRATE, -1, true, "quest"));
						sld.name = "Бернар";
						sld.lastname = "Венсан";
					}
					else sld = characterFromId("Vensan");
					sld.Dialog.Filename = "Quest\LongHappy.c";
					sld.dialog.currentnode = "Vensan_3";
					FantomMakeCoolFighter(sld, 35, 70, 70, "blade_21", "pistol5", "bullet", 250);
					LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
					ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit7");
					LAi_SetSitType(sld);
					pchar.questTemp.LongHappy.CountNeed = sti(pchar.questTemp.LongHappy.CountNeed)+1;
				}
			}
		break;
		
		case "LongHappy_DannyNorm": //
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_2";
			LAi_SetCitizenType(sld);
		break;
		
		case "LongHappy_BandosInDungeonAfterFight": //
			LAi_group_Delete("EnemyFight");
			DoQuestCheckDelay("hide_weapon", 1.3);
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "Nathaniel_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum") && GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			sld = characterFromId("Pirates_shipyarder");
			ChangeCharacterAddressGroup(sld, "none", "", "");
		break;
		
		case "LongHappy_TavernAfterFight": //
			LAi_group_Delete("EnemyFight");
			DoQuestCheckDelay("hide_weapon", 1.3);
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "Terrax_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "LongHappy_IslaTesoroTownFight": //
			// установить группировку наших пиратов
			for (i=1; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("LH_OurPirate_"+i, "citiz_"+(40+i), "man", "man", 30, PIRATE, 0, false, "soldier"));
				FantomMakeCoolFighter(sld, 30, 55, 55, LinkRandPhrase("blade_07","blade_08","blade_09"), "pistol1", "bullet", 150);
				ChangeCharacterAddressGroup(sld, "Pirates_town", "reload", "houseS1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// установить группировку пиратов Барбазона
			for (i=1; i<=15; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("LH_BarbPirate_"+i, "citiz_4"+(rand(8)+1), "man", "man", 35, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 35, 60, 60, LinkRandPhrase("blade_07","blade_08","blade_09"), "pistol1", "bullet", 180);
				ChangeCharacterAddressGroup(sld, "Pirates_town", "rld", "loc0");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LongHappy_TownAfterFight");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "LongHappy_TownAfterFight": //
			LAi_group_Delete("EnemyFight");
			DoQuestCheckDelay("hide_weapon", 1.3);
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "Nathaniel_12";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			// фикс Бейкера не офицера
			if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry") && GetCharacterIndex("Baker") != -1 && !IsOfficer(characterFromId("Baker")))
			{
				sld = characterFromId("Baker");
				ChangeCharacterAddressGroup(sld, "none", "", "");
				LAi_SetOfficerType(sld);
			}
		break;
		
		case "LongHappy_ResidenceAfterFight": //
			LAi_group_Delete("EnemyFight");
			DoQuestCheckDelay("hide_weapon", 1.3);
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Warrior"))
			{
				pchar.questTemp.LongHappy.Tichingitu_Victim = "true";
				DeleteAttribute(pchar, "questTemp.LongHappy.Tichingitu_Warrior");
			}
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "Nathaniel_15";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "LongHappy_IslaTesoroBedroom": //
			LAi_SetPlayerType(pchar);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran")) sld = characterFromId("Angerran"); // fix 02-04-20
			else sld = characterFromId("LH_Dussak");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_BedroomShot": //
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran")) sld = characterFromId("Angerran"); // fix 02-04-20
			else sld = characterFromId("LH_Dussak");
			LAi_ActorAnimation(sld, "shot", "LongHappy_BedroomShot_1", 1.2);
		break;
		
		case "LongHappy_BedroomShot_1": //
			sld = characterFromId("LH_Victim");
			LAi_KillCharacter(sld);
			LAi_SetPlayerType(pchar);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_7";
			}
			else
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_6";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_BedroomAfterFight": //
			LAi_group_Delete("EnemyFight");
			DoQuestCheckDelay("hide_weapon", 1.3);
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				sld = characterFromId("Nathaniel");
				sld.dialog.currentnode = "Nathaniel_17";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			}
			else
			{
				sld = characterFromId("Danielle");
				sld.dialog.currentnode = "Danielle_7";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			}
		break;
		
		case "LongHappy_FindJinoHurry": //
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			// ставим Натана или жену и в офицеры
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				sld = characterFromId("Nathaniel");
				ChangeCharacterAddressGroup(sld, "Pirates_town", "reload", "reload3"); 
				sld.dialog.currentnode = "Nathaniel_20";
				LAi_SetOfficerType(sld);
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, true);
				sld.CompanionDisable = true;
				sld.loyality = MAX_LOYALITY;
				sld.Payment = true;
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				log_info(""+GetFullName(sld)+" добавлен в вашу команду офицером");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				EquipCharacterbyItem(sld, pchar.questTemp.LongHappy.GBlade);
				EquipCharacterbyItem(sld, pchar.questTemp.LongHappy.GGun);
			}
			else
			{
				sld = characterFromId("Nathaniel");
				LAi_SetLayType(sld);
				ChangeCharacterAddressGroup(sld, "Location_reserve_04", "goto", "goto1"); 
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				ChangeCharacterAddressGroup(sld, "Pirates_town", "reload", "reload3"); 
				sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
				LAi_SetOfficerType(sld);
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, true);
				sld.loyality = MAX_LOYALITY;
				sld.Payment = true;
				sld.CompanionDisable = true;
				sld.dialog.currentnode = "LongHappy_43";
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				SaveCurrentNpcQuestDateParam(sld, "HiredDate");
				EquipCharacterbyItem(sld, pchar.questTemp.LongHappy.GBlade);
				EquipCharacterbyItem(sld, pchar.questTemp.LongHappy.GGun);
				log_info("Вы можете назначить "+GetFullName(sld)+" офицером-абордажником");
			}
			// открыть магазин, порт, комнату таверны, закрыть резиденцию
			LocatorReloadEnterDisable("Pirates_town", "reload1_back", false);
			LocatorReloadEnterDisable("Pirates_town", "reload6_back", false);
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
			LocatorReloadEnterDisable("Pirates_tavern", "reload2_back", false);
			// на море
			pchar.quest.longhappy_isla_hurry.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_hurry.win_condition.l1.location = "Bermudes";
			pchar.quest.longhappy_isla_hurry.function = "LongHappy_SeaBattle";
			// на таверну
			pchar.quest.longhappy_isla_hurry1.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_hurry1.win_condition.l1.location = "Pirates_tavern";
			pchar.quest.longhappy_isla_hurry1.function = "LongHappy_KillersInTavern";
			if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry") && !CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				// на магазин
				pchar.quest.longhappy_isla_hurry2.win_condition.l1 = "location";
				pchar.quest.longhappy_isla_hurry2.win_condition.l1.location = "Pirates_store";
				pchar.quest.longhappy_isla_hurry2.function = "LongHappy_KillersInStore";
			}
		break;
		
		case "LongHappy_StoreAfterFight": //
			LAi_group_Delete("EnemyFight");
			DoQuestCheckDelay("hide_weapon", 0.5);
			LAi_LocationFightDisable(&Locations[FindLocation("Pirates_store")], true);
			sld = characterFromId("Vensan");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		
		case "LongHappy_TavernKillerAfterFight": //
			LAi_group_Delete("EnemyFight");
			DoQuestCheckDelay("hide_weapon", 1.3);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_tavern", "reload1_back", true);
			AddQuestRecord("LongHappy", "17");
			pchar.quest.longhappy_isla_hurry3.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_hurry3.win_condition.l1.location = "Pirates_tavern_upstairs";
			pchar.quest.longhappy_isla_hurry3.function = "LongHappy_FindJinoTavern";
		break;
		
		case "LongHappy_BarbAfterFight": // 
			pchar.GenQuest.CannotReloadBoarding = true; // нельзя перегружаться
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				sld = characterFromId("Nathaniel");
				sld.dialog.currentnode = "Nathaniel_21";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				sld.dialog.currentnode = "LongHappy_44";
			}
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;
		
		case "LongHappy_BarbExit": //
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) pchar.questTemp.LongHappy.Terrax.Free = "true";
			DeleteAttribute(pchar, "GenQuest.CannotReloadBoarding"); // можно выходить
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				sld = characterFromId("Nathaniel");
				sld.dialog.currentnode = "Nathaniel_20";
				LAi_SetOfficerType(sld);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				sld.dialog.currentnode = "LongHappy_43";
				LAi_SetOfficerType(sld);
			}
		break;
		
		case "LongHappy_DannyInResidence": //
			sld = characterFromId("Svenson");
			ChangeCharacterAddressGroup(sld, "Pirates_townhall", "goto", "goto1");
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_11";
			ChangeCharacterAddressGroup(sld, "Pirates_townhall", "goto", "goto4");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "LongHappy_WifeInTown": //
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum")) sld.dialog.currentnode = "LongHappy_52";
			else sld.dialog.currentnode = "LongHappy_49";
			ChangeCharacterAddressGroup(sld, "Pirates_town", "rld", "loc1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim") && !CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died")) LongHappy_SetTichingituDelay(); 
		break;
		
		case "LongHappy_MarryFinalizing": 
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Следующим утром...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("LongHappy_MarryFinalizingReload", 4.0);
        break;
		
		case "LongHappy_MarryFinalizingReload": //
			DoQuestReloadToLocation("Pirates_town", "quest", "quest1", "LongHappy_IslaMarryFinal");
		break;
		
		case "LongHappy_IslaMarryFinal": //
			LongHappy_IslaTesoroClear(); // нормализация города
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto4"); // найти локатор рядом с ГГ
			sld = characterFromId("Svenson");
			ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto8");
			sld.dialog.currentnode = "Svenson_45";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "LongHappy_IslaMarryComplete": //
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			sld = characterFromId("Svenson");
			sld.Dialog.Filename = "Quest\Saga\Svenson.c";
			sld.dialog.currentnode = "First time";
			ChangeCharacterAddressGroup(sld, "Santacatalina_houseS1_residence", "sit", "sit1");
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			LAi_SetImmortal(sld, false);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			LAi_SetOfficerType(sld);
			sld.Payment = true;
			sld.DontClearDead = true;
			sld.dialog.currentnode = sld.id+"_officer";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld.CompanionDisable = true; // fix 25-03-20 блок компаньона у Мэри
			CloseQuestHeader("LongHappy");
			pchar.questTemp.LongHappy = "end";
		break;
	}	
}

// boal -->
////////////////////////   общие методы //////////////////////////
void SetActorDialogAny2Pchar(string _charId, string _doQuest, float time1, float time2)
{
    Pchar.AutoQuest.NPCharId = _charId;
    Pchar.AutoQuest.Quest    = _doQuest;
    Pchar.AutoQuest.Time1    = time1;
    Pchar.AutoQuest.Time2    = time2;
}

//для универсализации (navy 17.10.05)
//уcтановки для телепорта ГГ в любую локацию с задержкой или без. 
//Для отложенного вызова напр. AddDialogExitQuest()
void SetAnyReloadToLocation(string idLocation, string idGroup, string idLocator, string questName, int delayMonth, int delayDay, int delayHour, int delayMin)
{
    ref PChar = GetMainCharacter();

	PChar.AutoQuest.delayMonth	= delayMonth;
	PChar.AutoQuest.delayDay	= delayDay;
	PChar.AutoQuest.delayHour	= delayHour;
	PChar.AutoQuest.delayMin	= delayMin;

	PChar.AutoQuest.idLocation	= idLocation;
	PChar.AutoQuest.idGroup		= idGroup;
	PChar.AutoQuest.idLocator	= idLocator;
	PChar.AutoQuest.questName	= questName;
}

// Инициация таблички В это время на Беде  -->
// _FrameText - текст  Перенос строки делать "текст"+ NewStr() +"текст"
// _FrameQuest - квест после завершения таблички, если == "Reload_To_Location" см. SetLaunchFrameReloadLocationParam
// если же будет == "Run_Function" см. SetLaunchFrameRunFunctionParam
// _delay - время в с. отложения вызова таблички (нужно для неконфликта с заставкой загрузки локаций, где-то 0.1-1.5с)
// _autoEnd - время в с. автозавершения показа таблички, 4-6с на фразу
void SetLaunchFrameFormParam(string _FrameText, string _FrameQuest, float _delay, float _autoEnd)
{
    pchar.AutoQuest.FrameText    = _FrameText;
    pchar.AutoQuest.FrameQuest   = _FrameQuest;
    pchar.AutoQuest.FrameDelay   = _delay;
    pchar.AutoQuest.FrameAutoEnd = _autoEnd;
}

void SetLaunchFrameFormPic(string _FramePic)
{
    pchar.AutoQuest.FramePic    = _FramePic;
}
// метод для инициации перехода после таблички
void SetLaunchFrameReloadLocationParam(string idLocation, string idGroup, string idLocator, string questName)
{
    pchar.AutoQuest.FrameLocation      = idLocation;
    pchar.AutoQuest.FrameGroup         = idGroup;
    pchar.AutoQuest.FrameLocator       = idLocator;
    pchar.AutoQuest.FrameLocationQuest = questName;
}
// метод для вызова метода из кода после таблички _func - метод, _delay - задержка вызова метода после таблички в с.
void SetLaunchFrameRunFunctionParam(string _func, float _delay)
{
    pchar.AutoQuest.FrameFunction      = _func;
    pchar.AutoQuest.FrameFunctionDelay = _delay;
}
// Инициация таблички В это время на Беде  <--

void WaitNextHours(string qName)
{
	string sHour;
	float locx, locy, locz;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	pchar.locx = locx;
	pchar.locy = locy;
	pchar.locz = locz;
	sHour = "Прошло несколько часов...";
	if(sti(pchar.quest.waithours) == 1)		sHour = "Прошел один час...";
	if(sti(pchar.quest.waithours) == 24)	sHour = "Прошли одни сутки...";
	if(isShipInside(pchar.location))
	{
		SetLaunchFrameFormParam(sHour, "", 0.1, 2.0);
	}
	else
	{
		SetLaunchFrameFormParam(sHour, "Reload_To_Location", 0.1, 2.0);
		SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
	}
	
	WaitDate("", 0, 0, 0, sti(pchar.quest.waithours), 0);
	LaunchFrameForm();
	DeleteAttribute(pchar,"quest.waithours");
	RefreshLandTime();
	RecalculateJumpTable();
	Whr_UpdateWeather();
}

void RemovePatent()
{
	RemoveCharacterEquip(pchar, "patent");
    if (CheckCharacterItem(Pchar, "patent_eng"))
    {
        TakeItemFromCharacter(pchar, "patent_eng");
        ChangeCharacterComplexReputation(pchar,"nobility", -10);
    }
    if (CheckCharacterItem(Pchar, "patent_fra"))
    {
        TakeItemFromCharacter(pchar, "patent_fra");
        ChangeCharacterComplexReputation(pchar,"nobility", -10);
    }
    if (CheckCharacterItem(Pchar, "patent_spa"))
    {
        TakeItemFromCharacter(pchar, "patent_spa");
        ChangeCharacterComplexReputation(pchar,"nobility", -10);
    }
    if (CheckCharacterItem(Pchar, "patent_hol"))
    {
        TakeItemFromCharacter(pchar, "patent_hol");
        ChangeCharacterComplexReputation(pchar,"nobility", -10);
    }
}

void StartActorSelfDialog(string _CurrentNode)
{
    LAi_SetActorType(pchar);
    LAi_CharacterSaveAy(pchar);
    locCameraSleep(true);
    if (stf(pchar.chr_ai.type.ay) > 0)
    {
    	CharacterTurnAy(pchar,  -PI + abs(stf(pchar.chr_ai.type.ay)));  // 180 == 1
    }
    else
    {
    	CharacterTurnAy(pchar,  PI - abs(stf(pchar.chr_ai.type.ay)));  // 180 == 1
    }
    pchar.Dialog.CurrentNode = _CurrentNode;
    LAi_ActorSelfDialog(pchar, "pchar_back_to_player");
}

// подъем флагов
void Flag_PIRATE()
{
	PChar.nation	= PIRATE;
	Ship_FlagRefresh(PChar); //флаг на лету
	SetNationToOfficers(PIRATE);
	
	SetNationRelation2MainCharacter(ENGLAND, RELATION_ENEMY);
	SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
	SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
	
	SetNationRelation2MainCharacter(PIRATE, RELATION_FRIEND);
	SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY);
	
	LAi_group_SetRelation("PIRATE_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	//Relation_PIRATE_SOLDIERS();
	// сторожевики Тортуги
	if (pchar.location == "Tortuga" && !CheckAttribute(pchar, "questTemp.Sharlie.DelTerGuard")) Tortuga_ShipGuardAttack();
	// капеллан
	if (CheckAttribute(pchar, "questTemp.ShipCapellan.Yes")) ShipCapellan_Remove();
	// Addon 2016-1 Jason Пиратская линейка
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag"))
	{
		DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal");
		DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag");
		Mtraxx_CorridaIgnasioFailFlag();
	}
	LAi_group_ClearAllTargets();
	DoQuestCheckDelay("NationUpdate", 3.0);
	UpdateRelations();
	if(bSeaActive)
	{
	    RefreshBattleInterface();
	}
	wdmSetNationFlag(sti(pchar.nation));
}            

void Flag_FRANCE()
{
	PChar.nation	= FRANCE;
    Ship_FlagRefresh(PChar); //флаг на лету
    SetNationToOfficers(FRANCE);

    SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(ENGLAND, FRANCE));
    SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
    SetNationRelation2MainCharacter(SPAIN, GetNationRelation(FRANCE, SPAIN));
    SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);

    SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(FRANCE, HOLLAND));

    LAi_group_SetRelation("FRANCE_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL); //LAI_GROUP_FRIEND);
    //Relation_FRANCE_SOLDIERS();
	// Addon 2016-1 Jason Пиратская линейка
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag"))
	{
		DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal");
		DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag");
		Mtraxx_CorridaIgnasioFailFlag();
	}
    LAi_group_ClearAllTargets();
    DoQuestCheckDelay("NationUpdate", 3.0);
    UpdateRelations();
    if(bSeaActive)
    {
        RefreshBattleInterface();
    }
	wdmSetNationFlag(sti(pchar.nation));
}

void Flag_ENGLAND()
{
	PChar.nation	= ENGLAND;
    Ship_FlagRefresh(PChar); //флаг на лету
    SetNationToOfficers(ENGLAND);

	SetNationRelation2MainCharacter(ENGLAND, RELATION_FRIEND);
	SetNationRelation2MainCharacter(FRANCE, GetNationRelation(ENGLAND, FRANCE));
	SetNationRelation2MainCharacter(SPAIN, GetNationRelation(ENGLAND, SPAIN));
	SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);
    SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(ENGLAND, HOLLAND));

    LAi_group_SetRelation("ENGLAND_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
    //Relation_ENGLAND_SOLDIERS();
    LAi_group_ClearAllTargets();
    DoQuestCheckDelay("NationUpdate", 3.0);
    UpdateRelations();
    if(bSeaActive)
    {
        RefreshBattleInterface();
    }
	wdmSetNationFlag(sti(pchar.nation));
}

void Flag_SPAIN()
{
	PChar.nation = SPAIN;
    Ship_FlagRefresh(PChar); //флаг на лету
    SetNationToOfficers(SPAIN);

	SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(ENGLAND, SPAIN));
	SetNationRelation2MainCharacter(FRANCE, GetNationRelation(FRANCE, SPAIN));
	SetNationRelation2MainCharacter(SPAIN, RELATION_FRIEND);
	SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);
    SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(SPAIN, HOLLAND));

    LAi_group_SetRelation("SPAIN_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
    //Relation_SPAIN_SOLDIERS();
	if (pchar.location == "Tortuga" && !CheckAttribute(pchar, "questTemp.Sharlie.DelTerGuard")) Tortuga_ShipGuardAttack();
	// Addon 2016-1 Jason Пиратская линейка
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag"))
	{
		DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal");
		DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag");
		Mtraxx_CorridaIgnasioRightFlag();
	}
    LAi_group_ClearAllTargets();
    DoQuestCheckDelay("NationUpdate", 3.0);
    UpdateRelations();
    if(bSeaActive)
    {
        RefreshBattleInterface();
    }
	wdmSetNationFlag(sti(pchar.nation));
}

void Flag_HOLLAND()
{
	PChar.nation	= HOLLAND;
    Ship_FlagRefresh(PChar); //флаг на лету
    SetNationToOfficers(HOLLAND);

    SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(ENGLAND, HOLLAND));
    SetNationRelation2MainCharacter(FRANCE, GetNationRelation(FRANCE, HOLLAND));
    SetNationRelation2MainCharacter(SPAIN, GetNationRelation(SPAIN, HOLLAND));
    SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);
    SetNationRelation2MainCharacter(HOLLAND, RELATION_FRIEND);

    LAi_group_SetRelation("HOLLAND_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
    //Relation_HOLLAND_SOLDIERS();
    LAi_group_ClearAllTargets();
    DoQuestCheckDelay("NationUpdate", 3.0);
    UpdateRelations();
    if(bSeaActive)
    {
        RefreshBattleInterface();
    }
	wdmSetNationFlag(sti(pchar.nation));
}

void Flag_Rerise()
{
	switch (sti(PChar.nation))
	{
    	case ENGLAND:	Flag_ENGLAND();	break;
    	case FRANCE:	Flag_FRANCE();	break;
    	case SPAIN:		Flag_SPAIN();	break;
    	case PIRATE:	Flag_PIRATE();	break;
    	case HOLLAND:	Flag_HOLLAND();	break;
	}
}