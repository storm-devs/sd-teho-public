#define MINE_POWDER          200 // 07.07.07 мины

object	AISeaGoods;

void DeleteSeaGoodsEnvironment()
{
	DeleteClass(&AISeaGoods);

	DelEventHandler(SHIP_DEAD, "AISeaGoods_ShipDead");
}

void CreateSeaGoodsEnvironment()
{
	CreateEntity(&AISeaGoods, "AISeaGoods");
	
	LayerAddObject(SEA_EXECUTE, &AISeaGoods, -1);
	LayerAddObject(SEA_REALIZE, &AISeaGoods, 65532);

	SetEventHandler(SHIP_DEAD, "AISeaGoods_ShipDead", 0);
	SetEventHandler(SHIP_EAT_SWIM_GOOD, "AISeaGoods_ShipEatGood", 0);

	AISeaGoods.ModelsPath = "SwimGoods";
	AISeaGoods.DeleteGoodAnyway = false;
	AISeaGoods.DistanceMultiply = 0.5;
}

void AISeaGoods_ShipDead()
{
	ref rCharacter = GetCharacter(GetEventData());

	aref aGoods; makearef(aGoods, rCharacter.Ship.Cargo.Goods);
	int iNumGoods;
	iNumGoods = GetAttributesNum(aGoods); // оптимизация
	for (int i=0; i<iNumGoods; i++)
	{
		aref aGood = GetAttributeN(aGoods, i);
		int	iQuantity = sti(GetAttributeValue(aGood));
		ref	rGood = GetGoodByID(GetAttributeName(aGood));

		if (!CheckAttribute(rGood, "Swim")) { continue; }
		
		iQuantity = iQuantity / sti(rGood.Units);
		if (iQuantity <= 1) { continue; }

		if (rand(100) > 95) { continue; }

		int iSwimQuantity = 0; 
		iSwimQuantity = MakeInt(1 + iQuantity / 3 + rand(MakeInt(iQuantity / 2)));
		
		float fTime = stf(rGood.Swim.Time);
		string sModel = rGood.Swim.Model;

		fTime = fTime + (frnd() - 0.5) * fTime / 2.0;

		if (rand(1) == 0 && iSwimQuantity >= 2)
		{
			AISeaGoods_AddGood(rCharacter, GetAttributeName(aGood), sModel, fTime * 60.0, iSwimQuantity);
		}
		else
		{
			AISeaGoods_AddGood(rCharacter, GetAttributeName(aGood), sModel, fTime * 60.0, makeint(iSwimQuantity / 2));
			AISeaGoods_AddGood(rCharacter, GetAttributeName(aGood), sModel, fTime * 60.0, makeint(iSwimQuantity / 2)); // две бочки на один товар
		}
	}
}

void AISeaGoods_AddGood(ref rCharacter, string sGood, string sModel, float fTime, int iQuantity)
{
	if (!bSeaActive) return;

	//Trace("Add good : " + sGood + ", rCharacter.id = " + rCharacter.id + ", iQuantity = " + iQuantity);

	// calculate random position
		float fAng = stf(rCharacter.Ship.Ang.y) + PI + (frnd() - 0.5) * PI;
		float fDist = stf(rCharacter.Ship.BoxSize.z) / 2.0 + frnd() * 10.0;
		//float x = (frnd() - 0.5) * 20.0;
		//float z = (frnd() - 0.5) * 40.0;
		//RotateAroundY(&x, &z, cos(fAng), sin(fAng));

	AISeaGoods.Good = sGood;
	AISeaGoods.Pos.x = stf(rCharacter.Ship.Pos.x) + fDist * sin(fAng);
	AISeaGoods.Pos.z = stf(rCharacter.Ship.Pos.z) + fDist * cos(fAng);
	AISeaGoods.CharIndex = rCharacter.Index;
	AISeaGoods.Time = fTime;
	AISeaGoods.Quantity = iQuantity;
	AISeaGoods.Model = sModel;
	AISeaGoods.Add = "";
}

