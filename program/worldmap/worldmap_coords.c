/*
 * Пересчет игровых координат глобальной карты в реальные (условные) географические координаты Карибского архипелага
 * Ugeen - 12.08.09
 */
//#event_handler("frame", "CheckCoordinateQuest");

#event_handler("EventCoordUpdate", "wdmCoordUpdate");

#define WDM_RealCoordStartX 60 // начало координат по X - градусы западной долготы
#define WDM_RealCoordEndX 85   // конец координат по X - градусы западной долготы
#define WDM_RealCoordStartZ 10 // начало координат по Z - градусы северной широты
#define WDM_RealCoordEndZ 25   // конец координат по Z - градусы северной широты

float fShiftX = 1024.0; // смещение игровых координат по X
float fShiftZ = 1024.0; // смещение игровых координат по Z

float fScaleX = 2048.0;
float fScaleZ = 2048.0;

#define iSecondsX 90000
#define iSecondsZ 54000

string sCurCoordinateQuest = "";

void SetCoordinateQuest(string _sQuest)
{
    SetEventHandler(_sQuest, _sQuest, 0); // Ставим евент
    sCurCoordinateQuest = _sQuest;
}

void CheckCoordinateQuest() // Процессирование всего
{
    PostEvent(sCurCoordinateQuest, 100);
}

void DeleteCoordinateQuest(string _sQuest)
{
    sCurCoordinateQuest = "";
    DelEventHandler(_sQuest, _sQuest); // Удалим евент
}

/*
--> пример использования координатной сетки для квестов  
void CheckQuestCoordinates()
{
    int coordinateDegreeX = 70;
    int coordinateDegreeZ = 15;

    if(IsEntity(&worldMap)) // если на глобальной карте
    {
        Log_SetStringToLog("X : " + GetMapCoordDegreeX(makefloat(worldMap.playerShipX)) + " Z : " + GetMapCoordDegreeZ(makefloat(worldMap.playerShipZ)));
        if( (GetMapCoordDegreeX(makefloat(worldMap.playerShipX)) == coordinateDegreeX) &&
            (GetMapCoordDegreeZ(makefloat(worldMap.playerShipZ)) == coordinateDegreeZ) )
        {
            DeleteCoordinateQuest("CheckQuestCoordinates");
            Log_SetStringToLog("Текущие координаты : " + Map_GetRealCoordZ(makefloat(worldMap.playerShipZ)) + "  " + Map_GetRealCoordX(makefloat(worldMap.playerShipX)));
            Log_SetStringToLog("Достигли искомой точки - 70 гр. з.д. 15 гр. с.ш.");
        }
    }
}
*/

// получить масштаб глобальной карты отосительно режима "море"
int GetSeaToMapScale()
{
    int scale = WDM_MAP_TO_SEA_SCALE;
    if (worldMap.island == "Cuba1" || worldMap.island == "Cuba2" || worldMap.island == "Beliz" || worldMap.island == "SantaCatalina" || worldMap.island == "PortoBello" || worldMap.island == "Cartahena" || worldMap.island == "Maracaibo" || worldMap.island == "Caracas" || worldMap.island == "Cumana")
    {
        scale = 25;
    }
    return scale;
}

float GetSeaShipX(float X)
{
    float zeroX = MakeFloat(worldMap.zeroX);
    int scale = GetSeaToMapScale();
    float ShipX = (X / scale) + zeroX;

    return ShipX;
}

float GetSeaShipZ(float Z)
{
    float zeroZ = MakeFloat(worldMap.zeroZ);
    int scale = GetSeaToMapScale();
    float ShipZ = (Z / scale) + zeroZ;

    return ShipZ;
}

// секунды долготы относительно начала координат (глобальная карта)
int Map_GetRCoordSecondsX(float X)
{
    int iSecX = makeint((fShiftX - X) / fScaleX * iSecondsX);
    return iSecX;
}

// градусы долготы относительно начала координат (глобальная карта)
int Map_GetRCoordDegreeX(float X)
{
    int iDegX = Map_GetRCoordSecondsX(X);
    return makeint(iDegX / 3600.0);
}

// секунды широты относительно начала координат (глобальная карта)
int Map_GetRCoordSecondsZ(float Z)
{
    int iSecZ = makeint((fShiftZ + Z) / fScaleZ * iSecondsZ);
    return iSecZ;
}

