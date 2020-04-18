
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What kind of questions?", "What would you like?");
			link.l1 = RandPhraseSimple("I have changed my mind...", "I have got nothing to say now.");
		    link.l1.go = "exit";
			
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Tell me, does the name 'Juan' mean anything for you?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Listen, the frigate under the command of Miguel Dichoso touched a port here in April 1654. He disappeared then. Do you remember anything about it?";
				link.l1.go = "guardoftruth";
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
		
		
		case "Consumption":
			dialog.text = "Are you kidding me? There are Juans in every colony...";
			link.l1 = "I see. Sorry for troubling you...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Come on, captain! Do you think that I remember such things?","Forgive me, senor, I can't help you.","Sir, do you really think that remember such a rubbish? I have got enough of my own problems.");
			link.l1 = LinkRandPhrase("I see. Sorry for troubling you...","What a shame. See you.","");
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}


