void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "Exit_Fight":	
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar); 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			
			if(pchar.GenQuest.EncGirl == "RapersTreasure")
			{
				LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
			}			
			else
			{
				LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");			
				sld = CharacterFromID("CangGirl");
				LAi_SetActorType(sld);
				LAi_ActorAfraid(sld, npchar, true);
			}	
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_RapersBeforeDialog");
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();	
			AddDialogExitQuest("OpenTheDoors");			
		break;
		
		case "First time":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}

			if(pchar.GenQuest.EncGirl == "Begin_1")
			{
				dialog.text = LinkRandPhrase("Go your own way, "+ GetSexPhrase("buddy","lass") +". She will thank us in the end, you know.",
											 "Get lost! Let the gentlemen have some good time.",
											 "This is none of your business, "+ GetSexPhrase("stranger","lass") +". We will just have some fun, and that's all!");
				link.l1 = LinkRandPhrase("I will not allow this!","Abandon your evil plans this instant!","I will not tolerate any violence!");
				link.l1.go = "Node_Fight";
				link.l2 = RandPhraseSimple("I got it, leaving. Sorry to disturb.","I dare not to disturb you. Sorry to bother you.");
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
			}
			if(pchar.GenQuest.EncGirl == "Begin_2")
			{
				if(sti(pchar.rank) < 10)
				{
					dialog.text = LinkRandPhrase("Go your own way, "+ GetSexPhrase("buddy","lass") +". She will thank us in the end, you know.",
											 "Get lost! Let the gentlemen have some good time.",
											 "This is none of your business, "+ GetSexPhrase("stranger","lass") +". We will just have some fun, and that's all!!");
					link.l1 = LinkRandPhrase("I will not allow this!","Abandon your evil plans this instant!","I will not tolerate any violence!");
					link.l1.go = "Node_Fight";
					link.l2 = RandPhraseSimple("I got it, leaving. Sorry to disturb.","I dare not to disturb you. Sorry to bother you.");
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_11";
				}
				else
				{
					dialog.text = RandPhraseSimple("Hey, "+ GetSexPhrase("stranger","young lady") +", why are you looking for trouble? This girl is a well-known person in the settlement. We have already paid her. But she noticed you and decided to take flight.",
												   "Hey, "+ GetSexPhrase("buddy","lass") +", go your own way and don't interfere with our affairs. We've won this lass in a game of dice, but she was a little bit too quick - we've been chasing her down for an hour.");
					link.l1 = "I don't care - I will not let you harm her!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("Oh, so that's the deal! And I almost did not believe it! So beauty gives...","Ah, well, that's another matter. Well, have fun, if you want.");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}	
			}
			if(pchar.GenQuest.EncGirl == "Begin_3")
			{
				if(sti(pchar.rank) < 20)
				{	
					dialog.text = "Go your own way, "+ GetSexPhrase("good man","young lady") +". We'll figure it out without you.";
					link.l1 = "I will not tolerate any violence!";
					link.l1.go = "Node_5";
					pchar.GenQuest.EncGirl = "Begin_33";
				}
				else
				{
					dialog.text = RandPhraseSimple("Hey, "+ GetSexPhrase("stranger","young lady") +", why are you looking for trouble? This girl is a well-known person in the settlement. We have already paid her. But she noticed you and decided to take flight.",
												   "Hey, "+ GetSexPhrase("buddy","lass") +", go your own way and don't interfere with our affairs. We've won this lass in a game of dice, but she was a little bit too quick - we've been chasing her down for an hour.");
					link.l1 = "I don't care - I will not let you harm her!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("Oh, so that's the deal! And I almost did not believe it! So beauty takes...","Ah, well, that's another matter. Well, have fun, if you want.");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}			
		break;
		
		case "Node_Fight":
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("Well, you've certainly picked not the right time for a walk...","So, you decided to be a hero?") +" Down with h"+ GetSexPhrase("im","er") +", boys!","You "+ GetSexPhrase("slime","filth") +"! You dare to stand in our way?! Cut h"+ GetSexPhrase("im","er") +"!");
			link.l1 = "We've seen more threatening people!";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_3":
			pchar.GenQuest.EncGirl.price = 1100*(rand(4)+5) + 200 * sti(pchar.rank);
			dialog.text = "For your information, she cost us quite a bit! And if you are so noble, you can take her for " + sti(pchar.GenQuest.EncGirl.price) + " pesos."+ GetSexPhrase(" You'll have good time with her, he-he...","") +"";
			if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
			{
				link.l1 = RandPhraseSimple("Here's your money. I am taking her with me.","Stop grinning your teeth. I am taking the girl. Here is your money.");
				link.l1.go = "Node_4";
			}	
			link.l2 = LinkRandPhrase("So, money is what you want? How about cold steel?",
									 "That's good time for you, but look at the girl! She's so frightened!",
									 "Whom are you trying to put on, you scarecrow!");
			link.l2.go = "Node_Fight";
		break;
		
		case "Node_4": 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price))); 
			ChangeCharacterComplexReputation(pchar,"nobility", 7);
			
			sGlobalTemp = "Saved_CangGirl";
			pchar.GenQuest.EncGirl.Ransom = true;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_5":
			dialog.text = "Why do you believe her, in the first place? What violence? She ran away fro home, and we've been sent by our boss to find her.";
			link.l1 = RandPhraseSimple("Well, that's a different story, then. Go chase your runaway.","Oh, I see. Well, keep chasing her, then - and I've got business to do.");
			link.l1.go = "Exit_NoFight";
			link.l2 = RandPhraseSimple("Tell these fairy tales to your grandsons, if you live long enough to have them!","Whom are you trying to put on?!");
			link.l2.go = "Node_6";
			link.l3 = "Here are I myself take her home, so that does not happen too much. Who are her parents?";
			link.l3.go = "Node_7";
		break;
		
		case "Node_6":
			dialog.text = "You are had it coming...";
			link.l1 = "Look who's talking.";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_7":
			sGlobalTemp = "Saved_CangGirl";
			if(pchar.GenQuest.EncGirl.city == "Panama") i = drand(2);
			else	i = drand(3);
			switch (i)
			{
				case 0:
					pchar.GenQuest.EncGirl.FatherNom = "is a store owner";
					pchar.GenQuest.EncGirl.FatherGen = "of a store owner's";
					pchar.GenQuest.EncGirl.Father = "store_keeper";
				break;
				case 1:
					pchar.GenQuest.EncGirl.FatherNom = "serves in the port office";
					pchar.GenQuest.EncGirl.FatherGen = "who serves in the port office";
					pchar.GenQuest.EncGirl.Father = "portman_keeper";
				break;
				case 2:
					pchar.GenQuest.EncGirl.FatherNom = "serves as the prison's commandant";
					pchar.GenQuest.EncGirl.FatherGen = "of a prison's commandant's";
					pchar.GenQuest.EncGirl.Father = "fort_keeper";
				break;
				case 3:
					pchar.GenQuest.EncGirl.FatherNom = "is a shipyard owner";
					pchar.GenQuest.EncGirl.FatherGen = "of a shipyard owner's";
					pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
				break;				
			}
			dialog.text = "Her father - " + pchar.GenQuest.EncGirl.FatherNom + ", in the settlement of " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ". But don't let us down, because he really is a tough guy - he will skin us all alive...";
			link.l1 = "Don't bother. I'll deliver her to him.";
			link.l1.go = "Node_12";
			pchar.GenQuest.EncGirl = "toParents";
		break;
		
		case "Node_12":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, true);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
				sld.lifeDay = 0;
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_8":
			dialog.text = "And so we meet again. Where is your companion?.. Oh, well, I don't need her, if you're here.";
			link.l1 = "Gentlemen, I really think that you had already received just enough money to leave the lass alone.";
			link.l1.go = "Node_9";
		break;
		
		case "Node_9":
			if(drand(1) == 0)
			{	
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;	
			}	
			else
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);	
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;	
			}	
			pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			switch(drand(4))
			{
				case 0:
					sTemp = "a leg";
				break;
				case 1:
					sTemp = "an arm";
				break;
				case 2:
					sTemp = "an ear";
				break;
				case 3:
					sTemp = "a nose";
				break;
				case 4:
					sTemp = "an eye";
				break;
			}
			dialog.text = "What is your money compared to the treasures of " + GetName(pchar.GenQuest.EncGirl.PirateIdx , pchar.GenQuest.EncGirl.PirateName1, NAME_GEN) + "? " +
							"He was so greedy that he didn't marry his own daughter because he wanted to avoid extra expenses�\nBut there is our share in his chests! "+ 
							GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.PirateName2, NAME_NOM) +" has lost at boarding " + sTemp +"! Also what have instead? " + 
							"Pitiful handful of silver? " + GetName(pchar.GenQuest.EncGirl.PirateIdx , pchar.GenQuest.EncGirl.PirateName1, NAME_NOM) + " take all the booty in the hiding place. But now we are not going to give up! Shows where his the chests!";
			link.l1 = "Well, I surely didn't apply for guarding the treasures of your captain, but I cannot show you the place... Because I do not know where is this place.";
			link.l1.go = "Node_10";
		break;
		
		case "Node_10":
			dialog.text = "You lie!!! I can smell the scent of gold coming out of this cave! Show me the place if you don't want to die!";
			link.l1 = "I see that my words failed to convince you. Perhaps, my blade will be more expressive?";
			link.l1.go = "Node_11";
		break;
		
		case "Node_11":
			pchar.GenQuest.EncGirl = "RapersTreasure";
			dialog.text = "You "+ GetSexPhrase("cur","filth") +"! Make way!..";
			link.l1 = "Arrgh!";
			link.l1.go = "exit_fight";
		break;
		
		case "EncGirl_Berglar":
			dialog.text = "Hello, good "+ GetSexPhrase("man","lady") +". We have complaints about you.";
			link.l1 = "Complaints from whom? From that whore?";
			link.l1.go = "EncGirl_Berglar1";
		break;
		
		case "EncGirl_Berglar1":
			dialog.text = "Watch your tongue, okay? I will not allow you to insult my sister! First you molested her in the jungle, then brought her "+ GetSexPhrase("for more indecency","brought me here and robbed me") +".";
			link.l1 = "Hey, buddy - do I really have to listen to all of that?";
			link.l1.go = "EncGirl_Berglar2";
		break;
		
		case "EncGirl_Berglar2":
			pchar.GenQuest.EncGirl.BerglarSum = makeint(sti(pchar.money)/5) + 5000;
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 250000) pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 0)
			{
				dialog.text = "No. A modest sum of just " + sti(pchar.GenQuest.EncGirl.BerglarSum) + " pesos will save you all the trouble.";
				if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.BerglarSum))
				{
					link.l1 = "Well, noble deeds are surely a bit costly these days. Alright, take it...";
					link.l1.go = "EncGirl_Berglar3";
				}	
				link.l2 = "I think it'd be cheaper to make a hole in your belly so that you didn't stand on my way to the exit.";
				link.l2.go = "EncGirl_Berglar4";
			}
			else
			{
				dialog.text = "No. But you'll also turn your pockets inside out, otherwise I'll stab you!";
				link.l1 = "Alright, take it, you scoundrel! But you won't get away with that...";
				link.l1.go = "EncGirl_Berglar3_1";
				link.l2 = "I think it'd be easier to make a hole in your belly so that you didn't stand on my way to the exit.";
				link.l2.go = "EncGirl_Berglar4";				
			}			
		break;
		
		case "EncGirl_Berglar3":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BerglarSum)));
			dialog.text = "Very good. Good riddance.";
			link.l1 = "Good luck.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoom");			
		break;
		
		case "EncGirl_Berglar3_1":
			dialog.text = "Of course I won't, of course... Well, farewell to you, "+ GetSexPhrase("buddy","lass") +"."+ GetSexPhrase(" And keep in mind - you're not that handsome that any girl would have fallen for you the instant she saw you. That will be a lesson to you.","") +"";
			link.l1 = ""+ GetSexPhrase("That's for sure!..","Get lost already!") +"";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");			
		break;
		
		case "EncGirl_Berglar4":
			dialog.text = "You look like "+ GetSexPhrase("such a noble man","such a well brought-up lady") +", why the bad language?";
			link.l1 = "It suits you the most...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_fight");
		break;
		
		case "Node_2":
			dialog.text = "Well, you asked for it! Shall we tickle h"+ GetSexPhrase("im","er") +" with steel, boys?";
			Link.l1 = "Pray before you die!";
			Link.l1.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = "So, you'd like to join or what? "+ GetSexPhrase("Get lost - there's not enough for us","Get lost - one lass is good enough for us") +"!";
			Link.l1 = "Well, I shall not be disturbing you.";
			Link.l1.go = "Exit_NoFight";
			Link.l2 = "I will not allow any violence to happen in my own eyes!";
			Link.l2.go = "Node_2";
		break;				
	}
}
