// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("��� �� ������? �����������.", "� ������ ���, ��� �� ������?"), "������ ��� �� ���� �� ��������� ������ ������...", "� ������ ��� �� ���� �� ����� ��������� ������ ������...",
                          "�� ����� �� ��� ��������?! � ���� ��� ����� �� ���������� ������ ������, � �� ��� ������� ��������� ������!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������"+ GetSexPhrase("","�") +"...", "�� ������, �� ����� � �� �����..."), "��, �����... �� �� ������, �����...",
                      "�����, �����... ������ �����...", "��������, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "� ���� � ��� ���������� ����. ������� ������� ���-���� ����� ������� ���� �������� ������������� - ������� ����� � ���������. ���� � ���, ��� ���� ����� ��� ������� �� ������� ��������, ������ ��� ��������� ��� ���� ��������� ������...";
                link.l1.go = "guardoftruth";
			}
			// Jason ���
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "� ������ �� ������� �������-����������� ������� �� ������ ����� ������� ������������ ��� ����������� ���� ��������.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "� ����� ������� � ������� ������.";
                link.l1.go = "patria_2";
			}
		break;
		//************************** ��������� ������ ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("�� ��� ��� �������. ��� ��� ��� �����?", "������� �������� ��� ���-��, ��� �� �� ����������?");
            link.l1 = RandPhraseSimple("������������ ����������...", "��������, ����� �����"+ GetSexPhrase("","�") +" ��� �������...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "guardoftruth":
			dialog.text = "��. ����� ���������. �� ������ �� �� ��������, ��� �������� �������� ������ ���� ���������?";
			link.l1 = "���� �� � ��������, �����. ������� �� ����� ����� �� ������������� ��������. � ����� ������� ������ ��������� ����, ������� ������ ��������� �����������������, � � ��������� ������� �������� ��������� ������������...";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = "� ����� ��� �������� �������������� � ��������� ������� ���� ������� ����� ���� �������, �������� �� �����������.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "� � ����� ��� ��� �� ����� ����� ���������� � ��������������� ��������, �, "+pchar.name+"? ������� ��� �� ������, � � �� ������ ������� ��������� �������� �� ������� ���� � ���� �������. ������� ����� - � �����. ��� ��������� �������� ��������� � ������� � �������� �� �����, ��� ���...";
			link.l1 = "����� �� ������ ��� ������?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "���� �����������, "+pchar.name+": � �� ������ �������. � �� ��������� ����� � ���� ���������� ���������.";
			link.l1 = "����. �������� �� ������������, �����...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "28");
		break;
		
		// Jason ���
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "������� �����, �� � ��� ��� ����� ��� ����. ��������� ���� ������� � �������������, � � ����� ������� ��� ������.";
				link.l1 = "������.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "��, �������, ������� ����� � ������ � ����. ������� ���������� � ����� ��������� ��� ���� ������������.";
				link.l1 = "����� �� ������������ � ����. �� ��������, ���� ���������.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "�������. ����������. ������� ���������� � ����� ��������� ��� ���� ������������.";
			link.l1 = "����� �� ������������ � ����. �� ��������, ���� ���������.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateGlp(); // ������������ ������
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

