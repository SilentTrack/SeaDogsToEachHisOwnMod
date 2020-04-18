

#define BRDLT_SHIP	0
#define BRDLT_FORT	1

#define BRDLT_MAXCREW 60

#define LOCINITBRD_DEFAULTLOCATION "BOARDING_U_H_CS_T12"
#define LOCINITBRD_DEFAULTLOCATION_FORT "Any_fort_1"

#define MAX_GROUP_SIZE   24

bool   IsFort = false; 
int    boarding_location = -1;
int    boarding_location_type = -1;
object boarding_fader;


int   boarding_player_crew = 0;
int   boarding_officers    = 0;
float boarding_player_base_crew    = 0.0; 
float boarding_player_crew_per_chr = 1.0;
int   boarding_player_crew_start   = 0; 

int   boarding_enemy_crew = 0;
float boarding_enemy_base_crew    = 0.0;
float boarding_enemy_crew_per_chr = 1.0;
int   boarding_enemy_crew_start   = 0; 

ref    boarding_enemy;
object boarding_adr[4];
float  boarding_exp = 0;
float  boarding_player_hp = 40;
float  boarding_enemy_hp = 40;
int    boarding_echr_index = -1;
int    boarding_erank = 10;
bool   LAi_boarding_process = false;
bool   Surrendered = false; 

int inside_ecrew_1, inside_ecrew_2;


bool LAi_IsBoardingProcess()
{
	return LAi_boarding_process;
}


string LAi_GetBoardingImage(ref echr, bool isMCAttack)
{
	ref mchr = GetMainCharacter();
	string deckID = "";
	isMCAttack   = true;
	if(isMCAttack)
	{
		deckID = GetShipLocationID(echr);
	}else{
		deckID = GetShipLocationID(mchr);
	}
	int locID = -1;
	if(deckID != "")
	{
		locID = FindLocation(deckID);
		if(locID < 0)
		{
			Trace("Boarding: ship location not found <" + deckID + ">, set default");
			deckID = "";
		}
	}
	if(locID >= 0)
	{
		if(CheckAttribute(&Locations[locID], "image"))
		{
			if(Locations[locID].image != "")
			{
				return Locations[locID].image;
			}
		}
	}
	return "loading\battle.tga";
}


