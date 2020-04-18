 

#include "worldmap\worldmap_globals.c"
#include "worldmap\worldmap_events.c"
#include "worldmap\worldmap_reload.c"
#include "worldmap\worldmap_encgen.c"
#include "worldmap\worldmap_coords.c"





#event_handler("WorldMap_EncounterCreate", "wdmEvent_EncounterCreate");
#event_handler("WorldMap_PlayerInStorm", "wdmEvent_PlayerInStorm");
#event_handler("WorldMap_ShipEncounter", "wdmEvent_ShipEncounter");
#event_handler("WorldMap_UpdateDate", "wdmEvent_UpdateDate");
#event_handler("ExitFromWorldMap", "wdmReloadToSea");


#event_handler("EventTimeUpdate", "wdmTimeUpdate");







void wdmCreateMap(float x, float z, float ay)
{
	
	float zeroX = MakeFloat(worldMap.zeroX);
	float zeroZ = MakeFloat(worldMap.zeroZ);
	float ShipX, ShipZ;
	
	int scale = WDM_MAP_TO_SEA_SCALE;
	if (worldMap.island == "Cuba1" || worldMap.island == "Cuba2" || worldMap.island == "Beliz" || worldMap.island == "SantaCatalina" 
		|| worldMap.island == "PortoBello" || worldMap.island == "Cartahena" || worldMap.island == "Maracaibo"
		|| worldMap.island == "Caracas" || worldMap.island == "Cumana")
	{
		scale = 25;
	}
	shipX = (x/scale) + zeroX;
	shipZ = (z/scale) + zeroZ;
	worldMap.playerShipX = (x/scale) + zeroX;
	worldMap.playerShipZ = (z/scale) + zeroZ;
	worldMap.playerShipAY = ay;

	
	wdmCreateWorldMap();
}

void wdmTimeUpdate()
{
	
	
	QuestsCheck();
	PostEvent("EventTimeUpdate", 5000);
	
}

void wdmCreateWorldMap()
{
	
    
	worldMap.date.hourPerSec = 1.5 / 1.5;

	wdmLockReload = false;
	
	ClearAllLogStrings();
	
	ReloadProgressStart();
	
	worldMap.date.monthnames.m01 = XI_ConvertString("target_month_1");
	worldMap.date.monthnames.m02 = XI_ConvertString("target_month_2");
	worldMap.date.monthnames.m03 = XI_ConvertString("target_month_3");
	worldMap.date.monthnames.m04 = XI_ConvertString("target_month_4");
	worldMap.date.monthnames.m05 = XI_ConvertString("target_month_5");
	worldMap.date.monthnames.m06 = XI_ConvertString("target_month_6");
	worldMap.date.monthnames.m07 = XI_ConvertString("target_month_7");
	worldMap.date.monthnames.m08 = XI_ConvertString("target_month_8");
	worldMap.date.monthnames.m09 = XI_ConvertString("target_month_9");
	worldMap.date.monthnames.m10 = XI_ConvertString("target_month_10");
	worldMap.date.monthnames.m11 = XI_ConvertString("target_month_11");
	worldMap.date.monthnames.m12 = XI_ConvertString("target_month_12");
	worldMap.date.font = "normal";
	worldMap.date.coordinate = XI_ConvertString("Coordinates");
	
	wdmRemoveOldEncounters();



	worldMap.playerInStorm = "0";
	
	wdmReset();
	
	CreateEntity(&worldMap,"worldmap");
	worldMap.isLoaded = "true";
	
	worldMap.update = "";
	
	CreateEntity(&wdm_fader, "fader");
	if(IsEntity(wdm_fader) == 0) Trace("Fader not created!!!");	
	float fadeInTime = 0.5;
	SendMessage(&wdm_fader, "lfl", FADER_IN, fadeInTime, true);
	SendMessage(&wdm_fader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
	SendMessage(&wdm_fader, "ls",FADER_PICTURE,"loading\sea_0" + rand(2) + ".tga");	
	
	SetSchemeForMap();
	
	PostEvent("EventWorldMapInit", 830); 
	ReloadProgressEnd();
	PostEvent("EventTimeUpdate", 1000);	
	
	worldMap.addQuestEncounters = "updateQuest";
	wdmSetNationFlag(sti(pchar.nation));
	InitWmInterface();
}

void wdmLoadSavedMap()
{
	
	wdmCreateWorldMap();
}

void wdmRemoveOldEncounters()
{
	
	wdmMarkDeleteEncounters();
	
	aref encs;
	makearef(encs, worldMap.encounters);
	int num = GetAttributesNum(encs);
	object forDelete;
	string attr, encID;
	int count = 0;
	for(int i = 0; i < num; i++)
	{
		aref enc = GetAttributeN(encs, i);
		if(CheckAttribute(enc, "needDelete") != 0)
		{
			attr = "del" + count;
			forDelete.(attr) = GetAttributeName(enc);
			count = count + 1;
		}
	}
	for(i = 0; i < count; i++)
	{
		attr = "del" + i;
		encID = "encounters." + forDelete.(attr);
		DeleteAttribute(&worldMap, encID);
	}
}

float wdmGetDays(int year, int month, int day, int hour)
{
	
	if(year < 0) year = 0;
	if(year > 3000) year = 3000;
	year = year*365;
	
	for(int i = 1; i < month; i++)
	{
		day = day + GetMonthDays(i);
	}
	
	float days = year + day + (hour/24.0);
	return days;
}

void wdmSetNationFlag(int iNation)
{
	int Nation;
	if(isEntity(worldMap))
	{
		switch(iNation)
		{
			case ENGLAND 	: Nation = 1; break;			
			case FRANCE 	: Nation = 2; break;
			case SPAIN		: Nation = 3; break;
			case HOLLAND	: Nation = 0; break;
			case PIRATE		: Nation = 4; break;
		}
		SendMessage(&worldMap, "ll", MSG_WORLDMAP_SET_NATION_FLAG, Nation);
	}
}

void wdmMarkDeleteEncounters()
{
	
	int year = sti(worldMap.date.year);
	int month = sti(worldMap.date.month);
	int day = sti(worldMap.date.day);
	int hour = sti(worldMap.date.hour);
	float days = wdmGetDays(year, month, day, hour);
	int encYear, encMonth, encDay, encHour;
	
	aref encs;
	makearef(encs, worldMap.encounters);
	int num = GetAttributesNum(encs);
	for(int i = 0; i < num; i++)
	{
		aref enc = GetAttributeN(encs, i);
		if(CheckAttribute(enc, "Quest") != 0)
		{
			continue;
		}
		bool deleteMe = false;
		if(CheckAttribute(enc, "year") != 0)
		{
			encYear = sti(enc.year);
		}else{
			deleteMe = true;
		}
		if(CheckAttribute(enc, "month") != 0)
		{
			encMonth = sti(enc.month);
		}else{
			deleteMe = true;
		}
		if(CheckAttribute(enc, "day") != 0)
		{
			encDay = sti(enc.day);
		}else{
			deleteMe = true;
		}
		if(CheckAttribute(enc, "hour") != 0)
		{
			encHour = sti(enc.hour);
		}else{
			deleteMe = true;
		}
		if(deleteMe != true)
		{
			float deltaDays = wdmGetDays(encYear, encMonth, encDay, encHour) - days;
			if(deltaDays < 0)
			{
				deltaDays = -deltaDays;
			}
			if(deltaDays > 1.0)
			{
				deleteMe = true;
			}
		}
		if(deleteMe != false)
		{
			enc.needDelete = "Time delete";
		}
	}
}
