

bool Ship_AutoAbordage(ref rCharacter, float fMinEnemyDistance)
{
    int     i;
    float	fDistance;
    bool    bSuccess = false;

    
    if (fMinEnemyDistance < 70)
    {
	    int   bGrapplingProfessional  = sti(rCharacter.TmpPerks.GrapplingProfessional);
        float fOurGrappling           = 10 * stf(rCharacter.TmpSkill.Grappling);
	    float fOurMaxAbordageDistance = 15 + 7 * (bGrapplingProfessional + fOurGrappling);

		
		if (CheckAttribute(rCharacter, "Tasks.CanBoarding") && !sti(rCharacter.Tasks.CanBoarding)) return false;
		
		
		if (sti(RealShips[sti(rCharacter.ship.type)].basetype) == SHIP_POLACRE_QUEST && rCharacter.id == "Ignasio") return false;
		if (rCharacter.id == "Terrax") return false;

		if (fMinEnemyDistance > fOurMaxAbordageDistance) return bSuccess;
	    if (!CheckAttribute(rCharacter, "SeaAI.Task.Target")) return bSuccess;

        ref  rShipCharacter = GetCharacter(sti(rCharacter.SeaAI.Task.Target));
        if (LAi_IsDead(rShipCharacter)) return bSuccess;

        if (Ship_GetDistance2D(rCharacter, rShipCharacter) > 90) return bSuccess;

	    int  iRelation = SeaAI_GetRelation(sti(rCharacter.index), sti(rShipCharacter.index));

	    if (!Character_IsAbordageEnable(rShipCharacter) || sti(rShipCharacter.index) == GetMainCharacterIndex()) return bSuccess;

		if (iRelation != RELATION_ENEMY) return bSuccess;
		
		if (sti(rCharacter.Ship.Crew.Quantity) < (stf(rShipCharacter.Ship.Crew.Quantity) * 0.6)) return bSuccess;

	    float fOurHP                = Ship_GetHP(rCharacter);
	    float fOurFencing           = stf(rCharacter.TmpSkill.Grappling); 
	    float fOurCrewFencing       = (0.1 + fOurFencing * stf(rCharacter.Ship.Crew.Quantity)*GetCrewExp(rCharacter, "Soldiers"));

	    if (IsCompanion(rCharacter))
	    {           
	       fOurCrewFencing       = (0.1 + fOurFencing * GetWeaponCrew(rCharacter, sti(rCharacter.Ship.Crew.Quantity))*GetCrewExp(rCharacter, "Soldiers"));
	    }
	    float fMorale  = GetCharacterCrewMorale(rCharacter); 
        fOurCrewFencing = fOurCrewFencing * (0.5 + fMorale / MORALE_MAX);

	    float fEnHP                = Ship_GetHP(rShipCharacter);
	    float fEnFencing           = stf(rShipCharacter.TmpSkill.Grappling); 
	    float fEnCrewFencing       = (0.1 + fEnFencing * stf(rShipCharacter.Ship.Crew.Quantity) *GetCrewExp(rShipCharacter, "Soldiers"));

	    if (IsCompanion(rShipCharacter))
	    {   
	       fEnCrewFencing       = (0.1 + fEnFencing * GetWeaponCrew(rShipCharacter, sti(rShipCharacter.Ship.Crew.Quantity))*GetCrewExp(rShipCharacter, "Soldiers") );
	    }
        fMorale  = GetCharacterCrewMorale(rShipCharacter); 
        fEnCrewFencing = fEnCrewFencing * (0.5 + fMorale / MORALE_MAX);
        
		bool bAngleTest = true;
        int deadCrew = 0;
		if (bGrapplingProfessional || bAngleTest)
		{
			bSuccess = true;
			PlayStereoSound("Interface\abordage.wav");

            if (fOurCrewFencing >= fEnCrewFencing)
            { 
                if (IsCompanion(rShipCharacter))
			    {
			        Log_SetStringToLog("Our ship " + rShipCharacter.Ship.Name + " was boarded ");
			    }
			    else
			    {
			        Log_SetStringToLog("" + rShipCharacter.Ship.Name + " was boarded ");
					trace("" + rShipCharacter.Ship.Name + " was boarded ");
			    }
			    deadCrew = sti(rCharacter.Ship.Crew.Quantity) * fEnCrewFencing / (fOurCrewFencing*1.8);
				if (IsCompanion(rShipCharacter))
				{
					Statistic_AddValue(pchar, "Sailors_dead", deadCrew);
					Achievment_SetStat(pchar, 21, deadCrew);
				}
			    SetCrewQuantity(rCharacter, makeint(sti(rCharacter.Ship.Crew.Quantity) - deadCrew));
			    if (IsCompanion(rCharacter))
			    {
			        RemoveCharacterGoodsSelf(rCharacter, GOOD_WEAPON, deadCrew);
			    }
				
				if (CheckChanceOfBetterShip(rCharacter, rShipCharacter))
				{
					SeaExchangeCharactersShips(rCharacter, rShipCharacter, true, true);
				}
				DoTakeAbordageGoods(rCharacter, rShipCharacter);
				if (IsCompanion(rCharacter)) LeaveAbordageShipDrift(sti(rShipCharacter.index), sti(rCharacter.index));
			    else ShipDead(sti(rShipCharacter.index),KILL_BY_ABORDAGE,sti(rCharacter.index));
				
			    Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), nMainCharacterIndex);
            }
            else
            { 
                if (IsCompanion(rCharacter))
			    {
			        Log_SetStringToLog("Our ship " + rCharacter.Ship.Name + " has lost the fight ");
					Statistic_AddValue(pchar, "Sailors_dead", sti(rCharacter.Ship.Crew.Quantity));
					Achievment_SetStat(pchar, 21, sti(rCharacter.Ship.Crew.Quantity));
			    }
			    else
			    {
			        Log_SetStringToLog("" + rCharacter.Ship.Name + " lost the fight ");
					trace("" + rCharacter.Ship.Name + " lost the fight ");
			    }
			    deadCrew = sti(rShipCharacter.Ship.Crew.Quantity) * fOurCrewFencing/ (fEnCrewFencing*1.8);
			    SetCrewQuantity(rShipCharacter, makeint(sti(rShipCharacter.Ship.Crew.Quantity) - deadCrew));
			    if (IsCompanion(rShipCharacter))
			    {
			        RemoveCharacterGoodsSelf(rShipCharacter, GOOD_WEAPON, deadCrew);
			    }
				
				if (CheckChanceOfBetterShip(rShipCharacter, rCharacter))
				{
					SeaExchangeCharactersShips(rShipCharacter, rCharacter, true, true);
				}
				DoTakeAbordageGoods(rShipCharacter, rCharacter);
				if (IsCompanion(rShipCharacter)) LeaveAbordageShipDrift(sti(rCharacter.index), sti(rShipCharacter.index));
			    else ShipDead(sti(rCharacter.index),KILL_BY_ABORDAGE,sti(rShipCharacter.index));
				
            }  
		}
	}
    return bSuccess;
}




