


void OfficersReaction(string alignment)
{
	int iPassenger;
	int i, cn;
	ref sld;
	
	for (int io = 0; io<GetPassengersQuantity(pchar); io++)
	{   
		iPassenger = GetPassenger(pchar, io);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld, "OfficerWantToGo.DontGo") && !IsEquipCharacterByArtefact(sld, "totem_04"))
			{
				if(CheckAttribute(sld, "alignment"))
				{
					if (sld.alignment == alignment)
					{
						sld.loyality = makeint(sld.loyality) + 1;
					}
					else
					{
						sld.loyality = makeint(sld.loyality) - 1;
					}
				}
			}
		}
	}
	for (i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn!=-1)
		{
			sld = GetCharacter(cn);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld, "OfficerWantToGo.DontGo") && !IsEquipCharacterByArtefact(sld, "totem_04"))
			{
				if (sld.alignment == alignment)
				{
					sld.loyality = makeint(sld.loyality) + 1;
					if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, 1); 
				}
				else
				{
					sld.loyality = makeint(sld.loyality) - 1;
					
					if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, -1); 
				}
			}									
		}
	}
}


void ChangeOfficersLoyality(string alignment, int iLoyality)
{ 

	int iPassenger;
	int i, cn;
	ref sld;
	
	for (int io = 0; io<GetPassengersQuantity(pchar); io++)
	{   
		iPassenger = GetPassenger(pchar, io);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld, "OfficerWantToGo.DontGo"))
			{
				switch (alignment)
				{
					case "bad":
						if (sld.alignment == alignment) sld.loyality = makeint(sld.loyality) + iLoyality;				
						else 							sld.loyality = makeint(sld.loyality) - iLoyality;				
					break;
					case "good":
						if (sld.alignment == alignment) sld.loyality = makeint(sld.loyality) + iLoyality;				
						else 							sld.loyality = makeint(sld.loyality) - iLoyality;									
					break;
					case "bad_all":
						sld.loyality = makeint(sld.loyality) - iLoyality;
					break;
					case "good_all":
						sld.loyality = makeint(sld.loyality) + iLoyality;
					break;
				}
			}
		}	
	}
	for (i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn!=-1)
		{
			sld = GetCharacter(cn);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld, "OfficerWantToGo.DontGo"))
			{
				switch (alignment)
				{
					case "bad":
						if (sld.alignment == alignment) {
							sld.loyality = makeint(sld.loyality) + iLoyality;				
							if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, 1); 
						}	
						else 
						{
							sld.loyality = makeint(sld.loyality) - iLoyality;				
							if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, -1); 
						}	
					break;
					case "good":
						if (sld.alignment == alignment) {
							sld.loyality = makeint(sld.loyality) + iLoyality;
							if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, 1); 
						}	
						else 
						{							
							sld.loyality = makeint(sld.loyality) - iLoyality;
							if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, -1); 
						}	
					break;
					case "bad_all":
						sld.loyality = makeint(sld.loyality) - iLoyality;
						if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, -1); 
					break;
					case "good_all":
						sld.loyality = makeint(sld.loyality) + iLoyality;
						if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, 1); 
					break;
				}	
			}									
		}
	}	
}


