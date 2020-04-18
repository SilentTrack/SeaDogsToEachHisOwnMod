
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    
    
    

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "First time":
			location = &Locations[FindLocation(pchar.location)];
			if (rand(4) == 4 && GetNpcQuestPastDayParam(location, "gun_date") > 365 && !CheckAttribute(pchar, "questTemp.PrisonGun"))
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Listen, I have an important business with you. Hope you'd be able to help.","Captain, may I interest you with one quite a profitable offer?"), RandPhraseSimple("I just thought you could have helped us in one important affair.","Captain, I have a delicate offer for you, which could be quite profitable for both of us."));					
				link.l1 = "Well, speak your mind, and we'll see...";
				link.l1.go = "GiveTaskGun";
				location.quest.PrisonGun = "Target"; 
				SaveCurrentNpcQuestDateParam(location, "gun_date");
				break;
			}
		
			dialog.text = RandPhraseSimple("I am the commandant of the fort. What do you need here?", "What do you need? What have you come here for?");
			link.l1 = "Oh, nothing, just looking around. I dropped in here just by a lucky chance.";
			link.l1.go = "exit";
			
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_ammo" && GetQuestPastDayParam("questTemp.Wine_bottle") < 5)
			{
				link.l11 = "I have business with you, officer. It might be of some interest to you. One of your soldiers, "+pchar.questTemp.Wine.SName+" attempted to purchase wine in the city through my mediation. Considering your orders...";
				link.l11.go = "Wine_prison";
			}
			
			
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "fraht" && NPChar.location == "portpax_ammo")
			{
				link.l11 = "Hello, officer. I came from the colony of Basse-Terre, from a man by the name of Gerard LeCroix. There is a cargo of gunpowder and bombs for you in my hold...";
				link.l11.go = "trial";
			}
			
			if (pchar.location == "Cumana_Ammo")
			{
				if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
				{
					link.l1 = "You look worried, officer. How can I help you?";
					link.l1.go = "zpq_prs1";
				}
				if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 50000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
				{
					link.l2 = "I'm ready to report that the whole load of gunpowder is delivered. My ship is ready for unloading.";
					link.l2.go = "zpq_ex";
				}
				if (pchar.questTemp.zpq == "begin")
				{
					link.l3 = "I want to reject our gunpowder deal. This is too troublous.";
					link.l3.go = "zpq_fld2";
				}
			}
			
			NextDiag.TempNode = "First time";
		break;

		
		case "GiveTaskGun":
			dialog.Text = LinkRandPhrase("You see, the fort cannons are quite worn out. The treasury assigned funds to replace them, but I simply have no idea, where to purchase the new ones: there's simply no way to find them in our colony in the amount required. So, I thought that the guns from the ships we'd boarded could be quite useful to you.","I need to replace the gun battery of the fort. The funds have already been allocated, but, you know... It's just impossible to purchase the necessary amount in our colony.","I was tasked with the replacement of the worn fort cannons, but I just don't seem to be able to find enough anywhere.");
			Link.l1 = "Hmm... Can you go into a little bit more detail? Calibre, amount, price?";
			Link.l1.go = "GiveTaskGun_1";
			pchar.questTemp.PrisonGun = true;
			SaveCurrentQuestDateParam("pchar.questTemp.PrisonGun");
		break;
			
		case "GiveTaskGun_1":
			GetGunType();
			pchar.questTemp.PrisonGun.Sum = makeint(sti(pchar.questTemp.PrisonGun.Price)*sti(pchar.questTemp.PrisonGun.Qty));
			pchar.questTemp.PrisonGun.Luck = rand(4);
			pchar.questTemp.PrisonGun.Id = npchar.location;
			dialog.Text = "I need "+ pchar.questTemp.PrisonGun.Text +", in the amount of " + sti(pchar.questTemp.PrisonGun.Qty) + "  units exactly. I'll be paying in golden doubloons, "+ sti(pchar.questTemp.PrisonGun.Price) +" apiece. That would amount to " + FindRussianDublonString(sti(pchar.questTemp.PrisonGun.Sum)) + " in total. What say you? Oh, and one more thing - I will accept the entire batch, but no sooner than in a month - the money has not arrived yet.";
			Link.l1 = RandPhraseSimple("No, officer, your offer didn't interest me at all... I am sorry.","It's tempting, but I think I'll pass. Allow me to keep my reasoning to myself.");
			Link.l1.go = "exit_gun";
			Link.l2 = RandPhraseSimple("Well, that offer is certainly an interesting one. Consider it a deal.","I guess I'll take it. It's not that hard and clearly profitable.");
			Link.l2.go = "GiveTaskGun_2";
		break;
			
		case "exit_gun":
			dialog.Text = "A pity, captain, I was counting on you. And... I do hope that this conversation stays inside the fort?";
			Link.l1 = "You didn't have to remind me about that. Best  regards.";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
			
		case "GiveTaskGun_2":
			dialog.Text = "Well, then that's a bargain. I am not restricting you to certain terms, but please try not to prolong it over a half a year. And I hope you understand that this is strictly confidential?";
			Link.l1 = "Of course I do. Until we meet again.";
			Link.l1.go = "exit";	
			ReOpenQuestHeader("PrisonGun");
			AddQuestRecord("PrisonGun", "1");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			AddQuestUserData("PrisonGun", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("PrisonGun", "sQty", makeint(pchar.questTemp.PrisonGun.Qty));
			AddQuestUserData("PrisonGun", "sSum", makeint(pchar.questTemp.PrisonGun.Sum));
			AddQuestUserData("PrisonGun", "sText", pchar.questTemp.PrisonGun.Text);
			NextDiag.TempNode = "First time";
		break;	
		
		case "CheckGun":
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") < 30)
			{
				dialog.Text = "I told you not to come sooner than in a month!";
				Link.l1 = "Damn it! I was so busy"+ GetSexPhrase("","") +", that I lost"+ GetSexPhrase("","") +" track of time ... Sorry, I will come later, as agreed.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				break;
			}
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") > 180)
			{
				dialog.Text = "Hmm... You know, it's been over half a year since the day we've stricken our 'bargain'. I have already purchased the cannons. Did you really think that I'd be waiting for you forever?";
				Link.l1 = "Damn it! And what am I to do with them now?";
				Link.l1.go = "TakeGun_late";
				break;
			}
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = GetSquadronGoods(Pchar, iGunGoods) - sti(pchar.questTemp.PrisonGun.Qty);
			sTemp = sti(pchar.questTemp.PrisonGun.Qty);
			iTest = FindColony(NPChar.City); 
			
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.Text = "Yes, are you ready to make me happy?";
				if (amount < 0)
				{
					Link.l1 = "No, still in progress. Just wanted to make sure that our deal still stands.";
					Link.l1.go = "exit";
				}
				else
				{
					Link.l1 = "I am. The entire batch is in the hold - "+ sTemp +" units, as was agreed upon.";
					Link.l1.go = "TakeGun";
				}
			}
			else 
			{
				dialog.text = "I don't see your ship in the harbor. Are you suggesting dragging those cannons through the jungle? Make fast at our harbor and come back.";
				link.l1 = "My ship is at the other side of the island. I'll take it to the port.";
				link.l1.go = "exit";
			}
		break;
		
		case "TakeGun":
			if (pchar.questTemp.PrisonGun.Luck == 4)
			{
				dialog.Text = RandPhraseSimple("You know, it's really awkward, but I have to denounce our deal. We just had a financial inspection, and you know how scrupulous they are in such things. I just can't do anything. Sorry.","Captain, you know... Well, they have sent us cannons from the mother country, and I was forced to buy them out, of course. Exorbitant prices, of course, but... I am really sorry that I let you down... I don't feel good about it, either.");
				Link.l1 = "Damn it! And what am I to do with them now?";
				Link.l1.go = "TakeGun_no";
			}
			else
			{
				dialog.Text = RandPhraseSimple("Excellent. I will sent a party from the garrison to unload them.","Excellent. My soldiers will help you to unload the cannons.");
				Link.l1 = "Have you prepared the payment?";
				Link.l1.go = "TakeGun_1";
			}
		break;
		
		case "TakeGun_no":
			dialog.Text = "I don't know. Sell them at the shipyard, equip a trading vessel, sink them... I really have no idea. And please, don't tell  anyone about this deal.";
			Link.l1 = "You don't say so! Words fail me!";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "3");
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_late":
			dialog.Text = "I have no idea. It's your funeral. Sell them, throw them away, sink them - I really don't care.";
			Link.l1 = "Oh, that was simply a waste of time...";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "4");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("��","���"));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_1":
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = sti(pchar.questTemp.PrisonGun.Qty);
			iTemp = sti(pchar.questTemp.PrisonGun.Sum);
			dialog.Text = "Of course. Here is your gold - suit yourself.";
			Link.l1 = "Thanks! It was a pleasure doing business with you!";
            Link.l1.go = "TakeGun_2";
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(sti(pchar.questTemp.WPU.Escort.Money))+"");
			PlaySound("interface\important_item.wav");
			RemoveCharacterGoods(Pchar, iGunGoods, amount);
		break;
		
		case "TakeGun_2":
			dialog.Text = "The feeling is mutual. You've been very helpful. And, I beg you, keep this deal off the record.";
			Link.l1 = "Of course. Best wishes to you.";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "2");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("","�"));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		

		
		case "Wine_prison":
			dialog.text = "What?! I have strictly prohibited any drinking on the territory of the fort! Well, he will have to pay for this. I will deduct 1000 pesos from his allowance and will now hand them to you as a reward for your vigilance. And this guy will sit in detention for three days.";
			link.l1 = "Thank you, " + GetAddress_FormToNPC(NPChar) + ". Stopping such violations is our common duty.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 1000);
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			pchar.quest.Wine_Exchange.over = "yes";
			sld = characterFromId(pchar.questTemp.Wine.id);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			NextDiag.TempNode = "First time";
		break;
		
		
		
		case "trial":
			iTest = FindColony(NPChar.City); 
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetSquadronGoods(pchar, GOOD_BOMBS) < 2500 || GetSquadronGoods(pchar, GOOD_POWDER) < 2500)
				{
					dialog.text = "Hmm. But this batch is not full! How come?";
					link.l1 = "Damn it! Please excuse me - it's my fault. I will immediately purchase the missing amount and will hand you in the entire batch, as we agreed.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "So you are our courier? Fine. Let's sort the things out with the cargo, and then you will receive further instructions.";
					link.l1 = "Okay.";
					link.l1.go = "trial_1";
				}
			}
			else
			{
				dialog.text = "I don't see your ship in the harbor. Are you suggesting dragging the cargo through the jungle? Make fast at our harbor and come back.";
				link.l1 = "My ship is at the other side of the island. I'll take it to the port.";
				link.l1.go = "exit";
			}
		break;
		
		case "trial_1":
			pchar.quest.Trial_FrahtFail.over = "yes"; 
			dialog.text = "Alright, bombs and gunpowder, 2500 units each... Good. The soldiers will unload the cargo, your men can take a break. Here's your payment for the freight - five thousand pesos.";
			link.l1 = "Thanks! What am I to do next? Monsieur LeCroix said...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			AddMoneyToCharacter(pchar, 5000);
			RemoveCharacterGoods(pchar, GOOD_BOMBS, 2500);
			RemoveCharacterGoods(pchar, GOOD_POWDER, 2500);
			dialog.text = "Yes, yes, you will receive your instructions now. Are you ready to pay attention?";
			link.l1 = "Sure, officer.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "So. There is our military ship 'Warlike' cruising near Spanish colony Porto Bello, it's the Southern part of Spanish Main. This vessel is under command of Florian Shoke. He is preparing an ambush of Spanish heavy galleon which is supposed to leave Porto Bello in two weeks\nProblem is, that our frigate's cannons are suffering from casting defect, we need to replace fifteen cannons in order to save the mission, otherwise the galleon will outnumber 'Warlike' in guns and men\nWithout the replacement, Florian Shoke will be forced to sail away with no result. Such cause of events is highly undesirable. Your task is to save the mission by delivering fifteen cannons in fourteen days.";
			link.l1 = "So, I am to take aboard fifteen cannons, head to Portobello, seek out frigate 'Militant' and hand over the cannons to captain Florian Shoke?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "Exactly. You've got it right. Are you ready to take on this mission?";
			link.l1 = "What about payment?";
			link.l1.go = "trial_5";
			link.l2 = "I am sorry, officer, but I just don't want to get involved. Please excuse me.";
			link.l2.go = "trial_exit";
		break;
		
		case "trial_exit":
			dialog.text = "You're in your own right, although I kinda expected that you would agree. Now I'll have to find another courier, although I don't have much time left... Well, I am not keeping you any longer, captain.";
			link.l1 = "Best regards.";
			link.l1.go = "trial_exit_1";
		break;
		
		case "trial_exit_1":
			DialogExit();
			AddQuestRecord("Trial", "6");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
		break;
		
		case "trial_5":
			dialog.text = "Don't you worry about that. Florian Shoke will pay you two hundred golden doubloons from the ship's treasury. Besides, I am certain that he'd want to use you and your ship for his own goals - with your consent, of course.";
			link.l1 = "Alright, I am on this mission! Where are the cannons?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "I will have the soldiers load them onto your ship at once. Set sail as soon as you can, monsieur! Best of luck!";
			link.l1 = "Thanks. Luck will surely not hurt, and neither will tail wind...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			DialogExit();
			AddQuestRecord("Trial", "7");
			pchar.questTemp.Trial = "cannon";
			SetFunctionTimerCondition("Trial_CannonFail", 0, 0, 14, false); 
			SetCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24)+15);
			EnemyNationHunterOnMap(true);
			pchar.quest.Trial_cannon.win_condition.l1 = "location";
			pchar.quest.Trial_cannon.win_condition.l1.location = "Portobello";
			pchar.quest.Trial_cannon.function = "Trial_CreateFlorianFrigate";
		break;
		
		
		case "zpq_prs1":
			if(!isBadReputation(pchar, 70))
			{
				dialog.text = "Hm, perhaps You have got a good renown, so I'll take my chances to trust you. I wouldn't even talk about it otherwise. Thing is, that we need a quite large batch of a special cargo, so you will need a capacious vessel and a will to risk. Also, you must give me a word not to tell anybody\nIf you find it embarrassing then tell me about it right now. I trust that I have made my point...";
				link.l1 = "Sounds intriguing. I am in if the payment is fine, though I have no idea what cargo are you talking about. You have my word anyway.";
				link.l1.go = "zpq_prs2";
				link.l2 = "I'd say no, I suppose... if I would give you my word I would have to do work which seems quite troublous. I won't do this.";
				link.l2.go = "zpq_fld";
			}
			else
			{
				dialog.text = "Your reputation is acceptable for me. I ask you to free the room. We are able to solve our problems by ourselves.";
				link.l1 = "Whatever, solve them than...";
				link.l1.go = "exit";
			}		
		break;
		
		case "zpq_fld":
			dialog.text = "Well, at least you've rejected in honest way... Don't let me detain you.";
			link.l1 = "Farewell.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "failed";
		break;
		
		case "zpq_fld2":
			dialog.text = "Hm, actually I didn't expect that from you. I have to ask you to detain... And remember about your promise to don't divulge any information.";
			link.l1 = "I am sorry...";
			link.l1.go = "exit";
    		ChangeCharacterComplexReputation(pchar,"nobility", -10);
			if (pchar.questTemp.zpq == "begin")
			{
				AddQuestRecord("zpq", "6");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("","�"));
				CloseQuestHeader("zpq");
			}
			pchar.questTemp.zpq = "failed";
		break;
		
		case "zpq_prs2":
			dialog.text = "Splendid. The problem is that the recent storm has damaged our gun powder's supply in our fort's arsenal. I hope that I don't need to explain you that we have got a delicate trouble here. Fort will not be able to do it's job in case of a siege. We won't last long.";
			link.l1 = "Now I see what cargo do you need. And what the amount?";
			link.l1.go = "zpq_prs3";
		break;
		
		case "zpq_prs3":
			dialog.text = "We need 50 000 powder barrels. I will pay you 300 000 pesos... You must understand that it is a very good price. Our current state forces me to go with such costs though it was troubling to convince the governor's purser to that... The storm season won't allow us to use our own supply lines and we don't want everyone to know about this trouble...";
			link.l1 = "I see... the price is really nice. You've mentioned risks...";
			link.l1.go = "zpq_prs4";
		break;
		
		case "zpq_prs4":
			dialog.text = "I meant that amount of powder can be very dangerous while the transportation. I have seen a few explosions myself, sometimes a single spark can do the job. Not mentioning the storm... The whole convoys are usually keeping a distance from the potential brander. If it explodes, then everyone is dead!";
			link.l1 = "I see... But I always keep my word, consider it done.";
			link.l1.go = "zpq_prs5";
			link.l2 = "Well, senor... You've been telling me such awful things so I have lost any wish to do that job.";
			link.l2.go = "zpq_fld2";
		break;
		
		case "zpq_prs5":
			dialog.text = "Good, I am very glad that we made a deal. I will pay you as soon as you bring me the cargo\nI will have the coin in a week, so take your time but I'd ask you to try not to delay too much.";
			link.l1 = "I understand, senor. I am on it.";
			link.l1.go = "zpq_prs5_ok";
		break;
		
		case "zpq_prs5_ok":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.zpq = "begin";
			pchar.questTemp.zpq.time = 20;
			AddQuestRecord("zpq", "1");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("","�"));
			SaveCurrentQuestDateParam("pchar.questTemp.zpq");
		break;
		
		case "zpq_ex":
			dialog.text = "At last! I thought that you have already forgotten about our deal. I will immediately order my soldiers to start unloading your ship. Working with gun powder is a very delicate business, ha!";
			link.l1 = "It is great, senor, but I have to remind of payment.";
			link.l1.go = "zpq_ex2";
			RemoveCharacterGoods(pchar, GOOD_POWDER, 50000);
			AddCharacterExpToSkill(pchar, "Sailing", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 500);

            pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
            pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
            pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;
		
		case "zpq_ex2":
			dialog.text = "Yes, of course. You will be paid 150 000 pesos as we have agreed.";
			link.l1 = "You've got to be kidding me, senor?! We've agreed on 300 000 pesos!";
			link.l1.go = "zpq_ex3";
			link.l2 = "I am starting to think that you are going to cheat on me so I won't go away from here without my 450 000 pesos!";
			link.l2.go = "zpq_ex4";
			link.l3 = "Hm.. I see that the circumstances have changed. Well, I agree to your conditions.";
			link.l3.go = "zpq_ex5";
		break;
		
		case "zpq_ex3":
			if (GetSummonSkillFromName(pchar, "Leadership") > 50)
			{
				dialog.text = "Ah, yes... exactly! 300 000 pesos. I have forgotten, pardon me. It's my age to be blamed, sclerosis you know... Sure, here are your coins. I was a pleasure. Now I am sorry but I've got a lot of work to do...";
				link.l1 = "My pleasure too, senor. See you.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
            	AddQuestRecord("zpq", "2");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("","�"));
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 300000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				dialog.text = "What?! Take your money and get lost or you will rot in this casemate!";
				link.l1 = "You are such a liar, senor! I advice you to give me my money in a good way or I will take away the cargo!";
				link.l1.go = "zpq_ex_agry";
				link.l2 = "Pardon me... Fine, I'll take the sum you offer and we are done.";
				link.l2.go = "zpq_ex5";
			}
		break;
		
		case "zpq_ex4":
				dialog.text = "Such sauce! I am not mentally diseased and I precisely remember offering 300 000 pesos\n�Damn it! You won't screw me!";
				link.l1 = "Calm yourself. Think about the ready brander filled with powder right in front of your fort. If say a just a word than your fort will turn into the ruins.";
				link.l1.go = "zpq_ex6";
		break;
		
		case "zpq_ex6":
			if (GetSummonSkillFromName(pchar, "Leadership") > 75)
			{
				dialog.text = "Hm-Hm... strong argument. 450 000 pesos, you say? Here take them and pardon me now but I have a work to do.";
				link.l1 = "Farewell, senor. See you.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
            	AddQuestRecord("zpq", "5");
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 450000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				dialog.text = "What?! I am a military officer! You thought that you can scare me, kid?! Guards, take "+ GetSexPhrase("him","her") +"!";
				link.l1 = "Try, rats of casemates...";
				link.l1.go = "zpq_ex_war";
			}
		break;
		
		case "zpq_ex5":
			dialog.text = "Splendid! You have made the right choice. Take you coins and goodbye. It was a pleasure!";
			link.l1 = "Farewell...";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "3");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("","�"));
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 150000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		break;
		
		case "zpq_ex_agry":
			dialog.text = "Ah you bastard! Guards, take "+ GetSexPhrase("him","her") +"!";
			link.l1 = "Argh! It seems that I have to take my coins from your corpse...";
			link.l1.go = "zpq_ex_war";
		break;
		
        case "zpq_ex_war":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			Flag_PIRATE();
			pchar.questTemp.zpq = "failed";
            AddQuestRecord("zpq", "4");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 150000;
			AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum)*2 + rand(5000)));
			GiveItem2Character(npchar, "blade_21");
			EquipCharacterbyItem(npchar, "blade_21");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			npchar.cirassId = Items_FindItemIdx("cirass3");
			chrDisableReloadToLocation = true;
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_group_SetCheck(slai_group, "OpenTheDoors");
			AddSimpleRumour("Such things happen here!! They say that some prisoner has escaped from the casemates, slaughtered all the guards and stolen the treasury and just gone! Wow!", SPAIN, 5, 1);
		break;
		
	}
}

