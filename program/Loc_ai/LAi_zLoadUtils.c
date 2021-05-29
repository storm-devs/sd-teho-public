// Jason: LSC - поведение горожан-статиков - хождение по городу и заведениям
void CreateLostShipsCity(aref loc)
{	
	int i;
	if (loc.id == "LostShipsCity_town" && isDay())
	{
		ref sld;
		string sTemp, sLocator;
		int locNum, n, Index;
		int qtyTavern = 0; 
		//int qtyResidence = 0;
		int qtyChurch = 0;
		//int qtyPrison = 0;
		int qtyStore = 0;
		for(i=0; i<MAX_CHARACTERS; i++)
		{
			makeref(sld, characters[i]);
			if (sld.location == "FleuronTavern") qtyTavern++;
			//if (sld.location == "SanAugustineResidence") qtyResidence++;
			if (sld.location == "GloriaChurch") qtyChurch++;
			//if (sld.location == "TartarusPrison") qtyPrison++;
			if (sld.location == "EsmeraldaStoreBig") qtyStore++;
		}
		//размещаем нпс
		for(i=0; i<MAX_CHARACTERS; i++)
		{
			makeref(sld, characters[i]);
			if (CheckAttribute(sld, "city") && sld.city == "LostShipsCity")
			{
				//////// если внешний горожанин /////////
				if (sld.cityTape == "citizen")
				{
					if (GetNpcQuestPastTimeParam(sld, "location") > sti(sld.location.hours)) 
					{
						DeleteAttribute(sld, "location.going"); //снимаем флаг
						LAi_SetLoginTime(sld, 6.0, 21.99);
						//--> вечером организовываем толпу в таверне
						if (GetTime() > 19.0 && sld.sex == "man" && rand(1))
						{
							if (qtyTavern < LSC_MAX_TAVERN)
							{
								sld.location.going = "toTavern"; //флаг генерации в таверне
								qtyTavern++;
							}
							continue;
						}
						//<-- вечером организовываем толпу в таверне
						if (sld.location == "LostShipsCity_town") //если горожанин на улице
						{
							if (rand(1))
							{
								SaveCurrentNpcQuestDateParam(sld, "location");
								sld.location.hours = rand(3)+1;
								switch (rand(2))
								{
								case 0: //в церковь
									if (qtyChurch < LSC_MAX_CHURCH)
									{
										sld.location.going = "toChurch"; //флаг генерации в церкви
										qtyChurch++;
									}
									break;
								case 1: //в таверну
									if (qtyTavern < LSC_MAX_TAVERN)
									{
										sld.location.going = "toTavern"; //флаг генерации в таверне
										qtyTavern++;
									}
									break;
								case 2: //в магазин
									if (qtyStore < LSC_MAX_STORE)
									{
										sld.location.going = "toStore"; //флаг генерации в магазине	
										qtyStore++;
									}
									break;									
								}
							}
						}
						else
						{	//возвращемся на свой корабль
							//проверим занятость локатора								
							if (!LAi_CheckLocatorFree("goto", sld.location.baseLocator))
							{	//выберем незанятый 
								sTemp = sld.location.baseLocator;
								sTemp = strcut(sTemp, 4, 5);
								for (n=0; n<=9; n++)
								{											
									sLocator = "goto" + sTemp + "_" + n;
									if (LAi_CheckLocatorFree("goto", sLocator))
									{
										LAi_SetLSCoutTypeNoGroup(sld);
										ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sLocator);
										break;
									}
								}
							}
							else
							{
								LAi_SetLSCoutTypeNoGroup(sld);
								ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
							}
						}
					}
				}
				//////// если домашний горожанин /////////
				if (sld.cityTape == "citizenHome")
				{
					if (GetNpcQuestPastTimeParam(sld, "location") > sti(sld.location.hours)) 
					{
						DeleteAttribute(sld, "location.going"); //снимаем флаг
						LAi_SetLoginTime(sld, 6.0, 21.99);
						//--> вечером организовываем толпу в таверне
						if (GetTime() > 19.0 && sld.sex == "man" && rand(1))
						{
							if (qtyTavern < LSC_MAX_TAVERN)
							{
								sld.location.going = "toTavern"; //флаг генерации в таверне
								qtyTavern++;
							}
							continue;
						}
						//<-- вечером организовываем толпу в таверне
						if (sld.location == sld.location.baseLocation) //если горожанин у себя дома
						{
							if (rand(1))
							{
								SaveCurrentNpcQuestDateParam(sld, "location");
								sld.location.hours = rand(6)+1;
								switch (rand(3))
								{
								case 0: //в церковь
									if (qtyChurch < LSC_MAX_CHURCH)
									{
										sld.location.going = "toChurch"; //флаг генерации в церкви
										qtyChurch++;
									}
									break;
								case 1: //в таверну
									if (qtyTavern < LSC_MAX_TAVERN)
									{
										sld.location.going = "toTavern"; //флаг генерации в таверне
										qtyTavern++;
									}
									break;
								case 2: //в магазин
									if (qtyStore < LSC_MAX_STORE)
									{
										sld.location.going = "toStore"; //флаг генерации в магазине	
										qtyStore++;
									}
									break;	
								case 3: //на улицы
									//проверим занятость локатора								
									if (!LAi_CheckLocatorFree("goto", sld.location.baseLocator))
									{	//выберем незанятый 
										sTemp = sld.location.baseLocator;
										sTemp = strcut(sTemp, 4, 5);
										for (n=0; n<=9; n++)
										{											
											sLocator = "goto" + sTemp + "_" + n;
											if (LAi_CheckLocatorFree("goto", sLocator))
											{
												LAi_SetLSCoutTypeNoGroup(sld);
												ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sLocator);
												break;
											}
										}
									}
									else
									{
										LAi_SetLSCoutTypeNoGroup(sld);
										ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
									}
									break;	
								}
							}
						}
						else
						{	//возвращемся на свой корабль
							LAi_SetOwnerTypeNoGroup(sld);
							ChangeCharacterAddressGroup(sld, sld.location.baseLocation, "barmen", "stay");
						}
					}
				}
			}
		}
	}
	//------------------- таверна ------------------------
	if (loc.id == "FleuronTavern")
	{
		for(i=0; i<MAX_CHARACTERS; i++)
		{
			makeref(sld, characters[i]);
			if (CheckAttribute(sld, "location.going") && sld.location.going == "toTavern")
			{
				DeleteAttribute(sld, "location.going");
				LAi_RemoveLoginTime(sld);
				if (sld.sex == "man")
				{
					DeleteAttribute(sld, "nonTable");
					LAi_SetSitTypeNoGroup(sld);
					if (sld.id == "LSCMayor")
						ChangeCharacterAddressGroup(sld, loc.id, "quest", "head_sit");
					else
						PlaceCharacter(sld, "sit", "random_free");
				}
				else
				{
					LAi_SetCitizenTypeNoGroup(sld);
					PlaceCharacter(sld, "goto", "random_free");
				}
			}
		}
	}
	//------------------- церковь ------------------------
	if (loc.id == "GloriaChurch")
	{
		//сам падре
		if (!isDay())
		{
			Index = GetCharacterIndex("Julian");	
			if (Index != -1)
			{
				sld = &characters[Index];
				LAi_SetSitTypeNoGroup(sld);
				PlaceCharacter(sld, "quest", "priest");
			}
		}
		else
		{
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				makeref(sld, characters[i]);
				//падре днем
				if (sld.id == "Julian")
				{
					LAi_SetPriestTypeNoGroup(sld);
					ChangeCharacterAddressGroup(sld, sld.location, "barmen",  "stay");
				}
				//граждане
				if (CheckAttribute(sld, "location.going") && sld.location.going == "toChurch")
				{
					DeleteAttribute(sld, "location.going");
					if (sld.sex == "woman")
					{
						LAi_SetCitizenTypeNoGroup(sld);
						PlaceCharacter(sld, "goto", "random_free");
					}
					else
					{
						sld.nonTable = true;
						LAi_SetSitTypeNoGroup(sld);
						PlaceCharacter(sld, "sit", "random_free");
					}
				}
			}
		}
	}
	//------------------- магазин ------------------------
	if (loc.id == "EsmeraldaStoreBig")
	{
		for(i=0; i<MAX_CHARACTERS; i++)
		{
			makeref(sld, characters[i]);
			if (CheckAttribute(sld, "location.going") && sld.location.going == "toStore")
			{
				DeleteAttribute(sld, "location.going");
                LAi_SetStayTypeNoGroup(sld);
				PlaceCharacter(sld, "goto", "random_free");
			}
		}
	}
}

