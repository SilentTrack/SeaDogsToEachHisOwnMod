

void SetRandSelfSkill(ref _ch, int _min, int _max)
{
	int iDelta = _max-_min;
	_ch.skill.Leadership 	= _min + rand(iDelta);
	_ch.skill.FencingL 		= _min + rand(iDelta);
	_ch.skill.FencingS 		= _min + rand(iDelta);
	_ch.skill.FencingH 		= _min + rand(iDelta);
	_ch.skill.Pistol 		= _min + rand(iDelta);
	_ch.skill.Fortune 		= _min + rand(iDelta);
	_ch.skill.Sneak 		= _min + rand(iDelta);
}

void SetRandShipSkill(ref _ch, int _min, int _max)
{
	int iDelta = _max-_min;
	_ch.skill.Sailing = _min + rand(iDelta);
	_ch.skill.Commerce = _min + rand(iDelta);
	_ch.skill.Accuracy = _min + rand(iDelta);
	_ch.skill.Cannons = _min + rand(iDelta);
	_ch.skill.Repair = _min + rand(iDelta);
	_ch.skill.Grappling = _min + rand(iDelta);
	_ch.skill.Defence = _min + rand(iDelta);
}


void SelAllPerksToChar(ref _ch, bool _isOfficer)
{
	_ch.perks.list.BasicDefense = "1";
	_ch.perks.list.AdvancedDefense = "1";
	_ch.perks.list.CriticalHit = "1";
	_ch.perks.list.SwordplayProfessional = "1";
	_ch.perks.list.Grus = "1";
	_ch.perks.list.Rush = "1";
	_ch.perks.list.Tireless = "1";
	_ch.perks.list.HardHitter = "1";
	_ch.perks.list.BladeDancer = "1";
	_ch.perks.list.Sliding = "1";
	_ch.perks.list.Gunman = "1";
	_ch.perks.list.GunProfessional = "1";
	_ch.perks.list.IronWill = "1";
	_ch.perks.list.SharedExperience = "1";
	_ch.perks.list.Medic = "1";
	_ch.perks.list.HPPlus = "1";
	_ch.perks.list.EnergyPlus = "1";
	_ch.perks.list.Trustworthy = "1";
	_ch.perks.list.ShipEscape = "1";
	_ch.perks.list.Alchemy = "1";
	
	_ch.perks.list.FlagPir = "1";
	_ch.perks.list.FlagEng = "1";
	_ch.perks.list.FlagFra = "1";
	_ch.perks.list.FlagSpa = "1";
	_ch.perks.list.FlagHol = "1";
	_ch.perks.list.FastReload = "1";
	_ch.perks.list.ImmediateReload = "1";
	_ch.perks.list.HullDamageUp = "1";
	_ch.perks.list.SailsDamageUp = "1";
	_ch.perks.list.CrewDamageUp = "1";
	_ch.perks.list.CriticalShoot = "1";
	_ch.perks.list.LongRangeShoot = "1";
	_ch.perks.list.CannonProfessional = "1";
	_ch.perks.list.LongRangeGrappling = "1";
	_ch.perks.list.MusketsShoot = "1";
	_ch.perks.list.GrapplingProfessional = "1";
	_ch.perks.list.BasicBattleState = "1";
	_ch.perks.list.AdvancedBattleState = "1";
	_ch.perks.list.ShipDefenseProfessional = "1";
	_ch.perks.list.LightRepair = "1";
	_ch.perks.list.InstantRepair = "1";
	_ch.perks.list.ShipSpeedUp = "1";
	_ch.perks.list.ShipTurnRateUp = "1";
	_ch.perks.list.StormProfessional = "1";
	_ch.perks.list.Turn180 = "1";
	_ch.perks.list.SeaDogProfessional = "1";
	_ch.perks.list.SailingProfessional = "1";
	_ch.perks.list.Brander = "1";
	_ch.perks.list.Troopers = "1";
	_ch.perks.list.BasicCommerce = "1";
	_ch.perks.list.AdvancedCommerce = "1";
	_ch.perks.list.ProfessionalCommerce = "1";	
	_ch.perks.list.Carpenter = "1";
	_ch.perks.list.Builder = "1";
	_ch.perks.list.SelfRepair = "1";
	_ch.perks.list.WindCatcher = "1";
	_ch.perks.list.SailsMan = "1";
	_ch.perks.list.Doctor1 = "1";
	_ch.perks.list.Doctor2 = "1";
	
	if(_isOfficer) 
	{
		_ch.perks.list.ByWorker = "1";
		_ch.perks.list.ByWorker2 = "1";
	}
}


