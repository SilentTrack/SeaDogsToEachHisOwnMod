
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Paleface","White squaw") +" want to talk?", 
				"You again, "+ GetSexPhrase("paleface","white squaw") +".", 
				""+ GetSexPhrase("Paleface loves to talk. Like a squaw.","White squaw love to talk.") +"",
                "Spirits brought my paleface" + GetSexPhrase("brother","sister") + " to me.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes.", 
				"Yes, me again.",
                "Poetic.", 
				"I am glad too to see you.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Good day to you, white brother. You want talk Indian man?";
				link.l1 = "Greeting, son  of jungles. I am glad to see you but I have to go.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Don't tempt your fate, paleface! Sword away!", "Listen, I am the citizen of this town and I'd ask you to hold down your blade.");
			link.l1 = LinkRandPhrase("Fine.", "Whatever.", "Whatever you say...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

