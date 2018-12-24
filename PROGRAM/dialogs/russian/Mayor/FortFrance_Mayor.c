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
			//--> ����� ��������
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l1 = "�����, � ����� � �������� ���� �������, ������� ���������. �� ���� ����� ������� ���� ��� ��� ������ - ���� ����������� �� ������. �����, ��� ������������ ����-�� �� ������� ������� ������ ������?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- ����� ��������
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
		
		case "Sharlie_junglejew":
			dialog.text = "����� ��������� �������... ����������! ��� ������ ����������, �����! ��� ������ ���� ����. � ��� �� �� ������� ����� �������� � �������. ��� ������� ��������� ������� ����� ��� ���������� ���������������. � ��� � ����, ��� ��� ���� ��������!\n�����, � ����� ���, ��� �� ������ ����� �� ���, � �� ����� ������� ��� ������� ��� ���� ����������. � � ����� �� ��������. ��� � ������, �� ����������� ���������� �������? ��� �� ������ ����������� � �������� ����, �� ��� ���������� ����������� ����� ������ ����������. ���, �������� ��. ������, ��� �� ��� ��� ����������!";
			link.l1 = "�������, ���� ���������!";
			link.l1.go = "Sharlie_junglejew_1";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "jewelry25", 1);
			GiveItem2Character(pchar, "map_bad"); 
			AddQuestRecord("SharlieE", "2");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
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
			Patria_BastionFrigateMrt(); // ������������ ������
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

