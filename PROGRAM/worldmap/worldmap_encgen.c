






#define WDM_STORM_RATE   		0.0001

#define WDM_MERCHANTS_RATE		0.07

#define WDM_WARRING_RATE		0.012

#define WDM_FOLLOW_RATE  		0.020

#define WDM_SPECIAL_RATE  		0.0015










float wdmTimeOfLastStorm = 0.0;
float wdmTimeOfLastMerchant = 0.0;
float wdmTimeOfLastWarring = 0.0;
float wdmTimeOfLastFollow = 0.0;
float wdmTimeOfLastSpecial = 0.0;


void wdmReset()
{
	wdmTimeOfLastStorm = 0.0;
	wdmTimeOfLastMerchant = 0.0;
	wdmTimeOfLastWarring = 0.0;
	wdmTimeOfLastFollow = 0.0;
	wdmTimeOfLastSpecial = 0.0;
}


void wdmStormGen(float dltTime, float playerShipX, float playerShipZ, float playerShipAY)
{
	bool encoff = false;
	if(CheckAttribute(pchar,"worldmapencountersoff") == 1)
	{
		if(sti(pchar.worldmapencountersoff)) return;
	}
	int numStorms = wdmGetNumberStorms();
	if(numStorms < 1)
	{
		wdmTimeOfLastStorm = wdmTimeOfLastStorm + dltTime*WDM_STORM_RATE*1000.0*iEncountersRate;
		if(rand(1001) < wdmTimeOfLastStorm)
		{
			wdmCreateStorm();
			wdmTimeOfLastStorm = 0.0;
		}
	}else{
		wdmTimeOfLastStorm = 0.0;
	}
}


void wdmShipEncounter(float dltTime, float playerShipX, float playerShipZ, float playerShipAY)
{
	int numShips = wdmGetNumberShipEncounters();
	if( CheckAttribute(pchar,"worldmap.shipcounter") ) {
		numShips = numShips - sti(pchar.worldmap.shipcounter);
	}
	if( numShips < 0 )
	{
		trace("Warning! World map ship quantity < 0 : numShips = " + numShips);
		trace("pchar.worldmap.shipcounter = " + pchar.worldmap.shipcounter);
		numShips = 0;
	}
	if(numShips < 8)
	{
		
		wdmTimeOfLastMerchant = wdmTimeOfLastMerchant + dltTime*WDM_MERCHANTS_RATE*1000.0*iEncountersRate;
		wdmTimeOfLastWarring = wdmTimeOfLastWarring + dltTime*WDM_WARRING_RATE*1000.0*iEncountersRate;
		wdmTimeOfLastFollow = wdmTimeOfLastFollow + dltTime*WDM_FOLLOW_RATE*1000.0*iEncountersRate;
		wdmTimeOfLastSpecial = wdmTimeOfLastSpecial + dltTime*WDM_SPECIAL_RATE*1000.0*iEncountersRate;
		
		float nump = 1.0 - numShips*0.15;
		
		if(rand(1001) + 1 < wdmTimeOfLastMerchant)
		{
			wdmTimeOfLastMerchant = 0.0;
			wdmCreateMerchantShip(0.8 + rand(10)*0.03);
		}
		else
		{
			bool encoff = false;
			if(CheckAttribute(pchar,"worldmapencountersoff") == 1)
			{
				encoff = sti(pchar.worldmapencountersoff);
			}
			if(encoff == false)
			{
				if(rand(1001) + 1 < wdmTimeOfLastWarring)
				{
					wdmTimeOfLastWarring = 0.0;
					wdmCreateWarringShips();
				}
				else
				{
					if(rand(1001) + 1 < wdmTimeOfLastFollow)
					{
						wdmTimeOfLastFollow = 0.0;
						if(!IsStopMapFollowEncounters())
						{
							wdmCreateFollowShip(0.8 + rand(10)*0.05);
						}						
					}
				}
				if(rand(1001) + 1 < wdmTimeOfLastSpecial)
				{
					wdmTimeOfLastSpecial = 0.0;
					wdmCreateSpecial(0.05 + rand(10)*0.02);
				}					
			}
		}
	}
	else
	{
		wdmTimeOfLastMerchant = 0.0;
		wdmTimeOfLastWarring = 0.0;
		wdmTimeOfLastFollow = 0.0;
		wdmTimeOfLastSpecial = 0.0;
	}
}


