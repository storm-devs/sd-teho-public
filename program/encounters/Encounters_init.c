void Enc_ExcludeNation(ref rEnc, int iNation)
{
	string sNation = Nations[iNation].Name;
	rEnc.Nation.Exclude.(sNation) = true;
}

void Enc_AddShips(ref rEnc, string sEType, int iShipsMin, int iShipsMax)
{
	rEnc.(sEType).ShipsMin = iShipsMin;		
	rEnc.(sEType).ShipsMax = iShipsMax;
}

void Enc_AddClasses(ref rEnc, int iRank, int iMClassMin, int iMClassMax, int iWClassMin, int iWClassMax)
{
	string sRank = "Rank." + iRank;
	rEnc.(sRank).0 = iMClassMin; rEnc.(sRank).1 = iMClassMax;
	rEnc.(sRank).2 = iWClassMin; rEnc.(sRank).3 = iWClassMax;
}

void InitEncounters()
{
	int i;
	ref rEnc;

	for (i=0; i<MAX_ENCOUNTER_TYPES; i++)
	{
		makeref(rEnc, EncountersTypes[i]);
		rEnc.Index = i;
		rEnc.Chance = 100;
		rEnc.Skip = false;
		rEnc.MinRank = 1;
		rEnc.MaxRank = 1000;
		rEnc.Merchant.ShipsMin = 0;		
		rEnc.Merchant.ShipsMax = 0;
		rEnc.War.ShipsMin = 0;			
		rEnc.War.ShipsMax = 0;
		rEnc.Type = ENCOUNTER_TRADE;
	}
	////  boal баг фикс для квестовых, а то генерились в К3
    makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_ALONE]);
 	rEnc.Chance = 0;
	rEnc.Skip   = true;
	
	///////////////////////////////////////////////////////////////////////////////////////
	/// 1-2 торговца 5-6 класса.
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_SMALL]);
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.MinRank = 1;
	rEnc.MaxRank = 1000;
	rEnc.MerchantType = MER_TYPE_1; // каботажник
	rEnc.worldMapShip = "sloop";
	Enc_AddShips(rEnc, "Merchant", 1, 2);
	Enc_ExcludeNation(rEnc, PIRATE);

	Enc_AddClasses(rEnc, 1, 5, 6, 0, 0);
	Enc_AddClasses(rEnc, 1000,5, 6, 0, 0);
	
	///////////////////////////////////////////////////////////////////////////////////////
	/// 2-4 торговца 4-6 класса.
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_MEDIUM]);
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.MinRank = 1;
	rEnc.MaxRank = 1000;
	rEnc.MerchantType = MER_TYPE_2; 
	rEnc.worldMapShip = "bark";
	Enc_AddShips(rEnc, "Merchant", 2, 4);
	Enc_ExcludeNation(rEnc, PIRATE);

	Enc_AddClasses(rEnc, 1, 4, 6, 0, 0);
	Enc_AddClasses(rEnc, 1000,4, 6, 0, 0);

	///////////////////////////////////////////////////////////////////////////////////////
	/// 3-5 торговца 3-5 класса.
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_LARGE]);
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.MinRank = 1;
	rEnc.MaxRank = 1000;
	rEnc.MerchantType = MER_TYPE_3; 
	rEnc.worldMapShip = "galleon";
	Enc_AddShips(rEnc, "Merchant", 3, 5);
	Enc_ExcludeNation(rEnc, PIRATE);

	Enc_AddClasses(rEnc, 1, 3, 5, 0, 0);
	Enc_AddClasses(rEnc, 1000,3, 5, 0, 0);
		
	///////////////////////////////////////////////////////////////////////////////////////
	/// 1-3 торговца 4-5 класса плюс 1 корабль охраны
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_GUARD_SMALL]);
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.MinRank = 1;
	rEnc.MaxRank = 1000;
	rEnc.worldMapShip = "sloop";
	rEnc.MerchantType = MER_TYPE_1; // каботажник
	Enc_AddShips(rEnc, "Merchant", 1, 3);
	Enc_AddShips(rEnc, "War", 1, 1);
	Enc_ExcludeNation(rEnc, PIRATE);

	Enc_AddClasses(rEnc, 1, 4, 5, 4, 5);
	Enc_AddClasses(rEnc, 1000,4, 5, 4, 5);
	
	///////////////////////////////////////////////////////////////////////////////////////
	/// 2-3 торговца 4-5 класса плюс 1-2 корабля охраны
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_GUARD_MEDIUM]);
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.MinRank = 1;
	rEnc.MaxRank = 1000;
	rEnc.MerchantType = MER_TYPE_2; 
	rEnc.worldMapShip = "bark";
	Enc_AddShips(rEnc, "Merchant", 2, 3);
	Enc_AddShips(rEnc, "War", 1, 2);
	Enc_ExcludeNation(rEnc, PIRATE);

	Enc_AddClasses(rEnc, 1, 4, 5, 3, 5);
	Enc_AddClasses(rEnc, 1000,4, 5, 3, 5);
	
	///////////////////////////////////////////////////////////////////////////////////////
	/// 3-5 торговца 3-4 класса плюс 1-2 корабля охраны
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_GUARD_LARGE]);
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.MinRank = 5;
	rEnc.MaxRank = 1000;
	rEnc.MerchantType = MER_TYPE_3; 
	rEnc.worldMapShip = "galleon";
	Enc_AddShips(rEnc, "Merchant", 3, 5);
	Enc_AddShips(rEnc, "War", 1, 2);
	Enc_ExcludeNation(rEnc, PIRATE);

	Enc_AddClasses(rEnc, 1, 3, 4, 2, 4);
	Enc_AddClasses(rEnc, 1000,3, 4, 2, 4);
	
	///////////////////////////////////////////////////////////////////////////////////////
	/// 2-3 торговца 3-4 класса плюс 1-2 корабля охраны
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_ESCORT_SMALL]);
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.MinRank = 1;
	rEnc.MaxRank = 1000;
	rEnc.MerchantType = MER_TYPE_1; // каботажник
	rEnc.worldMapShip = "bark";
	Enc_AddShips(rEnc, "Merchant", 2, 3);
	Enc_AddShips(rEnc, "War", 1, 2);
	Enc_ExcludeNation(rEnc, PIRATE);

	Enc_AddClasses(rEnc, 2, 3, 4, 3, 4);
	Enc_AddClasses(rEnc, 1000,3, 4, 3, 4);
		
	///////////////////////////////////////////////////////////////////////////////////////
	/// 2-4 торговца 3-4 класса плюс 2-3 корабля охраны
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_ESCORT_MEDIUM]);
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.MinRank = 3;
	rEnc.MaxRank = 1000;
	rEnc.MerchantType = MER_TYPE_2; 
	rEnc.worldMapShip = "galleon";
	Enc_AddShips(rEnc, "Merchant", 2, 4);
	Enc_AddShips(rEnc, "War", 2, 3);
	Enc_ExcludeNation(rEnc, PIRATE);

	Enc_AddClasses(rEnc, 3, 3, 4, 2, 4);
	Enc_AddClasses(rEnc, 1000,3, 4, 2, 4);
	
	///////////////////////////////////////////////////////////////////////////////////////
	/// 3-5 торговца 3-4 класса плюс 2-4 корабля охраны
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_ESCORT_LARGE]);
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.MinRank = 4;
	rEnc.MaxRank = 1000;
	rEnc.MerchantType = MER_TYPE_3; 
	rEnc.worldMapShip = "manowar";
	Enc_AddShips(rEnc, "Merchant", 3, 5);
	Enc_AddShips(rEnc, "War", 2, 4);
	Enc_ExcludeNation(rEnc, PIRATE);

	Enc_AddClasses(rEnc, 4, 3, 4, 2, 3);
	Enc_AddClasses(rEnc, 1000,3, 4, 2, 3);

	// ======================== WAR ENCOUNTERS ========================
	
	///////////////////////////////////////////////////////////////////////////////////////
	/// 1-2 военных корабля 4-5 класса
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_PATROL_SMALL]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.MinRank = 1;
	rEnc.MaxRank = 1000;
	rEnc.worldMapShip = "bark";
	Enc_AddShips(rEnc, "War", 1, 3);
	Enc_ExcludeNation(rEnc, PIRATE);

	Enc_AddClasses(rEnc, 1, 0, 0, 4, 5);
	Enc_AddClasses(rEnc, 1000,0, 0, 4, 5);
	
	///////////////////////////////////////////////////////////////////////////////////////
	/// 2-4 военных корабля 3-5 класса
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_PATROL_MEDIUM]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.MinRank = 5;
	rEnc.MaxRank = 1000;
	rEnc.worldMapShip = "frigate";
	Enc_AddShips(rEnc, "War", 2, 4);
	Enc_ExcludeNation(rEnc, PIRATE);

	Enc_AddClasses(rEnc, 2, 0, 0, 3, 5);
	Enc_AddClasses(rEnc, 1000,0, 0, 3, 5);
	
	///////////////////////////////////////////////////////////////////////////////////////
	/// 3-5 военных корабля 2-4 класса
	/////////////////////////////////////////////////////////////////////////////////////// 
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_PATROL_LARGE]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.MinRank = 7;
	rEnc.MaxRank = 1000;
	rEnc.worldMapShip = "frigate";
	Enc_AddShips(rEnc, "War", 3, 5);
	Enc_ExcludeNation(rEnc, PIRATE);

	Enc_AddClasses(rEnc, 3, 0, 0, 2, 4);
	Enc_AddClasses(rEnc, 1000,0, 0, 2, 4);
		
	///////////////////////////////////////////////////////////////////////////////////////
	/// 1-5 пирата 5-6 класса 
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_PIRATE_SMALL]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.MinRank = 1;
	rEnc.MaxRank = 1000;
	rEnc.worldMapShip = "sloop";
	Enc_AddShips(rEnc, "War", 1, 2);
	Enc_ExcludeNation(rEnc, ENGLAND);
	Enc_ExcludeNation(rEnc, FRANCE);
	Enc_ExcludeNation(rEnc, SPAIN);
	Enc_ExcludeNation(rEnc, HOLLAND);

	Enc_AddClasses(rEnc, 1, 0, 0, 5, 6);
	Enc_AddClasses(rEnc, 1000,0, 0, 5, 6);

	///////////////////////////////////////////////////////////////////////////////////////
	/// 1-2 пирата 4-6 класса
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_PIRATE_MEDIUM]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.MinRank = 3;
	rEnc.MaxRank = 1000;
	rEnc.worldMapShip = "sloop";
	Enc_AddShips(rEnc, "War", 1, 4);
	Enc_ExcludeNation(rEnc, ENGLAND);
	Enc_ExcludeNation(rEnc, FRANCE);
	Enc_ExcludeNation(rEnc, SPAIN);
	Enc_ExcludeNation(rEnc, HOLLAND);

	Enc_AddClasses(rEnc, 2, 0, 0, 4, 6);
	Enc_AddClasses(rEnc, 1000,0, 0, 4, 6);
	
	///////////////////////////////////////////////////////////////////////////////////////
	/// 2-6 пирата
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_PIRATE_LARGE]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.MinRank = 4;
	rEnc.MaxRank = 1000;
	rEnc.worldMapShip = "galleon";
	Enc_AddShips(rEnc, "War", 2, 6);
	Enc_ExcludeNation(rEnc, ENGLAND);
	Enc_ExcludeNation(rEnc, FRANCE);
	Enc_ExcludeNation(rEnc, SPAIN);
	Enc_ExcludeNation(rEnc, HOLLAND);

	Enc_AddClasses(rEnc, 3, 0, 0, 2, 6);
	Enc_AddClasses(rEnc, 1000,0, 0, 2, 6);
	
	///////////////////////////////////////////////////////////////////////////////////////
	/// 1-3 пирата 2-3 класса
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_PIRATE_SCOUNDREL]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.MinRank = 5;
	rEnc.MaxRank = 1000;
	rEnc.worldMapShip = "manowar";
	Enc_AddShips(rEnc, "War", 1, 3);
	Enc_ExcludeNation(rEnc, ENGLAND);
	Enc_ExcludeNation(rEnc, FRANCE);
	Enc_ExcludeNation(rEnc, SPAIN);
	Enc_ExcludeNation(rEnc, HOLLAND);

	Enc_AddClasses(rEnc, 3, 0, 0, 2, 3);
	Enc_AddClasses(rEnc, 1000,0, 0, 2, 3);
	
	///////////////////////////////////////////////////////////////////////////////////////
	/// 2-3 военных корабля 2-4 класса
	/////////////////////////////////////////////////////////////////////////////////////// 
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_SQUADRON]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.MinRank = 4;
	rEnc.MaxRank = 1000;
	rEnc.worldMapShip = "frigate";
	Enc_AddShips(rEnc, "War", 2, 3);
	Enc_ExcludeNation(rEnc, PIRATE);

	Enc_AddClasses(rEnc, 4, 0, 0, 2, 4);
	Enc_AddClasses(rEnc, 1000,0, 0, 2, 4);
	
	///////////////////////////////////////////////////////////////////////////////////////
	/// 3-5 военных корабля 2-4 класса
	/////////////////////////////////////////////////////////////////////////////////////// 
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_FLEET]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.MinRank = 6;
	rEnc.MaxRank = 1000;
	rEnc.worldMapShip = "frigate";
	Enc_AddShips(rEnc, "War", 3, 5);
	Enc_ExcludeNation(rEnc, PIRATE);

	Enc_AddClasses(rEnc, 5, 0, 0, 2, 4);
	Enc_AddClasses(rEnc, 1000,0, 0, 2, 4);
	
	///////////////////////////////////////////////////////////////////////////////////////
	/// 3-9 военных корабля 2-4 класса
	/////////////////////////////////////////////////////////////////////////////////////// 
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_ARMADA]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.MinRank = 9;
	rEnc.MaxRank = 1000;
	rEnc.Chance = 30;
	rEnc.worldMapShip = "manowar";
	Enc_AddShips(rEnc, "War", 3, 9);
	Enc_ExcludeNation(rEnc, PIRATE);

	Enc_AddClasses(rEnc, 6, 0, 0, 2, 4);
	Enc_AddClasses(rEnc, 1000,0, 0, 2, 4);
			
	///////////////////////////////////////////////////////////////////////////////////////
	/// 5-9 военных корабля 2-3 класса
	/////////////////////////////////////////////////////////////////////////////////////// 
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_CROWN_ARMADA]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.MinRank = 9;
	rEnc.MaxRank = 1000;
	rEnc.Chance = 25;
	rEnc.worldMapShip = "manowar";
	Enc_AddShips(rEnc, "War", 3, 5);
	Enc_ExcludeNation(rEnc, PIRATE);
	Enc_ExcludeNation(rEnc, HOLLAND);

	Enc_AddClasses(rEnc, 6, 0, 0, 2, 3);
	Enc_AddClasses(rEnc, 1000,0, 0, 2, 3);
	
	///////////////////////////////////////////////////////////////////////////////////////
	/// 2-4 военных корабля 2-3 класса
	/////////////////////////////////////////////////////////////////////////////////////// 
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_PUNITIVE_SQUADRON]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.MinRank = 7;
	rEnc.MaxRank = 1000;
	rEnc.Chance = 30;
	rEnc.worldMapShip = "manowar";
	Enc_AddShips(rEnc, "War", 2, 4);
	Enc_ExcludeNation(rEnc, PIRATE);

	Enc_AddClasses(rEnc, 6, 0, 0, 2, 3);
	Enc_AddClasses(rEnc, 1000,0, 0, 2, 3);	

	///////////////////////////////////////////////////////////////////////////////////////
	/// 1-2 военных корабля 3-4 класса
	/////////////////////////////////////////////////////////////////////////////////////// 
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_WAR_PRIVATEER]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.MinRank = 4;
	rEnc.MaxRank = 1000;
	rEnc.Chance = 45;
	rEnc.worldMapShip = "galleon";
	Enc_AddShips(rEnc, "War", 1, 2);
	Enc_ExcludeNation(rEnc, PIRATE);

	Enc_AddClasses(rEnc, 6, 0, 0, 3, 4);
	Enc_AddClasses(rEnc, 1000,0, 0, 3, 4);	

	///////////////////////////////////////////////////////////////////////////////////////
	/// 1-3 торговых корабля 2-3 класса (коронный торговец) + 1-3 корабля охранения 2-3 класса
	/////////////////////////////////////////////////////////////////////////////////////// 
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_CROWN]);
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.MinRank = 4;
	rEnc.MaxRank = 1000;
	rEnc.MerchantType = MER_TYPE_4; 
	rEnc.worldMapShip = "bark";
	Enc_AddShips(rEnc, "Merchant", 1, 3);
	Enc_AddShips(rEnc, "War", 1, 3);
	Enc_ExcludeNation(rEnc, PIRATE);
	rEnc.Chance = 25;

	Enc_AddClasses(rEnc, 4, 2, 3, 2, 3);
	Enc_AddClasses(rEnc, 1000,2, 3, 2, 3);
	
	///////////////////////////////////////////////////////////////////////////////////////
	/// 1 торговый корабля 2 класса  + 1 корабль охранения 2-3 класса (экспедиция)
	/////////////////////////////////////////////////////////////////////////////////////// 	
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_EXPEDITION]);
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.MinRank = 4;
	rEnc.MaxRank = 1000;
	rEnc.MerchantType = MER_TYPE_5; 
	rEnc.worldMapShip = "galleon";
	Enc_AddShips(rEnc, "Merchant", 1, 1);
	Enc_AddShips(rEnc, "War", 1, 1);
	Enc_ExcludeNation(rEnc, PIRATE);
	rEnc.Chance = 55;

	Enc_AddClasses(rEnc, 4, 2, 2, 2, 3);
	Enc_AddClasses(rEnc, 1000,2, 2, 2, 3);
	
	///////////////////////////////////////////////////////////////////////////////////////
	/// Бочонок
	/////////////////////////////////////////////////////////////////////////////////////// 
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_BARREL]);
	rEnc.Type = ENCOUNTER_SPECIAL;
	rEnc.MinRank = 1;
	rEnc.MaxRank = 1000;
	rEnc.Chance = 45;
	rEnc.worldMapShip = "barrel";
	Enc_AddShips(rEnc, "Special", 0, 0);
	Enc_ExcludeNation(rEnc, PIRATE);
			
	///////////////////////////////////////////////////////////////////////////////////////
	/// Кораблекрушенец
	/////////////////////////////////////////////////////////////////////////////////////// 
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_BOAT]);
	rEnc.Type = ENCOUNTER_SPECIAL;
	rEnc.MinRank = 1;
	rEnc.MaxRank = 1000;
	rEnc.Chance = 25;
	rEnc.worldMapShip = "boat";
	Enc_AddShips(rEnc, "Special", 0, 0);
		
	Trace("Init encounters complete.");
}