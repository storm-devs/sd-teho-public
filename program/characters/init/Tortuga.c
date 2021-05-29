
int CreateTortugaCharacters(int n)
{
	ref ch;
	
	///////////////////////////////////////////////////////////////////////////////
	// ОСНОВНЫЕ ПЕРСОНАЖИ
	///////////////////////////////////////////////////////////////////////////////

	makeref(ch,Characters[n]);			//Губернатор
	ch.id = "Tortuga_Mayor";
	ch.model	= "huber_6";
	ch.sex = "man";
	ch.name 	= "Francois";
    ch.lastname = "Levasseur";
	ch.City = "Tortuga";
	ch.location	= "Tortuga_townhall";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Mayor.c";
	ch.greeting = "fra_gov_common";
	ch.nation = FRANCE;
	//ch.quest.type = "hovernor";
	GiveItem2Character(ch, "blade_19");
	EquipCharacterbyItem(ch, "blade_19");
	GiveItem2Character(ch, "pistol4"); 
	EquipCharacterbyItem(ch, "pistol4");
	ch.rank = 42;
	SetSPECIAL(ch, 6, 5, 6, 6, 6, 10, 6);
    SetSelfSkill(ch, 100, 100, 100, 100, 100);
	ch.standUp = true; //вставать и нападать на врага
	LAi_SetHP(ch, 300+MOD_SKILL_ENEMY_RATE*40, 300+MOD_SKILL_ENEMY_RATE*40);
	ch.MultiFighter = 1.0+MOD_SKILL_ENEMY_RATE/10; // мультифайтер
	ch.SuperShooter = true; 
	ch.cirassId = Items_FindItemIdx("cirass1");
	TakeNItems(ch, "potion2", 3+MOD_SKILL_ENEMY_RATE);
	TakeNItems(ch, "potion3", 5);
	GiveItem2Character(ch, "key_levasser"); 
	SelAllPerksToChar(ch, false);
	ch.SaveItemsForDead = true;
	ch.DontClearDead = true;
	LAi_SetHuberType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "FRANCE_CITIZENS");
	LAi_SetImmortal(ch, true);
	LAi_LoginInCaptureTown(ch, false);
	n = n + 1;

	makeref(ch,Characters[n]);			//Священик
	ch.id = "Tortuga_Priest";
	ch.model	= "priest_1";
	ch.model.animation	= "man";
	ch.sex = "man";
	ch.City = "Tortuga";
	ch.location	= "Tortuga_church";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_church.c";
	ch.greeting = "padre_2";
	ch.nation = FRANCE;
//	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetPriestType(ch);
	LAi_group_MoveCharacter(ch, "FRANCE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);		// ОФициантка
	ch.id = "Tortuga_waitress";
	ch.model	= "women_14";
	ch.sex = "woman";
	ch.City = "Tortuga";
	ch.location	= "Tortuga_tavern";
	ch.location.group = "waitress";
	ch.location.locator = "barmen";
	ch.Dialog.Filename = "Waitress_dialog.c";
	ch.greeting = "waitress";
	ch.nation = FRANCE;
	LAi_SetWaitressType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "FRANCE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Трактирщик
	ch.id = "Tortuga_tavernkeeper";
	ch.model	= "barmen_9";
	ch.greeting = "barmen_2";
	ch.sex = "man";
	ch.City = "Tortuga";
	ch.location	= "Tortuga_Tavern";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Tavern.c";
	ch.TavernMan = true;
	ch.nation = FRANCE;
	LAi_SetBarmanType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "FRANCE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;


	makeref(ch,Characters[n]);			//Торговец
	ch.id = "Tortuga_trader";
	ch.model	= "trader_9";
	ch.greeting = "store_2";
	ch.sex = "man";
	ch.City = "Tortuga";
	ch.location	= "Tortuga_Store";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Store.c";
	ch.quest.type = "trader";
	ch.nation = FRANCE;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "FRANCE_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;

	makeref(ch,Characters[n]);			//Корабел
	ch.id = "Tortuga_shipyarder";
	ch.model	= "shipowner_9";
	ch.greeting = "shipyarder_1";
	ch.sex = "man";
	ch.City = "Tortuga";
	ch.location	= "Tortuga_Shipyard";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Shipyard.c";
	ch.nation = FRANCE;
	ch.quest.shiping = "0";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, "topor_02");
	EquipCharacterbyItem(ch, GUN_COMMON); 
	EquipCharacterbyItem(ch, "topor_02"); 
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.standUp = true; //вставать и нападать на врага
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "FRANCE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Банкир
	ch.id		= "Tortuga_usurer";
	ch.model	= "banker_9";
	ch.sex = "man";
	ch.City = "Tortuga";
	ch.Merchant.type = "jeweller"; 
	ch.location	= "Tortuga_Bank";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Usurer_dialog.c";
	ch.nation = FRANCE;
	ch.greeting = "usurer_3";
	ch.quest.shiping = "0";
	ch.UsurerDeposit = 10000; // *1000 денег
	ch.money = USURER_MIN_MONEY + rand(USURER_NORM);
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "FRANCE_CITIZENS");
	n = n + 1;

	makeref(ch,Characters[n]);			//Начальник порта
	ch.id		= "Tortuga_PortMan";
	ch.model	= "citiz_2";
	ch.sex = "man";
	ch.City = "Tortuga";
	ch.location	= "Tortuga_PortOffice";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Portman.c";
	ch.nation = FRANCE;
	ch.greeting = "portman_3";
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "FRANCE_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;

	makeref(ch,Characters[n]);			//Хозяйка борделя
	ch.id		= "Tortuga_Hostess";
	ch.name		= "Janetta"
	ch.lastname = "";
	ch.model	= "maman_6";
	ch.model.animation = "woman_B";
	ch.sex = "woman";
	ch.City = "Tortuga";
	ch.location	= "Tortuga_SecBrRoom";
	ch.location.group = "goto";
	ch.location.locator = "goto8";
	ch.Dialog.Filename = "Common_Brothel.c";
	ch.nation = FRANCE;
	ch.greeting = "maman_2";
	ch.questChurch = ""; //флаг для пожертвований
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "FRANCE_CITIZENS");
	n = n + 1;

    makeref(ch,Characters[n]);
	ch.name 	= "Smuggler";
	ch.lastname = "";
	ch.id		= "Tortuga_Smuggler";
	ch.model    = "citiz_30";
	ch.sex      = "man";
	LAi_SetLoginTime(ch, 0.0, 24.0);
	ch.nation = PIRATE;
	GiveItem2Character(ch, BLADE_SABER);
	EquipCharacterbyItem(ch, BLADE_SABER);
	// посадим в генераторе
	ch.Dialog.Filename = "Smuggler Agent_dialog.c";
	LAi_SetSitType(ch);
	LAi_SetHP(ch, 80.0, 80.0);
	ch.greeting = "smuggler";
	n = n + 1;
	
	makeref(ch,Characters[n]);			//Смотритель маяка
	ch.id		= "Tortuga_Lightman";
	ch.model	= "keeper_5";
	ch.model.animation = "man_B";
	ch.sex = "man";
	ch.City = "Tortuga";
	ch.location = "Mayak6_Lighthouseroom";
	ch.location.group = "barmen";
	ch.location.locator = "bar2";
	ch.Dialog.Filename = "Common_lighthouse.c";
	ch.greeting = "lighthouseman_4";
	ch.Merchant = true;
	ch.Merchant.type = "lightman";
	ch.money = TRADER_MIN_MONEY + rand(TRADER_NORM);
	ch.nation = FRANCE;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "FRANCE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;
	
	return n;
}
