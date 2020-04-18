
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have for a soldier?", "A soldier has his whole life planned out �guarding, hustling... How can I help you, " + GetAddress_Form(NPChar) + "?"), "You are ill-informed to go ill with stupid questions to a soldier, " + GetAddress_Form(NPChar) + "...", "This is the third time today that you've tried to ask me a question...",
                          "The fate of a soldier isn't a wisp as it is, and now you, slink, driving me mad...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Nope...",
                      "Yeah, you are right, third time already...", "Sorry...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Tell me, does the name Juan mean anything to you?";
				link.l1.go = "Consumption";
			}
		break;
		
		
		case "Consumption":
			dialog.text = "No. Is that all?";
			link.l1 = "Yes. Sorry for bothering you, soldier...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}


