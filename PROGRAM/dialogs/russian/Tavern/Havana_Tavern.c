// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("��� ������� ������ "+ GetCityName(npchar.city) +" � ����� �������. ��� �� �� ������ ������?",
                          "�� ������ ��� ��������� ��� ����. ��, ��������, ������������...", "������� �� ��� ������ ��� �������� � �����-�� �������...",
                          "��� �� "+ GetSexPhrase("�������","��������") +" ��� ������� ���� � �� ��...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("������, " + NPChar.name + ", ���-������ � ��������� ���.", "�����, "+ GetSexPhrase("�����","������") +" ���-��...",
                      "�� ��, ������������� � ������ ���...", "�� ��...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Slavetrader") && pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "��������, �� ��������� �� � ��� � ������ ������� �������? � ���� ������ '" + pchar.questTemp.Slavetrader.ShipName+ "', ���� ���... ";
                link.l1.go = "Havana_ratT_1";
            }
			if (CheckAttribute(npchar, "quest.batabano"))
            {
                link.l1 = "�����, ��������, ��� ��� ����� ���� ����� �� �������? � �������? �� ��� ������ �� ����?";
                link.l1.go = "guardoftruth";
            }
			// �������
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "��������, � ��� � ����� �� �������� ������� �� ����� ������ ��������? ��������� ������, ����������, ����� ��� � ����������, � ������������� ��������?";
				link.l1.go = "caleuche";
			}
		break;

		case "Havana_ratT_1":
			dialog.text = "�-�, ���� ������� ���? ��, ������� �� �� ���, ��������������. ����� ���� �� �������: �� ����� �� ����� � ������ ���� ����� �� ������. ������� ����������� �� ��������� �������. �� ���-�� ��� � ���� �� ��������, � �� ������� �����.";
			Link.l1 = "� ���� �� �������, �� � �����? � �� ��� ��� � ������ ����� ����� ������, �� ��� ����� ����� �� ����������.";
			Link.l1.go = "Havana_ratT_2";
		break;
		
		case "Havana_ratT_2":
			dialog.text = "� ����� �� ����? �� ������� ������ - ����� �������� ��� ����, ��� ������ ������������ ���������� - �� ����� ���������. ����� ������ � ������������� ������� ����������. �� �� ���� �� �� ��� ���������?";
			Link.l1 = "�������, �� ��� �� ��� �� ��������� �����! � ���, �����"+ GetSexPhrase("","�") +" �� �����"+ GetSexPhrase("���","��") +" ������? �� ��� ��������, � ����� �������� ��� �������, ������� ��� ������ � ������ ��������, �� � �� ���� ��� ��� ��������� - ����� ��� �� ����.";
			Link.l1.go = "Havana_ratT_3";
		break;
		
		case "Havana_ratT_3":
			dialog.text = "�� ����? ��-��-��! �� ������ �� ���� �� ��� ������� �� ������ � �������� �� ���� ����� ����� ���������� ����������... ��, �� �� ������ ������, ������, �� ����� � ������� ��������. � �� ��������...";
			Link.l1 = "�����. ��������, ������� ������� �� ������ ��� ����������. ��� ������, ������� ������ ������� �� �������� �������. ��� ���� �� ����������?";
			Link.l1.go = "Havana_ratT_4";
		break;
		
		case "Havana_ratT_4":
			dialog.text = "��, ����� ���� ��� ��� ���� � ��� �� ����� �������, �� ������, ��� � ������������, ����� �����������������, ��������. �� ������� �� ����������... ���-�� �� ��� ��� ��������� ���� ��������, �� � ��� � �� ����� ������.";
			Link.l1 = "�� �������, ������? �������! �������, ���� ��� � ��� ������. ������� ����, " + npchar.name + ", �� ��� ������� �����. �����.";
			Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_7");
			pchar.questTemp.Slavetrader = "FindRatTortuga";
			pchar.quest.Slavetrader_findTortugaRat.win_condition.l1 = "location";
            pchar.quest.Slavetrader_findTortugaRat.win_condition.l1.location = "Tortuga_HouseHut";
            pchar.quest.Slavetrader_findTortugaRat.win_condition = "Slavetrader_findTortugaRat";
		break;

		case "guardoftruth":
			dialog.text = "��... � � ���� �� ��� �������� ���������������� ����� �����, �?";
			link.l1 = "��, ��� � ������� - �������� �� �����. � ����� �������� ��� ��� �������, ����������� ������������. ������... ������ ���������? � ���� ��� ����� ������� ������.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "�-�, ��� �� ��������� �� ��� �������������� ���� ��������? �������, ��� ������ ����. ��� ����� �� ������� ����� � ������� ������� �� ���� ��� ��� ��� �����, ������ ������ �������� � ���� �� ���������� �������. ���� �� �������� ������� ��������� ����� �� ���� ���-�� � ����� ����������� ����, ��� �� ������� ����� � ������ ��������� ��� �������, ��� ������ �������\n��� ��� ������� ���������� � ����� �� ��� - ��� ������ ���� � �������, � ��� ��� �����. �� �����, ��� ��� ������ ��� ������ �������� ��������.";
			link.l1 = "�������, ��������! �� ��� ����� �����!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "�� �� �� ���, �����������. ������ ��� ������ �������-��������.";
			link.l1 = "...";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			DialogExit();
			DeleteAttribute(npchar, "quest.batabano");
			AddQuestRecord("Guardoftruth", "47");
			pchar.quest.GuardOT_Batabano.win_condition.l1 = "location";
			pchar.quest.GuardOT_Batabano.win_condition.l1.location = "Shore13";
			pchar.quest.GuardOT_Batabano.function = "GuardOT_SanAntonioPrepare";
		break;
		
		// �������
		case "caleuche":
			dialog.text = "���� ��� �����, �������. �����, � ��������, �� ��� ������ � � ��� ������ �� ����. �� ������.";
			link.l1 = "����. ����. ���� ������ ������...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

