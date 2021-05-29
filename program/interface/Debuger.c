//  boal 14.02.06 меню дебугера
string totalInfo;
int idLngFile = -1;
int remInt = 0;

void InitInterface(string iniName)
{
 	StartAboveForm(true);
	
	GameInterface.title = "titleBoal_Debug";
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	
	CalculateInfoData();

	CalculateCheatsInfo(); 

	SetFormatedText("INFO_TEXT",totalInfo);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0); 
	SetEventHandler("exitCancel","ProcessCancelExit",0); 
	SetEventHandler("evntDoPostExit","DoPostExit",0); 
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("SetScrollerPos","SetScrollerPos",0);
	SetEventHandler("ScrollPosChange","ProcScrollPosChange",0);
	SetEventHandler("ScrollTopChange","ProcScrollChange",0);

    GameInterface.reload_edit.str = "Pirates_Shipyard, reload, reload1";
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_QUICK_SAVE );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_QUICK_SAVE );
}

void IDoExit(int exitCode)
{
    EndAboveForm(true);
	
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("ievnt_command","ProcCommand");
 	DelEventHandler("SetScrollerPos","SetScrollerPos");
	DelEventHandler("ScrollPosChange","ProcScrollPosChange");
	DelEventHandler("ScrollTopChange","ProcScrollChange");

	if(bSeaActive)
    {
        RefreshBattleInterface();
    }
	
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}


void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void CalculateInfoData()
{
	// тут высчитываем нужную информацию и выводим в totalInfo - Инициализация -->
	totalInfo = "This is cheat menu. Buttons: "+NewStr();
	totalInfo = totalInfo + "F1 - " + descF1 + NewStr() +
	                        "F2 - " + descF2 + NewStr() +
	                        "F3 - " + descF3 + NewStr() +
	                        "F4 - " + descF4 + NewStr() +
	                        "F5 - " + descF5 + NewStr() +
	                        "F6 - " + descF6 + NewStr() +
	                        "F7 - " + descF7 + NewStr() +
	                        "F8 - " + descF8 + NewStr() +
	                        "F9 - " + descF9 + NewStr() +
	                        "F10 - " + descF10 + NewStr() +
	                        "F11 - " + descF11 + NewStr() +
	                        "F12 - " + descF12 + NewStr() +
	                        "F13 - " + descF13 + NewStr() +
	                        "F14 - " + descF14 + NewStr() +
	                        "F15 - " + descF15 + NewStr() +
	                        "F16 - " + descF16 + NewStr() +
	                        "F17 - " + descF17 + NewStr() +
	                        "F18 - " + descF18 + NewStr() +
                            "F19 - " + descF19 + NewStr() +
                            "F20 - " + descF20 + NewStr() +
                            "F21 - " + descF21 + NewStr() +
                            "F22 - " + descF22 + NewStr() +
                            "F23 - " + descF23 + NewStr() +
	                        "F24 - " + descF24 + NewStr() +
	                        "F25 - " + descF25 + NewStr() +
	                        "F26 - " + descF26 + NewStr() +
	                        "F27 - " + descF27 + NewStr() +
	                        "F28 - " + descF28 + NewStr() +
	                        "F29 - " + descF29 + NewStr() +
	                        "F30 - " + descF30 + NewStr() +
							"F31 - " + descF31 + NewStr() +
	                        "F32 - " + descF32 + NewStr() +
							"F33 - " + descF33;
	// перевод строки (по другому у меня не вышло) +LanguageConvertString(idLngFile,"new_string");
    // тут высчитываем нужную информацию и выводим в totalInfo <--
}
void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
	    case "B_F1":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF1();
		  }
	    break;
	    case "B_F2":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF2();
		  }
	    break;
	    case "B_F3":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF3();
		  }
	    break;
	    case "B_F4":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF4();
		  }
	    break;
	    case "B_F5":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF5();
		  }
	    break;

	    case "B_F6":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF6();
		  }
	    break;

	    case "B_F7":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF7();
		  }
	    break;

	    case "B_F8":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF8();
		  }
	    break;

	    case "B_F9":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF9();
		  }
	    break;

	    case "B_F10":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF10();
		  }
	    break;

	    case "B_F11":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF11();
		  }
	    break;

	    case "B_F12":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF12();
		  }
	    break;

	    case "B_F13":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF13();
		  }
	    break;

	    case "B_F14":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF14();
		  }
	    break;

	    case "B_F15":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF15();
		  }
	    break;

	    case "B_F16":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF16();
		  }
	    break;

	    case "B_F17":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF17();
		  }
	    break;

	    case "B_F18":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF18();
		  }
	    break;
	    
	    case "B_F19":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF19();
		  }
	    break;

        case "B_F20":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF20();
		  }
	    break;
	    
	    case "B_F21":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF21();
		  }
	    break;
	    case "B_F22":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF22();
		  }
	    break;
	    case "B_F23":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF23();
		  }
	    break;
	    case "B_F24":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF24();
		  }
	    break;
	    case "B_F25":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF25();
		  }
	    break;
	    case "B_F26":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF26();
		  }
	    break;
	    case "B_F27":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF27();
		  }
	    break;
	    case "B_F28":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF28();
		  }
	    break;
	    case "B_F29":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF29();
		  }
	    break;
	    case "B_F30":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF30();
		  }
	    break;
	    case "B_31":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF31();
		}
	    break;
	    case "B_32":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF32();
		}
	    break;		
		case "B_33":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF33();
		}
	    break;		
	    case "B_BETA":
		  if(comName=="activate" || comName=="click")
		  {
              IDoExit(RC_INTERFACE_DO_BOAL_BETA);
		  }
	    break;
	    case "B_RELOAD":
		  if(comName=="activate" || comName=="click")
		  {
              ReloadByStr();
		  }
	    break;
	}
	
	CalculateCheatsInfo(); 
}

