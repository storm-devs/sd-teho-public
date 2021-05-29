///  BOAL переделка для SLib 02.07.06
/// Ugeen --> переделка для ККС 23.08.10
#define DEFAULT_NAME "Player"
#define DEFAULT_PASS ""

bool isOkExit = false;
int idLngFile = -1;
string sCharacterName;

bool g_bToolTipStarted = false;
int heroQty = 0;
string totalInfo;
string CurTable, CurRow, CurCol = 0;
int iSelected, iSelectedCol;
ref	nulChr;

void InitInterface(string iniName)
{
	nulChr = &NullCharacter;

	GameInterface.title = "titleCharacterSelect";
	GameInterface.faces.current = 1;
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetMainCharacterIndex(1);

	sCharacterName = pchar.id;
	
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"BLAZE", 5, 1);

	GameInterface.PROFILE_NAME.str = DEFAULT_NAME;
	GameInterface.PROFILE_PASS.str = DEFAULT_PASS;
	
    LoadStartGameParam(); // boal
    
	startHeroType = 1; // fix
    
	SetEventHandler("exitCancel", "exitCancel", 0);
	SetEventHandler("exitOk", "exitOk", 0);
	SetEventHandler("confirmChangeProfileName", "confirmChangeProfileName", 0);
	SetEventHandler("MouseRClickUP","HideInfo",0);
	SetEventHandler("ShowInfo","ShowInfo",0);
	SetEventHandler("OnTableClick", "OnTableClick", 0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("noteOk","procNoteOk",0);

	SetEventHandler("frame","IProcessFrame",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	
	CCS_SetNewMainCharacter(&NullCharacter, startHeroType);
	SetCharacterSPECIAL(NullCharacter.HeroParam.HeroType, &NullCharacter);
	SetSPECIALMiniTableCharSelect("TABLE_SMALLSKILL", &NullCharacter);
	SetSetupInfoText();
	
	SelectNation();

	if (!CheckAttribute(&GameInterface, "SavePath"))
		GameInterface.SavePath = "SAVE";
		
	EI_CreateFrame("CHARACTER_BIG_PICTURE_BORDER", 15,67,215,290);
    EI_CreateHLine("CHARACTER_BIG_PICTURE_BORDER", 18,91,212,1, 4);
	
	EI_CreateFrame("SETUP_BIG_PICTURE_BORDER",230,305,785,585); 
    EI_CreateHLine("SETUP_BIG_PICTURE_BORDER",233,535,782,1, 4);
    
    heroQty  = MaxHeroQty;
	
	if(heroQty == 1)
	{
		SetNodeUsing("LEFTCHANGE_CHARACTER",  false);
		SetNodeUsing("RIGHTCHANGE_CHARACTER", false);
	}
	
    if (!CheckAttribute(&NullCharacter, "HeroParam.HeroType") || !CheckAttribute(&NullCharacter, "HeroParam.nation"))
    {   // иначе уже загружен и выбран ГГ, смотрим настройки и идем обратно
		SetVariable(true);
	}
	else
	{
	    SetVariable(false);
	}
	TmpI_ShowLevelComplexity();
	SetByDefault();
	
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_SMALLSKILL", 0 );
}

void SetByDefault()
{
	if (iArcadeSails == 1)// 1 0
    {
    	CheckButton_SetState("CHECK_ARCADESAIL", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_ARCADESAIL", 2, true);
    }
    if (bRechargePistolOnLine)// 1 0
    {
    	CheckButton_SetState("CHECK_PISTOL", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_PISTOL", 1, false);
    }
    if (bHardcoreGame)// 1 0
    {
    	CheckButton_SetState("CHECK_HARDCORE", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_HARDCORE", 1, false);
    }
	
	if (bSeaBattleSave)// 1 0
    {
    	CheckButton_SetState("CHECK_SEABATTLESAVE", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_SEABATTLESAVE", 1, false);
    }	
	
	if (bRains)// 1 0
    {
    	CheckButton_SetState("CHECK_RAINS", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_RAINS", 1, false);
    }		
	
	if (bPartitionSet)// 1 0
    {
    	CheckButton_SetState("CHECK_PARTITION", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_PARTITION", 1, false);
    }
}

void IProcessFrame()
{
	if(GetCurrentNode() == "PROFILE_NAME")
	{
		if(!CheckAttribute(&characters[GetCharacterIndex(sCharacterName)], "profile.name"))
		{
			confirmChangeProfileName();
		}

		if(characters[GetCharacterIndex(sCharacterName)].profile.name!= GameInterface.PROFILE_NAME.str)
		{
			confirmChangeProfileName();
		}
	}

	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ARCADESAIL", 3, 1))
	{
		iArcadeSails = 1;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ARCADESAIL", 3, 2))
	{
		iArcadeSails = 0;
	}
	///
 	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_PISTOL", 3, 1))
	{
		bRechargePistolOnLine = true;
	}
	else
	{
		bRechargePistolOnLine = false;
	}
	///
 	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_HARDCORE", 3, 1))
	{
		bHardcoreGame = true;
	}
	else
	{
		bHardcoreGame = false;
	}
	
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_SEABATTLESAVE", 3, 1))
	{
		bSeaBattleSave = true;
	}
	else
	{
		bSeaBattleSave = false;
	}		
	
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_RAINS", 3, 1))
	{
		bRains = true;
	}
	else
	{
		bRains = false;
	}		
	
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_PARTITION", 3, 1))	
	{
		bPartitionSet = true;
	}
	else
	{
		bPartitionSet = false;
	}
}

void exitCancel()
{
	if( CheckAttribute(&InterfaceStates,"showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true)
	{	
		isOkExit = true;
		IDoExit(RC_INTERFACE_LAUNCH_GAMEMENU, true);
		return;
	}
	IDoExit(RC_INTERFACE_CHARACTER_SELECT_EXIT, true);
	ReturnToMainMenu();
}

void exitOk()
{
	if( !IsCorrectProfileName() )
	{
		ShowNoteText(true);
		return;
	}

	confirmChangeProfileName();

	if (!ProfileExists())
	{
		CreateProfileFolders();

        isOkExit = true;
		IDoExit(RC_INTERFACE_CHARACTER_SELECT_EXIT, true);
	} 
	else 
	{

		ShowConfirmWindow(true);
	}
}

bool IsCorrectProfileName()
{
	int n,nLen;
	string str,sCurProfileName;

	sCurProfileName = GameInterface.PROFILE_NAME.str;
	nLen = strlen(sCurProfileName);
	if( nLen==0 ) {return false;}

	for( n=0; n<nLen; n++ )
	{
		str = GetSymbol(&sCurProfileName,n);
		if( str=="*" ) {return false;}
		if( str=="?" ) {return false;}
		if( str=="\" ) {return false;}
		if( str=="/" ) {return false;}
	}
	return true;
}

void ShowNoteText(bool bShow)
{
	if( bShow ) {
		XI_WindowDisable("MAIN_WINDOW", true);

		XI_WindowDisable("NOTE_WINDOW", false);
		XI_WindowShow("NOTE_WINDOW", true);

		SetCurrentNode("NOTE_WINDOW_OK");
	} else {
		XI_WindowDisable("MAIN_WINDOW", false);

		XI_WindowDisable("NOTE_WINDOW", true);
		XI_WindowShow("NOTE_WINDOW", false);

		SetCurrentNode("PROFILE_NAME");
	}
}

void procNoteOk()
{
	ShowNoteText(false);
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
        case "LEFTCHANGE_COMPLEX":
			if(comName=="click")
			{
				if (MOD_SKILL_ENEMY_RATE > 2)
				{
					MOD_SKILL_ENEMY_RATE -= 2;
				}
				TmpI_ShowLevelComplexity();
			}
		break;

		case "RIGHTCHANGE_COMPLEX":
			if(comName=="click")
			{
			    if (MOD_SKILL_ENEMY_RATE < 10)
			    {
	               MOD_SKILL_ENEMY_RATE += 2;
	            }
	            TmpI_ShowLevelComplexity();
			}
		break;
		
		case "CONFIRM_WINDOW_MB_YES":

			if (comName == "click" || comName == "activate")
			{
				isOkExit = true;
				SaveStartGameParam(); // boal
				IDoExit(RC_INTERFACE_CHARACTER_SELECT_EXIT, true);
			}

			if (comName == "deactivate")
			{
				ShowConfirmWindow(false);
			}

			break;

		case "CONFIRM_WINDOW_MB_NO":

			if (comName == "click" || comName == "activate")
			{
				ShowConfirmWindow(false);
			}

			if (comName == "deactivate")
			{

				ShowConfirmWindow(false);
			}

			break;
			
		////////////////////////////////
		case "OK_BUTTON":
    		if(comName=="leftstep")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    		if(comName=="rightstep")
    		{
                ProcessCommandExecuteRight();
    		}
    	break;
    	case "CANCEL_BUTTON":
    		if(comName=="leftstep")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    		if(comName=="rightstep")
    		{
                ProcessCommandExecuteRight();
    		}
    	break;
    	
		case "LEFTCHANGE_CHARACTER":
    		if(comName=="click")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    	break;

    	case "RIGHTCHANGE_CHARACTER":
    		if(comName=="click")
    		{
    		    ProcessCommandExecuteRight();
    		}
    	break;

		case "LEFTCHANGE_SETUP":
    		if(comName=="click")
    		{
				ProcessCommandExecuteTypeLeft();
    		}
    	break;

    	case "RIGHTCHANGE_SETUP":
    		if(comName=="click")
    		{
				ProcessCommandExecuteTypeRight();
    		}
    	break;
		
		
    	case "FACEPICT":
    		if(comName=="click")
    		{
				totalInfo = nulChr.info;
				SetInfoText();
    		}
    	break;
		
		case "TABLE_SMALLSKILL":
			if(comName=="click")
			{
			}
		break;	
	}

}

void ShowConfirmWindow(bool show)
{
	if (show)
	{
		SetCurrentNode("CONFIRM_WINDOW_MB_NO");

		XI_WindowDisable("MAIN_WINDOW", true);
		XI_WindowDisable("CONFIRM_WINDOW", false);
		XI_WindowShow("CONFIRM_WINDOW", true);
		EI_CreateFrame("CONFIRM_WINDOW_BORDERS",190,190,610,360);
	} 
	else 
	{
		XI_WindowDisable("CONFIRM_WINDOW", true);
		XI_WindowShow("CONFIRM_WINDOW", false);
		XI_WindowDisable("MAIN_WINDOW", false);
		SetCurrentNode("OK_BUTTON");
	}
}

//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------
void CreateProfileFolders()
{
	String folder = GameInterface.SavePath + "\";
	folder+= pchar.profile.name;

	if (XI_CheckFolder(folder)) return;

	if(!XI_CreateFolder(folder)) 
		trace("Could not create profile folder");
}
//----------------------------------------------------------------------------------------------------
void DeleteProfile()
{
	String folder;

	folder = GameInterface.SavePath + "\"+ pchar.profile.name;

	int nSaveNum= 0;
	string saveName;
	int nSaveSize;

	String path = GameInterface.SavePath;
	GameInterface.SavePath = folder;

    while( SendMessage(&GameInterface,"llee",MSG_INTERFACE_SAVE_FILE_FIND,nSaveNum,&saveName,&nSaveSize)!=0 )
    {
		nSaveNum++;
		SendMessage(&GameInterface,"ls",MSG_INTERFACE_DELETE_SAVE_FILE,saveName);
    }

	GameInterface.SavePath = path;
	XI_DeleteFolder(folder);
}
//----------------------------------------------------------------------------------------------------
bool ProfileExists()
{
	String folder = GameInterface.SavePath + "\";

	folder+= pchar.profile.name;

	return (XI_CheckFolder(folder)); 
}
//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------

void SelectNation()
{
	int iNation = sti(nulChr.nation);
	string sNationPict = GetNationNameByType(iNation);				
	SetNewGroupPicture("NATIONS_PICTURE", "NATIONS", sNationPict);
	NullCharacter.HeroParam.Nation = iNation;
	totalInfo = GetRPGText(Nations[iNation].Name + "_descr");
	SetInfoText();
}

void IDoExit(int exitCode, bool bCode)
{
	DelEventHandler("exitCancel", "exitCancel");
	DelEventHandler("exitOk", "exitOk");
	DelEventHandler("MouseRClickUP","HideInfo");
	DelEventHandler("ShowInfo","ShowInfo");
	DelEventHandler("noteOk","procNoteOk");	
	DelEventHandler("frame","IProcessFrame");
	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("ievnt_command","ProcessCommandExecute");

	if(isOkExit == false)
	{
		EndCancelInterface(bCode);
	}
	else
	{
		MOD_EXP_RATE = makeint(5 + MOD_SKILL_ENEMY_RATE);  // 0т 5 до 15
		interfaceResultCommand = exitCode;
		EndCancelInterface(bCode);
	}
}

void confirmChangeProfileName()
{	
	PlayerProfile.name = GameInterface.PROFILE_NAME.str;
	pchar.profile.name = GameInterface.PROFILE_NAME.str;
}

void confirmChangeProfilePass()
{	
	PlayerProfile.password = GameInterface.PROFILE_PASS.str;
	pchar.profile.pass = GameInterface.PROFILE_PASS.str;
	SetCurrentNode("OK_BUTTON");
}

void ShowInfo()
{
	g_bToolTipStarted = true;
	string sHeader = "TEST";
	string sNode = GetCurrentNode();
	string sNation;

	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";

	switch(sNode)
	{
	
		case "TABLE_SMALLSKILL":
		    sHeader = XI_ConvertString("Characteristics");
			sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).(CurCol).UserData.ID);7
		break;
	
		case "NATIONS_PICTURE":
			sNation = GetNationNameByType(sti(nulChr.nation));
			sHeader = XI_ConvertString(sNation);
			sText1 = GetRPGText(sNation + "_descr");
		break;

		case "COMPLEX_TYPE":
			sHeader = XI_ConvertString("m_Complexity");
			sText1 = GetRPGText("LevelComplexity_desc");
		break;
				
		case "CHECK_ARCADESAIL":
			sHeader = XI_ConvertString("Sailing Mode");
			sText1 = GetRPGText("ArcadeSailMode_desc");
		break;
		
		case "CHECK_PISTOL":
			sHeader = XI_ConvertString("New Fight Mode");
			sText1 = GetRPGText("RechargePistolOnLine_desc");
		break;
		
		case "CHECK_HARDCORE":
			sHeader = XI_ConvertString("HardcoreGame");
			sText1 = GetRPGText("HardcoreGame_desc");
		break;
		
		case "CHECK_PARTITION":
			sHeader = XI_ConvertString("Partition Set");
			sText1 = GetRPGText("Partition_hint");
		break;
        case "CHECK_SEABATTLESAVE":
			sHeader = XI_ConvertString("Sea Battle Save");
			sText1 = GetRPGText("SeaBattleSave_desc");
		break;
        case "CHECK_RAINS":
			sHeader = XI_ConvertString("Rains");
			sText1 = GetRPGText("Rains_desc");
		break;
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
}

void HideInfo()
{
	if( g_bToolTipStarted ) 
	{
		g_bToolTipStarted = false;
		CloseTooltip();
		SetCurrentNode("OK_BUTTON");
	}
}

void ProcessCommandExecuteLeft()
{
    if (startHeroType > 1)
    {
       startHeroType--;
    }
    else
    {
       startHeroType = heroQty;
    }
    SetVariable(true);
}

void ProcessCommandExecuteRight()
{
    if (startHeroType < heroQty)
    {
       startHeroType++;
    }
    else
    {
       startHeroType = 1;
    }
    SetVariable(true);
}

void SetVariable(bool _init)
{
	if (startHeroType < 1) startHeroType = 1; // fix
	CCS_SetNewMainCharacter(&NullCharacter, startHeroType);
	SetFormatedText("HERO_NAME", GetFullName(&NullCharacter));
    SetFormatedText("HERO_TYPE", XI_ConvertString(nulChr.HeroParam.HeroType));

	SetNewPicture("FACEPICT", "interfaces\portraits\256\face_" + CCS_GetNewMainCharacterFace(&NullCharacter) + ".tga");
	SelectNation();
	totalInfo = nulChr.info;
    SetInfoText();
	
	SetFormatedText("SETUP_FRAME_CAPTION", XI_ConvertString(NullCharacter.HeroParam.HeroType)); 
	SetCharacterSPECIAL(NullCharacter.HeroParam.HeroType, &NullCharacter);
	SetSPECIALMiniTableCharSelect("TABLE_SMALLSKILL", &NullCharacter);
	SetSetupInfoText();
}

void SetInfoText()
{
    SetFormatedText("INFO_TEXT", totalInfo);
    SetVAligmentFormatedText("INFO_TEXT");
}

void SetSetupInfoText()
{
    SetFormatedText("SETUP_TEXT", SetSetupInfo(NullCharacter.HeroParam.HeroType));
    SetVAligmentFormatedText("SETUP_TEXT");
}

void TmpI_ShowLevelComplexity()
{
    SetFormatedText("COMPLEX_TYPE", GetLevelComplexity(MOD_SKILL_ENEMY_RATE));
}

void ProcessCommandExecuteTypeLeft()
{
    NullCharacter.HeroParam.HeroType = GetCharacterType(NullCharacter.HeroParam.HeroType, -1);
    SetFormatedText("SETUP_FRAME_CAPTION", XI_ConvertString(NullCharacter.HeroParam.HeroType)); 
	SetCharacterSPECIAL(NullCharacter.HeroParam.HeroType, &NullCharacter);
	SetSPECIALMiniTableCharSelect("TABLE_SMALLSKILL", &NullCharacter);
	SetSetupInfoText();
}

void ProcessCommandExecuteTypeRight()
{
    NullCharacter.HeroParam.HeroType = GetCharacterType(NullCharacter.HeroParam.HeroType, 1);
    SetFormatedText("SETUP_FRAME_CAPTION", XI_ConvertString(NullCharacter.HeroParam.HeroType));
	SetCharacterSPECIAL(NullCharacter.HeroParam.HeroType, &NullCharacter);
	SetSPECIALMiniTableCharSelect("TABLE_SMALLSKILL", &NullCharacter);
	SetSetupInfoText();	
}

string GetCharacterType(string type, int direction)
{
    switch (type)
	{
        case "HeroType_1":
            if (direction > 0)
            {
    	    	type = "HeroType_2";
    	    }
    	    else
    	    {
    	        type = "HeroType_4";
    	    }
	    break;

	    case "HeroType_2":
            if (direction > 0)
            {
    	    	type = "HeroType_3";
    	    }
    	    else
    	    {
    	        type = "HeroType_1";
    	    }
	    break;

	    case "HeroType_3":
            if (direction > 0)
            {
    	    	type = "HeroType_4";
    	    }
    	    else
    	    {
    	        type = "HeroType_2";
    	    }
	    break;
		
		case "HeroType_4":
            if (direction > 0)
            {
    	    	type = "HeroType_1";
    	    }
    	    else
    	    {
    	        type = "HeroType_3";
    	    }
	    break;		
	}

	return type;
}

string SetSetupInfo(string type)
{
	string setupInfo;
	switch (type)
	{
		case "HeroType_1":
			setupInfo = "Light armor is 20% more effective." + NewStr() +
						"Received damage doesn't make you loose energy, you also have a better skill for rapiers from the start.";
		break;
		case "HeroType_2":
			setupInfo = "Discounts and mark-ups are increased by 15%, rats spoil twice less goods. " + NewStr() +
						"Stealth operations are more effective, you also have a better skill for sabres from the start.";
		break;
		case "HeroType_3":
			setupInfo = "Energy regeneration is 15% faster. " + NewStr() +
						"Heavy armour is 15% more effective, you also have a better skill for broadswords and axes from the start.";
		break;
		case "HeroType_4":
			setupInfo = "You reload your firearms 40% faster." + NewStr() +
						"Cannons in your disposal explode much less often, you have a better skill for firearms from the start and your fire suppresses the enemy.";
		break;
	}
	return setupInfo;
}

void SetCharacterSPECIAL(string type, ref ch)
{
	switch (type)
	{
		case "HeroType_1":
			SetSPECIAL(ch, 5, 6, 6, 5, 7, 7, 6);
			SetSelfSkill(ch, 15, 5, 3, 8, 10);
			SetShipSkill(ch, 12, 5, 6, 3, 3, 3, 3, 3, 15);
		break;
		case "HeroType_2":
			SetSPECIAL(ch, 7, 4, 7, 6, 6, 7, 5);
			SetSelfSkill(ch, 4, 15, 4, 6, 8);
			SetShipSkill(ch, 15, 15, 3, 3, 3, 3, 3, 3, 8);
		break;
		case "HeroType_3":
			SetSPECIAL(ch, 10, 3, 8, 5, 4, 8, 4);
			SetSelfSkill(ch, 3, 5, 15, 7, 7);
			SetShipSkill(ch, 5, 3, 3, 8, 3, 10, 8, 3, 3);
		break;
		case "HeroType_4":
			SetSPECIAL(ch, 4, 9, 6, 4, 5, 5, 9);
			SetSelfSkill(ch, 5, 5, 5, 15, 20);
			SetShipSkill(ch, 10, 3, 15, 12, 3, 3, 3, 3, 12);
		break;
	}
}
		
void SetSPECIALMiniTableCharSelect(string _tabName, ref _chr)
{
    int     i;
	string  row, skillName, col;
    int     diff, skillVal;
    
    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	row = "tr1";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SPECIALType", i);
		GameInterface.(_tabName).(row).(col).UserData.ID = skillName;
		GameInterface.(_tabName).(row).(col).fontidx = 0;
		GameInterface.(_tabName).(row).(col).scale = 0.85;
		GameInterface.(_tabName).(row).(col).textoffset = "-5,-6";
		GameInterface.(_tabName).(row).(col).str = XI_ConvertString(skillName + "T");
	}
	row = "tr2";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SPECIALType", i);
		GameInterface.(_tabName).(row).(col).UserData.ID = skillName;
        skillVal = GetCharacterSPECIALCharSelect(_chr, skillName);
		GameInterface.(_tabName).(row).(col).fontidx = 1;
		GameInterface.(_tabName).(row).(col).scale = 0.95;
		GameInterface.(_tabName).(row).(col).textoffset = "-5,-2";
		GameInterface.(_tabName).(row).(col).str = skillVal;		
     	GameInterface.(_tabName).(row).(col).color = argb(255,255,255,255);		
	}
	
	// прорисовка
	Table_UpdateWindow(_tabName);
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
}

void RefreshTableByFrameEvent()
{
	DelEventHandler("frame", "RefreshTableByFrameEvent");
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_SMALLSKILL", 0 );
}

int GetCharacterSPECIALCharSelect(ref _refCharacter, string skillName)
{
	if (!CheckAttribute(_refCharacter,"SPECIAL."+skillName) )
    {
        return 3;
    }
	int skillN = sti(_refCharacter.SPECIAL.(skillName));
	
	if (skillN <= 1) skillN = 1;
	if( skillN > SPECIAL_MAX ) skillN = SPECIAL_MAX;

	return skillN;
}

void OnTableClick()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
	iSelectedCol = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected + 1);
	CurCol   =  "td" + (iSelectedCol);
	Table_UpdateWindow(sControl);
}

void CS_TableSelectChange()
{
	String sControl = GetEventData();
	iSelected = GetEventData();
	CurTable = sControl;
	CurRow   =  "tr" + (iSelected + 1);
	Table_UpdateWindow(sControl);
}
