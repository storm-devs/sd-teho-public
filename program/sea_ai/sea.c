#include "_settings_.h" 

#include "storm-engine\sea_ai\Script_defines.h"
#include "storm-engine\sea_ai\SeaPeople.h"

#include "sea_ai\AIGroup.c"
#include "sea_ai\AIShip.c"
#include "sea_ai\AIFort.c"
#include "sea_ai\AISea.c"
#include "sea_ai\AICameras.c"
#include "sea_ai\AIAbordage.c"
#include "sea_ai\Cabin.c" //boal
#include "sea_ai\AIFantom.c"
#include "sea_ai\AICannon.c"
#include "sea_ai\AIBalls.c"
#include "sea_ai\AIIsland.c"
#include "sea_ai\AISeaGoods.c"
#include "sea_ai\AITasks\AITasks.c"

#include "sea_ai\ShipBortFire.c"
#include "sea_ai\ShipDead.c"
#include "sea_ai\ShipWalk.c"

#include "sea_ai\CoastFoam.c"

#include "sea_ai\Telescope.c"

#include "battle_interface\BattleInterface.c"


#event_handler("Sea_FirstInit", "Sea_FirstInit");
#event_handler("SeaLoad_GetPointer", "SeaLoad_GetPointer");

#define PLAYER_GROUP	"OurGroup"

int	sCurrentSeaExecute = EXECUTE; 
int	sCurrentSeaRealize = REALIZE;

int		iAITemplatesNum;
bool	bSeaActive;
bool	bSeaLoaded = false;
bool 	bSkipSeaLogin = false;
bool	bIslandLoaded = false;
bool	bSeaReloadStarted = false;
bool	bNotEnoughBalls;
bool	bStorm, bTornado;
bool	bSeaQuestGroupHere = false;
bool 	bSeaCanGenerateShipSituation = true; 

int		iStormLockSeconds = 0;

object	Island, IslandReflModel, sLightModel, lighthouseLightModel;
object	Touch, AISea;
object	SeaFader;
object	Seafoam, BallSplash, SinkEffect, PeopleOnShip, Telescope, SeaOperator, Artifact;
object	Sharks;
object	SeaLighter;
object  ShipTracks;

object	SeaLocatorShow;
object	LoginGroupsNow;

ref		rSeaLoadResult;
object	oSeaSave;

bool	bSeaShowLocators = true;
bool	bQuestDisableMapEnter = false;
bool	bFromCoast = false;
bool    bFortCheckFlagYet = false; //eddy. флаг на распознавание врага фортом

float	SeaMapLoadX = -1570.99;
float	SeaMapLoadZ = 950.812;
float	SeaMapLoadAY = 10.54;

float	fSeaExp = 0.0;
float	fSeaExpTimer = 0.0;

int	iSeaSectionLang = -1;

void DeleteSeaEnvironment()
{
    PauseParticles(true); //fix
	Ship_Walk_Delete();

	StopMusic();
	bSeaActive = false;
	bSeaLoaded = false;

	sCurrentSeaExecute = EXECUTE;
	sCurrentSeaRealize = REALIZE;

	pchar.Ship.Stopped = true;
	DeleteBattleInterface();

	DelEventHandler(SHIP_BORT_FIRE, "Ship_BortFire");
	DelEventHandler(BALL_FLY_UPDATE, "Ball_OnFlyUpdate");

	SendMessage(&AISea, "l", AI_MESSAGE_UNLOAD);

	DeleteSea();

	DeleteClass(&ShipTracks);

	DeleteClass(&Island);
	DeleteGrass(); // трава на остров
	DeleteClass(&IslandReflModel);
	DeleteClass(&Touch);
	DeleteClass(&Seafoam);
	DeleteClass(&BallSplash);
	DeleteClass(&SinkEffect);
	//DeleteClass(&PeopleOnShip);
	DeleteClass(&SeaLocatorShow);
	DeleteClass(&SeaOperator);
	DeleteClass(&Telescope);
	DeleteClass(&Sharks);
	DeleteClass(&sLightModel);

	DeleteClass(&SeaLighter);

	if (IsEntity(&Artifact))
		DeleteClass(&Artifact);

	DeleteBallsEnvironment();
	DeleteCannonsEnvironment();
	DeleteSeaCamerasEnvironment();
	DeleteShipEnvironment();
	DeleteFortEnvironment();
	DeleteAbordageEnvironment();
	DeleteSeaGoodsEnvironment();

	DeleteWeatherEnvironment();

	DeleteCoastFoamEnvironment();

	DeleteAttribute(&AISea,"");

	LayerFreeze(SEA_EXECUTE, true);
	LayerFreeze(SEA_REALIZE, true);

	LayerFreeze(REALIZE, false);
	LayerFreeze(EXECUTE, false);

	DeleteClass(&AISea);

	DeleteAnimals();
	
	// delete masts fall modules
	DeleteEntitiesByType("mast");

	// delete hulls fall modules
	DeleteEntitiesByType("hull");	
		
 	// delete particle system
	//	DeleteParticles();

	// delete our group
		Group_DeleteGroup(PLAYER_GROUP);

	// delete fantom and dead groups
		Group_DeleteUnusedGroup();

	// 
		LanguageCloseFile(iSeaSectionLang); iSeaSectionLang = -1;

	//
		Encounter_DeleteDeadQuestMapEncounters();

}

void CreateSeaEnvironment()
{
	if (IsEntity(&Sea)) { Trace("ERROR: CreateSeaEnvironment Sea Already Loaded!!!"); return; } //fix
	
	sCurrentSeaExecute = SEA_EXECUTE;
	sCurrentSeaRealize = SEA_REALIZE;

	iSeaSectionLang = LanguageOpenFile("SeaSection.txt");

	CreateParticleEntity();

	Ship_Walk_Init();

	LayerFreeze(REALIZE, true);
	LayerFreeze(EXECUTE, true);
	//LayerCreate("sea_reflection", 1);
	LayerFreeze(SEA_REFLECTION, false);
	//LayerCreate("sea_reflection2", 1);			// this layer enabled for sea and disabled for abordage
	LayerFreeze(SEA_REFLECTION2, false);

	InterfaceStates.Buttons.Resume.enable = true;
	
	bSeaActive = true;

	//LayerCreate(SEA_REALIZE, 1);
	LayerSetRealize(SEA_REALIZE);
	//LayerCreate(SEA_EXECUTE, 1);
	LayerSetExecute(SEA_EXECUTE);

	LayerFreeze(SEA_EXECUTE, false);
	LayerFreeze(SEA_REALIZE, false);

	CreateSea(SEA_EXECUTE, SEA_REALIZE);			ReloadProgressUpdate();
	CreateWeather(SEA_EXECUTE, SEA_REALIZE);		ReloadProgressUpdate();
	
	CreateEntity(&AISea, "sea_ai");					ReloadProgressUpdate();
	LayerAddObject(SEA_EXECUTE, &AISea, 1);
	LayerAddObject(SEA_REALIZE, &AISea, -1);

	CreateEntity(&Touch, "touch");					ReloadProgressUpdate();
	LayerAddObject(SEA_EXECUTE, &Touch, 1);
	Touch.CollisionDepth = -10.0;
	//LayerAddObject(SEA_REALIZE, &Touch, -1);		// for collision debug

	CreateEntity(&BallSplash, "BallSplash");		ReloadProgressUpdate();
	LayerAddObject(SEA_EXECUTE, &BallSplash, -1);
	LayerAddObject(SEA_REALIZE, &BallSplash, 65535);

	CreateEntity(&SinkEffect, "SINKEFFECT");		ReloadProgressUpdate();
	LayerAddObject(SEA_EXECUTE, &SinkEffect, 65532);
	LayerAddObject(SEA_REALIZE, &SinkEffect, 65532);

	CreateEntity(&ShipTracks, "ShipTracks");		ReloadProgressUpdate();
	LayerAddObject(SEA_EXECUTE, &ShipTracks, 100);
	LayerAddObject(SEA_REALIZE, &ShipTracks, 65531);

/*
	CreateEntity(&PeopleOnShip, "PEOPLE_ON_SHIP");	ReloadProgressUpdate();
	LayerAddObject(SEA_EXECUTE, &PeopleOnShip, 100);
	LayerAddObject(SEA_REALIZE, &PeopleOnShip, 100);
*/
	CreateEntity(&SeaLocatorShow, "SeaLocatorShow"); ReloadProgressUpdate();
	LayerAddObject(SEA_REALIZE, &SeaLocatorShow, -1);

	/*CreateEntity(&Telescope, "TELESCOPE");			ReloadProgressUpdate();
	LayerAddObject(SEA_EXECUTE, &Telescope, -1);
	LayerAddObject(SEA_REALIZE, &Telescope, -3);*/
	TelescopeInitParameters(&Telescope);

	CreateSeaAnimals();								ReloadProgressUpdate();

	// create all other environment
	CreateBallsEnvironment();						ReloadProgressUpdate();
	CreateCannonsEnvironment();						ReloadProgressUpdate();
	CreateSeaCamerasEnvironment();					ReloadProgressUpdate();
	CreateShipEnvironment();						ReloadProgressUpdate();
	CreateFortEnvironment();						ReloadProgressUpdate();
	CreateAbordageEnvironment();					ReloadProgressUpdate();
	CreateSeaGoodsEnvironment();					ReloadProgressUpdate();

	//SetEventHandler(SHIP_CREATE, "Ship_Walk_Create", 0);
	SetEventHandler("MSG_TELESCOPE_REQUEST", "Telescope_Request", 0);
	SetEventHandler(SHIP_BORT_FIRE, "Ship_BortFire", 0);

	bNotEnoughBalls = false;

	Sharks.execute = SEA_EXECUTE;
	Sharks.realize = SEA_REALIZE;
	Sharks.executeModels = 75;
	Sharks.realizeModels = 75;
	Sharks.executeParticles = 78;
	Sharks.realizeParticles = 100001;

	CreateEntity(&Sharks, "Sharks");				ReloadProgressUpdate();

	//PeopleOnShip.isNight = Whr_IsNight();

	// тут лишнее QuestsCheck();
}
// boal -->
string Sea_FindNearColony()
{
	aref aLocators;
	int iNum =  GetAttributesNum(arIslandReload);
	string sColony = "none";

	for(int i = 0; i < iNum; i++)
	{
		aLocators = GetAttributeN(arIslandReload, i);
		if(aLocators.name == sIslandLocator)
		{
			sColony = aLocators.go;
            if(CheckAttribute(&locations[FindLocation(sColony)], "fastreload"))
            {
                sColony = locations[FindLocation(sColony)].fastreload;
                break;
            }
		}
	}
	return sColony;
}
// boal <--
void Sea_LandLoad()
{	
	pchar.shipx = pchar.ship.pos.x;
	pchar.shipz = pchar.ship.pos.z;
	ClearAllLogStrings();
	string sColony = Sea_FindNearColony(); // boal
	int iColony = FindColony(sColony);
	if(iColony != -1)
	{
		if (CheckAttribute(pchar, "ship.crew.disease"))  // to_do
		{
			if (pchar.ship.crew.disease == "1")
			{
				if (Colonies[iColony].disease != "1" && sti(Colonies[iColony].nation) != PIRATE)
				{
					LaunchDiseaseAlert(DISEASE_ON_SHIP);
					return;
				}
			}
		}
		if(CheckAttribute(&Colonies[iColony], "disease.time"))
		{
			if(sti(Colonies[iColony].disease.time > 0))
			{
				LaunchDiseaseAlert(DISEASE_ON_COLONY);  // to_do
				return;
			}
		}
	}
	pchar.CheckEnemyCompanionType = "Sea_LandLoad"; // откуда вход
    if (!CheckEnemyCompanionDistance2GoAway(true)) return; // && !bBettaTestMode  табличка выхода из боя
    
	bSeaReloadStarted = true;
	PauseAllSounds();
	//ResetSoundScheme();
	ResetSound(); // new

	if (bSeaActive == false) return;
	if (bCanEnterToLand == true)
	{
		LayerFreeze(REALIZE, false);
		LayerFreeze(EXECUTE, false);
		Reload(arIslandReload, sIslandLocator, sIslandID);
		ReleaseMapEncounters();
		EmptyAllFantomShips(); // boal
		//Partition_SetValue("after");// Дележ добычи уход на сушу
		DeleteAttribute(pchar, "CheckStateOk"); // проверка протектором
		Group_FreeAllDead();
	}
}

