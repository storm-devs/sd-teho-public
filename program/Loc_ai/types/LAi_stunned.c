/*
Тип: Оглушенный

	Используемые шаблоны:
		stay
		dialog
		ani
*/

#define LAI_TYPE_STUNNED		"stunned"
#define LAI_GROUP_STUNNED		"stunned"

void LAi_Stunned_StunCharacter(aref chr, float duration, bool resumeoldtype)
{
	string snd = "";
	if (CheckAttribute(chr, "nodisarm" )) return;
	if (IsMainCharacter(chr)) return;
	if (LAi_IsBoardingProcess() && CheckAttribute(chr, "chr_ai.group") && chr.chr_ai.group !=  LAI_GROUP_PLAYER) return;

	if(!CheckAttribute(chr, "stuntime"))
	{
		aref achr, astun;
		chr.stuntime.old_type = chr.chr_ai.type; 
		if(!CheckAttribute(chr, "first_oldtype")) chr.first_oldtype = chr.chr_ai.type; 
		if(chr.chr_ai.type == LAI_TYPE_ACTOR) 
		{
			chr.stuntime.actor.type = "";
			makearef(astun, chr.stuntime.actor.type);
			makearef(achr, chr.chr_ai.type);
			CopyAttributes(&astun, &achr);
			
			chr.stuntime.actor.tmpl = "";
			makearef(astun, chr.stuntime.actor.tmpl);
			makearef(achr, chr.chr_ai.tmpl);
			CopyAttributes(&astun, &achr);
			if(CheckAttribute(chr, "location.follower")) 
			{
				chr.stuntime.locfollow = chr.location.follower;
			}
		}
		LAi_SetStunnedTypeNoGroup(chr);	
		// сюды вставить звуки !!
		if(chr.sex == "woman")
		{
			//snd = "OBJECTS\Voices\dead\female\dead_wom2.wav";
		}
		else
		{
			//snd = "OBJECTS\Voices\dead\male\dead1.wav";
		}
		chr.stuntime.group = chr.chr_ai.group;
		LAi_Group_MoveCharacter(chr, LAI_GROUP_STUNNED);
		//LAI_group_SetRelationWithAllStock(LAI_GROUP_STUNNED, LAI_GROUP_NEITRAL);
	}
	chr.stuntime.duration = duration;
	chr.stuntime = locTmpTime;	
	if(resumeoldtype)
	{
		chr.stuntime.old_type_resume = true;
	}
	else DeleteAttribute(chr, "stuntime.old_type_resume");
	
	float x, y, z;
	GetCharacterPos(chr, &x, &y, &z);
	
	//LAi_CharacterPlaySound(chr, snd);
}

bool LAi_Stunned_AwakenCharacter(aref chr)
{
	if(!CheckAttribute(chr, "stuntime")) return false;		
	if(!CheckAttribute(chr,"stuntime.old_type_resume") && !CheckAttribute(chr, "stuntime.actor"))
	{
		if(!CheckAttribute(chr, "first_oldtype")) chr.first_oldtype = chr.stuntime.old_type; 
		LAi_SetCitizenTypeNoGroup(chr);
		chr.stunnewtype = true;
	} 
	else 
	{	
		if(chr.sex == "man" ) 
		{ 
			//CharacterPlayAction(chr, "Ground_StandUp"); 
			CharacterPlayAction(chr, ""); 
		}
		if(chr.sex == "woman")
		{ 
			CharacterPlayAction(chr, "idle_10"); 
		}		
	}
	
	if(!Lai_IsBoardingProcess()) PostEvent("LAi_StandsUp", 3750, "i", chr);
	else PostEvent("LAi_StandsUp", 3970, "i", chr);
	return true;
}

#event_handler("LAi_StandsUp", "LAi_StunnedStandsUp");
void LAi_StunnedStandsUp()
{
	aref chr = GetEventData();
	aref achr, astun;
	if(!CheckAttribute(chr,"stuntime.old_type_resume") && !CheckAttribute(chr, "stuntime.actor")) {  }
	else
	{
		string func;
		if(IsOfficer(chr) || bAbordageStarted) func = "LAi_Set" + chr.stuntime.old_type + "Type";
		else func = "LAi_Set" + chr.stuntime.old_type + "TypeNoGroup";
		call func(chr);
		if(CheckAttribute(chr, "stuntime.actor.type"))
		{
			DeleteAttribute(chr, "chr_ai.type");
			chr.chr_ai.type = "";
			makearef(astun, chr.stuntime.actor.type);
			makearef(achr, chr.chr_ai.type);
			CopyAttributes(&achr, &astun);
		}
		if(CheckAttribute(chr, "stuntime.actor.tmpl"))
		{
			DeleteAttribute(chr, "chr_ai.tmpl");
			chr.chr_ai.tmpl = "";
			makearef(astun, chr.stuntime.actor.tmpl);
			makearef(achr, chr.chr_ai.tmpl);
			CopyAttributes(&achr, &astun);
		}
		if(CheckAttribute(chr, "stuntime.locfollow")) 
		{
			chr.location.follower = chr.stuntime.locfollow;
		}
	}
	if(CheckAttribute(chr,"stuntime.group")) LAi_group_MoveCharacter(chr, chr.stuntime.group);			
	if(CheckAttribute(chr,"stuntime")) 
	{ 
		DeleteAttribute(chr,"stuntime"); 
	}
}

