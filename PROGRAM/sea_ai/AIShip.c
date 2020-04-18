object	Sail, Rope, Flag, Vant, VantL, VantZ ;

#define MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER				1000.0
#define MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER_FORT		1400.0
#define MIN_ENEMY_DISTANCE_TO_DISABLE_ENTER_2_LOCATION		1150.0

bool	bAbordageShipCanBe = false;
int		iAbordageShipEnemyCharacter;


bool	bCanEnterToLand = false;
aref	arIslandReload;
string	sIslandLocator;
string	sIslandID;
string	sSeaSoundPostfix;
int		iShipPriorityExecute = 2;
int		iShipPriorityRealize = 31;
bool	bUpdatePosMode = false;
int		iVicSoundTime = 0;
string	sSeaStartMusicName;
bool	isEnemyAround = false;

int		iNumShips = 0;
int		Ships[MAX_SHIPS_ON_SEA];

#define SHIP_DETONATE_SMALL		"ShipDetonateSmall"

#event_handler("Ship_StartLoad", "Ship_StartLoad");
#event_handler("Ship_EndLoad", "Ship_EndLoad");

void CreateRiggingEnvironment()
{
	CreateEntity(&Sail, "Sail");
	LayerAddObject(sCurrentSeaExecute, &Sail, iShipPriorityExecute + 1);
	LayerAddObject(sCurrentSeaRealize, &Sail, iShipPriorityRealize + 1);
	LayerAddObject("sails_trace", &Sail, 10);
	LayerAddObject("sea_reflection2", &Sail, 3);
	Sail.MinSpeed = 0.05;

	CreateEntity(&Rope, "Rope");
	LayerAddObject(sCurrentSeaExecute, &Rope, iShipPriorityExecute + 2);
	LayerAddObject(sCurrentSeaRealize, &Rope, iShipPriorityRealize + 2);
	
	CreateEntity(&Flag, "Flag");
	LayerAddObject(sCurrentSeaExecute, &Flag, iShipPriorityExecute + 3);
	LayerAddObject(sCurrentSeaRealize, &Flag, iShipPriorityRealize + 3);
	LayerAddObject("sea_reflection2", &Flag, 3);
	
	CreateEntity(&Vant, "Vant");
	LayerAddObject(sCurrentSeaExecute, &Vant, iShipPriorityExecute + 4);
	LayerAddObject(sCurrentSeaRealize, &Vant, iShipPriorityRealize + 4);
	
	CreateEntity(&VantL, "VantL");
	LayerAddObject(sCurrentSeaExecute, &VantL, iShipPriorityExecute + 4);
	LayerAddObject(sCurrentSeaRealize, &VantL, iShipPriorityRealize + 4);
	
	CreateEntity(&VantZ, "VantZ");
	LayerAddObject(sCurrentSeaExecute, &VantZ, iShipPriorityExecute + 4);
	LayerAddObject(sCurrentSeaRealize, &VantZ, iShipPriorityRealize + 4);
	
	iNumShips = 0;
}

void DeleteRiggingEnvironment()
{
	DeleteClass(&Sail);
	DeleteClass(&Rope);
	DeleteClass(&Flag);
	DeleteClass(&Vant);
	DeleteClass(&VantL);
	DeleteClass(&VantZ);
}

void DeleteShipEnvironment()
{
	DeleteRiggingEnvironment();

	DelEventHandler(SHIP_CHANGE_CHARGE, "Ship_ChangeChargeEvent");  
	DelEventHandler(SHIP_DROP_GOOD, "DropGoodsToSea");
	DelEventHandler(SHIP_HULL_HIT, "Ship_HullHitEvent");
	DelEventHandler(SHIP_CHECK_RELOAD_ENABLE, "Ship_CheckMainCharacter");
	DelEventHandler(SHIP_DETONATE_SMALL, "Ship_DetonateSmall");
	DelEventHandler(SHIP_BRANDER_DETONATE, "Ship_BranderDetonate");
	DelEventHandler(SHIP_FIRE_DAMAGE, "Ship_FireDamage");
	DelEventHandler(SHIP_TO_STRAND_NEXT, "Ship_OnStrandNext");
	DelEventHandler(SHIP_BORT_RELOADED, "Ship_OnBortReloaded");
	DelEventHandler(SHIP_ACTIVATE_FIRE_PLACE, "Ship_ActivateFirePlace");
	DelEventHandler(SHIP_UPDATE_PARAMETERS, "Ship_UpdateParameters");
	DelEventHandler(SHIP_CHECK_SITUATION, "Ship_CheckSituation");
	DelEventHandler(WHR_LIGHTNING, "Ship_Lightning");
	DelEventHandler("eSwitchPerks", "Ship_UpdatePerks");
	DelEventHandler("TornadoDamage", "Ship_TornadoDamage");
	DelEventHandler(SHIP_GET_RUNAWAY_POINT, "Ship_GetRunAwayPoint");
	DelEventHandler("frame", "Ship_VicSoundTime");
	DelEventHandler("Ship_SailsMoveSound", "Ship_SailsMoveSound");
	DelEventHandler("Ship_BortReloadEvent", "Ship_BortReloadEvent");
	DelEventHandler("Ship_VolleyHeelEnd", "Ship_VolleyHeelEnd");
	DelEventHandler(SHIP_SET_BLOT, "Ship_SetBlot");

	for (int i=0; i<iNumShips; i++) 
	{ 
		
		SendMessage(&Characters[Ships[i]], "l", MSG_SHIP_SAFE_DELETE); 

		
		if (CheckAttribute(&Characters[Ships[i]], "Ship.Sounds.WaterID")) 	ReleaseSound(sti(Characters[Ships[i]].Ship.Sounds.WaterID));
		if (CheckAttribute(&Characters[Ships[i]], "Ship.Sounds.SailsID"))   ReleaseSound(sti(Characters[Ships[i]].Ship.Sounds.SailsID));
		if (CheckAttribute(&Characters[Ships[i]], "Ship.Sounds.TurnID"))   ReleaseSound(sti(Characters[Ships[i]].Ship.Sounds.TurnID));
	}

	
	DeleteEntitiesByType("ship");
}

void ClearAllFire() 
{
    for (int i=0; i<iNumShips; i++)
	{
		
		SendMessage(&Characters[Ships[i]], "l", MSG_SHIP_SAFE_DELETE);
	}
}

void Sea_ClearCheckFlag() 
{
    if (bSeaActive)
    {
		int i;
		
		for (i=0; i<iNumShips; i++)
		{
			if (!CheckAttribute(&Characters[Ships[i]], "DontCheckFlag"))
			{
			    DeleteAttribute(&Characters[Ships[i]], "CheckFlagYet"); 
			    DeleteAttribute(&Characters[Ships[i]], "CheckFlagDate");
			}
			
		}
		
		for (i=0; i<MAX_COLONIES; i++)
		{
			if (CheckAttribute(&colonies[i], "commanderIdx"))
			{
				if (!CheckAttribute(&Characters[sti(colonies[i].commanderIdx)], "DontCheckFlag"))
				{
					DeleteAttribute(&Characters[sti(colonies[i].commanderIdx)], "CheckFlagYet"); 
				    DeleteAttribute(&Characters[sti(colonies[i].commanderIdx)], "CheckFlagDate");
			    }
			}
		}
	}
}

void CreateShipEnvironment()
{
	isEnemyAround = false;
	bUpdatePosMode = false;
	iVicSoundTime = 0;

	bAbordageFortCanBe = false;
	bAbordageShipCanBe = false;
	bCanEnterToLand = false;
	sIslandLocator = "";
	sIslandID = "";
	
	for (int i = 0; i < MAX_SHIPS_ON_SEA; i++) Ships[i] = -1;

	aref arCurWeather = GetCurrentWeather();
	sSeaSoundPostfix = arCurWeather.Sounds.Sea.Postfix;

	CreateRiggingEnvironment();

	SetEventHandler(SEA_GET_LAYERS, "SeaAI_GetLayers", 0);

	SetEventHandler(SHIP_NOT_ENOUGH_BALLS, "Ship_NotEnoughBalls", 0);
	SetEventHandler(SHIP_GET_CURRENT_BALLS_NUM, "Ship_GetCurrentBallsNum", 0);
	SetEventHandler(SHIP_SHIP2ISLAND_COLLISION, "Ship_Ship2IslandCollision", 0);
	SetEventHandler(SHIP_SHIP2SHIP_COLLISION, "Ship_Ship2ShipCollision", 0);
	SetEventHandler(SHIP_SAIL_DAMAGE, "Ship_SailDamage", 0);
	SetEventHandler(SHIP_FIRE_DAMAGE, "Ship_FireDamage", 0);
	SetEventHandler(SHIP_CHECK_SITUATION, "Ship_CheckSituation", 0);
	SetEventHandler(SHIP_TO_STRAND, "Ship_OnStrand", 0);
	SetEventHandler(SHIP_TO_STRAND_NEXT, "Ship_OnStrandNext", 0);
	SetEventHandler(SHIP_DEAD, "Ship_OnDead", 0);
	SetEventHandler(SHIP_UPDATE_PARAMETERS, "Ship_UpdateParameters", 0);
	SetEventHandler(SHIP_DROP_GOOD, "DropGoodsToSea", 0);
	SetEventHandler(SHIP_CREATE, "Ship_OnCreate", 0);
	SetEventHandler(SHIP_BORT_RELOADED, "Ship_OnBortReloaded", 0);
	SetEventHandler(SHIP_CHANGE_CHARGE, "Ship_ChangeChargeEvent", 0);
	SetEventHandler(SHIP_HULL_HIT, "Ship_HullHitEvent", 0);
	SetEventHandler(SHIP_CHECK_RELOAD_ENABLE, "Ship_CheckMainCharacter", 0);
	SetEventHandler(SHIP_FIRE_ACTION, "Ship_FireAction", 0);
	SetEventHandler(SHIP_GET_BORT_FIRE_DELTA, "Ship_GetBortFireDelta", 0);
	SetEventHandler(SHIP_DETONATE_SMALL, "Ship_DetonateSmall", 0);
	SetEventHandler(SHIP_ACTIVATE_FIRE_PLACE, "Ship_ActivateFirePlace", 0);
	SetEventHandler(WHR_LIGHTNING, "Ship_Lightning", 0);
	SetEventHandler(SHIP_CREATELOADSHIP, "Ship_LoadShip", 0);
	SetEventHandler(SHIP_LOAD_SHIPACTIVATEFIREPLACE, "Ship_LoadShipActivateFirePlace", 0);
	SetEventHandler(SHIP_GET_RUNAWAY_POINT, "Ship_GetRunAwayPoint", 0);
	SetEventHandler("TornadoDamage", "Ship_TornadoDamage", 0);

	SetEventHandler(SHIP_BRANDER_DETONATE, "Ship_BranderDetonate", 0);
	SetEventHandler(SHIP_MAST_DAMAGE, "Ship_MastDamage", 0);	
	SetEventHandler(SHIP_HULL_DAMAGE, "Ship_HullDamage", 0); 
	SetEventHandler("eSwitchPerks", "Ship_UpdatePerks", 0);
	SetEventHandler("frame", "Ship_VicSoundTime", 0);
	SetEventHandler("Ship_SailsMoveSound", "Ship_SailsMoveSound", 0);
	SetEventHandler("Ship_BortReloadEvent", "Ship_BortReloadEvent", 0);
	SetEventHandler("Ship_VolleyHeelEnd", "Ship_VolleyHeelEnd", 0);
	SetEventHandler(SHIP_SET_BLOT, "Ship_SetBlot", 0);
}	

float Ship_GetBortFireDelta()
{
	aref aCharacter = GetEventData();
	float x = GetEventData();
	float y = GetEventData();
	float z = GetEventData();
	float fDistance = GetDistance2D(x, z, stf(aCharacter.Ship.Pos.x), stf(aCharacter.Ship.Pos.z));
	
	float fAccuracy = 1.3 - stf(aCharacter.TmpSkill.Accuracy);
	
	
	if (iArcadeSails == 1)
	{
		fAccuracy  = fAccuracy - 0.2;
		if (fAccuracy < 0.1)
		{
			fAccuracy = 0.1;
		}
	}
	 
	

	float fRadius = fAccuracy * Bring2Range(0.0, 120.0, 0.0, 1000.0, fDistance);
	return fRadius;
}

string Ship_GetGroupID(ref rCharacter)
{
 	if (CheckAttribute(rCharacter, "SeaAI.Group"))
    {
        return rCharacter.SeaAI.Group.Name;
    }
    else
    {
        return "";
    }
}

void Ship_NationAgressivePatent(ref rCharacter)
{
	
    ref rMainCharacter = GetMainCharacter();

    if (isMainCharacterPatented())
    {
        if (sti(rCharacter.nation) != PIRATE && GetNationRelation(sti(Items[sti(rMainCharacter.EquipedPatentId)].Nation), sti(rCharacter.nation)) != RELATION_ENEMY)
        {
        	TakeItemFromCharacter(rMainCharacter, "patent_" + NationShortName(sti(Items[sti(rMainCharacter.EquipedPatentId)].Nation)));
        	ChangeCharacterHunterScore(rMainCharacter, NationShortName(sti(Items[sti(rMainCharacter.EquipedPatentId)].Nation)) + "hunter", 40);
        	Items[sti(rMainCharacter.EquipedPatentId)].TitulCur = 1; 
        	Items[sti(rMainCharacter.EquipedPatentId)].TitulCurNext = 0; 
        	RemoveCharacterEquip(rMainCharacter, "patent");
        	rCharacter.CheckNationBounty = true;
        }
    }
    else
    {
    	if (sti(rCharacter.nation) != PIRATE && !CheckAttribute(rCharacter, "CheckNationBounty"))   
    	{
    		if (GetNationRelation(GetBaseHeroNation(), sti(rCharacter.nation)) != RELATION_ENEMY)
    		{
				rCharacter.CheckNationBounty = true;
				ChangeCharacterHunterScore(rMainCharacter, NationShortName(sti(rCharacter.nation)) + "hunter", 1 + rand(2));
			}
    	}
    }
}
void Ship_NationAgressive(ref rMainGroupCharacter, ref rCharacter)
{    
    ref rMainCharacter = GetMainCharacter();
    
    if (CheckAttribute(rCharacter, "Coastal_Captain")) return;  

	
	if (rCharacter.id == "MQPirate" && sti(rCharacter.nation) != PIRATE)
	{
		rCharacter.nation = PIRATE;
		Ship_FlagRefresh(characterFromId("MQPirate")); 
		
      	Pchar.quest.DestroyPirate_PirateIsOut.win_condition.l1 = "ExitFromSea";
		Pchar.quest.DestroyPirate_PirateIsOut.win_condition = "DestroyPirate_PirateIsOut";
	}
	
	else
	{
		if (CheckAttribute(rCharacter, "ShipEnemyDisable") || CheckAttribute(rCharacter, "AlwaysFriend"))  return; 
	    if( sti(rMainCharacter.nation) == sti(rCharacter.nation) && sti(rMainCharacter.nation) != PIRATE)
	    {
            SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
            rMainCharacter.nation = PIRATE;
			DoQuestCheckDelay(NationShortName(PIRATE) + "_flag_rise", 0.1); 
	        ChangeCharacterComplexReputation(rMainCharacter,"nobility", -10);
			ChangeCharacterComplexReputation(rMainCharacter,"authority", -2);
			ChangeCharacterComplexReputation(rMainCharacter,"fame", 0.5);
	    }
	    Ship_NationAgressivePatent(rCharacter); 
		
	    
		for (int i=0; i<MAX_SHIP_GROUPS; i++) { AIGroups[i].TempTask = false; } 

	    SetNationRelation2MainCharacter(sti(rMainGroupCharacter.nation), RELATION_ENEMY);
	    SetCharacterRelationBoth(sti(rMainGroupCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
	    
	    if (sti(rMainGroupCharacter.nation) != PIRATE)
	    {
	    	ChangeCharacterHunterScore(rMainCharacter, NationShortName(sti(rMainGroupCharacter.nation)) + "hunter", 5);
	    }
    }
    
}

void Ship_FireAction()
{
	aref rCharacter = GetEventData();				
	aref rMainGroupCharacter = GetEventData();		
	int iRelation = GetEventData();
	
	if (LAi_IsDead(rCharacter)) return; 
	
	
	if (IsCompanion(rCharacter))
	{
		if (CheckAttribute(rCharacter, "CompanionEnemyEnable") && sti(rCharacter.CompanionEnemyEnable))
		{
			SeaAI_SetCompanionEnemy(rCharacter);
			
		}
		return;
	}
	else
	{
	    if (CheckAttribute(rCharacter, "ShipEnemyDisable") )  return; 
	    
	    DeleteAttribute(rCharacter, "AlwaysFriend");
	}
			
	if (iRelation != RELATION_ENEMY)
	{
		Ship_NationAgressive(rMainGroupCharacter, rCharacter);

		
		if (CheckAttribute(rMainGroupCharacter, "SeaAI.Group.Name"))
		{
			Group_SetEnemyToCharacter(rMainGroupCharacter.SeaAI.Group.Name, nMainCharacterIndex);
		}
		 
	}
	else
	{
	    
    	Ship_NationAgressivePatent(rCharacter);
	}
	DoQuestCheckDelay("NationUpdate", 0.3);
	
	RefreshBattleInterface();
	
	
	if (CheckAttribute(rCharacter, "ShipTaskLock")) return;
	
	int i;
	string sGroupID, sGroupType;
	ref rGroup;

	
	for (i=0; i<MAX_SHIP_GROUPS; i++) { AIGroups[i].TempTask = false; }

	
	for (i=0; i<iNumShips; i++)
	{
		ref rShipCharacter = GetCharacter(Ships[i]);

		if (SeaAI_GetRelation(GetMainCharacterIndex(), Ships[i]) != RELATION_ENEMY) { continue; }

		sGroupID = Ship_GetGroupID(rShipCharacter);
		sGroupType = Group_GetType(sGroupID);
		rGroup = Group_GetGroupByID(sGroupID);

		float fDistance = Ship_GetDistance2D(GetMainCharacter(), rShipCharacter);

		
		 
	}

	
	int iShipType = sti(rCharacter.Ship.Type);
	iShipType = sti(RealShips[iShipType].basetype);
	if (ShipsTypes[iShipType].name == "Fort") 
	{ 
		return; 
	}
	
	sGroupID = Ship_GetGroupID(rMainGroupCharacter);

	Group_SetTaskAttack(PLAYER_GROUP, sGroupID);
}

void Ship_SetBlot()
{
	aref rCharacter = GetEventData();
	
	
}

float Ship_MastDamage()
{
	int iDamageType 	= GetEventData();
	int iMastNum 		= GetEventData();
	float x 			= GetEventData();
	float y 			= GetEventData();
	float z 			= GetEventData();
	float fDamage 		= GetEventData();
	aref rCharacter 	= GetEventData();
	
	switch (iDamageType)
	{
		case SHIP_MAST_TOUCH_ISLAND:
			fDamage = fDamage + 0.25;
		break;
		case SHIP_MAST_TOUCH_SHIP:
			fDamage = fDamage + 0.2;
		break;
		case SHIP_MAST_TOUCH_BALL:
			int iBallOwnerIndex 	= GetEventData();
			ref	rBallCharacter 		= GetCharacter(iBallOwnerIndex);	
			int	iBallType = sti(AIBalls.CurrentBallType);   			
			switch (iBallType)
			{
				case GOOD_BALLS:
					fDamage = fDamage + 0.1;
				break;
				case GOOD_GRAPES:
					fDamage = fDamage + 0.05;
				break;
				case GOOD_KNIPPELS:
					fDamage = fDamage + 0.25;
				break;
				case GOOD_BOMBS:
					fDamage = fDamage + 0.15;
				break;
			}
			
		break;
	}
	if (2-sti(RealShips[sti(rCharacter.ship.type)].Class) > 0) 
	{
		fDamage = fDamage/2;
	}
	fDamage = Clampf(fDamage);

	if (fDamage >= 1.0)
	{
		Play3DSound("mast_fall", x, y, z);	
		rCharacter.Tmp.SpeedRecall = 0; 	
		RefreshBattleInterface();
	}
	
	if(iDamageType == SHIP_MAST_TOUCH_BALL)
	{
		rCharacter.Ship.LastBallCharacter = iBallOwnerIndex;

		if (sti(rCharacter.Ship.LastBallCharacter) == GetMainCharacterIndex() 
			&& GetNationRelation2MainCharacter(sti(rCharacter.nation)) != RELATION_ENEMY)
		{
			if (!IsCompanion(rCharacter) && !CheckAttribute(rCharacter, "Coastal_Captain")) 
			{
				Ship_NationAgressive(rCharacter, rCharacter);
				DoQuestCheckDelay("NationUpdate", 0.7);
			}
		}		
	}	
	return fDamage;	
}

float Ship_HullDamage()
{
	int iDamageType = GetEventData();
	int iHullNum = GetEventData(); 
	float x = GetEventData();
	float y = GetEventData();
	float z = GetEventData();
	float fDamage = GetEventData();
	aref rCharacter = GetEventData(); 
	aref aCharacter = GetEventData(); 
	string HullName = GetEventData(); 
	
	switch (iDamageType)
	{
		case SHIP_HULL_TOUCH_BALL:
			int	iBallType = sti(AIBalls.CurrentBallType);   
			switch (iBallType)
			{
				case GOOD_BALLS:
					fDamage = fDamage + 0.40;
				break;
				case GOOD_GRAPES:
					fDamage = fDamage + 0.10;
				break;
				case GOOD_KNIPPELS:
					fDamage = fDamage + 0.20;
				break;
				case GOOD_BOMBS:
					fDamage = fDamage + 0.65;
				break;
			}
		break;
	}

	fDamage = Clampf(fDamage);
	if (fDamage >= 1.0)
	{
		CreateBlast(x,y,z);
		CreateParticleSystem("blast_inv", x, y, z, 0.0, 0.0, 0.0, 0);
		Play3DSound("cannon_explosion", x, y, z); 	
		RefreshBattleInterface();
		
		if(HasSubStr(HullName, "baller")) 
		{
			rCharacter.Ship.hulls.baller_destroyed = true; 
			string sDamagedString = "They damaged a helm of '" + rCharacter.Ship.Name + "', she is out of control now.";
			Log_SetStringToLog(sDamagedString);
		}
	}
	return fDamage;
}


float Ship_GetSailState(ref rCharacter)
{
	float fSailState = 1.0;
	SendMessage(rCharacter, "le", MSG_SHIP_GET_SAIL_STATE, &fSailState);
	return fSailState;
}

void Ship_SetExplosion(ref rCharacter, ref	rShipObject)
{
    int i = 0;
    
	
	
	
	
		
	
	
	PostEvent(SHIP_BRANDER_DETONATE, 800, "l", sti(rCharacter.index));
    PlaySound("Sea Battles\Vzriv_fort_001.wav");
	Ship_SetTaskNone(SECONDARY_TASK, sti(rCharacter.index));
}

void Ship_SetSailState(int iCharacterIndex, float fSailState)
{
	SendMessage(&AISea, "laf", AI_MESSAGE_SHIP_SET_SAIL_STATE, &Characters[iCharacterIndex], fSailState);
}

void Ship_SetTaskNone(int iTaskPriority, int iCharacterIndex)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_NONE;
}

void Ship_SetTaskAbordage(int iTaskPriority, int iCharacterIndex, int iCharacterIndexAbordageTo)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_ABORDAGE;
	rCharacter.SeaAI.Task.Target = iCharacterIndexAbordageTo;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_ABORDAGE, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndexAbordageTo]);
}