void GetGunType()
{
	int iGunType;
	if(makeint(pchar.rank) < 6) iGunType = rand(1);	
	if(makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 15) iGunType = rand(2); 
	if(makeint(pchar.rank) >= 15 && makeint(pchar.rank) < 24) iGunType = rand(2)+2; 
	if(makeint(pchar.rank) >= 24) iGunType = 5-rand(1); 
	int iAdd = makeint(GetSummonSkillFromName(pchar, SKILL_COMMERCE)/20);
	
	switch (iGunType)
	{
		case 0:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_24;     					
			pchar.questTemp.PrisonGun.Price = 28 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "24 calibre cannons";
		break; 
		case 1:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_18;     					
			pchar.questTemp.PrisonGun.Price = 25 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "couleuvrines";
		break; 
		case 2:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_32;     					
			pchar.questTemp.PrisonGun.Price = 32 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "32 calibre cannons";
		break; 
		case 3:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_36;     					
			pchar.questTemp.PrisonGun.Price = 36 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "36 calibre cannons";
		break;
		case 4:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_36;     					
			pchar.questTemp.PrisonGun.Price = 49 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "full couleuvrines";
		break; 
		case 5:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_42;     					
			pchar.questTemp.PrisonGun.Price = 40 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+20+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "42 calibre cannons";
		break; 
	}
}
