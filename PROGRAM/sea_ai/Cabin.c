
bool	bCabinStarted = false;
bool	bDeckBoatStarted = false;

void Cabin_ReloadStartFade()
{
	int a = GetEventData();
	aref reload_fader = GetEventData();
	LayerFreeze(SEA_EXECUTE,true);
	LayerFreeze(SEA_REALIZE,true);
	LayerFreeze("sea_reflection2",true);
	LayerFreeze("execute",false);
	LayerFreeze("realize",false);

	MoveWeatherToLayers("execute", "realize");
	MoveSeaToLayers("execute", "realize");
	HideGrass();

	SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
    
    ClearAllFire();
    
	DelEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFade");

	fOldMaxSeaHeight = stf(Sea.MaxSeaHeight);
	Sea.MaxSeaHeight = 1.2;						
}

void Cabin_ReloadEndFade()
{
	
	AIBalls.Clear = "";

 	PauseParticles(true);
    

	
 	int a = GetEventData();
	aref reload_fader = GetEventData();
	
	Cabin_Start();
	
	DelEventHandler("FaderEvent_EndFade", "Cabin_ReloadEndFade");
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}

void Sea_CabinStartNow()
{
	if (CheckAttribute(pchar, "GenQuest.CabinLock")) 
	{
		PlaySound("interface\knock.wav");
		return;
	}
	if (!bCabinStarted)
	{
        bSeaReloadStarted = true;

        Set_My_Cabin();
        
    	object reload_fader;
    	CreateEntity(&reload_fader, "fader");
    	SetEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFade", 0);
    	SetEventHandler("FaderEvent_EndFade", "Cabin_ReloadEndFade", 0);

		SendMessage(&reload_fader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
    	SendMessage(&reload_fader, "ls", FADER_PICTURE, Get_My_Cabin_Pic());
    	SendMessage(&reload_fader, "lfl", FADER_OUT, 1.0, false);
    	SendMessage(&reload_fader, "l", FADER_STARTFRAME);

    	PauseAllSounds();
	     
		ResetSound(); 

    	bAbordageStarted = true;
    	bCabinStarted = true;
    	Sea.AbordageMode = true;
	}
	else
	{
	   Return2SeaAfterCabin();
	}
}


int cabin_officers;
void Cabin_Start()
{
 
	ResetSound(); 
	PauseAllSounds();
	int i;
	
	DeleteBattleInterface();
	InitBattleLandInterface();
	
	ref mchr = GetMainCharacter();
	
	string deckID = "";
	deckID = Get_My_Cabin();
	
	int locID = -1;
	locID = FindLocation(deckID);
	if(locID < 0)
	{
		Trace("Cabin: ship location not found <" + deckID + ">, set default");
	    deckID = "";
	    return;
	}
	
	boarding_adr[0].location = mchr.location;
	boarding_adr[0].group = mchr.location.group;
	boarding_adr[0].locator = mchr.location.locator;
	
	
	LAi_boarding_process = false;
	Cabin_LoadLocation(deckID);
	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}


void Cabin_LoadLocation(string locationID)
{
	Log_TestInfo("Cabin_LoadLocation " + locationID);
	ReloadProgressStart();
	
	int locIndex = FindLocation(locationID);
	Log_SetActiveAction("Nothing");
	if(locIndex >= 0)
	{
		
		ref mchr = GetMainCharacter();
		mchr.location = locationID;
		mchr.location.group = "rld";
		mchr.location.locator = "loc0";

		
		boarding_location = locIndex;
		Locations[locIndex].boarding = "true";
		if(LoadLocation(&Locations[locIndex]))
		{
			
            SetOfficersInCabin();
			
			dialogDisable = false;
		}else{
			Trace("Boarding: Boarding location not loaded, current loc <" + locationID + ">");
		}
	}else{
		Trace("Boarding: Boarding location not found, current loc <" + locationID + ">");
	}
	ReloadProgressEnd();
	PostEvent("LoadSceneSound", 500);
}
void SetOfficersInCabin()
{
	if (CheckAttribute(pchar, "GenQuest.DontSetCabinOfficer")) return; 
    
    ref chr, mchr;
    int i;
    int idx;
    
    mchr = GetMainCharacter();
	for (i = 1; i < 4; i++)
	{
		idx = GetOfficersIndex(mchr, i);
		if (idx < 1) continue;
		chr = &Characters[idx];
		PlaceCharacter(chr, "rld", mchr.location);
	}
}
void SetOfficersLocationToNone()
{
    
    ref chr, mchr;
    int i;
    int idx;

    mchr = GetMainCharacter();
	for (i = 1; i < 4; i++)
	{
		idx = GetOfficersIndex(mchr, i);
		if (idx < 1) continue;
		chr = &Characters[idx];
		chr.location = "none";
	}
}

void Return2SeaAfterCabin()
{
	Log_TestInfo("Return2SeaAfterCabin");
	
 	Return2SeaClearNPC();

    
	SetEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFadeAfter", 0);
	SetEventHandler("FaderEvent_EndFade", "Cabin_ReloadEndFadeAfter", 0);
	
	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
	SendMessage(&boarding_fader, "ls", FADER_PICTURE, "loading\sea_0" + rand(2) + ".tga");

	float fadeOutTime = RELOAD_TIME_FADE_OUT;

	SendMessage(&boarding_fader, "lfl", FADER_OUT, fadeOutTime, false);
	SendMessage(&boarding_fader, "l", FADER_STARTFRAME);
	
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Dove")) 
	{
		bQuestDisableMapEnter = true;
		bDisableCharacterMenu = true;
		InterfaceStates.Buttons.Save.enable = false;
		DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Dove");
		DoQuestFunctionDelay("Mtraxx_CorridaIgnasioDove", 3.0);
	}
}


void Return2SeaClearNPC()
{
	if (bDeckBoatStarted)
    {
        
    	DeleteNPCfromDeck();
	}
	else
	{
    	SetOfficersLocationToNone(); 
    	SetPrisonerLocationToNone(); 
    	SetOfficersInCampusToNone():
		CompanionSaveTasks(); 
    	DeleteQuestAttribute("SetNPCInShipDeck");
    	DeleteQuestAttribute("SetNPCInShipCabin");
    	DeleteQuestAttribute("SetNPCInShipCampus");
	}
	DeleteAttribute(pchar, "GenQuest.CaptainId");
}

void Cabin_ReloadStartFadeAfter()
{
	
 
	ResetSound(); 
	PauseAllSounds();
	
	DelEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFadeAfter");
	if(boarding_location >= 0) UnloadLocation(&Locations[boarding_location]);
}

void Cabin_ReloadEndFadeAfter()
{
	ref sld;
	
	DelEventHandler("FaderEvent_EndFade", "Cabin_ReloadEndFadeAfter");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
	boarding_location = -1;
	
	Log_SetActiveAction("Nothing");
	EndBattleLandInterface();
	
	ref mchr = GetMainCharacter();
	mchr.location = boarding_adr[0].location;
	mchr.location.group = boarding_adr[0].group;
	mchr.location.locator = boarding_adr[0].locator;
	
	
	if (bDisableMapEnter && !CheckAttribute(pchar, "GenQuest.MapClosedNoBattle")) 
	{
	    mchr.Ship.HP = makefloat(stf(mchr.Ship.HP) - GetCharacterShipHP(mchr) * 0.01);
	    if (stf(mchr.Ship.HP) < 0) mchr.Ship.HP = 0;
	} 
	
	
	
	
	LAi_boarding_process = false;

 	LayerFreeze("execute", true);
	LayerFreeze("realize", true);

	LayerFreeze("sea_reflection2", false);
	LayerFreeze(SEA_EXECUTE, false);
	LayerFreeze(SEA_REALIZE, false);

	MoveWeatherToLayers(SEA_EXECUTE, SEA_REALIZE);
	MoveSeaToLayers(SEA_EXECUTE, SEA_REALIZE);
	ShowGrass();

	Sea.MaxSeaHeight = fOldMaxSeaHeight;		
	bAbordageStarted = false;
	bCabinStarted    = false;
	bDeckBoatStarted = false;
	Sea.AbordageMode = false;

	InitBattleInterface();
	StartBattleInterface();
	RefreshBattleInterface();

	SetSchemeForSea();

	PauseParticles(false);

	bSeaReloadStarted = false;

	Ship_RecreateStaticSounds();
	
	 
	
	if (CheckAttribute(mchr, "StartBattleAfterDeck"))
	{
        Ship_NationAgressivePatent(characterFromID(mchr.StartBattleMainCaptanId));  
        Ship_FlagRefresh(characterFromID(mchr.StartBattleMainCaptanId)); 
        SetCharacterRelationBoth(GetCharacterIndex(mchr.StartBattleMainCaptanId), GetMainCharacterIndex(), RELATION_ENEMY);
	    Group_SetTaskAttack(mchr.StartBattleEncGroupName, PLAYER_GROUP);

	    SetNationRelation2MainCharacter(sti(Characters[GetCharacterIndex(mchr.StartBattleMainCaptanId)].nation), RELATION_ENEMY);
	    UpdateRelations();
	    RefreshBattleInterface();
	    DeleteAttribute(mchr, "StartBattleAfterDeck"); 
	    DoQuestCheckDelay("NationUpdate", 3.0);
	}
	if (CheckAttribute(mchr, "GenQuest.DestroyPirate.FightAfterDeck")) 
	{
		sld = characterFromId("MQPirate");
		DeleteAttribute(sld, "ShipTaskLock"); 
		sld.nation = PIRATE;
		Ship_NationAgressivePatent(sld);
		Ship_FlagRefresh(sld); 
		Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), 1);
		UpdateRelations();
		RefreshBattleInterface();
		DoQuestCheckDelay("NationUpdate", 0.1);
	}
	
	if (CheckAttribute(mchr, "GenQuest.CaptainComission.FightAfterDeck"))
	{
		sld = characterFromId("CapComission_1");
		DeleteAttribute(sld, "AlwaysFriend"); 
		sld.nation = PIRATE;
		Ship_NationAgressivePatent(sld);
		Ship_FlagRefresh(sld); 
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
		Group_SetTaskAttack("Sea_CapComission_1", PLAYER_GROUP);
		Group_LockTask("Sea_CapComission_1");
		UpdateRelations();
		RefreshBattleInterface();
		DoQuestCheckDelay("NationUpdate", 0.1);
	}
	
	
	
	CheckCaptainFreeQuestAboardSituation(); 
	
	
	DeleteParticles();
	CreateParticleEntity();
}