void CreatUnderwater(aref loc)
{
	if (loc.type == "underwater")
	{
		if (CheckAttribute(loc, "type.LSC"))
			{
				if (GetCharacterIndex("Mary") != -1) // ничего умнее этого не удалось придумать patch-10
				{
					sld = characterFromId("Mary");
					LAi_SetActorType(sld);
					LAi_ActorGoToLocation(sld, "reload", "reload1", "CeresSmithy", "goto", "goto11", "LSC_MaryReturnNormal_1", 1.5);
				}
				LocatorReloadEnterDisable("LostShipsCity_town", "reload72", true); //закрываем вход в Феникс
				LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", true); //закрываем выход от Механика
				DeleteAttribute(pchar, "questTemp.LSC.immersion");
				pchar.questTemp.LSC.UW_end = "true"; // сдача костюма
				SetShowTimer(500.0); //таймер на 20 игровых минут
				AddCharacterHealth(pchar, -3); //портим здоровье
			for (int i=1; i<=28; i++)
			{
				if (GetCharacterIndex("Crab_"+i) == -1)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Crab_"+i, "crabBig", "crab", "crabBig", 50+(MOD_SKILL_ENEMY_RATE), PIRATE, -1, false, "quest"));
					sld.name = "Giant crab";
					sld.lastname = "";
					GiveItem2Character(sld, "unarmed");
					EquipCharacterbyItem(sld, "unarmed");
					sld.SaveItemsForDead = true;
					if (bPincers()) TakeNItems(sld, "crab_pincers", 2); // клешни
					//if (rand(2) == 1) TakeNItems(sld, "crab_jaw", rand(1)); // жвалы
					int iTemp = 200+MOD_SKILL_ENEMY_RATE*10+sti(pchar.rank)*8;
					LAi_SetHP(sld, iTemp, iTemp);
					if (MOD_SKILL_ENEMY_RATE > 2) sld.MultiFighter = stf(MOD_SKILL_ENEMY_RATE/2.5);
					sld.animal = true;
					SetCharacterPerk(sld, "BasicDefense");
					SetCharacterPerk(sld, "AdvancedDefense");
					SetCharacterPerk(sld, "CriticalHit");
					LAi_SetWarriorType(sld);
					LAi_warrior_SetStay(sld, true);
					LAi_warrior_DialogEnable(sld, false);
					LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
				}
				PlaceCharacter(sld, "goto", "random_free");
			}
		}
		else
		{
			if (CheckAttribute(loc, "watertemple")) SetShowTimer(80.0); // 010912
			else SetShowTimer(60.0); //таймер
		}
	}
}

