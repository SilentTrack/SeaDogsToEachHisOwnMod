 



#define LAI_TYPE_OWNER		"owner"



void LAi_type_owner_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_OWNER;
	chr.chr_ai.type.state = "stay";
	chr.chr_ai.type.time = "0";
	chr.chr_ai.type.who = "-1";
	chr.chr_ai.type.timewait = "0";
	chr.chr_ai.type.locator = "stay";
	chr.chr_ai.type.wait = stf(5.0 + frnd() * 5.0);;
	LAi_tmpl_stay_InitTemplate(chr);
	
	LAi_SetDefaultStayAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}


void LAi_type_owner_CharacterUpdate(aref chr, float dltTime)
{
	int iNumEnemy, i, num;
	chr.chr_ai.type.wait = stf(chr.chr_ai.type.wait) - dltTime;
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG)
	{
		chr.chr_ai.type.time = "0";
		chr.chr_ai.type.who = "-1";
		chr.chr_ai.type.wait = "1.0";
		return;
	}
	if (chr.chr_ai.tmpl == LAI_TMPL_ANI)
	{
		if (chr.chr_ai.tmpl.animation == "")
		{	
			num = FindNearCharacters(chr, 20.0, -1.0, 180.0, 0.01, true, true);
			iNumEnemy = LAi_type_owner_FindEnemy(chr, num);
			if (iNumEnemy < 0) LAi_type_owner_SetGoto(chr);
			else
			{
				LAi_tmpl_ani_PlayAnimation(chr, "afraid", -1.0);
				CharacterTurnByChr(chr, &Characters[sti(chrFindNearCharacters[iNumEnemy].index)]);
				return;
			}
		}
		else return; 
	}
	num = FindNearCharacters(chr, 20.0, -1.0, 180.0, 0.01, true, true);
	iNumEnemy = LAi_type_owner_FindEnemy(chr, num);
	if(iNumEnemy < 0)
	{	
		if(chr.chr_ai.tmpl != LAI_TMPL_ANI)
		{
			if (num <= 0)
			{ 
				if(chr.chr_ai.tmpl == LAI_TMPL_STAY)
				{					
					LAi_type_owner_RestoreAngle(chr);
					if (stf(chr.chr_ai.type.wait) < 0.0)
					{									
						LAi_type_owner_SetGoto(chr);
					}
				}
			}
			else
			{
				
				for(i = 0; i < num; i++)
				{
					if(nMainCharacterIndex == sti(chrFindNearCharacters[i].index))
					{					
						
						if (bMainCharacterInBox && chr.chr_ai.type.state != "afraid")
						{
							
							if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
							{
								DeleteAttribute(pchar, "questTemp.HouseEncTimer");
							}
							
							if (chr.sex == "man") chr.greeting = "VOICE\Russian\soldier_arest_1.wav";
							else chr.greeting = "VOICE\Russian\Gr_Woman_Citizen_11.wav";
							chr.dialog.currentnode = chr.sex  + "_FackYou";
							LAi_SetActorTypeNoGroup(chr); 
							LAi_ActorDialog(chr, pchar, "", 0.0, 0);
						}
						else
						{
							if(chr.chr_ai.tmpl == LAI_TMPL_STAY)
							{
								
								if (LAi_CheckFightMode(pchar))
								{
									if (LAi_IsSetBale(chr))
									{	
										chr.chr_ai.type.state = "fight";
										if(!LAi_tmpl_SetFight(chr, pchar))
										{
											
											LAi_tmpl_stay_InitTemplate(chr);
											chr.chr_ai.type.state = "stay";
										}
									}
									else
									{
										LAi_tmpl_ani_PlayAnimation(chr, "afraid", -1.0);
										LAi_SetAfraidDead(chr);
										CharacterTurnByChr(chr, pchar);
									}							
									return;
								}
								
								if(stf(chrFindNearCharacters[i].dist) < 2.0)
								{ 
									CharacterTurnByChr(chr, &Characters[sti(chrFindNearCharacters[i].index)]);				
								}
								else
								{
									LAi_type_owner_RestoreAngle(chr);
									if (stf(chr.chr_ai.type.wait) < 0.0)
									{									
										LAi_type_owner_SetGoto(chr);
									}
								}
							}
						}
					}
				}
			}
		}
	}else{
		
		if(chr.chr_ai.tmpl != LAI_TMPL_ANI)
		{
			
			if (chr.sex == "man" && LAi_IsSetBale(chr))
			{
				chr.chr_ai.type.state = "fight";
				if(!LAi_tmpl_SetFight(chr, &Characters[sti(chrFindNearCharacters[iNumEnemy].index)]))
				{
					
					LAi_tmpl_stay_InitTemplate(chr);
					chr.chr_ai.type.state = "stay";
				}
			}
			else
			{	
				if(stf(chrFindNearCharacters[iNumEnemy].dist) < 3.0)
				{
					LAi_tmpl_ani_PlayAnimation(chr, "afraid", -1.0);
					LAi_SetAfraidDead(chr);
					CharacterTurnByChr(chr, &Characters[sti(chrFindNearCharacters[iNumEnemy].index)]);
					if (rand(100) > 70)	
					{
						if (chr.sex == "man") chr.greeting = "VOICE\Russian\soldier_arest_1.wav";
						else chr.greeting = "VOICE\Russian\Gr_Woman_Citizen_11.wav";
					}
				}
				else
				{
					if(chr.chr_ai.tmpl == LAI_TMPL_STAY)
					{
						LAi_type_owner_RestoreAngle(chr);
						if (stf(chr.chr_ai.type.wait) < 0.0)
						{									
							LAi_type_owner_SetGoto(chr);
						}						
					}
				}
			}
		}
	}
}

