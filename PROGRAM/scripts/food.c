#define I_MIN_MORALE	10


#define FOOD_BY_CREW       10.0
#define FOOD_BY_SLAVES     20.0
#define FOOD_BY_PASSENGERS 10.0
#define RUM_BY_CREW        60.0






int CalculateFood()
{
	int chrIndex;
	int iCrewQuantity = 0;
	float foodNeeded = 0;
	int iSlavesQuantity = 0;
	int iFoodQuantity = 0;

	for (int i=0; i<COMPANION_MAX; i++)
	{
		chrIndex = GetCompanionIndex(pchar, i);
		if (chrIndex != -1)
		{
            if (!GetRemovable(&characters[chrIndex])) continue;
			if (characters[chrIndex].ship.type != SHIP_NOTUSED)
			{
				iCrewQuantity   += sti(characters[chrIndex].ship.crew.quantity);
				iFoodQuantity   += makeint(GetCargoGoods(&characters[chrIndex], GOOD_FOOD) / isEquippedArtefactUse(&characters[chrIndex], "talisman6", 1.0, 0.75));
				iSlavesQuantity += GetCargoGoods(&characters[chrIndex], GOOD_SLAVES);
			}
		}
	}
	int iPassQuantity = GetPassengersQuantity(pchar);

	foodNeeded = makefloat(iCrewQuantity/FOOD_BY_CREW + iPassQuantity/FOOD_BY_PASSENGERS + iSlavesQuantity/FOOD_BY_SLAVES);

	if (foodNeeded < 1)
	{
		foodNeeded = 1;
	}

	iFoodQuantity = makeint(iFoodQuantity/foodNeeded + 0.2);

	return iFoodQuantity;
}


int CalculateShipFood(ref _chr)
{
	int iCrewQuantity = 0;
	float foodNeeded = 0.0;
	int iSlavesQuantity = 0;
	int iFoodQuantity = 0;
	int iPassQuantity = 0;

	iCrewQuantity   =  sti(_chr.ship.crew.quantity);
	iFoodQuantity   =  GetCargoGoods(_chr, GOOD_FOOD);
	iSlavesQuantity =  GetCargoGoods(_chr, GOOD_SLAVES);
	if (_chr.id == pchar.id) 
	{
		iPassQuantity = GetPassengersQuantity(pchar);
	}

	foodNeeded = isEquippedArtefactUse(_chr, "talisman6", 1.0, 0.75) * makefloat(iCrewQuantity/FOOD_BY_CREW + iPassQuantity/FOOD_BY_PASSENGERS + iSlavesQuantity/FOOD_BY_SLAVES);

	if (foodNeeded < 1.0)
	{
		foodNeeded = 1.0;
	}

	iFoodQuantity = makeint(iFoodQuantity/foodNeeded + 0.2);

	return iFoodQuantity;
}


int CalculateShipRum(ref _character)
{
	int crewQuantity 	= GetCrewQuantity(_character);
	int rumQuantity     = GetCargoGoods(_character, GOOD_RUM);	
	float rumNeeded 	= isEquippedArtefactUse(_character, "talisman4", 1.0, 0.2) * makefloat( (crewQuantity + 5.1) / (RUM_BY_CREW - MOD_SKILL_ENEMY_RATE * 2.5)); 
	
	if(rumNeeded < 1.0) rumNeeded = 1.0;	
	rumQuantity = makeint(rumQuantity/rumNeeded + 0.2);		
	return rumQuantity;
}


int CalculateRum()
{
	int 	chrIndex;
	int 	iCrewQuantity = 0;
	int 	iRumCount = 0;
	float 	RumNeeded = 0;

	for (int i=0; i<COMPANION_MAX; i++)
	{
		chrIndex = GetCompanionIndex(pchar, i);
		if (chrIndex != -1)
		{
            if (!GetRemovable(&characters[chrIndex])) continue;
			if (characters[chrIndex].ship.type != SHIP_NOTUSED)
			{
				iCrewQuantity   += GetCrewQuantity(&characters[chrIndex]);
				iRumCount       += makeint(GetCargoGoods(&characters[chrIndex], GOOD_RUM) / isEquippedArtefactUse(&characters[chrIndex], "talisman4", 1.0, 0.75));							
			}
		}
	}
	RumNeeded = makefloat(iCrewQuantity/(RUM_BY_CREW - MOD_SKILL_ENEMY_RATE * 2.5));

	if (RumNeeded < 1.0)
	{
		RumNeeded = 1.0;
	}

	return makeint(iRumCount/RumNeeded + 0.2);
}

