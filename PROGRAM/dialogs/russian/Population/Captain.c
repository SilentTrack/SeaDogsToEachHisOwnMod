//Jason ����� ������ ����������������� �� ������ ���������
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//������ �������
			if (npchar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//�������� ��������������� ���������
				{
					dialog.text = "��. �� ������ ��� ������ "+NationNameGenitive(sti(pchar.nation))+", ��������. � ���� ��� �������� ������� � ����� �������� - ����� ������� �� ���������... ������ ����� �������!";
					link.l1 = "�� ���� ��, ��� - �������, � ��� ���� ��...";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(npchar, "quest.march") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && GetCompanionQuantity(pchar) < 5)//������ ������������ ������ 2015
				{
					dialog.text = "��! �� ����� �������, �������... � ���� � ��� ������� �����������. � ��� ���� ���� ��������� �����?";
					link.l1 = "���. � ���������, �������. ���-������ � ������ ���.";
					link.l1.go = "exit_quest";
					link.l2 = "����. � ����� ��� ���������. ���� ����������? � �������?";
					link.l2.go = "march";
					break;
				}
				dialog.text = "��, ����������� ���, �������! ������� ������ �������������� ��������!";
				link.l1 = "��� �������, ���������! ��� ��� - "+GetFullName(pchar)+". �� �������� ������� ���������?";
				link.l1.go = "question";
				npchar.quest.meeting = "1";
			}
			else
			{
				//��������� ���������
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "� ���, ��������� ���������? � �� �����, ����� ���� ����������� � ����� � "+NationNameAblative(sti(pchar.nation))+"! ����������, �� �� ����� ������ ������!";
					link.l1 = "�����-�����, �� ��������. �����.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "��� ��� ����?";
					link.l1 = "������.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" � ����� �������, ��������! ��� �� ������ ������?", 
				"��� ���������, �������!", 
				"��, �������, � ���� ���� ��� �����...",
                "� ���������, ��� ���� ����. ����� �������!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�����, ���������� ��� ����������?", 
				"�����, ���������� ��� ����������?",
                "�����, ���������� ��� ����������?", 
				"��, �������. ����� ���!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_landcaptain", "rumours_landcaptain", "rumours_landcaptain", "exit", npchar, Dialog.CurrentNode);
		break;
		
		//��������� �����
			case "march":
				dialog.text = "���, �������, �� ����� � � ������� ����� ������ ����, � ��� ��� �� � ����, ������ ���. ���� ������ � ���, ����� ���-���� ���������� ��������, ��� ���... ������� ����� ���������� � ���� �� �������.";
				link.l1 = "������... ��� � ��� �� ����� � ��� ����������?";
				link.l1.go = "march_1";
				link.l2 = "���-�� ��� ��� ������� ��������������... ���, �������, � �������� �� ������ �����������. ��������, ������!";
				link.l2.go = "exit_quest";
			break;
			
			case "march_1":
				//���������� � ���������� ��������� � ����, �.�. ����� ����� �� ����� ��������� �������� :(
				pchar.GenQuest.MarchCap.Startisland = Islands[GetCharacterCurrentIsland(PChar)].id;
				pchar.GenQuest.MarchCap.Parts = GetCompanionQuantity(pchar)+1;
				pchar.GenQuest.MarchCap.shiptype = SelectCaptainShipType();
				pchar.GenQuest.MarchCap.shipname = GenerateRandomNameToShip(sti(npchar.nation));
				pchar.GenQuest.MarchCap.nation = sti(npchar.Nation);
				pchar.GenQuest.MarchCap.model = npchar.model;
				pchar.GenQuest.MarchCap.rank = sti(npchar.rank);
				pchar.GenQuest.MarchCap.name = npchar.name;
				pchar.GenQuest.MarchCap.lastname = npchar.lastname;
				pchar.GenQuest.MarchCap.BaseNation = npchar.nation;
				pchar.GenQuest.MarchCap.Nation = drand(HOLLAND);
				pchar.GenQuest.MarchCap.basecity = npchar.city;
				dialog.text = "��� ������� - "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.shiptype), "Name")))+" '"+pchar.GenQuest.MarchCap.shipname+"', ����� �� �����. �� �����������, �������: ����� ����� ����� � �������� ��������� �����!";
				link.l1 = "�������. ���������� ������� � ��� �������. �� �������!";
				link.l1.go = "march_2";
			break;
			
			case "march_2":
			DialogExit();
				LAi_SetActorType(npchar);
				LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 30.0);
				npchar.lifeday = 0;
				pchar.quest.MarchCapOver.win_condition.l1 = "Timer";
				pchar.quest.MarchCapOver.win_condition.l1.date.hour  = sti(GetTime() + 6);
				pchar.quest.MarchCapOver.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.MarchCapOver.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.MarchCapOver.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.MarchCapOver.function = "MarchCap_Over";
				pchar.quest.MarchCap_Create.win_condition.l1 = "location";
				pchar.quest.MarchCap_Create.win_condition.l1.location = pchar.GenQuest.MarchCap.Startisland;
				pchar.quest.MarchCap_Create.function = "MarchCap_Create";
				log_Testinfo(pchar.GenQuest.MarchCap.Startisland);
			break;
			
		//��������� �� ����������� ������ �� ���������� ���� citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "����������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ���������� �������.", "������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ���������� �������.");
			link.l1 = LinkRandPhrase("������.", "�����.", "��� �������...");
			link.l1.go = "exit";
		break;
		
		case "exit_quest":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

int SelectCaptainShipType()
{
	int iType;
	if (sti(pchar.rank) >= 19) iType = SHIP_FRIGATE_H;	
	if (sti(pchar.rank) >= 13 && sti(pchar.rank) < 19) iType = SHIP_GALEON_H + drand(makeint(SHIP_FRIGATE_H - SHIP_GALEON_H));	
	if (sti(pchar.rank) >= 8 && sti(pchar.rank) < 12) iType =  SHIP_CORVETTE + drand(makeint(SHIP_POLACRE -  SHIP_CORVETTE));
	if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 8) iType = SHIP_BRIGANTINE + drand(makeint(SHIP_GALEON_L - SHIP_BRIGANTINE));
	if (sti(pchar.rank) < 5) iType = SHIP_CAREERLUGGER + drand(makeint(SHIP_SLOOP - SHIP_CAREERLUGGER));
	
	return iType;
}