void SeaExchangeCharactersShips(ref rOneChr, ref rSecChr, bool _showLog, bool _swapCargo)
{
	int     nMyCrew;
	aref    arCargoOne, arCargoSec;
	object	oTmp;

	
	nMyCrew = GetCrewQuantity(rOneChr);
    float fMor = stf(rOneChr.ship.crew.morale);
    makearef(arCargoOne, rOneChr.Ship.Crew.Exp);
	CopyAttributes(&oTmp, arCargoOne); 
	
	
	SeaAI_SwapShipsAttributes(rOneChr, rSecChr);
	SeaAI_SwapShipAfterAbordage(rOneChr, rSecChr);
	
	SetCrewQuantity(rOneChr, nMyCrew);
	SetCrewQuantity(rSecChr, 0);
    rOneChr.ship.crew.morale = fMor;
    
    makearef(arCargoOne, rOneChr.Ship.Crew.Exp);
	DeleteAttribute(arCargoOne,"");
	CopyAttributes(arCargoOne,&oTmp);
	
	
	if (_swapCargo)
	{
		oTmp.Ship.Cargo = "";
		makearef(arCargoOne, rOneChr.Ship.Cargo);
		makearef(arCargoSec, oTmp.Ship.Cargo);

		CopyAttributes(arCargoSec, arCargoOne);
		DeleteAttribute(arCargoOne,"");

		makearef(arCargoSec, rSecChr.Ship.Cargo);
		CopyAttributes(arCargoOne,arCargoSec);
		DeleteAttribute(arCargoSec,"");

		makearef(arCargoOne, oTmp.Ship.Cargo);
		CopyAttributes(arCargoSec, arCargoOne);

		
		RefreshBattleInterface();
		DoQuestCheckDelay("NationUpdate", 1.0);
	}
	if (_showLog)
	{
		Log_SetStringToLog(GetFullName(rOneChr) + " changed one's ship to " +
						XI_ConvertString(RealShips[sti(rOneChr.Ship.Type)].BaseName) + " " + rOneChr.Ship.Name + ".");
		trace(GetFullName(rOneChr) + " changed one's ship to " +
						XI_ConvertString(RealShips[sti(rOneChr.Ship.Type)].BaseName) + " " + rOneChr.Ship.Name + ".");				
	}
}

