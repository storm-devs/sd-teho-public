
void ActivateTimeEvents()
{

}

//////////////////////// boal SLiB ////////////////////////////////
void SalaryNextDayUpdate()
{
	if (sti(NullCharacter.SalayPayMonth) != GetDataMonth() && !bDisableMapEnter) // boal
	{
		// проверка на наличие кому платить -->
		int nPaymentQ = 0;
		int i, cn;
		ref chref;
		
		for (i=0; i<COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(pchar, i);
			if (cn >= 0)
			{
				chref = GetCharacter(cn);
				if (GetRemovable(chref)) // считаем только своих, а то вских сопровождаемых кормить!!!
				{
					nPaymentQ += GetSalaryForShip(chref);
				}
			}
		}
		
		// проверка на наличие кому платить <--
		NullCharacter.SalayPayMonth = GetDataMonth(); // boal
		if (nPaymentQ > 0)
		{
			if( CheckAttribute(pchar,"CrewPayment") )
			{
				nPaymentQ += makeint(pchar.CrewPayment); // а тут помним все до копейки!
			}
			if( CheckAttribute(pchar,"Partition.MonthPart") )
			{
				nPaymentQ += makeint(pchar.Partition.MonthPart); // доля за месяц
				DeleteAttribute(pchar,"Partition.MonthPart")
			}
			
			pchar.CrewPayment = nPaymentQ;
			LaunchMoneyGraphCollect();
			
			if (!dialogRun && !bQuestCheckProcessFreeze && !bAbordageStarted) // можно показать
			{
				LaunchSalaryScreen("");
			}
			else
			{
				Pchar.quest.LaunchSalaryScreen.win_condition.l1 = "MapEnter";
				PChar.quest.LaunchSalaryScreen.win_condition    = "LaunchSalaryScreen";
				PChar.quest.LaunchSalaryScreen.function         = "LaunchSalaryScreen";
			}
		}
	}
}

