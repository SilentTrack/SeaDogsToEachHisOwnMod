#include "sail_msg.h"

#define		MAX_FORTS						16
#define		MIN_CANNON_DAMAGE_DISTANCE		20.0

object		AIFort;
object		Forts[MAX_FORTS];
object		FortsBlots[MAX_FORTS];
int			iNumForts = 0;
int iNumDamagedCannonsQuantity = 0;

void DeleteFortEnvironment()
{
    
	DelEventHandler(FORT_CANNON_DAMAGE, "Fort_CannonDamage");
	DelEventHandler(FORT_CREATE, "Fort_CreateEvent");
	DelEventHandler(FORT_LOADDMGCANNON, "Fort_LoadDamagedCannon");
	
	if (isEntity(&AIFort)) { DeleteClass(&AIFort); }
	for (int i=0; i<iNumForts; i++)
	{
		DeleteClass(&Forts[i]);
		DeleteClass(&FortsBlots[i]);
	}
	iNumForts = 0;
	for(i = 0; i < MAX_FORTS; i++) { Forts[i].fortcmdridx = -1; }
}

void CreateFortEnvironment()
{
	iNumForts = 0;
	for(int i = 0; i < MAX_FORTS; i++) { Forts[i].fortcmdridx = -1; }
	SetEventHandler(FORT_CANNON_DAMAGE, "Fort_CannonDamage", 0);
	SetEventHandler(FORT_CREATE, "Fort_CreateEvent", 0);
	SetEventHandler(FORT_LOADDMGCANNON, "Fort_LoadDamagedCannon", 0);
}

int Fort_FindCharacter(string sLocationID, string sLocationGroup, string sLocationLocator)
{
	for (int i=0; i<MAX_CHARACTERS; i++)
	{
		if (Characters[i].location == sLocationID) 
		{
			if (Characters[i].location.group == sLocationGroup) 
			{
				if (Characters[i].location.locator == sLocationLocator) 
				{
					return i;
				}
			}
		}
	}
	return -1;
}

