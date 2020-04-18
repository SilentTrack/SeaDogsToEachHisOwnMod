
int PsHeroQty = 0; 

#define PGG_TASK_NOTASK			"NoTask"
#define PGG_TASK_WAITINTAVERN	"WaitInTavern"
#define PGG_TASK_WORKONMAYOR	"WorkOnMayor"
#define PGG_TASK_SAILTOISLAND	"SailToIsland"
#define PGG_TASK_GOTOWAR		"GoToWar"
#define PGG_TASK_WORKCONVOY		"WorkConvoy"
#define PGG_TASK_WORKONSTORE	"WorkOnStore"
#define PGG_TASK_WORKWITHCONTRA	"WorkWithContra"
#define PGG_TASK_LOCKSERVICE	"LockService"


#define EXP_MODIFIER  0.25



void InitPsHeros()
{
	int n;
	ref ch;
	PsHeroQty = 0; 
	for (n = 1; n <= MaxPGGQty + MaxHeroQty; n++)
	{
		if(n <= MaxHeroQty)
		{
			if(n != startHeroType)
			{			
				PsHeroQty++;
				ch = GetCharacter(NPC_GenerateCharacter("PsHero_" + PsHeroQty, "off_hol_2", "man", "man", 5, PIRATE, -1, true, "pofficer"));
				CCS_setNewMainCharacter(ch, n);
			}
			else continue;
		}
		else
		{
			PsHeroQty++;
			ch = GetCharacter(NPC_GenerateCharacter("PsHero_" + PsHeroQty, "mercen_" + (rand(14)+14), "man", "man", 5, PIRATE, -1, true, "pofficer"));
			SetNPCModelUniq(ch, "pofficer", "man");
			SetRandomNameToCharacter_Generator(ch);
			ch.Nation = rand(4); 
			FaceMaker(ch);
			CirassMaker(ch);
		}
		if(rand(10) < 7) ch.HeroParam.HeroType = "HeroType_1";
		else
		{
			switch(rand(2))
			{
				case 0:
					ch.HeroParam.HeroType = "HeroType_2";
				break;
				case 1:
					ch.HeroParam.HeroType = "HeroType_3";
				break;
				case 2:
					ch.HeroParam.HeroType = "HeroType_4";
				break;
			}
		}	
		ch.PGGAi.HeroNum = PsHeroQty;
		ch.reputation = 2 + rand(86);
		ch.RebirthPhantom = true;  
		ch.Dialog.Filename = "pgg_dialog.c";
		ch.greeting = "Gr_PsHero";
		ch.SaveItemsForDead = true; 
		ch.DontClearDead = true;  
		ch.DontRansackCaptain = true; 
		ch.AlwaysSandbankManeuver = true;  
		ch.SuperShooter  = true;
		ch.perks.list.ByWorker = "1";
		ch.perks.list.ShipEscape = "1";
		ch.loyality = 10 + rand(10); 
		if (sti(ch.reputation) > 41)
		{
			ch.alignment = "good";
		}
		else
		{
			ch.alignment = "bad";
		}
		ch.HoldEquip = true; 			
		ch.PGGAi = true;    			
		ch.PGGAi.IsPGG = true;  		
		ch.PGGAi.location = "land";   	
		ch.PGGAi.location.town = PGG_FindRandomTownByNation(sti(ch.nation));
		SetFantomParamFromRank(ch, 1 + rand(5), true); 
		trace("PGG : " + GetFullName(ch) + " starting rank : " + sti(ch.rank) + " model : " + ch.model );
		SetCharacterPerk(ch, "Energaiser"); 
		ch.Money = 8000 + rand(1000)*10; 	
	}
	for (n = 1; n <= PsHeroQty; n++)
	{
		ch = CharacterFromID("PsHero_" + n);
		PGG_SetRelation2OtherAsNormal(ch);
	}
	trace("��� ��������� " + PsHeroQty);
	trace("��������� ������� ��� �����������.");
	SaveCurrentQuestDateParam("PGG_DailyUpdate");
}


void PGG_DailyUpdate()
{
	int i, j, iDays;

    if(!actLoadFlag)
    {
		iDays = GetQuestPastDayParam("PGG_DailyUpdate");
		if (iDays < 1) return;

		for (i = 0; i < iDays; i++)
		{
			for (j = 1; j <= PsHeroQty; j++)
			{
				PGG_DailyUpdateEx(j);
			}
		}
		SaveCurrentQuestDateParam("PGG_DailyUpdate");
	}
}

 
void PGG_DailyUpdateEx(int i)
{
	string sTask;
	ref chr;
	int iDays;



	chr = CharacterFromID("PsHero_" + i);

	
	if (IsCompanion(chr))
	{
		
		if (GetNpcQuestPastDayParam(chr, "Companion.CheckRelation") > 30)
		{
			
			if (PGG_ChangeRelation2MainCharacter(chr, 0) < 5 && sti(chr.Ship.Type) != SHIP_NOTUSED)
			{
				pchar.Quest.PGG_Companion_Leave.win_condition.l1 = "Location_Type";
				pchar.Quest.PGG_Companion_Leave.win_condition.l1.location_type = "tavern";
				pchar.Quest.PGG_Companion_Leave.function = "PGG_CompanionLeave";
				pchar.questTemp.PGG_Companion_Leave.index = chr.index;
			}
			SaveCurrentNpcQuestDateParam(chr, "Companion.CheckRelation");
		}
	}

	
	
	if (LAi_IsDead(chr) || !sti(chr.PGGAi.IsPGG)) 
	{
		if (LAi_IsDead(chr))
		{
			if (CheckAttribute(chr, "PGGAi.Rebirth") && sti(chr.PGGAi.Rebirth))
			{
				LAi_SetCurHPMax(chr);
				DeleteAttribute(chr, "PGGAi.Rebirth")
				DeleteAttribute(chr, "Ship");
				chr.Ship.Type = SHIP_NOTUSED;
				chr.Dialog.FileName = "PGG_dialog.c";
				chr.Dialog.CurrentNode = "Second Time";
			}
			else
			{
				PGG_CheckDead(chr);
			}
		}
 
		return;
	}

	
	
	if (rand(100) > 60) PGG_UpdateStats(chr, "Daily");
	
	if (CheckAttribute (chr, "PGGAi.Task") && chr.PGGAi.Task != PGG_TASK_NOTASK)
	{
		sTask = chr.PGGAi.Task;
		
		
		if (sTask == PGG_TASK_LOCKSERVICE || sTask == PGG_TASK_WORKONMAYOR)
		{
			DeleteAttribute(chr, "PGGAi.LockService");
			PGG_SelectTask(chr);
		}
		
		if (sTask == PGG_TASK_WORKWITHCONTRA)
		{
			chr.PGGAi.Task.DaysCounter = sti(chr.PGGAi.Task.DaysCounter) + 1;
			if (sti(chr.PGGAi.Task.DaysCounter) > 3)
			{
				if (CheckAttribute(pchar, "questTemp.PGGContra.Know"))
				{
					RemoveSmugglersFromShore();
					pchar.Quest.Rand_Smuggling.Over = "yes";
				}
				DeleteAttribute(chr, "PGGAi.LockService");
				DeleteAttribute(chr, "PGGAi.Task.DaysCounter");
				PGG_SelectTask(chr);
			}
			else PGG_DebugLog(chr.id + " " + chr.PGGAi.Task + " " + chr.PGGAi.Task.DaysCounter);
		}
		
		if (sTask == PGG_TASK_WAITINTAVERN)
		{
			
			if (sti(chr.Money) < 16000)
			{
				
				if (rand(100) < 60)
				{
					chr.PGGAi.Task = PGG_TASK_WORKONMAYOR;
					PGG_UpdateStats(chr, "Task");
				}
				else
				{
					PGG_DebugLog(chr.id + " stayed in tavern.");
				}
			}
			
			else
			{
				PGG_UpdateStats(chr, "");
				PGG_SelectTask(chr);
			}
		}
		
		if (sTask == PGG_TASK_SAILTOISLAND || sTask == PGG_TASK_WORKCONVOY || sTask == PGG_TASK_WORKONSTORE)
		{
			if (CheckAttribute(chr, "PGGAi.Task.days") && sti(chr.PGGAi.Task.Target.days) == GetNpcQuestPastDayParam(chr, "PGGAi.Task.days"))
			{
				chr.PGGAi.location = "land";
				chr.PGGAi.location.town = chr.PGGAi.Task.Target;
				
				AddRemoveGoodsInStore(chr.PGGAi.location.town, sti(chr.PGGAi.Task.Target.Goods), sti(chr.PGGAi.Task.Target.Goods.Qty), true);
				DeleteAttribute(chr, "PGGAi.Task");
				PGG_SelectTask(chr);
			}
			else
			{
				iDays = sti(chr.PGGAi.Task.Target.days);
				PGG_DebugLog(chr.id + " " + chr.PGGAi.Task + " Target: " + 
					chr.PGGAi.Task.Target + " days: " + iDays);
			}
		}
	}
	
	else 
	{
		PGG_SelectTask(chr);
	}
	if (chr.PGGAi.location == "land" && sti(chr.Ship.Type) != SHIP_NOTUSED) 
	{
		chr.location.from_sea = chr.PGGAi.location.town + "_town";
	}
	else
	{
		chr.location.from_sea = "";
	}
 
}



