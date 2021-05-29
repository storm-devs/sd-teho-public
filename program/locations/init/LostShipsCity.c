
int LocationInitLostShipsCity(int n)
{
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ГОРОД
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LostShipsCity_town";
	locations[n].id.label = "LSC Town";
	locations[n].worldmap = "LostShipsCity";
	
	locations[n].townsack = "LostShipsCity";
 	locations[n].islandId = "LostShipsCity";
	
	locations[n].filespath.models = "locations\LostShipsCity\";
	locations[n].image = "loading\OutsideLSC.tga";
	//Sound
	locations[n].type = "LostShipsCity";

	Locations[n].models.always.LostShipsCity = "LostShipsCity";	
	Locations[n].models.always.seabed = "LostShipsCity_seabed";	
	Locations[n].models.always.reflect = "LostShipsCity_reflect";
	Locations[n].models.always.reflect.sea_reflection = 1;

	Locations[n].models.always.sails = "LostShipsCity_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65539;
	
	Locations[n].models.always.plan1 = "LostShipsCity_plan1";
	Locations[n].models.always.plan1.sea_reflection = 1;
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65534;
	
	Locations[n].models.always.plan2 = "LostShipsCity_plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65533;

	Locations[n].models.always.plan3 = "LostShipsCity_plan3";
	Locations[n].models.always.plan3.tech = "LocationWindows";
	Locations[n].models.always.plan3.level = 65532;
	
	Locations[n].models.always.locators = "LostShipsCity_locators";
	
	Locations[n].models.always.grassPatch = "LostShipsCity_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";	
	//Day
	locations[n].models.day.charactersPatch = "LostShipsCity_patch_day";
	Locations[n].models.day.jumpPatch = "LostShipsCity_jump_patch";
	locations[n].models.day.fonar = "LostShipsCity_fd";	
	//Night
	locations[n].models.night.charactersPatch = "LostShipsCity_patch_day";	
	Locations[n].models.night.jumpPatch = "LostShipsCity_jump_patch";
	Locations[n].models.night.fonar = "LostShipsCity_fn";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
    // --> Типовые городские локации, четкая фиксация на 10 номеров.
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "LostShipsCity";
	locations[n].reload.l1.emerge = "reload_1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Sea";
	locations[n].locators_radius.reload.reload1_back = 1.8;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "LostShipsCity";
	locations[n].reload.l2.emerge = "reload_2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
	locations[n].reload.l2.disable = true; 
	locations[n].locators_radius.reload.reload2_back = 6.0;

	////////  Галеон Эва AvaShipInside3 //////////
	locations[n].reload.l3.name = "reload41";
	locations[n].reload.l3.go = "AvaShipInside3";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Ava Cabin";
	locations[n].reload.l3.close_for_night = 1;

	locations[n].reload.l4.name = "reload43";
	locations[n].reload.l4.go = "AvaShipInside3";
	locations[n].reload.l4.emerge = "reload2";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Ava Cabin";
	locations[n].reload.l4.close_for_night = 1;

	locations[n].reload.l5.name = "reload44";
	locations[n].reload.l5.go = "AvaShipInside3";
	locations[n].reload.l5.emerge = "reload3";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "Ava Cabin";
	locations[n].reload.l5.close_for_night = 1;

	locations[n].reload.l6.name = "reload42";
	locations[n].reload.l6.go = "AvaShipInside3";
	locations[n].reload.l6.emerge = "reload4";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "Ava Cabin";
	locations[n].reload.l6.close_for_night = 1;

	//////// Фрегат Каролина   CarolineBank ////////
	locations[n].reload.l7.name = "reload20";
	locations[n].reload.l7.go = "CarolineBank";
	locations[n].reload.l7.emerge = "reload1";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "Caroline cabin";
	locations[n].reload.l7.close_for_night = 1;

	locations[n].reload.l8.name = "reload24";
	locations[n].reload.l8.go = "CarolineBank";
	locations[n].reload.l8.emerge = "reload2";
	locations[n].reload.l8.autoreload = "0";
	locations[n].reload.l8.label = "Caroline cabin";
	locations[n].reload.l8.close_for_night = 1;

	locations[n].reload.l9.name = "reload25";
	locations[n].reload.l9.go = "CarolineBank";
	locations[n].reload.l9.emerge = "reload3";
	locations[n].reload.l9.autoreload = "0";
	locations[n].reload.l9.label = "Caroline cabin";
	locations[n].reload.l9.disable = true; //закрыто до поры

	//////// Флейт Церес Смити   CeresSmithy ////////
	locations[n].reload.l10.name = "reload65";
	locations[n].reload.l10.go = "CeresSmithy";
	locations[n].reload.l10.emerge = "reload1";
	locations[n].reload.l10.autoreload = "0";
	locations[n].reload.l10.label = "CeresSmithy cabin";
	locations[n].reload.l10.close_for_night = 1;

	locations[n].reload.l11.name = "reload64";
	locations[n].reload.l11.go = "CeresSmithy";
	locations[n].reload.l11.emerge = "reload2";
	locations[n].reload.l11.autoreload = "0";
	locations[n].reload.l11.label = "CeresSmithy cabin";
	locations[n].reload.l11.close_for_night = 1;

	locations[n].reload.l12.name = "reload62";
	locations[n].reload.l12.go = "CeresSmithy";
	locations[n].reload.l12.emerge = "reload3";
	locations[n].reload.l12.autoreload = "0";
	locations[n].reload.l12.label = "CeresSmithy cabin";
	locations[n].reload.l12.disable = true; //закрыто до поры

	locations[n].reload.l13.name = "reload63";
	locations[n].reload.l13.go = "CeresSmithy";
	locations[n].reload.l13.emerge = "reload4";
	locations[n].reload.l13.autoreload = "0";
	locations[n].reload.l13.label = "CeresSmithy cabin";
	locations[n].reload.l13.disable = true; //закрыто до поры
	
	locations[n].reload.l14.name = "reload59";
	locations[n].reload.l14.go = "CeresSmithy";
	locations[n].reload.l14.emerge = "reload5";
	locations[n].reload.l14.autoreload = "0";
	locations[n].reload.l14.label = "CeresSmithy cabin";
	locations[n].reload.l14.disable = true; //закрыто до поры
	
	locations[n].reload.l15.name = "reload60";
	locations[n].reload.l15.go = "CeresSmithy";
	locations[n].reload.l15.emerge = "reload6";
	locations[n].reload.l15.autoreload = "0";
	locations[n].reload.l15.label = "CeresSmithy cabin";

	locations[n].reload.l16.name = "reload61";
	locations[n].reload.l16.go = "CeresSmithy";
	locations[n].reload.l16.emerge = "reload7";
	locations[n].reload.l16.autoreload = "0";
	locations[n].reload.l16.label = "CeresSmithy cabin";

	//////// Галеон Эсмеральда   EsmeraldaStoreBig ////////
	locations[n].reload.l17.name = "reload45";
	locations[n].reload.l17.go = "EsmeraldaStoreBig";
	locations[n].reload.l17.emerge = "reload1";
	locations[n].reload.l17.autoreload = "0";
	locations[n].reload.l17.label = "EsmeraldaStoreBig cabin";
	locations[n].reload.l17.close_for_night = 1;

	locations[n].reload.l18.name = "reload48"; // вход в резиденцию нарвалов
	locations[n].reload.l18.go = "EsmeraldaStoreBig";
	locations[n].reload.l18.emerge = "reload2";
	locations[n].reload.l18.autoreload = "0";
	locations[n].reload.l18.label = "EsmeraldaStoreBig cabin";
	locations[n].reload.l18.close_for_night = 1;

	locations[n].reload.l19.name = "reload46";
	locations[n].reload.l19.go = "EsmeraldaStoreBig";
	locations[n].reload.l19.emerge = "reload3";
	locations[n].reload.l19.autoreload = "0";
	locations[n].reload.l19.label = "EsmeraldaStoreBig cabin";
	locations[n].reload.l19.close_for_night = 1;
	
	locations[n].reload.l20.name = "reload49";
	locations[n].reload.l20.go = "EsmeraldaStoreBig";
	locations[n].reload.l20.emerge = "reload4";
	locations[n].reload.l20.autoreload = "0";
	locations[n].reload.l20.label = "EsmeraldaStoreBig cabin";
	locations[n].reload.l20.close_for_night = 1;

	locations[n].reload.l21.name = "reload50";
	locations[n].reload.l21.go = "EsmeraldaStoreBig";
	locations[n].reload.l21.emerge = "reload5";
	locations[n].reload.l21.autoreload = "0";
	locations[n].reload.l21.label = "EsmeraldaStoreBig cabin";
	locations[n].reload.l21.close_for_night = 1;

	locations[n].reload.l22.name = "reload47";
	locations[n].reload.l22.go = "EsmeraldaStoreBig";
	locations[n].reload.l22.emerge = "reload6";
	locations[n].reload.l22.autoreload = "0";
	locations[n].reload.l22.label = "EsmeraldaStoreBig cabin";
	locations[n].reload.l22.close_for_night = 1;

	//////// Платформа Феникс   FenixPlatform ////////
	locations[n].reload.l23.name = "reload72";
	locations[n].reload.l23.go = "FenixPlatform";
	locations[n].reload.l23.emerge = "reload1";
	locations[n].reload.l23.autoreload = "0";
	locations[n].reload.l23.label = "FenixPlatform cabin";

	locations[n].reload.l231.name = "reload73";
	locations[n].reload.l231.go = "UnderWater";
	locations[n].reload.l231.emerge = "reload1";
	locations[n].reload.l231.autoreload = "0";
	locations[n].reload.l231.label = "UnderWater";
	locations[n].reload.l231.disable = true;
	locations[n].reload.l231.open_for_day = true;

	//////// Флейт Фернандо Диффиндур   FernandaDiffIndoor ////////
	locations[n].reload.l24.name = "reload74";
	locations[n].reload.l24.go = "FernandaDiffIndoor";
	locations[n].reload.l24.emerge = "reload1";
	locations[n].reload.l24.autoreload = "0";
	locations[n].reload.l24.label = "FernandaDiffIndoor cabin";
	locations[n].reload.l24.disable = 1;  //закрыто до поры

	//////// Каравелла Флерон   FleuronTavern ////////
	locations[n].reload.l25.name = "reload38";
	locations[n].reload.l25.go = "FleuronTavern";
	locations[n].reload.l25.emerge = "reload1";
	locations[n].reload.l25.autoreload = "0";
	locations[n].reload.l25.label = "FleuronTavern cabin";

	locations[n].reload.l26.name = "reload37";
	locations[n].reload.l26.go = "FleuronTavern";
	locations[n].reload.l26.emerge = "reload2";
	locations[n].reload.l26.autoreload = "0";
	locations[n].reload.l26.label = "FleuronTavern cabin";

	locations[n].reload.l27.name = "reload35";
	locations[n].reload.l27.go = "FleuronTavern";
	locations[n].reload.l27.emerge = "reload3";
	locations[n].reload.l27.autoreload = "0";
	locations[n].reload.l27.label = "FleuronTavern cabin";

	locations[n].reload.l28.name = "reload34";
	locations[n].reload.l28.go = "FleuronTavern";
	locations[n].reload.l28.emerge = "reload4";
	locations[n].reload.l28.autoreload = "0";
	locations[n].reload.l28.label = "FleuronTavern cabin";

	locations[n].reload.l29.name = "reload36";
	locations[n].reload.l29.go = "FleuronTavern";
	locations[n].reload.l29.emerge = "reload5";
	locations[n].reload.l29.autoreload = "0";
	locations[n].reload.l29.label = "FleuronTavern cabin";
	locations[n].reload.l29.disable = 1;  //закрыто навсегда

	locations[n].reload.l30.name = "reload39";
	locations[n].reload.l30.go = "FleuronTavern";
	locations[n].reload.l30.emerge = "reload6";
	locations[n].reload.l30.autoreload = "0";
	locations[n].reload.l30.label = "FleuronTavern cabin";

	locations[n].reload.l31.name = "reload40";
	locations[n].reload.l31.go = "FleuronTavern";
	locations[n].reload.l31.emerge = "reload7";
	locations[n].reload.l31.autoreload = "0";
	locations[n].reload.l31.label = "FleuronTavern cabin";

	//////// Пинас Фурия  FurieShipInside2 ////////
	locations[n].reload.l32.name = "reload29";
	locations[n].reload.l32.go = "FurieShipInside2";
	locations[n].reload.l32.emerge = "reload1";
	locations[n].reload.l32.autoreload = "0";
	locations[n].reload.l32.label = "FurieShipInside2 cabin";
	locations[n].reload.l32.close_for_night = 1;

	locations[n].reload.l33.name = "reload31";
	locations[n].reload.l33.go = "FurieShipInside2";
	locations[n].reload.l33.emerge = "reload2";
	locations[n].reload.l33.autoreload = "0";
	locations[n].reload.l33.label = "FurieShipInside2 cabin";
	locations[n].reload.l33.close_for_night = 1;

	locations[n].reload.l34.name = "reload32";
	locations[n].reload.l34.go = "FurieShipInside2";
	locations[n].reload.l34.emerge = "reload3";
	locations[n].reload.l34.autoreload = "0";
	locations[n].reload.l34.label = "FurieShipInside2 cabin";
	locations[n].reload.l34.close_for_night = 1;

	locations[n].reload.l35.name = "reload30";
	locations[n].reload.l35.go = "FurieShipInside2";
	locations[n].reload.l35.emerge = "reload4";
	locations[n].reload.l35.autoreload = "0";
	locations[n].reload.l35.label = "FurieShipInside2 cabin";
	locations[n].reload.l35.close_for_night = 1;

	locations[n].reload.l36.name = "reload28";
	locations[n].reload.l36.go = "FurieShipInside2";
	locations[n].reload.l36.emerge = "reload5";
	locations[n].reload.l36.autoreload = "0";
	locations[n].reload.l36.label = "FurieShipInside2 cabin";
	locations[n].reload.l36.close_for_night = 1;

	locations[n].reload.l37.name = "reload47";
	locations[n].reload.l37.go = "FurieShipInside2";
	locations[n].reload.l37.emerge = "reload6";
	locations[n].reload.l37.autoreload = "0";
	locations[n].reload.l37.label = "FurieShipInside2 cabin";
	locations[n].reload.l37.close_for_night = 1;

	//////// Галеон Глория  GloriaChurch ////////
	locations[n].reload.l38.name = "reload15";
	locations[n].reload.l38.go = "GloriaChurch";
	locations[n].reload.l38.emerge = "reload1";
	locations[n].reload.l38.autoreload = "0";
	locations[n].reload.l38.label = "GloriaChurch cabin";

	locations[n].reload.l39.name = "reload18";
	locations[n].reload.l39.go = "GloriaChurch";
	locations[n].reload.l39.emerge = "reload4";
	locations[n].reload.l39.autoreload = "0";
	locations[n].reload.l39.label = "GloriaChurch cabin";

	locations[n].reload.l40.name = "reload17";
	locations[n].reload.l40.go = "GloriaChurch";
	locations[n].reload.l40.emerge = "reload2";
	locations[n].reload.l40.autoreload = "0";
	locations[n].reload.l40.label = "GloriaChurch cabin";

	locations[n].reload.l41.name = "reload16";
	locations[n].reload.l41.go = "GloriaChurch";
	locations[n].reload.l41.emerge = "reload3";
	locations[n].reload.l41.autoreload = "0";
	locations[n].reload.l41.label = "GloriaChurch cabin";

	locations[n].reload.l42.name = "reload19";
	locations[n].reload.l42.go = "GloriaChurch";
	locations[n].reload.l42.emerge = "reload5";
	locations[n].reload.l42.autoreload = "0";
	locations[n].reload.l42.label = "GloriaChurch cabin";

	//////// Флейт  PlutoStoreSmall ////////
	locations[n].reload.l43.name = "reload10";
	locations[n].reload.l43.go = "PlutoStoreSmall";
	locations[n].reload.l43.emerge = "reload1";
	locations[n].reload.l43.autoreload = "0";
	locations[n].reload.l43.label = "PlutoStoreSmall cabin";
	locations[n].reload.l43.close_for_night = 1;
	locations[n].reload.l43.disable = true; //закрыто навсегда

	locations[n].reload.l44.name = "reload9";
	locations[n].reload.l44.go = "PlutoStoreSmall";
	locations[n].reload.l44.emerge = "reload2";
	locations[n].reload.l44.autoreload = "0";
	locations[n].reload.l44.label = "PlutoStoreSmall cabin";
	locations[n].reload.l44.close_for_night = 1;

	locations[n].reload.l45.name = "reload11";
	locations[n].reload.l45.go = "PlutoStoreSmall";
	locations[n].reload.l45.emerge = "reload3";
	locations[n].reload.l45.autoreload = "0";
	locations[n].reload.l45.label = "PlutoStoreSmall cabin";
	locations[n].reload.l45.close_for_night = 1;

	locations[n].reload.l46.name = "reload12";
	locations[n].reload.l46.go = "PlutoStoreSmall";
	locations[n].reload.l46.emerge = "reload4";
	locations[n].reload.l46.autoreload = "0";
	locations[n].reload.l46.label = "PlutoStoreSmall cabin";
	locations[n].reload.l46.close_for_night = 1;

	locations[n].reload.l47.name = "reload14";
	locations[n].reload.l47.go = "PlutoStoreSmall";
	locations[n].reload.l47.emerge = "reload5";
	locations[n].reload.l47.autoreload = "0";
	locations[n].reload.l47.label = "PlutoStoreSmall cabin";
	locations[n].reload.l47.close_for_night = 1;

	//////// Корвет Протектор  ProtectorFisher ////////
	locations[n].reload.l48.name = "reload33"; // резиденция ривадос
	locations[n].reload.l48.go = "ProtectorFisher";
	locations[n].reload.l48.emerge = "reload1";
	locations[n].reload.l48.autoreload = "0";
	locations[n].reload.l48.label = "ProtectorFisher cabin";
	locations[n].reload.l48.close_for_night = 1;

	//////// Варшип Сан Августин  SanAugustineResidence ////////
	locations[n].reload.l49.name = "reload1";
	locations[n].reload.l49.go = "SanAugustineResidence";
	locations[n].reload.l49.emerge = "reload1";
	locations[n].reload.l49.autoreload = "0";
	locations[n].reload.l49.label = "SanAugustineResidence cabin";
	locations[n].reload.l49.close_for_night = 1;
	locations[n].reload.l49.disable = true;

	locations[n].reload.l50.name = "reload3";
	locations[n].reload.l50.go = "SanAugustineResidence";
	locations[n].reload.l50.emerge = "reload2";
	locations[n].reload.l50.autoreload = "0";
	locations[n].reload.l50.label = "SanAugustineResidence cabin";
	locations[n].reload.l50.close_for_night = 1;
	locations[n].reload.l50.disable = true;

	locations[n].reload.l51.name = "reload4";
	locations[n].reload.l51.go = "SanAugustineResidence";
	locations[n].reload.l51.emerge = "reload3";
	locations[n].reload.l51.autoreload = "0";
	locations[n].reload.l51.label = "SanAugustineResidence cabin";
	locations[n].reload.l51.close_for_night = 1;
	locations[n].reload.l51.disable = true;

	locations[n].reload.l52.name = "reload6";
	locations[n].reload.l52.go = "SanAugustineResidence";
	locations[n].reload.l52.emerge = "reload4";
	locations[n].reload.l52.autoreload = "0";
	locations[n].reload.l52.label = "SanAugustineResidence cabin";
	locations[n].reload.l52.close_for_night = 1;

	locations[n].reload.l53.name = "reload5";
	locations[n].reload.l53.go = "SanAugustineResidence";
	locations[n].reload.l53.emerge = "reload5";
	locations[n].reload.l53.autoreload = "0";
	locations[n].reload.l53.label = "SanAugustineResidence cabin";
	locations[n].reload.l53.close_for_night = 1;
	locations[n].reload.l53.disable = true;

	locations[n].reload.l54.name = "reload7";
	locations[n].reload.l54.go = "SanAugustineResidence";
	locations[n].reload.l54.emerge = "reload6";
	locations[n].reload.l54.autoreload = "0";
	locations[n].reload.l54.label = "SanAugustineResidence cabin";
	locations[n].reload.l54.close_for_night = 1;
	locations[n].reload.l54.disable = true;

	locations[n].reload.l55.name = "reload8";
	locations[n].reload.l55.go = "SanAugustineResidence";
	locations[n].reload.l55.emerge = "reload7";
	locations[n].reload.l55.autoreload = "0";
	locations[n].reload.l55.label = "SanAugustineResidence cabin";
	locations[n].reload.l55.close_for_night = 1;

	locations[n].reload.l56.name = "reload2"; // проход из затопленного трюма
	locations[n].reload.l56.go = "SanAugustineResidence";
	locations[n].reload.l56.emerge = "reload8";
	locations[n].reload.l56.autoreload = "0";
	locations[n].reload.l56.label = "SanAugustineResidence cabin";

	//////// Барк Сан Габриель   SanGabrielMechanic ////////
	locations[n].reload.l57.name = "reload55";
	locations[n].reload.l57.go = "SanGabrielMechanic";
	locations[n].reload.l57.emerge = "reload1";
	locations[n].reload.l57.autoreload = "0";
	locations[n].reload.l57.label = "SanGabrielMechanic cabin";
	locations[n].reload.l57.close_for_night = 1;

	locations[n].reload.l58.name = "reload56";
	locations[n].reload.l58.go = "SanGabrielMechanic";
	locations[n].reload.l58.emerge = "reload2";
	locations[n].reload.l58.autoreload = "0";
	locations[n].reload.l58.label = "SanGabrielMechanic cabin";
	locations[n].reload.l58.close_for_night = 1;

	locations[n].reload.l59.name = "reload57";
	locations[n].reload.l59.go = "SanGabrielMechanic";
	locations[n].reload.l59.emerge = "reload3";
	locations[n].reload.l59.autoreload = "0";
	locations[n].reload.l59.label = "SanGabrielMechanic cabin";
	locations[n].reload.l59.close_for_night = 1;

	locations[n].reload.l60.name = "reload58";
	locations[n].reload.l60.go = "SanGabrielMechanic";
	locations[n].reload.l60.emerge = "reload4";
	locations[n].reload.l60.autoreload = "0";
	locations[n].reload.l60.label = "SanGabrielMechanic cabin";
	locations[n].reload.l60.close_for_night = 1;

	locations[n].reload.l61.name = "reload54";
	locations[n].reload.l61.go = "SanGabrielMechanic";
	locations[n].reload.l61.emerge = "reload5";
	locations[n].reload.l61.autoreload = "0";
	locations[n].reload.l61.label = "SanGabrielMechanic cabin";

	locations[n].reload.l62.name = "reload53";
	locations[n].reload.l62.go = "SanGabrielMechanic";
	locations[n].reload.l62.emerge = "reload6";
	locations[n].reload.l62.autoreload = "0";
	locations[n].reload.l62.label = "SanGabrielMechanic cabin";

	//////// Бриг Санта Флорентина  SantaFlorentinaShipInside4 ////////
	locations[n].reload.l63.name = "reload21";
	locations[n].reload.l63.go = "SantaFlorentinaShipInside4";
	locations[n].reload.l63.emerge = "reload1";
	locations[n].reload.l63.autoreload = "0";
	locations[n].reload.l63.label = "SantaFlorentinaShipInside4 cabin";

	locations[n].reload.l64.name = "reload22";
	locations[n].reload.l64.go = "SantaFlorentinaShipInside4";
	locations[n].reload.l64.emerge = "reload2";
	locations[n].reload.l64.autoreload = "0";
	locations[n].reload.l64.label = "SantaFlorentinaShipInside4 cabin";

	locations[n].reload.l65.name = "reload26";
	locations[n].reload.l65.go = "SantaFlorentinaShipInside4";
	locations[n].reload.l65.emerge = "reload3";
	locations[n].reload.l65.autoreload = "0";
	locations[n].reload.l65.label = "SantaFlorentinaShipInside4 cabin";

	locations[n].reload.l66.name = "reload27";
	locations[n].reload.l66.go = "SantaFlorentinaShipInside4";
	locations[n].reload.l66.emerge = "reload4";
	locations[n].reload.l66.autoreload = "0";
	locations[n].reload.l66.label = "SantaFlorentinaShipInside4 cabin";

	locations[n].reload.l67.name = "reload23";
	locations[n].reload.l67.go = "SantaFlorentinaShipInside4";
	locations[n].reload.l67.emerge = "reload5";
	locations[n].reload.l67.autoreload = "0";
	locations[n].reload.l67.label = "SantaFlorentinaShipInside4 cabin";

	//////// Бэттлшип Тартарус   TartarusPrison ////////
	locations[n].reload.l68.name = "reload51";
	locations[n].reload.l68.go = "TartarusPrison";
	locations[n].reload.l68.emerge = "reload1";
	locations[n].reload.l68.autoreload = "0";
	locations[n].reload.l68.label = "TartarusPrison cabin";
	locations[n].reload.l68.disable = true; // закрыто до поры

	locations[n].reload.l69.name = "reload52";
	locations[n].reload.l69.go = "TartarusPrison";
	locations[n].reload.l69.emerge = "reload2";
	locations[n].reload.l69.autoreload = "0";
	locations[n].reload.l69.label = "TartarusPrison cabin";
	locations[n].reload.l69.disable = true; // закрыто до поры

	//////// Галеон Веласко  VelascoShipInside1 ////////
	locations[n].reload.l70.name = "reload68";
	locations[n].reload.l70.go = "VelascoShipInside1";
	locations[n].reload.l70.emerge = "reload1";
	locations[n].reload.l70.autoreload = "0";
	locations[n].reload.l70.label = "VelascoShipInside1 cabin";
	locations[n].reload.l70.close_for_night = 1;

	locations[n].reload.l71.name = "reload66";
	locations[n].reload.l71.go = "VelascoShipInside1";
	locations[n].reload.l71.emerge = "reload2";
	locations[n].reload.l71.autoreload = "0";
	locations[n].reload.l71.label = "VelascoShipInside1 cabin";
	locations[n].reload.l71.close_for_night = 1;

	locations[n].reload.l72.name = "reload67";
	locations[n].reload.l72.go = "VelascoShipInside1";
	locations[n].reload.l72.emerge = "reload3";
	locations[n].reload.l72.autoreload = "0";
	locations[n].reload.l72.label = "VelascoShipInside1 cabin";
	locations[n].reload.l72.close_for_night = 1;

	locations[n].reload.l73.name = "reload69";
	locations[n].reload.l73.go = "VelascoShipInside1";
	locations[n].reload.l73.emerge = "reload4";
	locations[n].reload.l73.autoreload = "0";
	locations[n].reload.l73.label = "VelascoShipInside1 cabin";
	locations[n].reload.l73.close_for_night = 1;
	
	//////////// проход на корабль внешнего кольца ///////////
	locations[n].reload.l74.name = "reload_ring";
	locations[n].reload.l74.go = "ExternalRingInside";
	locations[n].reload.l74.emerge = "reload1";
	locations[n].reload.l74.autoreload = "0";
	locations[n].reload.l74.disable = 1;  //закрыто до поры
	locations[n].locators_radius.reload.reload_ring = 2.5;

	//ключи для сундуков и предметы внутри
	// наружные сундуки не содержат денег и дублонов. Содержимое: минералы, камни, лечилки, амулеты, хлам, металлолом, пули, порох, картечь
	locations[n].private1.key = "key3";		//внутри резиденции в трюме
	locations[n].private1.skel = true;
	locations[n].private1.items.mineral15 = 1;
	locations[n].private1.items.mineral19 = 12;
	locations[n].private1.items.slave_01 = 1;
	locations[n].private1.items.cartridge = 60;
	locations[n].private1.items.jewelry16 = 6;
	locations[n].private1.items.jewelry21 = 4;
	locations[n].private1.items.jewelry23 = 7;
	locations[n].private1.items.jewelry2 = 99;
	locations[n].private1.items.jewelry3 = 51;
	locations[n].private1.items.jewelry4 = 24;
	locations[n].private1.items.jewelry10 = 3; // Pt
	locations[n].private1.items.obereg_8 = 1;

	locations[n].private2.key = "key1";
	locations[n].private2.skel = true;
	locations[n].private2.items.mineral18 = 5;
	locations[n].private2.items.mineral21 = 1;
	locations[n].private2.items.slave_02 = 3;
	locations[n].private2.items.potion1 = 8;
	locations[n].private2.items.jewelry40 = 2;
	locations[n].private2.items.jewelry43 = 3;
	locations[n].private2.items.jewelry42 = 5;
	locations[n].private2.items.jewelry46 = 28;
	locations[n].private2.items.jewelry48 = 33;
	locations[n].private2.items.jewelry45 = 5;

	locations[n].private3.key = "key2";
	locations[n].private3.skel = true;
	locations[n].private3.items.mineral34 = 20;
	locations[n].private3.items.mineral26 = 2;
	locations[n].private3.items.mineral23 = 15;
	locations[n].private3.items.topor_05 = 2;
	locations[n].private3.items.potionwine = 1;
	locations[n].private3.items.blade_08 = 1;
	locations[n].private3.items.blade_05 = 1;
	locations[n].private3.items.blade_11 = 3;
	locations[n].private3.items.topor_02 = 4;
	locations[n].private3.items.topor_03 = 3;
	locations[n].private3.items.blade_12 = 1;
	locations[n].private3.items.indian_4 = 1;

	locations[n].private4.key = "key2";
	locations[n].private4.skel = true;
	locations[n].private4.items.mineral24 = 1;
	locations[n].private4.items.mineral6 = 3;
	locations[n].private4.items.grapeshot = 100;
	locations[n].private4.items.GunPowder = 48;
	locations[n].private4.items.potion1 = 5;
	locations[n].private4.items.potion2 = 5;
	locations[n].private4.items.mineral3 = 40;
	locations[n].private4.items.cirass5 = 1;
	locations[n].private4.items.obereg_5 = 1;

	locations[n].private5.key = "key1";
	locations[n].private5.skel = true;
	locations[n].private5.items.mineral1 = 4;
	locations[n].private5.items.mineral9 = 2;
	locations[n].private5.items.blade_07 = 1;
	locations[n].private5.items.potion3 = 9;
	locations[n].private5.items.mineral33 = 10;
	locations[n].private5.items.mineral35 = 1;
	locations[n].private5.items.mineral27 = 1;
	locations[n].private5.items.mineral22 = 15;
	locations[n].private5.items.mineral23 = 69;

	locations[n].private6.key = "key1";
	locations[n].private6.skel = true;
	locations[n].private6.items.mineral10 = 5;
	locations[n].private6.items.mineral11 = 3;
	locations[n].private6.items.pistol1 = 3;
	locations[n].private6.items.potionwine = 2;
	locations[n].private6.items.astrolab = 1;
	locations[n].private6.items.spyglass3 = 1;
	locations[n].private6.items.obereg_9 = 1;

	locations[n].private7.key = "key1";
	locations[n].private7.skel = true;
	locations[n].private7.items.mineral13 = 1;
	locations[n].private7.items.mineral20 = 6;
	locations[n].private7.items.mineral23 = 11;
	locations[n].private7.items.bullet = 90;
	locations[n].private7.items.pistol1 = 2;
	locations[n].private7.items.potion1 = 12;
	locations[n].private7.items.cirass1 = 1;
	
	locations[n].private8.key = "key_gun"; // тут лежит винтовальный штуцер
	locations[n].private8.key.delItem = true;
	locations[n].private8.items.mushket5 = 1;
	locations[n].private8.items.bullet = 5;
	locations[n].private8.items.GunPowder = 5;
	locations[n].private8.items.cartridge = 5;
	locations[n].private8.items.indian_2 = 1;

	locations[n].private9.key = "key3";
	locations[n].private9.skel = true;
	locations[n].private9.items.mineral25 = 1;
	locations[n].private9.items.mineral30 = 10;
	locations[n].private9.items.GunPowder = 100;
	locations[n].private9.items.potion2 = 20;
	locations[n].private9.items.jewelry6 = 58;
	locations[n].private9.items.jewelry10 = 3; // Pt
	
	locations[n].private10.key = "sant_anna_key";	//у скелета Ривадоса
	locations[n].private10.key.delItem = true;
	locations[n].private10.money = 200000;
	locations[n].private10.items.gold_dublon = 1000;
	locations[n].private10.items.jewelry5 = 300;
	locations[n].private10.items.jewelry6 = 350;
	locations[n].private10.items.jewelry10 = 5; // Pt
	locations[n].private10.items.map_bad = 1;
	locations[n].private10.items.mushket3 = 1;
	locations[n].private10.items.key_betancur = 1;

	locations[n].private11.key = "key3"; //внутри Диффиндура
	locations[n].private11.skel = true;
	locations[n].private11.money = 2111;
	locations[n].private11.items.potion7 = 1;
	locations[n].private11.items.blade_15 = 1;
	locations[n].private11.items.jewelry6 = 105;
	locations[n].private11.items.jewelry10 = 3; // Pt
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Галеон Эва   AvaShipInside3
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "AvaShipInside3";
	locations[n].id.label = "Ava Cabin";
	locations[n].filespath.models = "locations\LostShipsCityInsides\AvaShipInside3";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LostShipsCity";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	locations[n].islandId = "LostShipsCity";	
	//Models
	//Always	
	Locations[n].models.always.inside = "AvaShipInside3";
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.seabed = "AvaShipInside3_sb";
	Locations[n].models.always.outdoor = "AvaShipInside3_outdoor";		
	Locations[n].models.always.reflect = "AvaShipInside3_reflect";
	Locations[n].models.always.reflect.level = 65531;
	Locations[n].models.always.reflect.sea_reflection = 1;	
	Locations[n].models.always.windows = "AvaShipInside3_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;	
	Locations[n].models.always.sails = "AvaShipInside3_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65534;	
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;	
	Locations[n].models.always.plan2 = "Plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65532;	
	Locations[n].models.always.locators = "AvaShipInside3_locators";	
	Locations[n].models.always.grassPatch = "AvaShipInside3_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";					
	//Day
	locations[n].models.day.charactersPatch = "AvaShipInside3_patch_day";
	locations[n].models.day.fonarday = "AvaShipInside3_fd";	
	//Night
	locations[n].models.night.charactersPatch = "AvaShipInside3_patch_day";	
	Locations[n].models.night.fonarnight = "AvaShipInside3_fn";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload41";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "LostShipsCity_town";
	locations[n].reload.l2.emerge = "reload43";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "LSC Town";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "LostShipsCity_town";
	locations[n].reload.l3.emerge = "reload44";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "LSC Town";

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "LostShipsCity_town";
	locations[n].reload.l4.emerge = "reload42";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "LSC Town";

	//ключи для сундуков и предметы внутри. Отмычки открывают все. 
	locations[n].private1.key = "key3";
	locations[n].private1.skel = true;
	locations[n].private1.money = 25250;
	locations[n].private1.items.gold_dublon = 20;
	locations[n].private1.items.jewelry40 = 1;
	locations[n].private1.items.jewelry41 = 2;
	locations[n].private1.items.jewelry42 = 1;
	locations[n].private1.items.jewelry43 = 10;
	locations[n].private1.items.jewelry45 = 5;
	locations[n].private1.items.jewelry46 = 7;
	locations[n].private1.items.mineral29 = 1; // азотная кислота
	
	locations[n].private2.key = "key1"; // в трюме за бочками. Сюда положим бубен
	locations[n].private2.skel = true;
	locations[n].private2.items.gold_dublon = 9;
	locations[n].private2.items.buben = 1;
	locations[n].private2.items.obereg_2 = 1;
	locations[n].private2.items.indian_5 = 1;
	locations[n].private2.items.blade_12 = 1;
	locations[n].private2.items.Mineral33 = 10;

	locations[n].private3.key = "key2";
	locations[n].private3.skel = true;
	locations[n].private3.items.gold_dublon = 7;
	locations[n].private3.items.potion1 = 10;
	locations[n].private3.items.potion2 = 3;
	locations[n].private3.items.jewelry22 = 20;
	locations[n].private3.items.jewelry21 = 5;
	locations[n].private3.items.jewelry2 = 32;
	
	LAi_LocationFightDisable(&locations[n], true);

	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Фрегат Каролина   CarolineBank
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "CarolineBank";
	locations[n].id.label = "Caroline cabin";
	locations[n].filespath.models = "locations\LostShipsCityInsides\CarolineBank";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LostShipsCity";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	locations[n].islandId = "LostShipsCity";	
	//Models
	//Always	
	Locations[n].models.always.inside = "CarolineBank";	
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.outdoor = "CarolineBank_outdoor";		
	Locations[n].models.always.reflect = "CarolineBank_reflect";
	Locations[n].models.always.reflect.level = 65531;
	Locations[n].models.always.reflect.sea_reflection = 1;	
	Locations[n].models.always.windows = "CarolineBank_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;	
	Locations[n].models.always.sails = "CarolineBank_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65534;	
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;	
	Locations[n].models.always.plan2 = "Plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65532;	
	Locations[n].models.always.locators = "CarolineBank_locators";	
	Locations[n].models.always.grassPatch = "CarolineBank_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";					
	//Day
	locations[n].models.day.charactersPatch = "CarolineBank_patch_day";
	locations[n].models.day.fonarday = "CarolineBank_fd";	
	//Night
	locations[n].models.night.charactersPatch = "CarolineBank_patch_day";	
	Locations[n].models.night.fonarnight = "CarolineBank_fn";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload20";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "LostShipsCity_town";
	locations[n].reload.l2.emerge = "reload24";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "LSC Town";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "LostShipsCity_town";
	locations[n].reload.l3.emerge = "reload25";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "LSC Town";

	//ключи для сундуков и предметы внутри
	locations[n].private1.key = "key3"; // сюда положим записку Фацио, ключ сменится в процессе квеста
	locations[n].private1.money = 20000;
	locations[n].private1.items.gold_dublon = 50;

	locations[n].private2.key = "key_facioQ"; // квестовый
	locations[n].private2.money = 200000;
	locations[n].private2.items.gold_dublon = 700;
	locations[n].private2.items.jewelry4 = 25;
	locations[n].private2.items.jewelry2 = 50;
	locations[n].private2.items.map_trinidad = 1;
	locations[n].private2.items.talisman6 = 1;
	locations[n].private2.items.recipe_totem_09 = 1;
	locations[n].private2.items.totem_09 = 1;
	
	locations[n].locators_radius.item.key1 = 1.0;
	
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Флейт Церес Смити   CeresSmithy
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "CeresSmithy";
	locations[n].id.label = "CeresSmithy cabin";
	locations[n].filespath.models = "locations\LostShipsCityInsides\CeresSmithy";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LostShipsCity";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	locations[n].islandId = "LostShipsCity";	
	//Models
	//Always	
	Locations[n].models.always.inside = "CeresSmithy";
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.seabed = "CeresSmithy_sb";
	Locations[n].models.always.outdoor = "CeresSmithy_outdoor";		
	Locations[n].models.always.reflect = "CeresSmithy_reflect";
	Locations[n].models.always.reflect.level = 65531;
	Locations[n].models.always.reflect.sea_reflection = 1;	
	Locations[n].models.always.windows = "CeresSmithy_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;	
	Locations[n].models.always.sails = "CeresSmithy_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65534;	
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;	
	Locations[n].models.always.plan2 = "Plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65532;	
	Locations[n].models.always.locators = "CeresSmithy_locators";	
	Locations[n].models.always.grassPatch = "CeresSmithy_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";					
	//Day
	locations[n].models.day.charactersPatch = "CeresSmithy_patch_day";
	locations[n].models.day.fonarday = "CeresSmithy_fd";	
	//Night
	locations[n].models.night.charactersPatch = "CeresSmithy_patch_day";	
	Locations[n].models.night.fonarnight = "CeresSmithy_fn";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload65";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "LostShipsCity_town";
	locations[n].reload.l2.emerge = "reload64";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "LSC Town";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "LostShipsCity_town";
	locations[n].reload.l3.emerge = "reload62";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "LSC Town";
	locations[n].reload.l3.disable = true; //закрыто до поры

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "LostShipsCity_town";
	locations[n].reload.l4.emerge = "reload63";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "LSC Town";
	locations[n].reload.l4.disable = true; //закрыто до поры

	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "LostShipsCity_town";
	locations[n].reload.l5.emerge = "reload59";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "LSC Town";
	locations[n].reload.l5.disable = true; //закрыто до поры

	locations[n].reload.l6.name = "reload6";
	locations[n].reload.l6.go = "LostShipsCity_town";
	locations[n].reload.l6.emerge = "reload60";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "LSC Town";

	locations[n].reload.l7.name = "reload7";
	locations[n].reload.l7.go = "LostShipsCity_town";
	locations[n].reload.l7.emerge = "reload61";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "LSC Town";

	//ключи для сундуков и предметы внутри
	locations[n].private1.key = "key1"; // у Юргена - не взламывается
	locations[n].private1.items.spyglass1 = 102;

	locations[n].private2.key = "key2"; // у Мэри - не взламывается
	locations[n].private2.items.talisman8 = 1;
	
	locations[n].private3.key = "key3"; // в трюме - тоже квестовый
	locations[n].private3.money = 12834;
	
	LAi_LocationFightDisable(&locations[n], true);
	
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Галеон Эсмеральда   EsmeraldaStoreBig
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "EsmeraldaStoreBig";
	locations[n].id.label = "EsmeraldaStoreBig cabin";
	locations[n].filespath.models = "locations\LostShipsCityInsides\EsmeraldaStoreBig";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LostShipsCity";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	locations[n].islandId = "LostShipsCity";	
	//Models
	//Always	
	Locations[n].models.always.inside = "EsmeraldaStoreBig";
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.seabed = "EsmeraldaStoreBig_sb";
	Locations[n].models.always.outdoor = "EsmeraldaStoreBig_outdoor";		
	Locations[n].models.always.reflect = "EsmeraldaStoreBig_reflect";
	Locations[n].models.always.reflect.level = 65531;
	Locations[n].models.always.reflect.sea_reflection = 1;	
	Locations[n].models.always.windows = "EsmeraldaStoreBig_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;	
	Locations[n].models.always.sails = "EsmeraldaStoreBig_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65534;	
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;	
	Locations[n].models.always.plan2 = "Plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65532;	
	Locations[n].models.always.locators = "EsmeraldaStoreBig_locators";	
	Locations[n].models.always.grassPatch = "EsmeraldaStoreBig_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";					
	//Day
	locations[n].models.day.charactersPatch = "EsmeraldaStoreBig_patch_day";
	locations[n].models.day.fonarday = "EsmeraldaStoreBig_fd";	
	//Night
	locations[n].models.night.charactersPatch = "EsmeraldaStoreBig_patch_day";	
	Locations[n].models.night.fonarnight = "EsmeraldaStoreBig_fn";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload45";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "LostShipsCity_town";
	locations[n].reload.l2.emerge = "reload48";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "LSC Town";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "LostShipsCity_town";
	locations[n].reload.l3.emerge = "reload46";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "LSC Town";

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "LostShipsCity_town";
	locations[n].reload.l4.emerge = "reload49";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "LSC Town";

	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "LostShipsCity_town";
	locations[n].reload.l5.emerge = "reload50";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "LSC Town";

	locations[n].reload.l6.name = "reload6";
	locations[n].reload.l6.go = "LostShipsCity_town";
	locations[n].reload.l6.emerge = "reload47";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "LSC Town";

	locations[n].locators_radius.item.item1 = 1.2;

	//ключи для сундуков и предметы внутри
	locations[n].private1.key = "key2"; // у торговца
	locations[n].private1.skel = true;
	locations[n].private1.items.tigel = 1; // тигель
	locations[n].private1.items.mineral5 = 1;
	locations[n].private1.items.mineral23 = 45;
	locations[n].private1.items.mineral3 = 8;
	locations[n].private1.items.GunEchin = 20;

	locations[n].private2.key = "key1";	// в зале
	locations[n].private2.skel = true;
	locations[n].private2.money = 3520;
	locations[n].private2.items.gold_dublon = 2;
	locations[n].private2.items.mineral23 = 14;
	locations[n].private2.items.mineral35 = 1;
	locations[n].private2.items.mineral24 = 6;
	locations[n].private2.items.mineral22 = 10;
	locations[n].private2.items.jewelry20 = 55;
	locations[n].private2.items.recipe_totem_10 = 1;
	locations[n].private2.items.totem_10 = 1;

	locations[n].private3.key = "key3"; // у Дональда Гринспи - квестовый
	locations[n].private3.money = 27030;
	
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Платформа Феникс    FenixPlatform
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FenixPlatform";
	locations[n].id.label = "FenixPlatform cabin";
	locations[n].filespath.models = "locations\LostShipsCityInsides\FenixPlatform";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LostShipsCity";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	locations[n].islandId = "LostShipsCity";
	//Models
	//Always	
	Locations[n].models.always.inside = "FenixPlatform";
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.outdoor = "FenixPlatform_outdoor";		
	Locations[n].models.always.reflect = "FenixPlatform_reflect";
	Locations[n].models.always.reflect.level = 65531;
	Locations[n].models.always.reflect.sea_reflection = 1;	
	Locations[n].models.always.windows = "FenixPlatform_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;	
	Locations[n].models.always.sails = "FenixPlatform_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65534;	
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;	
	Locations[n].models.always.plan2 = "Plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65532;	
	Locations[n].models.always.locators = "FenixPlatform_locators";	
	Locations[n].models.always.grassPatch = "FenixPlatform_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";					
	//Day
	locations[n].models.day.charactersPatch = "FenixPlatform_patch_day";
	locations[n].models.day.fonarday = "FenixPlatform_fd";	
	//Night
	locations[n].models.night.charactersPatch = "FenixPlatform_patch_day";	
	Locations[n].models.night.fonarnight = "FenixPlatform_fn";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload72";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	locations[n].locators_radius.item.armor = 1.3;

	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Флейт Фернандо Диффиндур   FernandaDiffIndoor
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FernandaDiffIndoor";
	locations[n].id.label = "FernandaDiffIndoor cabin";
	locations[n].filespath.models = "locations\LostShipsCityInsides\FernandaDiffIndoor";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LostShipsCity";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	locations[n].islandId = "LostShipsCity";
	//Models
	//Always	
	Locations[n].models.always.inside = "FernandaDiffIndoor";
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.seabed = "FernandaDiffIndoor_sb";
	Locations[n].models.always.outdoor = "FernandaDiffIndoor_outdoor";		
	Locations[n].models.always.reflect = "FernandaDiffIndoor_reflect";
	Locations[n].models.always.reflect.level = 65531;
	Locations[n].models.always.reflect.sea_reflection = 1;	
	Locations[n].models.always.windows = "FernandaDiffIndoor_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;	
	Locations[n].models.always.sails = "FernandaDiffIndoor_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65534;	
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;	
	Locations[n].models.always.plan2 = "Plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65532;	
	Locations[n].models.always.locators = "FernandaDiffIndoor_locators";	
	Locations[n].models.always.grassPatch = "FernandaDiffIndoor_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";					
	//Day
	locations[n].models.day.charactersPatch = "FernandaDiffIndoor_patch_day";
	locations[n].models.day.fonarday = "FernandaDiffIndoor_fd";	
	//Night
	locations[n].models.night.charactersPatch = "FernandaDiffIndoor_patch_day";	
	Locations[n].models.night.fonarnight = "FernandaDiffIndoor_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload74";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	//ключи для сундуков и предметы внутри
	locations[n].private1.key = "key1";
	locations[n].private1.skel = true;
	locations[n].private1.items.jewelry8 = 99;
	locations[n].private1.items.jewelry7 = 1;
	locations[n].private1.items.jewelry11 = 1; // метеорит
	locations[n].private1.items.jewelry52 = 220;
	locations[n].private1.items.jewelry53 = 1344;
	locations[n].private1.items.mineral3 = 20;

	locations[n].private2.key = "key2";
	locations[n].private2.skel = true;
	locations[n].private2.items.jewelry19 = 64;
	locations[n].private2.items.mineral26 = 5;
	locations[n].private2.items.mineral19 = 12;
	locations[n].private2.items.mineral9 = 2;
	locations[n].private2.items.mineral2 = 4;
	locations[n].private2.items.gold_dublon = 13;
	locations[n].private2.items.mineral18 = 5;
	locations[n].private2.items.spyglass2 = 1;
	locations[n].private2.items.map_beliz = 1;
	
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Каравелла Флерон   FleuronTavern 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FleuronTavern";
	locations[n].id.label = "FleuronTavern cabin";
	locations[n].filespath.models = "locations\LostShipsCityInsides\FleuronTavern";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LostShipsCity";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	locations[n].islandId = "LostShipsCity";
	//Models
	//Always	
	Locations[n].models.always.inside = "FleuronTavern";
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.outdoor = "FleuronTavern_outdoor";		
	Locations[n].models.always.reflect = "FleuronTavern_reflect";
	Locations[n].models.always.reflect.level = 65531;
	Locations[n].models.always.reflect.sea_reflection = 1;	
	Locations[n].models.always.windows = "FleuronTavern_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;	
	Locations[n].models.always.sails = "FleuronTavern_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65534;	
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;	
	Locations[n].models.always.plan2 = "Plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65532;	
	Locations[n].models.always.locators = "FleuronTavern_locators";	
	Locations[n].models.always.grassPatch = "FleuronTavern_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";					
	//Day
	locations[n].models.day.charactersPatch = "FleuronTavern_patch_day";
	locations[n].models.day.fonarday = "FleuronTavern_fd";	
	//Night
	locations[n].models.night.charactersPatch = "FleuronTavern_patch_day";	
	Locations[n].models.night.fonarnight = "FleuronTavern_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	LAi_LocationFightDisable(&locations[n], true);
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload38";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "LostShipsCity_town";
	locations[n].reload.l2.emerge = "reload37";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "LSC Town";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "LostShipsCity_town";
	locations[n].reload.l3.emerge = "reload35";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "LSC Town";

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "LostShipsCity_town";
	locations[n].reload.l4.emerge = "reload34";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "LSC Town";

	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "LostShipsCity_town";
	locations[n].reload.l5.emerge = "reload36";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "LSC Town";
	locations[n].reload.l5.disable = 1;  //закрыто навсегда

	locations[n].reload.l6.name = "reload6";
	locations[n].reload.l6.go = "LostShipsCity_town";
	locations[n].reload.l6.emerge = "reload39";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "LSC Town";

	locations[n].reload.l7.name = "reload7";
	locations[n].reload.l7.go = "LostShipsCity_town";
	locations[n].reload.l7.emerge = "reload40";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "LSC Town";
	locations[n].locators_radius.item.detector1 = 0.3;

	//ключи для сундуков и предметы внутри
	locations[n].private1.key = "key1";
	locations[n].private1.skel = true;
	locations[n].private1.items.gold_dublon = 5;
	locations[n].private1.items.potion2 = 2;
	locations[n].private1.items.mineral3 = 66;
	locations[n].private1.items.jewelry15 = 20;
	locations[n].private1.items.pistol6 = 1;
	locations[n].private1.items.cirass6 = 1;

	locations[n].private2.key = "key2";
	locations[n].private2.skel = true;
	locations[n].private2.money = 11063;
	locations[n].private2.items.gold_dublon = 10;
	locations[n].private2.items.map_cayman = 1;
	locations[n].private2.items.spyglass1 = 1;
	locations[n].private2.items.mineral10 = 4;
	locations[n].private2.items.mineral15 = 2;
	locations[n].private2.items.mineral17 = 10;
	
	locations[n].private3.key = "key3"; // в кладовке
	locations[n].private3.skel = true;
	locations[n].private3.items.potion1 = 28;
	locations[n].private3.items.compass1 = 1;
	locations[n].private3.items.potionwine = 25;
	locations[n].private3.items.jewelry21 = 19;
	locations[n].private3.items.jewelry47 = 9;
	locations[n].private3.items.jewelry12 = 5;
	locations[n].private3.items.jewelry13 = 4;
	
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пинас Фурия   FurieShipInside2
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FurieShipInside2";
	locations[n].id.label = "FurieShipInside2 cabin";
	locations[n].filespath.models = "locations\LostShipsCityInsides\FurieShipInside2";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LostShipsCity";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	locations[n].islandId = "LostShipsCity";
	locations[n].lsc_inside = "rivados"; // внутренний корабль кланов
	//Models
	//Always	
	Locations[n].models.always.inside = "FurieShipInside2";
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.seabed = "FurieShipInside2_sb";
	Locations[n].models.always.outdoor = "FurieShipInside2_outdoor";		
	Locations[n].models.always.reflect = "FurieShipInside2_reflect";
	Locations[n].models.always.reflect.level = 65531;
	Locations[n].models.always.reflect.sea_reflection = 1;	
	Locations[n].models.always.windows = "FurieShipInside2_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;	
	Locations[n].models.always.sails = "FurieShipInside2_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65534;	
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;	
	Locations[n].models.always.plan2 = "Plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65532;	
	Locations[n].models.always.locators = "FurieShipInside2_locators";	
	Locations[n].models.always.grassPatch = "FurieShipInside2_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";					
	//Day
	locations[n].models.day.charactersPatch = "FurieShipInside2_patch_day";
	locations[n].models.day.fonarday = "FurieShipInside2_fd";	
	//Night
	locations[n].models.night.charactersPatch = "FurieShipInside2_patch_day";	
	Locations[n].models.night.fonarnight = "FurieShipInside2_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload29";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "LostShipsCity_town";
	locations[n].reload.l2.emerge = "reload31";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "LSC Town";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "LostShipsCity_town";
	locations[n].reload.l3.emerge = "reload32";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "LSC Town";

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "LostShipsCity_town";
	locations[n].reload.l4.emerge = "reload30";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "LSC Town";

	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "LostShipsCity_town";
	locations[n].reload.l5.emerge = "reload28";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "LSC Town";

	locations[n].reload.l6.name = "reload6";
	locations[n].reload.l6.go = "LostShipsCity_town";
	locations[n].reload.l6.emerge = "reload47";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "LSC Town";

	//ключи для сундуков и предметы внутри
	locations[n].private1.key = "key1";
	locations[n].private1.skel = true;
	locations[n].private1.money = 7473;
	locations[n].private1.items.gold_dublon = 4;
	locations[n].private1.items.mineral3 = 50;
	locations[n].private1.items.mineral4 = 5;
	locations[n].private1.items.mineral7 = 1;
	locations[n].private1.items.mineral9 = 2;
	locations[n].private1.items.mineral10 = 3;
	locations[n].private1.items.mineral14 = 1;
	locations[n].private1.items.mineral15 = 1;
	locations[n].private1.items.mineral16 = 1;
	locations[n].private1.items.mineral24 = 1;

	locations[n].private2.key = "key2";
	locations[n].private2.skel = true;
	locations[n].private2.money = 125;
	locations[n].private2.items.gold_dublon = 90;
	locations[n].private2.items.berserker_potion = 1;
	locations[n].private2.items.shotgun_bullet = 2; // револьверная пуля
	
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Галеон   GloriaChurch
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "GloriaChurch";
	locations[n].id.label = "GloriaChurch cabin";
	locations[n].filespath.models = "locations\LostShipsCityInsides\GloriaChurch";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LostShipsCity";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	locations[n].islandId = "LostShipsCity";
	//Models
	//Always	
	Locations[n].models.always.inside = "GloriaChurch";	
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.seabed = "GloriaChurch_sb";	
	Locations[n].models.always.outdoor = "GloriaChurch_outdoor";		
	Locations[n].models.always.reflect = "GloriaChurch_reflect";
	Locations[n].models.always.reflect.level = 65531;
	Locations[n].models.always.reflect.sea_reflection = 1;	
	Locations[n].models.always.windows = "GloriaChurch_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65540;	
	Locations[n].models.always.sails = "GloriaChurch_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65534;	
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;	
	Locations[n].models.always.plan2 = "Plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65532;	
	Locations[n].models.always.locators = "GloriaChurch_locators";	
	Locations[n].models.always.grassPatch = "GloriaChurch_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";		
	//Day
	locations[n].models.day.charactersPatch = "GloriaChurch_patch_day";
	locations[n].models.day.fonarday = "GloriaChurch_fd";	
	//Night
	locations[n].models.night.charactersPatch = "GloriaChurch_patch_day";	
	Locations[n].models.night.fonarnight = "GloriaChurch_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload4";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload18";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "LostShipsCity_town";
	locations[n].reload.l2.emerge = "reload17";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "LSC Town";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "LostShipsCity_town";
	locations[n].reload.l3.emerge = "reload16";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "LSC Town";

	locations[n].reload.l4.name = "reload1";
	locations[n].reload.l4.go = "LostShipsCity_town";
	locations[n].reload.l4.emerge = "reload15";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "LSC Town";

	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "LostShipsCity_town";
	locations[n].reload.l5.emerge = "reload19";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "LSC Town";

	//ключи для сундуков и предметы внутри
	locations[n].private1.key = "key3";
	locations[n].private1.skel = true;
	locations[n].private1.money = 35500;
	locations[n].private1.items.gold_dublon = 14;
	locations[n].private1.items.mineral3 = 228;
	locations[n].private1.items.amulet_10 = 1;
	locations[n].private1.items.amulet_11 = 1;
	locations[n].private1.items.jewelry45 = 25;
	
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Флейт Плуто  PlutoStoreSmall
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PlutoStoreSmall";
	locations[n].id.label = "PlutoStoreSmall cabin";
	locations[n].filespath.models = "locations\LostShipsCityInsides\PlutoStoreSmall";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LostShipsCity";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	locations[n].islandId = "LostShipsCity";
	//Models
	//Always	
	Locations[n].models.always.inside = "PlutoStoreSmall";	
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.seabed = "PlutoStoreSmall_sb";
	Locations[n].models.always.outdoor = "PlutoStoreSmall_outdoor";		
	Locations[n].models.always.reflect = "PlutoStoreSmall_reflect";
	Locations[n].models.always.reflect.level = 65531;
	Locations[n].models.always.reflect.sea_reflection = 1;	
	Locations[n].models.always.windows = "PlutoStoreSmall_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;	
	Locations[n].models.always.sails = "PlutoStoreSmall_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65534;	
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;	
	Locations[n].models.always.plan2 = "Plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65532;	
	Locations[n].models.always.locators = "PlutoStoreSmall_locators";	
	Locations[n].models.always.grassPatch = "PlutoStoreSmall_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";					
	//Day
	locations[n].models.day.charactersPatch = "PlutoStoreSmall_patch_day";
	locations[n].models.day.fonarday = "PlutoStoreSmall_fd";	
	//Night
	locations[n].models.night.charactersPatch = "PlutoStoreSmall_patch_day";	
	Locations[n].models.night.fonarnight = "PlutoStoreSmall_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload10";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";
	locations[n].reload.l1.disable = 1;  //закрыто навсегда

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "LostShipsCity_town";
	locations[n].reload.l2.emerge = "reload9";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "LSC Town";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "LostShipsCity_town";
	locations[n].reload.l3.emerge = "reload11";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "LSC Town";

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "LostShipsCity_town";
	locations[n].reload.l4.emerge = "reload12";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "LSC Town";

	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "LostShipsCity_town";
	locations[n].reload.l5.emerge = "reload14";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "LSC Town";

	//ключи для сундуков и предметы внутри
	locations[n].private1.key = "key3";
	locations[n].private1.skel = true;
	locations[n].private1.money = 5129;
	locations[n].private1.items.gold_dublon = 11;

	locations[n].private2.key = "key2"; // сюда положим зелье команчей
	locations[n].private2.skel = true;
	locations[n].private2.money = 24680;
	locations[n].private2.items.gold_dublon = 17;
	locations[n].private2.items.potion1 = 30;
	locations[n].private2.items.potion2 = 12;
	locations[n].private2.items.potion3 = 7;
	locations[n].private2.items.potion4 = 5;
	locations[n].private2.items.potionwine = 15;
	locations[n].private2.items.potion5 = 21;
	locations[n].private2.items.Ultimate_potion = 1;

	locations[n].private3.key = "key1";
	locations[n].private3.skel = true;
	locations[n].private3.money = 900;
	locations[n].private3.items.gold_dublon = 9;
	locations[n].private3.items.mineral7 = 2;
	locations[n].private3.items.mineral3 = 4;
	locations[n].private3.items.mineral23 = 19;
	
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Корвет Протектор  ProtectorFisher
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "ProtectorFisher";
	locations[n].id.label = "ProtectorFisher cabin";
	locations[n].filespath.models = "locations\LostShipsCityInsides\ProtectorFisher";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LostShipsCity";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	locations[n].islandId = "LostShipsCity";
	//Models
	//Always	
	Locations[n].models.always.inside = "ProtectorFisher";	
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.outdoor = "ProtectorFisher_outdoor";		
	Locations[n].models.always.reflect = "ProtectorFisher_reflect";
	Locations[n].models.always.reflect.level = 65531;
	Locations[n].models.always.reflect.sea_reflection = 1;	
	Locations[n].models.always.windows = "ProtectorFisher_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;	
	Locations[n].models.always.sails = "ProtectorFisher_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65534;	
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;	
	Locations[n].models.always.plan2 = "Plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65532;	
	Locations[n].models.always.locators = "ProtectorFisher_locators";	
	Locations[n].models.always.grassPatch = "ProtectorFisher_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";					
	//Day
	locations[n].models.day.charactersPatch = "ProtectorFisher_patch_day";
	locations[n].models.day.fonarday = "ProtectorFisher_fd";	
	//Night
	locations[n].models.night.charactersPatch = "ProtectorFisher_patch_day";	
	Locations[n].models.night.fonarnight = "ProtectorFisher_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload33";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	//ключи для сундуков и предметы внутри
	locations[n].private1.key = "key1"; // в резиденции Эдди
	locations[n].private1.money = 1;
	locations[n].private1.items.map_maine_2 = 1;
	
	LAi_LocationFightDisable(&locations[n], true);
	
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Варшип Сан Августин  SanAugustineResidence
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SanAugustineResidence";
	locations[n].id.label = "SanAugustineResidence cabin";
	locations[n].filespath.models = "locations\LostShipsCityInsides\SanAugustineResidence";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LostShipsCity";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	//locations[n].fastreload = "LostShipsCity";
	locations[n].islandId = "LostShipsCity";
	locations[n].lsc_inside = "shark"; // внутренний корабль кланов
	//Models
	//Always	
	Locations[n].models.always.inside = "SanAugustineResidence";
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.outdoor = "SanAugustineResidence_outdoor";		
	Locations[n].models.always.reflect = "SanAugustineResidence_reflect";
	Locations[n].models.always.reflect.level = 65531;
	Locations[n].models.always.reflect.sea_reflection = 1;	
	Locations[n].models.always.windows = "SanAugustineResidence_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;	
	Locations[n].models.always.sails = "SanAugustineResidence_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65534;	
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;	
	Locations[n].models.always.plan2 = "Plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65532;	
	Locations[n].models.always.locators = "SanAugustineResidence_locators";	
	Locations[n].models.always.grassPatch = "SanAugustineResidence_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";					
	//Day
	locations[n].models.day.charactersPatch = "SanAugustineResidence_patch_day";
	locations[n].models.day.fonarday = "SanAugustineResidence_fd";	
	//Night
	locations[n].models.night.charactersPatch = "SanAugustineResidence_patch_day";	
	Locations[n].models.night.fonarnight = "SanAugustineResidence_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "LostShipsCity_town";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "LSC Town";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "LostShipsCity_town";
	locations[n].reload.l3.emerge = "reload4";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "LSC Town";

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "LostShipsCity_town";
	locations[n].reload.l4.emerge = "reload6";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "LSC Town";

	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "LostShipsCity_town";
	locations[n].reload.l5.emerge = "reload5";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "LSC Town";

	locations[n].reload.l6.name = "reload6";
	locations[n].reload.l6.go = "LostShipsCity_town";
	locations[n].reload.l6.emerge = "reload7";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "LSC Town";

	locations[n].reload.l7.name = "reload7";
	locations[n].reload.l7.go = "LostShipsCity_town";
	locations[n].reload.l7.emerge = "reload8";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "LSC Town";

	locations[n].reload.l8.name = "reload8";
	locations[n].reload.l8.go = "LostShipsCity_town";
	locations[n].reload.l8.emerge = "reload2";
	locations[n].reload.l8.autoreload = "0";
	locations[n].reload.l8.label = "LSC Town";

	//ключи для сундуков и предметы внутри
	locations[n].private1.key = "key1"; //этот сундук пуст - для складирования лута ГГ

	locations[n].private2.key = "key2"; //напротив Акулы - злато-серебро-платина
	locations[n].private2.skel = true;
	locations[n].private2.money = 55000;
	locations[n].private2.items.gold_dublon = 100;
	locations[n].private2.items.chest = 2;
	locations[n].private2.items.incas_collection = 3;
	locations[n].private2.items.jewelry5 = 200;
	locations[n].private2.items.jewelry5 = 400;
	locations[n].private2.items.jewelry10 = 3; // 3 Pt

	locations[n].private3.key = "key1"; // в каморке
	locations[n].private3.skel = true;
	locations[n].private3.money = 2194;
	locations[n].private3.items.gold_dublon = 7;
	locations[n].private3.items.map_terks = 1;
	locations[n].private3.items.clock1 = 1;
	locations[n].private3.items.potion2 = 4;
	locations[n].private3.items.jewelry3 = 7;
	locations[n].private3.items.jewelry16 = 8;
	locations[n].private3.items.jewelry44 = 15;

	locations[n].private4.key = "key1"; // трюм под лестницей
	locations[n].private4.skel = true;
	locations[n].private4.money = 3412;
	locations[n].private4.items.map_trinidad = 1;
	locations[n].private4.items.gold_dublon = 11;
	locations[n].private4.items.jewelry49 = 5;
	locations[n].private4.items.jewelry23 = 11;
	locations[n].private4.items.jewelry14 = 1;
	locations[n].private4.items.jewelry8 = 5;
	locations[n].private4.items.mineral12 = 5;
	locations[n].private4.items.mineral21 = 1;
	locations[n].private4.items.mineral25 = 1;
	locations[n].private4.items.mineral3 = 15;

	locations[n].private5.key = "key3"; // нижний ярус - оружейка
	locations[n].private5.skel = true;
	locations[n].private5.items.blade_09 = 1;
	locations[n].private5.items.blade_10 = 1;
	locations[n].private5.items.blade_11 = 1;
	locations[n].private5.items.blade_12 = 1;
	locations[n].private5.items.blade_13 = 1;
	locations[n].private5.items.blade_14 = 1;
	locations[n].private5.items.blade_15 = 1;
	locations[n].private5.items.blade_16 = 1;
	locations[n].private5.items.indian_4 = 1;
	locations[n].private5.items.shotgun_bullet = 2; // револьверная пуля

	locations[n].private6.key = "key3"; // нижний ярус - оружейка
	locations[n].private6.skel = true;
	locations[n].private6.items.pistol1 = 10;
	locations[n].private6.items.pistol2 = 1;
	locations[n].private6.items.pistol3 = 5;
	locations[n].private6.items.pistol5 = 1;
	locations[n].private6.items.pistol6 = 1;
	locations[n].private6.items.indian_1 = 1;
	locations[n].private6.items.bullet = 100;
	locations[n].private6.items.grapeshot = 100;
	locations[n].private6.items.cartridge = 20;
	locations[n].private6.items.GunPowder = 200;
	
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Барк Сан Габриель   SanGabrielMechanic
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SanGabrielMechanic";
	locations[n].id.label = "SanGabrielMechanic cabin";
	locations[n].filespath.models = "locations\LostShipsCityInsides\SanGabrielMechanic";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LostShipsCity";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	locations[n].islandId = "LostShipsCity";
	locations[n].lsc_inside = "narval"; // внутренний корабль кланов
	//Models
	//Always	
	Locations[n].models.always.inside = "SanGabrielMechanic";
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.seabed = "SanGabrielMechanic_sb";
	Locations[n].models.always.outdoor = "SanGabrielMechanic_outdoor";		
	Locations[n].models.always.reflect = "SanGabrielMechanic_reflect";
	Locations[n].models.always.reflect.level = 65531;
	Locations[n].models.always.reflect.sea_reflection = 1;	
	Locations[n].models.always.reflTrum = "SanGabrielMechanic_refl_trum";
	Locations[n].models.always.reflTrum.level = 65539;
	Locations[n].models.always.reflTrum.sea_reflection = 1;	
	Locations[n].models.always.windows = "SanGabrielMechanic_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65540;	
	Locations[n].models.always.sails = "SanGabrielMechanic_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65534;	
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;	
	Locations[n].models.always.plan2 = "Plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65532;	
	Locations[n].models.always.locators = "SanGabrielMechanic_locators";	
	Locations[n].models.always.grassPatch = "SanGabrielMechanic_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";					
	//Day
	locations[n].models.day.charactersPatch = "SanGabrielMechanic_patch_day";
	locations[n].models.day.fonarday = "SanGabrielMechanic_fd";	
	//Night
	locations[n].models.night.charactersPatch = "SanGabrielMechanic_patch_day";	
	Locations[n].models.night.fonarnight = "SanGabrielMechanic_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload55";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "LostShipsCity_town";
	locations[n].reload.l2.emerge = "reload56";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "LSC Town";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "LostShipsCity_town";
	locations[n].reload.l3.emerge = "reload57";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "LSC Town";

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "LostShipsCity_town";
	locations[n].reload.l4.emerge = "reload58";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "LSC Town";

	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "LostShipsCity_town";
	locations[n].reload.l5.emerge = "reload54";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "LSC Town";

	locations[n].reload.l6.name = "reload6";
	locations[n].reload.l6.go = "LostShipsCity_town";
	locations[n].reload.l6.emerge = "reload53";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "LSC Town";

	//ключи для сундуков и предметы внутри
	locations[n].private1.key = "key1"; // сюда положим трубку
	locations[n].private1.skel = true;
	locations[n].private1.items.gold_dublon = 3;
	locations[n].private1.items.obereg_5 = 1;
	locations[n].private1.items.mineral3 = 8;
	locations[n].private1.items.jewelry44 = 50;
	locations[n].private1.items.jewelry49 = 24;
	locations[n].private1.items.smoking_tube = 1;
	
	locations[n].private2.key = "key3"; // у Механика - не взламывается
	locations[n].private2.money = 366430;
	locations[n].private2.items.indian_2 = 2;
	
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Бриг Санта Флорентина  SantaFlorentinaShipInside4
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantaFlorentinaShipInside4";
	locations[n].id.label = "SantaFlorentinaShipInside4 cabin";
	locations[n].filespath.models = "locations\LostShipsCityInsides\SantaFlorentinaShipInside4";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LostShipsCity";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	//locations[n].fastreload = "LostShipsCity";
	locations[n].islandId = "LostShipsCity";
	//Models
	//Always	
	Locations[n].models.always.inside = "SantaFlorentinaShipInside4";	
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.seabed = "SantaFlorentinaShipInside4_sb";	
	Locations[n].models.always.outdoor = "SantaFlorentinaShipInside4_outdoor";		
	Locations[n].models.always.reflect = "SantaFlorentinaShipInside4_reflect";
	Locations[n].models.always.reflect.level = 65541;
	Locations[n].models.always.reflect.sea_reflection = 1;		
	Locations[n].models.always.windows = "SantaFlorentinaShipInside4_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65540;	
	Locations[n].models.always.sails = "SantaFlorentinaShipInside4_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65534;	
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;	
	Locations[n].models.always.plan2 = "Plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65532;	
	Locations[n].models.always.locators = "SantaFlorentinaShipInside4_locators";	
	Locations[n].models.always.grassPatch = "SantaFlorentinaShipInside4_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";					
	//Day
	locations[n].models.day.charactersPatch = "SantaFlorentinaShipInside4_patch_day";
	locations[n].models.day.fonarday = "SantaFlorentinaShipInside4_fd";	
	//Night
	locations[n].models.night.charactersPatch = "SantaFlorentinaShipInside4_patch_day";	
	Locations[n].models.night.fonarnight = "SantaFlorentinaShipInside4_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload21";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "LostShipsCity_town";
	locations[n].reload.l2.emerge = "reload22";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "LSC Town";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "LostShipsCity_town";
	locations[n].reload.l3.emerge = "reload26";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "LSC Town";

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "LostShipsCity_town";
	locations[n].reload.l4.emerge = "reload27";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "LSC Town";

	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "LostShipsCity_town";
	locations[n].reload.l5.emerge = "reload23";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "LSC Town";

	//ключи для сундуков и предметы внутри
	locations[n].private1.key = "key1"; // в каморке
	locations[n].private1.skel = true;
	locations[n].private1.money = 5432;
	locations[n].private1.items.gold_dublon = 5;
	locations[n].private1.items.mineral28 = 1; // спирт // patch-11
	locations[n].private1.items.mineral5 = 5;
	locations[n].private1.items.jewelry45 = 8;
	locations[n].private1.items.jewelry3 = 11;
	locations[n].private1.items.mineral14 = 9;
	locations[n].private1.items.mineral4 = 3;
	locations[n].private1.items.mineral6 = 1;
	locations[n].private1.items.mineral35 = 1;

	locations[n].private2.key = "key2"; // в трюме
	locations[n].private2.skel = true;
	locations[n].private2.items.slave_02 = 16;
	locations[n].private2.items.mineral17 = 11;
	locations[n].private2.items.mineral3 = 10;
	locations[n].private2.items.jewelry7 = 3;
	locations[n].private2.items.mineral1 = 3;
	locations[n].private2.items.slave_01 = 10;
	locations[n].private2.items.jewelry12 = 3;
	locations[n].private2.items.mineral23 = 17;
	locations[n].private2.items.jewelry1 = 10;
	locations[n].private2.items.jewelry5 = 6;

	locations[n].private3.key = "key3"; // за ящиками
	locations[n].private3.skel = true;
	locations[n].private3.money = 12688;
	locations[n].private3.items.gold_dublon = 12;
	locations[n].private3.items.mineral32 = 1; // пулелейка
	locations[n].private3.items.jewelry45 = 3;
	locations[n].private3.items.jewelry11 = 1; // метеорит
	locations[n].private3.items.jewelry23 = 4;
	locations[n].private3.items.potion5 = 17;
	locations[n].private3.items.mineral23 = 8;
	locations[n].private3.items.mineral22 = 5;
	locations[n].private3.items.jewelry13 = 2;
	locations[n].private3.items.pistol1 = 2;
	locations[n].private3.items.cirass5 = 1;
	locations[n].private3.items.chest = 1;
	
	LAi_LocationFightDisable(&locations[n], true);
	
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Бэттлшип Тартарус   TartarusPrison
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "TartarusPrison";
	locations[n].id.label = "TartarusPrison cabin";
	locations[n].filespath.models = "locations\LostShipsCityInsides\TartarusPrison";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LostShipsCity";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	locations[n].islandId = "LostShipsCity";
	//Models
	//Always	
	Locations[n].models.always.inside = "TartarusPrison";
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.seabed = "TartarusPrison_sb";
	Locations[n].models.always.outdoor = "TartarusPrison_outdoor";		
	Locations[n].models.always.reflect = "TartarusPrison_reflect";
	Locations[n].models.always.reflect.level = 65531;
	Locations[n].models.always.reflect.sea_reflection = 1;	
	Locations[n].models.always.reflTrum = "TartarusPrison_refl_trum";
	Locations[n].models.always.reflTrum.level = 65539;
	Locations[n].models.always.reflTrum.sea_reflection = 1;	
	Locations[n].models.always.windows = "TartarusPrison_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65540;	
	Locations[n].models.always.sails = "TartarusPrison_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65534;	
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;	
	Locations[n].models.always.plan2 = "Plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65532;	
	Locations[n].models.always.locators = "TartarusPrison_locators";	
	Locations[n].models.always.grassPatch = "TartarusPrison_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";					
	//Day
	locations[n].models.day.charactersPatch = "TartarusPrison_patch_day";
	locations[n].models.day.fonarday = "TartarusPrison_fd";	
	//Night
	locations[n].models.night.charactersPatch = "TartarusPrison_patch_day";	
	Locations[n].models.night.fonarnight = "TartarusPrison_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload51";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "LostShipsCity_town";
	locations[n].reload.l2.emerge = "reload52";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "LSC Town";

	//ключи для сундуков и предметы внутри
	locations[n].private1.key = "key_capper"; // сундук внизу тюрьмы, открывается ломиком
	locations[n].private1.items.potion1 = 5;
	locations[n].private1.items.potion2 = 3;
	locations[n].private1.items.potionrum = 1;
	locations[n].private1.items.blade_04 = 1;
	locations[n].private1.items.bullet = 25;
	locations[n].private1.items.GunPowder = 25;
	locations[n].private1.items.pistol1 = 1;
	locations[n].private1.items.cirass1 = 1;
	locations[n].private1.items.cirass5 = 1;
	
	// сундук Каппера наверху тюрьмы
	locations[n].private2.key = "key_capper";
	locations[n].private2.money = 15250;
	locations[n].private2.items.gold_dublon = 15;
	locations[n].private2.items.potion1 = 5;
	locations[n].private2.items.potion2 = 3;
	locations[n].private2.items.potion3 = 2;
	locations[n].private2.items.potionrum = 10;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Галеон Веласко  VelascoShipInside1
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "VelascoShipInside1";
	locations[n].id.label = "VelascoShipInside1 cabin";
	locations[n].filespath.models = "locations\LostShipsCityInsides\VelascoShipInside1";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LostShipsCity";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	locations[n].islandId = "LostShipsCity";
	locations[n].lsc_inside = "rivados"; // внутренний корабль кланов
	//Models
	//Always	
	Locations[n].models.always.inside = "VelascoShipInside1";	
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.seabed = "VelascoShipInside1_sb";
	Locations[n].models.always.outdoor = "VelascoShipInside1_outdoor";		
	Locations[n].models.always.reflect = "VelascoShipInside1_reflect";
	Locations[n].models.always.reflect.level = 65531;
	Locations[n].models.always.reflect.sea_reflection = 1;	
	Locations[n].models.always.reflTrum = "VelascoShipInside1_refl_trum";
	Locations[n].models.always.reflTrum.level = 65539;
	Locations[n].models.always.reflTrum.sea_reflection = 1;
	Locations[n].models.always.windows = "VelascoShipInside1_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65540;	
	Locations[n].models.always.sails = "VelascoShipInside1_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65534;	
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;	
	Locations[n].models.always.plan2 = "Plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65532;	
	Locations[n].models.always.locators = "VelascoShipInside1_locators";	
	Locations[n].models.always.grassPatch = "VelascoShipInside1_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";					
	//Day
	locations[n].models.day.charactersPatch = "VelascoShipInside1_patch_day";
	locations[n].models.day.fonarday = "VelascoShipInside1_fd";	
	//Night
	locations[n].models.night.charactersPatch = "VelascoShipInside1_patch_day";	
	Locations[n].models.night.fonarnight = "VelascoShipInside1_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload68";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "LostShipsCity_town";
	locations[n].reload.l2.emerge = "reload66";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "LSC Town";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "LostShipsCity_town";
	locations[n].reload.l3.emerge = "reload67";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "LSC Town";

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "LostShipsCity_town";
	locations[n].reload.l4.emerge = "reload69";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "LSC Town";

	locations[n].locators_radius.item.item1 = 1.1;

	//ключи для сундуков и предметы внутри
	locations[n].private1.key = "key1";
	locations[n].private1.skel = true;
	locations[n].private1.items.potion1 = 25;
	locations[n].private1.items.potion2 = 10;
	locations[n].private1.items.potion3 = 5;
	locations[n].private1.items.potion4 = 3;
	locations[n].private1.items.potion5 = 20;
	locations[n].private1.items.GunCap_colt = 3;
	locations[n].private1.items.mineral23 = 22;

	locations[n].private2.key = "key2"; // содержит платину
	locations[n].private2.skel = true;
	locations[n].private2.items.jewelry5 = 100;
	locations[n].private2.items.jewelry2 = 20;
	locations[n].private2.items.jewelry6 = 150;
	locations[n].private2.items.jewelry10 = 5; // 4 Pt

	locations[n].private3.key = "key3"; // у входа
	locations[n].private3.skel = true;
	locations[n].private3.money = 90000;
	locations[n].private3.items.gold_dublon = 100;
	locations[n].private3.items.chest = 5;
	locations[n].private3.items.berserker_potion = 1;
	locations[n].private3.items.incas_collection = 3;

	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Квестовая корабельная палуба корабля внешнего кольца LSC
	//////////////////////////////////////////////////////////////////////////////////////////////
	
	Locations[n].id = "ExternalRingDeck";
	Locations[n].id.label = "Boarding deck";
	Locations[n].image = "loading\Quarter_" + rand(1) + ".tga";
	//Sound
	Locations[n].type = "LostShipsCity";
	Locations[n].lockCamAngle = 0.4;
	//Models	
	//Always
	Locations[n].filespath.models = "locations\decks\deck03";
	Locations[n].models.always.deck03 = "deck03";
	Locations[n].models.always.locators = "deck03_locators";

	Locations[n].models.always.plan3 = "LostShipsCity_plan3";
	Locations[n].models.always.plan3.tech = "LocationWindows";
	Locations[n].models.always.plan3.level = 65532;
	
	Locations[n].models.always.alpha = "deck03_alpha";
	
	//Day
	locations[n].models.day.charactersPatch = "deck03_patch";
	Locations[n].models.day.fonar = "deck03_fonars";	
	//Night
	locations[n].models.night.charactersPatch = "deck03_patch";
	Locations[n].models.night.fonar = "deck03_fonars";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true"; 
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "ExternalRingInside";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "My_Deck";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "ExternalRingCabin1";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "cabine";
	
	locations[n].private1.items.grenade = 10;
	locations[n].private1.items.powder_pellet = 12;
	locations[n].private1.items.grapeshot = 17;
	locations[n].private1.items.GunPowder = 25;
	
	locations[n].private2.items.blade_12 = 1;
	locations[n].private2.items.mushket1 = 1;
	locations[n].private2.items.cartridge = 25;
	
	locations[n].private3.items.potion5 = 50;
	
	locations[n].private4.items.potion2 = 8;
	
	locations[n].private5.items.cannabis1 = 15;
	locations[n].private5.items.cannabis2 = 8;
	locations[n].private5.items.cannabis3 = 13;
	locations[n].private5.items.cannabis4 = 7;
	locations[n].private5.items.cannabis5 = 21;
	locations[n].private5.items.cannabis6 = 18;
	
	locations[n].locators_radius.item.item1 = 1.3;
	
	n = n + 1;

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Квестовая локация корабля внешнего кольца - клон инсайда Плуто
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "ExternalRingInside";
	locations[n].id.label = "";
	locations[n].filespath.models = "locations\LostShipsCityInsides\PlutoStoreSmall";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "LostShipsCity";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	locations[n].islandId = "LostShipsCity";
	//Models
	//Always	
	Locations[n].models.always.inside = "PlutoStoreSmall";	
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.seabed = "PlutoStoreSmall_sb";
	Locations[n].models.always.outdoor = "PlutoStoreSmall_outdoor";		
	Locations[n].models.always.reflect = "PlutoStoreSmall_reflect";
	Locations[n].models.always.reflect.level = 65531;
	Locations[n].models.always.reflect.sea_reflection = 1;	
	Locations[n].models.always.windows = "PlutoStoreSmall_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;	
	Locations[n].models.always.sails = "PlutoStoreSmall_sails";
	Locations[n].models.always.sails.tech = "LocationWindows";
	Locations[n].models.always.sails.level = 65534;	
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;	
	Locations[n].models.always.plan2 = "Plan2";
	Locations[n].models.always.plan2.tech = "LocationWindows";
	Locations[n].models.always.plan2.level = 65532;	
	Locations[n].models.always.locators = "ExternalRingInside_locators";	
	Locations[n].models.always.grassPatch = "PlutoStoreSmall_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU1.tga.tx";					
	//Day
	locations[n].models.day.charactersPatch = "PlutoStoreSmall_patch_day";
	locations[n].models.day.fonarday = "PlutoStoreSmall_fd";	
	//Night
	locations[n].models.night.charactersPatch = "PlutoStoreSmall_patch_day";	
	Locations[n].models.night.fonarnight = "PlutoStoreSmall_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload_ring";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "ExternalRingDeck";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "LSC Town";

	// схроны
	locations[n].private1.items.Mineral1 = 3;
	locations[n].private1.items.Mineral3 = 10;
	locations[n].private1.items.Mineral5 = 1;

	locations[n].private2.items.Mineral11 = 1;
	locations[n].private2.items.Mineral21 = 1;
	locations[n].private2.items.Mineral19 = 2;
	
	locations[n].private3.items.Mineral26 = 1;
	locations[n].private3.items.Mineral18 = 1;
	
	locations[n].private4.items.potionrum = 40; // 40 бутылок рома
	
	locations[n].private5.items.Mineral35 = 1;
	
	locations[n].private6.items.potionwine = 20; // 20 бутылок вина
	
	locations[n].private7.items.rat_poison = 1;
	
	locations[n].private9.items.cirass1 = 1;
	
	locations[n].private10.items.jewelry15 = 3;
	locations[n].private10.items.jewelry19 = 1;
	
	locations[n].private11.items.jewelry1 = 2;
	
	n = n + 1;
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Квестовая каюта на корабле внешнего кольца - каюта ЛГ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
  	Locations[n].id = "ExternalRingCabin1"; 
    locations[n].id.label = "cabine";
	locations[n].filespath.models = "locations\inside\cabinFDM\";
	locations[n].image = "loading\Capdeck_" + rand(1) + ".tga";
	//Sound
	locations[n].type = "LSC_inside";
	locations[n].islandId = "LostShipsCity";
	//Models
	//Always
	locations[n].models.always.cabinFDM = "cabinFDM";
	locations[n].models.always.cabinFDM.level = 65538;
	locations[n].models.always.locators = "ExternalRingCabin_locators";

	locations[n].models.always.window = "cabinFDM_window";
	Locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	//Day
	locations[n].models.day.charactersPatch = "cabinFDM_patch";
	//Night
	locations[n].models.night.charactersPatch = "cabinFDM_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	
    Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "ExternalRingDeck";
	Locations[n].reload.l1.emerge = "reload2";
	Locations[n].reload.l1.label = "Boarding deck";
	locations[n].environment.weather.rain = false;
	
	locations[n].private1.money = 144;
	locations[n].private1.items.map_maine_2 = 1;
	
	locations[n].private2.items.jewelry49 = 1;
	locations[n].private2.items.jewelry50 = 1;
	locations[n].private2.items.indian_5 = 1;
	locations[n].private2.items.potion7 = 1;
	
	locations[n].private3.items.recipe_totem_08 = 1;
	locations[n].private3.items.totem_08 = 1;
	locations[n].private3.items.potion7 = 2;
	locations[n].private3.items.potion2 = 1;
	locations[n].private3.items.cannabis7 = 1;
	
	locations[n].private4.items.pistol6 = 1;
	locations[n].private4.items.bullet = 10;
	
	locations[n].locators_radius.item.item1 = 1.0;
	
	n = n + 1;
	
	return n;
}