bool CheckChanceOfBetterShip(ref rChar, ref rTryChar)
{
	float fChance;
	ref  rShip;
	ref  rTryShip;

	rShip    = GetRealShip(sti(rChar.Ship.Type));
	rTryShip = GetRealShip(sti(rTryChar.Ship.Type));

	
	if (CheckAttribute(rChar, "Tasks.CanChangeShipAfterBoarding") && !sti(rChar.Tasks.CanChangeShipAfterBoarding)) return false;
    if (CheckAttribute(rChar, "Tasks.CanBoarding") && !sti(rChar.Tasks.CanBoarding)) return false;
	
	
	if (sti(RealShips[sti(rCharacter.ship.type)].basetype) == SHIP_POLACRE_QUEST && rCharacter.id == "Ignasio") return false;
	if (rCharacter.id == "Terrax") return false;
    
	
	if (sti(rChar.Ship.Cannons.Type) == CANNON_TYPE_CANNON_LBS48 || sti(rTryChar.Ship.Cannons.Type) == CANNON_TYPE_CANNON_LBS48) return false;

	fChance = (stf(rShip.Class) / stf(rTryShip.Class)) * 0.3; 

	
	if (GetHullPercent(rChar) < 10 && GetHullPercent(rTryChar) > 30)
	{
		fChance += fChance * 3;
	}

	
	if (sti(rShip.SpeedRate) < sti(rTryShip.SpeedRate))				fChance += 0.2;
	if (sti(rShip.TurnRate) < sti(rTryShip.TurnRate))				fChance += 0.15;
	if (sti(rShip.CannonsQuantity) < sti(rTryShip.CannonsQuantity)) fChance += 0.1;
	if (sti(rShip.MaxCrew) < sti(rTryShip.MaxCrew))					fChance += 0.1;
	if (sti(rShip.Capacity) < sti(rTryShip.Capacity))				fChance += 0.1;
	if (sti(rShip.Price) < sti(rTryShip.Price))
	{
		fChance += 0.1;
	}
	else
	{
	    fChance -= 0.2;
	}

	if (fChance > 0.7) return true;
	return false;
}

void DoTakeAbordageGoods(ref rOneChr, ref rSecChr)
{
	int i, j, maxPrice, iGood, itmp;
	int freeSpace, freeQuantity;

	
	for (j=0; j < 3; j++)
	{
		freeSpace = GetCargoFreeSpace(rOneChr);
		
		if (freeSpace <= 0) return;

		maxPrice = 0;
		iGood = -1;
		
		for (i=0; i < GOODS_QUANTITY; i++)
		{
			itmp = GetCargoGoods(rSecChr, i);
			if (itmp > 0 && sti(Goods[i].Cost) > maxPrice)
			{
				maxPrice = sti(Goods[i].Cost);
				iGood = i;
			}
		}

		
		if (iGood == -1) return;

		
		freeQuantity = GetGoodQuantityByWeight(iGood, freeSpace);
		itmp = GetCargoGoods(rSecChr, iGood);
		if (itmp <= freeQuantity)
		{
			AddCharacterGoods(rOneChr, iGood, itmp);
			RemoveCharacterGoods(rSecChr, iGood, itmp);
		}
		else
		{
			AddCharacterGoods(rOneChr, iGood, freeQuantity);
			RemoveCharacterGoods(rSecChr, iGood, freeQuantity);
		}
	}
}

void LeaveAbordageShipDrift(int iDeadCharacterIndex, int iKillerCharacterIndex)
{
	
	ShipDead(iDeadCharacterIndex, KILL_BY_ABORDAGE, iKillerCharacterIndex);
	return;
	
	ref rDeadChar = GetCharacter(iDeadCharacterIndex);

	
	rDeadChar.taken = true;
	rDeadChar.taken.index = iKillerCharacterIndex;

	
	DoQuestCheckDelay("NationUpdate", 1.0);
	Ship_SetTaskDrift(SECONDARY_TASK, iDeadCharacterIndex);
	LAi_KillCharacter(rDeadChar);
}

