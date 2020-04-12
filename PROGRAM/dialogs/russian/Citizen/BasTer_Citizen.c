// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What kind of questions?", "What would you like?");
			link.l1 = RandPhraseSimple("I have changed my mind...", "I have got nothing to say now.");
		    link.l1.go = "exit";
		break;
		
		case "info":
			dialog.text = LinkRandPhrase("Who are you interested in?","Who do you need?","About who exactly?");
			link.l1 = "I want to know more about Fadey the Muscovite.";
			link.l1.go = "fadey";
			link.l2 = "Let's change the subject...";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("Where do you want to get?","What are you are looking for?","Were to?");
            link.l1 = "Where is Fadey's house?";
			link.l1.go = "fadey_house";
			link.l2 = "Let's talk about something different...";
			link.l2.go = "new question";
		break;
		
		case "fadey":
			dialog.text = RandPhraseSimple("An important man. He rules the local factory and he is on close with the high life in Basse-Terre. The man has a strong accent and he really likes to drink... but he never get drunk.","He is a big shot and a friend of governor. Owes a factory. Came here from a northern country very far way from here... I don't even know the name of it. The has strong hands and is able to drink the whole barrel of rum and won't get drunk.");
			link.l1 = "My thanks!";
			link.l1.go = "exit";
		break;
		
		case "fadey_house":
			dialog.text = RandPhraseSimple("Go straight from the pier until you see the square, a house on the left is the Fadey's mansion.","Go to the pier through the square from the governor's residence, a house on the right is the Fadey's mansion.");
			link.l1 = "My thanks!";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

