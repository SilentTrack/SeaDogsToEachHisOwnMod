string arrayNPCModel[64];
int    arrayNPCModelHow; // ��� ������������ ������� � ����� �������

void CreateTraders(aref loc)
{
	if(CheckAttribute(loc, "QuestCapture")) return; // ���� ���� ��������� ���
	if (loc.type == "town" && !LAi_IsCapturedLocation)
	{
		int iColony = -1;
		int iNation = -1;
		int iCitizensQuantity;
		ref chr;
		aref st;
		int iChar, iSex;
		string slai_group, sType, sTraderType;

		for(int n = 0; n < MAX_CHARACTERS; n++)
		{
			makeref(chr, Characters[n]);
			if (CheckAttribute(chr, "CityType") && CheckAttribute(chr, "Merchant.type") && chr.location == loc.id) return; 
		}				

		if(CheckAttribute(loc, "fastreload"))
		{
			iColony = FindColony(loc.fastreload);
		}
		if(iColony == -1)
		{
			return;
		}
	
		iNation = GetCityNation(loc.fastreload);
	
		if(iNation == -1)
		{
			return;
		}
				
		slai_group = GetNationNameByType(iNation)  + "_citizens"; 
		if (checkAttribute(loc, "locators.merchant"))
		{
			makearef(st, loc.locators.merchant);
			iCitizensQuantity = GetAttributesNum(st) / 2;
			for (int i=0; i<iCitizensQuantity; i++)
			{		
				switch (i)
				{
					case 0:
						iSex = 1;
						sType = "citizen";	
						sTraderType = "potion";	
					break;
					case 1:
						iSex = rand(1);
						sType = "citizen";
						sTraderType = "veteran";	
					break;
					case 2:
						iSex = 0;
						sType = "blade_trader";
						sTraderType = "armourer";	
					break;
					case 3:
						iSex = 0;
						sType = "monk";
						sTraderType = "monk";	
					break;
					case 4:
						iSex = 1;
						sType = "gipsy";
						sTraderType = "indian";	
					break
					case 5:
						iSex = rand(1);
						sType = "citizen";
						sTraderType = "veteran";	
					break;
					case 6:
						iSex = 0;
						sType = "blade_trader";
						sTraderType = "armourer";	
					break;
				}
			
				iChar = NPC_GeneratePhantomCharacter(sType, iNation, iSex, 180);

				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				chr.Merchant = true; // ���� "��������"
				chr.Merchant.type = sTraderType; 
				chr.money = TRADER_MIN_MONEY + rand(TRADER_NORM);
				
				LAi_SetLoginTime(chr, 7.0, 20.0);

				ChangeCharacterAddressGroup(chr, loc.id, "merchant", "merchant"+(i+1));
				LAi_SetMerchantType(chr);
				chr.dialog.filename = "Common_ItemTrader.c";
				chr.dialog.currentnode = "first time";
				if (chr.sex == "man") chr.greeting = "item_male";
				else chr.greeting = "item_female";			
	   			if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
			}
		} 
	}	
}