void Ship_SetTaskBrander(int iTaskPriority, int iCharacterIndex, int iCharacterIndexBranderTo)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_BRANDER;
	rCharacter.SeaAI.Task.Target = iCharacterIndexBranderTo;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_BRANDER, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndexBranderTo]);
}

void Ship_SetTaskMove(int iTaskPriority, int iCharacterIndex, float x, float z)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_MOVE;
	
	rCharacter.SeaAI.Task.Pos.x = x;
	rCharacter.SeaAI.Task.Pos.z = z;
	SendMessage(&AISea, "lllaff", AI_MESSAGE_SHIP_SET_TASK, AITASK_MOVE, iTaskPriority, &Characters[iCharacterIndex], x, z);
}

void Ship_SetTaskRunaway(int iTaskPriority, int iCharacterIndex, int iFromIndex)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_RUNAWAY;
	rCharacter.SeaAI.Task.Target = iFromIndex;	
	SendMessage(&AISea, "llla", AI_MESSAGE_SHIP_SET_TASK, AITASK_RUNAWAY, iTaskPriority, &Characters[iCharacterIndex]);	
}

void Ship_SetTaskAttack(int iTaskPriority, int iCharacterIndex, int iCharacterIndexVictim)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_ATTACK;
	rCharacter.SeaAI.Task.Target = iCharacterIndexVictim;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_ATTACK, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndexVictim]);
}

void Ship_SetTaskSailTo(int iTaskPriority, int iCharacterIndex, int iCharacterIndexSailTo)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_MOVE;
	rCharacter.SeaAI.Task.Target = iCharacterIndexSailTo;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_MOVE, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndexSailTo]);
}

void Ship_SetTaskDrift(int iTaskPriority, int iCharacterIndex)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_DRIFT;
	
	SendMessage(&AISea, "llla", AI_MESSAGE_SHIP_SET_TASK, AITASK_DRIFT, iTaskPriority, &Characters[iCharacterIndex]);
}

void Ship_SetTaskDefendGroup(int iTaskPriority, int iCharacterIndex, string sDefendGroup)
{
	SendMessage(&AISea, "lllas", AI_MESSAGE_SHIP_SET_TASK, AITASK_DEFEND_GROUP, iTaskPriority, &Characters[iCharacterIndex], sDefendGroup);
}

void Ship_SetTaskDefend(int iTaskPriority, int iCharacterIndex, int iCharacterIndex2Defend)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_DEFEND;
	rCharacter.SeaAI.Task.Target = iCharacterIndex2Defend;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_DEFEND, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndex2Defend]);
}

void Ship_DoFire()
{
	int bCameraOutside = SeaCameras_isCameraOutside();
	SendMessage(&AISea, "lal", AI_MESSAGE_CANNON_FIRE, &Characters[nMainCharacterIndex], bCameraOutside);
}

void Ship_StartLoad()
{
	aref rCharacter = GetEventData();
	if(rCharacter.id != "0" && sti(rCharacter.ship.type) != SHIP_NOTUSED)
	{
		ref refBaseShip;
		int nShipType = GetCharacterShipType(rCharacter);
		refBaseShip = GetRealShip(nShipType);
		SetTextureForShip(refBaseShip, rCharacter);
	}
}

void Ship_EndLoad()
{
	SetTexturePath(0, "");
}

void Ship_SetTrackSettings(ref rCharacter)
{
	ref rShip = GetRealShip(GetCharacterShipType(rCharacter));

	rCharacter.Ship.Track.Enable = rShip.Track.Enable;
	if (!sti(rShip.Track.Enable)) return;

	rCharacter.Ship.Track.TrackDistance = 1.0;
	rCharacter.Ship.Track.WaveHeight2 = 0.9;
	rCharacter.Ship.Track.WaveHeight1 = 0.2;

	rCharacter.Ship.Track1.Texture = "ships\trailShip.tga";
	rCharacter.Ship.Track1.TrackWidthSteps = 12.0;

	rCharacter.Ship.Track2.Texture = "ships\trailKeel.tga";
	rCharacter.Ship.Track2.TrackWidthSteps = 4.0;

	rCharacter.Ship.Track1.ZStart = rShip.Track1.ZStart;
	rCharacter.Ship.Track1.LifeTime = rShip.Track1.LifeTime;
	rCharacter.Ship.Track1.Width = rShip.Track1.Width;
	rCharacter.Ship.Track1.Speed = rShip.Track1.Speed;

	rCharacter.Ship.Track2.ZStart = rShip.Track2.ZStart;
	rCharacter.Ship.Track2.LifeTime = rShip.Track2.LifeTime;
	rCharacter.Ship.Track2.Width = rShip.Track2.Width;
	rCharacter.Ship.Track2.Speed = rShip.Track2.Speed;
}

void Ship_SetLightsOff(ref rCharacter, float fTime, bool bLights, bool bFlares, bool bNow)
{
	SendMessage(rCharacter, "lflll", MSG_SHIP_SETLIGHTSOFF, fTime, bLights, bFlares, bNow);
	rCharacter.Ship.Lights = 0; 
}

void Ship_SetLightsAndFlares(ref rCharacter)
{
	if(sti(sea.lights) == 1)
	{
		rCharacter.Ship.Flares = 1;
		rCharacter.Ship.Lights = 1;
	}
	else
	{
		rCharacter.Ship.Flares = 0;
		rCharacter.Ship.Lights = 0;
	}
}

void Ship_Add2Sea(int iCharacterIndex, bool bFromCoast, string sFantomType, bool isOffline)
{
	ref		rCharacter = GetCharacter(iCharacterIndex);

	DeleteAttribute(rCharacter, "ship.cannons.chance_for_explode"); 

	aref	arCharacter; makearef(arCharacter, Characters[sti(rCharacter.index)]);
	
	int iShipType = sti(rCharacter.Ship.Type);

	if(iShipType == SHIP_NOTUSED)
	{
		return;
	}

	int iRealShip = sti(RealShips[iShipType].basetype);

	if(!CheckAttribute(&RealShips[iShipType], "name"))
	{
		Trace("Ship_Add2Sea() : SHIP " + iShipType + ", have no name!   NPCid = "+ rCharacter.id);
		if (MOD_BETTATESTMODE == "On") Log_Info("Ship_Add2Sea ERROR : SHIP " + iShipType + ", have no name!   NPCid = "+ rCharacter.id);
		return;
	}
	if (iRealShip >= SHIP_TYPES_QUANTITY)
	{
		Trace("Character.id = " + rCharacter.id + ", have invalid ship type = " + iShipType + ", and try load to sea");
		return;
	}
	
	
    if (!CheckAttribute(rCharacter, "AlwaysEnemy") && !CheckAttribute(rCharacter, "AlwaysFriend")) 
    {
    	DelCharacterRelation(iCharacterIndex);
    }
    else
    {
		if (CheckAttribute(rCharacter, "AlwaysFriend"))
		{
			SetCharacterRelationBoth(iCharacterIndex, GetMainCharacterIndex(), RELATION_FRIEND);
		}
		if (CheckAttribute(rCharacter, "AlwaysEnemy"))
		{
			SetCharacterRelationBoth(iCharacterIndex, GetMainCharacterIndex(), RELATION_ENEMY);
		}
    }
    DeleteAttribute(rCharacter, "Ship_SetTaskAbordage"); 
    DeleteAttribute(rCharacter, "Killer.status"); 
    DeleteAttribute(rCharacter, "CheckFlagYet"); 
    DeleteAttribute(rCharacter, "CheckNationBounty"); 
    DeleteAttribute(rCharacter, "ShipCannonChargeType"); 
    
	if (CheckAttribute(rCharacter, "DontCheckFlag"))
	{
	    rCharacter.CheckFlagYet = true;
	}
    rCharacter.TmpSkillRecall = "0"; 
    rCharacter.Tmp.SpeedRecall = 0; 
    rCharacter.Tmp.fShipSpeed  = 1; 
	rCharacter.Tmp.fWatchFort  = rand(15); 
	rCharacter.Tmp.fWatchFort.Qty = 15;
    
	if (iCharacterIndex >= FANTOM_CHARACTERS)
	{
		SetBaseShipData(rCharacter);
		Ship_SetFantomData(rCharacter);
		Fantom_SetUpgrade(rCharacter, sFantomType);		
        Fantom_SetCannons(rCharacter, sFantomType);
		Fantom_SetBalls(rCharacter, sFantomType);
		Fantom_SetGoods(rCharacter, sFantomType);
		SaveCurrentNpcQuestDateParam(rCharacter, "Add2SeaTime"); 
	}
    AcceptWindCatcherPerk(rCharacter); 
	

	CharacterUpdateShipFromBaseShip(iCharacterIndex);

	rCharacter.Ship.Ang.y = 0.0;

	Ship_ClearImpulseStrength(rCharacter);
	Ship_SetLightsAndFlares(rCharacter);
	Ship_SetTrackSettings(rCharacter);

	aref baseship;
	ref refBaseShip;
	
	makearef(baseship,rCharacter.ship);
	int nShipType = GetCharacterShipType(rCharacter);
	refBaseShip = GetRealShip(nShipType);
	
	rCharacter.Tmp.BortsReloaded.Event = false;
	rCharacter.Tmp.BortsReloaded.cannonl = false;
	rCharacter.Tmp.BortsReloaded.cannonr = false;
    rCharacter.BOAL_ReadyCharge = "1"; 
    
	rCharacter.Features.GeraldSails = true;
	rCharacter.Ship.LastBallCharacter = -1;
	rCharacter.Ship.WindDotShip = 1.0;
	rCharacter.Ship.Speed.z = 0.0;
	rCharacter.Ship.Speed.y = 0.0;
	rCharacter.Ship.Speed.x = 0.0;
	
	
	rCharacter.Ship.BoxSize.x = 1.0;  
	rCharacter.Ship.BoxSize.y = 1.0;
	rCharacter.Ship.BoxSize.z = 2.0;
	
	rCharacter.Ship.Strand = false;
	rCharacter.Ship.Strand.SndID = SOUND_INVALID_ID;
	rCharacter.Ship.Stopped = false;
	rCharacter.Ship.POS.Mode = SHIP_SAIL;
	rCharacter.Ship.SeaAI.Init.AbordageDistance = 30.0;
	
	ref	rCannon = GetCannonByType(sti(rCharacter.Ship.Cannons.Type));
	float range = 550;
	if (CheckAttribute(rCannon, "FireRange")) range = stf(rCannon.FireRange);
	rCharacter.Ship.SeaAI.Init.AttackDistance = range  / (1.4 + frandSmall(2.0)); 
	rCharacter.Ship.SeaAI.Init.AttackDistance.qtyTryChangeCannon = 0; 
	
	rCharacter.Ship.SeaAI.Init.FollowDistance = makefloat(180.0 + rand(120)); 

	rCharacter.Ship.Sounds = "";

	if(sti(rCharacter.Ship.Cannons.Type) == CANNON_TYPE_NONECANNON)
	{
		rCharacter.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
	}

	if (bFromCoast == false) { rCharacter.Ship.Speed.z = 1.0; }

	
	Event("eSwitchPerks", "l", iCharacterIndex);											
	
	
	
	if(CheckAttribute(rCharacter,"Ship.Sink")) {trace("ShipSink rCharacter.id = " + rCharacter.id); DeleteAttribute(rCharacter,"Ship.Sink");}
	
	CreateEntity(&Characters[iCharacterIndex], "Ship");
	
    Event(SHIP_UPDATE_PARAMETERS, "lf", iCharacterIndex, stf(rCharacter.Ship.Speed.z));		
    		
	aref arChar, arShip;
	makearef(arChar, characters[iCharacterIndex]);
	makearef(arShip, RealShips[iShipType]);

	Ship_CreateStaticSounds(rCharacter);

	
	SendMessage(&AISea, "liaa", AI_MESSAGE_ADD_SHIP, &Characters[iCharacterIndex], arChar, arShip);

	float ax = 0.0;
	float az = 0.0;	
 	
	
	
	
     
	if(isOffline) ReloadProgressUpdate();
	
	Ships[iNumShips] = iCharacterIndex;
	iNumShips++;
}

void Ship_RecreateStaticSounds()
{
	for (int i=0; i<iNumShips; i++) { Ship_CreateStaticSounds(&Characters[Ships[i]]); }
}

void Ship_CreateStaticSounds(ref rCharacter)
{
    if (!CheckAttribute(rCharacter, "Ship.Pos.x")) return; 
	if (GetCharacterShipType(rCharacter) == SHIP_NOTUSED) return; 
	
    ref refBaseShip = GetRealShip(GetCharacterShipType(rCharacter));
	
	float fX = stf(rCharacter.Ship.Pos.x);
	float fY = stf(rCharacter.Ship.Pos.y);
	float fZ = stf(rCharacter.Ship.Pos.z);
	rCharacter.Ship.Sounds.WaterID.x = 0.0;
	rCharacter.Ship.Sounds.WaterID.y = 0.0;
	rCharacter.Ship.Sounds.WaterID.z = 0.12;
	rCharacter.Ship.Sounds.WaterID = Play3DSoundComplex("ship_water_" + refBaseShip.Soundtype, fX, fY, fZ, true, false);
	if (sti(rCharacter.Ship.Sounds.WaterID) > 0) { Sound_SetVolume(sti(rCharacter.Ship.Sounds.WaterID), 0.0); }
	rCharacter.Ship.Sounds.WaterSpeed = 30.0;

	
	rCharacter.Ship.Sounds.SailsID.x = 0.0;
	rCharacter.Ship.Sounds.SailsID.y = 0.5;
	rCharacter.Ship.Sounds.SailsID.z = 0.0;
	rCharacter.Ship.Sounds.SailsID = Play3DSoundComplex("sails_up_" + refBaseShip.Soundtype, fX, fY, fZ, true, false);
	if (sti(rCharacter.Ship.Sounds.SailsID) > 0) { Sound_SetVolume(sti(rCharacter.Ship.Sounds.SailsID), 0.0); }
	rCharacter.Ship.Sounds.SailsMove = 0.0;

	
	rCharacter.Ship.Sounds.TurnID.x = 0.0;
	rCharacter.Ship.Sounds.TurnID.y = 0.0;
	rCharacter.Ship.Sounds.TurnID.z = 0.0;
	rCharacter.Ship.Sounds.TurnID = Play3DSoundComplex("ship_turn_" + refBaseShip.Soundtype, fX, fY, fZ, true, false);
	if (sti(rCharacter.Ship.Sounds.TurnID) > 0) { Sound_SetVolume(sti(rCharacter.Ship.Sounds.TurnID), 0.0); }
	rCharacter.Ship.Sounds.TurnSpeed = 0.05;
}

void Ship_PlaySound3DComplex(ref rCharacter, string sSoundID, float fVolume, float fX, float fY, float fZ)
{
	
	float x = stf(rCharacter.Ship.Pos.x);
	float y = stf(rCharacter.Ship.Pos.y);
	float z = stf(rCharacter.Ship.Pos.z);

	float aY = stf(rCharacter.Ship.Ang.y);

    if (!CheckAttribute(rCharacter, "Ship.BoxSize.x")) return; 
     
	float x1 = fX * stf(rCharacter.Ship.BoxSize.x) / 2.0;
	float z1 = fZ * stf(rCharacter.Ship.BoxSize.z) / 2.0;
	RotateAroundY(&x1, &z1, cos(aY), sin(aY));

	int iSoundID = Play3DSound(sSoundID, x + x1, y + fY * stf(rCharacter.Ship.BoxSize.y) / 2.0, z + z1);
	if (iSoundID > 0) { Sound_SetVolume(iSoundID, fVolume); }
}

void Ship_PlaySound3D(ref rCharacter, string sSoundID, float fVolume)
{
	float x = stf(rCharacter.Ship.Pos.x);
	float y = stf(rCharacter.Ship.Pos.y);
	float z = stf(rCharacter.Ship.Pos.z);

	int iSoundID = Play3DSound(sSoundID, x, y, z);
	if (iSoundID > 0) { Sound_SetVolume(iSoundID, fVolume); }
}

void Ship_OnBortReloaded()
{
	aref aCharacter = GetEventData();
	string sBort = GetEventData();

	if (!bSeaLoaded || bAbordageStarted) { return; }  
	
	if (sti(aCharacter.index) != nMainCharacterIndex) { return; } 
	 

	if (!sti(aCharacter.Tmp.BortsReloaded.Event))
	{
		aCharacter.Tmp.BortsReloaded.Event = true;
		PostEvent("Ship_BortReloadEvent", 300, "a", aCharacter);
	}
	if (sBort == "cannonl") { aCharacter.Tmp.BortsReloaded.cannonl = true; }
	if (sBort == "cannonr") { aCharacter.Tmp.BortsReloaded.cannonr = true; }
}

void Ship_BortReloadEvent()
{
	aref aCharacter = GetEventData();
	
	if (sti(aCharacter.Tmp.BortsReloaded.Event))
	{
		bool bLeft = sti(aCharacter.Tmp.BortsReloaded.cannonl) == true;
		bool bRight = sti(aCharacter.Tmp.BortsReloaded.cannonr) == true;

		if (bLeft && bRight)
		{
			
			
		}
		else
		{
			if (bLeft)  { PlaySound("interface\_GunReadyL.wav"); }
			if (bRight) { PlaySound("interface\_GunReadyR.wav"); }
		}
	}

	Ship_ClearBortsReloadedEvent(aCharacter);
}

void Ship_ClearBortsReloadedEvent(aref aCharacter)
{
	aCharacter.Tmp.BortsReloaded.Event = false;
	aCharacter.Tmp.BortsReloaded.cannonl = false; 
	aCharacter.Tmp.BortsReloaded.cannonr = false; 
}

void Ship_ChangeChargeEvent() 
{
	string	sBallName;
	
	ref rCharacter = GetCharacter(GetEventData());

	SendMessage(&AISea, "la", AI_MESSAGE_CANNON_RELOAD, rCharacter);
	sBallName = GetEventData();
	rCharacter.Ship.Cannons.Charge = sBallName;
	Cannon_RecalculateParameters(sti(rCharacter.index));

	

	Ship_ClearBortsReloadedEvent(rCharacter);
}

void Ship_ChangeCharge(ref rCharacter, int iNewChargeType)
{
	SendMessage(&AISea, "la", AI_MESSAGE_CANNON_RELOAD, rCharacter); 

	ref rGood = GetGoodByType(iNewChargeType);
	rCharacter.Ship.Cannons.Charge = rGood.name;
	rCharacter.Ship.Cannons.Charge.Type = iNewChargeType;

	Cannon_RecalculateParameters(sti(rCharacter.index));
	rCharacter.BOAL_ReadyCharge = "1"; 
	
	

	Ship_ClearBortsReloadedEvent(rCharacter);
}

void Ship_OnCreate()
{
	ref rCharacter = GetCharacter(GetEventData());
	
	rCharacter.Ship.Speed.z = 0.0;
	rCharacter.Ship.Speed.y = 0.0;
	rCharacter.Ship.Speed.x = 0.0;
}