string descF1 = "Cheat 1";

void CalculateInfoDataF1()
{
	totalInfo = descF1;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F1", 1);
}

string descF2 = "Cheat 2";

void CalculateInfoDataF2()
{
	totalInfo = descF2;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F2", 1);
}

string descF3 = "Cheat 3";

void CalculateInfoDataF3()
{
	totalInfo = descF3;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F3", 1);
}

string descF4 = "Cheat 4";

void CalculateInfoDataF4()
{
	totalInfo = descF4;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F4", 1);
}

string descF5 = "Cheat 5";
int BOAL_debug_num = 1;
void CalculateInfoDataF5()
{
	totalInfo = descF5;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F5", 1);
}

string descF6 = "Cheat 6";

void CalculateInfoDataF6()
{
	totalInfo = descF6;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F6", 1);
}

string descF7 = "Cheat 7";

void CalculateInfoDataF7()
{
	totalInfo = descF7;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F7", 1);
}

string descF8 = "Cheat 8";

void CalculateInfoDataF8()
{
	totalInfo = descF8;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F8", 1);
}

string descF9 = "Cheat 9";

void CalculateInfoDataF9()
{
	totalInfo = descF9;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F9", 1);
}

string descF10 = "Cheat 10";

void CalculateInfoDataF10()
{
	totalInfo = descF10;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F10", 1);
}

string descF11 = "Cheat 11";

void CalculateInfoDataF11()
{
	totalInfo = descF11;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F11", 1);
}

string descF12 = "Cheat 12";

void CalculateInfoDataF12()
{
	totalInfo = descF12;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F12", 1);
}

string descF13 = "Cheat 13";
void CalculateInfoDataF13()
{
	totalInfo = descF13;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F13", 1);
}

string descF14 = "Cheat 14";

void CalculateInfoDataF14()
{
	totalInfo = descF14;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F14", 1);
}

string descF15 = "Cheat 15";

void CalculateInfoDataF15()
{
	totalInfo = descF15;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F15", 1);
}

string descF16 = "Cheat 16";

void CalculateInfoDataF16()
{
	totalInfo = descF16;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F16", 1);
}

string descF17 = "Cheat 17";

void CalculateInfoDataF17()
{
	totalInfo = descF17;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F17", 1);
}

string descF18 = "Cheat 18";

void CalculateInfoDataF18()
{
	totalInfo = descF18;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F18", 1);
}

string descF19 = "Cheat 19";
void CalculateInfoDataF19()
{
    totalInfo = descF19;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F19", 1);
}

string descF20 = "Cheat 20";
void CalculateInfoDataF20()
{
    totalInfo = descF20;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F20", 1);
}

string descF21 = "Cheat 21";
void CalculateInfoDataF21()
{
   totalInfo = descF21;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F21", 1);
}

string descF22 = "Cheat 22";
void CalculateInfoDataF22()
{
	totalInfo = descF22;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F22", 1);
}

string descF23 = "Cheat 23";
void CalculateInfoDataF23()
{
	totalInfo = descF23;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F23", 1);
}

string descF24 = "Cheat 24";
void CalculateInfoDataF24()
{
   totalInfo = descF24;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F24", 1);
}

string descF25 = "Cheat 25";
void CalculateInfoDataF25()
{
   totalInfo = descF25;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F25", 1);
}

