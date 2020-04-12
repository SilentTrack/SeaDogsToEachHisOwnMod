// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("All the rumors of "+ GetCityName(npchar.city) +" at your service. What would you like to find out?",
                          "We were just talking about that. You must have forgotten...", "This is the third time today you're talking about some question...",
                          "you're harping like a parrot the same...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + NPChar.name + ", maybe next time.", "Right, I've forgotten for some reason...",
                      "Yes, it really is the third time...", "Yep...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Slavetrader") && pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Listen, has Francois Gontier happened to stopped by your town by any chance? He has a corvette '" + pchar.questTemp.Slavetrader.ShipName+ "', just in case... ";
                link.l1.go = "Havana_ratT_1";
            }
			if (CheckAttribute(npchar, "quest.batabano"))
            {
                link.l1 = "Tell me, buddy, where could I find Don Diego de Montoya? Am I late? Has he already departed to Main?";
                link.l1.go = "guardoftruth";
            }
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Listen, did a man called Joachim Merriman arrive to your city? An elderly senior, Portuguese, eyes like gimlets, moustache?";
				link.l1.go = "caleuche";
			}
		break;

		case "Havana_ratT_1":
			dialog.text = "Aha, that gloomy fellow? Yes, he's stopped by at my place. I'll tell you a secret: he had an appointment with Oregon-and-Haskon. He applied to receive a patent. But it somehow didn't pan out for him and he got out of there.";
			Link.l1 = "And where did he sail off to, do you know? I'm been chasing after him since Porto Bello and I just can't find him.";
			Link.l1.go = "Havana_ratT_2";
		break;
		
		case "Havana_ratT_2":
			dialog.text = "What do you need him for? He's afraid of outsiders he's always hiding from everybody, as soon as he sees an armed stranger he grabs for his sword. He only walks around surrounded by four guards. Do you happen to be who he's on guard from?";
			Link.l1 = "Lord, people are saying that again and again! What do I look like a killer? He's my buddy, I'm in a hurry to pass on some news to him that he'll be quite overjoyed by and there's no need for him to hide any longer nobody's looking for him.";
			Link.l1.go = "Havana_ratT_3";
		break;
		
		case "Havana_ratT_3":
			dialog.text = "No need for him hide? Ha ha ha! Just one day before his departure from Havana a whole pack of hoodlums jumped on him in the jungle... Of course, he had his own people and they turned them into mince meat in a second. And here you are saying...";
			Link.l1 = "Oh, come on. It was probably just some local bandits jumping on him for his wallet. You know yourself how many scumbags are hanging around the jungle. So where did you go?";
			Link.l1.go = "Havana_ratT_4";
		break;
		
		case "Havana_ratT_4":
			dialog.text = "Well, after he experienced such a turn of events, he kept harping on that he'd  turn himself in to the frog eaters, to his countrymen. He's taken off to Tortuga, to d'Ogeron...He also muttered something about his lover, but I couldn't quite understand him.";
			Link.l1 = "So, Tortuga? Great! I hope I'll catch him there. Thank you, " + npchar.name + ", you've been a ton of help. Bye.";
			Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_7");
			pchar.questTemp.Slavetrader = "FindRatTortuga";
			pchar.quest.Slavetrader_findTortugaRat.win_condition.l1 = "location";
            pchar.quest.Slavetrader_findTortugaRat.win_condition.l1.location = "Tortuga_HouseHut";
            pchar.quest.Slavetrader_findTortugaRat.win_condition = "Slavetrader_findTortugaRat";
		break;

		case "guardoftruth":
			dialog.text = "Hm...And why would these Frenchmen be interested in Don Diego, huh?";
			link.l1 = "The fact that I'm French means nothing. What matters is this document signed by the inquisitor. Have a look... do you see now? I have an urgent message for Diego.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "A-ha, so you work for His Reverence, father Vincento? Sure, this changes things. Don Diego de Montoya left two days ago with his squadron, but soon returned on his courier lugger. One of his ship managed took the ground not far from south Cuba, so he was buying repair material today\nCheck the bay at the South, you shall find there a ship and the man himself. I doubt that they had already managed to fix holes.";
			link.l1 = "Thanks, buddy! You've been a lot of help!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Not at all, any time. I'm always happy to help my Jesuit brothers.";
			link.l1 = "...";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			DialogExit();
			DeleteAttribute(npchar, "quest.batabano");
			AddQuestRecord("Guardoftruth", "47");
			pchar.quest.GuardOT_Batabano.win_condition.l1 = "location";
			pchar.quest.GuardOT_Batabano.win_condition.l1.location = "Shore13";
			pchar.quest.GuardOT_Batabano.function = "GuardOT_SanAntonioPrepare";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Hell if I know, pal. He might had arrived, but I don't know about it. Sorry.";
			link.l1 = "I see. Pity. I shall continue my searches...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

