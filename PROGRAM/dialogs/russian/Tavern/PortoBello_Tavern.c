
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?", "How can I help you, " + GetAddress_Form(NPChar) + "?"), "You tried to ask me some question not long ago, " + GetAddress_Form(NPChar) + "...", "Over this whole day, this is the third time you're talking about some question...",
                          "More questions, I presume?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Umph, where has my memory gone...",
                      "Yes, it really is the third time...", "No, what questions?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";			
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Listen, have you happened to have seen a privateer by the name Francois Gontier? He was recently in your city.";
                link.l1.go = "Portobello_rat_1";
            }			
			
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && !CheckAttribute(npchar, "quest.trial"))
            {
                link.l1 = "Listen, would you be able to tell me where to find a merchant named Jaime Silicio? He was supposedly supposed to come and see you...";
                link.l1.go = "trial";
            }
			
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && !CheckAttribute(npchar, "quest.FMQG"))
            {
                link.l1 = "Look, I am in a search of a man named Bertrand Pinette, have you heard of him? He arrived to Portobello not long ago. An imposing gentleman in a curving wig. A trader. He might had been here...";
                link.l1.go = "FMQG";
            }
		break;
		
		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("No, I don't know. He didn't stop by the saloon and I didn't see him in town either.", "You've already asked about that and I've answered you.", "I told you, you've already asked about that Gontier.", "Listen, walk away and quit bothering me! Have you completely lost your noggin?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Well then, we'll have to look.", "Hm, I guess so...", "Yes, right, I've asked that...", "Sorry, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;		

		case "trial":
			dialog.text = "Senior Jaime Silicio? Oh, that venerable caballero is very well known in our town, especially the past couple of days! Hold on a minute, I'll go get a guy who can bring you to him... Senior Arturo! There's a guy here asking about Jaime Silicio!";
			link.l1 = "...";
			link.l1.go = "exit";
			npchar.quest.trial = true;
			AddDialogExitQuestFunction("Trial_TavernEnterSoldiers");
		break;
		
		
		case "FMQG":
			dialog.text = "Never heard of him, pal.";
			link.l1 = "He is an acquaintance of don Carlos de Milyar. You sure you never heard of him?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "I am. If he is a friend of de Milyar - go to a governor and ask for senor Carlos. He will tell you about this trader of yours.";
			link.l1 = "I might do that. Thanks for an advice!";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "9");
			npchar.quest.FMQG = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}


