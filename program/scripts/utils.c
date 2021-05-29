#include "scripts\colony.c"
#include "scripts\food.c"
#include "scripts\time_events.c"
#include "scripts\Rumour_Init.c" // homo 23/06/06
#include "scripts\islandships.c"
#include "scripts\officers.c"
#include "scripts\companions.c"
#include "scripts\ShipsUtilites.c"
#include "scripts\Crew.c"
#include "scripts\bountyhunters.c"
#include "scripts\tavern.c"
#include "scripts\idioms.c"
#include "scripts\smuggling.c"
#include "scripts\PsHero.c" // navy
#include "scripts\duel.c" // navy
#include "scripts\MerchantOnMap.c" // homo 29/07/06
#include "scripts\Siege.c" // homo 09/09/06 Осады
#include "scripts\Treasure.c"  // boal 02.09.06 клады
#include "scripts\Other_Quests.c" // Warship 09.05.08 прочие квесты
#include "scripts\GenQuests.c" // Warship 16.05.08 генераторы
#include "scripts\CompanionTravel.c" // Warship 17.07.08 Методы для свободного плавания компаньонов
#include "scripts\GameModeCondition.c" // Warship. Обраобтка прерывания, выполняющегося в каждом фрейме
#include "scripts\GenQuests_common.c" // Ugeen 12.01.10 общие функции для генераторов

#define MAN 			0
#define WOMAN 			1

#define WITHOUT_SHIP 	0
#define WITH_SHIP 		1

#define WARRIOR 		0
#define CITIZEN 		1
#define TRADER 			2
#define BOSS			3
#define FORT_COMMANDER	4
#define BOUNTY_HUNTER	5
#define SHAMAN			6
#define SOLDIER			7
#define OFFICER			8

#define QUEST_NOT_ACCEPTED	0
#define QUEST_ACCEPTED		1
#define QUEST_COMPLETED		2

#define TRADER_MAX_MONEY	30000
#define TRADER_MIN_MONEY	15000
#define TRADER_NORM			15000

#define USURER_MAX_MONEY	120000
#define USURER_MIN_MONEY	80000
#define USURER_NORM			100000

#define CAP_MAX_MONEY		45000
#define CAP_MIN_MONEY		20000
#define CAP_NORM			25000

#define	USURER_MAX_DUBLONS	  150
#define USURER_MIN_DUBLONS	   50

void SetNames()
{
	for(int i = 1; i <MAX_CHARACTERS; i++)
	{
		if (!CheckAttribute(&Characters[i], "name") || Characters[i].name == "none")
		{
			SetRandomNameToCharacter(&Characters[i]);
		}
	}
}

void SetNationRelations()
{
    Nations_SetAllFriends();

	SetNationRelationBoth(ENGLAND, PIRATE, RELATION_ENEMY);
	SetNationRelationBoth(ENGLAND, FRANCE, RELATION_NEUTRAL);

	SetNationRelationBoth(HOLLAND, PIRATE, RELATION_ENEMY);
	SetNationRelationBoth(FRANCE, PIRATE, RELATION_ENEMY);

	SetNationRelationBoth(SPAIN, ENGLAND, RELATION_ENEMY);
    SetNationRelationBoth(SPAIN, PIRATE, RELATION_ENEMY);
    SetNationRelationBoth(SPAIN, FRANCE, RELATION_ENEMY);
    SetNationRelationBoth(SPAIN, HOLLAND, RELATION_NEUTRAL);

    SetNationRelationBoth(HOLLAND, ENGLAND, RELATION_ENEMY);
    SetNationRelationBoth(HOLLAND, FRANCE, RELATION_FRIEND);
    
	// ГГ отношения от нации
	pchar = GetMainCharacter();
	SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(sti(pchar.nation), ENGLAND));
	SetNationRelation2MainCharacter(FRANCE,  GetNationRelation(sti(pchar.nation), FRANCE));
	SetNationRelation2MainCharacter(SPAIN,   GetNationRelation(sti(pchar.nation), SPAIN));
	SetNationRelation2MainCharacter(PIRATE,  GetNationRelation(sti(pchar.nation), PIRATE));
    SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(sti(pchar.nation), HOLLAND));
}

// метод установки отношений по дипломату
void ChangeNationRelationFromRelationAgent(aref chr)
{
	int iNation = sti(chr.quest.relation);

    int iDays = rand(10) + 5;
	string sQuest = "Change_Relation_for_Nation_" + GetNationNameByType(iNation) + "_by_relation_agent_" + iDays;
	
	SetTimerCondition(sQuest, 0, 0, iDays, false);
	pchar.quest.(sQuest).function = "ChangeNationRelationFromRelationAgentComplete";
	pchar.quest.(sQuest).nation = iNation;
}

void ChangeNationRelationFromRelationAgentComplete(string sQuest)
{
	int iNation = sti(pchar.quest.(sQuest).nation);
    string sNation = "RelationAgentRate" + GetNationNameByType(iNation);
    
	SetNationRelation2MainCharacter(iNation, RELATION_NEUTRAL);
	ChangeCharacterNationReputation(pchar, iNation, sti(Pchar.GenQuest.(sNation)));
	sti(Pchar.GenQuest.(sNation)) = 0; // чтоб второй раз не было
	sNation = "RelationAgent" + GetNationNameByType(iNation);
    Pchar.GenQuest.(sNation) = false;
    
	if (CheckAttribute(pchar, "GenQuest."+(sNation)+".loyer"))
	{
		Log_Info("Albert Loxley has done his job.");
		DeleteAttribute(pchar, "GenQuest."+(sNation)+".loyer");
	}
	else Log_Info("A diplomat has done his job.");
}

void ChangeNationRelationFromFadeyComplete(string sQuest) 
{
	int iNation = sti(pchar.GenQuest.FadeyNation);
	int rate = sti(pchar.GenQuest.FadeyNation.Rate);
	int nowrate = abs(ChangeCharacterNationReputation(pchar, iNation, 0));
	
	if (ChangeCharacterNationReputation(pchar, iNation, 0) < 0)
	{
		if (nowrate <= 20)
		{
			SetNationRelation2MainCharacter(iNation, RELATION_NEUTRAL);
			if (rate <= nowrate) ChangeCharacterNationReputation(pchar, iNation, rate);
			else ChangeCharacterNationReputation(pchar, iNation, nowrate);
		}
		else ChangeCharacterNationReputation(pchar, iNation, 20);
	}
	else SetNationRelation2MainCharacter(iNation, RELATION_NEUTRAL);
	
	ref sld = characterFromId("Fadey");
	if (CheckAttribute(sld, "quest.relation")) DeleteAttribute(sld, "quest.relation");
	if (CheckAttribute(pchar, "GenQuest.FadeyNation")) DeleteAttribute(pchar, "GenQuest.FadeyNation");
	
	Log_Info("Fadey has done his job."); // patch-10
}

void ChangeNationRelationFromBenuaComplete(string sQuest) // 141012
{
	int iNation = sti(pchar.GenQuest.BenuaNation);
	int rate = sti(pchar.GenQuest.BenuaNation.Rate);
	int nowrate = abs(ChangeCharacterNationReputation(pchar, iNation, 0));
	
	if (ChangeCharacterNationReputation(pchar, iNation, 0) < 0)
	{
		if (nowrate <= 20)
		{
			SetNationRelation2MainCharacter(iNation, RELATION_NEUTRAL);
			if (rate <= nowrate) ChangeCharacterNationReputation(pchar, iNation, rate);
			else ChangeCharacterNationReputation(pchar, iNation, nowrate);
		}
		else ChangeCharacterNationReputation(pchar, iNation, 20);
	}
	else SetNationRelation2MainCharacter(iNation, RELATION_NEUTRAL);
	
	ref sld = characterFromId("Benua");
	if (CheckAttribute(sld, "quest.relation")) DeleteAttribute(sld, "quest.relation");
	if (CheckAttribute(pchar, "GenQuest.BenuaNation")) DeleteAttribute(pchar, "GenQuest.BenuaNation");
	
	Log_Info("Abbot Benoit has done his job."); // patch-10
}

int CalculateRelationSum(int iNation)
{
	string sNation = "RelationAgentRate" + GetNationNameByType(iNation);
	Pchar.GenQuest.(sNation) = abs(ChangeCharacterNationReputation(pchar, iNation, 0))
	int iSumm = sti(Pchar.GenQuest.(sNation)) * 1500 +  makeint(stf(Pchar.rank)/stf(Pchar.reputation.nobility)*100000);

	//iSumm = iSumm * (1.0 + (0.1 * MOD_SKILL_ENEMY_RATE));
	
	return iSumm;
}

int CalculateRelationLoyerSum(int iNation) // Jason: сумма по адвокату Локсли
{
	string sNation = "RelationAgentRate" + GetNationNameByType(iNation);
	Pchar.GenQuest.(sNation) = abs(ChangeCharacterNationReputation(pchar, iNation, 0));
	int iSumm = sti(Pchar.GenQuest.(sNation)) * 1200 + makeint(stf(Pchar.rank)/stf(Pchar.reputation.nobility)*80000);
	
	return iSumm;
}
// to_do del нигде не используется
bool CreateParticleSystemOnLocator(string _location_id, string _locatorName, string _particleName)
{
	aref locator;
	if (!FindLocator(_location_id, _locatorName, &locator, true))
		return false;

	CreateParticleSystemX(_particleName,stf(locator.x),stf(locator.y),stf(locator.z), stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z),0);
	return true;
}

