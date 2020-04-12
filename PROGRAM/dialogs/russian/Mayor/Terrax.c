// Маркус Тиракс, барон Ла Веги
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && !CheckAttribute(npchar, "quest.mtraxx_complete")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "Ah Prince, finally you are here. At least one of you was bothered to come to me! There is business to be done and all of you have disappeared! Where the hell the rest are?";
					link.l1 = "No a clue... Marcus I am out. I had enough. Too much blood was spilled recently.";
					link.l1.go = "mtraxx_113";
					break;
				}
			}
			// Jason НСО
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Got any business for me?";
				link.l1 = "Greetings, Marcus. Yes, an affair. Financial and related to pirates.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Did you bring the money?";
				link.l1 = "Yes.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "That's our customer! The job is done, your baron is sitting in a well-guarded dungeon. Perhaps you'd like to take a look, he-he?!";
				link.l1 = "I will have plenty of time to do that, haha. Is he well-treated?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, what the hell!..";
				link.l1 = "Markus, there was an overlap. I could neither come nor inform you about my abscence...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Here's our puppeteer!";
				link.l1 = "Ha-ha! The spectacle was perfect";
				link.l1.go = "patria_x29";
				break;
			}
            dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("У тебя дело ко мне? Нет? Тогда вали отсюда!","Ха, " + pchar.name + "! У тебя дело ко мне? Нет? Тогда не отвлекай меня.") +"",
                         "I trust that I have made myself clear... Although I've made myself clear, you keep annoying me!",
                         "Right, I am getting tired of this rudeness.", "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I am leaving already.",
                                               "Sure, Marcus...",
                                               "Sorry, Marcus...",
                                               "Oups...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Are you insane? Wanted to play a butcher? All pirates are angry with you, pal, so you better leave this place…Are you insane? Wanted to play a butcher? All pirates are angry with you, pal, so you better leave this place.", "It seems, pal, that you got mad. Wanted to stretch your hands a bit? No offence, but you have nothing to do here. Get lost!");
				link.l1 = RandPhraseSimple("Listen, I want to fix the situation.", "Help me to solve the problem.");
				link.l1.go = "pirate_town";
				break;
			}
			// Сага - завершаем искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				// Addon 2016-1 Jason пиратская линейка патч 17/1
				if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Marcus will you ever stop being mad with me? I have saved your friend Vincent who once accompanied us in our raid on Cartagena, by the way I also saved your ass too! Or didn't Bernard even tell you?";
					link.l1.go = "Temptation_13";
				}
				else
				{
					link.l1 = "Why are you so rude, Marcus? Or haven't Bernard told you about me?";
					link.l1.go = "Temptation";
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "to_lavega")
			{
				link.l2 = "I want a job... Have anything profitable on your mind?";
				link.l2.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "I have a silk to sell.";
				link.l2.go = "Mtraxx_silktrade";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Are you insane? Wanted to play a butcher? All pirates are angry with you, pal, so you better leave this place...", "It seems, pal, that you got mad. Wanted to stretch your hands a bit? No offence, but you have nothing to do here. Get lost!");
				link.l1 = RandPhraseSimple("Listen, I want to fix the situation...", "Help me to solve the problem...");
				link.l1.go = "pirate_town";
				break;
			}
			// Jason НСО
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, what the hell!..";
				link.l1 = "Markus, there was an overlap. I could neither come nor inform you about my abscence...";
				link.l1.go = "patria_33";
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Glad to see you, friend!";
				link.l1 = "Glad to see you too. Thank you for the perfect spectacle!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Glad to see you, pal! How can I help you?";
				link.l1 = "I have a proposal for you. Pirate stuff, you know!";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "That's our customer! The job is done, your baron is sitting in a well-guarded dungeon. Perhaps you'd like to take a look, he-he?!";
				link.l1 = "I will have plenty of time to do that, haha. Is he well-treated?";
				link.l1.go = "patria_10";
				break;
			}
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Got any business for me?";
				link.l1 = "Greetings, Marcus. Yes, an affair. Financial and related to pirates.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Did you bring the money?";
				link.l1 = "Yes.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "That's our customer! The job is done, your baron is sitting in a well-guarded dungeon. Perhaps you'd like to take a look, he-he?!";
				link.l1 = "I will have plenty of time to do that, haha. Is he well-treated?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Какого дьявола!..";
				link.l1 = "Marcus, there was an overlap. I could neither come nor inform you about my abscence...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Here's our puppeteer!";
				link.l1 = "Ha-ha! The spectacle was perfect!";
				link.l1.go = "patria_x29";
				break;
			}
			// Тени прошлого
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Glad to see you, pal! How can I help you?";
				link.l1 = "Marcus, I have to talk to you. I am not sure that you'll like it but I need your help anyway.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Ha, here you are, "+pchar.name+". I was expecting your arrival. The Wood Devil has puzzled me with you Tortuga's matter...";
				link.l1 = "He has also told me that you have found a solution to it. Am I right?";
				link.l1.go = "terrapin";
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "I have a silk to sell.";
				link.l2.go = "Mtraxx_silktrade";
			}
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", Glad to you! What do you want?",
                         "What do you want?", "Again? Don't bother people if you have got nothing to do!",
                         "And "+ GetSexPhrase("good privateer","good girl") +", you can live for now. But I don't want to talk to you anymore.", "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Just wanted to see you.",
                                               "Nothing.",
                                               "Fine, Marcus, I am sorry.",
                                               "Damn it, caught it at last!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Robbery!!! That is unacceptable! Prepare yourself, rat...", "Hey, what are you doing there?! Thought that you could rob me? You are done...", "Wait, what the hell? Turns out that you are a thief! End of the line, good man...");
			link.l1 = LinkRandPhrase("Damn!", "Carramba!", "Ah, damn it!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("Go away","Get away") +" from here!", "Get away from my home!");
			link.l1 = "Oups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Don't bother me from my work by your worthless promises. Next time it won't end that good for you...";
        			link.l1 = "I get it.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("I am tired of you.", "I don't want to talk with you, so you better keep distance from me.");
			link.l1 = RandPhraseSimple("Whatever...", "Hm, fine then...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "I hope that you won't bother me with your bubble talk anymore or I'll have to kill you. I say, that I won't be glad to do so.";
        			link.l1 = "You can be sure in that, Marcus, I won't...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		
//--> -----------------------------Сага - Искушение Барбазона завершающие этапы---------------------------
		case "Temptation":
			dialog.text = "Ha! The hero of Turks? Sorry for the rough greeting, pal. Bernard has already told me about your wonderful involvement and said something about a trap for me. I'd like to hear the details...";
			link.l1 = "It was a trap. They were after you not Bernard.";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "";
			link.l1 = "The plan was simple. It was supposed that you'd run to save your pal and would be the first on the board of 'Separator'. And right then they had to shoot it and blow it sky high. The brigantine was loaded by gunpowder like a hell.";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Damn! Whose idea was this meanness?! And how could I know where they were hiding Bernard?!";
			link.l1 = "The authors of this plan were Jackman and his brother David. A messenger would make you know that the 'Separator' is waiting for your help in the Southern bay of Turks. They have chosen me as that messenger and it was their mistake.";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "I don't get it! What's your role in all of this?";
			link.l1 = "I've been watching that bastard Jackman for a long time.  I work with Jan Svensson if you don't know. Me and the Wood Devil have decided to expose him. Jan is sure that he is responsible for Blaze's death and Steven was accused for nothing.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end") link.l1.go = "Temptation_14";
			else link.l1.go = "Temptation_4"; //патч 17/1
		break;
		
		case "Temptation_4":
			dialog.text = "Heh! But there was a shark's tooth with his initials - S.D. This thing belongs to Steven, everyone knows that...";
			link.l1 = "It was planted. Jackman played with a high stake. He has gotten rid of Nathaniel Hawk and took his place in Maroon Town, then he murdered Sharp and made Shark responsible for the murder. I have enough proofs of his crimes. I have found them in Jacob's chest. There was the second part of the Sharp's map and the Hawk's shard.";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			dialog.text = "Damn! So Steven is innocent? And why has Jacob done all of this?";
			link.l1 = "He was counting to become the head of the Brotherhood and getting Isla Tesoro. He couldn't get yours and Svensson's support so he has decided to get rid of you both. You was the first in the list. Jan is a tough one so he was the second.";
			link.l1.go = "Temptation_6";
		break;
		
		case "Temptation_6":
			dialog.text = "Where is this bastard?! I will torn him apart!";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Jackman and his brother are dead as well as the rest of hunters. I have personally dealt with them. The bastard won't harm anyone anymore. Marcus, would you vote for Steven Dodson? This is my personal ask.";
				link.l1.go = "Temptation_7";
			}
			else
			{
				link.l1 = "Jackman and his brother are dead as well as the rest of hunters. I have personally dealt with them. The bastard won't harm anyone anymore. Unfortunately Steven is dead...";
				link.l1.go = "Temptation_10";
			}
		break;
		
		case "Temptation_7":
			dialog.text = "Sure I'll vote! I was always considering the Shark the most worthy of all of us. And I've almost believed in his guilt. We all have! Here, take my shard.";
			link.l1 = "Nice! Now you can breath freely.";
			link.l1.go = "Temptation_8";
		break;
		
		case "Temptation_8":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "True... I understand, that you represent the Shark's interests?";
			link.l1 = "Yes. Me and Jan Svensson. Fine, Marcus, see you there!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_10":
			dialog.text = "Dead?! How? Jackman's work too?";
			link.l1 = "No. His own boatswain did it, Chad Kapper was his name. He has already got what he deserves... Marcus, Svensson thinks that you are the worthiest to be the new president of the Brotherhood. The rest of barons will support this decision. Do you accept this?";
			link.l1.go = "Temptation_11";
		break;
		
		case "Temptation_11":
			dialog.text = "Heh! You don't need to ask me twice. It's a great honor to be the Head of the Brotherhood! Don't hope that I'll disagree.";
			link.l1 = "Splendid. I am glad that you have accepted this.";
			link.l1.go = "Temptation_12";
		break;
		
		case "Temptation_12":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Here, take my shard. Deliver it to Svensson. I take it that he is in charge?";
			link.l1 = "Yes, he is. Fine, Marcus, see you there!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_9":
			dialog.text = "Yes, and I want to thank you for saving my friend Bernard. Here, take this purse with gold.";
			link.l1 = "Thanks! Farewell!";
			link.l1.go = "Temptation_exit";
		break;
		
		case "Temptation_exit":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 300);
			Log_Info("You have received 300 doubloons");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "25");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "Temptation_13":
			dialog.text = "Yeah, he told me about a magnificent arrival of Charlie Prince at Turks... Saved my ass you say? How? Bernard told me something about a trap...";
			link.l1 = "It was a trap. You was the target, Bernard was a bait...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_14":
			dialog.text = "Ha-ha, working for the Forest Devil, huh Prince? What, did you make better coin with him that you did with me? Tell me in all honesty!";
			link.l1 = "Marcus let's set aside the past for good. We have a common goal now and it's much more vital than plundering caravans.";
			link.l1.go = "Temptation_15";
		break;
		
		case "Temptation_15":
			dialog.text = "Fine Prince let's do that! You are a freelancer after all, working for the Forest Devil was a right thing to do... Steven then... You said they slandered him?";
			link.l1 = "Yeah.";
			link.l1.go = "Temptation_4";
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Sure, I'll help you as I can! Go on.";
			link.l1 = "Take a look, Marcus... Here is a shark's tooth. What can you tell me about it?";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ha! It is a tooth of white shark which was killed by late Steven Dodson hoping to make an impression on one girl. They have started to call him the Shark since then. A very few could do that under water using just a simple sword. But he was young and stupid and Beatrice Sharp was the most beautiful girl in all of Caribbean... How have you got it?";
			link.l1 = "It was given to me by the ex-hangman of St. John's. This tooth was used to slay one man. His name was... Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "That is an old story. Steven did kill that man. He was shocked by the death of Beatrice and he thought that Leadbeater is the only living person responsible for her death. Though later he had found some papers on his corpse, studied them and repented his deed\nThe Mask wasn't to be blamed for Beatrice's death, he was only for Butcher. Butcher's jealous ex girlfriend Jessica had set up the whole thing.";
			link.l1 = "Have you read those papers?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Why should I? Of course not. I don't need them. But I can tell you the Mask was pursuing Butcher if you've got some spare time. Drunken Steven has been telling me this story for a few times.";
			link.l1 = "I have got time. Trust me, my interest has got purpose. I can even pay you for it.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "I know, that you never waste your time. Listen then. Joshua Leadbeater was the English naval captain and the famous 'Neptune' was under his command...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... Leadbeater has made it though and was picked up by some ship. His wound has defaced him and since then he was wearing a mask. They called him the Mask. His life's meaning has become to revenge and to punish the culprit of all of his hardships.";
			link.l1 = "I see... I have written all of it. I think that I must to re-read it. A sad story though. Have you seen Jessica?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Sure! She accompanied Butcher in all his voyages until he dumped her for Beatrice. Jess couldn't forgive him that. They called her the Butcher's talisman, because he always had luck while she was there with him\nBelieve it or not, but as soon as he got rid of her at Barbados, his business went bad, booty got poor and Neptune became an often guest at the shipyard of Isla Tesoro. Though it can be explained by the fact that Butcher had been spending most of his time with Beatrice in the cabin rather then at the quarterdeck\nBeatrice was not like Jessica, she wasn't addicted to adventures and war, although Nicolas taught her fencing and seamanship. Yes, she was fond of sea romance but she didn't have enough hardness of character. Butcher's Neptune wasn't the right place for her. In the end, it killed her.";
			link.l1 = "And what about Jessica?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Oh, she was something Every sailor of Neptune obeyed her orders and not just because she was a captain's girlfriend. Jess had mastered fencing and seamanship, Butcher's efforts were not wasted. She was tough and reckless, and also was gifted with a good look\nA lot of men wanted to share a bed with her, but she wanted Butcher only, bothering her was really risky - many tested the results on their own backs literally, and for the most persistent her fencing lessons turned to be the last\nJess owned a very special sword, the only of it's kind in the Caribbean, I have no clue where did she get. Flame-bladed sword. One can't grab it's blade and even the slightest touch leaves a terrible wound\nJess was an adventurer not by birth, but by vocation. By the way, if you need to learn more about her, you can talk to an acquaintance of yours. He can tell you about her much more than I can.";
			link.l1 = "Really? And who is this man?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svensson. Forest Devil will never admit it, but he had plans about Jessica. That was the time when he had already taken Western Main for himself and his fame was something to envy for, so the tigress was as good as him\nAfter Butcher got rid of Jess, Jan started to visit Barbados suspiciously often giving a shake to English garrison. As you know, Jessica was a daughter of Bridgetown's planter\nAll in all, his plans were well known in private circles, yet no one dared to speak one's mind about it, Jan may sit on his backsides in Blueweld now days, but back then any wrong word in his address could result badly\nIn the end, it didn't work out for them. Jess couldn't live with the way Butcher treated her and she had her revenge a year later with a help of the Mask. This vengeance ended terrible for everyone: for Butcher, for Beatrice, for the Mask and for herself. They all died.";
			link.l1 = "Nope. Butcher is alive.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "What?! Have I heard you wrong? Is he?!";
			link.l1 = "Yes. Captain Butcher wasn't hanged. He was actually but thanks to Jacob Jackman and Henry the Hangman, who have scared the hanger, he has made it alive. The hang was only a performance. I have got proofs.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Incredible! And where is he now?";
			link.l1 = "He is know as Lawrence Beltrop and he lives in Port-Royal. But it looks like that he hasn't changed and he is still that dangerous. Jackman who has made so many troubles inside the Brotherhood was following his orders.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "Damn! Quartermaster has found his captain after all! After so many years... Beltrop you say... wait! Now I see why in Blaze's papers was that strange protocol of the interrogation... It seems that Blaze has found out something about Butcher-Beltrop...";
			link.l1 = "What are talking about?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "When I have taken this residence I have afforded myself to take a look at Blaze's papers. I have found a protocol of interrogation of someone called Samuel Brooks. There was a lot of details about adventures of Thomas Beltrope, a famous pirate and a closest friend of Nicolas Sharp. It seems that he is a father of Butcher.";
			link.l1 = "Interesting. Looks like Beltrop's and Sharp's kids has carried their fathers job...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "It seems so... Tell me, friend, why are you so interested in the past of people who have been dead for a long time already? What's this all about?";
			link.l1 = "I need papers which could prove that Ellen McArthur is a daughter of Beatrice Sharp and a granddaughter of Nicolas Sharp and has all rights to carry this surname. I don't care that her surname could be Beltrop.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "I have found nothing about Ellen McArthur in the Blaze's archives. It is strange that Beatrice hasn't told Blaze about his niece birth. It's not her style.";
			link.l1 = "Listen, maybe there is something more in Sharp's papers about this story? I need every detail I can get!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Hm… I guess. According to Blaze's notes, he had been trying to find the island where his sister died. There are papers concerning Leadbeater's punitive expedition. Nothing interesting, except for a few numbers of latitude\nThis parallel crosses Caribbean sea in it's Northern part. But there is no sign of longitude. Obviously, Blaze's searches failed, you can not even imaging how many small islands at that latitude.";
			link.l1 = "And what's the latitude?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Let's see... Here: 21 32' North. I don't know how it can help you.";
			link.l1 = "It can. Thanks you, Marcus, for your confident story. See you!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "I_know_you_good";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "terrax"; // 280912
		break;		
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "Well, I can do something for you. As you know, Tortuga's security is not only provided by fort La Roche but also by a pirate squadron constantly guarding the shores of the island. The port of Tortuga is safe, these lads know their business and they have powerful ships. Levasseur has been buttering the captains for a long time\nThey are capable of fighting even against a line squadron and they will be serious opponents. So, being the keeper of the Code and also the leader of Brethren of the Coast I can make these watch dogs leave Tortuga's shores.";
			link.l1 = "And that's it?";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Is that not enough? I can help you more anyway. You have to storm the fort but at least you don't need to fight those guard ships now. Trust me, there are far too more dangerous than the Fort so my help will make it all easier.";
			link.l1 = "Well if I have to attack it anyway, the leaving of pirate's squadron will really help. Thanks, Marcus! When can I attack Tortuga?";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Whenever you want. The guard ships will leave on my signal.";
			link.l1 = "Fine. I have to go then to prepare myself.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			DialogExit();
			// Левассера - к барьеру!
			sld = characterFromId("Tortuga_Mayor");
			LAi_LoginInCaptureTown(sld, true);
			pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
			pchar.questTemp.Terrapin = "hardcore";
			pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
		break;
		
		case "pirate_town":
            dialog.text = "Solve the problem? Do you have any clue what you have done? Anyway, bring me a million pesos and I will persuade lads to forget your deed. If don't like the idea then you may go to hell.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Fine, I am ready to pay.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Farewell...";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Good! Consider yourself clean again. But I hope that you will not do such disgusting things again.";
			link.l1 = "I won't. Way too expensive for me. Farewell...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		// Addon 2016-1 Jason ------------------------- пиратская линейка --------------------------
		case "Mtraxx":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "First get a ship for yourself, then ask for a job. A land rubber has nothing to do here. Get lost!";
				link.l1 = "K-hm... I see.";
				link.l1.go = "exit";
				break;
			}
            dialog.text = "Want some action, huh? Ha! Good... Though I warn you, pal, you won't find any peace with me. If you are afraid of a smell of gunpowder or you can't spill blood - the door is behind you. I can't stand sissies. Also you won't last long enough with me if you are a snitch or a rat who fancy stealing a partner's share of plunder. So what? Are you in?";
			link.l1 = "I am in, Marcus. No dog can blame me of being either a coward or a rat.";
			link.l1.go = "Mtraxx_1";
			link.l2 = "Whoa, that's a tough interview! Beg pardon, Marcus, but I better take my leave...";
			link.l2.go = "Mtraxx_exit";
		break;
		
		case "Mtraxx_exit":
            DialogExit();
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_wait":
            dialog.text = "What, are you still here?";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Ha-ha, well-well, my brave little pirate, let's talk business then. My source in Santo Domingo informed me about some Spanish captain who is so rich with blue amber that he is gifting whores with it. Have you heard about blue amber?";
			link.l1 = "I have. A rare and valuable stone.";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Precisely. Even here, bankers and jewelers are paying a good coin for it and in old good Europe you can get ten times more. Amber is not a rare stone in the Caribbean but the blue one is a rarity. And now we have some Castilian sly dog bragging about having tons of it.";
			link.l1 = "Can the stories of some drunk Spanish be trusted?";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "I wouldn't had bought that but he was actually gifting whores with blue amber. Something in his bragging must be trustworthy. Go to Santo Domingo and investigate. If you find the blue amber deposit that would be even better. Do this and I can guarantee you a reward and respect in La Vega.";
			link.l1 = "What if your information is worthless?";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "Then prove to me that the Spanish is a liar.";
			link.l1 = "Very well. Who is you source in Santo Domingo?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "You need to find a whore called Gabriela Chapada. Mention my name a tell her a password - 'An amber necklace'. She will give you the details. Make haste, you have only a few days.";
			link.l1 = "Got it, Marcus. Heading to Santo-Domingo.";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_1";
			pchar.questTemp.Mtraxx.AffairOfHonor = "true"; // конфликт с делом чести
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_1", "1");
			Mtraxx_JewelryBegin();
		break;
		
		case "mtraxx_7":
			i = GetCharacterItem(pchar, "jewelry7");
            dialog.text = "I was already informed about your arrival. Give me a report!";
			link.l1 = "I've dealt with that blue amber lover although it wasn't easy. I have managed to find his deposits and plunder them. I have brought you "+FindRussianQtyString(i)+" pieces of blue amber.";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
			if (sti(pchar.questTemp.Mtraxx.JewQty) > GetCharacterItem(pchar, "jewelry7"))
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", GetCharacterItem(pchar, "jewelry7"));
				dialog.text = "Well-well... Son, you remember my warning about dangers of being a rat? What did you say to me then? No dog can blame you for that? You think I am stupid, kid? I am perfectly aware that you have plundered "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.JewQty))+" pieces of blue amber at Mosquitoes Coast. Now run, little rat, run, and pray we never meet again!";
				link.l1 = "Damn it!..";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.Dialog.currentnode = "First time";
				CloseQuestHeader("Roger_1");
			}
			else
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", sti(pchar.questTemp.Mtraxx.JewQty));
				dialog.text = "Nicely done, pal! Your results do you credits. I am glad I wasn't wrong about you.";
				link.l1 = "What about my cut, Marcus?";
				link.l1.go = "mtraxx_9";
			}
		break;
		
		case "mtraxx_9":
			i = sti(pchar.questTemp.Mtraxx.JewQty)/2;
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+FindRussianQtyString(i)+" pieces of blue amber");
			TakeNItems(pchar, "jewelry7", i);
            dialog.text = "Spoken by a true pirate, ha-ha! Half of plunder is yours. Take it.";
			link.l1 = "Thanks, captain. Got anything else to assign to me and my brave men?";
			link.l1.go = "mtraxx_10";
			DeleteAttribute(pchar, "questTemp.Mtraxx.JewQty");
			CloseQuestHeader("Roger_1");
			Achievment_SetStat(pchar, 57, 1);
		break;
		
		case "mtraxx_10":
            dialog.text = "I always have tasks for capable lads. There is a delicate business I want you to deal with. There is a ship stationed in Capsterville, called the Snake under command of Geffrey Brooke also known as Bald Geffrey. He works for me. An excellent fighter, knows everything about guns and blades yet a complete idiot in every other aspect of life. But let's not be rough with Baldy - you can't be good at everything, ha-ha!\nSo. This tough guy had hit hard a Dutch convoy and captured a bark filled with sacks of wheat. Thing is, he managed to find hidden ship silk among the sacks. A great deal of ship silk. This merchandise is extremely valuable and rare, the Dutch bring it from Europe for the needs of their military only. This silk is used for very special sails which increase ship's speed and ability to sail by the wind\nIt is almost impossible to buy, selling it is not a problem yet it is hard to find the right price. I am aware that there are people who are ready to pay a great deal in doubloons for this silk and your goal is to find such people\nWhat? Any fool can plunder caravans but trade is only for people with at least a sign of brains' existence in a skull. I am planning to sell ship silk on a monthly basis so your goal is to find a regular buyer who will pay at least twenty golden doubloons for a roll. You have two months to do that, I can not keep Bald Geffrey in Capsterville forever\nThat'll be all. Set sail to Capsterville and talk to Geffrey before he sells the cargo to smugglers for a penny. I've already told you that he is a bit simple.";
			link.l1 = "Hm... Got it. Already on my way.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_1";
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_2", "1");
			Mtraxx_SilkBegin();
		break;
		
		case "mtraxx_12":
            dialog.text = "Ha! "+GetFullName(pchar)+", a brave captain! What about the buyer?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				link.l1 = "I've found you a buyer. That's a shipbuilder of Port Royal. He needs ship silk for his production and he will be buying batches of one hundred rolls every month with a price of 25 doubloons for a roll. His men will be receiving the goods from 10th to 15th, at night, Negril Cape. The password - 'A merchant of Lyons'. It took me more than two months to find such buyer, Geffrey must had already sold the silk to smugglers. I am sorry, Marcus.";
				link.l1.go = "mtraxx_15";
			}
			else
			{
				link.l1 = "I've found you a buyer. That's a shipbuilder of Port Royal. He needs ship silk for his production and he will be buying batches of one hundred rolls every month with a price of 25 doubloons for a roll. His men will be receiving the goods from 10th to 15th, at night, Negril Cape. The password - 'A merchant of Lyons'. Bald Geffrey already has the first batch delivered to Jamaica.";
				link.l1.go = "mtraxx_13";
			}
		break;
		
		case "mtraxx_13":
            dialog.text = "That's great, my friend! Nicely done. It is hard to find a man capable of using both hands and a head. See me in 20 days to collect you reward."; // правки прогона 3
			link.l1 = "Very well, Marcus. See you soon. Hope you shall have another job for by then.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_14":
            dialog.text = "I will. See you later.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 30, false);
				SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 40, false);
				AddQuestRecord("Roger_2", "23");
			}
			else
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 20, false); // правки прогона 3
				SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 30, false);
				AddQuestRecord("Roger_2", "24");
			}
		break;
		
		case "mtraxx_15":
			pchar.quest.Mtraxx_SilkTimeLateAll.over = "yes";
            dialog.text = "Pity, but it is still a huge success. You did a good job and you shall have your reward although absent your cut from Geffrey's batch. See me in a month after I sell the first batch to your buyer, then we shall talk.";
			link.l1 = "Very well, Marcus. See you soon. Hope you shall have another job for by then.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_16":
			pchar.quest.Mtraxx_SilkPayLate.over = "yes";
            dialog.text = "There you are, "+pchar.name+". Let's talk your reward.";
			link.l1 = "I like where this is going, ha-ha! I am all ears.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate")) link.l1.go = "mtraxx_19";
			else link.l1.go = "mtraxx_17";
		break;
		
		case "mtraxx_17":
            dialog.text = "Bald Geffrey has sold to your buyer the first batch of 105 rolls of ship silk. Since I was expecting to sell it for twenty doubloons for a roll, I think it would be fair to give you the difference. That's my decision. Your share is 525 doubloons plus a bonus - a doubloon for a roll. It is 630 doubloons in total. Here, take them.";
			link.l1 = "Gratitude, Marcus!";
			link.l1.go = "mtraxx_18";
		break;
		
		case "mtraxx_18":
			TakeNItems(pchar, "gold_dublon", 630);
			Log_Info("You have received 630 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "One more thing. You can get an extra profit of this.";
			link.l1 = "Interesting... Go on.";
			link.l1.go = "mtraxx_19";
		break;
		
		case "mtraxx_19":
            dialog.text = "Your buyer wants more than 100 rolls of silk to be delivered for the next two months. If you'll have any then bring from 20 to 100 rolls for a price of 24 doubloons. The offer will stand for two months.";
			link.l1 = "Fine! I will bring more if I have any.";
			link.l1.go = "mtraxx_20";
			pchar.questTemp.Mtraxx.SilkTrade = "true";
			SetFunctionTimerCondition("Mtraxx_SilkTradeOver", 0, 0, 60, false);
		break;
		
		// торговля шелком
		case "mtraxx_silktrade":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "How much do you have?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			if (iTotalTemp > 100) link.l1.go = "mtraxx_silktrade_2";
			else link.l1.go = "mtraxx_silktrade_1";
		break;
		
		case "mtraxx_silktrade_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*24);
            dialog.text = "ЋVery good. Take the gold - 24 doubloons for a roll as we agreed on.";
			link.l1 = "Gratitude!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_2":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 100);
			TakeNItems(pchar, "gold_dublon", 2400);
            dialog.text = "I'll tale a hundred roll. Take the gold - 24 doubloons for a roll as we agreed on.";
			link.l1 = "Gratitude!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_3":
            DialogExit();
			npchar.dialog.currentnode = "First time";
			DeleteAttribute(pchar, "questTemp.Mtraxx.SilkTrade");
		break;
		
		case "mtraxx_20":
            dialog.text = "Let's talk something more urgent, shall we?";
			link.l1 = "Sure! Me and my men are ready to set sail immediately.";
			link.l1.go = "mtraxx_24";
		break;
		
		case "mtraxx_22":
            dialog.text = "For fucks sake, "+pchar.name+", where the hell have you been? Remember when I told you to come see me? I had a job for you and now it's wasted thanks to your excellent sense of time. You've made me really upset, pal. Get lost, I don't work with people who I can not rely on.";
			link.l1 = "Well, shit...";
			link.l1.go = "mtraxx_23";
		break;
		
		case "mtraxx_23":
			DialogExit();
            npchar.dialog.currentnode = "First time";
			CloseQuestHeader("Roger_2");
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_24":
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 40) sTemp = ".";
			else sTemp = " and also a trading license for 40 days";
            dialog.text = "Then pay attention. Two months ago I had an appointment with a captain by the name of Jean Picard. He didn't show up to the meeting and since I was going to discuss serious matters with him, I did some investigation regarding his whereabouts. Turned out our good brave privateer and his brigantine had managed to engage into a fight with a Spanish heavy galleon under command of don Eduardo de Losad and he is a tough son of a bitch. As a result, Jean and what's left of his crew was taken to Maracaibo and sold to a plantation. This is where he is, busy with honest labor, at the moment\nYour goal is get him out of there alive and also to investigate the details of his misfortunes. I need details of this story. I am assigning a captain of the Moray barquentine to assist you this. Name's Paul Chant also known as Pelly the Cutlass. Remember Geffrey? He is almost as dumb as him, hell of fighter too though\nHe will be waiting for you at Barbados. Get him and his Moray to Maracaibo and do the job. Cutlass will follow your orders without asking stupid questions. Actually, he won't be asking questions at all. Here is ten thousand pesos for future expenses"+sTemp+". Got anything to ask?";
			link.l1 = "Nope. Everything's clear. Heading to Barbados.";
			link.l1.go = "mtraxx_25";
		break;
		
		case "mtraxx_25":
			AddMoneyToCharacter(pchar, 10000);
			if (!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 40) GiveNationLicence(HOLLAND, 40);
            dialog.text = "I wish you luck then. Be swift, don't make Cutlass and poor Jean waiting.";
			link.l1 = "Sure thing, boss! On my way.";
			link.l1.go = "mtraxx_26";
		break;
		
		case "mtraxx_26":
            DialogExit();
			CloseQuestHeader("Roger_2");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_3", "1");
			Mtraxx_PlantBegin();
		break;
		
		case "mtraxx_27":
			pchar.quest.Mtraxx_PlantGoHomeOver.over = "yes"; 
            dialog.text = "Welcome back, my brave corsair, ha-ha! Did you take down a Spanish squadron? Picard has already told me. Nicely done!";
			link.l1 = "Yeah, my boys kicked them hard when we were leaving from Maracaibo.";
			link.l1.go = "mtraxx_28";
		break;
		
		case "mtraxx_28":
            dialog.text = "I can see you expecting a reward. Fair enough. Jan will pay you all your costs - it was his skin we were trying to save there. Send him a bill although take your time - the boy doesn't have a crew and a ship. Yet. A smart kid just like you, so his current state won't last long.";
			link.l1 = "Hm.. Well.. Okay. I'll take my time. Any work for me Marcus? Without saving and/or searching for anyone?";
			link.l1.go = "mtraxx_29";
		break;
		
		case "mtraxx_29":
            dialog.text = "Tired to be the brightest candle? Have to disappoint you there: I have enough brutes like Cutlass, your talents I will use accordingly. I'll have a job for you in a month, now you should sail to Isla Tesoro and lend a hand to Pasquale Lavoisier, he is a merchant of Sharptown\nYou have a week to show yourself to him. And be polite, this man is respected among the Brethren, so don't even think to fuck with him. Now go and see me in a month. Don't be late!";
			link.l1 = "Fine Marcus. See you!";
			link.l1.go = "mtraxx_30";
		break;
		
		case "mtraxx_30":
            DialogExit();
			CloseQuestHeader("Roger_3");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_4", "1");
			pchar.questTemp.Mtraxx = "pasq_start";
			Mtraxx_PasqualeBegin();
			SetFunctionTimerCondition("Mtraxx_PlantFithTaskTimer", 0, 0, 35, false);
			SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
		
		case "mtraxx_31":
            dialog.text = "Whoa! A dead man has returned! We have already buried you pal!";
			link.l1 = "Oh you shouldn't...";
			link.l1.go = "mtraxx_32";
		break;
		
		case "mtraxx_32":
            dialog.text = "Then why it took you so long to get to Hispaniola from Maracaibo? You are out of my organization now pal. I am really glad to see you alive, but there is no job for you here.";
			link.l1 = "Eh!.. What a shame...";
			link.l1.go = "mtraxx_33";
		break;
		
		case "mtraxx_33":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_34x":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_34";
		break;
		
		case "mtraxx_34":
			if (GetNpcQuestPastDayParam(npchar, "task_date") >= 35) // опоздал
			{
				dialog.text = "Damn it  "+pchar.name+", where have you been?! I told you to see me in a month! It's not a military here but some discipline is fucking expected! Get lost, I will not work with you anymore!";
				link.l1 = "Well now...";
				link.l1.go = "mtraxx_33";
				break;
			}
			if (GetNpcQuestPastDayParam(npchar, "task_date") < 28) // рано пришел
			{
				dialog.text = ""+pchar.name+", I told you - see me in a month. I have no time to spare on you right now.";
				link.l1 = "Fine...";
				link.l1.go = "mtraxx_34x";
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_angry")
			{
				dialog.text = "An agent of Lavoisier told me that you had fucked him with his iron wood. I warned you twice about not being a rat and being fair to Pasquale. You have broken both of my rules. You are a smart kid but this is unacceptable. Get the hell out of here and forget the road to this place.";
				link.l1 = "Khm...";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_fail")
			{
				dialog.text = "An agent of Lavoisier told me that you had fucked him with his iron wood - didn't bring the whole batch. I warned you twice about not being a rat and being fair to Pasquale. You have broken both of my rules. You are a smart kid but this is unacceptable. Get the hell out of here and forget the road to this place!";
				link.l1 = "Your Lavoisier is rat himself!..";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_late" || pchar.questTemp.Mtraxx == "pasq_sink" || pchar.questTemp.Mtraxx == "pasq_esc")
			{
				pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират // правки прогона 3
				dialog.text = "Ha! Charlie Prince, a brave captain! It's your new name in La Vega in case you didn't knowЙ So, did you enjoy being a brute? No? Figures. This is how my brainless agents like Cutlass live: today he parties in a brothel, wasting all he made, next day he is at my doorsteps begging a couple of thousands to pay his crew filled with idiots, just like he is. Whatever. Ready to hear it?";
				link.l1 = "Sure!";
				link.l1.go = "mtraxx_36";
				break;
			}
            dialog.text = "Ha! Charlie Prince, a brave captain! Ha-ha! An agent of Lavoisier told me you did well. I am glad you managed to show some respect to our profiteer.";
			link.l1 = "It's wouldn't hurt for him to have some more generosity...";
			link.l1.go = "mtraxx_35";
		break;
		
		case "mtraxx_35":
			pchar.questTemp.Mtraxx.Pasquale.Continue = "true"; // правки прогона 3
            dialog.text = "Remember what I said about brainless brutes and buyers of stolen goods? Right. Never take a job like this in the future. Leave it to Cutlass and people like him. Whatever. Ready to hear it?";
			link.l1 = "Sure!";
			link.l1.go = "mtraxx_36";
		break;
		
		case "mtraxx_36":
            dialog.text = "Great! Jan Picard is coming here - he will tell you more. It's his lead and you will work together on it. Plus it's his chance to pay his debt to you... There he is!";
			link.l1 = "...";
			link.l1.go = "mtraxx_37";
		break;
		
		case "mtraxx_37":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_38";
			chrDisableReloadToLocation = true;
			// преобразуем Пикара
			sld = characterFromId("Mrt_Rocur");
			sld.model = "Jan_Pikar";
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "GunProfessional");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			GiveItem2Character(sld, "blade_17");
			EquipCharacterbyItem(sld, "blade_17");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterbyItem(sld, "pistol6");
			TakeNItems(sld, "cartridge", 40);
			LAi_SetCharacterUseBullet(sld, "cartridge");
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.dialog.currentnode = "rocur_29";
			Characters_RefreshModel(sld);
			LAi_SetCheckMinHP(sld, 10, true, "");
			TakeNItems(sld, "potion2", 7);
			TakeNItems(sld, "potion3", 7);
			TakeNItems(sld, "potion4", 7);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "mtraxx_38":
            dialog.text = "My guy will join your raid. Names' Luka Bayard, mostly known as Luke Leprechaun. He and his men are buccaneers - hunters who spent most of their lives hunting in the forests of Hispaniola. Add to them your fighters and consider Merida to be yours. You'll take a third. The rest will be taken by Jan\nJan you will this brave captain what your own him from you share then bring what's left to me. We'll sort this out between us then. Questions?.. Splendid! Leprechaun will be waiting for you in our harbor. Godspeed corsairs, ha-ha!";
			link.l1 = "...";
			link.l1.go = "mtraxx_39";
		break;
		
		case "mtraxx_39":
            DialogExit();
			CloseQuestHeader("Roger_4");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_5", "1");
			pchar.questTemp.Mtraxx = "merida_start";
			Mtraxx_MeridaBegin();
			LAi_SetHuberType(npchar);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Mtraxx_MeridaAddPicar", 5.0);
			pchar.GenQuest.HunterLongPause = true;
		break;
		
		case "mtraxx_40":
            dialog.text = "Welcome back, my brave cutthroat! Rumors of your raid has already reached us.";
			link.l1 = "Can't say I like hearing it. Such things are better stay unknown...";
			link.l1.go = "mtraxx_41";
		break;
		
		case "mtraxx_41":
            dialog.text = "Trust me, they never are, my friend. Whatever. Has Picard wiped away his debt to you?";
			link.l1 = "Yes.";
			link.l1.go = "mtraxx_42";
		break;
		
		case "mtraxx_42":
            dialog.text = "Very good. Did Luke Leprechaun made a good impression on you?";
			link.l1 = "He did.";
			link.l1.go = "mtraxx_43";
		break;
		
		case "mtraxx_43":
            dialog.text = "Perfect then. Everyone is happy, everyone is paid.";
			link.l1 = "Do you have a job for me Marcus?";
			link.l1.go = "mtraxx_44";
		break;
		
		case "mtraxx_44":
            dialog.text = "No real job yet. Although I have a personal favor to ask. Interested?";
			link.l1 = "Sure boss. What favor?";
			link.l1.go = "mtraxx_45";
		break;
		
		case "mtraxx_45":
            dialog.text = "There is a pinnace the Kittie near the shores of La Vega. Been there for days waiting for an escort  to Bridgetown. No way I am letting her to sail there alone for obvious reasons. Would you be kindly to accompany her? I'll have a real job for you when you return. And, of course, the coin to pay you for this escort.";
			link.l1 = "Deal.";
			link.l1.go = "mtraxx_46";
		break;
		
		case "mtraxx_46":
            dialog.text = "Neat. Good sailing.";
			link.l1 = "Thanks!";
			link.l1.go = "mtraxx_47";
		break;
		
		case "mtraxx_47":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_6", "1");
			pchar.questTemp.Mtraxx = "ignasio_start";
			sld = characterFromId("Mtr_KittyCap");
			DeleteAttribute(sld, "DontDeskTalk");
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
		break;
		
		case "mtraxx_48":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "Ah, there you are... Been waiting for you already. Here is 10000 for an escort of the Kittie.";
			link.l1 = "Thanks... I have something to discuss with you Marcus.";
			link.l1.go = "mtraxx_49";
		break;
		
		case "mtraxx_49":
            dialog.text = "Do you?! Ha-ha! Shoot!..";
			link.l1 = "Remember how Jan Picard got enslaved? First he plundered a Dutch caravan along with a British privateer and then the same was done to him by a Spanish heavy galleon.";
			link.l1.go = "mtraxx_50";
		break;
		
		case "mtraxx_50":
            dialog.text = "Yeah. Why?";
			link.l1 = "I was approached in Bridgetown by Ignacio Marco. The privateer I mentioned. He offered me to plunder a Dutch caravan near the shores of inhabited island between Curacao and Trinidad.";
			link.l1.go = "mtraxx_51";
		break;
		
		case "mtraxx_51":
            dialog.text = "Well-well... Did you agree?";
			link.l1 = "I did. First, it was a good lead. Second, I recalled Picard's story and decided to investigate...";
			link.l1.go = "mtraxx_52";
		break;
		
		case "mtraxx_52":
            dialog.text = "I bet you did it.";
			link.l1 = "Yeah. There was a caravan, we did the job nice and clean. Then we split the spoils of it on a shoreЙ but first I put a watchman with a spyglass on a hill. And it paid off since a Spanish squadron had appeared shortly lead by a heavy galleon.";
			link.l1.go = "mtraxx_53";
		break;
		
		case "mtraxx_53":
            dialog.text = "You partner fled so the Spanish chased you?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.LosadaSink")) 
			{
				link.l1 = "Yep. They didn't even pay attention to him. Too bad for then: we did them a good beating to remember. They were good fighters but we managed to take down the whole squadron.";
				link.l1.go = "mtraxx_53x";
			}
			else
			{
				link.l1 = "Yep. They didn't even pay attention to him. Although I managed to flee. If it wasn't for my watchman...";
				link.l1.go = "mtraxx_53y";
			}
		break;
		
		case "mtraxx_53x":
			DeleteAttribute(pchar, "questTemp.Mtraxx.LosadaSink");
            dialog.text = "Heh! Taking down a squadron of Eduardo de Losad! You are a sea devil, Prince! I bet the Spanish have already sent hunters for your ass.";
			link.l1 = "Good for them... Nevertheless we should deal with this scum Ignacio. If you know what I mean.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_53y":
            dialog.text = "Heh! I imagine the shitstorm occurred when Castilians realized you've slipped from them! Nicely done!";
			link.l1 = "Their problems not mine.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_54":
            dialog.text = "I'll take care of it. We should learn more about Ignacio Marco. He might be working for someoneЙ His 'interest' in my men is suspicious. What ship he flies?";
			link.l1 = "A polacre, the Torero. A unique vessel, must be an original design.";
			link.l1.go = "mtraxx_55";
		break;
		
		case "mtraxx_55":
            dialog.text = "Good, easier to track her then... I got it. And for you, Prince, I have a job. Ready for it?";
			link.l1 = RandSwear()+"By all means, chief!";
			link.l1.go = "mtraxx_56";
		break;
		
		case "mtraxx_56":
            dialog.text = "Listen thenЙ Very recently we had a curious pirate in our region. Name's Wulfric Iogansen also known as Red Wolf. A very colorful character. He came here from the North of Europe a couple of years ago. This Viking were paying Levasseur a protection fee, didn't make friends and stayed on his own. A very secretive type, no one had ever left his crew alive\nUnlike most of our kind, Wulfric never wasted money on whores and drinks. Never sold his plunder for pennies. Never trusted bankers. He had a fine corvette, the Freyja and a loyal crew he paid well to. I believe he was planning to stash as much gold as possible and then return to Europe and live there like a king.\nIt didn't work out for him thanks to the Spanish hunters. The man had inflicted a colossal damage and losses to Spain, they sank the Freyja and killed the whole crew along with Wolf.\nThing is, they never found his treasures. He must had a huge one stashed somewhere. Now the interesting part comes: I have his log. It has no obvious leads to the treasure but you may try to find them between words. If you succeed - two thirds are yours. Are you in?";
			link.l1 = "Hm... it's is like looking for a black cat in a dark room. Where's the log?";
			link.l1.go = "mtraxx_57";
		break;
		
		case "mtraxx_57":
            dialog.text = "Here, take it. Good luck!";
			link.l1 = "Thanks, I am gonna need it...";
			link.l1.go = "mtraxx_58";
		break;
		
		case "mtraxx_58":
            DialogExit();
			CloseQuestHeader("Roger_6");
			npchar.dialog.currentnode = "mtraxx_wait";
			GiveItem2Character(pchar, "wolfreeks_book");
			AddQuestRecord("Roger_7", "1");
			pchar.questTemp.Mtraxx = "wolfreek_start";
			pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
			pchar.questTemp.Mtraxx.Logbook.Page1 = "true";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
		break;
		
		case "mtraxx_59":
            dialog.text = "Ah, there is our brave captain. What of Red Wolf's treasures?";
			link.l1 = "I am on it. Need you help in this.";
			link.l1.go = "mtraxx_60";
		break;
		
		case "mtraxx_60":
            dialog.text = "I am all ears.";
			link.l1 = "There is an unknown word written several times in Wulfric's log - ' Gord'. I must know it's meaning to move ahead in my investigation.";
			link.l1.go = "mtraxx_61";
		break;
		
		case "mtraxx_61":
            dialog.text = "Hm... Gord you say... Never heard it before too. Very well, see me in a week: I will consult with some big brainers who serve as pursers on ships. At least they know how to count and read. They might give us some idea.";
			link.l1 = "Fine Marcus. See you in a week then.";
			link.l1.go = "mtraxx_62";
		break;
		
		case "mtraxx_62":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			SetFunctionTimerCondition("Mtraxx_WolfreekTimer", 0, 0, 7, false);
		break;
		
		case "mtraxx_63":
            dialog.text = "I have an answer for you. One smart ass had enlightened me. Gord is a fortified settlement of a free jarl.";
			link.l1 = "A free jarl? Who is this?";
			link.l1.go = "mtraxx_64";
		break;
		
		case "mtraxx_64":
            dialog.text = "Some sort of a pirate admiral of Vikings. Me is a free jarl and La Vega is my gord. Seems like Red Wolf enjoyed his ancestors history, ha-ha! Did this information help you?";
			link.l1 = "Don't know yet. I should compare the notes first. Gord means settlement then... Thank you Marcus!";
			link.l1.go = "mtraxx_65";
		break;
		
		case "mtraxx_65":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			Mtraxx_WolfreekReadLogbookFourth();
		break;
		
		case "mtraxx_66":
            dialog.text = "So? You smug face is telling me that you had success.";
			link.l1 = "Yeah. Red Wolf's treasure was found. It wasn't easy though.";
			link.l1.go = "mtraxx_67";
		break;
		
		case "mtraxx_67":
            dialog.text = "How much did our Viking stashed?";
			link.l1 = "750 000 pesos and 900 doubloons.";
			link.l1.go = "mtraxx_68";
		break;
		
		case "mtraxx_68":
            dialog.text = "Ho-ho! You did good Prince. What of my cut?";
			if (sti(pchar.money) >= 250000 && GetCharacterItem(pchar, "gold_dublon") >= 300)
			{
				link.l1 = "Here, take this. According to our agreement: 250 000 pesos and 300 doubloons.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "All the money are in my cabin. Give me an hour to get them here!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_68_1":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_68_2";
		break;
		
		case "mtraxx_68_2":
            dialog.text = "Do you have it?";
			if (sti(pchar.money) >= 250000 && GetCharacterItem(pchar, "gold_dublon") >= 300)
			{
				link.l1 = "Here, take this. According to our agreement: 250 000 pesos and 300 doubloons.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Yes-yes, I an on my way!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_69":
			AddMoneyToCharacter(pchar, -250000);
			RemoveItems(pchar, "gold_dublon", 300);
			Log_Info("You have given 300 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "Very good. You did great again. Well done!";
			link.l1 = "Marcus did you dig up anything about Ignacio Marco?";
			link.l1.go = "mtraxx_70";
		break;
		
		case "mtraxx_70":
            dialog.text = "Yes but I need to verify it first...";
			link.l1 = "What?";
			link.l1.go = "mtraxx_71";
		break;
		
		case "mtraxx_71":
            dialog.text = "I have a suspicion that Marco is connected to someone... And you are to find it out. Sail to Martinique. Leave your ship in St. Pierre and get to Le Francois through the jungles. I was told that our guy is seen there. Don't ask pirates around, just watch and observe. Once you find the guy, follow him and see who is he meeting with. Do not attack him or his ship - by doing so you'd ruin a plan I am developing right now! I have warned you\nFollow and watch him, head back to me once you learn enough. I understand your hands are willing to strangle the bastard but keep your head cool. Now go. You have three weeks. Good luck.";
			link.l1 = "On my way boss.";
			link.l1.go = "mtraxx_72";
		break;
		
		case "mtraxx_72":
            DialogExit();
			CloseQuestHeader("Roger_7");
			RemoveItems(pchar, "wolfreeks_book", 1);
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_8", "1");
			pchar.questTemp.Mtraxx = "corrida_start";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1.location = "Martinique";
			pchar.quest.mtraxx_corrida_martinique.function = "Mtraxx_CorridaStart";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1.location = "LaVega_exittown";
			pchar.quest.mtraxx_pasq_continue.function = "Mtraxx_PasqualeJan";
			bDisableFastReload = true;
			SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
			
		case "mtraxx_73":
			if (GetNpcQuestPastDayParam(npchar, "task_date") >= 22) // опоздал
			{
				dialog.text = "Damn it Prince! You could have a revenge and helluva lot of money if you weren't so slow! Didn't expect this from you but since you are a good kid I forgive you. You'll have a chance to regain your reputation in my eyes in a month. I am gathering everyone for a raid!\nGet to me in a month on a single but powerful ship. Luke, Cutlass, Geffrey and Jan will take part in this too. Don't be late even for day!";
				link.l1 = "I understand Marcus. Won't happen again!";
				link.l1.go = "mtraxx_73x";
				break;
			}
			dialog.text = "Good timing! Report to me, now.";
			link.l1 = "I've tracked my obligor in Le Francois. His polacre was a part of a squadron of corvette and frigate. Marco himself was paying a visit to Barbason, they had a meeting in his place for two hours, other visitors had been sent away by his guards. Then he went out of the house with two gloomy bastards: one was red and beardy in a ritter's cuirass, the other had moustaches and was wearing a heavy trench armor. All went to a port and sailed away before I reached St. Pierre.";
			link.l1.go = "mtraxx_74";
		break;
		
		case "mtraxx_73x":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "5");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 28, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 30, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 31, false);
		break;
		
		case "mtraxx_74":
            dialog.text = "It's fine. Now I see the whole picture. These two devils you saw are working for Barbason and Jackman. They are almost just like my Luke and Cutlass although they fight better. The red is called Prowler, he is a captain of the ‘cuttlefish, a corvette, and the guy with moustaches is Ghoul, he sails the Merciless, a frigate. As for our friend Ignacio - he is working not only for the Brits and a Spanish don Losad but also for Barbason. This is why he tried to fuck you and Picard.";
			link.l1 = "Why?";
			link.l1.go = "mtraxx_75";
		break;
		
		case "mtraxx_75":
            dialog.text = "Barbason's order. You didn't know but the Good Jacques never misses a chance to piss in my porridge. He would never openly oppose me for obvious reasons, so he crosses me secretly. He knew that Picard and you are my men. Sending after you his mercenary was in his style. And didn't send an idiot.";
			link.l1 = "I'll pay Barbason a visit as soon as I take care of Marco...";
			link.l1.go = "mtraxx_76";
		break;
		
		case "mtraxx_76":
            dialog.text = "Get this crap out your head! You are no match to Barbason. He will screw you sideways with ease. We will repay him with his own trickery - by hitting his associates. Ready to do that? It's a messy business.";
			link.l1 = "Sound my kind of business!";
			link.l1.go = "mtraxx_77";
		break;
		
		case "mtraxx_77":
            dialog.text = "Ignacio Marco, Prowler, Goul and another Barbason's guys called Joker Jim have a plan to capture one of Spanish ships of the Golden Fleet. The whole operation was designed by Barbason himself and I've managed to learn the most of it. Marco has a task to obtain a sailing schedule of a Spanish galleon which is currently under repairmen on Cuba and is supposed to catch up with the rest of the Fleet later. He has connection within the Spanish so this task won't be a problem for him\nThe rest of Barbason's band is waiting for Marco at Sint Maarten which is an optimal place to start hunting this prize. Since Marco and the Dutch are not very fond of each other - he will have to send them a message with a sailing schedule...";
			link.l1 = "I guess I know what I am supposed to do here...";
			link.l1.go = "mtraxx_78";
		break;
		
		case "mtraxx_78":
            dialog.text = "It strikes me that you are so bright but I am not finished yet. I have interfered this place with a help from Gabriela Chapada. You know her. She made sure the Spanish are believing that the pirate ambush will be set not far from Puerto Rico. No way the galleon will be sailing through that area, they had secretly send pirate hunters there instead. You have a number of tasks. First would be finding and capturing the Torero. I guess you know what to do with her captain.";
			link.l1 = "Sure!";
			link.l1.go = "mtraxx_79";
		break;
		
		case "mtraxx_79":
            dialog.text = "Second, find out the real course of the Spanish golden galleon. Marco must have her schedule. Get it and send it to me.";
			link.l1 = "How?";
			link.l1.go = "mtraxx_80";
		break;
		
		case "mtraxx_80":
			GiveItem2Character(pchar, "Dove"); 
            dialog.text = "By air. Take a cage... This is Spyke, a post pigeon born in La Vega. He will always find a way here. Once you obtain the schedule, write a note, stick it to his leg and release him. Spyke will fly to me in a few hours. Take care of him!";
			link.l1 = "Whoa... Well boss!..";
			link.l1.go = "mtraxx_81";
		break;
		
		case "mtraxx_81":
            dialog.text = "Third, sail to Sint Maarten on the Torero. Only on her alone! Otherwise they will get suspicious too soon. Send them a signal to sail to Puerto Rico where the Spanish await. Their signal codes must be in Marco's papers. Or you can learn them from the man himself.";
			link.l1 = "I see. A smart move sending Barbason's men to the Spanish, ha-ha!";
			link.l1.go = "mtraxx_82";
		break;
		
		case "mtraxx_82":
            dialog.text = "Exactly! I will deliver him a blow from the shadow. Just like he did. And one last thing: once you send them a signal, immediately sail to intercept the Spanish galleon and her escort. No time will be left to waste.";
			link.l1 = "On a polacre? They will tear me apart!";
			link.l1.go = "mtraxx_83";
		break;
		
		case "mtraxx_83":
            dialog.text = "I am sorry, did you say something? Spyke will save your sorry ass. You won't be left without reinforcements. Just don't let the caravan to flee, do not let them get to the ocean. Got it?";
			link.l1 = "Yes, boss.";
			link.l1.go = "mtraxx_84";
		break;
		
		case "mtraxx_84":
            dialog.text = "Your reward will be a heavy load of gold plus Marco's polacre. They say she is a damn good ship. Any questions? Do you understand your mission?";
			link.l1 = "I am not Cutlass, I know what to do. Where should I intercept the Torero?";
			link.l1.go = "mtraxx_85";
		break;
		
		case "mtraxx_85":
            dialog.text = "While we are having this chit chat, she is swiftly sailing right to Philipsburg from Cuba. Must be around Tortuga now or a bit to the East from it. Catch them not far from Sint Maarten just don't let their friends to see the fight otherwise my plan is ruined.";
			link.l1 = "Getting underway right now!";
			link.l1.go = "mtraxx_86";
		break;
		
		case "mtraxx_86":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			AddQuestRecord("Roger_8", "6");
			pchar.questTemp.Mtraxx = "corrida_marko";
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.function = "Mtraxx_CorridaLandTimer";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_corrida_checktime.function = "Mtraxx_CorridaCheckTime";
			pchar.quest.mtraxx_corrida_torero.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.hour  = sti(GetTime()+12);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.function = "Mtraxx_CorridaToreroOnMap";
			SetFunctionTimerCondition("Mtraxx_CorridaTimeFindTorero", 0, 0, 7, false); // время на перехват Тореро, снимать при потоплении или захвате
		break;
		
		case "mtraxx_87":
            dialog.text = "So Prince did you screw everything up? Huh?";
			link.l1 = "I did. This mission was a much bigger challenge than I thought. You can give me an enraging speech and show me the door.";
			link.l1.go = "mtraxx_88";
		break;
		
		case "mtraxx_88":
            dialog.text = "Come on, quit it. It happens. You are good corsair and we all fail sometimes. Pity we didn't get that gold but if we didn't get it in one place, we should get from another, ha-ha! You'll have a chance to regain your reputation in my eyes in a month. I am gathering everyone for a raid!\nGet to me in three weeks on a single but powerful ship. Luke, Cutlass, Geffrey and Jan will take part in this too. Don't be late!";
			link.l1 = "I won't boss!";
			link.l1.go = "mtraxx_89";
		break;
		
		case "mtraxx_89":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "22");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 18, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 20, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 22, false);
			if (CheckCharacterItem(pchar, "Dove")) RemoveItems(pchar, "Dove", 1);
		break;
		
		case "mtraxx_board":
            dialog.text = "Ho-ho, greetings to brave corsair! Didn't expect to see me here, right? Ha-ha-ha! We've found the Spanish caravan after all...";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Gold")) // был абордаж
			{
				link.l1 = "Yes boss we did, although it wasn't easy.";
				link.l1.go = "mtraxx_board_1";
			}
			else
			{
				link.l1 = "Yeah although the golden galleon was sunken with all her gold.";
				link.l1.go = "mtraxx_board_7";
			}
		break;
		
		case "mtraxx_board_1":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_GOLD);
            dialog.text = "How much gold did we get, Prince?";
			if (iTotalTemp < 1) link.l1 = "Ќeh... Nothing.";
			else link.l1 = "Heh... "+iTotalTemp+"...";
			link.l1.go = "mtraxx_board_2";
		break;
		
		case "mtraxx_board_2":
			if (iTotalTemp < 20)
			{
				dialog.text = "Damn it! Spanish must had thrown it to the sea so we wouldn't get it. At least they paid for it. As well as Barbason's men which is also a result.";
				link.l1 = "Shame about the gold... What next Marcus? Are we going to La Vega?";
				link.l1.go = "mtraxx_board_4";
				AddQuestRecord("Roger_8", "18");
				break;
			}
			if (iTotalTemp >= 20 && iTotalTemp < 300)
			{
				dialog.text = "Pathetic. It doesn't even compensate my tour here. Obviously the Spanish must had thrown it to the sea so we wouldn't get it. At least they paid for it. As well as Barbason's men which is also a result.";
				link.l1 = "Shame about the gold... Let's split it anyway.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				break;
			}
			if (iTotalTemp >= 300 && iTotalTemp < 700)
			{
				dialog.text = "This is a poor prize. Just above of the costs. Obviously the Spanish must had thrown it to the sea so we wouldn't get it. At least they paid for it. As well as Barbason's men which is also a result.";
				link.l1 = "Shame about the gold... Let's split it anyway.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				break;
			}
			if (iTotalTemp >= 700 && iTotalTemp < 1000)
			{
				dialog.text = "Not bad, although I expected better. Obviously the Spanish must had thrown it to the sea so we wouldn't get it. At least they paid for it. As well as Barbason's men which is also a result.";
				link.l1 = "Let's split the prize!";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "20");
				AddCharacterExpToSkill(pchar, "Fortune", 200);
				break;
			}
			dialog.text = "Nice. We did good friend. And Barbason's men got what we had for them, ha-ha!";
			link.l1 = "Heh, that's a load of gold! Let's split it!";
			link.l1.go = "mtraxx_board_3";
			AddQuestRecord("Roger_8", "21");
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mtraxx_board_3":
			RemoveCharacterGoods(pchar, GOOD_GOLD, makeint(iTotalTemp/2));
			WaitDate("", 0, 0, 0, 3, 10);
			LAi_Fade("", "");
            dialog.text = "... like we always do in the Brethren - a fair cut to each. You can keep the Torero, she is your prize.";
			link.l1 = "What next Marcus? Are we going to La Vega?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_board_4":
            dialog.text = "I am. You should come to me in three weeks on a single but powerful ship. Luke, Cutlass, Geffrey and Jan will take part in this too. You will learn more later!";
			link.l1 = "Fine boss! See you in La Vega in three weeks.";
			link.l1.go = "mtraxx_board_5";
		break;
		
		case "mtraxx_board_5":
            dialog.text = "Farewell cutthroat! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "mtraxx_board_6";
		break;
		
		case "mtraxx_board_6":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Ship_SetTaskRunAway(SECONDARY_TASK, sti(npchar.index), sti(pchar.index));
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_corrida_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_corrida_complete.function = "Mtraxx_CorridaComplete";
			RemoveItems(pchar, "wolfreeks_book", 1);
		break;
		
		case "mtraxx_board_6x":
            dialog.text = "Anything else?";
			link.l1 = "No, I don't think so. Getting underway already.";
			link.l1.go = "mtraxx_board_6y";
		break;
		
		case "mtraxx_board_6y":
            DialogExit();
			npchar.DeckDialogNode = "mtraxx_board_6x";
		break;
		
		case "mtraxx_board_7":
            dialog.text = "Heh! And whose fault is that Prince? Was it yours?";
			link.l1 = "I am sorry boss, I am truly am, but you too did an excellent job shooting with your giant couleurins. Nice aiming by the way...";
			link.l1.go = "mtraxx_board_8";
		break;
		
		case "mtraxx_board_8":
            dialog.text = "Whatever. The fault is on both of us. We are not empty handed though - Barbason's men got we had for them which is also a result.";
			link.l1 = "Shame about the gold... What next Marcus? Are we going to La Vega?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_90x":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_90";
		break;
		
		case "mtraxx_90":
			pchar.quest.Mtraxx_CartahenaLate.over = "yes";
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Prince did you loose your brain? I told you to bring only one ship! Go get rid of the extra and come back as soon as possible! Now!";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (RealShips[sti(pchar.Ship.Type)].Type.Merchant) // торговые
			{
				dialog.text = "Prince have you decided to be my second Cutlass? Why did you bring a trade vessel to me? I was counting on you! Go bring here a decent warship! Now!";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) > 3)
			{
				dialog.text = "Prince did you loose your brain? I told you to bring a warship! Come back here on third of second rank vessel! Now! I am not gonna be waiting for anyone.";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Prince, why not bring here the Sovereign of the Seas? When I told you to bring a warship, I didn't mean to bring a fucking ship of the line! Come back here on third of second rank vessel! Now! I am not gonna be waiting for anyone.";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_90x";
				break;
			}
            dialog.text = "Good timing, corsair! Glad to see you in one piece! Ready for a voyage?";
			link.l1 = "Sure thing, chief. Always ready.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon")) link.l1.go = "mtraxx_91";
			else link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_91":
            dialog.text = "By the way, do want to know about Barbason's squadron you'd sent to Puerto-Rico?";
			link.l1 = "They have completely slipped from my mind. Sure, I want. Did they find their doom?";
			link.l1.go = "mtraxx_92";
		break;
		
		case "mtraxx_92":
            dialog.text = "They did. Joker Jim was burnt along with his ship. The other two got a heavy beating too yet they managed to flee. To be honest, the Spanish have disappointed me.";
			link.l1 = "Heh. Whatever. We still pissed in Barbason's boots. Gave him a message.";
			link.l1.go = "mtraxx_93";
		break;
		
		case "mtraxx_93":
            dialog.text = "True. Let's talk business.";
			link.l1 = "I am all ears.";
			link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_94":
            dialog.text = "My intelligence in the person of my good friend Bernard Vensan reported me about a huge pile of golden ingots the Spanish stored in Cartagena. Below it's fort, to be more specific. Normally it would had been attributed to the Golden Fleet of Spain but this time it is ours to take. We are heading to South Main to storm Cartagena.";
			link.l1 = "Argh! Did I hear it right? Are we to plunder a fucking colony with a fort?";
			link.l1.go = "mtraxx_95";
		break;
		
		case "mtraxx_95":
            dialog.text = "You heard right. My warship will deal with the fort with your help of course. Bold Jeffrey will be carrying ground troops on his ost-indian. Pelly got a decent corvetteЙ not without my financial aid. Paul Chant and you are responsible for taking out patrol fleet.\nJan Picard didn't show up which is odd since his vessel was seen in Port Royal. His problems, so fuck him. Instead of him, my friend will join the raid, Bernard Vensan. Plus, Leprechaun with his buccaneers will assist our troops. We will take the gold from the fort and ransom from the city. They won't forget it, ha-ha!\nCome join me and other captains in the tavern this evening! We should drink for our cause!";
			link.l1 = "Aye, aye, chief!..";
			link.l1.go = "mtraxx_96";
		break;
		
		case "mtraxx_96":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			chrDisableReloadToLocation = true;
			CloseQuestHeader("Roger_8");
			pchar.questTemp.Mtraxx = "cartahena";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LaVega_townhall", "goto", "goto3");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaReloadInTavern", 10.0);
			pchar.worldmapencountersoff = "1"; // уберем враждебные энкаунтеры
		break;
		
		case "mtraxx_97":
            dialog.text = "Prince, where the hell have you been? Sit down! Already? Well done. Let's begin!\nMy brave corsairs, tonight the best rum and the best women are all yours! The gold of Cartagena is waiting for us, so let's drink for our mutual success! To the dregs!..";
			link.l1 = "";
			link.l1.go = "mtraxx_98";
		break;
		
		case "mtraxx_98":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			LAi_SetSitType(npchar);
			DoQuestCheckDelay("Mtraxx_CartahenaTavernSong", 1.0);
		break;
		
		case "mtraxx_99":
            dialog.text = "Time to show them who we are, corsairs. Leprechaun! Take your men and take control of the city gates. We don't want them to send reinforcements to the fort! Hit them hard when we will push through soldiers of the fort!";
			link.l1 = "";
			link.l1.go = "mtraxx_100";
		break;
		
		case "mtraxx_100":
            dialog.text = "Prince and Paul! You saw the military squadron, get rid of them. Stay away from the fort and do no board their vessels. We have neither time, nor position to deal with prizes. Everything's clear?! Great, ha-ha! Charge!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaSquadronAttack");
		break;
		
		case "mtraxx_101":
            dialog.text = "So, the Spanish squadron is gone for good. Now it's time for the Red Dragon to play her part. We will turn the fort of Cartagena into a pile of rubble. Are you with me?";
			link.l1 = "Sure!";
			link.l1.go = "mtraxx_102";
		break;
		
		case "mtraxx_102":
            dialog.text = "The Red Dragon is very sturdy ship with a powerful artillery, yours is not a match to her. So be careful, don't play a hero and stay away from my guns!";
			link.l1 = "...";
			link.l1.go = "mtraxx_103";
		break;
		
		case "mtraxx_103":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Group_FindOrCreateGroup("Terrax_SeaGroup2");
			Group_DelCharacter("Terrax_SeaGroup", "Jeffry");
			Group_DelCharacter("Terrax_SeaGroup", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Jeffry");
			Group_AddCharacter("Terrax_SeaGroup2", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Pelly");
			Group_SetGroupCommander("Terrax_SeaGroup2", "Jeffry");
			Group_SetTaskNone("Terrax_SeaGroup2");
			Group_LockTask("Terrax_SeaGroup2");
			sld = CharacterFromID("Cartahena Fort Commander");
			LAi_SetImmortal(sld, false);
			Ship_SetTaskAttack(SECONDARY_TASK, sti(npchar.index), sti(sld.index));
			AddQuestRecord("Roger_9", "5");
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx.Cartahena.Fort = "true";
		break;
		
		case "mtraxx_104":
            dialog.text = RandSwear()+"Helluva fight! This is it, my brave corsairs! Cartagena is ours! Resistance is down! Bold, Leprechaun! Come with me to the fort - Bernie must had already found the gold. Prince, take Cutlass and negotiate the governor to pay us a ransom of 250000. They have the money, so be persistent. I know you can.";
			link.l1 = "Heh! Will be a pleasure, boss!";
			link.l1.go = "mtraxx_105";
		break;
		
		case "mtraxx_105":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "Cartahena_fort", "goto", "goto10", "", 5.0);
			sld = CharacterFromID("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto11", "", 5.0);
			sld = CharacterFromID("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto12", "", 5.0);
			sld = CharacterFromID("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			AddQuestRecord("Roger_9", "6");
			// запрещаем драки в городе, резиденции, форте
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_fort")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_town")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_townhall")], true);
			LAi_LocationDisableOfficersGen("Cartahena_townhall", true);
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1 = "locator";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.location = "Cartahena_town";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator = "reload3_back";
			pchar.quest.mtraxx_cartahena_townhall.function = "Mtraxx_CartahenaToResidence";
		break;
		
		case "mtraxx_106":
            dialog.text = "How are you doing, Prince?";
			link.l1 = "Everything is splendid. I forced the Cartagena's richest to pay 350 000.";
			link.l1.go = "mtraxx_107";
		break;
		
		case "mtraxx_107":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "Ho-ho, that's my boy! But where is the money?";
				link.l1 = RandSwear()+"I will bring them in no time!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Ho-ho, that's my boy! You and the Cutlass can keep 25 000 each as a bonus for speed and resourcefulness. The rest will be split between all of us later.";
				link.l1 = "Here you go!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_107x":
           DialogExit();
		   npchar.dialog.currentnode = "mtraxx_108";
		break;
		
		case "mtraxx_108":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "So? Stop playing around and bring the coin here!";
				link.l1 = "On my way!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Great! You and the Cutlass can keep 25 000 each as a bonus for speed and resourcefulness. The rest will be split between all of us later.";
				link.l1 = "Here you go!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_109":
			AddMoneyToCharacter(pchar, -325000);
            dialog.text = "You must be concerned about our gold? It is found - 5000 units and it's already being transported to our ships. The split was done already, men agreed with it, we hope that Cutlass and you will not object too.";
			link.l1 = "What is my share?";
			link.l1.go = "mtraxx_110";
		break;
		
		case "mtraxx_110":
            dialog.text = "Since the whole operation was planned by me, plus the Red Dragon did the toughest job of dealing with a fort, me and my men will receive a half of plunder. The other half will be shared between captains of other four ships according to the number of their crews. You have "+GetCrewQuantity(pchar)+" men in disposal, your share is "+sti(pchar.questTemp.Mtraxx.Cartahena.Gold)+" units of gold and "+sti(pchar.questTemp.Mtraxx.Cartahena.Money)+" pesos.";
			link.l1 = "Well, since everyone is fine with this then me too!..";
			link.l1.go = "mtraxx_111";
		break;
		
		case "mtraxx_111":
            dialog.text = "Splendid. Congratulations for this successful voyage, corsairs! Nothing is left to do for us here, time to go home. All of us including myself are receiving a vacation for a month. Not you, Prince, though, I have another task for you. See, Janette, a Madame of Tortuga's brothel, had a complain about you: she said that Charley Prince doesn't give much attention and love to her establishment. Therefore, I command you to sail to Tortuga, go to Janette's and waste your bonuses there. You have deserved it. Make the Madame and her girls happy. I don't want to see you before you get rested on Tortuga, ha-ha-ha!";
			link.l1 = "Got it, boss. This is the most pleasant assignment I ever received. Will do!";
			link.l1.go = "mtraxx_112";
		break;
		
		case "mtraxx_112":
            dialog.text = "Farewell, gentlemen! Get on your ships and set sails! See you all in La Vega!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaFinal");
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "mtraxx_113":
            dialog.text = "What?! Jan is now a bitch of the Englishmen, Bold and Cutlass have disappeared, Leprechaun and his men are nowhere to be found!! And now you?!";
			link.l1 = "Marcus I've made a decision. I made a good coin, you made quite a fortune on me  too. Time to part our ways. I am leaving.";
			link.l1.go = "mtraxx_114";
		break;
		
		case "mtraxx_114":
            dialog.text = "You, just like Picard, thought that you can have a better cut on your own? Yeah? Thought that you can do without me? Ha-ha-ha! Get the hell out of here Prince, I am not keeping you. Soon, very soon you'll see how wrong you are and then you will come back begging me to take your sorry ass back. And you know what? I won't! Ha-ha! Get out of my sight!";
			link.l1 = "...";
			link.l1.go = "mtraxx_115";
		break;
		
		case "mtraxx_115":
            DialogExit();
		    npchar.quest.mtraxx_complete = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Ho-ho! You've come to the right place! Spit it out!";
			link.l1 = "There is a fella that has no fear of pirates. He doesn't take them seriously. He needs to be taught a lesson om respect. Remember, don't kill him.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Huh! It's noone else than the old man Charles! I bet you got yourself into some affair again! Let's get to the details, who's the target this time and what shall we teach him";
			link.l1 = "A guest from Europe, an inspector of the French Ministry of Finance - baron Noel Forget. He wants to establish a French Trading Company here, but me and a close friend of mine object against it. We tried to convince the baron, that trading here would be very risky because of the Dutch, English and especially pirates after Levasseur was defeated, but he won't listen. We need to strike fear into him, to make him feel it on his own skin.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_x":
			dialog.text = "Ho-ho! You've come to the right place! Spit it out!";
			link.l1 = "There is a fella that has no fear of pirates. He doesn't take them seriously. He needs to be taught a lesson om respect. Remember, don't kill him.";
			link.l1.go = "patria_x1";
		break;
		
		case "patria_x1":
			dialog.text = "Huh! Why did you decide to harness pirates all of a sudden? Fine, I don't care as long as you pay me. Let's get to the details, who's the target this time and what shall we teach him";
			link.l1 = "A guest from Europe, an inspector of the French Ministry of Finance - baron Noel Forget. He wants to establish a French Trading Company here, but me and a close friend of mine object against it. We tried to convince the baron, that trading here would be very risky because of the Dutch, English and especially pirates after Levasseur was defeated, but he won't listen. We need to strike fear into him, to make him feel it on his own skin.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Yes-yes... An actual baron!.. Shall we assault his ship?";
			link.l1 = "Here's the plan: his vessel will depart to Capsterville from Port-au-Prince soon. He must be intercepted by Saint Kitts and take the baron as a hostage. It would be better if you didn't sink the ship and avoided killing men. The French are our friends, after all. Will you be able handle that?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Well, I can't promise anything. But I'll try. What ship is it?";
			link.l1 = "A brig called 'Favory'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "A brig is no match for my 'Red dragon'.We'll easily deal with them. If it surrenders, I'll let everyone live.";
			link.l1 = "Perfect. Strike fear and offer them to yield. Afterwards, send the baron to the rat-infested hold. Try to find the filthiest place you can, but keep him there no longer than a day, or else he could get sick and die. Then accomodate him in the cabin, go to the Isla Tesoro, and lock in some secluded place. Dress some of your men as captured French merchants and make them to act like ones. For three days straight, they should tell him all about how the ruthless pirates chase them, rob them, demand ransoms, torture them... with all the details required.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ha-ha-ha! This must be the funniest job I've ever taken on since a very long time! Well then, I will find such actors, pal. Have no doubt, after their stories your baron will crap his pants! They will show him scars from cutlasses and heated ramrods...";
			link.l1 = "Nailed it. Then you will force him to write a letter to Poincy, asking for ransom. Thirty five hundred thousand for such a big shot is not that much.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Good. What shall we do next?";
			link.l1 = "And then you'll bring the baron to Terrax. There you will take the ransom, and you will give me the baron. And additionally you should tell them, that they will answer for Tortuga and Levasseur.";
			if (CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax")) link.l1.go = "patria_x7";
			else link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ha-ha-ha! That one hell of a trick! We personally, well, you know what we did to Levasseur, and now... ha-ha-ha!.. Fine, pal. It will be done! You believe that the ship will arrive soon?";
			link.l1 = "Soon. We need to be on lookout.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_x7":
			dialog.text = "Ha-ha-ha! That one hell of a trick! How much should I charge you for this farce? Fine, hundred thousand will seal the deal. Hand in the money.";
			if (sti(pchar.money) >= 100000) 
			{
				link.l1 = "Take it.";
				link.l1.go = "patria_x8";
			}
			else
			{
				link.l1 = "Alright, I'll bring it.";
				link.l1.go = "patria_xwait";
			}
		break;
		
		case "patria_xwait":
			DialogExit();
			pchar.questTemp.Patria.Condotier.NeedMoney = "true";
		break;
		
		case "patria_x8":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Perfect! You believe that the ship will arrive soon?";
			link.l1 = "Soon. We need to be on lookout.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Don't be bothered , I won't let you down. I will handle this personally. When you hear rumor that the baron was captured, come to me.";
			link.l1 = "Good. My thanks, Marcus.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "71");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
			else LocatorReloadEnterDisable("Lavega_town", "reload6", true);
		break;
		
		case "patria_10":
			dialog.text = "Of course, pal. As agreed. Scary tales about evil pirates, slaughtering innocent French merchants, The sounds of a whip, moans and screams. Brazier with coal and scorched handcuffs. Just like it should be.";
			link.l1 = "Well now! Hold your horses. I need him alive";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Worry not, he will live. He wrote that letter with a shaky hand. Here it is.";
			link.l1 = "What is written there? He's begging Poincy to get him out of this?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Spot on, pal! He's begging!";
			link.l1 = "Throw this letter away, or better - burn it. We'll meet on Terks in a week. It must look as if we need time to collect the ransom.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Got it. In a week time, Northern gulf. Don't forget to take the money: this must look pretty. Afterwards, come to me, well settle this.";
			link.l1 = "Of course, I bet even the echinus would have figured that out. See you later!";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "Hey, frog! Halt!";
			link.l1 = "I'm not moving";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Here's your baron. A bit worn, but in one piece. Is it him?";
			link.l1 = "Yes.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Perfect. Now hand over the money or he is done for! And don't try to trick us, we've got you in the sights!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Here.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "Damn! I forot it on the ship...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ha-ha-ha! You're a smart kid, frenchie. Take thine holiness. And tell Poincy that he should prepare the money: you'll have to pay up for what you did to Levasseur and Tortuga. And your hagglers shall pay us with their, goods and ships. Ha-ha-ha! Don't forget to bring us some more barons to the archipelago, they bring us a lot of profit! Ha-ha-ha!";
			link.l1 = "Please go to my boat, baron.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "And don't even think about chasing us, captain. You know who I am. I hold the more frogs captive, and if I don't return home in time, they all be done for. Got it?";
			link.l1 = "The time will come and we shall deal with you, cursed blasphemers!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ha-ha-ha-ha!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax"))
			{
				LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
				Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			}
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "Are you messing with me?";
			link.l1 = "One minute, I'll bring it...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "Argh, Marcus, what has your dullard done!";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) link.l1.go = "patria_25";
			else link.l1.go = "patria_x25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, what were you doing? Where's the money? I didn't tell my boys that this wasn't real... and so this idiot decided that you wanted to trick them...";
			link.l1 = "What a shame! Baron is dead... What will Poincy do now?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_x25":
			dialog.text = "Charles, what were you doing? Where's the money? I didn't tell my boys that this wasn't real... and so this idiot decided that you wanted to trick them...";
			link.l1 = "What a shame! Baron is dead... What will Poincy do now?";
			link.l1.go = "patria_x26";
		break;
		
		case "patria_x26":
			dialog.text = "Well, pal, It's your fault, I hope you understand that. Perhaps it will be all the better for you, a dead man can't cause any harm.";
			link.l1 = "What an idiot I am! Messed everything up. Fine, I'll go to Poincy... Forgive me for being a fool, Marcus, see you.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_26":
			dialog.text = "Well, pal, It's your fault, I hope you understand that. Perhaps it will be all the better for you.";
			link.l1 = "What an idiot I am! Messed everything up. Fine, I'll go to Poincy... Forgive me for being a fool, Marcus, see you.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "You need to rest, you're losing your touch. Come to me sometime, I'll get you some rum and fine maidens.";
			link.l1 = "Thank you, I'll play you a visit when I can.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "You're welcome, pal. For me this was the most fun I've had this year! We laughed so much, me and my lads!.. So I'd like to thank you for this. Here's your money.";
			link.l1 = "You should keep yourself a share.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_x29":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Take your money, 'plotter'. Ha-ha! This was fun.";
			link.l1 = "Thank you for your help, Marcus. Good luck!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Forget it. I did this for the sake of our friendship. The Brotherhood of the Coast owes you much more, yet you didn't ask for a single dubloon.";
			link.l1 = "Still, take at least fifty thousand for the services and compensation. Thank you, Steven! I'm glad that I once met you on that strange island of the lost ships.";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "And so am I. Charles, pay me a visit whenever you have some time!";
			link.l1 = "With pleasure!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "You're late by a week! I didn't tell my boys that this wasn't real... ! They refused to wait any longer, and decided to end your baron!";
			link.l1 = "What an idiot I am! Messed everything up! What am I going to tell Poincy?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_x33":
			dialog.text = "You're late by a week! I didn't tell my boys that this wasn't real... ! They refused to wait any longer, and decided to end your baron!";
			link.l1 = "What an idiot I am! Messed everything up! What am I going to tell Poincy?";
			link.l1.go = "patria_x34";
		break;
		
		case "patria_34":
			dialog.text = "Well, pal, It's your fault, I hope you understand that. Perhaps it will be all the better for you.";
			link.l1 = "Fine, I'll go to Poincy... Forgive me for being a fool, Marcus, see you..";
			link.l1.go = "patria_35";
		break;
		
		case "patria_x34":
			dialog.text = "You've gotten yourself into this mess, it's your fault.";
			link.l1 = "See you later, I guess...";
			link.l1.go = "patria_36";
		break;
		
		case "patria_35":
			dialog.text = "You need to rest, you're losing your touch. Come to me sometime, I'll get you some rum and fine maidens.";
			link.l1 = "Thank you, I'll play you a visit when I can.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
	}
}