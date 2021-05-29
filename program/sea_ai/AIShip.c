object	Sail, Rope, Flag, Vant, VantL, VantZ ;

#define MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER				1000.0
#define MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER_FORT		1400.0
#define MIN_ENEMY_DISTANCE_TO_DISABLE_ENTER_2_LOCATION		1150.0

bool	bAbordageShipCanBe = false;
int		iAbordageShipEnemyCharacter;

//bool	bNoDamage2Us = false;
bool	bCanEnterToLand = false;
aref	arIslandReload;
string	sIslandLocator;
string	sIslandID;
string	sSeaSoundPostfix;
int		iShipPriorityExecute = 2;
int		iShipPriorityRealize = 31;
bool	bUpdatePosMode = false;
int		iVicSoundTime = 0;
string	sSeaStartMusicName;
bool	isEnemyAround = false;

int		iNumShips = 0;
int		Ships[MAX_SHIPS_ON_SEA];

#define SHIP_DETONATE_SMALL		"ShipDetonateSmall"

#event_handler("Ship_StartLoad", "Ship_StartLoad");
#event_handler("Ship_EndLoad", "Ship_EndLoad");

void CreateRiggingEnvironment()
{
	CreateEntity(&Sail, "Sail");
	LayerAddObject(sCurrentSeaExecute, &Sail, iShipPriorityExecute + 1);
	LayerAddObject(sCurrentSeaRealize, &Sail, iShipPriorityRealize + 1);
	LayerAddObject("sails_trace", &Sail, 10);
	LayerAddObject("sea_reflection2", &Sail, 3);
	Sail.MinSpeed = 0.05;

	CreateEntity(&Rope, "Rope");
	LayerAddObject(sCurrentSeaExecute, &Rope, iShipPriorityExecute + 2);
	LayerAddObject(sCurrentSeaRealize, &Rope, iShipPriorityRealize + 2);
	
	CreateEntity(&Flag, "Flag");
	LayerAddObject(sCurrentSeaExecute, &Flag, iShipPriorityExecute + 3);
	LayerAddObject(sCurrentSeaRealize, &Flag, iShipPriorityRealize + 3);
	LayerAddObject("sea_reflection2", &Flag, 3);
	
	CreateEntity(&Vant, "Vant");
	LayerAddObject(sCurrentSeaExecute, &Vant, iShipPriorityExecute + 4);
	LayerAddObject(sCurrentSeaRealize, &Vant, iShipPriorityRealize + 4);
	
	CreateEntity(&VantL, "VantL");
	LayerAddObject(sCurrentSeaExecute, &VantL, iShipPriorityExecute + 4);
	LayerAddObject(sCurrentSeaRealize, &VantL, iShipPriorityRealize + 4);
	
	CreateEntity(&VantZ, "VantZ");
	LayerAddObject(sCurrentSeaExecute, &VantZ, iShipPriorityExecute + 4);
	LayerAddObject(sCurrentSeaRealize, &VantZ, iShipPriorityRealize + 4);
	
	iNumShips = 0;
}

void DeleteRiggingEnvironment()
{
	DeleteClass(&Sail);
	DeleteClass(&Rope);
	DeleteClass(&Flag);
	DeleteClass(&Vant);
	DeleteClass(&VantL);
	DeleteClass(&VantZ);
}

void DeleteShipEnvironment()
{
	DeleteRiggingEnvironment();

	DelEventHandler(SHIP_CHANGE_CHARGE, "Ship_ChangeChargeEvent");  // нигде не используется???
	DelEventHandler(SHIP_DROP_GOOD, "DropGoodsToSea");
	DelEventHandler(SHIP_HULL_HIT, "Ship_HullHitEvent");
	DelEventHandler(SHIP_CHECK_RELOAD_ENABLE, "Ship_CheckMainCharacter");
	DelEventHandler(SHIP_DETONATE_SMALL, "Ship_DetonateSmall");
	DelEventHandler(SHIP_BRANDER_DETONATE, "Ship_BranderDetonate");
	DelEventHandler(SHIP_FIRE_DAMAGE, "Ship_FireDamage");
	DelEventHandler(SHIP_TO_STRAND_NEXT, "Ship_OnStrandNext");
	DelEventHandler(SHIP_BORT_RELOADED, "Ship_OnBortReloaded");
	DelEventHandler(SHIP_ACTIVATE_FIRE_PLACE, "Ship_ActivateFirePlace");
	DelEventHandler(SHIP_UPDATE_PARAMETERS, "Ship_UpdateParameters");
	DelEventHandler(SHIP_CHECK_SITUATION, "Ship_CheckSituation");
	DelEventHandler(WHR_LIGHTNING, "Ship_Lightning");
	DelEventHandler("eSwitchPerks", "Ship_UpdatePerks");
	DelEventHandler("TornadoDamage", "Ship_TornadoDamage");
	DelEventHandler(SHIP_GET_RUNAWAY_POINT, "Ship_GetRunAwayPoint");
	DelEventHandler("frame", "Ship_VicSoundTime");
	DelEventHandler("Ship_SailsMoveSound", "Ship_SailsMoveSound");
	DelEventHandler("Ship_BortReloadEvent", "Ship_BortReloadEvent");
	DelEventHandler("Ship_VolleyHeelEnd", "Ship_VolleyHeelEnd");
	DelEventHandler(SHIP_SET_BLOT, "Ship_SetBlot");
	DelEventHandler(SHIP_FAKE_FIRE, "Ship_EventFakeFire");


	for (int i=0; i<iNumShips; i++) 
	{ 
		// delete particles from ship/etc
		SendMessage(&Characters[Ships[i]], "l", MSG_SHIP_SAFE_DELETE); 

		// delete sounds from ship
		if (CheckAttribute(&Characters[Ships[i]], "Ship.Sounds.WaterID")) 	ReleaseSound(sti(Characters[Ships[i]].Ship.Sounds.WaterID));
		if (CheckAttribute(&Characters[Ships[i]], "Ship.Sounds.SailsID"))   ReleaseSound(sti(Characters[Ships[i]].Ship.Sounds.SailsID));
		if (CheckAttribute(&Characters[Ships[i]], "Ship.Sounds.TurnID"))   ReleaseSound(sti(Characters[Ships[i]].Ship.Sounds.TurnID));
	}

	// scan characters for delete snd id's
	DeleteEntitiesByType("ship");
}

void ClearAllFire() // boal new
{
    for (int i=0; i<iNumShips; i++)
	{
		// delete particles from ship/etc
		if (Ships[i] != -1) SendMessage(&Characters[Ships[i]], "l", MSG_SHIP_SAFE_DELETE);
	}
}
// boal new сбросить всем в море проверку смотрения на флаг.
void Sea_ClearCheckFlag() 
{
    if (bSeaActive)
    {
		int i;
		
		for (i=0; i<iNumShips; i++)
		{
			if(sti(Ships[i]) >= 0 && sti(Ships[i]) < TOTAL_CHARACTERS) {
			if (!CheckAttribute(&Characters[Ships[i]], "DontCheckFlag"))
			{
			    DeleteAttribute(&Characters[Ships[i]], "CheckFlagYet"); // флаг распознования врага
			    DeleteAttribute(&Characters[Ships[i]], "CheckFlagDate");
			}
			}
		}
		// фортам трем
		for (i=0; i<MAX_COLONIES; i++)
		{
			if (CheckAttribute(&colonies[i], "commanderIdx"))
			{
				if (!CheckAttribute(&Characters[sti(colonies[i].commanderIdx)], "DontCheckFlag"))
				{
					DeleteAttribute(&Characters[sti(colonies[i].commanderIdx)], "CheckFlagYet"); // флаг распознования врага
				    DeleteAttribute(&Characters[sti(colonies[i].commanderIdx)], "CheckFlagDate");
			    }
			}
		}
	}
}

void CreateShipEnvironment()
{
	isEnemyAround = false;
	bUpdatePosMode = false;
	iVicSoundTime = 0;

	bAbordageFortCanBe = false;
	bAbordageShipCanBe = false;
	bCanEnterToLand = false;
	sIslandLocator = "";
	sIslandID = "";
	
	for (int i = 0; i < MAX_SHIPS_ON_SEA; i++) Ships[i] = -1;

	aref arCurWeather = GetCurrentWeather();
	sSeaSoundPostfix = arCurWeather.Sounds.Sea.Postfix;

	CreateRiggingEnvironment();

	SetEventHandler(SEA_GET_LAYERS, "SeaAI_GetLayers", 0);

	SetEventHandler(SHIP_NOT_ENOUGH_BALLS, "Ship_NotEnoughBalls", 0);
	SetEventHandler(SHIP_GET_CURRENT_BALLS_NUM, "Ship_GetCurrentBallsNum", 0);
	SetEventHandler(SHIP_SHIP2ISLAND_COLLISION, "Ship_Ship2IslandCollision", 0);
	SetEventHandler(SHIP_SHIP2SHIP_COLLISION, "Ship_Ship2ShipCollision", 0);
	SetEventHandler(SHIP_SAIL_DAMAGE, "Ship_SailDamage", 0);
	SetEventHandler(SHIP_FIRE_DAMAGE, "Ship_FireDamage", 0);
	SetEventHandler(SHIP_CHECK_SITUATION, "Ship_CheckSituation", 0);
	SetEventHandler(SHIP_TO_STRAND, "Ship_OnStrand", 0);
	SetEventHandler(SHIP_TO_STRAND_NEXT, "Ship_OnStrandNext", 0);
	SetEventHandler(SHIP_DEAD, "Ship_OnDead", 0);
	SetEventHandler(SHIP_UPDATE_PARAMETERS, "Ship_UpdateParameters", 0);
	SetEventHandler(SHIP_DROP_GOOD, "DropGoodsToSea", 0);
	SetEventHandler(SHIP_CREATE, "Ship_OnCreate", 0);
	SetEventHandler(SHIP_BORT_RELOADED, "Ship_OnBortReloaded", 0);
	SetEventHandler(SHIP_CHANGE_CHARGE, "Ship_ChangeChargeEvent", 0);
	SetEventHandler(SHIP_HULL_HIT, "Ship_HullHitEvent", 0);
	SetEventHandler(SHIP_CHECK_RELOAD_ENABLE, "Ship_CheckMainCharacter", 0);
	SetEventHandler(SHIP_FIRE_ACTION, "Ship_FireAction", 0);
	SetEventHandler(SHIP_GET_BORT_FIRE_DELTA, "Ship_GetBortFireDelta", 0);
	SetEventHandler(SHIP_DETONATE_SMALL, "Ship_DetonateSmall", 0);
	SetEventHandler(SHIP_ACTIVATE_FIRE_PLACE, "Ship_ActivateFirePlace", 0);
	SetEventHandler(WHR_LIGHTNING, "Ship_Lightning", 0);
	SetEventHandler(SHIP_CREATELOADSHIP, "Ship_LoadShip", 0);
	SetEventHandler(SHIP_LOAD_SHIPACTIVATEFIREPLACE, "Ship_LoadShipActivateFirePlace", 0);
	SetEventHandler(SHIP_GET_RUNAWAY_POINT, "Ship_GetRunAwayPoint", 0);
	SetEventHandler("TornadoDamage", "Ship_TornadoDamage", 0);

	SetEventHandler(SHIP_BRANDER_DETONATE, "Ship_BranderDetonate", 0);
	SetEventHandler(SHIP_MAST_DAMAGE, "Ship_MastDamage", 0);	
	SetEventHandler(SHIP_HULL_DAMAGE, "Ship_HullDamage", 0); // ugeen 15.11.10 - обработка событий повреждений отделяемых элементов корпуса
	SetEventHandler("eSwitchPerks", "Ship_UpdatePerks", 0);
	SetEventHandler("frame", "Ship_VicSoundTime", 0);
	SetEventHandler("Ship_SailsMoveSound", "Ship_SailsMoveSound", 0);
	SetEventHandler("Ship_BortReloadEvent", "Ship_BortReloadEvent", 0);
	SetEventHandler("Ship_VolleyHeelEnd", "Ship_VolleyHeelEnd", 0);
	SetEventHandler(SHIP_SET_BLOT, "Ship_SetBlot", 0);
	SetEventHandler(SHIP_FAKE_FIRE, "Ship_EventFakeFire", 0);
}	

float Ship_GetBortFireDelta()
{
	aref aCharacter = GetEventData();
	float x = GetEventData();
	float y = GetEventData();
	float z = GetEventData();
	float fDistance = GetDistance2D(x, z, stf(aCharacter.Ship.Pos.x), stf(aCharacter.Ship.Pos.z));
	
	float fAccuracy = 1.3 - stf(aCharacter.TmpSkill.Accuracy);
	
	// to_do
	if (iArcadeSails == 1)// && aCharacter.id == characters[nMainCharacterIndex].id)
	{
		fAccuracy  = fAccuracy - 0.2;
		if (fAccuracy < 0.1)
		{
			fAccuracy = 0.1;
		}
	}
	/*
	if (aCharacter.id != characters[nMainCharacterIndex].id)
	{
		fAccuracy  = fAccuracy - 0.2;
		if (fAccuracy < 0.1)
		{
			fAccuracy = 0.1;
		}
	} */
	

	float fRadius = fAccuracy * Bring2Range(0.0, 120.0, 0.0, 1000.0, fDistance);
	return fRadius;
}

string Ship_GetGroupID(ref rCharacter)
{
 	if (CheckAttribute(rCharacter, "SeaAI.Group"))// boal fix bug
    {
        return rCharacter.SeaAI.Group.Name;
    }
    else
    {
        return "";
    }
}
// boal 030804 -->
void Ship_NationAgressivePatent(ref rCharacter)
{
	// патент отнимаем всегда, когда палим по другу патента
    ref rMainCharacter = GetMainCharacter();

    if (isMainCharacterPatented())
    {
        if (sti(rCharacter.nation) != PIRATE && GetNationRelation(sti(Items[sti(rMainCharacter.EquipedPatentId)].Nation), sti(rCharacter.nation)) != RELATION_ENEMY)
        {
        	TakeItemFromCharacter(rMainCharacter, "patent_" + NationShortName(sti(Items[sti(rMainCharacter.EquipedPatentId)].Nation)));
        	ChangeCharacterHunterScore(rMainCharacter, NationShortName(sti(Items[sti(rMainCharacter.EquipedPatentId)].Nation)) + "hunter", 40);
        	Items[sti(rMainCharacter.EquipedPatentId)].TitulCur = 1; // текущ звание сбросим
        	Items[sti(rMainCharacter.EquipedPatentId)].TitulCurNext = 0; // счетчик звание сбросим
        	RemoveCharacterEquip(rMainCharacter, "patent");// Удаляем патент из экипировки
        	rCharacter.CheckNationBounty = true;
        }
    }
    else
    {// без патента
    	if (sti(rCharacter.nation) != PIRATE && !CheckAttribute(rCharacter, "CheckNationBounty"))   // еще не наказывал
    	{
    		if (GetNationRelation(GetBaseHeroNation(), sti(rCharacter.nation)) != RELATION_ENEMY)
    		{
				rCharacter.CheckNationBounty = true;
				ChangeCharacterHunterScore(rMainCharacter, NationShortName(sti(rCharacter.nation)) + "hunter", 1 + rand(2));
			}
    	}
    }
}
void Ship_NationAgressive(ref rMainGroupCharacter, ref rCharacter)// ком группы и в кого попали
{    // используется на суше при атаке города
    ref rMainCharacter = GetMainCharacter();
    
    if (CheckAttribute(rCharacter, "Coastal_Captain")) return;  // есть флаг есть, то нет ругани, это таможенник и квестовый

	//--> eddy. квест мэра на пирата
	if (rCharacter.id == "MQPirate" && sti(rCharacter.nation) != PIRATE)
	{
		rCharacter.nation = PIRATE;
		Ship_FlagRefresh(characterFromId("MQPirate")); //флаг на лету
		//Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), nMainCharacterIndex); //сваливает
      	Pchar.quest.DestroyPirate_PirateIsOut.win_condition.l1 = "ExitFromSea";
		Pchar.quest.DestroyPirate_PirateIsOut.win_condition = "DestroyPirate_PirateIsOut";
	}
	//<-- eddy. квест мэра на пирата
	else
	{
		if (CheckAttribute(rCharacter, "ShipEnemyDisable") || CheckAttribute(rCharacter, "AlwaysFriend"))  return; // флаг не обижаться на выстрелы
	    if( sti(rMainCharacter.nation) == sti(rCharacter.nation) && sti(rMainCharacter.nation) != PIRATE)
	    {
            SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
            rMainCharacter.nation = PIRATE;
			DoQuestCheckDelay(NationShortName(PIRATE) + "_flag_rise", 0.1); // применение нац отношений флага
	        ChangeCharacterComplexReputation(rMainCharacter,"nobility", -10);
			ChangeCharacterComplexReputation(rMainCharacter,"authority", -2);
			ChangeCharacterComplexReputation(rMainCharacter,"fame", 0.5);
	    }
	    Ship_NationAgressivePatent(rCharacter); // патент отнимаем всегда, когда палим по другу патента
		
	    // clear group temporary task status
		for (int i=0; i<MAX_SHIP_GROUPS; i++) { AIGroups[i].TempTask = false; } // новая хрень к3

	    SetNationRelation2MainCharacter(sti(rMainGroupCharacter.nation), RELATION_ENEMY);
	    SetCharacterRelationBoth(sti(rMainGroupCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
	    // boal 04.04.04 -->
	    if (sti(rMainGroupCharacter.nation) != PIRATE)
	    {
	    	ChangeCharacterHunterScore(rMainCharacter, NationShortName(sti(rMainGroupCharacter.nation)) + "hunter", 5);
	    }
    }
    // boal 04.04.04 <--
}
// boal 030804 <--
void Ship_FireAction()
{
	aref rCharacter = GetEventData();				// we attack this character
	aref rMainGroupCharacter = GetEventData();		// commander character for rCharacter
	int iRelation = GetEventData();
	
	if (LAi_IsDead(rCharacter)) return; // fix - нефиг палить в труп!
	
	// if companion - decrease reputation
	if (IsCompanion(rCharacter))
	{
		if (CheckAttribute(rCharacter, "CompanionEnemyEnable") && sti(rCharacter.CompanionEnemyEnable))
		{
			SeaAI_SetCompanionEnemy(rCharacter);
			// disconnect companion from our group and set it enemy to us
		}
		return;
	}
	else
	{
	    if (CheckAttribute(rCharacter, "ShipEnemyDisable") )  return; // флаг не обижаться на выстрелы
	    // убрал || CheckAttribute(rCharacter, "AlwaysFriend") тк если по отпущенному торговцу палить, то должен обижаться
	    DeleteAttribute(rCharacter, "AlwaysFriend");
	}
			
	if (iRelation != RELATION_ENEMY)
	{
		Ship_NationAgressive(rMainGroupCharacter, rCharacter);// boal 030804 в один метод

		// making whole group as enemy to us
		if (CheckAttribute(rMainGroupCharacter, "SeaAI.Group.Name"))
		{
			Group_SetEnemyToCharacter(rMainGroupCharacter.SeaAI.Group.Name, nMainCharacterIndex);
		}
		/* // наследие К3, в ВМЛ только мешает
		if (CheckAttribute(&rCharacter, "relation.UseOtherCharacter"))
		{
			if (sti(rCharacter.relation.UseOtherCharacter) >= 0)
			{
				SetCharacterRelationBoth(nMainCharacterIndex, sti(rCharacter.relation.UseOtherCharacter), RELATION_ENEMY);
			}
		}*/
	}
	else
	{
	    // патент нужно отнять даже если враг
    	Ship_NationAgressivePatent(rCharacter);// патент отнимаем всегда, когда палим по другу патента
	}
	DoQuestCheckDelay("NationUpdate", 0.3);
	//UpdateRelations();
	RefreshBattleInterface();
	
	//eddy. корабли с залоченным таском не менять
	if (CheckAttribute(rCharacter, "ShipTaskLock")) return;
	//eddy
	int i;
	string sGroupID, sGroupType;
	ref rGroup;

	// clear group temporary task status
	for (i=0; i<MAX_SHIP_GROUPS; i++) { AIGroups[i].TempTask = false; }

	// looking for enemy war/trade ships around
	for (i=0; i<iNumShips; i++)
	{
		ref rShipCharacter = GetCharacter(Ships[i]);

		if (SeaAI_GetRelation(GetMainCharacterIndex(), Ships[i]) != RELATION_ENEMY) { continue; }

		sGroupID = Ship_GetGroupID(rShipCharacter);
		sGroupType = Group_GetType(sGroupID);
		rGroup = Group_GetGroupByID(sGroupID);

		float fDistance = Ship_GetDistance2D(GetMainCharacter(), rShipCharacter);

		//вообще неясно, для чего это, если ниже все одно атака групп
		/*if (!sti(rGroup.TempTask) && fDistance < 2000.0)	// if distance < 2 km
		{
			switch (sGroupType)
			{
				case "trade":
					Group_SetTaskRunaway(sGroupID, PLAYER_GROUP);
				break;
				case "war":
					Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
				break;
				case "pirate":
					Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
				break;
			}
		}*/
	}

	// if fort - return
	int iShipType = sti(rCharacter.Ship.Type);
	iShipType = sti(RealShips[iShipType].basetype);
	if (ShipsTypes[iShipType].name == "Fort") 
	{ 
		return; 
	}
	
	sGroupID = Ship_GetGroupID(rMainGroupCharacter);

	Group_SetTaskAttack(PLAYER_GROUP, sGroupID);
}

void Ship_SetBlot()
{
	aref rCharacter = GetEventData();
	
	// TODO
}

float Ship_MastDamage()
{
	int iDamageType 	= GetEventData();
	int iMastNum 		= GetEventData();
	float x 			= GetEventData();
	float y 			= GetEventData();
	float z 			= GetEventData();
	float fDamage 		= GetEventData();
	aref rCharacter 	= GetEventData();
	
	switch (iDamageType)
	{
		case SHIP_MAST_TOUCH_ISLAND:
			fDamage = fDamage + 0.25;
		break;
		case SHIP_MAST_TOUCH_SHIP:
			fDamage = fDamage + 0.2;
		break;
		case SHIP_MAST_TOUCH_BALL:
			int iBallOwnerIndex 	= GetEventData();
			ref	rBallCharacter 		= GetCharacter(iBallOwnerIndex);	// кто пуляет
			int	iBallType = sti(AIBalls.CurrentBallType);   			// спорно, тк это не ядра, того кто стрелял, а скорее ядра ГГ
			switch (iBallType)
			{
				case GOOD_BALLS:
					fDamage = fDamage + 0.1;
				break;
				case GOOD_GRAPES:
					fDamage = fDamage + 0.05;
				break;
				case GOOD_KNIPPELS:
					fDamage = fDamage + 0.25;
				break;
				case GOOD_BOMBS:
					fDamage = fDamage + 0.15;
				break;
			}
			
		break;
	}
	if (2-sti(RealShips[sti(rCharacter.ship.type)].Class) > 0) 
	{
		fDamage = fDamage/2;
	}
	fDamage = Clampf(fDamage);

	if (fDamage >= 1.0)
	{
		Play3DSound("mast_fall", x, y, z);	// if mast fall - play sound
		rCharacter.Tmp.SpeedRecall = 0; 	// чтоб пересчитался маневр
		RefreshBattleInterface();
	}
	
	if(iDamageType == SHIP_MAST_TOUCH_BALL)
	{
		rCharacter.Ship.LastBallCharacter = iBallOwnerIndex;
//		Log_Info(" Ship_MastDamage : Character.id = " + rCharacter.id + " BallOwner.id = " + rBallCharacter.id);
		if (sti(rCharacter.Ship.LastBallCharacter) == GetMainCharacterIndex() 
			&& GetNationRelation2MainCharacter(sti(rCharacter.nation)) != RELATION_ENEMY)
		{
			if (!IsCompanion(rCharacter) && !CheckAttribute(rCharacter, "Coastal_Captain")) 
			{
				Ship_NationAgressive(rCharacter, rCharacter);// boal 030804 в один метод
				DoQuestCheckDelay("NationUpdate", 0.7);
			}
		}		
	}	
	return fDamage;	
}

float Ship_HullDamage()
{
	int iDamageType = GetEventData();
	int iHullNum = GetEventData(); // номер ноды в которую прилетело
	float x = GetEventData();
	float y = GetEventData();
	float z = GetEventData();
	float fDamage = GetEventData();
	aref rCharacter = GetEventData(); // в кого прилетело
	aref aCharacter = GetEventData(); // владелец ядра (от кого прилетело)
	string HullName = GetEventData(); // имя ноды в которую прилетело
	
	switch (iDamageType)
	{
		case SHIP_HULL_TOUCH_BALL:
			int	iBallType = sti(AIBalls.CurrentBallType);   //спорно, тк это не ядра, того кто стрелял, а скорее ядра ГГ
			switch (iBallType)
			{
				case GOOD_BALLS:
					fDamage = fDamage + 0.40;
				break;
				case GOOD_GRAPES:
					fDamage = fDamage + 0.10;
				break;
				case GOOD_KNIPPELS:
					fDamage = fDamage + 0.20;
				break;
				case GOOD_BOMBS:
					fDamage = fDamage + 0.65;
				break;
			}
		break;
	}

	fDamage = Clampf(fDamage);
	if (fDamage >= 1.0)
	{
		CreateBlast(x,y,z);
		CreateParticleSystem("blast_inv", x, y, z, 0.0, 0.0, 0.0, 0);
		Play3DSound("cannon_explosion", x, y, z); 	
		RefreshBattleInterface();
		
		if(HasSubStr(HullName, "baller")) // потеряли перо руля
		{
			rCharacter.Ship.hulls.baller_destroyed = true; // признак поломки руля
			string sDamagedString = "На судне '" + rCharacter.Ship.Name + "' поврежден руль, судно потеряло управление.";
			Log_SetStringToLog(sDamagedString);
		}
	}
	return fDamage;
}


float Ship_GetSailState(ref rCharacter)
{
	float fSailState = 1.0;
	SendMessage(rCharacter, "le", MSG_SHIP_GET_SAIL_STATE, &fSailState);
	return fSailState;
}
// boal 27.09.05 -->
void Ship_SetExplosion(ref rCharacter, ref	rShipObject)
{
    int i = 0;
    // fire ship
	//int iNumFirePlaces = rand(2);
	//SendMessage(rShipObject, "le", MSG_SHIP_GET_NUM_FIRE_PLACES, &iNumFirePlaces);
	//for (i=0; i<=iNumFirePlaces; i++)
	//{
		//PostEvent(SHIP_ACTIVATE_FIRE_PLACE, rand(300), "ialsfl", rShipObject, rCharacter, i, "ship_onfire", 3, -1);
	//}
	//PostEvent(SHIP_ACTIVATE_FIRE_PLACE, 100, "ialsfl", rShipObject, rCharacter, i, "ship_onfire", 3, -1);  // дает вылет
	PostEvent(SHIP_BRANDER_DETONATE, 800, "l", sti(rCharacter.index));
    PlaySound("Sea Battles\Vzriv_fort_001.wav");
	Ship_SetTaskNone(SECONDARY_TASK, sti(rCharacter.index));
}
// boal <--
void Ship_SetSailState(int iCharacterIndex, float fSailState)
{
	SendMessage(&AISea, "laf", AI_MESSAGE_SHIP_SET_SAIL_STATE, &Characters[iCharacterIndex], fSailState);
}

void Ship_SetTaskNone(int iTaskPriority, int iCharacterIndex)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_NONE;
}

void Ship_SetTaskAbordage(int iTaskPriority, int iCharacterIndex, int iCharacterIndexAbordageTo)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_ABORDAGE;
	rCharacter.SeaAI.Task.Target = iCharacterIndexAbordageTo;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_ABORDAGE, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndexAbordageTo]);
}

