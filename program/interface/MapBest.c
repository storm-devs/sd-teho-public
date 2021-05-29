// Warship. Доведенный до ума интерфейс бумажной карты из К3. Теперь это интерфейс отличной карты.

void InitInterface(string iniName)
{
	GameInterface.title = "titlePaperMap";

	string sColony, sPic, sPicGroup, sSiegeCol;
	int Width, Height;
	float X, Y;
	ref rColony;

	for(int i=0; i<MAX_COLONIES; i++)
	{
		rColony = &colonies[i];
		sColony = rColony.id;
		
		string sColonyIslandID = rColony.Island;
		string sColonyTown = sColony + "_town";
		
		if(sColony == "Pearl") continue;
		if(sColony == "Tenotchitlan") continue;
		if(sColony == "Dominica") continue;
		if(sColony == "Terks") continue;
		if(sColony == "Caiman") continue;
		if(sColony == "LostShipsCity") continue;
		if(sColony == "KhaelRoa") continue;
		if(sColony == "Minentown") continue;
		if(sColony == "Ksochitam") continue;
		if(sColony == "RockIsland") continue;
		if(sColony == "SantaQuiteria") continue;
		if(sColony == "IslaDeVieques") continue;
		if(sColony == "SanAndres") continue;

		if(rColony.nation != "none")
			sPic = GetNationNameByType(sti(rColony.nation));
		else
			sPic = "Pirate";
			
		sPicGroup = "NATIONS_SMALL";
		Width = 16;
		Height = 16;
		
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
		
		/*if(sColony == "Tenotchitlan")
		{
			sPicGroup = "ICONS_SPEC";
			Width = 30;
			Height = 30;
			sPic = "fencing skill icon";
		}
		
		if(sColony == "Pearl")
		{
			sPicGroup = "GOODS";
			Width = 30;
			Height = 30;
			sPic = "Grapes";
		}*/
		
		GameInterface.MAP.imagelist.(sColony).group = sPicGroup;
		GameInterface.MAP.imagelist.(sColony).width = Width;
		GameInterface.MAP.imagelist.(sColony).height = Height;
		GameInterface.MAP.imagelist.(sColony).x = X;
		GameInterface.MAP.imagelist.(sColony).y = Y;
		GameInterface.MAP.imagelist.(sColony).pic = sPic;

		if(CheckAttribute(rColony, "siege") && sti(rColony.siege) != -1)
		{
			sSiegeCol = rColony.id;
			sSiegeCol = "SiegeOn" + sSiegeCol;
			GameInterface.MAP.imagelist.(sSiegeCol).group = "ICONS_SPEC";
			GameInterface.MAP.imagelist.(sSiegeCol).x = X + 35;
			GameInterface.MAP.imagelist.(sSiegeCol).y = Y - 3;
			GameInterface.MAP.imagelist.(sSiegeCol).pic = "weapon button";
			GameInterface.MAP.imagelist.(sSiegeCol).width = 20;
			GameInterface.MAP.imagelist.(sSiegeCol).height = 20;
			
			if(CheckAttribute(NullCharacter, "siege.nation"))
			{
				string sSiegeNation = GetNationNameByType(sti(NullCharacter.Siege.nation));
				sSiegeCol = sSiegeCol + "NationPic" + sSiegeNation;
				GameInterface.MAP.imagelist.(sSiegeCol).group = "NATIONS_SMALL";
				GameInterface.MAP.imagelist.(sSiegeCol).x = X + 70;
				GameInterface.MAP.imagelist.(sSiegeCol).y = Y;
				GameInterface.MAP.imagelist.(sSiegeCol).pic = sSiegeNation;
				GameInterface.MAP.imagelist.(sSiegeCol).width = 16;
				GameInterface.MAP.imagelist.(sSiegeCol).height = 16;
			}
		}
	}
	
	X = sti(worldMap.playerShipX)+1000;
	Y = -sti(worldMap.playerShipZ)+980;
	
	GameInterface.MAP.imagelist.PShip.group = "ICONS";
	GameInterface.MAP.imagelist.PShip.x = X;
	GameInterface.MAP.imagelist.PShip.y = Y;
	GameInterface.MAP.imagelist.PShip.pic = "ship class icon";
	GameInterface.MAP.imagelist.PShip.width = 25;
	GameInterface.MAP.imagelist.PShip.height = 23;
		
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	CreateString(true,"GameVersionInfo1", VERSION_NUMBER1, FONT_CAPTION, COLOR_NORMAL,170, 10, SCRIPT_ALIGN_CENTER, 0.8);
	CreateString(true,"GameVersionInfo2", GetVerNum(), FONT_CAPTION, COLOR_NORMAL, 630, 10, SCRIPT_ALIGN_CENTER, 0.8);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("SelectRColony","SelectRColony",0);
	SetEventHandler("MouseRClickUP", "HideRColony",0);
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
	DelEventHandler("SelectRColony","SelectRColony");
	DelEventHandler("MouseRClickUP", "HideRColony");

	// По всему файлу мне лень править, а здесь оно тоже будет работать прекрасно
	if(CheckAttribute(PChar, "ShowBestMap")) // Смотрим из меню
	{
		DeleteAttribute(PChar, "ShowBestMap");
		interfaceResultCommand = RC_INTERFACE_TO_ITEMS;
	}
	else // Warship fix 09.07.09 Надо так, иначе выходило не в интерфейс
	{
	if(CheckAttribute(PChar, "ShowBestMapAtlas")) // Смотрим из атласа
	{
		DeleteAttribute(PChar, "ShowBestMap");
		interfaceResultCommand = RC_INTERFACE_MAPVIEW;
	}	
	else
	{
		interfaceResultCommand = exitCode;
	}
	}
	
	EndCancelInterface(true);
}

void ProcCommand()
{

}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void SelectRColony()
{	
	float fMouseX = stf(GameInterface.mousepos.x) - 6.0 + 5;
	float fMouseY = stf(GameInterface.mousepos.y) - 50.0 + 5;

	//определяем верхний левый угол картинки
	float fOffsetX = stf(GameInterface.MAP.offset.x);
	float fOffsetY = stf(GameInterface.MAP.offset.y);

	fMouseX = fOffsetX + fMouseX * stf(GameInterface.MAP.scale.x);
	fMouseY = fOffsetY + fMouseY * stf(GameInterface.MAP.scale.y);

	string sColony;
	for(int i = 0; i < MAX_COLONIES; i++)
	{
		sColony = colonies[i].id;
		if(CheckAttribute(&GameInterface, "MAP.imagelist." + sColony))
		{
			if(fMouseX >= stf(GameInterface.MAP.imagelist.(sColony).x) + 30)
			{
				if(fMouseX <= stf(GameInterface.MAP.imagelist.(sColony).x) + 50.0)
				{
					if(fMouseY >= stf(GameInterface.MAP.imagelist.(sColony).y))
					{
						if(fMouseY <= stf(GameInterface.MAP.imagelist.(sColony).y) + 50.0)
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
		if(CheckAttribute(colonies[iColony], "Trade.Import." + sGoodNum))
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
		if(CheckAttribute(colonies[iColony], "Trade.Export." + sGoodNum)) // Если есть. На Бермудах третьего товара нету.
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