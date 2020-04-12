// Jason общий диалог смотрителей кладбищ
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Cemetery\" + NPChar.City + "_cemetery.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
    int iTemp;
	string sTemp;
	bool ok;
    
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("In city alerted to. Alike, and it is time me to take up arms...", "Whether does all municipal guard rush about not after you?. To me, soldiers!!!", "For me you will not find shelter. But will find a few inches of cold steel under a rib!"), 
					LinkRandPhrase("what do you want, scoundrel?! A municipal guard took your track already, far not to go away you, "+ GetSexPhrase("dirty pirate!","scoundrel") +"!", ""+ GetSexPhrase("Dirty killer! Guard!!!", "I am not afraid of you
, "+ GetSexPhrase("dirty pirate!","scoundrel") +"! Soon you will be hung up in our fort, far not to go away you..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("To live you bothered...", "And it does not live calmly to the peaceful citizens." + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple("Go to hell!", "To live there are a few seconds to you..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Good afternoon, sailor! I am called by "+GetFullName(npchar)+", and I - only living the soul here, ho! ho! ho! Why did grant?", "Hello! Old I did not see a living man... Allow to introduce oneself - "+GetFullName(npchar)+", and this cemetery is my last refuge. Apparently, here me and will bury. What can I serve as?");
				link.l1 = "Hello, "+npchar.name+"! My name is - "+GetFullName(pchar)+", and I am a captain. Here, walked about jungles and came here. Think, I will glance in this comfortable house, will look, whoever is afraid here to live...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А-а, my old friend, captain "+GetFullName(pchar)+"! Call, call!";
				link.l1 = "I welcome, friend! Very glad to see you. Do not at nights dancing skeletons and dead persons yet dream you with copper coins on eyes?";
				link.l1.go = "talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "And what to be here afraid, captain? To be afraid living is necessary, and the dead do not bite. Eh! Once I had quite another life, now here my caring is this cemetery. I look after graves. And also I a bit trade in every change...";
			link.l1 = "And what do you trade in, say please?";
			link.l1.go = "trade_info";
		break;
		
		case "talk":
			dialog.text = "What did bring you over to me this time?";
			link.l1 = "Show me what do you have for sale today.";
			link.l1.go = "trade";
			link.l2 = "I wanted to ask you a question...";
			link.l2.go = "quests";
			link.l3 = "Nothing serious. Simply dropped by to greet you.";
			link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "For me free plenty of time, therefore I like to walk about jungles and collect useful grasses. Then I sell them in city. Pure pence pay for them, but however better, than nothing. The most different objects give me my friends...";
			link.l1 = "Friends? Id est, do you resell that it is brought you?";
			link.l1.go = "trade_info_1";
		break;
		
		case "trade_info_1":
			dialog.text = "O-ho-ho... No, they all give me free of charge. What yet can be friends for a cemetery watch, if not deceaseds?";
			link.l1 = "Do you, pick dead bodies?";
			link.l1.go = "trade_info_2";
		break;
		
		case "trade_info_2":
			dialog.text = "I do not steal, and I take off things that already does not need them. Different people are buried here. Many unknown and not from our edges. A commandant will bring from a city dead body - it to you, "+npchar.name+", send him in the last way. Or tramps what damned a guard will interrupt, and old "+npchar.name+" buries their bodies on a christian custom.";
			link.l1 = "Clear. show the commodities to me.";
			link.l1.go = "trade";
			link.l2 = "Clear. It is time me to go. It was pleasant to become acquainted!";
			link.l2.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
			NextDiag.TempNode = "First time";
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
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("And you, "+GetFullName(pchar)+" thief, the nicest!!!", "Blimey! I gazed hardly, and you at once on trunks! Hold a thief!!!", "Guard! Rob!!! Catch a thief!!!");
			link.l1 = "Did not drive me!!!";
			link.l1.go = "fight";
		break;
	}
}