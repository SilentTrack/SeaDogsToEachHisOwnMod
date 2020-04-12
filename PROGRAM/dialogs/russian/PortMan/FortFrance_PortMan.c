// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "You've already tried to ask me a question " + GetAddress_Form(NPChar) + "...", "You have been talking about some question for the third time today...",
                          "Look, if you have nothing to tell me about the port's matters then don't bother me with your questions.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind.", "Sorry!"), "Sorry!", "Sorry!", "Sorry!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Ѕрем€ гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "ship" && !CheckAttribute(npchar, "quest.RescueDaughter"))
		{
			link.l1 = "Sir, I am looking for a job. But not a porter job, something more suitable for my rank. Mission, service, help in the delicate matter... I will take any assignment you have got.";
			link.l1.go = "Sharlie";
		}
		//<-- Ѕрем€ гасконца
		break;
		
		case "Sharlie":
			dialog.text = "Help? Hm. I am doing fine, thank God. But one my friend is really in need of help and it's urgent. He intends to go the jungles alone to fight the Indians, this is madness!\nI tried to reason him but he didn't listenЕ He worries to much about his daughter and even ready to give his life for her!";
			link.l1 = "Listen, I don't get it. Let's start again: who is your friend, where can I find him and what kind of help does he need?";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			dialog.text = "Ah, pardon me, I am just too anxiousЕ ProsperЕ He is going to die for sure! And I can't help him - I am not a soldier. His name? Prosper Troubale. His daughter is missing and he believes that the Indians are responsible\nImagine that, he plans to kill some Indian band on his own! They will cut him in pieces... At this moment he is buying a musket and getting ready to go to the selva!";
			link.l1 = "Oh, you are not the best talker... Where can I find your friend...what was his name... Prosper?";
			link.l1.go = "Sharlie_2";			
		break;
		
		case "Sharlie_2":
			dialog.text = "I have just talked with him and was trying to make him change his mind. He is not far from here, near the well. It's left from the door. Speak to him and do something! He won't get away from the jungles alone, I am sure in that. Red skinned devils will torn his...";
			link.l1 = "Enough, stop your complaining. I am heading to your friend immediately. I hope that I will be able to help him.";
			link.l1.go = "Sharlie_3";			
		break;
		
		case "Sharlie_3":
			DialogExit();
			AddQuestRecord("SharlieF", "1");
			RescueDaughter_CreateProsper();
			npchar.quest.RescueDaughter = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

