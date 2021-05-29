#define MAX_CANNON_DAMAGE_DISTANCE				3.0

#define MAX_HEEL_ANGLE							0.262 // в радианах = 15 гр. - максимальный угол крена при потере всех орудий с одного борта и всех целых другого борта
#define MAX_VOLLEY_HEEL_ANGLE					0.10  

void DeleteCannonsEnvironment()
{
	DelEventHandler(CANNON_GET_RECHARGE_TIME, "Cannon_GetRechargeTime");
	DelEventHandler(CANNON_GET_FIRE_TIME, "Cannon_GetFireTime");
	DelEventHandler(CANNON_GET_FIRE_HEIGHT, "Cannon_GetFireHeight");
	DelEventHandler(CANNON_FIRE, "Cannon_FireCannon");
	DelEventHandler(CANNON_UNLOAD, "Cannon_UnloadBall");
	DelEventHandler(CANNON_LOAD, "Cannon_LoadBall");
	DelEventHandler(CANNON_RECALCULATE_PARAMETERS, "Cannon_RecalculateParametersEvent");
	DelEventHandler(CANNON_DAMAGE, "Cannon_DamageEvent");
}

void CreateCannonsEnvironment()
{
	SetEventHandler(CANNON_GET_RECHARGE_TIME, "Cannon_GetRechargeTime", 0);
	SetEventHandler(CANNON_GET_FIRE_TIME, "Cannon_GetFireTime", 0);
	SetEventHandler(CANNON_GET_FIRE_HEIGHT, "Cannon_GetFireHeight", 0);
	SetEventHandler(CANNON_FIRE, "Cannon_FireCannon", 0);
	SetEventHandler(CANNON_UNLOAD, "Cannon_UnloadBall", 0);
	SetEventHandler(CANNON_LOAD, "Cannon_LoadBall", 0);
	SetEventHandler(CANNON_RECALCULATE_PARAMETERS, "Cannon_RecalculateParametersEvent", 0);
	SetEventHandler(CANNON_DAMAGE, "Cannon_DamageEvent", 0);

	SendMessage(&AISea, "lff", AI_MESSAGE_CANNONS_PARAMS, MAX_CANNON_DAMAGE_DISTANCE, 1.0);	// fMaxCannonDamageDistance, fMaxCannonDamageRadiusPoint
}

bool Cannon_LoadBall()
{
	aref	aCharacter = GetEventData();

	int iBallType = sti(aCharacter.Ship.Cannons.Charge.Type);
	int iNumBalls = GetCargoGoods(aCharacter, iBallType);
 	// boal -->
	int iNumPowder = GetCargoGoods(aCharacter, GOOD_POWDER);
	if (iNumBalls > 0 && iNumPowder > 0)
	{
		AddCharacterGoodsCannon(aCharacter, iBallType, -1);
		AddCharacterGoodsCannon(aCharacter, GOOD_POWDER, -1);
		// boal <--
		return true;
	}
	return false;
}

void Cannon_UnloadBall()
{
	aref aCharacter = GetEventData();
	if(CheckAttribute(aCharacter, "Ship.Cannons"))
	{
		AddCharacterGoodsCannon(aCharacter, sti(aCharacter.Ship.Cannons.Charge.Type), 1);
	}	
	// boal -->
	AddCharacterGoodsCannon(aCharacter, GOOD_POWDER, 1);
	// boal <--
}

void AddCharacterGoodsCannon(aref aCharacter, int iGood, int iQuantity)
{
	string sGoodName = Goods[iGood].name;
	aCharacter.Ship.Cargo.Goods.(sGoodName) = sti(aCharacter.Ship.Cargo.Goods.(sGoodName)) + iQuantity;
	aCharacter.Ship.Cargo.RecalculateCargoLoad = true;
}

void Cannon_RecalculateParametersEvent()
{
	int iCharacterIndex = GetEventData();
	Cannon_RecalculateParameters(iCharacterIndex);
}