void PGG_CheckDead(ref chr)
{
	if (chr.PGGAi.location == "Dead") return;
	if (IsCompanion(chr) && GetRemovable(chr) && CheckOfficersPerk(chr, "ShipEscape")) return;

	
	PChar.questTemp.Chr2Remove = chr.id;
	if (!bSeaActive)
	{
		PChar.Quest.RemovePGG.win_condition.l1 = "ExitFromLocation";
		PChar.Quest.RemovePGG.win_condition.l1.Location = PChar.location;
	}
	else
	{
		PChar.Quest.RemovePGG.win_condition.l1 = "ExitFromSea";
	}
	PChar.Quest.RemovePGG.win_condition = "RemoveCharacterFromLocation";

	
	if (sti(chr.PGGAi.IsPGG) && rand(100) > 50) 
	{
		PGG_DebugLog(chr.id + " ������ �� ���� :(");
	}
	else
	{
		if (IsOfficer(chr) || IsCompanion(chr))
		{
			PGG_DebugLog(chr.id + " ������ �� ���� :(((");
		}
		else
		{
			chr.PGGAi.Rebirth = true;
			PGG_DebugLog(chr.id + " ����� :)))");
			if (CheckAttribute(chr, "PGGAi.location.town.back"))
			{
				chr.PGGAi.location.town = chr.PGGAi.location.town.back;
			}
			if (chr.PGGAi.location.town == "None") 
			{
				chr.PGGAi.location.town = PGG_FindRandomTownByNation(sti(chr.nation));
			}
			DeleteAttribute(chr, "PGGAi.Task");
			DeleteAttribute(chr, "PGGAi.LockService");
			return;
		}
	}

	chr.chr_ai.hp = 0.0;

	DeleteAttribute(chr, "PGGAi.Task");
	DeleteAttribute(chr, "PGGAi.LockService");

	chr.PGGAi.location = "Dead";
	chr.PGGAi.location.town = "None";
}




void PGG_SelectTask(ref chr)
{
	ref rShip;
	int iRnd = -1;
	int iShipType = sti(chr.Ship.Type);
	
	if (iShipType == SHIP_NOTUSED)
	{
		if (rand(100) < 30)
		{
			chr.PGGAi.Task = PGG_TASK_WORKONMAYOR;
		}
		else
		{
			chr.PGGAi.Task = PGG_TASK_WAITINTAVERN;
		}
	}
	else iRnd = rand(6);

	switch(iRnd)
	{
	case 0:
		chr.PGGAi.Task = PGG_TASK_SAILTOISLAND;
		break;
	case 1:
		chr.PGGAi.Task = PGG_TASK_WORKONMAYOR;
		PGG_LockService(chr, "Store");
		break;
	
	case 2:
		chr.PGGAi.Task = PGG_TASK_LOCKSERVICE;
		PGG_LockService(chr, "");
		break;
	
	case 3:
		chr.PGGAi.Task = PGG_TASK_WORKCONVOY;
		break;
	
	case 4:
		chr.PGGAi.Task = PGG_TASK_WORKONSTORE;
		break;
	
	case 5:
		chr.PGGAi.Task = PGG_TASK_WORKWITHCONTRA;
		chr.PGGAi.Task.DaysCounter = 1;
		PGG_LockService(chr, "Smugglers");
		break;
	
	case 6:
		chr.PGGAi.Task = PGG_TASK_WORKONMAYOR;
		PGG_LockService(chr, "Store");
		break;
	}

	PGG_SetUpForTask(chr);
	PGG_UpdateStats(chr, "Task");

	
	if (rand(100) < 15) 
	{
		PGG_AddRumour(chr, chr.PGGAi.Task);
	}
}



void PGG_LockService(ref chr, string _service)
{
	if (_service != "") 
	{
		chr.PGGAi.LockService = _service;
		return;
	}

	if (rand(1) == 1)
	{
		chr.PGGAi.LockService = "Shipyard";
	}
	else
	{
		chr.PGGAi.LockService = "Store";
	}
}


void PGG_SetUpForTask(ref chr)
{
	int iTradeGoods, iQuantityGoods, iMoney;
	string sTask = chr.PGGAi.Task;

	if (sTask == PGG_TASK_WORKONSTORE || sTask == PGG_TASK_SAILTOISLAND || sTask == PGG_TASK_WORKCONVOY)
	{
		PGG_UpdateShipEquip(chr);
		
		PGG_PlaceCharacter2Tavern(chr, false);

		iTradeGoods = rand(GOOD_SILVER);
		RecalculateSquadronCargoLoad(chr);
		iQuantityGoods = GetSquadronFreeSpace(chr, iTradeGoods);
		iQuantityGoods = iQuantityGoods - rand(makeint(iQuantityGoods/3)) - 10;
		
		
		iMoney = makeint((iQuantityGoods / sti(Goods[iTradeGoods].Units)) * sti(Goods[iTradeGoods].Cost) * GetSummonSkillFromNameToOld(chr, SKILL_COMMERCE)/8);
	
		if (iQuantityGoods < 0) iQuantityGoods = 0;
		AddCharacterGoods(chr, iTradeGoods, iQuantityGoods);
		PGG_AddMoneyToCharacter(chr, iMoney);
		
		
		AddRemoveGoodsInStore(chr.PGGAi.location.town, iTradeGoods, iQuantityGoods, false);
		

		PGG_FindTargetTown(chr);
		chr.PGGAi.Task.Target.Goods = iTradeGoods;
		chr.PGGAi.Task.Target.Goods.Qty = iQuantityGoods;
		chr.PGGAi.location = "sea";
		SaveCurrentNpcQuestDateParam(chr, "PGGAi.Task.days");
	}
}


void PGG_UpdateStats(ref chr, string sExpType)
{
	float fMod;
	int iMoney = 0;
	int i, iRnd;
	string sHeroType = chr.HeroParam.HeroType;

	if (!CheckAttribute(chr, "PGGAi.OldRank")) chr.PGGAi.OldRank = chr.Rank;
	if (sExpType == "Daily")
	{
		if (chr.PGGAi.location == "land")
		{
			

			fMod = MOD_SKILL_ENEMY_RATE + rand(MOD_SKILL_ENEMY_RATE + 12);
			fMod = fMod*EXP_MODIFIER; 

			AddCharacterExpToSkill(chr, GetEquipedBladeType(chr), fMod*261);
			AddCharacterExpToSkill(chr, SKILL_PISTOL, fMod*34.444);
			AddCharacterExpToSkill(chr, SKILL_FORTUNE, fMod*11.369);
			AddCharacterExpToSkill(chr, SKILL_LEADERSHIP, fMod*11.759);
			AddCharacterExpToSkill(chr, SKILL_DEFENCE, fMod*11.5);
			
			fMod = MOD_SKILL_ENEMY_RATE + rand(12);
			fMod = fMod*EXP_MODIFIER; 
			AddCharacterExpToSkill(chr, SKILL_COMMERCE, fMod*25.2);
		}
		else
		{
			
			iRnd = 20;
			
			if (sHeroType != "Merchant")
			{
				iRnd += 15;
			}

			if (rand(100) < iRnd)
			{
				
				PGG_AddMoneyToCharacter(chr, PGG_AddShipsBattleExp(chr, 1 + rand(makeint(MOD_SKILL_ENEMY_RATE*0.5))));
			}
		}
	}
	if (sExpType == "Task")
	{
		switch (chr.PGGAi.Task)
		{
		case PGG_TASK_WORKONMAYOR:
            AddCharacterExpToSkill(chr, SKILL_LEADERSHIP, 20 + MOD_SKILL_ENEMY_RATE + rand(MOD_SKILL_ENEMY_RATE + 40));
		    AddCharacterExpToSkill(chr, SKILL_COMMERCE, 3 + MOD_SKILL_ENEMY_RATE);
			iMoney = Makeint(sti(chr.rank)*200 + (GetSummonSkillFromNameToOld(chr, SKILL_LEADERSHIP)*30 + 700 + rand(20)*100));
			
			iRnd = rand(100);
			
			if (sti(chr.Ship.Type) != SHIP_NOTUSED && iRnd > 67)
			{
				iMoney = PGG_AddShipsBattleExp(chr, 1);
			}
			
			else
			{
				
			}
			PGG_AddMoneyToCharacter(chr, iMoney);
			break;
		}
		PGG_DebugLog(chr.id + " " + chr.PGGAi.Task + " money: " + iMoney);
	}
	
	PGG_UpdatePerks(chr);
	PGG_UpdateEquip(chr);
	PGG_UpdateShipEquip(chr);
	
	if (chr.PGGAi.OldRank != chr.Rank && rand(100) < 40)
	{
		chr.PGGAi.OldRank = chr.Rank;
		DelBakSkillAttr(chr);
		ClearCharacterExpRate(chr);
		RefreshCharacterSkillExpRate(chr);
	}
}


