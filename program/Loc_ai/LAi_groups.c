

//Объект, описывающий отнощение одной группы к другой
object LAi_grp_relations;
float LAi_grp_playeralarm = 0;
bool LAi_grp_alarmactive = false;

//------------------------------------------------------------------------------------------
//Инициализация
//------------------------------------------------------------------------------------------

//Инициализация
bool LAi_group_Init()
{
	//Пока всё спокойно
	LAi_grp_playeralarm = 0;
	LAi_grp_alarmactive = false;
	//Создаём объект групп и загружаем параметры
	if(CreateEntity(&LAi_grp_relations, "CharactersGroups") == 0) return false;
	//Инициализация стандартной группы персонажей
	LAi_group_Register(LAI_DEFAULT_GROUP);
	LAi_group_SetPermanent(LAI_DEFAULT_GROUP);
	//Группа игрока
	LAi_group_Register(LAI_GROUP_PLAYER);
	LAi_group_SetPermanent(LAI_GROUP_PLAYER);
	LAi_group_SetLookRadius(LAI_GROUP_PLAYER, LAI_GROUP_PLA_LOOK);
	LAi_group_SetHearRadius(LAI_GROUP_PLAYER, LAI_GROUP_PLA_HEAR);
	LAi_group_SetSayRadius(LAI_GROUP_PLAYER, LAI_GROUP_PLA_SAY);
	LAi_group_SetPriority(LAI_GROUP_PLAYER, LAI_GROUP_PPLAYER);
	// BOAL 020804 Группа игрока  OWN
	LAi_group_Register(LAI_GROUP_PLAYER_OWN);
	LAi_group_SetPermanent(LAI_GROUP_PLAYER_OWN);
	LAi_group_SetRelation(LAI_GROUP_PLAYER_OWN, LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
	LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, LAI_GROUP_PLAYER_OWN, LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
	LAi_group_SetLookRadius(LAI_GROUP_PLAYER_OWN, LAI_GROUP_PLA_LOOK);
	LAi_group_SetHearRadius(LAI_GROUP_PLAYER_OWN, LAI_GROUP_PLA_HEAR);
	LAi_group_SetSayRadius(LAI_GROUP_PLAYER_OWN, LAI_GROUP_PLA_SAY);
	LAi_group_SetPriority(LAI_GROUP_PLAYER_OWN, LAI_GROUP_PPLAYER);
	
	LAi_group_Register("ENGLAND_CITIZENS");
	LAi_group_SetPermanent("ENGLAND_CITIZENS");
	LAi_group_SetLookRadius("ENGLAND_CITIZENS", LAI_GROUP_GRD_LOOK);
	LAi_group_SetHearRadius("ENGLAND_CITIZENS", LAI_GROUP_GRD_HEAR);
	LAi_group_SetSayRadius("ENGLAND_CITIZENS", LAI_GROUP_GRD_SAY);	
	LAi_group_SetPriority("ENGLAND_CITIZENS", LAI_GROUP_PGUARDS);
	LAi_group_SetAlarmReaction("ENGLAND_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmDown("ENGLAND_CITIZENS", LAI_GROUP_PLAYER, 0.02);

	LAi_group_Register("FRANCE_CITIZENS");
	LAi_group_SetPermanent("FRANCE_CITIZENS");
	LAi_group_SetLookRadius("FRANCE_CITIZENS", LAI_GROUP_GRD_LOOK);
	LAi_group_SetHearRadius("FRANCE_CITIZENS", LAI_GROUP_GRD_HEAR);
	LAi_group_SetSayRadius("FRANCE_CITIZENS", LAI_GROUP_GRD_SAY);
	LAi_group_SetPriority("FRANCE_CITIZENS", LAI_GROUP_PGUARDS);
	LAi_group_SetAlarmReaction("FRANCE_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmDown("FRANCE_CITIZENS", LAI_GROUP_PLAYER, 0.02);

	LAi_group_Register("SPAIN_CITIZENS");
	LAi_group_SetPermanent("SPAIN_CITIZENS");
	LAi_group_SetLookRadius("SPAIN_CITIZENS", LAI_GROUP_GRD_LOOK);
	LAi_group_SetHearRadius("SPAIN_CITIZENS", LAI_GROUP_GRD_HEAR);
	LAi_group_SetSayRadius("SPAIN_CITIZENS", LAI_GROUP_GRD_SAY);
	LAi_group_SetPriority("SPAIN_CITIZENS", LAI_GROUP_PGUARDS);
	LAi_group_SetAlarmReaction("SPAIN_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmDown("SPAIN_CITIZENS", LAI_GROUP_PLAYER, 0.02);

	LAi_group_Register("HOLLAND_CITIZENS");
	LAi_group_SetPermanent("HOLLAND_CITIZENS");
	LAi_group_SetLookRadius("HOLLAND_CITIZENS", LAI_GROUP_GRD_LOOK);
	LAi_group_SetHearRadius("HOLLAND_CITIZENS", LAI_GROUP_GRD_HEAR);
	LAi_group_SetSayRadius("HOLLAND_CITIZENS", LAI_GROUP_GRD_SAY);
	LAi_group_SetPriority("HOLLAND_CITIZENS", LAI_GROUP_PGUARDS);
	LAi_group_SetAlarmReaction("HOLLAND_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmDown("HOLLAND_CITIZENS", LAI_GROUP_PLAYER, 0.02);

	LAi_group_Register("PIRATE_CITIZENS");
	LAi_group_SetPermanent("PIRATE_CITIZENS");
	LAi_group_SetLookRadius("PIRATE_CITIZENS", LAI_GROUP_GRD_LOOK);
	LAi_group_SetHearRadius("PIRATE_CITIZENS", LAI_GROUP_GRD_HEAR);
	LAi_group_SetSayRadius("PIRATE_CITIZENS", LAI_GROUP_GRD_SAY);
	LAi_group_SetPriority("PIRATE_CITIZENS", LAI_GROUP_PGUARDS);
	LAi_group_SetAlarmReaction("PIRATE_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmDown("PIRATE_CITIZENS", LAI_GROUP_PLAYER, 0.02);

	//Группа охраников
	/*LAi_group_Register(LAI_GROUP_GUARDS);
	LAi_group_SetLookRadius(LAI_GROUP_GUARDS, LAI_GROUP_GRD_LOOK);
	LAi_group_SetHearRadius(LAI_GROUP_GUARDS, LAI_GROUP_GRD_HEAR);
	LAi_group_SetSayRadius(LAI_GROUP_GUARDS, LAI_GROUP_GRD_SAY);
	LAi_group_SetPriority(LAI_GROUP_PLAYER, LAI_GROUP_PGUARDS);*/

	//Группа актёров
	LAi_group_Register(LAI_GROUP_ACTOR);
	LAi_group_SetPermanent(LAI_GROUP_ACTOR);
	LAi_group_SetLookRadius(LAI_GROUP_GUARDS, LAI_GROUP_ACT_LOOK);
	LAi_group_SetHearRadius(LAI_GROUP_GUARDS, LAI_GROUP_ACT_HEAR);
	LAi_group_SetSayRadius(LAI_GROUP_GUARDS, LAI_GROUP_ACT_SAY);
	LAi_group_SetPriority(LAI_GROUP_PLAYER, LAI_GROUP_PDEFAULT);
	//Группа губернатора
	/*LAi_group_Register(LAI_GROUP_HUBER);
	LAi_group_SetLookRadius(LAI_GROUP_GUARDS, LAI_GROUP_HUB_LOOK);
	LAi_group_SetHearRadius(LAI_GROUP_GUARDS, LAI_GROUP_HUB_HEAR);
	LAi_group_SetSayRadius(LAI_GROUP_GUARDS, LAI_GROUP_HUB_SAY);
	LAi_group_SetPriority(LAI_GROUP_PLAYER, LAI_GROUP_PCITIZENS);*/
	
	//Группа монстров
	LAi_group_Register(LAI_GROUP_MONSTERS);
	LAi_group_SetPermanent(LAI_GROUP_MONSTERS);
	LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_SetLookRadius(LAI_GROUP_MONSTERS, LAI_GROUP_MNS_LOOK);
	LAi_group_SetHearRadius(LAI_GROUP_MONSTERS, LAI_GROUP_MNS_HEAR);
	LAi_group_SetSayRadius(LAI_GROUP_MONSTERS, LAI_GROUP_MNS_SAY);
	LAi_group_SetPriority(LAI_GROUP_PLAYER, 0);
	
	// Группа монстров Ксочитэма
	LAi_group_Register("KSOCHITAM_MONSTERS");
	LAi_group_SetPermanent("KSOCHITAM_MONSTERS");
	LAi_group_SetRelation("KSOCHITAM_MONSTERS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_SetLookRadius("KSOCHITAM_MONSTERS", LAI_GROUP_MNS_LOOK);
	LAi_group_SetHearRadius("KSOCHITAM_MONSTERS", LAI_GROUP_MNS_HEAR);
	LAi_group_SetSayRadius("KSOCHITAM_MONSTERS", LAI_GROUP_MNS_SAY);
	LAi_group_SetPriority(LAI_GROUP_PLAYER, 0);
	
	// Группа индейцев ица
	LAi_group_Register("ITZA");
	LAi_group_SetPermanent("ITZA");
	LAi_group_SetLookRadius("ITZA", LAI_GROUP_GRD_LOOK);
	LAi_group_SetHearRadius("ITZA", LAI_GROUP_GRD_HEAR);
	LAi_group_SetSayRadius("ITZA", LAI_GROUP_GRD_SAY);
	LAi_group_SetPriority(LAI_GROUP_PLAYER, 0);
	
	// группы LSC
	LAi_group_Register("LSC_NARVAL");
	LAi_group_SetPermanent("LSC_NARVAL");
	LAi_group_SetLookRadius("LSC_NARVAL", LAI_GROUP_GRD_LOOK);
	LAi_group_SetHearRadius("LSC_NARVAL", LAI_GROUP_GRD_HEAR);
	LAi_group_SetSayRadius("LSC_NARVAL", LAI_GROUP_GRD_SAY);
	LAi_group_SetPriority("LSC_NARVAL", LAI_GROUP_PGUARDS);
	LAi_group_SetAlarmReaction("LSC_NARVAL", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmDown("LSC_NARVAL", LAI_GROUP_PLAYER, 0.02);
	LAi_group_SetAlarmReaction("LSC_NARVAL", LAI_GROUP_ACTOR, LAI_GROUP_NEITRAL, LAI_GROUP_NEITRAL);
	
	LAi_group_Register("LSC_RIVADOS");
	LAi_group_SetPermanent("LSC_RIVADOS");
	LAi_group_SetLookRadius("LSC_RIVADOS", LAI_GROUP_GRD_LOOK);
	LAi_group_SetHearRadius("LSC_RIVADOS", LAI_GROUP_GRD_HEAR);
	LAi_group_SetSayRadius("LSC_RIVADOS", LAI_GROUP_GRD_SAY);
	LAi_group_SetPriority("LSC_RIVADOS", LAI_GROUP_PGUARDS);
	LAi_group_SetAlarmReaction("LSC_RIVADOS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmDown("LSC_RIVADOS", LAI_GROUP_PLAYER, 0.02);
	LAi_group_SetAlarmReaction("LSC_RIVADOS", LAI_GROUP_ACTOR, LAI_GROUP_NEITRAL, LAI_GROUP_NEITRAL);
	
	LAi_group_Register("LSC_SHARK");
	LAi_group_SetPermanent("LSC_SHARK");
	LAi_group_SetLookRadius("LSC_SHARK", LAI_GROUP_GRD_LOOK);
	LAi_group_SetHearRadius("LSC_SHARK", LAI_GROUP_GRD_HEAR);
	LAi_group_SetSayRadius("LSC_SHARK", LAI_GROUP_GRD_SAY);
	LAi_group_SetPriority("LSC_SHARK", LAI_GROUP_PGUARDS);
	LAi_group_SetAlarmReaction("LSC_SHARK", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmDown("LSC_SHARK", LAI_GROUP_PLAYER, 0.02);
	LAi_group_SetAlarmReaction("LSC_SHARK", LAI_GROUP_ACTOR, LAI_GROUP_NEITRAL, LAI_GROUP_NEITRAL);
	
	LAi_group_Register("LSC_CITIZEN");
	LAi_group_SetPermanent("LSC_CITIZEN");
	LAi_group_SetLookRadius("LSC_CITIZEN", LAI_GROUP_GRD_LOOK);
	LAi_group_SetHearRadius("LSC_CITIZEN", LAI_GROUP_GRD_HEAR);
	LAi_group_SetSayRadius("LSC_CITIZEN", LAI_GROUP_GRD_SAY);
	LAi_group_SetPriority("LSC_CITIZEN", LAI_GROUP_PGUARDS);
	LAi_group_SetAlarmReaction("LSC_CITIZEN", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmDown("LSC_CITIZEN", LAI_GROUP_PLAYER, 0.02);
	LAi_group_SetAlarmReaction("LSC_CITIZEN", LAI_GROUP_ACTOR, LAI_GROUP_NEITRAL, LAI_GROUP_NEITRAL);
	//Отношения	
	//giards
	//LAi_group_SetRelation(LAI_GROUP_GUARDS, LAI_DEFAULT_GROUP, LAI_GROUP_FRIEND);
	//LAi_group_SetAlarmReaction(LAI_GROUP_GUARDS, LAI_DEFAULT_GROUP, LAI_GROUP_FRIEND, LAI_GROUP_FRIEND);
	//LAi_group_SetRelation(LAI_GROUP_GUARDS, LAI_GROUP_HUBER, LAI_GROUP_FRIEND);
	//LAi_group_SetAlarmReaction(LAI_GROUP_GUARDS, LAI_GROUP_HUBER, LAI_GROUP_FRIEND, LAI_GROUP_FRIEND);
	//huber
	//LAi_group_SetRelation(LAI_GROUP_HUBER, LAI_DEFAULT_GROUP, LAI_GROUP_FRIEND);
	//LAi_group_SetAlarmReaction(LAI_GROUP_HUBER, LAI_DEFAULT_GROUP, LAI_GROUP_FRIEND, LAI_GROUP_FRIEND);
	//actor
	LAi_group_SetRelation(LAI_GROUP_ACTOR, LAI_DEFAULT_GROUP, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation(LAI_GROUP_ACTOR, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation(LAI_GROUP_ACTOR, LAI_GROUP_HUBER, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmReaction(LAI_GROUP_ACTOR, LAI_DEFAULT_GROUP, LAI_GROUP_NEITRAL, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmReaction(LAI_GROUP_ACTOR, LAI_GROUP_GUARDS, LAI_GROUP_NEITRAL, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmReaction(LAI_GROUP_ACTOR, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmReaction(LAI_GROUP_ACTOR, LAI_GROUP_HUBER, LAI_GROUP_NEITRAL, LAI_GROUP_NEITRAL);
	//player
	LAi_group_SetRelation(LAI_GROUP_PLAYER, LAI_DEFAULT_GROUP, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, LAI_DEFAULT_GROUP, LAI_GROUP_ENEMY, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, LAI_GROUP_GUARDS, LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
	LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, LAI_GROUP_HUBER, LAI_GROUP_ENEMY, LAI_GROUP_NEITRAL);
	//Востановим отношения
	SendMessage(&LAi_grp_relations, "s", "LoadDataRelations");
	//Учтём прошедшее время
	if(LAi_restoreStates)
	{
		SendMessage(&LAi_grp_relations, "s", "RestoreStates");
	}
	return true;
}

//Освобождение ресурсов
void LAi_group_Release()
{
	DeleteAttribute(&LAi_grp_relations, "quests");
	LAi_group_ClearAllTargets();
	//  boal fix 291105 - это тормоза, тк мусора много, но убирать низя, проблемы с запоминанием обид
	SendMessage(&LAi_grp_relations, "s", "SaveData");
	//Удаляем объект групп
	DeleteClass(&LAi_grp_relations);
	
	LAi_group_Clean(); // mitrokosta сборка мусора
}

// Не очищать группу при отсутствии в ней персонажей
void LAi_group_SetPermanent(string sName) {
	LAi_grp_relations.permanent.(sName) = true;
}

// Надо ли чистить группу?
bool LAi_group_IsPermanent(string sName) {
	if (sName == "" || CheckAttribute(&LAi_grp_relations, "permanent." + sName)) {
		return true;
	}
	
	return false;
}

// Чистка пустых групп
void LAi_group_Clean() {
	object oGrp;
	aref arData, arRel;
	ref chref, rGrp;
	int i, j, nRel, nChar;
	string sName, relName;
	
	makearef(arData, LAi_grp_relations.savedata);
	makeref(rGrp, oGrp);
	
	// первый проход - запоминаем все группы
	nRel = GetAttributesNum(arData);
	for (i = 0; i < nRel; i++) {
		arRel = GetAttributeN(arData, i);
		
		sName = arRel.name1;
		if (!LAi_group_IsPermanent(sName)) {
			rGrp.(sName) = true;
		}
		
		sName = arRel.name2;
		if (!LAi_group_IsPermanent(sName)) {
			rGrp.(sName) = true;
		}
	}
	
	// второй проход - ищем непустые
	nChar = GetArraySize(&characters);
	for (i = 0; i < nChar; i++) {
		makeref(chref, characters[i]);
		if (CheckAttribute(chref, "chr_ai.group") && chref.chr_ai.group != "") {
			DeleteAttribute(rGrp, chref.chr_ai.group);
			//trace("Group " + chref.chr_ai.group + " is not empty, it has " + chref.id + ", skipping");
		}
	}
	
	// третий проход - удаляем отношения между пустыми группами
	bool bDelete;
	
	for (i = 0; i < nRel; i++) {
		arRel = GetAttributeN(arData, i);
		relName = GetAttributeName(arRel);
		bDelete = false;
		
		if (!LAi_group_IsPermanent(arRel.name1) && CheckAttribute(rGrp, arRel.name1)) {
			bDelete = true;
		}
		
		if (!LAi_group_IsPermanent(arRel.name2) && CheckAttribute(rGrp, arRel.name2)) {
			bDelete = true;
		}
		
		if (bDelete) {
			//trace("Deleted group relation " + relName + " between " + arRel.name1 + " and " + arRel.name2);
			DeleteAttribute(arData, relName);
			i--;
			nRel--;
		}
	}
}

void LAi_group_SaveInfo()
{
	SendMessage(&LAi_grp_relations, "s", "SaveData");
}

//------------------------------------------------------------------------------------------
//Регистрация новой группы, установка общих параметров
//------------------------------------------------------------------------------------------

//Регистрация новой группы
void LAi_group_Register(string groupName)
{
	SendMessage(&LAi_grp_relations, "ss", "RegistryGroup", groupName);
	LAi_group_SetLookRadius(groupName, LAI_GROUP_DEF_LOOK);
	LAi_group_SetHearRadius(groupName, LAI_GROUP_DEF_HEAR);
	LAi_group_SetSayRadius(groupName, LAI_GROUP_DEF_SAY);
}

void LAi_group_Delete(string groupName)
{
	SendMessage(&LAi_grp_relations, "ss", "ReleaseGroup", groupName);
}


//Установить для группы радиус видимости
void LAi_group_SetLookRadius(string groupName, float radius)
{
	SendMessage(&LAi_grp_relations, "ssf", "SetGroupLook", groupName, radius);
}

//Установить для группы радиус слышимости
void LAi_group_SetHearRadius(string groupName, float radius)
{
	SendMessage(&LAi_grp_relations, "ssf", "SetGroupHear", groupName, radius);
}

//Установить для группы радиус сообщения
void LAi_group_SetSayRadius(string groupName, float radius)
{
	SendMessage(&LAi_grp_relations, "ssf", "SetGroupSay", groupName, radius);
}

//Установить для группы приоритет
void LAi_group_SetPriority(string groupName, int priority)
{
	SendMessage(&LAi_grp_relations, "ssl", "SetGroupPriority", groupName, priority);
}

//Установить уровень тревоги 0..1
void LAi_group_SetAlarm(string group1, string group2, float level)
{
	SendMessage(&LAi_grp_relations, "sssf", "SetAlarm", group1, group2, level);
}

//Установить скорость убывания тревоги ед/сек
void LAi_group_SetAlarmDown(string group1, string group2, float down)
{
	SendMessage(&LAi_grp_relations, "sssf", "SetAlarmDown", group1, group2, down);
}


//------------------------------------------------------------------------------------------
//Перемещение персонажа в группы
//------------------------------------------------------------------------------------------

//Переместить персонажа в новую группу
void LAi_group_MoveCharacter(aref chr, string groupName)
{
	chr.chr_ai.group = groupName;
	SendMessage(&LAi_grp_relations, "sis", "MoveChr", chr, groupName);	
}

//------------------------------------------------------------------------------------------
//Отношения групп
//------------------------------------------------------------------------------------------

//Установить отношения между группами
void LAi_group_SetRelation(string group1, string group2, string curRelation)
{
	if (group1 != group2) // boal fix
	{
		SendMessage(&LAi_grp_relations, "ssss", "SetRelation", group1, group2, curRelation);
	}
}

//Установить отношения между группами при активации тревоги и после
void LAi_group_SetAlarmReaction(string group1, string group2, string actRelation, string relRelation)
{
    if (group1 != group2) // boal fix
    {
		SendMessage(&LAi_grp_relations, "sssss", "SetAlarmReaction", group1, group2, actRelation, relRelation);
	}
}

//Натравить друг на друга 2 группы
void LAi_group_FightGroups(string group1, string group2, bool asignWarriarType)
{
    if (group1 != group2) // boal fix
    {
		LAi_group_FightGroupsEx(group1, group2, asignWarriarType, -1, -1, true, false);
	}
}

//Натравить друг на друга 2 группы, с возможной установкой командиров
void LAi_group_FightGroupsEx(string group1, string group2, bool asignWarriarType, int commander1, int commander2, bool isStay, bool isDialog)
{
    if (group1 == group2) // boal fix
    {
        return;
    }
	//Укажем что обновление надо провести немедленно
	SendMessage(&LAi_grp_relations, "s", "ResetWaveTime");
	//Установим войнов типы персонажем
	if(asignWarriarType)
	{
		for(int i = 0; i < LAi_numloginedcharacters; i++)
		{
			int idx = LAi_loginedcharacters[i];
			if(idx >= 0)
			{
				//Пропустим главного персонажа или офицера
				if(idx == nMainCharacterIndex) continue;
				for(int j = 1; j < 4; j++)
				{
					if(GetOfficersIndex(pchar, j) == idx) break;
				}
				if(j < 4) continue;
				//Проверяем попадание персонажа в группу
				ref chr = &Characters[idx];
				if(CheckAttribute(chr, "chr_ai.group"))
				{
					bool selected = false;
					bool isOne;
					if(chr.chr_ai.group == group1)
					{
						selected = true;
						isOne = true;
					}else{
						if(chr.chr_ai.group == group2)
						{
							selected = true;
							isOne = false;
						}
					}
					if(selected)
					{
						LAi_SetWarriorTypeNoGroup(chr);
						LAi_warrior_SetStay(chr, isStay);
						LAi_warrior_DialogEnable(chr, isDialog);
						if(isOne)
						{
							if(commander1 >= 0)
							{
								LAi_warrior_SetCommander(chr, &Characters[commander1]);
							}
							LAi_group_MoveCharacter(chr, group1);
						}else{
							if(commander2 >= 0)
							{
								LAi_warrior_SetCommander(chr, &Characters[commander2]);
							}
							LAi_group_MoveCharacter(chr, group2);
						}
					}
				}
			}
		}
	}
	//Настроим группы
	LAi_group_SetRelation(group1, group2, LAI_GROUP_ENEMY);
	LAi_group_SetHearRadius(group1, 40000000.0);
	LAi_group_SetSayRadius(group1, 40000000.0);
	LAi_group_SetHearRadius(group2, 40000000.0);	
	LAi_group_SetSayRadius(group2, 40000000.0);
}

//вывести отладочную информацию о кол-ве групп
void LAi_group_GetDbgInfo()
{
	SendMessage(&LAi_grp_relations, "s", "GetDbgInfo");
}

void LAi_group_NotFightPlayerVSGroup(string group2)
{
	LAi_group_SetHearRadius(LAI_GROUP_PLAYER, LAI_GROUP_PLA_HEAR);
	LAi_group_SetSayRadius(LAI_GROUP_PLAYER, LAI_GROUP_PLA_SAY);
	LAi_group_SetHearRadius(group2, LAI_GROUP_DEF_HEAR);	
	LAi_group_SetSayRadius(group2, LAI_GROUP_DEF_SAY);
}

//------------------------------------------------------------------------------------------
//Цели
//------------------------------------------------------------------------------------------

//Выбрать цель для данного персонажа
int LAi_group_GetTarget(aref chr)
{
	int index = -1;
	if(SendMessage(&LAi_grp_relations, "sie", "GetTrg", chr, &index) == 0)
	{
		index = -1;
	}
	else
	{
	    if (!LAi_group_IsEnemy(chr, &characters[index]))  // boal fix 19.08.06 ищет любых вооруженных НПС,  а нужно врагов
		{
		    index = -1;
		}
	}
	/*        // to_do del
	if(index != -1)
	{
		if(characters[index].id == pchar.id)
		{
			if(LAi_grp_alarmactive != true)
			{
				index = -1;
			}
		}
	}  */

	return index;
}

//Проверить цель
bool LAi_group_ValidateTarget(aref chr, aref trg)
{	
	return (SendMessage(&LAi_grp_relations, "sii", "VldTrg", chr, trg) != 0);
}

//Враг ли данный персонаж
bool LAi_group_IsEnemy(aref chr, aref trg)
{
	return (SendMessage(&LAi_grp_relations, "sii", "IsEnemy", chr, trg) != 0);
}

//------------------------------------------------------------------------------------------
//Реакция на атаку
//------------------------------------------------------------------------------------------

//Реакция групп на атаку attack->hit
bool LAi_group_Attack(aref attack, aref hit)
{
	if(attack.chr_ai.group == hit.chr_ai.group)
	{
		//Своих игнорируем
		return false;
	}
	//Jason: придется помирить все кланы, однако...
	if(CheckAttribute(attack, "LSC_clan") && CheckAttribute(hit, "LSC_clan"))
	{
		return false;
	}
	//Натравим друг на друга
	SendMessage(&LAi_grp_relations, "sss", "Attack", attack.chr_ai.group, hit.chr_ai.group);
	//Добавляем врага
	SendMessage(&LAi_grp_relations, "siif", "AddTarget", hit, attack, 10.0 + rand(10));
	return true;
}
//eddy.Можно пользоваться этим методом для непостоянного стравливания. Для групп горожан юзать только его!
bool LAi_group_AttackGroup(string attack, string hit)
{
	//Натравим друг на друга
	SendMessage(&LAi_grp_relations, "sss", "Attack", attack, hit);
	return true;
}

//Обновить список врагов персонажа
void LAi_group_UpdateTargets(aref chr)
{
	SendMessage(&LAi_grp_relations, "si", "UpdChrTrg", chr);
}

/*
void LAI_group_SetRelationWithAllStock(string targetgroup, string rel)
{
	string citgroup = GetCurrentCitizenGroup();
	string solgroup = GetCurrentSoldierGroup();
	if(citgroup != LAI_DEFAULT_GROUP) LAi_group_SetRelation(LAI_DEFAULT_GROUP, targetgroup, rel);
	if(solgroup != LAI_GROUP_GUARDS) LAi_group_SetRelation(LAI_GROUP_GUARDS, targetgroup, rel);
	LAi_group_SetRelation(citgroup, targetgroup, rel);				
	LAi_group_SetRelation(solgroup, targetgroup, rel);
	LAi_group_SetRelation(LAI_GROUP_PLAYER, targetgroup, rel);
	LAi_group_SetRelation(LAI_GROUP_MONSTERS, targetgroup, rel);
}
*/
//------------------------------------------------------------------------------------------
//Утилитные
//------------------------------------------------------------------------------------------

//Удалить все цели из списков
void LAi_group_ClearAllTargets()
{
	SendMessage(&LAi_grp_relations, "s", "ClearAllTargets");
}

//Получить значение тревоги для игрока
float LAi_group_GetPlayerAlarm()
{
	return LAi_grp_playeralarm;
}

//Активна ли тревога для игрока
bool LAi_group_IsActivePlayerAlarm()
{
	return LAi_grp_alarmactive;
}

//Установить квест на убивание группы
void LAi_group_SetCheck(string groupName, string quest)
{
	//Найдём свободное поле
	aref quests;
	makearef(quests, LAi_grp_relations.quests);
	int num = GetAttributesNum(quests);
	string atr = "q";
	for(int i = 0; i < num + 10; i++)
	{
		atr = "q" + i;
		if(!CheckAttribute(quests, atr)) break;
	}
	//Заполним
	quests.(atr).group = groupName;
	quests.(atr).quest = quest;
}

// Warship 18.08.09 Проверка убийства группы с вызовом функции
void LAi_group_SetCheckFunction(String _groupName, String _function)
{
	//Найдём свободное поле
	aref quests;
	makearef(quests, LAi_grp_relations.quests);
	int num = GetAttributesNum(quests);
	String atr = "q";
	
	for(int i = 0; i < num + 10; i++)
	{
		atr = "q" + i;
		if(!CheckAttribute(quests, atr)) break;
	}
	
	//Заполним
	quests.(atr).group = _groupName;
	quests.(atr).function = _function;
}

//Установить событие на убивание группы
void LAi_group_SetCheckEvent(string groupName)
{
	//Найдём свободное поле
	aref quests;
	makearef(quests, LAi_grp_relations.quests);
	int num = GetAttributesNum(quests);
	string atr = "q";
	for(int i = 0; i < num + 10; i++)
	{
		atr = "q" + i;
		if(!CheckAttribute(quests, atr)) break;
	}
	//Заполним
	quests.(atr).group = groupName;
}


//Убрать квест на убивание группы
void LAi_group_RemoveCheck(string groupName)
{
	//Найдём свободное поле
	aref quests;
	makearef(quests, LAi_grp_relations.quests);
	int num = GetAttributesNum(quests);
	for(int i = 0; i < num; i++)
	{
		aref atr = GetAttributeN(&quests, i);
		if(atr.group == groupName)
		{
			//Удалим
			DeleteAttribute(&quests, GetAttributeName(GetAttributeN(&quests, i)));
			i = -1;
			num = GetAttributesNum(&quests);
		}		
	}
}

//Проверить квест на убивание группы
void LAi_group_CheckGroupQuest(aref chr)
{
	//Получим ветку с квестами
	aref quests;
	makearef(quests, LAi_grp_relations.quests);
	int num = GetAttributesNum(&quests);
	String function;
	
	if(num <= 0) return;
	//Проверим остальных персонажей в данной группе
	if(!CheckAttribute(chr, "chr_ai.group"))
	{
		Trace("CheckGroupQuest: Character <" + chr.id + "> can't have field chr_ai.group");
		return;
	}
	string group = chr.chr_ai.group;
	int chridx = sti(chr.index);
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int idx = LAi_loginedcharacters[i];
		if(idx >= 0)
		{
			if(idx != chridx)
			{
				ref ch = &Characters[idx];
				if(!CheckAttribute(ch, "chr_ai.group")) ch.chr_ai.group = LAI_DEFAULT_GROUP;
				if(group == ch.chr_ai.group)
				{
					//Есть ещё живые в этой группе
					return;
				}
			}
		}
	}
	//Последний из магикан...
	for(i = 0; i < num; i++)
	{
		aref atr = GetAttributeN(&quests, i);
		if(atr.group == group)
		{
			//Нашли квест, запустим его на исполнение
			if(CheckAttribute(atr, "quest"))
			{
				LAi_QuestDelay(atr.quest, 0.000001);
			}
			else
			{
				// Warship 18.08.09 Вызов функции
				if(CheckAttribute(atr, "function"))
				{
					function = atr.function;
					call function(function); // В параметре - название самой функции
				}
				else
				{
				PostEvent("LAi_event_GroupKill", 1, "s", group);
			}
			}
			string atname = GetAttributeName(GetAttributeN(&quests, i));
			//Теперь удалим
			DeleteAttribute(&quests, atname);
			i = -1;
			num = GetAttributesNum(&quests);
		}
	}
}


//------------------------------------------------------------------------------------------
//Ответная реакция на запросы
//------------------------------------------------------------------------------------------

//Обновление аларма, вызывается на каждом кадре
#event_handler("CharacterGroup_UpdateAlarm", "LAi_group_UpdateAlarm");
void LAi_group_UpdateAlarm()
{
	LAi_grp_playeralarm = GetEventData();
	LAi_grp_alarmactive = GetEventData();

	/*if(CheckAttribute(pchar, "sneak.success"))
	{
		if(sti(pchar.sneak.success) == 1)
		{
			LAi_grp_playeralarm = 0.0;
			LAi_grp_alarmactive = false;
		}
	}  */

	Sound_OnAlarm(LAi_grp_alarmactive);
}