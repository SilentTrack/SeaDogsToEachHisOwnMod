#include "DIALOGS\russian\Rumours\Common_rumours.c" //Jason
// Jason общий диалог смотрителей ма€ков
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Lighthouse\" + NPChar.City + "_Lighthouse.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
    int iTest, iTemp;
	string sTemp;
	bool ok;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Alarm is raised in the town. Apparently, it's time for me to take up arms as well...", "Aren't the city guards running after you, by chance?", "You will find no shelter here - but you may well find several inches of cold steel under your rib!"), 
					LinkRandPhrase("What do you need, "+ GetSexPhrase("scoundrel","rascal") +"?! The city guards have already hit your scent, you won't get far, "+ GetSexPhrase("filthy pirate","stinker") +"!", ""+ GetSexPhrase("Filthy","Filthy") +" murderer! Guards!!!", "I don't fear you, "+ GetSexPhrase("creep","stinker") +"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("I see you're tired of living...", "So it seems, there is no peaceful live for citizens of " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple("Go to hell!", "Heh, those will be the last few seconds of your life..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Good afternoon, sailor! My name is "+GetFullName(npchar)+", and I am the keeper of this lighthouse. What wind has brought you here?", "Hi there! It's been quite a while I last saw new faces at my lighthouse... Allow me to introduce myself - "+GetFullName(npchar)+", and this lighthouse is my home and my job. What can I do for you?");
				link.l1 = "Hello there, "+npchar.name+"! My name is "+GetFullName(pchar)+", I am a ship captain. I was talking a stroll in this wonderful cove and decided to drop in and take a look who lives there...";
				link.l1.go = "Lightman_meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Oh, my old friend, captain "+GetFullName(pchar)+"! Come in, come in! What brings you here this time?";
				link.l1 = "Hail to you, old salt! Aren't you wailing in solitude here at your lighthouse?";
				link.l1.go = "Lightman_talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_meeting":
			dialog.text = "Now you know. I am a sailor, just like you, but it's been long ago since I last set foot on a ship's deck. Now this lighthouse is in my care, and I am also selling some stuff...";
			link.l1 = "And what exactly are you selling?";
			link.l1.go = "trade_info";
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_talk":
			dialog.text = " What has brought you here this time?";
			link.l1 = RandPhraseSimple("Can you tell me, if anything interesting had recently happened in your colony?","I haven't been on land for quite a while... What's going on here?");
			link.l1.go = "rumours_lighthouse";
			link.l2 = "Let's see what you have for sale.";
			link.l2.go = "Trade_lighthouse";
			if (CheckAttribute(npchar, "artefact"))
			{
				if (CheckAttribute(npchar, "quest.art"))
				{
					link.l3 = "So, "+npchar.name+", has my amulet arrived already?";
					link.l3.go = "Trade_artefact_3";
				}
				else
				{
					link.l3 = ""+npchar.name+", I want to order an amulet from you.";
					link.l3.go = "Trade_artefact_1";
				}
				// калеуче
				if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "amulet" && !CheckAttribute(npchar, "quest.Caleuche"))
				{
					link.l5 = "Listen, "+npchar.name+", I know that you engage in delivery of amulets under an order. So, you certainly understand them well. Look, please, on this little thing - that you can say about her?";
					link.l5.go = "Caleuche";
				}
//				if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster && CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "mayak")
				if (CheckAttribute(pchar, "questTemp.Caleuche") && npchar.id == pchar.questTemp.Caleuche.Amuletmaster && pchar.questTemp.Caleuche == "mayak")
				{
					link.l5 = "Friend, I again to you concerning those strange amulets";
					link.l5.go = "Caleuche_9";
				}
			}
			link.l4 = "There is something I was going to ask you...";
			link.l4.go = "quests";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "Sometimes I go to the shore and collect shells, so you can always buy pearls from me. Every storm brings amber, I sell it too, although it will cost you a lot\nSometimes the waves bring all kinds of interesting trinkets from sunken ships and my old buddies bring me special items. I am interested in enchanted amulets, wise men pay good coin for those\nI also offer weapons on special occasion. A city merchant buys all the crap from me, good stuff I sell myself after I repair and clean it\nI am interested in rum. I am not talking about the piss they serve in local tavern for two pesos per cup. I am talking about real bottled Jamaican rum. It heals and resurrects people. I will pay ten times for every bottle you bring. Think about it.";
			link.l1 = "Listen, "+npchar.name+", you said that you had old sailor friends, who bring you ensorcelled amulets. Is it possible to order a certain amulet from you? I will pay for it handsomely.";
			link.l1.go = "Trade_artefact";
		break;
		
		case "Trade_lighthouse":
			//иногда продает корабельные товары // Addon-2016 Jason
			npchar.quest.goods = GOOD_COFFEE + drand(sti(GOOD_PAPRIKA - GOOD_COFFEE));
			npchar.quest.goodsqty = 50+drand(100);
			if (sti(npchar.quest.goods) == GOOD_EBONY || sti(npchar.quest.goods) == GOOD_MAHOGANY) npchar.quest.goodsqty = 25+drand(50);
			npchar.quest.goodsprice = makeint(sti(Goods[sti(npchar.quest.goods)].Cost)/4);//цена единицы товара
			npchar.quest.goodscost = sti(npchar.quest.goodsprice)*sti(npchar.quest.goodsqty);//стоимость товара
			ok = (!CheckAttribute(npchar, "goods_date")) || (GetNpcQuestPastDayParam(npchar, "goods_date") >= 10)
			if (drand(2) == 1 && makeint(GetCharacterFreeSpace(pchar, sti(npchar.quest.goods))) > sti(npchar.quest.goodsqty) && sti(pchar.money) >= sti(npchar.quest.goodscost) && ok)
			{
				dialog.text = "Captain, an amount of goods was recently washed ashore - " + GetGoodsNameAlt(sti(npchar.quest.goods)) + ". Some part was spoiled by salty water, but " + FindRussianQtyString(sti(npchar.quest.goodsqty)) + " are in great state. Want to buy some? I'll give them away cheaply, just for "+FindRussianMoneyString(sti(npchar.quest.goodsprice))+" per unit.";
				link.l1 = "Nah. Show me you recent gatherings.";
				link.l1.go = "Trade_lighthouse_double";
				link.l2 = "Hm... An honest offer, I agree. I guess I could resell it for some profit. Let's see... That will amount to "+FindRussianMoneyString(sti(npchar.quest.goodscost))+". Is that correct?";
				link.l2.go = "Trade_goods";
				SaveCurrentNpcQuestDateParam(npchar, "goods_date");
			}
			else
			{
				DialogExit();
				if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
				{
					GiveItemToTrader(npchar);
					SaveCurrentNpcQuestDateParam(npchar, "trade_date");
				}
				LaunchItemsTrade(npchar, 0);
			}
		break;
		
		case "Trade_lighthouse_double":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		case "Trade_goods":
			AddCharacterGoods(pchar, sti(npchar.quest.goods), sti(npchar.quest.goodsqty));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.goodscost));
			AddMoneyToCharacter(npchar, sti(npchar.quest.goodscost));
			dialog.text = "You've got it right, captain. A great bargain! We both made decent profit of it...";
			link.l1 = "Alright, then. I'll send the sailors right away. Now show me what you've gathered for sale.";
			link.l1.go = "Trade_lighthouse_double";
		break;
