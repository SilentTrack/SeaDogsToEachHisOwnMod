
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want? Ask away.", "I am listening to you, what's the question?"), "It is the second time you are trying to ask...", "It is the third time you are again trying to ask...",
                          "When is it going to end?! I am a busy man, working on the colony's matters and you are still trying to ask something!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...", "Not now. There is no time."), "True... But later, not now...",
                      "I'll ask, I'll ask... a bit later though...", "I am sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("You have already taken everything. What else do you want?", "Haven't you taken already everything?");
            link.l1 = RandPhraseSimple("Just a final search for the loot...", "Just checking, I may have forgotten to take...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}


