 



#define LAI_TYPE_STAY		"stay"



void LAi_type_stay_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_STAY;
	chr.chr_ai.type.time = 0;
	LAi_tmpl_stay_InitTemplate(chr);
	
	if (chr.model.animation == "mushketer" && !CheckAttribute(chr, "isMusketer.weapon"))
	{
        LAi_NPC_MushketerEquip(chr);
	}
	else
	{
		LAi_SetDefaultStayAnimation(chr);
	}
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}


void LAi_type_stay_CharacterUpdate(aref chr, float dltTime)
{
	int num = FindNearCharacters(chr, 5.0, -1.0, -1.0, 0.001, true, true);
	int idx;
	bool bVis = false;	
	if(num > 0)
	{
		for(int i = 0; i < num; i++)
		{
			idx = sti(chrFindNearCharacters[i].index);
			if(LAi_group_IsEnemy(chr, &Characters[idx])) break;
			if (CheckAttribute(chr, "talker") && idx == nMainCharacterIndex && LAi_Character_CanDialog(chr, pchar)) 
			{	
				LAi_tmpl_SetDialog(chr, pchar, 1.0); 
				DeleteAttribute(chr, "talker");
				return;
			}
		}
		if(i < num)
		{
			if(chr.chr_ai.tmpl != LAI_TMPL_ANI)
			{
				LAi_tmpl_ani_PlayAnimation(chr, "afraid", -1.0);
				LAi_SetAfraidDead(chr);
			}
		}else{
			if(chr.chr_ai.tmpl != LAI_TMPL_STAY)
			{
				LAi_tmpl_stay_InitTemplate(chr);
				LAi_SetDefaultDead(chr);
			}
		}
	}
	else
	{
		if(chr.chr_ai.tmpl != LAI_TMPL_STAY)
		{
			LAi_tmpl_stay_InitTemplate(chr);
			LAi_SetDefaultDead(chr);
		}
	}
}


bool LAi_type_stay_CharacterLogin(aref chr)
{
	return true;
}


bool LAi_type_stay_CharacterLogoff(aref chr)
{
	return true;
}


void LAi_type_stay_TemplateComplite(aref chr, string tmpl)
{
}


void LAi_type_stay_NeedDialog(aref chr, aref by)
{
}


bool LAi_type_stay_CanDialog(aref chr, aref by)
{
	
	if(chr.chr_ai.tmpl != LAI_TMPL_STAY && by.id != "Blaze") return false;
	
	return true;
}


void LAi_type_stay_StartDialog(aref chr, aref by)
{
	
	LAi_CharacterSaveAy(chr); 
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}


void LAi_type_stay_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_CharacterRestoreAy(chr);
}



void LAi_type_stay_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}



void LAi_type_stay_Attacked(aref chr, aref by)
{
}