void Ship_SetTaskBrander(int iTaskPriority, int iCharacterIndex, int iCharacterIndexBranderTo)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_BRANDER;
	rCharacter.SeaAI.Task.Target = iCharacterIndexBranderTo;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_BRANDER, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndexBranderTo]);
}

void Ship_SetTaskMove(int iTaskPriority, int iCharacterIndex, float x, float z)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_MOVE;
	//rCharacter.SeaAI.Task.Target = "";
	rCharacter.SeaAI.Task.Pos.x = x;
	rCharacter.SeaAI.Task.Pos.z = z;
	SendMessage(&AISea, "lllaff", AI_MESSAGE_SHIP_SET_TASK, AITASK_MOVE, iTaskPriority, &Characters[iCharacterIndex], x, z);
}

void Ship_SetTaskRunaway(int iTaskPriority, int iCharacterIndex, int iFromIndex)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_RUNAWAY;
	rCharacter.SeaAI.Task.Target = iFromIndex;	
	SendMessage(&AISea, "llla", AI_MESSAGE_SHIP_SET_TASK, AITASK_RUNAWAY, iTaskPriority, &Characters[iCharacterIndex]);	
	Ship_SetSailState(iCharacterIndex, 1);
}

void Ship_SetTaskAttack(int iTaskPriority, int iCharacterIndex, int iCharacterIndexVictim)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_ATTACK;
	rCharacter.SeaAI.Task.Target = iCharacterIndexVictim;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_ATTACK, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndexVictim]);
}

void Ship_SetTaskSailTo(int iTaskPriority, int iCharacterIndex, int iCharacterIndexSailTo)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_MOVE;
	rCharacter.SeaAI.Task.Target = iCharacterIndexSailTo;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_MOVE, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndexSailTo]);
}

void Ship_SetTaskDrift(int iTaskPriority, int iCharacterIndex)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_DRIFT;
	//rCharacter.SeaAI.Task.Target = "";
	SendMessage(&AISea, "llla", AI_MESSAGE_SHIP_SET_TASK, AITASK_DRIFT, iTaskPriority, &Characters[iCharacterIndex]);
}

void Ship_SetTaskDefendGroup(int iTaskPriority, int iCharacterIndex, string sDefendGroup)
{
	SendMessage(&AISea, "lllas", AI_MESSAGE_SHIP_SET_TASK, AITASK_DEFEND_GROUP, iTaskPriority, &Characters[iCharacterIndex], sDefendGroup);
}

void Ship_SetTaskDefend(int iTaskPriority, int iCharacterIndex, int iCharacterIndex2Defend)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_DEFEND;
	rCharacter.SeaAI.Task.Target = iCharacterIndex2Defend;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_DEFEND, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndex2Defend]);
}

void Ship_DoFire()
{
	int bCameraOutside = SeaCameras_isCameraOutside();// || CrosshairHidden();     // LDH 17Jan17 aimed fire when crosshair visible
	// LDH 09Feb17 - tell player how to get aiming crogghair
/*	bool bTemp = bMapEnter || bCanEnterToLand;	// LDH 11Feb17
	if (CrosshairHidden() && GetCurControlGroup() == "Sailing1Pers" && bTemp)
		Log_Info("Нажмите клавишу 'C' для активации прицельного огня");*/
	SendMessage(&AISea, "lal", AI_MESSAGE_CANNON_FIRE, &Characters[nMainCharacterIndex], bCameraOutside);
}

void Ship_StartLoad()
{
	aref rCharacter = GetEventData();
	if(rCharacter.id != "0" && sti(rCharacter.ship.type) != SHIP_NOTUSED)
	{
		ref refBaseShip;
		int nShipType = GetCharacterShipType(rCharacter);
		refBaseShip = GetRealShip(nShipType);
		SetTextureForShip(refBaseShip, rCharacter);
	}
}

void Ship_EndLoad()
{
	SetTexturePath(0, "");
}

void Ship_SetTrackSettings(ref rCharacter)
{
	ref rShip = GetRealShip(GetCharacterShipType(rCharacter));

	rCharacter.Ship.Track.Enable = rShip.Track.Enable;
	if (!sti(rShip.Track.Enable)) return;

	rCharacter.Ship.Track.TrackDistance = 1.0;
	rCharacter.Ship.Track.WaveHeight2 = 0.9;
	rCharacter.Ship.Track.WaveHeight1 = 0.2;

	rCharacter.Ship.Track1.Texture = "ships\trailShip.tga";
	rCharacter.Ship.Track1.TrackWidthSteps = 12.0;

	rCharacter.Ship.Track2.Texture = "ships\trailKeel.tga";
	rCharacter.Ship.Track2.TrackWidthSteps = 4.0;

	rCharacter.Ship.Track1.ZStart = rShip.Track1.ZStart;
	rCharacter.Ship.Track1.LifeTime = rShip.Track1.LifeTime;
	rCharacter.Ship.Track1.Width = rShip.Track1.Width;
	rCharacter.Ship.Track1.Speed = rShip.Track1.Speed;

	rCharacter.Ship.Track2.ZStart = rShip.Track2.ZStart;
	rCharacter.Ship.Track2.LifeTime = rShip.Track2.LifeTime;
	rCharacter.Ship.Track2.Width = rShip.Track2.Width;
	rCharacter.Ship.Track2.Speed = rShip.Track2.Speed;
}

void Ship_SetLightsOff(ref rCharacter, float fTime, bool bLights, bool bFlares, bool bNow)
{
	SendMessage(rCharacter, "lflll", MSG_SHIP_SETLIGHTSOFF, fTime, bLights, bFlares, bNow);
	rCharacter.Ship.Lights = 0; //fix
}

void Ship_SetLightsAndFlares(ref rCharacter)
{
	if(CheckAttribute(sea,"lights") && sti(sea.lights) == 1)
	{
		rCharacter.Ship.Flares = 1;
		rCharacter.Ship.Lights = 1;
	}
	else
	{
		rCharacter.Ship.Flares = 0;
		rCharacter.Ship.Lights = 0;
	}
}

void Ship_Add2Sea(int iCharacterIndex, bool bFromCoast, string sFantomType, bool isOffline)
{
	ref		rCharacter = GetCharacter(iCharacterIndex);

	DeleteAttribute(rCharacter, "ship.cannons.chance_for_explode"); //to_do у нас не юзается

	aref	arCharacter; makearef(arCharacter, Characters[sti(rCharacter.index)]);
	
	int iShipType = sti(rCharacter.Ship.Type);

	if(iShipType == SHIP_NOTUSED)
	{
		return;
	}

	int iRealShip = sti(RealShips[iShipType].basetype);

	if(!CheckAttribute(&RealShips[iShipType], "name"))
	{
		Trace("Ship_Add2Sea() : SHIP " + iShipType + ", have no name!   NPCid = "+ rCharacter.id);
		if (MOD_BETTATESTMODE == "On") Log_Info("Ship_Add2Sea ERROR : SHIP " + iShipType + ", have no name!   NPCid = "+ rCharacter.id);
		return;
	}
	if (iRealShip >= SHIP_TYPES_QUANTITY)
	{
		Trace("Character.id = " + rCharacter.id + ", have invalid ship type = " + iShipType + ", and try load to sea");
		return;
	}
	// boal -->
	// 22.04.05 сброс всех отношений
    if (!CheckAttribute(rCharacter, "AlwaysEnemy") && !CheckAttribute(rCharacter, "AlwaysFriend")) // у врагов не трем
    {
    	DelCharacterRelation(iCharacterIndex);
    }
    else
    {
		if (CheckAttribute(rCharacter, "AlwaysFriend"))
		{
			SetCharacterRelationBoth(iCharacterIndex, GetMainCharacterIndex(), RELATION_FRIEND);
		}
		if (CheckAttribute(rCharacter, "AlwaysEnemy"))
		{
			SetCharacterRelationBoth(iCharacterIndex, GetMainCharacterIndex(), RELATION_ENEMY);
		}
    }
    DeleteAttribute(rCharacter, "Ship_SetTaskAbordage"); // boal
    DeleteAttribute(rCharacter, "Killer.status"); // boal 09.06.05 SUPER FIX
    DeleteAttribute(rCharacter, "CheckFlagYet"); // флаг распознования врага
    DeleteAttribute(rCharacter, "CheckNationBounty"); // Проверка НЗГ за нацию друга базе
    DeleteAttribute(rCharacter, "ShipCannonChargeType"); // флаг офов, чем пулять постоянно, ставится игроком командами, до след приказа Атака или конца снарядов
    
	if (CheckAttribute(rCharacter, "DontCheckFlag"))
	{
	    rCharacter.CheckFlagYet = true;
	}
    rCharacter.TmpSkillRecall = "0"; //boal 25.05.04 оптимизация расчета, когда == 0 считаем скилы
    rCharacter.Tmp.SpeedRecall = 0; // оптимизация скорости и маневра
    rCharacter.Tmp.fShipSpeed  = 1; // начальная инициация
	rCharacter.Tmp.fWatchFort  = rand(15); // оптимизация оглядок на форт
	rCharacter.Tmp.fWatchFort.Qty = 15;
    // boal <--
	if (iCharacterIndex >= FANTOM_CHARACTERS)
	{
		SetBaseShipData(rCharacter);
		Ship_SetFantomData(rCharacter);
		Fantom_SetUpgrade(rCharacter, sFantomType);		
        Fantom_SetCannons(rCharacter, sFantomType);
		Fantom_SetBalls(rCharacter, sFantomType);
		Fantom_SetGoods(rCharacter, sFantomType);
		SaveCurrentNpcQuestDateParam(rCharacter, "Add2SeaTime"); //фантомы помнят время входа в море
	}
    AcceptWindCatcherPerk(rCharacter); // применение перка ловец ветра, тут работает, а не где был в к3 boal 02/08/06
	//rCharacter.TmpPerks.Turn = false;

	CharacterUpdateShipFromBaseShip(iCharacterIndex);

	rCharacter.Ship.Ang.y = 0.0;

	Ship_ClearImpulseStrength(rCharacter);
	Ship_SetLightsAndFlares(rCharacter);
	Ship_SetTrackSettings(rCharacter);

	aref baseship;
	ref refBaseShip;
	
	makearef(baseship,rCharacter.ship);
	int nShipType = GetCharacterShipType(rCharacter);
	refBaseShip = GetRealShip(nShipType);
	
	rCharacter.Tmp.BortsReloaded.Event = false;
	rCharacter.Tmp.BortsReloaded.cannonl = false;
	rCharacter.Tmp.BortsReloaded.cannonr = false;
    rCharacter.BOAL_ReadyCharge = "1"; // в начале всегда заряжен ядрами, пусть и палит ими
    
	rCharacter.Features.GeraldSails = true;
	rCharacter.Ship.LastBallCharacter = -1;
	rCharacter.Ship.WindDotShip = 1.0;
	rCharacter.Ship.Speed.z = 0.0;
	rCharacter.Ship.Speed.y = 0.0;
	rCharacter.Ship.Speed.x = 0.0;
	
	//  убрать это, когда будет в ядре работать
	rCharacter.Ship.BoxSize.x = 1.0;  // должно считаться в ядре :( не работает
	rCharacter.Ship.BoxSize.y = 1.0;
	rCharacter.Ship.BoxSize.z = 2.0;
	
	rCharacter.Ship.Strand = false;
	rCharacter.Ship.Strand.SndID = SOUND_INVALID_ID;
	rCharacter.Ship.Stopped = false;
	rCharacter.Ship.POS.Mode = SHIP_SAIL;
	rCharacter.Ship.SeaAI.Init.AbordageDistance = 30.0;
	// boal -->
	ref	rCannon = GetCannonByType(sti(rCharacter.Ship.Cannons.Type));
	float range = 550;
	if (CheckAttribute(rCannon, "FireRange")) range = stf(rCannon.FireRange);
	rCharacter.Ship.SeaAI.Init.AttackDistance = range  / (1.4 + frandSmall(2.0)); // это очень важный параметр, он определяет дистанцию АИ, на которой будет стараться держаться корабль
	rCharacter.Ship.SeaAI.Init.AttackDistance.qtyTryChangeCannon = 0; //счетчик попыток смены боеприпасов при полном боезапаса, для фикса неубегаек
	// boal <--
	rCharacter.Ship.SeaAI.Init.FollowDistance = makefloat(180.0 + rand(120)); // было 300, делаю рандом для разнообразия поведения компаньонов и следования в группе

	rCharacter.Ship.Sounds = "";

	if(sti(rCharacter.Ship.Cannons.Type) == CANNON_TYPE_NONECANNON)
	{
		rCharacter.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
	}

	if (bFromCoast == false) { rCharacter.Ship.Speed.z = 1.0; }

	// create ship
	Event("eSwitchPerks", "l", iCharacterIndex);											// Perks
	//Event(SHIP_UPDATE_PARAMETERS, "lf", iCharacterIndex, stf(rCharacter.Ship.Speed.z));		// Parameters
	
	//ugeen --> жесть !! у энкаунтеров не снят атрибут Ship.Sink <-- 3 часа трахался из-за этой ошибки :(  <-- из-за нее некорректно работал мод флагов
	if(CheckAttribute(rCharacter,"Ship.Sink")) {trace("ShipSink rCharacter.id = " + rCharacter.id); DeleteAttribute(rCharacter,"Ship.Sink");}
	
	CreateEntity(&Characters[iCharacterIndex], "Ship");
	
    Event(SHIP_UPDATE_PARAMETERS, "lf", iCharacterIndex, stf(rCharacter.Ship.Speed.z));		// Parameters      после создания корабля
    		
	aref arChar, arShip;
	makearef(arChar, characters[iCharacterIndex]);
	makearef(arShip, RealShips[iShipType]);

	Ship_CreateStaticSounds(rCharacter);

	//SendMessage(&AISea, "liaa", AI_MESSAGE_ADD_SHIP, &Characters[iCharacterIndex], &Characters[iCharacterIndex], &RealShips[iShipType]);
	SendMessage(&AISea, "liaa", AI_MESSAGE_ADD_SHIP, &Characters[iCharacterIndex], arChar, arShip);

	float ax = 0.0;
	float az = 0.0;	
/*	
	if(SetHeel_XZ(rCharacter,  &ax, &az)) // крен
	{
		SendMessage(rCharacter, "lff", MSG_SHIP_SET_HEEL_XZ, ax, az); 
	}	
*/	
	// Только для примера - освободить все паруса одного корабля от эффекта надувания
	//SendMessage(&Sail,"li", MSG_SAIL_FREE_GROUP, &Characters[iCharacterIndex]);
	
    /* if (!CheckAttribute(rCharacter, "Ship.BoxSize.x"))
	{
		trace("No Ship.BoxSize id=" + rCharacter.id);
		rCharacter.Ship.BoxSize.x = 1.0;  // должно считаться в ядре
		rCharacter.Ship.BoxSize.y = 1.0;
		rCharacter.Ship.BoxSize.z = 2.0;
	} */
	if(isOffline) ReloadProgressUpdate();
	
	Ships[iNumShips] = iCharacterIndex;
	iNumShips++;
}

void Ship_RecreateStaticSounds()
{
	for (int i=0; i<iNumShips; i++) {
	     if (makeint(Ships[i]) > -1 && makeint(&Characters[Ships[i]]) > -1)
			Ship_CreateStaticSounds(&Characters[Ships[i]]);
	}
	
	if (CheckAttribute(&WeatherParams, "Rain.Sound") && sti(WeatherParams.Rain.Sound))
        Whr_SetRainSound(true, sti(Weathers[iCurWeatherNum].Night));

}

void Ship_CreateStaticSounds(ref rCharacter)
{
    if (!CheckAttribute(rCharacter, "Ship.Pos.x")) return; // fix
	if (GetCharacterShipType(rCharacter) == SHIP_NOTUSED) return; // может уже не быть
	
    ref refBaseShip = GetRealShip(GetCharacterShipType(rCharacter));
	// create water sound
	float fX = stf(rCharacter.Ship.Pos.x);
	float fY = stf(rCharacter.Ship.Pos.y);
	float fZ = stf(rCharacter.Ship.Pos.z);
	rCharacter.Ship.Sounds.WaterID.x = 0.0;
	rCharacter.Ship.Sounds.WaterID.y = 0.0;
	rCharacter.Ship.Sounds.WaterID.z = 0.12;
	rCharacter.Ship.Sounds.WaterID = Play3DSoundComplex("ship_water_" + refBaseShip.Soundtype, fX, fY, fZ, true, false);
	if (sti(rCharacter.Ship.Sounds.WaterID) > 0) { Sound_SetVolume(sti(rCharacter.Ship.Sounds.WaterID), 0.0); }
	rCharacter.Ship.Sounds.WaterSpeed = 30.0;

	// create sails sound
	rCharacter.Ship.Sounds.SailsID.x = 0.0;
	rCharacter.Ship.Sounds.SailsID.y = 0.5;
	rCharacter.Ship.Sounds.SailsID.z = 0.0;
	rCharacter.Ship.Sounds.SailsID = Play3DSoundComplex("sails_up_" + refBaseShip.Soundtype, fX, fY, fZ, true, false);
	if (sti(rCharacter.Ship.Sounds.SailsID) > 0) { Sound_SetVolume(sti(rCharacter.Ship.Sounds.SailsID), 0.0); }
	rCharacter.Ship.Sounds.SailsMove = 0.0;

	// create turn sound
	rCharacter.Ship.Sounds.TurnID.x = 0.0;
	rCharacter.Ship.Sounds.TurnID.y = 0.0;
	rCharacter.Ship.Sounds.TurnID.z = 0.0;
	rCharacter.Ship.Sounds.TurnID = Play3DSoundComplex("ship_turn_" + refBaseShip.Soundtype, fX, fY, fZ, true, false);
	if (sti(rCharacter.Ship.Sounds.TurnID) > 0) { Sound_SetVolume(sti(rCharacter.Ship.Sounds.TurnID), 0.0); }
	rCharacter.Ship.Sounds.TurnSpeed = 0.05;
}

void Ship_PlaySound3DComplex(ref rCharacter, string sSoundID, float fVolume, float fX, float fY, float fZ)
{
	//return;
	float x = stf(rCharacter.Ship.Pos.x);
	float y = stf(rCharacter.Ship.Pos.y);
	float z = stf(rCharacter.Ship.Pos.z);

	float aY = stf(rCharacter.Ship.Ang.y);

    if (!CheckAttribute(rCharacter, "Ship.BoxSize.x")) return; // fix габаритов
     
	float x1 = fX * stf(rCharacter.Ship.BoxSize.x) / 2.0;
	float z1 = fZ * stf(rCharacter.Ship.BoxSize.z) / 2.0;
	RotateAroundY(&x1, &z1, cos(aY), sin(aY));

	int iSoundID = Play3DSound(sSoundID, x + x1, y + fY * stf(rCharacter.Ship.BoxSize.y) / 2.0, z + z1);
	if (iSoundID > 0) { Sound_SetVolume(iSoundID, fVolume); }
}

void Ship_PlaySound3D(ref rCharacter, string sSoundID, float fVolume)
{
	float x = stf(rCharacter.Ship.Pos.x);
	float y = stf(rCharacter.Ship.Pos.y);
	float z = stf(rCharacter.Ship.Pos.z);

	int iSoundID = Play3DSound(sSoundID, x, y, z);
	if (iSoundID > 0) { Sound_SetVolume(iSoundID, fVolume); }
}

void Ship_OnBortReloaded()
{
	aref aCharacter = GetEventData();
	string sBort = GetEventData();

	if (!bSeaLoaded || bAbordageStarted) { return; }  // fix
	// далее по коду была глупость, тк прерывание шло по всем НПС, звуков таких не было вовсе в ресурсах, те мина была в игре. "Сапер boal"
	if (sti(aCharacter.index) != nMainCharacterIndex) { return; } // fix
	/*{
		if (sBort == "cannonl" || sBort == "cannonr") { Ship_PlaySound3D(aCharacter, "bortreloaded_" + sBort, 1.0);	}
		//"bortreloaded_all"
	}*/

	if (!sti(aCharacter.Tmp.BortsReloaded.Event))
	{
		aCharacter.Tmp.BortsReloaded.Event = true;
		PostEvent("Ship_BortReloadEvent", 300, "a", aCharacter);
	}
	if (sBort == "cannonl") { aCharacter.Tmp.BortsReloaded.cannonl = true; }
	if (sBort == "cannonr") { aCharacter.Tmp.BortsReloaded.cannonr = true; }
}

void Ship_BortReloadEvent()
{
	aref aCharacter = GetEventData();
	
	if (sti(aCharacter.Tmp.BortsReloaded.Event))
	{
		bool bLeft = sti(aCharacter.Tmp.BortsReloaded.cannonl) == true;
		bool bRight = sti(aCharacter.Tmp.BortsReloaded.cannonr) == true;

		if (bLeft && bRight)
		{
			//Ship_PlaySound3D(aCharacter, "bortreloaded_all", 1.0);
			// типа перезарядка двух бортов PlaySound("interface\_GunReady.wav");
		}
		else
		{
			if (bLeft)  { PlaySound("interface\_GunReadyL.wav"); }
			if (bRight) { PlaySound("interface\_GunReadyR.wav"); }
		}
	}

	Ship_ClearBortsReloadedEvent(aCharacter);
}

void Ship_ClearBortsReloadedEvent(aref aCharacter)
{
	aCharacter.Tmp.BortsReloaded.Event = false;
	aCharacter.Tmp.BortsReloaded.cannonl = false; 
	aCharacter.Tmp.BortsReloaded.cannonr = false; 
}

void Ship_ChangeChargeEvent() // нигде не используется???
{
	string	sBallName;
	
	ref rCharacter = GetCharacter(GetEventData());

	SendMessage(&AISea, "la", AI_MESSAGE_CANNON_RELOAD, rCharacter);
	sBallName = GetEventData();
	rCharacter.Ship.Cannons.Charge = sBallName;
	Cannon_RecalculateParameters(sti(rCharacter.index));

	//fix if (bSeaLoaded) { Ship_PlaySound3D(rCharacter, "reloadstart_" + sBallName, 1.0); }

	Ship_ClearBortsReloadedEvent(rCharacter);
}

void Ship_ChangeCharge(ref rCharacter, int iNewChargeType)
{
	SendMessage(&AISea, "la", AI_MESSAGE_CANNON_RELOAD, rCharacter); // must be first line in this function

	ref rGood = GetGoodByType(iNewChargeType);
	rCharacter.Ship.Cannons.Charge = rGood.name;
	rCharacter.Ship.Cannons.Charge.Type = iNewChargeType;

	Cannon_RecalculateParameters(sti(rCharacter.index));
	rCharacter.BOAL_ReadyCharge = "1"; // чтоб пока не стрельнул не выпендривал (нужно для приказа компаньону)
	
	//fix Ship_PlaySound3D(rCharacter, "reloadstart_" + rGood.name, 1.0);

	Ship_ClearBortsReloadedEvent(rCharacter);
}

void Ship_OnCreate()
{
	ref rCharacter = GetCharacter(GetEventData());
	
	rCharacter.Ship.Speed.z = 0.0;
	rCharacter.Ship.Speed.y = 0.0;
	rCharacter.Ship.Speed.x = 0.0;
}

void Ship_SetSurrendered(ref rCharacter)
{
	if (LAi_IsDead(rCharacter) || sti(rCharacter.ship.type) == SHIP_NOTUSED) return; 
	if (CheckAttribute(rCharacter,"surrendered")) return;
	
	ref rBaseShip = GetRealShip(sti(rCharacter.Ship.Type));
	rCharacter.surrendered = true;	
	Ship_FlagRefresh(rCharacter); //флаг на лету
	
	string sSurrenderString;
	string sSurrenderShipType = XI_ConvertString(rBaseShip.BaseName);
	sSurrenderString = sSurrenderShipType + " '" + rCharacter.Ship.Name + "' " +GetShipSexWord(rBaseShip.BaseName, "выбросил ", "выбросила ") + " белый флаг";
	Log_SetStringToLog(sSurrenderString);
	
	Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
	
	SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_FRIEND);
	rCharacter.AlwaysFriend = true; // флаг - не обижаться на выстрелы, абордировать нельзя, можно только выслать шлюпку
	UpdateRelations();
	RefreshBattleInterface();
	DoQuestCheckDelay("NationUpdate", 1.5);
}

