// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������, " + GetAddress_Form(NPChar) + "?"), "������ ������� �� �������� ������ ��� ������, " + GetAddress_Form(NPChar) + "...", "� ������� ����� ��� �� ��� ������ ��� �������� � �����-�� �������...",
                          "����� ������� ����� ��������?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "������ ��� �� � ��� ��������"), "��, ���-�� � ������� ���� �����...",
                      "�� ��, ������������� � ������ ���...", "�� ���, ����� �������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";						
			//Jason, ����� ��������
			if (CheckAttribute(PChar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "hire" && !CheckAttribute(npchar, "quest.storehelper"))
			{
				link.l1 = "��������, " + npchar.name + ", � � ���� �� ������ ���������� ����. ��� ����� ����� ��������, ������� ����� �� ����� � ��������� ����� �� ������ � �������� ��������� �������� � ������� ���-�����. ��������� �������, � ����� ��� ������� ����������. �� ������ ������������, � ���� ����������?";
				link.l1.go = "storehelper";
			}
			if (CheckAttribute(PChar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "seabattle" && !CheckAttribute(npchar, "quest.seabattle") && pchar.location.from_sea == "LeFransua_port")
			{
				link.l1 = "� �� ������ �������� � �����, ������� �� ����������� ��������� �� ��� ������� ��� �������� �� ���������...";
				link.l1.go = "seabattle";
			}
			//����� ��������
			//Jason, ����������
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalLeFransua" && !CheckAttribute(npchar, "quest.portugal") && Pchar.location.from_sea == "LeFransua_port")
			{
				link.l1 = "������, " + npchar.name + ", � ��� ������ ������ �����. �� ������ ��� �������� ����, � ��� �������������. ��������, ��� �������� ������...";
				link.l1.go = "Portugal";
			}
			//����������
		break;
		
		case "storehelper":
			dialog.text = "��... ���� ��� � ��� ��������� �������, �������� ������� ��������� ������ �� ����� ���������� �����. � ���� ������ ����, �� ����� ������: �� ���������.";
			link.l1 = "���! � ������� �� �� ������?";
			link.l1.go = "storehelper_1";
			npchar.quest.storehelper = "true";
		break;
		
		case "storehelper_1":
			dialog.text = "������ ����. � ���� ������ ������ �� �������� ������ - ����� ��� �������� �������� ����� � ���� � �������, � �� ����. ������� ���������� � ���� � �������, ��� ����������� ������ ������.";
			if (sti(Pchar.money) >= 1000)
			{
				link.l1 = "��-�... �����, ����� ���� ������!";
				link.l1.go = "storehelper_2";
			}
			link.l2 = "��� ����, �� � ���� ��� ����� �����!";
			link.l2.go = "storehelper_exit";
		break;
		
		case "storehelper_2":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "�� ��������� ���, ��������. �������� ���� ����� �������� ���� �� ��������� - � �����, ��� ������ ������ ����� �����, ��-��... ������ ������� ����������� �� ���������. ������ � ��� ������� ����� ��� - � ����� ������� � ��� �������� ������ ���� �����.";
			link.l1 = "������. � ������� ����� ���, " + npchar.name + ".";
			link.l1.go = "storehelper_3";
		break;
		
		case "storehelper_3":
			DialogExit();
			pchar.quest.storehelper1.win_condition.l1 = "Timer";
			pchar.quest.storehelper1.win_condition.l1.date.hour  = sti(GetTime() + 1);
			pchar.quest.storehelper1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.storehelper1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.storehelper1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.storehelper1.win_condition.l2 = "location";
			pchar.quest.storehelper1.win_condition.l2.location = "lefransua_tavern";
			pchar.quest.storehelper1.function = "Storehelper_hire";
		break;
		
		case "storehelper_exit":
			dialog.text = "��� ���� ����, ��������, ��� � ���� �� ���. �� �� ������� ����� ���� �� ��������, ��� ���������. ��� ���...";
			link.l1 = "�������. �� ����� ������������� ���. �����, �����...";
			link.l1.go = "exit";
			pchar.quest.storehelper.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			CloseQuestHeader("SharlieA");
		break;
		
		case "seabattle":
			dialog.text = "�� ��� ������ � ���, ��������? � ����� ���� �� ��������?";
			link.l1 = "���� ������� � ���� ������� �� ����� ������ ������. �� ������, ��� ���� ����� ������� ��� ��������� ������ ���� �� ���������, �� ������ ����� ����. � ��� ���� ����� ������ ��� ������� ��� ���� ������...";
			link.l1.go = "seabattle_1";
			npchar.quest.seabattle = "true";
		break;
		
		case "seabattle_1":
			dialog.text = "��������, �������, � �� ������ �����, � �� �������� � ����� �������, � �������� ������� ������� ����� �� ����.";
			link.l1 = "��� ��� �����! ��� ������, ���� ������ ��� ����� �� �� ����... �� � ���� ����� ��� ��� �������?";
			link.l1.go = "seabattle_2";
		break;
		
		case "seabattle_2":
			dialog.text = "���! ��, ��� ��� �����-�� ������, ��� ������ �����, ���...";
			link.l1 = "��� '���'?";
			link.l1.go = "seabattle_3";
		break;
		
		case "seabattle_3":
			dialog.text = "� ��� �� �������������? ����-�� ������������ �������� ���� � �� �������, � ��� ��� ��� ���� - �� ����. �� ����� ����� � �� ������ �������� �������� ������, �������� ��� ��������� ������������. ��� ���� ����� ������, ��������...";
			link.l1 = "�������, �� ����. ��� ���� ����� ������� ����� �� �����������. �����, �������� ������ ������. �����, ������!";
			link.l1.go = "seabattle_4";
		break;
		
		case "seabattle_4":
			DialogExit();
			AddQuestRecord("Sharlie", "16");
			pchar.quest.seabattle.win_condition.l1 = "location";
			pchar.quest.seabattle.win_condition.l1.location = "Martinique";
			pchar.quest.seabattle.function = "SharlieSeabattle_ship";
		break;
		
		case "Portugal":
			dialog.text = "��, ������� ��� ����, �������. ��� ����� �������, � ���� ������� �������. � ������ ��� �����, ��-��... ��� �����, � ��� � ��������!";
			link.l1 = "...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			DialogExit();
			AddDialogExitQuestFunction("Portugal_enterPirates");
			npchar.quest.portugal = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