void GenerateMaps(aref ch, int iProbability1, int iProbability2)
{
	int rank = sti(PChar.rank);
	
	if(rand(4) == 1) AddItems(ch, "map_bad", 1); 
	if(rand(6) == 1 && rank >= 10) AddItems(ch, "map_normal", 1); // patch-5
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_jam")) AddItems(ch, "map_jam", 1);
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_cayman")) AddItems(ch, "map_cayman", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_barbados")) AddItems(ch, "map_barbados", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_trinidad")) AddItems(ch, "map_trinidad", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_Curacao")) AddItems(ch, "map_Curacao", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_martiniqua")) AddItems(ch, "map_martiniqua", 1);
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_dominica")) AddItems(ch, "map_dominica", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_puerto")) AddItems(ch, "map_puerto", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_cuba")) AddItems(ch, "map_cuba", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_hisp")) AddItems(ch, "map_hisp", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_nevis")) AddItems(ch, "map_nevis", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_guad")) AddItems(ch, "map_guad", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_antigua")) AddItems(ch, "map_antigua", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_TORTUGA")) AddItems(ch, "map_TORTUGA", 1);
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_terks")) AddItems(ch, "map_terks", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_sm")) AddItems(ch, "map_sm", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_bermudas")) AddItems(ch, "map_bermudas", 1);
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_Pearl")) AddItems(ch, "map_Pearl", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_beliz")) AddItems(ch, "map_beliz", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_santa")) AddItems(ch, "map_santa", 1);
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_maine_1")) AddItems(ch, "map_maine_1", 1);
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_maine_2")) AddItems(ch, "map_maine_2", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_panama")) AddItems(ch, "map_panama", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_maracaibo")) AddItems(ch, "map_maracaibo", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_cumana")) AddItems(ch, "map_cumana", 1);
}

