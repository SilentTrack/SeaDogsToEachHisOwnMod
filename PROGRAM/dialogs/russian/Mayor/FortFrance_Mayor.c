// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want? Ask away.", "I am listening to you, what's the question?"), "It is the second time you are trying to ask...", "It is the third time you are again trying to ask...",
                          "When is it going to end?! I am a busy man, working on the colony's matters and you are still trying to ask something!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...", "Not now. There is no time."), "True... But later, not now...",
                      "I'll ask, I'll ask... a bit later though...", "I am sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l1 = "Monsieur, I have found a bandit corpse in jungles. He was killed by the Indians. There were those earrings on his body, looks like they were brought here from Europe. Maybe they were belonging to one of the nobles in your town?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "I arrived by the order of Governor General Philippe de Poincy to take command of your armed frigate.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "I'm ready to take the frigate into the squadron.";
                link.l1.go = "patria_2";
			}
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Let's take a closer look ... Incredible! It's just incredible, Charles! This is my wife's earrings. I gave them to her before I left for the colonies. They disappeared a few months ago under mysterious circumstances. I knew they were stolen!\nCharles, I'm very glad that you came directly to me, and did not sell this thing that I hold so dear to the merchants. I'll repay you your favour. From what I've heard, you are going to buy a ship? Since you decided to partake in seafaring, you will undoubtedly need a map of our archipelago. Here, take it. I'm sure it will come in handy!";
			link.l1 = "Thank you, your Grace!";
			link.l1.go = "Sharlie_junglejew_1";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "jewelry25", 1);
			GiveItem2Character(pchar, "map_bad"); 
			AddQuestRecord("SharlieE", "2");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
		break;
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "The ship is ready, but you do not have room for it. Reduce your squadron and return, and I will immediately give you the frigate..";
				link.l1 = "Fine.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Yes, of course, the ship is ready to sail. The captain is aware and will carry out all your orders.";
				link.l1 = "Then we're setting out. Farewell, Your Grace.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Excellent. Prepare to greet your new ship. The captain is aware and will follow all your orders.";
			link.l1 = "Then we're setting out. Farewell, Your Grace.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateMrt(); // присоединяем фрегат
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

