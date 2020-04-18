
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Speak, I am listening";
			link.l1 = "I was mistaken. Farewell.";
			link.l1.go = "Exit";
			
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalInPrison")
            {
                link.l1 = "Officer, you've got a prisoner here named Bartolomeo the Portuguese...";
                link.l1.go = "Portugal";
            }
		break;
		
		
		case "Portugal":
			dialog.text = "We have got him. And why do you care? Only envoys of the Dutch West India Company are allowed to see him and only by the written order of the governor. One of the Company's officer is interrogating this pirate right now. So if you've come here just to see him, you'd better go away and quickly.";
			link.l1 = "I have come here not to see him.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Why then, allow me to ask?";
			link.l1 = "To take him!";
			link.l1.go = "fight";
			chrDisableReloadToLocation = true;
			pchar.quest.InMarigoResidenceOver.over = "yes"; 
			InterfaceStates.Buttons.Save.enable = false;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}