string descF26 = "Cheat 26";
void CalculateInfoDataF26()
{
	totalInfo = descF26;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.26", 1);
}

string descF27 = "Cheat 27";
void CalculateInfoDataF27()
{
   totalInfo = descF27;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F27", 1);
}

string descF28 = "Cheat 28";
void CalculateInfoDataF28()
{
    totalInfo = descF28;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F28", 1);

}

string descF29 = "Cheat 29";
void CalculateInfoDataF29()
{
    totalInfo = descF29;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F29", 1);
}

string descF30 = "Cheat 30";
void CalculateInfoDataF30()
{
    totalInfo = descF30;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F30", 1);
}

string descF31 = "Cheat 31";
void CalculateInfoDataF31()
{
	totalInfo = descF31;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F31", 1);
}

string descF32 = "Cheat 32";
void CalculateInfoDataF32()
{
	totalInfo = descF32;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F32", 1);
}

string descF33 = "Cheat 33";
void CalculateInfoDataF33()
{
	totalInfo = descF33;
	PlaySound("interface\knock.wav");
    totalInfo = totalInfo + NewStr() + NewStr() + "Success";
    SetFormatedText("INFO_TEXT",totalInfo);
	Statistic_AddValue(PChar, "Cheats.F33", 1);
}

void ShipRepair(ref chr)
{
	int hp = MakeInt(GetHullPercent(chr));
	int sp = MakeInt(GetSailPercent(chr));	
	trace("hp " + hp + " sp " + sp);
	
	// процент ремонта в день (при ремонте на глобальной карте)
	float sail_RPD = GetSailRPD(chr);
	float hull_RPD = GetHullRPD(chr);	
	trace("hull_RPD " + hull_RPD + " sail_RPD " + sail_RPD);
	
	float timeHull, timeSail, timeMast;
	
	timeHull  = 0.0;
	timeSail  = 0.0;
	timeMast  = 0.0;
	
	float SailDamagePercent = 100.0 - GetSailPercent(chr);
	float HullDamagePercent = 100.0 - GetHullPercent(chr);
	
	if(HullDamagePercent > 0.0)
	{
		timeHull = HullDamagePercent * (8-GetCharacterShipClass(chr));
	}
	if(SailDamagePercent > 0.0)
	{
		timeSail  = SailDamagePercent * (8-GetCharacterShipClass(chr));
	}	
	
	// кол-во материала на один процент ремонта
	float sail_SPP = GetSailSPP(chr);
	float hull_PPP = GetHullPPP(chr);
	trace("hull_PPP " + hull_PPP + " sail_SPP " + sail_SPP);
	
	float matQ;	
	int shMastFall = GetShipFallMastsQuantity(chr);
	
	trace("timeHull " + timeHull + " timeSail " + timeSail + " time (hours) : " + makeint( (timeHull/4.0 + timeSail/6.0)) );
	
	
	if(shMastFall > 0)
	{
		matQ = 15.0*GetHullPPP(chr);		
	}

}

float GetMaxSpeedZ(float fWindAgainstSpeed, float fWindDotShip)
{
    float fMaxSpeedZ 	= 10.0;
	float BtWindR 		= 1.0 - fWindAgainstSpeed;
	float fkoeff 		= fWindAgainstSpeed; 
	if(fkoeff < 1.0) fkoeff = 1.0;
	
	if(fWindDotShip < BtWindR) // по ветру
	{
		fMaxSpeedZ = fMaxSpeedZ * (1.0 + 0.974 * (fWindDotShip - BtWindR) / (1.0 + BtWindR));
	}
	else // против ветра
	{
		fMaxSpeedZ = fkoeff*fMaxSpeedZ * (1.0  - (fWindDotShip - BtWindR)/ 2.0);
	}	
	return fMaxSpeedZ;
}


void ReloadByStr()
{
	// разбор строки
	string  loc = stripblank(GetSubStringByNum(GameInterface.reload_edit.str, 0));
	string  grp = stripblank(GetSubStringByNum(GameInterface.reload_edit.str, 1));
	string  ltr = stripblank(GetSubStringByNum(GameInterface.reload_edit.str, 2));

    int i = FindLocation(loc);
    if (i != -1)
    {
        if(CheckAttribute(&locations[i],"fastreload"))
        {
			if (GetCityFrom_Sea(locations[i].fastreload) != "")
		    {
		        setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		        setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
		    }
	    }
	    else
	    {
	        if (locations[i].type == "seashore" || locations[i].type == "mayak")
	        {
	            setCharacterShipLocation(pchar, loc));
		        setWDMPointXZ(loc);
	        }
	    }
	    DoQuestReloadToLocation(loc, grp, ltr, "");
	    Log_Info(loc);
	    
		// Статистика по читам
		Statistic_AddValue(PChar, "Cheats.ReloadByStr", 1);
    }
    else
    {
        Log_Info("Нет локации");
    }
}

