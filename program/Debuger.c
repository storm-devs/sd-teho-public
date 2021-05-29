// BOAL нажатие на F12 вызывает этот код. Его можно править с alt-tab в игре, изменения будут сразу
//native string GetHello();
//#libriary "b_engine"

void ActiveINSERTControl()
{
    //DoReloadCharacterToLocation(Pchar.location, "goto", "goto2");
    //DoReloadCharacterToLocation("PlutoStoreSmall", "reload", "reload1");
	//DoReloadCharacterToLocation("Panama_TownhallRoom", "reload", "reload1");
}

void ActiveF4Control()
{
	/*Log_Info("Test F4 button");
    SetRandGeraldSail(pchar, rand(4));*/
	
	/////////////////////////////////////
	
	Rat_GenerateRat();
	
	Log_Info("Сгенерили крысу!");
}

// Warship. Сюда повесил дамп аттрибутов - по Ф12 не нужно это
void ActiveF5Control()
{
	int characterIndex = LAi_FindNearestVisCharacter(PChar, 15);
	ref characterRef;
	
    if(characterIndex != -1)
    {
        characterRef = GetCharacter(characterIndex);
		
		trace("==================== " + characterRef.ID + " ====================");
		DumpAttributes(characterRef);
		trace("========================================");
		
		string sGun = GetCharacterEquipByGroup(characterRef, GUN_ITEM_TYPE);
		if(sGun != "") 
		{
			ref rItm = ItemsFromID(sGun); 
			trace("==================== " + rItm.ID + " ====================");
			DumpAttributes(rItm);
			trace("========================================");
		}	
	}

	Log_Info("Дамп аттрибутов ближайшего персонажа");
}

void ActiveF7Control()
{
	// Warship. Убить боижайшего персонажа
	int characterIndex = LAi_FindNearestVisCharacter(PChar, 25);
	ref characterRef;
	
    if(characterIndex != -1)
	{
		characterRef = &Characters[characterIndex];
		
		if(!LAi_IsImmortal(characterRef)) // Квестовые
		{
			LAi_KillCharacter(characterRef);
			Log_Info("Убили персонажа с ID == " + characterRef.Id);
		}
		else
		{
			Log_Info("Нельзя убить персонажа с ID == " + characterRef.Id);
		}
	}
}

void ActiveF10Control() {
	Log_Info("Консоль вызвана.");
	/*int iRank = 1;
	for(int i = 1; i <= 4; i++)
	{
		
		if (i < 4) {
			sld = GetCharacter(NPC_GenerateCharacter("Guard_itza_mush_"+i, "mush_itza_"+(rand(2)+1), "man", "mushketer", iRank, PIRATE, -1, false, "quest"));
			FantomMakeCoolFighter(sld, iRank, 1, 1, "", "mushket1", "cartridge", 1);
			sld.MusketerDistance = 0;
		} else {
			sld = GetCharacter(NPC_GenerateCharacter("Guard_itza_mush_"+i, "itza_"+(rand(2)+1), "man", "man", iRank, PIRATE, -1, false, "quest"));
		}
		ChangeCharacterAddressGroup(sld, "Temple_great", "monsters", "mushketer"+i);
		
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_warrior_DialogEnable(sld, false);
		LAi_group_MoveCharacter(sld, "ITZA");
	}*/
	for(int i = 1; i <= 3; i++) {
		sld = CharacterFromID("Guard_itza_mush_" + i);
		sld.MusketerDistance = 20;
	}
	LAi_group_FightGroups("ITZA", LAI_GROUP_PLAYER, true);
	Log_Info("Консоль отработала.");
}

