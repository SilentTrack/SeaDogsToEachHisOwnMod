

#define LAI_TMPL_WALK	"walk"


bool LAi_tmpl_walk_InitTemplate(aref chr)
{
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "LockFightMode", false);
	CharacterPlayAction(chr, "");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.tmpl"))
	{
		if(chr.chr_ai.tmpl != LAI_TMPL_WALK) isNew = true;
	}else{
		isNew = true;
	}
	if(isNew)
	{
		
		DeleteAttribute(chr, "chr_ai.tmpl");
		chr.chr_ai.tmpl = LAI_TMPL_WALK;
		chr.chr_ai.tmpl.locator = "";
		chr.chr_ai.tmpl.time = 0;
		float maxtime = rand(5);
		chr.chr_ai.tmpl.maxtime = maxtime;	
		if(rand(3) != 0)
		{
			chr.chr_ai.tmpl.state = "goto";
			if(LAi_IsInitedAI) LAi_tmpl_walk_go_notime(chr);
		}else{
			chr.chr_ai.tmpl.state = "stay";
			if(LAi_IsInitedAI) SetCharacterTask_Stay(chr);
		}
	}else{
		
		if(!CheckAttribute(chr, "chr_ai.tmpl.state")) chr.chr_ai.tmpl.state = "stay";
		if(CheckAttribute(chr, "chr_ai.tmpl.locator"))
		{
			if(chr.chr_ai.tmpl.locator == "") chr.chr_ai.tmpl.state = "stay";
		}else{
			chr.chr_ai.tmpl.state = "stay";
		}
		if(!CheckAttribute(chr, "chr_ai.tmpl.time")) chr.chr_ai.tmpl.time = 0;
		if(!CheckAttribute(chr, "chr_ai.tmpl.maxtime")) chr.chr_ai.tmpl.maxtime = 1 + rand(5);
		if(chr.chr_ai.tmpl.state == "goto")
		{
			if(LAi_IsInitedAI)
			{
				if(SetCharacterTask_GotoPoint(chr, "goto", chr.chr_ai.tmpl.locator) == false)
				{
					SetCharacterTask_Stay(chr);
					chr.chr_ai.tmpl.state = "stay";
				}
			}
		}
		if(chr.chr_ai.tmpl.state == "stay")
		{
			if(LAi_IsInitedAI) SetCharacterTask_Stay(chr);
			if(chr.chr_ai.tmpl.locator != "")
			{
				CharacterTurnByLoc(chr, "goto", chr.chr_ai.tmpl.locator);
			}
		}
	}
	return true;
}



void LAi_tmpl_walk_CharacterUpdate(aref chr, float dltTime)
{
	float time, maxtime;
	int idx;
	aref tmpl;
	float dist;
	makearef(tmpl, chr.chr_ai.tmpl);
	
	tmpl.time = stf(tmpl.time) + dltTime;
	if(tmpl.state == "stay")
	{
		
		time = stf(tmpl.time);
		maxtime = stf(tmpl.maxtime);
		if(time > maxtime)
		{
			
			LAi_tmpl_walk_go(chr);
		}else{
			
			if(rand(5) == 3)
			{
				idx = LAi_FindNearestVisCharacter(chr, 2.0);
				if(idx >= 0)
				{
					
					tmpl.state = "look";
					tmpl.state.time = 0;
					tmpl.state.maxtime = 3 + rand(3);
					tmpl.state.index = idx;
					CharacterTurnByChr(chr, &Characters[idx]);
				}
			}
		}
	}else{
		if(tmpl.state == "look")
		{
			tmpl.time = stf(tmpl.time) + dltTime;
			time = stf(tmpl.state.time);
			maxtime = stf(tmpl.state.maxtime);
			idx = sti(tmpl.state.index);
			if(GetCharacterDistByChr(chr, &Characters[idx], &dist) == false)
			{
				time = maxtime;
			}
			if(dist > 4.0 || dist < 0.0)
			{
				time = maxtime;
			}
			if(time < maxtime)
			{
				time = time + dltTime;
				tmpl.state.time = time;
				CharacterTurnByChr(chr, &Characters[idx]);
			}else{
				DeleteAttribute(chr, "chr_ai.tmpl.state");
				tmpl.state = "stay";
				CharacterTurnByLoc(chr, "goto", chr.chr_ai.tmpl.locator);
			}
		}
	}
}


void LAi_tmpl_walk_EndGoToPoint(aref chr)
{
	LAi_tmpl_walk_endgo(chr);
}


void LAi_tmpl_walk_FailureGoToPoint(aref chr)
{
	LAi_tmpl_walk_endgo(chr);
}



void LAi_tmpl_walk_EndRunToPoint(aref chr)
{
	LAi_tmpl_walk_endgo(chr);
}


void LAi_tmpl_walk_FailureRunToPoint(aref chr)
{
	LAi_tmpl_walk_endgo(chr);
}


void LAi_tmpl_walk_BusyPos(aref chr, float x, float y, float z)
{
	LAi_tmpl_walk_endgo(chr);
	if(chr.chr_ai.tmpl.state == "stay")
	{
		CharacterTurnByPoint(chr, x, y, z);
	}
}