void LAi_StartBoarding(int locType, ref echr, bool isMCAttack)
{
    SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); 
	
	ResetSound(); 
	PauseAllSounds();
	
	bQuestCheckProcessFreeze = true;
	
	EmptyAbordageCharacters();
	
	
	if(locType == BRDLT_FORT)
    {
        isMCAttack = true;
        IsFort = true;
    }
	else
    {
        IsFort = false;
    }
    
	
	SetEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill", 1);
	
	DeleteBattleInterface();
	InitBattleLandInterface();
	
	
	boarding_echr_index = sti(echr.index);
	
	ref mchr = GetMainCharacter();
	int mclass = GetCharacterShipClass(mchr); 
	int mcrew = GetCrewQuantity(mchr); 
	
	
	mchr.EnemyRank = echr.rank
	
	DeleteAttribute(pchar, "abordage_active");
	
	Log_TestInfo("����� �� ������ " + mcrew);
	mcrew = GetWeaponCrew(mchr, mcrew);
	
	
	int eclass = GetCharacterShipClass(echr); 
	int ecrew = GetCrewQuantity(echr); 
	int ecrewBak;
	int mcrewBak;

    Log_TestInfo("����� � ������� " + mcrew + " ������ " + ecrew);
    
    boarding_location_type = locType;
	
	if (echr.id == "WorldMarchCap1" || echr.id == "WorldMarchCap2" || echr.id == "WorldMarchCap3")
	{
		if (!CheckAttribute(pchar, "GenQuest.MarchCap.Battlestart")) DoQuestFunctionDelay("MarchCap2_CheckBattle", 0.5); 
	}
	
	bool blic = (CheckAttribute(echr, "Ship.Mode")) && (echr.Ship.Mode == "trade");
	if (CheckCharacterItem(pchar, "HolTradeLicence"))
	{
		if (blic || sti(echr.nation) == HOLLAND)
		{
			TakeNationLicence(HOLLAND);
			log_info("A trade license was annulled!");
		}
	}
	
	
	bool ok = (TestRansackCaptain) && (boarding_location_type != BRDLT_FORT);
    if (!CheckAttribute(echr, "DontRansackCaptain")) 
    {
    	if (CheckForSurrender(mchr, echr, 1) || ok) 
    	{
    		echr.ship.crew.morale = 5;

    		if (mclass < eclass)
			{
				AddCrewMorale(mchr, ( 3 + 2*rand(eclass-mclass)));
			} 
			else
			{
				AddCrewMorale(mchr, 3);
			}
			SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); 
            
			DelEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill");
			boarding_location = -1;
			
			
			DeleteAttribute(GetMainCharacter(), "EnemyRank");
		    bQuestCheckProcessFreeze = false;
		    
			
			Log_SetActiveAction("Nothing");
			EndBattleLandInterface();
            
            
			ChangeCrewExp(pchar, "Soldiers", 1);
			LaunchRansackMain(pchar, echr, "crew"); 
			
			
    		LAi_boarding_process = false;  
			Event(SHIP_CAPTURED, "l", sti(echr.index));
    		return;
    	}
	}
	
	
	
	float 	mShipClassCoeff, eShipClassCoeff;
	int   	mCrewShot = 0;
	int	  	eCrewShot = 0;
	float	mDamage, eDamage;	
	float   mCoeff 	= 0.0;	
	bool	bOk = false;
	
	if (CheckOfficersPerk(mchr, "MusketsShoot") && IsFort == false) 
	{
		bOk = true;
		int OffQty = GetOfficersQuantity(mchr); 
		if (OffQty < 0) OffQty = 1;
		
		mShipClassCoeff = (eclass - mclass) * 0.15; 
		mCrewShot = makeint(mcrew / 4);				

		if(IsCharacterEquippedArtefact(mchr, "indian_5")) ecrew = makeint(ecrew / 1.1);
		
		mCoeff = 0.5 + 0.1 * OffQty;
		
		mDamage = mcrew * mCoeff/4 + rand( makeint(mcrew * (1 - mCoeff)/4 ) );
		
		mDamage = mDamage * (1 + mShipClassCoeff);
		if(mDamage > ecrew * 0.75) mDamage = ecrew * 0.75;
		
		mDamage = mDamage * isEquippedArtefactUse(echr, "amulet_11", 1.0, 0.95));
		mDamage = mDamage * isEquippedArtefactUse(mchr, "indian_6", 1.0, 1.10));
		
		ecrewBak = makeint(mDamage);	
		ecrew = ecrew - ecrewBak;
		
		Log_SetStringToLog("A musket salvo eliminated " + ecrewBak + " enemy's crewmen");
	}
	if (CheckOfficersPerk(echr, "MusketsShoot") && IsFort == false) 
	{
		bOk = true;
		if(IsCharacterEquippedArtefact(ecrew, "indian_5")) mcrew = makeint(mcrew / 1.1);
	
		eShipClassCoeff = (mclass - eclass) * 0.15; 				
		eCrewShot = makeint(ecrew / 4);								
		eDamage = ecrew * 0.2 + rand(makeint(ecrew/20)); 			
		
		eDamage = eDamage * (1 + eShipClassCoeff);
		if(eDamage > mcrew * 0.75) eDamage = mcrew * 0.75;
		
		eDamage = eDamage * isEquippedArtefactUse(mchr, "amulet_11", 1.0, 0.95));
		eDamage = eDamage * isEquippedArtefactUse(echr, "indian_6", 1.0, 1.10));
		
		ecrewBak = makeint(eDamage);	
		mcrew = mcrew - ecrewBak;
		
		Log_SetStringToLog("A musket salvo eliminated " + ecrewBak + " your crewmen");
        Statistic_AddValue(mchr, "DeadCrewBoard", ecrewBak);
		Statistic_AddValue(mchr, "Sailors_dead", ecrewBak);
		
		Achievment_SetStat(mchr, 21, ecrewBak * 10);
	}
	if(bOk)
	{
		if(mclass <=2 || eclass <= 2) PlaySound("INTERFACE\MusketFire1.wav");
		else
		{
			if(rand(2) > 1) PlaySound("INTERFACE\MusketFire3.wav");
			else 			PlaySound("INTERFACE\MusketFire2.wav");
		}
	}
	
	

	if(ecrew < 0) ecrew = 0;
	if(mcrew < 0) mcrew = 0;
	boarding_erank = sti(echr.rank);

	
	boarding_enemy_base_crew = ecrew;
	boarding_player_base_crew = mcrew;
	
	
	GetBoardingHP(mchr, echr, &boarding_player_hp, &boarding_enemy_hp);
	
	
	boarding_location = -1;

	string deckID = "";
	isMCAttack   = true;
	if(isMCAttack)
	{
		deckID = GetShipLocationID(echr);
	}else{
		deckID = GetShipLocationID(mchr);
	}
	int locID = -1;
	if(deckID != "")
	{
		locID = FindLocation(deckID);
		if(locID < 0)
		{
			Trace("Boarding: ship location not found <" + deckID + ">, set default");
			deckID = "";
		}
	}
	if(deckID == "")
	{
		if(locType == BRDLT_FORT)
		{
			deckID = LOCINITBRD_DEFAULTLOCATION_FORT;
		}else{
			deckID = LOCINITBRD_DEFAULTLOCATION;
		}
		locID = FindLocation(deckID);
	}
	if (locID < 0)
	{   
		Trace("Boarding: ship location not found <" + deckID + ">, no start boarding");
		
		DeleteAttribute(GetMainCharacter(), "EnemyRank");
	    bQuestCheckProcessFreeze = false;
		    
		if(boarding_location_type == BRDLT_SHIP)
		{
            ChangeCrewExp(pchar, "Soldiers", 1);
            SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); 
			LaunchRansackMain(GetMainCharacter(), echr, "captain");	  
            LAi_boarding_process = false;
			Event(SHIP_CAPTURED, "l", sti(echr.index)); 
		}
		else
		{
			if (boarding_location_type == BRDLT_FORT)
			{
                ChangeCrewExp(pchar, "Soldiers", 1);
                SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); 
				Event(FORT_CAPTURED, "l", sti(echr.index));
				echr.Ship.Crew.Quantity = 10 + rand(350); 
                LaunchFortCapture(echr);
                LAi_boarding_process = false;
			}else{
				Trace("Boarding: unknow boarding location type");
			}
		}
		return;
	}

	pchar.abordage = 0;
	
	boarding_enemy = echr;
	
	int maxcrew = MAX_GROUP_SIZE;
	
    if(CheckAttribute(&Locations[locID], "boarding.locatorNum"))
	{
		maxcrew = sti(Locations[locID].boarding.locatorNum);
	}
    
    int iMaxcrew  = func_min(mclass, eclass); 
    switch (iMaxcrew)
    {
        case 7:
			iMaxcrew = 8;
		break;
		case 6:
			iMaxcrew = 10;
		break;
		case 5:
			iMaxcrew = 12;
		break;
		case 4:
			iMaxcrew = 14;
		break;
		case 3:
			iMaxcrew = 16;
		break;
		case 2:
			iMaxcrew = 22;
		break;
		case 1:
			iMaxcrew = 24;
		break;
    }
    if (iMaxcrew < maxcrew) maxcrew = iMaxcrew;
    
	if (boarding_location_type == BRDLT_SHIP && eclass != 6)  
	{
    	boarding_enemy.ShipCabinLocationId = GetShipCabinID(echr);
	}

	
	if(maxcrew > BRDLT_MAXCREW)
	{
	    maxcrew = BRDLT_MAXCREW;
	}
	

	

	
	
	int cn, j, compCrew;
    ref officer;
    if(IsFort)
    {
        mcrew = mcrew + GetTroopersCrewQuantity(GetMainCharacter()); 
        boarding_player_base_crew = mcrew;
        
        Log_TestInfo("�����: �� ������� mcrew = "+mcrew+ " ecrew = "+ ecrew + " boarding_enemy_hp = "+ boarding_enemy_hp + " boarding_player_hp = "+boarding_player_hp);
    }
    
    
	
	float rel;
	if(mcrew > ecrew)
	{
        
        boarding_player_hp = boarding_player_hp + GetBoarding_player_hp_Bonus(mcrew, ecrew);
		if (boarding_player_hp > 1000) boarding_player_hp = 1000;
		
        if(mcrew > maxcrew)
		{
			rel = makefloat(mcrew) / makefloat(maxcrew);
			mcrew = maxcrew;
			ecrew = MakeInt(ecrew / rel + 0.5);
		}
	}
	else
	{
		
		boarding_enemy_hp = boarding_enemy_hp + GetBoarding_enemy_hp_Bonus(mcrew, ecrew);
		if (boarding_enemy_hp > 1500) boarding_enemy_hp = 1500;
		
        if(ecrew > maxcrew)
		{       
			rel = makefloat(ecrew) / makefloat(maxcrew);
			ecrew = maxcrew;
			mcrew = MakeInt(mcrew/rel + 0.5);
		}
	}
	if(mcrew < 1) mcrew = 1;
	if(ecrew < 1) ecrew = 1;
	
    Log_TestInfo("����� ���������� mcrew = "+mcrew+ " ecrew = "+ ecrew + " boarding_enemy_hp = "+ boarding_enemy_hp + " boarding_player_hp = "+boarding_player_hp);

	
	
	
	
	inside_ecrew_1 = makeint(ecrew*0.3+0.5); 
	inside_ecrew_2 = makeint(ecrew*0.2+0.5); 
	if (inside_ecrew_1 < 1) inside_ecrew_1 = 1;
	if (inside_ecrew_2 < 1) inside_ecrew_2 = 1;
	if(IsFort) 
	{
		inside_ecrew_1 = ecrew*0.3+0.5; 
		inside_ecrew_2 = ecrew*0.3+0.5; 
		ecrew = ecrew*0.6+0.5;
	}
	
	
	
	boarding_enemy_crew        = ecrew;
	boarding_enemy_crew_start  = ecrew;
	boarding_player_crew       = mcrew;
	boarding_player_crew_start = mcrew;
	
	
	boarding_officers = 0;
	int passq;
	for(int i = 1; i < 4; i++)
	{
		passq = GetOfficersIndex(pchar, i);
		if (passq >= 0)
		{
            
		    
			
			boarding_officers = boarding_officers + 1;   
			LAi_SetOfficerType(&characters[passq]);
		}
	}
  
    
    boarding_player_crew_per_chr = makefloat(boarding_player_base_crew / makefloat(mcrew)); 
	
	boarding_enemy_crew_per_chr = makefloat(boarding_enemy_base_crew / makefloat(ecrew)); 
	

	
	LAi_SetCurHPMax(mchr);
	boarding_adr[0].location = mchr.location;
	boarding_adr[0].group    = mchr.location.group;
	boarding_adr[0].locator  = mchr.location.locator;
	for(i = 1; i < 4; i++)
	{
		int idx = GetOfficersIndex(GetMainCharacter(), i);
		if(idx < 0)
		{
			boarding_adr[i].location = "";
			boarding_adr[i].group    = "";
			boarding_adr[i].locator  = "";
			continue;
		}
		LAi_SetCurHPMax(&Characters[idx]);
		boarding_adr[i].location = Characters[idx].location;
		boarding_adr[i].group    = Characters[idx].location.group;
		boarding_adr[i].locator  = Characters[idx].location.locator;
	}
	
	LAi_boarding_process = true;
	LAi_LoadLocation(deckID, locType);
	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}


