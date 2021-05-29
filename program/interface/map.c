string totalInfo = "";
bool isSkipable = false;
bool bEncType   = false;
bool bShowVideo; // для показа квестовых роликов, если будут
bool bEscDisable = false; // belamour для выхода из меню на ESC BigPatch
string  sQuestSeaCharId = "";

void InitInterface(string iniName)
{
	EngineLayersOffOn(true);
	SetTimeScale(0.0);
	
	// лочим квест и карту
    bQuestCheckProcessFreeze = true;
    bEncType = false; // обычный тип
    bShowVideo = false;
    
    GameInterface.title = "title_map";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

    SetFormatedText("MAP_CAPTION", XI_ConvertString("title_map"));

	SetFormatedText("INFO_TEXT_QUESTION", XI_ConvertString("MapWhatYouWantToDo"));

	SetCurrentNode("INFO_TEXT_QUESTION");
	
	CalculateInfoData();

	SetFormatedText("INFO_TEXT",totalInfo);

	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);
	
	SetEventHandler("InterfaceBreak","ProcessBreakExit",0); // Выход на море
	SetEventHandler("exitCancel","ProcessCancelExit",0); // Выход на море по крестику или Esc
	SetEventHandler("ievnt_command","ProcCommand",0); // выход на карту только тут (по НЕТ)
	SetEventHandler("evntDoPostExit","DoPostExit",0); // выход из интерфейса
	
	EI_CreateFrame("INFO_BORDERS", 250,152,550,342);
	PlaySound("interface\_EvShip"+rand(1)+".wav");
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_MAP_EXIT );
	wdmReloadToSea();
}

