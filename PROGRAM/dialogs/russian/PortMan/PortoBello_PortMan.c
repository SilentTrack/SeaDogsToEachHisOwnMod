
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "You've already tried to ask me a question " + GetAddress_Form(NPChar) + "...", "You have been talking about some question for the third time today...",
                          "Look, if you have nothing to tell me about the port's matters then don't bother me with your questions.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind.", "Sorry!"), "Sorry!", "Pardon!", "Sorry!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello_1")
            {
                link.l1 = "Good day to you. I'd like to learn where is captain Francois Gontier. I have for it an important matter.";
                link.l1.go = "Portobello_ratP_1";
            }
		break;

		case "Portobello_ratP_1":
			dialog.text = "An important matter you say? Let's see than. Well...  Francois Gontier, corvette '" + pchar.questTemp.Slavetrader.ShipName + "'... According to my notes, senor Gontier was heading to Jamaica.";
			link.l1 = "Thank you! You've helped a lot!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatJamaica";
			AddQuestRecord("Slavetrader", "21_3");
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
		break;
		

	}
	UnloadSegment(NPChar.FileDialog2);  
}



