// boal установки игры BETATEST 20.08.04 -->

void InitInterface(string iniName)
{

    GameInterface.title = "titleBoal_SetupGame";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
    
    SetNodeUsing("QuestLogShow",false);
    SetNodeUsing("BETTAMODE",false);
    SetNodeUsing("TestRansackCaptain",false);
    SetNodeUsing("LocatorShow", false);
    SetNodeUsing("NoEatNoRats",false);
    SetNodeUsing("ExpLogShow",false);
    SetNodeUsing("PGGLogShow",false);
    SetNodeUsing("CameraEnableFree",false);
    SetNodeUsing("WorldAlivePause",false);
        
	if (MOD_BETTATESTMODE == "On")
	{
        SetNodeUsing("NoEatNoRats",true);
	    TmpI_ShowNoEatNoRats();
        SetNodeUsing("QuestLogShow",true);
	    TmpI_ShowQuestLogShow();
	    SetNodeUsing("TestRansackCaptain",true);
	    TmpI_ShowTestRansackCaptain();
	    SetNodeUsing("BETTAMODE",true);
	    TmpI_ShowBettaTestMode();
	    SetNodeUsing("LocatorShow",true);
	    TmpI_ShowLocatorShow();
	    SetNodeUsing("ExpLogShow",true);
	    TmpI_ShowExpLogShow();
	    SetNodeUsing("PGGLogShow",true);
	    TmpI_ShowPGGLogShow();
	    SetNodeUsing("CameraEnableFree",true);
	    TmpI_ShowCameraEnableFree();
	    SetNodeUsing("WorldAlivePause",true);
	    TmpI_ShowWorldAlivePause();
	}
	if (MOD_BETTATESTMODE == "Test")
	{
        SetNodeUsing("QuestLogShow",true);
	    TmpI_ShowQuestLogShow();
	    SetNodeUsing("LocatorShow",true);
	    TmpI_ShowLocatorShow();
	    SetNodeUsing("BETTAMODE",true);
	    TmpI_ShowBettaTestMode();
	}
	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
}

void ProcessCancelExit()
{
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
    DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcessCommandExecute");

    interfaceResultCommand = RC_INTERFACE_QUICK_SAVE;
    
    EndCancelInterface(true);
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	ref chr = GetMainCharacter();

	switch(nodName)
	{
    	case "QuestLogShow":
    		if(comName=="activate" || comName=="click")
    		{
    			bQuestLogShow = !bQuestLogShow;
    			TmpI_ShowQuestLogShow();
    		}
    	break;
    	
    	case "TestRansackCaptain":
    		if(comName=="activate" || comName=="click")
    		{
    			TestRansackCaptain = !TestRansackCaptain;
    			TmpI_ShowTestRansackCaptain();
    		}
    	break;
    	
    	case "BETTAMODE":
    		if(comName=="activate" || comName=="click")
    		{
    			bBettaTestMode = !bBettaTestMode;
    			TmpI_ShowBettaTestMode();
    		}
    	break;
    	
    	case "LocatorShow":
    		if(comName=="activate" || comName=="click")
    		{
    			bLocatorShow = !bLocatorShow;
    			TmpI_ShowLocatorShow();
    			if (bLocatorShow)
    			{
                    ShowAllLocators();
                    worldMap.debug = "true";
					worldMap.evwin = "true";
    			}
    			else
    			{
                    HideAllLocators();
                    worldMap.debug = "false";
					worldMap.evwin = "false";
    			}
    		}
    	break;
    	
    	case "ExpLogShow":
    		if(comName=="activate" || comName=="click")
    		{
    			bExpLogShow = !bExpLogShow;
    			TmpI_ShowExpLogShow();
    		}
    	break;
    	
    	case "NoEatNoRats":
    		if(comName=="activate" || comName=="click")
    		{
    			bNoEatNoRats = !bNoEatNoRats;
    			TmpI_ShowNoEatNoRats();
    		}
    	break;
    	
    	case "PGGLogShow":
    		if(comName=="activate" || comName=="click")
    		{
    			bPGGLogShow = !bPGGLogShow;
    			TmpI_ShowPGGLogShow();
    		}
    	break;
    	
    	case "CameraEnableFree":
    		if(comName=="activate" || comName=="click")
    		{
    			locCameraEnableFree = !locCameraEnableFree;
    			TmpI_ShowCameraEnableFree();
    		}
    	break;
    	
    	case "WorldAlivePause":
    		if(comName=="activate" || comName=="click")
    		{
    			bWorldAlivePause = !bWorldAlivePause;
    			TmpI_ShowWorldAlivePause();
    		}
    	break;
	}
}
// bNoEatNoRats
void TmpI_ShowNoEatNoRats()
{
	if(!bNoEatNoRats) {
		CreateImage("iNoEatNoRats","icons","complete",0,0,0,0);
	} else {
		CreateImage("iNoEatNoRats","icons","complete",560,70,592,102);
	}
}
//  QuestLogShow
void TmpI_ShowQuestLogShow()
{
	if(!bQuestLogShow) {
		CreateImage("QuestLog","icons","complete",0,0,0,0);
	} else {
		CreateImage("QuestLog","icons","complete",560,125,592,157);
	}
}
// TestRansackCaptain
void TmpI_ShowTestRansackCaptain()
{
	if(!TestRansackCaptain) {
		CreateImage("TestRansack","icons","complete",0,0,0,0);
	} else {
		CreateImage("TestRansack","icons","complete",560,180,592,212);
	}
}
// LocatorShow
void TmpI_ShowLocatorShow()
{
	if(!bLocatorShow) {
		CreateImage("bLocatorShow","icons","complete",0,0,0,0);
	} else {
		CreateImage("bLocatorShow","icons","complete",560,235,592,267);
	}
}
// ExpLogShow
void TmpI_ShowExpLogShow()
{
	if(!bExpLogShow) {
		CreateImage("ExpLog","icons","complete",0,0,0,0);
	} else {
		CreateImage("ExpLog","icons","complete",560,290,592,322);
	}
}

// PGGLogShow
void TmpI_ShowPGGLogShow()
{
	if(!bPGGLogShow) {
		CreateImage("iPGGLogShow","icons","complete",0,0,0,0);
	} else {
		CreateImage("iPGGLogShow","icons","complete",560,345,592,377);
	}
}

// CameraEnableFree
void TmpI_ShowCameraEnableFree()
{
	if(!locCameraEnableFree) {
		CreateImage("iCameraEnableFree","icons","complete",0,0,0,0);
	} else {
		CreateImage("iCameraEnableFree","icons","complete",560,400,592,432);
	}
}

// WorldAlivePause
void TmpI_ShowWorldAlivePause()
{
	if(!bWorldAlivePause) {
		CreateImage("iWorldAlivePause","icons","complete",0,0,0,0);
	} else {
		CreateImage("iWorldAlivePause","icons","complete",560,455,592,487);
	}
}

// BETTAMODE
void TmpI_ShowBettaTestMode()
{
	if(!bBettaTestMode) {
		CreateImage("BettaTestMode","icons","complete",0,0,0,0);
	} else {
		CreateImage("BettaTestMode","icons","complete",560,510,592,542);
	}
}
