
int LocationInitLaVega(int n)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Порт Ла Веги
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_port";
	locations[n].id.label = "LaVega Port";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "LaVega_port";
	//Town sack
	locations[n].townsack = "LaVega";
	//Sound
	locations[n].type = "seashore";
	locations[n].fastreload = "LaVega";
	locations[n].islandId = "Hispaniola";
	locations[n].Chestgennot = true; // не генерить сундуки
	//Models
	//Always
	locations[n].filespath.models = "locations\LaVega\Port";
	Locations[n].models.always.port = "qcport";
	locations[n].models.always.port.sea_reflection = 1;
	Locations[n].models.always.portseabed = "qcport_sb";
	Locations[n].models.always.locators = "QCport_l";

	Locations[n].models.always.grassPatch = "QCport_g";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	Locations[n].models.always.l4 = "QCport_j";	
	//Day
	locations[n].models.day.charactersPatch = "QCport_p";
	//Night
	locations[n].models.night.charactersPatch = "QCport_p";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "LaVega_ExitTown";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Hispaniola1";
	locations[n].reload.l2.emerge = "reload_4";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 5.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Выход из города Ла Вега
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_ExitTown";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\Gate" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LaVega";
	//Sound
	locations[n].type = "town";
	locations[n].fastreload = "LaVega";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	Locations[n].filespath.models = "locations\LaVega\Exit";
	Locations[n].models.always.Exit = "qcexit";	
	Locations[n].models.always.locators = "qcexit_l";		
	Locations[n].models.always.grassPatch = "qcexit_g";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "qcexit_p";
	locations[n].models.day.fonars = "qcexit_fd";
	//Night
	locations[n].models.night.charactersPatch = "qcexit_p";
	locations[n].models.night.fonars = "qcexit_fn";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Hispaniola_Jungle_03";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "LaVega_port";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "LaVega Port";
	locations[n].locators_radius.reload.reload1_back = 2.0;

    Locations[n].reload.l3.name = "reload3";
	Locations[n].reload.l3.go = "LaVega_town";
	Locations[n].reload.l3.emerge = "reload1";
	Locations[n].reload.l3.autoreload = "0";
	Locations[n].reload.l3.label = "Street";
	locations[n].locators_radius.reload.reload3 = 1.8;
	
	Locations[n].reload.l4.name = "reload4";
	Locations[n].reload.l4.go = "LaVega_JungleHouse";
	Locations[n].reload.l4.emerge = "reload1";
	Locations[n].reload.l4.autoreload = "0";
	Locations[n].reload.l4.label = "House";
	locations[n].reload.l4.disable = 1;//закрыто
	
	Locations[n].reload.l5.name = "reload5";
	Locations[n].reload.l5.go = "LaVega_JungleHouse";
	Locations[n].reload.l5.emerge = "reload2";
	Locations[n].reload.l5.autoreload = "0";
	Locations[n].reload.l5.label = "House";
	locations[n].reload.l5.disable = 1;//закрыто
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Ла Вега
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_town";
	locations[n].id.label = "Street";
	locations[n].image = "loading\towns\pearl1.tga";
	locations[n].worldmap = "LaVega_town";
	locations[n].citizens = true;
	locations[n].soldiers = true;	
	//Town sack
	locations[n].townsack = "LaVega";
	//Sound
	locations[n].type = "town";
	locations[n].fastreload = "LaVega";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	Locations[n].filespath.models = "locations\LaVega\Town";
	Locations[n].models.always.Town = "QCtown";	
	Locations[n].models.always.locators = "QCtown_l";		
	Locations[n].models.always.grassPatch = "QCtown_g";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "QCtown_p";
	locations[n].models.day.fonars = "QCtown_fd";
	//Night
	locations[n].models.night.charactersPatch = "QCtown_p";
	locations[n].models.night.fonars = "QCtown_fn";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map

	Locations[n].reload.l1.name = "reload1"; 
	Locations[n].reload.l1.go = "LaVega_ExitTown";
	Locations[n].reload.l1.emerge = "reload3";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "ExitTown";
	locations[n].locators_radius.reload.reload1 = 1.8;

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonHut";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "House";
	
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "CommonRoom_MH3";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "House";

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "CommonRoom_MH";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "House";

	Locations[n].reload.l5.name = "reload5";
	Locations[n].reload.l5.go = "LaVega_tavern";
	Locations[n].reload.l5.emerge = "reload1_back";
	Locations[n].reload.l5.autoreload = "0";
	Locations[n].reload.l5.label = "Tavern";

	Locations[n].reload.l6.name = "reload6";
	Locations[n].reload.l6.go = "LaVega_townhall";
	Locations[n].reload.l6.emerge = "reload1";
	Locations[n].reload.l6.autoreload = "0";
	Locations[n].reload.l6.label = "Townhall";
	Locations[n].reload.l6.close_for_night = 1;

	locations[n].reload.l7.name = "reload7";
	locations[n].reload.l7.go = "CommonRoom_MH2";
	locations[n].reload.l7.emerge = "reload1";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "House";

	Locations[n].reload.l8.name = "reload8";
	Locations[n].reload.l8.go = "LaVega_store";
	Locations[n].reload.l8.emerge = "reload1";
	Locations[n].reload.l8.autoreload = "0";
	Locations[n].reload.l8.label = "Store";
	Locations[n].reload.l8.close_for_night = 1;
	
	locations[n].reload.l9.name = "reload9";
	locations[n].reload.l9.go = "CommonRoom_MH4";
	locations[n].reload.l9.emerge = "reload1";
	locations[n].reload.l9.autoreload = "0";
	locations[n].reload.l9.label = "House";
	
	locations[n].reload.l10.name = "reload10";
	locations[n].reload.l10.go = "LaVega_TwoFloorHouse";
	locations[n].reload.l10.emerge = "reload1";
	locations[n].reload.l10.autoreload = "0";
	locations[n].reload.l10.label = "House";
	locations[n].reload.l10.disable = 1;//закрыто
    n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Таверна Ла Вега
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 	locations[n].id = "LaVega_tavern";
	locations[n].id.label = "Tavern";
	locations[n].filespath.models = "locations\inside\Tavern05\";
	locations[n].image = "loading\inside\tavern.tga";
	locations[n].habitues = 1;
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	locations[n].fastreload = "LaVega";
 	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].models.always.tavern = "Tavern05";
	locations[n].models.always.locators = "Tavern05_locators";
	locations[n].models.always.window = "tavern05_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;
	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "Tavern05_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tavern05_patch";
	locations[n].models.night.fonar = "Tavern05_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "LaVega_town";
	locations[n].reload.l1.emerge = "reload5"; 
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "LaVega_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; // закроем, но связку сделаем для квестовых нужд.
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комната в таверне наверху, Ла Вега
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_tavern_upstairs";
	locations[n].filespath.models = "locations\inside\Tavern_room";
	locations[n].id.label = "Tavern upstairs";
	locations[n].image = "loading\inside\tavern.tga";
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "LaVega";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].models.always.locators = "Tavern_room_locators";
	locations[n].models.always.tavern = "Tavern_room";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "tavern_room_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Tavern_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tavern_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "LaVega_tavern";
	locations[n].reload.l1.emerge = "reload2_back";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Магазин Ла Вега
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_store";
	locations[n].id.label = "Store";
	locations[n].image = "loading\inside\shop.tga";
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "LaVega";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\StoreSmall\";
	locations[n].models.always.locators = "StoreSmall_locators";
	locations[n].models.always.store = "StoreSmall";
	locations[n].models.always.window = "StoreSmall_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "StoreSmall_patch";
	//Night
	locations[n].models.night.charactersPatch = "StoreSmall_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LaVega_town";
	locations[n].reload.l1.emerge = "reload8"; 
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

    ////////////////////////==> комната в магазине
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonRoom_MH10";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Резиденция Ла Вега
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_townhall";
	locations[n].id.label = "Townhall";
	locations[n].image = "loading\inside\smallresidence.tga";
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "LaVega";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\pirateresidence";
	locations[n].models.always.house = "ResP";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "ResP_w";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.locators = "ResP_l";
	locations[n].models.day.charactersPatch = "ResP_p";
	//Night
	locations[n].models.night.locators = "ResP_l_n";
	locations[n].models.night.charactersPatch = "ResP_p";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LaVega_town";
	locations[n].reload.l1.emerge = "reload6";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	
	locations[n].box1.QuestClosed = true;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////
	/////Дом за воротами
	//////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_JungleHouse";
	locations[n].filespath.models = "locations\inside\Hut";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\hut.tga";
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].models.always.locators = "Hut_locators";
	locations[n].models.always.tavern = "Hut";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "Hut_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back2";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Hut_patch";
	//Night
	locations[n].models.night.charactersPatch = "Hut_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LaVega_ExitTown";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Jungle";
	
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "LaVega_ExitTown";
	locations[n].reload.l2.emerge = "reload5";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Jungle";
	
	locations[n].box1.QuestClosed = true;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// двухэтажный дом - резиденция Вуазье
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_TwoFloorHouse";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\TwoFloorHouse.tga";
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
 	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Pirate_House";
	locations[n].models.always.house = "PirH";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "PirH_w";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.locators = "PirH_l";
	locations[n].models.day.charactersPatch = "PirH_p";
	//Night
	locations[n].models.night.locators = "PirH_l_n";
	locations[n].models.night.charactersPatch = "PirH_p";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";

	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LaVega_town";
	locations[n].reload.l1.emerge = "reload10";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].reload.l1.disable = 1;//закрыто
	
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	return n;
}
