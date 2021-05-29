// BOAL 07.09.03  Mods on_off mode -->
#include "_LSC_on_off.h"
// BOAL 07.09.03  Mods on_off mode <--
#include "events.h"
#include "globals.c"
#include "animals.c"
#include "NumberUtilities.c" // Warship 26.07.09. Работа с числами
#include "sea_ai\sea.c"
#include "ships\ships.c"
#include "Encounters\Encounters.c"
#include "worldmap\worldmap.c"
#include "locations\locations.c"
#include "Loc_ai\LAi_init.c"
#include "store\goods.h"
#include "cannons\cannons.c"
#include "nations\nations.c"
#include "particles.c"
#include "characters\characters.c"
#include "interface\interface.h"
#include "store\storeutilite.c"
#include "dialog.c"
#include "quests\quests.c"
#include "islands\islands.c"
#include "colonies\colonies.c"
#include "reload.c"
#include "battle_interface\loginterface.c"
#include "calendar.c"
#include "teleport.c"
#include "utils.c"
#include "weather\WhrWeather.c"
#include "controls\controls.c"
#include "ITEMS\items.h"
#include "ITEMS\itemLogic.c"
#include "ITEMS\items_utilite.c"
#include "net\net.c"
#include "store\store.h"
#include "interface\interface.c"

extern void InitBaseCannons();
extern void InitCharacters();
extern void InitBaseInterfaces();

extern void wdmInitWorldMap();
extern void InitGoods();
extern void InitStores();
extern int InitItems();
extern void InitCharactersTables();
extern void InitCharactersNames();
extern void InitPiratesNames();
extern void InitGeneratorNames();
extern void InitIndianNames(); //Jason имена индейцев
extern void CreateCharacters();

extern void ActiveF4Control(); // boal debuger
extern void ActiveF5Control(); // boal debuger
extern void ActiveF7Control(); // boal debuger
extern void ActiveF10Control(); // boal debuger
extern void ActiveF12Control(); // boal debuger
extern void ActiveINSERTControl(); // boal debuger

native float Bring2RangeNoCheck(float fMin1, float fMax1, float fMin2, float fMax2, float fValue);
native float Bring2Range(float fMin1, float fMax1, float fMin2, float fMax2, float fValue);
native float Clampf(float fValue);
native float Degree2Radian(float fDegree);
native int RDTSC_B();
native int RDTSC_E(int iRDTSC);

native int SetTexturePath(int iLevel, string sPath);
native int SetGlowParams(float fBlurBrushSize, int Intensivity, int BlurPasses);
native int RPrint(int x, int y, string sPrint);


#libriary "script_libriary_test"
#libriary "dx8render_script_libriary"


#event_handler(NEW_GAME_EVENT,"NewGame");
#event_handler(GAME_OVER_EVENT,"GameOverE");
#event_handler("Control Activation","ProcessControls");
#event_handler("MainMenuKey","ProcessMainMenuKey");
#event_handler("InterfaceKey","ProcessInterfaceKey");
#event_handler("CameraPosAng","ProcessCameraPosAng");
#event_handler("Cheat","ProcessCheat");
#event_handler("SeaDogs_ClearSaveData", "ClearLocationsSaveData");
#event_handler("StopQuestCheckProcessFreeze","ProcessStopQuestCheckProcessFreeze"); // boal 240804

float fHighPrecisionDeltaTime;	

void ProcessStopQuestCheckProcessFreeze() // boal 240804
{
    bQuestCheckProcessFreeze = false;
    wdmLockReload            = false;
    QuestsCheck(); // выполнить отложенные

    if (rand(20) == 10) // 16.01.06 не помню уже зачем разлочивал ГГ, но на деле мешает до квестам, но если где повиснет, то спасет ф2
    {
    	DoQuestCheckDelay("pchar_back_to_player", 0.5); // если в диалоге залочило, вернем управление
    }
}

void ProcessVersionCheck() // boal 271004
{
    ref mc = GetMainCharacter();

    if (CheckAttribute(mc, "HeroParam")) // признак, что есть герой
    {
		/*Level_Complexity         = MOD_SKILL_ENEMY_RATE; // до новой игры из настроек, потом из сэйва
        bHardcoreGameStart       = bHardcoreGame;
        bPayForSaveLoadStart     = bPayForSaveLoad;
        bWorldAlivePauseStart    = bWorldAlivePause;  */
        
        if (!CheckAttribute(mc, "VersionNumber"))
    	{
            Log_Info("Загружена старая сохраненная запись.");
            Log_Info("Возможна нестабильная работа программы.");
			Log_Info("Желательно начать новую игру.");
    	}
        else
        {
            if (sti(mc.VersionNumberCompatibility) < VERSION_NUM_PRE && mc.VersionNumber != GetVerNum())
            {
                Log_Info("Загружена сохраненная запись версии " + mc.VersionNumber +".");
                Log_Info("Возможна нестабильная работа программы.");
				Log_Info("Желательно начать новую игру.");
            }
        }
    }
}

void ProcessCheat()
{
	string sCheatName;
	ref mc;
	sCheatName = GetEventData();
	mc = GetMainCharacter();

	switch(sCheatName)
	{
		case "Immortal":
			if(LAi_IsImmortal(GetMainCharacter()))
			{				
				LAi_SetImmortal(GetMainCharacter(), false);
				Log_SetStringToLog("God mode OFF");
			}else{
				
				LAi_SetImmortal(GetMainCharacter(), true);
				Log_SetStringToLog("God mode ON");
			}
		break;
		case "ShotGun":
			if(globalSGMode != false)
			{
				globalSGMode = false;
				Log_SetStringToLog("Shotgun mode OFF");
			}else{
				globalSGMode = true;
				Log_SetStringToLog("Shotgun mode ON");
			}
		break;

		case "Gold":
			mc.money = sti(mc.money) + 100000;
			Log_SetStringToLog(" + 100000 G");
		break;
		case "Skill":
			mc.skill.freeskill = 1;
	
			mc.skill.freeskill = sti(mc.skill.freeskill) + 50;
			Log_SetStringToLog(" + 50 SP");
		break;
		case "Reputation":
			mc.reputation = REPUTATION_NEUTRAL;
			Log_SetStringToLog("Reputation Set to NEUTRAL");
		break;
		case "Morale":

		break;
		case "Encounters":
			if(CheckAttribute(mc,"worldmapencountersoff") == 0)
			{
				mc.worldmapencountersoff = "1";
				Log_SetStringToLog("Worldmap encounters OFF");
			}
			else
			{
				if(mc.worldmapencountersoff == "1") 
				{
					mc.worldmapencountersoff = "0";
					Log_SetStringToLog("Worldmap encounters ON");
				}
				else 
				{
					mc.worldmapencountersoff = "1";
					Log_SetStringToLog("Worldmap encounters OFF");
				}
			}
		break;
		case "MainCharacter":
			mc.model	= "Danielle";
			mc.sex = "woman";
			mc.FaceId = 30;
			mc.model.animation = "woman";
			mc.model.height = 1.75;
		break;
		case "soundoff":
			SendMessage(&Sound,"ll",MSG_SOUND_SET_ENABLED,0);
			Log_SetStringToLog("Sound OFF");
		break;
	}
}

