
#define MUSIC_CHANGE_TIME  3000
#define MUSIC_SILENCE_TIME 180000.0
#define SOUNDS_FADE_TIME   200

#event_handler ("LoadSceneSound", "LoadSceneSound")

int Play3DSound(string name, float x, float y, float z)
{
	InitSound();
	
	return SendMessage(Sound,"lsllllllfff",MSG_SOUND_PLAY, name, SOUND_WAV_3D, VOLUME_FX, false, false, false, 0, x, y, z);
}

int Play3DSoundCached(string name, float x, float y, float z)
{
	InitSound();
	
	return SendMessage(Sound,"lsllllllfff",MSG_SOUND_PLAY, name, SOUND_WAV_3D, VOLUME_FX, false, false, true, 0, x, y, z);
}

int Play3DSoundComplex(string name, float x, float y, float z, bool bLooped, bool bCached)
{
	InitSound();
	return SendMessage(Sound,"lsllllllfff",MSG_SOUND_PLAY, name, SOUND_WAV_3D, VOLUME_FX, false, bLooped, bCached, 0, x, y, z);
}

int PlayStereoSound(string name)
{
	InitSound();
	
	return SendMessage(Sound,"lslllll",MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_FX, false, false, false);
}

int PlayStereoSoundLooped(string name)
{
	InitSound();
	
	return SendMessage(Sound,"lsllll",MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_FX, false, true, false);
}

int PlayStereoSoundLooped_JustCache(string name)
{
	InitSound();
	
	return SendMessage(Sound,"lslllll",MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_FX, true, true, false);
}

int PlayStereoOGG(string name)
{
	InitSound();
	
	return SendMessage(Sound,"lsllllll",MSG_SOUND_PLAY, name, SOUND_MP3_STEREO, VOLUME_FX, false, false, false, 0); 
}


void StopSound(int id, int fade)
{
	InitSound();
	
	SendMessage(Sound, "lll", MSG_SOUND_STOP, id, fade);
}

void ResumeSound(int id, int fade)
{
	InitSound();
	
	SendMessage(Sound, "lll", MSG_SOUND_RESUME, id, fade);
}

void ReleaseSound(int id)
{
	InitSound();
	
	SendMessage(Sound, "ll", MSG_SOUND_RELEASE, id);
}


void ResetSoundScheme()
{
	InitSound();
	
	SendMessage(Sound,"l",MSG_SOUND_SCHEME_RESET);
}

void SetSoundScheme(string schemeName)
{
	InitSound();
	
	SendMessage(Sound,"ls",MSG_SOUND_SCHEME_SET,schemeName);
}

void AddSoundScheme(string schemeName)
{
	InitSound();
	
	SendMessage(Sound,"ls",MSG_SOUND_SCHEME_ADD,schemeName);
}

 