int Fort_GetDeadDays(ref rCharacter)
{
	int		iDYear = sti(rCharacter.Fort.DieTime.Year);
	int		iDMonth = sti(rCharacter.Fort.DieTime.Month);
	int		iDDay = sti(rCharacter.Fort.DieTime.Day);
	float	fTime = stf(rCharacter.Fort.DieTime.Time);
	
	return GetPastTime("day", iDYear, iDMonth, iDDay, fTime, GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
}

void Fort_Login(int iIslandIndex)
{
	
	ref rIsland = GetIslandByIndex(iIslandIndex);
	aref arReload; makearef(arReload,rIsland.reload);
	int iNumReloads = GetAttributesNum(arReload);
	for (int i=0; i<iNumReloads; i++)
	{
		aref arLocator = GetAttributeN(arReload,i);
		ReloadProgressUpdate();
		if (CheckAttribute(arLocator,"fort"))
		{
			if (!CheckAttribute(arLocator,"fort.model") || arLocator.fort.model == "")
			{
				Trace("Island.id = " + rIsland.id + ", and reload." + GetAttributeName(arLocator) + ", doesn't have fort.model value.");
				continue;
			}
			CreateEntity(&Forts[iNumForts], "MODELR");
			string sFortModel = rIsland.filespath.models + "\" + arLocator.fort.model;
			
			
			
			SendMessage(&Forts[iNumForts], "ls", MSG_MODEL_SET_LIGHT_PATH, GetLightingPath());
			SendMessage(&Forts[iNumForts], "ls", MSG_MODEL_LOAD_GEO, sFortModel);
			SendMessage(&Island, "li", MSG_ISLAND_ADD_FORT,  &Forts[iNumForts]);
			
			LayerAddObject("fort_cannon_trace", &Forts[iNumForts], 1);
			LayerAddObject("sun_trace", &Forts[iNumForts], 1);
			SendMessage(SeaLighter, "ssi", "AddModel", arLocator.fort.model, &Forts[iNumForts]);
			iNumForts++;

			int iFortCharacter = Fort_FindCharacter(rIsland.id, "reload", arLocator.name);
			string sColonyName = arLocator.colonyname;
			int iColony = FindColony(sColonyName);

			if(iColony < 0)
			{
				trace("we have problem with indetify fort colony");
				continue;
			}
			if (iFortCharacter < 0)
			{
				Trace("FortLogin: Can't find character for fort: '" + arLocator.name + "', on island with id: '" + rIsland.id + "'");
				continue;
			}
			Forts[iNumForts - 1].fortcmdridx = iFortCharacter;
			if(colonies[iColony].nation != characters[iFortCharacter].nation)
			{
				trace("Colony " + colonies[iColony].id + " have wrong nation field.");
				continue;
			}
			if (isEntity(&AIFort) == 0)
			{
				CreateEntity(&AIFort, "AIFort");
				LayerAddObject(SEA_EXECUTE, &AIFort, 2);
				LayerAddObject(SEA_REALIZE, &AIFort, 10001);
				
			}
			
			ref rCharacter = GetCharacter(iFortCharacter);
			int iNation = sti(rCharacter.nation);
			 

            
			if (sti(rCharacter.nation) != PIRATE)
			{
                DelCharacterRelation(iFortCharacter);
            }
            
            DeleteAttribute(rCharacter, "CheckFlagYet"); 
    		rCharacter.TmpSkillRecall = "0"; 
			int iFortMode = FORT_NORMAL;
			if (CheckAttribute(rCharacter, "Fort.Mode"))
			{
				iFortMode = sti(rCharacter.Fort.Mode);
			}

			bool	bFortRessurect = false;
			int		iDeadDays = 0;
			switch (iFortMode)
			{
				case FORT_NORMAL:
				   
				   SetSeaFantomParam(rCharacter, "war"); 
				   			   
				   
				break;
				case FORT_ABORDAGE:
					iDeadDays = Fort_GetDeadDays(rCharacter);
					if (iDeadDays >= 6) { bFortRessurect = true; }
				break;
				case FORT_DEAD:
					iDeadDays = Fort_GetDeadDays(rCharacter);
					if (iDeadDays >= 8) { bFortRessurect = true; }
					DeleteAttribute(rCharacter, "PotOfGold"); 
					DeleteAttribute(rCharacter, "PotOfSilver");
				break;
			}

			if (iFortMode == FORT_DEAD && iDeadDays > 0)
			{ 
				rCharacter.Ship.Crew.Quantity = iDeadDays * 100 + rand(100);
			}

			if (bFortRessurect) 
			{
				SetFortCharacterCaptured(rCharacter, false);
				iFortMode = FORT_NORMAL;
				rCharacter.Ship.Crew.Quantity = 900 + rand(600);
			}

			rCharacter.Fort.Mode = iFortMode;
			rCharacter.Fort.PlayerDamage = 0.0;								

			Event("eSwitchPerks", "l", iFortCharacter);							
			Ship_UpdateTmpSkills(rCharacter);

			Fort_CheckAttributes(rCharacter);

			AIFort.MinCannonDamageDistance = MIN_CANNON_DAMAGE_DISTANCE;		
			rCharacter.Ship.Crew.MinRatio = 1.0;
			rCharacter.Ship.Name = XI_ConvertString(arLocator.fortname);
			
			
			rCharacter.Ship.Crew.Morale = 70;
	        if (iFortMode == FORT_NORMAL)
			{
			    SetCharacterGoods(rCharacter, GOOD_BOMBS,  300000 + rand(200));
			    SetCharacterGoods(rCharacter, GOOD_POWDER, 300000 + rand(200));
			}
			else
			{
			    SetCharacterGoods(rCharacter, GOOD_BOMBS,  100 + rand(200));
			    SetCharacterGoods(rCharacter, GOOD_POWDER, 100 + rand(200));
			}
			SetCharacterGoods(rCharacter, GOOD_BALLS,  2000  + rand(200));

			SetCharacterGoods(rCharacter, GOOD_FOOD,   200 + rand(550));
			SetCharacterGoods(rCharacter, GOOD_WEAPON, 100 + rand(500));
			SetCharacterGoods(rCharacter, GOOD_BRICK,  130  + rand(900));
			SetCharacterGoods(rCharacter, GOOD_SAILCLOTH, 10 + rand(450));
			SetCharacterGoods(rCharacter, GOOD_PLANKS,   20 + rand(750));
			SetCharacterGoods(rCharacter, GOOD_RUM,   5 + rand(150));

			
			SetCharacterGoods(rCharacter, GOOD_GOLD,   rand(25));
			SetCharacterGoods(rCharacter, GOOD_SILVER,   rand(50));

			
            if (CheckAttribute(rCharacter, "PotOfGoldMonth"))
            {
                if (rCharacter.PotOfGoldMonth == environment.date.month)
                {
                    if (CheckAttribute(rCharacter, "PotOfGold"))
                    {
                        SetCharacterGoods(rCharacter, GOOD_GOLD,   650 + rand(2300));
                    }
                }
                else
                {
                    DeleteAttribute(rCharacter, "PotOfGoldMonth");
                    DeleteAttribute(rCharacter, "PotOfGold");
                }
            }
            if (CheckAttribute(rCharacter, "PotOfSilverMonth"))
            {
                if (rCharacter.PotOfSilverMonth == environment.date.month)
                {
                    if (CheckAttribute(rCharacter, "PotOfSilver"))
                    {
                        SetCharacterGoods(rCharacter, GOOD_SILVER,   960 + rand(4300));
                    }
                }
                else
                {
                    DeleteAttribute(rCharacter, "PotOfSilverMonth");
                    DeleteAttribute(rCharacter, "PotOfSilver");
                }
            }
	        
			
			CreateEntity(&FortsBlots[iNumForts - 1], "blots");
			SendMessage(&FortsBlots[iNumForts - 1], "lia", MSG_BLOTS_SETMODEL, &Forts[iNumForts - 1], rCharacter);
			LayerAddObject(SEA_EXECUTE, &Forts[iNumForts], 10001);
			
			
			SendMessage(&AIFort, "laaaii", AI_MESSAGE_ADD_FORT, rIsland, arLocator, rCharacter, &Forts[iNumForts-1], &FortsBlots[iNumForts-1]);

			
			ref rNation = GetNationByType(iNation);
			
			SetFortFlag(&Forts[iNumForts - 1]);
			ReloadProgressUpdate();
		}
	}
}

void Fort_CreateEvent()
{
	int		iCannonsNum;
	aref	rCharacter;

	rCharacter = GetEventData();
	iCannonsNum = GetEventData();

	rCharacter.Fort.Cannons.Quantity = iCannonsNum;

	rCharacter.Ship.HP = iCannonsNum * 100;
	rCharacter.Fort.HP = rCharacter.Ship.HP;
}

int Fort_GetCannonsQuantity(ref rFortCharacter)
{
	if (!CheckAttribute(rFortCharacter, "Fort.Cannons.Quantity")) { return 0; }
	int iMaxCannonsQuantity = sti(rFortCharacter.Fort.Cannons.Quantity);
	int ResultCannons = sti(iMaxCannonsQuantity) - (iNumDamagedCannonsQuantity);
	return ResultCannons;
}

float Fort_CannonDamage()
{
	float	x, y, z;
	aref	aFortLabel;
	ref		rBallCharacter, rFortCharacter;
	int		iNumAllCannons, iNumDamagedCannons;
	int		iExp = 0;
	float	fDistance, fDamage;

	int iBallCharacterIndex = GetEventData();
	int iFortCharacterIndex = GetEventData();

	rBallCharacter = GetCharacter(iBallCharacterIndex);
	rFortCharacter = GetCharacter(iFortCharacterIndex);

	aFortLabel = GetEventData();

	iNumAllCannons = GetEventData();
	iNumDamagedCannons = GetEventData();
	iNumDamagedCannonsQuantity = iNumDamagedCannons;
	x = GetEventData();
	y = GetEventData();
	z = GetEventData();
	fDistance = GetEventData();	
	fDamage = GetEventData();	

	if (iBallCharacterIndex == iFortCharacterIndex) { return fDamage; }

	int iCompanionQuantity = GetCompanionQuantity(rBallCharacter);

	int iFortMode = sti(rFortCharacter.Fort.Mode);
	if (iFortMode != FORT_NORMAL) { return fDamage; }

	float fDistanceMul = pow(0.11, fDistance);

	ref rCannon = GetCannonByType(sti(rBallCharacter.Ship.Cannons.Type));
	float fCannonDamageMultiply = stf(rCannon.DamageMultiply) * fDistanceMul;

	ref rBall = GetGoodByType(sti(AIBalls.CurrentBallType));

	
	
	float fHullDamage = stf(rBall.DamageHull) * fCannonDamageMultiply * 0.4;
	float fCrewDamage = stf(rBall.DamageCrew) * fCannonDamageMultiply * 0.6;

	rFortCharacter.Ship.HP = (1.0 - MakeFloat(iNumDamagedCannons) / MakeFloat(iNumAllCannons)) * stf(rFortCharacter.Fort.HP);
	
	
	Ship_ApplyCrewHitpoints(rFortCharacter, fCrewDamage);

	float fDamagePiece = fHullDamage;
	
	fDamage = (fDamage + fDamagePiece);
	
	if (iBallCharacterIndex == nMainCharacterIndex)
	{
		int iRelation = SeaAI_GetRelation(iFortCharacterIndex, iBallCharacterIndex);
		if (iRelation != RELATION_ENEMY)
		{
			float fCurPlayerDamage = stf(rFortCharacter.Fort.PlayerDamage);

			if (iRelation == RELATION_FRIEND)	{ fCurPlayerDamage = fCurPlayerDamage + fDamagePiece * 0.8; }
			if (iRelation == RELATION_NEUTRAL)	{ fCurPlayerDamage = fCurPlayerDamage + fDamagePiece * 0.5; }

			if (fCurPlayerDamage >= 1.0)
			{
				SetCharacterRelationBoth(iBallCharacterIndex, iFortCharacterIndex, RELATION_ENEMY);
				SetNationRelation2MainCharacter(sti(rFortCharacter.Nation), RELATION_ENEMY);
				UpdateRelations();
				
				  
			}

			rFortCharacter.Fort.PlayerDamage = fCurPlayerDamage;
		}
	}
	bool bImmortal = LAi_IsImmortal(rFortCharacter);
	
	if (iBallCharacterIndex == GetMainCharacterIndex() && sti(Colonies[FindColony(rFortCharacter.City)].HeroOwn) == true)
	{
	    bImmortal = true;
	    iExp = 200;
	    AddCharacterExpToSkill(rBallCharacter, "Accuracy", -iExp / 3);
        AddCharacterExpToSkill(rBallCharacter, "Sailing", -iExp);
        AddCharacterExpToSkill(rBallCharacter, "Sneak", -iExp / 4);
        AddCharacterExpToSkill(rBallCharacter, SKILL_FORTUNE, -iExp / 4);
        AddCharacterExpToSkill(rBallCharacter, "Cannons", -iExp / 4);
	}
	
	if (fDamage >= 1.0)
	{ 
		Play3DSound("fort_cann_explode", x, y, z);
		CreateBlast(x, y, z);
		CreateParticleSystem("blast_inv", x, y, z, 0.0, 0.0, 0.0, 0);
		CreateParticleSystem("blast", x, y, z, 0.0, 0.0, 0.0, 0);
		

		if (!bImmortal)
		{
			iNumDamagedCannons++;
			fDamage = 1.0;
			
			CreateParticleSystem("SmallSmoke", x, y, z, -1.57, 0.0, 0.0, 0);

			 
		}
		else
		{
			fDamage = 0.0;
		}

		iExp = MakeInt(200 / iCompanionQuantity); 
		if (iBallCharacterIndex == GetMainCharacterIndex() && !bImmortal) 
		{
			object oRes;
			string sCannonString = LanguageConvertString(iSeaSectionLang, "Fort_cannon");
			Log_SetStringToLog(sCannonString);
			

			
			
		}
        if (!bImmortal)
        {
            
            
            AddCharacterExpToSkill(rBallCharacter, "Accuracy", iExp / 4);
            AddCharacterExpToSkill(rBallCharacter, "Sailing", iExp / 10);
            AddCharacterExpToSkill(rBallCharacter, "Sneak", iExp / 12);
            AddCharacterExpToSkill(rBallCharacter, SKILL_FORTUNE, iExp / 12);
            AddCharacterExpToSkill(rBallCharacter, "Cannons", iExp / 4);
            
        }
	}

	
	float fkoeff = 1.05+0.19*(10-MOD_SKILL_ENEMY_RATE)+0.1;
	if (rFortCharacter.id == "Tortuga Fort Commander") fkoeff = 1.15-MOD_SKILL_ENEMY_RATE/100;
	if (iNumDamagedCannons >= makeint(iNumAllCannons / fkoeff)) 
	{
		Fort_SetAbordageMode(rBallCharacter, rFortCharacter);
  		
		SetCharacterGoods(rFortCharacter, GOOD_BOMBS,  200 + rand(100));
		SetCharacterGoods(rFortCharacter, GOOD_POWDER,  200 + rand(100));
  		
	}

	return fDamage;
}

void Fort_SetAbordageMode(ref rKillerCharacter, ref rFortCharacter)
{
	
	rFortCharacter.Fort.Mode = FORT_ABORDAGE;

	
	rFortCharacter.Fort.DieTime.Year = GetDataYear();
	rFortCharacter.Fort.DieTime.Month = GetDataMonth();
	rFortCharacter.Fort.DieTime.Day = GetDataDay();
	rFortCharacter.Fort.DieTime.Time = GetTime();

	Event(FORT_DESTROYED, "l", sti(rFortCharacter.index));
	int iExp = 20000;
	
	if (GetRelation(sti(rFortCharacter.index), GetMainCharacterIndex()) == RELATION_ENEMY) 
	{
		
		AddCharacterExpToSkillSquadron(rKillerCharacter, "Grappling", 300);
		AddCharacterExpToSkillSquadron(rKillerCharacter, "Leadership", 150);
		AddCharacterExpToSkillSquadron(rKillerCharacter, "Sneak", 35);
		AddCharacterExpToSkillSquadron(rKillerCharacter, SKILL_FORTUNE, 35);
		AddCharacterExpToSkillSquadron(rKillerCharacter, "Cannons", 75);
	    

		
		object oRes;
		string sFortName = rFortCharacter.Ship.Name;
		string sFortString = LanguageConvertString(iSeaSectionLang, "Fort_destroy");
		string sExp = "600";

		Event(PARSE_STRING, "aslss", &oRes, sFortString, 2, sFortName, sExp);
		Log_SetStringToLog(oRes.Str);

	
	if (IsCompanion(rKillerCharacter))
	{
		Ship_PlayVictory("music_ship_victory", 8500);
	}   
	}
	
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Cartahena.Fort") && rFortCharacter.id == "Cartahena Fort Commander") Mtraxx_CartahenaPrepareFortBattle();
	
	if (CheckAttribute(pchar, "questTemp.Patria.SanJoseAttack") && rFortCharacter.id == "PortSpein Fort Commander") Patria_SanJoseFortDestroyed();
	if (CheckAttribute(pchar, "questTemp.Patria.CuracaoAttack") && rFortCharacter.id == "Villemstad Fort Commander") Patria_CuracaoFortDestroyed();
}

void Fort_SetCharacter(ref rCharacter, string sIslandID, string sLocationGroup, string sLocationLocator)
{
	int iCharacterIndex = Fort_FindCharacter(sIslandID, sLocationGroup, sLocationLocator);
	if (iCharacterIndex != -1)
	{
		ChangeCharacterAddress(&Characters[iCharacterIndex], "None", "");
	}

	ChangeCharacterAddressGroup(rCharacter, sIslandID, sLocationGroup, sLocationLocator);

	rCharacter.Ship.Type = Characters[iCharacterIndex].ship.type;

	Fort_CheckAttributes(rCharacter);
}

void Fort_CheckAttributes(ref rCharacter)
{
	if (!CheckAttribute(rCharacter, "Ship.Cannons.Type")) { rCharacter.Ship.Cannons.Type = CANNON_TYPE_CULVERINE_LBS18; }
	
	if (!CheckAttribute(rCharacter, "Ship.Cannons.Charge.Type")) { rCharacter.Ship.Cannons.Charge.Type = GOOD_BOMBS; }
	if (!CheckAttribute(rCharacter, "Fort.Cannons.Type.1")) 
	{ 
		Trace("Fort Error: Fort.Cannons.Type.1 can't find in character " + rCharacter.Name);
		rCharacter.Fort.Cannons.Type.1 = -1;
	}
	if (!CheckAttribute(rCharacter, "Fort.Cannons.Type.2")) 
	{ 
		Trace("Fort Error: Fort.Cannons.Type.2 can't find in character " + rCharacter.Name);
		rCharacter.Fort.Cannons.Type.2 = -1;
	}
	if (!CheckAttribute(rCharacter, "Fort.Cannons.Type.3")) 
	{ 
		Trace("Fort Error: Fort.Cannons.Type.3 can't find in character " + rCharacter.Name);
		rCharacter.Fort.Cannons.Type.3 = -1;
	}

	 
	rCharacter.Ship.Cannons.Charge.Type = GOOD_BOMBS;  
}

void Fort_LoadDamagedCannon()
{
	Trace("Fort_LoadDamagedCannon");
	float x = GetEventData();
	float y = GetEventData();
	float z = GetEventData();

	switch (rand(1))
	{
		case 0:
			CreateParticleSystem("ShipFire", x, y, z, -1.57, 0.0, 0.0, 0);
			CreateParticleSystem("fort_smoke", x, y, z, -1.57, 0.0, 0.0, 0);
		break;
		case 1:
			CreateParticleSystem("ShipFire", x, y, z, -1.57, 0.0, 0.0, 0);
			CreateParticleSystem("fort_gray_smoke", x, y, z, -1.57, 0.0, 0.0, 0);
		break;
	}
}


int Fort_FindCharacterByPort(string sIslandId, string sLocationLocator)
{
    ref   isl = GetIslandByID(sIslandId);
    aref  curItem;
	aref  rootItems;
	int   i;

	makearef(rootItems, isl.reload);
	int iHow;
	iHow = GetAttributesNum(rootItems);
	for (i=0; i<iHow; i++)
    {
        curItem = GetAttributeN(rootItems, i);
        if (curItem.name == sLocationLocator)
        {
            sLocationLocator = curItem.go;
            break;
        }
    }
    for (i=0; i<MAX_COLONIES; i++)
	{
	    if (colonies[i].from_sea == sLocationLocator)
	    {
	        if (CheckAttribute(&colonies[i], "commanderIdx"))
	        {
	            return  sti(colonies[i].commanderIdx);
	        }
	    }
	}

	return -1;
}

