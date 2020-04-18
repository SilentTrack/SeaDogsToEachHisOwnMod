
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "Questions again, " + GetAddress_Form(NPChar) + "...", "Questions, questions... How about to trade, " + GetAddress_Form(NPChar) + "?",
                          "Look, how long are planning to bubble talk?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("No questions...", "Nothing to say now..."), "Meh, once again...",
                      "Maybe it's really a time to trade...", "Hm, sorry, trader man...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}


