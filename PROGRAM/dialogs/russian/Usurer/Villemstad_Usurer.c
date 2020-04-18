
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?", "How can I help you?"), "You tried to ask me that question not long ago...", "Yup, let me guess... Once again going around in circles?",
                          "Listen, I do the finances here, I don't answer questions...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Umph, where has my memory gone...",
                      "You've guessed it, I'm sorry...", "I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Mynheer, I have somewhat of an unusual matter. I know that a French privateer by the name of Gaius Marchais had recently sold you two unique items: a gold ostensory and a gold censer. I would like to purchase them from you.";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(npchar, "quest.GOT_chest") && CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "I've brought you a small chest of doubloons.";
                link.l1.go = "guardoftruth_3";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Oh, yes! I remember them of course! Yes, they really were original, and more importantly, expensive items. But you're too late, captain: I don't have them anymore. I've already sold them.";
			link.l1 = "Incredible! And would  be interested in churchware of that sort? Mynheer, who did you sell them to? I'd like to try to repurchase them...";
			link.l1.go = "guardoftruth_1";
			npchar.quest.utensil = "true";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Hm, and why would I want to give out the name of my clients to you?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "self_win")
			{
				link.l1 = "Maybe because I've a good friend of Governor Matthias Beck and I can acquire a corresponding sanction to him for you?";
				link.l1.go = "guardoftruth_2_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "holl_win")
				{
					link.l1 = "Maybe because I'm in great relations with the Dutch West India Company and would render great help to everyone on the archipelago including Dutch settlers?";
					link.l1.go = "guardoftruth_2_2";
				}	
				else
				{
					link.l1 = "Maybe because I'll pay for it?";
					link.l1.go = "guardoftruth_2_3";
					npchar.quest.GOT_chest = "true";
				}
			}
		break;
		
		case "guardoftruth_2_1":
			dialog.text = "Ah, sure you're "+GetFullName(pchar)+", a friend of the governor himself who disclosed the criminal conspiracy of Lucas Rodenburg... How can I forget about that? Of course, I'll tell you.";
			link.l1 = "Then, I'm all ears.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_2":
			dialog.text = "Ah, right, you're "+GetFullName(pchar)+", the great conqueror of the 'ghost ship'. How could I forget that? Of course, I'll tell you.";
			link.l1 = "Then, I'm all ears.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_3":
			dialog.text = "All right, then. For a chest filled all the way to the top with gold  doubloons, I suppose I'll tell you the people you outraced you to make the purchase.";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "Here, you go. They're very dear items to me...";
				link.l1.go = "guardoftruth_3";
			}
			else
			{
				link.l1 = "All right, I'll bring you what you ask for. They're very dear items to me...";
				link.l1.go = "exit";
			}
		break;
		
		case "guardoftruth_3":
			RemoveItems(pchar, "chest", 1);
			Log_Info("You've given a chest of doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Wonderful. In that case I'm willing to share some information with you.";
			link.l1 = "I'm all ears.";
			link.l1.go = "guardoftruth_4";
			DeleteAttribute(npchar, "quest.GOT_chest");
		break;
		
		case "guardoftruth_4":
			dialog.text = "The gold censer was bought by a man named Rolande Moses, better known as Rollie the Cap. Why this butcher needed a precious church item, I can't wrap my mind around it, but for some reason he was indescribably overjoyed by it... By the way, I doubt you'll meet Rollie himself.";
			link.l1 = "Why is that?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Because this avid pincher of lone English merchants  has recently stumbled right into the paws of Colonel Fox on his schooner. Do you know who that is? ";
			link.l1 = "You bet! The commander of the 'sea foxes' in St. Jones on Antigua...";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Well, then you understand why we will never get a glimpse of poor Rolande again. The colonel seized his schooner with all of the survivors of his crew and delivered them to St. Jones where they've liked already each had a tie fastened around their necks.";
			link.l1 = "I see. And the ostensory?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "The ostensory was acquired very recently by Seniora Belinda de Ribero from Cumana. A very notable seniora, a relative of Fernando de Villegas himself, governor of Cumana. I take it that she wanted to bring it as a gift to the church.";
			link.l1 = "Seniora Belinda de Ribero? I can find here in Cumana, right?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Definitely. She said herself that she was going straight home from Willemstad.";
			link.l1 = "All right. Thanks, "+npchar.name+", you've been a big help!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Anytime, mynheer. Come by again later sometime!";
			link.l1 = "I wish you rich clients with fat wallets and scanty brains... Ha ha!";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			AddQuestRecord("Guardoftruth", "23");
			pchar.questTemp.Guardoftruth.Usurer = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}
