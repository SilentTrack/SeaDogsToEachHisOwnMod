#define WDM_MAP_TO_SEA_SCALE				50
#define WDM_MAP_ENCOUNTERS_TO_SEA_SCALE		25	

#define WDM_NONE_ISLAND				""

#define WDM_ETYPE_MERCHANT	0
#define WDM_ETYPE_FOLLOW	1
#define WDM_ETYPE_WARRING	2
#define WDM_ETYPE_SPECIAL	3


object worldMap;







void Map_CreateTrader(string beginlocator, string endLocator, string characterID, int TimeOut)  
{
	aref encField = wdmFindOrCreateQuestEncounter(characterID); 
	encField.type = "trader";
	encField.characterID = characterID;
	encField.beginlocator = beginlocator;
	encField.endLocator = endLocator;
	encField.TimeOut = TimeOut; 
	worldMap.addQuestEncounters = "updateQuest";
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		pchar.worldmap.shipcounter = 0;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) + 1;
}




void Map_CreateTraderXZ(float x1, float z1, float x2, float z2, string characterID, int TimeOut)  
{
	aref encField = wdmFindOrCreateQuestEncounter(characterID); 
	encField.type = "trader";
	encField.XZGoto = true;
	encField.characterID = characterID;
	encField.x1 = x1;
	encField.z1 = z1;
	encField.x2 = x2;
	encField.z2 = z2;
	encField.TimeOut = TimeOut; 
	worldMap.addQuestEncounters = "updateQuest";
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		pchar.worldmap.shipcounter = 0;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) + 1;
}


void Map_CreateCoolTrader(string beginlocator, string endLocator, string characterID, int TimeOut, float sp)  
{
	aref encField = wdmFindOrCreateQuestEncounter(characterID); 
	encField.type = "cooltrader";
	encField.characterID = characterID;
	encField.beginlocator = beginlocator;
	encField.endLocator = endLocator;
	encField.TimeOut = TimeOut; 
	encField.speed = sp;
	worldMap.addQuestEncounters = "updateQuest";
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		pchar.worldmap.shipcounter = 0;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) + 1;
}



void Map_CreateWarrior(string beginLocator, string characterID, int TimeOut)
{
	aref encField = wdmFindOrCreateQuestEncounter(characterID);
	encField.type = "warrior";
	encField.characterID = characterID;
	encField.beginlocator = beginlocator;
	encField.TimeOut = TimeOut;
	worldMap.addQuestEncounters = "updateQuest";
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		pchar.worldmap.shipcounter = 0;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) + 1;
}


void Map_CreateCoolWarrior(string beginLocator, string characterID, int TimeOut)
{
	aref encField = wdmFindOrCreateQuestEncounter(characterID);
	encField.type = "coolwarrior";
	encField.characterID = characterID;
	encField.beginlocator = beginlocator;
	encField.TimeOut = TimeOut;
	worldMap.addQuestEncounters = "updateQuest";
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		pchar.worldmap.shipcounter = 0;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) + 1;
}



void Map_CreateBattle(string characterID, int iEnemyNation, int TimeOut)
{
	aref encField = wdmFindOrCreateQuestEncounter(characterID);
	encField.type = "battle";
	encField.characterID = characterID;
	encField.iEnemyNation = iEnemyNation;
	encField.TimeOut = TimeOut;
	worldMap.addQuestEncounters = "updateQuest";
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		pchar.worldmap.shipcounter = 0;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) + 1;
}


void Map_ReleaseQuestEncounter(string characterID)
{
	
	aref encs, at;
	string aname;
	makearef(encs, worldMap.addQuestEncounters);
	int num = GetAttributesNum(encs);
	for(int cnt = 0; cnt < num; cnt++)
	{
		for(int i = 0; i < num; i++)
		{
			at = GetAttributeN(encs, i);
			aname = GetAttributeName(at);
			aname = "addQuestEncounters." + aname + ".characterID";
			if(worldMap.(aname) == characterID)
			{
				DeleteAttribute(&worldMap, aname);
				break;
			}
		}
		if(i >= num)
		{
			break;
		}
	}
	
	makearef(encs, worldMap.encounters);
	num = GetAttributesNum(encs);
	for(i = 0; i < num; i++)
	{
		aref enc = GetAttributeN(encs, i);
		if(CheckAttribute(enc, "quest.chrID") == 0) continue;
		if(enc.quest.chrID == characterID)
		{
			wdmDeleteLoginEncounter(GetAttributeName(enc));
		}
        num--; 
        i--;
	}
	worldMap.deleteUpdate = "";
}







int wdmGetNumberStorms()
{
	return MakeInt(worldMap.storm.num);
}



int wdmGetNumberShipEncounters()
{
	return MakeInt(worldMap.encounter.num);
}

