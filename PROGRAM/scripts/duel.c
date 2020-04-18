

void Duel_Prepare_Fight()
{
	int i, idx, iTemp;
	ref npchar, rLoc, sld;

	npchar = CharacterFromID(pchar.questTemp.duel.enemy);
	DeleteAttribute(npchar, "City"); 
	makeref(rLoc, Locations[FindLoadedLocation()]);

	if (CheckAttribute(npchar, "LifeDay") && npchar.LifeDay >= 0)
	{
		npchar.LifeDay = sti(npchar.LifeDay) + 2;
	}
	
	if (CheckAttribute(rLoc, "type") && rLoc.type == "tavern")
	{
		if (PChar.chr_ai.type == LAI_TYPE_SIT)
		{
			LAi_SetPlayerType(pchar);
			PlaceCharacter(pchar, "tables", pchar.location);
		}
		PChar.Quest.Duel_Fight_Right_Now.win_condition.l1 = "Location";
		PChar.Quest.Duel_Fight_Right_Now.win_condition.l1.Location = "Clone_location";
		PChar.Quest.Duel_Fight_Right_Now.function = "Duel_Fight_Right_Now";

		LocationMakeClone(pchar.location);
		Locations[FindLocation("Clone_location")].image = "loading\tavern_fight.tga";

		DoReloadCharacterToLocation("Clone_location", pchar.location.group, pchar.location.locator);
		
		if(CheckAttribute(PChar,"questTemp.duel.enemyQty")) 
		{
			iTemp = sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE); 
			for(i = 0; i < sti(PChar.questTemp.duel.enemyQty); i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Berglar_Duel"+i, "citiz_"+(rand(9)+21), "man", "man", iTemp, PIRATE, 1, true, "hunter"));				
				SetFantomParamHunter(sld);
				PlaceCharacter(sld, "tables", "Clone_location");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "DUEL_FIGHTER");
			}
		}		
		Log_TestInfo("������ �������a(��) � ������� " + PlaceCharacter(npchar, "tables", "Clone_location") + " ������ " + "tables");
	}
	else
	{

		DoQuestFunctionDelay("Duel_Fight_Right_Now", 0.5);
	}

	
	for(i=1; i<4; i++)
	{
		idx = GetOfficersIndex(pchar, i);
		if(idx != -1) 
		{
			SetCharacterTask_Stay(&Characters[idx]);
			Characters[idx].chr_ai.tmpl = LAI_TMPL_STAY;
		}
	}

	if (GetCharacterEquipByGroup(npchar, BLADE_ITEM_TYPE) == "")
	{
		Log_TestInfo(npchar.id + " has no blade.");
		SetFantomParamHunter(npchar);
	}

	LAi_SetWarriorType(npchar);
	LAi_group_MoveCharacter(npchar, "DUEL_FIGHTER");
}