// ������� ������� � ������� + �������, �������-����������� (����� 48�) ����������� boal 13.05.06
void CreateCitizens(aref loc)
{
	bool generateAffairOfHonor = true;
	
	if (loc.type != "town" && loc.type != "church" && loc.type != "residence") return; //��������� ��������� �� ������ ������������ �����
	if(LAi_IsCapturedLocation) // fix ����� �������, ����� ����� ������ ��� ������
	{
		return;
	}
	if(CheckAttribute(loc, "QuestCapture")) return; // ���� ���� ��������� ���
	
	int iColony = -1;
	int iNation = -1;

	if (isLocationHasCitizens(loc.id)) return; // boal  ���� ���� ��� � ���� ����, �� �� �����
	
	if(CheckAttribute(loc, "fastreload"))
	{
		iColony = FindColony(loc.fastreload);
	}
	if(iColony == -1)
	{
		return;
	}
	
	iNation = GetCityNation(loc.fastreload);
	
	if(iNation == -1)
	{
		return;
	}

	int iCitizensQuantity, iModel;
	int iSailorQty, iCapQty, iCitizQty, iNobleQty, iGipsyQty, iContraQty, iIndianQty, iMonkQty, iConvQty;
	ref chr;
	aref st;
	int iChar, i, iSex;
	bool bOk;
	string slai_group, locatorName, sType;
    slai_group = GetNationNameByType(iNation)  + "_citizens"; 

	// ����� -->
	if (loc.type == "town")
	{
		int iPoorIdx = GetCharacterIndex(colonies[iColony].id + "_Poorman");
		if (iPoorIdx != -1)
		{
			if (rand(1)) 
			{
				characters[iPoorIdx].PoorSit = true;
				sType = "locator" + rand(2);
				locatorName = characters[iPoorIdx].forSit.(sType);
			}
			else 
			{ 
				DeleteAttribute(&characters[iPoorIdx], "PoorSit");
				locatorName = characters[iPoorIdx].forStay.locator;
			}
			LAi_SetPoorTypeNoGroup(&characters[iPoorIdx]);
			if (LAi_CheckLocatorFree("goto", locatorName))
				ChangeCharacterAddressGroup(&characters[iPoorIdx], loc.id, "goto", locatorName);
			else
				PlaceCharacter(&characters[iPoorIdx], "patrol", "random_free");

		}
	}
	// ����� <--

    // �������� --> Jason: �������� ��������� ��������� ������� - ��������� �� �����
	iSailorQty = rand(2)+2;
	iContraQty = rand(1)+1;
	iCapQty = rand(1);
	iCitizQty = rand(4)+10;
	iNobleQty = rand(2)+1;
	iGipsyQty = rand(1);
	iMonkQty = rand(1);
	iIndianQty = 0;
	iConvQty = 0;
	iCitizensQuantity = rand(8)+6;
	if (loc.type == "church")
	{//����� ���, ��������� ������ �������� �����������
		iSailorQty = 0;
		iCapQty = 0;
		iNobleQty = 0;
		iContraQty = 0;
		iGipsyQty = 0;
		iMonkQty = 0;
		iIndianQty = 0;
		iConvQty = 0;
	}
	if (loc.id == "Minentown_town")
	{
		iIndianQty = rand(2)+10;
		iContraQty = rand(2)+4;
		iCitizQty = 0;
		iSailorQty = 0;
		iCapQty = rand(2);
		iNobleQty = 0;
		iGipsyQty = 0;
		iMonkQty = 0;
		iConvQty = rand(2)+4;
	}
    arrayNPCModelHow = 0;
	if (checkAttribute(loc, "citizens") || loc.type == "church")
	{
		if(iNation != PIRATE || sti(Colonies[iColony].HeroOwn) == true)//�������
		{
			if (Colonies[iColony].id == "Pirates") return; // ����-������ � �������� �������� � ������ �����
			for(i=0; i<iSailorQty; i++)//�������
			{
                iSex = MAN;
				sType = "sailor";
				iChar = NPC_GeneratePhantomCharacter("sailor", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				GiveItem2Character(chr, RandPhraseSimple("blade_03","blade_05"));
				EquipCharacterbyItem(chr, RandPhraseSimple("blade_03","blade_05"));
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "Population\Sailor.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "town_sailor";
				if (rand(5) == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) //���������� � �������
				{
					chr.quest.crew = "true";
					chr.quest.crew.qty = 5+rand(150);
					chr.quest.crew.type = rand(2);
					chr.quest.crew.money = (1+rand(1))*100+rand(50);
					chr.talker = rand(9);
				}
			}
			for(i=0; i<iGipsyQty; i++)//�������
			{
                iSex = WOMAN;
				sType = "gipsy";
				iChar = NPC_GeneratePhantomCharacter("gipsy", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "Population\Gipsy.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "gipsy";
				chr.talker = 5;
			}
			for(i=0; i<iContraQty; i++)//�������� � ������ ������ ��������
			{
                iSex = MAN;
				sType = "marginal";
				iChar = NPC_GeneratePhantomCharacter("marginal", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				GiveItem2Character(chr, RandPhraseSimple("blade_04","blade_06"));
				EquipCharacterbyItem(chr, RandPhraseSimple("blade_04","blade_06"));
				if (rand(7) < 2 && !CheckAttribute(pchar, "GenQuest.Marginpassenger") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && chr.City != "Minentown" && chr.City != "Panama") //������ ���������
				{
					chr.quest.passenger = "true";
					chr.talker = rand(3);
				}
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "Population\Marginal.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "marginal";
			}
			for(i=0; i<iCapQty; i++)//�������� ��������
			{
				iSex = MAN;
				sType = "captain";
				iChar = NPC_GeneratePhantomCharacter("captain", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				GiveItem2Character(chr, RandPhraseSimple("blade_10","blade_13"));
				EquipCharacterbyItem(chr, RandPhraseSimple("blade_10","blade_13"));
				if (rand(3) < 1 && !CheckAttribute(pchar, "GenQuest.MarchCap") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && chr.City != "Panama") //������ �� ������ patch-5
				{
					chr.quest.march = "true";
					chr.talker = rand(1);
				}
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "Population\Captain.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "captain";
			}
			for(i=0; i<iCitizQty; i++)//������-������� + ���������� ������
			{
				if (loc.type == "church") iSex = MAN;
				else iSex = rand(WOMAN);
				sType = "citizen";
				iChar = NPC_GeneratePhantomCharacter("citizen", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				if (loc.type == "church" && chr.sex == "man")
				{
				    LAi_SetSitType(chr);
					PlaceCharacter(chr, "sit", "random_free");
					chr.dialog.filename = "Enc_Walker.c";
					chr.greeting = "citizen_male";
					chr.nonTable = true;
				}
				else
				{
					LAi_SetCitizenType(chr);
					PlaceCharacter(chr, "goto", "random_free");
				}
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				chr.dialog.currentnode = "first time";
				if(chr.sex == "man")
				{
					chr.dialog.filename = "Population\Townman.c";
					chr.greeting = "citizen_male";
					if (rand(6) > 4 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && loc.type != "church" && chr.City != "Panama") //������������ ��������� patch-5
					{
						chr.quest.passenger = "true";
						chr.talker = rand(3);
					}
				}
				else
				{
					chr.dialog.filename = "Population\Towngirl.c";
					chr.greeting = "citizen_female";
				}
				// Warship, 25.05.11. "���� �����" -->
				bool bAh = (drand(11) == 5) && (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) && (!CheckAttribute(pchar, "GenQuest.Escort.Trader"))
				if(bAh || bBettaTestMode)
				{
					if(generateAffairOfHonor)
					{
						if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.FinishCount")) PChar.QuestTemp.AffairOfHonor.FinishCount = 0;
						//pchar.questTemp.AffairOfHonor.LighthouseId = Island_GetLighthouseId(loc.islandId);
						pchar.questTemp.AffairOfHonor.LighthouseId = Colony_GetLighthouseId(loc.fastreload);
						
						if(loc.type == "town" && chr.City != "PortRoyal" && chr.City != "FortOrange" && PChar.QuestTemp.AffairOfHonor.LighthouseId != "" && AffairOfHonor_GetCurQuest() == "")
						{
							if(sti(PChar.QuestTemp.AffairOfHonor.FinishCount) < 8 && !CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor") && GetCharacterIndex("AffairOfHonor_QuestMan") == -1)
							{
								if(chr.sex == "man" || !CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Cavalier"))
								{
									// Jason: ������� ��� �� ����� - ������ ����������
									int Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
									int Scl = 30+2*sti(pchar.rank);
									chr.id = "AffairOfHonor_QuestMan";
									chr.rank = Rank;
				if(chr.sex == "man")
				{
										FantomMakeCoolFighter(chr, Rank, Scl, Scl, RandPhraseSimple("blade_08","blade_09"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
										float Mft = MOD_SKILL_ENEMY_RATE/20;
										chr.MultiFighter = 1.0+Mft; // ������������
									}
									chr.dialog.filename = "Quest\ForAll_dialog.c";
									chr.dialog.currentnode = "AffairOfHonor_1";
									chr.talker = rand(3);
									LAi_SetImmortal(chr, true);
									generateAffairOfHonor = false; // ����� �� ������ ��� �� �������� �������������.
									Log_TestInfo("����������� ���� �����");
								}
							}
						}
					}
				}
				// <--
			}
			for(i=0; i<iNobleQty; i++)//�������
			{
				iSex = rand(WOMAN);
				sType = "noble";
				iChar = NPC_GeneratePhantomCharacter("noble", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				if(chr.sex == "man")
				{
					chr.dialog.filename = "Population\Nobleman.c";
					chr.greeting = "noble_male";
					GiveItem2Character(chr, RandPhraseSimple("blade_15","blade_16"));
					EquipCharacterbyItem(chr, RandPhraseSimple("blade_15","blade_16"));
					if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
					{
						if (rand(11) > 9 && GetCharacterIndex("QuestCitiz_" + loc.fastreload) == -1  && !CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
						{//��������� ���������
							chr.id = "QuestCitiz_" + loc.fastreload;
							chr.dialog.filename = "Quest\ForAll_dialog.c";
							chr.dialog.currentnode = "SCQ_Nobleman";
							chr.talker = rand(3); //������ ������
							chr.quest.SeekCap.numQuest = rand(1); //����� ����� ����� ������
						}
						if (rand(11) < 2  && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && chr.City != "Panama") //������������ ��������� patch-5
						{
							chr.quest.passenger = "true";
							chr.talker = rand(3);
						}
						if (rand(11) == 3) chr.quest.donation = "true"; //������� ������
						if (rand(11) == 5) chr.quest.lombard = "true"; //�������� ��������
						if (rand(11) == 7) chr.quest.slaves = "true"; //�������� �����
					}
				}
				else
				{
					chr.dialog.filename = "Population\Noblegirl.c";
					chr.greeting = "noble_female";
				}
			}
			for(i=0; i<iIndianQty; i++)//�������
			{
                if (i < 9) iSex = MAN;
				else iSex = WOMAN;
				sType = "indian";
				iChar = NPC_GeneratePhantomCharacter("indian", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				if(chr.sex == "man")
				{
					chr.name = GetIndianName(MAN);
					chr.lastname = "";
					GiveItem2Character(chr, "slave_02");
					EquipCharacterbyItem(chr, "slave_02");
					chr.greeting = "indian_male";
				}
				else
				{
					chr.name = GetIndianName(WOMAN);
					chr.lastname = "";
					RemoveAllCharacterItems(chr, true);
					//chr.greeting = "Gr_Woman_Citizen";
				}
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "Population\Indian.c";
				chr.dialog.currentnode = "first time";
			}
			for(i=0; i<iConvQty; i++)//���������� �� �������
			{
                iSex = MAN;
				sType = "convict";
				iChar = NPC_GeneratePhantomCharacter("convict", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				GiveItem2Character(chr, "slave_02");
				EquipCharacterbyItem(chr, "slave_02");
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "Population\Convict.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "convict";
			}
			for(i=0; i<iMonkQty; i++)//������
			{
                iSex = MAN;
				sType = "monk";
				iChar = NPC_GeneratePhantomCharacter("monk", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
				{
					if (rand(4) == 1) //�������� �������������
				{
					chr.quest.donation = "true";
					chr.talker = rand(3);
				}
					if (rand(4) == 0 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && chr.City != "Panama") //������������ ��������� patch-5
				{
					chr.quest.passenger = "true";
					chr.talker = rand(3);
				}
					if (rand(4) == 4 && !CheckAttribute(pchar, "questTemp.ShipCapellan") && 5-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0) //����������� ��������
				{
					chr.quest.capellan = "true";
					chr.talker = 9;
				}
				}
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "Population\Monk.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "monk";
			}
		}
		else
		{
			for(i=0; i<iCitizensQuantity; i++)//��������� ���������
			{
				iSex = MAN;
				sType = "pirate";
				iChar = NPC_GeneratePhantomCharacter("pirate", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetWarriorType(chr);
				LAi_warrior_DialogEnable(chr, true);
				chr.watchBoxes = true;
				LAi_group_MoveCharacter(chr, slai_group);
				chr.dialog.filename    = "Population\Townman.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "town_pirate";
				PlaceCharacter(chr, "goto", "random_free");
			}
		}
	}
	// �������� <--    
	
	// ������� -->
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
	{
		aref solderLoc;
		makearef(st, loc.locators.soldiers);
		iCitizensQuantity = GetAttributesNum(st);		
		for (i=0; i<iCitizensQuantity; i++)
		{
			if(iNation != PIRATE)
			{
                sType = "soldier";
				iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
			}
			else
			{
                sType = "pirate";
				iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 2);
			}
			chr = &characters[iChar];
			SetNPCModelUniq(chr, sType, MAN);
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
			chr.RebirthPhantom = true; 
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //������ ��� �� ���������� ����� �������� �� ������������
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // ������ ����
			LAi_SetLoginTime(chr, 6.0, 23.0); //� ����� ����� ������� �� ������� :)

			//locatorName = PlaceCharacter(chr, "soldiers", "random_free"); // ���� ��������� ���� ��-�� ������ �������
			solderLoc = GetAttributeN(st, i);
			locatorName = GetAttributeName(solderLoc);
			ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", locatorName);
			// eddy. ���������, ������ �� ������ ���� ����������� -->
			if (findsubstr(locatorName, "protector" , 0) != -1 && iNation != PIRATE) 
			{
				chr.protector = true;
				chr.greeting = "protector";
			}
			else chr.greeting = "soldier";
			// <-- eddy. ���������, ������ �� ������ ���� �����������
			
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";
			
			LAi_SetGuardianType(chr);

            if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "town_pirate";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
		}
	}
	// ������� <--
	// ������� -->
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
	{
		makearef(st, loc.locators.patrol);
		iCitizensQuantity = GetAttributesNum(st);
		if(iCitizensQuantity > 10)
		{
			iCitizensQuantity = 10;
		}
		for (i=0; i<iCitizensQuantity-3; i++)
		{
			if(iNation != PIRATE && LAi_IsCapturedLocation == 0)
			{
                sType = "soldier";
				iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
			}
			else
			{
                sType = "pirate";
				iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 2);
			}
			chr = &characters[iChar];
			SetNPCModelUniq(chr, sType, MAN);
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // ������ ����
			chr.RebirthPhantom = true; 
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //������ ��� �� ���������� ����� �������� �� ������������
			LAi_SetLoginTime(chr, 0.0, 24.0);
			
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";

			LAi_SetPatrolType(chr);
			
            if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "town_pirate";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
				chr.greeting = "soldier";
			}
			PlaceCharacter(chr, "patrol", "random_free");
		}
		//���������
		for (i=1; i<=3; i++)
		{
			if(iNation == PIRATE)
			{
                sType = "mush_ctz_" + (rand(2)+7);
			}
			else
			{
                sType = "mush_" + NationShortName(iNation) + "_" + i;
			}
			chr = GetCharacter(NPC_GenerateCharacter("GenChar_", sType, "man", "mushketer", sti(pchar.rank), iNation, 2, false, "soldier"));
			chr.id = "GenChar_" + chr.index;	
			chr.reputation = (1 + rand(44) + rand(44));// ���� ���� ���������
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
			chr.greeting = "soldier";
			chr.RebirthPhantom = true; 
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //������ ��� �� ���������� ����� �������� �� ������������
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // ������ ����
			LAi_SetLoginTime(chr, 0.0, 24.0); //� ����� ����� ������� �� ������� :)

			PlaceCharacter(chr, "patrol", "random_free");

			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";				

			LAi_SetPatrolType(chr);
			
            if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "town_pirate";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
		}
	}
	// ������� <--
	// �������� -->
	if (loc.type == "town" && CheckAttribute(loc, "carrier") && IsLoginTime())
	{
		int iTemp;
		int iQtyCarrier = rand(2) + 2;
		string locReload[7];
		locReload[0] = "reload4_back";
		locReload[1] = "reload5_back";
		locReload[2] = "reload6_back";
		locReload[3] = "reload7_back";
		locReload[4] = "reload8_back";
		locReload[5] = "reload10_back";
		locReload[6] = "reload9_back";
		string CarrierName[10];
		CarrierName[0] = "GenresBag1";
		CarrierName[1] = "GenresBag2";
		CarrierName[2] = "GenresBarrel1";
		CarrierName[3] = "GenresBarrel2";
		CarrierName[4] = "GenresBarrelTop1";
		CarrierName[5] = "GenresBarrelTop2";
		CarrierName[6] = "GenresBottle1";
		CarrierName[7] = "GenresBottle2";
		CarrierName[8] = "GenresChest1";
		CarrierName[9] = "GenresChest2";
		for (i=iQtyCarrier; i>0; i--)
		{
			//������� ���������� ��� ���� ������� ��������
			iSex = 1;
			while (iSex == 1)
			{
				iTemp = rand(9);
				if (CarrierName[iTemp] != "") iSex = 0;
			}
			chr = GetCharacter(NPC_GenerateCharacter("Carrier", CarrierName[iTemp], "man", "genres", 35, iNation, 2, false, "citizen"));
			chr.id = chr.id + "_" + chr.index;
			aref aLocator;
			makearef(aLocator, loc.locators.reload);
			CarrierName[iTemp] = ""; //��� �������� ������ �� ������
			LAi_SetImmortal(chr, true);
			LAi_SetLoginTime(chr, 7.0, 20.0);
			iSex = 1;
			while (iSex == 1)
			{
				iTemp = rand(6);
				if (CheckAttribute(aLocator, locReload[iTemp]) && locReload[iTemp] != "")
				{
					chr.firstLoc = locReload[iTemp];
					chr.firstLoc.timer = frand(7) + 4.0;
					locReload[iTemp] = "";
					iSex = 0;
				}
			}
			ChangeCharacterAddressGroup(chr, loc.id, "reload", "gate");
			LAi_SetCarrierType(chr);
			LAi_group_MoveCharacter(chr, slai_group);
		}
	}
	// �������� <--
}

void CreateIslatesoroEng(aref loc)//Jason, ���� ������ ��� ������� ����
{
	if (loc.id == "Pirates_town" && CheckAttribute(loc, "EngBase"))
	{
		int iNation = -1;
		iNation = GetCityNation(loc.fastreload);
		if(iNation == -1) return;
		if(iNation != ENGLAND) return;
		int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
		// ���������� -->
		for (i=1; i<=4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Eng_IT_Prot_"+i, "sold_eng_"+(rand(5)+1), "man", "man", iRank, ENGLAND, 1, false, "soldier"));
			SetFantomParamFromRank(sld, iRank, true);
			sld.dialog.Filename = "Common_Soldier.c";
			sld.dialog.currentnode = "first time";
			sld.greeting = "soldier"; 
			sld.RebirthPhantom = true; 
			LAi_CharacterReincarnation(sld, true, true);
			LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
			ChangeCharacterAddressGroup(sld, "Pirates_town", "soldiers", "soldier"+i);
			LAi_SetLoginTime(sld, 6.0, 23.0);
			if (i < 3) 
			{
				sld.protector = true;
				sld.protector.CheckAlways = true; //��������� ������
				sld.greeting = "protector"; 
			}
			LAi_SetGuardianType(sld);
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
		}
		// ����������
		for (i=1; i<=10; i++)
		{
			if (i < 8)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Eng_IT_Sold_"+i, "sold_eng_"+(rand(5)+1), "man", "man", iRank, ENGLAND, 1, false, "soldier"));
				SetFantomParamFromRank(sld, iRank, true);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Eng_IT_Sold_"+i, "mush_eng_"+(rand(4)+1), "man", "mushketer", iRank, ENGLAND, 1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, 70, 70, "", "mushket1", "bullet", 100);
			}
			sld.dialog.Filename = "Common_Soldier.c";
			sld.dialog.currentnode = "first time";
			sld.greeting = "soldier"; 
			sld.RebirthPhantom = true; 
			LAi_CharacterReincarnation(sld, true, true);
			LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
			LAi_CharacterReincarnation(sld, true, true);
			LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
			ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto"+i);
			LAi_SetLoginTime(sld, 0.0, 24.0);
			sld.city = "Pirates";
			sld.citytype = "soldier";
			LAi_SetPatrolType(sld);
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
		}
	}
}

// ������ ������������ � �������, ���� �������-������������ (24�) ����������� boal 13.05.06
void CreateHabitues(aref loc)
{
	int iColony = -1;
	int iNation = -1;
	
	bool generateAffairOfHonor = true;
	
	if (!checkAttribute(loc, "habitues")) return;
	if(LAi_IsCapturedLocation) return;
	if (CheckAttribute(pchar, "questTemp.Mtraxx.InTavern") && loc.id == "LaVega_tavern") return; // Addon 2016-1 Jason ��������� �������
	
	OfficersReactionResult(); // ���� ���� � ������, ��� ���� ����� � �� ��� - ���� ��� �������

	if (!isLocationHasCitizens(loc.id))  // boal  ���� ���� ��� � ���� ����, �� �� �����
	{
		if (CheckAttribute(loc, "fastreload"))
		{
			iColony = FindColony(loc.fastreload);

			if(iColony == -1)
			{
				return;
			}

			iNation = GetCityNation(loc.fastreload);

			if (iNation == -1)
			{
				return;
			}

			string sColony = loc.fastreload;
			int iCitizensQuantity, iModel;
			ref chr;
		    string slai_group;
			int iChar;
			int i, n, k;
			string sTemp;

			slai_group = GetNationNameByType(iNation)  + "_citizens";

            arrayNPCModelHow = 0;
			if (pchar.location == "Minentown_tavern")
			{
				for (i=1; i <=rand(2)+1; i++)
			{
                if (CheckFreeLocator(loc.id, "sit_base" + i, -1))
				{
					iChar = NPC_GeneratePhantomCharacter("spa_soldier", iNation, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, "spa_soldier", MAN);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					ChangeCharacterAddressGroup(chr, loc.id, "sit", "sit_base" + i);
					chr.Default           = loc.id;
					chr.Default.group     = "sit";
					chr.Default.ToLocator = "sit_front" + i;
					LAi_SetLoginTime(chr, 0.0, 24.0);
					LAi_SetSitType(chr);
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
					chr.quest.last_theme = 0;
					chr.dialog.filename = "Habitue_dialog.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "habitue";
				}
			}
				for (i=0; i<=rand(2); i++)
				{
				    iChar = NPC_GeneratePhantomCharacter("spa_soldier", iNation, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, "spa_soldier", MAN);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					sTemp = PlaceCharacter(chr, "sit", "random_free"); // ����� �� ���� �����, ���� ��� ����� ������
                    ReSitCharacterOnFree(chr, loc.id, sTemp);

					LAi_SetLoginTime(chr, 0.0 + rand(6), 24.0 - rand(10));
					LAi_SetSitType(chr);
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
					chr.quest.last_theme = 0;
					chr.dialog.filename = "Habitue_dialog.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "habitue";
				}
				return;
			}
			 //Jason --> ��������� ���� - 33%, ������� ���� ����� ��� ������� � ������
			if (rand(11) < 4 && loc.id != "Panama_tavern" && !CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{ // 170712
				i = rand(3)+1;
				if (CheckFreeLocator(loc.id, "sit_base"+i, -1))
				{
					iChar = NPC_GeneratePhantomCharacter("trader", iNation, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, "trader", MAN);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					ChangeCharacterAddressGroup(chr, loc.id, "sit", "sit_base"+i);
					chr.Default           = loc.id;
					chr.Default.group     = "sit";
					chr.Default.ToLocator = "sit_front"+i;
					LAi_SetSitType(chr);
					LAi_group_MoveCharacter(chr, slai_group);
					chr.dialog.filename = "Quest\QuestTrader_dialog.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "captain_trader";
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
				}
			}
			//<-- ��������� ����
			// ������ �����, �� �������� ����� ��� ��
			for (i = 1; i <=4; i++)
			{
                if (CheckFreeLocator(loc.id, "sit_base" + i, -1))
				{
					string sType = RandPhraseSimple("citizen","sailor");
					if (Colonies[iColony].nation == PIRATE) sType = RandPhraseSimple("pirate","sailor");
					iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, sType, MAN);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					ChangeCharacterAddressGroup(chr, loc.id, "sit", "sit_base" + i);
					chr.Default           = loc.id;
					chr.Default.group     = "sit";
					chr.Default.ToLocator = "sit_front" + i;
					LAi_SetLoginTime(chr, 0.0, 24.0);
					LAi_SetSitType(chr);
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
					chr.quest.last_theme = rand(1);
					chr.quest.last_theme_game = rand(1);
					chr.dialog.filename = "Habitue_dialog.c";
					chr.dialog.currentnode = "first time";
					if (chr.quest.last_theme == 0) chr.greeting = "habitue"; // �������
					else chr.greeting = "player"; // �����
					
					// Warship, 30.05.11. "���� �����" -->
					bool bAh = (drand(11) == 5) && (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) && (!CheckAttribute(pchar, "GenQuest.Escort.Trader"))
					if(bAh || bBettaTestMode)
					{
						if(generateAffairOfHonor && IsDay())
						{
							pchar.questTemp.AffairOfHonor.LighthouseId = Colony_GetLighthouseId(loc.fastreload);
							
							if(chr.City != "PortRoyal" && chr.City != "FortOrange" && PChar.QuestTemp.AffairOfHonor.LighthouseId != "" && AffairOfHonor_GetCurQuest() == "")
							{
								if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor") && GetCharacterIndex("AffairOfHonor_QuestMan") == -1)
								{
									chr.id = "AffairOfHonor_QuestMan";
									chr.dialog.filename = "Quest\ForAll_dialog.c";
									chr.dialog.currentnode = "AffairOfHonor_1";
									LAi_SetImmortal(chr, true);
									SetRandNationSoldierModel(chr);
									Characters_RefreshModel(chr); // Jason: ��������� ������ �����������
									generateAffairOfHonor = false; // ����� �� ������ ��� �� �������� �������������.
									Log_TestInfo("����������� ���� �����");
								}
							}
						}
					}
					// <--
				}
			}
			iChar = GetCharacterIndex(Colonies[iColony].id + "_Smuggler");
			if (iChar != -1) // � ������� ��� ������ - ��� �������
			{
		        chr = &characters[iChar];
				if (sti(Colonies[iColony].HeroOwn) != true)
				{ // ������ ���������� ������, �� ������, �� ������� � ������� ������ ���
		            chr.City = Colonies[iColony].id;  // ��� ����� ��������� � �������, �� ��� ������ �� 20 ������� ������.
		            chr.nation = iNation; // ����� ��� �����, �� ��� ����� ������ ������� �� ������, �� �� �����
					CreateModel(iChar, "pirate", MAN);
					sTemp = PlaceCharacter(chr, "sit", "random_free");
					ReSitCharacterOnFree(chr, loc.id, sTemp);
					LAi_group_MoveCharacter(chr, slai_group);
				}
				else
				{
				    ChangeCharacterAddressGroup(chr, "none", "none", "none");
				}
				// ��� ������
			}
			// ������� -->
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))//�� ���� ����� ������ �����
			{
				iCitizensQuantity = rand(8)-6;
				for (i = 0; i <iCitizensQuantity; i++)
				{
					iChar = NPC_GeneratePhantomCharacter("pofficer", iNation, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, "pofficer", MAN);
					SetOfficerParam(chr, rand(4));
					sTemp = PlaceCharacter(chr, "sit", "random_free");
					ReSitCharacterOnFree(chr, loc.id, sTemp);

					LAi_SetSitType(chr);
					// ��� ������
					chr.dialog.filename = "Enc_Officer_dialog.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "officer_hire";
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
				}
			}
			// ������� <--
			if (rand(15) == 3 || TestRansackCaptain) // ugeen --> �������� ����������� ��������� �������� �������� � ������ �� 1/20
			{ // ����� ������
                iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 1);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, "pirate", MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				sTemp = PlaceCharacter(chr, "sit", "random_free"); // ����� �� ���� �����, ���� ��� ����� ������
				ReSitCharacterOnFree(chr, loc.id, sTemp);

				LAi_SetSitType(chr);
				LAi_group_MoveCharacter(chr, slai_group);
				chr.dialog.filename = "Enc_Treasure_dialog.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "map_trader";
				
		        if (GetCharacterItem(pchar, "map_full") == 0) // ��� ����� - �������, ���� �����
		        {
		            aref item;
		            Items_FindItem("map_full", &item);
					FillMapForTreasure(item);
					//pchar.GenQuest.TreasureMoney = 5000 + rand(30)*500 + rand(30)*500;
					pchar.GenQuest.TreasureMoney = 100 + rand(50)*5; // Addon-2016 Jason
		        }
          		if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
			}
			else
			{
				iCitizensQuantity = rand(3) - 1 ; // ������� ����� ��� ��������
				for (i = 0; i <iCitizensQuantity; i++)
				{
				    iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, sType, MAN);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					sTemp = PlaceCharacter(chr, "sit", "random_free"); // ����� �� ���� �����, ���� ��� ����� ������
                    ReSitCharacterOnFree(chr, loc.id, sTemp);

					LAi_SetLoginTime(chr, 0.0 + rand(6), 24.0 - rand(10));
					LAi_SetSitType(chr);
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
					chr.quest.last_theme = 0;
					chr.dialog.filename = "Habitue_dialog.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "habitue";
				}
			}
		}
	}
	//PGG_TavernCheckIsPGGHere(); //Jason: ����� ��� �����������
	if (CheckAttribute(pchar, "GenQuest.Ole")) LSC_CheckOlePearl(); // ��� ������� ��������� ���������
}

void CreateMaltains(aref loc)//Jason, ���������� ���� ���������� � ���-�����
{	
	if (GetCityNation("FortFrance") != FRANCE) return; 
	if(CheckAttribute(loc, "QuestCapture")) return; // ���� ���� ��������� ���
	
	if (CheckAttribute(loc, "Maltains"))
	{
		ref sld;
		int i;
		if (!CheckAttribute(loc, "Maltains_date") || GetNpcQuestPastDayParam(loc, "Maltains_date") >= 2)
		{
			SaveCurrentNpcQuestDateParam(loc, "Maltains_date");
			//������
			sld = GetCharacter(NPC_GenerateCharacter("Maltie_officer", "off_Malt_1", "man", "man", 35, FRANCE, 2, false, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 100, 100, "blade_07", "pistol5", "bullet", 150);//�������
			sld.greeting = "patrol";
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Maltie_officer";
			ChangeCharacterAddressGroup(sld, "Fortfrance_dungeon", "sit", "sit1");
			LAi_SetHuberType(sld);
			sld.standUp = true;
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			//����������
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaltainsPro_"+i, "sold_fra_"+(i+8), "man", "man", 25, FRANCE, 2, false, "soldier"));
				FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 90, 90, "blade_08", "pistol6", "bullet", 100);//�������
				sld.greeting = "protector";
				sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
				sld.dialog.currentnode = "Maltie_soldier";
				ChangeCharacterAddressGroup(sld, "Fortfrance_dungeon", "soldiers", "soldier"+i);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			}
			//������� ������, 3 ��
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaltainsSit_"+i, "sold_fra_"+(rand(7)+9), "man", "man", 20, FRANCE, 2, false, "soldier"));
				FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 70, 70, "blade_08", "pistol7", "bullet", 100);//�������
				sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
				sld.dialog.currentnode = "Maltie_soldier";	
				sld.greeting = "soldier";
				LAi_LoginInCaptureTown(sld, true);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetSitType(sld);
				sld.standUp = true;
				PlaceCharacter(sld, "sit", "random_free");
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			}
			//������� ������, 4 ��
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaltainsStay_"+i, "sold_fra_"+(rand(7)+9), "man", "man", 20, FRANCE, 2, false, "soldier"));
				FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 70, 70, "blade_08", "pistol7", "bullet", 100);//�������
				sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
				sld.dialog.currentnode = "Maltie_soldier";	
				sld.greeting = "soldier";
				LAi_LoginInCaptureTown(sld, true);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetGuardianType(sld);
				PlaceCharacter(sld, "soldiers", "random_free");
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			}
			//�������� ������, 4 ��
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaltainsGo_"+i, "sold_fra_"+(rand(7)+9), "man", "man", 20, FRANCE, 2, false, "soldier"));
				FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 70, 70, "blade_08", "pistol7", "bullet", 100);//�������
				sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
				sld.dialog.currentnode = "Maltie_soldier";	
				sld.greeting = "soldier";
				LAi_LoginInCaptureTown(sld, true);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetPatrolType(sld);
				sld.city = "FortFrance";
				sld.citytype = "soldier";
				PlaceCharacter(sld, "goto", "random_free");
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			}
		}
		//�����������
		if (!CheckAttribute(loc, "Maltaprisoner_date") || GetNpcQuestPastDayParam(loc, "Maltaprisoner_date") > 15)
		{
			SaveCurrentNpcQuestDateParam(loc, "Maltaprisoner_date");
			for (i=2; i<=(rand(2)+2); i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaltainsPrisoner_"+i, "mercen_"+(rand(29)+1), "man", "man", 10, FRANCE, 15, false, "slave"));
				RemoveAllCharacterItems(sld, true);
				LAi_CharacterDisableDialog(sld);
				LAi_LoginInCaptureTown(sld, true);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				if (rand(1) == 0) LAi_SetStayType(sld);
				else LAi_SetGroundSitType(sld);
				ChangeCharacterAddressGroup(sld, "Fortfrance_dungeon", "quest", "quest"+i);
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			}
		}
	}
}

