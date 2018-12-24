
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;
	ref rColony;
	
	int iTest;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	iTest = FindColony(NPChar.City);
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_GoOut":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //��������� ���� � ���
					break;
    			}
    		}
			DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
			pchar.questTemp.HouseEncTimer = pchar.location;
			pchar.questTemp.HouseEncTimer.Id = npchar.id;
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_close":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //��������� ���� � ���
					break;
    			}
    		}
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------------- ����� ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Alarm is raised in the town. Apparently, it's time for me to take up arms as well...", "Aren't the city guards running after you, by chance? ", "You will find no shelter here - but you may well find several inches of cold steel under your rib!"), 
					LinkRandPhrase("What do you need,"+ GetSexPhrase("scoundrel","rascal") +"?! The city guards have already hit your scent, you won't get far, "+ GetSexPhrase("filthy pirate","stinker") +"!", "Filthy murderer! Guards!!!", "I don't fear you, "+ GetSexPhrase("creep","stinker") +"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("I see you're tired of living...", "So it seems, there is no peaceful live for citizens of " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple("Go to hell!", "Heh, those will be the last few seconds of your life..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "I have warned you. And then you can decide for yourself, if you want to run into trouble.";
					link.l1 = "Heh!";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "What do you need in my house, scoundrel?!";
					link.l1 = LinkRandPhrase("Heh, looks like they know me here, too!", "My fame has just preceded me...", "Hmm, I see.");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("I am glad to welcome you to my home. Do you have business with me?", 
						"What can I do for you?", 
						"Hmm... What can I do for you?",
						"I am sorry, but if you have no business with me, please do not disturb me...", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("No, just looking around, meeting new people...", 
						"No, nothing in particular...",
						"Nothing...", 
						"Fine, as you say.", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("I am sorry, but the night is not the best time for visiting, and therefore I would request that you leave my house at once!", 
						"I have already told you - it's late. Please leave.", 
						"I don't want to appear rude, but I insist that you leave my house at once!",
						"Goddammit, what's going on?! Guards! Thieves!", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Alright, I see...", 
						"Yeah, just a moment...",
						"Alright, just don't get so excited.", 
						"What thieves?! Shut up!", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = "Oh, allow me to introduce myself - " + GetFullName(npchar) + ". We're very happy to have you. In this town, the laws of hospitability are honored.";
			link.l1 = GetFullName(pchar) + ", if you please...";
			link.l1.go = "exit_setOwner";
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("You're "+ GetSexPhrase("a thief, I see! Guards, seize him","a thief, I see! Guards, seize her") +"!!!", "I can't believe it! I turned away for a second - and you're diving into my chest! Stop thief!!!", "Guards! Robbery! Stop thief!!!");
			link.l1 = "Aaaah, devil!!!";
			link.l1.go = "fight";
		break;
		// --------------------------------- ���� ---------------------------------
		case "HouseWoman":
			NextDiag.TempNode = "HouseWoman";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("I am warning you that my husband shall return soon! You'd better leave my house now!", "I don't think that you manage to escape! And be aware that my husband will be home soon!", "My husband will be home soon! You must leave at once!"), 
					LinkRandPhrase("A pity that my husband is not home... Get lost! Now!!!", "Filthy murderer - get out of my house at once! Guards!", ""+ GetSexPhrase("What a scoundrel","What a filth") +"...Soon my husband will return - and he will see what color your blood is!"));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Oh, your husband... I am trembling...", "Heh... You know, pussy, I am not scared of your husband..."), 
					RandPhraseSimple("Shut yup, darling, before I gut you...", "I will stay there for as long as I choose. And you better keep your mouth shut if you know what's good for you..."));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "I have warned you. Get lost or you will regret it!";
					link.l1 = "What a stupid wench...";
					link.l1.go = "exit";
				}
				else
				{					
					dialog.text = "What are you doing in my house, "+ GetSexPhrase("scoundrel","rascal") +"?! If you are not gone in then seconds, I am calling the guards!";
					link.l1 = "What a stupid wench...";
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("I am glad to see you in our house. My name is " + GetFullName(npchar) + ". What can I do for you?", 
						"You still here?", 
						"Hm, excuse me, but don't you think that it is time for you to leave?",
						"I would kindly ask you not to trespass on our hospitality.", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat( GetFullName(pchar) + " at your service. I came here for no particular reason, just to make acquaintance.", 
						"Still here.",
						"Well, that depends...", 
						"Fine.", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Oh my, why are breaking into my house at such a time! You scared me... Please, come visit us tomorrow!", 
						"Please, leave our house!"+ GetSexPhrase("","I am a married woman!") +"", 
						"Please, leave our house!",
						"But what is it done?!", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Don't be afraid, I will not hurt you.", 
						"Alright, just don't get so agitated.",
						"I am leaving.", 
						"What's up?", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseWoman_1":
			dialog.text = "We are always happy to have guests. Just don't stay here for too long,"+ GetSexPhrase(", since I have a lot to do."," since I am a married woman...") +"";
			link.l1 = "Oh, yeah, sure...";
			link.l1.go = "exit_setOwner";
		break;
		case "Woman_FackYou":
			dialog.text = "So that's how it is? I welcomed you as my guest, and you are rummaging through our chests?! Guards!";
			link.l1 = "Shut up, old hag.";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		case "HouseWoman_2":
			dialog.text = "I asked you to leave our house in a friendly way, but you just would not listen! Enough! Help! Guards!";
			link.l1 = "Shut up, you foolish woman! Are you crazy?!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break; 
		//--------------------------------- �������� ---------------------------------		
		case "SkladMan":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("Alarm is raised in the town. Apparently, it's time for me to take up arms as well...", "Aren't the city guards running after you, by chance? ", "You will find no shelter here - but you may well find several inches of cold steel under your rib!"), 
					LinkRandPhrase("What do you need,"+ GetSexPhrase("scoundrel","rascal") +"?! The city guards have already hit your scent, you won't get far, "+ GetSexPhrase("filthy pirate","stinker") +"!", "Filthy murderer! Guards!!!", "I don't fear you, "+ GetSexPhrase("creep","stinker") +"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("I see you're tired of living...", "So it seems, there is no peaceful live for citizens of " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple("Go to hell!", "Heh, those will be the last few seconds of your life..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
				dialog.text = NPCStringReactionRepeat("Welcome! My name is " + GetFullName(npchar) + ". Here, I am in charge, so don't even think of taking anything with you...", 
				"Behave and keep in mind that I am watching.", 
				"As long as you don't peek into the chests, you may stay here. I am bored alone, anyway...",
				RandPhraseSimple("Oh my, I am so bored!", "Goddammit, what to take up?.."), "block", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Alright, don't worry.", 
				"Sure!",
				"I see...", 
				"Yeah, that sounds like a problem.", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
		break;
		
		case "SkladMan1":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("Alarm is raised in the town. Apparently, it's time for me to take up arms as well...", "Aren't the city guards running after you, by chance? ", "You will find no shelter here - but you may well find several inches of cold steel under your rib!"), 
					LinkRandPhrase("What do you need,"+ GetSexPhrase("scoundrel","rascal") +"?! The city guards have already hit your scent, you won't get far, "+ GetSexPhrase("filthy pirate","stinker") +"!", ""+ GetSexPhrase("Filthy","Filthy") +" murderer! Guards!!!", "I don't fear you, "+ GetSexPhrase("creep","stinker") +"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("I see you're tired of living...", "So it seems, there is no peaceful live for citizens of " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple("Go to hell!", "Heh, those will be the last few seconds of your life..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			dialog.text = NPCStringReactionRepeat("Here, I am in charge, so don't even think of taking anything with you...", 
				"Behave and keep in mind that I am watching.", 
				"As long as you don't peek into the chests, you may stay here. I am bored alone, anyway...",
				RandPhraseSimple("Oh my, I am so bored!", "Goddammit, what to take up?.."), "block", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Alright, don't worry.", 
				"Sure!",
				"I see...", 
				"Yeah, that sounds like a problem.", npchar, Dialog.CurrentNode);	
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
			//���������� ����� ����� �� ������ ������������� ��������
			if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard")
			{
				link.l2 = "Listen, buddy, I wanted to talk to you openly.";
				link.l2.go = "ShipyardsMap_1";
				pchar.questTemp.different.ShipyardsMap = "toResult";					
			}
			// ugeen --> ����� ������� ��� ��				
			if(CheckAttribute(NPChar,"Storage"))
			{
				if(!CheckAttribute(NPChar, "Storage.Speak"))
				{
					dialog.text = "I have a tempting offer for you. Perhaps you might be interested in it.";
					link.l7 = "Really? Alright, I am listening.";
					link.l7.go = "storage_rent";
				}
				else
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Take me to the storehouse. I want to see, what condition it is in.";
						link.l7.go = "storage_0";
						link.l8 = "I have decided to vacate the warehouse. I don't need it anymore.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "You have mentioned a storehouse. Is it still vacant?";
							link.l7.go = "storage_01";
						}						
					}
				}		
			// <-- ugeen
			}		
		break;
		
		//--------------------------------- ������ ������ ---------------------------------
		case "storage_rent":
			NPChar.Storage.Speak = true;
			dialog.text = "We have an area suitable as a storehouse? Would you like to rent it for a reasonable price. Just think - you'd have your own storehouse...";
			link.l1 = "A storehouse, you say? Yeah, tempting, indeed... Is it large enough? And how much will you charge for the rent?";
			link.l1.go = "storage_rent1";
		break;
		
		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "It's quite spacious even for a port storehouse - it can hold 50000 centners of cargo. For " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + "  per month I can provide safekeeping of your goods. "+
				"This includes guarding, protection from waterlogging and fighting the rats. What say you? Oh, and confidentiality, too - that goes without saying.";
			link.l1 = "Will do. Can I take a look at it?";	
			link.l1.go = "storage_rent2";
			link.l2 = "That's too much. And I bet it's flooded and infested with rats.";
			link.l2.go = "storage_rent3";		
		break;
		
		case "storage_rent2":
			dialog.text = "Sure, sure. But... I'll need a month's payment in advance. ";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "You are... quite mercenary, I must say. Here's your money - I'll rent this shed.";
				link.l1.go = "storage_11";
			}
			else
			{	
				link.l1 = "You are... quite mercenary, I must say. Alright, I'll fetch the money.";
				link.l1.go = "exit";
			}	
		break;
		
		case "storage_rent3":
			dialog.text = "As you wish. If you change your mind - let me know. And keep in mind, that such a nice storehouse is unlikely to stay vacant for long...";
			link.l1 = "No problem. I'll let you know if I need it.";
			link.l1.go = "exit";
		break;
		
		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "And for the rent, you still owe me  " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "Alright, I'll pay for the rent now.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "I'll come back later.";
					link.l1.go = "exit";
				}
			}		
			else
			{
				dialog.text = "Go ahead.";
				link.l1 = "Thanks.";
				link.l1.go = "storage_2";
			}
			link.l2 = "No, I've changed my mind.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			dialog.text = "No, "+ GetSexPhrase("mister","ma'am") +", still vacant and waiting for you. I knew that you would not turn down my offer in the end.";
			link.l1 = "Very good. I'll rent it.";
			link.l1.go = "storage_1";
			link.l2 = "No, it just came to mind...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "As you should remember, I need a month's payment up front.";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Of course, I remember. Here you go.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Damn it. Alright, I'll fetch the money.";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "Leaving already? What a pity - that's really an excellent place on great terms. I assure you that you won't be getting a deal like this one nowhere in the Caribbean.";
			link.l1 = "I said, I am vacating it. Or do you propose me to pay for storing an air? You may look for another holder.";
			link.l1.go = "storage_4";
			link.l2 = "Nowhere in the Caribbean, you say? Alright, I'll bag it for awhile, then. But the rent cost, I must say, is a bit too high.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "And for the rent, you still owe me " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "Fine.";
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = "Collect your goods, and I will close the storehouse.";
				link.l1 = "Fine.";
				link.l1.go = "storage_6";
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		//--------------------------------- ������ ������ ---------------------------------
		
		case "ShipyardsMap_1":
			dialog.text = "Heh! Alright, let's talk.";
			link.l1 = "I need to get to the shipyard at night, when there's no one around.";
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			if (sti(pchar.questTemp.different.ShipyardsMap.skladFight))
			{
				dialog.text = "Look at you! Hey, guards, we have a thief here!!!";
				link.l1 = "What thief? I just wanted  to talk!";
				link.l1.go = "fight";
				AddCharacterExpToSkill(pchar, "FencingL", 5);
				AddCharacterExpToSkill(pchar, "FencingS", 5);
				AddCharacterExpToSkill(pchar, "FencingH", 5);
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
				dialog.text = "Wow! Look at you, "+ GetSexPhrase("buddy","lass") +". To come to the shipyard's storehouse with such a request!";
				link.l1 = "I need to get to the shipyard itself. I could not care less about your storehouse.";
				link.l1.go = "ShipyardsMap_3";
				AddCharacterExpToSkill(pchar, "Fortune", 10);
			}
		break;
		case "ShipyardsMap_3":
			dialog.text = "But what do you need it for?";
			link.l1 = "There is a need. And I am willing  to pay for it...";
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = "Hmm, that's better... Alright! Slip me " + FindRussianMoneyString(sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000) + ", and I'll be leaving the door to the shipyard open during the following day.";
			link.l1 = "That's too expensive. I'll have to do without it, then...";
			link.l1.go = "exit";
			if (sti(pchar.money) >= (sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000))
			{
				link.l2 = "Alright, I agree. Take your money and do as we agreed.";
				link.l2.go = "ShipyardsMap_5";
			}
		break;
		case "ShipyardsMap_5":
			dialog.text = "Don't bother, it will be done.";
			link.l1 = "I hope so...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000);
			AddQuestRecord("ShipyardsMap", "5");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			//������� close_for_night
			string  sName;
			int location_index = FindLocation(npchar.city + "_town");
    		makearef(arRld, Locations[location_index].reload);
    		Qty = GetAttributesNum(arRld);
    		for (int a=0; a<Qty; a++)
    		{
    			arDis = GetAttributeN(arRld, a);
				sName = arDis.go;
    			if (findsubstr(sName, "_shipyard" , 0) != -1)
    			{
					DeleteAttribute(arDis, "close_for_night");
					break;
    			}
    		}
			LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
			//������ ������ �� ������� close_for_night
			SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;

	}
}
