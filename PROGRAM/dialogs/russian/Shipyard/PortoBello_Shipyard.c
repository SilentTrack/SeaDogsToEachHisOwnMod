
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?", "How can I help you?"), "You tried to ask me a question a little while ago...", "At his dock, and you know what�I've never seen such flat, curious people before in town.",
                          "What's with all the questions? My job is to build ships. Let's take care about that.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Umph, where did my memory go...",
                      "Hm, well...", "Go ahead...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Listen, a privateer named Francois Gontier hasn't stopped by to talk to you by any chance, has he? He was in Porto Bello recently, I know that.";
                link.l1.go = "Portobello_ratS_1";
            }
		break;
		
		case "Portobello_ratS_1":
			dialog.text = "He has. He acquired a corvette from me and soon departed to sea.";
			link.l1 = "Thank you! And do you have any idea where he departed to?";
			link.l1.go = "Portobello_ratS_2";
		break;
			
		case "Portobello_ratS_2":
			dialog.text = "No, buddy, I haven't got a clue. I repair and sell ships, I don't track where they go. It's none of my business.";
			link.l1 = "Well, then. Let's find out...";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello_1";
			AddQuestRecord("Slavetrader", "21_2");
		break;
			
			
	}
	UnloadSegment(NPChar.FileDialog2);  
}


