
int LocationInitIslaDeVieques(int n)
{
	
	
	
	
	
	
	locations[n].id = "Shore74";
	locations[n].id.label = "Shore74";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "IslaDeVieques";
	
	locations[n].type = "questisland";
	locations[n].islandId = "IslaDeVieques";
	locations[n].DisableEncounters = true;
	locations[n].Chestgennot = true; 
	
	
	locations[n].filespath.models = "locations\Outside\Shores\Shore13";
	Locations[n].models.always.shore13 = "shore13";
	locations[n].models.always.shore13.sea_reflection = 1;
	Locations[n].models.always.shore13seabed = "shore13_seabed";
	Locations[n].models.always.locators = "shore13_locators";
	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	
	Locations[n].models.always.grassPatch = "shore13_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	
	locations[n].models.day.charactersPatch = "shore13_patch";
	
	locations[n].models.night.charactersPatch = "shore13_patch";		
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";	
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "IslaDeVieques_Jungle_01";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 8.0;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "IslaDeVieques";
	locations[n].reload.l2.emerge = "reload_2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	
	n = n + 1;

	
	
	
	locations[n].id = "IslaDeVieques_Jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	
	locations[n].type = "questisland";
	locations[n].islandId = "IslaDeVieques";
	locations[n].DisableEncounters = true;
	
	
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
	
	locations[n].models.day.charactersPatch = "jungle6_patch";
	
	locations[n].models.night.charactersPatch = "jungle6_patch";	
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "IslaDeVieques_CaveEntrance";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore74";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore74";
    locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "IslaDeVieques_HouseEntrance";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;

	
	
	
	locations[n].id = "IslaDeVieques_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	
	locations[n].type = "questisland";
	locations[n].islandId = "IslaDeVieques";
	locations[n].DisableEncounters = true;
	
	
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
	
	locations[n].models.day.charactersPatch = "caveEnt1_patch";
	
	locations[n].models.night.charactersPatch = "caveEnt1_patch";	
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "IslaDeVieques_Grot";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Grot";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "IslaDeVieques_Jungle_01";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	
	
	
	locations[n].id = "IslaDeVieques_Grot";
	locations[n].id.label = "Grot";
    locations[n].image = "loading\inside\cave.tga";
	
	locations[n].type = "Cave";
	locations[n].islandId = "IslaDeVieques";
	locations[n].DisableEncounters = true;
	
	
	locations[n].filespath.models = "locations\inside\grotto2";
	locations[n].models.always.grotto2 = "grotto2";
	locations[n].models.always.grotto2.sea_reflection = 1;
	locations[n].models.always.grotto2alpha = "grotto2_alpha";
	Locations[n].models.always.grotto2alpha.tech = "LocationWindows";	
	locations[n].models.always.grotto2alpha.level = 65532;	
	locations[n].models.always.locators = "grotto2_questlocators";	
	
	locations[n].models.day.charactersPatch = "grotto2_patch";
	
	locations[n].models.night.charactersPatch = "grotto2_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "IslaDeVieques_CaveEntrance";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Cave entrance";
	locations[n].locators_radius.reload.reload1_back = 2;
	n = n + 1;

	
	
	
	locations[n].id = "IslaDeVieques_HouseEntrance";
	locations[n].id.label = "jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	
	locations[n].type = "questisland";
	locations[n].islandId = "IslaDeVieques";
	locations[n].DisableEncounters = true;
	
	
	Locations[n].filespath.models = "locations\Outside\ArchyHouse";
    Locations[n].models.always.house = "RHouse";
    Locations[n].models.always.grassPatch = "rhouse_g";
    Locations[n].models.always.l1 = "rhouse_b01";
    Locations[n].models.always.l1.level = 9;
    Locations[n].models.always.l1.tech = "LocationModelBlend";
    Locations[n].models.always.l2 = "rhouse_b02";
    Locations[n].models.always.l2.level = 8;
    Locations[n].models.always.l2.tech = "LocationModelBlend";
    Locations[n].models.always.l3 = "rhouse_b03";
    Locations[n].models.always.l3.level = 7;
    Locations[n].models.always.l3.tech = "LocationModelBlend";
	Locations[n].models.always.l4 = "rhouse_b04";
    Locations[n].models.always.l3.level = 7;
    Locations[n].models.always.l4.tech = "LocationModelBlend";
	Locations[n].models.always.locators = "rhouse_l";
	
	Locations[n].models.always.grassPatch = "rhouse_g";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
    
    Locations[n].models.day.charactersPatch = "rhouse_p";
    
    Locations[n].models.night.charactersPatch = "rhouse_p";
    
    Locations[n].environment.weather = "true";
    Locations[n].environment.sea = "false";	
	
	locations[n].reload.l1.name = "reload2_back";
	locations[n].reload.l1.go = "IslaDeVieques_House";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "House";
	locations[n].locators_radius.reload.reload2 = 1.3;

	locations[n].reload.l2.name = "reload1_back";
	locations[n].reload.l2.go = "IslaDeVieques_Jungle_01";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;
	n = n + 1;

	
	
	
	locations[n].id = "IslaDeVieques_House";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	locations[n].islandId = "IslaDeVieques";
	
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "House";
	
	
	locations[n].filespath.models = "locations\inside\SmallHouse_inside\";
	locations[n].models.always.SmallHouse = "SmallHouse_inside";
	
	Locations[n].models.always.windows = "SmallHouse_inside_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back2";
	
	locations[n].models.day.charactersPatch = "SmallHouse_inside_patch";
	locations[n].models.day.locators = "SmallHouse_inside_ld";
	
	locations[n].models.night.charactersPatch = "SmallHouse_inside_patch";
	locations[n].models.night.locators = "SmallHouse_inside_ln";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	Locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "IslaDeVieques_HouseEntrance";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "jungle";
	n = n + 1;

	return n;
}
