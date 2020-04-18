
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
			
			if (CheckAttribute(pchar, "questTemp.Mtraxx"))
            {
				if (pchar.questTemp.Mtraxx == "silk_2" || pchar.questTemp.Mtraxx == "silk_3")
				{
					link.l1 = "I've heard this shipyard deals with improving the ship's sailing speed. It requires some silk sailcloth, which is seldom to come by. Would you be... interested in discussing these matters?";
					link.l1.go = "mtraxx";
				}
			}
		break;
		
		
		case "mtraxx":
            dialog.text = "Could you be more clear, young man? What exactly brought you here? If you want to improve your ship - let's get to business.";
			link.l1 = "Not entirely. The type of services you perform require goods not freely available in the store. I would like to offer you the type of materials you might require.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Well-well... Ugh... Are you aware that only the authorities on this colony are allowed to deal with such strategic goods? You are free to provide your own silk for me to work on improving your ship, however, selling it is strictly forbidden. As is buying it from me - such activities will be fined rather heavily.";
			link.l1 = "Well, this isn't a store, nor is it a customs office...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "I acquire all of the silk sailcloth directly from my clients, or purchase limited quantities with a special permission of the governor. If you don't have any further questions - please, let me get back to my job.";
			link.l1 = "Hm... Very well. Have a good day, master.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            DialogExit();
			AddQuestRecord("Roger_2", "5");
			pchar.questTemp.Mtraxx = "silk_4";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}