object Camera;

void ProcessCameraPosAng()
{
	Camera.Pos.x = GetEventData();
	Camera.Pos.y = GetEventData();
	Camera.Pos.z = GetEventData();

	Camera.Ang.x = GetEventData();
	Camera.Ang.y = GetEventData();
	Camera.Ang.z = GetEventData();
}

void proc_break_video()
{
	trace("proc_break_video()");
	if (sti(InterfaceStates.videoIdx) != 1)
	{
		//InterfaceStates.videoIdx = -1;
		//Event("ievntEndVideo");
	}
}

void Main()
{
    LayerCreate("realize", 1);
	LayerCreate("sea_realize", 1);
	LayerCreate("net_realize", 1);
	LayerCreate("iRealize", 1);
	LayerCreate("fader_realize", 1);
	LayerCreate("inf_realize", 1);

	ControlsInit(GetTargetPlatform(),true);
	nTeleportLocation = 1;

	NationsInit();
	EncountersInit();
	CannonsInit();
	ShipsInit();
	IslandsInit();
	WeatherInit();
	InitPerks();

	if(LoadSegment("store\initGoods.c"))
	{
		InitGoods();
		UnloadSegment("store\initGoods.c");
	}

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces_main();
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}
	
	SetEventHandler("Control Activation","proc_break_video",0);
	InterfaceStates.Launched = false;
	SetEventHandler(EVENT_END_VIDEO,"Main_LogoVideo",0);
	InterfaceStates.videoIdx = 0;
	Event(EVENT_END_VIDEO);

	SetGlowParams(1.0, 50, 2);
}

void Main_InitGame()
{
    LayerCreate("realize", 1);
	LayerCreate("sea_realize", 1);
	LayerCreate("net_realize", 1);
	LayerCreate("iRealize", 1);
	LayerCreate("fader_realize", 1);
	LayerCreate("inf_realize", 1);

	nTeleportLocation      = 1;
    bDisableLandEncounters = false;
	bDisableCharacterMenu  = false;
	bWorldAlivePause       = true;
	bPauseContrabandMetro  = false;
	bMonstersGen           = false;
	bLandEncountersGen     = true;
	chrDisableReloadToLocation = false;
	bDisableFastReload         = false;
	bDisableMapEnter           = false;
	bDisableSailTo             = false;
	bEnableIslandSailTo        = false;
	bReloadCanBe               = false;
	bMapEnter                  = false;
	bQuestDisableMapEnter      = false;
    bAbordageStarted           = false;
    bCabinStarted              = false;
	bDeckBoatStarted           = false;
	LAi_IsCapturedLocation     = false;
	LAi_IsBoarding             = false;
	LAi_restoreStates          = false;
	LAi_boarding_process       = false;
	boarding_location          = -1;
	
	NationsInit();
	EncountersInit();
	CannonsInit();
	ShipsInit();
	IslandsInit();
	WeatherInit();
	InitPerks();
	// Init network, clear massives and load favorite list
	Net_Init();
	Net_ClientFirstInit();
	Net_ServerFirstInit();
	if(LoadSegment("store\initGoods.c"))
	{
		InitGoods();
		UnloadSegment("store\initGoods.c");
	}

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces_main();
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}
}
void Main_LogoVideo()
{
	
	int i = sti(InterfaceStates.videoIdx);
	switch(i)
	{
	case 0:
		InterfaceStates.videoIdx = 1;
		StartPostVideo("AkellaLogo",1);
	break;

	case 1:
		InterfaceStates.videoIdx = 2;
		StartPostVideo("Blackmark",1);
	break;

	case 2:
		InterfaceStates.videoIdx = 4;
		StartPostVideo("Title",1);
	break;

	default:
		DelEventHandler(EVENT_END_VIDEO,"Main_LogoVideo");
		DeleteClass(&aviVideoObj);
		Event("DoInfoShower","sl","game prepare",true);
		SetEventHandler("frame","Main_Start",1);
	break;
	}

}

void Main_Start()
{
	ReloadProgressStart();
	
	DelEventHandler("Control Activation","proc_break_video");
	DelEventHandler("frame","Main_Start");

	if( GetTargetPlatform()=="pc" )	ControlsInit(GetTargetPlatform(),false);
    
	ReloadProgressUpdate();
	InitGame();
	ReloadProgressUpdate();

	Environment.date.hour = worldMap.date.hour;
	Environment.date.min = worldMap.date.min;
	Environment.date.sec = worldMap.date.sec;
	Environment.time = stf(worldMap.date.hour) + stf(worldMap.date.min)/60.0 + stf(worldMap.date.sec)/3600.0;
	Environment.date.year = worldMap.date.year;
	Environment.date.month = worldMap.date.month;
	Environment.date.day = worldMap.date.day;


	InterfaceStates.Buttons.Load.enable = true;
	
	Event("DoInfoShower","sl","game prepare",false);

	StartLanguageSetting(LanguageGetLanguage());
 	LoadPlayerProfileDefault(); // boal
	LaunchMainMenu();
	//LaunchNetTopListScreen();

	CharacterIsDead(GetMainCharacter());
	
	ReloadProgressEnd();

}

void SaveGame()
{
	string saveName = GetEventData();
	string saveData = GetEventData();
	DelEventHandler("evntSave","SaveGame");

	aref arTmp;
	if( !FindClass(arTmp,"fader") )
	{
		//implemet interface
		//LaunchQuickSaveMenu();
		pchar.version_number = 104;
		SaveEngineState(saveName);
		ISetSaveData(saveName,saveData);
	}

	//hide interface
	PostEvent("DoInfoShower",1,"sl","save game",false);
	DeleteEntitiesByType("scrshoter");
	HideQuickSaveMenu();
}

