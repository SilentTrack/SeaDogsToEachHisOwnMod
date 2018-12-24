void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref PChar;
	PChar = GetMainCharacter();

    string ret;
    
	switch(Dialog.CurrentNode)
	{
		case "exit":
			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
		break;

		case "start":
			dialog.text = "Wake up, " + Pchar.name + "! We have reached the "+ Pchar.HeroParam.Land +" destination at last after all of these storms!"+
                          "  What are you going to do now? You've lost your ship.";
			link.l1 = "Not my first time! Fortune is a bitch.";
			link.l1.go = "start1";
			link.l2 = "Do you want to offer me a job, Abraham?";
			link.l2.go = "start2";
		break;

		case "start1":
			dialog.text = "I hope that you'll have more like than with yours 'Mercury'. Farewell.";
			link.l1 = "No doubt in that. Farewell, captain!";
			link.l1.go = "game_begin";
		break;
		
		case "start2":
            ret = Pchar.name + ", I am a smuggler not a mayor.";
            if (sti(Pchar.nation) == PIRATE)
            {
                dialog.text = ret + " Check up the Inness's tavern. She is aware about everyone in the town."+
                              "  Go to Urksen, he is the leader here. But have a talk with local pirates first.";
            }
            else
            {
                dialog.text = ret + " Borrow some coin, sell your stuff. You know what to do.";
            }
            link.l1 = "Fine, thanks for an advice. Farwell.";
			link.l1.go = "game_begin";
			link.l2 = "You know, Abraham, I'd better take your ship. I kind of like it!";
			link.l2.go = "start3";
		break;
		
		case "game_begin":
			DialogExit();
            addDialogExitQuest("Tut_SkipTutorialOnShip");
		break;
		
		case "start3":
			dialog.text = "Bad joke, pal.";
			link.l1 = "Don't worry , old man. Farewell!";
			link.l1.go = "game_begin";
			link.l2 = "Who said that I was joking? You tell your people that you've sold your vessel to me. And I'll spare your life. Deal?";
			link.l2.go = "start4";
		break;
		
		case "start4":
			dialog.text = "They say that you've murdered your master Malcolm Hatcher for a cheap saber. I thought that it was just a bubble talk. Such a fool I was. You'll be feeding fish tonight, lad. You have got no chance.";
			link.l1 = "O really?";
			link.l1.go = "exit";
			addDialogExitQuest("Tut_KillOnShip");
		break;

		case "First time":
			dialog.text = "";
			Link.l1 = "Oops...";
			Link.l1.go = "exit";
		break;

////////////////////////////////////////////////////////////////////////////////
//	Корсарское метро
////////////////////////////////////////////////////////////////////////////////
		case "Travel_talkStart":
            NPChar.location = "none"; // чтоб на палубе не болтался
			//Шанс на то что продадут на рудники.
			int iRnd = (rand(100) == 30);
			if (iRnd)
			{
				dialog.text = "We have an idea to sell you as a slave. Ha.. Money are always useful.";
				link.l1 = "You don't say?";
				//заглушка, пока нет рудников.
				link.l1.go = "Travel_fight";
				//"Travel_mine"; //Собственно тоже можно боевку организовать, ГГ сопротивляется.
			}
			else
			{
				dialog.text = "We've reached our destination. Farewell.";
				link.l1 = "Farewell.";
				link.l1.go = "Travel_end";
				link.l2 = "I like your ship. Want to keep it to myself.";
				link.l2.go = "Travel_fight";
			}
		break;

		case "Travel_fight":
			ChangeContrabandRelation(pchar, -60);

			LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_SetCheck("TmpEnemy", "Travel_AfterDeckFight");
			LAi_group_FightGroups(LAI_GROUP_PLAYER, "TmpEnemy", true);
			LAi_SetPlayerType(PChar);
			//Вытащим саблю
   			LAi_SetFightMode(Pchar, true);

			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
			LAi_SetWarriorTypeNoGroup(NPChar);
		break;

		case "Travel_end":
			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
			//Квест бук
			AddQuestRecord("Gen_ContrabandTravel", "4");
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt")));


			LAi_SetPlayerType(PChar);
			//грузим ГГ куда нужно.... 
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc,
									pchar.GenQuest.contraTravel.destination.group,
									pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
			CloseQuestHeader("Gen_ContrabandTravel");
			//трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
		break;
	}
}