void GiveItemToTrader(aref ch)
{
	int 		i, j, irand;
	string 		itemID, merType;
	int 		rank = sti(PChar.rank); // makeint(pchar.rank) - и так было везде... Нет бы сразу переменную завести - это ведь быстрее будет в разы
	ref 		itm; 					// ref itm = ItemsFromID("map_LSC"); - тоже самое... Че за бред, заводить переденную внутри блока иф?
	
	DeleteAttribute(ch, "items");

	// boal зачем они в продаже?  ДЛЯ ОТЛАДКИ  -->
	if(bBettaTestMode)
	{
    	for(i = 0; i < ITEMS_QUANTITY; i++)
    	{
			itemID = Items[i].ID;
			irand = rand(2) + 1;			
			// Warship переделка
			if(IsGenerableItem(itemID)) // Уникальные предметы, которые сначало нужно генерить
			{
				GenerateAndAddItems(ch, itemID, irand);
				continue;
			}			
            AddItems(ch, itemID, irand);
    	}		
		return;
	}
	
	if(CheckAttribute(ch,"Merchant.type"))  merType = ch.Merchant.type;
	else 									merType = "veteran"; // если типа нет то продаем скобяные изделия
	// 170912 Jason убрал талисман-8
	
	switch (merType)
	{
		case "potion" 		: // лекарства и травы + обереги
			AddItems(ch, "mineral17", 	Rand(1) + 2);	
			AddItems(ch, "potion1", 	Rand(8) + 1);
			if (ch.id == "Merdok")
			{
				AddItems(ch, "potion2", drand(2)+1);
				AddItems(ch, "potion3", drand(2)+1);
				AddItems(ch, "potion4", drand(2)+1);
				AddItems(ch, "potion5", drand(2)+1);
			}
			else
			{
				irand = rand(12);
				if(irand == 1)
				{
					AddItems(ch,"potion2", Rand(3) + 1);
				}
				irand = rand(10);
				if(irand == 1)
				{
					AddItems(ch,"mineral27", 1);
				}
		
				irand = rand(8);
				if(irand == 1)
				{
					AddItems(ch, "potion3", Rand(3) + 1);
				}
		
				irand = rand(6);
				if(irand == 1)
				{
					AddItems(ch, "potion4", Rand(1) + 1);
				}
		
				irand = rand(3);
				if(irand == 1)
				{
					AddItems(ch, "potion5", Rand(5) + 1);
				}	
			}
			irand = rand(5);
			if(irand == 2)
			{
				AddItems(ch,"potionrum", Rand(3) + 2);
			}
			
			irand = rand(10); // пропишем тетра-гидро-каннабинолы :)
			if(irand == 0 ) AddItems(ch, "cannabis1", Rand(1) + 1);
			if(irand == 2 ) AddItems(ch, "cannabis2", Rand(1) + 1);
			if(irand == 4 ) AddItems(ch, "cannabis3", Rand(1) + 1);
			if(irand == 6 ) AddItems(ch, "cannabis4", Rand(1) + 1);
			if(irand == 8 ) AddItems(ch, "cannabis5", Rand(1) + 1);
			if(irand == 10) AddItems(ch, "cannabis6", Rand(1) + 1);
			// рецепты
			irand = drand(320); // 5% вероятности
			if(irand == 1 ) AddItems(ch, "recipe_potion2", 1);
			if(irand == 10 ) AddItems(ch, "recipe_potion3", 1);
			if(irand == 20 ) AddItems(ch, "recipe_berserker_potion", 1);
			if(irand == 40 ) AddItems(ch, "recipe_totem_01", 1);
			if(irand == 80 ) AddItems(ch, "recipe_totem_02", 1);
			if(irand == 100 ) AddItems(ch, "recipe_totem_03", 1);
			if(irand == 120) AddItems(ch, "recipe_totem_04", 1);
			if(irand == 150 ) AddItems(ch, "recipe_totem_05", 1);
			if(irand == 180 ) AddItems(ch, "recipe_totem_06", 1);
			if(irand == 210 ) AddItems(ch, "recipe_totem_07", 1);
			if(irand == 230 ) AddItems(ch, "recipe_totem_08", 1);
			if(irand == 250 ) AddItems(ch, "recipe_totem_09", 1);
			if(irand == 270 ) AddItems(ch, "recipe_totem_10", 1);
			if(irand == 290 ) AddItems(ch, "recipe_totem_11", 1);
			if(irand == 300 ) AddItems(ch, "recipe_totem_12", 1);
			if(irand == 320 ) AddItems(ch, "recipe_totem_13", 1);
		break;
		
		case "veteran" 		: // скобяные изделия
			AddItems(ch, "mineral1", 	Rand(3) + 2);	
			AddItems(ch, "mineral2", 	Rand(1) + 1);	
			
			irand = drand(5);
			if(irand == 1) AddItems(ch, "mineral3", 	Rand(4) + 5);
			if(irand == 2) AddItems(ch, "mineral5", 	Rand(1) + 1);
			
			irand = drand(6);
			if(irand == 3) AddItems(ch, "mineral6", 	Rand(2) + 1);
			if(irand == 4) AddItems(ch, "mineral7", 	Rand(2) + 1);				
			if(irand == 5) AddItems(ch, "mineral9", 	Rand(2) + 1);
			if(irand == 6) AddItems(ch, "mineral10", 	Rand(2) + 1);

			irand = drand(4);
			if(irand == 0) AddItems(ch, "mineral13", 	Rand(1) + 1);		
			if(irand == 1) AddItems(ch, "mineral15", 	Rand(1) + 1);
			if(irand == 2) AddItems(ch, "mineral16", 	Rand(1) + 1);
			
			irand = drand(8);
			if(irand == 1) AddItems(ch, "mineral18", 	Rand(1) + 1);
			if(irand == 8) AddItems(ch, "mineral19", 	Rand(1) + 1);
			if(irand == 5) AddItems(ch, "mineral20", 	Rand(1) + 1);
			
			irand = drand(9);
			if(irand == 9) AddItems(ch, "mineral21", 	Rand(1) + 1);
			if(irand == 7) AddItems(ch, "mineral22", 	Rand(5) + 2);
			if(irand == 5) AddItems(ch, "mineral23", 	Rand(12) + 3);
			if(irand == 3) AddItems(ch, "mineral24", 	Rand(1) + 1);
			
			irand = drand(15);
			if(irand == 15)AddItems(ch, "mineral25", 	Rand(1) + 2);
			if(irand == 5) AddItems(ch, "mineral26", 	Rand(1) + 3);
			if(irand == 7) AddItems(ch, "mineral33", 	Rand(1) + 1);
			if(irand == 9) AddItems(ch, "mineral35", 	1);
			
			// амулеты
			irand = drand(25); 
			if(irand == 1) AddItems(ch, "obereg_5", 1);
			if(irand == 15) AddItems(ch, "obereg_4", 1);
			if(irand == 25) AddItems(ch, "obereg_3", 1);
		break;
		
		case "armourer": // оружие и боеприпасы
			AddItems(ch, "bullet", 		Rand(20) + 10);	
			AddItems(ch, "grapeshot", 	Rand(5) + 5);    
			AddItems(ch, "gunpowder", 	Rand(10) + 5); // Warship. Порох
			// трубы
			irand = drand(10);
			if(irand == 1) AddItems(ch, "spyglass1", 1);
			irand = drand(15);
			if(irand == 1 && rank >=6) AddItems(ch, "spyglass2", 1); // fix 160912
			irand = drand(4);
			// пистоли
			if(irand == 1) AddItems(ch, "pistol1", Rand(2) + 1);
			if(rank >= 10 && rand(10) == 1)
			{
				if(irand == 1) AddItems(ch, "pistol2", Rand(1) + 1);
			}
			if(rank >= 5 && rand(7) == 1)
			{
				if(irand == 1) AddItems(ch, "pistol3", Rand(1) + 1);
			}
			// сабли
			irand = drand(3);
			if(irand == 1) GenerateAndAddItems(ch, "slave_01", Rand(2) + 1); 
			if(irand == 2) GenerateAndAddItems(ch, "slave_02", Rand(2) + 1); 
			if(irand == 3) GenerateAndAddItems(ch, "topor_05", 1);
			irand = drand(5);
			if(irand == 1 && rank >= 7) GenerateAndAddItems(ch, "topor_02", 1);
			if(rank >= 5)
			{
				irand = drand(6);
				if(irand == 1) GenerateAndAddItems(ch, "blade_03", 1);
				if(irand == 2) GenerateAndAddItems(ch, "blade_05", Rand(1) + 1);
				if(irand == 3) GenerateAndAddItems(ch, "blade_07", Rand(1) + 1);
				if(irand == 4) GenerateAndAddItems(ch, "blade_08", Rand(1) + 1);
				if(irand == 5) GenerateAndAddItems(ch, "blade_09", Rand(1) + 1);
			}
			// кирасы
			irand = drand(10);
			if (irand == 1 && rank >= 4) 	AddItems(ch, "cirass1", 1);
			if (irand == 5 && rank >= 6) 	AddItems(ch, "cirass5", 1);
			irand = drand(15);
			if (irand == 1 && rank >= 8) 	AddItems(ch, "cirass2", 1);
			if (irand == 7 && rank >= 10) 	AddItems(ch, "cirass6", 1);
			irand = drand(20);
			if (irand == 1 && rank >= 12) 	AddItems(ch, "cirass3", 1);
			if (irand == 8 && rank >= 14) 	AddItems(ch, "cirass7", 1);
			if(rank >= 7)
			{
				irand = drand(9);
				if(irand == 1) GenerateAndAddItems(ch, "blade_11", Rand(1) + 1);
				if(irand == 3) GenerateAndAddItems(ch, "blade_12", Rand(1) + 1);
				if(irand == 5) GenerateAndAddItems(ch, "blade_14", Rand(1) + 1);
			}
			// хорошие сабельки
			if(rank >= 10)
			{
				irand = drand(12);
				if(irand == 1) GenerateAndAddItems(ch, "blade_13", 1);
				if(irand == 4) GenerateAndAddItems(ch, "blade_04", 1);
				if(irand == 7) GenerateAndAddItems(ch, "blade_06", 1);
				if(irand == 10) GenerateAndAddItems(ch, "blade_10", 1);
				if(irand == 12) GenerateAndAddItems(ch, "blade_13", 1);
			}
			// приборы
			irand = drand(16);
			if(irand == 5 && rank >=5) AddItems(ch, "compass1", 1);
			if(irand == 1 && rank >=5) AddItems(ch, "sand_clock", 1);
			if(irand == 10 && rank >=7) AddItems(ch, "astrolab", 1);
			if(irand == 15 && rank >=7) AddItems(ch, "clock1", 1);
			// рецепты
			irand = drand(60); // 5% вероятности
			if(irand == 10 ) AddItems(ch, "recipe_powder_pellet", 1);
			if(irand == 35 ) AddItems(ch, "recipe_grenade", 1);
			if(irand == 60 ) AddItems(ch, "recipe_harpoon", 1);
			// амулеты
			irand = drand(30); 
			if(irand == 5) AddItems(ch, "obereg_1", 1);
			if(irand == 15) AddItems(ch, "obereg_2", 1);
			if(irand == 30) AddItems(ch, "obereg_6", 1);
			irand = drand(6);
			if(irand == 0) AddItems(ch, "Mineral15", drand(2)+1);
			if(irand == 3) AddItems(ch, "Mineral13", drand(2)+1);
			if(irand == 6) AddItems(ch, "Mineral30", drand(5)+1);
		break;

		case "monk" 		: //  амулеты+всякая мурня, карты убрал
			AddItems(ch, "Mineral3", drand(5)+1); // свечи всегда
			// прочие предметы
			irand = drand(10);
			if(irand == 1) AddItems(ch, "Mineral5", 1);
			irand = drand(5);
			if(irand == 1) AddItems(ch, "Mineral11", 1);
			irand = drand(12);
			if(irand == 1) AddItems(ch, "Mineral21", 1);
			irand = drand(7);
			if(irand == 1) AddItems(ch, "Mineral1", 1);
			irand = drand(4);
			if(irand == 1) AddItems(ch, "potionwine", drand(3));
			irand = drand(5);
			if(irand == 0) AddItems(ch, "jewelry45", drand(2)+1);
			if(irand == 1) AddItems(ch, "jewelry48", drand(2)+1);
			if(irand == 2) AddItems(ch, "jewelry46", drand(2)+1);
			if(irand == 3) AddItems(ch, "jewelry43", 1);
			if(irand == 4) AddItems(ch, "jewelry41", 1);
			if(irand == 5) AddItems(ch, "jewelry40", 1);
			irand = drand(3);
			if(irand == 1) AddItems(ch, "jewelry50", 1);
			if(irand == 2) AddItems(ch, "jewelry49", 1);
			if(irand == 3) AddItems(ch, "jewelry47", 1);
			// церковные амулеты
			irand = drand(15);
			if(irand == 1) AddItems(ch, "amulet_2", 1);
			if(irand == 3) AddItems(ch, "amulet_3", 1);
			if(irand == 6) AddItems(ch, "amulet_6", 1);
			if(irand == 0) AddItems(ch, "amulet_7", 1);
			if(irand == 15) AddItems(ch, "amulet_8", 1);
			if(irand == 9) AddItems(ch, "amulet_9", 1);
			if(irand == 12) AddItems(ch, "amulet_10", 1);
			irand = drand(10);
			if(irand == 1) AddItems(ch, "obereg_11", 1);
			if(irand == 5) AddItems(ch, "obereg_8", 1);
			if(irand == 10) AddItems(ch, "obereg_10", 1);
			irand = drand(40-GetCharacterSPECIALSimple(PChar, SPECIAL_L)*2);
			if(irand == 1) AddItems(ch, "obereg_7", 1);
			// рецепты
			irand = drand(55); // 5% вероятности
			if(irand == 1 ) AddItems(ch, "recipe_potion2", 1);
			if(irand == 30 ) AddItems(ch, "recipe_potion3", 1);
			if(irand == 55 ) AddItems(ch, "recipe_berserker_potion", 1);
			//GenerateMaps(ch, 35, 80);
		break;	
		
		case "indian" 		: // индейские артефакты
			AddItems(ch, "mineral4", 	Rand(2) + 1);
			AddItems(ch, "mineral11", 	Rand(4) + 7);
			AddItems(ch, "mineral12", 	Rand(3) + 7);		
			irand = rand(10);
			if(irand == 7) AddItems(ch, "mineral31", 	1);				
			irand = rand(10);
			if(irand == 1) AddItems(ch, "mineral14", 1);		
			irand = rand(10);
			if(irand == 5) AddItems(ch, "mineral33", 1);		
			irand = rand(10);
			if(irand == 1) AddItems(ch, "indian_1", 1);
			irand = rand(10);
			if(irand == 1) AddItems(ch, "indian_2", 1);
			irand = rand(40);
			if(irand == 1) AddItems(ch, "indian_3", 1);
			irand = rand(10);
			if(irand == 1) AddItems(ch, "indian_4", 1);
			irand = rand(10);
			if(irand == 1) AddItems(ch, "indian_5", 1);
			irand = rand(10);
			if(irand == 1) AddItems(ch, "indian_6", 1);
			irand = rand(40);
			if(irand == 1) AddItems(ch, "indian_7", 1);
			irand = rand(10);
			if(irand == 1) AddItems(ch, "indian_8", 1);
			irand = rand(10);
			if(irand == 1) AddItems(ch, "indian_9", 1);
			irand = rand(10);
			if(irand == 1) AddItems(ch, "indian_10", 1);
			irand = rand(10);
			if(irand == 1) AddItems(ch, "indian_11", 1);
		break;
		
		case "jeweller" 	:// ювелир
		
			AddItems(ch, "gold_dublon", Rand(USURER_MAX_DUBLONS - USURER_MIN_DUBLONS) + USURER_MIN_DUBLONS); // дублоны
			irand = rand(2);
			if(irand == 1) AddItems(ch, "chest_open", Rand(1) + 1); // пустые сундуки
			
			AddItems(ch, "jewelry1", Rand(4) + 1);
			AddItems(ch, "jewelry2", Rand(4) + 1);
			AddItems(ch, "jewelry3", Rand(4) + 1);
			AddItems(ch, "jewelry4", Rand(4) + 1);
			AddItems(ch, "jewelry5", Rand(4) + 1);
			AddItems(ch, "jewelry6", Rand(4) + 1);
			
			irand = rand(20);
			if(irand == 1) AddItems(ch, "jewelry7", 1);
			irand = rand(20);
			if(irand == 1) AddItems(ch, "jewelry8", 1);
			irand = rand(20);
			if(irand == 1) AddItems(ch, "jewelry9", 1);
			irand = rand(20);
			if(irand == 1) AddItems(ch, "jewelry10", 1);
			irand = rand(20);
			if(irand == 1) AddItems(ch, "jewelry11", 1);
			irand = rand(20);
			if(irand == 1) AddItems(ch, "jewelry12", 1);
			irand = rand(20);
			if(irand == 1) AddItems(ch, "jewelry13", 1);
			irand = rand(20);
			if(irand == 1) AddItems(ch, "jewelry14", 1);
			irand = rand(20);
			if(irand == 1) AddItems(ch, "jewelry15", 1);
			irand = rand(20);
			if(irand == 1) AddItems(ch, "jewelry16", 1);
			irand = rand(10);
			if(irand == 1) AddItems(ch, "jewelry17", Rand(4) + 1);
			irand = rand(10);
			if(irand == 1) AddItems(ch, "jewelry18", Rand(4) + 1);
			irand = rand(10);			
			if(irand == 1) AddItems(ch, "jewelry19", Rand(4) + 1);
			irand = rand(10);			
			if(irand == 1) AddItems(ch, "jewelry20", Rand(4) + 1);
			irand = rand(10);			
			if(irand == 1) AddItems(ch, "jewelry21", Rand(4) + 1);
			irand = rand(10);			
			if(irand == 1) AddItems(ch, "jewelry22", Rand(4) + 1);
			irand = rand(10);			
			if(irand == 1) AddItems(ch, "jewelry23", Rand(4) + 1);
		break;
		
		case "lightman": //Jason - смотрители маяков
			AddItems(ch, "jewelry52", 	dRand(8)+7);	
			AddItems(ch, "jewelry53", 	dRand(15)+15);
			AddItems(ch, "jewelry8", 	dRand(3));
			
			irand = drand(130);
			if(irand == 7) AddItems(ch, "indian_1", 1);
			if(irand == 17) AddItems(ch, "indian_2", 1);
			if(irand == 28) AddItems(ch, "indian_3", 1);
			if(irand == 38) AddItems(ch, "indian_4", 1);
			if(irand == 47) AddItems(ch, "indian_5", 1);
			if(irand == 57) AddItems(ch, "indian_6", 1);
			if(irand == 68) AddItems(ch, "indian_7", 1);
			if(irand == 78) AddItems(ch, "indian_8", 1);
			if(irand == 87) AddItems(ch, "indian_9", 1);
			if(irand == 97) AddItems(ch, "indian_10", 1);
			if(irand == 108) AddItems(ch, "indian_11", 1);
			irand = drand(130);
			if(irand == 1) AddItems(ch, "amulet_1", 1);
			if(irand == 10) AddItems(ch, "amulet_2", 1);
			if(irand == 20) AddItems(ch, "amulet_3", 1);
			if(irand == 30) AddItems(ch, "amulet_4", 1);
			if(irand == 40) AddItems(ch, "amulet_5", 1);
			if(irand == 50) AddItems(ch, "amulet_6", 1);
			if(irand == 60) AddItems(ch, "amulet_7", 1);
			if(irand == 70) AddItems(ch, "amulet_8", 1);
			if(irand == 80) AddItems(ch, "amulet_9", 1);
			if(irand == 90) AddItems(ch, "amulet_10", 1);
			if(irand == 100) AddItems(ch, "amulet_11", 1);
			irand = drand(130);
			if(irand == 5) AddItems(ch, "obereg_1", 1);
			if(irand == 15) AddItems(ch, "obereg_2", 1);
			if(irand == 25) AddItems(ch, "obereg_3", 1);
			if(irand == 35) AddItems(ch, "obereg_4", 1);
			if(irand == 45) AddItems(ch, "obereg_5", 1);
			if(irand == 55) AddItems(ch, "obereg_6", 1);
			if(irand == 65) AddItems(ch, "obereg_7", 1);
			if(irand == 75) AddItems(ch, "obereg_8", 1);
			if(irand == 85) AddItems(ch, "obereg_9", 1);
			if(irand == 95) AddItems(ch, "obereg_10", 1);
			if(irand == 105) AddItems(ch, "obereg_11", 1);
			if(irand == 115) AddItems(ch, "rat_poison", 1);
			irand = drand(120);
			if(irand == 9 && rank > 6) GenerateAndAddItems(ch, "blade_06", 1);
			if(irand == 49 && rank > 6) GenerateAndAddItems(ch, "blade_10", 1);
			if(irand == 99 && rank > 6) GenerateAndAddItems(ch, "blade_15", 1);
			irand = drand(250); // 170912
			if(irand == 6 && rank > 15) GenerateAndAddItems(ch, "blade_17", 1);
			if(irand == 96 && rank > 15) GenerateAndAddItems(ch, "blade_19", 1);
			if(irand == 226 && rank > 15) GenerateAndAddItems(ch, "blade_21", 1);
		break;
		
		case "minentown": //Jason - торговец на золотом руднике
			AddItems(ch, "jewelry5", 	dRand(30)+20);	
			AddItems(ch, "jewelry6", 	dRand(45)+30);
			AddItems(ch, "bullet", 		Rand(20) + 20);	
			AddItems(ch, "grapeshot", 	Rand(10) + 10);    
			AddItems(ch, "gunpowder", 	Rand(20) + 10);
			
			irand = drand(5);
			if(irand == 1) AddItems(ch, "jewelry10", dRand(7)+3));
			if(irand == 3) AddItems(ch, "jewelry14", 1+rand(4));
			if(irand == 5) AddItems(ch, "jewelry18", 1+rand(4));
			irand = drand(3);
			if(irand == 0) AddItems(ch, "jewelry13", dRand(5)+3));
			if(irand == 1) AddItems(ch, "jewelry16", 1+rand(4));
			if(irand == 2) AddItems(ch, "jewelry20", 1+rand(4));
			irand = drand(4);
			if(irand == 0) AddItems(ch, "jewelry12", dRand(5)+3));
			if(irand == 2) AddItems(ch, "jewelry17", 1+rand(4));
			if(irand == 4) AddItems(ch, "jewelry21", 1+rand(4));
			irand = drand(6);
			if(irand == 1) AddItems(ch, "jewelry15", 1+rand(4));
			if(irand == 3) AddItems(ch, "jewelry22", 1+rand(4));
			if(irand == 6) AddItems(ch, "jewelry23", 1+rand(4));
			irand = drand(10);
			if(irand == 0) AddItems(ch, "jewelry1", 1+rand(15));
			if(irand == 3) AddItems(ch, "jewelry2", 1+rand(15));
			if(irand == 6) AddItems(ch, "jewelry3", 1+rand(15));
			if(irand == 9) AddItems(ch, "jewelry4", 1+rand(15));
			if(irand == 10) AddItems(ch, "jewelry9", 1);
		break;
		
		case "LSC_trader": //Jason - торговец в LSC. Всегда есть: лечилки, пули, порох, картечь. Остальное - как рандом ляжет. Могут быть старшие лечилки, амулеты, группа jewelry, ХО и ОО, доспехи.
			// зелья:
			AddItems(ch, "potion1", 	dRand(5)+1);	
			AddItems(ch, "potion2", 	dRand(2));
			AddItems(ch, "potion3", 	dRand(2));
			AddItems(ch, "potion4", 	dRand(1));	
			AddItems(ch, "potionrum", 	dRand(1));    
			AddItems(ch, "potionwine", 	dRand(1));
			// боеприпасы:
			AddItems(ch, "bullet", 		dRand(12)+5);
			AddItems(ch, "grapeshot", 	dRand(8)+5);
			AddItems(ch, "GunPowder", 	dRand(10)+5);
			//всякий металлолом
			irand = drand(6);
			if(irand == 0) GenerateAndAddItems(ch, "blade_05", rand(1));
			if(irand == 2) GenerateAndAddItems(ch, "blade_07", rand(1));
			if(irand == 4) GenerateAndAddItems(ch, "blade_08", rand(1));
			if(irand == 6) GenerateAndAddItems(ch, "blade_11", rand(1));
			//сабли получше
			irand = drand(15);
			if(irand == 1) GenerateAndAddItems(ch, "blade_15", rand(1));
			if(irand == 7) GenerateAndAddItems(ch, "blade_13", rand(1));
			if(irand == 14) GenerateAndAddItems(ch, "blade_10", rand(1));
			// достойные клинки
			irand = drand(100);
			if(irand == 5) GenerateAndAddItems(ch, "blade_19", rand(1));
			if(irand == 40) GenerateAndAddItems(ch, "blade_21", rand(1));
			if(irand == 95) GenerateAndAddItems(ch, "blade_18", rand(1));
			// пистоли
			irand = drand(12);
			if(irand == 1) AddItems(ch, "pistol1", rand(1));
			if(irand == 3) AddItems(ch, "pistol3", rand(1));
			if(irand == 6) AddItems(ch, "pistol4", rand(1));
			if(irand == 9) AddItems(ch, "pistol6", rand(1));
			if(irand == 12) AddItems(ch, "pistol2", rand(1));
			// мушкет
			irand = drand(99);
			if(irand == 25) AddItems(ch, "mushket1", rand(1));
			// кирасы
			irand = drand(40);
			if(irand == 1) AddItems(ch, "cirass1", rand(1));
			if(irand == 6) AddItems(ch, "cirass2", rand(1));
			if(irand == 12) AddItems(ch, "cirass5", rand(1));
			if(irand == 18) AddItems(ch, "cirass6", rand(1));
			// амулеты
			irand = drand(130);
			if(irand == 7) AddItems(ch, "indian_1", 1);
			if(irand == 17) AddItems(ch, "indian_2", 1);
			if(irand == 28) AddItems(ch, "indian_3", 1);
			if(irand == 38) AddItems(ch, "indian_4", 1);
			if(irand == 47) AddItems(ch, "indian_5", 1);
			if(irand == 57) AddItems(ch, "indian_6", 1);
			if(irand == 68) AddItems(ch, "indian_7", 1);
			if(irand == 78) AddItems(ch, "indian_8", 1);
			if(irand == 87) AddItems(ch, "indian_9", 1);
			if(irand == 97) AddItems(ch, "indian_10", 1);
			if(irand == 108) AddItems(ch, "indian_11", 1);
			irand = drand(130);
			if(irand == 1) AddItems(ch, "amulet_1", 1);
			if(irand == 10) AddItems(ch, "amulet_2", 1);
			if(irand == 20) AddItems(ch, "amulet_3", 1);
			if(irand == 30) AddItems(ch, "amulet_4", 1);
			if(irand == 40) AddItems(ch, "amulet_5", 1);
			if(irand == 50) AddItems(ch, "amulet_6", 1);
			if(irand == 60) AddItems(ch, "amulet_7", 1);
			if(irand == 70) AddItems(ch, "amulet_8", 1);
			if(irand == 80) AddItems(ch, "amulet_9", 1);
			if(irand == 90) AddItems(ch, "amulet_10", 1);
			if(irand == 100) AddItems(ch, "amulet_11", 1);
			irand = drand(130);
			if(irand == 5) AddItems(ch, "obereg_1", 1);
			if(irand == 15) AddItems(ch, "obereg_2", 1);
			if(irand == 25) AddItems(ch, "obereg_3", 1);
			if(irand == 35) AddItems(ch, "obereg_4", 1);
			if(irand == 45) AddItems(ch, "obereg_5", 1);
			if(irand == 55) AddItems(ch, "obereg_6", 1);
			if(irand == 65) AddItems(ch, "obereg_7", 1);
			if(irand == 75) AddItems(ch, "obereg_8", 1);
			if(irand == 85) AddItems(ch, "obereg_9", 1);
			if(irand == 95) AddItems(ch, "obereg_10", 1);
			if(irand == 105) AddItems(ch, "obereg_11", 1);
			// группа jewelry
			irand = drand(8);
			if(irand == 0) AddItems(ch, "jewelry1", rand(3));
			if(irand == 1) AddItems(ch, "jewelry2", rand(5));
			if(irand == 2) AddItems(ch, "jewelry3", rand(4));
			if(irand == 3) AddItems(ch, "jewelry4", rand(3));
			if(irand == 4) AddItems(ch, "jewelry5", rand(3));
			if(irand == 5) AddItems(ch, "jewelry6", rand(5));
			if(irand == 6) AddItems(ch, "jewelry10", rand(4));
			if(irand == 7) AddItems(ch, "jewelry12", rand(5));
			if(irand == 8) AddItems(ch, "jewelry13", rand(5));
			irand = drand(6);
			if(irand == 3) AddItems(ch, "jewelry45", rand(2));
			if(irand == 4) AddItems(ch, "jewelry46", rand(2));
			if(irand == 4) AddItems(ch, "jewelry52", rand(5));
			if(irand == 6) AddItems(ch, "jewelry53", rand(7));
		break;
		
		case "LSC_indian": //Jason: индеец в LSC
			AddItems(ch, "jewelry53", 	dRand(4)+1);	
			AddItems(ch, "jewelry52", 	dRand(2)+1);
			AddItems(ch, "jewelry8", 	dRand(2));
			
			irand = drand(6);
			if(irand == 6) AddItems(ch, "jewelry7", 1);
			irand = drand(10);
			if(irand == 5) AddItems(ch, "jewelry11", 1);
		break;
		
		case "company": //Jason: главный клерк ГВИК: приборы, часы, карты, подзорные трубы
			AddItems(ch, "sand_clock", 	1);	// песочные часы
			irand = drand(2); // хронометр 33%
			if(irand == 2) AddItems(ch, "clock1", 1+(rand(1)));
			irand = drand(3); // компас 25%
			if(irand == 3) AddItems(ch, "compass1", 1);
			irand = drand(9); // астролябия 10%
			if(irand == 5) AddItems(ch, "astrolab", 1);
			irand = drand(4); 
			if(irand == 3) AddItems(ch, "spyglass1", 1);
			irand = drand(6); 
			if(irand == 6) AddItems(ch, "spyglass2", 1);
			irand = drand(100);
			if(irand == 50 && sti(pchar.rank) > 7) AddItems(ch, "spyglass3", 1);
			GenerateMaps(ch, 20, 50); // patch-5
		break;
		
		case "cemeteryman": //Jason: смотрители кладбищ
			irand = drand(1);
			if(irand == 0) AddItems(ch, "cannabis1", 1+(rand(3)));
			if(irand == 1) AddItems(ch, "cannabis2", 1+(rand(3)));
			irand = drand(3);
			if(irand == 0) AddItems(ch, "cannabis3", 1+(rand(3)));
			if(irand == 1) AddItems(ch, "cannabis4", 1+(rand(3)));
			if(irand == 2) AddItems(ch, "cannabis5", 1+(rand(3)));
			if(irand == 3) AddItems(ch, "cannabis6", 1+(rand(3)));
			irand = drand(4);
			if(irand == 0) AddItems(ch, "jewelry12", 1+(rand(1)));
			if(irand == 1) AddItems(ch, "jewelry13", 1+(rand(1)));
			if(irand == 2) AddItems(ch, "jewelry22", 1+(rand(1)));
			irand = drand(10);
			if(irand == 0) AddItems(ch, "blade_03", 1);
			if(irand == 3) AddItems(ch, "blade_05", 1);
			if(irand == 7) AddItems(ch, "blade_07", 1);
			irand = drand(120);
			if(irand == 10) AddItems(ch, "blade_04", 1);
			if(irand == 40) AddItems(ch, "blade_06", 1);
			if(irand == 80) AddItems(ch, "blade_10", 1);
			irand = drand(7);
			if(irand == 0) AddItems(ch, "pistol1", 1);
			irand = drand(5);
			if(irand == 0) AddItems(ch, "bullet", 1+(rand(10)));
			if(irand == 1) AddItems(ch, "grapeshot", 1+(rand(10)));
			if(irand == 2) AddItems(ch, "cartridge", 1+(rand(5)));
			if(irand == 3) AddItems(ch, "gunpowder", 1+(rand(10)));
			AddItems(ch, "mineral"+(drand(11)+1), 1);
			AddItems(ch, "mineral"+(drand(13)+13), 1);
		break;
	}	
}

