
#event_handler("evntChrPerkDelay","procChrPerkDelay");

object ChrPerksList;

extern void extrnInitPerks();

void InitPerks()
{
	if( LoadSegment("interface\perks\perks_init.c") )
	{
		extrnInitPerks();
		UnloadSegment("interface\perks\perks_init.c");
	}
}

bool CheckCharacterPerk(ref chref, string perkName)
{
	if( CheckAttribute(chref,"perks.list."+perkName) ) return true;
	return false;
}

bool SetCharacterPerk(ref chref, string perkName)
{
	chref.perks.list.(perkName) = true;
	
	switch (perkName)
	{
		 
		
		case "Grus":
			return true; 
		break;
	}
	
	return false; 
}

void ActivateCharacterPerk(ref chref, string perkName)
{
	if( !CheckAttribute(&ChrPerksList,"list."+perkName) )
	{
		trace("Invalid perk name - " + perkName);
		return;
	}

	int timeDelay = 0;
	int timeDuration = 0;

	if( CheckAttribute(&ChrPerksList,"list."+perkName+".TimeDuration") )
	{	timeDelay = sti(ChrPerksList.list.(perkName).TimeDuration);
		timeDuration = timeDelay;
	}
	if( CheckAttribute(&ChrPerksList,"list."+perkName+".TimeDelay") )
	{	timeDelay = sti(ChrPerksList.list.(perkName).TimeDelay);
		if(timeDuration<=0)	{timeDuration=timeDelay;}
	}
    
    
	
    int cn;
    if (!CheckCharacterPerk(chref, perkName))
    {

        cn = GetOfficersPerkUsingIdx(chref, perkName);
        if (cn != -1)
        chref = GetCharacter(cn);
    }
    
	chref.perks.list.(perkName).delay = timeDelay;
	chref.perks.list.(perkName).active = timeDuration;

	
	if (sti(chref.index) == nMainCharacterIndex || isOfficerInShip(chref, false)) 
	{
		AddPerkToActiveList(perkName);
	}

	if(timeDelay>0) PostEvent("evntChrPerkDelay",1000,"sl",perkName,sti(chref.index));
	Event("eSwitchPerks","l",sti(chref.index));
	
	Event("eSwitchPerks","l", GetMainCharacterIndex());
}

bool GetCharacterPerkUsing(ref chref, string perkName)
{   
	if( !CheckAttribute(chref,"perks.list."+perkName) ) return false;
	if( CheckAttribute(chref,"perks.list."+perkName+".delay") ) return false;
	return true;
}

bool GetOfficersPerkUsing(ref chref, string perkName)
{ 
	string  sOfficerType;	
	ref   offc;	   
	bool  ok = false; 
	bool  okDelay = true;
	int   cn;
	if (GetCharacterPerkUsing(chref, perkName)) {return true;} 
	if (!CheckAttribute(chref,"perks.list."+perkName))  
	{
		for(int i=1; i<=6; i++)
		{
			sOfficerType = GetOfficerTypeByNum(i);
			if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType") && ChrPerksList.list.(perkName).OfficerType == sOfficerType)
			{
				cn = sti(chref.Fellows.Passengers.(sOfficerType));
				if(cn<0) {continue;}
				offc = &Characters[cn];
				if (CheckAttribute(offc, "perks.list."+perkName) )          ok = true;
				if (CheckAttribute(offc, "perks.list."+perkName+".delay") ) okDelay = false;
				
			}
		}
	}
	return (ok) && (okDelay);
}


int GetOfficersPerkUsingIdx(ref chref, string perkName)
{
	string  sOfficerType;
	int     cn;
	if (GetCharacterPerkUsing(chref, perkName)) {return sti(chref.index);} 
	for(int i=1; i<=6; i++)
	{
		sOfficerType = GetOfficerTypeByNum(i);
		if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType") && ChrPerksList.list.(perkName).OfficerType == sOfficerType)
		{
			cn = sti(chref.Fellows.Passengers.(sOfficerType));
			if(cn<0) {continue;}
			if (GetCharacterPerkUsing(&Characters[cn], perkName) ) {return cn;}
		}
	}
	return -1;
}

