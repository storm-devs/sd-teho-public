#include "weather\WhrUtils.c"
#include "weather\WhrLightning.c"
#include "weather\WhrRain.c"
#include "weather\WhrSea.c"
#include "weather\WhrSky.c"
#include "weather\WhrSun.c"
#include "weather\WhrTornado.c"
#include "weather\WhrAstronomy.c"

#define WIND_NORMAL_POWER 20.0

#define MAX_WEATHERS 32

object Weather, WeatherParams, WhrCommonParams;
int iNextWeatherNum = -1;
int iCurWeatherNum = -1;
int iBlendWeatherNum = -1;
int iCurWeatherHour = -1;
bool bCurWeatherStorm = false;
int iTotalNumWeathers = 0;
string sLightingPath = "day";
string sLmLightingPath = "day";
string sInsideBack = "";
string sNewExecuteLayer, sNewRealizeLayer;
string sCurrentFog;
float fWeatherDelta = 0.0;
float fWeatherAngle, fWeatherSpeed;
float fFogDensity;
int iShadowDensity[2];
int iPrevWeather = -1;
bool bWeatherLoaded = false;
bool bWeatherIsNight = false;
bool bWeatherIsLight = false;
bool bWeatherIsRain = false;
bool bWeatherIsStorm = false;

object Weathers[MAX_WEATHERS];

extern int InitWeather();

#event_handler("EWhr_GetWindAngle", "Whr_GetWindAngle");
#event_handler("EWhr_GetWindSpeed", "Whr_GetWindSpeed");
#event_handler("EWhr_GetShadowDensity", "Whr_GetShadowDensity");
#event_handler("EWhr_GetFogDensity", "Whr_GetFogDensity");
#event_handler("WeatherTimeUpdate", "Whr_TimeUpdate");

void SetNextWeather(string sWeatherID)
{
    // find weather
    iNextWeatherNum = -1;
    for (int i = 0; i < MAX_WEATHERS; i++)
    {
        if (!CheckAttribute(&Weathers[i], "id"))
        {
            continue;
        }
        if (Weathers[i].id == sWeatherID)
        {
            iNextWeatherNum = i;
            //Trace("iNextWeatherNum = " + iNextWeatherNum);
            //Log_SetStringToLog("ПОГОДА: " + Weathers[i].Lighting);
            return;
        }
    }
}

void WeatherInit()
{
    //DeleteAttribute(&WeatherParams,"");

    if (LoadSegment("weather\WhrInit.c"))
    {
        iTotalNumWeathers = InitWeather();
        UnloadSegment("weather\WhrInit.c");
    }
}

void DeleteWeatherEnvironment()
{
    iBlendWeatherNum = -1;
    if (isEntity(&Weather))
    {
        DeleteClass(&Weather);
    }
    DeleteAttribute(&Weather, "");
    //WeatherParams.Tornado = false;
    //DeleteAttribute(&WeatherParams,"");

    WhrDeleteRainEnvironment();
    WhrDeleteSkyEnvironment();
    WhrDeleteSunGlowEnvironment();
    WhrDeleteLightningEnvironment();
    WhrDeleteTornadoEnvironment();
    WhrDeleteSeaEnvironment();
    WhrDeleteAstronomyEnvironment();

    DelEventHandler(WEATHER_CALC_FOG_COLOR, "Whr_OnCalcFogColor");
    DelEventHandler("frame", "Whr_OnWindChange");

    bWeatherLoaded = false;
}

aref GetCurrentWeather()
{
    aref arWeather;
    makearef(arWeather, Weathers[iCurWeatherNum]);
    return arWeather;
}

