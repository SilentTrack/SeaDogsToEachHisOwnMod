void ProcessDialogEvent()
{
	ref NPChar, her;
	aref Link, NextDiag;
	bool bOk = false;
    bool bOk2;
    
	int Sum, nRel, nDay, iChurchQuest2_Summ;
	ref sld;
	
	
	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra"))
	{
		iChurchQuest2_Summ = sti(PChar.rank)*100 + (rand(3)+1)*100;
		PChar.GenQuest.ChurchQuest_2.Summ_To_Contra = sti(iChurchQuest2_Summ);
	}
	
	
	string sColony;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

	
	if (CheckAttribute(pchar, "GenQuest.contraTravel.days") && GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
	{
		DeleteAttribute(pchar, "GenQuest.contraTravel");
		CloseQuestHeader("Gen_ContrabandTravel");
	}

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Smuggling_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			PlaceSmugglersOnShore(Pchar.quest.contraband.CurrentPlace);
			Pchar.quest.Contraband.active = true;
			pchar.GenQuest.Contraband.GuardNation = npchar.nation;
			pchar.GenQuest.Contraband.SmugglerId  = npchar.id;				
			SetAllContraGoods(&Stores[sti(Pchar.GenQuest.Contraband.StoreIdx)], npchar);
			ReOpenQuestHeader("Gen_Contraband");
            if (GetIslandByCityName(npchar.city) == "Mein")
            {
            	AddQuestRecord("Gen_Contraband", "t1_1");
            }
            else
            {
	            AddQuestRecord("Gen_Contraband", "t1");
				AddQuestUserData("Gen_Contraband", "sIsland", XI_ConvertString(GetIslandByCityName(npchar.city)));
			}
			AddQuestUserData("Gen_Contraband", "sLoc", GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt"));
				
			DialogExit();
		break;
		
		case "First time":											
			
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
            {
				dialog.text = "Monsieur, leave this place. I doubt that we have anything to talk about.";
				link.l1 = "Oh, really? You don't like my face? Fine, I am leaving...";
				link.l1.go = "exit";
				break;
			}
			
			
			if (CheckAttribute(pchar, "GenQuest.SmugglersBlock") && pchar.GenQuest.SmugglersBlock == npchar.location)
            {
				dialog.text = "������� ������� ������ �� �����.";
				link.l1 = "�������.";
				link.l1.go = "exit";
				break;
			}
			
			
			if (CheckAttribute(pchar, "questTemp.Consumption.Contra"))
            {
				dialog.text = "What do you want, captain?";
				link.l1 = "Can we talk a bit?";
				link.l1.go = "Consumption";
				break;
			}
			
			
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "What do you want, captain? I don't know your name and I can't tell you mine.";
				Link.l1 = "I am captain " + GetFullName(pchar) + ".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1"; 
			}
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 1)
				{
					if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
					{
						pchar.GenQuest.CaptainComission.SpeakContra = true;
						dialog.text = "No business today. There are patrols at every bay, our governor is looking for a cargo which was confiscated by some captain of" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " and stashed by him somewhere.";
						link.l1 = "And where is this captain" + pchar.GenQuest.CaptainComission.Name + "?";
						link.l1.go = "CapComission_1";
						break;
					}
					else
					{
						dialog.text = "No business today.";
						link.l1 = "I see.";
						link.l1.go = "exit";					
						break;
					}
				}

				if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
				{
					dialog.text = "No business today.";
					link.l1 = "I see.";
					link.l1.go = "exit";
					break;
				}

				Dialog.Text = "What do you want, captain?";
				if (LAi_group_GetPlayerAlarm() > 0)
				{
	       			Dialog.Text = RandPhraseSimple("Be swift, "+ GetSexPhrase("pal","girl") +", what do you want? They are chasing you!", "Speak your business and do it quickly!  Soldiers are chasing you and we don't have much time...");
				}
				
				if(FindContrabandGoods(PChar) != -1)
				{
					Link.l1 = "I'd like to buy or sell something.";
					Link.l1.go = "Meeting_3";
				}

				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
					Link.l2 = "About the trip...";
				else
					Link.l2 = "I need to get to one place.";
				Link.l2.go = "Travel";
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakSmuggler"))
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l3 = "I have got a 'special' stuff and I think that you would be interested. Take a look!";
						link.l3.go = "SM_ShipLetters_1";
					}	
				}				

				
				if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
				{
					Link.l8 = "I have got an unusual business for you.";
					Link.l8.go = "Shadowtrader_smugglers";
				}
				
				
				if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
				{
					Link.l9 = "I need to meet with Michael Rosenkraft. I've got the cargo which is interesting for him.";
					Link.l9.go = "bakaut";
				}
				
				
				
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					Link.l4 = "I need to find one thing out, pal.";
					Link.l4.go = "Contra_GenQuest_Church_2_1";
				}
				
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
				{
					Link.l5 = "A colleague of yours and my good friend from  " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + " told that you are aware of some business.";
					Link.l5.go = "Contra_GenQuest_Church_2_Contra2_1";
				}
				
				
				Link.l7 = "Nothing. See you.";
				Link.l7.go = "Exit";				
			}
		break;
		
		case "CapComission_1":
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				dialog.text = "In the fort's basement where else?.. That captain can reveal the stash to authorities any time and there is nothing will be left for us. Don't think about any business until this fuss is over.";
				link.l1 = "Listen, you know every single piece of this island. Do you really have no idea where the captain " + pchar.GenQuest.CaptainComission.Name + "stash is?";
				link.l1.go = "CapComission_4";
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				dialog.text = "At the heavens I guess. He was hanged with his crew. But they didn't mentioned in death sentence that it was a pirate vessel.";
				link.l1 = "And why are you so sure that the vessel was a pirate one?";
				link.l1.go = "CapComission_2";
			}	
		break;
		
		case "CapComission_2":
			dialog.text = "We had been watching the fight from the rock. Them, like five hours later, we saw a flash in the dark, it looked a blow of the magazine. Enough time to move the cargo to the shore.";
			link.l1 = "Don't you know where is the captain's " + pchar.GenQuest.CaptainComission.Name +" stash? You know every piece of this island.";
			link.l1.go = "CapComission_3";
		break;
		
		case "CapComission_3":
			dialog.text = "No. And we are looking for it too but we not for governor's amusement...";
			link.l1 = "I see.... Have a nice day.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "38");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")));
		break;
		
		case "CapComission_4":
			dialog.text = "No. And we are looking for it too but we not for governor's amusement... he-he";
			link.l1 = "I see... Have a nice day.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "19");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		break;
				
		case "SM_ShipLetters_1":
			pchar.questTemp.different.GiveShipLetters.speakSmuggler = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Why? I am an honest coaster. Look for another buyer.";
				link.l1 = "Thanks...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Why not? Maybe I'll find a use for your 'cargo'. Take " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " coins and forget about it.";
					link.l1 = "No, thanks.";
					link.l1.go = "SM_ShipLetters_2";	
					link.l2 = "And you have guessed that correctly I am starting to forget that!";
					link.l2.go = "SM_ShipLetters_3";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Exactly! I am really curious now. I suppose that if I'll pay you "+ sti(pchar.questTemp.different.GiveShipLetters.price3) +" coins you won't care at all about that papers.";
						link.l1 = "No, thanks.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "And you have guessed that correctly I am starting to forget that!";
						link.l2.go = "SM_ShipLetters_3";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Now, that's a chance to catch that insolent fellow! I am really, really curious. Look I'll pay you " + sti(pchar.questTemp.different.GiveShipLetters.price4) + " in gold and you will pretend that you have forgot about documents?";
						link.l1 = "I won't.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "And you have guessed that correctly I am starting to forget that!";
						link.l2.go = "SM_ShipLetters_3";
					}
				}
			}
		break;
		
		case "SM_ShipLetters_2":
			dialog.text = "Alright, alright but stop making more enemies.";
			link.l1 = "Same to you!";
			link.l1.go = "exit";
		break;
		
		case "SM_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; 
			AddQuestRecord("GiveShipLetters", "7");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Meeting":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 2)
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
				{
					pchar.GenQuest.CaptainComission.SpeakContra = true;
					dialog.text = "No business today. There are patrols at every bay, our governor is looking for a cargo which was confiscated by some captain of" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " and stashed by him somewhere.";
					link.l1 = "And where is this captain" + pchar.GenQuest.CaptainComission.Name + "?";
					link.l1.go = "CapComission_1";
					break;
				}
				else
				{
					dialog.text = "No business today.";
					link.l1 = "I see.";
					link.l1.go = "exit";					
					break;
				}
			}
			
			if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
			{
				dialog.text = "No business today.";
				link.l1 = "I see.";
				link.l1.go = "exit";
				break;
			}
			
			Dialog.Text = "How can I help you, captain?";
			
			if(FindContrabandGoods(PChar) != -1)
			{
				Link.l1 = "I want to buy or sell stuff.";
				Link.l1.go = "Meeting_1";
			}
			
			Link.l2 = "I need to get to one place.";
			Link.l2.go = "Travel";				
			
			
			if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
			{
				Link.l8 = "I've got a quite unusual business for ya.";
				Link.l8.go = "Shadowtrader_smugglers";
			}
			
			
			if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
			{
				Link.l9 = "I need to meet with Michael Rosenkraft. I've got the cargo which is interesting for him.";
				Link.l9.go = "bakaut";
			}
			
			
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				Link.l3 = "I need to find one thing out, pal.";
				Link.l3.go = "Contra_GenQuest_Church_2_1";
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
			{
				Link.l3 = "A colleague of yours and my good friend from  " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + " told that you are aware of some business.";
				Link.l3.go = "Contra_GenQuest_Church_2_Contra2_1";
			}
			

			Link.l5 = "Nothing. See you.";
			Link.l5.go = "Exit";				
		break;

		
		case "Contra_GenQuest_Church_2_1":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			dialog.text = "I am not a friend for ya. And it can cost you.";
				link.l1 = "Hm. I need to know something which costs not more than " + FindRussianMoneyString(iChurchQuest2_Summ) + ".";
				link.l1.go = "Contra_GenQuest_Church_2_2";
			break;
			
		case "Contra_GenQuest_Church_2_2":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			if(sti(PChar.money) >= iChurchQuest2_Summ)
			{
				dialog.text = "Give me your coins. And know that you won't get much for a sum like this.";
				link.l1 = "See, I missed my friends. I was late for a meeting, and they didn't wait for me...";
				link.l1.go = "Contra_GenQuest_Church_2_3";
				AddMOneyToCharacter(PChar, -iChurchQuest2_Summ);
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra");
			}
			else
			{
				dialog.text = "Ha, you don't have a coin! Come when you'll get some money.";
				link.l1 = "Exactly.";
				link.l1.go = "exit";
			}
			break;
			
		case "Contra_GenQuest_Church_2_3":
				dialog.text = "And why do you need me?";
				link.l1 = "They are not in the city and they don't own a ship. That is why I thought: maybe some of your business partners did them a favor?";
				link.l1.go = "Contra_GenQuest_Church_2_4";
			break;
			
		case "Contra_GenQuest_Church_2_4":
			sColony = QuestGetColony(PChar.GenQuest.ChurchQuest_2.QuestTown);
			dialog.text = "I see... Met a few guys, they told that they need to get away from the island and they didn't care where to. We don't ask reasons in such case, only about payment. We had a voyage to " + XI_ConvertString("Colony" + sColony + "Acc") + " , " + XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Dat") + " . We can get you there, if we agree on money.";
			link.l1 = "Thanks, I have got my own ship.";
			link.l1.go = "exit";
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "8");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","�"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + sColony + "Acc"));
			AddQuestUserData(sQuestTitle, "sIsland", XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Dat"));
			PChar.GenQuest.ChurchQuest_2.AskContra_2 = true;
			PChar.GenQuest.ChurchQuest_2.Contra_Colony = sColony;
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_1":
			dialog.text = "Never had a business with ya.";
			link.l1 = "We can fix it. You brought my friends here not long ago. I missed with "+ GetSexPhrase("them","them") +".";
			link.l1.go = "Contra_GenQuest_Church_2_Contra2_2";
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_2":
			string sGenLocation = IslandGetLocationFromType(locations[FindLocation(PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_Town")].IslandID, "Shore");
			PChar.GenQuest.ChurchQuest_2.QuestGangShore = sGenLocation;
			PChar.GenQuest.ChurchQuest_2.BanditsInShore = true;
			dialog.text = "Hm, we put them ashore at " + XI_ConvertString(sGenLocation + "Dat") + "... You know, they better would be your friends, otherwise I don't advice to bother them.";
			link.l1 = "Thanks for your concerns but I've got my equipment.";
			link.l1.go = "exit";
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "9");
			AddQuestUserData(sQuestTitle, "sShore", XI_ConvertString(sGenLocation + "Acc"));
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			SetFunctionTimerCondition("Church_GenQuest2_TimeIsLeft", 0, 0, 1, false);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2");
		break;
		

		case "Meeting_1":
			Dialog.Text = "Hm... and how does it concern me? You have probably lost yourself, captain. Go to the shop and sell or buy there whatever you wish.";
			Link.l1 = "No, I need you.";
			Link.l1.go = "Meeting_2";				
			Link.l2 = "Thanks for your advice. Have I nice day.";
			Link.l2.go = "exit";				
		break;

		case "Meeting_2":
			Dialog.Text = "For what?";
			Link.l1 = "Perhaps you will be interested in some special goods? Or perhaps you have got something to offer me instead?"
			Link.l1.go = "Meeting_3";				
		break;

		case "Meeting_3":
			int iTmp = false;
			int iChIdx, i;

			
			for (i=0; i<COMPANION_MAX; i++)
			{
				iChIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iChIdx>=0)
				{
					sld = GetCharacter(iChIdx);
            		if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
				}
			}
			
			if (iTmp)
			{
				dialog.text = NPCStringReactionRepeat("Why won't you take a royal man-of-war next time. You vessel can be spotted from the fort easily. We won't risk our heads. Come on a single small ship next time.", 
					"Should I repeat myself? Find a smaller ship and then we will talk.", 
					"Are you really that idiot? Find yourself a schooner or a brig. Only in that case we'll have business.",
					"Oh, such an idiot...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Fine, I understood you.", 
					"I get it, I only wanted to specify something.",
					"No, not an idiot, just a scrooge. Thought that something has changed. I'd take a few more pinnaces�", 
					"You see...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
				break;
			}
			bOk  = CheckAttribute(pchar, "GenQuest.contraTravel.active") && (sti(pchar.GenQuest.contraTravel.active) == true);
			bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
			bool bOk3 = CheckAttribute(Pchar, "questTemp.pirateStartQuest") && (Pchar.questTemp.pirateStartQuest == "3");
			if (bOk)
			{
			    if (GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
				{  
					DeleteAttribute(PChar, "GenQuest.contraTravel");
					CloseQuestHeader("Gen_ContrabandTravel");
					bOk = false;
				}
			}


			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "Sorry, "+ GetSexPhrase("pal","girl") +", we are busy already. Come back in a few days.";
				Link.l1 = "To bad...";
				Link.l1.go = "Exit";		
				break;
			}


			if (bOk || bOk2 || bOk3)
			{
				Dialog.Text = "How about finish our current business first?";
				Link.l1 = "I suppose you are right.";
				Link.l1.go = "Exit";				
			}
			else
			{
                if (npchar.quest.trade_date != lastspeak_date)
    			{
                    npchar.quest.trade_date = lastspeak_date;
                    
                    if (ChangeContrabandRelation(pchar, 0) > 5)
                    {
                        Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
						Pchar.quest.contraband.City = NPChar.city;
                        if (Pchar.quest.contraband.CurrentPlace != "None")
                        {
                            if (ChangeContrabandRelation(pchar, 0) >= 70)
                            {
                                Dialog.Text = "I know that we can do business with you. We will wait at " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
                            }
                            else
                            {
            				    Dialog.Text = "Hm... Perhaps we can find you a buyer. We will wait you at " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
            				}
            				Link.l1 = "Alright. See you.";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   
                            Dialog.Text = "No business today. Come here tomorrow.";
            				Link.l1 = "Fine.";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = "Do you really think that anyone will want to work with you after all of that? You'd better be glad that we didn't send the bounty hunters for you.";
        				Link.l1 = "Too bad. No chance for me to become a smuggler.";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    Dialog.Text = "No business today. Come here tomorrow.";
    				Link.l1 = "Fine.";
    				Link.l1.go = "Exit";
				}
			}
		break;



		case "Travel":

			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "Sorry, "+ GetSexPhrase("pal","girl") +", we are busy already. Come back in a few days.";
				Link.l1 = "Too bad.";
				Link.l1.go = "Exit";		
				break;
			}

			
			if (sti(pchar.ship.type) == SHIP_NOTUSED && GetCompanionQuantity(pchar) == 1 && GetPassengersQuantity(pchar) == 0)
			{
				
				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
				{
					
					if (CheckAttribute(pchar, "GenQuest.contraTravel.payed") && sti(pchar.GenQuest.contraTravel.payed) == true)
					{
						Dialog.Text = "I thought that we have already arranged the deal?";
						Link.l2 = "Indeed!";
					}
					
					else
					{
						if(GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = "I brought money?";
							Link.l1 = "Yes.";
							Link.l1.go = "Travel_pay";
							Link.l3 = "I've changed my mind...";
							Link.l3.go = "Travel_abort";
							Link.l2 = "Not yet.";
						}
						else
						{
                            if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
							{
								Dialog.Text = "I have already told you everything.";
								Link.l2 = "Exactly.";
								Link.l1 = "I've changed my mind...";
								Link.l1.go = "Travel_abort";
							}
							else 
							{
							    Dialog.Text = "Can't help you today. Come in a two days and maybe we will get something for you.";
								Link.l2 = "Too bad.";
								DeleteAttribute(PChar, "GenQuest.contraTravel");
								CloseQuestHeader("Gen_ContrabandTravel");
							}
						}
					}
				}
				
				else
				{
					nRel = ChangeContrabandRelation(pchar, 0);
					
					if (nRel > 0 && Statistic_AddValue(PChar, "contr_TravelKill", 0) < 20)
					{
						
						pchar.GenQuest.contraTravel.CurrentPlace = SelectSmugglingLocation();
						aref arTmp; makearef(arTmp, pchar.GenQuest.contraTravel);
						SetSmugglersTravelDestination(arTmp);
						
						pchar.GenQuest.contraTravel.price = (sti(PChar.rank)*250 + (100 - nRel)*10 + rand(30)*20) + sti(arTmp.destination.days)*100;
						
						
						bOk = !bPauseContrabandMetro && CheckNPCQuestDate(npchar, "Travel_Talk") && 
							Pchar.GenQuest.contraTravel.CurrentPlace != "None" && rand(50) < nRel;
                        bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
						if (bOk && !bOk2)
						{
							nDay = 1 + rand(3);
							SetNPCQuestDate(npchar, "Travel_Talk");
							SaveCurrentQuestDateParam("contraTravel");

							Dialog.Text = "Well we can get you to the " + GetConvertStr(locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)].id, "LocLables.txt") + " near " +
								XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen") + " for " + pchar.GenQuest.contraTravel.price + " gold. Bring the money in " +
								FindRussianDaysString(nDay) + ". The ship will wait for you in the " +
								GetConvertStr(locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)].id, "LocLables.txt") + " ����� �����.";

							pchar.GenQuest.contraTravel.days = nDay;
							Link.l1 = "Works for me.";
							Link.l1.go = "Travel_agree";
							Link.l2 = "No thanks.";
						}
						else
						{
							Dialog.Text = "Can't help you today. Come in a two days and maybe we will get something for you.";
							Link.l2 = "Too bad.";
						}
					}
					
					else
					{
                        Dialog.Text = "Do you really think that anyone will want to work with you after all of that? You'd better be glad that we didn't send the bounty hunters for you. Get away!";
        				Link.l2 = "Not in this life perhaps.";
					}

				}
			}
			
			else 
			{
				if(GetPassengersQuantity(pchar) != 0)
				{
					Dialog.Text = "No we won't take you all. Only one of you.";
					Link.l2 = RandSwear() + "I don't need that anyway!";
				}
				else
				{
					Dialog.Text = "Why won't you use your own ship? No we won't take you.";
					Link.l2 = "Not in this life perhaps.";
				}
			}
			Link.l2.go = "Exit";
			break;

		
		case "Travel_abort":
			ChangeContrabandRelation(pchar, -2);
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			CloseQuestHeader("Gen_ContrabandTravel");
			Dialog.Text = "Whatever you want.";
			Link.l1 = "";
			Link.l1.go = "Exit";
			break;

		
		case "Travel_agree":
			ReOpenQuestHeader("Gen_ContrabandTravel");
			AddQuestRecord("Gen_ContrabandTravel", "1");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_ContrabandTravel", "sLoc", GetConvertStr(pchar.GenQuest.contraTravel.CurrentPlace, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sPlaceTo", XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen"));
			AddQuestUserData("Gen_ContrabandTravel", "sDays", FindRussianDaysString(sti(pchar.GenQuest.contraTravel.days)));
			AddQuestUserData("Gen_ContrabandTravel", "sPrice", pchar.GenQuest.contraTravel.price);

			
			pchar.GenQuest.contraTravel.active = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;

		
		case "Travel_pay":
			
			Sum = sti(pchar.GenQuest.contraTravel.price);
			if (sti(pchar.money) >= Sum)
			{
				AddMoneyToCharacter(pchar, -1*Sum);
				
				pchar.GenQuest.contraTravel.payed = true;
				Dialog.Text = "Nice doing business with you. Don't be late on the ship.";
				Link.l1 = "I'll try.";
				AddQuestRecord("Gen_ContrabandTravel", "2");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("",""));
				
				
				PlaceSmugglersOnShore(PChar.GenQuest.contraTravel.CurrentPlace);
				
				Sum = sti(pchar.GenQuest.contraTravel.destination.days);
				sld = GetCharacter(NPC_GenerateCharacter("Abracham_Gray", "citiz_46", "man", "man", 5, PIRATE, Sum + 2, true, "hunter"));
				
				sld.nation = PIRATE;
				SetRandomNameToCharacter(sld);
				SetMerchantShip(sld, rand(GOOD_PAPRIKA));
				SetFantomParamHunter(sld);
				SetCaptanModelByEncType(sld, "pirate");
				SetCharacterShipLocation(sld, PChar.GenQuest.contraTravel.CurrentPlace);

				SetTimerCondition("RemoveTravelSmugglers", 0, 0, 1, false);
			}
			
			else
			{
				Dialog.Text = "It looks like you don't have enough coin."
				Link.l1 = "What a shame, I'll be back later.";
			}
			Link.l1.go = "Exit";
		break;  



				
		
		case "Shadowtrader_smugglers":
			dialog.text = "Very interesting. Show what you have got.";
			link.l1 = "I have heard that there is an underground shop where you can trade very 'special' goods with a tempting price and you have helped to start this shop. I'd like to talk with it's owner.";
			link.l1.go = "Shadowtrader_fail";
			link.l2 = "I have heard that there is an underground shop where you can trade very 'special' goods with a tempting price. I've got to sail in a few days and want to save some coin...";
			link.l2.go = "Shadowtrader_smugglers_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.seeksmugglers");
		break;
		
		case "Shadowtrader_fail":
			dialog.text = "What are you talking about? I don't get you. We didn't start a shop here this is nonsense, ha-ha! If you want to trade then bring us goods and we will talk in our usual way... A shop, ha!";
			link.l1 = "Hm...";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			AddQuestRecord("Shadowtrader", "3");
			CloseQuestHeader("Shadowtrader");
		break;
		
		case "Shadowtrader_smugglers_1":
			dialog.text = "Want a discount? Easy. Come at the harbor master's door when it's dark. Our man will meet you and take you to the right place. ";
			link.l1 = "Sure. I will be there!";
			link.l1.go = "Shadowtrader_smugglers_2";		
		break;
		
		case "Shadowtrader_smugglers_2":
			pchar.questTemp.Shadowtrader.SeekTrader = "true";
			AddQuestRecord("Shadowtrader", "5");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			SetFunctionTimerCondition("ShadowtraderTimeSmugglers_Over", 0, 0, 2, false);
			int iNation = pchar.questTemp.Shadowtrader.nation;
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+3;
			sld = GetCharacter(NPC_GenerateCharacter("ShadowAgent_1", "citiz_"+(rand(9)+41), "man", "man", iRank, iNation, 2, true, "quest"));
			SetFantomParamFromRank(sld, iRank, true);
			GiveItem2Character(sld, "blade_04");
			EquipCharacterbyItem(sld, "blade_04");
			LAi_SetCitizenType(sld);
			sld.dialog.Filename = "Common_citizen.c";
			sld.dialog.currentnode = "First time";	
			sld.greeting = "cit_common"; 
			sld.city = pchar.questTemp.Shadowtrader.City;
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City +"_town", "goto", "goto1");
			pchar.quest.Shadowtrader_SMG.win_condition.l1 = "locator";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.location = pchar.questTemp.Shadowtrader.City + "_town";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.locator_group = "reload";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.locator = "reload10_back";
			pchar.quest.Shadowtrader_SMG.win_condition.l2 = "Night";
			pchar.quest.Shadowtrader_SMG.function = "ShadowAgent";
			DialogExit();
		break;
		
			
		
		case "Consumption":
			dialog.text = "There are plenty of revelers here and if you've got no business, sir, drink or prate with them. This place is busy.";
			link.l1 = "Let's try again.  I will pay you for your time and my curiosity. I need answers.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			if (sti(pchar.money) >= 3002)
			{
				dialog.text = "He'll pay, ha! My time is not cheap, sir, it costs 3000 pesos plus this disgusting drink which they call a rum by mistake.";
				link.l1 = "Deal! Now tell me about one of your own who spent half of a year in the local prison and then passed over. What happened with him?";
				link.l1.go = "Consumption_2";
			}
			else
			{
				dialog.text = "You'd better fill your pockets with silver or gold which would be better. Then come and talk I have no time chatting with you for free.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3002);
			dialog.text = "I remember that though I don't understand why are you interested in this. The kid really has gone crazy in this undergrounds. He become a drunkard and was always talking some nonsense about consumption which takes people away and nobody is aware of it. He said that this consumption has a name and don't you dare to say it in loud. If you do - it will come and take you too.";
			link.l1 = "And what happened with him next?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "The story has an odd end, senior. At first, locals and sailors liked his tale, but eventually they had fed up with it. That always happens with any fable. So they provoked him to say the name. The guy was bucking and resisting but couldn't  bear mocking and literally cried it out\nNobody felt anything special, candles didn't die out, but the poor soul was found next morning behind the tavern with his throat cut.";
			link.l1 = "I don't see any magic here. Tell me the name.";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "I remember the name, but damn, I ain't going to say it out loud. There is something sinister in all of this. Don't you see that?";
			link.l1 = "Hey, pal, you have received a wallet full of coins from me, remember? So would you kindly tell me the name?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Oh it won't end well, senor, trust me... (lowering his voice) He said - Juan...";
			link.l1 = "Damn with you! Juan? It's just an ordinary name and it's quite popular here. Why is it so special?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Don't know, but the man who said this name was killed. Trust my guts, something is very wrong with the name. Is that all what you have wanted to know?";
			link.l1 = "I suppose so. You can buy a drink for yourself. See you!";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Consumption.Contra");
			pchar.questTemp.Consumption.AskJuan = 0;
			pchar.questTemp.Consumption = "current";
			AddQuestRecord("Consumption", "6");
		break;
		
		
		
		case "bakaut":
			dialog.text = "Is that so? Fine. Mynheer Rosenkraft need a batch of ironwood but not less than "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+". Do you have enough cargo?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "I do. Where can I find mynheer Rosenkraft?";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Hm. I don't have that much right now.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			dialog.text = "Don't disturb mynheer Rosenkraft then. Come when you'll have enough cargo.";
			link.l1 = "Fine.";
			link.l1.go = "exit";
		break;
		
		case "bakaut_1":
			dialog.text = "His galleon will be cruising close to the shores of "+XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen")+" for several days. So don't get too late - he might sail to another place of the archipelago.";
			link.l1 = "Alright, I'll speed up. Thanks!";
			link.l1.go = "bakaut_2";
		break;
		
		case "bakaut_2":
			DialogExit();
			sld = characterFromId("Rozencraft");
			sld.DeckDialogNode = "bakaut";
			DeleteAttribute(sld, "DontDeskTalk"); 
			pchar.GenQuest.Bakaut.Info = "true";
			ReOpenQuestHeader("Bakaut");
			AddQuestRecord("Bakaut", "1");
			AddQuestUserData("Bakaut", "sIsland", XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen"));
			AddQuestUserData("Bakaut", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Bakaut.DaysQty)));
			AddQuestUserData("Bakaut", "sQty", FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)));
			
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1 = "Timer";
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.function = "Bakaut_RozencraftRemove";
		break;
		
	}
}