void Sea_MapStartFade()
{
	DelEventHandler("FaderEvent_StartFade", "Sea_MapStartFade");
	DeleteSeaEnvironment();
	EmptyAllFantomCharacter(); // трем НПС
	EmptyAllFantomShips();    // трем корабли
	wdmEmptyAllDeadQuestEncounter(); // трем случайки
	pchar.location = "";
	PGG_DailyUpdate();
	Siege_DailyUpdate();//homo осады 05/11/06
	wdmUpdateAllEncounterLivetime(); // homo карта 25/03/07
	Flag_Rerise(); // переподнять флаг при выходе на карту, прменить отношения нации в столбец ГГ
}

void Land_MapStartFade()
{
	DelEventHandler("FaderEvent_StartFade", "Land_MapStartFade");
	//DeleteSeaEnvironment();
	string deckID = pchar.location; /// fix GetShipLocationID(pchar);

	ref loc = &locations[FindLocation(deckID)];

	UnloadLocation(loc);
	EmptyAllFantomShips();
	wdmEmptyAllDeadQuestEncounter(); // трем случайки
}

void Sea_MapEndFade()
{
	DelEventHandler("FaderEvent_EndFade", "Sea_MapEndFade");
	Partition_SetValue("after");// Дележ добычи уход на карту
	wdmCreateMap(SeaMapLoadX, SeaMapLoadZ, SeaMapLoadAY);
}

void Sea_MapLoadXZ_AY(float x, float z, float ay)
{
	Sea_MapLoad();

	SeaMapLoadX = x;
	SeaMapLoadZ = z;
	SeaMapLoadAY = ay;
}

