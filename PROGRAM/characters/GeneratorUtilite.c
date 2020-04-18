



int m_rank_bonus, e_rank_bonus;




void SetFantomParamFromRank(ref NPchar, int  rank, bool setEquip)
{
    SetRandSPECIAL(Npchar);
    CalculateSkillsFromRank(Npchar, rank);
    SetFantomHP(NPchar);
    if (setEquip)
    {
	    LAi_NPC_Equip(NPchar, sti(NPchar.rank), true, true);
    }
}



void CalculateSkillsFromRank(ref NPchar, int  rank)
{
    float  iMiddleK;
    
	
	iMiddleK = 6 + rank*GetCharacterRankRate(GetMainCharacter()) / 14.0;
	
	CalculateAppropriateSkillsParam(Npchar, iMiddleK, 5);
}

void CalculateAppropriateSkillsParam(ref NPchar, float  MiddleK, int _complex)
{
    
    float  fValue;
    
    fValue = (20 * _complex / 4.0);
    Npchar.skill.FencingL 	  = makeint(MiddleK + (frandSmall(fValue) + frandSmall((20* _complex / 3.2)) - 24));
    Npchar.skill.FencingS     = makeint(MiddleK + (frandSmall(fValue) + frandSmall((20* _complex / 3.0)) - 20));
    Npchar.skill.FencingH     = makeint(MiddleK + (frandSmall(fValue) + frandSmall((20* _complex / 3.5)) - 28));
    Npchar.skill.Pistol       = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Fortune      = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));

    Npchar.skill.Leadership   = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Commerce     = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Sailing      = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Accuracy     = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Cannons      = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Grappling    = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Repair       = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Defence      = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Sneak        = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));

    CorrectSkillParam(Npchar);

    SetRankFromSkill(Npchar);
}
void CalculateAppropriateSkills(ref NPchar)
{
    float   MiddleK;
    bool    ok;
    int     rank, i, j, k, sum, rank_bonus, base_rank;
    string  sTemp;
    
    SetRandSPECIAL(Npchar);
    if (false)
    {
    	MiddleK = GetMiddleMainSkill();

        CalculateAppropriateSkillsParam(Npchar, MiddleK, MOD_SKILL_ENEMY_RATE);
    }
    else
    
    {
        rank_bonus = 0;
        sTemp = "";
		if (CheckAttribute(NPchar, "RankBonus"))
		{
			rank_bonus = sti(NPchar.RankBonus);
		    sTemp = "RankBonus: " + rank_bonus;
		}

		base_rank = 0;
		if (CheckAttribute(NPchar, "BaseRank"))
		{       
			base_rank = sti(NPchar.BaseRank);
			sTemp += " BaseRank: " + base_rank;
		}

		if (sti(Pchar.rank) > base_rank) base_rank = sti(Pchar.rank);
		
		MiddleK = base_rank;
		
        ok =  (MOD_SKILL_ENEMY_RATE > 5) && (bNewCodeOn);
        if (!ok)
        {
        	ok =  (MOD_SKILL_ENEMY_RATE <= 5) && (!bNewCodeOn); 
        }
        ok =  (!CheckAttribute(NPchar, "OurMan")) || (ok);

  		if (!CheckAttribute(NPchar, "BaseRank") && ok)
  		{
            MiddleK = MiddleK + (MOD_SKILL_ENEMY_RATE-5) * 1.5;
            sTemp += " ComplexBonus = " + FloatToString((MOD_SKILL_ENEMY_RATE-5) * 1.5, 1);
  		}
  		rank = MakeInt(MiddleK + frandSmall(4) + frandSmall(4) + frandSmall(4) + frandSmall(4) - 8 + rank_bonus);

		if (rank < 1) rank = 1;
		if (rank > 300) rank = 300;

    	NPchar.rank = rank;
    	if (CheckAttribute(NPchar, "OurMan"))
    	{
            sTemp += " OurNPCRank: " + rank;
    	}
    	else
    	{
    	   sTemp += " NPCRank: " + rank;
        }
        
        if (CheckAttribute(NPchar, "RankBonus") || CheckAttribute(NPchar, "BaseRank") || CheckAttribute(NPchar, "OurMan"))
        {
    	   
    	}
    	
    	if (rank > (1400 / GetCharacterRankRate(Npchar)))
		{
            SetSelfSkill(Npchar, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX);
            SetShipSkill(Npchar, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX);
			return;
		}
        CalculateSkillsFromRank(Npchar, rank);
    }
}

