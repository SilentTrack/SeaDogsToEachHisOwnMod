int LocationInitOldWorld(int n)
{
	
	
	
	
	
	
	
	
	ref rLoc = &locations[n];
	String sLocID = "OldWorld_Port";
	rLoc.id = sLocID;
	rLoc.id.label = "Street";
	rLoc.worldmap = "PortRoyal";
	
	rLoc.townsack = "PortRoyal"; 
	rLoc.fastreload = "PortRoyal"; 
	rLoc.islandId = "OldWorld"; 
	
	rLoc.image = "loading\Town.tga";
	rLoc.citizens = true;
	rLoc.soldiers = true;
	 
	
	
	rLoc.type = "town";
	LAi_LocationFantomsGen(rLoc, true);


	
	
	rLoc.filespath.models = "Locations\OldWorld\Town_Port\";
	rLoc.models.always.Town_Port = "Town_Port";
	rLoc.models.always.seabed = "Town_Port_sb";
	rLoc.models.always.Town_Part1.tech = "DLightModel";
	rLoc.models.always.locators = "Town_Port_l"; 
	rLoc.models.always.grassPatch = "Town_Port_g"; 
	rLoc.models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	
	

	rLoc.models.day.rinok = "Town_Port_Rinok"; 
	rLoc.models.day.fonar = "Town_Port_fd"; 
	rLoc.models.day.charactersPatch = "Town_Port_pd"; 
	

	rLoc.models.night.fonar = "Town_Part1_fn"; 
	rLoc.models.night.charactersPatch = "Town_Port_pn"; 
	
	rLoc.environment.weather = "true";
	rLoc.environment.sea = "true";
	
	
	Location_AddReload(sLocID, 1, "reload2", "OldWorld_Town_Part1", "reload1", false, "Street", 2.0); 
	
	n++;
	
	
	
	
	
	rLoc = &locations[n];
	sLocID = "OldWorld_Town_Part1";
	
	rLoc.id = sLocID;
	rLoc.id.label = "Street";
	rLoc.worldmap = "PortRoyal";
	
	rLoc.townsack = "PortRoyal"; 
	rLoc.fastreload = "PortRoyal"; 
	rLoc.islandId = "Jamaica"; 
	
	rLoc.image = "loading\Town.tga";
	rLoc.citizens = true;
	 
	
	
	rLoc.type = "town";
	LAi_LocationFantomsGen(rLoc, true);


	
	
	
	rLoc.filespath.models = "Locations\OldWorld\Town_Part1\";
	rLoc.models.always.Town_Part1 = "Town_Part1";
	rLoc.models.always.Town_Part1.tech = "DLightModel";
	rLoc.models.always.locators = "Town_Part1_l";
	
	rLoc.models.always.grassPatch = "Town_Part1_g";
	rLoc.models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	
	
	rLoc.models.day.jumpPatch = "Town_Part1_j";
	rLoc.models.day.rinok = "Town_Part1_Rinok";
	rLoc.models.day.fonar = "Town_Part1_fd";
	rLoc.models.day.charactersPatch = "Town_Part1_pd";
	
	rLoc.models.night.jumpPatch = "Town_Part1_j";
	rLoc.models.night.fonar = "Town_Part1_fn";
	rLoc.models.night.charactersPatch = "Town_Part1_pn";
	
	rLoc.environment.weather = "true";
	rLoc.environment.sea = "false";
	
	Location_AddReload(sLocID, 1, "reload1", "OldWorld_Port", "reload2", false, "", 1.5); 
	Location_AddReload(sLocID, 2, "reload2", "OldWorld_Town_Part3", "reload6", true, "Street", 1.5);
	Location_AddReload(sLocID, 3, "reload3", "OldWorld_Town_Part4", "reload3", true, "Street", 1.5);
	Location_AddReload(sLocID, 4, "reload4", "OldWorld_Town_Part3", "reload9", true, "Street", 1.5);
	Location_AddReload(sLocID, 5, "reload20", "OldWorld_Town_Part2", "reload4", false, "Street", 1.5);
	
	n++;
	
	
	
	
	
	rLoc = &locations[n];
	sLocID = "OldWorld_Town_Part2";
	
	rLoc.id = sLocID;
	rLoc.id.label = "Street";
	rLoc.worldmap = "PortRoyal";
	
	rLoc.townsack = "PortRoyal"; 
	rLoc.fastreload = "PortRoyal"; 
	rLoc.islandId = "OldWorld"; 
	
	rLoc.image = "loading\Town.tga";
	rLoc.citizens = true;
	rLoc.soldiers = true;
	 
	
	
	rLoc.type = "town";
	LAi_LocationFantomsGen(rLoc, true);


	
	
	
	rLoc.filespath.models = "Locations\OldWorld\Town_Part2\";
	rLoc.models.always.Town_Part2 = "Town_Part2";
	rLoc.models.always.Town_Part2.tech = "DLightModel";
	rLoc.models.always.locators = "Town_Part2_l";
	
	rLoc.models.always.grassPatch = "Town_Part2_g";
	rLoc.models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	
	
	rLoc.models.day.jumpPatch = "Town_Part2_j";
	rLoc.models.day.fonar = "Town_Part2_fd";
	rLoc.models.day.charactersPatch = "Town_Part2_p";
	
	rLoc.models.night.jumpPatch = "Town_Part2_j";
	rLoc.models.night.fonar = "Town_Part2_fn";
	rLoc.models.night.charactersPatch = "Town_Part2_p";
	
	rLoc.environment.weather = "true";
	rLoc.environment.sea = "false";
	
	Location_AddReload(sLocID, 1, "Reload4", "OldWorld_Town_Part1", "reload20", false, "Street", 1.5); 
	
	n++;
	
	
	
	
	
	rLoc = &locations[n];
	sLocID = "OldWorld_Town_Part3";
	
	rLoc.id = sLocID;
	rLoc.id.label = "Street";
	rLoc.worldmap = "PortRoyal";
	
	rLoc.townsack = "PortRoyal"; 
	rLoc.fastreload = "PortRoyal"; 
	rLoc.islandId = "OldWorld"; 
	
	rLoc.image = "loading\Town.tga";
	rLoc.citizens = true;
	rLoc.soldiers = true;
	 
	
	
	rLoc.type = "town";
	LAi_LocationFantomsGen(rLoc, true);


	
	
	
	rLoc.filespath.models = "Locations\OldWorld\Town_Part3\";
	rLoc.models.always.Town_Part3 = "Town_Part3";
	rLoc.models.always.Town_Part3.tech = "DLightModel";
	rLoc.models.always.locators = "Town_Part3_l";
	
	rLoc.models.always.grassPatch = "Town_Part3_g";
	rLoc.models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	
	
	rLoc.models.day.jumpPatch = "Town_Part3_j";
	rLoc.models.day.fonar = "Town_Part3_fd";
	rLoc.models.day.rinok = "Town_Part3_rinok";
	rLoc.models.day.charactersPatch = "Town_Part3_pd";
	
	rLoc.models.night.jumpPatch = "Town_Part3_j";
	rLoc.models.night.fonar = "Town_Part3_fn";
	rLoc.models.night.charactersPatch = "Town_Part3_pn";
	
	rLoc.environment.weather = "true";
	rLoc.environment.sea = "false";
	
	Location_AddReload(sLocID, 1, "Reload1", "OldWorld_Town_Exit", "reload2", false, "ExitTown", 1.5); 
	Location_AddReload(sLocID, 2, "Reload6", "OldWorld_Town_Part1", "reload2", true, "Street", 1.5);
	Location_AddReload(sLocID, 3, "Reload9", "OldWorld_Town_Part1", "reload4", true, "Street", 1.5);

	n++;
	
	
	
	
	
	rLoc = &locations[n];
	sLocID = "OldWorld_Town_Part4";
	
	rLoc.id = sLocID;
	rLoc.id.label = "Street";
	rLoc.worldmap = "PortRoyal";
	
	rLoc.townsack = "PortRoyal"; 
	rLoc.fastreload = "PortRoyal"; 
	rLoc.islandId = "OldWorld"; 
	
	rLoc.image = "loading\Town.tga";
	rLoc.citizens = true;
	rLoc.soldiers = true;
	 
	
	
	rLoc.type = "town";
	LAi_LocationFantomsGen(rLoc, true);


	
	
	
	rLoc.filespath.models = "Locations\OldWorld\Town_Part4\";
	rLoc.models.always.Town_Part4 = "Town_Part4";
	rLoc.models.always.Town_Part4.tech = "DLightModel";
	rLoc.models.always.locators = "Town_Part4_l";
	
	rLoc.models.always.grassPatch = "Town_Part4_g";
	rLoc.models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	
	
	rLoc.models.day.jumpPatch = "Town_Part4_j";
	rLoc.models.day.fonar = "Town_Part4_fd";
	rLoc.models.day.charactersPatch = "Town_Part4_pd";
	
	rLoc.models.night.jumpPatch = "Town_Part4_j";
	rLoc.models.night.fonar = "Town_Part4_fn";
	rLoc.models.night.charactersPatch = "Town_Part4_pn";
	
	rLoc.environment.weather = "true";
	rLoc.environment.sea = "false";
	
	Location_AddReload(sLocID, 1, "reload3", "OldWorld_Town_Part1", "reload3", true, "Street", 1.5); 

	n++;
	
	
	
	
	
	rLoc = &locations[n];
	sLocID = "OldWorld_Town_Exit";
	
	rLoc.id = sLocID;
	rLoc.id.label = "ExitTown";
	rLoc.worldmap = "PortRoyal";
	
	rLoc.townsack = "PortRoyal"; 
	rLoc.fastreload = "PortRoyal"; 
	rLoc.islandId = "OldWorld"; 
	
	rLoc.image = "loading\Gate" + rand(1) + ".tga";
	 
	
	
	rLoc.type = "town";
	LAi_LocationFantomsGen(rLoc, true);


	
	
	
	rLoc.filespath.models = "Locations\OldWorld\Town_Exit\";
	rLoc.models.always.Town_Exit = "Town_Exit";
	rLoc.models.always.Town_Exit.tech = "DLightModel";
	rLoc.models.always.locators = "Town_Exit_l";
	
	rLoc.models.always.grassPatch = "Town_Exit_g";
	rLoc.models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	
	Location_AddNewModel(sLocID, "", "", "plan_1", "always", "LocationModelBlend", 9, false);
	Location_AddNewModel(sLocID, "", "", "plan_2", "always", "LocationModelBlend", 8, false);
	Location_AddNewModel(sLocID, "", "", "plan_3", "always", "LocationModelBlend", 7, false);

	
	
	rLoc.models.day.fonar = "Town_Exit_fd";
	rLoc.models.day.charactersPatch = "Town_Exit_p";
	
	rLoc.models.night.fonar = "Town_Exit_fn";
	rLoc.models.night.charactersPatch = "Town_Exit_p";
	
	rLoc.environment.weather = "true";
	rLoc.environment.sea = "false";
	
	Location_AddReload(sLocID, 1, "Reload2", "OldWorld_Town_Part3", "reload1", false, "Street", 1.5); 
	
	n++;

	return n;
}