void CreateHWICOffice(aref loc)//Jason, ���������� ����� ����
{	
	if (GetCityNation("Villemstad") != HOLLAND) return; 
	
	if (CheckAttribute(loc, "HWIC"))
	{
		ref sld;
		int i;
		if (!CheckAttribute(loc, "HWIC_date") || GetNpcQuestPastDayParam(loc, "HWIC_date") >= 30)
		{
			SaveCurrentNpcQuestDateParam(loc, "HWIC_date");
			//�������, 6 ��
			for (i=1; i<=6; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("HWIC_sold_"+i, "sold_hol_"+(i+9), "man", "man", 25, HOLLAND, 30, false, "soldier"));
				FantomMakeCoolFighter(sld, 35, 90, 90, "blade_08", "pistol1", "bullet", 100);
				sld.Dialog.Filename = "Quest\HollandGambit\HWIC_Office.c";
				sld.dialog.currentnode = "HWIC_soldier";
				sld.greeting = "protector";
				ChangeCharacterAddressGroup(sld, "Villemstad_houseS3", "soldiers", "soldier"+i);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			}
			//������, 2 ��
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("HWIC_clerk_"+i, "citiz_"+(rand(9)+11), "man", "man", 10, HOLLAND, 30, false, "citizen"));
				SetFantomParamFromRank(sld, 10, true);
				sld.Dialog.Filename = "Quest\HollandGambit\HWIC_Office.c";
				sld.dialog.currentnode = "HWIC_clerk";
				sld.greeting = "official";
				RemoveAllCharacterItems(sld, true);
				LAi_SetLoginTime(sld, 6.0, 21.99);
				LAi_SetHuberType(sld);
				ChangeCharacterAddressGroup(sld, "Villemstad_houseS3", "sit", "sit"+i);
				LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			}
		}
		// ������� �����, ������
		sld = GetCharacter(NPC_GenerateCharacter("HWIC_headclerk", "citiz_9", "man", "man", 20, HOLLAND, -1, false, "citizen"));
		SetFantomParamFromRank(sld, 20, true);
		sld.name = "Corice";
		sld.lastname = "Gerrits";
		sld.Dialog.Filename = "Quest\HollandGambit\HWIC_Office.c";
		sld.dialog.currentnode = "HWIC_headclerk";
		sld.greeting = "official";
		LAi_SetLoginTime(sld, 6.0, 21.99);
		RemoveAllCharacterItems(sld, true);
		sld.standUp = true; //�������� � �������� �� �����
		LAi_SetImmortal(sld, true);
		LAi_SetHuberType(sld);
		ChangeCharacterAddressGroup(sld, "Villemstad_houseS3", "sit", "sit3");
		LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		// 230912 �������
		sld.Merchant = true;
		sld.Merchant.type = "company";
		sld.money = TRADER_MIN_MONEY;
	}
}

