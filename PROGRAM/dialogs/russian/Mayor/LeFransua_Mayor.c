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

			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "� �� ������ ������ ��������.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "���������� " + NPChar.name + ", � �� ������ ������ ���������.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "� �� ������ ������ ��������.";
					link.l1.go = "CapComission6";
				}
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "� ������, ��� �� ����������� ��������, ��������� � ����������...";
				link.l1.go = "Marginpassenger";
			}
		break;
		
		
		case "CapComission1":
			dialog.text = "��-��. �� �������, � ���� ������ ���� �������? �������, ���� ��������� ������ � ����?";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName + ". ���� �����?";
			link.l1.go = "CapComission2";
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "���. � ��� ������ � �������� ������ ����� ���������� � ��������� - ���������� ������, �� ������� �� ������� ������.";
				link.l1 = "��� ����...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				pchar.quest.CaptainComission_SellSlave.over = "yes";
				dialog.text = "�-�, �� �������-��. � �� ���� ��������� ������� ��� � �������� ������ ����� ���������� � ���������, �� ������ ��������� � ���� ����� ������-������... �� ����� ����"+ GetSexPhrase("��","����") +"?";
				link.l1 = "������, "+ NPChar.name +", ��� ����� ����... � �����, � ���� ��� ����� �����. �� � �����" + GetSexPhrase("","�") +" ����������.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "������, ��� �� ������. ��� ������ - 150000 ����. ��� � ���� ��� �������?"
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "����� �� �����"+ GetSexPhrase("��","���") +"... � ������, ���� ��������� � ���� ����� �����? �, ��������, ��� ������������� ����� ��������.";
			link.l1 = "�� � �� ��������� ���� ������������� � �������"+ GetSexPhrase("","�") +".";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "��, �������"+ GetSexPhrase("","�") +" �� - ��� � ���� ��������?";
			link.l1 = "������, � �� ������� ������, ���� �� ������?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "�-�, �� ������, �������, �� � ���� �� �����. � �� �������� ������, ��-��-��-��... ��, �����.";
			link.l1 = "���������.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "���-���... ���� � ���� ���� ����... ���� �� ����, ��� ������... � �����, ����� ������� �� ��� ������ ������������ ������.";
				link.l1 = "� ����� ������ ������ ��� � ��������?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "��, " + pchar.name + ", �� �� ������, ��� ��� ���� �� ��������. ������� � �������� � �������� ������ ��������, ��-��.";
				link.l1 = "�� �����, �� �������.";
				link.l1.go = "exit";
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					AddQuestRecord("CaptainComission1", "31");
					AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
				}	
				pchar.GenQuest.CaptainComission.RepeatSpeak = true;
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "��, ��������� ��, ��� ��������� ���� �� ��������... ��� �� ������ ��� �����, ��� ����� ������ ����� � ������� ������� �������� ��� �� ��� ����� ������. ����, ���� �� ���������� � ���������� - � �� ��������.";
			link.l1 = "� ������ ���� �� ������� �� ��� ����� �����?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "��... � ����� ����� " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " ������ ����� �������, ��� � ����� ������� ���� " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + " ���� � �� ����. ������� ��� ������� � ����� � �� ���� ����� '" + pchar.GenQuest.CaptainComission.ShipName1 + "' � '" + pchar.GenQuest.CaptainComission.ShipName2 + "' ���� � " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl") + ". ��������� ������, ������ � �� ���� �������� ��� ���� ����� �����?";
			link.l1 = "�������. � ������� � ���� ���� �������?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "�����, ���� 12-15, �� ������. ��� �����, ���� ��� �� ������ ��������� �� �������, ����� ������ �� � ������ ������ �� ����� �� ����� ������. �� ����� ����� ����� ��� ����.";
			link.l1 = "������, � ������ �� ��� ����. ���������� ������.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);	
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
		break;
		
		case "CapComission2_3":
			dialog.text = "�� ���������. ��� ���� �������� ��� � ���� �� ����... � �� ���� ���?";
			link.l1 = "�����. � �������� ��������� ��� ������������.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "�-�, ��� ������. � �� � �� ���� �����������, ��� ����������, �������� ����� ������ ���� �� ������ ��������. ��-��-��-��... ��, �����.";
			link.l1 = "���������.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));			
			addMoneyToCharacter(pchar, -150000);
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission3":
			dialog.text = "�� ���, " + GetFullName(pchar) + ", ������ �� ��� ����� ��������?.. ��-��-��...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "���. � �� �����"+ GetSexPhrase("","�") +" �� �������. � �� �������� ���� ��� ��� �� ����������.";
				link.l1.go = "CapComission4";
			}
			else
			{
				if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
				{
					link.l1 = "��, ��� � �������������� - ��������"+ GetSexPhrase("","�") +" ������� ����.";
					link.l1.go = "CapComission5";
				}
			}	
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "׸��! ���������� - �� ����������, ����� ������ �������? �� � ��� �� ���������� ������?";
			link.l1 = "�����, � ���� ���� �����-������ ��������� �������? ";
			link.l1.go = "CapComission4_1";
			link.l2 = "������, " + NPChar.name + ", ������ ��� ����� �������� ���������...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "���.";
			link.l1 = "...��, ����� ��������� ����������...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","��"));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");			
		break;
		
		case "CapComission4_2":
			dialog.text = "���������?!! ������ ��� ��-�� ����� ��������������� � ������� ������ �������! � ������ � ���� �������� ��� ��������!.. ������� �� 200000, ���� ������.";
			link.l1 = "������ ���... ������...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "� ����, ����� ���� ������.";
				link.l2.go = "CapComission4_5";
			}	
		break;
				
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "������ ������� ��������...";
			link.l1 = "��������� ����������.";
			link.l1.go = "exit";
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
				
		case "CapComission5":
			dialog.text = "��-��! ��� ��� ������! ������� ������ �������� � ����� ������"+ GetSexPhrase("","�") +".";
			link.l1 = "�������. ��������� ����������.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;
				
		case "CapComission6":
			dialog.text = "�� ����� ������"+ GetSexPhrase("","��") +"? ���� � �� �����, ����� ������, ��� ������ ��� �����������.";			
			link.l1 = "������, "+ NPChar.name +", ��� ����� ����... � �����, � ���� ��� ����� �����. �� � �����"+ GetSexPhrase("","�") +" ����������.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "������, ��� �� ������. ��� ������ - 150000 ����. ��� � ���� ��� �������?"
				link.l2.go = "CapComission2_3";
			}			
		break;
		
		//������ ����������
		case "Marginpassenger":
			dialog.text = "� ����-�� ����� ���� �� ����, ��� � ���������, � ��� ���? ������ ���, ��� �� �� ���...";
			link.l1 = "����, �� ��������. � ������ � ���� �� ����, ������ ������ �� ����� ����.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "�-�, �� �����. �� ���� �� ������ �����?";
			link.l1 = "������. � ���� ������ �� ��� ����, ����� ��������, � ��� ����, ����� ���������� ���� ������ ������ ����� ��������. ��, � �� ����� c������ �������� �� ���� �����.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "��. � ����� ���� ������������ ��� ��������������? ���� ��� �� ������ �������� ������� ��������?";
			link.l1 = "��� ���� � ������ ������ ��� ������. ����� ���� �������� � ��������.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "���... ��, ������. ��� ��, ���� �������?";
			link.l1 = "��� "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "���-���... ���� �� �� �����, �� ��� ����� ��������� ���������� �������. �������, � ����� ��������� �� ����� �������� "+iTemp+" ����, ���, ���� ������, ���� ���������� �������� �����������. ��� ���� ������ ��������.";
			link.l1 = "����� ����� ����. � ��� ������� �������� � ���� �����, ���� ��� �������...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "��! ����� �������� ���-������ ��������. ������, ������ �� ��� �� ����������.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "������ - ��� ������. ���, �����. ������ ��� ������ �� ���� ������. ��������� �������� ����� ����.";
			link.l1 = "�� ������ ���� ��� ����� ��������� �����. �������! �� ���� �������.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "�� ������ ����������, ������� ���... �����!";
			link.l1 = "� ���� ����� �������...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			ref sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GOOD_EBONY + rand(makeint(GOOD_SANDAL - GOOD_EBONY));
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (drand(1))
			{
				case 0: //����� �� ����� �����
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "������� ����� ���� �� ��������� ���������, ������! ������ ������: ����� ��������� ���� � " + XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat") + " �������� ��������� ���������� �� �����, � �������� ������ ���������, � ����� ����� �������, ������� ������ ������ � ������� ����. ���� �� ������ �� ������� ���� ��������� - � ���� ����� ���� ������� ���� ����� ����\n�� ����� ����� � �� ��� ����� � ����� ��������. � ��������� ��������� �������� ����.";
					link.l1 = "���������! ��������� �������� ������� ������������ �� ��� ���������! � ��� �������� ��� ������ ���� ���-�� � ��������� �����. ��� � ���� ��������.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //������ ��������
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "������� ����� ���� �� ��������� ���������, ������! ������ ������: �������������� ����� ������ �� "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" ������ ��������� ���������� '"+pchar.GenQuest.Marginpassenger.ShipName1+"' � ������ ������ ��������� � ���������� � ���� "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". ���� �� ������ ������, �� �������� ����������� ��\n�� ��� �����? �� ����� ����� � �� ��� ����� � ����� ��������. � ��������� ��������� �������� ����.";
					link.l1 = "���������! ��������� �������� ������� ������������ �� ��� ���������! � ��� �������� ��� ������ ���� ���-�� � ��������� �����. ��� � ���� ��������.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen"));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (drand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