bool Ship_CheckSurrendered(ref echr)
{
	bool bOk = true;

	if (LAi_IsDead(echr) || sti(echr.ship.type) == SHIP_NOTUSED) return false;
	if (sti(echr.index) == nMainCharacterIndex) return false;
	if (IsCompanion(echr)) return false;	
	if (GetNationRelation2MainCharacter(sti(echr.nation)) != RELATION_ENEMY) return false;
	if (CheckAttribute(echr,"situation")) return false;
	
	if(CheckAttribute(echr,"DontSurrender")) return false;
	
	if (sti(echr.Nation) == PIRATE || CheckAttribute(echr, "DontRansackCaptain")) return false; // квестовые и пираты не выбрасывают белый флаг
	
	ref mchr = GetMainCharacter();
	
	if (sti(echr.rank) > (40 - MOD_SKILL_ENEMY_RATE)) bOk = false; 	
	if (sti(mchr.rank) < (sti(echr.rank) - MOD_SKILL_ENEMY_RATE / 2))  bOk = false;
	
	int eclass = GetCharacterShipClass(echr);
	int mclass = GetCharacterShipClass(mchr);
	if (eclass == 1) bOk = false;
	
	if(!bOk) 
	{
		echr.DontSurrender = true;
		return false;
	}	
	
	float fCrewRate = 0.5;  
	if (CheckAttribute(echr, "Ship.Mode"))
	{
		switch(echr.Ship.Mode)
		{
			case "Trade":
				fCrewRate = 0.6;
			break;
			case "War" 	:
				fCrewRate = 0.2;
			break;
		}
	}
	float mcrew = stf(GetWeaponCrew(mchr, GetCrewQuantity(mchr))); // честный учет с оружием
	float ecrew = stf(GetCrewQuantity(echr));
	
	float fRep    = abs(REPUTATION_NEUTRAL - sti(mchr.reputation.nobility)) / 50.0; // приведение к 0..1
	float emorale = stf(echr.ship.crew.morale) / MORALE_MAX; // 0..1  это рандом
	float mmorale = stf(mchr.ship.crew.morale) / MORALE_MAX; // 0..1
	float mskill  = (GetSummonSkillFromNameToOld(mchr, "Leadership") + GetSummonSkillFromNameToOld(mchr, "Grappling")) / 20.0;  // 0..10
	float eskill  = (GetCharacterSkillToOld(echr, "Leadership") + GetCharacterSkillToOld(echr, "Defence")) / 20.0;    // 0..10
	
	mcrew = mcrew * (mcrew * GetCrewExp(mchr, "Soldiers")) / (GetOptCrewQuantity(mchr) * GetCrewExpRate()); 
    ecrew = ecrew * (ecrew * GetCrewExp(echr, "Soldiers")) / (GetOptCrewQuantity(echr) * GetCrewExpRate());  // это рандом, а значит случайность
	
    mcrew = mcrew *(0.5 + mmorale);
    ecrew = ecrew *(0.5 + emorale); // рандом в  emorale - она ранд
    
    mcrew = mcrew * (0.2 + mskill)*(0.05 + fRep)*fCrewRate;
    ecrew = ecrew * (0.2 + eskill);

	int mShip = GetCompanionQuantity(mchr);
    int eShip;
    string sGroupID = Ship_GetGroupID(echr);
    if (sGroupID != "") eShip = Group_GetLiveCharactersNum(sGroupID);
    else				eShip = 1;

	mcrew = mcrew * (1.0 + mclass / 20.0); // влияние класса минимально, тк есть в экипаже
    ecrew = ecrew * (1.0 + eclass / 20.0);  // класс также влияет наоборот, дает бонус мелким
    
    mcrew = mcrew * (1.0 + (mShip-1) / 5.0);
    ecrew = ecrew * (1.0 + (eShip-1) / 5.0);

    if (mcrew > ecrew)
	{
		// проверка на мин HP && SP		
		if (GetSailPercent(echr) < 25.0 || GetHullPercent(echr) < 25.0) return true; // выбросил белый флаг			
	}
	return false; // не сдался
}

void Ship_CheckSituation()
{
	ref		rShip;
	aref	rSituation;
	
	aref	rCharacter = GetEventData();
	aref	rShipObject = GetEventData();
	
	if (sti(rCharacter.index) == nMainCharacterIndex) { return; }
	if (LAi_IsDead(rCharacter) || sti(rCharacter.ship.type) == SHIP_NOTUSED) { return; }  // super fix boal
	
	//Log_Testinfo("Ship_CheckSituation " + rCharacter.id);
	
	if (!CheckAttribute(rCharacter, "SeaAI.Task"))
	{
		trace("Character " + rCharacter.id  + " without task");
		rCharacter.SeaAI.Task = AITASK_NONE;
	}

	rShip = GetRealShip(sti(rCharacter.Ship.Type));
	makearef(rSituation, rCharacter.SeaAI.Update.Situation);

	float	fMinEnemyDistance = stf(rSituation.MinEnemyDistance);
	float	fDistance;
	// boal fix AI fMinEnemyDistance - не сбрасывается :( 23.05.05
	if (sti(rCharacter.Ship.LastBallCharacter) != -1 && LAi_IsDead(GetCharacter(sti(rCharacter.Ship.LastBallCharacter))))
	{
        rCharacter.Ship.LastBallCharacter = -1;
	}
	if (CheckAttribute(rCharacter, "SeaAI.Task.Target"))
	{
		if (rCharacter.SeaAI.Task.Target != "" && LAi_IsDead(GetCharacter(sti(rCharacter.SeaAI.Task.Target))))
	    {
	        rCharacter.SeaAI.Task.Target = "";
	    }
	    /*if (rCharacter.SeaAI.Task == AITASK_ABORDAGE && rCharacter.SeaAI.Task.Target == "")
	    {
	        Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), nMainCharacterIndex);  // это фикс зависшего абордажа
	    } */
    }
	// <--
	// boal проверка на абордаж не главного героя 27.01.2004 -->
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    // check ships for abordage
    if (Ship_AutoAbordage(rCharacter, fMinEnemyDistance)) { return; }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
	// ugeen ->  проверка на возможность выбросить белый флаг // комменчу нафик ибо толком не работает - 27.11.17
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//if(!CheckAttribute(rCharacter,"surrendered") && Ship_CheckSurrendered(rCharacter)) Ship_SetSurrendered(rCharacter);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// Warship 08.07.09 Запрет спуска парусов
	if(CheckAttribute(rCharacter, "CanDropSails") && !sti(rCharacter.CanDropSails)) //  && Ship_GetSailState(rCharacter) < 1.0 // Так работает через раз
	{
		Ship_SetSailState(sti(rCharacter.index), 1.0);
	}
		
	// check for enought quantity of balls 
	int iShipCannonsNum  = GetCannonsNum(rCharacter);//sti(rShip.CannonsQuantity);
	int iCurrentBallType = sti(rCharacter.Ship.Cannons.Charge.Type);
	bool bBalls, bKnippels, bBombs, bGrapes;
	bBalls = true; bKnippels = true; bBombs = true; bGrapes = true;
	// boal -->
	if (CheckAttribute(rCharacter, "ShipCannonChargeType")) // офам приказ, чем палить все время
	{
	    if (GetCargoGoods(rCharacter, sti(rCharacter.ShipCannonChargeType))    < iShipCannonsNum)
	    {
	        DeleteAttribute(rCharacter, "ShipCannonChargeType"); // следующий проход решит на что менять заряд
	    }
	}
	else
	{
        if (GetCargoGoods(rCharacter,GOOD_BALLS)    < iShipCannonsNum) { bBalls    = false; }
		if (GetCargoGoods(rCharacter,GOOD_BOMBS)    < iShipCannonsNum) { bBombs    = false; }
		if (GetCargoGoods(rCharacter,GOOD_KNIPPELS) < iShipCannonsNum) { bKnippels = false; }
		if (GetCargoGoods(rCharacter,GOOD_GRAPES)   < iShipCannonsNum) { bGrapes   = false; }

		int iNewBallType = iCurrentBallType;
		if( !CheckAttribute(rCharacter,"BOAL_ReadyCharge"))
	    {
	        rCharacter.BOAL_ReadyCharge = "1";
	    }
	    if (rCharacter.BOAL_ReadyCharge == "0")
	    {
	        iNewBallType = Ship_FindOtherBallType(rCharacter, fMinEnemyDistance, bBalls, bBombs, bGrapes, bKnippels);
	        rCharacter.BOAL_ReadyCharge = "1";
	    	if (iNewBallType >= 0 && iNewBallType != iCurrentBallType)
		    {
		   	   Ship_ChangeCharge(rCharacter, iNewBallType);
		    }
	    }
	    else
	    {
	        ref rCannon = GetCannonByType(sti(rCharacter.Ship.Cannons.Type));
		    float range = stf(rCannon.FireRange);
		    if ((fMinEnemyDistance > (range*0.9)) && bBalls) // из зоны ушли
	        {
	           iNewBallType = GOOD_BALLS;
	           if (iNewBallType != iCurrentBallType)
	           {
	               Ship_ChangeCharge(rCharacter, iNewBallType);
	           }
	        }
	    }
    }
    // выбор снаряда <--
    // сбособ второй, модифицированный от к3, но по тестам старый вмл милее и оптимальнее
	/*if(CheckAttribute(rCharacter, "Ship.Cannons.borts.cannonr.ChargeRatio"))
	{
		float fRightChargeRatio = stf(rCharacter.Ship.Cannons.borts.cannonr.ChargeRatio);
		float fLeftChargeRatio = stf(rCharacter.Ship.Cannons.borts.cannonl.ChargeRatio);
		
		float fFrontChargeRatio = 1.0;
		float fBackChargeRatio = 1.0;
		
		if (CheckAttribute(rCharacter, "Ship.Cannons.borts.cannonf.ChargeRatio"))
		{
			fFrontChargeRatio = stf(rCharacter.Ship.Cannons.borts.cannonf.ChargeRatio);
			fBackChargeRatio = stf(rCharacter.Ship.Cannons.borts.cannonb.ChargeRatio);
		}
		
		if (!CheckAttribute(rCharacter, "Sea_AI.cannon.charge"))
		{
			if (fRightChargeRatio <= 0.3 || fLeftChargeRatio <= 0.3 || fBackChargeRatio <=0.3 || fFrontChargeRatio <=0.3)
			{
				iNewBallType = Ship_FindOtherBallType(rCharacter, fMinEnemyDistance, bBalls, bBombs, bGrapes, bKnippels);
				rCharacter.Sea_AI.cannon.charge = iNewBallType;
			}
		}
		else
		{
			// делаем проверку на хрень типа:
			// корабль сделал выстрел
			// зарядился
			// но ситуация изменилась, и он не может достать выстрелом никого
			// причем эта проверка не позволит персу 
			// постоянно перезаряжать пушки
			// ибо при анализе ситуации 
			// заряд может и не измениться
			if(!CheckAttribute(rCharacter, "Sea_AI.cannon.charge.lasttime"))
			{
				rCharacter.Sea_AI.cannon.charge.lasttime = 0;
			}
			if (fRightChargeRatio == 1.0 && fLeftChargeRatio == 1.0 && fBackChargeRatio == 1.0 && fFrontChargeRatio == 1.0)
			{
				rCharacter.Sea_AI.cannon.charge.lasttime = sti(rCharacter.Sea_AI.cannon.charge.lasttime) + 1;
			}
			//int iCannonTime = sti(Cannons[sti(rCharacter.Ship.Cannons.Type)].ReloadTime) / 2;
			if(sti(rCharacter.Sea_AI.cannon.charge.lasttime) > 20)
			{
				iNewBallType = Ship_FindOtherBallType(rCharacter, fMinEnemyDistance, bBalls, bBombs, bGrapes, bKnippels);
				rCharacter.Sea_AI.cannon.charge = iNewBallType;
			}
		}
        if (iNewBallType >= 0 && iNewBallType != iCurrentBallType) 
		{
			Ship_ChangeCharge(rCharacter, iNewBallType);
		}
	} */
	bool bIsCompanion = IsCompanion(rCharacter);
	
	// check some tasks
	if (CheckAttribute(rCharacter, "SeaAI.Task") && CheckAttribute(rCharacter, "SeaAI.Task.Target"))
	{
		switch (sti(rCharacter.SeaAI.Task))
		{
			// boal potc -->
			case AITASK_BRANDER:
				ref rCharacter2Brander = GetCharacter(sti(rCharacter.SeaAI.Task.Target));
				ref rBaseShip = GetRealShip(sti(rCharacter.Ship.Type));
				float fBranderDistance = 45.0 + (7.0 - stf(rBaseShip.Class)) * 15.0; // просьба масс
				fDistance = Ship_GetDistance2D(rCharacter, rCharacter2Brander); // boal 21.01.2004
				if (fBranderDistance > fDistance)
				{
					// fire ship
					Ship_SetExplosion(rCharacter, rShipObject); //boal 27.09.05
					Log_Info("" + XI_ConvertString(rBaseShip.BaseName) + " '" + rCharacter.Ship.Name + "' " + GetShipSexWord(rBaseShip.BaseName, "взорвал", "взорвала") + " крюйт камеру.");
					return;
				}
				//Trace("test1 rCharacter2Brander = " + rCharacter2Brander.index);
			break;
			case AITASK_ATTACK:
				//to_del log
				//Log_SetStringToLog("Дистанция: " + Ship_GetDistance2D(rCharacter, &characters[sti(rCharacter.SeaAI.Task.Target)]) + "   Атаки: " + rCharacter.Ship.SeaAI.Init.AttackDistance);
				//-->> если есть цель для Атаки, то оптимизируем оптимальное расстояние для стрельбы	
				//только при полном боекомплекте на первом такте ожидания
				if (CheckAttribute(rCharacter, "Sea_AI.cannon.charge.lasttime") && sti(rCharacter.Sea_AI.cannon.charge.lasttime) == 1) 
				{
					if (sti(rCharacter.Ship.SeaAI.Init.AttackDistance.qtyTryChangeCannon) == 2 || sti(rCharacter.Ship.SeaAI.Init.AttackDistance.qtyTryChangeCannon) == 5)
					{
						rCharacter.Ship.SeaAI.Init.AttackDistance = 50; //отрезаем неубегаек
						Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.SeaAI.Task.Target));
					}
					else
					{
						float fAttackDist = Ship_GetDistance2D(rCharacter, &characters[sti(rCharacter.SeaAI.Task.Target)]);
						if (fAttackDist < 500)
						{
							rCharacter.Ship.SeaAI.Init.AttackDistance = fAttackDist;
							Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.SeaAI.Task.Target));
						}	
					}
				}
			break;
            // абордаж сам отработает
		}
	}
	// boal AI компа -->
    if (!bIsCompanion) //fix 171204 boal Не нужно наших с толку сбивать
    {
        string sGroupID = Ship_GetGroupID(rCharacter);
        
		if (CheckAttribute(rCharacter, "SeaAI.Task.Target"))
		{
	        if (iNewBallType < 0 || iShipCannonsNum < (sti(rShip.CannonsQuantity) / 10))
			{
				// maybe we can abordage???
				Ship_SetTaskRunaway(SECONDARY_TASK,sti(rCharacter.index), sti(rCharacter.SeaAI.Task.Target));
				return;
			}
		}
		if (GetNationRelation2MainCharacter(sti(rCharacter.nation)) == RELATION_ENEMY) // враг Гл героя
	    {
            if (CheckAttribute(rCharacter, "AlwaysFriend"))
	        {
	            SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_FRIEND);
	        }
	        else
	        {
				//--> eddy. анализим форт. проверяем наличие форта, враждебность и залоченный таск
				if (CheckAttribute(rCharacter, "WatchFort") && bIsFortAtIsland && GetRelation(sti(rCharacter.index), iFortCommander) == RELATION_ENEMY && !CheckAttribute(rCharacter, "ShipTaskLock"))
				{
					if (sti(rCharacter.Tmp.fWatchFort) >= sti(rCharacter.Tmp.fWatchFort.Qty))
					{					
						rCharacter.Tmp.fWatchFort = 0; //сброс счетчика оптимизации
						//проверяем расстояние до форта и наличие флага 'следить за фортом'
						if (GetDistance2D(stf(rCharacter.Ship.Pos.x), stf(rCharacter.Ship.Pos.z), fFort_x, fFort_z) < 1000)
						{
							Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), iFortCommander);
							rCharacter.Tmp.fWatchFort.Qty = 200; //не лочим таск, но увеличиваем паузу срабатывания
							//Log_SetStringToLog("Я ("+rCharacter.id+") ухожу от форта."); 
						}
					}
					else
					{
						rCharacter.Tmp.fWatchFort = sti(rCharacter.Tmp.fWatchFort) + 1;
					}
				}
				//<-- анализим форт
				if (!CheckAttribute(rCharacter, "SinkTenPercent")) // это не ЧЖ и не идущие на абордаж пираты
	            {
					int   SailsPercent    = sti(rCharacter.Ship.SP);
			        float HPPercent       = GetHullPercent(rCharacter);
			        int   CrewQuantity    = sti(rCharacter.Ship.Crew.Quantity);
			        int   MinCrewQuantity = GetMinCrewQuantity(rCharacter);
					int   iCharactersNum1, iCharactersNum2;

					if (GetRelation(sti(rCharacter.index), GetMainCharacterIndex()) != RELATION_ENEMY)
					{
						SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
				        Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
				        UpdateRelations();
				        DoQuestCheckDelay("NationUpdate", 0.9);
			        }
                    if (sti(rCharacter.Ship.LastBallCharacter) != -1 && !CheckAttribute(rCharacter, "Ship_SetTaskAbordage") && !CheckAttribute(rCharacter, "ShipTaskLock")) // нет приказа на абордаж
                    {
						if (!CheckAttribute(rCharacter, "SeaAI.Task") || sti(rCharacter.SeaAI.Task) == AITASK_NONE)
				        {
							//кэп без таска, такое маловероятно. но тем не менее...
							if (CheckAttribute(rCharacter, "AnalizeShips"))
							{									
								//проверим, стоит ли атаковать
								if (stf(rCharacter.ship.hp) < (stf(characters[sti(rCharacter.Ship.LastBallCharacter)].ship.hp) / 2))
								{
									Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
								}
								else
								{
									Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
								}							
							}
							else
							{	//кэп без атрибута проверки кораблей - всегда в атаке
								Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
							}									        
						}
				        else
				        {
							if ((SailsPercent > 50) && (HPPercent > 30) && sti(rCharacter.SeaAI.Task) != AITASK_RUNAWAY) // не убегает уже
					        {
								//корабль в хорошем состоянии, таск не ранэвей. здесь тоже проверим при наличии атрибута анализа кораблей
								if (CheckAttribute(rCharacter, "AnalizeShips"))
								{									
									// Warship fix Должно быть здесь
										iCharactersNum1 =  Group_GetLiveCharactersNum(rCharacter.SeaAI.Group.Name);
										iCharactersNum2 =  Group_GetLiveCharactersNum(characters[sti(rCharacter.Ship.LastBallCharacter)].SeaAI.Group.Name);	
									
									if(stf(rCharacter.ship.hp) < (stf(characters[sti(rCharacter.Ship.LastBallCharacter)].ship.hp) / 2))
									{
										if ((iCharactersNum1 / iCharactersNum2) >= 2.2 && iCharactersNum2 > 0) 
										{
											Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
										}
										else
										{
											Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
										}
									}
									else
									{	//если есть шанс победить, то проверяем еще и количественное соотношение групп. не лезть на крупные эскадры
										if((iCharactersNum2 / iCharactersNum1) >= 2.0 && sti(RealShips[sti(rCharacter.ship.type)].Class) > sti(RealShips[sti(characters[sti(rCharacter.Ship.LastBallCharacter)].ship.type)].Class))
										{
											Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
										}
										else
										{
											Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
										}
									}
								}
								else
								{	//кэп без атрибута проверки кораблей - всегда в атаке
									Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
								}
					        }  
					        else
					        {
						        // смертники!!!
						        if (HPPercent < 15)
						        {
						            if (rand(20) == 1)// очень часто плохо - убивает все вокруг
						            {
						                Ship_SetTaskBrander(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
						            }
						        }
						        else
						        {
						        	if ((HPPercent < 30) || (CrewQuantity <= (2*MinCrewQuantity)))// убрано, по тестам Дира || SailsPercent < 35)
							        {
							            Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
							        }
									else
									{	//eddy. здесь смотрим Runaway. проверяем атрибут анализа шипов и анализим, стоит ли атаковать
										if (CheckAttribute(rCharacter, "AnalizeShips") && stf(rCharacter.ship.hp) > (stf(characters[sti(rCharacter.Ship.LastBallCharacter)].ship.hp) / 2))
										{
											//может только что ушел от форта? 
											if (sti(rCharacter.Tmp.fWatchFort.Qty) == 200)
											{
												//тогда Runaway меняем за один такт до проверки форта
												if (sti(rCharacter.Tmp.fWatchFort) >= 199)
												{
													if (sti(rCharacter.Ship.LastBallCharacter) == iFortCommander)
													{	//только не на форткоммандера, комикадзе не делаем
														Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
													}
													else
													{
														Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
													}
												}
											}
											else
											{	//форт тут ни при чем
												if (sti(rCharacter.Ship.LastBallCharacter) == iFortCommander)
												{	//только не на форткоммандера, комикадзе не делаем
													Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
												}
												else
												{
													iCharactersNum1 =  Group_GetLiveCharactersNum(rCharacter.SeaAI.Group.Name);
													iCharactersNum2 =  Group_GetLiveCharactersNum(characters[sti(rCharacter.Ship.LastBallCharacter)].SeaAI.Group.Name);	
													if ((iCharactersNum2 / iCharactersNum1) >= 2.0 && sti(RealShips[sti(rCharacter.ship.type)].Class) > sti(RealShips[sti(characters[sti(rCharacter.Ship.LastBallCharacter)].ship.type)].Class))
													{
														Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
													}
													else
													{
														Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
													}
												}
											}		
										}
									}
						        }
					        }
				        }
			        }
			        else
			        {   
						// если плывет мимо и нет rCharacter.Ship.LastBallCharacter (никто по нему не стрелял)
                        if (!CheckAttribute(rCharacter, "ShipTaskLock"))
						{
				            if (!CheckAttribute(rCharacter, "SeaAI.Task.Target") || sti(rCharacter.SeaAI.Task.Target) == -1)
					        {
								if (CheckAttribute(rCharacter, "SeaAI.Task") && sti(rCharacter.SeaAI.Task) != AITASK_RUNAWAY)
								{
									//праздношатающийся кэп, проверяем атрибут анализа шипов. если атрибут есть и противник крут - валим.
									if (CheckAttribute(rCharacter, "AnalizeShips") && stf(rCharacter.ship.hp) < (stf(pchar.ship.hp) / 2))
							        {									
										iCharactersNum1 =  Group_GetLiveCharactersNum(rCharacter.SeaAI.Group.Name);
										iCharactersNum2 =  Group_GetLiveCharactersNum(characters[GetMainCharacterIndex()].SeaAI.Group.Name);	
										if ((iCharactersNum1 / iCharactersNum2) >= 2.2) 
										{
											Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex()));
										}
										else
										{
											Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
										}		
									}
									else
									{	//если есть шанс победить - атакуем
										Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
										{
											Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
										}
										else
										{
											Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
										}
									}
								}
								else
								{	//eddy. а то ранэвей у нас как залоченный таск
						        	if (CheckAttribute(rCharacter, "AnalizeShips") && (HPPercent > 60) && (SailsPercent > 70) && stf(rCharacter.ship.hp) > (stf(pchar.ship.hp) / 2))
							        {
							            Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
							        }
								}
					        }
				        }
			        }
		        }
		        else
		        {
					// --> Калеуче
					if (findsubstr(rCharacter.id, "Caleuche" , 0) != -1)
					{	
						if (rCharacter.id == "Caleuche_seacap") // у Доминики
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 500)
							{
								Ship_SetTaskAbordage(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
							}
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 150)
							{
								Caleuche_GhostshipBoarding(); // активизация квестового абордажа
							}
						}
						else // на карте
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 900)
							{
								Ship_SetTaskAbordage(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
								pchar.quest.Caleuche_map_clear.win_condition.l1 = "MapEnter";
								pchar.quest.Caleuche_map_clear.function = "Caleuche_ClearFromMap";
								rCharacter.lifeday = 0;
								Map_ReleaseQuestEncounter("Map_Caleuche");
							}
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 150)
							{
								Caleuche_MapGhostshipBoarding(); // активизация квестового абордажа
							}
						}
					}
					else
					{
						if (CheckAttribute(rCharacter, "PearlTartane") && sti(rCharacter.PearlTartane))
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 16)
							{
								PlaySound("interface\important_item.wav");
								int SmallPearlQty,BigPearlQty;
								if (CheckAttribute(rCharacter, "JewelryGulf")) // Addon 2016-1 Jason пиратская линейка
								{
									SmallPearlQty = rand(25) + 20;
									BigPearlQty = rand(20) + 15;
									TakeNItems(pchar, "jewelry8", SmallPearlQty);
									TakeNItems(pchar, "jewelry7", BigPearlQty);
									Log_SetStringToLog("Ловцы на баркасе " + rCharacter.ship.name + " отдали вам " + SmallPearlQty + " янтаря и " + BigPearlQty + " голубого янтаря.");
									pchar.questTemp.Mtraxx.JewQty = sti(pchar.questTemp.Mtraxx.JewQty)+BigPearlQty;
								}
								else
								{
									SmallPearlQty = rand(250) + 100;
									BigPearlQty = rand(150) + 50;
									TakeNItems(pchar, "jewelry53", SmallPearlQty);
									TakeNItems(pchar, "jewelry52", BigPearlQty);
									Log_SetStringToLog("Ловцы жемчуга на тартане " + rCharacter.ship.name + " отдали вам " + SmallPearlQty + " малых и " + BigPearlQty + " больших жемчужин.");
								}
								rCharacter.PearlTartane = false; //уже ограбили
								pchar.questTemp.GrabbingTartane = "success"; //флаг успешное нападение
							}
						}
						else
						{
						if (!CheckAttribute(rCharacter, "PearlTartane"))
						{
							Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
						}
							// Addon-2016-1 Jason, пиратская линейка
							if (rCharacter.id == "Losada_Seacap_1")
							{
								if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) > 3000 && CheckAttribute(pchar, "questTemp.Mtraxx.LosadaEscape")) Mtraxx_IgnasioOpenMap();		
							}
					}
		        }
	        }
	    }
	    }
	    else
	    {
	        // далее насильственное установление враждебности для определенных НПС
	        // boal 030804 узнал на днях, что можно это все делать оин раз и оно ПОМНИТ!!!  но тогда нужно ИД проверять, тк перекрываем выше
	        if (CheckAttribute(rCharacter, "AlwaysEnemy"))
	        {
	            SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
	            Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
	        }
	        else
	        {
                if (CheckAttribute(rCharacter, "AlwaysFriend"))
		        {
		            SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_FRIEND);
		        }
		        else
		        {
					// фикс отношений
			        if (sti(rCharacter.nation) != PIRATE || bBettaTestMode)//boal 030804 нужно чтоб при тесте флаг с пиратами мирил
			        {
	                    SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), GetNationRelation2MainCharacter(sti(rCharacter.nation)));
						// проверка на ложный флаг -->
						if (!CheckAttribute(rCharacter, "CheckFlagYet"))
						{
	                        if (!CheckAttribute(rCharacter, "CheckFlagDate") || GetNpcQuestPastDayParam(rCharacter, "CheckFlagDate") > 1)
	                        {
								if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER)
							    {
							        rCharacter.CheckFlagYet = true; // все, проверил
							        Ship_CheckFlagEnemy(rCharacter);
							        SaveCurrentNpcQuestDateParam(rCharacter, "CheckFlagDate");
							    }
						    }
						}
						// проверка на ложный флаг <--
						// Jason: корабли проверяют расстояние
						// --> Таможенный патруль
						if (rCharacter.id == "ContraCureerCap")
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 150)
							{
								SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
								SetCharacterRelationBoth(sti(GetCharacterIndex("ContraContraCap")), GetMainCharacterIndex(), RELATION_ENEMY);
								Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
								Group_LockTask(sGroupID);
								rCharacter.nation = PIRATE;
								ref rChar = characterFromId("ContraContraCap");	
								rChar.nation = PIRATE;
								Ship_FlagRefresh(rCharacter);
								Ship_FlagRefresh(rChar);
								UpdateRelations();
								RefreshBattleInterface();
							}
						}
						// --> Полакр Марлин
						if (rCharacter.id == "Cap_Marlin")
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 200)
							{
								SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
								Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
								Group_LockTask(sGroupID);
								UpdateRelations();
								RefreshBattleInterface();
							}
						}
						// --> фрегат Беспощадный
						if (rCharacter.id == "Saga_vampire")
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 200)
							{
								Saga_CheckVensanEnemyes(); // пытается распознать
							}
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 25)
							{
								if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Bomb")) Saga_HitSeaBomb();
							}
						}
						// --> Джекман, Центурион
						if (rCharacter.id == "Jackman")
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 200)
							{
								Saga_CheckJackmanFrigate(); // пытается распознать
							}
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 25)
							{
								if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Fugas")) Saga_HitSeaFugas();
							}
						}
						// --> Моллиган, Устрица
						if (rCharacter.id == "Molligan")
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 500 && CheckAttribute(pchar, "questTemp.Saga.Molligan.enemy")) Saga_MolliganAttack(); // атакует		
						}
						// --> Бейкер, лодка
						if (rCharacter.id == "Baker_Cap" && CheckAttribute(pchar, "questTemp.Saga.Shadows.Baker"))
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 20) Saga_BakerToCabin(); // принимаем на борт		
						}
						// --> люггер Диего 030712
						if (rCharacter.id == "GOT_camicadze")
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 200) GuardOT_CamicadzeBoom(); // атакует		
						}
						// --> // Addon-2016 Jason, французские миниквесты (ФМК) Мартиника
						if (rCharacter.id == "FMQM_Tartane_Cap")
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 500 && !CheckAttribute(rCharacter, "quest.seaattack")) FMQM_TartanaAlarm(); // 		
						}
			        }
			        else
			        {
			            SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);//на море пираты нападают всегда
			        }
		        }
	        }
	        // fix на нападение при условии, что нация дружеская, а с НПС мы все равно враждуем <--

	        if (GetRelation(GetMainCharacterIndex(), sti(rCharacter.index)) == RELATION_ENEMY)
	        {
	            Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
	            UpdateRelations(); // перенес от ниже, тк исходим из того, что изначально все друзья все равно
	        }
	        //UpdateRelations();  // to_do это тонкое место, это тормоз, но рефрешить нужно
	    }
	    // AI компа <--
    }
    /*else // наши компаньоны
    {
        // boal fix 23.05.05
    	if (rMyCharacter.SystemInfo.NoneOfEnimy == true)
    	{
            fMinEnemyDistance = 1000.0;
    	}
        rCharacter.SystemInfo.GlobalMinEnemyDistance    = fMinEnemyDistance;  
    } */
    // boal фикс выхода на карту
}