void CreatePlantation(aref loc)
{
	if(CheckAttribute(loc,"type") && loc.type == "Plantation")
	{
	    if(LAi_IsCapturedLocation) // fix нефиг грузить, когда город трупов или боевка
		{
			return;
		}
		if (GetNpcQuestPastDayWOInit(loc, "Plantation_date") < 2) return;

		int iColony = -1;
		int iNation = -1;

		string sAreal = GiveArealByLocation(loc);
		if (sAreal == "none") return;
		
		string sCity = GetCityNameByIsland(sAreal);
		if (sCity == "none") return;
		
	    iColony = FindColony(sCity);

		if(iColony == -1)
		{
			return;
		}

		iNation = GetCityNation(sCity);

		if(iNation == -1)
		{
			return;
		}
		
		SaveCurrentNpcQuestDateParam(loc, "Plantation_date");
		int iCitizensQuantity, iModel;
		ref chr;
		aref st;
		int iChar, i, iSex;
		string slai_group, locatorName, sType;
	    slai_group = GetNationNameByType(iNation)  + "_citizens";
		int num, iMassive, iRank;
		string sAnime;
		string model[10];
	    
	    	// ==> просто работники
			model[0] = "prizon_1";
			model[1] = "prizon_2";
			model[2] = "prizon_3";
			model[3] = "prizon_4";
			model[4] = "prizon_5";
			model[5] = "prizon_6";
			model[6] = "prizon_7";
			model[7] = "prizon_8";
			model[8] = "prizon_3";
			model[9] = "prizon_4";
			i = 0;
			num = rand(3) + 7; //кол-во
			while(i < num)
			{
				iMassive = rand(9);
				if (model[iMassive] != "")
				{
					sAnime = "man_B"
					if(model[iMassive] == "prison_5") sAnime = "man2";
					chr = GetCharacter(NPC_GenerateCharacter("Slave_"+i, model[iMassive], "man", sAnime, 7, iNation, 2, false, "slave"));

					chr.dialog.filename = "Quest\ForAll_dialog.c";
					chr.dialog.currentnode = "plantation_slave";
					
	                chr.greeting = "convict";
	                chr.CityType = "citizen";
					chr.city = Colonies[iColony].id;
					LAi_SetLoginTime(chr, 6.0, 22.99);

					PlaceCharacter(chr, "goto", "random_free");
					LAi_SetCitizenType(chr);
					LAi_group_MoveCharacter(chr, slai_group);
					i++;
					model[iMassive] = "";
				}
			}

		// солдаты -->
		if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
		{
	 		if(iNation == PIRATE)
			{
	            sType = "mushketer_" + (rand(4)+1);
			}
			else
			{
	            sType = "mush_" + NationShortName(iNation) + "_" + (rand(2)+1);
			}
			chr = GetCharacter(NPC_GenerateCharacter("GenChar_", sType, "man", "mushketer", sti(pchar.rank), iNation, 2, false, "soldier"));
			chr.id = "GenChar_" + chr.index;	
			chr.reputation.nobility = (1 + rand(44) + rand(44));// репа всем горожанам
			chr.City = Colonies[iColony].id;
	        chr.CityType = "soldier";
			chr.greeting = "soldier";
			chr.MusketerDistance = 0;
			LAi_SetLoginTime(chr, 6.0, 23.0); //а ночью будет беготня от патруля :)

			LAi_SetPatrolType(chr);
	        if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "pirat_guard";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";   
			ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", "soldier1");
		}
		// солдаты <--
		// патруль -->
		if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
		{
			makearef(st, loc.locators.patrol);
			iCitizensQuantity = GetAttributesNum(st);
			if(iCitizensQuantity > 10)
			{
				iCitizensQuantity = 10;
			}
			for (i=0; i<iCitizensQuantity-3; i++)
			{
	            if(iNation != PIRATE && LAi_IsCapturedLocation == 0)
				{
	                sType = "soldier";
					iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
				}
				else
				{
	                sType = "pirate";
					iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 2);
				}
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, MAN);
				chr.City = Colonies[iColony].id;
	            chr.CityType = "soldier";
	            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
				chr.RebirthPhantom = true;
				LAi_CharacterReincarnation(chr, true, true);
				LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
				LAi_SetLoginTime(chr, 0.0, 24.0);
				LAi_SetPatrolType(chr);

	            if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					chr.greeting = "town_pirate";
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
					chr.greeting = "soldier";
				}
				PlaceCharacter(chr, "patrol", "random_free");			
	            chr.dialog.filename = "Common_Soldier.c";            
				chr.dialog.currentnode = "first time";
			}
		}
		// патруль <--
		// грузчики -->
		if (loc.type == "town" && CheckAttribute(loc, "carrier") && IsLoginTime())
		{
			int iTemp;
			int iQtyCarrier = rand(2) + 2;
			string locReload[5];
			locReload[0] = "houseSp1";
			locReload[1] = "houseS1";
			locReload[2] = "houseF1";
			locReload[3] = "houseF2";
			locReload[4] = "houseS2";
			string CarrierName[10];
			CarrierName[0] = "GenresBag1";
			CarrierName[1] = "GenresBag2";
			CarrierName[2] = "GenresBarrel1";
			CarrierName[3] = "GenresBarrel2";
			CarrierName[4] = "GenresBarrelTop1";
			CarrierName[5] = "GenresBarrelTop2";
			CarrierName[6] = "GenresBottle1";
			CarrierName[7] = "GenresBottle2";
			CarrierName[8] = "GenresChest1";
			CarrierName[9] = "GenresChest2";
			for (i=iQtyCarrier; i>0; i--)
			{
				//выберем уникальную для этой локации модельку
				iSex = 1;
				while (iSex == 1)
				{
					iTemp = rand(9);
					if (CarrierName[iTemp] != "") iSex = 0;
				}
				chr = GetCharacter(NPC_GenerateCharacter("Carrier", CarrierName[iTemp], "man", "genres", 35, iNation, 2, false, "slave"));
				chr.id = chr.id + "_" + chr.index;
				aref aLocator;
				makearef(aLocator, loc.locators.reload);
				CarrierName[iTemp] = ""; //имя модельки уберем из списка
				LAi_SetImmortal(chr, true);
				iSex = 1;
				while (iSex == 1)
				{
					iTemp = rand(4);
					if (CheckAttribute(aLocator, locReload[iTemp]) && locReload[iTemp] != "")
					{
						chr.firstLoc = locReload[iTemp];
						chr.firstLoc.timer = rand(7) + 3;
						locReload[iTemp] = "";
						iSex = 0;
					}
				}
				ChangeCharacterAddressGroup(chr, loc.id, "reload", "gate");
				LAi_SetCarrierType(chr);
				LAi_SetLoginTime(chr, 6.0, 23.0);
				LAi_group_MoveCharacter(chr, slai_group);
			}
		}
		// грузчики <--
	}	
}