string PlaceCharacter(aref ch, string group, string location) //boal change
{  // location = "random"  "random_free"  и "random_must_be" - должен быть, даже если все занято  random_must_be_near - рядом
	float locx;
	float locy;
	float locz;
	string homelocator;
	bool ok;
	
	GetCharacterPos(GetMainCharacter(), &locx, &locy, &locz);
	if (location == "random_free") location = "random"; // совместимость с пред. правкой
	
	if (location == "random" || location == "random_must_be")
	{
		homelocator = LAi_FindFreeRandomLocator(group);
		ChangeCharacterAddressGroup(ch, pchar.location, group, homelocator);  // всегда, где ГГ
	}
	else
	{
		homelocator = LAi_FindNearestFreeLocator(group, locx, locy, locz);
		if (location == "random_must_be_near")
		{
		    ChangeCharacterAddressGroup(ch, pchar.location, group, homelocator);  // всегда, где ГГ
		}
		else
		{
			ChangeCharacterAddressGroup(ch, location, group, homelocator);
		}
	}

	if (homelocator == "" && location == "random_must_be") // дело плохо, свободных уже нет, но НПС-то нужен, ищем затяный
	{
	    homelocator = LAi_FindFarLocator(group, locx, locy, locz);
		ChangeCharacterAddressGroup(ch, pchar.location, group, homelocator);  // всегда, где ГГ
	}
	if (homelocator == "" && location == "random_must_be_near") // дело плохо, свободных уже нет, но НПС-то нужен, ищем затяный
	{
	    homelocator = LAi_FindNearestLocator(group, locx, locy, locz);
		ChangeCharacterAddressGroup(ch, pchar.location, group, homelocator);  // всегда, где ГГ
	}
    return homelocator; // boal нужно проверять куда его занесло
}