void Ship_SetSurrendered(ref rCharacter)
{
	if (LAi_IsDead(rCharacter) || sti(rCharacter.ship.type) == SHIP_NOTUSED) return; 
	if (CheckAttribute(rCharacter,"surrendered")) return;
	
	ref rBaseShip = GetRealShip(sti(rCharacter.Ship.Type));
	rCharacter.surrendered = true;	
	Ship_FlagRefresh(rCharacter); 
	
	string sSurrenderString;
	string sSurrenderShipType = XI_ConvertString(rBaseShip.BaseName);
	sSurrenderString = sSurrenderShipType + " '" + rCharacter.Ship.Name + "' " +GetShipSexWord(rBaseShip.BaseName, "raised", "raised") + " white flag";
	Log_SetStringToLog(sSurrenderString);
	
	Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
	
	SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_FRIEND);
	rCharacter.AlwaysFriend = true; 
	UpdateRelations();
	RefreshBattleInterface();
	DoQuestCheckDelay("NationUpdate", 1.5);
}

bool Ship_CheckSurrendered(ref echr)
{
	bool bOk = true;

	if (LAi_IsDead(echr) || sti(echr.ship.type) == SHIP_NOTUSED) return false;
	if (sti(echr.index) == nMainCharacterIndex) return false;
	if (IsCompanion(echr)) return false;	
	if (GetNationRelation2MainCharacter(sti(echr.nation)) != RELATION_ENEMY) return false;
	if (CheckAttribute(echr,"situation")) return false;
	
	if(CheckAttribute(echr,"DontSurrender")) return false;
	
	if (sti(echr.Nation) == PIRATE || CheckAttribute(echr, "DontRansackCaptain")) return false; 
	
	ref mchr = GetMainCharacter();
	
	if (sti(echr.rank) > (40 - MOD_SKILL_ENEMY_RATE)) bOk = false; 	
	if (sti(mchr.rank) < (sti(echr.rank) - MOD_SKILL_ENEMY_RATE / 2))  bOk = false;
	
	int eclass = GetCharacterShipClass(echr);
	int mclass = GetCharacterShipClass(mchr);
	if (eclass == 1) bOk = false;
	
	if(!bOk) 
	{
		echr.DontSurrender = true;
		return false;
	}	
	
	float fCrewRate = 0.5;  
	if (CheckAttribute(echr, "Ship.Mode"))
	{
		switch(echr.Ship.Mode)
		{
			case "Trade":
				fCrewRate = 0.6;
			break;
			case "War" 	:
				fCrewRate = 0.2;
			break;
		}
	}
	float mcrew = stf(GetWeaponCrew(mchr, GetCrewQuantity(mchr))); 
	float ecrew = stf(GetCrewQuantity(echr));
	
	float fRep    = abs(REPUTATION_NEUTRAL - sti(mchr.reputation.nobility)) / 50.0; 
	float emorale = stf(echr.ship.crew.morale) / MORALE_MAX; 
	float mmorale = stf(mchr.ship.crew.morale) / MORALE_MAX; 
	float mskill  = (GetSummonSkillFromNameToOld(mchr, "Leadership") + GetSummonSkillFromNameToOld(mchr, "Grappling")) / 20.0;  
	float eskill  = (GetCharacterSkillToOld(echr, "Leadership") + GetCharacterSkillToOld(echr, "Defence")) / 20.0;    
	
	mcrew = mcrew * (mcrew * GetCrewExp(mchr, "Soldiers")) / (GetOptCrewQuantity(mchr) * GetCrewExpRate()); 
    ecrew = ecrew * (ecrew * GetCrewExp(echr, "Soldiers")) / (GetOptCrewQuantity(echr) * GetCrewExpRate());  
	
    mcrew = mcrew *(0.5 + mmorale);
    ecrew = ecrew *(0.5 + emorale); 
    
    mcrew = mcrew * (0.2 + mskill)*(0.05 + fRep)*fCrewRate;
    ecrew = ecrew * (0.2 + eskill);

	int mShip = GetCompanionQuantity(mchr);
    int eShip;
    string sGroupID = Ship_GetGroupID(echr);
    if (sGroupID != "") eShip = Group_GetLiveCharactersNum(sGroupID);
    else				eShip = 1;

	mcrew = mcrew * (1.0 + mclass / 20.0); 
    ecrew = ecrew * (1.0 + eclass / 20.0);  
    
    mcrew = mcrew * (1.0 + (mShip-1) / 5.0);
    ecrew = ecrew * (1.0 + (eShip-1) / 5.0);

    if (mcrew > ecrew)
	{
		
		if (GetSailPercent(echr) < 25.0 || GetHullPercent(echr) < 25.0) return true; 
	}
	return false; 
}

void Ship_CheckSituation()
{
	ref		rShip;
	aref	rSituation;
	
	aref	rCharacter = GetEventData();
	aref	rShipObject = GetEventData();
	
	if (sti(rCharacter.index) == nMainCharacterIndex) { return; }
	if (LAi_IsDead(rCharacter) || sti(rCharacter.ship.type) == SHIP_NOTUSED) { return; }  
	
	
	
	if (!CheckAttribute(rCharacter, "SeaAI.Task"))
	{
		trace("Character " + rCharacter.id  + " without task");
		rCharacter.SeaAI.Task = AITASK_NONE;
	}

	rShip = GetRealShip(sti(rCharacter.Ship.Type));
	makearef(rSituation, rCharacter.SeaAI.Update.Situation);

	float	fMinEnemyDistance = stf(rSituation.MinEnemyDistance);
	float	fDistance;
	
	if (sti(rCharacter.Ship.LastBallCharacter) != -1 && LAi_IsDead(GetCharacter(sti(rCharacter.Ship.LastBallCharacter))))
	{
        rCharacter.Ship.LastBallCharacter = -1;
	}
	if (CheckAttribute(rCharacter, "SeaAI.Task.Target"))
	{
		if (rCharacter.SeaAI.Task.Target != "" && LAi_IsDead(GetCharacter(sti(rCharacter.SeaAI.Task.Target))))
	    {
	        rCharacter.SeaAI.Task.Target = "";
	    }
	     
    }
	
	
    
    
    if (Ship_AutoAbordage(rCharacter, fMinEnemyDistance)) { return; }
    
    
	
	
	if(!CheckAttribute(rCharacter,"surrendered") && Ship_CheckSurrendered(rCharacter)) Ship_SetSurrendered(rCharacter);
	
	
	
	if(CheckAttribute(rCharacter, "CanDropSails") && !sti(rCharacter.CanDropSails)) 
	{
		Ship_SetSailState(sti(rCharacter.index), 1.0);
	}
		
	
	int iShipCannonsNum  = GetCannonsNum(rCharacter);
	int iCurrentBallType = sti(rCharacter.Ship.Cannons.Charge.Type);
	bool bBalls, bKnippels, bBombs, bGrapes;
	bBalls = true; bKnippels = true; bBombs = true; bGrapes = true;
	
	if (CheckAttribute(rCharacter, "ShipCannonChargeType")) 
	{
	    if (GetCargoGoods(rCharacter, sti(rCharacter.ShipCannonChargeType))    < iShipCannonsNum)
	    {
	        DeleteAttribute(rCharacter, "ShipCannonChargeType"); 
	    }
	}
	else
	{
        if (GetCargoGoods(rCharacter,GOOD_BALLS)    < iShipCannonsNum) { bBalls    = false; }
		if (GetCargoGoods(rCharacter,GOOD_BOMBS)    < iShipCannonsNum) { bBombs    = false; }
		if (GetCargoGoods(rCharacter,GOOD_KNIPPELS) < iShipCannonsNum) { bKnippels = false; }
		if (GetCargoGoods(rCharacter,GOOD_GRAPES)   < iShipCannonsNum) { bGrapes   = false; }

		int iNewBallType = iCurrentBallType;
		if( !CheckAttribute(rCharacter,"BOAL_ReadyCharge"))
	    {
	        rCharacter.BOAL_ReadyCharge = "1";
	    }
	    if (rCharacter.BOAL_ReadyCharge == "0")
	    {
	        iNewBallType = Ship_FindOtherBallType(rCharacter, fMinEnemyDistance, bBalls, bBombs, bGrapes, bKnippels);
	        rCharacter.BOAL_ReadyCharge = "1";
	    	if (iNewBallType >= 0 && iNewBallType != iCurrentBallType)
		    {
		   	   Ship_ChangeCharge(rCharacter, iNewBallType);
		    }
	    }
	    else
	    {
	        ref rCannon = GetCannonByType(sti(rCharacter.Ship.Cannons.Type));
		    float range = stf(rCannon.FireRange);
		    if ((fMinEnemyDistance > (range*0.9)) && bBalls) 
	        {
	           iNewBallType = GOOD_BALLS;
	           if (iNewBallType != iCurrentBallType)
	           {
	               Ship_ChangeCharge(rCharacter, iNewBallType);
	           }
	        }
	    }
    }
    
    
	 
	bool bIsCompanion = IsCompanion(rCharacter);
	
	
	if (CheckAttribute(rCharacter, "SeaAI.Task") && CheckAttribute(rCharacter, "SeaAI.Task.Target"))
	{
		switch (sti(rCharacter.SeaAI.Task))
		{
			
			case AITASK_BRANDER:
				ref rCharacter2Brander = GetCharacter(sti(rCharacter.SeaAI.Task.Target));
				ref rBaseShip = GetRealShip(sti(rCharacter.Ship.Type));
				float fBranderDistance = 45.0 + (7.0 - stf(rBaseShip.Class)) * 15.0; 
				fDistance = Ship_GetDistance2D(rCharacter, rCharacter2Brander); 
				if (fBranderDistance > fDistance)
				{
					
					Ship_SetExplosion(rCharacter, rShipObject); 
					Log_Info("" + XI_ConvertString(rBaseShip.BaseName) + " '" + rCharacter.Ship.Name + "' " + GetShipSexWord(rBaseShip.BaseName, "exploded", "exploded") + " a powder-magazine.");
					return;
				}
				
			break;
			case AITASK_ATTACK:
				
				
				
				
				if (CheckAttribute(rCharacter, "Sea_AI.cannon.charge.lasttime") && sti(rCharacter.Sea_AI.cannon.charge.lasttime) == 1) 
				{
					if (sti(rCharacter.Ship.SeaAI.Init.AttackDistance.qtyTryChangeCannon) == 2 || sti(rCharacter.Ship.SeaAI.Init.AttackDistance.qtyTryChangeCannon) == 5)
					{
						rCharacter.Ship.SeaAI.Init.AttackDistance = 50; 
						Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.SeaAI.Task.Target));
					}
					else
					{
						float fAttackDist = Ship_GetDistance2D(rCharacter, &characters[sti(rCharacter.SeaAI.Task.Target)]);
						if (fAttackDist < 500)
						{
							rCharacter.Ship.SeaAI.Init.AttackDistance = fAttackDist;
							Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.SeaAI.Task.Target));
						}	
					}
				}
			break;
            
		}
	}
	
    if (!bIsCompanion) 
    {
        string sGroupID = Ship_GetGroupID(rCharacter);
        
		if (CheckAttribute(rCharacter, "SeaAI.Task.Target"))
		{
	        if (iNewBallType < 0 || iShipCannonsNum < (sti(rShip.CannonsQuantity) / 10))
			{
				
				Ship_SetTaskRunaway(SECONDARY_TASK,sti(rCharacter.index), sti(rCharacter.SeaAI.Task.Target));
				return;
			}
		}
		if (GetNationRelation2MainCharacter(sti(rCharacter.nation)) == RELATION_ENEMY) 
	    {
            if (CheckAttribute(rCharacter, "AlwaysFriend"))
	        {
	            SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_FRIEND);
	        }
	        else
	        {
				
				if (CheckAttribute(rCharacter, "WatchFort") && bIsFortAtIsland && GetRelation(sti(rCharacter.index), iFortCommander) == RELATION_ENEMY && !CheckAttribute(rCharacter, "ShipTaskLock"))
				{
					if (sti(rCharacter.Tmp.fWatchFort) >= sti(rCharacter.Tmp.fWatchFort.Qty))
					{					
						rCharacter.Tmp.fWatchFort = 0; 
						
						if (GetDistance2D(stf(rCharacter.Ship.Pos.x), stf(rCharacter.Ship.Pos.z), fFort_x, fFort_z) < 1000)
						{
							Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), iFortCommander);
							rCharacter.Tmp.fWatchFort.Qty = 200; 
							
						}
					}
					else
					{
						rCharacter.Tmp.fWatchFort = sti(rCharacter.Tmp.fWatchFort) + 1;
					}
				}
				
				if (!CheckAttribute(rCharacter, "SinkTenPercent")) 
	            {
					int   SailsPercent    = sti(rCharacter.Ship.SP);
			        float HPPercent       = GetHullPercent(rCharacter);
			        int   CrewQuantity    = sti(rCharacter.Ship.Crew.Quantity);
			        int   MinCrewQuantity = GetMinCrewQuantity(rCharacter);
					int   iCharactersNum1, iCharactersNum2;

					if (GetRelation(sti(rCharacter.index), GetMainCharacterIndex()) != RELATION_ENEMY)
					{
						SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
				        Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
				        UpdateRelations();
				        DoQuestCheckDelay("NationUpdate", 0.9);
			        }
                    if (sti(rCharacter.Ship.LastBallCharacter) != -1 && !CheckAttribute(rCharacter, "Ship_SetTaskAbordage") && !CheckAttribute(rCharacter, "ShipTaskLock")) 
                    {
						if (!CheckAttribute(rCharacter, "SeaAI.Task") || sti(rCharacter.SeaAI.Task) == AITASK_NONE)
				        {
							
							if (CheckAttribute(rCharacter, "AnalizeShips"))
							{									
								
								if (stf(rCharacter.ship.hp) < (stf(characters[sti(rCharacter.Ship.LastBallCharacter)].ship.hp) / 2))
								{
									Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
								}
								else
								{
									Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
								}							
							}
							else
							{	
								Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
							}									        
						}
				        else
				        {
							if ((SailsPercent > 50) && (HPPercent > 30) && sti(rCharacter.SeaAI.Task) != AITASK_RUNAWAY) 
					        {
								
								if (CheckAttribute(rCharacter, "AnalizeShips"))
								{									
									
										iCharactersNum1 =  Group_GetLiveCharactersNum(rCharacter.SeaAI.Group.Name);
										iCharactersNum2 =  Group_GetLiveCharactersNum(characters[sti(rCharacter.Ship.LastBallCharacter)].SeaAI.Group.Name);	
									
									if(stf(rCharacter.ship.hp) < (stf(characters[sti(rCharacter.Ship.LastBallCharacter)].ship.hp) / 2))
									{
										if ((iCharactersNum1 / iCharactersNum2) >= 2.2 && iCharactersNum2 > 0) 
										{
											Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
										}
										else
										{
											Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
										}
									}
									else
									{	
										if((iCharactersNum2 / iCharactersNum1) >= 2.0 && sti(RealShips[sti(rCharacter.ship.type)].Class) > sti(RealShips[sti(characters[sti(rCharacter.Ship.LastBallCharacter)].ship.type)].Class))
										{
											Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
										}
										else
										{
											Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
										}
									}
								}
								else
								{	
									Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
								}
					        }  
					        else
					        {
						        
						        if (HPPercent < 15)
						        {
						            if (rand(20) == 1)
						            {
						                Ship_SetTaskBrander(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
						            }
						        }
						        else
						        {
						        	if ((HPPercent < 30) || (CrewQuantity <= (2*MinCrewQuantity)))
							        {
							            Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
							        }
									else
									{	
										if (CheckAttribute(rCharacter, "AnalizeShips") && stf(rCharacter.ship.hp) > (stf(characters[sti(rCharacter.Ship.LastBallCharacter)].ship.hp) / 2))
										{
											
											if (sti(rCharacter.Tmp.fWatchFort.Qty) == 200)
											{
												
												if (sti(rCharacter.Tmp.fWatchFort) >= 199)
												{
													if (sti(rCharacter.Ship.LastBallCharacter) == iFortCommander)
													{	
														Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
													}
													else
													{
														Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
													}
												}
											}
											else
											{	
												if (sti(rCharacter.Ship.LastBallCharacter) == iFortCommander)
												{	
													Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
												}
												else
												{
													iCharactersNum1 =  Group_GetLiveCharactersNum(rCharacter.SeaAI.Group.Name);
													iCharactersNum2 =  Group_GetLiveCharactersNum(characters[sti(rCharacter.Ship.LastBallCharacter)].SeaAI.Group.Name);	
													if ((iCharactersNum2 / iCharactersNum1) >= 2.0 && sti(RealShips[sti(rCharacter.ship.type)].Class) > sti(RealShips[sti(characters[sti(rCharacter.Ship.LastBallCharacter)].ship.type)].Class))
													{
														Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
													}
													else
													{
														Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
													}
												}
											}		
										}
									}
						        }
					        }
				        }
			        }
			        else
			        {   
						
                        if (!CheckAttribute(rCharacter, "ShipTaskLock"))
						{
				            if (!CheckAttribute(rCharacter, "SeaAI.Task.Target") || sti(rCharacter.SeaAI.Task.Target) == -1)
					        {
								if (CheckAttribute(rCharacter, "SeaAI.Task") && sti(rCharacter.SeaAI.Task) != AITASK_RUNAWAY)
								{
									
									if (CheckAttribute(rCharacter, "AnalizeShips") && stf(rCharacter.ship.hp) < (stf(pchar.ship.hp) / 2))
							        {									
										iCharactersNum1 =  Group_GetLiveCharactersNum(rCharacter.SeaAI.Group.Name);
										iCharactersNum2 =  Group_GetLiveCharactersNum(characters[GetMainCharacterIndex()].SeaAI.Group.Name);	
										if ((iCharactersNum1 / iCharactersNum2) >= 2.2) 
										{
											Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex()));
										}
										else
										{
											Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
										}		
									}
									else
									{	
										Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
										{
											Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
										}
										else
										{
											Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
										}
									}
								}
								else
								{	
						        	if (CheckAttribute(rCharacter, "AnalizeShips") && (HPPercent > 60) && (SailsPercent > 70) && stf(rCharacter.ship.hp) > (stf(pchar.ship.hp) / 2))
							        {
							            Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
							        }
								}
					        }
				        }
			        }
		        }
		        else
		        {
					
					if (findsubstr(rCharacter.id, "Caleuche" , 0) != -1)
					{	
						if (rCharacter.id == "Caleuche_seacap") 
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 500)
							{
								Ship_SetTaskAbordage(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
							}
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 150)
							{
								Caleuche_GhostshipBoarding(); 
							}
						}
						else 
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 900)
							{
								Ship_SetTaskAbordage(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
								pchar.quest.Caleuche_map_clear.win_condition.l1 = "MapEnter";
								pchar.quest.Caleuche_map_clear.function = "Caleuche_ClearFromMap";
								rCharacter.lifeday = 0;
								Map_ReleaseQuestEncounter("Map_Caleuche");
							}
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 150)
							{
								Caleuche_MapGhostshipBoarding(); 
							}
						}
					}
					else
					{
						if (CheckAttribute(rCharacter, "PearlTartane") && sti(rCharacter.PearlTartane))
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 16)
							{
								PlaySound("interface\important_item.wav");
								int SmallPearlQty,BigPearlQty;
								if (CheckAttribute(rCharacter, "JewelryGulf")) 
								{
									SmallPearlQty = rand(25) + 20;
									BigPearlQty = rand(20) + 15;
									TakeNItems(pchar, "jewelry8", SmallPearlQty);
									TakeNItems(pchar, "jewelry7", BigPearlQty);
									Log_SetStringToLog("Fishers of " + rCharacter.ship.name + " gave you " + SmallPearlQty + " of amber and " + BigPearlQty + " of blue amber.");
									pchar.questTemp.Mtraxx.JewQty = sti(pchar.questTemp.Mtraxx.JewQty)+BigPearlQty;
								}
								else
								{
									SmallPearlQty = rand(250) + 100;
									BigPearlQty = rand(150) + 50;
									TakeNItems(pchar, "jewelry53", SmallPearlQty);
									TakeNItems(pchar, "jewelry52", BigPearlQty);
									Log_SetStringToLog("����� ������� �� ������� " + rCharacter.ship.name + " ������ ��� " + SmallPearlQty + " ����� � " + BigPearlQty + " ������� ��������.");
								}
								rCharacter.PearlTartane = false; 
								pchar.questTemp.GrabbingTartane = "success"; 
							}
						}
						else
						{
							if (!CheckAttribute(rCharacter, "PearlTartane"))
							{
								Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
							}
							
							if (rCharacter.id == "Losada_Seacap_1")
							{
								if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) > 3000 && CheckAttribute(pchar, "questTemp.Mtraxx.LosadaEscape")) Mtraxx_IgnasioOpenMap();		
							}
						}
					}
		        }
	        }
	    }
	    else
	    {
	        
	        
	        if (CheckAttribute(rCharacter, "AlwaysEnemy"))
	        {
	            SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
	            Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
	        }
	        else
	        {
                if (CheckAttribute(rCharacter, "AlwaysFriend"))
		        {
		            SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_FRIEND);
		        }
		        else
		        {
					
			        if (sti(rCharacter.nation) != PIRATE || bBettaTestMode)
			        {
	                    SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), GetNationRelation2MainCharacter(sti(rCharacter.nation)));
						
						if (!CheckAttribute(rCharacter, "CheckFlagYet"))
						{
	                        if (!CheckAttribute(rCharacter, "CheckFlagDate") || GetNpcQuestPastDayParam(rCharacter, "CheckFlagDate") > 1)
	                        {
								if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER)
							    {
							        rCharacter.CheckFlagYet = true; 
							        Ship_CheckFlagEnemy(rCharacter);
							        SaveCurrentNpcQuestDateParam(rCharacter, "CheckFlagDate");
							    }
						    }
						}
						
						
						
						if (rCharacter.id == "ContraCureerCap")
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 150)
							{
								SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
								SetCharacterRelationBoth(sti(GetCharacterIndex("ContraContraCap")), GetMainCharacterIndex(), RELATION_ENEMY);
								Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
								Group_LockTask(sGroupID);
								rCharacter.nation = PIRATE;
								ref rChar = characterFromId("ContraContraCap");	
								rChar.nation = PIRATE;
								Ship_FlagRefresh(rCharacter);
								Ship_FlagRefresh(rChar);
								UpdateRelations();
								RefreshBattleInterface();
							}
						}
						
						if (rCharacter.id == "Cap_Marlin")
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 200)
							{
								SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
								Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
								Group_LockTask(sGroupID);
								UpdateRelations();
								RefreshBattleInterface();
							}
						}
						
						if (rCharacter.id == "Saga_vampire")
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 200)
							{
								Saga_CheckVensanEnemyes(); 
							}
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 25)
							{
								if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Bomb")) Saga_HitSeaBomb();
							}
						}
						
						if (rCharacter.id == "Jackman")
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 200)
							{
								Saga_CheckJackmanFrigate(); 
							}
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 25)
							{
								if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Fugas")) Saga_HitSeaFugas();
							}
						}
						
						if (rCharacter.id == "Molligan")
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 500 && CheckAttribute(pchar, "questTemp.Saga.Molligan.enemy")) Saga_MolliganAttack(); 
						}
						
						if (rCharacter.id == "Baker_Cap" && CheckAttribute(pchar, "questTemp.Saga.Shadows.Baker"))
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 20) Saga_BakerToCabin(); 
						}
						
						if (rCharacter.id == "GOT_camicadze")
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 200) GuardOT_CamicadzeBoom(); 
						}
						
						if (rCharacter.id == "FMQM_Tartane_Cap")
						{
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 500 && !CheckAttribute(rCharacter, "quest.seaattack")) FMQM_TartanaAlarm(); 
						}
			        }
			        else
			        {
			            SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
			        }
		        }
	        }
	        

	        if (GetRelation(GetMainCharacterIndex(), sti(rCharacter.index)) == RELATION_ENEMY)
	        {
	            Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
	            UpdateRelations(); 
	        }
	        
	    }
	    
    }
     
    
}


