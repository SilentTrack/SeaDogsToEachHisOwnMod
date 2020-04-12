// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What kind of questions?", "What would you like?");
			link.l1 = RandPhraseSimple("I have changed my mind...", "I have got nothing to say now.");
		    link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince" && !CheckAttribute(npchar, "quest.Guardoftruth"))
			{
				link.l1 = "Tell me, "+GetAddress_FormToNPC(NPChar)+", was the galleon 'Santa Margarita' here not long ago? As a prize of privateer maybe?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Do I work for the secret service of "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Well... farewell then.";
			link.l1.go = "exit";
			link.l2 = "Next question then ";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Do I work on an enquiry position? Don't know. Don't know a thing.";

            link.l1 = "Such a muddle-head! See you.";
			link.l1.go = "exit";
			link.l2 = "A next question then";
			link.l2.go = "new question";
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("No, I don't remember a galleon with such a name. We actually don't see ships that large here.","Sorry, but I don't even understand you. What galleon? I have no idea.","No, sir, that ship hasn't touched at port or, at least, I don't remember that.");
			link.l1 = LinkRandPhrase("I see...","No questions left...","I see... what a shame.");
			link.l1.go = "exit";
			npchar.quest.Guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

