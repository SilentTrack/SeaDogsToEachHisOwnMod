
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
			dialog.text = NPCStringReactionRepeat("Senor, it is best for both of us that we don't talk to each other. They will flog me, and you will be asked to leave.", "I have already told you everything, senor. Or you would want me to be flogged because of you?", "I am not listening...", "The spa-ade is striking and clan-angs the pick...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Stern orders you have there...", "No, of course, I don't want it.", "You don't say!", "Hmm...", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Captain, what are you doing? Put away your weapon, before you make a lot of trouble!";
			link.l1 = LinkRandPhrase("Fine.", "Okay.", "Don't worry, I am putting it away...");
			link.l1.go = "exit";
		break;  
	}
}
