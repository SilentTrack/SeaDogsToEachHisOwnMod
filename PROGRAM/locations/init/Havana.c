
int LocationInitHavana(int n)
{
	
	
	
	
	locations[n].id = "Havana_town";
	locations[n].id.label = "Street";
	locations[n].worldmap = "Havana";
	
	locations[n].townsack = "Havana";
	locations[n].fastreload = "Havana";
 	locations[n].islandId = "Cuba";
	
	locations[n].filespath.models = "locations\Town_Havana\Town\";
	locations[n].image = "loading\Town.tga";
	locations[n].citizens = true;
	locations[n].soldiers = true;
	locations[n].carrier = true;
	
	locations[n].questSeekCap = 8; 
	
	locations[n].type = "town";
	LAi_LocationFantomsGen(&locations[n], true);
	locations[n].houseEnc = true; 
	
	
	locations[n].models.always.town = "Havana";
	locations[n].models.always.town.sea_reflection = 1;
	locations[n].models.always.L1 = "Havana_signsA";
	locations[n].models.always.seabed = "Havana_sb";
	locations[n].models.always.locators = "Havana_locators";
	locations[n].models.always.grassPatch = "Havana_grass";
	
	locations[n].models.always.plan = "plan1";
	locations[n].models.always.plan.level = 9;

	
	locations[n].models.always.Waterfall1 = "fontain1";
	locations[n].models.always.Waterfall1.uvslide.v0 = 0.5;
    locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	locations[n].models.always.Waterfall1.level = 50;
	
	locations[n].models.always.Waterfall2 = "fontain2";
	locations[n].models.always.Waterfall2.uvslide.v0 = 0.2;
    locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
	locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
	locations[n].models.always.Waterfall2.level = 49;

	
	locations[n].models.always.MillFan = "MillFan";
	Locations[n].models.always.MillFan.locator.group = "WindMill";
	Locations[n].models.always.MillFan.locator.name ="Fan";	
	Locations[n].models.always.MillFan.rotate.x = 0.0;
	Locations[n].models.always.MillFan.rotate.y = 0.0;
	Locations[n].models.always.MillFan.rotate.z = 0.2;

	
	locations[n].models.day.fonar = "Havana_fd";
	locations[n].models.day.charactersPatch = "Havana_patch_day";
	locations[n].models.day.rinok = "Havana_rinok";
	
	locations[n].models.night.fonar = "Havana_fn";
	locations[n].models.night.charactersPatch = "Havana_patch_night";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	

    
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Cuba2";
	locations[n].reload.l1.emerge = "reload_1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Sea";
	locations[n].locators_radius.reload.reload2_back = 1.8;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Cuba2";
	locations[n].reload.l2.emerge = "reload_1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.reload2_back = 1.8;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Havana_townhall";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Residence";
	locations[n].reload.l3.close_for_night = 1;

	locations[n].reload.lR1.name = "reloadR1";
	locations[n].reload.lR1.go = "Havana_TownhallRoom";
	locations[n].reload.lR1.emerge = "reload3";
	locations[n].reload.lR1.autoreload = "0";
	locations[n].reload.lR1.label = "Residence";
	locations[n].reload.lR1.close_for_night = 1;

	locations[n].reload.l4.name = "reload4_back";
	locations[n].reload.l4.go = "Havana_tavern";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Tavern";

	locations[n].reload.l5.name = "reload5_back";
	locations[n].reload.l5.go = "Havana_shipyard";
	locations[n].reload.l5.emerge = "reload1";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "Shipyard";
	locations[n].reload.l5.close_for_night = 1;

	locations[n].reload.l6.name = "reload6_back";
	locations[n].reload.l6.go = "Havana_store";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "Store";
	locations[n].reload.l6.close_for_night = 1;

	locations[n].reload.l7.name = "reload7_back";
	locations[n].reload.l7.go = "Havana_church";
	locations[n].reload.l7.emerge = "reload1";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "Church";

	locations[n].reload.l8.name = "reload8_back";
	locations[n].reload.l8.go = "Havana_bank";
	locations[n].reload.l8.emerge = "reload1";
	locations[n].reload.l8.autoreload = "0";
	locations[n].reload.l8.label = "Usurer House";
	locations[n].reload.l8.close_for_night = 1;

	locations[n].reload.l10.name = "reload10_back";
	locations[n].reload.l10.go = "Havana_PortOffice";
	locations[n].reload.l10.emerge = "reload1";
	locations[n].reload.l10.autoreload = "0";
	locations[n].reload.l10.label = "PortOffice";
	locations[n].reload.l10.close_for_night = 1;

	locations[n].reload.gate.name = "gate_back";
	locations[n].reload.gate.go = "Havana_ExitTown";
	locations[n].reload.gate.emerge = "reload4";
	locations[n].reload.gate.autoreload = "0";
	locations[n].reload.gate.label = "ExitTown";
	
	locations[n].reload.jail.name = "reload_jail";
	locations[n].reload.jail.go = "Havana_prison";
	locations[n].reload.jail.emerge = "reload1";
	locations[n].reload.jail.autoreload = "0";
	locations[n].reload.jail.label = "Prison";

    
	
    
	locations[n].reload.l20.name = "houseS4";
	locations[n].reload.l20.go = "CommonStoneHouse";
	locations[n].reload.l20.emerge = "reload1";
	locations[n].reload.l20.autoreload = "0";
	locations[n].reload.l20.label = "House";

	locations[n].reload.l21.name = "houseH1";
	locations[n].reload.l21.go = "CommonRoom_MH4";
	locations[n].reload.l21.emerge = "reload1";
	locations[n].reload.l21.autoreload = "0";
	locations[n].reload.l21.label = "House";

	locations[n].reload.l22.name = "houseS3";
	locations[n].reload.l22.go = "CommonFlamHouse";
	locations[n].reload.l22.emerge = "reload1";
	locations[n].reload.l22.autoreload = "0";
	locations[n].reload.l22.label = "House";

	locations[n].reload.l23.name = "houseSp3";
	locations[n].reload.l23.go = "CommonPirateHouse";
	locations[n].reload.l23.emerge = "reload1";
	locations[n].reload.l23.autoreload = "0";
	locations[n].reload.l23.label = "House";

	locations[n].reload.l24.name = "houseSp1";
	locations[n].reload.l24.go = "CommonDoubleflourHouse_1";
	locations[n].reload.l24.emerge = "reload1";
	locations[n].reload.l24.autoreload = "0";
	locations[n].reload.l24.label = "House";

	locations[n].reload.l25.name = "houseS2";
	locations[n].reload.l25.go = "CommonDoubleflourHouse_2";
	locations[n].reload.l25.emerge = "reload1";
	locations[n].reload.l25.autoreload = "0";
	locations[n].reload.l25.label = "House";

	locations[n].reload.l26.name = "houseF1";
	locations[n].reload.l26.go = "CommonRoom_MH3";
	locations[n].reload.l26.emerge = "reload1";
	locations[n].reload.l26.autoreload = "0";
	locations[n].reload.l26.label = "House";

	locations[n].reload.l27.name = "houseF2";
	locations[n].reload.l27.go = "CommonRoom_MH2";
	locations[n].reload.l27.emerge = "reload1";
	locations[n].reload.l27.autoreload = "0";
	locations[n].reload.l27.label = "House";

	locations[n].reload.l28.name = "houseF3";
	locations[n].reload.l28.go = "CommonRoom_MH";
	locations[n].reload.l28.emerge = "reload1";
	locations[n].reload.l28.autoreload = "0";
	locations[n].reload.l28.label = "House";

	locations[n].reload.l29.name = "houseH2";
	locations[n].reload.l29.go = "CommonRoom_MH3";
	locations[n].reload.l29.emerge = "reload1";
	locations[n].reload.l29.autoreload = "0";
	locations[n].reload.l29.label = "House";
	
	locations[n].reload.l30.name = "houseSp21";
	locations[n].reload.l30.go = "CommonFlamHouse";
	locations[n].reload.l30.emerge = "reload1";
	locations[n].reload.l30.autoreload = "0";
	locations[n].reload.l30.label = "House";
	
	locations[n].reload.l31.name = "houseSp2";
	locations[n].reload.l31.go = "CommonFlamHouse";
	locations[n].reload.l31.emerge = "reload2";
	locations[n].reload.l31.autoreload = "0";
	locations[n].reload.l31.label = "House";
	
	locations[n].reload.l32.name = "houseS1";
	locations[n].reload.l32.go = "CommonCobHouse";
	locations[n].reload.l32.emerge = "reload1";
	locations[n].reload.l32.autoreload = "0";
	locations[n].reload.l32.label = "House";
	n = n + 1;

	
	
	
	locations[n].id = "Havana_tavern";
	locations[n].id.label = "Tavern";
	locations[n].filespath.models = "locations\inside\tavern01\";
	locations[n].image = "loading\inside\tavern.tga";
	locations[n].habitues = 1;
	
	locations[n].townsack = "Havana";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "tavern";
	locations[n].fastreload = "Havana";
 	locations[n].islandId = "Cuba";
	
	
	locations[n].models.always.tavern = "Tavern01";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.locators = "Tavern01_locators";
	locations[n].models.always.window = "tavern01_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.window.level = 65529;
	
	locations[n].models.day.charactersPatch = "tavern01_patch";
	
	locations[n].models.night.charactersPatch = "tavern01_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Havana_town";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Havana_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Martinique Tavern upstairs";
	locations[n].reload.l2.disable = 1; 
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	
	
	
	locations[n].id = "Havana_tavern_upstairs";
	locations[n].filespath.models = "locations\inside\Tavern_room";
	locations[n].id.label = "Tavern upstairs";
	locations[n].image = "loading\inside\tavern.tga";
	
	locations[n].townsack = "Havana";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Havana";
  	locations[n].islandId = "Cuba";
	
	
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
	locations[n].reload.l1.go = "Havana_tavern";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

 	
	
	
	locations[n].id = "Havana_store";
	locations[n].id.label = "Store";
	locations[n].filespath.models = "locations\inside\store01\";
	locations[n].image = "loading\inside\shop.tga";
	
	locations[n].townsack = "Havana";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "shop";
	locations[n].fastreload = "Havana";
 	locations[n].islandId = "Cuba";
	
	
	locations[n].models.always.locators = "Store01_locators";
	locations[n].models.always.store = "Store01";
	locations[n].models.always.store.level = 65538;
	locations[n].models.always.window = "Store01_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	locations[n].models.day.charactersPatch = "store01_patch";
	
	locations[n].models.night.charactersPatch = "store01_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Havana_town";
	locations[n].reload.l1.emerge = "reload6";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.camdetector.camera1 = 5;
    
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonPackhouse_1";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	
	
	
	locations[n].id = "Havana_Bank";
	locations[n].id.label = "Usurer House";
	locations[n].filespath.models = "locations\inside\Bank01\";
	locations[n].image = "loading\inside\bank.tga";
	
	locations[n].townsack = "Havana";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "shop";
	locations[n].fastreload = "Havana";
 	locations[n].islandId = "Cuba";
	
	
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
	locations[n].reload.l1.go = "Havana_town";
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

 	
	
	
	locations[n].id = "Havana_Shipyard";
	locations[n].id.label = "Shipyard";
	locations[n].filespath.models = "locations\inside\Shipyard03\";
	locations[n].image = "loading\inside\shipyard.tga";
	
	locations[n].townsack = "Havana";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "shipyard";
	locations[n].fastreload = "Havana";
  	locations[n].islandId = "Cuba";
	
	
	locations[n].models.always.locators = "Shipyard03_locators";
	locations[n].models.always.shipyard = "Shipyard03";
	locations[n].models.always.shipyard.level = 65538;
	locations[n].models.always.window = "shipyard03_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	locations[n].models.day.charactersPatch = "Shipyard03_patch";
	
	locations[n].models.night.charactersPatch = "Shipyard03_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Havana_town";
	locations[n].reload.l1.emerge = "reload5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Havana_Packhouse";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "packhouse";
	locations[n].locators_radius.item.item1 = 1.0;
	n = n + 1;

	
	
	
	locations[n].id = "Havana_Packhouse";
	locations[n].id.label = "packhouse";
	locations[n].image = "loading\inside\sklad.tga";
	
	locations[n].townsack = "Havana";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Havana";
	locations[n].islandId = "Cuba";
	
	
	locations[n].filespath.models = "locations\inside\sklad03";
	locations[n].models.always.locators = "sklad03_locators";
	locations[n].models.always.modelSklad = "sklad03";
	locations[n].models.always.modelSklad.level = 65538;
	
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	locations[n].models.day.charactersPatch = "sklad03_patch";
	
	locations[n].models.night.charactersPatch = "sklad03_patch";
	
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Havana_Shipyard";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "shipyard";
	n = n + 1;

	
 	
	
	
	locations[n].id = "Havana_townhall";
	locations[n].id.label = "Townhall";
	locations[n].filespath.models = "locations\inside\Residence01";
	locations[n].image = "loading\inside\residence.tga";
	
	locations[n].townsack = "Havana";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "residence";
	locations[n].fastreload = "Havana";
  	locations[n].islandId = "Cuba";
  	
	locations[n].soldiers = true;
	LAi_LocationFantomsGen(&locations[n], true);
	
	
	locations[n].models.always.locators = "Residence01_locators";
	locations[n].models.always.l1 = "Residence01";
	locations[n].models.always.l1.level = 65538;
	locations[n].models.always.window = "residence01_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;	
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	locations[n].models.day.charactersPatch = "Residence01_patch";
	
	locations[n].models.night.charactersPatch = "Residence01_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Havana_town";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonResidence_4";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";

	locations[n].reload.l3.name = "reload3"; 
	locations[n].reload.l3.go = "Havana_TownhallRoom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Room";
	n = n + 1;

	
	locations[n].id = "Havana_TownhallRoom"; 
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\BigHouseBack.tga";
	
	locations[n].townsack = "Havana";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Havana";
 	locations[n].islandId = "Cuba";
	
	
	locations[n].filespath.models = "locations\inside\BigHouseBack";
	locations[n].models.always.house = "BigHouseBack";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "BigHouseBack_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	locations[n].models.day.charactersPatch = "BigHouseBack_patch";
	locations[n].models.day.locators = "BigHouseBack_locators";
	
	locations[n].models.night.charactersPatch = "BigHouseBack_patch";
	locations[n].models.night.locators = "BigHouseBack_Nlocators";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Havana_townhall";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Townhall";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonBedroom";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "BedRoom";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Havana_town";
	locations[n].reload.l3.emerge = "reloadR1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Street";
	n = n + 1;

	
	
	
	locations[n].id = "Havana_church";
	locations[n].id.label = "Church";
	locations[n].image = "loading\inside\church.tga";
	
	locations[n].townsack = "Havana";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "church";
	locations[n].fastreload = "Havana";
 	locations[n].islandId = "Cuba";
	
	
	locations[n].filespath.models = "locations\inside\churchInside3";
	locations[n].models.always.churchInside3 = "churchInside3";
	locations[n].models.always.churchInside3.level = 65538;	
	locations[n].models.always.locators = "churchInside3_locators";
	
	Locations[n].models.always.churchInside3windows = "churchInside3_windows";
	Locations[n].models.always.churchInside3windows.tech = "LocationWindows";
	locations[n].models.always.churchInside3windows.level = 65539;	
	
	locations[n].models.always.backgroundInsides = "backgroundInsides";
	locations[n].models.always.backgroundInsides.level = 65529;	
	
	locations[n].models.day.charactersPatch = "churchInside3_patch";
	
	locations[n].models.night.charactersPatch = "churchInside3_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Havana_town";
	locations[n].reload.l1.emerge = "reload7";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	
	
	
	locations[n].id = "Havana_PortOffice";
	locations[n].id.label = "PortOffice";
	locations[n].image = "loading\inside\portoffice.tga";
	
	locations[n].townsack = "Havana";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Havana";
 	locations[n].islandId = "Cuba";
	
	
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
	locations[n].reload.l1.go = "Havana_town";
	locations[n].reload.l1.emerge = "reload10";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	
	Locations[n].id = "Havana_prison";
	locations[n].id.label = "Prison";
	Locations[n].image = "loading\inside\prison.tga";
	locations[n].townsack = "Havana";
    locations[n].parent_colony = "Havana";
 	locations[n].fastreload = "Havana";
	locations[n].islandId = "Cuba";
	
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
	Locations[n].reload.l1.go = "Havana_town";
	Locations[n].reload.l1.emerge = "reload_jail";
	Locations[n].reload.l1.autoreload = "0";
	
	locations[n].locators_radius.box.box1 = 0.8;
	locations[n].box1.QuestClosed = true;
	n = n + 1;

	
	
	
	locations[n].id = "Havana_ExitTown";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\Gate" + rand(1) + ".tga";
	
	locations[n].townsack = "Havana";
	
	locations[n].type = "jungle";
 	locations[n].islandId = "Cuba";
	locations[n].islandIdAreal = "Cuba2";
	
	
	locations[n].filespath.models = "locations\Outside\Jungles\TownExitW";
	Locations[n].models.always.townExit = "townExitW";
	Locations[n].models.always.townWalls = "townExitW_wood";
	
	Locations[n].models.always.locators = "townExitW_locators";
		
	Locations[n].models.always.grassPatch = "townExitW_grass";
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
	
	locations[n].models.day.charactersPatch = "townExitW_patch";
	locations[n].models.day.fonars = "townExitW_fd";
	
	locations[n].models.night.charactersPatch = "townExitW_patch";
	locations[n].models.night.fonars = "townExitW_fn";	
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Havana_Graveyard";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Graveyard";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Cuba_jungle_10";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Havana_Fort";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Havana Fort";
	locations[n].locators_radius.reload.reload3_back = 2.0;

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "Havana_town";
	locations[n].reload.l4.emerge = "gate_back";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Havana";
	n = n + 1;
	
	
	
	
	locations[n].id = "Havana_Graveyard";
	locations[n].id.label = "Graveyard";
	locations[n].image = "loading\Cemetery_" + rand(1) + ".tga";
	
	locations[n].townsack = "Havana";
	
	locations[n].type = "jungle";
	locations[n].islandId = "Cuba";
	locations[n].islandIdAreal = "Cuba2";
	locations[n].DisableEncounters = true;
	
	
	locations[n].filespath.models = "locations\Outside\Graveyard";
	Locations[n].models.always.Graveyard = "Churchyard";		
	Locations[n].models.always.grassPatch = "Churchyard_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "Churchyard_plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "Churchyard_plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "Churchyard_plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	
	locations[n].models.day.charactersPatch = "Churchyard_patch";
	Locations[n].models.day.locators = "Churchyard_ld";	
	
	locations[n].models.night.charactersPatch = "Churchyard_patch";	
	Locations[n].models.night.locators = "Churchyard_ln";	
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Havana_ExitTown";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "ExitTown";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Mayak10";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Mayak10";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Havana_KeepersHouse";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "House";
	
	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "Havana_CryptBig1";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "�hapel";
	
	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "Common_Crypt";
	locations[n].reload.l5.emerge = "reload1";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "Crypt";
	n = n + 1;

	
	
	locations[n].id = "Havana_KeepersHouse";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	
	locations[n].townsack = "Havana";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "House";
	locations[n].islandId = "Cuba";
	locations[n].islandIdAreal = "Cuba2";
	
	
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
	
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Havana_Graveyard";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Graveyard";
	n = n + 1;

	
	
	locations[n].id = "Havana_CryptBig1";
	locations[n].id.label = "Crypt";
	locations[n].image = "loading\Crypt_" + rand(1) + ".tga";
	
	locations[n].townsack = "Havana";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "Dungeon";
	locations[n].islandId = "Cuba";
	locations[n].islandIdAreal = "Cuba2";
	
	
	locations[n].filespath.models = "locations\inside\crypt_2_1_inside\";
	locations[n].models.always.cryptbig = "crypt_2_1_inside";
	locations[n].models.always.back = "..\inside_back";
	
	locations[n].models.day.charactersPatch = "crypt_2_1_inside_patch";
	locations[n].models.day.locators = "crypt_2_1_inside_ld";
	
	locations[n].models.night.charactersPatch = "crypt_2_1_inside_patch";
	locations[n].models.night.locators = "crypt_2_1_inside_ln";
	
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Havana_Graveyard";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Graveyard";
	
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Havana_CryptBig2";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Crypt";
	n = n + 1;

	
	
	locations[n].id = "Havana_CryptBig2";
	locations[n].id.label = "Crypt";
	locations[n].image = "loading\Crypt_" + rand(1) + ".tga";
	
	locations[n].townsack = "Havana";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "Dungeon";
	locations[n].islandId = "Cuba";
	locations[n].islandIdAreal = "Cuba2";
	
	
	locations[n].filespath.models = "locations\inside\crypt_2_2_inside\";
	locations[n].models.always.cryptbig = "crypt_2_2_inside";
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.locators = "crypt_2_2_inside_locators";
	
	locations[n].models.day.charactersPatch = "crypt_2_2_inside_patch";
	
	locations[n].models.night.charactersPatch = "crypt_2_2_inside_patch";
	
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Havana_CryptBig1";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Crypt";
	
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Havana_CryptDungeon";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "";
	locations[n].reload.l2.disable = true; 
	n = n + 1;
	
	
	
	locations[n].id = "Havana_CryptDungeon";
	locations[n].id.label = "";
	locations[n].image = "loading\inside\dungeon.tga";
	
	locations[n].townsack = "Havana";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "Dungeon";
	locations[n].islandId = "Cuba";
	locations[n].islandIdAreal = "Cuba2";
	
	
	locations[n].filespath.models = "locations\inside\Animists_cave\";
	locations[n].models.always.CryptDungeon = "Animists_cave";
	locations[n].models.always.locators = "Animists_cave_locators";
	
	locations[n].models.day.charactersPatch = "Animists_cave_patch";
	
	locations[n].models.night.charactersPatch = "Animists_cave_patch";
	
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Havana_CryptBig2";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Crypt";
	
	n = n + 1;
	
	
	locations[n].id = "Havana_ReservedLoc";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	
	locations[n].townsack = "Havana";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "House";
	locations[n].islandId = "Cuba";
	locations[n].islandIdAreal = "Cuba2";
	
	
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
	
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Havana_Graveyard";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	n = n + 1;

	
	
	
	locations[n].id = "Mayak10";
	locations[n].id.label = "Mayak10";
	locations[n].worldmap = "Mayak10";
	locations[n].image = "loading\outside\lighthouse.tga";
	
	locations[n].type = "mayak";
 	locations[n].islandId = "Cuba";
	locations[n].islandIdAreal = "Cuba2";
	
	
	locations[n].filespath.models = "locations\Outside\Shores\Lighthouse";
	Locations[n].models.always.lighthouse = "lighthouse";
	locations[n].models.always.lighthouse.sea_reflection = 1;
	Locations[n].models.always.lighthouseSeabed = "lighthouse_sb";
	Locations[n].models.always.locators = "lighthouse_locators";
	
	Locations[n].models.always.dooropen = "lighthouse_dooropen";
	Locations[n].models.always.dooropen.tech = "DLightModel";	
	
	Locations[n].models.always.windows = "lighthouse_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 66530;
		
	Locations[n].models.always.grassPatch = "lighthouse_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";		
	
	locations[n].models.day.winday = "lighthouse_winday";
	locations[n].models.day.fonar = "lighthouse_fd";
	locations[n].models.day.charactersPatch = "lighthouse_patch";
	Locations[n].models.day.jumpPatch = "lighthouse_jamp";
	
	locations[n].models.day.glassinday = "lighthouse_glassinday";
	Locations[n].models.day.glassinday.tech = "LocationWindows";
	locations[n].models.day.glassinday.level = 66531;
	
	locations[n].models.day.glassonday = "lighthouse_glassonday";
	Locations[n].models.day.glassonday.tech = "LocationWindows";
	locations[n].models.day.glassonday.level = 66532;	
	
	locations[n].models.night.volumeLight= "lighthouse_volumeLight";
	locations[n].models.night.volumeLight.tech = "LighthouseLight";
	locations[n].models.night.volumeLight.level = 66529;	
	
	locations[n].models.night.fonar = "lighthouse_fn";
	locations[n].models.night.winnight = "lighthouse_winnight";
	locations[n].models.night.winnight.tech = "LighthouseLight";
	locations[n].models.night.winnight.level = 66529;
	locations[n].models.night.charactersPatch = "lighthouse_patch";	
	Locations[n].models.night.jumpPatch = "lighthouse_jamp";
	
	locations[n].models.night.glassinnight = "lighthouse_glassinnight";
	Locations[n].models.night.glassinnight.tech = "LocationWindows";
	locations[n].models.night.glassinnight.level = 66531;
	
	locations[n].models.night.glassonnight = "lighthouse_glassonnight";
	Locations[n].models.night.glassonnight.tech = "LocationWindows";
	locations[n].models.night.glassonnight.level = 66532;
	
	locations[n].models.night.fonaronnight = "lighthouse_fonaronnight";		
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Havana_Graveyard";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Graveyard";
	locations[n].locators_radius.reload.reload1_back = 3.0;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Cuba2";
	locations[n].reload.l2.emerge = "reload_2";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.boat = 12.0;
	
	locations[n].reload.l3.name = "reload2";
	locations[n].reload.l3.go = "Mayak10_Lighthouseroom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.label = "room";
	locations[n].locators_radius.reload.reload2 = 1.0;
	n = n + 1;
	
	
	
	
	
	locations[n].id = "Mayak10_Lighthouseroom";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	
	locations[n].townsack = "Havana";
	locations[n].islandId = "Cuba2";
	
	locations[n].type = "house";
	
	
	locations[n].filespath.models = "locations\inside\mediumhouse09";
	locations[n].models.always.house = "mediumhouse09";
	locations[n].models.always.house.level = 65538;
	locations[n].models.day.locators = "mediumhouse09_locators";
	locations[n].models.night.locators = "mediumhouse09_Nlocators";

	Locations[n].models.always.mediumhouse09windows = "mediumhouse09_windows";
	Locations[n].models.always.mediumhouse09windows.tech = "LocationWindows";
	locations[n].models.always.mediumhouse09windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	Locations[n].models.day.mediumhouse09rand= "mediumhouse09_rand";
	locations[n].models.day.charactersPatch = "mediumhouse09_patch";
	
	locations[n].models.night.charactersPatch = "mediumhouse09_patch";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Mayak10";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Mayak10";
	n = n + 1;

	
	
	
	locations[n].id = "Cuba_Jungle_10";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	
	locations[n].type = "jungle";
	locations[n].islandId = "Cuba";
	locations[n].islandIdAreal = "Cuba2";
	
	
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
	
	locations[n].models.day.charactersPatch = "jungle2_patch";
	
	locations[n].models.night.charactersPatch = "jungle2_patch";	
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Cuba_Jungle_12";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Havana_ExitTown";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Cuba_jungle_11";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;

	
	
	
	locations[n].id = "Cuba_jungle_11";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	
	locations[n].type = "jungle";
	locations[n].islandId = "Cuba";
	locations[n].islandIdAreal = "Cuba2";
	
	
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
	locations[n].reload.l1.go = "Shore13";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Shore13";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Cuba_Jungle_10";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Cuba_Jungle_07";
	locations[n].reload.l3.emerge = "reload3";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 3;
	n = n + 1;

	
	
	
	locations[n].id = "Shore13";
	locations[n].id.label = "Shore13";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "Shore13";
	
	locations[n].type = "seashore";
	locations[n].islandId = "Cuba";
	locations[n].islandIdAreal = "Cuba2";
	
	
	locations[n].filespath.models = "locations\Outside\Shores\Shore10";
	Locations[n].models.always.shore10 = "shore10";
	locations[n].models.always.shore10.sea_reflection = 1;
	Locations[n].models.always.shore10seabed = "shore10_sb";
	Locations[n].models.always.locators = "shore10_locators";
		
	Locations[n].models.always.grassPatch = "shore10_grass";
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
	
	locations[n].models.day.charactersPatch = "shore10_patch";
	
	locations[n].models.night.charactersPatch = "shore10_patch";		
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Cuba_jungle_11";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Cuba2";
	locations[n].reload.l2.emerge = "reload_5";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	
	
	
	locations[n].id = "Cuba_jungle_12";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	
	locations[n].type = "jungle";
 	locations[n].islandId = "Cuba";
	locations[n].islandIdAreal = "Cuba2";
	
	
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
	
	locations[n].models.day.charactersPatch = "jungle5_patch";
	
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Cuba_jungle_13";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Cuba_jungle_10";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Shore14";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Shore14";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;

	
	
	
	locations[n].id = "Shore14";
	locations[n].id.label = "Shore14";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "Shore14";
	
	locations[n].type = "seashore";
	locations[n].islandId = "Cuba";
	locations[n].islandIdAreal = "Cuba2";
	
	
	locations[n].filespath.models = "locations\Outside\Shores\Shore06";
	Locations[n].models.always.shore06 = "shore06";
	locations[n].models.always.shore06.sea_reflection = 1;
	Locations[n].models.always.shore06seabed = "shore06_sb";
	Locations[n].models.always.locators = "shore06_locators";
		
	Locations[n].models.always.grassPatch = "shore06_grass";
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
	
	locations[n].models.day.charactersPatch = "shore06_patch";
	
	locations[n].models.night.charactersPatch = "shore06_patch";		
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Cuba_jungle_12";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Cuba2";
	locations[n].reload.l2.emerge = "reload_4";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	
	
	
    locations[n].id = "Cuba_jungle_13";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
 	
	locations[n].type = "jungle";
	locations[n].islandId = "Cuba";
	locations[n].islandIdAreal = "Cuba2";
	
	
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
	
	locations[n].models.day.charactersPatch = "jungle8_patch";
	
	locations[n].models.night.charactersPatch = "jungle8_patch";	
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Shore15";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Shore15";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Cuba_jungle_12";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	
	
	
	locations[n].id = "Shore15";
	locations[n].id.label = "Shore15";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "Shore15";
	
	locations[n].type = "seashore";
	locations[n].islandId = "Cuba";
	locations[n].islandIdAreal = "Cuba2";
	
	
	locations[n].filespath.models = "locations\Outside\Shores\Shore02";
	Locations[n].models.always.shore02 = "shore02";
	locations[n].models.always.shore02.sea_reflection = 1;
	Locations[n].models.always.shore02seabed = "shore02_sb";
	Locations[n].models.always.locators = "shore02_locators";
		
	Locations[n].models.always.grassPatch = "shore02_grass";
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
	
	locations[n].models.day.charactersPatch = "shore02_patch";
	
	locations[n].models.night.charactersPatch = "shore02_patch";		
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Cuba_jungle_13";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Cuba2";
	locations[n].reload.l2.emerge = "reload_3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	return n;
}

