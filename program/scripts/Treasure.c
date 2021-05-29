// клады из ВМЛ

//  Карты сокровищ  ГЕНЕРАТОР -->
string GetIslandForTreasure()
{
	int iNum, m;
	ref Itm;
	aref arDest, arImt;
	string sAttr;
	
	m = 0;
	string sCurIsland = GetCharacterCurrentIslandId(pchar);
	makearef(arDest, NullCharacter.TravelMap.Islands);
	iNum = GetAttributesNum(arDest);
	
	string sArray[50]; // динамические массивы в Шторме не организуешь :(
	for (int i = 0; i<iNum; i++)
	{
		arImt = GetAttributeN(arDest, i);
		sAttr = GetAttributeName(arImt);
		if(CheckAttribute(&NullCharacter,"TravelMap.Islands." + sAttr + ".Treasure"))
		{
			if(sCurIsland == sAttr || CheckTreasureMaps(sAttr)) continue;
			else
			{
				sArray[m] = sAttr;
				m++;		
			}	
		}
	}
	m = rand(m-1);
	return sArray[m];
}

bool CheckTreasureMaps(string sIsland)
{
	ref Itm;
	
	if(GetCharacterItem(pchar,"mapQuest") > 0)
	{
		itm = ItemsFromID("mapQuest");
		if(CheckAttribute(itm, "MapIslId") && itm.MapIslId == sIsland) return true;
	}		
	if(GetCharacterItem(pchar,"map_full") > 0)
	{
		itm = ItemsFromID("map_full");
		if(CheckAttribute(itm, "MapIslId") && itm.MapIslId == sIsland) return true;
	}	
	return false;
}

string GetLocationForTreasure(string island)
{
    int iNum;
	aref arDest, arImt;
	string sAttr;

	makearef(arDest, NullCharacter.TravelMap.Islands.(island).Treasure);
	iNum = GetAttributesNum(arDest);
    iNum = rand(iNum-1);
    
    arImt = GetAttributeN(arDest, iNum);
	return GetAttributeName(arImt);
}

string GetBoxForTreasure(string island, string location)
{
    int iNum;
	aref arDest, arImt;
	string sAttr;

	makearef(arDest, NullCharacter.TravelMap.Islands.(island).Treasure.(location));
	iNum = GetAttributesNum(arDest);
    iNum = rand(iNum-1);
    
    arImt = GetAttributeN(arDest, iNum);
	return GetAttributeValue(arImt);  // тут не атрибут, а значеие
}

void GenerateMapsTreasure(ref item, int iProbability1, int iProbability2)
{		
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_jam")) 		item.BoxTreasure.map_jam 		= 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_cayman")) 	item.BoxTreasure.map_cayman 	= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_barbados")) 	item.BoxTreasure.map_barbados 	= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_trinidad")) 	item.BoxTreasure.map_trinidad 	= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_Curacao")) 	item.BoxTreasure.map_Curacao 	= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_martiniqua")) item.BoxTreasure.map_martiniqua = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_dominica")) 	item.BoxTreasure.map_dominica 	= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_puerto")) 	item.BoxTreasure.map_puerto 	= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_cuba")) 		item.BoxTreasure.map_cuba 		= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_hisp")) 		item.BoxTreasure.map_hisp 		= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_nevis")) 		item.BoxTreasure.map_nevis 		= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_guad")) 		item.BoxTreasure.map_guad 		= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_antigua")) 	item.BoxTreasure.map_antigua 	= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_TORTUGA")) 	item.BoxTreasure.map_TORTUGA 	= 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_terks")) 		item.BoxTreasure.map_terks 		= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_sm")) 		item.BoxTreasure.map_sm 		= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_bermudas")) 	item.BoxTreasure.map_bermudas 	= 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_Pearl")) 		item.BoxTreasure.map_Pearl 		= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_beliz")) 		item.BoxTreasure.map_beliz 		= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_santa")) 		item.BoxTreasure.map_santa 		= 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_maine_1")) 	item.BoxTreasure.map_maine_1	= 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_maine_2")) 	item.BoxTreasure.map_maine_2 	= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_panama")) 	item.BoxTreasure.map_panama 	= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_maracaibo")) 	item.BoxTreasure.map_maracaibo 	= 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_cumana")) 	item.BoxTreasure.map_cumana 	= 1;
}

