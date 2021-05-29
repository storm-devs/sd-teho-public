/// BOAL меню торговли
string CurTable, CurRow;

void InitInterface(string iniName)
{
    InterfaceStack.SelectMenu_node = "LaunchTradeBook"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleTradeBook";
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("TableSelectChange", "TableSelectChange", 0);
    SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
    SetEventHandler("MouseRClickUp","HideInfoWindow",0);
    
    XI_RegistryExitKey("IExit_F2");
// LDH 06Jul17 
    if (SORT_PRICELIST)
        FillPriceListTownSorted("TABLE_CITY");
    else
    FillPriceListTown("TABLE_CITY");
}

void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("TableSelectChange", "TableSelectChange");
    DelEventHandler("ShowInfoWindow","ShowInfoWindow");
    DelEventHandler("MouseRClickUp","HideInfoWindow");
    
	interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
        DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		EndCancelInterface(true);
	}
}
void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
    switch(nodName)
	{
		case "I_CHARACTER_2":
			if(comName=="click")
			{
			    nodName = "I_CHARACTER";
			}
		break;
		case "I_SHIP_2":
			if(comName=="click")
			{
			    nodName = "I_SHIP";
			}
		break;
		case "I_QUESTBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_QUESTBOOK";
			}
		break;
		case "I_TRADEBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_TRADEBOOK";
			}
		break;
		case "I_NATIONS_2":
			if(comName=="click")
			{
			    nodName = "I_NATIONS";
			}
		break;
		case "I_ITEMS_2":
			if(comName=="click")
			{
			    nodName = "I_ITEMS";
			}
		break;
	}
	// boal new menu 31.12.04 -->
	if (nodName == "I_CHARACTER" || nodName == "I_SHIP" ||
	    nodName == "I_QUESTBOOK" || nodName == "I_TRADEBOOK" ||
		nodName == "I_NATIONS" || nodName == "I_ITEMS")
	{
		if(comName=="click")
		{
            InterfaceStates.ReloadMenuExit = true;
			IDoExit(RC_INTERFACE_ANY_EXIT);
			PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			return;
		}
	}
	// boal new menu 31.12.04 -->
}
//  таблица: город, местоположение, актуальность
void FillPriceListTown(string _tabName)
{
	string  cityId, attr2, firstId;
    int     i, cn, n;
    ref     nulChr;
    string  row;
    aref    rootItems;
    aref    curItem;
    ref     rCity;
    
    // шапка -->
    GameInterface.(_tabName).select = 0;
    GameInterface.(_tabName).hr.td1.str = "Нация";
    GameInterface.(_tabName).hr.td1.scale = 0.77
	GameInterface.(_tabName).hr.td2.str = "Город";
	GameInterface.(_tabName).hr.td2.scale = 0.8;
	GameInterface.(_tabName).hr.td3.str = "Местоположение";
	GameInterface.(_tabName).hr.td3.scale = 0.7;
	GameInterface.(_tabName).hr.td4.str = "Актуальность";
	GameInterface.(_tabName).hr.td4.scale = 0.7;
    // <--
    nulChr = &NullCharacter;
    makearef(rootItems, nulChr.PriceList);  // тут живут ИД города и служ. инфа.
    n = 1;
    firstId = "";
    for (i=0; i<GetAttributesNum(rootItems); i++)
    {
        row = "tr" + n;
		curItem = GetAttributeN(rootItems, i);
		cityId = GetAttributeName(curItem);
        row = "tr" + n;	
		cn = FindColony(cityId);
		if (cn != -1)
		{
			rCity = GetColonyByIndex(cn);
			if (n == 1) firstId = cityId;
			GameInterface.(_tabName).(row).UserData.CityID  = cityId;
			GameInterface.(_tabName).(row).UserData.CityIDX = cn;
			GameInterface.(_tabName).(row).td1.icon.group  = "NATIONS";
			GameInterface.(_tabName).(row).td1.icon.image  = Nations[sti(rCity.nation)].Name;
			GameInterface.(_tabName).(row).td1.icon.width  = 26;
		    GameInterface.(_tabName).(row).td1.icon.height = 26;
		    GameInterface.(_tabName).(row).td1.icon.offset = "0, 3";
			GameInterface.(_tabName).(row).td2.str = GetConvertStr(cityId + " Town", "LocLables.txt");
			GameInterface.(_tabName).(row).td2.scale = 0.85;
			GameInterface.(_tabName).(row).td3.str = GetConvertStr(rCity.islandLable, "LocLables.txt");
			GameInterface.(_tabName).(row).td3.scale = 0.8;
			GameInterface.(_tabName).(row).td4.scale = 0.75;
			if (CheckAttribute(nulChr, "PriceList." + cityId + ".AltDate"))
		    {
		        GameInterface.(_tabName).(row).td4.str = nulChr.PriceList.(cityId).AltDate;
		    }
		    else
		    {
		        GameInterface.(_tabName).(row).td4.str = "??.??.????";
		    }
			n++;
		}
	}
	//if (n > 1) GameInterface.(_tabName).select = 1;
	Table_UpdateWindow(_tabName);
	FillPriceList("TABLE_GOODS", firstId);
}

