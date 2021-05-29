
int LocationInitPearl(int n)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Деревня мискито
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Miskito_village";
	locations[n].id.label = "Village";
	Locations[n].image = "loading\Village.tga";
	locations[n].pearlVillage = 1;
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Pearl";
	//Models
	//Always
	Locations[n].filespath.models = "locations\Outside\IndianVillage";
	Locations[n].models.always.village = "village";	
	Locations[n].models.always.locators = "village_locators";
	Locations[n].models.always.grassPatch = "village_grass";
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
	locations[n].models.day.charactersPatch = "village_patch";
	//Night
	locations[n].models.night.charactersPatch = "village_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map	
	Locations[n].reload.l1.name = "reload1_back";
	Locations[n].reload.l1.go = "Pearl_Jungle_02";
	Locations[n].reload.l1.emerge = "reload2";
	Locations[n].reload.l1.label = "Jungle";
	Locations[n].reload.l1.autoreload = 1;
	Locations[n].locators_radius.reload.reload1_back = 2;
	
	Locations[n].reload.l2.name = "reload2";
	Locations[n].reload.l2.go = "Miskito_shack1";
	Locations[n].reload.l2.emerge = "reload1";
	Locations[n].reload.l2.label = "shack";
	Locations[n].reload.l2.autoreload = "0";
	
	Locations[n].reload.l3.name = "reload3";
	Locations[n].reload.l3.go = "Miskito_shack2";
	Locations[n].reload.l3.emerge = "reload1";
	Locations[n].reload.l3.label = "shack";
	Locations[n].reload.l3.autoreload = "0";
	
	Locations[n].reload.l4.name = "reload4";
	Locations[n].reload.l4.go = "Miskito_shack3";
	Locations[n].reload.l4.emerge = "reload1";
	Locations[n].reload.l4.label = "shack";
	Locations[n].reload.l4.autoreload = "0";

	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//// хижина №1 - большая
	/////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Miskito_shack1";
	locations[n].id.label = "shack";
	locations[n].image = "loading\inside\Vigwam.tga";
	//Town sack
	locations[n].townsack = "Miskito_village";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Mein";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Hut_1_inside";
	locations[n].models.always.Hut_1_inside = "Hut_1_inside";
	locations[n].models.always.Hut_1_inside.level = 65538;
	Locations[n].models.always.locators = "Hut_1_inside_locators";

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Hut_1_inside_patch";
	//Night
	locations[n].models.night.charactersPatch = "Hut_1_inside_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Miskito_village";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//// хижина №2 Змеиного Глаза
	/////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Miskito_shack2";
	locations[n].id.label = "shack";
	locations[n].image = "loading\inside\Vigwam.tga";
	//Town sack
	locations[n].townsack = "Miskito_village";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Mein";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Hut_2_inside";
	locations[n].models.always.Hut_2_inside = "Hut_2_inside";
	locations[n].models.always.Hut_2_inside.level = 65538;
	Locations[n].models.always.Hut_2_insiderand = "Hut_2_inside_rand_1";
	locations[n].models.always.Hut_2_back = "Hut_2_back";
	locations[n].models.always.Hut_2_back.level = 65538; 
	locations[n].models.always.back = "..\inside_back2";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Hut_2_inside_patch";
	locations[n].models.day.locators = "Hut_2_inside_locators";
	//Night
	locations[n].models.night.charactersPatch = "Hut_2_inside_patch";
	locations[n].models.night.locators = "Hut_2_inside_locators";
	//locations[n].models.night.locators = "Hut_2_inside_ln";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Miskito_village";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//// хижина №3
	/////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Miskito_shack3";
	locations[n].id.label = "shack";
	locations[n].image = "loading\inside\Vigwam.tga";
	//Town sack
	locations[n].townsack = "Miskito_village";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Mein";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Hut_2_inside";
	locations[n].models.always.Hut_2_inside = "Hut_2_inside";
	locations[n].models.always.Hut_2_inside.level = 65538;
	Locations[n].models.always.Hut_2_insiderand = "Hut_2_inside_rand_2";
	locations[n].models.always.Hut_2_back = "Hut_2_back";
	locations[n].models.always.Hut_2_back.level = 65538; 
	locations[n].models.always.back = "..\inside_back2";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.locators = "Hut_2_inside_locators";
	locations[n].models.day.charactersPatch = "Hut_2_inside_patch";
	//Night
	locations[n].models.night.charactersPatch = "Hut_2_inside_patch";
	locations[n].models.night.locators = "Hut_2_inside_locators";
	//locations[n].models.night.locators = "Hut_2_inside_ln";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Miskito_village";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// залив Папагайо
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore49";
	locations[n].id.label = "Shore49";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "Shore49";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Pearl";
	locations[n].questflower = 1;
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
	locations[n].reload.l1.go = "Pearl_Jungle_01";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Pearl_Jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Pearl";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle6";
	Locations[n].models.always.jungle = "jungle6";	
	Locations[n].models.always.locators = "jungle6_locators";		
	Locations[n].models.always.grassPatch = "jungle6_grass";
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
	locations[n].models.day.charactersPatch = "jungle6_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle6_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Pearl_Jungle_02";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore49";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore49";
    locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Shore50";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Shore50";
	locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// залив Никоя
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore50";
	locations[n].id.label = "Shore50";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "Shore50";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Pearl";
	locations[n].questflower = 1;
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
	locations[n].reload.l1.go = "Pearl_Jungle_01";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Pearl_Jungle_02";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Pearl";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle7";
	Locations[n].models.always.jungle = "jungle7";	
	Locations[n].models.always.locators = "jungle7_locators";		
	Locations[n].models.always.grassPatch = "jungle7_grass";
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
	locations[n].models.day.charactersPatch = "jungle7_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle7_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Pearl_Jungle_03";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Miskito_village"; //поселение ловцов
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Village";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Pearl_Jungle_01";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "ExitTown";
	locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Pearl_Jungle_03";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Pearl";
	locations[n].questflower = 1;
	locations[n].dolly = 1;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle3";
	Locations[n].models.always.jungle = "jungle3";	
	Locations[n].models.always.locators = "jungle3_Dollylocators";	
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
	Locations[n].models.always.bracing = "bracing";	
	locations[n].models.always.bracing.locator.group = "item";
	locations[n].models.always.bracing.locator.name = "dolly1";
	//Day
	locations[n].models.day.charactersPatch = "jungle3_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle3_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Pearl_Jungle_02";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Pearl_Jungle_04";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Pearl_GrotEntrance";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2.0;
	
	locations[n].locators_radius.item.dolly1 = 1.0;
	locations[n].locators_radius.item.button01 = 1.2;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в грот
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Pearl_GrotEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Pearl";
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
	Locations[n].models.always.l4 = "plan4";
	Locations[n].models.always.l4.level = 6;
	Locations[n].models.always.l4.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "caveEnt2_patch";
	//Night
	locations[n].models.night.charactersPatch = "caveEnt2_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l3.name = "reload1_back";
	locations[n].reload.l3.go = "Pearl_Grot";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Grot";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Pearl_Jungle_03";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Грот
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Pearl_Grot";
	locations[n].id.label = "Grot";
    locations[n].image = "loading\inside\cave.tga";
	//Sound
	locations[n].type = "cave";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Pearl";
	locations[n].questflower = 1;
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\grotto1";
	locations[n].models.always.grotto1 = "grotto1";
	locations[n].models.always.grotto1alpha = "grotto1_alpha";
	Locations[n].models.always.grotto1alpha.tech = "LocationWindows";	
	locations[n].models.always.grotto1alpha.level = 65532;
	locations[n].models.always.chest = "chest";	
	locations[n].models.always.locators = "grotto1_locators";

	locations[n].locators_radius.item.duhi1 = 0.0;