int PGG_AddShipsBattleExp(ref chr, int _shipsNum)
{
	string sDebugStr;
	ref rShip;
	int i, iMoney;
	float fTmp = 0.0;
	float fMod = MOD_SKILL_ENEMY_RATE * EXP_MODIFIER * _shipsNum;

	AddCharacterExpToSkill(chr, SKILL_ACCURACY, fMod*29.4 + FRAND(100.0));
	AddCharacterExpToSkill(chr, SKILL_SAILING, fMod*7.0);
	AddCharacterExpToSkill(chr, SKILL_CANNONS, makefloat((12+rand(80))*12.5));

	sDebugStr = chr.id + " fight with " + _shipsNum + " ships.";
	iMoney = 0;
	
	if (rand(100) < 30)
	{
		
		rShip = GetRealShip(sti(chr.Ship.Type));
		if (rand(2) == 1)
		{
			fTmp = 1.0;
			
			iMoney = sti(rShip.Price)*0.2 + rand(sti(sti(rShip.Price)*0.5));
			sDebugStr += " Took them.";
		}
		
		else
		{
			AddCharacterExpToSkill(chr, SKILL_ACCURACY, fMod * 40);
			AddCharacterExpToSkill(chr, SKILL_SAILING, fMod * 70);
			AddCharacterExpToSkill(chr, SKILL_CANNONS, fMod * 40);
			AddCharacterExpToSkill(chr, SKILL_SAILING, fMod * 100);
			sDebugStr += " Destroyed them.";
		}

		i = sti(chr.ship.crew.quantity);
		AddCharacterExpToSkill(chr, GetEquipedBladeType(chr), fMod*FRAND(233.4));
		AddCharacterExpToSkill(chr, SKILL_PISTOL, fMod*3.48);
		AddCharacterExpToSkill(chr, SKILL_FORTUNE, fMod*(2.4 + fTmp*20));
		AddCharacterExpToSkill(chr, SKILL_LEADERSHIP, fMod*(2.4 + fTmp*25));
		AddCharacterExpToSkill(chr, SKILL_DEFENCE, fMod*(1.0 + fTmp*40));
		AddCharacterExpToSkill(chr, SKILL_COMMERCE, fMod * 50 * fTmp);
		AddCharacterExpToSkill(chr, SKILL_REPAIR, fMod * 60 * fTmp);

		AddCharacterExpToSkill(chr, SKILL_GRAPPLING, ((1+i-rand(i))/3+0.5+110) + (fMod * 120 * fTmp));
		AddCharacterExpToSkill(chr, SKILL_DEFENCE, (1+i-rand(i))/3+0.5+60); 
		AddCharacterExpToSkill(chr, SKILL_SAILING, ((1+i-rand(i))/3+0.5+110) + (fMod * 120 * fTmp));
		AddCharacterExpToSkill(chr, SKILL_FORTUNE, (1+i-rand(i))/3+0.5+60); 

		
		iMoney += 1000 + rand(2000);
		
		i = 1;
		
		if (rand(100) < 5)
		{
			PGG_DebugLog("PGG BIG LUCK");
			i = 5;
		}
		iMoney += rand(100)*10*i;
	}
	PGG_DebugLog(sDebugStr);
	return iMoney * _shipsNum;
}


void PGG_UpdatePerks(ref chr)
{
	
	if (!CheckAttribute(chr, "perks.freepoints_self")) chr.perks.freepoints_self = 0;
	if (!CheckAttribute(chr, "perks.freepoints_ship")) chr.perks.freepoints_ship = 0;

	if (sti(chr.perks.freepoints_self) > 0 || sti(chr.perks.freepoints_ship) > 0)
	{
		chr.perks.freepoints_self = 0;
		chr.perks.freepoints_ship = 0;
		LAi_NPC_EquipPerk(chr, "fantom");
		SetCharacterPerk(chr, "Energaiser"); 
	}
}





void PGG_UpdateEquip(ref chr)
{
	ref rShip;
	int aShips[20];
	int i, n, iClass, iType;
	bool bOk, bShipNotUsed;
	string blade;
	string sBullet, sGunPowder;




	iType = sti(chr.Ship.Type);
	bShipNotUsed = (iType == SHIP_NOTUSED);

	if (!bShipNotUsed) rShip = GetRealShip(iType);
	iClass = PGG_GetAvailableShipClass(chr);

	bOk = !bShipNotUsed && CheckAttribute(rShip, "Class") && (sti(rShip.Class) > iClass);
	if (bShipNotUsed || bOk)
	{
		n = 0;
		for (i = 0; i < SHIP_LINESHIP; i++)
		{
			if (CheckAttribute(&ShipsTypes[i], "Class") && sti(ShipsTypes[i].Class) == iClass) 
			{
				aShips[n] = i;
				n++;
			}
		}

		if (n != 0)
		{
			bOk = false;
			
			if (!bShipNotUsed) 
			{
				if (rand(100) < makeint(10*MOD_SKILL_ENEMY_RATE/2)) bOk = true;
			}
			
			else
			{
				bOk = true;
			}
			if (bOk)
			{
				i = rand(n-1);
				iType = aShips[i];
				i = sti(ShipsTypes[iType].Price);

				if (sti(chr.Money) > i)
				{
					PGG_DebugLog(chr.id + " Changed ship");
					chr.Ship.Type = GenerateShipExt(iType, rand(1), chr);
					SetBaseShipData(chr);
					if (!CheckAttribute(chr, "Ship.Name")) SetRandomNameToShip(chr);
					PGG_UpdateShipEquip(chr);

					PGG_AddMoneyToCharacter(chr, -i);
					chr.PGGAi.OwnShip = true;
				}
			}
		}
	}




	if (rand(100) < 5)
	{
		DeleteAttribute(chr, "equip");
		
		blade = FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE);
		while(blade != "")
		{
			TakeItemFromCharacter(chr, blade);
			blade = FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE);
		}

		blade = LAi_NPC_EquipBladeSelection(chr);
		GiveItem2Character(chr, blade);
		EquipCharacterByItem(chr, blade);

		if(rand(1000) < MOD_SKILL_ENEMY_RATE*100)
		{
			TakeNItems(chr, "potion1", rand(makeint(sti(chr.rank)/2 + 0.5))); 
		}

		if(rand(1000) < MOD_SKILL_ENEMY_RATE * sti(chr.rank) * 8)
		{
			
			blade = FindCharacterItemByGroup(chr, GUN_ITEM_TYPE);
			while(blade != "")
			{
				TakeItemFromCharacter(chr, blade);
				blade = FindCharacterItemByGroup(chr, GUN_ITEM_TYPE);
			}

			if(rand(100) < 50)
			{
				GiveItem2Character(chr, "pistol1");
				EquipCharacterByItem(chr, "pistol1");
				sBullet = "bullet";
			}
			else
			{
				if(rand(100) < 50)
				{
					GiveItem2Character(chr, "pistol2");
					EquipCharacterByItem(chr, "pistol2");
					sBullet = "grapeshot";
				}
				else
				{
					if(rand(100) < 50)
					{
						GiveItem2Character(chr, "pistol5");
						EquipCharacterByItem(chr, "pistol5");
						sBullet = "bullet";
					}
					else
					{
						if(rand(100) < 70)
    					{
    						GiveItem2Character(chr, "pistol3");
    						EquipCharacterByItem(chr, "pistol3");
							sBullet = "grapeshot";
    					}
						else
						{
							if(rand(100) < 80)
        					{
        						GiveItem2Character(chr, "pistol6");
        						EquipCharacterByItem(chr, "pistol6");
								sBullet = "bullet";
        					}
							else
							{
								if (sti(chr.rank) > 9) 
								{
									GiveItem2Character(chr, "pistol4");
            						EquipCharacterByItem(chr, "pistol4");
									sBullet = "bullet";
        						}
        					}
    					}
					}
				}
			}
			if (GetCharacterItem(chr, sBullet) < 10)
			{
				TakeNItems(chr, sBullet, 5 + rand(15));
			}
			LAi_SetCharacterUseBullet(chr, sBullet);
			sGunPowder = LAi_GetCharacterGunpowderType(chr);
			if(sGunPowder != "")
			{
				if(GetCharacterItem(chr, sGunPowder) < 10)
				{
					AddItems(chr, sGunPowder, 5 + rand(15));
				}
			}	
		}
	}
}



string GetEquipedBladeType(ref chr)
{
	string sBlade = GetCharacterEquipByGroup(chr, BLADE_ITEM_TYPE);
	if (sBlade != "")
	{
		ref rItm = ItemsFromID(sBlade);
		return rItm.FencingType;
	}
	return SKILL_FENCING;
}


