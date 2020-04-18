
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("All the rumors of "+ GetCityName(npchar.city) +" at your service. What would you like to find out?",
                          "We were just talking about that. You must have forgotten...", "This is the third time today you're talking about some question...",
                          "you're harping like a parrot the same...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + NPChar.name + ", maybe next time.", "Right, I've forgotten for some reason...",
                      "Yes, it really is the third time...", "Yep...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince")
			{
				link.l1 = "Tell me, has a galleon by the name of 'Santa Margarita' stopped at your colony lately? Maybe as a privateer prize?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Buddy, it pretty rare that anybody stops by our colony with prizes and we haven't had a galleon with a name like that. We're a small colony, quiet. We mostly do bull carcasses. Privateers don't usually hang around here �we don't have any brothels here and we've got the Spanish in close proximity. So search for your galleon in some other place.";
			link.l1 = "I see. Thanks for the advice!";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "7");
			pchar.questTemp.Guardoftruth = "tortuga";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}