/*	
	Locations[n].models.always.rays = "grotto1_rays";
	Locations[n].models.always.rays.level = 49;
	Locations[n].models.always.rays.tech= "LocVisRays";
	Locations[n].models.always.rays.uvslide.u1 = -0.03;
	Locations[n].models.always.rays.uvslide.v1 = -0.03;	
*/	
	//Day
	locations[n].models.day.charactersPatch = "grotto1_patch";
	//Night
	locations[n].models.night.charactersPatch = "grotto1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Pearl_GrotEntrance";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Cave entrance";
	locations[n].locators_radius.reload.reload1_back = 2;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Pearl_Jungle_04";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
 	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Pearl";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\jungle8\";
	Locations[n].models.always.jungle = "jungle8";	
	Locations[n].models.always.locators = "jungle8_locators";		
	Locations[n].models.always.grassPatch = "jungle8_grass";
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
	locations[n].models.day.charactersPatch = "jungle8_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle8_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tenotchitlan_Jungle_01";                    // на теночитлан
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Pearl_Jungle_03";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// залив Коронадо
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore51";
	locations[n].id.label = "Shore51";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "Shore51";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Pearl";
	locations[n].questflower = 1;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Shore09";
	Locations[n].models.always.shore09 = "shore09";
	locations[n].models.always.shore09.sea_reflection = 1;
	Locations[n].models.always.shore09seabed = "shore09_sb";
	Locations[n].models.always.locators = "shore09_locators";
		
	Locations[n].models.always.grassPatch = "shore09_grass";
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
	locations[n].models.day.charactersPatch = "shore09_patch";
	//Night
	locations[n].models.night.charactersPatch = "shore09_patch";		
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Pearl_Jungle_06";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Pearl_Jungle_06";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	locations[n].DisableEncounters = true;
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Pearl";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle2";
	Locations[n].models.always.jungle = "jungle2";	
	Locations[n].models.always.locators = "jungle2_locators";		
	Locations[n].models.always.grassPatch = "jungle2_grass";
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
	locations[n].models.day.charactersPatch = "jungle2_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle2_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Bravo_village";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Village";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Pearl_CaveEntrance";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Cave entrance";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Shore51";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Shore51";
	locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в пещеру
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Pearl_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Pearl";
	locations[n].questflower = 1;
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
	Locations[n].models.always.l4 = "plan4";
	Locations[n].models.always.l4.level = 6;
	Locations[n].models.always.l4.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "caveEnt2_patch";
	//Night
	locations[n].models.night.charactersPatch = "caveEnt2_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "SantaCatalina_PearlCave";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Cave";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Pearl_Jungle_06"; //выход с Санта Каталины
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Деревня индейцев браво
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Bravo_village";
	locations[n].id.label = "Village";
	Locations[n].image = "loading\Village.tga";
	locations[n].pearlVillage = 2;
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Pearl";
	//Models
	//Always
	Locations[n].filespath.models = "locations\Outside\IndianVillage";
	Locations[n].models.always.village = "village";	
	Locations[n].models.always.locators = "village_locators";
	Locations[n].models.always.grassPatch = "village_grass";
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
	locations[n].models.day.charactersPatch = "village_patch";
	//Night
	locations[n].models.night.charactersPatch = "village_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	Locations[n].reload.l1.name = "reload1_back";
	Locations[n].reload.l1.go = "Pearl_Jungle_06";
	Locations[n].reload.l1.emerge = "reload1";
	Locations[n].reload.l1.label = "Jungle";
	Locations[n].reload.l1.autoreload = 1;
	Locations[n].locators_radius.reload.reload1_back = 2;

	Locations[n].reload.l2.name = "reload2";
	Locations[n].reload.l2.go = "Bravo_shack1";
	Locations[n].reload.l2.emerge = "reload1";
	Locations[n].reload.l2.label = "shack";
	Locations[n].reload.l2.autoreload = "0";

	Locations[n].reload.l3.name = "reload3";
	Locations[n].reload.l3.go = "Bravo_shack2";
	Locations[n].reload.l3.emerge = "reload1";
	Locations[n].reload.l3.label = "shack";
	Locations[n].reload.l3.autoreload = "0";

	Locations[n].reload.l4.name = "reload4";
	Locations[n].reload.l4.go = "Bravo_shack3";
	Locations[n].reload.l4.emerge = "reload1";
	Locations[n].reload.l4.label = "shack";
	Locations[n].reload.l4.autoreload = "0";

	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//// хижина №1 - большая
	/////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Bravo_shack1";
	locations[n].id.label = "shack";
	locations[n].image = "loading\inside\Vigwam.tga";
	//Town sack
	locations[n].townsack = "Bravo_village";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Mein";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Hut_1_inside";
	locations[n].models.always.Hut_1_inside = "Hut_1_inside";
	locations[n].models.always.Hut_1_inside.level = 65538;
	Locations[n].models.always.locators = "Hut_1_inside_locators";

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Hut_1_inside_patch";
	//Night
	locations[n].models.night.charactersPatch = "Hut_1_inside_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Bravo_village";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//// хижина №2 
	/////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Bravo_shack2";
	locations[n].id.label = "shack";
	locations[n].image = "loading\inside\Vigwam.tga";
	//Town sack
	locations[n].townsack = "Bravo_village";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Mein";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Hut_2_inside";
	locations[n].models.always.Hut_2_inside = "Hut_2_inside";
	locations[n].models.always.Hut_2_inside.level = 65538;
	Locations[n].models.always.Hut_2_insiderand = "Hut_2_inside_rand_1";
	locations[n].models.always.Hut_2_back = "Hut_2_back";
	locations[n].models.always.Hut_2_back.level = 65538; 
	locations[n].models.always.back = "..\inside_back2";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Hut_2_inside_patch";
	locations[n].models.day.locators = "Hut_2_inside_locators";
	//Night
	locations[n].models.night.charactersPatch = "Hut_2_inside_patch";
	locations[n].models.night.locators = "Hut_2_inside_locators";
	//locations[n].models.night.locators = "Hut_2_inside_ln";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Bravo_village";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//// хижина №3
	/////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Bravo_shack3";
	locations[n].id.label = "shack";
	locations[n].image = "loading\inside\Vigwam.tga";
	//Town sack
	locations[n].townsack = "Bravo_village";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Mein";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Hut_2_inside";
	locations[n].models.always.Hut_2_inside = "Hut_2_inside";
	locations[n].models.always.Hut_2_inside.level = 65538;
	Locations[n].models.always.Hut_2_insiderand = "Hut_2_inside_rand_2";
	locations[n].models.always.Hut_2_back = "Hut_2_back";
	locations[n].models.always.Hut_2_back.level = 65538; 
	locations[n].models.always.back = "..\inside_back2";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.locators = "Hut_2_inside_locators";
	locations[n].models.day.charactersPatch = "Hut_2_inside_patch";
	//Night
	locations[n].models.night.charactersPatch = "Hut_2_inside_patch";
	locations[n].models.night.locators = "Hut_2_inside_locators";
	//locations[n].models.night.locators = "Hut_2_inside_ln";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Bravo_village";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	
	n = n + 1;

	return n;
}