void LAi_LoadLocation(string locationID, int locType)
{

	ReloadProgressStart();
	
	int locIndex = FindLocation(locationID);
	Log_SetActiveAction("Nothing");
    Dead_Char_num = 0; 
	if(locIndex >= 0)
	{
		
		ref mchr = GetMainCharacter();
		mchr.location = locationID;
		mchr.location.group = "rld";
		
		int locNum[20];
		int locI;
		int maxLocators = 2;
		
		if (CheckAttribute(&Locations[locIndex], "boarding.locatorNum"))
		{
			maxLocators = sti(Locations[locIndex].boarding.locatorNum);
		}
		locI = 0;
		locNum[locI] = rand(maxLocators-1);
		string sLocType = "loc";
		
		if (CheckAttribute(&Locations[locIndex], "UpDeckType"))
		{
		    sLocType = ChooseShipUpDeck(mchr, boarding_enemy);
		}

		mchr.location.locator = sLocType + locNum[locI];
		
		if (CheckAttribute(&Locations[locIndex], "CabinType") && CheckAttribute(&Locations[locIndex], "boarding.Loc.Hero"))
		{
		    mchr.location.locator = Locations[locIndex].boarding.Loc.Hero;
		}
		bool   okLoc;
		int iLoc, j;
		
		if (!CheckAttribute(&Locations[locIndex], "CabinType"))
		{ 
	        
	        int logined = 1;
			for(int i = 1; i < 4; i++)
			{
				int idx = GetOfficersIndex(mchr, i);
				if(idx < 0) continue;
				
				if (logined > maxLocators) break;

	            

				
				DeleteAttribute(&Characters[idx], "location");
				
				
				Characters[idx].location.loadcapture = true;
			    
				
				
				iLoc = rand(3);

				okLoc = false;
				while (!okLoc)
				{
				    for(j = 0; j <=locI; j++)
				    {
				        if (locNum[j] == iLoc)
				        {
				            iLoc = rand(3);
				            okLoc = false;
				            break;
				        }
				        okLoc = true;
				    }
				}
				locI++;
			    locNum[locI] = iLoc;
				
				
				ChangeCharacterAddressGroup(&Characters[idx], locationID, "rld", sLocType + locNum[locI]);
				logined = logined + 1;
			}
		}
		
		boarding_location = locIndex;
				
		if(LoadLocation(&Locations[boarding_location]))
		{
			
			if (CheckAttribute(&Locations[boarding_location], "CabinType"))
			{
				FillAboardCabinBox(&Locations[boarding_location], boarding_enemy);
			}  
			
			LAi_SetBoardingActors(locationID);
			
			
			SendMessage(&mchr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightMode", 1);
			
			dialogDisable = true;
		}else{
			Trace("Boarding: Boarding location not loaded, current loc <" + locationID + ">");
		}
	}else{
		Trace("Boarding: Boarding location not found, current loc <" + locationID + ">");
	}
	ReloadProgressEnd();
	PostEvent("LoadSceneSound", 500);
}


void LAi_ReloadBoarding()
{

	
	dialogDisable = false;
	
	if(boarding_location < 0)
	{
		Trace("Boarding: No loaded current boarding location");
		LAi_boarding_process = false;
		return;
	}
	
	SetEventHandler("FaderEvent_StartFade", "LAi_ReloadStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "LAi_ReloadEndFade", 0);
	
	CreateEntity(&boarding_fader, "fader");
	string nextDeck = Locations[boarding_location].boarding.nextdeck;
	if (nextDeck != "")
	{
		SendMessage(&boarding_fader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
		if(CheckAttribute(&Locations[FindLocation(nextDeck)], "image"))
		{
			SendMessage(&boarding_fader, "ls", FADER_PICTURE, Locations[FindLocation(nextDeck)].image);
		}
	}
	float fadeOutTime = RELOAD_TIME_FADE_OUT;
	SendMessage(&boarding_fader, "lfl", FADER_OUT, fadeOutTime, false);
	SendMessage(&boarding_fader, "l", FADER_STARTFRAME);
}

void LAi_ReloadStartFade()
{
	
 
	ResetSound(); 
	PauseAllSounds();
	SendMessage(&Particles,"l", PS_CLEAR_CAPTURED);
	DelEventHandler("FaderEvent_StartFade", "LAi_ReloadStartFade");
	if(boarding_location >= 0) UnloadLocation(&Locations[boarding_location]);
}

void LAi_ReloadEndFade()
{        
	bool bCaptanSurrender = false;
	
	DelEventHandler("FaderEvent_EndFade", "LAi_ReloadEndFade");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
	
	bool canReload = true;
	
	if(CheckAttribute(&Locations[boarding_location], "UpDeckType"))
	{
		boarding_enemy_crew = inside_ecrew_1*2; 
	}
	else boarding_enemy_crew = inside_ecrew_2*2; 
	
	if(IsFort)
    {
		if(CheckAttribute(&Locations[boarding_location], "insidenext")) boarding_enemy_crew = inside_ecrew_2*2;
		else boarding_enemy_crew = inside_ecrew_1*2;
	}
	
	if(!CheckAttribute(&Locations[boarding_location], "boarding.nextdeck")) canReload = false;
	if(Locations[boarding_location].boarding.nextdeck == "") canReload = false;
	
 	if(canReload) 
	{
		Trace("Boarding: go to inside location");
		LAi_LoadLocation(Locations[boarding_location].boarding.nextdeck, -1); 
	}
    else
    {
		if (CheckAttribute(boarding_enemy, "ShipCabinLocationId"))
		{
            if (!CheckAttribute(boarding_enemy, "DontRansackCaptain")) 
	        {
	            Surrendered = (Surrendered) || (TestRansackCaptain);
	    		if (Surrendered && (boarding_location_type == BRDLT_SHIP))
	    		{
	    		    bCaptanSurrender = true;    
	   			}
	    	}
    		if (!bCaptanSurrender)
    		{
				boarding_enemy_crew = 1;
				if(CheckAttribute(&Locations[FindLocation(boarding_enemy.ShipCabinLocationId)], "image"))
				{
					SendMessage(&boarding_fader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
					SendMessage(&boarding_fader, "ls", FADER_PICTURE, Locations[FindLocation(boarding_enemy.ShipCabinLocationId)].image);
				}
				LAi_LoadLocation(boarding_enemy.ShipCabinLocationId, -1);
				DeleteAttribute(boarding_enemy, "ShipCabinLocationId"); 
				return;
			}
		}
  		if (CheckAttribute(pchar, "GenQuest.QuestAboardCaptanSurrender")) 
		{
		    DeleteAttribute(pchar, "GenQuest.QuestAboardCaptanSurrender"); 
		    bCaptanSurrender = true;
		}
		SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); 
		
		DelEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill");
		boarding_location = -1;
		

		float crew = boarding_player_crew * boarding_player_crew_per_chr; 
		
		ref mchar       = GetMainCharacter();
		float fDefenceSkill = 0.9 + MakeFloat(GetSummonSkillFromName(mchar, SKILL_DEFENCE)) / SKILL_MAX;
		int deadCrew    = makeint((boarding_player_base_crew - crew) / fDefenceSkill + 0.3); 
		if (CheckAttribute(pchar, "questTemp.ShipCapellan.Yes")) deadCrew = makeint(deadCrew/2); 
		int deadCrewWOMedic = makeint(boarding_player_base_crew - crew); 
		float leaderSkill = GetSummonSkillFromNameToOld(mchar, SKILL_LEADERSHIP);
		int iTemp;
		if (leaderSkill < 1) leaderSkill = 1; 
		
		
		iTemp = deadCrewWOMedic - deadCrew;
		if(CheckShipSituationDaily_GenQuest(pchar) > 1) 
		{
			if(iTemp > 0) 
			{
				deadCrew += deadCrewWOMedic; 
			}	
		}	
		else
		{
			if (iTemp > 0)
			{
				if (GetCargoGoods(mchar, GOOD_MEDICAMENT) < iTemp)
				{
					deadCrewWOMedic = iTemp - GetCargoGoods(mchar, GOOD_MEDICAMENT); 
					RemoveCharacterGoodsSelf(mchar, GOOD_MEDICAMENT, GetCargoGoods(mchar, GOOD_MEDICAMENT)); 
					deadCrew += deadCrewWOMedic; 
					Log_Info("" + deadCrewWOMedic + " crewmen died due to the lack of medicines");
				}
				else
				{
					RemoveCharacterGoodsSelf(mchar, GOOD_MEDICAMENT, iTemp);
					if (GetCargoGoods(mchar, GOOD_MEDICAMENT) < 16)
					{
						Log_Info("" + mchar.Ship.Name + " is low on medicines");
					}
				}
			}
		}
		
		
		DeleteAttribute(mchar, "EnemyRank");
        bQuestCheckProcessFreeze = false;
        
		RemoveCharacterGoodsSelf(mchar, GOOD_WEAPON, deadCrew);
		
		crew = boarding_player_base_crew - deadCrew; 
		Statistic_AddValue(mchar, "Sailors_dead", deadCrew);
		Statistic_AddValue(mchar, "DeadCrewBoard", deadCrew);
		
		Achievment_SetStat(mchar, 21, deadCrew * 10);
		
		AddCharacterExpToSkill(mchar, "Defence", makeint(deadCrew / 3 + 0.5)); 
        AddCharacterExpToSkill(mchar, "Grappling", makeint(deadCrew / 3 + 0.5));
                	
		
		if (deadCrew > makeint(crew+0.3)) 
		{
      		AddCrewMorale(mchar, sti(-20 / leaderSkill));
			ChangeCharacterComplexReputation(pchar,"authority", -0.5);
		}
		else
		{  
			AddCrewMorale(mchar, sti(leaderSkill));
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
		}

		
		SetCrewQuantityOverMax(GetMainCharacter(), MakeInt(crew + 0.3)); 
		Log_TestInfo("----- � ����� ����� " + crew +" �������� ---");
		
		crew = 0;
		if (boarding_echr_index >= 0)
		{
			SetCrewQuantity(&Characters[boarding_echr_index], MakeInt(crew + 0.3));
			boarding_echr_index = -1;
		}

		
		
                
		
		Log_SetActiveAction("Nothing");
		EndBattleLandInterface();
		
		ref mchr = GetMainCharacter();
		mchr.location         = boarding_adr[0].location;
		mchr.location.group   = boarding_adr[0].group;
		mchr.location.locator = boarding_adr[0].locator;
		
		for(int i = 1; i < 4; i++)
		{
			int idx = GetOfficersIndex(GetMainCharacter(), i);
			if(idx < 0) continue;
			Characters[idx].location         = boarding_adr[i].location;
			Characters[idx].location.group   = boarding_adr[i].group;
			Characters[idx].location.locator = boarding_adr[i].locator;
		}
		
		LAi_boarding_process = false;
		
        if (bCaptanSurrender)
        {
			ChangeCrewExp(pchar, "Soldiers", 4);
			LAi_SetCurHPMax(boarding_enemy);  
			SetCrewQuantity(boarding_enemy, MakeInt(boarding_enemy_base_crew*(rand(20)*0.01))); 
			LaunchRansackMain(pchar, boarding_enemy, "captain"); 
			LAi_boarding_process = false;
			Event(SHIP_CAPTURED, "l", sti(boarding_enemy.index));
			return;
		}
		
		if(boarding_location_type == BRDLT_SHIP)
		{       
		    ChangeCrewExp(pchar, "Soldiers", 5);
		    
			LaunchRansackMain(pchar, boarding_enemy, ""); 
			LAi_boarding_process = false;	 
			Event(SHIP_CAPTURED, "l", sti(boarding_enemy.index));
			return;
		}
		if(boarding_location_type == BRDLT_FORT)
		{
            ChangeCrewExp(pchar, "Soldiers", 7);
			Event(FORT_CAPTURED, "l", sti(boarding_enemy.index));
			boarding_enemy.Ship.Crew.Quantity = 10 + rand(350); 
			LaunchFortCapture(boarding_enemy);
			LAi_boarding_process = false;
			return;
		}
		Trace("Boarding: unknow boarding location type");
		Log_TestInfo("Boarding - unknown boarding location type : " + boarding_location_type);
	}
}


#event_handler("LAi_event_boarding_EnableReload", "LAi_EnableReload");
void LAi_EnableReload()
{
    
	if (boardM == 1)
	{
	
		
		ResetSoundScheme(); 
		
		SetSoundScheme("deck"); 
		
		SetMusic("music_abordage");
		boardM = -1;
		
	}
	Surrendered = CheckForSurrender(GetMainCharacter(), boarding_enemy, 2); 

	SetEventHandler("Control Activation","LAi_ActivateReload",1);
	Log_SetActiveAction("Reload");
	
	ref mchr = GetMainCharacter();
	SendMessage(&mchr, "lsl", MSG_CHARACTER_EX_MSG, "ChangeFightMode", 0);
	
	
	Log_TestInfo("Start boarding_enemy_crew_start: " + boarding_enemy_crew_start + " boarding_enemy_crew: " + boarding_enemy_crew);
	Log_TestInfo("Start boarding_player_crew_start: " + boarding_player_crew_start + " boarding_player_crew: " + boarding_player_crew);
	
	
	
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int index = LAi_loginedcharacters[i];
		if(index >= 0)
		{
			if(index != GetMainCharacterIndex())
			{
				ref chr = &Characters[index];
				if(!LAi_IsDead(chr) && !IsOfficer(chr) && chr.model.animation != "mushketer") 
				{
					if(chr.chr_ai.group == LAI_GROUP_PLAYER)
					{
						boarding_player_crew = boarding_player_crew + 1;
						
						
						LAi_SetHuberStayTypeNoGroup(chr); 
					}
				}
			}
		}
	}
	
	int eclass = sti(GetCharacterShipClass(boarding_enemy)); 
	if (CheckAttribute(&Locations[boarding_location], "UpDeckType"))
	{
		switch (eclass)
		{
			case 1: Locations[boarding_location].boarding.nextdeck = "Boarding_GunDeck"; break;
			case 2: Locations[boarding_location].boarding.nextdeck = "Boarding_GunDeck"; break;
			case 3: Locations[boarding_location].boarding.nextdeck = "Boarding_Campus"; break;
			case 4: Locations[boarding_location].boarding.nextdeck = "Boarding_Campus"; break;
			case 5: Locations[boarding_location].boarding.nextdeck = "Boarding_Cargohold"; break;
			case 6: Locations[boarding_location].boarding.nextdeck = ""; break;
		}
	}
	if (IsFort && Locations[boarding_location].boarding.nextdeck == "Boarding_bastion")
	{
		Locations[boarding_location].boarding.nextdeck = "Boarding_bastion"+(drand(1)+1);
	}
	
	Log_TestInfo("New boarding_player_crew: " + boarding_player_crew);
	Log_TestInfo("Next Location: " + Locations[boarding_location].boarding.nextdeck);
	Log_TestInfo("Enemy ship class: " + eclass);
	
}


void LAi_ActivateReload()
{
	string controlName = GetEventData();
	if(controlName != "ChrAction") return;
	if (CheckAttribute(pchar, "GenQuest.CannotReloadBoarding")) return; 
	DelEventHandler("Control Activation", "LAi_ActivateReload");
	Log_SetActiveAction("Nothing");
	LAi_ReloadBoarding();
}


void LAi_SetBoardingActors(string locID)
{
    int    limit, i, iQty;
	ref    chr;
	string model, ani, sTemp;
	int    xhp;
	int    locIndex = FindLocation(locID);
	int    mclass = GetCharacterShipClass(GetMainCharacter());
	int    eclass = GetCharacterShipClass(boarding_enemy);
	ref    mchr = GetMainCharacter(); 
    int    locMChar;
    
	limit = MAX_GROUP_SIZE;
	
	chr = &Locations[locIndex];
	
	if(CheckAttribute(chr, "boarding.locatorNum")) limit = sti(chr.boarding.locatorNum);

	Log_TestInfo("Location: " + locID + " Limit: " + limit);
	Log_TestInfo("Player: " + boarding_player_crew + " � " + boarding_player_crew_per_chr + " Enemy: " + boarding_enemy_crew + " � " + boarding_enemy_crew_per_chr);

    string sLocType = "loc";
	
	if (CheckAttribute(&Locations[locIndex], "UpDeckType"))
	{
	    sLocType = ChooseShipUpDeck(mchr, boarding_enemy);
	}
	if (!CheckAttribute(&Locations[locIndex], "CabinType"))
	{ 
		for(i = LAi_numloginedcharacters; i < limit; i++)
		{
			if(boarding_player_crew <= 0) break;
			model = LAi_GetBoardingModel(mchr, &ani);
			
			if (mchr.location.locator == (sLocType + i))
			{ 
	           locMChar = rand(3);
	           while (mchr.location.locator == (sLocType + locMChar))
	           {
	               locMChar = rand(3);
	           }
		       chr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType+locMChar);
			}
			else
			{
			   chr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType + i);
			}
			

			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);

			boarding_player_crew = boarding_player_crew - 1;
			
			
			

			
			if (!IsFort)
			{
	            SetFantomParamAbordOur(chr);
			}
			else
			{
			    SetFantomParamFortOur(chr);
			}
			SetNewModelToChar(chr); 
			chr.AboardFantom = true;
			AddCharHP(chr, boarding_player_hp); 
			 
		}
		
		if (CheckOfficersPerk(mchr, "MusketsShoot") && CheckAttribute(&Locations[locIndex], "UpDeckType") && !CheckAttribute(boarding_enemy, "GenQuest.CrewSkelMode"))
		{
			if (!IsFort) iQty = 2;
			else iQty = 3;
			for(i=1; i<=iQty; i++)
			{
				if (LAi_CheckLocatorFree("rld", sLocType+"mush"+i))
				{			
					model = LAi_GetBoardingMushketerModel(mchr);
					chr = GetCharacter(NPC_GenerateCharacter("GenChar_", model, "man", "mushketer", 5, sti(mchr.nation), 0, false, "soldier"));					
					chr.id = "GenChar_" + chr.index;
					if(i == iQty && mclass <= 3) chr.MushketType = "mushket3"; 
					chr.AboardFantom = true;
					if (!IsFort) chr.MusketerDistance = 0;
					LAi_SetWarriorType(chr);
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
					ChangeCharacterAddressGroup(chr, locID, "rld", sLocType+"mush"+i);
				}
			}
			if (!IsFort)
			{
	            SetMushketerParamAbordOur(chr);
			}
			else
			{
			    SetMushketerParamFortOur(chr);
			}
			AddCharHP(chr, boarding_player_hp); 
		}
		
	}
	
	if (sLocType == "loc")
	{
	    sLocType = "aloc";
	}
	else
	{
	    sLocType = "loc";
	}
	trace("sLocType = " + sLocType);
	for(i = 0; i < limit; i++) 
	{
		if(boarding_enemy_crew <= 0) break;
		model = LAi_GetBoardingModel(boarding_enemy, &ani);
		if (i == 0 && CheckAttribute(&Locations[locIndex], "boarding.Loc.Capt")) 
		{
		    chr = LAi_CreateFantomCharacterEx(model, ani, "rld", Locations[locIndex].boarding.Loc.Capt);
		}
		else
		{
			chr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType + i);
		}
		
		LAi_group_MoveCharacter(chr, LAI_GROUP_BRDENEMY);

		boarding_enemy_crew = boarding_enemy_crew - 1;
		
		
		

		if (!IsFort)
		{
            SetFantomParamAbordEnemy(chr);
		}
		else
		{
            SetFantomParamFortEnemy(chr);
			
		}
		
		if (i == 0 && CheckAttribute(&Locations[locIndex], "CabinType"))
		{
			ChangeAttributesFromCharacter(chr, boarding_enemy, true);
			chr.CaptanId = boarding_enemy.id; 
			boarding_enemy.CaptanId = boarding_enemy.id;
			chr.SuperShooter = true; 
			if (boarding_enemy.sex == "man") chr.greeting = "CapSinkShip";
			SetCharacterPerk(chr, "Energaiser"); 
			if (CheckAttribute(chr,"Situation"))
			{
				if(bSeaCanGenerateShipSituation) SetQuestAboardCabinDialogSituation(chr);
				else DeleteAttribute(chr,"Situation");
			}
			else
			{
				CaptainComission_GenerateSituation(chr);
				SetQuestAboardCabinDialog(chr); 
			}	
			
			
			
			
		    xhp = makeint((MOD_SKILL_ENEMY_RATE*2+sti(chr.rank))/10.0);
		    if (xhp > 0)
		    {
		        if (xhp >= 5) xhp = 4; 
				else
				{
					if (xhp >= 3) xhp = 2; 
					else xhp = 1; 
				}
			
			
				model = "cirass" + xhp;
				chr.cirassId  = Items_FindItemIdx(model);
				Log_TestInfo("�� �������� ������ " + model);
		    }
		}
		SetNewModelToChar(chr); 
		chr.AboardFantom = true;
		
		AddCharHP(chr, boarding_enemy_hp); 
		
		
		if (CheckAttribute(&Locations[locIndex], "UpDeckType"))
		{
			int ihp = LAi_GetCharacterHP(chr)*0.85+0.5;
			LAi_SetHP(chr, ihp, ihp);
		}
		
		if (CheckAttribute(&Locations[locIndex], "InsideDeckType") || CheckAttribute(&Locations[locIndex], "AddFortType"))
		{
			ihp = LAi_GetCharacterHP(chr)/1.5;
			LAi_SetHP(chr, ihp, ihp);
		}
	}
	
	if (CheckCharacterPerk(boarding_enemy, "MusketsShoot") || IsFort)
	{
		if (CheckAttribute(&Locations[locIndex], "UpDeckType") && !CheckAttribute(boarding_enemy, "GenQuest.CrewSkelMode"))
		{
			if (!IsFort) iQty = 2;
			else iQty = 3;	
			for(i=1; i<=iQty; i++)
			{
				if (LAi_CheckLocatorFree("rld", sLocType+"mush"+i))
				{
					model = LAi_GetBoardingMushketerModel(boarding_enemy);		
					chr = GetCharacter(NPC_GenerateCharacter("GenChar_", model, "man", "mushketer", 5, sti(boarding_enemy.nation), 0, false, "soldier"));					
					chr.id = "GenChar_" + chr.index;
					if(i == iQty && eclass <= 3) chr.MushketType = "mushket3"; 
					chr.AboardFantom = true;
					chr.MusketerDistance = 0;
					LAi_SetWarriorType(chr);
					LAi_group_MoveCharacter(chr, LAI_GROUP_BRDENEMY);
					ChangeCharacterAddressGroup(chr, locID, "rld", sLocType+"mush"+i);
					boarding_enemy_crew = boarding_enemy_crew - 1;
				}
			}
			if (!IsFort)
			{
				SetMushketerParamAbordEnemy(chr);
			}
			else
			{
				SetMushketerParamFortEnemy(chr);
			}
			AddCharHP(chr, boarding_enemy_hp); 
		}
	}
	
	
	LAi_group_FightGroupsEx(LAI_GROUP_PLAYER, LAI_GROUP_BRDENEMY, true, GetMainCharacterIndex(), -1, false, false);
	LAi_group_SetCheckEvent(LAI_GROUP_BRDENEMY);
}


