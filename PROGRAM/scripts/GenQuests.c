

#define ShipSituation_0				0 	
#define ShipSituation_1				1	
#define ShipSituation_2				2	
#define ShipSituation_3				3	
#define ShipSituation_4				4	

int iGenRank;
string sGenLocation, sGenlocator, sGenBlade, sGenGun, sQuestTitle;

void Rat_GenerateRat()
{
	 
	
	ref rChar;
	int iRatCount = 1; 
	for(int i=1; i<=iRatCount; i++)
	{
		rChar = GetCharacter(NPC_GenerateCharacter("Test_Rat_"+i, "rat", "man", "rat", sti(PChar.rank)*5, PIRATE, -1, false, "citizen"));
		SetFantomParamFromRank(rChar, sti(PChar.rank)*5, true); 
		rChar.Dialog.FileName = "GenQuests_Dialog.c";
		LAi_SetStayType(rChar); 
		ChangeCharacterAddressGroup(rChar, PChar.location, "reload", FindNearestFreeLocator("reload")); 
	}
}




void ContraDeliverQuest_EnterToTavernRoom(string sQuest) 
{
	sGenLocation = PChar.GenQuest.ContraDeliver.ToColony;
	LocatorReloadEnterDisable(sGenLocation + "_Tavern", "reload2_back", true); 
	chrDisableReloadToLocation = true;
	bDisableFastReload         = true;
	DoQuestFunctionDelay("ContraDeliverQuest_ReloadConterToRoom", 3.0); 
}

void ContraDeliverQuest_ReloadConterToRoom(string sQuest) 
{
	ref rChar = GetCharacter(NPC_GenerateCharacter("ContraDeliverQuest_Contra_1", PChar.GenQuest.ContraDeliver.Model, "man", PChar.GenQuest.ContraDeliver.Model.Animation, sti(PChar.rank)*2, PIRATE, 0, true, "marginal"));
	rChar.DontClearDead = true;
	SetFantomParamFromRank(rChar, sti(PChar.rank)*2, true);
	rChar.Name = "Smuggler";
	rChar.LastName = "";
	rChar.greeting = "Gr_Smuggler Agent";
	LAi_SetActorType(rChar);
	rChar.Dialog.FileName = "GenQuests_Dialog.c";
	LAi_SetImmortal(rChar, true);
	ChangeCharacterAddressGroup(rChar, PChar.location, "reload", "reload1_back");
	LAi_ActorDialog(rChar, PChar, "", -1, 5);
}

void ContraDeliverQuest_ContraIsDead(string sQuest)
{
	ref rChar = &characters[GetCharacterIndex(sGenLocation + "_Smuggler")];
	rChar.model    = "citiz_" + (rand(9)+41); 
	FaceMaker(rChar);
	CirassMaker(rChar);
	chrDisableReloadToLocation = false;
	bDisableFastReload         = false;
	
	ChangeContrabandRelation(PChar, -10);
	sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
	AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "5");
	AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.ToColony + "Gen"));
	CloseQuestHeader(sQuestTitle);
	DeleteAttribute(PChar, "GenQuest.ContraDeliver");
}

void ContraDeliverQuest_GeneratePatrolToRoom()
{
	ref rChar;
	sGenLocation = PChar.GenQuest.ContraDeliver.ToColony;
	int iNation = sti(characters[GetCharacterIndex(sGenLocation + " Fort Commander")].nation);
	string sShortNation = NationShortName(iNation); 
	string sModel[3];
	sModel[0] = "off_" + sShortNation + "_1";
	sModel[1] = "sold_" + sShortNation + "_1";
	sModel[2] = "sold_" + sShortNation + "_2";
	string sGenGroup[3];
	sGenGroup[0] = "reload";
	sGenGroup[1] = "Quest";
	sGenGroup[2] = "Quest";
	string sGenLocatorArroy[3];
	sGenLocatorArroy[0] = "reload1_back";
	sGenLocatorArroy[1] = "Quest1";
	sGenLocatorArroy[2] = "Quest2";
	for(int i=0; i<=2; i++)
	{
		rChar = GetCharacter(NPC_GenerateCharacter("ContraDeliverQuest_Soldier_" + i, sModel[i], "man", "man", sti(PChar.rank)*2, iNation, 0, true, "soldier"));
		SetFantomParamFromRank(rChar, sti(PChar.rank)*2, true);
		rChar.Name = "Officer";
		rChar.LastName = "";
		rChar.Greeting = "soldier_arest";
		LAi_SetActorType(rChar);
		rChar.Dialog.FileName = "GenQuests_Dialog.c";
		LAi_SetImmortal(rChar, true);
		ChangeCharacterAddressGroup(rChar, PChar.location, sGenGroup[i], sGenLocatorArroy[i]);
		if(i != 0) LAi_CharacterDisableDialog(rChar);
		else LAi_ActorDialog(rChar, PChar, "", -1, 5);
	}
	
	rChar = CharacterFromID("ContraDeliverQuest_Contra_1");
	LAi_ActorGoToLocator(rChar, "goto", "goto2", "", 3);
}

void ContraDeliverQuest_SoldiersGoOut()
{
	ref rChar;
	for(int i=0; i<=2; i++)
	{
		rChar = CharacterFromID("ContraDeliverQuest_Soldier_" + i);
		LAi_ActorGoToLocation(rChar, "reload", "reload1_back", "none", "", "", "", 3.0);
	}
	
	rChar = CharacterFromID("ContraDeliverQuest_Contra_1");
	PChar.GenQuest.CallFunctionParam = "ContraDeliverQuest_AfterSoldiersOut";
	LAi_ActorGoToLocation(rChar, "reload", "reload1_back", "none", "", "", "CallFunctionParam", 3.0);
}

void ContraDeliverQuest_AfterSoldiersOut()
{
	chrDisableReloadToLocation = false;
	bDisableFastReload         = false;
	sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
	AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "7");
	CloseQuestHeader(sQuestTitle);
	DeleteAttribute(PChar, "GenQuest.ContraDeliver");
}







void ContraMeetManQuest_InitStartParam() 
{
	if(rand(1) == 0)
	{
		Log_TestInfo("� ����� ����� ����� �������.");
		PChar.GenQuest.ContraMeetMan.SoldiersInShore = true;
	}
	else
	{
		Log_TestInfo("� ����� ������ �� �����.");
		if(rand(1) == 0)
		{
			Log_TestInfo("������� �������� ����������.");
			PChar.GenQuest.ContraMeetMan.ManIsTraitor = true;
		}
		else Log_TestInfo("� ���� ������ �� ����������, ��� ������� - ���������.");
	}
}

void ContraMeetManQuest_EnterToShore(string sQuest) 
{
	ref rChar;
	if(!CheckAttribute(PChar, "GenQuest.ContraMeetMan.SoldiersInShore")) 
	{
		rChar = GetCharacter(NPC_GenerateCharacter("ContraMeetManQuest_QuestMan", "citiz_"+(rand(9)+21), "man", "man", sti(PChar.rank)*2, PIRATE, -1, true, "citizen"));
		SetFantomParamFromRank(rChar, sti(PChar.rank)*2, true);
		rChar.Greeting = "cit_common";
		LAi_SetCitizenType(rChar);
		rChar.Dialog.FileName = "GenQuests_Dialog.c";
		rChar.DontClearDead = true;
		LAi_SetImmortal(rChar, true); 
		ChangeCharacterAddressGroup(rChar, PChar.location, "goto", "goto1");
	}
	else 
	{
		sGenLocation = PChar.GenQuest.ContraMeetMan.QuestTown;
		int iNation = sti(characters[GetCharacterIndex(sGenLocation + " Fort Commander")].nation);
		string sShortNation = NationShortName(iNation); 
		int iSoldCount = 4+rand(2);
		PChar.GenQuest.ContraMeetMan.SoldCount = iSoldCount; 
		for(int i=0; i<=iSoldCount; i++)
		{
			sGenlocator = LAi_FindRandomLocator("goto");
			if(i==0) 
			{
				rChar = GetCharacter(NPC_GenerateCharacter("ContraMeetManQuest_Officer_" + i, "off_"+sShortNation+"_1", "man", "man", sti(PChar.rank)*2, iNation, -1, true, "officer"));
				SetFantomParamFromRank(rChar, sti(PChar.rank)*2, true);
				rChar.Name = "Officer";
				rChar.LastName = "";
			}
			else 
			{
				rChar = GetCharacter(NPC_GenerateCharacter("ContraMeetManQuest_Soldier_" + i, "sold_"+sShortNation+"_1", "man", "man", sti(PChar.rank), iNation, -1, true, "soldier"));
				SetFantomParamFromRank(rChar, sti(PChar.rank), true);
				rChar.Name = "Soldier";
				rChar.LastName = "";
			}
			
			rChar.Greeting = "soldier_arest";
			LAi_SetCitizenType(rChar);
			rChar.Dialog.FileName = "GenQuests_Dialog.c";
			LAi_SetImmortal(rChar, true);
			ChangeCharacterAddressGroup(rChar, PChar.location, "goto", sGenlocator);
		}	
	}
}

void ContraMeetManQuest_DeletePatrolFromShore()
{
	int iSoldCount = sti(PChar.GenQuest.ContraMeetMan.SoldCount);
	ref rChar;
	for(int i=0; i<=iSoldCount; i++)
	{
		if(i==0) rChar = CharacterFromID("ContraMeetManQuest_Officer_"+i);
		else rChar = CharacterFromID("ContraMeetManQuest_Soldier_"+i);
		
		rChar.LifeDay = 0;
	}
}

void ContraMeetManQuest_TimeIsLeft(string sQuest) 
{
	DeleteQuestCondition("ContraMeetManQuest_EnterToShore"); 
	if(GetCharacterIndex("ContraMeetManQuest_QuestMan") != -1)
	{
		ref rChar = CharacterFromID("ContraMeetManQuest_QuestMan");
		rChar.LifeDay = 0;
		ChangeCharacterAddressGroup(rChar, "none", "", "");
	}
	
	if(CheckAttribute(PChar, "Quest.ContraMeetManQuest_EnterToTavernRoom"))
	{
		LocatorReloadEnterDisable(PChar.GenQuest.ContraMeetMan.QuestTown + "_tavern", "reload2_back", true); 
		DeleteQuestCondition("ContraMeetManQuest_EnterToTavernRoom");
	}
	
	sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
	AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "2");
	AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
	CloseQuestHeader(sQuestTitle);
	DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters");
	DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
}

void ContraMeetManQuest_EnterToTavernRoom(string sQuest)
{
	sGenLocation = PChar.GenQuest.ContraMeetMan.QuestTown;
	DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); 
	LocatorReloadEnterDisable(sGenLocation + "_Tavern", "reload2_back", true); 
	DisableAllExits(true);
	DoQuestFunctionDelay("ContraMeetManQuest_ReloadConterToRoom", 3.0);
}

void ContraMeetManQuest_ReloadConterToRoom(string sQuest)
{
	ref rChar;
	string sGenGroup[2];
	sGenGroup[0] = "reload";
	sGenGroup[1] = "Quest";
	string sGenLocatorArroy[2];
	sGenLocatorArroy[0] = "reload1_back";
	sGenLocatorArroy[1] = "Quest2";
	for(int i=0; i<=1; i++)
	{
		rChar = GetCharacter(NPC_GenerateCharacter("ContraMeetManQuest_Contrick_" + i, "citiz_"+(rand(9)+41), "man", "man", sti(PChar.rank)*2, PIRATE, 0, true, "hunter"));
		SetFantomParamFromRank(rChar, sti(PChar.rank)*2, true);
		rChar.Name = "Smuggler";
		rChar.LastName = "";
		rChar.Greeting = "Gr_Smuggler Agent";
		LAi_SetActorType(rChar);
		rChar.Dialog.FileName = "GenQuests_Dialog.c";
		LAi_SetImmortal(rChar, true);
		rChar.SuperShooter  = true; 
		ChangeCharacterAddressGroup(rChar, PChar.location, sGenGroup[i], sGenLocatorArroy[i]);
		if(i != 0) LAi_CharacterDisableDialog(rChar);
		else LAi_ActorDialog(rChar, PChar, "", -1, 5);
	}
	
	rChar = CharacterFromID("ContraMeetManQuest_QuestMan"); 
	LAi_ActorGoToLocator(rChar, "goto", "goto2", "", 3);
}

void ContraMeetManQuest_ContersGoQut() 
{
	ref rChar;
	for(int i=0; i<=1; i++)
	{
		if(GetCharacterIndex("ContraMeetManQuest_Contrick_"+i) != -1 && !LAi_isDead(CharacterFromID("ContraMeetManQuest_Contrick_"+i)))
		{
			rChar = CharacterFromID("ContraMeetManQuest_Contrick_" + i);
			LAi_Type_Actor_Reset(rChar);
			LAi_ActorGoToLocation(rChar, "reload", "reload1_back", "none", "", "", "", 3.0);
		}
	}
	
	PChar.GenQuest.CallFunctionParam = "ContraMeetManQuest_AfterContersOut";
	rChar = CharacterFromID("ContraMeetManQuest_QuestMan");
	LAi_Type_Actor_Reset(rChar);
	LAi_ActorGoToLocation(rChar, "reload", "reload1_back", "none", "", "", "CallFunctionParam", 3.0);
}

void ContraMeetManQuest_AfterContersOut()
{
	DisableAllExits(false); 
	ref rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
	SaveCurrentNpcQuestDateParam(rChar, "work_date");
}

void ContraMeetManQuest_ContraBeatMan() 
{
	LAi_Group_Delete("ContraMeetManQuest_Group1"); 
	LAi_Group_Delete("ContraMeetManQuest_Group2");
	DisableAllExits(false); 
	ref rChar = CharacterFromID("ContraMeetManQuest_QuestMan");
	rChar.LifeDay = 0;
	LAi_SetImmortal(rChar, false);
	LAi_Group_MoveCharacter(rChar, "ContraMeetManQuest_Group1");
	for(int i=0; i<=1; i++)
	{
		rChar = CharacterFromID("ContraMeetManQuest_Contrick_"+i);
		LAi_Group_MoveCharacter(rChar, "ContraMeetManQuest_Group2");
	}
	LAi_Group_SetRelation("ContraMeetManQuest_Group1", "ContraMeetManQuest_Group2", LAI_GROUP_ENEMY);
	LAi_Group_FightGroups("ContraMeetManQuest_Group1", "ContraMeetManQuest_Group2", true);
	SetFunctionNPCDeathCondition("ContraMeetManQuest_ContraBeatMan_Complete", "ContraMeetManQuest_QuestMan", false);
}

void ContraMeetManQuest_ContraBeatMan_Complete(string sQuest)
{
	
	if(GetCharacterIndex("ContraMeetManQuest_Contrick_0") == -1 || GetCharacterIndex("ContraMeetManQuest_Contrick_1") == -1) return;
		
	ref rChar;
	for(int i=0; i<=1; i++)
	{
		rChar = CharacterFromID("ContraMeetManQuest_Contrick_"+i);
		LAi_SetActorType(rChar);
		LAi_ActorGoToLocation(rChar, "reload", "reload1_back", "none", "", "", "", 3.0);
	}
}

void ContraMeetManQuest_PlayerBeatContra()
{
	LAi_Group_Delete("ContraMeetManQuest_Group1"); 
	ref rChar = CharacterFromID("ContraMeetManQuest_QuestMan");
	rChar.LifeDay = 0;
	LAi_Group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
	for(int i=0; i<=1; i++)
	{
		rChar = CharacterFromID("ContraMeetManQuest_Contrick_"+i);
		LAi_SetImmortal(rChar, false);
		LAi_Group_MoveCharacter(rChar, "ContraMeetManQuest_Group1");
	}
	LAi_Group_SetRelation("ContraMeetManQuest_Group1", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_Group_FightGroups("ContraMeetManQuest_Group1", LAI_GROUP_PLAYER, true);
	LAi_SetFightMode(PChar, true);
	ChangeContrabandRelation(PChar, -15); 
	SetGameModeCondition("ContraMeetManQuest_CheckContraDead");
}

void ContraMeetManQuest_CheckContraDead()
{
	if(LAi_isDead(CharacterFromID("ContraMeetManQuest_Contrick_0")) && LAi_isDead(CharacterFromID("ContraMeetManQuest_Contrick_1")))
	{
		DeleteGameModeCondition("ContraMeetManQuest_CheckContraDead");
		Log_TestInfo("��������������� �����.");
		LAi_SetFightMode(PChar, false);
		LAi_LocationFightDisable(LoadedLocation, true);
		ref rChar = CharacterFromID("ContraMeetManQuest_QuestMan");
		PChar.GenQuest.ContraMeetMan.ContraIsDead = true;
		LAi_SetActorType(rChar);
		LAi_ActorDialog(rChar, PChar, "", -1, 5);	
	}
}







void CitizenFindItemMiniQuest_CheckItem()
{
	if(CheckCharacterItem(PChar, "DOjeronRing")) 
	{
		DeleteGameModeCondition("CitizenFindItemMiniQuest_CheckItem");
		PChar.GenQuest.CitizenFindItem.GiveItem = true; 
		string sCity = XI_ConvertString("Colony" + PChar.GenQuest.CitizenFindItem.City + "Gen");
		Log_Info("I found the girl's ring from " + sCity + ".");
	}
}

void CitizenFindItemMiniQuest_Timer(string sQuest)
{
	DeleteGameModeCondition("CitizenFindItemMiniQuest_CheckItem");
	if(CheckAttribute(PChar, "GenQuest.CitizenFindItem.GiveItem")) 
	{
		RemoveItems(PChar, "DOjeronRing", 1);
		BackItemDescribe("DOjeronRing");
		items[FindItem("DOjeronRing")].Name = "itmname_DOjeronRing";
		DeleteAttribute(&items[FindItem("DOjeronRing")], "City");
	}
	else
	{
		string sCity = PChar.GenQuest.CitizenFindItem.City + + "_ExitTown";
		string sTemp = PChar.GenQuest.CitizenFindItem.ItemLocator;
		PChar.GenQuestRandItem.(sCity).(sTemp) = "potionrum";
		BackItemDescribe("DOjeronRing");
		items[FindItem("DOjeronRing")].Name = "itmname_DOjeronRing";
		DeleteAttribute(&items[FindItem("DOjeronRing")], "City");
	}
}







void Church_GenQuest1_Timer(string sQuest)
{
	if(GetCharacterIndex("ChurchGenQuest1_Cap") != -1) 
	{
		ref sld = CharacterFromID("ChurchGenQuest1_Cap");
		ChangeCharacterAddressGroup(sld, "none", "", ""); 
	}
	items[FindItem("Bible")].Name = "itmname_bible"; 
	BackItemDescribe("Bible");
	DeleteAttribute(items[FindItem("Bible")], "City");
	Group_DeleteGroup("ChurchGenQuest1_CapGroup"); 
	PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = "yes";
	PChar.GenQuest.ChurchQuest_1.Complete.Timer = true;
	AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "14");
	CloseQuestHeader(sQuestTitle);
}

void Church_GenQuest1_ChangeCapitanLocation(string sQuest)
{
	if(GetCharacterIndex("ChurchGenQuest1_Cap") == -1) return; 
	ref sld = CharacterFromID("ChurchGenQuest1_Cap");
	if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern")) 
	{
		PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = "yes";
		sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1";
		return;
	}
	
	sld.Dialog.Filename = "GenQuests_Dialog.c";
	sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
	sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1";
	FreeSitLocator(PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern", "Sit1");
	ChangeCharacterAddressGroup(sld, PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern", "sit", "Sit1");
	LAi_SetSitType(sld);
}

void Church_GenQuest1_DeleteCapitan(string sQuest)
{
	ref sld = CharacterFromID("ChurchGenQuest1_Cap");
	Group_DeleteGroup("ChurchGenQuest1_CapGroup");
	PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = "yes";
	sld.LifeDay = 0;
}







void Church_GenQuest2_GenerateBandits(string sQuest)
{
	Log_TestInfo("����� � ������� � ���������");

	ref location = &locations[reload_location_index];
	LAi_LocationFightDisable(location, true);
	string encGenGroup = LAi_FindRandomLocator("encdetector");
	string sGenTemp = "locators." + encGenGroup;
	string sLocGroup;
	aref arGenAll;
	makearef(arGenAll, location.(sGenTemp));
	
	int iBanditsCount = GetAttributesNum(arGenAll); 
	if (iBanditsCount <= 0) iBanditsCount = 1;
	if (iBanditsCount >= 4) iBanditsCount = 3 + rand(1);	
	
	iGenRank = GetCoffDiff(sti(PChar.rank), 1000);
	if (iGenRank < MOD_SKILL_ENEMY_RATE) iGenRank = MOD_SKILL_ENEMY_RATE;
	
	PChar.GenQuest.ChurchQuest_2.BanditsCount = iBanditsCount;
	if(LAi_GetLocatorNum("encdetector") > 0) 	sLocGroup = "encdetector";
	else										sLocGroup = "goto";
	
	for(int i=0; i<iBanditsCount; i++)
	{
		ref rChar = GetCharacter(NPC_GenerateCharacter("Church_GenQuest2_Bandit_" + i, "citiz_" + (rand(9)+41), "man", "man", iGenRank, PIRATE, -1, true, "marginal"));
		if(i == 0) 
		{
			rChar.SaveItemsForDead = true; 
			rChar.DontClearDead = true;
		}
		SetFantomParamFromRank(rChar, iGenRank, true);



		PlaceCharacter(rChar, sLocGroup, pchar.location);
		LAi_SetGuardianType(rChar);
		rChar.Dialog.FileName = "GenQuests_Dialog.c";
		LAi_SetImmortal(rChar, true);
		LAi_SetActorType(rChar);
		if (i == 0) LAi_ActorDialog(rChar, pchar, "", -1, 5); 
		else
		{	
			LAi_CharacterDisableDialog(rChar);
			LAi_ActorFollow(rChar, CharacterFromID("Church_GenQuest2_Bandit_0"), "", -1);
		}	
	}
	PChar.Quest.Church_GenQuest2_TimeIsLeft.over = "yes";
	chrDisableReloadToLocation = true;	
	

}

void Church_GenQuest2_Dialog_With_Bandits(string sQuest)
{
	int iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
	for(int i=0; i<iBanditsCount; i++)
	{
		ref rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
		LAi_SetActorType(rChar);
		if (rChar.id == "Church_GenQuest2_Bandit_0")
			LAi_ActorDialog(rChar, PChar, "", -1, 5);
		else
			LAi_ActorFollow(rChar, CharacterFromID("Church_GenQuest2_Bandit_0"), "", -1);
		
	}
	
	
	PChar.Quest.Church_GenQuest2_TimeIsLeft.over = "yes";
	chrDisableReloadToLocation = true;
}

void Church_GenQuest2_DeadBandits(string sQuest)
{
	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant"))
	{
		sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
		PChar.GenQuest.ChurchQuest_2.Complete.Short_With_Mon = true;	
		Delay_DeleteGroup("Church_GenQuest2_Bandits_Group");
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "3");
		Log_TestInfo("�������� ��������. ����� �������� ������� � ����� ���������� (����� ������� �� ��������� ��������).");
	}
	
	DeleteAttribute(LoadedLocation, "DisableEncounters");
	chrDisableReloadToLocation = false;
}

void Church_GenQuest2_TimeIsLeft(string sQuest) 
{
	Log_TestInfo("����� �����, �� �� ������ �������� ���������� - ����� ��������.");
	
	
	if(!CheckAttribute(PChar, "Quest.Church_GenQuest2_GenerateBandits"))
	{
		int iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
		
		for(int i=0; i<iBanditsCount; i++)
		{
				ref rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				rChar.Dialog.CurrentNode = "Left_Time_Case";
				rChar.LifeDay = 0;
		}
	}
	
	PChar.Quest.Church_GenQuest2_GenerateBandits.over = "yes";
	PChar.Quest.Church_GenQuest2_Dialog_With_Bandits.over = "yes";
	ChangeCharacterComplexReputation(PChar,"nobility", -3);
	sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
	AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "13");
	AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","��"));
	AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
	CloseQuestHeader(sQuestTitle);
	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestGangJungle")) 
	{
		LAi_LocationFightDisable(&locations[FindLocation(PChar.GenQuest.ChurchQuest_2.QuestGangJungle)], false);
		DeleteAttribute(&locations[FindLocation(PChar.GenQuest.ChurchQuest_2.QuestGangJungle)], "DisableEncounters");
	}
	
	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestGangShore")) 
	{
		LAi_LocationFightDisable(&locations[FindLocation(PChar.GenQuest.ChurchQuest_2.QuestGangShore)], false);
		DeleteAttribute(&locations[FindLocation(PChar.GenQuest.ChurchQuest_2.QuestGangShore)], "DisableEncounters");
	}
	DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");	
}

void Church_GenQuest2_BanditsIsEnemies_2_Clear(string sQuest)
{
	Delay_DeleteGroup("Church_GenQuest2_Bandits_Group");
}







void ReasonToFast_CheckHorse(string qName)
{
	if(!CheckAttribute(pchar, "questTemp.ReasonToFast.speakHorse"))
	{
		DeleteAttribute(pchar, "questTemp.ReasonToFast");
	}	
}

