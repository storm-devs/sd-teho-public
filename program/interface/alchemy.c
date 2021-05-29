// Ugeen 26.08.10 - интерфейс мультиобъектов (на базе интерфейса обыска) 

int 	nCurScrollNum = 0;
ref 	refCharacter, rItem, nulChr;
aref    alchemy;
string  sCurItem;

bool 	bShowChangeWin = false;
int  	BuyOrSell = 0;
int  	iCharQty, iStoreQty, iCurGoodsIdx;

int 	iTableAddAllBtnX = 262;
int 	iTableAddAllBtnY = 175;
int 	iTableRemoveAllBtnX = 513;
int 	iTableRemoveAllBtnY = 175;

int iLinesCount = 0;

void InitInterface(string iniName)
{
	refCharacter = GetMainCharacter();
	nulChr = &NullCharacter;
	
	if(CheckAttribute(nulChr,"alchemy.items")) DeleteAttribute(nulChr,"alchemy.items");
	makearef(alchemy, nulChr.alchemy);
	
	StartAboveForm(true);
	
	GameInterface.TABLE_LIST.hr.td1.str = "Items";
	GameInterface.TABLE_LIST.hr.td1.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td2.str = "Function";
	GameInterface.TABLE_LIST.hr.td2.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td3.str = "Item name";
	GameInterface.TABLE_LIST.hr.td3.scale = 0.9;	
	GameInterface.TABLE_LIST.hr.td4.str = "Need";
	GameInterface.TABLE_LIST.hr.td4.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td5.str = "Items";
	GameInterface.TABLE_LIST.hr.td5.scale = 0.9;
	
	FillItemsScroll();
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	
	CreateString(true, "ItemName", "", FONT_NORMAL, COLOR_MONEY, 405, 105, SCRIPT_ALIGN_CENTER, 0.8);
	
	sCurItem = SetItemsName();
	AddToTable(ItemsFromId(sCurItem));
	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.tr1.index));
	
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY, iTableAddAllBtnX + 30, iTableAddAllBtnY + 30, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY, iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 30, 0);
	
	SetNodeUsing("GETALL_BUTTON", true);
	SetSelectable("GETALL_BUTTON", false);
	//SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "GETALL_BUTTON", 1, 345, 540, 470, 565);
	//SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "GETALL_BUTTON", 1, 345 + 80, 540, 470 + 80, 565);
	
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
	
	SetFormatedText("STORECAPTION1", XI_ConvertString("titleAlchemy"));
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\128\face_" + refCharacter.FaceId + ".tga");		
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_ALCHEMY_EXIT);
}

void ProcessCancelExit()
{
	if(bShowChangeWin)
	{
		EndTooltip();
	}
	else
	{
		IDoExit(RC_INTERFACE_ALCHEMY_EXIT);		
	}
}

void IDoExit(int exitCode)
{		
	aref rootItems, curItem, arItem;
	int iItemsQty;

	makearef(rootItems, alchemy.Items);
    for(int j = 0; j < GetAttributesNum(rootItems); j++)
    {
		curItem = GetAttributeN(rootItems,j);
		if( Items_FindItem(GetAttributeName(curItem), &arItem) >= 0 )
		{
			iItemsQty = sti(GetAttributeValue(curItem));
			AddItems(refCharacter, arItem.id, iItemsQty);
		}
	}

	EndAboveForm(true);

	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("MouseRClickUP","EndTooltip");
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
		case "TABLE_ADD_ALL_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				onTableAddAllBtnClick();
			}
		break;
		
		case "TABLE_REMOVE_ALL_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				onTableRemoveAllBtnClick();
			}
		break;
		
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
		
		case "GETALL_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				onGetAllBtnClick();
			}
		break;
	}	
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void ShowHelpHint()
{
	int    lngFileID;
	string sCurrentNode = GetCurrentNode();
	string sHeader;
	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";

	if(sCurrentNode == "ITEMS_SCROLL")
	{
		ref    arItm = ItemsFromID(sCurItem);
		lngFileID = LanguageOpenFile("ItemsDescribe.txt");
		sHeader = LanguageConvertString(lngFileID, arItm.name);
		sText1 =  GetItemDescribe(sti(arItm.index));
		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,192,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
		LanguageCloseFile(lngFileID);
	}
	else
	{
		if(!bShowChangeWin) // покажем помощь по работе с формой
		{
			sHeader = XI_ConvertString("titleAlchemy");
			sText1 = "";			
			sText2 = "";
			
			CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,192,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
		}
	}	
}