void LAi_tmpl_walk_FollowGo(aref chr)
{
	LAi_tmpl_walk_endgo(chr);
}


void LAi_tmpl_walk_FollowStay(aref chr)
{
	LAi_tmpl_walk_endgo(chr);
}


void LAi_tmpl_walk_FailureFollow(aref chr)
{
	LAi_tmpl_walk_endgo(chr);
}



void LAi_tmpl_walk_FightGo(aref chr)
{
	LAi_tmpl_walk_endgo(chr);
}


void LAi_tmpl_walk_FightStay(aref chr)
{
	LAi_tmpl_walk_endgo(chr);
}


void LAi_tmpl_walk_FailureFight(aref chr)
{
	LAi_tmpl_walk_endgo(chr);
}


bool LAi_tmpl_walk_IsFire(aref chr)
{
	return false;
}


bool LAi_tmpl_walk_IsFight(aref chr)
{
	return false;
}



void LAi_tmpl_walk_EndEscape(aref chr)
{
	LAi_tmpl_walk_endgo(chr);
}


void LAi_tmpl_walk_EscapeSlide(aref chr)
{
	LAi_tmpl_walk_endgo(chr);
}


void LAi_tmpl_walk_FailureEscape(aref chr)
{
	LAi_tmpl_walk_endgo(chr);
}



void LAi_tmpl_walk_ColThreshold(aref chr)
{
	if(chr.chr_ai.tmpl.state == "stay")
	{
		chr.chr_ai.tmpl.time = 0;
		chr.chr_ai.tmpl.maxtime = 5;
		LAi_tmpl_walk_go_notime(chr);
	}else{
		if(chr.chr_ai.tmpl.state == "look")
		{
			chr.chr_ai.tmpl.time = 0;
			chr.chr_ai.tmpl.maxtime = 5;
			LAi_tmpl_walk_go_notime(chr);
		}else{
			if(LAi_tmpl_walk_neareststaycheck(chr))
			{
				LAi_tmpl_walk_nowstay(chr);
			}else{
				chr.chr_ai.tmpl.time = 0;
				chr.chr_ai.tmpl.maxtime = 8;
				LAi_tmpl_walk_go_notime(chr);
			}
		}
	}
}



void LAi_tmpl_walk_EndAction(aref chr)
{
	LAi_tmpl_walk_endgo(chr);
}


void LAi_tmpl_walk_FreePos(aref chr, aref who)
{
	LAi_tmpl_walk_go(chr);
}





void LAi_tmpl_walk_go(aref chr)
{
	chr.chr_ai.tmpl.maxtime = 8 + rand(50);
	chr.chr_ai.tmpl.time = 0;
	LAi_tmpl_walk_go_notime(chr);
}

void LAi_tmpl_walk_go_notime(aref chr)
{
	string loc;
	if(rand(3) == 2)
	{
		loc = LAi_FindRandomLocator("goto");
	}else{
		loc = FindCharacterOptLocator(chr, "goto");
		if(loc == "")
		{
			loc = LAi_FindRandomLocator("goto");
		}
	}
	if(loc == "")
	{
		
		chr.chr_ai.tmpl.maxtime = 60;
		chr.chr_ai.tmpl.time = 0;
		chr.chr_ai.tmpl.state = "stay";
		return;
	}
	if(SetCharacterTask_GotoPoint(chr, "goto", loc) == false)	
	{
		
		chr.chr_ai.tmpl.maxtime = 1;
		chr.chr_ai.tmpl.time = 0;
		chr.chr_ai.tmpl.state = "stay";
		return;
	}
	chr.chr_ai.tmpl.state = "goto";
	chr.chr_ai.tmpl.locator = loc;
}


void LAi_tmpl_walk_endgo(aref chr)
{
	if(stf(chr.chr_ai.tmpl.time) > stf(chr.chr_ai.tmpl.maxtime))
	{
		
		if(LAi_tmpl_walk_neareststaycheck(chr))
		{
			
			LAi_tmpl_walk_nowstay(chr);
		}else{
			
			LAi_tmpl_walk_go_notime(chr);
		}
	}else{
		
		LAi_tmpl_walk_go_notime(chr);
	}
}

void LAi_tmpl_walk_nowstay(aref chr)
{
	
	chr.chr_ai.tmpl.time = 0;
	chr.chr_ai.tmpl.maxtime = 5 + rand(30);
	SetCharacterTask_Stay(chr);
	chr.chr_ai.tmpl.state = "stay";
	if(chr.chr_ai.tmpl.locator != "")
	{
		CharacterTurnByLoc(chr, "goto", chr.chr_ai.tmpl.locator);
	}
}

bool LAi_tmpl_walk_neareststaycheck(aref chr)
{
	int num = FindNearCharacters(chr, 4.0, -1.0, -1.0, 0.01, false, false);
	if(num <= 0) return true;
	int cnt = 0;
	for(int i = 0; i < num; i++)
	{
		int idx = sti(chrFindNearCharacters[i].index);
		if(CharacterGetTask(&Characters[idx]) == "Stay")
		{
			cnt++;
		}
	}	
	if(cnt > 1) return false;
	return true;
}



