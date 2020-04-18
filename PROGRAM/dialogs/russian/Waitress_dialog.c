
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			
			if (sti(pchar.rank) > 6 && npchar.location == "PortSpein_tavern" && !CheckAttribute(npchar, "quest.Consumption"))
            {
				dialog.text = "What do you wish, senor? I am sorry I am just... oh...";
				link.l1 = "Why are you so upset, my lady? Tears? What happened?";
				link.l1.go = "Consumption";
				break;
			}
			
			
			
			if (npchar.location == "PortPax_tavern" && CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin")
            {
				PlaySound("VOICE\Russian\Enc_RapersGirl_1.wav");
				dialog.text = "Monsieur! Monsieur, help! Murdering!";
				link.l1 = "Huh? Murdering whom? Where? Is this a joke, my dear?";
				link.l1.go = "FMQP";
				break;
			}
            NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = "I've asked you to get upstairs. Don't stay here and attract an attention.";
					link.l1 = "Fine, I won't set you down...";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = "I am new here so please don't make me too busy. I still can't get used to this work...";
					link.l1 = "And where is the waitress who worked here before you? " + pchar.questTemp.different.FackWaitress.Name + ", looks like...";
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{					
					dialog.text = "Come again, sweetie. We may have fun again. If I would have more free time...";
					link.l1 = "Sure!";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{					
					dialog.text = "I don't know you so don't bother me...";
					link.l1 = "Where is my money?!!";
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
		    switch (Rand(4))
			{
				case 0:
					dialog.text = "Sorry, "+ GetSexPhrase("handsome","pretty one") +", I'm too busy know. It's a good time for the tavern but not for a chat!";
					link.l1 = "...";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = "Please, captain, don't ruin this place! It's a hard work to clean this place.";
					link.l1 = ""+ GetSexPhrase("Hm... I wasn't even going to.","Do I look like a drunkard?") +"";
					link.l1.go = "exit";
				break;

				case 2:
					if (drand(1) == 0) 
					{
						dialog.text = ""+ GetSexPhrase("Oh, captain! Would you like to share a bed with me today? I don't like to boast myself but...","Take your sit, captain. It's always a pleasure to meet a real sea wolf like you.") +"";
						link.l1 = "Too bad that I am in hurry now. Next time!";
						link.l1.go = "exit";
						bool bOk = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")); 
						if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && PChar.sex != "woman" && pchar.GenQuest.EncGirl != "HorseToTavern" && !bOk)
						{
							link.l2 = "My pleasure, pretty thing!";
							link.l2.go = "Love_1";
						}
					}
					else
					{
						dialog.text = "Take your sit, captain. It's always a pleasure to meet a real sea wolf like you.";
						link.l1 = "Thank you, pretty thing.";
						link.l1.go = "exit";
					}
				break;

				case 3:
					dialog.text = "Talk to the master if you want to order something. He is behind the bar rack.";
					link.l1 = "Thanks for an advice.";
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = "If you want to take a rest and fix your health - take yourself a room then. The night stay in the hall won't help you.";
					link.l1 = "My thanks.";
					link.l1.go = "exit";
				break;
			}			
			link.l9 = "I want to ask you a few questions.";
			link.l9.go = "quests";
		break;
		
        case "Love_1":
			dialog.text = "Listen then. Rent a room here in the tavern. Go there and wait for me. I will sneak there a bit later...";
			link.l1 = "Ha! I'll make it done, honey! Looking forward!";
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); 
			
			pchar.questTemp.different.FackWaitress.Kick = dRand(2); 
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); 
			pchar.questTemp.different.FackWaitress.City = npchar.city;
			
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false, "citizen"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";	
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
		break;
		
        case "Love_IDN":
			dialog.text = "She doesn't work here anymore, she has retired. I am sorry, I have got a job to do.";
			link.l1 = "Fine...";
			link.l1.go = "exit";
		break;
		
        case "Love_IDN_1":
			dialog.text = "Listen well, bed hopper. I don't know where are your money! And if you'll keep pushing then I'll call the guards and you'll find yourself in prison!";
			link.l1 = "Fine, no guard is needed... Such a fool...";
			link.l1.go = "Love_IDN_2";
		break;
		
        case "Love_IDN_2":
			dialog.text = "Exactly, such a fool. Next time you'd be smarter and more descent.";
			link.l1 = "I'll try...";
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = "Are you here?";
			link.l1 = "Ugh..";
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = "Feeling bad? Got a headache?";
			link.l1 = "Damn it, where am I?";
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = "Don't you remember? They have robbed you.";
			link.l1 = "What? Oh.. My head... Who would dare?!";
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = "How should I know? They have come, threatened to kill, checked your wallets and gone. ";
			link.l2 = "Fine, whatever.";
			link.l2.go = "exit";
		break;
		
		
		case "Consumption":
			npchar.quest.Consumption = "true";
			dialog.text = "No, It's nothing, senor... thank you for your kindness but I ... (crying)";
			link.l1 = "Someone have offended you? Relax, pretty one, tell me everything.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "No, no, senor it's nothing. Forgive me for my lack of restraint, it is just... It's my brother, they say that he is dead but don't believe it. I don't know what to believe but I feel with my own heart that he is in great trouble. And I don't have anyone but Angelo after our parents have... (crying)";
			link.l1 = "I ask you to calm down, please. What happened to your brother?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "Senor... please understand me, but why should such a solid captain care about an ordinary and modest girl from the tavern? I don't even have a thing to promise you for your help... ";
			link.l1 = "Actually, you are right. Unselfishness is not for me, so be strong, we all loose our relatives. C'est la vie as we say in France...";
			link.l1.go = "exit";
			link.l2 = "Woman can always find a way to thank a man.... Ha-ha. Just stop crying and tell me about your problem.";
			link.l2.go = "Consumption_3_1";
			link.l3 = "Young senora, aren't' you informed that our Church teaches us to help each other? I'll try to help you if I will be able to do that of course.";
			link.l3.go = "Consumption_3_2";
		break;
		
		case "Consumption_3_1":
			if(sti(pchar.reputation.nobility) > 36)
			{
				dialog.text = "Was it a hint? Excuse me, it was my mistake to talk with you! Farewell 'caballero'.";
				link.l1 = "As you wish, sweetie.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Well then... At least you are honest in your wishes. I promise that if you'll find Angelo or tell me what really happened to him, you will get what you ask for my brother...";
				link.l1 = "Dear senora, it's a pleasure to do business with you... Now let's get straight to your brother's story.";
				link.l1.go = "Consumption_4";
				npchar.quest.Consumption.sex = "true";
			}
		break;
		
		case "Consumption_3_2":
			dialog.text = "Are you kidding me? Do you really want to help me for free?";
			link.l1 = "Only the bad man wouldn't help a crying girl. Don't worry, I really want to help you. What exactly happened to Angelo?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Very well, senor. My brother, he... oh, it's not easy to hold tears for me, I'm so sorry... We were really poor because of my... modesty at work perhaps and Angelo has gone to the locals. He thought that his small fishing boat will make more coins carrying something in avoid of customs.";
			link.l1 = "To put it in simpler words, your brother became a smuggler, right?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "No, senor, you don't understand... he is not like that! He has done it for me! To save me from making money on the side here... you know what I mean. We were indebted and he has done it for my honor. And then... he was caught. It would be fine, I have even borrowed more money to pay his fine... But they said that he is dead.";
			link.l1 = "They said? Who said? And why do you trust them? He died in a prison?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Yes. When I brought money to pay his fine the commandant told me that Angelo died of consumption. Just think - he got there in a good health and he died two weeks later right in those chambers. They... they didn't even allow me to see the body. They said that they bury prisoners right at the bay near the fort to avoid an epidemic.";
			link.l1 = "An epidemic? Sounds very true. Do you just don't want to believe in it or you've got more serious reasons?";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			dialog.text = "No� not! (weeping) I know it sounds stupid, but I am sure that I would know if he died. See, Angelo was always strong, tough - a real sailor. But there is one more thing\nMy granddad died of consumption when I was a kid and he, an old man, had been fighting it for years. I know it works, consumption doesn't kill people in days, trust me!";
			link.l1 = "Hm... You've made me hesitated too, something is very wrong here. I can't promise you a thing but I'll try to learn more.";
			link.l1.go = "Consumption_8";
		break;
		
		case "Consumption_8":
			dialog.text = "Even a simple promise is much more than I was counting on! You are so kind, senor! I will be waiting here!";
			link.l1 = "Youth! So inconstant.. Give me my hand back, beauty, and I'll go on search.";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			DialogExit();
			npchar.dialog.filename = "Quest\LineMiniQuests\Consumption.c";
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Consumption = "begin";
			AddQuestRecord("Consumption", "1");
		break;
		
		
		
		case "FMQP":
			dialog.text = "No, no jokes! Upstairs! Two thugs are murdering a noble gentleman! Help him captain, you are the only armed man here!";
			link.l1 = "Run outside, call the guards! I am going upstairs!!";
			link.l1.go = "FMQP_1";
			link.l2 = "My dear, you must have taken me for a guard. Call patrol in case of murder.";
			link.l2.go = "FMQP_exit";
		break;
		
		case "FMQP_exit":
			dialog.text = "A-ah, guards! Help me!";
			link.l1 = "...";
			link.l1.go = "FMQP_exit_1";
		break;
		
		case "FMQP_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
			LocatorReloadEnterDisable("Portpax_town", "reload4_back", true);
			SetFunctionTimerCondition("FMQP_Remove", 0, 0, 1, false);
		break;
		
		case "FMQP_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			pchar.quest.FMQP_room.win_condition.l1 = "locator";
			pchar.quest.FMQP_room.win_condition.l1.location = "Portpax_tavern";
			pchar.quest.FMQP_room.win_condition.l1.locator_group = "reload";
			pchar.quest.FMQP_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.FMQP_room.function = "FMQP_InRoom";
		break;
	}
}
