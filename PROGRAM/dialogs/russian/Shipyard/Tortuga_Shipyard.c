
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?", "How can I help you?"), "You tried to ask me a question a little while ago...", "At his dock, and you know what�I've never seen such flat, curious people before in town.",
                          "What's with all the questions? My job is to build ships. Let's take care about that.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Umph, where did my memory go...",
                      "Hm, well...", "Go ahead...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga1")
			{
				link.l1 = "I'm looking for a Gaius Marchais. The last I've heard was that he docked his galleon Santa Margarita for you to repair...";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "His own galleon? Ho-ho, that's a good joke, captain. Gaius Marchais owned only a half dead sloop... he has captured a galleon as a prize after he decided to become a privateer. Lucky devil, first raid and such trophy\nI offered good coin for her, but he rejected, imagine that! Instead he has sold his pathetic sloop for a small sum and used it to fix the galleon! New sails, new colors and a new name, which is normally not a good sign\nSure, the name was way too papist, but my daughter is also called Margarita, so I guess it was alright after all... He said that he had his fill of violence, so he will do trading. And he had the good fortune...";
			link.l1 = "Commerce, I suppose, would be reposeful, but papist galleons don't just come by every day on a shallop for the pickens. And what's his boat's new name now?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "'Admirable'... No wonder �he would just run around his galleon as if he was chasing his wife, just plain admiring it.";
			link.l1 = "I see. Is Gaius on Tortuga right now?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "No. He's set sail on his new ship and still hasn't returned to Tortuga. Where he took off �I have no clue. He didn't fill me in on that question.";
			link.l1 = "What an inconvenience... I really need him. We should even have a round of drinks for his 'admirable' ship. Anyway, thanks for the information.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Oh, no problem. Stop by again, captain. And don't forget �there's always a space saved in my docks waiting for you ship next time you need some repairs!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "9");
			pchar.questTemp.Guardoftruth = "tortuga2";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}