void CreateItzaLand(aref loc)
{
	if(CheckAttribute(loc, "ItzaLand") && !bBettaTestMode)
	{
		ref chr;
		aref grp;
		int iMassive, warriorRank, i, num;	
		string model[10];
		string encGroup, str, locator;
		
		encGroup = LAi_FindRandomLocator("encdetector");
		str = "locators." + encGroup;
		makearef(grp, loc.(str));
		num = GetAttributesNum(grp);
		
		if(num == 0 ) return;
		if(num > 10) num = 10;
		
		LAi_group_Delete("tayasal_monsters_group");
		
		model[0] = "Itza_1";
		model[1] = "Itza_2";
		model[2] = "Itza_3";
		model[3] = "Itza_4";
		model[4] = "Itza_5";	
		model[5] = "Itza_6";
		model[6] = "Itza_7";
		model[7] = "Itza_8";
		model[8] = "Itza_4";
		model[9] = "Itza_6";	
		
		i = 0;
		
		chrDisableReloadToLocation = true;
		
		//определим ранг войнов. обработаем от сложности, но не менее 20 уровня
		warriorRank = GetCoffDiff(sti(pchar.rank), 1000) + MOD_SKILL_ENEMY_RATE;
		if (warriorRank < 20) warriorRank = 20;
		
		while(i < num)
		{
			iMassive = rand(9);
			if (model[iMassive] != "")
			{
				chr = GetCharacter(NPC_GenerateCharacter("AztecWarrior" + loc.index + "_" + i, model[iMassive], "man", "man_A1", warriorRank, PIRATE, 0, true, "itza"));
				FantomMakeCoolFighter(chr, warriorRank, 80 + rand(20), 80 + rand(20), LinkRandPhrase("topor_01","blade_01","blade_02"),"","", 50);
				TakeNItems(chr,"potion2", rand(3)+1);
				SetCharacterPerk(chr, "Energaiser"); 
				
				locator = GetAttributeName(GetAttributeN(grp, i));
				ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
				
				LAi_SetWarriorType(chr);
				LAi_warrior_SetStay(chr, true);
				LAi_warrior_DialogEnable(chr, false);
				LAi_group_MoveCharacter(chr, "tayasal_monsters_group");
				i++;
				model[iMassive] = "";
			}
		}
		LAi_group_SetRelation("tayasal_monsters_group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);	
		LAi_group_FightGroups("tayasal_monsters_group", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("tayasal_monsters_group", "OpenTheDoors");		
	}
}
