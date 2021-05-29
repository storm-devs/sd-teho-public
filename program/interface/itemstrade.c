// boal 26/04/06 морма торговли предметами
int	nCurScrollNum = 0;
int iCharCapacity;
int iTotalSpace;
float fCharWeight, fStoreWeight;
int iMaxGoodsStore = 50000;

bool bShowChangeWin = false;
int  TradeMode; // 0 - песо, 1 - дублоны
int  BuyOrSell = 0; // 1-buy -1 sell
string sChrId;
//ref refStore,
ref refCharacter, refStoreChar; // текущий ГГ (оф) и торгаш
int iCharQty, iStoreQty, iCharPrice, iStorePrice;
float fWeight;
int  iCurGoodsIdx;
//----------------------------------------------------------------------------------------------------------------
void InitInterface_RI(string iniName, ref pTrader, int mode)
{
    StartAboveForm(true);

	refCharacter = pchar;
	refStoreChar = pTrader;
	TradeMode = mode;
	//GameInterface.TABLE_LIST.hr.height = 36;
	GameInterface.TABLE_LIST.hr.td1.str = "Items";
	GameInterface.TABLE_LIST.hr.td1.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td2.str = "Wgt";
	GameInterface.TABLE_LIST.hr.td2.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("Price sell");
	GameInterface.TABLE_LIST.hr.td3.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td4.str = "Items name";
	GameInterface.TABLE_LIST.hr.td4.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td5.str = XI_ConvertString("Price buy");
	GameInterface.TABLE_LIST.hr.td5.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td6.str = "Trader items";//XI_ConvertString("In the store");
	GameInterface.TABLE_LIST.hr.td6.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td7.str = "Wgt/pcs";
	GameInterface.TABLE_LIST.hr.td7.scale = 0.9;

    FillCharactersScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	CreateString(true,"CharName","",FONT_NORMAL,COLOR_MONEY, 405,105,SCRIPT_ALIGN_CENTER,1.0);
	
	CreateString(true,"Money_1","",FONT_NORMAL,COLOR_MONEY, 120,581,SCRIPT_ALIGN_LEFT,  0.9);
	CreateString(true,"Money_2","",FONT_NORMAL,COLOR_MONEY, 694,581,SCRIPT_ALIGN_RIGHT, 0.9);
	
	SetCharWeight();
	SetDescription();
	FillCharacterInfo();

	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);

	SetEventHandler("OnTableClick", "OnTableClick", 0);
	SetEventHandler("MouseRClickUP","EndTooltip",0);
	SetEventHandler("ShowHelpHint", "ShowHelpHint", 0);
	SetEventHandler("ShowItemInfo", "ShowItemInfo", 0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);

	SetEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON", 0);
	SetEventHandler("ADD_BUTTON","ADD_BUTTON",0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);
	SetEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON", 0);

	SetEventHandler("frame","ProcessFrame",1);

	SetFormatedText("STORECAPTION1", XI_ConvertString("titleItemsTrade"));

	SetNewPicture("OTHER_PICTURE", "interfaces\portraits\256\face_" + its(refStoreChar.FaceId) + ".tga");
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_FOOD_INFO_EXIT );
}

void ProcessCancelExit()
{
	if (bShowChangeWin)
	{
		EndTooltip();
	}
	else
	{
		IDoExit( RC_INTERFACE_FOOD_INFO_EXIT );
	}
}

void IDoExit(int exitCode)
{
    // boal проверка на перегруз 21.01.2004 -->
	CheckAndSetOverloadMode(GetMainCharacter());
	RefreshEquippedMaps(GetMainCharacter()); // рефрешим карты, если купили	
	// boal 21.01.2004 <--
	// раздайте патроны, порутчик Голицын -->
	int i, cn;
    for(i=1;i<4;i++)
	{
		cn = GetOfficersIndex(pchar, i);
		if (cn!=-1)
		{
			refCharacter = GetCharacter(cn);
            CheckAndSetOverloadMode(refCharacter);
			if (CheckAttribute(refCharacter, "skill.FencingS")) //boal fix иначе не берут саблю при перегрузе
			{
	            EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,BLADE_ITEM_TYPE));
	            EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,CIRASS_ITEM_TYPE)); // boal 08.10.04 броню офицерам
	        }
			if (CheckAttribute(refCharacter, "skill.Pistol") && GetCharacterSkill(refCharacter,"Pistol") > 0.1 )
			{
				EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,GUN_ITEM_TYPE));
			}
		}
	}
	// раздайте патроны, порутчик Голицын <--
	
	CheckTraderItems(refStoreChar);
	
	EndAboveForm(true);

	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("MouseRClickUP","EndTooltip");
	DelEventHandler("ShowHelpHint", "ShowHelpHint");
	DelEventHandler("ShowItemInfo", "ShowItemInfo");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("frame","ProcessFrame");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON","ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "QTY_OK_BUTTON":
			if(comName=="leftstep")
			{
	            ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
	            REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
	      		ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
	            REMOVE_ALL_BUTTON();
			}
		break;

		case "QTY_CANCEL_BUTTON":
			if(comName=="leftstep")
			{
	            ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
	            REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
	      		ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
	            REMOVE_ALL_BUTTON();
			}
		break;

		case "TABLE_LIST":
			if(comName=="leftstep")
			{
	            ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
	            REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
	      		ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
	            REMOVE_ALL_BUTTON();
			}
		break;
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void CalculateInfoData()
{
    AddToTable();
	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.tr1.index));
}