void ReasonToFast_MeetPatrolShore(string qName) 
{
	aref grp;
	ref chr, rCharacter;
	string encGroup, str, locator;
	int num, i, iNation, n;
	int iRank = sti(pchar.rank);
	ref pLoc;
	bool bOk = false;

	pLoc = &locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)];
	encGroup = LAi_FindRandomLocator("encdetector");
	str = "locators." + encGroup;
	makearef(grp, pLoc.(str));
	iNation = sti(pchar.questTemp.ReasonToFast.GuardNation); 
	num = GetAttributesNum(grp); 
	if (num <= 0) num = 1;
	
	str = "Patrol"+ pLoc.index + "_";
	string sGroup = "PatrolGroup_" + pLoc.index; 
	LAi_group_SetLookRadius(sGroup, 30);
	LAi_group_SetHearRadius(sGroup, 30);	

	pchar.questTemp.ReasonToFast = "MeetPatrol";
	for (i = 0; i < num; i++)
	{
		if (i == 0)
		{					
			int iPatrolOfficer = NPC_GenerateCharacter(str + i, "off_"+NationShortName(iNation)+"_"+(rand(1)+1), "man", "man", iRank + 2, iNation, 1, true, "officer");
			chr = &characters[iPatrolOfficer];
			SetFantomParamFromRank(chr, iRank + 2, true);
			chr.greeting = "soldier_arest";
			chr.dialog.filename = "Enc_Patrol.c";				
			if(GetOfficersQuantity(pchar) > 0) 
			{
				chr.dialog.currentnode = "First Time";
				pchar.questTemp.ReasonToFast = "MeetPatrolFail";
			}	
			else 
			{
				if(sti(pchar.questTemp.ReasonToFast.p1) < GetCharacterSPECIAL(pchar, "LUCK") * 10)	
				{
					chr.dialog.currentnode = "First Time";
					pchar.questTemp.ReasonToFast = "MeetPatrolFail";
				}
				else
				{
					chr.dialog.currentnode = "Reason_To_Fast_1";
					bOk = true;
				}	
			}
		}
		else
		{
			if (i == 3)
			{
				chr = GetCharacter(NPC_GenerateCharacter(str + i, "mush_" + NationShortName(iNation) + "_" +(rand(2)+1), "man", "mushketer", iRank, iNation, 1, false, "soldier"));
				chr.dialog.filename = "Enc_Patrol.c";				
				chr.dialog.currentnode = "Node_2";
			}
			else
			{
				chr = GetCharacter(NPC_GenerateCharacter(str + i, "sold_"+NationShortName(iNation)+"_"+(rand(7)+1), "man", "man", iRank, iNation, 1, true, "soldier"));
				SetFantomParamFromRank(chr, iRank, true);
				chr.dialog.filename = "Enc_Patrol.c";				
				chr.dialog.currentnode = "Node_2";
			}
		}	
		chr.City = pchar.questTemp.ReasonToFast.city;
		chr.CityType = "soldier";
		chr.EncQty = num;		
		LAi_SetStayType(chr);
		LAi_group_MoveCharacter(chr, sGroup);
		pchar.questTemp.ReasonToFast.LocIdx = pLoc.index; 
		pchar.questTemp.ReasonToFast.PatrolNum = num;
		
		locator = GetAttributeName(GetAttributeN(grp, i));
		ChangeCharacterAddressGroup(chr, pLoc.id, encGroup, locator);
		LAi_SetActorType(chr);
		if (i == 0) LAi_ActorDialog(chr, pchar, "", -1, 0); 
		else LAi_ActorFollow(chr, &characters[iPatrolOfficer], "", -1);
	}
	if(bOk) 
	{
		LAi_LocationFightDisable(pLoc, true);	
		LAi_SetFightMode(pchar, false);
		LAi_LockFightMode(pchar, true);
	}
}

void ReasonToFast_DeletePatrolFromShore(string qName) 
{
	ref pLoc, rChar;
	
	int iPatrolCount = sti(pchar.questTemp.ReasonToFast.PatrolNum);
	pLoc = &locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)];
	string str = "Patrol"+ pLoc.index + "_";
	string sTemp = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
	for(int i=0; i<iPatrolCount; i++)
	{
		if(i == 0) rChar = CharacterFromID(str + i);
		else rChar = CharacterFromID(str + i);		
		rChar.LifeDay = 0;
	}
	LAi_group_RemoveCheck(sTemp);
	LAi_group_Delete(sTemp);
}

void ReasonToFast_SpeakMayor(string qName)
{
	if(CheckAttribute(pchar,"questTemp.ReasonToFast.speakAfterPatrolDied") && pchar.questTemp.ReasonToFast.speakAfterPatrolDied == false)
	{
		AddQuestRecord("ReasonToFast", "13");			
		AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("��","���"));			
		CloseQuestHeader("ReasonToFast");
		DeleteAttribute(pchar, "questTemp.ReasonToFast");
	}
}

void ReasonToFast_GenerateHunter() 
{
	ref chr;
		
	int iRank = sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE);
	chr = GetCharacter(NPC_GenerateCharacter("ReasonToFast_Hunter", "mercen_"+(rand(14)+14), "man", "man", iRank, PIRATE, -1, true, "quest"));
	FantomMakeCoolFighter(chr, iRank, 80, 80, "blade_06", "pistol3", "grapeshot", 50);
	int jewelType = sti(pchar.questTemp.ReasonToFast.p4);
	string sItem = "jewelry" + jewelType; 
	AddItems(chr, sItem, 15); 
	chr.SaveItemsForDead = true;
	chr.dialog.Filename = "GenQuests_Dialog.c";
	chr.greeting = "Enc_Raiders"; 
	SetRandomNameToCharacter(chr);
	ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1");
	LAi_group_MoveCharacter(chr, "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx);
	
	LAi_SetActorType(pchar); 
	LAi_ActorTurnToCharacter(pchar, chr);
	LAi_SetActorType(chr);
	SetActorDialogAny2Pchar(chr.id, "", 0.0, 1.0);
	LAi_ActorFollow(chr, pchar, "ActorDialog_Any2Pchar", -1);	
}

int ReasonToFast_GetVictimShipType()
{
	string sTemp;	
	int iShipType = rand(4);
	switch (iShipType)
	{	
	    case 0: 		 
			iShipType = SHIP_BARQUE;     	
			sTemp = "Barque";
		break; 
	    case 1:  
			iShipType = SHIP_FLEUT;
			sTemp = "Fleut";
		break; 
	    case 2: 
			iShipType = SHIP_GALEON_L;         
			sTemp = "Galeon";
		break; 
	    case 3: 
			iShipType = SHIP_PINNACE; 			
			sTemp = "Pinnace";
		break;  	
		case 4: 
			iShipType = SHIP_CARACCA; 			
			sTemp = "Caracca";
		break;  	
	}
	pchar.questTemp.ReasonToFast.ShipTypeName = sTemp;
	
	return iShipType;
}

int ReasonToFast_GetVictimShipGoods()
{
	int iGoodIdx;
	switch (rand(6))
    {
        case 0 :
            iGoodIdx = GOOD_CHOCOLATE;
        break;
        case 1 :
            iGoodIdx = GOOD_TOBACCO;
        break;
        case 2 :
            iGoodIdx = GOOD_COFFEE;
        break;
        case 3 :
            iGoodIdx = GOOD_MAHOGANY;
        break;
        case 4 :
            iGoodIdx = GOOD_CINNAMON;
        break;
        case 5 :
            iGoodIdx = GOOD_EBONY;
        break;		
        case 6 :
            iGoodIdx = GOOD_COPRA;
        break;
    }
	return iGoodIdx;
}

void ReasonToFast_GenerateVictimShip(int iShipType, int iShipGoods) 
{
	int hcrew;
	int iNation = sti(pchar.questTemp.ReasonToFast.GuardNation);
	
	ref chref = GetCharacter(NPC_GenerateCharacter("VictimCap_1", "mercen_"+(rand(14)+1), "man", "man", 25, iNation, -1, true, "citizen"));

	chref.Ship.Name = pchar.questTemp.ReasonToFast.ShipName;			
    chref.Ship.Type = GenerateShipExt(iShipType, 1, chref);
    SetBaseShipData(chref);

    hcrew = GetMinCrewQuantity(chref);
    SetCrewQuantity(chref, hcrew);
    
    DeleteAttribute(chref,"ship.sails");
    DeleteAttribute(chref,"ship.masts");
    DeleteAttribute(chref,"ship.blots");
    DeleteAttribute(chref,"ship.hulls");
	
	Fantom_SetCannons(chref, "trade");
    Fantom_SetBalls(chref, "trade");
	
	int iSpace = GetCharacterFreeSpace(chref, iShipGoods);
	Fantom_SetCharacterGoods(chref, iShipGoods, iSpace, 1);
	
	string sGroup = "Sea_Victim_1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
    Group_SetType(sGroup, "trade");
        
    Group_AddCharacter(sGroup, "VictimCap_1");
    Group_SetGroupCommander(sGroup, "VictimCap_1");
	Group_SetAddress(sGroup, GetArealByCityName(pchar.questTemp.ReasonToFast.city),"quest_ships", "quest_ship_1");
	Group_SetTaskRunaway(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	
	pchar.quest.ReasonToFast_SetShip_1.win_condition.l1 = "Character_sink";
    pchar.quest.ReasonToFast_SetShip_1.win_condition.l1.character = "VictimCap_1";
    pchar.quest.ReasonToFast_SetShip_1.function = "ReasonToFast_KillVictim";
    
	pchar.quest.ReasonToFast_SetShip_2.win_condition.l1 = "Character_Capture";
    pchar.quest.ReasonToFast_SetShip_2.win_condition.l1.character = "VictimCap_1";
    pchar.quest.ReasonToFast_SetShip_2.function = "ReasonToFast_CaptureVictim";  
	
    SetTimerCondition("ReasonToFast_ClearVictim", 0, 0, 1, false);
}


void ReasonToFast_KillVictim(string qName)
{
	ref sld = characterFromId("VictimCap_1");
	sld.lifeDay = 0;
	pchar.quest.ReasonToFast_ClearVictim.over = "yes";
	pchar.quest.ReasonToFast_SetShip_1.over = "yes";
	pchar.quest.ReasonToFast_SetShip_2.over = "yes";
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	AddQuestRecord("ReasonToFast","19");
	CloseQuestHeader("ReasonToFast");
	Group_DeleteGroup("Sea_Victim_1");
	DeleteAttribute(pchar,"questTemp.ReasonToFast");
}


void ReasonToFast_CaptureVictim(string qName)
{
	ref sld = characterFromId("VictimCap_1");
	sld.lifeDay = 0;
	AddQuestRecord("ReasonToFast","18");
	Group_DeleteGroup("Sea_Victim_1");
	pchar.questTemp.ReasonToFast.SpeakOther = true; 
	pchar.quest.ReasonToFast_ClearVictim.over = "yes";
	pchar.quest.ReasonToFast_SetShip_1.over = "yes";
	pchar.quest.ReasonToFast_SetShip_2.over = "yes";
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
    pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";    
}

void ReasonToFast_RemoveVictim()
{
	ref sld = characterFromId("VictimCap_1");
	sld.lifeDay = 0;
	Group_DeleteGroup("Sea_Victim_1"); 
	pchar.quest.ReasonToFast_ClearVictim.over = "yes";	
	pchar.quest.ReasonToFast_SetShip_1.over = "yes";
	pchar.quest.ReasonToFast_SetShip_2.over = "yes";
	DeleteAttribute(pchar, "GenQuest.CannotWait");
}

void ReasonToFast_PreparePirateShip(string qName) 
{
	ref sld;
	int iRank = sti(pchar.rank) + 5 + rand(MOD_SKILL_ENEMY_RATE);
	int iShipRank, iShipType;
	string sTemp, sTemp1;

    if(makeint(pchar.rank) > 13) { iShipRank = rand(2) + 3; }
    if(makeint(pchar.rank) > 6 && makeint(pchar.rank) < 13) { iShipRank = rand(2); }	
	if(makeint(pchar.rank) < 7) { iShipRank = rand(1); }
	
	switch (iShipRank)
	{	
	    case 0: 		 
			iShipType = SHIP_SCHOONER_W;     	
			sTemp1 = "schooner";
		break; 		
	    case 1:  
			iShipType = SHIP_BRIG;     		
			sTemp1 = "brig";
		break; 		
	    case 2:  
			iShipType = SHIP_BRIGANTINE;
			sTemp1 = "brigantine";
		break; 
	    case 3: 
			iShipType = SHIP_CORVETTE; 	
			sTemp1 = "corvette";
		break; 
	    case 4: 
			iShipType = SHIP_FRIGATE;         
			sTemp1 = "frigate";
		break; 
	    case 5: 
			iShipType = SHIP_LINESHIP; 			
			sTemp1 = "ship-of-the-line";
		break;  	
	}
		
	Log_QuestInfo("������� ��������� ������� �� ��������.");
	
	sld = GetCharacter(NPC_GenerateCharacter("PirateCapt", "mercen_"+(rand(14)+14), "man", "man", iRank, PIRATE, 30, true, "quest"));	
	sld.dialog.filename      = "GenQuests_Dialog.c";
	sld.dialog.currentnode   = "ReasonToFast_FightCap";
	sTemp = GenerateRandomNameToShip(PIRATE);
	FantomMakeCoolSailor(sld, iShipType, sTemp, CANNON_TYPE_CULVERINE_LBS18, 50+rand(40), 50+rand(40), 50 + rand(40));
	sld.cirassId = Items_FindItemIdx("cirass1");  
    FantomMakeCoolFighter(sld, makeint(pchar.rank) + rand(10) + 5, 60 + rand(30), 50, "blade_06", "pistol3","grapeshot", 80);
		
    sld.SuperShooter  = true;
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Energaiser"); 					
	
	LAi_SetHP(sld, 100 + makeint(pchar.rank) * 2, 100 + makeint(pchar.rank) * 2);

	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "quest_ship"; 
	sld.mapEnc.Name = sTemp1 + " '" + sTemp + "'";
	
	sld.ship.Crew.Morale = 60 + rand(20);
	ChangeCrewExp(sld, "Sailors", 60 + rand(20));
	ChangeCrewExp(sld, "Cannoners", 60 + rand(20));
	ChangeCrewExp(sld, "Soldiers", 60 + rand(20));
	
	string sGroup = "Quest_Ship";  
	Group_DeleteGroup(sGroup);
    Group_FindOrCreateGroup(sGroup);
	Group_AddCharacter(sGroup, "PirateCapt");
    Group_SetGroupCommander(sGroup, "PirateCapt");

	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_SetTaskAttack(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	
	SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);
	
	Map_CreateWarrior("", "PirateCapt", 7);

    pchar.quest.ReasonToFast_PirateShip_Dead.win_condition.l1 = "NPC_Death";
	pchar.quest.ReasonToFast_PirateShip_Dead.win_condition.l1.character = "PirateCapt";
	pchar.quest.ReasonToFast_PirateShip_Dead.function = "ReasonToFast_PirateCapt_Dead";
	
	pchar.quest.ReasonToFast_PirateShip_Sink.win_condition.l1 = "Character_sink";
    pchar.quest.ReasonToFast_PirateShip_Sink.win_condition.l1.character = "PirateCapt";
    pchar.quest.ReasonToFast_PirateShip_Sink.function = "ReasonToFast_PirateCapt_Sink";
}

void ReasonToFast_PirateCapt_Dead(string qName)
{
	ref sld = characterFromId("PirateCapt");
	sld.lifeDay = 0;
	pchar.quest.ReasonToFast_PirateShip_Sink.over = "yes";
	pchar.quest.ReasonToFast_PirateShip_Dead.over = "yes";
	AddQuestRecord("ReasonToFast","22");
	AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT));
	CloseQuestHeader("ReasonToFast");
	DeleteAttribute(pchar,"questTemp.ReasonToFast");
}

void ReasonToFast_PirateCapt_Sink(string qName)
{
	ref sld = characterFromId("PirateCapt");
	sld.lifeDay = 0;
	pchar.quest.ReasonToFast_PirateShip_Sink.over = "yes";
	pchar.quest.ReasonToFast_PirateShip_Dead.over = "yes";
	AddQuestRecord("ReasonToFast","25");
	AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT));
	CloseQuestHeader("ReasonToFast");
	DeleteAttribute(pchar,"questTemp.ReasonToFast");
}

void ReasonToFast_SetHunterCoastal()
{
	pchar.quest.ReasonToFast_SetHunterPort_1.win_condition.l1 = "Location_Type";
	pchar.quest.ReasonToFast_SetHunterPort_1.win_condition.l1.location_type = "town"; 
	pchar.quest.ReasonToFast_SetHunterPort_1.function = "ReasonToFast_SetTreasureHunter";
	
	pchar.quest.ReasonToFast_SetHunterPort_2.win_condition.l1 = "Location_Type";
	pchar.quest.ReasonToFast_SetHunterPort_2.win_condition.l1.location_type = "seashore"; 
	pchar.quest.ReasonToFast_SetHunterPort_2.function = "ReasonToFast_SetTreasureHunter";
}

void ReasonToFast_SetTreasureHunter(string qName)
{
    int    j, i, k;
	string sTemp, sCapId, sLocGroup;
	ref    sld;
	bool   ok;

	pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
	pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
	
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); 
	
	Pchar.GenQuest.Hunter2Pause  = true;	
	sCapId = "LandHunter0";
	sTemp = "LAND_HUNTER";
	ok = true;
	arrayNPCModelHow = 0;
	
    for (i = 1; i <= 3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", 5, PIRATE, 1, true, "hunter"));
        SetFantomParamHunter(sld); 
        sld.dialog.filename = "Hunter_dialog.c";
		if(pchar.questTemp.ReasonToFast == "GetMap" || pchar.questTemp.ReasonToFast == "LakeyExitSuccess") 
		{
			sld.Dialog.CurrentNode = "ReasonToFast_HunterShore1";
		}
		if(pchar.questTemp.ReasonToFast == "LakeyExitFail") 
		{
			sld.Dialog.CurrentNode = "ReasonToFast_HunterShore2";
		}
		if(pchar.questTemp.ReasonToFast == "GetTreasure") 
		{
			sld.Dialog.CurrentNode = "ReasonToFast_THunter_1";
		}	
        sld.greeting = "hunter";
        sld.location = "none"; 
		
		SetModelPirate(sld);
        k = 0;
		while (!CheckNPCModelUniq(sld) && k < 10)
		{
		    k++;
			SetModelPirate(sld);
		}
		arrayNPCModel[arrayNPCModelHow] = sld.model;
		arrayNPCModelHow++;
		
		LAi_SetActorTypeNoGroup(sld);
		
		if(LAi_GetLocatorNum("goto") > 0) 	sLocGroup = "goto";
		else								sLocGroup = "encdetector";
		
		if (PlaceCharacter(sld, sLocGroup, "random_must_be_near") == "" && i == 1) 
        {
            ok = false;
            break;
        }
		LAi_ActorFollow(sld, pchar, "", 8.0);
        LAi_group_MoveCharacter(sld, sTemp);		
	}	
	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);

	LAi_group_ClearAllTargets();
	LAi_SetFightModeForOfficers(false);
	if (ok)
    {
        pchar.HunterCost.Qty = i;
        sld = characterFromID(sCapId + "1");
        LAi_type_actor_Reset(sld);
        LAi_ActorDialog(sld, pchar, "", 4.0, 0);
		chrDisableReloadToLocation = true;
		bDisableFastReload = true; 
    }				
}

void ReasonToFast_GenerateTreasureMap(ref item)
{
    item.MapIslId   = GetIslandForTreasure();
    item.MapLocId   = GetLocationForTreasure(item.MapIslId);
    item.MapBoxId   = GetBoxForTreasure(item.MapIslId, item.MapLocId);
	item.MapOwnId   = GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_NOM);
	
	DeleteAttribute(item, "BoxTreasure");

	pchar.questTemp.ReasonToFast.Treasure.Island = item.MapIslId;
	pchar.questTemp.ReasonToFast.Treasure.Location = item.MapLocId;
	pchar.questTemp.ReasonToFast.Treasure.Locator = item.MapBoxId;
	
    pchar.quest.ReasonToFast_SetTreasureFromMap.win_condition.l1  = "location";
    pchar.quest.ReasonToFast_SetTreasureFromMap.win_condition.l1.location = item.MapLocId;
    pchar.quest.ReasonToFast_SetTreasureFromMap.function = "ReasonToFast_SetTreasureBoxFromMap"; 
}

void ReasonToFast_ExitFromTownFight(string qName)
{
	Log_QuestInfo("��������� ����� �� ��������, ������� ������� � ��������");
	bQuestDisableMapEnter = true;
	QuestCloseSeaExit();
    DoQuestCheckDelay("ReasonToFast_MeetWithSailor", 1);
}

void ReasonToFast_SetTreasureBoxFromMap(string qName)
{
    aref   item;
    ref    loc;
    string box, itmName;
    aref   arToBox;
    aref   arFromBox;

    if (GetCharacterItem(pchar, "mapQuest") > 0 )
    {
        Log_Info("The treasures must be somewhere nearby!");
        PlaySound("interface\notebook.wav");
		Statistic_AddValue(pchar, "Treasure", 1);
		Achievment_SetStat(pchar, 8, 1);
		
        
        pchar.quest.ReasonToFast_SetTreasureHunter.win_condition.l1          = "ExitFromLocation";
        pchar.quest.ReasonToFast_SetTreasureHunter.win_condition.l1.location = pchar.location;
        pchar.quest.ReasonToFast_SetTreasureHunter.function    				= "ReasonToFast_SetTreasureHunter";   
		bDisableLandEncounters = true;	

        Items_FindItem("mapQuest", &item);
		
		itmName = "icollection"; 
		item.BoxTreasure.(itmName) = sti(pchar.questTemp.ReasonToFast.p8); 
		
		itmName = "Chest"; 
		item.BoxTreasure.(itmName) = sti(pchar.questTemp.ReasonToFast.p7); 

		itmName = "mineral5"; 
		item.BoxTreasure.(itmName) = rand(5) + 2;
		
		itmName = "mineral8"; 
		item.BoxTreasure.(itmName) = rand(7) + 4;
		
        box = item.MapBoxId;

        loc = &locations[FindLocation(item.MapLocId)];
        loc.(box).items = "";

        makearef(arToBox, loc.(box).items);
        makearef(arFromBox, item.BoxTreasure);
        CopyAttributes(arToBox, arFromBox);

        loc.(box) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
        loc.(box).Treasure =  true; 

        DeleteAttribute(item, "MapIslId");
        TakeNItems(pchar, "mapQuest", -1);
		pchar.questTemp.ReasonToFast = "GetTreasure";
    }
}

void ReasonToFast_ClearTreasureBox(string LocId)
{
	ref loc;
	aref boxLocator;
	string locatorName;
	
	loc = &locations[FindLocation(LocId)];
			
	for (int i=1; i < MAX_HANDLED_BOXES; i++)
	{		
		locatorName = "box"+i;
		if(!CheckAttribute(loc, locatorName)) break;
		DeleteAttribute(loc, locatorName + ".items");
		loc.(locatorName).items = "";
		loc.(locatorName).money = 0;	
		loc.(locatorName) = Items_MakeTime(0, 0, 1, 2003); 		
	}
}

int ReasonToFast_CheckTreasure(string ItmName, int ReqQty)
{
	ref loc;
	string locatorName, sName;
	aref arItems, arCur;
	int itemsQty;
	
	loc = &locations[FindLocation(pchar.questTemp.ReasonToFast.Treasure.Location)];
	locatorName = pchar.questTemp.ReasonToFast.Treasure.Locator;
	
	makearef(arItems, loc.(locatorName).items)
		
    int Qty = GetAttributesNum(arItems);
    for (int a = 0; a < Qty; a++)
    {
        sName = GetAttributeName(GetAttributeN(arItems, a));
		if(sName == ItmName)
		{
			arCur = GetAttributeN(arItems,a);
			itemsQty = sti(GetAttributeValue(arCur));
			return ReqQty - itemsQty;
		}
    }
	return ReqQty;
}

int ReasonToFast_CheckTreasureQty(string ItmName, int ReqQty)
{
	int iQty, iNeedQty = 0;
	int iPassenger, cn;
	ref sld;

	iQty = GetCharacterItem(pchar, ItmName);
	if(iQty > 0) 
	{
		iNeedQty += iQty;
		if(iNeedQty >= ReqQty) return iNeedQty;
	}
	for (int io = 0; io < GetPassengersQuantity(pchar); io++)
	{
		iPassenger = GetPassenger(pchar, io);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			iQty = GetCharacterItem(sld, ItmName);
			if(iQty > 0) 
			{
				iNeedQty += iQty;
				if(iNeedQty >= ReqQty) return iNeedQty;
			}
		}
	}	
	return iNeedQty;
}

void ReasonToFast_GetTreasure(string ItmName, int ReqQty)
{
	int iQty;
	int iPassenger, cn;
	ref sld;
	
	
	iQty = GetCharacterItem(pchar, ItmName);
	if(iQty > 0) 
	{
		TakeNItems(pchar, ItmName, -iQty);
		if(iQty == ReqQty) return;
		ReqQty = ReqQty - iQty;
	}	
	
	for (int io = 0; io < GetPassengersQuantity(pchar); io++)
	{
		iPassenger = GetPassenger(pchar, io);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			iQty = GetCharacterItem(sld, ItmName);
			if(iQty > 0) 
			{
				TakeNItems(sld, ItmName, -iQty);
				if(iQty == ReqQty) return;
				ReqQty = ReqQty - iQty;
			}
		}
	}
	
	for (int i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			sld = GetCharacter(cn);
			iQty = GetCharacterItem(sld, ItmName);
			if(iQty > 0) 
			{
				TakeNItems(sld, ItmName, -iQty);
				if(iQty == ReqQty) return;
				ReqQty = ReqQty - iQty;
			}
		}
	}
}

bool ReasonToFast_CreateResidenceNPC(aref loc)
{
	ref chr;
	int iBaseCity = FindLocation(loc.fastreload + "_town");
	int iNation = GetCityNation(pchar.questTemp.ReasonToFast.city);
	
	if (!CheckAttribute(&locations[iBaseCity], "houseEnc")) return false;
		
	if (CheckAttribute(loc, "PlayHall") || CheckAttribute(loc, "Bedroom") || (loc.id.label  == "TownhallRoom") || CheckAttribute(loc, "Office"))
	{	
		string slai_group = GetNationNameByType(iNation) + "_citizens";		
	
		if (GetCharacterIndex("ReasonToFastLakey_1") > 0) return false; 
		Log_QuestInfo("������� �����");		
		chr = GetCharacter(NPC_GenerateCharacter("ReasonToFastLakey_1", "barmen_"+(rand(15)+1), "man", "man", 5, iNation, 1, true, "citizen"));
		chr.dialog.Filename = "GenQuests_Dialog.c"; 
		chr.dialog.currentnode = "ReasonToFast_Lakey";
		chr.CityType = "citizen";
		chr.city = loc.fastreload; 
		chr.greeting = "worker";
		ChangeCharacterAddressGroup(chr, loc.id, "goto", "goto1");
		LAi_SetOwnerType(chr);
		LAi_group_MoveCharacter(chr, slai_group);	
		pchar.questTemp.ReasonToFast.LakeyLocation = loc.id;
		bDisableFastReload = true;
	}		
	return true;
}

void ReasonToFast_ClearLakey(string qName)
{
	AddQuestRecord("ReasonToFast","19");
	CloseQuestHeader("ReasonToFast");
	if (GetCharacterIndex("ReasonToFastLakey_1") > 0) 
	{
		ref sld = CharacterFromID("ReasonToFastLakey_1");
		sld.LifeDay = 0;
	}	
	DeleteAttribute(pchar,"questTemp.ReasonToFast");
}