int GetMultiObjectQty()
{
	int Qty = 0;
	for(int n = 0; n < ITEMS_QUANTITY; n++)
	{
		if( CheckAttribute(&Items[n],"multiobject") )
		{
			Qty++;
		}
	}
	return Qty;
}

void FillItemsScroll()
{
	int 	i, iNum;
	string 	attributeName, sAttr, sItemId, sItmId;
	ref     itm; 
	aref 	arImgGrp, rType;
	
	DeleteAttribute(&GameInterface, "ITEMS_SCROLL");

	nCurScrollNum = 0;
	GameInterface.ITEMS_SCROLL.current = 0;
	
	int nListSize = GetMultiObjectQty();
	
	GameInterface.ITEMS_SCROLL.NotUsed = 6;
	GameInterface.ITEMS_SCROLL.ListSize = nListSize + 2;

	GameInterface.ITEMS_SCROLL.ImagesGroup.t0 = "ITEMS_EMPTY";
	
	makearef(arImgGrp, GameInterface.ITEMS_SCROLL.ImagesGroup);
	FillImagesGroupForItems(arImgGrp);

	GameInterface.ITEMS_SCROLL.BadTex1 = 0;
	GameInterface.ITEMS_SCROLL.BadPic1 = "empty";
		
	int m = 0;
	for(int n = 0; n < ITEMS_QUANTITY; n++)
	{
		makeref(itm, Items[n]); 
				
		if(CheckAttribute(itm, "id") && CheckAttribute(itm, "multiobject") && CheckAttribute(itm, "multiobject.alchemy") && isMultiObjectKnown(itm.id))
		{
			if(itm.multiobject.alchemy == true && !CheckCharacterPerk(refCharacter, "Alchemy")) continue;
		
			attributeName = "pic" + (m + 1);
			GameInterface.ITEMS_SCROLL.(attributeName).itemId = itm.id;
			GameInterface.ITEMS_SCROLL.(attributeName).img1 = GetItemPictureName(itm.id);
			GameInterface.ITEMS_SCROLL.(attributeName).tex1 = GetItemPictureTexture("ITEMS_SCROLL.ImagesGroup",itm.id);
			
			sItemId = itm.id;
			alchemy.items.(sItemId) = 0;
			
			makearef(rType, itm.component);
			iNum = GetAttributesNum(rType);
			
			for(i = 0; i < iNum; i++)
			{
				sAttr = "t" + (i + 1);
				sItmId = itm.component.(sAttr).id;
				alchemy.items.(sItmId) = 0;
			}
			m++;
		}
	}
}

string SetItemsName()
{	
	string sAttr = "pic" + (nCurScrollNum + 1);
	string itemId = GameInterface.ITEMS_SCROLL.(sAttr).itemId;	
	ref rItem = ItemsFromID(itemId);	
	string sItemName = GetConvertStr(rItem.name, "ItemsDescribe.txt");	
	GameInterface.strings.ItemName = sItemName;
	
	return itemId;
}

void ProcessFrame()
{	
	if(sti(GameInterface.ITEMS_SCROLL.current) != nCurScrollNum && GetCurrentNode() == "ITEMS_SCROLL")
	{
		XI_WindowDisable("QTY_WINDOW", true);
		XI_WindowShow("QTY_WINDOW", false);
		nCurScrollNum = sti(GameInterface.ITEMS_SCROLL.current);
		string sAttr = "pic" + (nCurScrollNum + 1);
		string sItemId = GameInterface.ITEMS_SCROLL.(sAttr).itemId;
		
		rItem = ItemsFromId(sItemId);
		AddToTable(rItem);
		sCurItem = sItemId;
		
		GameInterface.TABLE_LIST.select = 1;
		GameInterface.TABLE_LIST.top = 0;
		SetItemsName();
		
		// Стрелочки на первую позицию
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY, iTableAddAllBtnX + 30, iTableAddAllBtnY + 30, 0);
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY, iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 30, 0);
	}
}

void ChangePosTable()
{
}