void PGG_UpdateShipEquip(ref chr)
{
	if (sti(chr.Ship.Type) == SHIP_NOTUSED) return;

	ref refTown, chref;
	string curTown;

	ProcessHullRepair(chr, 100.0);
	ProcessSailRepair(chr, 100.0);
	SetCrewQuantityFull(chr);
	
	if (chr.HeroParam.HeroType == "HeroType_2") 
	{
		Fantom_SetCannons(chr, "trade");
		Fantom_SetBalls(chr, "trade");
		Fantom_SetGoods(chr, "trade");
	}
	else 
	{
		Fantom_SetCannons(chr, "pirate");
		Fantom_SetBalls(chr, "pirate");
		Fantom_SetGoods(chr, "pirate");
	}

	curTown = chr.PGGAi.location.town;
	if (curTown != "")
	{
		if (rand(5) == 2)   
		{
			PGG_DebugLog("PGG ����� �������� � ������ " + curTown);
			refTown = GetColonyByIndex(FindColony(curTown));
			SetCrewQuantity(refTown, 0);
			chref = CharacterFromID(curTown + "_tavernkeeper");
			SaveCurrentNpcQuestDateParam(chref, "CrewHired");
			chref.CrewHired.PGGId = chr.id;

			AddRemoveGoodsInStore(curTown, GOOD_BALLS, makeint(195*1.4 + rand(20)), false);
			AddRemoveGoodsInStore(curTown, GOOD_BOMBS, makeint(60*1.4 + rand(40)), false);
			AddRemoveGoodsInStore(curTown, GOOD_KNIPPELS, makeint(95*1.4 + rand(20)), false);
			AddRemoveGoodsInStore(curTown, GOOD_GRAPES, makeint(75*1.4 + rand(20)), false);

			AddRemoveGoodsInStore(curTown, GOOD_POWDER, makeint(350*1.4 + rand(60)), false);
			AddRemoveGoodsInStore(curTown, GOOD_SAILCLOTH, makeint(5*1.4 + rand(20)), false);
			AddRemoveGoodsInStore(curTown, GOOD_PLANKS, makeint(10*1.4 + rand(40)), false);

			AddRemoveGoodsInStore(curTown, GOOD_FOOD, makeint(8*1.4 + rand(50)), false);
			AddRemoveGoodsInStore(curTown, GOOD_WEAPON, makeint(6*1.4 + rand(25)), false);
			AddRemoveGoodsInStore(curTown, GOOD_RUM, makeint(4*1.4 + rand(20)), false);
			AddRemoveGoodsInStore(curTown, GOOD_MEDICAMENT, makeint(4*1.4 + rand(25)), false);
		}
	}
}


void AddRemoveGoodsInStore(string _town, int _tradeGoods, int _quantityGoods, bool toAdd)
{
	int iTest;
	ref rStore;
	string sGoodName;
	
	iTest = FindColony(_town);
	if (iTest != -1)
	{
		rStore = GetColonyByIndex(iTest);
		iTest = sti(rStore.StoreNum);
		makeref(rStore, stores[iTest]);

		sGoodName = Goods[_tradeGoods].Name;
		iTest = sti(rStore.Goods.(sGoodName).Quantity);
		if (toAdd) 
		{
			iTest += _quantityGoods;
		}
		else 
		{
			iTest -= _quantityGoods;
		}
		if (iTest < 0) iTest = 0;
		rStore.Goods.(sGoodName).Quantity = iTest;
	}
}





string PGG_FindTargetTown(ref chr)
{
	int iRnd, iNum, iMin, iMax;
	aref arDest;
	string sAttr;
	string sCurTown = chr.PGGAi.location.town;

	makearef(arDest, NullCharacter.TravelMap.(sCurTown));
	iNum = GetAttributesNum(arDest);
	iRnd = rand(iNum-1);
	sAttr = "t" + iRnd;

	if (iRnd == -1)
	{
		trace("ERROR: <PsHero.c>: Can't find travel path from " + sCurTown);
		sAttr = "t0";
	}
	
	while (arDest.(sAttr).town == "")
	{
		sAttr = "t" + rand(iNum-1);
	}

	chr.PGGAi.Task.Target = arDest.(sAttr).town;
	iMin = sti(arDest.(sAttr).town.days.min);
	iMax = sti(arDest.(sAttr).town.days.max);
	chr.PGGAi.Task.Target.days = iMin + rand(iMax-iMin);
	
	return arDest.(sAttr).town;
}


string PGG_FindRandomTownByNation(int _nation)
{
	int i, n;
	string sTowns[MAX_COLONIES];
	n = 0;
	for (i = 0; i < MAX_COLONIES; i++)
	{
		if (sti(Colonies[i].nation) == _nation && Colonies[i].from_sea != "" && Colonies[i].id != "LostShipsCity") 
		{
			sTowns[n] = Colonies[i].id;
			n++;
		}
	}

	if (n == 0)
	{
		trace("ERROR: <PsHero.c>: Can't find any town for nation: " + _nation + " Use default.");
		return "Bridgetown";
	}
	return sTowns[rand(n-1)];
}


void PGG_TavernCheckIsPGGHere()
{
	ref chr;
	int i;
	for (i = 1; i <= PsHeroQty; i++)
	{
		chr = CharacterFromID("PsHero_" + i);
		if (findsubstr(pchar.location, chr.PGGAi.location.town, 0) != -1 && !LAi_IsDead(chr) && chr.PGGAi.location != "Dead") 
		{
			
			if (!CheckAttribute(pchar, "GenQuest.PGG_Quest") && PGG_CheckForQuestOffer(chr)) continue;
			
			if (rand(3) == 1)
			{
				PGG_PlaceCharacter2Tavern(chr, true);
				PGG_DebugLog("PGG " + chr.id + " in tavern");
			}
			else
			{
				PGG_PlaceCharacter2Tavern(chr, false);
			}
		}
	}
}


void PGG_PlaceCharacter2Tavern(ref chr, bool _bSet)
{
	int n = 0;
	string sTemp;

	if (_bSet)
	{
		sTemp = PlaceCharacter(chr, "sit", "random_free");
		n = 0;
		while (findsubstr(sTemp, "sit_front" , 0) != -1 && n < 50)
		{    
			sTemp = PlaceCharacter(chr, "sit", "random_free");
			n++;
		}
		LAi_SetSitType(chr);
	}
	else
	{
		ChangeCharacterAddressGroup(chr, "None", "", "");
		LAi_SetWarriorType(chr);
	}
}




int CheckFreeServiceForNPC(ref NPChar, string ServiceType)
{
	ref chr;
	for (int i = 1; i <= PsHeroQty; i++)
	{
		chr = CharacterFromID("PsHero_" + i);
		if (chr.PGGAi.location == "land" && chr.PGGAi.location.town == NPChar.City)
		{
			if (CheckAttribute(chr, "PGGAi.LockService") && chr.PGGAi.LockService == ServiceType) return sti(chr.index);
		}
		if (CheckAttribute(chr, "PGGAi.location.town.back") && chr.PGGAi.location.town.back == NPChar.City)
		{
			if (CheckAttribute(chr, "PGGAi.LockService") && chr.PGGAi.LockService == ServiceType) return sti(chr.index);
		}
	}
	return -1;
}


int CheckAvailableTaskForNPC(ref NPChar, string PGGTask)
{
	ref chr;
	for (int i = 1; i <= PsHeroQty; i++)
	{
		chr = CharacterFromID("PsHero_" + i);
		if (chr.PGGAi.location == "land" && chr.PGGAi.location.town == NPChar.City)
		{
			if (CheckAttribute (chr, "PGGAi.Task") && chr.PGGAi.Task == PGGTask) return sti(chr.index);
		}
	}
	return -1;
}


int PGG_GetAvailableShipClass(ref chr)
{
	int retVal = 7;
	int iSkill = sti(chr.skill.Sailing);

	if (iSkill > 0) retVal = 6;
	if (iSkill > 24) retVal = 5;
	if (iSkill > 39) retVal = 4;
	if (iSkill > 64) retVal = 3;
	if (iSkill > 79) retVal = 2;
	if (iSkill > 94) retVal = 1;

	return retVal;
}





int PGG_ChangeRelation2Character(ref pgg, ref chr, int _addValue)
{
	int curRel = 0;
	string chrID = chr.id;
	if (CheckAttribute(pgg, "PGGAi.relations." + chrID)) 
	{
		curRel = sti(pgg.PGGAi.relations.(chrID));
	}
	
	curRel += _addValue;
	if (curRel > 100) curRel = 100;
	if (curRel < 0) curRel = 0;

	PGG_DebugLog(pgg.id + " changed relation to " + chr.id + " " + _addValue);
	pgg.PGGAi.relations.(chrID) = curRel;
	return curRel;
}



int PGG_ChangeRelation2MainCharacter(ref pgg, int _addValue)
{
	return PGG_ChangeRelation2Character(pgg, GetMainCharacter(), _addValue);
}


