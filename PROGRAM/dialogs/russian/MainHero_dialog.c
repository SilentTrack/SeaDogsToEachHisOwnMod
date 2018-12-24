void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ref chr, sld, rShip, rItm, rItem;
    float  fTemp;
    bool bOk;
	int i, iTemp;
	string sAttr, sGun, sBullet, attrL;
	aref rType;
    
	// ��������� ��� �� ����� -->
	sAttr = Dialog.CurrentNode;
  	if (findsubstr(sAttr, "CabinCompanionTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i+1, strlen(sAttr)-1); // ������ � �����
 	    Dialog.CurrentNode = "Cabin_Companion_Talk";
 	}
	
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // ������ � �����
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
 	// ��������� ��� �� ����� <--

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		
		case "First time":
	      	NextDiag.TempNode = "First time";

	        Dialog.Text = "���� �� ������� ��� ������, ������, ���-�� ����� ��� � ����";
			Link.l1 = "�����";
			Link.l1.go = "exit";
			//--> ����������� ������
			if (CheckAttribute(pchar, "questTemp.HWIC_FindIsland"))
    		{
    		    dialog.text = "����, ��� �� � ����� ��� ����� �� �����. ������ ���. ����� ������������ �� ������.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuestFunction("SearchingForIslandOnMap");
    		}
			if (CheckAttribute(pchar, "questTemp.HWICMC") && pchar.questTemp.HWICMC == "Fleetwood")
    		{
    		    dialog.text = "���-���, ��� �� � �� �����. ���� �������� ������� � ������ �����, � ���� ������ ������ ����� ������� � ������������ �������� �������.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1.location = pchar.location;
				pchar.quest.Fleetwood_repeatShore.function = "Fleetwood_repeatShore";
    		}
			//<-- ����������� ������
			
			//--> ������ ����
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabinWoman" && PChar.location == Get_My_Cabin()) 
	        {
				dialog.text = "��... ������ ����� ���������� - ���� �������������, ���� ��� ������� ������ �� ������. ���� �����, �� ���� ��� �� �� ����. ��, �������, ���������-�� � � ��� ��������... ������! �������� ��� ����������� � ���� �������!";
    			link.l1 = "����, �������!";
	    		Link.l1.go = "exit";
				chr = characterFromId("FalseTraceWife");
				chr.dialog.currentnode = "FalseTrace_wife_6";
				pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
				AddDialogExitQuest("SetFalseTraceCharToCabin");
	    	}
			//<-- ������ ����
			
			//--> ����������
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "DigGems")
    		{
    		    dialog.text = "�������, ��� ��� �����. ��� ������������ �������� ������ � ������. �������, ������ ���� ������ �����.";
    			link.l1 = "(�������� ����)";
    			link.l1.go = "exit";
				AddDialogExitQuest("FindPortugalGems");
    		}
			//<-- ����������
			// ����
			if (CheckAttribute(pchar, "questTemp.Saga.JessSoul"))
    		{
    		    dialog.text = "��� ���? ��� �?! ��� �� �������� �����?";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("Saga_JessikaSoul_2");
    		}
            //--> ������� �� ������ � ����� ����������, LSC
			if (CheckAttribute(pchar, "questTemp.LSC.DiffIndoor"))
    		{
    		    dialog.text = "��� �����, ������� �� ���������� ��������� �������. �������... ���� ������ ���� ���. ��� ��� ������� ���? ���� ��������� �������� ������.";
    			link.l1 = "��������� ��� ����.";
    			link.l1.go = "knock_2";
				link.l2 = "��������� ��� ����.";
    			link.l2.go = "knock_3";
				link.l3 = "��������� ���� ���, �����, ��� ����.";
    			link.l3.go = "knock_1_3";
				link.l4 = "��������� ��� ����, �����, ��� ����.";
    			link.l4.go = "knock_2_2";
				link.l5 = "��������� ��� ����, �����, ���� ���.";
    			link.l5.go = "knock_3_1";
    		}
			//<-- ������� �� ������ � ����� ����������, LSC
			
			//--> �������� ���������� ��������, ��� �������� � ����� ����
			if (pchar.model == "protocusto")
    		{
    		    dialog.text = "��! �� � ������� �� ��� ���������!";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			//<-- ���������� ��������
			// ����� �� ������������
			if (IsCharacterInLocator(pchar, "item", "dolly1") || IsCharacterInLocator(pchar, "item", "dolly2") || IsCharacterInLocator(pchar, "item", "dolly3"))
    		{
    		    dialog.text = "���-���-���! ���� � �� �������! ���� ��� ������� �������!..";
    			link.l1 = "...";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "roof")
    		{
    		    dialog.text = "���� ������� - �������� �����. ��� ��������� �����, ��� � �����... �� ���-�� �� �� ���. ���� ���� ���� �� ������������ � ��������! ��� ������, ��� ���� ����� ������ ����, ���� ������ ������ ������\n�� ���� �� ��� ������� ���� ��� ����? ���������, �� ��� ������ � ������. ���� ���-�� ������, ���� � ���� ������� ������� �� ��� ���...";
    			link.l1 = "";
    			link.l1.go = "terrapin";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
    		{
    		    dialog.text = "���������, ���������... ��������� �����... � �� ���� � �������� ����������, ���� ������... ����� �� ������, ��� � ������������ ������� ����� ������ ������ �������� ���� ��� ����������� ������. �����, �� ����� ����������� � ���, ����� ������� ��� ������\n� ���� �����, �� ��� � ��� � ������� - �� ������ ��� �� ������� ������������, ��� ������ ���������� � ���-�����. ��� ������. �� � ������, ��� ��������� ������, ������� ������ '��� �� ������', � ������ ������ ������ - ���� � �� ��. ������� ����� �������� ��������� ������ ��������� � ����������� ������� �� '���������' �������� � �� ������\n������ ����������, ��� ������ ���-���, �� �� �����, � ������ ���-���, �� �� �����... �������! � ��� �� ����� ����������� ���������? �� �� ���� �� ��� ������ ���������� ������, �? �����, ��� ������ �� ����\n�������������, ���� ��� ����� ��� ������, �� � ���� ���� ������: � ������ �������� ������� � ��������� �����, �... ��-��, ������ ��� ������ �� ��������. �� � ������ �� ����� ����������� ���� ������? ������, �������� ������ ����������� � ���������\n��� ����� ������� �������� - � ��� � ������ �� ����������, � ��� ������ ���� ��������, ����������, �������� ���� ������... ��� ���� ��������. ������ ������ ������ �� ���������� ��������������, ���� ����� ������ � �� �������� �������� ��������\n������, ������... ���-�� � ��� ������ ��� ���... ��� ���? �����, ���� � ���. ����� � �������, �������� ������ �������, � ����������� � ��������.";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore")
    		{
    		    dialog.text = "������ ����������� �� �������, �� ������ ����� �������� �� ����������, � ���� ������ ������, ������ ����, ����� �������� � �������� ����, ���� � �������� � ����, ���� �� �������. � ����� �� ������� ������������ ��� ������������: ����� ������, ��� � ���� � ���������... ����������-�� � ������ � ����� ����� ������� � ��������, ��� ������ ��� ������� �����...";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "galeon")
    		{
    		    dialog.text = "������ �� ������� ������ �������, � ��� ���, ��� ���� - ������ � ����� �����. �����, � ����� �������� �� ���� �� ������, ���� �������� ����� �� ����� � ������ �������� �� �������...";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth_room"))
    		{
    		    dialog.text = "���������� ������ ��� � ������ ��������� �� ������ �����, � ����� �� ��������� � ������������� ��������... ������ ������� ������. ���� ������� � ���� � ������ �� �������� �����, �� � ��� ����� �������� � ������� ����. � ������ ��� ���� �����, ����� ����� �� �������...";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("GuardOT_FindWayToRoom");
    		}
			// ������ ���������
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_pearl")
    		{
    		    dialog.text = "���-���! ��� � � ����� �����, ��������� '�����������': ��� ��������� �������! ����� � ��� ������� ������� ������ ���� ��������� �������� � ��������� ������ ���� � �� �� �����������, ��� �� �������. ������� - ��������� ����� - ��������� �������. ������ ���� �������� �����������, ���� ��������� ������ ����, �� �����, � ����� ������������ �� ��������.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFirstWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_dominica")
    		{
    		    dialog.text = "���-���! ��� � � ����� �����, ��������� '�����������': ��� ��������� �������! ����� � ��� ������� ������� ������ ���� ��������� �������� � ��������� ������ � ���� � �� �� �������, ��� �� �������. ������� - ��������� ����� - ��������� �������. ������ ���� �������� �����������, ���� ��������� ������ ����, �� �����, � ����� ������������ �� ����.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindSecondWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "full")
    		{
    		    dialog.text = "��� ���������� �������! ������ ����� �������� ������ ����������� �� �����. ����������� ���� ����������� � ������ ��� ��������������� ������� ��������.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFullWay");
    		}
			// ����������� �� ��������
			if (CheckAttribute(pchar, "questTemp.Tieyasal_CabinTalk"))
    		{
				if (pchar.questTemp.Tieyasal_CabinTalk == "calendar")
				{
					dialog.text = "������ �� ���������� ������, ��� ���� �����-�� ���� � �������� � ������ ����������� ������. ������, ����� �������� ������ � ����� ������ � �������� ������. ������ � ���� �� ���� �� ������ ����� ����� � ���, ��� ���������������� ������ ���������� ��������������� ��� ������� � �������� ��������� ����� � ��������\n�� � ����� ������� ������� ���� �������, ��� �������� �� ������ ������ ���������� '���������' � ���� �����. �� ������ �� ����� ������� ��� ������� ��������? ��. ����� ����, �� ����� ���� ��������� ����� ������� ����������, ������������� ������� � �������� �������, ���� �����-�� ����������� � ���� �����\n��� �� ��� ����� �������? ��� ���� ���������� �����? ��� �����-�� �������������� �������� ��������? �������, ���� ����������� � ������� � ������������ �� ���� ������. ���� �� �������� ���� ������ � ����� �� ������ �����, ������� � ��������. ��������, ��� ����� ���� ���� � ����� �� ���� �� ������-�������� �����.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "������ �� ���������� ������, ��� ���� �����-�� ���� � �������� � ������ ����������� ������. ������, ����� �������� ������ � ����� ������ � �������� ������. ��������, ������ ��� ����� ����� ���� ���� � ����� �� ���� �� ������-�������� �����.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				AddDialogExitQuest("Tieyasal_AfterCabinTalk");
    		}
			// ������ - ����� ��� ������� 010912
			if (CheckAttribute(pchar, "questTemp.Tieyasal_final"))
    		{
				dialog.text = "��� � ����� �������� ����. � ����� ��� � ���� �����������, ��� ���������� ������ �����, � ��� ����� ��������� � ����������� ������� � ���? ��� � �������� ��� ������ ���� ���? ����� ����, ��� ������\n����� ����� ���� �� ������ �� �������. ������ ����� ������������ �����, �� �������. ��... ��� ������ ���� �� � �����?";
				link.l1 = "��, � ����������� � ������.";
				link.l1.go = "final_1";
				link.l2 = "���, � ������� �����, �� �������.";
				link.l2.go = "final_2";
    		}
			// �������� ����� 040912
			if (CheckAttribute(pchar, "questTemp.Europe"))
    		{
				PlaySound("VOICE\Russian\military02.wav");
				dialog.text = "�� �������, ��� ������ ���������? ����� �������� ���������! �������� ���� ���, ����������� �� � �������� ����, ��� ��� ���������! ������!!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuest("Europe_SharlieFinal_2");
    		}
			// Addon-2016 Jason, ����������� ���������� (���) ���������
			if (CheckAttribute(pchar, "questTemp.FMQG.Info") && pchar.location == "Bridgetown_Plantation")
    		{
    		    dialog.text = "��� ����� ������ ����� ��� ������. ����� ���� ������ � ��������� �������.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("FMQG_KidnappingInfo");
    		}
			// Addon-2016 Jason, ����������� ���������� (���) ����-���������
			if (CheckAttribute(pchar, "questTemp.FMQN.Choose") && pchar.location == "shore40")
    		{
				dialog.text = "��. ��� ��� ������� ����� ������. ������� ���, ��� �������� ������� �� ����-������ ����� � �� ������������. ���� ��������� ��������� ���� � ���� ������� ��������. �� ���-�� ��� �����? � �� ���� � �����������... ��� �� ��� ������? ���� ������ �� ����� �������� � ������ �� ���� ������ ��������, ��� ��������?";
				link.l1 = "�������� ��������.";
				link.l1.go = "FMQN_1";
				link.l2 = "��������.";
				link.l2.go = "FMQN_2";
    		}
			// Addon 2016-1 Jason ��������� �������
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Chest") && pchar.location == "shore37")
    		{
    		    dialog.text = "����, ������ �����������. ���� ���������� � ���� ������ ��� ����� ���� ������. ����� � ������ � ������ ���������� ������� �� �������� �� �������, � ������� � ������� �������� �������� ������� �� �����������: �������� - 30, �������� - 2. � ������� ������� ����� ���� �� 1 �����, � � ������� - 20, ����� �� ��� �� ����� �����. �������� ����� ���������� ��������, �� ����� 3 ���� �� �������� �� ����� ������. ��������� � �����!";
    			link.l1 = "*��� �������� ������� �� ��������� ����� �������� ����������� '����� �����'*";
    			link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_PlantChestReadyExit");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Boats") && pchar.location == "Maracaibo_river")
    		{
    		    dialog.text = "����, ����� ��������� ����� �����. ��� ����� ���� ����� ����������� 20 ������ ����������� ����� � 10 ����� ����. ���������� ������� �� �������. ���������� �������� ������ �������, ������������� � ���������� ���� � ������� ��������.";
    			link.l1 = "*��� ������ ������� � ��������� ����� ����������� '����� �����'*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Boats");
				AddQuestRecord("Roger_5", "11");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder") && pchar.location == "shore10")
    		{
    		    dialog.text = "����, � ������-�������� ������ ���� ����� �� ������ ��������. ��� ����� ��� ����������� 300 �������� ������, ����� ���������, � ����� ���� �� ������ ����� � ����� ������ - ������� ������.";
    			link.l1 = "*��� ������ ������� � �������� ������ � ������ ����������� '����� �����'*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder");
				pchar.questTemp.Mtraxx.Retribution = "powder";
				chrDisableReloadToLocation = false;
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed") && pchar.location == "Judgement_dungeon_01")
    		{
    		    dialog.text = RandSwear()+"����� ������!! ����� �� ��������� - ������ �� �������� ������� ���-�� �������!.. "+RandSwear()+"\n�-�-�... ��� ���?..";
    			link.l1 = "";
    			link.l1.go = "mtraxx_dungeon";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead") && pchar.location == "Judgement_church")
    		{
    		    dialog.text = "�� ��� � ���... �����. ������ ���� ������\n������, ��� ������ ��� ����: �� ���� ���������� �� ���������. ��������� ���� �������, ����� � ����� ����� �� ���� � '�����������', ����� ����� ������ ����� � ���������� � �����, �� ������... � ��� ������� ���� ������� - ������� � ��� ���� �� ���� ������ ��������? ������, ����? ��� �� ��� ���� � �����, ������ � �����\n� ��� �����, ������, �����-�� ���� �������. ����� ���������� ����� ��� ����, ����� ����������. ������ � ���� �����, ������� �����... ��������, � ����� ���� �����: � ������ �����, ��� ������� �� �����, � ���� �� ����� �����������. �����, �������, � �� �������� ������...";
    			link.l1 = "";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead");
				AddDialogExitQuestFunction("Mtraxx_RetributionBead");
    		}
		break;
		
		// boal -->
		case "TalkSelf_Main":
	   		NextDiag.TempNode = "First time";
//navy --> after duel in tavern
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				Dialog.Text = RandPhraseSimple("������ ���� �������... ������ ����� ������� ������������� ������.", "��! ��� ���� ������. � ��� ���������� ����� �����������!");
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.LocationClone");
				break;
			}
//navy <--
	        Dialog.Text = RandPhraseSimple("��... ��� �� ��� ������ �������� �������?", "��� �� ��������?");
	        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
	        {
				//navy --> 13.02.08
				if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
				{
    				link.l3 = "������� ����������.";
    				link.l3.go = "Cabin_CompanionSelect";
				}
				//navy <--
			}
			else 
			{   //���.�������, ����� �6, ����������� ������������ � ���������� �������
				if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
				{
					if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    			{
	    				link.l1 = "�������� �� ����.";
	    				link.l1.go = "TalkSelf_room_day";
	    			}
	    			else
	    			{
	    				link.l1 = "�������� �� ����.";
	    				link.l1.go = "TalkSelf_room_night";
	    				link.l2 = "�������� �� ���������� ����.";
						link.l2.go = "TalkSelf_room_day";
	    			}
				}
			}
	        if (!bDisableMapEnter)//��� � ���� ���
	        {
	            if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
	            {
	                Link.l5 = "��������� ����� � �������";
	        		Link.l5.go = "TalkSelf_SlavesToCrew";
	    		}
	        }
	        // ������ ������
	        if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack") && !CheckAttribute(Pchar, "questTemp.Sharlie.DefendSP"))
	        {
	            Link.l6 = "������ ������ ���������� ������.";
	    		Link.l6.go = "TalkSelf_TownAttack";
	        }
	        
			bool bSeaBattle = (bDisableMapEnter) && (bSeaActive) && (!CheckAttribute(pchar, "GenQuest.MapClosedNoBattle"));
	        if(!bSeaBattle && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar, "GenQuest.CannotWait")) 
	        {
	        	Link.l7 = "��� �� ������ �� ���������...";
	    		Link.l7.go = "TalkSelf_StartWait";
	    	}
			
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				if(CheckAttribute(pchar, "chr_ai.bulletNum") && sti(pchar.chr_ai.bulletNum) > 1)
				{
					Link.l8 = "���� ������� ��� ���������� ��� �������������� ������.";
					Link.l8.go = "SetGunBullets";
				}	
			}
			
			Link.l14 = "���� ������� ��� ��������� ����� ��� ����������� ������������.";
			Link.l14.go = "ChoosePotion";
			
			
			
			//--> ����������� ������
			if(CheckAttribute(pchar, "questTemp.HWIC_Coordinates") && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l9 = "�������� ����������� ������� �� ����������� �� �����.";
	    		Link.l9.go = "Seek_AbyIsland";
	    	}
			//<-- ����������� ������
			
			//--> ������ ����
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabin" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l11 = "������� ����� �������.";
	    		Link.l11.go = "FalseTrace_Cabin";
	    	}
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "CatchAdam" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l11 = "���������� ����� �������.";
	    		Link.l11.go = "FalseTrace_Cabin";
	    	}
			//<-- ������ ����
			// Addon 2016-1 Jason ��������� �������
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Ammo") && PChar.location == "Shore37") // ������ 3
	        {
	        	Link.l15 = "����������� ���������� ������� � ������� ������� �� ��������� ����� �������� ��� ���� ������.";
	    		Link.l15.go = "mtraxx_ammo";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Mutiny") && pchar.location == "Maracaibo_Plantation" && stf(environment.time) >= 3.00 && stf(environment.time) < 4.00) 
	        {
	        	Link.l15 = "������ ������ �� ����� �� ��������� ���������.";
	    		Link.l15.go = "mtraxx_mutiny";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_boats" && pchar.location == "Maracaibo_river") 
	        {
	        	Link.l15 = "������ ������ � ��������� �����.";
	    		Link.l15.go = "mtraxx_boats";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "powder" && pchar.location == "shore10") 
	        {
	        	Link.l15 = "������ ������ � �������� ������ � ������.";
	    		Link.l15.go = "mtraxx_powder";
	    	}
			// -->����������			
			if(Pchar.Location == Pchar.location.from_sea && CheckOfficersPerk(pchar, "SelfRepair") && CheckSelfRepairConditions()) 
			{
				Link.l12 = "������ ������ ��������";
				Link.l12.go = "StartSelfRepair";
			}			
			// <--����������
			//--> ���������� ����
			if(CheckAttribute(pchar, "questTemp.Tieyasal_WinEnd")) // patch-9
	        {
	        	Link.l13 = "��������� ���� �� ������� � ����������� � ������.";
	    		Link.l13.go = "final_1";
	    	}
			//<-- ���������� ����
			Link.l10 = RandPhraseSimple("�� ������. ��� �������.", "�������. ���� ����.");
			Link.l10.go = "exit";
		break;
		
		case "StartSelfRepair":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			LaunchRepair(pchar);
		break;
		
		case "SetGunBullets":
			Dialog.Text = "����� ���� ���������� :";
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;
		
		case "SetGunBullets2":
			i = sti(PChar.GenQuest.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, sBullet);
			LAi_GunSetUnload(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetGunBullets");
			DialogExit_Self();
		break;
		
		case "ChoosePotion":
			Dialog.Text = "";
	    	Link.l1 = "�������� ��������.";
	    	Link.l1.go = "ChoosePotion1";
			Link.l2 = "�������.";
	    	Link.l2.go = "ChoosePotion2";
			Link.l3 = "��������.";
	    	Link.l3.go = "ChoosePotion3";
			Link.l4 = "�������� ������.";
	    	Link.l4.go = "ChoosePotion4";
			Link.l5 = "���.";
	    	Link.l5.go = "ChoosePotion5";
			Link.l6 = "����.";
	    	Link.l6.go = "ChoosePotion6";
			if (CheckAttribute(pchar, "GenQuest.Potion_choice"))
			{
				Link.l7 = "���� �������� �������������.";
				Link.l7.go = "ChoosePotion7";
			}
			Link.l8 = "����, � ���������.";
	    	Link.l8.go = "ChoosePotion8";
		break;
		
		case "ChoosePotion1":
			log_info("�� ��������� ����� �������������� ����� '�������� ��������'");
			pchar.GenQuest.Potion_choice = "potion1";
			DialogExit_Self();
		break;
		
		case "ChoosePotion2":
			log_info("�� ��������� ����� �������������� ����� '�������'");
			pchar.GenQuest.Potion_choice = "potion2";
			DialogExit_Self();
		break;
		
		case "ChoosePotion3":
			log_info("�� ��������� ����� �������������� ����� '��������'");
			pchar.GenQuest.Potion_choice = "potion4";
			DialogExit_Self();
		break;
		
		case "ChoosePotion4":
			log_info("�� ��������� ����� �������������� ����� '�������� ������'");
			pchar.GenQuest.Potion_choice = "potion5";
			DialogExit_Self();
		break;
		
		case "ChoosePotion5":
			log_info("�� ��������� ����� �������������� ����� '���'");
			pchar.GenQuest.Potion_choice = "potionrum";
			DialogExit_Self();
		break;
		
		case "ChoosePotion6":
			log_info("�� ��������� ����� �������������� ����� '����'");
			pchar.GenQuest.Potion_choice = "potionwine";
			DialogExit_Self();
		break;
		
		case "ChoosePotion7":
			log_info("�������� ����� ����� ���������� �������������");
			DeleteAttribute(pchar, "GenQuest.Potion_choice");
			DialogExit_Self();
		break;
		
		case "ChoosePotion8":
			DialogExit_Self();
		break;
		
		case "TalkSelf_StartWait":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
			DoQuestCheckDelay("CallFunctionParam", 0.1); // ����� � ���������, ����� - �� �������� ���������
		break;
		
		case "TalkSelf_room_night":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Night");
			TavernWaitDate("wait_night");
			DialogExit_Self();
		break;

		case "TalkSelf_room_day":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Day");
			TavernWaitDate("wait_day");
			DialogExit_Self();
		break;
		//  ������ ������
		case "TalkSelf_TownAttack":
            bOk = (GetPartyCrewQuantity(Pchar, true) >= 500) || bBettaTestMode;
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
	        {
	            chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
	            if (chr.from_sea == Pchar.location.from_sea)
	            {
					Dialog.Text = "������ ������, �������, �����, �� ��� ������ ������� ��� ������� ����� ����� �� �����������. � ������ �������� �� ������.";
	    			Link.l1 = "...";
	    			Link.l1.go = "exit";
	            }
	            else
	            {
	                if (pchar.location == "Panama_ExitTown" || pchar.location == "Tortuga_ExitTown") // patch-5
					{
						Dialog.Text = "��-�-��, � �� �����������. ����� ���� ����� � ���� ����������...";
	    				Link.l1 = "...";
	    				Link.l1.go = "exit";
					}
					else
					{
						if (pchar.location == "Minentown_ExitTown")
						{
							Dialog.Text = "��� ������ ��������� ���� ������ ��� ����������� �������� � ��������� �� ��� ������ � �������. ������ �������� ����� ������ ��� ��� �������...";
							Link.l1 = "...";
							Link.l1.go = "exit";
						}
						else
						{
							Dialog.Text = "������� �� ����� " + GetCityName(chr.City) + ".";
							if (CheckAttribute(pchar, "questTemp.Patria.SanJoseAttack") && pchar.location == "PortSpein_ExitTown") // Jason ���
							{
								Link.l1 = "������ ���������� ����������! ���������!";
								Link.l1.go = "exit";
								break;
							}
							if (CheckAttribute(pchar, "questTemp.Patria")) // Jason ���
							{
								if (pchar.questTemp.Patria != "fail" || pchar.questTemp.Patria != "complete")
								{
									if (pchar.location == "Marigo_ExitTown" || pchar.location == "Villemstad_ExitTown")
									{
										Link.l1 = "������ ���������� ����������! ���������!";
										Link.l1.go = "exit";
										break;
									}
								}
							}
							Link.l1 = "� ������!";
							Link.l1.go = "TalkSelf_TownAttack_Start";
							Link.l2 = "���������!";
							Link.l2.go = "exit";
						}
	    		}
	        }
	        }
	        else
	        {
				if(!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
				{
					Dialog.Text = "��! ������� ��������, ����� ���� �� 500 �������.";
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					Dialog.Text = "�� ������������! ���������� �����!";
					Link.l2 = "...";
					Link.l2.go = "exit";				
				}			
			}
	    break;

		case "TalkSelf_TownAttack_Start":
	        NextDiag.CurrentNode = NextDiag.TempNode;

			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (isCityHasFort(chr.City))
			{
	        	SetLocationCapturedState(chr.from_sea, true);
	        }
	        else
	        {
	            SetLocationCapturedState(chr.Default, true); // ��� ����������
	        }
	        AddDialogExitQuest("Capture_Forts");
	        Ship_NationAgressive(chr, chr);
	        DialogExit_Self();
	    break;
	    // ��������� ����� � �������  -->
		case "TalkSelf_SlavesToCrew":
	        if (GetCurCrewEscadr() >= GetMaxCrewAble())
	        {
	            Dialog.Text = "����� �� ����� �� ����� ���� � �������.";
	            Link.l1 = "�� � �� �����!";
	    		Link.l1.go = "exit";
	        }
	        else
	        {
	            if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
	            {
	                Dialog.Text = "�� ������� ��� ����� ��� ����� ��������.";
	                Link.l1 = "��! ����� ����������� ����� ������� �� ������ �������.";
	        		Link.l1.go = "exit";
	            }
	            else
	            {
	                if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
	                {
	                    pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
	                }
	                else
	                {
	                    pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
	                }
	                Dialog.Text = "� ������� ������ ����� " + pchar.GenQuest.SlavesToCrew+ " �����. ����� ��?";
	                Link.l1 = "��";
	        		Link.l1.go = "TalkSelf_SlavesToCrew_1";
	        		Link.l2 = "���";
	        		Link.l2.go = "exit";
	    		}
			}
		break;

		case "TalkSelf_SlavesToCrew_1":
	        if (CheckOfficersPerk(pchar, "IronWill"))
	        {
	            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0))
	        }
	        else
	        {
	            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0))
	        }
			ChangeCharacterComplexReputation(pchar,"authority", -0.5);
	        // ������� ����� -->
	        fTemp =  stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
	        pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Sailors)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Cannoners)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Soldiers)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			// ������� ����� <-- 
			pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew); 
	        RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));       
			                            
	        NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		// ��������� ����� � �������  <--
		// boal <--