// LDH 06Jul17 
#define MAX_OURCOLONIES 42
void FillPriceListTownSorted(string _tabName)
{
	string  cityId, attr2, firstId;
    int     i, cn, n;
    ref     nulChr;
    string  row;
    aref    rootItems;
    aref    curItem;
    ref     rCity;

// LDH 06Jul17 -->
    string OurColonies[MAX_OURCOLONIES];
    i = 0;
    OurColonies[i] = "Havana";          i = i + 1;
    OurColonies[i] = "Santiago";        i = i + 1;
    OurColonies[i] = "PuertoPrincipe";  i = i + 1;
    OurColonies[i] = "PortRoyal";       i = i + 1;
    OurColonies[i] = "FortOrange";      i = i + 1;
    OurColonies[i] = "Tortuga";         i = i + 1;
    OurColonies[i] = "PortPax";         i = i + 1;
    OurColonies[i] = "SantoDomingo";    i = i + 1;
    OurColonies[i] = "LaVega";          i = i + 1;
    OurColonies[i] = "Terks";           i = i + 1;
    OurColonies[i] = "SanJuan";         i = i + 1;
    OurColonies[i] = "Pirates";         i = i + 1;
    OurColonies[i] = "Marigo";          i = i + 1;
    OurColonies[i] = "Charles";         i = i + 1;
    OurColonies[i] = "SentJons";        i = i + 1;
    OurColonies[i] = "BasTer";          i = i + 1;
    OurColonies[i] = "Dominica";        i = i + 1;
    OurColonies[i] = "FortFrance";      i = i + 1;
    OurColonies[i] = "LeFransua";       i = i + 1;
    OurColonies[i] = "Bridgetown";      i = i + 1;
    OurColonies[i] = "Villemstad";      i = i + 1;
    OurColonies[i] = "PortSpein";       i = i + 1;
    OurColonies[i] = "Cumana";          i = i + 1;
    OurColonies[i] = "Caracas";         i = i + 1;
    OurColonies[i] = "Maracaibo";       i = i + 1;
    OurColonies[i] = "Cartahena";       i = i + 1;
    OurColonies[i] = "PortoBello";      i = i + 1;
    OurColonies[i] = "Panama";          i = i + 1;
    OurColonies[i] = "Pearl";           i = i + 1;
    OurColonies[i] = "SantaCatalina";   i = i + 1;  // Blueweld
    OurColonies[i] = "Beliz";           i = i + 1;
    OurColonies[i] = "Caiman";          i = i + 1;
    
    OurColonies[i] = "Tenotchitlan";    i = i + 1;
    OurColonies[i] = "Minentown";       i = i + 1;
    OurColonies[i] = "LostShipsCity";   i = i + 1;
    OurColonies[i] = "KhaelRoa";        i = i + 1;
    OurColonies[i] = "Ksochitam";       i = i + 1;
    OurColonies[i] = "RockIsland";      i = i + 1;
    OurColonies[i] = "SantaQuiteria";   i = i + 1;
    OurColonies[i] = "IslaDeVieques";   i = i + 1;
    OurColonies[i] = "Is";              i = i + 1;
    OurColonies[i] = "SanAndres";

// LDH 06Jul17 <--
    
    // шапка -->
    GameInterface.(_tabName).select = 0;
    GameInterface.(_tabName).hr.td1.str = "Нация";
    GameInterface.(_tabName).hr.td1.scale = 0.77
	GameInterface.(_tabName).hr.td2.str = "Город";
	GameInterface.(_tabName).hr.td2.scale = 0.8;
	GameInterface.(_tabName).hr.td3.str = "Местоположение";
	GameInterface.(_tabName).hr.td3.scale = 0.7;
	GameInterface.(_tabName).hr.td4.str = "Актуальность";
	GameInterface.(_tabName).hr.td4.scale = 0.7;
    // <--
    nulChr = &NullCharacter;
    makearef(rootItems, nulChr.PriceList);  // тут живут ИД города и служ. инфа.
    n = 1;
    firstId = "";
// LDH 06Jul17 -->
    for (i=0; i<MAX_OURCOLONIES; i++)   
    {
		bool bFound = false;
		for (int j=0; j<GetAttributesNum(rootItems); j++)
		{
			curItem = GetAttributeN(rootItems, j);
			cityId = GetAttributeName(curItem);
			
			if(cityId == OurColonies[i])
			{
				bFound = true;
				break;
			}
		}
		
		if(!bFound)
			continue;
// LDH 06Jul17 <--

        row = "tr" + n;	
		cn = FindColony(cityId);
		if (cn != -1)
		{
			rCity = GetColonyByIndex(cn);
			if (n == 1) firstId = cityId;
			GameInterface.(_tabName).(row).UserData.CityID  = cityId;
			GameInterface.(_tabName).(row).UserData.CityIDX = cn;
			GameInterface.(_tabName).(row).td1.icon.group  = "NATIONS";
			GameInterface.(_tabName).(row).td1.icon.image  = Nations[sti(rCity.nation)].Name;
			GameInterface.(_tabName).(row).td1.icon.width  = 26;
		    GameInterface.(_tabName).(row).td1.icon.height = 26;
		    GameInterface.(_tabName).(row).td1.icon.offset = "0, 3";
			GameInterface.(_tabName).(row).td2.str = GetConvertStr(cityId + " Town", "LocLables.txt");
			GameInterface.(_tabName).(row).td2.scale = 0.85;
			GameInterface.(_tabName).(row).td3.str = GetConvertStr(rCity.islandLable, "LocLables.txt");
			GameInterface.(_tabName).(row).td3.scale = 0.8;
			GameInterface.(_tabName).(row).td4.scale = 0.75;
			if (CheckAttribute(nulChr, "PriceList." + cityId + ".AltDate"))
		    {
		        GameInterface.(_tabName).(row).td4.str = nulChr.PriceList.(cityId).AltDate;
		    }
		    else
		    {
		        GameInterface.(_tabName).(row).td4.str = "??.??.????";
		    }
			n++;
		}
	}
	//if (n > 1) GameInterface.(_tabName).select = 1;
	Table_UpdateWindow(_tabName);
	FillPriceList("TABLE_GOODS", firstId);
}
//  таблица
// картинка, название, картинка экспорта, продажа, покупка, колво, пачка, вес пачки
void FillPriceList(string _tabName, string  attr1)
{
    string  sGoods;
    int     i, n;
    ref     nulChr;
    string  row;
    nulChr = &NullCharacter;
    // шапка -->
    GameInterface.(_tabName).select = 0;
    GameInterface.(_tabName).hr.td1.str = XI_ConvertString("Good name");
    GameInterface.(_tabName).hr.td1.scale = 0.8;
    GameInterface.(_tabName).hr.td2.str = "Тип";
    GameInterface.(_tabName).hr.td2.scale = 0.85;
	GameInterface.(_tabName).hr.td3.str = XI_ConvertString("Price sell");
	GameInterface.(_tabName).hr.td3.scale = 0.8;
	GameInterface.(_tabName).hr.td4.str = XI_ConvertString("Price buy");
	GameInterface.(_tabName).hr.td4.scale = 0.8;
	GameInterface.(_tabName).hr.td5.str = XI_ConvertString("In the store");
	GameInterface.(_tabName).hr.td5.scale = 0.8;
	GameInterface.(_tabName).hr.td6.str = "Пачка";
	GameInterface.(_tabName).hr.td6.scale = 0.8;
	GameInterface.(_tabName).hr.td7.str = "Вес пачки";
	GameInterface.(_tabName).hr.td7.scale = 0.8;
	if (attr1 != "")
	{
	    // <--
	    n = 1;
	    for (i = 0; i < GOODS_QUANTITY; i++)
	    {
	        row = "tr" + n;
	        sGoods = "Gidx" + i;			
	        if (sti(nulChr.PriceList.(attr1).(sGoods).TradeType) == T_TYPE_CANNONS && !bBettaTestMode) continue; // не пушки
	        
            GameInterface.(_tabName).(row).UserData.ID = Goods[i].name;
            GameInterface.(_tabName).(row).UserData.IDX = i;
            
	        GameInterface.(_tabName).(row).td1.icon.group = "GOODS";
			GameInterface.(_tabName).(row).td1.icon.image = Goods[i].name;
			GameInterface.(_tabName).(row).td1.icon.offset = "1, 0";
			GameInterface.(_tabName).(row).td1.icon.width = 32;
			GameInterface.(_tabName).(row).td1.icon.height = 32;
			GameInterface.(_tabName).(row).td1.textoffset = "30,0";
			GameInterface.(_tabName).(row).td1.str = XI_ConvertString(Goods[i].name);
			GameInterface.(_tabName).(row).td1.scale = 0.85;

	        GameInterface.(_tabName).(row).td2.icon.group = "TRADE_TYPE";
			GameInterface.(_tabName).(row).td2.icon.image = "ico_" + nulChr.PriceList.(attr1).(sGoods).TradeType;
			GameInterface.(_tabName).(row).td2.icon.offset = "0, 1";
			GameInterface.(_tabName).(row).td2.icon.width = 16;
			GameInterface.(_tabName).(row).td2.icon.height = 28;

	        if (CheckAttribute(nulChr, "PriceList." + attr1 + "." + sGoods + ".Buy"))
	        {
	            GameInterface.(_tabName).(row).td3.str = nulChr.PriceList.(attr1).(sGoods).Buy;
	        }
	        else
	        {
	            GameInterface.(_tabName).(row).td3.str = "???";
	        }
	        if (CheckAttribute(nulChr, "PriceList." + attr1 + "." + sGoods + ".Sell"))
	        {
	            GameInterface.(_tabName).(row).td4.str = nulChr.PriceList.(attr1).(sGoods).Sell;
	        }
	        else
	        {
	            GameInterface.(_tabName).(row).td4.str = "???";
	        }
	        if (CheckAttribute(nulChr, "PriceList." + attr1 + "." + sGoods + ".Qty"))
	        {
	            GameInterface.(_tabName).(row).td5.str = nulChr.PriceList.(attr1).(sGoods).Qty;
	        }
	        else
	        {
	            GameInterface.(_tabName).(row).td5.str = "????";
	        }
	        GameInterface.(_tabName).(row).td6.str = Goods[i].Units;
			GameInterface.(_tabName).(row).td7.str = Goods[i].Weight;
	        n++;
	    }
    }
    Table_UpdateWindow(_tabName);
}