void Duel_Move_Opponent2Place(string qName)
{
	ref npchar, sld;
	aref arAll;
	string sTemp, attrName;

	npchar = CharacterFromID(pchar.questTemp.duel.enemy);
    
	if (GetQuestPastTimeParam("questTemp.Duel.StartTime") < sti(pchar.questTemp.Duel.WaitTime))
	{
		DeleteAttribute(pchar, "quest.duel_move_opponent2place.over");
		pchar.quest.Duel_CheckSituation.win_condition.l1 = "ExitFromLocation";
		pchar.quest.Duel_CheckSituation.win_condition.l1.location = pchar.location;
		pchar.quest.Duel_CheckSituation.function = "Duel_CheckSituation";
		return;
	}

	if (GetQuestPastTimeParam("questTemp.Duel.StartTime") >= sti(pchar.questTemp.Duel.WaitTime) + 1)
	{
		pchar.questTemp.Duel.Coward = true;
		return;
	}

	npchar.BackUp.location = npchar.location;
	npchar.BackUp.location.group = npchar.location.group;
	npchar.BackUp.location.locator = npchar.location.locator;
	npchar.BackUp.DialogNode = npchar.Dialog.CurrentNode;

	npchar.Dialog.CurrentNode = "talk_off_town";
	
	if (CheckAttribute(npchar, "PGGAi") && sti(npchar.PGGAi.IsPGG))
	{
		npchar.BackUp.town = npchar.PGGAi.location.town;
		npchar.PGGAi.location.town = "none";
	}

	sTemp = LAi_FindRandomLocator("encdetector");
	attrName = "locators." + sTemp;
	sld = &Locations[FindLocation(pchar.questTemp.duel.place)];
	makearef(arAll, sld.(attrName));
	attrName = GetAttributeName(GetAttributeN(arAll, rand(0)));
	ChangeCharacterAddressGroup(npchar, pchar.questTemp.duel.place, sTemp, attrName); 
	
	pchar.quest.Duel_Talk_Off_Town.win_condition.l1        = "locator";
	pchar.quest.Duel_Talk_Off_Town.win_condition.l1.location = sld.id;
	pchar.quest.Duel_Talk_Off_Town.win_condition.l1.locator_group = "Encdetector";
	pchar.quest.Duel_Talk_Off_Town.win_condition.l1.locator = sTemp;
	pchar.quest.Duel_Talk_Off_Town.function = "Duel_Talk_Off_Town";
	pchar.quest.Duel_Talk_Off_Town.EncQty = 1; 
	pchar.quest.Duel_Talk_Off_Town.LocIdx = sld.index; 

	
	LAi_SetGuardianType(npchar);
}

void Duel_CheckSituation(string qName)
{
	if (CheckAttribute(pchar, "questTemp.Duel.End")) return;
	if (GetQuestPastTimeParam("questTemp.Duel.StartTime") >= sti(pchar.questTemp.Duel.WaitTime))
	{
		if (GetQuestPastTimeParam("questTemp.Duel.StartTime") >= sti(pchar.questTemp.Duel.WaitTime)+1)
		{
			pchar.quest.duel_move_opponent2place.over = "yes";
			pchar.questTemp.Duel.End = true;
		}
		else
		{
			DoQuestFunctionDelay("Duel_Move_Opponent2Place", 2.0);
		}
	}
}


void Duel_Talk_Off_Town(string qName)
{	
	ref sld;
	sld = CharacterFromID(pchar.questTemp.duel.enemy);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}


