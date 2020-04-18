void Ship_BortFire()
{
	float	dx, dy, dz, d2x, d2y, d2z;
	float	ax = 0.0;
	float 	az = 0.0;
	float   vz = 0.0;
	aref	firedShip;
	string	bortName;
	ref rCharacter = GetCharacter(GetEventData());
	firedShip = GetEventData();
	bortName = GetEventData();
	dx = GetEventData();
	dy = GetEventData();
	dz = GetEventData();
	d2x = GetEventData();
	d2y = GetEventData();
	d2z = GetEventData();
    
    if (bortName == "cannonr" || bortName == "cannonl")
    { 
        rCharacter.BOAL_ReadyCharge = "0";
    }
    
	
	
	
	bool  bTempNotEnoughBalls = false;
	if (sti(rCharacter.index) == GetMainCharacterIndex())
	{
		ballNumber = 0;
        bTempNotEnoughBalls = bNotEnoughBalls;
	}
	bool bOfficer;
	bOfficer = (sti(rCharacter.index) == GetMainCharacterIndex()) || CheckAttribute(rCharacter, "Payment"); 
	if (bDisableMapEnter && bOfficer && !bTempNotEnoughBalls) 
	{
        if (bortName == "cannonr" || bortName == "cannonl")
        {
            AddCharacterExpToSkill(rCharacter, "Cannons", 3);
            ChangeCrewExp(rCharacter, "Cannoners", 0.28);
        }
        else
        {
            AddCharacterExpToSkill(rCharacter, "Cannons", 1);
            ChangeCrewExp(rCharacter, "Cannoners", 0.1);
        }
        
    }
    else
    {
    	if (bortName == "cannonr" || bortName == "cannonl")
        {
            ChangeCrewExp(rCharacter, "Cannoners", 0.08);
        }
        else
        {
            ChangeCrewExp(rCharacter, "Cannoners", 0.03);
        }
    }
    

	SendMessage(&SeaOperator, "lisffffff", MSG_SEA_OPERATOR_FIRE, firedShip, bortName, dx, dy, dz, d2x, d2y, d2z);
 	
}

void Ship_VolleyHeelEnd()
{
	float	ax = 0.0;
	float 	az = 0.0;

	aref aCharacter = GetEventData();
	if(!LAi_IsDead(aCharacter))
	{
		SetHeel_XZ(aCharacter,  &ax, &az);	
		SendMessage(aCharacter, "lff", MSG_SHIP_SET_HEEL_XZ, ax, az); 	
	}	
}

