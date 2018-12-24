// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;   
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions, "+ GetSexPhrase("young man","young lady") +"?", "What do you want, "+ GetSexPhrase("handsome","pretty one") +"? Ask it."), "Questions again", "Tee-hee, it's all the same for third time this day - questions...",
                          ""+ GetSexPhrase("Hm, why don't you pick up a beauty for yourself? I am starting to get suspicions about you...","Hm, why don't you pick up a beauty for yourself? We don't have boys here, sorry, tee-hee...") +"", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind.", "Well, it is nothing."), "I can't... no questions...",
                      "You're right it the third time already. Pardon me.", "Not now... next time...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> ����� ��������
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start")
			{
				link.l1 = "Listen, Aurora, I need a girl for this night. And I want to take her to my place. Can you help me with that?";
                link.l1.go = "Gigolo";
			}	
			//<-- ����� ��������
		break;
		
		//--> ����� ��������
		case "Gigolo":
			dialog.text = "Sure, darling. What kind of girl do you need? Have you already found the girl for yourself or you don't care?";
			link.l1 = "I do care. I need a girl named Lutess.";
			link.l1.go = "Gigolo_1";
		break;
		
		case "Gigolo_1":
			dialog.text = "You talk about Lutess Montagne?";
			link.l1 = "To be honest, I didn't ask her surname. I only know that she is young and hot blonde named Lutess.";
			link.l1.go = "Gigolo_2";
		break;
		
		case "Gigolo_2":
			dialog.text = "Very well... Tell me why have you chosen her? Are you not interested in other girls?";
			link.l1 = "Hm.. She has been working for you for a short time and I think that she is not the best girl in this job and can't cost a lot.";
			link.l1.go = "Gigolo_2_1";
			link.l2 = "I admire blondies with fair skin. That is why I have chosen her.";
			link.l2.go = "Gigolo_2_2";
		break;
		
		case "Gigolo_2_1":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand1) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 5000;
				dialog.text = "You are wrong. She is young, pretty, experienced and my clients like her. She will cost you. You have to pay five thousands pesos for night with her not a single centime less.";
				if (sti(pchar.money) >= 5000)
				{
					link.l1 = "Hm... Expensive. But I never turn away from my wishes. Here, take your coins.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Heh! I don't have that much money now. Let's get back to this talk later.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 2500;
				dialog.text = "Well, it's true. She has a lack of experience and my clients don't usually notice her, that was the reason why I asked. But if you are really fond of modest girls then I say it's a good choice. You have got to pay two thousands and five hundred pesos for a night with her.";
				if (sti(pchar.money) >= 2500)
				{
					link.l1 = "It's no problem. Take the money.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Heh! I don't have that much money now. Let's get back to this talk later.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_2_2":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand2) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 4500;
				dialog.text = "Yes and you are not alone in that. My clients have been standing in a queue for her sometimes. She is a very different from the dark-skinned daughters of our islands. You have got to pay four thousands and five hundred pesos for a night with her.";
				if (sti(pchar.money) >= 4500)
				{
					link.l1 = "Hm... Expensive. But I never turn away from my wishes. Here, take your coins.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Heh! I don't have that much money now. Let's get back to this talk later.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 3000;
				dialog.text = "Really? Feel a nostalgia for Europe perhaps? My Creoles and mulattos are much more passionate than this daughter from the Paris ghettos. But I would be glad if you really likes her. It will cost three thousands pesos. ";
				if (sti(pchar.money) >= 3000)
				{
					link.l1 = "It's no problem. Take the money.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Heh! I don't have that much money now. Let's get back to this talk later.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharlie.Gigolo.Money));
			dialog.text = "Very well, dear. The girl will free herself at eleven p.m. and she will be waiting for you. She must return not later than seven a.m. If you won't take her before the midnight, another client will and you will have to wait next evening\nAnd don't even try to... hurt her or I guarantee problems for you. Don't think of it as a threat, I am only warning you.";
			link.l1 = "Don't worry I am going to take this girl for a love not for a something else. I'll take her at eleven o'clock. Farewell!";
			link.l1.go = "Gigolo_4";
		break;
		
		case "Gigolo_4":
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DialogExit();
			AddQuestRecord("SharlieC", "2");
			pchar.questTemp.Sharlie.Gigolo = "girl";
			Sharlie_CreateGigoloGirl();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