void PrepareVisitCity()
{
	string sQuest;
	for (int i=0; i<MAX_COLONIES; i++)
	{
		if (Colonies[i].nation != "none")
		{
			sQuest = "VisitColony_" + Colonies[i].id;
			pchar.quest.(sQuest).win_condition.l1 = "location";
			pchar.quest.(sQuest).win_condition.l1.location = Colonies[i].id + "_town";
			pchar.quest.(sQuest).win_condition = "FirstVisitCity";
			pchar.quest.(sQuest).function      = "FirstVisitCity";
			pchar.quest.(sQuest).colonyId = Colonies[i].id;
		}
	}
}

void FirstVisitCity(string sQuest)
{
	string sColony = pchar.quest.(sQuest).colonyId;
	Colonies[FindColony(sColony)].visited = true;
}

// переделал 25.09.06 метод не зависит от ГГ, просто ранд корабли для порта
int SearchForMaxShip(aref chr, int isLock, int _tmp)
{
	int iType;
	
	if (sti(chr.nation) != PIRATE)
	{
		if (rand(100) > 70)
		{
			iType = rand(SHIP_FRIGATE);	
		}
		else
		{
			iType = rand(SHIP_BRIG);	
		}
	}
	else
	{
	 	if (rand(100) > 70)
		{
			iType = rand(SHIP_LINESHIP);	
		}
		else
		{
			iType = rand(SHIP_GALEON_L);	
		}
	}
	iType = GenerateShip(iType, isLock);
	return iType;
}

int FindFirstEmptyCharacter()
{
	for(int i = GlobalCharacters; i<TOTAL_CHARACTERS; i++)
	{
		if (characters[i].id == "0")
		{
			if (i >= MAX_CHARACTERS) MAX_CHARACTERS = i+1; //сдвигаем планку НПС
			return i;
		}
	}		
	return -1;
}

void AddGeometryToLocation(string LocationID, string ModelName)
{
	ref LocationRef;
	int n = 1;
	string str;
	locationRef = &locations[FindLocation(LocationID)];

	for(n = 1; n < 10; n++)
	{
		str = "l" + n;
		if(!CheckAttribute(LocationRef, "models.always." + str))
		{
			LocationRef.models.always.(str) = ModelName;
			LocationRef.models.always.(str).tech = "dLightModel";
			break;
		}
	}
}	

void RemoveGeometryFromLocation(string LocationID, string ModelName)
{
	ref LocationRef;
	int n = 1;
	string str;
	//trace("FUNCTION RemoveGeometryFromLocation reports: Current location ID is " + LocationID + " and geometry " + ModelName + " should be removed");
	if(FindLocation(LocationID) != -1)
	{
		locationRef = &locations[FindLocation(LocationID)];
	}
	else
	{
		return;
	}

	for(n = 1; n < 10; n++)
	{
		str = "l" + n;
		//trace("FUNCTION RemoveGeometryFromLocation reports: Checking Geometry name for n = " + str + ". It is " + LocationRef.models.always.(str));
		if(CheckAttribute(LocationRef, "models.always." + str) && LocationRef.models.always.(str) == ModelName)
		{
			DeleteAttribute(LocationRef, "models.always." + str);
			break;
		}
	}
}	


