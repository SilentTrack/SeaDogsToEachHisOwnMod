

void CompanionTravel_SetTraveller(ref _NPChar)
{
	ref sld;
	string sTemp, attrLoc, attr;
	int fChance;
	sld = &characters[sti(_NPChar.realcompanionidx)];

	if(!CheckAttribute(PChar, "CompanionTravel")) PChar.CompanionTravel = 0;
	PChar.CompanionTravel = sti(PChar.CompanionTravel) + 1; 
	for(iTemp=1; iTemp<=3; iTemp++) 
	{
		if(Group_IsDead("CompanionTravel_Companion"+iTemp))
			attr = "Companion" + iTemp;
	}
	
	CompanionTravel_SetSpecialShipAttributes(sld);
	sld.CompanionTravel.GroupID = "CompanionTravel_" + attr; 
	
	sTemp = _NPChar.ID;
	PChar.CompanionTravel.(attr).ID = sld.ID ; 
	PChar.CompanionTravel.(attr).Days = sti(sld.CompanionTravel.Days); 
	PChar.CompanionTravel.(attr).ToColonyID = sld.CompanionTravel.ToColonyID; 
	
	fChance = CompanionTravel_CalculateSinkChance(sld, PChar.CompanionTravel.(attr).ToColonyID);
	if(fChance > rand(100)) 
	{
		PChar.CompanionTravel.(attr).Sink = true;
	}
	
	attrLoc = "CompanionTravel_" + attr; 
	
	Group_FindOrCreateGroup(attrLoc);
	Group_SetType(attrLoc, "pirate");
	Group_AddCharacter(attrLoc, PChar.CompanionTravel.(attr).ID);
	Group_SetGroupCommander(attrLoc, PChar.CompanionTravel.(attr).ID);
	Group_SetTaskRunaway(attrLoc, PLAYER_GROUP); 
	Group_LockTask(attrLoc);
	
	
	 
	
	Log_TestInfo("=====" + attr + "=====");
	Log_TestInfo("ID ����������, �������������� � �������� - " + PChar.CompanionTravel.(attr).ID);
	Log_TestInfo("������� ����� � ��������� �������� - " + PChar.CompanionTravel.(attr).Days + " ����");
	Log_TestInfo("��������� ������� � ������� � ID - " + PChar.CompanionTravel.(attr).ToColonyID);
	Log_TestInfo("����, ��� ��������� �� ������ �� ����� ���������� - "+fChance);
	Log_TestInfo("������ �� ��������� �� ����� ���������� (0 - �� ������, 1 - ������) - "+!CheckAttribute(PChar, "CompanionTravel."+(attr)+".Sink"));
	RemoveCharacterCompanion(PChar, sld);
}

void CompanionTravel_ProcessAllTravellers() 
{
	aref arTravellers;
	makearef(arTravellers, PChar.CompanionTravel);
	int iTravellersCount = GetAttributesNum(arTravellers);
	if(iTravellersCount == 0) return;
	
	Log_TestInfo("����� �����������-���������������� - "+iTravellersCount);
		
	string sCompanionTraveller;
	for(int i=0; i<iTravellersCount; i++)
	{
		sCompanionTraveller = GetAttributeName(GetAttributeN(arTravellers, i));
		Log_TestInfo("��������� ����������-��������������� "+sCompanionTraveller);
		CompanionTravel_DayUpdate(sCompanionTraveller);
	}
}

void CompanionTravel_DayUpdate(string sCompanion) 
{
	string sID = PChar.CompanionTravel.(sCompanion).ID;
	int iDays = sti(PChar.CompanionTravel.(sCompanion).Days);
	ref rCompanion = CharacterFromID(sID);
	CompanionTravel_SetExperienceToTraveller(rCompanion); 
	if(!bNoEatNoRats)
	{
		DailyEatCrewUpdateForShip(rCompanion, true);
	}
	CompanionTravel_SetRandomEvent(rCompanion); 
	iDays--;
	PChar.CompanionTravel.(sCompanion).Days = iDays;
	Log_TestInfo(sCompanion+" - �������� ���� (���� < 0, ������ ���� � �����) - "+iDays);
	if(iDays == 0) 
	{
		CompanionTravel_TimerToSetInColony(sCompanion); 
	}
	
	if(iDays == -30) 
	{
		CompanionTravel_DeleteCompanion(sID, sCompanion, true);
	}
}

void CompanionTravel_TimerToSetInColony(string sCompanion) 
{
	if(!CheckAttribute(PChar, "CompanionTravel."+sCompanion+".ToColonyID")
	|| !CheckAttribute(PChar, "CompanionTravel."+sCompanion+".ID") || !CheckAttribute(PChar, "CompanionTravel."+sCompanion+".Days"))
	{
		Log_Info("����������� ���: �� ������ ���� �� ��������� � ����������-��������������� "+sCompanion+". ���������� �������� Warship'�.");
		return;
	}
	
	string sID = PChar.CompanionTravel.(sCompanion).ID;
	string sColony = PChar.CompanionTravel.(sCompanion).ToColonyID;
	int iDays = sti(PChar.CompanionTravel.(sCompanion).Days);
	ref sld = CharacterFromID(sID);
	
	if(CheckAttribute(PChar, "CompanionTravel."+sCompanion+".Sink")) 
	{
		CompanionTravel_DeleteCompanion(sID, sCompanion, false);
		return;
	}
	
	CompanionTravel_SetCompanionToColony(sColony, "CompanionTravel_"+sCompanion, sID); 
}

