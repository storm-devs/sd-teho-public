/*
Тип: лежачий, всегда лежит, отвечает на диалоги, никогда не боится

	Используемые шаблоны:
		stay
		dialog
*/


#define LAI_TYPE_LAY		"lay"

//Инициализация
void LAi_type_lay_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_LAY;
	LAi_tmpl_stay_InitTemplate(chr);
	//Установим анимацию персонажу
	LAi_SetDefaultLayAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//Процессирование типа персонажа
void LAi_type_lay_CharacterUpdate(aref chr, float dltTime)
{
	string snd = "PEOPLE\snore.wav";
	if(!CheckAttribute(chr,"InDialog"))
	{
		if(rand(300) == 123) { LAi_CharacterPlaySound(chr, snd); }
		else
		{
			if(FindNearCharacters(chr, 2.5, -1.0, 30.0, 0.1, false, false) > 0)
			{
				if(rand(100) == 10) { LAi_CharacterPlaySound(chr, snd); }
			}
		}
	}
}

//Загрузка персонажа в локацию
bool LAi_type_lay_CharacterLogin(aref chr)
{
	return true;
}

//Выгрузка персонажа из локацию
bool LAi_type_lay_CharacterLogoff(aref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_lay_TemplateComplite(aref chr, string tmpl)
{
	LAi_tmpl_player_InitTemplate(chr);
}

//Сообщить о желании завести диалог
void LAi_type_lay_NeedDialog(aref chr, aref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_lay_CanDialog(aref chr, aref by)
{
	//Если уже говорим, то откажем
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return false;
	//Согласимся на диалог
	return true;
}

//Начать диалог
void LAi_type_lay_StartDialog(aref chr, aref by)
{
	//Если мы пасивны, запускаем шаблон без времени завершения
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_tmpl_SetActivatedDialog(chr, by);
	LAi_tmpl_dialog_NoAni(chr);
	chr.InDialog = true;
}

//Закончить диалог
void LAi_type_lay_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	if(CheckAttribute(chr,"InDialog")) DeleteAttribute(chr,"InDialog");
}

//Персонаж атаковал другого персонажа
void LAi_type_lay_Attack(aref attack, aref enemy, float attackDmg, float hitDmg)
{
}

//Персонаж атоковал заблокировавшегося персонажа
void LAi_type_lay_Block(aref attack, aref enemy, float attackDmg, float hitDmg)
{
}

//Персонаж выстрелил
void LAi_type_lay_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}


//Персонаж атакован
void LAi_type_lay_Attacked(aref chr, aref by)
{
	
}