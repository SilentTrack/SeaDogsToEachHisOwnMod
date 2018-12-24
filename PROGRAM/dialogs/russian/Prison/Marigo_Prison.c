// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Speak, I am listening";
			link.l1 = "I was mistaken. Farewell.";
			link.l1.go = "Exit";
			//искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison"))
            { 
                link.l1 = "You have Simon Morelle under arrest here. He is a smuggler whose schooner was sunk by a patrol not long ago. Can I see him?";
                link.l1.go = "BarbTemptation";
				DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison");
            }
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div")
			{
				link.l1 = "Officer, I was sent here by mynheer governor of Philipsburg. He asked me to raid the island and it's waters in a search of English spies. His Excellence has also told me that you can provide me with useful information.";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div_2")
			{
				link.l1 = "Officer, I've found the missing patrol. I also found the British spies. They are here on the island.";
				link.l1.go = "FMQN_3";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_peace_rew")
			{
				link.l1 = "Me again, officer. Did you detain the spies?";
				link.l1.go = "FMQN_8";
			}
		break;
		
		//искушение барбазона
		case "BarbTemptation":
			dialog.text = "And why do you need him, sir?";
			link.l1 = "I want to tell him that he is a damn bastard and scoundrel. I hope that it will help him standing on gallows.";
			link.l1.go = "BarbTemptation_1";
		break;
		
		case "BarbTemptation_1":
			dialog.text = "Ha-ha! You've got a humor, sir... Well, two thousand pesos and you can move along.";
			if(sti(Pchar.money) >= 2000)
			{
				link.l1 = "Take them, officer. Thanks!";
				link.l1.go = "BarbTemptation_2";
			}
			link.l2 = "Hm... You know I have changed my mind. I'd better waste these money in a tavern.";
			link.l2.go = "BarbTemptation_4";
		break;
		
		case "BarbTemptation_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "You are welcome... Move along!";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "BarbTemptation_4":
			dialog.text = "Whatever, you want get such a proposal next time.";
			link.l1 = "I don't need it anyway. See you, officer!";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			dialog.text = "Useful? Ha! On the second thought, wait. I do have something useful to tell you. One of our patrols gone missing in the jungles. They were supposed to be back in their barracks by now but it seems that they prefer a company of parrots instead. Or something really has happened. If you find them during your searches, please tell them to make up a decent justification of their delay or otherwise I'll ground them. The patrol's commander is called Jannes Hoffman.";
			link.l1 = "That will be all officer?";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Yes, dammit. Good luck, captain.";
			link.l1 = "Thank you so much...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			DialogExit();
			pchar.questTemp.FMQN = "way_div_1";
			AddQuestRecord("FMQ_Nevis", "10");
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_3":
			dialog.text = "What?! I hope you are serious? Give me a report!";
			link.l1 = "I met a patrol near a cave in the jungles. They had stopped me and asked where I was heading to and why. Damn me, if it wasn't Brits disguised in Dutch uniform! I also saw something curious in the jungles which looked exactly like a bunch of naked men hidden in bushes. I assume, the British raiding party had unarmed your patrol and took their uniform.";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			dialog.text = "...";
			link.l1 = "As you understand, I didn't take my chances against a squad of trained marines and rushed to you with a report instead.";
			link.l1.go = "FMQN_5";
		break;
		
		case "FMQN_5":
			dialog.text = "Well-well... A cave you said? The number of heads?";
			link.l1 = "Five heads. I believe they went inside that cave.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			dialog.text = "I am sending a squad to the cave right away! Captain, you can count on a reward if the men you met really are the British spies. You are free to join the squad if you want to assist the authorities and receive an extra reward. Governor's orders. So, are you coming to the jungles?";
			link.l1 = "No officer, chasing spies is your job. Make sure to enforce the squad - those lads are a tough bunch.";
			link.l1.go = "FMQN_7";
			link.l2 = "I think I can do that. You men will find the spies faster with my help.";
			link.l2.go = "FMQN_10";
		break;
		
		case "FMQN_7":
			dialog.text = "No pressure, captain, I'll take your advice into account. Come see me tomorrow to hear about results of our operation.";
			link.l1 = "See you tomorrow.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeace");
		break;
		
		case "FMQN_8":
			dialog.text = "Your information was correct, captain. We had found the bastards inside the cave. They had shown no intention to surrender and engaged into a fight. Dead now, all of them.. We've also found the missing patrol. They are fine and alive, although a bit beaten... Thank you, captain, in the name of all good citizens of Philipsburg. Your vigilance will be rewarded as promised. Please take it.";
			link.l1 = "Thank you!";
			link.l1.go = "FMQN_9";
		break;
		
		case "FMQN_9":
			AddMoneyToCharacter(pchar, 10000);
			dialog.text = "You are always a welcome guest on Sint-Maarten. Now please excuse me - I have other business to attend to.";
			link.l1 = "Me too. Farewell.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeaceComplete");
		break;
		
		case "FMQN_10":
			dialog.text = "Very well. Your help is the most appreciated. Go to the city gates to join the squad in an hour.";
			link.l1 = "I suggest you order to send the best on this mission. Those spies are a tough lot.";
			link.l1.go = "FMQN_11";
		break;
		
		case "FMQN_11":
			dialog.text = "Don't you worry. I am sending our most experienced soldiers under command of Hans Shulte - the best officer of Philipsburg.";
			link.l1 = "No wasting time then.";
			link.l1.go = "exit";
			WaitDate("",0,0,0,1,5);
			AddDialogExitQuestFunction("FMQN_HollandBattle");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