void LAi_type_stunned_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_STUNNED;
	LAi_tmpl_stay_InitTemplate(chr);
	//Установим анимацию персонажу
	LAi_SetDefaultStayAnimation(chr);
	BeginChangeCharacterActions(chr);

	if(chr.sex == "man") 
	{ 
		//CharacterPlayAction(chr, "Ground_SitDown"); 
		CharacterPlayAction(chr, ""); 
	}
	if(chr.sex == "woman") 
	{ 
		CharacterPlayAction(chr, "Afraid"); 
	}
	PostEvent("LAi_BecameStunned", 3500, "i", chr);		
}

#event_handler ("LAi_BecameStunned", "LAi_CharacterBecameStunned");
void LAi_CharacterBecameStunned()
{
	aref chr = GetEventData();
	CharacterPlayAction(chr, "");

	if(chr.sex != "woman")
	{
		chr.actions.idle.i1 	= "idle_1";
		chr.actions.idle.i2 	= "idle_2";
		chr.actions.idle.i3 	= "idle_3";
		chr.actions.idle.i4 	= "idle_4";
		chr.actions.idle.i5 	= "idle_5";
		chr.actions.idle.i6 	= "idle_6";
		chr.actions.idle.i7 	= "idle_7";
		chr.actions.idle.i8 	= "idle_8";
		chr.actions.idle.i9 	= "idle_9";
		chr.actions.idle.i10 	= "idle_10";
		chr.actions.idle.i11 	= "idle_11";

/*	
		chr.actions.idle.i1 = "Ground_sitting";
		chr.actions.idle.i2 = "Ground_sitting";
		chr.actions.idle.i3 = "Ground_sitting";
		chr.actions.dead.d1 = "Ground_Death";
*/		
	}
	else
	{
		chr.actions.idle.i1 = "Afraid";
		chr.actions.idle.i2 = "Afraid";
		chr.actions.idle.i3 = "Afraid";
		switch(rand(1))
		{
			case 0: chr.actions.dead.d1 = "death_afraid_1"; break;
			case 1: chr.actions.dead.d1 = "death_afraid_2"; break;
		}
	}
	EndChangeCharacterActions(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//Процессирование типа персонажа
void LAi_type_stunned_CharacterUpdate(aref chr, float dltTime)
{
	if( CheckAttribute(chr, "stuntime" )) 	
	{
		if( stf(chr.stuntime) + stf(chr.stuntime.duration) < locTmpTime || locTmpTime < 3 )
		{ 
			LAi_Stunned_AwakenCharacter(&chr); return; 
		}
	}

	int num = FindNearCharacters(chr, 5.0, -1.0, -1.0, 0.001, false, true);
	int idx;
	if(num > 0)
	{
		for(int i = 0; i < num; i++)
		{
			idx = sti(chrFindNearCharacters[i].index);
			if(LAi_group_IsEnemy(chr, &Characters[idx])) break;
		}
		if(i >= num)
		{
			if(chr.chr_ai.tmpl != LAI_TMPL_STAY)
			{
				LAi_tmpl_stay_InitTemplate(chr);
				LAi_SetDefaultDead(chr);
			}
		}	
	}
	else
	{
		if(chr.chr_ai.tmpl != LAI_TMPL_STAY)
		{
			LAi_tmpl_stay_InitTemplate(chr);
			LAi_SetDefaultDead(chr);
		}
	}
}

//Загрузка персонажа в локацию
bool LAi_type_stunned_CharacterLogin(aref chr)
{
	return true;
}

//Выгрузка персонажа из локацию
bool LAi_type_stunned_CharacterLogoff(aref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_stunned_TemplateComplite(aref chr, string tmpl)
{
}

//Сообщить о желании завести диалог
void LAi_type_stunned_NeedDialog(aref chr, aref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_stunned_CanDialog(aref chr, aref by)
{
	//Если уже говорим, то откажем
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY) return true;
	return false;
}

//Начать диалог
void LAi_type_stunned_StartDialog(aref chr, aref by)
{
	//Если мы пасивны, запускаем шаблон без времени завершения
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//Закончить диалог
void LAi_type_stunned_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
}

//Персонаж атаковал другого персонажа
void LAi_type_stunned_Attack(aref attack, aref enemy, float attackDmg, float hitDmg)
{
}

//Персонаж атоковал заблокировавшегося персонажа
void LAi_type_stunned_Block(aref attack, aref enemy, float attackDmg, float hitDmg)
{
}

//Персонаж выстрелил
void LAi_type_stunned_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}

//Персонаж атакован
void LAi_type_stunned_Attacked(aref chr, aref by)
{
}