void SetHalfPerksToChar(ref _ch, bool _isOfficer)
{
	_ch.perks.list.BasicDefense = "1";
	_ch.perks.list.AdvancedDefense = "1";
	_ch.perks.list.CriticalHit = "1";
	_ch.perks.list.SwordplayProfessional = "1";
	_ch.perks.list.Gunman = "1";
	_ch.perks.list.SharedExperience = "1";
	
	_ch.perks.list.FlagPir = "1";
	_ch.perks.list.FlagEng = "1";
	_ch.perks.list.FlagFra = "1";
	_ch.perks.list.FlagSpa = "1";
	_ch.perks.list.FlagHol = "1";
	_ch.perks.list.HullDamageUp = "1";
	_ch.perks.list.SailsDamageUp = "1";
	_ch.perks.list.CrewDamageUp = "1";
	_ch.perks.list.CriticalShoot = "1";
	_ch.perks.list.LongRangeShoot = "1";
	_ch.perks.list.LongRangeGrappling = "1";
	_ch.perks.list.GrapplingProfessional = "1";
	_ch.perks.list.BasicBattleState = "1";
	_ch.perks.list.AdvancedBattleState = "1";
	_ch.perks.list.ShipSpeedUp = "1";
	_ch.perks.list.ShipTurnRateUp = "1";
	_ch.perks.list.StormProfessional = "1";
	_ch.perks.list.Turn180 = "1";
	_ch.perks.list.SailingProfessional = "1";
	_ch.perks.list.WindCatcher = "1";
	_ch.perks.list.SailsMan = "1";
	
	if(_isOfficer) 
	{
		_ch.perks.list.ByWorker = "1";
		_ch.perks.list.ByWorker2 = "1";
	}
}


void RemoveAllCharacterItems(ref _ch, bool _removemoney)
{
	
	if(_ch == GetMainCharacter())
	{
		StoreEquippedMaps(_ch);
		_ch.MapsAtlasCount = 0;
	}	
	RemoveCharacterEquip(_ch, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(_ch, GUN_ITEM_TYPE);
	RemoveCharacterEquip(_ch, SPYGLASS_ITEM_TYPE);
	RemoveCharacterEquip(_ch, PATENT_ITEM_TYPE);
	RemoveCharacterEquip(_ch, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(_ch, MAPS_ITEM_TYPE);
	RemoveCharacterEquip(_ch, TOOL_ITEM_TYPE);
	RemoveCharacterEquip(_ch, TALISMAN_ITEM_TYPE);
	
	RemoveCharacterArtefactEquip(_ch, ITEM_SLOT1_TYPE);
	RemoveCharacterArtefactEquip(_ch, ITEM_SLOT2_TYPE);
	RemoveCharacterArtefactEquip(_ch, ITEM_SLOT3_TYPE);
	
	
	aref arItems;
	string sName;
	ref rLoc;
	makearef(arItems, _ch.items);
	int	Qty = GetAttributesNum(arItems);
	for (int a=0; a<Qty; a++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, a));
		rLoc = ItemsFromID(sName);
		if (rLoc.ItemType == "QUESTITEMS")
		{
			_ch.questTemp.items.(sName) = _ch.items.(sName);
		}
	}			
	DeleteAttribute(_ch, "items");
	_ch.items = "";
	makearef(arItems, _ch.questTemp.items);
	Qty = GetAttributesNum(arItems);
	for (a=0; a<Qty; a++)
	{		
		sName = GetAttributeName(GetAttributeN(arItems, a));
		TakeNItems(_ch, sName, sti(arItems.(sName)));
	}		
	DeleteAttribute(_ch, "questTemp.items");
	
	_ch.SystemInfo.itemsCRC = CheckItemsCRC(_ch); 
	
	if(_removemoney)
	{
		_ch.money = 0;
	}
}


void RemoveAllPassengersAndCompanions()
{
    int iDay = GetPassengersQuantity(pchar);
    int i = 0;
    int n = 0;
	int idx;
	ref ch;
	
 	while (i < iDay)
	{
		i++;
		idx = GetPassenger(pchar, n); 
		if (idx == -1) break;
		ch = GetCharacter(idx);
		if (GetRemovable(ch)) 
		{
		    ch.LifeDay = 1; 
		    RemovePassenger(pchar, ch);
			ChangeCharacterAddress(ch,"none","");
		}
		else
		{
		    n++;
		}
	}
    for (i=0; i<COMPANION_MAX; i++)
	{
		idx = GetCompanionIndex(pchar, i);
		if (idx != -1)
		{
            ch = GetCharacter(idx);
			if (GetShipRemovable(ch) && GetRemovable(ch))  
			{
			    ch.LifeDay = 1; 
			    RemoveCharacterCompanion(pchar, ch);
			}
		}
	}
}

void CleanAllCabinBoxes()
{
	ref loc;
	int n;
	string sTemp;
	
    if (Pchar.SystemInfo.CabinType != "")
    {
	    loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; 

	    for (n = 1; n <= 4; n++)
	    {
	        sTemp = "box" + n;
			DeleteAttribute(loc, sTemp + ".items");
		    loc.(sTemp).items = "";
		    loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
		    loc.(sTemp).money = 0;
	    }
    }
    loc = &locations[FindLocation("My_Deck")];
    for (n = 1; n <= 4; n++)
    {
        sTemp = "box" + n;
		DeleteAttribute(loc, sTemp + ".items");
	    loc.(sTemp).items = "";
	    loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
	    loc.(sTemp).money = 0;
    }
}


int RandShipFromShipClass(ref _ch)
{
	int iShipClass = sti(RealShips[sti(_ch.Ship.Type)].Class);
	int iShipType;
	switch(iShipClass)
	{
		case 1:
			iShipType = SHIP_LINESHIP + rand(4);
			break;
			
		case 2:
			iShipType = SHIP_GALEON_H + rand(2);
			break;
		
		case 3:
			iShipType = SHIP_GALEON_L + rand(3);
			break;
			
		case 4:
			iShipType = SHIP_BRIGANTINE + rand(2);
			break;
			
		case 5:
			iShipType = SHIP_LUGGER + rand(1);
			break;
			
		case 6:
			iShipType = SHIP_WAR_TARTANE;
			break;
			
	}
	return iShipType;
}