void DailyRatsEatGoodsUpdate(ref chref)
{
	if(IsCharacterEquippedArtefact(chref, "talisman1")) return; 
	if(IsCharacterEquippedArtefact(chref, "rat_poison")) return; 
	if(CheckAttribute(pchar, "GenQuest.Ole")) return; 
    int iGoods = GOOD_FOOD + rand(GOOD_OIL - GOOD_FOOD);
	if(iGoods == GOOD_BRICK) return;
    int iQuantity = GetCargoGoods(chref, iGoods);
    int iSeaGoods = LanguageOpenFile("ShipEatGood.txt");
    if (iQuantity > 60 && rand(4) != 2) 
    {
        float fSkill = GetSummonSkillFromNameToOld(chref, SKILL_REPAIR) + GetSummonSkillFromNameToOld(chref,SKILL_FORTUNE);
        
        iQuantity = 1+ rand(makeint(iQuantity / (10+fSkill)));
		if (IsCharacterPerkOn(chref, "HT2")) iQuantity = makeint(iQuantity/2) + 1;
        RemoveCharacterGoodsSelf(chref, iGoods, iQuantity);
        
        Log_SetStringToLog(RandSwear());
        Log_SetStringToLog("Rats on " +
                           chref.Ship.Name + LinkRandPhrase(" spoiled ", " damaged ", " destroyed ")+
                           iQuantity + " pieces of " + LanguageConvertString(iSeaGoods, "seg_" + Goods[iGoods].Name));

        Statistic_AddValue(pchar, "RatsEatGoods", iQuantity);
                
		if (iQuantity > 400) iQuantity = 400;
		
		AddCharacterExpToSkill(chref, SKILL_REPAIR, iQuantity);
        AddCharacterExpToSkill(chref, SKILL_FORTUNE, iQuantity/10);
    }
    LanguageCloseFile(iSeaGoods);
}


void DailyEatCrewUpdate()   
{
    ref mainCh = GetMainCharacter();
    int i, cn, crew, morale;
    ref chref;
    int nMoraleDecreaseQ;
    
    
    
    
    
	
	
	DailyTradersMoneyUpdate();
	
	
    mainCh.questTemp.abordage = 0; 

    
    
    
    
    

    SetNewDayHealth(); 
  
	
	
    DeleteAttribute(mainCh, "GenQuest.Hunter2Pause");  
    

    
	if (CheckAttribute(mainCh, "questTemp.ShipCapellan.Yes")) AddCrewMorale(mainCh, 2); 

	
	if (bNoEatNoRats) return; 
    if (sti(mainCh.Ship.Type) == SHIP_NOTUSED ) return;

	
	if (CheckAttribute(pchar, "CrewPayment")) 
	{
		ChangeCharacterComplexReputation(pchar,"authority", -0.1);
        cn = makeint(pchar.CrewPayment);
        if (cn > 32000) cn = 32000;
		if (rand(cn) > 1000)
		{
            morale = 5 + CheckOfficersPerk(pchar, "IronWill");   
			for (i = 0; i<GetPassengersQuantity(pchar); i++)
			{   
				cn = GetPassenger(pchar, i);
				if (cn != -1)
				{
		            chref = &Characters[cn];
					if (CheckAttribute(chref, "loyality") && !CheckAttribute(chref, "OfficerWantToGo.DontGo") && rand(morale) == 2 && !IsEquipCharacterByArtefact(chref, "totem_04"))
					{
		    			chref.loyality = makeint(chref.loyality) - 1;
					}
				}
			}
		}
	}
	
	
	for(i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(mainCh,i);
		if( cn>=0 )
		{
			chref = GetCharacter(cn);

			if (!GetRemovable(chref)) continue;

			
			DailyRatsEatGoodsUpdate(chref);
			
			DailyEatCrewUpdateForShip(chref, false);
			
		}
	}
}




