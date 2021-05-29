// Интерфейс закупки товара казначеем

int iCurGoodIndex;
int iCurCompanion = 0;

void InitInterface(string iniName)
{
	string sGood;
	int i;
	int X = 90;
	int Y = 95;

	GameInterface.title = "titleGoodsTransfer";

	for(i = 0; i < GOODS_QUANTITY; i++)	// Картинки товаров
	{
		if(i == 6 || i == 12 || i == 18 || i == 24 || i == 30)	// Другой столбец
		{
			X += 123;
			Y = 95;
		}
		
		sGood = goods[i].name;
				
		// Это к магазину никакого отношения не имеет
		if(HasSubStr(sGood, "Cannon") || HasSubStr(sGood, "Culverine")) continue;
				
		GameInterface.GOODS_ICONS.imagelist.(sGood).group = "GOODS";
		GameInterface.GOODS_ICONS.imagelist.(sGood).width = 64;
		GameInterface.GOODS_ICONS.imagelist.(sGood).height = 64;
		GameInterface.GOODS_ICONS.imagelist.(sGood).x = X;
		GameInterface.GOODS_ICONS.imagelist.(sGood).y = Y;
		GameInterface.GOODS_ICONS.imagelist.(sGood).pic = sGood;
		
		Y += 82; // Интервал между картинками
	}
	
	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);
	
	EI_CreateFrame("BORDERS", 0,33,800,600);
	
	// Нужно после инициализации интерфейса
	CreateGoodNamesStrings();
	
	// Тут, т.к. изначально все по нулям и на кнопку можно не нажать
	if(!CheckAttribute(PChar, "TransferGoods.AllGoodsWeight")) PChar.TransferGoods.AllGoodsWeight = 0;
		
	SetCheckButtonsStates();
	
	CreateString(true, "CurCompanion", XI_ConvertString(GetShipTypeName(PChar)) + " '" + PChar.Ship.Name + "'", FONT_CAPTION, COLOR_NORMAL, 650, 568, SCRIPT_ALIGN_CENTER, 0.9);
	
	CreateString(true, "GameVersionInfo1", VERSION_NUMBER1, FONT_CAPTION, COLOR_NORMAL,150, 10, SCRIPT_ALIGN_CENTER, 0.8);
	CreateString(true, "GameVersionInfo2", GetVerNum(), FONT_CAPTION, COLOR_NORMAL, 650, 10, SCRIPT_ALIGN_CENTER, 0.8);
	
	SetEventHandler("UnShowTGWindow", "UnShowTGWindow", 0);
	SetEventHandler("ShowItemsWindow", "ShowItemsWindow", 0);
	SetEventHandler("exitCancel", "ProcessCancelExit", 0);
	SetEventHandler("ievnt_command", "ProcCommand", 0);
	SetEventHandler("evntDoPostExit", "DoPostExit", 0);
}

void SetCheckButtonsStates()
{
	String companionId = Characters[GetCompanionIndex(PChar, iCurCompanion)].Id;
	
	if(CheckAttribute(PChar, "TransferGoods." + companionId + ".BuyContraband"))
	{
		CheckButton_SetState("CHECK_BUYCONTRABAND", 1, true);
}
	else
	{
		CheckButton_SetState("CHECK_BUYCONTRABAND", 1, false);
	}
}

void CreateGoodNamesStrings()
{
	int x, y;
	int buyCount;
	String sGood;
	String companionId = Characters[GetCompanionIndex(PChar, iCurCompanion)].Id;
	
	for(int i = 0; i < GOODS_QUANTITY; i++)	// Названия товаров
	{
		sGood = Goods[i].name;
		
		if(CheckAttribute(GameInterface, "GOODS_ICONS.imagelist." + sGood))
		{
			x = MakeInt(GameInterface.GOODS_ICONS.imagelist.(sGood).x);
			y = MakeInt(GameInterface.GOODS_ICONS.imagelist.(sGood).y) - 40;
			
			if(CheckAttribute(PChar, "TransferGoods." + companionId + "." + sGood))
			{
				buyCount = sti(PChar.TransferGoods.(companionId).(sGood));
			}
			else
			{
				buyCount = 0;
			}
			
			// Строки
			SendMessage(&GameInterface,"lslsssllllllfl",MSG_INTERFACE_MSG_TO_NODE, "GOODS_NAMES", 0, sGood, XI_ConvertString(sGood), FONT_CAPTION, X, Y, COLOR_NORMAL, COLOR_NORMAL, SCRIPT_ALIGN_CENTER, true, 1, 100);
			SendMessage(&GameInterface,"lslsssllllllfl",MSG_INTERFACE_MSG_TO_NODE, "GOODS_NAMES", 0, "Transfer" + sGood, XI_ConvertString("BuyGoods") + buyCount, FONT_CAPTION, x, y + 52, COLOR_NORMAL, COLOR_NORMAL, SCRIPT_ALIGN_CENTER, true, 1, 100);
		}
	}
}

