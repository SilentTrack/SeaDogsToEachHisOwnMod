// ������� ������ - ����� ����-������ � ��������� ������
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
			dialog.text = "Want something?";
			link.l1 = "No, it's nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "baker":
			dialog.text = "Thank you, captain! I can't even imagine what would I do without you...";
			link.l1 = "I can imagine. You'd died of starvation or ended up in stomachs of savages from Dominica. But you have got a chance to repay me.";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "How can I help you, captain?";
			link.l1 = "I want to know more about one man. He is our common friend so to speak. A very close friend of yours actually. I mean captain Butcher. Yes, the one you hanged twenty years ago. Jesus, why are you so pale? Do you want some rum?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "Are... are you from him?";
			link.l1 = "Nonsense! How can I be 'from him' if he is dead! I am interested more not in Butcher himself but in the things he has left. Letters, paper. Perhaps something was in his pockets... Wait! I don't get it. Do you really think that Butcher is alive? You have executed him yourself!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			dialog.text = "Fuh! You don't know a thing. It means that you are not from Butcher as I thought...";
			link.l1 = "Well, well. It just getting more interesting. It seems that Henry had all reasons to be scared of Butcher and that's why he died because of heart attack... Is Butcher alive?";
			link.l1.go = "baker_4";
		break;
		
		case "baker_4":
			dialog.text = "He is, captain... And they are looking for me.";
			link.l1 = "Raymond, they have told me that you are not a stupid man. Don't try to play games with me. You are safe here despite of any threat. Tell me everything you know and I will think how to help you. Perhaps we share a common enemy. Let's start with Butcher.";
			link.l1.go = "baker_5";
		break;
		
		case "baker_5":
			dialog.text = "He is alive, but his name is different now! His men came to me at the night of execution. Jackman and another man with some odd nickname. As far as I remember it was the 'Drowned man'.";
			link.l1 = "Hangman. Henry the Hangman.";
			link.l1.go = "baker_6";
		break;
		
		case "baker_6":
			dialog.text = "Right! They said that I'll die in the most painful way if I won't save their captain. So I had to frame up the execution with a special equipment I have created in my free time. Such construction of belts and clumps can allocate the body's weight\nAll you have to do is link it with a secret hook in the loop. The 'corpse' must play it's role well though. I have to say that Lawrence's acting was most believable, he did everything right, but refused to piss himself, because of...";
			link.l1 = "Did you just call Butcher Laurence?";
			link.l1.go = "baker_7";
		break;
		
		case "baker_7":
			dialog.text = "That is his true name. I told you that he is called Lawrence Beltrope. I have been restless since he returned back to the Caribbean a year ago. And when I found out that some grumpy people are looking for me�\nI have even written a confession for the authorities just in case. I am keeping it with me all the time and I am too afraid to give it away. They might think that I was a willing abettor. Please, let me stay in your crew. I swear, I am an excellent physician and can help you a lot.";
			link.l1 = "Fine. And what about Butcher's... eh, Beltrope's things? Isn't he relative to Thomas Beltrope?";
			link.l1.go = "baker_8";
		break;
		
		case "baker_8":
			dialog.text = "No clue. Don't have anything special left from Beltrope himself. But I will give you everything I have got, you are free to do whatever you want with this. All papers related to the subject are in my bag. I saved everything just in case and keep it close to myself\nHere, take a look... this is the legend of captain Butcher, this is my confession... These are things belonged to Joshua Leadbeater...";
			link.l1 = "Stop! Leadbeater? Who is that?";
			link.l1.go = "baker_9";
		break;
		
		case "baker_9":
			dialog.text = "Oh! It was a very special man. The one who chased down Butcher himself. The people remembered him as the 'masked man'. He was murdered shortly after the Butcher's execution. They slit his throat with a shark's tooth! He must had been suffering\nI wish you saw his face under a mask! Nothing but meat! He had this journal paper in his pocket. This must be writings of Jessica Rose. Creepy story! Read it, it will make things much more understandable\nAnd this is the tooth itself. Can you see the letters? S.D. Whatever they mean. There are also some bloodstains left.";
			link.l1 = "Enough! I need to read everything carefully and sleep on it. And you will be my passenger or the ship doctor until I deal with all of this. You can breath freely, Raymond, you are safe here.";
			link.l1.go = "baker_10";
		break;
		
		case "baker_10":
			DialogExit();
			sld = characterFromId("Baker_Cap");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
			//sld.ship.hp = 0;
			//sld.SinkTenPercent = true;
			bQuestDisableMapEnter = false;
			GiveItem2Character(pchar, "shark_teeth");
			GiveItem2Character(pchar, "letter_jess");
			GiveItem2Character(pchar, "letter_baker"); // ��������� �������
			ChangeItemDescribe("letter_baker", "itmdescr_letter_baker"); // Addon-2016 Jason
			AddQuestRecordInfo("Legend_CapBucher", "1");
			AddQuestRecordInfo("Letter_jess", "1");
			AddQuestRecord("Shadows", "5");
			pchar.questTemp.Saga.Shadows = "islatesoro";
			// � �������
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true; //�� �������� ����
			npchar.CompanionDisable = true; //������ � ����������
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Baker_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddCharacterExpToSkill(pchar, "Sailing", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		//--> ----------------------------------- ���������� ���� ------------------------------------------
		case "Baker_officer":
			dialog.text = "Yes, captain?";
			Link.l1 = "Listen to my order!";
            Link.l1.go = "stay_follow";
			link.l2 = "It's nothing. Dismissed!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Baker_officer";
		break;
		
		case "stay_follow":
            dialog.Text = "Orders?";
            Link.l1 = "Stand here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and keep up!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.bulletNum") && sti(NPChar.chr_ai.bulletNum) > 1)
				{
					Link.l3 = "Change the type of ammo for your firearms.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choosing the type of ammo:";
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
            dialog.Text = "There is change of disposition!";
            Link.l1 = "Dismissed.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "There is change of disposition!";
            Link.l1 = "Dismissed.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- ���������� ���� ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}