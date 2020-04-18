 



#define LAI_TYPE_LSCOUT		"LSCout"



void LAI_type_LSCout_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.type") == false)
	{
		isNew = true;
	}
	else
	{
		if(chr.chr_ai.type != LAI_TYPE_LSCOUT) isNew = true;
	}
	if(isNew)
	{
		DeleteAttribute(chr, "chr_ai.type");
		chr.chr_ai.type = LAI_TYPE_LSCOUT;
		chr.chr_ai.type.locator = "";
		chr.chr_ai.type.state = "stay";
		chr.chr_ai.type.time = rand(5);
		chr.chr_ai.type.notalk = rand(10);
		chr.chr_ai.type.look_around = 0;
		chr.location.going = true; 
		LAi_tmpl_stay_InitTemplate(chr);
	}
	else
	{
		if(!CheckAttribute(chr, "chr_ai.type.locator")) chr.chr_ai.type.locator = "";
		if(!CheckAttribute(chr, "chr_ai.type.state")) chr.chr_ai.type.state = "stay";
		if(!CheckAttribute(chr, "chr_ai.type.time")) chr.chr_ai.type.time = rand(5);
		if(!CheckAttribute(chr, "chr_ai.type.player")) chr.chr_ai.type.player = "0";
	}
	
	LAi_SetDefaultStayAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}


void LAI_TYPE_LSCout_CharacterUpdate(aref chr, float dltTime)
{
	
	
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return;
	
	if(chr.chr_ai.tmpl != LAI_TMPL_FIGHT && chr.chr_ai.tmpl != LAI_TMPL_AFRAID)
	{
		bool isDialog = false;		
		
		int trg = LAi_group_GetTarget(chr);
		if(trg < 0)
		{			
			float time = stf(chr.chr_ai.type.time) - dltTime;
			chr.chr_ai.type.time = time;
			chr.chr_ai.type.look_around = stf(chr.chr_ai.type.look_around) - dltTime;
			chr.chr_ai.type.notalk = stf(chr.chr_ai.type.notalk) - dltTime;
			if(stf(chr.chr_ai.type.look_around) < 0.0)
			{
				chr.chr_ai.type.look_around = 1.0; 
				int num = FindNearCharacters(chr, 4.0, -1.0, -1.0, 0.01, true, true);
				if(num > 0)
				{
					for(int i = 0; i < num; i++)
					{
						
						int idx = sti(chrFindNearCharacters[i].index);
						by = &Characters[idx];
						if (LAi_CheckFightMode(by))
						{
							
							if (LAi_grp_playeralarm == 0)
							{
								
								LAi_SetFightMode(by, false);
								if(LAi_Character_CanDialog(chr, by))
								{
									chr.chr_ai.type.state = "dialog";
									if (by.id == "Blaze") chr.Dialog.CurrentNode = "LSCNotBlade";
									LAi_tmpl_SetDialog(chr, by, -1.0);
								}
							}
							else
							{
								LAi_tmpl_afraid_SetAfraidCharacter(chr, by, true);
							}							
							return;
						}
						
						if(nMainCharacterIndex == sti(chrFindNearCharacters[i].index))
						{
							break;
						}
					}
					if(i < num)
					{
						
						if(CheckAttribute(chr, "talker"))
						{
							LAi_tmpl_SetDialog(chr, pchar, -1.0);
							DeleteAttribute(chr, "talker");
							return;
						}
						else CharacterTurnByChr(chr, pchar);
					}
					else
					{	
						trg = sti(chrFindNearCharacters[0].index);
						if (stf(chrFindNearCharacters[0].dist) < 2.5 && stf(chr.chr_ai.type.notalk) <= 0.0) 
						{
							isDialog = true;
						}
					}
				}
			}
			
			if(chr.chr_ai.tmpl == LAI_TMPL_GOTO)
			{
				if (isDialog && rand(1))
				{
					if(LAi_Character_CanDialog(chr, &Characters[trg]))
					{
						chr.chr_ai.type.notalk = 15.0 + rand(20);
						Characters[trg].chr_ai.type.notalk = chr.chr_ai.type.notalk;
						if(!LAi_tmpl_SetDialog(chr, &Characters[trg], 3.0 + rand(10)))
						{
							LAI_TYPE_LSCout_Goto(chr);
						}
					}
				}			
				if(LAi_tmpl_goto_IsWait(chr))
				{
					if(rand(100) < 20) LAI_TYPE_LSCout_Goto(chr);
				}
				if (chr.chr_ai.tmpl.state == "wait") LAI_TYPE_LSCout_Goto(chr);
				if (chr.chr_ai.tmpl.state == "falure") LAI_TYPE_LSCout_Goto(chr);
				return;
			}
			
			if(rand(1000) == 125)
			{
				LAi_CharacterPlaySound(chr, "sigh");
			}
			
			if(chr.chr_ai.tmpl == LAI_TMPL_STAY)
			{
				if(trg >= 0) 
				{
					if (isDialog && rand(1))
					{
						ref by = &Characters[trg];
						if(LAi_Character_CanDialog(chr, by))
						{
							chr.chr_ai.type.notalk = 15.0 + rand(20);
							by.chr_ai.type.notalk = chr.chr_ai.type.notalk;
							if(!LAi_tmpl_SetDialog(chr, by, 3.0 + rand(10)))
							{
								LAI_TYPE_LSCout_Goto(chr);
							}
						}
					}
					else
					{
						CharacterTurnByChr(chr, &Characters[trg]);
					}
				}
				else
				{
					if (time < 0.0)
					{
						LAI_TYPE_LSCout_Goto(chr);
					}
				}
			}

		}else{
			
			if(LAi_IsSetBale(chr))
			{
				chr.chr_ai.type.state = "fight";
				if(!LAi_tmpl_SetFight(chr, &Characters[trg]))
				{
					
					LAI_TYPE_LSCout_Stay(chr);
				}
			}else{
				
				LAi_tmpl_afraid_SetAfraidCharacter(chr, &Characters[trg], true);
				LAi_SetAfraidDead(chr);
			}
		}
	}else{
		if(chr.chr_ai.tmpl == LAI_TMPL_FIGHT)
		{
			
			bool isValidate = false;
			trg = LAi_tmpl_fight_GetTarget(chr);
			if(trg >= 0)
			{
				if(LAi_group_ValidateTarget(chr, &Characters[trg]))
				{
					if(!LAi_tmpl_fight_LostTarget(chr))
					{
						isValidate = true;
					}
				}
			}
			if(!isValidate)
			{
				
				trg = LAi_group_GetTarget(chr);
				if(trg >= 0)
				{
					chr.chr_ai.type.state = "fight";
					if(!LAi_tmpl_SetFight(chr, &Characters[trg]))
					{
						
						LAI_TYPE_LSCout_Stay(chr);
					}
				}else{
					LAI_TYPE_LSCout_Stay(chr);
				}
			}
		}
		else
		{
			if(chr.chr_ai.tmpl == LAI_TMPL_AFRAID)
			{
				if(LAi_tmpl_afraid_IsNoActive(chr) && !LAi_grp_alarmactive)
				{
					
					LAi_SetDefaultDead(chr);
					LAI_TYPE_LSCout_Goto(chr);
				}
			}
		}
	}
}