// ugeen --> выкидываем либо бочку со спецпредметом либо шлюпку с кораблекрушенцем
void AISeaGoods_AddGood_Special(ref rCharacter, string sGood, string sModel, float fTime, int iQuantity)
{
	if (!bSeaActive) return;
	
	float fAng = stf(pchar.Ship.Ang.y) + PI + (frnd() - 0.5) * PI;
	float fDist = stf(pchar.Ship.BoxSize.z) / 2.0 + frnd() * 10.0 + 20.0 + makefloat(rand(70));
	
	AISeaGoods.Good = sGood;
	AISeaGoods.Pos.x = stf(pchar.Ship.Pos.x) + fDist * sin(fAng);
	AISeaGoods.Pos.z = stf(pchar.Ship.Pos.z) + fDist * cos(fAng);
	AISeaGoods.CharIndex = rCharacter.Index;
	AISeaGoods.Time = fTime;
	AISeaGoods.Quantity = iQuantity;
	AISeaGoods.Model = sModel;
	AISeaGoods.Add = "";
}
// <-- ugeen

bool AISeaGoods_ShipEatGood()
{
	object oRes;

	int iCharacterIndex = GetEventData();
	int iGoodCharacterIndex = GetEventData();  // с кого товар
	string sGood = GetEventData();
	int iQuantity = GetEventData();

	ref rCharacter = GetCharacter(iCharacterIndex);
	
	if (LAi_IsDead(rCharacter)) 
	{
		return false;
	}
	
	switch (sGood)
	{
		case "boat":   //homo 22/06/07 если подобрали шлюпку и ГГ
			if (iCharacterIndex == sti(pchar.index))
			{
				pchar.GenQuest.Survive_In_SeaOfficerIdx = iGoodCharacterIndex;
	            DoQuestCheckDelay("Survive_In_SeaOfficer", 1.0);
	            return true;
			}
			else
			{
				DeleteAttribute(Pchar, "GenQuest.Survive_In_SeaOfficerIdx");
				return true;
			}
		break;
		
		case "enemy_boat":   //homo 22/06/07 если подобрали шлюпку
	        if (iCharacterIndex == sti(pchar.index))
			{
				pchar.GenQuest.Survive_In_SeaPrisonerIdx = iGoodCharacterIndex;
	            DoQuestCheckDelay("Survive_In_SeaPrisoner", 1.0);
	            return true;
			}
			else
			{
				return true;
			}
		break;
		
		case "unknown_boat":
			if (iCharacterIndex == sti(pchar.index))
			{
				Log_TestInfo("Picked up the boat from the shipwrecked");
				Achievment_SetStat(pchar, 60, 1);
				pchar.GenQuest.Survive_In_SeaPrisonerIdx = iGoodCharacterIndex;
				DoQuestCheckDelay("Survive_In_SeaPrisoner", 1.0);
			}	
			return true;
		break;
		// мины 07.07.07
		case "powder1":
		    MakeMineBoom(iCharacterIndex, iGoodCharacterIndex, 600.0);
			return true;
		break;
		
		case "powder2":
		    MakeMineBoom(iCharacterIndex, iGoodCharacterIndex, 1000.0);
			return true;
		break;
		
		case "powder3":
		    MakeMineBoom(iCharacterIndex, iGoodCharacterIndex, 1500.0);
			return true;
		break;
		
		case "barrel_treasure":
			if (iCharacterIndex == sti(pchar.index))
			{
				Log_TestInfo("Picked up a barrel with unknown contents");
				Achievment_SetStat(pchar, 59, 1);
				DoQuestCheckDelay("Get_TreasureBarrel", 1.0);
				return true;
			}
			else
			{
				return true;
			}	
		break;
    }

	if (iGoodCharacterIndex == iCharacterIndex) 
	{
		return false;
	}

	//trace("character " + rCharacter.id + " eat good");

	ref rShip = GetRealShip(sti(rCharacter.Ship.Type));
	int iGood = FindGood(sGood);

	ref rGood = &Goods[iGood];

	//int iLoad = GetCargoLoad(rCharacter);
	//int iCapacity = sti(rShip.Capacity);
	int iGoodWeight = sti(rGood.Weight);
	int iGoodUnits = sti(rGood.Units);

	int iMaxGoodAllow = GetCharacterFreeSpace(rCharacter, iGood);
	//int iMaxGoodAllow = (iCapacity - iLoad) / iGoodWeight;

	/*if(iCapacity < iGoodWeight)
	{
		return false;
	}
	*/

	if(iMaxGoodAllow == 0)
	{
		return false;
	}

	string sGoodName = LanguageConvertString(iSeaSectionLang, "seg_" + sGood);

	if (iMaxGoodAllow == 0)
	{
		string sShipCantGotGood = LanguageConvertString(iSeaSectionLang, "Ship_cant_got_good");
		Event(PARSE_STRING, "asls", &oRes, sShipCantGotGood, 1, sGoodName);
		Log_SetStringToLog(oRes.Str);
		return false;
	}

	if (iQuantity > iMaxGoodAllow) 
	{
		iQuantity = iMaxGoodAllow;
	}

	if (iCharacterIndex == nMainCharacterIndex)
	{
        PlaySound("INTERFACE\_Gotcha.wav"); // boal
		string sGoodQuantity = iQuantity * iGoodWeight;
		string sShipGotGood = LanguageConvertString(iSeaSectionLang, "Ship_got_good");
		Event(PARSE_STRING, "aslss", &oRes, sShipGotGood, 2, sGoodQuantity, sGoodName);
		Log_SetStringToLog(oRes.Str);
	}

	iQuantity = iQuantity * iGoodUnits;

	AddCharacterGoods(rCharacter, iGood, iQuantity);
	
	return true;
}
// мины boal 07.07.07
void MakeMineBoom(int iCharacterIndex, int iGoodCharacterIndex, float damg)
{
    ref rCharacter = GetCharacter(iCharacterIndex);

    // если ГГ или компаньон пустили бочку и был мир
    if (isCompanion(GetCharacter(iGoodCharacterIndex)) && GetNationRelation2MainCharacter(sti(rCharacter.nation)) != RELATION_ENEMY)
    {
        if (!isCompanion(rCharacter) && !CheckAttribute(rCharacter, "Coastal_Captain")) // по своим можно палить таможня пофиг
        {
            Ship_NationAgressive(rCharacter, rCharacter);
            DoQuestCheckDelay("NationUpdate", 0.7);
        }
    }
    Ship_ApplyHullHitpoints(rCharacter, damg, KILL_BY_BALL, iGoodCharacterIndex);
    
    if (bBettaTestMode)  // дает вылет :(
    {
		int iRandStartTime = rand(1000);
		float fTotalFireTime = Ship_GetTotalFireTime(rCharacter);

		PostEvent(SHIP_ACTIVATE_FIRE_PLACE, iRandStartTime, "ialsfl", rCharacter, rCharacter, 0, "ship_onfire", fTotalFireTime, iGoodCharacterIndex);
		PostEvent(SHIP_FIRE_DAMAGE, iRandStartTime, "lllf", iCharacterIndex, iGoodCharacterIndex, 0, fTotalFireTime);
		//    PlaySound("Sea Battles\vzriv_pogreb_002.wav");
	}
	Ship_Detonate(rCharacter, false, false);
}

void SetMineFree(ref xi_refCharacter, int type)
{
    AISeaGoods_AddGood(xi_refCharacter, "powder" + type, "barrel", 600.0, 1);
    PlaySound("Ships\jakor_002.wav");
    RemoveCharacterGoods(xi_refCharacter, GOOD_POWDER, type * MINE_POWDER);
    xi_refCharacter.Tmp.SpeedRecall = 0;  // чтоб пересчитались скорость и маневр
	Achievment_SetStat(xi_refCharacter, 61, 1);
	if (!CheckAttribute(pchar, "questTemp.Sharlie.DelTerGuard") && pchar.location == "tortuga" && sti(xi_refCharacter.index) == GetMainCharacterIndex() && !bDisableMapEnter) Tortuga_ShipGuardAttack();
}