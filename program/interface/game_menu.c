bool DLCState;
int	 DLCCount; 	
int	 DLCAppID = 0; 

void InitInterface_gm(string iniName)
{
	GameInterface.title = "titleGameMenu";

	SetTimeScale(0.0);
	locCameraSleep(true);

	EngineLayersOffOn(true);

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("frame","IProcessFrame",0);

	SetEventHandler("UpdatesClick","UpdatesClick",0);
	SetEventHandler("LoadClick","LoadClick",0);
	SetEventHandler("SaveClick","SaveClick",0);
	SetEventHandler("ResumeClick","ResumeClick",0);
	SetEventHandler("OptionsClick","OptionsClick",0);
	SetEventHandler("QuitClick","QuitClick",0);
	SetEventHandler("QuitProcess","QuitProcess",0);
	SetEventHandler("evntSteamOverlayActivated","UpdateInterface",0);

	SetEventHandler("ConfirmExitClick","ConfirmExitClick",0);
	SetEventHandler("ConfirmExitCancel","ConfirmExitCancel",0);

	InterfaceStates.showGameMenuOnExit = true;

	if(CheckAttribute(&InterfaceStates,"Buttons.Resume.enable") && sti(InterfaceStates.Buttons.Resume.enable) == true)
	{
		SetSelectable("MB_RESUME", true);
	} 
	else 
	{
		SetSelectable("MB_RESUME", false);
	}

	if (QuickSaveGameEnabledHardcore()) // boal 09.07.06
	{
		SetSelectable("MB_SAVE", true);
	} 
	else 
	{
		SetSelectable("MB_SAVE", false);
	}

	if (!CheckSaveGameEnabled())
	{
		SetSelectable("MB_SAVE", false);
	}
	
	string Vers = VERSION_NUMBER1 + GetVerNum();	
	SetFormatedText("VERSION_TEXT", Vers);

	string sText = "";

	sText = "BlackMark Studio, Akella ";
	sText = sText + "- 2019";
	SetFormatedText("COPYRIGHTS_TEXT", sText);
	
	string sDLC = "";
	SetFormatedText("DLC_TEXT", sDLC);

	SetNewPicture("LOGO", "Interfaces\SL_logo.tga");

	if(LAi_IsBoardingProcess())	SetSelectable("MB_RESUME",false);

	if(bSteamAchievements && GetSteamEnabled())
	{
			DLCAppID = CheckUpdates();	
			if(DLCAppID > 0) // есть обновления
			{
				SetSelectable("MB_UPDATES", true);
			}
			else
			{	// обновлений нет
				SetSelectable("MB_UPDATES", false);
			}
	}
	else
	{ // обновлений нет
		SetSelectable("MB_UPDATES", false);
	}
}


void IProcessFrame()
{
}

void ProcessCancelExit()
{
	if(CheckAttribute(&InterfaceStates,"Buttons.Resume.enable") && sti(InterfaceStates.Buttons.Resume.enable) == true)
	IDoExit(RC_INTERFACE_DO_RESUME_GAME, true);
}

void IDoExit(int exitCode, bool bClear)
{
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("frame","IProcessFrame");

	DelEventHandler("UpdatesClick","UpdatesClick");
	DelEventHandler("LoadClick","LoadClick");
	DelEventHandler("SaveClick","SaveClick");
	DelEventHandler("ResumeClick","ResumeClick");
	DelEventHandler("OptionsClick","OptionsClick");
	DelEventHandler("QuitClick","QuitClick");
    DelEventHandler("QuitProcess","QuitProcess");
	DelEventHandler("evntSteamOverlayActivated","UpdateInterface");
    
	DelEventHandler("ConfirmExitClick","ConfirmExitClick");
	DelEventHandler("ConfirmExitCancel","ConfirmExitCancel");

	SetTimeScale(1.0);
	TimeScaleCounter = 0;
	DelPerkFromActiveList("TimeSpeed");
	locCameraSleep(false);
	DeleteAttribute(pchar, "pause");

	interfaceResultCommand = exitCode;

	if( interfaceResultCommand == RC_INTERFACE_DO_RESUME_GAME ) 
	{
		DeleteEntitiesByType("scrshoter");
	}
	EndCancelInterface(bClear);
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "MB_UPDATES":
			if (comName == "click" || comName == "activate")
			{
				if(DLCAppID > 0 && bSteamAchievements && GetSteamEnabled())
				{
					DLCState = DLCStartOverlay(MAIN_APPID); // открываем окошко в стиме для главной игры а не для дополнения
				}
			}
			break;

		case "MB_OPTIONS":
			if (comName == "click" || comName == "activate")
			{
				IDoExit(RC_INTERFACE_DO_OPTIONS, true);
			}	
            break;		
			
		case "CONFIRM_WINDOW_MB_YES":
			if (comName == "click" || comName == "activate")
			{
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
	}

}

