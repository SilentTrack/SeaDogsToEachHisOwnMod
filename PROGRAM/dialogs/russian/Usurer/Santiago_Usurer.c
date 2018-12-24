// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?", "How can I help you?"), "You tried to ask me that question not long ago...", "Yup, let me guess... Once again going around in circles?",
                          "Listen, I do the finances here, I don't answer questions...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Umph, where has my memory gone...",
                      "You've guessed it, I'm sorry...", "I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//����������� ������, ���������
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				link.l1 = "Senior, I'm captain " + GetFullName(pchar) + ", and I'm here on an errand for Lucas Rodenburg. I have a package from him to you.";
				link.l1.go = "SantiagoTripBank";	
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripReturn")
			{
				link.l1 = "I've come for Senior Lucas Rodenburg's reply.";
				link.l1.go = "SantiagoTripBank_3";	
			}
			//����������� ������, ���������
		break;
		
		case "SantiagoTripBank":
			if (GetCharacterItem(pchar, "Chest") >= 5)
			{
			dialog.text = "You don't say� a package! Well, give it, senior.";
			link.l1 = "Also, Senior Rodenburg asked to tell you this...";
			link.l1.go = "SantiagoTripBank_1";
			RemoveItems(PChar, "NPC_Letter", 1);
			RemoveItems(PChar, "Chest", 5);
			}
			else
			{
			dialog.text = "As far as I know, there was something else I was supposed to receive besides the package, captain. So...where is it? Do you understand what I'm talking about?";
			link.l1 = "But of course! The chests are under secure watch on my ship. I'll have them delivered to you now.";
			link.l1.go = "exit";
			}
		break;
		
		case "SantiagoTripBank_1":
			dialog.text = "Hm-m... interesting. So he 'sends his regrets'. Well-well. Though, senior Rodenburg's regrets are quite persuasive, I'll give him that. Senior, it will take time to write a proper answer, could you come see me tomorrow and take a reply? Rest in a tavern, walk around the city. Santiago has a lot to offer.";
			link.l1 = "Fine, I shall come by tomorrow. See you, senior.";
			link.l1.go = "SantiagoTripBank_2";
		break;
		
		case "SantiagoTripBank_2":
			DialogExit();
			pchar.quest.SantiagoTripOver.over = "yes"; //����� ������
			bDisableFastReload = true;
			pchar.quest.Santiago_Trip.win_condition.l1 = "location";
			pchar.quest.Santiago_Trip.win_condition.l1.location = "Santiago_town";
			pchar.quest.Santiago_Trip.function = "SantiagoTrip_Attack";
			pchar.questTemp.HWIC.Holl = "SantiagoTripAttack";
			LAi_LocationDisableOfficersGen("Santiago_town", true);//�������� �� ������� // 291112
		break;
		
		case "SantiagoTripBank_3":
			dialog.text = "Yes, of course... but I believe we can do without written conventionalities. Just tell him these words � 'this man must die'. That would be fair and we won't have any problems as far as a loud written apology.";
			link.l1 = "Fine, I shall remember that, senior. Anything else?";
			link.l1.go = "SantiagoTripBank_4";
		break;
		
		case "SantiagoTripBank_4":
			dialog.text = "Yes, of course. What I've said is the will of the Giraldi family. And you can, of course, pass my best wishes onto Senior Lucas. I wish you a fair wind, captain " + GetFullName(pchar) + ".";
			link.l1 = "I understand. Farewell, senior "+npchar.name+".";
			link.l1.go = "SantiagoTripBank_5";
		break;
		
		case "SantiagoTripBank_5":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "SantiagoTripFinal";
			LAi_LocationDisableOfficersGen("Santiago_town", false);//�������� ������� // 291112
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

