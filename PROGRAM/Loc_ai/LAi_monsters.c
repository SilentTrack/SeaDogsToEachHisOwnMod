
void LAi_GenerateFantomFromMe(aref chr)
{
	
	if(!TestRef(loadedLocation)) return;
	if(!IsEntity(loadedLocation)) return;
	if(LAi_LocationIsFantomsGen(loadedLocation) == false) return;
	
	if(LAi_CharacterIsReincarnation(chr) == false) return;
	
	bool isGen = LAi_CharacterReincarnationMode(chr);
	if(CheckAttribute(chr, "model") == false) isGen = true;
	if(CheckAttribute(chr, "model.animation") == false) isGen = true;
	if(chr.model == "") isGen = true;
	if(chr.model.animation == "") isGen = true;
	string model, ani;
	if(isGen)
	{
		int nat = GetLocationNation(loadedLocation)
		if(nat < 0) nat = PIRATE;
		if(nat >= MAX_NATIONS) nat = PIRATE;
		if(CheckAttribute(&Nations[nat], "fantomModel") == false)
		{
			Trace("Nation (Nations[" + nat + "]) by name " + Nations[nat].name + " not include fantoms");
			return;
		}
		aref fantoms;
		makearef(fantoms, Nations[nat].fantomModel);
		int num = GetAttributesNum(fantoms);
		if(num <= 0)
		{
			Trace("Nation (Nations[" + nat + "]) by name " + Nations[nat].name + " not include have fantoms");
			return;
		}
		num = rand(num - 1);
		string m = GetAttributeName(GetAttributeN(fantoms, num));
		model = fantoms.(m);
		ani = "man";
		m = m + ".ani";
		if(CheckAttribute(fantoms, m) != false)
		{
			ani = fantoms.(m);
		}
	}else{
		model = chr.model;
		ani = chr.model.animation;
	}
	
	object tmp;
	CopyAttributes(&tmp, chr);
	
	if(ani == "mushketer")
	{
		ref sld = GetCharacter(NPC_GenerateCharacter("GenChar_", model, "man", "mushketer", chr.rank, sti(chr.nation), sti(chr.lifeDay), false, "soldier"));
		sld.id = "GenChar_" + sld.index;
		sld.reputation = chr.reputation;
		sld.City = chr.City;
        sld.CityType = chr.CityType;
		sld.RebirthPhantom = true; 
		sld.dialog.filename = "Common_Soldier.c";
		sld.dialog.currentnode = "first time";
		LAi_CharacterReincarnation(sld, true, true);
		LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
		if (CheckAttribute(chr, "chr_ai.reincarnation.step"))
		{
			SetFantomParamFromRank(sld, sti(chr.rank) + sti(chr.chr_ai.reincarnation.step), true); 
		}
		LAi_SetLoginTime(sld, 6.0, 23.0); 
		sld.dialog.filename = chr.dialog.filename;
		sld.dialog.currentnode = chr.dialog.currentnode;
		SetRandomNameToCharacter(sld);
		LAi_SetPatrolType(sld);
		LAi_group_MoveCharacter(sld, chr.chr_ai.group);
		PlaceCharacter(sld, "patrol", "random_free");
	}
	else
	{
		ref fnt = LAi_CreateFantomCharacterEx(model, ani, LAi_CharacterReincarnationGroup(chr), "");
		string curidx = fnt.index;
		
		CopyAttributes(fnt, &tmp);
		
		
		
		if (CheckAttribute(chr, "chr_ai.reincarnation.step"))
		{
			SetFantomParamFromRank(fnt, sti(chr.rank) + sti(chr.chr_ai.reincarnation.step), true); 
			characters[sti(fnt.baseIndex)].rank = fnt.rank; 
		}
		else 
		{
			LAi_NPC_Equip(fnt, sti(fnt.rank), true, true);
			LAi_SetCurHPMax(fnt);
		}
		
		if(CheckAttribute(fnt, "chr_ai.group"))
		{
			LAi_group_MoveCharacter(fnt, fnt.chr_ai.group);
		}else{
			LAi_group_MoveCharacter(fnt, "");
		}
		
		fnt.model = model;
		fnt.model.animation = ani;
		
		if(!CheckAttribute(fnt, "chr_ai.type")) fnt.chr_ai.type = "";
		string chrtype = fnt.chr_ai.type;
		SetRandomNameToCharacter(fnt);
		fnt.id = tmp.id;
		fnt.index = curidx;
		LAi_tmpl_stay_InitTemplate(fnt);
		fnt.chr_ai.type = "";
		if(chrtype != "")
		{
			chrtype = "LAi_type_" + chrtype + "_Init";
			call chrtype(fnt);
		}
		SetNewModelToChar(fnt);   
	}
}

bool LAi_CreateFlowers(ref location)
{
	ref rItm;
	if (CheckAttribute(location, "fastreload") && location.id.label != "exittown") return false;
	if(!CheckAttribute(location, "locators.item") || location.id.label == "Cave entrance" || location.type == "seashore" || location.type == "cave") return false;
	if(location.type != "jungle") return false;
	
	if(CheckAttribute(location, "growflower") && GetNpcQuestPastDayParam(location, "Fl_date") > 9) DeleteAttribute(location, "growflower");
	
	if (!CheckAttribute(location, "growflower"))
	{
		int n = 1;
		if(location.id.label == "exittown" && !CheckAttribute(location, "fastreload")) n = 2;
			for(int i = 0; i < n; i++)
			{
				rItm = ItemsFromID("cannabis"+(rand(5)+1));
				rItm.shown = true;
				rItm.startLocation = location.id;
				rItm.startLocator = "flower" + (rand(9)+1);
				
			}
		SaveCurrentNpcQuestDateParam(location, "Fl_date");
		location.growflower = true;
	}
	return true;
}

bool LAi_CreateQuestFlowers(ref location) 
{
	ref rItm;
	int i;
	if (CheckAttribute(location, "questflower"))
	{
		i = sti(location.questflower);
		rItm = ItemsFromID("cannabis7");
		rItm.shown = true;
		rItm.startLocation = location.id;
		rItm.startLocator = "qflower"+i;
		
		DeleteAttribute(location, "questflower");
	}
	return true;
}