void XI_SetScroller(float pos)
{
	SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"QUESTSCROLL",pos);
}

void SetScrollerPos()
{
	string nodName = GetEventData();
	float pos = GetEventData();
	XI_SetScroller(pos);
}

void ProcScrollPosChange()
{
	float newPos = GetEventData();
    SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",2, newPos);
}

void ProcScrollChange()
{
	int changeNum = GetEventData();
	if(changeNum==0) return;
	string controlNode = "";
	if( GetSelectable("INFO_TEXT") ) controlNode = "INFO_TEXT";
	
	if(controlNode!="")
	{
		if(changeNum>0) {
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,controlNode,-1, 0,ACTION_DOWNSTEP);
		} else {
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,controlNode,-1, 0,ACTION_UPSTEP);
		}
	}
}


void GetRealCoordsObjects()
{
	trace("---------");
	trace("Barbados (island)					: " + Map_GetRealCoordX(946.0062) + " " + Map_GetRealCoordZ(-486.9014));
	trace("Бриджтаун 							: " + Map_GetRealCoordX(903.6217) + " " + Map_GetRealCoordZ(-522.2799));
	trace("Mayak2 (маяк Барбадоса)				: " + Map_GetRealCoordX(918.619) + " " + Map_GetRealCoordZ(-506.827));
	trace("Shore4 (мыс Гаррисон)				: " + Map_GetRealCoordX(919.808) + " " + Map_GetRealCoordZ(-448.061));
	trace("Shore5 (мыс Раггед Пойнт)			: " + Map_GetRealCoordX(983.787) + " " + Map_GetRealCoordZ(-518.14));	
	trace("---------");
	trace("Antigua (island)						: " + Map_GetRealCoordX(903.9222) + " " + Map_GetRealCoordZ(109.0605));
	trace("Сент-Джонс 							: " + Map_GetRealCoordX(852.4083) + " " + Map_GetRealCoordZ(128.9092));
	trace("Shore1 (мыс Бун)						: " + Map_GetRealCoordX(880.892) + " " + Map_GetRealCoordZ(148.897));
	trace("Shore2 (залив Уиллогби)				: " + Map_GetRealCoordX(931.028) + " " + Map_GetRealCoordZ(74.5353));
	trace("---------");
	trace("Curacao (island) 					: " + Map_GetRealCoordX(383.4142) + " " + Map_GetRealCoordZ(-691.11));
	trace("Виллемштадт 							: " + Map_GetRealCoordX(396.1) + " " + Map_GetRealCoordZ(-722.8));	
	trace("Shore22 (Пальмовый берег)			: " + Map_GetRealCoordX(354.604) + " " + Map_GetRealCoordZ(-678.54));
	trace("Shore23 (Мыс Кальвинистов)			: " + Map_GetRealCoordX(347.313) + " " + Map_GetRealCoordZ(-705.112));
	trace("Shore24 (берег Приют Контрабандиста)	: " + Map_GetRealCoordX(455.427) + " " + Map_GetRealCoordZ(-740.655));
	trace("---------");
	trace("SentMartin (island)					: " + Map_GetRealCoordX(921.559) + " " + Map_GetRealCoordZ(523.596));
	trace("Мариго 								: " + Map_GetRealCoordX(900.0994) + " " + Map_GetRealCoordZ(501.6531));	
	trace("Shore40 (берег Спасения)				: " + Map_GetRealCoordX(924.442) + " " + Map_GetRealCoordZ(554.385));	
	trace("Shore41 (бухта Неистового ветра)		: " + Map_GetRealCoordX(898.877) + " " + Map_GetRealCoordZ(522.703));	
	trace("---------");
	trace("Guadeloupe (island)					: " + Map_GetRealCoordX(537.114) + " " + Map_GetRealCoordZ(-25.3853));	
	trace("Бас-Тер 								: " + Map_GetRealCoordX(462.2107) + " " + Map_GetRealCoordZ(-73.0837));		
	trace("Mayak4 (маяк Гваделупы)				: " + Map_GetRealCoordX(465.076) + " " + Map_GetRealCoordZ(-38.9423));		
	trace("Shore28 (бухта Морн л'О)				: " + Map_GetRealCoordX(536.636) + " " + Map_GetRealCoordZ(26.1279));		
	trace("Shore29 (пляж Капстер)				: " + Map_GetRealCoordX(507.669) + " " + Map_GetRealCoordZ(-75.4176));		
	trace("Shore30 (бухта Гран Бур)				: " + Map_GetRealCoordX(549.807) + " " + Map_GetRealCoordZ(-69.7107));		
	trace("Shore31 (мыс Недоступный)			: " + Map_GetRealCoordX(589.889) + " " + Map_GetRealCoordZ(-65.0601));		
	trace("---------");
	trace("Martinique (island) 					: " + Map_GetRealCoordX(538.524) + " " + Map_GetRealCoordZ(-385.567));		
	trace("Сен-Пьер 						    : " + Map_GetRealCoordX(513.51) + " " + Map_GetRealCoordZ(-397.645));		
	trace("Ле-Франсуа 							: " + Map_GetRealCoordX(559.008) + " " + Map_GetRealCoordZ(-368.16));		
	trace("Shore38 (пляж Ламантен)				: " + Map_GetRealCoordX(481.181) + " " + Map_GetRealCoordZ(-340.832));		
	trace("Shore39 (бухта Ле Марен)				: " + Map_GetRealCoordX(557.181) + " " + Map_GetRealCoordZ(-422.987));		
	trace("---------");
	trace("Bermudes (island)					: " + Map_GetRealCoordX(920.738) + " " + Map_GetRealCoordZ(920.767));		
	trace("Шарптаун     					    : " + Map_GetRealCoordX(931.059) + " " + Map_GetRealCoordZ(928.281));		
	trace("Shore3 (залив Руны)					: " + Map_GetRealCoordX(915.745) + " " + Map_GetRealCoordZ(966.469));		
	trace("Shore_ship1 (бухта Разбитого Корыта) : " + Map_GetRealCoordX(968.947) + " " + Map_GetRealCoordZ(923.636));		
	trace("---------");
	trace("Maracaibo (areal) 					: " + Map_GetRealCoordX(178.51) + " " + Map_GetRealCoordZ(-870.37));		
	trace("Маракайбо 							: " + Map_GetRealCoordX(134.82) + " " + Map_GetRealCoordZ(-939.65));		
	trace("Shore37 (бухта Гуахира)				: " + Map_GetRealCoordX(140.753) + " " + Map_GetRealCoordZ(-828.99));		
	trace("Shore_ship3 (мыс Несбывшихся Надежд)	: " + Map_GetRealCoordX(198.162) + " " + Map_GetRealCoordZ(-994.035));		
	trace("---------");
	trace("Beliz (areal) 						: " + Map_GetRealCoordX(-896.084) + " " + Map_GetRealCoordZ(230.227));		
	trace("Shore_ship2 (залив Гибели)			: " + Map_GetRealCoordX(-1022.94) + " " + Map_GetRealCoordZ(629.355));		
	trace("Shore6 (мыс Каточе)					: " + Map_GetRealCoordX(-909.655) + " " + Map_GetRealCoordZ(629.079));		
	trace("Shore7 (залив Косумель)				: " + Map_GetRealCoordX(-915.581) + " " + Map_GetRealCoordZ(409.002));		
	trace("Shore8 (бухта Четумаль)				: " + Map_GetRealCoordX(-963.489) + " " + Map_GetRealCoordZ(281.628));		
	trace("Белиз 								: " + Map_GetRealCoordX(-978.396) + " " + Map_GetRealCoordZ(158.751));		
	trace("Shore9 (бухта Аматике)				: " + Map_GetRealCoordX(-1017.2) + " " + Map_GetRealCoordZ(-33.7293));		
	trace("Shore10 (лагуна Каратаска)			: " + Map_GetRealCoordX(-818.198) + " " + Map_GetRealCoordZ(-177.208));		
	trace("---------");
	trace("Jamaica (island)						: " + Map_GetRealCoordX(-298.0) + " " + Map_GetRealCoordZ(-128.0));		
	trace("Порт-Ройал 							: " + Map_GetRealCoordX(-250.157) + " " + Map_GetRealCoordZ(-150.839));		
	trace("Shore35 (мыс Негрил)					: " + Map_GetRealCoordX(-446.951) + " " + Map_GetRealCoordZ(-107.118));			
	trace("Shore36 (бухта Портленд)				: " + Map_GetRealCoordX(-281.543) + " " + Map_GetRealCoordZ(-164.245));			
	trace("Mayak3 (маяк Порт Рояля)				: " + Map_GetRealCoordX(-224.127) + " " + Map_GetRealCoordZ(-163.435));			
	trace("---------");
	trace("PuertoRico (island) 					: " + Map_GetRealCoordX(506.489) + " " + Map_GetRealCoordZ(460.815));			
	trace("Сан-Хуан 							: " + Map_GetRealCoordX(528.645) + " " + Map_GetRealCoordZ(484.18));				
	trace("Shore44 (бухта Агуадилья)			: " + Map_GetRealCoordX(392.82) + " " + Map_GetRealCoordZ(501.808));				
	trace("Shore45 (пляж Фахардо)				: " + Map_GetRealCoordX(602.049) + " " + Map_GetRealCoordZ(458.322));				
	trace("---------");
	trace("Cuba1 (areal) 						: " + Map_GetRealCoordX(-358.027) + " " + Map_GetRealCoordZ(819.223));				
	trace("Сантьяго 							: " + Map_GetRealCoordX(-339.796) + " " + Map_GetRealCoordZ(771.839));					
	trace("Пуэрто-Принсипе 						: " + Map_GetRealCoordX(-282.032) + " " + Map_GetRealCoordZ(839.056));					
	trace("Shore11 (мыс Камагуэй)				: " + Map_GetRealCoordX(-386.907) + " " + Map_GetRealCoordZ(883.044));				
	trace("Shore12 (залив Анна Мария)			: " + Map_GetRealCoordX(-468.486) + " " + Map_GetRealCoordZ(838.497));				
	trace("Mayak9 (маяк Сантьяго)				: " + Map_GetRealCoordX(-333.295) + " " + Map_GetRealCoordZ(723.486));				
	trace("---------");
	trace("Cuba2 (areal) 						: " + Map_GetRealCoordX(-640.61) + " " + Map_GetRealCoordZ(870.058));					
	trace("Гавана 								: " + Map_GetRealCoordX(-663.685) + " " + Map_GetRealCoordZ(913.862));					
	trace("Shore13 (залив Батабано)				: " + Map_GetRealCoordX(-613.56) + " " + Map_GetRealCoordZ(886.009));				
	trace("Shore14 (бухта Хувентуд)				: " + Map_GetRealCoordX(-653.269) + " " + Map_GetRealCoordZ(871.013));				
	trace("Shore15 (мыс Сан Антонио)			: " + Map_GetRealCoordX(-715.129) + " " + Map_GetRealCoordZ(797.212));				
	trace("Mayak10 (маяк Гаваны)				: " + Map_GetRealCoordX(-647.18) + " " + Map_GetRealCoordZ(925.046));				
	trace("---------");
	trace("Tortuga (island) 					: " + Map_GetRealCoordX(102.328) + " " + Map_GetRealCoordZ(852.912));				
	trace("Тортуга 								: " + Map_GetRealCoordX(116.875) + " " + Map_GetRealCoordZ(817.942));				
	trace("Shore58 (пляж Глаз Рыбы)				: " + Map_GetRealCoordX(131.064) + " " + Map_GetRealCoordZ(849.44));				
	trace("Mayak6 (маяк Тортуги)				: " + Map_GetRealCoordX(103.23) + " " + Map_GetRealCoordZ(812.356));				
	trace("---------");
	trace("Trinidad (island)					: " + Map_GetRealCoordX(889.76) + " " + Map_GetRealCoordZ(-774.746));				
	trace("Порт-оф-Спейн 						: " + Map_GetRealCoordX(848.282) + " " + Map_GetRealCoordZ(-822.588));				
	trace("Shore59 (бухта Скарборо)				: " + Map_GetRealCoordX(937.322) + " " + Map_GetRealCoordZ(-737.478));				
	trace("Shore60 (мыс Галера)					: " + Map_GetRealCoordX(906.25) + " " + Map_GetRealCoordZ(-757.928));				
	trace("Mayak1 (маяк Тринидада и Тобаго)		: " + Map_GetRealCoordX(821.24) + " " + Map_GetRealCoordZ(-847.69));				
	trace("---------");
	trace("Nevis (island)						: " + Map_GetRealCoordX(681.595) + " " + Map_GetRealCoordZ(256.013));				
	trace("Чарльзтаун 							: " + Map_GetRealCoordX(658.918) + " " + Map_GetRealCoordZ(241.972));				
	trace("Shore42 (бухта Ньюкасл)				: " + Map_GetRealCoordX(690.047) + " " + Map_GetRealCoordZ(291.621));					
	trace("Shore43 (пляж Бат)					: " + Map_GetRealCoordX(684.026) + " " + Map_GetRealCoordZ(212.793));					
	trace("Mayak5 (маяк Невиса)					: " + Map_GetRealCoordX(663.418) + " " + Map_GetRealCoordZ(228.281));					
	trace("---------");
	trace("Hispaniola1 (areal) 					: " + Map_GetRealCoordX(198.977) + " " + Map_GetRealCoordZ(588.696));					
	trace("Санто-Доминго 						: " + Map_GetRealCoordX(198.683) + " " + Map_GetRealCoordZ(547.97));					
	trace("Ла-Вега 								: " + Map_GetRealCoordX(166.708) + " " + Map_GetRealCoordZ(662.952));					
	trace("Shore32 (мыс Исабела)				: " + Map_GetRealCoordX(130.591) + " " + Map_GetRealCoordZ(682.362));						
	trace("Shore33 (бухта Самана)				: " + Map_GetRealCoordX(229.081) + " " + Map_GetRealCoordZ(593.727));						
	trace("Mayak8 (маяк Санто-Доминго)			: " + Map_GetRealCoordX(168.314) + " " + Map_GetRealCoordZ(520.218));						
	trace("---------");
	trace("Hispaniola2 (areal) 					: " + Map_GetRealCoordX(-47.1762) + " " + Map_GetRealCoordZ(625.596));					
	trace("Порт-о-Пренс 						: " + Map_GetRealCoordX(22.521) + " " + Map_GetRealCoordZ(592.233));					
	trace("Shore34 (бухта Гонаив)				: " + Map_GetRealCoordX(0.999614) + " " + Map_GetRealCoordZ(643.122));							
	trace("Mayak7 (маяк Порт-о-Пренса)			: " + Map_GetRealCoordX(-14.9756) + " " + Map_GetRealCoordZ(606.258));						
	trace("---------");
	trace("Dominica 							: " + Map_GetRealCoordX(783.057) + " " + Map_GetRealCoordZ(-256.833));					
	trace("Shore27 (мыс Скотс Хед)				: " + Map_GetRealCoordX(779.89) + " " + Map_GetRealCoordZ(-295.002));								
	trace("Shore26 (пляж Касл Брус)				: " + Map_GetRealCoordX(803.577) + " " + Map_GetRealCoordZ(-252.617));								
	trace("---------");
	trace("Теркс 								: " + Map_GetRealCoordX(443.257) + " " + Map_GetRealCoordZ(939.102));						
	trace("Shore57 (залив Южный)				: " + Map_GetRealCoordX(434.944) + " " + Map_GetRealCoordZ(923.524));								
	trace("Shore56 (залив Северный)				: " + Map_GetRealCoordX(444.298) + " " + Map_GetRealCoordZ(954.975));								
	trace("---------");
	trace("Кайман 								: " + Map_GetRealCoordX(-489.6) + " " + Map_GetRealCoordZ(362.455));						
	trace("Shore17 (залив Эсмеральды)			: " + Map_GetRealCoordX(-505.038) + " " + Map_GetRealCoordZ(348.115));									
	trace("Shore16 (Пустынный пляж)				: " + Map_GetRealCoordX(-449.837) + " " + Map_GetRealCoordZ(366.308));
	trace("---------");
	trace("Panama (areal) 						: " + Map_GetRealCoordX(-395.198) + " " + Map_GetRealCoordZ(-972.801));							
	trace("Панама 								: " + Map_GetRealCoordX(-389.965) + " " + Map_GetRealCoordZ(-949.118));							
	trace("Shore63 (залив Сан Мигель) 			: " + Map_GetRealCoordX(-328.166) + " " + Map_GetRealCoordZ(-1023.72));
	trace("---------");
	trace("PortoBello (areal) 					: " + Map_GetRealCoordX(-435.73) + " " + Map_GetRealCoordZ(-895.763));							
	trace("Порто-Белло 							: " + Map_GetRealCoordX(-427.183) + " " + Map_GetRealCoordZ(-907.277));
	trace("Shore46 (лагуна Чирики)				: " + Map_GetRealCoordX(-627.474) + " " + Map_GetRealCoordZ(-940.853));
	trace("Shore47 (залив Москитос)				: " + Map_GetRealCoordX(-486.49) + " " + Map_GetRealCoordZ(-976.966));
	trace("Shore48 (Дарьенский залив)			: " + Map_GetRealCoordX(-279.316) + " " + Map_GetRealCoordZ(-1005.49));
	trace("---------");
	trace("Cartahena (areal) 					: " + Map_GetRealCoordX(-51.2104) + " " + Map_GetRealCoordZ(-851.77));								
	trace("Картахена 							: " + Map_GetRealCoordX(-26.7669) + " " + Map_GetRealCoordZ(-872.535));								
	trace("Shore25 (бухта Ковеньяс)				: " + Map_GetRealCoordX(-115.589) + " " + Map_GetRealCoordZ(-937.387));
	trace("Mayak11 (маяк Картахены)				: " + Map_GetRealCoordX(-65.6347) + " " + Map_GetRealCoordZ(-842.072));
	trace("---------");
	trace("Caracas (areal) 						: " + Map_GetRealCoordX(435.126) + " " + Map_GetRealCoordZ(-936.197));								
	trace("Каракас 								: " + Map_GetRealCoordX(440.684) + " " + Map_GetRealCoordZ(-960.339));
	trace("Shore21 (мыс Аруба)					: " + Map_GetRealCoordX(410.688) + " " + Map_GetRealCoordZ(-913.531));
	trace("---------");
	trace("Cumana (areal) 						: " + Map_GetRealCoordX(767.999) + " " + Map_GetRealCoordZ(-936.266));								
	trace("Кумана 								: " + Map_GetRealCoordX(691.343) + " " + Map_GetRealCoordZ(-896.619));								
	trace("Shore20 (пляж Лос Текес)				: " + Map_GetRealCoordX(574.327) + " " + Map_GetRealCoordZ(-929.042));
	trace("Shore19 (бухта Карупано)				: " + Map_GetRealCoordX(768.622) + " " + Map_GetRealCoordZ(-914.469));
	trace("Shore18 (берег Бока де ла Сьерпе)	: " + Map_GetRealCoordX(924.423) + " " + Map_GetRealCoordZ(-969.921));
	trace("---------");
	trace("SantaCatalina (areal) 				: " + Map_GetRealCoordX(-742.269) + " " + Map_GetRealCoordZ(-563.205));									
	trace("Санта-Каталина 						: " + Map_GetRealCoordX(-769.375) + " " + Map_GetRealCoordZ(-537.051));
	trace("Shore53 (Берег Москитов)				: " + Map_GetRealCoordX(-792.718) + " " + Map_GetRealCoordZ(-331.728));
	trace("Shore54 (мыс Перлас)					: " + Map_GetRealCoordX(-760.343) + " " + Map_GetRealCoordZ(-484.106));
	trace("Shore55 (залив Сан Хуан дель Норте)	: " + Map_GetRealCoordX(-736.763) + " " + Map_GetRealCoordZ(-756.295));
	trace("---------");
	trace("ГПК									: " + Map_GetRealCoordX(-938.667) + " " + Map_GetRealCoordZ(938.654));										
	trace("---------");
	trace("Teno (areal)							: " + Map_GetRealCoordX(-966.062) + " " + Map_GetRealCoordZ(-294.232));										
	trace("Теночтитлан 							: " + Map_GetRealCoordX(-969.194) + " " + Map_GetRealCoordZ(-305.237));										
	trace("Shore61 (Тепейакак) 					: " + Map_GetRealCoordX(-955.553) + " " + Map_GetRealCoordZ(-281.197));
	trace("Shore62 (Истапалапу)					: " + Map_GetRealCoordX(-935.811) + " " + Map_GetRealCoordZ(-316.162));
	trace("---------");
	trace("Ксочитэм								: " + Map_GetRealCoordX(-597.3333) + " " + Map_GetRealCoordZ(85.3333));										
	trace("---------");	
	trace("RockIsland							: " + Map_GetRealCoordX(-511.9965) + " " + Map_GetRealCoordZ(554.6586));										
	trace("---------");	
	trace("KhaelRoa								: " + Map_GetRealCoordX(810.6678) + " " + Map_GetRealCoordZ(298.6671));										
	trace("---------");	
	trace("Providence							: " + Map_GetRealCoordX(-512.0) + " " + Map_GetRealCoordZ(-426.6667));										
	trace("---------");	
	trace("SantaQuiteria						: " + Map_GetRealCoordX(-213.3336) + " " + Map_GetRealCoordZ(-512.0));										
	trace("---------");	
	trace("IslaDeVieques						: " + Map_GetRealCoordX(85.3334) + " " + Map_GetRealCoordZ(-70.6667));										
	trace("---------");	
	trace("IslaMona								: " + Map_GetRealCoordX(0) + " " + Map_GetRealCoordZ(170.6669));										
	trace("---------");	
	trace("IslaDeCoche							: " + Map_GetRealCoordX(640.0) + " " + Map_GetRealCoordZ(-640.0));										
	trace("---------");		
}