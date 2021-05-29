/// BOAL меню предметов
#include "interface\character_all.h"

void InitInterface(string iniName)
{
    InterfaceStack.SelectMenu_node = "LaunchItems"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleItems";
	
	xi_refCharacter = pchar;
	
	FillCharactersScroll();
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("frame","ProcessFrame",1);
    SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("eTabControlPress","procTabChange",0);
	SetEventHandler("ExitMapWindow","ExitMapWindow",0);
    
    XI_RegistryExitKey("IExit_F2");
    SetVariable();
    SetNewGroupPicture("Weight_PIC", "ICONS_CHAR", "weight");
    SetNewGroupPicture("Money_PIC", "ICONS_CHAR", "Money");
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
    DelEventHandler("frame","ProcessFrame");
    DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("eTabControlPress","procTabChange");
	DelEventHandler("ExitMapWindow","ExitMapWindow");

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
		case "EQUIP_BUTTON":
			if (comName=="activate" || comName=="click")
			{
				EquipPress();
			}
		break;
		
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

void ProcessFrame()
{
	if (sti(GameInterface.CHARACTERS_SCROLL.current)!=nCurScrollNum && GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		nCurScrollNum = sti(GameInterface.CHARACTERS_SCROLL.current);
		SetButtonsState();
		return;
	}
}

void SetButtonsState()
{
	string attributeName = "pic" + (nCurScrollNum+1);
	
	if(GameInterface.CHARACTERS_SCROLL.(attributeName).character != "0")
	{
		int iCharacter = sti(GameInterface.CHARACTERS_SCROLL.(attributeName).character);
		xi_refCharacter = &characters[iCharacter];
		SetVariable();
	}
	else
	{
        xi_refCharacter = pchar;
        SetVariable();
	}
}

void SetVariable()
{
	SetFormatedText("SETUP_FRAME_CAPTION", XI_ConvertString("Equipment") + ": " + GetFullName(xi_refCharacter));
	// сортировка -->
	SortItems(xi_refCharacter);
	// сортировка -->
	SetControlsTabMode(1);
	HideItemInfo();
	SetFormatedText("Weight_TEXT", XI_ConvertString("weight") + ": " + FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / "+GetMaxItemsWeight(xi_refCharacter));
	SetFormatedText("Money_TEXT", MakeMoneyShow(sti(xi_refCharacter.Money), MONEY_SIGN,MONEY_DELIVER));

	SetNodeUsing("EQUIP_BUTTON" , true);
	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
}

void FillItemsTable(int _mode) // 1 - все 2 - оружие 3 - остальное
{
	int n, i;
	string row;
	string sGood;
	string groupID;
	string itemType;
	int  idLngFile;
	bool ok, ok0, ok1, ok2, ok3;
	aref rootItems, arItem;
	aref  curItem;
	
	GameInterface.TABLE_ITEMS.hr.td1.str = "Items name";
	GameInterface.TABLE_ITEMS.hr.td1.scale = 0.8;
	GameInterface.TABLE_ITEMS.hr.td2.str = "Wgt/pcs";
	GameInterface.TABLE_ITEMS.hr.td2.scale = 0.8;
	GameInterface.TABLE_ITEMS.hr.td3.str = "Qty";
	GameInterface.TABLE_ITEMS.hr.td3.scale = 0.8;
	GameInterface.TABLE_ITEMS.hr.td4.str = "Wgt";
	GameInterface.TABLE_ITEMS.hr.td4.scale = 0.8;
	GameInterface.TABLE_ITEMS.select = 0;
	GameInterface.TABLE_ITEMS.top = 0;
	n = 1;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	Table_Clear("TABLE_ITEMS", false, true, false);
	
	// Заполним вещами от нас
	makearef(rootItems, xi_refCharacter.Items);
    for (i=0; i<GetAttributesNum(rootItems); i++)
    {
		curItem = GetAttributeN(rootItems, i);
		groupID = "";
		itemType = "";

		if (Items_FindItem(GetAttributeName(curItem), &arItem)>=0 )
		{
			row = "tr" + n;
			sGood = arItem.id;
			if(CheckAttribute(arItem,"groupID")) 	groupID 	= arItem.groupID;
			if(CheckAttribute(arItem,"itemType")) 	itemType	= arItem.itemType;

/*
			ok = arItem.ItemType == "WEAPON" || arItem.ItemType == "SUPPORT";
			if(CheckAttribute(arItem,"mapType"))
			{
				if(arItem.mapType == "") ok2 = true;
				else					 ok2 = false;
			}
			if (_mode == 1 && arItem.ItemType == "MAP" && ok2) continue
			ok2 = ok2 && arItem.ItemType == "MAP";
			if (_mode == 2 && !ok && ok2) continue;
			ok = ok || arItem.ItemType == "MAP";
			if (_mode == 3 && ok && ok2) continue;
			if (_mode == 4 && arItem.ItemType != "MAP") continue;
*/			

			ok = (groupID == BLADE_ITEM_TYPE) || 	// холодное оружие
				 (groupID == GUN_ITEM_TYPE)	||		// огнестрел
                 (groupID == SPYGLASS_ITEM_TYPE) || // трубы
				 (groupID == CIRASS_ITEM_TYPE) ||   // костюмы и доспехи
				 (groupID == TOOL_ITEM_TYPE) ||     // навигационные приборы котороые можно экипировать в спецслот
				 (groupID == AMMO_ITEM_TYPE);		// расходники для огнестрела
			
			ok1 = (groupID == PATENT_ITEM_TYPE)	||	// патенты
                  (groupID == MAPS_ITEM_TYPE) ||	// карты
                  (groupID == SPECIAL_ITEM_TYPE) || // спецпредметы
				  (itemType == "QUESTITEMS"); 	    // квестовые предметы			  
			
			ok2	= (groupID == ITEM_SLOT_TYPE) && (itemType == "ARTEFACT"); // артефакты
			
			ok3 = (groupID == TALISMAN_ITEM_TYPE) || ok2; // талисманы
                 
			if(_mode == 1 && groupID == MAPS_ITEM_TYPE)	continue;	
			if(_mode == 2 && !ok)  continue;
			if(_mode == 3) 
			{
				if (!ok1) continue;
				if (GetCharacterFreeItem(xi_refCharacter, arItem.id) < 1 && arItem.id != "MapsAtlas") continue;
			}
			if(_mode == 4 && !ok3) continue;	 
			
			if (GetCharacterItem(xi_refCharacter, sGood) > 0)
			{		
				GameInterface.TABLE_ITEMS.(row).index = GetItemIndex(arItem.id);
				
				GameInterface.TABLE_ITEMS.(row).td1.icon.group = arItem.picTexture;
				GameInterface.TABLE_ITEMS.(row).td1.icon.image = "itm" + arItem.picIndex;
				GameInterface.TABLE_ITEMS.(row).td1.icon.offset = "2, 0";
				GameInterface.TABLE_ITEMS.(row).td1.icon.width = 32;
				GameInterface.TABLE_ITEMS.(row).td1.icon.height = 32;
				GameInterface.TABLE_ITEMS.(row).td1.textoffset = "31,0";
				GameInterface.TABLE_ITEMS.(row).td1.str = LanguageConvertString(idLngFile, arItem.name);
				GameInterface.TABLE_ITEMS.(row).td1.scale = 0.85;
				
				GameInterface.TABLE_ITEMS.(row).td2.str   = FloatToString(stf(arItem.Weight), 1);
				GameInterface.TABLE_ITEMS.(row).td2.scale = 0.9;
				GameInterface.TABLE_ITEMS.(row).td3.str   = GetCharacterItem(xi_refCharacter, sGood);
				GameInterface.TABLE_ITEMS.(row).td3.scale = 0.9;
				GameInterface.TABLE_ITEMS.(row).td4.str   = FloatToString(stf(arItem.Weight) * sti(GameInterface.TABLE_ITEMS.(row).td3.str), 1);
				GameInterface.TABLE_ITEMS.(row).td4.scale = 0.9;
				n++;
			}
		}
    }
    
	Table_UpdateWindow("TABLE_ITEMS");
	LanguageCloseFile(idLngFile);
	if (_mode == 1)
	{
		FillItemsSelected();
	}
}

void FillItemsSelected() 
{
	int    i, picIndex;
	string sGood, sSlot, remainTime;
	int iLastGunItem;
	ref rLastGunItem;
	
	// Скроем по умолчанию
	SetNodeUsing("ITEM_1", false);
	SetNodeUsing("ITEM_2", false);
	SetNodeUsing("ITEM_3", false);
	SetNodeUsing("ITEM_4", false);
	SetNodeUsing("ITEM_5", false);
	SetNodeUsing("ITEM_6", false);
	SetNodeUsing("ITEM_7", false);
	
	SetNodeUsing("SLOT_ITEM_1", false);
	SetNodeUsing("SLOT_ITEM_2", false);
	SetNodeUsing("SLOT_ITEM_3", false);
	
	SetNewGroupPicture("SLOT_ITEM_1", "ITEMS_EMPTY", "empty");
	SetNewGroupPicture("SLOT_ITEM_2", "ITEMS_EMPTY", "empty");
	SetNewGroupPicture("SLOT_ITEM_3", "ITEMS_EMPTY", "empty");
	
	SetNodeUsing("SLOT1_TEXT", false);
	SetNodeUsing("SLOT2_TEXT", false);
	SetNodeUsing("SLOT3_TEXT", false);
	
	SetNodeUsing("SLOT_PIC_1", false);
	SetNodeUsing("SLOT_PIC_2", false);
	SetNodeUsing("SLOT_PIC_3", false);
		
    for (i = 0; i< TOTAL_ITEMS; i++)
	{
		if(!CheckAttribute(&Items[i], "ID"))
		{
			continue;
		}
		
		sGood = Items[i].id;
		
		if (GetCharacterItem(xi_refCharacter, sGood) > 0)
		{		
			/// экипировка
			if (IsEquipCharacterByItem(xi_refCharacter, sGood))
			{
				switch (Items[i].groupID) 
				{
					case BLADE_ITEM_TYPE:
						SetNewGroupPicture("ITEM_1", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetNodeUsing("ITEM_1" , true);
					break;
					case GUN_ITEM_TYPE:
						if(CheckAttribute(xi_refCharacter, "IsMushketer"))
						{
							iLastGunItem = GetItemIndex(xi_refCharacter.IsMushketer.LastGunID);
							// Покажем картинку старого пистоля, если он еще есть
							if(iLastGunItem != -1 && GetCharacterItem(xi_refCharacter, xi_refCharacter.IsMushketer.LastGunID) > 0)
							{
								rLastGunItem = &Items[iLastGunItem];
								SetNewGroupPicture("ITEM_2", rLastGunItem.picTexture, "itm" + rLastGunItem.picIndex);
								SetNodeUsing("ITEM_2" , true);
							}							
							rLastGunItem = &Items[GetItemIndex(xi_refCharacter.IsMushketer.MushketID)];
							SetNodeUsing("ITEM_5", true);
							SetNewGroupPicture("ITEM_5", rLastGunItem.picTexture, "itm" + rLastGunItem.picIndex);
						}
						else
						{
							SetNewGroupPicture("ITEM_2", Items[i].picTexture, "itm" + Items[i].picIndex);
							SetNodeUsing("ITEM_2" , true);
							SetNodeUsing("ITEM_5" , false); // Мушкет не юзается - уберем картинку
						}
					break;
					case SPYGLASS_ITEM_TYPE:
						SetNewGroupPicture("ITEM_3", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetNodeUsing("ITEM_3" , true);
					break;
					case CIRASS_ITEM_TYPE:
						SetNewGroupPicture("ITEM_4", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetNodeUsing("ITEM_4" , true);
					break;
					case TALISMAN_ITEM_TYPE:
						SetNewGroupPicture("ITEM_6", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetNodeUsing("ITEM_6" , true);
					break;
					case TOOL_ITEM_TYPE:
						SetNewGroupPicture("ITEM_7", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetNodeUsing("ITEM_7" , true);
					break;
				}
			}
			if(CheckAttribute(&Items[i], "groupID") && Items[i].groupID == ITEM_SLOT_TYPE && IsEquipCharacterByArtefact(xi_refCharacter, sGood))
			{
				sSlot = GetCharacterEquipSlot(xi_refCharacter, sGood);								
				switch (sSlot)
				{
					case ITEM_SLOT1_TYPE:
						SetNewGroupPicture("SLOT_ITEM_1", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetNodeUsing("SLOT_ITEM_1" , true);
						remainTime = GetCharacterSlotRemainTime(xi_refCharacter, ITEM_SLOT1_TYPE);
						if(CheckAttribute(&Items[i],"time") && Items[i].time > -1 && remainTime != "")
						{
							SetFormatedText("SLOT1_TEXT", remainTime + "/" + Items[i].time);
							SetNodeUsing("SLOT1_TEXT", true);	
							SetVAligmentFormatedText("SLOT1_TEXT");		
						}	
						
						picIndex = GetCharacterEquipSlotUsedPicture(xi_refCharacter, ITEM_SLOT1_TYPE);
						if(picIndex > 0) 
						{
							SetNewGroupPicture("SLOT_PIC_1", "ITEMS_USE", "items_use" + picIndex);
							SetNodeUsing("SLOT_PIC_1", true);	
						}
					break;
					case ITEM_SLOT2_TYPE:
						SetNewGroupPicture("SLOT_ITEM_2", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetNodeUsing("SLOT_ITEM_2" , true);
						remainTime = GetCharacterSlotRemainTime(xi_refCharacter, ITEM_SLOT2_TYPE);
						if(CheckAttribute(&Items[i],"time") && Items[i].time > -1 && remainTime != "")
						{
							SetFormatedText("SLOT2_TEXT", remainTime + "/" + Items[i].time);
							SetNodeUsing("SLOT2_TEXT", true);	
							SetVAligmentFormatedText("SLOT2_TEXT");		
						}	
						
						picIndex = GetCharacterEquipSlotUsedPicture(xi_refCharacter, ITEM_SLOT2_TYPE);
						if(picIndex > 0) 
						{
							SetNewGroupPicture("SLOT_PIC_2", "ITEMS_USE", "items_use" + picIndex);
							SetNodeUsing("SLOT_PIC_2", true);	
						}
					break;
					case ITEM_SLOT3_TYPE:
						SetNewGroupPicture("SLOT_ITEM_3", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetNodeUsing("SLOT_ITEM_3" , true);
						remainTime = GetCharacterSlotRemainTime(xi_refCharacter, ITEM_SLOT3_TYPE);
						if(CheckAttribute(&Items[i],"time") && Items[i].time > -1 && remainTime != "")
						{
							SetFormatedText("SLOT3_TEXT", remainTime + "/" + Items[i].time);
							SetNodeUsing("SLOT3_TEXT", true);	
							SetVAligmentFormatedText("SLOT3_TEXT");		
						}	
						
						picIndex = GetCharacterEquipSlotUsedPicture(xi_refCharacter, ITEM_SLOT3_TYPE);
						if(picIndex > 0) 
						{
							SetNewGroupPicture("SLOT_PIC_3", "ITEMS_USE", "items_use" + picIndex);
							SetNodeUsing("SLOT_PIC_3", true);	
						}
					break;
				}				
			}
		}			
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
		/*case "CHARACTER_NATION_PICTURE":
		    sHeader = XI_ConvertString("Nation");
			sText1 = GetRPGText("Nation_hint");
		break;   */
	}
	sHeader = "Items";
	sText1  = "Equipment management for you and your officers";
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
}

void HideInfoWindow()
{
	CloseTooltip();
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    
    // отрисовка инфы
    SetItemInfo();
}

void SetItemInfo()
{
	int iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	ref arItm = &Items[iGoodIndex];
	string describeStr;
	
	if(CheckAttribute(arItm,"groupID") && arItm.groupID == GUN_ITEM_TYPE && IsEquipCharacterByItem(xi_refCharacter, arItm.ID))
	{
		int    lngFileID = LanguageOpenFile("ItemsDescribe.txt");

		if (HasSubStr(arItm.id, "mushket")) describeStr = GetAssembledString(LanguageConvertString(lngFileID,"mushket parameters equipped"), arItm) + newStr();		
		else 								describeStr = GetAssembledString(LanguageConvertString(lngFileID,"weapon gun parameters equipped"), arItm) + newStr();
		describeStr = describeStr + GetAssembledString(LanguageConvertString(lngFileID, Items[iGoodIndex].describe), arItm);
		SetFormatedText("INFO_TEXT", describeStr);
		LanguageCloseFile(lngFileID);
	}
	else
	{	
		SetFormatedText("INFO_TEXT", GetItemDescribe(iGoodIndex));
	}	
	SetNewGroupPicture("INFO_PIC", Items[iGoodIndex].picTexture, "itm" + Items[iGoodIndex].picIndex);
	SetNodeUsing("INFO_TEXT", true);
	SetNodeUsing("INFO_PIC", true);
	SetVAligmentFormatedText("INFO_TEXT");
	
	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	SetSelectable("EQUIP_BUTTON",ThisItemCanBeEquip(&Items[iGoodIndex]));
}

void HideItemInfo()
{
	SetNodeUsing("INFO_TEXT", false);
	SetNodeUsing("INFO_PIC", false);
	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	SetSelectable("EQUIP_BUTTON",false);
}

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	SetCurrentNode("TABLE_ITEMS");
	HideItemInfo();
	if( sNodName == "TABBTN_1" )
	{
		SetControlsTabMode( 1 );
		return;
	}
	if( sNodName == "TABBTN_2" )
	{
		SetControlsTabMode( 2 );
		return;
	}
	if( sNodName == "TABBTN_3" )
	{
		SetControlsTabMode( 3 );
		return;
	}
	if( sNodName == "TABBTN_4" )
	{
		SetControlsTabMode( 4 );
		return;
	}
}

void SetControlsTabMode(int nMode)
{
	int nColor1 = argb(255,196,196,196);
	int nColor2 = nColor1;
	int nColor3 = nColor1;
	int nColor4 = nColor1;

	string sPic1 = "TabSelected";
	string sPic2 = sPic1;
	string sPic3 = sPic1;
	string sPic4 = sPic1;

	switch (nMode)
	{
		case 1: //
			sPic1 = "TabDeSelected";
			nColor1 = argb(255,255,255,255);
		break;
		case 2:
			sPic2 = "TabDeSelected";
			nColor2 = argb(255,255,255,255);
		break;
		case 3:
			sPic3 = "TabDeSelected";
			nColor3 = argb(255,255,255,255);
		break;
		case 4:
			sPic4 = "TabDeSelected";
			nColor4 = argb(255,255,255,255);
		break;
	}
    
	SetNewGroupPicture("TABBTN_1", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_2", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_3", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_4", "TABS", sPic4);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_1", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_2", 8,0,nColor2);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_3", 8,0,nColor3);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_4", 8,0,nColor4);
	FillControlsList(nMode);
}

void FillControlsList(int nMode)
{
	switch (nMode)
	{
	    case 1: FillItemsTable(1); break;  // все
	    case 2: FillItemsTable(2); break;  // снаряжение
	    case 3: FillItemsTable(3); break;  // остальное
	    case 4: FillItemsTable(4); break;  // карты
	}
}

bool ThisItemCanBeEquip( aref arItem )
{
	if( !CheckAttribute(arItem,"groupID") )
	{
		return false;
	}
	if( !IsCanEquiping(xi_refCharacter, arItem.groupID) )
	{
		return false;
	}	
	
	if(arItem.id == "MapsAtlas" && sti(xi_refCharacter.index) == sti(pchar.index)) 
	{
		if(IsMainCharacter(xi_refCharacter)) return true;
		return false;
	}
	// спецпредметы только для ГГ
	if (arItem.groupID == SPECIAL_ITEM_TYPE && !IsMainCharacter(xi_refCharacter)) 
	{
		return false;
	}
	if (arItem.groupID == AMMO_ITEM_TYPE) 
	{
		if (arItem.ID == "GunPowder") return false;
	}
	
	if (xi_refCharacter.id == "Mary" && arItem.groupID == BLADE_ITEM_TYPE)
	{
		return false; // чтобы нарвал не отбирали
	}
	if (xi_refCharacter.id == "Danielle" && arItem.groupID == BLADE_ITEM_TYPE)
	{
		return false; // чтобы саблю не отбирали лесник - пусть сама рашает что ей лучше то и выбирает. как Мери. 	
	}
																		   
	
	if (arItem.groupID == GUN_ITEM_TYPE) 
	{
		if (!IsMainCharacter(xi_refCharacter) && !CheckAttribute(xi_refCharacter, "CanTakeMushket")) 
		{
			return false;
		}	
		if (!CheckAttribute(arItem,"chargeQ") )
		{
			return false;
		}
		int chrgQ = sti(arItem.chargeQ);

		if (chrgQ >= 2 && !IsCharacterPerkOn(xi_refCharacter,"GunProfessional") )
		{
			if(arItem.id == "pistol9") return true;
			return false;
		}
				
		// Для мушкетов нужен соответствующий перк
		if(HasSubStr(arItem.id, "mushket") && !IsCharacterPerkOn(xi_refCharacter,"Gunman"))
		{
			return false;
		}
		
		// Нельзя экипировать мушкет в непредназначенных для этого локациях (Таверна)
		if(HasSubStr(arItem.id, "mushket") && !CanEquipMushketOnLocation(PChar.Location))
		{
			return false;
		}
	}
    
	if (arItem.groupID == ITEM_SLOT_TYPE)
	{
		if (IsEquipCharacterByArtefact(xi_refCharacter, arItem.id))
		{
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Delete that"));
			return true;
		}
		else
		{
			if(GetCharacterFreeSlot(xi_refCharacter) != SLOT_NOT_USED && IsCanArtefactBeEquipped(xi_refCharacter, arItem.id))
			{
				SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
				return true;
			}
			return false;
		}
	}	
	
    if (IsEquipCharacterByItem(xi_refCharacter, arItem.id))
	{		
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Remove that"));
		if(arItem.groupID == BLADE_ITEM_TYPE || arItem.groupID == SPYGLASS_ITEM_TYPE || arItem.groupID == PATENT_ITEM_TYPE)
		{
			return false;
		}		
		//Jason: под водой ничего нельзя снимать
		if (xi_refCharacter.location == "underwater")
		{
		    return false;
	    }
		//Jason: запрет снятия кирасы
		if (arItem.groupID == CIRASS_ITEM_TYPE && CheckAttribute(xi_refCharacter, "GenQuest.CirassExchangeDisable"))
	    {
		    return false;
	    }
	}
	else
	{ // Jason: убираем влияние перка кирасы - кирасу носим без перка
		/*if (arItem.groupID == CIRASS_ITEM_TYPE && !IsCharacterPerkOn(xi_refCharacter,"Ciras") && arItem.Clothes == false)
	    {	
		    return false;
	    }*/
		//Jason: под водой ничего нельзя одевать
		if (xi_refCharacter.location == "underwater")
	    {
		    return false;
	    }
		//Jason: запрет одевания кирасы
		if (arItem.groupID == CIRASS_ITEM_TYPE && CheckAttribute(xi_refCharacter, "GenQuest.CirassExchangeDisable"))
	    {
		    return false;
	    }
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));			
	}
	
	if (IsMainCharacter(xi_refCharacter) || CheckAttribute(xi_refCharacter, "CanTakeMushket"))
	{
		if(CheckAttribute(xi_refCharacter, "IsMushketer"))
		{
			if(arItem.ID == xi_refCharacter.IsMushketer.MushketID)
		{
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Remove that"));
			return true;
		}
		
		if(arItem.groupID == BLADE_ITEM_TYPE || arItem.groupID == SPYGLASS_ITEM_TYPE || arItem.groupID == GUN_ITEM_TYPE || arItem.groupID == CIRASS_ITEM_TYPE)
		{
			return false;
		}
	}
	}
	
	return true;
}

void EquipPress()
{
	int  iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	ref itmRef = &Items[iGoodIndex];
	string totalInfo;
	int  i;
	
	if (CheckAttribute(itmRef, "groupID"))
	{
		string itmGroup = itmRef.groupID;
		if (itmGroup == MAPS_ITEM_TYPE)
		{
			// Warship. Отличная карта, у нее отдельный интерфейс
			if(itmRef.ID == "Map_Best")
			{
				PChar.ShowBestMap = true; // Флаг, что смотрим из интерфейса придметов
				IDoExit(RC_INTERFACE_BEST_MAP);
				return;
			}
			// Ugeen --> интерфейс атласа карт
			if(itmRef.ID == "MapsAtlas") // взяли атлас карт
			{
				PChar.ShowMapsAtlas = true; // Флаг, что смотрим из интерфейса предметов
				IDoExit(RC_INTERFACE_MAPVIEW);
				return;
			}
			// Ugeen --> специальная квестовая карта
			if(itmRef.id == "mapQuest")
			{
				totalInfo = GenQuest_GetQuestTreasureMapDescription(itmRef);
				SetNewPicture("MAP_PICTURE", "interfaces\Maps\treasure map.tga");
				SetFormatedText("MAP_TEXT", totalInfo);
				SetVAligmentFormatedText("MAP_TEXT");
				ShowMapWindow();
				return;
			}
			// Addon 2016-1 Jason пиратская линейка
			if(itmRef.id == "mapEnrico")
			{
				totalInfo = "Go west from Laguna de Caratasca. Keep to the right side of the road. Get through a logjam. The path will lead you to the ruins of old town, destroyed by an earthquake 20 years ago. Find treasures in the dungeons below abandoned mines.";
				SetNewPicture("MAP_PICTURE", "interfaces\Maps\treasure map.tga");
				SetFormatedText("MAP_TEXT", totalInfo);
				SetVAligmentFormatedText("MAP_TEXT");
				ShowMapWindow();
				return;
			}
            if (itmRef.id == "map_full" || itmRef.id == "map_part1" || itmRef.id == "map_part2")
            {// клады
            	SetNewPicture("MAP_PICTURE", "interfaces\Maps\treasure map2.tga");
            	if (GetCharacterItem(pchar, "map_part1")>0  && GetCharacterItem(pchar, "map_part2")>0)
			    {
			        TakeNItems(xi_refCharacter, "map_part1", -1);
			        TakeNItems(xi_refCharacter, "map_part2", -1);
			        TakeNItems(pchar, "map_full",   1);
			        itmRef = &Items[Items_FindItem("map_full", &itmRef)];
			        // здесь генерация назначение и типа клада
			        pchar.GenQuest.TreasureBuild = true;
			        FillMapForTreasure(itmRef);
			        SetVariable();
			    }
			    // тут применяем логику двух кусков, из них одна карта <--
			    if (itmRef.mapType == "Full")
			    {
		            if (sti(itmRef.MapTypeIdx) == -1)
				    {
                        SetFormatedText("MAP_TEXT", GetConvertStr("type_fake", "MapDescribe.txt"));
					    DeleteAttribute(itmRef, "MapIslId");
					    TakeNItems(GetMainCharacter(), "map_full", -1);
				    }
				    else
				    {
				        if (!CheckAttribute(itmRef, "MapIslId"))
				        {
				            FillMapForTreasure(itmRef); //заполним если смотрим карту из сундука
				        }
                        //totalInfo = GetConvertStr(itmRef.MapIslId, "LocLables.txt");
                        i = FindLocation(itmRef.MapLocId);  // ищем ареал
						if (i != -1 && locations[i].islandId != "Mein")
                        {
                            totalInfo = GetConvertStr(locations[i].islandId, "LocLables.txt");
                            totalInfo = GetConvertStr("type_full_" + itmRef.MapTypeIdx + "_isl", "MapDescribe.txt") + " " + totalInfo;
                        }
                        else
                        {
                            totalInfo = GetConvertStr("type_full_" + itmRef.MapTypeIdx + "_mein", "MapDescribe.txt");
                        }
						itmRef.MapIslName = totalInfo;
						totalInfo = GetConvertStr(itmRef.MapLocId, "MapDescribe.txt") + ", " + GetConvertStr(itmRef.MapLocId + "_" + itmRef.MapBoxId, "MapDescribe.txt");
				        itmRef.MaplocName = totalInfo;

				        totalInfo = GetConvertStr("type_full_" + itmRef.MapTypeIdx, "MapDescribe.txt");
				        totalInfo = GetAssembledString(totalInfo, itmRef);
				        SetFormatedText("MAP_TEXT", totalInfo);
				    }
			    }
			    else
			    {
           			SetFormatedText("MAP_TEXT", GetConvertStr("type_part", "MapDescribe.txt"));
				}
            	SetVAligmentFormatedText("MAP_TEXT");
            }
            else
            {
            	SetNewPicture("MAP_PICTURE", "interfaces\Maps\" + itmRef.imageTga + ".tga");
            	SetFormatedText("MAP_TEXT", "");
            }
            ShowMapWindow();
		}
		else
		{ 
			if (itmGroup == SPECIAL_ITEM_TYPE) // Jason, спецпредметы
			{
				if (itmRef.id == "Ultimate_potion") UltimatePotionEffect(); // зелье команчей
				if (itmRef.id == "berserker_potion") // зелье берсеркера
				{
					if (GetCharacterPerkUsing(pchar, "Rush"))
					{
						ActivateCharacterPerk(pchar, "Rush");
						PerkBerserkerReaction();
					}
					else PlaySound("interface\knock.wav");
				}
				if (itmRef.id == "potion7") // слезы Иш-Чель
				{
					Log_Info("An Indian healing potion was used");
					PlaySound("Ambient\Tavern\glotok_001.wav");
					AddCharacterHealth(pchar, 10);
					AddCharacterMaxHealth(pchar, 4);
					RemoveItems(pchar, "potion7", 1);
				}
				// мангароса
				if (itmRef.id == "mangarosapower") 	MangarosaEffect("power"); 	// зелье силы
				if (itmRef.id == "mangarosafast") 	MangarosaEffect("fast"); 	// зелье реакции
				if (itmRef.id == "mangarosatotal") 	MangarosaEffect("total"); 	// комплексное зелье
				// калеуче
				if (findsubstr(itmRef.id, "kaleuche_amulet", 0) != -1)
				{
					Log_Info("A powerful potion was used");
					PlaySound("Ambient\Tavern\glotok_001.wav");
					AddCharacterHealth(pchar, 5);
					RemoveItems(pchar, itmRef.id, 1);
					Caleuche_MangarosaPotionEffect(itmRef.id); 	
				}
				// калеуче - ящик Мерримана
				if (itmRef.id == "MerrimanBook") Caleuche_MerrimanBoxOpen();
				if (findsubstr(itmRef.id, "recipe_" , 0) != -1) // рецепты
				{
					if (isMultiObjectKnown(itmRef.result))
					{
						PlaySound("interface\knock.wav");
						log_info("You already know this recipe");
					}
					else
					{
						RemoveItems(pchar, itmRef.id, 1);
						AddQuestRecordInfo("Recipe", itmRef.result);
						SetAlchemyRecipeKnown(itmRef.result);
					}
				}
				if (findsubstr(itmRef.id, "purse" , 0) != -1) // кошельки
				{
					RemoveItems(pchar, itmRef.id, 1);
					TakeNItems(pchar, itmRef.result, sti(itmRef.result.qty));
					PlaySound("Ambient\Tavern\monetki_taverna_001.wav");
					log_info("You have acquired "+sti(itmRef.result.qty)+XI_ConvertString("dublon4")+"");
				}
				if (itmRef.id == "RingCapBook") // СЖ пинаса 'Санта-Люсия' и дневник Колхауна
				{
					RemoveItems(pchar, itmRef.id, 1);
					AddQuestRecordInfo("RingCapBook", "1");
					pchar.questTemp.LSC.Ring.ReadCapBook = "true";
				}
				if (itmRef.id == "ArchyBook") // // Jason 070712 дневник Колхауна
				{
					RemoveItems(pchar, itmRef.id, 1); 
					GuardOT_ReadArchyBook(); // Jason 050712
				}
				if (itmRef.id == "specialletter") // спецписьмо
				{
					RemoveItems(pchar, itmRef.id, 1);
					AddQuestRecordInfo(itmRef.text, "1");
					pchar.GenQuest.specialletter.read = itmRef.text;
					if (pchar.GenQuest.specialletter.read == "Letter_Vincento") GuardOT_VinsentoLetterRead();
					if (pchar.GenQuest.specialletter.read == "Letter_Vincento_next") GuardOT_VinsentoNextLetterRead();
					if (pchar.GenQuest.specialletter.read == "Letter_Vincento_last") Ksochitam_VinsentoLastLetterRead();
					if (pchar.GenQuest.specialletter.read == "Letter_Dichoso") Tieyasal_DichosoLetterRead();
				}
				if (itmRef.id == "skinmap") // // Jason 120712 карта двух появлений
				{
					int mark = sti(itmRef.mark);
					SetNewPicture("MAP_PICTURE", "interfaces\Maps\skinmap_"+mark+".tga");
					ShowMapWindow();
					if (CheckAttribute(pchar, "questTemp.Ksochitam"))
					{
						if (pchar.questTemp.Ksochitam == "skinmap_1") Ksochitam_LookSkinmapFirstTime();
						if (pchar.questTemp.Ksochitam == "skinmap_2") Ksochitam_LookSkinmapSecondTime();
					}
					return;
				}
				if (itmRef.id == "mark_map") // // Jason 130712 карта с пометками
				{
					mark = sti(itmRef.mark);
					SetNewPicture("MAP_PICTURE", "interfaces\Maps\map_TM_"+mark+".tga");
					ShowMapWindow();
					return;
				}
				if (itmRef.id == "SQCapBook") // // Jason 240712 СЖ капитана Санта-Квитерии
				{
					RemoveItems(pchar, itmRef.id, 1); 
					AddQuestRecordInfo("SQCapBook", "1");
					pchar.questTemp.Ksochitam.SQCapBookRead = "true";
				}
				if (itmRef.id == "wolfreeks_book") Mtraxx_WolfreekReadLogbook(); // // Addon 2016-1 Jason Пиратская линейка журнал Вульфрика
				SetVariable();
				return;
			}
			else
			{
				bool bCanmakeMushketer = (IsMainCharacter(xi_refCharacter)) || (CheckAttribute(xi_refCharacter, "CanTakeMushket"))
				if(HasSubStr(itmRef.id, "Mushket") && bCanmakeMushketer)
				{
					if (IsMainCharacter(xi_refCharacter)) // ГГ
				{
					if(!CheckAttribute(PChar, "IsMushketer")) // Не мушкетер. Делаем мушкетером
					{
						SetMainCharacterToMushketer(itmRef.id, true);
					}
					else // Мушкетер. Делаем обычным фехтовальщиком
					{
						SetMainCharacterToMushketer("", false);
					}
				}
				else
				{
						if(!CheckAttribute(xi_refCharacter, "IsMushketer")) // Не мушкетер. Делаем мушкетером
						{
							SetOfficerToMushketer(xi_refCharacter, itmRef.id, true);
						}
						else // Мушкетер. Делаем обычным фехтовальщиком
						{
							SetOfficerToMushketer(xi_refCharacter, itmRef.id, false);
						}
					}
				}
				else
				{
					if (itmGroup == ITEM_SLOT_TYPE)
					{
						if(IsEquipCharacterByArtefact(xi_refCharacter, itmRef.id))
						{
							RemoveCharacterArtefactEquip(xi_refCharacter, GetCharacterEquipSlot(xi_refCharacter, itmRef.id));
							SetVariable();
							return;
						}
						else
						{
							EquipCharacterByArtefact(xi_refCharacter, itmRef.id);
						}
						if (itmRef.id == "indian_poison") // ugeen 2016
						{
							Achievment_SetStat(xi_refCharacter, 71, 1);
						}
					}
					else
					{
						if (itmRef.groupID == AMMO_ITEM_TYPE) 
						{
							string sGun = GetCharacterEquipByGroup(xi_refCharacter, GUN_ITEM_TYPE);
							if (sGun == "pistol7")
							{
								PlaySound("interface\knock.wav");
								return;
							}
							if (itmRef.ID == "bullet" || itmRef.ID == "cartridge")
							{	
								if (sGun == "pistol2" || sGun == "pistol3" || sGun == "pistol8" || sGun == "mushket3" || sGun == "grape_mushket" || sGun == "mushket6")
								{
									PlaySound("interface\knock.wav");
									return;
								}
							}
							if (itmRef.ID == "grapeshot")
							{	
								if (sGun == "pistol1" || sGun == "pistol4" || sGun == "pistol5" || sGun == "pistol6" || sGun == "pistol9" || sGun == "mushket1" || sGun == "mushket2" || sGun == "mushket5" || sGun == "grape_mushket" || sGun == "mushket2x2")
								{
									PlaySound("interface\knock.wav");
									return;
								}
							}
							if (itmRef.ID == "powder_pellet" || itmRef.ID == "grenade")
							{	
								if (sGun != "grape_mushket")
								{
									PlaySound("interface\knock.wav");
									return;
								}
							}
							if (itmRef.ID == "gunechin")
							{	
								if (sGun == "pistol1" || sGun == "pistol2" || sGun == "pistol3" || sGun == "pistol4" || sGun == "pistol5" || sGun == "pistol6" || sGun == "pistol9" || sGun == "mushket1" || sGun == "mushket2" || sGun == "mushket3" || sGun == "mushket5" || sGun == "grape_mushket" || sGun == "mushket2x2")
								{
									PlaySound("interface\knock.wav");
									return;
								}
							}
							if (itmRef.ID == "harpoon")
							{	
								if (sGun != "pistol8")
								{
									PlaySound("interface\knock.wav");
									return;
								}
							}
							LAi_SetCharacterUseBullet(xi_refCharacter, itmRef.ID);
							LAi_GunSetUnload(xi_refCharacter);
							log_info("Ammo received - "+GetConvertStr(itmRef.name, "ItemsDescribe.txt")+"");
							PlaySound("People Fight\reload1.wav");
							SetVariable();
							return;
						}
						else
						{
							if(IsEquipCharacterByItem(xi_refCharacter, itmRef.id))
							{
								RemoveCharacterEquip(xi_refCharacter, itmGroup);
							}
							else
							{
								EquipCharacterByItem(xi_refCharacter, itmRef.id);
							}
						}
					}	
				}
			}
			FillItemsSelected();
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
			SetSelectable("EQUIP_BUTTON",ThisItemCanBeEquip(&Items[iGoodIndex]));
			SetItemInfo();
		}
	}
} 

void ExitMapWindow()
{
	XI_WindowShow("MAP_WINDOW", false);
	XI_WindowDisable("MAP_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_ITEMS");
}

void ShowMapWindow()
{
	XI_WindowShow("MAP_WINDOW", true);
	XI_WindowDisable("MAP_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("MAP_TEXT");
}