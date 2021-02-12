// Ugeen && Warship --> интерфейс картографического атласа

ref xi_refCharacter; 
string CurRow;
int iSelected = 1; // курсор в таблице
int iStartX = 20;
int iStartY = 62;
int iLengthX = 580;//606;
int iLengthY = 520;//542 

void InitInterface(string iniName)
{
	GameInterface.title = "titleMapView";
	
	xi_refCharacter = pchar;
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("SelectRColony","SelectRColony",0);
	SetEventHandler("MouseRClickUP", "HideRColony",0);
		
	FillMapsTable();
}

void ProcessBreakExit()
{
	IDoExit(-1);
}

void ProcessCancelExit()
{
	IDoExit(-1);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("SelectRColony","SelectRColony");
	DelEventHandler("MouseRClickUP", "HideRColony");

	// По всему файлу мне лень править, а здесь оно тоже будет работать прекрасно
	if(CheckAttribute(PChar, "ShowMapsAtlas")) // Смотрим из меню
	{
		DeleteAttribute(PChar, "ShowMapsAtlas");
		interfaceResultCommand = RC_INTERFACE_TO_ITEMS;
	}
	else
	{
		interfaceResultCommand = exitCode;
	}
	
	EndCancelInterface(true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();
		
	switch(nodName)
	{
		case "TABLE_MAPS":
			if(comName == "click")
			{
				nodName = "TABLE_MAPS";
			}
		break;
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void FillMapsTable() 
{
	int n, i;
	string row;
	string sGood, selectedId = "";
	int  idLngFile;
	bool ok = true;
	aref rootItems, arItem;
	aref  curItem;
		
	n = 1;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");	
	if(CheckAttribute(pchar, "showlastmap")) { selectedId = pchar.showlastmap; }
	
	GameInterface.TABLE_MAPS.hr.td1.str = "";
	SetFormatedText("STR_1", XI_ConvertString("Select map"));
	Table_UpdateWindow("TABLE_MAPS");

	// Заполним картами
	makearef(rootItems, xi_refCharacter.Items);
    for (i=0; i<GetAttributesNum(rootItems); i++)
    {
		curItem = GetAttributeN(rootItems, i);
		if (Items_FindItem(GetAttributeName(curItem), &arItem)>=0 )
		{
			row = "tr" + n;
			sGood = arItem.id;			
			if(CheckAttribute(arItem,"mapType"))
			{
				if(arItem.mapType == "") ok = true;
				else					 ok = false;
			}
			if (arItem.ItemType != "MAP" || !ok) continue;			

			if (selectedId == sGood) { iSelected = n; }			
			if (GetCharacterItem(xi_refCharacter, sGood) > 0)
			{					
				GameInterface.TABLE_MAPS.(row).index = GetItemIndex(arItem.id);				
				//GameInterface.TABLE_MAPS.(row).td1.icon.group = arItem.picTexture;
				//GameInterface.TABLE_MAPS.(row).td1.icon.image = "itm" + arItem.picIndex;
				//GameInterface.TABLE_MAPS.(row).td1.icon.offset = "0, 0";
				//GameInterface.TABLE_MAPS.(row).td1.icon.width = 30;
				//GameInterface.TABLE_MAPS.(row).td1.icon.height = 30;
				//GameInterface.TABLE_MAPS.(row).td1.textoffset = "31,0";
				GameInterface.TABLE_MAPS.(row).td1.textoffset = "1,0";
				GameInterface.TABLE_MAPS.(row).td1.str = LanguageConvertString(idLngFile, arItem.name);
				GameInterface.TABLE_MAPS.(row).td1.scale = 0.72;				
				n++;							
			}
		}		
    }		
	GameInterface.TABLE_MAPS.select = iSelected;
	CurRow   =  "tr" + (iSelected);    
	SetNewMapPicture();
		
	Table_UpdateWindow("TABLE_MAPS");
	LanguageCloseFile(idLngFile);
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurRow   =  "tr" + (iSelected);    
    SetNewMapPicture();
}

void SetNewMapPicture()
{
	int  iGoodIndex = sti(GameInterface.TABLE_MAPS.(CurRow).index);
	ref itmRef = &Items[iGoodIndex];
	
	if (CheckAttribute(itmRef, "groupID"))
	{
		string itmGroup = itmRef.groupID;
		if (itmGroup == MAPS_ITEM_TYPE)
		{
			SetNewPicture("MAP", "interfaces\Maps\" + itmRef.imageTga + ".tga");
			pchar.showlastmap = itmRef.id;							
		}
	}	
} 

void ShowInfoWindow()
{
	int  iGoodIndex = sti(GameInterface.TABLE_MAPS.(CurRow).index);
	ref  itmRef = &Items[iGoodIndex];
	int  idLngFile;

	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup = itmRef.picTexture; 
	string sGroupPicture = "itm" + itmRef.picIndex

	sPicture = "-1";

	idLngFile = LanguageOpenFile("ItemsDescribe.txt");	
	sHeader = LanguageConvertString(idLngFile, itmRef.name);
	sText1  = GetItemDescribe(iGoodIndex); 
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
	LanguageCloseFile(idLngFile);
}

void HideInfoWindow()
{
	CloseTooltip();
}

void SelectRColony()
{	
	float X, Y;
	int   X1, Y1;

	float fMouseX = stf(GameInterface.mousepos.x);
	float fMouseY = stf(GameInterface.mousepos.y);
			
	string sColony;
	ref rColony;
	
	int  iGoodIndex = sti(GameInterface.TABLE_MAPS.(CurRow).index);
	ref  itmRef = &Items[iGoodIndex];
	
	if(itmRef.id != "Map_Best") return;

	for(int i = 0; i < MAX_COLONIES; i++)
	{
		sColony = colonies[i].id;
		rColony = &colonies[i];
		
		string sColonyIslandID = rColony.Island;
		string sColonyTown = sColony + "_town";

		if(sColony == "Pearl") continue;
		if(sColony == "Tenotchitlan") continue;
		if(sColony == "Dominica") continue;
		if(sColony == "Terks") continue;
		if(sColony == "Caiman") continue;
		if(sColony == "LostShipsCity") continue;
				
		if(sColony != "FortOrange" && sColony != "LaVega")
		{
			X = makefloat(worldMap.islands.(sColonyIslandID).(sColonyTown).position.x)+1000;
			Y = -makefloat(worldMap.islands.(sColonyIslandID).(sColonyTown).position.z)+1000;
		}
		
		// Оранж и Ла-Вегу придется выставлять ручками
		if(sColony == "FortOrange")
		{
			X = 600;
			Y = 1080;
		}
		
		if(sColony == "LaVega")
		{
			X = 1150;
			Y = 350;
		}

		X1 = makeint(X * iLengthX/2048) + iStartX;
		Y1 = makeint(Y * iLengthY/2048) + iStartY;
		
		if(fMouseX >= X1 - 10.0)
		{
			if(fMouseX <= X1 + 10.0)
			{
				if(fMouseY >= Y1 - 10.0)
				{
					if(fMouseY <= Y1 + 10.0)
					{
						if(sColony != "Tenotchitlan" && sColony != "Pearl" && sColony != "Panama")
						{
							XI_WindowDisable("MAIN_WINDOW", true);
							XI_WindowDisable("INFO_WINDOW", false);
							XI_WindowShow("INFO_WINDOW", true);
							ShowColonyInfo(i);
						}
					}
				}
			}
		}				
	}	
}

void HideRColony()
{
	XI_WindowDisable("MAIN_WINDOW", false);
	XI_WindowDisable("INFO_WINDOW", true);
	XI_WindowShow("INFO_WINDOW", false);
}

void ShowColonyInfo(int iColony)
{
	// "COLONY_INFO_TEXT" - названия, "COLONY_INFO_TEXT2" - значения
	string sText;
	ref sld, rColony;
	rColony = &colonies[iColony];
	string sColony = colonies[iColony].id;
	int iColor;

	sText = XI_ConvertString("Colony" + sColony);
	SetFormatedText("INFO_CAPTION", sText);

	sText = GetNationNameByType(sti(rColony.nation));
	SetNewGroupPicture("INFO_NATION_PICTURE", "NATIONS", sText);

	SetFormatedText("COLONY_INFO", "");
	SetFormatedText("COLONY_INFO_TEXT", "");
	SetFormatedText("COLONY_INFO_TEXT2", "");
	SetFormatedText("COLONY_INFO_SIEGE", "");
	SetFormatedText("IMPORT_CAPTION", XI_ConvertString("IMPORTING:"));
	SetFormatedText("EXPORT_CAPTION", XI_ConvertString("EXPORTING:"));
	SetFormattedTextLastLineColor("IMPORT_CAPTION", argb(255,196,196,255));
	SetFormattedTextLastLineColor("EXPORT_CAPTION", argb(255,196,255,196));
	
	int iDays = makeint(GetDistanceToColony2D(sColony)/100);
	if(iDays <= 0) iDays = 1;
	sText = XI_ConvertString("ColonyDistance") + " - " + iDays + " " + XI_ConvertString("day1") + ".";
	SetFormatedText("COLONY_TRAVEL_INFO", sText);
	
//	ref rFC = CharacterFromID(sColony + " Fort Commander");
//	DumpAttributes(rColony);

	sText = XI_ConvertString("ColonyInfo");
	AddLineToFormatedText("COLONY_INFO_LABEL", sText);
	
	sText = XI_ConvertString("SalaryQuantity");
	AddLineToFormatedText("COLONY_INFO_TEXT", sText);
	sText = sti(colonies[iColony].ship.crew.quantity);
	AddLineToFormatedText("COLONY_INFO_TEXT2", sText);
	sText = XI_ConvertString("Fort");
	AddLineToFormatedText("COLONY_INFO_TEXT", sText);

	if(!CheckAttribute(rColony, "HasNoFort"))
	{
		sText = XI_ConvertString("FortYes");
		AddLineToFormatedText("COLONY_INFO_TEXT2", sText);

		sld = CharacterFromID(sColony + " Fort Commander");
		sText = XI_ConvertString("CrewQuantity");
		AddLineToFormatedText("COLONY_INFO_TEXT", sText);
		sText = sti(sld.ship.crew.quantity);
		AddLineToFormatedText("COLONY_INFO_TEXT2", sText);

		sText = XI_ConvertString("Quantity_info");
		AddLineToFormatedText("COLONY_INFO_TEXT", sText);
		sText = GetMaxFortCannons(sld.id);
		AddLineToFormatedText("COLONY_INFO_TEXT2", sText);
	}
	else
	{
		sText = XI_ConvertString("FortNo");
		AddLineToFormatedText("COLONY_INFO_TEXT2", sText);
	}
	
	if(CheckAttribute(rColony, "siege"))
	{
		sText = XI_ConvertString("ThisColonySiege");
		AddLineToFormatedText("COLONY_INFO_SIEGE", sText);
	}

	SetFormatedText("IMPORT_INFO", "");
	SetFormatedText("EXPORT_INFO", "");
	
	int iGood = -1;
	string sGood = "";
	int iIsland = FindIsland(rColony.Island);

	for(int i=1; i<=3; i++)
	{
		string sGoodNum = "id" + i;
		// Импорт
		if(CheckAttribute(islands[iIsland], "Trade.Import." + sGoodNum))
		{
			iColor = argb(255,196,196,255);
			iGood = islands[iIsland].Trade.Import.(sGoodNum);
			sGood = goods[iGood].name;
			SetNewGroupPicture("IMPORT" + i + "_PICTURE", "GOODS", sGood);
		
			sGood = XI_ConvertString(sGood);
			AddLineToFormatedText("IMPORT_INFO", sGood);
			SetFormattedTextLastLineColor("IMPORT_INFO", iColor);
		}
		else
		{
			SetNewGroupPicture("IMPORT" + i + "_PICTURE", "", "");
		}
		
		// Экспорт
		if(CheckAttribute(islands[iIsland], "Trade.Export." + sGoodNum)) // Если есть. На Бермудах третьего товара нету.
		{
			iColor = argb(255,196,255,196);
			iGood = islands[iIsland].Trade.Export.(sGoodNum);
			sGood = goods[iGood].name;
			SetNewGroupPicture("EXPORT" + i + "_PICTURE", "GOODS", sGood);
			
			sGood = XI_ConvertString(sGood);
			AddLineToFormatedText("EXPORT_INFO", sGood);
			SetFormattedTextLastLineColor("EXPORT_INFO", iColor);
		}
		else
		{
			SetNewGroupPicture("EXPORT" + i + "_PICTURE", "", "");
		}
	}
}

int GetMaxFortCannons(string _FortCommander)
{
	int _iCannons = 0;
	switch(_FortCommander)
	{
		case "Bridgetown Fort Commander": _iCannons = 39; break;
			
		case "SentJons Fort Commander": _iCannons = 103; break;
			
		case "SanJuan Fort Commander": _iCannons = 45; break;
			
		case "Charles Fort Commander": _iCannons = 157; break;
			
		case "Marigo Fort Commander": _iCannons = 161; break;
			
		case "BasTer Fort Commander": _iCannons = 82; break;
			
		case "FortFrance Fort Commander": _iCannons = 92; break;
			
		case "Villemstad Fort Commander": _iCannons = 76; break;
			
		case "PortSpein Fort Commander": _iCannons = 83; break;
			
		case "Cumana Fort Commander": _iCannons = 80; break;
			
		case "Caracas Fort Commander": _iCannons = 164; break;
			
		case "Maracaibo Fort Commander": _iCannons = 70; break;
			
		case "Cartahena Fort Commander": _iCannons = 85; break;
			
		case "PortoBello Fort Commander": _iCannons = 82; break;
			
		case "SantaCatalina Fort Commander": _iCannons = 164; break;
			
		case "Beliz Fort Commander": _iCannons = 80; break;
			
		case "PortRoyal Fort Commander": _iCannons = 204; break;
			
		case "PortPax Fort Commander": _iCannons = 179; break;
			
		case "SantoDomingo Fort Commander": _iCannons = 128; break;
			
		case "Santiago Fort Commander": _iCannons = 128; break;
			
		case "Tortuga Fort Commander": _iCannons = 28; break;
			
		case "Havana Fort Commander": _iCannons = 80; break;
	}
	
	return _iCannons;
}
