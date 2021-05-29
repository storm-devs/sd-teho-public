bool PrepareSiege()
{
    int iColony, iNation, iAtaker, n;
    ref rColony;
    aref aData;
    makearef(aData, NullCharacter.Siege);
    n = 0;
    while (n < 10)
    {
        if (rand(100)<=60) // 40 мало все время испанские колонии осаждают причем одни и те же
        {
            iNation = rand(PIRATE);
            iColony = SelectColonyForSiege(iNation);//ранд нация жертва, сразу ищем город
            if (iColony != -1)
            {
                iAtaker = FindEnemyNation2NationWithoutPirates(iNation);//нашли - ищем атакера по врагу
                if (iAtaker != -1 )
                {
                    makeref(rColony, Colonies[iColony]);
                    aData.nation = iAtaker;
                    aData.conation = sti(rColony.nation);
                    aData.colony = rColony.id;
                    aData.island = rColony.island;
                    Log_TestInfo("рандом "+iColony);
                    return true;
                }
            }
        }
        else
        {
            //ищем жертву по мах городу
            NationForceBalance(aData);
            iNation = func_max_pos(sti(aData.nation_0), sti(aData.nation_1), sti(aData.nation_2), sti(aData.nation_3));
            iColony = SelectColonyForSiege(iNation);
            if (iColony != -1)
            {
                iAtaker = FindEnemyNation2NationWithoutPirates(iNation);//нашли - ищем атакера по врагу
                if (iAtaker != -1 )
                {
                    makeref(rColony, Colonies[iColony]);
                    aData.nation = iAtaker;
                    aData.conation = sti(rColony.nation);
                    aData.colony = rColony.id;
                    aData.island = rColony.island;
                    Log_TestInfo("мочим тех, у кого колоний много ");
                    return true;
                }
            }
        }
        n++;
    }
    return false;
}

int func_max_pos(int a, int b, int c, int d)
{
	if (a >= b && a >= c && a >= d) return 0;
	if (b >= a && b >= c && b >= d) return 1;
	if (c >= a && c >= b && c >= d) return 2;
	if (d >= a && d >= b && d >= c) return 3;
}

bool CheckQuestColonyList(string sColony)
{
    if (CheckAttribute(pchar, "GenQuest.Intelligence.City" ) && pchar.GenQuest.Intelligence.City == sColony) return false;

    if (CheckAttribute(pchar, "GenQuest.Intelligence.MayorId") &&
        characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].City == sColony) return false;
        
	// mitrokosta фикс осад регатных городов
	bool isRegataCity = (sColony == "PortRoyal") || (sColony == "Beliz") || (sColony == "PortPax") || (sColony == "SentJons") || (sColony == "Bridgetown");
	if (CheckAttribute(pchar, "questTemp.Regata") && isRegataCity) {
		return false;
	}
	
    if (CheckAttribute(pchar, "questTemp.State") && pchar.questTemp.State == "EndOfQuestLine") return true;

    if (CheckAttribute(pchar, "questTemp.NationQuest")) // если взята национальная линейка квестов - таковых в ККС нет
    {
        switch(sti(pchar.questTemp.NationQuest))
        {
            case ENGLAND:               
            break;

            case FRANCE:                
            break;
            
            case SPAIN:                
            break;

            case HOLLAND:
            break;
        }
    }
	
    return true;
}

void NationForceBalance(aref base)
{
    string nat;

    base.nation_0 = 0;
    base.nation_1 = 0;
    base.nation_2 = 0;
    base.nation_3 = 0;
    base.nation_4 = 0;

    for (int i=0; i<MAX_COLONIES; i++)
	{
        nat = "nation_"+sti(Colonies[i].nation);
        if (Colonies[i].nation != "none") base.(nat) = sti(base.(nat))+ 1;
	}
	Log_TestInfo("Eng = "+base.nation_0);
	Log_TestInfo("Fra = "+base.nation_1);
	Log_TestInfo("Spa = "+base.nation_2);
	Log_TestInfo("Hol = "+base.nation_3);
	Log_TestInfo("Pir = "+base.nation_4);
}