bool IsPCharHaveTreasurer()
{
	ref rOfficer;

	for(int i=0; i<MAX_CHARACTERS; i++)
	{
		rOfficer = &characters[i];
		if(CheckAttribute(rOfficer, "treasurer") && sti(rOfficer.Treasurer) == 1)
		{
			return true; 
		}
		
	}
	
	return false;
}


ref GetPCharTreasurerRef()
{
	if(!IsPCharHaveTreasurer()) return &NullCharacter;
	for(int i=0; i<MAX_CHARACTERS; i++)
	{
		if(CheckAttribute(&characters[i], "treasurer") && sti(characters[i].Treasurer) == 1)
		{
			return &characters[i];
		}
	}
	
	return &NullCharacter;
}


string GetAttrValue(ref _rChar, string _sAttr)
{
	string sTemp;
	if(!CheckAttribute(_rChar, _sAttr)) _rChar.(_sAttr) = "";
	
	sTemp = _rChar.(_sAttr);
	return sTemp;
}


string IslandGetLocationFromType(string _island, string _type)
{
	ref rLoc;
	int i, iMaxLoc[MAX_LOCATIONS];
	int iRandLoc = 0;
	for(i=1; i<MAX_LOCATIONS; i++)
	{
		makeref(rLoc, locations[i]);
		if(findsubstr(rLoc.id, _type, 0) != -1 && rLoc.islandId == _island)
		{
			iMaxLoc[iRandLoc] = i;
			iRandLoc++;
		}
	}
	
	if(iRandLoc == 0)
		return "none";
	
	i = iMaxLoc[rand(iRandLoc-1)];
	return locations[i].id;
}


void DisableAllExits(bool _truefalse)
{
	chrDisableReloadToLocation = _truefalse;
	bDisableFastReload         = _truefalse;
}




void LockQuestLine(ref refChar) 
{
	refChar.notQuestLine = true;
}

