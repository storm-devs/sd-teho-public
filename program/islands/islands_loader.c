#define DIRECTSAILDEBUG 0

#define DIRECTENCOUNTERRANDDISTANCE 6250000.0  // 2500 ^ 2
#define DIR_SAIL_STORM_DIST_REL 12250000.0     // 3500 ^ 2
#define DIR_SAIL_STORMWARN_DIST_REL 25000000.0 // 5000 ^ 2
#define DIR_SAIL_STORM_DIST 3500.0

#define DIR_PORTBOW 1
#define DIR_FORWARD 2
#define DIR_STARBOW 3
#define DIR_STAR 4
#define DIR_PORT 5
#define DIR_PORTSTERN 6
#define DIR_ABAFT 7
#define DIR_STARSTERN 8

#define DIR_FORE 4

extern void evtDirSail(aref rRawG, aref encDataForS, int iNumMerchantS, int iNumWarS,
                       float playerShipX, float playerShipZ, float locx, float locay, float locz,
                       float dst, float fScale, string eID);

void getRTplayerShipXZ(ref RTplayerShipX, ref RTplayerShipZ, ref scale)
{
    float zeroX = MakeFloat(worldMap.zeroX);
    float SeaX = stf(pchar.Ship.Pos.x);
    float zeroZ = MakeFloat(worldMap.zeroZ);
    float SeaZ = stf(pchar.Ship.Pos.z);
    string sIsland = worldMap.island;

    scale = WDM_MAP_TO_SEA_SCALE;
    if (sIsland == "Cuba1" || sIsland == "Cuba2" || sIsland == "Beliz" || sIsland == "SantaCatalina" || sIsland == "PortoBello" || sIsland == "Cartahena" || sIsland == "Maracaibo" || sIsland == "Caracas" || sIsland == "Cumana")
    {
        scale = 25;
    }
    RTplayerShipX = (SeaX / scale) + zeroX;
    RTplayerShipZ = (SeaZ / scale) + zeroZ;
    return;
}

float getRTplayerShipAY()
{
    float RTplayerShipAY = stf(pchar.Ship.Ang.y);
    return RTplayerShipAY;
}

int getRTclosestIsland(float RTplayerShipX, float RTplayerShipZ, int curScale, ref iDistanceNow, ref scaleDiff)
{
    if (DIRECTSAILDEBUG)
        Log_SetStringToLog("getRTclosestIsland. curr island: " + worldMap.island);

    bool tempDiff;
    float distance, iBearing, offShip, shipAY, iX, iZ;

    iDistanceNow = 2500000000.0;
    scaleDiff = false;

    int nextisland = -1;

    ref rIsland;
    string islandTemp;
    shipAY = stf(pchar.Ship.Ang.y);

    for (int inum = 0; inum <= iNumIslands; inum++)
    {
        rIsland = GetIslandByIndex(inum);
        islandTemp = rIsland.id;

        if (Islands[inum].visible == false)
            continue;

        iX = stf(worldMap.islands.(islandTemp).position.x);
        iZ = stf(worldMap.islands.(islandTemp).position.z);

        iBearing = GetAngleY(iX - RTplayerShipX, iZ - RTplayerShipZ);
        offShip = iBearing - shipAY;
        int nBear = ClosestDirFA(offShip);
        if (nBear != DIR_FORWARD)
            continue;

        tempDiff = false;
        if (curScale == WDM_MAP_TO_SEA_SCALE)
        {
            if (islandTemp == "Cuba1" || islandTemp == "Cuba2" || islandTemp == "Beliz" || islandTemp == "SantaCatalina" || islandTemp == "PortoBello" || islandTemp == "Cartahena" || islandTemp == "Maracaibo" || islandTemp == "Caracas" || islandTemp == "Cumana")
            {
                tempDiff = true;
            }
        }

        distance = GetDistance2DRel(RTplayerShipX, RTplayerShipZ, iX, iZ);

        if (DIRECTSAILDEBUG)
            trace("getRTclosestIsland. islandTemp=" + islandTemp + ", distance=" + distance + ", iDistanceNow=" + iDistanceNow);

        if (distance < iDistanceNow)
        {
            iDistanceNow = distance
                nextisland = inum;
            scaleDiff = tempDiff;
        }
    }
    if (DIRECTSAILDEBUG)
        Log_SetStringToLog("getRTclosestIsland. closest island: " + Islands[nextisland].id + ", idx=" + nextisland);

    return nextisland;
}

