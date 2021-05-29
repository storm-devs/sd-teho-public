//  интерфейс Выбора герба на парус (boal 08.02.08)
ref    shref;
int    price;

void InitInterface_R(string iniName, ref _shipyarder)
{
	StartAboveForm(true);
	// лочим квест и карту
	bQuestCheckProcessFreeze = true;
	int st = GetCharacterShipType(pchar);
	shref = GetRealShip(st);

	price = GetSailsTuningPrice(Pchar, _shipyarder, SAILSGERALD_PRICE_RATE);

	SetEventHandler("GetInterfaceTexture", "ScrollGetTexture", 0);
	LoadIcons("ships\gerald\", "*.tga.tx", "SCROLL_GERALD", 0);

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("ChangeSelectScrollImage", "ChangeSelectScrollImage", 0);

	if(!CheckAttribute(&GameInterface,"SCROLL_GERALD.current"))
	{
		GameInterface.SCROLL_GERALD.current = 0;
	}
	CheckChangeSailStatus();
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void IDoExit(int exitCode)
{
    EndAboveForm(true);
    
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
    DelEventHandler("GetInterfaceTexture", "ScrollGetTexture");
    DelEventHandler("ChangeSelectScrollImage", "ChangeSelectScrollImage");
    
    UnloadIcons("SCROLL_GERALD");
    
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
    PostEvent("StopQuestCheckProcessFreeze", 100);//заморозка проверки квестов
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
    	case "B_OK":
    		if(comName=="activate" || comName=="click")
    		{
                SetNewSailsGerald();
    		}
    	break;
    	
    	case "B_REMOVE":
    		if(comName=="activate" || comName=="click")
    		{
                ClearSailsGerald();
    		}
    	break;
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

int ScrollGetTexture()
{
	string sName = GetEventData();
	int iPicIndex = GetEventData();
	string sScrollID = GetEventData();
	
	string sAttr = "pic" + (iPicIndex + 1);
	int iTexture = sti(GameInterface.(sScrollID).(sAttr).TexId);

	return iTexture;
}

void ChangeSelectScrollImage()
{
	string sNod = GetEventData();
	int nIdx = GetEventData();
	if (sNod == "SCROLL_GERALD")
	{
		GameInterface.SCROLL_GERALD.current = nIdx;
		CheckChangeSailStatus();
	}
}

void CheckChangeSailStatus()
{
	bool bNewValue = true;
	
	if (CheckAttribute(shref, "ShipSails.Gerald_Name"))
	{
		bNewValue = false;

		int nEmblem = sti(GameInterface.SCROLL_GERALD.current);

		string sattr = "pic"+(nEmblem+1);
		if (GameInterface.SCROLL_GERALD.(sattr).FileName != shref.ShipSails.Gerald_Name)
		{
			bNewValue = true;
		}
	}
	SetSelectable("B_OK", bNewValue);
	SetSelectable("B_REMOVE", !bNewValue);
}

void SetNewSailsGerald()
{
	int nEmblem = sti(GameInterface.SCROLL_GERALD.current);

	string sattr = "pic"+(nEmblem+1);
	shref.ShipSails.Gerald_Name = GameInterface.SCROLL_GERALD.(sattr).FileName;
	Log_testInfo(shref.ShipSails.Gerald_Name);
	AddMoneyToCharacter(Pchar, -price);
	WaitDate("",0,0,0, 1, 30);
	ProcessCancelExit();
}

void ClearSailsGerald()
{
    AddMoneyToCharacter(Pchar, -price);
	DeleteAttribute(shref, "ShipSails.Gerald_Name");
	WaitDate("",0,0,0, 1, 30);
	ProcessCancelExit();
}