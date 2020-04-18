void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk, bOk1;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Gang" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_Robbed":
			int iMoney = makeint(makeint(Pchar.money)/20)*10;
			AddMoneyToCharacter(pchar, -iMoney);
			AddSimpleRumour(LinkRandPhrase("Have you heard? The local robber " + GetFullName(npchar) + " found a new victim. One captain has chickened out and bought him off. They say, he gave him " + FindRussianMoneyString(iMoney) + ", he-he... ", 
				"Yeah, captain " + GetFullName(pchar) + ", I already heard that you had to pay " + FindRussianMoneyString(iMoney) + ", to buy off a local bandit, " + GetFullName(npchar) + ". Now that's what I call bad luck! Ha-ha-ha!", 
				"Have you heard that the local bandits attacked one captain? He was totally robbed - lost " + FindRussianMoneyString(iMoney) + "!"), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgain";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();			
		break;

		case "exit_fight":
			sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_RunFight":
			AddSimpleRumour(LinkRandPhrase(RandPhraseSimple("Have you heard? That bandit  " + GetFullName(npchar) + " has finally found justice. He and his boys tries to rob "+ GetSexPhrase("some captain, but he turned out to be","some lady captain, but she turned out to be") +" a tough nut. So our daring robber had pooped his pants, ha-ha! That'll be a lesson for him! Robbing the local farmers is one thing - a brave captain is a different story!", 
				"Thank you, captain " + GetFullName(pchar) + ", for finally dealing with the gang of that bandit " + GetFullName(npchar) + ". Those rascals were really a pain in everyone's butt. We were scared to even send couriers to the farm for milk - they could have intercepted them and rob of all the money."), 
				"Have you heard, "+ GetSexPhrase("finally, some captain","finally, some lady captain") +" repulsed that rascal " + GetFullName(npchar) + ", who was at work in the jungle, terrorizing all the local farmers. I wonder if that disinclines them for their dirty deeds for long enough...", 
				"Have you heard that local bandit " + GetFullName(npchar) + " and his boys attempted to rob "+ GetSexPhrase("some captain","some lady captain") +"? Bah! Nothing of the sort! That captain turned out to be a tough nut. They say, he these grief robbers chased on jungle like a shark flocks of sardines. Thank God that there are still people who can to stand up for us at a time when the authorities do nothing, too busy with their dark deeds ..."), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorAfraid(sld, Pchar, true);
				sld.Dialog.CurrentNode = "GetTheHellOut";
			}
			DialogExit();
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "GetLost";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}		
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase(LinkRandPhrase("Stand where you are and drop your weapons! Your money or your life!",
				"Stand where you are, "+ GetSexPhrase("traveler","lass") +"! Don't touch your weapons and no sudden moves!",
				"Stand where you are, "+ GetSexPhrase("traveler","lass") +"! This is a toll road. If you wanna pass - pay the toll."),
				LinkRandPhrase("Hey, "+ GetSexPhrase("buddy","lass") +"! Not so fast! I want to see how heavy your purse is.",
				"Would you come closer, friend. I want to hear the jingle of gold in your purse.",
				"Hold on, "+ GetSexPhrase("buddy","lass") +". Me and the guys had bet on how much gold will fit into your purse. Now we must check it before things get violent."),
				"Don't hurry, "+ GetSexPhrase("traveler","darling") +"! Let's have a heart-t-heart talk, shall we?");				
			Link.l1 = LinkRandPhrase(LinkRandPhrase("What's all this nonsense?","What's up?", "What are you talking about?"), "What do you mean?", "Just what are you implying?");
			Link.l1.go = "Node_2";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("Brigands?! Excellent, I was longing for a fight!", 
				"Oh, you're brigands! Hiding from justice, I take it? Well, it seems that justice has just come for you...",
				"Haven't you been taught that robbering people a bad thing? Seems that I'll have to teach you that lesson..."),
				LinkRandPhrase("Oh, you're an insolent one, aren't you?! I hope that your blade is as sharp as your tongue.",
				"I see your tongue is sharp - but is your blade as sharp?",
				"Oh, bandits! Your kind is getting handed all the time - and you still have no clue what's good for you."),
				LinkRandPhrase(RandPhraseSimple("Oh, brigands! You know, I usually do not waste words with your kind!",
				"What an insolent fellow! Stinks like a steaming pile of shit - and still dares to address a decent "+ GetSexPhrase("guy","girl") +"."),
				"I will not waste words with you, but you'll find my pistol quite talkative!",
				"Brigands again! Well, I will not promise you the gallows, but I can surely give you a couple of holes in your belly!"));
			Link.l2.go = "CheckSkills";	
			Link.l3 = LinkRandPhrase("And do you know that a patrolling party is following me closely? I can just give them a whistle - and you are done for.", 
				RandPhraseSimple("You know, I can call the patrol - are you not afraid of that? They are nearby, looking for you.", 
				"A patrolling party has been recently dispatched to find you, and they shall be there any moment. You're taking a great risk."),
				RandPhraseSimple("I would advise you to take to your heels. A patrolling party is heading this way, I've just talked with their officer.",
				"I would gladly continued the conversation, but I'm afraid the patrol unit that I just met, will not develop our acquaintance into a close friendship."));
			Link.l3.go = "Node_3";
		break;
		
		case "Node_2":
			dialog.text = LinkRandPhrase(LinkRandPhrase("Don't play the fool! Cash on the nail - and maybe then I will let you go!",
				"Haven't you heard about the travelling pay? You will not part with the gold - will part with a head!",
				"Heh, this ordinary adventure will cost you a purse... if I do not get angry."),
				RandPhraseSimple("It's very simple. You give us all your gold and then you are free to leave - or you stay here, and we take off with your gold, anyway. But I think that this way is not what you would like, he-he.",
				"Don't pretend you don't understand! Give me your purse if you don't want me to take it from your body!"),
				"I'll explain, if you're so slow-witted - give me all your money, if you cherish your life.");
			Link.l1 = "Goddammit, scoundrel! I only have " + makeint(makeint(Pchar.money)/20)*10 + " pesos.";
			Link.l1.go = "CheckMoney";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("You want my money? Come and get it, and I will see how much you're worth!",
				"How dare you, boor! I'll teach you a lesson in good manners!",
				"What a self-assurance! Well, let's see how you stand against a real "+ GetSexPhrase("naval officer","girl is old salt") +"!"),
				LinkRandPhrase("You should be flogged for such outrage!",
				"You scoundrels! Pray to your sea devils!",
				"You should have been hanged long ago, gallows-birds! Well, it seems that I will have to stain my saber with your blood!"),
				RandPhraseSimple("And what makes you think that I would give you my money?",
				"And don't you think that I am not bad armed and don't run away so easily?"));
			Link.l2.go = "CheckSkills";	
		break;

		case "Node_3":
			bOk = makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 90;  
			if(bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				dialog.text = RandPhraseSimple("Damn it! Alright, you may leave. But be quiet about it!", 
					"This time you got lucky, but the next time you'll owe us twice as much! Don't forget to remind us, he-he.");
				Link.l1 = RandPhraseSimple("But of course.", "Run already, while you still can.");
				Link.l1.go = "Exit_NoFight";
			}
			else
			{
				bOk1 = makeint(pchar.reputation.nobility) < 51 && makeint(pchar.reputation.nobility) > 41;
				if(!bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
				{
					dialog.text = RandPhraseSimple("We'll butcher you quietly, you won't even let out a scream.", 
						"Goddammit! We'll have to butcher you quickly before you can raise alarm.");
					Link.l1 = "Well, this is your funeral. I warned you.";
					Link.l1.go = "Exit_Fight";
				}
				else
				{
					dialog.text = RandPhraseSimple("And why would I care about your patrol? I am paying them. So, slip me your purse and shut the hell up.", 
						"Who decided to scare you? I myself in this jungle patrol to like you. Yet no one has not left without a fee!");
					Link.l1 = "Goddammit, scoundrel! I only have " + makeint(makeint(Pchar.money)/20)*10 + " pesos.";
					Link.l1.go = "CheckMoney";	
					Link.l2 = RandPhraseSimple(LinkRandPhrase("I will not be taking orders from the likes of you.", 
						"I'll make a couple of new holes in your dome for such impudence - just to ventilate your brains a bit.",
						"Such impudence shall not go unpunished!"),
						"You should not have done that...");
					Link.l2.go = "CheckSkills";
				}
			}
		break;
		
		case "CheckSkills":
			bool z_ok = (GetCharacterSkillToOld(Pchar, "FencingS") >= 7) && (makeint(Pchar.Rank) >= 8) && (Makeint(PChar.reputation.nobility) <= 30);
			if (z_ok || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				Diag.TempNode = "GetLost";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Hey, don't get so excited, "+ GetSexPhrase("buddy","lass") +"! I was just kidding! Go about your business!",
					"Alright, I crossed my mind. You may go, if you're so formidable."),
					"What, a "+ GetSexPhrase("'gallant captain'","'militant lass'") +"? again? Alright, go in peace...",
					"Quiet, "+ GetSexPhrase("buddy","lass") +". You see, we were mistaken "+ GetSexPhrase(" - we thought it was a merchant","") +". Go away from sin.");
				Link.l1 = LinkRandPhrase(LinkRandPhrase("Alright, until we meet again, then!",
					"You should quit robbering, while you still can.",
					"Alright, but if I ever see you again..."),
					RandPhraseSimple("Next time pay attention whom you are threatening, cur.",
					"Thank God that I am in a good mood today."),	
					RandPhraseSimple("This criminal trade will surely get you in the end. Farewell.",
					"That's a wise decision. Well, good luck!"));
				Link.l1.go = "Exit_NoFight";
				Link.l99 = LinkRandPhrase("No, buddy. Now I'll teach you good manners!",
					"Chickened out? Well, one should answer for his deeds, right?",
					"No! Now I will not calm down until I have skinned you alive!");
				Link.l99.go = "GetTheHellOut";
			}
			else 
			{
				dialog.text = LinkRandPhrase("But it could go in peace! Now blame yourself!",
								"You should not have started it, you rascal! Now you will die like a dog!",
								"Ah well! I'll tear you to pieces! Cut out the liver and feed the dogs!");
				Link.l1 = RandPhraseSimple("I will stuff your words back into your throat!","Whom are you threatening, scum?!");
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "CheckMoney":
			if(makeint(makeint(Pchar.money)/20)*10 >= makeint(Pchar.rank)*100)
			{
				Diag.TempNode = "OnceAgain";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Alright! Give it to me and get lost!",
					"Not much, but still better than nothing. It's good to deal with a smart person! You're free to go."),
					"Now that's a different story! Like one my friend was saying - it's always good to listen to someone smart, but you can always talk to the fool! He-he!",
					"In exchange for your gold I shall give you an advice - you should not walk in the jungle, if you're "+ GetSexPhrase("such a wimp. Drink your rum at the tavern, if you know what's good for you!","a lass. You know, being robbed is not the worst that could have happened to you.") +".");
				Link.l1 = "Damned hanged!";
				Link.l1.go = "Exit_Robbed";				
			}
			else
			{
				dialog.text = "I guess you're trying to put me on! No worry, though - I'll tickle you, and maybe something drops.";
				Link.l1 = "Dammit!";
				Link.l1.go = "Exit_Fight";				
			}				
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase("You again? Run home to your mommy, before I am angry with you!",
				"What? You haven't given up all your gold yet? Ha-ha!",
				"Look, "+ GetSexPhrase("buddy","lass") +", you bore me! Go away of sight as long still alive!");
			Link.l1 = "Yeah, I am already leaving.";
			Link.l1.go = "Exit";
			Link.l2 = "I thought that it would be not fair. Here, I decided to equalize the costs...";
			Link.l2.go = "Exit_Fight";
		break;
				
		case "GetLost":
			Diag.TempNode = "GetLost";
			dialog.text = LinkRandPhrase("What else do you need? We have already agreed that you're leaving!",
				"Leave me be, "+ GetSexPhrase("fellow","lass") +". I mind my own business, you have your own, and we shouldn't try to get along!",
				"Leave now, "+ GetSexPhrase("buddy","lass") +"! Goddammit - are you really willing to give away all your money?");
			Link.l1 = "Yeah, I am already leaving.";
			Link.l1.go = "Exit";
			Link.l2 = "I remembered that you did not say goodbye! So let's say - goodbye ...!";
			Link.l2.go = "Exit_Fight";
		break;

		case "GetTheHellOut":
			Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase("Leave me be! Help me! I want to live!",
				"Help me! "+ GetSexPhrase("He is a maniac","She is a maniac") +"! Don't kill me!",
				"Spare me! I am just a humble brigand! I am too young to die!");
			Link.l1 = LinkRandPhrase(LinkRandPhrase("If you stayed at home, you would have lived on!",
				"You should have thought about it before!",
				"You should have realized the consequences!"),
				"Sooner or later, this was bound to happen.",
				"Late repent - Protect Yourselves!");
			Link.l1.go = "exit_Fight";			
		break; 				
	}
}