void PGG_SetRelation2OtherAsNormal(ref pgg)
{
	ref chr;
	string chrID;
	for (int i = 1; i <= PsHeroQty; i++)
	{
		chr = CharacterFromID("PsHero_" + i);
		if (chr.id != pgg.id)
		{
			chrID = chr.id;
			pgg.PGGAi.relations.(chrID) = 50;
		}
	}
	chr = GetMainCharacter();
	chrId = chr.id;
	pgg.PGGAi.relations.(chrID) = 50;
}





void PGG_AddRumour(ref chr, string _idTmpl)
{
	int iCol;
	
	if (_idTmpl != PGG_TASK_WAITINTAVERN && _idTmpl != PGG_TASK_WORKONMAYOR &&
		_idTmpl != PGG_TASK_SAILTOISLAND && _idTmpl != PGG_TASK_WORKONSTORE &&
		_idTmpl != PGG_TASK_WORKWITHCONTRA) return;

	
	iCol = FindColony(chr.PGGAi.location.town);
	if (iCol != -1 && sti(Colonies[iCol].nation) == PIRATE) return;

	
	if (_idTmpl == PGG_TASK_SAILTOISLAND || _idTmpl == PGG_TASK_WORKONSTORE || _idTmpl == PGG_TASK_WAITINTAVERN)
	{
		if (rand(10) != 1) return;
	}

	pchar.questTemp.PGG_Rumour = chr.index;
	AddTemplRumour(_idTmpl, id_counter+1);
	DeleteAttribute(pchar, "questTemp.PGG_Rumour");
}


void PGG_OnInit_WaitInTavern(ref rTmpl)
{
	object oPrm;
	ref chr = GetCharacter(sti(pchar.questTemp.PGG_Rumour));

	oPrm.PsHero_Name = GetFullName(chr);
	oPrm.Town_Name = XI_ConvertString("Colony" + chr.PGGAi.location.town + "Gen");
	ttttstr = GetAssembledString(ttttstr, &oPrm);
}

void PGG_OnInit_WorkOnMayor(ref rTmpl)
{
	object oPrm;
	ref chr = GetCharacter(sti(pchar.questTemp.PGG_Rumour));

	oPrm.PsHero_Name = GetHeroName(sti(chr.PGGAi.HeroNum));
	ttttstr = GetAssembledString(ttttstr, &oPrm);

	rTmpl.City = chr.PGGAi.location.town;
}

void PGG_OnInit_SailToIsland(ref rTmpl)
{
	object oPrm;
	ref chr = GetCharacter(sti(pchar.questTemp.PGG_Rumour));

	oPrm.PsHero_Name = GetFullName(chr);
	oPrm.To = "�";
	if (chr.PGGAi.Task.Target == "Tortuga") oPrm.To = "��";
	oPrm.Town_Name = XI_ConvertString("Colony" + chr.PGGAi.Task.Target + "Acc");
	ttttstr = GetAssembledString(ttttstr, &oPrm);

	rTmpl.actualtime = sti(chr.PGGAi.Task.Target.days);
}

void PGG_OnInit_WorkOnStore(ref rTmpl)
{
	int iGood;
	object oPrm;
	ref chr = GetCharacter(sti(pchar.questTemp.PGG_Rumour));

	iGood = sti(chr.PGGAi.Task.Target.Goods);
	oPrm.PsHero_Name = GetFullName(chr);
	oPrm.Good = XI_ConvertString(Goods[iGood].name);
	oPrm.Town_Name = XI_ConvertString("Colony" + chr.PGGAi.Task.Target + "Acc");
	ttttstr = GetAssembledString(ttttstr, &oPrm);

	rTmpl.actualtime = sti(chr.PGGAi.Task.Target.days);
}

void PGG_OnInit_WorkWithContra(ref rTmpl)
{
	ref chr = GetCharacter(sti(pchar.questTemp.PGG_Rumour));

	rTmpl.City = chr.PGGAi.location.town;
	rTmpl.Var = sti(chr.index);
}


string PGG_Event_WorkWithContra(ref rRum)
{
	int i, iTmp;
	string sSmugglersLocation, sTemp;
	object oPrm;
	ref sld;
	ref chr = GetCharacter(sti(rRum.Var));

	sSmugglersLocation = SelectSmugglingLocation();
	if (!CheckAttribute(pchar, "quest.Contraband.Active") && !CheckAttribute(pchar, "questTemp.PGGContra") && !CheckAttribute(pchar, "GenQuest.contraTravel.active"))
	{
		chr.PGGAi.location.town.back = chr.PGGAi.location.town;
		chr.PGGAi.location.town = "none";
		pchar.questTemp.PGGContra.Loc = sSmugglersLocation;
		pchar.questTemp.PGGContra = chr.index;
		PlaceSmugglersOnShore(sSmugglersLocation);

		ChangeCharacterAddressGroup(chr, sSmugglersLocation, "smugglers", "smugglerload");
		chr.location.from_sea = sSmugglersLocation;

		
		LAi_SetWarriorType(chr);
		LAi_group_MoveCharacter(chr, "PGGTmp");


		iTmp = 3 + rand(MakeInt(MOD_SKILL_ENEMY_RATE*0.4));
		for (i = 0; i < iTmp; i++)
		{
			sTemp = "citiz_" + (rand(9)+41);
			sld = GetCharacter(NPC_GenerateCharacter("Rand_Enemy0" + i, sTemp, "man", "man", 5, PIRATE, 3, true, "hunter"));
			ChangeCharacterAddressGroup(sld, sSmugglersLocation, "goto", "goto" + (5 + i));

			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PGGTmp");
			LAi_warrior_SetCommander(sld, chr);
			SetCharacterTask_FollowCharacter(sld, chr);

			sld.Dialog.FileName = "Quest\sailors_dialog.c";
		}
		LAi_group_SetRelation("PGGTmp", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		LAi_group_SetRelation("PGGTmp", "Smugglers_1", LAI_GROUP_FRIEND);

		
		pchar.questTemp.PGGContra.Know = true;

		ReOpenQuestHeader("Gen_StrangeInfo");
		AddQuestRecord("Gen_StrangeInfo", "1");
		AddQuestUserData("Gen_StrangeInfo", "sName", GetFullName(chr));
		AddQuestUserData("Gen_StrangeInfo", "sLoc", GetConvertStr(sSmugglersLocation, "LocLables.txt"));
	}

	oPrm.PsHero_Name = GetFullName(chr);
	oPrm.ContraPlace = GetConvertStr(sSmugglersLocation, "LocLables.txt");

	return GetAssembledString(rRum.text, &oPrm);
}


void PGG_DebugLog(string _sLog)
{
	if (bBettaTestMode && bPGGLogShow)
	{
		Log_SetStringToLog(_sLog);
		trace("PGG: " + GetQuestBookDataDigit() + " " + _sLog);
	}
}





void PGG_BecomeHiredOfficer()
{
	ref chr = &Characters[sti(pchar.questTemp.HiringOfficerIDX)];

	AddPassenger(pchar, chr, false);

	chr.location = "None";
	chr.PGGAi.location.town = "Officer";
	chr.PGGAi.IsPGG = false;
	chr.Dialog.CurrentNode = "hired";
	chr.Dialog.FileName = "Enc_Officer_dialog.c";
	
	chr.PGGAi.Officer = 1;
	
	chr.Money   = 0;
	chr.Payment = true;
	

	DeleteAttribute(pchar, "questTemp.HiringOfficerIDX");
	PGG_ChangeRelation2MainCharacter(chr, 10);
	SetCharacterTask_FollowCharacter(chr, pchar);
}

void PGG_FireOfficer()
{
	ref chr = &Characters[sti(pchar.questTemp.FiringOfficerIDX)];
	CheckForReleaseOfficer(sti(pchar.questTemp.FiringOfficerIDX));

	RemovePassenger(pchar, chr);
	RemoveCharacterCompanion(pchar, chr);

	LAi_SetWarriorType(chr);

	chr.Dialog.CurrentNode = "Second time";
	chr.Dialog.TempNode = "Second time";
	chr.Dialog.FileName = "PGG_Dialog.c";
	chr.location = "none";
	chr.PGGAi.location.town = GetCurrentTown();
	chr.PGGAi.IsPGG = true;

	DeleteAttribute(Pchar, "quest.TempFiringOfficerIDX");
	PGG_ChangeRelation2MainCharacter(chr, -20);
}


void PGG_CompanionLeave(string qName)
{
	ref chr;
	chrDisableReloadToLocation = true;
	chr = &Characters[sti(pchar.questTemp.PGG_Companion_Leave.index)];
	PlaceCharacter(chr, "goto", "random_must_be_near");

	chr.Dialog.CurrentNode = "companion_leave";
	chr.Dialog.FileName = "PGG_Dialog.c";
	LAi_SetActorType(chr);
	LAi_ActorDialog(chr, pchar, "", 2.0, 0);
	DoQuestCheckDelay("OpenTheDoors", 5.0);   
}


bool PGG_CheckForQuestOffer(ref chr)
{
	bool retVal = false;
	
	if (rand(2) == 1) return retVal; 
	
	int iTst = 110 - PGG_ChangeRelation2MainCharacter(chr, 0); 
	
	if (bBettaTestMode && CheckAttribute(PChar, "PGGAlwaysQuest")) iTst = 10; 
	if (sti(chr.Ship.Type) != SHIP_NOTUSED && sti(PChar.Ship.Type) != SHIP_NOTUSED && rand(100) > iTst && CheckNPCQuestDate(chr, "QuestOffer"))
	{
		if (GetCharacterShipClass(PChar) <= 4 && GetCompanionQuantity(PChar) < COMPANION_MAX && GetCharacterShipClass(chr) <= 4 && PGG_IsQuestAvaible())
		{
			chr.PGGAi.ActiveQuest.QstNumber = 0; 
			retVal = true;
		}
	}
	SetNPCQuestDate(chr, "QuestOffer"); 
	if (retVal)
	{
		chrDisableReloadToLocation = true;
		PlaceCharacter(chr, "goto", "random_must_be_near");
        PChar.GenQuest.PGG_Quest = 1;
		chr.Dialog.CurrentNode = "quest_onStay";
		chr.PGGAi.ActiveQuest = 1;
		LAi_SetActorType(chr);
		LAi_ActorDialog(chr, pchar, "", 2.0, 0);
		DoQuestCheckDelay("OpenTheDoors", 5.0);      
	}
	return retVal;
}

bool PGG_IsQuestAvaible()
{
	string sTown;
	bool retVal = true;

	sTown = GetCurrentTown();
	if (sTown == "" || sTown == "Panama" || Colonies[FindColony(sTown)].from_sea == "" || CheckAttribute(Colonies[FindColony(sTown)], "HasNoFort")) retVal = false;
	return retVal;
}



void PGG_Q1RemoveShip(string qName)
{
	ref chr = CharacterFromID(PChar.GenQuest.PGG_Quest.PGGid);

	chr.Dialog.CurrentNode = "Second Time";
	DeleteAttribute(chr, "DeckDialogNode");

	Group_SetAddress("PGGQuest", "None", "", "");
	Group_DelCharacter("PGGQuest", chr.id);

	if (CheckAttribute(PChar, "GenQuest.PGG_Quest.Stage") && sti(PChar.GenQuest.PGG_Quest.Stage) < 2 && sti(PChar.GenQuest.PGG_Quest.Stage) >= 0)
	{
		chr.Dialog.CurrentNode = "Second Time";
		DeleteAttribute(chr, "PGGAi.ActiveQuest");
		DeleteAttribute(PChar, "GenQuest.PGG_Quest");
		PGG_ChangeRelation2MainCharacter(chr, -10);
		CloseQuestHeader("Gen_PGGQuest1");
	}
	DeleteAttribute(chr, "AlwaysFriend");
}


void PGG_Q1AfterDeckFight()
{
	ref chr, rGroup;
	string sGroup;
	sGroup = PChar.GenQuest.PGG_Quest.GrpID;

	chr = CharacterFromID(PChar.GenQuest.PGG_Quest.PGGid);
	chr.AlwaysEnemy = true;
	chr.Coastal_Captain    = true;  
	chr.Abordage.Enable = false;
	LAi_SetImmortal(chr, false);


	DelEventHandler("LAi_event_GroupKill", "PGG_Q1AfterDeckFight");
	
	DeleteAttribute(PChar, "GenQuest.PGG_Quest.GrpID");
	chrDisableReloadToLocation = false;
	if (sti(PChar.GenQuest.PGG_Quest.Stage) < 4)
	{
		AddQuestRecord("Gen_PGGQuest1", "q1_RefuseFight");
		AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("��","���"));
		AddQuestUserData("Gen_PGGQuest1", "sSex1", GetSexPhrase("��","��"));
		AddQuestUserData("Gen_PGGQuest1", "sNation", NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)));
		AddQuestUserData("Gen_PGGQuest1", "sPsName", GetFullName(chr));
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
	}
	else
	{
		if (!CheckAttribute(PChar, "GenQuest.PGG_Quest.Ok"))
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_FailNotPay");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Gen_PGGQuest1", "sSex1", GetSexPhrase("��","��"));
			AddQuestUserData("Gen_PGGQuest1", "sPsName", GetFullName(chr));
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_OkNotShare");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("","�"));
		}
	}
	DoQuestCheckDelay("hide_weapon", 2.0);

	rGroup = Group_FindOrCreateGroup("PGGQuest");
	PChar.Quest.PGGQuest1_AfterDeckFight.win_condition.l1 = "location";
	PChar.Quest.PGGQuest1_AfterDeckFight.win_condition.l1.location = rGroup.Location;
	PChar.Quest.PGGQuest1_AfterDeckFight.function = "PGG_Q1SeaFightAfterDeck";

	CloseQuestHeader("Gen_PGGQuest1");
}