void AddToTable()
{
	int n, i;
	string row, sShipGroup;
	string sGood;
	int  idLngFile;
	int leftQty, rightQty;
	n = 1;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	Table_Clear("TABLE_LIST", false, true, false);
	
	// Сначало уникальные предметы
	for (i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
        row = "tr" + n;
		
		if(!CheckAttribute(&Items[i], "ID"))
		{
			continue;
		}
		
		if(TradeMode == 1) continue; // рандомящиеся предметы за дублоны не продаем
		
		sGood = Items[i].id;
		// проверка на экипировку, их не продаем
		leftQty  = GetCharacterFreeItem(refCharacter, sGood);
		rightQty = GetCharacterFreeItem(refStoreChar, sGood);
		
		if (leftQty > 0 || rightQty > 0)
		{
			GameInterface.TABLE_LIST.(row).td1.str = leftQty;
			GameInterface.TABLE_LIST.(row).td2.str = FloatToString(stf(Items[i].Weight) * leftQty, 1);
			GameInterface.TABLE_LIST.(row).td7.str = FloatToString(stf(Items[i].Weight), 1);
			
			GameInterface.TABLE_LIST.(row).td6.str = rightQty;
			
	        GameInterface.TABLE_LIST.(row).td4.icon.group = Items[i].picTexture;
			GameInterface.TABLE_LIST.(row).td4.icon.image = "itm" + Items[i].picIndex;
			GameInterface.TABLE_LIST.(row).td4.icon.offset = "3, 0";
			GameInterface.TABLE_LIST.(row).td4.icon.width = 32;
			GameInterface.TABLE_LIST.(row).td4.icon.height = 32;
			GameInterface.TABLE_LIST.(row).td4.textoffset = "31,0";
			GameInterface.TABLE_LIST.(row).td4.str = LanguageConvertString(idLngFile, Items[i].name);
			GameInterface.TABLE_LIST.(row).index = i;
			GameInterface.TABLE_LIST.(row).td4.scale = 0.9;
            GameInterface.TABLE_LIST.(row).td3.str = GetTradeItemPrice(i, PRICE_TYPE_BUY, refStoreChar);
			GameInterface.TABLE_LIST.(row).td5.str = GetTradeItemPrice(i, PRICE_TYPE_SELL, refStoreChar);
			n++;
		}
	}
	
    for (i = 0; i < ITEMS_QUANTITY; i++)
	{
        row = "tr" + n;
		
		if(!CheckAttribute(&Items[i], "ID"))
		{
			continue;
		}
		
		sGood = Items[i].id;
		
		if(TradeMode == 1) // тока за дублоны
		{						
			if(!CheckAttribute(&Items[i],"PriceDublon")) continue;
		}
		else
		{	if(!bBettaTestMode)
			{
				if(CheckAttribute(&Items[i],"Price") && sti(Items[i].price) == 0) continue;
			}	
		}
				
		// проверка на экипировку, их не продаем
		leftQty  = GetCharacterFreeItem(refCharacter, sGood);
		rightQty = GetCharacterFreeItem(refStoreChar, sGood);
				
		if (leftQty > 0 || rightQty > 0)
		{
			GameInterface.TABLE_LIST.(row).td1.str = leftQty;
			GameInterface.TABLE_LIST.(row).td2.str = FloatToString(stf(Items[i].Weight) * leftQty, 1);
			GameInterface.TABLE_LIST.(row).td7.str = FloatToString(stf(Items[i].Weight), 1);
			
			GameInterface.TABLE_LIST.(row).td6.str = rightQty;
			
	        GameInterface.TABLE_LIST.(row).td4.icon.group = Items[i].picTexture;
			GameInterface.TABLE_LIST.(row).td4.icon.image = "itm" + Items[i].picIndex;
			GameInterface.TABLE_LIST.(row).td4.icon.offset = "3, 0";
			GameInterface.TABLE_LIST.(row).td4.icon.width = 32;
			GameInterface.TABLE_LIST.(row).td4.icon.height = 32;
			GameInterface.TABLE_LIST.(row).td4.textoffset = "31,0";
			GameInterface.TABLE_LIST.(row).td4.str = LanguageConvertString(idLngFile, Items[i].name);
			GameInterface.TABLE_LIST.(row).index = i;
			GameInterface.TABLE_LIST.(row).td4.scale = 0.9;
			//GameInterface.TABLE_LIST.(row).td4.color = iColor;
			if(TradeMode == 0)
			{
				GameInterface.TABLE_LIST.(row).td3.str = GetTradeItemPrice(i, PRICE_TYPE_BUY, refStoreChar);
				GameInterface.TABLE_LIST.(row).td5.str = GetTradeItemPrice(i, PRICE_TYPE_SELL, refStoreChar);
			}
			else
			{
				GameInterface.TABLE_LIST.(row).td3.str = GetTradeItemPriceDublon(i, PRICE_TYPE_BUY, refStoreChar);
				GameInterface.TABLE_LIST.(row).td5.str = GetTradeItemPriceDublon(i, PRICE_TYPE_SELL, refStoreChar);
			}			
			n++;
		}
	}
	
	NextFrameRefreshTable();
	LanguageCloseFile(idLngFile);
}