void CreateWeatherEnvironment()
{
    int iWeatherFound[MAX_WEATHERS];
    int iNumWeatherFound = 0;
    int iHour = MakeInt(GetHour());

    bool bWhrStorm = false;
    bool bWhrTornado = false;
    if (CheckAttribute(&WeatherParams, "Storm"))
    {
        bWhrStorm = sti(WeatherParams.Storm);
    }
    if (CheckAttribute(&WeatherParams, "Tornado"))
    {
        bWhrTornado = sti(WeatherParams.Tornado);
    }

    //Trace("bCurWeatherStorm = " + bCurWeatherStorm);
    if (iNextWeatherNum != -1)
    {
        if (iPrevWeather == -1)
        {
            iPrevWeather = iCurWeatherNum;
        }
        iCurWeatherHour = iHour;
        iCurWeatherNum = iNextWeatherNum;
        iNextWeatherNum = -1;
        Trace("Weather: used preset weather " + iCurWeatherNum);
    }
    else
    {
        // search weather for hour
        for (int i = 0; i < MAX_WEATHERS; i++)
        {
            if (!CheckAttribute(&Weathers[i], "hour"))
            {
                continue;
            }
            if (CheckAttribute(&Weathers[i], "skip"))
            {
                if (sti(Weathers[i].skip))
                {
                    continue;
                }
            }

            bool bCanStorm = sti(Weathers[i].Storm);
            bool bCanTornado = sti(Weathers[i].Tornado);
            int iMin = sti(Weathers[i].Hour.Min);
            int iMax = sti(Weathers[i].Hour.Max);
            if (iMin == iMax && iMin != iHour)
            {
                continue;
            }
            if (iMin > iMax)
            {
                if (iHour < iMin && iHour > iMax)
                {
                    continue;
                }
            }
            if (iMin < iMax)
            {
                if (iHour < iMin || iHour > iMax)
                {
                    continue;
                }
            }
            if (bWhrStorm != bCanStorm)
            {
                continue;
            }
            if (bWhrTornado == true && bWhrTornado != bCanTornado)
            {
                continue;
            }

            iWeatherFound[iNumWeatherFound] = i;
            iNumWeatherFound++;
        }

        iCurWeatherHour = iHour;

        if (iNumWeatherFound == 0)
        {
            Trace("Error: iNumWeatherFound = 0, for hour = " + iHour);
            iCurWeatherNum = 0;
        }
        else
        {
            iCurWeatherNum = iWeatherFound[rand(iNumWeatherFound - 1)];
        }
    }

    int iCurLocation;
    int iTestWeather;
    if (CheckAttribute(pchar, "location"))
    {
        iCurLocation = FindLocation(pchar.location);
        if (iCurLocation != -1)
        {
            if (CheckAttribute(&locations[iCurLocation], "storm"))
            {
                bWhrStorm = 1;
            }
            if (CheckAttribute(&locations[iCurLocation], "tornado"))
            {
                bWhrTornado = 1;
            }
            if (CheckAttribute(&locations[iCurLocation], "QuestlockWeather"))
            {
                iTestWeather = FindWeather(locations[iCurLocation].QuestlockWeather);
                if (iTestWeather != -1)
                {
                    iCurWeatherNum = iTestWeather;

                    worldMap.date.hour = Weathers[iCurWeatherNum].Hour.Min;
                    Environment.date.hour = Weathers[iCurWeatherNum].Hour.Min;

                    Environment.time = Weathers[iCurWeatherNum].Hour.Min + "." + Environment.date.min;
                }
            }
        }
        if (iCurLocation == -1)
        {
            iCurLocation = FindIsland(pchar.location);
            if (iCurLocation != -1)
            {
                if (CheckAttribute(&Islands[iCurLocation], "storm"))
                {
                    bWhrStorm = 1;
                }
                if (CheckAttribute(&Islands[iCurLocation], "tornado"))
                {
                    bWhrTornado = 1;
                }
                if (CheckAttribute(&Islands[iCurLocation], "QuestlockWeather"))
                {
                    iTestWeather = FindWeather(Islands[iCurLocation].QuestlockWeather);
                    if (iTestWeather != -1)
                    {
                        iCurWeatherNum = iTestWeather;

                        worldMap.date.hour = Weathers[iCurWeatherNum].Hour.Min;
                        Environment.date.hour = Weathers[iCurWeatherNum].Hour.Min;

                        Environment.time = Weathers[iCurWeatherNum].Hour.Min + "." + Environment.date.min;
                    }
                }
            }
        }
    }
    bWeatherIsStorm = bWhrStorm;
    bCurWeatherStorm = bWhrStorm;

    iBlendWeatherNum = FindBlendWeather(iCurWeatherNum);

    // create main module Weather
    DeleteAttribute(&Weather, "");
    if (!isEntity(&Weather))
    {
        CreateEntity(&Weather, "Weather");
    }

    aref aCurWeather = GetCurrentWeather();

    sLightingPath = Whr_GetString(aCurWeather, "Lighting");
    sLmLightingPath = Whr_GetString(aCurWeather, "LightingLm");
    sInsideBack = Whr_GetString(aCurWeather, "InsideBack");
    bWeatherIsNight = Whr_GetLong(aCurWeather, "Night");
    bWeatherIsLight = Whr_GetLong(aCurWeather, "Lights");

    if (CheckAttribute(pchar, "wind.angle"))
    {
        Weather.Wind.Angle = pchar.wind.angle;
        //DeleteAttribute(pchar, "wind.angle");
    }
    else
    {
        Weather.Wind.Angle = frand(PIm2); //Whr_GetFloat(aCurWeather,"Wind.Angle");
        pchar.wind.angle = Weather.Wind.Angle;
    }

    if (CheckAttribute(pchar, "wind.speed"))
    {
        Weather.Wind.Speed = pchar.wind.speed;
        //DeleteAttribute(pchar, "wind.speed");
    }
    else
    {
        Weather.Wind.Speed = Whr_GetFloat(aCurWeather, "Wind.Speed");
        pchar.wind.speed = Weather.Wind.Speed;
    }

    pchar.quest.EraseWind.win_condition.l1 = "ExitFromSea";
    pchar.quest.EraseWind.win_condition = "EraseWind";

    sCurrentFog = "Fog";
    if (bSeaActive)
    {
        if (CheckAttribute(aCurWeather, "SpecialSeaFog"))
        {
            sCurrentFog = "SpecialSeaFog";
        }
    }

    FillWeatherData(iCurWeatherNum, iBlendWeatherNum);

    if (iBlendWeatherNum < 0)
    {
        Weather.Time.time = GetHour();
        Weather.Time.speed = 0.0;           // количество секунд на смену погоды
        Weather.Time.updatefrequence = 0.0; // количество обновлений на смену погоды
    }
    else
    {
        Weather.Time.time = GetTime();
        Weather.Time.speed = 600;          // количество секунд на смену погоды
        Weather.Time.updatefrequence = 60; // количество обновлений на смену погоды
    }

    Weather.isDone = "";

    SetEventHandler(WEATHER_CALC_FOG_COLOR, "Whr_OnCalcFogColor", 0);
    SetEventHandler("frame", "Whr_OnWindChange", 0);

    fFogDensity = stf(Weather.Fog.Density);

    fWeatherDelta = 0.0;
    //fWeatherAngle = stf(Weather.Wind.Angle);
    fWeatherAngle = GetAngleY(stf(worldMap.WindX), stf(worldMap.WindZ));
    fWeatherSpeed = stf(Weather.Wind.Speed);

    int iLoc;
    if (CheckAttribute(pchar, "location"))
    {
        iLoc = FindLocation(pchar.location);
        if (iLoc != -1)
        {
            if (CheckAttribute(&locations[iLoc], "type"))
            {
                if (Locations[iLoc].type == "residence" || Locations[iLoc].type == "tavern" || Locations[iLoc].type == "house" || Locations[iLoc].type == "shop" || Locations[iLoc].type == "shipyard" || Locations[iLoc].type == "church")
                {
                    ClearRainEnvironment();
                }
                else
                {
                    WhrCreateRainEnvironment();
                }
            }
            else
            {
                WhrCreateRainEnvironment();
            }
        }
        else
        {
            WhrCreateRainEnvironment();
        }
    }
    else
    {
        WhrCreateRainEnvironment();
    }
    WhrCreateSunGlowEnvironment();
    WhrCreateLightningEnvironment();
    WhrCreateSkyEnvironment();
    WhrCreateSeaEnvironment();
    WhrCreateAstronomyEnvironment();
    string sLocation = pchar.location;
    int iLocation = FindLocation(sLocation);
    if (iLocation != -1)
    {
        if (CheckAttribute(&Locations[iLocation], "lockWeather"))
        {
            bWhrTornado = false;
        }
    }
    if (bWhrTornado)
    {
        WhrCreateTornadoEnvironment();
    }

    Particles.windpower = 0.05 * Clampf(Whr_GetWindSpeed() / WIND_NORMAL_POWER);
    Particles.winddirection.x = sin(Whr_GetWindAngle());
    Particles.winddirection.z = cos(Whr_GetWindAngle());

    bWeatherLoaded = true;

    if (bSeaActive)
    {
        Island.LightingPath = GetLightingPath();
        Island.FogDensity = Weather.Fog.IslandDensity;
        SendMessage(&IslandReflModel, "lllf", MSG_MODEL_SET_FOG, 1, 1, stf(Weather.Fog.IslandDensity));
    }

    //Trace("Whr: Select id = " + aCurWeather.id);
}