void PGG_Q1SeaFightAfterDeck(string qName)
{
	string sTemp = "PGGQuest";
	Group_SetTaskAttackEx(sTemp, PLAYER_GROUP, false);
	Group_LockTask(sTemp);
	
	ref chr = CharacterFromID(PChar.GenQuest.PGG_Quest.PGGid);
	LAi_SetImmortal(chr, false);

	PChar.Quest.PGGQuest1_AfterSeaFight.win_condition.l1 = "Group_Death";
	PChar.Quest.PGGQuest1_AfterSeaFight.win_condition.l1.group = sTemp;
	PChar.Quest.PGGQuest1_AfterSeaFight.function = "PGG_Q1AfterSeaFight";

	if (sti(PChar.GenQuest.PGG_Quest.Stage) < 4)
	{
		PChar.Quest.PGGQuest1_Runaway.win_condition.l1 = "ExitFromSea";
		PChar.Quest.PGGQuest1_Runaway.function = "PGG_Q1AfterSeaFight";
	}
	else
	{
		PChar.Quest.PGGQuest1_Runaway.win_condition.l1 = "MapEnter";
		PChar.Quest.PGGQuest1_Runaway.function = "PGG_Q1AfterSeaFight";
	}
}


void PGG_Q1AfterSeaFight(string qName)
{
	ref chr;

	chr = CharacterFromID(PChar.GenQuest.PGG_Quest.PGGid);
	chr.Abordage.Enable = true;
	chr.Dialog.CurrentNode = "Second Time";
	if (CheckAttribute(chr, "Nation.Bak")) chr.Nation = chr.Nation.Bak;
	chr.PGGAi.IsPGG = true;
	chr.RebirthPhantom = true;
	if (chr.PGGAi.location.town == "none") 
	{
		chr.PGGAi.location.town = PGG_FindRandomTownByNation(sti(chr.nation));
	}

	Group_SetAddress("PGGQuest", "None", "", "");
	Group_DeleteGroup("PGGQuest");

	PChar.Quest.PGGQuest1_AfterSeaFight.Over = "yes";
	PChar.Quest.PGGQuest1_Runaway.Over = "yes";

	ChangeCharacterAddressGroup(chr, "None", "", "");

	DeleteAttribute(chr, "AlwaysEnemy");
	DeleteAttribute(chr, "Coastal_Captain");
	DeleteAttribute(chr, "PGGAi.ActiveQuest");
	DeleteAttribute(PChar, "GenQuest.PGG_Quest");
}

void PGG_Q1PlaceShipsNearIsland()
{
	ref chr;
	string sTmp, sLoc, sType;
	int i, iRnd, iNation, iLifeDay, iRank, iGoods, iSpace;

	sLoc = PChar.GenQuest.PGG_Quest.Island;
	iRank = sti(PChar.Rank);
	iGoods = sti(PChar.GenQuest.PGG_Quest.Goods);
	iNation = sti(PChar.GenQuest.PGG_Quest.Nation);
	iLifeDay = 2 + sti(PChar.GenQuest.PGG_Quest.Days);
	
	iRnd = 3 + rand(2);
	for (i = 0; i < iRnd; i++)
	{
		sTmp = "citiz_" + (i + 41);
		chr = GetCharacter(NPC_GenerateCharacter("RandQuestCap_0" + i, sTmp, "man", "man", MakeInt(iRank/2 + rand(iRank)), iNation, iLifeDay, true, "hunter"));
		chr.AlwaysSandbankManeuver = true;
		if (i < 2)
		{
			chr.Ship.Type = GenerateShipExt(13 + rand(3), 1, chr);
			SetBaseShipData(chr);
			SetCrewQuantityFull(chr);
			Fantom_SetCannons(chr, "war"); 
			Fantom_SetBalls(chr, "pirate");
			Fantom_SetGoods(chr, "war");
			SetRandomNameToShip(chr);
			SetFantomParamHunter(chr); 
			SetCaptanModelByEncType(chr, "war");
		}
		else
		{
			SetShipTypeMerchant(chr);
			iSpace = GetCharacterFreeSpace(chr, iGoods);
			iSpace = MakeInt(iSpace/2 + rand(iSpace/2));
			if (!CheckAttribute(PChar, "GenQuest.PGG_Quest.Goods.Qty")) PChar.GenQuest.PGG_Quest.Goods.Qty = 0;
			PChar.GenQuest.PGG_Quest.Goods.Qty = sti(PChar.GenQuest.PGG_Quest.Goods.Qty) + iSpace;
			Fantom_SetCharacterGoods(chr, iGoods, iSpace, 1);

			SetCaptanModelByEncType(chr, "trade");

		}
		Group_AddCharacter("PGGQuest", chr.id);
		chr.AlwaysEnemy = true;
	}
	Group_SetGroupCommander("PGGQuest", "RandQuestCap_01");
	Group_SetAddress("PGGQuest", PChar.GenQuest.PGG_Quest.Island, "Quest_Ships", "Quest_Ship_" + (3+ rand(4)));
	Group_SetTaskNone("PGGQuest");

	PChar.Quest.PGGQuest1_GroupDead.win_condition.l1 = "Group_Death";
	PChar.Quest.PGGQuest1_GroupDead.win_condition.l1.Group = "PGGQuest";
	PChar.Quest.PGGQuest1_GroupDead.function = "PGG_Q1AfterBattle";

	PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1 = "Location";
	PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1.Location = PChar.GenQuest.PGG_Quest.Island;
	PChar.Quest.PGGQuest1_CheckStartState.function = "PGG_Q1CheckStartState";
}