void NextFrameRefreshTable()
{
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
}

void RefreshTableByFrameEvent()
{
	DelEventHandler("frame", "RefreshTableByFrameEvent");
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_LIST", 0 );
}

void OnTableClick()
{
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();

	string sRow = "tr" + (iRow + 1);
    Table_UpdateWindow(sControl);
}

void ChangePosTable()
{
}

void ShowHelpHint()
{
    string sHeader;
	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";

	if (!bShowChangeWin)
	{// покажем помощь по работе с формой
        sHeader = XI_ConvertString("titleItemsTrade");
		sText1 = "";

        sText3 = "";
		sText2 = "";

		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,192,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
	}
}

void EndTooltip()
{
	CloseTooltip(); // всегда убирать, если был
    GameInterface.qty_edit.str = 0;
	SetCharWeight();
	SetVariable();
	SetCurrentNode("TABLE_LIST");
 	XI_WindowDisable("QTY_WINDOW", true);
	XI_WindowShow("QTY_WINDOW", false);
	bShowChangeWin = false;
}

void ShowItemInfo()
{
	if (bShowChangeWin) // жмем окей, когда курсор на таблице
	{
	    TransactionOK();
	}
	else
	{
		GameInterface.qty_edit.str = "0";
		BuyOrSell = 0;
		ChangeQTY_EDIT();

		XI_WindowDisable("QTY_WINDOW", false);
		XI_WindowShow("QTY_WINDOW", true);
		bShowChangeWin = true;
	}
}

void CS_TableSelectChange()
{
	string sControl = GetEventData();
	int iSelected = GetEventData();
    string sRow = "tr" + (iSelected);
	SetCharWeight();
	SetVariable();
    ShowGoodsInfo(sti(GameInterface.TABLE_LIST.(sRow).index));
}

void FillCharactersScroll()
{
	int i;
	string faceName;
	string attributeName;
	string PsgAttrName;
	int _curCharIdx;
	ref _refCurChar;
	aref pRef, pRef2;
	bool bOk;
	DeleteAttribute(&GameInterface, "CHARACTERS_SCROLL");

	nCurScrollNum = -1;
	GameInterface.CHARACTERS_SCROLL.current = 0;
	makearef(pRef,pchar.Fellows.Passengers);

	int nListSize = GetPassengersQuantity(pchar);
	int nListSizeFree = GetNotQuestPassengersQuantity(pchar);

	GameInterface.CHARACTERS_SCROLL.NotUsed = 6;
	GameInterface.CHARACTERS_SCROLL.ListSize = nListSizeFree + 2;

	GameInterface.CHARACTERS_SCROLL.ImagesGroup.t0 = "EMPTYFACE";

	FillFaceList("CHARACTERS_SCROLL.ImagesGroup", pchar, 2); // passengers

	GameInterface.CHARACTERS_SCROLL.BadTex1 = 0;
	GameInterface.CHARACTERS_SCROLL.BadPic1 = "emptyface";

	int m = 0;
	attributeName = "pic" + (m + 1);
	GameInterface.CHARACTERS_SCROLL.(attributeName).character = nMainCharacterIndex;
	GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(pchar);
	GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_" + pchar.FaceID);
	m++;

	for(i = 0; i < nListSize; i++)
	{
		_curCharIdx = GetPassenger(pchar, i);

        bOk = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
		if(_curCharIdx != -1  && !CheckAttribute(&characters[_curCharIdx], "isquest") && !bOk)
		{
			if (IsOfficer(&characters[_curCharIdx]) && PChar.location == Characters[_curCharIdx].location)  // boal
			// Jason: фикс - офицеры только в одной с ГГ локации
			{
				attributeName = "pic" + (m + 1);
				GameInterface.CHARACTERS_SCROLL.(attributeName).character = _curCharIdx;
				GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
				GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+Characters[_curCharIdx].FaceID);
				m++;
			}
		}
	}
}

