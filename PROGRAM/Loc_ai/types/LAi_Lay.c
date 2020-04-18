 


#define LAI_TYPE_LAY		"lay"


void LAi_type_lay_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_LAY;
	LAi_tmpl_stay_InitTemplate(chr);
	
	LAi_SetDefaultLayAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}


void LAi_type_lay_CharacterUpdate(aref chr, float dltTime)
{
	string snd = "PEOPLE\snore.wav";
	if(!CheckAttribute(chr,"InDialog"))
	{
		if(rand(300) == 123) { LAi_CharacterPlaySound(chr, snd); }
		else
		{
			if(FindNearCharacters(chr, 2.5, -1.0, 30.0, 0.1, false, false) > 0)
			{
				if(rand(100) == 10) { LAi_CharacterPlaySound(chr, snd); }
			}
		}
	}
}


bool LAi_type_lay_CharacterLogin(aref chr)
{
	return true;
}


bool LAi_type_lay_CharacterLogoff(aref chr)
{
	return true;
}


void LAi_type_lay_TemplateComplite(aref chr, string tmpl)
{
	LAi_tmpl_player_InitTemplate(chr);
}


void LAi_type_lay_NeedDialog(aref chr, aref by)
{
}


bool LAi_type_lay_CanDialog(aref chr, aref by)
{
	
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return false;
	
	return true;
}


void LAi_type_lay_StartDialog(aref chr, aref by)
{
	
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_tmpl_SetActivatedDialog(chr, by);
	LAi_tmpl_dialog_NoAni(chr);
	chr.InDialog = true;
}


void LAi_type_lay_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	if(CheckAttribute(chr,"InDialog")) DeleteAttribute(chr,"InDialog");
}


void LAi_type_lay_Attack(aref attack, aref enemy, float attackDmg, float hitDmg)
{
}


void LAi_type_lay_Block(aref attack, aref enemy, float attackDmg, float hitDmg)
{
}


void LAi_type_lay_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}



void LAi_type_lay_Attacked(aref chr, aref by)
{
	
}
