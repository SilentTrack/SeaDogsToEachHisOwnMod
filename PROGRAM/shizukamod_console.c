void ExecuteConsole()
{
	int i;
	//InitCharles();
	ref target = GetMainCharacter();
	//target.rank = 22;
	//InitTichingitu();
	//target.questTemp.LSC.Drink.Chance = 100;
	//Log_SetStringToLog(target.questTemp.LSC.Drink.Chance);
	//DeleteAttribute(target, "questTemp.Saga.Helena_friend");

	//JorgenSword();
	//MaryNarwhal();

	//Achievement(2);
	//target.questTemp.LSC.Mary = "return";
	//Log_SetStringToLog(pchar.questTemp.Caleuche.Amuletmaster);
	//Flamberge();
	//ChieftainsTalon();
	//SetAchievement("ach_79");
	Log_SetStringToLog(target.reputation.fame);
	Log_SetStringToLog(target.reputation.nobility);
	Log_SetStringToLog(target.reputation.authority);

	//ref sld = characterFromId("Mary");
	//sld.CanTakeMushket = true;

	//InitTeammate("Baker");
	//Log_SetStringToLog(target.questTemp.HWIC.Self.SpainCity);
	//target.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS48;
	Log_SetStringToLog("Executed Console");
}

void Achievement(int achievNum)
{
	string sAchiev = Achievment_GetID(achievNum);
	string achState = GetAchievement(sAchiev);
	Log_SetStringToLog(sAchiev);
	Log_SetStringToLog(achState);

	Achievment_SetStat(GetMainCharacter(), achievNum, 1);
	if (bSeaActive)
	{
		Log_SetStringToLog("True!");
	}
	else
	{
		Log_SetStringToLog("False, fuck!");
	}
}

void ChieftainsTalon()
{
	aref arItm;
	Items_FindItem("knife_01", &arItm);
	arItm.Attack = 34.5;
	arItm.Balance = 2.0;
	arItm.Weight = 3.0;
}

void Flamberge()
{
	aref arItm;
	Items_FindItem("blade_25", &arItm);
	arItm.Balance = 0.0;
	arItm.Weight = 3.0;
}

void JorgenSword()
{
	aref arItm;
	Items_FindItem("q_blade_21", &arItm);
	arItm.Balance = 2.0;
	arItm.Weight = 4.5;
}

void MaryNarwhal()
{
	sld = characterFromId("Mary");
	RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
	RemoveItems(sld, "blade_31", 1);
	sTemp = GetBestGeneratedItem("blade_31");
	int itemIndex;
	ref rItem1;
	itemIndex = GetItemIndex(sTemp);
	rItem1 = &Items[itemIndex];
	rItem1.Attack = 100.0;
	rItem1.Weight = 4.5;
	rItem1.Balance = 2.0;
	GiveItem2Character(sld, sTemp);
	EquipCharacterbyItem(sld, sTemp);
}

void InitTeammate(string id)
{
	ref target = GetCharacter(NPC_FindOrCreateCharacter(id));
	SetSPECIAL(target, 10, 10, 10, 10, 10, 10, 10);
	AddAllPerks(target);
	target.PerkValue.EnergyPlus = "8192";
}

void InitCharles()
{
	ref target = GetMainCharacter();
	SetSPECIAL(target, 10, 10, 10, 10, 10, 10, 10);
	SetSelfSkill(target, 1, 1, 1, 1, 1);
	SetShipSkill(target, 1, 1, 1, 1, 1, 1, 1, 1, 1);

	SetCharacterPerk(target, "HT1");
	SetCharacterPerk(target, "HT2");
	SetCharacterPerk(target, "HT3");
	SetCharacterPerk(target, "HT4");

	AddAllPerks(target);

	target.PerkValue.EnergyPlus = "8192";
}

void AddAllPerks(ref target)
{
	SetCharacterPerk(target, "BasicDefense");
	SetCharacterPerk(target, "AdvancedDefense");
	SetCharacterPerk(target, "CriticalHit");
	SetCharacterPerk(target, "HPPlus");
	SetCharacterPerk(target, "Tireless");
	SetCharacterPerk(target, "EnergyPlus");
	SetCharacterPerk(target, "Sliding");
	SetCharacterPerk(target, "SwordplayProfessional");
	SetCharacterPerk(target, "HardHitter");
	SetCharacterPerk(target, "BladeDancer");
	SetCharacterPerk(target, "Gunman");
	SetCharacterPerk(target, "GunProfessional");
	SetCharacterPerk(target, "Grus");
	SetCharacterPerk(target, "ByWorker");
	SetCharacterPerk(target, "ByWorker2");
	SetCharacterPerk(target, "IronWill");
	SetCharacterPerk(target, "ShipEscape");
	SetCharacterPerk(target, "SharedExperience");
	SetCharacterPerk(target, "Medic");
	SetCharacterPerk(target, "Trustworthy");
	SetCharacterPerk(target, "Alchemy");
	SetCharacterPerk(target, "Brander");
	SetCharacterPerk(target, "Troopers");
	SetCharacterPerk(target, "LongRangeGrappling");
	SetCharacterPerk(target, "GrapplingProfessional");
	SetCharacterPerk(target, "MusketsShoot");
	SetCharacterPerk(target, "BasicCommerce");
	SetCharacterPerk(target, "AdvancedCommerce");
	SetCharacterPerk(target, "ProfessionalCommerce");
	SetCharacterPerk(target, "FastReload");
	SetCharacterPerk(target, "ImmediateReload");
	SetCharacterPerk(target, "HullDamageUp");
	SetCharacterPerk(target, "SailsDamageUp");
	SetCharacterPerk(target, "CrewDamageUp");
	SetCharacterPerk(target, "CriticalShoot");
	SetCharacterPerk(target, "LongRangeShoot");
	SetCharacterPerk(target, "CannonProfessional");
	SetCharacterPerk(target, "Carpenter");
	SetCharacterPerk(target, "LightRepair");
	SetCharacterPerk(target, "Builder");
	SetCharacterPerk(target, "BasicBattleState");
	SetCharacterPerk(target, "AdvancedBattleState");
	SetCharacterPerk(target, "InstantRepair");
	SetCharacterPerk(target, "SelfRepair");
	SetCharacterPerk(target, "ShipDefenseProfessional");
	SetCharacterPerk(target, "ShipSpeedUp");
	SetCharacterPerk(target, "ShipTurnRateUp");
	SetCharacterPerk(target, "StormProfessional");
	SetCharacterPerk(target, "WindCatcher");
	SetCharacterPerk(target, "SailsMan");
	SetCharacterPerk(target, "Turn180");
	SetCharacterPerk(target, "SailingProfessional");
	SetCharacterPerk(target, "Doctor1");
	SetCharacterPerk(target, "Doctor2");
	SetCharacterPerk(target, "SeaDogProfessional");
	SetCharacterPerk(target, "FlagPir");
	SetCharacterPerk(target, "FlagEng");
	SetCharacterPerk(target, "FlagFra");
	SetCharacterPerk(target, "FlagSpa");
	SetCharacterPerk(target, "FlagHol");
}