// ������������� �������� ���������� � LSC - �������-����������
void CreateLSCGuardClan(aref loc)
{	
	if (loc.id == "LostShipsCity_town")
	{
		ref sld;
		string LocatorGroup, LocatorName;
		int i;
		int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15;
		int iScl = 30 + 3*sti(pchar.rank);
		
		int imush = 17; // ����� ����� ����������
		int isold = 15; // ����� ����� ������
		int iprot = 10; // ����� ����� �����������
		if (CheckNPCQuestDate(loc, "LSCGuard_date"))
		{
			SetNPCQuestDate(loc, "LSCGuard_date");
			LocatorGroup = "soldiers";
			// ������ ����������
			for (i=1; i<=imush; i++)
			{
				LocatorGroup = "soldiers";
				LocatorName = "mushketer"+i;	
				if (i <= 7) // ������� 7 ��
				{
					sld = GetCharacter(NPC_GenerateCharacter("NarvalMush_"+i, "mush_ctz_"+(rand(2)+10), "man", "mushketer", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket2", "cartridge", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c"; // 170912
					sld.dialog.currentnode = "Narval_soldier";	
					sld.greeting = "Narval";
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_NarvalConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetGuardianType(sld);
					sld.MusketerDistance = 0;
					LAi_group_MoveCharacter(sld, "LSC_NARVAL");
					sld.LSC_clan = true;
				}
				if (i >= 8 && i <= 14) // ������� 7 ��
				{
					sld = GetCharacter(NPC_GenerateCharacter("RivadosMush_"+i, "mush_rvd_"+(rand(2)+1), "man", "mushketer", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c";
					sld.dialog.currentnode = "Rivados_soldier";	
					sld.greeting = "Rivados"; 
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_RivadosConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetGuardianType(sld);
					sld.MusketerDistance = 0;
					LAi_group_MoveCharacter(sld, "LSC_RIVADOS");
					sld.LSC_clan = true;
				}
				if (i >= 15) // ������ �����
				{
					sld = GetCharacter(NPC_GenerateCharacter("SharkMush_"+i, "mush_ctz_"+(rand(2)+7), "man", "mushketer", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c";
					sld.dialog.currentnode = "Shark_soldier";	
					sld.greeting = "SharkPirate"; 
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_SharkConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetGuardianType(sld);
					sld.MusketerDistance = 0;
					LAi_group_MoveCharacter(sld, "LSC_SHARK");
					sld.LSC_clan = true;
				}
			}
			// ������ ������
			for (i=1; i<=isold; i++)
			{
				LocatorGroup = "soldiers";
				LocatorName = "soldier"+i;	
				if (i <= 6) // �������
				{
					sld = GetCharacter(NPC_GenerateCharacter("NarvalSold_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_15","blade_16","blade_13"), RandPhraseSimple("pistol6","pistol4"), "bullet", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c";
					sld.dialog.currentnode = "Narval_soldier";	
					sld.greeting = "Narval"; 
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_NarvalConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetGuardianType(sld);
					LAi_group_MoveCharacter(sld, "LSC_NARVAL");
					sld.LSC_clan = true;
				}
				if (i >= 7 && i <= 12) // �������
				{
					sld = GetCharacter(NPC_GenerateCharacter("RivadosSold_"+i, "rivados_"+(rand(6)+1), "man", "man", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_08","blade_04","blade_06"), RandPhraseSimple("pistol6","pistol5"), "bullet", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c";
					sld.dialog.currentnode = "Rivados_soldier";	
					sld.greeting = "Rivados"; 
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_RivadosConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetGuardianType(sld);
					LAi_group_MoveCharacter(sld, "LSC_RIVADOS");
					sld.LSC_clan = true;
				}
				if (i >= 13) // ������ �����
				{
					sld = GetCharacter(NPC_GenerateCharacter("SharkSold_"+i, "citiz_"+(rand(9)+41), "man", "man", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_15","blade_10","blade_13"), RandPhraseSimple("pistol6","pistol5"), "bullet", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c";
					sld.dialog.currentnode = "Shark_soldier";	
					sld.greeting = "SharkPirate"; 
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_SharkConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetGuardianType(sld);
					LAi_group_MoveCharacter(sld, "LSC_SHARK");
					sld.LSC_clan = true;
				}
			}
			// ������ �����������
			for (i=1; i<=iprot; i++)
			{
				LocatorGroup = "soldiers";
				LocatorName = "protector"+i;	
				if (i <= 3) // �������
				{
					sld = GetCharacter(NPC_GenerateCharacter("NarvalProt_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_15","blade_16","blade_13"), "pistol4", "bullet", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c";
					if (i == 1) sld.dialog.currentnode = "Narval_warning";	
					if (i == 2) sld.dialog.currentnode = "Narval_parol";
					if (i == 3) sld.dialog.currentnode = "Narval_residence";
					sld.greeting = "Narval"; 
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_NarvalConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					sld.protector = true;
					if (i != 2) sld.protector.CheckAlways = true; //��������� ������
					LAi_SetGuardianType(sld);
					LAi_group_MoveCharacter(sld, "LSC_NARVAL");
					sld.LSC_clan = true;
				}
				if (i >= 4 && i <= 8) // �������
				{
					sld = GetCharacter(NPC_GenerateCharacter("RivadosProt_"+i, "rivados_"+(rand(6)+1), "man", "man", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_08","blade_04","blade_06"), "pistol4", "bullet", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c";
					if (i == 5 || i == 7) sld.dialog.currentnode = "Rivados_warning";	
					if (i == 6 || i == 8) sld.dialog.currentnode = "Rivados_parol";
					if (i == 4) sld.dialog.currentnode = "Rivados_residence";
					sld.greeting = "Rivados"; 
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_RivadosConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetGuardianType(sld);
					sld.protector = true;
					if (i != 6 ) sld.protector.CheckAlways = true; //��������� ������
					if (i != 8) sld.protector.CheckAlways = true; //��������� ������
					LAi_group_MoveCharacter(sld, "LSC_RIVADOS");
					sld.LSC_clan = true;
				}
				if (i >= 9) // ������ �����
				{
					sld = GetCharacter(NPC_GenerateCharacter("SharkProt_"+i, "citiz_"+(rand(9)+41), "man", "man", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_15","blade_10","blade_13"), "pistol4", "bullet", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c";
					if (i == 9) sld.dialog.currentnode = "Shark_storage";
					if (i == 10 || i == 11) sld.dialog.currentnode = "Shark_residence";	
					sld.greeting = "SharkPirate"; 
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_SharkConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetGuardianType(sld);
					sld.protector = true;
					sld.protector.CheckAlways = true; //��������� ������
					LAi_group_MoveCharacter(sld, "LSC_SHARK");
					sld.LSC_clan = true;
				}
			}
		}
	}
}

void CreateLSCInsideClan(aref loc) // ������� ����� ������ �� ��������
{
	if (CheckAttribute(loc, "lsc_inside"))
	{
		ref sld;
		string LocatorGroup, LocatorName;
		int i;
		int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15;
		int iScl = 30 + 3*sti(pchar.rank);
		
		if (CheckNPCQuestDate(loc, "LSCInside_date"))
		{
			SetNPCQuestDate(loc, "LSCInside_date");
			LocatorGroup = "goto";
			LocatorName = "goto"+i;	
			switch (loc.lsc_inside)
			{
				case "narval": // �������
					for (i=1; i<=10; i++)
					{
						LocatorGroup = "goto";
						LocatorName = "goto"+i;	
						sld = GetCharacter(NPC_GenerateCharacter("NarvalSoldInside_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, 1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_15","blade_16","blade_13"), RandPhraseSimple("pistol6","pistol4"), "bullet", iScl+100);
						sld.dialog.Filename = "Quest\LSC\Guardian.c";
						sld.dialog.currentnode = "Narval_soldier";	
						sld.greeting = "Narval"; 
						sld.RebirthPhantom = true; 
						LAi_CharacterReincarnation(sld, true, true);
						LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
						LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_NarvalConflict");
						ChangeCharacterAddressGroup(sld, loc.id, LocatorGroup, LocatorName);
						LAi_SetLoginTime(sld, 0.0, 24.0);
						LAi_SetWarriorType(sld);
						LAi_warrior_DialogEnable(sld, true);
						sld.watchBoxes = true;
						LAi_group_MoveCharacter(sld, "LSC_NARVAL");
						sld.LSC_clan = true;
					}
				break;
				
				case "rivados": // �������
					for (i=1; i<=8; i++)
					{
						LocatorGroup = "goto";
						LocatorName = "goto"+i;	
						sld = GetCharacter(NPC_GenerateCharacter("RivadosSoldInside_"+i, "rivados_"+(rand(6)+1), "man", "man", iRank, PIRATE, 1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_08","blade_04","blade_06"), RandPhraseSimple("pistol6","pistol5"), "bullet", iScl+100);
						sld.dialog.Filename = "Quest\LSC\Guardian.c";
						sld.dialog.currentnode = "Rivados_soldier";	
						sld.greeting = "Rivados"; 
						sld.RebirthPhantom = true; 
						LAi_CharacterReincarnation(sld, true, true);
						LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
						LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_RivadosConflict");
						ChangeCharacterAddressGroup(sld, loc.id, LocatorGroup, LocatorName);
						LAi_SetLoginTime(sld, 0.0, 24.0);
						LAi_SetWarriorType(sld);
						LAi_warrior_DialogEnable(sld, true);
						sld.watchBoxes = true;
						LAi_group_MoveCharacter(sld, "LSC_RIVADOS");
						sld.LSC_clan = true;
					}
				break;
				
				case "shark": // ������ �����
					for (i=1; i<=10; i++)
					{
						LocatorGroup = "goto";
						LocatorName = "goto"+i;	
						sld = GetCharacter(NPC_GenerateCharacter("SharkSoldInside_"+i, "citiz_"+(rand(9)+41), "man", "man", iRank, PIRATE, 1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_15","blade_10","blade_13"), RandPhraseSimple("pistol6","pistol5"), "bullet", iScl+100);
						sld.dialog.Filename = "Quest\LSC\Guardian.c";
						sld.dialog.currentnode = "Shark_soldier";	
						sld.greeting = "SharkPirate"; 
						sld.RebirthPhantom = true; 
						LAi_CharacterReincarnation(sld, true, true);
						LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
						LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_SharkConflict");
						ChangeCharacterAddressGroup(sld, loc.id, LocatorGroup, LocatorName);
						LAi_SetLoginTime(sld, 0.0, 24.0);
						LAi_SetWarriorType(sld);
						LAi_warrior_DialogEnable(sld, true);
						sld.watchBoxes = true;
						LAi_group_MoveCharacter(sld, "LSC_SHARK");
						sld.LSC_clan = true;
					}
				break;
			}
		}
	}
}

// ������ �������� - �������
void CreateKsochitamSkeletons(aref loc) //Jason
{	
	if (CheckAttribute(loc, "KsochitamSkeletons"))
	{
		ref sld;
		int i;
		int n = sti(loc.KsochitamSkeletons);
		string sIdf = loc.id;
		string sModel = "skel"+(rand(3)+1);
		string sBlade = LinkRandPhrase("blade_10","blade_06","blade_04");
		string sPistol = LinkRandPhrase("pistol6","pistol1","pistol5");
		int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+8;
		if (iRank > 56) iRank = 56;
		int iScl = 25+2*sti(pchar.rank);
		float fMft = MOD_SKILL_ENEMY_RATE/20;
		if (!CheckAttribute(loc, "Ksochitam_date") || GetNpcQuestPastDayParam(loc, "Ksochitam_date") >= 2)
		{
			SaveCurrentNpcQuestDateParam(loc, "Ksochitam_date");
			for (i=1; i<=n; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter(sIdf+"_skeleton_"+i, sModel, "skeleton", "skeleton", iRank, PIRATE, 2, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, sBlade, sPistol, "bullet", iScl*2+100);
				sld.MultiFighter = 0.9+fMft; // ������������
				ChangeCharacterAddressGroup(sld, sIdf, "monsters", "monster"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_group_MoveCharacter(sld, "KSOCHITAM_MONSTERS");
			}
		}
	}
}

// ������� - ���� �� ����� ��� - ������
void CreateKhaelRoaSkeletons(aref loc) //Jason
{	
	if (CheckAttribute(loc, "id.label"))
	{
		if (loc.id.label == "Maze" || loc.id.label == "Alcove")
		{
			ref sld;
			aref grp;
			makearef(grp, loc.locators.monsters);
			int n = GetAttributesNum(grp);
			int i;
			string sIdf = loc.id;
			string sPistol = "pistol1";
			if (MOD_SKILL_ENEMY_RATE > 2) sPistol = "pistol5";
			if (MOD_SKILL_ENEMY_RATE > 4) sPistol = "pistol6";
			if (MOD_SKILL_ENEMY_RATE > 8) sPistol = "pistol4";
			
			int iRank = 17+MOD_SKILL_ENEMY_RATE*2;
			int iHp = 300+MOD_SKILL_ENEMY_RATE*70;
			int iHpt = 200+MOD_SKILL_ENEMY_RATE*30;
			float fMft = 1.0+MOD_SKILL_ENEMY_RATE/20;
			
			if (!CheckAttribute(loc, "KhaelRoa_date") || GetNpcQuestPastDayParam(loc, "KhaelRoa_date") >= 1)
			{
				SaveCurrentNpcQuestDateParam(loc, "KhaelRoa_date");
				for (i=0; i<n; i++)
				{
					if (rand(1) == 0 || loc.id.label == "Alcove") // ��������
					{
						sld = GetCharacter(NPC_GenerateCharacter(sIdf+"_skeleton_"+i, "Chavinavi_1", "skeleton", "skeleton", iRank+5, PIRATE, 1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank+5, 80, 80, "topor_01", "", "", 50);
						LAi_SetHP(sld, iHp, iHp);
						sld.KhaelRoaMonster = true;
						sld.name = "Chavinavy";
						sld.lastname = "";
						sld.MultiFighter = fMft; // ������������
					}
					else // �������
					{
						sld = GetCharacter(NPC_GenerateCharacter(sIdf+"_skeleton_"+i, "skel"+(rand(3)+1), "skeleton", "skeleton", iRank, PIRATE, 1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_10","blade_06","blade_04"), sPistol, "bullet", 50);
						LAi_SetHP(sld, iHpt, iHpt);
						sld.name = "temple undead";
						sld.lastname = "";
					}
					sld.LSC_clan = true; // ��� ����������������
					ChangeCharacterAddressGroup(sld, sIdf, "monsters", GetAttributeName(GetAttributeN(grp, i)));
					LAi_SetWarriorType(sld);
					LAi_warrior_SetStay(sld, true);
					LAi_CharacterDisableDialog(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
				}
			}
		}
	}
}

// ���������� ����������. eddy
void CreateIncquisitio(aref loc)
{	
	if (GetCityNation("Santiago") != SPAIN) return; 
	
	if (CheckAttribute(loc, "Incquisitio"))
	{
		ref sld;
		string LocatorGroup, LocatorName;
		int i, nSit;
		//====> �������� �����������
		if (CheckNPCQuestDate(loc, "Incquisitor_date"))
		{
			SetNPCQuestDate(loc, "Incquisitor_date");
			LocatorGroup = "goto";
			nSit = rand(2)+1;
			for (i=1; i<=3; i++)
			{
				LocatorGroup = "goto";
				LocatorName = LAi_FindRandomLocator("goto");				 
				if (i==nSit) 
				{
					LocatorGroup = "sit";
					LocatorName = "sit"+(rand(3)+1);			
				}
				sld = GetCharacter(NPC_GenerateCharacter("Incquisitor_"+i, "priest_sp"+i, "man", "man2", 20, SPAIN, 1, false, "citizen"));
				sld.Dialog.Filename = "Incquistors.c";									
				LAi_LoginInCaptureTown(sld, true);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				if (i==nSit) LAi_SetSitType(sld);
				else LAi_SetCitizenType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", LocatorGroup, LocatorName);
			}
		}
		//====> �������� ������.
		if (CheckNPCQuestDate(loc, "Guard_date"))
		{
			SetNPCQuestDate(loc, "Guard_date");
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("IncqGuard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", 35, SPAIN, 1, true, "soldier"));
				sld.City = "Santiago";
				sld.CityType = "soldier";
				LAi_LoginInCaptureTown(sld, true);
				FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15, 100, 90, BLADE_LONG, "pistol3", "grapeshot", 100);//�������
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");	
				locatorName = PlaceCharacter(sld, "soldiers", "random");
				// eddy. ���������, ������ �� ������ ���� ����������� -->				
				if (locatorName == "soldier1" || locatorName == "soldier2")
				{
					sld.protector.CheckAlways = true; //��������� ������
					sld.Dialog.Filename = "Incquistors.c";
					sld.greeting = "protector";
				}
				else
				{
					if (findsubstr(locatorName, "protector" , 0) != -1) sld.protector = true;
					sld.Dialog.Filename = "Common_Soldier.c";
					sld.greeting = "soldier";
				}
				// <-- eddy. ���������, ������ �� ������ ���� �����������
			}
		}
		//====> �������� �����������, ��� � �����.
		if (!CheckAttribute(loc, "Prison_date") || GetNpcQuestPastDayParam(loc, "Prison_date") > 30)
		{
			SaveCurrentNpcQuestDateParam(loc, "Prison_date");
			for (i=1; i<=8; i++)
			{
				if (rand(100)<70)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Prisoner_"+i, "Prison_"+(rand(4)+1), "man", "man2", 10, SPAIN, 30, false, "slave"));							
					sld.Dialog.Filename = "Incquistors.c";
					sld.greeting = "Gr_prison";
					LAi_LoginInCaptureTown(sld, true);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetActorType(sld);
					if (rand(10)>5) LAi_ActorSetLayMode(sld);
					else 
					{
						LAi_SetGroundSitType(sld);
					}				
					//ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "prison", "prison"+i);
					PlaceCharacter(sld, "prison", "random_free");
				}
			}
		}
	}
}
//eddy. ���������� �����
void CreateMayak(aref loc)
{
	if (loc.type == "mayak")
	{		
		if (!CheckAttribute(loc, "Mayak_date") || GetNpcQuestPastDayParam(loc, "Mayak_date") > 2)
		{
			SaveCurrentNpcQuestDateParam(loc, "Mayak_date");

			if(CheckAttribute(loc, "from_colony")) 
			{
				int iColony = FindColony(loc.from_colony);
			}
			else 
			{
				iColony = FindColony(GetCityNameByIsland(GiveArealByLocation(loc)));
			}
			if(iColony == -1) return;

			int iNation = GetCityNation(GetCityNameByIsland(GiveArealByLocation(loc)));
			if(iNation == -1) return;

			int iCitizensQuantity, iModel;
			ref chr;
			aref st, solderLoc;
			int iChar, i;
			string slai_group, locatorName;
			slai_group = GetNationNameByType(iNation)  + "_mayak"; 
			// ������� -->
			if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
			{
				makearef(st, loc.locators.soldiers);
				iCitizensQuantity = GetAttributesNum(st);
				for (i=0; i<iCitizensQuantity; i++)
				{
					solderLoc = GetAttributeN(st, i);
					locatorName = GetAttributeName(solderLoc);					
					if (findsubstr(locatorName, "protector" , 0) != -1) 
					{		
						iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
						chr = &characters[iChar];
					}
					else
					{
						chr = GetCharacter(NPC_GenerateCharacter("GenChar_", "mush_eng_1", "man", "mushketer", sti(pchar.rank), iNation, 2, false, "soldier"));
						chr.id = "GenChar_" + chr.index;
						chr.MusketerDistance = 0;
					}					
					chr.City = Colonies[iColony].id;
					chr.CityType = "soldier";
					chr.greeting = "soldier_common";
					SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+6, true); // ������ ����
					LAi_SetLoginTime(chr, 0.0, 24.0);
					solderLoc = GetAttributeN(st, i);
					locatorName = GetAttributeName(solderLoc);
					ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", locatorName);
					// eddy. ���������, ������ �� ������ ���� ����������� -->
					if (findsubstr(locatorName, "protector" , 0) != -1) 
					{
						chr.protector = true;
						chr.greeting = "protector";
						if (locatorName != "protector1" && locatorName != "protector2") 
						{
							chr.protector.CheckAlways = 1; //��������� ������
							if (locatorName == "protector11") chr.dialog.currentnode = "PortRoyal_Mayak";
							else chr.dialog.currentnode = "PortRoyal_Gans";
						}
					}
					else chr.greeting = "soldier";
					// <-- eddy. ���������, ������ �� ������ ���� �����������
					chr.dialog.filename = "Common_Soldier.c";
					LAi_SetGuardianType(chr);
					LAi_group_MoveCharacter(chr, slai_group);
				}
			}
			// ������� <--
			// ������� -->
			if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
			{
				makearef(st, loc.locators.patrol);
				iCitizensQuantity = GetAttributesNum(st);
				for (i=0; i<iCitizensQuantity; i++)
				{
					iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
					chr = &characters[iChar];
					chr.City = Colonies[iColony].id;
					chr.CityType = "soldier";
					SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // ������ ����
					LAi_SetLoginTime(chr, 0.0, 24.0);
					LAi_SetPatrolType(chr);
					LAi_group_MoveCharacter(chr, slai_group);
					chr.greeting = "soldier";
					PlaceCharacter(chr, "patrol", "random_free");
					chr.dialog.filename = "Common_Soldier.c";
					chr.dialog.currentnode = "first time";
				}
			}
			// ������� <--
			LAi_group_SetLookRadius(slai_group, 80);
			LAi_group_SetHearRadius(slai_group, 80);
		}
	}
}

void CreateBrothels(aref loc)
{
	if (CheckAttribute(loc, "brothel"))
	{
		ref location;
		if (findsubstr(loc.id, "SecBrRoom", 0) != -1)
		{
			location = &locations[FindLocation(loc.fastreload + "_Brothel")];
		}
		else
		{
			makeref(location, loc);
		}
		if (!CheckAttribute(location, "Brothel_date") || GetNpcQuestPastDayParam(location, "Brothel_date") > 100)
		{
			ref sld;
			int iColony, iNation, qty, num, qtyAll;
			// ==>  ������ ������� ����, ���� �� �������� � ��������
			string horse[8];
			horse[0] = "women_19";
			horse[1] = "women_20";
			horse[2] = "women_21";
			horse[3] = "women_22";
			horse[4] = "women_23";
			horse[5] = "women_24";
			horse[6] = "women_25";
			horse[7] = "women_26";
			SaveCurrentNpcQuestDateParam(location, "Brothel_date");
			if(CheckAttribute(location, "fastreload"))
			{
				iColony = FindColony(location.fastreload);
			}
			else return;
			iNation = GetCityNation(location.fastreload);
			string slai_group = GetNationNameByType(iNation)  + "_citizens";
			qty = 1;
			qtyAll = rand(2) + 4;
			while (qty < qtyAll)
			{
				num = rand(7);
				if (horse[num] != "")
				{
					sld = GetCharacter(NPC_GenerateCharacter("HorseGen_"+location.index +"_"+ qty, horse[num], "woman", "towngirl", 3, iNation, 100, false, "soldier"));
					sld.City = location.fastreload;
					sld.CityType = "horse";
					sld.dialog.filename = "Common_Brothel.c";
					sld.dialog.currentnode = "Horse_talk";
					sld.greeting = "whore";
					switch (location.fastreload)
					{
						case "Marigo": 			sld.quest.price = 40*(rand(5) + rand(5)); 			break;
						case "Tortuga":   		sld.quest.price = 40*(rand(5) + rand(5)); 			break;
						case "FortFrance":  	sld.quest.price = 50 + 40*(rand(5) + rand(5)); 		break;
						case "PortRoyal":  		sld.quest.price = 150 + 40*(rand(5) + rand(5)); 	break;
						case "Charles":   		sld.quest.price = 200 + 40*(rand(5) + rand(5)); 	break;
						case "Bridgetown":  	sld.quest.price = 250 + 40*(rand(5) + rand(5)); 	break;
						case "SantoDomingo": 	sld.quest.price = 300 + 40*(rand(5) + rand(5)); 	break;
						case "Panama":   		sld.quest.price = 500 + 40*(rand(5) + rand(5)); 	break;
					}
					LAi_SetCitizenType(sld);
					LAi_group_MoveCharacter(sld, slai_group);
					ChangeCharacterAddressGroup(sld, location.id, "goto", "goto"+qty);
					horse[num] = "";
					qty++;
				}
			}
		}
	}
}

void CreatePearlVillage(aref loc) // Jason: ������� �������
{
	if (CheckAttribute(loc, "pearlVillage"))
	{
		if (CheckNPCQuestDate(loc, "miskito_date"))
		{
			SetNPCQuestDate(loc, "miskito_date");
			int i, iMassive;
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int grp = sti(loc.pearlVillage);
			int num = rand(2)+6; //���-�� 
			ref chr;
			string model[10];		
			model[0] = "Miskito_1";
			model[1] = "Miskito_2";
			model[2] = "Miskito_3";
			model[3] = "Miskito_4";
			model[4] = "Miskito_5";
			model[5] = "Miskito_6";
			model[6] = "Miskito_1";
			model[7] = "Miskito_2";
			model[8] = "Miskito_3";
			model[9] = "Miskito_4";
			i = 0;
			
			while(i < num)
			{
				iMassive = rand(9);
				if (model[iMassive] != "")
				{
					chr = GetCharacter(NPC_GenerateCharacter("Miskito"+grp+"_"+i, model[iMassive], "man", "man", iRank, ENGLAND, 1, true, "native"));
					SetFantomParamFromRank(chr, iRank, true);
					chr.name = GetIndianName(MAN);
					chr.lastname = "";
					LAi_SetLoginTime(chr, 6.0, 21.99);
					LAi_CharacterReincarnation(chr, true, true);
					LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); 
					chr.dialog.Filename = "indian_dialog.c";
					chr.dialog.currentnode = "IndianMan";
					chr.greeting = "indian_male";
					GiveItem2Character(chr, LinkRandPhrase("slave_01","slave_02","topor_05"));
					EquipCharacterbyItem(chr, LinkRandPhrase("slave_01","slave_02","topor_05"));
					chr.city = "SantaCatalina"; //��� �����-��������
					if (grp == 3) chr.city = "Maracaibo"; // Addon 2016-1 Jason ��������� �������
					PlaceCharacter(chr, "goto", "random");
					LAi_SetWarriorType(chr);
					LAi_group_MoveCharacter(chr, "MiskitoGroup"+grp);
					i++;
					model[iMassive] = "";
				}
			}
			if (rand(1) == 1) // ������� � ��������
			{
				for (i=1; i<=2; i++)
				{
					chr = GetCharacter(NPC_GenerateCharacter("MiskitoSit"+grp+"_"+i, "Miskito_"+(rand(5)+1), "man", "man", iRank, ENGLAND, 1, true, "native"));
					SetFantomParamFromRank(chr, iRank, true);
					chr.name = GetIndianName(MAN);
					chr.lastname = "";
					chr.dialog.Filename = "Indian_dialog.c";
					chr.dialog.currentnode = "IndianMan";
					chr.greeting = "indian_male";
					GiveItem2Character(chr, LinkRandPhrase("slave_01","slave_02","topor_05"));
					EquipCharacterbyItem(chr, LinkRandPhrase("slave_01","slave_02","topor_05"));
					chr.city = "SantaCatalina"; //��� �����-��������
					if (grp == 3) chr.city = "Maracaibo"; // Addon 2016-1 Jason ��������� �������
					ChangeCharacterAddressGroup(chr, loc.id, "sit", "ground"+i);
					LAi_SetGroundSitType(chr);
					LAi_group_MoveCharacter(chr, "MiskitoGroup"+grp);
				}
			}
			for (i=1; i<=3; i++) // �������
			{
				chr = GetCharacter(NPC_GenerateCharacter("MiskitoWoman"+grp+"_"+i, "squaw_"+i, "woman", "woman_B", 10, ENGLAND, 1, true, "citizen"));
				SetFantomParamFromRank(chr, 10, true);
				chr.name = GetIndianName(WOMAN);
				chr.lastname = "";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				chr.dialog.Filename = "Indian_dialog.c";
				chr.dialog.currentnode = "IndianWoman";
				//chr.greeting = "cit_common";
				RemoveAllCharacterItems(chr, true);
				chr.city = "SantaCatalina"; //��� �����-��������
				if (grp == 3) chr.city = "Maracaibo"; // Addon 2016-1 Jason ��������� �������
				PlaceCharacter(chr, "goto", "random");
				LAi_SetCitizenType(chr);
				LAi_group_MoveCharacter(chr, "MiskitoGroup"+grp);
			}
			LAi_group_SetLookRadius("MiskitoGroup"+grp, 16);
			LAi_group_SetHearRadius("MiskitoGroup"+grp, 10);				
		}
	}
}

void CreateIndianVillage(aref loc) // Jason: ������� �������
{
	if (CheckAttribute(loc, "indianVillage"))
	{	
		if (CheckNPCQuestDate(loc, "canib_date"))
		{
			SetNPCQuestDate(loc, "canib_date");
			int i, iMassive;
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int num = rand(2)+6; //���-�� 
			ref chr;
			string model[10];
				
			model[0] = "canib_1";
			model[1] = "canib_2";
			model[2] = "canib_3";
			model[3] = "canib_4";
			model[4] = "canib_5";
			model[5] = "canib_6";
			model[6] = "canib_1";
			model[7] = "canib_2";
			model[8] = "canib_3";
			model[9] = "canib_4";
			i = 0;
			
			while(i < num)
			{
				iMassive = rand(9);
				if (model[iMassive] != "")
				{
					chr = GetCharacter(NPC_GenerateCharacter("Canib_"+i, model[iMassive], "man", "man", iRank, PIRATE, 1, true, "native"));
					SetFantomParamFromRank(chr, iRank, true);
					chr.name = GetIndianName(MAN);
					chr.lastname = "";
					LAi_SetLoginTime(chr, 6.0, 21.99);
					LAi_CharacterReincarnation(chr, true, true);
					LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); 
					chr.dialog.Filename = "Indian_dialog.c";
					chr.dialog.currentnode = "IndianMan";
					chr.greeting = "indian_male";
					GiveItem2Character(chr, LinkRandPhrase("slave_01","slave_02","topor_05"));
					EquipCharacterbyItem(chr, LinkRandPhrase("slave_01","slave_02","topor_05"));
					PlaceCharacter(chr, "goto", "random");
					LAi_SetWarriorType(chr);
				LAi_group_MoveCharacter(chr, "IndianGroup");
				i++;
				model[iMassive] = "";
			}
		}
			if (rand(1) == 1) // ������� � ��������
			{
				for (i=1; i<=2; i++)
				{
					chr = GetCharacter(NPC_GenerateCharacter("CanibSit_"+i, "Canib_"+(rand(5)+1), "man", "man", iRank, PIRATE, 1, true, "native"));
					SetFantomParamFromRank(chr, iRank, true);
					chr.name = GetIndianName(MAN);
					chr.lastname = "";
					chr.dialog.Filename = "Indian_dialog.c";
					chr.dialog.currentnode = "IndianMan";
					chr.greeting = "indian_male";
					GiveItem2Character(chr, LinkRandPhrase("slave_01","slave_02","topor_05"));
					EquipCharacterbyItem(chr, LinkRandPhrase("slave_01","slave_02","topor_05"));
					ChangeCharacterAddressGroup(chr, loc.id, "sit", "ground"+i);
					LAi_SetGroundSitType(chr);
					LAi_group_MoveCharacter(chr, "IndianGroup");
				}
			}
			for (i=1; i<=3; i++) // �������
			{
				chr = GetCharacter(NPC_GenerateCharacter("CanibWoman_"+i, "squaw_"+i, "woman", "woman_B", 10, PIRATE, 1, true, "citizen"));
				SetFantomParamFromRank(chr, 10, true);
				chr.name = GetIndianName(WOMAN);
				chr.lastname = "";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				chr.dialog.Filename = "Indian_dialog.c";
				chr.dialog.currentnode = "IndianWoman";
				//chr.greeting = "cit_common";
				RemoveAllCharacterItems(chr, true);
				PlaceCharacter(chr, "goto", "random");
				LAi_SetCitizenType(chr);
				LAi_group_MoveCharacter(chr, "IndianGroup");
			}
			LAi_group_SetLookRadius("IndianGroup", 20);
			LAi_group_SetHearRadius("IndianGroup", 15);				
		}
	}
}

void CreateMinentownMine(aref loc) // Jason: ����� �� �������
{
	if (loc.id == "Minentown_mine")
	{
		if (!CheckAttribute(loc, "mine_date") || GetNpcQuestPastDayParam(loc, "mine_date") > 30)
		{
			SaveCurrentNpcQuestDateParam(loc, "mine_date");
			int i;
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			ref chr;
			for (i=1; i<=21; i++) // ����������
			{
				chr = GetCharacter(NPC_GenerateCharacter("MineConvict_"+i, "prizon_"+(rand(7)+1), "man", "man_B", iRank, PIRATE, 30, true, "native"));
				SetFantomParamFromRank(chr, iRank, true);
				chr.dialog.Filename = "Convict_dialog.c";
				chr.dialog.currentnode = "First time";
				chr.greeting = "convict";
				GiveItem2Character(chr, RandPhraseSimple("slave_01","topor_05"));
				EquipCharacterbyItem(chr, RandPhraseSimple("slave_01","topor_05"));
				chr.city = "Minentown"; 
				ChangeCharacterAddressGroup(chr, loc.id, "monsters", "convict"+i);
				LAi_SetStayType(chr);
				LAi_group_MoveCharacter(chr, "SPAIN_CITIZENS");
			}
			for (i=1; i<=7; i++) // �������� �������
			{
				chr = GetCharacter(NPC_GenerateCharacter("MineSoldier_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank+5, SPAIN, 30, true, "soldier"));
				SetFantomParamFromRank(chr, iRank+5, true);
				chr.dialog.Filename = "Common_Soldier.c";
				chr.greeting = "soldier";
				LAi_CharacterReincarnation(chr, true, true);
				LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); 
				chr.city = "Minentown";
				chr.CityType = "soldier";
				PlaceCharacter(chr, "goto", "random");
				LAi_SetPatrolType(chr);
				LAi_group_MoveCharacter(chr, "SPAIN_CITIZENS");
			}
			for (i=1; i<=4; i++) // ����������
			{
				chr = GetCharacter(NPC_GenerateCharacter("MineProtector_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank+10, SPAIN, 30, true, "soldier"));
				SetFantomParamFromRank(chr, iRank+10, true);
				chr.dialog.Filename = "Common_Soldier.c";
				chr.greeting = "protector";
				LAi_CharacterReincarnation(chr, true, true);
				LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); 
				chr.city = "Minentown";
				ChangeCharacterAddressGroup(chr, loc.id, "soldiers", "soldier"+i);
				LAi_SetGuardianType(chr);
				LAi_group_MoveCharacter(chr, "SPAIN_CITIZENS");
			}	
		}
		chr = GetCharacter(NPC_GenerateCharacter("MineHead", "off_spa_5", "man", "man", 35, SPAIN, 30, true, "soldier"));
		FantomMakeCoolFighter(chr, 35, 100, 100, "blade_17", "pistol4", "bullet", 250);
		chr.dialog.Filename = "MineHead_dialog.c";
		chr.greeting = "patrol";
		chr.city = "Minentown";
		ChangeCharacterAddressGroup(chr, loc.id, "quest", "quest1");
		LAi_SetGuardianType(chr);
		LAi_group_MoveCharacter(chr, "SPAIN_CITIZENS");
	}
}

void CreateMineBandits(aref loc) // Jason: ������� � ������� � ���������
{
	ref chr;
	int i;
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
	int iScl = 80;
	if (CheckAttribute(loc, "mine_bandits"))
	{
		if (loc.id == "Mine_exit")
		{
			// ������������ ���� � �������
			chrDisableReloadToLocation = true;//������� �������
			DoQuestCheckDelay("Saga_MineBanditsTalk", 2.0);
			if (CheckNPCQuestDate(loc, "bandits_date"))
			{
				SetNPCQuestDate(loc, "bandits_date");
				for (i=1; i<=6; i++)
				{
					if (i >= 3)
					{
						chr = GetCharacter(NPC_GenerateCharacter("Mine_bandit_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, 1, true, "soldier"));
						FantomMakeCoolFighter(chr, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
					}
					else
					{
						chr = GetCharacter(NPC_GenerateCharacter("Mine_bandit_"+i, "mush_ctz_"+(rand(2)+10), "man", "mushketer", iRank, PIRATE, 1, false, "soldier"));
						FantomMakeCoolFighter(chr, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
						chr.MusketerDistance = 0; 
					}
					chr.dialog.Filename = "Quest\Saga\OtherNPC.c";
					if (i == 3) chr.dialog.currentnode = "mine_bandit";
					else chr.dialog.currentnode = "mine_bandit_0";
					chr.greeting = "bandos";
					LAi_CharacterReincarnation(chr, true, true);
					LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "Saga_MineBanditsFire");
					ChangeCharacterAddressGroup(chr, loc.id, "soldiers", "protector"+i);
					LAi_SetGuardianType(chr);
					LAi_group_MoveCharacter(chr, "PIRATE_CITIZENS");
				}
			}
		}
		if (loc.id == "Mine_01")
		{
			if (CheckNPCQuestDate(loc, "bandits_date"))
			{
				SetNPCQuestDate(loc, "bandits_date");
				for (i=1; i<=4; i++)
				{
					if (i == 3 || i == 4)
					{
						chr = GetCharacter(NPC_GenerateCharacter("Mine_banditx_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, 1, true, "soldier"));
						FantomMakeCoolFighter(chr, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
					}
					else
					{
						chr = GetCharacter(NPC_GenerateCharacter("Mine_banditx_"+i, "mush_ctz_"+(rand(2)+10), "man", "mushketer", iRank, PIRATE, 1, false, "soldier"));
						FantomMakeCoolFighter(chr, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
						chr.MusketerDistance = 0; 
					}
					chr.dialog.Filename = "Quest\Saga\OtherNPC.c";
					if (i == 1) chr.dialog.currentnode = "mine_banditx";
					else chr.dialog.currentnode = "mine_bandit_0";
					chr.greeting = "bandos";
					LAi_CharacterReincarnation(chr, true, true);
					LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2);
					LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "Saga_MineBanditsxFire");
					ChangeCharacterAddressGroup(chr, loc.id, "soldiers", "protector"+i);
					LAi_SetGuardianType(chr);
					LAi_group_MoveCharacter(chr, "PIRATE_CITIZENS");
				}
			}
		}
	}
}

void CreateInsideHouseEncounters(aref loc)
{	
	if (CheckAttribute(loc, "MustSetReloadBack") && loc.id.label == "house" && CheckAttribute(loc,"fastreload") && !IsLocationCaptured(loc.fastreload+"_town"))
	{
		// ��������� ���������� ������ �� ������������ �����������
		int iBaseCity = FindLocation(loc.fastreload+"_town");
		if (!CheckAttribute(&locations[iBaseCity], "houseEnc")) return;
		if (CheckAttribute(&locations[iBaseCity], "QuestCapture")) return; // ���� ���� ��������� ���
		//==> ��������� ����� ����
		if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location") && pchar.GenQuest.SeekSpy.Location == loc.id) return;
		//==> ��������� ����� �������� ������
		if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId") && pchar.questTemp.jailCanMove.Deliver.locationId == loc.id) return;
		if (CheckAttribute(pchar, "questTemp.Shadowtrader.ClearHouse")) return; // 240912
		if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "sdm" && loc.id == "CommonPirateHouse") return; // Addon-2016 Jason, ����������� ���������� (���)
		//--> ����� �� ���������
		bool bDN = IsDay();
    	aref arRld, arDis;
		makearef(arRld, loc.reload);
		int i;
    	int	Qty = GetAttributesNum(arRld);
		for (i=0; i<Qty; i++)
    	{
    		arDis = GetAttributeN(arRld, i);
    		if (arDis.name != "reload1")
    		{
				if (bDN && !isBadReputation(pchar, 40)) DeleteAttribute(arDis, "disable");
				else arDis.disable = true; //��������� ���� � ������� 2 ������
    		}
    	}
		//<-- ����� �� ���������
		//==> ��������� ������� ������� ������		
		if (locations[reload_cur_location_index].type == "town")
		{
			ref chr, npchar;
			aref rCity;
			makearef(rCity, locations[iBaseCity].houseEnc);		
			bool bMW = rand(1);
			int iNation = GetCityNation(loc.fastreload);
			string slai_group = GetNationNameByType(iNation)  + "_citizens";
			string Model, Name, LastName, sName;
			string sTemp = reload_locator_ref.name + loc.index;
			int iManIdx = GetCharacterIndex("HouseMan_"+iBaseCity+"_"+loc.index);
			int iWomanIdx = GetCharacterIndex("HouseWoman_"+iBaseCity+"_"+loc.index);
			if (iWomanIdx != -1 || iManIdx != -1) 
			{				
				if (!CheckAttribute(rCity, sTemp)) //��� ���� ������, �� ��� �� ��� ��, �����!!! ������� �� ������� ������� ������
				{
					if (iWomanIdx != -1) 
					{
						npchar = &characters[iWomanIdx];
						SetRandomNameToCharacter(npchar);
						npchar.model = "women_"+(rand(3)+7);
						FaceMaker(npchar);
						CirassMaker(npchar);
						SetNewModelToChar(npchar);  // ���������� ������ �� ����			
						LAi_SetActorType(npchar);
						LAi_ActorDialog(npchar, pchar, "", 1.0, 0); 
						LAi_group_MoveCharacter(npchar, slai_group);
						rCity.(sTemp) = "woman"; //��������� �����������
						rCity.(sTemp).woman.model = npchar.model;
						rCity.(sTemp).woman.name = npchar.name;
						rCity.(sTemp).woman.lastname = npchar.lastname;
						//<-- �������� ��������� ��� � ��������� �������
					}
					else 
					{
						npchar = &characters[iManIdx];
						SetRandomNameToCharacter(npchar);
						npchar.model = "citiz_"+(rand(9)+1);
						FaceMaker(npchar);
						CirassMaker(npchar);
						SetNewModelToChar(npchar);  // ���������� ������ �� ����			
						LAi_SetActorType(npchar);
						LAi_ActorDialog(npchar, pchar, "", 1.0, 0); 
						LAi_group_MoveCharacter(npchar, slai_group);
						//--> �������� ��������� ��� � ��������� �������
						rCity.(sTemp) = "man"; //��������� �����������
						rCity.(sTemp).man.model = npchar.model;
						rCity.(sTemp).man.name = npchar.name;
						rCity.(sTemp).man.lastname = npchar.lastname;
						//<-- �������� ��������� ��� � ��������� �������
					}
				}
				else //��� ���� ��������� �� ��� � ������� �������
				{
					if (iWomanIdx != -1) npchar = &characters[iWomanIdx];
					else npchar =  &characters[iManIdx];
					string sSex = sTemp + "." + rCity.(sTemp);
					if (rCity.(sSex).model != npchar.model) 
					{	//������ �� ������� ������, ���������� ��������	
						npchar.model = rCity.(sSex).model;
						if (rCity.(sTemp) == "man") 
						{
							npchar.sex = "man";
							npchar.model.animation = "man";
							npchar.dialog.currentnode = "HouseMan";
							npchar.greeting = "citizen_male";
							LAi_NPC_Equip(npchar, sti(npchar.rank), true, true);
						}
						else 
						{
							npchar.sex = "woman";
							npchar.model.animation = "towngirl";
							npchar.dialog.currentnode = "HouseWoman";
							npchar.greeting = "citizen_female";
							DeleteAttribute(npchar, "equip");
						}
						npchar.name = rCity.(sSex).name;
						npchar.lastname = rCity.(sSex).lastname;
						FaceMaker(npchar);
						CirassMaker(npchar);
						SetNewModelToChar(npchar);  // ���������� ������ �� ����					
					}
				}
				return;
			}
			Model = "";
			Name = "";
			LastName = "";
			//-->> ��������� �� ����� ������		
			if (CheckAttribute(rCity, sTemp))
			{
				if (GetNpcQuestPastDayParam(rCity, sTemp) < 30)
				{
					if (rCity.(sTemp) == "man") 
					{//���� ��� �����, �� ����. - ����
						bMW = true;
						if (CheckAttribute(rCity, sTemp + ".woman.model"))
						{
							Model = rCity.(sTemp).woman.model;
							Name = rCity.(sTemp).woman.name;
							LastName = rCity.(sTemp).woman.lastname;
						}
						else
						{
							if (CheckAttribute(rCity, sTemp + ".man.lastname"))
							{
								LastName = rCity.(sTemp).man.lastname;
							}
						}
					}
					else 
					{//���� ���� ����, �� ����. - �����
						bMW = false;
						if (CheckAttribute(rCity, sTemp + ".man.model"))
						{
							Model = rCity.(sTemp).man.model;
							Name = rCity.(sTemp).man.name;
							LastName = rCity.(sTemp).man.lastname;
						}
						else
						{
							if (CheckAttribute(rCity, sTemp + ".woman.lastname"))
							{
								LastName = rCity.(sTemp).woman.lastname;
							}
						}
					}
				}
				else //����� ������ � ����
				{
					if (rand(10) > 8) //���� �� ������ ���.
					{
						for (i=0; i<Qty; i++) 
    					{//������� ��������� ���� �������� ������� ������ (���� ���� � �� ��������) 
    						arDis = GetAttributeN(arRld, i);
    						if (arDis.name != "reload1")
    						{
								DeleteAttribute(arDis, "disable");
    						}
    					}
						return; 
					}
					SaveCurrentNpcQuestDateParam(rCity, sTemp); //����� ���� ��������� ������� ��� � ���� �������
				}
			}
			else 
			{
				if (rand(10) > 8) //���� �� ������ ���.
				{
					for (i=0; i<Qty; i++) 
    				{//������� ��������� ���� �������� ������� ������ (���� ���� � �� ��������) 
    					arDis = GetAttributeN(arRld, i);
    					if (arDis.name != "reload1")
    					{
							DeleteAttribute(arDis, "disable");
    					}
    				}
					return; 
				}
				SaveCurrentNpcQuestDateParam(rCity, sTemp); //����� ���� ��������� ������� ��� � ���� �������
			}
			//<<-- ��������� �� ����� ������
			if (bMW)
			{//============= ������� ���� ====================
				if (Model == "") Model = "women_"+(rand(3)+7);
				sName = "HouseWoman_"+reload_cur_location_index+"_"+loc.index;
				chr = GetCharacter(NPC_GenerateCharacter(sName, Model, "woman", "towngirl", rand(2)+4, iNation, 3, false, "citizen"));
				if (Name != "") chr.name = Name;
				if (LastName != "") chr.lastname = LastName;
				chr.dialog.Filename = "HouseEnc_dialog.c"; 
				chr.dialog.currentnode = "HouseWoman";
				chr.CityType = "citizen";
				chr.city = loc.fastreload; //���
				chr.greeting = "citizen_female";			
				ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
				LAi_SetActorType(chr);
				LAi_ActorDialog(chr, pchar, "", 1.0, 0); 
				LAi_group_MoveCharacter(chr, slai_group);
				//--> �������� ��������� ��� � ��������� �������
				rCity.(sTemp) = "woman"; //��������� �����������
				rCity.(sTemp).woman.model = chr.model;
				rCity.(sTemp).woman.name = chr.name;
				rCity.(sTemp).woman.lastname = chr.lastname;
				//<-- �������� ��������� ��� � ��������� �������
			}
			else
			{//============ ������� ������ ==================
				if (Model == "") Model = "citiz_"+(rand(9)+11);
				sName = "HouseMan_"+reload_cur_location_index+"_"+loc.index;
				chr = GetCharacter(NPC_GenerateCharacter(sName, Model, "man", "man", rand(10)+4, iNation, 3, true, "citizen"));
				if (Name != "") chr.name = Name;
				if (LastName != "") chr.lastname = LastName;
				chr.dialog.Filename = "HouseEnc_dialog.c"; 
				chr.dialog.currentnode = "HouseMan";
				chr.CityType = "citizen";
				chr.city = loc.fastreload; //���
				chr.greeting = "citizen_male";
				ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
				LAi_SetActorType(chr);
				LAi_ActorDialog(chr, pchar, "", 1.0, 0); 
				LAi_group_MoveCharacter(chr, slai_group);
				//--> �������� ��������� ��� � ��������� �������
				rCity.(sTemp) = "man"; //��������� �����������
				rCity.(sTemp).man.model = chr.model;
				rCity.(sTemp).man.name = chr.name;
				rCity.(sTemp).man.lastname = chr.lastname;
				//<-- �������� ��������� ��� � ��������� �������
				
				// --> �������
				if(CheckAttribute(PChar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "seek" && chr.city == "Beliz")
				{
					chr.id = "Beliz_townbandos";
					chr.model = "citiz_23";
					Characters_RefreshModel(chr); 
					Rank = 20+MOD_SKILL_ENEMY_RATE*3;
					FantomMakeCoolFighter(chr, Rank, 60, 60, RandPhraseSimple("blade_12","blade_13"), RandPhraseSimple("pistol6","pistol4"), "bullet", 250);
					Mft = MOD_SKILL_ENEMY_RATE/20;
					chr.MultiFighter = 1.0+Mft; // ������������
					chr.dialog.filename = "Quest\Caleuche_dialog.c";
					chr.dialog.currentnode = "Beliz_townbandos";
					chr.greeting = "marginal";
					LAi_SetImmortal(chr, true);
					GiveItem2Character(chr, "kaleuche_letter");
					chr.SaveItemsForDead = true;
					chr.DontClearDead = true;
					pchar.questTemp.Caleuche.Bandos = "find";
					chrDisableReloadToLocation = true;//������� �������
					return;
				}
				// <-- �������
				
				if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor.NeedGenerateDuelMan"))
				{
					chr.id = "AffairOfHonor_CoatHonor_Man";
					SetRandNationOfficerModel(chr);
					Characters_RefreshModel(chr); // Jason: ��������� ������ �����������
					// Jason: ������� ��� �� ����� - ������ ����������
					int Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
					int Scl = 35+2*sti(pchar.rank);
					FantomMakeCoolFighter(chr, Rank, Scl, Scl, RandPhraseSimple("blade_12","blade_13"), RandPhraseSimple("pistol6","pistol5"), "bullet", Scl*3);
					float Mft = MOD_SKILL_ENEMY_RATE/20;
					chr.MultiFighter = 1.0+Mft; // ������������
					chr.dialog.filename = "Quest\ForAll_dialog.c";
					chr.dialog.currentnode = "AffairOfHonor_CoatHonor_4";
					LAi_SetWarriorType(chr);
					LAi_SetImmortal(chr, true);
					DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor.NeedGenerateDuelMan");
				}
			}
		}
		//==> ���������� ������� �� �� � ������ ������� ����
		else
		{
			//���� � ������� ��� ���� ���-��, �� �� ������� �� �� �� ������ ����
			for(int n=0; n<MAX_CHARACTERS; n++)
			{
				if (characters[n].location == pchar.location && characters[n].id != "Blaze")
				{
					return;
				}
			}
			//��������� ������� �� ������ ����				
			int iLocIndexEnc;
			if (pchar.location.locator == "reload1") iLocIndexEnc = reload_cur_location_index;
			else iLocIndexEnc = reload_location_index;
			int iEnc = GetCharacterIndex("HouseWoman_"+iBaseCity+"_"+iLocIndexEnc);
			if (iEnc != -1)
			{
				ChangeCharacterAddressGroup(&characters[iEnc], loc.id, "barmen", "stay");
			}
			else
			{
				iEnc = GetCharacterIndex("HouseMan_"+iBaseCity+"_"+iLocIndexEnc);
				if (iEnc != -1)
				{
					ChangeCharacterAddressGroup(&characters[iEnc], loc.id, "barmen", "stay");
				}
			}
			
		}
	}
}

//���������� � �����������
void CreateInsideResidenceEncounters(aref loc)
{	
	bool bOk;
	if (CheckAttribute(loc, "MustSetReloadBack"))
	{ //���� ��������
		if (loc.id.label == "TownhallRoom" || loc.id.label == "Townhall")
		{
			bOk = CreateQuestResidenceNPC(loc);
			if(!bOk) 
			{
				CreateResidenceNpc(loc);
			}	
		}	
	}
	else
	{ //���� ��������� �������
		if (loc.id.label == "TownhallRoom")
		{
			bOk = CreateQuestResidenceNPC(loc);
			if(!bOk)
			{
				CreateResidenceNpc(loc);
			}	
		}	
	}
}
//��������� � ������ ����
void CreateResidenceNpc(aref loc)
{
	ref chr;
	int Rank;
	string sModel, sSex, sAni, sNode, sGreeting;
	bool bWeapon;
	int iBaseCity = FindLocation(loc.fastreload + "_town");
	if (!CheckAttribute(&locations[iBaseCity], "houseEnc")) return;
	if (rand(10) > 8) return; //���� �� ������ �������
	if (CheckAttribute(pchar, "questTemp.FMQT.Common")) return; // Addon-2016 Jason, ����������� ���������� (���) �������
	//==> �������� ���
	int iEncType = rand(3); //0 - ����, 1 - �������, 2 - ������.
	if (loc.id.label  == "TownhallRoom") iEncType = 2;
	if (CheckAttribute(loc, "Bedroom"))  iEncType = 0;	
	if (CheckAttribute(loc, "PlayHall")) iEncType = 1;	
	int iNation = GetCityNation(loc.fastreload);
	if (iNation == PIRATE) return; //��������� ���������� ��� �� �����
	switch (iEncType)
	{
	case 0:
		Rank = 3;
		sModel = "women_"+(rand(5)+1);
		sSex = "woman";
		sAni = "towngirl"
		bWeapon = false;
		sNode = "ResWoman";
		sGreeting = "bedroom_lady";
		break;
	case 1:
		Rank = 5;
		sModel = "barmen_"+(rand(15)+1);
		sSex = "man";
		sAni = "man"
		bWeapon = true;
		sNode = "ResMan";
		sGreeting = "worker";
		break;
	case 2:
		Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
		sModel = "sold_"+NationShortName(iNation)+"_"+(rand(7)+1);
		sSex = "man";
		sAni = "man"
		bWeapon = true;
		sNode = "ResGuard";
		sGreeting = "soldier_guard";
		break;
	}
	//==> ������� ������
	string slai_group = GetNationNameByType(iNation) + "_citizens";		
	string sName = "EncResidence_" + iBaseCity + "_" + loc.index;
	if (GetCharacterIndex(sName) > 0) return; //���� ����
	chr = GetCharacter(NPC_GenerateCharacter(sName, sModel, sSex, sAni, Rank, iNation, 1, bWeapon, "citizen"));
	chr.dialog.Filename = "ResidenceEnc_dialog.c"; 
	chr.dialog.currentnode = sNode;
	chr.CityType = "citizen";
	chr.city = loc.fastreload; //���
	chr.greeting = sGreeting;
	ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
	LAi_SetOwnerType(chr);
	LAi_group_MoveCharacter(chr, slai_group);
}

bool CreateQuestResidenceNPC(aref loc)
{
	bool bOk;
	if(CheckAttribute(pchar,"questTemp.ReasonToFast"))
	{
		if(!CheckAttribute(pchar,"questTemp.ReasonToFast.GenerateLakey") && (pchar.questTemp.ReasonToFast.chain == "A1"))
		{
			// ������� �����
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther")) return false;
			bOk = ReasonToFast_CreateResidenceNPC(loc);
			if(bOk) 
			{
				pchar.questTemp.ReasonToFast.GenerateLakey = true;
				return true;	
			}
			else return false;	
		}
	}
	return false;
}

//���������� �� ����� ����� � ��������
void CreateSkladInsideEncounters(aref loc)
{
	if (CheckAttribute(loc, "packhouse") && !IsLocationCaptured(loc.id))
	{
		ref chr;
		int iNation = GetCityNation(loc.fastreload);
		string slai_group = GetNationNameByType(iNation) + "_citizens";		
		string sName = "SkladMan_"+reload_cur_location_index;
		if (GetCharacterIndex(sName) > 0) return; //���� ����
		int Rank = sti(pchar.rank) + rand(6);
		if (Rank < 10) Rank += 10;
		if (Rank > 30) Rank -= 10;
		chr = GetCharacter(NPC_GenerateCharacter(sName, "citiz_"+(rand(9)+1), "man", "man", Rank, iNation, 2, true, "citizen"));
		chr.dialog.Filename = "HouseEnc_dialog.c"; 
		chr.dialog.currentnode = "SkladMan";
		chr.CityType = "citizen";
		chr.city = loc.fastreload; //���
		chr.greeting = "citizen_male";
		LAi_LoginInCaptureTown(chr, false);
		ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
		LAi_SetOwnerType(chr);
		LAi_group_MoveCharacter(chr, slai_group);
	}
}

//������
void CreateJail(aref loc)
{
	if (loc.type == "jail")
	{
		ref sld;
		string LocatorGroup, LocatorName, slai_group, nShortName;
		int i, nSit, iNation, iRank;			
		if(!CheckAttribute(pchar, "isload") && reload_location_index != reload_cur_location_index)
		{
			pchar.questTemp.jailCanMove = false;
		}
		if (CheckNPCQuestDate(loc, "Jail_date"))
		{
			SetNPCQuestDate(loc, "Jail_date");
			LAi_group_Delete("Prisoner_Group"); 
			iNation = GetCityNation(loc.parent_colony);
			slai_group = GetNationNameByType(iNation)  + "_citizens";
			nShortName = NationShortName(iNation);
			iRank = sti(pchar.rank) + rand(4);
			if (iRank < 10) iRank = 10;
			if (iRank > 20) iRank = 20;
			//====> ��������� ������
			sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"JailOff", "off_"+nShortName+"_"+(rand(1)+1), "man", "man", iRank+5, iNation, 2, true, "governor"));
			sld.City = loc.parent_colony;
			sld.CityType = "soldier";
			sld.standUp = true; //�������� � �������� �� �����
 			sld.Dialog.Filename = "Common_prison.c";
			sld.dialog.currentnode = "First_officer";
			sld.greeting = "prisonboss_"+(rand(3)+1);
			FantomMakeCoolFighter(sld, iRank+5, 70, 50, BLADE_LONG, "pistol3", "grapeshot", 30);//�������
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, slai_group);
			ChangeCharacterAddressGroup(sld, loc.id, "sit", "sit1");
			//====> �������
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"JailSold_"+i, "sold_"+nShortName+"_"+(rand(7)+1), "man", "man", iRank, iNation, 2, true, "soldier"));
				sld.City = loc.parent_colony;
				sld.CityType = "soldier";
				sld.rank = iRank;
				sld.Dialog.Filename = "Common_prison.c";
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, slai_group);
				locatorName = PlaceCharacter(sld, "soldiers", "random_free");
				// eddy. ���������, ������ �� ������ ���� ����������� -->				
				if (locatorName == "protector1")
				{
					sld.protector = true;
					sld.protector.CheckAlways = 1; //��������� ������
					sld.dialog.currentnode = "First_protector";
					sld.greeting = "protector";
				}
				else
				{
					sld.dialog.currentnode = "First_soldier";
					sld.greeting = "soldier";
				}
				// <-- eddy. ���������, ������ �� ������ ���� �����������
			}
			//====> �������� �����������
			for (i=1; i<=10; i++)
			{
				if (rand(100)<70)
				{
					sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"Prisoner_"+i, "Prison_"+(rand(4)+1), "man", "man2", 10, iNation, 2, false, "slave"));							
					sld.Dialog.Filename = "Common_prison.c";
					sld.dialog.currentnode = "First_prisoner";
					sld.City = loc.parent_colony;
					sld.greeting = "convict";
					//LAi_LoginInCaptureTown(sld, true);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetActorType(sld);
					locatorName = "prison"+i;
					if (rand(10)>5) 
					{
						LAi_ActorSetLayMode(sld);
						locatorName += "lay";
					}
					else LAi_SetGroundSitType(sld);
					LAi_group_MoveCharacter(sld, "Prisoner_Group");
					ChangeCharacterAddressGroup(sld, loc.id, "prison", locatorName);
				}
			}
		}
	}
}

//�����
void CreateFortsNPC(aref loc)
{	
	if (loc.type == "fort")
	{
		if (loc.id == "Jungle_fort") return;
		int iNation = GetCityNation(loc.parent_colony);	
		if(iNation == -1) return;
		string slai_group = GetNationNameByType(iNation)  + "_citizens";
		if (locations[reload_cur_location_index].type == "jail" && GetNationRelation2MainCharacter(iNation) == RELATION_ENEMY && !CheckAttribute(loc, "loginNpc"))
		{
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			return;
		}
		DeleteAttribute(loc, "loginNpc"); //������� ��������� ���� �� ��������� ��� ��� ������ �� ������
		if (GetNpcQuestPastDayWOInit(loc, "Fort_date") < 2) return;
		if(CheckAttribute(loc, "QuestCapture")) return; // ���� ���� ��������� ���
		ref chr;
		int iCitizensQuantity, iChar, i;
		string locatorName, sType;
		int iColony = -1;
		SaveCurrentNpcQuestDateParam(loc, "Fort_date");
		if(CheckAttribute(loc, "parent_colony")) iColony = FindColony(loc.parent_colony);
		if(iColony == -1) return;		
		arrayNPCModelHow = 0;
		// ������� -->
		if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
		{
			aref solderLoc, st;
			makearef(st, loc.locators.soldiers);
			iCitizensQuantity = GetAttributesNum(st);		
			for (i=0; i<iCitizensQuantity; i++)
			{	
				if(iNation != PIRATE)
				{
					sType = "soldier";
					iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
				}
				else
				{
					sType = "pirate";
					iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 2);
				}
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "soldier";
				chr.RebirthPhantom = true; 
				LAi_CharacterReincarnation(chr, true, true);
				LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //������ ��� �� ���������� ����� �������� �� ������������
				SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // ������ ����
				solderLoc = GetAttributeN(st, i);
				locatorName = GetAttributeName(solderLoc);
				ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", locatorName);
				// eddy. ���������, ������ �� ������ ���� ����������� -->
				if (findsubstr(locatorName, "protector" , 0) != -1 && iNation != PIRATE) 
				{
					chr.protector = true;
					chr.greeting = "protector";
				}
				else chr.greeting = "soldier";
				// <-- eddy. ���������, ������ �� ������ ���� �����������
				LAi_SetLoginTime(chr, 0.0, 24.0);
				LAi_SetGuardianType(chr);
				if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
				chr.dialog.filename = "Common_Fort.c";
				chr.dialog.currentnode = "First time";
			}
		}
		// ������� <--
		// ������� -->
		if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
		{			
			makearef(st, loc.locators.patrol);
			iCitizensQuantity = GetAttributesNum(st);
			for (i=0; i<iCitizensQuantity; i++)
			{
				if(iNation != PIRATE)
				{
					sType = "soldier";
					iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
				}
				else
				{
					sType = "pirate";
					iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 2);
				}
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "fortPatrol";
				SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // ������ ����
				chr.RebirthPhantom = true; 
				LAi_CharacterReincarnation(chr, true, true);
				LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //������ ��� �� ���������� ����� �������� �� ������������
				LAi_SetLoginTime(chr, 0.0, 24.0);
				LAi_SetPatrolType(chr);

				if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					chr.greeting = "town_pirate";
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
					chr.greeting = "soldier";
				}
				PlaceCharacter(chr, "patrol", "random_free");
				chr.dialog.filename = "Common_Fort.c";
				chr.dialog.currentnode = "First time";
			}
		}
		// ������� <--
	}
}

void CreateAmmo(aref loc) // Jason, ���������
{
	if (loc.type == "ammo")
	{
		if (Loc.id == "Jungle_fort_ammo") return;
		ref sld;
		int i, iNation, iRank;			
		if (!CheckAttribute(loc, "Ammo_date") || GetNpcQuestPastDayParam(loc, "Ammo_date") > 2)
		{
			SaveCurrentNpcQuestDateParam(loc, "Ammo_date");
			iNation = GetCityNation(loc.parent_colony);
			string slai_group = GetNationNameByType(iNation)  + "_citizens";
			iRank = sti(pchar.rank)+5+MOD_SKILL_ENEMY_RATE*2;
			// ���������
			sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"AmmoOff", "off_"+NationShortName(iNation)+"_"+(rand(1)+1), "man", "man", iRank, iNation, 2, true, "governor"));
			FantomMakeCoolFighter(sld, iRank+5, 70, 70, "blade_13", "pistol3", "grapeshot", 100);
			sld.City = loc.parent_colony;
			sld.CityType = "soldier";
			sld.standUp = true; //�������� � �������� �� �����
			sld.Dialog.Filename = "Common_Ammo.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "comandante";
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, slai_group);
			ChangeCharacterAddressGroup(sld, loc.id, "sit", "sit1");
			// �������
			for (i=1; i<=3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"AmmoSold_"+i, "sold_"+NationShortName(iNation)+"_"+(rand(7)+1), "man", "man", iRank, iNation, 2, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, 60, 60, "blade_13", "pistol1", "bullet", 50);
				sld.City = loc.parent_colony;
				sld.CityType = "soldier";
				sld.rank = iRank;
				sld.Dialog.Filename = "Common_soldier.c";
				sld.greeting = "soldier";
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, slai_group);
				ChangeCharacterAddressGroup(sld, loc.id, "soldiers", "soldier"+i);
			}
		}
	}
}

int GetCityNation(string _sColony) // boal ����� ������ ����� �� �� ������
{
    int iColony = FindColony(_sColony)
	if (colonies[iColony].nation == "none")
	{
		return PIRATE;
	}
	return sti(Colonies[iColony].nation);
}

/// boal
// �������� ������� �� ������������ � ��� ������� �����������, ���� ����, �� ����� �� ������
bool isLocationHasCitizens(string _locId)
{
    ref rCharacter; //����
	int n, Qty;
	bool bOk = false;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter,Characters[n]);
		if (CheckAttribute(rCharacter, "CityType") && !CheckAttribute(rCharacter, "Merchant.type")) // ������� �������-�����������
		{
            if (rCharacter.location == _locId)
			{
				bOk = true;
				if (rCharacter.chr_ai.type == "patrol")
					PlaceCharacter(rCharacter, "patrol", "random_free"); //������� ��������� � ������ ���������
			}
		}
    }
	return bOk;
}

void ReSitCharacterOnFree(ref chr, string _locId, string sTemp)
{
	int n, k;
	
	n = 0;
	while (!CheckFreeLocator(_locId, sTemp, sti(chr.index)) && n < 10)
	{
	    sTemp = PlaceCharacter(chr, "sit", "random_free");
	    n++;
	}
	
	n = 0;
	while (findsubstr(sTemp, "sit_front" , 0) != -1 && n < 20)
	{    // ���� �� �������� ����� ��������
	    sTemp = PlaceCharacter(chr, "sit", "random_free");
	    k = 0;
	    while (!CheckFreeLocator(_locId, sTemp, sti(chr.index)) && k < 10)
		{
		    sTemp = PlaceCharacter(chr, "sit", "random_free");
		    k++;
		}
	    n++;
	}
}

bool CheckNPCModelUniq(ref chr)
{
	int   i, n;
	bool  bOk;
	string sModel = chr.model;
	
    bOk = true;
	for (i=0; i<arrayNPCModelHow; i++)
	{
	    if (arrayNPCModel[i] == sModel)
	    {
	        bOk = false;
	        break;
	    }
	}
	return bOk;
}

void SetNPCModelUniq(ref chr, string sType, int iSex)
{
	int i;
	
	i = 0;
	while (!CheckNPCModelUniq(chr) && i < 10)
	{
	    i++;
	    CreateModel(sti(chr.index), sType, iSex);
	}
	arrayNPCModel[arrayNPCModelHow] = chr.model;
	arrayNPCModelHow++;
}