// проверка флага НПС у ГГ, мож он пират?
void Ship_CheckFlagEnemy(ref rCharacter)
{
	ref     mChar = GetMainCharacter();
	int     iCompan, iClass;
	float   fSneak;
	float   fPerkInfl = 1.0;
	int     i, cn;
	ref     chref;
	bool    bViewFlag = false;
	int     iNationToChange = sti(mChar.nation);  // было

	if (sti(rCharacter.nation) == PIRATE) return;
    iCompan = GetCompanionQuantity(mChar);
    iClass  = 6;
	// поиск мин.  те старшего класса
	for (i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(GetMainCharacter(), i);
		if (cn>=0)
		{
			chref = GetCharacter(cn);
            if (GetCharacterShipClass(chref) < iClass) iClass = GetCharacterShipClass(chref);
		}
	}
    if (GetNationRelation(GetBaseHeroNation(), sti(rCharacter.nation)) == RELATION_ENEMY && GetDaysContinueNationLicence(HOLLAND) == -1) // проверка грамот
    {
        // to_do ch.CheckLicence    = true; // Проверять наличие торговой лицензии при распознании,нужно фортам и сторожевикам
		iNationToChange = GetBaseHeroNation();
        bViewFlag       = true;
    }
    if (!bViewFlag)
    {
        if (ChangeCharacterHunterScore(mChar, NationShortName(sti(rCharacter.nation)) + "hunter", 0) > (8 + rand( (iClass-1)*(6-iCompan) ) ))
        {
            bViewFlag       = true;
            iNationToChange = PIRATE;
        }
    }
    if (bViewFlag)
    {  // смотрим флаг у ГГ и узнаем в нем...
		if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && pchar.location == "cuba1") return; // грамота отца Винсенто
		if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && pchar.location == "Trinidad") return; // грамота отца Винсенто

		fSneak  = stf(mChar.TmpSkill.Sneak); // 0.01..1.0
		int rep = sti(abs(REPUTATION_NEUTRAL - sti(mChar.reputation.nobility)) * 0.75);
		if(CheckCharacterPerk(mChar, "HT2")) fPerkInfl = 2.0;
		if ((rand(100) + rand(20) + rand(rep)) > (fPerkInfl*fSneak * 10 * iClass * (6-iCompan) * isEquippedArtefactUse(mChar, "indian_11", 1.0, 1.15)))
		{
			/*mChar.nation = iNationToChange;  // to_do ролик флага сделать
			Ship_FlagRefresh(PChar); //флаг на лету
	        SetNationToOfficers(iNationToChange);
	        SetNationRelation2MainCharacter(sti(rCharacter.nation), RELATION_ENEMY);
	        */
			pchar.MoorName = " ";	// LDH 12Feb17 - don't display MoorName in battle
                        Log_Info("Сойти за друга не удалось - "+ NationNamePeople(sti(rCharacter.nation)) + " распознали в нас врага.");
			SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
			DoQuestCheckDelay(NationShortName(iNationToChange) + "_flag_rise", 0.1); // применение нац отношений флага
			if (sti(pchar.questTemp.stels.sea) != GetDataDay())
			{
				AddCharacterExpToSkill(mChar, SKILL_SNEAK, 50);
				pchar.questTemp.stels.sea = GetDataDay();
			}
		}
		else
		{ // не узнал
			if (sti(pchar.questTemp.stels.sea) != GetDataDay())
			{
				AddCharacterExpToSkill(mChar, SKILL_SNEAK, (iCompan * 200 / iClass));
				ChangeCrewExp(mChar, "Sailors", 0.5);
				pchar.questTemp.stels.sea = GetDataDay();
			}
		}
	}
	if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MIRAGE && sti(rCharacter.nation) == ENGLAND && CheckAttribute(pchar, "questTemp.HWIC.Holl"))//Мираж для англичан враг
	{
		Log_Info("Англичане узнали 'Мираж' и приняли нас за врага!");
		SetNationRelation2MainCharacter(ENGLAND, RELATION_ENEMY);
		LAi_group_ClearAllTargets();
		DoQuestCheckDelay("NationUpdate", 3.0);
		UpdateRelations();
	    RefreshBattleInterface();
	}
	if (LineShips_CheckAndIdentify(sti(rCharacter.nation))) // если пришел на линейнике этой нации
	{
		Log_Info("Тревога, "+ NationNamePeople(sti(rCharacter.nation)) + " узнали свой линейный корабль, который вы у них захватили!");
		SetNationRelation2MainCharacter(sti(rCharacter.nation), RELATION_ENEMY);
		LAi_group_ClearAllTargets();
		DoQuestCheckDelay("NationUpdate", 3.0);
		UpdateRelations();
	    RefreshBattleInterface();
		ChangeCharacterNationReputation(pchar, sti(rCharacter.nation), -3);
	}
}

void Ship_ActivateFirePlace()
{
	aref	arShipObject = GetEventData();
	aref	arCharacter = GetEventData();
	int		iFirePlaceIndex = GetEventData();
	string	sSoundName = GetEventData();
	float	fFireTime = GetEventData();
	int		iBallCharacterIndex = GetEventData();

	if (!bAbordageStarted) // fix
	{
		if(rand(5) < 4) 	SendMessage(arShipObject, "llsssfl", MSG_SHIP_ACTIVATE_FIRE_PLACE, iFirePlaceIndex, "ship_smoke", "ship_fire", sSoundName, fFireTime, iBallCharacterIndex);
		else				SendMessage(arShipObject, "llsssfl", MSG_SHIP_ACTIVATE_FIRE_PLACE, iFirePlaceIndex, "sea_smoke", "ship_fire", sSoundName, fFireTime, iBallCharacterIndex);
	}
}

void Ship_BranderDetonate()
{
	ref		rCharacter = GetCharacter(GetEventData());

	ref		rBranderBaseShip = GetRealShip(sti(rCharacter.Ship.Type));
 	float	fBranderDistance = 1.9 * (45.0 + (6.0 - stf(rBranderBaseShip.Class)) * 15.0); //fix
	float   fMaxDamage = 1000.0 + MakeFloat(GetCargoGoods(rCharacter, GOOD_POWDER)) * 4;

	aref	arShipObjects[64];
	int		iBranderNumShips = 1;
	
	if(CheckAttribute(rCharacter,"Situation") && rCharacter.situation == "Explosion" ) // ситуация со взрывом
	{
		fMaxDamage = 1000.0 + MakeFloat(GetCargoGoods(rCharacter, GOOD_POWDER)) * 3;
		if(GetCargoGoods(rCharacter, GOOD_POWDER) < 300) { fMaxDamage += 400.0; }	
		ref mc = GetMainCharacter();
		int iDiffClass = sti(RealShips[sti(mc.Ship.Type)].Class) - sti(RealShips[sti(rCharacter.Ship.Type)].Class);
		if(iDiffClass > 0) fMaxDamage += iDiffClass * 500.0;
		fMaxDamage = fMaxDamage / 20.0 * MOD_SKILL_ENEMY_RATE;		
	}	
	if (!FindClass(&arShipObjects[0], "ship")) { return; }// can't be
	while (FindClassNext(&arShipObjects[iBranderNumShips])) { iBranderNumShips++; }
	
	// enumerate ship and do damage
	for (int i=0; i<iBranderNumShips; i++)
	{
		int iCharacterIndex = -1;
		SendMessage(arShipObjects[i], "le", MSG_SHIP_GET_CHARACTER_INDEX, &iCharacterIndex);
		if (iCharacterIndex == sti(rCharacter.index)) { continue; }
		ref rOtherCharacter = GetCharacter(iCharacterIndex);
		ref	rOtherBaseShip = GetRealShip(sti(rOtherCharacter.Ship.Type));
		float fDistance = Ship_GetDistance2D(rCharacter, rOtherCharacter);
		if (fDistance > fBranderDistance) { continue; }
		float fDamageMultiply = Bring2Range(1.0, 0.0, 10.0, fBranderDistance, fDistance);
		Ship_ApplyHullHitpoints(rOtherCharacter, fMaxDamage * fDamageMultiply, KILL_BY_SPY, sti(rCharacter.index));
		// fire random fire places
		//int iNumFirePlaces = 0;
		//SendMessage(&arShipObjects[i], "le", MSG_SHIP_GET_NUM_FIRE_PLACES, &iNumFirePlaces);

		// add move impulse to ship
		float x = stf(rOtherCharacter.Ship.Pos.x) - stf(rCharacter.Ship.Pos.x);
		float z = stf(rOtherCharacter.Ship.Pos.z) - stf(rCharacter.Ship.Pos.z);
		float fLen = stf(rOtherBaseShip.Class) * fDamageMultiply * (1.0 / sqrt(x * x + z * z));
		SendMessage(&arShipObjects[i], "llffffff", MSG_SHIP_ADD_MOVE_IMPULSE, false, x * fLen, 0.0, z * fLen, 0.0, 0.0, 0.0);
	}
	Ship_Detonate(rCharacter, true, true);
}

float Ship_GetDistance2D(ref rCharacter1, ref rCharacter2)
{
	if (CheckAttribute(rCharacter1, "Ship.Pos.x") && CheckAttribute(rCharacter2, "Ship.Pos.x")) // fix boal
	{
		return GetDistance2D(stf(rCharacter1.Ship.Pos.x), stf(rCharacter1.Ship.Pos.z), stf(rCharacter2.Ship.Pos.x), stf(rCharacter2.Ship.Pos.z));
	}   
	else
	{
		return 1000.0;
	}
}

int Ship_FindOtherBallType(ref rCharacter, float fMinEnemyDistance, bool bBalls, bool bBombs, bool bGrapes, bool bKnippels)
{
	ref	rCannon = GetCannonByType(sti(rCharacter.Ship.Cannons.Type));
	float range = stf(rCannon.FireRange);
	if (checkAttribute(rCharacter, "SeaAI.task.target") && rCharacter.SeaAI.task.target != "") //fix
	{
		int enemy = sti(rCharacter.SeaAI.task.target);
		ref rBaseShip = GetRealShip(GetCharacterShipType(rCharacter));
		
		rCannon = GetCannonByType(sti(characters[enemy].Ship.Cannons.Type));
		float TargetRange = stf(rCannon.FireRange);

		int iType = -1;
		float fRangeModifier = 1.0;
		// оптимизация float fDistance = Ship_GetDistance2D(rCharacter, &characters[enemy]);

		/*if (sti(rCharacter.SeaAI.Task) == AITASK_RUNAWAY)
		{
			Ship_SetSailState(sti(rCharacter.index), 1);
			if (sti(characters[enemy].ship.sp) > 20 && ShipSailState(enemy) < 2)
			{
				if(fMinEnemyDistance <= (range * 0.9) && bKnippels)
				{
					iType = GOOD_KNIPPELS;
				}
				if(fMinEnemyDistance <= (range * 0.4) && bGrapes)
				{
					iType = GOOD_GRAPES;
				}
			}
		}*/

		if ( bBalls) //(fMinEnemyDistance <= range) && //если дистанция больше, то тем более на ядра
		{
			iType = GOOD_BALLS;
		}

		if ( (fMinEnemyDistance <= (range * 0.8)) && bKnippels) 
		{
			if (sti(characters[enemy].ship.sp) > 30 && ShipSailState(enemy) >= 0.5)  // супер баг акелловцев  ShipSailState - 0 нет паруса 1 боевой 2 - полный
			{
				iType = GOOD_KNIPPELS;
			}
			fRangeModifier = 0.8;
		}

		if ( (fMinEnemyDistance <= (range * 0.5)) && bBombs)
		{
			iType = GOOD_BOMBS;
			fRangeModifier = 0.6;
		}

		if ((fMinEnemyDistance <= (range * 0.2)) && bGrapes)
		{
			if (sti(characters[enemy].ship.crew.quantity) > sti(rBaseShip.MinCrew))
			{
				iType = GOOD_GRAPES;  
			}
			fRangeModifier = 0.3;
		}

		rCharacter.Ship.SeaAI.Init.AttackDistance = range * fRangeModifier / (1.4 + frandSmall(3.0));

		/*if (range > fDistance)
		{
			rCharacter.Ship.SeaAI.Init.AttackDistance = range;
		} */

		return iType;
	}
	
	if (bBalls) return GOOD_BALLS;
	if (bBombs) return GOOD_BOMBS;
	if (bKnippels) return GOOD_KNIPPELS;
	if (bGrapes) return GOOD_GRAPES;
	
	return -1;
}

// event: indicate that ball is not enough for fire for main character
void Ship_NotEnoughBalls()
{
	bNotEnoughBalls = GetEventData();
	// boal -->
	if (!bNotEnoughBalls)
	{
	    if (GetCargoGoods(pchar, GOOD_POWDER) < 1)
	    {
	        bNotEnoughBalls = true;
	    }
	}
	// boal <--

}

int Ship_GetCurrentBallsNum()
{
	aref aCharacter = GetEventData();
	return GetCargoGoods(aCharacter,sti(aCharacter.Ship.Cannons.Charge.Type));
}

void Ship_SailDamage()
{
	float x, y, z;
	int iCharacterIndex 	= GetEventData();
	int	iBallCharacterIndex = GetEventData();
	x = GetEventData();
	y = GetEventData();
	z = GetEventData();

	ref	rBallCharacter 	= GetCharacter(iBallCharacterIndex);	// кто пуляет
	ref	rOurCharacter 	= GetCharacter(iCharacterIndex);   		// по кому
	
//	Log_Info(" Ship_SailDamage : rOurCharacter.id = " + rOurCharacter.id + " rBallCharacter.id = " + rBallCharacter.id);
	
	rOurCharacter.Ship.LastBallCharacter = iBallCharacterIndex;
	
	string sSound;
	int	iBallType = sti(AIBalls.CurrentBallType);
	switch (iBallType)
	{
		case GOOD_BALLS:	sSound = "ball2sail";		break;
		case GOOD_GRAPES:	sSound = "grapes2sail";		break;
		case GOOD_KNIPPELS:	sSound = "knippel2sail";	break;
		case GOOD_BOMBS:	sSound = "ball2sail"; 		break;
	}

	Play3DSound(sSound, x, y, z);
	if (rand(100) < 15) { Play3DSound("fly_ball_misc", x, y, z); }
	
	bool    isOurCompanion   = IsCompanion(rOurCharacter);
	
	if (sti(rOurCharacter.Ship.LastBallCharacter) == GetMainCharacterIndex() 
	        && GetNationRelation2MainCharacter(sti(rOurCharacter.nation)) != RELATION_ENEMY)
    {	
        if (!IsCompanion(rOurCharacter) && !CheckAttribute(rOurCharacter, "Coastal_Captain")) // по своим можно палить таможня пофиг
        {
            Ship_NationAgressive(rOurCharacter, rOurCharacter);
            DoQuestCheckDelay("NationUpdate", 0.7);
        }	
    }	
}

void Ship_Ship2IslandCollision()
{
	float	fPower, fSlide, x, y, z;
	int		iOurCharacterIndex, iEnemyCharacterIndex, iTouchPoint;

	iOurCharacterIndex = GetEventData();
	iEnemyCharacterIndex = GetEventData();
	fPower = abs(GetEventData());
	fSlide = abs(GetEventData());
	iTouchPoint = GetEventData();
	x = GetEventData();
	y = GetEventData();
	z = GetEventData();

	ref rOurCharacter = GetCharacter(iOurCharacterIndex);

    if (!CheckAttribute(rOurCharacter, "AlwaysSandbankManeuver"))  //boal
    {
		float fHP = (1.0 - fSlide) * fPower * 3.0;
		Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_ISLAND, -1);

		if (fPower > 1.0) { Play3DSound("coll_ship2rock", x, y, z); }
	}
}

float Ship_GetAttackHP(int iCharacterIndex, float fDistance)
{
	float fAttackHP = 0.0;
	if (bSeaActive)
	{
		SendMessage(&AISea, "lafe", AI_MESSAGE_SHIP_GET_ATTACK_HP, &Characters[iCharacterIndex], fDistance, &fAttackHP);
	}
	return fAttackHP;
}

float Ship_GetHP(ref rCharacter) 
{ 
	return stf(rCharacter.Ship.HP); 
}

void Ship_Ship2ShipCollision()
{
	int		iOurCharacterIndex, iEnemyCharacterIndex, iTouchPoint;
	float	fPower, fSlide, x, y, z;
	
	iOurCharacterIndex = GetEventData();   // кого
	iEnemyCharacterIndex = GetEventData();  // кто
	fPower = abs(GetEventData());
	fSlide = abs(GetEventData());
	iTouchPoint = GetEventData();
	x = GetEventData();
	y = GetEventData();
	z = GetEventData();
	
	ref rOurCharacter = GetCharacter(iOurCharacterIndex);

	float fHP = (1.0 - fSlide) * fPower * 10.0;
	//Trace("Ship->Ship touch: idx = " + iOurCharacterIndex + ", fpower = " + fPower + ", fHP = " + fHP + ", fSlide = " + fSlide);
	Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_TOUCH, iEnemyCharacterIndex);
	// зашита от потопления тараном -->
	if (iEnemyCharacterIndex == GetMainCharacterIndex() && GetHullPercent(rOurCharacter) <= 14  && !LAi_IsDead(rOurCharacter))
	{
		if (!IsCompanion(rOurCharacter) && GetRelation(sti(rOurCharacter.index), GetMainCharacterIndex()) != RELATION_ENEMY)
		{
			Ship_NationAgressive(rOurCharacter, rOurCharacter);
	    	DoQuestCheckDelay("NationUpdate", 0.9);
    	}
	}
	// зашита от потопления тараном <--

	if (fPower>1.0) { Play3DSound("coll_ship2ship", x, y, z); }
}

void Ship_ApplyCrewHitpoints(ref rOurCharacter, float fCrewHP)
{         // че-то распук метод "неподецки" - переделал 29.07.06 boal
	if (LAi_IsImmortal(rOurCharacter)) 
	{ 
		return; 
	}

	ref rBaseShip = GetRealShip(GetCharacterShipType(rOurCharacter));
	float fMultiply = 1.0 - (0.75 * stf(rOurCharacter.TmpSkill.Defence)); // было 0.05 - что полная хрень, тк скил 0..1

	if(CheckOfficersPerk(rOurCharacter, "Doctor2"))
	{
		fMultiply = fMultiply * 0.8;
	}
	else
	{
		if(CheckOfficersPerk(rOurCharacter, "Doctor1"))
		{
			fMultiply = fMultiply * 0.9;
		}
	}
	
	fMultiply = fMultiply * isEquippedArtefactUse(rOurCharacter, "amulet_10", 1.0, 0.95 ); //belamour isEquippedAmuletUse не работает на офицерах, только на ГГ
	float fDamage = fCrewHP * fMultiply; 

	float fNewCrewQuantity = stf(rOurCharacter.Ship.Crew.Quantity) - fDamage;
	float f5Percent = stf(rBaseShip.MinCrew) * 0.25; // boal fix неубиваемые 25% команды- было 0.05;
	// boal  check skill -->
	if (fNewCrewQuantity >= f5Percent && IsCompanion(rOurCharacter))
	{
       AddCharacterExpToSkill(rOurCharacter, "Defence", makefloat(fCrewHP / 2 + 0.5));
       ChangeCrewExp(rOurCharacter, "Soldiers",  (fCrewHP / stf(rBaseShip.OptCrew))); // to_do может быть много
    }
    // boal <--
	
	if (fNewCrewQuantity < f5Percent) { fNewCrewQuantity = f5Percent; }
	if (fNewCrewQuantity < 0.0) { fNewCrewQuantity = 0.0; }
	
	if (sti(rOurCharacter.index) == GetMainCharacterIndex() && stf(rBaseShip.MinCrew) > fNewCrewQuantity && stf(rBaseShip.MinCrew) <= stf(rOurCharacter.Ship.Crew.Quantity))
    {  // переход на мин команду
        PlaySound("OBJECTS\SHIPCHARGE\_Damage1.wav");
    }
	// boal fix утопленников   -->
	if (stf(rOurCharacter.Ship.Crew.Quantity) > fNewCrewQuantity)
	{   // на случай косяков со знаком fCrewHP
		if (sti(rOurCharacter.index) == GetMainCharacterIndex() || IsCompanion(rOurCharacter))
		{
			Statistic_AddValue(GetMainCharacter(), "Sailors_dead", stf(rOurCharacter.Ship.Crew.Quantity) - fNewCrewQuantity);
			Achievment_SetStat(GetMainCharacter(), 21, makeint(sti(rOurCharacter.Ship.Crew.Quantity) - fNewCrewQuantity));
		}
		rOurCharacter.Ship.Crew.Quantity = fNewCrewQuantity;
	}
	if (stf(rOurCharacter.Ship.Crew.Quantity) < 0.0) { rOurCharacter.Ship.Crew.Quantity = 0.0; }
	// boal fix утопленников   <--
}