void SetVariable()
{
	string sText, sTextSecond;

	iCharCapacity = GetMaxItemsWeight(refCharacter);
	sText  = FloatToString(fCharWeight, 1) + " / " + iCharCapacity;
	SetFormatedText("CAPACITY", XI_ConvertString("Weight") + ":\n" + sText);

	iTotalSpace = iMaxGoodsStore;
	string sMaxGoodsStore;
    sMaxGoodsStore = "Trader"; //XI_ConvertString("store");
	SetFormatedText("STORE_CAPACITY", sMaxGoodsStore);

	if(!CheckAttribute(refStoreChar,"Merchant.type"))
	{
		if(TradeMode == 0)
		{
			sText = XI_ConvertString("OurMoney") + " " + FindRussianMoneyString(sti(pchar.money));
		}
		else
		{
			sText = XI_ConvertString("OurMoney") + " " + FindRussianDublonString(sti(pchar.dublon));
		}	
		SetFormatedText("OUR_GOLD", sText);
	}
	else
	{
		if(TradeMode == 0) sText = XI_ConvertString("OurMoney") + " " + FindRussianMoneyString(sti(pchar.money));
		else			   sText = XI_ConvertString("OurMoney") + " " + FindRussianDublonString(sti(pchar.dublon));
		GameInterface.strings.Money_1 = sText;
		
		if(TradeMode == 0) sText = XI_ConvertString("TraderMoney") + " " + FindRussianMoneyString(sti(refStoreChar.money));
		else               sText = XI_ConvertString("TraderMoney") + " " + FindRussianDublonString(sti(refStoreChar.dublon));
		GameInterface.strings.Money_2 = sText;
	}
}

void ProcessFrame()
{
	if(sti(GameInterface.CHARACTERS_SCROLL.current) != nCurScrollNum && GetCurrentNode() == "CHARACTERS_SCROLL")
	{
        XI_WindowDisable("QTY_WINDOW", true);
		XI_WindowShow("QTY_WINDOW", false);
		nCurScrollNum = sti(GameInterface.CHARACTERS_SCROLL.current);
		string sAttr = "pic" + (nCurScrollNum + 1);
		refCharacter = &characters[sti(GameInterface.CHARACTERS_SCROLL.(sAttr).character)];
		SetDescription();
		//FillEquipInfo();
		FillCharacterInfo();
		GameInterface.TABLE_LIST.select = 1;
		GameInterface.TABLE_LIST.top = 0;
	}
}
void FillCharacterInfo()
{
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\256\face_" + refCharacter.FaceId + ".tga");
	GameInterface.strings.CharName = GetFullName(refCharacter);
}
void SetDescription()
{
 	if(GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		string attributeName = attributeName = "pic" + (nCurScrollNum+1);
		if(CheckAttribute(&GameInterface, "CHARACTERS_SCROLL." + attributeName))
		{
			SetCharWeight();
		}
	}
    CalculateInfoData();
	SetVariable();
}