void Ship_CheckFlagEnemy(ref rCharacter)
{
	ref     mChar = GetMainCharacter();
	int     iCompan, iClass;
	float   fSneak;
	float   fPerkInfl = 1.0;
	int     i, cn;
	ref     chref;
	bool    bViewFlag = false;
	int     iNationToChange = sti(mChar.nation);  

	if (sti(rCharacter.nation) == PIRATE) return;
    iCompan = GetCompanionQuantity(mChar);
    iClass  = 6;
	
	for (i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(GetMainCharacter(), i);
		if (cn>=0)
		{
			chref = GetCharacter(cn);
            if (GetCharacterShipClass(chref) < iClass) iClass = GetCharacterShipClass(chref);
		}
	}
    if (GetNationRelation(GetBaseHeroNation(), sti(rCharacter.nation)) == RELATION_ENEMY && GetDaysContinueNationLicence(HOLLAND) == -1) 
    {
        
		iNationToChange = GetBaseHeroNation();
        bViewFlag       = true;
    }
    if (!bViewFlag)
    {
        if (ChangeCharacterHunterScore(mChar, NationShortName(sti(rCharacter.nation)) + "hunter", 0) > (8 + rand( (iClass-1)*(6-iCompan) ) ))
        {
            bViewFlag       = true;
            iNationToChange = PIRATE;
        }
    }
    if (bViewFlag)
    {  
		if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && pchar.location == "cuba1") return; 
		if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && pchar.location == "Trinidad") return; 

		fSneak  = stf(mChar.TmpSkill.Sneak); 
		int rep = sti(abs(REPUTATION_NEUTRAL - sti(mChar.reputation.nobility)) * 0.75);
		if(CheckCharacterPerk(mChar, "HT2")) fPerkInfl = 2.0;
		if ((rand(100) + rand(20) + rand(rep)) > (fPerkInfl*fSneak * 10 * iClass * (6-iCompan) * isEquippedArtefactUse(mChar, "indian_11", 1.0, 1.15)))
		{
			 
			Log_Info("You failed to be taken for a friend - "+ NationNamePeople(sti(rCharacter.nation)) + " recognized you as an enemy.");
			SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
			DoQuestCheckDelay(NationShortName(iNationToChange) + "_flag_rise", 0.1); 
			if (sti(pchar.questTemp.stels.sea) != GetDataDay())
			{
				AddCharacterExpToSkill(mChar, SKILL_SNEAK, 50);
				pchar.questTemp.stels.sea = GetDataDay();
			}
		}
		else
		{ 
			if (sti(pchar.questTemp.stels.sea) != GetDataDay())
			{
				AddCharacterExpToSkill(mChar, SKILL_SNEAK, (iCompan * 200 / iClass));
				ChangeCrewExp(mChar, "Sailors", 0.5);
				pchar.questTemp.stels.sea = GetDataDay();
			}
		}
	}
	if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MIRAGE && sti(rCharacter.nation) == ENGLAND && CheckAttribute(pchar, "questTemp.HWIC.Holl"))
	{
		Log_Info("Englishmen have recognized 'Mirage', they believe that we are their enemies!");
		SetNationRelation2MainCharacter(ENGLAND, RELATION_ENEMY);
		LAi_group_ClearAllTargets();
		DoQuestCheckDelay("NationUpdate", 3.0);
		UpdateRelations();
	    RefreshBattleInterface();
	}
	if (LineShips_CheckAndIdentify(sti(rCharacter.nation))) 
	{
		Log_Info("Alarm, "+ NationNamePeople(sti(rCharacter.nation)) + " recognized their ship of the line which you captured from them!");
		SetNationRelation2MainCharacter(sti(rCharacter.nation), RELATION_ENEMY);
		LAi_group_ClearAllTargets();
		DoQuestCheckDelay("NationUpdate", 3.0);
		UpdateRelations();
	    RefreshBattleInterface();
		ChangeCharacterNationReputation(pchar, sti(rCharacter.nation), -3);
	}
}

void Ship_ActivateFirePlace()
{
	aref	arShipObject = GetEventData();
	aref	arCharacter = GetEventData();
	int		iFirePlaceIndex = GetEventData();
	string	sSoundName = GetEventData();
	float	fFireTime = GetEventData();
	int		iBallCharacterIndex = GetEventData();

	if (!bAbordageStarted) 
	{
		if(rand(5) < 4) 	SendMessage(arShipObject, "llsssfl", MSG_SHIP_ACTIVATE_FIRE_PLACE, iFirePlaceIndex, "ship_smoke", "ship_fire", sSoundName, fFireTime, iBallCharacterIndex);
		else				SendMessage(arShipObject, "llsssfl", MSG_SHIP_ACTIVATE_FIRE_PLACE, iFirePlaceIndex, "sea_smoke", "ship_fire", sSoundName, fFireTime, iBallCharacterIndex);
	}
}

void Ship_BranderDetonate()
{
	ref		rCharacter = GetCharacter(GetEventData());

	ref		rBranderBaseShip = GetRealShip(sti(rCharacter.Ship.Type));
 	float	fBranderDistance = 1.9 * (45.0 + (6.0 - stf(rBranderBaseShip.Class)) * 15.0); 
	float   fMaxDamage = 1000.0 + MakeFloat(GetCargoGoods(rCharacter, GOOD_POWDER)) * 4;

	aref	arShipObjects[64];
	int		iBranderNumShips = 1;
	
	if(CheckAttribute(rCharacter,"Situation") && rCharacter.situation == "Explosion" ) 
	{
		fMaxDamage = 1000.0 + MakeFloat(GetCargoGoods(rCharacter, GOOD_POWDER)) * 3;
		if(GetCargoGoods(rCharacter, GOOD_POWDER) < 300) { fMaxDamage += 400.0; }	
		ref mc = GetMainCharacter();
		int iDiffClass = sti(RealShips[sti(mc.Ship.Type)].Class) - sti(RealShips[sti(rCharacter.Ship.Type)].Class);
		if(iDiffClass > 0) fMaxDamage += iDiffClass * 500.0;
		fMaxDamage = fMaxDamage / 20.0 * MOD_SKILL_ENEMY_RATE;		
	}	
	if (!FindClass(&arShipObjects[0], "ship")) { return; }
	while (FindClassNext(&arShipObjects[iBranderNumShips])) { iBranderNumShips++; }
	
	
	for (int i=0; i<iBranderNumShips; i++)
	{
		int iCharacterIndex = -1;
		SendMessage(arShipObjects[i], "le", MSG_SHIP_GET_CHARACTER_INDEX, &iCharacterIndex);
		if (iCharacterIndex == sti(rCharacter.index)) { continue; }
		ref rOtherCharacter = GetCharacter(iCharacterIndex);
		ref	rOtherBaseShip = GetRealShip(sti(rOtherCharacter.Ship.Type));
		float fDistance = Ship_GetDistance2D(rCharacter, rOtherCharacter);
		if (fDistance > fBranderDistance) { continue; }
		float fDamageMultiply = Bring2Range(1.0, 0.0, 10.0, fBranderDistance, fDistance);
		Ship_ApplyHullHitpoints(rOtherCharacter, fMaxDamage * fDamageMultiply, KILL_BY_SPY, sti(rCharacter.index));
		
		
		

		
		float x = stf(rOtherCharacter.Ship.Pos.x) - stf(rCharacter.Ship.Pos.x);
		float z = stf(rOtherCharacter.Ship.Pos.z) - stf(rCharacter.Ship.Pos.z);
		float fLen = stf(rOtherBaseShip.Class) * fDamageMultiply * (1.0 / sqrt(x * x + z * z));
		SendMessage(&arShipObjects[i], "llffffff", MSG_SHIP_ADD_MOVE_IMPULSE, false, x * fLen, 0.0, z * fLen, 0.0, 0.0, 0.0);
	}
	Ship_Detonate(rCharacter, true, true);
}

float Ship_GetDistance2D(ref rCharacter1, ref rCharacter2)
{
	if (CheckAttribute(rCharacter1, "Ship.Pos.x") && CheckAttribute(rCharacter2, "Ship.Pos.x")) 
	{
		return GetDistance2D(stf(rCharacter1.Ship.Pos.x), stf(rCharacter1.Ship.Pos.z), stf(rCharacter2.Ship.Pos.x), stf(rCharacter2.Ship.Pos.z));
	}   
	else
	{
		return 1000.0;
	}
}

int Ship_FindOtherBallType(ref rCharacter, float fMinEnemyDistance, bool bBalls, bool bBombs, bool bGrapes, bool bKnippels)
{
	ref	rCannon = GetCannonByType(sti(rCharacter.Ship.Cannons.Type));
	float range = stf(rCannon.FireRange);
	if (checkAttribute(rCharacter, "SeaAI.task.target") && rCharacter.SeaAI.task.target != "") 
	{
		int enemy = sti(rCharacter.SeaAI.task.target);
		ref rBaseShip = GetRealShip(GetCharacterShipType(rCharacter));
		
		rCannon = GetCannonByType(sti(characters[enemy].Ship.Cannons.Type));
		float TargetRange = stf(rCannon.FireRange);

		int iType = -1;
		float fRangeModifier = 1.0;
		

		 

		if ( bBalls) 
		{
			iType = GOOD_BALLS;
		}

		if ( (fMinEnemyDistance <= (range * 0.8)) && bKnippels) 
		{
			if (sti(characters[enemy].ship.sp) > 30 && ShipSailState(enemy) >= 0.5)  
			{
				iType = GOOD_KNIPPELS;
			}
			fRangeModifier = 0.8;
		}

		if ( (fMinEnemyDistance <= (range * 0.5)) && bBombs)
		{
			iType = GOOD_BOMBS;
			fRangeModifier = 0.6;
		}

		if ((fMinEnemyDistance <= (range * 0.2)) && bGrapes)
		{
			if (sti(characters[enemy].ship.crew.quantity) > sti(rBaseShip.MinCrew))
			{
				iType = GOOD_GRAPES;  
			}
			fRangeModifier = 0.3;
		}

		rCharacter.Ship.SeaAI.Init.AttackDistance = range * fRangeModifier / (1.4 + frandSmall(3.0));

		 

		return iType;
	}
	
	if (bBalls) return GOOD_BALLS;
	if (bBombs) return GOOD_BOMBS;
	if (bKnippels) return GOOD_KNIPPELS;
	if (bGrapes) return GOOD_GRAPES;
	
	return -1;
}


void Ship_NotEnoughBalls()
{
	bNotEnoughBalls = GetEventData();
	
	if (!bNotEnoughBalls)
	{
	    if (GetCargoGoods(pchar, GOOD_POWDER) < 1)
	    {
	        bNotEnoughBalls = true;
	    }
	}
	

}

int Ship_GetCurrentBallsNum()
{
	aref aCharacter = GetEventData();
	return GetCargoGoods(aCharacter,sti(aCharacter.Ship.Cannons.Charge.Type));
}

void Ship_SailDamage()
{
	float x, y, z;
	int iCharacterIndex 	= GetEventData();
	int	iBallCharacterIndex = GetEventData();
	x = GetEventData();
	y = GetEventData();
	z = GetEventData();

	ref	rBallCharacter 	= GetCharacter(iBallCharacterIndex);	
	ref	rOurCharacter 	= GetCharacter(iCharacterIndex);   		
	

	
	rOurCharacter.Ship.LastBallCharacter = iBallCharacterIndex;
	
	string sSound;
	int	iBallType = sti(AIBalls.CurrentBallType);
	switch (iBallType)
	{
		case GOOD_BALLS:	sSound = "ball2sail";		break;
		case GOOD_GRAPES:	sSound = "grapes2sail";		break;
		case GOOD_KNIPPELS:	sSound = "knippel2sail";	break;
		case GOOD_BOMBS:	sSound = "ball2sail"; 		break;
	}

	Play3DSound(sSound, x, y, z);
	if (rand(100) < 15) { Play3DSound("fly_ball_misc", x, y, z); }
	
	bool    isOurCompanion   = IsCompanion(rOurCharacter);
	
	if (sti(rOurCharacter.Ship.LastBallCharacter) == GetMainCharacterIndex() 
	        && GetNationRelation2MainCharacter(sti(rOurCharacter.nation)) != RELATION_ENEMY)
    {	
        if (!IsCompanion(rOurCharacter) && !CheckAttribute(rOurCharacter, "Coastal_Captain")) 
        {
            Ship_NationAgressive(rOurCharacter, rOurCharacter);
            DoQuestCheckDelay("NationUpdate", 0.7);
        }	
    }	
}

void Ship_Ship2IslandCollision()
{
	float	fPower, fSlide, x, y, z;
	int		iOurCharacterIndex, iEnemyCharacterIndex, iTouchPoint;

	iOurCharacterIndex = GetEventData();
	iEnemyCharacterIndex = GetEventData();
	fPower = abs(GetEventData());
	fSlide = abs(GetEventData());
	iTouchPoint = GetEventData();
	x = GetEventData();
	y = GetEventData();
	z = GetEventData();

	ref rOurCharacter = GetCharacter(iOurCharacterIndex);

    if (!CheckAttribute(rOurCharacter, "AlwaysSandbankManeuver"))  
    {
		float fHP = (1.0 - fSlide) * fPower * 3.0;
		Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_ISLAND, -1);

		if (fPower > 1.0) { Play3DSound("coll_ship2rock", x, y, z); }
	}
}

float Ship_GetAttackHP(int iCharacterIndex, float fDistance)
{
	float fAttackHP = 0.0;
	if (bSeaActive)
	{
		SendMessage(&AISea, "lafe", AI_MESSAGE_SHIP_GET_ATTACK_HP, &Characters[iCharacterIndex], fDistance, &fAttackHP);
	}
	return fAttackHP;
}

float Ship_GetHP(ref rCharacter) 
{ 
	return stf(rCharacter.Ship.HP); 
}

void Ship_Ship2ShipCollision()
{
	int		iOurCharacterIndex, iEnemyCharacterIndex, iTouchPoint;
	float	fPower, fSlide, x, y, z;
	
	iOurCharacterIndex = GetEventData();   
	iEnemyCharacterIndex = GetEventData();  
	fPower = abs(GetEventData());
	fSlide = abs(GetEventData());
	iTouchPoint = GetEventData();
	x = GetEventData();
	y = GetEventData();
	z = GetEventData();
	
	ref rOurCharacter = GetCharacter(iOurCharacterIndex);

	float fHP = (1.0 - fSlide) * fPower * 10.0;
	
	Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_TOUCH, iEnemyCharacterIndex);
	
	if (iEnemyCharacterIndex == GetMainCharacterIndex() && GetHullPercent(rOurCharacter) <= 14  && !LAi_IsDead(rOurCharacter))
	{
		if (!IsCompanion(rOurCharacter) && GetRelation(sti(rOurCharacter.index), GetMainCharacterIndex()) != RELATION_ENEMY)
		{
			Ship_NationAgressive(rOurCharacter, rOurCharacter);
	    	DoQuestCheckDelay("NationUpdate", 0.9);
    	}
	}
	

	if (fPower>1.0) { Play3DSound("coll_ship2ship", x, y, z); }
}

void Ship_ApplyCrewHitpoints(ref rOurCharacter, float fCrewHP)
{         
	if (LAi_IsImmortal(rOurCharacter)) 
	{ 
		return; 
	}

	ref rBaseShip = GetRealShip(GetCharacterShipType(rOurCharacter));
	float fMultiply = 1.0 - (0.75 * stf(rOurCharacter.TmpSkill.Defence)); 

	if(CheckOfficersPerk(rOurCharacter, "Doctor2"))
	{
		fMultiply = fMultiply * 0.8;
	}
	else
	{
		if(CheckOfficersPerk(rOurCharacter, "Doctor1"))
		{
			fMultiply = fMultiply * 0.9;
		}
	}
	
	fMultiply = fMultiply * isEquippedAmuletUse(rOurCharacter, "amulet_10", 1.0, 0.95 );
			
	float fDamage = fCrewHP * fMultiply; 

	float fNewCrewQuantity = stf(rOurCharacter.Ship.Crew.Quantity) - fDamage;
	float f5Percent = stf(rBaseShip.MinCrew) * 0.25; 
	
	if (fNewCrewQuantity >= f5Percent && IsCompanion(rOurCharacter))
	{
       AddCharacterExpToSkill(rOurCharacter, "Defence", makefloat(fCrewHP / 2 + 0.5));
       ChangeCrewExp(rOurCharacter, "Soldiers",  (fCrewHP / stf(rBaseShip.OptCrew))); 
    }
    
	
	if (fNewCrewQuantity < f5Percent) { fNewCrewQuantity = f5Percent; }
	if (fNewCrewQuantity < 0.0) { fNewCrewQuantity = 0.0; }
	
	if (sti(rOurCharacter.index) == GetMainCharacterIndex() && stf(rBaseShip.MinCrew) > fNewCrewQuantity && stf(rBaseShip.MinCrew) <= stf(rOurCharacter.Ship.Crew.Quantity))
    {  
        PlaySound("OBJECTS\SHIPCHARGE\_Damage1.wav");
    }
	
	if (stf(rOurCharacter.Ship.Crew.Quantity) > fNewCrewQuantity)
	{   
		if (sti(rOurCharacter.index) == GetMainCharacterIndex() || IsCompanion(rOurCharacter))
		{
			Statistic_AddValue(GetMainCharacter(), "Sailors_dead", stf(rOurCharacter.Ship.Crew.Quantity) - fNewCrewQuantity);
			Achievment_SetStat(GetMainCharacter(), 21, makeint(sti(rOurCharacter.Ship.Crew.Quantity) - fNewCrewQuantity));
		}
		rOurCharacter.Ship.Crew.Quantity = fNewCrewQuantity;
	}
	if (stf(rOurCharacter.Ship.Crew.Quantity) < 0.0) { rOurCharacter.Ship.Crew.Quantity = 0.0; }
	
}

