
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
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "I have got a delicate matter for you. No long ago one privateer has granted a golden cross with a lazurite on it to the parish of Basse-Terre. The problem is that the cross was stolen from the Santiago's parish and the servant was murdered during the theft...";
                link.l1.go = "guardoftruth";
			}
			
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "I arrived by the order of Governor General Philippe de Poincy to take command of your armed frigate.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "I'm ready to take the frigate into the squadron.";
                link.l1.go = "patria_2";
			}
		break;
		
		case "Cupture_after":
            dialog.text = RandPhraseSimple("You have already taken everything. What else do you want?", "Haven't you taken already everything?");
            link.l1 = RandPhraseSimple("Just a final search for the loot...", "Just checking, I may have forgotten to take something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "guardoftruth":
			dialog.text = "Hm. That's quite interesting. But why do you think that I care about problems of Spanish?";
			link.l1 = "It is not about the Spanish, monsieur. Nation's matters mean nothing to the religion. There is an item which is covered in the holy servant's blood in your parish and there was a desecration made to the Santiago's parish...";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = "I ask you to show a justice and to order holy father to return the cross to it's owners.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "And since when you have become such a true and earnest believer, "+pchar.name+"? Spanish are not friends of ours and I see no reason to push on the holy father in this matter. The cross was a gift and that's fine. Our priest has no connection to that theft and murder, so...";
			link.l1 = "And you can't help me, right?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "To be honest, "+pchar.name+", I don't feel that I have to. I have no love to those Papist's fanatics.";
			link.l1 = "I see. Farewell then, monsieur...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "28");
		break;
		
		
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "The ship is ready, but you do not have room for it. Reduce your squadron and return, and I will immediately give you the frigate.";
				link.l1 = "Fine.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Yes, of course, the ship is ready to sail. The captain is aware and will carry out all your orders.";
				link.l1 = "Then we're setting out. Farewell, Your Grace.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Excellent. Prepare to greet your new ship. The captain is aware and will follow all your orders.";
			link.l1 = "Then we're setting out. Farewell, Your Grace.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateGlp(); 
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}


