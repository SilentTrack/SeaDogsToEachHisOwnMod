// ������ ������������� ����������� �������
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat("You again, senor?", 
				"Listen, sir, you'd better walk away...", 
				"Don't bother me, sir! I kindly ask you.",
                "Oh, I can't endure that... Even the mine was kinder to me.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes, it's me again.", 
				"Don't tell me what to do.",
                "And what about the hard way?", 
				"Get back to the mine!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "What do you want, senor?";
				link.l1 = "From you? Nothing I suppose. Just saying hi.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//��������� �� ����������� ������ �� ���������� ���� citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Don't challenge your fate, pal! Take away your weapon!", "Listen, I am the citizen of this town and I'd ask you to hold down your blade.");
			link.l1 = LinkRandPhrase("Fine.", "Fair enough.", "As you say...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