void SetWeatherScheme(string scheme)
{
	if (Whr_IsStorm())
	{
		if (Whr_IsNight())
		{
			SetSoundScheme(scheme+"_night_storm");
		}
		else
		{
			SetSoundScheme(scheme+"_day_storm");
		}
	}
	else 
	{ 
		if (Whr_IsRain())
		{
			if (Whr_IsNight())
			{
					SetSoundScheme(scheme+"_night_rain");
			}
			else
			{
					SetSoundScheme(scheme+"_day_rain");
			}					
		}
		else
		{
			if (Whr_IsNight())
			{
					SetSoundScheme(scheme+"_night");
			}
			else
			{
					SetSoundScheme(scheme+"_day");
			}
		}
	}
}

 
void SetSchemeForLocation (ref loc)
{
    ref mchref = GetMainCharacter();
    mchref.GenQuest.God_hit_us = false; 
    int iColony = -1; 
    
    if(CheckAttribute(loc,"type"))
	{
		ResetSoundScheme();
		SetMusicAlarm(""); 
		switch (loc.type)
		{
			case "town":
				SetWeatherScheme("town");
				if (CheckAttribute(loc,"QuestCapture"))
				{
					SetMusicAlarm("music_military");
				}
				if (CheckAttribute(loc,"fastreload"))
				{
					iColony = FindColony(loc.fastreload);
				}
				if (iColony != -1)
				{
					if (CheckAttribute(loc,"QuestCapture")) SetMusicAlarm("music_military");
					else 
				{
					if (Whr_IsDay()) SetMusicAlarm(NationShortName(sti(Colonies[iColony].nation)) + "_music_day");
					else SetMusicAlarm(NationShortName(sti(Colonies[iColony].nation)) + "_music_night");
				}
				}
				else
				{
					SetMusicAlarm("music_gorod");
				}
			break;
			
			case "land": 
				SetWeatherScheme("land");
				SetMusicAlarm("music_jungle");
			break;
			
			case "jungle":
				SetWeatherScheme("land");
				if (loc.id.label == "Village" || loc.id.label == "ExitTown" || loc.id.label == "Incas Temple")
				{
					switch (loc.id.label)
					{
						case "ExitTown":
							if (Whr_IsDay()) SetMusicAlarm("music_exittown");
							else SetMusicAlarm("music_nightjungle");
						break;
						case "Incas Temple":
							SetMusicAlarm("music_Incas_Temple");
						break;
						case "Village":
							SetMusicAlarm("music_village");
						break;
					}
				}
				else
				{
					if (Whr_IsDay()) SetMusicAlarm("music_jungle");
					else SetMusicAlarm("music_nightjungle");
				}
				DeleteAttribute(pchar, "CheckStateOk"); 
			break;
			
			case "mayak":
				ResetSoundScheme();
				SetWeatherScheme("seashore");
				SetMusicAlarm("music_mayak");
			break;
			
			case "seashore": 
				ResetSoundScheme();
				SetWeatherScheme("seashore");
				SetMusicAlarm("music_shore");
				DeleteAttribute(pchar, "CheckStateOk"); 
			break;
			
			case "cave": 
				SetSoundScheme("cave");
				SetMusicAlarm("music_cave");
				bMonstersGen = false; 
			break;
			
			case "dungeon": 
				SetSoundScheme("dungeon");
				SetMusicAlarm("music_cave");
				bMonstersGen = false; 
			break;
			
			case "reef":
				ResetSoundScheme();
				SetSoundScheme("reef");
				SetMusicAlarm("music_reef");
			break;
			
			case "mine":
				ResetSoundScheme();
				SetSoundScheme("mine");
				SetMusicAlarm("music_cave");
			break;
			
			case "inca_temple": 
				SetSoundScheme("inca_temple");
				SetMusicAlarm("music_coridor");
			break;
			
			case "x_seashore":
				ResetSoundScheme();
				SetWeatherScheme("seashore");
				SetMusicAlarm("music_teno");
			break;
			
			case "x_jungle":
				ResetSoundScheme();
				SetWeatherScheme("land");
				SetMusicAlarm("music_teno");
			break;
			
			case "questisland":
				ResetSoundScheme();
				if (loc.id.label == "jungle") SetWeatherScheme("land");
				else SetWeatherScheme("seashore");
				SetMusicAlarm("music_questislands");
			break;
			
			case "plantation":
				ResetSoundScheme();
				SetWeatherScheme("land");
				SetMusicAlarm("music_plantation");
			break;
			
			case "house":
				SetSoundScheme("house");
				if (CheckAttribute(loc,"brothel") && sti(loc.brothel) == true)
				{
					SetMusicAlarm("music_brothel");
				}
				else
				{
					if (CheckAttribute(loc,"id.label") && loc.id.label == "portoffice")
					{
						SetMusicAlarm("music_portoffice");
					}
					else
					{
						SetMusicAlarm("music_gorod");
					}
				}
				mchref.GenQuest.God_hit_us = true; 
			break;
			
			case "tavern":
				SetSoundScheme("tavern");
				if (CheckAttribute(loc,"fastreload"))
				{
					iColony = FindColony(loc.fastreload);
				}
				if (iColony != -1)
				{
			    	SetMusicAlarm(NationShortName(sti(Colonies[iColony].nation)) + "_music_tavern");
				}
				else
				{
					SetMusicAlarm("music_tavern");
				}
			break;
			
			case "shop":
				SetSoundScheme("shop");
				if (CheckAttribute(loc,"id.label") && loc.id.label == "Usurer House")
				{
					SetMusicAlarm("music_bank");
				}
				else
				{
					SetMusicAlarm("music_shop");
				}
			break;
			
			case "residence":
				SetSoundScheme("residence");
				if (CheckAttribute(loc,"fastreload"))   
				{
					iColony = FindColony(loc.fastreload);
				}
				if (iColony != -1)
				{
			    	SetMusicAlarm(NationShortName(sti(Colonies[iColony].nation)) + "_music_gubernator");
				}
				else
				{
					SetMusicAlarm("music_deck");
				}
			break;
			
			case "church":
				if (isDay()) SetSoundScheme("church");
				if (CheckAttribute(loc,"fastreload"))
				{
					iColony = FindColony(loc.fastreload);
				}
				if (iColony != -1)
				{
			    	SetMusicAlarm(NationShortName(sti(Colonies[iColony].nation)) + "_music_church");
				}
				else
				{
				SetMusicAlarm("music_church");
				}
			break;
			
			case "shipyard":
				SetSoundScheme("shipyard");
				SetMusicAlarm("music_shipyard");
			break;
			
			case "fort_attack": 
				SetSoundScheme("fort_attack");
				SetMusicAlarm("music_bitva");
			break;
			
			case "fort": 
				SetWeatherScheme("seashore");
				if (CheckAttribute(loc, "parent_colony"))
				{
					iColony = FindColony(loc.parent_colony);
				}
				if (iColony != -1)
				{
					if (CheckAttribute(loc,"QuestCapture")) SetMusicAlarm("music_military");
					else SetMusicAlarm("music_fort");
				}
				else
				{
					SetMusicAlarm("music_gorod");
				}
			break;
			
			case "deck": 
				SetSoundScheme("deck");
				if (Whr_IsDay()) SetMusic("music_sea_day");
				else SetMusic("music_sea_night");
			break;
			
			case "deck_fight": 
				SetSoundScheme("deck_fight");
				SetMusic("music_abordage");
			break;
			
			case "slave_deck": 
				SetSoundScheme("slave_deck");
				
			break;
			
			case "boarding_cabine":
				SetSoundScheme("cabine");
				SetMusic("music_abordage");
			break;
			
			case "sailing_cabine":
				SetSoundScheme("sail_cabine");
				if (Whr_IsDay()) SetMusicAlarm("music_sea_day");
				else SetMusicAlarm("music_sea_night");
			break;
			
			case "incquisitio":
				SetSoundScheme("incquisitio");
				SetMusicAlarm("music_incquisitio");
			break;
			
			case "jail":
				SetSoundScheme("jail");
				SetMusicAlarm("music_jail");
			break;
			
			case "ammo":
				SetSoundScheme("jail");
				SetMusicAlarm("music_jail");
			break;
			
			case "LostShipsCity":
				SetWeatherScheme("LostShipsCity");
				SetMusicAlarm("music_LostShipsCity");
			break;
			
			case "LSC_inside":
				SetWeatherScheme("LSC_inside");
				SetMusicAlarm("music_LostShipsCity");
			break;
			
			case "underwater":
				SetSoundScheme("underwater");
				SetMusicAlarm("music_underwater");
			break;
			
			case "teno":
				SetWeatherScheme("land");
				SetMusicAlarm("music_teno");
			break;
			
			case "teno_inside":
				SetSoundScheme("teno_inside");
				SetMusicAlarm("music_teno_inside");
			break;
			
			case "Alcove": 
				SetSoundScheme("teno_inside");
				SetMusicAlarm("music_alcove");
			break;
			
			case "Alcove_1": 
				SetSoundScheme("teno_inside");
				SetMusicAlarm("music_alcove_1");
			break;
			
			case "Judgement_dungeon": 
				SetSoundScheme("dungeon");
				SetMusicAlarm("music_alcove");
			break;
			
			case "Judgement_hell_dungeon": 
				SetSoundScheme("dungeon");
				if (loc.id == "Judgement_dungeon_10") SetMusicAlarm("music_retribution_1");
				else SetMusicAlarm("music_retribution");
			break;
		}
	}
	SetStaticSounds(loc);
}

