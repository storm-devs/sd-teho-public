// BOAL 07.09.03  Mods on_off mode
// здесь и далее ник boal - это разработческий ник ALexusB

#define VERSION_NUMBER1       "Корсары: Каждому Свое  " // Корсары: КС modding base #1
#define VERSION_NUMBER2       "ver. 1.7.3 (15.04.21) x64"
#define VERSION_NUMBER3       "BlackMark.bz"

#define VERSION_NUM      99940  // текущий номер
#define VERSION_NUM_PRE  99940  // последний совместмый

//Сайт: http://seadogs.4fans.org
#define VERSION_WWW     "http://www.blackmark.bz"

// Show special message for test game statment
#define MOD_BETTATESTMODE			"On"  // On -DEV version; Test - TST ver; Off - relize

// глобальные строковые переменные
String sGlobalTemp;
String sTotalTemp;
string sNrvParol, sRvdParol;

// две глобальные целочисленные переменные
int iGlobalTemp, iTotalTemp;

// quest.c bool    bQuestCheckProcessFreeze = false; // заморозка квестов

// запрет всех случаек на суше (офицеры и клады тоже)
bool    bDisableLandEncounters = false;
// запрет жать ф2
bool    bDisableCharacterMenu  = false;
// флаг - игрок читер
bool    bPlayerIsCheater =  false;  // на перспективу, патчем
// режим супер читов
bool    bBettaTestMode = true; // в релизе убрать!!!!!!!!!!!!!
// показывать quest_reaction Log
bool    bQuestLogShow  = false;
// показывать инфу по балансу
bool    bExpLogShow    = false;
// всегда сдаются капитаны - отладка
bool    TestRansackCaptain = false;
// показ локаторов
bool    bLocatorShow  = false;
// Не жрать, нет крыс
bool    bNoEatNoRats  = false;
// Живой мир на паузе: губер не переезжает от времени, нации не объявляют войну и мир, эскадры не берут город себе, город нельзя взять себе (даже с патентом)
bool    bWorldAlivePause      = true;
// пауза метро
bool bPauseContrabandMetro = false;
// лог для ПГГ
bool bPGGLogShow = false;
// флаг генерации монстров
bool bMonstersGen = false;
// флаг генерации сухопутных энкаунтеров
bool bLandEncountersGen = true;
// флаг в сундуке
bool bMainCharacterInBox = false;
// флаг в огне
bool bMainCharacterInFire = false;
// главное меню
bool bMainMenu = false;
//загрузка начала игры
bool startGameWeather = false;
// отображение статусной инфы у кораблей в море и у противника на суше
bool bDrawBars = true;
// отправление полученных ачивок в стим; для внутренних тестов устанавливать в false !!!
bool bSteamAchievements	= false;
// дополнительный контент, для внутренних тестов ставим в true
bool bAddonContent = true;

// --> резервные глобальные переменные на всякий случай
bool bGlobalVar1 = false;
bool bGlobalVar2 = false;
bool bGlobalVar3 = false;
bool bGlobalVar4 = false;
bool bGlobalVar5 = false;

#define BI_COMPARE_HEIGHT 900
int iGlobalVar1 = BI_COMPARE_HEIGHT;   // забрал ugeen 13.09.2020, нужна для HUD
int iGlobalVar2 = 0;
// <-- резервные глобальные переменные на всякий случай

//int iScriptVersion = 15650;
//int iScriptVersion = 57853; 
int iScriptVersion = 54128;

// дожди и шторма
bool 	bRains						= true;
// пистолеты перезаряжаются без сабли
bool    bRechargePistolOnLine  		= true;  
// упрощение невозможного
bool    bNewCodeOn                	= false;  // упрощение абордажа
// нет сайвов, токо в церкви есть
bool    bHardcoreGame             	= false;
// платный сайв-лоад
//bool    bPayForSaveLoad           = true;
// сохранение в море в боевом режиме
bool	bSeaBattleSave				= true;
// раздел добычи
bool 	bPartitionSet 				= true;

///////////////////////////////////////////////////
//          complexity
//  Next Level rate
int MOD_EXP_RATE           = 10; // это база... + (сложность)
//  complexity of fantom skill
// 1- easy; 2; 3; 4;  5-medium; 6; 7; 8; 9;  10 - hard (please, do not set more 10 or less 1 it mays crash game
// для ККС - уровни сложности 2 - легкий,4,6,8 - средние, 10 - сложный
int MOD_SKILL_ENEMY_RATE   = 4; 


// Killed body clear
#define MOD_DEAD_CLEAR           "On"
#define MOD_DEAD_CLEAR_TIME      100 // in sec.

#define CHAR_ITEMS_WEIGHT        70

#define InstantRepairRATE        65.0

// дистанция до корабля для разговора
#define DistanceToShipTalk        300.0

//#define ShipyardMoneyInit        190000.0
//#define ShipyardMoneyMax         900000.0
//#define ShipyardMoneyAdd         2000

// boal 23.01.2004 доработка 091004 сколь угодно героев -->
int    startHeroType 	= 1;
int    MaxHeroQty		= 4;  // максимальное кол-во ГГ
int    MaxPGGQty		= 10; // максимальное кол-во ПГГ (+2 оставшихся ГГ)
//int    heroFaceId    = 1;
// boal 23.01.2004 <--

int ItemDeadStartCount = 0; // заполняется в itemInit порог для заполения трупов (оптимизация)

#define STARTGAME_YEAR       1654
#define STARTGAME_MONTH      10
#define STARTGAME_DAY        1

// пасхалка Кукурузина
#define FUNY_SHIP_NAME    "Кукурузина"
#define KEY_ENG_LINE	  "uFRklw7Ghww19ywWQ"

int TimeScaleCounter = 0;
// запрет перехода
bool chrDisableReloadToLocation = false;
// для видения форта в АИ шипов
bool bIsFortAtIsland = false;
float fFort_x, fFort_z;
int iFortNation, iFortCommander;
//начало и конец предметов для локаторов item
int ItemsForLocators_start, ItemsForLocators_end;

GetEngineVersion();
//bAddonContent = GetDLCenabled();
/////////////////////////////