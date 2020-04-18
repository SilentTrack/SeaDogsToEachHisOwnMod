
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "We have nothing to talk about!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		
		case "PearlMan":
			NextDiag.TempNode = "PearlMan";
			dialog.text = NPCStringReactionRepeat("Hello! My name is  " + GetFullName(npchar) + ". What can I do for you?", 
				"Hello once again!", 
				"Guest are very rare in this back of beyond...",
                "It's such a pleasure to chat with a new face! I am already sick with all those old snouts...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Oh, nothing, really...", 
				"Me too...",
                "I see...", 
				"Heh...", npchar, Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
		break;
		case "PearlMan_1":
			dialog.text = "We're gathering pearls here, serving  " + NationNameGenitive(sti(npchar.nation)) + ", you know...";
			link.l1 = "Yeah, I know...";
			link.l1.go = "exit";
			link.l2 = "Hey, listen - is it possible to buy several of these little trinkets directly from the producer, so to say?";
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = "Oh no, of course, not! A theft of even just one small pearl is punishable by death!";
				link.l1 = "Cruel orders you have there, that's for sure...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Yeah, we have harsh orders here, and one can easily lose his had for any wrongdoings. I am not dealing in this, but I can advise you to talk to the local Indians about this. They have somewhere to run to if anything goes wrong, so they should be bolder than us...";
				link.l1 = "I see... Alright, thanks.";
				link.l1.go = "exit";
			}
		break;
		case "PearlMan_Sharp_1":
			dialog.text = LinkRandPhrase("Are you totally  "+ GetSexPhrase("crazy? Get lost, you idiot","crazy? Get lost, you stupid woman") +"!", 
				""+ GetSexPhrase("What?! Are you out of your mind, idiot","What?! Are you out of your stupid woman") +"?! Get lost with all your questions...", 
				""+ GetSexPhrase("Have you lost your mind, dear? What pirates? Here?! Just get lost, you dimwit","Have you lost your mind, darling? What pirates? Here?! Just get lost, you stupid woman") +"...");
			link.l1 = RandPhraseSimple("No need to be rude...", "Watch your tongue!");
			link.l1.go = "exit";
		break;

		
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Paleface","White squaw") +" wants to talk?", 
				"You again, "+ GetSexPhrase("paleface","white squaw") +".", 
				""+ GetSexPhrase("Paleface likes talk. He look like squaw.","White squaw likes talk.") +"",
                "Spirits brought my paleface "+ GetSexPhrase("brother","sister") +" to me.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes.", 
				"Yea, me again.",
                "Very poetic.", 
				"I, too, am happy", npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = "Now tell me, why have you come.";
			link.l1 = "Oh, nothing in particular, just wanted to listen to what you have to say.";
			link.l1.go = "exit";
		break;
		
				
		case "CitizenNotBlade":
			dialog.text = "Captain, what are you doing? Put away your weapon, before you make a lot of trouble!";
			link.l1 = LinkRandPhrase("Fine.", "Okay.", "Don't worry, I am putting it away...");
			link.l1.go = "exit";
		break;  

	}
}