//------------------------------------------------заказ артефактов------------------------------------------------
		case "Trade_artefact":
			if (CheckAttribute(npchar, "artefact")) // Addon-2016 Jason за дублоны
			{
				dialog.text = "Well, not all of them, but several trinkets are coming in more often that others, so I guess I'd be able to help you. But I warn you: all amulets you would order in this way will cost you 100 doubloons. You should understand...";
				link.l1 = "Price is no problem. What amulets can you fetch in this matter?";
				link.l1.go = "Trade_artefact_1";
				link.l2 = "Pff! One could buy a ship for such money. That's too expensive. I guess I'll do fine by myself...";
				link.l2.go = "exit_artefact";
			}
			else
			{
				dialog.text = "No, captain. Such things can be found purely by chance, so it's impossible to place orders for them in advance. And also you'd have to wait for them forever...";
				link.l1 = "Well, if that's the case, there's nothing to be done.";
				link.l1.go = "exit_artefact";
			}
		break;
		
		case "exit_artefact":
			if (CheckAttribute(npchar, "artefact")) dialog.text = "As you wish. Come see me if you change your mind.";
			else dialog.text = "Would you like to see what I have for sale today, captain? If you don't find anything worthy, come again soon - I might have something else up for sale.";
			link.l1 = "Show me your wares.";
			link.l1.go = "Trade_lighthouse";
			link.l2 = "Just tell me, what interesting things had happened in your colony recently?";
			link.l2.go = "rumours_lighthouse";
			link.l3 = "That's fine and stuff, but I wanted to ask you something...";
			link.l3.go = "quests";
			link.l4 = "Have a nice day, "+npchar.name+"! It was nice meeting you! I'll drop in some other time...";
			link.l4.go = "exit";
		break;
		
		case "Trade_artefact_1":
			dialog.text = "Make your pick.";
			iTemp = 1;
			string sArt;
			if (CheckAttribute(npchar, "artefact.indian")) sArt = "indian_";
			if (CheckAttribute(npchar, "artefact.amulet")) sArt = "amulet_";
			if (CheckAttribute(npchar, "artefact.obereg")) sArt = "obereg_";
			for (i=11; i>=1; i--)
			{
				sTemp = "l"+iTemp;
				link.(sTemp) = XI_ConvertString(sArt+i);
				link.(sTemp).go = sArt+i;
				iTemp++;
			}
			link.l12 = "Unfortunately, nothing from this list interests me so far.";
			link.l12.go = "exit";
		break;
		
		//группа indian
		case "indian_1":
			dialog.text = "A voodoo doll? You're fond of firearms? Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_1";
		break;
		
		case "indian_2":
			dialog.text = "A gunpowder tester? Sharpshooting is a key to success in any skirmish. Nice...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_2";
		break;
		
		case "indian_3":
			dialog.text = "A ritual knife? You like slashing your enemies with powerful swings of a heavy broadsword? That's for you, then. Good... ";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_3";
		break;
		
		case "indian_4":
			dialog.text = "A pole axe? A top-down strike of a huge axe will crush any enemy! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_4";
		break;
		
		case "indian_5":
			dialog.text = "A tsantsa? Now that thing can scare even the most reckless pirate. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_5";
		break;
		
		case "indian_6":
			dialog.text = "A coral head? The grapeshot of your cannons will fly straight to the target! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_6";
		break;
		
		case "indian_7":
			dialog.text = "Humpback? Tirelessness is warrior's best friend. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_7";
		break;
		
		case "indian_8":
			dialog.text = "Xiuhtecuhtli? Let the enemy ship's hull crumble to dust! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_8";
		break;
		
		case "indian_9":
			dialog.text = "Baldo? Put Baldo on - and all cannonballs will fly straight to the target! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_9";
		break;
		
		case "indian_10":
			dialog.text = "Cascavella? Snake's venom is the most dangerous thing. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_10";
		break;
		
		case "indian_11":
			dialog.text = "Ngombo mask? Put it on and lull your enemies, ha-ha! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_11";
		break;
		
		//группа amulet
		case "amulet_1":
			dialog.text = "Ngombo shield? If you didn't manage to dodge a bullet, this amulet can save your live. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_1";
		break;
		
		case "amulet_2":
			dialog.text = "Euchologion? A good prayer can even divert a bullet. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_2";
		break;
		
		case "amulet_3":
			dialog.text = "A crucifix? This one will greatly aid a Christian in close combat. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_3";
		break;
		
		case "amulet_4":
			dialog.text = "El Trozo? This one will make a mortal wound just a scratch. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_4";
		break;
		
		case "amulet_5":
			dialog.text = "Sogbo? And let the cannons always be ready for battle! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_5";
		break;
		
		case "amulet_6":
			dialog.text = "Madonna? The visage of the Most Holy Virgin possesses powerful healing properties. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_6";
		break;
		
		case "amulet_7":
			dialog.text = "Holy water? Even a weakling sprinkled with holy water shall become an epic hero! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_7";
		break;
		
		case "amulet_8":
			dialog.text = "An anchor? And may your ship stay afloat even under a volley of cannonballs, ha-ha! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_8";
		break;
		
		case "amulet_9":
			dialog.text = "Encolpion? You sails shall fear no wind, while you possess this amulet. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_9";
		break;
		
		case "amulet_10":
			dialog.text = "Wonderworker? May the Lord watch over you crew both on land and at sea! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_10";
		break;
		
		case "amulet_11":
			dialog.text = "Cimaruta? Musket bullets shall fly over your head, causing no harm! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_11";
		break;
		
		//группа obereg
		case "obereg_1":
			dialog.text = "Teredo? Every shipwright dreams of that one. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_1";
		break;
		
		case "obereg_2":
			dialog.text = "Xochipilli? That will save some time darning the sails. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_2";
		break;
		
		case "obereg_3":
			dialog.text = "A monkey? A pack mule, I'd say! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_3";
		break;
		
		case "obereg_4":
			dialog.text = "Gypsy's fan? Put the blinkers on a patroller's eyes! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_4";
		break;
		
		case "obereg_5":
			dialog.text = "A jade turtle? That's your joker in a deck of cards! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_5";
		break;
		
		case "obereg_6":
			dialog.text = "A monkey's fist? As they say - make them respect yourself! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_6";
		break;
		
		case "obereg_7":
			dialog.text = "A fisherman? That's every navigator's dream. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_7";
		break;
		
		case "obereg_8":
			dialog.text = "Merchant's beads? Money likes to be counted, doesn't it? Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_8";
		break;
		
		case "obereg_9":
			dialog.text = "Ehecatl? Any low-speed old tub will fly faster than wind! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_9";
		break;
		
		case "obereg_10":
			dialog.text = "Seafarer's earring? Give that one to your helmsman! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_10";
		break;
		
		case "obereg_11":
			dialog.text = "Pilgrim? Head wind becomes tail wind. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_11";
		break;
		
		case "Trade_artefact_2":
			dialog.text = "In two months, no sooner. I think by that time they will already get it to me. So I'll be waiting for you with the money by the time.";
			link.l1 = "Great! I'll be there! Thank you, "+npchar.name+"!";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "art_date");
			npchar.quest.artday = rand(20)+50;
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "1");
			ReOpenQuestHeader(sTemp);
			AddQuestUserData(sTemp, "sAml", XI_ConvertString(npchar.quest.art)); // dlc
		break;
		
		case "Trade_artefact_3":
			if (CheckAttribute(npchar, "art_date") && GetNpcQuestPastDayParam(npchar, "art_date") >= sti(npchar.quest.artday))
			{
			dialog.text = "Yeah, I have it. Have you prepared 100 doubloons, captain?"; // Addon-2016 Jason
				if(GetCharacterItem(pchar, "gold_dublon") >= 100)
				{
					link.l1 = "Sure! Here you go, as agreed.";
					link.l1.go = "Trade_artefact_4";
				}
				else
				{
					link.l1 = "Oh, I've forgot the money on the ship! I'll fetch it right now.";
					link.l1.go = "exit";
				}
			}
			else
			{
			dialog.text = "Not yet. Come see me in a bit. And don't you worry - your amulet will surely arrive.";
			link.l1 = "Fine.";
			link.l1.go = "exit";
			}
		break;
		
		case "Trade_artefact_4":
			RemoveItems(pchar, "gold_dublon", 100); // Addon-2016 Jason
			Log_Info("You have given 100 doubloons");
			dialog.text = "Everything seems fine. Here is your amulet. Good luck with it!";
			link.l1 = "Thank you, "+npchar.name+"!";
			link.l1.go = "Trade_artefact_5";
		break;
		
		case "Trade_artefact_5":
			DialogExit();
			Log_Info("You have received "+XI_ConvertString(npchar.quest.art)+"");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, npchar.quest.art, 1);
			DeleteAttribute(npchar, "quest.art");
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "2");
			CloseQuestHeader(sTemp);
		break;
		
		// --> калеуче
		case "caleuche":
			PlaySound("interface\important_item.wav");
			dialog.text = "Show that there for you.";
			link.l1 = "Here, look like the ancient Indian amulet. But only he can be needed for what - a mind I will not attach.";
			link.l1.go = "caleuche_1";
			npchar.quest.caleuche = "true";
		break;
		
		case "caleuche_1":
			if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster)
			{
				dialog.text = "Well-wellЕ You are already the third man who shows me such thing. Pal, this amulet was brought here from the wild selva of Southern Main. There are Indians, not far from Panama, who wear trinkets like this one. The redskins say that this is a legacy of their 'great ancestors'\nI have no idea who were their ancestors and what kind legacy did they left. But I can give you an advice where to ask. Interested?";
				link.l1 = "Certainly!";
				link.l1.go = "caleuche_2";
			}
			else
			{
				dialog.text = "Hmm... I hold a lot of different amulets in their hands, but that I see for the first time in the Caribbean. Sorry, buddy, I can not help - I do not know what kind of curiosity. But that is not a simple thing - a fact. Ask somebody else - maybe someone met like.";
				link.l1 = "Sorry... I will continue to ask - look, we're lucky.";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_2":
			dialog.text = "Dominica Carib village leader has Moknitekuvri. They have a shaman named Tuttuathapak, highly respected Indian. He's not one of the Caribs, and just one of those places about which I told you. It was he sure can tell more about this amulet me. But be careful - Tuttuathapak hates whites. Very. After all, they once took him into slavery and taken away from their homes...";
			link.l1 = "So he's that way and got to the Caribbean?";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Yes. This is quite an interesting story. The ship, which carried Indian slaves, was trapped by a dead calm and half of a crew died from sudden fever. Yet not a single Indian got ill!\nAfterwards, a captain got mad and set his vessel on fire. As a result, the imprisoned Indian slaughtered the crew. Guess who was their leader?";
			link.l1 = "Guess...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "That's it. I do not drink rum until the end of my days, if it is not a spell shaman brought calm sea, and infection at the team captain's obsession. This Indian is very smart and very dangerous. If you go to him - behave politely and follow what you say - otherwise there will be trouble. And without offering him not put - he would not even talk to you.";
			link.l1 = "And what kind of offering does he want?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Any nonsense you did not buy. From what I hear, he sends his soldiers Carib buy White firearms. Bring him a gift musket - I think he will be pleased and will give you a bit of your attention.";
			link.l1 = "Thank you! And do... Say, buddy, how do you know all this?";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "My friend was a sailor on the ill-fated ship. Fortunately, he managed to survive in that hell kromeshnom... He and I saw for the first time with this bling pattern as on your amulet - to see, along with the late Indian captain also grabbed their belongings. I am sure that your pet from his collection - when the captain went crazy and started a fire, his sailors koknuli and then looted the chests in the cabin.";
			link.l1 = "Clear. Then I just have to go with a gift on Dominica. Thanks for your help and for the interesting story!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Good luck, my friend, and be careful with this redhead devil...";
			link.l1 = "...";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			AddQuestRecord("Caleuche", "2");
			pchar.questTemp.Caleuche = "dominica"; 
			Caleuche_CreateShamane();
		break;
		
		case "caleuche_9":
			dialog.text = "Yes? You've been to Tuttuathapaka?";
			link.l1 = "Exactly. And now I want to find two more charm. I thought you said I was the third, who showed you this artifact. And who were the other two?";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "One - this is my friend, the one sailor with slave ship, which brought Tuttuathapaka. Since that incident, he is more than a foot in the sea. I have not seen him, but I know where it is acquired. Look for it in the West Maine in Belize - he patched hunter and now shastaet jungle. Name - Fergus Hooper.";
			link.l1 = "Remember. And the second?";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "I know about the second bit. Whether his name is Jack, or Jackson, and whether it is a privateer, or small businessman, or simply an adventurer. He xebec with a strange name... m-hmm... what was called his pelvis? Damn, I forgot! But the name of a demonic. I asked him what it meant, and he said it was a bird-woman, born marine deities. Ugh, heathen...";
			link.l1 = "That nerd... So turn up the names Xebec not you remember?";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "No, thunder strike me, I do not remember. Oh, and when it seemed to me, he said that he and Barbados.";
			link.l1 = "That's something! Okay, I'll try to find this amateur feathered women until he found someone else... Thanks, buddy, you helped me a lot!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			dialog.text = "Not at all, cap, would drop more and chat.";
			link.l1 = "Look in necessarily!";
			link.l1.go = "caleuche_14";
		break;
		
		case "caleuche_14":
			DialogExit();
			AddQuestRecord("Caleuche", "7");
			pchar.questTemp.Caleuche = "hunting"; 
			pchar.questTemp.Caleuche.Belizterms = rand(4)+3;
			pchar.quest.caleuche_prepare_beliz.win_condition.l1 = "location";
			pchar.quest.caleuche_prepare_beliz.win_condition.l1.location = "Beliz";
			pchar.quest.caleuche_prepare_beliz.function = "Caleuche_PrepareBeliz";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакци€ на попытку залезть в сундук
			dialog.text = LinkRandPhrase("You're "+ GetSexPhrase("thief, my dear! Sentinel, keep it "," thief! Guards keep her") +"!!!", "Wow! I gazed a little, and you're right in the chest with his head! Hold the thief!", "Guards! Rob! Stop thief!");
			link.l1 = "behold, the devil!";
			link.l1.go = "fight";
		break;
	}
}