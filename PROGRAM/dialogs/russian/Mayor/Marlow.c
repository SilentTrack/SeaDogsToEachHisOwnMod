
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);


    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) 
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) 
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    } 

	switch(Dialog.CurrentNode)
	{
		case "First time":
            dialog.text = NPCStringReactionRepeat("Do you have got something to tell me? No? Then get away from here! Don't bother me then.",
                         "I trust that I have made myself clear.", "Although I've made myself clear, you keep annoying me!",
                         "Right, I am getting tired of this rudeness.", "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I am leaving already.",
                                               "Of course, Pastor.",
                                               "I am sorry, Pastor.",
                                               "Oups...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Are you insane? Wanted to play a butcher? All pirates are angry with you, pal, so you better leave this place.", "It seems, pal, that you got mad. Wanted to stretch your hands a bit? No offence, but you have nothing to do here. Get lost!");
				link.l1 = RandPhraseSimple("Listen, I want to fix the situation...", "Help me to solve the problem...");
				link.l1.go = "pirate_town";
				break;
			}
			
			
			if(CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && !CheckAttribute(npchar, "quest.sharkbegin"))
			{
				link.l1 = "I am trying to find Shark Dodson. They say that you are the last man who saw him. Can you help me with that?";
				link.l1.go = "Shark";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax" && CheckCharacterItem(pchar, "witches_hammer"))
			{
				link.l1 = "Why are you so rude if you are interested in getting your desired book from me?";
				link.l1.go = "book";
			}
			
			
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "I want to talk about your prisoner.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Hello, Pastor. I want to talk about your mission.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "I want to talk about your prisoner.";
					link.l1.go = "CapComission6";
				}
			}
		break;
		
		case "shark":
			dialog.text = "Steven Dodson? Don't know how my story would help you because Shark has been missing for the last few months and no one has seen him. It is not a surprise though, he has killed Blaze Sharp and discredited his own name by this foolish action. He has made a few powerful corsairs his enemies.";
			link.l1 = "I have all reasons to think that Shark is innocent of Sharp's death. I can't prove it, perhaps Shark can do it himself. Are you going to tell me anything about him?";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "A few months ago, Steven came to me and offered a very odd deal: he left his frigate Fortune in gage for a month in exchange for a brig loaded with provisions. Then he either return me the brig and money for provisions or I keep his frigate. A month passed - no sign of neither Shark, nor my brig, nor money\nBesides, I heard rumors that Blaze is murdered and Shark is suspected. What could I think? Correct! I thought that Steven had escaped from the worst. I sold his frigate to some Englishman named William Patterson, he was very pleased and paid a great pile of doubloons for the ship\nTherefore, I have completely compensated my expenses and hold no grudge against him. I don't care about Sharp's death, I have my own problems to worry about.";
			link.l1 = "Don't you think that if he has wanted to escape he wouldn't need your brig? He had his own ship hundred times better then any brig. It looks like Shark had a plan but it hasn't turned well so he got too late.";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "As I have already told you, I don't care about Dodson's problems. I have fulfilled my part of the bargain and you'd better ask him why he had a such need in my brig. I haven't forced him to take it.";
			link.l1 = "Fine, whatever. You are right, of course. Tell me, are you aware about where Steven was heading on your brig?";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "Who knows for sure. But I have got some guesses. He sailed North West towards Main. So it's either Bay of Peril which is known for it's hostile Indians or New Spain which is known for it's Papists and inquisition\nI doubt that he would go there. But they say that there is a strange place called Justice Island North West of Cuba. A lot of people consider this a myth but not me. Not because I am such a romantic person, but because there are real people who sail there on their longboats. Or they used to.";
			link.l1 = "And who are they?";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "Buccaneers from Cuba. They were loading there barques with bull's carcasses and sailing to north - west. They were always returning a bit later with their pockets filled with coins or with rare and valuable goods.";
			link.l1 = "Intriguing! Where can I find those buccaneers?";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "Why ask me? Search Cuba's woods. Even if you will find them, they won't tell you anything, why should they expose the source of their good living? So don't waste your time, no one has seen them doing it again since a long time\nI heard of some notes written by Spanish sailor Alvarado who visited the island himself. So I am curious, perhaps Steven did sail there after all.";
			link.l1 = "The unknown isle which is not on maps... Well. That is not promising information.";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "I have told you in the beginning that my story won't help you. And why do you need Dodson?";
			link.l1 = "Me and the Wood Devil want to elect him as leader of the Brethren of the Coast. As I have told you already there are some serious reasons to suggest that Blaze was murdered by someone else.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "Heh! I take it that Jan is standing for him? Well, you know the law - Dodson will have to get a vote from the each baron.";
			link.l1 = "I do know the law. My second question then. Will you vote for Dodson on the election?";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "Well, he should return first. Actually, I don't care who will lead the Brethren as long as he does his business well and doesn't bother me. As I said, I have problems of my own. Do you know how many witches and mages are on our island? No? I will tell you: a legion! Besides, there are also a lot of Papists in Santiago and Havana\nSpeaking of mages. There is a book called 'Hammer for the Witches'. I really want to get it, but only in English, I don't need Latin, German or Spanish translations, I don't know these languages. Bring me the book and I will vote for Dodson\nBe aware that Jackman promised me to find it too, so if he succeeds first... don't blame me then.";
			link.l1 = "Fine, I will consider that. Thanks for your time. See you.";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "after_marlow";
			npchar.quest.sharkbegin = "true";
			AddQuestRecord("SharkHunt", "2");
		break;
		
		case "book":
			dialog.text = "The book? I take it that you are talking about the 'Hammer for the Witches'?";
			link.l1 = "Of course. I was able to find it for you. It is on English as you have asked.";
			link.l1.go = "book_1";
		break;
		
		case "book_1":
			dialog.text = "Ha, sorry for such a rough welcome, pal. Won't happen again... Let me see that wonder!";
			link.l1 = "Sure, take a look.";
			link.l1.go = "book_2";
		break;
		
		case "book_2":
			RemoveItems(pchar, "witches_hammer", 1); 
			dialog.text = "Finally! Tremble now, servants of hell! I won't leave you alone until my hand is able to hand...";
			link.l1 = "I am glad for you, Pastor. So what about your vote?";
			link.l1.go = "book_3";
		break;
		
		case "book_3":
			dialog.text = "As I've said you before - I don't care about who will become the head. I am sure that Svensson won't choose an unworthy man. So take my vote. Do whatever you want with it. Here is my shard.";
			link.l1 = "Thank you, Zechariah. See you there!";
			link.l1.go = "book_4";
		break;
		
		case "book_4":
			GiveItem2Character(pchar, "splinter_zm"); 
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "27");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", I am glad to see you! What do you wish?",
                         "What do you want?", "Again? Don't bother people if you have got nothing to do!",
                         "And "+ GetSexPhrase("good privateer","good girl") +", , you can live for now. But I don't want to talk to you anymore.", "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I am just paying a visit.",
                                               "Nothing...",
                                               "Fine, Pastor, I am sorry...",
                                               "Damn it, caught it at last!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Are you insane? Wanted to play a butcher? All pirates are angry with you, pal, so you better leave this place�", "It seems, pal, that you got mad. Wanted to stretch your hands a bit? No offence, but you have nothing to do here. Get lost!");
				link.l1 = RandPhraseSimple("Listen, I want to fix the situation�", "Help me to solve the problem�");
				link.l1.go = "pirate_town";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "It's about your prisoner.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}		
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
			{
				link.l1 = "Good day, Pastor, it is about your prisoner.";
				link.l1.go = "CapComission3";
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				link.l1 = "It's about your prisoner.";
				link.l1.go = "CapComission6";
			}
		break;
		
	
		case "CapComission1":
			dialog.text = "Ha-ha. Do you think that I have got only one prisoner here? Name him.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName + ". Is he here?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "He was. I have sold him away to this plantation owner from Barbados - colonel Bishop, when he was here a week ago.";
				link.l1 = "Damn...Damn...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ah, at last. I was thinking to sell him away to that plantation owner from Barbados, he will be here in a week or two... Do you have a ransom?";
				link.l1 = "Look, there is a small problem... Actually, I don't have so much money. But I am ready to work.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "It's good that you haven't sold him. Here are your coins - 150000 pesos. Where can I get him?"
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "You were too  slow... And why do you care about him? I has been negotiating with his relatives only.";
			link.l1 = "The have asked me to come here.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Well, I am late..";
			link.l1 = "Listen for how much have you sold him if it's not a secret?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, it's not. But I won't tell you, you would laugh if I will. Ha-ha! Farewell.";
			link.l1 = "See you.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Well, well.. I have got a one business... Don't even know how to start. I need to sink one pirate who has went too far.";
				link.l1 = "Can't he simply die in the jungles?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "Well, " + pchar.name + ", you know, it won't work like that. Come back with money and you'll get you weakling, ha-ha.";
				link.l1 = "Fine. See you.";
				link.l1.go = "CapComission2_4";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "It's not the way how business works, you know... I don't need his death, I need to teach some people to avoid taking my part of a loot. But I won't regret his death.";
			link.l1 = "Why don't you send your own people for him?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "Hm.. Well" + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " has convinced a part of pirates that in our stash not far from " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + ". Their two ships raised anchor not long ago and sailed to " + sLoc + ". Now you see why I can't trust my men to do that job?";
			link.l1 = "I do. How much time do I have?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12-15 days not more, I suppose. I don't want them to get to the stash, there is no meaning to sink them with a valuable cargo. At least, they could it get here...";
			link.l1 = "Fine, I am in. I'll try to catch them.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Don't worry. My men will deliver him to your ship. And why do you care about him?";
			link.l1 = "I don't. His relatives asked me to deliver him.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, that's fine. I was almost sorry for giving such a low price for your man. Ha-ha. Farewell.";
			link.l1 = "See you.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));			
			addMoneyToCharacter(pchar, -150000);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "So, , " + GetFullName(pchar) + ", did you sink my buddy?.. He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "No. I failed to catch them. And I didn't meet them on return.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "I have sunk them as you have told me.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Damn! It doesn't matter now, right?.. And what will be your next suggest?";
			link.l1 = "Maybe you have got an easer job for me?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Listen, "+ NPChar.name +", bring down the price for the prisoner...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "No.";
			link.l1 = "..Farewell then...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Bring down the price? I have just lost my stash because of your sluggishness! And now I can rise up the price! You can take him for 200000 pesos if you want.";
			link.l1 = "It's way too expensive... Farewell...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Damn, take your coins.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","��"));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "You can take this weakling...";
			link.l1 = "Farewell.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Well done! Take your weakling and good luck.";
			link.l1 = "Thanks. Farewell.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission6":
			dialog.text = "Do you have a ransom? I wasn't kidding about selling the man to planters.";			
			link.l1 = "Listen, "+ NPChar.name +", there is a problem... I don't have that much money. But I am ready to work.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "It's good that you haven't sold him. Here are your coins - 150000 pesos. Where can I get him?"
				link.l2.go = "CapComission2_3";
			}			
		break;

		
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Robbery!!! That is unacceptable! Prepare yourself, "+ GetSexPhrase("pal","girl") +"...", "Thought that you could rob me? You are done...", "Wait, what the hell? Turns out that you are a thief! End of the line, good man...");
			link.l1 = LinkRandPhrase("Damn!", "Carramba!!", "Damn it!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("Get away ","Get away") +" from here!", "Get out of my home!");
			link.l1 = "Oups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) 
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Don't bother me with your cheap promises. Next time you might won't like the result...";
        			link.l1 = "I got it.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryRepeat_2":
            dialog.text = "It's over, no talking.";
			link.l1 = RandPhraseSimple("I hope that you will show more respect to me as well and will stop barking?", "You can be sure, Jaques, I won't.");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) 
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "I hope that you will show more respect to me as well and will stop barking?";
        			link.l1 = "You can be sure, Pastor, I won't.";
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
            DoReloadCharacterToLocation("Puertoprincipe_town","reload","reload6");
		break;
		
		case "pirate_town":
            dialog.text = "Solve the problem? Do you have any clue what you have done? Anyway, bring me a million pesos and I will persuade lads to forget your deed. If don't like the idea then you may go to hell.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Fine, I am ready to pay.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Got it. I am leaving.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;
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
	}
}