void ReasonToFast_InitVariables()
{
	int s1, s2;

	pchar.questTemp.ReasonToFast.p1 = rand(100);
	pchar.questTemp.ReasonToFast.p2 = rand(100);
	pchar.questTemp.ReasonToFast.p3 = "l" + rand(GetNamesCount(NAMETYPE_MAIN) - 1); 	
	pchar.questTemp.ReasonToFast.p4 = rand(3) + 1; 	
	pchar.questTemp.ReasonToFast.p5 = (110 - GetSummonSkillFromName(pchar, SKILL_FORTUNE)) * MOD_SKILL_ENEMY_RATE * 1000;	
	pchar.questTemp.ReasonToFast.p6 = GenQuest_GenerateGoodBlade(); 
	s1 = GetCharacterSPECIAL(pchar,"Charisma");
	s1 = s1 - rand(makeint(s1/2));
	s2 = GetCharacterSPECIAL(pchar,"Intellect");
	s2 = s2 - rand(makeint(s2/2));
	pchar.questTemp.ReasonToFast.p7 = s1;
	pchar.questTemp.ReasonToFast.p8 = s2;	
	s1 = GetCharacterSPECIAL(pchar,"Charisma");
	s2 = GetCharacterSPECIAL(pchar,"Intellect");
	pchar.questTemp.ReasonToFast.p9 = 50 * (5 + s1 - 2 * rand(makeint(s1/2)) + (s2 - 2 * rand(makeint(s2/2))) * 4) * (200 + GetSummonSkillFromName(pchar, SKILL_COMMERCE));
	pchar.questTemp.ReasonToFast.p10 = 4500000 * (s1 + 4 * s2)/(200 + GetSummonSkillFromName(pchar, SKILL_COMMERCE));
	pchar.questTemp.ReasonToFast.target = rand(1);
	if(rand(1) == 0) 
	{ 
		pchar.questTemp.ReasonToFast.map = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1); 
		pchar.questTemp.ReasonToFast.mapIdx = NAMETYPE_NICK;
	}
	else
	{ 
		pchar.questTemp.ReasonToFast.map = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);
		pchar.questTemp.ReasonToFast.mapIdx = NAMETYPE_VIP;
	}
	
	if(CheckAttribute(pchar,"questTemp.ReasonToFast.speakOther")) DeleteAttribute(pchar,"questTemp.ReasonToFast.speakOther");
	if(CheckAttribute(pchar,"questTemp.ReasonToFast.speakAfterPatrolDied")) DeleteAttribute(pchar,"questTemp.ReasonToFast.speakAfterPatrolDied");
}







void BurntShipQuest_TimeIsOver(String _quest)
{
	ref character = CharacterFromID(PChar.Quest.(_quest).PortmanId);
	
	SetRandomNameToCharacter(character);
	character.model = "usurer_" + (rand(7) + 1);
	
	character.Quest.BurntShip.TimeIsOver = true;
}







void PiratesOnUninhabited_LocationExit(String _quest)
{
	int index;

	for(int i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
	{
		index = GetCharacterIndex("PirateOnUninhabited_" + i);
		
		if(index != -1)
		{
			Characters[index].LifeDay = 3;
			SaveCurrentNpcQuestDateParam(&Characters[index], "LifeTimeCreate");
		}
	}
	
	DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
}

void PiratesOnUninhabited_LocationExit_Good(String _quest)
{
	for(int i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
	{
		ChangeCharacterAddressGroup(CharacterFromID("PirateOnUninhabited_" + i), "none", "", "");
	}
}

void PiratesOnUninhabited_OnShore(String _quest)
{
	ref character;
	
	if(!CheckAttribute(LoadedLocation, "onUninhabitedIsland"))
	{
		for(int i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
		{
			character = CharacterFromID("PirateOnUninhabited_" + i);
			
			ChangeCharacterAddressGroup(character, PChar.location, "goto", "goto" + (i + 1));
			LAi_SetActorTypeNoGroup(character);
			
			if(i == 0)
			{
				if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureMap"))
				{
					if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.ClearShip")) 
					{
						character.dialog.currentnode = "PiratesOnUninhabited_12";
					}
					else
					{
						character.dialog.currentnode = "PiratesOnUninhabited_51";
					}
				}
				else
				{
					character.dialog.currentnode = "PiratesOnUninhabited_26";
				}
				
				LAi_ActorDialog(character, PChar, "", 7.0, 0.0);
			}
			else
			{
				LAi_ActorFollow(character, PChar, "", 7.0);
			}
		}
		
		
		PChar.Quest.PiratesOnUninhabited_OnShore.over = "yes";
		PChar.Quest.PiratesOnUninhabited_OnMayak.over = "yes";
	}
}

void PiratesOnUninhabited_TreasureLose(String _quest)
{
	PChar.GenQuest.PiratesOnUninhabited.TreasureLose = true;
}

void PiratesOnUninhabited_InTreasureLoc(String _quest)
{
	ref location = &Locations[FindLocation(PChar.GenQuest.PiratesOnUninhabited.TreasureShore)];
	ref character;
	String boxId = PChar.GenQuest.PiratesOnUninhabited.TreasureBox;
	String model[10];
	String attribute;
	aref boxItems;
	int i = 0;
	int count, temp, rank;
	
	model[0] = "citiz_41";
	model[1] = "citiz_42";
	model[2] = "citiz_43";
	model[3] = "citiz_44";
	model[4] = "citiz_45";
	model[5] = "citiz_46";
	model[6] = "citiz_47";
	model[7] = "citiz_48";
	model[8] = "citiz_49";
	model[9] = "citiz_50";
	
	makearef(boxItems, location.(boxId).items);
	
	Log_Info("The treasures must be somewhere nearby!");
	Statistic_AddValue(Pchar, "Treasure", 1);
	Achievment_SetStat(Pchar, 8, 1);
	
	PChar.Quest.PiratesOnUninhabited_TreasureLose.over = "yes";
	
	if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureLose"))
	{
		count = 2 + makeint(MOD_SKILL_ENEMY_RATE / 3) + dRand(1);
		
		PChar.GenQuest.PiratesOnUninhabited.ShorePiratesQty = count;
		
		rank = sti(PChar.rank);
		
		while(i < count)
		{
			temp = rand(9);
			
			if(model[temp] != "")
			{
				if(!CheckAttribute(location, "locators.goto.goto" + (i + 1))) 
				{
					PChar.GenQuest.PiratesOnUninhabited.ShorePiratesQty = i;
					break;
				}
				
				attribute = "l" + (i + 1);
				
				character = GetCharacter(NPC_GenerateCharacter("PirateOnUninhabited_ShorePirate" + i, model[temp], "man", "man", rank, PIRATE, -1, true, "marginal"));
				SetFantomParamFromRank(character, rank, true);
				ChangeCharacterAddressGroup(character, location.id, "goto", "goto" + (i + 1));
				character.dialog.filename = "GenQuests_Dialog.c";
				character.dialog.currentnode = "PiratesOnUninhabited_34";
				character.greeting = "Enc_Raiders";
				LAi_SetWarriorTypeNoGroup(character);
				LAi_Group_MoveCharacter(character, "PiratesOnUninhabited_ShoreGroup");
				LAi_Group_SetRelation("PiratesOnUninhabited_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				
				PChar.Quest.PiratesOnUninhabited_OpenChest.win_condition.(attribute) = "NPC_Death";
				PChar.Quest.PiratesOnUninhabited_OpenChest.win_condition.(attribute).character = "PirateOnUninhabited_ShorePirate" + i;
				
				i++;
				model[temp] = "";
			}
		}
		
		PChar.Quest.PiratesOnUninhabited_OpenChest.function = "PiratesOnUninhabited_OpenChest";
		
		PChar.Quest.PiratesOnUninhabited_ShoreTreasureLose.win_condition.l1 = "Timer";
		PChar.Quest.PiratesOnUninhabited_ShoreTreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		PChar.Quest.PiratesOnUninhabited_ShoreTreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		PChar.Quest.PiratesOnUninhabited_ShoreTreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		PChar.Quest.PiratesOnUninhabited_ShoreTreasureLose.win_condition = "PiratesOnUninhabited_ShoreTreasureLose";
		
		
		if(rand(2) == 1)
		{
			boxItems.chest = 1 + rand(14);
		}
		else
		{
			boxItems.jewelry2 = 10 + rand(3);
		}
		
		if(rand(2) == 1)
		{
			boxItems.icollection = 1 + rand(4);
		}
		
		if(rand(1) == 1)
		{
			boxItems.jewelry1 = 15 + rand(100);
		}
		
		if(rand(1) == 1)
		{
			boxItems.jewelry3 = 15 + rand(100);
		}
		
		if(rand(1) == 1)
		{
			boxItems.jewelry5 = 15 + rand(100);
		}
		
		if(rand(1) == 1)
		{
			boxItems.jewelry6 = 5 + rand(100);
		}
		
		if(rand(4) == 1)
		{
			boxItems.cirass3 = 1;
		}
		if (drand(7) == 1 && CheckAttribute(pchar, "questTemp.AdmiralMap")) 
		{
			string amap = SelectAdmiralMaps();
			if (amap != "") boxItems.(amap)	= 1;
		}
		
		location.(boxId) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
		location.(boxId).QuestClosed = true;
		location.(boxId).Treasure = true; 
		location.(boxId).PiratesOnUninhabitedTreasure = true;
		
		Log_TestInfo("������ �� ����������: ����������� ������ �����");
	}
	else
	{
		
		
		PChar.Quest.PiratesOnUninhabited_ClearQuest.win_condition.l1 = "ExitFromLocation";;
		PChar.Quest.PiratesOnUninhabited_ClearQuest.win_condition.l1.Location = PChar.GenQuest.PiratesOnUninhabited.TreasureShore;
		PChar.Quest.PiratesOnUninhabited_ClearQuest.function = "PiratesOnUninhabited_ClearQuest";
		
		Log_TestInfo("������ �� ����������: ������ ������, ������ �� ������");
	}
	
	TraderHunterOnMap(); 
}


void PiratesOnUninhabited_OpenChest(String _quest)
{
	DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.PiratesOnUninhabited.TreasureShore)], PChar.GenQuest.PiratesOnUninhabited.TreasureBox + ".QuestClosed");
	
	Log_TestInfo("������ �� ����������: �������� �������, ����� ����� � ������");
}


void PiratesOnUninhabited_ShoreTreasureLose(String _quest)
{
	ref location = &Locations[FindLocation(PChar.GenQuest.PiratesOnUninhabited.TreasureShore)];
	int index;
	String boxId = PChar.GenQuest.PiratesOnUninhabited.TreasureBox;

	for(int i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.ShorePiratesQty); i++)
	{
		index = GetCharacterIndex("PirateOnUninhabited_ShorePirate" + i);
		
		if(index != -1)
		{
			Characters[index].LifeDay = 0;
		}
	}
	
	DeleteAttribute(location, boxId + ".items");
	DeleteAttribute(location, boxId + ".Treasure");
	DeleteAttribute(location, boxId + ".PiratesOnUninhabitedTreasure");
	
	PiratesOnUninhabited_ClearQuest(""); 
}


void PiratesOnUninhabited_ClearQuest(String _quest)
{
	String title = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
	
	AddQuestRecordEx(title, "PiratesOnUninhabited", "8");
	AddQuestUserData(title, "sSex", GetSexPhrase("��","���"));
	AddQuestUserData(title, "shore", LowerFirst(XI_ConvertString(PChar.location + "Dat")));
	CloseQuestHeader(title);
	
	DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
}

void PiratesOnUninhabited_ShipSink(String _quest)
{
	PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
	Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); 
	
	PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1 = "Location_Type";
	PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1.location_type = "seashore";
	PChar.Quest.PiratesOnUninhabited_OnShore.again = true;
	PChar.Quest.PiratesOnUninhabited_OnShore.function = "PiratesOnUninhabited_OnShore";
	
	PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1 = "Location_Type";
	PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1.location_type = "mayak";
	PChar.Quest.PiratesOnUninhabited_OnMayak.again = true;
	PChar.Quest.PiratesOnUninhabited_OnMayak.function = "PiratesOnUninhabited_OnShore";
	
	Log_TestInfo("PiratesOnUninhabited_ShipSink");
}