void GenerateAdmiralMapsTreasure(ref item, int abl) // Jason, адмиральские карты по 1 шт 240912
{
	if (!CheckAttribute(pchar, "questTemp.AdmiralMap")) return;
	if (rand(abl) == 1)
	{
		string amap = SelectAdmiralMaps();
		if (amap != "") item.BoxTreasure.(amap)	= 1;
	}
}


void FillMapForTreasure(ref item)
{
    item.MapIslId   = GetIslandForTreasure();
    item.MapLocId   = GetLocationForTreasure(item.MapIslId);
    item.MapBoxId   = GetBoxForTreasure(item.MapIslId, item.MapLocId);
    item.MapTypeIdx = rand(2);

    // генерим клад
    DeleteAttribute(item, "BoxTreasure");
    FillBoxForTreasure(item, rand(3));
    FillBoxForTreasureAddition(item);

    if (!CheckAttribute(Pchar, "GenQuest.TreasureBuild"))
    {
        if (rand(15) == 1) item.MapTypeIdx = -1;
    }
    else
    {
       FillBoxForTreasureSuper(item);
    }
    DeleteAttribute(Pchar, "GenQuest.TreasureBuild"); //сборный

    if (sti(item.MapTypeIdx) != -1)
    {
        Pchar.quest.SetTreasureFromMap.win_condition.l1          = "location";
        Pchar.quest.SetTreasureFromMap.win_condition.l1.location = item.MapLocId;
        Pchar.quest.SetTreasureFromMap.win_condition             = "SetTreasureFromMap";
		
		pchar.GenQuest.Treasure.Vario = rand(5); // определяем событие
		locations[FindLocation(item.MapLocId)].DisableEncounters = true; //энкаутеры закрыть
    }
}
void FillBoxForTreasure(ref item, int i)
{
	// определяем тип
	switch (i)
	{
		// good
		case 0:
		    if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry2 = 2 + rand(30);
	        }
	        else
	        {
	            item.BoxTreasure.jewelry3 = 10 + rand(3);
	        }
			if (rand(1) == 1)
	        {
            	item.BoxTreasure.gold_dublon = 20 + rand(100);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry3 = 1 + rand(30);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry5 = 5 + rand(60);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry40 = 15 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry41 = 15 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry42 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry43 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry44 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry45 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral2 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral5 = 5 + rand(100);
	        }
	        if (rand(4) == 1 && sti(pchar.rank) >= 10)
	        {
            	item.BoxTreasure.cirass6 = 1;
	        }
			if (rand(4) == 1 && sti(pchar.rank) >= 14)
	        {
            	item.BoxTreasure.cirass7 = 1;
	        }
			GenerateMapsTreasure(item, 35, 70);
			GenerateAdmiralMapsTreasure(item, 40); // 240912
	    break;
	    // best
	    case 1:
            if (rand(2) == 1)
	        {
            	item.BoxTreasure.chest = 1 + rand(14);
	        }
	        else
	        {
	            item.BoxTreasure.jewelry53 = 10 + rand(3);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.icollection = 1 + rand(4);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry1 = 15 + rand(100);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry53 = 15 + rand(100);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry52 = 15 + rand(100);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry6 = 5 + rand(100);
	        }
	        if (rand(4) == 1 && sti(pchar.rank) >= 12)
	        {
            	item.BoxTreasure.cirass3 = 1;
	        }
			if (rand(1) == 1)
	        {
            	item.BoxTreasure.gold_dublon = 50 + rand(150);
	        }
			if (drand(5) == 1)
			{
				item.BoxTreasure.rat_poison = 1;
			}
			GenerateMapsTreasure(item, 25, 50);
			GenerateAdmiralMapsTreasure(item, 20); // 240912
	    break;
	    // bad
	    case 2:
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.slave_01 = 20 + rand(80);
	        }
	        else
	        {
                item.BoxTreasure.blade_05 = 5 + rand(100);//fix
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.blade_07 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.slave_02 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry16 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral4 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral6 = 5 + rand(200);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral7 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral9 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral10 = 25 + rand(300);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral1 = 15 + rand(300);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral11 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral12 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral13 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral16 = 5 + rand(200);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral23 = 10 + rand(100);
	        }
			if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral22 = 5 + rand(50);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.blade_03 = 1;
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.cirass1 = 1;
	        }
			if (rand(3) == 1)
	        {
            	item.BoxTreasure.cirass5 = 1;
	        }
			if (rand(2) == 1)
	        {
            	item.BoxTreasure.Chest_open = 3;
	        }
	    break;

	    case 3:
	        FillBoxForTreasure(item, 0);
	    break;
	}
}