void Cannon_RecalculateParameters(int iCharacterIndex)
{
	if (sti(Characters[iCharacterIndex].Ship.Cannons.Type) == CANNON_TYPE_NONECANNON) { return; }

	ref	rCharacter = GetCharacter(iCharacterIndex);
	ref	rCannon = GetCannonByType(sti(rCharacter.Ship.Cannons.Type));
	ref	rBall = GetGoodByType(sti(rCharacter.Ship.Cannons.Charge.Type));
	if (CheckAttribute(rCharacter, "TmpPerks.LongRangeShoot"))
	{
		rCharacter.Ship.Cannons.SpeedV0 = stf(rCannon.SpeedV0) * stf(rBall.SpeedV0) * AIShip_isPerksUse(rCharacter.TmpPerks.LongRangeShoot, 1.0, 1.15); //slib
	}
	else
	{
	    rCharacter.Ship.Cannons.SpeedV0 = stf(rCannon.SpeedV0) * stf(rBall.SpeedV0);
	}
	rCharacter.Ship.Cannons.FireAngMax = rCannon.FireAngMax;
	rCharacter.Ship.Cannons.FireAngMin = rCannon.FireAngMin;
}

float Cannon_GetFireHeight()
{
	aref aCharacter = GetEventData();
	aref aEnemy = GetEventData();
	
	ref rBallType = GetGoodByType(sti(aCharacter.Ship.Cannons.Charge.Type));
	ref rEnemyShip = GetRealShip(sti(aEnemy.Ship.Type));

	string sBallName = rBallType.Name;

	float Y,DY;
	Y = stf(rEnemyShip.Height.(sBallName).Y);
	DY = stf(rEnemyShip.Height.(sBallName).DY);

    // charge/ship depend
	// boal new goals -->
	//return (Y + (frnd()-0.5) * DY * 2);
	// введем логику и учет от расстояния. также учет что, бомбы тяжелее ядер
	float dist = Ship_GetDistance2D(aCharacter, aEnemy);
	// Y- высоты прицела, задана для борта от типа корабля противника 1-3 для ядер 10-20 для книпперей 2-4 картеч DY - дисперсия
	// Будем исходить из подобия треугольников и того, что высота подобрана Акеллой на середину радиура выстрела
	ref	rCannon = GetCannonByType(sti(aCharacter.Ship.Cannons.Type));
	if (sBallName == "Bombs" || sBallName == "Grapes")
	{
	   Y = Y + 0.6;
	}
	if (sti(aEnemy.Ship.Type) == SHIP_FORT)
	{
	   Y = 40;
	   DY = 16;
	}
	float RY = abs(Y * (dist / ( stf(rCannon.FireRange) / 2)) + (frnd()-0.5) * DY / 4));
	if (RY < 0.8)
	{
	   RY = 0.8;
	}
	if (RY > 55)
	{
	   RY = 55;
	}
	return RY;
	// boal <--
}

// calculate recharge time for cannon
float Cannon_GetRechargeTime()
{
	aref	aCharacter = GetEventData();

	float	fCannonSkill = 1.0 - stf(aCharacter.TmpSkill.Cannons) / 3.0;

	ref		rCannon = GetCannonByType(sti(aCharacter.Ship.Cannons.Type));
	float	fReloadTime = GetCannonReloadTime(rCannon); // boal 28.01.03 - 09.02.05

	float fMultiply = 1.0;
	// boal -->

       // EvgAnat - фикс fMultiply --> 

        fMultiply = fMultiply * AIShip_isPerksUse(aCharacter.TmpPerks.FastReload, 1.0, 0.9);
        fMultiply = fMultiply * AIShip_isPerksUse(aCharacter.TmpPerks.ImmediateReload, 1.0, 0.5); 
        fMultiply = fMultiply * isEquippedArtefactUse(aCharacter, "amulet_5", 1.0, 0.85);
  
       //<-- EvgAnat 

	ref refBaseShip = GetRealShip(sti(aCharacter.ship.Type));
	if (sti(refBaseShip.BaseType) != SHIP_FORT)
	{
        // boal 060804 для компа поблажки
		if (sti(aCharacter.index) != GetMainCharacterIndex())
		{
		    fReloadTime -= MOD_SKILL_ENEMY_RATE; // -10c на невозможном
			if (fReloadTime < 5.0) fReloadTime = 5.0; //Jason - фикс пулеметов 3 калибра
		}
		// boal <--
		float crewQty  = GetCrewQuantity(aCharacter);
	    float OptCrew  = GetOptCrewQuantity(aCharacter); 
	    float MaxCrew  = GetMaxCrewQuantity(aCharacter); 
	    float fMorale  = GetCharacterCrewMorale(aCharacter); 
	    
	    if (crewQty > MaxCrew) crewQty = MaxCrew; // fix 14/03/05
	    if (OptCrew > 0)
	    {
            float  fExp;
			fExp = 0.001 + stf(GetCrewExp(aCharacter, "Cannoners") * crewQty) / stf(OptCrew * GetCrewExpRate());
			if (fExp > 1) fExp = 1;
			fReloadTime = fReloadTime * (1.0 + (1.0 - fExp) * 3.0);
        }
	    fReloadTime = fReloadTime * (1.0 + (1.0 - fMorale / MORALE_NORMAL) * 0.2);
	    
        if (crewQty <= (GetMinCrewQuantity(aCharacter)))
        {
            fReloadTime = fReloadTime * 3.0; //меньше команды - тормозим
        } 
    // boal  корректный учет команды <--
    }
	return  fMultiply * fReloadTime * fCannonSkill;
}

