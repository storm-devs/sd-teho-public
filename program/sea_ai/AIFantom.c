
#define INVALID_SHIP_TYPE			-1

ref Fantom_GetNextFantom()
{
	iNumFantoms++;
	return &Characters[FANTOM_CHARACTERS + iNumFantoms];
}

// -> ugeen 26.01.09
int Fantom_GenerateEncounterExt(string sGroupName, object oResult, int iEType, int iNumWarShips, int iNumMerchantShips, int iNation) 
{
	aref	aWar, aMerchant;
	ref		rEnc;
	int		i;
	int		iWarClassMax, iWarClassMin, iMerchantClassMax, iMerchantClassMin;

	makeref(rEnc, EncountersTypes[iEType]);
	makearef(aWar, rEnc.War);
	makearef(aMerchant, rEnc.Merchant);
	
	if(iEType == ENCOUNTER_TYPE_BARREL || iEType == ENCOUNTER_TYPE_BOAT)
	{
		ref rFantom = GetFantomCharacter(iNumFantoms);
		
		DeleteAttribute(rFantom, "relation");
		DeleteAttribute(rFantom, "abordage_twice");
		DeleteAttribute(rFantom, "QuestDate");
		DeleteAttribute(rFantom, "ransom");

		rFantom.SeaAI.Group.Name = sGroupName;
		iNumFantoms++;
		return 0;
	}
	
	int iRank = sti(pchar.Rank);
	trace("iRank = " + iRank + " iEtype " + iEType);
	Encounter_GetClassesFromRank(iEType, iRank, &iMerchantClassMin, &iMerchantClassMax, &iWarClassMin, &iWarClassMax);
	
	int iFantomIndex, iShipType;

	for (i=0; i<iNumMerchantShips; i++)
	{
		if(iNumShips + i >= MAX_SHIPS_ON_SEA) return i;
		iShipType = Fantom_GetShipTypeExt(iMerchantClassMin, iMerchantClassMax, "Merchant", sGroupName, "Trade", iEType, iNation );
		if (iShipType == INVALID_SHIP_TYPE) continue;
	}

	for (i=0; i<iNumWarShips; i++)
	{
		if(iNumShips + iNumMerchantShips + i >= MAX_SHIPS_ON_SEA) return iNumMerchantShips + i; 
		iShipType = Fantom_GetShipTypeExt(iWarClassMin, iWarClassMax, "War", sGroupName, "War", iEType, iNation);
		if (iShipType == INVALID_SHIP_TYPE) continue;
	}

	return iNumWarShips + iNumMerchantShips;
}

int Fantom_GenerateEncounter(string sGroupName, int iEType, int iNation) // --> взято из Новых Горизонтов с разрешения Питера Боелена
{
	aref	aWar, aMerchant;
	ref		rEnc;
	int		i, iNumMerchantShips, iNumWarShips;
	int		iWarClassMax, iWarClassMin, iMerchantClassMax, iMerchantClassMin;

	ref rCharacter = GetMainCharacter();

	makeref(rEnc, EncountersTypes[iEType]);
	makearef(aWar, rEnc.War);
	makearef(aMerchant, rEnc.Trade);
	
	if(iEType == ENCOUNTER_TYPE_BARREL || iEType == ENCOUNTER_TYPE_BOAT)
	{
		ref rFantom = GetFantomCharacter(iNumFantoms);
		
		DeleteAttribute(rFantom, "relation");
		DeleteAttribute(rFantom, "abordage_twice");
		DeleteAttribute(rFantom, "QuestDate");
		DeleteAttribute(rFantom, "ransom");

		rFantom.SeaAI.Group.Name = sGroupName;
		iNumFantoms++;
		return 0;
	}	

	iNumMerchantShips 	= MakeInt(aMerchant.ShipsMin) + rand(MakeInt(aMerchant.ShipsMax) - MakeInt(aMerchant.ShipsMin));
	iNumWarShips 		= MakeInt(aWar.ShipsMin) + rand(MakeInt(aWar.ShipsMax) - MakeInt(aWar.ShipsMin));

	int iRank = sti(rCharacter.Rank);
	trace("iRank = " + iRank + " iEtype " + iEType);
	
	Encounter_GetClassesFromRank(iEType, iRank, &iMerchantClassMin, &iMerchantClassMax, &iWarClassMin, &iWarClassMax);
	
	int iFantomIndex, iShipType;

	trace("Fantom_GenerateEncounter: type = "+ iEType +", # Mer = " + iNumMerchantShips + ", Mer MAX = " + iMerchantClassMax + ", Mer MIN = " + iMerchantClassMin + ", # War = " + iNumWarShips + ", War MAX = " + iWarClassMax + ", War MIN = " + iWarClassMin);
	
	for (i=0; i<iNumMerchantShips; i++)
	{
		if(iNumShips + i >= MAX_SHIPS_ON_SEA) return i;
		iShipType = Fantom_GetShipTypeExt(iMerchantClassMin, iMerchantClassMax, "Merchant", sGroupName, "Trade", iEType, iNation );
		if (iShipType == INVALID_SHIP_TYPE) continue;
	}

	for (i=0; i<iNumWarShips; i++)
	{
		if(iNumShips + iNumMerchantShips + i >= MAX_SHIPS_ON_SEA) return iNumMerchantShips + i; 
		iShipType = Fantom_GetShipTypeExt(iWarClassMin, iWarClassMax, "War", sGroupName, "War", iEType, iNation);
		if (iShipType == INVALID_SHIP_TYPE) continue;
	}

	return iNumWarShips + iNumMerchantShips;
}