// градусы широты относительно начала координат (глобальная карта)
int Map_GetRCoordDegreeZ(float Z)
{
    int iDegZ = Map_GetRCoordSecondsZ(Z);
    return makeint(iDegZ / 3600.0);
}

int GetMapCoordDegreeX(float X)
{
    int iRDegX = Map_GetRCoordDegreeX(X);
    return iRDegX + WDM_RealCoordStartX;
}

int GetMapCoordMinutesX(float X)
{
    int iRDegX = Map_GetRCoordDegreeX(X);
    int iRSecX = Map_GetRCoordSecondsX(X);

    return makeint((iRSecX - iRDegX * 3600) / 60);
}

int GetMapCoordDegreeZ(float Z)
{
    int iRDegZ = Map_GetRCoordDegreeZ(Z);
    return iRDegZ + WDM_RealCoordStartZ;
}

int GetMapCoordMinutesZ(float Z)
{
    int iRDegZ = Map_GetRCoordDegreeZ(Z);
    int iRSecZ = Map_GetRCoordSecondsZ(Z);

    return makeint((iRSecZ - iRDegZ * 3600) / 60);
}

int GetSeaCoordDegreeX(float X)
{
    float ShipX = GetSeaShipX(X);
    return GetMapCoordDegreeX(ShipX);
}

int GetSeaCoordDegreeZ(float Z)
{
    float ShipZ = GetSeaShipZ(Z);
    return GetMapCoordDegreeZ(ShipZ);
}

int GetSeaCoordMinutesX(float X)
{
    float ShipX = GetSeaShipX(X);
    return GetMapCoordMinutesX(X);
}

int GetSeaCoordMinutesZ(float Z)
{
    float ShipZ = GetSeaShipZ(Z);
    return GetMapCoordMinutesZ(Z);
}

//  строка координат долготы на глобальной карте
string Map_GetRealCoordX(float X)
{
    int iRSecX;
    int iRMinX = 0;
    int iRDegX = 0;

    iRSecX = Map_GetRCoordSecondsX(X);
    iRDegX = makeint(iRSecX / 3600.0);

    iRMinX = makeint((iRSecX - iRDegX * 3600) / 60);
    iRDegX += WDM_RealCoordStartX;

    string sCoordX = "W " + iRDegX + " " + iRMinX + "'";
    return sCoordX;
}

// строка координат широты на глобальной карте
string Map_GetRealCoordZ(float Z)
{
    int iRSecZ;
    int iRMinZ = 0;
    int iRDegZ = 0;

    iRSecZ = Map_GetRCoordSecondsZ(Z);
    iRDegZ = makeint(iRSecZ / 3600.0);

    iRMinZ = makeint((iRSecZ - iRDegZ * 3600) / 60);
    iRDegZ += WDM_RealCoordStartZ;

    string sCoordZ = "N " + iRDegZ + " " + iRMinZ + "'";
    return sCoordZ;
}

void wdmCoordUpdate()
{
    bool isLongitude = false;
    bool isLatitude = false;

    string sCoordinates = "";
    string longitude = "W -- --'";
    string latitude = "N -- --'";

    if (IsEntity(&worldMap))
    {
        if (IsEquipCharacterByItem(pchar, "sextant2"))
        {
            isLongitude = true;
            isLatitude = true;
        }

        if (!isLatitude && IsEquipCharacterByItem(pchar, "bussol"))
        {
            isLatitude = true;
        }

        if (!isLongitude && IsCharacterEquippedArtefact(pchar, "clock2"))
        {
            isLongitude = true;
        }

        if (isLatitude)
            latitude = Map_GetRealCoordZ(makefloat(worldMap.playerShipZ));
        if (isLongitude)
            longitude = Map_GetRealCoordX(makefloat(worldMap.playerShipX));

        sCoordinates = latitude + " " + longitude;

        if (isLongitude || isLatitude)
        {
            SendMessage(&worldMap, "ls", MSG_WORLDMAP_SET_COORDINATES, sCoordinates);
        }

        PostEvent("EventCoordUpdate", 1000);
    }
}

//  строка координат долготы в режиме "море"
string Sea_GetRealCoordX(float X)
{
    float ShipX = GetSeaShipX(X);
    string sCoordX = Map_GetRealCoordX(ShipX);
    return sCoordX;
}

// строка координат широты в режиме "море"
string Sea_GetRealCoordZ(float Z)
{
    float ShipZ = GetSeaShipZ(Z);
    string sCoordZ = Map_GetRealCoordZ(ShipZ);
    return sCoordZ;
}