void OfficersReactionResult()
{
	int iPassenger;
	int i;
	ref sld;
	
	if (LAi_IsCapturedLocation) return;
	if (chrDisableReloadToLocation) return; 
	if (CheckAttribute(Pchar,"questTemp.MunityOfficerIDX") && Pchar.questTemp.MunityOfficerIDX.begin == "1") return;
	
	for (i = 0; i<GetPassengersQuantity(pchar); i++)
	{   
		iPassenger = GetPassenger(pchar, i);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld,"prisoned") && GetRemovable(sld) && !CheckAttribute(sld, "OfficerWantToGo.DontGo"))
			{
				if (sti(sld.loyality) < 1)
				{
					if (PlaceCharacter(sld, "goto", "random_must_be_near") != "")
					{
						sld.dialog.filename = "Enc_Officer_dialog.c";
						sld.dialog.currentnode = "WantToRemove";
				      	if (sld.sex != "woman")
						{
					    	sld.greeting = "Gr_Officer_Fired";
					    }
						DeleteAttribute(sld, "quest.officertype");
	
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", 2.0, 0);
						
			    		
			    		chrDisableReloadToLocation = true;
			    		DoQuestCheckDelay("OpenTheDoors", 5.0);
						break; 
					}
				}
			}
		}
	}
	if (chrDisableReloadToLocation) return; 
	
	if (CheckNPCQuestDate(pchar, "OfficerWantToGo") && rand(1) == 1) 
	{
		SetNPCQuestDate(pchar, "OfficerWantToGo");
		for (i = 0; i<GetPassengersQuantity(pchar); i++)
		{   
			iPassenger = GetPassenger(pchar, i);
			if (iPassenger != -1)
			{
				sld = GetCharacter(iPassenger);
				if (!CheckAttribute(sld,"prisoned") && !CheckAttribute(sld, "OfficerWantToGo.DontGo") && GetRemovable(sld) && rand(10) == 5 && GetNpcQuestPastDayParam(sld, "HiredDate") > 60)
				{
					if (sld.dialog.filename == "Enc_Officer_dialog.c") 
					{
						if (PlaceCharacter(sld, "goto", "random_must_be_near") != "")
						{
							sld.dialog.currentnode = "WantToGo";
		                    sld.greeting           = "Gr_Officer_Salary";
		
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", 2.0, 0);
							
				    		
				    		chrDisableReloadToLocation = true;
				    		DoQuestCheckDelay("OpenTheDoors", 5.0);
							break; 
						}
					}
				}
			}
		}
	}
}

bool isOfficerInShip(ref _chr, bool _withBoard)
{
	if(sti(pchar.Fellows.Passengers.navigator) == sti(_chr.index))
	{
  		return true;
	}

	if(sti(pchar.Fellows.Passengers.boatswain) == sti(_chr.index))
	{
		return true;;
	}

	if(sti(pchar.Fellows.Passengers.cannoner) == sti(_chr.index))
	{
  		return true;
	}

	if(sti(pchar.Fellows.Passengers.doctor) == sti(_chr.index))
	{
  		return true;
	}

	if(sti(pchar.Fellows.Passengers.carpenter) == sti(_chr.index))
	{
  		return true;
	}
    if(sti(pchar.Fellows.Passengers.treasurer) == sti(_chr.index))
	{
  		return true;
	}
	if(_withBoard && IsOfficer(_chr))
	{
		return true;
	}
	return false;
}

void CheckForReleaseOfficer(int iCharIndex)
{
	if(sti(pchar.Fellows.Passengers.navigator) == iCharIndex)
	{
		pchar.Fellows.Passengers.navigator = -1;
		DeleteAttribute(&characters[iCharIndex], "navigator"); 
	}

	if(sti(pchar.Fellows.Passengers.boatswain) == iCharIndex)
	{
		pchar.Fellows.Passengers.boatswain = -1;
		DeleteAttribute(&characters[iCharIndex], "boatswain"); 
	}

	if(sti(pchar.Fellows.Passengers.cannoner) == iCharIndex)
	{
		pchar.Fellows.Passengers.cannoner = -1;
		DeleteAttribute(&characters[iCharIndex], "cannoner"); 
	}

	if(sti(pchar.Fellows.Passengers.doctor) == iCharIndex)
	{
		pchar.Fellows.Passengers.doctor = -1;
		DeleteAttribute(&characters[iCharIndex], "doctor"); 
	}

	if(sti(pchar.Fellows.Passengers.carpenter) == iCharIndex)
	{
		pchar.Fellows.Passengers.carpenter = -1;
		DeleteAttribute(&characters[iCharIndex], "carpenter"); 
	}
	
    if(sti(pchar.Fellows.Passengers.treasurer) == iCharIndex)
	{
		pchar.Fellows.Passengers.treasurer = -1;
		DeleteAttribute(&characters[iCharIndex], "treasurer"); 
	}
	
	
	
		
		RemoveOfficersIndex(pchar, iCharIndex);
		DeleteAttribute(&characters[iCharIndex], "fighter"); 
	
	DeleteAttribute(&characters[iCharIndex], "isfree"); 
}

