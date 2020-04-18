
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) 
			{
				dialog.text = "It`s good to see you, my son.  You are here to wipe away your debt?";
				if (GetCharacterItem(pchar, "gold_dublon") >= 100 && sti(pchar.money) >= 50000)
				{
					link.l1 = "Yes, pater. I am.";
					link.l1.go = "FastStart_7";
				}
				else
				{
					link.l1 = "I am sorry for the delay, but I am not. But I will don`t you worry.";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
			{
				dialog.text = "Is there something you need, my son?";
				link.l1 = "Yes, father. I would like to see my brother, Michel de Monper. He said...";
				link.l1.go = "escape";
				break;
			}
			dialog.text = "Is there something you need, my son?";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) 
			{
				link.l1 = "Yes, pater. I need your help. My name is "+GetFullName(pchar)+". Michelle de Monper advised me to talk to you.";
				link.l1.go = "FastStart";
			}
			if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) 
			{
				link.l1 = "Yes, father. I need your help.  My name is "+GetFullName(pchar)+". I was advised to talk to you by my brother, Michel de Monper.";
				link.l1.go = "meet";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Yes, pater. I need a ship to help Michelle yet I have just recently arrived to the Caribbean and my purse is empty. My brother told me you could lend me some money...";
				link.l1.go = "FastStart_2";
			}
			if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Yes, father. I need your help.";
				if (CheckAttribute(npchar, "quest.relation_info")) link.l1.go = "help";
				else link.l1.go = "help_start";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && GetCharacterItem(pchar, "gold_dublon") >= 100 && sti(pchar.money) >= 50000)
			{
				link.l2 = "Yes, pater. I am.";
				link.l2.go = "FastStart_7";
			}
			link.l9 = "No, nothing, father.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Benua_meeting":
			dialog.text = "What brings you to me, my son?";
			link.l1 = "Hello, father. I was advised to talk to you. My name is Charles de Maure. I am searching for Michel de Monper. As far as I know, he should be somewhere here on Martinique. I'm... his brother.";
			link.l1.go = "Benua_meeting_1";			
		break;
		
		case "Benua_meeting_1":
			dialog.text = "Michel de Monper's brother? De Maure? How strange...";
			link.l1 = "I understand your doubts, father. We simply have different fathers. My father is Henry de Monper.";
			link.l1.go = "Benua_meeting_2";			
		break;
		
		case "Benua_meeting_2":
			dialog.text = "A-ah, I see now. I used to know Henri de Monper personally. Turn yourself to the light, young man. Right! You do look like him. Same looks, same noble side view! I am glad to see a son of Henri de Monper in our parish\nAnd concerning your question I will tell you that Michel is a high-ranked officer of the Order of Malta, but he is... in trouble. Come here tomorrow, my son, and I will introduce you to one man, I believe he will be able to get you to your brother. Go to the tavern now, get some rest.";
			link.l1 = "Thank you, father. I will be here tomorrow morning.";
			link.l1.go = "Benua_meeting_3";			
		break;
		
		case "Benua_meeting_3":
			DialogExit();
			NextDiag.CurrentNode = "Benua_meeting_repeat";
			AddQuestRecord("Sharlie", "4");
			pchar.quest.Sharlie_Benua.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Benua.win_condition.l1.date.hour  = 6;
			pchar.quest.Sharlie_Benua.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Sharlie_Benua.function = "Sharlie_BenuaMaltie";
		break;
		
		case "Benua_meeting_repeat":
			dialog.text = "My son, come tomorrow morning. At the moment, I have nothing more to tell you.";
			link.l1 = "All right.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Benua_meeting_repeat";
		break;
		
		case "Benua_maltie":
			dialog.text = "Hello, my son. As promised, the person you're needing is already here waiting for you. He's ready to show you to your miserable brother. May the Lord have mercy on his soul...";
			link.l1 = "Who is this man, holy father?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break;
		
		case "escape":
			dialog.text = "Yes, Charles, I'm aware of that. But I must disappoint you. Michel is not here.";
			link.l1 = "What do you mean he's not here? He said that he'd be waiting for me in your church! Father, what happened? Where's my brother?!";
			link.l1.go = "escape_1";
		break;
		
		case "escape_1":
			dialog.text = "My son, your brother was here and he left my modest tabernacle late last night. Where he did he go, I don't know. But he left you this letter.";
			link.l1 = "I can't believe it... after what I did for him! Give me that letter!";
			link.l1.go = "escape_2";
		break;
		
		case "escape_2":
			dialog.text = "Don't get go enraged, Charles. Here's the letter. Read it and then... then I would like to speak with you. But first read your brother's message.";
			link.l1 = "I'm burning from impatience!";
			link.l1.go = "escape_3";
		break;
		
		case "escape_3":
			DialogExit();
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_mishelle");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Mishelle";
			NextDiag.CurrentNode = "escape_4";
		break;
		
		case "escape_4":
			if (CheckAttribute(pchar, "GenQuest.specialletter.read") && pchar.GenQuest.specialletter.read == "Letter_Mishelle")
			{
				dialog.text = "I see you read the letter. Now I would like to tell you something, Charles...";
				link.l1 = "But... how can that be? What kind of balderdash is this? I know my brother is peculiar, but he's not a madman!";
				link.l1.go = "escape_5";
			}
			else
			{
				dialog.text = "My son, read the letter. We'll speak later.";
				link.l1 = "Yes, father...";
				link.l1.go = "exit";
				NextDiag.TempNode = "escape_4";
			}
		break;
		
		case "escape_5":
			dialog.text = "Your brother's actions surprise me as well, Charles. In addition, I still have my moments of perplexity. A loyal servant of the Order and the Trinity and he's behaving like a deserter.";
			link.l1 = "You have no idea what is the reason of such strange behaviour?";
			link.l1.go = "escape_6";
		break;
		
		case "escape_6":
			dialog.text = "Alas, I do not. But I suppose that he does have motives of his own, deep motives. For abrogating one's entire past would suggest an extremely significant reason. I can't even imagine what it is. But I sense, that it involves something extremely bad... even awful.";
			link.l1 = "What could it be, father?";
			link.l1.go = "escape_7";
		break;
		
		case "escape_7":
			dialog.text = "My son, a priest sees not with his eyes, but with his heart. I cannot explain to you in words, but... you brother has set forth to do something unclean. I never though my mouth could utter this, however...";
			link.l1 = "Well, I don't doubt that my brother has planned something unclean. I can even get what it exactly he's planning to do. This 'something' involves something yellow and makes a nice clink sound.";
			link.l1.go = "escape_8";
		break;
		
		case "escape_8":
			dialog.text = "I don't think the lust for gold is what drives you brother. I would say that he needs something bigger.";
			link.l1 = "I have learned a lot from Michel and have a grasp on his philosophy, so I can assume what's important to him and what isn't. But I will keep your words in mind, reverend father.";
			link.l1.go = "escape_9";
		break;
		
		case "escape_9":
			dialog.text = "God bless you, my son. Go, now. My the Lord watch over you!";
			link.l1 = "Thank you, father. Goodbye!";
			link.l1.go = "escape_10";
		break;
		
		case "escape_10":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			pchar.questTemp.Sharlie = "escape";
			CloseQuestHeader("Sharlie");
			AddQuestRecord("Guardoftruth", "1");
			pchar.questTemp.Guardoftruth = "begin";
			
			sld = GetCharacter(NPC_GenerateCharacter("spa_baseprisoner", "q_spa_off_1", "man", "man", 30, SPAIN, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_13", "pistol1", "bullet", 150);
			sld.dialog.FileName = "Quest\Sharlie\Guardoftruth.c";
			sld.dialog.currentnode = "spa_prisoner";
			RemoveAllCharacterItems(sld, true);
			LAi_SetStayType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Fortfrance_dungeon", "quest", "quest1");
			LAi_CharacterDisableDialog(sld);
		break;
		
		
		case "meet":
			dialog.text = "Michel de Monper's brother? De Maure? How strange...";
			link.l1 = "I understand your doubts, father. We simply have different fathers. My father is Henry de Monper.";
			link.l1.go = "meet_1";			
		break;
		
		case "meet_1":
			dialog.text = "A-ah, I see now. I new Henri de Monper personally. Turn yourself to the light, young man... Right! You do look like him. Same looks, same noble side view! I am glad to see a son of Henri de Monper in our parish\nI have already heard that Michel was visited by some man arrived from Europe, but I couldn't even imagine that it was his own brother. I hope that you will be able to help Michel, he is experiencing a difficult time. So how can I be of service?";
			link.l1 = "Michel told me that you would be able to help if I get into specific troubles with the authorities.";
			link.l1.go = "help_info";	
			npchar.quest.meet = true;
		break;
		
		case "help_info":
			dialog.text = "That is what Michel told you? I see. Well, I can be of some help in such matters. I have some influence within Holy Roman Church and Dutch colonies. Therefore I might to intercede for you to the Spanish and the Dutch authorities. Surely, I won't be able to do much if your misconduct is too heavy - in that case only a slight extenuation can be achieved\nIt will require several intercessions for a complete reconciliation. Besides, you will have to supply me with golden doubloons for charities and for voyage spendings. Only one nation at one go, of course. If you find it acceptable then don't hesitate to appeal, we'll see what can be done.";
			link.l1 = "Thank you! I'll keep that in mind.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "help_start":
			dialog.text = "What can I do for you, my son? Speak, I am listening.";
			link.l1 = "Michel told me that you would be able to help if I get into specific troubles with the authorities.";
			link.l1.go = "help_info";
		break;
		
		case "help":
			dialog.text = "How can I help you, my son?";
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "I've got into troubles with the Spanish authorities.";
				link.l1.go = "relation_spa";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "I've got into troubles with the Dutch authorities.";
				link.l2.go = "relation_hol";
			}
			link.l9 = "Sorry, I think I'll handle things myself.";
			link.l9.go = "exit";
		break;
		
		case "relation_spa": 
			pchar.GenQuest.BenuaNation = SPAIN;
			dialog.text = "So, the noble seniors are eager to put you inside Havana's dungeons...";
			link.l1 = "Exactly so, father...";
			link.l1.go = "relation";
		break;
		
		case "relation_hol":
			pchar.GenQuest.BenuaNation = HOLLAND;
			dialog.text = "So, the smart merchants are eager to put you inside Willemstad's dungeons...";
			link.l1 = "Exactly so, father...";
			link.l1.go = "relation";
		break;
		
		case "relation":
			rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
			if (rate <= 10)
			{
				dialog.text = "Yes, those rumours have reached our church as well. I can help you with your dilemma. It's something that can be solved. I need two hundred fifty gold doubloons to smooth out the predicament.";
				if (GetCharacterItem(pchar, "gold_dublon") >= 250)
				{
					link.l1 = "Great! Here's the gold.";
					link.l1.go = "agree";
					iTotalTemp = 250;
				}
				link.l2 = "Then it's just the right time for me to go get the coins.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate <= 20)
				{
					dialog.text = "Yes, rumours of your 'feats' have reached our church as well. You've tarnished your reputation, my son. You should be more prudent. But I can help you. I need five hundred gold doubloons to smooth out the predicament.";
					if (GetCharacterItem(pchar, "gold_dublon") >= 500)
					{
						link.l1 = "Great! Here's the gold.";
						link.l1.go = "agree";
						iTotalTemp = 500;
					}
					link.l2 = "Then it's just the right time for me to go get the coins.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Yes, my son. You're just as desperate as your brother... This is probably a family trait. I can't completely correct the situation, but nevertheless, I believe I can soften your dismal predicament. And later we will make more offering if you wish. I need six hundred gold doubloons and I will begin solving your dilemma right away.";
					if (GetCharacterItem(pchar, "gold_dublon") >= 600)
					{
						link.l1 = "Great! Here's the gold.";
						link.l1.go = "agree";
						iTotalTemp = 600;
					}
					link.l2 = "Then it's just the right time for me to go get the coins.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveItems(pchar, "gold_dublon", iTotalTemp);
			Log_Info("You've given "+iTotalTemp+" doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Now wait at least two weeks. I think that in this time I'll be able to meet and have a word with the right people.";
			link.l1 = "Thank you, father! I will be waiting...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, 10+rand(5), false);
			pchar.GenQuest.BenuaNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
			npchar.quest.relation = "true";
		break;
		
		
		case "FastStart":
			dialog.text = "De Maure? And you are a brother of Michelle de Monper? Odd...";
			link.l1 = "I understand your doubts, padre. My father is Henri de Monper.";
			link.l1.go = "FastStart_1";			
		break;
		
		case "FastStart_1":
			dialog.text = "A-ah, I see. I knew Henri de Monper personally. Turn to the light, young man� Right! Same eyes, same noble features! I am pleased to see a son of Henri de Monper in my church. Hope you will help you brother out� He had a bad luck recently.";
			link.l1 = "Yes, pater. I need a ship to help Michelle yet I have just recently arrived to the Caribbean and my purse is empty. My brother told me you could lend me some money...";
			link.l1.go = "FastStart_2";	
			npchar.quest.meet = true;
		break;
		
		case "FastStart_2":
			dialog.text = "Michelle told you so?";
			link.l1 = "Padre, it may sound not trustworthy yet it`s true. The sooner I get a ship, the sooner I will get my brother out of jail.";
			link.l1.go = "FastStart_3";
		break;
		
		case "FastStart_3":
			dialog.text = "I see, my son. I can hear you speaking the truth. Well, for the sake of Michelle and your father I will help you out. I have some saving, take them. I assume 50 000 pesos and 100 doubloons will suffice.";
			link.l1 = "Thank you, padre. What are the terms?";
			link.l1.go = "FastStart_4";
		break;
		
		case "FastStart_4":
			AddMoneyToCharacter(pchar, 50000);
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "No pressure. A half of a year will be enough.";
			link.l1 = "Very good, holy father. Thank you again!";
			link.l1.go = "FastStart_5";
		break;
		
		case "FastStart_5":
			dialog.text = "Go with my blessing, my son.";
			link.l1 = "...";
			link.l1.go = "FastStart_6";
		break;
		
		case "FastStart_6":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			npchar.quest.FastStart = "true";
			pchar.questTemp.Sharlie.BenuaLoan = "true";
			SetFunctionTimerCondition("Sharlie_BenuaLoanTime", 0, 0, 180, false);
			AddQuestRecord("Sharlie", "5-2");
		break;
		
		case "FastStart_7":
			dialog.text = "Splendid, my son. Hope these money did you some good.";
			link.l1 = "You bet they did! Thanks!";
			link.l1.go = "FastStart_8";
		break;
		
		case "FastStart_8":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddMoneyToCharacter(pchar, -50000);
			RemoveItems(pchar, "gold_dublon", 100);
			pchar.quest.Sharlie_BenuaLoanTime.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.BenuaLoan");
			AddQuestRecord("Sharlie", "5-3");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