void ChangeSeaMapNew()
{
    DelEventHandler("FaderEvent_StartFade", "ChangeSeaMapNew");
    PauseAllSounds();
    DeleteSeaEnvironment();
    LayerAddObject(SEA_REALIZE, &wdm_fader, -1);
}

void Sea2Sea_Reload()
{
    DelEventHandler("FaderEvent_EndFade", "Sea2Sea_Reload");
    ReloadProgressStart();
    object seaLoginToSea;

    float CX;
    float CZ;
    int scale = WDM_MAP_TO_SEA_SCALE;
    float fScrap;
    getRTplayerShipXZ(&CX, &CZ, &scale);

    float CAY = getRTplayerShipAY();
    bool bScaleDiff;
    int nextisland = getRTclosestIsland(CX, CZ, scale, &fScrap, &bScaleDiff);
    ref rIsland = GetIslandByIndex(nextisland);
    string CIsland = rIsland.id;

    float ix = MakeFloat(worldMap.islands.(CIsland).position.x);
    float iz = MakeFloat(worldMap.islands.(CIsland).position.z);

    seaLoginToSea.playerGroup.x = (CX - ix) * scale;
    seaLoginToSea.playerGroup.z = (CZ - iz) * scale;
    seaLoginToSea.playerGroup.ay = CAY;
    seaLoginToSea.island = CIsland;

    seaLoginToSea.imageName = "loading\sea_0" + rand(2) + ".tga";

    SeaLogin(&seaLoginToSea);
    LayerAddObject(SEA_REALIZE, &wdm_fader, -1);
    ReloadProgressEnd();

    float RTplayerShipX;
    float RTplayerShipZ;

    getRTplayerShipXZ(&RTplayerShipX, &RTplayerShipZ, &scale);

    worldMap.playerShipX = RTplayerShipX;
    worldMap.playerShipZ = RTplayerShipZ;
    worldMap.playerShipAY = getRTplayerShipAY();
    worldMap.island = rIsland.id;
    worldMap.zeroX = ix;
    worldMap.zeroZ = iz;
}

int ClosestDirE(float dir)
{
    float aX[8];
    float aZ[8];

    aX[0] = -0.5;
    aX[1] = 0.0;
    aX[2] = 0.5;
    aX[3] = 1.0;
    aX[4] = -1.0;
    aX[5] = -0.5;
    aX[6] = 0.0;
    aX[7] = 0.5;
    aZ[0] = 1.0;
    aZ[1] = 1.0;
    aZ[2] = 1.0;
    aZ[3] = 0.0;
    aZ[4] = 0.0;
    aZ[5] = -1.0;
    aZ[6] = -1.0;
    aZ[7] = -1.0;

    float maxDot = -99999999.0;
    int nRet = 0;
    for (int i = 0; i < 8; i++)
    {
        float v = GetAngleY(aX[i], aZ[i]);
        float t = GetDotProduct(v, dir);
        if (t > maxDot)
        {
            nRet = i + 1;
            maxDot = t;
        }
    }
    return nRet;
}

int ClosestDirFA(float dir)
{
    float aX[6];
    float aZ[6];

    aX[0] = -1.0;
    aX[1] = 0.0;
    aX[2] = 1.0;
    aX[3] = -1.0;
    aX[4] = 0.0;
    aX[5] = 1.0;
    aZ[0] = 0.5;
    aZ[1] = 1.0;
    aZ[2] = 0.5;
    aZ[3] = 0.0;
    aZ[4] = -1.0;
    aZ[5] = 0.0;

    float maxDot = -99999999.0;
    int nRet = 0;
    for (int i = 0; i < 6; i++)
    {
        float v = GetAngleY(aX[i], aZ[i]);
        float t = GetDotProduct(v, dir);
        if (t > maxDot)
        {
            nRet = i + 1;
            maxDot = t;
        }
    }
    if (nRet < 4)
        nRet = DIR_FORWARD;
    else
        nRet = DIR_ABAFT;

    return nRet;
}