void SetStaticSounds (ref loc)
{
	if(IsEntity(loc) != true) return;
	string locatorGroupName = "locators.sound";
	if(CheckAttribute(loadedLocation, locatorGroupName) == 0) return;
	aref locatorGroup;
	makearef(locatorGroup, loc.(locatorGroupName));
	int locatorCount = GetAttributesNum(locatorGroup);
	if(locatorCount <= 0) return;
	string locatorName, locatorType;
	int locatorNameLength;

	for(int i = 0; i < locatorCount; i++)
	{
		aref locator = GetAttributeN(locatorGroup, i);
		locatorName = GetAttributeName(locator);
		locatorNameLength = strlen(locatorName);
		locatorType = strcut(locatorName, 0, locatorNameLength-3);
		if ((locatorType == "nightinsects")||(locatorType == "torch"))
		{
			if (Whr_IsDay() && loc.type != "Dungeon" && loc.type != "cave" && loc.type != "fort_attack") continue;
   		}
		if (locatorType == "shipyard")
		{
			if (Whr_IsNight()) continue;
   		}
		if (locatorType == "church")
		{
			if (Whr_IsNight()) continue;
   		}
		if (locatorType == "windmill")
		{
			continue;
   		}

		
		SendMessage(Sound, "lsllllllfff", MSG_SOUND_PLAY, locatorType, SOUND_WAV_3D, VOLUME_FX, 0, 1, 0, 0, stf(locator.x), stf(locator.y), stf(locator.z));
	}
	
}