void RefreshGoodsCountStrings()
{
	int buyCount;
	int curString = 2; // Со второй, т.к. первая - название
	String sGood;
	String companionId = Characters[GetCompanionIndex(PChar, iCurCompanion)].Id;
	
	for(int i = 0; i < GOODS_QUANTITY; i++)	// Названия товаров
	{
		sGood = Goods[i].name;
		
		if(CheckAttribute(GameInterface, "GOODS_ICONS.imagelist." + sGood))
		{
			if(CheckAttribute(PChar, "TransferGoods." + companionId + "." + sGood))
			{
				buyCount = sti(PChar.TransferGoods.(companionId).(sGood));
			}
			else
			{
				buyCount = 0;
			}
			
			SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, "GOODS_NAMES", 1, curString, "#" + XI_ConvertString("BuyGoods") + buyCount);
			curString += 2;
		}
	}
}

void ShowItemsWindow()	// Принцип тот-же, что и в интерфейса отличной карты
{
	float offsetX, offsetY;
	
	GetXYWindowOffset(&offsetX, &offsetY);
	
	float fMouseX = stf(GameInterface.mousepos.x) - 6.0 + 5;
	float fMouseY = stf(GameInterface.mousepos.y) - 50.0 + 5;
	
	//определяем верхний левый угол картинки
	float fOffsetX = stf(GameInterface.GOODS_ICONS.offset.x);
	float fOffsetY = stf(GameInterface.GOODS_ICONS.offset.y);

	fMouseX = fOffsetX + fMouseX * stf(GameInterface.GOODS_ICONS.scale.x);
	fMouseY = fOffsetY + fMouseY * stf(GameInterface.GOODS_ICONS.scale.y);
	
	string sGood;
	for(int i=0; i<GOODS_QUANTITY; i++)
	{
		sGood = goods[i].name;
		if(CheckAttribute(&GameInterface, "GOODS_ICONS.imagelist." + sGood))
		{
			if(fMouseX >= stf(GameInterface.GOODS_ICONS.imagelist.(sGood).x) - 32 + offsetX)
			{
				if(fMouseX <= stf(GameInterface.GOODS_ICONS.imagelist.(sGood).x) + 32.0 + offsetX)
				{
					if(fMouseY >= stf(GameInterface.GOODS_ICONS.imagelist.(sGood).y) - 80 + offsetY)
					{
						if(fMouseY <= stf(GameInterface.GOODS_ICONS.imagelist.(sGood).y) - 16 + offsetY)
						{
							ShowMainWindow(false);
							ShowTransferGoods(i);
						}
					}
				}
			}
		}
	}
}

void ShowMainWindow(bool _truefalse)
{
	if(_truefalse)
	{	// Видим главное окно
		CreateGoodNamesStrings(); // Обновим
		XI_WindowDisable("MAIN_WINDOW", false);
		XI_WindowDisable("GOODS_TRANSFER_WINDOW", true);
		XI_WindowShow("GOODS_TRANSFER_WINDOW", false);
		SetCurrentNode("MAIN_BACK");
	}
	else
	{
		XI_WindowDisable("MAIN_WINDOW", true);
		XI_WindowDisable("GOODS_TRANSFER_WINDOW", false);
		XI_WindowShow("GOODS_TRANSFER_WINDOW", true);
		SetCurrentNode("TG_CANCEL_BUTTON");
	}
}

void UnShowTGWindow()
{
	ShowMainWindow(true);
}

