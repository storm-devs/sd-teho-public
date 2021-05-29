/*
Тип:  сидящий на земле

	Используемые шаблоны:
		stay
		dialog
		ani
*/



#define LAI_TYPE_GROUNDSIT		"groundSit"


//Инициализация
void LAi_type_GroundSit_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_GROUNDSIT;
	LAi_tmpl_stay_InitTemplate(chr);
	//Установим анимацию персонажу
	//LAi_SetDefaultStayAnimation(chr);
	LAi_SetSitPoorAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//Процессирование типа персонажа
void LAi_type_GroundSit_CharacterUpdate(aref chr, float dltTime)
{
	int num = FindNearCharacters(chr, 5.0, -1.0, -1.0, 0.001, false, true);
	int idx;
	if(num > 0)
	{
		for(int i = 0; i < num; i++)
		{
			idx = sti(chrFindNearCharacters[i].index);
			if(LAi_group_IsEnemy(chr, &Characters[idx])) break;
		}
		if(i < num)
		{
			if(chr.chr_ai.tmpl != LAI_TMPL_ANI)
			{
				LAi_tmpl_ani_PlayAnimation(chr, "afraid", -1.0);
				LAi_SetAfraidDead(chr);
			}
		}else{
			if(chr.chr_ai.tmpl != LAI_TMPL_STAY)
			{
				LAi_tmpl_stay_InitTemplate(chr);
				LAi_SetDefaultDead(chr);
			}
		}
	}else{
		if(chr.chr_ai.tmpl != LAI_TMPL_DIALOG)
		{
			if(rand(500) == 123)
			{
				LAi_CharacterPlaySound(chr, "poorman");
			}
		}
		if(chr.chr_ai.tmpl != LAI_TMPL_STAY)
		{
			LAi_tmpl_stay_InitTemplate(chr);
			LAi_SetDefaultDead(chr);
		}
	}
}

//Загрузка персонажа в локацию
bool LAi_type_GroundSit_CharacterLogin(aref chr)
{
	return true;
}

//Выгрузка персонажа из локацию
bool LAi_type_GroundSit_CharacterLogoff(aref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_GroundSit_TemplateComplite(aref chr, string tmpl)
{
}

//Сообщить о желании завести диалог
void LAi_type_GroundSit_NeedDialog(aref chr, aref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_GroundSit_CanDialog(aref chr, aref by)
{
	//Если уже говорим, то откажем
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY) return true;
	//Согласимся на диалог
	return false;
}

//Начать диалог
void LAi_type_GroundSit_StartDialog(aref chr, aref by)
{
	//Если мы пасивны, запускаем шаблон без времени завершения
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//Закончить диалог
void LAi_type_GroundSit_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
}

//Персонаж выстрелил
void LAi_type_GroundSit_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}


//Персонаж атакован
void LAi_type_GroundSit_Attacked(aref chr, aref by)
{
	LAi_SetWarriorTypeNoGroup(chr);
}

