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
		
		case "DestroyGang_begin":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); 
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
			dialog.text = LinkRandPhrase("Give me all your money "+ GetSexPhrase("buddy","lass") +"! My name is " + GetFullName(npchar) + ", and I am not used to objections...",
				"Now show me your purse, "+ GetSexPhrase("buddy","lass") +", and be quick about it! My name is  " + GetFullName(npchar) + ", and I hope you've heard abut me...",
				"Give me every valuable you possess, I also requisition the contents of your purse. And hurry, patience is not my strongest part. Can't say the same about my blood thirst!");
			Link.l1 = LinkRandPhrase("Heh, so you're that very " + GetFullName(npchar) + ", about whom the local governor " + sTemp + " speaks?",
				"Oh, so you're that very bandit hunted down by the local governor " + sTemp + " ?!", 
				"Glad"+ GetSexPhrase("","�") +" to see you, " + GetFullName(npchar) + ". The local governor, " + sTemp + " was talking about?");
			Link.l1.go = "DestroyGang_1";
		break;		
		case "DestroyGang_1":
			dialog.text = LinkRandPhrase("Yes, I am well-known in these places, he-he... Hold on, aren't you another "+ GetSexPhrase("filthy hound","filthy bitch") +" of the governor whom he is attempting to set on my trail?",
				"The governor is a good friend of mine, that's true. And aren't you, by chance, "+ GetSexPhrase("another hero, sent","another heroine, sent") +" by him after my head?",
				"Friendly' inclination of the governor towards myself is a sure fact, he-he. But how do you know that? Perhaps, he sent you after me?");
			Link.l1 = LinkRandPhrase("Exactly, scoundrel. Prepare to die!", "Aren't you a quick witted one! Alright, time to proceed with your liquidation. Enough talking.", "Yeah, that's me. Draw steel, buddy! Let's see what color your blood is.");
			Link.l1.go = "DestroyGang_ExitFight";	
			Link.l2 = LinkRandPhrase("Oh, nevermind! I have no need of such troubles at all...", "No, no, I am not a hero, by no means...", "No, no, never! I don't need trouble...");
			Link.l2.go = "DestroyGang_2";	
		break;
		case "DestroyGang_2":
			dialog.text = LinkRandPhrase("That's better, "+ GetSexPhrase("buddy","lass") +"...And now get lost!",
				"And that's the right decision. I wish you knew how many heroes I have sent to the afterlife� Fine, less words. Get lost, "+ GetSexPhrase("slimeball","bitch") +"!",
				"Attaboy! A very wise social position - to not interfere in the affairs of others... Alright, get lost already, "+ GetSexPhrase("buddy","lass") +".");
			Link.l1 = "Farewell and best of luck to you...";
			Link.l1.go = "DestroyGang_ExitAfraid";	
		break;

		case "DestroyGang_ExitAfraid":
			pchar.GenQuest.DestroyGang = "Found"; 
			npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
			pchar.money = 0;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar)-1, false, "DestroyGang_SuddenAttack");
			for(i = 1; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;	
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
				LAi_SetImmortal(sld, true);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DestroyGang_SuddenAttack");
			}
			DialogExit();
		break;

		case "DestroyGang_ExitFight":
			for(i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		
		case "ContraPass_abordage":
			dialog.text = "Arghh, you scoundrel! How did you dare to attack my ship?! That will cost you dearly!";
			link.l1 = "On the contrary - I am actually being paid for it. You have one certain man on board, by the name of "+pchar.GenQuest.TakePassenger.Name+". He's the one I need.";
			link.l1.go = "ContraPass_abordage_1";
		break;
		
		case "ContraPass_abordage_1":
			dialog.text = "I knew that this crook will bring trouble upon us... But you will not get me that easily! Defend yourself, filthy pirate!";
			link.l1 = "It's you who needs to think about defense, cur.";
			link.l1.go = "ContraPass_abordage_2";
		break;
		
		case "ContraPass_abordage_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "ContraPass_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Tempsailor":
			dialog.text = "Captain, we have searched the cabins and the hold, as you had ordered. That scoundrel tried to hide, but we have found him.";
			link.l1 = "Excellent! Where is he now?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Manacled, in the hold - as you told us.";
			link.l1 = "Excellent! Now let's get off this old tub. It's time to return. ";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Right away, captain!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			sld = GetCharacter(NPC_GenerateCharacter("ContraPass", "citiz_"+(rand(9)+11), "man", "man", 10, sti(pchar.GenQuest.TakePassenger.Nation), -1, true, "quest"));
			sld.name = pchar.GenQuest.TakePassenger.Name;
			sld.lastname = "";
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.TakePassenger.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
		break;
		
		case "Fugitive_city": 
			pchar.quest.AllMayorsQuests_Late.over = "yes"; 
			dialog.text = "What do you want, sir?";
			link.l1 = "So, so... You are So, so... You are "+pchar.GenQuest.FindFugitive.Name+", aren't you? I am overjoyed to see you...";
			link.l1.go = "Fugitive_city_1";
		break;
		
		case "Fugitive_city_1":
			dialog.text = "Well, that's me, indeed, although your 'joy' seems strange to me, since I've never seen you before... Mind to explain yourself!";
			link.l1 = "But of course. I came from "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity+"Gen")+", by orders of the local governor. I must deliver you to the defined city... Don't try anything stupid, good man, or it will turn bad!";
			link.l1.go = "Fugitive_city_2";
		break;
		
		case "Fugitive_city_2":
			dialog.text = "So, you have found me after all� Sir, listen to me and, perhaps, you will change you mind. Yes, I have deserted from the garrison. But I couldn't watch the degradation of our army!\nI want a peaceful life and I have found such life here, in this village... Leave me alone, tell them that you have failed to find me or that I have escaped with pirates into the open sea. In return I will give you this knapsack of amber. A very valuable item I might add...";
			link.l1 = "Don't even think about bribing me, mister! Surrender your weapon and follow me!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Hmm... Chaos? Quiet and peaceful life? Alright, I guess I can bend to your wish. Where is your amber?";
			link.l2.go = "Fugitive_city_gift";
		break;
		
		case "Fugitive_city_fight":
			dialog.text = "Then unsheathe your blade, mercenary! You won't get me that easily!";
			link.l1 = "Alright, let's see your worth!";
			link.l1.go = "Fugitive_fight_1";
		break;
		
		case "Fugitive_city_gift":
			TakeNItems(pchar, "jewelry8", 50+drand(25));
			TakeNItems(pchar, "jewelry7", 2+drand(5));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received amber");
			dialog.text = "Here... And I do hope that I will never see neither you nor other 'envoys' again.";
			link.l1 = "I am sure that you will not. Farewell, mister!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_gift_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.FindFugitive = "Found"; 
			AddQuestRecord("MayorsQuestsList", "12-4");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity));
		break;
		
		case "Fugitive_fight_1":
			chrDisableReloadToLocation = true;
			DialogExit();
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Fugitive_afterfight":
			dialog.text = "Arrgh! You win, damn you! I surrender...";
			link.l1 = "Watch your tongue, mister! And now your saber, please... Follow me, and no silly tricks!";
			link.l1.go = "Fugitive_afterfight_1";
		break;
		
		case "Fugitive_afterfight_1":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, true);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.FindFugitive.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			pchar.GenQuest.FindFugitive = "Execute"; 
			pchar.quest.FindFugitive1.win_condition.l1 = "location";
			pchar.quest.FindFugitive1.win_condition.l1.location = pchar.GenQuest.FindFugitive.Startcity+"_townhall";
			pchar.quest.FindFugitive1.function = "FindFugitive_inResidence";
			SetFunctionTimerCondition("FindFugitive_Over", 0, 0, 30, false);
		break;
		
		case "Fugitive_shore": 
			pchar.quest.AllMayorsQuests_Late.over = "yes"; 
			dialog.text = "Mister, I am not in the mood to talk to you, so...";
			link.l1 = "Nevertheless, you will have to talk to me. You are "+pchar.GenQuest.FindFugitive.Name+", aren't you? I think you should not deny it.";
			link.l1.go = "Fugitive_shore_1";
		break;
		
		case "Fugitive_shore_1":
			dialog.text = "And I am not going to deny it, that's me. But what do you want?";
			link.l1 = "I need to bring you to "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+", the local governor is dying to see you. No silly tricks, please! Surrender your weapon and follow me!";
			link.l1.go = "Fugitive_shore_2";
		break;
		
		case "Fugitive_shore_2":
			dialog.text = "I see� Sir, before you shoot from the hip let me tell you something. Yes, I have deserted from the garrison. But I had reasons to do so. I can't stay at the service, it is too much for me! I can not!\nI want a peaceful life and I have found such life here, in this village... Leave me alone, tell them that you have failed to find me or that I have escaped with pirates into the open sea. In return I will give you my weekly catch of pearls. That's all I have got.";
			link.l1 = "Don't even think about bribing me, mister! Surrender your weapon and follow me!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Hmm... Are you tired of military service? Alright, I guess I can bend to your wish. Where is your pearl?";
			link.l2.go = "Fugitive_shore_gift";
		break;
		
		case "Fugitive_shore_gift":
			TakeNItems(pchar, "jewelry52", 100+drand(40));
			TakeNItems(pchar, "jewelry53", 400+drand(100));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received pearl");
			dialog.text = "Here... And I do hope that I will never see neither you nor other 'envoys' again.";
			link.l1 = "I am sure that you will not. Farewell, mister!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern": 
			pchar.quest.AllMayorsQuests_Late.over = "yes"; 
			dialog.text = "Ehhh... hic! Mister, I am not looking for company - especially yours. Get lost!";
			link.l1 = "But I am seeking your company, "+pchar.GenQuest.FindFugitive.Name+". And you will tolerate my company in the hold of my ship. We are going to  "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+", to the local governor. He is nearly dying to see you.";
			link.l1.go = "Fugitive_tavern_1";
		break;
		
		case "Fugitive_tavern_1":
			dialog.text = "H-Hic!"+RandSwear()+" So he has chased me down after all! Listen, pal, you don't know the origin� I couldn't stay at the service, I simply could not! I still drink like a fish every evening to forget about that\nLook, let's make a deal. Tell him that you have failed to find me or that I have escaped with pirates into the open sea. In return I will give you all nuggets I found in the local cave. That's all I have got, see, I am giving away everything to you, just to never see "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+"...";
			link.l1 = "Don't even think about bribing me, mister! Surrender your weapon and follow me!";
			link.l1.go = "Fugitive_tavern_fight";
			link.l2 = "Hmm... An unpleasant story? Are you tormented by nightmares or guilty conscience? Alright, I guess I can bend to your wish. Where is your pearl?";
			link.l2.go = "Fugitive_tavern_gift";
		break;
		
		case "Fugitive_tavern_gift":
			TakeNItems(pchar, "jewelry5", 50+drand(30));
			TakeNItems(pchar, "jewelry6", 100+drand(50));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received ingots");
			dialog.text = "Here... And I do hope that I will never see neither you nor other 'envoys' again.";
			link.l1 = "I am sure that you will not. Farewell, mister!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern_fight":
			dialog.text = "Then unsheathe your blade, mercenary! You won't get me that easily!";
			link.l1 = "Alright, let's see your worth!";
			link.l1.go = "Fugitive_fight_2";
		break;
		
		case "Fugitive_fight_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetImmortal(npchar, false);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}

