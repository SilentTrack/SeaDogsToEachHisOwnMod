

#define LAI_TMPL_RUNTO	"runto"

 

bool LAi_tmpl_runto_InitTemplate(aref chr)
{
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "LockFightMode", false);
	CharacterPlayAction(chr, "");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.tmpl"))
	{
		if(chr.chr_ai.tmpl != LAI_TMPL_RUNTO) isNew = true;
	}else{
		isNew = true;
	}
	if(isNew)
	{
		DeleteAttribute(chr, "chr_ai.tmpl");
		chr.chr_ai.tmpl = LAI_TMPL_RUNTO;
		chr.chr_ai.tmpl.state = "stay";
		chr.chr_ai.tmpl.wait = 0;
		chr.chr_ai.tmpl.timeout = -1;
		chr.chr_ai.tmpl.time = 0;
		if(LAi_IsInitedAI) SetCharacterTask_Stay(chr);
	}else{
		isNew = true;
		if(CheckAttribute(chr, "chr_ai.tmpl.group"))
		{
			if(CheckAttribute(chr, "chr_ai.tmpl."))
			{
				if(chr.chr_ai.tmpl.group != "")
				{
					if(chr.chr_ai.tmpl.locator != "")
					{
						isNew = false;
					}
				}
			}
		}
		if(isNew)
		{
			chr.chr_ai.tmpl.group = "";
			chr.chr_ai.tmpl.locator = "";
			chr.chr_ai.tmpl.state = "stay";
		}else{
			chr.chr_ai.tmpl.state = "runto";
		}
		chr.chr_ai.tmpl.wait = "0";
		if(!CheckAttribute(chr, "chr_ai.tmpl.timeout")) chr.chr_ai.tmpl.timeout = "-1";
		if(!CheckAttribute(chr, "chr_ai.tmpl.time")) chr.chr_ai.tmpl.time = "0";
		LAi_tmpl_runto_Restart(chr);
	}
	return true;
}


void LAi_tmpl_runto_SetLocator(aref chr, string group, string locator, float timeout)
{
	chr.chr_ai.tmpl.state = "runto";
	chr.chr_ai.tmpl.wait = "0";
	chr.chr_ai.tmpl.group = group;
	chr.chr_ai.tmpl.locator = locator;
	chr.chr_ai.tmpl.timeout = timeout;
	chr.chr_ai.tmpl.time = "0";
	LAi_tmpl_runto_Restart(chr);
}

bool LAi_tmpl_runto_IsStay(aref chr)
{
	if(chr.chr_ai.tmpl.state != "runto") return true;
	return false;
}


void LAi_tmpl_runto_CharacterUpdate(aref chr, float dltTime)
{
	aref tmpl;
	makearef(tmpl, chr.chr_ai.tmpl);
	if(tmpl.state == "runto")
	{

		float time = stf(tmpl.wait);
		if(time > 0.0)
		{
			
			if(time > 1.0)
			{
				
				tmpl.wait = time - dltTime;
			}else{
				
				tmpl.wait = "0";
				LAi_tmpl_runto_Restart(chr);
			}
		}
		float timeout = stf(tmpl.timeout);
		if(timeout > 0.0)
		{
			time = stf(tmpl.time) + dltTime;
			tmpl.time = time;
			if(time >= timeout)
			{
				
				
				if(LAi_tmpl_runto_Teleport(chr))
				{
					LAi_tmpl_runto_Complite(chr);
				}else{
					chr.chr_ai.tmpl.state = "falure";
					SetCharacterTask_Stay(chr);
				}
			}
		}
	}
}


void LAi_tmpl_runto_EndGoToPoint(aref chr)
{
	LAi_tmpl_runto_Restart(chr);
}


void LAi_tmpl_runto_FailureGoToPoint(aref chr)
{
	Trace("Template <runto> -> failure for chr.id = " + chr.id);
	if(LAi_tmpl_runto_Teleport(chr))
	{
		LAi_tmpl_runto_Complite(chr);
	}else{
		chr.chr_ai.tmpl.state = "falure";
		SetCharacterTask_Stay(chr);
	}
}



