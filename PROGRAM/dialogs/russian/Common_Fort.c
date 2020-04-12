// boal 25/04/04 общий диалог солдат форта
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Fort\" + NPChar.City + "_Fort.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":			
            NextDiag.TempNode = "First time";
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("A spy! Surrender your weapons and follow me!", "An enemy agent! Seize "+ GetSexPhrase("him","her") +"!");
				link.l1 = RandPhraseSimple("Shut up, sissy!", "Says you!");
				link.l1.go = "fight"; 
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetRelation2BaseNation(sti(npchar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple("Who are you and what are you doing here?", "Hold still! Who are you? For shat reason are you trying to enter the fort?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Officer, I have " + GetRusNameNationLicence(sti(npchar.nation)) + ", so I am here on legal grounds. Here, please take a look...";
						link.l1.go = "LicenceOk";
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("Pirates in the fort?! Seize"+ GetSexPhrase("him","her") +"!!", "It is a pirate, sniffs up something here!! To arrest!!!!");
							link.l1 = RandPhraseSimple("Yes, I am a pirate - now what?", "Heh, catch me if you can...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Don't you see on the mast of my ship the flag" + NationNameGenitive(sti(pchar.nation)) + "?!";
						}
						else //если причалил не в городе
						{
							link.l1 = "I cast anchor at " + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + " under the flag" + NationNameGenitive(sti(pchar.nation)) + ". For crying out loud!";
						}
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
						{
							link.l1.go = "PegYou";
						}
						else
						{
							link.l1.go = "NotPegYou";
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn)) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Oh, captain, we've had such a great time with you at sea! So many ships we have sunk together under your command! And here...";
									link.l1 = "And here, my friend, you can feast your eyes upon charming ladies, for you will not see them at sea.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "Captain, what have we done to deserve this?! We aren't landlubbers, are we?";
									link.l1 = "Quiet, sailor! Your post is an important and honorary one, so quit your whining.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "What's up with te sea, captain? Will we ever see it again?";
									link.l1 = "But of course, sailor! Once you are relieved from duty, you can go to the pier and enjoy the sea as much as you like.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "I want to complain, captain: every one of us longs to ship out. We're all totally fed up with this land duty!";
									link.l1 = "I got tired from this whining! A drinking-bout has you and on earth! Serve wherein you were put by a captain! And then somebody will be to hitch up for an example.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "I'll tell you in confidence, captain, the new governor is a grafter and embezzler of funds. Now that's really none of my business...";
									link.l1 = "Exactly, corsair. Your business is standing at your post and keeping order. And to hang the governor on the yardarm is my business. Good job!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Thank you for not forgetting about us, captain! We'd go through fire and water for your sake!";
									link.l1 = "I know your type, crooks! All you really love is gold. Now, there's a carouse at the tavern today, it's on me. Don't forget to show up.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Heh, captain! Just think about it - can a corsair really be a keeper of order?! It's been so long we've last been on the real business!";
									link.l1 = "No time for relaxing, corsair! Enemy armadas are scouring the seas near our islands, and we must be ready for a bloodbath at any time.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Captain, they say that the Crown had sent another squadron our way?";
									link.l1 = "Of course, corsair. While we live, there will be no peace for us. And even in Hell we shall be fighting devils!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Yo-ho-ho! Now that was a real carouse yesterday, captain! It's a pity you weren't there.";
									link.l1 = "No big deal, I'll make up for it. And I don't envy you, guys.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "I'll tell you in confidence, captain, 'cause you've always treated us well - we had some good time with a really nice chick yesterday...";
									link.l1 = "Heh, corsair, a noose is something you really need!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Cap! Please relieve me from this cursed duty! I simply can't play the part of a keeper of order anymore.";
									link.l1 = "Night watch on a ship is no cakewalk, either. Now duty is duty, whatever and wherever it is.";
									link.l1.go = "exit";
								break;
							}
							link.l2 = RandPhraseSimple("I've got an important business!", "I have business with you.");
							link.l2.go = "quests";//(перессылка в файл города)
							break;
						}
					}
					
					//Jason --> мини-квест Дефицитный товар
					if (!CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && sti(pchar.rank) < 4 && !CheckAttribute(pchar, "questTemp.Wine") && npchar.location.group == "soldiers")
					{// Addon 2016-1 Jason пиратская линейка
						if (npchar.location.locator == "protector1" || npchar.location.locator == "protector2")
						{
							dialog.text = "Hey, buddy! Can you make me a small favor?";
							link.l1 = "Depends on what needs to be done.";
							link.l1.go = "Wine_soldier";
							link.l2 = "I don't have time for this.";
							link.l2.go = "exit";
							pchar.questTemp.Wine = "true";
							break;
						}
					}
					// <-- мини-квест Дефицитный товар
					
					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "Can't you see? I'm on duty. Stop bothering me.";
							link.l1 = "Alright, alright...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Are you going to tell me about some suspicious activity?";
							link.l1 = "No, none at all, and I am a captain, by the way. I see you're not listening anymore? See ya.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "This is a military objective, so keep quiet there.";
							link.l1 = "Alright, I'll keep that in mind.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Such fair weather, and I'm bound to stand there. In towns, there are girls at the least, and here.";
							link.l1 = ""+ GetSexPhrase("I sympathize, but there's nothing I can do to help - it's your duty.","Hey! What's wrong with me? Am I not a girl?") +"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "If you like to chat, find someone else. I must keep order here, and I have no time for chit-chat.";
							link.l1 = "Oh, no, I was just "+ GetSexPhrase("checking","checking") +", if you're still alive - you were standing just like a statue.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "You probably think that garrison working days are a cakewalk? Says you! It's a hard and important work. I remember... ";
							link.l1 = "You tall me that story some other time - I am in a bit of hurry today.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "Careful here, you're in a fort! Be quiet as a lamb!";
							link.l1 = "As you say, soldier.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "Hey! Do you have any water, by chance? I am dying of thirst.";
							link.l1 = "No, buddy, keep your patience...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "How boring is the garrison life - only rednecks like you around! Now the town garrison surely has better time...";
							link.l1 = "And you are calling this 'being on duty'? This way you'll surely let a spy slip past you!";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+ GetSexPhrase("You look like a stout guy, don't you? Would you like to sign up for duty at the fort's garrison? We have roomy barracks, two meals a day - and booze for free.","Oh, young lady, you have no idea, how pleasant it is to meet such a nice damsel in this back of beyond!") +"";
							link.l1 = ""+ GetSexPhrase("That's certainly tempting, but I still must refuse. All that drill is just not for me.","Thank you for a compliment, soldier.") +".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "Such heat... I would gladly give up half of my life to go back to Europe.";
							link.l1 = "Yeah, I can see that you're not fit for the local climate.";
							link.l1.go = "exit";
						break;
					}
					link.l3 = "I see... You know, I "+ GetSexPhrase("wanted to") +" ask you something...";
					link.l3.go = "quests";//(перессылка в файл города)
				}
			}
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_soldier":
			dialog.text = "You see, I badly want some wine... But not the local swill made of rotten fruits, which sells for two pesos per barrel - I want a bottle of real European wine. You can get it in the town from merchants. The price is quite steep, but I will pay in full and will even add three hundred pesos on top of it. So, will you bring me some?";
			link.l1 = "And why can't you het it yourself? You won't need to overpay - just wait until you're relieved and go for it. What's the catch?";
			link.l1.go = "Wine_soldier_1";
		break;
		
		case "Wine_soldier_1":
			dialog.text = "There is no catch. I just can't leave the fort to go to the town until I get my leave, which is not going to happen anytime soon. Besides, our commander strictly banned all drinking in the fort, bad cess to him! So, will you help a soldier out?";
			link.l1 = "Well, why not? I'll fetch you that wine, I have some spare time anyway.";
			link.l1.go = "Wine_soldier_2";
			link.l2 = "I am sorry, buddy, but I can't do that. Look for someone else to help you.";
			link.l2.go = "exit";
		break;
		
		case "Wine_soldier_2":
			dialog.text = "Great! Thank you very much! Today I am on watch, so come tomorrow. You'll find me on the fort's topmost platform - there you can slip me the bottle so no one takes notice...";
			link.l1 = "Alright. Wait for me - I'll come see you tomorrow.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.id = npchar.ID;
			pchar.questTemp.Wine.SName = GetFullName(npchar);
			pchar.questTemp.Wine.bottle = "true";
			npchar.lifeday = 5;
			SetFunctionTimerCondition("Wine_Exchange", 0, 0, 1, false);
			pchar.questTemp.Wine.City = GetCityNameByIsland(LoadedLocation.islandId);
			Log_TestInfo(pchar.questTemp.Wine.City);
			SaveCurrentQuestDateParam("questTemp.Wine_bottle");
			AddQuestRecord("Wine", "0");
		break;
		// <-- мини-квест Дефицитный товар
		
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("It seems to me some trickery is afoot. Let's go see the commandant, "+ GetSexPhrase("buddy","deary") +", and figure it all out...", "Hmm... Something tells me that you're not "+ GetSexPhrase("the one","the one") +", who you're pretending to be... Now surrender your weapons, " + GetAddress_Form(npchar) + ", and follow me for further investigation!");
			link.l1 = RandPhraseSimple("Says you!", "When two Sundays come in one week...");
			link.l1.go = "fight";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Oh, I see... Everything seems to be in order, you're free to go, " + GetAddress_Form(pchar) + ".", "I must have gotten a bit tired standing on watch... Everything seems to be fine, " + GetAddress_Form(pchar) + ", I am sorry.");
			link.l1 = "That'll teach you!";
			link.l1.go = "exit";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "Just come to think of it! Such insolence! To come here under the guise of a merchant! Your pictures are posted in every barrack, you bastard! You won't get away with it this time! Seize him!";
				link.l1 = RandPhraseSimple("Arrgh!..", "Well, you asked for it...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе
			{
				dialog.text = "You have come to trade here? Might I ask how? Where is your ship? You know, it all looks very suspicious, and I am forced to detain you until we figure it all out. Surrender your weapons and follow me!";
				link.l1 = RandPhraseSimple("Says you!", "When two Sundays come in one week...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "Your license has to be revoked since it is expired and is not valid for that reason. Surrender your weapons and follow me for further investigation!";
				link.l1 = RandPhraseSimple("Says you!", "When two Sundays come in one week...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Hmm... Everything looks okay. Still, I must note that your license expires today. I will let you pass this time, but you still will have to get a new license.";
				link.l1 = "Thank you, I'll do it at my earliest convenience.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Hmm... Everything looks okay. Still, I must note that your license expires rather soon - it is still valid only for " + FindRussianDaysString(iTemp) + ". So keep that in mind, " + GetAddress_Form(npchar) + ".";
				link.l1 = "Thank you, I'll get a new one at my earliest convenience.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Well, everything looks fine. Your license is valid for another " + FindRussianDaysString(iTemp) + ". You may pass.", "Everything is clear, "+GetAddress_Form(npchar)+". You can freely go in and out of town, your license is valid for another " + FindRussianDaysString(iTemp) + ". Sorry for bothering you.", "Everything looks fine, " + GetAddress_Form(npchar) + ", I am no longer keeping you there.");
				link.l1 = RandPhraseSimple("Excellent. Best regards.", "Thank you, officer.");
				link.l1.go = "exit";
			}
		break;

		//замечение по обнаженному оружию
		case "SoldierNotBlade":
			dialog.text = LinkRandPhrase("Why the hell are you running around with an unsheathed blade? Put away your weapon at once!", "I am ordering you to sheathe your weapon at once!", "Hey, "+ GetSexPhrase("buddy","lass") +", stop scaring the folks! Sheathe your weapon.");
			link.l1 = LinkRandPhrase("Fine.", "Okay.", "As you say...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Says you!", "There's no harm in dreaming...", "When two Sundays come in one week.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
	}
}