//navy CONTRABAND METRO -->
		case "GenTravel_Main":
			NextDiag.TempNode = "First time";
			dialog.Text = "������ ���� �������� ������� ���, � � ����� �������! ����, �������� �������� ��� �������.";
			Link.l1 = "���� �� �����...";
			Link.l1.go = "exit";

			chr = CharacterFromID("Abracham_Gray");
			chr.location = "none";
			SeaExchangeCharactersShips(PChar, chr, false, false);
			SetCrewQuantity(PChar, 0);

			//������ �� ���� �����...
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
            
			CloseQuestHeader("Gen_ContrabandTravel");
			setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

			//���� ���������
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			break;
//navy CONTRABAND METRO <--

//navy --> 13.02.08
		case "Cabin_CompanionSelect":
			Dialog.Text = "���� �� ����������� �������?";
			for (i = 1; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
				{
					sAttr = "l" + i;
					rShip = GetRealShip(sti(chr.Ship.Type));
					link.(sAttr) = GetFullName(chr) + " - " + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
					link.(sAttr).go = "CabinCompanionTalk_" + i;
				}
			}
			link.l9 = "� ������ ���.";
			link.l9.go = "exit";
			break;

		case "Cabin_Companion_Talk":
			i = sti(PChar.GenQuest.CabinCompanionNum);
			PlaceCompanionCloneNearMChr(i, false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			break;
//navy <--

		//--> ����������� ������
		case "Seek_AbyIsland":
			bOk = CheckCharacterItem(pchar, "bussol") && CheckCharacterItem(pchar, "clock2");
			bool bOk1 = CheckCharacterItem(pchar, "sextant2");
			if (bOk || bOk1)
			{
				DialogExit();
				DeleteAttribute(pchar, "questTemp.HWIC_Coordinates");
				pchar.questTemp.HWIC_FindIsland = "true";
				AddDialogExitQuestFunction("PrepareSearchingFor");
			}
			else
			{
				dialog.text = "��, � ���� ��� ����������� ������������� �������� ��� ����������� ������ � �������. ����. ������ ������� �������� ��������.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		//<-- ����������� ������
		
		//--> ������ ����
		case "FalseTrace_Cabin":
			dialog.text = "������! ���������� ��������� �� ��� ����� �������!";
			link.l1 = "����, �������!";
			link.l1.go = "exit";
			chr = characterFromId("Mugger");
			if (pchar.questTemp.FalseTrace == "CatchAdam") chr.dialog.currentnode = "FalseTrace_17";
			else chr.dialog.currentnode = "FalseTrace_7";
			pchar.questTemp.FalseTrace.CharID = "Mugger";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		
		case "FalseTrace_Woman":
			DialogExit();
			chr = characterFromId("FalseTraceWife");
			chr.dialog.currentnode = "FalseTrace_wife_6";
			pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		//<-- ������ ����
		
		//--> LSC, ������� �� ������ � �����
		case "knock_2":
			PlaySound("interface\knock_2.wav");
			dialog.text = "���������, ������ �������� ������...";
			link.l1 = "(�����)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3":
			PlaySound("interface\knock.wav");
			dialog.text = "���������, ������ �������� ������...";
			link.l1 = "(�����)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3_1":
			PlaySound("interface\knock_3_1.wav");
			dialog.text = "���������, ������ �������� ������...";
			link.l1 = "(�����)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_1_3":
			PlaySound("interface\knock_1_3.wav");
			dialog.text = "���������, ������ �������� ������...";
			link.l1 = "(�����)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_2_2":
			PlaySound("interface\knock_2_2.wav");
			dialog.text = "���������, ������ �������� ������...";
			link.l1 = "(�����)";
			link.l1.go = "knock_right";
		break;
		
		case "knock_wrong":
			dialog.text = "�� ���������... ������, ������� ���� ���� �� ���. ��� ��, ����� ������ � �������� ��� ��� - ������� ��� ��� ��������� �� �������.";
			link.l1 = "(����)";
			link.l1.go = "exit";
		break;
		
		case "knock_right":
			PlaySound("interface\key.wav");
			PlaySound("voice\russian\YouFace.wav");
			dialog.text = "�! ���������! � ����� �����! ����� �������...";
			link.l1 = "(�����)";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.DiffIndoor");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload74", false);
		break;
		//<-- LSC, ������� �� ������ � �����
		
		// ��� �� ��������
		case "terrapin":
			PlaySound("Interface\Door_Kick.wav");
			PlaySound("voice\russian\EvilPirates02.wav");
			dialog.text = "�������! ��� � ���������! ������ ���������� ������� ���������... ����� ����� �� �����. �� ��� ��, �������� ������ �� ���� - ����� ����. ���� ������ �� ����-�� ���� ��������!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Terrapin_GoWindow");
		break;
		
		// ������ ���-�����
		case "SP_defend":
			PlaySound("VOICE\Russian\military02.wav");
			dialog.text = "����, ����� ���� ���������� ������ - ������ ����� ��������� ���������� �� ��������� ���-����. ���� ��������, ��� ���� �� ������ ������. � ����� ���-����� ������������� ������ ��������� �������, ������� ������� - �������� �������. ��������� ������� ���������� - � ����� ������ �������, ����� ����, ��������� � ������ �� �������� ��� �������� ������ �� ������\n������� ���� ���� ������� ������� ������ ����� ������� � ��������� ��������� � ���� ����� ��������� ������. ������� ����� � ���� �� �����������, �������� ��������. �������� ��������� �����, ��� ������ ������� ����� ��������\n��� ��������� ���������, � � ����� ������������ ��������� ����� ������ ��������� ��� ����� ���� �� ��� �������. �������, ��� ������� ���� ��������� � ����������� �����. ������!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("DefendSP_GoJungle");
		break;
		
		// ����� ����
		case "final_1": // Jason ���
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) // �������-���������� ������ �� �����
			{
				dialog.text = "����, ���� ��� � ��������? � �� ���� �������� ���� �������-����������� ��� ���������� �� ������! ����� �� ������� ���� ����� ����������� ����� ����� �� ����������� ���������� ��������� �������. �����, � ���� ������� �� ����...";
				link.l1 = "";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "����� �� ����� ������ �������! � ��� ���������� �� ����� ������ �������! ��������� ������!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("Final_ReturnToEurope");
			}
		break;
		
		case "final_2":
			dialog.text = "� � �����, ��� ���������� �������! ��� � ��� �����, � ���� ��������-������, ����� ����� � ����� ������ ����? � ��������� �� ������� � ������ �����!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Final_StayInCarribean"); // 010912
			DeleteAttribute(pchar, "questTemp.Tieyasal_final");
		break;
		
		// Addon-2016 Jason, ����������� ���������� (���) ����-���������
		case "FMQN_1":
			dialog.text = "� ��� ����� ������ �������. ����������� �� ������� � ���������� �������� ������.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseExit");
		break;
		
		case "FMQN_2":
			dialog.text = "��� ��, ���-���� ��������. �� ����� � ��� � ���� ������ � ����� � ���� ������ - ����������� �� �������, ����� � ���� ����������� � �������� ����������. � �� ������� ����������� ������ ������� � ����� �� ���������� ������� �����������.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseContinue");
		break;
		
		// Addon 2016-1 Jason ��������� �������
		case "mtraxx_ammo":
			Mtraxx_PlantCheckShoreBox(); // ����������� ���������� �������
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.Blade") && !CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.NoBlade")) // ������� 30 ������
			{
				dialog.text = "�������� ������ ��������� ������ � �������! ����� ���������, ���� ������� ��� ��������, ����, �����?..";
				link.l1 = "���� ������ � �������� ��������!";
				link.l1.go = "mtraxx_ammo_1";
				link.l2 = "���, ���� ��������� ������ ������.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = "�������� ������ ��������� ������ ��� �� �������! ���� ���������� ������.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_ammo_1":
            dialog.text = "������ �������� � ������������� ���� �� ��� �������� �������� �� ���������.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantShoreBoxComplete");
		break;
		
		case "mtraxx_mutiny":
            dialog.text = "������, � �����! ���!!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantMutiny");
		break;
		
		case "mtraxx_boats":
            if (GetSquadronGoods(pchar, GOOD_PLANKS) >= 20 && GetSquadronGoods(pchar, GOOD_LEATHER) >= 10) // ������� ����������
			{
				if (Mtraxx_MeridaCheckCarpenter()) // ������� ��������
				{
					dialog.text = "��� ��������� ������������, ���������� � ��������� �����!";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_MeridaBuildBoats");
				}
				else
				{
					dialog.text = "��� ���������� �������� ��������, ��������� ����� ����������� ���������� �����. ���� ��������� ������ �������.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "������������ ����������, ����� �� ����� 20 ������ ����� � 10 ����� ����.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_powder":
            if (GetSquadronGoods(pchar, GOOD_POWDER) >= 300) // ������� ������
			{
				if (GetCrewQuantity(pchar) >= 20) // ������� �������
				{
					dialog.text = "��� �������� ������ ��� ������ - ������� ������� � ������!";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_RetributionBarrels");
				}
				else
				{
					dialog.text = "��� ������������ ���������� ����� ��� ��������� ��������, ���� �� ������ 20 ������� � �������.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "������������ ������, ����� �� ������ 300 ��������.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_dungeon":
			PlaySound("ambient\jail\jail_door2.wav");
            dialog.text = "�������, ���-�� ��������� � �������� �����...";
			link.l1 = "";
			link.l1.go = "mtraxx_dungeon_1";
		break;
		
		case "mtraxx_dungeon_1":
			PlaySound("ambient\jail\jail_door1.wav");
            dialog.text = "�����!.. ���-�� ��������� ����... ���?..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionRunToEnrico");
		break;
	}
}

void  DialogExit_Self()
{
    DialogExit();
	locCameraSleep(false); //boal
}