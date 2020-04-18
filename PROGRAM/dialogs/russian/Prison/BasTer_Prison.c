
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Speak, I am listening";
			link.l1 = "I was mistaken. Farewell.";
			link.l1.go = "Exit";
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "true")
            {
                link.l1 = "There is an Indian under arrest. He was captured by Fadey the Muscovite. Can I talk with him?";
                link.l1.go = "Tichingitu";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "commandante")
            {
                link.l1 = "Tell me, are you really going to hang this Indian? Is that not a too tough punishment for such a small crime?";
                link.l1.go = "Tichingitu_3";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "pay")
            {
                link.l1 = "It is me again, commandant. Fadey the Muscovite has written this petition for freeing the Indian. Here it is.";
                link.l1.go = "Tichingitu_6";
            }
		break;
		
		case "Tichingitu":
			dialog.text = "A-ah, Fadey has told you his story? I have no reasons to forbid you from taking a look at him, monsieur. You are not the first who come to see that Indian. In ten days every citizen will be able to observe hanged Indian though...";
			link.l1 = "So can I enter the prison?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "I 'have told you already that I have no reasons to forbid you that. Move along.";
			link.l1 = "Thanks!";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "Tichingitu_3":
			dialog.text = "You are new here, aren't you, monsieur? Right from Europe? You don't understand a situation in the colonies. This execution will be a lesson for the rest of red skinned bastards who would dare to encroach on the property of French colonists. Besides, Fadey himself insists on that and he is a very respected man here and the close friend of our governor.";
			link.l1 = "Is there any way to soften the punishment? I still think that it is too tough...";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Oh, don't go into philosophy! Go to Fadey and ask for this Indian if you really that care about his fate. If Fadey will write a petition for freeing, we would satisfy it.";
			link.l1 = "Understood, officer. I'll go to Fadey.";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "fadey";
		break;
		
		case "Tichingitu_6":
			RemoveItems(pchar, "letter_1", 1);
			dialog.text = "(reading) Hm... This Fadey is strange... He has demanded for a demonstrative execution and now he is asking to release this Indian... Whatever, I suppose that all governor's friends are like him. Fine, you can go and take this red one.";
			link.l1 = "My thanks, officer!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_6";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}