void Ship_ApplyHullHitpoints(ref rOurCharacter, float fHP, int iKillStatus, int iKillerCharacterIndex)
{
   	if (LAi_IsImmortal(rOurCharacter)) { return; }

	float fCurHP;
	float fMinus 	= 0.0;
	float fPlus 	= 0.0;
	float fPercent	= 0.0;
	
    if (bSeaReloadStarted) { return; }
	if (fHP <= 0.0) { return; }
	if (LAi_IsDead(rOurCharacter) || !CheckAttribute(rOurCharacter, "Ship.HP")) { return; }   // fix
	
    if (iKillerCharacterIndex >= 0)
	{
		if (sti(Characters[iKillerCharacterIndex].TmpPerks.HullDamageUp)) 		fPlus = 0.15;
		if (sti(Characters[iKillerCharacterIndex].TmpPerks.CannonProfessional)) fPlus = 0.3;
		
		if(IsCharacterEquippedArtefact(&Characters[iKillerCharacterIndex], "indian_8")) fPlus += 0.05; // belamour произведение дает 0 без перков
	}

	if (sti(rOurCharacter.TmpPerks.BasicBattleState))			fMinus = 0.15;
	if (sti(rOurCharacter.TmpPerks.AdvancedBattleState))		fMinus = 0.25;
	if (sti(rOurCharacter.TmpPerks.ShipDefenseProfessional))	fMinus = 0.35;
	
	if(IsCharacterEquippedArtefact(rOurCharacter, "amulet_8")) fMinus += 0.05; // belamour произведение дает 0 без перков
	
	if (CheckAttribute(rOurCharacter, "SeaBoss")) fMinus = fPlus + stf(rOurCharacter.SeaBoss); // Addon 2016-1 Jason Пиратская линейка

	fCurHP = stf(rOurCharacter.Ship.HP) - fHP * (1.0 + fPlus - fMinus);
	
	if (CheckAttribute(rOurCharacter, "ShipHideImmortal")) // Addon 2016-1 Jason Пиратская линейка
	{
		if (fCurHP <= sti(rOurCharacter.ShipHideImmortal)) LAi_SetImmortal(rOurCharacter, true);
	}
	if (fCurHP <= 0.0)
	{
	if (CheckAttribute(rOurCharacter, "ShipHideImmortal"))
	{
			fCurHP = 200.0;
			LAi_SetImmortal(rOurCharacter, true);
		}
		else
	{
		fCurHP = 0.0;
		ShipDead(sti(rOurCharacter.index), iKillStatus, iKillerCharacterIndex);
	}
	}
	
    if(fCurHP > sti(RealShips[sti(rOurCharacter.ship.type)].HP))
	{
		fCurHP = RealShips[sti(rOurCharacter.ship.type)].HP;
	}
	rOurCharacter.Ship.HP = fCurHP;
	
	// расчет пенальти в корпус для последующего учета при ремонте
	if(CheckAttribute(RealShips[sti(rOurCharacter.ship.type)],"QuestShip")) fPercent = 1.0;
	else fPercent = 1.0 + (makefloat(MOD_SKILL_ENEMY_RATE)/4.0);
	
	rOurCharacter.Ship.HP_penalty = makefloat(sti(RealShips[sti(rOurCharacter.ship.type)].HP) * fPercent/100.0 * (100.0 - GetHullPercent(rOurCharacter))/100.0);
	
	//trace("Character : " + rOurCharacter.id + " percent :" + fPercent + " hp_penalty : " + rOurCharacter.Ship.HP_penalty);
}


void Ship_AddCharacterExp(ref rCharacter, int iExpQuantity)
{
	if(IsCompanion(rCharacter) == true || rCharacter.id == pchar.id)
	{
		AddPartyExp(pchar, iExpQuantity);
	}
	
	if (sti(rCharacter.index) == nMainCharacterIndex)
	{
		fSeaExp = fSeaExp + iExpQuantity;
	}
}


void ShipDead(int iDeadCharacterIndex, int iKillStatus, int iKillerCharacterIndex)
{
	ref rDead, rKillerCharacter, rBaseShip, rKillerBaseShip, sld;

	rDead = GetCharacter(iDeadCharacterIndex);
	if (!CheckAttribute(rDead, "Ship.Type")) // fix
    {
        if (MOD_BETTATESTMODE == "On") Log_Info("Error: ShipDead Нет корабля у iDeadCharacterIndex = "+iDeadCharacterIndex);
        return;
    }
    bool bDeadCompanion = IsCompanion(rDead);
	rBaseShip = GetRealShip(sti(rDead.Ship.Type));

	if (iKillerCharacterIndex != -1)
	{
		rKillerCharacter = GetCharacter(iKillerCharacterIndex);
		rKillerBaseShip = GetRealShip(sti(rKillerCharacter.Ship.Type));
		// boal  check skill -->
		if (!bDeadCompanion && iKillStatus != KILL_BY_SPY)
        {
			switch (iKillStatus)
		    {
			    case KILL_BY_TOUCH:
	                AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 90);
	                ChangeCrewExp(rKillerCharacter, "Sailors", 1);
	                // boal statistic info 17.12.2003 -->
	                Statistic_AddValue(rKillerCharacter, "KillShip_" + rBaseShip.Class, 1);
					Achievment_SetStat(rKillerCharacter, 3, 1);
					if(sti(rKillerCharacter.nation) == PIRATE) Achievment_SetStat(rKillerCharacter, 50, 1);
	                // boal statistic info 17.12.2003 <--
			    break;
			    case KILL_BY_BALL:
			        AddCharacterExpToSkill(rKillerCharacter, "Accuracy", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 35);
			        AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 65);
			        AddCharacterExpToSkill(rKillerCharacter, "Cannons", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 40);
			        ChangeCrewExp(rKillerCharacter, "Sailors", 1);
			        ChangeCrewExp(rKillerCharacter, "Cannoners", 2);
			        // boal statistic info 17.12.2003 -->
	                Statistic_AddValue(rKillerCharacter, "KillShip_" + rBaseShip.Class, 1);
					Achievment_SetStat(rKillerCharacter, 3, 1);
					if(sti(rKillerCharacter.nation) == PIRATE) Achievment_SetStat(rKillerCharacter, 50, 1);
	                // boal statistic info 17.12.2003 <--
	                //homo 25/06/07 только враг и 1/4
        			if (rand(4) == 2 && GetRelation(sti(rDead.Index), sti(Pchar.Index))== RELATION_ENEMY)
                    {
                        //обычный
                        if(!CheckAttribute(rDead, "DontRansackCaptain") || rDead.DontRansackCaptain == false) AISeaGoods_AddGood(rDead, "enemy_boat", "lo_boat", 1000.0, 1); //homo 25/06/07 спасается на шлюпке
                    }
                    //homo
			    break;
			    case KILL_BY_ABORDAGE:
			        AddCharacterExpToSkill(rKillerCharacter, "Grappling", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 110);
			        AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 70);
			        AddCharacterExpToSkill(rKillerCharacter, SKILL_FORTUNE, stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 10);
			        AddCharacterExpToSkill(rKillerCharacter, "Defence", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 60);
			        ChangeCrewExp(rKillerCharacter, "Sailors", 0.5);
					// в лаи_бординг ChangeCrewExp(rKillerCharacter, "Soldiers", 4);
			        // boal statistic info 17.12.2003 -->
	                Statistic_AddValue(rKillerCharacter, "KillAbordShip_" + rBaseShip.Class, 1);
	                // boal statistic info 17.12.2003 <--
			    break;
		    }
			if (iKillStatus != KILL_BY_SELF)
			{
		        AddCharacterExpToSkill(rKillerCharacter, SKILL_FORTUNE, stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 20);
		        AddCharacterExpToSkill(rKillerCharacter, "Leadership", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 25);

	            // статистка по нации
		    	Statistic_AddValue(rKillerCharacter, NationShortName(sti(rDead.nation))+"_KillShip", 1);
		    	if (rand(8) < 3 && sti(rDead.nation) != PIRATE)  // 30% повышаем награду
		    	{
					ChangeCharacterHunterScore(rKillerCharacter, NationShortName(sti(rDead.nation)) + "hunter", 1+rand(1));
				}
			}
        }
        // boal 04.04.04 <--
	}

	//int iQuantity = GetCompanionQuantity(pchar);
	
	float fX = stf(rDead.Ship.Pos.x);
	float fY = stf(rDead.Ship.Pos.y);
	float fZ = stf(rDead.Ship.Pos.z);

	rDead.Ship.HP = 0;
	rDead.Killer.Status = iKillStatus;
	rDead.Killer.Index = iKillerCharacterIndex;
		
	LAi_SetCurHP(rDead, 0.0);
		
	int iExp = 0;
	if (iKillerCharacterIndex != -1) 
	{ 
		iExp = 2 * MakeInt(stf(rBaseShip.HP) * stf(rKillerBaseShip.Class) / stf(rBaseShip.Class)); 
	}

	bool bCompanion = false;
	if (iKillerCharacterIndex != -1) 
	{ 
		bCompanion = IsCompanion(rKillerCharacter); 
	}

 	if (bCompanion && bDeadCompanion)
	{
		iExp = 0;
		// boal -->
		if (iKillerCharacterIndex == GetMainCharacterIndex())
		{
			ChangeCharacterComplexReputation(pchar,"nobility", -15);
		}
		// boal <--
	}      
    
	bool bRealKill = false;
	switch (iKillStatus)
	{
		case KILL_BY_TOUCH:
			if (iKillerCharacterIndex != -1) { bRealKill = true; }
		break;
		case KILL_BY_BALL:
			bRealKill = true;
		break;
		case KILL_BY_ABORDAGE:
			bRealKill = true;
		break;
	}

	// Ship sunk log
	if (iDeadCharacterIndex != nMainCharacterIndex)
	{
		string sSunkString;
		string sSunkShipType = XI_ConvertString(rBaseShip.BaseName);
		string sKillShipType = "";
		string sKillShipName = "";
		if (iKillerCharacterIndex != -1)
		{
		    sKillShipType = XI_ConvertString(rKillerBaseShip.BaseName);
		    sKillShipName = "" + rKillerCharacter.Ship.Name;
		}
		if (bCompanion && !bDeadCompanion && bRealKill)
		{
            sSunkString = sSunkShipType + " '" + rDead.Ship.Name + "' " + GetShipSexWord(rBaseShip.BaseName, "был потоплен ", "была потоплена ") + GetFullName(rKillerCharacter);
        }
        else
        {
            if (sKillShipName == "")
            {
            	sSunkString = sSunkShipType + " '" + rDead.Ship.Name + "' " + GetShipSexWord(rBaseShip.BaseName, "был потоплен.", "была потоплена.");
            }
            else
            {
				sSunkString = sSunkShipType + " '" + rDead.Ship.Name + "' " +GetShipSexWord(rBaseShip.BaseName, "был потоплен ", "была потоплена ") + sKillShipType + " '" + sKillShipName + "'";
			}
        }
		Log_SetStringToLog(sSunkString);
	}

 	if (rand(10) >= 6) // глупое условие... это все классы :)  && sti(rBaseShip.Class) <= 6)
	{ 
		bool bDetonate = false;
		switch (iKillStatus)
		{
			case KILL_BY_BALL:	
				bDetonate = true; 
			break;
			/*case KILL_BY_SPY:	
				bDetonate = true; 
			break;  */ // идет вылет, если второй раз рекурсию Ship_Detonate делать
		}
		if (bDetonate) 
		{ 
			Ship_Detonate(rDead, true, false); 
		}
	}

	// set attributes for sinking effect
	rDead.Ship.Sink = "";
	aref aSink; makearef(aSink, rDead.Ship.Sink);
	
/*	
	aSink.Speed.y = 0.35;	// speed of sink y
	aSink.Speed.x = 0.017 * (frnd() * 2.0 - 1.0);	// speed sink angle rotate around x
	aSink.Speed.z = 0.017 * (frnd() * 2.0 - 1.0);	// speed sink angle rotate around z
*/
	// корабль тонет  - немного добавим драматизьму :-)
	aSink.Speed.y = 0.25 + (frnd() * 0.05);	// speed of sink y
	aSink.Speed.x = 0.021 * (frnd() * 2.0 - 1.0);	// speed sink angle rotate around x
	aSink.Speed.z = 0.04 * (frnd() * 2.0 - 1.0);	// speed sink angle rotate around z
	
	if (iDeadCharacterIndex == nMainCharacterIndex)
	{ 
		SeaCameras_SetDieCamera();
		FadeOutMusic(2);
		//PlayStereoOGG("music_ship_dead");
		// убил ЛГ
		if (iKillerCharacterIndex != -1 && rKillerCharacter.id == "GhostCapt")
		{
		    DoQuestCheckDelay("Survive_In_Sea", 9.0);
		}
		else
		{
			InterfaceStates.Buttons.Save.enable = false;
			PostEvent(GAME_OVER_EVENT, 15000);
		}
	}
    // спасем офицеров boal 07/02/05
	else
	{
        if (bDeadCompanion && CheckOfficersPerk(rDead, "ShipEscape") && GetRemovable(rDead)) // выживаем
        {
            //homo 22/06/07
            AISeaGoods_AddGood(rDead, "boat", "lo_boat", 1000.0, 1);
            RemoveCharacterCompanion(pchar, rDead);
            Log_Info(GetFullName(rDead) + " спасся на шлюпке.");
        }
	}
	// спасем офицеров boal 07/02/05
	Play3DSound("ship_sink", fX, fY, fZ);

	// Message to AI
	SendMessage(&AISea, "la", AI_MESSAGE_CHARACTER_DEAD, rDead);

	// Event
	Event(SHIP_DEAD, "l", iDeadCharacterIndex);
}

// boal -->
void ShipTaken(int iDeadCharacterIndex, int iKillStatus, int iKillerCharacterIndex)
{
	ref rDead, rKillerCharacter, rMainCharacter, rBaseShip, rKillerBaseShip;

	rDead = GetCharacter(iDeadCharacterIndex);
	rDead.Killer.Index = iKillerCharacterIndex;
	rBaseShip = GetRealShip(sti(rDead.Ship.Type));
	rMainCharacter = GetMainCharacter();

	bool bCompanion = false;
	bool bDeadCompanion = IsCompanion(rDead);

    LAi_SetCurHP(rDead, 0.0); // умер
	rDead.Killer.Status = iKillStatus;
	rDead.Killer.Index = iKillerCharacterIndex;
    if (iKillerCharacterIndex != -1 && !bDeadCompanion)
	{
		rKillerCharacter = GetCharacter(iKillerCharacterIndex);
		rKillerBaseShip = GetRealShip(sti(rKillerCharacter.Ship.Type));
		bCompanion = IsCompanion(rKillerCharacter);
		// boal  check skill -->
        AddCharacterExpToSkill(rKillerCharacter, SKILL_FORTUNE, stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 20);
        AddCharacterExpToSkill(rKillerCharacter, "Leadership", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 25);
        AddCharacterExpToSkill(rKillerCharacter, "Grappling", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 120);
		AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 70);
		AddCharacterExpToSkill(rKillerCharacter, "Commerce", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 30);
		AddCharacterExpToSkill(rKillerCharacter, "Repair", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 60);
		AddCharacterExpToSkill(rKillerCharacter, "Defence", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 60);
        // boal <--
        // boal statistic info 17.12.2003 -->
        Statistic_AddValue(rKillerCharacter, "AbordShip_" + rBaseShip.Class, 1);
        Statistic_AddValue(rKillerCharacter, NationShortName(sti(rDead.nation))+"_AbordShip", 1);
		Achievment_SetStat(rKillerCharacter, 2, 1);
        // boal statistic info 17.12.2003 <--
        
        ChangeCrewExp(rKillerCharacter, "Sailors", 0.5);
		// в лаи_бординг ChangeCrewExp(rKillerCharacter, "Soldiers", 5); // to_do перенести на форму захвата
	}
	if (iDeadCharacterIndex != GetMainCharacterIndex())
	{
		string sSunkShipType = XI_ConvertString(rBaseShip.BaseName);
		string sKillShipType = XI_ConvertString(rKillerBaseShip.BaseName);

		if(bCompanion && !bDeadCompanion)
		{
            Log_SetStringToLog(sSunkShipType + " '" + rDead.Ship.Name + "' " + "был захвачен!");
        }
	}
    if (rand(8) < 3 && !bDeadCompanion && sti(rDead.nation) != PIRATE)  // 30% повышаем награду
    {
        ChangeCharacterHunterScore(rKillerCharacter, NationShortName(sti(rDead.nation)) + "hunter", 1+rand(1));
    }
}
// захваченный корабль, отпущен
void ShipTakenFree(int iDeadCharacterIndex, int iKillStatus, int iKillerCharacterIndex)
{
	ref rDead, rKillerCharacter, rMainCharacter, rBaseShip, rKillerBaseShip;

	rDead = GetCharacter(iDeadCharacterIndex);
	rDead.Killer.Index = iKillerCharacterIndex;
	rBaseShip = GetRealShip(sti(rDead.Ship.Type));
	rMainCharacter = GetMainCharacter();

    LAi_SetCurHP(rDead, 0.0); // умер
	rDead.Killer.Status = iKillStatus;
	rDead.Killer.Index = iKillerCharacterIndex;
    if (iKillerCharacterIndex != -1)
	{
		rKillerCharacter = GetCharacter(iKillerCharacterIndex);
		rKillerBaseShip = GetRealShip(sti(rKillerCharacter.Ship.Type));
		
        AddCharacterExpToSkill(rKillerCharacter, "Leadership", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 50);
        AddCharacterExpToSkill(rKillerCharacter, "Grappling", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 120);
		AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 80);
		AddCharacterExpToSkill(rKillerCharacter, SKILL_FORTUNE, stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 70);
		AddCharacterExpToSkill(rKillerCharacter, "Repair", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 10);
		AddCharacterExpToSkill(rKillerCharacter, "Defence", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 10);
        
		Statistic_AddValue(rKillerCharacter, "AbordShipFree_" + rBaseShip.Class, 1);  // эту статистику пока нигде не видно to_do
        Statistic_AddValue(rKillerCharacter, NationShortName(sti(rDead.nation))+"_AbordShipFree", 1);
        Statistic_AddValue(rKillerCharacter, "AbordShipFree", 1); // отпущено
        
        ChangeCrewExp(rKillerCharacter, "Sailors", 0.5);
		// в лаи_бординг ChangeCrewExp(rKillerCharacter, "Soldiers", 5); // to_do перенести на форму захвата
		if(!CheckAttribute(rDead,"Situation"))
		{
			ChangeCharacterComplexReputation(rKillerCharacter,"nobility", 2); 
			ChangeCharacterComplexReputation(rKillerCharacter,"authority", -2); 
			ChangeCharacterComplexReputation(rKillerCharacter,"fame", 1); 
			OfficersReaction("good");
		}	
	}
	if (iDeadCharacterIndex != GetMainCharacterIndex() && !CheckAttribute(rDead,"Situation"))
	{
		string sSunkShipType = XI_ConvertString(rBaseShip.BaseName);
		string sKillShipType = XI_ConvertString(rKillerBaseShip.BaseName);

        Log_SetStringToLog(sSunkShipType + " '" + rDead.Ship.Name + "' " + "был захвачен, но отпущен после грабежа.");
		if (CheckAttribute(pchar, "GenQuest.Detonation"))
		{
			DoQuestCheckDelay("CanNotEnterToMap", 0.2); // patch-4
			DeleteAttribute(pchar, "GenQuest.Detonation");
		}
	}
    if (rand(20) < 3 && sti(rDead.nation) != PIRATE)  // 14% повышаем награду
    {
        ChangeCharacterHunterScore(rKillerCharacter, NationShortName(sti(rDead.nation)) + "hunter", 1+rand(1));
    }
}
// boal <--

void Ship_PlayVictory(string sSound, int iSoundTime)
{
	FadeOutMusic(3); // boal 3000
	PlayStereoOgg(sSound);

	iVicSoundTime = iSoundTime;
}
  /// странные методы ??? не было их в ПКМ и все было гут
void Ship_VicSoundTime()
{
	if (bAbordageStarted || sti(InterfaceStates.Launched)) { return; }

	if (iVicSoundTime > 0)
	{
		iVicSoundTime = iVicSoundTime - iRealDeltaTime;
		if (iVicSoundTime <= 0)
		{
			bUpdatePosMode = true;
		}
	}
}

void Ship_SailHitEvent()
{
}

void Ship_HullHitEvent()
{
	float	fHP;

	int		iBallType = sti(AIBalls.CurrentBallType);

	aref	rShipObject = GetEventData();

	int		iBallCharacterIndex = GetEventData();
	int		iOurCharacterIndex = GetEventData();

	ref		rBallCharacter = GetCharacter(iBallCharacterIndex);	// кто пуляет
	ref		rOurCharacter = GetCharacter(iOurCharacterIndex);   // по кому

	rOurCharacter.Ship.LastBallCharacter = iBallCharacterIndex;

	float	x = GetEventData();
	float	y = GetEventData();
	float	z = GetEventData();

	int		iFirePlaceIndex = GetEventData();   
	float	fFirePlaceDistance = GetEventData();
	
	//Log_Info(" Ship_HullHitEvent : rOurCharacter.id = " + rOurCharacter.id + " rBallCharacter.id = " + rBallCharacter.id);

	bool	bDead = LAi_IsDead(rOurCharacter) && CheckAttribute(rBallCharacter, "Ship.Cannons.Type");  // boal fix

	bool	bSeriousBoom = false;
	bool	bInflame = false;
    bool    isOurCompanion   = IsCompanion(rOurCharacter);
    float   fTmpCannonDamage = 0;
    
    if (bDead) return; // фикс, не нужно обсчитывать труп
	// Cannon damage multiply
	ref rCannon = GetCannonByType(sti(rBallCharacter.Ship.Cannons.Type));
	float fCannonDamageMultiply = stf(rCannon.DamageMultiply);

	float fDistanceDamageMultiply = Bring2Range(1.2, 0.25, 0.0, stf(AIBalls.CurrentMaxBallDistance), stf(AIBalls.CurrentBallDistance));

    if (sti(rBallCharacter.TmpPerks.CriticalShoot) && rand(19)==10) { bSeriousBoom = true; }		// +5%
	if (sti(rBallCharacter.TmpPerks.CannonProfessional) && rand(9)==4) { bSeriousBoom = true; }		// +10%
	
	ref rBall = GetGoodByType(iBallType);
	switch (iBallType)
	{
		case GOOD_BALLS:
			if (rand(85) == 17) { bSeriousBoom = true; }  // boal 35
			if (rand(30) == 15) { bInflame = true; }
			Play3DSound("ball2bort", x, y, z);
		break;
		case GOOD_GRAPES:
			bSeriousBoom = false;
			Play3DSound("grapes2bort", x, y, z);
            if (rand(100) < 30) {Play3DSound("episode_boom", x, y, z);}
		break;
		case GOOD_KNIPPELS:
			bSeriousBoom = false;
			Play3DSound("ball2bort", x, y, z);
		break;
		case GOOD_BOMBS:
			if (rand(50) == 10) { bSeriousBoom = true; }  // boal 20
			if (rand(5) == 1) { bInflame = true; }
			Play3DSound("bomb2bort", x, y, z);
		break;
	}
	fTmpCannonDamage = fCannonDamageMultiply * stf(rBall.DamageHull);
	if (rand(2) == 1) CreateParticleSystem("blast", x, y, z, 0.0, 0.0, 0.0, 0);// boal fix

    if (sti(rOurCharacter.TmpPerks.ShipDefenseProfessional) && rand(1000) < 700) { bSeriousBoom = false; }				// no seriouse boom

    float fCrewDamage = stf(rBall.DamageCrew) * fCannonDamageMultiply * AIShip_isPerksUse(rBallCharacter.TmpPerks.CrewDamageUp, 1.0, 1.15);

	if (bSeriousBoom)
	{
		fCrewDamage = fCrewDamage * 7.0;
		fHP = fDistanceDamageMultiply * fCannonDamageMultiply * stf(rBall.DamageHull) * (8.0 + frnd() * 4.0); // 4.0
		Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_BALL, iBallCharacterIndex);

		if (iBallCharacterIndex == nMainCharacterIndex)
		{
			Log_SetStringToLog(LanguageConvertString(iSeaSectionLang, "Ship_critical"));
		}
		/*int iFlow = rand(100);  // to_do
		if(iFlow < 10)
		{
			if(sti(rOurCharacter.index) == nMainCharacterIndex)
			{
				Log_SetStringToLog(LanguageConvertString(iSeaSectionLang, "Ship_flow"));
			}
			rOurCharacter.ship.flow = iFlow;
		}
		*/
		// boal  check skill -->
		if (!isOurCompanion && IsCompanion(rBallCharacter) && !CheckAttribute(rOurCharacter, "ShipEnemyDisable"))
		{
            AddCharacterExpToSkill(rBallCharacter, "Accuracy", 15);
            AddCharacterExpToSkill(rBallCharacter, SKILL_FORTUNE, 15);
            AddCharacterExpToSkill(rBallCharacter, "Leadership", 2);
            AddCharacterExpToSkill(rBallCharacter, "Sailing", 15);
            AddCharacterExpToSkill(rBallCharacter, "Cannons", 15);
            ChangeCrewExp(rBallCharacter, "Sailors", 0.05);
			ChangeCrewExp(rBallCharacter, "Cannoners", 0.5);
        }
        // boal <--
	}
	else
	{ 
		fHP = fDistanceDamageMultiply * fCannonDamageMultiply * stf(rBall.DamageHull);
		Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_BALL, iBallCharacterIndex); 
		// boal  check skill -->
		if (!isOurCompanion && IsCompanion(rBallCharacter) && !CheckAttribute(rOurCharacter, "ShipEnemyDisable"))
		{
            AddCharacterExpToSkill(rBallCharacter, "Accuracy", 2.5);
            AddCharacterExpToSkill(rBallCharacter, "Sailing", 1);
            AddCharacterExpToSkill(rBallCharacter, "Cannons", 1);
            ChangeCrewExp(rBallCharacter, "Cannoners", 0.01);
        }
        // boal <--
	}
	Ship_ApplyCrewHitpoints(rOurCharacter, fCrewDamage);

	if (bInflame == true && fFirePlaceDistance < 4.0 && iFirePlaceIndex >= 0)
	{
		int iRandStartTime = rand(1000);
		float fTotalFireTime = Ship_GetTotalFireTime(rOurCharacter); 

		PostEvent(SHIP_ACTIVATE_FIRE_PLACE, iRandStartTime, "ialsfl", rShipObject, rOurCharacter, iFirePlaceIndex, "ship_onfire", fTotalFireTime, iBallCharacterIndex);
		PostEvent(SHIP_FIRE_DAMAGE, iRandStartTime, "lllf", iOurCharacterIndex, iBallCharacterIndex, iFirePlaceIndex, fTotalFireTime);
	}

	if (bSeriousBoom == true) 
	{ 
		if (rOurCharacter.id == pchar.id || rand(2) == 1)
		{
			Ship_Serious_Boom(x, y, z); 
		}
		fTmpCannonDamage = fTmpCannonDamage * 6.0;
		//boal 27.09.05 -->
		if ((GetCargoGoods(rOurCharacter, GOOD_POWDER) / 20.0) > (GetCargoMaxSpace(rOurCharacter) * 0.25) && rand(1) == 1)
		{
			Ship_SetExplosion(rOurCharacter, rShipObject);
			Log_Info("На корабле " + rOurCharacter.Ship.Name + " сдетонировал весь пороховой запас.");
		}
		//boal 27.09.05 <--
	}
    SendMessage(&AISea, "laffff", AI_MESSAGE_CANNONS_BOOM_CHECK, rOurCharacter, fTmpCannonDamage, x, y, z);  // fix перенес с проверкой на труп
	// boal 290704 раз в минуту проверяем обиду на гл героя, если жухлит через желтый прицел -->
	//Log_Info(rOurCharacter.id);
	
