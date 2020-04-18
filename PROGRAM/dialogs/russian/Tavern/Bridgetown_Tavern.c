
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?", "How can I help you, " + GetAddress_Form(NPChar) + "?"), "You tried to ask me some question not long ago, " + GetAddress_Form(NPChar) + "...", "Over this whole day, this is the third time you're talking about some question...",
                          "More questions, I presume?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Umph, where has my memory gone...",
                      "Yes, it really is the third time...", "No, what questions?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "I'd like a drink. Poor me some of the best rum you have.";
                link.l1.go = "TavernDone";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "toBarbados")
            {
                link.l1 = "Listen, where is Callow Gaston?";
                link.l1.go = "Tonzag_Letter";
            }
			
			if (!CheckAttribute(npchar, "quest.HWICTake") && CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Self") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
                link.l1 = "Do you happen to have any kind of work? Or maybe you'd be able to suggest something?";
                link.l1.go = "Tonzag_check";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FernandoDie")
			{
                link.l1 = "I've finished the job. Fernando Rodriguez is dead.";
                link.l1.go = "Task_check";
            }
			
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Listen, has there been an alchemist that arrived here in this town, a physician? He's Italian, about thirty years old, his name is Gino Gvineili. Have you heard anything about that?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		
		case "TavernDone":
			dialog.text = "Here's your drink. The very best rum for our dear guest! Is this a special occasion or have you just dropped by to rinse your throat?";
			link.l1 = "You can say it's a special occasion. I'm taking some slaves into Blueweld. I've recently redone his new brig specifically for this purpose. So, I stopped by a plantation and spoke with the overseer �he ordered a decent batch of 'black wood' from me. So you can expect me back visiting soon. I'll take some merchandise to Blueweld  �I'll be taking it to Barbados, he he...";
			link.l1.go = "TavernDone_1";
		break;
		
		case "TavernDone_1":
			dialog.text = "You don't say? Well, there's no shame in drinking to a good deal! So you say you're going to take the 'merchandise' to Barbados, haha?! That's great...";
			link.l1 = "All right... I'll go look for a place I can sit down.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-12");
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "Tonzag_Letter":
			dialog.text = "Gaston has left the city two day after that 'trader' performance of yours. Your deception was exposed quickly, this town is small and gossips travel fast. This made Gaston to take leave. No one has seen him again here since then. He has left a letter for you, though\nAsked to give it personally to you in case you show up here before him. Actually, you are not the first man looking for Gaston. There was some narrow-eyed big man and an old one. Spanish or Portuguese, I can't tell for sure. But I can't forget his face, something with him was very wrong...";
			link.l1 = "Give me that letter... Thanks!";
			link.l1.go = "Tonzag_Letter_1";
		break;
		
		case "Tonzag_Letter_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-22");
			AddQuestRecordInfo("LetterFromGaston", "1");
			pchar.questTemp.HWIC.Eng = "toCuracao";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", true);
			pchar.quest.Knippel_Shore.win_condition.l1 = "location";
			pchar.quest.Knippel_Shore.win_condition.l1.location = "Shore24";
			pchar.quest.Knippel_Shore.function = "KnippelOnCuracao";
		break;
		
		
		case "Tonzag_check":
			if(sti(pchar.reputation.nobility) > 41)
			{
				PlaySound("VOICE\Russian\hambit\Ercule Tongzag-03.wav");
				dialog.text = "I don't need the services of some shirkers. I don't have any advice I can offer you.";
				link.l1 = "Hey, hey. Easy with the language, buddy!";
				link.l1.go = "exit";
				break;
			}
			if(GetSummonSkillFromName(pchar, SKILL_F_LIGHT) < 25 || GetSummonSkillFromName(pchar, SKILL_FENCING) < 25 || GetSummonSkillFromName(pchar, SKILL_F_HEAVY) < 25 || GetSummonSkillFromName(pchar, SKILL_PISTOL) < 25)
			{
				dialog.text = "Captain, I need a warrior a little more vicious than you. Come back when you learn how to handle that iron dangling on your belt. And a little adroitness wouldn't hurt either.";
				link.l1 = "I see. Then I'll pay you a visit later.";
				link.l1.go = "exit";
				break;
			}
			if(sti(Pchar.rank) > 15)
			{
				dialog.text = "You're too well-known on the Archipelago, cap. I don't think you'd be interested in my assignments.";
				link.l1 = "All right, if you don't think I'd be interested, then what can I do. Farewell.";
				link.l1.go = "exit";
				break;
			}
			PlaySound("VOICE\Russian\hambit\Ercule Tongzag-02.wav");
			dialog.text = "Hm... You're actually on time. I've got one errand that must be fulfilled right away. If you show yourself in good light, I'll introduce you to some influential people. Now listen, here's what you've got to do.";
			link.l1 = "I'm all ears.";
			link.l1.go = "Tonzag_task";
		break;
		
		case "Tonzag_task":
			pchar.questTemp.HWIC.Self.SpainCity = FindSpainCity();
			log_Testinfo(pchar.questTemp.HWIC.Self.SpainCity);
			dialog.text = "One hidalgo has recently arrived from Castilia with intentions to avoid unwanted consequences of� a duel in Europe. But vengeance has no limits and one Spanish noble family wishes this hidalgo dead. Fulfill their request by any means necessary\nBring the target's finger with a ring on it as a proof. Also, bring all items you'll find on his corpse. Are you ready to take the job?";
			link.l1 = "If the payment is dignified, then I'm in.";
			link.l1.go = "Tonzag_task_1";
			link.l2 = "Work as a hit man? No way!";
			link.l2.go = "Tonzag_exit";
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Self = "true";
		break;
		
		case "Tonzag_exit":
			dialog.text = "Then get lost and forget what we talked about.";
			link.l1 = "Have a nice stay.";
			link.l1.go = "exit";	
			DeleteAttribute(pchar, "questTemp.HWIC.Self");
			pchar.questTemp.HWIC.Fail3 = "true";
		break;
		
		case "Tonzag_task_1":
			dialog.text = "Your reward will be 30 000 pesos, good money. Besides, you may take every coin you shall find on his body. Now let's talk details. Name's don Fernando Rodriguez\n35 years, tall, swarthy, dressed like a military. Good sailor and experienced fencer. Can't tell where to find him, all I know that he is somewhere in the Caribbean\nSearch every Spanish city until you got him. You have two months. One last thing: I am aware what he is carrying with him, so don't even think to hide any item from me. Questions?";
			link.l1 = "I don't have any questions. Off I go!";
			link.l1.go = "Tonzag_task_2";	
		break;
		
		case "Tonzag_task_2":
			DialogExit();
			pchar.questTemp.HWIC.Self = "start";
			SetFunctionTimerCondition("TargetFernandoOver", 0, 0, 60, false); 
			AddQuestRecord("Holl_Gambit", "3-1");
			Log_TestInfo(""+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Self.SpainCity)+"");
		break;
		
		case "Task_check":
			dialog.text = "Do you have the finger with the ring on it with you? Let me see it.";
			if (CheckCharacterItem(pchar, "Finger"))
			{
				link.l1 = "Yes, of course. Here it is.";
				link.l1.go = "Task_check_1";	
			}
			else
			{
				link.l1 = "No. Fernando sank in the water along with his ship and the finger sank with Fernando.";
				link.l1.go = "Task_fail";	
			}
		break;
		
		case "Task_fail":
			dialog.text = "The finger with the ring was an obligatory condition in the contract. It was supposed to serve as confirmation of the client's death. Who knows if Rodriquez swam to the shore from out of the sunken ship? Did you check? No. You've basically failed the assignment, so our agreement is over. All the best.";
			link.l1 = "But I did away with him. He's gone! Oh, forget you... There's plenty of other stuff to do on the archipelago. Bye.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Fail3 = "true";
			AddQuestRecord("Holl_Gambit", "3-8");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Self");
		break;
		
		case "Task_check_1":
			RemoveItems(PChar, "Finger", 1);
			dialog.text = "Wonderful! I'll keep the finger myself. Now for the contents of his pockets. Let's have a look what you've brought.";
			link.l1 = "Go ahead, have a look...";
			link.l1.go = "Task_check_2";	
		break;
		
		case "Task_check_2":
			if (CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "totem_05") && CheckCharacterItem(pchar, "amulet_1"))
			{
				dialog.text = "Aha, that's all I need. Well done! You've done a good job. I'm very pleased with you.";
				link.l1 = "Thank you! It's always nice to get praised on a job well done.";
				link.l1.go = "Task_complete";	
			}
			else
			{
				dialog.text = "Hm... I warned you I know what Rodriguez would never do without. And I don't see what I need here. Have you pocketed those things? Did you lose them? It doesn't matter anyway. I have no desire to be involved with you anymore. Get out of here.";
				link.l1 = "Oh, forget you...";
				link.l1.go = "exit";
				pchar.questTemp.HWIC.Fail3 = "true";
				AddQuestRecord("Holl_Gambit", "3-9");
				CloseQuestHeader("Holl_Gambit");
				DeleteAttribute(pchar, "questTemp.HWIC.Self");
			}
		break;
		
		case "Task_complete":
			RemoveItems(PChar, "jewelry7", 1);
			RemoveItems(PChar, "totem_05", 1);
			RemoveItems(PChar, "amulet_1", 1);
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "Here is your reward as promised, thirty thousand. And I also have an additional, high-responsibility, high-risk assignment, but the pay will rise accordingly, �40,000 pesos.";
			link.l1 = "I'm all ears. Who's the next client?";
			link.l1.go = "Fleetwood_house";	
		break;
		
		
		case "Fleetwood_house":
			PlaySound("VOICE\Russian\hambit\Ercule Tongzag-05.wav");
			dialog.text = "This time you are going to hunt not a man, but an item. You must sneak into Richard Fleetwood's house and his log. He is an English captain. The place is being guarded and Richard himself rarely visits the place\nThe plan is simple. The governor of St. Jones will be organizing a private party in ten days, Fleetwood will attend. You must get inside the house at night between one and three o'clock. There will be only one soldier inside\nGet rid of him. Search for a journal inside Richard's apartment. Take this key.";
			link.l1 = "Hm... Interesting. I've got the assignment. I'm ready to get going!";
			link.l1.go = "Fleetwood_house_1";	
		break;
		
		case "Fleetwood_house_1":
			GiveItem2Character(pchar, "key3");
			dialog.text = "Be careful. Don't sneak into the house before the date I've indicated to you. Otherwise, the best case scenario is they'll just kick you out of there or in the worst case, you'll end up behind bars. Repeat to me the date and time.";
			link.l1 = "In exactly ten days, between one and three a.m.";
			link.l1.go = "Fleetwood_house_2";	
		break;
		
		case "Fleetwood_house_2":
			dialog.text = "Okay. Now off you go. Good luck!";
			link.l1 = "Thank you, Gaston.";
			link.l1.go = "Fleetwood_house_3";
		break;
		
		case "Fleetwood_house_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-10");
			pchar.questTemp.HWIC.Self = "theft";
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");
			LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.FleetwoodJournal = 1;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.sand_clock = 1;
			AddDialogExitQuestFunction("CreateFleetwoodSoldiers");
			SetFunctionTimerCondition("FleetwoodJournalOver", 0, 0, 11, false);
			pchar.quest.Fleetwood_Journal.win_condition.l1 = "Timer";
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l2 = "Hour";
			pchar.quest.Fleetwood_Journal.win_condition.l2.start.hour = 0;
			pchar.quest.Fleetwood_Journal.win_condition.l2.finish.hour = 3;
			pchar.quest.Fleetwood_Journal.win_condition.l3 = "locator";
			pchar.quest.Fleetwood_Journal.win_condition.l3.location = "SentJons_town";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator_group = "reload";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator = "houseSP3";
			pchar.quest.Fleetwood_Journal.function = "FleetwoodHouseEnter";
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("No, I haven't. We have herbalists and physicians, but none of them with such a name.","This is the first time I've heard such a weird name. No, we've never had a visit from the man you speak of.","We don't have any kind of alchemists at all. We've got physicians, but none with such a weird name.");
			link.l1 = "I see. That's too bad. I'll keep looking!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}

string FindSpainCity()
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation == SPAIN && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && colonies[n].nation != "none")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[dRand(howStore-1)];
	return colonies[nation].id;
}
