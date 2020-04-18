
void AIAttack_GroupAttack(string sGroupAttacker, string sGroupAttacked, bool bAttackedTask)
{
	ref rG1 = Group_GetGroupByID(sGroupAttacker);
	ref rG2 = Group_GetGroupByID(sGroupAttacked);

	
	

	
	

	
	string sGroupType2 = Group_GetTypeR(rG2);

    
    if (!CheckAttribute(rG1, "Task")) { return; }
    
    
	
	if (sti(rG1.Task) == AITASK_ATTACK)
	{
		if (rG1.Task.Target != sGroupAttacked) { return; }
		
	}
	
	
	if (sGroupAttacker != PLAYER_GROUP)
	{
		int iIndex = 0;

		int iCharactersNum2 = Group_GetCharactersNumR(rG2);
		int iDeadCharactersNum2 = Group_GetDeadCharactersNumR(rG2);
		int iCharactersNum1 = Group_GetCharactersNumR(rG1) - Group_GetDeadCharactersNumR(rG1); 

		
		if (iCharactersNum2 != iDeadCharactersNum2 && iCharactersNum2 > 0)
		{
			int i = 0;
			
			while (true)
			{
				int iCharacterIndex = Group_GetCharacterIndexR(rG1, i); i++;
				if (iCharacterIndex < 0) { break; }
				
				if (LAi_IsDead(&Characters[iCharacterIndex])) { continue; }

				int iCharacterVictim = -1;
				while (iCharacterVictim < 0)
				{
					iCharacterVictim = Group_GetCharacterIndexR(rG2, iIndex); 
					if (iCharacterVictim < 0) { iIndex = 0; continue; }
					if (LAi_IsDead(&Characters[iCharacterVictim])) { iCharacterVictim = -1; }
					iIndex++;
				}
				
                if (CheckAttribute(&Characters[iCharacterIndex], "ShipTaskLock"))  { continue; } 
				
				if (CheckAttribute(&Characters[iCharacterIndex], "AnalizeShips"))
				{				
					
					if (CheckAttribute(&Characters[iCharacterIndex], "Tmp.fWatchFort.Qty") && sti(Characters[iCharacterIndex].Tmp.fWatchFort.Qty) == 200)
					{
						Characters[iCharacterIndex].Tmp.fWatchFort = 199; 
						Characters[iCharacterIndex].Ship.LastBallCharacter = iCharacterVictim;
					}
					else
					{	

						
						if (stf(Characters[iCharacterIndex].ship.hp) > (stf(Characters[iCharacterVictim].ship.hp) / 2) || GetCrewQuantity(&Characters[iCharacterIndex]) > GetCrewQuantity(&Characters[iCharacterVictim]))
						{	
							if (((iCharactersNum2 - iDeadCharactersNum2) / iCharactersNum1) >= 2.0 && sti(RealShips[sti(characters[iCharacterIndex].ship.type)].Class) > sti(RealShips[sti(characters[iCharacterVictim].ship.type)].Class))
							{							
								Ship_SetTaskRunaway(SECONDARY_TASK, iCharacterIndex, iCharacterVictim);								
							}
							else
							{
								Ship_SetTaskAttack(SECONDARY_TASK, iCharacterIndex, iCharacterVictim);
							}							
						}
						else
						{	
							if ((iCharactersNum1 / (iCharactersNum2 - iDeadCharactersNum2)) >= 2.2)
							{
								Ship_SetTaskAttack(SECONDARY_TASK, iCharacterIndex, iCharacterVictim);
							}
							else
							{
								Ship_SetTaskRunaway(SECONDARY_TASK, iCharacterIndex, iCharacterVictim);
							}							
						}						
					}					
				}
				else
				{
					Ship_SetTaskAttack(SECONDARY_TASK, iCharacterIndex, iCharacterVictim);
				}
				
				
			}				
		}		
	}
	
	
	bool bTaskLock = false;

	if (sGroupAttacked == PLAYER_GROUP) { return; }
	if (!bAttackedTask) { return; } 

	if (Group_isTaskLockR(rG2)) 
	{ 
        
	    if (!CheckAttribute(rG2, "Task")) { return; }
	    
		if (sti(rG2.Task) != AITASK_ATTACK) { return; }
		if (rG2.Task.Target != sGroupAttacker) { return; }

		bTaskLock = true;
	}

	 
	
	Group_SetTaskAttackEx(sGroupAttacked, sGroupAttacker, false);
	
}

