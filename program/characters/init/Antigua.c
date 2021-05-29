int CreateAntiguaCharacters(int n)
{
	ref ch;
	
	///////////////////////////////////////////////////////////////////////////////
	// ОСНОВНЫЕ ПЕРСОНАЖИ
	///////////////////////////////////////////////////////////////////////////////
    makeref(ch,Characters[n]);			//Персонаж который фиксит багу
	ch.id		= "Bug Fixer";
	ch.model	= "usurer_8";
	ch.sex = "man";
	ch.location	= "none";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Mayor.c";
	ch.nation = ENGLAND;
	ch.quest.type = "hovernor";
	ch.money = 100000; // boal test
	TakeNItems(ch, "bullet", 20);
	AddItems(ch, "GunPowder", 20);
	TakeNItems(ch, "potion2", 3);
	TakeNItems(ch, "mineral13", 3);
    TakeNItems(ch, "SpyGlass2", 1);
    TakeNItems(ch, "SpyGlass3", 1);
    TakeNItems(ch, "SpyGlass4", 1);
    TakeNItems(ch, "SpyGlass5", 1);
	LAi_SetHuberType(ch);
	LAi_RemoveLoginTime(ch);
	//LAi_group_MoveCharacter(ch, "NONE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;   // boal зачем рн тут не ведаю. Но, зная шаманство К3, пусть будет имено тут (те за номером 2)
	
	makeref(ch,Characters[n]);			//губернатор
	ch.id		= "SentJons_Mayor";
	ch.model	= "huber_10";
	ch.name 	= "Cristofer";
    ch.lastname = "Keynell";
	ch.sex = "man";
	ch.City = "SentJons";
	ch.greeting = "mayor_1";
	ch.location = "SentJons_townhall";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Mayor.c";
	ch.nation = ENGLAND;
	ch.quest.type = "hovernor";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, BLADE_LONG);
	EquipCharacterbyItem(ch, GUN_COMMON); 
	EquipCharacterbyItem(ch, BLADE_LONG); 
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.standUp = true; //вставать и нападать на врага
	LAi_SetImmortal(ch, true);
	LAi_SetHuberType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//денщик Фокса
	ch.id		= "BenjaminJons";
	ch.model	= "Addington";
	ch.name 	= "Benjamin";
    ch.lastname = "Johnes";
	ch.sex = "man";
	ch.City = "SentJons";
	ch.greeting = "soldier";
	ch.location = "SentJons_Roomtownhall";
	ch.location.group = "sit";
	ch.location.locator = "sit2";
	ch.Dialog.Filename = "quest\sharlie\terrapin.c";
	ch.dialog.currentnode = "BenjaminJons";
	ch.nation = ENGLAND;
	ch.quest.type = "hovernor";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, BLADE_LONG);
	EquipCharacterbyItem(ch, GUN_COMMON); 
	EquipCharacterbyItem(ch, BLADE_LONG); 
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.standUp = true; //вставать и нападать на врага
	LAi_SetHuberType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Священик
	ch.id		= "SentJons_Priest";
	ch.model	= "priest_2";
	ch.model.animation = "man";
	ch.sex = "man";
	ch.City = "SentJons";
	ch.location	= "SentJons_church";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_church.c";
	ch.greeting = "padre_1";
	ch.nation = ENGLAND;
//	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetPriestType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);		// ОФициантка
	ch.id		= "SentJons_waitress";
	ch.model	= "women_11";
	ch.sex = "woman";
	ch.City = "SentJons";
	ch.location	= "SentJons_tavern";
	ch.location.group = "waitress";
	ch.location.locator = "barmen";
	ch.Dialog.Filename = "Waitress_dialog.c";
	ch.greeting = "waitress";
	ch.nation = ENGLAND;
	LAi_SetWaitressType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Трактирщик
	ch.id		= "SentJons_tavernkeeper";
	ch.model	= "barmen_11";
	ch.sex = "man";
	ch.City = "SentJons";
	ch.location	= "SentJons_Tavern";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Tavern.c";
	ch.greeting = "barmen_1";
	ch.nation = ENGLAND;
	ch.TavernMan = true;
	LAi_SetBarmanType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Торговец
	ch.id		= "SentJons_trader";
	ch.model	= "trader_11";
	ch.greeting = "store_1";
	ch.sex = "man";
	ch.City = "SentJons";
	ch.location	= "SentJons_Store";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Store.c";
	ch.quest.type = "trader";
	ch.nation = ENGLAND;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	// настройка магазина -->
	ch.StoreNum   = SentJons_STORE;
	ch.from_sea   = "SentJons_town";
	// настройка магазина <--
	n = n + 1;

	makeref(ch,Characters[n]);			//Корабел
	ch.id		= "SentJons_shipyarder";
	ch.model	= "shipowner_11";
	ch.greeting = "shipyarder_1";
	ch.sex = "man";
	ch.City = "SentJons";
	ch.location	= "SentJons_Shipyard";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Shipyard.c";
	ch.nation = ENGLAND;
	ch.quest.shiping = "0";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, "topor_02");
	EquipCharacterbyItem(ch, GUN_COMMON); 
	EquipCharacterbyItem(ch, "topor_02"); 
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.standUp = true; //вставать и нападать на врага
	LAi_SetHuberType(ch);
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Банкир
	ch.id		= "SentJons_usurer";
	ch.model	= "banker_11";
	ch.sex = "man";
	ch.City = "SentJons";
	ch.Merchant.type = "jeweller"; 
	ch.location	= "SentJons_Bank";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Usurer_dialog.c";
	ch.nation = ENGLAND;
	ch.greeting = "usurer_1";
	ch.quest.shiping = "0";
	ch.UsurerDeposit = 10000; // *1000 денег
	ch.money = USURER_MIN_MONEY + rand(USURER_NORM);
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Начальник порта
	ch.id		= "SentJons_PortMan";
	ch.model	= "citiz_6";
	ch.sex = "man";
	ch.City = "SentJons";
	ch.location	= "SentJons_PortOffice";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Portman.c";
	ch.nation = ENGLAND;
	ch.greeting = "portman_1";
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;
	
	makeref(ch,Characters[n]);
	ch.name 	= "Smuggler";
	ch.lastname = "";
	ch.id		= "SentJons_Smuggler";
	ch.model    = "sitiz_28";
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
	
	return n;
}