void LoadGame()
{
    PauseParticles(true); //fix вылета у форта
    // не помогло DeleteFortEnvironment();  //fix
    
	PauseAllSounds(); // boal fix
    ResetSound();  // fix
    // вылетам у форта НЕТ -->
    if (bSeaActive && !bAbordageStarted)
    {
		SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
	}
	// вылетам у форта НЕТ <--
	
	string saveName = GetEventData();
	DelEventHandler("evntLoad","LoadGame");

	string retStr="";
	SendMessage(&GameInterface,"lse",MSG_INTERFACE_GET_SAVE_DATA,saveName,&retStr);
	if( retStr=="" ) {return;}

	DeleteEntities();
	ClearEvents();
	ClearPostEvents();
	SetTimeScale(1.0);
	TimeScaleCounter = 0;

    string loadScr="";
			loadScr = "loading\start_loading.tga";
				
	CreateEntity(&LanguageObject,"obj_strservice");
	CreateEntity(&reload_fader, "fader");
	SendMessage(&reload_fader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
	SendMessage(&reload_fader, "ls",FADER_PICTURE, loadScr);
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
	ReloadProgressStart();
	pchar.savegamename = saveName;
	SetEventHandler("frame","LoadGame_continue",1);
	
	iCalculateSaveLoadCount("Load");
//	isLoaded = true;
}

void LoadGame_continue()
{
	DelEventHandler("frame","LoadGame_continue");
	FreezeGroupControls(curKeyGroupName,true);
	LoadEngineState(pchar.savegamename);
}

void InterfaceDoExit()
{
	DelEventHandler("frame","InterfaceDoExit");
	InterfaceStates.Launched=false;
	if(sti(InterfaceStates.doUnFreeze)==true)
	{
		SendMessage(&GameInterface,"l",MSG_INTERFACE_RELEASE);
		if(!IsEntity(&aviVideoObj))
		{
			if( bSeaActive && !bAbordageStarted )
			{
				LayerFreeze("sea_realize",false);
				LayerFreeze("sea_execute",false);
			}
			else
			{
				LayerFreeze("realize",false);
				LayerFreeze("execute",false);
			}
		}
		DeleteAttribute(&GameInterface,"");
	}
	switch(interfaceResultCommand)
	{
		case RC_INTERFACE_FORTCAPTURE_EXIT:
			ReloadAfterFortCapture();
			break;

		case RC_INTERFACE_DO_NOTHING:
			break;
		case RC_INTERFACE_MAIN_MENU_EXIT:
			break;
		case RC_INTERFACE_DO_CHECK_UPDATES:
            break;		
		case RC_INTERFACE_DO_NEW_GAME:
			InterfaceStates.doUnFreeze = false;
			DeleteEntities();
			//DeleteSeaEnvironment();
			ResetSound();  // fix
			/*musicName = "";
			oldMusicName = "";
			ResetSoundScheme();
			StopSound(0,0);
			ReleaseSound(0);*/
			ClearEvents();
			ClearPostEvents();

            if (CheckAttribute(pchar, "HeroParam")) // признак, что есть герой
            {
				trace("Main_InitGame");
				Main_InitGame(); // boal вынес все в одинметод, новая игра из страой глючит
			}
			else
			{
				if(LoadSegment("Interface\BaseInterface.c"))
				{
					InitBaseInterfaces_main();
					InitBaseInterfaces();
					UnloadSegment("Interface\BaseInterface.c");
				}
			}
			LaunchSelectCharacter();
		break;
		
		case RC_INTERFACE_DO_LOAD_GAME:
			if(CheckAttribute(&InterfaceStates,"Buttons.Resume.enable") && sti(InterfaceStates.Buttons.Resume.enable) == true)
			{
				LaunchLoadGame(false);
			}
			else
			{
				LaunchLoadGame(true);
			}
			break;
		case RC_INTERFACE_DO_SAVE_GAME:
			LaunchSaveGame();
			break;

		case RC_INTERFACE_DO_OPTIONS:
			LaunchOptionScreen();
			break;
		/*case RC_INTERFACE_DO_CONTROLS:
			LaunchControlsScreen();
			break;
			*/
		case RC_INTERFACE_DO_CREDITS:
		    LaunchAboutScreen();
		break;
		case RC_INTERFACE_DO_RESUME_GAME:
		break;
		case RC_INTERFACE_NET_FINDGAME:
			PrepareNetEnvironment();
			LaunchNetFindGame();
		break;
		case RC_INTERFACE_NET_CREATEGAME:
			LaunchNetCreateGame();
		break;
		case RC_INTERFACE_NET_PLAYERSETTINGS:
			LaunchNetPlayerSettings();
		break;
		case RC_INTERFACE_NET_BUY:
			LaunchNetBuyScreen();
		break;
		case RC_INTERFACE_RANSACK_MAIN_EXIT:
			Return2SeaAfterAbordage();
			break;
		case RC_INTERFACE_CHARACTER_SELECT_EXIT:
			DeleteEntities();
			ClearEvents();
			SetEventHandler("frame","NewGame",1);
			InterfaceStates.doUnFreeze = false;
		break;
		
		/*case RC_INTERFACE_SPEAK_EXIT_AND_CAPTURE:
			string sTargetChr = pchar.speakchr;
			
			pchar.abordage = 1;
			
			Sea_AbordageStartNow(SHIP_ABORDAGE, GetCharacterIndex(sTargetChr), true, true);
			
			
			SetTimeScale(1.0);
			TimeScaleCounter = 0;
			DelPerkFromActiveList("TimeSpeed"); //boal
			
			pchar.speakchr = 0;
			pchar.whospeak = 0;
		break;
		
		case RC_INTERFACE_SPEAK_EXIT_AND_TRADE:
			LaunchStore(SHIP_STORE);
		break;  */
		
		case RC_INTERFACE_TO_CHAR:
			pchar = GetMainCharacter();
			LaunchCharacter(pchar);
		break;
		
		/*
		case RC_INTERFACE_TO_PASS:
			pchar = GetMainCharacter();
			LaunchPassengers(pchar);
		break;
		*/
		
		case RC_INTERFACE_TO_SHIP:
			LaunchShipState();
		break;
		
		/*
		case RC_INTERFACE_TO_TRADEBOOK:
			LaunchTradeBook();
		break;
		*/
		
		case RC_INTERFACE_TO_LOGBOOK:
			LaunchQuestBook();
		break;
		
		case RC_INTERFACE_TO_ITEMS:
			LaunchItems(); // to_do
		break;

		case RC_INTERFACE_LAUNCH_GAMEMENU:
			LaunchGameMenuScreen();
			break;
		case INTERFACE_NET_ENDGAME:
			ReturnToMainMenu();
		break;
		// boal -->
  		case RC_INTERFACE_DO_BOAL_BETA:
		     LaunchBoalBetaScreen();
        break;
		// boal <--
		
		// Warship -->
		case RC_INTERFACE_BEST_MAP:
			LaunchBestMapScreen(); // Смотрим отличную карту
			break;
		// <-- Warship
		
		case RC_INTERFACE_MAPVIEW:
			LaunchMapViewScreen(); // Смотрим атлас карт
			break;
	}
}

void EngineLayersOffOn(bool on)
{
	on = !on;
	if( on ) {
		LayerFreeze("realize",on);
		LayerFreeze("execute",on);
		LayerFreeze("sea_realize",on);
		LayerFreeze("sea_execute",on);
	} else {
		if(bSeaActive && !bAbordageStarted) {
			LayerFreeze("sea_realize",on);
			LayerFreeze("sea_execute",on);
		} else {
			LayerFreeze("realize",on);
			LayerFreeze("execute",on);
		}
	}
}

string seadogs_saveFrom = "";

void OnSave()
{
	seadogs_saveFrom = "";
	if(IsEntity(&worldMap) != 0)
	{
		seadogs_saveFrom = "world map";
	}
	else
	{
		if(IsEntity(&AISea) != 0)
		{
			Sea_Save();
			seadogs_saveFrom = "sea";
		}
		else
		{
			int ldLoc = FindLoadedLocation();
			if(ldLoc >= 0)
			{
				seadogs_saveFrom = "location";
				SendMessage(&Locations[ldLoc], "l", MSG_LOCATION_SETCHRPOSITIONS);
				LAi_SaveInfo();
				PostEvent("SeaDogs_ClearSaveData", 400, "a", &Locations[ldLoc]);
			}
			else
			{
				Trace("OnSave() -> unknow character location");
				return;
			}
		}
	}
	
	
	
	iCalculateSaveLoadCount("Save");

}

void ClearLocationsSaveData()
{
	aref loc = GetEventData();
	SendMessage(loc, "l", MSG_LOCATION_CLRCHRPOSITIONS);
}

int actLoadFlag = 0;

void OnLoad()
{
	actLoadFlag = 1;
    
	DeleteAttribute( pchar, "abordage_active_count" );
	FreezeGroupControls(curKeyGroupName,false);

	if( CharacterIsDead(pchar) ) {
		pchar.chr_ai.hp = 1.0;
	}

	Nation_InitAfterLoading();
	ResetSound();

	//CreateClass("dummy");

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		//InitBaseInterfaces_main();
		InitBaseInterfaces();
		InitInterfaceTables();
		UnloadSegment("Interface\BaseInterface.c");
	}
	
	ReloadProgressUpdate();
	
	DialogsInit();
	//IslandsInit();
	//LocationInit();

	ReloadProgressUpdate();

	InitCharacterEvents();
	ReloadProgressUpdate();

	QuestsInit();
	ReloadProgressUpdate();
	
	InitTeleport();
	ReloadProgressUpdate();
	
	InitParticles();
	ReloadProgressUpdate();
	//ImportFuncTest();

//	if(LoadSegment("items\initItems.c")) // ugeen fix 29.03.2020
//	{
//		InitItems();
//		UnloadSegment("items\initItems.c");
//	}
//	ReloadProgressUpdate();
//	GenerateGenerableItems(); // <-- ugeen генерация предметов	

    fix30032020();

	WeatherInit();
	ReloadProgressUpdate();

	InterfaceStates.Buttons.Resume.enable = true;
	InterfaceStates.Buttons.Save.enable = true;
	InterfaceStates.Buttons.Load.enable = true;

	if(seadogs_saveFrom == "location")
	{
		ref mainchar;
		mainchar = GetMainCharacter();
		// boal: лажа это!!  есть actLoadFlag  //mainchar.isload = 1;
		LoadMainCharacterInFirstLocation(mainchar.location,"", mainchar.location.from_sea);
		int ldLoc = FindLoadedLocation();
		if(ldLoc >= 0)
		{
			SendMessage(&Locations[ldLoc], "l", MSG_LOCATION_TLPCHRPOSITIONS);
		}
	}
	else
	{
		if (seadogs_saveFrom == "sea")
		{
			Sea_Load();
 		}
		else
		{
			if(seadogs_saveFrom == "world map")
			{
				wdmLoadSavedMap();
			}
			else
			{
				Trace("Unknow seadogs_saveFrom == " + seadogs_saveFrom);
			}
		}
	}

	//ReloadEndFade();
	EngineLayersOffOn(true);
	//NewGame();
	DialogRun = false;
	InterfaceStates.Launched = false;
	
	ReloadProgressUpdate();

	PerkLoad();

	ReloadProgressUpdate();
	
	LoadGameOptions();

	ReloadProgressEnd();

	if( CheckAttribute(&InterfaceStates,"WorldSituationUpdateStep") &&
		sti(InterfaceStates.WorldSituationUpdateStep) < 10 )
	{
		Event("EvSituationsUpdate", "l", sti(InterfaceStates.WorldSituationUpdateStep));
	}

	actLoadFlag = 0;
	////
	ProcessVersionCheck();
	
	iCalculateSaveLoadCount("Load");
	
	String sCondition;
	for(int i=0; i<MAX_GAMEMODE_CONDITIONS; i++)
	{
		sCondition = GameModeConditions[i];
		if(sCondition == "") continue;
		SetEventHandler(sCondition, sCondition, 0); // Обновим евент, т.к. терся
		Log_TestInfo("Обновлено прерывание - " + sCondition);
		if(sCondition == "JunglesSitBand_InFlameLocator")
		{
			CreateFireParticles("Sit", "KosterFlame");
			Log_TestInfo("Обновлен партикл огня");
		}
	}
//	isLoaded = true;
}

