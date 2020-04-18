
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions, "+ GetSexPhrase("young man","young lady") +"?", "What do you want, "+ GetSexPhrase("handsome","pretty one") +"? Ask it."), "Questions again?", "Tee-hee, it's all the same for third time this day - questions...",
                          ""+ GetSexPhrase("Hm, why don't you pick up a beauty for yourself? I am starting to get suspicions about you...","Hm, why don't you pick up a beauty for yourself? We don't have boys here, sorry, tee-hee...") +"", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...", "Well, it is nothing..."), "I can't... no questions...",
                      "You're right it the third time already. Pardon me.", "Not now... next time...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}


