

void LoginCharactersInLocation(ref loc)
{
    
	SetTimeScale(1.0);
    TimeScaleCounter = 0;
� � DelPerkFromActiveList("TimeSpeed");
	
	LocAi_Init(loc);
	string locID = loc.id;
	for(int i = 0; i < MAX_CHARACTERS; i++)
	{
        DelBakSkillAttr(&Characters[i]); 
        ClearCharacterExpRate(&Characters[i]);
		LoginCharacter(&Characters[i], locID);
	}
	if(actLoadFlag)
	{
		for(i = 0; i < MAX_CHARS_IN_LOC; i++)
		{
            DelBakSkillAttr(&Characters[LOC_FANTOM_CHARACTERS + i]); 
            ClearCharacterExpRate(&Characters[LOC_FANTOM_CHARACTERS + i]);
			LoginCharacter(&Characters[LOC_FANTOM_CHARACTERS + i], locID);
		}
	}
	
	
	for(i = FANTOM_CHARACTERS; i < TOTAL_CHARACTERS; i++)
	{
        DelBakSkillAttr(&Characters[i]); 
        ClearCharacterExpRate(&Characters[i]);
        LoginCharacter(&Characters[i], locID);
	}
	LocAi_PostInit(loc);
	
	Dead_Char_num = 0; 
	
}

void LoginCharacter(aref chr, string locID)
{
	if(LAi_CharacterLogin(chr, locID))
	{
		bool isNoCreated = true;
		if(CreateCharacter(chr))
		{
			isNoCreated = false;			
			if(TeleportCharacterToLocator(chr, chr.location.group, chr.location.locator)==0)
			{
				if((CheckAttribute(chr, "index") != false) && (GetMainCharacterIndex() == sti(chr.index)))
				{
					Trace("Main character <" + chr.id + "> error teleportation by location: " + chr.location + "  on locator: " + chr.location.group + "::" + chr.location.locator);
				}
				else
				{
					isNoCreated = true;
					DeleteCharacter(chr);
					Trace("Delete character <" + chr.id + "> , error teleportation by location: " + chr.location + " on locator: " + chr.location.group + "::" + chr.location.locator);
				}
			}
		}else{
			Trace("Can't create character: " + chr.id);
		}
		if(isNoCreated)
		{
			LAi_CharacterLogoff(chr);
		}
	}
}

void LogoffCharacter(aref chr)
{
	if(IsEntity(chr))
	{
        DelBakSkillAttr(chr); 
		LAi_CharacterLogoff(chr);
		CharacterExitFromLocation(chr);
	}
}


bool ChangeCharacterAddress(ref character, string location_id, string locator)
{
	return ChangeCharacterAddressGroup(character, location_id, "goto", locator);
}

string GetCharacterShipLocation(ref rCharacter)
{
	if (CheckAttribute(rCharacter,"location.from_sea")) return rCharacter.location.from_sea;
	Trace("Character '" + rCharacter.id + "' location.from_sea is absent");
	return "None";
}

bool SetCharacterShipLocation(ref character, string location_id)
{
	if (location_id == "")  
	{
		character.location.from_sea = location_id;	
		return true;
	}
	
	int lindex = FindLocation(location_id);
	if (lindex < 0)
	{
		Trace("Incorrect location id 'SetCharacterShipLocation' (location " + location_id + " not found");
		return false;
	}
	character.location.from_sea = location_id;
	return true;
}

bool ChangeCharacterShipGroup(ref rCharacter, string group_id)
{
	rCharacter.Ship.AI.GroupName = group_id;
	if (IsEntity(&AISea))
	{
		SendMessage(&AISea,"las",AI_MESSAGE_SHIP_CHANGE_GROUP,&rCharacter,group_id);
	}
	return true;
}

bool SetCharacterIslandLocation(ref character, string location_id, string group, string locator, string group_id, string task, string target_group_id)
{
	bool bRet = ChangeCharacterAddressGroup(character, location_id, group, locator);
	if (!bRet) return false;
	character.Ship.AI.GroupName = group_id;
	character.Ship.AI.Task = task;
	character.Ship.AI.Task.Group = target_group_id;
	return true;
}

bool ChangeCharacterAddressGroup(ref character, string location_id, string group, string locator)
{
	
	int lindex = FindLocation(location_id);
	if(lindex < 0)
	{
		
		LogoffCharacter(character);
		lindex = FindIsland(location_id);
		if(lindex < 0)
		{
			Trace("Incorrect location id 'ChangeCharacterAddressGroup' (location " + location_id + " not found");
			return false;
		}
		character.location = location_id;
		character.location.group = group;
		character.location.locator = locator;
		return true;
	}
	
	if (!CheckAttribute(character, "location"))
	{
	    trace ("character " + character.id + " have no location field");
		character.location = "none";
	}
	else
	{
		if (location_id == character.location && IsEntity(character)) 
		{
			TeleportCharacterToLocator(character, group, locator);
			character.location = location_id;
			character.location.group = group;
			character.location.locator = locator;
			return true;
		}
	}
	
	LogoffCharacter(character);
	
	string oldLocation = character.location;
	character.location = location_id;
	character.location.group = group;
	character.location.locator = locator;
	
	if(IsEntity(&Locations[lindex]))
	{
		LoginCharacter(character, Locations[lindex].id);
		LAi_PostLoginInit(character);
	}
	return true;
}