void NewGame()
{
	DeleteEntities();
	DelEventHandler("frame","NewGame");

	CreateEntity(&LanguageObject,"obj_strservice");
	CreateEntity(&reload_fader, "fader");
	SendMessage(&reload_fader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
	//SendMessage(&reload_fader, "ls",FADER_PICTURE, RandPhraseSimple("loading\battle.tga", "loading\Start_Loading.tga"));
	SendMessage(&reload_fader, "ls",FADER_PICTURE, "loading\Start_Loading.tga");
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);

	SetEventHandler("frame","NewGame_continue",1);
}

void NewGame_continue()
{
	DeleteAttribute( pchar, "abordage_active_count" );  // это тут не рабоатет :)  Но и не мешает Boal

	ReloadProgressStart();

	DelEventHandler("frame","NewGame_continue");

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}

	InitGame();
	
	ReloadProgressUpdate();
	
	CreateColonyCommanders();

	ReloadProgressUpdate();

	SetNames();
		
	ReloadProgressUpdate();
	
	Environment.date.hour = worldMap.date.hour;
	Environment.date.min = worldMap.date.min;
	Environment.date.sec = worldMap.date.sec;
	Environment.time = stf(worldMap.date.hour) + stf(worldMap.date.min)/60.0 + stf(worldMap.date.sec)/3600.0; //boal
	Environment.date.year = worldMap.date.year;
	Environment.date.month = worldMap.date.month;
	Environment.date.day = worldMap.date.day;

	InterfaceStates.WorldSituationUpdateStep = 100;
	InterfaceStates.Buttons.Resume.enable = true;
	InterfaceStates.Buttons.Save.enable = true;
	InterfaceStates.Buttons.Load.enable = true;
	
	pchar = GetMainCharacter(); //fix
		
	initNewMainCharacter(); // все там
	
	ReloadProgressUpdate();
		
	InitPsHeros();   // boal 05/07/06 ПГГ	
	ReloadProgressUpdate();
	
    RumourInit();  //homo 23/06/06	
	ReloadProgressUpdate();
	
	ActivateTimeEvents();
	ReloadProgressUpdate();
			
	startGameWeather = true;
		
	InterfaceStates.startGameWeather = FindWeather("11 Hour");
	if (startHeroType != 1) LoadMainCharacterInFirstLocationGroup("Ship_deck_Low", "goto", "goto4");
    	
	UpdateCrewInColonies(); // пересчет наемников в городах
	
	ReloadProgressEnd();
