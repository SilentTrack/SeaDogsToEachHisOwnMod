
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
					dialog.text = RandPhraseSimple("������, � ���������� ����!!!", "���������� �������, ������!!!");
					link.l1 = "�� ��, ����� ���������� �� �������...";
					link.l1.go = "fight";			
			}
			else
			{

				
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����������, "+ GetSexPhrase("��� ���","���� ���") +". ������ �������� � ���?..", "��� ������ ���� � ����� �������, "+ GetSexPhrase("��� ���","���� ���") +". ����� ���������"+ GetSexPhrase("","�") +"?"),
							""+ GetSexPhrase("��� ���","���� ���") +", �� ��� �������� � ����� �������. ���� ����� ���-�� ���?", ""+ GetSexPhrase("��� ���","���� ���") +", ����������� ������ ������ �� �������� ��������. ��� ��� ���� ���������: ���� ���-������ �����?",
							RandPhraseSimple("������ ��������� � ���������� ������ � ��������� ������ �� ������. ����� � �� ��������� �� �����...", ""+ GetSexPhrase("��� ���","���� ���") +", � �� ����� ����� ������������� ���������. ���� � �� ����� ����� �� �����."), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("�� ���, ��������"+ GetSexPhrase("","�") +" �� �����, ������ ����...", "��� �� �����, �����. �������, ��� ����� - "+ GetSexPhrase("����","���") +" � �������..."), 
							"�� ���, ������ ����...", "���, �����, ������ �����"+ GetSexPhrase("","�") +" ���������...", RandPhraseSimple("��...", "��, ��� ������, ������ ����..."), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);				
			}
			if (CheckAttribute(npchar, "protector.CheckAlways")) //����� �� �������
			{
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{					
					dialog.text = "���� ������, ��� �����! ����� ���!!!";
					link.l1 = "��������!!";
					link.l1.go = "fight";
				}
				else
				{
					dialog.text = LinkRandPhrase("��� ���������� ������, ���� ���� ������������� ��������!!!", "���� � �� ����� ���� ������� - �������� �������.", "���� ��� ������ ���� ������ - � ���� �����...");
					link.l1 = RandPhraseSimple("����, ������.", "�������...");	
					link.l1.go = "exit";
				}
			}
			if (findsubstr(npchar.id, "Prisoner", 0) != -1) //�����������
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = LinkRandPhrase("��-��, �� ���� �� ������ ��������, ��� '�������' ������������ �������� � ��!", "�������, ������� ���� ���-�� ��������� ������� �� �����!!", "� ��� �� ����� �� ���� ����� - �����... �� �� ��������"+ GetSexPhrase("","�") +" ��� ��������� ������������ � �����. �������...");
					link.l1 = RandPhraseSimple("���!", "����...");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("��� ������ �������� � ���� '������'. ������� ��� ����� - ������ �� � ��� �� ���� ����...", "���������� ��������� � �����! � ���� � �� �� � ��� �� ������� ����� ��������!!!", "����� ���� ��� ����� �� ������, ��� ��� ��� ������ ��� �� ����... � ������� ��� ��������?..");
					link.l1 = RandPhraseSimple("��... ��, �� ����...", "��� ��, �������...");
					link.l1.go = "exit";
				}
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
	}
}