void CreateModel(int iChar, string sType, int iSex)
{
	int iNation = sti(characters[iChar].nation);
	
	string sBody = "";
	string sPrefix = "";
	int iNumber = -1;
		
	switch (sType)
	{
		case "pofficer":
			sBody = "mercen";
			if(iNation == PIRATE)
			{
				if(rand(1) == 0) iNumber = rand(4) + 6;
				else			 iNumber = rand(4) + 16;
			}
			else
			{
				if(rand(1) == 0) iNumber = rand(4) + 1;
				else			 iNumber = rand(4) + 11;
			}
		break;

		case "officer":
			sBody = "off";
			iNumber = rand(1)+1;
		break;
		
		case "soldier":
			sBody = "sold";
			iNumber = rand(7)+1;
		break;
		
		case "pirate":
			sBody = "citiz";
			iNumber = rand(9)+41;
		break;

		case "trader":
			sBody = "trader";
			iNumber = rand(13)+1; // 170712
		break;
		
		case "monk":
			sBody = "monk";
			iNumber = rand(5)+1;
		break;	
		
		case "blade_trader":
			sBody = "mercen";
			iNumber = rand(4) + 7;
		break;
				
		case "citizen": //мещане-бюргеры
			if(iSex == MAN)
			{
				sBody = "citiz";
				iNumber = rand(9)+11;
			}
			else
			{
					sBody = "women";
					iNumber = rand(11)+7;
				}	
		break;

		case "whore":
			sBody = "whore";
			iNumber = rand(3) + 1;
		break;
		
		//Jason --> новые типы горожан
		case "marginal": //маргиналы
			sBody = "citiz";
			iNumber = rand(9)+21;
		break;
		
		case "captain": //капитаны
			if (rand(1) == 0)
			{
				sBody = "citiz";
				iNumber = rand(9)+51;
			}
			else
			{
				sBody = "mercen";
				iNumber = rand(14)+16;
			}
		break;
		
		case "noble": //дворяне
			if(iSex == MAN)
			{
				sBody = "citiz";
				iNumber = rand(9)+1;
			}
			else
			{
				sBody = "women";
				iNumber = rand(5)+1;
			}
		break;
		
		case "gipsy": //цыганки
			sBody = "gipsy";
			iNumber = rand(3)+1;
		break;
		
		case "sailor": //матросы
			sBody = "citiz";
			iNumber = rand(9)+31;
		break;
		
		case "indian": //индейцы
			if(iSex == MAN)
			{
			sBody = "Miskito";
			iNumber = rand(5)+1;
			}
			else
			{
				sBody = "squaw"; 
				iNumber = rand(2)+1;
			}
		break;
		
		case "convict": //каторжники
			sBody = "prizon";
			iNumber = rand(3)+5;
		break;
		//<-- новые типы горожан
		
		case "spa_soldier": //солдаты рудника в таверне
			if (rand(4) < 4)
			{
				sBody = "sold_spa";
				iNumber = rand(15)+1;
			}
			else
			{
				sBody = "off_spa";
				iNumber = rand(5)+1;
			}
		break;
	}

	sPrefix = "_";
	
	if(sType == "officer" || sType == "soldier")
	{
		switch (iNation)
		{
			case ENGLAND:
				sPrefix = "_eng_";
			break;
			
			case FRANCE:
				sPrefix = "_fra_";
			break;
			
			case SPAIN:
				sPrefix = "_spa_";
			break;
			
			case HOLLAND:
				sPrefix = "_hol_";
			break;
			
			case PIRATE:
				sPrefix = "";
			break;
		}
	}
	
	string sResult = "";
	
	sResult = sBody+sPrefix+iNumber;
	
	characters[iChar].model = sResult;

	FaceMaker(&characters[iChar]);
	CirassMaker(&characters[iChar]);
}

// метод вернет случайный дружественный iNation город, неравный  sBeginColony _checkPort - Проверка порта
int FindNonEnemyColonyForAdventure(int iNation, string sBeginColony, bool _checkPort)
{
	int iArray[MAX_COLONIES];
	int m = 0;
	
	for (int i=0; i<MAX_COLONIES; i++)
	{
		if (colonies[i].nation != "none")
		{
			if (_checkPort && CheckAttribute(&Colonies[i], "HasNoFort")) continue;  // без форта не берем
			
			if (GetNationRelation(sti(Colonies[i].nation), iNation) != RELATION_ENEMY && Colonies[i].id != sBeginColony)
			{
				iArray[m] = i;
				m++;
			}
		}
	}
	
	if (m == 0)
	{
		return -1;
	}
	
	m = rand(m-1);
	m = iArray[m];
	return m;
}

int FindNonEnemyColonyForNation(int iNation, bool _checkPort)
{
	return FindNonEnemyColonyForAdventure(iNation, "NOT_IN_USE", _checkPort);
}

string FindAlliedColonyForNation(int iNation, bool _checkPort)
{
	int iArray[MAX_COLONIES];
	int m = 0;
	string sColony = "";
	
	for (int i = 0; i<MAX_COLONIES; i++)
	{
		if (colonies[i].nation != "none" && colonies[i].id != "Panama" && colonies[i].id != "SanAndres")
		{
			if (_checkPort && CheckAttribute(&Colonies[i], "HasNoFort")) continue;  // без форта не берем
			if (sti(Colonies[i].nation)== iNation)
			{
				iArray[m] = i;
				m++;
			}
		}
	}
	
	if (m == 0)
	{
		return "-1";
	}
	
	m = rand(m-1);
	m = iArray[m];
	sColony =  Colonies[m].id;
	
	return sColony;
}

string FindAlliedColonyForNationExceptColony(string sHomeColony)
{
	int iArray[MAX_COLONIES];
	int m = 0;
	string sColony = "";

	int iNation = sti(colonies[FindColony(sHomeColony)].nation);
	
	for (int i = 0; i<MAX_COLONIES; i++)
	{
		if(colonies[i].nation != "none" && colonies[i].id != sHomeColony && colonies[i].id != "Panama")
		{
			if (sti(Colonies[i].nation) == iNation)
			{
				iArray[m] = i;
				m++;
			}
		}
	}
	
	if (m == 0)
	{
		return "-1";
	}
	
	m = rand(m-1);
	m = iArray[m];
	sColony =  Colonies[m].id;
	
	return sColony;
}

string FindColonyWithMayakExceptIsland(string sIsland)
{
	int iArray[MAX_COLONIES];
	int m = 0;
	string sColony = "";
	
	for (int i = 0; i<MAX_COLONIES; i++)
	{
		if (colonies[i].nation != "none" && GetMayakByCityName(colonies[i].id) != "" && GetArealByCityName(colonies[i].id) != sIsland)	
		{
			iArray[m] = i;
			m++;		
		}
	}
	if (m == 0)
	{
		return "-1";
	}
	m = rand(m-1);
	m = iArray[m];
	sColony =  Colonies[m].id;
	
	return sColony;	
}

string SelectQuestDestinationAnyNationExceptColony(string sColony)
{
	int m;

	string sTempColony = sColony;

	while(sTempColony == sColony)
	{
		m = rand(MAX_COLONIES-1);
		if(colonies[m].nation != "none")
		{
			sTempColony = Colonies[m].id;
		}
	}

	return sTempColony;
}

// ugeen --> выбор случайной бухты на острове, где находится ГГ
string SelectQuestShoreLocation() 
{
    ref CurIsland;
	int n, i;
	string TargetLocation = "";
	
	i = 0;
	n = GetCharacterCurrentIsland(pchar);
	if (n < 0) 
	{
		TargetLocation = "";
	}
	else
	{
		CurIsland = GetIslandByIndex(n);
		while(TargetLocation == "" && i < 10)
		{
			TargetLocation = GetIslandRandomShoreId(CurIsland.id);
			if (!isLocationFreeForQuests(TargetLocation)) 
			{
				TargetLocation = ""; i++;
			}	
		}		
    }
	if(TargetLocation == "") TargetLocation = GetIslandRandomShoreId(CurIsland.id);
	Log_QuestInfo("TargetLocation = " + TargetLocation);
    return TargetLocation;
}

string SelectQuestShoreLocationFromSea(string CurIsland)
{
	string TargetLocation = "";
	int n, i;
	ref rIsland;
	
	i = 0;
	n = FindIsland(CurIsland);
	if (n < 0) 
	{
		TargetLocation = "None";
	}	
	else
	{
		rIsland = GetIslandByIndex(n);
		while(TargetLocation == "" && i < 10)
		{
			TargetLocation = GetIslandRandomShoreId(rIsland.id);
			if (!isLocationFreeForQuests(TargetLocation)) 
			{
				TargetLocation = ""; i++;
			}	
		}		
	}
	if(TargetLocation == "") TargetLocation = GetIslandRandomShoreId(rIsland.id);
	Log_QuestInfo("TargetLocation = " + TargetLocation);
	return TargetLocation;
} 
// ugeen

void EmptyAbordageCharacters()
{
	for (int i=GlobalCharacters; i<MAX_CHARACTERS; i++)
	{
		if (CheckAttribute(&characters[i], "AboardFantom"))	InitCharacter(&characters[i], i);		
	}
}

void EmptyAllFantomCharacter()
{
	if (bAbordageStarted) return; // иначе трутся НПС при переходе в каюте
	int cn = -1;
	for (int i=GlobalCharacters; i<MAX_CHARACTERS; i++)
	{
		// отдельный код зачистки boal -->
		if (LAi_IsDead(&characters[i]) && !CheckAttribute(&characters[i], "RebirthPhantom"))
		{
      			if(GetCompanionQuantity(&characters[i]) > 1) // Хм, а у фантомов есть компаньоны как у взрослых ГГ? оставлю на всяк случай (для ПГГ)
				{
					for(int k = 0; k < COMPANION_MAX; k++)
					{
						cn = GetCompanionIndex(&characters[i], k);
						if(cn != -1)
						{
							InitCharacter(&characters[cn], cn);
						}
					}
				}
				else
				{
     				InitCharacter(&characters[i], i);
				}
		}
		else
		{
			if (CheckAttribute(&characters[i], "LifeDay") &&
			    GetNpcQuestPastDayParam(&characters[i], "LifeTimeCreate") >= sti(characters[i].LifeDay) &&
				characters[i].location != pchar.location) // не трем, если ГГ в локации,иначе горожане пропадают на лету
			{ // время вышло
				InitCharacter(&characters[i], i);  // тут проверку на компаньонов не нужно, тк они все одинаковые по времени
			}
		}
		// boal <--
	}
}

// метод оставлен для совместимости со старым кодом К3
int GenerateCharacter(int iNation, int isShip, string sModel, int iSex, int isLock, int CharacterType)
{
    int iChar = NPC_GeneratePhantomCharacter(sModel, iNation, iSex, -isLock); // -isLock) == -1 || 0

	if (IsShip == WITH_SHIP)
	{
		// to_do del
		if(CharacterType == FORT_COMMANDER)
		{
			characters[iChar].ship.type = GenerateShip(SHIP_FORT, isLock);
			Fantom_SetRandomCrewExp(&characters[iChar], "war");
		}
		else
		{
			characters[iChar].ship.type = SearchForMaxShip(&characters[iChar], isLock, CharacterType);
			Fantom_SetRandomCrewExp(&characters[iChar], "war");
			
		}
		
		SetBaseShipData(&characters[iChar]);
		
		SetRandomNameToShip(&characters[iChar]);
	}
	else
	{
		characters[iChar].ship.type = SHIP_NOTUSED;
		DeleteAttribute(&characters[iChar], "ship.upgrades");
	}
	return iChar;
}

