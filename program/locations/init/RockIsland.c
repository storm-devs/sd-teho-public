
int LocationInitRockIsland(int n)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Северные рифы
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Риф67
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore67";
	locations[n].id.label = "Shore67";
	locations[n].image = "loading\RockIsland.tga";
	locations[n].worldmap = "RockIsland";
	locations[n].parent_colony = "RockIsland";
	//Sound
	locations[n].type = "reef";
	locations[n].islandId = "RockIsland";
	locations[n].onUninhabitedIsland = true;
	locations[n].DisableEncounters = true;
	locations[n].questflower = 1;
	locations[n].Chestgennot = true; // не генерить сундуки
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\MountainPathDMChest";
	Locations[n].models.always.shore = "MountainPathDMChest";
	locations[n].models.always.shore.sea_reflection = 1;
	Locations[n].models.always.seabed = "MountainPathDMChest_sb";
	Locations[n].models.always.locators = "MountainPathDMChest_locators"; 
		
	Locations[n].models.always.grassPatch = "MountainPath_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	
	Locations[n].models.always.Waterfall1 = "WaterFall1";
	Locations[n].models.always.Waterfall1.uvslide.v0 = 0.6;
    Locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall1.level = 50;
	
	Locations[n].models.always.Waterfall2 = "WaterFall2";
	Locations[n].models.always.Waterfall2.uvslide.v0 = 0.3;
    Locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall2.level = 49;
	
	//Day
	locations[n].models.day.charactersPatch = "MountainPathDMChest_patch_day";
	//Night
	locations[n].models.night.charactersPatch = "MountainPathDMChest_patch_day";		
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";		
	//Reload map
	Locations[n].reload.l1.name = "reload1_back";
    Locations[n].reload.l1.go = "RockIsland";
    Locations[n].reload.l1.emerge = "reload_1";
    Locations[n].reload.l1.autoreload = "0";
    Locations[n].reload.l1.label = "Sea";
	Locations[n].locators_radius.reload.reload1 = 2.5;
	
	Locations[n].locators_radius.item.splash1 = 1.0;
	Locations[n].locators_radius.item.splash2 = 1.0;
	Locations[n].locators_radius.item.splash3 = 1.0;
	Locations[n].locators_radius.item.splash4 = 1.0;
	Locations[n].locators_radius.item.splash5 = 1.0;

	n = n + 1;

	return n;
}
