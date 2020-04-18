
void ActivateTimeEvents()
{

}


void SalaryNextDayUpdate()
{
	if (sti(NullCharacter.SalayPayMonth) != GetDataMonth() && !bDisableMapEnter) 
	{
		
		int nPaymentQ = 0;
		int i, cn;
		ref chref;
		
		for (i=0; i<COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(pchar, i);
			if (cn >= 0)
			{
				chref = GetCharacter(cn);
				if (GetRemovable(chref)) 
				{
					nPaymentQ += GetSalaryForShip(chref);
				}
			}
		}
		
		
		NullCharacter.SalayPayMonth = GetDataMonth(); 
		if (nPaymentQ > 0)
		{
			if( CheckAttribute(pchar,"CrewPayment") )
			{
				nPaymentQ += makeint(pchar.CrewPayment); 
			}
			if( CheckAttribute(pchar,"Partition.MonthPart") )
			{
				nPaymentQ += makeint(pchar.Partition.MonthPart); 
				DeleteAttribute(pchar,"Partition.MonthPart")
			}
			
			pchar.CrewPayment = nPaymentQ;
			LaunchMoneyGraphCollect();
			
			if (!dialogRun && !bQuestCheckProcessFreeze && !bAbordageStarted) 
			{
				LaunchSalaryScreen("");
			}
			else
			{
				Pchar.quest.LaunchSalaryScreen.win_condition.l1 = "MapEnter";
				PChar.quest.LaunchSalaryScreen.win_condition    = "LaunchSalaryScreen";
				PChar.quest.LaunchSalaryScreen.function         = "LaunchSalaryScreen";
			}
		}
	}
}

#event_handler("EvSituationsUpdate","WorldSituationsUpdate");
void WorldSituationsUpdate()
{
	int iStep = GetEventData();
	float dayRandom;

	
	 
	

	switch(iStep)
	{
		case 0:
            DeleteAttribute(pchar, "SkipEshipIndex");
			DailyEatCrewUpdate(); 
			Log_QuestInfo("WorldSituationsUpdate DailyEatCrewUpdate");
			
			dayRandom = Random();
			PChar.DayRandom = dayRandom;
			Log_TestInfo("dayRandom == " + dayRandom);
			CheckCharactersUpdateItems();
			if (CheckAttribute(pchar, "questTemp.LSC")) 
			{ 
				if (GetDataDay() == 7 || GetDataDay() == 14 || GetDataDay() == 21 || GetDataDay() == 28)
				{
					sNrvParol = UpdateLSCClanParol();
					sRvdParol = UpdateLSCClanParol();
					if (CheckAttribute(pchar, "questTemp.LSC.NParol_bye")) DeleteAttribute(pchar, "questTemp.LSC.NParol_bye");
					if (CheckAttribute(pchar, "questTemp.LSC.RParol_bye")) DeleteAttribute(pchar, "questTemp.LSC.RParol_bye");
				}
				if (CheckAttribute(pchar, "questTemp.LSC.parol_nrv")) DeleteAttribute(pchar, "questTemp.LSC.parol_nrv");
				if (CheckAttribute(pchar, "questTemp.LSC.parol_rvd")) DeleteAttribute(pchar, "questTemp.LSC.parol_rvd");
			} 
			if (CheckAttribute(pchar, "questTemp.Saga.JessOnShip")) 
			{ 
				AddCrewMorale(pchar, -5);
				ChangeOfficersLoyality("bad_all", 1);
				AddCharacterHealth(pchar, -2);
			}
			
			Tortuga_DeleteShipGuard();
		break;
		
		case 1:
            SalaryNextDayUpdate();  
			Log_QuestInfo("WorldSituationsUpdate SalaryNextDayUpdate");
			if (rand(2) == 0) Norman_ChangeFesivalFace(); 
			if (GetDataDay() == 5 && CheckAttribute(pchar, "questTemp.OilTrade")) DoQuestFunctionDelay("Oil_SetSergioToMayak", 1.0); 
			if (GetDataDay() == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.IslandLock")) 
			{
				for (int i=0; i<MAX_ISLANDS; i++)
				{				
					if (!CheckAttribute(&Islands[i], "hidden")) Island_SetReloadEnableGlobal(Islands[i].id, true);
				}
			}
			
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "Start") DoQuestFunctionDelay("Caleuche_StartGo", 1.0);
			
			if (!CheckAttribute(pchar, "questTemp.FMQ.Success") && sti(pchar.rank) > 3) DoQuestFunctionDelay("FMQ_SetConditions", 1.0);
		break;
		
		case 2:
			
			Tortuga_SetShipGuard();
			ProcessHullDecrease();	
			ProcessDayRepair();
			
			if (CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince"))
			{
				if (GetDataDay() == 5 || GetDataDay() == 10 || GetDataDay() == 15 || GetDataDay() == 20 || GetDataDay() == 25 || GetDataDay() == 30)
				{
					ChangeCharacterComplexReputation(pchar, "nobility", -1);
				}
				if (GetDataDay() == 10 || GetDataDay() == 20 || GetDataDay() == 30)
				{
					OfficersReaction("bad");
				}
			}
			if (!CheckAttribute(pchar, "questTemp.Mtraxx.BugsFixer")) Mtraxx_BugsFixer(); 
		break;
		
		case 3:
			
			Group_FreeAllDead();
			
			if (CheckAttribute(pchar, "questTemp.Patria.Governor") && GetDataDay() == 15)
			{
				AddMoneyToCharacter(pchar, 100000);
				log_info("You have received your share of profit from Poincy");
			}
		break;
		
		case 4:
			QuestActions(); 
		break;
		
		case 5:
			
			wdmEmptyAllOldEncounter();
		break;
		
		case 6:
			UpdateCrewExp();  
		break;
		
		case 7:
			UpdateCrewInColonies(); 
		break;
		
		case 8:
			if(IsEntity(worldMap))
			{
				EmptyAllFantomCharacter(); 
				wdmEmptyAllDeadQuestEncounter();
			}
		break;
		
		case 9:
				UpdateReputation();
				GenerateRumour() 
		break;
		
		case 10:
			
		break;
	}

	iStep++;
	InterfaceStates.WorldSituationUpdateStep = iStep;

	if(iStep <= 10)
	{
		PostEvent("EvSituationsUpdate", 1000, "l", iStep);
	}
}



void Tut_StartGame(string sQuest)
{
    InterfaceStates.Buttons.Save.enable = false;
	StartQuestMovie(true, true, true);
    SetCharacterTask_None(GetMainCharacter());
    LAi_LockFightMode(Pchar, true);
	PChar.GenQuest.CallFunctionParam = "Tut_Continue";
	DoQuestCheckDelay("CallFunctionParam", 5.0);
	LAi_LocationFightDisable(loadedLocation, true);
	InterfaceStates.Buttons.Save.enable = false;
	DoQuestFunctionDelay("Tut_locCamera_1", 0.1);
}

void Tut_locCamera_1(string _tmp)
{
    locCameraToPos(-5, 2.5, 5.6, false);
    DoQuestFunctionDelay("Tut_locCamera_2", 10.0);
}

void Tut_locCamera_2(string _tmp)
{
    locCameraFollow();
}
void Tut_Continue()
{
    ref sld;
    LAi_LocationFightDisable(loadedLocation, false);
    LAi_SetFightMode(Pchar, false);
    LAi_LockFightMode(pchar, true);
    
	sld = GetCharacter(NPC_GenerateCharacter("Sailor_1", "citiz_31", "man", "man", 1, PIRATE, 0, false, "soldier"));
    sld.name 	= "������";
    sld.lastname 	= "����";
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\StartGame_dialog.c";
    sld.greeting = "Teacher_pirat";

    SetSPECIAL(sld, 9,8,10,3,6,10,4);
    InitStartParam(sld);
    SetEnergyToCharacter(sld);

    LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_1");
    GiveItem2Character(sld, "blade_11");
	EquipCharacterByItem(sld, "blade_11");
	
    ChangeCharacterAddressGroup(sld, "Ship_deck_Low", "reload", "reload1");
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);

	
	sld = GetCharacter(NPC_GenerateCharacter("Sailor_2", "citiz_36", "man", "man", 1, PIRATE, 0, false, "soldier"));
    sld.name 	= "����";
    sld.lastname 	= "�������";

    SetSPECIAL(sld, 8,10,9,3,6,10,4);
    InitStartParam(sld);
    SetEnergyToCharacter(sld);

    LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_2");
    GiveItem2Character(sld, "blade_12");
	EquipCharacterByItem(sld, "blade_12");
	GiveItem2Character(sld, "pistol1");
	EquipCharacterByItem(sld, "pistol1");
		
	AddItems(sld, "bullet", 30);
	AddItems(sld, "gunpowder", 30);
	LAi_SetCharacterUseBullet(sld, "bullet");	
	
    sld.location = "Ship_deck_Low";  
	
	
}