//	isLoaded = false;
}

void InitGame()
{
	LayerCreate("realize", 1);
	LayerCreate("sea_realize", 1);
	LayerCreate("iRealize", 1);
	LayerCreate("fader_realize", 1);
	LayerCreate("inf_realize", 1);
	
	InitSound();

	ReloadProgressUpdate();

	DeleteSeaEnvironment();
	//CharactersInit();
	if(LoadSegment("worldmap\worldmap_init.c"))
	{
		wdmInitWorldMap();
		UnloadSegment("worldmap\worldmap_init.c");
	}
    InitPerks();
    ReloadProgressUpdate();
    
	IslandsInit();
	ReloadProgressUpdate();
	
	LocationInit();
	ReloadProgressUpdate();
	
	DialogsInit();
	ReloadProgressUpdate();
	
	InitTeleport();
	ReloadProgressUpdate();
	
	InitParticles();
	ReloadProgressUpdate();

    if(LoadSegment("items\initItems.c"))
	{
		InitItems();
		UnloadSegment("items\initItems.c");
	}

	ReloadProgressUpdate();
	GenerateGenerableItems(); // <-- ugeen генерация предметов
	
	ReloadProgressUpdate();
	
	CharactersInit();

	ReloadProgressUpdate();
	
	ColoniesInit();
	ReloadProgressUpdate();
	
	if(LoadSegment("store\initStore.c"))
	{
		InitStores();
		UnloadSegment("store\initStore.c");
	}
	
	QuestsInit();
	ReloadProgressUpdate();

	
	SeaAIGroupsInit();
	ReloadProgressUpdate();
	
	InitQuestMapEncounters();
	ReloadProgressUpdate();
	
	//InitLandRandomEncounters();
	//ReloadProgressUpdate();

	//SetNextWeather("10 Hours");

	ResetQuestMovie();
	ReloadProgressUpdate();
	
	LoadGameOptions();

	ReloadProgressUpdate();
	InfoShowSetting();
	
	bAddonContent = GetDLCenabled(DLC_APPID_1);
	//bAddonContent = true;
	trace("bAddonContent1 " + bAddonContent);
/*	
	bAddon2 = GetDLCenabled(DLC_APPID_2);
	//bAddon2 = true;
	trace("bAddonContent2 " + bAddon2);
*/	
}

