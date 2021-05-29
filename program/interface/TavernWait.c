int iHourWait = 0;

void InitInterface(string iniName)
{
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	locCameraSleep(true);
	SetTimeScale(0.0);
	EngineLayersOffOn(true);
	CreateString(true, "Frame_Caption", "Recreation", FONT_CAPTION, COLOR_NORMAL, 400, 205, SCRIPT_ALIGN_CENTER, 1.2);
	CreateString(true, "MainString", "How many hours do you want to relax?", FONT_CAPTION, COLOR_NORMAL, 400, 235, SCRIPT_ALIGN_CENTER, 1.2);
	SetEventHandler("ievnt_command", "ProcCommand", 0);
	SetEventHandler("exitcancel", "ExitCancel", 0);
	SetEventHandler("eSlideChange", "ProcSlideChange", 0);
	GameInterface.nodes.HOURS_SLIDE.value = 0.5;
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "HOURS_SLIDE", 0, 0.5);
	SetCurrentNode("HOURS_SLIDE");
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "HOURS_SLIDE":
			if(comName=="downstep")
			{
				if(GetSelectable("OK_BTN"))
					SetCurrentNode("OK_BTN");
				else
					SetCurrentNode("CANCEL_BTN");
			}
		break;
	
		case "OK_BTN":
			if(comName=="activate" || comName=="click")
				WaitProcess(iHourWait);
				
			if(comName=="rightstep")
				SetCurrentNode("CANCEL_BTN");
			
			if(comName=="upstep")
				SetCurrentNode("HOURS_SLIDE");
		break;
			
		case "CANCEL_BTN":
			if(comName=="leftstep")
			{
				if(GetSelectable("OK_BTN"))
					SetCurrentNode("OK_BTN");
			}
		
			if(comName=="upstep")
				SetCurrentNode("HOURS_SLIDE");
		break;
	}
}

void ProcSlideChange()
{
	string 	sNodeName 	= GetEventData();
	int 	iVal 		= GetEventData(); // int GameInterface.nodes.<node_name>.value
	float 	fVal 		= GetEventData(); // float GameInterface.nodes.<node_name>.value

	if(sNodeName == "HOURS_SLIDE")
	{
		iHourWait = sti(fVal*24);
		CanWait();
		SetFormatedText("INFO_TEXT", GetCorrectHourString(iHourWait));
	}
}

void WaitProcess(int _iHour)
{
	ExitCancel();
	pchar.quest.waithours = _iHour;
	DoQuestFunctionDelay("WaitNextHours", 0.1);
}

void IDoExit(int exitCode, bool bClear)
{
	EngineLayersOffOn(false);
	locCameraSleep(false);
	SetTimeScale(1.0);
	DelEventHandler("ievnt_command", "ProcCommand");
	DelEventHandler("exitcancel", "ExitCancel");
	DelEventHandler("eSlideChange", "ProcSlideChange");
	interfaceResultCommand = exitCode;
	EndCancelInterface(bClear);
}

void ExitCancel()
{
	IDoExit(RC_INTERFACE_TAVERN_WAIT, true);
}

void CanWait()
{
	if(iHourWait <= 0 || chrDisableReloadToLocation)
		SetSelectable("OK_BTN", false);
	else
		SetSelectable("OK_BTN", true);
}

string GetCorrectHourString(int _hour)
{
	string sRetStr = "";
	
	switch(_hour)
	{
		case "0": 	sRetStr = "Less than one hour"; 				break;
		case "1": 	sRetStr = "About 1 hour . . ."; 	break;
		case "2": 	sRetStr = "About 2 hours . . ."; 	break;
		case "3": 	sRetStr = "About 3 hours . . ."; 	break;
		case "4": 	sRetStr = "About 4 hours . . ."; 	break;
		case "5": 	sRetStr = "About 5 hours . . ."; 	break;
		case "6": 	sRetStr = "About 6 hours . . ."; 	break;
		case "7": 	sRetStr = "About 7 hours . . ."; 	break;
		case "8": 	sRetStr = "About 8 hours . . ."; 	break;
		case "9": 	sRetStr = "About 9 hours . . ."; 	break;
		case "10": 	sRetStr = "About 10 hours . . ."; 	break;
		case "11": 	sRetStr = "About 11 hours . . ."; 	break;
		case "12": 	sRetStr = "About 12 hours . . ."; 	break;
		case "13": 	sRetStr = "About 13 hours . . ."; 	break;
		case "14": 	sRetStr = "About 14 hours . . ."; 	break;
		case "15": 	sRetStr = "About 15 hours . . ."; 	break;
		case "16": 	sRetStr = "About 16 hours . . ."; 	break;
		case "17": 	sRetStr = "About 17 hours . . ."; 	break;
		case "18": 	sRetStr = "About 18 hours . . ."; 	break;
		case "19": 	sRetStr = "About 19 hours . . ."; 	break;
		case "20": 	sRetStr = "About 20 hours . . ."; 	break;
		case "21": 	sRetStr = "About 21 hours . . ."; 	break;
		case "22": 	sRetStr = "About 22 hours . . ."; 	break;
		case "23": 	sRetStr = "About 23 hours . . ."; 	break;
		case "24": 	sRetStr = "About 1 day . . ."; 	break;
	}

	return sRetStr;
}