bool LAI_TYPE_LSCout_CharacterLogin(aref chr)
{
	return true;
}


bool LAI_TYPE_LSCout_CharacterLogoff(aref chr)
{
	return true;
}


void LAI_TYPE_LSCout_TemplateComplite(aref chr, string tmpl)
{	
	if(tmpl == "goto")
	{
		LAI_TYPE_LSCout_Stay(chr);
		CharacterTurnByLoc(chr, "goto", chr.chr_ai.type.locator);
		chr.chr_ai.type.locator = "";
	}
}


void LAI_TYPE_LSCout_NeedDialog(aref chr, aref by)
{
}


bool LAI_TYPE_LSCout_CanDialog(aref chr, aref by)
{
	if(chr.chr_ai.type.state == "dialog")
	{
		if(sti(by.index) == nMainCharacterIndex)
		{
			chr.chr_ai.type.state = "stay";
			return true;
		}
		return false;
	}
	if(LAi_CanNearEnemy(chr, 5.0)) return false;
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY) return true;
	if(chr.chr_ai.tmpl == LAI_TMPL_GOTO) return true;
	if(sti(by.index) == nMainCharacterIndex)
	{
		if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG)
		{
			if(LAi_tmpl_dialog_StopNPC(chr)) return true;
		}
	}
	return false;
}


void LAI_TYPE_LSCout_StartDialog(aref chr, aref by)
{
	
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}


void LAI_TYPE_LSCout_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_CharacterRestoreAy(chr);
	bool isSet = false;
	if(chr.chr_ai.type.state == "goto")
	{
		if(chr.chr_ai.type.locator != "")
		{
			LAi_tmpl_goto_InitTemplate(chr);
			LAi_tmpl_goto_SetLocator(chr, "goto", chr.chr_ai.type.locator, -1.0);
			isSet = true;
		}
	}
	if(!isSet)
	{
		LAI_TYPE_LSCout_Stay(chr);
	}
}



void LAI_TYPE_LSCout_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}



void LAI_TYPE_LSCout_Attacked(aref chr, aref by)
{
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG)
	{
		LAi_tmpl_dialog_StopNPC(chr);
	}	
	
	if(!LAi_group_IsEnemy(chr, by)) return;
    
    float dist = -1.0;
	
	if(!GetCharacterDistByChr3D(chr, by, &dist)) return;
	if(dist < 0.0) return;
	if(dist > 20.0) return;
	
	if(LAi_IsSetBale(chr))
	{
		chr.chr_ai.type.state = "fight";
		if(!LAi_tmpl_SetFight(chr, by))
		{
			
			LAI_TYPE_LSCout_Stay(chr);
		}
	}else{
		
		LAi_tmpl_afraid_SetAfraidCharacter(chr, by, true);
		LAi_SetAfraidDead(chr);
	}
    
}


void LAI_TYPE_LSCout_Stay(aref chr)
{
	chr.chr_ai.type.time = 2 + rand(20);
	chr.chr_ai.type.state = "stay";
	LAi_tmpl_stay_InitTemplate(chr);
}


void LAI_TYPE_LSCout_Goto(aref chr)
{
	
	string newloc = chr.location.locator;
	int locQty = 9;
	newloc = strcut(newloc, 4, 5);
	
	if (rand(10) == 5 && sti(chr.location.baseShip.going)) 
	{
		int iTemp = rand(15)+1;
		if (iTemp < 10) newloc = "0" + iTemp;
		else newloc = "" + iTemp;
	}
	if (newloc == "06" || newloc == "07" || newloc == "10" || newloc == "12" || newloc == "13" || newloc == "16")
	{
		locQty = 4;
	}
	newloc = "goto" + newloc + "_" + rand(locQty);
	if(newloc != "")
	{
		LAi_tmpl_goto_InitTemplate(chr);
		LAi_tmpl_goto_SetLocator(chr, "goto", newloc, -1.0);
		chr.chr_ai.type.state = "goto";
		chr.chr_ai.type.locator = newloc;
	}	
}





