void Ship_ApplyHullHitpoints(ref rOurCharacter, float fHP, int iKillStatus, int iKillerCharacterIndex)
{
   	if (LAi_IsImmortal(rOurCharacter)) { return; }

	float fCurHP;
	float fMinus 	= 0.0;
	float fPlus 	= 0.0;
	float fPercent	= 0.0;
	
    if (bSeaReloadStarted) { return; }
	if (fHP <= 0.0) { return; }
	if (LAi_IsDead(rOurCharacter) || !CheckAttribute(rOurCharacter, "Ship.HP")) { return; }   
	
    if (iKillerCharacterIndex >= 0)
	{
		if (sti(Characters[iKillerCharacterIndex].TmpPerks.HullDamageUp)) 		fPlus = 0.15;
		if (sti(Characters[iKillerCharacterIndex].TmpPerks.CannonProfessional)) fPlus = 0.3;
		
		if(IsCharacterEquippedArtefact(&Characters[iKillerCharacterIndex], "indian_8")) fPlus = fPlus * 1.05;
	}

	if (sti(rOurCharacter.TmpPerks.BasicBattleState))			fMinus = 0.15;
	if (sti(rOurCharacter.TmpPerks.AdvancedBattleState))		fMinus = 0.25;
	if (sti(rOurCharacter.TmpPerks.ShipDefenseProfessional))	fMinus = 0.35;
	
	if(IsCharacterEquippedArtefact(rOurCharacter, "amulet_8")) fMinus = fMinus * 1.05; 
	
	if (CheckAttribute(rOurCharacter, "SeaBoss")) fMinus = fPlus + stf(rOurCharacter.SeaBoss); 

	fCurHP = stf(rOurCharacter.Ship.HP) - fHP * (1.0 + fPlus - fMinus);
	
	if (CheckAttribute(rOurCharacter, "ShipHideImmortal")) 
	{
		if (fCurHP <= sti(rOurCharacter.ShipHideImmortal)) LAi_SetImmortal(rOurCharacter, true);
	}
	if (fCurHP <= 0.0)
	{
		if (CheckAttribute(rOurCharacter, "ShipHideImmortal"))
		{
			fCurHP = 200.0;
			LAi_SetImmortal(rOurCharacter, true);
		}
		else
		{
			fCurHP = 0.0;
			ShipDead(sti(rOurCharacter.index), iKillStatus, iKillerCharacterIndex);
		}
	}
	
    if(fCurHP > sti(RealShips[sti(rOurCharacter.ship.type)].HP))
	{
		fCurHP = RealShips[sti(rOurCharacter.ship.type)].HP;
	}
	rOurCharacter.Ship.HP = fCurHP;
	
	
	if(CheckAttribute(RealShips[sti(rOurCharacter.ship.type)],"QuestShip")) fPercent = 1.0;
	else fPercent = 1.0 + (makefloat(MOD_SKILL_ENEMY_RATE)/4.0);
	
	rOurCharacter.Ship.HP_penalty = makefloat(sti(RealShips[sti(rOurCharacter.ship.type)].HP) * fPercent/100.0 * (100.0 - GetHullPercent(rOurCharacter))/100.0);
	
	
}


void Ship_AddCharacterExp(ref rCharacter, int iExpQuantity)
{
	if(IsCompanion(rCharacter) == true || rCharacter.id == pchar.id)
	{
		AddPartyExp(pchar, iExpQuantity);
	}
	
	if (sti(rCharacter.index) == nMainCharacterIndex)
	{
		fSeaExp = fSeaExp + iExpQuantity;
	}
}


void ShipDead(int iDeadCharacterIndex, int iKillStatus, int iKillerCharacterIndex)
{
	ref rDead, rKillerCharacter, rBaseShip, rKillerBaseShip, sld;

	rDead = GetCharacter(iDeadCharacterIndex);
	if (!CheckAttribute(rDead, "Ship.Type")) 
    {
        if (MOD_BETTATESTMODE == "On") Log_Info("Error: ShipDead ��� ������� � iDeadCharacterIndex = "+iDeadCharacterIndex);
        return;
    }
    bool bDeadCompanion = IsCompanion(rDead);
	rBaseShip = GetRealShip(sti(rDead.Ship.Type));

	if (iKillerCharacterIndex != -1)
	{
		rKillerCharacter = GetCharacter(iKillerCharacterIndex);
		rKillerBaseShip = GetRealShip(sti(rKillerCharacter.Ship.Type));
		
		if (!bDeadCompanion && iKillStatus != KILL_BY_SPY)
        {
			switch (iKillStatus)
		    {
			    case KILL_BY_TOUCH:
	                AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 90);
	                ChangeCrewExp(rKillerCharacter, "Sailors", 1);
	                
	                Statistic_AddValue(rKillerCharacter, "KillShip_" + rBaseShip.Class, 1);
					Achievment_SetStat(rKillerCharacter, 3, 1);
					if(sti(rKillerCharacter.nation) == PIRATE) Achievment_SetStat(rKillerCharacter, 50, 1);
	                
			    break;
			    case KILL_BY_BALL:
			        AddCharacterExpToSkill(rKillerCharacter, "Accuracy", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 35);
			        AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 65);
			        AddCharacterExpToSkill(rKillerCharacter, "Cannons", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 40);
			        ChangeCrewExp(rKillerCharacter, "Sailors", 1);
			        ChangeCrewExp(rKillerCharacter, "Cannoners", 2);
			        
	                Statistic_AddValue(rKillerCharacter, "KillShip_" + rBaseShip.Class, 1);
					Achievment_SetStat(rKillerCharacter, 3, 1);
					if(sti(rKillerCharacter.nation) == PIRATE) Achievment_SetStat(rKillerCharacter, 50, 1);
	                
	                
        			if (rand(4) == 2 && GetRelation(sti(rDead.Index), sti(Pchar.Index))== RELATION_ENEMY)
                    {
                        
                        if(!CheckAttribute(rDead, "DontRansackCaptain") || rDead.DontRansackCaptain == false) AISeaGoods_AddGood(rDead, "enemy_boat", "lo_boat", 1000.0, 1); 
                    }
                    
			    break;
			    case KILL_BY_ABORDAGE:
			        AddCharacterExpToSkill(rKillerCharacter, "Grappling", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 110);
			        AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 70);
			        AddCharacterExpToSkill(rKillerCharacter, SKILL_FORTUNE, stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 10);
			        AddCharacterExpToSkill(rKillerCharacter, "Defence", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 60);
			        ChangeCrewExp(rKillerCharacter, "Sailors", 0.5);
					
			        
	                Statistic_AddValue(rKillerCharacter, "KillAbordShip_" + rBaseShip.Class, 1);
	                
			    break;
		    }
			if (iKillStatus != KILL_BY_SELF)
			{
		        AddCharacterExpToSkill(rKillerCharacter, SKILL_FORTUNE, stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 20);
		        AddCharacterExpToSkill(rKillerCharacter, "Leadership", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 25);

	            
		    	Statistic_AddValue(rKillerCharacter, NationShortName(sti(rDead.nation))+"_KillShip", 1);
		    	if (rand(8) < 3 && sti(rDead.nation) != PIRATE)  
		    	{
					ChangeCharacterHunterScore(rKillerCharacter, NationShortName(sti(rDead.nation)) + "hunter", 1+rand(1));
				}
			}
        }
        
	}

	
	
	float fX = stf(rDead.Ship.Pos.x);
	float fY = stf(rDead.Ship.Pos.y);
	float fZ = stf(rDead.Ship.Pos.z);

	rDead.Ship.HP = 0;
	rDead.Killer.Status = iKillStatus;
	rDead.Killer.Index = iKillerCharacterIndex;
		
	LAi_SetCurHP(rDead, 0.0);
		
	int iExp = 0;
	if (iKillerCharacterIndex != -1) 
	{ 
		iExp = 2 * MakeInt(stf(rBaseShip.HP) * stf(rKillerBaseShip.Class) / stf(rBaseShip.Class)); 
	}

	bool bCompanion = false;
	if (iKillerCharacterIndex != -1) 
	{ 
		bCompanion = IsCompanion(rKillerCharacter); 
	}

 	if (bCompanion && bDeadCompanion)
	{
		iExp = 0;
		
		if (iKillerCharacterIndex == GetMainCharacterIndex())
		{
			ChangeCharacterComplexReputation(pchar,"nobility", -15);
		}
		
	}      
    
	bool bRealKill = false;
	switch (iKillStatus)
	{
		case KILL_BY_TOUCH:
			if (iKillerCharacterIndex != -1) { bRealKill = true; }
		break;
		case KILL_BY_BALL:
			bRealKill = true;
		break;
		case KILL_BY_ABORDAGE:
			bRealKill = true;
		break;
	}

	
	if (iDeadCharacterIndex != nMainCharacterIndex)
	{
		string sSunkString;
		string sSunkShipType = XI_ConvertString(rBaseShip.BaseName);
		string sKillShipType = "";
		string sKillShipName = "";
		if (iKillerCharacterIndex != -1)
		{
		    sKillShipType = XI_ConvertString(rKillerBaseShip.BaseName);
		    sKillShipName = "" + rKillerCharacter.Ship.Name;
		}
		if (bCompanion && !bDeadCompanion && bRealKill)
		{
            sSunkString = sSunkShipType + " '" + rDead.Ship.Name + "' " + GetShipSexWord(rBaseShip.BaseName, "was sunk by ", "was sunk by ") + GetFullName(rKillerCharacter);
        }
        else
        {
            if (sKillShipName == "")
            {
            	sSunkString = sSunkShipType + " '" + rDead.Ship.Name + "' " + GetShipSexWord(rBaseShip.BaseName, "was sunk.", "was sunk.");
            }
            else
            {
				sSunkString = sSunkShipType + " '" + rDead.Ship.Name + "' " +GetShipSexWord(rBaseShip.BaseName, "was sunk by ", "was sunk by ") + sKillShipType + " '" + sKillShipName + "'";
			}
        }
		Log_SetStringToLog(sSunkString);
	}

 	if (rand(10) >= 6) 
	{ 
		bool bDetonate = false;
		switch (iKillStatus)
		{
			case KILL_BY_BALL:	
				bDetonate = true; 
			break;
			  
		}
		if (bDetonate) 
		{ 
			Ship_Detonate(rDead, true, false); 
		}
	}

	
	rDead.Ship.Sink = "";
	aref aSink; makearef(aSink, rDead.Ship.Sink);
	
 
	
	aSink.Speed.y = 0.25 + (frnd() * 0.05);	
	aSink.Speed.x = 0.021 * (frnd() * 2.0 - 1.0);	
	aSink.Speed.z = 0.04 * (frnd() * 2.0 - 1.0);	
	
	if (iDeadCharacterIndex == nMainCharacterIndex)
	{ 
		SeaCameras_SetDieCamera();
		FadeOutMusic(2);
		
		
		if (iKillerCharacterIndex != -1 && rKillerCharacter.id == "GhostCapt")
		{
		    DoQuestCheckDelay("Survive_In_Sea", 9.0);
		}
		else
		{
			InterfaceStates.Buttons.Save.enable = false;
			PostEvent(GAME_OVER_EVENT, 15000);
		}
	}
    
	else
	{
        if (bDeadCompanion && CheckOfficersPerk(rDead, "ShipEscape") && GetRemovable(rDead)) 
        {
            
            AISeaGoods_AddGood(rDead, "boat", "lo_boat", 1000.0, 1);
            RemoveCharacterCompanion(pchar, rDead);
            Log_Info(GetFullName(rDead) + " used a rowboat.");
        }
	}
	
	Play3DSound("ship_sink", fX, fY, fZ);

	
	SendMessage(&AISea, "la", AI_MESSAGE_CHARACTER_DEAD, rDead);

	
	Event(SHIP_DEAD, "l", iDeadCharacterIndex);
}


void ShipTaken(int iDeadCharacterIndex, int iKillStatus, int iKillerCharacterIndex)
{
	ref rDead, rKillerCharacter, rMainCharacter, rBaseShip, rKillerBaseShip;

	rDead = GetCharacter(iDeadCharacterIndex);
	rDead.Killer.Index = iKillerCharacterIndex;
	rBaseShip = GetRealShip(sti(rDead.Ship.Type));
	rMainCharacter = GetMainCharacter();

	bool bCompanion = false;
	bool bDeadCompanion = IsCompanion(rDead);

    LAi_SetCurHP(rDead, 0.0); 
	rDead.Killer.Status = iKillStatus;
	rDead.Killer.Index = iKillerCharacterIndex;
    if (iKillerCharacterIndex != -1 && !bDeadCompanion)
	{
		rKillerCharacter = GetCharacter(iKillerCharacterIndex);
		rKillerBaseShip = GetRealShip(sti(rKillerCharacter.Ship.Type));
		bCompanion = IsCompanion(rKillerCharacter);
		
        AddCharacterExpToSkill(rKillerCharacter, SKILL_FORTUNE, stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 20);
        AddCharacterExpToSkill(rKillerCharacter, "Leadership", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 25);
        AddCharacterExpToSkill(rKillerCharacter, "Grappling", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 120);
		AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 70);
		AddCharacterExpToSkill(rKillerCharacter, "Commerce", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 30);
		AddCharacterExpToSkill(rKillerCharacter, "Repair", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 60);
		AddCharacterExpToSkill(rKillerCharacter, "Defence", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 60);
        
        
        Statistic_AddValue(rKillerCharacter, "AbordShip_" + rBaseShip.Class, 1);
        Statistic_AddValue(rKillerCharacter, NationShortName(sti(rDead.nation))+"_AbordShip", 1);
		Achievment_SetStat(rKillerCharacter, 2, 1);
        
        
        ChangeCrewExp(rKillerCharacter, "Sailors", 0.5);
		
	}
	if (iDeadCharacterIndex != GetMainCharacterIndex())
	{
		string sSunkShipType = XI_ConvertString(rBaseShip.BaseName);
		string sKillShipType = XI_ConvertString(rKillerBaseShip.BaseName);

		if(bCompanion && !bDeadCompanion)
		{
            Log_SetStringToLog(sSunkShipType + " '" + rDead.Ship.Name + "' " + "was captured!");
        }
	}
    if (rand(8) < 3 && !bDeadCompanion && sti(rDead.nation) != PIRATE)  
    {
        ChangeCharacterHunterScore(rKillerCharacter, NationShortName(sti(rDead.nation)) + "hunter", 1+rand(1));
    }
}

void ShipTakenFree(int iDeadCharacterIndex, int iKillStatus, int iKillerCharacterIndex)
{
	ref rDead, rKillerCharacter, rMainCharacter, rBaseShip, rKillerBaseShip;

	rDead = GetCharacter(iDeadCharacterIndex);
	rDead.Killer.Index = iKillerCharacterIndex;
	rBaseShip = GetRealShip(sti(rDead.Ship.Type));
	rMainCharacter = GetMainCharacter();

    LAi_SetCurHP(rDead, 0.0); 
	rDead.Killer.Status = iKillStatus;
	rDead.Killer.Index = iKillerCharacterIndex;
    if (iKillerCharacterIndex != -1)
	{
		rKillerCharacter = GetCharacter(iKillerCharacterIndex);
		rKillerBaseShip = GetRealShip(sti(rKillerCharacter.Ship.Type));
		
        AddCharacterExpToSkill(rKillerCharacter, "Leadership", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 50);
        AddCharacterExpToSkill(rKillerCharacter, "Grappling", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 120);
		AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 80);
		AddCharacterExpToSkill(rKillerCharacter, SKILL_FORTUNE, stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 70);
		AddCharacterExpToSkill(rKillerCharacter, "Repair", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 10);
		AddCharacterExpToSkill(rKillerCharacter, "Defence", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 10);
        
		Statistic_AddValue(rKillerCharacter, "AbordShipFree_" + rBaseShip.Class, 1);  
        Statistic_AddValue(rKillerCharacter, NationShortName(sti(rDead.nation))+"_AbordShipFree", 1);
        Statistic_AddValue(rKillerCharacter, "AbordShipFree", 1); 
        
        ChangeCrewExp(rKillerCharacter, "Sailors", 0.5);
		
		if(!CheckAttribute(rDead,"Situation"))
		{
			ChangeCharacterComplexReputation(rKillerCharacter,"nobility", 2); 
			ChangeCharacterComplexReputation(rKillerCharacter,"authority", -2); 
			ChangeCharacterComplexReputation(rKillerCharacter,"fame", 1); 
			OfficersReaction("good");
		}	
	}
	if (iDeadCharacterIndex != GetMainCharacterIndex() && !CheckAttribute(rDead,"Situation"))
	{
		string sSunkShipType = XI_ConvertString(rBaseShip.BaseName);
		string sKillShipType = XI_ConvertString(rKillerBaseShip.BaseName);

        Log_SetStringToLog(sSunkShipType + " '" + rDead.Ship.Name + "' " + "was captured but released after the plunder.");
		if (CheckAttribute(pchar, "GenQuest.Detonation"))
		{
			DoQuestCheckDelay("CanNotEnterToMap", 0.2); 
			DeleteAttribute(pchar, "GenQuest.Detonation");
		}
	}
    if (rand(20) < 3 && sti(rDead.nation) != PIRATE)  
    {
        ChangeCharacterHunterScore(rKillerCharacter, NationShortName(sti(rDead.nation)) + "hunter", 1+rand(1));
    }
}


void Ship_PlayVictory(string sSound, int iSoundTime)
{
	FadeOutMusic(3); 
	PlayStereoOgg(sSound);

	iVicSoundTime = iSoundTime;
}
  
void Ship_VicSoundTime()
{
	if (bAbordageStarted || sti(InterfaceStates.Launched)) { return; }

	if (iVicSoundTime > 0)
	{
		iVicSoundTime = iVicSoundTime - iRealDeltaTime;
		if (iVicSoundTime <= 0)
		{
			bUpdatePosMode = true;
		}
	}
}

void Ship_SailHitEvent()
{
}