void PlaceCompanionCloneNearMChr(int _index, bool _isCampus)
{
	int iTemp;
	ref chr, sld;
	aref arClone, arReal;

	chr = GetCharacter(GetCompanionIndex(PChar, _index));
	iTemp = NPC_GeneratePhantomCharacter("citizen", sti(chr.Nation), MAN, 0);  
	if (iTemp != -1)
	{
		sld = &Characters[iTemp];
        ChangeAttributesFromCharacter(sld, chr, true);
		makearef(arReal, chr.Tasks);
		makearef(arClone, sld.Tasks);
		CopyAttributes(arClone, arReal);

		if (_isCampus)
		{
			PlaceCharacter(sld, "sit", PChar.location);
			LAi_SetSitType(sld);
		}
		else
		{
			LAi_SetCitizenType(sld);
			PlaceCharacter(sld, "rld", PChar.location);
		}
		LAi_SetImmortal(sld, true); 
		sld.IsCompanionClone = true; 
        sld.RealCompanionIdx = chr.index;
        
		chr.Tasks.Clone = iTemp; 
	}
}

void CompanionSaveTasks()
{
	int i;
	ref chr, sld;
	aref arClone, arReal;

	for (i = 1; i < GetCompanionQuantity(PChar); i++)
	{
		chr = GetCharacter(GetCompanionIndex(PChar, i));
		if (CheckAttribute(chr, "Tasks.Clone"))
		{
			sld = GetCharacter(sti(chr.Tasks.Clone));

			makearef(arReal, chr.Tasks);
			makearef(arClone, sld.Tasks);
			CopyAttributes(arReal, arClone);

			sld.location = "none";
			DeleteAttribute(chr, "Tasks.Clone");
		}
	}
}




bool CheckEnemyCompanionDistance2GoAway(bool _loadForm)
{
    aref	arUpdate;
	int		i, k, cn, iRelation;
	float	fDistance;
	string  attr;
	
	ref rCharacter, rFortCharacter, rShipCharacter;

	makearef(arUpdate, pchar.SeaAI.Update);

	if (!CheckAttribute(arUpdate, "Ships")) { return true; }
	if (!CheckAttribute(arUpdate, "Forts")) { return true; }

	aref aShips, aForts;
	aref aFort;
	aref aShip;
	
	makearef(aShips, arUpdate.Ships);
	makearef(aForts, arUpdate.Forts);

	
	int iShipsNum = GetAttributesNum(aShips);
	
	int iFortsNum = GetAttributesNum(aForts);
	int iFortMode;

	DeleteAttribute(pchar, "CheckEnemyCompanionDistance");
	for (k=1; k<COMPANION_MAX; k++)
	{
		cn = GetCompanionIndex(pchar, k);
		if( cn>=0 )
		{
            attr = "CompIDX" + k;
			rCharacter = GetCharacter(cn);
			if (!GetRemovable(rCharacter)) continue;  
			
			
			for (i=0; i<iFortsNum; i++)
			{
				aFort = GetAttributeN(aForts, i);
				iRelation = sti(aFort.relation);

				rFortCharacter = GetCharacter(sti(aFort.idx));
				if (LAi_IsDead(rFortCharacter)) { continue; }
				iFortMode = sti(rFortCharacter.Fort.Mode);

				switch (iFortMode)
				{
					case FORT_NORMAL:
						if (iRelation == RELATION_ENEMY)
						{
		                    fDistance = Ship_GetDistance2D(rCharacter, rFortCharacter);
							if (fDistance < MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER_FORT)
							{
							    if (!_loadForm) return false; 
								
           						pchar.CheckEnemyCompanionDistance.(attr)) = cn;
							}
						}
					break;
				}
			}
			
			for (i=0; i<iShipsNum; i++)
			{
				aShip = GetAttributeN(aShips, i);

				rShipCharacter = GetCharacter(sti(aShip.idx));
				iRelation = sti(aShip.relation);

				if (LAi_IsDead(rShipCharacter)) { continue; }
				if (iRelation != RELATION_ENEMY) { continue; }
		        fDistance = Ship_GetDistance2D(rCharacter, rShipCharacter);
				if (fDistance < MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER)
				{
				    if (!_loadForm) return false; 
					pchar.CheckEnemyCompanionDistance.(attr)) = cn;
				}
			}
		}
	}
	if (_loadForm && CheckAttribute(pchar, "CheckEnemyCompanionDistance"))
	{
		
		LaunchLeaveBattleScreen();
		return false;
	}
	return true; 
}
