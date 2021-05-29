
#include "locations\locations_loader.c"
#include "locations\locations_camera.c"


extern void InitLocations();


native int NativeFindCharacter(ref charactersArray, string id);
native int NativeFindLocation(ref charactersArray, string id);
native int NativeFindLoadCharacter();
native void SetReloadProgressBackImage(string imageName);
native void ReloadProgressStart();
native void ReloadProgressUpdate();
native void ReloadProgressEnd();
native void SystemDelay(int millsec);
native void ExecuteTechnique(string techName);
native string GetNextLineString();
native void SetReloadNextTipsImage();

#libriary "ScriptLocationLibrary"


void LocationInit()
{
	locCameraInit();
	if(LoadSegment("locations\locations_init.c"))
	{
		InitLocations();
		UnloadSegment("locations\locations_init.c");
	}
	locDisableUpdateTime = false;
	locTmpTime = 0.0;
}
/*
void LocationTestProcess()
{
	SetReloadProgressBackImage("Loading\initialization.tga.tx");
	ReloadProgressStart();
	LocationInit();
	Locations_TestAll();
	ReloadProgressEnd();
}
*/

int FindLoadedLocation()
{
	return NativeFindLoadCharacter();
}

bool SetLocatorGroupRadius(ref loc, string grpName, float rad)
{
	return SendMessage(loc, "lsf", MSG_LOCATION_GRP_RADIUS, grpName, rad);
}

bool SetLocatorRadius(ref loc, string grpName, string locName, float rad)
{
	return SendMessage(loc, "lssf", MSG_LOCATION_LOC_RADIUS, grpName, locName, rad);
}


bool VisibleLocatorsGroup(string group, float kRadius, float viewLabelsDist, int a, int r, int g, int b)
{
	
	int i = FindLoadedLocation();
	if(i < 0) return false;
	int color = argb(a, r, g, b);
	return SendMessage(&Locations[i], "lsffl", MSG_LOCATION_VIEWLGROUP, group, kRadius, viewLabelsDist, color);
}

void HideLocatorsGroup(string group)
{
	int i = FindLoadedLocation();
	if(i < 0) return;
	SendMessage(&Locations[i], "ls", MSG_LOCATION_HIDELGROUP, group);
}

bool WaitNight()
{
	return true;
}


bool WaitNightPause(bool paused)
{
	return true;
}

void LocationWaitNihgtEndFadeOut()
{
	bool isFadeIn = GetEventData();
	aref fader = GetEventData();
	if(isFadeIn == false)
	{
		SendMessage(&fader, "lfl", FADER_IN, 1.0, true);
	}
	SetEventHandler("FaderEvent_EndFadeIn", "LocationWaitNihgtEndFadeIn", 0);
	DelEventHandler("FaderEvent_EndFade", "LocationWaitNihgtEndFadeOut");
}

void LocationWaitNihgtEndFadeIn()
{
	bool isFadeIn = GetEventData();
	aref fader = GetEventData();
	if(isFadeIn != false)
	{
		DelEventHandler("FaderEvent_EndFadeIn", "LocationWaitNihgtEndFadeIn");
		int i = FindLoadedLocation();
		if(i >= 0)
		{
			SendMessage(&Locations[i], "ll", MSG_LOCATION_PAUSE, false);
		}
		PostEvent("LocationWaitNihgtEnd", 1);
	}	
}

//navy -->
void LocationMakeClone(string _locId)
{
	ref rOrg, rClone;
	int iOrg, iClone;

	iOrg = FindLocation(_locId);
	iClone = FindLocation("Clone_location");

	makeref(rOrg, Locations[iOrg]);
	makeref(rClone, Locations[iClone]);

	DeleteAttribute(rClone, "");
	CopyAttributes(rClone, rOrg);
	rClone.id = "Clone_location";
	rClone.type = "clone";
	rClone.index = iClone;
//а так не работает... :) проверка только на аттрибут ;)	
//	rClone.habitues = false;
	DeleteAttribute(rClone, "habitues");

	pchar.questTemp.LocationClone = true;
	pchar.questTemp.LocationClone.id = rOrg.id;
}
//navy <--

// Warship -->
// Подключить к локации еще одну модельку
// Ввел доп. проверки в иф, чтобы можно было этим методом "прилеплять" к локации модели еще при инициализации
bool Location_AddNewModel(String _LocID, String _GroupName, String _LocatorName, String _Model, String _Type, String _Tech, int _Level, bool _Now)
{
	int iLoc =  FindLocation(_LocID);
	if(iLoc == -1) return false;
	ref rLoc = &locations[iLoc];
	rLoc.models.(_Type).(_Model) = _Model; // Название модели
	if(_GroupName != "" && _LocatorName != "")
	{
		rLoc.models.(_Type).(_Model).locator.group = _GroupName; // Название группы локаторов, куда грузим модель
		rLoc.models.(_Type).(_Model).locator.name = _LocatorName; // Название локатора, где будет модель
	}
	if(_Tech != "") rLoc.models.(_Type).(_Model).tech = _Tech; // Техника
	if(_Level > 0) rLoc.models.(_Type).(_Model).level = _Level; // Порядок загрузки
	if(_Now) LocLoadModel(rLoc, "models." + _Type + "." +_Model, ""); // Грузим модель динамически!
	return true;
}

// Удалить модель из локации (удалится токо позле перегруза локации)
bool Location_DeleteModel(String _LocID, String sType, String _Model)
{
	int iLoc =  FindLocation(_LocID);
	if(iLoc == -1) return false;
	ref rLoc = &locations[iLoc];
	DeleteAttribute(rLoc, "models." + sType + "." +_Model);
	return true;
}

// Находится ли перс в заданном локаторе?
bool IsCharacterInLocator(ref rChar, string LocGroup, string LocName)
{
	float fx, fy, fz;
	if(GetCharacterPos(rChar, &fx, &fy, &fz))
	{
		if(CheckCurLocator(LocGroup, LocName, fx, fy, fz)) return true;
	}
	return false;
}

bool Location_AddReload(string _LocID, int iNum, string _name, string _go, string _emerge, bool _autoreload, string _label, float _radius)
{
	int iLoc =  FindLocation(_LocID);
	if(iLoc == -1) return false;
	ref rLoc = &locations[iLoc];
	string sNum = "l"+iNum;
	rLoc.reload.(sNum).name = _name;
	rLoc.reload.(sNum).go = _go;
	rLoc.reload.(sNum).emerge = _emerge;
	if(_autoreload)
		rLoc.reload.(sNum).autoreload = "1";
	else
		rLoc.reload.(sNum).autoreload = "0";
	rLoc.reload.(sNum).label = _label;
	rLoc.locators_radius.reload.(_name) = _radius;
	return true;
}
// <-- Warship