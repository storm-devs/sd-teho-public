

int LocationInitKhaelRoa(int n)
{
	// -------------------------------------------------
	Locations[n].id = "KhaelRoa_port";
	Locations[n].worldmap = "Khael Roa";
	Locations[n].filespath.models = "locations\Incas Temple\Port";
	Locations[n].image = "loading\haelroa.tga";
	locations[n].id.label = "Shore64";
	locations[n].islandId = "KhaelRoa";
	locations[n].onUninhabitedIsland = true;
	locations[n].Chestgennot = true; // не генерить сундуки
	//Sound
	locations[n].type = "seashore";
	//Models
	//Always
	Locations[n].models.always.locators = "KRport_l";
	Locations[n].models.always.shore = "KRport";
	Locations[n].models.always.seabed = "KRport_sb";
	Locations[n].models.always.grasspatch = "KRport_g";	
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
/*	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";		
*/	
	//Day
	Locations[n].models.day.charactersPatch = "KRport_p";	
	//Night
	Locations[n].models.night.charactersPatch = "KRport_p";
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "true";
	//Reload map
	Locations[n].reload.l1.name = "reload2";
	Locations[n].reload.l1.go = "KhaelRoa";
	Locations[n].reload.l1.emerge = "reload_1";
	Locations[n].reload.l1.autoreload = "0";
	
	Locations[n].reload.l2.name = "reload1";
	Locations[n].reload.l2.go = "Temple_h";
	Locations[n].reload.l2.emerge = "reload1";
	Locations[n].reload.l2.autoreload = "1";

	Locations[n].reload.l3.name = "reload1_back";
	Locations[n].reload.l3.go = "Temple_h";
	Locations[n].reload.l3.emerge = "reload1";
	Locations[n].reload.l3.autoreload = "1";
	Locations[n].locators_radius.reload.reload1_back = 2;

	n = n + 1;
	
	// -------------------------------------------------
	Locations[n].id = "Temple_h";
	Locations[n].filespath.models = "locations\Incas Temple\Temple\";
	//Sound
	locations[n].type = "questisland";
	Locations[n].image = "loading\outside\temple.tga";
	locations[n].id.label = "Incas Temple";
	//Models
	//Always
	Locations[n].models.always.locators = "hram_l";
	Locations[n].models.always.l1 = "Hram";
	Locations[n].models.always.grasspatch = "hram_g";	
	//Day
	Locations[n].models.day.charactersPatch = "Hram_p";
	Locations[n].models.day.jumppatch = "hram_j";
	//Night
	Locations[n].models.night.charactersPatch = "Hram_p";
	Locations[n].models.night.jumppatch = "hram_j";

	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";

	//Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "KhaelRoa_port";
	Locations[n].reload.l1.emerge = "reload1";
	Locations[n].reload.l1.autoreload = "1";

	Locations[n].reload.l3.name = "reload1_back";
	Locations[n].reload.l3.go = "KhaelRoa_port";
	Locations[n].reload.l3.emerge = "reload1";
	Locations[n].reload.l3.autoreload = "1";
	Locations[n].locators_radius.reload.reload1_back = 3;

	Locations[n].reload.l2.name = "reload2";
	Locations[n].reload.l2.go = "labirint_1";
	Locations[n].reload.l2.emerge = "reload27";
	Locations[n].reload.l2.autoreload = "1";

	n = n + 1;


	// -------------------------------------------------
	Locations[n].id = "Labirint_1";
	Locations[n].filespath.models = "locations\Incas Temple\Labirint\";
	//Sound
	Locations[n].image = "loading\outside\TempleInside.tga";
	locations[n].type = "teno_inside";
	locations[n].id.label = "Maze";
	//Models
	//Always
	Locations[n].models.always.locators = "lab1_l";
	Locations[n].models.always.l1 = "lab1";
	//Day
	Locations[n].models.day.charactersPatch = "lab1_p";
	//Night
	Locations[n].models.night.charactersPatch = "lab1_p";
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";
	Locations[n].lockWeather = "Alcove";
	
	//Reload map

	Locations[n].reload.l2.name = "reload4";
	Locations[n].reload.l2.go = "labirint_2";
	Locations[n].reload.l2.emerge = "reload3";
	Locations[n].reload.l2.autoreload = "1";
      
	Locations[n].reload.l22.name = "reload4_back";
	Locations[n].reload.l22.go = "labirint_2";
	Locations[n].reload.l22.emerge = "reload3";
	Locations[n].reload.l22.autoreload = "1";

    Locations[n].reload.l3.name = "reload11";
	Locations[n].reload.l3.go = "labirint_2";
	Locations[n].reload.l3.emerge = "Reload12";
	Locations[n].reload.l3.autoreload = "1";

	Locations[n].reload.l23.name = "reload11_back";
	Locations[n].reload.l23.go = "labirint_2";
	Locations[n].reload.l23.emerge = "Reload12";
	Locations[n].reload.l23.autoreload = "1";

	Locations[n].reload.l4.name = "reload17";
	Locations[n].reload.l4.go = "labirint_2";
	Locations[n].reload.l4.emerge = "reload18";
	Locations[n].reload.l4.autoreload = "1";
      
	Locations[n].reload.l5.name = "reload20";
	Locations[n].reload.l5.go = "labirint_2";
	Locations[n].reload.l5.emerge = "Reload19";
	Locations[n].reload.l5.autoreload = "1";

	Locations[n].reload.l6.name = "reload22";
	Locations[n].reload.l6.go = "labirint_2";
	Locations[n].reload.l6.emerge = "reload21";
	Locations[n].reload.l6.autoreload = "1";
      
    Locations[n].reload.l7.name = "reload23";
	Locations[n].reload.l7.go = "labirint_2";
	Locations[n].reload.l7.emerge = "Reload24";
	Locations[n].reload.l7.autoreload = "1";

	Locations[n].reload.l8.name = "reload26";
	Locations[n].reload.l8.go = "labirint_2";
	Locations[n].reload.l8.emerge = "reload25";
	Locations[n].reload.l8.autoreload = "1";

	Locations[n].reload.l28.name = "reload26_back";
	Locations[n].reload.l28.go = "labirint_2";
	Locations[n].reload.l28.emerge = "reload25";
	Locations[n].reload.l28.autoreload = "1";

    Locations[n].reload.l9.name = "reload1";
	Locations[n].reload.l9.go = "labirint_3";
	Locations[n].reload.l9.emerge = "Reload2";
	Locations[n].reload.l9.autoreload = "1";

	Locations[n].reload.l29.name = "reload1_back";
	Locations[n].reload.l29.go = "labirint_3";
	Locations[n].reload.l29.emerge = "Reload2";
	Locations[n].reload.l29.autoreload = "1";

	Locations[n].reload.l10.name = "reload6";
	Locations[n].reload.l10.go = "labirint_3";
	Locations[n].reload.l10.emerge = "reload5";
	Locations[n].reload.l10.autoreload = "1";

	Locations[n].reload.l20.name = "reload6_back";
	Locations[n].reload.l20.go = "labirint_3";
	Locations[n].reload.l20.emerge = "reload5";
	Locations[n].reload.l20.autoreload = "1";
      
    Locations[n].reload.l11.name = "reload7";
	Locations[n].reload.l11.go = "labirint_3";
	Locations[n].reload.l11.emerge = "Reload8";
	Locations[n].reload.l11.autoreload = "1";

    Locations[n].reload.l21.name = "reload7_back";
	Locations[n].reload.l21.go = "labirint_3";
	Locations[n].reload.l21.emerge = "Reload8";
	Locations[n].reload.l21.autoreload = "1";

	Locations[n].reload.l12.name = "reload9";
	Locations[n].reload.l12.go = "labirint_3";
	Locations[n].reload.l12.emerge = "reload10";
	Locations[n].reload.l12.autoreload = "1";

	Locations[n].reload.l22.name = "reload9_back";
	Locations[n].reload.l22.go = "labirint_3";
	Locations[n].reload.l22.emerge = "reload10";
	Locations[n].reload.l22.autoreload = "1";

	n = n + 1;
	
	// -------------------------------------------------
	Locations[n].id = "Labirint_2";
	Locations[n].filespath.models = "locations\Incas Temple\Labirint\";
	//Sound
		Locations[n].image = "loading\outside\TempleInside.tga";
	locations[n].type = "teno_inside";
	locations[n].id.label = "Maze";
	//Models
	//Always
	Locations[n].models.always.locators = "lab2_l";
	Locations[n].models.always.l1 = "lab2";
	//Day
	Locations[n].models.day.charactersPatch = "lab2_p";
	//Night
	Locations[n].models.night.charactersPatch = "lab2_p";
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";
	Locations[n].lockWeather = "Alcove";
	
	//Reload map

	Locations[n].reload.l2.name = "reload3";
	Locations[n].reload.l2.go = "labirint_1";
	Locations[n].reload.l2.emerge = "reload4";
	Locations[n].reload.l2.autoreload = "1";

	Locations[n].reload.l22.name = "reload3_back";
	Locations[n].reload.l22.go = "labirint_1";
	Locations[n].reload.l22.emerge = "reload4";
	Locations[n].reload.l22.autoreload = "1";
      
    Locations[n].reload.l3.name = "reload12";
	Locations[n].reload.l3.go = "labirint_1";
	Locations[n].reload.l3.emerge = "Reload11";
	Locations[n].reload.l3.autoreload = "1";

	Locations[n].reload.l23.name = "reload12_back";
	Locations[n].reload.l23.go = "labirint_1";
	Locations[n].reload.l23.emerge = "Reload11";
	Locations[n].reload.l23.autoreload = "1";

	Locations[n].reload.l4.name = "reload18";
	Locations[n].reload.l4.go = "labirint_1";
	Locations[n].reload.l4.emerge = "reload17";
	Locations[n].reload.l4.autoreload = "1";
      
    Locations[n].reload.l5.name = "reload19";
	Locations[n].reload.l5.go = "labirint_1";
	Locations[n].reload.l5.emerge = "Reload20";
	Locations[n].reload.l5.autoreload = "1";

	Locations[n].reload.l6.name = "reload21";
	Locations[n].reload.l6.go = "labirint_1";
	Locations[n].reload.l6.emerge = "reload22";
	Locations[n].reload.l6.autoreload = "1";
      
    Locations[n].reload.l7.name = "reload24";
	Locations[n].reload.l7.go = "labirint_1";
	Locations[n].reload.l7.emerge = "Reload23";
	Locations[n].reload.l7.autoreload = "1";

	Locations[n].reload.l8.name = "reload25";
	Locations[n].reload.l8.go = "labirint_1";
	Locations[n].reload.l8.emerge = "reload26";
	Locations[n].reload.l8.autoreload = "1";

	Locations[n].reload.l28.name = "reload25_back";
	Locations[n].reload.l28.go = "labirint_1";
	Locations[n].reload.l28.emerge = "reload26";
	Locations[n].reload.l28.autoreload = "1";

    Locations[n].reload.l9.name = "reload14";
	Locations[n].reload.l9.go = "labirint_3";
	Locations[n].reload.l9.emerge = "Reload13";
	Locations[n].reload.l9.autoreload = "1";

	Locations[n].reload.l29.name = "reload14_back";
	Locations[n].reload.l29.go = "labirint_3";
	Locations[n].reload.l29.emerge = "Reload13";
	Locations[n].reload.l29.autoreload = "1";

	Locations[n].reload.l10.name = "reload16";
	Locations[n].reload.l10.go = "labirint_3";
	Locations[n].reload.l10.emerge = "reload15";
	Locations[n].reload.l10.autoreload = "1";

	Locations[n].reload.l20.name = "reload16_back";
	Locations[n].reload.l20.go = "labirint_3";
	Locations[n].reload.l20.emerge = "reload15";
	Locations[n].reload.l20.autoreload = "1";
      
    n = n + 1;
	
	// -------------------------------------------------
	Locations[n].id = "Labirint_3";
	Locations[n].filespath.models = "locations\Incas Temple\Labirint\";
	//Sound
	Locations[n].image = "loading\outside\TempleInside.tga";
	locations[n].type = "teno_inside";
	locations[n].id.label = "Maze";
	//Models
	//Always
	Locations[n].models.always.locators = "lab3_l";
	Locations[n].models.always.l1 = "lab3";
	Locations[n].models.always.l2 = "lab3_blocks";
	//Day
	Locations[n].models.day.charactersPatch = "lab3_p";
	//Night
	Locations[n].models.night.charactersPatch = "lab3_p";
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";
	Locations[n].lockWeather = "Alcove";

	//Reload map
	Locations[n].reload.l2.name = "reload13";
	Locations[n].reload.l2.go = "labirint_2";
	Locations[n].reload.l2.emerge = "reload14";
    Locations[n].reload.l2.autoreload = "1";

	Locations[n].reload.l22.name = "reload13_back";
	Locations[n].reload.l22.go = "labirint_2";
	Locations[n].reload.l22.emerge = "reload14";
    Locations[n].reload.l22.autoreload = "1";

    Locations[n].reload.l3.name = "reload15";
	Locations[n].reload.l3.go = "labirint_2";
	Locations[n].reload.l3.emerge = "Reload16";
	Locations[n].reload.l3.autoreload = "1";

	Locations[n].reload.l23.name = "reload15_back";
	Locations[n].reload.l23.go = "labirint_2";
	Locations[n].reload.l23.emerge = "Reload16";
	Locations[n].reload.l23.autoreload = "1";

	Locations[n].reload.l4.name = "reload2";
	Locations[n].reload.l4.go = "labirint_1";
	Locations[n].reload.l4.emerge = "reload1";
	Locations[n].reload.l4.autoreload = "1";

	Locations[n].reload.l24.name = "reload2_back";
	Locations[n].reload.l24.go = "labirint_1";
	Locations[n].reload.l24.emerge = "reload1";
	Locations[n].reload.l24.autoreload = "1";
      
    Locations[n].reload.l5.name = "reload5";
	Locations[n].reload.l5.go = "labirint_1";
	Locations[n].reload.l5.emerge = "Reload6";
	Locations[n].reload.l5.autoreload = "1";

	Locations[n].reload.l25.name = "reload5_back";
	Locations[n].reload.l25.go = "labirint_1";
	Locations[n].reload.l25.emerge = "Reload6";
	Locations[n].reload.l25.autoreload = "1";

	Locations[n].reload.l6.name = "reload8";
	Locations[n].reload.l6.go = "labirint_1";
	Locations[n].reload.l6.emerge = "reload7";
	Locations[n].reload.l6.autoreload = "1";

	Locations[n].reload.l26.name = "reload8_back";
	Locations[n].reload.l26.go = "labirint_1";
	Locations[n].reload.l26.emerge = "reload7";
	Locations[n].reload.l26.autoreload = "1";
      
    Locations[n].reload.l7.name = "reload10";
	Locations[n].reload.l7.go = "labirint_1";
	Locations[n].reload.l7.emerge = "Reload9";
	Locations[n].reload.l7.autoreload = "1";

	Locations[n].reload.l27.name = "reload10_back";
	Locations[n].reload.l27.go = "labirint_1";
	Locations[n].reload.l27.emerge = "Reload9";
	Locations[n].reload.l27.autoreload = "1";

	Locations[n].reload.l28.name = "reload30_back";
	Locations[n].reload.l28.go = "Treasure_Alcove";
	Locations[n].reload.l28.emerge = "Reload1";
	Locations[n].reload.l28.autoreload = "1";

	n = n + 1;

	// -------------------------------------------------
	Locations[n].id = "Treasure_Alcove";
	Locations[n].filespath.models = "locations\Incas Temple\Alcove\";
	//Sound
	Locations[n].image = "loading\outside\TempleInside.tga";
	locations[n].type = "Alcove";
	locations[n].id.label = "Alcove";
	//Models
	//Always
	Locations[n].models.always.locators = "Alcove_l";
	Locations[n].models.always.l1 = "alcove";
	//Rays
	Locations[n].models.always.l2 = "rays";
	Locations[n].models.always.l2.level = 100;
	Locations[n].models.always.l2.tech = "LocVisRays";
	Locations[n].models.always.l2.uvslide.u1 = -0.02;
	Locations[n].models.always.l2.uvslide.v1 = -0.02;
	//Artifact
	Locations[n].models.always.l3 = "artifact";
	Locations[n].models.always.l3.locator.name = "artifact";
	Locations[n].models.always.l3.locator.group = "gm";
	Locations[n].models.always.l3.rotate.x = 0.0;
	Locations[n].models.always.l3.rotate.y = 0.777;
	Locations[n].models.always.l3.rotate.z = 0.0;
	Locations[n].models.always.l3.tech = "EnvironmentShader";
	Locations[n].models.always.l3.reflection = 0.4;
	//Bird
	Locations[n].models.always.l4 = "Bird";
	Locations[n].models.always.l4.locator.name = "Bird";
	Locations[n].models.always.l4.locator.group = "gm";
	Locations[n].models.always.l4.tech = "EnvironmentShader";
	Locations[n].models.always.l4.reflection = 0.4;
	//Blue portal
	Locations[n].models.always.blue1 = "Blueport";
	Locations[n].models.always.blue1.level = 100;
	Locations[n].models.always.blue1.tech = "LocVisRays";
	Locations[n].models.always.blue1.uvslide.u0 = 0.06;
	Locations[n].models.always.blue1.uvslide.v0 = 0.00;
	Locations[n].models.always.blue1.uvslide.u1 = 0.16;
	Locations[n].models.always.blue1.uvslide.v1 = 0.00;

	//Day
	Locations[n].models.day.charactersPatch = "alcove_p";
	//Night
	Locations[n].models.night.charactersPatch = "alcove_p";
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";
	Locations[n].lockWeather = "Alcove";

	//Reload map
	Locations[n].reload.l2.name = "reload1";
	Locations[n].reload.l2.go = "labirint_3";
	Locations[n].reload.l2.emerge = "reload30";
    Locations[n].reload.l2.autoreload = "1";
    
	n = n + 1;

	return n;
}