#event_handler("EvSituationsUpdate","WorldSituationsUpdate");
void WorldSituationsUpdate()
{
	int 	iStep = GetEventData();
	float 	dayRandom;

	switch(iStep)
	{
		case 0:		
			DailyEatCrewUpdate();
		
            DeleteAttribute(pchar, "SkipEshipIndex");// boal
			Log_QuestInfo("WorldSituationsUpdate DailyEatCrewUpdate");
			
			dayRandom = Random();
			PChar.DayRandom = dayRandom;
			Log_TestInfo("dayRandom == " + dayRandom);

			CheckCharactersUpdateItems();
						
			if (CheckAttribute(pchar, "questTemp.LSC")) 
			{ //Jason: еженедельное обновление паролей кланов LSC и ежедневное вытирание
				if (GetDataDay() == 7 || GetDataDay() == 14 || GetDataDay() == 21 || GetDataDay() == 28)
				{
					sNrvParol = UpdateLSCClanParol();
					sRvdParol = UpdateLSCClanParol();
					if (CheckAttribute(pchar, "questTemp.LSC.NParol_bye")) DeleteAttribute(pchar, "questTemp.LSC.NParol_bye");
					if (CheckAttribute(pchar, "questTemp.LSC.RParol_bye")) DeleteAttribute(pchar, "questTemp.LSC.RParol_bye");
				}
				if (CheckAttribute(pchar, "questTemp.LSC.parol_nrv")) DeleteAttribute(pchar, "questTemp.LSC.parol_nrv");
				if (CheckAttribute(pchar, "questTemp.LSC.parol_rvd")) DeleteAttribute(pchar, "questTemp.LSC.parol_rvd");
			} 
			if (CheckAttribute(pchar, "questTemp.Saga.JessOnShip")) 
			{ //Jason: отрицательные явления при наличии на корабле Джессики
				AddCrewMorale(pchar, -5);
				ChangeOfficersLoyality("bad_all", 1);
				AddCharacterHealth(pchar, -2);
			}
			// трем эскадру у Тортуги
			Tortuga_DeleteShipGuard();						
		break;
		
		case 1:			
			SalaryNextDayUpdate();  // зряплата
			Log_QuestInfo("WorldSituationsUpdate SalaryNextDayUpdate");

			if (rand(2) == 0) Norman_ChangeFesivalFace(); // выходки Нормана
			if (GetDataDay() == 5 && CheckAttribute(pchar, "questTemp.OilTrade")) DoQuestFunctionDelay("Oil_SetSergioToMayak", 1.0); // генератор смол
			if (GetDataDay() == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.IslandLock")) // Addon 2016-1 Jason пиратская линейка
			{
				for (int i=0; i<MAX_ISLANDS; i++)
				{				
					if (!CheckAttribute(&Islands[i], "hidden")) Island_SetReloadEnableGlobal(Islands[i].id, true);
				}
			}
			// калеуче - без НИ
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "Start") DoQuestFunctionDelay("Caleuche_StartGo", 1.0);
			
			AchievmentsDayUpdateStart();			
		break;
		
		case 2:				
			// Jason: ежедневная переустановка сторожевиков Тортуги
			Tortuga_SetShipGuard();
			ProcessHullDecrease();	// учет безвозвратной убыли корпуса
			ProcessDayRepair();
			
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince"))
			{
				if (GetDataDay() == 5 || GetDataDay() == 10 || GetDataDay() == 15 || GetDataDay() == 20 || GetDataDay() == 25 || GetDataDay() == 30)
				{
					ChangeCharacterComplexReputation(pchar, "nobility", -1);
				}
				if (GetDataDay() == 10 || GetDataDay() == 20 || GetDataDay() == 30)
				{
					OfficersReaction("bad");
				}
			}
		break;
		
		case 3:				
			Group_FreeAllDead();

			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.Governor") && GetDataDay() == 15)
			{
				AddMoneyToCharacter(pchar, 100000);
				log_info("You have received your share of profit from Poincy");
			}
			
			// Jason Дороже золота
			if(GetDLCenabled(DLC_APPID_5))
			{	
				if (!CheckAttribute(pchar, "questTemp.GoldenGirl") && CheckAttribute(pchar, "questTemp.Guardoftruth"))
				{
					GoldenGirl_Start();
					log_Testinfo("Стартовал квест Дороже золота");
				}
			}
			// Jason Долго и счастливо
			if(GetDLCenabled(DLC_APPID_5))
			{	
				if (!CheckAttribute(pchar, "questTemp.LongHappy") && LongHappy_CheckCondisiones())
				{
					LongHappy_Start();
					log_Testinfo("Стартовал квест Долго и счастливо");
				}
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.BaronPart") && GetDataDay() == 5)
			{
				LongHappy_GiveBaronPart();
				log_info("Jean David prepared your share in Le Francois");
			}
		break;
		
		case 4:		
			QuestActions(); //eddy				
		break;
		
		case 5:
			wdmEmptyAllOldEncounter();// homo чистка энкоутеров				
		break;
		
		case 6:
			UpdateCrewExp();  // изменение опыта команды	
		break;
		
		case 7:
			UpdateCrewInColonies(); // пересчет наемников в городах	
		break;
		
		case 8:
			if(IsEntity(&worldMap))
			{
				EmptyAllFantomCharacter(); // трем НПС
				wdmEmptyAllDeadQuestEncounter();
			}				
		break;
		
		case 9:		
			UpdateReputation();
		break;
		
		case 10:
			GenerateRumour() //homo 05/07/06			
		break;		
		
	}

	iStep++;
	InterfaceStates.WorldSituationUpdateStep = iStep;

	if(iStep <= 10)
	{
		PostEvent("EvSituationsUpdate", 1000, "l", iStep);
	}
}


//////////////////////////////// начало игры - туториал ////////////////////////////////
void Tut_StartGame(string sQuest)
{
    InterfaceStates.Buttons.Save.enable = false;
	StartQuestMovie(true, true, true);
    SetCharacterTask_None(GetMainCharacter());
    LAi_LockFightMode(Pchar, true);
	PChar.GenQuest.CallFunctionParam = "Tut_Continue";
	DoQuestCheckDelay("CallFunctionParam", 5.0);
	LAi_LocationFightDisable(loadedLocation, true);
	InterfaceStates.Buttons.Save.enable = false;
	DoQuestFunctionDelay("Tut_locCamera_1", 0.1);
}

void Tut_locCamera_1(string _tmp)
{
    locCameraToPos(-5, 2.5, 5.6, false);
    DoQuestFunctionDelay("Tut_locCamera_2", 10.0);
}

void Tut_locCamera_2(string _tmp)
{
    locCameraFollow();
}
void Tut_Continue()
{
    ref sld;
    LAi_LocationFightDisable(loadedLocation, false);
    LAi_SetFightMode(Pchar, false);
    LAi_LockFightMode(pchar, true);
    
	sld = GetCharacter(NPC_GenerateCharacter("Sailor_1", "citiz_31", "man", "man", 1, PIRATE, 0, false, "soldier"));
    sld.name 	= "Сандро";
    sld.lastname 	= "Торн";
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\StartGame_dialog.c";
    sld.greeting = "Teacher_pirat";

    SetSPECIAL(sld, 9,8,10,3,6,10,4);
    InitStartParam(sld);
    SetEnergyToCharacter(sld);

    LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_1");
    GiveItem2Character(sld, "blade_11");
	EquipCharacterByItem(sld, "blade_11");
	// пустоля нет, лечилок нет
    ChangeCharacterAddressGroup(sld, "Ship_deck_Low", "reload", "reload1");
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);

	// генерим второго матроса, но пока не ставим
	sld = GetCharacter(NPC_GenerateCharacter("Sailor_2", "citiz_36", "man", "man", 1, PIRATE, 0, false, "soldier"));
    sld.name 	= "Джим";
    sld.lastname 	= "Хопкинс";

    SetSPECIAL(sld, 8,10,9,3,6,10,4);
    InitStartParam(sld);
    SetEnergyToCharacter(sld);

    LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_2");
    GiveItem2Character(sld, "blade_12");
	EquipCharacterByItem(sld, "blade_12");
	GiveItem2Character(sld, "pistol1");
	EquipCharacterByItem(sld, "pistol1");
		
	AddItems(sld, "bullet", 30);
	AddItems(sld, "gunpowder", 30);
	LAi_SetCharacterUseBullet(sld, "bullet");	
	// лечилок нет
    sld.location = "Ship_deck_Low";  // чтоб не терся, пока его нет
	//раскидаем квестовых нпс по локациям
	//SetQuestsCharacters();	
}

