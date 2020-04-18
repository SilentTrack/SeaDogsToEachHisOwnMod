
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What would you like?", "What did you want to know ?"), "Tell me, what are you interested in, " + GetAddress_Form(NPChar) + "?", "It's the third time you try to ask...", "I had enough of you. Leave my place!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I crossed my mind...", "I've got nothing to say to you"), "Oh, my bad, indeed... I am sorry",
                      "You're right it the third time already. Pardon me...", "Oh, my bad, indeed... I am sorry...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}


