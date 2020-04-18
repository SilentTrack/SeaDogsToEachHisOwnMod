object Animals;

void CreateAnimals(ref Location)
{
	if (!IsEntity(Animals))
		CreateEntity(&Animals, "Animals");

	float midX, midY, midZ;
	SendMessage(Location, "lseee", MSG_LOCATION_EX_MSG, "GetPatchMiddlePos", &midX, &midY, &midZ);
	Animals.midY = midY;

	aref locator_group;
	aref locator;
	int n;
	int num;
	
	

	SendMessage(Animals, "l", MSG_ANIMALS_BUTTERFLIES_HIDE);
	SendMessage(Animals, "l", MSG_ANIMALS_FISHSCHOOLS_HIDE);
	SendMessage(Animals, "l", MSG_ANIMALS_SEAGULLS_HIDE);

	if (!Whr_IsRain()  )
	{
		if (!Whr_IsNight())
		{
			if (!Whr_IsStorm())
			{
				
				if(CheckAttribute(Location, "locators") && (Location.environment.weather == "true"))
				{
					SendMessage(Animals, "l", MSG_ANIMALS_SEAGULLS_SHOW);
					if(CheckAttribute(Location, "locators.seagull"))
					{
						makearef(locator_group, location.locators.seagull);
						num = GetAttributesNum(locator_group);
						for(n = 0; n < num; n++)
						{
							locator = GetAttributeN(locator_group, n);
							
							SendMessage(Animals, "lfff", MSG_ANIMALS_SEAGULLS_ADD, stf(locator.x), stf(locator.y), stf(locator.z));
						}
					}
				}

				
				if(!CheckAttribute(Location, "type")) Log_SetStringToLog("� ������� ���, ��� ���� id=" + Location.id );
				if (Location.type == "jungle")
				{
					SendMessage(Animals, "l", MSG_ANIMALS_BUTTERFLIES_SHOW);
				}
			}
		}
	}

}

void CreateSeaAnimals()
{
	if (!IsEntity(Animals))
	{
		CreateEntity(&Animals, "Animals");
		LayerAddObject(SEA_EXECUTE, &Animals, 77);
		LayerAddObject(SEA_REALIZE, &Animals, 77);
	}

	Animals.midY = 0.0;

	SendMessage(Animals, "l", MSG_ANIMALS_BUTTERFLIES_HIDE);
	SendMessage(Animals, "l", MSG_ANIMALS_FISHSCHOOLS_SHOW);
	SendMessage(Animals, "l", MSG_ANIMALS_SEAGULLS_HIDE);

	if (!Whr_IsRain())
	{
		if (!Whr_IsNight())
		{
			if (!Whr_IsStorm())
			{
				SendMessage(Animals, "l", MSG_ANIMALS_SEAGULLS_SHOW);
				SendMessage(Animals, "lfff", MSG_ANIMALS_SEAGULLS_ADD, 0.0, 0.0, 0.0);
			}
		}
	}

}

void DeleteAnimals()
{
	if (IsEntity(Animals))
		DeleteClass(Animals);
}