void SetRankFromSkill(ref Npchar)
{
    Npchar.rank = 1 + makeint( (sti(Npchar.skill.FencingL) + sti(Npchar.skill.FencingH) + sti(Npchar.skill.Fortune) +
                           sti(Npchar.skill.Pistol) + sti(Npchar.skill.Leadership) + sti(Npchar.skill.FencingS) +
                           sti(Npchar.skill.Sailing) + sti(Npchar.skill.Accuracy) + sti(Npchar.skill.Cannons) +
                           sti(Npchar.skill.Grappling) + sti(Npchar.skill.Repair) + sti(Npchar.skill.Defence) +
                           sti(Npchar.skill.Commerce) + sti(Npchar.skill.Sneak) - 84) / GetCharacterRankRate(Npchar) );
    if (sti(Npchar.rank) < 1)
    {
        Npchar.rank = 1;
    }
}

void CorrectSkillParam(ref Npchar)
{
    int i;
    string  skillName;

    for (i=1; i<15; i++)
    {
        skillName = GetSkillNameByIdx(i);
        if(sti(Npchar.skill.(skillName)) > SKILL_MAX) Npchar.skill.(skillName) = SKILL_MAX;
        if(sti(Npchar.skill.(skillName)) < 1)         Npchar.skill.(skillName) = 1;
    }
}
float GetMiddleMainSkill()
{
    float MiddleK;

    MiddleK = makefloat(GetSkillSum(Pchar) / 14.0) ;

    return  MiddleK;
}
int GetSkillSum(ref Npchar)
{
    int i, sum;
    string  skillName;
    
	sum = 0;
    for (i=1; i<15; i++)
    {
        skillName = GetSkillNameByIdx(i);
        sum += sti(Npchar.skill.(skillName));
    }
    return sum;
}

int GetSPECIALSum(ref Npchar)
{
    int i, sum;
    string  skillName;

	sum = 0;
    for (i=15; i<22; i++)
    {
        skillName = GetSkillNameByIdx(i);
        sum += sti(Npchar.SPECIAL.(skillName));
    }
    return sum;
}


void SetFantomParam(ref _pchar)
{
    SetFantomParamCommon(_pchar);
}

void SetFantomParamCommon(ref _pchar)
{
    CalculateAppropriateSkills(_pchar);
    SetFantomHP(_pchar);
    
    DeleteAttribute(_pchar, "Items");
    
    LAi_NPC_Equip(_pchar, sti(_pchar.rank), true, true);
    
}

void SetFantomParamEncout(ref _pchar)  
{
    CalculateAppropriateSkills(_pchar);
    SetFantomHP(_pchar);
    
    DeleteAttribute(_pchar, "Items");
    DeleteAttribute(_pchar, "equip");
    DeleteAttribute(_pchar, "perks.list");
    
	
	
    
    
}

void SetSeaFantomParam(ref _pchar, string type)
{
	ref MChar;

	MChar = GetMainCharacter();
	if (CheckAttribute(MChar, "EnemyRank"))
	{
		Log_TestInfo("If you see this, feel free to kick Gray: " + MChar.EnemyRank);
		DeleteAttribute(MChar, "EnemyRank");
	}
		
	switch(type)
	{
		case "pirate"	:
			_pchar.PhantomType = "marginal";
		break;
		case "war" 		:
			_pchar.PhantomType = "officer";
		break;
		case "trade"	:
			_pchar.PhantomType = "citizen";
		break;
		case "hunter"	:
			_pchar.PhantomType = "hunter";
		break;	
	}

	Fantom_SetRandomSkills(_pchar, type); 
	Fantom_SetRandomMoney(_pchar, type);
	Fantom_SetRandomCrewExp(_pchar, type);
	DeleteAttribute(_pchar, "items");

	SetFantomHP(_pchar);
	LAi_NPC_Equip(_pchar, sti(_pchar.rank), true, true);
	
}