void Ship_HullHitEvent()
{
	float	fHP;

	int		iBallType = sti(AIBalls.CurrentBallType);

	aref	rShipObject = GetEventData();

	int		iBallCharacterIndex = GetEventData();
	int		iOurCharacterIndex = GetEventData();

	ref		rBallCharacter = GetCharacter(iBallCharacterIndex);	
	ref		rOurCharacter = GetCharacter(iOurCharacterIndex);   

	rOurCharacter.Ship.LastBallCharacter = iBallCharacterIndex;

	float	x = GetEventData();
	float	y = GetEventData();
	float	z = GetEventData();

	int		iFirePlaceIndex = GetEventData();   
	float	fFirePlaceDistance = GetEventData();
	
	

	bool	bDead = LAi_IsDead(rOurCharacter) && CheckAttribute(rBallCharacter, "Ship.Cannons.Type");  

	bool	bSeriousBoom = false;
	bool	bInflame = false;
    bool    isOurCompanion   = IsCompanion(rOurCharacter);
    float   fTmpCannonDamage = 0;
    
    if (bDead) return; 
	
	ref rCannon = GetCannonByType(sti(rBallCharacter.Ship.Cannons.Type));
	float fCannonDamageMultiply = stf(rCannon.DamageMultiply);

	float fDistanceDamageMultiply = Bring2Range(1.2, 0.25, 0.0, stf(AIBalls.CurrentMaxBallDistance), stf(AIBalls.CurrentBallDistance));

    if (sti(rBallCharacter.TmpPerks.CriticalShoot) && rand(19)==10) { bSeriousBoom = true; }		
	if (sti(rBallCharacter.TmpPerks.CannonProfessional) && rand(9)==4) { bSeriousBoom = true; }		
	
	ref rBall = GetGoodByType(iBallType);
	switch (iBallType)
	{
		case GOOD_BALLS:
			if (rand(85) == 17) { bSeriousBoom = true; }  
			if (rand(30) == 15) { bInflame = true; }
			Play3DSound("ball2bort", x, y, z);
		break;
		case GOOD_GRAPES:
			bSeriousBoom = false;
			Play3DSound("grapes2bort", x, y, z);
            if (rand(100) < 30) {Play3DSound("episode_boom", x, y, z);}
		break;
		case GOOD_KNIPPELS:
			bSeriousBoom = false;
			Play3DSound("ball2bort", x, y, z);
		break;
		case GOOD_BOMBS:
			if (rand(50) == 10) { bSeriousBoom = true; }  
			if (rand(5) == 1) { bInflame = true; }
			Play3DSound("bomb2bort", x, y, z);
		break;
	}
	fTmpCannonDamage = fCannonDamageMultiply * stf(rBall.DamageHull);
	if (rand(2) == 1) CreateParticleSystem("blast", x, y, z, 0.0, 0.0, 0.0, 0);

    if (sti(rOurCharacter.TmpPerks.ShipDefenseProfessional) && rand(1000) < 700) { bSeriousBoom = false; }				

    float fCrewDamage = stf(rBall.DamageCrew) * fCannonDamageMultiply * AIShip_isPerksUse(rBallCharacter.TmpPerks.CrewDamageUp, 1.0, 1.15);

	if (bSeriousBoom)
	{
		fCrewDamage = fCrewDamage * 7.0;
		fHP = fDistanceDamageMultiply * fCannonDamageMultiply * stf(rBall.DamageHull) * (8.0 + frnd() * 4.0); 
		Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_BALL, iBallCharacterIndex);

		if (iBallCharacterIndex == nMainCharacterIndex)
		{
			Log_SetStringToLog(LanguageConvertString(iSeaSectionLang, "Ship_critical"));
		}
		 
		
		if (!isOurCompanion && IsCompanion(rBallCharacter) && !CheckAttribute(rOurCharacter, "ShipEnemyDisable"))
		{
            AddCharacterExpToSkill(rBallCharacter, "Accuracy", 15);
            AddCharacterExpToSkill(rBallCharacter, SKILL_FORTUNE, 15);
            AddCharacterExpToSkill(rBallCharacter, "Leadership", 2);
            AddCharacterExpToSkill(rBallCharacter, "Sailing", 15);
            AddCharacterExpToSkill(rBallCharacter, "Cannons", 15);
            ChangeCrewExp(rBallCharacter, "Sailors", 0.05);
			ChangeCrewExp(rBallCharacter, "Cannoners", 0.5);
        }
        
	}
	else
	{ 
		fHP = fDistanceDamageMultiply * fCannonDamageMultiply * stf(rBall.DamageHull);
		Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_BALL, iBallCharacterIndex); 
		
		if (!isOurCompanion && IsCompanion(rBallCharacter) && !CheckAttribute(rOurCharacter, "ShipEnemyDisable"))
		{
            AddCharacterExpToSkill(rBallCharacter, "Accuracy", 2.5);
            AddCharacterExpToSkill(rBallCharacter, "Sailing", 1);
            AddCharacterExpToSkill(rBallCharacter, "Cannons", 1);
            ChangeCrewExp(rBallCharacter, "Cannoners", 0.01);
        }
        
	}
	Ship_ApplyCrewHitpoints(rOurCharacter, fCrewDamage);

	if (bInflame == true && fFirePlaceDistance < 4.0 && iFirePlaceIndex >= 0)
	{
		int iRandStartTime = rand(1000);
		float fTotalFireTime = Ship_GetTotalFireTime(rOurCharacter); 

		PostEvent(SHIP_ACTIVATE_FIRE_PLACE, iRandStartTime, "ialsfl", rShipObject, rOurCharacter, iFirePlaceIndex, "ship_onfire", fTotalFireTime, iBallCharacterIndex);
		PostEvent(SHIP_FIRE_DAMAGE, iRandStartTime, "lllf", iOurCharacterIndex, iBallCharacterIndex, iFirePlaceIndex, fTotalFireTime);
	}

	if (bSeriousBoom == true) 
	{ 
		if (rOurCharacter.id == pchar.id || rand(2) == 1)
		{
			Ship_Serious_Boom(x, y, z); 
		}
		fTmpCannonDamage = fTmpCannonDamage * 6.0;
		
		if ((GetCargoGoods(rOurCharacter, GOOD_POWDER) / 20.0) > (GetCargoMaxSpace(rOurCharacter) * 0.25) && rand(1) == 1)
		{
			Ship_SetExplosion(rOurCharacter, rShipObject);
			Log_Info("Whole powder supply got exploded on " + rOurCharacter.Ship.Name + ".");
		}
		
	}
    SendMessage(&AISea, "laffff", AI_MESSAGE_CANNONS_BOOM_CHECK, rOurCharacter, fTmpCannonDamage, x, y, z);  
	
	
	
 	
	
	if (sti(rOurCharacter.Ship.LastBallCharacter) == GetMainCharacterIndex() && GetNationRelation2MainCharacter(sti(rOurCharacter.nation)) != RELATION_ENEMY)
    {
        if (!isOurCompanion && !CheckAttribute(rOurCharacter, "Coastal_Captain")) 
        {
            Ship_NationAgressive(rOurCharacter, rOurCharacter);
            DoQuestCheckDelay("NationUpdate", 0.7);
        }
    }
	
	bool btrade = (sti(rOurCharacter.Ship.LastBallCharacter) == GetMainCharacterIndex()) && (CheckAttribute(rOurCharacter, "Ship.Mode")) && (rOurCharacter.Ship.Mode == "trade");
	bool bhol = (sti(rOurCharacter.Ship.LastBallCharacter) == GetMainCharacterIndex()) && (sti(rOurCharacter.nation) == HOLLAND)
	if (CheckCharacterItem(pchar, "HolTradeLicence"))
	{
		if (btrade || bhol)
		{
			TakeNationLicence(HOLLAND);
			log_info("A trade license was annulled!");
		}
	}
	 
	if (rOurCharacter.id == "WorldMarchCap1" || rOurCharacter.id == "WorldMarchCap2" || rOurCharacter.id == "WorldMarchCap3") 
	{
		if (!CheckAttribute(pchar, "GenQuest.MarchCap.Battlestart")) DoQuestFunctionDelay("MarchCap2_CheckBattle", 0.5);
	}
	if (rOurCharacter.id == "Cap_Vensan") 
	{
		if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Vensan_free")) DoQuestFunctionDelay("Saga_BrigantineDetonate", 0.5);
	}
	if (rOurCharacter.id == "Saga_Vagrant" || rOurCharacter.id == "Saga_vampire") 
	{
		Saga_VagrantVampireAttack();
	}
	if (rOurCharacter.id == "Jackman") 
	{
		Saga_CenturionAttack();
	}
	if (rOurCharacter.id == "Molligan" && CheckAttribute(pchar, "questTemp.Saga.Molligan.friend") && sti(AIBalls.CurrentBallType) == GOOD_GRAPES) 
	{
		Saga_MolliganCriticalAttack();
	}
	if (rOurCharacter.id == "Rozencraft" && CheckAttribute(pchar, "GenQuest.Bakaut")) 
	{
		DeleteAttribute(pchar, "GenQuest.Bakaut"); 
	}
	if (rOurCharacter.id == "Cap_Utreht" && !CheckAttribute(pchar, "questTemp.Mtraxx.check")) 
	{
		pchar.questTemp.Mtraxx.watcher = "true"; 
		pchar.questTemp.Mtraxx.check = "true";
		
	}
    
}

float Ship_GetTotalFireTime(ref rCharacter)
{
	int iRepairSkill = MakeInt(stf(rCharacter.TmpSkill.Repair) * 10.0); 
	return MakeFloat(5 + 3 * (10 - iRepairSkill));
}

void Ship_FireDamage()
{
	int iOurCharacterIndex = GetEventData();
	int iBallCharacterIndex = GetEventData();

	int iFirePlaceIndex = GetEventData();
	float fTotalFireTime = GetEventData();

	ref rOurCharacter = GetCharacter(iOurCharacterIndex);
	
	
	int iSClass = GetCharacterShipClass(rOurCharacter);

	float fHP = (8 - iSClass) * (0.5 + frnd() * 0.5);

	int iTime = 1000 + rand(500);

	
	if (!bAbordageStarted && !sti(InterfaceStates.Launched)) 
	{ 
		Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_BALL, iBallCharacterIndex); 

		fTotalFireTime = fTotalFireTime - MakeFloat(iTime) / 250.0;
	}

	if (fTotalFireTime > 0.0)
	{
		PostEvent(SHIP_FIRE_DAMAGE, iTime, "lllf", iOurCharacterIndex, iBallCharacterIndex, iFirePlaceIndex, fTotalFireTime);
	}
}

void Ship_Serious_Boom(float x, float y, float z)
{
	CreateBlast(x,y,z);
	CreateParticleSystem("ShipExplode", x, y, z, 0.0, 0.0, 0.0, 0);
	Play3DSound("ship_explosion", x, y, z);
}

void Ship_SetFantomData(ref rFantom)
{
	ref		rBaseShip;

	rBaseShip = GetRealShip(sti(rFantom.Ship.Type));

	int iOptCrew = sti(rBaseShip.OptCrew);

	int iBaseHP = sti(rBaseShip.HP);
	int iCapacity = sti(rBaseShip.Capacity);

	rFantom.ship.Crew.Quantity = iOptCrew - rand(makeint(iOptCrew / 3)) + makeint(iOptCrew / 5); 
	
	rFantom.Ship.HP = iBaseHP;
	if (rand(3) == 2) 
	{ 
		rFantom.Ship.HP = iBaseHP - rand(makeint(iBaseHP / 8));
	}
	if (CheckAttribute(rFantom, "Ship.Masts")) { DeleteAttribute(rFantom, "Ship.Masts"); }
	if (CheckAttribute(rFantom, "Ship.Blots")) { DeleteAttribute(rFantom, "Ship.Blots"); }
	if (CheckAttribute(rFantom, "Ship.Sails")) { DeleteAttribute(rFantom, "Ship.Sails"); }
	if (CheckAttribute(rFantom, "Ship.Hulls")) { DeleteAttribute(rFantom, "Ship.Hulls"); }
}

void CharacterUpdateShipFromBaseShip(int iCharacterIndex)
{
	ref rCharacter, rBaseShip;
	
	rCharacter = GetCharacter(iCharacterIndex);
	rBaseShip = GetRealShip(sti(rCharacter.Ship.Type));

	if (!CheckAttribute(rCharacter,"Ship.Crew.Quantity")) 
	{ 
		rCharacter.ship.Crew.Quantity = rBaseShip.MaxCrew; 
	}

	if (!CheckAttribute(rCharacter,"Ship.HP")) 
	{ 
		rCharacter.Ship.HP = rBaseShip.HP; 
	}
	if (!CheckAttribute(rCharacter,"Ship.SP")) 
	{ 
		rCharacter.Ship.SP = rBaseShip.SP; 
	}

	if (!CheckAttribute(rCharacter,"Ship.Cannons.Charge.Type")) 
	{ 
		rCharacter.Ship.Cannons.Charge.Type = GOOD_BOMBS; 
	}
	
	
	if (!CheckAttribute(rCharacter,"Ship.Cannons.Type")) 
	{ 
		rCharacter.Ship.Cannons.Type = CANNON_TYPE_CULVERINE_LBS8; 
	}

	rCharacter.Ship.Cannons.Borts = "";
}

float Ship_CalcGrapplingPerk(ref rCharacter)
{
	aref	arTmpPerks; 
	makearef(arTmpPerks, rCharacter.TmpPerks);

	float fGrapplingPerk = AIShip_isPerksUse(rCharacter.TmpPerks.LongRangeGrappling, 1.0, 1.15); 
	return AIShip_isPerksUse(rCharacter.TmpPerks.GrapplingProfessional, fGrapplingPerk, 1.25);

	return fGrapplingPerk;
}

float Ship_CalcMaxAbordageDistance(float fGrappling, float fGrapplingPerk)
{
	return fGrapplingPerk * Bring2Range(15.0, 40.0, 0.0, 1.0, fGrappling);
}

float Ship_CalcMaxAbordageAngle(float fGrappling)
{
	return Bring2Range(0.70, 0.45, 0.0, 1.0, fGrappling);
}

float Ship_CalcMaxAbordageSpeed(float fGrappling)
{
	return Bring2Range(3.0, 5.0, 0.0, 1.0, fGrappling);
}

void Ship_CheckEnemiesAroundMainCharacter()
{
}