void Sea_DeckBoatStartNow(ref _iShipsCharacter)
{
	string boat_pic = "loading\boat_"+rand(1)+".tga";	
	if(CheckAttribute(pchar, "TownEscape")) boat_pic = "loading\Start_Loading.tga";
	
	if (!bAbordageStarted)
	{
	    bSeaReloadStarted = true;

		object reload_fader;
		CreateEntity(&reload_fader, "fader");
		SetEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFade", 0);  
		SetEventHandler("FaderEvent_EndFade", "DeckBoat_ReloadEndFade", 0);
		
		SendMessage(&reload_fader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");	
		SendMessage(&reload_fader, "ls", FADER_PICTURE, boat_pic);
		SendMessage(&reload_fader, "lfl", FADER_OUT, 1.0, false);
		SendMessage(&reload_fader, "l", FADER_STARTFRAME);

        MakeCloneShipDeck(_iShipsCharacter, false); 
		SetSailorDeck_Ships(_iShipsCharacter);

		PauseAllSounds();
	 	
		ResetSound(); 

	    

		bAbordageStarted = true;
		bDeckBoatStarted = true;
		Sea.AbordageMode = true;
	}

}

void DeckBoat_ReloadEndFade()
{
	
	AIBalls.Clear = "";
 	PauseParticles(true);
    

	
	int a = GetEventData();
	aref reload_fader = GetEventData();

	DeckBoat_Start();

	DelEventHandler("FaderEvent_EndFade", "DeckBoat_ReloadEndFade");
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}
void DeckBoat_Start()
{
 
	
	
	int i;
	
	DeleteBattleInterface();
	StartBattleLandInterface();
    if(!CheckAttribute(GetMainCharacter(), "TownEscape") && !CheckAttribute(GetMainCharacter(), "questTemp.Sharlie.Sea")) 
	{
		PlaySound("interface\_Abandon0.wav");
	}	
	ref mchr = GetMainCharacter();

	string DeckBoatID = "";
	DeckBoatID = "Deck_Near_Ship";


	int locID = -1;
	locID = FindLocation(DeckBoatID);
	if(locID < 0)
	{
		Trace("Boarding: ship location not found <" + DeckBoatID + ">, set default");
	    DeckBoatID = "";
	    return;
	}
	
	boarding_adr[0].location = mchr.location;
	boarding_adr[0].group = mchr.location.group;
	boarding_adr[0].locator = mchr.location.locator;
	for(i = 1; i < 4; i++)
	{
		int idx = GetOfficersIndex(GetMainCharacter(), i);
		if(idx < 0)
		{
			boarding_adr[i].location = "";
			boarding_adr[i].group = "";
			boarding_adr[i].locator = "";
			continue;
		}
		boarding_adr[i].location = Characters[idx].location;
		boarding_adr[i].group = Characters[idx].location.group;
		boarding_adr[i].locator = Characters[idx].location.locator;
	}

	
	LAi_boarding_process = false;
	DeckBoat_LoadLocation(DeckBoatID);
	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}


void DeckBoat_LoadLocation(string locationID)
{
	ReloadProgressStart();
	
	int locIndex = FindLocation(locationID);
	Log_SetActiveAction("Nothing");
	if(locIndex >= 0)
	{
		
		ref mchr = GetMainCharacter();

		DeleteAttribute(mchr, "StartBattleAfterDeck"); 

		mchr.location = locationID;
		mchr.location.group = "goto";
		mchr.location.locator = "goto5";


		
		boarding_location = locIndex;
		Locations[locIndex].boarding = "true";
		if(LoadLocation(&Locations[locIndex]))
		{
			
			dialogDisable = false;
		}else{
			Trace("Boarding: Boarding location not loaded, current loc <" + locationID + ">");
		}
	}else{
		Trace("Boarding: Boarding location not found, current loc <" + locationID + ">");
	}
	ReloadProgressEnd();
	PostEvent("LoadSceneSound", 500);
}
void Sea_DeckBoatLoad(int ShipsCharacter)
{
	if (bSeaActive == false) { return; }
	ref rCharacter = GetCharacter(ShipsCharacter);

	if (LAi_IsDead(rCharacter)) return;  
	if (CheckAttribute(rCharacter, "DontDeskTalk")) return; 
	
	Sea_DeckBoatStartNow(rCharacter);
}

void SetSailorDeck_Ships(ref Chref)
{
	String characterID = Chref.id;
	ref sld;
    string  ani, model;
    int cn, Rank = 10;

	
	pchar.GenQuest.CaptainId = characterID; 
	pchar.quest.Munity = ""; 
	
	
	
	
	if(characterID == "MaryCelesteCapitan")
	{
		model = LAi_GetBoardingModel(PChar, &ani);
		sld = GetCharacter(NPC_GenerateCharacter("saylor_0" + i, model, "man", ani, Rank, sti(PChar.nation), 0, true, "soldier"));
	    sld.name = "Sailor";
	    sld.lastname = "";
        sld.Dialog.Filename = "Quest\sailors_dialog.c";
    	sld.Dialog.CurrentNode = "On_MaryCeleste_Deck";
    	sld.greeting = "sea_sailors";
		
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, PChar, "", 5.0, 0);
		
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto8");
		
		chrDisableReloadToLocation = true; 
		
		PChar.QuestTemp.MaryCeleste = "OnDeck";
		Map_ReleaseQuestEncounter(characterID); 
		return;
	}
	if (characterID == "Cap_Vensan")
	{
		Saga_CreateCapnCrewVensan();
		chrDisableReloadToLocation = true; 
		return;
	}
	
	if (CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
	{
		sld = characterFromId("Rum_Cap");
		chrDisableReloadToLocation = true; 
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, PChar, "", 5.0, 0);
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto8");				
		return;
	}
	
	if(CheckAttribute(pchar,"questTemp.ReasonToFast.canSpeakSailor") || CheckAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain"))
	{
		model = LAi_GetBoardingModel(PChar, &ani);
		sld = GetCharacter(NPC_GenerateCharacter("saylor_0"+i, model, "man", ani, 10, sti(PChar.nation), 0, true, "soldier"));
		sld.name = "������";
	    sld.lastname = "";
		sld.Dialog.Filename = "Quest\sailors_dialog.c";
		if(CheckAttribute(pchar,"questTemp.ReasonToFast.canSpeakSailor"))
		{
			sld.Dialog.CurrentNode = "On_MyShip_Deck";
		}
		if(CheckAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain"))
		{
			sld.Dialog.CurrentNode = "CapComission_OnShipDeck";
		}	
    	sld.greeting = "sea_sailors";
		
		chrDisableReloadToLocation = true; 
				
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, PChar, "", 5.0, 0);
		
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto8");				
		return;
	}
	
	if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest.canSpeakSailor"))
	{
		model = LAi_GetBoardingModel(PChar, &ani);
		sld = GetCharacter(NPC_GenerateCharacter("saylor_0"+i, model, "man", ani, 10, sti(PChar.nation), 0, true, "soldier"));
		sld.name = "������";
	    sld.lastname = "";
		sld.Dialog.Filename = "Quest\sailors_dialog.c";
		if(pchar.GenQuest.Hold_GenQuest == "prisoner_escaped")
		{
			sld.Dialog.CurrentNode = "Hold_GenQuest_OnShipDeck";
		}
		if(pchar.GenQuest.Hold_GenQuest == "prisoner_ransom")
		{
			sld.Dialog.CurrentNode = "Hold_GenQuest_OnShipDeck4";
		}	
    	sld.greeting = "sea_sailors";
		
		chrDisableReloadToLocation = true; 
				
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, PChar, "", 5.0, 0);
		
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto8");				
		return;	
	}
	
	if(CheckAttribute(pchar,"GenQuest.CaptainComission.canSpeakCaptain"))
	{
		sld = characterFromID("CapComission_1");
		sld.dialog.currentnode = "CaptainComission_380";
		sld.greeting = "Gr_Soldier";
		chrDisableReloadToLocation = true; 
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto8");	
		LAi_CharacterEnableDialog(sld);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		return;	
	}

	if (characterID == "MQPirate" || characterID == "CapComission_1") 
	{  
	    ref CopyChref;
	    
		CopyChref = GetCharacter(NPC_GenerateCharacter("FantomDeckCap", "none", "man", "man", 1, PIRATE, 0, false, "citizen"));
		
	    int NewCapIdx = sti(CopyChref.index);
		aref arToChar, arFromChar;
		
		DeleteAttribute(CopyChref, "");
		
	    makearef(arToChar, CopyChref);
	    makearef(arFromChar, Chref);
	    CopyAttributes(arToChar, arFromChar);
	    
		CopyChref.index = NewCapIdx;
		CopyChref.id = "FantomDeckCap";
		CopyChref.lifeDay = 0;
		
	    LAi_SetWarriorType(CopyChref);
		LAi_warrior_DialogEnable(CopyChref, true);
		LAi_SetLoginTime(CopyChref, 0.0, 24.0); 
		
		if (!CheckAttribute(CopyChref,"DeckDialogNode"))
	    {
	        CopyChref.Dialog.Filename = "Capitans_dialog.c";
		    CopyChref.greeting = "Gr_Commander";
		    CopyChref.Dialog.CurrentNode = "First time";
	    }
	    else
	    {
	        CopyChref.Dialog.CurrentNode = CopyChref.DeckDialogNode;
	    }
	    
	    if (CheckAttribute(CopyChref, "talk_date_Go_away") && CopyChref.talk_date_Go_away == LastSpeakDate())
	    {
	        CopyChref.Dialog.CurrentNode = "Go_away";
	    }
	    

		ChangeCharacterAddressGroup(CopyChref, "Deck_Near_Ship", "goto", "goto9");
	}
	else
	{   
		LAi_SetWarriorType(Chref);
		LAi_warrior_DialogEnable(Chref, true);
		LAi_SetLoginTime(Chref, 0.0, 24.0); 
		
		if (CheckAttribute(Chref, "Dialog.Filename"))
	    {
	        Chref.Bak.Dialog.Filename    = Chref.Dialog.Filename;
	        Chref.Bak.Dialog.CurrentNode = Chref.Dialog.CurrentNode;
	    }
	    else
	    {
	        Chref.Bak.Dialog.Filename    = "";
	        Chref.Bak.Dialog.CurrentNode = "First time";
	    }
		if (!CheckAttribute(Chref,"DeckDialogNode"))
	    {
	        Chref.Dialog.Filename = "Capitans_dialog.c";
		    Chref.greeting = "Gr_Commander";
		    Chref.Dialog.CurrentNode = "First time";
	    }
	    else
	    {
	        Chref.Dialog.CurrentNode = Chref.DeckDialogNode;
	    }
	    
	    if (CheckAttribute(Chref, "talk_date_Go_away") && Chref.talk_date_Go_away == LastSpeakDate())
	    {
	        Chref.Dialog.CurrentNode = "Go_away";
	    }
	    

		ChangeCharacterAddressGroup(Chref, "Deck_Near_Ship", "goto", "goto9");
	}

	if(CheckAttribute(pchar,"GenQuest.CaptainComission")) Rank = sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE); 
    
    for (int i=1; i<5; i++)
    {
        model = LAi_GetBoardingModel(Chref, &ani);
		cn = NPC_GenerateCharacter("saylor_0" + i, model, "man", ani, Rank, sti(Chref.nation), 0, true, "soldier");
		sld = &Characters[cn];
        LAi_SetWarriorType(sld); 
    	LAi_warrior_DialogEnable(sld, true);
	    sld.name    = "Sailor";
	    sld.lastname = "";
        sld.Dialog.Filename = "Quest\sailors_dialog.c";
    	sld.Dialog.CurrentNode = "On_Deck";
    	sld.greeting = "sea_sailors";
	}

	ChangeCharacterAddressGroup(characterFromID("saylor_01"), "Deck_Near_Ship", "goto", "goto8");
	ChangeCharacterAddressGroup(characterFromID("saylor_02"), "Deck_Near_Ship", "goto", "goto3");
	ChangeCharacterAddressGroup(characterFromID("saylor_03"), "Deck_Near_Ship", "goto", "goto6");
	ChangeCharacterAddressGroup(characterFromID("saylor_04"), "Deck_Near_Ship", "goto", "goto7");
}

