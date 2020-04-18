




void wdmEvent_EncounterCreate()
{
	float dltTime = GetEventData();
	float playerShipX = GetEventData();
	float playerShipZ = GetEventData();
	float playerShipAY = GetEventData();
	
	if(CheckAttribute(worldMap, "noenc") != 0)
	{
		if(worldMap.noenc == "true") return;
	}
	
	worldMap.playerShipX = playerShipX;
	worldMap.playerShipZ = playerShipZ;
	worldMap.playerShipAY = playerShipAY;
	
	
	wdmStormGen(dltTime, playerShipX, playerShipZ, playerShipAY);
	wdmShipEncounter(dltTime, playerShipX, playerShipZ, playerShipAY);
}


void wdmEvent_PlayerInStorm()
{
	float playerShipX = GetEventData();
	float playerShipZ = GetEventData();
	float playerShipAY = GetEventData();
	int stormIndex = GetEventData();
	wdmReloadToSea();
}

void wdmEvent_ShipEncounter()
{
	float playerShipX = GetEventData();
	float playerShipZ = GetEventData();
	float playerShipAY = GetEventData();
	int eshipIndex = GetEventData();	
	if (CheckAttribute(pchar, "SkipEshipIndex") && pchar.SkipEshipIndex == eshipIndex) return; 
	pchar.eshipIndex = eshipIndex;
	LaunchMapScreen();

}

void wdmEvent_UpdateDate()
{
	Environment.date.day = worldMap.date.day;
	Environment.date.month = worldMap.date.month;	
	Environment.date.year = worldMap.date.year;
	Environment.date.hour = worldMap.date.hour;
	Environment.date.min = worldMap.date.min;
	Environment.date.sec = worldMap.date.sec;
	Environment.time = GetEventData();
}


#event_handler("WorldMap_AddQuestEncounters", "wdmEvent_AddQuestEncounters");
void wdmEvent_AddQuestEncounters()
{
	int idx = -1;
	string encID = "";
	string encPath = "";
	aref encs, at;
	makearef(encs, worldMap.addQuestEncounters);
	int num = GetAttributesNum(encs);
	for(int i = 0; i < num; i++)
	{
		at = GetAttributeN(encs, i);
		
		if (CheckAttribute(at, "characterID")) 
		{
			if(at.type == "trader")
			{
				if(!GenerateMapEncounter_Alone(at.characterID, &idx))
				{
					PostEvent("Map_TraderSucces", 100, "s", at.characterID);
					return;
				}
				
				encID = "";
				if (CheckAttribute(at, "XZGoto")) 
				{
					if(!wdmCreateMerchantShipXZByIndex(1.0, idx, &encID, stf(at.x1), stf(at.z1), stf(at.x2), stf(at.z2), sti(at.TimeOut)))
					{
						PostEvent("Map_TraderSucces", 100, "s", at.characterID);
						return;
					}
				}
				else
				{
					if(!wdmCreateMerchantShipByIndex(1.0, idx, &encID, at.beginlocator, at.endLocator, sti(at.TimeOut)))
					{
						PostEvent("Map_TraderSucces", 100, "s", at.characterID);
						return;
					}
				}
				
				encPath = "encounters." + encID;
				
				worldMap.(encPath).quest.event = "Map_TraderSucces";
				worldMap.(encPath).quest.chrID = at.characterID;
			}
			if(at.type == "cooltrader")
			{
				if(!GenerateMapEncounter_Alone(at.characterID, &idx))
				{
					PostEvent("Map_TraderSucces", 100, "s", at.characterID);
					return;
				}
				
				encID = "";
				if(!wdmCreateMerchantShipByIndex(stf(at.speed), idx, &encID, at.beginlocator, at.endLocator, sti(at.TimeOut)))
				{
					PostEvent("Map_TraderSucces", 100, "s", at.characterID);
					return;
				}
				
				encPath = "encounters." + encID;
				
				worldMap.(encPath).quest.event = "Map_TraderSucces";
				worldMap.(encPath).quest.chrID = at.characterID;
			}
			if(at.type == "warrior")
			{			
				if(!GenerateMapEncounter_Alone(at.characterID, &idx))
				{
					PostEvent("Map_WarriorEnd", 100, "s", at.characterID);
					return;
				}
				
				encID = "";
				
				if(!wdmCreateRealFollowShipByIndex(1.0, idx, &encID, sti(at.TimeOut)))
				{
					PostEvent("Map_WarriorEnd", 100, "s", at.characterID);
					return;
				}
				
				encPath = "encounters." + encID;
				
				worldMap.(encPath).quest.event = "Map_WarriorEnd";
				worldMap.(encPath).quest.chrID = at.characterID;
			}
			if(at.type == "coolwarrior")
			{			
				if(!GenerateMapEncounter_Alone(at.characterID, &idx))
				{
					PostEvent("Map_WarriorEnd", 100, "s", at.characterID);
					return;
				}
				
				encID = "";
				
				if(!wdmCreateRealFollowShipByIndex(1.7, idx, &encID, sti(at.TimeOut)))
				{
					PostEvent("Map_WarriorEnd", 100, "s", at.characterID);
					return;
				}
				
				encPath = "encounters." + encID;
				
				worldMap.(encPath).quest.event = "Map_WarriorEnd";
				worldMap.(encPath).quest.chrID = at.characterID;
			}
			if(at.type == "battle")
			{
				
			}
		}
	}
	DeleteAttribute(&worldMap, "addQuestEncounters");
	worldMap.addQuestEncounters = "";
	
	ReleaseMapEncounters();
}