bool LAi_CreateShoreChest(ref location) 
{
	string sTemp = location.id;
	DeleteAttribute(location, "box1.NotChest");
	DeleteAttribute(location, "box2.NotChest");
	if(CheckAttribute(location, "Chestgennot")) return false;
	if (location.type == "seashore")
	{
		location.box1.NotChest = true;
		location.box2.NotChest = true;
		if(CheckAttribute(location, "Chestgennot")) return false;
		if (CheckAttribute(pchar, "questTemp.Sharlie.Lock")) return false; 
		if (!CheckAttribute(location, "shorechest") && drand(100) < 5) 
		{
			string sModel = "chest_"+(rand(2)+1);
			location.num = drand(1)+1;
			location.numbox = "box"+(sti(location.num));
			location.shorechest = true;
			location.models.always.chest = sModel;
			location.models.always.chest.locator.group = "box";
			location.models.always.chest.locator.name = location.numbox;
			location.models.always.chest.tech = "DLightModel"; 
			
			return true;
		}
		if(CheckAttribute(location, "shorechest")) 
		{
			
			if (sti(location.num) == 1) DeleteAttribute(location, "box1.NotChest");
			else DeleteAttribute(location, "box2.NotChest");
			if(CheckAttribute(location, "chest_date") && GetNpcQuestPastDayParam(location, "chest_date") > 2) 
			{
				DeleteAttribute(&locations[FindLocation(sTemp)], location.numbox);
				DeleteAttribute(location, "shorechest");
				DeleteAttribute(location, "shorefill");
				DeleteAttribute(location, "chest_date");
				DeleteAttribute(location, "models.always.chest");
				
			}
			else 
			{
				if(!CheckAttribute(location, "shorefill")) 
				{
					FillShorechestBox(sTemp, sti(location.num), drand(5));
					SaveCurrentNpcQuestDateParam(location, "chest_date");
					location.shorefill = true;
					
				}
				else
				{
					
					return true;
				}
			}
		}
	}
	return true;
}

bool LAi_CreateDolly(ref location) 
{
	ref rItm = ItemsFromID("dolly0");
	ref rItem = ItemsFromID("dolly5");
	if (CheckAttribute(location, "dolly"))
	{
		int i = sti(location.dolly);
		float fStrTime, fFinTime;
		switch (i)
		{
			case 1:
				fStrTime = 0.00;
				fFinTime = 1.00;
			break;
			
			case 2:
				fStrTime = 8.00;
				fFinTime = 9.00;
			break;
			
			case 3:
				fStrTime = 16.00;
				fFinTime = 17.00;
			break;
		}
		if (stf(environment.time) >= fStrTime && stf(environment.time) < fFinTime && CheckAttribute(pchar, "questTemp.Dolly"))
		{
			rItm.shown = false;
			rItem.shown = true;
			rItem.startLocation = location.id;
			rItem.startLocator = "dolly"+i;
			location.canteleport = true;
			CreateLocationParticles("shadowstar", "camera", "dolly", 1.15, 0, 0, "");
		}
		else
		{
			rItem.shown = false;
			rItm.shown = true;
			rItm.startLocation = location.id;
			rItm.startLocator = "dolly"+i;
			DeleteAttribute(location, "canteleport");
		}
	}
	return true;
}