void FillBoxForTreasureAddition(ref item)
{
    float   nLuck   = GetCharacterSkillToOld(Pchar, SKILL_FORTUNE);

    if (5*nLuck > rand(55))
    {
	    if (GetCharacterItem(Pchar, "map_part1") == 0)
	    {
	        item.BoxTreasure.map_part1 = 1;
	    }
	    else
	    {
	        if (GetCharacterItem(Pchar, "map_part2") == 0)
		    {
		        item.BoxTreasure.map_part2 = 1;
		    }
	    }
	}
	// +1 вещи
	switch (rand(40))
	{
		case 1:
		    item.BoxTreasure.gold_dublon = rand(40) + 20; // 160912
		break;
		case 2:
		    item.BoxTreasure.jewelry10 = 1;
		break;
		case 3:
		    item.BoxTreasure.jewelry11 = 1;
		break;
		case 4:
		    item.BoxTreasure.jewelry12 = 1;
		break;
		case 5:
		    item.BoxTreasure.indian_6 = 1;
		break;
		case 6:
		    item.BoxTreasure.indian_2 = 1;
		break;
		case 7:
		    item.BoxTreasure.jewelry13 = 1;
		break;
		case 8:
		    item.BoxTreasure.indian_3 = 1;
		break;
		case 9:
		    item.BoxTreasure.indian_1 = 1;
		break;
		case 10:
		    item.BoxTreasure.indian_4 = 1;
		break;
		case 11:
		    item.BoxTreasure.indian_5 = 1;
		break;
		case 12:
		    item.BoxTreasure.indian_7 = 1;
		break;
		case 13:
		    item.BoxTreasure.indian_8 = 1;
		break;
		case 14:
		    item.BoxTreasure.indian_9 = 1;
		break;
		case 15:
		    item.BoxTreasure.indian_10 = 1;
		break;
		case 16:
		    item.BoxTreasure.indian_11 = 1;
		break;
		case 17:
		    item.BoxTreasure.amulet_1 = 1;
		break;
		case 18:
		    item.BoxTreasure.amulet_2 = 1;
		break;
		case 19:
		    item.BoxTreasure.amulet_3 = 1;
		break;
		case 20:
		    item.BoxTreasure.amulet_4 = 1;
		break;
		case 21:
		    item.BoxTreasure.amulet_5 = 1;
		break;
		case 22:
		    item.BoxTreasure.Mineral14 = 1;
		break;
		case 23:
		    item.BoxTreasure.Mineral15 = 1;
		break;
		case 24:
		    item.BoxTreasure.gold_dublon = rand(40) + 20; // 160912
		break;
		case 25:
		    item.BoxTreasure.amulet_6 = 1;
		break;
		case 26:
		    item.BoxTreasure.amulet_7 = 1;
		break;
		case 27:
		    item.BoxTreasure.amulet_8 = 1;
		break;
		case 28:
		    item.BoxTreasure.gold_dublon = rand(40) + 20;
		break;
	}
	GenerateMapsTreasure(item, 10, 20);
	
}

