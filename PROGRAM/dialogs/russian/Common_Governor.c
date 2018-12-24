// boal 25/04/04 ����� ������ Governor
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // ����� ������� �� ������� -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(sti(NPChar.nation)) + "_Governor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // ����� ������� �� ������� <--
    
    ref offref, sld;
    int i, cn;
    int qty;
    int iSumm;
    string attrLoc;

    /// ����� �������
    ref CaptGovenor, FortColony;
    int f, colony_money;

    int k = 1000;
    if (CheckAttribute(Nations[sti(NPChar.nation)], "Fort"))
    {
        k = (300 - sti(Nations[sti(NPChar.nation)].Fort)*10);
    }
	bool ok;
	
	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // ����� � �����
 	    Dialog.CurrentNode = "ColonyGive";
 	}
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("�� ������� ������� � �������-�����������?! ������ ���...", "��� ��� ����������� ���������, ����� �� ��� �������� ����?! ��� �����������...", "�� ��, ��� ������ ��������� �����, ��� "+ GetSexPhrase("�����-�� ����������","�����-�� �����������") +" ������ � ���� ����������..."), 
					LinkRandPhrase("��� ���� �����, "+ GetSexPhrase("�������","���������") +"?! ��� ������� ��� ����� ���� ����, ������ ���� �� ����, "+ GetSexPhrase("������� �����","��������") +"!", ""+ GetSexPhrase("�������","�������") +" ������, ��� �� ���� ����������! ������!!", "� �� ����� ����, "+ GetSexPhrase("��������","��������") +"! ����� ���� ������� � �����, ������ ���� �� ����..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("�������� ���� ���� �����...", "�� ���� �� �� ��� �� �������."), 
					RandPhraseSimple("������ ���� �����, ��������, � �� �� ����� ���� ������� ����!", "��� ��� � ���� �����, ��������: ���� ����, � ������ ����..."));
				link.l1.go = "fight";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "� ������, ��� �� ����� ���������� ������� ���������. ���� ����� " + GetFullName(npchar) +
                              ". � �������-���������� ������� " + NationNameGenitive(sti(NPChar.nation))+ ", ��������� ������ " + NationKingsName(npchar)+
                              " � ���� �����. � ������ ������������� �������� ���� ������ ������, " + GetAddress_Form(NPChar) + ".";
				link.l1 = "��� ��� " + GetFullName(pchar) + ".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple("�, ��� ����� ��? �� ������ ������� ��� ����������� �������-���������� " + NationNameGenitive(sti(NPChar.nation))+ " �� ���� ���?",
                              "����� ��������� ���� �� ������ ��������������� ���? ��� ��� ������, " +GetAddress_Form(NPChar)+"?");
				link.l1 = "� ���� ���������� � ������ �� ����� ������ " + NationNameGenitive(sti(NPChar.nation));
				link.l1.go = "work";
				link.l2 = "����� ���������� � ���� �� ����� ����.";
				link.l2.go = "quests"; // ���� �����
				//Jason --> ������
				if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
				{
					link.l3 = "� ������ �� ����������� ��� ������� � ������. ��� ��� �����������.";
					link.l3.go = "Regata";
				}
				//<-- ������
				link.l10 = "����� ��������, �� ���� ���� ����.";
				link.l10.go = "exit";
			}
		break;
		
		case "node_1":
			dialog.text = "��� ����� ������� ��������� ��� ������ ���� � ��������� ���� �� ������ ��������������� ���?";
			link.l1 = "� ���� ���������� � ������ �� ����� ������ " + NationNameGenitive(sti(NPChar.nation));
			link.l1.go = "work";
			link.l2 = "����� ���������� � ���� �� ����� ����.";
			link.l2.go = "quests";
			//Jason --> ������
			if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
			{
				link.l3 = "� ������ �� ����������� ��� ������� � ������. ��� ��� �����������.";
				link.l3.go = "Regata";
			}
			//<-- ������
			link.l10 = "��� ������ ����� ���������� � ������ �����, "+GetAddress_FormToNPC(NPChar);
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = "� ����� ������, � ������� ��� �������� ��� ������� � �� ������ ��� ��������.";
			link.l1 = "��, ��, �������, ��������, ��� ����������"+ GetSexPhrase("","�") +" ���.";
			link.l1.go = "exit";
		break;
		
		case "work":
            dialog.text = "�� ������ ������ ����������� � ������������ �������. �� ��������� ��������� ��������� � �������� ��������.";
			link.l1 = "����� � ��������. �������.";
			link.l1.go = "exit";
		break;
		
		//--> Jason ������
		case "Regata":
			dialog.text = "�-�, ������������, ��� ��� ������, �������! �� ������ �������, ������ �������� ����� ��������� ����. �� ������ � �������� ������ � ������, ���������� ��� ��������?";
			link.l1 = "��, ���, ������.";
			link.l1.go = "Regata_1";
			RemoveItems(PChar, "letter_open", 1);//������ ������
			TakeNationLicence(HOLLAND);//������ ��������
			DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		break;
		
		case "Regata_1":
			dialog.text = "����, �� ����������� 50 000 ���� - ����� � �������� ����?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "��, �������. ���, ������� ��� �����.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "� ���� ������ ������������ �����. �� � ����������� ������� ��.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "����� ������. ���� �� �������� - ���� ������ �������� � ���, ������ � ����������� �������. ������ ��� ����� ������� ������������ � ��������� ������\n��� ����������� ������� � ���� ����� ����������, �� ������ ���������� � ������� ����������. �������� � ���� - �� ��� ��� ��������.";
			link.l1 = "������. � ��� � ������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "������. �� ������ �� ����������� � ����, �������. ������ ����� ����� ��� �����.";
			link.l1 = "� �������. ���� � ��� �� ������, � ��������, ��� ����� ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//������-�����
		case "Regata_Final":
			dialog.text = "�, ��� � ���������� ������! ������ ����, ������� " + GetFullName(pchar) + "! ���������� ��� � ���� ������������ ������� - ���������� ����� ������ ������ ���������� ����������� ������������� � ���������� ��������. ";
			link.l1 = "������� �� ������������, ���!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "������ �������� � ����� �������� ��� ��� ����� - ��������� �������. ����, �������� �������������� �� ������ ���������� 250 000 ����. �������� ��������!";
			link.l1 = "���������!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			int iGift;
			string sItem1, sItem2, sItem3, sAdd;
			if (sti(pchar.rank) < 6) iGift = 0;
			if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 13) iGift = 1;
			if (sti(pchar.rank) >= 13 && sti(pchar.rank) < 20) iGift = 2;
			if (sti(pchar.rank) > 20) iGift = 3;
			switch (iGift)
			{
				case 0:
					sItem1 = "blade_10";//����
					sItem2 = "cirass6";
					sItem3 = "bussol";
					sAdd = "����, ����� ������� � �������";
				break;
				
				case 1:
					sItem1 = "blade_15";//��������
					sItem2 = "cirass2";//���������� �������
					sItem3 = "bussol";
					sAdd = "��������, ���������� ������� � �������";
				break;
				
				case 2:
					sItem1 = "blade_17";//������
					sItem2 = "cirass7";//��������
					sItem3 = "bussol";
					sAdd = "������, �������� � �������";
				break;
				
				case 3://
					sItem1 = "blade_20";//�������
					sItem2 = "cirass2";//���������� ������
					sItem3 = "bussol";
					sAdd = "'�������', ���������� ������ � �������";
				break;
			}
			GiveItem2Character(pchar, sItem1);
			GiveItem2Character(pchar, sItem2);
			GiveItem2Character(pchar, sItem3);
			dialog.text = "����� ��� ������� �������� ������ ������: "+sAdd+". ������ ��� ��� - ����.";
			link.l1 = "����� ���, ���. �����, ���� �� ������.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "�� ���� ���� ������� ���������� ������� ��������� ��� �� ������� � ������, � ��� ��� ���������� � �������! ���� �� ������� ������ - ����� ����� ����� � ���� ����� ���������� � �������� ���� �������, ���� �� ����� ��� �� �������. ����� ��� �����, �������!";
			link.l1 = "������� �� ������ �����, ���! � ���� ������� ��������� ��� �� ��, ��� ���� ��� ����������� ����������� � ���� ������������ �����������. � ������ ��������� �����������.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- ������
	}
}