void PiratesOnUninhabited_CapDeath(String _quest)
{
	float locx, locy, locz;
	ref character = CharacterFromID("PirateOnUninhabited_0");
	
	GetCharacterPos(PChar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(character, PChar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
	
	LAi_SetActorTypeNoGroup(character);
	character.dialog.currentnode = "PiratesOnUninhabited_49";
	LAi_ActorDialog(character, PChar, "", 5.0, 0.0);
	
	Log_TestInfo("PiratesOnUninhabited_CapDeath");
}







bool CheckShipSituation_GenQuest()
{
	if(CheckAttribute(pchar,"GenQuest.ShipSituation.Explosion") || CheckAttribute(pchar,"GenQuest.ShipSituation.Epidemy")) return true;
	else return false;
}

void RemoveCrewEpidemy_GenQuest()
{
	ref mainCh = GetMainCharacter(); 
	ref chref;
	int i, cn, crew, hcrew;
	int ShipType;
	
	Log_SetStringToLog("Captain! We have an epidemic here!");
	for(i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(mainCh,i);
		if(cn >= 0)
		{
			chref = GetCharacter(cn);
			if (!GetRemovable(chref)) continue;
			ShipType = sti(chref.Ship.Type);
			crew = makeint(GetCrewQuantity(chref)/(20 - 10 * GetCrewQuantity(chref)/GetMaxCrewQuantity(chref) + GetCharacterSPECIAL(pchar,"Luck")));
			if(ShipType != sti(pchar.GenQuest.ShipSituation.Epidemy.ShipType) && !IsMainCharacter(chref))
			{
				crew = makeint(crew/2);
			}
			Log_SetStringToLog("" + crew + " men are already dead on " + chref.Ship.Name + "");
			Statistic_AddValue(mainCh, "Sailors_dead", crew);
			Achievment_SetStat(mainCh, 21, crew);
			hcrew = GetCrewQuantity(chref);
			SetCrewQuantity(chref, hcrew - crew);
		}
	}
}

int CheckShipSituationDaily_GenQuest(ref refChar)
{
	int cn = 1;
	int ShipType = sti(refChar.Ship.Type);
	bool bOk;
	
	if(CheckAttribute(pchar,"GenQuest.ShipSituation.Epidemy"))
	{
		bOk = CheckAttribute(pchar,"GenQuest.ShipSituation.Epidemy.ShipType") && (ShipType == sti(pchar.GenQuest.ShipSituation.Epidemy.ShipType));
		if(bOk || IsMainCharacter(refChar))
		{
			switch(sti(pchar.GenQuest.ShipSituation.Epidemy))
			{
				case ShipSituation_0:
					cn = 1;
				break;
				case ShipSituation_1:
					cn = 2;
				break;
				case ShipSituation_2:
					cn = 2;
				break;
				case ShipSituation_3:
					cn = 3;
				break;
				case ShipSituation_4:
					cn = 1;
				break;
			}
		}	
	}
	return cn;
}


void SetFreeQuestAboardShipSituation(string qName)
{
	if(CheckShipSituation_GenQuest()) 
	{
		DeleteAttribute(pchar,"GenQuest.ShipSituation");
	}	
	bSeaCanGenerateShipSituation = false;
	pchar.CanGenerateShipSituation = false;	
	SetFunctionTimerCondition("CanGenerateQuestAboardShipSituation", 0, 0, rand(15) + 30, false);
}


void CanGenerateQuestAboardShipSituation(string qName)
{
	bSeaCanGenerateShipSituation = true;
	pchar.CanGenerateShipSituation = true;	
}


void CheckCaptainFreeQuestAboardSituation()
{
	ref sld;
	if(CheckShipSituation_GenQuest())
	{
		if(CheckAttribute(pchar,"GenQuest.ShipSituation.Explosion")) 
		{
			sld = CharacterFromID(pchar.GenQuest.ShipSituation.Explosion.CapId);
			SetCaptainFreeQuestAboardSituation(sld);
		}
		if(CheckAttribute(pchar,"GenQuest.ShipSituation.Epidemy")) 
		{
			sld = CharacterFromID(pchar.GenQuest.ShipSituation.Epidemy.CapId);			
			pchar.GenQuest.ShipSituation.Epidemy.ShipName = sld.Ship.Name;
			pchar.GenQuest.ShipSituation.Epidemy.ShipType = sti(sld.Ship.Type);
			if(pchar.GenQuest.ShipSituation.Epidemy.CapState == "Died") 
			{
				SetCaptainDiedQuestAboardSituation(sld);
				ShipSituation_SetConsequence(sti(pchar.GenQuest.ShipSituation.Epidemy));
			}
			if(pchar.GenQuest.ShipSituation.Epidemy.CapState == "Live") 
			{
				SetCaptainFreeQuestAboardSituation(sld);
				ShipSituation_SetConsequence(sti(pchar.GenQuest.ShipSituation.Epidemy));
			}	
		}	
	}	
}


void ShipSituation_SetConsequence(int iSituation)
{
	if(GetCharacterSPECIAL(pchar,"LUCK") * 10 > rand(120)) 
	{
		DoQuestFunctionDelay("SetFreeQuestAboardShipSituation", 1.0); 
	}
	else 
	{
		switch (iSituation)
		{
			case ShipSituation_0: 
				pchar.GenQuest.ShipSituation.Epidemy.Days = 3;
			break;
			case ShipSituation_1: 
				pchar.GenQuest.ShipSituation.Epidemy.Days = 7 + rand(4);
			break;
			case ShipSituation_2: 
				pchar.GenQuest.ShipSituation.Epidemy.Days = 15 + rand(5);
			break;
			case ShipSituation_3: 
				pchar.GenQuest.ShipSituation.Epidemy.Days = 15 + rand(5);
			break;
			case ShipSituation_4: 
				pchar.GenQuest.ShipSituation.Epidemy.Days = 1;
			break;
		}
		pchar.GenQuest.ShipSituation.Epidemy.DaysQty = sti(pchar.GenQuest.ShipSituation.Epidemy.Days);
	}
}

void ShipSituation_CheckConsequence(int iSituation)
{
	int DayQty;
	if(sti(pchar.GenQuest.ShipSituation.Epidemy.Days) > 0)
	{
		DayQty = sti(pchar.GenQuest.ShipSituation.Epidemy.DaysQty) - sti(pchar.GenQuest.ShipSituation.Epidemy.Days);
		if(DayQty == 0)
		{
			ReOpenQuestHeader("ShipEpidemy");
		}
		switch(iSituation)
		{
			case ShipSituation_0:
				if(DayQty == 0)
				{
					pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*10; 
					AddQuestRecord("ShipEpidemy","1");
					AddQuestUserData("ShipEpidemy", "sSex", GetSexPhrase("","�"));
					AddQuestUserData("ShipEpidemy", "sShipName", pchar.GenQuest.ShipSituation.Epidemy.ShipName);					
				}
				else
				{
					if(DayQty < 3) pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*5; 
				}
			break;
			case ShipSituation_1:
				if(DayQty == 0)
				{
					pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*10; 
					ChangeOfficersLoyality("bad_all", 1);
					AddQuestRecord("ShipEpidemy","3");
					AddQuestUserData("ShipEpidemy", "sShipName", pchar.GenQuest.ShipSituation.Epidemy.ShipName);
					RemoveCrewEpidemy_GenQuest();					
				}
				else
				{
					if(DayQty < 3) pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*5; 
				}	
			break;
			case ShipSituation_2:
				if(DayQty == 0)
				{
					pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*10; 
					ChangeOfficersLoyality("bad_all", 1);
					AddQuestRecord("ShipEpidemy","3");
					AddQuestUserData("ShipEpidemy", "sShipName", pchar.GenQuest.ShipSituation.Epidemy.ShipName);	
					RemoveCrewEpidemy_GenQuest();
				}
				else
				{
					if(DayQty < 3) pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*5; 
				}	
			break;
			case ShipSituation_3:
				if(DayQty == 0)
				{
					pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*10; 
					ChangeOfficersLoyality("bad_all", 2);
					AddQuestRecord("ShipEpidemy","3");
					AddQuestUserData("ShipEpidemy", "sShipName", pchar.GenQuest.ShipSituation.Epidemy.ShipName);	
					RemoveCrewEpidemy_GenQuest();
				}
				else
				{
					if(DayQty < 3) pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*5; 
				}		
			break;
			case ShipSituation_4:
				pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*10;
				AddQuestRecord("ShipEpidemy","1");
				AddQuestUserData("ShipEpidemy", "sShipName", pchar.GenQuest.ShipSituation.Epidemy.ShipName);	
			break;
		}
		pchar.GenQuest.ShipSituation.Epidemy.Days = sti(pchar.GenQuest.ShipSituation.Epidemy.Days) - 1;	
	}
	else
	{
		if(iSituation < 4)
		{
			switch(iSituation)
			{
				case ShipSituation_0:
					AddQuestRecord("ShipEpidemy","2");
				break;
				case ShipSituation_1:
					AddQuestRecord("ShipEpidemy","4");
				break;
				case ShipSituation_2:
					AddQuestRecord("ShipEpidemy","4");
				break;
				case ShipSituation_3:
					AddQuestRecord("ShipEpidemy","4");
				break;
			}
		}	
		CloseQuestHeader("ShipEpidemy");
		DoQuestFunctionDelay("SetFreeQuestAboardShipSituation", 5.0);
	}
}


void SetCaptainDiedQuestAboardSituation(ref chr)
{
	ShipDead(sti(chr.index), KILL_BY_ABORDAGE, sti(pchar.index));
}


void SetCaptainFreeQuestAboardSituation(ref chr)
{
	aref    arTo, arFrom;	
	ref sld = GetCharacter(NPC_GenerateCharacter(chr.id + "_free", "off_hol_2", "man", "man", 60, sti(chr.nation), 0, true, "citizen")); 
	ChangeAttributesFromCharacter(sld, chr, false);
	DeleteAttribute(sld, "ship");
	sld.ship = "";
			 
	makearef(arTo, sld.ship);
	makearef(arFrom, chr.Ship);
	CopyAttributes(arTo, arFrom);
	sld.AlwaysFriend = true;
	sld.Abordage.Enable = false; 
		    			
	SeaAI_SetCaptainFree(sld, chr);
	chr.location = "none"; 
		    
	if (bSeaActive)
	{			
		PostEvent("evntQuestsCheck", 400);
		ShipTakenFree(sti(chr.index), KILL_BY_ABORDAGE, sti(pchar.index)); 
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
		UpdateRelations();
		RefreshBattleInterface();
		CheckQuestAboardCabinSituation(sld);
		DoQuestCheckDelay("NationUpdate", 1.5);
	}
}

void ShipSituation_SetQuestSituation(int iSituation)
{
	if(CheckAttribute(pchar,"GenQuest.ShipSituation.Explosion")) 
	{
		pchar.GenQuest.ShipSituation.Explosion = iSituation;
	}
	if(CheckAttribute(pchar,"GenQuest.ShipSituation.Epidemy"))
	{
		pchar.GenQuest.ShipSituation.Epidemy = iSituation;
	}	
}


void ShipSituation_MakeDetonate(string qName)
{
	Log_TestInfo("����� ���������� � ����������� !!");
	ref sld = CharacterFromID(pchar.GenQuest.ShipSituation.Explosion.CapId + "_free");
	ref rBaseShip = GetRealShip(sti(sld.Ship.Type));
	Event(SHIP_BRANDER_DETONATE,"l", sti(sld.index));
    PlaySound("Sea Battles\Vzriv_fort_001.wav");
	Ship_SetTaskNone(SECONDARY_TASK, sti(sld.index));
	Log_Info("" + XI_ConvertString(rBaseShip.BaseName) + " '" + sld.Ship.Name + "' " + GetShipSexWord(rBaseShip.BaseName, "exploded", "exploded") + " a powder-magazine.");
	bQuestDisableMapEnter = false;
	RefreshBattleInterface();
	if (sld.id == "Fleetwood_free") DoQuestFunctionDelay("FleetwoodJournalFind", 0.1);
	DoQuestFunctionDelay("SetFreeQuestAboardShipSituation", 5.0);
}

void CheckQuestAboardCabinSituation(ref echar)
{
	if(CheckAttribute(pchar,"GenQuest.ShipSituation.Explosion")) 
	{	
		echar.FaceId = 333;
		echar.name = "the ship is empty";
		echar.lastname = "";
		bQuestDisableMapEnter = true;

		if(sti(pchar.GenQuest.ShipSituation.Explosion) == ShipSituation_1)
		{
			DoQuestFunctionDelay("ShipSituation_MakeDetonate", 0.5);	
		}
		else
		{
			if(sti(pchar.GenQuest.ShipSituation.Explosion) == ShipSituation_0)
			{				
				if(iArcadeSails == 1)
				{
					DoQuestFunctionDelay("ShipSituation_MakeDetonate", 15.0);
				}
				else
				{
					DoQuestFunctionDelay("ShipSituation_MakeDetonate", 40.0);
				}	
			}
			else
			{
				if(iArcadeSails == 1)
				{
					DoQuestFunctionDelay("ShipSituation_MakeDetonate", 30.0);
				}	
				else
				{
					DoQuestFunctionDelay("ShipSituation_MakeDetonate", 75.0);
				}	
			}
		}
	}
	if(CheckAttribute(pchar,"GenQuest.ShipSituation.Epidemy"))
	{
		pchar.GenQuest.ShipSituation.Epidemy.ShipName = echar.Ship.Name;
		pchar.GenQuest.ShipSituation.Epidemy.ShipType = sti(echar.Ship.Type);
		ShipSituation_SetConsequence(sti(pchar.GenQuest.ShipSituation.Epidemy));
	}	
}







void EncGirl_Saved()
{
	ref sld = CharacterFromID("CangGirl");
	sld.greeting = "rapers_girl_2";
	sld.dialog.filename = "Enc_RapersGirl_dialog.c";
	if(pchar.GenQuest.EncGirl == "toParents")
	{
		sld.dialog.currentnode = "Node_250"; 
	}
	else
	{
		sld.dialog.currentnode = "ThanksForSave"; 
	}	
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void EncGirl_GirlGoAway()
{
	ChangeCharacterComplexReputation(pchar,"nobility", -5);
	ref sld = CharacterFromID("CangGirl");
	LAi_SetActorType(sld);
	string sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
	LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "","", -1.0);
	sld.lifeDay = 0; 
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_toChurch(string qName)
{
	ref sld = CharacterFromID("CangGirl");
	ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirl.city + "_church", "goto", "goto1");
	LAi_SetStayType(sld);
}

void EncGirl_GenQuest_GetCoins(string qName)
{
	ref sld = CharacterFromID("CangGirl");
	ChangeCharacterAddress(sld, "None", ""); 
	sld.lifeDay = 0; 
	
	ChangeCharacterComplexReputation(pchar,"nobility", -10);
	AddQuestRecord("JungleGirl", "3");
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","�"));
	AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
	CloseQuestHeader("JungleGirl");
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_GenQuest_GetChestPlaceName()
{
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0: 
			pchar.GenQuest.EncGirl.islandId = "Bermudes"
			pchar.GenQuest.EncGirl.placeId = "Bermudes_Cavern";
			pchar.GenQuest.EncGirl.shoreId = "Shore_ship1";
		break;
		case 1: 
			pchar.GenQuest.EncGirl.islandId = "Caiman";
			pchar.GenQuest.EncGirl.placeId = "Caiman_Grot";
			pchar.GenQuest.EncGirl.shoreId = "Shore17";
		break;
		case 2: 
			pchar.GenQuest.EncGirl.islandId = "Dominica";
			pchar.GenQuest.EncGirl.placeId = "Dominica_Grot";
			pchar.GenQuest.EncGirl.shoreId = "Shore26";
		break;
		case 3: 
			pchar.GenQuest.EncGirl.islandId = "Terks";
			pchar.GenQuest.EncGirl.placeId = "Terks_Grot";
			pchar.GenQuest.EncGirl.shoreId = "Shore56";
		break;
	}
} 

void EncGirl_Death(string qName)
{
	AddQuestRecord("JungleGirl", "5");
    AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
	CloseQuestHeader("JungleGirl");
	pchar.quest.EncGirl_FindChest.over = "yes";
	DeleteAttribute(pchar, "pchar.GenQuest.EncGirl.islandId");	
	DeleteAttribute(pchar, "pchar.GenQuest.EncGirl.placeId");
	ChangeCharacterComplexReputation(pchar,"nobility", -30);
    pchar.quest.DeleteGirlGroup.win_condition.l1 = "ExitFromLocation";
    pchar.quest.DeleteGirlGroup.win_condition.l1.location = pchar.location;
    pchar.quest.DeleteGirlGroup.function = "EncGirl_DeleteGirlGroup";
}

void EncGirl_DeathAgain(string qName)
{
	AddQuestRecord("JungleGirl", "7");
	AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
	CloseQuestHeader("JungleGirl");
	ChangeCharacterComplexReputation(pchar,"nobility", -30);
	pchar.quest.EncGirl_DeliveBack.over = "yes";
	pchar.quest.DeleteGirlGroup.win_condition.l1 = "ExitFromLocation";
    pchar.quest.DeleteGirlGroup.win_condition.l1.location = pchar.location;
    pchar.quest.DeleteGirlGroup.function = "EncGirl_DeleteGirlGroup";
}

void EncGirl_DeathSimple(string qName)
{
	if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
	{
		AddQuestRecord("JungleGirl", "10");
		AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);	
		CloseQuestHeader("JungleGirl");
	}
	ChangeCharacterComplexReputation(pchar,"nobility", -30);
	pchar.quest.DeleteGirlGroup.win_condition.l1 = "ExitFromLocation";
    pchar.quest.DeleteGirlGroup.win_condition.l1.location = pchar.location;
    pchar.quest.DeleteGirlGroup.function = "EncGirl_DeleteGirlGroup";
}

void EncGirl_FindChest(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationDisableMonstersGen(pchar.location, true);
	pchar.quest.EncGirl_Death.over = "yes";
	ref sld = characterFromId("CangGirl");
	sld.dialog.filename = "Enc_RapersGirl_dialog.c";
	sld.dialog.currentnode = "Node_132_12";
	LAi_SetActorTypeNoGroup(sld);
	GetCharacterPos(sld, &locx, &locy, &locz);	
	ChangeCharacterAddressGroup(sld, pchar.location, "monsters", LAi_FindFarLocator("monsters", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
}

void EncGirl_AddPassenger(string qName)
{
	ref sld = characterFromId("CangGirl");	
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);		
	LAi_type_actor_Reset(sld); 
	ChangeCharacterAddress(sld, "none", ""); 
}

void EncGirl_DialogAtShore(string qName)
{
	ref sld = characterFromId("CangGirl");
	sld.dialog.filename = "Enc_RapersGirl_dialog.c";
	sld.dialog.currentnode = "Node_132_11_1";	
	PlaceCharacter(sld, "goto", pchar.location);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
	pchar.quest.EncGirl_EnterToSea.win_condition.l1 = "EnterToSea";
	pchar.quest.EncGirl_EnterToSea.function = "EncGirl_EnterToSea";
	pchar.quest.EncGirl_Death.over = "yes";
}

void EncGirl_EnterToSea(string qName)
{
	ref sld = characterFromId("CangGirl");
	if(pchar.GenQuest.EncGirl == "ChestGetted") 
	{
		LAi_type_actor_Reset(sld); 
	}
	else 
	{
		pchar.quest.EncGirl_DeliveBack.over = "yes"; 
		pchar.quest.EncGirl_DeathAgain.over = "yes";
		pchar.quest.EncGirl_FindChest.over = "yes";
		ChangeCharacterComplexReputation(pchar,"nobility", -5);
		AddQuestRecord("JungleGirl", "5_1");
		AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","�"));
		AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		CloseQuestHeader("JungleGirl");
		RemovePassenger(pchar, sld);
		ChangeCharacterAddress(sld, "none", "");
		sld.lifeDay = 0; 
		DeleteAttribute(pchar, "GenQuest.EncGirl");
	}
}

void EncGirl_DeleteGirlGroup(string qName)
{
	LAi_group_Delete("DeliveQuest_Girl");
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_DeliveBack(string qName)
{
	ref sld = characterFromId("CangGirl");	
	sld.dialog.filename = "Enc_RapersGirl_dialog.c";
	if(pchar.GenQuest.EncGirl == "ChestGetted")
	{
		chrDisableReloadToLocation = true;
		LAi_type_actor_Reset(sld); 
		sld.dialog.currentnode = "Node_132_18";
		pchar.quest.EncGirl_DeathAgain.over = "yes";
	}
	if(pchar.GenQuest.EncGirl == "FindCoins")
	{
		sld.dialog.currentnode = "Node_260";
		pchar.quest.EncGirl_DeathSimple.over = "yes";
	}
	if(pchar.GenQuest.EncGirl == "HorseToTavern")
	{
		sld.dialog.currentnode = "Node_225";
		pchar.quest.EncGirl_DeathSimple.over = "yes";
	}
	PlaceCharacter(sld, "goto", "random_must_be_near");
	if(pchar.GenQuest.EncGirl != "FindCoins")
	{
		LAi_SetActorType(pchar); 
		LAi_ActorTurnToCharacter(pchar, sld);
		LAi_SetActorTypeNoGroup(sld);
		SetActorDialogAny2Pchar(sld.id, "", -1, 1.0);
		LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);	
	}	
	else
	{
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);		
	}
}

void EncGirl_GenerateChest(ref chref)
{
	pchar.GenQuest.EncGirl.Treasure.Island = GetArealByCityName(chref.city);
	pchar.GenQuest.EncGirl.Treasure.Location = GetLocationForTreasure(pchar.GenQuest.EncGirl.Treasure.Island);
	pchar.GenQuest.EncGirl.Treasure.Locator = GetBoxForTreasure(pchar.GenQuest.EncGirl.Treasure.Island, pchar.GenQuest.EncGirl.Treasure.Location);

	pchar.quest.EncGirl_FindTreasure.win_condition.l1 = "location";
	pchar.quest.EncGirl_FindTreasure.win_condition.l1.location = pchar.GenQuest.EncGirl.Treasure.Location;
	pchar.quest.EncGirl_FindTreasure.function = "EncGirl_FindTreasure";
}

void EncGirl_FindTreasure(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationDisableMonstersGen(pchar.location, true);
	pchar.quest.EncGirl_DeathSimple.over = "yes";
	ref sld = characterFromId("CangGirl");
	sld.dialog.filename = "Enc_RapersGirl_dialog.c";
	sld.dialog.currentnode = "Node_207";
	LAi_SetActorTypeNoGroup(sld);
	GetCharacterPos(sld, &locx, &locy, &locz);	
	ChangeCharacterAddressGroup(sld, pchar.location, "monsters", LAi_FindFarLocator("monsters", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
}

void EncGirl_GirlFollow()
{
	sGlobalTemp = "Saved_CangGirl";
	ref sld = characterFromId("CangGirl");
	DeleteAttribute(sld, "LifeDay"); 
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed"); 
	LAi_SetActorType(sld);
	LAi_group_Register("DeliveQuest_Girl"); 
	LAi_group_SetRelation("DeliveQuest_Girl", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);

	LAi_group_MoveCharacter(sld, "DeliveQuest_Girl"); 
	LAi_ActorFollowEverywhere(sld, "", -1); 
	
	if(pchar.GenQuest.EncGirl != "GetChest")
	{
		pchar.quest.EncGirl_DeathSimple.win_condition.l1 = "NPC_Death";
		pchar.quest.EncGirl_DeathSimple.win_condition.l1.character = "CangGirl";
		pchar.quest.EncGirl_DeathSimple.function = "EncGirl_DeathSimple";
	}	
}

void EncGirl_MeetRapers(string qName)
{
	ref sld;
	for(i = 1; i <= 3; i++)
	{
		if (GetCharacterIndex("GangMan_" + i) == -1) continue;
		sld = CharacterFromID("GangMan_" + i);
		LAi_SetImmortal(sld, false);
		LAi_type_actor_Reset(sld);
		sld.dialog.filename = "Enc_Rapers_dialog.c";
		sld.dialog.currentnode = "Node_8";
		sld.greeting = "Enc_Raiders";
		sld.location = "none";
		PlaceCharacter(sld, "goto", "random_must_be_near");
		LAi_ActorFollow(sld, pchar, "", -1);
        LAi_group_MoveCharacter(sld, "EnemyFight");	
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);

	LAi_group_ClearAllTargets();
	LAi_SetFightModeForOfficers(false);
	
    sld = characterFromID("GangMan_1");
    LAi_type_actor_Reset(sld);
    LAi_ActorDialog(sld, pchar, "", 4.0, 0);
	chrDisableReloadToLocation = true;
	DoQuestCheckDelay("OpenTheDoors", 5.0);							
}

void EncGirl_GenerateLeatherBag(string qName)
{
	ref location;
	string boxId = "box1";
	aref boxItems;
	
	if(pchar.GenQuest.EncGirl == "Bag_BrothelRoomUp") 
	{
		location = &Locations[FindLocation(pchar.GenQuest.EncGirl.city + "_Brothel_room")];
	}
	if(pchar.GenQuest.EncGirl == "Bag_BrothelRoom")
	{
		location = &Locations[FindLocation(pchar.GenQuest.EncGirl.city + "_SecBrRoom")];
	}
	
	makearef(boxItems, location.(boxId).items);
		
	boxItems.leather_bag = 1;
	location.(boxId) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
	Log_TestInfo("���������� �������");
}

void EncGirl_RapersChest(string qName)
{
	ref location = &Locations[FindLocation(pchar.GenQuest.EncGirl.Treasure.Location)];
	string boxId = pchar.GenQuest.EncGirl.Treasure.Locator;
	aref boxItems;
	
	makearef(boxItems, location.(boxId).items);
			
	boxItems.gold = GetSummonSkillFromName(pchar, SKILL_FORTUNE) * 100 + rand(3000);
	
	if(rand(3) == 1) 
	{ 
		boxItems.jewelry2 = 10 + rand(3); 	
	}				
	if(rand(1) == 1) 
	{ 
		boxItems.jewelry1 = 15 + rand(10); 	
	}		
	if(rand(1) == 1) 
	{ 
		boxItems.jewelry52 = 25 + rand(15);	
	}
	if(rand(1) == 1) 
	{ 
		boxItems.jewelry53 = 18 + rand(20); 
	}
	if(rand(1) == 1) 
	{ 
		boxItems.jewelry47 = 22 + rand(12);	
	}
	if (drand(6) == 1 && CheckAttribute(pchar, "questTemp.AdmiralMap")) 
	{
		string amap = SelectAdmiralMaps();
		if (amap != "") boxItems.(amap)	= 1;
	}
		
	location.(boxId) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
	location.(boxId).Treasure = true; 
}

void EncGirl_TreasureLose(string qName)
{
	ref location = &Locations[FindLocation(pchar.GenQuest.EncGirl.Treasure.Location)];
	string boxId = pchar.GenQuest.EncGirl.Treasure.Locator;
	
	pchar.quest.EncGirl_RapersTreasure.over = "yes";
	
	DeleteAttribute(location, boxId + ".items");
	DeleteAttribute(location, boxId + ".Treasure");
	
	DeleteAttribute(pchar, "GenQuest.EncGirl");	
}

void EncGirl_RapersAfter(string qName)
{
	pchar.quest.EncGirl_TreasureLose.win_condition.l1 = "Timer";
	pchar.quest.EncGirl_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
	pchar.quest.EncGirl_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
	pchar.quest.EncGirl_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
	pchar.quest.EncGirl_TreasureLose.function = "EncGirl_TreasureLose";

	pchar.quest.EncGirl_RapersTreasure.win_condition.l1 = "location";
	pchar.quest.EncGirl_RapersTreasure.win_condition.l1.location = pchar.GenQuest.EncGirl.Treasure.Location;
	pchar.quest.EncGirl_RapersTreasure.function = "EncGirl_RapersChest";
}

void EncGirl_SpeakInRoom(string qName)
{
	chrDisableReloadToLocation = true;
	LocatorReloadEnterDisable(locations[reload_location_index].fastreload + "_tavern", "reload2_back", true);
	DoQuestFunctionDelay("EncGirl_SpeakInRoomEnter", 2);
}

void EncGirl_SpeakInRoomEnter(string qName)
{
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	ref sld = characterFromId("CangGirl");	
	sld.dialog.filename = "Enc_RapersGirl_dialog.c";
	sld.dialog.currentnode = "Node_228";
	PlaceCharacter(sld, "goto", "random_must_be_near"));
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);
}	

void EncGirl_SetBerglar(string qName)
{
	int iTemp = sti(pchar.rank) + rand(5);
	ref sld = GetCharacter(NPC_GenerateCharacter("Berglar_EncGirl", "mercen_"+(rand(14)+14), "man", "man", iTemp, PIRATE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, iTemp, 50 + rand(30), 50 + rand(30), "topor_04", "pistol6", "bullet", 50);
	sld.dialog.filename = "Enc_Rapers_dialog.c";
	sld.dialog.currentnode = "EncGirl_Berglar";	
	sld.greeting = "Enc_Raiders"; 
	PlaceCharacter(sld, "goto", "random_must_be_near"));
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_ActorDialog(sld, pchar, "", 4.0, 0);
}

void EncGirlFack_outRoom()
{
	pchar.GenQuest.EncGirl = "EncGirlFack_fighted";
	AddCharacterExpToSkill(pchar, "Pistol", 100); 
	sld = characterFromId("Berglar_EncGirl");
	sld.LifeDay = 0;
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
	SetFunctionTimerCondition("EncGirl_SpeakTavernKeeper", 0, 0, 1, false);
}

void EncGirlFack_outRoomRaped()
{
	
	RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
    while (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) != "")
    {
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE));
    }
    while (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "")
    {             
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE));
    }
    pchar.money = 0;
    
	pchar.GenQuest.EncGirl = "EncGirlFack_fighted";
	AddCharacterExpToSkill(pchar, "Pistol", 100); 
	sld = characterFromId("Berglar_EncGirl");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
	SetFunctionTimerCondition("EncGirl_SpeakTavernKeeper", 0, 0, 1, false);
}

void EncGirlFack_fight()
{
	AddCharacterExpToSkill(pchar, "FencingL", 30);
	AddCharacterExpToSkill(pchar, "FencingS", 30);
	AddCharacterExpToSkill(pchar, "FencingH", 30);
	LAi_SetFightMode(pchar, true);
	pchar.GenQuest.EncGirl = "EncGirlFack_fighted";
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	pchar.quest.EncGirl_afterFight.win_condition.l1 = "NPC_Death";
	pchar.quest.EncGirl_afterFight.win_condition.l1.character = "Berglar_EncGirl";
	pchar.quest.EncGirl_afterFight.win_condition = "OpenTheDoors";
	SetFunctionTimerCondition("EncGirl_SpeakTavernKeeper", 0, 0, 1, false);
}

void EncGirl_SpeakTavernKeeper(string qName)
{
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_GenQuest_GetBag(string qName)
{
	ref sld = CharacterFromID("CangGirl");
	sld.lifeDay = 0; 
	
	
	
	ChangeCharacterComplexReputation(pchar,"nobility", -8);
	pchar.quest.EncGirl_GenerateBag.over = "yes";
	pchar.quest.EncGirl_SpeakHorse.over = "yes";	
	AddQuestRecord("JungleGirl", "22");
	CloseQuestHeader("JungleGirl");
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_ExitTavernRoom(string qName)
{
	LocatorReloadEnterDisable(pchar.GenQuest.EncGirl.city + "_tavern", "reload2_back", false);
	
	pchar.quest.EncGirl_SpeakHorse.win_condition.l1 = "location";
	pchar.quest.EncGirl_SpeakHorse.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern_upstairs";
	pchar.quest.EncGirl_SpeakHorse.function = "EncGirl_SpeakHorse";
	ref sld = characterFromId("CangGirl");	
	ChangeCharacterAddress(sld, "none", ""); 
}

void EncGirl_SpeakHorse(string qName)
{
	ref sld = characterFromId("CangGirl");	
	sld.dialog.filename = "Enc_RapersGirl_dialog.c";
	sld.dialog.currentnode = "Node_240_1";
	ChangeCharacterAddress(sld, pchar.location, "goto1");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);		
}

void EncGirl_DeliveToParents(string qName)
{
	ref sld;
	sld = characterFromId("CangGirl");	
	RemovePassenger(pchar, sld);
	sld.dialog.filename = "Enc_RapersGirl_dialog.c";
	sld.dialog.currentnode = "Node_245";		
	PlaceCharacter(sld, "goto", pchar.location);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
}

void EncGirl_GenerateLover(string qName)
{
	int iTemp = sti(pchar.rank) + rand(5);
	ref sld = GetCharacter(NPC_GenerateCharacter("Lover_EncGirl", "mercen_"+(rand(14)+1), "man", "man", iTemp, sti(pchar.GenQuest.EncGirl.nation), -1, true, "citizen"));
	sld.name = pchar.GenQuest.EncGirl.sLoverId;
	sld.lastname = "";
	FantomMakeCoolFighter(sld, iTemp, 80, 80, "topor_04", "pistol6", "bullet", 50);
	pchar.quest.EncGirl_SpeakLoverTavern.win_condition.l1 = "location";
	pchar.quest.EncGirl_SpeakLoverTavern.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
	pchar.quest.EncGirl_SpeakLoverTavern.function = "EncGirl_SpeakLover";
}

void EncGirl_SpeakLover(string qName)
{
	chrDisableReloadToLocation = true;
	ref sld = characterFromId("Lover_EncGirl");	
	sld.dialog.filename = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "EncGirl_Lover";	
	sld.greeting = "Gr_Officer"; 
	PlaceCharacter(sld, "goto", pchar.GenQuest.EncGirl.city + "_tavern");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
}

void EncGirl_LoverExit()
{
	string sTemp;
	pchar.quest.EncGirl_DeathSimple.over = "yes";
	AddQuestRecord("JungleGirl", "14");
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","�"));
	CloseQuestHeader("JungleGirl");		
	ChangeCharacterComplexReputation(pchar,"nobility", -3);	
	sTemp = LAi_FindNearestFreeLocator2Pchar("reload");

	for (i = 1; i <= 2; i++)
	{
		if (i == 1) sld = characterFromId("Lover_EncGirl");
		else sld = characterFromId("CangGirl");
		sld.lifeDay = 0;
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", 5.0);
	}

	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_ToLoverParents()
{
	ref sld;
	string sTemp;
	pchar.quest.EncGirl_DeathSimple.over = "yes";
	AddQuestRecord("JungleGirl", "15");
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("��","���"));
	AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.LoverCity));
	ChangeCharacterComplexReputation(pchar,"nobility", 1);
	sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
	
	for (i = 1; i <= 2; i++)
	{
		if (i == 1) sld = characterFromId("Lover_EncGirl");
		else sld = characterFromId("CangGirl");
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, false);
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", 5.0);
	}			
	
	pchar.quest.EncGirl_DeliveToLoverParents.win_condition.l1 = "location";
	pchar.quest.EncGirl_DeliveToLoverParents.win_condition.l1.location = pchar.GenQuest.EncGirl.LoverCity + "_town";
	pchar.quest.EncGirl_DeliveToLoverParents.function = "EncGirl_DeliveToLoverParents";
}

void EncGirl_ToLoverParentsExit()
{
	pchar.quest.EncGirl_DeathSimple.over = "yes";
	ChangeCharacterComplexReputation(pchar,"nobility", -3);
	AddMoneyToCharacter(pchar, 500 * (sti(pchar.rank) + 10) + drand(5000));
	AddQuestRecord("JungleGirl", "13");
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","�"));
	CloseQuestHeader("JungleGirl");
	ref sld = CharacterFromID("CangGirl");
	string sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "","", -1.0);
	sld.lifeDay = 0; 
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_DeliveToLoverParents(string qName)
{
	pchar.GenQuest.Hunter2Pause = true;
	ref sld;	
	sld = characterFromId("CangGirl");
	RemovePassenger(pchar, sld);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
	sld.lifeday = 0;		
	sld = characterFromId("Lover_EncGirl");
	RemovePassenger(pchar, sld);
	chrDisableReloadToLocation = true;
	sld.dialog.filename = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "EncGirl_Lover6";	
	PlaceCharacter(sld, "goto", pchar.location);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void EncGirl_GenQuest_GetLoverFather(string qName)
{
	AddQuestRecord("JungleGirl", "17");
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","�"));
	CloseQuestHeader("JungleGirl");
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}







void Set_TreasureBarrel()
{
	ref			nulChr;
	aref     	trBarrel;

	nulChr = &NullCharacter;
	if(CheckAttribute(nulChr,"GenQuest.Barrel")) DeleteAttribute(nulChr,"GenQuest.Barrel");

	makearef(trBarrel, nulChr.GenQuest.Barrel);
	int irand;

	if(GetSummonSkillFromName(pchar, "Fortune") > drand(200))
	{
		irand = drand(20);
		if(irand == 1) trBarrel.items.jewelry1 = rand(18) + 27;
		irand = drand(20);
		if(irand == 2) trBarrel.items.jewelry2 = rand(22) + 22;
		irand = drand(20);
		if(irand == 3) trBarrel.items.jewelry3 = rand(15) + 32;
		irand = drand(20);
		if(irand == 4) trBarrel.items.jewelry4 = rand(22) + 15;
		irand = drand(20);
		if(irand == 5) trBarrel.items.jewelry5 = rand(19) + 22;
		irand = drand(20);
		if(irand == 6) trBarrel.items.jewelry6 = rand(22) + 16;
		irand = drand(20);
		if(irand == 7) trBarrel.items.jewelry7 = rand(17) + 32;
		irand = drand(20);
		if(irand == 8) trBarrel.items.jewelry40 = rand(5) + 18;		
		irand = drand(20);
		if(irand == 9) trBarrel.items.jewelry41 = rand(8) + 12;				
		irand = drand(20);
		if(irand == 10) trBarrel.items.jewelry42 = rand(35) + 12;
		irand = drand(20);
		if(irand == 11) trBarrel.items.jewelry43 = rand(13) + 27;
		irand = drand(20);
		if(irand == 12) trBarrel.items.jewelry44 = rand(16) + 18);
		irand = drand(20);
		if(irand == 13) trBarrel.items.jewelry45 = rand(30) + 15);
		irand = drand(20);
		if(irand == 14) trBarrel.items.jewelry46 = rand(30) + 15);
		irand = drand(20);
		if(irand == 15) trBarrel.items.jewelry47 = rand(35) + 14);
		irand = drand(20);
		if(irand == 16) trBarrel.items.jewelry48 = rand(24) + 18);
		irand = drand(20);
		if(irand == 17) trBarrel.items.jewelry49 = rand(17) + 13);		
		irand = drand(24);
		if(irand == 18) trBarrel.items.jewelry50 = rand(15) + 22);		
		irand = drand(24);
		if(irand == 19) trBarrel.items.jewelry51 = rand(35) + 42);		
		irand = drand(24);
		if(irand == 22) trBarrel.items.jewelry52 = rand(41) + 12);		
		irand = drand(24);
		if(irand == 23) trBarrel.items.jewelry53 = rand(66) + 70);		
		irand = drand(20);						
		if(irand == 18) trBarrel.items.chest = rand(2) + 1;		
		irand = drand(20); 
				
		irand = drand(25);
		if(irand == 3) trBarrel.items.amulet_5 = 1;		
		irand = drand(25);
		if(irand == 6) trBarrel.items.amulet_10 = 1;
		irand = drand(25);
		if(irand == 9) trBarrel.items.amulet_11 = 1;		
		irand = drand(25);
		if(irand == 15) 	trBarrel.items.indian_8 = 1;				
		irand = drand(25);
		if(irand == 18) 	trBarrel.items.indian_5 = 1;		
		irand = drand(25);		
		if(irand == 21) trBarrel.items.icollection = 1; 

		irand = drand(25);
		if(irand == 24 && GetCharacterItem(pchar, "map_full") == 0)
		{
			if (GetCharacterItem(pchar, "map_part1") == 0) trBarrel.items.map_part1 = 1;
			else
			{
				if (GetCharacterItem(pchar, "map_part2") == 0) trBarrel.items.map_part2 = 1;
			}			
		}
		if (drand(30) == 1 && CheckAttribute(pchar, "questTemp.AdmiralMap")) 
		{
			string amap = SelectAdmiralMaps();
			if (amap != "") trBarrel.items.(amap) = 1;
		}
	}
	else
	{
		if(rand(1) == 0) trBarrel.items.mineral2 = rand(7) + 7;
		if(rand(1) == 0) trBarrel.items.mineral3 = rand(15) + 5;
		if(rand(1) == 0) trBarrel.items.mineral4 = rand(10) + 2;
		if(rand(1) == 0) trBarrel.items.mineral5 = rand(8) + 4;
		if(rand(1) == 0) trBarrel.items.mineral6 = rand(14) + 7;
		if(rand(1) == 0) trBarrel.items.mineral7 = rand(12) + 8;
		if(rand(1) == 0) trBarrel.items.mineral8 = rand(12) + 6;
		if(rand(1) == 0) trBarrel.items.mineral9 = rand(8) + 2;
		if(rand(1) == 0) trBarrel.items.mineral10 = rand(16) + 6;
	}	
	trBarrel.items.gold = drand(5000) + 5000;	
	LaunchItemsBarrel(&trBarrel);
}