int SelectColonyForSiege(int ination)  // выбираем колонию для нападения
{
    ref AttakColony;
    int i = 0;
    int j = 0;
    bool bb, aa;
    
    while (i < 20)
    {
        j = rand(MAX_COLONIES-1);
        makeref(AttakColony, Colonies[j]);
        bb = sti(AttakColony.nation) == ination && !CheckAttribute(AttakColony, "HasNoFort");
        aa = CheckAttribute(AttakColony, "FortValue") && sti(AttakColony.HeroOwn) == false;
        if ( bb && aa && CheckQuestColonyList(AttakColony.id))
        {
            return j;
        }
        i++;
    }
    return -1;
}

void BeginSiegeMap(string sChar)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    SiegeRumourEx("They say that local fishers saw a mighty squadron in this area.", aData.Colony, sti(aData.nation)+10, -1, 2, 1, "citizen,habitue,trader,tavern");
    int idist = makeint(GetDistanceToColony(aData.Colony));
    if (idist != -1 && idist <= 100 )
    {
        Log_TestInfo("Squadron on the map!");
        Map_CreateTrader("none", aData.Colony, sChar, 1);
        return;
    }
    else
    {
        Log_TestInfo("Squadron on the Timer");
        aData.progress = -1;
        string sQuest = "BattleOfTheColony";
        SetTimerCondition(sQuest, 0, 0, 2, false);
        pchar.quest.(sQuest).win_condition = "BattleOfTheColony";
        pchar.quest.(sQuest).function= "BattleOfTheColony";
    }
}

float GetDistanceToColony(string sColony);
{
    if (!IsEntity(loadedLocation))
    {
        int iCnum = FindColony(sColony);
		string sIsland = Colonies[iCnum].island;
		string sTemp = sColony+"_town";
		
        return GetDistance2D(stf(worldMap.playerShipX), stf(worldMap.playerShipZ),
                            stf(worldMap.islands.(sIsland).(sTemp).position.x),
                            stf(worldMap.islands.(sIsland).(sTemp).position.z));
    }
    else
    {
        int locnum = FindLocation(pchar.location);
        if (locnum != -1 && CheckAttribute(locations[locnum], "townsack") )
        {
            if (sColony == locations[locnum].townsack)
            return makefloat(0);
        }
    }
    return makefloat(-1);
}

void EndSiegeMap()
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sHead = FillSquadronGoods();
    Map_CreateTrader(aData.Colony, colonies[FindNonEnemyColonyForNation(sti(aData.nation), true)].id, sHead, 4);
    string sQuest = "ClearSiege";
    SetTimerCondition(sQuest, 0, 0, 5, false);
    pchar.quest.(sQuest).win_condition = "ClearSiege";
    pchar.quest.(sQuest).function= "SiegeClear";
    //--> слухи
    SiegeRumourEx("They say that the squadron responsible for pillaging our city is still not far away. I wish there were some brave captain who would risk to attack them back.", aData.Colony, sti(aData.conation), -1, 5, 3, "citizen,habitue,trader,tavern");
    //<-- слухи
}

string FillSquadronGoods()
{
    aref aData;
    ref rchar;

    makearef(aData, NullCharacter.Siege);
    Group_FreeAllDead();
    string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";

    ref rGroup = Group_GetGroupByID(sGroup);
    rGroup.Task = AITASK_MOVE;
    rchar = Group_GetGroupCommander(sGroup);
    return rchar.id;
}

int MakeSiegeSquadron(int ination)
{
    ref sld;
    aref aData;
    bool btmp = false;
    string sCapId = NationShortName(ination)+"SiegeCap_";
    string sGroup = "Sea_" + sCapId + "1";
    makearef(aData, NullCharacter.Siege);
    aData.iSquadronPower = 0;
    int itmp = 0;
    
    Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);

    aData.ishipcount = 5 + rand(2);
    aData.imanofwars = rand(1);
    if (sti(aData.imanofwars) < 0) aData.imanofwars = 0;
    int icon = sti(aData.ishipcount);
    for (int i = 1; i <= icon; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", 5, ination, 30, true, "officer"));

        sld.dialog.filename = "Capitans_dialog.c";
	    sld.dialog.currentnode = "Siegehelp";
	    sld.DeckDialogNode = "Siegehelp";

        itmp = SetSiegeShip(sld);
        aData.iSquadronPower = sti(aData.iSquadronPower) + itmp;
        SetFantomParamHunter(sld); //крутые парни
        SetCaptanModelByEncType(sld, "war");
        sld.mapEnc.type = "war";
        sld.mapEnc.worldMapShip = Nations[ination].worldMapShip+"_manowar";
        sld.mapEnc.Name = "эскадра военных кораблей";
        Group_AddCharacter(sGroup, sCapId + i);
        if (i == 1) SetRandGeraldSail(sld, sti(sld.Nation)); // homo Гербы
    }
    aData.iSquadronPower = sti(aData.iSquadronPower) - 19;
    Log_TestInfo("Squadron Power: "+aData.iSquadronPower+"%");
    Log_TestInfo("Colony Power: "+sti(colonies[FindColony(aData.colony)].FortValue)+"%");
    
    Group_SetGroupCommander(sGroup, sCapId+ "1");
    ref rGroup = Group_GetGroupByID(sGroup);
    rGroup.Task = AITASK_MOVE;
    
    return sti(aData.iSquadronPower);
}


