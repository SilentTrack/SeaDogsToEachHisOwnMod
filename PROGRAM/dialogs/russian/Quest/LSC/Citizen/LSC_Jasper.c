
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "I don't want to talk with you. You attack peaceful civilians with no reasons and provoke them. Get lost!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Good day, mister. Want something?";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+", and what is yours? I am new her...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "�h, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Want something?";
				link.l1 = LinkRandPhrase("Got anything interesting to say?", "Has something new happened on the island?", "Will you tell me the last gossips?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; 
				link.l5 = "Just wanted to know how are you doing. See you!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": 
			dialog.text = "Me? I a, Jasper, the ex state convict. That is why people look askance at me. Ah, hell with them, I got used to it...";
			link.l1 = "I don't care about who have you been. Who you are now is the thing that matters.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "It is too bad, that not everyone think like you, mister.";
			link.l1 = "Well, I am known for my liberal attitude...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Glad for you. Don't worry, despite of my past, I am not a threat to the purses and chests of the Island's inhabitants. I am glad that I can live in peace at last.";
			link.l1 = "Glad to meet you, Jasper. See you!"
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Got anything interesting to say?", "Has something new happened on the island?", "Will you tell me the last gossips?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; 
			NextDiag.TempNode = "First time";
		break;
		

		case "int_quests":
			dialog.text = "Yes, sure. I will answer you if I can. Ask.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How have you become the Island's inhabitant?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Do you like this place?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "You have mentioned that people look askance at you. Is that because your past?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "This Island is quite interesting, don't you think?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "I ran away from Cubian plantation. There were five of us and we decided that dying is more preferable than to continue breaking ours backs for beating. We had managed to trick the guards and to disappear in jungles, then we reached the shore and built a raft\nWe wanted to reach Tortuga but the fate decided otherwise. No one of us knew how to navigate, so we got lost. Then the water run off... I don't want to remember that. As a result, I was the one who reached the Island and survived.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "You know, I am fine with that. After all I've been trough on plantation this place feels like a heaven for me. I don't need much... A bit of food, water and a glass of rum every evening. Nobody bother me here and I am not going to leave this place. I will die here when my time will come.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Thing is that the Island is a playground for some mysterious thief. Locks are not a problem for him. Mostly he hangs around admiral's chambers. Though our chests are not left intact too. Nobody knows who is this thief, so they suspect people with� hm, criminal past\nThe thief is a bit strange though: first, he only takes bottles with spirits and some trinkets, he never takes valuable items. Funny isn't it?";
			link.l1 = "Got it...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Yes, I agree. I swam a lot around the inner ships of the Island. There are a very few exits from the water. San Augustin, the bridge place. Gloria, the fallen mast. If you swim close to Fenix platform and then around Ceres Smitie you will reach Mary Casper's cabin at the ship's bow\nThe rift in Tartarus will lead you to the prison. There is a hole in San Augustine's bow, you may get inside admiral's storage room, but it's inadvisable course of action. The lowest door of Tartarus is often closed, remember that\n And of course you can get inside Fernanda, it is the lone and torn apart flute. They say that no one lives there but I often notice lights inside the cabin and sometimes I can hear odd drunk songs and cries.";
			link.l1 = "Interesting... I need to explore this place more.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;

		

		
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("What are you doing there, ah? Thief!", "Just look at that! As soon as I was lost in contemplation, you decided to check my chest!", "Decided to check my chests? You won't get away with it!");
			link.l1 = "Damn it!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "What?! Decided to check my chests? You won't get away with it!";
			link.l1 = "Foolish girl!...";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Listen, you'd better take your weapon away. It makes me nervous.", "You know, running with blade is not tolerated here. Take it away.", "Listen, don't play a kid running with a rapier around. Take it away it doesn't suit you...");
			link.l1 = LinkRandPhrase("Fine.", "Whatever then.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, I am the citizen of the city and I'd ask you to hold down your blade.", "Listen, I am the citizen of the city and I'd ask you to hold down your blade.");
				link.l1 = LinkRandPhrase("Fine.", "Whatever then.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Be careful, pal, while running with a weapon. I can get nervous...", "I don't like when men walking in front of me with their weapon ready. It scares me...");
				link.l1 = RandPhraseSimple("Got it.", "I am taking it away.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