void SetCharWeight()
{
    fCharWeight  = GetItemsWeight(refCharacter);

    fStoreWeight = 0;
}
// инфа о предмете
void ShowGoodsInfo(int iGoodIndex)
{
	string GoodName = Items[iGoodIndex].name;
	ref    arItm = &Items[iGoodIndex];
	int    lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	string sHeader = LanguageConvertString(lngFileID, GoodName);

    iCurGoodsIdx = iGoodIndex;

    string describeStr = "";

	if(bBettaTestMode)
	{
	    describeStr += " id = " + Items[iGoodIndex].id + NewStr();
	    
	    if(CheckAttribute(arItm, "dmg_min.old") && CheckAttribute(arItm, "dmg_max.old"))
	    {
	    	describeStr += "OldDmgMin = " + sti(arItm.dmg_min.old) + ", OldDmgMax = "+sti(arItm.dmg_max.old) + newStr();
	    }
	}
	describeStr += GetItemDescribe(iGoodIndex);

	fWeight = stf(Items[iGoodIndex].weight);

    BuyOrSell = 0;
    SetFormatedText("QTY_TypeOperation", "");
    SetFormatedText("QTY_Result", "");
    GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", Items[iCurGoodsIdx].picTexture, "itm" + Items[iCurGoodsIdx].picIndex);
    SetFormatedText("QTY_CAPTION", sHeader);
    SetFormatedText("QTY_GOODS_INFO", describeStr);
	LanguageCloseFile(lngFileID);

	iCharQty = GetCharacterFreeItem(refCharacter, Items[iGoodIndex].id);

	iStoreQty = GetCharacterFreeItem(refStoreChar, Items[iGoodIndex].id);

	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty));
	BuyOrSell = 0;

	if(TradeMode == 0) iStorePrice = GetTradeItemPrice(iGoodIndex, PRICE_TYPE_SELL, refStoreChar);
	else 			   iStorePrice = GetTradeItemPriceDublon(iGoodIndex, PRICE_TYPE_SELL, refStoreChar);
    SetFormatedText("QTY_INFO_STORE_PRICE",XI_ConvertString("Price buy") + NewStr() + its(iStorePrice));

	if(TradeMode == 0) iCharPrice = GetTradeItemPrice(iGoodIndex, PRICE_TYPE_BUY, refStoreChar);
	else 			   iCharPrice = GetTradeItemPriceDublon(iGoodIndex, PRICE_TYPE_BUY, refStoreChar);
	SetFormatedText("QTY_INFO_SHIP_PRICE", XI_ConvertString("Price sell") + NewStr() + its(iCharPrice));
}

void TransactionOK()
{
	int nTradeQuantity, moneyback;
	confirmChangeQTY_EDIT();
	nTradeQuantity = sti(GameInterface.qty_edit.str);
	if (BuyOrSell == 0)
	{
	    EndTooltip();
	    return;
	}

 	if (BuyOrSell == 1) // BUY
	{
		TakeNItems(refStoreChar, Items[iCurGoodsIdx].id, -nTradeQuantity);
		TakeNItems(refCharacter, Items[iCurGoodsIdx].id, nTradeQuantity);				
		moneyback = makeint(iCharPrice*stf(GameInterface.qty_edit.str) + 0.5);
		
		if(TradeMode == 0)
		{
			pchar.money = sti(pchar.money)  - moneyback;
			if(CheckAttribute(refStoreChar,"money") && CheckAttribute(refStoreChar,"Merchant.type"))
			{
				refStoreChar.money = sti(refStoreChar.money) + moneyback;
			}
			Statistic_AddValue(Pchar, "Money_spend", moneyback);
			// boal  check skill -->
	        AddCharacterExpToSkill(pchar, "Commerce", moneyback / 700.0);
		}
		else
		{
			TakeNItems(refStoreChar, "gold_dublon", moneyback);
			TakeNItems(pchar, "gold_dublon", -moneyback);
			AddCharacterExpToSkill(pchar, "Commerce", moneyback / 70.0);	
		}
		
    	WaitDate("",0,0,0, 0, 5);
        // boal <--
	}
 	else
	{ // SELL
	    TakeNItems(refStoreChar, Items[iCurGoodsIdx].id, nTradeQuantity);
		TakeNItems(refCharacter, Items[iCurGoodsIdx].id, -nTradeQuantity);				
		moneyback = makeint(iStorePrice*stf(GameInterface.qty_edit.str) + 0.5);
		
		if(TradeMode == 0)
		{
	  		pchar.money = sti(pchar.money)  + moneyback;
			if(CheckAttribute(refStoreChar,"money") && CheckAttribute(refStoreChar,"Merchant.type"))
			{
				refStoreChar.money = sti(refStoreChar.money) - moneyback;
			}
			Statistic_AddValue(Pchar, "Money_get", moneyback);
			Achievment_SetStat(pchar, 39, moneyback);
			// boal  check skill -->
	        AddCharacterExpToSkill(pchar, "Commerce", moneyback / 1000.0);
		}
		else
		{
			TakeNItems(refStoreChar, "gold_dublon", -moneyback);
			TakeNItems(pchar, "gold_dublon", moneyback);				
			AddCharacterExpToSkill(pchar, "Commerce", moneyback / 100.0);
		}
		
		
    	WaitDate("",0,0,0, 0, 5);
        // boal <--
	}
	AddToTable();
	EndTooltip();
	ShowGoodsInfo(iCurGoodsIdx); //сбросим все состояния
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
    SetCurrentNode("QTY_OK_BUTTON");
}

