
int LocationInitPanama(int n)
{
	
	
	
	
	locations[n].id = "Panama_town";
	locations[n].id.label = "Street";
	locations[n].worldmap = "Panama";
	
	locations[n].townsack = "Panama";
	locations[n].fastreload = "Panama";
 	locations[n].islandId = "Mein";
	
	locations[n].filespath.models = "locations\Town_Panama\Town\";
	locations[n].image = "loading\Town.tga";
	locations[n].citizens = true;
	locations[n].soldiers = true;
	locations[n].carrier = true;
	
	locations[n].type = "town";
	LAi_LocationFantomsGen(&locations[n], true);
	locations[n].houseEnc = true; 
	
	
	locations[n].models.always.town = "Panama";
	locations[n].models.always.town.sea_reflection = 1;
	locations[n].models.always.L1 = "Panama_signsA";
	locations[n].models.always.locators = "Panama_locators";
	locations[n].models.always.seabed = "Panama_sb";
	locations[n].models.always.grassPatch = "Panama_grass";
	
	locations[n].models.always.plan = "plan1";
	locations[n].models.always.plan.level = 9;

	
	locations[n].models.always.MillFan = "MillFan";
	Locations[n].models.always.MillFan.locator.group = "WindMill";
	Locations[n].models.always.MillFan.locator.name ="Fan";	
	Locations[n].models.always.MillFan.rotate.x = 0.0;
	Locations[n].models.always.MillFan.rotate.y = 0.0;
	Locations[n].models.always.MillFan.rotate.z = 0.2;	
	
	
	locations[n].models.day.fonar = "Panama_fd";
	locations[n].models.day.charactersPatch = "Panama_patch_day";
	locations[n].models.day.rinok = "Panama_rinok";
	
	locations[n].models.night.fonar = "Panama_fn";
	locations[n].models.night.charactersPatch = "Panama_patch_night";
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	

    
	locations[n].reload.l0.name = "reload1";
	locations[n].reload.l0.go = "Panama";
	locations[n].reload.l0.emerge = "reload_1";
	locations[n].reload.l0.autoreload = "0";
	locations[n].reload.l0.label = "Sea";
	locations[n].locators_radius.reload.reload1 = 0.2;

	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Panama";
	locations[n].reload.l1.emerge = "reload_1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Sea";
	locations[n].locators_radius.reload.reload1_back = 1.8;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Panama_townhall";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Residence";
	locations[n].reload.l3.close_for_night = 1;

	locations[n].reload.lR1.name = "reloadR1";
	locations[n].reload.lR1.go = "Panama_TownhallRoom";
	locations[n].reload.lR1.emerge = "reload2";
	locations[n].reload.lR1.autoreload = "0";
	locations[n].reload.lR1.label = "Residence";
	locations[n].reload.lR1.close_for_night = 1;

	locations[n].reload.l4.name = "reload4_back";
	locations[n].reload.l4.go = "Panama_tavern";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Tavern";

	locations[n].reload.l6.name = "reload6_back";
	locations[n].reload.l6.go = "Panama_store";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "Shipyard";
	locations[n].reload.l6.close_for_night = 1;

	locations[n].reload.l7.name = "reload7_back";
	locations[n].reload.l7.go = "Panama_church";
	locations[n].reload.l7.emerge = "reload1";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "Church";

	locations[n].reload.l8.name = "reload8_back";
	locations[n].reload.l8.go = "Panama_bank";
	locations[n].reload.l8.emerge = "reload1";
	locations[n].reload.l8.autoreload = "0";
	locations[n].reload.l8.label = "Usurer House";
	locations[n].reload.l8.close_for_night = 1;

	locations[n].reload.l9.name = "reload9_back";
	locations[n].reload.l9.go = "Panama_brothel";
	locations[n].reload.l9.emerge = "reload1";
	locations[n].reload.l9.autoreload = "0";
	locations[n].reload.l9.label = "Brothel";
	
 	locations[n].reload.l91.name = "reload91";
	locations[n].reload.l91.go = "Panama_SecBrRoom";
	locations[n].reload.l91.emerge = "reload2";
	locations[n].reload.l91.autoreload = "0";
	locations[n].reload.l91.label = "Brothel";

	locations[n].reload.l10.name = "reload10_back";
	locations[n].reload.l10.go = "Panama_PortOffice";
	locations[n].reload.l10.emerge = "reload1";
	locations[n].reload.l10.autoreload = "0";
	locations[n].reload.l10.label = "PortOffice";
	locations[n].reload.l10.close_for_night = 1;

	locations[n].reload.gate.name = "gate_back";
	locations[n].reload.gate.go = "Panama_ExitTown";
	locations[n].reload.gate.emerge = "reload4";
	locations[n].reload.gate.autoreload = "0";
	locations[n].reload.gate.label = "ExitTown";
	
	locations[n].reload.jail.name = "reload_jail";
	locations[n].reload.jail.go = "Panama_prison";
	locations[n].reload.jail.emerge = "reload1";
	locations[n].reload.jail.autoreload = "0";
	locations[n].reload.jail.label = "Prison";

    

    
	locations[n].reload.l20.name = "houseS1";
	locations[n].reload.l20.go = "CommonDoubleflourHouse_2";
	locations[n].reload.l20.emerge = "reload1";
	locations[n].reload.l20.autoreload = "0";
	locations[n].reload.l20.label = "House";

	locations[n].reload.l21.name = "houseF1";
	locations[n].reload.l21.go = "CommonRoom_MH2";
	locations[n].reload.l21.emerge = "reload1";
	locations[n].reload.l21.autoreload = "0";
	locations[n].reload.l21.label = "House";
    
	locations[n].reload.l22.name = "houseSp2";
	locations[n].reload.l22.go = "CommonPirateHouse";
	locations[n].reload.l22.emerge = "reload1";
	locations[n].reload.l22.autoreload = "0";
	locations[n].reload.l22.label = "House";
    
	locations[n].reload.l23.name = "houseH1";
	locations[n].reload.l23.go = "CommonRoom_MH5";
	locations[n].reload.l23.emerge = "reload1";
	locations[n].reload.l23.autoreload = "0";
	locations[n].reload.l23.label = "House";

	locations[n].reload.l24.name = "houseS2";
	locations[n].reload.l24.go = "CommonFlamHouse";
	locations[n].reload.l24.emerge = "reload1";
	locations[n].reload.l24.autoreload = "0";
	locations[n].reload.l24.label = "House";

	locations[n].reload.l25.name = "houseH2";
	locations[n].reload.l25.go = "CommonRoom_MH4";
	locations[n].reload.l25.emerge = "reload1";
	locations[n].reload.l25.autoreload = "0";
	locations[n].reload.l25.label = "House";

	locations[n].reload.l26.name = "houseSp3";
	locations[n].reload.l26.go = "CommonDoubleflourHouse_1";
	locations[n].reload.l26.emerge = "reload1";
	locations[n].reload.l26.autoreload = "0";
	locations[n].reload.l26.label = "House";
	
	locations[n].reload.l27.name = "houseSp1";
	locations[n].reload.l27.go = "CommonDoubleflourHouse_1";
	locations[n].reload.l27.emerge = "reload1";
	locations[n].reload.l27.autoreload = "0";
	locations[n].reload.l27.label = "House";
	n = n + 1;

	
	
	
	locations[n].id = "Panama_tavern";
	locations[n].id.label = "Tavern";
	locations[n].filespath.models = "locations\inside\tavern03\";
	locations[n].image = "loading\inside\tavern.tga";
	locations[n].habitues = 1;
	
	locations[n].townsack = "Panama";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "tavern";
	locations[n].fastreload = "Panama";
   	locations[n].islandId = "Mein";
	
	
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
	locations[n].reload.l1.go = "Panama_town";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Panama_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; 
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	
	
	
	locations[n].id = "Panama_tavern_upstairs";
	locations[n].id.label = "Panama_tavern_upstairs";
	locations[n].filespath.models = "locations\inside\Tavern_room";
	locations[n].image = "loading\inside\tavern.tga";
	
	locations[n].townsack = "Panama";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Panama";
 	locations[n].islandId = "Mein";
	
	
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
	locations[n].reload.l1.go = "Panama_tavern";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

 	
	
	
	locations[n].id = "Panama_store";
	locations[n].id.label = "Store";
	locations[n].filespath.models = "locations\inside\Store04\";
	locations[n].image = "loading\inside\shop.tga";
	
	locations[n].townsack = "Panama";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "shop";
	locations[n].fastreload = "Panama";
 	locations[n].islandId = "Mein";
	
	
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
	locations[n].reload.l1.go = "Panama_town";
	locations[n].reload.l1.emerge = "reload6";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.camdetector.camera1 = 5;
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	
	
	
	locations[n].id = "Panama_bank";
	locations[n].id.label = "Usurer House";
	locations[n].filespath.models = "locations\inside\Bank01\";
	locations[n].image = "loading\inside\bank.tga";
	
	locations[n].townsack = "Panama";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "shop";
	locations[n].fastreload = "Panama";
  	locations[n].islandId = "Mein";
	
	
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
	locations[n].reload.l1.go = "Panama_town";
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

 	
	
	
	 

 	
	
	
	locations[n].id = "Panama_townhall";
	locations[n].id.label = "Townhall";
	locations[n].filespath.models = "locations\inside\Residence02";
	locations[n].image = "loading\inside\residence.tga";
	
	locations[n].townsack = "Panama";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "residence";
	locations[n].fastreload = "Panama";
 	locations[n].islandId = "Mein";
 	
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
	locations[n].reload.l1.go = "Panama_town";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Panama_TownhallRoom";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "TownhallRoom";
	n = n + 1;

	
	locations[n].id = "Panama_TownhallRoom"; 
	locations[n].id.label = "TownhallRoom";
	locations[n].image = "loading\inside\BigHouse01.tga";
	
	locations[n].townsack = "Panama";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Panama";
 	locations[n].islandId = "Mein";
	
	
	locations[n].filespath.models = "locations\inside\BigHouse01_2Door";
	locations[n].models.always.model = "BigHouse01_2Door";
	locations[n].models.always.model.level = 65538;
	locations[n].models.always.locators = "BigHouse01_2Door_locators";
	
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
	locations[n].reload.l1.go = "Panama_townhall";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Townhall";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Panama_town";
	locations[n].reload.l2.emerge = "reloadR1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";

	
	locations[n].private1.key = "keyPanama";
	
	locations[n].private1.items.gold = 50000000;
	locations[n].private2.items.map_terks = 1;
	locations[n].private2.items.map_Pearl = 1;
	locations[n].private2.items.potion2 = 5;
	locations[n].private2.items.potionwine = 2;
	locations[n].private2.items.potion5 = 1;
	locations[n].private2.items.potionrum = 2;
	locations[n].private2.items.potion4 = 3;
	n = n + 1;

	
	
	
	locations[n].id = "Panama_Brothel";
	locations[n].id.label = "Brothel";
	locations[n].filespath.models = "locations\inside\Brothel\";
	locations[n].image = "loading\inside\brothell_hall.tga";
	
	locations[n].townsack = "Panama";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Panama";
  	locations[n].islandId = "Mein";
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
	locations[n].reload.l1.go = "Panama_town";
	locations[n].reload.l1.emerge = "reload9";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Panama_Brothel_room";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Brothel Room";
	locations[n].reload.l2.disable = 1;  

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Panama_SecBrRoom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	
	
	
	locations[n].id = "Panama_Brothel_room";
	locations[n].id.label = "Brothel Room";
	locations[n].filespath.models = "locations\inside\Brothel_room\";
	locations[n].image = "loading\inside\brothell_room.tga";
	
	locations[n].townsack = "Panama";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Panama";
  	locations[n].islandId = "Mein";
	
	
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
	locations[n].reload.l1.go = "Panama_brothel";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	locations[n].locators_radius.item.item1 = 1;
	n = n + 1;

	
	locations[n].id = "Panama_SecBrRoom"; 
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\BigHouse03.tga";
 	
	locations[n].townsack = "Panama";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Panama";
  	locations[n].islandId = "Mein";
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
	locations[n].reload.l1.go = "Panama_Brothel";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Panama_town";
	locations[n].reload.l2.emerge = "reload91";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	
	
	
	locations[n].id = "Panama_church";
	locations[n].id.label = "Church";
	locations[n].filespath.models = "locations\inside\Church01";
	locations[n].image = "loading\inside\church.tga";
	
	locations[n].townsack = "Panama";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "church";
	locations[n].fastreload = "Panama";
 	locations[n].islandId = "Mein";
	
	
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
	locations[n].reload.l1.go = "Panama_town";
	locations[n].reload.l1.emerge = "reload7";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	
	
	
	locations[n].id = "Panama_PortOffice";
	locations[n].id.label = "PortOffice";
	locations[n].image = "loading\inside\portoffice.tga";
	
	locations[n].townsack = "Panama";
	locations[n].lockWeather = "Inside";
	
	locations[n].type = "house";
	locations[n].fastreload = "Panama";
 	locations[n].islandId = "Mein";
	
	
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
	locations[n].reload.l1.go = "Panama_town";
	locations[n].reload.l1.emerge = "reload10";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	
	Locations[n].id = "Panama_prison";
	locations[n].id.label = "Prison";
	Locations[n].image = "loading\inside\prison.tga";
	locations[n].townsack = "Panama";
    locations[n].parent_colony = "Panama";
 	locations[n].fastreload = "Panama";
	locations[n].islandId = "Mein";
	
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
	Locations[n].reload.l1.go = "Panama_town";
	Locations[n].reload.l1.emerge = "reload_jail";
	Locations[n].reload.l1.autoreload = "0";
	
	locations[n].locators_radius.box.box1 = 0.8;
	locations[n].box1.QuestClosed = true;
	n = n + 1;

	
	
	
	locations[n].id = "Panama_ExitTown";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\Gate" + rand(1) + ".tga";
	
	locations[n].townsack = "Panama";
	
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Panama";
	
	
	locations[n].filespath.models = "locations\Outside\Jungles\TownExitW";
	Locations[n].models.always.townExit = "townExitW";
	Locations[n].models.always.townWalls = "townExitW_stone";
	
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
	
	locations[n].reload.l1.name = "reload4";
	locations[n].reload.l1.go = "Panama_town";
	locations[n].reload.l1.emerge = "gate_back";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Panama";

	locations[n].reload.l2.name = "reload1_back";
	locations[n].reload.l2.go = "Panama_jungle_01";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l3.name = "reload2_back";
	locations[n].reload.l3.go = "Panama_jungle_03";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l4.name = "reload3_back";
	locations[n].reload.l4.go = "Panama_Fort";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "1";
	locations[n].reload.l4.label = "Panama Fort";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	
	
	
    locations[n].id = "Panama_jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
 	
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Panama";
	
	
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
	locations[n].reload.l1.go = "Panama_ExitTown";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Panama_jungle_02";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	
	
	
	locations[n].id = "Panama_jungle_02";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Panama";
	
	
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
	
	locations[n].models.day.charactersPatch = "jungle3_patch";
	
	locations[n].models.night.charactersPatch = "jungle3_patch";	
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Panama_jungle_01";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "PortoBello_Jungle_01";       
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Panama_CaveEntrance";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2.0;
	n = n + 1;

	
	
	
	locations[n].id = "Panama_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	
	locations[n].type = "jungle";
 	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Panama";
	
	
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
	locations[n].reload.l1.go = "Panama_Cave";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Cave";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Panama_jungle_02";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	
	
	
	locations[n].id = "Panama_Cave";
	locations[n].image = "loading\inside\cave.tga";
	locations[n].id.label = "Cave";
	
	locations[n].type = "cave";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Panama";
	locations[n].nofire = true;
	
	
	locations[n].filespath.models = "locations\inside\DungeonDuffer2";
	locations[n].models.always.DungeonDuffer2 = "DungeonDuffer2";
	locations[n].models.always.locators = "DungeonDuffer2_locators";

	locations[n].locators_radius.item.duhi1 = 1.3;
 	
	
	locations[n].models.day.charactersPatch = "DungeonDuffer2_patch";
	
	locations[n].models.night.charactersPatch = "DungeonDuffer2_patch";
	
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
 	
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Panama_CaveEntrance";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].locators_radius.item.berglar1 = 3.0;
	n = n + 1;
	
	
	
	
	locations[n].id = "Panama_jungle_03";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Panama";
	
	
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
	
	locations[n].models.day.charactersPatch = "jungle1_patch";
	
	locations[n].models.night.charactersPatch = "jungle1_patch";	
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Panama_ExitTown";
	locations[n].reload.l1.emerge = "reload2_back";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Panama_jungle_04";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	
	
	
	locations[n].id = "Panama_jungle_04";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Panama";
	
	
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
	locations[n].reload.l1.go = "Panama_jungle_03";
	locations[n].reload.l1.emerge = "reload2_back";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore63";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore63";
    locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Panama_jungle_05";   
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;
	
	
	
	
	locations[n].id = "Shore63";
	locations[n].id.label = "Shore63";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "Shore63";
	
	locations[n].type = "seashore";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Panama";
	locations[n].questflower = 1;
	
	
	locations[n].filespath.models = "locations\Outside\Shores\Shore01";
	Locations[n].models.always.shore01 = "shore01";
	locations[n].models.always.shore01.sea_reflection = 1;
	Locations[n].models.always.shore01seabed = "shore01_sb";
	Locations[n].models.always.locators = "shore01_locators";

	Locations[n].models.always.grassPatch = "shore01_grass";
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
	
	locations[n].models.day.charactersPatch = "shore01_patch";
	
	locations[n].models.night.charactersPatch = "shore01_patch";	
	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Panama_jungle_04";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Panama";
	locations[n].reload.l2.emerge = "reload_2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	
	
	
    locations[n].id = "Panama_jungle_05";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
 	
	locations[n].type = "jungle";
	locations[n].islandId = "Mein";
	locations[n].islandIdAreal = "Panama";
	
	
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
	locations[n].reload.l1.go = "Shore48";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Shore48";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Panama_jungle_04";
	locations[n].reload.l2.emerge = "reload3_back";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;
	
	return n;
}

