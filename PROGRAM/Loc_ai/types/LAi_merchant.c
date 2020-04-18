 



#define LAI_TYPE_MERCHANT		"merchant"



void LAi_type_merchant_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_MERCHANT;
	chr.chr_ai.type.state = "stay";
	chr.chr_ai.type.time = "0";
	chr.chr_ai.type.who = "-1";
	chr.chr_ai.type.timewait = "0";
	chr.chr_ai.type.afraid = "0";
	LAi_tmpl_stay_InitTemplate(chr);
	
	LAi_SetDefaultStayAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}


void LAi_type_merchant_CharacterUpdate(aref chr, float dltTime)
{
	float time, tw;
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY)
	{
		
		time = stf(chr.chr_ai.type.time);
		int num = FindNearCharacters(chr, 4.5, -1.0, -1.0, 0.001, false, true);
		if(num > 0)
		{
			if(LAi_type_merchant_FindEnemy(chr, num) < 0)
			{				
				int ichr = sti(chrFindNearCharacters[0].index);
				
				time = time + dltTime;
				chr.chr_ai.type.time = time;
				if(stf(chr.chr_ai.type.who) != ichr)
				{
					chr.chr_ai.type.time = "0";
					chr.chr_ai.type.who = ichr;
				}
				tw = stf(chr.chr_ai.type.timewait);
				tw = tw + dltTime;
				chr.chr_ai.type.timewait = tw;
				if(time < 60.0)
				{
					if(tw > 6.0)
					{
						if(rand(100) < 30)
						{
							
							LAi_type_merchant_Ask(chr);
							chr.chr_ai.type.timewait = "0";
							CharacterTurnByChr(chr, &Characters[ichr]);
						}
					}
				}else{
					LAi_type_merchant_RestoreAngle(chr);
					if(time > 200.0)
					{
						chr.chr_ai.type.time = "0";					
					}				
				}
			}else{
				
				chr.chr_ai.type.afraid = "1";
				LAi_tmpl_ani_PlayAnimation(chr, "afraid", -1.0);
				LAi_SetAfraidDead(chr);
				LAi_type_merchant_RestoreAngle(chr);
			}
		}else{
			chr.chr_ai.type.time = "0";
			chr.chr_ai.type.who = "-1";
			chr.chr_ai.type.timewait = "1";
			LAi_type_merchant_RestoreAngle(chr);
		}
	}else{
		if(chr.chr_ai.tmpl != LAI_TMPL_ANI)
		{
			chr.chr_ai.type.time = "0";
			chr.chr_ai.type.who = "-1";
			chr.chr_ai.type.timewait = "3";
		}else{
			
			time = stf(chr.chr_ai.type.time);
			num = FindNearCharacters(chr, 5.5, -1.0, -1.0, 0.001, false, false);
			if(num > 0)
			{
				if(LAi_type_merchant_FindEnemy(chr, num) < 0) num = 0;
			}
			if(num <= 0)
			{
				if(sti(chr.chr_ai.type.afraid) != 0)
				{
					chr.chr_ai.type.afraid = "0";
					LAi_SetDefaultDead(chr);
					LAi_tmpl_stay_InitTemplate(chr);
				}
			}else{
				LAi_SetAfraidDead(chr);
			}
		}
	}
}


bool LAi_type_merchant_CharacterLogin(aref chr)
{
	return true;
}


bool LAi_type_merchant_CharacterLogoff(aref chr)
{
	return true;
}


void LAi_type_merchant_TemplateComplite(aref chr, string tmpl)
{
	if(chr.chr_ai.tmpl == LAI_TMPL_ANI)
	{
		if(sti(chr.chr_ai.type.afraid) == 0)
		{
			LAi_tmpl_stay_InitTemplate(chr);
		}
	}
}


void LAi_type_merchant_NeedDialog(aref chr, aref by)
{
}


bool LAi_type_merchant_CanDialog(aref chr, aref by)
{
	
	if(chr.chr_ai.type.afraid == "1") return false;
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY) return true;
	if(chr.chr_ai.tmpl == LAI_TMPL_ANI) return true;
	return false;
}


void LAi_type_merchant_StartDialog(aref chr, aref by)
{
	
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}


void LAi_type_merchant_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_CharacterRestoreAy(chr);
}


void LAi_type_merchant_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{

}



void LAi_type_merchant_Attacked(aref chr, aref by)
{
	
}


void LAi_type_merchant_Ask(aref chr)
{
	
	string animation;
	switch(rand(2))
	{
	case 0:
		if (chr.sex == "man") animation = "Merchant_invite";
		else animation = "dialog_stay2";
		break;
	case 1:
		animation = "dialog_stay4";
		break;
	case 2:
		animation = "dialog_stay5";
		break;
	}
	LAi_tmpl_ani_PlayAnimation(chr, animation, 2.0 + frand(2.0));
	
	LAi_CharacterPlaySound(chr, "merchant");
}


void LAi_type_merchant_RestoreAngle(aref chr)
{
	if(CheckAttribute(chr, "location.group"))
	{
		if(CheckAttribute(chr, "location.locator"))
		{
			CharacterTurnByLoc(chr, chr.location.group, chr.location.locator);
		}
	}
}


int LAi_type_merchant_FindEnemy(aref chr, int num)
{
	int i, idx;
	if(LAi_grp_alarmactive == true)
	{
		for(i = 0; i < num; i++)
		{
			idx = sti(chrFindNearCharacters[i].index);
			if(LAi_group_IsEnemy(chr, &Characters[idx])) return idx;
		}
	}
	else
	{
		for(i = 0; i < num; i++)
		{
			idx = sti(chrFindNearCharacters[i].index);
			ref by = &Characters[idx];
			if (LAi_CheckFightMode(by)) return idx;
		}
	}
	return -1;
}