void CaptainComission_GenerateSituation(ref chref)
{
	if(CheckAttribute(chref, "RealEncounterType") && sti(chref.RealEncounterType) != ENCOUNTER_TYPE_ALONE && !CheckAttribute(pchar,"GenQuest.CaptainComission"))
	{
		aref chrShip;
		makearef(chrShip, chref.Back.Ship);
		if (CheckAttribute(chrShip, "Mode") && chrShip.Mode == "trade")
		{
			if(rand(4) == 1 || bBettaTestMode) 
			{
				pchar.GenQuest.CaptainComission = "Begin";
				pchar.GenQuest.CaptainComission.CapId = chref.CaptanId;
				pchar.GenQuest.CaptainComission.CapName = chref.Name;
				pchar.GenQuest.CaptainComission.ShipType = GetCharacterShipType(chrShip);
			}	
		}	
	}
}

void CaptainComission_Init(ref chref)
{
	pchar.GenQuest.CaptainComission.Nation = chref.nation;
	pchar.GenQuest.CaptainComission.City = GetQuestNationsCity(sti(chref.nation));
	pchar.GenQuest.CaptainComission.Name = GenerateRandomName_Generator(sti(chref.nation), "man");
	pchar.GenQuest.CaptainComission.SlaveName = GenerateRandomName_Generator(sti(chref.nation), "man");
	pchar.GenQuest.CaptainComission.ShipName = chref.Back.Ship.Name;
	pchar.GenQuest.CaptainComission.Speak_Tavern = false;
	pchar.GenQuest.CaptainComission.variant = "A0";
	pchar.GenQuest.CaptainComission.Item = GenQuest_GeneratePrize();
}

void CaptainComission_Speak(string qName)
{
	if(pchar.GenQuest.CaptainComission == "Begin_1" || pchar.GenQuest.CaptainComission == "Begin_2")
	{
		AddQuestRecord("CaptainComission1", "2");
		AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
		CloseQuestHeader("CaptainComission1");
		DeleteAttribute(pchar,"GenQuest.CaptainComission");
	}
}

void CaptainComission_SellSlave(string qName)
{
	pchar.GenQuest.CaptainComission.DaysLeft = true;
}

void CaptainComission_EndTavern()
{
	ref sld;
	sld = characterFromId("CapComission_1");
	sld.lifeDay = 0; 
	LAi_CharacterDisableDialog(sld);
	
	sld = characterFromId("CapComission_Slave");
	RemovePassenger(pchar, sld);
	sld.lifeDay = 0; 
	
	DeleteAttribute(pchar,"GenQuest.CaptainComission");
}

void CaptainComission_GenerateChar(string qName)
{
	ref sld = GetCharacter(NPC_GenerateCharacter("CapComission_1" , "officer_12", "man", "man", 10, sti(pchar.GenQuest.CaptainComission.Nation), -1, true, "quest"));
	FantomMakeCoolFighter(sld, 10, 30, 35, LinkRandPhrase("blade_05","blade_04","blade_07"), "pistol1", "bullet", 10);	
	sld.name = pchar.GenQuest.CaptainComission.Name;
	sld.lastname = "";
	sld.SaveItemsForDead = true; 
	sld.DontClearDead = true; 
	sld.dialog.FileName = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "CaptainComission_3";
	sld.greeting = "cit_quest";
	LAi_SetSitType(sld);
	LAi_SetImmortal(sld, true);	
	string sLoc = pchar.GenQuest.CaptainComission.City + "_tavern"; 
	FreeSitLocator(sLoc, "sit2");
	ChangeCharacterAddressGroup(sld, sLoc, "sit", "sit2");
}

void CaptainComission_GetPirateIsland()
{
	ref sld;
	string CityId, PirateId;	
	switch (rand(1))
	{
		case 0:
			CityId = "PuertoPrincipe"; 
			PirateId = "Marlow";
			sld = CharacterFromID("Marlow");
		break;
		case 1:
			CityId = "LeFransua"; 
			PirateId = "Barbazon";
			sld = CharacterFromID("Barbazon");
		break;
	}
	pchar.GenQuest.CaptainComission.PiratesCity = CityId;
	pchar.GenQuest.CaptainComission.PirateId = PirateId;
	pchar.GenQuest.CaptainComission.PirateName = ChangeNameCase(NAMETYPE_MAIN, sld.name, NAME_NOM);
}

void CaptainComission_GetFamilyType()
{
	pchar.GenQuest.CaptainComission.FamilyType = drand(4) + 1;
}

void CaptainComission_30DaysIsLeft(string qName) 
{
	ref sld;
	if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
	{
		sld = characterFromId("CapComission_1");
		ChangeCharacterAddress(sld, "none", ""); 
		sld.lifeDay = 0; 
		int idx = GetCharacterIndex("Bishop_manager");
		if(idx != -1) 
		{
			sld = &characters[idx];
			sld.lifeDay = 0; 
		}	
		if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
		{
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("CaptainComission1", "6");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("�� ��-�������������","���������"));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sSex2", GetSexPhrase("","��"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
		}
		if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
		{
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			AddQuestRecord("CaptainComission1", "7");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.GenQuest.CaptainComission.Nation)) + "hunter", 50);
		}
		CloseQuestHeader("CaptainComission1");
		DeleteAttribute(pchar,"GenQuest.CaptainComission");
	}
}

void CaptainComission_PirateShipsOver(string qName)
{
	pchar.quest.CapComission_PirateAttack.over = "yes";
	AddQuestRecord("CaptainComission1", "26");
	AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
	AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
	pchar.GenQuest.CaptainComission.PirateShips = "goaway";
	ChangeOfficersLoyality("bad_all", 1);
}

void CaptainComission_GetRandomShore()
{
	pchar.GenQuest.CaptainComission.Island = GetRandomIslandId();
	while(pchar.GenQuest.CaptainComission.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
	{
		pchar.GenQuest.CaptainComission.Island = GetRandomIslandId();
	}
	pchar.GenQuest.CaptainComission.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.CaptainComission.Island);
	while(pchar.GenQuest.CaptainComission.Island.Shore == "")
	{
		pchar.GenQuest.CaptainComission.Island = GetRandomIslandId();
		pchar.GenQuest.CaptainComission.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.CaptainComission.Island);
		if (!isLocationFreeForQuests(pchar.GenQuest.CaptainComission.Island)) pchar.GenQuest.CaptainComission.Island.Shore = "";
	} 
}

void CaptainComission_GenerateManager()
{
    ref sld;
	string sModel, sName, sLastName;
	int idx;
	switch(rand(2))
	{
		case 0:
			sModel = "trader_2";
			sName = "George";
			sLastName = "Bush";		
		break;
		case 1:
			sModel = "citiz_41";
			sName = "Rabak";
			sLastName = "Maboa";				
		break;
		case 2:
			sModel = "trader_3";
			sName = "Abraham";
			sLastName = "Lincoln";				
		break;
	}
	
	Log_TestInfo("������� ������������");	
   	sld = GetCharacter(NPC_GenerateCharacter("Bishop_manager", sModel, "man", "man", 1, GetCityNation("Bridgetown"), -1, false, "citizen"));
    sld.name = sName;
    sld.lastname = sLastName;
	sld.dialog.filename = "GenQuests_Dialog.c";
    sld.Dialog.CurrentNode = "CaptainComission_10";
    sld.greeting = "Gr_Bishop";

	string sTemp = GetNationNameByType(GetCityNation("Bridgetown")) + "_citizens";
    LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetCitizenType(sld);
	LAi_SetImmortal(sld, true);

	ChangeCharacterAddressGroup(sld, "Plantation_Sp1", "goto", "goto1");
	
	LAi_LocationDisableOfficersGen("BridgeTown_Plantation", true);
	
	idx = GetCharacterIndex("Bishop");
	if(idx != -1) 
	{
		sld = &characters[idx];
		ChangeCharacterAddress(sld, "None", ""); 
	}		
}

void CaptainComission_GenerateSlave(string qName)
{
	string model[10];
	string sTemp = "SlaveGuards";
	int iNation = GetCityNation("Bridgetown");
	string slai_group = GetNationNameByType(iNation)  + "_citizens";
		
	model[0] = "citiz_26";
	model[1] = "citiz_27";
	model[2] = "citiz_28";
	model[3] = "citiz_29";
	model[4] = "citiz_30";
	model[5] = "citiz_31";
	model[6] = "citiz_32";
	
	int iMassive = rand(6);
	
	ref sld = GetCharacter(NPC_GenerateCharacter("CapComission_Slave", model[iMassive], "man", "man", rand(5) + 5, sti(pchar.GenQuest.CaptainComission.Nation), -1, true, "slave"));	
	sld.city = pchar.GenQuest.CaptainComission.City;
	sld.name = pchar.GenQuest.CaptainComission.SlaveName;
	sld.lastname = "";	
	sld.greeting = "Gr_slave";
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed"); 
	sld.dialog.filename = "GenQuests_Dialog.c";
	LAi_SetHP(sld, 50.0, 60.0); 

	if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")	
	{
		Log_QuestInfo("�������� ����");
		sld.dialog.currentnode = "CaptainComission_20";	
		PlaceCharacter(sld, "goto", "random_must_be_near");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);		
	}	
	if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")	
	{
		Log_QuestInfo("���� ����������� ����");
		LAi_LocationFightDisable(&Locations[FindLocation("BridgeTown_Plantation")], true);
		LAi_SetFightMode(pchar, false);
		LAi_LockFightMode(pchar, true);
		sld.dialog.currentnode = "CaptainComission_70";
		ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "quest", "sit2");
		LAi_SetActorType(sld);
		LAi_ActorSetLayMode(sld);
		LAi_SetGroundSitTypeNoGroup(sld); 
		
		
		for (int i = 0; i < 3; i++)
		{		
			sld = GetCharacter(NPC_GenerateCharacter("SlaveGuard_"+i, "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 1, true,"soldier"));
			SetFantomParamFromRank(sld, sti(pchar.rank) + MOD_SKILL_ENEMY_RATE, true); 
            LAi_SetActorType(sld);
            LAi_SetStayType(sld); 
            LAi_group_MoveCharacter(sld, sTemp);
			LAi_group_SetLookRadius(sTemp, 10);
			LAi_group_SetHearRadius(sTemp, 10);	
			LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetRelation(sTemp, slai_group, LAI_GROUP_FRIEND);
            if(i < 2) 	ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "quest", "sit"+(2*i+1));
			else		PlaceCharacter(sld, "goto", "random_free");
			sld.dialog.filename = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "CaptainComission_80";							
        }				
		SetFunctionTimerConditionParam("CaptainComission_SlaveIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false); 
		pchar.quest.CapComission_SlaveDeath.win_condition.l1 = "NPC_Death";
		pchar.quest.CapComission_SlaveDeath.win_condition.l1.character = "CapComission_Slave";
		pchar.quest.CapComission_SlaveDeath.function = "CaptainComission_SlaveDeath";		
	}
}

void CaptainComission_GeneratePassengerSlave()
{
	string model[3];
	string sTemp = "TmpEnemy";
		
	model[0] = "citiz_26";
	model[1] = "shipowner_10";
	model[2] = "barmen_1";
	
	int iMassive = rand(2);
	
	ref sld = GetCharacter(NPC_GenerateCharacter("CapComission_Slave", model[iMassive], "man", "man", rand(5) + 5, sti(pchar.GenQuest.CaptainComission.Nation), -1, true, "slave"));	
	sld.city = pchar.GenQuest.CaptainComission.City;	
	sld.name = pchar.GenQuest.CaptainComission.SlaveName;
	sld.lastname = "";	
	
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed"); 
	
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);
	pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
}

void CaptainComission_GuardsAfter(string qName)
{
	pchar.quest.CaptainComission_SlaveIsOver.over = "yes";
		
	ref sld = CharacterFromId("CapComission_Slave");	
	
	if (!LAi_IsDead(sld))
	{
		sld.dialog.filename = "GenQuests_Dialog.c";
		sld.dialog.currentnode = "CaptainComission_85";	
		sld.greeting = "Gr_slave"; 
		LAi_SetStayType(sld); 
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);	
	
		pchar.quest.CaptainComission_SlaveOnMayak.win_condition.l1 = "Location";
		pchar.quest.CaptainComission_SlaveOnMayak.win_condition.l1.location = "Mayak2";
		pchar.quest.CaptainComission_SlaveOnMayak.function = "CaptainComission_OnMayak";
	
		SetFunctionTimerConditionParam("CaptainComission_SlaveDeathJungles", 0, 0, 2, MakeInt(24 - GetHour()), false);
	}	

}

void CaptainComission_SlaveDeathJungles(string qName) 
{
	pchar.GenQuest.CaptainComission.GetSlave = "SlaveDied";
	pchar.quest.CaptainComission_SlaveOnMayak.over = "yes";
	AddQuestRecord("CaptainComission1", "17_1");
	AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
	ref sld = characterFromId("CapComission_Slave");
	ChangeCharacterAddress(sld, "none", ""); 
	sld.lifeDay = 0; 
}

void CaptainComission_OnMayak(string qName)
{
	aref grp;	
	ref pLoc, sld;
	string encGroup, str, locator;
	int	num;

	AddQuestRecord("CaptainComission1", "18");
	AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
	
	pchar.quest.CaptainComission_SlaveDeathJungles.over = "yes";
	
	chrDisableReloadToLocation = true;
	
	pLoc = &locations[FindLocation("Mayak2")];
	encGroup = LAi_FindRandomLocator("encdetector");
	str = "locators." + encGroup;
	makearef(grp, pLoc.(str));
	num = GetAttributesNum(grp);
	if (num <= 0) num = 1;

	sld = CharacterFromId("CapComission_Slave");	
	LAi_CharacterEnableDialog(sld);
	sld.dialog.filename = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "CaptainComission_90";	
		
	string sEquipItem = "slave_02"; 
	AddItems(sld, sEquipItem, 1);
	EquipCharacterByItem(sld, sEquipItem);
		
	LAi_SetStayType(sld);
	locator = GetAttributeName(GetAttributeN(grp, 1));
	ChangeCharacterAddressGroup(sld, pLoc.id, encGroup, locator);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0); 
}

void CaptainComission_SlaveDeath(string qName)
{
	pchar.GenQuest.CaptainComission.GetSlave = "SlaveDied";
	pchar.quest.CaptainComission_SlaveOnMayak.over = "yes";
	AddQuestRecord("CaptainComission1", "17");
	AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
}

void CaptainComission_SlaveIsOver(string qName)
{
	pchar.GenQuest.CaptainComission.GetSlave = "SlaveDied";
	ref sld = characterFromId("CapComission_Slave");
	ChangeCharacterAddress(sld, "none", ""); 
	sld.lifeDay = 0; 
}

void CaptainComission_GeneratePatrol()
{
	ref pLoc, chr;
	string str;
	int iRank, i, num;
	int iNation = GetCityNation("Bridgetown");

	pLoc = &locations[FindLocation("Mayak2")];
	
	str = "Patrol"+ pLoc.index + "_";
	string sGroup = "PatrolGroup_" + pLoc.index; 
	iRank = sti(pchar.rank);
	if(MOD_SKILL_ENEMY_RATE > 5) num = 5;
	else						 num = 3;	
	
	for(i = 0; i < num; i++)
	{
		if(i == 0)
		{
			int iPatrolOfficer = NPC_GenerateCharacter(str + i, "off_"+NationShortName(iNation)+"_"+(rand(1)+1), "man", "man", iRank + 2, iNation, 1, true, "officer");
			chr = &characters[iPatrolOfficer];
			SetFantomParamFromRank(chr, iRank + 2, true);	
			chr.greeting = "soldier_arest";
		}	
		else
		{
			chr = GetCharacter(NPC_GenerateCharacter(str + i, "sold_"+NationShortName(iNation)+"_"+(rand(7)+1), "man", "man", iRank, iNation, 1, true, "soldier"));
			SetFantomParamFromRank(chr, iRank, true);		
		}
		chr.City = "Bridgetown";
		chr.CityType = "soldier";
		LAi_SetWarriorType(chr);
		ChangeCharacterAddressGroup(chr, pLoc.id, "reload", "reload1");
		LAi_group_MoveCharacter(chr, sGroup);
	}
	
	LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true); 
	LAi_group_SetCheckFunction(sGroup, "CaptainComission_ExitFromMayak");
	LAi_group_SetCheck(sGroup, "OpenTheDoors"); 	
}

void CaptainComission_ExitFromMayak(string qName)
{
	ref sld;
	
	sld = characterFromId("CapComission_Slave");
	if (!LAi_IsDead(sld)) 	pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
	else 					pchar.GenQuest.CaptainComission.GetSlave = "SlaveDied";
				
	if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
	{
		pchar.quest.CapComission_SlaveDeath.over = "yes";
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, false);
				
		if(pchar.GenQuest.CaptainComission == "toEnemyTavern")
		{
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";			
		}
	}	
}

void CaptainComission_GetSlave()
{	
	ref sld = CharacterFromId("Bishop_manager");
	sld.lifeDay = 1; 
	
	pchar.quest.CapComission_GetSlave.win_condition.l1 = "ExitFromLocation";
	pchar.quest.CapComission_GetSlave.win_condition.l1.location = pchar.location;
	pchar.quest.CapComission_GetSlave.function = "CaptainComission_GenerateSlave";
	
	pchar.quest.CaptainComission_30DaysIsLeft.over = "yes";
}

void CaptainComission_DeliveSlave(string qName)
{
	chrDisableReloadToLocation = true;
	ref sld = characterFromId("CapComission_Slave");
	RemovePassenger(pchar, sld);	
	sld.dialog.filename = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "CaptainComission_100";	
	PlaceCharacter(sld, "goto", "random_must_be_near");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
}

void GetSlaveSpeciality()
{
	string Speciality;
	int Spec = drand(2);
	switch (Spec)
    {
        case 0 :
             Speciality = "in shipbuilding";
        break;
        case 1 :
            Speciality = "in artillery";
        break;
        case 2 :
            Speciality = "in navigation";
        break;
    }
	pchar.GenQuest.CaptainComission.SlaveSpeciality = Speciality;	
	pchar.GenQuest.CaptainComission.Speciality = Spec;
}

void CaptainComission_GeneratePirateShips(string qName)
{
	int i, ShipType, Rank, iShipRank, iCannonType;
	ref sld;
	string Blade, sTemp;
			
	Log_QuestInfo("��������� ������� �����������, ����� ������ ��������.");
    Island_SetReloadEnableGlobal(pchar.GenQuest.CaptainComission.Island, false);
    Group_FindOrCreateGroup("Pirate_Attack");
	Group_SetType("Pirate_Attack", "war");
	
	for (i=1; i<=2; i++)
	{
		Rank = sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE);
		if(makeint(pchar.rank) > 13) { iShipRank = rand(2) + 3; }
		if(makeint(pchar.rank) > 6 && makeint(pchar.rank) < 13) { iShipRank = rand(2); }	
		if(makeint(pchar.rank) < 7) { iShipRank = rand(1); }
		switch (iShipRank)
		{
			case 0: 		 
				ShipType = SHIP_SCHOONER_W;
				Rank = 10 + rand(5);
                Blade = "blade_11";
				iCannonType = CANNON_TYPE_CANNON_LBS16;
			break; 		
			case 1:  
				ShipType = SHIP_BRIG;     					
				Rank = 14 + rand(5);
                Blade = "blade_12";
				iCannonType = CANNON_TYPE_CANNON_LBS16;
			break; 		
			case 2:  
				ShipType = SHIP_BRIGANTINE;			
				Rank = 20 + rand(5);
                Blade = "blade_10";
				iCannonType = CANNON_TYPE_CANNON_LBS16;
			break; 
			case 3: 
				ShipType = SHIP_CORVETTE; 				
				Rank = 25 + rand(5);
                Blade = "blade_15";
				iCannonType = CANNON_TYPE_CANNON_LBS20;
			break; 
			case 4: 
				ShipType = SHIP_FRIGATE;         			
				Rank = 30 + rand(5);
                Blade = "blade_19";
				iCannonType = CANNON_TYPE_CANNON_LBS24;
			break; 
			case 5: 
				ShipType = SHIP_LINESHIP; 						
				Rank = 35 + rand(5);
                Blade = "blade_21";
				iCannonType = CANNON_TYPE_CANNON_LBS32;
			break;  				
		}
		if(i == 1) 	sTemp = pchar.GenQuest.CaptainComission.ShipName1;
		else 		sTemp = pchar.GenQuest.CaptainComission.ShipName2;
		sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, "mercen_"+(rand(14)+14), "man", "man", Rank, PIRATE, 3, true, "quest"));
		FantomMakeCoolSailor(sld, ShipType, sTemp, iCannonType, 60 + rand(20), 95, 95);
		FantomMakeCoolFighter(sld, Rank, 50 + rand(30), 50 + rand(20), Blade, "pistol3", "grapeshot", 50);
		Group_AddCharacter("Pirate_Attack", "CaptainAttack_"+i);
		
		sld.SuperShooter  = true;

		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "GunProfessional");
		SetCharacterPerk(sld, "MusketsShoot");
		
		sld.ship.Crew.Morale = 50 + rand(30);
		ChangeCrewExp(sld, "Sailors", 70 + rand(10));
		ChangeCrewExp(sld, "Cannoners", 70 + rand(10));
		ChangeCrewExp(sld, "Soldiers", 70 + rand(10));
    }
    
	Group_SetGroupCommander("Pirate_Attack", "CaptainAttack_1");
	Group_SetTaskAttack("Pirate_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Pirate_Attack", PLAYER_GROUP);
	Group_SetAddress("Pirate_Attack", pchar.GenQuest.CaptainComission.Island, "", "");
	Group_LockTask("Pirate_Attack");
			
    
    pchar.quest.CapComission_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.CapComission_AfterBattle.win_condition.l1.group = "Pirate_Attack";
	pchar.quest.CapComission_AfterBattle.function = "CaptainComission_PirateAttack_AfterBattle";
	pchar.quest.CapComission_DieHard.win_condition.l1 = "MapEnter";
    pchar.quest.CapComission_DieHard.function = "CaptainComission_PirateAttack_DieHard";
}

void CaptainComission_PirateAttack_AfterBattle(string qName)
{
	Log_QuestInfo("��������� ������� �������.");
	Group_DeleteGroup("Pirate_Attack");
	Island_SetReloadEnableGlobal(pchar.GenQuest.CaptainComission.Island, true);
    pchar.quest.CapComission_DieHard.over = "yes";
	pchar.quest.CaptainComission_PirateShipsOver.over = "yes";
	AddQuestRecord("CaptainComission1", "25");
	AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_GEN));
	AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
	AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
	AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Gen"));
	AddQuestUserData("CaptainComission1", "sNameNom", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
	pchar.GenQuest.CaptainComission.PirateShips = "died";
	DeleteAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak");
}

void CaptainComission_PirateAttack_DieHard(string qName)
{
	Log_QuestInfo("������ � ���� ���, ����� �����.");
	Group_DeleteGroup("Pirate_Attack");
    Island_SetReloadEnableGlobal(pchar.GenQuest.CaptainComission.Island, true);
    pchar.quest.CapComission_AfterBattle.over = "yes";
	pchar.quest.CaptainComission_PirateShipsOver.over = "yes";
	AddQuestRecord("CaptainComission1", "33");
	AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","��"));
	AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
	AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
	AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
	pchar.GenQuest.CaptainComission.PirateShips = "goaway";
	ChangeOfficersLoyality("bad_all",1);
}







void CaptainComission_GaleonInit(ref chref)
{
	pchar.GenQuest.CaptainComission.Nation = chref.nation;
	pchar.GenQuest.CaptainComission.City = GetQuestNationsCity(sti(chref.nation));
	pchar.GenQuest.CaptainComission.Name = GenerateRandomName_Generator(sti(chref.nation), "man");
	pchar.GenQuest.CaptainComission.ShipName = chref.Back.Ship.Name;
	pchar.GenQuest.CaptainComission.City1 = FindAlliedColonyForNationExceptColony(pchar.GenQuest.CaptainComission.City);
	pchar.GenQuest.CaptainComission.Goods = CaptainComission_GetVictimShipGoods();
	pchar.GenQuest.CaptainComission.Speak_Tavern = false;
	pchar.GenQuest.CaptainComission.Prize = GenQuest_GeneratePrize();
	CaptainComission_GenerateShips();
}

void CaptainComission_GenerateShips()
{
	int iShipType, iShipTypeVictim;
	if(sti(pchar.rank) < 20)
	{
		switch(rand(1))
		{
			case 0: iShipType = SHIP_LUGGER; 	break;
			case 1: iShipType = SHIP_SLOOP;		break;
		}
		switch(rand(2))
		{
			case 0: iShipTypeVictim = SHIP_CARAVEL; 	break;
			case 1: iShipTypeVictim = SHIP_BARKENTINE;	break;
			case 2: iShipTypeVictim = SHIP_FLEUT;		break;
		}
	}
	else
	{
		switch(rand(2))
		{
			case 0: iShipType = SHIP_BARQUE;	break;
			case 1: iShipType = SHIP_BRIG;		break;
			case 2:	iShipType = SHIP_CORVETTE;	break;
		}
		switch(rand(2))
		{
			case 0: iShipTypeVictim = SHIP_GALEON_L;	break;
			case 1: iShipTypeVictim = SHIP_GALEON_H;	break;
			case 2:	iShipTypeVictim = SHIP_PINNACE;		break;
		}
	}
	pchar.GenQuest.CaptainComission.ShipType = iShipType;
	pchar.GenQuest.CaptainComission.ShipTypeVictim = iShipTypeVictim;
	pchar.GenQuest.CaptainComission.ShipTypeName = GenerateRandomNameToShip(sti(pchar.GenQuest.CaptainComission.Nation));
	pchar.GenQuest.CaptainComission.VictimShipName = GenerateRandomNameToShip(rand(3));
}


void CaptainComission_TimeIsOver(string qName)
{
	ref sld;
	if(CheckAttribute(pchar,"GenQuest.CaptainComission.variant"))
	{
		if(pchar.GenQuest.CaptainComission.variant == "A1")
		{
			pchar.quest.CaptainComission_SailToShore.over = "yes";
			Group_DeleteGroup("Sea_CapComission_1"); 
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;	
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			return;
		}
		if(pchar.GenQuest.CaptainComission.variant == "A2")
		{
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			return;			
		}
		if(pchar.GenQuest.CaptainComission.variant == "A3")
		{
			pchar.quest.CaptainComission_MeetCanoneerInShoreTimer.over = "yes";
			sld = CharacterFromID("CapComission_Canoneer");
			sld.LifeDay = 0;
			AddQuestRecord("CaptainComission2", "44");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			CloseQuestHeader("CaptainComission2");
			ChangeOfficersLoyality("bad_all", 1);
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			return;
		}
	}	
	
	AddQuestRecord("CaptainComission2", "2");
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
	CloseQuestHeader("CaptainComission2");
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}