void TableSelectChange()
{
	string sControl = GetEventData();
	int iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
 	//NullSelectTable("TABLE_CITY");
    NullSelectTable("TABLE_GOODS");
    // перерисуем "прайс"
    if (CurTable == "TABLE_CITY")
    {
    	FillPriceList("TABLE_GOODS", GameInterface.(CurTable).(CurRow).UserData.CityID);
    }
}

void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
	    GameInterface.(sControl).select = 0;
	    Table_UpdateWindow(sControl);
	}
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;

	sPicture = "-1";
	string sAttributeName;
	int nChooseNum = -1;
	switch (sCurrentNode)
	{
		case "TABLE_GOODS":
		    sGroup = "GOODS";
		    sGroupPicture = GameInterface.(CurTable).(CurRow).UserData.ID;
		    sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    iItem = sti(GameInterface.(CurTable).(CurRow).UserData.IDX);
		    sText1  = GetAssembledString(GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID + "_descr", "GoodsDescribe.txt"), &Goods[iItem]);
			sText2 = "Цвета указателя типа товара :" + newStr() + 
				 "- зелёный : колониальные товары" + newStr() + 
				 "- синий : импортные товары" + newStr() + 
				 "- красный : контрабандные товары" + newStr() + 
				 "- персиковый : товары агрессивного спроса";
		break;
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);

}
void HideInfoWindow()
{
	CloseTooltip();
}