void PGG_Q1PGGDead(string qName)
{
	ref chr = CharacterFromID(PChar.GenQuest.PGG_Quest.PGGid);
	if (sti(PChar.GenQuest.PGG_Quest.Template)) 
	{
		if (sti(PChar.GenQuest.PGG_Quest.Stage) < 3)
		{
			Group_SetAddress("PGGQuest", "None", "", "");
			Group_DeleteGroup("PGGQuest");

			if (CheckAttribute(chr, "PGGAi.ActiveQuest"))
			{
				AddQuestRecord("Gen_PGGQuest1", "q1_PGGDeadNoShips");
			}
			else
			{
				AddQuestRecord("Gen_PGGQuest1", "q1_PGGDeadNoShips_1");
			}
			PChar.Quest.PGGQuest1_CheckStartState.Over = "yes"; 
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_PGGDeadShips");
		}
		AddQuestUserData("Gen_PGGQuest1", "sPsName", GetFullName(chr));

		PChar.Quest.PGGQuest1_GroupDead.Over = "yes";
		PChar.Quest.PGGQuest1_Time2Late.Over = "yes";
		PChar.Quest.PGGQuest1_Time2Fight.Over = "yes";

		DeleteAttribute(PChar, "GenQuest.PGG_Quest");
	}
	else
	{
		PChar.GenQuest.PGG_Quest.PGGid.Dead = 1;
		AddQuestRecord("Gen_PGGQuest1", "q1_PGGDead");
	}
	DeleteAttribute(chr, "PGGAi.ActiveQuest");
	CloseQuestHeader("Gen_PGGQuest1");
}

void PGG_Q1CheckStartState(string qName)
{
	ref chr;
	int i, n, iNum;

	PChar.GenQuest.PGG_Quest.Stage = 3;
	PChar.Quest.PGGQuest1_Time2Late.Over = "yes";
	PChar.Quest.PGGQuest1_Time2Late_01.Over = "Yes";
	PChar.Quest.PGGQuest1_Time2Late_02.Over = "Yes";

	if (sti(PChar.GenQuest.PGG_Quest.Template)) 
	{
		SetTimerCondition("PGGQuest1_Time2Fight", 0, 0, 2, false);
		PChar.Quest.PGGQuest1_Time2Fight.function = "PGG_Q1AfterBattle";
	}
	else
	{
		if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island.Shore))
		{
			DeleteAttribute(PChar, "Quest.PGGQuest1_CheckStartState.Over");
			return;
		}
		else
		{
			PGG_Q1FightOnShore();
		}
	}
	PChar.GenQuest.PGG_Quest.StartGoods = 0; 

	n = GetCompanionQuantity(PChar);
	for (i = 0; i < n; i++)
	{
		iNum = GetCompanionIndex(PChar, i);
		if (iNum != -1)
		{
			chr = GetCharacter(iNum);
			if (GetRemovable(chr))
			{
				PChar.GenQuest.PGG_Quest.StartGoods = sti(PChar.GenQuest.PGG_Quest.StartGoods) + GetCargoGoods(chr, sti(PChar.GenQuest.PGG_Quest.Goods));
			}
		}
	}
}

void PGG_Q1AfterBattle(string qName)
{
	ref chr;
	aref arOldMapPos;
	int i, n, iNum, iRnd;
	string sLoc;
	bool bLater = false;
	bool bOk = !Group_isDead("PGGQuest") && !bMapEnter;

	if (bOk || !bSeaActive)
	{
		if (IsEntity(worldMap))
		{

			bLater = true;
		}
		else
		{
			SetTimerConditionParam("PGGQuest1_Time2Fight", "PGGQuest1_Time2Fight", 0, 0, 0, MakeInt(GetHour() + 2), false);
			DeleteAttribute(PChar, "Quest.PGGQuest1_Time2Fight.Over");
			return;
		}
	}

	
	PChar.GenQuest.PGG_Quest.Goods.Taken = 0;
	n = GetCompanionQuantity(PChar);
	for (i = 0; i < n; i++)
	{
		iNum = GetCompanionIndex(PChar, i);
		if (iNum != -1)
		{
			chr = GetCharacter(iNum);
			if (GetRemovable(chr))
			{
				PChar.GenQuest.PGG_Quest.Goods.Taken = sti(PChar.GenQuest.PGG_Quest.Goods.Taken) + GetCargoGoods(chr, sti(PChar.GenQuest.PGG_Quest.Goods));
			}
		}
	}

	chr = CharacterFromID(PChar.GenQuest.PGG_Quest.PGGid);
	sLoc = PChar.GenQuest.PGG_Quest.Island.Shore;

	PChar.GenQuest.PGG_Quest.Goods.Taken = sti(PChar.GenQuest.PGG_Quest.Goods.Taken) - sti(PChar.GenQuest.PGG_Quest.StartGoods); 
	PChar.GenQuest.PGG_Quest.GrpLoc = Island_FindNearestLocator2PChar("Quest_Ships");
	PChar.GenQuest.PGG_Quest.GrpLocation = PChar.location;

	if (!bLater)
	{
		if (isLocationFreeForQuests(sLoc))
		{
			PChar.location.from_sea = sLoc;
			Locations[FindLocation(sLoc)].DisableEncounters = true;
			DoReloadFromSeaToLocation(sLoc, "reload", "sea");
		}
		else
		{
			MakeCloneShipDeck(pchar, true); 
			DoReloadFromSeaToLocation("Ship_deck", "goto", "goto5");
   			pchar.quest.Munity = "";
			sLoc = "Ship_deck";
		}
	}
	else
	{
		makearef(arOldMapPos, worldMap.old);
		WdmPrepareMapForAbordage(arOldMapPos);
		MakeCloneShipDeck(pchar, true); 
		LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], true);
		DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto5");
		ReloadFromWMtoL_complete();
		LAi_LockFightMode(pchar, true);
		PChar.Quest.Munity = "";
		sLoc = "Ship_deck";
	}

	PChar.Quest.PGGQuest1_LocationLoaded.win_condition.l1 = "Location";
	PChar.Quest.PGGQuest1_LocationLoaded.win_condition.l1.Location = sLoc;
	PChar.Quest.PGGQuest1_LocationLoaded.function = "PGG_Q1LocationLoaded";

	PChar.Quest.PGGQuest1_PGGDead.Over = "yes";
	PChar.Quest.PGGQuest1_GroupDead.Over = "yes";
	PChar.Quest.PGGQuest1_Time2Fight.Over = "yes";
	PChar.Quest.PGGQuest1_Time2Late_01.Over = "Yes";
	PChar.Quest.PGGQuest1_Time2Late_02.Over = "Yes";

	chrDisableReloadToLocation = true;
}
void PGG_Q1LocationLoaded(string qName)
{
	ref chr;
	int i, iRnd;
	string attrName;

	Group_SetAddress("PGGQuest", "", "", "");
	chr = CharacterFromID(PChar.GenQuest.PGG_Quest.PGGid);
	chr.Dialog.CurrentNode = "Quest_1_CheckResult";
	LAi_SetImmortal(chr, true);

	PlaceCharacter(chr, "goto", "random_must_be_near");
	LAi_SetActorType(chr);
	LAi_ActorDialog(chr, pchar, "", 2.0, 0);

	iRnd = 3 + rand(2);
	PChar.GenQuest.PGG_Quest.GrpID.Qty = iRnd;
	chr.location = pchar.location;
	for (i = 1; i < iRnd; i++)
	{
		attrName = "citiz_" + (i + 40);
		chr = GetCharacter(NPC_GenerateCharacter(attrName, attrName, "man", "man", 15, PIRATE, 0, true, "marginal"));
		chr.dialog.Filename = "Quest\sailors_dialog.c";
		LAi_SetWarriorType(chr);
		LAi_SetLoginTime(chr, 0.0, 24.0);
		LAi_SetHP(chr, 100.0, 100.0);
		ChangeCharacterAddressGroup(chr, PChar.location, "goto", "goto"+i);
		LAi_group_MoveCharacter(chr, "PGGTmp");
	}
	LAi_group_SetRelation("PGGTmp", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);	

	PChar.GenQuest.PGG_Quest.GrpID = "PGGTmp";
	PChar.location.from_sea = PChar.location;
}

