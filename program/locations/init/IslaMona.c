
int LocationInitIslaMona(int n)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Мыс 76
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore76";
	locations[n].id.label = "Shore76";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "IslaMona";
	//Sound
	locations[n].type = "questisland";
	locations[n].islandId = "IslaMona";
	locations[n].onUninhabitedIsland = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Shore03";
	Locations[n].models.always.shore03 = "shore03";
	locations[n].models.always.shore03.sea_reflection = 1;
	Locations[n].models.always.shore03seabed = "shore03_sb";
	Locations[n].models.always.locators = "shore03_locators";
		
	Locations[n].models.always.grassPatch = "shore03_grass";
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
	locations[n].models.day.charactersPatch = "shore03_patch";
	//Night
	locations[n].models.night.charactersPatch = "shore03_patch";		
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";	
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "IslaMona_CaveEntrance";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Cave entrance";
	locations[n].locators_radius.reload.reload1_back = 2;

	Locations[n].DisableEncounters = true;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в пещеру
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "IslaMona_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "questisland";
	locations[n].islandId = "IslaMona";
	locations[n].onUninhabitedIsland = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\CaveEnt1";
	Locations[n].models.always.caveEnt1 = "caveEnt1";	
	Locations[n].models.always.locators = "caveEnt1_locators";		
	Locations[n].models.always.grassPatch = "caveEnt1_grass";
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
	locations[n].models.day.charactersPatch = "caveEnt1_patch";
	//Night
	locations[n].models.night.charactersPatch = "caveEnt1_patch";	
	//Environment	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "IslaMona_Cave";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Cave";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore76";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore76";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	Locations[n].DisableEncounters = true;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пещера
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "IslaMona_Cave";
	locations[n].id.label = "Cave";
	locations[n].image = "loading\inside\cave.tga";
	//Sound
	locations[n].type = "cave";
 	locations[n].islandId = "IslaMona";
	locations[n].onUninhabitedIsland = true;
	locations[n].changeAnimation = "man_A"; //сменить анимацию на обычную
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\cavernMedium2";
	locations[n].models.always.cavernMedium2 = "cavernMedium2";
	locations[n].models.always.locators = "cavernMedium2_IMlocators";
	locations[n].models.always.well_on = "well_on";
	Locations[n].models.always.well_on.locator.group = "reload";
	Locations[n].models.always.well_on.locator.name = "reload3";
	Locations[n].models.always.well_on.tech = "DLightModel";	

	locations[n].locators_radius.item.duhi1 = 0.0;
	//Day
	locations[n].models.day.charactersPatch = "cavernMedium2_patch";
	//Night
	locations[n].models.night.charactersPatch = "cavernMedium2_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "IslaMona_CaveEntrance";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].locators_radius.reload.reload1 = 2.0;
	
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "IslaMona_Basement";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Basement";
	locations[n].locators_radius.reload.reload2 = 2.0;
	
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "IslaMona_WaterCave";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].locators_radius.reload.reload3 = 1.0;
	Locations[n].DisableEncounters = true;
	locations[n].DisableOfficers = "1";
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Затопленная пещера
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "IslaMona_WaterCave";
	locations[n].id.label = "";
	locations[n].image = "loading\inside\cave.tga";
	//Sound
	locations[n].islandId = "IslaMona";
	locations[n].DisableEncounters = true;
	locations[n].type = "underwater";
	locations[n].changeAnimation = "swim"; //сменить анимацию на плавание
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\cavernLow2";
	locations[n].models.always.cavernLow2 = "cavernLow2";
	
	locations[n].models.always.cavernLow1Crystals = "cavernLow2_crystals";
	locations[n].models.always.cavernLow1Crystals.tech = "EnvironmentShader";
	locations[n].models.always.cavernLow1Crystals.reflection = 0.25;
	
	locations[n].models.always.Waterfall = "water";
	locations[n].models.always.Waterfall.uvslide.v0 = 0.0;
	locations[n].models.always.Waterfall.uvslide.v1 = 0.0;
	locations[n].models.always.Waterfall.tech = "LocationWaterFall";
	locations[n].models.always.Waterfall.level = 51;

	locations[n].models.always.Cfall = "cfall";
	locations[n].models.always.Cfall.uvslide.v0 = 0.3;
    locations[n].models.always.Cfall.uvslide.v1 = 0.0;
	locations[n].models.always.Cfall.tech = "LocationWaterFall";
	locations[n].models.always.Cfall.level = 50;
	locations[n].models.always.locators = "cavernLow2_IMlocators";
	
	locations[n].models.always.chest = "chest_1";
	Locations[n].models.always.chest.locator.group = "box";
	Locations[n].models.always.chest.locator.name = "private1";
	Locations[n].models.always.chest.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "cavernLow2_patch";
	//Night
	locations[n].models.night.charactersPatch = "cavernLow2_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	locations[n].underwater = true;
	Locations[n].QuestlockWeather = "Underwater";
	Locations[n].lockWeather = "Inside";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "IslaMona_Cave";
	locations[n].reload.l1.emerge = "reload3_back";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Cave";
	
	locations[n].DisableOfficers = "1";
	LAi_LocationFightDisable(&locations[n], true);
	
	locations[n].private1.money = 750000;
	locations[n].private1.items.gold_dublon = 900;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Форт
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "IslaMona_fort";
	locations[n].id.label = "Jungle Fort";
	locations[n].image = "loading\towns\pearl1.tga";
 	//Sound
	locations[n].type = "questisland";
	locations[n].islandId = "IslaMona";
	locations[n].onUninhabitedIsland = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\PirateFort";
	Locations[n].models.always.fort = "piratefort";	
	Locations[n].models.always.locators = "piratefort_locators";		
	Locations[n].models.always.grassPatch = "piratefort_grass";
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
	Locations[n].models.always.l4 = "plan4";
	Locations[n].models.always.l4.level = 6;
	Locations[n].models.always.l4.tech = "LocationModelBlend";
	locations[n].models.always.mortair = "mortair";
	Locations[n].models.always.mortair.locator.group = "quest";
	Locations[n].models.always.mortair.locator.name = "mortair";
	//Day
	locations[n].models.day.fonar = "piratefort_fd";
	locations[n].models.day.charactersPatch = "piratefort_patch";
	//Night
	locations[n].models.night.fonar = "piratefort_fn";
	locations[n].models.night.charactersPatch = "piratefort_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "IslaMona_jungle_01";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

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
	
	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "CommonRoom_MH2";
	locations[n].reload.l5.emerge = "reload1";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "House";
	
	locations[n].reload.l6.name = "reload6";
	locations[n].reload.l6.go = "IslaMona_TwoFloorHouse";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "House";
	
	locations[n].locators_radius.quest.detector = 3.0;
	Locations[n].DisableEncounters = true;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Двухэтажный дом
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "IslaMona_TwoFloorHouse"; 
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\largehouse01.tga";
	//Town sack
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "IslaMona";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Doubleflour_house";
	locations[n].models.always.largehouse01 = "LH_Floor1";
	locations[n].models.always.largehouse01.level = 65538;
	locations[n].models.always.locators = "LH_Floor1_locators";
	Locations[n].models.always.largehouse01windows = "LH_Floor1_window";
	Locations[n].models.always.largehouse01windows.tech = "LocationWindows";
	locations[n].models.always.largehouse01windows.level = 65539;
	locations[n].models.always.Trapdoor = "trapdoor";
	Locations[n].models.always.Trapdoor.locator.group = "reload";
	Locations[n].models.always.Trapdoor.locator.name = "reload3";
	Locations[n].models.always.Trapdoor.tech = "DLightModel";

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "LH_Floor1_patch";
	//Night
	locations[n].models.night.fonar = "LH_Floor1_fn";
	locations[n].models.night.charactersPatch = "LH_Floor1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "IslaMona_fort";
	locations[n].reload.l1.emerge = "reload6";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Jungle Fort";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "IslaMona_TwoFloorRoom";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "IslaMona_Basement";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Basement";
	locations[n].locators_radius.reload.reload3 = 0.5;
	
	locations[n].private1.items.topor_06 = 1;
	locations[n].private1.items.cirass2 = 1;
	locations[n].private1.items.clock1 = 1;
	locations[n].private1.items.totem_02 = 1;
	locations[n].private1.items.indian_4 = 1;
	locations[n].private1.items.obereg_6 = 1;
	locations[n].private1.items.amulet_11 = 1;
	locations[n].private1.items.potion2 = 5;
	locations[n].private1.items.potion4 = 2;
	locations[n].private1.items.berserker_potion = 1;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// комната на 2 этаже
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "IslaMona_TwoFloorRoom"; 
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "IslaMona";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Doubleflour_house";
	locations[n].models.always.largehouse01 = "LH_Floor2";
	locations[n].models.always.largehouse01.level = 65538;
	locations[n].models.always.locators = "LH_Floor2_locators";
	Locations[n].models.always.largehouse01windows = "LH_Floor2_window";
	Locations[n].models.always.largehouse01windows.tech = "LocationWindows";
	locations[n].models.always.largehouse01windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "LH_Floor2_patch";
	//Night
	locations[n].models.night.fonar = "LH_Floor2_fn";
	locations[n].models.night.charactersPatch = "LH_Floor2_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "IslaMona_TwoFloorHouse";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "House";
	
	locations[n].private1.items.potionrum = 5;
	locations[n].private1.items.Mineral3 = 10;
	locations[n].private1.items.Mineral5 = 1;
	locations[n].private1.items.Mineral10 = 1;
	locations[n].private1.items.Mineral15 = 1;
	locations[n].private1.items.Mineral21 = 1;
	locations[n].private1.items.Mineral18 = 1;
	locations[n].private1.items.obereg_5 = 1;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Подвал
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "IslaMona_Basement";
	locations[n].id.label = "Basement";
	locations[n].image = "loading\inside\cave.tga";
	//Town sack
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "Cave";
	locations[n].islandId = "IslaMona";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\grotto3";
	locations[n].models.always.grotto3 = "grotto3";
	locations[n].models.always.locators = "grotto3_IMlocators";
	locations[n].models.always.l1 = "Grotenve2";
	Locations[n].models.always.l2 = "Ladder";
	locations[n].models.always.l2.locator.group = "reload";
	locations[n].models.always.l2.locator.name = "reload1_back";
	Locations[n].models.always.l2.tech = "DLightModel";
	locations[n].models.always.hatch = "hatch";
	Locations[n].models.always.hatch.locator.group = "reload";
	Locations[n].models.always.hatch.locator.name = "reload2";
	Locations[n].models.always.hatch.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "grotto3_patch";
	//Night
	locations[n].models.night.charactersPatch = "grotto3_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "IslaMona_TwoFloorHouse";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "House";
	
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "IslaMona_Cave";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Cave";
	
	locations[n].locators_radius.reload.reload1_back = 1.5;
	locations[n].locators_radius.reload.reload2 = 0.5;
	locations[n].DisableOfficers = "1";
	Locations[n].DisableEncounters = true;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "IslaMona_Jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "questisland";
	locations[n].islandId = "IslaMona";
	locations[n].onUninhabitedIsland = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle3";
	Locations[n].models.always.jungle = "jungle3";	
	Locations[n].models.always.locators = "jungle3_locators";		
	Locations[n].models.always.grassPatch = "jungle3_grass";
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
	locations[n].models.day.charactersPatch = "jungle3_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle3_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Shore75";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Shore75";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore77";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore77";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "IslaMona_fort";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle Fort";
	locations[n].locators_radius.reload.reload3_back = 2;
	Locations[n].DisableEncounters = true;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пляж 75
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore75";
	locations[n].id.label = "Shore75";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "Shore75";
	//Sound
	locations[n].type = "questisland";
	locations[n].islandId = "IslaMona";
	locations[n].onUninhabitedIsland = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Shore07";
	Locations[n].models.always.shore07 = "shore07";
	locations[n].models.always.shore07.sea_reflection = 1;
	Locations[n].models.always.shore07seabed = "shore07_sb";
	Locations[n].models.always.locators = "shore07_locators";
		
	Locations[n].models.always.grassPatch = "shore07_grass";
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
	locations[n].models.day.charactersPatch = "shore07_patch";
	//Night
	locations[n].models.night.charactersPatch = "shore07_patch";		
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "IslaMona_Jungle_01";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "IslaMona";
	locations[n].reload.l2.emerge = "reload_1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	Locations[n].DisableEncounters = true;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Бухта77
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore77";
	locations[n].id.label = "Shore77";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "Shore77";
	//Sound
	locations[n].type = "questisland";
	locations[n].islandId = "IslaMona";
	locations[n].onUninhabitedIsland = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Shore08";
	Locations[n].models.always.shore08 = "shore08";
	locations[n].models.always.shore08.sea_reflection = 1;
	Locations[n].models.always.shore08seabed = "shore08_sb";
	Locations[n].models.always.locators = "shore08_locators";		
	Locations[n].models.always.grassPatch = "shore08_grass";
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
	locations[n].models.day.charactersPatch = "shore08_patch";
	//Night
	locations[n].models.night.charactersPatch = "shore08_patch";		
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "IslaMona_Jungle_01";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "IslaMona";
	locations[n].reload.l2.emerge = "reload_3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	Locations[n].DisableEncounters = true;
	n = n + 1;

	return n;
}