void SetSchemeForSea ()
{
	ResetSoundScheme();

	
	if (Whr_IsNight())
	{
		if (Whr_IsStorm())
		{
			AddSoundScheme("sea_night_storm");
			SetMusic("music_storm");
		}
		else 
		{ 
			if (pchar.Ship.POS.Mode == SHIP_WAR)
			{
				SetMusic("music_sea_battle");
			}
			else
			{
				if (Whr_IsDay()) SetMusic("music_sea_day");
				else SetMusic("music_sea_night");
			}
			if (Whr_IsRain())
			{
				AddSoundScheme("sea_night_rain");
			}
			else
			{
				AddSoundScheme("sea_night");
			}
		}
	}
	else 
	{
		if (Whr_IsStorm())
		{
			AddSoundScheme("sea_day_storm");
			SetMusic("music_storm");
		}
		else 
		{ 
   			if (pchar.Ship.POS.Mode == SHIP_WAR)
			{
				SetMusic("music_sea_battle");
			}
			else
			{
				if (Whr_IsDay()) SetMusic("music_sea_day");
				else SetMusic("music_sea_night");
			}
			if (Whr_IsRain())
			{
				AddSoundScheme("sea_day_rain");
			}
			else
			{
				AddSoundScheme("sea_day");
			}
		}
	}
	ResumeAllSounds();
}

void SetSchemeForMap ()
{
	ResetSoundScheme();
	AddSoundScheme("sea_map");
	SetMusic("music_map");
	ResumeAllSounds();
	bFortCheckFlagYet = false; 
}


int musicID = -1;
int oldMusicID = -1;
int boardM = -1;
string musicName = "";
string oldMusicName = "";
void SetMusic(string name)
{
	if (pchar.location == "UnderWater") return; 
	InitSound();
	

	if (name == musicName)
	{
		SendMessage(Sound, "lll", MSG_SOUND_RESUME, musicID, SOUNDS_FADE_TIME);
		return;
	}

	
	if (oldMusicID >= 0)
	{
		SendMessage(Sound, "ll", MSG_SOUND_RELEASE, oldMusicID);
		oldMusicID = -1;
	}

	if (musicID >= 0)
	{
		SendMessage(Sound, "lll", MSG_SOUND_STOP, musicID, MUSIC_CHANGE_TIME);
		oldMusicID = musicID;
	}

	
	
	
	
	musicID = SendMessage(Sound, "lslllllllf", MSG_SOUND_PLAY, name, SOUND_MP3_STEREO, VOLUME_MUSIC, true, true, false, 0, MUSIC_CHANGE_TIME, 1.0);
	SendMessage(Sound, "lll", MSG_SOUND_RESUME, musicID, MUSIC_CHANGE_TIME);
	
	oldMusicName = musicName;
	musicName = name;
}


void SetMusicOnce(string name)
{
	if (pchar.location == "UnderWater") return; 
	InitSound();
	
	if (name == musicName)
	{
		SendMessage(Sound, "lll", MSG_SOUND_RESUME, musicID, SOUNDS_FADE_TIME);
		return;
	}

	if (oldMusicID >= 0)
	{
		SendMessage(Sound, "ll", MSG_SOUND_RELEASE, oldMusicID);
		oldMusicID = -1;
	}

	if (musicID >= 0)
	{
		SendMessage(Sound, "lll", MSG_SOUND_STOP, musicID, MUSIC_CHANGE_TIME);
		oldMusicID = musicID;
	}
	musicID = SendMessage(Sound, "lslllllllf", MSG_SOUND_PLAY, name, SOUND_MP3_STEREO, VOLUME_MUSIC, false, false, false, 0, MUSIC_CHANGE_TIME, 1.0);
	SendMessage(Sound, "lll", MSG_SOUND_RESUME, musicID, MUSIC_CHANGE_TIME);
	
	oldMusicName = musicName;
	musicName = name;
}

void FadeOutMusic(int _time)
{
	if (musicID >= 0)
	{
		StopSound(musicID, _time);
		musicID = -1;
		musicName = "";
	}
}


