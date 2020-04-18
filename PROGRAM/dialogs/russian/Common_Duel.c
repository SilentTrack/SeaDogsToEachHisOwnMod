




void ProcessDuelDialog(ref NPChar, aref Link, aref NextDiag)
{
	int iHour;
	string sLocation;

	
	DeleteAttribute(NPChar, "Outrage");
    switch (Dialog.CurrentNode)
	{
	case "outraged":
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
				RandPhraseSimple("How dare you to insult me, rascal?!", "These words will cost you dearly!"), 
				RandPhraseSimple("My honor is at the stake, " + GetAddress_Form(NPChar) + "! And you will have to pay for that.", "How you dare? Take back your words this instant!"));

		
		MakeRandomLinkOrderTwo(link, 
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("Ha?! I would not even want to stain my sword with your blood!", "Ha?! I would not even want to stain my sword with your blood!"), 
				RandPhraseSimple("I am always at your service!", "I am not going to choose expressions, speaking with the rabble!")), "outraged_1",
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("I didn't mean it!", "I fired up..."), 
				RandPhraseSimple("That was a mistake. I am sorry.", "I took you for someone else, " + GetAddress_FormToNPC(NPChar) + ". Please excuse me.")), "change_mind");
		break;

	case "outraged_1":
		Dialog.Text = NPCharRepPhrase(NPChar,  
				RandPhraseSimple("I'll cut your ears off!", "I'll cut your heart off!"), 
				RandPhraseSimple("I do hope that you'd excuse yourself or I don't guarantee I'll control myself!", "You do realize what it means, don't you?"));

		MakeRandomLinkOrderTwo(link,
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("I do hope that your saber is as swift as your tongue!", "My blade will speak for myself."), 
				RandPhraseSimple("I challenge you to a duel!", "That's a matter of honor!")), "let_s_duel",
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("I think I am not ready yet!", "Think, it is not needed so to get excited! It is words only!"), 
				RandPhraseSimple("I remembered, I am waited. All blessing...", "Ah! Seems, my ship sails already.")), "change_mind");
		break;

	case "let_s_duel":
		
		if (CheckAttribute(PChar, "questTemp.duel.Start") && sti(PChar.questTemp.duel.Start))
		{
			Dialog.Text = "First you settle your business with others, and then we'll talk.";
			if (PChar.questTemp.duel.enemy == NPChar.id)
			{
				Dialog.Text = "We had already come to an agreement.";
			}
			link.l1 = RandSwear() + "Oh, how could I forget...";
			link.l1.go = "exit";
			break
		}
		
		if (rand(100) < 30)
		{
			Dialog.Text = RandPhraseSimple("Duel?! Get lost, you're not worth of wasting time on you.", "Duel? You don't deserve the honor! Get lost!");
			link.l1 = RandPhraseSimple("Alright...", "Guess I can wait...");
			link.l1.go = "exit";
 
			
			if (rand(100) < 30)
			{
				link.l1 = RandPhraseSimple("Well, we'll see about that!!!", "Oh really?! I'll see what color your blood is!");
				link.l1.go = "fight_right_now";
			}
 
			break;
		}

		
		Dialog.Text = RandPhraseSimple("A duel, you say? That's fine with me. Swords and pistols shall be our weapons.", 
			"Can you even wield a sword?");
		link.l1 = RandPhraseSimple("You will be for mercy, standing on your knees.", "I will strangle you with these bare hands, you scoundrel!");
		link.l1.go = "land_duel";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			Dialog.Text = RandPhraseSimple(Dialog.Text + " Or we can ship out and see who's who!", 
				"A duel?!! Ha, I'll squish you like a flea! Choose how you'd want to die!");
			link.l2 = RandPhraseSimple("At sea, I am second to none.", "My ship will easily sink your old tub!");
			link.l2.go = "sea_duel";
		}
		link.l3 = "I changed my mind...";
		link.l3.go = "change_mind";
		break;

	
	case "sea_duel":
		Dialog.Text = RandPhraseSimple("I don't see your ship in the harbor...", "Get lost until you find a crappy old tub at the least!");
		link.l1 = RandPhraseSimple("My mistake...", "...Then I am leaving you.");
		link.l1.go = "exit";
		if (pchar.location.from_sea == GetCurrentTown() + "_town")
		{
			Dialog.Text = "Alright, I'll be waiting for you at the exit from the cove...";
			link.l1 = "I won't keep you waiting for too long.";

			pchar.questTemp.Duel.enemy = NPChar.id;
			pchar.questTemp.Duel.Sea_Location = Islands[GetCharacterCurrentIsland(PChar)].id;
			AddDialogExitQuestFunction("Duel_Sea_Prepare");
		}

		break;

	
	case "land_duel":
		iHour = 1 + rand(2);
		if (GetTime() > 4.0 && GetTime() < 17.0)
		{

		}
		pchar.questTemp.Duel.WaitTime = iHour;
		Dialog.Text = RandSwear() + RandPhraseSimple("Draw steel, and let's see what color your blood is!", "Well, if you have a death wish...");
		link.l1 = RandPhraseSimple("We'd better go someplace without too many witnesses. I know just the right place past the city gates. Let's meet there in " + iHour + " hours.",
			"Hold your horses. Such things are better settled without witnesses. Come in " + iHour + "  hours to the entrance to the city.");
		link.l1.go = "fight_off_town";
		link.l2 = RandPhraseSimple("Well, if you are longing to die that much...", "Damn it! I'll help you to go straight to hell!");
		link.l2.go = "fight_right_now";
		link.l3 = "I changed my mind...";
		link.l3.go = "change_mind";

		if (rand(1))
		{
			Dialog.Text = RandSwear() + RandPhraseSimple("I thing we'd better go past the city gates. I'll be waiting for you there in " + pchar.questTemp.Duel.WaitTime + " hours. Don't delay!", 
				"This is not the best place for settling disputes. We'd better get out of town. In " + pchar.questTemp.Duel.WaitTime + " hours I will be there.");
			link.l1 = RandPhraseSimple("You don't deserve the honor! Defend yourself!", "I have no time! Draw steel!");
			link.l1.go = "fight_right_now";
			link.l2 = RandPhraseSimple("Alright, let's take a stroll.", "You're probably right. Let's meet past the gates.");
			link.l2.go = "fight_off_town_prep";
		}
		break;

	
	case "fight_off_town":
		Dialog.Text = RandPhraseSimple("You don't deserve the honor! Defend yourself!", "I have no time! Right here and now!");
		link.l1 = RandPhraseSimple("Well, if you are longing to die that much...", "Damn it! I'll help you to go straight to hell!");
		link.l1.go = "fight_right_now";
		if (rand(1))
		{
			Dialog.Text = RandPhraseSimple("Alright, let's take a stroll.", "You're probably right. Let's meet past the gates.");
			link.l1 = RandPhraseSimple("I'll be waiting for you there.", "Don't delay.");
			link.l1.go = "fight_off_town_prep";
		}
		break;

	
	case "fight_off_town_prep":
		SaveCurrentQuestDateParam("questTemp.Duel.StartTime");
		PChar.questTemp.duel.Start = true;
		PChar.questTemp.duel.enemy = NPChar.id;
		sLocation = GetCurrentTown();
		if (sLocation != "")
		{
			
			sLocation += "_ExitTown";
			pchar.questTemp.duel.place = sLocation;

			Locations[FindLocation(sLocation)].DisableEncounters = true;
			
			pchar.quest.duel_move_opponent2place.win_condition.l1 = "Location";
			pchar.quest.duel_move_opponent2place.win_condition.l1.location = pchar.questTemp.duel.place;
			pchar.quest.duel_move_opponent2place.function = "Duel_Move_Opponent2Place";
			
			SetTimerConditionParam("duel_move_opponentBack", "Duel_Move_OpponentBack", 0, 0, 0, sti(GetTime() + 0.5) + sti(pchar.questTemp.Duel.WaitTime) + 1, false);
			pchar.quest.duel_move_opponentBack.function = "Duel_Move_OpponentBack";
			if (CheckAttribute(NPChar, "CityType"))
			{
				DeleteAttribute(NPChar, "City"); 
	    		DeleteAttribute(NPChar, "CityType");
				if (!CheckAttribute(NPChar, "PGGAi")) 
				{
					if (!CheckAttribute(NPChar, "LifeDay")) npchar.LifeDay = 0;
					npchar.LifeDay = sti(npchar.LifeDay) + 3; 
				}
    		}
		}
		NextDiag.CurrentNode = "let_s_duel";
		DialogExit();
		break;

	
	case "talk_off_town":
		Dialog.Text = "So, are you ready?";
		link.l1 = "Yeah. Let's see who's a better person!";
		link.l1.go = "fight_right_now";
		link.l2 = "No, I decided to bring the apologies to you. I Was wrong, fired up.";
		link.l2.go = "change_mind";
		if (rand(100) < 20)
		{
			Dialog.Text = RandPhraseSimple("Hey, listen, I meditated on it and I now see that I was wrong. My apologies.", 
				"Damn it! It's all that damned rum!!! My apologies, "+ GetSexPhrase("brother","sister") +"!");
			link.l1 = NPCharRepPhrase(pchar, 
				RandPhraseSimple("No, only your blood can give me satisfaction now!", "Draw steal and stop being such a wuss!"), 
				RandPhraseSimple("No! I demand satisfaction!", "You're the disgrace of your family! Unsheathe your sword!"));
			link.l1.go = "fight_right_now";
			link.l2 = NPCharRepPhrase(pchar, 
				RandPhraseSimple("Alright, I agree. We got a bit worked up.", "Who's keeping score between friends!"), 
				RandPhraseSimple("You're probably right. We shouldn't spill blood on such petty things.", "My generosity knows no bounds! You're forgiven!"));
			link.l2.go = "peace";
		}
		NextDiag.TempNode = npchar.BackUp.DialogNode;
		pchar.questTemp.Duel.End = true;
		break;

	
	case "fight_right_now":
		PChar.questTemp.duel.enemy = NPChar.id;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight_right_now_1":	
		PChar.questTemp.duel.enemy = NPChar.id;
		PChar.questTemp.duel.enemyQty = rand(2) + 1;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();	
		break;
		
	
	case "change_mind":
		if (CheckAttribute(pchar, "questTemp.Duel.End")) LAi_SetWarriorType(NPChar);
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
				RandPhraseSimple("Then get lost!", "Get lost then, before I change my mind."), 
				RandPhraseSimple("In that case I am nit delaying you any longer!", "Then you better leave before I change my mind."));
		link.l1 = "I am already leaving...";
		link.l1.go = "peace";
		break;

	case "after_peace":
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
				RandPhraseSimple("Get lost!", "Disappear from my sight, before I change my mind."),
				RandPhraseSimple("Can I help you?", "Did you want anything?"));
		link.l1 = "I am leaving.";
		link.l1.go = "peace";
		break;

	
	case "peace":
		LAi_SetWarriorType(NPChar);
		NextDiag.CurrentNode = "after_peace";
		DialogExit();
		break;
	}
}