int Fantom_GetShipTypeExt(int iClassMin, int iClassMax, string sShipType, string sGroupName, string sFantomType, int iEncounterType, int iNation)
{
	int iShips[50];
	int i, iShipsNum;
	iShipsNum = 0;
	aref aNation;
	string sAttr;
	bool bOk;

	for (i = SHIP_TARTANE; i <= SHIP_LSHIP_ENG; i++)  //энкаунтеры только до линкора, квестовые корабли отдельно
	{
		object rShip = GetShipByType(i);
		if (!CheckAttribute(rship, "class"))
		{
			trace ("bad ship is: " + rship.name);
		}
		int iClass = MakeInt(rShip.Class);
		
		if (iClass > iClassMin) { continue; }
		if (iClass < iClassMax) { continue; }
		if (sti(rShip.CanEncounter) != true) { continue; }
		if (sti(rShip.Type.(sShipType)) != true) { continue; }

		bOk = false;
		if(CheckAttribute(rShip, "nation"))
		{
			makearef(aNation, rShip.nation);
			int q = GetAttributesNum(aNation);
			for(int j = 0; j < q; j++)
			{
				sAttr = GetAttributeName(GetAttributeN(aNation, j)); 
				if(GetNationTypeByName(sAttr) == iNation && rShip.nation.(sAttr) == true ) bOk = true;
			}
		}	
		if(!bOk) { continue; }
		iShips[iShipsNum] = i;
		iShipsNum++;
	}
	if (iShipsNum == 0 ) 
	{
		Trace("Can't find ship type '" + sShipType + "' with ClassMin = " + iClassMin + " and ClassMax = " + iClassMax);
		return INVALID_SHIP_TYPE;
	}

	int iBaseShipType = iShips[rand(iShipsNum - 1)];

	ref rFantom = GetFantomCharacter(iNumFantoms);

	DeleteAttribute(rFantom, "relation");
	DeleteAttribute(rFantom, "abordage_twice");
	DeleteAttribute(rFantom, "QuestDate");
	DeleteAttribute(rFantom, "ransom");

	rFantom.SeaAI.Group.Name = sGroupName;
	rFantom.Ship.Mode = sFantomType;
	rFantom.Charge.Type = GOOD_BALLS;
	
	iNumFantoms++;
	
	int iRealShipType = GenerateShipExt( iBaseShipType, 0, rFantom );
	
	rFantom.Ship.Type = iRealShipType;
			
	return iRealShipType;
	
}
// -> ugeen 26.01.09

// return new added fantom character
// мктод этот походу левый, тк перекрывается в сиа.с
void Fantom_AddFantomCharacter(string sGroupName, int iShipType, string sFantomType, int iEncounterType)
{
	ref rFantom = GetFantomCharacter(iNumFantoms);
	
	DeleteAttribute(rFantom, "relation");
	DeleteAttribute(rFantom, "abordage_twice");
	DeleteAttribute(rFantom, "QuestDate");
	DeleteAttribute(rFantom, "ransom");

	rFantom.SeaAI.Group.Name = sGroupName;
	rFantom.Ship.Type = iShipType;
	rFantom.Ship.Mode = sFantomType;
	rFantom.Charge.Type = GOOD_BALLS;
	
	iNumFantoms++;
}
// на деле этот метод бесполезен, тк золото в сундуке генерится в др месте, а то что, в к3 тут были распределения опыта и команды вообще позорище.
void Fantom_SetRandomMoney(ref rFantom, string sFantomType)
{
	// clear money from character
	rFantom.Money = 0;

	//GenerateBootyItems(rFantom); // to_do del
	if (!CheckAttribute(rFantom, "ship.type")) return; // fix
	
    int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix
	
	// clear money from character
	rFantom.Money = 0;

	// ship class
	int iSClass = GetCharacterShipClass(rFantom);

	// add money
// boal 20.01.2004 -->
	switch (sFantomType)
	{
		case "trade":
			rFantom.Money = (10 - iSClass) * 100 + rand((10 - iSClass) * 800);
			return;
		break;
		case "war":
			rFantom.Money = (10 - iSClass) * 40 + rand((10 - iSClass) * 350);
			return;
		break;
		case "pirate":
		    rFantom.Money = (10 - iSClass) * 80 + rand((10 - iSClass) * 500);
			return;
		break;
	}
// boal 20.01.2004 <--
	//Trace("Fantom index = " + rFantom.index + ", group id = " + rFantom.SeaAI.Group.Name + ", have invalid encounter type = " + sFantomType);
}

// boal перенес из ВМЛ
int Fantom_CalcSkill(ref rMainCharacter, string sSkill, int iShipClass, int iSkillMin, int iSkillMax, int iSClass7, int iSClass6, int iSClass5, int iSClass4, int iSClass3, int iSClass2, int iSClass1)
// Stone-D : It was all backwards!
{
	int iSkill = GetSummonSkillFromName(rMainCharacter, sSkill);
    // boal 15.03.04 -->
    int minSkillLevel = 0;
	iSkill = iSkill + iSkillMin + rand(iSkillMax - iSkillMin);
	switch (iShipClass)
	{
		case 1: minSkillLevel =  iSClass1; break;
		case 2: minSkillLevel =  iSClass2; break;
		case 3: minSkillLevel =  iSClass3; break;
		case 4: minSkillLevel =  iSClass4; break;
		case 5: minSkillLevel =  iSClass5; break;
		case 6: minSkillLevel =  iSClass6; break;
		case 7: minSkillLevel =  iSClass7; break;
	}
	minSkillLevel = minSkillLevel*10; // приведение скила к 1-100
	
    if (iSkill < minSkillLevel)	iSkill = minSkillLevel;
    // boal 15.03.04 <--
	if (iSkill < 1)		    	iSkill = 1;
	if (iSkill > SKILL_MAX)     iSkill = SKILL_MAX;
	return iSkill;
}

