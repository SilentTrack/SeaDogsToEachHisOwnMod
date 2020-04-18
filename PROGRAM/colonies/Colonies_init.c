
void InitColonies()
{
	int n, i;

	for (i=0; i<MAX_COLONIES; i++)
	{
		DeleteAttribute(&Colonies[i], "");

        Colonies[i].index = i; 
		Colonies[i].id = "";
        Colonies[i].nation = "none";
		Colonies[i].commander = "-1";
		Colonies[i].island = "0"; 
		colonies[i].HeroOwn = false; 
		
		
		colonies[i].isBought = false;  
		colonies[i].from_sea = ""; 
		colonies[i].Default.BoardLocation = ""; 
		Colonies[i].visited = false; 
		
		
		Colonies[i].money = 0;
		Colonies[i].reload_enable = true;
		Colonies[i].visible = true;
		Colonies[i].capturetime = "";  
		Colonies[i].capture_day = ""; 
		Colonies[i].capture_month = ""; 
		Colonies[i].capture_year = "";  
		Colonies[i].timerInfo = "0";
		Colonies[i].captureInfo = "0";
		Colonies[i].captureSuccesInfo = "0";
		Colonies[i].resquetime = "";
		Colonies[i].days_for_resque = "-1";
		Colonies[i].capture_flag = "0"; 
		Colonies[i].agressor = "-1";
		Colonies[i].loyality = "1";
		Colonies[i].disease = "0";
		Colonies[i].disease.time = "0";

		Colonies[i].num = "1";
		colonies[i].population = 0;
		colonies[i].colonists = 0;
		colonies[i].tax_rate = (MOD_SKILL_ENEMY_RATE);
		colonies[i].isBuild = 0;
		colonies[i].info.day = worldMap.date.day;
		colonies[i].info.month = worldMap.date.month;
		colonies[i].info.year = worldMap.date.year;
		colonies[i].ismaincolony = 0;

		colonies[i].fort = 3;
		colonies[i].jail = rand(1); 

		
	}
	
		
	
	
	
		n = 0;
		Colonies[n].id = "Bridgetown";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = ENGLAND;
		Colonies[n].nation = ENGLAND;
		Colonies[n].island = "Barbados";
		Colonies[n].islandLable = "Barbados";
		colonies[n].num = 1;
		colonies[n].map.x = 1812;
		colonies[n].map.y = 1655;
		colonies[n].StoreNum   = Bridgetown_STORE;
		colonies[n].from_sea   = "Bridgetown_town";
		colonies[n].Default.BoardLocation = "Bridgetown_ExitTown";
		colonies[n].FortValue = 60; 
		colonies[n].mayak = 2;
				
	
	
	
		n = n + 1;
		Colonies[n].id = "SanJuan";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = SPAIN;
		Colonies[n].nation = SPAIN;
		Colonies[n].island = "PuertoRico";
		Colonies[n].islandLable = "PuertoRico";
		colonies[n].num = 1;
		colonies[n].map.x = 933;
		colonies[n].map.y = 312;
		colonies[n].StoreNum   = SanJuan_STORE;
		colonies[n].from_sea   = "SanJuan_town";
		colonies[n].Default.BoardLocation = "SanJuan_ExitTown";
		colonies[n].FortValue = 75; 
						
	
	
	
		n = n + 1;
		Colonies[n].id = "PortRoyal";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = ENGLAND;
		Colonies[n].nation = ENGLAND;
		Colonies[n].island = "Jamaica";
		Colonies[n].islandLable = "Jamaica";
		colonies[n].ismaincolony = 1;
		colonies[n].num = 1;
		colonies[n].map.x = 933;
		colonies[n].map.y = 312;
		colonies[n].StoreNum   = PortRoyal_STORE;
		colonies[n].from_sea   = "PortRoyal_town";
		colonies[n].Default.BoardLocation = "PortRoyal_ExitTown";
		colonies[n].FortValue = 95; 
		colonies[n].mayak = 3;
		
	
	
	
		n = n + 1;
		Colonies[n].id = "FortOrange";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = PIRATE;
		Colonies[n].nation = PIRATE;
		Colonies[n].island = "Jamaica";
		Colonies[n].islandLable = "Jamaica";
		Colonies[n].num = "1";
		colonies[n].map.x = 450;
		colonies[n].map.y = 325;
		colonies[n].StoreNum   = FortOrange_STORE;
		colonies[n].from_sea   = "";
		colonies[n].HasNoFort = true;
		colonies[n].Default.BoardLocation = "FortOrange_ExitTown";
		
	
	
	
		n = n + 1;
		Colonies[n].id = "Santiago";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = SPAIN;
		Colonies[n].nation = SPAIN;
		Colonies[n].island = "Cuba1";
		Colonies[n].islandLable = "Cuba";
		colonies[n].num = 1;
		colonies[n].map.x = 206;
		colonies[n].map.y = 440;
		colonies[n].StoreNum   = Santiago_STORE;
		colonies[n].from_sea   = "Santiago_town";
		colonies[n].Default.BoardLocation = "Santiago_ExitTown";
		colonies[n].FortValue = 70; 
		colonies[n].mayak = 9;
				
	
	
	
		n = n + 1;
		Colonies[n].id = "PuertoPrincipe";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = PIRATE;
		Colonies[n].nation = PIRATE;
		Colonies[n].island = "Cuba1";
		Colonies[n].islandLable = "Cuba";
		colonies[n].num = 1;
		colonies[n].map.x = 206;
		colonies[n].map.y = 440;
		colonies[n].HasNoFort = true;
		colonies[n].StoreNum   = PuertoPrincipe_STORE;
		colonies[n].from_sea   = "PuertoPrincipe_port";
				
	
	
	
		n = n + 1;
		Colonies[n].id = "Havana";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = SPAIN;
		Colonies[n].nation = SPAIN;
		Colonies[n].island = "Cuba2";
		Colonies[n].islandLable = "Cuba";
		colonies[n].ismaincolony = 1;
		colonies[n].num = 1;
		colonies[n].map.x = 1450;
		colonies[n].map.y = 895;
		colonies[n].StoreNum   = Havana_STORE;
		colonies[n].from_sea   = "Havana_town";
		colonies[n].Default.BoardLocation = "Havana_ExitTown";
		colonies[n].FortValue = 95; 
		colonies[n].mayak = 10;
				
	
	
	
		n = n + 1;
		Colonies[n].id = "Villemstad";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = HOLLAND;
		Colonies[n].nation = HOLLAND;
		Colonies[n].island = "Curacao";
		Colonies[n].islandLable = "Curacao";
		colonies[n].ismaincolony = 1;
		colonies[n].num = 1;
		colonies[n].map.x = 625;
		colonies[n].map.y = 1895;
		colonies[n].StoreNum   = Villemstad_STORE;
		colonies[n].from_sea   = "Villemstad_town";
		colonies[n].Default.BoardLocation = "Villemstad_ExitTown";
		colonies[n].FortValue = 95; 
		colonies[n].notCaptured = true; 
				
	
	
	
		n = n + 1;
		Colonies[n].id = "Tortuga";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = FRANCE;
		Colonies[n].nation = FRANCE;
		Colonies[n].island = "Tortuga";
		Colonies[n].islandLable = "Tortuga";
		colonies[n].num = 1;
		colonies[n].map.x = 450;
		colonies[n].map.y = 195;
		colonies[n].StoreNum   = Tortuga_STORE;
		colonies[n].from_sea   = "Tortuga_town";
		colonies[n].Default.BoardLocation = "Tortuga_ExitTown";
		colonies[n].FortValue = 95; 
		colonies[n].mayak = 6;
				
	
	
	
		n = n + 1;
		Colonies[n].id = "Marigo";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = HOLLAND;
		Colonies[n].nation = HOLLAND;
		Colonies[n].island = "SentMartin";
		Colonies[n].islandLable = "SentMartin";
		colonies[n].num = 1;
		colonies[n].map.x = 1320;
		colonies[n].map.y = 371;
		colonies[n].StoreNum   = Marigo_STORE;
		colonies[n].from_sea   = "Marigo_town";
		colonies[n].Default.BoardLocation = "Marigo_ExitTown";
		colonies[n].FortValue = 80; 
				
	
	
	
		n = n + 1;
		Colonies[n].id = "PortSpein";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = SPAIN;
		Colonies[n].nation = SPAIN;
		Colonies[n].island = "Trinidad";
		Colonies[n].islandLable = "Trinidad";
		colonies[n].num = 1;
		colonies[n].map.x = 1315;
		colonies[n].map.y = 648;
		colonies[n].StoreNum   = PortSpein_STORE;
		colonies[n].from_sea   = "PortSpein_town";
		colonies[n].Default.BoardLocation = "PortSpein_ExitTown";
		colonies[n].FortValue = 40; 
		colonies[n].mayak = 1;
		
	
	
	
		n = n + 1;
		Colonies[n].id = "Charles";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = FRANCE;
		Colonies[n].nation = FRANCE;
		Colonies[n].island = "Nevis";
		Colonies[n].islandLable = "Nevis";
		colonies[n].ismaincolony = 1;
		colonies[n].num = 1;
		colonies[n].map.x = 1381;
		colonies[n].map.y = 770;
		colonies[n].StoreNum   = Charles_STORE;
		colonies[n].from_sea   = "Charles_town";
		colonies[n].Default.BoardLocation = "Charles_ExitTown";
		colonies[n].FortValue = 55; 
		colonies[n].mayak = 5;
				
	
	
	
		n = n + 1;
		Colonies[n].id = "SentJons";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = ENGLAND;
		Colonies[n].nation = ENGLAND;
		Colonies[n].island = "Antigua";
		Colonies[n].islandLable = "Antigua";
		colonies[n].num = 1;
		colonies[n].map.x = 1495;
		colonies[n].map.y = 635;
		colonies[n].StoreNum   = SentJons_STORE;
		colonies[n].from_sea   = "SentJons_town";
		colonies[n].Default.BoardLocation = "SentJons_ExitTown";
		colonies[n].FortValue = 75; 
	    colonies[n].jail = 0; 
		
	
	
	
		n = n + 1;
		Colonies[n].id = "BasTer";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = FRANCE;
		Colonies[n].nation = FRANCE;
		Colonies[n].island = "Guadeloupe";
		Colonies[n].islandLable = "Guadeloupe";
		colonies[n].num = 1;
		colonies[n].map.x = 1560;
		colonies[n].map.y = 1010;
		colonies[n].StoreNum   = BasTer_STORE;
		colonies[n].from_sea   = "BasTer_town";
		colonies[n].Default.BoardLocation = "BasTer_ExitTown";
		colonies[n].FortValue = 85; 
		colonies[n].mayak = 4;
		
	
	
	
		n = n + 1;
		Colonies[n].id = "FortFrance";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = FRANCE;
		Colonies[n].nation = FRANCE;
		Colonies[n].island = "Martinique";
		Colonies[n].islandLable = "Martinique";
		colonies[n].num = 1;
		colonies[n].map.x = 1648;
		colonies[n].map.y = 1432;
		colonies[n].StoreNum   = FortFrance_STORE;
		colonies[n].from_sea   = "FortFrance_town";
		colonies[n].Default.BoardLocation = "FortFrance_ExitTown";
		colonies[n].FortValue = 80; 
		colonies[n].jail = 0; 
		
    
	
    
		n = n + 1;
		Colonies[n].id = "LeFransua";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = PIRATE;
		Colonies[n].nation = PIRATE;
		Colonies[n].island = "Martinique";
		Colonies[n].islandLable = "Martinique";
		colonies[n].num = 1;
		colonies[n].map.x = 1648;
		colonies[n].map.y = 1432;
		colonies[n].StoreNum   = LeFransua_STORE;
		colonies[n].from_sea   = "LeFransua_port";
		colonies[n].HasNoFort = true;

	
	
	
		n = n + 1;
		Colonies[n].id = "LaVega";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = PIRATE;
		Colonies[n].nation = PIRATE;
		Colonies[n].island = "Hispaniola1";
		Colonies[n].islandLable = "Hispaniola";
		Colonies[n].num = "1";
		colonies[n].map.x = 535;
		colonies[n].map.y = 265;
		colonies[n].StoreNum   = LaVega_STORE;
		colonies[n].from_sea   = "LaVega_port";
		colonies[n].HasNoFort = true;
        		
	
	
	
		n = n + 1;
		Colonies[n].id = "SantoDomingo";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = SPAIN;
		Colonies[n].nation = SPAIN;
		Colonies[n].island = "Hispaniola1";
		Colonies[n].islandLable = "Hispaniola";
		Colonies[n].num = "1";
		colonies[n].map.x = 568;
		colonies[n].map.y = 322;
		colonies[n].StoreNum   = SantoDomingo_STORE;
		colonies[n].from_sea   = "SantoDomingo_town";
		colonies[n].Default.BoardLocation = "SantoDomingo_ExitTown";
		colonies[n].FortValue = 45; 
		colonies[n].mayak = 8;
		
	
	
	
		n = n + 1;
		Colonies[n].id = "Pirates";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = PIRATE;
		Colonies[n].nation = PIRATE;
		Colonies[n].island = "Bermudes";
		Colonies[n].islandLable = "Bermudes";
		Colonies[n].num = "1";
		colonies[n].map.x = 720;
		colonies[n].map.y = 395;
		colonies[n].colonylevel = 0;
		colonies[n].StoreNum   = Pirates_STORE;
		colonies[n].from_sea   = "Pirates_town";
		colonies[n].HasNoFort = true;
				
	
	
	
		n = n + 1;
		Colonies[n].id = "PortPax";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = FRANCE;
		Colonies[n].nation = FRANCE;
		Colonies[n].island = "Hispaniola2";
		Colonies[n].islandLable = "Hispaniola";
		Colonies[n].num = "1";
		colonies[n].map.x = 450;
		colonies[n].map.y = 325;
		colonies[n].StoreNum   = PortPax_STORE;
		colonies[n].from_sea   = "PortPax_town";
		colonies[n].Default.BoardLocation = "PortPax_ExitTown";
		colonies[n].FortValue = 55; 
		colonies[n].mayak = 7;
		
	
	
	
		n = n + 1;
		Colonies[n].id = "Panama";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = SPAIN;
		Colonies[n].nation = SPAIN;
		Colonies[n].island = "Panama";  
		Colonies[n].islandLable = "Mein";
		Colonies[n].num = "1";
		colonies[n].map.x = 450;
		colonies[n].map.y = 325;
		colonies[n].StoreNum   = Panama_STORE;
		colonies[n].from_sea   = "Panama_town";    
		colonies[n].Default.BoardLocation = "Panama_ExitTown";
		
		
						
	
	
	
		n = n + 1;
		Colonies[n].id = "PortoBello";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = SPAIN;
		Colonies[n].nation = SPAIN;
		Colonies[n].island = "PortoBello";
		Colonies[n].islandLable = "Mein";
		colonies[n].ismaincolony = 1;
		colonies[n].num = 1;
		colonies[n].map.x = 1370;
		colonies[n].map.y = 505;
		colonies[n].StoreNum   = PortoBello_STORE;
		colonies[n].from_sea   = "PortoBello_town";
		colonies[n].Default.BoardLocation = "PortoBello_ExitTown";
		colonies[n].FortValue = 65; 
		colonies[n].notCaptured = true; 
				
	
	
	
		n = n + 1;
		Colonies[n].id = "Cartahena";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = SPAIN;
		Colonies[n].nation = SPAIN;
		Colonies[n].island = "Cartahena";
		Colonies[n].islandLable = "Mein";
		colonies[n].num = 1;
		colonies[n].map.x = 1370;
		colonies[n].map.y = 505;
		colonies[n].StoreNum   = Cartahena_STORE;
		colonies[n].from_sea   = "Cartahena_town";
		colonies[n].Default.BoardLocation = "Cartahena_ExitTown";
		colonies[n].FortValue = 45; 
		colonies[n].mayak = 11;
				
	
	
	
		n = n + 1;
		Colonies[n].id = "Maracaibo";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = SPAIN;
		Colonies[n].nation = SPAIN;
		Colonies[n].island = "Maracaibo";
		Colonies[n].islandLable = "Mein";
		colonies[n].num = 1;
		colonies[n].map.x = 1370;
		colonies[n].map.y = 505;
		colonies[n].StoreNum   = Maracaibo_STORE;
		colonies[n].from_sea   = "Maracaibo_town";
		colonies[n].Default.BoardLocation = "Maracaibo_ExitTown";
		colonies[n].FortValue = 90; 
				
	
	
	
		n = n + 1;
		Colonies[n].id = "Caracas";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = SPAIN;
		Colonies[n].nation = SPAIN;
		Colonies[n].island = "Caracas";
		Colonies[n].islandLable = "Mein";
		colonies[n].num = 1;
		colonies[n].map.x = 1370;
		colonies[n].map.y = 505;
		colonies[n].StoreNum   = Caracas_STORE;
		colonies[n].from_sea   = "Caracas_town";
		colonies[n].Default.BoardLocation = "Caracas_ExitTown";
		colonies[n].FortValue = 40; 
		
	
	
	
		n = n + 1;
		Colonies[n].id = "Cumana";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = SPAIN;
		Colonies[n].nation = SPAIN;
		Colonies[n].island = "Cumana";
		Colonies[n].islandLable = "Mein";
		colonies[n].num = 1;
		colonies[n].map.x = 1370;
		colonies[n].map.y = 505;
		colonies[n].StoreNum   = Cumana_STORE;
		colonies[n].from_sea   = "Cumana_town";
		colonies[n].Default.BoardLocation = "Cumana_ExitTown";
		colonies[n].FortValue = 75; 
				
	
	
	
		n = n + 1;
		Colonies[n].id = "SantaCatalina";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = ENGLAND;
		Colonies[n].nation = ENGLAND;
		Colonies[n].island = "SantaCatalina";
		Colonies[n].islandLable = "Mein";
		colonies[n].num = 1;
		colonies[n].map.x = 1370;
		colonies[n].map.y = 505;
		colonies[n].StoreNum   = SantaCatalina_STORE;
		colonies[n].from_sea   = "SantaCatalina_town";
		colonies[n].Default.BoardLocation = "SantaCatalina_ExitTown";
		colonies[n].FortValue = 65; 
		
	
	
	
		n = n + 1;
		Colonies[n].id = "Beliz";
		Colonies[n].visible = true;
		Colonies[n].smuggling_nation = ENGLAND;
		Colonies[n].nation = ENGLAND;
		Colonies[n].island = "Beliz";
		Colonies[n].islandLable = "Mein";
		colonies[n].num = 1;
		colonies[n].map.x = 1370;
		colonies[n].map.y = 505;
		colonies[n].StoreNum   = Beliz_STORE;
		colonies[n].from_sea   = "Beliz_town";
		colonies[n].Default.BoardLocation = "Beliz_ExitTown";
		colonies[n].FortValue = 85; 
		
	
	
	
		n = n + 1;
		Colonies[n].id = "Pearl";
		Colonies[n].visible = false;
		Colonies[n].smuggling_nation = "none";
		Colonies[n].nation = "none";
		Colonies[n].island = "Pearl";
		Colonies[n].islandLable = "Pearl";
		colonies[n].num = 1;
		colonies[n].map.x = 1370;
		colonies[n].map.y = 505;
		colonies[n].StoreNum   = Pirates_STORE; 
		colonies[n].from_sea   = "";
		colonies[n].HasNoFort = true;

	
	
	
		n = n + 1;
		Colonies[n].id = "Tenotchitlan";
		Colonies[n].visible = false;
		Colonies[n].smuggling_nation = "none";
		Colonies[n].nation = "none";
		Colonies[n].island = "Tenotchitlan";
		Colonies[n].islandLable = "Tenotchitlan";
		colonies[n].num = 1;
		colonies[n].map.x = 1370;
		colonies[n].map.y = 505;
		colonies[n].StoreNum   = Pirates_STORE; 
		colonies[n].from_sea   = "";
		colonies[n].HasNoFort = true;

	
	
	
		n = n + 1;
		Colonies[n].id = "Minentown";
		Colonies[n].visible = false;
		Colonies[n].smuggling_nation = "none";
		Colonies[n].nation = SPAIN;
		Colonies[n].island = "Minentown";
		Colonies[n].islandLable = "Mein";
		colonies[n].num = 1;
		colonies[n].map.x = 1370;
		colonies[n].map.y = 505;
		colonies[n].StoreNum   = Pirates_STORE; 
		colonies[n].from_sea   = "";
		colonies[n].HasNoFort = true;



	
	
	
		n = n + 1;
		Colonies[n].id = "Dominica";
		Colonies[n].visible = false;
		Colonies[n].smuggling_nation = "none";
		Colonies[n].nation = "none";
		Colonies[n].island = "Dominica";
		Colonies[n].num = "1";
		colonies[n].map.x = 1595;
		colonies[n].map.y = 1250;
		colonies[n].colonylevel = 0;
		colonies[n].StoreNum   = Pirates_STORE; 
		colonies[n].from_sea   = "";
		colonies[n].HasNoFort = true;

	
	
	
		n = n + 1;
		Colonies[n].id = "Terks";
		Colonies[n].visible = false;
		Colonies[n].smuggling_nation = "none";
		Colonies[n].nation = "none";
		Colonies[n].island = "Terks";
		Colonies[n].num = "1";
		colonies[n].map.x = 1605;
		colonies[n].map.y = 1852;
		colonies[n].colonylevel = 0;
		colonies[n].StoreNum   = Pirates_STORE; 
		colonies[n].from_sea   = "";
		colonies[n].HasNoFort = true;

	
	
	
		n = n + 1;
		Colonies[n].id = "Caiman";
		Colonies[n].visible = false;
		Colonies[n].smuggling_nation = "none";
		Colonies[n].nation = "none";
		Colonies[n].island = "Caiman";
		Colonies[n].num = "1";
		colonies[n].map.x = 1605;
		colonies[n].map.y = 1852;
		colonies[n].colonylevel = 0;
		colonies[n].StoreNum   = Pirates_STORE; 
		colonies[n].from_sea   = "";
		colonies[n].HasNoFort = true;

	
	
	
		n = n + 1;
		Colonies[n].id = "LostShipsCity";
		Colonies[n].visible = false;
		Colonies[n].smuggling_nation = "none";
		Colonies[n].nation = "none";
		Colonies[n].island = "LostShipsCity";
		Colonies[n].islandLable = "LostShipsCity";
		Colonies[n].num = "1";
		colonies[n].map.x = 1605;
		colonies[n].map.y = 1852;
		colonies[n].StoreNum   = Pirates_STORE; 
		colonies[n].from_sea   = "LostShipsCity_town";
		colonies[n].HasNoFort = true;
				
	
	
	
		n = n + 1;
		Colonies[n].id = "KhaelRoa";
		Colonies[n].visible = false;
		Colonies[n].smuggling_nation = "none";
		Colonies[n].nation = "none";
		Colonies[n].island = "KhaelRoa";
		Colonies[n].islandLable = "KhaelRoa";
		Colonies[n].num = "1";
		colonies[n].map.x = 1698;
		colonies[n].map.y = 1598;
		colonies[n].colonylevel = 0;
		colonies[n].StoreNum   = Pirates_STORE; 
		colonies[n].from_sea   = "";
		colonies[n].HasNoFort = true;		
		
	
	
	
		n = n + 1;
		Colonies[n].id = "Ksochitam";
		Colonies[n].visible = false;
		Colonies[n].smuggling_nation = "none";
		Colonies[n].nation = "none";
		Colonies[n].island = "Ksochitam";
		Colonies[n].islandLable = "Ksochitam";
		Colonies[n].num = "1";
		colonies[n].map.x = 1698;
		colonies[n].map.y = 1598;
		colonies[n].colonylevel = 0;
		colonies[n].StoreNum   = Pirates_STORE; 
		colonies[n].from_sea   = "";
		colonies[n].HasNoFort = true;				
		
	
	
	
		n = n + 1;
		Colonies[n].id = "RockIsland";
		Colonies[n].visible = false;
		Colonies[n].smuggling_nation = "none";
		Colonies[n].nation = "none";
		Colonies[n].island = "RockIsland";
		Colonies[n].islandLable = "RockIsland";
		Colonies[n].num = "1";
		colonies[n].map.x = 1698;
		colonies[n].map.y = 1598;
		colonies[n].colonylevel = 0;
		colonies[n].StoreNum   = Pirates_STORE; 
		colonies[n].from_sea   = "";
		colonies[n].HasNoFort = true;					
		
	
	
	
		n = n + 1;
		Colonies[n].id = "SantaQuiteria";
		Colonies[n].visible = false;
		Colonies[n].smuggling_nation = "none";
		Colonies[n].nation = "none";
		Colonies[n].island = "SantaQuiteria";
		Colonies[n].islandLable = "SantaQuiteria";
		Colonies[n].num = "1";
		colonies[n].map.x = 1698;
		colonies[n].map.y = 1598;
		colonies[n].colonylevel = 0;
		colonies[n].StoreNum   = Pirates_STORE; 
		colonies[n].from_sea   = "";
		colonies[n].HasNoFort = true;			

	
	
	
		n = n + 1;
		Colonies[n].id = "IslaDeVieques";
		Colonies[n].visible = false;
		Colonies[n].smuggling_nation = "none";
		Colonies[n].nation = "none";
		Colonies[n].island = "IslaDeVieques";
		Colonies[n].islandLable = "IslaDeVieques";
		Colonies[n].num = "1";
		colonies[n].map.x = 1698;
		colonies[n].map.y = 1598;
		colonies[n].colonylevel = 0;
		colonies[n].StoreNum   = Pirates_STORE; 
		colonies[n].from_sea   = "";
		colonies[n].HasNoFort = true;			
	
	
	
	
		n = n + 1;
		Colonies[n].id = "Is";
		Colonies[n].visible = false;
		Colonies[n].smuggling_nation = "none";
		Colonies[n].nation = "none";
		Colonies[n].island = "IslaMona";
		Colonies[n].islandLable = "IslaMona";
		Colonies[n].num = "1";
		colonies[n].map.x = 1698;
		colonies[n].map.y = 1598;
		colonies[n].colonylevel = 0;
		colonies[n].StoreNum   = Pirates_STORE; 
		colonies[n].from_sea   = "";
		colonies[n].HasNoFort = true;				
		
	
	
	
		n = n + 1;
		Colonies[n].id = "Is";
		Colonies[n].visible = false;
		Colonies[n].smuggling_nation = "none";
		Colonies[n].nation = "none";
		Colonies[n].island = "IslaDeCoche";
		Colonies[n].islandLable = "IslaDeCoche";
		Colonies[n].num = "1";
		colonies[n].map.x = 1698;
		colonies[n].map.y = 1598;
		colonies[n].colonylevel = 0;
		colonies[n].StoreNum   = Pirates_STORE; 
		colonies[n].from_sea   = "";
		colonies[n].HasNoFort = true;

	
	
	
		n = n + 1;
		Colonies[n].id = "SanAndres";
		Colonies[n].visible = false;
		Colonies[n].smuggling_nation = SPAIN;
		Colonies[n].nation = SPAIN;
		Colonies[n].island = "Providence";
		Colonies[n].islandLable = "Providence";
		Colonies[n].num = "1";
		colonies[n].map.x = 1605;
		colonies[n].map.y = 1852;
		colonies[n].StoreNum   = SanAndres_STORE; 
		colonies[n].from_sea   = "SanAndres_town";
		colonies[n].Default.BoardLocation = "SanAndres_ExitTown";
		colonies[n].FortValue = 80; 		
		colonies[n].DontSetShipInPort = true; 
} 