///  статы персонажа в близи
void ActiveF12Control()
{
    ref mainCh = GetMainCharacter();
    
    //Найти ближайшего видимого персонажа в заданном радиусе
    int res = LAi_FindNearestVisCharacter(mainCh, 15);
    if (res != -1)
    {
        ref findCh = GetCharacter(res);
        res = findCh.chr_ai.hp;
        Log_SetStringToLog("" + GetFullName(findCh) +
                           " "+XI_ConvertString("Rank")+" " + findCh.rank + " "+XI_ConvertString("Health")+" "+res + "/" + LAi_GetCharacterMaxHP(findCh));

		if (bBettaTestMode)
        {
            Log_SetStringToLog("Id= " + findCh.id);
            Log_SetStringToLog("Idx= " + findCh.index);
            
            if(CheckAttribute(findCh, "LifeDay"))
		Log_Info("LifeDay - " + findCh.LifeDay);
		
	    if(CheckAttribute(findCh, "City"))
	    	Log_Info("City - " + findCh.City);
            
            if (CheckAttribute(findCh, "equip.blade"))
            {
                Log_SetStringToLog("Blade= " + findCh.equip.blade);
            }
            if (CheckAttribute(findCh, "equip.pistol"))
            {
                Log_SetStringToLog("Pistol= " + findCh.equip.pistol);
            }
            Log_SetStringToLog("model= " + findCh.model);
            Log_SetStringToLog("face= " + findCh.faceId);
            Log_SetStringToLog("chr_ai.type= " + findCh.chr_ai.type);
            Log_SetStringToLog("Group= "+findCh.location.group + " locator= " + findCh.location.locator);
            if (CheckAttribute(findCh, "cirassId"))
            {
                Log_SetStringToLog("cirassId= " + sti(findCh.cirassId));
            }
            else
            {
                Log_SetStringToLog("Нет брони");
            }
            if (CheckAttribute(findCh, "chr_ai.FencingType"))
            {
                Log_SetStringToLog("chr_ai.FencingType= " + findCh.chr_ai.FencingType));
            }
            else
            {
                Log_SetStringToLog("Нет FencingType - error");
            }
            /*int dchr_index;
            ref deadCh;
            dchr_index = Dead_FindCloseBody();
            if (dchr_index != -1)
            {
                deadCh = &Dead_Characters[dchr_index];
                Log_SetStringToLog("Dead=" + deadCh.id);
            } */
			Log_SetStringToLog("Нация: " + findCh.nation);
			Log_SetStringToLog("Пол: " + findCh.sex);
			Log_SetStringToLog("Группа: " + findCh.chr_ai.group);
			Log_SetStringToLog("Темплейт: " + findCh.chr_ai.tmpl);

			//Log_SetStringToLog("Стейт: " + findCh.chr_ai.tmpl.state);
		//	dumpattributes(findCh);

            mainCh.SystemInfo.OnlyShowCharacter = true;
			LaunchCharacter(findCh);
        }
        else
        {
            if (MOD_BETTATESTMODE == "Test")
	        {
	            Log_SetStringToLog("Id= " + findCh.id);
	        }
        }
    }
}

///////////////////////////// test //////////////
void TestColonyCommanders()
{
	int iChar;

	string sColony;

	int i;
	float x, y, z;  // boal

	for (i=0; i<MAX_COLONIES; i++)
	{
		if (colonies[i].nation == "none") continue; // необитайки
		// зададим базовых мэров городов
		iChar = GetCharacterIndex(colonies[i].id + "_Mayor");
		if (iChar != -1)
		{   // мэр есть
        	Log_Info("M: " + characters[iChar].id + " L:" + characters[iChar].location +
        	" " + characters[iChar].City + "  " + characters[iChar].nation);
        	trace("M: " + characters[iChar].id + " L:" + characters[iChar].location +
        	" " + characters[iChar].City + "  " + characters[iChar].nation);
        }

		// добавить проверку на пиратов, у них нет фортов, нафиг им коммандер?
		if (CheckAttribute(&colonies[i], "HasNoFort"))
		{
			continue;
		}
		iChar = GetCharacterIndex(colonies[i].id + " Fort Commander");
		Log_Info("F: " + characters[iChar].id + " L:" + characters[iChar].location + " g " + characters[iChar].location.group + " r " + characters[iChar].location.locator +
  		" " + characters[iChar].City + "  " + characters[iChar].nation);
  		trace("F: " + characters[iChar].id + " L:" + characters[iChar].location + " g " + characters[iChar].location.group + " r " + characters[iChar].location.locator +
  		" " + characters[iChar].City + "  " + characters[iChar].nation);
	}
}
// проверка ликвидности товара - цена-вес, что выгоднее - выводим в компил.лог список, строим заполняя трюм товаром по одной пачке
void TestGoodsLiquidity()
{
	int i, j, idx;
	float fMaxCost;
	
	for (i = 0; i< GOODS_QUANTITY; i++)
	{
		SetCharacterGoods(pchar, i, sti(Goods[i].Units));
	}
	trace("======= TestGoodsLiquidity ======== start ");
	for (j = 0; j< GOODS_QUANTITY; j++)
	{
		fMaxCost = 0;
		idx = -1; 
		for (i = 0; i< GOODS_QUANTITY; i++)
		{
			if (GetCargoGoods(pchar, i) > 0)
			{
				if (fMaxCost < stf(Goods[i].Cost)/stf(Goods[i].Weight)) 
				{
					fMaxCost = stf(Goods[i].Cost)/stf(Goods[i].Weight);
					idx = i;
				} 
			}
		}
		if (fMaxCost > 0)
		{
			SetCharacterGoods(pchar, idx, 0);	
			trace(Goods[idx].Name + " = " + fMaxCost);
			Log_info(Goods[idx].Name + " = " + fMaxCost);
		}
	}
	trace("======= TestGoodsLiquidity ======== end ");
}
