// ������ ������, �� �� �������� ������
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // ������ � �����
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MainBegin")
			{
				dialog.text = "Well, hello, " + pchar.name + ". Glad to see you alive.";
				link.l1 = "Gaston! Is that you?";
				link.l1.go = "SJ_talk";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetTonzag")
			{
				dialog.text = "Greetings, " + pchar.name + ". I already know about your dealings - John told me everything. I don't even know what to say. I admire you!";
				link.l1 = "It is very pleasant to hear such a praise from you, Hercule!";
				link.l1.go = "SJ_talk_11";
				break;
			}
			dialog.text = "Good afternoon. Do you have business with me?";
			link.l1 = "No. My mistake. I am sorry. Bye. .";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "SJ_talk":
			dialog.text = "You knew me by that name. But my real name is Hercule. Hercule Tonzag.";
			link.l1 = "Holy Lord! I am also glad to see you... I didn't not recognized you in the heat of the fight. You were just in time with your help.";
			link.l1.go = "SJ_talk_1";
		break;
		
		case "SJ_talk_1":
			dialog.text = "Right after your departure I got news that Fleetwood stepped up efforts to protect his house. I suggested there may be a trap behind this or something like that. I had immediately set sail to Antigua on my lugger - and, as you see now, for a good reason.";
			link.l1 = "True. I barely managed to deal with the guards inside the house, but I was too exhausted to go on in the street...";
			link.l1.go = "SJ_talk_2";
		break;
		
		case "SJ_talk_2":
			dialog.text = "After this fight Fleetwood had put a Dutch spy on the wanted list. They thought you were a Dutch spy. He is at inveterate feud with them. The bad thing was that one soldier in the house survived and remembered your face. But, anyway, it is not a problem now. I have finished what you'd started. This soldier will not be able to recognize anybody anymore...";
			link.l1 = "Did you kill him? I see...";
			link.l1.go = "SJ_talk_3";
		break;
		
		case "SJ_talk_3":
			dialog.text = "Yes. While you were lying unconscious at John's place, I injured Fleetwood, but the fucker managed to survive. I struck him blind - threw pepper in his eyes, and then hit him before he had a chance to draw his sword. But this scum wore a hauberk under his uniform - it saved his life. Smart. Now he is staying in bed at home with increased security. It is very unfortunate that he survived.";
			link.l1 = "So, your main task on Antigua was eliminating Fleetwood?";
			link.l1.go = "SJ_talk_4";
		break;
		
		case "SJ_talk_4":
			dialog.text = "Generally, yes. Now it seems undoable, though - the house is always locked up, there are half a dozen of selected guardsmen on duty round the clock, and they allow only his confidant to see him - an old canoneer Charlie nicknamed Knippel.";
			link.l1 = "That's already something...";
			link.l1.go = "SJ_talk_5";
		break;
		
		case "SJ_talk_5":
			dialog.text = "Wait a bit... Are you going to interfere with this affair?";
			link.l1 = "Why not? Don't you need help? You saved me, and I want to help. Plus, I still in a need of coins.";
			link.l1.go = "SJ_talk_6";
		break;
		
		case "SJ_talk_6":
			dialog.text = "Believe me, friend, you will not manage that. You are a fine fellow, a real talent, and the logbook, which you had fetched, helped me to plan an attempt on Fleetwood's life, you did a good job at slicing the guards - but you will never be able to get to Fleetwood now. Even I have no slightest clue how to do it.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "I will think it over. I still have time. It's too bad that my ship was arrested, and I do not have a crew.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "I will think about that. I have time and a ship.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_7":
			dialog.text = "Do not worry about that. When your old tub was placed under arrest, I took all your officers and some of the sailors on board of my lugger. They know that you are alive and agreed to stay in service. And in reward for the journal, I am relinquishing my lugger to you.";
			link.l1 = "Thank you! I will remember that!";
			link.l1.go = "SJ_talk_9";
			pchar.Ship.Type = GenerateShipHand(pchar, SHIP_CAREERLUGGER, 12, 580, 30, 800, 20000, 16.5, 65.5, 1.6);
			pchar.Ship.name = "Twilight";
			SetBaseShipData(pchar);
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
			SetCrewQuantityFull(pchar);
			pchar.Ship.Crew.Morale = 80;
			pchar.Ship.Crew.Exp.Sailors = 90;
			pchar.Ship.Crew.Exp.Cannoners = 70;
			pchar.Ship.Crew.Exp.Soldiers = 70;
			SetCharacterGoods(pchar, GOOD_BALLS, 100);
			SetCharacterGoods(pchar, GOOD_GRAPES, 100);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			SetCharacterGoods(pchar, GOOD_BOMBS, 100);
			SetCharacterGoods(pchar, GOOD_FOOD, 100);
			SetCharacterGoods(pchar, GOOD_POWDER, 300);
			SetCharacterGoods(pchar, GOOD_WEAPON, 60);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 60);
		break;
		
		case "SJ_talk_8":
			AddMoneyToCharacter(pchar, 15000);
			dialog.text = "Yes, I would like to pay you for the journal. 15000 - I do not have more at the moment, unfortunately. We'll settle it up one day. ";
			link.l1 = "No need. This is enough. If not for you, I would not need any money, anyway.";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_9":
			dialog.text = "Alright, " + pchar.name + ", I have to go. I am not going back to Bridgetown yet. Should you really need me - ask John. Good luck!";
			link.l1 = "Good luck, Hercule!";
			link.l1.go = "SJ_talk_10";
		break;
		
		case "SJ_talk_10":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-13");
			pchar.questTemp.HWIC.Self = "HuntFleetwood";
		break;
		
		case "SJ_talk_11":
			dialog.text = "I would like to present you this armour for eliminating Fleetwood. It will protect you in future battles. Let's go see John now. He wants to talk to you and offer you... one interesting affair.";
			link.l1 = "Thank you for the present. Alright, let's go...";
			link.l1.go = "SJ_talk_12";
		break;
		
		case "SJ_talk_12":
			DialogExit();
			GiveItem2Character(pchar, "cirass7");//���� ����
			sld = characterFromId("Merdok");
			LAi_SetOwnerType(sld);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddQuestRecord("Holl_Gambit", "3-35");
		break;
		
		case "Tonzag_hired":
			dialog.text = "I also would like to talk to you, captain. I was going to teach you my trade, but now I see that it is me who should learn from you now. Hire me as an officer on your ship - and you will not regret this.";
			link.l1 = "With pleasure, Hercule! Welcome to the crew!";
			link.l1.go = "Tonzag_hired_1";
			link.l2 = "Hercule, I cannot imagine myself being your superior. Thank you for your offer, but I just cannot see you as my subordinate.";
			link.l2.go = "Tonzag_exit";
		break;
		
		case "Tonzag_hired_1"://������� - � �������
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			npchar.greeting = "tonzag_hire";
			NextDiag.CurrentNode = "tonzag_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			LAi_SetImmortal(npchar, false);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		break;
		
		case "Tonzag_exit":
			dialog.text = "As you say, " + pchar.name + ". See you. Perhaps we will meet again. It's been a pleasure working with you.";
			link.l1 = "Good luck, friend!";
			link.l1.go = "Tonzag_exit_1";
		break;
		
		case "Tonzag_exit_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DialogExit();
		break;
		
		//--> ----------------------------------- ���������� ���� ------------------------------------------
		case "tonzag_officer":
			dialog.text = "I am listening to you, captain. What do you have to say?";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Hercule, I am going to the old Indian city of Tayasal and, which is even more unusual, my way lies through a teleportation statue. Will you join me?";
				Link.l4.go = "tieyasal";
			}
			Link.l1 = "Listen to my order!";
            Link.l1.go = "stay_follow";
			link.l2 = "Nothing at the moment. At ease!";
			link.l2.go = "exit";
			NextDiag.TempNode = "tonzag_officer";
		break;
		
		case "stay_follow":
            dialog.Text = "What are your orders? ?";
            Link.l1 = "Stay here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and don't fall behind!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.bulletNum") && sti(NPChar.chr_ai.bulletNum) > 1)
				{
					Link.l3 = "Change the type of your ammo.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choice of ammunition type:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, sBullet);
			LAi_GunSetUnload(NPChar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Aye!";
            Link.l1 = "At ease.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Aye!";
            Link.l1 = "At ease.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- ���������� ���� ----------------------------------------
	
	// �� ��������
		case "tieyasal":
			dialog.text = "You are lucky son of bitch, captain. I am glad I've joined you back then in John's. May a shark swallow me, if I won't support you in this undertaking!";
			link.l1 = "Thank you, Hercule! I am glad that I was right about you.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "So, when are we departing?";
			link.l1 = "A bit later. Now we should get prepared for the journey.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "23");
			npchar.quest.Tieyasal = "teleport";
		break;
	}
}