void AddToTable(ref rItem)
{
	string 	sItemId, sItmId, sAttr, sList, sItmUse, sItmReq;
	int 	n, i, iNum, iLeftQty, iRightQty;
	aref    rType;
	ref     itm;
	
	n = 1;	
	iLinesCount = 1;
	Table_Clear("TABLE_LIST", false, true, false);
	
	sItemId = rItem.id;

	makearef(rType, rItem.component);
	iNum = GetAttributesNum(rType);
	
	for(i = 0; i < iNum; i++) // кол-во компонентов и прочего
	{	
		sAttr 		= GetAttributeName(GetAttributeN(rType, i));
		sItmId 		= rItem.component.(sAttr).id;
		sItmUse 	= rItem.component.(sAttr).use;
		sItmReq     = rItem.component.(sAttr).qty;
		
		itm = ItemsFromId(sItmId);
		trace("sItemId :" +sItemId +" sItmId : " + sItmId);	
		
		sList = "tr" + n;
		iLeftQty  = GetCharacterFreeItem(refCharacter, sItmId);
		if(CheckAttribute(alchemy, "items."+(sItmId))) iRightQty = sti(alchemy.items.(sItmId));
		else iRightQty = 0;
		
		GameInterface.TABLE_LIST.(sList).td1.str = iLeftQty;
		GameInterface.TABLE_LIST.(sList).td1.scale = 0.9;
		GameInterface.TABLE_LIST.(sList).td2.str = XI_ConvertString(sItmUse);
		GameInterface.TABLE_LIST.(sList).td2.scale = 0.9;
		GameInterface.TABLE_LIST.(sList).td3.icon.group = itm.picTexture;
		GameInterface.TABLE_LIST.(sList).td3.icon.image = "itm" + itm.picIndex;
		GameInterface.TABLE_LIST.(sList).td3.icon.offset = "0, 1";
		GameInterface.TABLE_LIST.(sList).td3.icon.width = 56;
		GameInterface.TABLE_LIST.(sList).td3.icon.height = 56;
		GameInterface.TABLE_LIST.(sList).td3.textoffset = "60, 0";
		GameInterface.TABLE_LIST.(sList).td3.str = GetConvertStr(itm.name, "ItemsDescribe.txt");
		GameInterface.TABLE_LIST.(sList).index = itm.index;
		GameInterface.TABLE_LIST.(sList).td3.scale = 0.9;
		GameInterface.TABLE_LIST.(sList).td4.str = sItmReq;
		GameInterface.TABLE_LIST.(sList).td4.scale = 0.9;
		GameInterface.TABLE_LIST.(sList).td5.str = iRightQty;
		GameInterface.TABLE_LIST.(sList).td5.scale = 0.9;
		
		n++;			
		iLinesCount++;
	}

	Table_UpdateWindow("TABLE_LIST");
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
}

void RefreshTableByFrameEvent()
{
	DelEventHandler("frame", "RefreshTableByFrameEvent");
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_LIST", 0 );
}

void CS_TableSelectChange()
{
	String sControl = GetEventData();
	int iSelected = GetEventData();
	int iCol = GetEventData();
	
	// Warship 26.04.09 fix - при прокрутке могло вылазить за экран, неправильно определялась текущая линия
	int iSelLine = iSelected;
	
	if(CheckAttribute(&GameInterface, "TABLE_LIST.top"))
	{
		iSelLine = iSelected - sti(GameInterface.TABLE_LIST.top);
	}
	
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY + 60 * (iSelLine - 1), iTableAddAllBtnX + 30, iTableAddAllBtnY + 60 * (iSelLine - 1) + 30, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY + 60 * (iSelLine - 1), iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 60 * (iSelLine - 1) + 30, 0);
	
	String sList = "tr" + iSelected;
	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.(sList).index));
}

void OnTableClick()
{
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();
	
	string sRow = "tr" + (iRow + 1);
	Table_UpdateWindow(sControl);
}

void EndTooltip()
{
	CloseTooltip(); // всегда убирать, если был
	GameInterface.qty_edit.str = 0;
	SetCurrentNode("TABLE_LIST");
 	XI_WindowDisable("QTY_WINDOW", true);
	XI_WindowShow("QTY_WINDOW", false);
	bShowChangeWin = false;
}