int SetSiegeShip(ref rChar)
{
    int SiegeShips, hcrew, rez;
	int Nation = sti(rChar.nation);
    aref aData;
    makearef(aData, NullCharacter.Siege);

    if (sti(aData.imanofwars) > 0)
    {
		switch (Nation)
		{	
			case PIRATE   :	SiegeShips = SHIP_LINESHIP; 													 break; 
			case ENGLAND  : SiegeShips = RandFromThreeDight(SHIP_LINESHIP, SHIP_LSHIP_ENG,  SHIP_LINESHIP);  break; 
			case FRANCE	  : SiegeShips = RandFromThreeDight(SHIP_LINESHIP, SHIP_LSHIP_FRA,  SHIP_LINESHIP);  break; 					
			case SPAIN	  : SiegeShips = RandFromThreeDight(SHIP_LINESHIP, SHIP_LSHIP_SPA,  SHIP_LINESHIP);  break; 					
			case HOLLAND  : SiegeShips = RandFromThreeDight(SHIP_LINESHIP, SHIP_LSHIP_HOL,  SHIP_LINESHIP);  break; 
		}
        aData.imanofwars = sti(aData.imanofwars) - 1;
        rez = SiegeShips;
    }
    else
    {
		switch (Nation)
		{	
			case PIRATE   :	SiegeShips = RandFromThreeDight(SHIP_CORVETTE, SHIP_GALEON_H, SHIP_FRIGATE); 	break; 
			case ENGLAND  : SiegeShips = RandFromThreeDight(SHIP_CORVETTE, SHIP_FRIGATE,  SHIP_FRIGATE_H); 	break; 
			case FRANCE	  : SiegeShips = RandFromThreeDight(SHIP_CORVETTE, SHIP_FRIGATE,  SHIP_FRIGATE_H); 	break; 					
			case SPAIN	  : SiegeShips = RandFromThreeDight(SHIP_POLACRE,  SHIP_GALEON_H, SHIP_FRIGATE_H);  break; 					
			case HOLLAND  : SiegeShips = RandFromThreeDight(SHIP_XebekVML, SHIP_FRIGATE,  SHIP_FRIGATE_H);  break; 
		}		
        rez = SiegeShips;
    }

    SetRandomNameToCharacter(rChar);
    SetRandomNameToShip(rChar);
    rChar.Ship.Type = GenerateShipExt(SiegeShips, 1, rChar);
    SetBaseShipData(rChar);
    hcrew = GetMaxCrewQuantity(rChar);
    SetCrewQuantity(rChar, hcrew);
    SetCrewQuantityFull(rChar); // to_do

    DeleteAttribute(rChar,"ship.sails");
    DeleteAttribute(rChar,"ship.masts");
    DeleteAttribute(rChar,"ship.blots");
	DeleteAttribute(rChar,"ship.hulls");
	
    Fantom_SetCannons(rChar, "war");
	Fantom_SetBalls(rChar, "war");
	Fantom_SetGoods(rChar, "war");
	
    return rez;
}

void Siege_DailyUpdate()
{
	int iDays;
    if(!actLoadFlag)
    {
		iDays = GetQuestPastDayParam("Siege_DailyUpdate");
		if (iDays >= 120+rand(60))
		{   trace("CreateSieg!");
	        CreateSiege("");
	        SaveCurrentQuestDateParam("Siege_DailyUpdate");
		}
	}
}