void Tut_RestoreState()
{
	ref sld;
	
	pchar.Health.Damg = 0.0; 
	pchar.Health.weekDamg = 0.0;

	LAi_SetCurHPMax(pchar);
	LAi_SetCheckMinHP(pchar, 1, true, "Tut_StartGame_CheckMinHP_Hero");
	LAi_SetImmortal(pchar, false);
	
	sld = characterFromID("Sailor_1");
	LAi_SetCurHPMax(sld);
	LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_1");
	LAi_SetImmortal(sld, false);
	
	sld = characterFromID("Sailor_2");
	LAi_SetCurHPMax(sld);
	LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_2");
	LAi_SetImmortal(sld, false);
	
	DeleteAttribute(pchar, "HeroParam.Teach_beat");
}

void Tut_TeachBattle()
{
	ref sld;
	
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(Pchar, true);
	sld = characterFromID("Sailor_1");
	LAi_SetWarriorType(sld);
    LAi_group_MoveCharacter(sld, "TmpEnemy");
	
	if (sti(pchar.HeroParam.Teach_battle) == 2)
	{
        sld = characterFromID("Sailor_2");
		if (!IsEntity(sld))
        {
        	ChangeCharacterAddressGroup(sld, "Ship_deck_Low", "reload", "reload1");
        }
		LAi_SetWarriorType(sld);
	    LAi_group_MoveCharacter(sld, "TmpEnemy");
	}
	LAi_group_SetHearRadius("TmpEnemy", 100.0);
    LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
    LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
}

void Tut_StartDialog()
{
	ref sld = characterFromID("Sailor_1");
	
	if (CheckAttribute(pchar, "HeroParam.Teach_beat"))
	{ 
		if (sti(pchar.HeroParam.Teach_beat) == 3)
		{
		    sld.Dialog.CurrentNode = "Teach_battle_win_2";
		}
		else
		{
			if (sti(pchar.HeroParam.Teach_battle) == 1)
			{
				sld.Dialog.CurrentNode = "Teach_battle_win";
			}
			else
			{
			    sld.Dialog.CurrentNode = "Teach_battle_win_3";
			}
		}
	}
	else
	{
		sld.Dialog.CurrentNode = "Teach_battle_lose";
	}
	LAi_ActorWaitDialog(pchar, sld);
	LAi_ActorDialog(sld, pchar, "", 4.0, 0);
}

