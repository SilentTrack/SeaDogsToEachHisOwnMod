
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What kind of questions?", "What would you like?");
			link.l1 = RandPhraseSimple("I have changed my mind...", "I have got nothing to say now.");
		    link.l1.go = "exit";
			
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && !CheckAttribute(npchar, "quest.Sharlie"))
			{
				link.l1 = "Excuse me, "+GetAddress_FormToNPC(NPChar)+" can you tell me where can I find Michel de Monper? He has to be somewhere in your town.";
                link.l1.go = "Sharlie";
			}	
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "findskiper" && !CheckAttribute(npchar, "quest.Sharlie1"))
			{
				link.l1 = "Listen, "+GetAddress_FormToNPC(NPChar)+", I want to ask something... I am looking for a navigator to serve on my ship, do you know someone in your town?";
                link.l1.go = "Sharlie_1";
			}
			
		break;
		
		case "info":
        
			dialog.text = "Do I work for the secret service of "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Well... farewell then.";
			link.l1.go = "exit";
			link.l2 = "Next question then ";
			link.l2.go = "new question";
		break;
		
		case "town":
        
			dialog.text = "Do I work on an enquiry position? Don't know. Don't know a thing.";
            link.l1 = "Such a muddle-head! See you.";
			link.l1.go = "exit";
			link.l2 = "Next question then ";
			link.l2.go = "new question";
		break;
		
		
		case "Sharlie":
			if (sti(pchar.questTemp.Sharlie.Citcount) == 3)
			{
				dialog.text = "Hm... You must be new here since you fearlessly ask such questions... I advice you to stop that or you'll get troubles on your head otherwise. And about your question... Talk to the abbot. You can find him at the church.";
				link.l1 = "Gratitude!";
				link.l1.go = "exit";
				AddDialogExitQuest("Sharlie_SetBenua");
			}
			else
			{
				dialog.text = LinkRandPhrase("No, I don't know this name.","Can't help you. I have to go, bye.","Sorry, I have never heard that name before. So..");
				link.l1 = "I see... Sorry for troubling you. ";
				link.l1.go = "exit";
				pchar.questTemp.Sharlie.Citcount = sti(pchar.questTemp.Sharlie.Citcount)+1;
				npchar.quest.Sharlie = "true";
			}
		break;
		
		case "Sharlie_1":
			dialog.text = LinkRandPhrase("No, I don't know any navigators.","I have no idea. I have to go, bye.","Sorry, I have never heard that name before. So..");
			link.l1 = "I see. Pardon me...";
			link.l1.go = "exit";
			npchar.quest.Sharlie1 = "true";
			npchar.dialog.currentnode = "first time";
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  
}