void LAi_BoardingGroupKill()
{
	string group = GetEventData();
	if(group != LAI_GROUP_BRDENEMY) return;
	

	PostEvent("LAi_event_boarding_EnableReload", 5000);
}


string LAi_GetBoardingModel(ref rCharacter, ref ani)
{
	ani = "man";
	int iNation = sti(rCharacter.nation);
	string atr;
	string model;
	
	
	if (CheckAttribute(rCharacter, "GenQuest.CrewSkelMode"))
    {
        model = GetRandSkelModel();
		ani = "man";
		return model;
    }	

	if(sti(rCharacter.index) == GetMainCharacterIndex())
	{
        
        if (CheckAttribute(rCharacter, "GenQuest.CrewSkelMode"))
        {
            model = GetRandSkelModel();
			ani = "man";
			return model;
        }
	
	if (CheckAttribute(rCharacter, "questTemp.HWIC.HollEquip") && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
        {
            model = GetRandQuestSoldierModel(HOLLAND);
			ani = "man";
			return model;
        }
	if (CheckAttribute(rCharacter, "questTemp.HWIC.EngEquip") && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA)
        {
            model = GetRandQuestSoldierModel(ENGLAND);
			ani = "man";
			return model;
        }
	
        if (isMainCharacterPatented() && sti(Items[sti(rCharacter.EquipedPatentId)].TitulCur) > 1) 
        {
            atr = "boardingModel.enemy";
            iNation = sti(Items[sti(rCharacter.EquipedPatentId)].Nation);
        }
        else
        {
            atr = "boardingModel.player";
        }
        
	}
	else
    {   
		if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Trade")
		{
            atr = "boardingModel.merchant";
        }
		else
        {
			if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "mercenary")
			{ 
				model = GetRandQuestMercenaryModel();
				ani = "man";
				return model;
			}
			else
			{
            atr = "boardingModel.enemy";
        }
	}
	}
	
	if (iNation < 0) iNation = PIRATE;
	
	if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Pirate" && !IsMainCharacter(rCharacter)) iNation = PIRATE;
	Nations[iNation].boardingModel.player = "";
	Nations[iNation].boardingModel.enemy = "";
		
	aref models;
	makearef(models, Nations[iNation].(atr));
	int num = GetAttributesNum(models);
	if(num <= 0) return "";
	int i = rand(num - 1);
	atr = GetAttributeName(GetAttributeN(models, i));
	model = models.(atr);
	atr = atr + ".ani";
	if(CheckAttribute(models, atr))
	{
		if(models.(atr) != "")
		{
			ani = models.(atr);
		}
	}
	return model;
}


