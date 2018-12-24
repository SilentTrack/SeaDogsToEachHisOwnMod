// ������ �������� � ����������
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "�� � ��� ��������!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> ������� � ���������
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("�����������","����� ����") +" ����� ��������?", 
				"����� ��, "+ GetSexPhrase("�����������","����� ����") +".", 
				""+ GetSexPhrase("����������� ����� ��������. �� ����� �� ����.","����� ���� ����� ��������.") +"",
                "���� ������� �� ��� ���������"+ GetSexPhrase("��� �����","�� ������") +".", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��.", 
				"��, ����� �.",
                "����� ��������.", 
				"� ���� ���"+ GetSexPhrase("","�") +" ���� ������.", npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		
		case "IndPearlMan_1":
			dialog.text = "������, ����� ����"+ GetSexPhrase("��","��") +".";
			link.l1 = "�� ������ ����������, ��������� ���� �����"+ GetSexPhrase("","�") +"...";
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat("����� ������� ����� ��������?", 
				"����� ��, �������?", 
				"����������� ����� ��������.",
                "���� ������� �� ��� ������������ �����...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��.", 
				"��, ����� �.",
                "����� ��������.", 
				"� ���� ��� ���� ������.", npchar, Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(""+npchar.name+" ������� ����, ��� ����.","��� �� ������ �� "+npchar.name+", �����������?","��� ��� ������� ��� ����� ����, ���������.");
			if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase("� ���� ���� ���-��� ��� ����. ������ ����������?","������, ������ ���� ���-��� ����������? ���� ����������...","� ���� ���� ���-���, ��� �������� ����, ���� ��������... ������ �������?");
				link.l1.go = "gift";
			}
			link.l9 = "�� ������ ����������, ������ ��������� ���� �����...";
			link.l9.go = "exit";
		break;
		
		case "gift":
			iTemp = 2;
			dialog.text = RandPhraseSimple(""+npchar.name+" ������ ����������. ����������.", ""+npchar.name+" ���������. �������� ���.");
			if (CheckCharacterItem(pchar, "mineral6"))
			{
				link.l1 = "�������� ���������.";
				link.l1.go = "gift_1";
			}
			for (i=50; i>=47; i--)
			{
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = "�������� "+XI_ConvertString("jewelry"+i)+".";
					link.(sTemp).go = "gift_"+i;
					iTemp++;				
				}
			}
		break;
		
		case "gift_1":
			RemoveItems(pchar, "mineral6", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "��! ������ "+npchar.name+" ������ �������� �� ���� �� ������ � ������ ����! �������, ������ ���������!";
			link.l1 = "�� ����������, ������������ ���� ������ �������...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_47":
			RemoveItems(pchar, "jewelry47", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "��! ����� �������! ���� ������� ��� "+npchar.name+"? �������, ������ ���������!";
			link.l1 = "������ �� ���� ������� �����, ��������, ���� ��� ������...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_48":
			RemoveItems(pchar, "jewelry48", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "��! ����� �������� ��������� �������! ��� ��� "+npchar.name+", ��? �������, ������ ���������!";
			link.l1 = "������ ��� �� ���� �������, ����� �������� ������������...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_49":
			RemoveItems(pchar, "jewelry49", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "��! ���� ������������ ������� ���� - ��� "+npchar.name+"? ����� �������! �������, ������ ���������!";
			link.l1 = "������ ��� ���� �����, ���� ������, ����� ��� �����������...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_50":
			RemoveItems(pchar, "jewelry50", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "��! ����� ������������� ������� ������! ��� ������� ��� "+npchar.name+"? �������, ������ ���������!";
			link.l1 = "�� ����� ����� ��� ����� ���������� ������ ���������, �������...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_exit":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) // Addon 2016-1 Jason ��������� �������
			{
				dialog.text = "�� ������ ���-�� �������� � "+npchar.name+", ��� ����?";
				link.l1 = "��, ���������. � � ��� �������� ����� ���������� � ������, � ��������� �������� ����� ��� � ���� ����������. � ����� ����� ����, ��� ������ �� ����: ��� ������ �������� �����, ��� � ��� ����. � ���� ����� ��������: �������� ���������, ���������� ������������� �����, ���������, ��������, ��������, ������. �����, ���� ��� ������� ��� ������?";
				link.l1.go = "hayamee";
			}
			else
			{
				DialogExit();
			}
			ChangeIndianRelation(0.75);
			npchar.quest.gift = true;
		break;
		
		// Addon 2016-1 Jason ��������� �������
		// �������, ����� ������� ��������
		case "cumvana":
			dialog.text = "�������������� ����, ��� ����. � - �������, ����� ���� �������� ������� ������. ����� ���� ������� ���� � ���� �������?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "� ������ ���� �������, �����. �������, ���� ����������.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "�����, � ������ ������� ���� � ������. ��� ����� ������ � ��������� �������� ��� ��������� ������ - ��� ��������� � ����� ������ ����� ���, �� � �� ���� ������...";
				link.l1.go = "cumvana_no";
			}
		break;
		
		case "cumvana_no":
			dialog.text = "� ��� ����� ������ ��� ����, ��� ����, ��� �� �� ����� ������ ����. ���� ������ ����� ���, ����� �������� �������� ����� ������. ��� ��������� ������, �-��! � ������� �� ������ � ��� ��������� ���������. ��� ����� - ������ �����, � �� �� ����� �� ����� ������� ������. ������� �� ����� ���� ����� ����.";
			link.l1 = "�� ������� �� ���-�� ������ ����! �� � � �� ����� ���� ��������...";
			link.l1.go = "cumvana_no_1";
		break;
		
		case "cumvana_no_1":
			dialog.text = "� ���� �� �������. ��� �������� �������� �����, ��� ������� ���� ����� � ����. ������� ��� ������.";
			link.l1 = "��� ��������...";
			link.l1.go = "cumvana_no_2";
		break;
		
		case "cumvana_no_2":
			DialogExit();
			AddQuestRecord("Roger_5", "5");
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_1":
			dialog.text = "�-��! ��� ����� ��, ��� ����. ��� �� ������ ������� �������?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "� ������ ���� �������, �����. �������, ���� ����������.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "������� ����� ������ �� ��������� ����...";
				link.l1.go = "cumvana_1_1";
			}
		break;
		
		case "cumvana_1_1":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_2":
			dialog.text = "������ ������ ���� ������ �������.";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0)
			{
				link.l1 = "�������� �������� �������."; // 5
				link.l1.go = "cumvana_2_1";
			}
			if (CheckCharacterItem(pchar, "compass1")) // 3
			{
				link.l2 = "�������� ������.";
				link.l2.go = "cumvana_2_2";
			}
			if (GetCharacterFreeItem(pchar, "spyglass1") > 0)
			{
				link.l3 = "�������� ������� ��������� �����.";
				link.l3.go = "cumvana_2_3";
			}
			if (GetCharacterFreeItem(pchar, "spyglass2") > 0)
			{
				link.l4 = "�������� ������� ��������� �����."; // 2
				link.l4.go = "cumvana_2_4";
			}
			if (GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l5 = "�������� ������� ��������� �����."; // 4
				link.l5.go = "cumvana_2_5";
			}
		break;
		
		case "cumvana_2_1":
			Log_Info("�� ������ �������� �������");
			Log_Info("�� �������� �������");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "pistol5", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_3");
			dialog.text = "�-��! ����� �������� ������ �����������! ������� ������� ���� �������. � ��, ��� ����, ����� ������� �� ������� � ����� ������.";
			link.l1 = "�������, �����!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_2":
			Log_Info("�� ������ ������");
			Log_Info("�� �������� �������");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "compass1", 1);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "�-��! ������������ ������ �����������! ������� ������� ���� �������. � ��, ��� ����, ����� ������� �� ������� � ����� ������.";
			link.l1 = "�������, �����!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_3":
			Log_Info("�� ������ ������� ��������� �����");
			Log_Info("�� �������� �������");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass1", 1);
			GiveItem2Character(pchar, "obereg_2");
			GiveItem2Character(pchar, "indian_5");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "�-��! ���������� ����� �����������! ������� ������� ���� �������. � ��, ��� ����, ����� ������� �� ������� � ����� ������.";
			link.l1 = "�������, �����!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_4":
			Log_Info("�� ������ ������� ��������� �����");
			Log_Info("�� �������� �������");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass2", 1);
			GiveItem2Character(pchar, "obereg_6");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "�-��! ���������� ����� �����������! ������� ������� ���� �������. � ��, ��� ����, ����� ������� �� ������� � ����� ������.";
			link.l1 = "�������, �����!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_5":
			Log_Info("�� ������ ������� ��������� �����");
			Log_Info("�� �������� �������");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass3", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_5");
			dialog.text = "�-��! ���������� ����� �����������! ������� ������� ���� �������. � ��, ��� ����, ����� ������� �� ������� � ����� ������.";
			link.l1 = "�������, �����!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_3":
			dialog.text = "����� ���� ������� ���� � ���� �������, ��� ����?";
			link.l1 = "�����, � ������ ������� ���� � ������. ��� ����� ������ � ��������� �������� ��� ��������� ������ - ��� ��������� � ����� ������ ����� ���, �� � �� ���� ������. ��� �� �� �� ����� ��������� ����� ����� ������ �������, ������� ������ �� �������� ���� ����?";
			link.l1.go = "cumvana_4";
		break;
		
		case "cumvana_4":
			dialog.text = "�-��! ������ ���� ����� ���������. ���� ������ ����� ���, ����� �������� �������� ����� ������. ��� ��������� ������! ��� ����� - ������ �����, � �� �������� ����� ����� ������.";
			link.l1 = "��� ����� ���� ������� � ������. �������, ������ ����� ����� - ���������� �� ��� �������������� � ����� ������? ��� ���� �������, ������ ��������� � �� ������ �� ������. ��������� ����� ��� �������� �������, � �� ������ ������� ������� �������.";
			link.l1.go = "cumvana_5";
		break;
		
		case "cumvana_5":
			dialog.text = "������, ��� ����. � ������ ����� ������ � ������� �� ���� �������. ������� ������ ����� ������ ������, � ���� �����.";
			link.l1 = "�������, �����!";
			link.l1.go = "cumvana_6";
		break;
		
		case "cumvana_6":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "6");
			pchar.quest.mtraxx_merida_wait.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait.win_condition.l1.date.hour  = 7.0;
			pchar.quest.mtraxx_merida_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait.function = "Mtraxx_MeridaCumvanaTimer";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
		break;
		
		case "cumvana_7":
			dialog.text = "�-��! ��� ����� ��, ��� ����. ��� �� ������ ������� �������?";
			link.l1 = "���� ������, �����...";
			link.l1.go = "cumvana_7x";
		break;
		
		case "cumvana_7x":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
		break;
		
		case "cumvana_8":
			dialog.text = "��� � ��, ��� ����. ������� ������� � ����� ������.";
			link.l1 = "� ����� ���������? ���� ����������?";
			link.l1.go = "cumvana_9";
		break;
		
		case "cumvana_9":
			dialog.text = "� ��� ����� ���� ��������� ��������, ������� ������ ����. �� ��� ������� ������ - ������ ����� �� ����� �����. ���� �� ����� - �������, ������ �������� ��� �����. ������ �� ������ �����.";
			link.l1 = "��� ����� ������� ����� ��������! ����� ����� ������ ��� ����� ������� � �������� - �� �� ������� ����!";
			link.l1.go = "cumvana_10";
		break;
		
		case "cumvana_10":
			dialog.text = "��� ����, ��� ����. ��� �������� ������. ������ �������, ����� ������� ����. ����� �� ������� ��������� ���� �����.";
			link.l1 = "������, ����� ����� ��� ��������� ������? ��������?";
			link.l1.go = "cumvana_11";
		break;
		
		case "cumvana_11":
			dialog.text = "����� ������� ����, ���� ������� ����� �� ����, ����� ���������� � ������������ �����. ����� �� ��� - ������� � ������ � ���������. ���� ������ ����� ���������. �� ��� �� �����, ��� ����.";
			link.l1 = RandSwear()+"��� �� ��� ������? ��� ��� ��������� ����� ���������?";
			link.l1.go = "cumvana_12";
		break;
		
		case "cumvana_12":
			dialog.text = "������� ������ ������ �������, ��� ����.";
			link.l1 = "�����...";
			link.l1.go = "cumvana_13";
		break;
		
		case "cumvana_13":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "7");
			pchar.questTemp.Mtraxx = "merida_advice";
		break;
		
		// ������
		case "hayamee":
			if (npchar.id == "Hayamee")
			{
				dialog.text = "��� ��� ������ ������ ������� �����. �-��! "+npchar.name+" ��������� ���� ���. "+npchar.name+" ����� ������ � ������ ������ � ������. ������ ������. ������ �����, ��� ��������� �������.";
				link.l1 = ""+npchar.name+", � ��� ����� �������� ���� � ������, ���� �� �������� ��� ����. ��� ���������� � ����� �����?";
				link.l1.go = "hayamee_1";
			}
			else
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("��� ��� �� ������ � ������, ��� ����. �� ������ � ���� ����. ������� �����, �-��!","��� ��� ������� �������, �-��, �� �� �� ������ ��� ������� � �������."), RandPhraseSimple("����� ������ ��� ��� �� �����. ������ �� ������ ������� � ������ ������, ����� � ���, �-��!","����� ��� ����� �� ��� ��� � ������ ������� ��� ����� ������. ������ �� �� ������ �� ����� ������ �� �������, �������! �-��!"));
				link.l1 = LinkRandPhrase("����� ����...","��� ��������...","����� ������..."));
				link.l1.go = "exit";
			}
		break;
		
		case "hayamee_1":
			dialog.text = "������ ���� �� ����� ���� �����. ������� ��������� ������ � ����� ������. ��������� ������ ����� �����, ��� ����. � ���� ������ � ������ � ��� ������. � �������� ���, ����� �� � ����, ��� ���.";
			link.l1 = "������� ������, ��� � ��� ��� ��� ����� �������� ��������. � ���� ����� ���������.";
			link.l1.go = "hayamee_2";
		break;
		
		case "hayamee_2":
			dialog.text = "�-��!";
			link.l1 = "...";
			link.l1.go = "hayamee_3";
		break;
		
		case "hayamee_3":
			DialogExit();
			AddQuestRecord("Roger_5", "9");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.hour  = 22.0;
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.function = "Mtraxx_MeridaHayameeTimer";
		break;
		
		case "hayamee_4":
			pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
			dialog.text = ""+npchar.name+" ���� ������ ���� ����. ������ ���������. �� �� ������ ������� ����� ������ � ������ ������. �� ������ ���, ������ ��������. � ���� ��������.";
			link.l1 = "������, "+npchar.name+". ���� ��� �������� ��� � ������?";
			link.l1.go = "hayamee_5";
		break;
		
		case "hayamee_5":
			dialog.text = "������ ����������� �������� ���� ����� ����� ������ � ��������� �������. �� ���� ��������� �������...";
			link.l1 = "�����?";
			link.l1.go = "hayamee_6";
		break;
		
		case "hayamee_6":
			dialog.text = "�� �������� ������ �� ����-������. ������ �� �������� � ����� �� � ������, �� � �������. ���� ��� ������� ���������, �� ������ �������� � �������, � ��� ����� �� ����� - �� ������ ������� ������.";
			link.l1 = "�������. �� ������������ � ����� ����, ��� �����������. ������, �� ����� ������ ��������� �� ���������� ����.";
			link.l1.go = "hayamee_7";
		break;
		
		case "hayamee_7":
			dialog.text = "�-��! ������ ������ �������� �� ��� ���� ��� �������: ���� ��������, �������� ����, ������ �������, �������� ������ �������, � �����, �������, ������� ������ �� ��� ���� ��� ����, � ������ �������.";
			link.l1 = "���! �� ���� ��� ����������� � ������, � ������... ������. ��� ���?";
			link.l1.go = "hayamee_8";
		break;
		
		case "hayamee_8":
			dialog.text = "������ ������ ��������� ���� �����.";
			link.l1 = "��������� �����? �����. ��� ���?";
			link.l1.go = "hayamee_9";
		break;
		
		case "hayamee_9":
			dialog.text = "��� ������ ���. � "+npchar.name+" ������ �������� ����. ������ ������ � ������� ������� ������ � ���� �� �����-����� ������� ��������� ������. "+npchar.name+" ������ ����� � ����� ���� � ���������.";
			link.l1 = "������� ������ � ������� � ���������� ����?";
			link.l1.go = "hayamee_10";
		break;
		
		case "hayamee_10":
			dialog.text = "���� ������ ����� �� ������. �� ���������, � ����� ���� ��� ������.";
			link.l1 = "�������? ���������� ��������?";
			link.l1.go = "hayamee_11";
		break;
		
		case "hayamee_11":
			dialog.text = "�-��!";
			link.l1 = "���, "+npchar.name+" ����� ���� � ����������! ������, ����� ���� � ������ ���������, � ���� ����������.";
			link.l1.go = "hayamee_12";
		break;
		
		case "hayamee_12":
			dialog.text = "�������� ����� ��� ���� "+npchar.name+", ��� ����. � ����� ������ ������� ���� � ���� �����. �� �� ������ ����� - ����� �������� ���� �� � ������ ������ ����� � �������� ������� �� ��������. � ������ ����, "+npchar.name+" ������ �����.";
			link.l1 = "� �� �������� ���� ����� �����. �� �������.";
			link.l1.go = "hayamee_13";
		break;
		
		case "hayamee_13":
			DialogExit();
			AddQuestRecord("Roger_5", "10");
			LAi_CharacterDisableDialog(npchar);
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeLate", 0, 0, 15, false); // ������
			// ������ � ������� ���������
			pchar.quest.mtraxx_merida_wait2.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.hour  = 9.0;
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.function = "Mtraxx_MeridaTagofaHide";
		break;
		
		case "hayamee_14":
			bOk = GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0;
			dialog.text = "�� �������� ��, ��� ������� "+npchar.name+" � ������?";
			if (bOk && GetCharacterFreeItem(pchar, "pistol3") > 0 && GetCharacterFreeItem(pchar, "pistol5") > 0 && GetCharacterItem(pchar, "bullet") >= 30 && GetCharacterItem(pchar, "grapeshot") >= 30 && GetCharacterItem(pchar, "gunpowder") >= 60 && CheckCharacterItem(pchar, "jewelry41") && CheckCharacterItem(pchar, "jewelry42"))
			{
				link.l1 = "��. ���, ��� �� ����������.";
				link.l1.go = "hayamee_15";
			}
			else
			{
				link.l1 = "���, � ��� ������� ��� ����.";
				link.l1.go = "hayamee_14x";
			}
		break;
		
		case "hayamee_14x":
			DialogExit();
			npchar.dialog.currentnode = "hayamee_14";
		break;
		
		case "hayamee_15":
			pchar.quest.Mtraxx_MeridaHayameeLate.over = "yes";
			Mtraxx_MeridaRemoveGifts();
			dialog.text = ""+npchar.name+" ����, ��� ����. ������ � ������� ����. �� ����� � ����� � �����. �� �������, ��� �� ������� "+npchar.name+"!";
			link.l1 = "��-��, � ������ �� �������.";
			link.l1.go = "hayamee_16";
		break;
		
		case "hayamee_16":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7.0);
			DoQuestFunctionDelay("Mtraxx_MeridaTagofaEnter", 20.0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
			
		case "CitizenNotBlade":
			dialog.text = "������� ������, �������, ���� �� �� ��������� ���� ��� �������!";
			link.l1 = LinkRandPhrase("������.", "�����.", "�� ���������, ��� ������...");
			link.l1.go = "exit";
		break;  

	}
}
