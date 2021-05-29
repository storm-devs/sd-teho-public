// Warship. Доведенный до ума интерфейс бумажной карты из К3. Теперь это интерфейс отличной карты.
// espkk # ActiveMap 1.3 # 25/Sep/2017 - map with trade assistant for Sea Dogs: TEHO / Теперь действительно доведенный до ума =) 

//settings file
#include "activemap_settings.h"

//changing this requires frame resizing
#define TRADEASSISTANT_MAXGOODS 5

///espkk. utils -->
void AddImageToImageList(string sImgName, string sPicGroup, string sPic, float X, float Y, int Width, int Height)
{
	GameInterface.MAP.imagelist.(sImgName).group = sPicGroup;
	GameInterface.MAP.imagelist.(sImgName).pic = sPic;
	GameInterface.MAP.imagelist.(sImgName).x = X;
	GameInterface.MAP.imagelist.(sImgName).y = Y;
	GameInterface.MAP.imagelist.(sImgName).width = Width;
	GameInterface.MAP.imagelist.(sImgName).height = Height;
}

//Whether on worldmap or not. Supports Hook's mod position fix
void GetCorrectShipCoords(ref X, ref Y)
{
	if(IsEntity(&worldMap))
	{
		X = sti(worldMap.playerShipX);
		Y = -sti(worldMap.playerShipZ);
	}
		else
	{
		// Compability with Hook's mod (LDH 14Mar17 add check for on dock, display last ship location before docking)
		// this cannot be implemented without modifying sea.c
		if (!bSeaActive && CheckAttribute(pchar, "shipx"))
		{
			X = GetSeaShipX(stf(pchar.shipx));
			Y = -GetSeaShipZ(stf(pchar.shipz));
		}
		else
		{
			X = GetSeaShipX(stf(pchar.Ship.Pos.X));
			Y = -GetSeaShipZ(stf(pchar.Ship.Pos.Z));
		}
	}
	
	X+=1000;
	Y+=1000;
}