void FillBoxForTreasureSuper(ref item)
{
    float     nLuck   = GetCharacterSkillToOld(Pchar, SKILL_FORTUNE);
	int     i;
	string  itmName;

    if (3*nLuck > rand(21))// еще поди найди 2 куска
    {
		i = 0;
		itmName = "";
		while (itmName == "" && i < 15)
		{
            switch (rand(19)) // 170912 belamour 20102020 ДиС
			{
                case 0:
        			itmName = "pistol4";
				break;
				case 1:
					itmName = "cirass1";
				break;
				case 2:
					itmName = "cirass2";
				break;
				case 3:
					itmName = "spyglass3";
				break;
				case 4:
					itmName = "mushket1";
				break;
				case 5:
        			itmName = "talisman8";
				break;
				case 6:
                    itmName = GetGeneratedItem("topor_04");
				break;
				case 7:
        			itmName = "spyglass4";
				break;
				case 8:
        			itmName = GetGeneratedItem("blade_17");
				break;
				case 9:
        			itmName = GetGeneratedItem("blade_21");
				break;
				case 10:
        			itmName = "cirass3";
				break;
				case 11:
        			itmName = GetGeneratedItem("blade_19");
				break;
				case 12:
        			itmName = "cirass7";
				break;
				case 13:
        			itmName = GetGeneratedItem("blade_18");
				break;
				case 14:
        			itmName = GetGeneratedItem("blade_20");
				break;
				case 15:
        			itmName = "cirass6";
				break;				
				case 16:
        			itmName = "mushket2";
				break;					
				case 17:
        			itmName = "mushket3";
				break;	
                                case 18:
        			itmName = GetGeneratedItem("shamshir"); // belamour клинок ДиС
				break;	
                                case 19:
        			itmName = "howdah";                    // belamour картечница ДиС
				break;	
			}
			if (GetCharacterItem(Pchar, itmName) > 0)
		    {
          		itmName = "";
		    }
		    i++;
	    }
	    if (itmName != "")
	    {
	        item.BoxTreasure.(itmName) = 1;
	    }
		GenerateAdmiralMapsTreasure(item, 15); // 240912
	}
}

void SetTreasureBoxFromMap()
{
    aref   item;
    ref    loc;
    string box;
    aref   arToBox;
    aref   arFromBox;

    if (GetCharacterItem(Pchar, "map_full")>0 )
    {
        Log_Info("The treasures must be somewhere nearby!");
        PlaySound("interface\notebook.wav");
		Statistic_AddValue(Pchar, "Treasure", 1);
		Achievment_SetStat(Pchar, 8, 1);
        // немного веселой жизни
        if (rand(1) == 0) TraderHunterOnMap();
		else CoolTraderHunterOnMap();
        if( CheckAttribute(Pchar,"location.from_sea") )
        {
            if (rand(2) == 1) //33%
            {
                Pchar.quest.SetTreasureHunter.win_condition.l1          = "location";
                Pchar.quest.SetTreasureHunter.win_condition.l1.location = Pchar.location.from_sea;
                Pchar.quest.SetTreasureHunter.win_condition             = "";
                Pchar.quest.SetTreasureHunter.function    = "SetTreasureHunter";
            }
        }

        Items_FindItem("map_full", &item);

        box = item.MapBoxId;

        loc = &locations[FindLocation(item.MapLocId)];
        loc.(box).items = "";

        makearef(arToBox, loc.(box).items);
        makearef(arFromBox, item.BoxTreasure);
        CopyAttributes(arToBox, arFromBox);

        loc.(box) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
        loc.(box).Treasure =  true; // признак сокровища в сундуке

        DeleteAttribute(item, "MapIslId");
        TakeNItems(Pchar, "map_full", -1);
    }
}
//  Карты сокровищ  ГЕНЕРАТОР <--

// погодня за ГГ на карте
void  TraderHunterOnMap()
{
    // немного веселой жизни
    ref  sld;
    int  i;

    string sCapId = "Follower0";
    string sGroup = "Sea_" + sCapId + "1";

	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
    for (i = 1; i <= GetCompanionQuantity(pchar); i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", sti(PChar.rank) + 5, PIRATE, 15, true, "hunter"));
        SetShipHunter(sld);
        SetFantomParamHunter(sld); //крутые парни
        SetCaptanModelByEncType(sld, "war");
        sld.AlwaysEnemy = true;
        sld.DontRansackCaptain = true;
        sld.mapEnc.type = "war";
        sld.mapEnc.Name = "gentlemen of Fortune";
		sld.hunter = "pirate";
        Group_AddCharacter(sGroup, sCapId + i);
    }

    Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
    Map_CreateWarrior("", sCapId + "1", 8);
}

