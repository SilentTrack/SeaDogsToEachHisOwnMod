

#define MAX_RUMOURS_ABOUT_OWNERS 7

void ProcessCommonDialogRumors(ref NPChar, aref Link, aref NextDiag);
{
    string strum;
    string srum;
	switch(Dialog.CurrentNode)
	{

		case "rumours_towngirl":	
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("towngirl", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; 
        string posrep1, posrep2, answ1, answ2, answ3, answ4;
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" This is it...", " You might find it funny.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "You are saying interesting things, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Interesting! There is one more thing I wanted to ask...","One more question.");
            answ3 = RandPhraseSimple("All kinds of stuff happen all the time. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I have got anything of interest to tell you.","It will be my pleasure, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Alas, nothing more to tell ya, let me pass.","I had enough of your questions, excuse me, I have got business to attend to."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
                                            answ2,
                                            answ3,
                                            answ4,
                                            npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Thanks, I should go.","Farewell.");
		link.l2.go = "exit";
	break;


	case "rumours_townman":	
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("townman", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; 
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" This is it...", " You might find it funny.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "You are saying interesting things, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Interesting! There is one more thing I wanted to ask...","One more question.");
            answ3 = RandPhraseSimple("All kinds of stuff happen all the time. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I have got anything of interest to tell you.","It will be my pleasure, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Alas, nothing more to tell ya, let me pass.","I had enough of your questions, excuse me, I have got business to attend to."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
                                            answ2,
                                            answ3,
                                            answ4,
                                            npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Thanks, I should go.","Farewell.");
		link.l2.go = "exit";
	break;
	
	
	case "rumours_marginal":	
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("townman", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; 
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" This is it...", " You might find it funny.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "You are saying interesting things, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("All kinds of stuff happen all the time. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I have got anything of interest to tell you.","It will be my pleasure, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Alas, nothing more to tell ya, let me pass.","I had enough of your questions, excuse me, I have got business to attend to."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Thanks, I should go.","Farewell.");
		link.l2.go = "exit";
	break;
	

	case "rumours_nobleman":	
        srum = SelectRumourEx("nobleman", NPChar);
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" This is it...", " You might find it funny.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "You are saying interesting things, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("All kinds of stuff happen all the time. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I have got anything of interest to tell you.","It will be my pleasure, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("I trust that I have made my point - I am done.","I had enough of your questions, captain. Go find something better to do!"),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Thanks, I should go.","Farewell.");
		link.l2.go = "exit";
	break;
	

	case "rumours_noblegirl":	
        srum = SelectRumourEx("noblegirl", NPChar);
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" This is it...", " You might find it funny.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "You are saying interesting things, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("All kinds of stuff happen all the time. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I have got anything of interest to tell you.","It will be my pleasure, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("I trust that I have made my point - I am done.","I had enough of your questions, captain. Go find something better to do!"),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Thanks, I should go.","Farewell.");
		link.l2.go = "exit";
	break;
	
	
	case "rumours_sailor":	
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2) srum = SelectRumourEx("sailor", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; 
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" This is it...", " You might find it funny.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "You are saying interesting things, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("All kinds of stuff happen all the time. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I have got anything of interest to tell you.","It will be my pleasure, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Alas, nothing more to tell ya, let me pass.","I had enough of your questions, excuse me, I have got business to attend to."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Thanks, I should go.","Farewell.");
		link.l2.go = "exit";
	break;

	case "rumours_habitue":
		Dialog.Text = LinkRandPhrase("Well... hic! ","Eh, what a rum! ","Well... ")+SelectRumourEx("habitue", NPChar);
		link.l1 = RandPhraseSimple(RandSwear() + "This is worth an extra cup...",
                                 "This is worth of an extra cup.");
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple("Thanks, I should go.",
                                 "Eh, helluva rum. Fine, I should go, have fun here.");
		link.l2.go = "exit_sit";

		
		if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
        {
			dialog.text = "(singing some crappy tavern song) Hey, sailor, how are you doing? How is the sea?";
            link.l1 = "Sea? Same shit as always. Salt and wet. I say, tell me about my pal who rented a room here not long ago? Gontier was his name.";
            link.l1.go = "Jamaica_ratH_1";
        }
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "(singing some crappy tavern song) Pour, sailor! First day ashore, still trying to pull myself back.";
            link.l1 = "Have a drink, pal! How is the sea?";
            link.l1.go = "EscapeSlave_Villemstad_H1";
        }
		
				
		
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "LetterToLucasSent" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "Eh, the sea... I wish I was in your shoes!";
            link.l1 = "Don't see any problems, friend. Join my crew anytime.";
            link.l1.go = "Lucas_Tavern";
        }
		
		
		
		if (CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE && !CheckAttribute(npchar, "quest.fugitive"))
        {
			dialog.text = LinkRandPhrase("Have a rum, go brave and find a thousand of friends! Ha-ha!","After a decent cup of rum even a jailer will seem lovely! Ha-ha!","Rum and ale will lead you to heavens, so drink, dammit! Ha!");
            link.l1 = "Sure, let's share a drink� Tell me, good man, do you know "+pchar.GenQuest.FindFugitive.Name+"? He is my old squad mate. Some fellas told me that he moved his arse to this place...";
            link.l1.go = "FindFugitiveHb";
        }
		
		
		
		if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && npchar.location == "Portobello_tavern")
		{
			dialog.text = "News? Hic! Haven't you heard already? Our soldiers captured a French spy. Fucking pretender, tried to act like a merchant, but *hic* - our commander is a tough bastard!";
            link.l1 = "You don't say! And what did that frog eater tried to sniff out?";
            link.l1.go = "trial_spy";
		}
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	    {
			dialog.text = "Eh, " + GetAddress_Form(pchar) + " what a world are we living at... Shitty people all around!";
			link.l1 = "What do you mean, pal?";
			link.l1.go = "Alcogol_GenQuest_Church_2_1";
		}
	break;

		case "rumours_trader":
            if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader!= 3 )
            strum = SelectRumourEx("trader", NPChar);
            else strum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; 
			Dialog.Text =  NPCStringReactionRepeat(strum, strum+" Yup. Nothing more to tell.",
                strum+" Now I should get to business.",RandPhraseSimple("I have already told you, that I don't have time for a chit chat!","I am a busy man, I don't have time to talk gossip!"),"block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear() + "Interesting! But let's get to the point","Gratitude, here is one more thing."), pcharrepphrase(""+ GetSexPhrase("Damn me","Interesting") +"! Nice talker. But I have one more question.","Let's not waste more time and talk business."),
pcharrepphrase(RandSwear() +" One more topic and I'll leave.","You are correct, time is money."),pcharrepphrase("Always thinking only about your own profits. Fine, don't go mad.","Forgive me. Let's talk business."),npchar, Dialog.CurrentNode);
			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Farewell, you old drunkass.",
"Bye, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),pcharrepphrase("Carramba! Don't go far away. I'll be back shortly.","Pleasure to see you, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"! Farewell!")),NPCharRepPhrase(npchar,pcharrepphrase("Cast off!","Farewell!"),pcharrepphrase("Hey! What are you hiding there? Rum? No!?! Whatever, I'll get some drink.","I am sorry, I have an important business in the city.")),NPCharRepPhrase(npchar,pcharrepphrase("Heh! See you around!","I should go. Bye, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!"),pcharrepphrase("Don't you dare to argue with me! I have no wish for this!","I guess I should check my ship. See you, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("What's wrong you, pal? It's me - " +GetFullName(pchar)+ "! Have a nap, I will talk to you later.","I fear that your liver will kill you before I come here again."),pcharrepphrase("Count your silver, sly dog! I'll see you later.","Pleasure to see you, " + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),npchar, Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;

        case "rumours_capitan":
			Dialog.Text = SelectRumourEx("capitan", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + "Interesting! There is one more thing I wanted to ask...",
                                     "One more question.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Thanks, I should go.",
                                     "Farewell.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "quests";
            NPChar.talk_date =  lastspeakdate();
		break;
		
		 case "rumours_landcaptain":
			Dialog.Text = SelectRumourEx("landcaptain", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + "Interesting! There is one more thing I wanted to ask...",
                                     "One more question.");
			Link.l1.go = "question";
			Link.l2 = RandPhraseSimple("Thanks, I should go.",
                                     "Farewell.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "question";
            NPChar.talk_date =  lastspeakdate();
		break;

		case "rumours_tavern":  

                 Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Information costs money. 1000 pieces and I will tell you everything I know.",
                "Something's wrong with my memory, 1000 coins might help me remember something.",
                "I am eager to share with information. But it will cost you 1000 pesos. No bargaining."),
                "Nothing more to add here. Now, excuse me, I should go.",
                "", "", "block", 1, npchar, Dialog.CurrentNode);
             
    			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear() + "I am not paying for a worthless chit chat.",
                                         "I am thinking about better ways to spend these money."), "Let's change the subject.", "Let's change the subject.", "Let's change the subject.", npchar, Dialog.CurrentNode);
                link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);
                NextDiag.CurrentNode = NextDiag.TempNode;
    			if (makeint(pchar.money) >= 1000 )
    			{
    				link.l2 = HeroStringReactionRepeat(RandPhraseSimple("You will have them if I learn something worthy from you.", "I'll pay if you give me something of value."),
                     "", "", "" , npchar, Dialog.CurrentNode);
    				link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
    			}
    			else
    			{
                    link.l2 =  HeroStringReactionRepeat("I don't have such sum.", "", "", "", npchar, Dialog.CurrentNode);
    				link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
    			}

		break;
		
		case "rumours_tavern_yes":
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation"))
			{
				bool bOk = (pchar.questTemp.Saga.BarbTemptation == "silk") || (pchar.questTemp.Saga.BarbTemptation == "give_silk");
				if (bOk && npchar.location == "Marigo_tavern" && !CheckAttribute(npchar, "quest.barbtemptation"))
				{
					AddMoneyToCharacter(pchar, -1000);
					Dialog.Text =  "Our patrol has recently destroyed a brigantine of some French smuggler Morel. The man is now sitting in the dungeons and facing a death sentence. They still try to find his cargo, bastard dies when they do.";
					link.l1 = "Interesting... Fine, take the money. Anything else to tell?";
					link.l1.go = "rumours_tavern";
					Saga_CreateMorelle(); 
					npchar.quest.barbtemptation = "true";
					pchar.questTemp.Saga.BarbTemptation.Prison = "true";
					break;
				}
			}	
			
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && npchar.location == "portobello_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  "There was a big party in a governor's palace. His excellence's friend, don Carlos de Milyar is back. He was captured in a sea battle, but he managed to escape with the help of a French lieutenant. Don Carlos is not only smart, he is also a very generous man. This lieutenant, Jean Deno, is a captain of the Sario now. As far as I've heard he was also gifted by a small plantation. Now the frog eater is called Juan! What a story!";
				link.l1 = "Intriguing... Fine, the money is yours. Take this. Anything else to tell me?";
				link.l1.go = "rumours_tavern";
				pchar.questTemp.FMQG = "headhunter_juan";
				AddQuestRecord("FMQ_Guadeloupe", "10");
				pchar.quest.FMQG_Juanship.win_condition.l1 = "location";
				pchar.quest.FMQG_Juanship.win_condition.l1.location = "PortoBello";
				pchar.quest.FMQG_Juanship.function = "FMQG_CreateJuanship";
				break;
			}	
			
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "town" && npchar.location == "Marigo_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  "Our commandant has sent extra forces to patrol the jungles. Not to mention the city guard. There are rumors about Englishmen planning to infiltrate Philipsburg and set the captured officers free.";
				link.l1 = "You don't say? Do they actually have balls to perform such a trick?.. And what officers are you talking about exactly?";
				link.l1.go = "FMQN_r";
				break;
			}	
			
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && npchar.location == "Havana_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  "The other day the whole town got agitated. An officer from a military lugger got dead drunk in my tavern, and just about raped a married girl. Then proceeded to beat up her husband, who tried to defend his wife, and even threatened him with a sword. Imagine all that right in front of the town's guard! As they say, dog does not eat dog. The soldiers just turned away while this bastard was raging\nBut the scoundrel was disarmed by - who would've thought - some sailors from a merchant's ship. They almost pinned him down, although the bastard got away and hid on his ship. Commandant and alcalde tried to sweep it under the rug, but the assaulted man is a respected citizen, who turned to his Excellence don Diego de Toledo and made some noise among the local bourgeoisie\nThey issued officer's arrest and suggested his captain to hastily leave the port with him, transferring the scoundrel to a different location. However, lugger's captain, Esberdo Cabanas, was a man of honor. Once he learned what the officer has done, he immediately arrested the scoundrel and sent him back to the shore. The bastard is rotting in prison for the foreseeable future, where he belongs if you ask me. And then, maybe, he'll get disranked to make an example.";
				link.l1 = "Wait, did you say captain Esberdo Cabanas? Huh... an exciting story, indeed!.. Alright, you earned your money - here you go. Anything else you could tell me?";
				link.l1.go = "rumours_tavern";
				Mtraxx_CreateOfficer(); 
				pchar.questTemp.Mtraxx = "jewelry_4";
				pchar.GenQuest.PrisonQuestLock = "true";
				AddQuestRecord("Roger_1", "7");
				break;
			}
            string RumText = SelectRumourEx("tavern", NPChar); 
			
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; 
                link.l1 = RandPhraseSimple("Worthless crap. I am paying for this. Bye.", "Your information costs nothing, so you get nothing.");

			    link.l1.go = "Exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                AddMoneyToCharacter(pchar, -1000);
                Dialog.Text = RumText;
    			link.l1 = RandPhraseSimple("Thanks, take the money. Anything else to tell?", "Fine, take the money. Anything else to tell?");
    			link.l1.go = "rumours_tavern";
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;

		case "rumours_tavern_no":
			Dialog.Text = "I have a family, you know.";
            link.l1 = "Let's change the subject.";
			link.l1.go = "first time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			link.l2 = LinkRandPhrase("Thanks, I should go.",
                                     "Farewell.","Bye.");
			link.l2.go = "Exit";
		break;	

        case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "Interesting. One more question...",
										"Hm, let me ask something else...");
				Link.l1.go = "rumours_poor_2";
				Link.l2 = RandPhraseSimple("Well, farewell.",
										"Bye, pal.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("Told you all I know.", 
					"Nothing more to share, sorry...");
				Link.l1 = RandPhraseSimple("I see. Farewell.",
										"Goodbye, pal...");
				Link.l1.go = "exit";			
			}
            NPChar.talk_date = lastspeakdate();
		break;
        case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "Interesting. One more question...",
										"Hm, let me ask something else...");
				Link.l1.go = "rumours_poor";
				Link.l2 = RandPhraseSimple("Well, farewell.",
										"Bye, pal.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("Told you all I know.", 
					"Nothing more to share, sorry...");
				Link.l1 = RandPhraseSimple("I see. Farewell.",
										"Goodbye, pal...");
				Link.l1.go = "exit";			
			}
			NPChar.talk_date = lastspeakdate();
		break;


        case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC", NPChar);
				Link.l1 = RandPhraseSimple("Understood...",
										"I see...");
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else  
			{
				Dialog.Text = NPCharSexPhrase(npchar, RandPhraseSimple("Told you all I know.", "Told you all I know, sorry..."), 
					RandPhraseSimple("Told you all I know.", "Told you all I know, sorry..."));
				Link.l1 = RandPhraseSimple("I see. Farewell.", "Goodbye.");
				Link.l1.go = "exit";			
			}
		break;
		

		case "rumours_lighthouse": 
			Dialog.Text = NPCStringReactionRepeat(RandPhraseSimple("Eh, captain! It's always nice chatting with you. Being on my own here is quite dull sometimes...", "I live alone, visitors are a rare occasion. So I am always in a mood to talk."), "Fancy a chit chat, captain? Well, I might have something else to tell...", "Take a bottle of rum next time you visit me...", "Alas, I told you everything I know.", "block", 1, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Then share your information. I like talking with people, you know...", "Tell me! You know what they say about value of information?"), "Like what?", "By all means! Got anything else to share?", "Fine, we had a nice chat anyway." , npchar, Dialog.CurrentNode);
    		link.l1.go = HeroStringReactionRepeat("rumours_lighthouse_yes", "rumours_lighthouse_void", "rumours_lighthouse_void", "exit", npchar, Dialog.CurrentNode);
		break;
		
		case "rumours_lighthouse_yes":
            RumText = SelectRumourEx("tavern", NPChar);
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("Thank you! Anything else?", "Very interesting! Anything else?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Gratitude! It was quite entertaining...", "Thank you for telling me!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                Dialog.Text = RumText;
    			link.l1 = RandPhraseSimple("Thank you! Anything else?", "Very interesting! Anything else?");
    			link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Gratitude! It was quite entertaining...", "Thank you for telling me!");
			    link.l2.go = "exit";
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;
		
		case "rumours_lighthouse_void":
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("Thank you! Anything else?", "Very interesting! Anything else?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Gratitude! It was quite entertaining...", "Thank you for telling me!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "Postcureer_LevelUp_ForAll":
			
			if (!CheckCharacterItem(pchar, pchar.questTemp.WPU.Current.Item))
			{
				dialog.text = "But where is the package? You don't have it?";
	        	link.l1 = "Well... I was supposed to deliver it to you. But it was� to be completely honest, it was taken from me. I couldn't fight back and gave them the package myself. ";
	        	link.l1.go = "Postcureer_LevelUp_complete_fail";
				break;
			}
			
			if (sti(pchar.questTemp.WPU.Postcureer.AgentChance) == 4)
			{
				dialog.text = "Hm. Excuse me, but the package was opened before! It's crystal for me. The seal is was re-stamped...";
	        	link.l1 = "" + GetAddress_FormToNPC(NPChar) + ", it is the package I was given at harbor office of " +XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+ ", and I don't see why...";
	        	link.l1.go = "Postcureer_LevelUp_complete_Agentfail";
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "late")
			{
				int iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money)/(sti(iTime)+1));
				dialog.text = "I was waiting for you. But you are " + FindRussianDaysString(iTime)+ " late! The information you are carrying has become much less useful� It still has some value of course, so I will pay you - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ". Please, take the money and farewell.";
	        	link.l1 = "Thanks. I guess.";
	        	link.l1.go = "Postcureer_LevelUp_complete";
				pchar.quest.PostcureerTime_FullOver.over = "yes";
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-1;
				AddQuestRecord("Postcureer", "8");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(iTime));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "lost")
			{
				dialog.text = "So it is you! I've been waiting for you quite a while, even took steps to retrieve the package. Give me it. I don't need it now really, thanks to your timing, but I'd like to keep it to myself\nAs you understand, I can't pay you anything, yet I will make sure your good name is restored.";
	        	link.l1 = "Thanks... I guess. I am sorry for the delay, I really do. Farewell.";
	        	link.l1.go = "Postcureer_LevelUp_complete_bad";
				break;
			}
			dialog.text = "I was waiting for you. You are just in time, the information you brought me will be a good use. Please, accept these money for your job - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ". My thanks for your timing.";
        	link.l1 = "You are welcome. Farewell!";
        	link.l1.go = "Postcureer_LevelUp_complete";
			pchar.quest.PostcureerTime_Over.over = "yes";
			AddQuestRecord("Postcureer", "10");
		break;
		
		case "Postcureer_LevelUp_complete":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 120);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_bad":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "9");
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 33);
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_fail":
			dialog.text = "Eh, I knew it would end this way... I should had hired a military courier vessel, not a civilian captain... Whatever, " + GetAddress_Form(NPChar) + ", you are not a soldier, so there is nothing to blame you for. Farewell.";
			link.l1 = "Bye, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;
		
		case "Postcureer_LevelUp_complete_Agentfail":
			dialog.text = "Sir, I know the harbor master of " +XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+ " personally, he is an honest man. Plus, there was no point for him to open the message. " + GetAddress_Form(NPChar) + ", you are a fraud! I am not paying you a single copper. Get lost!";
			link.l1 = "Hm...";
			link.l1.go = "Postcureer_LevelUp_complete_Agentfail_1";
		break;
		
		case "Postcureer_LevelUp_complete_Agentfail_1":
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "17");
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		



		case "Device_Common":
			dialog.text = "Looked like shit. A beggar or a hobo. Can't tell where exactly did he go, I didn't care to follow him.";
			link.l1 = "Better than nothing. Thank you! I should go.";
			link.l1.go = "Device_Common_1";
		break;
		
		case "Device_Common_1":
			string sNation = pchar.GenQuest.Device.Shipyarder.Nation;
			sld = GetCharacter(NPC_GenerateCharacter("Device_poorman", "panhandler_"+(rand(5)+1), "man", "man", sti(pchar.rank)+5, sNation, 20, true, "quest"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+5, true);         
			GiveItem2Character(sld, "slave_02");
			EquipCharacterbyItem(sld, "slave_02");
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, sNation+"_CITIZENS");
			sld.Dialog.Filename = "Quest\Other_Quests_NPC.c"; 
			sld.dialog.currentnode = "Device_poorman"; 
			sld.greeting = "Gr_poorman";
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance2))
			{
				case 0:
					sld = characterFromId("Device_poorman");
					GetCharacterPos(pchar, &locx, &locy, &locz);
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City +"_town", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
				break;
				case 1:
					sld = characterFromId("Device_poorman");
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City + "_ExitTown", "goto", "goto1");
				break;
				case 2:
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
				break;
				case 3:
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Location = GetDeviceLocation(npchar); 
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Location, "goto", "goto1");
					if (pchar.GenQuest.Device.Shipyarder.Location == "none" || CheckAttribute(pchar, "GenQuest.SeekSpy.Location"))
					{
						pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
					}
				break;
			}
			pchar.GenQuest.Device.Shipyarder = "inSeek";
			DialogExit();
			AddQuestRecord("Device", "9");
		break;
		
		
		
		case "FMQN_r":
			Dialog.Text =  "Not long ago they captured an English vessel not far from Sint-Maarten, she was carrying a few high-ranked officers. It's decided to sent them to Willemstad but at this moment they are held here in our comfortable dungeons. They say that one of them has told our superiors about intentions of the English to sent here a raiding party to rescue the officers. That's why our good old commandant is ready and prepared. Why wouldn't he be - if the prisoners are gone, they will demote him to a soldier!";
			link.l1 = "Intriguing... Fine, the money is yours. Take this. Anything else to tell me?";
			link.l1.go = "rumours_tavern";
			pchar.questTemp.FMQN = "governor";
			pchar.quest.FMQN_governor.win_condition.l1 = "location";
			pchar.quest.FMQN_governor.win_condition.l1.location = "Marigo_town";
			pchar.quest.FMQN_governor.function = "FMQN_ToGovernor";
			if (Whr_IsDay()) AddDialogExitQuest("FMQN_GetRumoursDay");
			else AddDialogExitQuest("FMQN_GetRumoursNight");
		break;




		case "IntelligenceForAll":
            Dialog.Text = RandPhraseSimple("Very well then. I have the package here, ready to delivery. Take it.\nDon't come here and don't talk to me anymore, it is too dangerous. Watch yourself out there...", 
				"Hm, great. Take the package and make sure you deliver it to the man we just talked about.\nGoodbye and don't talk to me anymore, it is too dangerous.");
            link.l1 = RandPhraseSimple("Got it. Goodbye...", "Farewell and good luck.");
			link.l1.go = "exit";
			pchar.GenQuest.Intelligence = "Execute";
			GiveItem2Character(pchar, "sicretLetter");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			ref rItem = ItemsFromID("sicretLetter");
			rItem.City = XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen")); 
			rItem.Mayor = GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)); 
			AddQuestRecord("MayorsQuestsList", "7");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)], "Gen"));
			AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)]));			
		break;




        case "Man_FackYou":
			dialog.text = LinkRandPhrase("A robbery in the middle of the day!!! Really?! Stay where you are, pal...", "Hey, what are doing there?! Seems like someone was going to rob me. You are done...", "Wait, we are you going? A thief! End of the line, pal...");
			link.l1 = LinkRandPhrase("Flames!!", "Carramba!!", "Dammit!");
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}