void ShowItemInfo()
{
	if(bShowChangeWin) // жмем окей, когда курсор на таблице
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

int CheckAlchemy(string sItemID)
{
	ref 	rItem;
	aref 	rType;
	int 	Qty = 0;
	int 	iNum, itmReq, itmQty;
	string  sAttr, sItmId, sItmUse;
	bool	bOk = false;
	
	rItem = ItemsFromId(sItemId);
	makearef(rType, rItem.component);
	iNum = GetAttributesNum(rType);
	
	for(int i = 0; i < iNum; i++) // кол-во компонентов и прочего
	{	
		sAttr 		= GetAttributeName(GetAttributeN(rType, i));
		sItmId 		= rItem.component.(sAttr).id;
		itmReq      = sti(rItem.component.(sAttr).qty);
		sItmUse 	= rItem.component.(sAttr).use;	
		if(sItmUse == "component")
		{
			itmQty 		= makeint(GetCharacterFreeItem(alchemy, sItmId)/itmReq);
			if(itmQty > 0)
			{
				if(itmQty < Qty && Qty != 0) 	Qty = itmQty;
				else
				{	
					if(Qty == 0) 				Qty = itmQty;
				}
				bOk = true;	
			}
			else
			{	
				Qty = 0; bOk = false; break;	
			}	
		}		
		else
		{
			if(GetCharacterFreeItem(alchemy, sItmId) >= itmReq) bOk = true;
			else 
			{												
				bOk = false;
				break;
			}	
		}	
	}		
	
	if(!bOk) return 0;
	return Qty;
}

// Жмакнули по кнопке "взять все"
void onGetAllBtnClick()
{
	aref 	rType;
	int 	iNum, itmReq;
	string  sAttr, sItmId, sItmUse;

	ref rItem 	= ItemsFromId(sCurItem);
	int Qty 	= CheckAlchemy(sCurItem);
	
	makearef(rType, rItem.component);
	iNum = GetAttributesNum(rType);
	
	for(int i = 0; i < iNum; i++) // кол-во компонентов и прочего
	{
		sAttr 		= GetAttributeName(GetAttributeN(rType, i));
		sItmId 		= rItem.component.(sAttr).id;
		itmReq      = sti(rItem.component.(sAttr).qty);		
		sItmUse 	= rItem.component.(sAttr).use;
		
		if(sItmUse == "component")
		{
			RemoveItems(alchemy, sItmId, Qty * itmReq);
		}
		if(sItmUse == "catalizator")
		{
			RemoveItems(alchemy, sItmId, 1);
		}
		
	}
	AddItems(refCharacter, sCurItem, Qty * sti(rItem.multiobject.qty));
	WaitDate("", 0, 0, 0, 0, 15 + (5 * (Qty - 1)));
	Statistic_AddValue(refCharacter, "Alchemy", Qty);
	Achievment_SetStat(refCharacter, 7, Qty);
	
	// ugeen 2016
	if(rItem.id == "mangarosapower")
	{
		if (!CheckAttribute(refCharacter, "Mangarosa.Alchemy.MP"))
		{
			refCharacter.Mangarosa.Alchemy.MP = true;
		}	
	}
	if(rItem.id == "mangarosafast")
	{
		if (!CheckAttribute(refCharacter, "Mangarosa.Alchemy.MF"))
		{
			refCharacter.Mangarosa.Alchemy.MF = true;
		}	
	}
	if(rItem.id == "mangarosatotal")
	{
		if (!CheckAttribute(refCharacter, "Mangarosa.Alchemy.MT"))
		{
			refCharacter.Mangarosa.Alchemy.MT = true;
		}		
	}
	
	AddToTable(ItemsFromId(sCurItem)); // Рефрешь таблицы
	
	if(CheckAlchemy(sCurItem) > 0) 	SetSelectable("GETALL_BUTTON", true);
	else							SetSelectable("GETALL_BUTTON", false);
	
	GameInterface.TABLE_LIST.top = 0;
	GameInterface.TABLE_LIST.select = 1;

	// Рефреш позиции стрелочек
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY, iTableAddAllBtnX + 30, iTableAddAllBtnY + 30, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY, iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 30, 0);
	// <-- Warship fix 10.06.09	
}

// Нажали на табличной стрелочке "взять все предметы одного типа"
void onTableAddAllBtnClick()
{
	String item = Items[iCurGoodsIdx].id;
	int iItemsQty = GetCharacterFreeItem(alchemy, item);
		
	if(iItemsQty > 0) // fix
	{
		RemoveItems(alchemy, item, iItemsQty);
		AddItems(refCharacter, item, iItemsQty);
		
		AddToTable(ItemsFromId(sCurItem));
		if(CheckAlchemy(sCurItem) > 0) 	SetSelectable("GETALL_BUTTON", true);
		else							SetSelectable("GETALL_BUTTON", false);
				
		iCharQty = GetCharacterFreeItem(refCharacter, item);
		iStoreQty = GetCharacterFreeItem(alchemy, item);	
	}
}

