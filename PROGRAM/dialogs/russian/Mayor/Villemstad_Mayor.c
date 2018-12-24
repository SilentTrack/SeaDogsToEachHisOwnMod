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
			//����������
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad"))
			{
				link.l1 = "� ����, ��� ����������� ����-������� �������� �������� ��������� ������� ���� �� ������ ������ ������, � ������ - ���������� �����������. ��� ������� �������� ���. ������ �� ��������� � ����� ����� ������� � � ����� ������ ��� �������.";
                link.l1.go = "Portugeze";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("�� ��� ��� �������. ��� ��� ��� �����?", "������� �������� ��� ���-��, ��� �� �� ����������?");
            link.l1 = RandPhraseSimple("������������ ����������...", "��������, ����� �����"+ GetSexPhrase("","�") +" ��� �������...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//����������
		case "Portugeze":
			dialog.text = "���� ����������?! �� � ���? �����?";
			link.l1 = "� � �����, ��� ������� �� ��� �� �����. �����. � ��� �������� ��������� ������ ������, ���� ������, ����� �� ����� �� ����� ���!";
			link.l1.go = "Portugeze_1";
		break;
		
		case "Portugeze_1":
			dialog.text = "�����������! ������ �� �� ���������... ������, ������������� ����������� �������� � ��������� �� �����. �� ���������� ������� ������� ����� � ����� ������ �����.";
			link.l1 = "� �� ����� ������� �������� ������ ���� �������, ������... ���� �� �� ����������.";
			link.l1.go = "Portugeze_2";
		break;
		
		case "Portugeze_2":
			dialog.text = "������, �� ������ �� ����������� - ������� �� ��������. �� ������ ���������� ����������� �� ���������� ������� - ������� ������ ������� ��������. ���������! �������� ��������� �������� ��� ��������������!";
			link.l1 = "��... ������, ����� ������ ��� � ���� ������� ��������... �����, ������� - ������, �������.";
			link.l1.go = "Portugeze_3";
		break;
		
		case "Portugeze_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info("�� �������� 1500 ��������");
			PlaySound("interface\important_item.wav");
			dialog.text = "� ������ ������ ��� �������, �������, �������� �������� �����������. ��� ������ �� �������� ������ � ��� ������.";
			link.l1 = "�������, ������. ����������� ����� � ��������� � ����� �������.";
			link.l1.go = "Portugeze_4";
		break;
		
		case "Portugeze_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}