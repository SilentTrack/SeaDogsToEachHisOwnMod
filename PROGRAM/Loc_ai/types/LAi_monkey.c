

#define LAI_TYPE_MONKEY		"monkey"



void LAi_type_monkey_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_MONKEY;
	LAi_tmpl_stay_InitTemplate(chr);
	
	BeginChangeCharacterActions(chr);
	chr.actions.idle.i1 = "idle_1";
	chr.actions.idle.i2 = "idle_2";
	chr.actions.idle.i3 = "idle_3";
	chr.actions.walk = "walk";
	chr.actions.backwalk = "back walk";
	chr.actions.run = "walk";
	chr.actions.backrun = "back walk";
	chr.actions.stsUp = "walk";
	chr.actions.stsDown = "walk";
	chr.actions.stsUpBack = "back walk";
	chr.actions.stsDownBack = "back walk";
	chr.actions.stsUpRun = "walk";
	chr.actions.stsDownRun = "walk";
	chr.actions.stsUpRunBack = "back walk";
	chr.actions.stsDownRunBack = "back walk";
	chr.actions.turnLeft = "skip";
	chr.actions.turnRight = "skip";
	chr.actions.swim = "walk";	
	chr.actions.fightwalk = "walk";
	chr.actions.fightbackwalk = "back walk";
	chr.actions.fightrun = "walk";
	chr.actions.fightbackrun = "back walk";
	chr.actions.fightidle.i1 = "idle_1";
	chr.actions.fightidle.i2 = "idle_2";
	chr.actions.fightidle.i3 = "idle_3";
	chr.actions.attack.a1 = "attack";
	chr.actions.attacktl.a1 = "attack";
	chr.actions.attacktr.a1 = "attack";
	chr.actions.hit.h1 = "hit";
	chr.actions.block = "block";
	chr.actions.blockhit = "block_hit";
	chr.actions.recoil = "Recoil";
	chr.actions.shot = "skip";
	chr.actions.dead.d1 = "death";
	chr.actions.fightdead.d1 = "death";
	EndChangeCharacterActions(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", true);
}


void LAi_type_monkey_CharacterUpdate(aref chr, float dltTime)
{
	int trg = -1;
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
			if(trg < 0)
			{
				
				LAi_type_monkey_Return(chr);
			}else{
				
				LAi_tmpl_SetFight(chr, &Characters[trg]);
				if(rand(100) < 50)
				{
					LAi_CharacterPlaySound(chr, "monkey");
				}
			}
		}else{
			if(rand(4000) == 1224)
			{
				LAi_CharacterPlaySound(chr, "monkey");
			}
		}
	}else{
		
		trg = LAi_group_GetTarget(chr);
		if(trg >= 0)
		{
			
			LAi_tmpl_SetFight(chr, &Characters[trg]);
			if(rand(100) < 90)
			{
				LAi_CharacterPlaySound(chr, "monkey");
			}
		}
	}
}


bool LAi_type_monkey_CharacterLogin(aref chr)
{
	return true;
}


bool LAi_type_monkey_CharacterLogoff(aref chr)
{
	return true;
}


void LAi_type_monkey_TemplateComplite(aref chr, string tmpl)
{
	if(tmpl == "goto")
	{
		LAi_tmpl_stay_InitTemplate(chr);
		if(CheckAttribute(chr, "location.group"))
		{
			if(CheckAttribute(chr, "location.locator"))
			{
				CharacterTurnByLoc(chr, chr.location.group, chr.location.locator);
			}
		}
	}
}


void LAi_type_monkey_NeedDialog(aref chr, aref by)
{
}


bool LAi_type_monkey_CanDialog(aref chr, aref by)
{
	return false;
}


void LAi_type_monkey_StartDialog(aref chr, aref by)
{
}


void LAi_type_monkey_EndDialog(aref chr, aref by)
{
}


void LAi_type_monkey_Attack(aref attack, aref enemy, float attackDmg, float hitDmg)
{
	if(rand(1000) < 100)
	{
		
		float poison = 0.0;
		if(CheckAttribute(enemy, "chr_ai.poison"))
		{
			poison = stf(enemy.chr_ai.poison);
			if(poison < 1.0) poison = 1.0;
		}		
		enemy.chr_ai.poison = poison + 30 + rand(20);
		Log_SetStringToLog(XI_ConvertString("You've been poisoned"));
	}
}


void LAi_type_monkey_Block(aref attack, aref enemy, float attackDmg, float hitDmg)
{
}


void LAi_type_monkey_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}



void LAi_type_monkey_Attacked(aref chr, aref by)
{
	
}

void LAi_type_monkey_Return(aref chr)
{
	bool isSet = false;
	if(CheckAttribute(chr, "location.group"))
	{
		if(CheckAttribute(chr, "location.locator"))
		{
			isSet = true;
			CharacterTurnByLoc(chr, chr.location.group, chr.location.locator);
		}
	}
	if(isSet)
	{
		LAi_tmpl_goto_InitTemplate(chr);
		LAi_tmpl_goto_SetLocator(chr, chr.location.group, chr.location.locator, -1.0);
	}else{
		LAi_tmpl_stay_InitTemplate(chr);
	}
}