string QuestGetGangLocation(string _areal)	
{
	int n;
	string island = GetArealByCityName(_areal);
	string LocationId, sAreal;
	int storeArray[MAX_LOCATIONS];
	int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{				
		if(GiveArealByLocation(&locations[n]) == island)
		{			
			
			if(CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true) continue;
			LocationId = locations[n].id;
			if(findsubstr(LocationId, "jungle" , 0) != -1 || findsubstr(LocationId, "Shore" , 0) != -1 || findsubstr(LocationId, "CaveEntrance" , 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[rand(howStore-1)];
	return locations[n].id;
}

string QuestGetColony(string _city) 
{
    int storeArray[MAX_COLONIES];
    int howStore = 0;
	string sChrId;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != _city)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[rand(howStore-1)]].id;
}

string GetColonyExpect2Colonies(string _city1, string _city2) 
{
	int storeArray[MAX_COLONIES];
	int howStore = 0;
	string sChrId;
	ref rColony;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		makeref(rColony, colonies[n]);
		if(!CheckAttribute(rColony, "HasNoFort") && rColony.nation != "none" && sti(rColony.nation) != PIRATE && GetRelation2BaseNation(sti(rColony.nation)) != RELATION_ENEMY && rColony.id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && rColony.id != _city1 && rColony.id != _city2)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[rand(howStore-1)]].id;
}


void InitAlchemy()
{
	ref item;		
	for(int n = 0; n < ITEMS_QUANTITY; n++)
	{
		item = &Items[n];
		if( CheckAttribute(item,"multiobject") )
		{
			string sGood = item.id;
			pchar.alchemy.(sGood).isKnown = false;
			
			
			
		}
	}
}


bool isMultiObjectKnown(string itemId)
{
	ref item;		
	for(int n = 0; n < ITEMS_QUANTITY; n++)
	{
		item = &Items[n];
		if( CheckAttribute(item,"multiobject") )
		{
			string sGood = item.id;
			if(sGood == itemId && pchar.alchemy.(sGood).isKnown == true) return true;
		}
	}
	return false;
}

void SetAlchemyRecipeKnown(string Recipe)
{
	pchar.alchemy.(Recipe).isKnown = true;
}

void initStartState2Character(ref ch)
{
    NullCharacter.Siege = "";
    
	ch.SystemInfo.SaveCount = 0;
    ch.SystemInfo.LoadCount = 0;
    ch.SystemInfo.DeadCount = 0;

    ch.SystemInfo.CabinType          = ""; 
    
    ch.questTemp.Contraband.relation = 60;
	ch.questTemp.Indian.relation = 30; 
    DeleteAttribute(ch, "quest.meeting");
    ch.ShipInStock = 0; 
	ch.questTemp.abordage = 0;   
	ch.questTemp.donate   = 0; 

	ch.questTemp.friend_in_tavern = ""; 
	ch.questTemp.RelationAgentMet = "0"; 

	ch.questTemp.NationQuest = ""; 

	ch.GenQuest.BrothelCount = "0"; 
	
	ch.I_MAP_SHOW = false;  
	ch.CameraHoldPos = false;
	ch.CameraShipNPC = 0;
	ch.GenQuestFort.FarLocator = true; 
    
    ch.GenQuest.Find_Merchant.lastspeak_date = "";
    ch.GenQuest.ConvoyPassenger = ""; 

	
	ch.questTemp.State = "";
	
	ch.questTemp.Waiting_time = "2";
	
	ch.questTemp.CurQuestNumber = "2";
	
	InitTravelMap();
	
	pchar.RomanticQuest.HorseCheck = -1;
	
	ch.MapsAtlasCount = 0;
	
	ch.Flags.Pirate = 3;
	
	ch.questTemp.Slavetrader = "canTakeQuest"; 
	
	SelectSlavetraderRendom(); 
	
	PoormansInit();
	
	pchar.questTemp.HorseLoot = 0;
	
	pchar.questTemp.HorseQty = 0;
	
	pchar.questTemp.WPU.Fraht.count = 0;
	pchar.questTemp.WPU.Postcureer.count = 0;
	pchar.questTemp.WPU.Escort.count = 0;
	
	ch.questTemp.jailCanMove = false;
	
	ch.questTemp.different = "free";
	ch.questTemp.WPU = "0";
	
	ch.CanGenerateShipSituation = true;
	
	InitAlchemy();
	
	HollandGambitNpcInit();
	
	SharlieNpcInit();
	
	SagaNpcInit();
	
	LSC_NpcInit();
	
	pchar.quest.Red_Chieftain.win_condition.l1 = "Rank";
	pchar.quest.Red_Chieftain.win_condition.l1.value = 8; 
	pchar.quest.Red_Chieftain.win_condition.l1.operation = ">=";
	pchar.quest.Red_Chieftain.function = "RedChieftain_Prepare";
	pchar.quest.False_Trace.win_condition.l1 = "Rank";
	pchar.quest.False_Trace.win_condition.l1.value = 15; 
	pchar.quest.False_Trace.win_condition.l1.operation = ">=";
	pchar.quest.False_Trace.function = "FalseTrace_Prepare";
	
	pchar.quest.Mangarosa.win_condition.l1 = "item";
	pchar.quest.Mangarosa.win_condition.l1.item = "cannabis7";
	pchar.quest.Mangarosa.function = "Mangarosa_Start";
	
	pchar.GenQuest.Piratekill = 0;
	
	pchar.questTemp.TavernVisit.counter = 0;
	pchar.questTemp.ShipyardVisit.counter = 0;
}


void QuestActions()
{
	ref sld;
	int i;
	CompanionTravel_ProcessAllTravellers(); 
	
	for (i=0; i<4; i++)
	{
		if (CheckCharacterItem(pchar, NationShortName(i)+"TradeLicence") && GetDaysContinueNationLicence(i) == -1)
		{
			TakeNationLicence(i);
		}		
	}

	
	if(CheckAttribute(pchar, "questTemp.ReasonToFast"))
	{
		if(pchar.questTemp.ReasonToFast == "SpeakHorse") 
		{
			AddQuestRecord("ReasonToFast", "2");	
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("","�"));			
			CloseQuestHeader("ReasonToFast");
			pchar.questTemp.ReasonToFast.end = true;
		}
		if(pchar.questTemp.ReasonToFast == "MeetPatrolFail") 
		{
			AddQuestRecord("ReasonToFast", "3");		
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("��","���"));		
			CloseQuestHeader("ReasonToFast");
			pchar.questTemp.ReasonToFast.end = true;
		}
		if(CheckAttribute(pchar, "questTemp.ReasonToFast.PatrolLocation"))
		{
			if(CheckAttribute(Locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)],"DisableEncounters"))
			{
				DeleteAttribute(Locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], "DisableEncounters");
			}
		}	
		if(CheckAttribute(pchar, "questTemp.ReasonToFast.end"))
		{
			DeleteAttribute(pchar, "questTemp.ReasonToFast");
		}	
	}
	
	if(CheckAttribute(pchar,"GenQuest.ShipSituation.Epidemy"))
	{
		ShipSituation_CheckConsequence(sti(pchar.GenQuest.ShipSituation.Epidemy));
	}
	
	if (GetDataDay() == 5 || GetDataDay() == 20)
	{
		if (CheckAttribute(NullCharacter, "capitainBase"))
		{
			string sName;
			int capIndex, a;
			aref arCapBase, arBase;
    		makearef(arBase, NullCharacter.capitainBase);
    		int	Qty = GetAttributesNum(arBase);
    		for (a=0; a<Qty; a++)
    		{
    			arCapBase = GetAttributeN(arBase, a);
				sName = GetAttributeName(arCapBase); 
				capIndex = GetCharacterIndex(sName);
    			
				if (capIndex == -1)
    			{	
					
					 
					DeleteAttribute(arBase, sName);
					Qty --; 
					a--;
				}
				
				else
				{
					if (GetNpcQuestPastDayParam(arCapBase, "checkTime") >= sti(arCapBase.checkTime))
					{
						
						
							Cap_SetMapAgain(&characters[capIndex], arCapBase);
						
					}
				}		
    		}
		}
	}
}