void ChangeQTY_EDIT()
{
	float  iWeight;
	SetCharWeight();
	GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str);
	if (sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_TypeOperation", "");
	    SetFormatedText("QTY_Result", "");
	    BuyOrSell = 0;
	}
	else
	{
		if (sti(GameInterface.qty_edit.str) < 0 || BuyOrSell == -1)
		{
			if (BuyOrSell != -1)
			{
		    	GameInterface.qty_edit.str = -sti(GameInterface.qty_edit.str);
		    }
		    BuyOrSell = -1;
		    // проверка на колво доступное -->
		    if (sti(GameInterface.qty_edit.str) > iCharQty)
		    {
		        GameInterface.qty_edit.str = iCharQty;
		    }
		    iWeight = (fWeight * sti(GameInterface.qty_edit.str));
		    if ((fStoreWeight + iWeight) > iTotalSpace)
		    {
		        iWeight = iTotalSpace - fStoreWeight - 0.01; // чуть меньше
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight );
		        iWeight = fWeight * sti(GameInterface.qty_edit.str);
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight ); // округление
		    }
			if(CheckAttribute(refStoreChar,"Merchant.type"))
			{
				if(TradeMode == 0)
				{
					if (makeint(iStorePrice*stf(GameInterface.qty_edit.str) + 0.5) > sti(refStoreChar.money))
					{
						GameInterface.qty_edit.str = makeint(sti(refStoreChar.money) / iStorePrice);
						iWeight = fWeight * sti(GameInterface.qty_edit.str);
					}
				}
				else
				{
					if (makeint(iStorePrice*stf(GameInterface.qty_edit.str) + 0.5) > sti(refStoreChar.dublon))
					{
						GameInterface.qty_edit.str = makeint(sti(refStoreChar.dublon) / iStorePrice);
						iWeight = fWeight * sti(GameInterface.qty_edit.str);
					}				
				}	
			}	
		    // проверка на колво доступное <--
		    // квестовые не продать -->
		    if (IsQuestUsedItem(Items[iCurGoodsIdx].id))
		    {
		        GameInterface.qty_edit.str = 0;
		    }
		    // квестовые не продать <--
		    SetFormatedText("QTY_TypeOperation", "Sell");
		    SetFormatedText("QTY_Result", "Money " + makeint(iStorePrice*stf(GameInterface.qty_edit.str) + 0.5) +
			                ", weight " + FloatToString(iWeight, 1) );
		}
		else
		{
			BuyOrSell = 1;
	        // проверка на колво доступное -->
		    if (sti(GameInterface.qty_edit.str) > iStoreQty)
		    {
		        GameInterface.qty_edit.str = iStoreQty;
		    }
		    iWeight = (fWeight * sti(GameInterface.qty_edit.str));
		    if ((fCharWeight + iWeight) > iCharCapacity)
		    {
		        iWeight = iCharCapacity - fCharWeight - 0.01; // чуть меньше
				if (iWeight < 0) iWeight = 0;
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight );
		        iWeight = fWeight * sti(GameInterface.qty_edit.str);
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight ); // округдение
		    }
			if(TradeMode == 0)
			{
				if (makeint(iCharPrice*stf(GameInterface.qty_edit.str) + 0.5) > sti(pchar.money))
				{
					GameInterface.qty_edit.str = makeint(sti(pchar.money) / iCharPrice);
					iWeight = fWeight * sti(GameInterface.qty_edit.str);
				}
			}	
			else
			{
				if (makeint(iCharPrice*stf(GameInterface.qty_edit.str) + 0.5) > sti(pchar.dublon))
				{
					GameInterface.qty_edit.str = makeint(sti(pchar.dublon) / iCharPrice);
					iWeight = fWeight * sti(GameInterface.qty_edit.str);
				}
			}	
		    // проверка на колво доступное <--

			SetFormatedText("QTY_TypeOperation", "Buy");
			SetFormatedText("QTY_Result", "Money " + makeint(iCharPrice*stf(GameInterface.qty_edit.str) + 0.5) +
			                ", weight " + FloatToString(iWeight, 1) );
		}
	}
	// если получили ноль
	if (sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_TypeOperation", "");
	    SetFormatedText("QTY_Result", "");
	    BuyOrSell = 0;
	}
    SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty - BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty + BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetCharWeight();
    fCharWeight  = fCharWeight  + BuyOrSell * iWeight;
	fStoreWeight = fStoreWeight - BuyOrSell * iWeight;
    SetVariable();
}

void REMOVE_ALL_BUTTON()  // продать все
{
	if (!bShowChangeWin)
	{
	    ShowItemInfo();
	}
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = -iCharQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void ADD_ALL_BUTTON()  // купить все
{
    if (!bShowChangeWin)
	{
	    ShowItemInfo();
	}
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = iStoreQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void REMOVE_BUTTON()  // продать
{
    if (!bShowChangeWin) return;
	if (BuyOrSell == 0)
    {
        GameInterface.qty_edit.str = -1;
    }
    else
    {
		if (BuyOrSell == -1)
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) + 1);
		}
		else
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - 1);
		}
		BuyOrSell = 0;
	}
	ChangeQTY_EDIT();
}