void CaptainComission_GenerateQuestContinuation(string qName)
{
	int DaysIsLeft = GetQuestPastDayParam("GenQuest.CaptainComission");
	
	pchar.quest.CaptainComission_TimeIsOver.over = "yes"; 
	if(DaysIsLeft <= 5) 
	{
		pchar.GenQuest.CaptainComission.variant = "A1";
	}
	else
	{
		if(DaysIsLeft <= 10) 
		{
			if(rand(1) == 0) 	pchar.GenQuest.CaptainComission.variant = "A1";
			else				pchar.GenQuest.CaptainComission.variant = "A2";
		}
		else 
		{
			int iRnd = rand(9); 
			if(iRnd < 3) pchar.GenQuest.CaptainComission.variant = "A1";
			else 
			{
				if(iRnd < 6) 	pchar.GenQuest.CaptainComission.variant = "A2";
				else			pchar.GenQuest.CaptainComission.variant = "A3";
			}	
		}
	}
	CaptainComission_GenerateQuestVariant();
}

void CaptainComission_GenerateQuestVariant()
{
	switch(pchar.GenQuest.CaptainComission.variant)
	{
		case "A1":
			Log_QuestInfo("������� 1");
			CaptainComission_GenerateShip();
		break;
		case "A2":
			Log_QuestInfo("������� 2");
			CaptainComission_GenerateRumourCaptainPrison();
		break;
		case "A3":
			Log_QuestInfo("������� 3");
			CaptainComission_GenerateRumourCaptainDeath();
		break;
	}
}

void CaptainComission_GenerateShip()
{
	int iRank = sti(pchar.rank) + 5 + rand(MOD_SKILL_ENEMY_RATE);
	int iNation = sti(pchar.GenQuest.CaptainComission.Nation);
	ref chref = GetCharacter(NPC_GenerateCharacter("CapComission_1", "off_"+NationShortName(iNation)+"_"+(rand(1)+1), "man", "man", iRank, iNation, -1, true, "quest"));
	
	chref.name = pchar.GenQuest.CaptainComission.Name;
	chref.lastname = "";
	chref.city = pchar.GenQuest.CaptainComission.City;
	chref.dialog.filename      = "GenQuests_Dialog.c";
	chref.DeckDialogNode	   = "CaptainComission_301";	 
	chref.dialog.currentnode   = "CaptainComission_301";
		
	chref.Ship.Name = pchar.GenQuest.CaptainComission.ShipTypeName;
	FantomMakeCoolSailor(chref, sti(pchar.GenQuest.CaptainComission.ShipType), chref.Ship.Name, CANNON_TYPE_CULVERINE_LBS18, 90, 90, 90);	
	FantomMakeCoolFighter(chref, makeint(pchar.rank) + rand(10) + 5, 90, 50, LinkRandPhrase("blade_06","blade_08","blade_10"), "pistol3", "grapeshot", 80);
	chref.cirassId = Items_FindItemIdx("cirass1");  
	LAi_SetHP(chref, 200 + makeint(pchar.rank) * 5, 200 + makeint(pchar.rank) * 5);

	SetCharacterPerk(chref, "MusketsShoot");
	SetCharacterPerk(chref, "Energaiser"); 	
	
	chref.ship.Crew.Morale = 90;
	ChangeCrewExp(chref, "Sailors", 100);
	ChangeCrewExp(chref, "Cannoners", 100);
	ChangeCrewExp(chref, "Soldiers", 100);
   		
	chref.AlwaysFriend = true;
	chref.Abordage.Enable = false; 
	
	string sGroup = "Sea_CapComission_1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
    Group_SetType(sGroup, "war");
	
	SetCharacterRelationBoth(sti(chref.index), GetMainCharacterIndex(), RELATION_FRIEND);
	
	int IslandID = FindIsland(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
	ref pLoc = &Islands[IslandID];
	float x, y, z;
	FindIslandLocatorXYZ(IslandID, "reload1", &x, &y, &z); 
	string sLocator = GetSeaQuestShipFarLocator(pLoc, "Quest_ships", x, y, z);
	
	Group_AddCharacter(sGroup, "CapComission_1");
    Group_SetGroupCommander(sGroup, "CapComission_1");
	Group_SetAddress(sGroup, GetArealByCityName(pchar.GenQuest.CaptainComission.City),"quest_ships", sLocator);
	Group_SetTaskNone(sGroup);
	
	SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
}

void CaptainComission_ExitFromLoc(string qName)
{
	ref sld;
	if(pchar.GenQuest.CaptainComission == "close")
	{
		if(pchar.GenQuest.CaptainComission.variant == "A1")
		{
			sld = CharacterFromID("CapComission_1");
			sld.Dialog.Filename = "Capitans_dialog.c"; 
			sld.greeting        = "Gr_Commander";
			sld.DeckDialogNode  = "Go_away";
			sld.LifeDay = 2;					
		}
		if(pchar.GenQuest.CaptainComission.variant == "A3")
		{
			sld = CharacterFromID("CapComission_Canoneer");
			sld.LifeDay = 0;					
		}
		DeleteAttribute(pchar, "GenQuest.CaptainComission");
	}
}

int CaptainComission_GetVictimShipGoods()
{
	int iGoodIdx;
	switch (rand(6))
    {
        case 0 :
            iGoodIdx = GOOD_CHOCOLATE;
        break;
        case 1 :
            iGoodIdx = GOOD_TOBACCO;
        break;
        case 2 :
            iGoodIdx = GOOD_COFFEE;
        break;
        case 3 :
            iGoodIdx = GOOD_MAHOGANY;
        break;
        case 4 :
            iGoodIdx = GOOD_CINNAMON;
        break;
        case 5 :
            iGoodIdx = GOOD_EBONY;
        break;		
        case 6 :
            iGoodIdx = GOOD_COPRA;
        break;		
    }
	return iGoodIdx;
}

void CaptainComission_CapIsOut(string qName) 
{
	ref sld;
	pchar.GenQuest.CaptainComission = "CaptainIsOut"; 
	pchar.quest.CaptainComission_CapIsDead.over = "yes";
	Group_DeleteGroup("Sea_CapComission_1");
	sld = CharacterFromID("CapComission_1");
	sld.LifeDay = 0;	
	
	AddQuestRecord("CaptainComission2", "6");
	AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("��","���"));
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
	AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
	CloseQuestHeader("CaptainComission2");	
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_CapIsDead(string qName)
{
	pchar.quest.CaptainComission_CapIsOut.over = "yes";	
	AddQuestRecord("CaptainComission2", "5");
	AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("��","���"));
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
	AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
	CloseQuestHeader("CaptainComission2");	
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_toShore() 
{
	ref sld;
	Group_DeleteGroup("Sea_CapComission_1");
	sld = CharacterFromID("CapComission_1");
	sld.LifeDay = 0;
	
	DeleteAttribute(pchar, "ship"); 
	pchar.ship.name = "";
	pchar.ship.type = SHIP_NOTUSED;
	
	SetCharacterShipLocation(pchar, "");
	
	pchar.money = 0;
	RemoveAllPassengersAndCompanions();
	CleanAllCabinBoxes();
	
	
	
	pchar.quest.Munity = "Deads";
	pchar.location.from_sea = pchar.GenQuest.CaptainComission.City + "_town";
	
	AddQuestRecord("CaptainComission2", "4");
	AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
	AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
	CloseQuestHeader("CaptainComission2");
	
	if(bDisableMapEnter) bDisableMapEnter = false; 
	
	DoReloadFromDeckToLocation(pchar.GenQuest.CaptainComission.ShoreLocation, "reload", "sea");
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_SailToShore(string qName)
{
	Log_QuestInfo("���������� ���������� �� ���������� ������� � �����");
	ref sld = characterFromId("CapComission_1");
	SetCharacterShipLocation(sld, pchar.GenQuest.CaptainComission.ShoreLocation);
	SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ShoreLocation, false); 
}


void CaptainComission_MeetInShore(string qName)
{
	chrDisableReloadToLocation = true;
	pchar.quest.CaptainComission_TimeIsOver.over = "yes"; 
	ref sld = characterFromId("CapComission_1");
	if(pchar.GenQuest.CaptainComission.variant == "A1")
	{	
		sld.dialog.currentnode = "CaptainComission_315";	
	}
	if(pchar.GenQuest.CaptainComission.variant == "A2")
	{
		sld.dialog.currentnode = "CaptainComission_383";
		LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, true);
		pchar.quest.CaptainComission_CapEscapeTimer.over = "yes";	
		DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain");
		CaptainComission_GenerateGangInShore();
	}
	PlaceCharacter(sld, "goto", "random_must_be_near");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
}

void CaptainComission_GenerateShorePatrol()
{
	ref sld;
	string attrName;

	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	int iTemp = sti(pchar.GenQuest.CaptainComission.Nation);
	pchar.GenQuest.CaptainComission.SoldierQty = makeint(2 * GetOfficersQuantity(pchar) + 3);
	for (int i = 2; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
	{
		sld = SetFantomDefenceForts("", "", iTemp, "CoastalGuards");
		attrName = "SoldierIDX" + i;
    	pchar.GenQuest.CaptainComission.(attrName) = sld.index;
		LAi_SetActorType(sld);
    	LAi_ActorFollow(sld, pchar, "", 38);
		LAi_CharacterDisableDialog(sld);
		sld.greeting = "Gr_Costal_Guards";
	}
	sld = SetFantomOfficer("", "", iTemp, "CoastalGuards");
	pchar.GenQuest.CaptainComission.SoldierIDX1 = sld.index;
	LAi_SetActorType(sld);
	sld.Dialog.Filename = "GenQuests_Dialog.c";
	sld.Dialog.CurrentNode = "CaptainComission_317";
	sld.greeting = "Gr_Costal_Guards";

	LAi_ActorDialog(&Characters[makeint(pchar.GenQuest.CaptainComission.SoldierIDX1)], pchar, "", 35, 1);
	LAi_group_SetCheck("CoastalGuards", "OpenTheDoors");	
	LAi_group_SetCheckFunction("CoastalGuards", "CaptainComission_AfterShoreBattle"); 
}

void CaptainComission_AfterShoreBattle(string qName)
{
	ref sld = characterFromId("CapComission_1");	
	if (LAi_IsDead(sld))
	{
		AddQuestRecord("CaptainComission2", "9");
		AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat"));
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		CloseQuestHeader("CaptainComission2");	
		DeleteAttribute(pchar, "GenQuest.CaptainComission");	
	}
	else
	{
		sld.dialog.currentnode = "CaptainComission_320";	
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);	
	}
}

void CaptainComission_GenerateCoastalPatrol()
{
	ref CoastGuard;
	int i;
	int iNation = sti(pchar.GenQuest.CaptainComission.Nation);
	string Model;
	
	for (i = 1; i <= 3; i++)
    {
        Model = "off_" + NationShortName(iNation) + "_" + (rand(1) + 1);
		CoastGuard = GetCharacter(NPC_GenerateCharacter("Coastal_Captain0" + i, Model, "man", "man", sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE), iNation, 3, true, "officer")); 
		SetFantomParam(CoastGuard);
		SelectCoastalGuardShip(CoastGuard);
		CoastGuard.AlwaysEnemy = true;
		CoastGuard.DontRansackCaptain = true;
		CoastGuard.AlwaysSandbankManeuver = true;
		Group_AddCharacter("Coastal_Guards", CoastGuard.id);
		SetCharacterRelationBoth(sti(CoastGuard.index), GetMainCharacterIndex(), RELATION_ENEMY);
		if (makeint(pchar.rank) < 6 && i == 1 && GetCompanionQuantity(pchar) == 1) break;
		if (makeint(pchar.rank) < 9 && i == 2 && GetCompanionQuantity(pchar) < 3) break;
    }
	Group_SetGroupCommander("Coastal_Guards", "Coastal_Captain01");
	Group_SetAddress("Coastal_Guards", Islands[GetCharacterCurrentIsland(Pchar)].id, "", "");
	Group_SetPursuitGroup("Coastal_Guards", PLAYER_GROUP);
	Group_SetTaskAttack("Coastal_Guards", PLAYER_GROUP);
	Group_LockTask("Coastal_Guards");
}

void CaptainComission_CapShip_Sink(string qName)
{
	pchar.quest.CaptainComission_MapEnter.over = "yes";
	AddQuestRecord("CaptainComission2", "12");
	AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
	AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
	AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
	CloseQuestHeader("CaptainComission2");	
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_MapEnter(string qName)
{
	DeleteAttribute(pchar,"GenQuest.CannotWait");
	pchar.quest.CaptainComission_CapShip_Sink.over = "yes";
	SetFunctionLocationCondition("CaptainComission_ConvoyInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
	pchar.quest.CaptainComission_Ship_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.CaptainComission_Ship_Sink.win_condition.l1.character = "CapComission_1";
	pchar.quest.CaptainComission_Ship_Sink.function = "CaptainComission_Ship_Sink";
	SetFunctionTimerCondition("CaptainComission_ConvoyTimeIsOut", 0, 0, sti(pchar.GenQuest.CaptainComission.iDay) * 2, false);
	SaveCurrentQuestDateParam("GenQuest.CaptainComission");
}

void CaptainComission_ConvoyInShore(string qName)
{
	ref sld;
	pchar.quest.CaptainComission_Ship_Sink.over = "yes";
	pchar.quest.CaptainComission_ConvoyTimeIsOut.over = "yes";
	
	int DaysIsLeft = GetQuestPastDayParam("GenQuest.CaptainComission");
	
	sld = characterFromId("CapComission_1");	
	PlaceCharacter(sld, "goto", "random_must_be_near");
	if(DaysIsLeft <= sti(pchar.GenQuest.CaptainComission.iDay))
	{
		LAi_SetActorTypeNoGroup(sld);
		CaptainComission_GenerateGangInShore();
	}
	else
	{
		sld.dialog.currentnode = "CaptainComission_340";	
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);	
	}		
}

void CaptainComission_GenerateGangInShore()
{
	string encGroup, str, locator;
	int num, i, k, iNation, iRank, n;
	ref pLoc, sld;
	aref grp;
	
	chrDisableReloadToLocation = true;
	pLoc = &locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)];
	encGroup = "smugglers";
	str = "locators." + encGroup;
	makearef(grp, pLoc.(str));
	num = GetAttributesNum(grp); 
	if (num <= 0) num = 1;
	
	str = "Gang" + "_";
	string sGroup = "GangGroup_0"; 
	LAi_LocationFightDisable(pLoc, true);	
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
		
	arrayNPCModelHow = 0;
	
	for (i = 0; i < num; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter(str + i, "off_hol_2", "man", "man", 5, PIRATE, 3, true, "hunter"));
        SetFantomParamHunter(sld); 
		SetModelPirate(sld);
		k = 0;
		while (!CheckNPCModelUniq(sld) && k < 10)
		{
		    k++;
			SetModelPirate(sld);
		}
		arrayNPCModel[arrayNPCModelHow] = sld.model;
		arrayNPCModelHow++;

		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, sGroup);
		pchar.GenQuest.CaptainComission.GangNum = num;
		sld.greeting = "Gr_Smuggler_OnShore";
		locator = GetAttributeName(GetAttributeN(grp, i));
		ChangeCharacterAddressGroup(sld, pLoc.id, encGroup, locator);
		LAi_SetImmortal(sld, true);
		if (i == 0) 
		{
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true; 
			sld.dialog.filename = "GenQuests_Dialog.c";
			if(pchar.GenQuest.CaptainComission.variant == "A1")
			{
				sld.Dialog.CurrentNode = "CaptainComission_326";
			}
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				if(pchar.GenQuest.CaptainComission == "GetGoodsEscape")
				{
					sld.Dialog.CurrentNode = "CaptainComission_396";
				}
				else
				{
					sld.Dialog.CurrentNode = "CaptainComission_384";
				}	
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				sld.Dialog.CurrentNode = "CaptainComission_360";
			}
		}
		else
		{
			LAi_CharacterDisableDialog(sld);
		}
	}
	sld = CharacterFromID("CapComission_1");
	if(pchar.GenQuest.CaptainComission.variant == "A1")
	{
		sld.Dialog.CurrentNode = "CaptainComission_326_0";
	}	
	if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "GetGoodsEscape")
	{
		sld.Dialog.CurrentNode = "CaptainComission_396_0";
	}	
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);		
}

void CaptainComission_DialogInShore()
{
	ref sld = CharacterFromID("CapComission_1");
	sld.CaptainComission.Name = pchar.GenQuest.CaptainComission.Name;
	sld.CaptainComission.CapName = pchar.GenQuest.CaptainComission.CapName;
	sld.CaptainComission.FullName = GetFullName(pchar);
	sld.CaptainComission.ShipTypeVictim = pchar.GenQuest.CaptainComission.ShipTypeVictim;

	bDisableCharacterMenu = true;
	ChangeShowIntarface();
	InterfaceStates.Buttons.Save.enable = false;
	StartQuestMovie(true, true, true);
	LAi_SetActorType(pchar);	

	SetMainCharacterIndex(GetCharacterIndex("CapComission_1"));
	pchar = GetMainCharacter();
	locCameraTarget(pchar)
	locCameraFollow();
	LAi_SetActorType(pchar);		
	LAi_SetActorType(CharacterFromID("Gang_0"));
	SetActorDialogAny2Pchar("Gang_0", "", -1.0, 0.0);
	LAi_ActorFollow(pchar, CharacterFromID("Gang_0"), "ActorDialog_Any2Pchar", -1);		
}


void CaptainComission_GangDialog()
{
	ref sld;

	SetMainCharacterIndex(1);
    pchar = GetMainCharacter();
    LAi_SetPlayerType(pchar);
	locCameraTarget(pchar);
    locCameraFollow();
    EndQuestMovie(); 
	ChangeShowIntarface();
	bDisableCharacterMenu = false;
	
	sld = CharacterFromID("Gang_0");
	sld.Dialog.CurrentNode = "CaptainComission_328";
	LAi_SetActorType(pchar); 
	LAi_ActorTurnToCharacter(pchar, sld);
	LAi_SetActorType(sld);
	SetActorDialogAny2Pchar(sld.id, "", 0.0, 1.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
}

void CaptainComission_GangExit()
{
	ref sld;
	int iTemp;
	float locx, locy, locz;
	
	DoQuestCheckDelay("OpenTheDoors", 1.0);
	LAi_SetPlayerType(pchar);
	GetCharacterPos(pchar, &locx, &locy, &locz);
    for (int i = 0; i < sti(pchar.GenQuest.CaptainComission.GangNum); i++)
	{
		sld = characterFromID("Gang_" + i);
		LAi_SetActorType(sld); 
		LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", -1.0);			
		iTemp = GetCharacterIndex("Gang_" + i);
		if (iTemp != -1)
		{
			characters[iTemp].lifeDay = 0;
		}
	}
	sld = characterFromID("CapComission_1");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", -1.0);
	sld.lifeDay = 0;
	pchar.quest.CaptainComission_ExitFromShoreAfterGang.win_condition.l1 = "MapEnter";           	
    pchar.quest.CaptainComission_ExitFromShoreAfterGang.function = "CaptainComission_ExitFromShoreAfterGang";
	InterfaceStates.Buttons.Save.enable = true; 
}

void CaptainComission_ExitFromShoreAfterGang(string qName)
{	
	if (GetCharacterIndex("CapComission_2") > 0) 
	{
		characters[GetCharacterIndex("CapComission_2")].lifeDay = 0;
	}
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_ChangeCaptain()
{
	int iRank = sti(pchar.rank) + 5 + rand(MOD_SKILL_ENEMY_RATE);
	int iNation = sti(pchar.GenQuest.CaptainComission.Nation);
	aref	arShip1, arShip2;
	ref chref, sld;
	
	chref = GetCharacter(NPC_GenerateCharacter("CapComission_2", "mercen_"+(rand(14)+1), "man", "man", iRank, iNation, -1, true, "hunter"));
	chref.name = GenerateRandomName_Generator(sti(chref.nation), "man");
	chref.lastname = "";
	SetCharacterPerk(chref, "MusketsShoot");
	SetCharacterPerk(chref, "Energaiser"); 	
	FantomMakeCoolFighter(chref, makeint(pchar.rank) + rand(10) + 5, 90, 50, "blade_06", "pistol3", "grapeshot", 80);
	chref.cirassId = Items_FindItemIdx("cirass1");  
	LAi_SetHP(chref, 200 + makeint(pchar.rank) * 5, 200 + makeint(pchar.rank) * 5);
	
	DeleteAttribute(chref, "ship"); 
	chref.ship = ""; 
	
	sld = CharacterFromID("CapComission_1");
	
	makearef(arShip1, sld.Ship);
	makearef(arShip2, chref.Ship);
	CopyAttributes(arShip2,arShip1);
	DeleteAttribute(sld, "ship"); 
	sld.ship.type = SHIP_NOTUSED;
	SeaAI_SetOfficer2ShipAfterAbordage(chref, sld); 
	
	RemoveCharacterCompanion(pchar, sld);

	Group_DelCharacter(PLAYER_GROUP, sld.id);
	
	string sGroup = "Sea_CapComission_2";
	Group_FindOrCreateGroup(sGroup);
    Group_SetType(sGroup, "war");
			
	Group_AddCharacter(sGroup, "CapComission_2");
    Group_SetGroupCommander(sGroup, "CapComission_2");
	Group_SetAddress(sGroup, Islands[GetCharacterCurrentIsland(Pchar)].id, "", "");
	Group_SetPursuitGroup(sGroup, PLAYER_GROUP);
	
	chref.nation = PIRATE;
	Ship_NationAgressivePatent(chref);
	Ship_FlagRefresh(chref); 
	
	SetCharacterRelationBoth(sti(chref.index), GetMainCharacterIndex(), RELATION_ENEMY);
	DeleteAttribute(chref, "AlwaysFriend"); 
	DeleteAttribute(chref,"Abordage.Enable");
	
	Group_SetTaskAttack(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);			
}

void CaptainComission_GangDied(string qName)
{
	if(pchar.GenQuest.CaptainComission.variant == "A1")
	{
		AddQuestRecord("CaptainComission2", "16");
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat")));
		CloseQuestHeader("CaptainComission2");	
		pchar.quest.CaptainComission_MapEnterAfterGang.win_condition.l1 = "MapEnter";
		pchar.quest.CaptainComission_MapEnterAfterGang.function = "CaptainComission_ExitFromShoreAfterGang"; 
	}
	if(pchar.GenQuest.CaptainComission.variant == "A2")
	{
		ref sld = CharacterFromId("CapComission_1");	
		if (LAi_IsDead(sld)) 
		{
			AddQuestRecord("CaptainComission2", "33");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			OfficersReaction("bad");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");			
		}
		else
		{
			sld.dialog.currentnode = "CaptainComission_401";	
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
		}
	}
	InterfaceStates.Buttons.Save.enable = true;
}

void CaptainComission_ConvoyTimeIsOut(string qName)
{
	pchar.quest.CaptainComission_ConvoyInShore.over = "yes"; 
	pchar.quest.CaptainComission_Ship_Sink.over = "yes";
	ref sld = CharacterFromId("CapComission_1");
	RemoveCharacterCompanion(pchar, sld);
	AddQuestRecord("CaptainComission2", "14");
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Acc"));
	CloseQuestHeader("CaptainComission2");	
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_Ship_Sink(string qName)
{
	pchar.quest.CaptainComission_ConvoyInShore.over = "yes"; 
	pchar.quest.CaptainComission_ConvoyTimeIsOut.over = "yes";
	AddQuestRecord("CaptainComission2", "13");
	AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))); 
	AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
	AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	CloseQuestHeader("CaptainComission2");	
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}


void CaptainComission_GenerateRumourCaptainPrison()
{
	string sShipType = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"));
	
	
	
	
	
}

void CaptainComission_RumourCaptainPrison()
{
	if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
	{
		AddQuestRecord("CaptainComission2", "18");
		AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);				
		pchar.GenQuest.CaptainComission.GetRumour = true;
		SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");	
		SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
	}
}

void CaptainComission_GetSecretTimeIsOut(string qName)
{
	AddQuestRecord("CaptainComission2", "20");
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);			
	AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
	CloseQuestHeader("CaptainComission2");	
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_GenerateCaptainInPrison()
{
	ref sld = GetCharacter(NPC_GenerateCharacter("CapComission_1" , "mercen_19", "man", "man", 10, sti(pchar.GenQuest.CaptainComission.Nation), -1, true, "quest"));
	SetSPECIAL(sld, 10,9,10,5,10,9,10);
	SetRandSelfSkill(sld, 75, 95);
	SetRandShipSkill(sld, 75, 95); 
	FantomMakeCoolFighter(sld, sti(pchar.rank) + rand(15), 95, 95, LinkRandPhrase("blade_13","blade_14","blade_09"), "pistol2"," grapeshot", 10);	
	sld.name = pchar.GenQuest.CaptainComission.Name;
	sld.lastname = "";
	sld.greeting = "Gr_prison";
	sld.dialog.FileName = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "CaptainComission_370";
	RemoveAllCharacterItems(sld, true); 
	ChangeCharacterAddress(sld, "none", ""); 
}

void CaptainComission_ExitFromTown(string qName)
{
	bQuestDisableMapEnter = true;
	QuestCloseSeaExit();
    DoQuestCheckDelay("CaptainComission_MeetWithCaptain", 1);
}	

void CaptainComission_CapEscapeTimer(string qName)
{
	Log_QuestInfo("���������� ���������� �� ������� ��������");
	ref sld = characterFromId("CapComission_1");
	RemovePassenger(pchar, sld);
	ChangeCharacterAddress(sld, "none", "");
	sld.lifeDay = 0; 
	pchar.GenQuest.CaptainComission = "CapEscape";
	pchar.GenQuest.CaptainComission.canSpeakBoatswain = true;
	pchar.TownEscape = true;
	pchar.quest.CaptainComission_ExitFromTown.win_condition.l1 	= "EnterToSea";           	
	pchar.quest.CaptainComission_ExitFromTown.function    		= "CaptainComission_ExitFromTown";
}

void CaptainComission_GangDialogGetGoods()
{
	ref sld;
	for (int i = 0; i < sti(pchar.GenQuest.CaptainComission.GangNum); i++)
	{
		sld = characterFromID("Gang_" + i);
		LAi_SetActorType(sld); 	
		if (i == 0) LAi_ActorDialog(sld, pchar, "", -1, 0); 
		else LAi_ActorFollow(sld, &characters[GetCharacterIndex("Gang_0")], "", -1);
	}	
}