int AIAttack_SelectTask(string sGroupType, float fRatio)
{
	return AITASK_ATTACK; 
	 
}


void AIAttack_CheckTask(string sGroupID)
{
	ref rG1 = Group_GetGroupByID(sGroupID);
	ref rG2;
    
	string sGroupType1 = Group_GetTypeR(rG1);

	ref rCharacter1 = Group_GetGroupCommanderR(rG1);

	
	if (sGroupID == PLAYER_GROUP) { return; }

	
	float fAng = frnd() * PIm2;
	
	
	string rG2name = "none_group_1"; 
	if (CheckAttribute(rG1, "Task.Target"))
	{
        rG2name = rG1.Task.Target;
	}
	if (Group_isDead(rG2name))
	{
		switch (sGroupType1)
		{
			case "trade":
			    if (CheckAttribute(rG1, "Task.Target.Pos.x")) 
				{
					Group_SetTaskMove(sGroupID, stf(rG1.Task.Target.Pos.x), stf(rG1.Task.Target.Pos.z));
				}
				else
				{
				    Group_SetTaskMove(sGroupID, 10000.0 * sin(fAng) , 10000.0 * cos(fAng));
				}
			break;
			case "war":
				Group_SetTaskMove(sGroupID, 10000.0 * sin(fAng) , 10000.0 * cos(fAng));
			break;
			case "pirate":
				Group_SetTaskMove(sGroupID, 10000.0 * sin(fAng) , 10000.0 * cos(fAng));
			break;
		}
		
		return;
	}
    
    rG2 = Group_GetGroupByID(rG1.Task.Target);
    
	 

	
	int iIndex = 0;

	int iCharactersNum2 = Group_GetCharactersNumR(rG2);

	
	int i = 0;
	
	bool isDead = false;
	int  newCommanderIndex = -1;
	int iCharacterIndex;
	
	while (true)
	{
		iCharacterIndex = Group_GetCharacterIndexR(rG1, i);
		i++;
		if (iCharacterIndex < 0) { break; }
		ref rCharacter = GetCharacter(iCharacterIndex);
		if (LAi_IsDead(rCharacter))
		{
   			if (iCharacterIndex == sti(rCharacter1.index)) {isDead = true;} 
			continue;
		}
		if (iCharacterIndex != sti(rCharacter1.index)) newCommanderIndex = iCharacterIndex; 

		if (CheckAttribute(rCharacter, "SeaAI.Task"))
		{
			if (sti(rCharacter.SeaAI.Task) != AITASK_ATTACK) { continue; }
			if (!LAi_IsDead(&Characters[sti(rCharacter.SeaAI.Task.Target)])) { continue; }
		}

		int iCharacterVictim = -1;
		while (iCharacterVictim < 0)
		{
			iCharacterVictim = Group_GetCharacterIndexR(rG2, iIndex); 
			if (iCharacterVictim < 0) { iIndex = 0; continue; }
			if (LAi_IsDead(&Characters[iCharacterVictim])) { iCharacterVictim = -1; }
			iIndex++;
		}
        if (CheckAttribute(&Characters[iCharacterIndex], "ShipTaskLock"))  { continue; } 
		Ship_SetTaskAttack(SECONDARY_TASK, iCharacterIndex, iCharacterVictim);
	}
	if (isDead && newCommanderIndex != -1) Group_SetGroupCommander(sGroupID, Characters[newCommanderIndex].id); 
}