void ShowTransferGoods(int iGood)
{
	string sText;
	String sGood = Goods[iGood].name;
	String companionId = Characters[GetCompanionIndex(PChar, iCurCompanion)].Id;
	int buyCount;
	
	iCurGoodIndex = iGood; // Какой товар выбрали
	
	if(CheckAttribute(PChar, "TransferGoods." + companionId + "." + sGood))
	{
		buyCount = sti(PChar.TransferGoods.(companionId).(sGood));
	}
	else
	{
		buyCount = 0;
	}
	
	GameInterface.TG_EDIT.str = buyCount;
	
	sText = XI_ConvertString("titleGoodsTransfer"); // Заголовок
	SetFormatedText("TG_GOODS_CAPTION", sText);
	
	SendMessage(&GameInterface, "lslss", MSG_INTERFACE_MSG_TO_NODE, "TG_GOODS_PICTURE", 6, "GOODS", sGood); // Ставим картинку
	sText = GetConvertStr(sGood, "GoodsDescribe.txt") + NewStr(); // описание товара
	sText = sText + GetAssembledString(GetConvertStr(sGood + "_descr", "GoodsDescribe.txt"), &Goods[iGood]);
	SetFormatedText("TG_GOODS_INFO", sText);
	
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_GOODS_TRANSFER);
}

void IDoExit(int exitCode)
{
	SetContrabandBuyFromCheckBox();
	
	DelEventHandler("exitCancel", "ProcessCancelExit");
	DelEventHandler("ievnt_command", "ProcCommand");
	DelEventHandler("evntDoPostExit", "DoPostExit");
	DelEventHandler("UnShowTGWindow", "UnShowTGWindow");
	DelEventHandler("ShowItemsWindow", "ShowItemsWindow");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	
	int iNum = 0;
	string sGood;
	int iTemp = 0;
	ref rGood;
	
	String companionId = Characters[GetCompanionIndex(PChar, iCurCompanion)].Id;
	
	switch(nodName)
	{
		case "TG_ADD_ALL_BUTTON":
			GameInterface.TG_EDIT.str = 10000;
			break;
	
		case "TG_ADD_BUTTON":
			OnAddBtnClick();
			break;
			
		case "TG_REMOVE_ALL_BUTTON":
			GameInterface.TG_EDIT.str = 0;
			break;
			
		case "TG_REMOVE_BUTTON":
			OnRemoveBtnClick();
			break;	
			
		case "TG_CANCEL_BUTTON":
			if(comName == "click" || comName == "activate")
			{
				UnShowTGWindow();
			}
			break;
			
		case "TG_OK_BUTTON":
			if(comName == "click" || comName == "activate")
			{
				rGood = &Goods[iCurGoodIndex];
				sGood = rGood.name;
				iNum =  sti(GameInterface.TG_EDIT.str);
				
				PChar.TransferGoods.(companionId).(sGood) = iNum; // Прибавим в список закупок
				
				UnShowTGWindow();	
			}
			break;
		
		// Warship 19.08.09 Выбор корабля, для кого запукаем
		case "BTN_CHOOSESHIP_LEFT":
			SetCurrentCompanion(iCurCompanion - 1);
		break;
		
		case "BTN_CHOOSESHIP_RIGHT":
			SetCurrentCompanion(iCurCompanion + 1);
		break;
	}
}

void SetCurrentCompanion(int _num)
{
	ref character;
	int characterIndex = GetCompanionIndex(PChar, _num);
	
	if(characterIndex > 0)
	{
		character = &Characters[characterIndex];
		
		if(GetRemovable(character))
		{
			SetContrabandBuyFromCheckBox();
			
			iCurCompanion = _num;
			GameInterface.Strings.CurCompanion = XI_ConvertString(GetShipTypeName(character)) + " '" + character.Ship.Name + "'";
			
			SetCheckButtonsStates();
			RefreshGoodsCountStrings();
		}
	}
}

void OnAddBtnClick()
{
	ref rGood;
	int iNum = MakeInt(GameInterface.TG_EDIT.str);
	
	if(iNum < 10000)
	{
		rGood = &Goods[iCurGoodIndex];
		GameInterface.TG_EDIT.str = iNum + sti(rGood.Units);
	}
}

void OnRemoveBtnClick()
{
	ref rGood;
	int iNum = MakeInt(GameInterface.TG_EDIT.str);;
	
	if(iNum > 0)
	{
		rGood = &Goods[iCurGoodIndex];
		GameInterface.TG_EDIT.str = iNum - sti(rGood.Units);
	}
}

void SetContrabandBuyFromCheckBox()
{
	String companionId = Characters[GetCompanionIndex(PChar, iCurCompanion)].Id;
	
 	if(SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "CHECK_BUYCONTRABAND", 3, 1))
	{
		PChar.TransferGoods.(companionId).BuyContraband = true;
	}
	else
	{
		DeleteAttribute(PChar, "TransferGoods." + companionId + ".BuyContraband");
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}