void LAi_tmpl_runto_EndRunToPoint(aref chr)
{
	LAi_tmpl_runto_Complite(chr);
}


void LAi_tmpl_runto_FailureRunToPoint(aref chr)
{
	LAi_tmpl_runto_Restart(chr);
}


void LAi_tmpl_runto_BusyPos(aref chr, float x, float y, float z)
{
	if(chr.chr_ai.tmpl.state == "runto")
	{
		
		LAi_Character_FreeLocator(chr, chr.chr_ai.tmpl.group, chr.chr_ai.tmpl.locator);
		
		chr.chr_ai.tmpl.wait = 3.0 + rand(4)*0.5;
		SetCharacterTask_Stay(chr);
	}
}


void LAi_tmpl_runto_FollowGo(aref chr)
{
	LAi_tmpl_runto_Restart(chr);
}


void LAi_tmpl_runto_FollowStay(aref chr)
{
	LAi_tmpl_runto_Restart(chr);
}


void LAi_tmpl_runto_FailureFollow(aref chr)
{
	LAi_tmpl_runto_Restart(chr);
}



void LAi_tmpl_runto_FightGo(aref chr)
{
	LAi_tmpl_runto_Restart(chr);
}


void LAi_tmpl_runto_FightStay(aref chr)
{
	LAi_tmpl_runto_Restart(chr);
}


void LAi_tmpl_runto_FailureFight(aref chr)
{
	LAi_tmpl_runto_Restart(chr);
}


bool LAi_tmpl_runto_IsFire(aref chr)
{	
	return false;
}


bool LAi_tmpl_runto_IsFight(aref chr)
{
	return false;
}



void LAi_tmpl_runto_EndEscape(aref chr)
{
	LAi_tmpl_runto_Restart(chr);
}


void LAi_tmpl_runto_EscapeSlide(aref chr)
{
	LAi_tmpl_runto_Restart(chr);
}


void LAi_tmpl_runto_FailureEscape(aref chr)
{
	LAi_tmpl_runto_Restart(chr);
}



void LAi_tmpl_runto_ColThreshold(aref chr)
{
}



void LAi_tmpl_runto_EndAction(aref chr)
{
	LAi_tmpl_runto_Restart(chr);
}



void LAi_tmpl_runto_FreePos(aref chr, aref who)
{
}



void LAi_tmpl_runto_Restart(aref chr)
{
	if(chr.chr_ai.tmpl.state == "runto")
	{
		if(LAi_IsInitedAI)
		{
			if(stf(chr.chr_ai.tmpl.wait) < 1.0)
			{
				if(SetCharacterTask_RuntoPoint(chr, chr.chr_ai.tmpl.group, chr.chr_ai.tmpl.locator) == false)
				{
					Trace("Template <runto> -> path not found chr.id = " + chr.id);
					if(LAi_tmpl_runto_Teleport(chr))
					{
						LAi_tmpl_runto_Complite(chr);
					}else{
						chr.chr_ai.tmpl.state = "falure";
						SetCharacterTask_Stay(chr);
					}
				}
			}else{
				SetCharacterTask_Stay(chr);
			}
		}
	}else{
		if(LAi_IsInitedAI) SetCharacterTask_Stay(chr);
	}
}

bool LAi_tmpl_runto_Teleport(aref chr)
{
	if(stf(chr.chr_ai.tmpl.timeout) >= 0)
	{
		
		TeleportCharacterToLocator(chr, chr.chr_ai.tmpl.group, chr.chr_ai.tmpl.locator);
		return true;
	}
	return false;
}


void LAi_tmpl_runto_Complite(aref chr)
{
	if(LAi_IsInitedAI) SetCharacterTask_Stay(chr);
	chr.chr_ai.tmpl.group = "";
	chr.chr_ai.tmpl.locator = "";
	chr.chr_ai.tmpl.state = "stay";
	chr.chr_ai.tmpl.wait = "0";
	chr.chr_ai.tmpl.timeout = "-1";
	chr.chr_ai.tmpl.time = "0";
	LAi_Character_TemplateComplite(chr, LAI_TMPL_RUNTO);
}