void Ship_CheckMainCharacter()
{
	aref	arUpdate;
	ref		rIsland;
	int		i, iRelation;
	float	x, z, fBestDistance, fDistance;
	float	fMinEnemyDistance = 1000000.0;
	float	fMinFortAbordDistance = 1000000.0; 
	float	fortDistance = 1000000.0; 
	bool	bAbordageStartNow = false;
	int		iAbordageStartNowCharacter = -1;

	PostEvent(SHIP_CHECK_RELOAD_ENABLE, 1000);

	ref rCharacter = pchar;

	
	if (bAbordageStarted) { return; }

	
	if (sti(InterfaceStates.Launched)) { return; }

	
	if (LAi_IsDead(rCharacter)) { return; }

	iStormLockSeconds = iStormLockSeconds - 1;
	if (iStormLockSeconds < 0) { iStormLockSeconds = 0; }

	bAbordageFortCanBe = false;
	bAbordageShipCanBe = false;
	bCanEnterToLand = false;
	bDisableSailTo = false;
	sIslandLocator = "";
	sIslandID = "";

	makearef(arUpdate, rCharacter.SeaAI.Update);

	if (!CheckAttribute(arUpdate, "Ships")) { return; }
	if (!CheckAttribute(arUpdate, "Forts")) { return; }
    
    locTmpTime = locTmpTime + 0.5;  
    if (locTmpTime > 9)
	{
		 
		    CalcLocalTime(2);
      		BattleInterface.textinfo.Date.text = XI_convertString("Date:")+GetQuestBookData();
		
	}
	
	
	x = stf(rCharacter.Ship.Pos.x);
	z = stf(rCharacter.Ship.Pos.z);

	float fOurHP = Ship_GetHP(rCharacter);
	float fOurFencing = stf(rCharacter.TmpSkill.Fencing);
	float fOurGrappling = stf(rCharacter.TmpSkill.Grappling);
	float fOurCrewFencing = (0.1 + fOurFencing * stf(rCharacter.Ship.Crew.Quantity));

	float fOurBoxSizeX = stf(rCharacter.Ship.BoxSize.x) / 2.0;

	bool bGrapplingProfessional = sti(rCharacter.TmpPerks.GrapplingProfessional);

	
	float fOurGrapplingPerk = Ship_CalcGrapplingPerk(rCharacter);

	float fOurMaxAbordageDistance = Ship_CalcMaxAbordageDistance(fOurGrappling, fOurGrapplingPerk);
	float fOurMaxAbordageAngle = Ship_CalcMaxAbordageAngle(fOurGrappling); 
	float fOurMaxAbordageSpeed = Ship_CalcMaxAbordageSpeed(fOurGrappling);

	string sPlayerLocation = rCharacter.location;
	string sPlayerLocator = rCharacter.location.locator;

	
	int iIslandIndex = FindIsland(sPlayerLocation);
	if (iIslandIndex >= 0)
	{
		rIsland = GetIslandByIndex(iIslandIndex);
	}

	aref aShips, aForts;
	makearef(aShips, arUpdate.Ships);
	makearef(aForts, arUpdate.Forts);

	
	int iFortsNum = GetAttributesNum(aForts);
	fBestDistance = 10000000.0;
	for (i=0; i<iFortsNum; i++)
	{
		aref aFort = GetAttributeN(aForts, i);
		iRelation = sti(aFort.relation);

		ref rFortCharacter = GetCharacter(sti(aFort.idx)); 
		if (LAi_IsDead(rFortCharacter)) { continue; }
		int iFortMode = sti(rFortCharacter.Fort.Mode);
		aref aRLoc = FindIslandReloadLocator(sPlayerLocation, rFortCharacter.location.locator);
		if (!CheckAttribute(aRLoc, "Radius")) { continue; }  
		float fRadius = stf(aRLoc.Radius);
		fDistance = stf(aFort.Distance);
		switch (iFortMode)
		{
			case FORT_NORMAL:
				if (iRelation == RELATION_ENEMY)
				{
					if (fMinEnemyDistance > fDistance) { fortDistance = fDistance; }
				}
				else
				{
					
					
					if (!CheckAttribute(rFortCharacter, "CheckFlagYet"))
					{
                        if (!CheckAttribute(rFortCharacter, "CheckFlagDate") || GetNpcQuestPastDayParam(rFortCharacter, "CheckFlagDate") > 1)
                        { 
							if (fDistance < (MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER_FORT * 1.5))
						    {
						        rFortCharacter.CheckFlagYet = true; 
						        Ship_CheckFlagEnemy(rFortCharacter);
						        SaveCurrentNpcQuestDateParam(rFortCharacter, "CheckFlagDate");
						    }
					    }
					}
					
				}
				
				if (fDistance < 3000 && CheckAttribute(pchar, "questTemp.Mtraxx.check"))
				{
					DeleteAttribute(pchar, "questTemp.Mtraxx.check");
					pchar.questTemp.Mtraxx.Silkfail = "true";
				}
				if (fDistance < 5000 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Check"))
				{
					DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Check");
					pchar.questTemp.Mtraxx.Ignasio.Fail = "true";
				}
				if (fDistance < 5000 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Ship"))
				{
					Mtraxx_CorridaCheckPolacre();
				}
				if (fDistance < 1500 && fDistance > 800 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal"))
				{
					pchar.questTemp.Mtraxx.Ignasio.Flag = "true";
				}
				if (fDistance > 1500 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal") && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag"))
				{
					DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag");
				}
				if (fDistance < 800 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal"))
				{
					DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal");
					DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag");
					RemoveItems(pchar, "wolfreeks_book", 1);
					AddQuestRecord("Roger_8", "13");
					Mtraxx_CorridaIgnasioFail();
				}
				
				if (fDistance < 1000 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Patria.SanMartinFort") && ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
				{
					bQuestDisableMapEnter = true;
					DoQuestFunctionDelay("Mtraxx_MarkusGameOver", 3.0);
				}
				if (fDistance < 400 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Patria.SanMartinFort"))
				{
					Patria_SanMartinFortAttack();
				}
				if (fDistance > 1500 && pchar.location == "Nevis" && CheckAttribute(pchar, "questTemp.Patria.Escape"))
				{
					DeleteAttribute(pchar, "questTemp.Patria.Escape");
					bQuestDisableMapEnter = false;
				}
			break;
			case FORT_DEAD:
                if (iRelation == RELATION_FRIEND) { continue; }
				if (fDistance > fRadius) { continue; }
				if (fBestDistance > fDistance)
				{
					fBestDistance = fDistance;

					bCanEnterToLand = true;

					sIslandID = rIsland.id;
					makearef(arIslandReload, rIsland.reload);
					sIslandLocator = aRLoc.GoAfterBoard.location;
				}
			break;
			case FORT_ABORDAGE:
                if (iRelation == RELATION_FRIEND) { continue; }
				if (iRelation == RELATION_ENEMY)
				{
					
					if (fMinFortAbordDistance > fDistance) { fMinFortAbordDistance = fDistance; } 
				}
				if (fDistance > fRadius) { continue; }
				if (!Character_IsAbordageEnable(rFortCharacter) || bDisableMapEnter)  { continue; } 
				
				if (fBestDistance > fDistance)
				{
					fBestDistance = fDistance;

					bAbordageFortCanBe = true;
					sAbordageLocator = rFortCharacter.location.locator;
					iAbordageFortEnemyCharacter = sti(rFortCharacter.index);
				}
			break;
		}
	}

	
	int iShipsNum = GetAttributesNum(aShips);
	fBestDistance = 10000000.0;
	for (i=0; i<iShipsNum; i++)
	{
		aref aShip = GetAttributeN(aShips, i);

		ref rShipCharacter = GetCharacter(sti(aShip.idx)); 
		fDistance = stf(aShip.Distance);		
		iRelation = sti(aShip.relation);
		
		if (LAi_IsDead(rShipCharacter)) 
		{ 
			continue; 
		}
		if (iRelation != RELATION_ENEMY) 
		{ 
			continue; 
		}
		if (fMinEnemyDistance > fDistance) 
		{ 
			fMinEnemyDistance = fDistance; 
		}

		if (!Character_IsAbordageEnable(rShipCharacter)) 
		{ 
			continue; 
		}

		float fAng = stf(aShip.d_ay);						
		float fRelativeSpeed = stf(aShip.RelativeSpeed);	
		float fEnemyBoxSizeX = stf(rShipCharacter.Ship.BoxSize.x) / 2.0;

		bool bOurAngleTest = abs(fAng) > fOurMaxAbordageAngle && fRelativeSpeed < fOurMaxAbordageSpeed;
		float fAbordageDistance = fDistance - fEnemyBoxSizeX - fOurBoxSizeX;

		
		if (bGrapplingProfessional || bOurAngleTest)
		{
			if (fAbordageDistance < fOurMaxAbordageDistance && fBestDistance > fDistance)
			{
				
				fBestDistance = fDistance;
				bAbordageShipCanBe = true;
				iAbordageShipEnemyCharacter = sti(rShipCharacter.index);
			}
		}

		
		float fEnemyGrappling = stf(rShipCharacter.TmpSkill.Grappling);

		
		float fEnemyGrapplingPerk = Ship_CalcGrapplingPerk(rShipCharacter);

		float fEnemyMaxAbordageDistance = Ship_CalcMaxAbordageDistance(fEnemyGrappling, fEnemyGrapplingPerk);
		float fEnemyMaxAbordageAngle = Ship_CalcMaxAbordageAngle(fEnemyGrappling); 
		float fEnemyMaxAbordageSpeed = Ship_CalcMaxAbordageSpeed(fEnemyGrappling);

		bool bEnemyAngleTest = abs(fAng) > fEnemyMaxAbordageAngle && fRelativeSpeed < fEnemyMaxAbordageSpeed;
		if (bEnemyAngleTest)
		{
			if (fAbordageDistance < fEnemyMaxAbordageDistance)
			{
				
				float fEnemyFencing = stf(rCharacter.TmpSkill.Fencing); 
				float fEnemyCrewFencing = (0.1 + fEnemyFencing * stf(rShipCharacter.Ship.Crew.Quantity));
				float fRatio = fEnemyCrewFencing / fOurCrewFencing;
				if (sti(rShipCharacter.nation) == PIRATE) 
				{ 
					fRatio = fRatio * 1.6; 
				}
				if (fRatio > 1.2 && !CheckAttribute(rShipCharacter, "Abordage.MakeDisable")) 
				{
					iAbordageStartNowCharacter = sti(rShipCharacter.index);
					bAbordageStartNow = true;
					break;
				}
			}
		}
	}

	
	if (iIslandIndex >= 0 && fMinEnemyDistance > MIN_ENEMY_DISTANCE_TO_DISABLE_ENTER_2_LOCATION)
	{
		if (Island_isReloadEnableGlobal(sPlayerLocation))
		{
			aref arReload;
			makearef(arReload, rIsland.Reload);

			int iNumLocators = GetAttributesNum(arReload);
			for (int j=0; j<iNumLocators; j++)
			{
				aref arLocator;
				arLocator = GetAttributeN(arReload, j);
				string sLocatorName = GetAttributeName(arLocator);
				if (Island_isReloadFort(sPlayerLocation, arLocator.name)) { continue; }
				if (!Island_isReloadEnableLocal(sPlayerLocation, arLocator.name)) { continue; }
				if(!CheckAttribute(rIsland, "reload." + sLocatorName + ".x") || !CheckAttribute(rIsland, "reload." + sLocatorName + ".z"))
				{
					continue;
				}

				float x1 = stf(rIsland.reload.(sLocatorName).x);
				float z1 = stf(rIsland.reload.(sLocatorName).z);
				 
				float r = stf(rIsland.reload.(sLocatorName).radius);
				if (sqrt(sqr(x1 - x) + sqr(z1 - z)) < r)
				{
					bCanEnterToLand = true;
					sIslandID = rIsland.id;
					makearef(arIslandReload, rIsland.reload);
					sIslandLocator = rIsland.reload.(sLocatorName).name;
					break;
				}
			}
		}
	}

	
	if (Whr_IsStorm())
	{
		bAbordageStartNow = false;
		bAbordageFortCanBe = false;
		bAbordageShipCanBe = false;
	}

	
	
	int iPrevShipPOSMode = sti(rCharacter.Ship.POS.Mode);
	rCharacter.Ship.POS.Mode = SHIP_SAIL;

	bDisableMapEnter = false;
	if (fMinEnemyDistance < MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER)
	{
		bCanEnterToLand = false;
		bDisableMapEnter = true;

		rCharacter.Ship.POS.Mode = SHIP_WAR;
	}
	if (fortDistance < MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER_FORT)
	{
		bCanEnterToLand = false;
		bDisableMapEnter = true;
		rCharacter.Ship.POS.Mode = SHIP_WAR;
	}
    
    if (fMinFortAbordDistance < MIN_ENEMY_DISTANCE_TO_DISABLE_ENTER_2_LOCATION)
    {
        bCanEnterToLand = false;
    }
    
	if (iStormLockSeconds)
	{
		bDisableMapEnter = true;
		bCanEnterToLand = false;
		bDisableSailTo = true;

		rCharacter.Ship.POS.Mode = SHIP_STORM;
	}

	
	bool bMakeCurrentUpdate = bUpdatePosMode;
	if( iVicSoundTime<=0 && sti(rCharacter.Ship.POS.Mode) != iPrevShipPOSMode ) {
		bMakeCurrentUpdate = true;
	}
	if( bMakeCurrentUpdate )
	{
		switch (sti(rCharacter.Ship.POS.Mode))
		{
			case SHIP_SAIL:
				if (!Whr_IsStorm()) 
				{ 
					seaAlarmed = false;
					if (iPrevShipPOSMode == SHIP_WAR)
					{
                   		Ship_PlayVictory("music_ship_victory", 8500);
						
					} 
					FadeOutMusic(3);
					
					if (Whr_IsDay()) SetMusic("music_sea_day");
					else SetMusic("music_sea_night");
					

				}
				else
				{ 
					FadeOutMusic(3); 
					PlayStereoOGG("music_End_storm"); 
				}
			break;
			case SHIP_WAR:
				FadeOutMusic(3); 
				
				seaAlarmed = true;
				SetMusic("music_sea_battle");
				
			break;
		}

		bUpdatePosMode = false;
	}

	
	if (bQuestDisableMapEnter) { bDisableMapEnter = true; }

	
	if (bAbordageStartNow) 
	{ 
		ref rTargetCharacter = GetCharacter(iAbordageStartNowCharacter);
		if(GetRelation(sti(rCharacter.index), iAbordageStartNowCharacter) == RELATION_ENEMY)
		{
			if(LAi_IsDead(rCharacter) == false && LAi_IsDead(rTargetCharacter) == false)
			{
				iAbordageShipEnemyCharacter = iAbordageStartNowCharacter;
				Sea_AbordageLoad(SHIP_ABORDAGE, false); 
			}
		}
	}
}

void Ship_OnStrandNext()
{
	ref	rCharacter = GetCharacter(GetEventData());
	if (LAi_IsDead(rCharacter)) { return; }

	bool bOnStrand = sti(rCharacter.Ship.Strand);
	if (!bOnStrand) 
	{ 
		int iSoundID = sti(rCharacter.Ship.Strand.SndID);
		if (iSoundID != 0) { StopSound(sti(rCharacter.Ship.Strand.SndID), 3000); }
		rCharacter.Ship.Strand.SndID = SOUND_INVALID_ID;
		return; 
	}
	if (!CheckAttribute(rCharacter, "AlwaysSandbankManeuver"))  
	{
		float fCurrentSpeedZ = stf(rCharacter.Ship.Speed.z);
		float fHP = 4.0 * fCurrentSpeedZ / 7.0;
		Ship_ApplyHullHitpoints(rCharacter, fHP, KILL_BY_ISLAND, -1);
	}
	PostEvent(SHIP_TO_STRAND_NEXT, 100 + rand(100), "l", sti(rCharacter.index));
}

void Ship_OnStrand()
{
	ref rCharacter = GetCharacter(GetEventData());
	bool bNewStrand = GetEventData();
	
	bool bPrevStrand = sti(rCharacter.Ship.Strand);

	rCharacter.Ship.Strand = bNewStrand;

	float x = stf(rCharacter.Ship.Pos.x);
	float y = stf(rCharacter.Ship.Pos.y);
	float z = stf(rCharacter.Ship.Pos.z);

	if (bPrevStrand == 0 && bNewStrand == 1)
	{
		PostEvent(SHIP_TO_STRAND_NEXT, 100, "l", sti(rCharacter.index));
		rCharacter.Ship.Strand.SndID = Play3DSoundComplex("ship_aground", x, y, z, true, false);
	}
}


void Ship_DetonateSmall()
{
	ref		rCharacter = GetCharacter(GetEventData());
	aref	arCharShip; makearef(arCharShip, rCharacter.Ship);

    if (bAbordageStarted) { return; }
	if (sti(InterfaceStates.Launched)) { return; }
	
	float x = stf(arCharShip.Pos.x);
	float y = stf(arCharShip.Pos.y);
	float z = stf(arCharShip.Pos.z);
	
	if (y > -3.0)
	{
		int iSClass = GetCharacterShipClass(rCharacter);
		PostEvent(SHIP_DETONATE_SMALL, 200 + iSClass * 300 + rand(900), "l", sti(rCharacter.index));
	}

	float bx = arCharShip.BoxSize.x;
	float by = arCharShip.BoxSize.y;
	float bz = arCharShip.BoxSize.z;

	float fCos = cos(stf(arCharShip.Ang.y));
	float fSin = sin(stf(arCharShip.Ang.y));

	
	
		float x1, y1, z1;
		x1 = (frnd() - 0.5) * bx;
		z1 = (frnd() - 0.5) * bz;

		RotateAroundY(&x1, &z1, fCos, fSin);

		y1 = 1.0 + y + frnd() * 3.0;
		Ship_Serious_Boom(x1 + x, y1, z1 + z);
		CreateParticleSystem("blast", x1 + x, y1, z1 + z, 0.0, 0.0, 0.0, 0);
	
}

void Ship_Turn180(ref rCharacter)
{
	
	
	rCharacter.Tmp.SpeedRecall = 0; 
}


void Ship_Detonate(ref rCharacter, bool bMakeSmallBoom, bool bMakeDead)
{
	if (!CheckAttribute(rCharacter, "Ship.Pos.x")) 
	{
		Trace("Ship_Detonate: Can't find Ship.Pos in character with id: " + rCharacter.id);
		return;
	}
	aref	arCharShip; makearef(arCharShip, rCharacter.Ship);
	
	float x = stf(arCharShip.Pos.x);
	float y = stf(arCharShip.Pos.y);
	float z = stf(arCharShip.Pos.z);

	int iMinBoom = MakeInt(Bring2Range(6.0, 2.0, 1.0, 7.0, stf(GetCharacterShipClass(rCharacter))));

	float bx = arCharShip.BoxSize.x;
	float by = arCharShip.BoxSize.y;
	float bz = arCharShip.BoxSize.z;

	float fCos = cos(stf(arCharShip.Ang.y));
	float fSin = sin(stf(arCharShip.Ang.y));

	bool isBoomAlready = false;
	int iMax = iMinBoom + rand(2); 
	for (int i=0; i<iMax; i++)
	{
		float x1, y1, z1;
		x1 = (frnd() - 0.5) * bx;
		z1 = (frnd() - 0.5) * bz;

		RotateAroundY(&x1, &z1, fCos, fSin);
		
		y1 = 1.0 + y + frnd() * 3.0;
		if(isBoomAlready == false)
		{
			Ship_Serious_Boom(x1 + x, y1, z1 + z);
		}
		isBoomAlready = true;
		CreateParticleSystem("blast_inv", x1 + x, y1, z1 + z, 0.0, 0.0, 0.0, 0);
	}
	if (bMakeDead) { ShipDead(sti(rCharacter.Index), KILL_BY_SPY, -1); }

	if (bMakeSmallBoom) { PostEvent(SHIP_DETONATE_SMALL, 600 + rand(1000), "l", sti(rCharacter.index)); } 
}

float AIShip_isPerksUse(string sPerk, float fOff, float fOn)
{
	if (sti(sPerk)) { return fOn; }
	return fOff;
}


void Ship_UpdateParameters()
{
	int		iCharacterIndex = GetEventData();
	ref		rCharacter = GetCharacter(iCharacterIndex);
	float	fSailState = GetEventData();
	
	bool	bDead = LAi_IsDead(rCharacter);
	
	
	if(sti(rCharacter.ship.type) == SHIP_NOTUSED || bDead)   
	{
		return;
	}
    
	aref	arTmpPerks; makearef(arTmpPerks, rCharacter.TmpPerks);

	
	Ship_UpdateTmpSkills(rCharacter);

	Cannon_RecalculateParameters(sti(rCharacter.index));

	
	aref	arCharShip; makearef(arCharShip, rCharacter.Ship);
	ref		rShip = GetRealShip(sti(arCharShip.Type));

    float fShipSpeed, fShipTurnRate;
    
	
	if (!CheckAttribute(rCharacter, "Tmp.SpeedRecall") || sti(rCharacter.Tmp.SpeedRecall) <= 0)
	{
		fShipSpeed    = FindShipSpeed(rCharacter);
		fShipTurnRate = FindShipTurnRate(rCharacter);
		
		rCharacter.Tmp.SpeedRecall   = 8 + rand(5);
		rCharacter.Tmp.fShipSpeed    = fShipSpeed;
		rCharacter.Tmp.fShipTurnRate = fShipTurnRate;
	}
	else
	{
		fShipSpeed    = stf(rCharacter.Tmp.fShipSpeed);
		fShipTurnRate = stf(rCharacter.Tmp.fShipTurnRate);
		
		rCharacter.Tmp.SpeedRecall   = sti(rCharacter.Tmp.SpeedRecall) - 1;
	}
    
    
	
	float	fWindPower = Whr_GetWindSpeed() / WIND_NORMAL_POWER;	
	float	fWindDotShip = GetDotProduct(Whr_GetWindAngle(), stf(arCharShip.Ang.y));		
	float   fKint = 1.0 + (0.5 - makefloat(sti(RealShips[sti(rCharacter.ship.type)].Class))/6.0) * ((Whr_GetWindSpeed() - 8.0)/10.0);
    
	fShipSpeed = (fShipSpeed * fWindPower * fKint);  
	arCharShip.MaxSpeedZ = fShipSpeed; 
	
	arCharShip.MaxSpeedZ = Sea_ApplyMaxSpeedZ(arCharShip, fWindDotShip, rCharacter); 
	
	
	
	
	
	float fMaxSpeedY = stf(rShip.TurnRate) / Sea_TurnRateMagicNumber(); 

	float fTRFromSailState = 1.0;
	switch (MakeInt(fSailState * 2.0))
	{
		case 0: fTRFromSailState = 0.05; break;
		case 1: fTRFromSailState = 1.0; break;
		case 2: fTRFromSailState = 0.68; break;
	}
	
    float	fTRFromSpeed = 1.0;
    float fCurrentSpeedZ = stf(rCharacter.Ship.Speed.z);
	if (iCharacterIndex == GetMainCharacterIndex())
	{
        if (MOD_SKILL_ENEMY_RATE > 2) 
        {
            if (iArcadeSails == 1)
        	{
               fTRFromSpeed = 1.0 - 0.5 * (1.0 - Clampf(fCurrentSpeedZ / fShipSpeed));
    		}
    		else
    		{
    		    fTRFromSpeed = 1.0 - 0.86 * (1.0 - Clampf(fCurrentSpeedZ / fShipSpeed));
    		}
        }
	}
	else
	{
		if (iArcadeSails == 1)
    	{
           fTRFromSpeed = 1.0 - (0.51 - MOD_SKILL_ENEMY_RATE*0.01) * (1.0 - Clampf(fCurrentSpeedZ / fShipSpeed));
		}
		else
		{
		    fTRFromSpeed = 1.0 - (0.87 - MOD_SKILL_ENEMY_RATE*0.01) * (1.0 - Clampf(fCurrentSpeedZ / fShipSpeed));
		}
	}
	
	float fTRResult = fMaxSpeedY * fShipTurnRate * fTRFromSailState * fTRFromSpeed;
	
	
	
	
	 
	fTRResult = Bring2Range(0.07, 0.95, 0.00001, 1.0, fTRResult);
	arCharShip.MaxSpeedY =	fTRResult;

    
	if (iArcadeSails == 1)
	{
		
		arCharShip.MaxSpeedZ = (2.5 * stf(arCharShip.MaxSpeedZ));
		arCharShip.MaxSpeedY = (2.0 * stf(arCharShip.MaxSpeedY));
	}
	else
	{
		
		arCharShip.MaxSpeedZ = (1.0 * stf(arCharShip.MaxSpeedZ));
	}
	
	
	float	fLoad = Clampf(GetCargoLoad(rCharacter) / stf(rShip.Capacity));
	arCharShip.Immersion = (stf(rShip.SubSeaDependWeight) * fLoad); 

	
	float fBaseSailHP = stf(rShip.SP);
	float fBaseShipHP = stf(rShip.HP);
	float fCurHP = stf(arCharShip.HP);
	if(fBaseShipHP < fCurHP)
	{
		fBaseShipHP = fCurHP;
	}
	if (bSeaActive && (fCurHP / fBaseShipHP < 0.09999))
	{
        float fLightRepair = AIShip_isPerksUse(arTmpPerks.LightRepair, 1.0, 0.0);
        
        if (CheckAttribute(rCharacter, "SinkTenPercent") && !sti(rCharacter.SinkTenPercent)) { fLightRepair = 0.0; }
		float fSinkDamage = fLightRepair * (fBaseShipHP / 100.0) * 0.08;
		if (CheckAttribute(rCharacter, "Ship.LastBallCharacter")) 
		{ 
			Ship_ApplyHullHitpoints(rCharacter, fSinkDamage, KILL_BY_BALL, sti(rCharacter.Ship.LastBallCharacter));
		}
		else
		{
			Ship_ApplyHullHitpoints(rCharacter, fSinkDamage, KILL_BY_TOUCH, -1);
		}
		 
		if (iCharacterIndex == nMainCharacterIndex) 
		{ 
            
			if(!IsPerkIntoList("sink"))
� � � � 	{
				if (rand(1) == 0)
				{
					PlaySound("Interface\_Abandon1.wav");
				}
				else
				{
					PlaySound("Interface\_Abandon2.wav");
				}
			}
			
			AddPerkToActiveList("sink"); 
		}
	}
	else
	{
		if (iCharacterIndex == nMainCharacterIndex) { DelPerkFromActiveList("sink"); }
	}

	float fStormProfessional = AIShip_isPerksUse(arTmpPerks.StormProfessional, 1.0, 0.7);

    
    if (CheckAttribute(rCharacter, "DontHitInStorm"))
    {
		fStormProfessional = 0;
	}
	
	
	if (bStorm && bSeaActive)
	{
		float fWindAttack = 1.0 - abs(fWindDotShip);
		
		float fDamageMultiply = fStormProfessional * Bring2Range(0.25, 1.0, 0.0, 1.0, fWindAttack) * isEquippedArtefactUse(rCharacter, "talisman2", 1.0, 0.2);

		
		float fDamageHP = (fBaseShipHP / 100.0) * 1.1;
		Ship_ApplyHullHitpoints(rCharacter, fDamageMultiply * fDamageHP, KILL_BY_TOUCH, -1);

		
		switch (MakeInt(fSailState * 2.0))
		{
			case 0: MakeSailDmg(iCharacterIndex, fDamageMultiply * (fBaseSailHP / 100.0) * 0.15); break;
			case 1: MakeSailDmg(iCharacterIndex, fDamageMultiply * (fBaseSailHP / 100.0) * 0.55); break;
			case 2: MakeSailDmg(iCharacterIndex, fDamageMultiply * (fBaseSailHP / 100.0) * 1.1); break;
		}

		
		float fExp = (1.0 - fWindAttack) * fDamageHP / (8 - GetCharacterShipClass(rCharacter)); 
		fExp = fExp / 10;
  		if (!bDead)
        {
            Ship_AddCharacterExp(rCharacter, MakeInt(fExp));
			
            if (IsCompanion(rCharacter))
            {
               AddCharacterExpToSkill(rCharacter, "Sailing", fExp);
               ChangeCrewExp(rCharacter, "Sailors", 0.5);
            }
            
        }

		
  		float fRotate = stf(rCharacter.Ship.Tornado.Rotate.y) + (frnd() * 0.08 - 0.04);  
		if (fRotate > 0.01)
		{
			fRotate = 0.01;
		}
		if (fRotate < -0.01)
		{
			fRotate = -0.01;
		}

		rCharacter.Ship.Tornado.Rotate.y = fRotate;  
		arCharShip.Impulse.Rotate.y = fRotate;
	}

	if (bTornado && bSeaActive)
	{
		float fTornadoDistance = GetDistance2D(stf(Tornado.x), stf(Tornado.z), stf(arCharShip.Pos.x), stf(arCharShip.Pos.z));
		float fTornadoDamageMultiply = fStormProfessional * Bring2Range(1.0, 0.0, 0.0, 100.0, fTornadoDistance) * isEquippedArtefactUse(rCharacter, "talisman2", 1.0, 0.2);

		
		Ship_ApplyHullHitpoints(rCharacter, fTornadoDamageMultiply * (fBaseShipHP / 100.0) * 8.5, KILL_BY_TOUCH, -1);

		
		switch (MakeInt(fSailState * 2.0))
		{
			case 0: 
				MakeSailDmg(iCharacterIndex, fTornadoDamageMultiply * (fBaseSailHP / 100.0) * 1.5);
			break;
			case 1: 
				MakeSailDmg(iCharacterIndex, fTornadoDamageMultiply * (fBaseSailHP / 100.0) * 4.5); 
			break;
			case 2: 
				MakeSailDmg(iCharacterIndex, fTornadoDamageMultiply * (fBaseSailHP / 100.0) * 8.5); 
			break;
		}
	}
	
	
	if (iCharacterIndex == nMainCharacterIndex && bSeaActive)
	{
		fSeaExpTimer = fSeaExpTimer + 1.0;
		if (fSeaExpTimer >= 15.0 && bStorm)
		{
			if (!bDead)
			{ 
				
			}

			fSeaExpTimer = 0.0;
			fSeaExp = 0.0;
		}
	}

	
	if (CheckAttribute(rCharacter, "Ship.Cargo.RecalculateCargoLoad") && sti(rCharacter.Ship.Cargo.RecalculateCargoLoad))
	{
		if (rand(5) == 1)  
		{
			RecalculateCargoLoad(rCharacter);
			rCharacter.Ship.Cargo.RecalculateCargoLoad = 0;
		}
	}
    
	if (bSeaLoaded && CheckAttribute(rCharacter, "SeaAI.Task.Target"))
	{
		if(sti(rCharacter.SeaAI.Task.Target) > 0)
		{
			ref rTargetCharacter = GetCharacter(sti(rCharacter.SeaAI.Task.Target));
			bool bSkipTarget = false;
			if(!CheckAttribute(rTargetCharacter, "location"))
			{
				bSkipTarget = true;
			}
			if(rTargetCharacter.location == "none")
			{
				bSkipTarget = true;
			}
			if(rTargetCharacter.location != rCharacter.location)
			{
				bSkipTarget = true;
			}
			if (!bSkipTarget)
			{
				float fDistance = Ship_GetDistance2D(rCharacter, rTargetCharacter);
				float fEnemyLeadership = stf(rTargetCharacter.TmpSkill.Leadership); 
				float fEnemyFencing = stf(rTargetCharacter.TmpSkill.Fencing); 
				float fEnemyCrewFencing = (0.1 + fEnemyLeadership + fEnemyFencing * stf(rCharacter.Ship.Crew.Quantity));
				float fOurLeadership = stf(rCharacter.TmpSkill.Leadership); 
				float fOurFencing = stf(rCharacter.TmpSkill.Fencing);
				float fOurCrewFencing = (0.1 + fOurLeadership + fOurFencing * stf(rTargetCharacter.Ship.Crew.Quantity));
				float fRatio = fEnemyCrewFencing / fOurCrewFencing;
				if (sti(rCharacter.nation) == PIRATE) 
				{ 
					fRatio = fRatio * 1.6; 
				}
				if (sti(rCharacter.rank) > sti(rTargetCharacter.rank)) 
				{ 
					fRatio = fRatio * 1.2; 
				}
				
				if (fRatio > 1.2 && CheckAttribute(rCharacter, "Tmp.fShipSpeed") && CheckAttribute(rTargetCharacter, "Tmp.fShipSpeed") && stf(rCharacter.Tmp.fShipSpeed) > (stf(rTargetCharacter.Tmp.fShipSpeed) / 1.5))
				{
					
					if(GetRelation(sti(rCharacter.index), sti(rTargetCharacter.index)) == RELATION_ENEMY)
					{
						Ship_SetTaskAbordage(SECONDARY_TASK, sti(rCharacter.index), sti(rTargetCharacter.index)); 
						rCharacter.Ship_SetTaskAbordage = true; 
					}
				}
				else
				{
					DeleteAttribute(rCharacter, "Ship_SetTaskAbordage");
				}

				if (sti(rCharacter.SeaAI.Task) == AITASK_RUNAWAY)
				{
					 
					
					Ship_SetSailState(sti(rCharacter.index), 1);  
					if (sti(rCharacter.Ship.Lights) == 1)
					{
						Ship_SetLightsOff(rCharacter, 15.0, true, true, false);
					}
					if (sti(rCharacter.Ship.SP) > 50 && rand(100) > 80)  
					{
						PostEvent(SHIP_DROP_GOOD, 1000, "a", rCharacter);
					}
					
					if (sti(rCharacter.Ship.SP) < 60 && GetCargoGoods(rCharacter, GOOD_POWDER) >= MINE_POWDER*2 && rand(39) == 5)
					{
						SetMineFree(rCharacter, 1); 
					}
					
					
				}
		        else
		        {
					if (sti(rCharacter.SeaAI.Task) == AITASK_ABORDAGE)
					{
						if (GetRelation(sti(rCharacter.index), sti(rTargetCharacter.index)) == RELATION_ENEMY)
						{
							if(LAi_IsDead(rCharacter) == false && LAi_IsDead(rTargetCharacter) == false)
							{
								if (sti(rTargetCharacter.index) == nMainCharacterIndex)
								{
									float fCharacterGrappling = stf(rCharacter.TmpSkill.Grappling);
									float fCharacterGrapplingPerk  = Ship_CalcGrapplingPerk(rCharacter);
									float fCharacterDistance = Ship_CalcMaxAbordageDistance(fCharacterGrappling, fCharacterGrapplingPerk);
									float fCharacterAngle = Ship_CalcMaxAbordageAngle(fCharacterGrappling);
									float fCharacterSpeed = Ship_CalcMaxAbordageSpeed(fCharacterGrappling);
		
									float fAng = 0.0;
									float fRelativeSpeed = stf(arCharShip.Speed.z);
		
									aref	arUpdate;
									makearef(arUpdate, rCharacter.SeaAI.Update);
									aref aShips;
									makearef(aShips, arUpdate.Ships);
									int iShipsNum = GetAttributesNum(aShips);
									for (int i=0; i<iShipsNum; i++)
									{
										aref aShip = GetAttributeN(aShips, i);
										ref rShipCharacter = GetCharacter(sti(aShip.idx)); 
										if(rShipCharacter.id == rTargetCharacter.id)
										{
											fRelativeSpeed = stf(aShip.RelativeSpeed);
											fAng = stf(aShip.d_ay);
										}
									}
									float fEnemyBoxSizeX = stf(rTargetCharacter.Ship.BoxSize.x) / 2.0;
									float fCharacterBoxSizeX = stf(rCharacter.Ship.BoxSize.x) / 2.0;
									float fAbordageDistance = fDistance - fEnemyBoxSizeX - fCharacterBoxSizeX;
							
									if (fAbordageDistance < fCharacterDistance && fAng < fCharacterAngle && fRelativeSpeed < fCharacterSpeed)
									{
										  
										
										
										if (fRatio > 1.2)
										{
											iAbordageShipEnemyCharacter = sti(rCharacter.index);
											Sea_AbordageLoad(SHIP_ABORDAGE, false);
										}
										else
										{
											if (stf(rCharacter.ship.hp) > (stf(rTargetCharacter.ship.hp) / 2) || GetCrewQuantity(rCharacter) > GetCrewQuantity(rTargetCharacter)) 
											{
												Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rTargetCharacter.index));   
											}
											else
											{
												Ship_SetTaskRunaway(SECONDARY_TASK,sti(rCharacter.index), sti(rCharacter.SeaAI.Task.Target));  
											}
										}
										
									}
								} 
							}
						}
					}
				} 
			}
		}
	}
	
	
	if (rand(40) <= fSailState * 5.0) { Ship_PlaySound3DComplex(rCharacter, "sails_ambient", fSailState * 0.5, 0.0, 0.0, 0.5 + frnd() * 0.0); }

	
	if (rand(2) == 1) { Ship_PlaySound3DComplex(rCharacter, "squeak_sea"+sSeaSoundPostfix, 0.9, frnd() * 1.2 - 0.6, 0.0, frnd() * 1.6 - 0.8); }
}

void Ship_SailsMoveSound()
{
	aref arCharacter = GetEventData();
	bool bMove = GetEventData();

	
	if (CheckAttribute(arCharacter, "Ship.Sounds") && sti(arCharacter.Ship.Sounds.SailsID) > 0) 
		{ Sound_SetVolume(sti(arCharacter.Ship.Sounds.SailsID), 0.75 * bMove); }
}

void Ship_PrintExp(int iExp)
{
	if (iExp <= 0) { return; }

	object oRes;
	string sExpQuantity = iExp;
	string sExpString = LanguageConvertString(iSeaSectionLang, "sea_exp_add");

	Event(PARSE_STRING, "asls", &oRes, sExpString, 1, sExpQuantity);

	Log_SetStringToLog(oRes.Str);
}

void Ship_TornadoDamage()
{
	float fTime = GetEventData();
	
	Tornado.x = GetEventData();
	Tornado.z = GetEventData();
}

void Ship_UpdateTmpSkills(ref rCharacter)
{
	
	if (!CheckAttribute(rCharacter, "TmpSkillRecall") || sti(rCharacter.TmpSkillRecall) <= 0)
    {
        rCharacter.TmpSkill = "";

    	aref aTmpSkill; makearef(aTmpSkill, rCharacter.TmpSkill);

    	
    	
    	aTmpSkill.Leadership = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_LEADERSHIP)) / SKILL_MAX;
    	aTmpSkill.Sneak     = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_SNEAK)) / SKILL_MAX;
    	aTmpSkill.Defence   = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_DEFENCE)) / SKILL_MAX;
    	aTmpSkill.Grappling = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_GRAPPLING)) / SKILL_MAX;
    	aTmpSkill.Sailing   = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_SAILING)) / SKILL_MAX;
    	aTmpSkill.Repair    = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_REPAIR)) / SKILL_MAX;
    	aTmpSkill.Fencing   = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_FENCING)) / SKILL_MAX;
    	aTmpSkill.Accuracy  = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_ACCURACY)) / SKILL_MAX;
    	aTmpSkill.Cannons   = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_CANNONS)) / SKILL_MAX;

        if (sti(rCharacter.index) == GetMainCharacterIndex())
        {
            if (SeaCameras.Camera == "SeaDeckCamera")
        	{
        		aTmpSkill.Accuracy = Clampf(stf(aTmpSkill.Accuracy) + 0.15); 
        	}
        	
        	if (rand(10) == 3)
        	{
        	    DoQuestCheckDelay("NationUpdate", 1.0);
        	}
    	}
    	rCharacter.TmpSkillRecall = 25 + rand(49); 
    	
		if (GetNpcQuestPastTimeParam(rCharacter, "Add2SeaTime") > 55) 
		{
		    if (CheckAttribute(rCharacter, "SeaAI.Task") && rCharacter.SeaAI.Task != AITASK_RUNAWAY) 
	        {
	        	Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(pchar.index));
	        }
		}
	}
	else
	{
        rCharacter.TmpSkillRecall = sti(rCharacter.TmpSkillRecall) - 1;

        if (sti(rCharacter.index) == GetMainCharacterIndex())
    	{
            rCharacter.TmpSkill.Accuracy  = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_ACCURACY)) / SKILL_MAX;
            if (SeaCameras.Camera == "SeaDeckCamera")
            {
                rCharacter.TmpSkill.Accuracy = Clampf(stf(rCharacter.TmpSkill.Accuracy) + 0.15);
            }
    	}
	}
}