// calculate delay before fire
float Cannon_GetFireTime()
{
	//aref aCharacter = GetEventData();
	aref aCharacter = GetEventData();
	ref refBaseShip = GetRealShip(sti(aCharacter.ship.Type));

	// make 10 seconds random delay between fire from fort cannons
	if (refBaseShip.Name == ShipsTypes[SHIP_FORT].Name) { return frnd() * 20.0; }   // иначе пулеметный залп

	float fCannonSkill = stf(aCharacter.TmpSkill.Cannons);
	float fFireTime = 1.3 - fCannonSkill;
	//fFireTime = fFireTime * Bring2RangeNoCheck(3.0, 1.0, 0.0, 1.0, stf(aCharacter.Ship.Crew.MinRatio));
	fFireTime = frnd() * fFireTime * 6.0;
	if (iArcadeSails) { fFireTime = fFireTime * 0.5; }
				   
	float crewQ   = GetCrewQuantity(aCharacter);
 	float crewMax = stf(refBaseShip.MaxCrew);
 	float crewOpt = stf(refBaseShip.OptCrew);
 	if (crewMax < crewQ) crewQ  = crewMax; 
 	
	float fCrewMorale = GetCharacterCrewMorale(aCharacter);

    float  fExp;
	fExp = 0.05 + stf(GetCrewExp(aCharacter, "Cannoners") * crewQ) / stf(crewOpt * GetCrewExpRate());
	if (fExp > 1.0) fExp = 1.0;
	
	fFireTime = fFireTime * (2.0 - fExp);
	fFireTime = fFireTime * (1.0 + (1.0 - fCrewMorale/MORALE_NORMAL)/5.0);
	
	return fFireTime;  
}

void Cannon_FireCannon()
{
	float fX, fY, fZ, fSpeedV0, fDirAng, fHeightAng, fCannonDirAng, fMaxFireDistance;

	aref aCharacter = GetEventData();

	DeleteAttribute(aCharacter, "Sea_AI.Cannon.Charge"); //должно располагаться здесь, а не выше

	fX = GetEventData();
	fY = GetEventData();
	fZ = GetEventData();
	fSpeedV0 = GetEventData();
	fDirAng = GetEventData();
	fHeightAng = GetEventData();
	fCannonDirAng = GetEventData();
	fMaxFireDistance = GetEventData();
		
	 // boal навел порядок по оптимизации
	Ball_AddBall(aCharacter, fX, fY, fZ, fSpeedV0, fDirAng, fHeightAng, fCannonDirAng, fMaxFireDistance);
}