void Sea_MapLoad()
{
	// boal 201004 проверка на перегруз и мин команду -->
	ref  rPlayer = GetMainCharacter();
    int  i, cn;
    ref  chref;
    bool ok = true;
    //float minShipSpeed = 40; // заведомый мах
    for (i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(rPlayer,i);
		if( cn>=0 )
		{
			chref = GetCharacter(cn);
			
			// запишем текущее состояние парусов для всей эскадры на момент выхода на глобу (это нужно если вдруг нужен ремонт)
			// ибо на глобе некоторые параметры парусов хер определишь без подгрузки корабельных моделек
			GetAllSailsDamagePercent(chref);	
            // рассчет времени на карте от скорости кораблей -->
            /*r1 = GetSailPercent(chref) / 100.0 * GetCharacterShipSpeedRate(chref);
            if (minShipSpeed > r1)
            {
                minShipSpeed = r1;
            }       */
            // рассчет времени на карте от скорости кораблей <--
			if (!GetRemovable(chref)) continue;
			
            if (GetCargoLoad(chref) > GetCargoMaxSpace(chref))
            {
                ok = false;
                Log_SetStringToLog("Корабль '" +  chref.Ship.Name + "' перегружен.");
            }
            if (MOD_SKILL_ENEMY_RATE > 2) // халява и юнга - послабление
    		{
	            if (i > 0 && GetMinCrewQuantity(chref) > GetCrewQuantity(chref))
	            {
	                ok = false;
	                Log_SetStringToLog("На корабле '" +  chref.Ship.Name + "' нет минимального экипажа.");
	            }
			}
			
            if (GetMaxCrewQuantity(chref) < GetCrewQuantity(chref))
            {
                ok = false;
                Log_SetStringToLog("На корабле '" +  chref.Ship.Name + "' перегруз экипажа больше допустимого.");
            }  
        }
    }
    if (!ok)
    {
        Log_Info("Выход на карту невозможен.");
        PlaySound("interface\knock.wav");
        return;
    }
    // boal 201004 проверка на перегруз и мин команду <--
    // рассчет времени на карте от скорости кораблей -->
    /*if (minShipSpeed < 1)
	{
		minShipSpeed = 1;
	}
    worldMap.date.hourPerSec = makefloat(12.5 / minShipSpeed * 4.0);  */
    // рассчет времени на карте от скорости кораблей <--
    pchar.CheckEnemyCompanionType = "Sea_MapLoad"; // откуда вход
    if (!CheckEnemyCompanionDistance2GoAway(true)) return; // && !bBettaTestMode  табличка выхода из боя
    
	LAi_SetAlcoholNormal(pchar);
    
	bSeaReloadStarted = true;
	PauseAllSounds();

 	//ResetSoundScheme();
	ResetSound(); // new
		
	SetEventHandler("FaderEvent_StartFade", "Sea_MapStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "Sea_MapEndFade", 0);

	CreateEntity(&SeaFader, "fader");
	SendMessage(&SeaFader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
	SendMessage(&SeaFader, "lfl", FADER_OUT, 0.7, true);
	SendMessage(&SeaFader, "l", FADER_STARTFRAME);
	SendMessage(&SeaFader, "ls", FADER_PICTURE, "loading\sea_0" + rand(2) + ".tga");

	bSkipSeaLogin = true;

	SeaMapLoadX = stf(pchar.Ship.Pos.x);
	SeaMapLoadZ = stf(pchar.Ship.Pos.z);
	SeaMapLoadAY = stf(pchar.Ship.Ang.y);
}

// нигде не пользуетя, может глючить для абордажа
void Land_MapLoad()
{
	bSeaReloadStarted = true;
	PauseAllSounds();

 	//ResetSoundScheme();
	ResetSound(); // new

	SetEventHandler("FaderEvent_StartFade", "Land_MapStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "Sea_MapEndFade", 0);

	CreateEntity(&SeaFader, "fader");
	SendMessage(&SeaFader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
	SendMessage(&SeaFader, "lfl", FADER_OUT, 0.7, true);
	SendMessage(&SeaFader, "l", FADER_STARTFRAME);
	SendMessage(&SeaFader, "ls", FADER_PICTURE, "loading\sea_0" + rand(2) + ".tga");

	bSkipSeaLogin = true;

	SeaMapLoadX = stf(pchar.Ship.Pos.x);
	SeaMapLoadZ = stf(pchar.Ship.Pos.z);
	SeaMapLoadAY = stf(pchar.Ship.Ang.y);
}

string	sTaskList[2];

void Sea_FreeTaskList()
{
	ref rMassive; 
	makeref(rMassive, sTaskList);
	SetArraySize(rMassive, 2);
}

void Sea_AddGroup2TaskList(string sGroupID)
{
	ref rMassive; 
	makeref(rMassive, sTaskList);
	int iSize = GetArraySize(rMassive);
	SetArraySize(rMassive, iSize + 1);
	sTaskList[iSize-2] = sGroupID;
}

void Sea_LoginGroupNow(string sGroupID)
{
	LoginGroupsNow.QuestGroups = "";
	aref arGroups; makearef(arGroups, LoginGroupsNow.QuestGroups);
	string sID = "n" + GetAttributesNum(arGroups);
	arGroups.(sID) = sGroupID;
}


void SeaLogin(ref Login)
{
	int		i, j, k, iShipType;
	float	x, y, z, ay;
	ref		rCharacter, rGroup, rEncounter;
	aref	rRawGroup;
	aref	arQCGroups; 
	string	sGName;
	int		iNumQCGroups;
	ref 	rFantom;

	bSeaLoaded = false;

	int iRDTSC = RDTSC_B();

	// clear load groups now object
	DeleteAttribute(&LoginGroupsNow, "");

	iStormLockSeconds = 0;
	iNumFantoms = 0;
	bSkipSeaLogin = false;
	bSeaReloadStarted = false;
	bSeaQuestGroupHere = false;
	bIslandLoaded = false;

	fSeaExp = 0.0;
	fSeaExpTimer = 0.0;

	Sea_FreeTaskList();	
	
	Encounter_DeleteDeadQuestMapEncounters();

	// weather parameters
	WeatherParams.Tornado = false; 
	WeatherParams.Storm = false; 
	if (CheckAttribute(&Login,"Storm")) { WeatherParams.Storm = Login.Storm; } 
	if (CheckAttribute(&Login,"Tornado")) { WeatherParams.Tornado = Login.Tornado; } 
	bStorm = sti(WeatherParams.Storm);
	bTornado = sti(WeatherParams.Tornado); 
	if (bStorm)
	{
		iStormLockSeconds = 60;
	}

	// Island
	int iIslandIndex = FindIsland(Login.Island);
	//Trace("Island id = " + Login.Island + ", Island index = " + iIslandIndex);
	string sIslandID = "";
	if (iIslandIndex != -1) { sIslandID = Islands[iIslandIndex].id; }
	
	// main character
	pchar.Ship.Stopped = false;
	pchar.Ship.POS.Mode = SHIP_SAIL;
	pchar.location = sIslandID;

	// clear old fantom relations in our character
		if (CheckAttribute(pchar, "Relation"))
		{
			aref	arRelations; makearef(arRelations, pchar.Relation);
			int		iNumRelations = GetAttributesNum(arRelations);
			for (i=0; i<iNumRelations; i++)
			{
				aref arRelation = GetAttributeN(arRelations, i);
				string sRName = GetAttributeName(arRelation);
				if (sti(sRName) >= FANTOM_CHARACTERS)
				{
					DeleteAttribute(arRelations, sRName);
					iNumRelations--;
					i--;
				}
			}
		}

	// Quest check
	Event(EVENT_SEA_LOGIN, "");
	if (bSkipSeaLogin) return;

	// Sea Fader start
	if (!CheckAttribute(&Login,"ImageName")) { Login.ImageName = "loading\sea_0" + rand(2) + ".tga"; }

	CreateEntity(&SeaFader, "fader");
	SendMessage(&SeaFader, "lfl", FADER_IN, 0.5, true);
	SendMessage(&SeaFader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
	SendMessage(&SeaFader, "ls", FADER_PICTURE, Login.ImageName);

	// create all sea modules
	CreateSeaEnvironment();

	// delete our group
	Group_DeleteGroup(PLAYER_GROUP);

	// set commander to group
	Group_SetGroupCommander(PLAYER_GROUP, Characters[nMainCharacterIndex].id);

	// set our group position
	/*if (checkAttribute(pchar, "sneak"))   // to_do del
	{
		Login.PlayerGroup.x = pchar.sneak.x;
		Login.PlayerGroup.z = pchar.sneak.z;
		pchar.sneak.success = 1;
	}*/
	Group_SetXZ_AY(PLAYER_GROUP, stf(Login.PlayerGroup.x), stf(Login.PlayerGroup.z), stf(Login.PlayerGroup.ay) );
	//Trace("Set player group : " + PLAYER_GROUP + ", PLAYER x = " + Login.PlayerGroup.x + ", PLAYER z = " + Login.PlayerGroup.z + ", PLAYER ay = " + Login.PlayerGroup.ay);
	// boal -->
	NullCharacter.Login.PlayerGroup.x  = Login.PlayerGroup.x;  // 1.2.3 попытка записать коорд ГГ для размещения Group_SetPursuitGroup в кильватерную линию
	NullCharacter.Login.PlayerGroup.z  = Login.PlayerGroup.z;
	NullCharacter.Login.PlayerGroup.ay = Login.PlayerGroup.ay;
	
    pchar.Ship.Pos.x = stf(Login.PlayerGroup.x);
    pchar.Ship.Pos.z = stf(Login.PlayerGroup.z);
    //trace("pchar.Ship.Pos.x = " + pchar.Ship.Pos.x + " pchar.Ship.Pos.z = " + pchar.Ship.Pos.z);
    // boal <--
	Sea.MaxSeaHeight = 200;

	ReloadProgressUpdate();

	// login island if exist
	Sea_LoadIsland(sIslandID);
	
	AISea.Island = sIslandID;

	// clear some of group attributes
	for (i=0; i<MAX_SHIP_GROUPS; i++) 
	{
		rGroup = Group_GetGroupByIndex(i);
		if (CheckAttribute(rGroup, "AlreadyLoaded")) 
		{ 
			DeleteAttribute(rGroup, "AlreadyLoaded"); 
		}
	}

	ReloadProgressUpdate();

	// from coast check (move / stop)
	bFromCoast = false;
	if (CheckAttribute(&Login, "FromCoast")) { bFromCoast = sti(Login.FromCoast); }

	// login main player and his friends
	int iCompanionIndex;

	pchar.SeaAI.Group.Name = PLAYER_GROUP;
	pchar.Ship.Type = Characters[nMainCharacterIndex].Ship.Type;
	pchar.Ship.Stopped = false;
	Partition_SetValue("before");// Дележ добычи
/*	
	if(CheckItemsCRC(pchar) != sti(pchar.SystemInfo.itemsCRC)) 
	{
		Log_Info("CheckItemsCRC(pchar) : " + CheckItemsCRC(pchar) + " sti(pchar.SystemInfo.itemsCRC) :" + sti(pchar.SystemInfo.itemsCRC));
		LAi_SetHP(pchar, 1.0, 1.0);
	}
*/	
	Ship_Add2Sea(nMainCharacterIndex, bFromCoast, "", true);
	Group_AddCharacter(PLAYER_GROUP, Characters[nMainCharacterIndex].id);
	//Sea.Sea2.BumpScale = stf(Sea.Sea2.BumpScale) * stf(RealShips[sti(pchar.Ship.Type)].sea_enchantment);
	int iPlayerCompanionsQ = GetCompanionQuantity(pchar);
	if(iPlayerCompanionsQ > 1)
	{
		for (i=1; i<COMPANION_MAX; i++)
		{
			iCompanionIndex = GetCompanionIndex(&Characters[nMainCharacterIndex],i);
			if (iCompanionIndex == -1) 
			{ 
				continue; 
			}
			DeleteAttribute(&Characters[iCompanionIndex], "SeaAI"); // сброс для кэпов офов из пленных
			Characters[iCompanionIndex].SeaAI.Group.Name = PLAYER_GROUP;
			// to_do убрал для пробы, в ПКМ не было и не тупили	Ship_SetTaskNone(PRIMARY_TASK, iCompanionIndex); // сброс для кэпов офов из пленных
			Ship_Add2Sea(iCompanionIndex, bFromCoast, "", true);

			// add companion to player group
			Group_AddCharacter(PLAYER_GROUP, Characters[iCompanionIndex].id);
			//Ship_SetTaskDefendGroup(PRIMARY_TASK, iCompanionIndex, PLAYER_GROUP);
			// to_do убрал для пробы, в ПКМ не было и не тупили
			Ship_SetTaskDefend(PRIMARY_TASK, iCompanionIndex, nMainCharacterIndex);
		}
	}
    //SetMaxSeaHeight(sIslandID); // boal волны у острова
	// set ship for sea camera
	SeaCameras_SetShipForSeaCamera(&pchar);

	// login encounters
	object oResult;
	int iFantomIndex;

	if (sIslandID != "")
	{
		GenerateIslandShips(sIslandID);
	}

	ReloadProgressUpdate();

	// login quest group if island exist
	ReloadProgressUpdate();
	if (sIslandID != "")
	{
		for (i=0; i<MAX_SHIP_GROUPS; i++) 
		{
			rGroup = Group_GetGroupByIndex(i);
			if (!CheckAttribute(rGroup,"AlreadyLoaded")) 
			{ 
				DeleteAttribute(rGroup,"AlreadyLoaded");	
			}

			if (!CheckAttribute(rGroup, "id")) { continue; }
			if (!CheckAttribute(rGroup, "location")) { continue; }
			if (rGroup.location != sIslandID) { continue; }

			Sea_LoginGroup(rGroup.id);
		}
	}

	// login quest groups to sea 
	if (CheckAttribute(&Login, "QuestGroups"))
	{
		arQCGroups; makearef(arQCGroups, Login.QuestGroups);
		iNumQCGroups = GetAttributesNum(arQCGroups);
		for (i=0; i<iNumQCGroups; i++)
		{
			Sea_LoginGroup(GetAttributeValue(GetAttributeN(arQCGroups, i)));
		}
	}

	ReloadProgressUpdate();

	// login quest groups to sea from LoginGroupsNow object
	if (CheckAttribute(&LoginGroupsNow, "QuestGroups"))
	{
		makearef(arQCGroups, LoginGroupsNow.QuestGroups);
		iNumQCGroups = GetAttributesNum(arQCGroups);
		for (i=0; i<iNumQCGroups; i++)
		{
			Sea_LoginGroup(GetAttributeValue(GetAttributeN(arQCGroups, i)));
		}
	}
	
	ReloadProgressUpdate();
		

	//if (!bStorm) //убираем по требованию продюсеров
	//{
	// login fantom groups		
	aref arEncounters;
	makearef(arEncounters,Login.Encounters);
	int iNumGroups = GetAttributesNum(arEncounters);

	for (i=0; i<iNumGroups; i++)
	{
		int iAloneCharIndex = -1;

		rRawGroup = GetAttributeN(arEncounters, i);
		rEncounter = GetMapEncounterRef(sti(rRawGroup.type));
		
		if (!CheckAttribute(rEncounter, "RealEncounterType")) // boal проверка на лажу
		{
			trace("Для случайки не указан RealEncounterType, игнорируем её");
			continue;
		}		
		int iEncounterType = sti(rEncounter.RealEncounterType);
		//trace ("RealEncounterType is " + iEncounterType);

		x = stf(rRawGroup.x);
		z = stf(rRawGroup.z);
		ay = stf(rRawGroup.ay);

		//Trace("Set raw group : x = " + x + ", z = " + z + ", ay = " + ay);
		
		ReloadProgressUpdate();

		int iCompanionsQ;
		int cn;

		if (iEncounterType == ENCOUNTER_TYPE_ALONE)
		{		
			iAloneCharIndex = GetCharacterIndex(rEncounter.CharacterID);
			if (iAloneCharIndex < 0) 
			{ 
				continue; 
			}
			sGName = "Sea_" + rEncounter.CharacterID; //boal для удобства манипулирования в др методах "EncTypeAlone_" + iAloneCharIndex;
			// можно задать группу их 10 кораблей или всего 4 компаньона - работает и так, и так. И даже задать и то, и то. Будут вместе.
			
			Group_AddCharacter(sGName, rEncounter.CharacterID);
			
			iCompanionsQ = GetCompanionQuantity(&Characters[iAloneCharIndex]);
			if(iCompanionsQ > 1)
			{
				for(k = 1; k < COMPANION_MAX; k++)
				{
					cn = GetCompanionIndex(&characters[iAloneCharIndex], k);
					if (cn != -1)
					{
						Group_AddCharacter(sGName, characters[cn].id);
					}
				}
			}

			Group_SetGroupCommander(sGName, characters[iAloneCharIndex].id);

			if(GetNationRelation2MainCharacter(sti(characters[iAloneCharIndex].nation)) == RELATION_ENEMY)
			{
				Group_SetTaskAttack(sGName, PLAYER_GROUP);
				Group_LockTask(sGName);
			}

			rEncounter.qID = sGName; // перевел все в группу boal 23/06/06
			
		}
		else
		{
			sGName = rEncounter.GroupName;
		}
		// check for Quest fantom
		if (CheckAttribute(rEncounter, "qID"))
		{
			//Trace("SEA: Login quest encounter " + rEncounter.qID);
			Group_SetAddressNone(rEncounter.qID);
			Group_SetXZ_AY(rEncounter.qID, x, z, ay);						
			Sea_LoginGroup(rEncounter.qID);			
			continue;
		}

		//if (bSeaQuestGroupHere) { continue; }

		Sea_AddGroup2TaskList(sGName);

		//rGroup = Group_GetGroupByIndex(Group_CreateGroup(sGName));
		//rGroup = Group_GetGroupByIndex(Group_FindOrCreateGroup(sGName)); // <--- Вот кто это написал!!!??? :)
		//trace("sGName = " + sGName);
		rGroup = Group_FindOrCreateGroup(sGName); // надо так
		Group_SetXZ_AY(sGName, x, z, ay);
		Group_SetType(sGName, rEncounter.Type);
		Group_DeleteAtEnd(sGName);

		// copy task attributes from map encounter to fantom group
		if (CheckAttribute(rEncounter, "Task"))							
		{ 
			rGroup.Task = rEncounter.Task; 
		}
		if (CheckAttribute(rEncounter, "Task.Target"))					
		{ 
			rGroup.Task.Target = rEncounter.Task.Target; 
		}
		if (CheckAttribute(rEncounter, "Task.Pos")) 
		{
			rGroup.Task.Target.Pos.x = rEncounter.Task.Pos.x;
			rGroup.Task.Target.Pos.z = rEncounter.Task.Pos.z;
		}
		if (CheckAttribute(rEncounter, "Lock") && sti(rEncounter.Lock)) { Group_LockTask(sGName); }
        // перевел все в группу boal 23/06/06 -->
		/*if (iEncounterType == ENCOUNTER_TYPE_ALONE)
		{
			//Group_SetGroupCommander(sGName, Characters[iAloneCharIndex].id);
			Characters[iAloneCharIndex].SeaAI.Group.Name = sGName;
			Ship_Add2Sea(iAloneCharIndex, 0, rEncounter.Type, true);

			iCompanionsQ = GetCompanionQuantity(&Characters[iAloneCharIndex]);
			if(iCompanionsQ > 1)
			{
				for(int l = 1; l < COMPANION_MAX; l++)
				{
					cn = GetCompanionIndex(&characters[iAloneCharIndex], l);
					if (cn != -1)
					{
						Characters[cn].SeaAI.Group.Name = sGName;
						Ship_Add2Sea(cn, 0, rEncounter.Type, true);
					}
				}
			}
			continue;
		} */
		// перевел все в группу boal 23/06/06   <--

		int iNumWarShips = 0;
		int iNumMerchantShips = 0;
		int iNation = PIRATE;
		if(CheckAttribute(rEncounter, "NumWarShips"))
		{
			iNumWarShips = sti(rEncounter.NumWarShips);
		}

		if(CheckAttribute(rEncounter, "NumMerchantShips"))
		{
			iNumMerchantShips = sti(rEncounter.NumMerchantShips);
		}

		if(CheckAttribute(rEncounter, "Nation"))
		{
			iNation = sti(rEncounter.Nation);
		}
		
		int iNumFantomShips = Fantom_GenerateEncounterExt(sGName, &oResult, iEncounterType, iNumWarShips, iNumMerchantShips, iNation);
		
		// Ugeen --> генерация параметров	для спецэнкаунтеров
		if (iEncounterType == ENCOUNTER_TYPE_BARREL || iEncounterType == ENCOUNTER_TYPE_BOAT)
		{	
			iFantomIndex = FANTOM_CHARACTERS + iNumFantoms;
			rFantom = &Characters[iFantomIndex];
			rFantom.id = iFantomIndex;
			rFantom.index = iFantomIndex;
			rFantom.Nation = PIRATE;			
			rFantom.EncType  = "pirate";
            rFantom.RealEncounterType = iEncounterType;//boal
			rFantom.reputation = 5 + rand(84);
			rFantom.EncGroupName = sGName;
			rFantom.MainCaptanId = Characters[iFantomIndex].id;
			rFantom.location = sIslandID;
			rGroup.EmptyFantom = true;
			rFantom.sex = "man";
			rFantom.model.animation = "man";			
			SetCaptanModelByEncType(rFantom, rFantom.EncType);
			SetRandomNameToCharacter(rFantom);
			SetSeaFantomParam(rFantom, rEncounter.Type);
			int iRank = sti(pchar.rank) - rand(5) + rand(5);
			if (iRank < 1) iRank = 1;
			SetFantomParamFromRank(rFantom, iRank, false); 
			rFantom.SeaAI.Group.Name = sGName;
			Group_AddCharacter(sGName, rFantom.id);
			Log_TestInfo("Generate Special Encounter");
			EmptyFantom_DropGoodsToSea(rFantom, iEncounterType);			
			continue;
		}
		// <-- Ugeen
		
		//Trace("Set group coords : " + sGName + ", x = " + x + ", z = " + z + ", ay = " + ay);		

        //navy --> 28.12.2009 изменение алгоритам загрузки кораблей случаек в море, чтобы ГГ мордой в центр экскадры не грузился.
        float b, x_mc, z_mc, ay_mc, ay_res, ay_e, z1;
        bool isMChrAttack = false;

        //координаты ГГ
        x_mc = 	stf(Login.PlayerGroup.x);
        z_mc = 	stf(Login.PlayerGroup.z);
        ay_mc = stf(Login.PlayerGroup.ay);
		
		if(ay_mc < 0) ay_mc = ay_mc + PIm2;
		ay_e = ay;
		if(ay < 0) ay_e = ay_e + PIm2;
		
        //угол результирующего вектора между случайкой и ГГ на карте
        ay_res = atan(-((z_mc-z)/(x-x_mc)));

		//Trace("ay_res = " + ay_res);		
		
        //т.к. арктангенс дает только острые углы, то считаем тупые
        if (ay_res < 0 && z > z_mc)
        {
            ay_res += PI;
        }

        if (ay_res > 0 && z < z_mc)
        {
            ay_res += PI;
        }

		//Trace("1. Set player group coords :  x = " + x_mc + ", z = " + z_mc + ", ay = " + ay_mc + ", ay_res = " + ay_res);		
		//Trace("2. Set enemy group coords :  x = " + x + ", z = " + z +", ay = " + ay + ", ay_e = " + ay_e);		
		
        //если угол между вектором ГГ и результирующим вектором острый,
        //то считаем, что атакует ГГ
        if (cos(ay_res - ay_mc) > 0) 
		{
			isMChrAttack = true;
//			Log_TestInfo("ГГ атакует !");
		}

        if (isMChrAttack)
        {
            //определяем знак приращения координаты Х
            if (abs(ay) < PI) k = 1;
            else k = -1;
				
            //уравнение прямой для случайки z = k * x + b
            b = z - ay_e * x;

            //смещаем позицию случайки, коэффициент смещения подобрать экспериментально или ввести функцию.
//			z1 = (k * iNumFantomShips * 200 + x) * ay - b;
			//z1 = k * x * ay + b;
			
//            		Group_SetXZ_AY(sGName, x, z, ay);
			//Trace("Set group new coords : " + sGName + ", x = " + x + ", z = " + z + ", ay_e = " + ay_e + ", b = " + b + ", k = " + k);		
			
        }
		
        //navy <--

		// load ship to sea
		if (iNumFantomShips) 
		{
			for (j=0; j<iNumFantomShips; j++)
			{
				iFantomIndex = FANTOM_CHARACTERS + iNumFantoms - iNumFantomShips + j;
				rFantom = &Characters[iFantomIndex];
                DeleteAttribute(rFantom, "items"); // boal 28.07.04 фикс кучи сабель, когда идет в плен
				DeleteAttribute(rFantom, "DontRansackCaptain");
				DeleteAttribute(rFantom, "surrendered");
				DeleteAttribute(rFantom, "AlwaysFriend");
				rFantom.id = "fenc_" + iFantomIndex;
                // boal 26.02.2004 -->
				rFantom.location = sIslandID;
				// boal 26.02.2004 <--
				// set commander to group
				if (j==0) { Group_SetGroupCommander(sGName, Characters[iFantomIndex].id); }
				
				// set random character and ship names, face id
				rFantom.sex = "man";
				rFantom.model.animation = "man";
				rFantom.Nation = rEncounter.Nation; 
				// boal разговор в море -->
                rFantom.reputation = 5 + rand(84);
                rFantom.EncType      = rEncounter.Type; // тип  war, trade pirate
                rFantom.RealEncounterType = iEncounterType;//boal
                rFantom.EncGroupName = sGName;
                rFantom.MainCaptanId = Characters[iFantomIndex - j].id;
				rFantom.WatchFort = true; //следить за фортом
				rFantom.AnalizeShips = true; //анализить враждебные корабли сразу же с загрузки и далее

				if (CheckAttribute(rFantom, "Ship.Mode"))
                {
                	SetCaptanModelByEncType(rFantom, rFantom.Ship.Mode);
                }
                else
                {
                    SetCaptanModelByEncType(rFantom, rEncounter.Type);
                }
                // boal разговор в море <--
				
				SetRandomNameToCharacter(rFantom);
				SetRandomNameToShip(rFantom);
				
				SetSeaFantomParam(rFantom, rEncounter.Type); // все там
				
				if(j == 0 && rFantom.EncType == "pirate")
				{
					rFantom.Flags.Pirate = rand(2);
				}
				
				if(iEncounterType == ENCOUNTER_TYPE_WAR_PRIVATEER) {rFantom.DontRansackCaptain = true;} // не сдаемся
				
//				trace("rFantom.id = " + rFantom.id + " Ship.pos.x = " + rFantom.Ship.pos.x + " Ship.pos.z = " + rFantom.Ship.pos.z);
//				trace("pchar.Ship.pos.x = " + pchar.Ship.pos.x + " pchar.Ship.pos.z = " + pchar.Ship.pos.z);
								
				//ugeen --> установка возможных ситуаций в каюте кэпа при абордаже - взрыв или эпидемия
				if(j != 0 && bSeaCanGenerateShipSituation && iEncounterType != ENCOUNTER_TYPE_ALONE && sti(pchar.CanGenerateShipSituation) == 1)  // флагманы и одиночки исключаем
				{
					trace("bSeaCanGenerateShipSituation = " + bSeaCanGenerateShipSituation);
					if (CheckAttribute(rFantom, "hunter")) // ОЗГ или ДУ
					{
						if(rFantom.hunter == "hunter") Fantom_SetQuestSitiation(rFantom, "hunter");
						else Fantom_SetQuestSitiation(rFantom, "pirate");	
					}
					else
					{	
						if(sti(rFantom.Nation) == PIRATE) Fantom_SetQuestSitiation(rFantom, "pirate");	
						else
						{
							if(rFantom.EncType == "trade") // военники в составе торговых караванов
							{
								if (CheckAttribute(rFantom, "Ship.Mode") && rFantom.Ship.Mode != "trade")
								{
									Fantom_SetQuestSitiation(rFantom, "war"); // торгаши отдельно
								}	
							}
							else Fantom_SetQuestSitiation(rFantom, "war"); // военные корабли - патрули и пр.
						}
					}
				}				
				if(bSeaCanGenerateShipSituation && sti(pchar.CanGenerateShipSituation) == 1)
				{
					if (iEncounterType == ENCOUNTER_TYPE_MERCHANT_SMALL || iEncounterType == ENCOUNTER_TYPE_MERCHANT_MEDIUM) // а вот тут торгаши - устанавливаем для флотилии из одного-двух кораблей
					{
						Fantom_SetQuestSitiation(rFantom, "trade");
					}				
				}	
				// <-- ugeen
				Fantom_SetCannons(rFantom, rEncounter.Type);
				Fantom_SetSails(rFantom, rEncounter.Type);
                // boal <--
				rFantom.SeaAI.Group.Name = sGName;
				rFantom.Experience = 0;
				rFantom.Skill.FreeSkill = 0;
				
				Fantom_SetDamage(rFantom, rEncounter.Type);

				//rFantom.Features.GeraldSails = false;  // код от к3, весьмя страннй, тк при выгрузке в Ship_Add2Sea всем тупо пробивается труе :)
				//if (CheckAttribute(rEncounter, "GeraldSails")) { rFantom.Features.GeraldSails = sti(rEncounter.GeraldSails); }

				// boal герб на флагман -->
				DeleteAttribute(rFantom, "ShipSails.gerald_name");   // мог быть с того раза
				if (j == 0 || GetCharacterShipClass(rFantom) == 1)
				{
					SetRandGeraldSail(rFantom, sti(rFantom.Nation));
				}
                // boal герб на флагман <--
                
				// add fantom
				Group_AddCharacter(sGName, rFantom.id);
				
				// add to sea
				Ship_Add2Sea(iFantomIndex, 0, rEncounter.Type, true);
			}
		}
	}
	//}
	
	ReloadProgressUpdate();

	// set tasks 2 all groups
	for (i=0; i<GetArraySize(&sTaskList)-2; i++)
	{
		string sGroupID = sTaskList[i];

		rGroup = Group_GetGroupByID(sGroupID);
		
		// set task 
		switch (sti(rGroup.Task))
		{
			case AITASK_RUNAWAY:
				Group_SetTaskRunAway(sGroupID, rGroup.Task.Target);
			break;
			case AITASK_ATTACK:
				Group_SetTaskAttack(sGroupID, rGroup.Task.Target);
			break;
			case AITASK_MOVE:
				if (CheckAttribute(rGroup, "Task.Target.Pos"))
				{
					Group_SetTaskMove(sGroupID, stf(rGroup.Task.Target.Pos.x), stf(rGroup.Task.Target.Pos.z));
				}
				else
				{
					x = 10000.0 * sin(stf(rGroup.Pos.ay));
					z = 10000.0 * cos(stf(rGroup.Pos.ay));
					Group_SetTaskMove(sGName, x, z);
				}
			break;
		}
		
		if(!CheckAttribute(rGroup,"EmptyFantom"))
		{
			rCharacter = Group_GetGroupCommanderR(rGroup);
			int iRelation = GetRelation(nMainCharacterIndex, sti(rCharacter.index));

			// set relations to all characters in this group
			int qq = 0;
			while (true)
			{
				int iCharacterIndex = Group_GetCharacterIndexR(rGroup, qq); qq++;
				if (iCharacterIndex < 0) { break; }
				SetCharacterRelationBoth(iCharacterIndex, nMainCharacterIndex, iRelation);
			}
		}	
		
	}	

	// update AISea 
	AISea.DistanceBetweenGroupShips = 250.0;
	AISea.isDone = "";
	
	InitBattleInterface();							ReloadProgressUpdate();
	StartBattleInterface();							ReloadProgressUpdate();
	RefreshBattleInterface();						ReloadProgressUpdate();
	
	/*CreateEntity(&SeaOperator, "SEA_OPERATOR");
	LayerAddObject(SEA_EXECUTE, &SeaOperator, -1);
	LayerAddObject(SEA_REALIZE, &SeaOperator, 3);*/

	SendMessage(&Telescope, "leee", MSG_TELESCOPE_INIT_ARRAYS, &Nations, &RealShips, &Goods);

	PostEvent(SHIP_CHECK_RELOAD_ENABLE, 1);
	
	SetSchemeForSea();								ReloadProgressUpdate();
	sSeaStartMusicName = oldMusicName;

	iRDTSC = RDTSC_E(iRDTSC);
	//Trace("SeaLogin RDTSC = " + iRDTSC);
	//Trace("iNumFantomShips = " + iNumFantomShips);

	pchar.space_press = "0";
	DeleteAttribute(pchar, "SkipEshipIndex");// boal
	
	pchar.DirSailFail = ""; // mitrokosta удалить флаг фейла директсаила
	
	/*if (checkattribute(pchar, "sneak"))
	{
		string sgroup = pchar.sneak.group;
		LAi_group_NotFightPlayerVSGroup(sgroup);
		deleteAttribute(pchar, "sneak");
	}*/
	
	PostEvent("Sea_FirstInit", 1);
}

void Sea_LoginGroup(string sGroupID)
{
	if (!isEntity(&Sea)) { Trace("Error: Sea_LoginGroup sGroupID = " + sGroupID + ", but Sea is not active!"); return; }

	if (Group_FindGroup(sGroupID) < 0)
	{
		Trace("Not find group '" + sGroupID + "' in groups massive, but login try spotted");
		return;
	}

	ref rGroup = Group_GetGroupByID(sGroupID); 
	if (!CheckAttribute(rGroup, "Quest"))			{ Trace("Error: Sea_LoginGroup sGroupID = " + sGroupID + ", but group doesn't contain any quest ships!"); return; }
	if (CheckAttribute(rGroup, "AlreadyLoaded"))	{ Trace("Error: Group sGroupID = " + sGroupID + ", already loaded... check for duplicate group login"); return; }
	if (Group_GetGroupCommanderIndexR(rGroup) < 0)
	{
		Group_DeleteAtEnd(sGroupID);
		return;
	}

	aref arQuestShips; makearef(arQuestShips, rGroup.Quest);

	int iNumQuestShips = GetAttributesNum(arQuestShips);
	if (iNumQuestShips == 0) { return; }

	float x, z, ay; x = 0.0; z = 0.0; ay = 0.0;

	// find group position
	if (CheckAttribute(rGroup, "location") && CheckAttribute(rGroup, "location.group") && rGroup.location != "none")
	{
		string sLocationGroup = rGroup.location.group;
		string sLocationLocator = rGroup.location.locator;

		ref rIsland = GetIslandByID(rGroup.location);

		string sTst = sLocationGroup + "." + sLocationLocator + ".x";
		if (CheckAttribute(rIsland, sTst))
		{
			x = stf(rIsland.(sLocationGroup).(sLocationLocator).x);
			z = stf(rIsland.(sLocationGroup).(sLocationLocator).z);
			ay = stf(rIsland.(sLocationGroup).(sLocationLocator).ay);
		}
		else
		{
			x = 0.0; z = 0.0; ay = 0.0;
			Trace("ERR: Group " + sGroupID + ", Island " + rGroup.location);
			Trace("ERR: Find locators Group " + sLocationGroup + ", Locator " + sLocationLocator);
		}
	}
	else
	{
		if (CheckAttribute(rGroup, "Pos"))
		{
			x = stf(rGroup.Pos.x);
			z = stf(rGroup.Pos.z);
			ay = stf(rGroup.Pos.ay);
		}
		else
		{
			Trace("Error: Sea_LoginGroup sGroupID = " + sGroupID + ", I can't find any locators or position for this group, maybe you can check this???");
		}
	}
    // 1.2.3 - кильваторный строй, вместо каши в  Group_SetPursuitGroup -->
    if (CheckAttribute(rGroup, "location.neargroup"))
	{
  		float fAngle = frnd() * PIm2;
  		ay = 500.0 + rand(700);
  		//Log_testInfo("Group_SetPursuitGroup " + NullCharacter.Login.PlayerGroup.x + " " + NullCharacter.Login.PlayerGroup.z + " " + NullCharacter.Login.PlayerGroup.ay + " fAngle " + fAngle);
  		x  = stf(NullCharacter.Login.PlayerGroup.x) + ay*cos(fAngle); // окружность радиуса 500
  		z  = stf(NullCharacter.Login.PlayerGroup.z) + ay*sin(fAngle);
  		ay = stf(NullCharacter.Login.PlayerGroup.ay) + fAngle;
  		//NullCharacter.Login.PlayerGroup.ay = stf(NullCharacter.Login.PlayerGroup.ay) + frnd() * PI;
	}
	// 1.2.3 - кильваторный строй, вместо каши в  Group_SetPursuitGroup   <--
	// set group position
	Group_SetXZ_AY(sGroupID, x, z, ay);
	Trace("Set enemy encounter group : " + sGroupID + ", x = " + x + ", z = " + z + ", ay = " + ay);
	
	// set group commander
	ref rGroupCommander = Group_GetGroupCommander(sGroupID);
	// update commander for SEA AI
	if(sti(rGroupCommander.index) <= 0)
	{
		return;
	}
	Group_SetGroupCommander(sGroupID, rGroupCommander.id);  // странная проверка и назначение, но было и пусть будет

	// set location near 
	/*if (CheckAttribute(rGroup, "location.neargroup"))
	{
		Group_SetPursuitGroup(sGroupID, rGroup.location.neargroup);
	} */
	
	// load group ships
	int iNumDeadCharacters = 0;
	for (int i=0; i<iNumQuestShips; i++) //? homo;
	{
		aref arShip;
		
		arShip = GetAttributeN(arQuestShips, i);
		int itmp = GetCharacterIndex(GetAttributeValue(arShip));  // homo fix 29/09/06
		if (itmp != -1)
		{
    		ref rCharacter = GetCharacter(itmp);// bad homo
    		if (!CheckAttribute(rCharacter, "index") || rCharacter.index == "none") // boal for slib
    		{
    			continue;
    		}
    		int iCharacterIndex = sti(rCharacter.index);

    		if(iCharacterIndex <= 0)
    		{
    			continue;
    		}

    		if (LAi_IsDead(rCharacter))
    		{
    			iNumDeadCharacters++; continue;
    		}
    		if (iCharacterIndex == nMainCharacterIndex)
    		{
    			Trace("Error: You assigned main character to quest group... This is a error!");
    			continue;
    		}

    		rCharacter.SeaAI.Group.Name = sGroupID;
    		if (CheckAttribute(rGroup, "location"))
    		{
            	rCharacter.location = rGroup.location;  // установка НПС лацации
            }
    		Ship_Add2Sea(sti(rCharacter.index), bFromCoast, "", true);

    		ReloadProgressUpdate();

            // перевел все в группу boal 23/06/06 -->
    		/*int iCompanionsNum = GetCompanionQuantity(rCharacter);
    		//int iGroupIndex = Group_FindGroup(sGroupID);
    		if (iCompanionsNum > 1)
    		{
    			int cn = -1;
    			for(int k = 1; k < COMPANION_MAX; k++)
    			{
    				cn = GetCompanionIndex(rCharacter, k);
    				if(cn != -1)
    				{
    					rCharacter = &characters[cn];

    					rCharacter.SeaAI.Group.Name = sGroupID;

    					Ship_Add2Sea(sti(rCharacter.index), bFromCoast, "");

    					ReloadProgressUpdate();
    				}
    			}
    		} */
    		// <--
        }//<- homo fix
	}

	rGroup.AlreadyLoaded = "";

	if (iNumDeadCharacters == iNumQuestShips)
	{
		Trace("Warn: I am automatic delete group '" + sGroupID +"', because it's empty");
		Group_DeleteAtEnd(sGroupID);
		//Group_DeleteGroup(sGroupID);
		return;
	}

	bSeaQuestGroupHere = true;

	Sea_AddGroup2TaskList(sGroupID);
}

void Sea_FirstInit()
{ 
	bSeaLoaded = true;
	RefreshBattleInterface();
	if( SeaCameras.Camera == "SeaDeckCamera" ) {
		Sailors.IsOnDeck = "1";
	}
	CreateEntity(&Seafoam,"Seafoam");//				ReloadProgressUpdate();
	LayerAddObject(SEA_EXECUTE, &Seafoam, -1);
	LayerAddObject(SEA_REALIZE, &Seafoam, -1);
	if (Whr_IsStorm()) { Seafoam.storm = "true"; }
	
	QuestsCheck(); // boal 26/05/06 тут ему место
}

void Sea_Reload()
{
	DelEventHandler("Sea_Reload", "Sea_Reload");

	object Login;

	Login.PlayerGroup.ay = 0.0;
	Login.PlayerGroup.x = 0.0;
	Login.PlayerGroup.y = 0.0;
	Login.PlayerGroup.z = 0.0;
	Login.Island = pchar.location;

	SeaLogin(&Login);	
}

void Sea_ReloadStart()
{
	if (!bSeaActive) { return; }
	ShipsInit();	
	//characters[1].ship.type = GenerateShip(SHIP_barque, 1);
	DeleteSeaEnvironment();
	SetEventHandler("Sea_Reload", "Sea_Reload", 0);
	PostEvent("Sea_Reload", 1);
}


void Sea_Save()
{
	DeleteAttribute(&oSeaSave, "");

	SendMessage(&AISea, "l", AI_MESSAGE_SEASAVE);
}

// boal -->
float SetMaxSeaHeight(int islandIdx)
{
	if (!bSeaActive) return   6.0; // ситуция когда нет моря, нет координат pchar.Ship.Pos.x
	if (bStorm) return 200.0;
	string sIslandID = Islands[islandIdx].id;

	float  fMaxViewDist;
    int    i, iQty;
	
	if (CheckAttribute(Islands[islandIdx], "MaxSeaHeight")) return stf(Islands[islandIdx].MaxSeaHeight);

	// поиск мин расстояния до городов по фортам -->
    //fMaxViewDist = 2000; // послужит временно дистанцией
	
	aref arReloadLoc, arLocator;	
	makearef(arReloadLoc, Islands[islandIdx].reload);
	string  sLabel;
	iQty = GetAttributesNum(arReloadLoc); 
    //Log_TestInfo("Sea.MaxSeaHeight " + Sea.MaxSeaHeight);
	for (i=0; i<iQty; i++)
	{
		arLocator = GetAttributeN(arReloadLoc, i);
		sLabel = arLocator.label;

		//расстояние до бухт и маяков
		if (findsubstr(sLabel, "Shore" , 0) != -1 || findsubstr(sLabel, "Mayak" , 0) != -1)
		{
			if (CheckAttribute(pchar, "Ship.Pos.x") && CheckAttribute(arLocator, "x"))  // fix кривых локаторов у острова, правка должна быть в модели to_do
			{
				if (GetDistance2D(stf(pchar.Ship.Pos.x), stf(pchar.Ship.Pos.z), stf(arLocator.x), stf(arLocator.z)) < 1500)
					return 6.0;
			}
			else
			{
				trace("Error: проблема определения SetMaxSeaHeight для " + sLabel);
			}
		}
		//расстояние до форта
		if (findsubstr(sLabel, "Fort" , 0) != -1)  
		{
			if (CheckAttribute(pchar, "Ship.Pos.x") && CheckAttribute(arLocator, "x"))  // fix кривых локаторов у острова, правка должна быть в модели to_do
			{
				if (GetDistance2D(stf(pchar.Ship.Pos.x), stf(pchar.Ship.Pos.z), stf(arLocator.x), stf(arLocator.z)) < 1700)
					return 6.0;
			}
			else
			{
				trace("Error: проблема определения SetMaxSeaHeight для " + sLabel);
			}				
		}
		//расстояние до порта
		if (findsubstr(sLabel, "Port" , 0) != -1)
		{
			if (CheckAttribute(pchar, "Ship.Pos.x") && CheckAttribute(arLocator, "x"))  // fix кривых локаторов у острова, правка должна быть в модели to_do
			{
				if (GetDistance2D(stf(pchar.Ship.Pos.x), stf(pchar.Ship.Pos.z), stf(arLocator.x), stf(arLocator.z)) < 2000)
					return 6.0;
			}
			else
			{
				trace("Error: проблема определения SetMaxSeaHeight для " + sLabel);
			}
		}
	}
    //Log_TestInfo("Sea.MaxSeaHeight Max 200");
	return 200.0;
}
// boal <--
void Sea_LoadIsland(string sIslandID)
{
	bIsFortAtIsland = false;
	if (sIslandID == "") { return; }

	int iIslandIndex = FindIsland(sIslandID);
	if (iIslandIndex != -1 && Islands[iIslandIndex].visible == true)
	{
		// boal -->
		float  fMaxViewDist;
        Sea.MaxSeaHeight = SetMaxSeaHeight(iIslandIndex); // тут нужно для загрузки игры из сайва, для нормального перехода не работает, тк ГГ еще не в море, нет коорд
        Log_TestInfo("Sea_LoadIsland Sea.MaxSeaHeight " + Sea.MaxSeaHeight);
		// boal <--
		CreateEntity(&Island, "Island");
		Island.LightingPath = GetLightingPath();
		Island.dynamicLightsOn = DYNAMIC_LIGHTS;
		Island.ImmersionDistance = Islands[iIslandIndex].ImmersionDistance;			// distance = fRadius * ImmersionDistance, from island begin immersion
		Island.ImmersionDepth = Islands[iIslandIndex].ImmersionDepth;			// immersion depth = (Distance2Camera / (fRadius * ImmersionDistance) - 1.0) * ImmersionDepth
		string sTexturePath = "islands\" + Islands[iIslandIndex].TexturePath + "\";
		SetTexturePath(0, sTexturePath);
		Island.FogDensity = Weather.Fog.IslandDensity;
		// трава на остров
		if( CheckAttribute(&Islands[iIslandIndex],"jungle") )
		{
			float fJungleScale = 10.0;
			if( CheckAttribute(&Islands[iIslandIndex],"jungle.scale") )
			{
				fJungleScale = stf(Islands[iIslandIndex].jungle.scale);
			}
			CreateGrass("resource\models\islands\"+ Islands[iIslandIndex].id +"\"+ Islands[iIslandIndex].jungle.patch + ".grs", "Grass\"+Islands[iIslandIndex].jungle.texture+".tga", fJungleScale, 20.0, 200.0, 100.0, 1000.0, 0.6);
		}
/*		
		if (MOD_BETTATESTMODE == "On")
		{
			CreateEntity(&SeaLighter, "lighter");  //eddy. не надо это пока коментить, это и есть Lighter. ошибку дает, если в локлайтере лоадинг == 0, т.к. в этом случае тулза не инитится в движке.
		}
*/		
		SendMessage(&SeaLighter, "ss", "ModelsPath", Islands[iIslandIndex].filespath.models);
		SendMessage(&SeaLighter, "ss", "LightPath", GetLightingPath());

		SendMessage(&Island, "lsss", MSG_ISLAND_LOAD_GEO, "islands", Islands[iIslandIndex].filespath.models, Islands[iIslandIndex].model);
		LayerAddObject(SEA_REALIZE, &Island, 4);
		LayerAddObject(MAST_ISLAND_TRACE, &Island, 1);
		LayerAddObject(SUN_TRACE, &Island, 1);
		fMaxViewDist = 6000.0;
		if(CheckAttribute(&Islands[iIslandIndex], "maxviewdist"))
		{
			fMaxViewDist = stf(Islands[iIslandIndex].maxviewdist);
		}
		SendMessage(&Island, "lf", MSG_MODEL_SET_MAX_VIEW_DIST, fMaxViewDist);

		CreateEntity(&IslandReflModel, "MODELR");
		string sReflModel = Islands[iIslandIndex].filespath.models + "\" + Islands[iIslandIndex].refl_model;
		SendMessage(&IslandReflModel, "ls", MSG_MODEL_SET_LIGHT_PATH, GetLightingPath());
		SendMessage(&IslandReflModel, "ls", MSG_MODEL_LOAD_GEO, sReflModel);
		SendMessage(&IslandReflModel, "lllf", MSG_MODEL_SET_FOG, 1, 1, stf(Weather.Fog.IslandDensity));
		LayerAddObject(SEA_REFLECTION2, &IslandReflModel, -1);
		SendMessage(&SeaLighter, "ssi", "AddModel", Islands[iIslandIndex].refl_model, &IslandReflModel);
		
		// Warship Вынес в метод - создание освещения маяка
		Sea_CreateLighthouse(sIslandID);
		
		bIslandLoaded = true;
		SendMessage(&SeaLocatorShow, "a", &Islands[iIslandIndex]);
		Fort_Login(iIslandIndex);	
		SetTexturePath(0, "");

		CreateCoastFoamEnvironment(sIslandID, SEA_EXECUTE, SEA_REALIZE);
		//eddy. запишем в переменные координаты форта
		aref arReloadFort;	
		makearef(arReloadFort, Islands[iIslandIndex].reload.l2);
		if (!CheckAttribute(arReloadFort, "colonyname")) return;
		string sTest = arReloadFort.colonyname + " Fort";
		if (arReloadFort.label == sTest && CheckAttribute(arReloadFort, "x") && CheckAttribute(arReloadFort, "z"))
		{
			fFort_x = stf(arReloadFort.x);
			fFort_z = stf(arReloadFort.z);
			int iColony = FindColony(arReloadFort.colonyname);
			iFortNation = sti(colonies[iColony].nation);
			iFortCommander = sti(colonies[iColony].commanderIdx);
			//следить за фортом только, если он жив
			if (!CheckAttribute(&characters[iFortCommander], "Fort.Mode") || sti(characters[iFortCommander].Fort.Mode) != FORT_DEAD)
			{
				bIsFortAtIsland = true; 
			}
		}
	}
}

// Warship Метод по созданию освещения маяков в море
void Sea_CreateLighthouse(String _islandID)
{
	ref islandRef;
	int islandIndex = FindIsland(_islandID);
	
	String lighthouseLightModelName;
	
	if(islandIndex == -1) return;
	
	islandRef = &Islands[islandIndex];

	//--> eddy. да будет свет на маяке
	if(CheckAttribute(&islandRef, "mayak"))
	{
		CreateEntity(&sLightModel, "MODELR");
		
		if(isDay())
		{
			lighthouseLightModelName = islandRef.filespath.models + "\" + islandRef.mayak.model_day;
		}
		else
		{
			lighthouseLightModelName = islandRef.filespath.models + "\" + islandRef.mayak.model_night;
		}
		
		//SendMessage(&sLightModel, "ls", MSG_MODEL_SET_TECHNIQUE, "LocVisRays");
		SendMessage(&sLightModel, "ls", MSG_MODEL_LOAD_GEO, lighthouseLightModelName);
		SendMessage(&island, "li", MSG_ISLAND_ADD_FORT,  &sLightModel); // &island - обьект-остров (сущность), а не элемент массива Islands[]
		SendMessage(SeaLighter, "ssi", "AddModel", islandRef.mayak.model_night, &sLightModel);
	}
	//<-- eddy. да будет свет на маяке
	
	// Warship Новое - создание света маяка -->
	// Атрибут маяка у острова тут не проверяется - он есть только у маяка Ямайки
	if(_islandID == "Jamaica" || _islandID == "Cuba1" || _islandID == "Cuba2")
	{
		if(IsEntity(lighthouseLightModel))
		{
			DeleteClass(&lighthouseLightModel);
		}
		
		if(!IsDay())
		{
			CreateEntity(&lighthouseLightModel, "MODELR");
			// Коммент - текстура для модельки будет браться из "RESOURCE\TEXTURES\" + DIRPATH и никак это не исправить :(
			// В общем, текстура должна лежать в той же папке, что и модель, только в каталоге "TEXTURES"
			//SendMessage(&lighthouseLightModel, "ls", MSG_MODEL_SET_DIRPATH, "");
			SendMessage(&lighthouseLightModel, "ls", MSG_MODEL_LOAD_GEO, "lighthouse_volumeLight");
			SendMessage(&lighthouseLightModel, "ls", MSG_MODEL_SET_TECHNIQUE, "LighthouseLight");
			LayerAddObject(SEA_EXECUTE, &lighthouseLightModel, ITEMS_LAYER);
			LayerAddObject(SEA_REALIZE, &lighthouseLightModel, ITEMS_LAYER);
			
			if(_islandID == "Jamaica")
			{
				SendMessage(&lighthouseLightModel, "lffffffffffff", MSG_MODEL_SET_POSITION, 3000.0, 24.5, -1679.1, 1, 0, 0, 0, 1, 0, 0, 0, 1);
			}
			
			if(_islandID == "Cuba1")
			{
				// TO_DO Крутануть его - криво сейчас
				SendMessage(&lighthouseLightModel, "lffffffffffff", MSG_MODEL_SET_POSITION, 627.0, 24.0, -2170.5, 1, 0, 0, 0, 1, 0, 0, 0, 1);
			}
			
			if(_islandID == "Cuba2")
			{
				SendMessage(&lighthouseLightModel, "lffffffffffff", MSG_MODEL_SET_POSITION, -413.0, 65.5, 815.1, 1, 0, 0, 0, 1, 0, 0, 0, 1);
			}
		}
	}
	// <-- создание света маяка
}

bool bSeaLoad = false;

void Sea_Load()
{
	bSeaLoad = true;
	
	CreateSeaEnvironment();	
	// login island if exist
	Sea_LoadIsland(AISea.Island);	
	
	SendMessage(&AISea, "l", AI_MESSAGE_SEALOAD);		
	SendMessage(&Telescope, "leee", MSG_TELESCOPE_INIT_ARRAYS, &Nations, &RealShips, &Goods);	
		
	PostEvent(SHIP_CHECK_RELOAD_ENABLE, 1);	
	SetSchemeForSea();
	PostEvent("Sea_FirstInit", 1);

	DeleteAttribute(&oSeaSave, "");
	bSeaLoad = false;
	
	InitBattleInterface();
	StartBattleInterface();
	RefreshBattleInterface();					
}

ref SeaLoad_GetPointer()
{
	string sType = GetEventData();
	int iIndex = GetEventData();
	
	switch (sType)
	{
		case "character":
			makeref(rSeaLoadResult, Characters[iIndex]);
		break;
		case "ship":
			makeref(rSeaLoadResult, RealShips[iIndex]);
		break;
		case "seacameras":
			makeref(rSeaLoadResult, SeaCameras);
		break;
		case "seasave":
			makeref(rSeaLoadResult, oSeaSave);
		break;
	}
	return rSeaLoadResult;
}

void Sea_LoginGroupCurrentSea(string sGroupID)
{
	if (!isEntity(&Sea)) { Trace("Error: Sea_LoginGroup sGroupID = " + sGroupID + ", but Sea is not active!"); return; }

	if (Group_FindGroup(sGroupID) < 0)
	{
		Trace("Not find group '" + sGroupID + "' in groups massive, but login try spotted");
		return;
	}

	ref rGroup = Group_GetGroupByID(sGroupID); 
	
	if (!CheckAttribute(rGroup, "Quest"))			{ Trace("Error: Sea_LoginGroup sGroupID = " + sGroupID + ", but group doesn't contain any quest ships!"); return; }
	if (CheckAttribute(rGroup, "AlreadyLoaded"))	{ Trace("Error: Group sGroupID = " + sGroupID + ", already loaded... check for duplicate group login"); return; }
	if (Group_GetGroupCommanderIndexR(rGroup) < 0)
	{
		Group_DeleteAtEnd(sGroupID);
		return;
	}

	aref arQuestShips; makearef(arQuestShips, rGroup.Quest);

	int iNumQuestShips = GetAttributesNum(arQuestShips);
	
	if (iNumQuestShips == 0) { return; }

	float x, z, ay; x = 0.0; z = 0.0; ay = 0.0;

	// find group position
	if (CheckAttribute(rGroup, "location") && CheckAttribute(rGroup, "location.group") && rGroup.location != "none")
	{
		string sLocationGroup = rGroup.location.group;
		string sLocationLocator = rGroup.location.locator;

		ref rIsland = GetIslandByID(rGroup.location);

		string sTst = sLocationGroup + "." + sLocationLocator + ".x";
		if (CheckAttribute(rIsland, sTst))
		{
			x = stf(rIsland.(sLocationGroup).(sLocationLocator).x);
			z = stf(rIsland.(sLocationGroup).(sLocationLocator).z);
			ay = stf(rIsland.(sLocationGroup).(sLocationLocator).ay);
		}
		else
		{
			x = 0.0; z = 0.0; ay = 0.0;
			Trace("ERR: Group " + sGroupID + ", Island " + rGroup.location);
			Trace("ERR: Find locators Group " + sLocationGroup + ", Locator " + sLocationLocator);
		}
	}
	else
	{
		if (CheckAttribute(rGroup, "Pos"))
		{
			x = stf(rGroup.Pos.x);
			z = stf(rGroup.Pos.z);
			ay = stf(rGroup.Pos.ay);
		}
		else
		{
			Trace("Error: Sea_LoginGroup sGroupID = " + sGroupID + ", I can't find any locators or position for this group, maybe you can check this???");
		}
	}
	
	trace("after find group position");
	

	float fAngle = frnd() * PIm2;	// угол
	float d_ay = 500.0 + rand(300); // дистанция
	
	ref mc = GetMainCharacter();		
	if (CheckAttribute(mc, "Ship.pos.x"))	// отосительно позиции флагмана ГГ
	{
		x  = stf(mc.Ship.pos.x); 
		z  = stf(mc.Ship.pos.z);
		ay = stf(mc.Ship.Ang.y) + fAngle;		
	}
	else
	{
		x  = stf(NullCharacter.Login.PlayerGroup.x); 
		z  = stf(NullCharacter.Login.PlayerGroup.z);
		ay = stf(NullCharacter.Login.PlayerGroup.ay) + fAngle;		
	}		
	float d_cos	= 	d_ay * cos(fAngle);
	float d_sin	= 	d_ay * sin(fAngle);
	
	float signX		=	1.0;
	float signZ		= 	1.0; 		
	float d_x		=	1.0; 
	float d_z 		= 	1.0;
	
	if(x < 0.0)
	{
		d_x = -1.0;
		if(d_cos > 0) signX = -1.0;
	}
	else
	{
		if(d_cos < 0) signX = -1.0;
	}
	
	if(z < 0.0)
	{
		d_z = -1.0;
		if(d_sin > 0) signZ = -1.0;
	}
	else
	{
		if(d_sin < 0) signZ = -1.0;
	}
					
	x += signX * d_cos + d_x * (500 + rand(300));
	z += signZ * d_sin + d_z * (500 + rand(300));
	
	trace("Group_SetPursuitGroup x: " + NullCharacter.Login.PlayerGroup.x + " z:" + NullCharacter.Login.PlayerGroup.z + " ay:" + NullCharacter.Login.PlayerGroup.ay + " fAngle " + fAngle);
	trace("ship(x,z, ay)= "+pchar.Ship.pos.x +", "+pchar.Ship.pos.z +", "+ pchar.Ship.Ang.y + ", "+ d_ay); 		

	// set group position
	Group_SetXZ_AY(sGroupID, x, z, ay);
	Trace("Set enemy encounter group : " + sGroupID + ", x = " + x + ", z = " + z + ", ay = " + ay);
	
	// set group commander
	ref rGroupCommander = Group_GetGroupCommander(sGroupID);
	// update commander for SEA AI
	if(sti(rGroupCommander.index) <= 0)
	{
		return;
	}
	Group_SetGroupCommander(sGroupID, rGroupCommander.id);  // странная проверка и назначение, но было и пусть будет

	// load group ships
	int iNumDeadCharacters = 0;
	for (int i=0; i<iNumQuestShips; i++)
	{
		aref arShip;
		
		arShip = GetAttributeN(arQuestShips, i);
		int itmp = GetCharacterIndex(GetAttributeValue(arShip));  // homo fix 29/09/06
		if (itmp != -1)
		{
    		ref rCharacter = GetCharacter(itmp);// bad homo
    		if (!CheckAttribute(rCharacter, "index") || rCharacter.index == "none") // boal for slib
    		{
    			continue;
    		}
    		int iCharacterIndex = sti(rCharacter.index);

    		if(iCharacterIndex <= 0)
    		{
    			continue;
    		}

    		if (LAi_IsDead(rCharacter))
    		{
    			iNumDeadCharacters++; continue;
    		}
    		if (iCharacterIndex == nMainCharacterIndex)
    		{
    			Trace("Error: You assigned main character to quest group... This is a error!");
    			continue;
    		}

    		rCharacter.SeaAI.Group.Name = sGroupID;
    		if (CheckAttribute(rGroup, "location"))
    		{
            	rCharacter.location = rGroup.location;  // установка НПС лацации
            }
    		Ship_Add2Sea(sti(rCharacter.index), bFromCoast, "", false);
        }
	}

	rGroup.AlreadyLoaded = "";

	if (iNumDeadCharacters == iNumQuestShips)
	{
		Trace("Warn: I am automatic delete group '" + sGroupID +"', because it's empty");
		Group_DeleteAtEnd(sGroupID);
		return;
	}

	bSeaQuestGroupHere = true;
	Sea_AddGroup2TaskList(sGroupID);
	UpdateRelations();
	RefreshBattleInterface();
}

