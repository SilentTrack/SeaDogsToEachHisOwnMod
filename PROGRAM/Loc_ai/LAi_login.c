
int LAi_loginedcharacters[MAX_CHARS_IN_LOC];
int LAi_numloginedcharacters = 0;


bool LAi_CharacterLogin(aref chr, string locID)
{
	string func;
	
	if(CheckAttribute(chr, "location") == false)
	{
		Trace("Character <" + chr.id + "> have not field [location]");
		return false;
	}
	if(chr.id == "0")
	{
		chr.location = "none";
		return false;
	}
	bool isLogin = false;
	if(chr.location == locID)
	{
		if(sti(chr.index) == nMainCharacterIndex) isLogin = true;
		if(CheckAttribute(chr, "location.stime") != false)
		{
			if(CheckAttribute(chr, "location.etime") != false)
			{
				
				if(LAi_login_CheckTime(stf(chr.location.stime), stf(chr.location.etime))) 
				{
					isLogin = true;
				}
			}
			else 
			{
				isLogin = true;
			}
		}
		else 
		{
			isLogin = true;
		}
	}
	
	if(!LAi_IsBoarding)
	{
		if(CheckAttribute(chr, "location.follower") != false)
		{
			chr.location = pchar.location;
			chr.location.group = pchar.location.group;
			chr.location.locator = pchar.location.locator;
			isLogin = true;
			if(LAi_restoreStates)
			{
				LAi_SetCurHPMax(chr);
			}
		}
	}
	
	if(LAi_IsCapturedLocation)
	{
		if(GetMainCharacterIndex() != sti(chr.index))
		{
   			
			if(!IsOfficer(chr))
			{
				if(CheckAttribute(chr, "location.loadcapture") == 0)
				{
					isLogin = false;
				}else{
					if(sti(chr.location.loadcapture) == 0)
					{
						isLogin = false;
					}
				}
			}
			
		}
	}
	if(!isLogin) return false;
	
	if(LAi_numloginedcharacters >= MAX_CHARS_IN_LOC)
	{
		Trace("LAi_CharacterLogin -> many logined characters in location > " + MAX_CHARS_IN_LOC);
		return false;
	}
	
	if(CheckAttribute(chr, "chr_ai.type") == false)
	{
		chr.chr_ai.type = LAI_DEFAULT_TYPE;
	}
	if(CheckAttribute(chr, "chr_ai.tmpl") == false)
	{
		chr.chr_ai.tmpl = LAI_DEFAULT_TEMPLATE;
	}
	if(CheckAttribute(chr, "chr_ai.group") == false)
	{
		chr.chr_ai.group = LAI_DEFAULT_GROUP;
	}
	if(CheckAttribute(chr, "chr_ai.alarmreact") == false)
	{
		chr.chr_ai.alarmreact = LAI_DEFAULT_ALARMREACT;
	}
	if(CheckAttribute(chr, "chr_ai.grpalarmr") == false)
	{
		chr.chr_ai.grpalarmr = LAI_DEFAULT_GRPALARMR;
	}
	if(CheckAttribute(chr, "chr_ai.hp") == false)
	{
		chr.chr_ai.hp = LAI_DEFAULT_HP;
	}
	if(CheckAttribute(chr, "chr_ai.hp_max") == false)
	{
		chr.chr_ai.hp_max = LAI_DEFAULT_HP_MAX;
	}
	if(CheckAttribute(chr, "chr_ai.charge") == false)
	{
		chr.chr_ai.charge = LAI_DEFAULT_CHARGE;
	}
	 
	SetEnergyToCharacter(chr);  
	
	
	float hp = stf(chr.chr_ai.hp);
	float hpmax = stf(chr.chr_ai.hp_max);
	if(hpmax < 1) hpmax = 1;
	chr.chr_ai.hp_max = hpmax;
	if(hp > hpmax) hp = hpmax;
	if(hp < 0) hp = 0;
	chr.chr_ai.hp = hp;
	if(!actLoadFlag)
	{
		if(hp < 1)
		{
			if(CheckAttribute(chr, "location.norebirth") != false)
			{
				if(sti(chr.location.norebirth) != 0) return false;
			}
			
			chr.chr_ai.hp = hpmax;
			hp = hpmax;
			if (!CheckAttribute(chr, "location.rebirthOldName"))
			{
				SetRandomNameToCharacter(chr);
			}
			func = chr.chr_ai.type;
			chr.chr_ai.type = "";
			chr.chr_ai.tmpl = "";
			if(func != "")
			{
				func = "LAi_type_" + func + "_Init";
				call func(chr);
			}
		}
	}
	if(hp < 1) return false;
	
	if(LAi_CheckCharacter(chr, "LAi_CharacterLogin") == false) return false;
	
	
	
	
	func = chr.chr_ai.type;
	bool res = true;
	if(func != "")
	{
		func = "LAi_type_" + func + "_CharacterLogin";
		res = call func(chr);
	}
	if(res == false) return false;
	chr.chr_ai.login = true;
	LAi_AddLoginedCharacter(chr);

	 
	if(CheckAttribute(chr, "quest.questflag"))
	{
		CheckQuestForCharacter(chr);
		if(chr.chr_ai.type == LAI_TYPE_CITIZEN)
		{
			chr.chr_ai.group = "";
		}
	}
	if(CheckAttribute(chr, "currentquest"))
	{
		CheckQuestForCharacter(chr);
		if(chr.chr_ai.type == LAI_TYPE_CITIZEN)
		{
			chr.chr_ai.group = "";
		}
	}
	return true;
}