void PauseAllSounds()
{
	
	SendMessage(Sound,"lll",MSG_SOUND_STOP, 0, SOUNDS_FADE_TIME);
}

void ResumeAllSounds()
{
	
	SendMessage(Sound,"lll",MSG_SOUND_RESUME, musicID, SOUNDS_FADE_TIME);
}


int PlaySoundDist3D(string name, float x, float y, float z)
{
	return Play3DSound(name, x,y,z);
}

int PlaySoundLoc3D(string name, float x, float y, float z)
{
	return Play3DSoundCached(name, x,y,z);
}

int PlaySound3D(string name, float x, float y, float z)
{
	return Play3DSound(name, x,y,z);
}

void Sound_SetVolume(int iSoundID, float fVolume)
{
	SendMessage(Sound, "llf", MSG_SOUND_SET_VOLUME, iSoundID, fVolume);
}

int PlaySound(string name)
{
	return PlayStereoSound(name);
}

int PlaySoundComplex(string sSoundName, bool bSimpleCache, bool bLooped, bool bCached, int iFadeTime)
{
	return SendMessage(Sound,"lsllllll",MSG_SOUND_PLAY,VOLUME_FX,sSoundName,SOUND_WAV_3D,bSimpleCache,bLooped,bCached,iFadeTime);
}

void StopMusic()
{
}

void PlayMusic(string n)
{
}



object Sound;

int alarmed = 0;
int oldAlarmed = 0;
bool seaAlarmed = false;
bool oldSeaAlarmed = false;
void SetMusicAlarm(string name)
{
	if (alarmed == 0)
	{
		SetMusic(name);
	}
	else
	{
  		if (loadedLocation.type == "x_jungle" || loadedLocation.type == "x_seashore" || loadedLocation.id.label == "Maze") SetMusic("music_teno"); 
		else
		{
			if (loadedLocation.id.label == "Alcove")
			{
				if (loadedLocation.type == "Alcove") SetMusic("music_alcove");
				else SetMusic("music_alcove_1");
			}
		else
		{
			if (loadedLocation.id == "shore67" || loadedLocation.id == "IslaDeVieques_HouseEntrance" || loadedLocation.id == "Shore_mask") SetMusic("music_q_battle");
		else
		{
  		SetMusic("music_bitva");
		if (LAi_boarding_process != 0)
		{
			if (!CheckAttribute(loadedLocation, "CabinType"))
			{
				boardM = 1; 
			}
		}
	}
}
}
}
}

void Sound_OnAllarm()
{
	Sound_OnAlarm(GetEventData());
}

int abordageSoundID;

void Sound_OnAlarm(bool _alarmed)
{
	alarmed = _alarmed;
	if (alarmed == oldAlarmed)
		return;

	if (alarmed != 0)
	{ 
		if (loadedLocation.id == "shore67") SetMusic("music_q_battle");
		else SetMusic("music_bitva");
	}
	else
	{ 
		SetMusic(oldMusicName);
	}
	oldAlarmed = alarmed;
}

void Sound_OnSeaAlarm(bool _seaAlarmed)
{
	seaAlarmed = _seaAlarmed;
	if (seaAlarmed == oldSeaAlarmed)
		return;

	if (seaAlarmed)
	{ 
		SetMusic("music_sea_battle");
	}
	else
	{ 
		SetMusic(oldMusicName);
	}
	oldSeaAlarmed = seaAlarmed;
}


void Sound_OnSeaAlarm555(bool _seaAlarmed, bool bHardAlarm)
{
	if (bHardAlarm) { oldSeaAlarmed = !_seaAlarmed; }
	
	Sound_OnSeaAlarm(_seaAlarmed);
}

void InitSound()
{
	
	if (!IsEntity(&Sound))
	{
		CreateEntity(&Sound, "Sound");
		SetEventHandler("eventAllarm", "Sound_OnAllarm", 0);
	}
	
}

void ResetSound()
{
	
	if (musicID > 0)
	{
		StopSound(musicID,0);
	}
	if (oldMusicID > 0)
	{
		StopSound(oldMusicID,0);
	}
	ResetSoundScheme();
	
	StopSound(0,0);
	ReleaseSound(0);
	musicName = "";
	oldMusicName = "";
	musicID = -1;    
    oldMusicID = -1;
}

void LoadSceneSound()
{
	int i = FindLoadedLocation();
	if (i != -1)
		SetSchemeForLocation(&Locations[i]);
}
