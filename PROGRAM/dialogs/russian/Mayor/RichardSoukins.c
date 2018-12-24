// ������� � ������-��������
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- ������ ������ - ������ �������
		case "First time":
            dialog.text = "� ���� ���� �� ���? ���? ����� "+ GetSexPhrase("���� ������","������� �� ��������� ����.") +"";
			link.l1 = "��� �����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";


					if (npchar.city == sti(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "����� ����� ��������� ��� ���� ��������?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "� ���"+ GetSexPhrase("��","��") +" �� ����, �� ��� ����� ������ - 30 000 ����, ����� �������� ����� �� ����.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "��������, ��� �� ������ � ���"+ GetSexPhrase("��","��") +" �� ����� ������ �� ���������������.";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "���� �������. ������ ���� ������ �� ����� �������� ���������� � �������� �������.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//zagolski. ��������� ����� �� ������ ===================================
		case "pirateStartQuest":
			dialog.text = "��... ���������, ��������? � ��� ���� ����� ������, ��� �� �� ��� �������"+ GetSexPhrase("��","���") +". ��� ��� ��� ����� ������� �� �������. ���������� ���-��� ��������� � �������� ���������, � ���� ����� ��� �����, ��� �����������. ����� ����� �� ������, �� ���-��� ���������.";
			link.l1 = "��� � ������. � ��� �� ����?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "������, �� ������� � ��������� �� ����. ������...";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "� ���� � ��������� - � ����� ����� ���������� � � ��������� ����� '�������' � �������� 200 �����, ����� ������� �� ������ ���������� �� ��������� ���������. ��� � ����� ��������� �����, � �������� ����������, � ��� ����� ��� ��������, ��� ��� ����� ������ � ��������� �������. ��!.. ������� � ���� �� ��������. � ������� ��������� ���������� ������� ������� � ������, ��� ����� ��� ���������� � ������ ����� - ���� � ������, �� ��� ������ � �����.";
			link.l1 = "� ���? � ����"+ GetSexPhrase("��","��") +" � ��������� ��� ��������� 200 �����, ���� �� �� ������� �������? � ��� ��� �� �������?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "���, �������. ����� � ����� �� ������? ������� � �� ����� � ����� ������. �� ��� ����� ��������������, ��� ����, ������� ��� ����������� - ��� � ���� ��� ������. � �� ������ ������� ���, ��� ��������� ��� ����� ������, � �������� ���� 10 000 ����. ��������� ��� ������. �� ���, ��������?";
			link.l1 = "������! � ��� ��� ����� ����? ���� �����-�� �����������?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "���. ������ ��������� ����, ��������� ��� � ����� �� 10 000 - ������, �� ��������.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "���� �� � ���� ��� ���� �����, � �������� �� � ��� ����� �����. ��� �� ��� � ���� ������ ��������� �� �����. �� ���� ������ ���������� ������ - ��� ��� ������ � ����� '�������' � � ���� ���������? �� ����� ��� ������ � ��� ��������. ��������?";
			link.l1 = "��, ���� ���-�� �������������� ����������.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "���! ��� ��� � ���. ������� ���� ��������� ����������� � ������� ����� - � ���� ���� �� �������. ��� ����� ����������, � ������ - ��� ������ �� �������. ������ �� ���������, ������ ����� �� ���� �� ���� ������� ����� �� ������? ���� � �� ������, ��� ������� ���������� - ����������� ���� �������. � ��� ����� ����� �� �������...";
			link.l1 = "�������... ������, ����� ����������� ���� � �� ��������� �����. ����������� �� ������.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "�������� �����, ��������? ��� ������� �����... ���� ���� ������ 5000 ����, ������ � ���� ������ ���. �� ���� ��������� ������� � ���� - ����� � ������ �� ��������� ������! �� ���� ����� ����� �� �������.";
			link.l1 = "����� ���� �����...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "���, �����. ��� ���������� ������.";
			link.l1 = "��� ����� � �������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "��! �������� �������! � ��� ������, ��� �� � ���� ����������. �� ��� ������ ������ ���������� ����������.";
			link.l1 = "� ������ ���� ��������"+ GetSexPhrase("","�") +". ���� �������� ���� ������ �����.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "�������, ��� ��������� �������. �� �� �� �����, � ���� �������� ���� ��� ���� ����\n������� - ��� ������� �� ������� ������� ����, ������� ����� �� ������� '�������'. � ������, ��� ������ ���� � ���� ����������, ���� �� � �� �����. ��� ������� ������ � ��������� �������, ���� ������ - ��������� ����� � �������� �������. � ������ ��� �� ���� �� ������"+ GetSexPhrase("","�") +", ������� � ������ ���� �������� ��� ���� ����. ������� 15 000 ����. ������"+ GetSexPhrase("��","��") +"?";
			link.l1 = "������! ������, ��� ��������� ������ ���� ��� ��������.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "������ ���, ������� ��� � ��� �����������... �� � �������. ������, �� � ���.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "�����-�����. ��� ���� ��������� ��� � ��� �������� ���, ��� �� ������� �������"+ GetSexPhrase("��","���") +". �� ��� �, ���� ���� �� �������� ������"+ GetSexPhrase("","�") +", ��� ��������� ������� � 15 000 ����. � ������� ����, ������� �� ��� �����"+ GetSexPhrase("","��") +".";
			link.l1 = "��� � �������, ���"+ GetSexPhrase(" ���","� ����") +" ������! � ������ ���� ���� ����, � � ��� ����� ��������"+ GetSexPhrase("��","���") +". �� �������!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;


	}
}