void Fantom_SetCannons(ref rFantom, string sFantomType)
{
	int iSClass = GetCharacterShipClass(rFantom);
	ref rShip = GetRealShip(GetCharacterShipType(rFantom));

 	int iCannonsType = sti(rShip.Cannon);
	string sCannonType = "cannon";
	int iCaliber = sti(rShip.MaxCaliber);
    // boal 03.02.2004 -->
    switch(iCaliber)
	{
		case 3:
            iCaliber = 0;
		break;				
		case 6:
			iCaliber = 1;
		break;				
		case 8:
			iCaliber = 2;
		break;				
		case 12:
			iCaliber = 3;
		break;				
		case 16:
			iCaliber = 4;
		break;
		case 18:
			iCaliber = 5;
		break;
		case 20:
			iCaliber = 6;
		break;				
		case 24:
			iCaliber = 7;
		break;
		case 32:
			iCaliber = 8;
		break;
		case 36:
			iCaliber = 9;
		break;
		case 42:
			iCaliber = 10;
		break;	
	}
	if (iCaliber > 0)
	{
	   iCaliber = iCaliber - rand(1);
	}
	else
	{
		iCaliber = 0;
	}
	switch(iCaliber)
	{
		case 0:
			iCaliber = 3;
		break;
		case 1:
			iCaliber = 6;
		break;
		case 2:
			iCaliber = 8;
		break;
		case 3:
			iCaliber = 12;
		break;
		case 4:
			iCaliber = 16;
		break;
		case 5:
			iCaliber = 18;
		break;
		case 6:
			iCaliber = 20;
		break;
		case 7:
			iCaliber = 24;
		break;
		case 8:
			iCaliber = 32;
		break;
		case 9:
			iCaliber = 36;
		break;
		case 10:
			iCaliber = 42;
		break;	
	}
	if (iCaliber < 3)
	{
	   iCaliber = 3;
	}
    // boal 03.02.2004 <--
	if (iCaliber > sti(rShip.MaxCaliber)) { iCaliber=sti(rShip.MaxCaliber); }

	switch (sFantomType)
	{
        case "trade":
            // boal 20.01.2004 -->
		    if (rand(1000) < 700)
		    {
			   sCannonType = "cannon";
			}
			else
			{
			   sCannonType = "culverine";
			}
		break;

		case "war":
			if (rand(1000) < 200)
		    {
			   sCannonType = "cannon";
			}
			else
			{
			   sCannonType = "culverine";
			}
		    break;

		case "pirate":
			if (rand(1000) < 400)
		    {
			   sCannonType = "cannon";
			}
			else
			{
			   sCannonType = "culverine";
			}
		    break;
		    // boal 20.01.2004 <--
	}

	if (sti(rShip.Cannon) == CANNON_TYPE_NONECANNON)
	{
		rFantom.Ship.Cannons.Type = CANNON_TYPE_NONECANNON;
		return;
	}
	if (iCaliber == 42)
	{
	    sCannonType = "cannon";
	}
	rFantom.Ship.Cannons.Type = GetCannonByTypeAndCaliber(sCannonType, iCaliber);
}

void Fantom_SetSails(ref rFantom, string sFantomType)
{
	rFantom.Ship.Sails.Gerald = false;
	if (sFantomType == "war") rFantom.Ship.Sails.Gerald = true;
}