void Whr_UpdateWeather()
{
    if (!isEntity(&Weather))
    {
        return;
    }

    WeatherInit();

    CreateWeatherEnvironment();
    MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);
}

void Whr_LoadNextWeather(int nPlus)
{
    if (!isEntity(&Weather))
    {
        return;
    }
    WeatherInit();

    iCurWeatherHour = MakeInt(GetHour());
    iCurWeatherNum = iCurWeatherNum + nPlus;

    if (iCurWeatherNum < 0)
    {
        iCurWeatherNum = iTotalNumWeathers - 1;
    }
    if (iCurWeatherNum >= iTotalNumWeathers)
    {
        iCurWeatherNum = 0;
    }

    if (CheckAttribute(&Weathers[iCurWeatherNum], "Skip"))
    {
        if (sti(Weathers[iCurWeatherNum].skip))
        {
            Whr_LoadNextWeather(nPlus);
            return;
        }
    }
    Log_SetStringToLog("ПОГОДА: " + Weathers[iCurWeatherNum].id + " ОСВЕЩЕНИЕ: " + Weathers[iCurWeatherNum].Lighting);

    iNextWeatherNum = iCurWeatherNum;
    CreateWeatherEnvironment();
    MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);

    aref aCurWeather = GetCurrentWeather();
    iCurWeatherHour = sti(aCurWeather.Hour.Min);

    SetCurrentTime(iCurWeatherHour, 0);
}

