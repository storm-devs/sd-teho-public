
int LocationInitKsochitam(int n)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Остров Ксочитэм
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Бухта65
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore65";
	locations[n].id.label = "Shore65";
	locations[n].image = "loading\Ksochitem.tga";
	locations[n].worldmap = "Ksochitam";
	//Sound
	locations[n].type = "x_seashore";
	locations[n].islandId = "Ksochitam";
	locations[n].onUninhabitedIsland = true;
	locations[n].DisableEncounters = true;
	locations[n].Chestgennot = true; // не генерить сундуки
	locations[n].KsochitamSkeletons = 7; // число монстров в локации
	//Models
	//Always	
	locations[n].filespath.models = "locations\Outside\Shores\Shore12";
	Locations[n].models.always.shore12 = "rockshore";
	locations[n].models.always.shore12.sea_reflection = 1;
	Locations[n].models.always.shore12seabed = "rockshore_sb";
	Locations[n].models.always.locators = "rockshore_locators";
		
	Locations[n].models.always.grassPatch = "rockshore_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";

	//Day
	locations[n].models.day.charactersPatch = "rockshore_patch_day";
	//Night
	locations[n].models.night.charactersPatch = "rockshore_patch_day";		
	
	Locations[n].models.day.jumpPatch = "rockshore_jump_patch";
	Locations[n].models.night.jumpPatch = "rockshore_jump_patch"; 	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].alwaysStorm = true; //живем в штормах
	locations[n].alwaysStorm.WaveHeigh = true; //поднять уровень воды до 2.5 для низкого волнения
	locations[n].storm = true;
	locations[n].tornado = true;
	//Reload map
	locations[n].reload.l1.name = "reload2_back";
	locations[n].reload.l1.go = "Ksochitam_Jungle_01";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 1;

	locations[n].reload.l2.name = "reload1_back";
	locations[n].reload.l2.go = "Ksochitam";
	locations[n].reload.l2.emerge = "reload_2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 3.0;
	locations[n].locators_radius.reload.reload1_back = 1.5;
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли - перепутье
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Ksochitam_Jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "x_jungle";
	locations[n].islandId = "Ksochitam";
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	locations[n].KsochitamSkeletons = 10+MOD_SKILL_ENEMY_RATE/2; // число монстров в локации
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle9";
	Locations[n].models.always.jungle = "jungle9";	
	Locations[n].models.always.locators = "jungle9_locators";		
	Locations[n].models.always.grassPatch = "jungle9_grass";
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
	//Day
	locations[n].models.day.charactersPatch = "jungle9_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle9_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	locations[n].alwaysStorm = true; //живем в штормах
	locations[n].storm = true;
	locations[n].tornado = true;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Shore65";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Shore65";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Ksochitam_Jungle_02";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
    locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Ksochitam_Jungle_03";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли - к сокровищам
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Ksochitam_Jungle_02";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "x_jungle";
	locations[n].islandId = "Ksochitam";
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	locations[n].KsochitamSkeletons = 10; // число монстров в локации
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle10";
	Locations[n].models.always.jungle = "jungle10";	
	Locations[n].models.always.locators = "jungle10_locators";		
	Locations[n].models.always.grassPatch = "jungle10_grass";
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
	locations[n].models.day.charactersPatch = "jungle10_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle10_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	locations[n].alwaysStorm = true; //живем в штормах
	locations[n].storm = true;
	locations[n].tornado = true;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Ksochitam_Jungle_01";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;
	
	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore_ship4";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore_ship4";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Ksochitam_GrotEntrance";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
    locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Бухта с кораблем
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore_ship4";
	locations[n].id.label = "Shore_ship4";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "Ksochitam";
	locations[n].Chestgennot = true; // не генерить сундуки
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	locations[n].KsochitamSkeletons = 9+MOD_SKILL_ENEMY_RATE/2; // число монстров в локации
    //Sound
	locations[n].type = "x_seashore";
 	locations[n].islandId = "Ksochitam";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\ShoreShip2";
	Locations[n].models.always.shore = "shoreShip2";
	locations[n].models.always.shore.sea_reflection = 1;
	Locations[n].models.always.shoreShip1seabed = "shoreShip2_sb";
	Locations[n].models.always.locators = "shoreShip2_locators";		
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";
	locations[n].models.always.Chest = "Chest_1";
	Locations[n].models.always.Chest.locator.group = "box";
	Locations[n].models.always.Chest.locator.name = "private3";
	//Day
	locations[n].models.day.charactersPatch = "shoreShip2_patch";
	//Night
	locations[n].models.night.charactersPatch = "shoreShip2_patch";		
	//Environment
	locations[n].alwaysStorm = true; //живем в штормах
	locations[n].storm = true;
	locations[n].tornado = true;
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Ksochitam_Jungle_02";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 3;
	
	locations[n].private1.items.jewelry5 = 250;
	locations[n].private1.items.talisman4 = 1;
	
	locations[n].private2.items.chest = 5;
	
	locations[n].private3.items.jewelry2 = 200;
	locations[n].private3.items.jewelry3 = 200;
	locations[n].private3.items.jewelry4 = 150;
	locations[n].private3.items.jewelry8 = 100;
	locations[n].private3.items.jewelry9 = 10;
	locations[n].private3.items.jewelry10 = 10;
	locations[n].private3.items.jewelry52 = 500;
	locations[n].private3.items.jewelry53 = 1500;
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в грот - к сокровищам
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Ksochitam_GrotEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "x_jungle";
	locations[n].islandId = "Ksochitam";
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	locations[n].KsochitamSkeletons = 4; // число монстров в локации
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\CaveEnt3";
	Locations[n].models.always.caveEnt1 = "caveEnt3";	
	Locations[n].models.always.locators = "caveEnt3_locators";		
	Locations[n].models.always.grassPatch = "caveEnt3_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "CaveEnt3_b01";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "CaveEnt3_b02";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "CaveEnt3_b03";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	Locations[n].models.always.l3 = "CaveEnt3_b04";
	Locations[n].models.always.l3.level = 6;
	Locations[n].models.always.l3.tech = "LocationModelBlend";
	//Day
	locations[n].models.day.charactersPatch = "caveEnt3_patch";
	//Night
	locations[n].models.night.charactersPatch = "caveEnt3_patch";	
	//Environment	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	locations[n].alwaysStorm = true; //живем в штормах
	locations[n].storm = true;
	locations[n].tornado = true;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Ksochitam_Grot";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Grot";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Ksochitam_Jungle_02";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Грот - к сокровищам
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Ksochitam_Grot";
	locations[n].id.label = "Cave";
	locations[n].image = "loading\inside\cave.tga";
	locations[n].changeAnimation = "man_A"; //сменить анимацию на обычную
	locations[n].DisableEncounters = true;
	//Sound
	locations[n].islandId = "Ksochitam";
	locations[n].type = "cave";
	locations[n].KsochitamSkeletons = 4+MOD_SKILL_ENEMY_RATE/2; // число монстров в локации
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\cavernLow3";
	locations[n].models.always.cavernLow2 = "cavernLow3";
	
	locations[n].models.always.cavernLow1Crystals = "crystals";
	locations[n].models.always.cavernLow1Crystals.tech = "EnvironmentShader";
	
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
	
	locations[n].models.always.locators = "cavernLow3_locators";
	//Day
	locations[n].models.day.charactersPatch = "cavernLow3_patch";
	//Night
	locations[n].models.night.charactersPatch = "cavernLow3_patch";
	//Environment
	locations[n].MaxWaveHeigh = 2.0;
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	
	Locations[n].lockWeather = "Inside";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Ksochitam_GrotEntrance";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Jungle";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Ksochitam_WaterCave";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "FloodedCave";
	locations[n].locators_radius.reload.reload2_back = 2;
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Затопленная пещера - к сокровищам
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Ksochitam_WaterCave";
	locations[n].id.label = "FloodedCave";
	locations[n].image = "loading\inside\cave.tga";
	locations[n].DisableEncounters = true;
	//Sound
	locations[n].islandId = "Ksochitam";
	locations[n].type = "underwater";
	locations[n].changeAnimation = "swim"; //сменить анимацию на плавание
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\cavernMedium4";
	locations[n].models.always.cavernMedium4 = "cavernMedium4";
	locations[n].models.always.cavernMedium4.sea_reflection = 1;
	locations[n].models.always.locators = "cavernMedium4_locators";	
	//Day
	locations[n].models.day.charactersPatch = "cavernMedium4_patch";
	//Night
	locations[n].models.night.charactersPatch = "cavernMedium4_patch";
	//Environment
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
	locations[n].reload.l1.go = "Ksochitam_WaterGrot";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Cave";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Ksochitam_Grot";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Jungle";
	
	locations[n].DisableOfficers = "1";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Грот подтопленный - к сокровищам
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Ksochitam_WaterGrot";
	locations[n].id.label = "grot";
	locations[n].image = "loading\inside\cave.tga";
	locations[n].DisableEncounters = true;
	//Sound
	locations[n].type = "cave";
	locations[n].islandId = "Ksochitam";
	locations[n].changeAnimation = "man_A"; //сменить анимацию на обычную
	locations[n].KsochitamSkeletons = 3; // число монстров в локации
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\grotto2";
	locations[n].models.always.grotto2 = "grotto2";
	locations[n].models.always.grotto2.sea_reflection = 1;
	locations[n].models.always.grotto2alpha = "grotto2_alpha";
	Locations[n].models.always.grotto2alpha.tech = "LocationWindows";	
	locations[n].models.always.grotto2alpha.level = 65532;	
	locations[n].models.always.locators = "grotto2_Kslocators";
	//Day
	locations[n].models.day.charactersPatch = "grotto2_patch";
	//Night
	locations[n].models.night.charactersPatch = "grotto2_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	locations[n].MaxWaveHeigh = 3.0;
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Shore66";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Shore66";
	locations[n].locators_radius.reload.reload1_back = 1;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Ksochitam_WaterCave";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "FloodedCave";
	locations[n].locators_radius.reload.reload2_back = 1.5;
	
	locations[n].DisableOfficers = "1";
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// бухта с сокровищами
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore66";
	locations[n].id.label = "Shore66";
	locations[n].image = "loading\Ksochitem.tga";
	locations[n].worldmap = "Ksochitam";
	//Sound
	locations[n].type = "x_seashore";
	locations[n].islandId = "Ksochitam";
	locations[n].Chestgennot = true; // не генерить сундуки
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	locations[n].KsochitamSkeletons = 10+MOD_SKILL_ENEMY_RATE; // число монстров в локации
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Shore11";
	Locations[n].models.always.shore11 = "sandshore";
	locations[n].models.always.shore11.sea_reflection = 1;
	Locations[n].models.always.shore11seabed = "sandshore_sb";
	Locations[n].models.always.locators = "sandshore_Qlocators";
	
	Locations[n].models.always.shore11_quest = "sandshore_quest2";
	Locations[n].models.always.shore11_quest_seabed = "sandshorequest_sb";
	locations[n].models.always.shore11_quest.sea_reflection = 1;
	Locations[n].models.always.shore11_sqiut = "sandshore_squit";
	locations[n].models.always.shore11_sqiut.sea_reflection = 1;
	Locations[n].models.always.thing = "sandshore_thing";
	
	Locations[n].models.always.grassPatch = "sandshore_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	locations[n].models.always.l1.sea_reflection = 1;
	
	Locations[n].models.always.Waterfall1 = "WaterFall1";
	Locations[n].models.always.Waterfall1.uvslide.v0 = 0.2;
    Locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall1.level = 50;
	
	Locations[n].models.always.Waterfall2 = "WaterFall2";
	Locations[n].models.always.Waterfall2.uvslide.v0 = 0.3;
    Locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall2.level = 49;
	//Day
	locations[n].models.day.charactersPatch = "sandshore_patch2";
	//Night
	locations[n].models.night.charactersPatch = "sandshore_patch2";	
	// Jump patch
	Locations[n].models.day.jumpPatch = "sandshore_jump_patch";
	Locations[n].models.night.jumpPatch = "sandshore_jump_patch";
	
	Locations[n].animals = "true";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].alwaysStorm = true; //живем в штормах
	locations[n].storm = true;
	locations[n].tornado = true;
	//Reload map
	locations[n].reload.l1.name = "reload2_back";
	locations[n].reload.l1.go = "Ksochitam_WaterGrot";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Cave";
	locations[n].locators_radius.reload.reload2_back = 2;
	
	locations[n].reload.l2.name = "reload1";
	locations[n].reload.l2.go = "SantaQuiteriaInside";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "SantaQuiteriaInside";
	
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "SantaQuiteriaInside";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "SantaQuiteriaInside";
	
	locations[n].reload.l4.name = "boat";
	locations[n].reload.l4.go = "Ksochitam";
	locations[n].reload.l4.emerge = "reload_1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Sea";
    locations[n].locators_radius.reload.boat = 6.0;
	
	locations[n].DisableOfficers = "1";
	
	locations[n].private1.items.mask_false = 1;
	locations[n].private1.key = "key_archy";
	locations[n].private1.key.delItem = true;
	
	locations[n].private2.items.icollection = 8;
	
	locations[n].private3.items.icollection = 10;
	
	locations[n].private4.items.icollection = 14;
	
	locations[n].private5.items.icollection = 8;
	
	locations[n].private6.items.icollection = 12;
	
	locations[n].private7.items.icollection = 13;
	
	locations[n].private8.items.icollection = 8;
	
	locations[n].private9.items.icollection = 15;
	
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Фрегат Санта-Квитерия - внутри корабля
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantaQuiteriaInside";
	locations[n].id.label = "SantaQuiteriaInside";
	locations[n].filespath.models = "locations\Inside\squit";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "x_seashore";
	locations[n].islandId = "Ksochitam";	
	//Models
	//Always	
	Locations[n].models.always.inside = "squit";
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.windows = "squit_win";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;	
	Locations[n].models.always.locators = "squit_loc";
	//Day
	locations[n].models.day.charactersPatch = "squit_patch";
	//Night
	locations[n].models.night.charactersPatch = "squit_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].alwaysStorm = true; //живем в штормах
	locations[n].storm = true;
	locations[n].tornado = true;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "shore66";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "shore66";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "shore66";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "shore66";
	
	locations[n].locators_radius.item.item1 = 1.2;

	//ключи для сундуков и предметы внутри
	locations[n].private1.money = 10000;
	locations[n].private1.items.potion5 = 5;
	locations[n].private1.items.icollecton = 2;

	locations[n].private2.money = 5000;
	locations[n].private2.items.gold_dublon = 300;
	locations[n].private2.items.icollecton = 5;
	
	locations[n].private3.items.icollecton = 6;
	locations[n].private3.items.potion7 = 1;
	
	locations[n].private4.items.icollecton = 4;
	locations[n].private4.items.berserker_potion = 1;
	
	locations[n].private5.items.icollecton = 3;
	locations[n].private5.items.potion7 = 1;
	
	locations[n].private6.items.icollecton = 5;
	locations[n].private6.items.berserker_potion = 1;
	
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли - к маске
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Ksochitam_Jungle_03";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "x_jungle";
	locations[n].islandId = "Ksochitam";
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	locations[n].KsochitamSkeletons = 10; // число монстров в локации
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle11";
	Locations[n].models.always.jungle = "jungle11";	
	Locations[n].models.always.locators = "jungle11_locators";		
	Locations[n].models.always.grassPatch = "jungle11_grass";
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
	locations[n].models.day.charactersPatch = "jungle11_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle11_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	locations[n].alwaysStorm = true; //живем в штормах
	locations[n].storm = true;
	locations[n].tornado = true;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Ksochitam_Jungle_01";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;
	
	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Ksochitam_CaveEntrance";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "CaveEntrance";
	locations[n].locators_radius.reload.reload2_back = 2;

	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в пещеру - к маске Кукулькана
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Ksochitam_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "x_jungle";
	locations[n].islandId = "Ksochitam";
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	locations[n].KsochitamSkeletons = 5; // число монстров в локации
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\CaveEnt2";
	Locations[n].models.always.caveEnt2 = "caveEnt2";	
	Locations[n].models.always.locators = "caveEnt2_locators";		
	Locations[n].models.always.grassPatch = "caveEnt2_grass";
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
	locations[n].models.day.charactersPatch = "caveEnt2_patch";
	//Night
	locations[n].models.night.charactersPatch = "caveEnt2_patch";	
	//Environment	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	locations[n].alwaysStorm = true; //живем в штормах
	locations[n].storm = true;
	locations[n].tornado = true;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Ksochitam_Cave";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Cave";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Ksochitam_Jungle_03";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пещера - к маске
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Ksochitam_Cave";
	locations[n].id.label = "Cave";
	locations[n].image = "loading\inside\cave.tga";
	//Sound
	locations[n].type = "cave";
	locations[n].islandId = "Ksochitam";
	locations[n].DisableEncounters = true;
	locations[n].changeAnimation = "man_A"; //сменить анимацию на обычную
	locations[n].KsochitamSkeletons = 13; // число монстров в локации
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\cavernMedium3";
	locations[n].models.always.cavernMedium3 = "cavernMedium3";
	locations[n].models.always.cavernMedium3.sea_reflection = 1;
	locations[n].models.always.locators = "cavernMedium3_locators";	
	//Day
	locations[n].models.day.charactersPatch = "cavernMedium3_patch";
	Locations[n].models.day.jumpPatch = "CavernMedium3_jump";
	//Night
	locations[n].models.night.charactersPatch = "cavernMedium3_patch";
	Locations[n].models.night.jumpPatch = "CavernMedium3_jump";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	locations[n].MaxWaveHeigh = 0.9;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Ksochitam_CaveEntrance";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Jungle";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Ksochitam_FloodedCaveLock";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "FloodedCave";
	locations[n].locators_radius.reload.reload2 = 1.0;
	
	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Ksochitam_FloodedCave";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "FloodedCave";
	locations[n].locators_radius.reload.reload3_back = 0.2;
	
	locations[n].locators_radius.randitem.randitem1 = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Затопленная пещера - тупиковая
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Ksochitam_FloodedCaveLock";
	locations[n].id.label = "FloodedCave";
	locations[n].image = "loading\inside\cave.tga";
	//Sound
	locations[n].islandId = "Ksochitam";
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
	locations[n].models.always.locators = "cavernLow2_Flocators";
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
	locations[n].reload.l1.name = "reload2_back";
	locations[n].reload.l1.go = "Ksochitam_Cave";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Cave";
	
	locations[n].DisableOfficers = "1";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Затопленная пещера - к маске
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Ksochitam_FloodedCave";
	locations[n].id.label = "FloodedCave";
	locations[n].image = "loading\inside\cave.tga";
	//Sound
	locations[n].islandId = "Ksochitam";
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
	locations[n].models.always.locators = "cavernLow2_locators";
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
	locations[n].reload.l1.go = "Ksochitam_Cave";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Cave";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Ksochitam_DumpGrot";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Grot";
	locations[n].locators_radius.reload.reload2_back = 0.2;
	
	locations[n].DisableOfficers = "1";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Грот подтопленный - к маске
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Ksochitam_DumpGrot";
	locations[n].id.label = "Grot";
	locations[n].image = "loading\inside\cave.tga";
	//Sound
	locations[n].type = "cave";
	locations[n].islandId = "Ksochitam";
	locations[n].DisableEncounters = true;
	locations[n].changeAnimation = "man_A"; //сменить анимацию на обычную
	locations[n].KsochitamSkeletons = 3; // число монстров в локации
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\grotto1";
	locations[n].models.always.grotto1 = "grotto1";
	locations[n].models.always.grotto1alpha = "grotto1_alpha";
	Locations[n].models.always.grotto1alpha.tech = "LocationWindows";	
	locations[n].models.always.grotto1alpha.level = 65532;
	locations[n].models.always.locators = "grotto1_Kslocators";
	locations[n].models.always.ladder = "ladder";
	Locations[n].models.always.ladder.locator.group = "quest";
	Locations[n].models.always.ladder.locator.name = "ladder";
	//Day
	locations[n].models.day.charactersPatch = "grotto1_patch";
	//Night
	locations[n].models.night.charactersPatch = "grotto1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].MaxWaveHeigh = 10.0;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Shore_mask";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Shore_mask";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Ksochitam_FloodedCave";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "FloodedCave";
	locations[n].locators_radius.reload.reload2_back = 1.2;
	
	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Ksochitam_DeadlockGrot";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "grot";
	
	locations[n].DisableOfficers = "1";
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Грот и склеп Стража маски
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore_mask";
	locations[n].id.label = "Shore_mask";
	locations[n].filespath.models = "locations\Outside\Shores\GuardGrot";
	locations[n].image = "loading\inside\cave.tga";
	//Sound
	locations[n].type = "x_seashore";
 	locations[n].islandId = "Ksochitam";
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	locations[n].Chestgennot = true; // не генерить сундуки
	//Models
	//Always
	locations[n].models.always.grot = "Grotto1";
	locations[n].models.always.grot.sea_reflection = 1;
	locations[n].models.always.seabed = "Grotto1_sb";
	locations[n].models.always.grassPatch = "Grotto1_grass";
	locations[n].models.always.locators = "Grotto1_locators";
	
	locations[n].models.always.Cfall = "Cfall";
	locations[n].models.always.Water = "Water";
	
	Locations[n].models.always.Waterfall1 = "Waterfall1";
	Locations[n].models.always.Waterfall1.uvslide.v0 = 0.7;
	Locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall1.level = 50;

	Locations[n].models.always.Waterfall2 = "Waterfall2";
	Locations[n].models.always.Waterfall2.uvslide.v0 = 0.3;
	Locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall2.level = 50;
	//Day
	locations[n].models.day.charactersPatch = "Grotto1_patch";
	//Night
	locations[n].models.night.charactersPatch = "Grotto1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].alwaysStorm = true; //живем в штормах
	locations[n].storm = true;
	locations[n].tornado = true;

	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Ksochitam_DumpGrot";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Grot";
	
	locations[n].DisableOfficers = "1";
	
	string sloc;
	int i;
	for (i=1; i<=95; i++)
	{
		sloc = "fire"+i;
		locations[n].locators_radius.item.(sloc) = 1.0;
	}
	for (i=1; i<=4; i++)
	{
		sloc = "incasfire"+i;
		locations[n].locators_radius.item.(sloc) = 1.5;
	}
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Тупиковый грот
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Ksochitam_DeadlockGrot";
	locations[n].id.label = "grot";
	locations[n].image = "loading\inside\cave.tga";
	//Sound
	locations[n].type = "cave";
	locations[n].islandId = "Ksochitam";
	locations[n].DisableEncounters = true;
	locations[n].KsochitamSkeletons = 4; // число монстров в локации
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\grotto3";
	locations[n].models.always.grotto3 = "grotto3";
	locations[n].models.always.l1 = "Grotenve2";
	locations[n].models.always.locators = "grotto3_locators";
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
	locations[n].reload.l1.go = "Ksochitam_DumpGrot";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "grot";
	locations[n].locators_radius.reload.reload1_back = 1.5;
	
	locations[n].DisableOfficers = "1";
	n = n + 1;
		
	return n;
}