// Damage 2 cannon from balls
float Cannon_DamageEvent()
{
	//return 0.0;
	aref	aCharacter = GetEventData();
	float	fBallDamage = GetEventData();	// ball damage
	float	fCurDamage = GetEventData();	// current cannon damage (0.0 .. 1.0)
	float	fDistance = GetEventData();		// distance from ball 2 cannon
	float	x = GetEventData();				// x, y, z - cannon position
	float	y = GetEventData();
	float	z = GetEventData();
	
	float	ax = 0.0;
	float 	az = 0.0;

	if(CheckAttribute(aCharacter, "chr_ai.immortal"))
	{
		if(sti(aCharacter.chr_ai.immortal) == 1)
		{
			return 0.0;
		}
	}
	if(IsCharacterEquippedArtefact(aCharacter, "talisman3")) return 0.0;
	
	ref	rCannon = GetCannonByType(sti(aCharacter.Ship.Cannons.Type));
	
	float fMaxCHP = stf(rCannon.hp);
	//fCurDamage = (fCurDamage * fMaxCHP + fBallDamage * (1.0 - fDistance / MAX_CANNON_DAMAGE_DISTANCE)) / fMaxCHP;
    //Log_TestInfo("fBallDamage "  + fBallDamage + " fCurDamage " +fCurDamage + " fMaxCHP " + fMaxCHP + " fDistance " +fDistance);
    fBallDamage *= 0.1 / fDistance;
    fCurDamage =  fCurDamage  + fBallDamage / fMaxCHP;  // TO_DO
	if (IsCharacterPerkOn(aCharacter, "HT4")) fCurDamage = fCurDamage/2.0;
    
	//fCurDamage = fCurDamage - fCurDamage/100*(sti(aCharacter.ship.upgrades.cannons)-1)*20;
	if (fCurDamage >= 1.0)
	{
		fCurDamage = 1.0;
		CreateBlast(x,y,z);
		CreateParticleSystem("blast_inv", x, y, z, 0.0, 0.0, 0.0, 0);
		Play3DSound("cannon_explosion", x, y, z);
		if (sti(aCharacter.index) == GetMainCharacterIndex())
		{
		    Log_Info(XI_ConvertString("Cannon_DamageEvent"));
		}
		aCharacter.Ship.Cargo.RecalculateCargoLoad = true; // boal 27.07.06 пушки - груз
/*		
		if(SetHeel_XZ(aCharacter,  &ax, &az))
		{
			SendMessage(aCharacter, "lff", MSG_SHIP_SET_HEEL_XZ, ax, az); 
		}	
*/		
	}

	return fCurDamage;
}

int GetBortIntactCannonsNum(ref rCharacter, string sBort, int iNumCannonsOnBort)
{
	float fDamage  = 0.0;
	
        if(sti(rCharacter.ship.type) == SHIP_NOTUSED) return 0;
	if(iNumCannonsOnBort <= 0) return 0;
	if (!CheckAttribute(rCharacter, "Ship.Cannons.Borts." + sBort + ".damages")) return iNumCannonsOnBort;				
	aref arDamages;	
	makearef(arDamages, rCharacter.Ship.Cannons.Borts.(sBort).damages);
		
	int iNumIntactCannons = 0;
	for (int i=0; i<GetAttributesNum(arDamages); i++)
	{
		fDamage = stf(GetAttributeValue(GetAttributeN(arDamages, i)));
		if (fDamage < 1.0) { iNumIntactCannons++; }
	}	
	return iNumIntactCannons;
}

int GetBortCannonsQtyMax(ref rCharacter, string sBort)
{
	float 	fDamage;
	int	  	iCannons = 0;	
	int		iDisabledCannons = 0;
	string  sDamage;

	int 	nShipType = sti(rCharacter.ship.type);	
	ref 	refBaseShip = GetRealShip(nShipType);	
	
	iCannons = sti(refBaseShip.(sBort));	// это теоретический максимум !
	
	// ищем задизейбленные орудия
	if (CheckAttribute(rCharacter, "Ship.Cannons.Borts." + sBort + ".damages"))		
	{
		aref arDamages;	
		makearef(arDamages, rCharacter.Ship.Cannons.Borts.(sBort).damages);
		for (int i=0; i<GetAttributesNum(arDamages); i++)
		{
			fDamage = stf(GetAttributeValue(GetAttributeN(arDamages, i)));
			if (fDamage > 1.0) { iDisabledCannons++; }
		}
	}
	iCannons -= iDisabledCannons;
	if(iCannons < 0) iCannons = 0;
	
	return iCannons;	
}

bool SetHeel_XZ(ref rCharacter,  ref float_x, ref float_z)
{
	float 	ang_x = 0.0; 
	float 	ang_z = 0.0;
	
	int 	iRCannon = 0;
	int 	iLCannon = 0;
	
	iRCannon = GetBortCannonsQtyMax(rCharacter, "cannonr");
	iLCannon = GetBortCannonsQtyMax(rCharacter, "cannonl");
	
	if(iRCannon != iLCannon) 
	{
		float_x = ang_x; float_z = ang_z;
		return false;
	}
	
	if(iRCannon == 0 || iLCannon == 0) return false;
	
	int iIntactRCannon = GetBortCannonsQty(rCharacter, "cannonr");
	int iIntactLCannon = GetBortCannonsQty(rCharacter, "cannonl");
		
	int iDelta = iIntactRCannon - iIntactLCannon;
	
	ang_z = MAX_HEEL_ANGLE * makefloat(iDelta)/makefloat(iRCannon);
	ang_x = 0.0; // TODO
	
	float_x = ang_x; float_z = ang_z;
	return true;
}