bool CheckForAllOfficers() 
{
	bool bOk = true;

	if( !CheckAttribute(pchar,"Fellows.Passengers.navigator") || sti(pchar.Fellows.Passengers.navigator) < 0 ) bOk = false; 
	if( !CheckAttribute(pchar,"Fellows.Passengers.boatswain") || sti(pchar.Fellows.Passengers.boatswain) < 0 ) bOk = false; 
	if( !CheckAttribute(pchar,"Fellows.Passengers.cannoner")  || sti(pchar.Fellows.Passengers.cannoner)  < 0 ) bOk = false; 
	if( !CheckAttribute(pchar,"Fellows.Passengers.doctor")    || sti(pchar.Fellows.Passengers.doctor)    < 0 ) bOk = false; 
	if( !CheckAttribute(pchar,"Fellows.Passengers.treasurer") || sti(pchar.Fellows.Passengers.treasurer) < 0 ) bOk = false; 
	if( !CheckAttribute(pchar,"Fellows.Passengers.carpenter") || sti(pchar.Fellows.Passengers.carpenter) < 0 ) bOk = false; 
	
	for(int i=1; i<4; i++)
	{	
		if (sti(GetOfficersIndex(pchar, i)) < 0) bOk = false;			
	}
	return bOk;
}


void SetOfficerParam(ref Npchar, int _type)
{
	float upSkill = 0.7;
	
	ClearCharacterExpRate(Npchar); 

    Npchar.quest.LeadershipModify  = 0;
	Npchar.quest.FencingModify     = 0;
	Npchar.quest.SailingModify     = 0;
	Npchar.quest.AccuracyModify    = 0;
	Npchar.quest.CannonsModify     = 0;
	Npchar.quest.GrapplingModify   = 0;
	Npchar.quest.RepairModify      = 0;
	Npchar.quest.DefenseModify     = 0;
	Npchar.quest.CommerceModify    = 0;
	Npchar.quest.SneakModify       = 0;
	Npchar.quest.PistolModify      = 0;

	SetRandSPECIAL(Npchar);
	Npchar.quest.officertype_2 = "";
    switch(_type)
	{
		case 0:
			Npchar.quest.officertype = "boatswain";
			Npchar.quest.officertype_2 = RandPhraseSimple("I can also be a doctor if I must to. ", "Plus, I can fix bones and heal wounds. ");
			Npchar.quest.LeadershipModify     = frandSmall(2.0);
			Npchar.quest.FencingModify     = Rand(1);
			Npchar.quest.GrapplingModify   = frandSmall(2.0) + 2;
			Npchar.quest.DefenseModify     = frandSmall(2.0) + 2;
			Npchar.quest.SneakModify       = Rand(1);
			
			
            
		break;

		case 1:
			Npchar.quest.officertype = "cannoner";
			Npchar.quest.AccuracyModify      = frandSmall(2.0) + 2;
			Npchar.quest.CannonsModify       = frandSmall(2.0) + 2;
			Npchar.quest.SneakModify         = Rand(1);
			
			
            
		break;

		case 2:
			Npchar.quest.officertype_2 = RandPhraseSimple("I am capable of repairing ships too. ", "I also know how to deal with repair tools. ");
			Npchar.quest.officertype = "treasurer";
			Npchar.quest.RepairModify        = frandSmall(2.0) + 3;
			Npchar.quest.CommerceModify      = frandSmall(2.0) + 2;
			Npchar.quest.SneakModify         = frandSmall(2.0) + 2;
			
			
            
		break;

		case 3:
			Npchar.quest.officertype_2 = RandPhraseSimple("Also got some knowledge of medicine. ", "Not a physician, but can help if need be. ");
			Npchar.quest.officertype = "navigator";
			Npchar.quest.SailingModify        = frandSmall(2.0) + 2;
			Npchar.quest.DefenseModify        = frandSmall(2.0) + 1.3;
			Npchar.quest.SneakModify          = frandSmall(2.0);
			
			
		break;

        case 4:
			Npchar.quest.officertype = "fighter";
			Npchar.quest.FencingModify         = frandSmall(2.0) + 2;
			Npchar.quest.PistolModify          = frandSmall(2.0) + 2;
			
			
            
		break;
        
        case 5:
			
			Npchar.quest.LeadershipModify     = frandSmall(3.0) + 2;
			Npchar.quest.SailingModify        = frandSmall(1.0) + 1;
			Npchar.quest.SneakModify          = Rand(3) + 1;
			
			
            
		break;
		
		case 6:
			
			Npchar.quest.DefenseModify       = Rand(3) + 3;
			Npchar.quest.SneakModify         = Rand(3);
		break;
		
		case 7:
			
			Npchar.quest.RepairModify         = Rand(3) + 3;
			Npchar.quest.SneakModify          = Rand(3);
		break;
	}

	
	Npchar.experience = 0;
    
	
	float MiddleK = GetMiddleMainSkill();

    Npchar.skill.Leadership    = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.FencingS      = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Sailing       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Accuracy      = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Cannons       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Grappling     = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Repair        = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Defence       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Commerce      = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Sneak         = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
    Npchar.skill.Pistol        = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
    Npchar.skill.FencingL      = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
    Npchar.skill.FencingH      = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
    Npchar.skill.Fortune       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;

    CorrectSkillParam(Npchar); 
    

	Npchar.skill.Leadership   = makeint(stf(Npchar.skill.Leadership)   + 10*stf(Npchar.quest.LeadershipModify));
	Npchar.skill.FencingS     = makeint(stf(Npchar.skill.FencingS)     + 10*stf(Npchar.quest.FencingModify));
	Npchar.skill.Sailing      = makeint(stf(Npchar.skill.Sailing)      + 10*stf(Npchar.quest.SailingModify));
	Npchar.skill.Accuracy     = makeint(stf(Npchar.skill.Accuracy)     + 10*stf(Npchar.quest.AccuracyModify));
	Npchar.skill.Cannons      = makeint(stf(Npchar.skill.Cannons)      + 10*stf(Npchar.quest.CannonsModify));
	Npchar.skill.Grappling    = makeint(stf(Npchar.skill.Grappling)    + 10*stf(Npchar.quest.GrapplingModify));
	Npchar.skill.Repair       = makeint(stf(Npchar.skill.Repair)       + 10*stf(Npchar.quest.RepairModify));
	Npchar.skill.Defence      = makeint(stf(Npchar.skill.Defence)      + 10*stf(Npchar.quest.DefenseModify));
	Npchar.skill.Commerce     = makeint(stf(Npchar.skill.Commerce)     + 10*stf(Npchar.quest.CommerceModify));
	Npchar.skill.Sneak        = makeint(stf(Npchar.skill.Sneak)        + 10*stf(Npchar.quest.SneakModify));
    Npchar.skill.Pistol       = makeint(stf(Npchar.skill.Pistol)       + 10*stf(Npchar.quest.PistolModify));
    Npchar.skill.FencingL     = makeint(stf(Npchar.skill.FencingL)     + 10*stf(Npchar.quest.FencingModify));
    Npchar.skill.FencingH     = makeint(stf(Npchar.skill.FencingH)     + 10*stf(Npchar.quest.FencingModify));
    Npchar.skill.Fortune      = makeint(stf(Npchar.skill.Fortune)      + 10*stf(Npchar.quest.SneakModify));

    CorrectSkillParam(Npchar); 

    Npchar.reputation = rand(84) + 5;
    
    Npchar.loyality = 5 + rand(10);
    if (sti(Npchar.reputation) > 41)
    {
        Npchar.alignment = "good";
    }
    else
    {
        Npchar.alignment = "bad";
    }
    SetRankFromSkill(Npchar);

    LAi_NPC_Equip(Npchar, sti(Npchar.rank), true, true); 
    
    SetFantomHP(Npchar);
    
    Npchar.quest.OfficerPrice    = (11 + 2*sti(Npchar.rank))*(150 + MOD_SKILL_ENEMY_RATE*20) + rand(5)*10;
    Npchar.quest.OfficerLowPrice = makeint(sti(Npchar.quest.OfficerPrice)/1.5 + 0.5);
}