void Fantom_SetBalls(ref rFantom, string sFantomType)
{
	float fKBalls = 6 - GetCharacterShipClass(rFantom);

	if (fKBalls <= 0) fKBalls = 0.7; // баркас
	switch (sFantomType)
	{
		case "war":
			fKBalls = fKBalls * 1.7;
		break;
		case "trade":
			fKBalls = fKBalls * 0.8;
		break;
		case "pirate":
			fKBalls = fKBalls * 1.0;
		break;
	}
	if (GetCharacterShipClass(rFantom) == 1) fKBalls = fKBalls * 2.2; 
	if (GetCharacterShipClass(rFantom) == 2) fKBalls = fKBalls * 1.8; 
    // boal 20.01.2004 -->
	Fantom_SetCharacterGoods(rFantom, GOOD_BALLS,    	MakeInt(195 * fKBalls + rand(MakeInt(10 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_BOMBS,    	MakeInt(60  * fKBalls + rand(MakeInt(20 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_KNIPPELS, 	MakeInt(90  * fKBalls + rand(MakeInt(10 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_GRAPES,   	MakeInt(70  * fKBalls + rand(MakeInt(10 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_POWDER,   	MakeInt(350 * fKBalls + rand(MakeInt(30 * fKBalls))), 0);

	Fantom_SetCharacterGoods(rFantom, GOOD_SAILCLOTH, 	MakeInt(4 	* fKBalls + rand(MakeInt(10 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_PLANKS, 		MakeInt(3 	* fKBalls + rand(MakeInt(20 * fKBalls))), 0);

    Fantom_SetCharacterGoods(rFantom, GOOD_FOOD, 		MakeInt(20 	* fKBalls + rand(MakeInt(26 * fKBalls))), 0);
    Fantom_SetCharacterGoods(rFantom, GOOD_WEAPON, 		MakeInt(8  	* fKBalls + rand(MakeInt(13 * fKBalls))), 0);
    Fantom_SetCharacterGoods(rFantom, GOOD_RUM, 		MakeInt(4  	* fKBalls + rand(MakeInt(10 * fKBalls))), 0);
    Fantom_SetCharacterGoods(rFantom, GOOD_MEDICAMENT, 	MakeInt(4  	* fKBalls + rand(MakeInt(13 * fKBalls))), 0);
    // boal 20.01.2004 <--
}

void Fantom_SetGoods(ref rFantom, string sFantomType)
{
	int 	iShipClass = 6 - GetCharacterShipClass(rFantom);  // для баркаса = 0
	int 	i, iGoods, iRandGoods, iGoodName, iGoodQuantity;
	
	int 	iMultiply 		= 10;
	int 	iRandMultiply 	= 1;
	
	int 	iStart 	= GOOD_BALLS;
	int 	iFinish = GOOD_POWDER - iStart - 1;
	
	bool 	isLock; 
	bool 	bOk = false;
	
	float 	fModifikator = 0.0;
	
	int 	Nation = sti(rFantom.nation);
	
	if(CheckAttribute(rFantom, "situation")) bOk = true;
	
	switch (sFantomType)
	{
		case "war":
			iStart 	= GOOD_BALLS;
			if( CheckAttribute(rFantom, "RealEncounterType") && sti(rFantom.RealEncounterType) == ENCOUNTER_TYPE_WAR_PRIVATEER )
			{
				iFinish = GOOD_GOLD - iStart - 1;			
				iMultiply = (rand(3)+2) * (rand(iShipClass) + 1);	
			}
			else
			{
				iFinish = GOOD_BRICK - iStart - 1;
				iMultiply = (rand(5)+5) * (rand(iShipClass) + 1);		
			}
			iRandMultiply = 1 + rand(iShipClass);		
			iRandGoods = rand(5)+3; 
			for (i = 0; i < iRandGoods; i++)
			{
				if(rand(4) == 1) isLock = 1; 
				else			 isLock = 0; 	
				isLock = isLock || bOk; 
			    Fantom_SetCharacterGoods(rFantom, iStart + rand(iFinish), iMultiply * rand(iRandMultiply * 3), isLock);
			}

			iMultiply = GetCannonGoodsIdxByType(sti(rFantom.Ship.Cannons.Type));
			if (iMultiply != -1)
			{
				iRandMultiply = rand(6) - 2;  // 0..4 пушки
				if (iRandMultiply > 0)
				{
					Fantom_SetCharacterGoods(rFantom, iMultiply, iRandMultiply, 0);	
				}
			}			
		break;
		
		case "trade":
			iRandMultiply = 2 + rand(iShipClass);
			if (CheckAttribute(rFantom, "RealEncounterType"))
			{
				switch (sti(rFantom.RealEncounterType))
				{
					//  товары повседневного спроса
					case ENCOUNTER_TYPE_MERCHANT_SMALL 			:
						iGoods = rand(2) + 4; 
						fModifikator = 0.2 + 8.0/iGoods;
						iStart 	= GOOD_FOOD;
						iFinish = GOOD_POWDER - iStart - 1;						
					break;
					
					case ENCOUNTER_TYPE_MERCHANT_GUARD_SMALL 	:
						iGoods = rand(2) + 4; 
						fModifikator = 0.2 + 8.0/iGoods;
						iStart 	= GOOD_FOOD;
						iFinish = GOOD_POWDER - iStart - 1;						
					break;
					
					case ENCOUNTER_TYPE_ESCORT_SMALL 			:
						iGoods = rand(2) + 4; 
						fModifikator = 0.2 + 8.0/iGoods;
						iStart 	= GOOD_FOOD;
						iFinish = GOOD_POWDER - iStart - 1;	
					break;
					
					//  товары повседневного спроса + боеприпасы + колониальные товары
					case ENCOUNTER_TYPE_MERCHANT_MEDIUM 		:
						iGoods = rand(4) + 4; 
						fModifikator = 0.2 + 8.0/iGoods;
						iStart 	= GOOD_BALLS;
						iFinish = GOOD_POWDER - iStart - 1;					
					break;
					
					case ENCOUNTER_TYPE_MERCHANT_GUARD_MEDIUM 	:
						iGoods = rand(4) + 4; 
						fModifikator = 0.2 + 8.0/iGoods;
						iStart 	= GOOD_BALLS;
						iFinish = GOOD_POWDER - iStart - 1;					
					break;

					case ENCOUNTER_TYPE_ESCORT_MEDIUM 			:
						iGoods = rand(4) + 4; 
						fModifikator = 0.2 + 8.0/iGoods;
						iStart 	= GOOD_BALLS;
						iFinish = GOOD_POWDER - iStart - 1;
					break;
					
					// колониальные товары
					case ENCOUNTER_TYPE_MERCHANT_LARGE			:
						iGoods = rand(6) + 4; 
						fModifikator = 0.4 + 12.0/iGoods;
						iStart = GOOD_COFFEE;
						iFinish = GOOD_POWDER - iStart - 1;					
					break;
					
					case ENCOUNTER_TYPE_MERCHANT_GUARD_LARGE 	:
						iGoods = rand(6) + 4; 
						fModifikator = 0.4 + 12.0/iGoods;
						iStart = GOOD_COFFEE;
						iFinish = GOOD_POWDER - iStart - 1;					
					break;
					
					case ENCOUNTER_TYPE_ESCORT_LARGE 			:
						iGoods = rand(6) + 4; 
						fModifikator = 0.4 + 12.0/iGoods;
						iStart = GOOD_COFFEE;
						iFinish = GOOD_POWDER - iStart - 1;
					break;
					
					// привозные товары из Европы + колониальные товары
					case ENCOUNTER_TYPE_MERCHANT_CROWN 			:
						iGoods = rand(3) + 3; 
						fModifikator = 0.4 + 12.0/iGoods;
						iStart = GOOD_COFFEE;
						iFinish = GOOD_SHIPSILK - iStart - 1;
					break;
					
					//  уникальные товары + коронные товары
					case ENCOUNTER_TYPE_MERCHANT_EXPEDITION 	:
						iGoods = rand(2) + 2; 
						fModifikator = 0.4 + 12.0/iGoods;
						iStart = GOOD_SHIPSILK;
						if(Nation == SPAIN) iFinish = GOOD_CANNON_3 - iStart - 1; // золото и серебро только у испанцев !!!!
						else 				iFinish = GOOD_GOLD - iStart - 1;
					break;
				}
				
				for (i = 0; i < iGoods; i++)
				{
					iGoodName = iStart + rand(iFinish);
					iGoodQuantity = makeint(20 + fModifikator * iMultiply * (2 + rand(iRandMultiply * 3)));
					
					// уникальные и коронные товары
					if(iGoodName >= GOOD_SHIPSILK && iGoodName <= GOOD_SILVER)
					{
						iGoodQuantity = makeint(rand(25) + rand(15) +  1.5 * (10 - MOD_SKILL_ENEMY_RATE) + 15 * (7 - iShipClass) );
						if(iGoodQuantity < 1) iGoodQuantity = 1;
						isLock = 1; 
						Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);			
					}
/*					
					if(iGoodName == GOOD_GOLD || iGoodName == GOOD_SILVER)
					{
						iRandMultiply = 2 + rand(iShipClass); // max 8
						iMultiply = (rand(10)+ 10) * (rand(iShipClass) + 2); 	// max 20 * 8 = 160
						iGoodQuantity = makeint((fModifikator * 50 + iMultiply * (1 + rand(iRandMultiply * 3)))/(1.2 * MOD_SKILL_ENEMY_RATE));
						if(iGoodQuantity < 1) iGoodQuantity = 1;
						isLock = 1; 
						Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);			
					}
*/					
					else
					{
						if(rand(4) == 1) isLock = 1; 
						else			 isLock = 0; 	
						isLock = isLock || bOk; 
						Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
					}	
				}
			}
		break;
		
		case "pirate": 
			fModifikator = 1.2;
			iMultiply = (rand(10)+3) * (rand(iShipClass) + 1);
			iRandMultiply = 2 + rand(iShipClass);
			iRandGoods = rand(3) + 1;
			
			iStart 	= GOOD_BALLS;
			iFinish = GOOD_POWDER - iStart - 1;
			
			if (CheckAttribute(rFantom, "RealEncounterType"))
			{
				switch (sti(rFantom.RealEncounterType))
				{
					case ENCOUNTER_TYPE_PIRATE_SMALL 	: // контрабандисты
						iRandGoods = rand(3) + 1;
						iStart 	= GOOD_BALLS;
						iFinish = GOOD_COFFEE - iStart - 1;
					break;
					
					case ENCOUNTER_TYPE_PIRATE_MEDIUM 	: // "прибрежные крысы"
						iRandGoods = rand(4) + 1;
						iStart 	= GOOD_BALLS;
						iFinish = GOOD_BRICK  - iStart - 1;
					break;
					
					case ENCOUNTER_TYPE_PIRATE_LARGE 	: // рейдер
						iRandGoods = rand(5) + 1;
						iStart 	= GOOD_BALLS;
						iFinish = GOOD_BRICK  - iStart - 1;
					break;
					
					case ENCOUNTER_TYPE_PIRATE_SCOUNDREL : // "отморозок"
						iRandGoods = rand(6) + 1;
						iStart = GOOD_FOOD;
						iFinish = GOOD_GOLD - iStart - 1;
					break;
				}
			}
			
			for (i = 0; i < iRandGoods; i++)
			{
				iGoodName = iStart + rand(iFinish);
				iGoodQuantity = makeint(20 + fModifikator * iMultiply * (1+rand(iRandMultiply * 3)));

				if(rand(4) == 1) isLock = 1; 
				else			 isLock = 0; 	
				isLock = isLock || bOk; 
				Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
			}			
			
			iMultiply = GetCannonGoodsIdxByType(sti(rFantom.Ship.Cannons.Type));
			if (iMultiply != -1)
			{
				iRandMultiply = rand(6) - 2;  // 0..4 пушки
				if (iRandMultiply > 0)
				{
					Fantom_SetCharacterGoods(rFantom, iMultiply, iRandMultiply, 0);	
				}
			}			
		break;
		
	}	
	RecalculateCargoLoad(rFantom);
}

// доработал метод, теперь возвращает сколько взял
int Fantom_SetCharacterGoods(ref rFantom, int iGoods, int iQuantity, bool isLock)
{
	if (iQuantity == 0) { return 0; }

	if(iGoods > GOODS_QUANTITY - 1 || iGoods < 0) //fix
	{ 
		trace("rChar " + rFantom.id +"     goods :" + iGoods + " out of order" ); return 0; 
	}
	string sGood = Goods[iGoods].name;
	int iFreeQuantity = GetGoodQuantityByWeight( iGoods, GetCargoFreeSpace(rFantom) );
	if (iFreeQuantity < 0) { iFreeQuantity = 0; }

	if (iQuantity > iFreeQuantity) { iQuantity = iFreeQuantity; }
	
	if (CheckAttribute(rFantom,"Ship.Cargo.Goods." + sGood))
	{
		rFantom.Ship.Cargo.Goods.(sGood) = sti(rFantom.Ship.Cargo.Goods.(sGood)) + iQuantity;
	}
    else
	{	
		rFantom.Ship.Cargo.Goods.(sGood) = iQuantity;
	}
	
	if(isLock) {rFantom.Ship.Cargo.Goods.(sGood).Lock = true;}
	RecalculateCargoLoad(rFantom);
	return iQuantity;
}

// опыт матросов
void Fantom_SetRandomCrewExp(ref rFantom, string sFantomType)
{
    if (!CheckAttribute(rFantom, "ship.type")) return; // fix
    
	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix
	
	// ship class
	int iSClass = GetCharacterShipClass(rFantom);

	switch (sFantomType)
	{
		case "trade":
			rFantom.Ship.Crew.Exp.Sailors   = 20 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(70);
			rFantom.Ship.Crew.Exp.Cannoners = 20 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(70);
			rFantom.Ship.Crew.Exp.Soldiers  = 20 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(70);
		break;
		case "war":
			rFantom.Ship.Crew.Exp.Sailors   = 30 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(60);
			rFantom.Ship.Crew.Exp.Cannoners = 30 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(60);
			rFantom.Ship.Crew.Exp.Soldiers  = 30 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(60);
		break;
		case "pirate":
		    rFantom.Ship.Crew.Exp.Sailors   = 35 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(55);
			rFantom.Ship.Crew.Exp.Cannoners = 35 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(55);
			rFantom.Ship.Crew.Exp.Soldiers  = 35 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(55);
		break;
	}
}

void Fantom_SetQuestSitiation(ref rFantom, string sFantomType)
{
	string sSituation;
	bool CanGenerateSituation = false;
	if (!CheckAttribute(rFantom, "ship.type")) return; 
    
	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; 
	
	switch (sFantomType)
	{
		case "pirate": // пираты или ДУ
			if(rand(120) < 3) 
			{
				sSituation = "Explosion";
				CanGenerateSituation = true;
			}	
		break;
		case "hunter": // ОЗГ
			if(rand(120) < 3) 
			{
				sSituation = "Explosion";
				CanGenerateSituation = true;
			}	
		break;
		case "war": // военные корабли
			if(rand(120) < 3) 
			{
				sSituation = "Explosion";
				CanGenerateSituation = true;
			}	
		break;
		case "trade": // торговцы
			if(rand(120) < 3) 
			{
				sSituation = "Epidemy";
				CanGenerateSituation = true;
			}	
		break;		
	}
	if(CanGenerateSituation)
	{
		rFantom.situation = sSituation;
		rFantom.situation.type = sFantomType;
		rFantom.DontRansackCaptain = true; // Врагу не сдается наш гордый Варяг !!
	}
}

void Fantom_SetDamage(ref rFantom, string sFantomType)
{
	if (!CheckAttribute(rFantom, "ship.type")) return; // fix
    
	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix

	switch (sFantomType)
	{
		case "pirate":
			if(rand(100) < 5)
			{
				GenerateShipDamageParameters(rFantom);
			}	
		break;
		case "hunter":
			if(rand(100) < 5)
			{
				GenerateShipDamageParameters(rFantom);
			}			
		break;
		case "trade" :
			if(rand(100) < 10)
			{
				GenerateShipDamageParameters(rFantom);
			}			
		break;
		case "war"	 :
			if(rand(100) < 3)
			{
				GenerateShipDamageParameters(rFantom);
			}			
		break;
	}
}

void GenerateShipDamageParameters(ref rFantom)
{
	int i = rand(100);
	int j = rand(2);
	
	if(i < 33) 
	{
		if( j == 0 ) Fantom_SetDamageHull(rFantom);
		if( j == 1 ) Fantom_SetDamageCrew(rFantom);
		if( j == 2 ) Fantom_SetDamageCannons(rFantom);
		return;
	}	
	if((i >= 33) && (i < 66))
	{
		if( j == 0 )
		{
			Fantom_SetDamageHull(rFantom);
			Fantom_SetDamageCrew(rFantom);
		}
		if( j == 1 )
		{
			Fantom_SetDamageHull(rFantom);
			Fantom_SetDamageCannons(rFantom);
		}
		if( j == 2 )
		{
			Fantom_SetDamageCrew(rFantom);
			Fantom_SetDamageCannons(rFantom);
		}
		return;
	}
	if((i >= 66))
	{
		Fantom_SetDamageHull(rFantom);
		Fantom_SetDamageCrew(rFantom);
		Fantom_SetDamageCannons(rFantom);
		return;	
	}
}

void Fantom_SetDamageHull(ref rFantom)
{
	int nMaxDamageProcent = rand(20) + 20;
	int nHP = GetCurrentShipHP( rFantom );
	nHP -= nHP * nMaxDamageProcent / 100;
	rFantom.ship.hp = nHP; 
}

void Fantom_SetDamageCrew(ref rFantom)
{
	int nMaxDamageProcent = rand(10) + 15;
	int nCrew = GetCrewQuantity( rFantom );
	nCrew -= nCrew * nMaxDamageProcent / 100;
	SetCrewQuantity(rFantom, nCrew);
}

void Fantom_SetDamageCannons(ref rFantom)
{
	aref 	refShip;
	string 	sAttr, sBort;
	int 	i;
	
	makearef(refShip, rFantom.Ship);
	ref rRealShip = GetRealShip(GetCharacterShipType(rFantom));
	
	int iCannonDiff = 0;	
	int rCannonQty = GetBortIntactCannonsNum(rFantom, "cannonr", sti(rRealShip.rcannon));
	int lCannonQty = GetBortIntactCannonsNum(rFantom, "cannonl", sti(rRealShip.lcannon));

	if(rCannonQty > 4)
	{
		iCannonDiff = rand(1) + 1;
		sBort		= "cannonr";
		if(iCannonDiff > 0)
		{
			for (i = 0; i < iCannonDiff; i++)
			{
				sAttr = "c" + i;	
				if (CheckAttribute(rFantom, "Ship.Cannons.Borts." + sBort + ".damages"))
				{
					rFantom.Ship.Cannons.Borts.(sBort).damages.(sAttr) 		= 1.0; 			
				}	
			}
		}	
	}
	if(lCannonQty > 4)
	{
		iCannonDiff = rand(1) + 1;		
		sBort		= "cannonl";
		if(iCannonDiff > 0)
		{
			for (i = 0; i < iCannonDiff; i++)
			{
				sAttr = "c" + i;
				if (CheckAttribute(rFantom, "Ship.Cannons.Borts." + sBort + ".damages"))
				{	
					rFantom.Ship.Cannons.Borts.(sBort).damages.(sAttr) 		= 1.0; 
				}	
			}
		}	
	}			
}

// ugeen 03.06.09 - вероятность корабликов быть проапгрейженными на 1, 2 ...  все параметры
void Fantom_SetUpgrade(ref rFantom, string sFantomType)
{
	if (!CheckAttribute(rFantom, "ship.type")) return; // fix
    
	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix
	
	// ship class
	int iSClass = GetCharacterShipClass(rFantom);
	int i = rand(100);
	
	switch (sFantomType)
	{
		case "pirate":   // апгрейдим параметр(ы)  шипа пиратских случаек
			if(i < (6 - iSClass)*4)  
			{
				GenerateShipUpgradeParameters(rFantom);
			}
		break;
		case "hunter":   // апгрейдим параметр(ы) шипа ДУ или ОЗГов
			if(i < ((6 - iSClass)*4 +10)) 
			{
				GenerateShipUpgradeParameters(rFantom);
			}			
		break;
		case "war":   // апгрейдим параметр(ы)  военных кораблей
			if(i < (6 - iSClass)*4)  
			{
				GenerateShipUpgradeParameters(rFantom);
			}
		break;
		case "trade":   // апгрейдим параметр(ы)  торгашей
			if(i < (6 - iSClass)*4 +10)  
			{
				GenerateShipUpgradeParameters(rFantom);
			}
		break;
	}
}

int GetPossibilityCannonsUpgrade(ref rFantom, bool isUpgrade)
{
	ref 	shTo;
	
	shTo = &RealShips[sti(rFantom.Ship.Type)];

	int  cannonQ       = sti(shTo.CannonsQuantity);		
	int	 cannonMaxQ;	
	int	 cannonMinQ    = sti(shTo.CannonsQuantityMin); 
	
	if(CheckAttribute(shTo,"CannonsQuantityMax")) 	cannonMaxQ = sti(shTo.CannonsQuantityMax); 
	else
	{		
		cannonMaxQ = sti(shTo.CannonsQuantity); 
		shTo.CannonsQuantityMax = sti(shTo.CannonsQuantity);
	}	
	
	//trace("cannonQ :" + cannonQ + " cannonMaxQ :" + cannonMaxQ + " cannonMinQ :" + cannonMinQ);
	
	if(isUpgrade) 
	{
		if( (cannonMaxQ - cannonQ) == 0) return 0;		// максимум орудий - апгрейд невозможен
	}	
	else	
	{
		if( (cannonQ - cannonMinQ) == 0) return 0;		// минимум орудий - даунгрейд невозможен
	}		
	return 1;
}

void GenerateShipUpgradeParameters(ref rFantom)
{
	int iNation = sti(rFantom.nation);
	
	switch (iNation)
	{
		case ENGLAND  		: // SW: SpeedRate&fWindAgainstSpeed
			if(rand(1) == 0) 
			{
				UpgradeShipParameter(rFantom, "SpeedRate");
				DegradeShipParameter(rFantom, "WindAgainstSpeed");
			}	
			else
			{
				UpgradeShipParameter(rFantom, "WindAgainstSpeed");
				DegradeShipParameter(rFantom, "SpeedRate");
			}
		break;
		
		case FRANCE	  		: // TM: TurnRate&MinCrew
			if(rand(1) == 0) 
			{
				UpgradeShipParameter(rFantom, "TurnRate");
				DegradeShipParameter(rFantom, "MinCrew");
			}
			else
			{
				UpgradeShipParameter(rFantom, "MinCrew");
				DegradeShipParameter(rFantom, "TurnRate");
			}
		break;
		
		case SPAIN	  		: // CC: Cannons&Capacity
			if(rand(1) == 0) 
			{
				if(GetPossibilityCannonsUpgrade(rFantom, true) > 0)
				{
					UpgradeShipParameter(rFantom, "Cannons");
					DegradeShipParameter(rFantom, "Capacity");
				}	
			}
			else
			{
				if(GetPossibilityCannonsUpgrade(rFantom, false) > 0)
				{
					UpgradeShipParameter(rFantom, "Capacity");
					DegradeShipParameter(rFantom, "Cannons");
				}	
			}
		break;
		
		case HOLLAND  		: // HP&MMaxCrew
			if(rand(1) == 0) 
			{
				UpgradeShipParameter(rFantom, "HP");
				DegradeShipParameter(rFantom, "MaxCrew");
			}
			else
			{
				UpgradeShipParameter(rFantom, "MaxCrew");
				DegradeShipParameter(rFantom, "HP");
			}
		break;
		
		case PIRATE			:
			switch(rand(3))
			{
				case 0: 
					if(rand(1) == 0) 
					{
						UpgradeShipParameter(rFantom, "SpeedRate");
						DegradeShipParameter(rFantom, "WindAgainstSpeed");
					}	
					else
					{
						UpgradeShipParameter(rFantom, "WindAgainstSpeed");
						DegradeShipParameter(rFantom, "SpeedRate");
					}				
				break;
				case 1: 
					if(rand(1) == 0) 
					{
						UpgradeShipParameter(rFantom, "TurnRate");
						DegradeShipParameter(rFantom, "MinCrew");
					}
					else
					{
						UpgradeShipParameter(rFantom, "MinCrew");
						DegradeShipParameter(rFantom, "TurnRate");
					}					
				break;
				case 2: 
					if(rand(1) == 0) 
					{
						if(GetPossibilityCannonsUpgrade(rFantom, true) > 0)
						{
							UpgradeShipParameter(rFantom, "Cannons");
							DegradeShipParameter(rFantom, "Capacity");
						}	
					}
					else
					{
						if(GetPossibilityCannonsUpgrade(rFantom, false) > 0)
						{
							UpgradeShipParameter(rFantom, "Capacity");
							DegradeShipParameter(rFantom, "Cannons");
						}	
					}				
				break;
				case 3: 
					if(rand(1) == 0) 
					{
						UpgradeShipParameter(rFantom, "HP");
						DegradeShipParameter(rFantom, "MaxCrew");
					}
					else
					{
						UpgradeShipParameter(rFantom, "MaxCrew");
						DegradeShipParameter(rFantom, "HP");
					}				
				break;
			}
		break;
	}
}

void DegradeShipParameter(ref _chr, string _param)
{
	ref 	shTo;
	aref 	refShip;
	int		iCannonDiff;
	int		i;
	string  attr; 
	
	shTo = &RealShips[sti(_chr.Ship.Type)];
	makearef(refShip, _chr.Ship);
	
	switch(_param)
	{
		case "SpeedRate":
			shTo.SpeedRate = (stf(shTo.SpeedRate) - stf(shTo.SpeedRate)* 0.15);
			shTo.DontTuning.SpeedRate = true;		
		break;
		
		case "TurnRate":
			shTo.TurnRate = (stf(shTo.TurnRate) - stf(shTo.TurnRate) * 0.15);
			shTo.DontTuning.TurnRate = true;
		break;
		
		case "HP":
			shTo.HP = sti(shTo.HP) - makeint(sti(shTo.HP) * 0.15);
			shTo.DontTuning.HP = true;
		break;
		
		case "WindAgainstSpeed":
			shTo.WindAgainstSpeed   = FloatToString(stf(shTo.WindAgainstSpeed) - 0.15 * stf(shTo.WindAgainstSpeed), 2);
			shTo.DontTuning.WindAgainst = true;
		break;
		
		case "Capacity":
			shTo.Capacity = sti(shTo.Capacity) - makeint(sti(shTo.Capacity) * 0.15);
			shTo.DontTuning.Capacity = true;
		break;
		
		case "MaxCrew":
			shTo.MaxCrew = sti(shTo.MaxCrew) - makeint(sti(shTo.MaxCrew) * 0.15);
			shTo.DontTuning.MaxCrew = true;	
		break;
		
		case "MinCrew":
			shTo.MinCrew = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew) * 0.15);
			if(sti(shTo.MinCrew) < 1) shTo.MinCrew = 1;
			shTo.DontTuning.MinCrew = true;	
		break;
		
		case "Cannons":		
			if(GetPossibilityCannonsUpgrade(_chr, false) > 0 && CheckAttribute(refShip,"CannonDiff"))
			{
				iCannonDiff = sti(refShip.CannonDiff);
				iCannonDiff += 1;
								
				for (i = 0; i < sti(shTo.cannonr); i++)
				{
					attr = "c" + i;					
					if(i >= sti(shTo.cannonr) - iCannonDiff)	
					{
						refShip.Cannons.Borts.cannonr.damages.(attr) = 2.0; 
					}
				}	
				for (i = 0; i < sti(shTo.cannonl); i++)
				{
					attr = "c" + i;
					if(i >= sti(shTo.cannonl) - iCannonDiff)	
					{
						refShip.Cannons.Borts.cannonl.damages.(attr) = 2.0; 
					}
				}	
				shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
				shTo.CannonsQuantity = sti(shTo.Cannons);
		
				refShip.Cannons = sti(shTo.Cannons);
				refShip.CannonDiff = iCannonDiff;

				shTo.DontTuning.Cannon = true;		
			}							
		break;
	}
}

void UpgradeShipParameter(ref _chr, string _param)
{
	ref 	shTo;
	aref 	refShip;
	int 	iCaliber;
	int		iCannonDiff;
	int		i;
	string  attr; 
	
	shTo = &RealShips[sti(_chr.Ship.Type)];
	makearef(refShip, _chr.Ship);
	
	switch(_param)
	{
		case "SpeedRate":		
			if(!CheckAttribute(shTo, "Tuning.SpeedRate"))
			{
				if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
				}		
				shTo.Tuning.SpeedRate = true;		
			}				
		break;		
		
		case "TurnRate":		
			if(!CheckAttribute(shTo, "Tuning.TurnRate"))
			{
				if(!CheckAttribute(shTo, "Bonus_TurnRate"))
				{
					shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
				}
				else
				{
					shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
				}	
				shTo.Tuning.TurnRate = true;
			}				
		break;
		
		case "HP":		
			if(!CheckAttribute(shTo, "Tuning.HP"))
			{
				if(!CheckAttribute(shTo, "Bonus_HP"))
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
				}
				else
				{
					shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
				}	
				shTo.Tuning.HP = true;
			}				
		break;
		
		case "WindAgainstSpeed":
			if(!CheckAttribute(shTo, "Tuning.WindAgainst"))
			{
				shTo.WindAgainstSpeed   = FloatToString(stf(shTo.WindAgainstSpeed) +  0.20 * stf(shTo.WindAgainstSpeed), 2);
				shTo.Tuning.WindAgainst = true;
			}				
		break;
		
		case "Capacity":		
			if(!CheckAttribute(shTo, "Tuning.Capacity"))
			{
				if(!CheckAttribute(shTo, "Bonus_Capacity"))
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
				}
				else
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
				}					
				shTo.Tuning.Capacity = true;
			}				
		break;
		
		case "MaxCrew":		
			if(!CheckAttribute(shTo, "Tuning.MaxCrew"))
			{
				shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
				shTo.Tuning.MaxCrew = true;				
			}				
		break;
		
		case "MinCrew":
			if(!CheckAttribute(shTo, "Tuning.MinCrew"))
			{
				shTo.MinCrew        = sti(shTo.MinCrew) * 2;
				shTo.Tuning.MinCrew = true;
			}	
		break;
		
		case "Cannons":					
			if(!CheckAttribute(shTo, "Tuning.Cannon") && GetPossibilityCannonsUpgrade(_chr, true) > 0)
			{
				iCannonDiff = sti(refShip.CannonDiff);
				iCannonDiff -= 1;
								
				for (i = 0; i < sti(shTo.cannonr); i++)
				{
					attr = "c" + i;										
					
					if(i < (sti(shTo.cannonr) - iCannonDiff) )	
					{
						if( stf(refShip.Cannons.Borts.cannonr.damages.(attr)) > 1.0 )
						{
							refShip.Cannons.Borts.cannonr.damages.(attr) = 0.0; 
						}	
					}					
				}	
				for (i = 0; i < sti(shTo.cannonl); i++)
				{
					attr = "c" + i;
					if(i < (sti(shTo.cannonl) - iCannonDiff) )	
					{
						if( stf(refShip.Cannons.Borts.cannonl.damages.(attr)) > 1.0 )
						{
							refShip.Cannons.Borts.cannonl.damages.(attr) = 0.0; 
						}	
					}										
				}	
				
				shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
				shTo.CannonsQuantity = sti(shTo.Cannons);
		
				refShip.Cannons = sti(shTo.Cannons);
				refShip.CannonDiff = iCannonDiff;
			
				shTo.Tuning.Cannon = true;		
			}							
		break;
	}
}
// ugeen

// eddy. подбор типа корабля для фантома от ранга и нац. принадлежности
void SetShipToFantom(ref _chr, string _type, bool _setgoods)
{
	int ShipType;
	int Nation = sti(_chr.nation);
	int Rank = sti(pchar.rank);
	switch (_type)
	{
		case "trade":		
			if (Rank < 11)
			{
				ShipType = RandFromFiveDight(SHIP_BARQUE, SHIP_SCHOONER, SHIP_BARKENTINE, SHIP_SHNYAVA, SHIP_FLEUT);
			}
			if (Rank >= 11 && Rank <= 20)
			{
				ShipType = RandFromThreeDight(SHIP_CARAVEL, SHIP_PINNACE, SHIP_CARACCA);
			}
			if (Rank > 20)
			{
				if (Nation == SPAIN) ShipType = RandFromThreeDight(SHIP_CARACCA, SHIP_NAVIO, SHIP_GALEON_H);
				else				 ShipType = RandFromThreeDight(SHIP_CARACCA, SHIP_NAVIO, SHIP_EASTINDIAMAN);
			}
		break;
		case "pirate":
			if (Rank < 4)
			{
				ShipType = SHIP_LUGGER;
			}			
			if (Rank >= 4 && Rank < 11)
			{
				ShipType = RandFromThreeDight(SHIP_SLOOP, SHIP_BRIGANTINE, SHIP_BRIG);
			}
			if (Rank >= 11 && Rank <= 20)
			{
				ShipType = RandFromThreeDight(SHIP_SCHOONER_W, SHIP_GALEON_L, SHIP_CORVETTE);
			}
			if (Rank > 20)
			{
				ShipType = RandFromThreeDight(SHIP_CORVETTE, SHIP_GALEON_H, SHIP_LINESHIP);
			}
		break;

		case "war":
			if (Rank < 11)
			{
				ShipType = RandFromThreeDight(SHIP_CAREERLUGGER, SHIP_LUGGER, SHIP_SLOOP);
			}
			if (Rank >= 11 && Rank <= 20)
			{
				switch (Nation)
				{
					case ENGLAND  : ShipType = RandFromThreeDight(SHIP_BRIG, SHIP_GALEON_L, SHIP_CORVETTE); break; 
					case FRANCE	  : ShipType = RandFromThreeDight(SHIP_SCHOONER_W, SHIP_GALEON_L, SHIP_CORVETTE); break; 					
					case SPAIN	  : ShipType = RandFromThreeDight(SHIP_BRIGANTINE, SHIP_GALEON_L, SHIP_XebekVML); break; 					
					case HOLLAND  : ShipType = RandFromFiveDight(SHIP_SCHOONER_W, SHIP_GALEON_L, SHIP_CORVETTE, SHIP_POLACRE, SHIP_SCHOONER_W); break; 
				}						
			}
			if (Rank > 20)
			{
				switch (Nation)
				{
					case ENGLAND  : ShipType = RandFromThreeDight(SHIP_FRIGATE, SHIP_FRIGATE_H, SHIP_LINESHIP); break; 
					case FRANCE	  : ShipType = RandFromThreeDight(SHIP_FRIGATE, SHIP_FRIGATE_H, SHIP_LINESHIP); break; 					
					case SPAIN	  : ShipType = RandFromFiveDight(SHIP_POLACRE, SHIP_GALEON_H, SHIP_FRIGATE_H, SHIP_GALEON_H, SHIP_LINESHIP); break; 					
					case HOLLAND  : ShipType = RandFromThreeDight(SHIP_FRIGATE, SHIP_FRIGATE_H, SHIP_LINESHIP); break; 
				}						
			}
		break;
	}
	_chr.Ship.Type = GenerateShipExt(ShipType, true, _chr);
	SetRandomNameToShip(_chr);
    SetBaseShipData(_chr);
    SetCrewQuantityFull(_chr);
    Fantom_SetCannons(_chr, _type);
    Fantom_SetBalls(_chr, _type);

	if(_type == "pirate")
	{
		Fantom_SetUpgrade(_chr, "pirate");
	}
	
    if (_setgoods)
    {
        Fantom_SetGoods(_chr, _type);
    }
}