void CheckIslandChange()
{
    float RTplayerShipX;
    float RTplayerShipZ;
    int scale;
    bool isStorm, isTornado;

    getRTplayerShipXZ(&RTplayerShipX, &RTplayerShipZ, &scale);

    float distToClosestIsland, distStorm;
    bool bScaleDiff;
    bool bCheckEnc = true;

    int nextisland = getRTclosestIsland(RTplayerShipX, RTplayerShipZ, scale, &distToClosestIsland, &bScaleDiff);

    if (DIRECTSAILDEBUG)
        Log_SetStringToLog("CheckIslandChange: nextisland = " + nextisland);

    while (nextisland > -1 && nextisland != FindIsland(worldMap.island))
    {
        ref rIsland = GetIslandByIndex(nextisland);
        string sNewIslandId = rIsland.id;
        string sIslandNow = worldMap.island;

        float distToCurIsland;

        if (worldMap.island == WDM_NONE_ISLAND)
        {
            distToCurIsland = 2500000000.0;
        }
        else
        {
            distToCurIsland = GetDistance2DRel(RTplayerShipX, RTplayerShipZ, stf(worldMap.islands.(sIslandNow).position.x), stf(worldMap.islands.(sIslandNow).position.z));
        }

        if (bScaleDiff)
        {
            if (distToClosestIsland * 1.12 > distToCurIsland)
                break;
        }
        else
        {
            if (distToClosestIsland * 1.85 > distToCurIsland)
                break;
        }

        bCheckEnc = false;

        aref rSituation;
        makearef(rSituation, pchar.SeaAI.Update.Situation);

        float enemydist = 0.0;
        int nextenemy = 0;
        float enemyDistLimit = 1000.0;
        float neutralDistLimit = 1000.0;
        /*
        nextenemy = sti(rSituation.MinEnemyIndex);
        enemydist = stf(rSituation.MinEnemyDistance);
        //if (DIRECTSAILDEBUG) trace("DirectsailCheck; next enemy: "+nextenemy + " dist: "+enemydist);
        if(nextenemy!= -1 && enemydist<enemyDistLimit )
        {
            //if (DIRECTSAILDEBUG) trace("Directsail aborted due to hostile ship, dist = " + enemydist);    
            break;
        }
        
        nextenemy = sti(rSituation.MinNeutralIndex);
        enemydist = stf(rSituation.MinNeutralDistance);

        //if (DIRECTSAILDEBUG) trace("DirectsailCheck; next neutral ship: "+nextenemy + " dist: "+enemydist);
        if(nextenemy!= -1 && enemydist<neutralDistLimit && sti(Characters[nextenemy].ship.type) != SHIP_FORT ) 
        {
          //if (DIRECTSAILDEBUG) trace("Directsail aborted due to neutral ship, dist = " + enemydist);    
          break;
        }
*/
        if (!bMapEnter)
        {
            if (DIRECTSAILDEBUG)
                trace("Directsail aborted in battle");
            break;
        }

        sIslandID = sNewIslandId;

        SetEventHandler("FaderEvent_StartFade", "ChangeSeaMapNew", 0);
        SetEventHandler("FaderEvent_EndFade", "Sea2Sea_Reload", 0);

        CreateEntity(&wdm_fader, "fader");
        if (IsEntity(wdm_fader) == 0)
            Trace("Fader not created!!!");

        float fadeOutTime = 0.5;

        SendMessage(&wdm_fader, "lfl", FADER_OUT, fadeOutTime, true);
        SendMessage(&wdm_fader, "l", FADER_STARTFRAME);

        string imageName = "loading\sea_0" + rand(2) + ".tga";
        wdmLoginToSea.imageName = imageName;

        SendMessage(&wdm_fader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
        SendMessage(&wdm_fader, "ls", FADER_PICTURE, imageName);

        break;
    }

    if (bCheckEnc)
    {
        if (DIRECTSAILDEBUG)
            Log_SetStringToLog("bCheckEnc : " + bCheckEnc);

        checkWMEnctr(RTplayerShipX, RTplayerShipZ, scale, &isStorm, &isTornado, &distStorm);

        if (isStorm)
        {
            if (distStorm <= DIR_SAIL_STORM_DIST_REL)
            {
                WeatherParams.Tornado = isTornado;
                WeatherParams.Storm = true;
                iStormLockSeconds = 60;
                Seafoam.storm = "true";
                Whr_UpdateWeather();
                SetSchemeForSea();
            }
            else
            {
                WeatherParams.Rain.ThisDay = true;
                WeatherParams.Rain.StartTime = MakeInt(GetHour());
                WeatherParams.Rain.Duration = 75.0;
                Whr_UpdateWeather();
                Log_SetStringToLog("Капитан, рядом шторм!");
            }
        }
    }
}

void checkWMEnctr(float RTplayerShipX, float RTplayerShipZ, int scale, ref bStorm, ref bTornado, ref distStorm)
{
    bStorm = false;
    distStorm = 0.0;

    if (!bMapEnter)
        return; // если выход на глобус запрещен

    int i;
    ref rSGroup;
    aref WME;
    makearef(WME, worldmap.encounters);

    aref rRawGroup, encDataForSlot, fndGroup;

    int nWME = GetAttributesNum(WME);
    int iNumWarShips = 0;
    int iNumMerchantShips = 0;
    int nShipCnt = 0;
    bool bFound = false;
    float fScale = makefloat(scale);
    float x, z, ay, dist, xs, zs, dists;
    string encID = "";

    bTornado = false;

    RTplayerShipX *= fScale;
    RTplayerShipZ *= fScale;

    if (DIRECTSAILDEBUG)
        Log_SetStringToLog("nWME : " + nWME);

    for (i = 0; i < nWME, i++)
    {
        if (bStorm && bFound)
            break;
        rRawGroup = GetAttributeN(WME, i);
        if (!CheckAttribute(rRawGroup, "type"))
            continue;
        if (CheckAttribute(rRawGroup, "needDelete"))
            continue;
        if (CheckAttribute(rRawGroup, "dirSailEnc"))
            continue;

        if (rRawGroup.type == "Storm")
        {
            if (bStorm)
                continue;

            xs = stf(rRawGroup.px) * fScale;
            zs = stf(rRawGroup.pz) * fScale;

            dists = GetDistance2DRel(RTplayerShipX, RTplayerShipZ, xs, zs);
            if (dists > DIR_SAIL_STORMWARN_DIST_REL)
                continue;

            bStorm = true;
            distStorm = dists;

            if (CheckAttribute(rRawGroup, "isTornado") && sti(rRawGroup.isTornado) != 0)
                bTornado = true;
            if (dists <= DIR_SAIL_STORM_DIST_REL)
                rRawGroup.needDelete = "Reload delete storm encounter";
        }
        else
        {
            if (bFound)
                continue

                    if (!CheckAttribute(rRawGroup, "encdata")) continue;

            encID = "";
            encID = GetAttributeName(rRawGroup);

            if (DIRECTSAILDEBUG)
            {
                trace("enccID : " + encID);
                DumpAttributes(rRawGroup);
            }

            makearef(encDataForSlot, rRawGroup.encdata);

            rSGroup = Group_GetGroupByID("Sea_" + encDataForSlot.GroupName);
            if (CheckAttribute(rSGroup, "AlreadyLoaded"))
                continue;

            nShipCnt = iNumShips;

            if (CheckAttribute(encDataForSlot, "NumMerchantShips"))
            {
                iNumMerchantShips = sti(encDataForSlot.NumMerchantShips);
                nShipCnt += iNumMerchantShips;
            }
            if (CheckAttribute(encDataForSlot, "NumWarShips"))
            {
                iNumWarShips = sti(encDataForSlot.NumWarShips);
                nShipCnt += iNumWarShips;
            }
            if (nShipCnt > MAX_SHIPS_IN_LOCATION)
                continue;

            x = stf(rRawGroup.x) * fScale;
            z = stf(rRawGroup.z) * fScale;
            ay = stf(rRawGroup.ay);
            dist = GetDistance2DRel(RTplayerShipX, RTplayerShipZ, x, z);

            if (dist > DIRECTENCOUNTERRANDDISTANCE)
                continue;

            fndGroup = rRawGroup;
            bFound = true;
        }
    }

    if (DIRECTSAILDEBUG)
        Log_SetStringToLog("bFound : " + bFound + " encID : " + encID);

    if (!bFound || encID == "")
        return;

    rRawGroup = fndGroup;

    LaunchDirSailEnc();

    evtDirSail(rRawGroup, encDataForSlot, iNumMerchantShips, iNumWarShips, RTplayerShipX, RTplayerShipZ, x, ay, z, dist, fScale, encID);

    return;
}
