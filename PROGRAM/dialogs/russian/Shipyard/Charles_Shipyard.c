
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
			
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_2")
            {
                link.l1 = "Listen, master, you're building ships here, right?.. And changing sails as well... have you ever thought of... some better sailcloth fabric?";
                link.l1.go = "mtraxx";
			}
		break;
		
		
		case "mtraxx":
            dialog.text = "You are talking in riddles, sir... Speak frankly - what brought you here? Nothing to worry, I am no pen pusher and this here ain't customs.";
			link.l1 = "Ah, I'm glad we're on the same page! Silk sailcloth, sir. As I understand, there is no better material for the sails if speed is your concern.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Not only speed, but also her ability to sail by the wind. You are offering ship silk for purchase? It's a valuable cargo, indeed. But there is an obstacle: I simply don't know how to use it in production. Do you follow? A material like this requires very special abilities and skills which I lack. To be honest, my shipyard has a very different specialization - had you offered me some ropes from Russia, I'd gladly buy them all. We are in a constant need of ropes, however ship silk is not in demand here, I am sorry!";
			link.l1 = "Hm. I see. Thank you for your time, master. Good luck!";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            DialogExit();
			AddQuestRecord("Roger_2", "4");
			pchar.questTemp.Mtraxx = "silk_3";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}