#event_handler("Map_TraderSucces", "Map_TraderSucces");
#event_handler("Map_WarriorEnd", "Map_WarriorEnd");

void Map_WarriorEnd()
{
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		return;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	if(sti(pchar.worldmap.shipcounter) < 0)
	{
		sti(pchar.worldmap.shipcounter) = 0;
	}
}
void Map_TraderSucces()
{
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{		
		return;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	if(sti(pchar.worldmap.shipcounter) < 0)
	{
		pchar.worldmap.shipcounter = 0;
	}
	string sChar = GetEventData();

	Map_TraderSucces_quest(sChar); 

	
	if (findsubstr(sChar, "_QuestMerchant" , 0) != -1)
	{
        Map_ReleaseQuestEncounter(sChar);
        Group_DeleteGroup("Sea_"+sChar);
        CloseQuestHeader("MerchantOnMap");
	}
    
    if (sChar == "Head_of_Gold_Squadron")
	{
        RouteGoldFleet();
	}
	
	if (findsubstr(sChar, "SiegeCap_" , 0) != -1)
	{
        SiegeProgress();
	}
	 
}

void Map_TraderSucces_quest(string sChar)
{
	ref character = CharacterFromID(sChar);
	
	
	
	if(sChar == "MaryCelesteCapitan")
	{
		Map_ReleaseQuestEncounter("MaryCelesteCapitan");
		
		
		if(PChar.QuestTemp.MaryCeleste != "OnDeck")
		{
			character.fromCity = character.toCity; 
			character.fromShore = character.toShore;
			character.toCity = SelectAnyColony(character.fromCity); 
			character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
			
			Map_CreateTrader(character.fromShore, character.toShore, "MaryCelesteCapitan", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)));
			
			Log_TestInfo("���������� ���� ������ ����� �� " + character.fromCity + " � ����������� � " + character.toShore);
		}
	}
	
	
	
	if(sChar == "PiratesOnUninhabited_BadPirate")
	{
		Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate");
		
		if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.ClearShip"))
		{
			character.fromCity = character.toCity; 
			character.fromShore = character.toShore;
			character.toCity = SelectAnyColony(character.fromCity); 
			character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
			
			Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", -1);
			
			Log_TestInfo("������ �� ����������: ��� ����� �� " + character.fromCity + " � ���������� �: " + character.toShore);
		}
	}
	
	
	if(sChar == "PirateCapt")
	{
		Log_TestInfo("��������� ������� ����� �� ����� ����������.");
		Map_ReleaseQuestEncounter(sChar);
		AddQuestRecord("ReasonToFast","26");
		CloseQuestHeader("ReasonToFast");
		DeleteAttribute(pchar,"questTemp.ReasonToFast");
	}
	
	
	if (findsubstr(sChar, "PortmansCap_" , 0) != -1 && characters[GetCharacterIndex(sChar)].quest == "InMap")
	{
		SetCapitainFromSeaToCity(sChar);
		Log_TestInfo("��������� ����������� ���� " + sChar + " ����� �� ����� ����������.");
	}
	
	if (findsubstr(sChar, "SeekCap_" , 0) != -1 && characters[GetCharacterIndex(sChar)].quest == "InMap")
	{
		SetRobberFromMapToSea(sChar);
		Log_TestInfo("��������� ����-���� " + sChar + " ����� �� ����� ����������.");
	}
	
	if (findsubstr(sChar, "SeekCitizCap_" , 0) != -1)
	{
		if(character.quest == "InMap")
		{
			CitizCapFromMapToCity(sChar);
			Log_TestInfo("��������� ���� " + sChar + " ����� �� ����� ����������.");
		}
		
		if(character.quest == "outMap")
		{
			string sTemp = "SCQ_" + character.index;
			pchar.quest.(sTemp).over = "yes"; 
			character.lifeDay = 0;
		}
	}
}