//Correct version of GetDistanceToColony2D
int _GetDistanceToColony2D(string _sColony)
{
	ref rColony = GetColonyRefByID(_sColony);
	string sColonyIslandID = rColony.Island;
	string sColonyTown = _sColony + "_town";

	if(_sColony == "FortOrange") sColonyTown = "Shore36";
	if(_sColony == "LaVega") sColonyTown = "LaVega_Port";

	float X1, Z1;
	GetCorrectShipCoords(&X1, &Z1)
	float X2 = makefloat(worldMap.islands.(sColonyIslandID).(sColonyTown).position.x)+1000;
	float Z2 = -makefloat(worldMap.islands.(sColonyIslandID).(sColonyTown).position.z)+1000;
	
	return makeint(GetDistance2D(X1, Z1, X2, Z2));
}
///espkk. utils <--

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
		if(sColony == "Is") continue;
		if(sColony == "IslaMona" && GetCharacterIndex("Islamona_carpenter") < 0) continue;

		if(sColony == "IslaMona")
			sPic = "Smuggler";
		else
			sPic = GetNationNameByType(sti(rColony.nation));
			
		if(sColony != "FortOrange" && sColony != "LaVega" && sColony != "IslaMona")
		{
			X = makefloat(worldMap.islands.(sColonyIslandID).(sColonyTown).position.x)+1000;
			Y = -makefloat(worldMap.islands.(sColonyIslandID).(sColonyTown).position.z)+1000;
		}
		
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
				
		if(sColony == "IslaMona")
		{
			X = 1000;
			Y = 829;
		}
	
		//Draw colony on the map
		AddImageToImageList(sColony, "NATIONS_SMALL", sPic, X, Y, 16, 16);

		ref chref;
		for (int iChar=1; iChar<MAX_CHARACTERS; iChar++)
		{
			makeref(chref, Characters[iChar]);
			
			//Draw packhouses
			if (CheckAttribute(chref, "Storage.Activate"))
			{
				if (sColony == chref.city)
				{
					AddImageToImageList(sColony + "_storage", "ICONS", "ship capacity icon", X, Y + 50, 13, 13);
				}
			}
			
			//Draw ships
    		if (CheckAttribute(chref, "ShipInStockMan"))
    		{
				bool bIslaMonaShip = (sColony == "IslaMona") && (chref.ShipInStockMan == "Islamona_carpenter"); //stupid compiler >:|
                if (chref.ShipInStockMan == (sColony + "_PortMan") || bIslaMonaShip) 
				{
					AddImageToImageList(sColony + "_shipinstock", "ICONS_SPEC", "ship button", X - 35, Y, 24, 24);
				}
			}
		}
		
		//Draw our moneylenders
		aref quests;
		int  nQuestsNum, n;
		string sQuestName, sType;
		for(int iType=0; iType<2; iType++)
		{
			if(iType)
				sType = "Quest.Loans";
			else
				sType = "Quest.Deposits";

			if (CheckAttribute(pchar, sType))
			{
				makearef(quests, pchar.(sType));
				nQuestsNum = GetAttributesNum(quests);

				for(n = 0; n < nQuestsNum; n++)
				{
					sQuestName = GetAttributeName(GetAttributeN(quests,n));
					if (sColony == Pchar.Quest.Deposits.(sQuestName).City)
					{
						AddImageToImageList(sColony + "_money", "ICONS", "commerce skill icon", X, Y - 55, 13, 13);

						iType = 2; //stop for
						break;
					}
				}
			}
		}
		
		//Draw sieges
		if(CheckAttribute(rColony, "siege") && sti(rColony.siege) != -1)
		{
			sSiegeCol = "SiegeOn" + sColony;
			AddImageToImageList(sSiegeCol, "ICONS_SPEC", "weapon button", X + 35, Y - 3, 20, 20);
			
			if(CheckAttribute(NullCharacter, "siege.nation"))
			{
				string sSiegeNation = GetNationNameByType(sti(NullCharacter.Siege.nation));
				sSiegeCol = sSiegeCol + "NationPic" + sSiegeNation;
				AddImageToImageList(sSiegeCol, "NATIONS_SMALL", sSiegeNation, X + 70, Y, 16, 16);
			}
		}
	}
	
	//Draw our ship
	GetCorrectShipCoords(&X, &Y);
	AddImageToImageList("PShip", "ICONS", "ship class icon", X, Y, 20, 20);

	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, "RESOURCE\INI\INTERFACES\MapBest.ini");
	
	//Show boundaries
	if(SHOW_BOUNDARIES == 1)
	{
		SetNewPicture("BOUNDARIES", "interfaces\maps\map_good_boundaries.tga");
		SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"BOUNDARIES", 4, 
			argb(makeint(255/(makefloat(100)/BOUNDARIES_OPACITY)), BOUNDARIES_R, BOUNDARIES_G, BOUNDARIES_B));
	}
	
	CreateString(true,"DateTime", GetDateString() + " " + GetTimeString(), FONT_CAPTION, COLOR_NORMAL, 170, 10, SCRIPT_ALIGN_CENTER, 0.8);
	CreateString(true,"ProvisionsInfo", XI_ConvertString("Food for") + CalculateShipFood(pchar) + "/" + CalculateShipRum(pchar) + XI_ConvertString("days") + 
		" (" + XI_ConvertString("FoodAcc") + "/" + XI_ConvertString("RumAcc") + ")", FONT_CAPTION, COLOR_NORMAL, 630, 10, SCRIPT_ALIGN_CENTER, 0.8);

	SetEventHandler("InterfaceBreak","ProcessExit",0);
	SetEventHandler("exitCancel","ProcessExit",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("SelectRColony","SelectRColony",0);
	SetEventHandler("MouseRClickUP","HideRColony",0);
}

