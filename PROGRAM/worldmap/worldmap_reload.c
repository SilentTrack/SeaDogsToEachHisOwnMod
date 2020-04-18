

object wdmLoginToSea;
object wdm_fader;
bool wdmLockReload = false;
bool questwdmLockReload = false;

void wdmReloadToSea()
{
	
	if(wdmLockReload)
	{
		return;
	}
	if(questwdmLockReload)
	{
		Log_Info("You can't leave to the war map right now");
		return;
	}
	
	EmptyAllFantomCharacter();
	PGG_DailyUpdate();
	Siege_DailyUpdate();
	SaveCurrentQuestDateParam("WordMapEncounters_DailyUpdate"); 
	
	
	wdmLockReload = true;
	
	SetReloadNextTipsImage();
	
	DeleteAttribute(&wdmLoginToSea, "");
	
	worldMap.encounter.type = "";
	worldMap.playerShipUpdate = "";
	worldMap.info.updateinfo = "";
	
	WdmAddPlayerGroup();
	
	bool isShipEncounterType;
	isShipEncounterType = WdmAddEncountersData();
	
	SendMessage(&worldMap, "l", MSG_WORLDMAP_CREATEENC_RELEASE);
	
	WdmStormEncounter();
	
	worldMap.deleteUpdate = "";
	
	SetEventHandler("FaderEvent_StartFade", "WdmStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "WdmEndFade", 0);
	wdm_fader.thisWorldMapFader = "";
	CreateEntity(&wdm_fader, "fader");
	if(IsEntity(wdm_fader) == 0) Trace("Fader not created!!!");	
	float fadeOutTime = 0.5;
	SendMessage(&wdm_fader, "lfl", FADER_OUT, fadeOutTime, true);
	SendMessage(&wdm_fader, "l", FADER_STARTFRAME);
	
	string imageName = "loading\sea_0" + rand(2) + ".tga";
	if(isShipEncounterType)
	{
		imageName = RandPhraseSimple("loading\battle.tga", "loading\shipcannon.tga"));
	}
	if(MakeInt(wdmLoginToSea.storm) != 0)
	{
		imageName = "loading\Storm.tga";
		  
	}
	wdmLoginToSea.imageName = imageName;
	SendMessage(&wdm_fader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
	SendMessage(&wdm_fader, "ls",FADER_PICTURE, imageName);
}

void WdmStartFade()
{
	PauseAllSounds();
	
	DelEventHandler("FaderEvent_StartFade", "WdmStartFade");
	
	worldMap.playerShipUpdate = "";
	DeleteClass(&worldMap);
	worldMap.isLoaded = "false";
	DeleteWmInterface();
}

void WdmEndFade()
{
	int a = GetEventData();
	aref reload_fader = GetEventData();
	
	DelEventHandler("FaderEvent_EndFade", "WdmEndFade");
	
	ReloadProgressStart();	
	SeaLogin(&wdmLoginToSea);
	LayerAddObject(SEA_REALIZE, &reload_fader, -1);
	ReloadProgressEnd();
}

void QuitFromWorldMap()
{
	
	SetEventHandler("FaderEvent_StartFade", "WdmStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "WdmEndFadeA", 0);
	wdm_fader.thisWorldMapFader = "";
	CreateEntity(&wdm_fader, "fader");
	if(IsEntity(wdm_fader) == 0) Trace("Fader not created!!!");	
	float fadeOutTime = 0.5;
	SendMessage(&wdm_fader, "lfl", FADER_OUT, fadeOutTime, true);
	SendMessage(&wdm_fader, "l", FADER_STARTFRAME);
}

void WdmEndFadeA()
{
	
	DelEventHandler("FaderEvent_EndFade", "WdmEndFadeA");
	
	Event("QuitFromWorldMap");

}


void WdmPrepareMapForAbordage(aref arPos)
{
	
	float psX = MakeFloat(worldMap.playerShipX);
	float psZ = MakeFloat(worldMap.playerShipZ);
	
	if(worldMap.island != WDM_NONE_ISLAND)
	{
		
		wdmLoginToSea.island = worldMap.island;
		float ix = MakeFloat(worldMap.island.x);
		float iz = MakeFloat(worldMap.island.z);
		int scale = WDM_MAP_TO_SEA_SCALE;
		if (worldMap.island == "Cuba1" || worldMap.island == "Cuba2" || worldMap.island == "Beliz" || worldMap.island == "SantaCatalina"
			|| worldMap.island == "PortoBello" || worldMap.island == "Cartahena" || worldMap.island == "Maracaibo"
			|| worldMap.island == "Caracas" || worldMap.island == "Cumana")
		{
			scale = 25;
		}
		arPos.x = (psX - ix)*scale;
		arPos.z = (psZ - iz)*scale;
		arPos.y = worldMap.playerShipAY;
		worldMap.zeroX = ix;
		worldMap.zeroZ = iz;
	}else{
		
		wdmLoginToSea.island = "";
		
		arPos.x = 0;
		arPos.z = 0;
		arPos.y = worldMap.playerShipAY;
		worldMap.zeroX = worldMap.playerShipX;
		worldMap.zeroZ = worldMap.playerShipZ;
	}
}

void WdmAddPlayerGroup()
{
	
	float psX = MakeFloat(worldMap.playerShipX);
	float psZ = MakeFloat(worldMap.playerShipZ);
	
	
	
	
	
	
	if(worldMap.island != WDM_NONE_ISLAND)
	{
		
		wdmLoginToSea.island = worldMap.island;
		float ix = MakeFloat(worldMap.island.x);
		float iz = MakeFloat(worldMap.island.z);
		int scale = WDM_MAP_TO_SEA_SCALE;
		if (worldMap.island == "Cuba1" || worldMap.island == "Cuba2" || worldMap.island == "Beliz" || worldMap.island == "SantaCatalina"
			|| worldMap.island == "PortoBello" || worldMap.island == "Cartahena" || worldMap.island == "Maracaibo" 
			|| worldMap.island == "Caracas" || worldMap.island == "Cumana")
		{
			scale = 25;
		}
		wdmLoginToSea.playerGroup.x = (psX - ix)*scale;
		wdmLoginToSea.playerGroup.z = (psZ - iz)*scale;
		wdmLoginToSea.playerGroup.ay = worldMap.playerShipAY;
		worldMap.zeroX = ix;
		worldMap.zeroZ = iz;
	}else{
		
		wdmLoginToSea.island = "";
		
		wdmLoginToSea.playerGroup.x = 0;
		wdmLoginToSea.playerGroup.z = 0;
		wdmLoginToSea.playerGroup.ay = worldMap.playerShipAY;
		worldMap.zeroX = worldMap.playerShipX;
		worldMap.zeroZ = worldMap.playerShipZ;
	}
}

bool WdmAddEncountersData()
{
	bool isShipEncounter = false;
	
	ReleaseMapEncounters();
	
	int numEncounters = wdmGetNumberShipEncounters();
	
	float mpsX = MakeFloat(worldMap.playerShipX);
	float mpsZ = MakeFloat(worldMap.playerShipZ);
	
	float wpsX = MakeFloat(wdmLoginToSea.playerGroup.x);
	float wpsZ = MakeFloat(wdmLoginToSea.playerGroup.z);
	
	for(int i = 0; i < numEncounters; i++)
	{
		
		if(wdmSetCurrentShipData(i))
		{
			
			if(MakeInt(worldMap.encounter.select) == 0) continue;
			
			string encStringID = worldMap.encounter.id;
			if(encStringID == "") continue;
			encStringID = "encounters." + encStringID + ".encdata";
			if(CheckAttribute(&worldMap, encStringID) == 0) continue;
			int mapEncSlot = FindFreeMapEncounterSlot();
			if(mapEncSlot < 0) continue;
			ref mapEncSlotRef = GetMapEncounterRef(mapEncSlot);
			aref encDataForSlot;
			makearef(encDataForSlot, worldMap.(encStringID));
			CopyAttributes(mapEncSlotRef, encDataForSlot);
			
			isShipEncounter = true;
			
			string grp; grp = "group" + i;
			float encX = MakeFloat(worldMap.encounter.x);
			float encZ = MakeFloat(worldMap.encounter.z);
			wdmLoginToSea.encounters.(grp).x = wpsX + (encX - mpsX)*WDM_MAP_ENCOUNTERS_TO_SEA_SCALE;
			wdmLoginToSea.encounters.(grp).z = wpsZ + (encZ - mpsZ)*WDM_MAP_ENCOUNTERS_TO_SEA_SCALE;
			wdmLoginToSea.encounters.(grp).ay = worldMap.encounter.ay;
			wdmLoginToSea.encounters.(grp).type = mapEncSlot;
			wdmLoginToSea.encounters.(grp).id = worldMap.encounter.id;
			
			encStringID = worldMap.encounter.id;
			encStringID = "encounters." + encStringID;
			if(CheckAttribute(&worldMap, encStringID + ".quest") == 0)
			{			
				worldMap.(encStringID).needDelete = "Reload delete non quest encounter";
			}
		}
	}
	return isShipEncounter;
}

void WdmStormEncounter()
{
	wdmLoginToSea.storm = worldMap.playerInStorm;
	if(MakeInt(wdmLoginToSea.storm) != 0)
	{
		wdmLoginToSea.tornado = worldMap.stormWhithTornado;
	}else{
		wdmLoginToSea.tornado = "0";
	}

	

	if(CheckAttribute(&worldMap, "stormId") != 0)
	{
		if(worldMap.stormId != "")
		{
			string encStringID = worldMap.stormId;
			encStringID = "encounters." + encStringID;
			worldMap.(encStringID).needDelete = "Reload delete storm";
		}
	}	
}