void CaptainComission_CheckCaptainAfterBattle(string qName)
{
	ref sld = characterFromId("CapComission_1");	
	if (LAi_IsDead(sld)) 
	{
		AddQuestRecord("CaptainComission2", "22");
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		CloseQuestHeader("CaptainComission2");	
		DeleteAttribute(pchar, "GenQuest.CaptainComission");	
	}
	else 
	{
		if(GetCharacterEquipByGroup(sld, BLADE_ITEM_TYPE) == "") 
		{
			string sEquipItem = GenQuest_GenerateGoodBlade();
			AddItems(sld, sEquipItem, 1);
			EquipCharacterByItem(sld, sEquipItem);
		}	
		sld.dialog.currentnode = "CaptainComission_387";	
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);	
	}	
}

void CaptainComission_CheckCaptainDied(string qName)
{
	if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
	{
		AddQuestRecord("CaptainComission2", "28");
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
		pchar.GenQuest.CaptainComission = "GetGoodsSuccess";
		OfficersReaction("good");
		SetFunctionTimerConditionParam("CaptainComission_SpeakMayorGoods", 0, 0, 1, MakeInt(24 - GetHour()), false);
	}
	else
	{
		AddQuestRecord("CaptainComission2", "27");
		AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
		AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
		CloseQuestHeader("CaptainComission2");
		int iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
		if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
		SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));
		OfficersReaction("bad");
		ChangeCharacterComplexReputation(pchar,"nobility", -5);
		CaptainComission_GenerateCoastalPatrol();
		pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
		pchar.quest.CaptainComission_MapEnter.win_condition = "CaptainComission_MapEnterCapDied";  
	}
}

void CaptainComission_SpeakMayorGoods(string qName)
{
	AddQuestRecord("CaptainComission2", "29");
	AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	pchar.GenQuest.CaptainComission = "GetGoods";
}

void CaptainComission_CapMeetInShore(string qName)
{	
	int DaysIsLeft = GetQuestPastDayParam("GenQuest.CaptainComission.DeleiveCapShore");
	
	ref sld = characterFromId("CapComission_1");	
	RemovePassenger(pchar, sld);	
	PlaceCharacter(sld, "goto", "random_must_be_near");
	if(DaysIsLeft <= sti(pchar.GenQuest.CaptainComission.iDay))
	{
		LAi_SetActorTypeNoGroup(sld);
		CaptainComission_GenerateGangInShore();
	}
	else
	{
		sld.dialog.currentnode = "CaptainComission_392";	
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);	
	}				
}

void CaptainComission_CaptainDiedDuel(string qName)
{
	if(CheckAttribute(pchar, "GenQuest.CaptainComission.Duel"))
	{
		AddQuestRecord("CaptainComission2", "33");
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);	
	}
	else
	{
		AddQuestRecord("CaptainComission2", "31");
		AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	}	
	CloseQuestHeader("CaptainComission2");
	ChangeCharacterComplexReputation(pchar,"nobility", -8);
	OfficersReaction("bad");
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_BattleInShore(string qName)
{
	ref sld;
	string sTemp = "Gang_";
	string sGroup = "GangGroup_0";			
	LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
	int iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("CapComission_1");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	
	for(int i = 0; i < iTemp; i++)
	{
		sld = CharacterFromID(sTemp + i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, sGroup);
		LAi_SetImmortal(sld, false);
	}			
	LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
	LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
	LAi_SetFightMode(pchar, true);
}

bool CaptainComission_CheckAllPassengersHired()
{
    int iQty = GetPassengersQuantity(pchar);
    int i = 0;
	int n = 0;
	int idx;
	ref ch;
			
 	while (i < iQty)
	{
		i++;
		idx = GetPassenger(pchar, n);
		if (idx == -1) break;
		ch = GetCharacter(idx);
		if(CheckAttribute(ch, "CaptainComission")) return true;
		n++;
	}
    for (i=0; i<COMPANION_MAX; i++)
	{
		idx = GetCompanionIndex(pchar, i);
		if (idx != -1)
		{
            ch = GetCharacter(idx);
			if(CheckAttribute(ch, "CaptainComission")) return true;
		}
	}
	return false;
} 


void CaptainComission_GenerateRumourCaptainDeath()
{
	string sShipType = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"));
	
	
	
	
	
}

void CaptainComission_RumourCaptainDeath()
{
	if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
	{
		AddQuestRecord("CaptainComission2", "37");
		AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
		AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);		
		pchar.GenQuest.CaptainComission.GetRumour = true;
		SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
	}
}

void CaptainComission_GenerateCanoneer(string qName)
{
	int Rank = sti(pchar.rank) + 3 + rand(10);
	ref sld = GetCharacter(NPC_GenerateCharacter("CapComission_Canoneer", "officer_15", "man", "man", 10, sti(pchar.GenQuest.CaptainComission.Nation), -1, true, "quest"));
	FantomMakeCoolFighter(sld, Rank, 100, 90, "blade_09", "pistol3", "bullet", 150);
	sld.name = GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM);
	sld.lastname = "";
	sld.dialog.FileName = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "CaptainComission_Canoneer";
	sld.greeting = "cit_quest";
	sld.CityType = "citizen";
	sld.City = pchar.GenQuest.CaptainComission.City;
	LAi_SetImmortal(sld, true);	
	string sLoc = pchar.GenQuest.CaptainComission.City + "_tavern"; 
	ref pLoc = &locations[FindLocation(sLoc)];
	if (!LAi_CheckLocatorFree("sit", "sit_front2")) FreeSitLocator(sLoc, "sit_front2");
	FreeSitLocator(sLoc, "sit_base2");
	ChangeCharacterAddressGroup(sld, sLoc, "sit", "sit_base2");
	LAi_SetSitType(sld);
}


void CaptainComission_CanoneerWaitMoney(string qName)
{
	ref sld = characterFromId("CapComission_Canoneer");
	ChangeCharacterAddress(sld, "none", ""); 
	sld.LifeDay = 0;
	ChangeOfficersLoyality("bad_all", 1);
	AddQuestRecord("CaptainComission2", "42");
	AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
	CloseQuestHeader("CaptainComission2");
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_MeetCanoneerInShoreTimer(string qName)
{
	SetFunctionLocationCondition("CaptainComission_MeetCanoneerInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
}

void CaptainComission_MeetCanoneerInShore(string qName)
{
	pchar.quest.CaptainComission_TimeIsOver.over = "yes";
	pchar.quest.CaptainComission_CanoneerWaitMoney.over = "yes";
	if(pchar.Location == pchar.location.from_sea) 
	{
		chrDisableReloadToLocation = true;	
		CaptainComission_GenerateGangInShore();	
		ref sld = characterFromId("CapComission_Canoneer");
		LAi_SetImmortal(sld, true);
		LAi_CharacterEnableDialog(sld);
		sld.dialog.currentnode = "CaptainComission_350";	
		PlaceCharacter(sld, "goto", "random_must_be_near");
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);	
	}
	else 
	{ 
		sld = CharacterFromID("CapComission_Canoneer");
		sld.LifeDay = 0;
		AddQuestRecord("CaptainComission2", "44");
		AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
		CloseQuestHeader("CaptainComission2");
		ChangeOfficersLoyality("bad_all", 1);
		DeleteAttribute(pchar, "GenQuest.CaptainComission");		
	}	
}

void CaptainComission_NoGangDialog(string qName)
{
	ref sld;
	int iTemp;
	float locx, locy, locz;
	string sTemp;
	
	GetCharacterPos(pchar, &locx, &locy, &locz);
	sTemp = LAi_FindNearestLocator("reload", locx, locy, locz);
	sld = characterFromId("CapComission_Canoneer");
	LAi_SetActorType(sld); 
	LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);			
	sld.LifeDay = 0;
	for(int i = 0; i < sti(pchar.GenQuest.CaptainComission.GangNum); i++)
	{
		iTemp = GetCharacterIndex("Gang_" + i);
		if (iTemp != -1)
		{
			sld = characterFromId("Gang_" + i);
			LAi_SetActorType(sld); 
			LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "", -1.0);			
			sld.lifeDay = 0;
		}
	}
	AddQuestRecord("CaptainComission2", "45");
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
	CloseQuestHeader("CaptainComission2");	
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_CheckGangAfterBattle(string qName)
{
	ref sld;
	int iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
	if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;	
	SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));
	if (GetCharacterIndex("CapComission_Canoneer") > 0) 
	{
		sld = CharacterFromId("CapComission_Canoneer");
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, false);
		sld.dialog.currentnode = "CaptainComission_365";	
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);			
		AddQuestRecord("CaptainComission2", "47");
		AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission2", "sSum", iGoods);
		AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
		AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ACC));
		AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity));
		SetFunctionLocationCondition("CaptainComission_DeleiveCanoneer", pchar.GenQuest.CaptainComission.CanoneerCity + "_town", false);
	}
	else 
	{
		AddQuestRecord("CaptainComission2", "46");
		AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
		AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
		AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
		AddQuestUserData("CaptainComission2", "sSum", iGoods);
		AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
		CloseQuestHeader("CaptainComission2");
		OfficersReaction("bad");
		ChangeCharacterComplexReputation(pchar,"nobility", -5);
	}
	CaptainComission_EnterToSeaAfterShoreBattle();
	pchar.quest.CaptainComission_MapEnterAfterShoreBattle.win_condition.l1 = "MapEnter";
    pchar.quest.CaptainComission_MapEnterAfterShoreBattle = "CaptainComission_MapEnterAfterShoreBattle";
}

void CaptainComission_DeleiveCanoneer(string qName)
{
	ref sld = characterFromId("CapComission_Canoneer");	
	RemovePassenger(pchar, sld);
	sld.dialog.currentnode = "CaptainComission_366";		
	PlaceCharacter(sld, "goto", pchar.location);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
}

void CaptainComission_EnterToSeaAfterShoreBattle()
{
	ref sld;
	Group_DeleteGroup("Pirate_Guards");	
	Group_FindOrCreateGroup("Pirate_Guards");
    Group_SetType("Pirate_Guards", "pirate");
	for (int i = 1; i <= 3; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("Pirate_Captain0" + i, "mercen_"+(rand(14)+14), "man", "man", 5, PIRATE, 3, true, "quest")); 
		FantomMakeCoolFighter(sld, makeint(pchar.rank) + rand(10) + 5, 90, 50, "blade_06", "pistol3","grapeshot", 80);
		SetFantomParam(sld);
		SelectCoastalGuardShip(sld);
		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.AlwaysSandbankManeuver = true;
		Group_AddCharacter("Pirate_Guards", sld.id);
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
    }
	Group_SetGroupCommander("Pirate_Guards", "Pirate_Captain01");
	Group_SetPursuitGroup("Pirate_Guards", PLAYER_GROUP);
	Group_SetAddress("Pirate_Guards", Islands[GetCharacterCurrentIsland(Pchar)].id, "", "");
	Group_SetTaskAttack("Pirate_Guards", PLAYER_GROUP);
	Group_LockTask("Pirate_Guards");
}






void Convict_LocExit(string qName)
{
	ref sld;
	int i;
	if(pchar.GenQuest.Convict == "close")
	{
		for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
		{
			sld = CharacterFromID("Convict_" + i);
			sld.LifeDay = 0;
		}
		LAi_group_Delete("ConvictGroup");
		DeleteAttribute(pchar, "GenQuest.Convict");
		return;
	}
	if(pchar.GenQuest.Convict == "fight")
	{
		ChangeCharacterComplexReputation(pchar,"nobility", -2);
		OfficersReaction("bad");		
		DeleteAttribute(pchar, "GenQuest.Convict");
		return;
	}
	if(pchar.GenQuest.Convict == "ToShore" || pchar.GenQuest.Convict == "GetShip" || pchar.GenQuest.Convict == "ToMayak")
	{
		for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
		{
			sld = CharacterFromID("Convict_" + i);
			ChangeCharacterAddress(sld, "none", ""); 
		}
	}
	if(pchar.GenQuest.Convict == "FightInShore" || pchar.GenQuest.Convict == "ShoreFight" || pchar.GenQuest.Convict == "MayakFight")
	{
		if(pchar.GenQuest.Convict == "FightInShore")
		{
			AddQuestRecord("Convict", "6");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("����� �����������","'������� ���� �����'"));
			AddQuestUserData("Convict", "sSex1", GetSexPhrase("","�"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString("Shore" + pchar.GenQuest.Convict.ShoreLocation + "Acc"));
		}
		if(pchar.GenQuest.Convict == "ShoreFight")
		{
			AddQuestRecord("Convict", "9");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("��","���"));
		}	
		if(pchar.GenQuest.Convict == "MayakFight")
		{
			AddQuestRecord("Convict", "13");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("����� �����������","'������� ���� �����'"));
			AddQuestUserData("Convict", "sSex1", GetSexPhrase("","�"));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Abl"));
		}	
		
		CloseQuestHeader("Convict");
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		OfficersReaction("bad");		
		DeleteAttribute(pchar, "GenQuest.Convict");	
	}
}

void Convict_GetMineType()
{
	pchar.GenQuest.Convict.MineType = drand(2) + 1;
}

void Convict_MeetInShore(string qName)
{
	ref sld;
	int i;
	pchar.quest.Convict_SetTimer.over = "yes";
	pchar.quest.Convict_MapEnter.over = "yes";
	
	DeleteAttribute(&Locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)], "DisableEncounters");
		
	if(pchar.Location == pchar.location.from_sea) 
	{
		chrDisableReloadToLocation = true;
		bDisableFastReload = true;	
		for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
		{
			sld = CharacterFromID("Convict_" + i);
			PlaceCharacter(sld, "goto", pchar.location);
			if(i == 0)
			{
				LAi_CharacterEnableDialog(sld);
				if(pchar.GenQuest.Convict == "GetShip")
				{
					sld.dialog.currentnode = "Convict_15";	
				}
				if(pchar.GenQuest.Convict == "ToShore")	
				{
					sld.dialog.currentnode = "Convict_16";	
				}
				if(pchar.GenQuest.Convict == "ToMayak")	
				{
					sld.dialog.currentnode = "Convict_16";	
				}
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);					
			}
		}	
	}
	else 
	{
		AddQuestRecord("Convict", "3");
		AddQuestUserData("Convict", "sSex", GetSexPhrase("","�"));
		CloseQuestHeader("Convict");
		for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
		{
			sld = CharacterFromID("Convict_" + i);
			sld.LifeDay = 0;
		}
		LAi_group_Delete("ConvictGroup");
		DeleteAttribute(pchar, "GenQuest.Convict");	
	}
}

void Convict_SetTimer(string qName)
{
	pchar.quest.Convict_ToShore.over = "yes";
	pchar.quest.Convict_MapEnter.over = "yes";
	AddQuestRecord("Convict", "3");
	AddQuestUserData("Convict", "sSex", GetSexPhrase("","�"));
	CloseQuestHeader("Convict");
	for(int i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
	{
		sld = CharacterFromID("Convict_" + i);
		sld.LifeDay = 0;
	}
	LAi_group_Delete("ConvictGroup");
	DeleteAttribute(pchar, "GenQuest.Convict");
}

void Convict_SetTimerMeet(string qName)
{
	pchar.quest.Convict_ToShore.win_condition.l1 = "Location";
	pchar.quest.Convict_ToShore.win_condition.l1.location = pchar.GenQuest.Convict.ShoreLocation;
	pchar.quest.Convict_ToShore.function = "Convict_MeetInShore";
		
	SetFunctionTimerConditionParam("Convict_SetTimer", 0, 0, 0, 14, false);


}

void Convict_MapEnter(string qName)
{
	pchar.quest.Convict_SetTimer.over = "yes";
	pchar.quest.Convict_ToShore.over = "yes";
	AddQuestRecord("Convict", "3");
	AddQuestUserData("Convict", "sSex", GetSexPhrase("","�"));
	CloseQuestHeader("Convict");
	for(int i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
	{
		sld = CharacterFromID("Convict_" + i);
		sld.LifeDay = 0;
	}
	LAi_group_Delete("ConvictGroup");
	DeleteAttribute(pchar, "GenQuest.Convict");
}

void Convict_DialogDisable()
{
	ref sld;
	for(int i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
	{
		sld = CharacterFromID("Convict_" + i);
		LAi_CharacterDisableDialog(sld);
		LAi_SetStayType(sld);
	}
}

int Convict_GetShipPrice(int iShipType)
{
	ref sld, chr;
	int price = sti(GetBaseShipParamFromType(iShipType, "price"));
	sld = CharacterFromID("Convict_0");
	if (CheckAttribute(sld, "city")) 
	{
		string sCity = sld.city; 
		if(CheckCharacterID(sld, sCity + "_shipyarder"))
		{
			chr = CharacterFromID(sCity + "_shipyarder");
			price = GetShipBuyPrice(iShipType, chr);
		}
	}	
	return price;
}

void Convict_OnMayak(string qName)
{
	ref sld;
	if(pchar.location == pchar.location.from_sea) 
	{
		pchar.quest.Convict_OnMayak.over = "yes"; 
		DeleteAttribute(&Locations[FindLocation(pchar.GenQuest.Convict.Mayak)], "DisableEncounters");
		
		for(int i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
		{
			sld = CharacterFromID("Convict_" + i);			
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto" + (i + 1));
			LAi_SetActorTypeNoGroup(sld);			
			if(i == 0)
			{
				RemovePassenger(pchar, sld);
				LAi_CharacterEnableDialog(sld);
				sld.dialog.filename = "GenQuests_Dialog.c";
				sld.dialog.currentnode = "Convict_17";				
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				LAi_ActorFollow(sld, pchar, "", -1);
			}		
		}	
	}
}

bool Convict_CheckShipType(int iShipType)
{
	int cn;
	ref sld;
	for (int i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			sld = &characters[cn];
			if (RealShips[sti(sld.Ship.Type)].basetype == iShipType)
			{
				pchar.GenQuest.Convict.CharShipId = sld.id;	
				pchar.GenQuest.Convict.ShipPrice = Convict_GetShipPrice(iShipType);
				return true;
			}
		}
	}
	return false;
}

void Convict_SetConvictToShip()
{
	ref sld, chr;
	aref arTo, arFrom;
	if(CheckAttribute(pchar,"GenQuest.Convict.CharShipId"))
	{
		sld = CharacterFromID("Convict_0");			
		chr = CharacterFromID(pchar.GenQuest.Convict.CharShipId);			
		
		DeleteAttribute(sld,"ship");
		sld.ship = "";
					 
		makearef(arTo, sld.ship);
		makearef(arFrom, chr.Ship);
		CopyAttributes(arTo, arFrom);

		SeaAI_SetOfficer2ShipAfterAbordage(sld, chr); 			
		DeleteAttribute(chr,"ship"); 
		chr.ship.type = SHIP_NOTUSED;
		
		RemoveCharacterCompanion(pchar, chr);
		AddPassenger(pchar, chr, false);
		
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
		
		DeleteAttribute(pchar,"GenQuest.Convict.CharShipId");
		
		pchar.GenQuest.Convict = "close";
		SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
	}	
}







void ShipWreck_LocationExit(string _quest)
{
	int index, i;
	ref sld;
	if(pchar.GenQuest.ShipWreck == "SailorsSaved")
	{
		for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
		{
			index = GetCharacterIndex("ShipWreck_" + i);		
			if(index != -1)
			{
				sld = CharacterFromID("ShipWreck_" + i);
				ChangeCharacterAddress(sld, "None", ""); 
			}
		}			
	}
	else
	{
		for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
		{
			index = GetCharacterIndex("ShipWreck_" + i);		
			if(index != -1)
			{
				Characters[index].LifeDay = 0;
			}
		}	
		DeleteAttribute(pchar, "GenQuest.ShipWreck");
	}	
}

string ShipWreck_GetStringQty(int Qty)
{
	string strQty;
	switch(Qty)
	{
		case 3:    	strQty = "the three"; 	break;
		case 4:    	strQty = "the four"; 	break;
		case 5: 	strQty = "the five"; 	break;
		case 6: 	strQty = "the six";		break;
		case 7: 	strQty = "the seven";	break;
		case 8: 	strQty = "the eight";	break;
		case 9: 	strQty = "the nine";	break;
		case 10:	strQty = "the ten";		break;		
	}
	return strQty;
}

void ShipWreck_SetCapToMap()
{
	int temp;
	String group = "ShipWreck_SeaGroup";
	ref character = GetCharacter(NPC_GenerateCharacter("ShipWreck_BadPirate", "", "man", "man", sti(pchar.rank) + 5, PIRATE, -1, true, "hunter"));
		
	character.name = pchar.GenQuest.ShipWreck.BadName;
	character.lastname = "";
	
	character.Ship.Type = GenerateShipExt(sti(pchar.GenQuest.ShipWreck.StartShipType), true, character);
	character.Ship.Name = pchar.GenQuest.ShipWreck.ShipTypeName;
	SetCaptanModelByEncType(character, "pirate");
    SetBaseShipData(character);
    SetCrewQuantityFull(character);
    Fantom_SetCannons(character, "pirate");
    Fantom_SetBalls(character, "pirate");
	
	character.Ship.Mode = "pirate";	

	DeleteAttribute(character, "SinkTenPercent");
	DeleteAttribute(character, "SaveItemsForDead");
	DeleteAttribute(character, "DontClearDead");
	DeleteAttribute(character, "AboardToFinalDeck");
	DeleteAttribute(character, "SinkTenPercent");
	
	character.AlwaysSandbankManeuver = true;
	character.AnalizeShips = true;  
	character.DontRansackCaptain = true; 
	
	SelAllPerksToChar(character, false);
	
	Group_FindOrCreateGroup(group);
	Group_SetTaskAttackInMap(group, PLAYER_GROUP);
	Group_LockTask(group);
	Group_AddCharacter(group, character.id);
	Group_SetGroupCommander(group, character.id);
	SetRandGeraldSail(character, PIRATE);
	
	character.fromCity = SelectAnyColony(""); 
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); 
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	character.mapEnc.type = "trade";
	character.mapEnc.worldMapShip = "quest_ship";
	character.mapEnc.Name = LowerFirst(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name)) + " '" + pchar.GenQuest.ShipWreck.ShipTypeName + "'";
	
	Map_CreateTrader(character.fromShore, character.toShore, "ShipWreck_BadPirate", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)) + 15);
	
	temp = GetCharacterFreeSpace(character, GOOD_SLAVES); 
	AddCharacterGoodsSimple(character, GOOD_SLAVES, makeint(temp / 2 + dRand(temp / 2)) - 1);
	
	pchar.quest.ShipWreck_ShipSink.win_condition.l1 = "Character_sink";
	pchar.quest.ShipWreck_ShipSink.win_condition.l1.character = "ShipWreck_BadPirate";
	pchar.quest.ShipWreck_ShipSink.function = "ShipWreck_ShipSink";
	
	Log_TestInfo("���������������: ��� ����� �� " + character.fromCity + " � ���������� �: " + character.toShore);
}

