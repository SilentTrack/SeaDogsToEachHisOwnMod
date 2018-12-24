// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "��������, � ������.";
			link.l1 = "� "+ GetSexPhrase("������","��������") +". ��������.";
			link.l1.go = "Exit";
			//����������
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalInPrison")
            {
                link.l1 = "������, � ��� ���������� ������� - ���������� ����������...";
                link.l1.go = "Portugal";
            }
		break;
		
		//����������
		case "Portugal":
			dialog.text = "����������. � ��� ����� ����? � ���� ����������� ������ ������������� ����������� ����-������� ��������, � �� - ������ � ����������� ���������� �����������. ���� �� �������� �������� ��� ��� ����������� ����� ������. ��� ��� ���� �� �������, ����� ��� ������� - ��� ����� ����, � ���������.";
			link.l1 = "� ������ �� ��� ����, ����� ��� �������.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "� ��� ���� ��, ��������� ��������?";
			link.l1 = "��� ����, ����� ������� ���!";
			link.l1.go = "fight";
			chrDisableReloadToLocation = true;
			pchar.quest.InMarigoResidenceOver.over = "yes"; //����� ������
			InterfaceStates.Buttons.Save.enable = false;//��������� �����������
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}
