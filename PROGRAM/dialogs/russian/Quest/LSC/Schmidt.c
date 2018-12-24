// ����� ����� - ���������
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iRem;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "����������, ���������, �� ����� ���� ��� ����������, �? ���� �� � ���� � ����� - ��� ������ ������ � ���� ����������. �������!";
				link.l1 = "��...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // ���� ������ ��������
				{
					dialog.text = "�, "+GetFullName(pchar)+"! ��������, �������� � ����� �����. �������, ��� �� ����� ������ �������� � ����� �����������. ������� ����� ������ ������, ��� � ��� ������ �����.";
					link.l1 = "�������, ��� ��� ���. � ���� ������������ �� ���� ������?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "��? ���� ���� ����?";
					link.l1 = TimeGreeting()+". ���� ����� "+GetFullName(pchar)+". � ������ ���������� � ������. � ��� ������� �� ���?";
				link.l1.go = "meeting";
				}
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // ���� ������ ��������
				{
					dialog.text = "�, "+GetFullName(pchar)+"! ��������, �������� � ����� �����. �������, ��� �� ����� ������ �������� � ����� �����������. ������� ����� ������ ������, ��� � ��� ������ �����.";
					link.l1 = "�������, ��� ��� ���. ������ � ���� ������������ �� ���� ������?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "�, "+GetFullName(pchar)+"! ����� ��������� ����������? ��, ��� � ��� ��������� - ��� � ���� �� ��� �� �������, �� �������.";
					link.l1 = "������, �� ���� ��� ���������.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // ������ �������
			dialog.text = "�����! �� ���� ��������� �� ���, ������. � ����� �����, ������ � ��������� ��������, � ����������� ��� ���� �������. �� ����� ������� ������� ������, ��� �������� �������� ��������� ���������, ��� ������� ����� ����� � ���� - ����� �����, �������� � ��������������. ������� � �� �����, ����� ���� ��������� �� ������.";
			link.l1 = "�� ������� ������? � �������� � ��� ���-������ �����?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "���. � ����� ������ ������ ��� ������ ����� ������. ��� ��� �������, � � �� ���� �� �������� �� �� ���. ��� ��� �� �������������, ������. �������� � ���� ������, ���, ��� �������, ��������� ����� ��������� - ����� � ���������, ���������.";
			link.l1 = "�����. ����� � �����. ��������, ��� �����������!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "friend":
			dialog.text = "������. ���� �������� - ��� ����, ��� ��� ������ ����������� ���� ���������.";
			link.l1 = "� �� ����� ���������� ������ ��� �����.";
			link.l1.go = "blade";
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l2 = "� ������, �� ���������� ��� ��������� ����� ������ ������ ������. � ����� ���� ����� - ������������ ������. � ��� �� � ��� �������� ���� ����� ��?";
				link.l2.go = "narval";
			}
			link.l3 = "���� ������� ��������� ���, ������ � ������ �� ��������. ������� - � ����������� �������!.";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "Jurgen":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "��, "+GetFullName(pchar)+"! ��� �� �� ������? ��� ��� ��! �� ����� �� �������?";
				link.l1 = "�� ����������, �����. �����! � ������ � �� ��������� - ��� �� ��� ������������� ������� ����...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				NextDiag.TempNode = "Jurgen";
				break;
			}
			dialog.text = "�, "+GetFullName(pchar)+"! �� ������ ���� ����������?";
			if (CheckAttribute(npchar, "quest.narval_blade") && npchar.quest.narval_blade == "ferrum")
			{
				if (GetCharacterItem(pchar, "jewelry11") >= 3)
				{
					link.l4 = "� ������ ��� ����� ������� ������, ��� �� � �������. ������� - ��� ���?";
					link.l4.go = "narval_7";
				}
				if (CheckCharacterItem(pchar, "meteorite"))
				{
					link.l5 = "������� ����, �����. � ����� ���������� ������ ������ �� ���, �� �� ����� ������� ������, ��� �� �������� - � ��� �� ������ ���� ������.";
					link.l5.go = "narval_7_1";
				}
			}
			if (!CheckAttribute(npchar, "quest.blade_done"))
			{
				link.l1 = "� �� ����� ���������� ������ ��� �����.";
				if (!CheckAttribute(npchar, "quest.blade_rules")) link.l1.go = "blade";
				else link.l1.go = "blade_4";
			}
			if (CheckAttribute(npchar, "quest.blade_payseek"))
			{
				link.l1 = "� ������ ��� �������� � ���� ������ �� ������.";
				link.l1.go = "blade_3";
			}
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive" && npchar.quest.narval_blade == "begin" && pchar.questTemp.LSC != "return") // patch-9
			{
				link.l2 = "� ������, �� ���������� ��� ��������� ����� ������ ������ ������. � ����� ���� ����� - ������������ ������. � ��� �� � ��� �������� ���� ����� ��?";
				link.l2.go = "narval";
			}
			if (CheckAttribute(npchar, "blade_date") && GetNpcQuestPastDayParam(npchar, "blade_date") >= 20)
			{
				link.l1 = "� ������ �� ����� �������. �� ��� ������ ���� �����, ��� � �������?";
				link.l1.go = "blade_done_2";
			}
			link.l3 = "�� ���, ������, ������ ����� �������������.";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		// --> ����� �������
		case "blade":
			dialog.text = "������. �� � ���� ���� ������������ ���������� � ������, ��� ��� ���������� �������, � ����� ������� - ����������, ��� ���.";
			link.l1 = "� ��� ����������� ������.";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "�� ������ �������� � ���� ������ ���� ������ � ������ ���� ���. ����� � �� �������� ������ ������-�� ����������� ������, �� ������ ������� ������ ���, ������� ������ - ������, ����� ��� �����, � �� ��� ��������� �������� - ����� �������� �� ����, ����� ��������� � ���� � ������� �� ������ ������\n��� ��� ���������� ���������, ������ ��� ������� �����. �����. ���� ������������ - �������� ����. ������ - ������������� � ��������. ������ � ���� �������������, �� ����� ������ - ������ �������. ������ ������.";
			link.l1 = "���! ��������, ������...";
			link.l1.go = "blade_2";
		break;
		
		case "blade_2":
			dialog.text = "��, ��������. �� � ������ � ����� ���������������� ��������, ��� ��� ���� ���������. �������, � ��� �� ���������: ������ - �����������, ������ - ���.";
			link.l1 = "� ��� �����, �����. ��, � ���� ������� �����.";
			link.l1.go = "blade_3";
			link.l2 = "��. �������, ��� ����� ���������� ��������, ������ ��� �������� �� �����. �������� � ����� ��������� �����!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
			npchar.quest.blade_rules = "true";
			npchar.quest.blade_dublon = 1000;
			AddQuestRecord("LSC", "17");
		break;
		
		case "blade_3":
			dialog.text = "����� ������. ����� ������� ���� �������.";
			if (CheckCharacterItem(pchar, "gold_dublon"))
			{
				npchar.quest.blade_pay = GetCharacterItem(pchar, "gold_dublon");
				link.l1 = "���, ����������. � ���� ���� � ����� "+FindRussianQtyString(sti(npchar.quest.blade_pay))+".";
				link.l1.go = "blade_pay";
			}
			link.l2 = "��. � ���� ������ �� � ����� ���, � ���������. �� � ����������� �������, � �� �������� � ����� ���������.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "blade_4":
			dialog.text = "�� ���-���� ������� ���� �����? ������ ��������?";
			link.l1 = "��. � ��������� �����������.";
			link.l1.go = "blade_3";
		break;
		
		case "blade_pay": // ������
			if (sti(npchar.quest.blade_dublon) < sti(npchar.quest.blade_pay)) // ������ �����
			{
				npchar.quest.blade_pay = sti(npchar.quest.blade_dublon);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.blade_dublon)-sti(npchar.quest.blade_pay);
			npchar.quest.blade_dublon = iTemp; // ���������� �������
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.blade_pay));
			Log_Info("�� ������ "+sti(npchar.quest.blade_pay)+" ��������");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "�������. ������, ����� �� �������� ��� ������ � ���������, � ���� ���������� � ����.";
				link.l1 = "� ���� ������ �����?";
				link.l1.go = "blade_done";
			}
			else
			{
				dialog.text = "������. � �������� � ��� �������. ��� �������� �������� ��� "+FindRussianQtyString(sti(npchar.quest.blade_dublon))+".";
				link.l1 = "��� ������ ������ ��� �������� - ���������� ������� ���.";
				link.l1.go = "exit";
				npchar.quest.blade_payseek = "true";
			}
		break;
		
		case "blade_done":
			DeleteAttribute(npchar, "quest.blade_payseek");
			dialog.text = "�������! ����� ������ ��� �� ���� - ������, ����� ��� ������?";
			link.l1 = "������. ����� ������� ������ ������.";
			link.l1.go = "rapier";
			link.l2 = "�����. ��� ����������� ������� � ���� ����� ������.";
			link.l2.go = "sabre";
			link.l3 = "������� ��, ������! ������ ��� ������, ��� ���������!";
			link.l3.go = "palash";
		break;
		
		case "rapier":
			npchar.quest.blade_done = SelectJurgenBladeDone("rapier");
			dialog.text = "��� �������. �� ������� ��������� ����� �������� ����, �� ������.";
			link.l1 = "�������! ���� � ��������� �����. �� ��������, �����.";
			link.l1.go = "blade_done_1";
		break;
		
		case "sabre":
			npchar.quest.blade_done = SelectJurgenBladeDone("sabre");
			dialog.text = "��� �������. �� ������� ��������� ����� �������� ����, �� ������.";
			link.l1 = "�������! ���� � ��������� �����. �� ��������, �����.";
			link.l1.go = "blade_done_1";
		break;
		
		case "palash":
			npchar.quest.blade_done = SelectJurgenBladeDone("palash");
			dialog.text = "��� �������. �� ������� ��������� ����� �������� ����, �� ������.";
			link.l1 = "�������! ���� � ��������� �����. �� ��������, �����.";
			link.l1.go = "blade_done_1";
		break;
		
		case "blade_done_1":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "blade_date");
			NextDiag.CurrentNode = "Jurgen";
			AddQuestRecord("LSC", "18");
		break;
		
		case "blade_done_2":
			dialog.text = "��. ��� ������ �����. ����������, �������� � �������� �� ��������. ��� ������ �� �������� ��� � ����, ����� �������, ��� �� ����� ����������� �� ���� �����.";
			link.l1 = "�������, �����.";
			link.l1.go = "blade_done_3";
		break;
		
		case "blade_done_3":
			DialogExit();
			NextDiag.CurrentNode = "Jurgen";
			GiveItem2Character(pchar, npchar.quest.blade_done);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "blade_date");
		break;
		
		// ����� ������ ������ ��� ����
		case "narval":
			dialog.text = "���, �������, �� ��� � ��� �������� �������� �� ���� ��������. ��-������, ����� ����� � �������� ������ ������ ��� ����� ����� ������, � �� - �� ��� �������. � ��-������, � ���� ��� ��������� ��� ��� ������������.";
			link.l1 = "� ��� �� ������ ������ ��� ���� �����? � ������, ��� ��� ��������� �� ���...";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "������ ���. ����� ����� ������ ���������� �� ����� ����������. ������ ��� ��� ������� - ��� ��������. �� ������ ������������� ���������� - �� ������� ������, � ������ �� ���� �� �������. ��� ��� ���� �� �� �����-�� ������� ������� ��� ������ - ����� ���� �� ������ ������. �� ����� �� �������� - �� �� ������...";
			link.l1 = "��. � ��, ��� � �� ������ - ��� ����� ��������� �������������� ��������?";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "��. ������������� ��� ��� ��� �������, ���� ������, �� ����� ����� � ���� ������ ������ ��� �������.";
			link.l1 = "���... �����, �����, ��� ������������. �� � ���� �������� ������ �����. � ���� �� � �������� ���� ������ � ������� ��� ����� ����� ������?";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "��. ��, ���� �� ��������� ��� ������ ��� ������������, �� ��������, ��. ��� ����� �� ����� ������������� ��������... � ��� ���� �� ������ ������� ���� �����?";
			link.l1 = "��� ������� ����. ��� �� ����� ������, � ������ ����������� ����� ������� ����� ������������� �������.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "��! � ��� �� ���������� � ���. ������... �� ��� ��, � ��������. ���� ����� ������ � �������� �� ������ �������, � ������... ������ ������ - � � ������ �����. �� ������ � ������... �, �������, ������ �� ����. ����� ��� ����� ������� �� ������ �� ���, �� � �� ����.";
			link.l1 = "�������! ������� ��� ����� ������ ��� ��� ������������?";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "�����, ������� �������� �� ���, ���� ��� �������� ����������� ������� - �� ����� � ���������. ��� ����� ��� �����.";
			link.l1 = "������. � ���������� ������ ��. ����� � �������� � ������ ���������.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			DialogExit();
			npchar.quest.narval_blade = "ferrum";
			NextDiag.CurrentNode = "Jurgen";
			// ������ ���������� ����� ��������� �� ���
			sld = ItemsFromID("meteorite");
			sld.shown = true;
			sld.startLocation = "underwater";
			sld.startLocator = "item"+(rand(7)+1);
			Log_TestInfo("�������� � ��������" + sld.startLocator);
			pchar.quest.LSC_narval_ferrum.win_condition.l1 = "item";
			pchar.quest.LSC_narval_ferrum.win_condition.l1.item = "meteorite";
			pchar.quest.LSC_narval_ferrum.function = "LSC_NarvalFerrum";
			AddQuestRecord("LSC", "19");
		break;
		
		case "narval_7":
			RemoveItems(pchar, "jewelry11", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "��-��, ��������... ��, ����� - ���! ��� ���� ������ - �������� ����� ��������� ����� �� ���?";
			link.l1 = "��, ��� �������... �� ���� ���� ���� ����� ���� �����������, �� ��� ��?";
			link.l1.go = "narval_8";
			pchar.quest.LSC_narval_ferrum.over = "yes"; //����� ����������
		break;
		
		case "narval_7_1":
			RemoveItems(pchar, "meteorite", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "��-��, ��������... ���! ��, ��� �� ����� ������ ������, �� ����� �������� ������ � ��� �� �����. ��� ������ � ������ ������ ��� ������������ ������. ��� ����, ��������, ������ - ����� ���?";
			link.l1 = "��, ��� �������... �� ���� ���� ���� ����� ���� �����������, �� ��� ��?";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			dialog.text = "�� ��������� ��� ��� ������ � ������, "+pchar.name+"... �� ��� ��, �������. ������ ������ ����� � ��� ����������� ��� ����� ���������� ��������. ������ ������ ��� ��� - � ������� ��� ������ ������ � ������� �������\n��������� ����������� �� ��� ������ � ����. ������ �� �������� �� ������ ������� - ������� �������. ��� ����� ����������, ��� �������.";
			link.l1 = "������, �����. ������������. ����� - �� �����������!";
			link.l1.go = "narval_9";
		break;
		
		case "narval_9":
			DialogExit();
			npchar.quest.narval_blade = "work";
			NextDiag.CurrentNode = "narval_10";
			SetFunctionTimerCondition("LSC_NarvalBladeForMary", 0, 0, 2, false); // ������
			AddQuestRecord("LSC", "21");
		break;
		
		case "narval_10":
			dialog.text = ""+pchar.name+", �� ���������� ����. �� �� ������, ����� ����� ��� ����� �������?";
			link.l1 = "��, �������. � ��� �����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_10";
		break;
		
//----------------------------------------- ����������� ������� -----------------------------------------------
		//����������� �� � ��������
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("��� �� ��� ���������, �? �� �� ���!", "��� ��� ��! ���� � ����������, � �� ����� � ������ � �������!", "�� �������� ������ �������?! ���� ��� ����� �� �������!");
			link.l1 = "�-���, ������!!!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//��������� �� ����������� ������
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("������, �� �� ����� ������. � �� ���������� �������...", "������, � ��� ��� �� ������� ��������� �����������. ����� ������.", "������, ��� ��, ��� �'��������, ������� ���, ������ ������? ����� ������, �� � ���� ��� ���������� �������...");
			link.l1 = LinkRandPhrase("������.", "�����.", "��� �������...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "����������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ���������� �������.", "������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ���������� �������.");
				link.l1 = LinkRandPhrase("������.", "�����.", "��� �������...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "��������� �� ���������, ��������, ����� ������ � ������� � �����. � ���� ���� � ������������...", "��� �� ��������, ����� ������� ����� ������ ���� � ������� �� ���������. ��� ���� ������...");
				link.l1 = RandPhraseSimple("�����.", "������.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- ����������� �������
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string SelectJurgenBladeDone(string _sType)
{
	string sBlade;
	switch (_sType)
	{
		case "rapier":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_18"; 
			else sBlade = "q_blade_16";
		break;
		
		case "sabre":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_19"; 
			else sBlade = "q_blade_10";
		break;
		
		case "palash":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_21"; 
			else sBlade = "q_blade_13";
		break;
	}
	return sBlade;
}