void CreateSiege(string tmp)
{
    SiegeClear("");
    ref rColony;
    aref aData;
    makearef(aData, NullCharacter.Siege);
    
    if (PrepareSiege())
    { 
        aData.progress = 0;
        DeleteAttribute(aData, "loot");
        DeleteAttribute(aData, "PlayerHelpMayor");
        DeleteAttribute(aData, "HelpColony");
        string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";
        Log_TestInfo("CreateSiege "+NationShortName(sti(aData.nation)));
        makeref(rColony, Colonies[FindColony(aData.colony)]);
        MakeSiegeSquadron(sti(aData.nation));
        aData.SiegeHP = Group_GetPowerHP(sGroup);
        //Log_TestInfo
        trace("Attak "+aData.colony);
        //Log_TestInfo
        trace("SiegeHP: "+aData.SiegeHP);
        ClearIslandShips(aData.colony);
        BeginSiegeMap(NationShortName(sti(aData.nation))+"SiegeCap_1");
        aData.isSiege = 1;
    }
}

void SiegeProgress()
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    int i = sti(aData.progress);
    
    switch (i)
    {
        case 0:
	        Log_TestInfo("По карте!");
	        BattleOfTheColony("");
        break;
        
        case 1:
        	SiegeClear("");
        break
        
    }
    i++;
    aData.progress = i;
}

int CheckSquadronInjuri()
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    float maxHP = stf(aData.SiegeHP);
    string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";
    return makeint(Group_GetPowerHP(sGroup)*(100/maxHP));
}

int CheckFortInjuri()
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    ref FC = GetFortCommander(aData.colony);
    float maxCannons = 10;
    if (CheckAttribute(FC, "fort.cannons.quantity"))
    {
    	maxCannons = sti(FC.fort.cannons.quantity);
    }
    if (CheckAttribute(FC, "Fort.Mode") && sti(FC.Fort.Mode) == FORT_DEAD) return 0;
    return makeint(makeint(GetCurrentShipHP(FC)/100)*(100/maxCannons)));
}

void LeaveBattle(string tmp)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sQuest = "SiegeResult";
    pchar.quest.(sQuest).win_condition.l1 = "ExitFromLocation";
    pchar.quest.(sQuest).win_condition.l1.location = aData.island;
    pchar.quest.(sQuest).win_condition = "SiegeResult";
    pchar.quest.(sQuest).function = "SiegeResult";
}

void LeaveTown(string tmp)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sCap = NationShortName(sti(aData.nation))+"SiegeCap_";
    string sGroup = "Sea_"+sCap+"1";
    ref NPChar = Group_GetGroupCommander(sGroup);
    
    AfterTownBattle();  // все, все свободны
    LAi_LoginInCaptureTown(NPChar, false);
    aData.win = 1;
    EndOfTheSiege("End");
    NPChar.location = "";
}

void SiegeResult(string tmp)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    int ifortPower = sti(colonies[FindColony(aData.colony)].FortValue);
    int fortDamage = CheckFortInjuri();
    int SquadronDamage = CheckSquadronInjuri();
    Log_TestInfo("fortDamage: "+ fortDamage);
    Log_TestInfo("SquadronDamage: "+ SquadronDamage);
    aData.win =((ifortPower)*fortDamage < sti(aData.iSquadronPower)*SquadronDamage );
    Log_TestInfo(" Win: "+aData.win);
    
    string sQuest = "LeaveBattle";
    pchar.quest.(sQuest).win_condition.l1 = "location";
    pchar.quest.(sQuest).win_condition.l1.location = aData.island;
    pchar.quest.(sQuest).function= "LeaveBattle";
    CheckGroupCommander("");
}

void CheckGroupCommander(string tmp)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sCap = NationShortName(sti(aData.nation))+"SiegeCap_";
    string sGroup = "Sea_"+sCap+"1";
    ref rchar = Group_GetGroupCommander(sGroup);
    bool bhasCom = false;
    
    if ( !CharacterIsDead(rchar)) return;
    
    int CapNum = sti(aData.ishipcount) + sti(aData.imanofwars);
    
    for(int k = 1; k <= CapNum ; k++)
    {
		if (GetCharacterIndex(sCap+k) != -1 && !CharacterIsDead(CharacterFromID(sCap+k)))
		{
            Group_AddCharacter(sGroup,sCap + k);
            if (!bhasCom)
            {
                Group_SetGroupCommander(sGroup, sCap+k );
                bhasCom = true;
            }
		}
    }
}

