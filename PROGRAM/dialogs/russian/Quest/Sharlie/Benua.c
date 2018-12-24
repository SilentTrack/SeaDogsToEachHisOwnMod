// ����� �����
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) // Addon 2016-1 Jason ��������� ������� 1
			{
				dialog.text = "��� ������ ����, ��� ���. �� ������, ����� ������� ��� ����?";
				if (GetCharacterItem(pchar, "gold_dublon") >= 100 && sti(pchar.money) >= 50000)
				{
					link.l1 = "��, ����. � ����� ������ ��� ����.";
					link.l1.go = "FastStart_7";
				}
				else
				{
					link.l1 = "� ��� �����, ����. ����� �������� �� �������� - ���� ���� �� ������ �������, �� � ��������� ����� � �����������, ������.";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
			{
				dialog.text = "�� ���-�� �����, ��� ���?";
				link.l1 = "��, ����. � ���� ������� ������ �����, ������ �� �����. �� ������, ���...";
				link.l1.go = "escape";
				break;
			}
			dialog.text = "�� ���-�� �����, ��� ���?";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) // ��� �� ��������
			{
				link.l1 = "��, ����. ��� ����� ���� ������. ���� ����� "+GetFullName(pchar)+". ��� �������������� ���������� � ��� ��� ����, ������ �� �����.";
				link.l1.go = "FastStart";
			}
			if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) // ��� �� ��������
			{
				link.l1 = "��, ����. ��� ����� ���� ������. ���� ����� "+GetFullName(pchar)+". ��� �������������� ���������� � ��� ��� ����, ������ �� �����.";
				link.l1.go = "meet";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "��, ����. ��� ����, ����� ������ ������, ��� ����� �������. �� � ������ ������� ������ �� ������, � ����� ��� ����� � �������. ��� ���� ������ ���, ��� �� ������ ������� ��� ��������� ����� �����...";
				link.l1.go = "FastStart_2";
			}
			if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "��, ����. ��� ����� ���� ������.";
				if (CheckAttribute(npchar, "quest.relation_info")) link.l1.go = "help";
				else link.l1.go = "help_start";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && GetCharacterItem(pchar, "gold_dublon") >= 100 && sti(pchar.money) >= 50000)
			{
				link.l2 = "��, ����. � ����� ������ ��� ����.";
				link.l2.go = "FastStart_7";
			}
			link.l9 = "�� ���, ������, ����.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Benua_meeting":
			dialog.text = "��� ������� ���� �� ���, ��� ���?";
			link.l1 = "������������, ����. ��� ������������ ���������� � ���. ��� ��� - ����� �� ���. � ���������� ������ �� �����. ��� ��� ��������, �� ������ ���� ���-�� �����, �� ���������. �... ��� ����.";
			link.l1.go = "Benua_meeting_1";			
		break;
		
		case "Benua_meeting_1":
			dialog.text = "���� ������ �� �����? �� ���? ����� �������...";
			link.l1 = "� ������� ���� ��������, ����. � ��� ������ ������ �������. ��� ���� - ���� �� �����.";
			link.l1.go = "Benua_meeting_2";			
		break;
		
		case "Benua_meeting_2":
			dialog.text = "�-�, ��� ��� ���������. � ����� ���� ���� �� �����. ��������� � �����, �����... �����! �� ������������� ����� �� ����... ����� �� ������, ����� �� ����������� �������! � ��� ������ ���� ���� �� ����� � ����� �������\n��� �� �� ������� ������, �� � ������ ����, ��� ������ - ���� �� ������������������ ������ ������ ����������� �������, ������... � ��� ��������� ����. ������� ������ �����, ��� ���, � ���������� ���� � ����� ��������� - �����, �� ������ ��������� ���� � �����.";
			link.l1 = "�������, ����! � ���� ������ �����.";
			link.l1.go = "Benua_meeting_3";			
		break;
		
		case "Benua_meeting_3":
			DialogExit();
			NextDiag.CurrentNode = "Benua_meeting_repeat";
			AddQuestRecord("Sharlie", "4");
			pchar.quest.Sharlie_Benua.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Benua.win_condition.l1.date.hour  = 6;
			pchar.quest.Sharlie_Benua.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Sharlie_Benua.function = "Sharlie_BenuaMaltie";
		break;
		
		case "Benua_meeting_repeat":
			dialog.text = "��� ���, ������� ������ �����. ��� ���� ������ ������� ���� �����.";
			link.l1 = "������.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Benua_meeting_repeat";
		break;
		
		case "Benua_maltie":
			dialog.text = "����������, ��� ���. ��� � � ������ - ������ ������� ��� ����� � ���� ����. �� ����� �������� ���� � ������ ����������� �����, �� ��������� ������� ��� ��� �������...";
			link.l1 = "��� �� ���� �������, ����?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break;
		
		case "escape":
			dialog.text = "��, �����, � � �����. �� �������� ���� ��������. ������ ����� ���.";
			link.l1 = "��� ���?! �� �� ������, ��� ����� ����� ���� � ������ � ���! ����, ��� ���������? ��� ��� ����?!";
			link.l1.go = "escape_1";
		break;
		
		case "escape_1":
			dialog.text = "��� ���, ���� ���� ��� ����� � ������� ��� �������� ������� �������� �����. ���� �� ���������� - ��� ��������. �� �� ������� ��� ���� ������.";
			link.l1 = "����������... � ��� ����� ����, ��� � ������ ��� ����! ����� �� ��� ��� ������!";
			link.l1.go = "escape_2";
		break;
		
		case "escape_2":
			dialog.text = "�� ��������, �����. ��� ��� ������. ������ ���, � �����... ����� � ���� ���������� � �����. �� ������� �������� �������� ������ �����.";
			link.l1 = "� ������ �� ����������!";
			link.l1.go = "escape_3";
		break;
		
		case "escape_3":
			DialogExit();
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_mishelle");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Mishelle";
			NextDiag.CurrentNode = "escape_4";
		break;
		
		case "escape_4":
			if (CheckAttribute(pchar, "GenQuest.specialletter.read") && pchar.GenQuest.specialletter.read == "Letter_Mishelle")
			{
				dialog.text = "� ����, �� ������ ������. ������ � ���� ������� ���� ���-���, �����...";
				link.l1 = "��... ��� �� ���? ��� �� ������ �� �����? � ����, ��� � ����� ����� ���� ����������, �� �� ������������ �� �� �����!";
				link.l1.go = "escape_5";
			}
			else
			{
				dialog.text = "��� ���, ������ ������. ����� ���������.";
				link.l1 = "��, ����...";
				link.l1.go = "exit";
				NextDiag.TempNode = "escape_4";
			}
		break;
		
		case "escape_5":
			dialog.text = "���� ���� ������ �������� ������ �����, �����. ����� - � �� ��� ��� �������� � �������������. ������ ����� ������ � ��������� - � ��������� ��� ��������...";
			link.l1 = "�� �� ������������� � �������� ����� ��������� ��������?";
			link.l1.go = "escape_6";
		break;
		
		case "escape_6":
			dialog.text = "���, �� - ���. �� �������, ��� ��� ����� ���� ������, ����� �������� ������. ��� ����� �������� �� ����� ������ ��������, ����� ����� �����-�� ����� ������������ �������. � ���� �� ���� �����������, �����. �� � ��������, ��� ����� �������� ���-�� ������ ���������... ���� �������.";
			link.l1 = "��� ������, ����?";
			link.l1.go = "escape_7";
		break;
		
		case "escape_7":
			dialog.text = "��� ���, ��������� ����� �� �������, � �������. � �� ���� ��������� ���� �������, ��... ���� ���� ������� ���-�� ��������. � ������� �� �����, ��� ��� ���� ������ ���������� �����, ������...";
			link.l1 = "��, � ���, ��� ��� ���� ���-�� ������� - � �� ����������. � ���� �����������, ��� ������. ��� '���-��' ����� ���-��, ����� ������ ���� � ������� �����������.";
			link.l1.go = "escape_8";
		break;
		
		case "escape_8":
			dialog.text = "� �� �����, ��� ����� ������ ������ ����� ������. ������� ���, ��� ��� ����� ����� �������.";
			link.l1 = "� ������� �������� �� ������ � ������ ��� ���������, ��� ��� ���� ���������, ��� ��� ���� �����, � ��� ���. �� � ���� ���� �����, ������ ����.";
			link.l1.go = "escape_9";
		break;
		
		case "escape_9":
			dialog.text = "������������ ����, ��� ���. � ������ ������. �� ������ ���� �������!";
			link.l1 = "�������, ����. �� ��������!";
			link.l1.go = "escape_10";
		break;
		
		case "escape_10":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			pchar.questTemp.Sharlie = "escape";
			CloseQuestHeader("Sharlie");
			AddQuestRecord("Guardoftruth", "1");
			pchar.questTemp.Guardoftruth = "begin";
			// ������ �������� �������
			sld = GetCharacter(NPC_GenerateCharacter("spa_baseprisoner", "q_spa_off_1", "man", "man", 30, SPAIN, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_13", "pistol1", "bullet", 150);
			sld.dialog.FileName = "Quest\Sharlie\Guardoftruth.c";
			sld.dialog.currentnode = "spa_prisoner";
			RemoveAllCharacterItems(sld, true);
			LAi_SetStayType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Fortfrance_dungeon", "quest", "quest1");
			LAi_CharacterDisableDialog(sld);//������ �������
		break;
		
		// ���������� ������� �� ������
		case "meet":
			dialog.text = "���� ������ �� �����? �� ���? ����� �������...";
			link.l1 = "� ������� ���� ��������, ����. � ��� ������ ������ �������. ��� ���� - ���� �� �����.";
			link.l1.go = "meet_1";			
		break;
		
		case "meet_1":
			dialog.text = "�-�, ��� ��� ���������. � ����� ���� ���� �� �����. ��������� � �����, �����... �����! �� ������������� ����� �� ����... ����� �� ������, ����� �� ����������� �������! � ��� ������ ���� ���� �� ����� � ����� �������\n� ��� ������, ��� ������ ������� ����� �������, ��������� �� ������, �� ���� � ����������� ���� �� ���, ��� ��� - ��� ����. �������, ��� �� ������� ������ ������, � ���� ������ ������� ���. ��� ��� � ���� ������� ��� ����?";
			link.l1 = "������ ������ ���, ��� �� ������ ������ � ������, ���� � ���� ��������� �������� � ��������...";
			link.l1.go = "help_info";	
			npchar.quest.meet = true;
		break;
		
		case "help_info":
			dialog.text = "��� ������ ��� ������? ����... ��� ��, ������� ������������ ������ � ���� ������� � �����. � ���� ���� ������������ ������� � ������� ������� ������������ ������ �����, �� ����������, � ����� � ���������� ����������. ����� �������, � ���� ��������������� �� ���� ����� �������� ������� � ���������. ����������, � �� ����� ������� � ������, � ���� ���� ����������� ����� ������ - �� ����� ���� ������� ���������� ��������� � ����\n��� ������� ���������� ����������� ��������� ����������. ����� ����, �� ������ ������ �������� ���� �������� ��������� ��� ������ ������������� � �������� ��������. ��, � ������ � ����� �������� �� ���, �������. ���� ���� ����� ���������� - ���������, ����� ��������� ���� ����.";
			link.l1 = "�������! ����� � ��������.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "help_start":
			dialog.text = "��� ��� � ���� ������� ��� ����, ��� ���? ������, � ������.";
			link.l1 = "������ ������ ���, ��� �� ������ ������ � ������, ���� � ���� ��������� �������� � ��������...";
			link.l1.go = "help_info";
		break;
		
		case "help":
			dialog.text = "��� � ���� ������, ��� ���?";
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "� ���� �������� ������������ � ���������� ��������.";
				link.l1.go = "relation_spa";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "� ���� �������� ������������ � ������������ ��������.";
				link.l2.go = "relation_hol";
			}
			link.l9 = "��������, � ���� �������� ������ ������.";
			link.l9.go = "exit";
		break;
		
		case "relation_spa": // patch-10
			pchar.GenQuest.BenuaNation = SPAIN;
			dialog.text = "������, ����������� ������� ������ ������� ���� ���������� � ������� � ��������� ������...";
			link.l1 = "������ ���, ����...";
			link.l1.go = "relation";
		break;
		
		case "relation_hol":
			pchar.GenQuest.BenuaNation = HOLLAND;
			dialog.text = "������, �������������� ���������� ������ ������� ���� ���������� � ������� � ��������� �����������...";
			link.l1 = "������ ���, ����...";
			link.l1.go = "relation";
		break;
		
		case "relation":
			rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
			if (rate <= 10)
			{
				dialog.text = "��, ��� ����� �������� � ����� ������. ����� � ������ ����� ����, ��� ���� ����������. ��� ����� ������ ��������� ������� ��������, ����� ������� ������������.";
				if (GetCharacterItem(pchar, "gold_dublon") >= 250)
				{
					link.l1 = "�������! ���, ������� �������.";
					link.l1.go = "agree";
					iTotalTemp = 250;
				}
				link.l2 = "����� ��� ����� ����� ����������� �� ��������.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate <= 20)
				{
					dialog.text = "��, ����� � ����� '��������' �������� � ����� ������. �������� �� ���� ���������, ��� ���, ���� ���� ���� ��������������. �� ������ ��� �� � �����. ��� ����� ������� ������� ��������, ����� ������� ������������.";
					if (GetCharacterItem(pchar, "gold_dublon") >= 500)
					{
						link.l1 = "�������! ���, ������� �������.";
						link.l1.go = "agree";
						iTotalTemp = 500;
					}
					link.l2 = "����� ��� ����� ����� ����������� �� ��������.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "��, ��� ���, �� ����� �� ���������, ��� � ���� ����... ���, ��������, ���� ������� �����. ��������� �������� � ��������� �� �����, �� �������� ���� ����������� ��������� - �����, �����. � ����� ��� ��� ������������� �������, ���� ���������. ��� ����� �������� ������� �������� - � ����� ����� ������ ���� ��������.";
					if (GetCharacterItem(pchar, "gold_dublon") >= 600)
					{
						link.l1 = "�������! ���, ������� �������.";
						link.l1.go = "agree";
						iTotalTemp = 600;
					}
					link.l2 = "����� ��� ����� ����� ����������� �� ��������.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveItems(pchar, "gold_dublon", iTotalTemp);
			Log_Info("�� ������ "+iTotalTemp+" ��������");
			PlaySound("interface\important_item.wav");
			dialog.text = "������ ������ �� ����� ���� ������. �����, �� ��� ����� � ��������� � ���������� � ������� ������.";
			link.l1 = "�������, ����! ���� �����...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, 10+rand(5), false);
			pchar.GenQuest.BenuaNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
			npchar.quest.relation = "true";
		break;
		
		// Addon 2016-1 Jason ��������� ������� 1
		case "FastStart":
			dialog.text = "���� ������ �� �����? �� ���? ����� �������...";
			link.l1 = "� ������� ���� ��������, ����. � ��� ������ ������ �������. ��� ���� - ���� �� �����.";
			link.l1.go = "FastStart_1";			
		break;
		
		case "FastStart_1":
			dialog.text = "�-�, ��� ��� ���������. � ����� ���� ���� �� �����. ��������� � �����, �����... �����! �� ������������� ����� �� ����... ����� �� ������, ����� �� ����������� �������! � ��� ������ ���� ���� �� ����� � ����� �������. �������, ��� �� ������� ������ ������, � ���� ������ ������� ���. ��� ��� � ���� ������� ��� ����?";
			link.l1 = "��� ����, ����� ������ ������, ��� ����� �������. �� � ������ ������� ������ �� ������, � ����� ��� ����� � �������. ��� ���� ������ ���, ��� �� ������ ������� ��� ��������� ����� �����...";
			link.l1.go = "FastStart_2";	
			npchar.quest.meet = true;
		break;
		
		case "FastStart_2":
			dialog.text = "��� ������ ��� ������?";
			link.l1 = "����, � ������� ���� ��������, �� ��� ������������� ���. ��� ������� � ����� ���������� � ��������� �����, ��� ������� ����� ��������� ������, ������������ �� ������ � ���������� ����� �� �������.";
			link.l1.go = "FastStart_3";
		break;
		
		case "FastStart_3":
			dialog.text = "� �����, ��� ���. � �����, ��� �� �������� ��� ������. ��� ��, ���� ������ � ���� ������ ����, �, �������, ������ ����. � ���� ���� ������ ����������, ������� � ������� ��������� ���-�����. � ����� �������� �� ���� �� �����, ���� ��� ������������� ������� ������ �����. ��������� ����� ���� � ��� ������� �������� - ����� ������ ���� ������� � ������.";
			link.l1 = "�������, ����. ������� ������� � ���� �� ������� �����?";
			link.l1.go = "FastStart_4";
		break;
		
		case "FastStart_4":
			AddMoneyToCharacter(pchar, 50000);
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "� �� ���� ���� ��������. ������� - ����, �����, ��� �����������.";
			link.l1 = "������, ������ ����. ��� ��� ��������� ���!";
			link.l1.go = "FastStart_5";
		break;
		
		case "FastStart_5":
			dialog.text = "������ � ���� ��������������, ��� ���.";
			link.l1 = "...";
			link.l1.go = "FastStart_6";
		break;
		
		case "FastStart_6":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			npchar.quest.FastStart = "true";
			pchar.questTemp.Sharlie.BenuaLoan = "true";
			SetFunctionTimerCondition("Sharlie_BenuaLoanTime", 0, 0, 180, false);
			AddQuestRecord("Sharlie", "5-2");
		break;
		
		case "FastStart_7":
			dialog.text = "���������, ��� ���. �������, ��� ������ ���� �����������.";
			link.l1 = "��� ���, ����! �������.";
			link.l1.go = "FastStart_8";
		break;
		
		case "FastStart_8":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddMoneyToCharacter(pchar, -50000);
			RemoveItems(pchar, "gold_dublon", 100);
			pchar.quest.Sharlie_BenuaLoanTime.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.BenuaLoan");
			AddQuestRecord("Sharlie", "5-3");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}