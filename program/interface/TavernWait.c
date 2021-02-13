int iHourWait = 0;

void InitInterface(string iniName)
{
    SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);
    locCameraSleep(true);
    SetTimeScale(0.0);
    EngineLayersOffOn(true);
    CreateString(true, "Frame_Caption", "Отдых", FONT_CAPTION, COLOR_NORMAL, 400, 205, SCRIPT_ALIGN_CENTER, 1.2);
    CreateString(true, "MainString", "Сколько часов вы желаете отдыхать ?", FONT_CAPTION, COLOR_NORMAL, 400, 235, SCRIPT_ALIGN_CENTER, 1.2);
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

    switch (nodName)
    {
    case "HOURS_SLIDE":
        if (comName == "downstep")
        {
            if (GetSelectable("OK_BTN"))
                SetCurrentNode("OK_BTN");
            else
                SetCurrentNode("CANCEL_BTN");
        }
        break;

    case "OK_BTN":
        if (comName == "activate" || comName == "click")
            WaitProcess(iHourWait);

        if (comName == "rightstep")
            SetCurrentNode("CANCEL_BTN");

        if (comName == "upstep")
            SetCurrentNode("HOURS_SLIDE");
        break;

    case "CANCEL_BTN":
        if (comName == "leftstep")
        {
            if (GetSelectable("OK_BTN"))
                SetCurrentNode("OK_BTN");
        }

        if (comName == "upstep")
            SetCurrentNode("HOURS_SLIDE");
        break;
    }
}

void ProcSlideChange()
{
    string sNodeName = GetEventData();
    int iVal = GetEventData();   // int GameInterface.nodes.<node_name>.value
    float fVal = GetEventData(); // float GameInterface.nodes.<node_name>.value

    if (sNodeName == "HOURS_SLIDE")
    {
        iHourWait = sti(fVal * 24);
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
    if (iHourWait <= 0 || chrDisableReloadToLocation)
        SetSelectable("OK_BTN", false);
    else
        SetSelectable("OK_BTN", true);
}

string GetCorrectHourString(int _hour)
{
    string sRetStr = "";

    switch (_hour)
    {
    case "0":
        sRetStr = "Менее одного часа";
        break;
    case "1":
        sRetStr = "1 час или около того . . .";
        break;
    case "2":
        sRetStr = "2 часа или около того . . .";
        break;
    case "3":
        sRetStr = "3 часа или около того . . .";
        break;
    case "4":
        sRetStr = "4 часа или около того . . .";
        break;
    case "5":
        sRetStr = "5 часов или около того . . .";
        break;
    case "6":
        sRetStr = "6 часов или около того . . .";
        break;
    case "7":
        sRetStr = "7 часов или около того . . .";
        break;
    case "8":
        sRetStr = "8 часов или около того . . .";
        break;
    case "9":
        sRetStr = "9 часов или около того . . .";
        break;
    case "10":
        sRetStr = "10 часов или около того . . .";
        break;
    case "11":
        sRetStr = "11 часов или около того . . .";
        break;
    case "12":
        sRetStr = "12 часов или около того . . .";
        break;
    case "13":
        sRetStr = "13 часов или около того . . .";
        break;
    case "14":
        sRetStr = "14 часов или около того . . .";
        break;
    case "15":
        sRetStr = "15 часов или около того . . .";
        break;
    case "16":
        sRetStr = "16 часов или около того . . .";
        break;
    case "17":
        sRetStr = "17 часов или около того . . .";
        break;
    case "18":
        sRetStr = "18 часов или около того . . .";
        break;
    case "19":
        sRetStr = "19 часов или около того . . .";
        break;
    case "20":
        sRetStr = "20 часов или около того . . .";
        break;
    case "21":
        sRetStr = "21 час или около того . . .";
        break;
    case "22":
        sRetStr = "22 часа или около того . . .";
        break;
    case "23":
        sRetStr = "23 часа или около того . . .";
        break;
    case "24":
        sRetStr = "Сутки или около того . . .";
        break;
    }

    return sRetStr;
}