void Duel_Fight_Right_Now(string qName)
{
	bool bOk = false;
	ref sld = &Locations[FindLocation(pchar.location)];

	
	if (CheckAttribute(sld, "noFight"))
	{
		bOk = sti(sld.noFight);
	}
	if (bOk)
	{
		LAi_LocationFightDisable(sld, !bOk);
		pchar.questTemp.LocFightEnable = bOk;
	}
	
	LAi_SetFightMode(pchar, true);
	LAi_group_SetRelation("DUEL_FIGHTER", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("DUEL_FIGHTER", LAI_GROUP_PLAYER, true);

	SetEventHandler("LAi_event_GroupKill", "Duel_Kill_Enemy", 0);
	LAi_group_SetCheckEvent("DUEL_FIGHTER");
	PChar.questTemp.Duel.Enemy.GrpId = "DUEL_FIGHTER";
}


void Duel_Kill_Enemy()
{
	ref sld;
	string sGroup = GetEventData();
	if (sGroup != PChar.questTemp.Duel.Enemy.GrpId) return;

    DelEventHandler("LAi_event_GroupKill", "Duel_Kill_Enemy");
	
	pchar.quest.Duel_Clear_Enemy.win_condition.l1 = "ExitFromLocation";
	pchar.quest.Duel_Clear_Enemy.win_condition.l1.location = pchar.location;
	pchar.quest.Duel_Clear_Enemy.function = "Duel_Clear_Enemy";
	
	
	
	
	if(CheckAttribute(PChar,"questTemp.duelQty")) 	
	{	
		pchar.questTemp.duelQty = sti(pchar.questTemp.duelQty) + 1;
		if(sti(pchar.questTemp.duelQty) == 7 + rand(2))
		{
			pchar.questTemp.HabitueSpeakDisable = true; 
			SetTimerCondition("HabitueSpeakDisable_End", 0, 2, rand(10), false);
		}
	}	
	else pchar.questTemp.duelQty = 1;
	
	if(CheckAttribute(PChar,"questTemp.duel.enemyQty")) DeleteAttribute(PChar,"questTemp.duel.enemyQty");	
	
	if (CheckAttribute(pchar, "questTemp.LocFightEnable") && sti(pchar.questTemp.LocFightEnable))
	{
		sld = &Locations[FindLocation(pchar.location)];
		LAi_LocationFightDisable(sld, true);
		DeleteAttribute(pchar, "questTemp.LocFightEnable");
	}

	
	if (CheckAttribute(pchar, "questTemp.LocationClone") && sti(pchar.questTemp.LocationClone))
	{
		DoQuestCheckDelay("TalkSelf_Start", 0.2);
	}

	
	DoQuestCheckDelay("hide_weapon", 2.0);
	
	if (Statistic_AddValue(PChar, "DuelKills", 1) > 20)
	{
		
		AddTemplRumour("DuelHero", id_counter+1) ;
	}
}


void Duel_Clear_Enemy(string qName)
{
	
	if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "duel")
	{
		if (!CheckCharacterItem(pchar, "kaleuche_key")) 
		{
			sld = CharacterFromID("FMQT_wife");
			sld.lifeday = 0;
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			AddQuestRecord("FMQ_Tortuga", "14");
			pchar.questTemp.FMQT = "fail";
			CloseQuestHeader("FMQ_Tortuga");
			FMQT_ClearChest();
		}
		else
		{
			AddQuestRecord("FMQ_Tortuga", "15");
			pchar.questTemp.FMQT = "key";
			FMQT_KeyNextDay();
		}
	}
}


void Duel_Move_OpponentBack(string qName)
{
	ref npchar = CharacterFromID(pchar.questTemp.duel.enemy);

	if (!CheckAttribute(pchar, "questTemp.Duel.End") || CheckAttribute(pchar, "questTemp.Duel.Coward"))
	{
		ChangeCharacterComplexReputationABS(pchar,"nobility", -5.0);
		ChangeCharacterComplexReputationABS(pchar,"fame", -5.0);
		AddTemplRumour("DuelCoward", id_counter+1);
	}

	if (sti(npchar.PGGAi))
	{
		npchar.PGGAi.location.town = npchar.BackUp.town;
	}

	if (CheckAttribute(npchar, "BackUp"))
	{
		ChangeCharacterAddressGroup(npchar, npchar.BackUp.location, npchar.BackUp.location.group, npchar.BackUp.location.locator); 
		npchar.Dialog.CurrentNode = npchar.BackUp.DialogNode;
	}
	Locations[FindLocation(pchar.questTemp.duel.place)].DisableEncounters = false;
	
	Log_TestInfo("Duel: POST CHECK!");
	DeleteAttribute(pchar, "questTemp.Duel");
	DeleteAttribute(npchar, "BackUp");
}