void CoolTraderHunterOnMap()//Jason, быстрые ДУ
{
    ref  sld;
    int  i;

    string sCapId = "Follower0";
    string sGroup = "Sea_" + sCapId + "1";

	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
    for (i = 1; i <= GetCompanionQuantity(pchar); i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", sti(PChar.rank) + 8, PIRATE, 15, true, "hunter"));
        SetShipHunter(sld);
        SetFantomParamHunter(sld); //крутые парни
        SetCaptanModelByEncType(sld, "war");
        sld.AlwaysEnemy = true;
        sld.DontRansackCaptain = true;
        sld.mapEnc.type = "war";
        sld.mapEnc.Name = "gentlemen of Fortune";
		sld.hunter = "pirate";
        Group_AddCharacter(sGroup, sCapId + i);
    }

    Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
    Map_CreateCoolWarrior("", sCapId + "1", 8);
}

void SetTreasureHunter(string temp)
{
    int    j, i, k;
	string sTemp, sCapId;
	ref    sld;
	bool   ok;

	if (chrDisableReloadToLocation) return; // идет некий другой квест с запретом выхода
	
    Pchar.GenQuest.Hunter2Pause            = true;
    
    j = GetOfficersQuantity(Pchar) + 2;
    
	sCapId = "LandHunter0";
    sTemp = "LAND_HUNTER";
	ok = true;
	arrayNPCModelHow = 0;
    for (i = 1; i <= j; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", sti(PChar.rank) + 5, PIRATE, 0, true, "hunter"));
        SetFantomParamHunter(sld); //крутые парни
        sld.Dialog.CurrentNode = "TreasureHunter";
        sld.dialog.filename = "Hunter_dialog.c";
        sld.greeting = "hunter";
        sld.location = "none"; // вот где порылась собака!!!!!!!!!!!

        SetModelPirate(sld);
        k = 0;
		while (!CheckNPCModelUniq(sld) && k < 10)
		{
		    k++;
			SetModelPirate(sld);
		}
		arrayNPCModel[arrayNPCModelHow] = sld.model;
		arrayNPCModelHow++;
		
        LAi_SetActorTypeNoGroup(sld);
        LAi_SetCheckMinHP(sld, (LAi_GetCharacterHP(sld) - 1), false, "Battle_Hunters_Land");
        if (PlaceCharacter(sld, "goto", "random_must_be_near") == "" && i == 1) // fix если вдруг нет в локации
        {
            ok = false;
            break;
        }
        LAi_ActorFollow(sld, pchar, "", 8.0);
        //LAi_Actor2WaitDialog(sld, pchar); // ждать диалог, но бежать
        LAi_group_MoveCharacter(sld, sTemp);
    }

	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);

	LAi_group_ClearAllTargets();
	LAi_SetFightModeForOfficers(false);
	if (ok)
    {
        PChar.HunterCost = makeint(sti(Pchar.money) / 5) + rand(20)*1000; //сразу генерим
        PChar.HunterCost.Qty = i;
        PChar.HunterCost.TempHunterType = "";
        sld = characterFromID(sCapId + "1");
        LAi_type_actor_Reset(sld);
        LAi_ActorDialog(sld, pchar, "", 4.0, 0);
		chrDisableReloadToLocation = true;
		DoQuestCheckDelay("OpenTheDoors", 5.0);
    }
}

ref SetFantomSkeletForts(string group, string locator, string enemygroup, string _type)
// _type = "GhostShipCrew"   _type = "ParamHunter"  _type = "none"
{
    string emodel;
    ref    Cr;

    emodel = GetRandSkelModel();

    Cr = LAi_CreateFantomCharacterEx(emodel, "man", group, locator);

    if (Cr.location.locator != "")
    {
		if (_type == "GhostShipCrew" || _type == "ParamHunter")
		{
			SetFantomParamHunter(Cr);
		}
		else
		{
		    SetFantomParam(Cr);
		}
		LAi_SetWarriorType(Cr);
	    LAi_group_MoveCharacter(Cr, enemygroup);
	    LAi_NoRebirthEnable(Cr); //не показывать убитых при входе в локацию
	    LAi_LoginInCaptureTown(Cr, true); // для записи игры
	    if (_type == "GhostShipCrew")
	    {
		    // возможно дает вылеты от многих трупов Cr.DontClearDead = true;
		    Cr.GhostShipCrew = true;
	    }
    }
    return Cr;
}