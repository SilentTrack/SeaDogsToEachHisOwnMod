
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you think about our fort? Looking good, yes? And the garrison is not worse, ha...", "The fort soldier's life is quite dull, it's all about a watch and a guard mounting. But it's all different in the town... What do you want, " + GetAddress_Form(NPChar) + "?"), "Bothering a soldier with stupid questions is not welcome, " + GetAddress_Form(NPChar) + "...", "It's the third time you try to ask...",
                          "It's not easy being a soldier and you are here again"+ GetSexPhrase(", jerk,  "," ") +" trying to teed me off. Be careful or you will end up in a basement of the fort...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...", "I've got nothing to say to you..."), "Bothering a soldier with stupid questions is not welcome...",
                      "You're right it the third time already. Pardon me...", "Pardon me...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}