void Whr_OnWindChange()
{
    float fDeltaTime = MakeFloat(GetDeltaTime()) * 0.001;
    fWeatherDelta = fWeatherDelta + fDeltaTime;

    float fSpd = fWeatherSpeed + (fWeatherSpeed / 6.0) * 0.1 * (sin(fWeatherDelta) + sin(0.2 * fWeatherDelta) + sin(PI + 0.8 * fWeatherDelta) + cos(1.5 * fWeatherDelta));
    float fAng = fWeatherAngle + 0.02 * (sin(fWeatherDelta) + sin(0.2 * fWeatherDelta) + sin(PI + 0.8 * fWeatherDelta) + cos(1.5 * fWeatherDelta));

    Weather.Wind.Angle = fAng;
    Weather.Wind.Speed = fSpd;
}

int Whr_OnCalcFogColor()
{
    int iAlpha, iColor;
    float x, y, z;

    x = GetEventData();
    y = GetEventData();
    z = GetEventData();

    if (iBlendWeatherNum < 0)
    {
        aref aCurWeather = GetCurrentWeather();
        iAlpha = 255 - MakeInt(255.0 * Clampf(y / stf(aCurWeather.(sCurrentFog).Height)));

        //iColor = argb(0,0,0,0);
        int iFogColor = sti(Weather.Fog.Color);
        iColor = or (shl(iAlpha, 24), iFogColor);
    }
    else
    {
        float fBlend = stf(Environment.time) - sti(Environment.time);
        float fH = Whr_BlendFloat(fBlend, stf(Weathers[iCurWeatherNum].(sCurrentFog).Height), stf(Weathers[iBlendWeatherNum].(sCurrentFog).Height));
        int iColorTmp = Whr_BlendColor(fBlend, sti(Weathers[iCurWeatherNum].(sCurrentFog).Color), sti(Weathers[iBlendWeatherNum].(sCurrentFog).Color));

        iAlpha = 255 - MakeInt(255.0 * Clampf(y / fH));
        iColor = or (shl(iAlpha, 24), iColorTmp);
    }

    return iColor;
}