void CitizCapIsDead_CloseQuest(aref arCapBase, string capId)
{
	ref sld;
	string sTemp;
	
	sTemp = "SecondTimer_" + capId;
	if (capId == "MushketCap") sTemp = "MushketTimer";
	if (capId == "Danielle")   sTemp = "DanielleTimer";
	pchar.quest.(sTemp).over = "yes";
	
	int iTemp = GetCharacterIndex(arCapBase.questGiver);
	if (iTemp != -1)
	{
		
		ref npchar = &characters[iTemp];
		if (CheckAttribute(npchar, "quest.PortmansSeekShip") || CheckAttribute(npchar, "quest.PortmansJornal"))
		{
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			DeleteAttribute(npchar, "quest.PortmansJornal");
			npchar.quest = ""; 
		}
		else
		{
			sTemp = "SCQ_" + iTemp;
			pchar.quest.(sTemp).over = "yes"; 
			characters[iTemp].lifeDay = 0;
		}
	}
	string sTitle1 = arCapBase.Tilte1;
	string sTitle2 = arCapBase.Tilte2;
}


void Cap_SetMapAgain(ref sld, aref arCapBase) 
{
	
	string sGroup = "SeekCapShip_" + sld.index;
	group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	switch (arCapBase.quest)
	{
	case "mushket": 
		if (sld.cityShore == sld.quest.targetShore)
		{
			sld.quest.targetShore = SelectAnyColony(sld.cityShore);
		}
		Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, sti(arCapBase.checkTime)-5);
		break
	case "citizen": 
		if (sld.city == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.city);
		}
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-5);
		break
	case "robber": 
		if (sld.city == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.city);
		}
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-5);
		break
	case "jornal": 
		if (sld.quest.baseShore == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.quest.baseShore);
		}
		Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-5);
		break
	case "Danielle": 
		if (sld.cityShore == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.cityShore);
		}
		Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, sti(arCapBase.checkTime)-5);
		break
	}
	
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = iTemp + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}