void BattleOfTheColony(string tmp)
{
    aref aData;
    ref rColony;
    makearef(aData, NullCharacter.Siege);
    string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";
    
    if (CheckAttribute(PChar, "quest.BattleOfTheColony")) Pchar.quest.BattleOfTheColony.over = "yes";
    CheckGroupCommander("");
    
    makeref(rColony, Colonies[FindColony(aData.Colony)]);
    rColony.DontSetShipInPort = true;
    rColony.Siege = true;
    
    ref FC = GetFortCommander(aData.colony);
    Group_SetTaskMove(sGroup, stf(FC.ship.pos.x), stf(FC.ship.pos.z));
    Group_SetAddress(sGroup, aData.island, "Quest_ships", "reload_fort1_siege");//  to_do

    string sQuest = "EndOfTheSiege";
    int ifort = sti(colonies[FindColony(aData.colony)].FortValue);
    int btime = ifort - sti(aData.iSquadronPower);
    aData.win =(ifort < sti(aData.iSquadronPower));
    int SiegeTime = 14 - makeint((abs(btime))/10);
    aData.SiegeTime = SiegeTime;
    Log_TestInfo("Siege period: "+SiegeTime);
    Log_TestInfo("Win: "+aData.win);
    
    SetTimerCondition(sQuest, 0, 0, SiegeTime, false);
    pchar.quest.(sQuest).win_condition = "EndOfTheSiege";
    pchar.quest.(sQuest).function= "EndOfTheSiege";
    
    sQuest = "LeaveBattle";
    pchar.quest.(sQuest).win_condition.l1 = "location";
    pchar.quest.(sQuest).win_condition.l1.location = aData.island;
    pchar.quest.(sQuest).function= "LeaveBattle";
    
    sQuest = "PlayerKillSquadron";
    pchar.quest.(sQuest).win_condition.l1 = "Group_Death";
    pchar.quest.(sQuest).win_condition.l1.group = sGroup;
    pchar.quest.(sQuest).function= "PlayerKillSquadron";
    
    SaveCurrentQuestDateParam("Siege_Start");
    aData.tmpID1 = SiegeRumourEx("Are you deaf? "+NationNameSK(sti(aData.nation))+" ships are bombing our fort. It may fall anytime and awful thing will start happen.", aData.Colony, sti(aData.nation)+10, -1, sti(aData.SiegeTime)-2, 3, "citizen,habitue,trader,tavern");
    aData.tmpID2 = SiegeRumour("OnSiege_1", "", sti(aData.conation)+10, sti(aData.nation)+10, sti(aData.SiegeTime)-2, 3);
    aData.tmpID3 = SiegeRumour("OnSiege_2", "", sti(aData.nation), -1, sti(aData.SiegeTime)-2, 3);
    aData.tmpID4 = SiegeRumour("OnSiege_3", "!"+aData.Colony, sti(aData.conation), -1, sti(aData.SiegeTime)-2, 3);
}

void PlayerKillSquadron(string tmp)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    Log_TestInfo("Player Kill Squadron!");
    aData.win = 0;
    if (GetNationRelation2MainCharacter(sti(aData.nation))) aData.PlayerHelpMayor = true;
    EndOfTheSiege("End");
}