void PGG_Q1EndClear(string qName)
{
	ref chr = CharacterFromID(PChar.GenQuest.PGG_Quest.PGGid);

	chr.Dialog.CurrentNode = "Second Time";
	chr.PGGAi.IsPGG = true;
	chr.RebirthPhantom = true;
	chr.Nation = chr.Nation.Bak;
	LAi_SetImmortal(chr, false);
	LAi_SetWarriorType(chr);
    SetCharacterRemovable(chr, true);
     
	PChar.Quest.PGGQuest1_EndExitSea.Over = "Yes";
	PChar.Quest.PGGQuest1_EndExitLoc.Over = "Yes";
	PChar.Quest.PGGQuest1_Time2Late_01.Over = "Yes";
	PChar.Quest.PGGQuest1_Time2Late_02.Over = "Yes";

	LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);

	DeleteAttribute(chr, "PGGAi.ActiveQuest");
	DeleteAttribute(chr, "AlwaysFriend");
	DeleteAttribute(PChar, "GenQuest.PGG_Quest");

	chr.PGGAi.location.town = PGG_FindRandomTownByNation(sti(chr.nation));
	ChangeCharacterAddressGroup(chr, "None", "", "");
	LAi_group_Delete("PGGTmp"); 
}

void PGG_Q1Time2Late(string qName)
{
	int i;
	string attrName;
	ref chr;
	aref arOldMapPos;

	chr = CharacterFromID(PChar.GenQuest.PGG_Quest.PGGid);
	if (!bQuestCheckProcessFreeze)
	{
		if (IsEntity(worldMap))
		{
			PChar.Quest.PGGQuest1_Time2Late_01.over = "yes"; 
			PChar.Quest.PGGQuest1_Time2Late_02.over = "yes";
	       
			makearef(arOldMapPos, worldMap.old);
			WdmPrepareMapForAbordage(arOldMapPos);
			MakeCloneShipDeck(pchar, true); 
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], true);
			DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto7");
			
			LAi_LockFightMode(pchar, true);
	        
			ChangeCharacterAddressGroup(chr, "Ship_deck", "goto", "goto2");
			LAi_group_MoveCharacter(chr, "GroupDeck");
			chr.Dialog.CurrentNode = "Quest_1_Time2Late";
			
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "", 3.0, 0); 
	        
			
			for (i=1; i<5; i++)
			{
				attrName = "citiz_" + (i + 40);
				Log_TestInfo(attrName);
				chr = GetCharacter(NPC_GenerateCharacter(attrName, attrName, "man", "man", 15, PIRATE, 1, true, "marginal"));
				SetFantomParam(chr);
				chr.dialog.Filename = "Quest\sailors_dialog.c";
				LAi_SetWarriorType(chr);
				LAi_SetLoginTime(chr, 0.0, 24.0);
				LAi_SetHP(chr, 100.0, 100.0);
				ChangeCharacterAddressGroup(chr, "Ship_deck", "goto", "goto"+(i+2));
				LAi_group_MoveCharacter(chr, "GroupDeck");
			}
    		pchar.quest.Munity = "";  
		}
		else
		{
			if (isLocationFreeForQuests(PChar.location) && !bSeaActive && !LAi_grp_alarmactive) 
			{
				if (PlaceCharacter(chr, "goto", "random_must_be_near") != "")
				{
					PChar.Quest.PGGQuest1_Time2Late_01.over = "yes";
					PChar.Quest.PGGQuest1_Time2Late_02.over = "yes";
	
					chrDisableReloadToLocation = true;

					chr.Dialog.CurrentNode = "Quest_1_Time2Late";
					LAi_SetActorType(chr);
					LAi_ActorDialog(chr, pchar, "", 2.0, 0);
				}
				else
				{
					PChar.Quest.PGGQuest1_Time2Late_02.win_condition.l1 = "ExitFromLocation";
					PChar.Quest.PGGQuest1_Time2Late_02.win_condition.l1.Location = PChar.location;
					PChar.Quest.PGGQuest1_Time2Late_02.function = "PGG_Q1Time2Late";
					DeleteAttribute(PChar, "Quest.PGGQuest1_Time2Late_02.Over");
				}
			}
			else
			{
				PChar.Quest.PGGQuest1_Time2Late_02.win_condition.l1 = "ExitFromLocation";
				PChar.Quest.PGGQuest1_Time2Late_02.win_condition.l1.Location = PChar.location;
				PChar.Quest.PGGQuest1_Time2Late_02.function = "PGG_Q1Time2Late";
				DeleteAttribute(PChar, "Quest.PGGQuest1_Time2Late_02.Over");
			}
		}
	}
	else
	{
		
		PChar.Quest.PGGQuest1_Time2Late_01.win_condition.l1 = "MapEnter";
		PChar.Quest.PGGQuest1_Time2Late_01.function = "PGG_Q1Time2Late";
	}
}

void PGG_Q1FightOnShore()
{
	ref chr;
	string attrName, sLoc;
	int i, iRnd, iNation;

	sLoc = PChar.GenQuest.PGG_Quest.Island.Shore;
	iNation = sti(PChar.GenQuest.PGG_Quest.Nation);

	chrDisableReloadToLocation = true;
	
	if (!CheckAttribute(PChar, "GenQuest.PGG_Quest.PGGid.Dead"))
	{
		chr = CharacterFromID(PChar.GenQuest.PGG_Quest.PGGid);
		PlaceCharacter(chr, "goto", "random_must_be_near");
		LAi_SetWarriorType(chr);
		LAi_SetImmortal(chr, true);
		LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);

		iRnd = 9 - rand(MakeInt(MOD_SKILL_ENEMY_RATE/2));
		PChar.GenQuest.PGG_Quest.GrpID.Qty = iRnd;
		PChar.GenQuestFort.FarLocator = false;
		for (i = 1; i < iRnd; i++)
		{
			SetFantomDefenceForts("goto", "", PIRATE, LAI_GROUP_PLAYER);
		}
		Pchar.GenQuestFort.FarLocator = true;	
	}

	
	iRnd = 10 + rand(MakeInt(MOD_SKILL_ENEMY_RATE/2));
	Pchar.GenQuestFort.FarLocator = true;
	sLoc = LAi_FindNPCLocator("officers");	
	for (i = 1; i < iRnd; i++)
	{
		chr = SetFantomDefenceForts("officers", sLoc, iNation, "PGGTmp");
		chr.id = "pirate_" + i;
	}
	
	LAi_group_SetHearRadius("PGGTmp", 100.0);
	LAi_group_FightGroupsEx("PGGTmp", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
	LAi_group_SetRelation("PGGTmp", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);	

	LAi_group_SetCheck("PGGTmp", "PGG_Q1AfterShoreFight");
	LAi_SetFightMode(pchar, true);
	PChar.GenQuest.PGG_Quest.GrpID = "PGGTmp";
}

void PGG_Q1AfterShoreFight()
{
	ref chr, rGroup;
	string sGroup;
	sGroup = PChar.GenQuest.PGG_Quest.GrpID;

	DoQuestCheckDelay("hide_weapon", 2.0);

	
	PChar.GenQuest.PGG_Quest.Goods.Taken = 500 + rand(500) + MakeInt(GetSquadronFreeSpace(PChar, sti(PChar.GenQuest.PGG_Quest.Goods)) / (3 + rand(2)))
	chr = CharacterFromID(PChar.GenQuest.PGG_Quest.PGGid);
	if (!CheckAttribute(PChar, "GenQuest.PGG_Quest.PGGid.Dead"))
	{
		PChar.Quest.PGGQuest1_PGGDead.Over = "yes";
		chr.Dialog.CurrentNode = "Quest_1_SharePrise";
		LAi_SetActorType(chr);
		LAi_ActorDialog(chr, pchar, "", 2.0, 0);
	}
	else
	{
		chrDisableReloadToLocation = false;
		SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), sti(PChar.GenQuest.PGG_Quest.Goods.Taken));
	}
}

void PGG_AddMoneyToCharacter(ref chr, int iMoney)
{
	int Norm = 100000 + sti(chr.rank)*10000;
	AddMoneyToCharacter(chr, iMoney);
	if (sti(chr.Money) > Norm) chr.Money = Norm;
}
