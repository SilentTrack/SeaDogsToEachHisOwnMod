// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = RandPhraseSimple("What kind of questions?", "What would you like?");
			link.l1 = RandPhraseSimple("I have changed my mind...", "I have nothing to say now.");
		    link.l1.go = "exit";
		break;
		
		//******************** ����������� ������� ***************************
		case "work_1":  // ������ �� ����� ������ - ������� �����
			if (CheckAttribute(npchar, "notQuestLine"))
			{
				dialog.text = "Unfortunately I can offer you a job. You are not that type of people who I want to work with.";
                link.l1 = "Seriously...";              
                link.l1.go = "exit";
				break;
			}            
		break;		 		            
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}