void ProcessCancelExit()
{
	//IDoExit( RC_INTERFACE_MAP_EXIT );
	//wdmReloadToSea();
	
	//belamour выход через ESC -->
	if (!bEscDisable) 
	{ 
		pchar.SkipEshipIndex = pchar.eshipIndex; 
		IDoExit(RC_INTERFACE_MAP_EXIT);
	}
	//<-- belamour BigPatch
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	
    SetTimeScale(1.0);
	TimeScaleCounter = 0; //boal
	if(IsPerkIntoList("TimeSpeed"))
	{	
		DelPerkFromActiveList("TimeSpeed");
	}
	
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
	
	PostEvent("StopQuestCheckProcessFreeze", 100);//boal 230804 заморозка проверки квестов
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	
	switch(nodName)
	{
		case "B_OK":
			if(comName=="activate" || comName=="click")
			{
				if (sQuestSeaCharId != "")
				{
					wdmEnterSeaQuest(sQuestSeaCharId);
				}
				// напасть
				IDoExit(RC_INTERFACE_MAP_EXIT);
				wdmReloadToSea();
			}
			if(comName=="downstep")
			{
				if(GetSelectable("B_CANCEL"))	{SetCurrentNode("B_CANCEL");}
			}
		break;

		case "B_CANCEL":
			if(comName=="activate" || comName=="click")
			{
				//пропустить
				//PostEvent("evntDoPostExit",1,"l",RC_INTERFACE_MAP_EXIT);
				pchar.SkipEshipIndex = pchar.eshipIndex;
				IDoExit(RC_INTERFACE_MAP_EXIT);
			}	
			if(comName=="upstep")
			{
				if(GetSelectable("B_OK"))	{SetCurrentNode("B_OK");}
			}
		break;
	}
}
void wdmRecalcReloadToSea()
{
	worldMap.encounter.type = "";
	totalInfo = "";
	string loadScr = "";
	int iRand;
	//Encounters
	int numEncounters = wdmGetNumberShipEncounters();
	int isShipEncounterType = 0;
	//Log_TestInfo("Начинаем перебирать энкаунтеров");
	for(int i = 0; i < numEncounters; i++)
	{
		if(wdmSetCurrentShipData(i))
		{
			if(MakeInt(worldMap.encounter.select) == 0) continue;
			isShipEncounterType++;
						
			string encID = worldMap.encounter.id;
			
			aref rEncounter;
			makearef(rEncounter, worldMap.encounters.(encID).encdata);

			int iRealEncounterType = sti(rEncounter.RealEncounterType);

			if (isShipEncounterType > 1 && iRealEncounterType < ENCOUNTER_TYPE_BARREL)
			{
			    totalInfo = totalInfo + XI_ConvertString("But in the same way");
			}

			int iNumMerchantShips = 0;
			int iNumWarShips = 0;
			if(CheckAttribute(rEncounter, "NumMerchantShips"))
			{
				iNumMerchantShips = sti(rEncounter.NumMerchantShips);
			}
			if(CheckAttribute(rEncounter, "NumWarShips"))
			{
				iNumWarShips = sti(rEncounter.NumWarShips);
			}

			if (CheckAttribute(rEncounter, "CharacterID"))
			{
                iNumWarShips = GetCharacterIndex(rEncounter.CharacterID);
                if (iNumWarShips != -1)
                {
					sQuestSeaCharId = characters[iNumWarShips].id; // квестовый 
					if (CheckAttribute(&characters[iNumWarShips], "mapEnc.Name"))
					{
						totalInfo = totalInfo + characters[iNumWarShips].mapEnc.Name;
					}
					else
					{
						totalInfo = totalInfo + "'" + characters[iNumWarShips].ship.name + "'."
					}
				}
				bEncType = true;
			}
			else
			{
				if(iRealEncounterType <= ENCOUNTER_TYPE_MERCHANT_LARGE)
				{
					totalInfo = totalInfo + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("of traders");
				}
				
				if(iRealEncounterType >= ENCOUNTER_TYPE_MERCHANT_GUARD_SMALL && iRealEncounterType <= ENCOUNTER_TYPE_MERCHANT_GUARD_LARGE)
				{
					totalInfo = totalInfo + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("merchants in accompaniment") + GetTextOnSecondShipsQuantity(iNumWarShips) + XI_ConvertString("guards");
				}
				
				if(iRealEncounterType >= ENCOUNTER_TYPE_ESCORT_SMALL && iRealEncounterType <= ENCOUNTER_TYPE_ESCORT_LARGE)
				{
					totalInfo = totalInfo + XI_ConvertString("Trade caravan") + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("merchants in accompaniment") + GetTextOnSecondShipsQuantity(iNumWarShips) + XI_ConvertString("guards");
				}
				
				if(iRealEncounterType == ENCOUNTER_TYPE_MERCHANT_CROWN)
				{
					totalInfo = totalInfo + XI_ConvertString("Crown caravan") + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("merchants in accompaniment") + GetTextOnSecondShipsQuantity(iNumWarShips) + XI_ConvertString("guards");
				}
				
				if(iRealEncounterType == ENCOUNTER_TYPE_MERCHANT_EXPEDITION)
				{
					totalInfo = totalInfo + XI_ConvertString("Trade expedition") + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("merchants in accompaniment") + GetTextOnSecondShipsQuantity(iNumWarShips) + XI_ConvertString("guards");
				}

				if(iRealEncounterType >= ENCOUNTER_TYPE_PATROL_SMALL && iRealEncounterType <= ENCOUNTER_TYPE_PATROL_LARGE)
				{
					totalInfo = totalInfo + XI_ConvertString("Patrol") + GetTextOnShipsQuantity(iNumWarShips);
				}

				if(iRealEncounterType >= ENCOUNTER_TYPE_PIRATE_SMALL && iRealEncounterType <= ENCOUNTER_TYPE_PIRATE_SCOUNDREL)
				{
					totalInfo = totalInfo + XI_ConvertString("Pirates") + GetTextOnShipsQuantity(iNumWarShips);
				}

				if(iRealEncounterType >= ENCOUNTER_TYPE_SQUADRON && iRealEncounterType <= ENCOUNTER_TYPE_ARMADA)
				{
					totalInfo = totalInfo + XI_ConvertString("Naval squadron") + GetTextOnShipsQuantity(iNumWarShips);
				}

				if(iRealEncounterType == ENCOUNTER_TYPE_CROWN_ARMADA)
				{
					totalInfo = totalInfo + XI_ConvertString("Crown Armada") + GetTextOnShipsQuantity(iNumWarShips);
				}
				
				if(iRealEncounterType == ENCOUNTER_TYPE_PUNITIVE_SQUADRON)
				{
					totalInfo = totalInfo + XI_ConvertString("Punitive expedition") + GetTextOnShipsQuantity(iNumWarShips);
				}

				if(iRealEncounterType == ENCOUNTER_TYPE_WAR_PRIVATEER)
				{
					totalInfo = totalInfo + XI_ConvertString("Privateer") + GetTextOnShipsQuantity(iNumWarShips);
				}
				
				if(iRealEncounterType == ENCOUNTER_TYPE_BARREL)
				{
					totalInfo = totalInfo + XI_ConvertString("SailingItems");
				}
			
				if(iRealEncounterType == ENCOUNTER_TYPE_BOAT)
				{
					totalInfo = totalInfo + XI_ConvertString("ShipWreck");
				}				
			}
			
			if(sti(rEncounter.Nation) < 0)
			{
        		totalInfo = totalInfo + "БАГА -1.";
      		}
	        
			if(iRealEncounterType != ENCOUNTER_TYPE_BARREL && iRealEncounterType != ENCOUNTER_TYPE_BOAT)
			{
				switch(sti(rEncounter.Nation))
				{		        
					case ENGLAND:		
						totalInfo = totalInfo + XI_ConvertString("under english flag");
					break;
					case FRANCE:		
						totalInfo = totalInfo + XI_ConvertString("under french flag");
					break;
					case SPAIN:		
						totalInfo = totalInfo + XI_ConvertString("under spanish flag");
					break;
					case HOLLAND:		
						totalInfo = totalInfo + XI_ConvertString("under dutch flag");
					break;
					case PIRATE:		
						totalInfo = totalInfo + ".";
					break;
				}
			}	

			if(GetNationRelation2MainCharacter(sti(rEncounter.Nation)) != RELATION_ENEMY)
			{
				isSkipable = true;
			}
		}
	}
	//Log_TestInfo("isShipEncounterType :" + isShipEncounterType);
	
	if (isShipEncounterType > 1)
	{
		switch (rand(1))
		{
			case 0 :
				if(IsDay()) loadScr = "loading\sea_1.tga";
				else		loadScr = "loading\sea_2.tga";
			break;
			case 1 :
				loadScr = "loading\sea_3.tga";
			break;
		}
		SetNewPicture("INFO_PICTURE", loadScr); 
		totalInfo = XI_ConvertString("NavalSignal") + XI_ConvertString("battle on course") + totalInfo;
	}
	else
	{
		if(iRealEncounterType == ENCOUNTER_TYPE_BARREL || iRealEncounterType == ENCOUNTER_TYPE_BOAT)
		{		
			if(iRealEncounterType == ENCOUNTER_TYPE_BARREL) 
			{
				SetNewPicture("INFO_PICTURE", "loading\polundra.tga"); 
			}	
			if(iRealEncounterType == ENCOUNTER_TYPE_BOAT) 
			{
				SetNewPicture("INFO_PICTURE", "loading\flplndra.tga"); 
			}			
			totalInfo = XI_ConvertString("NavalSignal") + XI_ConvertString("SpecialSituation") + totalInfo;
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_OK",0, "#"+XI_ConvertString("GetItemToBort"));
		}
		else
		{
			switch (rand(1))
			{
				case 0 :
					if(IsDay()) loadScr = "loading\sea_1.tga";
					else		loadScr = "loading\sea_2.tga";
				break;
				case 1 :
					loadScr = "loading\sea_3.tga";
				break;
			}

			SetNewPicture("INFO_PICTURE", loadScr); 
			totalInfo = XI_ConvertString("NavalSignal") + XI_ConvertString("someone sails") + totalInfo;
		}	
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void CalculateInfoData()
{
    wdmRecalcReloadToSea();
    
	if (pchar.space_press == "1")
	{
		isSkipable = true;
	}
	SetCurrentNode("B_OK");
		
    SetSelectable("B_CANCEL",true);

        if (!isSkipable && !bBettaTestMode)
        {
        	if (CheckOfficersPerk(pchar, "SailingProfessional"))
        	{
			if (rand(100) > 75) {SetSelectable("B_CANCEL",false); bEscDisable = true;} // belamour BigPatch
        	}
		else
		{
			if (rand(100) > 25) {SetSelectable("B_CANCEL",false); bEscDisable = true;} // belamour BigPatch
        }
	}
	if (pchar.space_press == "1") bEncType = false;
	
	if (bEncType && !bBettaTestMode) // спец тип не пропустить
	{
        SetSelectable("B_CANCEL",false);
		bEscDisable = true; // belamour BigPatch
	}
	pchar.space_press = 0;
}