int counter = 0;
void ProcessControls()
{
	string ControlName;
	ControlName = GetEventData();
	// boal -->
 	aref  arItm;
    int   itmIdx;
	String itemID;
	bool bOk, bOk1;
	
	//if (bBettaTestMode) Log_QuestInfo(ControlName);
    // boal <--
	//trace("ProcessControls() : " + ControlName);
 	if( !IsNetActive() )
	{
		if (ControlName == "QuickSave") { MakeQuickSave(); }
		if (ControlName == "QuickLoad") { MakeQuickLoad(); }
	}

    if (dialogRun) return;
	if (sti(InterfaceStates.Launched)==true) return;
	
	if (ControlName == "WhrPrevWeather")	{ Whr_LoadNextWeather(-1); }
	if (ControlName == "WhrNextWeather")	{ Whr_LoadNextWeather(1); }
	if (ControlName == "WhrUpdateWeather")	{ Whr_UpdateWeather(); }
	
	//if (ControlName == "Help") RunHelpChooser();

	if(bSeaActive && !bAbordageStarted)
	{
		switch(ControlName)
		{
			case "MainMenu": ProcessMainMenuKey();	break;
			case "MainMenuDouble": ProcessMainMenuKey(); break;
			case "Interface": ProcessInterfaceKey(); break;

			case "Sea_CameraSwitch": SeaCameras_Switch(); break;
			case "Ship_Fire": Ship_DoFire(); break;

			case "Tele": Sea_ReloadStart(); break;
		}
	}
	else
	{
		switch(ControlName)
		{
			case "MainMenu": ProcessMainMenuKey();	break;
			case "MainMenuDouble": ProcessMainMenuKey(); break;
			case "Interface": ProcessInterfaceKey();break;
			case "Tele": 
				StartQuickTeleport();
				break;
			case "TeleBack": Teleport(-1); break;
			case "Action":
				//DumpAttributes(loadedLocation/*loadedLocation.reload.reload1.x*/);
				//trace("Y: " + loadedLocation.reload.reload1.y);
				//trace("Z: " + loadedLocation.reload.reload1.z);
			break;
		}
	}
	
	

    // boal 27.11.03 time -->
  	if (ControlName=="TimeScaleFaster" || ControlName == "TimeScaleSlower")
  	{
        if (loadedLocation.type == "underwater") return; //запрет ускорения под водой.
		if (CheckAttribute(pchar, "questTemp.NoFast")) return; //запрет ускорения
		DeleteAttribute(pchar, "pause");
		if (ControlName == "TimeScaleFaster")
     	{
			if (TimeScaleCounter >= 12)
			{
			    TimeScaleCounter += 4;
			}
			else
			{
                if (TimeScaleCounter >= 4)
				{
				    TimeScaleCounter += 2;
				}
				else
				{
					TimeScaleCounter++;
				}
			}
		}
     	else
     	{
            if (TimeScaleCounter >= 16)
			{
			    TimeScaleCounter -= 4;
			}
			else
			{
                if (TimeScaleCounter >= 6)
				{
				    TimeScaleCounter -= 2;
				}
				else
				{
					TimeScaleCounter--;
				}
			}
		}
		if (true) // MOD_SKILL_ENEMY_RATE > 1) // запрет 0.25 скорости
        {
		   if (!bBettaTestMode && TimeScaleCounter < -2) TimeScaleCounter = -2;
		} 
        if (bDisableMapEnter)
        {
            if (TimeScaleCounter > 20) TimeScaleCounter = 20;
        }
        else
        {   // без боя
            if (bSeaActive && !bAbordageStarted )
            {
            	if (TimeScaleCounter > 28) TimeScaleCounter = 28; // море
            }
            else
            {
            	if (TimeScaleCounter > 8) TimeScaleCounter = 8; // суша
            }
        }
        if (IsEntity(worldMap))
        {
            if (TimeScaleCounter > 6) TimeScaleCounter = 6;
        }
     	float newTimeScale = 1 + (TimeScaleCounter)*0.25; // GetSeaTimeScale()
     	if (newTimeScale < 0) //don't wanna crash the game
     	{
        		TimeScaleCounter = -4;
        		newTimeScale = 0;
     	}

     	Log_SetStringToLog("x" + newTimeScale);
     	if (TimeScaleCounter == 0) //back to normal
     	{
			if(IsPerkIntoList("TimeSpeed"))
        	{
        		SetTimeScale(1.0);
        		DelPerkFromActiveList("TimeSpeed");
        	}
     	}
     	else
     	{
        	SetTimeScale(newTimeScale);
        	//if perk not in list
        	if(!IsPerkIntoList("TimeSpeed"))
        	{
				AddPerkToActiveList("TimeSpeed");
			}
     	}
	}
	// boal <--
	switch(ControlName)
	{
        case "TimeScale":
            DeleteAttribute(pchar, "pause");
			if (loadedLocation.type == "Underwater") return; //запрет ускорения под водой.
			if (CheckAttribute(pchar, "questTemp.NoFast")) return; //запрет ускорения
			if(IsPerkIntoList("TimeSpeed"))
			{
				SetTimeScale(1.0);
				TimeScaleCounter = 0;
                Log_SetStringToLog(XI_ConvertString("Time x1"));
				DelPerkFromActiveList("TimeSpeed");
			}
			else
			{
				SetTimeScale(GetSeaTimeScale());
				TimeScaleCounter = 4;
                Log_SetStringToLog(XI_ConvertString("Time x2"));
				AddPerkToActiveList("TimeSpeed");
			}
		break;
	
		case "ChangeShowInterface":
			bOk = bSeaActive || IsEntity(worldMap);
			bOk1 = bLandInterfaceStart;			
			if(bOk || bOk1) 
			{ 
				ChangeShowIntarface();
			}			
		break;
		
		case "TestShipCurrentSea":
			// пока не вытирать - нужно для всяческих тестов !!!!						
//			bOk = !bSeaActive;
//			bOk1 = bLandInterfaceStart && !LAi_IsFightMode(pchar);			
//			if(bOk || bOk1) 
//			{
//				pchar.chr_ai.energy = 0;
//				MakeSailDmg(1, 15.0);
//				GetAllSailsDamagePercent(pchar);
//				LaunchRepair(pchar);
//				TestShipInCurrentSea();
//			}
		break;
	
		case "VK_PAUSETimePause":
			if (!CheckAttribute(pchar, "pause"))
			{
				pchar.pause = true;
				SetTimeScale(0.0);
			    TimeScaleCounter = -3;
			    AddPerkToActiveList("TimeSpeed");
			}
			else
			{
                DeleteAttribute(pchar, "pause");
				SetTimeScale(1.0);	
				DelPerkFromActiveList("TimeSpeed");
				TimeScaleCounter = 0;
			}
		break;
		
		case "WMapCancel":
			if(IsEntity(&worldMap))
			{
				pchar.space_press = 1;
				DeleteAttribute(pchar, "SkipEshipIndex");// boal
			}
		break;
		
		case "Map_Best":
		//	if (bBettaTestMode) LaunchPaperMapScreen();
			if(CheckCharacterItem(PChar, "Map_Best") || bBettaTestMode) LaunchBestMapScreen();
		break;

		// --> ugeen
		case "MapView":
			bOk = bSeaActive && !bAbordageStarted;
			bOk1 = bLandInterfaceStart && !LAi_IsFightMode(pchar);			
			if(bOk || bOk1) 
			{ // изврат - но по другому никак :(
				if(CheckCharacterItem(PChar, "MapsAtlas") && pchar.MapsAtlasCount > 0) LaunchMapViewScreen();
			}	
		break;
		
		case "Alchemy":				
			if(CheckAttribute(pchar,"alchemy.known") && bLandInterfaceStart && !LAi_IsFightMode(pchar))
			{
				LaunchAlchemyScreen();
			}
		break;
		// <-- ugeen

		case "OfficersCharge":
			if(GetOfficersQuantity(pchar) > 0)
			{
				pchar.OfficerAttRange = 35.0;
				OfficersFollow();
				Log_SetStringToLog("Officers Charge!");
			}	
		break;

		case "OfficersFollow":
			if(GetOfficersQuantity(pchar) > 0)
			{
				pchar.OfficerAttRange = 7.0;
				OfficersFollow();
				Log_SetStringToLog("Officers Follow!");
			}	
		break;

		case "OfficersHold":
			if(GetOfficersQuantity(pchar) > 0)
			{
				pchar.OfficerAttRange = 7.0;
				OfficersHold();
				Log_SetStringToLog("Officers Hold!");
			}	
		break;
		
		// boal -->
		case "ChrBackward": //ChrStrafeLeft ChrStrafeRight
            if (bLandInterfaceStart && LAi_IsFightMode(pchar))
            {
				pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
 				if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
	        }
		break;
		
		case "ChrStrafeLeft":
            if (bLandInterfaceStart && LAi_IsFightMode(pchar))
            {
				pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
 				if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
	        }
		break;
		
		case "ChrStrafeRight":
            if (bLandInterfaceStart && LAi_IsFightMode(pchar))
            {
				pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
 				if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
	        }
		break;
		
		case "BOAL_UsePotion": // boal KEY_C
            if (bLandInterfaceStart)
            {
				if(LAi_IsPoison(pchar)) 
				{
					if (UseBestPotion(pchar, true) == 0) 
					{
						if (UseBestPotion(pchar, false) == 0) 
						{
							Log_SetStringToLog(XI_ConvertString("No Potion Found"));
						}
					}
				}
				else 
				{
					if (UseBestPotion(pchar, false) == 0) 
					{
						if (UseBestPotion(pchar, true) == 0) 
						{
							Log_SetStringToLog(XI_ConvertString("No Potion Found"));
						}
					}
				}	
	        }
		break;
		
		// Warship 13.06.09 Выпить противоядие KEY_V
		case "UseAntidote":
			if(bLandInterfaceStart)
            {
				if(FindCharacterAntidote(PChar, &itemID)) // В itemID запишется ID предмета, который можно использовать
				{
					DoCharacterUsedItem(PChar, itemID);
					Log_Info("Use antidote");
				}
			}
		break;
		
		case "Dolly":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(location, "dolly"))
			{
				bOk = (IsCharacterInLocator(pchar, "item", "dolly1")) || (IsCharacterInLocator(pchar, "item", "dolly2")) || (IsCharacterInLocator(pchar, "item", "dolly3"))
				if (CheckAttribute(location, "canteleport") && bOk && !CheckAttribute(pchar, "questTemp.LSC.MaryBye"))
				{
					if (CheckAttribute(pchar, "questTemp.NotTeleportation")) DoQuestCheckDelay("TalkSelf_Quest", 0.1);
					else
					{
					if (IsCharacterInLocator(pchar, "item", "dolly1")) sGlobalTemp = "dolly1";
					if (IsCharacterInLocator(pchar, "item", "dolly2")) sGlobalTemp = "dolly2";
					if (IsCharacterInLocator(pchar, "item", "dolly3")) sGlobalTemp = "dolly3";
					Dolly_TeleportStart();
				}
			}
			}
			if (CheckAttribute(location, "id") && location.id == "Treasure_Alcove") // калеуче
			{
				bOk = (IsCharacterInLocator(pchar, "teleport", "teleport0")) || (IsCharacterInLocator(pchar, "teleport", "teleport1")) || (IsCharacterInLocator(pchar, "teleport", "teleport2")) || (IsCharacterInLocator(pchar, "teleport", "teleport3")) || (IsCharacterInLocator(pchar, "teleport", "teleport4")) || (IsCharacterInLocator(pchar, "teleport", "teleport5")) || (IsCharacterInLocator(pchar, "teleport", "teleport6"))
				if (bOk)
				{
					if (IsCharacterInLocator(pchar, "teleport", "teleport0")) sGlobalTemp = "teleport0";
					if (IsCharacterInLocator(pchar, "teleport", "teleport1")) sGlobalTemp = "teleport1";
					if (IsCharacterInLocator(pchar, "teleport", "teleport2")) sGlobalTemp = "teleport2";
					if (IsCharacterInLocator(pchar, "teleport", "teleport3")) sGlobalTemp = "teleport3";
					if (IsCharacterInLocator(pchar, "teleport", "teleport4")) sGlobalTemp = "teleport4";
					if (IsCharacterInLocator(pchar, "teleport", "teleport5")) sGlobalTemp = "teleport5";
					if (IsCharacterInLocator(pchar, "teleport", "teleport6")) sGlobalTemp = "teleport6";
					Caleuche_TeleportStart();
				}
			}
		break;
		
		case "Ultimate_potion":
			if (CheckCharacterItem(pchar, "Ultimate_potion")) UltimatePotionEffect();
		break;
		
		case "WMapGetCoords":
			/*if(IsEntity(worldMap))
			{		
				Log_SetStringToLog("X = " + worldMap.playerShipX + " Z = " + worldMap.playerShipZ + " AY = " + worldMap.playerShipAY);
				Log_SetStringToLog("Текущие координаты : " + Map_GetRealCoordZ(makefloat(worldMap.playerShipZ)) + "  " + Map_GetRealCoordX(makefloat(worldMap.playerShipX)));
			}	*/
		break;

		case "Ship_GetPosition":
/*		
			if (bSeaActive && !bAbordageStarted)
			{
				if (CheckAttribute(pchar, "Ship.pos.x"))
				{
					//Log_SetStringToLog("X :" + pchar.ship.pos.x + " Y :" + pchar.ship.pos.y + " Z :" + pchar.ship.pos.z);
					Log_SetStringToLog("aX :" + pchar.ship.ang.x + " aY :" + pchar.ship.ang.y + " aZ :" + pchar.ship.ang.z);
					trace("aX :" + pchar.ship.ang.x + " aY :" + pchar.ship.ang.y + " aZ :" + pchar.ship.ang.z);
					//Log_SetStringToLog("Текущие координаты : " + Sea_GetRealCoordZ(makefloat(pchar.Ship.pos.z)) + "  " + Sea_GetRealCoordX(makefloat(pchar.Ship.pos.x)));	
				}	
			}	
*/			
		break;
		
		case "Test_MastFall":
			if (bSeaActive && !bAbordageStarted)
			{
				Log_SetStringToLog("Test_MastFall");
				SendMessage(pchar, "ll", MSG_SHIP_TEST_MAST_FALL, 0);
			}	
		break;
		
        case "BOAL_ActivateRush":  // boal KEY_F
			if (bLandInterfaceStart && GetCharacterPerkUsing(pchar, "Rush") && CheckCharacterItem(pchar, "berserker_potion"))
            {
		        ActivateCharacterPerk(pchar, "Rush");
				PerkBerserkerReaction();
		    }
            else
            {
                if (bLandInterfaceStart && curKeyGroupName == "FightModeControls")
                {
                    PlaySound("interface\knock.wav");
                }
            }
	    break;

	    case "BOAL_DeadSearch":  // boal KEY_1
			if (bLandInterfaceStart)
            {
                itmIdx = Dead_FindCloseBody();
			    if (itmIdx != -1)
			    {
					Dead_OpenBoxProcedure();
				}
				else
				{
                    Log_Info("Некого обыскивать");
				}
		    }
	    break;
	    
		case "BOAL_SetCamera":
		    // по F10
		    //CameraHoldPos();
		    if (MOD_BETTATESTMODE == "On")
		    {
                if(LoadSegment("Debuger.c"))
            	{
                    ActiveF10Control();
            		UnloadSegment("Debuger.c");
            	}
		    }
		break;

        case "BOAL_Control":
		    // по F11 вызывает окно отладчика
		    if (MOD_BETTATESTMODE == "On" || MOD_BETTATESTMODE == "Test")
		    {
		       LaunchDebuderMenu();
		    }
		break;

		case "BOAL_Control3":
		    // по F9 вызывает окно отладчика			
		    if (MOD_BETTATESTMODE == "On")
		    {
		       //LaunchBoalDebugScreenSecond();
		    }
		break;
		
	case "Person_Say": // KEY_T
		// Интерфейс отдыха
		/*if(bLandInterfaceStart) // В "Мыслях вслух"
			LaunchTavernWaitScreen();*/
	break;
		
	case "Say": // KEY_Y
		// Интерфейс автозакупки товаров
		if(bLandInterfaceStart && IsPCharHaveTreasurer() && CheckAttribute(PChar, "TransferGoods.Enable")) // Если есть казначей, включена автозакупка и ГГ находится на суше
			LaunchTransferGoodsScreen();
	break;
        
        case "TeleportActive":
		    if (MOD_BETTATESTMODE == "On")
		    {
                if(LoadSegment("Debuger.c"))
            	{
                    ActiveF4Control();
            		UnloadSegment("Debuger.c");
            	}
		    }
		break;
		
		case "BOAL_ControF5":		
		    if (MOD_BETTATESTMODE == "On")
		    {
                if(LoadSegment("Debuger.c"))
            	{
                    ActiveF5Control();
            		UnloadSegment("Debuger.c");
            	}
		    }
			else
			{
				Statistic_AddValue(PChar, "Cheats.F5", 1);
			}			
		break;

		case "BOAL_ControF7":
		    // по F7 вызывает окно отладчика
		    if (MOD_BETTATESTMODE == "On")
		    {
                if(LoadSegment("Debuger.c"))
            	{
                    ActiveF7Control();
            		UnloadSegment("Debuger.c");
            	}
		    }
			else
			{
				Statistic_AddValue(PChar, "Cheats.F7", 1);
			}			
		break;

        case "BOAL_Control2": // F12
            //Найти ближайшего видимого персонажа в заданном радиусе				
            if(LoadSegment("Debuger.c"))
        	{
                ActiveF12Control(); // можно меять пряв в рабочей игре
        		UnloadSegment("Debuger.c");
        	}		
        break;

        case "BOAL_ControlDebug": // VK_INSERT
            if (MOD_BETTATESTMODE == "On")
		    {
                if(LoadSegment("Debuger.c"))
            	{
                    ActiveINSERTControl();
            		UnloadSegment("Debuger.c");
            	}
        	}
        break;
        // boal <--
	}
	
}

