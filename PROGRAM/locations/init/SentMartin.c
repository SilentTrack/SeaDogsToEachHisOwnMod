
int LocationInitSentMartin(int n)
{
	
	
	
	
	locations[n].id = "Marigo_town";
	locations[n].id.label = "Street";
	locations[n].worldmap = "SentMartin";
	
	locations[n].townsack = "Marigo";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	
	locations[n].filespath.models = "locations\Town_StMartin\Town\";
	locations[n].image = "loading\Town.tga";
	locations[n].citizens = true;
	locations[n].soldiers = true;
	locations[n].carrier = true;
	
	locations[n].questSeekCap = 5; 
	
	locations[n].type = "town";
	LAi_LocationFantomsGen(&locations[n], true);
	locations[n].houseEnc = true; 
	
	
	locations[n].models.always.town = "StMartin";
	locations[n].models.always.town.sea_reflection = 1;
	locations[n].models.always.L1 = "StMartin_signsA";
	locations[n].models.always.locators = "StMartin_locators";
	locations[n].models.always.seabed = "StMartin_sb";
	locations[n].models.always.grassPatch = "StMartin_grass";
	
	locations[n].models.always.plan = "plan1";
	locations[n].models.always.plan.level = 9;

	
	locations[n].models.always.MillFan = "MillFan";
	Locations[n].models.always.MillFan.locator.group = "WindMill";
	Locations[n].models.always.MillFan.locator.name ="Fan";	
	Locations[n].models.always.MillFan.rotate.x = 0.0;
	Locations[n].models.always.MillFan.rotate.y = 0.0;
	Locations[n].models.always.MillFan.rotate.z = 0.1;

	
	locations[n].models.day.fonar = "StMartin_fd";
	locations[n].models.day.charactersPatch = "StMartin_patch_day";
	locations[n].models.day.rinok = "StMartin_rinok";
	
	locations[n].models.night.fonar = "StMartin_fn";
	locations[n].models.night.charactersPatch = "StMartin_patch_night";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	

    
	locations[n].reload.l0.name = "reload1";
	locations[n].reload.l0.go = "SentMartin";
	locations[n].reload.l0.emerge = "reload_1";
	locations[n].reload.l0.autoreload = "0";
	locations[n].reload.l0.label = "Sea";
	locations[n].locators_radius.reload.reload1 = 0.2;

	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "SentMartin";
	locations[n].reload.l1.emerge = "reload_1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Sea";
	locations[n].locators_radius.reload.reload1_back = 1.8;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Marigo_townhall";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Residence";
	locations[n].reload.l3.close_for_night = 1;

	locations[n].reload.lR1.name = "reloadR1";
	locations[n].reload.lR1.go = "Marigo_TownhallRoom";
	locations[n].reload.lR1.emerge = "reload2";
	locations[n].reload.lR1.autoreload = "0";
	locations[n].reload.lR1.label = "Residence";
	locations[n].reload.lR1.close_for_night = 1;

	locations[n].reload.l4.name = "reload4_back";
	locations[n].reload.l4.go = "Marigo_tavern";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Tavern";

	locations[n].reload.l5.name = "reload5_back";
	locations[n].reload.l5.go = "Marigo_shipyard";
	locations[n].reload.l5.emerge = "reload1";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "Shipyard";
	locations[n].reload.l5.close_for_night = 1;

	locations[n].reload.l6.name = "reload6_back";
	locations[n].reload.l6.go = "Marigo_store";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "Shipyard";
	locations[n].reload.l6.close_for_night = 1;

	locations[n].reload.l7.name = "reload7_back";
	locations[n].reload.l7.go = "Marigo_church";
	locations[n].reload.l7.emerge = "reload1";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "Church";
	

	locations[n].reload.l8.name = "reload8_back";
	locations[n].reload.l8.go = "Marigo_bank";
	locations[n].reload.l8.emerge = "reload1";
	locations[n].reload.l8.autoreload = "0";
	locations[n].reload.l8.label = "Usurer House";
	locations[n].reload.l8.close_for_night = 1;

	locations[n].reload.l9.name = "reload9_back";
	locations[n].reload.l9.go = "Marigo_brothel";
	locations[n].reload.l9.emerge = "reload1";
	locations[n].reload.l9.autoreload = "0";
	locations[n].reload.l9.label = "Brothel";
	
 	locations[n].reload.l91.name = "reload91";
	locations[n].reload.l91.go = "Marigo_SecBrRoom";
	locations[n].reload.l91.emerge = "reload2";
	locations[n].reload.l91.autoreload = "0";
	locations[n].reload.l91.label = "Brothel";

	locations[n].reload.l10.name = "reload10_back";
	locations[n].reload.l10.go = "Marigo_PortOffice";
	locations[n].reload.l10.emerge = "reload1";
	locations[n].reload.l10.autoreload = "0";
	locations[n].reload.l10.label = "PortOffice";
	locations[n].reload.l10.close_for_night = 1;

	locations[n].reload.gate.name = "gate_back";
	locations[n].reload.gate.go = "Marigo_ExitTown";
	locations[n].reload.gate.emerge = "reload3";
	locations[n].reload.gate.autoreload = "0";
	locations[n].reload.gate.label = "ExitTown";
	
	locations[n].reload.jail.name = "reload_jail";
	locations[n].reload.jail.go = "Marigo_prison";
	locations[n].reload.jail.emerge = "reload1";
	locations[n].reload.jail.autoreload = "0";
	locations[n].reload.jail.label = "Prison";

    
	locations[n].reload.l11.name = "houseF1";
	locations[n].reload.l11.go = "Marigo_houseF1";
	locations[n].reload.l11.emerge = "reload1";
	locations[n].reload.l11.autoreload = "0";
	locations[n].reload.l11.label = "House";
	
	locations[n].reload.l12.name = "houseSp2";
	locations[n].reload.l12.go = "Marigo_houseSp2";
	locations[n].reload.l12.emerge = "reload1";
	locations[n].reload.l12.autoreload = "0";
	locations[n].reload.l12.label = "House";
	locations[n].reload.l12.disable = true; 
    
    
	locations[n].reload.l20.name = "houseSp1";
	locations[n].reload.l20.go = "CommonDoubleflourHouse_1";
	locations[n].reload.l20.emerge = "reload1";
	locations[n].reload.l20.autoreload = "0";
	locations[n].reload.l20.label = "House";

	locations[n].reload.l21.name = "houseS1";
	locations[n].reload.l21.go = "CommonPirateHouse";
	locations[n].reload.l21.emerge = "reload1";
	locations[n].reload.l21.autoreload = "0";
	locations[n].reload.l21.label = "House";
    
	 
    
	locations[n].reload.l23.name = "houseH1";
	locations[n].reload.l23.go = "CommonRoom_MH9";
	locations[n].reload.l23.emerge = "reload1";
	locations[n].reload.l23.autoreload = "0";
	locations[n].reload.l23.label = "House";

	locations[n].reload.l24.name = "houseS2";
	locations[n].reload.l24.go = "CommonFlamHouse";
	locations[n].reload.l24.emerge = "reload1";
	locations[n].reload.l24.autoreload = "0";
	locations[n].reload.l24.label = "House";
	
	locations[n].reload.l25.name = "houseH2";
	locations[n].reload.l25.go = "CommonPirateResidence";
	locations[n].reload.l25.emerge = "reload1";
	locations[n].reload.l25.autoreload = "0";
	locations[n].reload.l25.label = "House";
	n = n + 1;

	
	
	
	locations[n].id = "Marigo_tavern";
	locations[n].id.label = "Tavern";
	locations[n].filespath.models = "locations\inside\tavern03\";
	locations[n].image = "loading\inside\tavern.tga";
	locations[n].habitues = 1;
	
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "tavern";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	
	
	locations[n].models.always.tavern = "tavern03";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.locators = "tavern03_locators";
	locations[n].models.always.window = "tavern03_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	locations[n].models.day.charactersPatch = "tavern03_patch";
	
	locations[n].models.night.charactersPatch = "tavern03_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Marigo_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; 
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	
	
	
	locations[n].id = "Marigo_tavern_upstairs";
	locations[n].id.label = "Marigo_tavern_upstairs";
	locations[n].filespath.models = "locations\inside\Tavern_room";
	locations[n].image = "loading\inside\tavern.tga";
	
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
	locations[n].islandId = "SentMartin";
	
	
	locations[n].models.always.locators = "Tavern_room_locators";
	locations[n].models.always.tavern = "Tavern_room";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "tavern_room_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	locations[n].models.day.charactersPatch = "Tavern_room_patch";
	
	locations[n].models.night.charactersPatch = "Tavern_room_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_tavern";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

 	
	
	
	locations[n].id = "Marigo_store";
	locations[n].id.label = "Store";
	locations[n].filespath.models = "locations\inside\Store04\";
	locations[n].image = "loading\inside\shop.tga";
	
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "shop";
	locations[n].fastreload = "Marigo";
	locations[n].islandId = "SentMartin";
	
	
	locations[n].models.always.locators = "Store04_locators";
	locations[n].models.always.store = "Store04";
	locations[n].models.always.window = "store04_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	
	locations[n].models.day.charactersPatch = "Store04_patch";
	
	locations[n].models.night.charactersPatch = "Store04_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "reload6";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.camdetector.camera1 = 5;
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	
	
	
	locations[n].id = "Marigo_bank";
	locations[n].id.label = "Usurer House";
	locations[n].filespath.models = "locations\inside\Bank01\";
	locations[n].image = "loading\inside\bank.tga";
	
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "shop";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	
	
	locations[n].models.always.locators = "Bank01_locators";
	locations[n].models.always.store = "Bank01";
	locations[n].models.always.store.level = 65538;
	locations[n].models.always.window = "Bank01_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	locations[n].models.day.charactersPatch = "Bank01_patch";
	
	locations[n].models.night.charactersPatch = "Bank01_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "reload8";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonResidence_5";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	
	
	
	locations[n].id = "Marigo_Shipyard";
	locations[n].id.label = "Shipyard";
	locations[n].filespath.models = "locations\inside\Shipyard01\";
	locations[n].image = "loading\inside\shipyard.tga";
	
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "shipyard";
	locations[n].fastreload = "Marigo";
	locations[n].islandId = "SentMartin";
	
	
	locations[n].models.always.locators = "Shipyard01_locators";
	locations[n].models.always.shipyard = "Shipyard01";
	locations[n].models.always.shipyard.level = 65538;
	locations[n].models.always.window = "shipyard01_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	locations[n].models.day.charactersPatch = "Shipyard01_patch";
	
    locations[n].models.night.charactersPatch = "Shipyard01_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "reload5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonPackhouse_1";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	locations[n].locators_radius.item.item1 = 1.0;
	n = n + 1;

 	
	
	
	locations[n].id = "Marigo_townhall";
	locations[n].id.label = "Townhall";
	locations[n].filespath.models = "locations\inside\Residence02";
	locations[n].image = "loading\inside\residence.tga";
	
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "residence";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
 	
	locations[n].soldiers = true;
	LAi_LocationFantomsGen(&locations[n], true);
	
	
	locations[n].models.always.locators = "Residence02_locators";
	locations[n].models.always.l1 = "Residence02";
	locations[n].models.always.l1.level = 65538;
	locations[n].models.always.window = "residence02_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;	
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	locations[n].models.day.charactersPatch = "Residence02_patch";
	
	locations[n].models.night.charactersPatch = "Residence02_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Marigo_TownhallRoom";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "TownhallRoom";
	n = n + 1;

	
	locations[n].id = "Marigo_TownhallRoom"; 
	locations[n].id.label = "TownhallRoom";
	locations[n].image = "loading\inside\BigHouse01.tga";
	
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
	locations[n].islandId = "SentMartin";
	
	
	locations[n].filespath.models = "locations\inside\BigHouse01_2Door";
	locations[n].models.always.model = "BigHouse01_2Door";
	locations[n].models.always.model.level = 65538;
	locations[n].models.day.locators = "BigHouse01_2Door_locators";
	locations[n].models.night.locators = "BigHouse01_2Door_Nlocators";
	locations[n].models.always.window = "BigHouse01_2Door_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	locations[n].models.day.charactersPatch = "BigHouse01_2Door_patch";
	
	locations[n].models.night.charactersPatch = "BigHouse01_2Door_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_townhall";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Townhall";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Marigo_town";
	locations[n].reload.l2.emerge = "reloadR1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	n = n + 1;

	
	
	
	locations[n].id = "Marigo_Brothel";
	locations[n].id.label = "Brothel";
	locations[n].filespath.models = "locations\inside\Brothel\";
	locations[n].image = "loading\inside\brothell_hall.tga";
	
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	locations[n].brothel = true;
	
	
	locations[n].models.always.locators = "Brothel_locators";
	locations[n].models.always.store = "Brothel";
	locations[n].models.always.window = "brothel_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	
	locations[n].models.day.charactersPatch = "Brothel_patch";
	
	locations[n].models.night.charactersPatch = "Brothel_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "reload9";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Marigo_Brothel_room";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Brothel Room";
	locations[n].reload.l2.disable = 1;  

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Marigo_SecBrRoom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	
	
	
	locations[n].id = "Marigo_Brothel_room";
	locations[n].id.label = "Brothel Room";
	locations[n].filespath.models = "locations\inside\Brothel_room\";
	locations[n].image = "loading\inside\brothell_room.tga";
	
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
	locations[n].islandId = "SentMartin";
	
	
	locations[n].models.always.locators = "Brothel_room_locators";
	locations[n].models.always.store = "Brothel_room";
	locations[n].models.always.window = "Brothel_room_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	
	locations[n].models.day.charactersPatch = "Brothel_room_patch";
	
	locations[n].models.night.charactersPatch = "Brothel_room_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_brothel";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	locations[n].locators_radius.item.item1 = 1;
	n = n + 1;

	
	locations[n].id = "Marigo_SecBrRoom"; 
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\BigHouse03.tga";
 	
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	locations[n].brothel = true;
	
	
	locations[n].filespath.models = "locations\inside\BigHouse03\";
	locations[n].models.always.house = "BigHouse03";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "BigHouse03_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	locations[n].models.day.charactersPatch = "BigHouse03_patch";
	locations[n].models.day.locators = "BigHouse03_locators";
	
	locations[n].models.night.charactersPatch = "BigHouse03_patch";
	locations[n].models.night.locators = "BigHouse03_Nlocators";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_Brothel";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Marigo_town";
	locations[n].reload.l2.emerge = "reload91";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	
	
	
	locations[n].id = "Marigo_church";
	locations[n].id.label = "Church";
	locations[n].filespath.models = "locations\inside\Church01";
	locations[n].image = "loading\inside\church.tga";
	
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "church";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	
	
	locations[n].models.always.locators = "Church01_locators";
	locations[n].models.always.tavern = "Church01";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "Church01_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	locations[n].models.day.charactersPatch = "Church01_patch";
	
	locations[n].models.night.charactersPatch = "Church01_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "reload7";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	
	
	
	locations[n].id = "Marigo_PortOffice";
	locations[n].id.label = "PortOffice";
	locations[n].image = "loading\inside\portoffice.tga";
	
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	
	
	locations[n].filespath.models = "locations\inside\PortOffice";
	locations[n].models.always.housePortOffice = "PortOffice";
	locations[n].models.always.housePortOffice.level = 65538;
	locations[n].models.always.locators = "PortOffice_locators";

	Locations[n].models.always.PortOffice = "PortOffice_windows";
	Locations[n].models.always.PortOffice.tech = "LocationWindows";
	locations[n].models.always.PortOffice.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	locations[n].models.day.charactersPatch = "PortOffice_patch";
	
	locations[n].models.night.charactersPatch = "PortOffice_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "reload10";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	
	
	locations[n].id = "Marigo_houseF1";
	locations[n].filespath.models = "locations\inside\StoneHouse";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\stonehouse.tga";
	
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	
	
	locations[n].models.always.tavern = "StoneHouse";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "StoneHouse_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.day.locators = "StoneHouse_locators";
	locations[n].models.night.locators = "StoneHouse_Nlocators";

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	locations[n].models.day.charactersPatch = "StoneHouse_patch";
	
	locations[n].models.night.charactersPatch = "StoneHouse_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "houseF1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Marigo_RoomHouseF1";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	n = n + 1;

	
	
	locations[n].id = "Marigo_RoomHouseF1";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	
	
	locations[n].filespath.models = "locations\inside\mediumhouse05";
	locations[n].models.always.mediumhouse05 = "mediumhouse05";
	locations[n].models.always.mediumhouse05.level = 65538;
	locations[n].models.day.locators = "mediumhouse05_locators";
	locations[n].models.night.locators = "mediumhouse05_Nlocators";

	Locations[n].models.always.mediumhouse05windows = "mediumhouse05_windows";
	Locations[n].models.always.mediumhouse05windows.tech = "LocationWindows";
	locations[n].models.always.mediumhouse05windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	Locations[n].models.day.mediumhouse05rand= "mediumhouse05_rand";
	locations[n].models.day.charactersPatch = "mediumhouse05_patch";
	
	locations[n].models.night.charactersPatch = "mediumhouse05_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_houseF1";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "House";
	n = n + 1;
	
	
	
	
	locations[n].id = "Marigo_houseSp2";
	locations[n].filespath.models = "locations\inside\StoneHouse";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\stonehouse.tga";
	
	locations[n].townsack = "Marigo";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Marigo";
 	locations[n].islandId = "SentMartin";
	
	
	locations[n].models.always.tavern = "StoneHouse";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "StoneHouse_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.day.locators = "StoneHouse_locators";
	locations[n].models.night.locators = "StoneHouse_Nlocators";

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	locations[n].models.day.charactersPatch = "StoneHouse_patch";
	
	locations[n].models.night.charactersPatch = "StoneHouse_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "houseSp2"; 
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonRoom_MH6";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	
	locations[n].box1.QuestClosed = true;
	n = n + 1;
	
	
	Locations[n].id = "Marigo_prison";
	locations[n].id.label = "Prison";
	Locations[n].image = "loading\inside\prison.tga";
	locations[n].townsack = "Marigo";
    locations[n].parent_colony = "Marigo";
 	locations[n].fastreload = "Marigo";
	locations[n].islandId = "SentMartin";
	
	locations[n].type = "jail";
	
	
	locations[n].filespath.models = "locations\inside\prison1";
	locations[n].models.always.prison1 = "prison1";
	locations[n].models.always.lamps = "prison1_lamps";
	locations[n].models.always.locators = "prison1_locators";	
	locations[n].models.always.chest = "chest1";
	
	locations[n].models.day.charactersPatch = "prison1_patch";
	
	locations[n].models.night.charactersPatch = "prison1_patch";
	
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
    
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Marigo_town";
	Locations[n].reload.l1.emerge = "reload_jail";
	Locations[n].reload.l1.autoreload = "0";
	
	locations[n].locators_radius.box.box1 = 0.8;
	locations[n].box1.QuestClosed = true;
	n = n + 1;

	
	
	
	locations[n].id = "Marigo_ExitTown";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\Gate" + rand(1) + ".tga";
	
	locations[n].townsack = "Marigo";
	
	locations[n].type = "jungle";
	locations[n].islandId = "SentMartin";
	
	
	locations[n].filespath.models = "locations\Outside\Jungles\TownExitT";
	Locations[n].models.always.townExit = "townExitT";
	Locations[n].models.always.townWalls = "townExitT_stone";
	
	Locations[n].models.always.locators = "townExitT_locators";
		
	Locations[n].models.always.grassPatch = "townExitT_grass";
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
	
	locations[n].models.day.charactersPatch = "townExitT_patch";
	locations[n].models.day.fonars = "townExitT_fd";
	
	locations[n].models.night.charactersPatch = "townExitT_patch";
	locations[n].models.night.fonars = "townExitT_fn";	
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload3";
	locations[n].reload.l1.go = "Marigo_town";
	locations[n].reload.l1.emerge = "gate_back";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Marigo";

	locations[n].reload.l2.name = "reload1_back";
	locations[n].reload.l2.go = "Marigo_jungle_01";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l3.name = "reload2_back";
	locations[n].reload.l3.go = "Marigo_fort";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Marigo Fort";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	
	
	
	locations[n].id = "Marigo_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	
	locations[n].type = "jungle";
	locations[n].islandId = "SentMartin";
	
	
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
	locations[n].reload.l1.go = "Marigo_Cave";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Cave";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Marigo_jungle_01";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	
	
	
	locations[n].id = "Marigo_Cave";
	locations[n].id.label = "Cave";
	locations[n].image = "loading\inside\cave.tga";
	
	locations[n].type = "cave";
 	locations[n].islandId = "SentMartin";
	
	
	locations[n].filespath.models = "locations\inside\cavernMedium2";
	locations[n].models.always.cavernMedium2 = "cavernMedium2";
	locations[n].models.always.lamps = "cavernMedium2_lamps";	
	locations[n].models.always.locators = "cavernMedium2_locators";	

	locations[n].locators_radius.item.duhi1 = 0.0;
 	
	
	locations[n].models.day.charactersPatch = "cavernMedium2_patch";
	
	locations[n].models.night.charactersPatch = "cavernMedium2_patch";
	
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_CaveEntrance";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].locators_radius.reload.reload1 = 2.0;

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Marigo_Jungle_02";
	locations[n].reload.l2.emerge = "reloadW";
	locations[n].locators_radius.reload.reload2 = 2.0;
	locations[n].locators_radius.item.berglar1 = 3.5;
	locations[n].locators_radius.item.CheckReload1 = 3.5;
	n = n + 1;

	
	
	
    locations[n].id = "Marigo_jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
 	
	locations[n].type = "jungle";
	locations[n].islandId = "SentMartin";
	
	
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
	
	locations[n].models.day.charactersPatch = "jungle4_patch";
	
	locations[n].models.night.charactersPatch = "jungle4_patch";	
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_ExitTown";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Marigo_jungle_02";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Marigo_CaveEntrance";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	
	
	
	locations[n].id = "Marigo_Jungle_02";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	
	locations[n].type = "jungle";
	locations[n].islandId = "SentMartin";
	
	
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

	locations[n].models.always.well_small = "well_big";
	Locations[n].models.always.well_small.locator.group = "reload";
	Locations[n].models.always.well_small.locator.name ="reloadW_back";	
	Locations[n].models.always.well_small.tech = "DLightModel";
	
	locations[n].models.day.charactersPatch = "jungle2_pSentMartin02";
	
	locations[n].models.night.charactersPatch = "jungle2_pSentMartin02";	
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Shore41";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Shore41";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore40";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore40";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Marigo_jungle_01";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2;

	locations[n].reload.l4.name = "reloadW_back";
	locations[n].reload.l4.go = "Marigo_Cave";
	locations[n].reload.l4.emerge = "reload2";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Jungle";
	locations[n].locators_radius.reload.reloadW_back = 2.3;
	n = n + 1;

	
	
	
	locations[n].id = "Shore41";
	locations[n].id.label = "Shore41";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "Shore41";
	
	locations[n].type = "seashore";
	locations[n].islandId = "SentMartin";
	
	
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
	
	locations[n].models.day.charactersPatch = "shore07_patch";
	
	locations[n].models.night.charactersPatch = "shore07_patch";		
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_Jungle_02";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "SentMartin";
	locations[n].reload.l2.emerge = "reload_2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	
	
	
	locations[n].id = "Shore40";
	locations[n].id.label = "Shore40";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "Shore40";
	
	locations[n].type = "seashore";
	locations[n].islandId = "SentMartin";
	
	
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
	
	locations[n].models.day.charactersPatch = "shore08_patch";
	
	locations[n].models.night.charactersPatch = "shore08_patch";		
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Marigo_Jungle_02";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "SentMartin";
	locations[n].reload.l2.emerge = "reload_3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	return n;
}

