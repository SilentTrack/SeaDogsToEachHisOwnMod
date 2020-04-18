
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
			
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "I have had a profitable deal on Martinique and I am planning to sail to Blueweld. I want to buy redwood and coffee in your colony. Besides, my brig can't hold that much cargo which I am willing to buy, so I need to get a flute from your shipyard.";
                link.l1.go = "MayorDone";
            }
		break;
		
		case "MayorDone":
			dialog.text = "My assistance? Our trader is a very honest man, so I doubt that he will attempt to fool you. Talk to the shipmaster about the flute, he will help you with this matter. And if you will have troubles anyway, then come see me. I am interested in advance of trade connections with our colony and I will show you all my support\nYes, I am arranging an entertainment tonight at my place, all Bridgetown's brightest will attend. You should come too, captain.";
			link.l1 = "Thanks for your invitation but unfortunately I am too busy. Farewell and thanks for your agency!";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-8");
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
			pchar.quest.GotoBridgetownOver.over = "yes";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				
				
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}