bool wdmSetCurrentShipData(int shipIndex)
{
	worldMap.encounter.cur = shipIndex;
	int i = MakeInt(worldMap.encounter.cur);
	if(i < 0 || i != shipIndex) return 0;
	return 1;
}




bool wdmCreateSpecial(float kSpeed)
{
	
	int i1 = -1;
	int i2 = -1;
	
	if(GenerateMapEncounter(WDM_ETYPE_SPECIAL, worldMap.island, &i1, &i2) == false) return false;
	string encID = "";
	bool res = wdmCreateSpecialByIndex(kSpeed, i1, &encID, "", "", 5+rand(5)); 
	
	
	ReleaseMapEncounters();
	return res;
}


bool wdmCreateSpecialByIndex(float kSpeed, int index, ref encID, string from, string to, int timeOutInDays)  
{
	
	string nationShipName = wdmEncounterModelName(index);
	
	ref mapEncSlotRef = GetMapEncounterRef(index);
	
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec); 
	float timeOutInSec = daysPerSec*timeOutInDays;
	
	bool res = SendMessage(&worldMap, "lsssff", MSG_WORLDMAP_CREATEENC_MER, nationShipName, from, to, kSpeed, timeOutInSec);
	
	
	WdmCopyEncounterData(mapEncSlotRef, worldMap.EncounterID1);
	
	encID = worldMap.EncounterID1;
	return res;
}


bool wdmCreateMerchantShip(float kSpeed)
{
	
	int i1 = -1;
	int i2 = -1;
	if(GenerateMapEncounter(WDM_ETYPE_MERCHANT, worldMap.island, &i1, &i2) == false) return false;
	
	string encID = "";
	bool res = wdmCreateMerchantShipByIndex(kSpeed, i1, &encID, "", "", 5+rand(5)); 
	
	ReleaseMapEncounters();
	return res;
}


bool wdmCreateMerchantShipByIndex(float kSpeed, int index, ref encID, string from, string to, int timeOutInDays)  
{
	
	string nationShipName = wdmEncounterModelName(index);
	
	ref mapEncSlotRef = GetMapEncounterRef(index);
	
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec); 
	float timeOutInSec = daysPerSec*timeOutInDays;
	
	bool res = SendMessage(&worldMap, "lsssff", MSG_WORLDMAP_CREATEENC_MER, nationShipName, from, to, kSpeed, timeOutInSec);
	
	
	WdmCopyEncounterData(mapEncSlotRef, worldMap.EncounterID1);
	
	encID = worldMap.EncounterID1;
	return res;
}

bool wdmCreateMerchantShipXZByIndex(float kSpeed, int index, ref encID, float x1, float z1, float x2, float z2, int timeOutInDays)  
{
	
	string nationShipName = wdmEncounterModelName(index);
	
	ref mapEncSlotRef = GetMapEncounterRef(index);
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec); 
	float timeOutInSec = daysPerSec*timeOutInDays;
	
	bool res = SendMessage(&worldMap, "lsffffff", MSG_WORLDMAP_CREATEENC_MER_XZ, nationShipName, x1, z1, x2, z2, kSpeed, timeOutInSec);
	
	WdmCopyEncounterData(mapEncSlotRef, worldMap.EncounterID1);
	
	encID = worldMap.EncounterID1;
	return res;
}


bool wdmCreateFollowShip(float kSpeed)
{
	
	int i1 = -1;
	int i2 = -1;
	if(GenerateMapEncounter(WDM_ETYPE_FOLLOW, worldMap.island, &i1, &i2) == false) return false;
	
	string encID = "";
	bool res = wdmCreateFollowShipByIndex(kSpeed, i1, &encID, 5+rand(5)); 
	
	ReleaseMapEncounters();
	return res;
}


bool wdmCreateFollowShipByIndex(float kSpeed, int index, ref encID, int timeOutInDays)
{
	
	string nationShipName = wdmEncounterModelName(index);
	
	ref n = GetMapEncounterRef(index);
	int iNation = PIRATE;
	if(CheckAttribute(n, "nation"))
	{
		iNation = sti(n.Nation);
	}
	
	ref mapEncSlotRef = GetMapEncounterRef(index);
	
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec); 
	float timeOutInSec = daysPerSec*timeOutInDays;
	
	bool res = false;
	bool klas = (IsCharacterPerkOn(pchar,"SeaDogProfessional")) && (GetCharacterShipClass(pchar) < 5);
	if (klas || (GetNationRelation2MainCharacter(iNation) != RELATION_ENEMY))
	{
		res = SendMessage(&worldMap, "lsssff", MSG_WORLDMAP_CREATEENC_MER, nationShipName, "", "", kSpeed, timeOutInSec); 
	}
	else
	{   
		
		res = SendMessage(&worldMap, "lsff", MSG_WORLDMAP_CREATEENC_FLW, nationShipName, kSpeed, timeOutInSec);
	}
	
	WdmCopyEncounterData(mapEncSlotRef, worldMap.EncounterID1);
	encID = worldMap.EncounterID1;
	return res;
}