int FindFreeRandomOfficer()
{
	int Counter, OfficerIdx;
	string OfficerId;
	
	if (GetCharacterMaxOfficersQty(Pchar) <= (GetOfficerPassengerQuantity(Pchar) + GetCompanionQuantity(Pchar) - 1)) return -1;
	return 1;
}
void LandEnc_OfficerHired()
{
	ref sld = &Characters[sti(Pchar.questTemp.HiringOfficerIDX)];
    sld.Money = 0; 

	AddPassenger(pchar, sld, false);

	sld.location = "None";
	sld.Dialog.CurrentNode = "hired";
	 
	
	sld.Payment = true;  
	sld.DontClearDead = true;  
	
	DeleteAttribute(Pchar, "questTemp.HiringOfficerIDX");
	DeleteAttribute(sld, "LifeDay") 
	SaveCurrentNpcQuestDateParam(sld, "HiredDate"); 
}

void LandEnc_OfficerStay()
{
    SetCharacterTask_Stay(Characters[makeint(Pchar.questTemp.HiringOfficerIDX)]);
    Characters[makeint(Pchar.questTemp.HiringOfficerIDX)].chr_ai.tmpl = LAI_TMPL_STAY;
    DeleteAttribute(Pchar, "questTemp.HiringOfficerIDX");
}   