void DailyEatCrewUpdateForShip(ref rChar, bool IsCompanionTraveler) 
{
	int iCrewQty = GetCrewQuantity(rChar);
	int cn, morale, nMoraleDecreaseQ, iDeadCrew;
	if(iCrewQty < 1 && GetCargoGoods(rChar, GOOD_SLAVES) < 1) return;
	if(!CheckAttribute(rChar, "Ship.Crew.Morale"))
	{
		rChar.Ship.Crew.Morale = 50;
	}
	
	if(rand(4) == 2)
	{
		
		cn = iCrewQty / 10;
		if(cn > 30) cn = 30;
		cn = rand(cn)+1;
		if(iCrewQty < cn) cn = iCrewQty;
		if(cn > 0)
		{
			if(GetCargoGoods(rChar, GOOD_MEDICAMENT) < 1)
			{
				if(!IsCompanionTraveler) Log_Info("On " + rChar.Ship.Name + " illness killed " + FindRussianSailorString(cn, "No"));
				iCrewQty = iCrewQty - cn;
				Statistic_AddValue(pchar, "Sailors_dead", cn);
				Achievment_SetStat(pchar, 21, cn);
				rChar.Ship.Crew.Quantity = iCrewQty;
				
				morale = sti(rChar.Ship.Crew.Morale);
				
				if(CheckOfficersPerk(rChar, "IronWill")) cn /= 1.5;
				
				AddCrewMorale(rChar, -makeint(cn / 2)); 
				ChangeCharacterComplexReputation(pchar,"authority", -1);
			}
			else
			{
				if(CheckShipSituationDaily_GenQuest(rChar) == 2) cn = cn * 2;
				if(CheckShipSituationDaily_GenQuest(rChar) == 3) cn = cn * 3;
				
				RemoveCharacterGoodsSelf(rChar, GOOD_MEDICAMENT, cn);
				if(GetCargoGoods(rChar, GOOD_MEDICAMENT) < 16)
				{
					if(!IsCompanionTraveler) Log_Info("" + rChar.Ship.Name + " is low on medicines");
				}
			}
		}
		
		cn = GetCargoGoods(rChar, GOOD_SLAVES) / 10;
		if(cn > 30) cn = 30;
		cn = rand(cn)+1;
		if(GetCargoGoods(rChar, GOOD_SLAVES) < cn) cn = GetCargoGoods(rChar, GOOD_SLAVES);
		if(cn > 0)
		{
			if(GetCargoGoods(rChar, GOOD_MEDICAMENT) < 1)
			{
				if(!IsCompanionTraveler) Log_Info("On " + rChar.Ship.Name + " illness killed " + FindRussianSlavesString(cn, "No"));
				RemoveCharacterGoodsSelf(rChar, GOOD_SLAVES, cn);
			}
			else
			{
				cn /= 3;
				RemoveCharacterGoodsSelf(rChar, GOOD_MEDICAMENT, cn);
			}
		}
		
		if(iCrewQty < 1 && GetCargoGoods(rChar, GOOD_SLAVES) < 1) return;
	}
	

	
	iCrewQty = GetCrewQuantity(rChar);
	float rumNeeded = isEquippedArtefactUse(rChar, "talisman4", 1.0, 0.2) * makefloat( (iCrewQty + 5.1) / (RUM_BY_CREW - MOD_SKILL_ENEMY_RATE * 2.5)); 
	
	if(rumNeeded < 1.0) rumNeeded = 1.0;
	iCrewQty = makeint(rumNeeded);
	
	if(iCrewQty > 0)
	{
		if(GetCargoGoods(rChar, GOOD_RUM) >= iCrewQty)
		{
			RemoveCharacterGoodsSelf(rChar, GOOD_RUM, iCrewQty);
			
			cn = makeint(GetCargoGoods(rChar, GOOD_RUM) / iCrewQty);
			if (cn < 1)
			{
				if(!IsCompanionTraveler) Log_Info("No rum left on " + rChar.Ship.Name + "");
			}
			
			if(CheckShipSituationDaily_GenQuest(rChar) == 1) AddCrewMorale(rChar, 2);
		}
		else
		{
			iCrewQty = GetCargoGoods(rChar, GOOD_RUM);
			RemoveCharacterGoodsSelf(rChar, GOOD_RUM, iCrewQty);
		}
	}
	
	
	iCrewQty = GetCrewQuantity(rChar);
	
	if(iCrewQty > GetOptCrewQuantity(rChar) && !IsCharacterEquippedArtefact(rChar, "talisman4"))
	{
		AddCrewMorale(rChar, -(1+rand(3)));
		ChangeCharacterComplexReputation(pchar,"authority", -0.1);
	} 
	
	
	
	if(iCrewQty > 0 && CheckAttribute(PChar, "CrewPayment"))
	{
		cn = makeint(PChar.CrewPayment);
		if(cn > 32000) cn = 32000;
		if(rand(cn) > 1000)
		{
			ChangeCharacterComplexReputation(pchar,"authority", -0.2);
			AddCrewMorale(rChar, -1);
			cn = 5 + CheckOfficersPerk(PChar, "IronWill");  
			if(i > 0 && rand(cn) == 2 && !CheckAttribute(rChar, "OfficerWantToGo.DontGo") && !IsEquipCharacterByArtefact(rChar, "totem_04"))
			{
				rChar.loyality = sti(rChar.loyality) - 1;
			}
		}
	}
	
	iCrewQty = makeint(isEquippedArtefactUse(rChar, "talisman6", 1.0, 0.75) * (iCrewQty+5.1) / FOOD_BY_CREW + GetPassengersQuantity(rChar) / FOOD_BY_PASSENGERS); 
	iCrewQty = iCrewQty + makeint((GetCargoGoods(rChar, GOOD_SLAVES)+6)/ FOOD_BY_SLAVES);  
	if(iCrewQty == 0) iCrewQty = 1;
	if(GetCargoGoods(rChar, GOOD_FOOD) >= iCrewQty)
	{
		RemoveCharacterGoodsSelf(rChar, GOOD_FOOD, iCrewQty);
		
		cn = makeint(GetCargoGoods(rChar, GOOD_FOOD) / iCrewQty);
		if (cn < 4)
		{
			if(!IsCompanionTraveler)
			{
				Log_Info("" + rChar.Ship.Name + " has enough provisions only for " + FindRussianDaysString(cn));
				Log_Info("We need to restock as soon as possible!");
				PlaySound("interface\notebook.wav");
			}
		}
		
		if (sti(rChar.index) == GetMainCharacterIndex() && GetCargoGoods(rChar, GOOD_SLAVES) > (GetCrewQuantity(rChar)*1.5 + sti(rChar.Ship.Crew.Morale)))
		{
			nMoraleDecreaseQ = 12 - GetSummonSkillFromNameToOld(rChar, SKILL_LEADERSHIP);
			if(CheckOfficersPerk(rChar, "IronWill")) nMoraleDecreaseQ /= 2;
			if(rand(2) == 1 && nMoraleDecreaseQ > rand(10))
			{
				if(IsEntity(worldMap))
				{
					rChar.GenQuest.SlavesMunity = true;
					Log_Info("Slaves have revolted!");
					MunityOnShip("SlavesMunity");
				}
			}
		}
	}
	else
	{
		iCrewQty = GetCargoGoods(rChar, GOOD_FOOD);
		RemoveCharacterGoodsSelf(rChar, GOOD_FOOD, iCrewQty);
		PlaySound("interface\notebook.wav");
		
		if(!IsCompanionTraveler) Log_Info("Crew of " + rChar.Ship.Name + " is starving. People are angry.");
		
		if(sti(rChar.index) == GetMainCharacterIndex())
		{
			AddCharacterHealth(PChar, -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
		}
		
		cn = GetCrewQuantity(rChar);
		if(cn > 1)
		{
			iDeadCrew = makeint(cn/10 +0.5);
			rChar.Ship.Crew.Quantity = cn - iDeadCrew;
			Statistic_AddValue(pchar, "Sailors_dead", iDeadCrew);
			Achievment_SetStat(pchar, 21, iDeadCrew);
			if(!IsCompanionTraveler) Log_Info("Crewmen are dying of starvation");
		}
		cn = GetCargoGoods(rChar, GOOD_SLAVES);
		if(cn > 0)
		{
			RemoveCharacterGoodsSelf(rChar, GOOD_SLAVES, makeint(cn/5 + 0.5));
			if(!IsCompanionTraveler) Log_Info("Slaves are dying of starvation");
		}
		morale = sti(rChar.Ship.Crew.Morale);
		
		nMoraleDecreaseQ = 12 - GetSummonSkillFromNameToOld(rChar, SKILL_LEADERSHIP);
		if(CheckOfficersPerk(rChar, "IronWill")) nMoraleDecreaseQ /= 2;
		rChar.Ship.Crew.Morale = morale - nMoraleDecreaseQ;
		if(sti(rChar.Ship.Crew.Morale) < MORALE_MIN) rChar.Ship.Crew.Morale = MORALE_MIN;  
	}
	
	if(sti(rChar.index) == GetMainCharacterIndex())
	{
		if(sti(rChar.Ship.Crew.Morale) <= MORALE_MIN || makeint(rChar.reputation.authority) < 5)
		{
			
			if(IsEntity(worldMap) && GetCrewQuantity(rChar) > 0 && !IsCharacterEquippedArtefact(rChar, "totem_02"))
			{
				Log_Info("A mutiny on " + rChar.Ship.Name + "! ");
				MunityOnShip("ShipMunity");
			}
		}
	}
	else
	{
		if(GetShipRemovable(rChar) && !CheckAttribute(rChar, "OfficerWantToGo.DontGo") && !IsCompanionTraveler && !IsEquipCharacterByArtefact(rChar, "totem_04")) 
		{
			if(sti(rChar.Ship.Crew.Morale) <= MORALE_MIN || sti(rChar.loyality) <= 0) 
			{
				if(GetCrewQuantity(rChar) > 0 && !IsCharacterEquippedArtefact(rChar, "totem_02"))
				{
					Log_Info("A mutiny on " + rChar.Ship.Name + "! ");
					Log_SetStringToLog("The ship is leaving from your squadron");
					Statistic_AddValue(PChar, "ShipMunity", 1);
					RemoveCharacterCompanion(PChar, rChar);
					
					if(!CheckAttribute(rChar, "PGGAi"))
					{
						rChar.LifeDay = 0; 
					}
					else
					{
						rChar.PGGAi.IsPGG = true;
						rChar.RebirthPhantom = true;
						rChar.PGGAi.location.town = PGG_FindRandomTownByNation(sti(rChar.nation));
						rChar.Dialog.FileName = "PGG_Dialog.c";
						rChar.Dialog.CurrentNode = "Second Time";
						PGG_ChangeRelation2MainCharacter(rChar, -20);
					}
					rChar.location = ""; 
					rChar.location.group = "";
					rChar.location.locator = "";
				}
			}
		}
	}
}

void DailyTradersMoneyUpdate()
{
	ref rCharacter;
	
	for(int n = 0; n < MAX_CHARACTERS; n++)
	{
		makeref(rCharacter,Characters[n]);
		if (CheckAttribute(rCharacter, "Merchant.type")) 
		{
			if(rCharacter.Merchant.type != "jeweller")
			{
				if(sti(rCharacter.money) > TRADER_MAX_MONEY || sti(rCharacter.money) < TRADER_MIN_MONEY) 	
				{
					rCharacter.money = TRADER_MIN_MONEY + rand(TRADER_NORM);
				}
			}
			else
			{
				if(sti(rCharacter.money) > USURER_MAX_MONEY || sti(rCharacter.money) < USURER_MIN_MONEY) 	
				{
					rCharacter.money = USURER_MIN_MONEY + rand(USURER_NORM);
				}
			}	
		}
	}
}