bool wdmCreateRealFollowShipByIndex(float kSpeed, int index, ref encID, int timeOutInDays)
{
	
	string nationShipName = wdmEncounterModelName(index);
	
	ref n = GetMapEncounterRef(index);
	int iNation = PIRATE;
	if(CheckAttribute(n, "nation"))
	{
		iNation = sti(n.Nation);
	}
	
	ref mapEncSlotRef = GetMapEncounterRef(index);
	
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec); 
	float timeOutInSec = daysPerSec*timeOutInDays;
	
	bool res = false;
	   
		res = SendMessage(&worldMap, "lsff", MSG_WORLDMAP_CREATEENC_FLW, nationShipName, kSpeed, timeOutInSec);
	
	
	WdmCopyEncounterData(mapEncSlotRef, worldMap.EncounterID1);
	encID = worldMap.EncounterID1;
	return res;
}


bool wdmCreateWarringShips()
{
	
	int i1 = -1;
	int i2 = -1;
	if(GenerateMapEncounter(WDM_ETYPE_WARRING, worldMap.island, &i1, &i2) == false) 
	{
		ReleaseMapEncounters();
		return false;
	}
	
	string encID1 = "";
	string encID2 = "";
	bool res = wdmCreateWarringShipsByIndex(i1, i2, &encID1, &encID2, 5+rand(5));  
	
	ReleaseMapEncounters();
	return res;
}


bool wdmCreateWarringShipsByIndex(int index1, int index2, ref encID1, ref encID2, int timeOutInDays)
{
	
	string nationShipName1 = wdmEncounterModelName(index1);
	string nationShipName2 = wdmEncounterModelName(index2);
	
	ref mapEncSlotRef1 = GetMapEncounterRef(index1);
	ref mapEncSlotRef2 = GetMapEncounterRef(index2);
	
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec); 
	float timeOutInSec = daysPerSec*timeOutInDays;
	
	bool res = SendMessage(&worldMap, "lssf", MSG_WORLDMAP_CREATEENC_WAR, nationShipName1, nationShipName2, timeOutInSec);
	
	WdmCopyEncounterData(mapEncSlotRef1, worldMap.EncounterID1);
	WdmCopyEncounterData(mapEncSlotRef2, worldMap.EncounterID2);
	encID1 = worldMap.EncounterID1;
	encID2 = worldMap.EncounterID2;
	return res;
}


void wdmCreateStorm()
{
    if(CheckAttribute(pchar,"worldmapencountersoff") == 1)
	{  
		if(sti(pchar.worldmapencountersoff)) return;
	}
	int isTornado = 0;
	if(worldMap.island == WDM_NONE_ISLAND)
	{
		int r = rand(1000);
		if(r != 0)
		{
			if(r < 450)
			{
				isTornado = 1;
			}
		}
	}
	
	isTornado = 1;
	
	SendMessage(&worldMap, "ll", MSG_WORLDMAP_CREATESTORM, isTornado);
}


string wdmEncounterModelName(int encIndex)
{
	ref n = GetMapEncounterRef(encIndex);
	if(CheckAttribute(n, "worldMapShip") != 0)
	{
		return n.worldMapShip;
	}
	return "ship";
}


void WdmCopyEncounterData(ref mapEncSlotRef, string encStringID)
{
	encStringID = "encounters." + encStringID + ".encdata";
	worldMap.(encStringID) = "";
	aref destRef;
	makearef(destRef, worldMap.(encStringID));
	CopyAttributes(destRef, mapEncSlotRef);
}


aref wdmCreateNewQuestEncDescription()
{
	string gname, aname;
	aref encs, at;
	makearef(encs, worldMap.addQuestEncounters);
	int num = GetAttributesNum(encs);
	for(int cnt = 0; cnt < num + 10; cnt++)
	{	
		gname = "e" + cnt;
		for(int i = 0; i < num; i++)
		{
			at = GetAttributeN(encs, i);
			aname = GetAttributeName(at);
			if(aname == gname)
			{
				break;
			}
		}
		if(i >= num)
		{
			break;
		}
	}
	aref retVal;
	makearef(retVal, worldMap.addQuestEncounters.(gname));
	return retVal;
}


