
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?", "How can I help you, " + GetAddress_Form(NPChar) + "?"), "You tried to ask me some question not long ago, " + GetAddress_Form(NPChar) + "...", "Over this whole day, this is the third time you're talking about some question...",
                          "More questions, I presume?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Umph, where has my memory gone...",
                      "Yes, it really is the third time...", "No, what questions?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
			{
				link.l1 = "Monsieur, I'm looking for work. May it be that you have some kind of errand that you could hand over to me?";
                link.l1.go = "Sharlie_rum";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
			{
				link.l1 = "I've fulfilled your assignment. The long boat with the rum has been delivered to Le Francois bay and transferred to your people.";
                link.l1.go = "Sharlie_rum_5";
			}	
			
			
			
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToMartinique" && !CheckAttribute(npchar, "quest.Portugal"))
			{
				link.l1 = "I need to rent one of your rooms for two or three days. I have a man on board that's wounded. He needs to get some rest and recover.";
				link.l1.go = "Portugal";
			}
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernorEnd")
			{
				link.l1 = "Tell me. My friend that I rented the room for, has he left? He promised to wait for me, but the room is empty.";
				link.l1.go = "Portugal_2";
			}
			
		break;
		
		
		case "Sharlie_rum":
			dialog.text = "A task? Hm... Looks like you have got something inside your skull, young man. I may have something for you\nThis job may sound easy, but it requires responsibility and brains. I can not trust these idiots to do business, they'll ruin it for sure...";
			link.l1 = "Listen, can you please just tell me what the heck it is you want to assign me? I swear, I won't let you down or at least I'll do  my damnest.";
			link.l1.go = "Sharlie_rum_1";
		break;
		
		case "Sharlie_rum_1":
			switch(rand(4))
			{
				case 0:
					pchar.questTemp.Sharlie.Rum.Pass = "old Thomas has grown tired of waiting for the beer";
				break;
				case 1:
					pchar.questTemp.Sharlie.Rum.Pass = "the boards and the oakum will be here in the morning";
				break;
				case 2:
					pchar.questTemp.Sharlie.Rum.Pass = "don't wait for the south wind";
				break;
				case 3:
					pchar.questTemp.Sharlie.Rum.Pass = "the bay is ready for disembarkation";
				break;
				case 4:
					pchar.questTemp.Sharlie.Rum.Pass = "the camels are going north";
				break;
			}
			dialog.text = "Good. I need someone to deliver several crates of elite Jamaica rum to my tavern. Taxes are way too brutal and my best customers are waiting, so we need to act smart in order to avoid unwanted attention of port officials. Lugger 'Ghost' will arrive to Martinique's shores tonight\nThey will drop an anchor not far from Lamanten bay. You must find this vessel and get aboard. I will provide you with a long boat and five sailors, they will follow your orders\nOnce you are aboard, a man will speak to you. You shall have to tell him a password: '"+pchar.questTemp.Sharlie.Rum.Pass+"'\nYou shall have only one try, so write it down and don't make a mistake or the deal is off. That's why I can't entrust it to those brainless morons who will sail with you. Repeat the password.";
			link.l1 = "'"+pchar.questTemp.Sharlie.Rum.Pass+"'.";
			link.l1.go = "Sharlie_rum_2";
		break;
		
		case "Sharlie_rum_2":
			dialog.text = "Splendid. After they will load crates on the long boat, take it to Le Francois bay. I have got men who shall meet you there. This is it\nThe longboat will stay at the bay and you will have to move on foot to Saint Pierre through jungles. So, are you not scared yet? I will pay five thousand pesos once it's done.";
			link.l1 = "What made you decide I'm supposed to be scared? I'll do what you tell me to do. Where's the longboat?";
			link.l1.go = "Sharlie_rum_3";
			link.l2 = "So, you propose that I take up smuggling? Hm... You know, I can't risk my name. You'll have to excuse me, we'll pretend that I didn't hear anything.";
			link.l2.go = "Sharlie_rum_exit";
		break;
		
		case "Sharlie_rum_exit":
			dialog.text = "As you wish, monsieur. I don't have any other errands.";
			link.l1 = "I see. Then all the best, "+npchar.name+".";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
		break;
		
		case "Sharlie_rum_3":
			dialog.text = "The longboat will be at the pier closer to the docks at seven in the evening. Don't be late it's no less than a five or six hour trip to Lamanten Beach and the Ghost will be waiting for you only until five in the morning. And take this spyglass to ease your searches it's junk, of course, but it's better than nothing. Lamanten beach is located at the northern tip of the island, so leaving the port, keep the course due north. And don't forget the password!";
			link.l1 = "I remember. See you soon, "+npchar.name+"!";
			link.l1.go = "Sharlie_rum_4";
		break;
		
		case "Sharlie_rum_4":
			DialogExit();
			AddQuestRecord("SharlieB", "1");
			GiveItem2Character(pchar, "spyglass1"); 
			Log_Info("You've received a spyglass");
			PlaySound("interface\important_item.wav");
			pchar.quest.Sharlie_rum.win_condition.l1 = "locator";
			pchar.quest.Sharlie_rum.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_rum.win_condition.l1.locator_group = "rld";
			pchar.quest.Sharlie_rum.win_condition.l1.locator = "loc0";
			pchar.quest.Sharlie_rum.win_condition.l2 = "HardHour";
			pchar.quest.Sharlie_rum.win_condition.l2.hour = 19.00;
			pchar.quest.Sharlie_rum.function = "Rum_CreateBarkas";
			SetFunctionTimerCondition("Rum_CreateBarkasOver", 0, 0, 1, false);
			pchar.questTemp.Sharlie.Rum = "true";
			npchar.quest.Rum = "true";
		break;
		
		case "Sharlie_rum_5":
			dialog.text = "Wonderful! I know I could depend on you. Was it hard?";
			link.l1 = "Well, that depends on how you define hard...";
			link.l1.go = "Sharlie_rum_6";
		break;
		
		case "Sharlie_rum_6":
			dialog.text = "Well, here's your reward �five thousand. You can keep the spyglass. And also, another little present �take these three bottles of rum. After you try it, you'll see right away why there's so much of a demand for it.";
			link.l1 = "Thank you! It was nice working with you! See you later!";
			link.l1.go = "Sharlie_rum_7";
		break;
		
		case "Sharlie_rum_7":
			DialogExit();
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "potionrum", 3);
			AddQuestRecord("SharlieB", "5");
			CloseQuestHeader("SharlieB");
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
		break;
		
		
		
		case "Portugal":
			dialog.text = "No problem, I have a room. For 50 pesos ,it's yours for three days.";
			if (sti(pchar.money) >= 50)
			{
				link.l1 = "Here you go.";
				link.l1.go = "Portugal_1";
			}
			else
			{
				link.l1 = "I'll go take the money from the paymaster and I'll be back.";
				link.l1.go = "exit";
			}
		break;
		
		case "Portugal_1":
			ref sld;
			DialogExit();
			AddMoneyToCharacter(pchar, -50);
			npchar.quest.Portugal = "true";
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", false);
			pchar.quest.Portugal_Ill3.over = "yes";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", true);
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto3");
			sld = characterFromId("PortugalDoctor");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto1");
			pchar.quest.Portugal_tavernroom.win_condition.l1 = "location";
			pchar.quest.Portugal_tavernroom.win_condition.l1.location = "FortFrance_tavern_upstairs";
			pchar.quest.Portugal_tavernroom.function = "PortugalInTavernRoom";
		break;
		
		case "Portugal_2":
			dialog.text = "I wouldn't say that he up and took off by himself, monsieur. Some people came by here yesterday. One of them was a one-eyed tall lanky man �an obvious bandit by how he looks, lisping too like a Castilian. I was just surprised and that lisper gave me this look...just like a louse �before a pounding. And so they asked about your friend...and I told them. What else was I supposed to do?";
			link.l1 = "I know, " + npchar.name + ", you're no hero, that's right. What else did you see? Where did they take off?";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "That's pretty much it...wait, no! Hold on, the one-eyed man said something about a wagon. I believe they took a wagon and dragged your friend clear over the other side of the island. That's all monsieur, I swear... I would call the guard, but that lisper told me I had a beautiful wife while I was leaving... See? If they find out I told you all this they'll...";
			if (pchar.money >= 1000)
			{
				link.l1 = "Don't be afraid, they won't hear anything from me besides bullets. You've really helped me, thank you. Here, take your 1000 pesos.";
				link.l1.go = "Portugal_4";
			}
			link.l2 = "It's not a lot, but thanks anyway. Next time �call the guard and don't be such a squab.";
			link.l2.go = "Portugal_5";
		break;
		
		case "Portugal_4":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Thank you, monsieur. I can give you my word that your friend has almost recovered. He at least was walking by himself. And the second man, that quiet Dutchman �he came in off the street. He spotted that pack and leaped outside, but he wasn't seen.";
			link.l1 = "I'd say he's already departed on the first ship he could take. Thank you for the information, it's time for me to go.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_5":
			dialog.text = "Not every man's to be a hero with his sword unsheathed, captain.";
			link.l1 = "Well... that's the man's choice.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_seapatrol_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  
}
