// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "��������, � ������.";
			link.l1 = "� "+ GetSexPhrase("������","��������") +". ��������.";
			link.l1.go = "Exit";
			//--> ����� ��������
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "������, � ��� �����, ��� � ��� � ������ ���������� ������� �� ����� ����� �����. ����� �� ���� �� ���-������ ���������������� ��� ������������?";
                link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "������, � ����� �� ������ ������������ ����� ������. � ����� ����� �� ��� ���� � ����������, � ������ ����, ����� ����� �������� �������� ���. ��� ��� �������� ������, ������������.";
                link.l1.go = "Sharlie_3";
			}	
			//<-- ����� ��������
		break;
		
		//--> ����� ��������
		case "Sharlie":
			dialog.text = "�, ���� �����? �� ���� � ���� � ������ ���������� ��������� ����� �����, �� ������ �� ������� �, ����� ���� - ���� ����������. ������ ��� ������ �����. � ��� ��� �� ��� ������, � ���� �� �������� ��� ����� - ����� ������ �� ��������.";
			link.l1 = "��. �� ��� �� �� ������ ���������� �����, �������� � ������?";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "� ���, �����, ���� �� ��������.";
			link.l1 = "�������... � ������� �� �� ������, ���� ����������?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "�� ����. �������� � ���������� - �� ��� �������� ��� ���������.";
			link.l1 = "�������. �� ��� ��, ������� �� ����������, ������.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskiper";
		break;
		
		case "Sharlie_3":
			Log_Info("�� �������� �������� ��������");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			dialog.text = "��. �� �����. �� ������������� ������, ����� � ��������� ����� ������������?";
			link.l1 = "��. ����� ��� �� ��� ������ ��� ������? � ���� ���� ������ ��������� ��� ���������� ���������� �����.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "������, �����. � �� ���� ������ ��� ����������. ������ ������ ��������. �� � ������ ����� ������ ������������ ���, ��� ���� ��� ���������� �� ��� ��� ������ �� �����������, ��� ��� �� ������� �� ��� ���� ������� �������.";
			link.l1 = "� ���� ���, ������. � ������ � �� ����� ������� ������ ��������.";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "��, �������. �������! �������� ���� ������������ ������ ������!";
			link.l1 = "...";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			DialogExit();
			chrDisableReloadToLocation = true;//������� �������
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//��������� �������
			// ������������ ��
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto17"); // 170712
			//������� ��������
			ref sld = GetCharacter(NPC_GenerateCharacter("Folke", "DeLuck", "man", "man", 1, FRANCE, -1, false, "quest"));
			sld.name = "�����";
			sld.lastname = "�����";
			sld.greeting = "officer_hire";
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Folke";
			LAi_SetImmortal(sld, true);
			sld.CompanionDisable = true;
			sld.rank = 5;
			LAi_SetHP(sld, 90, 90);
			sld.money = 0;
			SetSelfSkill(sld, 25, 28, 21, 24, 22);
			SetShipSkill(sld, 10, 5, 24, 22, 25, 15, 5, 15, 18);
			SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "BasicDefense");
			GiveItem2Character(sld, "unarmed");
			EquipCharacterbyItem(sld, "unarmed");
			ChangeCharacterAddressGroup(sld, "Fortfrance_prison", "goto", "goto23");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "FolkeStay", -1);
			pchar.questTemp.Sharlie = "takeskiper";
		break;
		//<-- ����� ��������
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}