void  wdmEmptyAllDeadQuestEncounter()
{
    aref encs;
    string sdel,aname;
	bool isWMap = IsEntity(worldMap);
	
    makearef(encs, worldMap.encounters);

    int num = GetAttributesNum(encs);
    for(int i = 0; i < num; i++)
    {
        aref enc = GetAttributeN(encs, i);
        if(CheckAttribute(enc, "quest.chrID"))
        {
            int iChar = GetCharacterIndex(enc.quest.chrID)
            sdel  = "encounters."+GetAttributeName(enc);
            if (iChar == -1 || CharacterIsDead(&characters[iChar]))
            {
	            if (!isWMap)
				{
					DeleteAttribute(&worldMap, sdel);
	                num = GetAttributesNum(encs);
	                pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	            }
	            else
	            {
	            	 enc.livetime = 0;
	            }
	        }
        }
    }

   	makearef(encs, worldMap.addQuestEncounters);
    num = GetAttributesNum(encs);
	for(i = 0; i < num; i++)
	{
		aref at = GetAttributeN(encs, i);
		sdel = GetAttributeName(at);
		aname = "addQuestEncounters." + sdel + ".characterID";
		if (CheckAttribute(&worldMap, aname))
		{
	        iChar = GetCharacterIndex(worldMap.(aname));
	        if (iChar == -1 || CharacterIsDead(&characters[iChar]))
	        {
	            DeleteAttribute(&worldMap, "addQuestEncounters." + sdel);
	            num = GetAttributesNum(encs);
	            pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	        }
        }
    }
}


void  wdmEmptyAllOldEncounter()
{
    aref encs;
    string sdel,aname;
	bool isWMap = IsEntity(worldMap);

    makearef(encs, worldMap.encounters);

    int num = GetAttributesNum(encs);
    aref enc;
    int  i;
    
    for (i = 0; i < num; i++)
    {
        enc = GetAttributeN(encs, i);
        if (CheckAttribute(enc, "needDelete") && enc.needDelete == "wdmEncounterDelete")
        {
	        sdel  = "encounters."+GetAttributeName(enc);
			DeleteAttribute(&worldMap, sdel);
	        num--; 
	        i--;
	        if (CheckAttribute(enc, "quest")) pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
        }
    }
}

void  wdmUpdateAllEncounterLivetime()
{
    aref encs;
    int ihours;
    string sdel;
    float b,k;
    if(!actLoadFlag)
    {
		ihours = GetQuestPastTimeParam("WordMapEncounters_DailyUpdate");
		if (ihours > 0)
		{
            Log_TestInfo("������ ���� : "+makeint(ihours/24.0));
            float timeOutInSec = ihours/stf(worldMap.date.hourPerSec);

            makearef(encs, worldMap.encounters);
            int num = GetAttributesNum(encs);
            aref enc;
            int  i;

            for (i = 0; i < num; i++)
            {
                enc = GetAttributeN(encs, i);          
                if (CheckAttribute(enc, "livetime") && CheckAttribute(enc, "quest"))
                {
                    Log_TestInfo(enc.livetime+" - "+timeOutInSec+" : "+stf(stf(enc.livetime) - timeOutInSec));
                     
                    enc.livetime = stf(stf(enc.livetime) - timeOutInSec);
                    DeleteAttribute(enc, "quest.event"); 

                    if (sti(enc.livetime)<=0)
                    {
                        
						Map_TraderSucces_quest(enc.quest.chrID); 
               	        sdel  = "encounters."+GetAttributeName(enc);
                        DeleteAttribute(&worldMap, sdel);
						pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
						num--;
						i--;
                    }
                }
            }
		}
	}
}



aref  wdmFindOrCreateQuestEncounter(string _chrId)
{
    aref encs;
    string sdel,aname;
	bool isWMap = IsEntity(worldMap);

    makearef(encs, worldMap.encounters);

    int num = GetAttributesNum(encs);
    for(int i = 0; i < num; i++)
    {
        aref enc = GetAttributeN(encs, i);
        if (CheckAttribute(enc, "quest.chrID"))
        {
            int iChar = GetCharacterIndex(enc.quest.chrID)
            sdel  = "encounters."+GetAttributeName(enc);
            if (iChar == -1 || characters[iChar].id == _chrId)
            {
	            if (!isWMap)
				{
					DeleteAttribute(&worldMap, sdel);
	                num = GetAttributesNum(encs);
	                pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	            }
	            else
	            {
	            	 enc.livetime = 0;
	            }
	        }
        }
    }

   	makearef(encs, worldMap.addQuestEncounters);
    num = GetAttributesNum(encs);
	for(i = 0; i < num; i++)
	{
		aref at = GetAttributeN(encs, i);
		sdel = GetAttributeName(at);
		aname = "addQuestEncounters." + sdel + ".characterID";
		if (CheckAttribute(&worldMap, aname))
		{
	        iChar = GetCharacterIndex(worldMap.(aname));
	        if (iChar == -1 || characters[iChar].id == _chrId)
	        {
	            DeleteAttribute(&worldMap, "addQuestEncounters." + sdel);
	            num = GetAttributesNum(encs);
	            pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	        }
        }
    }

	return wdmCreateNewQuestEncDescription();
}