bool LAi_CreateEncounters(ref location)
{
	aref grp, st, at;
	ref chr, rCharacter, rItm;
	string encGroup, str, locator, sAreal, sCity, sEncType;
	int num, i, iChar, iNation, iRank, n, iTemp, iMassive, iRnd, iRand, iEncrnd;
	string model[10];
	if (!bLandEncountersGen) 
	{		
		bLandEncountersGen = true;
		return false;
	}
	
	if(CheckAttribute(location, "DisableEncounters")) return false;
	if(!CheckAttribute(location, "locators.encdetector") || !CheckNPCQuestDate(location, "Enc_date") || bDisableLandEncounters) return false;
	if (CheckAttribute(location, "fastreload")) return false; 
    
	if (CheckAttribute(pchar, "GenQuest.Enc2Pause"))
	{
	    DeleteAttribute(pchar, "GenQuest.Enc2Pause");
	    return false;
	}
	
	
	if (location.type == "seashore") 
	{
		makearef(st, location.models.always);
		num = GetAttributesNum(st);
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(st, i);	
			str = GetAttributeName(at);
			if(st.(str) == "smg")
			{
				return false;
			}
		}			
	}
	
	SetNPCQuestDate(location, "Enc_date"); 
	
	
	
	sAreal = GiveArealByLocation(location);
	if (sAreal == "none") return false;
	
	
	if(!CheckAttribute(location, "onUninhabitedIsland"))
	{
		sCity = GetCityNameByIsland(sAreal);
		if (sCity == "none") return false;
		iNation = GetCityNation(sCity);
		if (iNation == -1 || iNation == PIRATE) return false;
	}
	
	
	
	if(CheckAttribute(location, "ItzaLand")) return false;
	
	
	
	if(!isLocationFreeForQuests(location.Id)) return false;
	
	
	encGroup = LAi_FindRandomLocator("encdetector");
	str = "locators." + encGroup;
	makearef(grp, location.(str));
	if(CheckAttribute(location, "onUninhabitedIsland") || CheckAttribute(location, "deadlocked")) 
	{
		if(location.type == "seashore") iRand = rand(1) + 7;
		else iRand = 1;
	}	
	else
	{	
		iRand = rand(6);
	}	
	switch (iRand)
	{
		
		case 0:
			if (rand(10) > 6) return false;
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock")) return false;
			if(CheckAttribute(location, "onUninhabitedIsland") || location.type == "seashore" || location.type == "mayak" || location.type == "questisland") return false; 
			if(location.id == "Curacao_jungle_03" || location.id == "Hispaniola_Jungle_02") return false;
			num = GetAttributesNum(grp) - rand(2); 
			if (num <= 0 ) num = 1; 
			str = "Gang"+ location.index + "_";
			
			if (sti(pchar.rank) > 6) 
			{
				if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5/num);
				else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*1.6/num);
			}
			else iRank = sti(pchar.rank); 
	
			
			
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
			
			LAi_grp_alarmactive = false;
			LAi_group_ClearAllTargets();
			
			i = 0;
			iEncrnd = rand(1);
			while(i < num)
			{
				iMassive = rand(9);
				if (model[iMassive] != "")
				{
					chr = GetCharacter(NPC_GenerateCharacter(str + i, model[iMassive], "man", "man", iRank, iNation, 1, true, "marginal"));
					SetFantomParamFromRank(chr, iRank, true);
					
					if (iEncrnd == 0)
					{
						rItm = ItemsFromID("fire");
						rItm.shown = true;
						rItm.startLocation = location.id;
						rItm.startLocator = "fire";
						location.fire = true;
						encGroup = "enc01";
						locator = "ass"+(i+1);
						ChangeCharacterAddressGroup(chr, location.id, "goto", locator);
						LAi_SetGroundSitTypeNoGroup(chr);
					}
					else
					{
						locator = GetAttributeName(GetAttributeN(grp, i));
						ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
						LAi_SetStayType(chr);
					}
					chr.dialog.filename = "Enc_Raiders_dialog.c";
					chr.greeting = "banditos"; 
					chr.EncQty = num;
					LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, true, "LandEnc_RaidersBeforeDialog");
					LAi_group_MoveCharacter(chr, "RaidersGroup_" + location.index);
					if (i == 0) 			
					{
						sAreal = "Raiders_" + location.index;
						pchar.GenQuest.(sAreal).name = GetFullName(chr); 
						pchar.GenQuest.(sAreal).nation = iNation; 
					}
					i++;
					model[iMassive] = "";
				}
			}
			str = "EncRaiders_" + location.index;
			pchar.quest.(str).win_condition.l1        = "locator";
			pchar.quest.(str).win_condition.l1.location = location.id;
			pchar.quest.(str).win_condition.l1.locator_group = "encdetector";
			pchar.quest.(str).win_condition.l1.locator = encGroup;
			pchar.quest.(str).win_condition = "LandEnc_RaidersBegin";
			pchar.quest.(str).EncQty = num; 
			pchar.quest.(str).LocIdx = location.index; 
			pchar.GenQuest.LandEnc.LocId = location.id;
			str = "TimeRaiders_" + location.index;
			pchar.quest.(str).win_condition.l1            = "Timer";
			pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.(str).win_condition               = "LandEnc_RaidersOver";	
			pchar.quest.(str).LocIdx = location.index;
		break;
		
		
		case 1:				
			if (rand(10) > 7) return false;
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock")) return false;
			if(location.type == "seashore" || location.type == "mayak") return false;
			if(location.id == "Curacao_jungle_03" || location.id == "Hispaniola_Jungle_02") return false;
			num = 4; 
			str = "Carib"+ location.index + "_";
			
			if (sti(pchar.rank) > 6) 
			{
				if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5/num);
				else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*1.6/num);
			}
			else iRank = sti(pchar.rank)+3; 
			
			
			
			if (rand(1) == 0) sEncType = "war";
			else sEncType = "peace";
			
			
			if (sEncType == "war")
			{
				model[0] = "canib_1";
				model[1] = "canib_2";
				model[2] = "canib_3";
				model[3] = "canib_4";
				model[4] = "canib_5";
				model[5] = "canib_6";
				model[6] = "canib_1";
				model[7] = "canib_2";
				model[8] = "canib_3";
				model[9] = "canib_4";
			}
			else
			{
				model[0] = "miskito_1";
				model[1] = "miskito_2";
				model[2] = "miskito_3";
				model[3] = "miskito_4";
				model[4] = "miskito_5";
				model[5] = "miskito_6";
				model[6] = "miskito_1";
				model[7] = "miskito_2";
				model[8] = "miskito_3";
				model[9] = "miskito_4";
			}
			
			LAi_grp_alarmactive = false;
			LAi_group_ClearAllTargets();
			
			i = 0;
			iEncrnd = rand(2);
			while(i < num)
			{
				iMassive = rand(9);
				if (model[iMassive] != "")
				{
					chr = GetCharacter(NPC_GenerateCharacter(str + i, model[iMassive], "man", "man", iRank, PIRATE, 1, true, "native"));
					SetFantomParamFromRank(chr, iRank, true);
					
					if (iEncrnd > 0)
					{
						rItm = ItemsFromID("fire");
						rItm.shown = true;
						rItm.startLocation = location.id;
						rItm.startLocator = "fire";
						location.fire = true;
						encGroup = "enc01";
						locator = "ass"+(i+1);
						ChangeCharacterAddressGroup(chr, location.id, "goto", locator);
						LAi_SetGroundSitTypeNoGroup(chr);
					}
					else
					{
						locator = GetAttributeName(GetAttributeN(grp, i));
						ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
						LAi_SetStayType(chr);
					}
					
					if (CheckAttribute(pchar, "questTemp.Caleuche.SeekAmulet") && i == 0 && drand(2) == 1) 
					{
						GiveItem2Character(chr, "kaleuche_amulet1");
						chr.SaveItemsForDead = true;
						chr.DontClearDead = true;
					}
					
					chr.dialog.filename = "Enc_Carib_dialog.c";
					chr.greeting = "indiano"; 
					chr.name = GetIndianName(MAN);
					chr.lastname = "";
					chr.EncQty = num;
					if (sEncType == "war")
					{
						chr.dialog.currentnode = "war_indian";
						if (drand(9) < 8) LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, true, "LandEnc_CaribBeforeDialog");
						else LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, true, "LandEnc_MiskitoBeforeDialog");
					}
					else
					{
						chr.dialog.currentnode = "peace_indian";
						if (drand(9) > 8) LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, true, "LandEnc_CaribBeforeDialog");
						else LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, true, "LandEnc_MiskitoBeforeDialog");
					}
					LAi_group_MoveCharacter(chr, "CaribGroup_" + location.index);
					i++;
					model[iMassive] = "";
				}
			}
			str = "EncCarib_" + location.index;
			pchar.quest.(str).win_condition.l1        = "locator";
			pchar.quest.(str).win_condition.l1.location = location.id;
			pchar.quest.(str).win_condition.l1.locator_group = "encdetector";
			pchar.quest.(str).win_condition.l1.locator = encGroup;
			pchar.quest.(str).win_condition = "LandEnc_CaribBegin";
			pchar.quest.(str).EncQty = num; 
			pchar.quest.(str).LocIdx = location.index;
			pchar.GenQuest.LandEnc.LocId = location.id;
			str = "TimeCarib_" + location.index;
			pchar.quest.(str).win_condition.l1            = "Timer";
			pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.(str).win_condition               = "LandEnc_CaribOver";	
			pchar.quest.(str).LocIdx = location.index;
		break;
		
		
		case 2:				
			if(rand(12) > 6) return false;	
			if(CheckAttribute(location, "onUninhabitedIsland") || location.type == "seashore" || location.type == "mayak") return false; 
			num = GetAttributesNum(grp); 
			if (num < 2) return false;
			if(CheckAttribute(pchar, "GenQuest.EncGirl")) return false;		
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock")) return false;
			if (CheckAttribute(pchar, "questTemp.Sharlie.DefendSP")) return false;
			if (!CheckAttribute(location, "locators.reload.reloadW_back"))
			{
				if (sti(pchar.rank) > 6) 
				{
					if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5/num);
					else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*1.6/num);
				}
				else iRank = sti(pchar.rank);
	
				
				LAi_group_Delete("EnemyFight");
				LAi_group_Delete("LandEncGroup");
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
				LAi_SetFightMode(pchar, false);
				LAi_LockFightMode(pchar, true);
				chrDisableReloadToLocation = true;
				
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
				i = 0;
				while(i < num)
				{
					iMassive = rand(9);
					if (model[iMassive] != "")
					{
						
						locator = GetAttributeName(GetAttributeN(grp, i));
						if (i == 0)
						{	
							switch(rand(2)) 
							{
								case 0:
									Log_QuestInfo("������ � �������� : ���������� ������� 1");
									iChar =	NPC_GenerateCharacter("CangGirl", "women_"+(rand(5)+11), "woman", "towngirl", 5, iNation, -1, false, "citizen");
									chr = &characters[iChar];
									chr.dialog.filename = "Enc_RapersGirl_dialog.c";
									chr.dialog.currentnode = "Begin_1";
									pchar.GenQuest.EncGirl = "Begin_1";
								break;
								case 1:	
									Log_QuestInfo("������ � �������� : ���������� ������� 2");	
									iChar =	NPC_GenerateCharacter("CangGirl", "women_"+(rand(5)+11), "woman", "towngirl", 5, iNation, -1, false, "citizen");
									chr = &characters[iChar];
									chr.dialog.filename = "Enc_RapersGirl_dialog.c";
									chr.dialog.currentnode = "Begin_2";
									pchar.GenQuest.EncGirl = "Begin_2";
									pchar.GenQuest.EncGirl.Horse = true;									
								break;
								case 2:								
									Log_QuestInfo("������ � �������� : ���������� ������� 3");
									iChar =	NPC_GenerateCharacter("CangGirl", "women_"+(rand(5)+11), "woman", "towngirl", 5, iNation, -1, false, "citizen");
									chr = &characters[iChar];
									chr.dialog.filename = "Enc_RapersGirl_dialog.c";
									chr.dialog.currentnode = "Begin_3";
									pchar.GenQuest.EncGirl = "Begin_3";
								break;								
							}
							chr.name = GenerateRandomName_Generator(iNation, "woman");			
							chr.lastname = "";
							chr.greeting = "rapers_girl_1";
							ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
							LAi_SetActorType(chr);
							LAi_group_MoveCharacter(chr, "LandEncGroup");
							LAi_ActorDialog(chr, pchar, "", -1, 0);  
							LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "LandEnc_RapersBeforeDialog");
							str = location.index;
							pchar.GenQuest.EncGirl.city = sCity; 
							pchar.GenQuest.EncGirl.nation = iNation; 
							pchar.GenQuest.EncGirl.name = GetFullName(chr); 
							pchar.GenQuest.EncGirl.LocIdx = location.index; 
							chr.city = sCity;
							i++;
							continue;
						}
						chr = GetCharacter(NPC_GenerateCharacter("GangMan_" + i, model[iMassive], "man", "man", iRank, PIRATE, 100, true, "marginal"));
						SetFantomParamFromRank(chr, iRank, true);
						chr.dialog.filename = "Enc_Rapers_dialog.c";
						chr.dialog.currentnode = "First time";
						chr.greeting = "banditos";
						ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
						LAi_SetActorType(chr);
						LAi_group_MoveCharacter(chr, "EnemyFight");
						LAi_ActorFollow(chr, &characters[iChar], "", -1);
						LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "LandEnc_RapersBeforeDialog");
						i++;
						model[iMassive] = "";
					}
				}
				iRnd = 1;
				if(sti(pchar.rank) > 10) iRnd = 2;
				pchar.GenQuest.EncGirl.variant = rand(iRnd);	
				pchar.GenQuest.EncGirl.item = GenQuest_GenerateArtefact();
				pchar.GenQuest.EncGirl.sum  =  500 * (sti(pchar.rank) + 10) + rand(5000);
				sGlobalTemp = "";
				
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
				pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			}
			else
			{
				LAi_group_Delete("LandEncGroup");
    			aref arRld, arDis;
				makearef(arRld, Locations[sti(location.index)].reload);
    			int	Qty = GetAttributesNum(arRld);
				str = "none";
				for (int a=0; a<Qty; a++)
    			{
    				arDis = GetAttributeN(arRld, a);
    				if (arDis.name == "reloadW_back")
    				{
						str = arDis.go; 
    				}
    			}
				if (str == "none") return false; 
				
				locator = GetAttributeName(GetAttributeN(grp, 1));
				chr =	GetCharacter(NPC_GenerateCharacter("FriendGirl", "women_"+(rand(5)+11), "woman", "towngirl", 5, iNation, 0, false, "citizen"));
				chr.dialog.filename = "Enc_FriendGirl_dialog.c";
				chr.dialog.currentnode = "First time";
				chr.greeting = "rapers_girl_1";
				ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
				LAi_SetActorType(chr);
				LAi_group_MoveCharacter(chr, "LandEncGroup");
				LAi_ActorDialog(chr, pchar, "", -1, 0); 
				pchar.GenQuest.EncGirlF.locationId = str; 
				pchar.GenQuest.EncGirlF.nation = iNation; 
				pchar.GenQuest.EncGirlF.name = GetFullName(chr); 
				pchar.quest.Enc_FriendGirl_after.win_condition.l1 = "NPC_Death";
				pchar.quest.Enc_FriendGirl_after.win_condition.l1.character = "FriendGirl";
				pchar.quest.Enc_FriendGirl_after.win_condition = "Enc_FriendGirl_after";				
			}						
		break;
		
		case 3:
			LAi_group_Delete("LandEncGroup");
			if (rand(10) > 7) return false;	
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock")) return false;
			locator = GetAttributeName(GetAttributeN(grp, 0));
			chr = GetCharacter(NPC_GenerateCharacter("Walker", "miskito_"+(rand(5)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true, "native"));
				SetFantomParamFromRank(chr, sti(pchar.rank), true);
			chr.name = GetIndianName(MAN);
			chr.lastname = "";
			chr.greeting = "item_indian";
			chr.dialog.filename = "Enc_Indian.c";
			chr.dialog.currentnode = "First time";
			LAi_SetCitizenType(chr);
			LAi_group_MoveCharacter(chr, "LandEncGroup");
			ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
			chr.Merchant.type = "indian";
			chr.money = TRADER_MIN_MONEY;
		break;
		
		case 4:
			if (rand(10) > 3) return false;
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock")) return false;
			if (CheckAttribute(pchar, "questTemp.Sharlie.DefendSP")) return false;
			if(CheckAttribute(location, "onUninhabitedIsland")) return false; 
			
			num = GetAttributesNum(grp); 
			if (num <= 0) num = 1;
			if (sti(pchar.rank) > 14) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5/num);
			else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*1.6/num);
			
			
			str = "Patrol"+ location.index + "_";
			string sGroup = "PatrolGroup_" + location.index; 
			LAi_group_Register("PatrolGroup_" + location.index);
			for(i = 0; i < num; i++)
			{
				if (i == 0)
				{					
					chr = GetCharacter(NPC_GenerateCharacter(str + i, "off_"+NationShortName(iNation)+"_"+(rand(1)+1), "man", "man", iRank+2, iNation, 1, true, "officer"));
					SetFantomParamFromRank(chr, iRank+2, true);
				}
				else
				{
					if (i == 3)
					{
						chr = GetCharacter(NPC_GenerateCharacter(str + i, "mush_" + NationShortName(iNation) + "_" +(rand(2)+1), "man", "mushketer", iRank, iNation, 1, false, "soldier"));
						
					}
					else
					{
						chr = GetCharacter(NPC_GenerateCharacter(str + i, "sold_"+NationShortName(iNation)+"_"+(rand(7)+1), "man", "man", iRank, iNation, 1, true, "soldier"));
						SetFantomParamFromRank(chr, iRank, true);
					}
				}
				chr.City = sCity;
				chr.CityType = "soldier";				
				chr.greeting = "patrol";
				chr.dialog.filename = "Enc_Patrol.c";
				chr.EncQty = num;
				LAi_SetStayType(chr);
				LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "LandEnc_PatrolBeforeDialog");
				LAi_group_MoveCharacter(chr, sGroup);
				
				locator = GetAttributeName(GetAttributeN(grp, i));
				ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
			}
			LAi_group_SetLookRadius(sGroup, 100);
			LAi_group_SetHearRadius(sGroup, 100);

			str = "EncPatrol_" + location.index;
			pchar.quest.(str).win_condition.l1        = "locator";
			pchar.quest.(str).win_condition.l1.location = location.id;
			pchar.quest.(str).win_condition.l1.locator_group = "encdetector";
			pchar.quest.(str).win_condition.l1.locator = encGroup;
			pchar.quest.(str).win_condition = "LandEnc_PatrolBegin";
			pchar.quest.(str).EncQty = num; 
			pchar.quest.(str).LocIdx = location.index; 
			str = "TimePatrol_" + location.index;
			pchar.quest.(str).win_condition.l1            = "Timer";
			pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.(str).win_condition               = "LandEnc_PatrolOver";	
			pchar.quest.(str).LocIdx = location.index;
			str = location.index;
			pchar.GenQuest.(str).nation = iNation; 
		break;
		
		
		case 5:
			if(rand(15) > 3 || CheckAttribute(pchar, "GenQuest.Convict") || location.type == "seashore" || location.type == "mayak" ) return false;	
			if(CheckAttribute(location, "onUninhabitedIsland")) return false; 
			if (sAreal == "Panama") return false;
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock")) return false;
			num = GetAttributesNum(grp); 
			if(num <= 1) return false;
			if (num <= 2) num = 2;
			iRank = 2 + rand(3); 
						
			model[0] = "prizon_1";
			model[1] = "prizon_2";
			model[2] = "prizon_3";
			model[3] = "prizon_4";
			model[4] = "prizon_5";
			model[5] = "prizon_6";
			model[6] = "prizon_7";
			model[7] = "prizon_8";
			model[8] = "prizon_3";
			model[9] = "prizon_4";

			i = 0;
			pchar.GenQuest.Convict.ConvictQty = num;
			pchar.GenQuest.Convict.city = sCity;

			chrDisableReloadToLocation = true;
			
			while(i < num)
			{
				iMassive = rand(9);
				
				if(model[iMassive] != "")
				{
					chr = GetCharacter(NPC_GenerateCharacter("Convict_" + i, model[iMassive], "man", "man_B", iRank, PIRATE, -1, true, "slave"));
					SetFantomParamFromRank(chr, iRank, true);
					locator = GetAttributeName(GetAttributeN(grp, i));
					ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
					chr.dialog.filename = "GenQuests_Dialog.c";
					chr.dialog.currentnode = "First time";
					chr.greeting = "convict"; 
					chr.city = sCity;
					LAi_SetImmortal(chr, true); 
					LAi_SetActorTypeNoGroup(chr);
						
					if(i == 0)
					{
						LAi_ActorDialog(chr, pchar, "", -1, 0.0);
					}
					else
					{
						LAi_ActorFollow(chr, pchar, "", -1);
					}
						
					LAi_Group_MoveCharacter(chr, "ConvictGroup");
					LAi_Group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
						
					i++;
					model[iMassive] = "";				
				}
			}
			
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			pchar.GenQuest.Convict.Item = GenQuest_GenerateArtefact();
				
			iRnd = rand(9);
			if(iRnd <= 5) pchar.GenQuest.Convict.variant = 1;
			if(iRnd > 5 && iRnd < 8) pchar.GenQuest.Convict.variant = 2;
			if(iRnd >= 8) pchar.GenQuest.Convict.variant = 3;				
			pchar.GenQuest.Convict.var = rand(2);
			Log_TestInfo("���������: ���������� �����");			
		break
				
		
		case 6:
			if (rand(10) > 6 && !bBettaTestMode) return false;
			if(CheckAttribute(PChar, "GenQuest.JusticeOnSale")) return false;
			if(CheckAttribute(PChar, "questTemp.Sharlie.Lock")) return false;
			if(CheckAttribute(location, "onUninhabitedIsland") || location.type == "seashore" || location.type == "mayak") return false; 
			num = GetAttributesNum(grp) - rand(2); 
			if (num <= 0 ) num = 1; 
			
			
			if (sti(pchar.rank) > 6) 
			{
				if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5/num);
				else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*1.6/num);
			}
			else iRank = sti(pchar.rank); 
			
			
			
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
			
			LAi_grp_alarmactive = false;
			LAi_group_ClearAllTargets();
			
			i = 0;
			while(i < num)
			{
				iMassive = rand(9);
				if (model[iMassive] != "")
				{
					chr = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_Jungle_" + i, model[iMassive], "man", "man", iRank, iNation, 0, true, "marginal"));
					SetFantomParamFromRank(chr, iRank, true);
					
					locator = GetAttributeName(GetAttributeN(grp, i));
					ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
					chr.dialog.filename = "GenQuests_Dialog.c";
					chr.dialog.currentnode = "First time";
					chr.greeting = "smuggler"; 
					
					LAi_SetCitizenType(chr);
					LAi_group_MoveCharacter(chr, "JusticeOnSaleGroup_" + location.index);
					
					i++;
					model[iMassive] = "";
				}
			}
			if (sCity == "Panama") sCity = "Portobello";
			PChar.GenQuest.JusticeOnSale.EncQty = num;
			PChar.GenQuest.JusticeOnSale.CityId = sCity;
			PChar.GenQuest.JusticeOnSale.ShoreId = SelectQuestShoreLocation();
			PChar.GenQuest.JusticeOnSale.SmugglerName = GenerateRandomName_Generator(PIRATE, "man");
			
			PChar.Quest.JusticeOnSale_LocationExit.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.JusticeOnSale_LocationExit.win_condition.l1.location = PChar.location;
			PChar.Quest.JusticeOnSale_LocationExit.function = "JusticeOnSale_LocationExit";
			
			Log_TestInfo("���������� ����� '���������� �� �������'");
			Log_TestInfo("��� ��������: " + PChar.GenQuest.JusticeOnSale.SmugglerName);
			Log_TestInfo("Id �����: " + PChar.GenQuest.JusticeOnSale.ShoreId);
		break;
		
		
		
		case 7:
			
			if(num <= 0) return false;
			if(rand(4) == 1 && CheckAttribute(location, "onUninhabitedIsland") && !CheckAttribute(location, "deadlocked") && !CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited") && !CheckAttribute(pchar, "GenQuest.ShipWreck") && reload_cur_island_index > -1)
			{
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
				
				i = 0;
				iRank = sti(PChar.rank) + MOD_SKILL_ENEMY_RATE;
				
				num = 2 + makeint(MOD_SKILL_ENEMY_RATE / 3) + dRand(1); 
				PChar.GenQuest.PiratesOnUninhabited.PiratesQty = num;
				
				while(i < num)
				{
					iMassive = rand(9);
					
					if(model[iMassive] != "")
					{
						chr = GetCharacter(NPC_GenerateCharacter("PirateOnUninhabited_" + i, model[iMassive], "man", "man", iRank, PIRATE, -1, true, "marginal"));
						SetFantomParamFromRank(chr, iRank, true);
						locator = GetAttributeName(GetAttributeN(grp, i));
						ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
						
						chr.dialog.filename = "GenQuests_Dialog.c";
						chr.dialog.currentnode = "First time";
						chr.greeting = "robinzons_1"; 
						LAi_SetImmortal(chr, true); 
						LAi_SetActorTypeNoGroup(chr);
						
						if(i == 0)
						{
							LAi_ActorDialog(chr, PChar, "", -1, 0.0);
						}
						else
						{
							LAi_ActorFollow(chr, PChar, "", -1);
						}
						
						LAi_Group_MoveCharacter(chr, "PiratesOnUninhabitedGroup");
						LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
						
						i++;
						model[iMassive] = "";
					}
				}
				
				PChar.quest.PiratesOnUninhabited_LocExit.win_condition.l1 = "ExitFromLocation";
				PChar.quest.PiratesOnUninhabited_LocExit.win_condition.l1.location = PChar.location;
				PChar.quest.PiratesOnUninhabited_LocExit.function = "PiratesOnUninhabited_LocationExit";
				
				Log_TestInfo("������ �� ����������: ���������� �����");
			}
		break;
		
		
		case 8:
			if(num <= 0) return false;
			if(rand(4) == 1 && !CheckAttribute(pchar, "GenQuest.PiratesOnUninhabited") && !CheckAttribute(pchar, "GenQuest.ShipWreck") && pchar.location == pchar.location.from_sea)
			{
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

				i = 0;
				iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
				
				num = 3 + dRand(5); 
				pchar.GenQuest.ShipWreck.Qty = num;	
				pchar.GenQuest.ShipWreck.Nation = drand(3); 
				pchar.GenQuest.ShipWreck.Prize = GenQuest_GeneratePrize();
				
				while(i < num)
				{
					iMassive = rand(9);
					
					if(model[iMassive] != "")
					{
						chr = GetCharacter(NPC_GenerateCharacter("ShipWreck_" + i, model[iMassive], "man", "man", iRank, sti(pchar.GenQuest.ShipWreck.nation), -1, true, "citizen"));
						SetFantomParamFromRank(chr, iRank, true);
						locator = GetAttributeName(GetAttributeN(grp, i));
						ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
						
						FaceMaker(chr);
						CirassMaker(chr);
						chr.dialog.filename = "GenQuests_Dialog.c";
						chr.dialog.currentnode = "First time";
						chr.greeting = "robinzons_2"; 
						LAi_SetImmortal(chr, true); 
						LAi_SetActorTypeNoGroup(chr);
						
						if(i == 0)
						{
							pchar.GenQuest.ShipWreck.Name = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
							chr.name = pchar.GenQuest.ShipWreck.Name;
							chr.lastname = "";
							LAi_ActorDialog(chr, pchar, "", -1, 0); 
						}
						else
						{
							LAi_ActorFollow(chr, pchar, "", -1);
						}
						
						LAi_Group_MoveCharacter(chr, "ShipWreckGroup");
						LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
						
						i++;
						model[iMassive] = "";
					}
				}
				SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);				
				Log_TestInfo("���������������: ���������� �����");				
			}
		break;
	}
	return true;
}

