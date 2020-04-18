
#include "DIALOGS\russian\Rumours\Common_rumours.c"  
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
    
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
    
    string iDay, iMonth, lastspeak_date, eggStr;
    string sTemp, sTitle;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }
	
    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {	
        npchar.quest.BadMeeting = "";
    }
    if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
    {
        npchar.quest.GhostShipMonth = "";
    }
    
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
	}
	
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
	}
	
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
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(""+ GetSexPhrase("My son","My daughter") +", unfortunately, I cannot give you shelter. Run!", "The city guard is scouring the city looking for you, "+ GetSexPhrase("my son","my daughter") +". The doors of my church are always open for the suffering, but I cannot give you shelter...", ""+ GetSexPhrase("My son","My daughter") +", you have to run! Don't delay, I beg you!"), 
					LinkRandPhrase("What are you doing in the church, fallen soul? I demand that you leave at once, before the soldiers find you here and perpetrate a massacre!", "Leave the temple this instant, you scoffer! I will never stand up for one , such as you!", "Leave the temple of our Lord this instant! We don't need murders here!"));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Oh, come on, padre...", "I don't need your help anyway..."), 
					LinkRandPhrase("Just don't get under my feet, Father...", "I'll leave, don't you worry...", "Padre, stop the fuss - I really have no time for it"));
				link.l1.go = "fight";
				break;
			} 
            if (npchar.quest.BadMeeting != lastspeak_date)
			{
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_2.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && NPChar.location != "Minentown_church" && rand(5) == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) 
				{
					dialog.text = "...they shall burn in the fiery hell forever! Never shall they see...";
					link.l1 = RandPhraseSimple("Ugh! Did I disturb you?", "Here it is speech!");
					link.l1.go = "GenQuest_Church_2_Start_1";
					NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; 
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
				{
					Dialog.Text = ""+ GetSexPhrase("My son","y daughter") +", I am glad to see you again!";
					link.l1 = "And I am glad to see you in a kind health, padre" + NPChar.name + "...";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
				{
					Dialog.Text = ""+ GetSexPhrase("My son","My daughter") +"! I am glad to see you again alive and in good mood. The Lord must have helped us in our affair, I take it?";
					link.l1 = "Yes, " + RandPhraseSimple("padre", "Father") + ", though in my sails and not always blew the following wind, though I and spent some more time, forces and money, but your commission is executed in the total.";
					link.l1.go = "GenQuest_Church_1_Complete_1";
					break;
				}
				Dialog.Text = "Welcome to our holy abode, "+ GetSexPhrase("My son","My daughter") +".";
				link.l1 = "Hello, Father.";
				link.l1.go = "node_3";
				Link.l2 = "You're not my father and don't you ever address me that way again.";
				Link.l2.go = "node_2";
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date;	
			}
			else
			{
				Dialog.Text = "Go away from the temple of Lord, blaspheme! To us with you not about what to talk!";
				Link.l1 = "Not that I wanted to.";
				Link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "node_2":
			dialog.text = "Oh, you blasphemer! Away with you! Don't you dare to defile our Lord's temple with your presence!";
			link.l1 = "And I and so did not gather here to stay too long.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			dialog.text = "May the Lord bless you and your affairs... Have you come to me for a particular reason?";
    		link.l1 = RandPhraseSimple("I'd like to make a donation.", "I want to donate to a good cause.");
    		link.l1.go = "donation";
    		link.l2 = RandPhraseSimple("I think it's time for a confession.","I want to confess, "+RandPhraseSimple("padre.", "Father."));
    		link.l2.go = "ispoved";
    		link.l3 = RandPhraseSimple("I have business with you, " + RandPhraseSimple("padre.", "Father."),
                                           "I arrived in business," + RandPhraseSimple("padre.", "Father."));
    		link.l3.go = "work";
			
			
			
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && pchar.location == "Cartahena_church" && sti(pchar.money) >= 1000)
			{
				link.l4 = "I want to order prayer service for the peace the souls of one lady.";
				link.l4.go = "saga";				
			}
			
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location != "Bridgetown_church" && !CheckAttribute(npchar, "quest.seektreatment"))
			{ 
				link.l4 = "Father, I need help. I am really sick. Some foul pagan curse has befallen upon me. Please, help me, I beg you!";
				link.l4.go = "seektreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location == "Bridgetown_church")
			{ 
				link.l4 = "Father, I need help. I am really sick. Some foul pagan curse has befallen upon me. Please, help me, I beg you!";
				link.l4.go = "findtreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessFindTreatment") && pchar.location == "Bridgetown_church")
			{ 
				link.l4 = "Father, I need help. I am really sick. Some foul pagan curse has befallen upon me. I was told that you are the one who can help me. I beg you...";
				link.l4.go = "findtreatment";
			}
			
			if(CheckAttribute(pchar, "questTemp.Saga.JessTreatment") && pchar.location == "Bridgetown_church")
			{
				link.l4 = "Father, I need help. I am really sick. Some foul pagan curse has befallen upon me. I was sent to you by... Jessica Rose. She told me you'd be able to help me.";
				link.l4.go = "treatment";
			}
			if(CheckAttribute(npchar, "quest.candle"))
			{
				link.l4 = "About the candles...";
				link.l4.go = "candle";
			}
			if(CheckAttribute(npchar, "quest.prayer") && GetNpcQuestPastDayParam(npchar, "prayer_date") >= 1 && stf(environment.time) >= 22.0)
			{
				link.l4 = "I am ready to pray, Father.";
				link.l4.go = "prayer";
			}
			
			
			
			if(CheckAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest") && AffairOfHonor_GetCurQuest() == "GodJudgement" &&
				NPChar.city == PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId)
			{
				link.l5 = "Terrible things are happening, Father.";
				link.l5.go = "AffairOfHonor_GodJudgement_1";
			}
			
			link.l6 = "Excuse me, but I have to go.";
			link.l6.go = "exit";
		break;

		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "Worry not, my son. The Lord will see you suffering and He will extend a helping hand. Always carry a cross on you to strengthen your faith.";
			Link.l1 = "Thank you, Father.";
			Link.l1.go = "exit";
			AddItems(PChar, "amulet_3", 15);
			DeleteAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest");
		break;


		
		case "saga" :
			dialog.text = "I will humbly carry out your will for 1000 pesos.";
			Link.l1 = "Here you go, Father - please take these coins.";
			Link.l1.go = "saga_1";
		break;
		
		case "saga_1" :
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Thank you, my son. What's the name of the senora, whose soul I shall pray for?";
			Link.l1 = "Her name is Chica Gonzales, and she has left this world many years ago.";
			Link.l1.go = "saga_2";
		break;
		
		case "saga_2" :
			dialog.text = "That's strange... Did something happen to Alvares, and he asked you about this?";
			Link.l1 = "And who is this Alvarez and what's so strange about my request?";
			Link.l1.go = "saga_3";
		break;
		
		case "saga_3" :
			dialog.text = "Well how! Each month guard of our lighthouse, Alvares, since two decades, orders prayer service for the peace of the soul of this lady. Anyone but he still did not have nothing to do with Lady Gonzales. And you come here. So I thought. However, it is not my business. Certainly, I will be glad to humbly carry out your wishes to help the stray soul to find calmness and road to paradise.";
			Link.l1 = "Thank you, Father.";
			Link.l1.go = "saga_4";
		break;
		
		case "saga_4" :
			DialogExit();
			AddQuestRecord("Saga", "15");
			Saga_SetOrtega();
			pchar.questTemp.Saga = "ortega";
			pchar.quest.Saga_Gonsales1.over = "yes"; 
			if (GetCharacterIndex("SagaGonsalesB") != -1)
			{
				sld = characterFromId("SagaGonsalesB");
				sld.lifeday = 0;
			}
		break;
		
		
		
		case "treatment":
			dialog.text = "Jessica? I remember her. Poor sinner. But didn't she die?";
			link.l1 = "She died, Father. Now she's dead, may the Lord rest her soul. But she assured me that you'd be able to help me.";
			link.l1.go = "treatment_1";
			DeleteAttribute(pchar, "questTemp.Saga.JessTreatment");
		break;
		
		case "treatment_1":
			dialog.text = "Who placed these spells upon you, my son? Tell me honestly.";
			link.l1 = "She... she did. Jessica.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "God save us! That's what I thought. Delving into pagan rites may cast even stronger souls into the abyss of darkness... But... did she really die? Or... not completely?";
			link.l1 = "You're extremely insightful, Father. Now she's totally dead.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			dialog.text = "I had confessed this poor sinner quite a few times. Hate completely destroyed her from the inside. I knew what she was up to. I attempted to stop her, tried to make her follow the straight and narrow, but all my efforts were in vain. I warned her about the terrible danger and dire consequences of the unholy rights...";
			link.l1 = "Yes, Father. What I had seen, was terrible indeed. But... how can I be cured?";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "By the power of prayer, my son. By the power of the holy cleansing prayer at our temple. You will have to pray for very long, and not for yourself only. You'll have to pray for her as well.";
			link.l1 = "For Jessica?";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "Yes. For yourself and for her soul. Come here by ten at night, so that no one would be distracting you. You'll have to pray all night through. Bring with you twenty thick wax candles, light them up and pray until they all burn out.";
			link.l1 = "And then I shall be healed?";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "Everything is in the hands of the Lord. I will teach you how to pray and leave there Holy Scripture for you. The power of holy prayer shall destroy foul spells which befell you, and also cleanse the soul of poor Jessica.";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "I have twenty wax candles with me. I am ready to stay at the temple and begin praying.";
				link.l1.go = "treatment_9";
			}
			else
			{
				link.l1 = "I don't have twenty candles on me yet. I shall get them!";
				link.l1.go = "treatment_7";
			}
		break;
		
		case "treatment_7":
			dialog.text = "Okay, my son. I'll be waiting for you. Don't waste time!";
			link.l1 = "I'll be here soon...";
			link.l1.go = "treatment_8";
		break;
		
		case "treatment_8":
			DialogExit();
			npchar.quest.candle = "true";
		break;
		
		case "candle":
			dialog.text = "Have you brought twenty candles, my son?";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "Yes, Father. I have twenty wax candles with me. I am ready to stay at the temple and begin praying.";
				link.l1.go = "treatment_9";
				DeleteAttribute(npchar, "quest.candle");
			}
			else
			{
				link.l1 = "Not yet - but I will get them by all means.";
				link.l1.go = "exit";
			}
		break;
		
		case "treatment_9":
			dialog.text = "Well, my son. Give them to me and come back tomorrow after ten o'clock. I will teach you the necessary prayers and leave you in the church at night.";
			link.l1 = "Thanks, Father. See you tomorrow!";
			link.l1.go = "treatment_10";
		break;
		
		case "treatment_10":
			DialogExit();
			RemoveItems(pchar, "mineral3", 20);
			LAi_RemoveLoginTime(npchar);
			LAi_SetLoginTime(npchar, 6.0, 22.99);
			npchar.quest.prayer = "true";
			SaveCurrentNpcQuestDateParam(npchar, "prayer_date");
		break;
		
		case "prayer":
			dialog.text = "I have prepared for you the texts of the prayers, my son. I also leave there your twenty candles and the Holy Scripture. Light the candles and start praying. Pray without a stop; pray for your recovery and for the soul of this poor sinner Jessica. If you forget something or if you don't understand something - it doesn't really matter. Pray from your heart, for your sincere desire is what matters to our Lord.";
			link.l1 = "Thank you, Father. I got it.";
			link.l1.go = "prayer_1";
		break;
		
		case "prayer_1":
			dialog.text = "I will come back in the morning. I will be praying for you, too...";
			link.l1 = "Thank you, Father.";
			link.l1.go = "prayer_2";
		break;
		
		case "prayer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_BarbadosTreatment", -1);
			chrDisableReloadToLocation = true;
		break;
		
		case "seektreatment":
			dialog.text = "What pagan spells have stricken you, my son?";
			link.l1 = "I don't know how they are called. I am weak and sluggish; I cannot run around, and it is very difficult for me to fight.";
			link.l1.go = "seektreatment_1";
		break;
		
		case "seektreatment_1":
			if (sti(pchar.questTemp.Saga.JessSeekTreatment) == 3)
			{
				dialog.text = "I have heard of those... They were brought into our world by unholy witches of these red-skinned pagans. I would advise you to see father superior of the church of Bridgetown - he had spent several years studying the pernicious influence of Indian curses on the bodies and souls of Christians.";
				link.l1 = "And he'd be able to help me?!";
				link.l1.go = "seektreatment_4";
			}
			else
			{
				dialog.text = "I have heard of those... They were brought into our world by unholy witches of these red-skinned pagans. Unfortunately, the only advice I can give you is spending more time praying, my son, and set your hopes upon the mercy of our Lord.";
				link.l1 = "But is there really nothing to be done about it, Father?! Will I stay like that... till the end of my days?";
				link.l1.go = "seektreatment_2";
			}
		break;
		
		case "seektreatment_2":
			dialog.text = "Don't despair, my son. The Lord will hear you and He will send you help. But I would recommend you to ask around in other holy abodes - perhaps there are priests who know how to remove pagan enchantments.";
			link.l1 = "Thank you, Father! I will be healed - even if I have to visit every church on the archipelago!";
			link.l1.go = "seektreatment_3";
		break;
		
		case "seektreatment_3":
			dialog.text = "Go, my son, and may the Lord watch over you.";
			link.l1 = "Goodbye, padre.";
			link.l1.go = "exit";
			npchar.quest.seektreatment = "true";
			pchar.questTemp.Saga.JessSeekTreatment = sti(pchar.questTemp.Saga.JessSeekTreatment)+1;
		break;
		
		case "seektreatment_4":
			dialog.text = "Only the Lord can help you - and you yourself, my son. A priest can only teach you, what to do and how. Come see him.";
			link.l1 = "Thank you, padre! You have saved me! I shall immediately leave for Barbados!";
			link.l1.go = "seektreatment_5";
		break;
		
		case "seektreatment_5":
			dialog.text = "Go now, and may the Lord watch over you.";
			link.l1 = "Goodbye, Father.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment");
			pchar.questTemp.Saga.JessFindTreatment = "true";
		break;
		
		case "findtreatment":
			dialog.text = "What pagan curses have befallen you, my son? Let me guess: you cannot run, a saber is too heavy for you and your movements are slow and sluggish?";
			link.l1 = "How did you know it, Father?";
			link.l1.go = "findtreatment_1";
		break;
		
		case "findtreatment_1":
			dialog.text = "Judging by your step as you approached me, my son, it was not too hard to see it. My the Lord be merciful to our sinful souls... Tell me, my son, and be honest - who has placed these enchantments upon you?";
			link.l1 = "You need a name, Father?";
			link.l1.go = "findtreatment_2";
		break;
		
		case "findtreatment_2":
			dialog.text = "If you do know the name, then speak it.";
			link.l1 = "Her name was... Jessica Rose.";
			link.l1.go = "findtreatment_3";
		break;
		
		case "findtreatment_3":
			dialog.text = "God save us! Delving into pagan rites may cast even stronger souls into the abyss of darkness...";
			link.l1 = "She died, Father.";
			link.l1.go = "findtreatment_4";
		break;
		
		case "findtreatment_4":
			dialog.text = "But... did she really die? Or... not completely?";
			link.l1 = "You're extremely insightful, Father. Now she's totally dead.";
			link.l1.go = "treatment_3";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment"); 
			DeleteAttribute(pchar, "questTemp.Saga.JessFindTreatment"); 
		break;
		
		
		
		case "GenQuest_Church_2_Start_1":
			dialog.text = "...and Lord's mercy! May the universal darkness consume their souls for their sins...";
			link.l1 = LinkRandPhrase("Father", "Padre", "Father") + ", aren't you a bit too zealous? You know, you can have a stroke...";
			link.l1.go = "GenQuest_Church_2_Start_2";
			link.l2 = "Well... shit. Farewell then.";
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_2":
			dialog.text = "Oh, "+ GetSexPhrase("my son","my daughter") +", terrible sacrilege, the most foul of crimes had just come to pass! Stealing from the church!!! It's like dipping one's hand into the pocket of the Lord Himself!";
			link.l1 = "Oh, I see... How did it happen?";
			link.l1.go = "GenQuest_Church_2_Start_3";
			link.l2 = LinkRandPhrase("It's very sad and stuff, but I really must go...", "My condolences, padre, but I have to go...", "You must have been relying on the Almighty too much. You should have used safer locks. Well, I have to go...");
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_3":
			dialog.text = "Under cloud of night, some scoundrels snatched everything collected by the parish! These blasphemers have taken even the sacrificial chalice!";
			link.l1 = "O tempora, o mores... But, I hope, you have undertaken something on a hot scent?";
			link.l1.go = "GenQuest_Church_2_Start_4";
		break;
			
		case "GenQuest_Church_2_Start_4":
			dialog.text = "But of course! I have excommunicated these blasphemous robbers, and now I am pronouncing an anathema against them!";
			link.l1 = "I do not doubt that it is the most effective measure. But I meant something more practical. To organize pursuit, for example.";
			link.l1.go = "GenQuest_Church_2_Start_5";
		break;
			
		case "GenQuest_Church_2_Start_5":
			dialog.text = "Ah, that does the simple priest bound by the vow of non-resistance to the evil can? These scoundrels certainly already far from here - drink away in taverns amassed by robbery, or give way to the debauch and dissipation in the cuddles of strange women! I hope, there to them and an end will come!";
			link.l1 = RandPhraseSimple("I am sure, that such end is much more attractive, than to dangle on a yard. However, I will not you interfere with. All kind", "Well, one time sooner or later it is fated all of us to leave to the forefathers - from such end and I would not refuse. However, already it is time me. I wish successes with your heavy labour.");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Father", "Padre", "Father") + ", but I am unconnected no vows and with readiness I will help Lord to approach the o'clock of retribution.";
			link.l2.go = "GenQuest_Church_2_Start_5_1";
		break;
		
		case "GenQuest_Church_2_Start_5_1": 
			dialog.text = "I will be praying for you, my son! Go now and give these swindlers their due!";
			link.l1 = "Have no doubt, " + RandPhraseSimple("Father", "Padre", "Father");
			link.l1.go = "GenQuest_Church_2_Start_6";
		break;
			
		case "GenQuest_Church_2_Start_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_2.StartQuest = true;
			PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City;	
			PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; 
			PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_2.AskPeople = true;
			PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
			PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
			PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank)+8)*543+3210;
			PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount)/3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		break;
			
		case "GenQuest_Church_2_Thief_2":
			dialog.text = "Well, perhaps the all-good Creator visits his foolish children with pestilence and hunger to punish them for their grave sins...";
				link.l1 = "For pride, for example, or greed... Why have you turned pale, padre?";
				link.l1.go = "GenQuest_Church_2_Thief_3";
			break;
			
		case "GenQuest_Church_2_Thief_3":
			if(rand(1) == 0) 
			{
				dialog.text = "Jesus, my Lord, show mercy on thy sinful servant... Have you... Have you found the robbers? Have you slain them?";
					link.l1 = "Or consider the ten commandments, known to every good Christian from the cradle: thou shalt not kill, thou shalt not steal, thou shalt not bear false witness. Can a God-fearing person violate them - and, all the more, a spiritual shepherd?!..";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
			}
			else
			{
				dialog.text = "There's such a thick air here... Have you found the robbers? Have you slain them?";
					link.l1 = "Or consider the ten commandments, known to every good Christian from the cradle: thou shalt not kill, thou shalt not steal, thou shalt not bear false witness. Can a God-fearing person violate them - and, all the more, a spiritual shepherd?!..";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_1_1":
			dialog.text = ""+ GetSexPhrase("My son, mister","My daughter, lady") +"... God forgive me... such money, such temptation... the man is weak, truly weak! I couldn't stand it... I was out of my mind... I prayed day and night, did penance, I was rigorously fasting, I was mortifying my flesh... Unworthy, I was begging the Heavens only to spare those poor men, whom I had tempted, driven by my own greed...";
			link.l1 = LinkRandPhrase("Father", "Padre", "Father") + ", calm down. They haven't told anything about it... and they won't be telling it, that's for sure. By the way, they have voluntarily returned to me the Communion chalice, which I brought back to you.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_2":
			dialog.text = "My Lord, I thank thee! You've heard the prayers of your unworthy servant, a stumbled sinner bogged down in filth and vices...";
			link.l1 = "Anyone could have stumbled... But since your repentance seems sincere, I'd say so: you're a decent man and a good priest. If you stand before the court, there will be no good out of it. And it is up to you to decide whether to stay  in Lord's service or not - only He can tell you that and guide you...";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_3":
			if(rand(1) == 0) 
			{
				dialog.text = ""+ GetSexPhrase("My son","My daughter") +"... With the tears of repentance and gratitude I shall accept this chalice from you. The purity and nobility of your soul have truly shaken me. I bless you with all my heart and I humbly beg you to accept this small reward of " + FindRussianMoneyString(iMoneyToCharacter) + "... I hope it's enough to cover your expenses?";
				
				link.l1 = "This is unnecessary, Father " + NPChar.name + ". I am not exactly the poorest person, so you better use this money for the good of your parish.";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				
				link.l2 = "���������, " + LinkRandPhrase("Father", "Padre", "Father") + ", that's more than enough.";
				link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("My son","My daughter") +"... With the tears of repentance and gratitude I shall accept this chalice from you as a sign of Lord's mercy and forgiveness. The purity and nobility of your soul have truly shaken me. I bless you with all my heart!";
				link.l1 = "Thank you for the blessing, " + LinkRandPhrase("padre.", "Father.") + ".";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				link.l1 = "Benediction, certainly, business necessary, but it would not be bad to support him by something more material, because in transit I bore the considerable spending...";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_6";
			}
			ChurchGenQuest2_RemoveCup();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("c�","���"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Thief_4_1_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6":
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "Oh, child, I am truly sorry... I hope this small contribution of " + FindRussianMoneyString(iMoneyToCharacter) + " should be enough to cover your expenses?";
			link.l1 = "Yes, " + LinkRandPhrase("padre.", "Father.") + ", thanks.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Thief_4_2_1":
			dialog.text = "I don't quite understand your insinuations, "+ GetSexPhrase("my son","my daughter") +", what are you talking about?!";
			link.l1 = "I am talking about terrible things that greed can do to a man. That I got from shake-rags allegedly robbing your church... Did you something want to say?";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_2":
			dialog.text = "I'd tell you, child, that you are talking to a clergy and you should show a little bit more respect, or you could end up regretting it. As for this chalice - I've never seen it before, but if you are willing to donate it to the parish, then...";
			link.l1 = "Hold your horses, padre. You won't have it until you explain yourself.";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_3":
			if(rand(1) == 0) 
			{
				dialog.text = "What is it there to explain?! Now, look - you're a "+ GetSexPhrase("clever man","clever girl") +", and surely you must understand that whatever these crooks might have told you that I had supposedly hired them, is a blatant lie! The Lord shall punish this blasphemers not only for sacrilege, but also for false evidence!";
				link.l1 = "Leave the Lord alone! How can you know what those poor things have told me - those you set me up against? Maybe, did I kill them before they had time to tell bad acts about your?";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
			}
			else
			{
				dialog.text = "There's nothing for me to talk about with you! You haven't fulfilled your obligation in the face of our Lord; you're swearing at the temple; you're attempting to blackmail a priest, displaying some church utensils - and it remains yet to be seen, how had you got hold on it! Thank the God that I am not calling the acolytes to catch you red-handed!";
				link.l1 = "Well... I see that you had bogged down in sin so deeply that you no longer fear the judgment of men. But there's yet divine justice, and every one of us shall answer to it sooner or later. Take your 'church utensils' and think if you are worthy to touch it, Father " + NPChar.name + ".";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
				link.l2 = "Please forgive me my doubts, Father, for a mortal heart is weak, and the soul is confused. Please take the chalice and give me your blessing.";
				link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1":
			dialog.text = "Mmmm... "+ GetSexPhrase("My son... Mister... Sir...","My daughter... Miss... Lady...") +" " + PChar.name + "... I am ready to bend before you... consider our disagreements, so to say... and compensate your expenses with this modest sum of " + FindRussianMoneyString(iMoneyToCharacter) + "... of course, if you are not going to involve others in this affair...";
			
			link.l1 = "I am not going to involve anyone. Take the chalice! And don't even think that I would accept the gold you were secretly pinching from the pockets of your parishioners!";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_1";
			
			link.l2 = "I nobody gather to mix in. Take a bowl! This gold I take only because expended in you plenty of time and money.";
			link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoneyToCharacter));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1":
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All"))
			{
				link.l1 = "Dire news, " + LinkRandPhrase("Father", "Padre", "Father") + ": the robbers were too treacherous and resourceful, and so I failed to get back the church gold...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
				break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
			{
				link.l1 = "Dire news, " + LinkRandPhrase("Father", "Padre", "Father") + ": I managed to catch up with the robbers, but my only trophy was this Communion chalice.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "I am certain, that you'll like the news - I approximately punished robbers and took away parish money for them, and also here this bowl for a participle.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				
				link.l2 = LinkRandPhrase("Father", "Padre", "Father") + ", I brought bad news... I had to spend plenty of time, forces and facilities, to hunt down scoundrels, but, when I nevertheless got to them. Appeared, that they had time to drink away and squander everything, except here this bowl for a participle...";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
			{
				dialog.text = "Oh, "+ GetSexPhrase("my son","my daughter") +", what could possibly have happened to me? It is your way that's full of dangers and anxiety, and my peaceful cell, dominion of refection and prayer, is a quiet island in a raging ocean of human passions...";
					link.l1 = "And nothing can disturb the serenity of your blissful solitude?";
					link.l1.go = "GenQuest_Church_2_Thief_2";
				break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "I am sure that news you will make happy - I punished robbers and brought parish money.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				
				link.l2 = LinkRandPhrase("Father", "Padre", "Father") + "... I force to distress you. I pursued robbers on all archipelago, overcame the great number of dangers and barriers, almost ruined oneself and eventually overtook them, but alas... they already had time to squander church money.";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1": 
			if(rand(1) == 0)	
			{
				if(rand(4) == 3) 
				{
					dialog.text = "Oh, "+ GetSexPhrase("my son","my daughter") +". Your words plunged me into deep sorrow - but not despair, for desperation is a mortal sin! The Lord has visited us with another trial in order to strengthen our faith.";
						link.l1 = "Amen, Father...";
						link.l1.go = "exit";
						sQuestTitle = NPChar.City + "ChurchGenQuest2";
						AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
						AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
						CloseQuestHeader(sQuestTitle);
						ChangeCharacterComplexReputation(PChar,"nobility", -2);
						DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
						NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
				}
				else
				{
					dialog.text = ""+ GetSexPhrase("My son","My daughter") +", don't lie to your spiritual shepherd.";
						link.l1 = "I am really sorry, Father, but I swear that I am telling the truth";
						link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
				}
			}
			else
			{
				
				iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
				dialog.text = "Oh, "+ GetSexPhrase("my son","my daughter") +". Your words plunged me into deep sorrow - but not despair, for desperation is a mortal sin! The Lord has visited us with another trial in order to strengthen our faith. But your efforts and expenses should be compensated, despite being fruitless. Please accept this modest sum - " + FindRussianMoneyString(iMoneyToCharacter) + " - and continue on your righteous path!";
					link.l1 = "Hmm!... Thank you, padre, I shall use this money for a virtuous cause.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
					link.l2 = LinkRandPhrase("Father", "Padre", "Father") + "... you're putting me on the spot. I cannot accept reward for the job I never did. You better use this money to renew the altar.";
					link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
			if(rand(6) == 3)
			{
				dialog.text = "Alright, I believe you, "+ GetSexPhrase("my son","my daughter") +". The Lord has visited us with another trial in order to strengthen our faith.";
				link.l1 = "Amen...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1"
				break;
			}
				dialog.text = "Despicable, did you really think deceive our Lord?! Curse you"+ GetSexPhrase("","") +"! Clean up it away and remember that these money will not bring no benefit to you!";
				link.l1 = "How is that?! Padre!..";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			ChangeCharacterComplexReputation(PChar,"nobility", -3);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			ChangeCharacterComplexReputation(PChar, "nobility", -6);
			AddCharacterExpToSkill(PChar, "Leadership", -50);
			AddCharacterExpToSkill(PChar, "Fortune", -70);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			npchar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1":
			if(rand(1) == 0) 
			{
				dialog.text = "Oh, "+ GetSexPhrase("my son","my daughter") +". Your words plunged me into deep sorrow - but not despair, for desperation is a mortal sin! The Lord has visited us with another trial in order to strengthen our faith.";
				link.l1 = "Amen, Father...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; 
			}
			else
			{
				dialog.text = "Yes, it is that very chalice that was gone with the money... But... If you got it, how come that you have not brought back the money? It was a hefty sum, and surely those rascals could not have spent it all so quickly... "+ GetSexPhrase("My son","My daughter") +", remember that there is no greater sin than lying to your spiritual shepherd and bearing false evidence in the temple in the face of God!";
				link.l1 = "Father " + NPChar.name + ", I almost lost my life, obtaining this vase - thought to make happy you. I will say nothing about that, how many spent money on all of it!";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
			}
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
			dialog.text = "Get lost and thank the Almighty who had given me a meek heart, for it is that only reason why you are not branded thief!";
			link.l1 = "How is that?! " + LinkRandPhrase("Father", "Padre", "Father") + "!..";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -5);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, iMoneyToCharacter);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -1);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_1":
			dialog.text = "Oh, "+ GetSexPhrase("my son","my daughter") +". Your words plunged me into deep sorrow - but not despair, for desperation is a mortal sin! The Lord has visited us with another trial in order to strengthen our faith.";
			link.l1 = "Amen, Father...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_1":
			dialog.text = "Lord, I thank Thee! Indeed, you were His tool, my child! I knew that or Celestial Father would show you the way and provide all the help you needed. I was praying without a break, and...";
			link.l1 = "You know, padre, in affairs like this one, weapons are surely more useful than prayers. But, apparently, your prayers indeed were heeded.";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_2":
			dialog.text = ""+ GetSexPhrase("My son","My daughter") +", I want to reward you deservedly, for you"+ GetSexPhrase(", like a true knight of Mother Church,","") +" did everything in power overca...";
			link.l1 = "Father, you are really exaggerating my humble achievements. I shall now leave you to praise our Lord...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
		

		case "donation":
			dialog.Text = "Of course, "+ GetSexPhrase("my son","my daughter") +". How much you would like to donate to the Holy Church?";
			Link.l1 = "I am sorry, saint father, but offering will not be.";
			Link.l1.go = "No donation";
			if(makeint(PChar.money)>=100)
			{
				Link.l2 = "My donation will be a modest one - just 100 pesos.";
				Link.l2.go = "donation paid_100";
			}
			if(makeint(PChar.money)>=1000)
			{
				Link.l3 = "1000 pesos. I think that should do.";
				Link.l3.go = "donation paid_1000";
			}
			if(makeint(PChar.money)>=5000)
			{
				Link.l4 = "I am lucky with money, so I will donate 5000 pesos.";
				Link.l4.go = "donation paid_5000";
			}
			
			if(pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = "Father, I want to make a donation not on my behalf. I am doing in on a request.";
				Link.l5.go = "HostessChurch";
			}
			
		break;

		case "No donation":
			dialog.Text = "Hmm... Well, this is your decision, and you are free to change your mind. And don't forget that this will be accounted for on the Day of Judgement.";
			Link.l1 = "As many other things will, too. Let's change the subject.";
			Link.l1.go = "node_3";
			Link.l2 = "I am sorry, Father, but it's time for me to leave.";
			Link.l2.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = "On behalf of the Holy Church I thank you, "+ GetSexPhrase("my son","my daughter") +", for your gift.";
			Link.l1 = "I need to talk to you, Father.";
			Link.l1.go = "node_3";
			Link.l2 = "I am sorry, Father, but it's time for me to leave.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = "On behalf of the Holy Church I thank you.";
            Link.l1 = "I need to talk to you, Father.";
			Link.l1.go = "node_3";
			Link.l2 = "I am sorry, Father, but it's time for me to leave.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = "�On behalf of the Holy Church I thank you, for your gift.";
            Link.l1 = "I need to talk to you, Father.";
			Link.l1.go = "node_3";
			Link.l2 = "I am sorry, Father, but it's time for me to leave.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "ispoved":
			dialog.text = "Of course, "+ GetSexPhrase("my son","my daughter") +", I am listening to you.";
			link.l1 = "I crossed my mind. It can be other time.";
			link.l1.go = "exit";
			link.l2 = "I am so full of sins, Father. A day will not be enough to list all my misdeeds...";
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = "Every one of us is a sinner, my child...";
			link.l1 = "Yes, but on my conscience the load of thousands of deaths lies a severe burden. I robbed and drowned ships...";
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = "I hope there were none among those that sailed under the flag of " + NationNameGenitive(sti(NPChar.nation)) + "?";
			link.l1 = "No, of course, not, Father.";
			link.l1.go = "ispoved_3";
			link.l2 = "All sorts of them, Father...";
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = "Then our Lord shall absolve you of those sins. For this is a cruel age, and by destroying the enemies of your sovereign you are saving the lives of his loyal subjects.";
			link.l1 = "Thank you, Father, that was a great consolation... I'll be going now.";
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = "The Lord shall not absolve you of such a sin! Pray and repent, repent and pray! There's only one way for you now - to the cloister!";
			link.l1 = "The cloister will have to wait. Not in this life, at the least. Farewell...";
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

        case "work":
        	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
        	{
        		dialog.text = "I am sorry, "+ GetSexPhrase("my son","my daughter") +", but all confessionals are busy at the moment. I will be able to listen to your confession in half an hour at the least.";
				link.l1 = "Excuse me, " + RandPhraseSimple("padre.", "Father.") + ", this is a different business. Father " + PChar.GenQuest.ChurchQuest_1.PriestName + " �� " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " when gave that to you priceless treasures of the theological library, now charged to return them me, if that to happen.";
				link.l1.go = "GenQuest_Church_1_Dialog_1";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
				break;
        	}
			dialog.text = "What kind of business has brought you here, "+ GetSexPhrase("my son","my daughter") +"?";
			link.l1 = "I want to ask you one question, Padre...";
			link.l1.go = "quests"; 
            link.l2 = RandPhraseSimple("I wanted to talk about working for the good of the church of " + NationNameGenitive(sti(NPChar.nation)) + ".",
                                        "How are things going in the parish? Do you need any help?");
			link.l2.go = "prihod";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
	            link.l3 = RandPhraseSimple("Padre.", "Father.") + ", I want to talk to you about financial businesses."; 
	            link.l3.go = "LoanForAll";
            }
			
            if (stf(pchar.Health.HP) < 60.0)
            {
                link.l4 = "I need healing.";
                link.l4.go = "healthAdd_1";
            }
            
			
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
	            link.l7 = RandPhraseSimple("Padre.", "Father.") + ", I am here on request of one certain man. His name is governor " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".";
	            link.l7.go = "IntelligenceForAll";
            }
			
			if (CheckAttribute(pchar, "GenQuest.Monkletter") && npchar.city == pchar.GenQuest.Monkletter.City)
			{
	            link.l10 = "Padre, I have brought you papers from a monk in the town of "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity)+".";
	            link.l10.go = "Monkletter";
            }
			
			
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "go" && sti(npchar.nation) == sti(pchar.GenQuest.Churchbooks.Nation) && npchar.city != pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "Padre, I am coming from the colony of "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity)+". The local church needs more prayer books, and that monk suggested seeing you regarding this matter.";
	            link.l11.go = "Churchbooks";
            }
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "return" && npchar.city == pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "Father, I have brought the prayer books for your parish.";
	            link.l11.go = "Churchbooks_2";
            }
			
			link.l99 = "I changed mind, I am awaited by business.";
			link.l99.go = "exit";
		break;

		case "prihod":
			if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
		    {
		        dialog.text = "That's great. And still, in these grim times, "+ GetSexPhrase("my son","my daughter") +", not every visitor of the temple can be useful to our Mother Church.";
				link.l1 = LinkRandPhrase("Father", "Padre", "Father") + ", I am a true Christian, and my intentions to serve our Mother Church are the most sincere."+ GetSexPhrase(" Who will support Her, if not her loyal knights, like myself?","") +"";
				link.l1.go = "GenQuest_Church_1_Start_1";
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; 
		    }
			else
			{
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	
			}	
            dialog.text = "Everything is quiet in the parish so far, "+ GetSexPhrase("my son","my daughter") +". Thank you for the offer.";
    		link.l2 = "Well, if things are fine, I guess I'll go about my business.";
    		link.l2.go = "exit";
			DeleteAttribute(npchar, "quest.add");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	
		break;
		
		
		case "GenQuest_Church_1_Start_1":
			dialog.text = "Well, I do have one rather delicate mission, which would require not only purity of intentions, but also great bravery and considerable discretion...";
			link.l1 = LinkRandPhrase("Father", "Padre", "Father") + ", I will be happy to render any service to you, even if for this purpose I will have to go out into hell! It will be said not in a church.";
			link.l1.go = "GenQuest_Church_1_Start_2";
		break;
			
		case "GenQuest_Church_1_Start_2":
			PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
			Church_GenQuest1_InitStartParam(NPChar);
			dialog.text = "Oh! Good... But, again, this is a very delicate business... Some time ago father superior " + PChar.GenQuest.ChurchQuest_1.ToName + " from " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + ", " + XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland + "Dat") + " took for me for a time a few theological labours and ancient manuscripts from a church library. Because a request was supported by the requirement of archbishop not to prevent to distribution of lovely light of knowledge, to say no I did not could, supposed though, that complication of voyages would not allow to return manuscripts him in time... Would not you could to assist permission of this problem?";
			link.l1 = "I am afraid, " + LinkRandPhrase("Father", "Padre", "Father") + ", that I won't live up to your expectation. This is a very delicate business, and only a real diplomat would succeed in settling it.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Father", "Padre", "Father") + ", your mission doesn't seem too complicated to me. I shall leave there at once.";
			link.l2.go = "GenQuest_Church_1_Start_3";
		break;
			
		case "GenQuest_Church_1_Start_3":	
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.StartQuest = true;
			PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_1.AskOwner = true;
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
		break;
			
		case "GenQuest_Church_1_Dialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene"))	
			{
				dialog.text = "Oh! Yeah... Indeed, now I remember... But, "+ GetSexPhrase("my son","my daughter") +", these treasures are more of spiritual rather than material nature! They already have aided my parishioners immensely and could have done so in the future!";
				link.l1 = "But, " + LinkRandPhrase("Father", "Padre", "Father") + ", the parishioners of Father " + PChar.GenQuest.ChurchQuest_1.PriestName + " are just in the same need of salvation, and without these works he's lacking support of the pillars of theosophy, and his sermons lack inspiration.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_1";
			}
			else	
			{
				dialog.text = "Oh, yes!.. Indeed... "+ GetSexPhrase("My son","My daughter") +", these treasures are more of spiritual rather than material nature! They already have aided my parishioners immensely, and that's why I still haven't returned them to their rightful owner, to my ignominy...";
				link.l1 = "Indeed, " + RandPhraseSimple("Father", "Padre", "Father") + ", indeed. That's why Father " + PChar.GenQuest.ChurchQuest_1.PriestName + " requested that I deliver this books to him personally.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_1": 
			dialog.text = "I understand, my child, but aren't we praying to our Lord every day: 'and forgive us our trespasses, as we forgive those who trespass against us'? And the church " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " on much rich of my modest arrival.";
			link.l1 = "You're certainly right, Father, but I just thought of other lines in the Holy Scripture: 'seek not for an easy path, for it is there where the Devil lies in wait for us, and his voice is all the more subtle and the temptation is all the more strong, the easier the path!' And padre " + PChar.GenQuest.ChurchQuest_1.PriestName + " was already going to send a message regarding your forgetfulness to the archbishop - I only just dissuaded him from that.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_1":
			dialog.text = "T-To the archbishop?! About such a petty thing!.. Why, really? I was going to send these works to my beloved brother in Christ anyway - it's just there wasn't a save opportunity to deliver them to him. But in you, "+ GetSexPhrase("my son","my daughter") +", I have seen a truly deserving servant of our Lord. Here - take these books and manuscripts and please deliver them to Father " + PChar.GenQuest.ChurchQuest_1.PriestName + " safe and sound. And also add to that my most sincere gratitude.";
			link.l1 = "By all means, " + LinkRandPhrase("Father", "Padre", "Father") + ". By all means.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			
			AddItems(PChar, "Bible", 1);	
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); 
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); 
			
		break;
			
		case "GenQuest_Church_1_Dialog_1_2":	
			
			sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "mercen_" + (rand(14)+14), "man", "man", 15, NPChar.nation, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 40, 35, "blade_13", "pistol3", "grapeshot", 30);
			FantomMakeCoolSailor(sld, 7 + rand(2), "", CANNON_TYPE_CANNON_LBS16, 75, 70, 65);
			sld.Abordage.Enable = false;
			sld.ShipEnemyDisable  = true; 
			LAi_SetImmortal(sld, true);
			sld.Dialog.FileName = "GenQuests_Dialog.c";
			sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
			Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetType("ChurchGenQuest1_CapGroup", "trade");
			Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetTaskNone("ChurchGenQuest1_CapGroup");
			Group_LockTask("ChurchGenQuest1_CapGroup");
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
			PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
			PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
			PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) 
			{
				dialog.text = "but, "+ GetSexPhrase("my son","my daughter") +"... You see, the deal is that last week I met a captain of vessel '" + sld.Ship.Name + "', where I was called to make communion of a dying sailor. To my great joy, captain " + GetFullName(sld) + " told me that he was going to " + XI_ConvertString("Colony" + GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown)) + ". And although he didn't warrant any terms, he still agreed to help and assured me, that to the port of " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " he will call certainly. Certainly, I took advantage of opportunity, sent away books with this kind man and handed their further fate to Lord.";
				link.l1 = "Hmm, are you certain that this captain could be trusted?.. Did he realize the value of the works entrusted to him and the importance of this mission?";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
			}
			else 
			{
				dialog.text = "Oh, "+ GetSexPhrase("my son","my daughter") +"! You were just several hours late! I have already sent the books of Father " + PChar.GenQuest.ChurchQuest_1.PriestName + " with captain " + PChar.GenQuest.ChurchQuest_1.CapFullName + ". This morning, that God-fearing man came to make a confession and mentioned that today his vessel was sailing to " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapColony) + ". And although sir captain didn't warrant any terms, he still agreed to help and assured me, that to the port of " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " he will call necessarily.";
				link.l1 = LinkRandPhrase("Father", "Padre", "Father") + "... are you certain that this captain could be trusted? And I also want to know, as his ship is named.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1":	
			dialog.text = "I trust people, "+ GetSexPhrase("my son","my daughter") +", every single one of us is created in our Lord's image and likeness, and His sacred fire is burning in every soul!";
			link.l1 = "Ugh. That's a weighty argument, for sure. Well... Then bless me, Father, and wish me luck in my search for that captain.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; 
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_1":
			dialog.text = "You should trust people, "+ GetSexPhrase("my son","my daughter") +". As for his ship - I don't have anything to say.";
			link.l1 = "And you have given precious manuscripts to some captain without even bothering to know the name of his ship?!!";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_2":
			dialog.text = "You see, "+ GetSexPhrase("my son","my daughter") +", captain " + PChar.GenQuest.ChurchQuest_1.CapFullName + " is a very God-fearing...";
			link.l1 = "Well, I already heard that.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_3":
			dialog.text = "Patience, "+ GetSexPhrase("young man","young lady") +"! Captain " + PChar.GenQuest.ChurchQuest_1.CapFullName + " is a very God-fearing person, and until this day his vessel bore a name, which a clergy should never say even in thought, let alone aloud! And today during his confession I had pointed this out to him. For, like the Bible says, the purity of the soul must be preserved by us, sinners, more than the purity of the body, for our Lord denies His Kingdom to the foul-mouthed...";
			link.l1 = "I see, " + LinkRandPhrase("Father", "Padre", "Father") + ", I see! " + PChar.GenQuest.ChurchQuest_1.CapFullName + ", a notorious gambler and drunkard, well known across all the Caribbean, decided to rename his old tub on your suggestion?..";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_4":
			dialog.text = "You're very insightful, "+ GetSexPhrase("my son","my daughter") +". I don't know the new name of this ship, but certainly it's gonna be something exalted.";
			link.l1 = "Oh, " + RandPhraseSimple("Father", "Padre", "Father") + "... Thank you for everything. And pray for my sinful soul...";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
		break;
			
		case "GenQuest_Church_1_Complete_1":
			dialog.text = "Oh, my child! I have been praying zealously, and everything seems to have resolved it the best way possible! For your help and faith, "+ GetSexPhrase("my son","my daughter") +", paradise and angelic singing will certainly be waiting for...";
			link.l1 = RandPhraseSimple("Padre.", "Father.") + ", I am not going to meet Saint Peter any time soon, God forbid. As for the living - they do require many material things beside promises of heavenly bliss...";
			link.l1.go = "GenQuest_Church_1_Complete_2";
		break;
			
		case "GenQuest_Church_1_Complete_2":
			dialog.text = "Yes, yes, "+ GetSexPhrase("my son","my daughter") +", of course. I will reward you deservedly. Here, take this and remember that our Lord punishes those foolish souls, who crave too much for earthly blessings and worship the yellow devil!";
			link.l1 = "Thank you, " + LinkRandPhrase("Father", "Padre", "Father") + ". Please take your long-expected books and manuscripts and pray for my sinful soul... Farewell!";
			link.l1.go = "GenQuest_Church_1_Complete_3";
		break;
			
		case "GenQuest_Church_1_Complete_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			RemoveItems(PChar, "Bible", 1);
			items[FindItem("Bible")].Name = "itmname_bible";
			BackItemDescribe("Bible");
			DeleteAttribute(items[FindItem("Bible")], "City");
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddCharacterExpToSkill(PChar, "Leadership", 50); 
			AddCharacterExpToSkill(PChar, "Fortune", 50); 
			TakeNItems(pchar, "chest", 3+drand(1));
			PlaySound("interface\important_item.wav");
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
			Group_DeleteGroup("ChurchGenQuest1_CapGroup"); 
			PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = true; 
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSumm", FindRussianMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
			break;
		

        case "healthAdd_1":
            if (GetHealthMaxNum(pchar) == 6) 
            {
                dialog.text = "Your health " + GetHealthNameMaxSmall(pchar) + ", and the wounds will close up by themselves. You just need to avoid bloodshed and take care of your health.";
    			link.l1 = "Thank you, that's surely a relief. I'll try to restrain myself from fights for some time.";
    			link.l1.go = "exit";
            }
            else
            {
    			dialog.text = "Your health " + GetHealthNameMaxSmall(pchar) + ", and although the wounds will close up by themselves, you should take care of it.";
    			link.l1 = "What is needed for that?";
    			link.l1.go = "healthAdd_2";
			}
			link.l2 = "And why does my health gets worse?";
    		link.l2.go = "healthAdd_info";
		break;

		case "healthAdd_info":
			dialog.text = "That's very simple, "+ GetSexPhrase("my son","my daughter") +", you take damage each time you're wounded. That doesn't slip by without a trace. Your health gets worse with every wound, and, as a result, you become weaker. Your command, seeing weak fugleman, loses respect to you. But you are done by more careful and ability of defence increases temporally. Timely rest and small wounds will help to remain always much force.";
			link.l1 = "Thank you for the enlightenment.";
			link.l1.go = "exit";
		break;

		case "healthAdd_2":
			dialog.text = "Prayers and abstaining from violence, "+ GetSexPhrase("my son","my daughter") +". Then the Lord will give you back that which you have lost.";
			link.l1 = "But could you pray for me?";
			link.l1.go = "healthAdd_3";
			link.l2 = "So there is no way? Hmm... You've certainly reassured me, thanks.";
			link.l2.go = "exit";
		break;

		case "healthAdd_3":
            if (npchar.quest.HealthMonth != iMonth)
            {
    			dialog.text = "Me? This is likely possible. But you will have to make a donation to our parish.";
    			link.l1 = pcharrepphrase("How much?", "Gladly! How much?");
    			link.l1.go = "healthAdd_4";
    			link.l2 = "I guess I'll manage myself...";
    			link.l2.go = "exit";
			}
			else
			{
                dialog.text = ""+ GetSexPhrase("My son","My daughter") +", I am already praying for your well-being. These prayers will take up all my time until the end of the month.";
    			link.l1    = "Thank you, "+RandPhraseSimple("padre.", "Father.");
    			link.l1.go = "exit";
			}
		break;

		case "healthAdd_4":
			dialog.text = "A hundred thousand pesos will be a sufficient payment for the miracle of healing.";
			link.l1 = pcharrepphrase("What?!! Are you totally crazy? I'll pay such a sum once I'll have robbed a couple of churches!", "That's too much for me. True they say - health cannot be bought for money.");
			link.l1.go = "exit";
            if (sti(pchar.Money) >= 100000)
            {
    			link.l2 = "I agree!";
    			link.l2.go = "healthAdd_5";
			}
		break;

		case "healthAdd_5":
            AddMoneyToCharacter(pchar, -100000);
            AddCharacterMaxHealth(pchar, 4); 
            npchar.quest.HealthMonth = iMonth;
			dialog.text = "Fine. Your health will improve a little. But you still need to avoid skirmishes and take good care of yourself, or this effect wears off. I will need to spend an entire month in prayers for your perishable body.";
			link.l1 = "Thanks. Should anything happen, I'll come to see you again in a month.";
			link.l1.go = "exit";
		break;
		
		
		case "HostessChurch":
			dialog.text = "And who is that kind soul donating the money?";
			link.l1 = "Hmm... That's the madam of the local brothel.";
			link.l1.go = "HostessChurch_call";
			link.l2 = "I would prefer to keep the names secret. There can be an anonymous donation, right?";
			link.l2.go = "HostessChurch_notCall";
			pchar.questTemp.different = "HostessChurch_return"; 
		break;
		
		case "HostessChurch_call":
			if (isBadReputation(pchar, 5)) 
			{
				if (rand(100) < GetCharacterSkill(pchar, "Fortune")) 
				{
					dialog.text = "You are a sinner, yet for a sinner does ask? About the soul would think better, in fact all of us will appear before Lord!";
					link.l1 = "That's true. I hope that our Lord will be merciful to me... So, what about the donation?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Get thee behind me, Satan!!! Take your unholy money and get lost!";
					link.l1 = "How so, Father?! We came to you with an open heart, and you...";
					link.l1.go = "HostessChurch_bad";
				}
			}
			else
			{
				if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) 
				{
					dialog.text = "I am glad that you are helping the sinners to find their way to our Lord. For that you will be given your due in Heaven!";
					link.l1 = "That'd be great! So, what about the donation?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "I cannot accept money procured in sin. Return it to that loose woman, "+ GetSexPhrase("my son","my daughter") +". One cannot find a way to God through money.";
					link.l1 = "It's a pity that you are rejecting her. A pity indeed.";
					link.l1.go = "HostessChurch_bad_1";
				}
			}
		break;
		
		case "HostessChurch_notCall":
			if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				dialog.text = "To take this money, without even knowing, where it came from...";
				link.l1 = "Yes, padre, exactly. Please accept this contribution, made from the heart!";
				link.l1.go = "HostessChurch_ok_1";
			}
			else
			{
				dialog.text = "To take this money, without even knowing, where it came from? Are you crazy?! And what if this money is stained with blood!";
				link.l1 = "Father, all money is stained with blood...";
				link.l1.go = "HostessChurch_bad_2";
			}
		break;

		case "HostessChurch_ok":
			dialog.text = "I accept it, "+ GetSexPhrase("my son","my daughter") +". Go and tell that your loose woman.";
			link.l1 = "Alright, padre. Thank you.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_ok_1":
			dialog.text = "I accept it, "+ GetSexPhrase("my son","my daughter") +". Tell about it that donator of yours.";
			link.l1 = "Alright, padre. Thank you.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_bad":
			dialog.text = "Get lost, scion of Hell, and don't you dare to show your face here again!";
			link.l1 = "Heh, whatever.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.quest.BadMeeting = lastspeak_date;
			
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_1":
			dialog.text = "This is my decision. Go in peace, "+ GetSexPhrase("my son","my daughter") +".";
			link.l1 = "Farewell, padre.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_2":
			dialog.text = "That's what you think, blasphemer! Leave the temple this instant and don't you dare to show your face here again!";
			link.l1 = "Oh, really? Nevermind, I'll leave...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			npchar.quest.BadMeeting = lastspeak_date;
			
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;

		
		case "Monkletter":
			if (CheckAttribute(pchar, "GenQuest.Monkletter.Late"))
			{
				dialog.text = "I almost lost hope to see these papers again. Why did it take you so long, my son?";
				link.l1 = "It was... unforeseen developments, Father.";
				link.l1.go = "Monkletter_1";
			}
			else
			{
				dialog.text = "I've been waiting for these papers, son. Thank you for swift delivery. Please accept these coins and go with my blessing.";
				link.l1 = "Thank you, Father. It was my pleasure to help the Holy Church!";
				link.l1.go = "Monkletter_3";
			}
		break;
		
		case "Monkletter_1":
			dialog.text = "We are all in God's hands, my son... Man proposes, but God disposes. Hand me these papers and go in peace.";
			link.l1 = "Here you go, padre. All the best to you!";
			link.l1.go = "Monkletter_2";
		break;
		
		case "Monkletter_2":
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);
			AddQuestRecord("Monkletter", "2");
			CloseQuestHeader("Monkletter");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter_3":
			dialog.text = "God's blessing, my son. May the Almighty watch over you in your travels!";
			link.l1 = "Goodbye, Father.";
			link.l1.go = "Monkletter_4";
		break;
		
		case "Monkletter_4":
			pchar.quest.Monkletter_Over.over = "yes"; 
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);
			AddQuestRecord("Monkletter", "3");
			CloseQuestHeader("Monkletter");
			TakeNItems(pchar, "gold_dublon", 10+rand(5));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		
		
		case "Churchbooks":
			dialog.text = "You've been sent to take from us prayer books for the church of "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity+"Gen")+"? Well. I have packing with three ten of prayer books. Take her, my son.";
			link.l1 = "Thank you, padre. Goodbye!";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			dialog.text = "May the Lord watch over you in your travels! Go in peace...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Churchbooks", "2");
			pchar.GenQuest.Churchbooks = "return";
			GiveItem2Character(pchar, "prayer_book");
		break;
		
		case "Churchbooks_2":
			if (CheckAttribute(pchar, "GenQuest.Churchbooks.Late"))
			{
				dialog.text = "Thank you for your help, my son, although it had arrived with some delay.";
				link.l1 = "I was delayed by unforeseen developments, Father.";
				link.l1.go = "Churchbooks_3";
			}
			else
			{
				dialog.text = "Thank you for your help, my son. You have brought these books just in time. Please accept this sanctified ward as a reward - it shall keep you from harm in the darkest hour.";
				link.l1 = "Thank you, Father. It was my pleasure to help the Holy Church!";
				link.l1.go = "Churchbooks_4";
			}
		break;
		
		case "Churchbooks_3":
			dialog.text = "God knows best, my son. Go in peace!";
			link.l1 = "Goodbye, padre.";
			link.l1.go = "exit";
			RemoveItems(PChar, "prayer_book", 1);
			AddQuestRecord("Churchbooks", "3");
			CloseQuestHeader("Churchbooks");
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;
		
		case "Churchbooks_4":
			dialog.text = "God's blessing, my son. May the Almighty keep you from harm on your ways!";
			link.l1 = "Goodbye, Father.";
			link.l1.go = "Churchbooks_5";
		break;
		
		case "Churchbooks_5":
			pchar.quest.Churchbooks_Over.over = "yes"; 
			DialogExit();
			RemoveItems(PChar, "prayer_book", 1);
			GiveItem2Character(pchar, pchar.GenQuest.Churchbooks.Item);
			Log_Info("You have received '"+XI_ConvertString(pchar.GenQuest.Churchbooks.Item)+"'");
			AddQuestRecord("Churchbooks", "4");
			CloseQuestHeader("Churchbooks");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;
	}
}

void ChurchGenQuest2_RemoveCup()
{
	RemoveItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	DeleteAttribute(rItem, "City");
	rItem.Weight = 2;
	rItem.Name = "itmname_Bible";
	rItem.picIndex = 6;
	rItem.picTexture = "ITEMS_9";
	BackItemDescribe("Bible");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
	string sColony = SelectNotEnemyColony(chr); 
	PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
	PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
	PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].Island;
	PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;
	
	
	int iRand = Rand(2);
	switch(iRand)
	{
		case "0":
			PChar.GenQuest.ChurchQuest_1.2A_Scene = true;
			Log_TestInfo("��������� ��������� 1: �������� ����� - 2� (������ ������� � ���������� ��������)."); 
		break;
		
		case "1":
			PChar.GenQuest.ChurchQuest_1.2BA_Scene = true;
			Log_TestInfo("��������� ��������� 1: �������� ����� - 2�-� (����� ����. � ��� ���� ������ ����).");
		break;
		
		case "2": 
			PChar.GenQuest.ChurchQuest_1.2BB_Scene = true;
			Log_TestInfo("��������� ��������� 1: �������� ����� - 2�-� (����� ����. �������� ���� ����������.)"); 
		break;
	}
}