float Whr_BlendFloat(float fBlend, float f1, float f2)
{
    float f = f1 + fBlend * (f2 - f1);
    return f;
}

int Whr_BlendLong(float fBlend, int i1, int i2)
{
    int i = makeint(i1 + fBlend * (i2 - i1));
    return i;
}

int Whr_BlendColor(float fBlend, int col1, int col2)
{
    int a1 = shr(and(col1, 4278190080), 24); // get alpha 1
    int a2 = shr(and(col2, 4278190080), 24); // get alpha 2

    int r1 = shr(and(col1, 16711680), 16); // get red color 1
    int r2 = shr(and(col2, 16711680), 16); // get red color 2

    int g1 = shr(and(col1, 65280), 8); // get green color 1
    int g2 = shr(and(col2, 65280), 8); // get green color 2

    int b1 = and(col1, 255); // get blue color 1
    int b2 = and(col2, 255); // get blue color 2

    int r = r1 + MakeInt(fBlend * (r2 - r1));
    int g = g1 + MakeInt(fBlend * (g2 - g1));
    int b = b1 + MakeInt(fBlend * (b2 - b1));
    int a = a1 + MakeInt(fBlend * (a2 - a1));

    return argb(a, r, g, b);
}

void Whr_TimeUpdate()
{
    if (iBlendWeatherNum < 0)
    {
        return;
    }

    float fTime = GetEventData();
    float fBlend = fTime - makeint(fTime);

    //
    Environment.time = fTime;
    int nOldHour = sti(Environment.date.hour);
    int nNewHour = makeint(fTime);
    int nNewMin = makeint((fTime - nNewHour) * 60);
    int nNewSec = makeint(((fTime - nNewHour) * 60 - nNewMin) * 60);
    Environment.date.min = nNewMin;
    Environment.date.hour = nNewHour;
    Environment.date.sec = nNewSec;
    if (nNewHour < nOldHour) // обновление дня
    {
        AddDataToCurrent(0, 0, 1);
    }

    iCurWeatherNum = FindWeatherByHour(makeint(fTime));
    iBlendWeatherNum = FindBlendWeather(iCurWeatherNum);

    if (nNewHour != nOldHour)
    {
        Whr_UpdateWeatherHour();
    }

    // update weather: sun lighting
    FillWeatherData(iCurWeatherNum, iBlendWeatherNum);
    Weather.isDone = "";

    // update rain: rain drops, rain colors, rain size, rainbow
    FillRainData(iCurWeatherNum, iBlendWeatherNum);
    Rain.isDone = "";

    // update sun glow: sun\moon, flares
    WhrFillSunGlowData(iCurWeatherNum, iBlendWeatherNum);
    SunGlow.isDone = true;

    // update sky: fog
    Sky.TimeUpdate = fTime;
}

#event_handler("eChangeDayNight", "eChangeDayNight");

