
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "You've already tried to ask me a question " + GetAddress_Form(NPChar) + "...", "You have been talking about some question for the third time today...",
                          "Look, if you have nothing to tell me about the port's matters then don't bother me with your questions.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind.", "Sorry!"), "Sorry!", "Pardon!", "Sorry!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Good day to you. I'd like to learn about a corvette '" + pchar.questTemp.Slavetrader.ShipName + "' under the command of Francois Gontier.";
                link.l1.go = "Havana_ratP_1";
			}
			
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Excuse me - has a man by the name of Joachim Merryman arrived at your port? A middle-aged senor, Portuguese, with moustache and imperial beard and piercing eyes?";
				link.l1.go = "caleuche";
			}
			
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && !CheckAttribute(npchar, "quest.Mtraxx"))
			{
				link.l1 = "The ship, 'Cantavro'. I am looking for her captain, one Esberdo Cabanas, on a private matter. Could you lend me a hand here?";
				link.l1.go = "mtraxx";
			}
		break;
		
		case "Havana_ratP_1":
			dialog.text = NPCStringReactionRepeat("Yes, he was here. But he has gone already. Ask our tavern keeper about him, he has rented the room in the tavern.", "You have already  about this and I've answered.", "I tell you that you have already asked about this Gontier..", "I ask you to don't bother me!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Thanks. I'll do that.", "Hm, well ...", "Yes, I have really asked ...", "Pardon, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		
		case "caleuche":
			dialog.text = "Can't tell you anything about him. Even if he arrived there, he never go registered anywhere.";
			link.l1 = "I see. Pity. Alright, I'll continue my search ...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
		
		
		case "mtraxx":
			dialog.text = "Let's see... Schooner the 'Cantavro' set sail two days. Mission - patrolling... however, the location is not listed. She is a military vessel, so it will be known only to her captain and the fort commandant. I would suggest you to talk with the commandant directly, at the fort, if you wish to know more. Unfortunately, that is all I can do for you.";
			link.l1 = "I see. Well, thank you for your time...";
			link.l1.go = "exit";
			npchar.quest.Mtraxx = "true";
			AddQuestRecord("Roger_1", "5");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}