void Fantom_SetRandomSkills(ref rFantom, string sFantomType)
{
	aref aFSkills;
	int iSClass;
	
    makearef(aFSkills, rFantom.Skill);

	CalculateAppropriateSkills(rFantom);

	if(sFantomType == "special")	
	{
		iSClass = 2 + rand(4);
	}
	else
	{
		iSClass = GetCharacterShipClass(rFantom);
	}	
    
     
    
	switch (sFantomType)
	{
		case "trade":
		
            
            aFSkills.Leadership = Fantom_CalcSkill(rFantom, SKILL_LEADERSHIP,iSClass, 0, 0, 0, 1, 1, 2, 2, 3, 4);
            aFSkills.Accuracy	= Fantom_CalcSkill(rFantom, SKILL_ACCURACY,	iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 5);
			aFSkills.Cannons	= Fantom_CalcSkill(rFantom, SKILL_CANNONS,	iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 5);
			aFSkills.Sailing	= Fantom_CalcSkill(rFantom, SKILL_SAILING,	iSClass, 0, 0, 0, 1, 1, 2, 3, 6, 7);
			aFSkills.Defence	= Fantom_CalcSkill(rFantom, SKILL_DEFENCE,	iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 5);
		break;
		case "war":
            aFSkills.Leadership = Fantom_CalcSkill(rFantom, SKILL_LEADERSHIP,iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 5);
            aFSkills.Accuracy	= Fantom_CalcSkill(rFantom, SKILL_ACCURACY,	iSClass, 0, 0, 0, 1, 2, 3, 4, 6, 7);
			aFSkills.Cannons	= Fantom_CalcSkill(rFantom, SKILL_CANNONS,	iSClass, 0, 0, 0, 1, 2, 3, 4, 7, 8);
			aFSkills.Sailing	= Fantom_CalcSkill(rFantom, SKILL_SAILING,	iSClass, 0, 0, 0, 1, 2, 3, 4, 6, 7);
			aFSkills.Defence	= Fantom_CalcSkill(rFantom, SKILL_DEFENCE,	iSClass, 0, 0, 0, 1, 2, 3, 4, 5, 7);
		break;
		case "pirate":
            aFSkills.Leadership = Fantom_CalcSkill(rFantom, SKILL_LEADERSHIP,iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 4);
            aFSkills.Accuracy	= Fantom_CalcSkill(rFantom, SKILL_ACCURACY,	iSClass, 0, 0, 0, 2, 3, 4, 5, 6, 7);
			aFSkills.Cannons	= Fantom_CalcSkill(rFantom, SKILL_CANNONS,	iSClass, 0, 0, 0, 2, 3, 4, 5, 6, 7);
			aFSkills.Sailing	= Fantom_CalcSkill(rFantom, SKILL_SAILING,	iSClass, 0, 0, 0, 2, 3, 4, 5, 7, 8);
            aFSkills.Defence	= Fantom_CalcSkill(rFantom, SKILL_DEFENCE,	iSClass, 0, 0, 0, 1, 2, 3, 4, 5, 6);
		break;
		case "special":
            aFSkills.Leadership = Fantom_CalcSkill(rFantom, SKILL_LEADERSHIP,iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 4);
            aFSkills.Accuracy	= Fantom_CalcSkill(rFantom, SKILL_ACCURACY,	iSClass, 0, 0, 0, 2, 3, 4, 5, 6, 7);
			aFSkills.Cannons	= Fantom_CalcSkill(rFantom, SKILL_CANNONS,	iSClass, 0, 0, 0, 2, 3, 4, 5, 6, 7);
			aFSkills.Sailing	= Fantom_CalcSkill(rFantom, SKILL_SAILING,	iSClass, 0, 0, 0, 2, 3, 4, 5, 7, 8);
            aFSkills.Defence	= Fantom_CalcSkill(rFantom, SKILL_DEFENCE,	iSClass, 0, 0, 0, 1, 2, 3, 4, 5, 6);			
		break;
	}
    
    
	SetRankFromSkill(rFantom);
	
}

void SetFantomHP(ref _pchar)
{
	int hp;
	hp = GetCharacterBaseHPValue(_pchar) + (sti(_pchar.rank) * GetCharacterAddHPValue(_pchar));
	LAi_SetHP(_pchar, hp, hp);
	LAi_SetCurHPMax(_pchar);
}

void SetMonsterLoginHP(ref _pchar) 
{
	int hp;
	if (true)
	{
		int rank = makeint(sti(_pchar.rank) * (1 + MOD_SKILL_ENEMY_RATE / 40.0));
		hp = LAI_DEFAULT_HP_MAX + rank * 5;
		_pchar.rank = rank;
		LAi_SetHP(_pchar, hp, hp);
		LAi_SetCurHPMax(_pchar);
	}
	else
	{
		hp = LAI_DEFAULT_HP_MAX + makeint(sti(_pchar.rank)*(MOD_SKILL_ENEMY_RATE / 2.0 + 5.0)) + 10;
		LAi_SetHP(_pchar, hp, hp);
		LAi_SetCurHPMax(_pchar);
	}
}


