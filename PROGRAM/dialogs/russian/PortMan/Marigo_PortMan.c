
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "You've already tried to ask me a question " + GetAddress_Form(NPChar) + "...", "You have been talking about some question for the third time today...",
                          "Look, if you have nothing to tell me about the port's matters then don't bother me with your questions.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind.", "Sorry!"), "Sorry!", "Sorry!", "Sorry!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten1")
			{
				link.l1 = "There was a galleon named 'Admirable' under the French flag. It's captain name was Gaius Marchais. Can you tell me where has he sailed to next? Perhaps he has registered himself here?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "'Admirable'? Galleon? I remember it. We have  freighted  it to deliver paprika to Bridgetown at Barbados. Something happened?";
			link.l1 = "No, but Gaius is my friend and I am looking forward to meet him.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Then sail to Barbados. But I doubt that you will find him there, it has been too long. At least you can ask the local harbor master to help you.";
			link.l1 = "Thanks! You've helped me a lot.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "12");
			pchar.questTemp.Guardoftruth = "barbados";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  
}



