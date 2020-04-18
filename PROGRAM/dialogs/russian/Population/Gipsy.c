

#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int poison_price;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "You again, darling? What do you want?";
			link.l1 = "Nothing I suppose.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("I have got a question for you.", "I need an information.");
			link.l2.go = "quests";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Darling, would you be kindly to spare some gold? I'll tell you the truth.","Hey, sailor, don't hurry like that! Do you want to know the truth?","Give me some tobacco and a few silver coins, brave young man. And I will take a look at your future.");
				link.l1 = "Sorry but I have to go.";
				link.l1.go = "exit";
				
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Listen, kind lady, I know that your people are experts in potions. I was told that you could be interested in this plant. Take a look.";
					link.l5.go = "mangarosa";
				}
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy_trade" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Hey, dark-browed, I have got something for you... This is Manga Rosa. Want to buy some?Hey, dark-browed, I have got something for you... This is Manga Rosa. Want to buy some?";
					link.l5.go = "mangarosa_trade1";
				}
				
				link.l2 = "Can you tell fortunes for me?";
				link.l2.go = "guess";
				link.l3 = RandPhraseSimple("I have got a question for you.", "I need an information.");
				link.l3.go = "quests";
				npchar.quest.meeting = "1";
			}
			if (!CheckAttribute(npchar, "quest.poison_price") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && rand(2) == 0)
			{
				link.l4 = "Hey, dark-browed, do you have some poisons for rats? I am too tired of them!";
				link.l4.go = "get_poison_1";
			}
			NextDiag.TempNode = "First time";
		break;


		case "guess":
			dialog.text = "Sure, brave young man. Give me some coins and show your right hand. I'll tell you about your future with no cheating!";
			link.l1 = "Actually I have changed my mind. I am not in the mood...";
			link.l1.go = "exit";
			link.l2 = "How much?";
			link.l2.go = "guess_1";
		break;
		
		case "guess_1":
			dialog.text = "Ah, sweetie, as much as your purse and wish will let you.";
			link.l1 = "100 pesos";
			link.l1.go = "guess_rate_1";
			link.l2 = "500 pesos";
			link.l2.go = "guess_rate_2";
			link.l3 = "1000 pesos";
			link.l3.go = "guess_rate_3";
			link.l4 = "5000 pesos";
			link.l4.go = "guess_rate_4";
		break;
		
		sTemp = GuessText();
		case "guess_rate_1":
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Ah, thanks for a few coins, my brave young man! Now listen: "+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! That's very interesting. I'll consider that...","Really? I'll consider that...","Oh, really? Are you serious? Well, I'll remember that...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "The ugliest and the unavoidable misfortune is waiting for you. Curse the mocker! Let the dark clouds to gather upon you and let the punishment find you!";
				link.l1 = "Ha-ha! Have you really hoped that I would give money, witch? Get out of my way!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_2":
			if (sti(pchar.money) >= 500)
			{
				AddMoneyToCharacter(pchar, -500);
				dialog.text = "Ah, thank you, brave young man! Now listen:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! That's very interesting. I'll consider that...","Really? I'll consider that...","Oh, really? Are you serious? Well, I'll remember that...");
				link.l1.go = "exit";
				if (drand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 30+rand(10));
				else AddCharacterExpToSkill(pchar, "Sneak", 30+rand(10));
			}
			else
			{
				dialog.text = "The ugliest and the unavoidable misfortune is waiting for you. Curse the mocker! Let the dark clouds to gather upon you and let the punishment find you!";
				link.l1 = "Ha-ha! Have you really hoped that I would give money, witch? Get out of my way!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_3":
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Ah, thanks for your silver, brave young man! Now listen:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! That's very interesting. I'll consider that...","Really? I'll consider that...","Oh, really? Are you serious? Well, I'll remember that...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				if (drand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 50+rand(20));
				else AddCharacterExpToSkill(pchar, "Sneak", 50+rand(20));
			}
			else
			{
				dialog.text = "The ugliest and the unavoidable misfortune is waiting for you. Curse the mocker! Let the dark clouds to gather upon you and let the punishment find you!";
				link.l1 = "Ha-ha! Have you really hoped that I would give money, witch? Get out of my way!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_4":
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Ah, thank you for your generosity, brave young man! Now listen:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! That's very interesting. I'll consider that...","Really? I'll consider that...","Oh, really? Are you serious? Well, I'll remember that...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 2);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCharacterExpToSkill(pchar, "Fortune", 50+rand(100));
				AddCharacterExpToSkill(pchar, "Sneak", 50+rand(50));
				AddComplexSelfExpToScill(20, 20, 20, 20);
			}
			else
			{
				dialog.text = "The ugliest and the unavoidable misfortune is waiting for you. Curse the mocker! Let the dark clouds to gather upon you and let the punishment find you!";
				link.l1 = "Ha-ha! Have you really hoped that I would give money, witch? Get out of my way!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_exit":
			DialogExit();
			AddCharacterHealth(pchar, -10);
			LAi_CharacterDisableDialog(npchar);
		break;



		case "get_poison_1" :
			npchar.quest.poison_price = (drand(3) + 1) * 10;
			if(drand(10) == 3)
			{				
				dialog.text = LinkRandPhrase("Oh, I am not sure, handsome! There was a guy not long ago asking to help in killing rats and then someone has poisoned soldiers in the fort. They were interrogating us every day until they've found that murderer. He was an enemy spy.",
				                             "And how can I be sure in your purpose? Maybe you just want to poison a nobleman who you are scared to fight in an honorable duel?",
											 "They've told me that someone has poisoned some trade man in the tavern and has taken all of his belongings then. The man was suffering for a long time until he has gone. Are you responsible for that, my love?");
				link.l1 = "And that is your opinion about me! Don't worry I am not going to poison people, it's not my style. I have my own weapons against them, but I can't handle those rats.";
				link.l1.go = "get_poison_2";
			}
			else
			{
				dialog.text = "And that what you ask?! No I don't have any poison. I have got plants, potions but no poisons.";
				link.l1 = "Whatever then.";
				link.l1.go = "exit";
			}	
		break;
		
		case "get_poison_2" :
			dialog.text = "Fine, I'd help you. But don't tell anyone. Pay me "+sti(npchar.quest.poison_price)+" doublons.";
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.poison_price)) 
			{				
				link.l1 = "Pricey,,, Fine, I hope that it will help.";
				link.l1.go = "get_poison_4";
			}
			else
			{
				link.l1 = "No way! I was buying for five last time! I would catch every rat by myself for that much money!";
				link.l1.go = "get_poison_3";
			}
		break;
		
		case "get_poison_3" :
			dialog.text = "Catch them then and don't bother. I will call soldiers next time.";
			link.l1 = "There is no need in soldiers, I am leaving.";
			link.l1.go = "exit";
		break;
		
		case "get_poison_4" :
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.poison_price));
			TakeNItems(pchar, "rat_poison", 1);
			DialogExit();
		break;


	
		case "mangarosa":
			dialog.text = LinkRandPhrase("Show me your plant, sweetie... Hm... I suppose that I can buy it from you. Three hundred pesos?","Show me it, friend... Heh... Well I can pay two hundred and a half for it.","Let's see... Oh! An interesting example! Two hundred pesos! Deal?")"";
			link.l1 = LinkRandPhrase("Here are we go... Dark-browed, I am not some fool from the village. I know this plant. It is Manga Rosa...","Oh, really?! This is Manga Rosa and it's a perfect plant. Don't try to cheat on me.","Aha, and you suppose that I will give you the Manga Rosa for a few coins...");
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			dialog.text = "Fine, Fine, handsome. I see that you know something about this plant. Fifty doubloons. Give it to me.";
			link.l1 = "Oh, calm down! I want to know how do you use it and for what. Can you tell me about that? All of your people are willing to pay a lot of gold for this green bush!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			
			if (sti(pchar.questTemp.Mangarosa.g_count) == 5 || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 10+drand(25)+drand(30))
			{
				dialog.text = "Hm... I suppose that it won't be bad if I'll tell you a bit about her. You won't be able to do anything with the plant without some special skills.";
				link.l1 = "I am listening.";
				link.l1.go = "mangarosa_3";
			}
			else
			{
				dialog.text = LinkRandPhrase("My people might pay a lot of gold but the would never expose their secrets.","Gold is gold and secrets are secrets, young man... ","Sure, we are willing to pay but not to tell.")+"So are you going to sell me your Manga Rosa? Fifty doubloons is our normal tax for it, no one will pay you more.";
				link.l1 = "Oh, fine... I am. Fifty doubloons will work for me. Take it.";
				link.l1.go = "mangarosa_trade";
				link.l2 = "Understand that I don't want to sell it. I want to know why do you need it. Share your knowledge with me and I will give it to you for free.";
				link.l2.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_trade":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Take your coins, handsome. And if you'll find more - bring it to us. But we buy it only by one plant because we don't carry big sums with us. The guards like to grasp our kind.";
			link.l1 = "Fine. If I'll find more - I'll bring it.";
			link.l1.go = "mangarosa_trade_exit";
		break;
		
		case "mangarosa_trade_exit":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "gipsy_trade";
			AddQuestRecord("Mangarosa", "3");
		break;
		
		case "mangarosa_exit":
			dialog.text = LinkRandPhrase("No way! If you don't want to sell it - don't do so then. I won't tell you a thing.","I won't expose our secrets to the outsider. Don't want to sell it? Hell with you.","Friend, that is now for your ears. Don't want to sell it for fifty doubloons? Go and sell to the trade girl for two hundred pesos.");
			link.l1 = LinkRandPhrase("Too bad for you then! Another one of your people will tell me about it anyway. And she will get the plant as a present. See you!","Why so stubborn? If you won't tell me the other would. And she will get Manga Rosa as a present. Farewell.","Why do you stink like that? I will het what I want eventually. One of your people will be more talkative and will get the plant for free. See you.");
			link.l1.go = "exit";
			npchar.quest.mangarosa = "true";
			pchar.questTemp.Mangarosa.g_count = sti(pchar.questTemp.Mangarosa.g_count)+1;
		break;
		
		case "mangarosa_trade1":
			dialog.text = "And why do you ask, handsome?! Sure! Give it to me.";
			link.l1 = "Give me fifty doubloons.";
			link.l1.go = "mangarosa_trade1_1";
			link.l2 = "Oups! It seems that I've lost it or forgot on my ship. Such a shame. Sorry...";
			link.l2.go = "exit";
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_trade1_1":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Don't worry, I won't cheat on you. Take your coins.";
			link.l1 = "Take you Manga Rosa. I will bring more if I find.";
			link.l1.go = "exit";
		break;
		
		case "mangarosa_3":
			dialog.text = "We grind it in the special way, then dry it, mix it with tobacco, tamp our pipes and smoke the mix. And we are getting an... unforgettable effect. One plant is enough for a two dozens pipes.";
			link.l1 = "I see now! Can you teach me that? I can pay you well...";
			link.l1.go = "mangarosa_4";
		break;
		
		case "mangarosa_4":
			dialog.text = "Brave young man, trust me, it isn't worth it. Don't get involved in all of this, it will ruin you. Don't even ask me. But... I see a brave man in front of me, with a sword, sailor...even the captain perhaps?";
			link.l1 = "You are right.";
			link.l1.go = "mangarosa_5";
		break;
		
		case "mangarosa_5":
			dialog.text = "Listen here then. Manga Rosa can be utilized for much noble goals and you may find it useful. One healer of ours knows all secrets of it. She is the one you need\nGive me your plant and I will tell you her name and location. Persuading her to share her secrets with you will be only yours pain in the head.";
			link.l1 = "Fine. Take the plant and tell me how to find your healer.";
			link.l1.go = "mangarosa_6";
		break;
		
		case "mangarosa_6":
			RemoveItems(pchar, "cannabis7", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Her name is Amelia. She lives alone on a small house among the dunes not far from the sea, somewhere at the south-west of Main as the wise folks say.";
			link.l1 = "Hm. Can you tell me more about where to find her?";
			link.l1.go = "mangarosa_7";
		break;
		
		case "mangarosa_7":
			dialog.text = "You are a sailor, brave man, and I am not. Seek her well there where I said. Her home is really close to the seacoast. There is some bay not far from there - sailors must know it.";
			link.l1 = "Alright, I'll try to find it...";
			link.l1.go = "mangarosa_8";
		break;
		
		case "mangarosa_8":
			dialog.text = "Take a Manga Rosa to her or she will not even talk to you. And don't forget about doubloons, don't you think that she will teach you for free!";
			link.l1 = "I'll consider that. Thanks for your story!";
			link.l1.go = "mangarosa_9";
		break;
		
		case "mangarosa_9":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "amelia";
			pchar.questTemp.Mangarosa.Tell = "true"; 
			AddQuestRecord("Mangarosa", "4");
			
			sld = GetCharacter(NPC_GenerateCharacter("Amelia", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Amelia";
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Mangarosa.c";
			sld.dialog.currentnode = "amelia";
			
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Amelia_house", "barmen", "stay");
		break;
		
		
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Listen, I am the citizen of this town and I'd ask you to hold down your blade.", "Listen, I am the citizen of this town and I'd ask you to hold down your blade.");
			link.l1 = LinkRandPhrase("Fine.", "Whatever.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GuessText()
{
	string sText;
	switch (drand(19))
	{
		case 0: sText = "you will have a luck, brave young man, tomorrow you'll be lucky with cards!" break;
		case 1: sText = "the fortune will be kind with you in your business, captain!" break;
		case 2: sText = "there is a misfortune in the open sea, it's waiting just for you, wait for a three days!" break;
		case 3: sText = "I see that you need to seek help from your closest ones, you won't make it alone in your next fight!" break;
		case 4: sText = "go and light a candle in a church, you were cursed by your enemy. You won't make it without God's help!" break;
		case 5: sText = "you are going to loose a lot soon, but don't despair and hope for yourself and seek a help from you friends..." break;
		case 6: sText = "the heavy loss is waiting for you in the sea, but I see, that you, captain, will be able to compensate it even if you won't get what you want." break;
		case 7: sText = "you have entered in the rot, captain! Visit a brothel and have some rest." break;
		case 8: sText = "you will get what you want, captain, but don't expect anything good from it. All what you've wanted so passionately, cap, will bring only the bad things so you'd better drop you plans away." break;
		case 9: sText = "I see that there is a sign on the face of yours, the sign of an ultimate luck. You will get more than you've expected to get, young man!" break;
		case 10: sText = "you need to evaluate your with once again and decide. Do you really need it? Your fate is giving you a chance to rethink." break;
		case 11: sText = "it's a rare luck, not everyday we've getting a chance to rethink. Take a rest for a few days, bright-eyed, think about fleeting stuff. Don't hurry to your death!" break;
		case 12: sText = "though all of your efforts won't give you the expected result, don't despair, bright one, there is a luck is waiting for you in the most unexpected day, don't loose it!" break;
		case 13: sText = "your problem won't be solved in a positive way but you are a stubborn one and you'll get what you want but, perhaps, not from the place you've expected." break;
		case 14: sText = "you'd better forget about the business you are up to. You will never be lucky in this and if you'll be continuing in it than, perhaps, your closest people will be harmed or get dead." break;
		case 15: sText = "there is an event which is waiting for you, captain, and it will completely change you life. Your recent concerns will lost all of their meaning to you after that." break;
		case 16: sText = "there is a danger on your way to your dream, captain, and you would be really lucky if you will be able to get what you want without any heavy losses. It's better to turn away and forget your unachievable dream. Or perhaps, the fate could be fooled if you'll loose in cards or dices right now..." break;
		case 17: sText = "I see a strong power in you like a rock and the light as bright as the stars which lead people. There is a good sign and a new. There are waiting for you." break;
		case 18: sText = "a bad sign is on you way rising, fear the evil eye and keep the loyal people close to yourself." break;
		case 19: sText = "the lucky event is rising on your way right behind your own back. Look for the stuff which is coming right in your hands and don't chase the unachievable." break;
	}
	return sText;
}