bool IsCharacterPerkOn(ref chref, string perkName)
{
	aref arRoot, arBase;
	makearef(arRoot,chref.perks.list);
	if( !CheckAttribute(arRoot,perkName) ) return false;
	makearef(arBase,ChrPerksList.list.(perkName));
	if( CheckAttribute(arBase,"TimeDuration") || CheckAttribute(arBase,"TimeDelay") ) {
		return CheckAttribute(arRoot,perkName+".active");
	}
	return true;
}

void CharacterPerkOff(ref chref, string perkName)
{
	if (perkName == "Turn180")
	{
		chref.Tmp.SpeedRecall = 0; 
	}
	DeleteAttribute(chref,"perks.list."+perkName+".active");
	Event("eSwitchPerks","l",sti(chref.index));	 
	
	Event("eSwitchPerks","l", GetMainCharacterIndex());
	if (sti(chref.index) == nMainCharacterIndex || isOfficerInShip(chref, false)) 
	{
		DelPerkFromActiveList(perkName);
	}
}

bool CheckOfficersPerk(ref chref, string perkName)
{ 
	bool ret = CheckOfficersPerkWOSelf(chref, perkName);

	if (ret) return true;
	
	if(IsCharacterPerkOn(chref,perkName) == true)
	{
		return true;
	}
	return false;
}

bool CheckOfficersPerkWOSelf(ref chref, string perkName)
{
	int     iOfficer = -1;
	string  sOfficerType;
	if(chref.id == pchar.id)
	{
		if (CheckAttribute(&ChrPerksList, "list." + perkName))
		{
			
			if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType"))
			{
				sOfficerType = ChrPerksList.list.(perkName).OfficerType;
				iOfficer = sti(pchar.Fellows.Passengers.(sOfficerType));
			}
		}	
	}

	if(iOfficer != -1)
	{
		if(IsCharacterPerkOn(GetCharacter(iOfficer), perkName) == true )
		{
			return true;
		}
	}
	return false;
}

bool CheckCompanionsPerk(ref chref, string perkName)
{
	int i,cn;
	for(i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(chref,i);
		if(cn>=0)
		{	if( IsCharacterPerkOn(GetCharacter(cn),perkName) )	{return true;}
		}
	}
	return false; 
}

void procChrPerkDelay()
{
	string perkName = GetEventData();
	int chrIdx = GetEventData();

	aref arPerk;
	makearef(arPerk,Characters[chrIdx].perks.list.(perkName));
	if( !CheckAttribute(arPerk,"delay") ) return;
	int delay = sti(arPerk.delay);
 	
 	bool ok;
 	ok = (!bAbordageStarted) && (!bSeaReloadStarted);
 	if (ok || perkName == "Rush")
 	{
		delay--;
	}

	if( CheckAttribute(arPerk,"active") )
	{
		int iActive = sti(arPerk.active)-1;
		if( iActive>0 )	{arPerk.active = iActive;}
		else
		{
			CharacterPerkOff(GetCharacter(chrIdx),perkName);
		}
	}

	if( delay<=0 )
	{	DeleteAttribute(&Characters[chrIdx],"perks.list."+perkName+".delay");
		DeleteAttribute(&Characters[chrIdx],"perks.list."+perkName+".active");
		PostEvent("evntPerkAgainUsable",1);
	}
	else
	{
		Characters[chrIdx].perks.list.(perkName).delay = delay;
		PostEvent("evntChrPerkDelay",1000,"sl",perkName,chrIdx);
	}
}

void EnableUsingAbility(ref chref,string perkName)
{
    
    
	int cn;
    if (!CheckCharacterPerk(chref, perkName))
    {

        cn = GetOfficersPerkUsingIdx(chref, perkName);
        if (cn != -1)
        chref = GetCharacter(cn);
    }
    
    
	Event("evntChrPerkDelay","sl",perkName, sti(chref.index));
}