void  EndOfTheSiege(string tmp)
{
    ref sld;
    int l, f;
    string tmpName;
    
	Log_TestInfo("Siege End");
	
    bool bcapt = false;
    aref aData;
    
    makearef(aData, NullCharacter.Siege);
    
    string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";
    ref rColony = GetColonyByIndex(FindColony(aData.colony));
    int ifortPower = sti(rColony.FortValue);
    int idist = makeint(GetDistanceToColony(aData.Colony));
    
    if(idist == -1 || idist > 60 || tmp != "")
    {
        // чистим слухи
        for (l = 0; l <= 4; l++)
        {
            tmpName = "tmpID"+l;
            if (CheckAttribute(aData, tmpName))
            {
                f = FindRumour(sti(aData.(tmpName)));
                Rumour[f].state = 0;
                DeleteAttribute(aData, tmpName);
            }
        }
        // меняем диалог
        ref comand = Group_GetGroupCommander(sGroup);
        if (!CheckAttribute(comand, "dialog")
        || !CheckAttribute(comand, "dialog")
        || comand.dialog.currentnode != "no_return_02"
        || comand.DeckDialogNode != "no_return_02")
        {
            comand.dialog.currentnode = "First time";
		    comand.DeckDialogNode = "First time";
        }
        // возвращаем мэру обычный диалог
        DeleteAttribute(rColony, "Siege"); //снимаем осаду
        
        if (CheckAttribute(PChar, "quest.EndOfTheSiegeLater.again"))
        {
            DeleteAttribute(Pchar, "quest.EndOfTheSiegeLater.again");
            Pchar.quest.EndOfTheSiegeLater.over = "yes";
        }
        if (CheckAttribute(PChar, "quest.SiegeResult")) Pchar.quest.SiegeResult.over = "yes";
        if (CheckAttribute(PChar, "quest.LeaveBattle")) Pchar.quest.LeaveBattle.over = "yes";
        if (sti(aData.win) == 1)
        {
            aData.loot = 200000+100000*makeint(ifortPower/30);
            Log_TestInfo("Siege loot ="+aData.loot);
            if (CheckSquadronInjuri()>= 70)
            {
                int icon = Group_GetCharactersNum(sGroup);
                ref rgrp = Group_GetGroupByID(sGroup);
                int i, j;
                int qrew;
                
                for (i =0; i < icon; i++)
                {
                    j = Group_GetCharacterIndexR(rgrp, i);
                    if (j != -1) sld = &Characters[j];
                    Fantom_SetGoods(sld, "trade");
                    if (i > 3 && rand(1) == 0)
                    {
                        Group_DelCharacter(sGroup, sld.id);
                        Log_TestInfo(sld.id+" - dead!");
                        DeleteCharacter(sld);
                    }
                    else
                    {
                        if (rand(3)==1)
						{
							sld.ship.masts.mast3 = 1;
						}
                        else
						{
							sld.ship.SP = sti(sld.ship.SP) - 10*(rand(3)+1);
						}
    	                sld.ship.HP = sti(sld.ship.HP) - makeint(sti(sld.ship.HP)/(2+rand(2)));
    	                qrew = GetMaxCrewQuantity(sld);
    	                SetCrewQuantity(sld, qrew - makeint(qrew/(2+rand(1))));
                    }
                }
            }
            EndSiegeMap();
            if (ifortPower <= 60 ) //Решение о взятии колонии себе взвешивается очень тщательно!
            {
                bcapt = (rand(3)==2)
            }
            else
            {  // Если колония важная, то вероятность меньше
               bcapt = sti(aData.iSquadronPower) > ifortPower && rand(abs(ifortPower-60)) == 0 ;
            }
            if (!bWorldAlivePause && bcapt && !CheckAttribute(rColony, "notCaptured"))
            {
                SetCaptureTownByNation(aData.colony, sti(aData.nation))
                
               // SiegeRumour("Сегодня славный день для "+ NationNameGenitive(sti(aData.nation))+" - нам удалось захватить такую важную колонию как "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+"! Весь "+NationNameSK(sti(aData.conation))+"ий гарнизон был перебит, а форт занят нашими войсками и уже снова укреплен!", aData.Colony, sti(aData.nation), -1, 15, 3);
               // SiegeRumour("Говорят, что "+NationNameSK(sti(aData.nation))+"ая эскадра, после длительной осады, захватила "+NationNameSK(sti(aData.conation))+"ую колонию "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+". Теперь "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+" - "+NationNameSK(sti(aData.nation))+"ая колония!", "", sti(aData.conation)+10, sti(aData.nation)+10, 30, 3);
               // SiegeRumour("Поговаривают, что "+NationNamePeople(sti(aData.nation))+" подло напали на нашу колонию "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+" и захватили город!", "", sti(aData.conation), -1, 30, 3);
                //SiegeRumour("Вы слышали новость? Наш доблестный флот отбил у "+ NationNameGenitive(sti(aData.conation))+" богатую колонию "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+". ", ("!"+aData.Colony), sti(aData.nation), -1, 30, 3);
                
            }
            else
            {
                SetNull2StoreMan(rColony)// нулим магазин при захвате города эскадрой
                SetNull2Deposit(aData.colony);// нулим ростовщиков
				SetNull2ShipInStockMan(aData.colony)
                
                SiegeRumourEx("Sad day for "+ NationNameGenitive(sti(aData.conation))+" - we failed to protect our colony. The fort was destroyed by "+NationNameSK(sti(aData.nation))+" ships, and the city was pillaged.", aData.Colony, sti(aData.conation), -1, 15, 3, "citizen,habitue,trader,tavern");
                SiegeRumour("There are rumors that "+NationNameSK(sti(aData.nation))+" captured "+NationNameSK(sti(aData.conation))+" colony "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+". They pillaged the city and sailed away.", "", sti(aData.conation)+10, sti(aData.nation)+10, 30, 3);
                //SiegeRumour("Поговаривают, что "+NationNamePeople(sti(aData.nation))+" внезапно атаковали нашу колонию "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+" и разграбили город, до того как подоспело подкрепление! Затем "+NationNamePeople(sti(aData.nation))+" постыдно ретировались с награбленным.", "!"+aData.Colony, sti(aData.conation), -1, 30, 3);
                SiegeRumour("Heard the news? Our military squadron successfully besieged "+NationNameSK(sti(aData.conation))+" city called "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+". The garrison's resistance was broken but, of course, our forces had to leave. But the prize...", "!"+aData.Colony, sti(aData.nation), -1, 30, 3);
            }
            FortDestroy();// уничтожаем форт
            Group_SetAddressNone(sGroup);
            Log_TestInfo("Siege Finish - Squadron win!");
        }
        else
        {
            SiegeRumourEx("Today we are celebrating! "+NationNameSK(sti(aData.nation))+" attackers were eliminated and the city is safe.", aData.Colony, sti(aData.conation), -1, 15, 3, "citizen,habitue,trader,tavern");
          //  SiegeRumour("Говорят, что "+NationNameSK(sti(aData.nation))+"ая эскадра потерпела поражение при штурме "+NationNameSK(sti(aData.conation))+"ой колонии "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+". Защитники оказались сильней.", "", sti(aData.conation)+10, sti(aData.nation)+10, 30, 3);
            SiegeRumour("They say that "+NationNamePeople(sti(aData.nation))+" suddenly attacked "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+", but reinforcements came just in time! All "+NationNameSK(sti(aData.nation))+" were sunken.", "!"+aData.Colony, sti(aData.conation), -1, 30, 3);
            SiegeRumour("I have heard that our squadron failed to besiege "+NationNameSK(sti(aData.conation))+" colony "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+". It was a long siege but our ships were sunken! Next time, I guess.", "!"+aData.Colony, sti(aData.nation), -1, 30, 3);
            SiegeClear("");
            Log_TestInfo("Siege Finish - Squadron defeat!");
        }
    }
    else
    {
        Log_TestInfo("End Siege Later!");
        string sQuest = "EndOfTheSiegeLater";
        SetTimerCondition(sQuest, 0, 0, 1, true);
        pchar.quest.(sQuest).win_condition = "EndOfTheSiegeLater";
        pchar.quest.(sQuest).function= "EndOfTheSiege";
    }
}