void PoormansInit()
{
	ref sld;
	
	sld = GetCharacter(NPC_GenerateCharacter("SentJons_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false, "slave"));
	sld.city = "SentJons";	
	sld.location	= "SentJons_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; 
	sld.forSit.locator0 = "goto15";
	sld.forSit.locator1 = "goto17"; 
	sld.forSit.locator2 = "goto4";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	sld = GetCharacter(NPC_GenerateCharacter("Bridgetown_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false, "slave"));
	sld.city = "Bridgetown";
	sld.location	= "Bridgetown_town";
	sld.location.group = "goto";
	sld.location.locator = "goto12";
	sld.forStay.locator = "goto12"; 
	sld.forSit.locator0 = "goto9";
	sld.forSit.locator1 = "goto19"; 
	sld.forSit.locator2 = "goto4";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	sld = GetCharacter(NPC_GenerateCharacter("Beliz_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false, "slave"));
	sld.city = "Beliz";
	sld.location	= "Beliz_town";
	sld.location.group = "goto";
	sld.location.locator = "goto9";
	sld.forStay.locator = "goto9"; 
	sld.forSit.locator0 = "goto7";
	sld.forSit.locator1 = "goto19"; 
	sld.forSit.locator2 = "goto3";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	sld = GetCharacter(NPC_GenerateCharacter("Caracas_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false, "slave"));
	sld.city = "Caracas";
	sld.location	= "Caracas_town";
	sld.location.group = "goto";
	sld.location.locator = "goto20";
	sld.forStay.locator = "goto20"; 
	sld.forSit.locator0 = "goto1";
	sld.forSit.locator1 = "goto21"; 
	sld.forSit.locator2 = "goto23";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	
	sld = GetCharacter(NPC_GenerateCharacter("Cartahena_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false, "slave"));
	sld.city = "Cartahena";
	sld.location	= "Cartahena_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; 
	sld.forSit.locator0 = "goto18";
	sld.forSit.locator1 = "goto14"; 
	sld.forSit.locator2 = "goto6";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	
	sld = GetCharacter(NPC_GenerateCharacter("Cumana_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false, "slave"));
	sld.city = "Cumana";
	sld.location	= "Cumana_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; 
	sld.forSit.locator0 = "goto13";
	sld.forSit.locator1 = "goto15"; 
	sld.forSit.locator2 = "goto3";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");	
	
	
	sld = GetCharacter(NPC_GenerateCharacter("BasTer_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false, "slave"));
	sld.city = "BasTer";
	sld.location	= "BasTer_town";
	sld.location.group = "goto";
	sld.location.locator = "goto18";
	sld.forStay.locator = "goto18"; 
	sld.forSit.locator0 = "goto24";
	sld.forSit.locator1 = "goto16"; 
	sld.forSit.locator2 = "goto17";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	
	
	sld = GetCharacter(NPC_GenerateCharacter("Havana_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false, "slave"));
	sld.city = "Havana";
	sld.location	= "Havana_town";
	sld.location.group = "goto";
	sld.location.locator = "goto12";
	sld.forStay.locator = "goto12"; 
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto22"; 
	sld.forSit.locator2 = "goto23";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	
	sld = GetCharacter(NPC_GenerateCharacter("PortRoyal_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false, "slave"));
	sld.city = "PortRoyal";
	sld.location	= "PortRoyal_town";
	sld.location.group = "goto";
	sld.location.locator = "goto15";
	sld.forStay.locator = "goto15"; 
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto28"; 
	sld.forSit.locator2 = "goto7";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	sld = GetCharacter(NPC_GenerateCharacter("FortFrance_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false, "slave"));
	sld.city = "FortFrance";
	sld.location	= "FortFrance_town";
	sld.location.group = "goto";
	sld.location.locator = "goto4";
	sld.forStay.locator = "goto4"; 
	sld.forSit.locator0 = "goto14";
	sld.forSit.locator1 = "goto10"; 
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	
	sld = GetCharacter(NPC_GenerateCharacter("Charles_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false, "slave"));
	sld.city = "Charles";
	sld.location	= "Charles_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; 
	sld.forSit.locator0 = "goto19";
	sld.forSit.locator1 = "goto13"; 
	sld.forSit.locator2 = "goto3";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	
	sld = GetCharacter(NPC_GenerateCharacter("PortoBello_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false, "slave"));
	sld.city = "PortoBello";
	sld.location	= "PortoBello_town";
	sld.location.group = "goto";
	sld.location.locator = "goto15";
	sld.forStay.locator = "goto15"; 
	sld.forSit.locator0 = "goto3";
	sld.forSit.locator1 = "goto25"; 
	sld.forSit.locator2 = "goto12";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	
	sld = GetCharacter(NPC_GenerateCharacter("PortPax_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false, "slave"));
	sld.city = "PortPax";
	sld.location	= "PortPax_town";
	sld.location.group = "goto";
	sld.location.locator = "goto14";
	sld.forStay.locator = "goto14"; 
	sld.forSit.locator0 = "goto25";
	sld.forSit.locator1 = "goto13"; 
	sld.forSit.locator2 = "goto11";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	
	sld = GetCharacter(NPC_GenerateCharacter("Santiago_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false, "slave"));
	sld.city = "Santiago";
	sld.location	= "Santiago_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; 
	sld.forSit.locator0 = "goto3";
	sld.forSit.locator1 = "goto15"; 
	sld.forSit.locator2 = "goto28";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	
	sld = GetCharacter(NPC_GenerateCharacter("Marigo_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, HOLLAND, -1, false, "slave"));
	sld.city = "Marigo";
	sld.location	= "Marigo_town";
	sld.location.group = "goto";
	sld.location.locator = "goto16";
	sld.forStay.locator = "goto16"; 
	sld.forSit.locator0 = "goto1";
	sld.forSit.locator1 = "goto4"; 
	sld.forSit.locator2 = "goto9";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	
	sld = GetCharacter(NPC_GenerateCharacter("Tortuga_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false, "slave"));
	sld.city = "Tortuga";
	sld.location	= "Tortuga_town";
	sld.location.group = "goto";
	sld.location.locator = "goto23";
	sld.forStay.locator = "goto23"; 
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto18"; 
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	
	sld = GetCharacter(NPC_GenerateCharacter("PortSpein_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false, "slave"));
	sld.city = "PortSpein";
	sld.location	= "PortSpein_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; 
	sld.forSit.locator0 = "goto9";
	sld.forSit.locator1 = "goto14"; 
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
}


string GetQuestNationsCity(int _nation) 
{
	int n, iRes;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none"  && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && sti(colonies[n].nation) == _nation && GiveArealByLocation(loadedLocation) != colonies[n].island) 
		{
			if (GetCharacterIndex(colonies[n].id + "_tavernkeeper") > 0 && GetCharacterIndex(colonies[n].id + "_usurer") > 0)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	iRes = storeArray[dRand(howStore-1)];
	return colonies[iRes].id;
}


string SelectNotEnemyColony(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && colonies[n].id != "FortOrange" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandByCityName(npchar.city) != colonies[n].islandLable) 
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[dRand(howStore-1)];
	return colonies[nation].id;
}


string SelectAnyColony(string _City)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && colonies[n].id != "FortOrange" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandByCityName(_City) != colonies[n].islandLable) 
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[dRand(howStore-1)];
	return colonies[nation].id;
}

string SelectAnyColony2(string _City1, string _City2)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && colonies[n].id != "FortOrange" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandByCityName(_City1) != colonies[n].islandLable && GetIslandByCityName(_City2) != colonies[n].islandLable) 
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[dRand(howStore-1)];
	return colonies[nation].id;
}


void SetCapitainFromSeaToCity(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InCity"; 
	sld.City = sld.quest.targetCity; 
	sld.location	= sld.City + "_PortOffice";
	sld.location.group = "goto";
	sld.location.locator = "goto"+(rand(2)+1);
	LAi_SetCitizenType(sld);

	 

	
	int Qty = rand(4)+3;
	string name = "Timer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetCapitainFromCityToSea";
	pchar.quest.(name).CapId = sld.id; 
	
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	
	AddSimpleRumourCity(LinkRandPhrase("Captain " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' is in the city. He must be in a harbor office.", 
		"Captain " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' is in the city. He must be in a harbor office.", 
		"Captain " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' is in the city. He must be in a harbor office."), sld.City, Qty, 1, "none");
}

void PortmansBook_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString)
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;	
		string sTitle = characters[GetCharacterIndex(sld.quest.firstCity + "_PortMan")].id + "PortmansBook_Delivery";
		AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "4");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandByCityName(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", ", on the " + XI_ConvertString(GetIslandByCityName(sld.quest.targetCity) + "Dat"));
		}
	}
}


void SetRobberFromMapToSea(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InPort"; 
	sld.City = sld.quest.targetCity; 
	int iColony = FindColony(sld.City);
	sld.nation = colonies[iColony].nation; 

	string sGroup = "SeekCapShip_" + sld.index;
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);			
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
	Group_SetTaskNone(sGroup);

	
	int Qty = rand(5)+4;
	string name = "SecondTimer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetRobberFromSeaToMap";
	pchar.quest.(name).CapId = sld.id; 
	
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	
	AddSimpleRumourCity(LinkRandPhrase("Captain " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' is on his vessel at the port. Odd fellow, I say, never put his steps ashore.", 
		"Captain " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' is on his vessel at the port. Odd fellow, I say, never put his steps ashore.", 
		"Captain " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' is on his vessel at the port. Odd fellow, I say, never put his steps ashore."), sld.City, Qty, 1, "none");
}

void PortmansSeekShip_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString)
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;	
		ref npchar = &characters[GetCharacterIndex(sld.quest.firstCity + "_PortMan")];
		string sTitle = npchar.id + "Portmans_SeekShip";
		AddQuestRecordEx(sTitle, "Portmans_SeekShip", "3");
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName)));
		AddQuestUserData(sTitle, "sShipName", sld.Ship.name);
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		iTemp = RealShips[sti(sld.Ship.Type)].basetype;
		AddQuestUserData(sTitle, "sSexWord", GetShipSexWord(ShipsTypes[iTemp].name, "����", "����"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandByCityName(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", ", on the " + XI_ConvertString(GetIslandByCityName(sld.quest.targetCity) + "Dat"));
		}
	}
}


void CitizCapFromMapToCity(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InCity"; 
	sld.City = sld.quest.targetCity; 
	int iColony = FindColony(sld.City);
	sld.nation = colonies[iColony].nation; 
	if (rand(1))
	{	
		sld.location	= sld.City + "_town";
		sld.location.group = "goto";
		sld.location.locator = "goto"+(rand(5)+1);
		LAi_SetCitizenType(sld);
		string slai_group = GetNationNameByType(sti(colonies[iColony].nation))  + "_citizens";
		LAi_group_MoveCharacter(sld, slai_group);
		
		AddSimpleRumourCity(LinkRandPhrase("Captain " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' is the city. His name is " + GetFullName(sld) + ", I believe.", 
			"Captain " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' is the city.", 
			"Captain " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' is the city. His name is " + GetFullName(sld) + ", I believe. " + GetFullName(sld) + " ����� �� ��� �����..."), sld.City, Qty, 1, "none");
	}
	else
	{	
		string sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_AddCharacter(sGroup, sld.id);			
		Group_SetGroupCommander(sGroup, sld.id);
		Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
		Group_SetTaskNone(sGroup);
		
		AddSimpleRumourCity(LinkRandPhrase("Captain " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' is on his vessel at the port. His name is " + GetFullName(sld) + ", I believe.", 
			"Captain " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' is on his vessel at the port.", 
			"Captain " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' is on his vessel at the port. His name is " + GetFullName(sld) + ", I believe."), sld.City, Qty, 1, "none");
	}
	
	int Qty = rand(7)+5; 
	string name = "SecondTimer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "CitizCapFromSeaToMap";
	pchar.quest.(name).CapId = sld.id; 
	
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}


void CitizSeekCap_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString)
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;
		ref npchar = &characters[GetCharacterIndex("QuestCitiz_" + sld.quest.cribCity)];
		string sTitle = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "3");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandByCityName(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", ", on the " + XI_ConvertString(GetIslandByCityName(sld.quest.targetCity) + "Dat"));
		}
	}
}


void SetShowTimer(float time)
{
	pchar.showTimer = time + 0.99;
	pchar.quest.ClearTimer.win_condition.l1 = "ExitFromLocation";
	pchar.quest.ClearTimer.win_condition.l1.location = pchar.location;
	pchar.quest.ClearTimer.function = "ClearTimer";
}

void ClearTimer(string qName)
{
	DeleteAttribute(pchar, "showTimer");
	ClearAllLogStrings();
}


void CopyPassForAztecSkull()
{
	if (CheckCharacterItem(pchar, "SkullAztec"))
	{	
        
		DeleteAttribute(pchar, "AztecSkull");
		pchar.AztecSkull = "";
		
		string sTemp,;
		aref	arFromBox, arToBox;
    	makearef(arFromBox, pchar.fellows.passengers.officers);
		makearef(arToBox, pchar.AztecSkull);
		CopyAttributes(arToBox, arFromBox);
	}
}

bool IsAztecSkullOfficer(ref sld)
{
	if (!CheckAttribute(pchar, "AztecSkull.id1")) return false;
	string sTemp;
	aref arOfficer;
    makearef(arOfficer, pchar.AztecSkull);
    for (i=1; i<=3; i++)
    {
		sTemp = "id" + i;
		if (arOfficer.(sTemp) == sld.index)
		{
			return true;
		}
	}
	return false;
}


bool CheckMainHeroMap(string itemName)
{
    if( CheckAttribute(pchar,"Items."+itemName) && sti(pchar.Items.(itemName))>0 )	
	{
		return true;
	}
	return false;	
}



void OtherQuestCharactersInit()
{
}


void MaryCelesteInit()
{
	ref character, realShip;
	String capID = "MaryCelesteCapitan";
	String seaGroup = "MaryCelesteGroup";
	int good;
	
	
	
	 
	
	int generableGoods[15];
	
	generableGoods[0] = GOOD_FOOD;
	generableGoods[1] = GOOD_WEAPON;
	generableGoods[2] = GOOD_MAHOGANY;
	generableGoods[3] = GOOD_MEDICAMENT;
	generableGoods[4] = GOOD_PAPRIKA;
	generableGoods[5] = GOOD_COPRA;
	generableGoods[6] = GOOD_COFFEE;
	generableGoods[7] = GOOD_CLOTHES;
	generableGoods[8] = GOOD_EBONY;
	generableGoods[9] = GOOD_TOBACCO;
	generableGoods[10] = GOOD_CHOCOLATE;
	generableGoods[11] = GOOD_WINE;
	generableGoods[12] = GOOD_RUM;
	generableGoods[13] = GOOD_CINNAMON;
	generableGoods[14] = GOOD_LEATHER;
	
	character = GetCharacter(NPC_GenerateCharacter(capID , "citiz_45", "man", "man", 50, ENGLAND, -1, true, "citizen"));
	FantomMakeCoolSailor(character, SHIP_BRIGANTINE, "Mary Celeste", CANNON_TYPE_CANNON_LBS16, 50, 50, 50);
	character.name = "The ship is empty";
	character.lastname = "";
	character.mapEnc.type = "trade";
	character.mapEnc.Name = "brigantine 'Mary Celeste'";
	LAi_SetImmortal(character, true);
	SetCharacterGoods(character, GOOD_RUM, 700);
	Character_SetAbordageEnable(character, false); 
	
	SetCrewQuantityOverMax(character, 0); 
	
	realShip = GetRealShip(GetCharacterShipType(character));
	
	PChar.QuestTemp.MaryCeleste = "NotFind";
	PChar.QuestTemp.MaryCeleste.TurnRate = realShip.TurnRate; 
	
	realShip.lowpolycrew = 0; 
	realShip.TurnRate = 1; 
	realShip.capacity = 2820;
	
	NullCharacterGoods(character); 
	
	AddCharacterGoodsSimple(character, GOOD_BALLS, 		200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_GRAPES, 	200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_KNIPPELS, 	200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_BOMBS, 		100 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_POWDER, 	500 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_FOOD, 		50  + rand(50));
	AddCharacterGoodsSimple(character, GOOD_WEAPON, 	20  + rand(30));
	AddCharacterGoodsSimple(character, GOOD_MEDICAMENT, 10  + rand(20));
	AddCharacterGoodsSimple(character, GOOD_SAILCLOTH,  50  + rand(50));
	AddCharacterGoodsSimple(character, GOOD_PLANKS,     20  + rand(30));
	
	good = generableGoods[rand(14)];
	
	AddCharacterGoodsSimple(character, good, GetCharacterFreeSpace(character, good) - 1);
	
	character.AlwaysFriend = true; 
	character.ShipEnemyDisable = true; 
	character.CanDropSails = false; 
	
	Group_FindOrCreateGroup(seaGroup);
	Group_SetTaskAttackInMap(seaGroup, PLAYER_GROUP);
	Group_LockTask(seaGroup);
	Group_AddCharacter(seaGroup, capID);
	Group_SetGroupCommander(seaGroup, capID);
	SetRandGeraldSail(character, ENGLAND);
	
	character.fromCity = SelectAnyColony(""); 
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); 
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	Map_CreateTrader(character.fromShore, character.toShore, capID, GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)));
	
	
}


void TestShipInCurrentSea()
{
	ref sld;

	int iRank = sti(PChar.rank) + 7;

    Group_FindOrCreateGroup("Pirate_Attack");
	Group_SetType("Pirate_Attack", "war");
	
	sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "mercen_"+(rand(14)+14), "man", "man", 10, PIRATE, 3, true, "quest"));
	FantomMakeSmallSailor(sld, SHIP_VALCIRIA, "���������", CANNON_TYPE_CANNON_LBS20, 60+rand(10), 55+rand(20), 55+rand(20), 50+rand(15), 55+rand(25));
	FantomMakeCoolFighter(sld, iRank, 60, 60, "blade_14", "pistol3", "grapeshot", 100);

	Group_AddCharacter("Pirate_Attack", "CaptainAttack_1");
		
	sld.SuperShooter  = true;

	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "MusketsShoot");
	
	sld.ship.Crew.Morale = 50 + rand(30);
	ChangeCrewExp(sld, "Sailors", 70 + rand(10));
	ChangeCrewExp(sld, "Cannoners", 70 + rand(10));
	ChangeCrewExp(sld, "Soldiers", 70 + rand(10));
    	
	Group_SetGroupCommander("Pirate_Attack", "CaptainAttack_1");
	Group_SetAddress("Pirate_Attack", "Cuba2", "", "");
	Group_SetTaskAttack("Pirate_Attack", PLAYER_GROUP);
	Group_LockTask("Pirate_Attack");
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	
	Sea_LoginGroupCurrentSea("Pirate_Attack");
	log_info("��������� �� ���������!");
	PlaySound("interface\_EvEnemy1.wav");
}