/*	
	Log_Info(" Ship_HullHitEvent : LastBallCharacter : " + rOurCharacter.Ship.LastBallCharacter + " mCharIndex : " + GetMainCharacterIndex());
	Log_Info(" GetNationRelation2MainCharacter(sti(rOurCharacter.nation)) : " + GetNationRelation2MainCharacter(sti(rOurCharacter.nation)));
	if(CheckAttribute(rOurCharacter, "Coastal_Captain")) Log_Info("Coastal_Captain");
*/	
	
	if (sti(rOurCharacter.Ship.LastBallCharacter) == GetMainCharacterIndex() && GetNationRelation2MainCharacter(sti(rOurCharacter.nation)) != RELATION_ENEMY)
    {
        if (!isOurCompanion && !CheckAttribute(rOurCharacter, "Coastal_Captain")) // по своим можно палить таможня пофиг
        {
            Ship_NationAgressive(rOurCharacter, rOurCharacter);// boal 030804 в один метод
            DoQuestCheckDelay("NationUpdate", 0.7);
        }
    }
	// Jason: изъятие лицензии
	bool btrade = (sti(rOurCharacter.Ship.LastBallCharacter) == GetMainCharacterIndex()) && (CheckAttribute(rOurCharacter, "Ship.Mode")) && (rOurCharacter.Ship.Mode == "trade");
	bool bhol = (sti(rOurCharacter.Ship.LastBallCharacter) == GetMainCharacterIndex()) && (sti(rOurCharacter.nation) == HOLLAND)
	if (CheckCharacterItem(pchar, "HolTradeLicence"))
	{
		if (btrade || bhol)
		{
			TakeNationLicence(HOLLAND);
			log_info("Торговая лицензия аннулирована!");
		}
	}
	/* if (rOurCharacter.id == "TortugaBranderCap_2" || rOurCharacter.id == "TortugaBranderCap_3") //Jason: атака брандеров у Тортуги 2015
	{
		if (sti(rOurCharacter.Ship.LastBallCharacter) == GetMainCharacterIndex() && CheckAttribute(rOurCharacter, "checkattack")) Tortuga_ShipGuardAttack();
	} */
	if (rOurCharacter.id == "WorldMarchCap1" || rOurCharacter.id == "WorldMarchCap2" || rOurCharacter.id == "WorldMarchCap3") //Jason: горячий рейд
	{
		if (!CheckAttribute(pchar, "GenQuest.MarchCap.Battlestart")) DoQuestFunctionDelay("MarchCap2_CheckBattle", 0.5);
	}
	if (rOurCharacter.id == "Cap_Vensan") //Jason: сага, бригантина венсана
	{
		if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Vensan_free")) DoQuestFunctionDelay("Saga_BrigantineDetonate", 0.5);
	}
	if (rOurCharacter.id == "Saga_Vagrant" || rOurCharacter.id == "Saga_vampire") //Jason: сага - Бродяга и Упырь
	{
		Saga_VagrantVampireAttack();
	}
	if (rOurCharacter.id == "Jackman") //Jason: сага - Джекман
	{
		Saga_CenturionAttack();
	}
	if (rOurCharacter.id == "Molligan" && CheckAttribute(pchar, "questTemp.Saga.Molligan.friend") && sti(AIBalls.CurrentBallType) == GOOD_GRAPES) //Jason: сага - Моллиган 
	{
		Saga_MolliganCriticalAttack();
	}
	if (rOurCharacter.id == "Rozencraft" && CheckAttribute(pchar, "GenQuest.Bakaut")) //Jason: генератор бакаута 
	{
		DeleteAttribute(pchar, "GenQuest.Bakaut"); // конец генератора
	}
	if (rOurCharacter.id == "Cap_Utreht" && !CheckAttribute(pchar, "questTemp.Mtraxx.check")) // Addon 2016-1 Jason пиратская линейка 
	{
		pchar.questTemp.Mtraxx.watcher = "true"; // ГГ вступил в бой и может быть замечен
		pchar.questTemp.Mtraxx.check = "true";
		//log_info("Проверка на Утрехт установлена!");
	}
    // boal 290704 раз в минуту проверяем обиду на гл героя, если жухлит через желтый прицел <--sti(AIBalls.CurrentBallType)
}

float Ship_GetTotalFireTime(ref rCharacter)
{
	int iRepairSkill = MakeInt(stf(rCharacter.TmpSkill.Repair) * 10.0); 
	return MakeFloat(5 + 3 * (10 - iRepairSkill));
}

void Ship_FireDamage()
{
	int iOurCharacterIndex = GetEventData();
	int iBallCharacterIndex = GetEventData();

	int iFirePlaceIndex = GetEventData();
	float fTotalFireTime = GetEventData();

	ref rOurCharacter = GetCharacter(iOurCharacterIndex);
	//ref rBallCharacter = GetCharacter(iBallCharacterIndex);
	
	int iSClass = GetCharacterShipClass(rOurCharacter);

	float fHP = (8 - iSClass) * (0.5 + frnd() * 0.5);

	int iTime = 1000 + rand(500);

	// if abordage or interface launched
	if (!bAbordageStarted && !sti(InterfaceStates.Launched)) 
	{ 
		Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_BALL, iBallCharacterIndex); 

		fTotalFireTime = fTotalFireTime - MakeFloat(iTime) / 250.0;
	}

	if (fTotalFireTime > 0.0)
	{
		PostEvent(SHIP_FIRE_DAMAGE, iTime, "lllf", iOurCharacterIndex, iBallCharacterIndex, iFirePlaceIndex, fTotalFireTime);
	}
}

void Ship_Serious_Boom(float x, float y, float z)
{
	CreateBlast(x,y,z);
	CreateParticleSystem("ShipExplode", x, y, z, 0.0, 0.0, 0.0, 0);
	Play3DSound("ship_explosion", x, y, z);
}

void Ship_SetFantomData(ref rFantom)
{
	ref		rBaseShip;

	rBaseShip = GetRealShip(sti(rFantom.Ship.Type));

	int iOptCrew = sti(rBaseShip.OptCrew);

	int iBaseHP = sti(rBaseShip.HP);
	int iCapacity = sti(rBaseShip.Capacity);

	rFantom.ship.Crew.Quantity = iOptCrew - rand(makeint(iOptCrew / 3)) + makeint(iOptCrew / 5); //отп команды +-20%
	
	rFantom.Ship.HP = iBaseHP;
	if (rand(3) == 2) 
	{ 
		rFantom.Ship.HP = iBaseHP - rand(makeint(iBaseHP / 8));
	}
	if (CheckAttribute(rFantom, "Ship.Masts")) { DeleteAttribute(rFantom, "Ship.Masts"); }
	if (CheckAttribute(rFantom, "Ship.Blots")) { DeleteAttribute(rFantom, "Ship.Blots"); }
	if (CheckAttribute(rFantom, "Ship.Sails")) { DeleteAttribute(rFantom, "Ship.Sails"); }
	if (CheckAttribute(rFantom, "Ship.Hulls")) { DeleteAttribute(rFantom, "Ship.Hulls"); }
}

void CharacterUpdateShipFromBaseShip(int iCharacterIndex)
{
	ref rCharacter, rBaseShip;
	
	rCharacter = GetCharacter(iCharacterIndex);
	rBaseShip = GetRealShip(sti(rCharacter.Ship.Type));

	if (!CheckAttribute(rCharacter,"Ship.Crew.Quantity")) 
	{ 
		rCharacter.ship.Crew.Quantity = rBaseShip.MaxCrew; 
	}

	if (!CheckAttribute(rCharacter,"Ship.HP")) 
	{ 
		rCharacter.Ship.HP = rBaseShip.HP; 
	}
	if (!CheckAttribute(rCharacter,"Ship.SP")) 
	{ 
		rCharacter.Ship.SP = rBaseShip.SP; 
	}

	if (!CheckAttribute(rCharacter,"Ship.Cannons.Charge.Type")) 
	{ 
		rCharacter.Ship.Cannons.Charge.Type = GOOD_BOMBS; 
	}
	
	//Trace("Init cindex = " + iCharacterIndex + ", ship HP = " + rCharacter.Ship.HP + ", id = " + rCharacter.id + ", idx = " + rCharacter.index);
	if (!CheckAttribute(rCharacter,"Ship.Cannons.Type")) 
	{ 
		rCharacter.Ship.Cannons.Type = CANNON_TYPE_CULVERINE_LBS8; 
	}

	rCharacter.Ship.Cannons.Borts = "";
}

float Ship_CalcGrapplingPerk(ref rCharacter)
{
	aref	arTmpPerks; 
	makearef(arTmpPerks, rCharacter.TmpPerks);

	float fGrapplingPerk = AIShip_isPerksUse(rCharacter.TmpPerks.LongRangeGrappling, 1.0, 1.15); 
	return AIShip_isPerksUse(rCharacter.TmpPerks.GrapplingProfessional, fGrapplingPerk, 1.25);

	return fGrapplingPerk;
}

float Ship_CalcMaxAbordageDistance(float fGrappling, float fGrapplingPerk)
{
	return fGrapplingPerk * Bring2Range(15.0, 40.0, 0.0, 1.0, fGrappling);
}

float Ship_CalcMaxAbordageAngle(float fGrappling)
{
	return Bring2Range(0.70, 0.45, 0.0, 1.0, fGrappling);
}

float Ship_CalcMaxAbordageSpeed(float fGrappling)
{
	return Bring2Range(3.0, 5.0, 0.0, 1.0, fGrappling);
}

void Ship_CheckEnemiesAroundMainCharacter()
{
}

