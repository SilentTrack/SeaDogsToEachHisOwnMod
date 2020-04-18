
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want?", "What would you like to know?"), "Tell me, what are you interested in, " + GetAddress_Form(NPChar) + "?", "It's the third time you try to ask...", "I had enough of you. Leave my place!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...", "I have got nothing to say now."), "It seems I've forgotten, sorry...",
                      "You're right it the third time already. Pardon me.", "I am sorry...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Hey, listen - has a man by the name of Joachim Merryman arrived here? A middle-aged senor, Portuguese, with moustache and imperial beard and piercing eyes? Perhaps, he disembarked in a cove or at the lighthouse? Have you seen someone like him?";
				link.l1.go = "merriman";
			}
		break;
		
		
		case "merriman":
			dialog.text = "No, buddy, no one like that. I would have taken notice.";
			link.l1 = "I see. Pity. Alright, I'll continue my search...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}