string LAi_GetBoardingMushketerModel(ref rCharacter)
{
	string model;
	int iNation = sti(rCharacter.nation);
	
	if(sti(rCharacter.index) == GetMainCharacterIndex()) 
	{
		
		if (CheckAttribute(rCharacter, "questTemp.HWIC.HollEquip") && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
        {
            model = "mush_hol_"+(rand(5)+1);
			return model;
        }
		if (CheckAttribute(rCharacter, "questTemp.HWIC.EngEquip") && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA)
        {
            model = "mush_eng_"+(rand(5)+1);
			return model;
        }
		
        if (isMainCharacterPatented() && sti(Items[sti(rCharacter.EquipedPatentId)].TitulCur) > 1) 
        {
            iNation = sti(Items[sti(rCharacter.EquipedPatentId)].Nation);
			model = "mush_"+NationShortName(iNation)+"_"+(rand(5)+1); 
        }
        else model = "mush_ctz_"+(rand(2)+4); 
	}
	else 
    {   
		if (CheckAttribute(rCharacter, "Ship.Mode")) 
		{
			switch (rCharacter.Ship.Mode)
			{
				case "war": 		
				if(iNation == PIRATE)
				{
					model = "mush_ctz_"+(rand(2)+7);
				}	
				else
				{		
					model = "mush_"+NationShortName(iNation)+"_"+(rand(5)+1); 
				}	
				break; 
				case "trade": 		model = "mush_ctz_"+(rand(2)+1); break; 
				case "pirate": 		model = "mush_ctz_"+(rand(2)+7); break; 
				case "hunter": 		model = "mush_ctz_"+(rand(2)+7); break; 
				case "mercenary": 	model = "mush_ctz_"+(rand(2)+10); break; 
			}
        }
		else 
        {
			if (iNation == PIRATE) model = "mush_ctz_"+(rand(2)+7);
			else model = "mush_"+NationShortName(iNation)+"_"+(rand(5)+1); 
        }
	}
	return model;
}


bool CheckForSurrender(ref mchr, ref echr, int _deck)
{
    if(boarding_location_type == BRDLT_FORT) return false; 
    
    if (GetPrisonerQty() > PRISONER_MAX) return false; 
    
	if (sti(echr.rank) > (50 - MOD_SKILL_ENEMY_RATE)) return false; 

	if (!IsCharacterPerkOn(mchr,"SeaDogProfessional")) 
	{
		if (sti(mchr.rank) < (sti(echr.rank) - MOD_SKILL_ENEMY_RATE / 2))  return false; 
	}
    
	int eclass = GetCharacterShipClass(echr);
	int mclass = GetCharacterShipClass(mchr);
	if (eclass == 1) return false; 
	
	float fCrewRate = 0.5;  
	if (sti(echr.Nation) == PIRATE)
	{
		fCrewRate = 0.2;
	}
	else
	{
		if (CheckAttribute(echr, "Ship.Mode") && echr.Ship.Mode == "Trade") 
		{
			fCrewRate = 0.9; 
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
    if (sGroupID != "")
    {
    	eShip = Group_GetLiveCharactersNum(sGroupID);
    }
    else
    {
    	eShip = 1;
    }
	
	float fStep = 1;
	if (_deck == 2)
	{
		fStep = 1.4;
	}
    mcrew = mcrew * (1.0 + mclass / 20.0) * fStep; 
    ecrew = ecrew * (1.0 + eclass / 20.0);  
    
    mcrew = mcrew * (1.0 + (mShip-1) / 5.0);
    ecrew = ecrew * (1.0 + (eShip-1) / 5.0);
    if (bBettaTestMode) 
    {
    	Log_Info("Surrender Hero = "+ mcrew + "    Enemy = " + ecrew + " eShipQty = " + eShip);
    }
    if (mcrew > ecrew)
	{
		return true; 
	}
	return false; 
}


string ChooseShipUpDeck(ref _mchar, ref _enemy)
{
    string sLoc = "loc";
    
	if (GetCargoMaxSpace(_mchar) > GetCargoMaxSpace(_enemy))
	{
	    sLoc = "aloc";
	}
	
    return sLoc;
}