void ADD_BUTTON()  // купить
{
    if (!bShowChangeWin) return;
	if (BuyOrSell == 0)
    {
        GameInterface.qty_edit.str = 1;
    }
    else
    {
  		if (BuyOrSell == 1)
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + 1);
		}
		else
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) - 1);
		}
		BuyOrSell = 0;
	}
	ChangeQTY_EDIT();
}

int GetTradeItemPrice(int itmIdx, int tradeType, ref chr)
{
	int itmprice 		= 0;
	int itmtype 		= ITEM_TRADE_NORMAL;
	int FinalItmPrice 	= 0;
	float priceModify 	= 1.0;
	string sItemid;
	
	if(itmIdx<0 || itmIdx>TOTAL_ITEMS) return 0;

	if(CheckAttribute(&Items[itmIdx],"price"))
	{
		itmprice = sti(Items[itmIdx].price);
	}
	if(CheckAttribute(&Items[itmIdx],"TradeType"))
	{
		itmtype = sti(Items[itmIdx].TradeType);
	}
	if(CheckAttribute(&Items[itmIdx],"id"))
	{
		sItemid = Items[itmIdx].id;
	}

	float skillDelta = GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE);
	float skillModify;
	if(tradeType == PRICE_TYPE_BUY)	// покупка предметов героем
	{
		skillModify = 1.325 - skillDelta * 0.005; 		
		if(CheckAttribute(chr, "Merchant.type"))//Jason
		{
			if(chr.Merchant.type == "lightman")
			{
				if(itmtype == ITEM_TRADE_ARTEFACT || sItemid == "potionrum") skillModify *= 30.0;
				if(sItemid == "jewelry8") skillModify *= 10.0;
			}	
			if(chr.Merchant.type == "jeweller")
			{
				if(sItemid == "gold_dublon") 
				{
					FinalItmPrice = makeint(itmprice * 1.05);
					return FinalItmPrice;
				}	
			}			
		}
		if(CheckCharacterPerk(pchar,"HT2"))
		{
			if(CheckOfficersPerk(pchar,"ProfessionalCommerce"))	{ skillModify -= 0.20; }
			else
			{
				if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ skillModify -= 0.15; }
				else skillModify -= 0.05;
			}						
		}
		else
		{
			if(CheckOfficersPerk(pchar,"ProfessionalCommerce"))	{ skillModify -= 0.15; }
			else
			{
				if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ skillModify -= 0.10; }
			}				
		}								
		FinalItmPrice = makeint(makefloat(itmprice)*skillModify);
	}
	else // продажа предметов героем
	{
		if(CheckAttribute(&Items[itmIdx],"fixedprice")) return itmprice;
		
		skillModify = 0.675 + skillDelta * 0.005; 
		if(CheckCharacterPerk(chr,"HT2"))
		{
			if(CheckOfficersPerk(pchar,"ProfessionalCommerce"))	skillModify += 0.20;
			else
			{
				if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ skillModify += 0.15; }
				else skillModify += 0.05;
			}				
		}
		else
		{
			if(CheckOfficersPerk(pchar,"ProfessionalCommerce"))	skillModify += 0.15;
			else
			{
				if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ skillModify += 0.10; }
			}		
		}			
				
		priceModify = GetPriceModify(itmIdx, itmtype, chr);		
		FinalItmPrice = makeint(makefloat(itmprice)*skillModify * priceModify);
	}	

	return FinalItmPrice;
}

int GetTradeItemPriceDublon(int itmIdx, int tradeType, ref chr)
{
	int itmprice = 0;
	
	if(itmIdx < 0 || itmIdx > TOTAL_ITEMS) return 0;

	if(CheckAttribute(&Items[itmIdx],"PriceDublon"))
	{
		itmprice = sti(Items[itmIdx].PriceDublon);
	}

	float skillDelta = GetSummonSkillFromNameToOld(chr, SKILL_COMMERCE);
	float skillModify;
	if(tradeType == PRICE_TYPE_BUY)
	{
		skillModify = 1.325 - skillDelta * 0.005; 		
		if(CheckCharacterPerk(pchar,"HT2"))
		{
			if(CheckOfficersPerk(pchar,"ProfessionalCommerce"))	{ skillModify -= 0.20; }
			else
			{
				if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ skillModify -= 0.15; }
				else skillModify -= 0.05;
			}						
		}
		else
		{
			if(CheckOfficersPerk(pchar,"ProfessionalCommerce"))	{ skillModify -= 0.15; }
			else
			{
				if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ skillModify -= 0.10; }
			}				
		}						
	}
	else
	{
		skillModify = 0.675 + skillDelta * 0.005; 
		if(CheckCharacterPerk(chr,"HT2"))
		{
			if(CheckOfficersPerk(pchar,"ProfessionalCommerce"))	skillModify += 0.20;
			else
			{
				if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ skillModify += 0.15; }
				else skillModify += 0.05;
			}				
		}
		else
		{
			if(CheckOfficersPerk(pchar,"ProfessionalCommerce"))	skillModify += 0.15;
			else
			{
				if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ skillModify += 0.10; }
			}		
		}				
	}
	return makeint(makefloat(itmprice)*skillModify);
}


