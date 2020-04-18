#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			
			if (CheckAttribute(pchar, "questTemp.Caleuche.SeekAmulet") && drand(1) == 0 && sti(Pchar.money) >= 2000) 
			{
				dialog.text = "Look, sir, do not want to buy one amusing little thing? Take inexpensive, just some few thousand pesos...";
				link.l1 = "Hmm. Probably snuck this 'little thing', but now I try to shake off?";
				link.l1.go = "caleuche";
				break;
			}
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Hello. My name is " + GetFullName(npchar) + ". I do not hope that you would like to meet me, but, perhaps, you will remember this name...", 
					"Greetings, " + GetAddress_Form(NPChar) +  ". My name is " + GetFullName(npchar) + ".", 
					"My name is " + GetFullName(npchar) + ", " + GetAddress_Form(NPChar) + ". Nice meeting you.");
				link.l1 = RandPhraseSimple("Greetings.", "Hello.");
				link.l1.go = "First time";
				
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = "Hey, listen, would you like to earn a couple thousand pesos instead of this pitiful alms?";
					link.l2.go = "trial";
				}
				npchar.quest.meeting = "1";
			}			
			else
			{
				dialog.text = NPCStringReactionRepeat("See how low I fell...", 
					"Living on alms is not easy...", 
					"I'd give everything to break out of this poverty!",
					"You again?..", "block", 1, npchar, Dialog.CurrentNode);

				link.l1 = HeroStringReactionRepeat("I see. Well, no big deal.", 
					"Of course. There's little one can afford with such money.",
					"Then you shouldn't be wearing your trousers down to holes, but start to do something.", 
					"Ah-ha. Did bore?", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple("What do you need?", "What do you want?");
				link.l2.go = "Whants";
				
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = "Hey, listen, would you like to earn a couple thousand pesos instead of this pitiful alms?";
					link.l2.go = "trial";
				}
				link.l3 = LinkRandPhrase("Can you tell me anything of interest?", 
					"What's new in the town?", "Oh, would love to hear the latest gossip...");
				link.l3.go = "rumours_poor";
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple("No, why just bored? I'm not particularly busy, as you can see for yourself ...", 
				"You make me tired. Though I am a beggar, but also a man.");
			link.l1 = "Heh, I see...";
			link.l1.go = "exit";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
    		{
				dialog.text = PCharRepPhrase("Hmm, " + GetAddress_Form(NPChar) +  ", people say a lot of ugly things about you. But I trust in people - even in those like you. Please give me alms for a meal and a drink, have mercy on me.",
					"I beg you, " + GetAddress_Form(NPChar) +  "! Please don't turn a poor man down, give alms for a meal...");
				link.l1 = RandPhraseSimple("I won't give you anything.", "You'll do without it.");
				link.l1.go = "exit";
				Link.l2 = "Alright, and just how much do you need?";
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase("From you? Nothing.", "I don't need anything, " + GetAddress_Form(NPChar) + ", thanks.");
				link.l1 = RandPhraseSimple("Hmm, alright.", "Apparently, your life is not nearly as bad, buddy.");
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = "I would not reject even a petty copper, " + GetAddress_Form(NPChar) + ". As much as far your purse and your mercy can go...";
			Link.l1.edit = 2;			
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "Mocking at the weak and weary is a sin...";
				link.l1 = "Ha-ha-ha! You thought for a moment I'd give you money, you deranged beggar?!";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = "Thank you for " + FindRussianMoneyString(iTemp) + ", " + GetAddress_Form(NPChar) + ". Now I can buy some bread with that money...";
				link.l1 = "Here, tramp - go fortify yourself a bit.";
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 100 && iTemp <= 500)
			{
				dialog.text = "Thank you, " + GetAddress_Form(NPChar) + ". I can now live a week on that money!";
				link.l1 = "It was a pleasure to help.";
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 500 && iTemp <= 1000)
			{
				dialog.text = "Thank you, " + GetAddress_Form(NPChar) + ". I will tell everyone about your kindness!";
				link.l1 = "This is not really necessary.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", sti(iTemp/2000+0.5));
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = "Thank you, respected "+ GetSexPhrase("sir","lady") +" " + GetAddress_Form(NPChar) + ". May the Lord watch over you...";
				link.l1 = "Yeah, His protection would certainly not hurt!";
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), sti(iTemp/10000+0.5));
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 5000 && iTemp <= 10000)
			{
				dialog.text = "Thank you, "+ GetSexPhrase("most esteemed sir","most esteemed lady") +" " + GetAddress_Form(NPChar) + ". I wish you all the best!";
				link.l1 = "Thank you, buddy.";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", sti(iTemp/5000));
				AddCharacterExpToSkill(pchar, "Fortune", sti(iTemp/5000));
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 10000)
			{
				dialog.text = "Listen, " + GetAddress_Form(NPChar) + ", are you crazy or what? You're giving me " + FindRussianMoneyString(iTemp) + "! I cannot take such money, surely there must be a catch... Leave me be!";
				link.l1 = "Well, as you like...";
				link.l1.go = "exit";
			}
		break;
		
		case "trial":
			dialog.text = "A silly question, senor! If course, I'd love to. But... what will I have to do? Certainly you are not going to give me that money for the hell of it.";
			link.l1 = "Of course, not. Listen now. I am acting on behalf of the governor himself. His grace suspects that someone at the shipyard is deliberately sabotaging the launch of 'Alacantara', his galleon. And his suspicions just grew stronger after a French spy had been caught recently...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "";
			link.l1 = "His grace already heard the excuses of the shipwright, but he's not sure he was telling the truth. We need to find out, who is sabotaging the work and why. Go to the docks, take a look around and ask the workers, why the hell 'Alacantara' is still not ready to sail...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "";
			link.l1 = "No one will suspect you - you even might get hold of a pile of tobacco. As for me, no one will tell me anything. Everyone will know who I am working for. If you manage to learn anything worthy, you will receive three thousand pesos. Enough to abandon your 'job' for a month at the least.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "Three thousand pesos? But, esteemed sir...";
			link.l1 = "Are you haggling with me or what? Oh, and if you find out, who's behind all this stalling, you'll get another two thousand. Deal?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "Alright, senor. Shouldn't be too difficult - many of my old buddies are working at the docks these days. Hey, I, too, was a sailor some time ago. Like, ten years ago...";
			link.l1 = "You can tell me your life story later. Meet me on a pier at night after eleven. Now go.";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			chrDisableReloadToLocation = true;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "OpenTheDoors", 10.0);
			LAi_RemoveLoginTime(npchar);
			pchar.questTemp.Trial = "spy_poorman";
			pchar.quest.trial_spy_poorman.win_condition.l1 = "Timer";
			pchar.quest.trial_spy_poorman.win_condition.l1.date.hour  = 23.00;
			pchar.quest.trial_spy_poorman.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.trial_spy_poorman.function = "Trial_SetPoormanInPort";
			SetTimerCondition("Trial_ReturnPoormanNorm", 0, 0, 1, false);
			AddQuestRecord("Trial", "15");
		break;
		
		case "trial_6":
			dialog.text = "Good evening, senor...";
			link.l1 = "So? Did you learn anything?";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			dialog.text = "I did, senor, I did. Not sure, though, how does it all agree with what you told me... Have you brought the money? Five thousand pesos.";
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = "Don't worry. Here's your coin. Now spit it out.";
				link.l1.go = "trial_8";
			}
			else
			{
				link.l1 = "Information first, and then the money. Come on, don't waste my time!";
				link.l1.go = "trial_fail";
			}
		break;
		
		case "trial_fail":
			dialog.text = "You're trying to put me on, senor! If you're not going to pay - go and ask around yourself. And don't even think of reaching for your piece of iron - I'll call the guards!";
			link.l1 = "...";
			link.l1.go = "trial_fail_1";
		break;
		
		case "trial_fail_1":
			chrDisableReloadToLocation = true;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_fail";
			AddQuestRecord("Trial", "16");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_failspy_5";
		break;
		
		case "trial_8":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "This is the case. 'Alakantara' has been ready to sail since long time, but she didnt't get loaded intentionally, and by order of the governor. Well, so I'm told. And carpenters are now doing all odd jobs, which don't affect the vessel at sea\nEveryone is waiting for the arrival of some bark from Cartagen. The fact that 'Alakantara' insufficient, according to the captain, the stock of gunpowder. Here and wait 'Puebla' bring gunpowder for 'Alakantara'\nBut all this waiting is rather tired, so if 'Puebla' arrives in three days - 'Alakantara' hit the road, and so...";
			link.l1 = "Is that so? And who told you that? Name?";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "One of the sailors from 'Alacantara' - Felipe Dabinho... But that's actually no secret at all, and His Grace governor himself had ordered...";
			link.l1 = "I see. That's what I expected. French spies are in town - and they're wagging their tongs like fishwives. Any first comer can learn whatever he wants about the plans of His Grace. Oh, that Felipe Dabinho is in serious trouble now! And the bosun of 'Alacantara' too - it's his fault that his crew doesn't know a thing about discipline!";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "Oh... So, you knew it from the start? But why... It's not my fault! You told me to do it!";
			link.l1 = "It doesn't have to do anything with you, don't you worry. Now we know that the crew of 'Alacantara' can blab out any information to the enemy - even what's supposed to be kept in secret. Alright, you can go now. Thanks for your help. Go spend your money.";
			link.l1.go = "trial_11";
		break;
		
		case "trial_11":
			chrDisableReloadToLocation = true;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_win";
			AddQuestRecord("Trial", "17");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_12";
		break;
		
		
		case "Caleuche":
			dialog.text = "Pardon me, good sir... I won it the other day in the bone at some passer thought - charmed healing amulet, but lost: and it does not cure ailments, and market traders interested. And here you are - the sailor, captain, a learned man - look, you and she would be useful\nYes, is for you these couple of thousand - a mere trifle, and me - a piece of bread and a sip of rum for a month. Look, mister...";
			link.l1 = "Okay, show...";
			link.l1.go = "Caleuche_1";
		break;
		
		case "Caleuche_1":
			Log_Info("You got a strange amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Here...";
			link.l1 = "So-so... Interesting thing, I agree. Explicitly exported from the Indian settlements. Okay, I'll take her. Here's your silver";
			link.l1.go = "Caleuche_2";
		break;
		
		case "Caleuche_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Thank you, my dear sir! Hopefully, this thing will bring you luck! May God protect you!";
			link.l1 = "And you happy, man. Not only deflate all the money at once in a tavern.";
			link.l1.go = "Caleuche_3";
		break;
		
		case "Caleuche_3":
			DialogExit();
			GiveItem2Character(pchar, "kaleuche_amulet1"); 
		break;
		
	}
}