void CompanionTravel_DeleteCompanion(string sID, string sCompanion, bool WaitInColony)
{
	ref rTraveller = CharacterFromID(sID);
	DeleteAttribute(rTraveller, "CompanionTravel");
	rTraveller.LifeDay = 0;
	DeleteAttribute(PChar, "CompanionTravel."+sCompanion);
	if(WaitInColony)
	{
		Log_TestInfo("���� ������ CompanionTravel_"+sCompanion+" ������� ����� ���� � ������� � ������.");
	}
	else
	{
		Log_TestInfo("����� ���� ������ CompanionTravel_"+sCompanion+" �� ����� �� ����� ����������.");
	}
	
	
	Group_DeleteAtEnd("CompanionTravel_"+sCompanion);
	PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; 
}

void CompanionTravel_SetCompanionToColony(string sColony, string sGroupID, string sID) 
{
	string sIsland = colonies[FindColony(sColony)].Island;
	Log_TestInfo("��������� ������� ���� - " + sID + ", ������ - " + sGroupID + " � ������� - " + sColony + " (" + sIsland + ")");
	ref sld = CharacterFromID(sID);
	sld.CompanionTravel.WaitOnColony = true;
	sld.DeckDialogNode = "hired";
	Group_FindOrCreateGroup(sGroupID);
	Group_SetType(sGroupID, "pirate");
	Group_AddCharacter(sGroupID, sID);
	Group_SetGroupCommander(sGroupID, sID);
	Group_SetTaskNone(sGroupID);
	if(sIsland != "Barbados")
		Group_SetAddress(sGroupID, sIsland, "Quest_Ships", "reload_fort1_siege");
	else
		Group_SetAddress(sGroupID, sIsland, "Quest_Ships", "reload_fort1__siege");
	Group_LockTask(sGroupID);
}

float CompanionTravel_CalculateSinkChance(ref _NPC, String _sColony)
{
	Log_TestInfo("=============== ������������ ���� ���������� ===============");
	
	float fChance = 5;
	int iHPPercent = GetHullPercent(_NPC);
	int iSPPercent = GetSailPercent(_NPC);
	int iCrew = sti(_NPC.Ship.Crew.Quantity);
	int iRealShipOptimalCrew = sti(RealShips[sti(_NPC.Ship.Type)].SailorCrew);
	int iSailSkill = GetSummonSkillFromNameSimple(_NPC, SKILL_SAILING);
	int iShipClass = GetCharacterShipClass(_NPC);
	int iNeedSailSkill = GetShipClassNavySkill(iShipClass);
	int iDays = makeint(GetDistanceToColony2D(_sColony)/100); 
	
	Log_TestInfo("���� - "+fChance);
	if(iHPPercent < 50) fChance = fChance+(50-iHPPercent)*1.5; 
	Log_TestInfo("���� + ���� ������� - "+fChance);
	
	if(iSPPercent < 50) fChance = fChance+(50-iSPPercent)*0.5; 
	Log_TestInfo("���� + ���� ������� + ���� ������� - "+fChance);
	
	if(iSailSkill < iNeedSailSkill) fChance = fChance+(iNeedSailSkill-iSailSkill)*0.8; 
	Log_TestInfo("���� + ���� ������� + ���� ������� + ���� ���� - "+fChance);
	
	if(iDays > 7) fChance = fChance*((iDays-7)*0.1+1);
	Log_TestInfo("( ���� + ���� ������� + ���� ������� + ���� ���� ) * ���� ���� - "+fChance);
	Log_TestInfo("=============== ���� ���������� ���������. ���� - "+fChance+" ===============");
	
	return fChance;
}

void CompanionTravel_SetSpecialShipAttributes(ref _NPChar)
{
	_NPChar.Abordage.Enable = false;
	_NPChar.DontCheckFlag = true;
	_NPChar.AlwaysFriend        = true;
	_NPChar.ShipEnemyDisable  = true;
}

void CompanionTravel_DeleteSpecialShipAttributes(ref _NPChar)
{
	DeleteAttribute(_NPChar, "Abordage.Enable");
	DeleteAttribute(_NPChar, "DontCheckFlag");
	DeleteAttribute(_NPChar, "AlwaysFriend");
	DeleteAttribute(_NPChar, "ShipEnemyDisable");
}

void CompanionTravel_SetExperienceToTraveller(ref _NPC)
{
	int iRank = sti(_NPC.Rank);
	int iExp = (rand(1)+1)+(iRank/2);
	AddCharacterExpToSkill(_NPC, "Leadership", iExp);
	AddCharacterExpToSkill(_NPC, "Fortune", iExp);
	AddCharacterExpToSkill(_NPC, "Sailing", iExp);
	AddCharacterExpToSkill(_NPC, "Accuracy", iExp/2);
	AddCharacterExpToSkill(_NPC, "Cannons", iExp/2);
}

 

void CompanionTravel_SetRandomEvent(ref _NPC) 
{
	int iRand = rand(4);
	int iShipHP = sti(_NPC.Ship.HP);
	int iShipHPMax = sti(RealShips[sti(_NPC.Ship.Type)].hp);
	int iShipSP = GetSailPercent(_NPC);
	int iCrew = GetCrewQuantity(_NPC);
	int iMinCrew = sti(RealShips[sti(_NPC.Ship.Type)].mincrew)
	
	switch(iRand)
	{
		case 0: 
			if(iShipHP <= iShipHPMax/10) break;
			_NPC.Ship.HP = sti(_NPC.Ship.HP) - (iShipHPMax/30);
		break;
		
		case 1: 
			  
		break;
		
		case 2: 
			if(iCrew <= iMinCrew) break;
			_NPC.Ship.Crew.Quantity = iCrew-(rand(4)+2);
		break;
		
		case 3:
		
		break;
		
		case 4:
		
		break;
	}
}