string sRumourAboutOwners_CityRumour(string sCity, string sOwnerType) 
{
	string sRetRumour = "����� ���. �������� � ��� ��, ��� Warship'�.";
	
	switch(sCity)
	{
		case "Tortuga":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 0;
		break;
		
		case "PortRoyal":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 1;
		break;
		
		case "FortOrange":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 2;
		break;
		
		case "Beliz":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 3;
		break;
		
		case "PortoBello":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 4;
		break;
		
		case "Cartahena":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 5;
		break;
		
		case "Maracaibo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 6;
		break;
		
		case "Caracas":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 7;
		break;
		
		case "Cumana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 8;
		break;
		
		case "SantaCatalina":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 9;
		break;
		
		case "SanJuan":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 10;
		break;
		
		case "Marigo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 11;
		break;
		
		case "Charles":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 12;
		break;
		
		case "SentJons":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 13;
		break;
		
		case "FortFrance":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 14;
		break;
		
		case "BasTer":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 15;
		break;
		
		case "Bridgetown":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 16;
		break;
		
		case "PortSpein":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 17;
		break;
		
		case "Havana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 18;
		break;
		
		case "Villemstad":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 19;
		break;
		
		case "Santiago":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 20;
		break;
		
		case "PortPax":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 21;
		break;
		
		case "SantoDomingo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 22;
		break;
	}
	
	return sRetRumour;
}