// Нажали на табличной стрелочке "отдать все предметы одного типа"
void onTableRemoveAllBtnClick()
{
	String item = Items[iCurGoodsIdx].id;
	int iItemsQty = GetCharacterFreeItem(refCharacter, item);
						
	if(iItemsQty > 0) 
	{
		RemoveItems(refCharacter, item, iItemsQty);
		AddItems(alchemy, item, iItemsQty);
		
		AddToTable(ItemsFromId(sCurItem));
		if(CheckAlchemy(sCurItem) > 0) 	SetSelectable("GETALL_BUTTON", true);
		else							SetSelectable("GETALL_BUTTON", false);
						
		iCharQty = GetCharacterFreeItem(refCharacter, item);
		iStoreQty = GetCharacterFreeItem(alchemy, item);	
	}		
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
		describeStr += "id = " + Items[iGoodIndex].id + NewStr();
	}
	describeStr += GetItemDescribe(iGoodIndex);

	BuyOrSell = 0;
	SetFormatedText("QTY_TypeOperation", "");
	SetFormatedText("QTY_Result", "");
	GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", Items[iCurGoodsIdx].picTexture, "itm" + Items[iCurGoodsIdx].picIndex);
	SetFormatedText("QTY_CAPTION", sHeader);
	SetFormatedText("QTY_GOODS_INFO", describeStr);
	LanguageCloseFile(lngFileID);

	iCharQty = GetCharacterFreeItem(refCharacter, Items[iGoodIndex].id);
	iStoreQty = GetCharacterFreeItem(alchemy, Items[iGoodIndex].id);
		
	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty));
	BuyOrSell = 0;	
}

void TransactionOK()
{
	int nTradeQuantity;
	String list;
	confirmChangeQTY_EDIT();
	nTradeQuantity = sti(GameInterface.qty_edit.str);
	if(BuyOrSell == 0)
	{
	    EndTooltip();
	    return;
	}

 	if(BuyOrSell == 1) // Забираем
	{
		RemoveItems(alchemy, Items[iCurGoodsIdx].id, nTradeQuantity);
		AddItems(refCharacter, Items[iCurGoodsIdx].id, nTradeQuantity);
	}
 	else // Отдаем
	{
		AddItems(alchemy, Items[iCurGoodsIdx].id, nTradeQuantity);
		RemoveItems(refCharacter, Items[iCurGoodsIdx].id, nTradeQuantity);
	}
	
	AddToTable(ItemsFromId(sCurItem));
	if(CheckAlchemy(sCurItem) > 0) 	SetSelectable("GETALL_BUTTON", true);
	else							SetSelectable("GETALL_BUTTON", false);
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
	GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str);
	if(sti(GameInterface.qty_edit.str) == 0)
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

		    SetFormatedText("QTY_TypeOperation", "To give");
		}
		else
		{
			BuyOrSell = 1;
			
	        // проверка на колво доступное -->
		    if (sti(GameInterface.qty_edit.str) > iStoreQty)
		    {
		        GameInterface.qty_edit.str = iStoreQty;
		    }
			SetFormatedText("QTY_TypeOperation", "Pick up");
		}
	}
	// если получили ноль
	if (sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_TypeOperation", "");
	    BuyOrSell = 0;
	}
    SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty - BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty + BuyOrSell*sti(GameInterface.qty_edit.str)));
}

void REMOVE_ALL_BUTTON()  
{
	if(!bShowChangeWin)
	{
	    ShowItemInfo();
	}
	
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = -iCharQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();	
}

void ADD_ALL_BUTTON()  
{
	if(!bShowChangeWin)
	{
	    ShowItemInfo();
	}
	
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = iStoreQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();	
}

void REMOVE_BUTTON()  
{
	if(!bShowChangeWin) return;
	
	if(BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = -1;
	}
	else
	{
		if(BuyOrSell == -1)
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

void ADD_BUTTON()  
{
	if(!bShowChangeWin) return;
	
	if(BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = 1;
	}
	else
	{
		if(BuyOrSell == 1)
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
