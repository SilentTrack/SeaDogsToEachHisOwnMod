// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������, "+ GetSexPhrase("������� �������","���� ����") +"?", "���� �� ������, "+ GetSexPhrase("���������","��������") +"? �� ���� ����� ���."), "����� �������?", "��-��, ������ ��� �� ��� ���� � �� �� - �������...",
                          ""+ GetSexPhrase("��, ����� �� �������� �����-������ �������� ����? � �� � ���� ��� ������������ � ��������� ���� ������ ������������ ������...","��, ����� �� �������� �����-������ �������� ����? ��������� �� ������, ��-��...") +"", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������...", "��, �� ������..."), "�� ����... ��� ��������...",
                      "�� ��, ������������� � ������ ���... ������.", "�� ������... � ������ ���...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//����������� ������
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "� ��� ��������� ������� ������� �� ������� � ����������� � ��������. ������� - ������� �������, ������� � ���� ����, ������ ����������... ������� ����� ������ ����� ��� ���� �������� ���� ��������?";
                link.l1.go = "BrothelDone";
            }
		break;
		
		case "BrothelDone":
			dialog.text = "���� �������� - ���������� �����.";
			link.l1 = "���! ������... �����, ��� ������� ��� ����.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-7");
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.quest.GotoBridgetownOver.over = "yes";//����� ������
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