void Whr_UpdateWeatherHour()
{
    bool bOldIsDay = Whr_IsDay();

    bWeatherIsLight = Whr_GetLong(&Weathers[iCurWeatherNum], "Lights");
    bWeatherIsNight = Whr_GetLong(&Weathers[iCurWeatherNum], "Night");

    FillAstronomyFadeValue();
    Astronomy.TimeUpdate = 1;

    if (Whr_IsDay() != bOldIsDay)
    { // меняем источники освещения
        Whr_ChangeDayNight();
        Event("eChangeDayNight");
    }
}

void Whr_ChangeDayNight()
{
    int loadLocationIndex = FindLoadedLocation();
    if (loadLocationIndex >= 0)
    {
        LocationSetLights(&Locations[loadLocationIndex]);
        if (Whr_IsDay())
        {
            SendMessage(&Locations[loadLocationIndex], "ls", MSG_LOCATION_EX_MSG, "DelFlys");
        }
    }
}

void FillWeatherData(int nw1, int nw2)
{
    if (nw1 < 0 || nw1 >= MAX_WEATHERS)
    {
        return;
    }

    string sCurFog = Whr_GetCurrentFog();
    if (nw2 < 0)
    {
        Weather.Fog.Enable = Whr_GetLong(&Weathers[nw1], sCurFog + ".Enable");
        Weather.Fog.Start = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Start");
        Weather.Fog.Density = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density");
        Weather.Fog.Color = Whr_GetColor(&Weathers[nw1], sCurFog + ".Color");
        Weather.Fog.IslandDensity = Whr_GetFloat(&Weathers[nw1], sCurFog + ".IslandDensity");

        Weather.Sun.Color = Whr_GetColor(&Weathers[nw1], "Sun.Color");
        Weather.Sun.HeightAngle = Whr_GetFloat(&Weathers[nw1], "Sun.HeightAngle");
        Weather.Sun.AzimuthAngle = Whr_GetFloat(&Weathers[nw1], "Sun.AzimuthAngle");
        Weather.Sun.Ambient = Whr_GetColor(&Weathers[nw1], "Sun.Ambient");
    }
    else
    {
        float fBlend = stf(Environment.Time) - sti(Environment.Time);
        Weather.Fog.Enable = Whr_GetLong(&Weathers[nw1], sCurFog + ".Enable");
        Weather.Fog.Start = Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Start"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".Start"));
        Weather.Fog.Density = Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".Density"));
        Weather.Fog.Color = Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1], sCurFog + ".Color"), Whr_GetColor(&Weathers[nw2], sCurFog + ".Color"));
        Weather.Fog.IslandDensity = Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".IslandDensity"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".IslandDensity"));

        Weather.Sun.Color = Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1], "Sun.Color"), Whr_GetColor(&Weathers[nw2], "Sun.Color"));
        Weather.Sun.HeightAngle = Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], "Sun.HeightAngle"), Whr_GetFloat(&Weathers[nw2], "Sun.HeightAngle"));
        Weather.Sun.AzimuthAngle = Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], "Sun.AzimuthAngle"), Whr_GetFloat(&Weathers[nw2], "Sun.AzimuthAngle"));
        Weather.Sun.Ambient = Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1], "Sun.Ambient"), Whr_GetColor(&Weathers[nw2], "Sun.Ambient"));
    }
}

int FindWeatherByHour(int nHour)
{
    for (int n = 0; n < MAX_WEATHERS; n++)
    {
        if (!CheckAttribute(&Weathers[n], "hour"))
        {
            continue;
        }
        if (CheckAttribute(&Weathers[n], "skip") && sti(Weathers[n].skip) == true)
        {
            continue;
        }
        if (CheckAttribute(&Weathers[n], "Storm") && sti(Weathers[n].Storm) == true)
        {
            continue;
        }

        if (sti(Weathers[n].hour.min) == nHour)
        {
            return n;
        }
    }
    return -1;
}

