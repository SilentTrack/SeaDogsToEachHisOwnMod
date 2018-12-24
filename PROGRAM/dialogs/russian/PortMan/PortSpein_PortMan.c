// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������, " + GetAddress_Form(NPChar) + "?"), "������ ������� �� �������� ������ ��� ������ " + GetAddress_Form(NPChar) + "...", "� ������� ����� ��� �� ��� ������ ��� �������� � �����-�� �������...",
                          "����������, ���� �� �� �� ����� �����, �� �� ����� ���� ��������� ��������.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������"+ GetSexPhrase("","�") +"...", "������ ��� �� � ��� ��������"), "��, ���-�� � ������� ���� �����...",
                      "�� ��, ������������� � ������ ���...", "��������, �� �������� ���� ���� ������ �� ����������.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//���� �������
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "�������, ��� '����' ��� ���-������ �������?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "������, � ������ 1654 ���� � ��� ���� ������� ������ ��� ������������� �������� ������ ������. �� ����� �����. �� ������������ ������ ���������� � ���? �����, ������ ������� � ���, ���������...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//���� �������
		case "Consumption":
			dialog.text = "����? � ���? ����� ��������� �������, ���, ���� ��, �������� �����? ����� �� ��������� �������, �������� � ������ � �������� ��� ��� ������� � ��������, � � ���� ������� ������ �� �� ������, ��� ���, ���� �� ����� ������ �� ������ � � ��� ������ �� �����.";
			link.l1 = "����. �������� �� ������������...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "������� ��������� ������...���-���. ��, ��� ����� ������ ������ � ������ 1654 ����, ������ '�����-��������'. ������������� ���������, ������ �� ������� ���-������, �����������, ����� ���������� - �����, ������. ����� 14 ������ 1654 ����. ������ ������� �������� � ���� ���.";
			link.l1 = "����. ������� � �� ����!";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "39");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}


