// ��������� ���� - ��������� ����� �����-�����
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "�� ���-�� ������?";
			link.l1 = "�� ���, ������.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "diffindoor":
			PlaySound("VOICE\Russian\saga\Nataniel Hawk-02.wav");
			dialog.text = "�... ��� �� �����, ���� ������?.. ���.. ���-��-���! ��������� ��������...";
			link.l1 = "����������, ���������. ���� ��� �� - ��������� ����?";
			link.l1.go = "diffindoor_1";
		break;
		
		case "diffindoor_1":
			dialog.text = "��, ��� �, ���� ����� ��� �������. � ��� �����-�� ���������� ������, � ������ � ������ ����� � �������. ���� ��� �������, ��� ������� ������! ��� ������ �� ���� ��� �����.";
			link.l1 = "�������� �������...";
			link.l1.go = "diffindoor_2";
		break;
		
		case "diffindoor_2":
			dialog.text = "�� ��� �� ��� ����� ���� ���� �������, ������, ���� �� ���� �� ���������, � ��� � ������? �-�-��... ������ ��� - ���� ��������� �������� � ������ ���, � ������ �����-�� ������ ������������ � ��������� �������, ������������ ���� �������������� ���������\n� ����� ������� �� �����, � ����� ���� ������������ ���������� ����� � �����, ��� ���� ��� ����� �� ������, �� ���... � ������ ��� ����������! ���� �������� ������� ����-�-���� ����� �� ��� ��������� ����, ������� �������� ������ � ����!";
			link.l1 = "�����, �����, ����� ���������. ������������ - "+GetFullName(pchar)+". ������ � ����, ��� � ��������� ���� �������, ������ ��� � ������ ���� ��� �� �����, ��� � �� - ����� ������ ����������.";
			link.l1.go = "diffindoor_3";
		break;
		
		case "diffindoor_3":
			dialog.text = "�� ��?! � ���� �� ����� �� ��������� ����������, ��� �������? ��� ����... ��������� ������� ���� ������ �� ����?";
			link.l1 = "����� ������� ������� ����, ��� �����, ������� ����� ���� ������ �� �����, ��� ��� ����� ������� �����. � ����� ��� ����� ����, ��� ���� ��������� �� '���-���������', � ��������� ���������. ������, ������� ���� ������ ������ � ����. ���� ������ �� ���� ���������.";
			link.l1.go = "diffindoor_4";
		break;
		
		case "diffindoor_4":
			dialog.text = "�, ���� ������! �����? �� ������ �� �� ��� ��� �� ���?";
			link.l1 = "��� �� �������� - �� ���� �������. �� ����� �������, � �� ������ ���� ������� ���� �� ���� �������� - ������ ����������.";
			link.l1.go = "diffindoor_5";
		break;
		
		case "diffindoor_5":
			PlaySound("VOICE\Russian\saga\Nataniel Hawk-01.wav");
			dialog.text = "��������? ��... �� ����� �� ������, � ����� � ���������? � ���� ����� ������� �� ����. ����� ����� ������� ��� ���������? ����� ����, ��� ���� ��� �� ����� ������ ����. ���, ���������� ��� �������... �� ������ ���? ";
			link.l1 = "��. �� ��� � ��������� � ����: � ��� ���� �����, � ��� ������ ���� �������� �������, � ��� �� ������� ��� ������� �� ��������...";
			link.l1.go = "diffindoor_6";
		break;
		
		case "diffindoor_6":
			dialog.text = "���� � �� ���� ���� ���, � ���������� �� ��� ���� �������, ��� ������ ������� �����. ������ �� ��� ���-�� ������������ ��� ����. ���...";
			link.l1 = "���� ��� ��� �� �����? ��� � ����� ������������?";
			link.l1.go = "diffindoor_7";
		break;
		
		case "diffindoor_7":
			dialog.text = "��, �� ������, ����� ���... �� �������� �����. ��, ������, ������� �������, ����� ������ ����� ���� ������? ������ ����� �� ������ ����, �� ��� ������������ ������? ����� ��������� �� ����?";
			link.l1 = "��, � �����-�� ��. �� �������� �� ��������, �� � �������� ���� ���� ����� ������ ���� � ����� �����: ����� ����. � �������� � ��������� ���������� �������� � ����������� ��� ��������.";
			link.l1.go = "diffindoor_8";
		break;
		
		case "diffindoor_8":
			dialog.text = "���� ������... ������ ������? �-�-��... �� ������, ����� ������ ����? ��� ���? ��� �������� ������ �� ������� �����������. ����� - �� ���� ������� �����. ���� ���� ��������� ���-�� �� ���� �������� - � ��� ��� ��������, ��� �������� ������.";
			link.l1 = "�� ��� ������ � ���? �-�, �������. ��, ��� � �������, �����, ��� ��� ������� ����������� �� ���� ������ � ������? ������, �� �� ��� ���. ��������, �� �� ����� �������, � ������ ���������� �� ������ ������ �����������.";
			link.l1.go = "diffindoor_9";
		break;
		
		case "diffindoor_9":
			dialog.text = "��� ���? ��������� ��� ��� �������. � ��� �����... �� ��� ����� ����� �� ���� ����? ��� ����� ��� ���������� � �������� ������. ��� �����. � ��� ���� ���� ����������� �����! ��� � ���� ���� �������� �������� �������� ���� �����, � ����� ������ �������� �� ��������...";
			link.l1 = "������ ������, ������������ ���� � �� ����, �� ������, ��� �� ���� ����� �������. ������� ����� ����������: ������� �����, ����� ��... ������� ������ � ������ � ��������� ����, ��� ����� � ���� �� ����. ������ �� ����������� �����-����, ������ ����.";
			link.l1.go = "diffindoor_10";
		break;
		
		case "diffindoor_10":
			dialog.text = "�������? ��� �������! ��.. � ��������� ���� �������� ����� ������������, �� ��, ��� � ����� �������. ������� ������ ��������� �� ����� �������, ������� �� ��� ���������, � ��������� ���������� ������ ������� � ��� ��������. �������� ��� ����� ��� ���� ������ �����...";
			link.l1 = "���� ����� � ����? �������� ���������.";
			link.l1.go = "diffindoor_11";
		break;
		
		case "diffindoor_11":
			dialog.text = "� ��� ��� ������������! ��� � ��� ������ - ������� � ������ ������� ������������� �������. ��� ����������� ����� � ��������, � ���� ��������� ���-�� ������. ���� ����� ��� ��� ����������, �� ��� ����� �� �������. � ����� ��� �� �����. ��� ������ ���� �� ����������� ������ � ������� � ����� �� ����� - ��� ��� �������, '�� ������� �����'\n� �����, ��� '����' - ��� �������, �� � ����� ���� �������, ��� ��� ��������� �������. ��� ��� �� ���� ���� ����� - ��� �� �������, �� ������, ��� ����� ����� ��������� � ��� � �� �� ������.";
			link.l1 = "�� ����������. ������� ������, ��� ������ ������� ������� � �������� ������ �����... ��� ���� ������� ������?";
			link.l1.go = "diffindoor_12";
		break;
		
		case "diffindoor_12":
			dialog.text = "�����-�� ������� �� ������ ������ ���� ������, ������� ����. ��� � �����, ������� ������ ������������� ���� ��������. � �����, ��������� �����, ��� ��� �����-�� ����� �������, ������� ���� ����� ��� ������: ����� ������� ������ ��� ������, ��������� ������, ��������� �������, ����������� ����, � �� ������ ���� � ������\n�� ����� ������� ���� � ���� �������, � �������. �� ������ � ������ ��� ����� ��������, ��� ��� ���� �������� ����� ��������� ������. ������� ��� �� ���� �� �����. ������� ���� ������, ��������� �����, �� ��� ��� ����� �������� ���. ������, ��� ������� ���������\n� ����� �� ��� ���� �� ������� � ������� �������, ������� �������� ���. � ��� ��� ������ �� �� � ���������� ������� �� ���, � ����� ����, ������ ���� ���� � ������. ���� �������, � � ��� ������ ����� ��� ����� ������, ������� ��� ��������� ������� ��������... ������� ���� ������, ��� ��� ������������ ���� �������� - �������� �� ������ � ������������ � ���\n� ���� ��� ������, �� ��� �� �����, ��������� ��������� �� ���������, ���� ���? � ��������� �� �������� � ����������� � ����. � ���... ��� ���� ���-�� �������������!";
			link.l1 = "������ �� ��������� - � ����, ��� ��� ���������.";
			link.l1.go = "diffindoor_13";
		break;
		
		case "diffindoor_13":
			dialog.text = "������� � � ������ ����� ������������ �������. �� ���� �� ����� ���. � ��� ������������� ������ �������. � ������ ������� ����������� ��� ����. ��� �������� ������� - �� ���� � ���� �����-�� �������� �����, �� ����� - ��������� ��������, ����� ����������� � �������� ��������, � ����� ��� ����\n����� ����� �����. � �����, ���������������� ������ ������, ��������� ���� �� ���� ����, �� ���� ���������� �������. ��� � � ���� ������ �����, ��� ���� �� ����, �������, ��� ��� ������� ���� �������.";
			link.l1 = "��� ����� ������, �����. � ��� �� ��������� ������� �����, � �� ������� � ��� ���� �� �������� �����. ���� ������� ��������� �� ���� ����� � �����-����, � � ������� �������� �� �����������.";
			link.l1.go = "diffindoor_14";
		break;
		
		case "diffindoor_14":
			dialog.text = "� �����-����? � ��� �� ���� ��� �������������, ������? �������� �� ����: ����������� ����� ���������! ���� �� ���... ���, ���� ����� ��������� �����-������ ���� �������� � ������������. � ������ �� ���� ��������� �������� ��������, �, �����, ������. ������� � ��� �������? �����, ���, ���?\n� ����� ��� � �������� ������ �� ���� ������ ������, � ��� ������� ��, ��� ��������� �� ��������� �����, � ����. �� ��� ���� ������ ����� ��������, ��� ��� ��, ��� � ������ ������� �� ����� ���� �����. ��, ��� �������, ��������.";
			link.l1 = "�� ���� ����� �����������. � ������ ���� ������.";
			link.l1.go = "diffindoor_15";
		break;
		
		case "diffindoor_15":
			dialog.text = "�������� ����? � ���-�� �� ��� ����������� ������ ����������? �������� ����� ���. ������ ������� ����?";
			link.l1 = "���. � ���� �� ���� ��� �� �����, ��� � ������: ����� ������ ����������. � ����, ��� ��������� ������... ��, ��������������. � ����� ��, � ����� ������� ���� �� ������� �� ����� � ������ ��������. � ����� ���������� � �������� ����� - �� ������ �������� ���� �� ����.";
			link.l1.go = "diffindoor_16";
		break;
		
		case "diffindoor_16":
			dialog.text = "��� �� ������? ������ ��������? ���� ���� �����? ��� �������� �����...";
			link.l1 = "��, �� �����. �� '����������' ����� ������� �������� ��������, ���� ����� ��� �������. � ��������� ����� � ����, �� �� ������ �� �����.";
			link.l1.go = "diffindoor_17";
		break;
		
		case "diffindoor_17":
			dialog.text = "� �� ����. �� ����, ����� �� ����� ���� �����. ��������, ����� ������� ����? ����� � ��� ����... ������, �� ������� ���-�� ��� �����... �� ����� ��?";
			link.l1 = "��. ��� ���� ���� ����� � ���������. ��� ���������� ��� �� ��������� �������� � ������, ��� �� �� �������� ����� ���� � ��������� ������ ��������. ��� ����� �� ��� �������� �� �������, ����� ������ ��� ��������� ����.";
			link.l1.go = "diffindoor_18";
		break;
		
		case "diffindoor_18":
			dialog.text = "��, ��� ����� �������! ��� ����� ��, ������ �� ��������: ���� ��� - ����� �� ����� � �� ������... �� ���� �� �������������, ��� �� � ����� ������ �� ������� � ������! � ��� ������ �����, ���� ������� �����. ���������, �������, ����� ���������� ��� ������, ��, ��� ����, � ��� ����, ��������� ������ � ���� �����. ��� �� ������������ ������� � ������ ����� ����!\n������� ������, ���� ���������� ��������, ���������� �����-������. � ��� ������ ������������ ���� �� ����: ���������� �������� ����, �������� � �������� � ��� ����������, �������������� �������� � ����, �������� ����� ��������... ��� ����� - ������ ���� �� �����! � �... � ��� ����� ������� ��, ��� ����� ��!\n� ����� ��������� ��� ����, ����� �� ���������� ���� ����� � ����� � ������ ���� ������! ������, ������ ����� � ������� ���������� � ������������� ��������� � ������������� �����, � ����� ����� ��� ��������� ����, ��� ������� �� ��� ������. ���������� ����? ����� �������� �������.";
			link.l1 = "������ �� � ���? �����������!";
			link.l1.go = "story";
			link.l2 = "�����, ������ �� ����� ��� ������������. ���������� �����, �� ���������� ����, ����� �� ����� ������ ��� ������� � ������� �������.";
			link.l2.go = "diffindoor_19";
		break;
		
		case "story":
			dialog.text = "��� ���� ����� �������� ���� ��� ���� �����... � ����� ������� �� ������� - ������, ��� ����� � �����, � �� ���� �� ������ �����. � ����� � ��� ��� ������, � ��� ��� ���������, ����� ���������, �� � � �� ����, �� �� ��� ����� ��������� � ��������� ��������� � ����� ���� ����� �������. ������ ��������... �� � ���������� ��, ��������, ��� ���� ������ � ��������!\n��� ���. ����� ������ �� � ����� ��������� � ���� ������� � ����� ����������� ������. � ���������� � ��� � ���� ������ ����� ������������ ������� ��� ��������� ����� ���, ��� ����� ���� �������� ��������� ��������. ����� ����, �� ���������� ��������� �������� �����, ������ ����� ������� ����� ���������������� ������, ������ ������� ������� ��������\n���� ������� ��������������� ����������: ��������� ��������� �������. �� ����������� ��������������� � ��� ����������� ����������� ��������� � �������� - ��������� ������... ���� ��� �����, ����� ������� � ����������, �� ����� ������� �� �������� - �� �� �����. �� � ����� ����������� �� ���� ������. � ��� ������� ����� ����������� ����, ���� �������� ������ � ���������. �� ����� ������ � ��������� � ���������� ���������\n������������ � �������������� ��������, �� ����� � ����������� ���������� ����� � ������ � ����� - ����� �� ���� �������. �� ������ ��� ���� �����������, ��� �������� ��������� �������� �������� � �������� � ���������� �����������. � �������� � ���������� ����, �...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "idol";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_1";
		break;
		
		case "story_1":
			dialog.text = "�������� ����� ���� �� ��������� ������ ����, � ���� �� ���� ��������� � ������� ������ ������. ���� ������� � �����, �� �������� ���� � ��� - � ��� � �� ���� ��� ��������. �� ����� � ����� ����� � ����� ������ �������� ������ � �������� ���. ��� ��� ���� �������!\n������ ��������������� ���������� � ��� �� ��������: ����� ������ ����������� ����������, ������ �������� ������. �� �������� ���� ���, �� �������� �� ���� � �����.";
			link.l1 = "���, �� �������, ��� ����� � ��������� � ����� ����� ���������: ����� ������ - ���� ����������...";
			link.l1.go = "story_2";
		break;
		
		case "story_2":
			dialog.text = "��������� ���. � �����-������ �� ����� � �������� ���, � ����� �������� ������ �������� ������ � ���� �����. ����� �� �������� ����������� ������������ ����, ����� ����, ��� ����� ��� ��������� � �������. �� ������� �����. ��� ��������� �����������, ����� � �������, ����� �������� ���������� ���. �������, ��� �� ���!\n�� ��� ������ � � �� �� �����... ������ ��������. ���� � ���������, ��� �� ���, �����... �� �� ��� ������ ��������! - ������������ � ����. �� ��� �� ������ ����, ����� ����������� � ��������, ���������������� � ����������� �������� � ������� � ��� � �����. � ���...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "temple";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_3";
		break;
		
		case "story_3":
			dialog.text = "��������, �� ��������� ������������. ���� ������ ����: ��� ������ ������������, ����� �������� ������� � ������ �������������. ��� ����� �� ��������� ���� ��������� �������, � ��� �������� �� ��� ���� ����... �� ��������� ������, �� �������� ������, � ����� �� ���� �� ����� ������� ����� � ������ �������� �����.";
			link.l1 = "��� ��� ��!";
			link.l1.go = "story_4";
		break;
		
		case "story_4":
			dialog.text = "� ��� ������, ��������, � ����. ��...";
			link.l1 = "��� �� ������� ����� � ������ �� ���� ������. �� � ��� ����� ���������� �� �������, � ������ �������, ��� ��� �� �������� ���� ��� ���������. ���������. ��� �� ��������?";
			link.l1.go = "story_5";
		break;
		
		case "story_5":
			dialog.text = "�� ������� �� ����� � ������������ ��������� �� ������ �������. � �������� ���������� ��������� ����� - �� ������ ��� ����� ������ �������� �� ����� ������� �����.";
			link.l1 = "���! ������, ������ �������� �� �������� �����-�� �������� ��������? ��������, � ������� - ����������� ������, ��-��... � ���������� ����� ��������� �� �����? ��� �� �������� ����������?";
			link.l1.go = "story_6";
		break;
		
		case "story_6":
			dialog.text = "������. �� ���� ���� ����������� �� �����������. �������� ��� � �����, � ������ �� ������ ���������� � ����� � ������� ����������� ���, ��� ���� ���������, �������� ����, � ��-�� ���� �������� �������. � ����! ��� ��� ���...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "blackpearl";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_7";
		break;
		
		// ��� ��� ������ ��������, � ����������� ������ �� ����� �������
		case "story_7":
			dialog.text = "... ��� ��� �����!!";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "��� ��� �����? ��. ��� ���?";
				link.l1.go = "story_8_1";
			}
			else
			{
				link.l1 = "� ��� ��� ����� - ��� ��� �����?";
				link.l1.go = "story_8";
			}
		break;
		
		case "story_8":
			dialog.text = "�� ���, ������� �� ������ � '������� ���������'?";
			link.l1 = "��� �� �� ������ � '������� ���������'! � ����� ����� ���������� � ����� ���������� � �������� ��� �������� �� ��� �������: �� �������� ����� ������������ �������, ������������� ���� ����� ������ ����������� �������, ����� ���������� � ������ �������.";
			link.l1.go = "story_9";
		break;
		
		case "story_8_1":
			dialog.text = "��, ��� ��� ��� �����, ������� '�������� ���������'!";
			link.l1 = "���������... ����������� ������. ��� �� �������� �� ���� ���������?";
			link.l1.go = "story_11";
		break;
		
		case "story_9":
			dialog.text = "�-�, �������... �� ������ ���� ��������, � �� ��� ��������� '������� ���������' - �������� ������� �������. �� ������� ������� ���� ������������� � ���. ��� �������, ��� ��� �����, � ��� �������, �����-�� ���� �������� � �������� ������ ��������� �� �����, ��� ������� �������� � ������ � ��� ������� ����������\n����� � ��������� ��� ������ ������ �����, ��� ������� ���������, ������� � ����� � ����������� �������, � ��� ������ - ������ ������ � ������ ���������, ����� ��������� �� ������... ��� ��� ������, ��-��...";
			link.l1 = "������� ��� ������?";
			link.l1.go = "story_10";
		break;
		
		case "story_10":
			dialog.text = "� ����� ���������� �� ������, ��� �� ���... ������� � '������� ����������' �������� ���� ����: ������ ������. �� �����, ����� �����, ���� �������� ���� ��� ������ �������� ��������� �� ���� ����� ������� ������, � �������... ��� �� ���� ������������� ����� � ����������?";
			link.l1 = "�� �� �� ���-�� �������� �� ���� ���������!";
			link.l1.go = "story_11";
		break;
		
		case "story_11":
			dialog.text = "��� ��� ��������� ���� ������� ������� � ���������� ���������, ������� �� ������� �� �����. � �������� ���������� � ���, ���� �������, ��� ���� ���� �������. '������� ���������' �����������, � ������ ����� ��� ��������� ������� � ������ ��� ��� ������, ��������� �������. ������� ����� �������������� � ��� ������, � ���...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "artefact";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_12";
		break;
		
		case "story_12":
			dialog.text = "����� ������� ����� �������� � ��������� ���. ������ ��� ��� ������� - � �� ����. ��� ��� ��������� ����� - ������� ��������... �������� �� ����. �� ����� ����������� � ���������� ��� � ������, ������ ������. ������� �� ��������, ������ �����������, � �����\n����� �� ������ ���� �� ����, �� �������, ��� �������-������� ��� �������� ������� ����� ���������� � �����, ���������� ������ ������� ��������, � �������, ������ �����������, � ���������� ������ �� ������. � �������� ������� �����\n������ �������� ���� ����� ����� �������� ��������� ������������. �� ������ ������� ������� �������� � ������� � �� ��������� ������ ���� ��� ����� �������� �������, ���� ��� ���������� �� ����������� ��������� � ��������� ���...";
			link.l1 = "���� ��� �� �������� ��������� � ����?";
			link.l1.go = "story_13";
		break;
		
		case "story_13":
			dialog.text = "��������. �, ������� ������, ��� ��� ����� ������� ��� � ���� �����. �� ��������� �������, ���������� ���������, ���� ��������� �� ����, �� ��� ������ �������� ��� ����������, ���� �� �� ������� �� ������ ������, ���������� �����-������.";
			link.l1 = "��� �� ������� ���? �� ������� '�������� ���������'?";
			link.l1.go = "story_14";
		break;
		
		case "story_14":
			dialog.text = "��, ���� ������! �� �������� ���!..";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "ending";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_15";
		break;
		
		case "story_15":
			dialog.text = "��������� ������� ���������� �� ���. �� ���� ����� ������� ������, ���� ����������. �� ���� ���������... �� �� �������������, ���. �� ��������� �� ��� ����������, ��� ��������, ������. ����� ��� �� ��������, ��� ����� �������. � �� ������� ������� ��, ��� ������ ���� ������� ��� �����: ������ ���� �����, ������������, �������, ��� �����, � ��������� ���� ������ ��� ���������� �����.";
			link.l1 = "� ��� ��� � ����������...";
			link.l1.go = "story_16";
		break;
		
		case "story_16":
			dialog.text = "��, ������ ���. �� � �������� ����������, � � �� �� ������ �� ������� �� ����. ������ ���� � ������ ������� ������ ���� � �����������.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "��� ��� ��� ���� ������������ �������, ������� ������� '�������� ���������'... �����!";
				link.l1.go = "story_17_1";
			}
			else
			{
				link.l1 = "��� ��, ����������, �����? �������� ����������� �������-�������. ������! �� ������� ������, ��� '������� ���������' � �� ��� ���� �������� ����... ��� ����� ����� ����, ���� �� �� ���?";
				link.l1.go = "story_17";
			}
		break;
		
		case "story_17":
			dialog.text = "�-�, �������, �� ������, ������ ������ �� ������... ��� ��� ������ ����� ��������, �� ����� ��� - ������. ���������, ���������� ��� ���, ��� �������� � ��������, ������� ����� ������...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_17_1":
			dialog.text = "�����, � �����, �� ������ ��� ��� ������ ������ �����. ���������, ���������� ��� ���, ��� �������� � ��������, ������� ����� ������...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_18":
			dialog.text = "������ ������������, ��� ����� ���� �������, ��������� �� ����������� � ����� ������������ � ���� ����������� ��������, �������� �� ����� �����.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "����, ����, ���������. ������, ������ '������� ���������' ������ �� ����������.";
				link.l1.go = "story_22";
			}
			else
			{
				link.l1 = "��, ������, � ��� ��� ��� ������ �� �������. �������� ���������� ���������, ���������� �����...";
				link.l1.go = "story_19";
			}
		break;
		
		case "story_19":
			dialog.text = "����� ����, ��� �� � ����� ������� ��� ��� ������, ��� ������� ����� ��� ������ � ��������� ����... ��� � ����� ��� - �������, ��� ���.";
			link.l1 = "� ��� ��� ������, � ������, ��� �� ����� ���� ��������?";
			link.l1.go = "story_20";
		break;
		
		case "story_20":
			dialog.text = "�� ����� �� ��������� � ��������� �� ������� ���������� ����. ��� ����� �������� � ���� ���-�� � �����-�����, � ���� ��� ������ �� ���������. �� � ������ ����� - �� ������� � �� ���� ��������� ������ �������.";
			link.l1 = "���������� �������. ��� �� ����� ���� ������!";
			link.l1.go = "story_21";
		break;
		
		case "story_21":
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
			pchar.questTemp.NatanStory = "true";
			dialog.text = "��, �� �������... � ����� ���� ����� �� �����.";
			link.l1 = "� � �� ����������... �����, ������� �� ���������� �������! ������ ���� ����� ������� ������ � ����� ����. �� ������ � ������ - ����� �������!";
			link.l1.go = "diffindoor_19";
		break;
		
		case "story_22":
			dialog.text = "�� ��� � ��� ������, ��������? ����� �� �� ����� - ��� ������ �����!";
			link.l1 = "���������, � ��� �� ����� ���. � � ����� ��������, ���� �� � ������� � �����-�� �������� �������� �������� ���� �����, ���� ���. ��������, ������� �� ���������� � �����, ��������� '��� ����������� ������'. ������ �� � ������� �������� '�������� ���������'. �� ����� �� ��������� ���������.";
			link.l1.go = "story_23";
		break;
		
		case "story_23":
			dialog.text = "�� ��� �� ����� ���? �� ����� ����! ��� ������?";
			link.l1 = "�������. ��� ������ �� ��������� ��� �������� � �������� ������ �����, � ����� �����, ��� ��� �� �����. � ����� ����������� ��� ������� ����� ������� ������������. ��-�� � �������� ���� �� ������. �� ��������� ����-����������, ���������, � ���� ������, ����� �����, � ������ ��������� �����. �� ����� ����-������������ �������� ����� ����� � ����� � ���� ��������.";
			link.l1.go = "story_24";
		break;
		
		case "story_24":
			dialog.text = "��� �����! ��� ����� ���. � ����� �� ���� �����?";
			link.l1 = "����� ����� �������� � �������... ��, '�������� ���������'. �� ����� ����, �� ��������� '������� ������', � �������� ����� ��������� �� ������. ��� ������� ������� ����� ��������� ��� ������ �� ������. � ����� � ���� ���������� ����� �� ������, ���������� �����-�� ���� �����������, � ������� �� ��� ����� ��������� ����� ������� �������...";
			link.l1.go = "story_25";
		break;
		
		case "story_25":
			dialog.text = "";
			link.l1 = "...������ �����, � ���� ��������� � �������. � ��� ��� �� ���� ���� ��� ��� ��������� �������, �� �� ������, � ����� ����� � ������� �������, ������, ��� �� ����. �� ������ � ���������� ������� � ���� � ����������, ��� � ������ ������������. ��� ���... ��� ������ '�������� ���������'. � ����� �� ���� �����������.";
			link.l1.go = "story_26";
		break;
		
		case "story_26":
			dialog.text = "������� ���� ����! � �������! ��... �� � ������ �� ����������� ������� ������? ���, � ����, ���� ����� �� ����! �� �� - �����!";
			link.l1 = "��, �����, ��� �� �����, � ����������� ������� ������, ��� � ��. �����, �� � ����� ��� ����� ��������� � �������, ��� � ��� ���� ����� ����.";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
		break;
		
		case "diffindoor_19":
			dialog.text = "�� ������ �������, �������, ���?";
			link.l1 = "��, �����. �������, � ���� ����� �����. ������ ����. ������� - ������ �� ����� �����������, � ����� ��� ����� ������. �� ����� ���������� ��������, � �� ����� ����� �������.";
			link.l1.go = "diffindoor_20";
		break;
		
		case "diffindoor_20":
			dialog.text = "����� ������ � ���� � �������? ������, ������������ �� ���. ��� � ������ ����� �� ���������� - ��� ����� �� �����������, ������� � ����� ����� ��� ���������. � ������� ��, ����� �������, ��� � ����� ������ �� �����...";
			link.l1 = "������� �����������. �� ������� �� ����� ������ � ���, �����. � ������. �������, �� ����� �����. ��� ����������� � ����. �� ������ �������!";
			link.l1.go = "diffindoor_21";
		break;
		
		case "diffindoor_21":
			DialogExit();
			LAi_SetGroundSitTypeNoGroup(npchar);
			NextDiag.CurrentNode = "diffindoor_wait";
			pchar.questTemp.LSC.NatanTalk = "true"; // ������� - �������� � ������� ���������
			AddQuestRecord("BaronReturn", "10");
			npchar.greeting = "nathaniel_1";
		break;
		
		case "diffindoor_wait":
			dialog.text = "�, ��� ��, "+pchar.name+". ��� �� �������� � �������?";
			link.l1 = "�� ����������, �����, ��� ���� �� �����. �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "diffindoor_wait";
		break;
		
		case "danny":
			PlaySound("VOICE\Russian\saga\Nataniel Hawk-03.wav");
			dialog.text = "�������!.. �����! ������� ���!..";
			link.l1 = "...";
			link.l1.go = "danny_1";
		break;
		
		case "danny_1": // ������������ pchar
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Nathaniel"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = "danny_2";
		break;
		
		case "danny_2":
			dialog.text = "������� ����, ����. ������� �� ���, � � ����������� - �� �������...";
			link.l1 = "�� �� ���, �����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "danny_2";
		break;
		
		// � �����-�����
		case "marun_town":
			dialog.text = "��� � ��� ������! ��� �� "+GetFullName(pchar)+" ����������� ��������! �������, �������, �������! ��� ��?";
			link.l1 = "�-�� ���������. � ��, �����? ������, �� ����� ������ � ������ �� �������� � �����. � ��������� ���������. ������� ���� ���������� �� �����!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "��, ���� ����� ������������� �������� �����������. � �������� ���� �����, ��� �� ���� ������������ ���������! � ������ ��������� ��� �� ������!.. "+pchar.name+", � � ���������� ����� ����� �����. � �������: �� ������� ���, �� ���� ����������� ���� ��������, ���������� �����������, ������ ����� ������ ������, ������� ���� �� ��� ������, ������ ��� ����!\n���, ��� �� ���! �� ������ ��� � ����� ��� ������� �... ���� ���. �� ��� ������ ����. ��������. ���� ���� ���-�� ����� ����� - �� ������, � ���� ����������! � �����-����� �� ������ ������� ������, ���������, � ���� ����������� - �������\n���� ������� ������� �� ���� ������� � ������ ���������. � � ������ ����� ���� ����� ���� ��������� �����, ����� ������ ���, ������ ������� � �������� �����. �� � ����� �� ���� �����������.";
			link.l1 = "�������, �����! � �������� ��� ������ ���� � ������ ������� �... ������ � �����.";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			dialog.text = "� ������ ������ ������, "+pchar.name+", � ���������� �������: ������ � ������ ������. ��������, ���� ����������� � ��������� �������� �������� ����� ���������� �����������, � ��� '���������' �������� ������� ����������. ��������� ����� ������ �������� ������� ������������ ���������, ������� ������������ ������� � ������� ��� ����, ���, ����� ���� ����.";
			link.l1 = "�������� �����! ���������!";
			link.l1.go = "marun_town_3";
		break;
		
		case "marun_town_3":
			GiveItem2Character(pchar, "grape_mushket"); 
			GiveItem2Character(pchar, "recipe_grenade"); 
			Log_Info("�� �������� ���������");
			Log_Info("�� �������� ���������� �� ������������ �������");
			PlaySound("interface\important_item.wav");
			dialog.text = "������ � ��� ������, "+pchar.name+"! �� � ����� ����� ����� ���� ���� ������ � ����� ����� ��� � ����.";
			link.l1 = "� ������������� ���� �������� ���. ��� ��� ����� � �����!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "marun_town_4":
			dialog.text = "�, ��� ���� "+GetFullName(pchar)+"! �������, �������, �������! ��� ����? ����� �����-������ ������?";
			// �������
			if (CheckAttribute(pchar, "questTemp.Caleuche.NatanInfo"))
			{
				link.l2 = "�����, � �� ����� ������� ����. �������, �� ��� �� ������� �������� �������� �����������, ��� �� � ����� ���������� � ��������� ����, � ����� ������ '�������� ���������'?";
				link.l2.go = "caleuche";
			}
			link.l1 = "�������, ��� ������! ������ ����� �������� ���.";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "caleuche":
			dialog.text = "�������, �����.";
			link.l1 = "��� ����� ������� �� ���� ������ � ������. ����� �����. �� ������, ��� � ���� ���� ��� �����. �� ������ ������� ����������?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "��, ������� ���� �� ������, �������... ���� ����� ��� - �������. ����� �� ��, ��� ��� �������...";
			link.l1 = "������ ��� ������� ������� ����������, ��� ��, ������� �� �����, � ��� �� �����, � ������� ����� ����.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "� �� ����� ����, ���� �� ��������� ���. "+pchar.name+", �����: ����� ��� ��������! ����� ����� �������, � ��� ������ ���� ����� ����� '�������� ���������'...";
			link.l1 = "� ��� � ��� ����������, ��� ��� ����, ��� �� �� �����, � �������� ������� �� ����. �����, ����������, ��� ��� ���������� ����� ��� � ��������, ��� ������ � �����, ����� ����, ��� ��� ������� ����� ��������-������.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "��... � �� ���� ���� ��������, �������, ��... �� �� �������������, ��� �� ��� � ����� ��������! ����� ��� ��������� �������� ����-����������, � ��� ����� � ����� ����� �� ����������� � �����-����, ��� ��� ���... (�������) ����, ����������: 19 �������� 25 ����� �������� ������, 62 ������� 8 ����� �������� �������.";
			link.l1 = "� ������ � ������... �������, �����!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "�� ���������... ������ �����������. ������ ����� ��� ������������ ����� ��������� ������ � ������ ������. ��� ������ ����� ���� - ��� �������� �������. � ����� ������ ����� � ���������� �� ����. ��� ������ ����� � ����� �������, ��� ��� ����. ����� �������� ���� � ��������� �������� - ��� � ���� ������ ���� ����\n��� ������ ����� � ���������, � ��� � ����� ���������� ������ ��������. ���� � ���� ������� ��������. ������ ����� ��� ������� - ��� � �������. ��������� �� �������� � ��������� �� �������� � �������� �������-��������. ��� ��� ���� � ������ ��� � ��������� �������� �������, ��� ��� ���� ����������\n������ ���������� ��������. �� ����� ����������, � � � ����� �� ������� ���������� ����. ��, � � ��� ������-����� ������ ������. ���� ������ - �������� ��, ��������� ������ � ������� � ��� � ����� �������, ������ ��������� � ��������� �� ������ �������� ���� - ��� ���������� ���������. �������� ����� � ���� �������, � ��� �� �� �������� - �� �����������\n��� ���� �����-�� ��������, �� �� ���� ��� ���� �� ����� ����, ���� � ���-�� � ��� �����! � ���� ��� ���� - ����, � ������� ��� � ����������� �������� �����, � ����� ���������. �� � ���� ����� ���, ��� ��� �������� ���-�� ������� � �������� ������, ��� �������� ��������� �����.";
			link.l1 = "���� �����������. ��� � ���������?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "��������� - �������� ��� � ���������� �������� � �������� ��������� ����������. ��� ������ ������������ ��� ������ - �� �������� ��� �� ������ ������ ����������. �� ��������� �����, ������, ���� �� ������ ������� �� ��� ����, �� � ������� �������. ��� ���� ���-�� ����� �������� ����������, ����� ������� ���� ������������ � ����� �� �����\n�� ����� ������� �� - ��� �������� ������������� ������������. �� ������ ����� ����� ��� �������, ���� �� ��� - �������, �� ����� �� ���� - �� �����, ��� ��� ���� ����� �� �����! ������ ������ ��������� ���� �� ������ ����. ��� ����� ��� ���� ������, � ������������� ����, � ����� - � ����� ������ �����\n���, � �������� ������ � ���� �����, �� � ����� � ������� ���������� ��������. ��� ���� ����� - � ���� �����������.";
			link.l1 = "� ��� ��������. �������, ���������. �� ��� ����� �����.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "������ ����, "+pchar.name+". �������� � ���� ����� ����� ����������. ���� ������������ ��� - � �� ���������� ��� ������.";
			link.l1 = "Praemonitus praemunitus, �������. ��� ������������ - ��� ��������, � � - ������������. ��� ���� � ����. �� �������!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "�����, "+pchar.name+"!";
			link.l1 = "�������!";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NatanStory");
			DeleteAttribute(pchar, "questTemp.Caleuche.NatanInfo");
			AddQuestRecord("Caleuche", "35");
			NextDiag.CurrentNode = "marun_town_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}