int FindBlendWeather(int iWeatherNum)
{
    //return -1;
    if (iWeatherNum < 0 || iWeatherNum >= MAX_WEATHERS)
    {
        return -1;
    }

    if (!CheckAttribute(&Weathers[iWeatherNum], "hour"))
    {
        return -1;
    }
    if (CheckAttribute(&Weathers[iWeatherNum], "Storm") && sti(Weathers[iWeatherNum].Storm) == true)
    {
        return -1;
    }
    if (CheckAttribute(&Weathers[iWeatherNum], "skip") && sti(Weathers[iWeatherNum].skip) == true)
    {
        return -1;
    }

    int nBlendWeatherHour = sti(Weathers[iWeatherNum].hour.min) + 1;
    if (nBlendWeatherHour >= 24)
    {
        nBlendWeatherHour = 0;
    }

    return FindWeatherByHour(nBlendWeatherHour);
}

void CreateWeather(string sExecuteLayer, string sRealizeLayer)
{
    CreateWeatherEnvironment();
    MoveWeatherToLayers(sExecuteLayer, sRealizeLayer);
}

void DeleteWeather()
{
    DeleteWeatherEnvironment();
}

void MoveWeatherToLayers(string sExecuteLayer, string sRealizeLayer)
{
    LayerDelObject("execute", &Weather);
    LayerDelObject("realize", &Weather);
    LayerDelObject(SEA_EXECUTE, &Weather);
    LayerDelObject(SEA_REALIZE, &Weather);

    sNewExecuteLayer = sExecuteLayer;
    sNewRealizeLayer = sRealizeLayer;

    LayerAddObject(sExecuteLayer, &Weather, 1000000);
    LayerAddObject(sRealizeLayer, &Weather, 65530);

    MoveRainToLayers(sExecuteLayer, sRealizeLayer);
    MoveLightningToLayers(sExecuteLayer, sRealizeLayer);
    MoveSkyToLayers(sExecuteLayer, sRealizeLayer);
    MoveSunGlowToLayers(sExecuteLayer, sRealizeLayer);
    MoveAstronomyToLayers(sExecuteLayer, sRealizeLayer);
}

float Whr_GetFogDensity()
{
    return fFogDensity;
}

float Whr_GetWindAngle()
{
    if (!CheckAttribute(&Weather, "Wind.Angle"))
    {
        return 0.0;
    }
    return stf(Weather.Wind.Angle);
}

float Whr_GetWindSpeed()
{
    if (!CheckAttribute(&Weather, "Wind.Speed"))
    {
        return 3.0;
    }
    return stf(Weather.Wind.Speed);
}

ref Whr_GetShadowDensity()
{
    aref aCurWeather = GetCurrentWeather();

    iShadowDensity[0] = argb(255, 96, 96, 96);
    iShadowDensity[1] = argb(255, 96, 96, 64);

    if (bWeatherLoaded)
    {
        iShadowDensity[0] = Whr_GetColor(aCurWeather, "Shadow.Density.Head");
        iShadowDensity[1] = Whr_GetColor(aCurWeather, "Shadow.Density.Foot");
    }

    return &iShadowDensity;
}

string Whr_GetCurrentFog()
{
    return sCurrentFog;
}

string Whr_GetInsideBack()
{
    return sInsideBack;
}
string GetLightingPath()
{
    return sLightingPath;
}
string GetLmLightingPath()
{
    return sLmLightingPath;
}

bool Whr_IsDay()
{
    return !bWeatherIsNight;
};
bool Whr_IsNight()
{
    return bWeatherIsNight;
};
bool Whr_IsLight()
{
    return bWeatherIsLight;
};
bool Whr_IsRain()
{
    return bWeatherIsRain;
}
bool Whr_IsStorm()
{
    return bWeatherIsStorm;
}

int FindWeather(string sWeatherID)
{
    for (int i = 0; i < MAX_WEATHERS; i++)
    {
        if (!CheckAttribute(&Weathers[i], "id"))
        {
            continue;
        }
        if (Weathers[i].id == sWeatherID)
        {
            return i;
        }
    }
    return -1;
}