void Ship_CheckMainCharacter()
{
	aref	arUpdate;
	ref		rIsland;
	int		i, iRelation;
	float	x, z, fBestDistance, fDistance;
	float	fMinEnemyDistance = 1000000.0;
	float	fMinFortAbordDistance = 1000000.0; // для работы доплыть до при разбитом форте
	float	fortDistance = 1000000.0; //для разделения дистанций выхода на карту кораблей и фортов
	bool	bAbordageStartNow = false;
	int		iAbordageStartNowCharacter = -1;

	PostEvent(SHIP_CHECK_RELOAD_ENABLE, 1000);

	ref rCharacter = pchar;

	// if abordage launched, return
	if (bAbordageStarted) { return; }

	// if interface launched, return
	if (sti(InterfaceStates.Launched)) { return; }

	// if main character is dead - skip
	if (LAi_IsDead(rCharacter)) { return; }

	iStormLockSeconds = iStormLockSeconds - 1;
	if (iStormLockSeconds < 0) { iStormLockSeconds = 0; }

	bAbordageFortCanBe = false;
	bAbordageShipCanBe = false;
	bCanEnterToLand = false;
	bDisableSailTo = false;
	sIslandLocator = "";
	sIslandID = "";

	makearef(arUpdate, rCharacter.SeaAI.Update);

	if (!CheckAttribute(arUpdate, "Ships")) { return; }
	if (!CheckAttribute(arUpdate, "Forts")) { return; }
    // boal время в море идет!!! -->
    locTmpTime = locTmpTime + 0.5;  // можно засунуть проверку locDisableUpdateTime, если нужно выключить
    if (locTmpTime > 9)
	{
		/*if (bDisableMapEnter)
		{
			if (locTmpTime > 29)
			{
				CalcLocalTime(6);
    			BattleInterface.textinfo.Date.text = XI_convertString("Date:")+GetQuestBookData();
			}
		}
		else
		{ */
		    CalcLocalTime(2);
      		BattleInterface.textinfo.Date.text = XI_convertString("Date:")+GetQuestBookData();
		//}
	}
	// boal время в море идет!!! <--
	
	x = stf(rCharacter.Ship.Pos.x);
	z = stf(rCharacter.Ship.Pos.z);

	float fOurHP = Ship_GetHP(rCharacter);
	float fOurFencing = stf(rCharacter.TmpSkill.Fencing);
	float fOurGrappling = stf(rCharacter.TmpSkill.Grappling);
	float fOurCrewFencing = (0.1 + fOurFencing * stf(rCharacter.Ship.Crew.Quantity));

	float fOurBoxSizeX = stf(rCharacter.Ship.BoxSize.x) / 2.0;

	bool bGrapplingProfessional = sti(rCharacter.TmpPerks.GrapplingProfessional);

	// max abordage parameters for our player
	float fOurGrapplingPerk = Ship_CalcGrapplingPerk(rCharacter);

	float fOurMaxAbordageDistance = Ship_CalcMaxAbordageDistance(fOurGrappling, fOurGrapplingPerk);
	float fOurMaxAbordageAngle = Ship_CalcMaxAbordageAngle(fOurGrappling); 
	float fOurMaxAbordageSpeed = Ship_CalcMaxAbordageSpeed(fOurGrappling);

	string sPlayerLocation = rCharacter.location;
	string sPlayerLocator = rCharacter.location.locator;

	// find island
	int iIslandIndex = FindIsland(sPlayerLocation);
	if (iIslandIndex >= 0)
	{
		rIsland = GetIslandByIndex(iIslandIndex);
	}

	aref aShips, aForts;
	makearef(aShips, arUpdate.Ships);
	makearef(aForts, arUpdate.Forts);

	// check forts for abordage
	int iFortsNum = GetAttributesNum(aForts);
	fBestDistance = 10000000.0;
	for (i=0; i<iFortsNum; i++)
	{
		aref aFort = GetAttributeN(aForts, i);
		iRelation = sti(aFort.relation);

		ref rFortCharacter = GetCharacter(sti(aFort.idx)); 
		if (LAi_IsDead(rFortCharacter)) { continue; }
		int iFortMode = sti(rFortCharacter.Fort.Mode);
		aref aRLoc = FindIslandReloadLocator(sPlayerLocation, rFortCharacter.location.locator);
		if (!CheckAttribute(aRLoc, "Radius")) { continue; }  // fix
		float fRadius = stf(aRLoc.Radius);
		fDistance = stf(aFort.Distance);
		switch (iFortMode)
		{
			case FORT_NORMAL:
				if (iRelation == RELATION_ENEMY)
				{
					if (fMinEnemyDistance > fDistance) { fortDistance = fDistance; }
				}
				else
				{
					// единоразовое узнавание врага
					// проверка на ложный флаг -->
					if (!CheckAttribute(rFortCharacter, "CheckFlagYet"))
					{
                        if (!CheckAttribute(rFortCharacter, "CheckFlagDate") || GetNpcQuestPastDayParam(rFortCharacter, "CheckFlagDate") > 1)
                        { // второй раз подряд уже не смотрим, на выход их порта
							if (fDistance < (MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER_FORT * 1.5))
						    {
						        rFortCharacter.CheckFlagYet = true; // все, проверил
						        Ship_CheckFlagEnemy(rFortCharacter);
						        SaveCurrentNpcQuestDateParam(rFortCharacter, "CheckFlagDate");
						    }
					    }
					}
					// проверка на ложный флаг <--
				}
				// Addon 2016-1 Jason пиратская линейка
				if (fDistance < 3000 && CheckAttribute(pchar, "questTemp.Mtraxx.check"))
				{
					DeleteAttribute(pchar, "questTemp.Mtraxx.check");
					pchar.questTemp.Mtraxx.Silkfail = "true";
				}
				if (fDistance < 5000 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Check"))
				{
					DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Check");
					pchar.questTemp.Mtraxx.Ignasio.Fail = "true";
				}
				if (fDistance < 5000 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Ship"))
				{
					Mtraxx_CorridaCheckPolacre();
				}
				if (fDistance < 1500 && fDistance > 800 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal"))
				{
					pchar.questTemp.Mtraxx.Ignasio.Flag = "true";
				}
				if (fDistance > 1500 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal") && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag"))
				{
					DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag");
				}
				if (fDistance < 800 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal"))
				{
					DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal");
					DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag");
					RemoveItems(pchar, "wolfreeks_book", 1);
					AddQuestRecord("Roger_8", "13");
					Mtraxx_CorridaIgnasioFail();
				}
				// Jason НСО
				if (fDistance < 1000 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Patria.SanMartinFort") && ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
				{
					bQuestDisableMapEnter = true;
					DoQuestFunctionDelay("Mtraxx_MarkusGameOver", 3.0);
				}
				if (fDistance < 400 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Patria.SanMartinFort"))
				{
					Patria_SanMartinFortAttack();
				}
				if (fDistance > 1500 && pchar.location == "Nevis" && CheckAttribute(pchar, "questTemp.Patria.Escape"))
				{
					DeleteAttribute(pchar, "questTemp.Patria.Escape");
					bQuestDisableMapEnter = false;
				}
			break;
			case FORT_DEAD:
                if (iRelation == RELATION_FRIEND) { continue; }
				if (fDistance > fRadius) { continue; }
				if (fBestDistance > fDistance)
				{
					fBestDistance = fDistance;

					bCanEnterToLand = true;

					sIslandID = rIsland.id;
					makearef(arIslandReload, rIsland.reload);
					sIslandLocator = aRLoc.GoAfterBoard.location;
				}
			break;
			case FORT_ABORDAGE:
                if (iRelation == RELATION_FRIEND) { continue; }
				if (iRelation == RELATION_ENEMY)
				{
					//if (fMinEnemyDistance > fDistance) { fMinEnemyDistance = fDistance; }
					if (fMinFortAbordDistance > fDistance) { fMinFortAbordDistance = fDistance; } //fix входа в порт
				}
				if (fDistance > fRadius) { continue; }
				if (!Character_IsAbordageEnable(rFortCharacter) || bDisableMapEnter)  { continue; } // bDisableMapEnter - значит враги рядом, нефиг брать форт под пушками кораблей boal
				
				if (fBestDistance > fDistance)
				{
					fBestDistance = fDistance;

					bAbordageFortCanBe = true;
					sAbordageLocator = rFortCharacter.location.locator;
					iAbordageFortEnemyCharacter = sti(rFortCharacter.index);
				}
			break;
		}
	}

	// check ships for abordage
	int iShipsNum = GetAttributesNum(aShips);
	fBestDistance = 10000000.0;
	for (i=0; i<iShipsNum; i++)
	{
		aref aShip = GetAttributeN(aShips, i);

		ref rShipCharacter = GetCharacter(sti(aShip.idx)); 
		fDistance = stf(aShip.Distance);		// distance between player ship and this ship
		iRelation = sti(aShip.relation);
		
		if (LAi_IsDead(rShipCharacter)) 
		{ 
			continue; 
		}
		if (iRelation != RELATION_ENEMY) 
		{ 
			continue; 
		}
		if (fMinEnemyDistance > fDistance) 
		{ 
			fMinEnemyDistance = fDistance; 
		}

		if (!Character_IsAbordageEnable(rShipCharacter)) 
		{ 
			continue; 
		}

		float fAng = stf(aShip.d_ay);						// it's dot.ay between ships
		float fRelativeSpeed = stf(aShip.RelativeSpeed);	// it's relative speed about player ship
		float fEnemyBoxSizeX = stf(rShipCharacter.Ship.BoxSize.x) / 2.0;

		bool bOurAngleTest = abs(fAng) > fOurMaxAbordageAngle && fRelativeSpeed < fOurMaxAbordageSpeed;
		float fAbordageDistance = fDistance - fEnemyBoxSizeX - fOurBoxSizeX;

		// test our ship with enemy
		if (bGrapplingProfessional || bOurAngleTest)
		{
			if (fAbordageDistance < fOurMaxAbordageDistance && fBestDistance > fDistance)
			{
				// abordage enable
				fBestDistance = fDistance;
				bAbordageShipCanBe = true;
				iAbordageShipEnemyCharacter = sti(rShipCharacter.index);
			}
		}

		// test enemy ship with our
		float fEnemyGrappling = stf(rShipCharacter.TmpSkill.Grappling);

		// max abordage parameters for our player
		float fEnemyGrapplingPerk = Ship_CalcGrapplingPerk(rShipCharacter);

		float fEnemyMaxAbordageDistance = Ship_CalcMaxAbordageDistance(fEnemyGrappling, fEnemyGrapplingPerk);
		float fEnemyMaxAbordageAngle = Ship_CalcMaxAbordageAngle(fEnemyGrappling); 
		float fEnemyMaxAbordageSpeed = Ship_CalcMaxAbordageSpeed(fEnemyGrappling);

		bool bEnemyAngleTest = abs(fAng) > fEnemyMaxAbordageAngle && fRelativeSpeed < fEnemyMaxAbordageSpeed;
		if (bEnemyAngleTest)
		{
			if (fAbordageDistance < fEnemyMaxAbordageDistance)
			{
				// maybe other character want abordage us?
				float fEnemyFencing = stf(rCharacter.TmpSkill.Fencing); 
				float fEnemyCrewFencing = (0.1 + fEnemyFencing * stf(rShipCharacter.Ship.Crew.Quantity));
				float fRatio = fEnemyCrewFencing / fOurCrewFencing;
				if (sti(rShipCharacter.nation) == PIRATE) 
				{ 
					fRatio = fRatio * 1.6; 
				}
				if (fRatio > 1.2 && !CheckAttribute(rShipCharacter, "Abordage.MakeDisable")) // Jason НСО
				{
					iAbordageStartNowCharacter = sti(rShipCharacter.index);
					bAbordageStartNow = true;
					break;
				}
			}
		}
	}

	// check reload to locations possibility
	if (iIslandIndex >= 0 && fMinEnemyDistance > MIN_ENEMY_DISTANCE_TO_DISABLE_ENTER_2_LOCATION)
	{
		if (Island_isReloadEnableGlobal(sPlayerLocation))
		{
			aref arReload;
			makearef(arReload, rIsland.Reload);

			int iNumLocators = GetAttributesNum(arReload);
			for (int j=0; j<iNumLocators; j++)
			{
				aref arLocator;
				arLocator = GetAttributeN(arReload, j);
				string sLocatorName = GetAttributeName(arLocator);
				if (Island_isReloadFort(sPlayerLocation, arLocator.name)) { continue; }
				if (!Island_isReloadEnableLocal(sPlayerLocation, arLocator.name)) { continue; }
				if(!CheckAttribute(rIsland, "reload." + sLocatorName + ".x") || !CheckAttribute(rIsland, "reload." + sLocatorName + ".z"))
				{
					continue;
				}

				float x1 = stf(rIsland.reload.(sLocatorName).x);
				float z1 = stf(rIsland.reload.(sLocatorName).z);
				/*if (checkAttribute(rIsland, "reload."+sLocatorName+".wdmisland"))
				{
					wdmCurrentIsland = rIsland.reload.(sLocatorName).wdmisland;
				}*/
				float r = stf(rIsland.reload.(sLocatorName).radius);
				if (sqrt(sqr(x1 - x) + sqr(z1 - z)) < r)
				{
					bCanEnterToLand = true;
					sIslandID = rIsland.id;
					makearef(arIslandReload, rIsland.reload);
					sIslandLocator = rIsland.reload.(sLocatorName).name;

					// LDH 24Jan17 - display mooring location name -->
                    int nFile = LanguageOpenFile("LocLables.txt");
					string MoorName = LanguageConvertString(nFile, rIsland.reload.(sLocatorName).label);
                    LanguageCloseFile(nFile);
					if (!CheckAttribute(pchar, "MoorName")) pchar.MoorName = " ";
					if (MoorName != pchar.MoorName)
                    {
						// LDH 14Feb17 rewrite
						// LDH 26Jan17 - play anchor sound if moor location changes due to overlapping locations
						if (pchar.MoorName != " " && MoorName != " ")
						{
							boal_soundOn = false;		// make sure it's only played once
							PlaySound("interface\_Yakordrop.wav");
						}
						pchar.MoorName = MoorName;
                    }
					// LDH 24Jan17 <--

					break;
				}
			}

			// LDH 12Feb17 display moor name in battle interface -->
			// If we don't do this, location does not update
			BattleInterface.textinfo.Location.text = GetBILocationName();
			// LDH 12Feb17 <--
		}
	}
	else
	{
		// LDH 13Feb17 display region name in battle interface -->
		pchar.Moorname = " ";
		// If we don't do this, location does not update
		BattleInterface.textinfo.Location.text = GetBILocationName();
		// LDH 13Feb17 <--
	}

	// disable any abordage if storm
	if (Whr_IsStorm())
	{
		bAbordageStartNow = false;
		bAbordageFortCanBe = false;
		bAbordageShipCanBe = false;
	}

	// Enter 2 map enable/disable
	// Peoples on ship mode update
	int iPrevShipPOSMode = sti(rCharacter.Ship.POS.Mode);
	rCharacter.Ship.POS.Mode = SHIP_SAIL;

	bDisableMapEnter = false;
	if (fMinEnemyDistance < MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER)
	{
		bCanEnterToLand = false;
		bDisableMapEnter = true;

		rCharacter.Ship.POS.Mode = SHIP_WAR;
	}
	if (fortDistance < MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER_FORT)
	{
		bCanEnterToLand = false;
		bDisableMapEnter = true;
		rCharacter.Ship.POS.Mode = SHIP_WAR;
	}
    // boal fix входа в порт -->
    if (fMinFortAbordDistance < MIN_ENEMY_DISTANCE_TO_DISABLE_ENTER_2_LOCATION)
    {
        bCanEnterToLand = false;
    }
    // boal <--
	if (iStormLockSeconds)
	{
		bDisableMapEnter = true;
		bCanEnterToLand = false;
		bDisableSailTo = true;

		rCharacter.Ship.POS.Mode = SHIP_STORM;
	}

	// new music
	bool bMakeCurrentUpdate = bUpdatePosMode;
	if( iVicSoundTime<=0 && sti(rCharacter.Ship.POS.Mode) != iPrevShipPOSMode ) {
		bMakeCurrentUpdate = true;
	}
	if( bMakeCurrentUpdate )
	{
		switch (sti(rCharacter.Ship.POS.Mode))
		{
			case SHIP_SAIL:
				if (!Whr_IsStorm()) 
				{ 
					seaAlarmed = false;
					if (iPrevShipPOSMode == SHIP_WAR)
					{
                   		Ship_PlayVictory("music_ship_victory", 8500);
						//PlayStereoOGG("music_ship_victory");
					} // fix boal
					FadeOutMusic(3);
					//PlayStereoOGG(sSeaStartMusicName); 
					if (Whr_IsDay()) SetMusic("music_sea_day");
					else SetMusic("music_sea_night");
					//Sound_OnSeaAlarm555(false, bUpdatePosMode); 

				}
				else
				{ 
					FadeOutMusic(3); //fix
					PlayStereoOGG("music_End_storm"); 
				}
			break;
			case SHIP_WAR:
				FadeOutMusic(3); // fix
				//PlayStereoOGG("music_sea_battle"); 
				seaAlarmed = true;
				SetMusic("music_sea_battle");
				//Sound_OnSeaAlarm555(true, bUpdatePosMode);
			break;
		}

		bUpdatePosMode = false;
	}

	// if quest disable enter 2 map
	if (bQuestDisableMapEnter) { bDisableMapEnter = true; }

	// Start abordage automatically
	if (bAbordageStartNow) 
	{ 
		ref rTargetCharacter = GetCharacter(iAbordageStartNowCharacter);
		if(GetRelation(sti(rCharacter.index), iAbordageStartNowCharacter) == RELATION_ENEMY)
		{
			if(LAi_IsDead(rCharacter) == false && LAi_IsDead(rTargetCharacter) == false)
			{
				iAbordageShipEnemyCharacter = iAbordageStartNowCharacter;
				Sea_AbordageLoad(SHIP_ABORDAGE, false); 
			}
		}
	}
}

void Ship_OnStrandNext()
{
	ref	rCharacter = GetCharacter(GetEventData());
	if (LAi_IsDead(rCharacter)) { return; }

	bool bOnStrand = sti(rCharacter.Ship.Strand);
	if (!bOnStrand) 
	{ 
		int iSoundID = sti(rCharacter.Ship.Strand.SndID);
		if (iSoundID != 0) { StopSound(sti(rCharacter.Ship.Strand.SndID), 3000); }
		rCharacter.Ship.Strand.SndID = SOUND_INVALID_ID;
		return; 
	}
	if (!CheckAttribute(rCharacter, "AlwaysSandbankManeuver"))  //boal
	{
		float fCurrentSpeedZ = stf(rCharacter.Ship.Speed.z);
		float fHP = 4.0 * fCurrentSpeedZ / 7.0;
		Ship_ApplyHullHitpoints(rCharacter, fHP, KILL_BY_ISLAND, -1);
	}
	PostEvent(SHIP_TO_STRAND_NEXT, 100 + rand(100), "l", sti(rCharacter.index));
}

void Ship_OnStrand()
{
	ref rCharacter = GetCharacter(GetEventData());
	bool bNewStrand = GetEventData();
	
	bool bPrevStrand = sti(rCharacter.Ship.Strand);

	rCharacter.Ship.Strand = bNewStrand;

	float x = stf(rCharacter.Ship.Pos.x);
	float y = stf(rCharacter.Ship.Pos.y);
	float z = stf(rCharacter.Ship.Pos.z);

	if (bPrevStrand == 0 && bNewStrand == 1)
	{
		PostEvent(SHIP_TO_STRAND_NEXT, 100, "l", sti(rCharacter.index));
		rCharacter.Ship.Strand.SndID = Play3DSoundComplex("ship_aground", x, y, z, true, false);
	}
}

// Small boom
void Ship_DetonateSmall()
{
	ref		rCharacter = GetCharacter(GetEventData());
	aref	arCharShip; makearef(arCharShip, rCharacter.Ship);

    if (bAbordageStarted) { return; }
	if (sti(InterfaceStates.Launched)) { return; }
	
	float x = stf(arCharShip.Pos.x);
	float y = stf(arCharShip.Pos.y);
	float z = stf(arCharShip.Pos.z);
	
	if (y > -3.0)
	{
		int iSClass = GetCharacterShipClass(rCharacter);
		PostEvent(SHIP_DETONATE_SMALL, 200 + iSClass * 300 + rand(900), "l", sti(rCharacter.index));
	}

	float bx = arCharShip.BoxSize.x;
	float by = arCharShip.BoxSize.y;
	float bz = arCharShip.BoxSize.z;

	float fCos = cos(stf(arCharShip.Ang.y));
	float fSin = sin(stf(arCharShip.Ang.y));

	//for (int i=0; i < 1 + rand(1); i++)
	//{
		float x1, y1, z1;
		x1 = (frnd() - 0.5) * bx;
		z1 = (frnd() - 0.5) * bz;

		RotateAroundY(&x1, &z1, fCos, fSin);

		y1 = 1.0 + y + frnd() * 3.0;
		Ship_Serious_Boom(x1 + x, y1, z1 + z);
		CreateParticleSystem("blast", x1 + x, y1, z1 + z, 0.0, 0.0, 0.0, 0);
	//}
}

void Ship_Turn180(ref rCharacter)
{
	//rCharacter.TmpPerks.Turn = true;
	//rCharacter.TmpPerks.Turn.Angle = PI;
	rCharacter.Tmp.SpeedRecall = 0; // чтоб пересчитался маневр
}

// Big Boom on ship
void Ship_Detonate(ref rCharacter, bool bMakeSmallBoom, bool bMakeDead)
{
	if (!CheckAttribute(rCharacter, "Ship.Pos.x")) 
	{
		Trace("Ship_Detonate: Can't find Ship.Pos in character with id: " + rCharacter.id);
		return;
	}
	aref	arCharShip; makearef(arCharShip, rCharacter.Ship);
	
	float x = stf(arCharShip.Pos.x);
	float y = stf(arCharShip.Pos.y);
	float z = stf(arCharShip.Pos.z);

	int iMinBoom = MakeInt(Bring2Range(6.0, 2.0, 1.0, 7.0, stf(GetCharacterShipClass(rCharacter))));

	float bx = arCharShip.BoxSize.x;
	float by = arCharShip.BoxSize.y;
	float bz = arCharShip.BoxSize.z;

	float fCos = cos(stf(arCharShip.Ang.y));
	float fSin = sin(stf(arCharShip.Ang.y));

	bool isBoomAlready = false;
	int iMax = iMinBoom + rand(2); //fix
	for (int i=0; i<iMax; i++)
	{
		float x1, y1, z1;
		x1 = (frnd() - 0.5) * bx;
		z1 = (frnd() - 0.5) * bz;

		RotateAroundY(&x1, &z1, fCos, fSin);
		
		y1 = 1.0 + y + frnd() * 3.0;
		if(isBoomAlready == false)
		{
			Ship_Serious_Boom(x1 + x, y1, z1 + z);
		}
		isBoomAlready = true;
		CreateParticleSystem("blast_inv", x1 + x, y1, z1 + z, 0.0, 0.0, 0.0, 0);
	}
	if (bMakeDead) { ShipDead(sti(rCharacter.Index), KILL_BY_SPY, -1); }

	if (bMakeSmallBoom) { PostEvent(SHIP_DETONATE_SMALL, 600 + rand(1000), "l", sti(rCharacter.index)); } 
}

float AIShip_isPerksUse(string sPerk, float fOff, float fOn)
{
	if (sti(sPerk)) { return fOn; }
	return fOff;
}

// EVENT, calculate dynamic parameters for ship, one per second
void Ship_UpdateParameters()
{
	int		iCharacterIndex = GetEventData();
	ref		rCharacter = GetCharacter(iCharacterIndex);
	float	fSailState = GetEventData();
	
	bool	bDead = LAi_IsDead(rCharacter);
	//Log_Testinfo("Ship_UpdateParameters " + rCharacter.id);
	
	if(sti(rCharacter.ship.type) == SHIP_NOTUSED || bDead)   // super fix boal
	{
		return;
	}
    // рудимент bool	bStrand = sti(rCharacter.Ship.Strand);
	aref	arTmpPerks; makearef(arTmpPerks, rCharacter.TmpPerks);

	// update temporary skill storage
	Ship_UpdateTmpSkills(rCharacter);

	Cannon_RecalculateParameters(sti(rCharacter.index));

	// some of ship parameters
	aref	arCharShip; makearef(arCharShip, rCharacter.Ship);
	ref		rShip = GetRealShip(sti(arCharShip.Type));

    float fShipSpeed, fShipTurnRate;
    
	// boal кэш оптимизация -->
	if (!CheckAttribute(rCharacter, "Tmp.SpeedRecall") || sti(rCharacter.Tmp.SpeedRecall) <= 0)
	{
		fShipSpeed    = FindShipSpeed(rCharacter);
		fShipTurnRate = FindShipTurnRate(rCharacter);
		
		rCharacter.Tmp.SpeedRecall   = 8 + rand(5);
		rCharacter.Tmp.fShipSpeed    = fShipSpeed;
		rCharacter.Tmp.fShipTurnRate = fShipTurnRate;
	}
	else
	{
		fShipSpeed    = stf(rCharacter.Tmp.fShipSpeed);
		fShipTurnRate = stf(rCharacter.Tmp.fShipTurnRate);
		
		rCharacter.Tmp.SpeedRecall   = sti(rCharacter.Tmp.SpeedRecall) - 1;
	}
    // boal кэш оптимизация <--
    
	// wind power
	float	fWindPower = Whr_GetWindSpeed() / WIND_NORMAL_POWER;	
	float	fWindDotShip = GetDotProduct(Whr_GetWindAngle(), stf(arCharShip.Ang.y));		// Wind.ay | Ship.ay
	float   fKint = 1.0 + (0.5 - makefloat(sti(RealShips[sti(rCharacter.ship.type)].Class))/6.0) * ((Whr_GetWindSpeed() - 8.0)/10.0);
    // boal -->
	fShipSpeed = (fShipSpeed * fWindPower * fKint);  // boal крейсерская скорость до уменьшений при данном ветре.
	arCharShip.MaxSpeedZ = fShipSpeed; 
	//Log_info("1 = " + arCharShip.MaxSpeedZ);
	arCharShip.MaxSpeedZ = Sea_ApplyMaxSpeedZ(arCharShip, fWindDotShip, rCharacter); // учет парусов в др месте
	
	//Log_info("2 = " + arCharShip.MaxSpeedZ);
	// boal <--
	//  поднимем выше и закэшируем float fShipTurnRate = FindShipTurnRate(rCharacter);
	
	float fMaxSpeedY = stf(rShip.TurnRate) / Sea_TurnRateMagicNumber(); //boal

	float fTRFromSailState = 1.0;
	switch (MakeInt(fSailState * 2.0))
	{
		case 0: fTRFromSailState = 0.05; break;
		case 1: fTRFromSailState = 1.0; break;
		case 2: fTRFromSailState = 0.68; break;
	}
	// boal зависимость от скорости на маневр -->
    float	fTRFromSpeed = 1.0;
    float fCurrentSpeedZ = stf(rCharacter.Ship.Speed.z);
	if (iCharacterIndex == GetMainCharacterIndex())
	{
        if (MOD_SKILL_ENEMY_RATE > 2) // халява и юнга - послабление)
        {
            if (iArcadeSails == 1)
        	{
               fTRFromSpeed = 1.0 - 0.5 * (1.0 - Clampf(fCurrentSpeedZ / fShipSpeed));
    		}
    		else
    		{
    		    fTRFromSpeed = 1.0 - 0.86 * (1.0 - Clampf(fCurrentSpeedZ / fShipSpeed));
    		}
        }
	}
	else
	{
		if (iArcadeSails == 1)
    	{
           fTRFromSpeed = 1.0 - (0.51 - MOD_SKILL_ENEMY_RATE*0.01) * (1.0 - Clampf(fCurrentSpeedZ / fShipSpeed));
		}
		else
		{
		    fTRFromSpeed = 1.0 - (0.87 - MOD_SKILL_ENEMY_RATE*0.01) * (1.0 - Clampf(fCurrentSpeedZ / fShipSpeed));
		}
	}
	// boal зависимость от скорости на маневр <--
	float fTRResult = fMaxSpeedY * fShipTurnRate * fTRFromSailState * fTRFromSpeed;
	// ===============
	// boal далее я все закоментил, тк мешало работать коду от скорости, да и вообще сомнительно это для маневра.
	// VANO :: update fTRResult using rotate with wind direction
	//float fRotateSide = stf(arCharShip.speed.y);
	/*float fPrevWindDotShip = stf(arCharShip.WindDotShip);
	bool bShipTurnToWind = fWindDotShip >= fPrevWindDotShip;
	float fWindTurnMultiply = 1.0;
	if (bShipTurnToWind) 
		{ fWindTurnMultiply = Bring2Range(1.5, 1.0, 0.0, 1.0, abs(fWindDotShip)); }
	else 
		{ fWindTurnMultiply = Bring2Range(0.5, 1.0, 0.0, 1.0, abs(fWindDotShip)); }

	arCharShip.WindDotShip = fWindDotShip;
	//Trace("fWindTurnMultiply = " + fWindTurnMultiply);
	// ===============

	fTRResult = fWindTurnMultiply * Bring2Range(0.01, 1.0, 0.00001, 1.0, fTRResult);
	*/
	fTRResult = Bring2Range(0.07, 0.95, 0.00001, 1.0, fTRResult);
	arCharShip.MaxSpeedY =	fTRResult;

    // Apply arcade mode
	if (iArcadeSails == 1)
	{
		//arCharShip.MaxSpeedZ = 6.0 * stf(arCharShip.MaxSpeedZ);
		arCharShip.MaxSpeedZ = (2.5 * stf(arCharShip.MaxSpeedZ));
		arCharShip.MaxSpeedY = (2.0 * stf(arCharShip.MaxSpeedY));
	}
	else
	{
		//arCharShip.MaxSpeedY = 0.75 * stf(arCharShip.MaxSpeedY);
		arCharShip.MaxSpeedZ = (1.0 * stf(arCharShip.MaxSpeedZ));
	}
	//Log_Info("MaxSpeedY = "  + arCharShip.MaxSpeedY);
	// calculate immersion
	float	fLoad = Clampf(GetCargoLoad(rCharacter) / stf(rShip.Capacity));
	arCharShip.Immersion = (stf(rShip.SubSeaDependWeight) * fLoad); // это уровень погружения от веса

	// do damage if ship hull < 10%, sinking
	float fBaseSailHP = stf(rShip.SP);
	float fBaseShipHP = stf(rShip.HP);
	float fCurHP = stf(arCharShip.HP);
	if(fBaseShipHP < fCurHP)
	{
		fBaseShipHP = fCurHP;
	}
	if (bSeaActive && (fCurHP / fBaseShipHP < 0.09999))
	{
        float fLightRepair = AIShip_isPerksUse(arTmpPerks.LightRepair, 1.0, 0.0);
        // это спец атрибут по убиванию этой функции
        if (CheckAttribute(rCharacter, "SinkTenPercent") && !sti(rCharacter.SinkTenPercent)) { fLightRepair = 0.0; }
		float fSinkDamage = fLightRepair * (fBaseShipHP / 100.0) * 0.08;
		if (CheckAttribute(rCharacter, "Ship.LastBallCharacter")) 
		{ 
			Ship_ApplyHullHitpoints(rCharacter, fSinkDamage, KILL_BY_BALL, sti(rCharacter.Ship.LastBallCharacter));
		}
		else
		{
			Ship_ApplyHullHitpoints(rCharacter, fSinkDamage, KILL_BY_TOUCH, -1);
		}
		/*if(!CheckAttribute(rCharacter, "ship.flow")) // to_do
		{
			rCharacter.ship.flow = 0;
		}
		rCharacter.ship.flow = sti(rCharacter.ship.flow) + 1;
		*/
		if (iCharacterIndex == nMainCharacterIndex) 
		{ 
            // boal -->
			if(!IsPerkIntoList("sink"))
        	{
				if (rand(1) == 0)
				{
					PlaySound("Interface\_Abandon1.wav");
				}
				else
				{
					PlaySound("Interface\_Abandon2.wav");
				}
			}
			// boal <--
			AddPerkToActiveList("sink"); 
		}
	}
	else
	{
		if (iCharacterIndex == nMainCharacterIndex) { DelPerkFromActiveList("sink"); }
	}

	float fStormProfessional = AIShip_isPerksUse(arTmpPerks.StormProfessional, 1.0, 0.7);

    // boal fix defence ship in storm 11.05.05 -->
    if (CheckAttribute(rCharacter, "DontHitInStorm"))
    {
		fStormProfessional = 0;
	}
	// boal fix defence ship in storm 11.05.05 <--
	// do damage if storm or tornado
	if (bStorm && bSeaActive)
	{
		float fWindAttack = 1.0 - abs(fWindDotShip);
		
		float fDamageMultiply = fStormProfessional * Bring2Range(0.25, 1.0, 0.0, 1.0, fWindAttack) * isEquippedArtefactUse(rCharacter, "talisman2", 1.0, 0.2);

		// hull damage
		float fDamageHP = (fBaseShipHP / 100.0) * 1.1;
		Ship_ApplyHullHitpoints(rCharacter, fDamageMultiply * fDamageHP, KILL_BY_TOUCH, -1);

		// sails damage
		switch (MakeInt(fSailState * 2.0))
		{
			case 0: MakeSailDmg(iCharacterIndex, fDamageMultiply * (fBaseSailHP / 100.0) * 0.15); break;
			case 1: MakeSailDmg(iCharacterIndex, fDamageMultiply * (fBaseSailHP / 100.0) * 0.55); break;
			case 2: MakeSailDmg(iCharacterIndex, fDamageMultiply * (fBaseSailHP / 100.0) * 1.1); break;
		}

		// experience
		float fExp = (1.0 - fWindAttack) * fDamageHP / (8 - GetCharacterShipClass(rCharacter)); // fDamageHP - это процент корпуса, для мановара слишком жирно
		fExp = fExp / 10;
  		if (!bDead)
        {
            Ship_AddCharacterExp(rCharacter, MakeInt(fExp));
			// boal -->
            if (IsCompanion(rCharacter))
            {
               AddCharacterExpToSkill(rCharacter, "Sailing", fExp);
               ChangeCrewExp(rCharacter, "Sailors", 0.5);
            }
            // boal <--
        }

		// rotate impulse
  		float fRotate = stf(rCharacter.Ship.Tornado.Rotate.y) + (frnd() * 0.08 - 0.04);  //fix boal
		if (fRotate > 0.01)
		{
			fRotate = 0.01;
		}
		if (fRotate < -0.01)
		{
			fRotate = -0.01;
		}

		rCharacter.Ship.Tornado.Rotate.y = fRotate;  //fix boal
		arCharShip.Impulse.Rotate.y = fRotate;
	}

	if (bTornado && bSeaActive)
	{
		float fTornadoDistance = GetDistance2D(stf(Tornado.x), stf(Tornado.z), stf(arCharShip.Pos.x), stf(arCharShip.Pos.z));
		float fTornadoDamageMultiply = fStormProfessional * Bring2Range(1.0, 0.0, 0.0, 100.0, fTornadoDistance) * isEquippedArtefactUse(rCharacter, "talisman2", 1.0, 0.2);

		// hull damage
		Ship_ApplyHullHitpoints(rCharacter, fTornadoDamageMultiply * (fBaseShipHP / 100.0) * 8.5, KILL_BY_TOUCH, -1);

		// sails damage
		switch (MakeInt(fSailState * 2.0))
		{
			case 0: 
				MakeSailDmg(iCharacterIndex, fTornadoDamageMultiply * (fBaseSailHP / 100.0) * 1.5);
			break;
			case 1: 
				MakeSailDmg(iCharacterIndex, fTornadoDamageMultiply * (fBaseSailHP / 100.0) * 4.5); 
			break;
			case 2: 
				MakeSailDmg(iCharacterIndex, fTornadoDamageMultiply * (fBaseSailHP / 100.0) * 8.5); 
			break;
		}
	}
	
	// Expirience log section
	if (iCharacterIndex == nMainCharacterIndex && bSeaActive)
	{
		fSeaExpTimer = fSeaExpTimer + 1.0;
		if (fSeaExpTimer >= 15.0 && bStorm)
		{
			if (!bDead)
			{ 
				//Ship_PrintExp(MakeInt(fSeaExp));
			}

			fSeaExpTimer = 0.0;
			fSeaExp = 0.0;
		}
	}

	// Recalculate Cargo Load if need
	if (CheckAttribute(rCharacter, "Ship.Cargo.RecalculateCargoLoad") && sti(rCharacter.Ship.Cargo.RecalculateCargoLoad))
	{
		if (rand(5) == 1)  // оптимизация, сильные тормоза
		{
			RecalculateCargoLoad(rCharacter);
			rCharacter.Ship.Cargo.RecalculateCargoLoad = 0;
		}
	}
    //  to_do не было в ПКМ -->
	if (bSeaLoaded && CheckAttribute(rCharacter, "SeaAI.Task.Target"))
	{
		if(sti(rCharacter.SeaAI.Task.Target) > 0)
		{
			ref rTargetCharacter = GetCharacter(sti(rCharacter.SeaAI.Task.Target));
			bool bSkipTarget = false;
			if(!CheckAttribute(rTargetCharacter, "location"))
			{
				bSkipTarget = true;
			}
			if(rTargetCharacter.location == "none")
			{
				bSkipTarget = true;
			}
			if(rTargetCharacter.location != rCharacter.location)
			{
				bSkipTarget = true;
			}
			if (!bSkipTarget)
			{
				float fDistance = Ship_GetDistance2D(rCharacter, rTargetCharacter);
				float fEnemyLeadership = stf(rTargetCharacter.TmpSkill.Leadership); 
				float fEnemyFencing = stf(rTargetCharacter.TmpSkill.Fencing); 
				float fEnemyCrewFencing = (0.1 + fEnemyLeadership + fEnemyFencing * stf(rCharacter.Ship.Crew.Quantity));
				float fOurLeadership = stf(rCharacter.TmpSkill.Leadership); 
				float fOurFencing = stf(rCharacter.TmpSkill.Fencing);
				float fOurCrewFencing = (0.1 + fOurLeadership + fOurFencing * stf(rTargetCharacter.Ship.Crew.Quantity));
				float fRatio = fEnemyCrewFencing / fOurCrewFencing;
				if (sti(rCharacter.nation) == PIRATE) 
				{ 
					fRatio = fRatio * 1.6; 
				}
				if (sti(rCharacter.rank) > sti(rTargetCharacter.rank)) 
				{ 
					fRatio = fRatio * 1.2; 
				}
				
				if (fRatio > 1.2 && CheckAttribute(rCharacter, "Tmp.fShipSpeed") && CheckAttribute(rTargetCharacter, "Tmp.fShipSpeed") && stf(rCharacter.Tmp.fShipSpeed) > (stf(rTargetCharacter.Tmp.fShipSpeed) / 1.5))
				{
					//ref rTargetCharacter = GetCharacter(sti(rCharacter.SeaAI.Task.Target));
					if(GetRelation(sti(rCharacter.index), sti(rTargetCharacter.index)) == RELATION_ENEMY)
					{
						Ship_SetTaskAbordage(SECONDARY_TASK, sti(rCharacter.index), sti(rTargetCharacter.index)); // fix PRIMARY_TASK
						rCharacter.Ship_SetTaskAbordage = true; // запомним, чтоб не сбивать
					}
				}
				else
				{
					DeleteAttribute(rCharacter, "Ship_SetTaskAbordage");
				}

				if (sti(rCharacter.SeaAI.Task) == AITASK_RUNAWAY)
				{
					/*Ship_SetSailState(sti(rCharacter.index), 1);

					//проверяем дистанцию и дальность стрельбы орудий противника
					//проверяем нашу скорость и скорость противника
					//делаем чек на лидершип
					//проверяем мораль команды
					//если набираем 2 или больше очков - выкидываем груз за борт.
					//выключаем фонари.
					Ship_SetLightsOff(rCharacter, 15.0, true, true, false);

					ref rCannon = GetCannonByType(sti(rTargetCharacter.Ship.Cannons.Type));
					float TargetRange = stf(rCannon.FireRange);
					int isDropGoods = 0;

					if(fDistance <= TargetRange)
					{
						isDropGoods = isDropGoods + 1;
					}
					
					float fOurSpeed = FindShipSpeed(rCharacter);
					float fEnemySpeed = FindShipSpeed(rTargetCharacter);

					if(fOurSpeed <= fEnemySpeed)
					{
						isDropGoods = isDropGoods + 1;
					}

					if(fOurLeadership < rand(12))
					{
						isDropGoods = isDropGoods + 1;
					}

					float fOurMorale = GetCharacterCrewMorale(rCharacter);
					if(fOurMorale < rand(99))
					{
						isDropGoods = isDropGoods + 1;
					}

					if(isDropGoods > 2)
					*/
					// бешенная оптимизация, если кто-то убегает -->
					Ship_SetSailState(sti(rCharacter.index), 1);  // to_do нужно проверять, может довольно одного раза или в ядре будет дурить
					if (sti(rCharacter.Ship.Lights) == 1)
					{
						Ship_SetLightsOff(rCharacter, 15.0, true, true, false);
					}
					if (sti(rCharacter.Ship.SP) > 50 && rand(100) > 80)  // не выкидывать, если не убежать, а то нет смысла брать приз
					{
						PostEvent(SHIP_DROP_GOOD, 1000, "a", rCharacter);
					}
					// сброс мины 09.07.07 boal -->
					if (sti(rCharacter.Ship.SP) < 60 && GetCargoGoods(rCharacter, GOOD_POWDER) >= MINE_POWDER*2 && rand(39) == 5)
					{
						SetMineFree(rCharacter, 1); 
					}
					// сброс мины <--
					// бешенная оптимизация, если кто-то убегает <--
				}
		        else
		        {
					if (sti(rCharacter.SeaAI.Task) == AITASK_ABORDAGE)
					{
						if (GetRelation(sti(rCharacter.index), sti(rTargetCharacter.index)) == RELATION_ENEMY)
						{
							if(LAi_IsDead(rCharacter) == false && LAi_IsDead(rTargetCharacter) == false)
							{
								if (sti(rTargetCharacter.index) == nMainCharacterIndex)
								{
									float fCharacterGrappling = stf(rCharacter.TmpSkill.Grappling);
									float fCharacterGrapplingPerk  = Ship_CalcGrapplingPerk(rCharacter);
									float fCharacterDistance = Ship_CalcMaxAbordageDistance(fCharacterGrappling, fCharacterGrapplingPerk);
									float fCharacterAngle = Ship_CalcMaxAbordageAngle(fCharacterGrappling);
									float fCharacterSpeed = Ship_CalcMaxAbordageSpeed(fCharacterGrappling);
		
									float fAng = 0.0;
									float fRelativeSpeed = stf(arCharShip.Speed.z);
		
									aref	arUpdate;
									makearef(arUpdate, rCharacter.SeaAI.Update);
									aref aShips;
									makearef(aShips, arUpdate.Ships);
									int iShipsNum = GetAttributesNum(aShips);
									for (int i=0; i<iShipsNum; i++)
									{
										aref aShip = GetAttributeN(aShips, i);
										ref rShipCharacter = GetCharacter(sti(aShip.idx)); 
										if(rShipCharacter.id == rTargetCharacter.id)
										{
											fRelativeSpeed = stf(aShip.RelativeSpeed);
											fAng = stf(aShip.d_ay);
										}
									}
									float fEnemyBoxSizeX = stf(rTargetCharacter.Ship.BoxSize.x) / 2.0;
									float fCharacterBoxSizeX = stf(rCharacter.Ship.BoxSize.x) / 2.0;
									float fAbordageDistance = fDistance - fEnemyBoxSizeX - fCharacterBoxSizeX;
							
									if (fAbordageDistance < fCharacterDistance && fAng < fCharacterAngle && fRelativeSpeed < fCharacterSpeed)
									{
										/*if (sti(rTargetCharacter.index) != nMainCharacterIndex)
										{
											CalculateAbordage(rCharacter);
										}
										else  */ // код К3 пошел лесом, тк иначе случаи захвата очень редки
										//if (sti(rTargetCharacter.index) == nMainCharacterIndex)
										//{
										if (fRatio > 1.2)
										{
											iAbordageShipEnemyCharacter = sti(rCharacter.index);
											Sea_AbordageLoad(SHIP_ABORDAGE, false);
										}
										else
										{
											if (stf(rCharacter.ship.hp) > (stf(rTargetCharacter.ship.hp) / 2) || GetCrewQuantity(rCharacter) > GetCrewQuantity(rTargetCharacter)) //boal fix
											{
												Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rTargetCharacter.index));   //fix
											}
											else
											{
												Ship_SetTaskRunaway(SECONDARY_TASK,sti(rCharacter.index), sti(rCharacter.SeaAI.Task.Target));  //fix
											}
										}
										//}
									}
								} // if ГГ
							}
						}
					}
				} // else
			}
		}
	}
	//  to_do <--
	// start random sounds :: SAILS
	if (rand(40) <= fSailState * 5.0) { Ship_PlaySound3DComplex(rCharacter, "sails_ambient", fSailState * 0.5, 0.0, 0.0, 0.5 + frnd() * 0.0); }

	// start random sounds :: SHIPS
	if (rand(2) == 1) { Ship_PlaySound3DComplex(rCharacter, "squeak_sea"+sSeaSoundPostfix, 0.9, frnd() * 1.2 - 0.6, 0.0, frnd() * 1.6 - 0.8); }
}

void Ship_SailsMoveSound()
{
	aref arCharacter = GetEventData();
	bool bMove = GetEventData();

	// update sounds :: SAILS - moving
	if (CheckAttribute(arCharacter, "Ship.Sounds") && sti(arCharacter.Ship.Sounds.SailsID) > 0) 
		{ Sound_SetVolume(sti(arCharacter.Ship.Sounds.SailsID), 0.75 * bMove); }
}

void Ship_PrintExp(int iExp)
{
	if (iExp <= 0) { return; }

	object oRes;
	string sExpQuantity = iExp;
	string sExpString = LanguageConvertString(iSeaSectionLang, "sea_exp_add");

	Event(PARSE_STRING, "asls", &oRes, sExpString, 1, sExpQuantity);

	Log_SetStringToLog(oRes.Str);
}

void Ship_TornadoDamage()
{
	float fTime = GetEventData();
	
	Tornado.x = GetEventData();
	Tornado.z = GetEventData();
}

void Ship_UpdateTmpSkills(ref rCharacter)
{
	///// с оптимизацией
	if (!CheckAttribute(rCharacter, "TmpSkillRecall") || sti(rCharacter.TmpSkillRecall) <= 0)
    {
        rCharacter.TmpSkill = "";

    	aref aTmpSkill; makearef(aTmpSkill, rCharacter.TmpSkill);

    	// calc skills for speed optimization
    	//aTmpSkill.Commerce = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_COMMERCE)) / SKILL_MAX;
    	aTmpSkill.Leadership = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_LEADERSHIP)) / SKILL_MAX;
    	aTmpSkill.Sneak     = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_SNEAK)) / SKILL_MAX;
    	aTmpSkill.Defence   = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_DEFENCE)) / SKILL_MAX;
    	aTmpSkill.Grappling = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_GRAPPLING)) / SKILL_MAX;
    	aTmpSkill.Sailing   = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_SAILING)) / SKILL_MAX;
    	aTmpSkill.Repair    = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_REPAIR)) / SKILL_MAX;
    	aTmpSkill.Fencing   = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_FENCING)) / SKILL_MAX;
    	aTmpSkill.Accuracy  = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_ACCURACY)) / SKILL_MAX;
    	aTmpSkill.Cannons   = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_CANNONS)) / SKILL_MAX;

        if (sti(rCharacter.index) == GetMainCharacterIndex())
        {
            if (SeaCameras.Camera == "SeaDeckCamera")
        	{
        		aTmpSkill.Accuracy = Clampf(stf(aTmpSkill.Accuracy) + 0.15); // было 0.4
        	}
        	//rCharacter.SystemInfo.GlobalMinEnemyDistance = stf(rCharacter.SystemInfo.LastMainMinEnemyDistance); // fix выхода на карту
        	if (rand(10) == 3)//boal fix отношений, редко обновляется дял профилактики
        	{
        	    DoQuestCheckDelay("NationUpdate", 1.0);
        	}
    	}
    	rCharacter.TmpSkillRecall = 25 + rand(49); // разное время - размазанный пересчет, а то все скопом все равно //"60"; // считаем раз в минуту
    	// анализ погони
		if (GetNpcQuestPastTimeParam(rCharacter, "Add2SeaTime") > 55) // 2 дня Только у фантомов есть признак, остальные 0
		{
		    if (CheckAttribute(rCharacter, "SeaAI.Task") && rCharacter.SeaAI.Task != AITASK_RUNAWAY) // че б не было, все равно может гнать за ГГ
	        {
	        	Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(pchar.index));
	        }
		}
	}
	else
	{
        rCharacter.TmpSkillRecall = sti(rCharacter.TmpSkillRecall) - 1;

        if (sti(rCharacter.index) == GetMainCharacterIndex())
    	{
            rCharacter.TmpSkill.Accuracy  = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_ACCURACY)) / SKILL_MAX;
            if (SeaCameras.Camera == "SeaDeckCamera")
            {
                rCharacter.TmpSkill.Accuracy = Clampf(stf(rCharacter.TmpSkill.Accuracy) + 0.15);
            }
    	}
	}
}

