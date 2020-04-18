
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "You've already tried to ask me a question " + GetAddress_Form(NPChar) + "...", "You have been talking about some question for the third time today...",
                          "Look, if you have nothing to tell me about the port's matters then don't bother me with your questions.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind.", "Sorry!"), "Sorry!", "Pardon!", "Sorry!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";

			
			if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_P")
            {
    			link.l1 = "I'd like to learn concerning the bark which was gone in the night after revolt of slaves.";
    			link.l1.go = "EscapeSlave_Villemstad_P1";
            }
			
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "SeekFleut")
            {
    			link.l1 = "I want to find a captain named Toff Keller. He owns a flute 'Leiden'. I am informed that he often visits Willemstad so it won't difficult for you to help me I suppose.";
    			link.l1.go = "SeekTradeFleut";
            }
		break;

		
		case "EscapeSlave_Villemstad_P1":
				dialog.text = "Hm... And why are you interested in that?";
				link.l1 = "I am here by the order of Mathias Beck, the governor. I have all reasons to suspect runaway slaves for the ship's disappear. So I ask you to give me all possible help in my searches.";
				link.l1.go = "EscapeSlave_Villemstad_P2";
		break;
		
		case "EscapeSlave_Villemstad_P2":
				dialog.text = "I see. But unfortunately I can't help you. Bark named '" + pchar.questTemp.Slavetrader.ShipName + "' disappeared at night, no one saw anything. The watch is gone and left no trail\nThe authorities have failed to find it and, to be honest, they didn't try much. The city was in panic, people expected the slaves' attack...";
				link.l1 = "Well, there are really not much information... But thanks for that anyway. Farewell.";
				link.l1.go = "exit";
				AddQuestRecord("Slavetrader", "22_3");
				AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
				pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_H";
		break;				
		
		case "SeekTradeFleut":
			dialog.text = "Toff Keller? Sure I know him! He regularly sails voyages to Cumana and San Jose which is on the Trinidad. He have sailed to Trinidad not long ago. I suppose that you can find him there.";
			link.l1 = "Thanks!";
			link.l1.go = "SeekTradeFleut_1";
		break;
		
		case "SeekTradeFleut_1":
			DialogExit();
			pchar.questTemp.HWIC.Self = "FleutOnTrinidad";
			AddQuestRecord("Holl_Gambit", "3-59");
			pchar.quest.Seek_Fleut.win_condition.l1 = "location";
			pchar.quest.Seek_Fleut.win_condition.l1.location = "Trinidad";
			pchar.quest.Seek_Fleut.function = "CreateTradeFleut";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}