bool GetBoardingHP(ref mchr, ref echr, ref float_boarding_player_hp, ref float_boarding_enemy_hp)
{
	float b_p_hp, b_e_hp;
	float moral;
	float exp;
	b_p_hp = LAi_GetCharacterMaxHP(mchr) / 3.0;  
	
	exp = GetCrewExp(mchr, "Soldiers") / GetCrewExpRate() - 0.7;
	moral = 0;
	if(CheckAttribute(mchr, "ship.crew.morale"))
	{
		moral = (stf(mchr.ship.crew.morale) - MORALE_NORMAL)/(MORALE_MAX - MORALE_MIN);
		if(moral < -0.5) moral = -0.5;
		if(moral > 0.5) moral = 0.5;
	}
	exp = exp + moral;  
	b_p_hp = b_p_hp*exp; 
	
	b_e_hp = 0;  
	 
	float_boarding_player_hp   =  b_p_hp;
	float_boarding_enemy_hp    =  b_e_hp;
	
	return true;
}
void AddCharHP(ref _pchar, int _bonus)
{
	int hp = LAi_GetCharacterMaxHP(_pchar) + _bonus;
	if (hp < 1) hp = 1;
	LAi_SetHP(_pchar, hp, hp);
	LAi_SetCurHPMax(_pchar);
}





int GetBoarding_player_hp_Bonus(int mcrew, int ecrew) 
{
    m_rank_bonus = 0;
    e_rank_bonus = 0;
	if(ecrew == 0) ecrew = 1; 
    if (true)
	{     
		if (mcrew > ecrew)
		{
			m_rank_bonus = makeint(0.5 * MOD_SKILL_ENEMY_RATE * makefloat((mcrew - ecrew) / makefloat(ecrew)));
			Log_TestInfo("����� � ������ ������ �� ������� � �����������: " + m_rank_bonus);
		}
		return 0;
	}
	else
	{
		return makeint(5 * MOD_SKILL_ENEMY_RATE * makefloat((mcrew - ecrew) / makefloat(ecrew)));
	}
}

int GetBoarding_enemy_hp_Bonus(int mcrew, int ecrew) 
{
    m_rank_bonus = 0;
    e_rank_bonus = 0;
	if (mcrew < 1) mcrew = 1;
    if (true)
	{     
		if (ecrew > mcrew)
		{
			e_rank_bonus = makeint(2 * MOD_SKILL_ENEMY_RATE * makefloat((ecrew - mcrew) / makefloat(mcrew)));
			Log_TestInfo("����� � ������ ������ �� ������� � �����������: " + e_rank_bonus);
		}
		return 0;
	}
	else
	{
		return makeint(6 * MOD_SKILL_ENEMY_RATE * makefloat((ecrew - mcrew) / makefloat(mcrew)));
	}
}

float GetBoarding_player_hp(float b_p_hp) 
{
	return b_p_hp; 
}

float GetBoarding_enemy_hp(float b_e_hp) 
{
	return b_e_hp + 4*(MOD_SKILL_ENEMY_RATE - 5); 
}

void SetFantomParamAbordOur(ref _pchar)
{
	_pchar.RankBonus = m_rank_bonus;
	_pchar.OurMan = true;
	SetFantomParamCommon(_pchar);
	DeleteAttribute(_pchar, "RankBonus");
	DeleteAttribute(_pchar, "OurMan");
}
void SetMushketerParamAbordOur(ref _pchar)
{
	_pchar.RankBonus = m_rank_bonus;
	_pchar.OurMan = true;
    CalculateAppropriateSkills(_pchar);
    SetFantomHP(_pchar);
	DeleteAttribute(_pchar, "RankBonus");
	DeleteAttribute(_pchar, "OurMan");
}

void SetFantomParamFortOur(ref _pchar)
{
	_pchar.RankBonus = m_rank_bonus;
	_pchar.OurMan = true;
	SetFantomParamCommon(_pchar);
	DeleteAttribute(_pchar, "RankBonus");
	DeleteAttribute(_pchar, "OurMan");
}
void SetMushketerParamFortOur(ref _pchar)
{
	_pchar.RankBonus = m_rank_bonus;
	_pchar.OurMan = true;
    CalculateAppropriateSkills(_pchar);
    SetFantomHP(_pchar);
	DeleteAttribute(_pchar, "RankBonus");
	DeleteAttribute(_pchar, "OurMan");
}