void FortDestroy()
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    int ind = GetCharacterIndex(aData.colony + " Fort Commander");
    ref FC;
    
	if (ind == -1) return;

    FC = &Characters[ind];
    FC.Fort.Mode = FORT_DEAD;
	// data of frot die
	FC.Fort.DieTime.Year = GetDataYear();
	FC.Fort.DieTime.Month = GetDataMonth();
	FC.Fort.DieTime.Day = GetDataDay();
	FC.Fort.DieTime.Time = GetTime();
	Event(FORT_DESTROYED, "l", sti(FC.index));
    Log_TestInfo("FORT_DEAD");
}

void SiegeClear(string tmp)
{
    aref aData;
    ref rColony;
    if (CheckAttribute( NullCharacter, "Siege.Colony"))
    {
        makearef(aData, NullCharacter.Siege);
        makeref(rColony, Colonies[FindColony(aData.Colony)]);
        DeleteAttribute(rColony, "DontSetShipInPort"); //возвращаем жизнь
        DeleteAttribute(rColony, "Siege"); //снимаем осаду
        if (CheckAttribute(PChar, "quest.Union_with_Escadra")) Pchar.quest.Union_with_Escadra.over = "yes";
        if (CheckAttribute(PChar, "quest.BattleOfTheColony")) Pchar.quest.BattleOfTheColony.over = "yes";
        if (CheckAttribute(PChar, "quest.EndOfTheSiege")) Pchar.quest.EndOfTheSiege.over = "yes";
        if (CheckAttribute(PChar, "quest.ClearSiege")) Pchar.quest.ClearSiege.over = "yes";
        if (CheckAttribute(PChar, "quest.LeaveBattle")) Pchar.quest.LeaveBattle.over = "yes";
        if (CheckAttribute(PChar, "quest.SiegeResult")) Pchar.quest.SiegeResult.over = "yes";
        if (CheckAttribute(PChar, "quest.PlayerKillSquadron")) Pchar.quest.PlayerKillSquadron.over = "yes";
        if (CheckAttribute(PChar, "Siege_Start")) DeleteAttribute(PChar, "Siege_Start");
        string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";
        aData.progress = 1;
        Group_SetAddressNone(sGroup);
        Group_DeleteGroup(sGroup);
        aData.isSiege = 0;
    }
}