float GetPriceModify(int itmIdx, int itmTradeType, ref _chr)
{
	aref arItem;
	string 	sMerchantType, sItemType, sItemid;
	float fModify = 1.0;
	
	if(itmIdx<0 || itmIdx>TOTAL_ITEMS) return 0;

	if(CheckAttribute(&Items[itmIdx],"id"))
	{
		sItemid = Items[itmIdx].id;
	}
	
	if(CheckAttribute(_chr, "Merchant.type"))
	{
		sMerchantType = _chr.Merchant.type;
		switch(sMerchantType)
		{
			case "potion"	:
				if(itmTradeType != ITEM_TRADE_NORMAL && itmTradeType != ITEM_TRADE_POTION) 
				{
					 fModify = 0.7;
				}
			break;
			case "veteran"	:
				if(itmTradeType != ITEM_TRADE_NORMAL) 
				{
					fModify = 0.7;
				}								
			break;
			case "armourer"	:
				if(itmTradeType != ITEM_TRADE_AMMUNITION) 
				{
					fModify = 0.7;
				}				
			break;
			case "monk"		:
				if(itmTradeType != ITEM_TRADE_ARTEFACT && itmTradeType != ITEM_TRADE_MAP) 
				{
					fModify = 0.7;
				}
			break;
			case "indian"	:
				if(itmTradeType != ITEM_TRADE_NORMAL && itmTradeType != ITEM_TRADE_ARTEFACT) 
				{
					fModify = 0.7;
				}
			break;
			case "jeweller"	:
				if(itmTradeType != ITEM_TRADE_JEWELRY) 
				{
					fModify = 0.7;
				}
			break;
			case "lightman"	://Jason
					if(sItemid == "potionrum") fModify = 10.0;
					else fModify = 0.5;
			break;
			case "LSC_indian"	://Jason 230912
					fModify = 0.3;
			break;
			case "company"	://Jason 230912
					fModify = 0.1;
			break;
		}						
	}
	return fModify;
}

void CheckTraderItems(ref chr)
{
	string 	sMerchantType, sItemType;
	aref 	rootItems, curItem, arItem;
	
	if(CheckAttribute(chr, "Merchant.type")) // уличный торговец или ювелир
	{
		sMerchantType = chr.Merchant.type;
		makearef(rootItems, chr.Items);
		for(int j = 0; j < GetAttributesNum(rootItems); j++)
		{
			curItem = GetAttributeN(rootItems, j);
			if( Items_FindItem(GetAttributeName(curItem), &arItem) >= 0 )
			{
				if(CheckAttribute(arItem, "TradeType")) 
				{
					sItemType = arItem.TradeType;
					switch(sMerchantType)
					{
						case "potion"	:
							if(sItemType != ITEM_TRADE_NORMAL 
								&& sItemType != ITEM_TRADE_POTION) DeleteAttribute(chr, "items." + arItem.id); 
						break;
						case "veteran"	:
							if(sItemType != ITEM_TRADE_NORMAL) 
								DeleteAttribute(chr, "items." + arItem.id); 
						break;
						case "armourer"	:
							if(sItemType != ITEM_TRADE_AMMUNITION) 
								DeleteAttribute(chr, "items." + arItem.id); 
						break;
						case "monk"		:
							if(sItemType != ITEM_TRADE_ARTEFACT 
								&& sItemType != ITEM_TRADE_MAP) DeleteAttribute(chr, "items." + arItem.id); 
						break;
						case "indian"	:
							if(sItemType != ITEM_TRADE_NORMAL 
								&& sItemType != ITEM_TRADE_ARTEFACT) DeleteAttribute(chr, "items." + arItem.id); 
						break;
						case "jeweller"	:
							if(sItemType != ITEM_TRADE_JEWELRY) 
								DeleteAttribute(chr, "items." + arItem.id); 
						break;
					}
				}	
			}
		}
	}
}