void ShipWreck_DeliveToCity(string qName)
{
	ref sld;
	if(pchar.location == pchar.location.from_sea && reload_cur_island_index > -1)
	{
		chrDisableReloadToLocation = true;
		Log_Info("have delivered convicts to ");
		for(int i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
		{
			sld = CharacterFromID("ShipWreck_" + i);
			PlaceCharacter(sld, "goto", "random_must_be_near");
			if(i == 0)
			{
				if(CheckAttribute(pchar,"GenQuest.ShipWreck.Crazy")) 
				{
					sld.dialog.currentnode = "ShipWreck_34";	
				}
				else
				{
					RemovePassenger(pchar, sld);
					if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny"))
					{
						sld.dialog.currentnode = "ShipWreck_48";	
					}
					else
					{
						if(pchar.GenQuest.ShipWreck.variant == "1")
						{
							sld.dialog.currentnode = "ShipWreck_30";	
						}	
						if(pchar.GenQuest.ShipWreck.variant == "2")
						{
							sld.dialog.currentnode = "ShipWreck_32";	
						}						
					}	
				}	
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		}
	}
	else
	{
		SetFunctionExitFromLocationCondition("ShipWreck_ExitFromTown", pchar.location, false);				
	}	
}

void ShipWreck_ExitFromTown(string _quest)
{
	pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
	pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
	pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";						
}

void ShipWreck_GoOut()
{
	ref sld;	
	float locx, locy, locz;
	
	GetCharacterPos(pchar, &locx, &locy, &locz);
	for(int i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
	{
		sld = CharacterFromID("ShipWreck_" + i);
		sld.LifeDay = 0;
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", -1.0);		
	}
	DeleteAttribute(pchar,"GenQuest.ShipWreck");
	DoQuestCheckDelay("OpenTheDoors", 1.0);
}

void ShipWreck_AfterBattle(string qName)
{
	int index;
	for(int i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
	{
		index = GetCharacterIndex("ShipWreck_" + i);		
		if(index != -1)
		{
			Characters[index].LifeDay = 0;
		}
	}	
	if(CheckAttribute(pchar,"GenQuest.ShipWreck.Crazy"))
	{
		AddQuestRecord("ShipWrecked", "8");
		CloseQuestHeader("ShipWrecked");	
	}
	DeleteAttribute(pchar, "GenQuest.ShipWreck");
}

void ShipWreck_DialogDisable()
{
	ref sld;
	for(int i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
	{
		sld = CharacterFromID("ShipWreck_" + i);
		LAi_CharacterDisableDialog(sld);
	}
}

void ShipWreck_SaveSailors(string qName)
{
	pchar.quest.ShipWreck_MeetInShore.over = "yes";
	ChangeCharacterComplexReputation(pchar,"nobility", -5);
	AddQuestRecord("ShipWrecked", "12");
	CloseQuestHeader("ShipWrecked");
	DeleteAttribute(pchar, "GenQuest.ShipWreck");	
}

void ShipWreck_MeetInShore(string qName)
{
	ref sld;
	string sLocGroup;
	
	for(int i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
	{
		sld = CharacterFromID("ShipWreck_" + i);
		if(GetFreeCrewQuantity(pchar) < sti(pchar.GenQuest.ShipWreck.Qty)) 
		{
			ChangeCharacterAddress(sld, "None", ""); 
		}
		else 
		{
			pchar.quest.ShipWreck_MeetInShore.over = "yes"; 
			if(LAi_GetLocatorNum("encdetector") > 0) 	sLocGroup = "encdetector";
			else										sLocGroup = "goto";
			PlaceCharacter(sld, sLocGroup, pchar.GenQuest.ShipWreck.Shore);
			if(i == 0)
			{
				sld.dialog.currentnode = "ShipWreck_44";
				LAi_ActorDialog(sld, pchar, "", 5.0, 0.0);
			}
			else
			{
				LAi_ActorFollow(sld, pchar, "", 5.0);
			}
		}
	}	
}

void ShipWreck_afterCabinFight(string qName)
{
	ref sld;
	float locx,locy,locz;

	sld = CharacterFromID("ShipWreck_0");
	sld.dialog.currentnode = "ShipWreck_53";
	LAi_SetStayType(sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
	LAi_SetActorType(pchar);
	LAi_SetActorType(sld);
	SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
}

void ShipWreck_SetShipNew()
{
	ref sld, chr;
	aref arTo, arFrom;

	sld = CharacterFromID("ShipWreck_0");
	chr = CharacterFromID("ShipWreck_BadPirate");			
		
	DeleteAttribute(sld, "ship");
	sld.ship = "";
					 
	makearef(arTo, sld.ship);
	makearef(arFrom, chr.ship);
	CopyAttributes(arTo, arFrom);

	SeaAI_SetOfficer2ShipAfterAbordage(sld, chr); 			

	
	
	
	chr.LifeDay = 0;
	
	RemovePassenger(pchar, sld);
	sld.AlwaysFriend = true;
	sld.Abordage.Enable = false; 
	SetCrewQuantity(sld, 15 + rand(10));
	
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
	pchar.GenQuest.ShipWreck = "close";
	pchar.quest.ShipWreck_MapEnter.win_condition.l1 = "MapEnter";
	pchar.quest.ShipWreck_MapEnter.function = "ShipWreck_LocationExit"; 			

	AddQuestRecord("ShipWrecked", "18");
	AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","�"));
	AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")));
	AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
	AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
	CloseQuestHeader("ShipWrecked");
}

void ShipWreck_ShipSink(string qName)
{
	ref sld;
	for(int i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
	{
		sld = CharacterFromID("ShipWreck_" + i);
		if(i == 0) 
		{
			RemovePassenger(pchar, sld);
		}
		sld.LifeDay = 0;
	}
	AddQuestRecord("ShipWrecked", "19");
	AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")));
	AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
	AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
	CloseQuestHeader("ShipWrecked");
	DeleteAttribute(pchar, "GenQuest.ShipWreck");	
}






void Hold_GenQuest_Init(ref chref)
{
	ref rColony;
	string sColony;
	
	if(!CheckAttribute(chref,"EncType")) chref.EncType = "trade";
	
	switch(chref.EncType)
	{
		case "trade":
			chref.Hold_GenQuest.variant = rand(2);  
		break;
		case "war":
			chref.Hold_GenQuest.variant = 0;
		break;
		case "pirate":
			chref.Hold_GenQuest.variant = rand(1); 
		break;
	}

	switch(sti(chref.Hold_GenQuest.variant))	
	{
		case 0: 
			chref.Hold_GenQuest.Goods = Hold_GenQuest_GetVictimShipGoods();
			chref.Hold_GenQuest.Nation = FindEnemyNation2NationWithoutPirates(GetBaseHeroNation()); 
			if(sti(chref.Hold_GenQuest.Nation) < 0) 
			{
				chref.Hold_GenQuest.Nation = rand(3);
			}	
			chref.Hold_GenQuest.Name = GenerateRandomName_Generator(sti(chref.Hold_GenQuest.Nation), "man");
			
			sColony = Sea_FindNearColony();
			if (sColony != "none") 
			{
				chref.Hold_GenQuest.ToCity = FindAlliedColonyForNationExceptColony(sColony);
			}
			else
			{
				chref.Hold_GenQuest.ToCity = GetQuestNationsCity(sti(chref.Hold_GenQuest.Nation));
			}	
			chref.Hold_GenQuest.FromCity = FindAlliedColonyForNationExceptColony(chref.Hold_GenQuest.ToCity);
			chref.Hold_GenQuest.ShipName = GenerateRandomNameToShip(sti(chref.Hold_GenQuest.Nation));
			if(rand(1) == 0) 	chref.Hold_GenQuest.City = chref.Hold_GenQuest.ToCity;
			else 				chref.Hold_GenQuest.City = chref.Hold_GenQuest.FromCity;
		break;

		case 1: 
			chref.Hold_GenQuest.Nation = rand(3);
			chref.Hold_GenQuest.City = GetQuestNationsCity(sti(chref.Hold_GenQuest.Nation));
			chref.Hold_GenQuest.Name = GenerateRandomName_Generator(sti(chref.Hold_GenQuest.Nation), "man");
			chref.Hold_GenQuest.PirateName = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);
		break;
		
		case 2: 
			chref.Hold_GenQuest.City = GetQuestNationsCity(rand(3));							
			rColony = GetColonyByIndex(FindColony(chref.Hold_GenQuest.City));
			chref.Hold_GenQuest.Nation = sti(rColony.nation);
			chref.Hold_GenQuest.Name = GenerateRandomName_Generator(sti(chref.Hold_GenQuest.Nation), "man");
		break;			
	}
}

int Hold_GenQuest_GetVictimShipGoods()
{
	int iGoodIdx;
	switch (rand(10))
    {
        case 0 :
            iGoodIdx = GOOD_TOBACCO;
        break;
        case 1 :
            iGoodIdx = GOOD_COFFEE;
        break;
        case 2 :
            iGoodIdx = GOOD_MAHOGANY;
        break;						
        case 3 :
            iGoodIdx = GOOD_FOOD;
        break;
        case 4 :
            iGoodIdx = GOOD_EBONY;
        break;				
        case 5 :
            iGoodIdx = GOOD_RUM;
        break;
        case 6 :
            iGoodIdx = GOOD_WEAPON;
        break;
        case 7 :
            iGoodIdx = GOOD_WINE;
        break;
        case 8 :
            iGoodIdx = GOOD_CHOCOLATE;
        break;				
        case 9 :
            iGoodIdx = GOOD_CINNAMON;
        break;
        case 10 :
            iGoodIdx = GOOD_LEATHER;
        break;		
    }
	return iGoodIdx;
}

void Hold_GenQuest_SetMerchant_pre(string qName)
{
	SetFunctionLocationCondition("Hold_GenQuest_SetMerchant", pchar.GenQuest.Hold_GenQuest.Island, false);
}

void Hold_GenQuest_SetMerchant(string qName)
{
	ref chref, sld;
	pchar.quest.Hold_GenQuest_MerchantOver.over = "yes";
	
	int iChar = NPC_GenerateCharacter("Hold_QuestMerchant", "off_spa_2", "man", "man", 5, sti(pchar.GenQuest.Hold_GenQuest.Nation), 3, true, "citizen");
	makeref(chref, Characters[iChar]);
	int iRank = SetShipTypeMerchant(chref); 
	chref.Ship.Name = pchar.GenQuest.Hold_GenQuest.ShipName;
	SetFantomParamHunter(chref); 
	
	SetCaptanModelByEncType(chref, "trade");	
	int iSpace = GetCharacterFreeSpace(chref, sti(pchar.GenQuest.Hold_GenQuest.Goods));
    
    float del = makefloat(7 - iRank + rand(1))/10; 
    if (del > 1.0 ) del = 1;
    Log_TestInfo("goods load = "+iSpace+"/"+makeint(iSpace*del));
    iSpace = makeint(iSpace * del); 
    Fantom_SetCharacterGoods(chref, sti(pchar.GenQuest.Hold_GenQuest.Goods), iSpace, 1);
	
	string sGroup = "Sea_" + chref.id
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
    Group_SetType(sGroup, "trade");
	
	int IslandID = FindIsland(GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City));
	ref pLoc = &Islands[IslandID];
	float x, y, z;
	FindIslandLocatorXYZ(IslandID, "reload1", &x, &y, &z); 
	string sLocator = GetSeaQuestShipFarLocator(pLoc, "Quest_ships", x, y, z);
	
	chref.DontRansackCaptain = true;
	
	Group_SetAddress(sGroup, GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City),"quest_ships", sLocator);        
    Group_AddCharacter(sGroup, chref.id);
    Group_SetGroupCommander(sGroup, chref.id);
	Group_SetTaskRunaway(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	
	pchar.quest.Hold_GenQuest_SinkMerchant.win_condition.l1 = "Character_sink";
    pchar.quest.Hold_GenQuest_SinkMerchant.win_condition.l1.character = "Hold_QuestMerchant";
    pchar.quest.Hold_GenQuest_SinkMerchant.function = "Hold_GenQuest_SinkMerchant";
    
	pchar.quest.Hold_GenQuest_CaptureMerchant.win_condition.l1 = "Character_Capture";
    pchar.quest.Hold_GenQuest_CaptureMerchant.win_condition.l1.character = "Hold_QuestMerchant";
    pchar.quest.Hold_GenQuest_CaptureMerchant.function = "Hold_GenQuest_CaptureMerchant";  

	SetFunctionTimerConditionParam("Hold_GenQuest_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
	
	int gcount = rand(3)-1;
    if (gcount < 0 || makeint(pchar.rank) < 5) gcount = 0;
    
    for (int i = 0; i < gcount; i++) 
    {
        iChar = NPC_GenerateCharacter("Hold_QuestMerchantGuard_"+i, "off_spa_2", "man", "man", 5, sti(pchar.GenQuest.Hold_GenQuest.Nation), 3, true, "hunter"));
        makeref(sld, Characters[iChar]);
        SetShipHunter(sld);
        SetFantomParamHunter(sld); 
        SetCaptanModelByEncType(sld, "war");
        sld.Ship.Mode = "war";
		sld.DontRansackCaptain = true;
        Group_AddCharacter(sGroup, sld.id);
    }
    chref.gcount = gcount;    	
}

void Hold_GenQuest_MerchantOver(string qName) 
{
	pchar.quest.Hold_GenQuest_SetMerchant.over = "yes";
	AddQuestRecord("HoldQuest", "3");
	AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
	AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Gen"))); 
	CloseQuestHeader("HoldQuest");
	DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");
}

void Hold_GenQuest_SinkMerchant(string qName)
{
	pchar.quest.Hold_GenQuest_CaptureMerchant.over = "yes";
	pchar.quest.Hold_GenQuest_TimeIsOver.over = "yes";
	AddQuestRecord("HoldQuest", "5");
	AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
	AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Gen"))); 
	CloseQuestHeader("HoldQuest");
	DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");	
}

void Hold_GenQuest_CaptureMerchant(string qName)
{
	pchar.quest.Hold_GenQuest_SinkMerchant.over = "yes";
	pchar.quest.Hold_GenQuest_TimeIsOver.over = "yes";
	AddQuestRecord("HoldQuest", "4");
	AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
	AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Gen"))); 
	CloseQuestHeader("HoldQuest");
	DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");		
}

void Hold_GenQuest_TimeIsOver(string qName)
{
	pchar.quest.Hold_GenQuest_SinkMerchant.over = "yes";
	pchar.quest.Hold_GenQuest_CaptureMerchant.over = "yes";
	ref sld = characterFromId("Hold_QuestMerchant");
	Group_DeleteGroup("Sea_" + sld.id); 
	AddQuestRecord("HoldQuest", "2");
	AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("","�"));
	AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
	CloseQuestHeader("HoldQuest");
	DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");
}

void Hold_GenQuest_GenerateChar()
{
	int Rank = sti(pchar.rank) + rand(10);
	ref sld = GetCharacter(NPC_GenerateCharacter("Hold_GenQuestChar", "trader_"+(rand(5)+1), "man", "man", 10, sti(pchar.GenQuest.Hold_GenQuest.Nation), 3, true, "quest"));
	FantomMakeCoolFighter(sld, Rank, 100, 90, "blade_09", "pistol3", "grapeshot", 50);
	sld.name = pchar.GenQuest.Hold_GenQuest.Name;
	sld.lastname = "";
	sld.dialog.FileName = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "Hold_GenQuest1";
	sld.greeting = "cit_quest";
	sld.CityType = "citizen";
	sld.City = pchar.GenQuest.Hold_GenQuest.City;
	LAi_SetImmortal(sld, true);	
	string sTemp = pchar.GenQuest.Hold_GenQuest.City + "_" + pchar.GenQuest.Hold_GenQuest.found;
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, sTemp, "goto", "goto2");
}

void Hold_GenQuest_AfterBattle(string qName)
{
	chrDisableReloadToLocation = false; 
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);  
}

void Hold_GenQuest_FindCharTimeIsOver(string qName)
{
	ref sld = characterFromId("Hold_QuestChar");
	sld.LifeDay = 0;
	AddQuestRecord("HoldQuest", "9");
	AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("","�"));
	AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
	pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
}

void Hold_GenQuest_PrisonerEscaped()
{
	pchar.quest.Hold_GenQuest_ExitFromTown.win_condition.l1			= "EnterToSea";         
	pchar.quest.Hold_GenQuest_ExitFromTown.function    				= "Hold_GenQuest_ExitFromTownFight";									
	pchar.GenQuest.Hold_GenQuest.canSpeakSailor = true;
	pchar.TownEscape = true; 
}

void Hold_GenQuest_ExitFromTownFight(string qName)
{
	Log_QuestInfo("��������� ����� �� ��������, ������� ������� � ��������");
	bQuestDisableMapEnter = true;
	QuestCloseSeaExit();
    DoQuestFunctionDelay("Hold_GenQuest_MeetWithSailor", 1);
}

void Hold_GenQuest_MeetWithSailor(string qName)
{
	Sea_DeckBoatStartNow(pchar); 
}

void Hold_GenQuest_GetMapTimeIsOver(string qName)
{
	pchar.quest.Hold_GenQuest_SpeakMapCharTavern.over = "yes";
	ref sld = characterFromId("Hold_QuestChar");
	sld.LifeDay = 0;
	AddQuestRecord("HoldQuest", "14");
	AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("","�"));
	AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
	CloseQuestHeader("HoldQuest");
	DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");				
}

void Hold_GenQuest_GenerateMapChar()
{
	ref sld = GetCharacter(NPC_GenerateCharacter("Hold_GenQuestChar", "citiz_"+(rand(9)+21), "man", "man", 5, sti(pchar.GenQuest.Hold_GenQuest.Nation), 3, true, "hunter"));
	sld.name = pchar.GenQuest.Hold_GenQuest.Name;
	sld.lastname = "";
	LAi_SetImmortal(sld, true);
	pchar.quest.Hold_GenQuest_SpeakMapCharTavern.win_condition.l1 = "location";
	pchar.quest.Hold_GenQuest_SpeakMapCharTavern.win_condition.l1.location = pchar.GenQuest.Hold_GenQuest.City + "_tavern";
	pchar.quest.Hold_GenQuest_SpeakMapCharTavern.function = "Hold_GenQuest_SpeakMapChar";
}

void Hold_GenQuest_SpeakMapChar(string qName)
{
	chrDisableReloadToLocation = true;
	ref sld = characterFromId("Hold_GenQuestChar");	
	sld.dialog.filename = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "Hold_GenQuest80";	
	sld.greeting = "cit_quest";
	sld.CityType = "citizen";
	sld.City = pchar.GenQuest.Hold_GenQuest.City;
 	ChangeCharacterAddressGroup(sld, pchar.GenQuest.Hold_GenQuest.city + "_tavern", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
}

void Hold_GenQuest_GenerateTreasureMap(ref item)
{
    item.MapIslId   = GetIslandForTreasure();
    item.MapLocId   = GetLocationForTreasure(item.MapIslId);
    item.MapBoxId   = GetBoxForTreasure(item.MapIslId, item.MapLocId);
	item.MapOwnId   = GetName(NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_NOM);
	
	DeleteAttribute(item, "BoxTreasure");

	pchar.GenQuest.Hold_GenQuest.Treasure.Island = item.MapIslId;
	pchar.GenQuest.Hold_GenQuest.Treasure.Location = item.MapLocId;
	pchar.GenQuest.Hold_GenQuest.Treasure.Locator = item.MapBoxId;
	
	SetFunctionLocationCondition("Hold_GenQuest_SetTreasureBoxFromMap", item.MapLocId, false);	
}

void Hold_GenQuest_SetTreasureBoxFromMap(string qName)
{
    ref    loc;
    string box, itmName;
    aref   item, arToBox, arFromBox;
	if (GetCharacterItem(pchar, "mapQuest") > 0 )
    {
        Log_Info("The treasures must be somewhere nearby!");
        PlaySound("interface\notebook.wav");
		Statistic_AddValue(Pchar, "Treasure", 1);
		Achievment_SetStat(Pchar, 8, 1);

		Items_FindItem("mapQuest", &item);
		
		if(sti(pchar.GenQuest.Hold_GenQuest.Treasure) == 0)
		{
			itmName = GenQuest_GeneratePrize();
			item.BoxTreasure.(itmName) = 1;
			
			if(rand(1) == 0)
			{
				itmName = GenQuest_GenerateGoodBlade();
				item.BoxTreasure.(itmName) = 1;
			}	
			
			itmName = "icollection"; 
			item.BoxTreasure.(itmName) = 1 + makeint(sti(pchar.rank)/6); 
			
			itmName = "jewelry2";
			item.BoxTreasure.(itmName) = rand(5) + 5;
			
			itmName = "jewelry3";
			item.BoxTreasure.(itmName) = rand(4) + 10;
			
			GenerateAdmiralMapsTreasure(item, 12); 
		}
		else
		{
			itmName = GetGeneratedItem("slave_02");
			item.BoxTreasure.(itmName) = rand(8) + 4;
		
			itmName = "mineral5"; 
			item.BoxTreasure.(itmName) = rand(5) + 2;
		
			itmName = "mineral8"; 
			item.BoxTreasure.(itmName) = rand(7) + 4;		
			
			if (rand(2) == 1)
	        {
            	item.BoxTreasure.slave_01 = 5 + rand(100);
	        }
	        else
	        {
				itmName = GetGeneratedItem("blade_11");
                item.BoxTreasure.(itmName) = 5 + rand(100);
	        }
			if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral4 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral6 = 5 + rand(200);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral7 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral9 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral10 = 25 + rand(300);
	        }	        	        	        
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.cirass1 = 1;
	        }
			GenerateAdmiralMapsTreasure(item, 50); 
		}
        box = item.MapBoxId;

        loc = &locations[FindLocation(item.MapLocId)];
        loc.(box).items = "";

        makearef(arToBox, loc.(box).items);
        makearef(arFromBox, item.BoxTreasure);
        CopyAttributes(arToBox, arFromBox);

        loc.(box) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
        loc.(box).Treasure = true; 
		loc.(box).Hold_GenQuest_Treasure = true;

        DeleteAttribute(item, "MapIslId");
        TakeNItems(pchar, "mapQuest", -1);	

		pchar.GenQuest.Hold_GenQuest = "in_TreasureLoc";	
	}
}







void GenQuest_EnableMonstersGen(string qName)
{
	if(CheckAttribute(pchar, "GenQuest.monstersTimer"))
	{
		DeleteAttribute(pchar, "GenQuest.monstersTimer");
	}	
}

bool GenQuest_CheckMonstersGen()
{
	if(CheckAttribute(pchar, "GenQuest.monstersTimer")) return false;
	else return true;
}









void JusticeOnSale_LocationExit(string _quest)
{
	
	if(!CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait"))
	{
		DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
	}
	else
	{
		PChar.Quest.JusticeOnSale_MapEnter.win_condition.l1 = "MapEnter";
		PChar.Quest.JusticeOnSale_MapEnter.function = "JusticeOnSale_MapEnter";
	}
}


void JusticeOnSale_MapEnter(string _quest)
{
	ref sld;
	
	DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)], "DisableEncounters");
	
	DeleteQuestCondition("JusticeOnSale_ShoreEnterWithSmuggler");
	DeleteQuestCondition("JusticeOnSale_ShoreEnterFromMayor");
	DeleteQuestCondition("JusticeOnSale_ShoreEnterFromMayor");
	DeleteQuestCondition("JusticeOnSale_PirateShip_Sink");
	
	if(CheckPassengerInCharacter(PChar, "JusticeOnSale_Smuggler"))
	{
		sld = CharacterFromID("JusticeOnSale_Smuggler");
		RemovePassenger(PChar, sld);
		sld.LifeDay = 0;
		
		AddQuestRecord("JusticeOnSale", "2");
	}
	
	CloseQuestHeader("JusticeOnSale");
	DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
}


void JusticeOnSale_ShoreEnterWithSmuggler(string _quest)
{
	int curModel, i = 0;
	ref location = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
	ref character;
	string model[11];
	
	model[0] = "citiz_41";
	model[1] = "citiz_42";
	model[2] = "citiz_43";
	model[3] = "citiz_44";
	model[4] = "citiz_45";
	model[5] = "citiz_46";
	model[6] = "citiz_47";
	model[7] = "citiz_48";
	model[8] = "citiz_49";
	model[9] = "citiz_50";
	model[10] = PChar.GenQuest.JusticeOnSale.SmugglerModel;
	
	DeleteQuestCondition("JusticeOnSale_MapEnter");
	
	character = CharacterFromID("JusticeOnSale_Smuggler");
	RemovePassenger(PChar, character);
	character.LifeDay = 0;
	
	while(i < sti(PChar.GenQuest.JusticeOnSale.EncQty))
	{
		if(i == 0)
		{
			curModel = 10;
		}
		else
		{
			curModel = rand(9);
		}
		
		if(model[curModel] != "")
		{
			character = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_ShorePirate_" + i, model[curModel], "man", "man", sti(PChar.rank), PIRATE, 0, true, "marginal"));
			SetFantomParamFromRank(character, sti(PChar.rank), true);
			ChangeCharacterAddressGroup(character, location.id, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			character.dialog.filename = "GenQuests_Dialog.c";
			character.dialog.currentnode = "JusticeOnSale_9";
			character.greeting = "Enc_Raiders";
			LAi_SetActorType(character);
			
			if(i == 0)
			{
				character.name = PChar.GenQuest.JusticeOnSale.SmugglerName;
				character.lastName = "";
				LAi_ActorDialog(character, PChar, "", 3, 3);
			}
			else
			{
				LAi_ActorFollow(character, CharacterFromID("JusticeOnSale_ShorePirate_0"), "", -1);
			}
			
			model[curModel] = "";
			i++;
		}
	}
	
	chrDisableReloadToLocation = true;
	
	PChar.Quest.JusticeOnSale_LocationExit.win_condition.l1 = "ExitFromLocation";
	PChar.Quest.JusticeOnSale_LocationExit.win_condition.l1.location = PChar.location;
	PChar.Quest.JusticeOnSale_LocationExit.function = "JusticeOnSale_ClearShore";
}


void JusticeOnSale_ShoreEnterFromMayor(string _quest)
{
	int i = 0;
	string attr;
	ref character;
	ref location = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
	
	while(i < sti(PChar.GenQuest.JusticeOnSale.EncQty))
	{
		character = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_ShorePirate_" + i, "", "man", "man", sti(PChar.rank), PIRATE, 0, true, "marginal"));
		SetModelPirate(character);
		SetFantomParamFromRank(character, sti(PChar.rank) + 5, true);
		ChangeCharacterAddressGroup(character, location.id, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
		
		LAi_SetWarriorTypeNoGroup(character);
		LAi_Group_MoveCharacter(character, "JusticeOnSale_ShoreGroup");
		
		attr = "l" + (i + 1);
		PChar.Quest.JusticeOnSale_KillSmugglers.win_condition.(attr) = "NPC_Death";
		PChar.Quest.JusticeOnSale_KillSmugglers.win_condition.(attr).character = "JusticeOnSale_ShorePirate_" + i;
		
		i++;
	}
	
	LAi_Group_SetRelation("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_Group_FightGroups("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, true);
	
	PChar.Quest.JusticeOnSale_KillSmugglers.function = "JusticeOnSale_KillSmugglers";
	
	PChar.Quest.JusticeOnSale_LocExitAfterMayor.win_condition.l1 = "ExitFromLocation";
	PChar.Quest.JusticeOnSale_LocExitAfterMayor.win_condition.l1.location = PChar.location;
	PChar.Quest.JusticeOnSale_LocExitAfterMayor.function = "JusticeOnSale_LocExitAfterMayor";
}

void JusticeOnSale_ClearShore(string _quest)
{
	DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)], "DisableEncounters");
	DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
}


void JusticeOnSale_LocExitAfterMayor(string _quest)
{
	DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)], "DisableEncounters");
	DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
	
	DeleteQuestCondition("JusticeOnSale_KillSmugglers");
	
	Group_DeleteGroup("JusticeOnSaleGroup"); 
	
	AddQuestRecord("JusticeOnSale", "6");
	CloseQuestHeader("JusticeOnSale");
	
	Log_TestInfo("����� �� �������, � ���.");
}


void JusticeOnSale_PirateShip_Sink(string _quest)
{
	PChar.GenQuest.JusticeOnSale.ShipSink = true;
	
	DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)], "DisableEncounters");
	
	if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.KillSmugglers"))
	{
		
		AddQuestRecord("JusticeOnSale", "7");
		CloseQuestHeader("JusticeOnSale");
	}
	else
	{
		
		DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
		
		DeleteQuestCondition("JusticeOnSale_ShoreEnterFromMayor");
		
		Group_DeleteGroup("JusticeOnSaleGroup"); 
		
		AddQuestRecord("JusticeOnSale", "6");
		CloseQuestHeader("JusticeOnSale");
	}
	
	DeleteQuestCondition("JusticeOnSale_MapEnter");
}


void JusticeOnSale_KillSmugglers(string _quest)
{
	ref character;
	
	PChar.GenQuest.JusticeOnSale.KillSmugglers = true;
	
	if(GetCharacterShipLocation(PChar) == PChar.GenQuest.JusticeOnSale.ShoreId && !CheckAttribute(PChar, "GenQuest.JusticeOnSale.ShipSink"))
	{
		
		DeleteQuestCondition("JusticeOnSale_LocExitAfterMayor");
		
		character = CharacterFromID("JusticeOnSale_ShipPirate");
		DeleteAttribute(character, "AlwaysFriend");
		SetCharacterRelationBoth(sti(character.index), GetMainCharacterIndex(), RELATION_ENEMY);
		
		Log_TestInfo("����� ���� �� ����������� ��������.");
	}
	else
	{
		
		DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)], "DisableEncounters");
		DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
		
		Group_DeleteGroup("JusticeOnSaleGroup"); 
		
		DeleteQuestCondition("JusticeOnSale_PirateShip_Sink");
		
		AddQuestRecord("JusticeOnSale", "6");
		CloseQuestHeader("JusticeOnSale");
	}
	
	Log_TestInfo("�������� ���� ���������, ������� � ����!");
}