void Tut_RestoreState()
{
	ref sld;
	
	pchar.Health.Damg = 0.0; // здоровье бережем
	pchar.Health.weekDamg = 0.0;

	LAi_SetCurHPMax(pchar);
	LAi_SetCheckMinHP(pchar, 1, true, "Tut_StartGame_CheckMinHP_Hero");
	LAi_SetImmortal(pchar, false);
	
	sld = characterFromID("Sailor_1");
	LAi_SetCurHPMax(sld);
	LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_1");
	LAi_SetImmortal(sld, false);
	
	sld = characterFromID("Sailor_2");
	LAi_SetCurHPMax(sld);
	LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_2");
	LAi_SetImmortal(sld, false);
	
	DeleteAttribute(pchar, "HeroParam.Teach_beat");
}

void Tut_TeachBattle()
{
	ref sld;
	
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(Pchar, true);
	sld = characterFromID("Sailor_1");
	LAi_SetWarriorType(sld);
    LAi_group_MoveCharacter(sld, "TmpEnemy");
	
	if (sti(pchar.HeroParam.Teach_battle) == 2)
	{
        sld = characterFromID("Sailor_2");
		if (!IsEntity(sld))
        {
        	ChangeCharacterAddressGroup(sld, "Ship_deck_Low", "reload", "reload1");
        }
		LAi_SetWarriorType(sld);
	    LAi_group_MoveCharacter(sld, "TmpEnemy");
	}
	LAi_group_SetHearRadius("TmpEnemy", 100.0);
    LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
    LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
}

void Tut_StartDialog()
{
	ref sld = characterFromID("Sailor_1");
	
	if (CheckAttribute(pchar, "HeroParam.Teach_beat"))
	{ // признак, что выиграл
		if (sti(pchar.HeroParam.Teach_beat) == 3)
		{
		    sld.Dialog.CurrentNode = "Teach_battle_win_2";
		}
		else
		{
			if (sti(pchar.HeroParam.Teach_battle) == 1)
			{
				sld.Dialog.CurrentNode = "Teach_battle_win";
			}
			else
			{
			    sld.Dialog.CurrentNode = "Teach_battle_win_3";
			}
		}
	}
	else
	{
		sld.Dialog.CurrentNode = "Teach_battle_lose";
	}
	LAi_ActorWaitDialog(pchar, sld);
	LAi_ActorDialog(sld, pchar, "", 4.0, 0);
}