bool LAi_type_owner_CharacterLogin(aref chr)
{
	return true;
}


bool LAi_type_owner_CharacterLogoff(aref chr)
{
	return true;
}


void LAi_type_owner_TemplateComplite(aref chr, string tmpl)
{
	switch(chr.chr_ai.type.state)
	{
	case "waiting":
		LAi_tmpl_stay_InitTemplate(chr);
		chr.chr_ai.type.state = "stay";
		break;
	case "goto":
		
		LAi_type_owner_SetAfterGoto(chr);
		break;
	case "work":
		LAi_type_owner_SetGoto(chr);
		break;
	case "stay":
		LAi_tmpl_stay_InitTemplate(chr);
		break;
	}
}


void LAi_type_owner_NeedDialog(aref chr, aref by)
{
}


bool LAi_type_owner_CanDialog(aref chr, aref by)
{
	
	if(chr.chr_ai.type.state == "afraid") return false;
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY || chr.chr_ai.tmpl == LAI_TMPL_GOTO || chr.chr_ai.tmpl == LAI_TMPL_ANI) return true;
	return false;
}


void LAi_type_owner_StartDialog(aref chr, aref by)
{
	
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}


void LAi_type_owner_EndDialog(aref chr, aref by)
{
	if(chr.chr_ai.type.state == "goto")
	{
		LAi_tmpl_goto_InitTemplate(chr);
		LAi_tmpl_goto_SetLocator(chr, "barmen", chr.chr_ai.type.locator, 600.0);
	}else{
		LAi_tmpl_stay_InitTemplate(chr);
		LAi_CharacterRestoreAy(chr);
	}
}


void LAi_type_owner_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{

}



void LAi_type_owner_Attacked(aref chr, aref by)
{
	if(!LAi_group_IsEnemy(chr, by)) return;
	LAi_group_UpdateTargets(chr);
	LAi_tmpl_SetFight(chr, by);
	if(rand(100) > 90)
	{
		LAi_type_warrior_PlaySound(chr);
	}
}


void LAi_type_owner_RestoreAngle(aref chr)
{
	CharacterTurnByLoc(chr, "barmen", chr.chr_ai.type.locator);
}


int LAi_type_owner_FindEnemy(aref chr, int num)
{
	int idx;
	if(num > 0)
	{
		for(int i = 0; i < num; i++)
		{
			idx = sti(chrFindNearCharacters[i].index);
			if(LAi_group_IsEnemy(chr, &Characters[idx])) return i;
		}
	}
	return -1;
}


void LAi_type_owner_SetGoto(aref chr)
{
	if(chr.chr_ai.type.locator == "stay")
	{
		if (rand(1)) chr.chr_ai.type.locator = "bar1";
		else chr.chr_ai.type.locator = "bar2";
	}else{
		chr.chr_ai.type.locator = "stay";
	}
	LAi_tmpl_goto_InitTemplate(chr);
	LAi_tmpl_goto_SetLocator(chr, "barmen", chr.chr_ai.type.locator, 600.0);
	chr.chr_ai.type.state = "goto";
}


void LAi_type_owner_SetAfterGoto(aref chr)
{
	if(rand(100) < 80 && chr.chr_ai.type.locator != "stay")
	{
		LAi_type_owner_RestoreAngle(chr);
		chr.chr_ai.type.state = "work";
		if (chr.sex == "man") LAi_tmpl_ani_PlayAnimation(chr, "Barman_idle", 1.0 + rand(10));
		else LAi_tmpl_ani_PlayAnimation(chr, "taverngirl", 1.0 + rand(12));
	}
	else
	{
		LAi_CharacterPlaySound(chr, "owner");
		LAi_tmpl_stay_InitTemplate(chr);
		chr.chr_ai.type.state = "stay";
		if (chr.chr_ai.type.locator == "stay") chr.chr_ai.type.wait = stf(5.0 + frnd() * 20.0);
		else chr.chr_ai.type.wait = stf(1.0 + frnd() * 4.0);
	}
}

void LAi_type_owner_TestControl(aref chr)
{	
	if(LAi_Character_CanDialog(chr, pchar))
	{
		chr.chr_ai.type.state = "dialog";
		LAi_tmpl_SetDialog(chr, pchar, -1.0);
		chr.chr_ai.type.wait = 10.0;
	}
}