void DeleteNPCfromDeck()
{
    int i;
    ref Cref;
    
    for (i=0; i< TOTAL_CHARACTERS; i++)
    {
        Cref = GetCharacter(i);

        if (CheckAttribute(Cref, "location"))
        {
            if (Cref.location == "Deck_Near_Ship")
            {
               Cref.location = "none";
               
               
               if (CheckAttribute(Cref, "Dialog.Filename") && Cref.Dialog.Filename == "Capitans_dialog.c")
               {
                   Cref.Dialog.Filename    = Cref.Bak.Dialog.Filename;
                   Cref.Dialog.CurrentNode = Cref.Bak.Dialog.CurrentNode;
               }
            }
        }
    }
}


void SetPrisonerLocationToNone()
{
    ref offref;
    int i, cn;

    ref mchr = GetMainCharacter();

    for (i=0; i < GetPassengersQuantity(mchr); i++)
    {
        cn = GetPassenger(mchr,i);
        if(cn != -1)
        {
            offref = GetCharacter(cn);
            if(CheckAttribute(offref,"prisoned"))
            {
	            if(sti(offref.prisoned)==true && GetRemovable(offref)) 
	            {
			        offref.location = "none";
                }
            }
        }
    }
}

void SetPrisonerInHold()
{
    
	ref offref;
    int i, cn;

    ref mchr = GetMainCharacter();

    for (i=0; i < GetPassengersQuantity(mchr); i++)
    {
        cn = GetPassenger(mchr,i);
        if(cn != -1)
        {
            offref = GetCharacter(cn);
            if(CheckAttribute(offref,"prisoned"))
            {
	            if(sti(offref.prisoned)==true && GetRemovable(offref)) 
	            {
                    PlaceCharacter(offref, "goto", mchr.location);
                }
            }
        }
    }
}

void SetOfficersInCampusToNone()
{
    ref offref;
    int i, cn;

    ref mchr = GetMainCharacter();

    for (i=0; i < GetPassengersQuantity(mchr); i++)
    {
        cn = GetPassenger(mchr,i);
        if(cn != -1)
        {
            offref = GetCharacter(cn);
            if (!CheckAttribute(offref,"prisoned") || sti(offref.prisoned) == false)
            {
	            if (GetRemovable(offref) && !IsOfficer(offref))  
	            {
			        offref.location = "none";
                }
            }
        }
    }
}
void SetOfficersInCampus()
{
    
	ref offref;
    int i, cn;

    ref mchr = GetMainCharacter();

    for (i=0; i < GetPassengersQuantity(mchr); i++)
    {
        cn = GetPassenger(mchr,i);
        if(cn != -1)
        {
            offref = GetCharacter(cn);
            if (!CheckAttribute(offref,"prisoned") || sti(offref.prisoned) == false)
            {
	            if (GetRemovable(offref) && !IsOfficer(offref))  
	            {
                    LAi_SetCitizenType(offref);
					PlaceCharacter(offref, "goto", mchr.location);
                }
            }
        }
    }

	
 	  
	
}