void Ship_UpdatePerks()
{
	int iCharacterIndex = GetEventData();
	ref rCharacter = GetCharacter(iCharacterIndex);

	//Trace("Ship_UpdatePerks: rCharacter.id = " + rCharacter.id);
	if (sti(rCharacter.ship.type) == SHIP_NOTUSED) return; // fix для смены корабля
	rCharacter.TmpPerks = "";
	aref aTmpPerks; makearef(aTmpPerks, rCharacter.TmpPerks);

	// calc perks for speed optimization
	//if (!CheckAttribute(rCharacter, "TmpPerks.Turn")) {	rCharacter.TmpPerks.Turn = 0; }
      // to_do
	aTmpPerks.StormProfessional	  	    = CheckOfficersPerk(rCharacter, "StormProfessional");
    aTmpPerks.FastReload				= CheckOfficersPerk(rCharacter, "FastReload");
	aTmpPerks.ImmediateReload			= CheckOfficersPerk(rCharacter, "ImmediateReload");
	aTmpPerks.HullDamageUp			 	= CheckOfficersPerk(rCharacter, "HullDamageUp");
	aTmpPerks.CrewDamageUp				= CheckOfficersPerk(rCharacter, "CrewDamageUp");
	aTmpPerks.CriticalShoot				= CheckOfficersPerk(rCharacter, "CriticalShoot");
	aTmpPerks.LongRangeShoot			= CheckOfficersPerk(rCharacter, "LongRangeShoot");
	aTmpPerks.CannonProfessional		= CheckOfficersPerk(rCharacter, "CannonProfessional");
	aTmpPerks.LongRangeGrappling		= CheckOfficersPerk(rCharacter, "LongRangeGrappling");
	aTmpPerks.GrapplingProfessional		= CheckOfficersPerk(rCharacter, "GrapplingProfessional");
	aTmpPerks.BasicBattleState			= CheckOfficersPerk(rCharacter, "BasicBattleState");
	aTmpPerks.AdvancedBattleState		= CheckOfficersPerk(rCharacter, "AdvancedBattleState");
	aTmpPerks.ShipDefenseProfessional	= CheckOfficersPerk(rCharacter, "ShipDefenseProfessional");
	aTmpPerks.ShipSpeedUp				= CheckOfficersPerk(rCharacter, "ShipSpeedUp");
	aTmpPerks.ShipTurnRateUp			= CheckOfficersPerk(rCharacter, "ShipTurnRateUp");
	aTmpPerks.SailingProfessional		= CheckOfficersPerk(rCharacter, "SailingProfessional");
	aTmpPerks.LightRepair				= CheckOfficersPerk(rCharacter, "LightRepair");
	// update main character if rCharacter is companion   - это было, но зачем?? (boal)
	if (iCharacterIndex != nMainCharacterIndex && IsCompanion(rCharacter))
	{
		Event("eSwitchPerks", "l", nMainCharacterIndex);
	}
}

void Ship_Lightning()
{
	if (!bSeaActive) { return; }

	float x = GetEventData();
	float y = GetEventData();
	float z = GetEventData();

	for (int i=0; i<iNumShips; i++)
	{
		ref rCharacter = GetCharacter(Ships[i]);
		aref arShipChar; makearef(arShipChar, rCharacter.Ship);

		float sx = stf(arShipChar.Pos.x);
		float sy = stf(arShipChar.Pos.y);
		float sz = stf(arShipChar.Pos.z);
		float bx = stf(arShipChar.BoxSize.x);
		float by = stf(arShipChar.BoxSize.y);
		float bz = stf(arShipChar.BoxSize.z);
		float fDist = GetDistance2D(x, z, sx, sz);
		float fMinLightningDist = 20.0 + bz / 1.5;
		if (fDist < fMinLightningDist)
		{
			int iMinBoom = MakeInt(Bring2Range(5.0, 2.0, 1.0, 7.0, stf(GetCharacterShipClass(rCharacter))));
			float fCos = cos(stf(arShipChar.Ang.y));
			float fSin = sin(stf(arShipChar.Ang.y));
			int iMax = iMinBoom + rand(2);
			for (int k=0; k<iMax; k++)
			{
				float dx = 0.6 * bx * (frnd() - 0.5);
				float dz = 0.7 * bz * (frnd() - 0.5);
				RotateAroundY(&dx, &dz, fCos, fSin);
				Ship_Serious_Boom(sx + dx, sy + 0.1 * by * frnd(), sz + dz);
			}

			Ship_ApplyHullHitpoints(rCharacter, iMinBoom * 40.0, KILL_BY_TOUCH, -1);
			Ship_ApplyCrewHitpoints(rCharacter, MakeFloat(rand(3)));

			int iNumFirePlaces = 0;
			SendMessage(rCharacter, "le", MSG_SHIP_GET_NUM_FIRE_PLACES, &iNumFirePlaces);
			
			float fFirePlaces = Bring2Range(1.0, 0.1, 0.0, fMinLightningDist, fDist);

			float fCurr = 0.0;
			float fTest = (1.0 - fFirePlaces) * iNumFirePlaces;
			for (int j=0; j<iNumFirePlaces; j++)
			{
				fCurr = fCurr + 1.0;
				if (fCurr < fTest) { continue; }
	
				fCurr = 0.0;
				int iRandStartTime = rand(10000);
				float fTotalFireTime = Ship_GetTotalFireTime(rCharacter);

				PostEvent(SHIP_ACTIVATE_FIRE_PLACE, iRandStartTime, "ialsfl", rCharacter, rCharacter, j, "ship_onfire", fTotalFireTime, -1);
				PostEvent(SHIP_FIRE_DAMAGE, iRandStartTime, "lllf", Ships[i], -1, j, fTotalFireTime);
			}
		}
	}
}

// Create a new ship for character  to_do del нигде не юзается
void Ship_CreateForCharacter(ref rCharacter, int iShipType, string sShipName)
{
	DeleteAttribute(rCharacter, "Ship");

	rCharacter.Ship.Type = iShipType;
	rCharacter.Ship.Name = sShipName;

	rCharacter.Ship.Cannons.Borts = "";
	rCharacter.Ship.Cannons.Charge.Type = GOOD_BOMBS;
	rCharacter.Ship.Ang.y = 0.0;
	rCharacter.Ship.Pos.x = 0.0;
	rCharacter.Ship.Pos.y = 0.0;
	rCharacter.Ship.Pos.z = 0.0;
	rCharacter.Ship.Speed.z = 0.0;

	SetBaseShipData(rCharacter);
}

void Ship_ClearImpulseStrength(ref rCharacter)
{
	aref arImpulse; makearef(arImpulse, rCharacter.Ship.Impulse);
	arImpulse.Rotate.x = 0.0;
	arImpulse.Rotate.y = 0.0;
	arImpulse.Rotate.z = 0.0;
	arImpulse.Speed.x = 0.0;
	arImpulse.Speed.y = 0.0;
	arImpulse.Speed.z = 0.0;

	rCharacter.Ship.Tornado.Rotate.y = 0.0;  // fix boal
}

void Ship_PrepareShipForLocation(ref rCharacter)
{
	Ship_ClearImpulseStrength(rCharacter);
}
//  далее новые методы, не было в ПКМ
void Ship_LoadShip()
{
	int iCharacterIndex = GetEventData();
	
	ref rCharacter = GetCharacter(iCharacterIndex);
	
	//Dev_Trace("Ship_LoadShip = " + iCharacterIndex + " id = " + rCharacter.id + " ship.type = " + rCharacter.ship.type + " IsDead = " + LAi_IsDead(rCharacter));

	//if (sti(rCharacter.ship.type) != SHIP_NOTUSED && !LAi_IsDead(rCharacter))
	if (sti(rCharacter.ship.type) != SHIP_NOTUSED)
	{
		Event("eSwitchPerks", "l", iCharacterIndex);
		Ships[iNumShips] = iCharacterIndex;
		Event(SHIP_UPDATE_PARAMETERS, "lf", iCharacterIndex, stf(rCharacter.Ship.Speed.z));		// Parameters      после создания корабля
		iNumShips++;
	}
}

void Ship_LoadShipActivateFirePlace()
{
	int iOurCharacterIndex = GetEventData();
	int iBallCharacterIndex = GetEventData();
	int iFirePlaceIndex = GetEventData();
	float fTotalFireTime = GetEventData();

	Dev_Trace("iBallCharacterIndex = " + iBallCharacterIndex);
	int iStartTime = 500;

	PostEvent(SHIP_FIRE_DAMAGE, iStartTime, "lllf", iOurCharacterIndex, iBallCharacterIndex, iFirePlaceIndex, fTotalFireTime);
}

void SetTextureForShip(aref refBaseShip, aref rCharacter)
{
	if(!CheckAttribute(refBaseShip, "name"))
	{
		trace("SetTextureForShip(): ship " + refBaseShip.basetype + " have no name! NPCid = "+ rCharacter.id);
		if (MOD_BETTATESTMODE == "On") Log_Info("SetTextureForShip(): ship " + refBaseShip.basetype + " have no name! NPCid = "+ rCharacter.id);
		return;
	}

	string sPath = "ships\" + refBaseShip.name + "\";
	
	if(CheckAttribute(refBaseShip, "ship.Upgrades.hull"))  // boal 16/07/06 просто разные корпуса, без НПС
	{
		sPath = sPath + "hull" + refBaseShip.ship.upgrades.hull + "\";
	}
	
	SetTexturePath(0, sPath);
}

void DropGoodsToSea()
{
	aref rCharacter = GetEventData();

	ref rGood;
	string sGood;

	for (int i=GOOD_BALLS; i<GOOD_CULVERINE_36; i++)
	{
		sGood = Goods[i].name;
		if (CheckAttribute(&Goods[i], "DontDrop")) continue;

		if(CheckAttribute(rCharacter, "Ship.Cargo.Goods."+sGood))
		{
			int	iQuantity = sti(rCharacter.Ship.Cargo.Goods.(sGood));
			
			if(CheckAttribute(rCharacter, "Ship.Cargo.Goods."+sGood+".Lock")) continue; // залоченные товары не выкидывать !!!!! <-- ugeen fix
			
			if (iQuantity < 1 && rand(1) == 1) continue; 
			iQuantity = makeint(iQuantity/2 + rand(makeint(iQuantity/3)));   // выкидываем не все и не всегда, а то под ноль
			
			if (iQuantity < 1) continue; 
			
			RemoveCharacterGoods(rCharacter, i, iQuantity);

			iQuantity = iQuantity / sti(Goods[i].Units);

			if (iQuantity <= 1) 
			{ 
				continue; 
			}

			rCharacter.Ship.Cargo.Goods.(sGood) = 0;
            rCharacter.Ship.Cargo.RecalculateCargoLoad = true; // boal fix оптимизация
			//RecalculateCargoLoad(rCharacter);
            rCharacter.Tmp.SpeedRecall = 0; // чтоб пересчитались скорость и маневр
            
			if (CheckAttribute(&Goods[i], "Swim")) 
			{ 
				int iSwimQuantity = makeint(iQuantity/3 + rand(makeint(iQuantity/3)) + rand(makeint(iQuantity/3)));

				if(iSwimQuantity < 1)
				{
					iSwimQuantity = 1;
				}
				float fTime = stf(Goods[i].Swim.Time);
				string sModel = Goods[i].Swim.Model;

				//trace ("sModel is " + sModel);

				fTime = fTime + (frnd() - 0.5) * fTime / 2.0;

				AISeaGoods_AddGood(rCharacter, sGood, sModel, fTime * 60.0, iSwimQuantity);
			}
			return;
		}
	}
}

int Ship_GetRunAwayPoint()
{
	aref arChar = GetEventData();
	float fX = GetEventData();
	float fZ = GetEventData();

	float fRadius = 10000.0;
	float fWindAngle = Whr_GetWindAngle();

	arChar.SeaAI.WindAngle = fWindAngle;
	arChar.SeaAI.RunAwayPnt.x = stf(arChar.Ship.Pos.x) + fRadius * sin(fWindAngle);
	arChar.SeaAI.RunAwayPnt.z = stf(arChar.Ship.Pos.z) + fRadius * cos(fWindAngle);

	return 0;
}

// boal -->
string GetShipSexWord(string _type, string _man, string _woman)
{
    if (_type == "WarTartane" || 
	    _type == "Schooner"   || 
		_type == "Schooner_W" ||
		_type == "Caravel"    || 
		_type == "Shnyava"    || 
		_type == "Caracca"    || 
		_type == "Brigantine" ||
		_type == "XebekVML")
    {
        return _woman;
    }
    else
    {
        return _man;
    }
}
// boal 08.08.06 метод пересчета орудий на корабле  - доработал ядро
void Ship_ResearchCannons(ref aCharacter)
{
	if (bSeaLoaded)
	{
		SendMessage(&AISea, "la", AI_MESSAGE_RESEARCH_CANNONS, aCharacter);
		RefreshBattleInterface();
		Ship_ChangeCharge(aCharacter, sti(aCharacter.Ship.Cannons.Charge.Type));
	}
}
// boal 20.08.06 перерисовка флага -->
void Ship_FlagRefresh(ref rCharacter)
{
    if (bSeaLoaded)
	{
		SendMessage(rCharacter, "l", MSG_SHIP_FLAG_REFRESH);
	}
}

void EmptyFantom_DropGoodsToSea(ref rChar, int iFantomType)
{
	float fTime;
	string sGood, sModel;
	int iQty;
	if(iFantomType == ENCOUNTER_TYPE_BARREL)
	{	
		int irand = drand(100);
		if(irand > 92) // делаем бум
		{
			AISeaGoods_AddGood_Special(rChar, "powder1", "barrel_treasure", 1500.0, 1); // нарвались на беспризорную мину
		}
		else
		{
			if(irand < 40) 
			{
				for (int i=GOOD_FOOD; i<=GOOD_OIL; i++)
				{
					sGood = Goods[i].name;
					if (rand(3) > 1) continue; 
					if (CheckAttribute(&Goods[i], "Swim")) 
					{
						iQty = rand(15) + rand(10) + 5; 
						fTime = stf(Goods[i].Swim.Time);
						sModel = Goods[i].Swim.Model;
						fTime = fTime + (frnd() - 0.5) * fTime / 2.0;

						AISeaGoods_AddGood_Special(rChar, sGood, sModel, fTime * 60.0, iQty);
					}	
				}
			}		
			AISeaGoods_AddGood_Special(rChar, "barrel_treasure", "barrel_treasure", 1500.0, 1);			
		}	
	}
	if(iFantomType == ENCOUNTER_TYPE_BOAT)
	{
		AISeaGoods_AddGood_Special(rChar, "unknown_boat", "lo_boat", 1500.0, 1);
	}
	SendMessage(&AISea, "la", AI_MESSAGE_CHARACTER_DEAD, rChar);
}

void Ship_DoFakeFire(ref rChar, string sBort, float fRandTime)
{
	SendMessage(rChar, "lsf", MSG_SHIP_DO_FAKE_FIRE, sBort, fRandTime);
}

void Ship_EventFakeFire()
{
	float fX 	= GetEventData();
	float fY 	= GetEventData();
	float fZ 	= GetEventData();
	float fAY 	= GetEventData();
	
	CreateParticleSystem("cancloud_fire", fX, fY, fZ, 0.0, fAY, 0.0, 5);
	Play3DSound("cannon_fire", fX, fY, fZ);
}

void Ship_SetTechnique(ref rCharacter, string sTech)
{
	SendMessage(rCharacter, "ls", MSG_MODEL_SET_TECHNIQUE, sTech);
}

void Ship_SetGhostShip(ref rCharacter, string sTech)
{
	Ship_SetTechnique(rCharacter, sTech);
	
	LayerDelObject(sCurrentSeaRealize, rCharacter);
	LayerAddObject(sCurrentSeaRealize, rCharacter, 100000);

//	Ship_SetRiggingAlpha(rCharacter,128);
}
/*
void Ship_SetRiggingAlpha(ref rCharacter, int alpha)
{
	aref arVant;
	if( FindClass(&arVant,"Vant") ) {
		SendMessage(arVant,"lil",40400,rCharacter,alpha);
		LayerDelObject(sCurrentSeaRealize, arVant);
		LayerAddObject(sCurrentSeaRealize, arVant, 100001);
	}

	aref arRope;
	if( FindClass(&arRope,"Rope") ) {
		SendMessage(arRope,"lil",40400,rCharacter,alpha);
		LayerDelObject(sCurrentSeaRealize, arRope);
		LayerAddObject(sCurrentSeaRealize, arRope, 100001);
	}

	aref arSail;
	if( FindClass(&arSail,"Sail") ) {
		SendMessage(arSail,"lil",40400,rCharacter,alpha);
		LayerDelObject(sCurrentSeaRealize, arSail);
		LayerAddObject(sCurrentSeaRealize, arSail, 100001);
	}
}
*/
