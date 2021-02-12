
int LocationInitTenotchitlan(int n)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Теночтитлан
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли  ----------- ход к пирамиде и жемчужным промыслам из бухты Аматике (shore9)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tenotchitlan_Jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\jungle1\";
	Locations[n].models.always.jungle = "jungle1";
	Locations[n].models.always.locators = "jungle1_locators";		
	Locations[n].models.always.grassPatch = "jungle1_grass";
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
	locations[n].models.day.charactersPatch = "jungle1_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle1_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Pearl_Jungle_04"; //жемчужный берег
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.5;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tenotchitlan_Jungle_02";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tenotchitlan_Jungle_02";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	locations[n].questflower = 1;
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
	locations[n].reload.l1.go = "Tenotchitlan_Jungle_01";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tenotchitlan_Jungle_03";       // на Shore9
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Temple";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2.0;
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пирамида
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Temple";
	Locations[n].image = "loading\outside\temple.tga";
	//Sound
	locations[n].type = "teno";
	locations[n].id.label = "Incas Temple";
 	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	//Models
	//Always
	Locations[n].filespath.models = "locations\Outside\pyramid1\";
	Locations[n].models.always.pyramid1 = "pyramid1";
	locations[n].models.always.pyramid1.sea_reflection = 1;
	Locations[n].models.always.pyramid1seabed = "pyramid1_sb";
	Locations[n].models.always.locators = "pyramid1_locators";
	
	Locations[n].models.always.grassPatch = "pyramid1_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
			
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 99948;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 99947;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 99946;
	Locations[n].models.always.l3.tech = "LocationModelBlend";
	Locations[n].models.always.l4 = "plan4";
	Locations[n].models.always.l4.level = 99945;
	Locations[n].models.always.l4.tech = "LocationModelBlend";	
	//Waterfall
	Locations[n].models.always.Waterfall1 = "waterfall1";
	Locations[n].models.always.Waterfall1.uvslide.v0 = 0.2;
    Locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall1.level = 99950;
	
	Locations[n].models.always.Waterfall2 = "waterfall2";
	Locations[n].models.always.Waterfall2.uvslide.v0 = 0.3;
    Locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall2.level = 99949;	
	//Day
	locations[n].models.day.charactersPatch = "pyramid1_patch";
	//Night
	locations[n].models.night.charactersPatch = "pyramid1_patch";		
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	Locations[n].reload.l1.name = "reload1_back";
	Locations[n].reload.l1.go = "Tenotchitlan_Jungle_02";
	Locations[n].reload.l1.emerge = "reload3";
	Locations[n].reload.l1.autoreload = "1";
	Locations[n].locators_radius.reload.reload1_back = 3;

	Locations[n].reload.l2.name = "reload2";
	Locations[n].reload.l2.go = "Temple_Inside";
	Locations[n].reload.l2.emerge = "reload1";
	Locations[n].reload.l2.autoreload = "0";
	Locations[n].reload.l2.disable = true;
	Locations[n].locators_radius.item.item1 = 0.9;
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пирамида Старая Изнутри
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Temple_Inside";
	locations[n].id.label = "Pyramid1Inside";
	Locations[n].image = "loading\outside\TempleInside.tga";	
	//Sound
	locations[n].type = "teno_inside";
	locations[n].id.label = "Incas Temple";
 	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	//Models
	//Always
	Locations[n].filespath.models = "Locations\Inside\Pyramid1Inside\";
	//Always	
	Locations[n].models.always.pyramid1 = "Pyramid1Inside";
	Locations[n].models.always.locators = "Pyramid1Inside_locators";	
	//Day
	locations[n].models.day.charactersPatch = "Pyramid1Inside_patch";
	//Night
	locations[n].models.night.charactersPatch = "Pyramid1Inside_patch";			
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Temple";
	Locations[n].reload.l1.emerge = "reload2";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].locators_radius.item.item1 = 1.1;
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tenotchitlan_Jungle_03";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
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
	locations[n].reload.l1.go = "Beliz_jungle_02"; //из Белиза от бухты Аматике
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tenotchitlan_Jungle_02";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Tenotchitlan_CaveEntrance";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в пещеру
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tenotchitlan_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
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
	locations[n].reload.l3.go = "Tenotchitlan_Cave";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Cave";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tenotchitlan_Jungle_03";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пещера
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tenotchitlan_Cave";
	locations[n].id.label = "Cave";
	locations[n].image = "loading\inside\cave.tga";
	//Sound
	locations[n].type = "cave";
 	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\cavernMedium1";
	locations[n].models.always.cavernMedium1 = "cavernMedium1";
	locations[n].models.always.cavernMedium1.sea_reflection = 1;
	locations[n].models.always.lamps = "cavernMedium1_lamps";	
	locations[n].models.always.locators = "cavernMedium1_locators";	

	locations[n].locators_radius.item.duhi1 = 0.0;