#event_handler("WorldMap_IsSkipEnable", "wdmIsSkipEnable");
bool wdmSkipReturnBool = false;
bool wdmIsSkipEnable()
{
	wdmSkipReturnBool = false;
	if(CheckOfficersPerk(pchar, "SailingProfessional")) 
	{
		if(rand(100) <= 50)
		{
			wdmSkipReturnBool = true;
		}
	}
	return wdmSkipReturnBool;
}



void wdmDeleteLoginEncounter(string encID)
{
	Event("WorldMap_EncounterDelete", "s", encID);
}

#event_handler("WorldMap_EncounterDelete", "wdmEncounterDelete");
ref wdmEncounterDelete()
{
	BI_intRetValue = true;

	string encID = GetEventData();
	string encPath = "encounters." + encID;
	if(CheckAttribute(&worldMap, encPath) == 0)
	{
		return &BI_intRetValue;
	}
	aref enc;
	makearef(enc, worldMap.(encPath));
	
	bool needEvent = false;
	string eventName = "";
	string chrID = "";
	if(CheckAttribute(enc, "quest.chrID"))
	{
    
    
    	if(CheckAttribute(&enc, "Gotox") && CheckAttribute(&enc, "Gotoz"))
		{

			float fDeltaX = (stf(enc.x) - stf(enc.Gotox));
			float fDeltaZ = (stf(enc.z) - stf(enc.Gotoz));
			float fRadSqr = fDeltaX*fDeltaX + fDeltaZ*fDeltaZ;
			if( fRadSqr > 100.0 && stf(enc.livetime) > 1.0) 
			{
				BI_intRetValue = false;
				
			}
		}

		if(CheckAttribute(enc, "quest.event") != 0)
		{
			eventName = enc.quest.event;
			chrID = enc.quest.chrID;
			needEvent = true;
		}
		 
	}
	
	enc.needDelete = "wdmEncounterDelete";
	
	DeleteAttribute(&enc, "quest");
	if (!IsEntity(worldMap))
	{
	   
        DeleteAttribute(&worldMap, encPath);
    }
	
	if(needEvent)
	{
		PostEvent(eventName, 100, "s", chrID);
	}
	return &BI_intRetValue;
}

#event_handler("WorldMap_GetMoral", "wdmGetMoral");
float wdmGetMoral()
{
	int iMorale = 0;
	int cn = -1;
	int iRealCompNum = 0;
	for(int i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			iMorale = iMorale + GetCharacterCrewMorale(&characters[cn]);
			iRealCompNum++;
		}
	}
	iMorale = iMorale / iRealCompNum;
	return stf(iMorale);
}

#event_handler("WorldMap_GetFood", "wdmGetFood");
float wdmGetFood()
{
	return makefloat(CalculateFood());
}

#event_handler("WorldMap_GetRum", "wdmGetRum");
float wdmGetRum()
{
	return makefloat(CalculateShipRum(pchar));
}


void wdmEnterSeaQuest(string _chrId)
{
	ref NPChar = characterFromID(_chrId);
	
	if (findsubstr(_chrId, "Hunter0" , 0) != -1) 
	{
		AddQuestRecord("HeadHunter", "HeadHunter_Sea");
		AddQuestUserData("HeadHunter", "sSex", GetSexPhrase("��","���"));
		AddQuestUserData("HeadHunter", "sNation", NationNameGenitive(sti(NPChar.Nation)));
	}
		
	if (_chrId == "Head_of_Gold_Squadron")
	{
        string sQuest = "GoldFleetEncounter";
        pchar.quest.(sQuest).win_condition.l1 = "EnterToSea";  
        pchar.quest.(sQuest).win_condition = "GoldFleetEncounter";
        pchar.quest.(sQuest).function = "GoldFleetEncounter";
	}
	
	if (findsubstr(_chrId, "SiegeCap_1" , 0) != -1)
	{
        SiegeSquadronOnMap(_chrId);
	}
}

#event_handler("WorldMap_GetWindParameters", "wdmGetWindParameters");
void wdmGetWindParameters()
{
	float WindForce = GetEventData();
	float WindAngle = GetEventData();
	
	pchar.WorldMap.WindForce = WindForce;
	pchar.WorldMap.WindAngle = WindAngle;
	
	
}