int GetRandomNationForMapEncounter(string sIslandID, bool bMerchant)
{   // boal: метод соверненно не понятен, убрал из него массив НатионСтайт, заменив на 1.0, раз работало - пусть будет как было, но логика чумовая
	int iNation = -1;
	if(sIslandID != "")
	{
		int iIsland = FindIsland(sIslandID);
		for(int i = 0; i < MAX_COLONIES; i++)
		{
			if(colonies[i].island == sIslandID)
			{
				if (colonies[i].nation != "none")
				{
					iNation = sti(colonies[i].nation);
					break;
				}
			}
		}
	}

	float fEngland  = 1.0;
	float fFrance   = 1.0;
	float fSpain    = 1.0;
	float fHolland  = 1.0;
	float fPirate   = 1.0;

	// бонус за ближ город
	if(iNation != -1)
	{
	    switch (iNation )
		{
			case ENGLAND:
				fEngland += 0.2;
			break;
			case FRANCE:
    			fFrance += 0.2;
			break;
			case SPAIN:
    			fSpain += 0.2;
			break;
			case HOLLAND:
    			fHolland += 0.2;
			break;
			case PIRATE:
    			fPirate += 0.2;
			break;
		}
	}

	float fProbablyNation;
	if(bMerchant)
	{
		fProbablyNation = fEngland + fFrance + fSpain + fHolland;
	}
	else
	{
		fProbablyNation = fEngland + fFrance + fSpain + fHolland + fPirate;
	}

	fProbablyNation = frand(fProbablyNation);

	fFrance   = fFrance  + fEngland;
	fSpain    = fFrance  + fSpain;
	fHolland  = fSpain   + fHolland;
	fPirate   = fHolland + fPirate;

	if(bMerchant == 0)
	{
		if(fProbablyNation >= fFrance && fProbablyNation < fSpain)
		{
			return FRANCE;
		}

		if(fProbablyNation >= fSpain && fProbablyNation < fHolland)
		{
			return SPAIN;
		}

		if(fProbablyNation >= fHolland && fProbablyNation < fPirate)
		{
			return HOLLAND;
		}

		if(fEngland <= fProbablyNation)
		{
			return ENGLAND;
		}
	}
	else
	{
		if (rand(2) == 1) return HOLLAND; //голланцев на карту
		
		if(fProbablyNation >= fFrance && fProbablyNation < fSpain)
		{
			return FRANCE;
		}

		if(fProbablyNation >= fSpain && fProbablyNation < fHolland)
		{
			return SPAIN;
		}

		if(fProbablyNation >= fHolland && fProbablyNation < fPirate)
		{
			return HOLLAND;
		}

		if(fEngland <= fProbablyNation)
		{
			return ENGLAND;
		}
	}

	return PIRATE;
}


string CheckingTranslate(int idLngFile, string idString)
{
	string retString = LanguageConvertString ( idLngFile, idString );
	if(retString=="")
	{
		trace("Warning! No text for lable <" + idString + "> into language file <LocLables.txt>");
	}
	return retString;
}

// to_do
void LaunchMoneyGraphCollect()
{
	string sYear = "year" + worldMap.date.year;
	string sMonth = "month" + worldMap.date.month;

	pchar.MoneyGraph.(sYear).(sMonth) = pchar.money;
}

string FindNearestFreeLocator(string group)
{
	float locx;
	float locy;
	float locz;
	string homelocator;
	
	GetCharacterPos(pchar, &locx, &locy, &locz);
	homelocator = LAi_FindNearestFreeLocator(group, locx, locy, locz);
	
	return homelocator;
}

string SetModelFlag(aref chr)
{
	string sResult = "";

	if(chr.chr_ai.type == LAI_TYPE_ACTOR)
	{
		return "";
	}

	if(CheckAttribute(&InterfaceStates,"EnabledQuestsMarks") )
	{
		if(sti(InterfaceStates.EnabledQuestsMarks) == 0)
		{
			return "";
		}
	}

	if(CheckAttribute(chr, "quest.questflag"))
	{
		switch(sti(chr.quest.questflag))
		{
			case 1:
				sResult = "exclamationmarkY";
			break;
			
			case 2:
				sResult = "questionmarkY";
			break;

			case 3:
				sResult = "questionmarkW";
			break; 
		}
	}

	chr.quest.questflag.technique = GetTechNameForSign();

	return sResult;
}

string GetTechNameForSign()
{
	return "RandItem";
}

void CheckQuestForCharacter(aref chr)
{

}

////////////////////////// boal набор методов для генерации фантомов
// boal -->
void InitCharacter(ref ch, int n)
{
    //DeleteAttribute(ch,"act");
	DeleteAttribute(ch,"");
	//Logic data
	ch.id = "0";
	ch.index = n;
	ch.name 	= "none";
	ch.lastname = "none";
	ch.sex = "man";
	//Model data
	ch.model = "none";
	ch.model.entity = "NPCharacter";
	ch.model.animation = "";
	//Address
	ch.location = "none";
	ch.location.group = "";
	ch.location.locator = "";
	ch.location.from_sea = "";
	//Ship data
	ch.Ship.Type = SHIP_NOTUSED;
	//Quest data
	ch.Dialog.CurrentNode = "First time";
	ch.Dialog.TempNode = "First time";
	ch.quest.meeting = "0";
	ch.quest = "True";
	ch.quest_date = 0;
	//Misc data
	ch.nation = ENGLAND;
	ch.skill.freeskill = 0;
	ch.perks.freepoints = 0;
	ch.rank = 1;
	ch.reputation 			= REPUTATION_NEUTRAL;
	ch.reputation.fame 		= COMPLEX_REPUTATION_MIN;
	ch.reputation.nobility 	= COMPLEX_REPUTATION_NEUTRAL;
	ch.reputation.authority = COMPLEX_REPUTATION_NEUTRAL;
	ch.reputation.france = 0;
	ch.reputation.england = 0;
	ch.reputation.spain = 0;
	ch.reputation.holland = 0;
	ch.reputation.pirate = 0;
	ch.reputation.smuggler = 0;
	ch.reputation.trader = 0;
	ch.fame = 1;
	// boal -->
    SetRandSPECIAL(ch);
    //InitStartParam(ch);
    SetSelfSkill(ch, 1, 1, 1, 1, 1);
    SetShipSkill(ch, 1, 1, 1, 1, 1, 1, 1, 1, 1);

	ch.Skill.FreeSPECIAL  = 0;
    ch.Health.HP        = 60.0; // отличное
	ch.Health.maxHP     = 60.0;
	ch.Health.Damg      = 0.0;
	ch.Health.weekDamg  = 0.0;
	ch.Health.TotalDamg = 0.0;
	// <--
	ch.rank = 1;
	ch.experience = 0;

	ch.Fellows.Passengers.id0 = n; // свой пассажир

	ch.Fellows.Passengers.boatswain = "-1";
	ch.Fellows.Passengers.navigator = "-1";
	ch.Fellows.Passengers.doctor = "-1";
	ch.Fellows.Passengers.cannoner = "-1";
	ch.Fellows.Passengers.treasurer = "-1";
	ch.Fellows.Passengers.carpenter = "-1";

	//ch.prisoned = false;

	ch.money = "0";
	ch.dublon = "0";
	// battle hp
	ch.headModel = "";
	//LAi_SetLoginTime(ch, 6.0, 21.98333);
	LAi_SetLoginTime(ch, 0.0, 24.0); // круглосуточно
 	LAi_SetHP(ch, LAI_DEFAULT_HP, LAI_DEFAULT_HP_MAX);
	
	ch.BaseCRC = 1 + rand(5);
	ch.SystemInfo.itemsCRC = CheckItemsCRC(ch);
	
	// слоты под предметы
	ch.equip_item = "";
	ch.equip_item.slot1 = SLOT_NOT_USED;
	ch.equip_item.slot1.time = -1;
	ch.equip_item.slot2 = SLOT_NOT_USED;
	ch.equip_item.slot2.time = -1;
	ch.equip_item.slot3 = SLOT_NOT_USED;
	ch.equip_item.slot3.time = -1;
}
// boal <--
// метод ищет или создает НПС с указанным ID. Для последуешего применения
int NPC_FindOrCreateCharacter(string _id)
{
	int ci = GetCharacterIndex(_id);
	if (ci == -1)
    { // не нашли
        ci = FindFirstEmptyCharacter();
        if (ci != -1)
		{
			InitCharacter(&Characters[ci], ci);
			Characters[ci].id = _id;
		}
    }
    return ci;
}
// _ani нужно для двух рас пкм + к3
// _LifeDay - сколько дней живет, если -1, то вечный, если 0, то трется при выходе из локации
// _equip - экипировка саблями, перки все равно раздадутся
// _type - тип персонажа
/*
Возможные типы персонажей
"slave" - каторжники, рабы, мятежники
"native" - караибы
"marginal" - бандиты, экипажи пиратских судов, жители пиратских поселений
"pirate" - обычные пираты
"citizen" - экипажи торговых судов, горожане, верфисты.
"skeleton" - нечисть
"soldier" - солдаты в патрулях, в городе, экипажи всех военных судов, пиратские кэпы на судах 6-4 ранга
"officer" - офицеры (все офицеры в игре), начальники патрулей, капитаны военных кораблей 6-2 классов, пиратские кэпы на судах 1-3 ранга
"hunter" - ОЗГ, ДУ
"mercenary" - наемники в тавернах
"governor" - губернаторы, капитаны военных кораблей 1-го класса, призонбоссы
"itza" - воины ица
"quest" - отдельные квестовые персонажи не создаваемые функцией МэйкКулФайтер
*/
int NPC_GenerateCharacter(string _id, string _model, string _sex, string _ani, int _rank, int _nation, int _LifeDay, bool _equip, string _type)
{
    int iChar = NPC_FindOrCreateCharacter(_id);
	ref ch;
	if (iChar == -1) return -1;
	
    ch = &Characters[iChar];
	ch.rank 		= _rank;
    ch.nation   	= _nation;
    ch.sex      	= _sex;
    ch.model    	= _model;
	ch.PhantomType 	= _type;
    if(ch.sex == "man")
	{
		ch.model.height = 1.8;
	}else{
		ch.model.height = 1.75;
	}
	ch.model.animation = _ani;
	FaceMaker(ch);
	CirassMaker(ch);
	SetRandomNameToCharacter(ch);
	SetFantomParamFromRank(ch, _rank, _equip);
	if (_LifeDay >= 0)
	{
	    ch.LifeDay = _LifeDay;
	    SaveCurrentNpcQuestDateParam(ch, "LifeTimeCreate");
	}
	else
	{
     	DeleteAttribute(ch, "LifeDay");
	}
	return  iChar;
}
// сгенерим разового фантома - нашего моряка (в  форме, если патент)
ref GetOurSailor(string _id) // моежт быть нужно несколько
{
    string  smodel;
    ref     CrOur;
    string  ani;
    int     i;

    smodel = LAi_GetBoardingModel(GetMainCharacter(), &ani);
    
	i = NPC_GenerateCharacter(_id, smodel, "man", ani, 10, sti(pchar.nation), 0, true, "soldier");
	CrOur = GetCharacter(i);
	CrOur.name     = "Sailor";
	CrOur.lastname = "";
	
	return CrOur;
}