void PerkLoad()
{

	string locName = pchar.location;
	aref arPerksRoot,arPerk;
	int i,j,n,tmpi;

	for(i=0; i<MAX_CHARACTERS; i++)
	{
		if(Characters[i].location == locName)
		{
			makearef(arPerksRoot,Characters[i].perks.list);
			n = GetAttributesNum(arPerksRoot);
			for(j=0; j<n; j++)
			{
				arPerk = GetAttributeN(arPerksRoot,j);
				if( CheckAttribute(arPerk,"delay") )
				{
					tmpi = sti(arPerk.delay);
					if( tmpi>0 )
					{
						PostEvent("evntChrPerkDelay",1000,"sl",GetAttributeName(arPerk),i);
					}
				}
			}
		}
	}


}

void ClearActiveChrPerks(ref chref)
{
	int i,cn;
    ref offc; 
    string  sOfficerType;	
    
    if (bAbordageStarted || bSeaReloadStarted) return; 
	
	ClearActive(chref); 
	if (CheckAttribute(chref, "Fellows.Passengers")) 
	{
		for (i=1; i<=6; i++)
		{
			sOfficerType = GetOfficerTypeByNum(i);
			cn = sti(chref.Fellows.Passengers.(sOfficerType));
			if(cn<0) {continue;}
			offc = &Characters[cn];
			ClearActive(offc);
		}
	}
}

void ClearActive(ref offic)
{
	aref arPerksRoot, arPerk;
	int i,n;
	
	makearef(arPerksRoot, offic.perks.list);
		
	n = GetAttributesNum(arPerksRoot);
	for (i=0; i<n; i++)
	{
		arPerk = GetAttributeN(arPerksRoot,i);

		if (CheckAttribute(arPerk, "delay"))
        {
			DeleteAttribute(arPerk,"delay");
		}
		if (CheckAttribute(arPerk,"active"))
        {
			DeleteAttribute(arPerk,"active");
		}
	}
}

void AcceptWindCatcherPerk(ref refCharacter)
{
    int  nShipType;
    ref  refBaseShip, refRealShip;

	nShipType = GetCharacterShipType(refCharacter);
	if (nShipType==SHIP_NOTUSED) return;

	refRealShip = GetRealShip(nShipType);
	refBaseShip = GetShipByType(sti(refRealShip.BaseType));
		
	if (CheckOfficersPerk(refCharacter, "WindCatcher"))
	{
		refRealShip.InertiaAccelerationX	= stf(refBaseShip.InertiaAccelerationX) + stf(refBaseShip.InertiaAccelerationX) / 10.0;
		refRealShip.InertiaAccelerationY	= stf(refBaseShip.InertiaAccelerationY) + stf(refBaseShip.InertiaAccelerationY) / 10.0;
		refRealShip.InertiaAccelerationZ	= stf(refBaseShip.InertiaAccelerationZ) + stf(refBaseShip.InertiaAccelerationZ) / 10.0;
		
	}
	else
	{   
	    refRealShip.InertiaAccelerationX	= stf(refBaseShip.InertiaAccelerationX);
		refRealShip.InertiaAccelerationY	= stf(refBaseShip.InertiaAccelerationY);
		refRealShip.InertiaAccelerationZ	= stf(refBaseShip.InertiaAccelerationZ);
	}
	if (iArcadeSails == 0) 
	{
	    refRealShip.InertiaAccelerationY = stf(refRealShip.InertiaAccelerationY) / 2.0;
	}
}


void PerkBerserkerReaction()
{
	RemoveItems(pchar, "berserker_potion", 1);
	AddCharacterHealth(pchar, -2);
	log_info("Used Ometochli tincture! Your strength has increased several times!");
	PlaySound("Ambient\Tavern\glotok_001.wav");
	PlaySound("Types\warrior03.wav");
}