void LandEnc_OfficerFired()
{
	ref sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
	CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
	RemovePassenger(Pchar, sld);
	RemoveCharacterCompanion(pchar, sld);
	LAi_SetCitizenType(sld);
	sld.location = "none";
	if (sld.sex != "woman")
	{
    	sld.greeting = "Gr_Officer_Fired";
    }
    sld.LifeDay = 0; 
    DeleteAttribute(sld, "Payment"); 
	DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");
}			


bool SetOfficerToMushketer(ref rCharacter, string sMushket, bool _ToMushketer) 
{
	int iItem;
	string sLastGun = "";
	
	if(_ToMushketer && sMushket != "") 
	{
		iItem = GetItemIndex(sMushket);
		if(iItem == -1) return false;
		sLastGun = GetCharacterEquipByGroup(rCharacter, GUN_ITEM_TYPE);
		rCharacter.DefaultAnimation = rCharacter.model.Animation;
		rCharacter.IsMushketer = true; 
		rCharacter.IsMushketer.MushketID = sMushket; 
		rCharacter.IsMushketer.LastGunID = sLastGun; 
		rCharacter.model = rCharacter.model + "_mush";
		rCharacter.model.animation = "mushketer"; 
		Characters_RefreshModel(rCharacter); 
		EquipCharacterByItem(rCharacter, sMushket); 
		rCharacter.Equip.TempGunID = sLastGun; 
		if (!CheckAttribute(rCharacter, "MusketerDistance")) rCharacter.MusketerDistance = 10.0;
		rCharacter.isMusketer = true;
		rCharacter.isMusketer.weapon = true;
		LAi_SetOfficerType(rCharacter);
	}
	else 
	{
		rCharacter.model = FindStringBeforeChar(rCharacter.model, "_mush"); 
		rCharacter.model.Animation = rCharacter.DefaultAnimation;
		Characters_RefreshModel(rCharacter);
		RemoveCharacterEquip(rCharacter, GUN_ITEM_TYPE); 
		if(rCharacter.IsMushketer.LastGunID != "" && GetCharacterItem(rCharacter, rCharacter.IsMushketer.LastGunID) > 0)
		{
			EquipCharacterByItem(rCharacter, rCharacter.IsMushketer.LastGunID); 
		}
		DeleteAttribute(rCharacter, "IsMushketer");
		DeleteAttribute(rCharacter, "Equip.TempGunID");
		DeleteAttribute(rCharacter, "MusketerDistance");
		DeleteAttribute(rCharacter, "isMusketer");
		LAi_SetOfficerType(rCharacter);
	}
	return true;
}