/*	
	Locations[n].models.always.rays = "cavernMedium1_rays";
	Locations[n].models.always.rays.level = 49;
	Locations[n].models.always.rays.tech= "LocVisRays";
	Locations[n].models.always.rays.uvslide.u1 = -0.03;
	Locations[n].models.always.rays.uvslide.v1 = -0.03;	
*/	
	//Day
	locations[n].models.day.charactersPatch = "cavernMedium1_patch";
	Locations[n].models.day.jumpPatch = "CavernMedium1_jump";
	//Night
	locations[n].models.night.charactersPatch = "cavernMedium1_patch";
	Locations[n].models.night.jumpPatch = "CavernMedium1_jump";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tenotchitlan_CaveEntrance";
	locations[n].reload.l1.emerge = "reload1";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tenotchitlan_Jungle_05";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\jungle1\";
	Locations[n].models.always.jungle = "jungle1";
	Locations[n].models.always.locators = "jungle1_locators";		
	Locations[n].models.always.grassPatch = "jungle1_grass";
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
	locations[n].models.day.charactersPatch = "jungle1_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle1_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";    //на мыс Перлас
	locations[n].reload.l1.go = "Shore53";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.5;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tenotchitlan_Jungle_06";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Tenotchitlan_Jungle_06";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
 	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\jungle8";
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
//	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.go = "Mine_03";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Shore9";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tenotchitlan_Jungle_05";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Тайясаль
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tenochtitlan";
	locations[n].id.label = "Tenochtitlan";
	locations[n].filespath.models = "locations\Tenochtitlan";
	locations[n].image = "loading\outside\TenochtitlanCity.tga";
	//Sound
	locations[n].type = "teno";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	locations[n].changeAnimation = "man_A"; //сменить анимацию на обычную
	//Models
	//Always
	locations[n].models.always.Tenochtitlan = "Tenochtitlan";
	locations[n].models.always.reflect = "Tenochtitlan_reflect";
	locations[n].models.always.reflect.sea_reflection = 1;
	locations[n].models.always.seabed = "Tenochtitlan_sb";
	locations[n].models.always.grassPatch = "Tenochtitlan_grass";
	Locations[n].models.day.jumpPatch = "Tenochtitlan_jamp";
	Locations[n].models.night.jumpPatch = "Tenochtitlan_jamp";
	locations[n].models.always.locators = "Tenochtitlan_locators";
	locations[n].models.always.plan = "plan1";
	locations[n].models.always.plan.level = 12;
	locations[n].models.always.plan = "plan2";
	locations[n].models.always.plan.level = 11;
	locations[n].models.always.plan = "plan3";
	locations[n].models.always.plan.level = 10;
	locations[n].models.always.plan = "plan4";
	locations[n].models.always.plan.level = 9;	
	//Day
	locations[n].models.day.charactersPatch = "Tenochtitlan_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tenochtitlan_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l99.name = "reload1_back";
	locations[n].reload.l99.go = "Tayasal_jungle_11";
	locations[n].reload.l99.emerge = "reload3";
	locations[n].reload.l99.autoreload = "1";
	locations[n].locators_radius.reload.reload1_back = 2.0;
	
	// храмы богов майя
	//---------- храм Тохила ----------
	locations[n].reload.l1.name = "reloadTemple1";
	locations[n].reload.l1.go = "Temple_1";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l2.name = "reloadTemple2";
	locations[n].reload.l2.go = "Temple_1";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l3.name = "reloadTemple3";
	locations[n].reload.l3.go = "Temple_1";
	locations[n].reload.l3.emerge = "reload3";
	locations[n].reload.l4.name = "reloadTemple4";
	locations[n].reload.l4.go = "Temple_1";
	locations[n].reload.l4.emerge = "reload4";
	locations[n].reload.l5.name = "reloadTemple5";
	locations[n].reload.l5.go = "Temple_1";
	locations[n].reload.l5.emerge = "reload5";
	
	//---------- храм Кавиля ----------
	locations[n].reload.l6.name = "reloadTemple6";
	locations[n].reload.l6.go = "Temple_2";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l7.name = "reloadTemple7";
	locations[n].reload.l7.go = "Temple_2";
	locations[n].reload.l7.emerge = "reload2";
	locations[n].reload.l8.name = "reloadTemple8";
	locations[n].reload.l8.go = "Temple_2";
	locations[n].reload.l8.emerge = "reload3";
	locations[n].reload.l9.name = "reloadTemple9";
	locations[n].reload.l9.go = "Temple_2";
	locations[n].reload.l9.emerge = "reload4";
	locations[n].reload.l10.name = "reloadTemple10";
	locations[n].reload.l10.go = "Temple_2";
	locations[n].reload.l10.emerge = "reload5";
	
	//---------- храм Чака ----------
	locations[n].reload.l11.name = "reloadTemple11";
	locations[n].reload.l11.go = "Temple_3";
	locations[n].reload.l11.emerge = "reload1";
	locations[n].reload.l12.name = "reloadTemple12";
	locations[n].reload.l12.go = "Temple_3";
	locations[n].reload.l12.emerge = "reload2";
	locations[n].reload.l13.name = "reloadTemple13";
	locations[n].reload.l13.go = "Temple_3";
	locations[n].reload.l13.emerge = "reload3";
	locations[n].reload.l14.name = "reloadTemple14";
	locations[n].reload.l14.go = "Temple_3";
	locations[n].reload.l14.emerge = "reload4";
	locations[n].reload.l15.name = "reloadTemple15";
	locations[n].reload.l15.go = "Temple_3";
	locations[n].reload.l15.emerge = "reload5";
	
	//---------- храм Кинич-Ахау ----------
	locations[n].reload.l16.name = "reloadTemple16";
	locations[n].reload.l16.go = "Temple_4";
	locations[n].reload.l16.emerge = "reload1";
	locations[n].reload.l17.name = "reloadTemple17";
	locations[n].reload.l17.go = "Temple_4";
	locations[n].reload.l17.emerge = "reload2";
	locations[n].reload.l18.name = "reloadTemple18";
	locations[n].reload.l18.go = "Temple_4";
	locations[n].reload.l18.emerge = "reload3";
	locations[n].reload.l19.name = "reloadTemple19";
	locations[n].reload.l19.go = "Temple_4";
	locations[n].reload.l19.emerge = "reload4";
	locations[n].reload.l20.name = "reloadTemple20";
	locations[n].reload.l20.go = "Temple_4";
	locations[n].reload.l20.emerge = "reload5";
	
	//---------- храм Ицамны ----------
	locations[n].reload.l21.name = "reloadTemple21";
	locations[n].reload.l21.go = "Temple_5";
	locations[n].reload.l21.emerge = "reload1";
	locations[n].reload.l22.name = "reloadTemple22";
	locations[n].reload.l22.go = "Temple_5";
	locations[n].reload.l22.emerge = "reload2";
	locations[n].reload.l23.name = "reloadTemple23";
	locations[n].reload.l23.go = "Temple_5";
	locations[n].reload.l23.emerge = "reload3";
	locations[n].reload.l24.name = "reloadTemple24";
	locations[n].reload.l24.go = "Temple_5";
	locations[n].reload.l24.emerge = "reload4";
	locations[n].reload.l25.name = "reloadTemple25";
	locations[n].reload.l25.go = "Temple_5";
	locations[n].reload.l25.emerge = "reload5";
	
	//---------- храм Эк-Чуах ----------
	locations[n].reload.l26.name = "reloadTemple26";
	locations[n].reload.l26.go = "Temple_6";
	locations[n].reload.l26.emerge = "reload1";
	locations[n].reload.l27.name = "reloadTemple27";
	locations[n].reload.l27.go = "Temple_6";
	locations[n].reload.l27.emerge = "reload2";
	locations[n].reload.l28.name = "reloadTemple28";
	locations[n].reload.l28.go = "Temple_6";
	locations[n].reload.l28.emerge = "reload3";
	locations[n].reload.l29.name = "reloadTemple29";
	locations[n].reload.l29.go = "Temple_6";
	locations[n].reload.l29.emerge = "reload4";
	locations[n].reload.l30.name = "reloadTemple30";
	locations[n].reload.l30.go = "Temple_6";
	locations[n].reload.l30.emerge = "reload5";
	
	//---------- круглый храм Кукулькана ----------
	locations[n].reload.l31.name = "reloadTemple31";
	locations[n].reload.l31.go = "Temple_round";
	locations[n].reload.l31.emerge = "reload1";
	locations[n].reload.l31.disable = true;

	//---------- храм большой ----------
	// верхний вход
	locations[n].reload.l32.name = "reloadTemple32";
	locations[n].reload.l32.go = "Temple_great";
	locations[n].reload.l32.emerge = "reload1";
	locations[n].reload.l32.disable = true;
	locations[n].reload.l33.name = "reloadTemple33";
	locations[n].reload.l33.go = "Temple_great";
	locations[n].reload.l33.emerge = "reload2";
	locations[n].reload.l33.disable = true;
	locations[n].reload.l34.name = "reloadTemple34";
	locations[n].reload.l34.go = "Temple_great";
	locations[n].reload.l34.emerge = "reload3";
	locations[n].reload.l34.disable = true;
	// нижний правый вход
	locations[n].reload.l35.name = "reloadTemple41";
	locations[n].reload.l35.go = "Temple_great";
	locations[n].reload.l35.emerge = "reload4";
	locations[n].reload.l36.name = "reloadTemple42";
	locations[n].reload.l36.go = "Temple_great";
	locations[n].reload.l36.emerge = "reload5";
	locations[n].reload.l37.name = "reloadTemple43";
	locations[n].reload.l37.go = "Temple_great";
	locations[n].reload.l37.emerge = "reload6";
	// нижний левый вход
	locations[n].reload.l38.name = "reloadTemple38";
	locations[n].reload.l38.go = "Temple_great";
	locations[n].reload.l38.emerge = "reload11";
	locations[n].reload.l39.name = "reloadTemple39";
	locations[n].reload.l39.go = "Temple_great";
	locations[n].reload.l39.emerge = "reload8";
	locations[n].reload.l40.name = "reloadTemple40";
	locations[n].reload.l40.go = "Temple_great";
	locations[n].reload.l40.emerge = "reload7";
	
	//---------- сокровищница ----------
	locations[n].reload.l41.name = "reloadTemple35";
	locations[n].reload.l41.go = "Temple_Treasure";
	locations[n].reload.l41.emerge = "reload1";
	locations[n].reload.l41.disable = true;
	locations[n].reload.l42.name = "reloadTemple36";
	locations[n].reload.l42.go = "Temple_Treasure";
	locations[n].reload.l42.emerge = "reload1";
	locations[n].reload.l42.disable = true;
	locations[n].reload.l43.name = "reloadTemple37";
	locations[n].reload.l43.go = "Temple_Treasure";
	locations[n].reload.l43.emerge = "reload1";
	locations[n].reload.l43.disable = true;
	
	//---------- подводные лабиринты ----------
	locations[n].reload.l44.name = "reloadU1_back";
	locations[n].reload.l44.go = "Temple_Underwater_right";
	locations[n].reload.l44.emerge = "reload1";
	locations[n].reload.l44.autoreload = "1";
	locations[n].locators_radius.reload.reloadU1_back = 3.0;
	locations[n].reload.l45.name = "reloadU2_back";
	locations[n].reload.l45.go = "Temple_Underwater_left";
	locations[n].reload.l45.emerge = "reload1";
	locations[n].reload.l45.autoreload = "1";
	locations[n].locators_radius.reload.reloadU2_back = 3.0;
	locations[n].locators_radius.teleport.fire1 = 4.1;
	
	locations[n].DisableOfficers = "1";
	
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Храмы богов
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//----------------- Храм Кавиля ------------------------	
	locations[n].id = "Temple_1";
	locations[n].id.label = "Temple_1";
	locations[n].filespath.models = "locations\TenochtitlanInside\TemplePointInside";
	locations[n].image = "loading\outside\TempleInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TemplePointInside";
	locations[n].models.always.locators = "TemplePointInside_locators";	
	//Day
	locations[n].models.day.charactersPatch = "TemplePointInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TemplePointInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple1";
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Tenochtitlan";
	locations[n].reload.l2.emerge = "reloadTemple2";
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Tenochtitlan";
	locations[n].reload.l3.emerge = "reloadTemple3";
	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "Tenochtitlan";
	locations[n].reload.l4.emerge = "reloadTemple4";
	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "Tenochtitlan";
	locations[n].reload.l5.emerge = "reloadTemple5";
	
	locations[n].DisableOfficers = "1";
	n = n + 1;
	
	//----------------- Храм Тохила ------------------------
	locations[n].id = "Temple_2";
	locations[n].id.label = "Temple_2";
	locations[n].filespath.models = "locations\TenochtitlanInside\TemplePointInside";
	locations[n].image = "loading\outside\TempleInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TemplePointInside";
	locations[n].models.always.locators = "TemplePointInside_locators";	
	//Day
	locations[n].models.day.charactersPatch = "TemplePointInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TemplePointInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple6";
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Tenochtitlan";
	locations[n].reload.l2.emerge = "reloadTemple7";
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Tenochtitlan";
	locations[n].reload.l3.emerge = "reloadTemple8";
	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "Tenochtitlan";
	locations[n].reload.l4.emerge = "reloadTemple9";
	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "Tenochtitlan";
	locations[n].reload.l5.emerge = "reloadTemple10";
	
	locations[n].DisableOfficers = "1";
	n = n + 1;
	
	//----------------- Храм Чака ------------------------
	locations[n].id = "Temple_3";
	locations[n].id.label = "Temple_3";
	locations[n].filespath.models = "locations\TenochtitlanInside\TemplePointInside";
	locations[n].image = "loading\outside\TempleInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TemplePointInside";
	locations[n].models.always.locators = "TemplePointInside_locators";	
	//Day
	locations[n].models.day.charactersPatch = "TemplePointInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TemplePointInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple11";
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Tenochtitlan";
	locations[n].reload.l2.emerge = "reloadTemple12";
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Tenochtitlan";
	locations[n].reload.l3.emerge = "reloadTemple13";
	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "Tenochtitlan";
	locations[n].reload.l4.emerge = "reloadTemple14";
	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "Tenochtitlan";
	locations[n].reload.l5.emerge = "reloadTemple15";
	
	locations[n].DisableOfficers = "1";
	n = n + 1;
	
	//----------------- Храм Кинич-Ахау ------------------------
	locations[n].id = "Temple_4";
	locations[n].id.label = "Temple_4";
	locations[n].filespath.models = "locations\TenochtitlanInside\TemplePointInside";
	locations[n].image = "loading\outside\TempleInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TemplePointInside";
	locations[n].models.always.locators = "TemplePointInside_locators";	
	//Day
	locations[n].models.day.charactersPatch = "TemplePointInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TemplePointInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple16";
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Tenochtitlan";
	locations[n].reload.l2.emerge = "reloadTemple17";
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Tenochtitlan";
	locations[n].reload.l3.emerge = "reloadTemple18";
	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "Tenochtitlan";
	locations[n].reload.l4.emerge = "reloadTemple19";
	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "Tenochtitlan";
	locations[n].reload.l5.emerge = "reloadTemple20";
	
	locations[n].DisableOfficers = "1";
	n = n + 1;
	
	//----------------- Храм Ицамны ------------------------
	locations[n].id = "Temple_5";
	locations[n].id.label = "Temple_5";
	locations[n].filespath.models = "locations\TenochtitlanInside\TemplePointInside";
	locations[n].image = "loading\outside\TempleInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TemplePointInside";
	locations[n].models.always.locators = "TemplePointInside_locators";	
	//Day
	locations[n].models.day.charactersPatch = "TemplePointInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TemplePointInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple21";
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Tenochtitlan";
	locations[n].reload.l2.emerge = "reloadTemple22";
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Tenochtitlan";
	locations[n].reload.l3.emerge = "reloadTemple23";
	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "Tenochtitlan";
	locations[n].reload.l4.emerge = "reloadTemple24";
	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "Tenochtitlan";
	locations[n].reload.l5.emerge = "reloadTemple25";
	
	locations[n].DisableOfficers = "1";
	n = n + 1;
	
	//----------------- Храм Эк-Чуах ------------------------
	locations[n].id = "Temple_6";
	locations[n].id.label = "Temple_6";
	locations[n].filespath.models = "locations\TenochtitlanInside\TemplePointInside";
	locations[n].image = "loading\outside\TempleInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TemplePointInside";
	locations[n].models.always.locators = "TemplePointInside_locators";	
	//Day
	locations[n].models.day.charactersPatch = "TemplePointInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TemplePointInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple26";
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Tenochtitlan";
	locations[n].reload.l2.emerge = "reloadTemple27";
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Tenochtitlan";
	locations[n].reload.l3.emerge = "reloadTemple28";
	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "Tenochtitlan";
	locations[n].reload.l4.emerge = "reloadTemple29";
	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "Tenochtitlan";
	locations[n].reload.l5.emerge = "reloadTemple30";
	
	locations[n].DisableOfficers = "1";
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Большой Храм
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Temple_great";
	locations[n].id.label = "TempleGreatInside";
	locations[n].filespath.models = "locations\TenochtitlanInside\TempleGreatInside";
	locations[n].image = "loading\outside\TempleInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	locations[n].changeAnimation = "man_A"; //сменить анимацию на обычную
	//Models
	//Always
	locations[n].models.always.TemplePointInside = "TempleGreatInside";
	locations[n].models.always.locators = "TempleGreatInside_locators";	
	Locations[n].models.always.disk = "destroyer";	
	locations[n].models.always.disk.locator.group = "item";
	locations[n].models.always.disk.locator.name = "button04";
	Locations[n].models.always.button = "button03_border";
	//Day
	locations[n].models.day.charactersPatch = "TempleGreatInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TempleGreatInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple32";
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Tenochtitlan";
	locations[n].reload.l2.emerge = "reloadTemple33";
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Tenochtitlan";
	locations[n].reload.l3.emerge = "reloadTemple34";

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "Tenochtitlan";
	locations[n].reload.l4.emerge = "reloadTemple41";
	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "Tenochtitlan";
	locations[n].reload.l5.emerge = "reloadTemple42";
	locations[n].reload.l6.name = "reload6";
	locations[n].reload.l6.go = "Tenochtitlan";
	locations[n].reload.l6.emerge = "reloadTemple43";

	locations[n].reload.l7.name = "reload11";
	locations[n].reload.l7.go = "Tenochtitlan";
	locations[n].reload.l7.emerge = "reloadTemple38"; // 090912
	locations[n].reload.l8.name = "reload8";
	locations[n].reload.l8.go = "Tenochtitlan";
	locations[n].reload.l8.emerge = "reloadTemple39";
	locations[n].reload.l9.name = "reload7";
	locations[n].reload.l9.go = "Tenochtitlan";
	locations[n].reload.l9.emerge = "reloadTemple40";

	locations[n].reload.l10.name = "reload9";
	locations[n].reload.l10.go = "Temple_Underwater_right";
	locations[n].reload.l10.emerge = "reload2";
	locations[n].reload.l10.autoreload = "1";
	locations[n].reload.l11.name = "reload10";
	locations[n].reload.l11.go = "Temple_Underwater_left";
	locations[n].reload.l11.emerge = "reload2";
	locations[n].reload.l11.autoreload = "1";

	locations[n].locators_radius.reload.reload9 = 1.2;
	locations[n].locators_radius.reload.reload10 = 1.2;
	locations[n].locators_radius.item.defend1 = 5.2;
	locations[n].locators_radius.item.defend2 = 2.5;
	locations[n].locators_radius.item.defend3 = 4.0;
	locations[n].locators_radius.item.defend4 = 2.0;
	locations[n].locators_radius.quest.detector1 = 4.0;
	locations[n].locators_radius.quest.detector2 = 6.0;
	locations[n].locators_radius.quest.detector3 = 2.0;
	locations[n].locators_radius.item.item1 = 0.9;
	
	//каменные сундуки
	locations[n].private1.key = "stonekey";
	locations[n].private1.items.talisman1 = 1;
	locations[n].private1.items.totem_12 = 1;
	locations[n].private1.items.indian_3 = 1;
	locations[n].private1.items.indian_10 = 1;
	locations[n].private1.items.obereg_2 = 1;
	locations[n].private1.items.potion7 = 10;
	locations[n].private1.items.cannabis1 = 20;
	locations[n].private1.items.cannabis4 = 20;
	locations[n].private1.items.cannabis7 = 5;
	locations[n].private1.items.jewelry22 = 100; // всякое уже не очень нужное барахло
	
	locations[n].private2.key = "stonekey";
	locations[n].private2.items.Tablet_1 = 1; // скрижаль Ицамны

	locations[n].private3.key = "stonekey";
	locations[n].private3.items.Tablet_3 = 1; // скрижаль Чака
	
	locations[n].DisableOfficers = "1";
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Круглый Храм Кукулькана - телепортатор в прошлое
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Temple_round";
	locations[n].id.label = "TempleRoundInside";
	locations[n].filespath.models = "locations\TenochtitlanInside\TempleRoundInside";
	locations[n].image = "loading\outside\TempleInside.tga";	
	//Sound
	locations[n].type = "teno_inside";
	//Models
	//Always
	locations[n].models.always.TempleRoundInside = "TempleRoundInside";
	locations[n].models.always.locators = "TempleRoundInside_locators";	
	locations[n].models.always.dolly = "dolly_5";
	locations[n].models.always.dolly.locator.group = "item";
	locations[n].models.always.dolly.locator.name = "dolly";
	//Day
	locations[n].models.day.charactersPatch = "TempleRoundInside_patch";
	//Night
	locations[n].models.night.charactersPatch = "TempleRoundInside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple31";
	
	locations[n].locators_radius.item.dolly = 2.0;
	locations[n].locators_radius.item.item1 = 1.1;
	
	locations[n].DisableOfficers = "1";
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Тайясаль сокровищница
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Temple_Treasure";
	locations[n].id.label = "TempleTreasure";
	Locations[n].image = "loading\outside\TempleInside.tga";
	//Sound
	locations[n].type = "teno_inside";
	//Models
	//Always
	Locations[n].filespath.models = "Locations\Inside\Pyramid1Inside\";
	//Always
	Locations[n].models.always.pyramid1 = "Pyramid1Inside";
	Locations[n].models.always.pyramid2 = "Pyramid1_treasure";
	Locations[n].models.always.pyramid3 = "Pyramid1_other";
	Locations[n].models.always.locators = "Pyramid1_locators";
	Locations[n].models.always.pyramid1gold = "Pyramid1_gold";
	Locations[n].models.always.pyramid1gold.reflection = 0.15;
	Locations[n].models.always.pyramid1gold.tech = "EnvironmentShader";
	//Day
	locations[n].models.day.charactersPatch = "Pyramid1_patch";
	//Night
	locations[n].models.night.charactersPatch = "Pyramid1_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadTemple36";
	
	// лари, сундуки
	locations[n].private1.key = "stonekey";
	locations[n].private1.items.icollection = 10;
	locations[n].private1.items.jewelry14 = 500;
	locations[n].private1.items.jewelry15 = 400;
	
	locations[n].private2.key = "stonekey";
	locations[n].private2.items.icollection = 10;
	locations[n].private2.items.jewelry2 = 1000;
	locations[n].private2.items.jewelry10 = 100;
	
	locations[n].private3.key = "stonekey";
	locations[n].private3.items.icollection = 10;
	locations[n].private3.items.jewelry16 = 300;
	locations[n].private3.items.jewelry17 = 600;
	
	locations[n].private4.key = "stonekey";
	locations[n].private4.items.icollection = 10;
	locations[n].private4.items.jewelry18 = 450;
	locations[n].private4.items.jewelry20 = 700;
	
	locations[n].private5.key = "stonekey";
	locations[n].private5.items.icollection = 10;
	locations[n].private5.items.jewelry3 = 1000;
	
	locations[n].private6.key = "stonekey";
	locations[n].private6.items.icollection = 10;
	locations[n].private6.items.jewelry4 = 1000;
	
	locations[n].private7.key = "stonekey";
	locations[n].private7.items.icollection = 10;
	locations[n].private7.items.jewelry14 = 500;
	
	locations[n].private8.key = "stonekey";
	locations[n].private8.items.icollection = 10;
	locations[n].private8.items.jewelry1 = 1000;
	locations[n].private8.items.jewelry7 = 100;
	
	locations[n].private9.key = "stonekey";
	locations[n].private9.items.icollection = 10;
	locations[n].private9.items.jewelry21 = 250;
	locations[n].private9.items.jewelry23 = 750;
	
	locations[n].private10.key = "stonekey";
	locations[n].private10.items.icollection = 100;
	
	locations[n].private11.key = "stonekey";
	locations[n].private11.items.icollection = 100;
	
	locations[n].private12.key = "stonekey";
	locations[n].private12.items.icollection = 100;
	
	locations[n].private13.key = "stonekey";
	locations[n].private13.items.icollection = 10;
	locations[n].private13.items.jewelry22 = 2000;
	
	locations[n].private14.key = "stonekey";
	locations[n].private14.items.icollection = 10;
	locations[n].private14.items.jewelry8 = 1000;
	
	locations[n].private15.key = "stonekey";
	locations[n].private15.items.icollection = 10;
	locations[n].private15.items.jewelry9 = 500;
	locations[n].private15.items.jewelry19 = 300;
	
	locations[n].private16.key = "stonekey";
	locations[n].private16.items.potion2 = 1000;
	locations[n].private16.items.potion3 = 1000;
	locations[n].private16.items.potion4 = 1000;
	locations[n].private16.items.potion7 = 10;
	locations[n].private16.items.berserker_potion = 20;
	
	locations[n].private17.key = "stonekey";
	locations[n].private17.items.icollection = 100;
	
	locations[n].private18.key = "stonekey";
	locations[n].private18.items.jewelry5 = 2000;
	
	locations[n].private19.key = "stonekey";
	locations[n].private19.items.jewelry6 = 4000;
	
	locations[n].private20.key = "stonekey";
	locations[n].private20.items.icollection = 200;
	locations[n].private20.items.jewelry5 = 5000;
	locations[n].private20.items.jewelry6 = 10000;
	
	locations[n].private21.key = "stonekey";
	locations[n].private21.items.mushket3 = 1;
	
	locations[n].DisableOfficers = "1";
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Тайясаль Затопленный Храм левый
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Temple_Underwater_left";
	locations[n].id.label = "TempleUnderwater";
	Locations[n].image = "loading\outside\TempleInside.tga";
	//Sound	
	locations[n].type = "underwater";
	locations[n].changeAnimation = "swim"; //сменить анимацию на плавание
	locations[n].watertemple = true;
	//Models
	//Always
	Locations[n].filespath.models = "Locations\TenochtitlanInside\TempleUnderwater\";
	Locations[n].models.always.Temple = "TempleUnderwater";
	Locations[n].models.always.reflect = "TempleUnderwater_reflect";
	Locations[n].models.always.reflect.sea_reflection = 1;
	Locations[n].models.always.locators = "TempleUnderwater_locators";	
	//Day
	locations[n].models.day.charactersPatch = "TempleUnderwater_patch";
	//Night
	locations[n].models.night.charactersPatch = "TempleUnderwater_patch";			
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	locations[n].underwater = true;
	Locations[n].QuestlockWeather = "Underwater";
	Locations[n].lockWeather = "Inside";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadU2";
	locations[n].reload.l1.autoreload = "1";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Temple_great";
	locations[n].reload.l2.emerge = "reload10";
	locations[n].reload.l2.autoreload = "1";
	locations[n].locators_radius.reload.reload1_back = 0.4;
	locations[n].locators_radius.reload.reload2_back = 0.4;
	LAi_LocationFightDisable(&locations[n], true);
	
	locations[n].DisableOfficers = "1";
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Тайясаль Затопленный Храм правый
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Temple_Underwater_right";
	locations[n].id.label = "TempleUnderwater";
	Locations[n].image = "loading\outside\TempleInside.tga";
	//Sound	
	locations[n].type = "underwater";
	locations[n].changeAnimation = "swim"; //сменить анимацию на плавание
	locations[n].watertemple = true;
	//Models
	//Always
	Locations[n].filespath.models = "Locations\TenochtitlanInside\TempleUnderwater\";
	Locations[n].models.always.Temple = "TempleUnderwater";
	Locations[n].models.always.reflect = "TempleUnderwater_reflect";
	Locations[n].models.always.reflect.sea_reflection = 1;
	Locations[n].models.always.locators = "TempleUnderwater_locators";	
	//Day
	locations[n].models.day.charactersPatch = "TempleUnderwater_patch";
	//Night
	locations[n].models.night.charactersPatch = "TempleUnderwater_patch";			
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	locations[n].underwater = true;
	Locations[n].QuestlockWeather = "Underwater";
	Locations[n].lockWeather = "Inside";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tenochtitlan";
	locations[n].reload.l1.emerge = "reloadU1";
	locations[n].reload.l1.autoreload = "1";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Temple_great";
	locations[n].reload.l2.emerge = "reload9";
	locations[n].reload.l2.autoreload = "1";
	locations[n].locators_radius.reload.reload1_back = 0.4;
	locations[n].locators_radius.reload.reload2_back = 0.4;
	LAi_LocationFightDisable(&locations[n], true);
	
	locations[n].DisableOfficers = "1";
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли шахты
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Mine_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
 	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	locations[n].DisableEncounters = true;
	locations[n].mine_bandits = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle3";
	Locations[n].models.always.jungle = "jungle3";	
	Locations[n].models.always.locators = "Jungle3_mine_locators";		
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
	Locations[n].models.always.l4 = "Jungle3_wall";
	//Day
	locations[n].models.day.charactersPatch = "jungle3_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle3_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload2_back";
	locations[n].reload.l1.go = "Mine_04";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l2.name = "reload3_back"; 
	locations[n].reload.l2.go = "Mine";
	locations[n].reload.l2.emerge = "reload6";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2.0;
	Locations[n].reload.l2.disable = true; // закрыто до поры
	locations[n].locators_radius.item.detector1 = 5.0;
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Mine_02";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
 	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	locations[n].DisableEncounters = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle4";
	Locations[n].models.always.jungle = "jungle4";	
	Locations[n].models.always.locators = "jungle4_locators";		
	Locations[n].models.always.grassPatch = "jungle4_grass";
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
	locations[n].models.day.charactersPatch = "jungle4_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle4_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Mine_03"; 
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Mine_04"; 
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Mine_exit";
	locations[n].reload.l3.emerge = "reload2"; 
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2.0;
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Mine_03";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
 	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	locations[n].DisableEncounters = true;
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
	locations[n].reload.l1.go = "Tenotchitlan_Jungle_06"; 
	locations[n].reload.l1.emerge = "reload1"; 
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Mine_02"; 
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Mine_04"; 
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2.0;
	n = n + 1;	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Mine_04";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	locations[n].DisableEncounters = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle2";
	Locations[n].models.always.jungle = "jungle2";	
	Locations[n].models.always.locators = "jungle2_lSentMartin02";		
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

	locations[n].models.always.l4 = "well_big";
	Locations[n].models.always.l4.locator.group = "reload";
	Locations[n].models.always.l4.locator.name ="reloadW_back";	
	Locations[n].models.always.l4.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "jungle2_pSentMartin02";
	//Night
	locations[n].models.night.charactersPatch = "jungle2_pSentMartin02";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Mine_02";  
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Mine_03"; 
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "jungle";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Mine_01"; 
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Выход к шахте
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Mine_exit";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
	locations[n].DisableEncounters = true;
	locations[n].mine_bandits = true;
	//Sound
	locations[n].type = "jungle";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\DuelField";
	Locations[n].models.always.Mine_exit = "DuelField";	
	Locations[n].models.always.locators = "duelfield_locators";		
	Locations[n].models.always.grassPatch = "duelfield_grass";
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
	locations[n].models.always.l4 = "DuelField_plan";
	locations[n].models.always.l5 = "duelfield_gate";
	// пушки
	locations[n].models.always.Gun1 = "mortair";
	Locations[n].models.always.Gun1.locator.group = "quest";
	Locations[n].models.always.Gun1.locator.name = "gun1";
	locations[n].models.always.Gun2 = "mortair";
	Locations[n].models.always.Gun2.locator.group = "quest";
	Locations[n].models.always.Gun2.locator.name = "gun2";
	locations[n].models.always.I1 = "barrel";
	Locations[n].models.always.I1.locator.group = "item";
	Locations[n].models.always.I1.locator.name = "item1";
	locations[n].models.always.I2 = "box";
	Locations[n].models.always.I2.locator.group = "item";
	Locations[n].models.always.I2.locator.name = "item2";
	locations[n].models.always.I3 = "barrel";
	Locations[n].models.always.I3.locator.group = "item";
	Locations[n].models.always.I3.locator.name = "item3";
	locations[n].models.always.I4 = "box";
	Locations[n].models.always.I4.locator.group = "item";
	Locations[n].models.always.I4.locator.name = "item4";
	locations[n].models.always.I5 = "barrel";
	Locations[n].models.always.I5.locator.group = "item";
	Locations[n].models.always.I5.locator.name = "item5";
	//Day
	locations[n].models.day.fonar = "duelfield_fd";
	locations[n].models.day.charactersPatch = "duelfield_mortair_patch";
	//Night
	locations[n].models.night.fonar = "duelfield_fn";
	locations[n].models.night.charactersPatch = "duelfield_mortair_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Mine";  
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "jungle";
	locations[n].locators_radius.reload.reload1_back = 2;
	Locations[n].reload.l1.disable = true; // закрыто до поры

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Mine_02"; 
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "jungle";
	locations[n].locators_radius.reload.reload2_back = 2;
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Шахта бандитов
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Mine";
    locations[n].id.label = "mines";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Tenotchitlan";
    Locations[n].image = "loading\Mine.tga";
    //Sound
    locations[n].type = "jungle";
    //Models
	locations[n].filespath.models = "Locations\Outside\Canyon";
    //Always
	locations[n].models.always.Canyon = "Canyon";
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";
	
    locations[n].models.always.locators = "canyon_locators";
    locations[n].models.always.grassPatch = "canyon_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	//Day
	locations[n].models.day.charactersPatch = "canyon_patch";
	locations[n].models.day.fonar = "canyon_fd";
	//Night
	locations[n].models.night.charactersPatch = "canyon_patch";
	locations[n].models.night.fonar = "canyon_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
    //Reload map	
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Mine_exit";
    locations[n].reload.l1.emerge = "reload1";  
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "jungle";
    locations[n].locators_radius.reload.reload1 = 2.0;
	
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonRoom_MH4";
    locations[n].reload.l2.emerge = "reload1";  
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "House";
	
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "CommonRoom_MH7";
    locations[n].reload.l3.emerge = "reload1";  
    locations[n].reload.l3.autoreload = "0";
    locations[n].reload.l3.label = "House";
	
	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "Mine_mines";
    locations[n].reload.l4.emerge = "reload1";  
    locations[n].reload.l4.autoreload = "0";
    locations[n].reload.l4.label = "mines";
	
	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "Mine_residence";
    locations[n].reload.l5.emerge = "reload1";  
    locations[n].reload.l5.autoreload = "0";
    locations[n].reload.l5.label = "House";
	
	locations[n].reload.l6.name = "reload6";
	locations[n].reload.l6.go = "Mine_01";
    locations[n].reload.l6.emerge = "reload3_back";  
    locations[n].reload.l6.autoreload = "0";
    locations[n].reload.l6.label = "jungle";
    locations[n].locators_radius.reload.reload6 = 2.0;
	locations[n].locators_radius.rld.warrior = 5.0;
	
	n = n + 1;
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// шахта
	///////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Mine_mines";
	locations[n].id.label = "mines";
    locations[n].image = "loading\Mine.tga";
	//Sound
	locations[n].type = "cave";
	locations[n].islandId = "Mein";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\DungeonDuffer2";
	locations[n].models.always.DungeonDuffer2 = "DungeonDuffer2";
	locations[n].models.always.locators = "MinentownMine_locators";
