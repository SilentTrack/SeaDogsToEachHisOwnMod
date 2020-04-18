
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Speak, I am listening";
			link.l1 = "I was mistaken. Farewell.";
			link.l1.go = "Exit";
			
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "A bird said that you have an epidemic here, am I correct?";
				link.l1.go = "Consumption";
			}
		break;
		
		
		case "Consumption":
			dialog.text = "Correct, so avoid visiting the dungeons without a serious reason. Why?";
			link.l1 = "Just curious. So if my boys will get too drunk and end up here - should I prepare some yellow linen then?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "Alas, senior, I don't get the joke in case you were joking. The dungeons are wet and cold and you know the climate. Consumption is an often guest in these dungeons. I even have to pay my lads for bringing food to chambers. Patrolling there is considered to be the same as penal servitude.";
			link.l1 = "I am sorry, I just wanted to know how serious is this?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "Exactly so. We don't even have a physician here - he died of the damn consumption too. Now only a medic of local garrisson examines prisoners once in a week. But who gives a damn about these low-lifes and criminals?\nMost folks think that they totally deserved such fate and it's hard to argue about this.";
			link.l1 = "My knowledge of medicine is modest, but as far as I know, consumption doesn't kill people in days like it does here. Shouldn't victims pine for months or even years?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "As you have just mentioned, you are not a physician, therefore talking about disease's characteristics is quite groundlessly for you. I don't get your curiosity and cynic behavior. People die here!";
			link.l1 = "Didn't you just said that they deserve it?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Enough, senior! I believe that you and me have other matters to attend to rather then to sparkle with wit. The door is right behind you.";
			link.l1 = "Fine, forgive me my tactlessness, I am leaving already.";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			DialogExit();
			npchar.quest.Consumption = "true";
			pchar.questTemp.Consumption.Commandant = "true";
			AddQuestRecord("Consumption", "3");
			pchar.quest.Consumption.win_condition.l1 = "location";
			pchar.quest.Consumption.win_condition.l1.location = "PortSpein_houseF2";
			pchar.quest.Consumption.function = "Consumption_CommandantHouse";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  
}