void SiegeSquadronOnMap(string _chrId)
{
    Group_FreeAllDead();
}

//////////////////////////////СЛУХИ////////////////////////////////////////////
int SiegeRumour(string stext, string sCity, int nation1, int nation2, int terms, int qty)
{
   return SiegeRumourEX(stext, sCity, nation1, nation2, terms, qty, "all")
}

int SiegeRumourEX(string stext, string sCity, int nation1, int nation2, int terms, int qty, string tip)
{
    object tmp;
    
    if (findsubstr(stext, "OnSiege_" , 0) != -1)
	{
		tmp.event = stext;
	}
    else
	{
		tmp.event = "none";
	}
    
    tmp.text = stext;
    tmp.state = qty;//кол-во раз
    tmp.tip = tip;
    tmp.rep = "none";
    if (sCity != "") tmp.City = sCity;
	//10, 11, 12, 13 - исключить эти нации из слухов
    if (nation1 != -1)
    {
        if (nation1 > 5)
        {
	    	tmp.nonation.n1 = nation1 - 10;
	    }
	    else
		{
			tmp.onlynation = nation1; //локализация
		}
	}
	
	if (nation2 != -1 && nation2 > 5)
	tmp.nonation.n2 = nation2 - 10;
	
    tmp.starttime = 0;
    tmp.actualtime = terms; //сроки
    tmp.next = "none";
    return AddRumorR(&tmp);
}

string NationNameSK(int nat)
{
    switch (nat)
    {
        case ENGLAND:
        	return "england";
        break;
        
        case FRANCE:
        	return "france";
        break;
        
        case SPAIN:
        	return "spain";
        break;
        
        case HOLLAND:
        	return "holland";
        break;
    }
}

string SiegeRumourText(int inum)
{
    aref aData;
    string sDays;
    
    makearef(aData, NullCharacter.Siege);
    
    int iDays = sti(aData.SiegeTime) - GetQuestPastDayParam("Siege_Start");
    sDays = iDays+" days";
    
    if (iDays < 5) sDays = iDays+" day";
    if (iDays <= 1 ) sDays = "several hours";
    
    switch (inum)
    {
        case 1:
        	return "They say that "+NationNamePeople(sti(aData.nation))+" have attacked "+NationNameSK(sti(aData.conation))+" colony "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+". They are still fighting, but defenders are low on supplies. They can hold on  for "+sDays+" at most.";
        break;

        case 2:
        	return "There are rumors that our unstoppable fleet is storming "+NationNameSK(sti(aData.conation))+" colony  "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+".  Our enemies are fighting hard, but, most likely, we shall learn who is a victor in "+sDays+".";
        break;
        
        case 3:
        	return ""+NationNamePeople(sti(aData.nation))+" have attacked our colony "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+". Our brave defenders have only "+sDays+" before they will run out of provisions.";
        break;
    }
}