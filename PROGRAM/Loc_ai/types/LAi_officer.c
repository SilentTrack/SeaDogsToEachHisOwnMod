 



#define LAI_TYPE_OFFICER		"officer"



void LAi_type_officer_Init(aref chr)
{
	
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_OFFICER;
	chr.chr_ai.type.bottle = rand(10)+2;
	chr.chr_ai.type.checkTarget = 0;
	if(CheckAttribute(chr, "chr_ai.tmpl"))
	{
		if (chr.chr_ai.tmpl != LAI_TMPL_STAY)
		{
	    	if (!LAi_IsFightMode(GetMainCharacter()))
	        {
	    	    LAi_tmpl_SetFollow(chr, GetMainCharacter(), -1.0);
	    	}
	    	else
	    	{
	            LAi_tmpl_fight_SetWaitState(chr);
	    	}
		}
	}
	else
	{
     	LAi_tmpl_SetFollow(chr, pchar, -1.0);
	}
	
	if (chr.model.animation == "mushketer" && !CheckAttribute(chr, "CanTakeMushket") && !CheckAttribute(chr, "isMusketer.weapon"))
	{
		LAi_NPC_MushketerEquip(chr);
	}
	else
	{
		LAi_SetDefaultStayAnimation(chr);
	}
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

void LAi_type_follower_Init(aref chr)
{
	
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = "follower";
	LAi_tmpl_SetFollow(chr, pchar, -1.0);
	
	LAi_SetDefaultStayAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}


void LAi_type_officer_CharacterUpdate(aref chr, float dltTime)
{
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return;
	string btl = "";
	
	float fCheck = stf(chr.chr_ai.type.bottle) - dltTime;
	if(CheckAttribute(chr, "chr_ai.poison"))
	{
		chr.chr_ai.type.bottle = 6.0;
		if(LAi_GetCharacterRelHP(chr) < 0.8)
		{
			bool antidotUse = false;
			if(LAi_GetCharacterRelHP(chr) < 0.6)
			{
				if(GetCharacterItem(&Characters[sti(chr.index)], "potion4") > 0)
				{
					antidotUse = true;
					DoCharacterUsedItem(&Characters[sti(chr.index)], "potion4");
				}
			}
			if(!antidotUse)
			{
				if(GetCharacterItem(&Characters[sti(chr.index)], "potion3") > 0)
				{
					DoCharacterUsedItem(&Characters[sti(chr.index)], "potion3");
				}
			}
		}
	}
	 
	
	float dist = 0.0;
	float dhlt;
	if(!GetCharacterDistByChr3D(chr, pchar, &dist)) dist = -1.0;
	if(fCheck < 0)	
	{
		chr.chr_ai.type.bottle = 6.0;
		if(!LAi_IsBottleWork(chr))
		{
			if(LAi_GetCharacterRelHP(chr) < 0.7)
			{
				dhlt = LAi_GetCharacterMaxHP(chr) - LAi_GetCharacterHP(chr);
				btl = FindHealthForCharacter(&Characters[sti(chr.index)], dhlt);
				DoCharacterUsedItem(&Characters[sti(chr.index)], btl);
			}
		}
	}
	else chr.chr_ai.type.bottle = fCheck;
	
	if (chr.chr_ai.tmpl == LAI_TMPL_STAY) return; 
	
	if (CheckAttribute(loadedLocation, "noFight")) return;

	
	if (chr.chr_ai.tmpl != LAI_TMPL_FIGHT)
	{
		if(!GetCharacterDistByChr3D(chr, GetMainCharacter(), &dist)) dist = -1.0;
		if (dist < 0.0 || dist > 30)
		{
			if( SendMessage(GetMainCharacter(),"ls",MSG_CHARACTER_EX_MSG,"IsFightMode") == 0)
			{
				LAi_tmpl_SetFollow(chr, GetMainCharacter(), -1.0);
    			return;
			}
		}
	}
	LAi_type_officer_FindTarget(chr);   
	
	if(chr.chr_ai.tmpl == LAI_TMPL_FOLLOW)
	{
		if(dist < 30.0)
		{
			LAi_type_officer_FindTarget(chr);
		}
	}else{
		if(chr.chr_ai.tmpl == LAI_TMPL_FIGHT)
		{
			if(LAi_tmpl_fight_LostTarget(chr))
			{
				LAi_type_officer_FindTarget(chr);
			}else{
				if(LAi_tmpl_fight_IsGo(chr))
				{
					if(dist > 12.0)
					{
						
						if( SendMessage(GetMainCharacter(),"ls",MSG_CHARACTER_EX_MSG,"IsFightMode") == 0)
                        {
						    LAi_tmpl_SetFollow(chr, GetMainCharacter(), -1.0);
						}
					}
				}
				else
				{
					
					fCheck = stf(chr.chr_ai.type.checkTarget) - dltTime;
					chr.chr_ai.type.checkTarget = fCheck;
					if (stf(LAi_grp_relations.distance) > 2.0 && fCheck < 0) 
					{
						LAi_type_officer_FindTarget(chr);
					}
				}
			}
		}
		else
		{
		    LAi_type_officer_FindTarget(chr);
		}
	}
}

void LAi_type_follower_CharacterUpdate(aref chr, float dltTime)
{
}


bool LAi_type_officer_CharacterLogin(aref chr)
{
	return true;
}

bool LAi_type_follower_CharacterLogin(aref chr)
{
	return true;
}


bool LAi_type_officer_CharacterLogoff(aref chr)
{
	return true;
}

bool LAi_type_follower_CharacterLogoff(aref chr)
{
	return true;
}


void LAi_type_officer_TemplateComplite(aref chr, string tmpl)
{
	if(chr.chr_ai.tmpl != LAI_TMPL_FOLLOW)
    {
        if (chr.chr_ai.tmpl != LAI_TMPL_STAY && SendMessage(GetMainCharacter(),"ls",MSG_CHARACTER_EX_MSG,"IsFightMode") == 0) 
        {
            LAi_tmpl_SetFollow(chr, GetMainCharacter(), -1.0);
        }
    }
}

void LAi_type_follower_TemplateComplite(aref chr, string tmpl)
{
	if(chr.chr_ai.tmpl != LAI_TMPL_FOLLOW) LAi_tmpl_SetFollow(chr, pchar, -1.0);
}


void LAi_type_officer_NeedDialog(aref chr, aref by)
{
}

void LAi_type_follower_NeedDialog(aref chr, aref by)
{
}



bool LAi_type_officer_CanDialog(aref chr, aref by)
{
	if(LAi_IsBoardingProcess()) return false;
	
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return false;
	if(chr.chr_ai.tmpl == LAI_TMPL_FIGHT) return false;
	
	return true;
}

bool LAi_type_follower_CanDialog(aref chr, aref by)
{
	if(LAi_IsBoardingProcess()) return false;
	
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return false;
	if(chr.chr_ai.tmpl == LAI_TMPL_FIGHT) return false;
	
	return true;
}


void LAi_type_officer_StartDialog(aref chr, aref by)
{
	
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

void LAi_type_follower_StartDialog(aref chr, aref by)
{
	
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}


void LAi_type_officer_EndDialog(aref chr, aref by)
{
	LAi_CharacterRestoreAy(chr);
	if (chr.chr_ai.tmpl != LAI_TMPL_STAY)
	   LAi_tmpl_SetFollow(chr, GetMainCharacter(), -1.0);
}

void LAi_type_follower_EndDialog(aref chr, aref by)
{
	LAi_CharacterRestoreAy(chr);
	LAi_tmpl_SetFollow(chr, pchar, -1.0);
}



void LAi_type_officer_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{

}



void LAi_type_officer_Attacked(aref chr, aref by)
{
	
	if (LAi_tmpl_fight_GetTarget(chr) == sti(by.index)) return;	
	
	if(!LAi_group_IsEnemy(chr, by)) return;
	float dist = -1.0;
	

	 
	
	dist = -1.0;
	if(!GetCharacterDistByChr3D(chr, by, &dist)) return;
	if(dist < 0.0) return;
	if(dist > 20.0) return;
	
	if(!LAi_tmpl_SetFight(chr, by))
	{
		LAi_type_officer_FindTarget(chr);
	}
}


void LAi_type_officer_FindTarget(aref chr)
{
	
	int trg = LAi_group_GetTarget(chr);
	if(trg >= 0 && LAi_IsSetBale(&Characters[trg]))
	{
		if(LAi_type_officer_CheckDists(chr, &Characters[trg]))
		{
			if(LAi_tmpl_SetFight(chr, &Characters[trg])) 
			{
				chr.chr_ai.type.checkTarget = rand(3) + 2; 
				return;
			}
		}
	}
	trg = LAi_group_GetTarget(pchar);
	if(trg >= 0  && LAi_IsSetBale(&Characters[trg]))
	{
		if(LAi_type_officer_CheckDists(chr, &Characters[trg]))
		{
			chr.chr_ai.type.checkTarget = rand(3) + 2; 
			if(!LAi_tmpl_SetFight(chr, &Characters[trg]))
			{
				
				
				LAi_tmpl_fight_SetWaitState(chr);
			}
		}
	}else{
		if(chr.chr_ai.tmpl != LAI_TMPL_FOLLOW)
		{
            if( SendMessage(GetMainCharacter(),"ls",MSG_CHARACTER_EX_MSG,"IsFightMode") == 0) 
            {
                LAi_tmpl_SetFollow(chr, GetMainCharacter(), -1.0);
            }
		}
	}
}

bool LAi_type_officer_CheckDists(aref chr, aref trg)
{
	float dist = -1.0;
	float searchDist = 10;
	if(CheckAttribute(pchar, "OfficerAttRange")) {
		searchDist = stf(pchar.OfficerAttRange);
	}
	if(!GetCharacterDistByChr3D(pchar, trg, &dist)) dist = -1.0;
	if(dist >= 0.0 && dist < searchDist)
	{
		if(!GetCharacterDistByChr3D(chr, trg, &dist)) dist = -1.0;
		if(dist >= 0.0 && dist < searchDist)
		{
			return true;
		}
	}
	return false;
}