void LAi_CharacterPostLogin(ref location)
{
	
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int idx = LAi_loginedcharacters[i];
		if(idx >= 0)
		{
			
			ref chr = &Characters[idx];
			if(CheckAttribute(chr, "location.follower") != false)
			{
				
				float x, y, z;
				if(GetCharacterPos(pchar, &x, &y, &z) == false)
				{
					x = 0.0; y = 0.0; z = 0.0;
				}
				
				string locator = LAi_FindNearestFreeLocator("goto", x, y, z);
				if(locator != "")
				{
					TeleportCharacterToLocator(chr, "goto", locator)
					CharacterTurnByChr(chr, pchar);
				}else{
					Trace("Can't find good locator for follower character <" + chr.id + ">");
				}
			}
		}
	}
	if(!actLoadFlag)
	{
		QuestsCheck(); 
		
		CreateCitizens(location);
		CreateTraders(location);
		CreateHabitues(location);
		CreateIncquisitio(location);
		CreateMinentownMine(location); 
		CreateMaltains(location); 
		CreateHWICOffice(location); 
		CreateLSCGuardClan(location); 
		CreateLSCInsideClan(location); 
		CreateLostShipsCity(location); 
		CreateMineBandits(location); 
		CreateIslatesoroEng(location); 
		CreateAmmo(location); 
		CreateKsochitamSkeletons(location) 
		CreateKhaelRoaSkeletons(location) 
		CreateMayak(location);
		CreateBrothels(location);
		CreatePearlVillage(location);
		CreateIndianVillage(location);
		CreateInsideHouseEncounters(location);
		CreateInsideResidenceEncounters(location);
		CreateSkladInsideEncounters(location);
		CreateJail(location);
		CreateFortsNPC(location);
		CreatUnderwater(location);
		CreatePlantation(location);
		CreateItzaLand(location);
		
		LAi_CreateEncounters(location); 
		LAi_CreateParticles(location);
		LAi_CreateFlowers(location); 
		LAi_CreateQuestFlowers(location); 
		LAi_CreateDolly(location); 
		LAi_CreateShoreChest(location); 
		LAi_CreateCaveEncounters(location);
		
		LandHunterReactionResult(location);
		
		CopyPassForAztecSkull();

	}
}

bool LAi_CharacterLogoff(aref chr)
{
	chr.chr_ai.login = false;	
	
	if(LAi_CheckCharacter(chr, "LAi_CharacterLogoff") == false) return false;
	LAi_DelLoginedCharacter(chr);
	string func = chr.chr_ai.type;
	bool res = true;
	if(func != "")
	{
		func = "LAi_type_" + func + "_CharacterLogoff";
		res = call func(chr);
	}
	if(res == false) return false;
	return true;
}

void LAi_AddLoginedCharacter(aref chr)
{
	int index = sti(chr.index);
	LAi_loginedcharacters[LAi_numloginedcharacters] = index;
	LAi_numloginedcharacters = LAi_numloginedcharacters + 1;
}

void LAi_DelLoginedCharacter(aref chr)
{
	int index = sti(chr.index);
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		if(LAi_loginedcharacters[i] == index)
		{
			LAi_loginedcharacters[i] = LAi_loginedcharacters[LAi_numloginedcharacters - 1];
			LAi_numloginedcharacters = LAi_numloginedcharacters - 1;
		}		
	}
	if(LAi_numloginedcharacters < 0) LAi_numloginedcharacters = 0;
}

bool LAi_login_CheckTime(float start, float end)
{
	float curTime = GetTime();
	if(start <= end)
	{
		if((curTime >= start) && (curTime <= end)) return true;
	}else{
		if(curTime >= start) return true;
		if(curTime <= end) return true;
	}
	return false;
}

void LAi_PostLoginInit(aref chr)
{
	if(!IsEntity(chr)) return;
	
	LAi_group_MoveCharacter(chr, chr.chr_ai.group);
	
	string func = chr.chr_ai.tmpl;
	if(func != "")
	{
		func = "LAi_tmpl_" + func + "_InitTemplate";
		bool res = call func(&chr);
		if(res == false)
		{
			chr.chr_ai.tmpl = LAI_DEFAULT_TEMPLATE;
		}
	}
	
	func = chr.chr_ai.type;
	if(func != "")
	{
		func = "LAi_type_" + func + "_Init";
		call func(&chr);
	}
}
