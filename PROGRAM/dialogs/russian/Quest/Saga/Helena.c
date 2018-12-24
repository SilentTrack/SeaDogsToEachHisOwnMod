// ���� ��� ����� - ������������ ������ � ������
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
		
		case "After_boarding":
			dialog.text = "Thanks for you help, captain!";
			link.l1 = "Hm... You are even more beautiful than I imagined!";
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = "To hell with my beauty! It nearly got me killed. He wouldn't let me leave the corvette alive, because I know too much about the bastard. Yesterday he told me that he is tired of waiting and going to get my favour against my will\nSo you have shown a perfect timing, captain! Well met. My name is Helen McArthur. My dad used to call me Rumba for my cheerful temper, so that's how they call me now.";
			link.l1 = "Well and my name is "+GetFullName(pchar)+". I have been looking for you across all of archipelago for several days because miss Gladys asked me to do so.";
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = "How is she?";
			link.l1 = "She really worries about you. Anyway, soon you will see her, we are sailing to Blueweld now.";
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = "To be honest, "+pchar.name+", I'd like to have some meal and a nap. I am so tired due to all of these days I have spent on the ship of that monster...";
			link.l1 = "No problem, Helen. I will order to serve you a meal and prepare a bed for you. Be my guest.";
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//�� ������ �����
			bQuestDisableMapEnter = false;//������� �����
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = "My captain, I thank you again from the bottom of my heart for my rescue. You must visit me and my mother. Our house is not far from here. Here it is, on the left from the pier. And know, "+pchar.name+", I will never forgive you if you'll disappear without saying goodbye, know that!";
			link.l1 = "Sure, I will visit you!";
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // ������� ������� ��������
			pchar.questTemp.Saga = "svenson";//���� � ��������
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//������� ������� ����
			// ������� ����� �� ������ � ������
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = "Ah, there you are, my captain! I am so glad, "+pchar.name+", that you have finally decided to visit me. I have got a lot to tell you.";
			link.l1 = "We will delay this conversation a bit. I need to get some more information before I am able to answer your questions. And now I ask you to don't show yourself at the streets. I hope that your waiting will not last long. Trust me and wait.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
		break;
		
		case "Helena_hire":
			dialog.text = "Ah, there you are, my captain! Your eyes tell me that you have got news for me!";
			link.l1 = "Svensson told me that you are really eager to become my officer. I appreciate your wish, Gladys mentioned that you have missed the sea. Welcome to my crew, officer Helen McArthur!";
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = "Svensson told me that you are really eager to become my officer. I appreciate your wish, Gladys mentioned that you have missed the sea. Welcome to my crew, officer Helen Sharp!";
			link.l2.go = "Helena_hire_2";
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			dialog.text = "Aye-aye, my captain! But know that I am a proud girl, I can stand up for myself and I won't tolerate any liberties.";
			link.l1 = "Don't worry, there is an order on my ship. We shall stay professional. Besides, I want you to know something extra...";
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = "And what is it?";
			link.l1 = "Jan Svensson and I have found out that you have got succession to Isla Tesoro. Yes, yes, it is true though it seems impossible. I have got a half of the map which can prove your rights. It won't be easy, but me and mister Svensson will do our best to help you to become a rightful ruler of the island.";
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = ""+pchar.name+", are you serious? No, you are kidding the poor girl! How can I have rights to the whole island?";
			link.l1 = "I am absolutely serious, Helen. And what is more, I am going to help you to arrange your life. And let's sail now!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = "What did you say? Helen Sharp? Why Sharp?";
			link.l1 = "Helen, you are a daughter of Beatrice Sharp and an heir presumptive. This is a half of the map which had been kept by Gladys for all last years. It's an evidence of your rights to Isla Tesoro. It won't be easy, but me and mister Svensson will do our best to help you to become a rightful heir of your grandfather.";
			link.l1.go = "Helena_hire_3";
		break;
		
		case "Helena_hire_3":
			dialog.text = "Ah... My poor mother! I hope to find her grave one day and take care about it. But... wait! Impossible!";
			link.l1 = "What is it, Helen?";
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = "The Gypsy's prophecy has just come true... I understand it now.";
			link.l1 = "What prophecy? What are you talking about?";
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+pchar.name+", you might call me naive, but I will share it with you anyway. Several years ago a gypsy told me that my fate is in the hands of the man who won't take the widow's coin,  who will return the dead man's gold and who will name the mother\nI thought that it was a nonsense back then, but somehow you've managed to fulfil every part of the prophecy, you couldn't know about before!";
			link.l1 = "A fate, you say... Well, perhaps you are right. I'll do my best to don't disappoint you and we shall look for your mother's grave together. And for now... Officer Helen Sharp! Get yourself ready and don't be late!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = "Aye-aye, captain!";
			link.l1 = "...";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//������� �������
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//������� ������ �� ������
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2+rand(2), false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		//-->  ������������ �� ������� ��������� � ��������� ���������
		case "sea_bomb":
			dialog.text = ""+pchar.name+"! I have got an idea...";
			link.l1 = ""+npchar.name+"? It's not safe here and I have ordered you to stay on the ship...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+", there are too much gunpowder in this old tub so if it blows up then the whole island will fly sky high. There is no difference in where to stay now. Listen to me!";
			link.l1 = "So? What did you want to tell me?";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "The corvette and the frigate. They believe that we are their own... Knive. This could be an opportunity for us. Let's take a few barrels of gunpowder, a fuse and sail to the ships\nAfter they let us close, we light the fuse, drop the barrel and sail away as fast as we can. And then we shall watch a spectacular explosion... What say you?";
			link.l1 = "Tricky! Though, your plan might work... Only in case they won't recognize us.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Let's just risk it, "+pchar.name+"? It won't be easy to fight two ships at once but we have got a chance...";
			link.l1 = "Fine. We will do that! Lads! Take three barrels with gunpowder! And we are going to get away from here! You are very imaginative, "+npchar.name+"... I would have never come to this idea myself.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = "Yes, sure. What is the matter?";
			link.l1 = "There is a Jackman's ship at Sabo-Matila Cove, heavy frigate Centurion. This ship was a property of Hawkes, besides there must be important items and documents in Jackman's cabin... anyway, we must board it.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "I see. And how are you going to do that on our polacre? They have more men and cannons.";
			link.l1 = "You are right. Jackman has at least twice more men than we have and all of them are perfectly skilled -  selected mercenaries. It would be madness to attack them without any preparatory bombardment. The protracted fighting is not the best option too. So I've been thinking about what to do with that.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = "You won't believe, "+pchar.name+", but I have an idea! They haven't recognized us as an enemy yet like those two idiots back at Turks... We can repeat our trick...";
			link.l1 = "Helen, I have just told you that we must board the frigate, sinking it is not an option.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "I know that, "+pchar.name+". We will not sink her. Listen, we are going to take a few empty rum barrels and grape shot. Short fuse. Then we will come close to their frigate and throw barrels with our fire rum at their deck.";
			link.l1 = "Ha! You think that it is going to work?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "And why not? Their boards are higher than ours but two men will be able to throw a barrel easily. We'll shout them - 'catch some rum from the Knave'! Barrels will explode even before they would start thinking.";
			link.l1 = "The grape shot will spread and eliminate everybody around the explosion... Damn, it sounds tempting. There are hordes of mercenaries walking around at the deck! They are the main threat.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Let's throw five barrels at different places. "+pchar.name+", we have got a great advantage - a surprise. They don't suspect of anything! And then we will immediately sail away from them before they have a chance to board us.";
			link.l1 = "Well, let's try. They must not identify us before we throw barrels... Damn it, it wont' be easy to get close to them. Jackman is not that idiotic like Vampire was.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Let's risk it, "+pchar.name+"! It won't get worse anyway.";
			link.l1 = "It won't, that is for sure... Prepare the fougasses and get ready to fight!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//<--  ������������ �� ������� ���������
		
	// --> �������� �� ������ ����
		case "result":
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // �� ������
			{
				dialog.text = "Well, my captain... It is time for us to say goodbye to each other. My service is ended and it's time to get used to a role of the mistress of Isla Tesoro. I hope that I will be a worthy successor of my uncle. Thank you for your help.";
				link.l1 = "Sure, it's a pity to part with you, but there is nothing I can do. You have got more important things to do than to serve on my ship.";
				link.l1.go = "result_1";
			}
			else
			{
				dialog.text = "It's so strange, "+pchar.name+"! I have just become an owner of the whole island but I don't feel myself as a mistress of Isla Tesoro... I suppose that a new head of the Brethren will manage the colony better than I would. The rent will be enough for me.";
				link.l1 = "Hm. Are you sure, Helen? Think about it, you own the whole island!";
				link.l1.go = "result_9";
			}
		break;
		
		case "result_1":
			dialog.text = "You are right... I was able to collect some gold while sailing on your ship. Take it and don't even try to reject my offer - I don't want to be in your debt.";
			link.l1 = "Hm. Actually...";
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = "I know what are you going to say. Sure, you help costs much more than that chest with coins. But this is almost all I have got in my possesion right now and I have to repay you. Take it, if you don't take it yourself I will leave it in your cabin.";
			link.l1 = "Are you going to sail on your own now? Perhaps I could take you to Isla Tesoro?";
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			Log_Info("You have received a chest with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "No need for that, "+pchar.name+". I will get to the island myself. I have got some cash on me, it will suffice for a while... I am sure that the mistress of Isla Tesoro doesn't need to worry about an income.";
			link.l1 = "Whatever you say. I wish you luck in your new life.";
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = "Thanks. But that is not all I wanted to say. I have found my father again, though it was a bit strange. He has basically paid with his good name of English nobleman for my inheritance and that bothers me. They have declared a hunt for his head and I don't want you, "+pchar.name+", to participate in it.";
			link.l1 = "Come to your senses, Helen! He is a bandit and a pirate!";
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = "Pirate? And who the fuck are you? He is my father and that is the most important! And I, the daughter of a bandit and a pirate, don't give a damn what does the English justice think of him. If you try to harm my father in any way, I will forget everything good you have done to me, know that. Consider this as a warning.";
			link.l1 = "Is that so? Actually, girl, you'd better be more polite. I didn't notice any complains from you about my pirate's attitude while I was saving your pretty ass from the hands of Donovan!";
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = "I am sorry. I have gone into a passion. But still, I'd like to stay your friend which would be impossible if you play against my father.";
			link.l1 = "Understood. But don't ever dare to threat me, Helen... Beltrope. You had to come to understanding, while saving on my ship, that I don't fear anyone and anything. I won't be scared of you, trust me. Farewell now. Nevertheless, I wish you luck.";
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = "Thanks. Perhaps we will meet again, "+pchar.name+"...";
			link.l1 = "And why not? I will visit Isla Tesoro more than once in future. See you there... Bye, Helen!";
			link.l1.go = "result_8";
		break;
		
		case "result_8": // ���� ������, �� �� �� ��������
			DialogExit();
			RemovePassenger(pchar, npchar);
			chrDisableReloadToLocation = true;//������� �������
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
		break;
		
		case "result_9": // ��� ��� - �������� ������, ���� ����� ����� ���� - �������, ����� ������� �����
			dialog.text = "I am sure. "+pchar.name+", I'd like to stay on your ship if you let me. To stay with you...";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "(choose Mary) Helen! It looks like you don't understand. All your future is secured now and there is nothing for you to worry about. And I have got a war, political intrigues and the total uncertainty ahead of me. You must to arrange a life of your own, there is no room for such an adventurer like myself in it.";
				link.l1.go = "result_10";
				link.l2 = "(choose Helen) It's more than I could hope for, Helen. Of course, I don't want to loose you, but perhaps it will better for you to go to Isla Tesoro. Who knows where will my fate lead me to. I have got a war, political intrigues and the total uncertainty ahead of me.";
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = "It's more than I can hope for, Helen. Of course I don't want to loose you but perhaps it will better for you to go to Isla Tesoro. Who knows where will my fate lead me to. I have got a war, political intrigues and the total uncertainty ahead of me.";
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+pchar.name+"! Don't lie to me. You just don't want to... Tell me, who is she? That ginger girl from the Island of Abandoned Ships? Am I right?";
			link.l1 = "Helen! It is you who I carry about in first place! How don't you understand that?!";
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = "I knew that... And how was she able to charm you, huh? Is she really that good? Eh, "+pchar.name+"... Well, it's your decision, I have nothing left, but to go to my island. I won't stand between you two\nAnyways, thank you for everything you've done for me. You are the best man I've ever met. I hope that we shall stay friends?";
			link.l1 = "Sure... Helen, we will meet several times again on Isla Tesoro. Do you want me to take you there?";
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = "No need in that. I will buy a new ship. I have collected the sum enough to buy and to equip a schooner while serving under your command. I will sail on my 'Rainbow' again.";
			link.l1 = "I am really glad, Helen, that you were so... practical. But sailing on a schooner doesn't suit to the mistress of Isla Tesoro. Soon, I believe, you will get a frigate to yourself.";
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = "Perhaps, "+pchar.name+". Fine. I will go to the shipyard but at first... kiss me goodbye. Please...";
			link.l1 = "Helen...";
			link.l1.go = "result_14";
		break;
		
		case "result_14": // ���������� �������
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //������ �����
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 12.0);
			pchar.questTemp.LSC.Mary = "return"; // � ����
		break;
		
		case "result_15":
			dialog.text = "My fate has become your fate since we met. Don't you understand that? "+pchar.name+"? I will follow you at the back of beyond!";
			link.l1 = "And what of your father? Laurence Beltrope? He has become my enemy...";
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = "My father is Sean McArthur. I loved him and mourned the loss of him. He was my only father. And that pirate... I don't even want to talk about him.";
			link.l1 = "Helen... Dear Helen!..";
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+", I have always wanted to tell you that you are incredible, you are the best! You have done so much to me that I will never be able to repay you. I want to stay with you. Forever. I will marry you if you want... I love you.";
			link.l1 = "We shall be together. I promise!"; // � ���� �� �� ������ �������� :)
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+pchar.name+", dear... Embrace me! I have been waiting for this moment for too long!";
			link.l1 = "Helen, my girl...";
			link.l1.go = "result_19";
		break;
		
		case "result_19": // ��������-�����
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			bDisableCharacterMenu = true;//������� ����������
			InterfaceStates.Buttons.Save.enable = false;//��������� �����������
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			// DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
			pchar.questTemp.LSC.Mary = "return";
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! That was... incredible! I don't want to go anywhere else... Let's stay here until morning. The world can wait!";
			link.l1 = "We'll let it wait, Helen!";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // ����������, ��� ���� - ���� ��������
		break;
		
	// -------------------------------------------- ������� ���� ------------------------------------
		case "failcenturion":
			dialog.text = "Captain! Jackman is eliminated... So it seems that my family is safe, isn't it?";
			link.l1 = "Yes, Helen, it is safe. But 'Centurion' was sunk and so were all documents and things which could help us to find your mother's grave and prove your rights to claim Isla Tesoro... Eh... Now I will have to storm Tortuga for my own...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = ""+pchar.name+", don't worry to much. There is nothing we can do now. Don't worry about me either, I will live fine without that island. Thank you for you've done for me!";
			link.l1 = "It sounds like you are going to... leave me, right?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Yes, my captain. I was able to collect enough money to buy and to equip a schooner. I will sail on my 'Rainbow' again. We will meet again at Blueweld, won't we? I am going back home.";
			link.l1 = "Well... good luck, Helen!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // � ����
			}
		break;
		
		case "late_l1":
			dialog.text = "Well, my captain... It seems that we have failed. Farewell. I am going back home. I have earned enough money under your command to buy a new schooner for myself so we will meet again at the sea!";
			link.l1 = "Good luck, Helen. I am sorry for all of that. Farewell.";
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = "Captain! Jackman is eliminated... So it seems that my family is safe, isn't it?";
			link.l1 = "Yes, Helen, it is safe. But I am not happy, I have lost too much time and Isla Tesoro is now the English colony. You were left without any inheritance, so I'll have to storm Tortuga myself...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+", what did lawyer tell to you?";
			link.l1 = "Eh! I have lost too much time and Isla Tesoro is now the English colony. You were left without any inheritance, so I'll have to storm Tortuga myself...";
			link.l1.go = "failcenturion_1";
		break;
	// <-- ������� ����
		
		// ���� - ���� ����������� �� ������ (������ �����, � ��� �� ������? :)) � ���� �� ������� �����
		case "cabin_sex":
			if (drand(4) == 0) // ����������� ������ 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", I am not feeling well today. Don't feel bad, please. Let's don't do it today...",""+pchar.name+", darling, I have been so tired for the last few days. To be honest, I only want to sleep. Forgive me. Let's do it another time.");
				link.l1 = RandPhraseSimple("Fine...","I am fine. Whatever you say...");
				link.l1.go = "sex_exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", I gladly approve your idea! Let's go!",""+pchar.name+", sure, no questions asked! Let's go!");
				link.l1 = RandPhraseSimple("You are my good girl...","You are so charming, Helen...");
				link.l1.go = "cabin_sex_go";
			}
		break;
		
		case "sex_exit":
			DialogExit();
			npchar.quest.daily_sex = true;
			SetFunctionTimerCondition("Helena_SexReady", 0, 0, 1, false);
		break;
		
		case "cabin_sex_go":
			DialogExit();
			chrDisableReloadToLocation = true;//������� �������
			DoQuestCheckDelay("Helena_LoveSex", 1.0);
			NextDiag.CurrentNode = "sex_after";
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("It was great, "+pchar.name+"!..","You were great as always, darling...");
			link.l1 = RandPhraseSimple("I am glad that you were satisfied...","It is always good to be with you, Helen...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//������� �������
			npchar.quest.daily_sex = true;
			SetFunctionTimerCondition("Helena_SexReady", 0, 0, 1, false);
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", I always glad to... But it's not the right time now - we have to catch that scum Thibaut until he escaped.";
				link.l1 = "You are right as always, my girl...";
				link.l1.go = "exit";
				break;
			}
			if (drand(4) == 0) // ����������� ������ 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", I am not feeling well today. Don't feel hurt, please. Let's don't do it today...",""+pchar.name+", darling, I have been so tired for the last few days. To be honest, I only want to sleep. Forgive me. Let's do it another time.");
				link.l1 = RandPhraseSimple("Fine...","I am fine. Whatever you say...");
				link.l1.go = "sex_exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", I gladly approve your idea! Let's go!",""+pchar.name+", sure, no questions asked! Let's go!");
				link.l1 = RandPhraseSimple("You are my good girl...","You are so charming, Helen...");
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			DoQuestCheckDelay("Helena_LoveSex", 1.5);
			NextDiag.CurrentNode = "sex_after";
		break;
		
		//--> ----------------------------------- ���������� ���� ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Yes, "+pchar.name+"?","Yes, my captain?","I am listening, "+pchar.name+"...");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Helen, I am going to visit the old Indian city Tayasal. I won't lie to you: this trip is very dangerous and even more - it includes teleportation through the idol. Will you... follow me?";
				Link.l4.go = "tieyasal";
			}
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Helen, I need your advice.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Helen, I have got an order for you...";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex"))
			{
				Link.l2 = RandPhraseSimple("Helen, let's stay in the cabin together alone... for a few hours? Are you okay with that?","Dear, let's spend next few hours tete-a-tete? Do you like this idea?");
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && !CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				Link.l2 = RandPhraseSimple("Helen, why won't we take a room and stay there in private... for a next few hours? How do you feel about that?","Dear, let's spend next few hours tete-a-tete? We'll take a room... Will you stay?");
				Link.l2.go = "room_sex";
			}
			link.l9 = "It's nothing so far, Helen.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
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
            dialog.Text = "At once, captain!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "At once, captain!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- ���������� ���� ----------------------------------------
		
		// --> ��� �� ��������
		case "terrapin_grot":
			dialog.text = "There you are! I have barely found you... That was something, my captain! I have never seen such a roof run and a jump from such a breathtaking height! My heart was ready to explode! One day you will kill me with these tricks of yours, dear... Oh, ain't you alone here? Who is that girl?";
			link.l1 = "This is Catherine Fox, a daughter of colonel Fox, commander of 'sea foxes' marines. We will be taking her to Antigua.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Intriguing! Welcome aboard miss Fox... And now lets get to the longboat - we need to get out here.";
			link.l1 = "You are the best, Helen! And what would I do without you?.. Catherine, follow me!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- ��� �� ��������
		
		// --> �������
		case "on_coast":
			dialog.text = "Finally you woke up, darling. How do you feel? You have really scared me";
			link.l1 = "Helen, what happened? My head is splitting...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "When we entered the captain's cabin, you were lying on the floor still. My heart has almost stopped beating! The guys picked you up and dragged you to our ship - and just in time, since the dead men lying on the deck began to rise again.\nThat was a real nightmare! They were totally impervious! We quickly cut the ropes and tried to sail away, but a volley from their ship quickly turned our old tub into splinters. And then they hoisted sails and were gone in blink of an eye.\nOur ship sank, and everyone who managed to survive, have reached the shore in a boat. I managed to take your chest from the cabin. I know you keep many important things in there...";
			link.l1 = "You're a smart girl, Helen. What would I have done without you?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "I dragged you into the boat and then got you to the shore. You seemed dead, only your heart was beating very faintly. My hands are still shaking";
			link.l1 = "Thank you, love. I am indebted to you. How long had I been lying there, unconscious?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "For an entire day. I washed and bound your wounds, gave you medicine and poured some rum into you. Now you must get well!";
			link.l1 = "I promise I will not die this time, darling. Although I don't feel really well...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "That's for sure... Was it the 'Flying Dutchman', cap? Why did they attack us? And why didn't they shoot at us before the boarding, but sank the ship with just one volley later?";
			link.l1 = "Their captain needed the amulet, about which I had talked to Tuttuathapak, an Indian shaman. That's why they haven't sunk us immediately, but as soon as their leader got the amulet, they quickly disposed of us... What a nightmare! A ship manned by the dead! Impossible to believe...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Yeah, now it was our turn to encounter the 'Flying Dutchman'. When I have the chance, I'll go to church, light the candle for our miraculous delivery, and pray to our Lord";
			link.l1 = "Me too, Helen, I guess. But first I'll go back to that village. I need to tell Tuttuathapak everything about it. That accursed ship attacked us because of the amulet! I hope that red-skinned devil has some ideas, why in hell those living dead might have needed it.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Alright. But you must be careful - your wounds have barely healed.";
			link.l1 = "But you will help me to heal, won't you? And Helen, I love you...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//������� �������
			dialog.text = "I love you too, my darling...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- �������
		
		// �� ��������
		case "tieyasal":
			dialog.text = ""+pchar.name+", I have told you once that we share our fates together now. Your fate is my fate. When are we going to go there?";
			link.l1 = "You said yes, my dear... I am very glad. I will tell you a bit later when we are going to go there. We need to prepare ourselves.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "I am ready, my captain! I will follow you at the back of beyond!";
			link.l1 = "Thank you, my love...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// �� ���� ������
		case "islatesoro":
			dialog.text = "Oh, "+pchar.name+"! Glad to see you! What are you doing here, on Isla Tesoro?";
			link.l1 = "Same as always - business matters. And of course I wanted to check on you, Helen...";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}