void Teleport(int step)
{
	nTeleportLocation = nTeleportLocation + step;
	if(nTeleportLocation >=	nLocationsNum) nTeleportLocation = 1;
	if(nTeleportLocation <=	0) nTeleportLocation = nLocationsNum - 1;
	
	sTeleportLocName = Locations[nTeleportLocation].id;
	Trace("Teleport to '" + sTeleportLocName + "'");

	ReleaseSound(0);
	ClearEvents();
	ClearPostEvents();
	DeleteEntities();
	SetEventHandler("frame","NewGame",1);
}

void ProcessMainMenuKey()
{
	if (interfacestates.buttons.resume.enable == "1")
	{
		//LaunchMainMenu();
		LaunchGameMenuScreen();
	}
}
// вызов меню по Ф2
void ProcessInterfaceKey()
{
	if( CharacterIsDead(GetMainCharacter()) ) {return;}
	if(bSeaActive && !bAbordageStarted)
	{
		if( CheckAttribute(&BattleInterface,"ComState") && sti(BattleInterface.ComState) != 0 )
			{return;}
	}
	else
	{
		if( SendMessage(GetMainCharacter(),"ls",MSG_CHARACTER_EX_MSG,"IsFightMode") != 0 )
			{return;}
		if( CheckAttribute(&objLandInterface,"ComState") && sti(objLandInterface.ComState) != 0 )
			{return;}
	}
	if (bDisableCharacterMenu) // boal
	{
		Log_SetStringToLog(XI_ConvertString("You can`t launch menu"));
		return;
	}
	if (bAbordageStarted && !bCabinStarted && !bDeckBoatStarted)
	{
		Log_SetStringToLog(XI_ConvertString("You can`t launch menu"));
		return;
	}
	LaunchSelectMenu();
}

