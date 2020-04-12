// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What kind of questions?", "What would you like?");
			link.l1 = RandPhraseSimple("I have changed my mind...", "I have got nothing to say now.");
		    link.l1.go = "exit";
			//Jason, ��� �� ��������
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin") && CheckAttribute(PChar, "questTemp.Terrapin.SJ_count"))
			{
				link.l1 = "I am looking for mister Johns. Do you know him?";
				link.l1.go = "terrapin";
			}
		break;
		
		case "terrapin":
			if (sti(pchar.questTemp.Terrapin.SJ_count) == 5 || rand(9) == 1) // 10% ��� ������
			{
				dialog.text = "There are a lot of Johnses here. The most renowned I know is the colonel Fox's batman, Benjamin Johns. He usually meets visitors in the regiment's headquarters.";
				link.l1 = "Has he got a sister Molly?";
				link.l1.go = "terrapin_yes";
			}
			else
			{
				dialog.text = LinkRandPhrase("Which Johns do you need? I know two dozens of them at least.","We have got too many Johnses here. Specify please.","There are a lot of Johnses here just as Johnsons or Jacksons. Can you tell me anything specific about him?");
				link.l1 = "He has got an adult sister Molly. They say that she has got a rare beauty...";
				link.l1.go = "terrapin_no";
			}
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_no":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Hm. Can't help you with that.","I don't know him.","Well, if that Molly Johns has got a beauty than our colonel Fox is a priest."), LinkRandPhrase("I know a few Mollies Johnses. One of them really has got a brother but she is not who are you looking for. Only a man who has been living with apes would call her beautiful.","I am sorry, but all Johnses I know don't have sisters.","I am sorry, I can't help you. Ask someone else."));
			link.l1 = "Sorry for troubling you...";
			link.l1.go = "exit";
			pchar.questTemp.Terrapin.SJ_count = sti(pchar.questTemp.Terrapin.SJ_count)+1;
		break;
		
		case "terrapin_yes":
			dialog.text = "Yes, but she'd better be a man. This strapper won't likely find yourself a groom because of her mug.";
			link.l1 = "Thanks for your help!";
			link.l1.go = "terrapin_yes_1";
		break;
		
		case "terrapin_yes_1":
			DialogExit();
			AddQuestRecord("Terrapin", "2");
			pchar.questTemp.Terrapin.Benjamin = true;
			DeleteAttribute(pchar, "questTemp.Terrapin.SJ_count");
		break;
		
		case "info":
        // �������� �� �������� ����� ���, �� �������
			dialog.text = "Do I work for the secret service of "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Well... farewell then.";
			link.l1.go = "exit";
			link.l2 = "Next question then ";
			link.l2.go = "new question";
		break;
		
		case "town":
        // �������� �� �������� ��� ������, �� �������
			dialog.text = "Do I work on an enquiry position? Don't know. Don't know a thing.";

            link.l1 = "Such a muddle-head! See you.";
			link.l1.go = "exit";
			link.l2 = "A next question then";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

