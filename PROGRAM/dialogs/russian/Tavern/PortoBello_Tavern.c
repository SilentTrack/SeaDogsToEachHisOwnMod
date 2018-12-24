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
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "��������, �� ����� �� �� ������ �� ����� ������� �������? �� ������� ��� � ����� ������.";
                link.l1.go = "Portobello_rat_1";
            }			
			// ��������� �����
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && !CheckAttribute(npchar, "quest.trial"))
            {
                link.l1 = "��������, �� ����������, ��� ����� �������� �� ����� ����� �������? �� ����� ��� � ��� ���������...";
                link.l1.go = "trial";
            }
			// Addon-2016 Jason ���-���������
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && !CheckAttribute(npchar, "quest.FMQG"))
            {
                link.l1 = "��������, � ��� �������� �� ����� ������� ������, �� ������ � �����? �� ������� ������ � �����-�����. �������� ����� ��������, ��������, � ������ ��������. �����, ������� � ����...";
                link.l1.go = "FMQG";
            }
		break;
		
		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("���, �� ����. � ������� �� �� �������, �� � � ������ � ��� �� �����.", "�� ��� "+ GetSexPhrase("���������","����������") +" �� ����, � ���� �������.", "� �� ������ ����, �� ��� "+ GetSexPhrase("���������","����������") +" �� ���� ��������.", "��������, ������ � �� �����! ������ ��� �� ����� �������?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�� ��� ��, ����� ������.", "��, �� ��...", "��, �����, "+ GetSexPhrase("���������","����������") +"...", "������, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;		

		case "trial":
			dialog.text = "������ ����� �������? �, ���� ����������� ��������� ����� �������� � ����� ������, �������� � ��������� ���� ����! �������� �������, � ������ ��������, ������� �������� ��� � ����... ������ ������! ��� �� ������ ����� �������!";
			link.l1 = "...";
			link.l1.go = "exit";
			npchar.quest.trial = true;
			AddDialogExitQuestFunction("Trial_TavernEnterSoldiers");
		break;
		
		// Addon-2016 Jason ���-���������
		case "FMQG":
			dialog.text = "������ �� ������ �� ���� ���������, ��������.";
			link.l1 = "�� �������� ���� ������� �� �������. ����� ������ �� ����������?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "���. ��� ���� ��� � ����� �� �������� ������ - ��� �� ����� � ����������� � ������� � ������� � �������� ��������. � ���� � ���������� � ����� ��������.";
			link.l1 = "�������, ��� � ������. ������� �� �����!";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "9");
			npchar.quest.FMQG = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