int NPC_GeneratePhantomCharacter(string sType, int iNation, int iSex, int _LifeDay)//, int CharacterType)
{
    int iChar = FindFirstEmptyCharacter();
    ref ch;

	if (iChar == -1) return -1;
	ch = &Characters[iChar];
    InitCharacter(ch, iChar);
    
	if (_LifeDay >= 0)
	{
	    ch.LifeDay = _LifeDay;
	    SaveCurrentNpcQuestDateParam(ch, "LifeTimeCreate");
	}
	else
	{
     	DeleteAttribute(ch, "LifeDay");
	}
	
	ch.PhantomType = sType; // не нужно пока для дела, впрок

	if(iSex == MAN)
	{
		ch.sex = "man";
		if(sType == "monk" || sType == "convict") ch.model.animation = "man_B";
		else 				ch.model.animation = "man";
		ch.model.height = 1.80
	}
	else
	{
		ch.sex = "woman";
		if(sType == "indian") ch.model.animation = "woman_B";
		else ch.model.animation = "towngirl";
		ch.model.height = 1.70
	}

	ch.nation = iNation;

	SetRandomNameToCharacter(ch);
    ch.reputation = (1 + rand(44) + rand(44));// репа всем горожанам
	ch.id = "GenChar_" + iChar;
	
    CreateModel(iChar, sType, iSex);
    SetFantomParam(ch);
	    
    if (sType == "citizen" || sType == "blade_trader" || sType == "monk")
	{
		LAi_NPC_Equip(ch, sti(ch.rank), false, false);
	}
	else
	{
	    LAi_NPC_Equip(ch, sti(ch.rank), true, true);
	}
	
	return  iChar;
}

// boal prison count -->
int GetPrisonerQty()
{
    ref offref;
    int i, cn, iMax;
    ref mchr = GetMainCharacter();
    int qty = 0;

    iMax = GetPassengersQuantity(mchr);
    for(i=0; i < iMax; i++)
    {
        cn = GetPassenger(mchr,i);
        if(cn != -1)
        {
            offref = GetCharacter(cn);
            if(CheckAttribute(offref,"prisoned"))
            {
	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
	            {
                    qty++;
                }
            }
        }
    }
    return qty;
}
int SetCharToPrisoner(ref refEnemyCharacter)
{
    ref  rChTo, refMyCharacter;

    refMyCharacter =  GetMainCharacter();

    int  iNextPrisoner = FindFirstEmptyCharacter();
	
	if (iNextPrisoner != -1)
	{
	    rChTo = &Characters[iNextPrisoner];
	    InitCharacter(rChTo, iNextPrisoner);

		ChangeAttributesFromCharacter(rChTo, refEnemyCharacter, false);   // было четкое копирование, но что-то наследовалось от той жижни и в море вел по АИ убегания
	    rChTo.index = iNextPrisoner;
	    rChTo.id = "prisoner_" + iNextPrisoner;
	    rChTo.Dialog.Filename = "Ransack_captain_dialog.c";
	    rChTo.Dialog.CurrentNode = "First time";
	    DeleteAttribute(rChTo, "items");
		DeleteAttribute(rChTo, "equip");
		DeleteAttribute(rChTo, "LifeDay"); // постоянный
		DeleteAttribute(rChTo, "ship");
		DeleteAttribute(rChTo, "ShipSails.gerald_name");

		DeleteAttribute(rChTo, "AlwaysEnemy");
		DeleteAttribute(rChTo, "ShipTaskLock");
		DeleteAttribute(rChTo, "WatchFort");
		DeleteAttribute(rChTo, "AnalizeShips");

	    rChTo.ship.type = SHIP_NOTUSED;
		GiveItem2Character(rChTo, "unarmed");
	    EquipCharacterByItem(rChTo, "unarmed");

	    rChTo.greeting = "ransack";
				
		if(rand(2) == 1) Hold_GenQuest_Init(rChTo);
		
	    LAi_SetCitizenTypeNoGroup(rChTo);
	    LAi_group_MoveCharacter(rChTo, "Prisoner");
	    LAi_SetLoginTime(rChTo, 0.0, 24.0);
	    LAi_NoRebirthEnable(rChTo);

	    SetCharacterRemovable(rChTo, true);
	    AddPassenger(refMyCharacter,rChTo,true);
    }
    return iNextPrisoner;
}

void ReleasePrisoner(ref NPChar)
{
    DeleteAttribute(NPChar,"prisoned"); // освободили пленника
	RemovePassenger(PChar, NPChar);
	NPChar.LifeDay = 0; // трем
}

void FreeSitLocator(string location, string locator)
{	
	ref rCharacter; //ищем
	int n;

	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter,Characters[n]);
		if (CheckAttribute(rCharacter, "location"))
		{
            if (rCharacter.location == location && rCharacter.location.locator == locator)
            {
            	ChangeCharacterAddressGroup(rCharacter, "none", "none", "none"); // в никуда
            }
            else
            {
            	if (rCharacter.location == "none") // офы, которые уже наняты, но сидят
            	{
            		//Если загруженны, то выйдем из локации
					LogoffCharacter(rCharacter);
            	}
            }
		}
    }
}

bool CheckFreeLocator(string location, string locator, int idxDontSee)
{
	return LAi_CheckLocatorFree("sit", locator);
	/*ref rCharacter; //ищем
	int n;

	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter,Characters[n]);
		if (CheckAttribute(rCharacter, "location") && n != idxDontSee) // не смотрим самого себя, если нужно
		{
            if (rCharacter.location == location && rCharacter.location.locator == locator)
            {
				return false;
            }
		}
    }
    return true;*/
}
// boal <--

int RandFromThreeDight(int _Num1, int _Num2, int _Num3)
{
	switch (rand(2))
	{
		case 0: return _Num1; break;
		case 1: return _Num2; break;
		case 2: return _Num3; break;
	}
}

int RandFromFiveDight(int _Num1, int _Num2, int _Num3, int _Num4, int _Num5)
{
	switch (rand(4))
	{
		case 0: return _Num1; break;
		case 1: return _Num2; break;
		case 2: return _Num3; break;
		case 3: return _Num4; break;
		case 4: return _Num5; break;
	}
}


// Отключить на время форт (потом сам восстановится)
void MakeFortDead(string _ColonyFort)
{
	int ind = GetCharacterIndex(_ColonyFort + " Fort Commander");
	if(ind == -1) return;
	ref FC = &Characters[ind];
	FC.Fort.Mode = FORT_DEAD;
	// data of fort die
	FC.Fort.DieTime.Year = GetDataYear();
	FC.Fort.DieTime.Month = GetDataMonth();
	FC.Fort.DieTime.Day = GetDataDay();
	FC.Fort.DieTime.Time = GetTime();
	Event(FORT_DESTROYED, "l", sti(FC.index));
}

// ugeen --> получить наиболее дальний из группы локаторов для постановки квестовых  кораблей
string GetSeaQuestShipFarLocator(ref _loc, string group, float x, float y, float z)
{
	if(CheckAttribute(_loc, group) == 0) return "";
	aref grp;
	makearef(grp, _loc.(group));
	int num = GetAttributesNum(grp);
	if(num <= 0) return "";
	int j = -1;
	float dist = -1;
	for(int i = 0; i < num; i++)
	{
		aref loc = GetAttributeN(grp, i);
		float dx = x - stf(loc.x);
		float dy = y - stf(loc.y);
		float dz = z - stf(loc.z);
		float d = dx*dx + dy*dy + dz*dz;
		if(j >= 0)
		{
			if(d >= dist)
			{
				dist = d;
				j = i;
			}
		}
		else
		{
			j = i;
			dist = d;
		}				
	}
	if(j < 0) return "";
	return GetAttributeName(GetAttributeN(grp, j));
}

// ugeen --> получить наиболее ближний из группы локаторов для постановки квестовых  кораблей
string GetSeaQuestShipNearestLocator(ref _loc, string group, float x, float y, float z)
{
	if(CheckAttribute(_loc, group) == 0) return "";
	aref grp;
	makearef(grp, _loc.(group));
	int num = GetAttributesNum(grp);
	if(num <= 0) return "";
	int j = -1;
	float dist = -1;
	for(int i = 0; i < num; i++)
	{
		aref loc = GetAttributeN(grp, i);
		float dx = x - stf(loc.x);
		float dy = y - stf(loc.y);
		float dz = z - stf(loc.z);
		float d = dx*dx + dy*dy + dz*dz;
		if(j >= 0)
		{
			if(d < dist)
			{
				dist = d;
				j = i;
			}
		}
		else
		{
			j = i;
			dist = d;
		}
	}
	if(j < 0) return "";
	return GetAttributeName(GetAttributeN(grp, j));
}