/*	
	Locations[n].models.always.rays = "DungeonDuffer2_rays";
	Locations[n].models.always.rays.level = 49;
	Locations[n].models.always.rays.tech= "LocVisRays";
	Locations[n].models.always.rays.uvslide.u1 = -0.03;
	Locations[n].models.always.rays.uvslide.v1 = -0.03;	
*/	
	//Day
	locations[n].models.day.charactersPatch = "DungeonDuffer2_patch";
	//Night
	locations[n].models.night.charactersPatch = "DungeonDuffer2_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "mine";
	locations[n].reload.l1.emerge = "reload4";
	Locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "mines";
	n = n + 1;

	/////////////////// Резиденция ////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Mine_residence";
	locations[n].id.label = "House";
	locations[n].MustSetReloadBack = true;
	locations[n].image = "loading\inside\SmallResidence.tga";
	//Town sack
	locations[n].townsack = "";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "";
	//Models
	locations[n].filespath.models = "locations\inside\SmallResidence";
	//Always
	locations[n].models.always.house = "SmallResidence";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "SmallResidence_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.locators = "SmallResidence_locators";

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "SmallResidence_patch";
	//Night
	locations[n].models.night.charactersPatch = "SmallResidence_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Mine";
	locations[n].reload.l1.emerge = "reload5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.item.item1 = 1.0;
	n = n + 1;
	
	return n;
}