string sRumourAboutOwners_Init(string sOwnerType, int iRumourNum) 
{
	
	string STR_MAYOR[MAX_RUMOURS_ABOUT_OWNERS]; 
	STR_MAYOR[0] = "Oh, sir governor is an excellent man. He manages our colony with a great skill, never had a single conflict since the day of foundation\nHis only flaw is... he is� well... he is quite saving. It might be just another virtue though.";
	STR_MAYOR[1] = "Oh, sir governor is an excellent man. He manages our colony with a great skill, never had a single conflict since the day of foundation\nHis only flaw is... he is� well... he is quite saving. It might be just another virtue though.";
	STR_MAYOR[2] = "Oh, sir governor is an excellent man. He manages our colony with a great skill, never had a single conflict since the day of foundation\nHis only flaw is... he is� well... he is quite saving. It might be just another virtue though.";
	STR_MAYOR[3] = "Oh, sir governor is an excellent man. He manages our colony with a great skill, never had a single conflict since the day of foundation\nHis only flaw is... he is� well... he is quite saving. It might be just another virtue though.";
	STR_MAYOR[4] = "Oh, sir governor is an excellent man. He manages our colony with a great skill, never had a single conflict since the day of foundation\nHis only flaw is... he is� well... he is quite saving. It might be just another virtue though.";
	STR_MAYOR[5] = "Oh, sir governor is an excellent man. He manages our colony with a great skill, never had a single conflict since the day of foundation\nHis only flaw is... he is� well... he is quite saving. It might be just another virtue though.";
	STR_MAYOR[6] = "Oh, sir governor is an excellent man. He manages our colony with a great skill, never had a single conflict since the day of foundation\nHis only flaw is... he is� well... he is quite saving. It might be just another virtue though.";
	
	string STR_TAVERNKEEPER[MAX_RUMOURS_ABOUT_OWNERS]; 
	STR_TAVERNKEEPER[0] = "Quite a pleasant guy. It is always nice spending time in his place, he also got a great sense of humor. The most important thing about him is that he keeps a tavern in order and prevents drunk lowlifes from pestering good citizens.";
	STR_TAVERNKEEPER[1] = "Quite a pleasant guy. It is always nice spending time in his place, he also got a great sense of humor. The most important thing about him is that he keeps a tavern in order and prevents drunk lowlifes from pestering good citizens.";
	STR_TAVERNKEEPER[2] = "Quite a pleasant guy. It is always nice spending time in his place, he also got a great sense of humor. The most important thing about him is that he keeps a tavern in order and prevents drunk lowlifes from pestering good citizens.";
	STR_TAVERNKEEPER[3] = "Quite a pleasant guy. It is always nice spending time in his place, he also got a great sense of humor. The most important thing about him is that he keeps a tavern in order and prevents drunk lowlifes from pestering good citizens.";
	STR_TAVERNKEEPER[4] = "Quite a pleasant guy. It is always nice spending time in his place, he also got a great sense of humor. The most important thing about him is that he keeps a tavern in order and prevents drunk lowlifes from pestering good citizens.";
	STR_TAVERNKEEPER[5] = "Quite a pleasant guy. It is always nice spending time in his place, he also got a great sense of humor. The most important thing about him is that he keeps a tavern in order and prevents drunk lowlifes from pestering good citizens.";
	STR_TAVERNKEEPER[6] = "Quite a pleasant guy. It is always nice spending time in his place, he also got a great sense of humor. The most important thing about him is that he keeps a tavern in order and prevents drunk lowlifes from pestering good citizens.";
	
	string STR_SHIPYARDER[MAX_RUMOURS_ABOUT_OWNERS]; 
	STR_SHIPYARDER[0] = "Great lad. Always willing to help. I have to say, he builds fine ships for such a shithole like this place. ";
	STR_SHIPYARDER[1] = "Great lad. Always willing to help. I have to say, he builds fine ships for such a shithole like this place. ";
	STR_SHIPYARDER[2] = "Great lad. Always willing to help. I have to say, he builds fine ships for such a shithole like this place. ";
	STR_SHIPYARDER[3] = "Great lad. Always willing to help. I have to say, he builds fine ships for such a shithole like this place. ";
	STR_SHIPYARDER[4] = "Great lad. Always willing to help. I have to say, he builds fine ships for such a shithole like this place. ";
	STR_SHIPYARDER[5] = "Great lad. Always willing to help. I have to say, he builds fine ships for such a shithole like this place. ";
	STR_SHIPYARDER[6] = "Great lad. Always willing to help. I have to say, he builds fine ships for such a shithole like this place. ";
	
	string STR_TRADER[MAX_RUMOURS_ABOUT_OWNERS]; 
	STR_TRADER[0] = "Nothing bad about him. A decent citizen, often visits our chapel. People seem to like him. Never heard of anyone being angry at him.";
	STR_TRADER[1] = "Nothing bad about him. A decent citizen, often visits our chapel. People seem to like him. Never heard of anyone being angry at him.";
	STR_TRADER[2] = "Nothing bad about him. A decent citizen, often visits our chapel. People seem to like him. Never heard of anyone being angry at him.";
	STR_TRADER[3] = "Nothing bad about him. A decent citizen, often visits our chapel. People seem to like him. Never heard of anyone being angry at him.";
	STR_TRADER[4] = "Nothing bad about him. A decent citizen, often visits our chapel. People seem to like him. Never heard of anyone being angry at him.";
	STR_TRADER[5] = "Nothing bad about him. A decent citizen, often visits our chapel. People seem to like him. Never heard of anyone being angry at him.";
	STR_TRADER[6] = "Nothing bad about him. A decent citizen, often visits our chapel. People seem to like him. Never heard of anyone being angry at him.";
	
	string sTempMayor = STR_MAYOR[iRumourNum];
	string sTempTavernkeper = STR_TAVERNKEEPER[iRumourNum];
	string sTempShipyarder = STR_SHIPYARDER[iRumourNum];
	string sTempTrader = STR_TRADER[iRumourNum];
	
	if(sOwnerType == "Mayor") return sTempMayor;
	if(sOwnerType == "TavernKeeper") return sTempTavernkeper;
	if(sOwnerType == "ShipYarder") return sTempShipyarder;
	if(sOwnerType == "Trader") return sTempTrader;
}

string GetDeviceLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId") || CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) 
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[dRand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); 
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}
