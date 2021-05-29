

int LocationInitQuestLocations(int n)
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Локация клон
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Clone_location";
	locations[n].id.label = "Farm Field";
	locations[n].filespath.models = "locations\";
	locations[n].image = "loading\Farmfield.tga";
	//Sound
	locations[n].type = "land";
	//Models
	//Always
	locations[n].models.always.house = "farmfield";
	locations[n].models.always.locators = "farmfield_locators";
	locations[n].models.always.grassPatch = "farmfield_grass";

	locations[n].models.always.plan = "farmfield_plan";
	locations[n].models.always.plan.level = 9;

	//Day
	locations[n].models.day.charactersPatch = "farmfield_patch";
	locations[n].models.day.fonar = "farmfield_fd";

	//Night
	locations[n].models.night.charactersPatch = "farmfield_patch";
	locations[n].models.night.fonar = "farmfield_fn";

	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";

	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tortuga_tavern";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Cob_house";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "House";

	n = n + 1;
	
	////////////////////////////////////////////////////////////
	/// Корабельная палуба  для карта - море
	////////////////////////////////////////////////////////////
	Locations[n].id = "Ship_deck";
	Locations[n].image = "loading\art\open_sea_clear.tga";
	locations[n].id.label = "Boarding deck";
	//Sound
	Locations[n].type = "deck";
	// нельзя, иначе нет моря Locations[n].boarding = "true";
	Locations[n].lockCamAngle = 0.4;
	Locations[n].camshuttle = 1;
	//Models
	//Always
	Locations[n].filespath.models = "locations\decks\deckMedium";
	Locations[n].models.always.deckMedium = "deckMedium";
	Locations[n].models.always.locators = "deckMedium_locators";
	//Day
	locations[n].models.day.charactersPatch = "deckMedium_patch";
	Locations[n].models.day.deckMediumFonarsDay = "deckMedium_fd";
	//Night
	locations[n].models.night.charactersPatch = "deckMedium_patch";
	Locations[n].models.night.deckMediumFonarsNight= "deckMedium_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";

	n = n + 1;
	
	////////////////////////////////////////////////////////////
	/// Корабельная палуба  для море - море
	////////////////////////////////////////////////////////////
    //ID
	Locations[n].id = "Deck_Near_Ship";   // выслать туда шлюпку
	Locations[n].id.label = "Boarding deck";
	//Info
	Locations[n].image = "loading\Quarter_" + rand(1) + ".tga";
	//Sound
	Locations[n].type = "residence";
	Locations[n].boarding = "true";
	Locations[n].lockCamAngle = 0.4;
	Locations[n].camshuttle = 1;
	//Models
	//Always
	Locations[n].filespath.models = "locations\decks\deckMedium";
	Locations[n].models.always.deckMedium = "deckMedium";
	Locations[n].models.always.locators = "deckMedium_locators";
	//Day
	locations[n].models.day.charactersPatch = "deckMedium_patch";
	Locations[n].models.always.deckMediumFonarsDay = "deckMedium_fd";
	//Night
	locations[n].models.night.charactersPatch = "deckMedium_patch";
	Locations[n].models.always.deckMediumFonarsNight= "deckMedium_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	LAi_LocationFightDisable(&Locations[n], true);
	n = n + 1;
	
	////////////////////////////////////////////////////////////
	/// Квестовая корабельная палуба  для море - море
	////////////////////////////////////////////////////////////
    //ID
	Locations[n].id = "Deck_Galeon_Ship";   // выслать туда шлюпку
	Locations[n].id.label = "Boarding deck";
	//Info
	Locations[n].image = "loading\Quarter_" + rand(1) + ".tga";
	//Sound
	Locations[n].type = "residence";
	//Locations[n].boarding = "true";
	Locations[n].lockCamAngle = 0.4;
	Locations[n].camshuttle = 1;
	//Models
	//Always
	Locations[n].filespath.models = "locations\decks\deck01";
	Locations[n].models.always.deckGaleon = "deck01";
	Locations[n].models.always.locators = "deck01_locators";
	locations[n].models.always.charactersJumpPatch = "deck01_jump_patch";
	Locations[n].models.always.Fonars = "deck01_fonars";
	Locations[n].models.always.alpha = "deck01_alpha";
	Locations[n].models.always.window = "deck01_window";
	//Day
	locations[n].models.day.charactersPatch = "deck01_patch";
	//Night
	locations[n].models.night.charactersPatch = "deck01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	LAi_LocationFightDisable(&Locations[n], true);
	n = n + 1;

  	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Имение Оглторпа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Estate";
	locations[n].id.label = "Estate";
	locations[n].filespath.models = "locations\Estate";
	locations[n].image = "loading\EstateN.tga";
	//Sound
	locations[n].type = "europe";
	//Models
	//Always
	locations[n].models.always.estate = "estate";
	
	locations[n].models.always.windows = "estate_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";	
	Locations[n].models.always.windows.level = 66532;	
	//VolumeLight	
	Locations[n].models.always.vlight = "estate_vlight";
	Locations[n].models.always.vlight.uvslide.v0 = 0.05;
    Locations[n].models.always.vlight.uvslide.v1 = 0.0;
	Locations[n].models.always.vlight.tech = "LocationWaterFall";
	Locations[n].models.always.vlight.level = 99950;
	
	locations[n].models.always.locators = "estate_locators";
	locations[n].models.always.grassPatch = "estate_grass";
	//Day
	locations[n].models.day.charactersPatch = "estate_patch";
	locations[n].models.day.fonar = "estate_fd";
	//Night
	locations[n].models.night.charactersPatch = "estate_patch";
	locations[n].models.night.fonar = "estate_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	Locations[n].QuestlockWeather = "20 Hour";
	Locations[n].QuestlockWeather.hours = 20;
	Locations[n].QuestlockWeather.minutes = 00;
	//Reload map
	locations[n].reload.l1.name = "reload3";
	locations[n].reload.l1.go = "EstateBadRoom1";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Bedroom";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "EstateBadRoom2";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Bedroom";

	locations[n].reload.l3.name = "reload5";
	locations[n].reload.l3.go = "EstateOffice";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Cabinet";
	locations[n].locators_radius.item.item1 = 1.0;
	
	locations[n].private1.key = "key3";
	locations[n].private1.key.delItem = true;
	locations[n].private1.items.blade_03 = 1;
	locations[n].private1.items.pistol1 = 1;
	locations[n].private1.items.bullet = 10;
	locations[n].private1.items.GunPowder = 10;
	n = n + 1;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Спальня #1 Оглторпа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "EstateBadRoom1";
	locations[n].id.label = "Bedroom";
	locations[n].filespath.models = "locations\EstateRooms\EstateBadRoom1";
	locations[n].image = "loading\EstateRoomN.tga";		
	//Models
	//Sound
	locations[n].type = "house";
	//Always
	locations[n].models.always.estateBadRoom = "estateBadRoom1";	
	locations[n].models.always.windows = "estateBadRoom1_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 66532;	
	//VolumeLight	
	Locations[n].models.always.vlight = "estateBadRoom1_vlight";
	Locations[n].models.always.vlight.uvslide.v0 = 0.05;
    Locations[n].models.always.vlight.uvslide.v1 = 0.0;
	Locations[n].models.always.vlight.tech = "LocationWaterFall";
	Locations[n].models.always.vlight.level = 99950;
	
	locations[n].models.always.locators = "estateBadRoom1_locators";
	locations[n].models.always.grassPatch = "estateRooms_grass";
	//Day
	locations[n].models.day.charactersPatch = "estateBadRoom1_patch";
	locations[n].models.day.fonar = "estateRooms_fd";
	//Night
	locations[n].models.night.charactersPatch = "estateBadRoom1_patch";
	locations[n].models.night.fonar = "estateRooms_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	Locations[n].QuestlockWeather = "20 Hour";	
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Estate";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Estate";
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Подводная Локация
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "UnderWater";
	locations[n].id.label = "UnderWater";
	locations[n].filespath.models = "locations\UnderWater";	
	locations[n].image = "loading\UnderWater_" + rand(1) + ".tga";
	//Sound	
	locations[n].type = "underwater";
	locations[n].type.LSC = true; //локация ГПК
	locations[n].dolly = 2;
	//Models
	//Always	
	Locations[n].models.always.UnderWater = "UnderWater";
	Locations[n].models.always.UnderWater.tech = "DLightModel";	
	
	Locations[n].models.always.outside = "UnderWater_outside";
	Locations[n].models.always.outside.tech = "DLightModel";
			
	Locations[n].models.always.reflect = "UnderWater_reflect";
	Locations[n].models.always.reflect .tech = "DLightModel";	
	Locations[n].models.always.reflect.sea_reflection = 1;
		
	Locations[n].models.always.sails = "UnderWater_sails";	
	Locations[n].models.always.sails.tech = "DLightModel";
		
	Locations[n].models.always.plants = "UnderWater_plants";	
	Locations[n].models.always.plants.tech = "DLightModel";
	//Locations[n].models.always.plants.tech = "LocationWindows";
	//Locations[n].models.always.plants.level = 66532;
		
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.sea_reflection = 1;
		
	Locations[n].models.always.plan2 = "Plan2";
		
	Locations[n].models.always.locators = "UnderWater_locators";	
	
	Locations[n].models.always.grassPatch = "UnderWater_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU2.tga.tx";						
	//Day
	locations[n].models.day.charactersPatch = "UnderWater_patch_day";
	//Night
	locations[n].models.night.charactersPatch = "UnderWater_patch_day";		
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	locations[n].underwater = true;
	Locations[n].QuestlockWeather = "Underwater";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload73";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	locations[n].DisableOfficers = "1";

	locations[n].locators_radius.reload.reload1 = 2.0;
	locations[n].locators_radius.item.dolly2 = 1.0;
	locations[n].locators_radius.item.item1 = 0.6;
	locations[n].locators_radius.item.item2 = 0.6;
	locations[n].locators_radius.item.item3 = 0.6;
	locations[n].locators_radius.item.item4 = 0.6;
	locations[n].locators_radius.item.item5 = 0.6;

	//в сундуках
	locations[n].private1.items.gold_dublon = 154;
	locations[n].private1.items.jewelry5 = 166;
	locations[n].private1.items.jewelry6 = 211;
	locations[n].private1.items.jewelry10 = 3;
	
	locations[n].private2.money = 38745;
	locations[n].private2.items.jewelry1 = 90;
	locations[n].private2.items.jewelry2 = 65;
	locations[n].private2.items.jewelry3 = 144;
	locations[n].private2.items.jewelry4 = 48;
	locations[n].private2.items.jewelry8 = 72;

	locations[n].private3.key = "key3";
	locations[n].private3.skel = true;
	locations[n].private3.money = 58931;
	locations[n].private3.items.jewelry40 = 101;
	locations[n].private3.items.jewelry41 = 88;
	locations[n].private3.items.jewelry42 = 52;
	locations[n].private3.items.jewelry43 = 67;
	locations[n].private3.items.jewelry46 = 115;
	locations[n].private3.items.jewelry48 = 195;
	locations[n].private3.items.jewelry50 = 21;
	locations[n].private3.items.jewelry52 = 954;
	locations[n].private3.items.jewelry53 = 2087;

	locations[n].private4.key = "key3";
	locations[n].private4.skel = true;
	locations[n].private4.items.icollection = 2;
	locations[n].private4.items.Chest = 3;
	locations[n].private4.items.jewelry8 = 57;
	locations[n].private4.items.talisman8 = 1;

	locations[n].private5.money = 60802;
	locations[n].private5.items.jewelry5 = 220;
	locations[n].private5.items.jewelry6 = 310;

	locations[n].private6.items.gold_dublon = 100;
	locations[n].private6.items.jewelry5 = 10;
	locations[n].private6.items.jewelry6 = 2000;
	locations[n].private6.items.jewelry10 = 33;

	locations[n].private7.key = "key_betancur"; // сундук Бетанкура
	locations[n].private7.key.delItem = true;
	locations[n].private7.money = 100000; 
	locations[n].private7.items.gold_dublon = 500;
	locations[n].private7.items.icollection = 12; // чтоб удавиться от жадности
	locations[n].private7.items.jewelry5 = 400;
	locations[n].private7.items.jewelry6 = 1000;
	locations[n].private7.items.jewelry10 = 19;
	locations[n].private7.items.talisman1 = 1;

	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Спецлокация
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Terrain";
	//locations[n].image = "loading\outside\jungle_" + rand(2) + ".tga";
	locations[n].MustSetReloadBack = true;
	//Sound
	locations[n].type = "shore";
	locations[n].islandId = "Mein";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Terrain";
	Locations[n].models.always.Terrain = "Terrain";	
	Locations[n].models.always.locators = "Terrain_locators";
	//Day
	locations[n].models.day.charactersPatch = "Terrain_patch";
	//Night
	locations[n].models.night.charactersPatch = "Terrain_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	
	LAi_LocationFightDisable(&Locations[n], true);
	n = n + 1;
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// резервные локации
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 1
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 2
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_02";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 3
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_03";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 4 // Jason „олго и счастливо
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_04";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 5
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_05";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 6
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_06";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 7
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_07";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 8
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_08";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 9
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_09";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 10
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_10";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 11
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_11";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_12";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 13
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_13";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 14
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_14";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 15
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_15";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 16
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_16";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 17
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_17";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 18
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_18";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 19
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_19";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 20
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_20";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 21
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_21";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 22
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_22";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 23
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_23";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 24
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_24";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 25
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_25";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 26
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_26";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 27
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_27";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 28
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_28";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 29
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_29";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 30
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_30";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 31
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_31";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 32
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_32";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 33
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_33";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 34
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_34";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 35
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_35";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 36
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_36";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 37
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_37";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 38
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_38";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 39
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_39";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 40
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_40";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 41
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_41";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 42
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_42";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 43
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_43";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 44
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_44";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 45
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_45";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 46
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_46";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 47
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_47";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 48
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_48";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 49
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_49";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 50
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_50";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	return n;
}