void Duel_Sea_Prepare()
{
	string sTemp = "DUEL_SEA";
	ref NPChar = characterFromID(pchar.questTemp.duel.enemy);
	
	
	
	NPChar.AlwaysEnemy = true;		  
	NPChar.Coastal_Captain = true;  
	NPChar.Abordage.Enable = false;
	NPChar.Nation.Bak = NPChar.Nation;
	NPChar.Nation = GetCityNation(GetCurrentTown());
	SetCharacterRelationBoth(sti(pchar.index), sti(npchar.index), RELATION_ENEMY);

	Group_AddCharacter(sTemp, npchar.id);
	Group_SetGroupCommander(sTemp, npchar.id);
	Group_SetAddress(sTemp, pchar.questTemp.Duel.Sea_Location, "Quest_Ships", "Quest_Ship_3");

	pchar.quest.Duel_Sea_Start.win_condition.l1 = "location";
	pchar.quest.Duel_Sea_Start.win_condition.l1.location = pchar.questTemp.Duel.Sea_Location;
	pchar.quest.Duel_Sea_Start.function = "Duel_Sea_Start";
}

void Duel_Sea_Start(string qName)
{
	string sTemp = "DUEL_SEA";
	Group_SetTaskAttackEx(sTemp, PLAYER_GROUP, false);
	Group_LockTask(sTemp);

	PChar.Quest.Duel_Sea_End.win_condition.l1 = "Group_Death";
	PChar.Quest.Duel_Sea_End.win_condition.l1.group = sTemp;
	PChar.Quest.Duel_Sea_End.function = "Duel_Sea_End";
}

void Duel_Sea_End(string qName)
{
	ref sld;
	sld = characterFromID(PChar.questTemp.duel.enemy);
	sld.Nation = sld.Nation.Bak;
	sld.Abordage.Enable = true;
	DeleteAttribute(PChar, "questTemp.duel");
	Group_DeleteGroup("DUEL_SEA");
}


void OnInit_DuelCoward(ref rTmpl)
{
	object oPrm;

	oPrm.Name = GetFullName(pchar);
	ttttstr = GetAssembledString(ttttstr, &oPrm);
}

string Event_DuelHero(ref rRum)
{
	object oPrm;

	oPrm.Name = GetFullName(pchar);
	oPrm.Kill = Statistic_AddValue(pchar, "DuelKills", 0);
	return GetAssembledString(rRum.text, &oPrm);
}



void MakeRandomLinkOrderTwo(aref link, string l1, string l1_go, string l2, string l2_go)
{
	link.l1 = l1;
	link.l1.go = l1_go;
	link.l2 = l2;
	link.l2.go = l2_go;
	if (rand(1))
	{
		link.l1 = l2;
		link.l1.go = l2_go;
		link.l2 = l1;
		link.l2.go = l1_go;
	}
}

void MakeRandomLinkOrderThree(aref link, string l1, string l1_go, string l2, string l2_go, string l3, string l3_go)
{
	switch (rand(5))
	{
	case 0:
		link.l1 = l1;
		link.l1.go = l1_go;
		link.l2 = l2;
		link.l2.go = l2_go;
		link.l3 = l3;
		link.l3.go = l3_go;
		break;

	case 1:
		link.l1 = l1;
		link.l1.go = l1_go;
		link.l2 = l3;
		link.l2.go = l3_go;
		link.l3 = l2;
		link.l3.go = l2_go;
		break;

	case 2:
		link.l1 = l2;
		link.l1.go = l2_go;
		link.l2 = l1;
		link.l2.go = l1_go;
		link.l3 = l3;
		link.l3.go = l3_go;
		break;

	case 3:
		link.l1 = l2;
		link.l1.go = l2_go;
		link.l2 = l3;
		link.l2.go = l3_go;
		link.l3 = l1;
		link.l3.go = l1_go;
		break;

	case 4:
		link.l1 = l3;
		link.l1.go = l3_go;
		link.l2 = l1;
		link.l2.go = l1_go;
		link.l3 = l2;
		link.l3.go = l2_go;
		break;

	case 5:
		link.l1 = l3;
		link.l1.go = l3_go;
		link.l2 = l2;
		link.l2.go = l2_go;
		link.l3 = l1;
		link.l3.go = l1_go;
		break;
	}
}
 
void TestFnc()
{
	Log_TestInfo("TestFnc Works");
}
 