void Ship_UpdatePerks()
{
	int iCharacterIndex = GetEventData();
	ref rCharacter = GetCharacter(iCharacterIndex);

	
	if (sti(rCharacter.ship.type) == SHIP_NOTUSED) return; 
	rCharacter.TmpPerks = "";
	aref aTmpPerks; makearef(aTmpPerks, rCharacter.TmpPerks);

	
	
      
	aTmpPerks.StormProfessional	  	    = CheckOfficersPerk(rCharacter, "StormProfessional");
    aTmpPerks.FastReload				= CheckOfficersPerk(rCharacter, "FastReload");
	aTmpPerks.ImmediateReload			= CheckOfficersPerk(rCharacter, "ImmediateReload");
	aTmpPerks.HullDamageUp			 	= CheckOfficersPerk(rCharacter, "HullDamageUp");
	aTmpPerks.CrewDamageUp				= CheckOfficersPerk(rCharacter, "CrewDamageUp");
	aTmpPerks.CriticalShoot				= CheckOfficersPerk(rCharacter, "CriticalShoot");
	aTmpPerks.LongRangeShoot			= CheckOfficersPerk(rCharacter, "LongRangeShoot");
	aTmpPerks.CannonProfessional		= CheckOfficersPerk(rCharacter, "CannonProfessional");
	aTmpPerks.LongRangeGrappling		= CheckOfficersPerk(rCharacter, "LongRangeGrappling");
	aTmpPerks.GrapplingProfessional		= CheckOfficersPerk(rCharacter, "GrapplingProfessional");
	aTmpPerks.BasicBattleState			= CheckOfficersPerk(rCharacter, "BasicBattleState");
	aTmpPerks.AdvancedBattleState		= CheckOfficersPerk(rCharacter, "AdvancedBattleState");
	aTmpPerks.ShipDefenseProfessional	= CheckOfficersPerk(rCharacter, "ShipDefenseProfessional");
	aTmpPerks.ShipSpeedUp				= CheckOfficersPerk(rCharacter, "ShipSpeedUp");
	aTmpPerks.ShipTurnRateUp			= CheckOfficersPerk(rCharacter, "ShipTurnRateUp");
	aTmpPerks.SailingProfessional		= CheckOfficersPerk(rCharacter, "SailingProfessional");
	aTmpPerks.LightRepair				= CheckOfficersPerk(rCharacter, "LightRepair");
	
	if (iCharacterIndex != nMainCharacterIndex && IsCompanion(rCharacter))
	{
		Event("eSwitchPerks", "l", nMainCharacterIndex);
	}
}

void Ship_Lightning()
{
	if (!bSeaActive) { return; }

	float x = GetEventData();
	float y = GetEventData();
	float z = GetEventData();

	for (int i=0; i<iNumShips; i++)
	{
		ref rCharacter = GetCharacter(Ships[i]);
		aref arShipChar; makearef(arShipChar, rCharacter.Ship);

		float sx = stf(arShipChar.Pos.x);
		float sy = stf(arShipChar.Pos.y);
		float sz = stf(arShipChar.Pos.z);
		float bx = stf(arShipChar.BoxSize.x);
		float by = stf(arShipChar.BoxSize.y);
		float bz = stf(arShipChar.BoxSize.z);
		float fDist = GetDistance2D(x, z, sx, sz);
		float fMinLightningDist = 20.0 + bz / 1.5;
		if (fDist < fMinLightningDist)
		{
			int iMinBoom = MakeInt(Bring2Range(5.0, 2.0, 1.0, 7.0, stf(GetCharacterShipClass(rCharacter))));
			float fCos = cos(stf(arShipChar.Ang.y));
			float fSin = sin(stf(arShipChar.Ang.y));
			int iMax = iMinBoom + rand(2);
			for (int k=0; k<iMax; k++)
			{
				float dx = 0.6 * bx * (frnd() - 0.5);
				float dz = 0.7 * bz * (frnd() - 0.5);
				RotateAroundY(&dx, &dz, fCos, fSin);
				Ship_Serious_Boom(sx + dx, sy + 0.1 * by * frnd(), sz + dz);
			}

			Ship_ApplyHullHitpoints(rCharacter, iMinBoom * 40.0, KILL_BY_TOUCH, -1);
			Ship_ApplyCrewHitpoints(rCharacter, MakeFloat(rand(3)));

			int iNumFirePlaces = 0;
			SendMessage(rCharacter, "le", MSG_SHIP_GET_NUM_FIRE_PLACES, &iNumFirePlaces);
			
			float fFirePlaces = Bring2Range(1.0, 0.1, 0.0, fMinLightningDist, fDist);

			float fCurr = 0.0;
			float fTest = (1.0 - fFirePlaces) * iNumFirePlaces;
			for (int j=0; j<iNumFirePlaces; j++)
			{
				fCurr = fCurr + 1.0;
				if (fCurr < fTest) { continue; }
	
				fCurr = 0.0;
				int iRandStartTime = rand(10000);
				float fTotalFireTime = Ship_GetTotalFireTime(rCharacter);

				PostEvent(SHIP_ACTIVATE_FIRE_PLACE, iRandStartTime, "ialsfl", rCharacter, rCharacter, j, "ship_onfire", fTotalFireTime, -1);
				PostEvent(SHIP_FIRE_DAMAGE, iRandStartTime, "lllf", Ships[i], -1, j, fTotalFireTime);
			}
		}
	}
}


void Ship_CreateForCharacter(ref rCharacter, int iShipType, string sShipName)
{
	DeleteAttribute(rCharacter, "Ship");

	rCharacter.Ship.Type = iShipType;
	rCharacter.Ship.Name = sShipName;

	rCharacter.Ship.Cannons.Borts = "";
	rCharacter.Ship.Cannons.Charge.Type = GOOD_BOMBS;
	rCharacter.Ship.Ang.y = 0.0;
	rCharacter.Ship.Pos.x = 0.0;
	rCharacter.Ship.Pos.y = 0.0;
	rCharacter.Ship.Pos.z = 0.0;
	rCharacter.Ship.Speed.z = 0.0;

	SetBaseShipData(rCharacter);
}

void Ship_ClearImpulseStrength(ref rCharacter)
{
	aref arImpulse; makearef(arImpulse, rCharacter.Ship.Impulse);
	arImpulse.Rotate.x = 0.0;
	arImpulse.Rotate.y = 0.0;
	arImpulse.Rotate.z = 0.0;
	arImpulse.Speed.x = 0.0;
	arImpulse.Speed.y = 0.0;
	arImpulse.Speed.z = 0.0;

	rCharacter.Ship.Tornado.Rotate.y = 0.0;  
}

void Ship_PrepareShipForLocation(ref rCharacter)
{
	Ship_ClearImpulseStrength(rCharacter);
}

void Ship_LoadShip()
{
	int iCharacterIndex = GetEventData();
	
	ref rCharacter = GetCharacter(iCharacterIndex);
	
	

	
	if (sti(rCharacter.ship.type) != SHIP_NOTUSED)
	{
		Event("eSwitchPerks", "l", iCharacterIndex);
		Ships[iNumShips] = iCharacterIndex;
		Event(SHIP_UPDATE_PARAMETERS, "lf", iCharacterIndex, stf(rCharacter.Ship.Speed.z));		
		iNumShips++;
	}
}

void Ship_LoadShipActivateFirePlace()
{
	int iOurCharacterIndex = GetEventData();
	int iBallCharacterIndex = GetEventData();
	int iFirePlaceIndex = GetEventData();
	float fTotalFireTime = GetEventData();

	Dev_Trace("iBallCharacterIndex = " + iBallCharacterIndex);
	int iStartTime = 500;

	PostEvent(SHIP_FIRE_DAMAGE, iStartTime, "lllf", iOurCharacterIndex, iBallCharacterIndex, iFirePlaceIndex, fTotalFireTime);
}

void SetTextureForShip(aref refBaseShip, aref rCharacter)
{
	if(!CheckAttribute(refBaseShip, "name"))
	{
		trace("SetTextureForShip(): ship " + refBaseShip.basetype + " have no name! NPCid = "+ rCharacter.id);
		if (MOD_BETTATESTMODE == "On") Log_Info("SetTextureForShip(): ship " + refBaseShip.basetype + " have no name! NPCid = "+ rCharacter.id);
		return;
	}

	string sPath = "ships\" + refBaseShip.name + "\";
	
	if(CheckAttribute(refBaseShip, "ship.Upgrades.hull"))  
	{
		sPath = sPath + "hull" + refBaseShip.ship.upgrades.hull + "\";
	}
	
	SetTexturePath(0, sPath);
}

void DropGoodsToSea()
{
	aref rCharacter = GetEventData();

	ref rGood;
	string sGood;

	for (int i=GOOD_BALLS; i<GOOD_CULVERINE_36; i++)
	{
		sGood = Goods[i].name;
		if (CheckAttribute(&Goods[i], "DontDrop")) continue;

		if(CheckAttribute(rCharacter, "Ship.Cargo.Goods."+sGood))
		{
			int	iQuantity = sti(rCharacter.Ship.Cargo.Goods.(sGood));
			
			if(CheckAttribute(rCharacter, "Ship.Cargo.Goods."+sGood+".Lock")) continue; 
			
			if (iQuantity < 1 && rand(1) == 1) continue; 
			iQuantity = makeint(iQuantity/2 + rand(makeint(iQuantity/3)));   
			
			if (iQuantity < 1) continue; 
			
			RemoveCharacterGoods(rCharacter, i, iQuantity);

			iQuantity = iQuantity / sti(Goods[i].Units);

			if (iQuantity <= 1) 
			{ 
				continue; 
			}

			rCharacter.Ship.Cargo.Goods.(sGood) = 0;
            rCharacter.Ship.Cargo.RecalculateCargoLoad = true; 
			
            rCharacter.Tmp.SpeedRecall = 0; 
            
			if (CheckAttribute(&Goods[i], "Swim")) 
			{ 
				int iSwimQuantity = makeint(iQuantity/3 + rand(makeint(iQuantity/3)) + rand(makeint(iQuantity/3)));

				if(iSwimQuantity < 1)
				{
					iSwimQuantity = 1;
				}
				float fTime = stf(Goods[i].Swim.Time);
				string sModel = Goods[i].Swim.Model;

				

				fTime = fTime + (frnd() - 0.5) * fTime / 2.0;

				AISeaGoods_AddGood(rCharacter, sGood, sModel, fTime * 60.0, iSwimQuantity);
			}
			return;
		}
	}
}

int Ship_GetRunAwayPoint()
{
	aref arChar = GetEventData();
	float fX = GetEventData();
	float fZ = GetEventData();

	float fRadius = 10000.0;
	float fWindAngle = Whr_GetWindAngle();

	arChar.SeaAI.WindAngle = fWindAngle;
	arChar.SeaAI.RunAwayPnt.x = stf(arChar.Ship.Pos.x) + fRadius * sin(fWindAngle);
	arChar.SeaAI.RunAwayPnt.z = stf(arChar.Ship.Pos.z) + fRadius * cos(fWindAngle);

	return 0;
}


string GetShipSexWord(string _type, string _man, string _woman)
{
    if (_type == "WarTartane" || 
	    _type == "Schooner"   || 
		_type == "Schooner_W" ||
		_type == "Caravel"    || 
		_type == "Shnyava"    || 
		_type == "Caracca"    || 
		_type == "Brigantine" ||
		_type == "XebekVML")
    {
        return _woman;
    }
    else
    {
        return _man;
    }
}

void Ship_ResearchCannons(ref aCharacter)
{
	if (bSeaLoaded)
	{
		SendMessage(&AISea, "la", AI_MESSAGE_RESEARCH_CANNONS, aCharacter);
		RefreshBattleInterface();
		Ship_ChangeCharge(aCharacter, sti(aCharacter.Ship.Cannons.Charge.Type));
	}
}

void Ship_FlagRefresh(ref rCharacter)
{
    if (bSeaLoaded)
	{
		SendMessage(rCharacter, "l", MSG_SHIP_FLAG_REFRESH);
	}
}

void EmptyFantom_DropGoodsToSea(ref rChar, int iFantomType)
{
	float fTime;
	string sGood, sModel;
	int iQty;
	if(iFantomType == ENCOUNTER_TYPE_BARREL)
	{	
		int irand = drand(100);
		if(irand > 92) 
		{
			AISeaGoods_AddGood_Special(rChar, "powder1", "barrel_treasure", 1500.0, 1); 
		}
		else
		{
			if(irand < 40) 
			{
				for (int i=GOOD_FOOD; i<=GOOD_OIL; i++)
				{
					sGood = Goods[i].name;
					if (rand(3) > 1) continue; 
					if (CheckAttribute(&Goods[i], "Swim")) 
					{
						iQty = rand(15) + rand(10) + 5; 
						fTime = stf(Goods[i].Swim.Time);
						sModel = Goods[i].Swim.Model;
						fTime = fTime + (frnd() - 0.5) * fTime / 2.0;

						AISeaGoods_AddGood_Special(rChar, sGood, sModel, fTime * 60.0, iQty);
					}	
				}
			}		
			AISeaGoods_AddGood_Special(rChar, "barrel_treasure", "barrel_treasure", 1500.0, 1);			
		}	
	}
	if(iFantomType == ENCOUNTER_TYPE_BOAT)
	{
		AISeaGoods_AddGood_Special(rChar, "unknown_boat", "lo_boat", 1500.0, 1);
	}
	SendMessage(&AISea, "la", AI_MESSAGE_CHARACTER_DEAD, rChar);
}