void GameOverE()
{
	// вылетам у форта НЕТ -->
    if (bSeaActive && !bAbordageStarted)
    {
		PauseParticles(true); //fix вылета у форта
		SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
	}
	// вылетам у форта НЕТ <--
	GameOver("sea");
	DeleteSeaEnvironment();
}

void GameOver(string sName)
{
	ref mc;
	int nSelect;
	string sFileName;
	//ResetSoundScheme();
	PauseAllSounds();
	ResetSound();
	EngineLayersOffOn(false);
	
	mc = GetMainCharacter();
	
	ClearEvents();
	ClearPostEvents();
	DeleteEntities();

	if(sti(InterfaceStates.Launched)) {
		UnloadSegment(Interfaces[CurrentInterface].SectionName);
	}

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}
	InterfaceStates.showGameMenuOnExit = false;
	InterfaceStates.Buttons.Resume.enable = false;
	InterfaceStates.Buttons.Save.enable = false;

	InitSound();
	SetEventHandler(EVENT_END_VIDEO,"LaunchMainMenu_afterVideo",0);
	//PlayStereoOGG("music_ship_dead");   // boal звук убиения
	switch(sName)
	{
		case "sea":
			/*nSelect = rand(1);
			sFileName = "skeleton_on_beach";
			switch(nSelect)
			{
				case 0: sFileName = "skeleton_on_beach"; break;
				case 1: sFileName = "undersea"; break;
			}
			StartPostVideo(sFileName,1);   */
			StartPictureAsVideo( "loading\seadeath.tga", 5.3 );
			PlayStereoOGG("music_ship_dead");
		break;

		case "boarding":
			StartPictureAsVideo( "loading\seadeath.tga", 5.3 );
		break;

		case "land":
			StartPictureAsVideo( "loading\death.tga", 5.3 );
			PlayStereoOGG("music_death");
		break;

		case "mutiny":
			StartPictureAsVideo( "loading\finalbad2.tga", 5.3 );
			PlayStereoOGG("music_death");
		break;

		case "town":
			StartPictureAsVideo( "loading\finalbad1.tga", 5.3 );
			PlayStereoOGG("music_death");
		break;

		case "blood":
			StartPictureAsVideo( "loading\finalbad2.tga", 5.3 );
			PlayStereoOGG("music_death");
		break;
		
		case "complete": // 040912
			StartPostVideo("credits",1);
		break;
	}
}

void PrepareNetEnvironment()
{
	Net_Start();
}

string its(int iNumber)
{
	string sText = iNumber;
	return sText;
}

// тяжкая игра - сайв токо в церкви 17.03.05 boal
bool QuickSaveGameEnabledHardcore()
{
    bool TmpBool = false;
    ref mchref = GetMainCharacter();

	if (bHardcoreGame)
	{
		int idxLoadLoc = FindLoadedLocation();
	    if( idxLoadLoc!=-1 )
	    {
	        if (CheckAttribute(&Locations[idxLoadLoc], "type"))
	        {
	            if (Locations[idxLoadLoc].type == "church" || Locations[idxLoadLoc].id == "GloriaChurch")
	            {
	                TmpBool = true;
	            }
	        }
	    }
    }
    else
    {
        TmpBool = true;
    }

    return TmpBool;
}

bool CheckBattleSeaSaveEnabled()
{
	return bSeaBattleSave;
}


bool CheckSaveGameEnabled()
{
    bool TmpBool = true;
    ref mchref = GetMainCharacter();
	
    if (CheckAttribute(&InterfaceStates, "Buttons.Save.enable")) 
	{
		if(InterfaceStates.Buttons.Save.enable != 1) 
		{
			TmpBool = false;
		}
	} 
	else 
	{
		TmpBool = false;
	}

	if (bAbordageStarted) {TmpBool = false;}

	if(LAi_IsBoardingProcess()) {TmpBool = false;}

	if( CharacterIsDead(mchref) ) {TmpBool = false;}
		
	if(LAi_IsFightMode(mchref) && MOD_SKILL_ENEMY_RATE > 1) {TmpBool = false;} 
	
	if(bDisableMapEnter && !CheckBattleSeaSaveEnabled() && bSeaActive) {TmpBool = false;} 
	
	if (TmpBool)
	{
		int idxLoadLoc = FindLoadedLocation();
	    if (idxLoadLoc != -1 )
	    {
	        if (Locations[idxLoadLoc].id == "Ship_deck" || Locations[idxLoadLoc].id == "Deck_Near_Ship") // сайв на палубе глюкавый
	        {
	            TmpBool = false;
	        }
	    }
	}
    return TmpBool;
}

// Статистика по сэйвам/лоадам
// Просто чтоб код был в одном месте. _SaveLoad - только "Save" или "Load". Метод вернет общее кол-во загрузок/сохранения
int iCalculateSaveLoadCount(string _SaveLoad)
{
	int iCount;
	ref MChref = GetMainCharacter();
	string sAttrName = _SaveLoad + "Count";	
	iCount = sti(MChref.SystemInfo.(sAttrName));
	iCount++;
	MChref.SystemInfo.(sAttrName) = iCount;
	return iCount;
}

extern void ItemsFix_30032020();


void fix30032020()
{
	ref MChref = GetMainCharacter();
	if( !CheckAttribute(MChref, "fix30032020") )
	{
		if( LoadSegment("items\initItems.c") )
		{
			ItemsFix_30032020();

    			UnloadSegment("items\initItems.c");
    			MChref.fix30032020 = true;
    		}
	}
}