bool LAi_CreateCaveEncounters(ref location) 
{
	if (CheckAttribute(location, "type") && location.type == "cave")
	{
		if (!bLandEncountersGen) 
		{		
			bLandEncountersGen = true;
			return false;
		}
		if(CheckAttribute(location, "DisableEncounters")) return false;
		if (CheckAttribute(location, "enc") && GetNpcQuestPastDayParam(location, "enc") < 1) return false;
		if (findsubstr(location.id, "Ksochitam_" , 0) != -1 || findsubstr(location.id, "mine_" , 0) != -1) return false;
		if (CheckAttribute(pchar, "questTemp.Sharlie.Lock")) return false;
		if (location.id == "Bermudes_Cavern" || location.id == "FortFrance_Dungeon") return false; 
		if (drand(12) > 5) return false;
		
		
		ref chr, rItm;
		int i, num, iMassive;
		string str, locator, sItm, sJew, sGem, sMin;
		string model[10];
		float locx, locy, locz;
		int iRank = 8+sti(pchar.rank)+makeint(MOD_SKILL_ENEMY_RATE)/2;
		switch(rand(4))
		{
			case 0: 
				str = "CaveBandos"+ location.index + "_";
				num = 4;
				i = 0;
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
				while(i < num)
				{
					iMassive = rand(9);
					
					if(model[iMassive] != "")
					{
						chr = GetCharacter(NPC_GenerateCharacter(str+i, model[iMassive], "man", "man", iRank, PIRATE, 1, true, "marginal"));
						SetFantomParamFromRank(chr, iRank, true);
						chr.dialog.filename = "CaveEnc_dialog.c";
						chr.greeting = "banditos";
						LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "CaveEnc_RaidersBeforeDialog"); 
						if(!CheckAttribute(location, "nofire")) 
						{
							chr.dialog.currentnode = "CaveBanditosSit";
							rItm = ItemsFromID("fire");
							rItm.shown = true;
							rItm.startLocation = location.id;
							rItm.startLocator = "fire";
							location.fire = true;
							CreateFireParticles("goto", "fire");
							locator = "ass"+(i+1);
							ChangeCharacterAddressGroup(chr, location.id, "goto", locator);
							LAi_SetGroundSitTypeNoGroup(chr);
						}
						else 
						{
							chr.dialog.currentnode = "CaveBanditosStay";
							GetCharacterPos(pchar, &locx, &locy, &locz);
							ChangeCharacterAddressGroup(chr, location.id, "monsters", LAi_FindFarFreeLocator("monsters", locx, locy, locz));
							LAi_SetGuardianType(chr);
							chr.protector = true;
						}
						if (drand(14) == 1) 
						{
							chr.dialog.currentnode = "CaveBanditosTreasure";
							chr.SaveItemsForDead = true;
							AddMoneyToCharacter(chr, 2000+drand(2000));
							TakeNItems(chr, "gold_dublon", drand(25));
							if (drand(5) == 1) TakeNItems(chr, "chest", 1);
							if (drand(10) == 2) TakeNItems(chr, "icollection", 1);
							if (drand(7) == 0) TakeNItems(chr, "jewelry1", drand(50));
							if (drand(7) == 1) TakeNItems(chr, "jewelry2", drand(30));
							if (drand(7) == 2) TakeNItems(chr, "jewelry3", drand(40));
							if (drand(7) == 3) TakeNItems(chr, "jewelry4", drand(30));
							if (drand(7) == 4) TakeNItems(chr, "jewelry5", drand(100));
							if (drand(7) == 5) TakeNItems(chr, "jewelry6", drand(200));
							if (drand(7) == 6) TakeNItems(chr, "jewelry52", drand(200));
							if (drand(7) == 7) TakeNItems(chr, "jewelry53", drand(500));
						}
						i++;
						model[iMassive] = "";
					}
				}
				pchar.GenQuest.LandEnc.LocId = location.id;
				str = "TimeCaveRaiders_" + location.index;
				pchar.quest.(str).LocIdx = location.index;
				pchar.quest.(str).win_condition.l1 = "Timer";
				pchar.quest.(str).win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition = "CaveEnc_RaidersOver";
				SaveCurrentNpcQuestDateParam(location, "enc");
			break;
			
			case 1: 
				str = "CaveBandos"+ location.index + "_";
				num = 4;
				i = 0;
				model[0] = "canib_1";
				model[1] = "canib_2";
				model[2] = "canib_3";
				model[3] = "canib_4";
				model[4] = "canib_5";
				model[5] = "canib_6";
				model[6] = "canib_1";
				model[7] = "canib_2";
				model[8] = "canib_3";
				model[9] = "canib_4";
				while(i < num)
				{
					iMassive = rand(9);
					
					if(model[iMassive] != "")
					{
						chr = GetCharacter(NPC_GenerateCharacter(str+i, model[iMassive], "man", "man", iRank+5, PIRATE, 1, true, "native"));
						SetFantomParamFromRank(chr, iRank+5, true);
						chr.dialog.filename = "CaveEnc_dialog.c";
						chr.greeting = "indiano";
						chr.name = GetIndianName(MAN);
						chr.lastname = "";
						LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "CaveEnc_RaidersBeforeDialog"); 
						if(!CheckAttribute(location, "nofire")) 
						{
							chr.dialog.currentnode = "CaveCaribSit";
							rItm = ItemsFromID("fire");
							rItm.shown = true;
							rItm.startLocation = location.id;
							rItm.startLocator = "fire";
							location.fire = true;
							CreateFireParticles("goto", "fire");
							locator = "ass"+(i+1);
							ChangeCharacterAddressGroup(chr, location.id, "goto", locator);
							LAi_SetGroundSitTypeNoGroup(chr);
						}
						else 
						{
							chr.dialog.currentnode = "CaveCaribStay";
							GetCharacterPos(pchar, &locx, &locy, &locz);
							ChangeCharacterAddressGroup(chr, location.id, "monsters", LAi_FindFarFreeLocator("monsters", locx, locy, locz));
							LAi_SetGuardianType(chr);
							chr.protector = true;
						}
						if (drand(10) == 0) 
						{
							chr.SaveItemsForDead = true;
							if (drand(3) == 0) TakeNItems(chr, "jewelry5", drand(100));
							if (drand(3) == 1) TakeNItems(chr, "jewelry6", drand(150));
							if (drand(3) == 2) TakeNItems(chr, "jewelry52", drand(300));
							if (drand(3) == 3) TakeNItems(chr, "jewelry53", drand(700));
						}
						i++;
						model[iMassive] = "";
					}
				}
				pchar.GenQuest.LandEnc.LocId = location.id;
				str = "TimeCaveRaiders_" + location.index;
				pchar.quest.(str).LocIdx = location.index;
				pchar.quest.(str).win_condition.l1 = "Timer";
				pchar.quest.(str).win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition = "CaveEnc_RaidersOver";
				SaveCurrentNpcQuestDateParam(location, "enc");
			break;
			
			case 2: 
				str = "CaveWalker"+location.index;
				chr = GetCharacter(NPC_GenerateCharacter(str, "miskito_"+(rand(5)+1), "man", "man", iRank, PIRATE, 1, true, "native"));
				SetFantomParamFromRank(chr, iRank, true);
				chr.name = GetIndianName(MAN);
				chr.lastname = "";
				chr.greeting = "item_indian";
				chr.dialog.filename = "Enc_Indian.c";
				chr.dialog.currentnode = "First time";
				LAi_SetWarriorType(chr);
				GetCharacterPos(pchar, &locx, &locy, &locz);
				ChangeCharacterAddressGroup(chr, location.id, "monsters", LAi_FindFarFreeLocator("monsters", locx, locy, locz));
				chr.Merchant.type = "indian";
				chr.money = TRADER_MIN_MONEY;
				SaveCurrentNpcQuestDateParam(location, "enc");
			break;
			
			case 3: 
				if(CheckAttribute(location, "id.label") && location.id.label == "Grot") return false;
				str = "CaveSkelet"+ location.index + "_";
				sTotalTemp = str;
				for(i=0; i<4; i++)
				{
					chr = GetCharacter(NPC_GenerateCharacter(str+i, "skel"+(rand(3)+1), "man", "man", iRank, PIRATE, 1, true, "marginal"));
					RemoveAllCharacterItems(chr, true);
					chr.SaveItemsForDead = true;
					chr.DontClearDead = true; 
					CaveEnc_FillSkeleton(chr, i);
					LAi_SetWarriorType(chr);
					GetCharacterPos(pchar, &locx, &locy, &locz);
					ChangeCharacterAddressGroup(chr, location.id, "monsters", LAi_FindFarFreeLocator("monsters", locx, locy, locz));
				}
				DoQuestCheckDelay("CaveEnc_SkeletDie", 1.3);
				SaveCurrentNpcQuestDateParam(location, "enc");
			break;
			
			case 4: 
				str = location.id;
				sJew = "jewelry"+(drand(11)+12);
				sGem = "jewelry"+(drand(5)+1);
				sMin = "mineral"+(drand(13)+13);
				switch (drand(2))
				{
					case 0: sItm = "indian_"+(drand(10)+1); break;
					case 1: sItm = "amulet_"+(drand(10)+1); break;
					case 2: sItm = "obereg_"+(drand(10)+1); break;
				}
				pchar.GenQuestBox.(str) = true;
				if (drand(10) == 0) pchar.GenQuestBox.(str).box1.items.gold_dublon = drand(100);
				if (drand(10) == 1) pchar.GenQuestBox.(str).box1.items.chest = drand(1);
				if (drand(10) == 2) pchar.GenQuestBox.(str).box1.items.jewelry7 = drand(3);
				if (drand(10) == 3) pchar.GenQuestBox.(str).box1.items.jewelry5 = drand(100);
				if (drand(10) == 4) pchar.GenQuestBox.(str).box1.items.jewelry6 = drand(200);
				if (drand(10) == 5) pchar.GenQuestBox.(str).box1.items.jewelry6 = drand(200);
				if (drand(10) > 5) pchar.GenQuestBox.(str).box1.items.(sMin) = 1;
				if (drand(7) == 0) pchar.GenQuestBox.(str).box1.items.(sItm) = 1;
				if (drand(7) == 1) pchar.GenQuestBox.(str).box1.items.(sJew) = drand(20);
				if (drand(7) == 2) pchar.GenQuestBox.(str).box1.items.(sGem) = drand(30);
				SaveCurrentNpcQuestDateParam(location, "enc");
			break;
		}
		return true;
	}
	return false;
}

void LAi_CreateParticles(ref location)
{
	if (CheckAttribute(location, "fire"))
	{
		CreateFireParticles("goto", "fire");
	}
}
