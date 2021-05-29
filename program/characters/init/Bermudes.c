
int CreateBermudesCharacters(int n)
{
	ref ch;
	
	///////////////////////////////////////////////////////////////////////////////
	// ОСНОВНЫЕ ПЕРСОНАЖИ
	///////////////////////////////////////////////////////////////////////////////
		
	makeref(ch,Characters[n]);		// ОФициантка
	ch.id		= "Pirates_waitress";
	ch.model	= "women_7";
	ch.sex = "woman";
	ch.City = "Pirates";
	ch.location	= "Pirates_tavern";
	ch.location.group = "waitress";
	ch.location.locator = "barmen";
	ch.Dialog.Filename = "Waitress_dialog.c";
	ch.greeting = "Waitress";
	ch.nation = PIRATE;
	LAi_SetWaitressType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Трактирщик
	ch.id		= "Pirates_tavernkeeper";
	ch.model	= "Tuerto";
	ch.greeting = "barmen_1";
	ch.name		= "One-eyed";
	ch.lastname = "";
	ch.sex = "man";
	ch.City = "Pirates";
	ch.location	= "Pirates_Tavern";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Tavern.c";
	ch.TavernMan = true;
	ch.nation = PIRATE;
	LAi_SetBarmanType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Торговец
	ch.id		= "Pirates_trader";
	ch.name		= "Pascal";
	ch.lastname = "Voisier";
	ch.model	= "Pasquale";
	ch.greeting = "store_3";
	ch.sex = "man";
	ch.City = "Pirates";
	ch.location	= "Pirates_Store";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Store.c";
	ch.quest.type = "trader";
	ch.nation = PIRATE;
	LAi_SetBarmanType(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	// настройка магазина -->
	ch.Storage 	  = true; // можем завести склад
	ch.StoreNum   = Pirates_STORE;
	ch.from_sea   = "Pirates_town";
	// настройка магазина <--
	n = n + 1;

	makeref(ch,Characters[n]);			//Корабел
	ch.id		= "Pirates_shipyarder";
	ch.model	= "Alexus";//"trader_15";
	ch.model.animation = "man_A1";
	ch.greeting = "Gr_shipyarderA";
	ch.name 	= "Master";
    ch.lastname = "Alexis";
	ch.sex = "man";
	ch.City = "Pirates";
	ch.location	= "Pirates_Shipyard";
	ch.location.group = "goto";
	ch.location.locator = "goto3";
	ch.Dialog.Filename = "Common_Shipyard.c";
	ch.nation = PIRATE;
	ch.quest.shiping = "0";
	//LAi_SetHuberType(ch);
	LAi_SetCitizenTypeNoGroup(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			// Норман
	ch.id		= "Norman";
	ch.name 	= "Abraham";
	ch.lastname = "Norman";
	ch.model	= "Norman_1";
    ch.rank     = 45;
	ch.sex = "man";
    ch.model.animation = "Norman"; 
	ch.City = "Pirates";
	ch.location	= "Pirates_town";
	ch.location.group = "goto";
	ch.location.locator = "goto1";
	ch.Dialog.Filename = "Quest\Sharlie\Norman.c";
	ch.dialog.currentnode = "norman_us";
	ch.greeting = "Norman_1";
	ch.nation = PIRATE;
	ch.MultiFighter = 2.5; // мультифайтер
	TakeNItems(ch, "potion2", 20);
	TakeNItems(ch, "bullet", 100);
	TakeNItems(ch, "gunpowder", 100);
	GiveItem2Character(ch, "pistol5");
	GiveItem2Character(ch, "blade_29");
	EquipCharacterbyItem(ch, "pistol5"); 
	EquipCharacterbyItem(ch, "blade_29");
	LAi_SetCharacterUseBullet(ch, "bullet");
	SetSPECIAL(ch, 10, 10, 10, 5, 5, 10, 5);
	LAi_SetHP(ch, 700, 700);
    SetSelfSkill(ch, 100, 100, 100, 100, 100);
	LAi_SetLoginTime(ch, 11.0, 20.0);
	LAi_SetWarriorType(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	//LAi_SetImmortal(ch, true);
	n = n + 1;

	return n;
}
