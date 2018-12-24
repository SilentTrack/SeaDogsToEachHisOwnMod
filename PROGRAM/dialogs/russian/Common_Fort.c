// boal 25/04/04 ����� ������ ������ �����
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // ����� ������� �� ������� -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Fort\" + NPChar.City + "_Fort.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // ����� ������� �� ������� <--
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // �����
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":			
            NextDiag.TempNode = "First time";
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("�����? ����� ������!! ��������� �� ����!", "��������� �����!! ���������� �������� �"+ GetSexPhrase("��","�") +"!");
				link.l1 = RandPhraseSimple("��������, �����������!", "��� �� �� ���!");
				link.l1.go = "fight"; 
			}
			else
			{
				// eddy. ���������, �� ������� ��. -->
				if (GetRelation2BaseNation(sti(npchar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple("��� �� � ��� ���� ����� �����?", "����! ��� ��? �� ����� ��������� ��������� ����� � ����?");
					//==> �� ��������
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "������, � ���� ������� " + GetRusNameNationLicence(sti(npchar.nation)) + ", ��� ���, � �������� ����� �� �������� ����������. ����� ������������...";
						link.l1.go = "LicenceOk";
					}
					else
					{
						//==> �� �����
						// �������� �� ������
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("������ � �����?! ����� �"+ GetSexPhrase("��","�") +"!!", "��� �����, ��"+ GetSexPhrase("","�") +" ���������� ����� ���-��!! ����� �"+ GetSexPhrase("��","�") +"!!!");
							link.l1 = RandPhraseSimple("��, �����, �� � ���?..", "���, ���������� ��������...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //���� �������� � ������
						{
							link.l1 = "�� ���, �� ������, ��� �� ����� ����� ������� ����������� ����" + NationNameGenitive(sti(pchar.nation)) + "?!";
						}
						else //���� �������� �� � ������
						{
							link.l1 = "� ������ ����� � " + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + " ��� ������ " + NationNameGenitive(sti(pchar.nation)) + ". ��� ���� ��� �� ����?";
						}
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
						{
							link.l1.go = "PegYou";
						}
						else
						{
							link.l1.go = "NotPegYou";
						}
					}
				}
				// <-- eddy. ���������, �� ������� ��.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn)) // ��� ���������
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "��, �������, ��� ������ ���� � ���� � ����! ������� �������� �� �������� ��� ����� ��������! � ���...";
									link.l1 = "� ���, ���� ���, ����� ���� ��������� �������� �������������� �������, ������� � ���� �� ������.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "�������, �� ��� ����� ���������?! �� ���� �� ���������� �����!";
									link.l1 = "��������, �����! �� �� ������ � �������� �����, ��� ��� �� �����.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "��� ��� � ����, �������? �� �����-������ ����� ������ ���?";
									link.l1 = "�������, ������! ��������� � �������, ������� �� ���� � ������������� ����� ������� ������.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "����� ������������, �������: �� ��� ��������� ����� � ����. ��� ������ �� ���� ������ ������� ����� �����!";
									link.l1 = "� �����"+ GetSexPhrase("","�") +" �� ����� �����! ������� ��� ������� � �� �����! ����� ���, ��� ���� ��������"+ GetSexPhrase("","�") +" �������! � �� ���-���� �������� ��������� ��� �������.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "����� ��� �� �������, �������, ����� ���������� - ��������� � ���������. �� ���, �������, �� ��� ����";
									link.l1 = "�� ����, ������: ���� ���� - ������ �� ����� � ������� �� ��������. �� � ��������� ����������� �� ��� ��� - ��� ��� ������� ��� ����. �������!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "�������, ��� �� ��������� � ��� �������! �� �� ��� � � ����� � � ����!";
									link.l1 = "���� � ���, �����������! ������ ������ ������. ������� � ������� �������, � ������. �� ������ ���������.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "��, �������! ��, ����� �� �������� ���������� �������?! ��� ����� �� �� ���� � ��������� ����!";
									link.l1 = "�� ������������, ������! ��������� ������ ����� ������ ����� ��������, ��� ��� �������� ���� ����� ������������ � ����� ������.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "�������, �������, ����������� ������ ����� �������� ���� �������?";
									link.l1 = "�������, ������. ���� �� ����, ���� �� ����� �������. ���� � ��� ��� �������� ��������� � �������!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "��-��-��! ����� ������� ����� � ��� ���� �������, �������! �����, ��� ��� �� ����.";
									link.l1 = "������, � ���� ��� ���������. � ���, ������, � �� �������.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "����� ��� �� �������, �������, ��������� �� ��� ������� �� �������, �������� �� ����� � �������� ����� ���� �������...";
									link.l1 = "��, ������, ������ �� ��� �����!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "���! ���������� �� ���� �� ���� ��������� ����������! ��, �� ���� � ����� ���������� ������� �����������!";
									link.l1 = "�� ����� �������: ������ ����� �� ������� ������ ���� �������. ������, ����, ��� ����� ������.";
									link.l1.go = "exit";
								break;
							}
							link.l2 = RandPhraseSimple("���� ������ ����!", "� ���� � ���� ����.");
							link.l2.go = "quests";//(���������� � ���� ������)
							break;
						}
					}
					
					//Jason --> ����-����� ���������� �����
					if (!CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && sti(pchar.rank) < 4 && !CheckAttribute(pchar, "questTemp.Wine") && npchar.location.group == "soldiers")
					{// Addon 2016-1 Jason ��������� �������
						if (npchar.location.locator == "protector1" || npchar.location.locator == "protector2")
						{
							dialog.text = "��, �������! �� ������� ��� ��������� ������?";
							link.l1 = "��, ������ � ��� ���������.";
							link.l1.go = "Wine_soldier";
							link.l2 = "������� ���.";
							link.l2.go = "exit";
							pchar.questTemp.Wine = "true";
							break;
						}
					}
					// <-- ����-����� ���������� �����
					
					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "�� ������, � �� �����! �� �������� ����.";
							link.l1 = "������, ������...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "�� ������ �������� ��� � ���-�� ��������������?";
							link.l1 = "���, ������ ������, � ���� �� � �������. ����, �� ��� �� ��������? ������.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "�������, ��� ������� ������! ��� ��� ���� ���� ����� ����.";
							link.l1 = "������, � ����� ��� � ��������.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "����� ������, � � �������� ������ �����. ��, � ������� ���� ������� �����, � ����� ������ ����������� ����� ������...";
							link.l1 = ""+ GetSexPhrase("����������. �� ����� �� ���� ������, ������ � ���� �����.","��! � � ��� - �� �������?") +"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "���� ��� ������� ���������, �� ������� ���� ����-������ �������, � � ������ ������� �� ��������, � ��� ������� ������ � ���� ������.";
							link.l1 = "�� ���, � ������ "+ GetSexPhrase("��������","���������") +", ��� �� �� ���, � �� ������, ��� ������.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "��� �� �������, ����������� ����� - ��� �������? ��� �� �� ���! ��� ����� ������������� � ������� ����. ��� ��������...";
							link.l1 = "���������� ���� ������� ���-������ � ������ ���, � ������ � �����.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "���������� �����, ��� ����! ���� ���� ���� ����...";
							link.l1 = "��� �������, ������.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "��! ��� �� � ���� ����? ������ �� �����.";
							link.l1 = "���, ��������, �������...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = ""+ GetSexPhrase("��, � ����� �� � ���������, ������ ���� ����������� ������� ����� ����! � ��� ��������� �������� ������...","��, ���������! ��� ������ ����, ����� ������� ������������ � ������ ������?") +"";
							link.l1 = ""+ GetSexPhrase("� ��� ���������� '����� ������'? ������, ����������� ������-������ ���������!","��� ���� �� �������� �������... � ����� �������.") +"";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+ GetSexPhrase("�� ��������� ������� ������! �� ������ ��������� �� ������ � �������� �����? � ��� ���������� �������, ����������� �������, ���� ������� ���������.","�, �� ���� �� �������������, �������, ��������� ������� ��������� � ���� ���������� ����� ����� �����, ��� ��!") +"";
							link.l1 = ""+ GetSexPhrase("��������������, ���� ������, �� � �������� ����������. ����������� ������ �� ��� ����","������� �� ����������, ������") +".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "��� ����... � �� �������� �����, ����� ����� ��������� � ������.";
							link.l1 = "��, ������, ��� �������� ������� �� ��������� �� �����.";
							link.l1.go = "exit";
						break;
					}
					link.l3 = "�-��... ����. � ��� ��� "+ GetSexPhrase("�����","������") +" ��������...";
					link.l3.go = "quests";//(���������� � ���� ������)
				}
			}
		break;
		
		//Jason --> ����-����� ���������� �����
		case "Wine_soldier":
			dialog.text = "���������, � �����-����� ���� ����... �� �� ��� ����� �������� ������� �� ������ �������, �� ��� ���� �� �������, � ��������� ���������� ������������ ����. ��� ����� ������� � ������ � ���������. ����� ��� ��������, �� � ������� ������, � ������� ��� ����� ���� ����� ����. ���������?";
			link.l1 = "� ���� ��� ������� �� ������? ���������� �����, � ��� �������, � �� ���� �������������... � ��� ������-��?";
			link.l1.go = "Wine_soldier_1";
		break;
		
		case "Wine_soldier_1":
			dialog.text = "�������� ������� ���. ������ � �� ���� ���������� �� ����� � ����� - ������, ��������� ��, � � ���������� ��� �� �����. ����� ����, ��� �������� ��������� ��������� ����������� �������� � �����, ���� �� ��� ������. �� ��� ���, �������� �������?";
			link.l1 = "� ������ �� � ���? ������� ���� ���� ����, ����� ��������� � ���� ����.";
			link.l1.go = "Wine_soldier_2";
			link.l2 = "������, ��������, �� � �� ���� ���� ��������. ����� ���� ������� ���������.";
			link.l2.go = "exit";
		break;
		
		case "Wine_soldier_2":
			dialog.text = "��� � ������������, ������� ����! ������� � � �������, ��� ��� ������� ������. ������� ���� �� ����� ������� �������� �����. ��� ��������� � �������� ���������...";
			link.l1 = "������. ���, ������ ������ ����.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.id = npchar.ID;
			pchar.questTemp.Wine.SName = GetFullName(npchar);
			pchar.questTemp.Wine.bottle = "true";
			npchar.lifeday = 5;
			SetFunctionTimerCondition("Wine_Exchange", 0, 0, 1, false);
			pchar.questTemp.Wine.City = GetCityNameByIsland(LoadedLocation.islandId);
			Log_TestInfo(pchar.questTemp.Wine.City);
			SaveCurrentQuestDateParam("questTemp.Wine_bottle");
			AddQuestRecord("Wine", "0");
		break;
		// <-- ����-����� ���������� �����
		
		//============================== ���� �� �������� ��� ������������� =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("������� ���, ��� ��� �����... �����-�� ������� � ����������, �����"+ GetSexPhrase("���","����") +", ��� ����������...", "��, ���-�� ������������ ���, ��� �� �� "+ GetSexPhrase("���","��") +", �� ���� ���� �������... ���������� ���� ������, " + GetAddress_Form(npchar) + ", � ������ �� ���� ��� ����������� ���������������!");
			link.l1 = RandPhraseSimple("��� �� �� ���!", "����� ��������, � �������...");
			link.l1.go = "fight";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple("�-�-�, ����... ��� � �������, �� ������ ����, " + GetAddress_Form(pchar) + ".", "���-�� � ������� �������� � �������... ��� � �������, " + GetAddress_Form(pchar) + ", ����� ��������.");
			link.l1 = "���-��!";
			link.l1.go = "exit";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "������ ��������, ����� ��������! ������� ���� ��� ����� ��������! �� ���� �������� ��������� � ������ �������, �������! ��, ������ �� �� ������! ������ ���!";
				link.l1 = RandPhraseSimple("����!..", "��, �� ���� �����������...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //���� �������� �� � ������
			{
				dialog.text = "�� ������� ���� ���������? ��������� �������� - �� ���? ��� ��� �������? ��� ��� ����� ������������� - � �������� ��� ��������� �� ���������. ������ ������ � �������� �� ����!";
				link.l1 = RandPhraseSimple("��� �� �� ���!", "����� ��������, � �������...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "���� �������� �������� �������, ��� ��� ���������� � ������� ���������������. ������ ������ � �������� �� ���� ��� ����������� ��������������!";
				link.l1 = RandPhraseSimple("��� �� �� ���!", "����� ��������, � �������...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "��, ��� �����. ������ ������� ���� ��������, ��� ���� �������� ����� �������� ������� ��������. � ������� ��� ������, �� ��� ����� ����� �������� ����� ��������.";
				link.l1 = "�������, � ������ ��� ��� ������ �� �����������.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "��, ��� �����. ������ ������� ���� ��������, ��� ���� �������� ����� �������� ������ �������� - ��� ������������� ��� ������ " + FindRussianDaysString(iTemp) + ". ��� ��� ������ � ����, " + GetAddress_Form(npchar) + ".";
				link.l1 = "�������, � ���������� ����� ��� ������ �� �����������.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("�� ��� ��, ����� ������, ���� �������� ��������� ��� " + FindRussianDaysString(iTemp) + ". �� ������ ������.", "��� ����, "+GetAddress_Form(npchar)+". �� ������ �������� ��������� � �����, ���� �������� ��������� ��� " + FindRussianDaysString(iTemp) + ". ����� �������� �� ������������.", "��� � �������, " + GetAddress_Form(npchar) + ", �� ���� ��� �����������.");
				link.l1 = RandPhraseSimple("�������. ����� ��������.", "�������, ������.");
				link.l1.go = "exit";
			}
		break;

		//��������� �� ����������� ������
		case "SoldierNotBlade":
			dialog.text = LinkRandPhrase("������ ����� �� ������� �� ������ � ���������� �������? ���������� ����� ������!", "���������� ��� ���������� ������ ������ � �����!", "��, "+ GetSexPhrase("��������","�������") +", �������� ������ �����! ����� ������ � �����.");
			link.l1 = LinkRandPhrase("������.", "�����.", "��� �������...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("����� � ���!", "��������...", "����� ��������, � �������.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
	}
}