void UpdatesClick()
{
	IDoExit( RC_INTERFACE_DO_CHECK_UPDATES, true);
}

void LoadClick()
{
	IDoExit( RC_INTERFACE_DO_LOAD_GAME, true);
}

void SaveClick()
{
	IDoExit( RC_INTERFACE_DO_SAVE_GAME, true);
}

void ResumeClick()
{
	IDoExit(RC_INTERFACE_DO_RESUME_GAME, true);
}

void OptionsClick()
{
	IDoExit(RC_INTERFACE_DO_OPTIONS, true);
}

void QuitClick()
{
	XI_WindowDisable("MAIN_WINDOW",true);
	XI_WindowDisable("CONFIRM_EXIT_WINDOW",false);
	XI_WindowShow("CONFIRM_EXIT_WINDOW", true);
	SetCurrentNode("CONFIRM_EXIT_NO");
}

void ConfirmExitClick()
{
    PauseParticles(true); //fix вылета у форта
	EngineLayersOffOn(false);
	QuitProcess();
}

void ConfirmExitCancel()
{
    XI_WindowDisable("CONFIRM_EXIT_WINDOW",true);
	XI_WindowShow("CONFIRM_EXIT_WINDOW",false);
	XI_WindowDisable("MAIN_WINDOW",false);
	SetCurrentNode("MB_EXITGAME");
}

void ShowConfirmWindow(bool show)
{
	if (show)
	{
		SetCurrentNode("CONFIRM_WINDOW_MB_NO");

		XI_WindowDisable("MAIN_WINDOW", true);
		XI_WindowDisable("CONFIRM_WINDOW", false);
		XI_WindowShow("CONFIRM_WINDOW", true);
		EI_CreateFrame("CONFIRM_WINDOW_BORDER",190,190,610,360);

	} 
	else 
	{
		XI_WindowDisable("CONFIRM_WINDOW", true);
		XI_WindowShow("CONFIRM_WINDOW", false);
		XI_WindowDisable("MAIN_WINDOW", false);

		if(GetSelectable("MB_RESUME")) 
			SetCurrentNode("MB_RESUME"); 
		else
			SetCurrentNode("MB_LOAD");
	}
}

void QuitProcess()
{
    // вылетам у форта НЕТ -->
    if (bSeaActive && !bAbordageStarted)
    {
		SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
	}
	// вылетам у форта НЕТ <--
	IDoExit(-1, false);
	ExitProgram();
}

void UpdateInterface()
{
	bool isSteamOverlayEnabled = GetEventData();

	if(!bSteamAchievements || !GetSteamEnabled()) return;
	
	trace("isSteamOverlayEnabled : " + isSteamOverlayEnabled );
	if(!isSteamOverlayEnabled) // оверлей закрыт
	{
		DLCAppID = CheckUpdates();	
		if(DLCAppID > 0) 
		{   // есть обновления
			SetSelectable("MB_UPDATES", true);
		}
		else
		{	// обновлений нет
			SetSelectable("MB_UPDATES", false);
		}
	}
	else // оверлей открыт, ничего не делаем
	{
	}
}

bool CheckUpdates()
{
	bool   bOk  = false;
	bool   bOk1 = false;
	bool   bOk2 = false;
	int	   i;
	int	   appID;
	string sText = "";
	int    dlcCount = 0; 

	if(bSteamAchievements && GetSteamEnabled())
	{
		dlcCount = GetDLCCount();
		for(i = 0; i < dlcCount; i++)
		{
			appID = GetDLCData(i);
			if( appID > 0 )
			{
				bOk = GetDLCenabled(appID);
				if(!bOk) 
				{
					bOk1 = true;
				}	
				else
				{
					switch (i)
					{
						case 0:						
							sText = sText + " + 'The Сaleuche'";
						break;
					
						case 1:
							sText = sText + " + 'The Final Lesson'";		
						break;
						
						case 2:
							sText = sText + " + 'Flying the Jolly Roger'";		
						break;
						
						case 3:
							sText = sText + NewStr() + " + 'Hero of the Nation'";	
							bOk2 = true;							
						break;
						
						case 4:
							if(bOk2)   	sText = sText + " + 'Happily Ever After'";		
							else 		sText = sText + NewStr() + " + 'Happily Ever After'";		
						break;
						
					}
				}
			}
		}
		SetFormatedText("DLC_TEXT", sText);
	}
	return bOk1;
}


