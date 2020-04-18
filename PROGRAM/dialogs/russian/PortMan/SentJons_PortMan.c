
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "What do you want? A-ha, you are the participant of the regatta! Am I right?";
				link.l1 = "Exactly, mister. I need to get registered here according to the rules.";
				link.l1.go = "Regata_check";
				break;
			}
			
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "You've already tried to ask me a question " + GetAddress_Form(NPChar) + "...", "You have been talking about some question for the third time today...",
                          "Look, if you have nothing to tell me about the port's matters then don't bother me with your questions.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind.", "Sorry!"), "Sorry!", "Pardon!", "Sorry!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
		{
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Portpax") || GetCompanionQuantity(pchar) > 1 || sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_LUGGER || pchar.Ship.Name != "Santa Catherina")
			{
			dialog.text = "Hm... You have broken the rules of regatta and I have to disqualify you. I am sorry. You are not participating in the next voyage. I have already prepared a dispatch to Port-Royal.";
			link.l1 = "Eh... what a shame! But I can't do anything here, you were too vigilant. Farewell!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			}
			else
			{
			pchar.questTemp.Regata.ThirdTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
			dialog.text = "Let's register: captain "+ GetFullName(pchar) +", ship is - "+pchar.Ship.Name+"... Regatta's time in hours is "+sti(pchar.questTemp.Regata.ThirdTransitionTime)+". Done, your result if registered, you can continue your way.";
			link.l1 = "Tell me my rank.";
			link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "You are here but I don't see your ship. Where is it?";
			link.l1 = "I am sorry, sir. I will transfer my ship to the port immediately.";
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				if (pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.ThirdTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);
				}
			}
			if (n==1)
			{
			dialog.text = "You are in the lead. Congratulation! Keep it up!";
			link.l1 = "Thanks!";
			link.l1.go = "exit";
			}
			else
			{
				if (n==6)
				{
				dialog.text = "You are the last. You should hurry up.";
				link.l1 = "I am on my way!";
				link.l1.go = "exit";
				}
				else
				{
					if (n==2)
					{
					dialog.text = "You are the second. The leader is "+sName+" on the ship "+sShip+". I suppose that you can still outrun him.";
					link.l1 = "Thanks! I'll be trying!";
					link.l1.go = "exit";
					}
					else
					{
					dialog.text = "You rank is "+n+". Your closest opponent is "+sName+" on the ship "+sShip+".";
					link.l1 = "Thanks!";
					link.l1.go = "exit";
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);
			AddCharacterExpToSkill(pchar, "Defence", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
			AddCharacterExpToSkill(pchar, "Sneak", 30);
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Sentjons = "true";
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Guadeloupe";
			pchar.quest.Regata_Check1.function = "RegataCheck";
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Martinique";
			pchar.quest.Regata_Check2.function = "RegataCheck";
			pchar.quest.Regata_Check3.win_condition.l1 = "location";
			pchar.quest.Regata_Check3.win_condition.l1.location = "Dominica";
			pchar.quest.Regata_Check3.function = "RegataCheck";
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Barbados";
			pchar.quest.Regata_Check.function = "RegataCheck";
			pchar.questTemp.Regata.AttackIsland = "Guadeloupe";
			pchar.questTemp.Regata.AttackNation = PIRATE;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Guadeloupe";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";
			pchar.quest.Regata_Attack1.win_condition.l1 = "location";
			pchar.quest.Regata_Attack1.win_condition.l1.location = "Guadeloupe";
			pchar.quest.Regata_Attack1.function = "RegataAttack_Brigantine";
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Martinique";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";
			pchar.questTemp.Regata.Town = "Bridgetown";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload11_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";
			
			pchar.quest.Regata_SpgGirl.win_condition.l1 = "location";
			pchar.quest.Regata_SpgGirl.win_condition.l1.location = "Sentjons_town";
			pchar.quest.Regata_SpgGirl.function = "RegataSpyglassGirl";
			pchar.quest.Regata_Attack2.win_condition.l1 = "location";
			pchar.quest.Regata_Attack2.win_condition.l1.location = "Antigua";
			pchar.quest.Regata_Attack2.function = "RegataAttack_Brander";
			i = FindColony("Bridgetown");
			colonies[i].DontSetShipInPort = true; 
			pchar.quest.Regata_Siege.win_condition.l1 = "location";
			pchar.quest.Regata_Siege.win_condition.l1.location = "Barbados";
			pchar.quest.Regata_Siege.function = "RegataSiege";
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  
}