void ProcessExit()
{
	IDoExit(-1);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessExit");
	DelEventHandler("exitCancel","ProcessExit");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("SelectRColony","SelectRColony");
	DelEventHandler("MouseRClickUP","HideRColony");

	if(CheckAttribute(pchar, "ShowBestMap")) { // Смотрим из меню
		DeleteAttribute(pchar, "ShowBestMap");
		interfaceResultCommand = RC_INTERFACE_TO_ITEMS;
	} else {
	interfaceResultCommand = exitCode;
	}
	
	EndCancelInterface(true);
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
	
	//Getting correct image offsets
	float fOffsetX, fOffsetY;
	GetXYWindowOffset(&fOffsetX, &fOffsetY);

	fMouseX = (fMouseX - fOffsetX) * stf(GameInterface.MAP.scale.x);
	fMouseY = (fMouseY - fOffsetY) * stf(GameInterface.MAP.scale.y);

	//Check if clicked on colony
	string sColony;
	for(int i = 0; i < MAX_COLONIES; i++)
	{
		sColony = colonies[i].id;
		if(CheckAttribute(&GameInterface, "MAP.imagelist." + sColony))
		{
			// LDH 21Mar17 enlarge click spot by 10 each direction
			if(fMouseX >= stf(GameInterface.MAP.imagelist.(sColony).x) + 20)	// 30
			{
				if(fMouseX <= stf(GameInterface.MAP.imagelist.(sColony).x) + 60.0)	// 50
				{
					if(fMouseY >= stf(GameInterface.MAP.imagelist.(sColony).y - 10))	// 0
					{
						if(fMouseY <= stf(GameInterface.MAP.imagelist.(sColony).y) + 60.0)	// 50
						{
							if(sColony != "Panama" && sColony != "IslaMona")
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
	string sText;
	ref sld, rColony;
	rColony = &colonies[iColony];
	string sColony = colonies[iColony].id;
	int iColor;

	//Clean up -->
	sText = XI_ConvertString("Colony" + sColony);
	SetFormatedText("INFO_CAPTION", sText);

	sText = GetNationNameByType(sti(rColony.nation));
	SetNewGroupPicture("INFO_NATION_PICTURE", "NATIONS", sText);

	SetFormatedText("EXPORT_CAPTION", GetConvertStr("EXPORT", "activemap.txt"));
	SetFormatedText("IMPORT_CAPTION", GetConvertStr("IMPORT", "activemap.txt"));
	SetFormatedText("CONTRABAND_CAPTION", GetConvertStr("CONTRABAND", "activemap.txt"));
	SetFormatedText("AGGRESSIVE_CAPTION", "");
	SetFormatedText("COLONY_INFO", "");
	SetFormatedText("COLONY_INFO_TEXT", "");
	SetFormatedText("COLONY_INFO_TEXT2", "");
	SetFormatedText("COLONY_INFO_SIEGE", "");
	SetFormatedText("TRADEASSISTANT_CAPTION", "");
	SetFormatedText("TRADEASSISTANT_TO", "");
	SetFormatedText("TRADEASSISTANT_FROM", "");	
	SetFormatedText("TRADEASSISTANT_PRICES1", "");
	SetFormatedText("TRADEASSISTANT_PRICES2", "");	
	SetFormatedText("TRADEASSISTANT_SPECIAL", "");

	SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"GOODS_PICTURES", 2 ); 
	//Clean up <--
	
	//Time to travel
	//Thanks to LDH
	sText = XI_ConvertString("ColonyDistance") + " - ";
	
	if(TRAVELTIME_MODE == 0)
	{
		int iDays1 = makeint(_GetDistanceToColony2D(sColony)/300 + 0.5); //min - sailing on deck
		int iDays2 = makeint(_GetDistanceToColony2D(sColony)/100 + 0.5); //max - worldmap

		if (iDays1 < 1)	iDays1 = 1;
		if (iDays2 < 1) iDays2 = 1;
		
		if (iDays1 == iDays2) {
			sText += iDays1 + " ";
			if(iDays2%10 == 1) {
				sText += GetConvertStr("day2", "activemap.txt");
			} else {
				sText += GetConvertStr("days", "activemap.txt");
			}
		} else {
			sText += GetConvertStr("TRAVEL_from", "activemap.txt") + " " + iDays1 + " " + GetConvertStr("TRAVEL_to", "activemap.txt") + " " + iDays2 + " " + GetConvertStr("days", "activemap.txt");
		}
		sText+=".";
	}
	else
	{
		int iDistance;
		
		if(TRAVELTIME_MODE == 1)
		{
			iDistance = makeint(_GetDistanceToColony2D(sColony)/6.5 + 0.5)
			
			sText = GetConvertStr("Distance", "activemap.txt") + " = " + iDistance + " ";
			if (iDistance == 1)
			{
				sText += GetConvertStr("nautical_mile", "activemap.txt");
			}
			else 
			{
				if(iDistance%10 == 1)
				{
					sText += GetConvertStr("nautical_mile2", "activemap.txt");
				}
				else
				{
					bool lc1 = iDistance%100 < 10 || iDistance%100 > 20;
					if(lc1 && iDistance%10 > 1 && iDistance%10 < 5)
						sText += GetConvertStr("nautical_miles2", "activemap.txt");
					else
						sText += GetConvertStr("nautical_miles", "activemap.txt");
				}
			}
            // LDH 12Jul17 - add direction
            sText += " " + GetMapDir16(_GetDirToColony(sColony));
            sText += " (" + GetMapDir32(_GetDirToColony(sColony)) + ")";
			sText += ".";
		}
		else
		{
			float AverageSpeed = TRAVELTIME_AVERAGE_SPEED;
			if (iArcadeSails == 0) AverageSpeed *= 0.7;
			iDistance = makeint(_GetDistanceToColony2D(sColony)/(TRAVELTIME_AVERAGE_SPEED * 6.5) + 0.5)
			
			sText += iDistance + " ";
			if (iDistance == 1)
			{
				sText += GetConvertStr("hour", "activemap.txt");
			}
			else
			{
				if (iDistance%10 == 1)
				{
					sText += GetConvertStr("hour", "activemap.txt");
				}
				else
				{
					bool lc2 = iDistance%100 < 10 || iDistance%100 > 20;
					if(lc2 && iDistance%10 > 1 && iDistance%10 < 5)
						sText += GetConvertStr("hours2", "activemap.txt");
					else
						sText += GetConvertStr("hours", "activemap.txt");
				}
			}
			sText += ".";
		}
	}
	SetFormatedText("COLONY_TRAVEL_INFO", sText);
	
	//Colony info
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
		AddLineToFormatedText("COLONY_INFO_TEXT", sText);
		SetFormattedTextLastLineColor("COLONY_INFO_TEXT", argb(255,255,168,168));
	}
	
	///Draw categorized goods
	int iGood = -1;
	string sGood = "";
	int iIsland = FindIsland(rColony.Island);
	
	int i, iType;
	int iGoods_x, iGoods_y;
	string sGoodNum, sType;
	
	for(iType=0; iType<4; iType++)
	{
		i = 1;
		sGoodNum = "id" + i;
		iGoods_x = 410;
		
		switch(iType)
		{
		case 0:
			sType = "Trade.Export";
			iGoods_y = 245;
			break;
		case 1:
			sType = "Trade.Import";
			iGoods_y = 330;
			break;
		case 2:
			sType = "Trade.Contraband";
			iGoods_y = 415;
			break;
		case 3:
			sType = "Trade.Aggressive";
			iGoods_y = 470;
			break;	
		}
		
		while(CheckAttribute(islands[iIsland], sType + "." + sGoodNum))
		{
			iColor = argb(255,196,196,255);
			iGood = islands[iIsland].(sType).(sGoodNum);
			sGood = goods[iGood].name;
			SendMessage( &GameInterface,"lslslllll",MSG_INTERFACE_MSG_TO_NODE,"GOODS_PICTURES", 0,
				sGood, argb(255, 128, 128, 128), iGoods_x,iGoods_y,iGoods_x+28,iGoods_y+28 );
			
			if(i%6)
				iGoods_x+=28;
			else
			{
				iGoods_y+=28;
				iGoods_x=410;
			}
			
			i++;
			sGoodNum = "id" + i;
		}
		
		if(iType == 3 && i > 1)
			SetFormatedText("AGGRESSIVE_CAPTION", GetConvertStr("AGGRESSIVE", "activemap.txt"));
	}
	
	///Trade assistant
	string sTown = GetCurrentTown();
	
	if(sTown == "" || sTown == sColony)
		return;
	
	SetFormatedText("TRADEASSISTANT_CAPTION", "Trade assistant");
	
	//Find town in trade book
	bool bFound = true; 
	if(TRADEASSISTANT_MODE == 0)
	{
		aref rootItems;
		makearef(rootItems, NullCharacter.PriceList);
		bFound = CheckAttribute(rootItems, sColony);
	}
	
	if(!bFound)
	{
		SetFormatedText("TRADEASSISTANT_SPECIAL", GetConvertStr("No_price", "activemap.txt"));
		return;
	}
		
	//Find our store
	ref refStore, refStore2;
	aref arefStore2, refGoods;
	for(i = 0; i < STORE_QUANTITY; i++)
	{
		makeref(refStore, Stores[i]);
		if (refStore.colony == sTown)
			break;
	}	
	//Find target store
	if(TRADEASSISTANT_MODE == 0)
	{
		makearef(arefStore2, NullCharacter.PriceList.(sColony));
	}
	else
	{
		for(i = 0; i < STORE_QUANTITY; i++)
		{		
			makeref(refStore2, Stores[i]);
			if (refStore2.colony == sColony)
					break;
		}		
	}
	
	float a_fMax[TRADEASSISTANT_MAXGOODS];
	int a_iMax[TRADEASSISTANT_MAXGOODS];
	float fTemp;
	int nSell, nBuy;
	
	bFound = false; //at least one good displayed
	
	//Calculate profit
	for(iType=0; iType<2; iType++)
	{
		if(iType)
		{
			iGoods_x = 310;
			iColor = argb(255,196,255,196);
		}
		else
		{
			iGoods_x = 230;
			iColor = argb(255,196,196,255);
		}
		
		for(i=0; i<TRADEASSISTANT_MAXGOODS-1; i++)
			a_fMax[i] = 0.;

		for (i = GOOD_BALLS; i < GOOD_SHIPSILK; i++) //Skip Shipsilk, Ropes, Sandal, Oil, Gold, Silver, Cannons
		{
			sGood = Goods[i].name;
			if(refStore.Goods.(sGood).TradeType == T_TYPE_CONTRABAND)
				continue;
			
			if(TRADEASSISTANT_MODE == 1)
			{
				if(refStore2.Goods.(sGood).TradeType == T_TYPE_CONTRABAND)
					continue;
			}		
			else
			{
				sGood = "Gidx" + i;
				
				if(arefStore2.(sGood).TradeType == T_TYPE_CONTRABAND)
					continue;
			}	
			
			if(iType == 0)
			{
				nBuy = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_BUY, pchar, 1);
				if(TRADEASSISTANT_MODE == 0)
					nSell = arefStore2.(sGood).Sell;
				else
					nSell = GetStoreGoodsPrice(refStore2, i, PRICE_TYPE_SELL, pchar, 1);
			}
			else
			{
				nSell = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_SELL, pchar, 1);
				if(TRADEASSISTANT_MODE == 0)
					nBuy = arefStore2.(sGood).Buy;
				else
					nBuy = GetStoreGoodsPrice(refStore2, i, PRICE_TYPE_BUY, pchar, 1);
			}
			
			fTemp = (nSell - nBuy) / stf(Goods[i].weight); //price per pound
			
			//Sort
			for(int k=0; k<TRADEASSISTANT_MAXGOODS; k++)
			{
				if(fTemp > a_fMax[k])
				{
					for(int j=TRADEASSISTANT_MAXGOODS-1; j>k; j--)
					{
						a_fMax[j] = a_fMax[j-1];
						a_iMax[j] = a_iMax[j-1];
					}
					a_fMax[k] = fTemp;
					a_iMax[k] = i;
					break;
				}
			}
		}
		
		//Draw goods
		iGoods_y = 395;
		for(i=0; i<TRADEASSISTANT_MAXGOODS; i++)
		{
			if(!a_fMax[i])
				break;
			
			AddLineToFormatedText("TRADEASSISTANT_PRICES" + (iType+1), FloatToString(a_fMax[i], 1));
			SetFormattedTextLastLineColor("TRADEASSISTANT_PRICES" + (iType+1), iColor);
			
			SendMessage( &GameInterface,"lslslllll",MSG_INTERFACE_MSG_TO_NODE,"GOODS_PICTURES", 0,
				Goods[a_iMax[i]].name, argb(255, 128, 128, 128), iGoods_x,iGoods_y,iGoods_x+28,iGoods_y+28 );
			iGoods_y+=28;
			
			bFound = true;
		}
	}
	
	if(bFound)
	{
		SetFormatedText("TRADEASSISTANT_TO", GetConvertStr("To", "activemap.txt"));
		SetFormatedText("TRADEASSISTANT_FROM", GetConvertStr("From", "activemap.txt"));
	}
	else
	{
		SetFormatedText("TRADEASSISTANT_SPECIAL", GetConvertStr("No_profit", "activemap.txt"));
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
// LDH 12Jul17 compass directions -->
string GetMapDir16(float dir)      // N, NNE, NE
{
	dir = Normalize360(Radian2Degree(dir));
	int index = makeint((dir / 22.5) + 0.5);   // round to nearest compass16 point
	if (index >= 16) index = 0;

	switch (index)
	{
	    case  0: return "N"; break;
	    case  1: return "NNE"; break;
	    case  2: return "NE"; break;
	    case  3: return "ENE"; break;
	    case  4: return "E"; break;
	    case  5: return "ESE"; break;
	    case  6: return "SE"; break;
	    case  7: return "SSE"; break;
	    case  8: return "S"; break;
	    case  9: return "SSW"; break;
	    case 10: return "SW"; break;
	    case 11: return "WSW"; break;
	    case 12: return "W"; break;
	    case 13: return "WNW"; break;
	    case 14: return "NW"; break;
	    case 15: return "NNW"; break;
	}
}

string GetMapDir32(float dir)      // N, NbE, NNE
{
	dir = Normalize360(Radian2Degree(dir));
	int index = makeint((dir / 11.25) + 0.5);   // round to nearest compass32 point
	if (index >= 32) index = 0;

	switch (index)
	{
	    case  0: return "N"; break;
	    case  1: return "NbE"; break;
	    case  2: return "NNE"; break;
	    case  3: return "NEbN"; break;
	    case  4: return "NE"; break;
	    case  5: return "NEbE"; break;
	    case  6: return "ENE"; break;
	    case  7: return "EbN"; break;
	    case  8: return "E"; break;
	    case  9: return "EbS"; break;
	    case 10: return "ESE"; break;
	    case 11: return "SEbE"; break;
	    case 12: return "SE"; break;
	    case 13: return "SEbS"; break;
	    case 14: return "SSE"; break;
	    case 15: return "SbE"; break;
	    case 16: return "S"; break;
	    case 17: return "SbW"; break;
	    case 18: return "SSW"; break;
	    case 19: return "SWbS"; break;
	    case 20: return "SW"; break;
	    case 21: return "SWbW"; break;
	    case 22: return "WSW"; break;
	    case 23: return "WbS"; break;
	    case 24: return "W"; break;
	    case 25: return "WbN"; break;
	    case 26: return "WNW"; break;
	    case 27: return "NWbW"; break;
	    case 28: return "NW"; break;
	    case 29: return "NWbN"; break;
	    case 30: return "NNW"; break;
	    case 31: return "NbW"; break;
	}
}

float _GetDirToColony(string _sColony)
{
	ref rColony = GetColonyRefByID(_sColony);
	string sColonyIslandID = rColony.Island;
	string sColonyTown = _sColony + "_town";

	if(_sColony == "FortOrange") sColonyTown = "Shore36";
	if(_sColony == "LaVega") sColonyTown = "LaVega_Port";

	float X1, Z1;
	GetCorrectShipCoords(&X1, &Z1)
	float X2 = makefloat(worldMap.islands.(sColonyIslandID).(sColonyTown).position.x)+1000;
	float Z2 = -makefloat(worldMap.islands.(sColonyIslandID).(sColonyTown).position.z)+1000;
    
    if (Z2 > Z1)
        return PI + atan((X1-X2)/(Z2-Z1));
    else
        return atan((X1-X2)/(Z2-Z1));

}

float Normalize360(float dir)
{
    if (dir < 0.0) dir += 360.0;
    if (dir > 360.0) dir -= 360.0;
    return dir;
}
// LDH 12Jul17 <-									 