void SetFantomParamAbordEnemy(ref _pchar)
{
	ref MChar;

	MChar = GetMainCharacter();
	if (CheckAttribute(MChar, "EnemyRank"))
	{
		_pchar.BaseRank = MChar.EnemyRank;
	}
	_pchar.RankBonus = e_rank_bonus;

	SetFantomParamCommon(_pchar);
	DeleteAttribute(_pchar, "BaseRank");
	DeleteAttribute(_pchar, "RankBonus");
}
void SetMushketerParamAbordEnemy(ref _pchar)
{
	ref MChar;
	MChar = GetMainCharacter();
	if (CheckAttribute(MChar, "EnemyRank"))
	{
		_pchar.BaseRank = MChar.EnemyRank;
	}
	_pchar.RankBonus = e_rank_bonus;
    CalculateAppropriateSkills(_pchar);
    SetFantomHP(_pchar);
	DeleteAttribute(_pchar, "BaseRank");
	DeleteAttribute(_pchar, "RankBonus");
}

void SetFantomParamFortEnemy(ref _pchar)
{
	ref MChar;

	MChar = GetMainCharacter();
	if (CheckAttribute(MChar, "EnemyRank"))
	{
		_pchar.BaseRank = MChar.EnemyRank;
	}
	_pchar.RankBonus = e_rank_bonus;

	SetFantomParamCommon(_pchar);
	DeleteAttribute(_pchar, "BaseRank");
	DeleteAttribute(_pchar, "RankBonus");
}
void SetMushketerParamFortEnemy(ref _pchar)
{
	ref MChar;
	MChar = GetMainCharacter();
	if (CheckAttribute(MChar, "EnemyRank"))
	{
		_pchar.BaseRank = MChar.EnemyRank;
	}
	_pchar.RankBonus = e_rank_bonus;
    CalculateAppropriateSkills(_pchar);
    SetFantomHP(_pchar);
	DeleteAttribute(_pchar, "BaseRank");
	DeleteAttribute(_pchar, "RankBonus");
}


void SetFantomParamHunter(ref sld)
{
    SetSeaFantomParam(sld, "hunter");
    LAi_SetHP(sld, LAI_DEFAULT_HP_MAX + sti(sld.chr_ai.hp), LAI_DEFAULT_HP_MAX + sti(sld.chr_ai.hp));
    TakeNItems(sld,"potion2", 2);
}



void AntiCheat(ref _pchar)
{
     
}

void CheckAntiCheat()
{
 	if (CheckAttribute(PChar, "SystemInfo.CRC"))
 	{
		if (stf(PChar.SystemInfo.CRC) != GetCRCCheatSum(PChar))
		{
		    bPlayerIsCheater = true;
		}
	}
}

void SetAntiCheat()
{
	PChar.SystemInfo.CRC = GetCRCCheatSum(PChar);
}

float GetCRCCheatSum(ref _PChar)
{
	return makefloat(GetSPECIALSum(_PChar) + GetSkillSum(_PChar) + sti(_PChar.Ship.Type) + stf(_PChar.Health.HP) + sti(_PChar.rank) + sti(_PChar.Money) + stf(_PChar.chr_ai.hp));
}




float Sea_TurnRateMagicNumber();
{
    return 244.444; 
}


 
float Sea_ApplyMaxSpeedZ(aref arCharShip, float fWindDotShip, ref rCharacter) 
{
	ref		rShip = GetRealShip(sti(arCharShip.Type)); 
    float   fMaxSpeedZ = 0.0;
    float   fWindAgainstSpeed;
	
	fMaxSpeedZ 			= stf(arCharShip.MaxSpeedZ);	
	fWindAgainstSpeed   = FindShipWindAgainstSpeed(rCharacter);
	arCharShip.WindAgainstSpeed = acos(1.0 - fWindAgainstSpeed) * 180.0/PI;
		
	float BtWindR = 1.0 -  stf(fWindAgainstSpeed);
	
	float fkoeff = stf(fWindAgainstSpeed); 
	if (stf(fkoeff) < 1) fkoeff = 1; 

	if(fWindDotShip < BtWindR) 
	{
		fMaxSpeedZ = fMaxSpeedZ * (1.0 + 0.974 * (fWindDotShip - BtWindR) / (1.0 + BtWindR));
	}
	else 
	{
		fMaxSpeedZ = fkoeff*fMaxSpeedZ * (1.0  - (fWindDotShip - BtWindR)/ 2.0);
	}	
	
	return fMaxSpeedZ;
}









