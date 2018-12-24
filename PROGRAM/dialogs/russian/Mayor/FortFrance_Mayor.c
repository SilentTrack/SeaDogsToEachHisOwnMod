// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Что вы хотели? Спрашивайте.", "Я слушаю вас, что за вопрос?"), "Второй раз за день вы пытаетесь задать вопрос...", "В третий раз за день вы опять пытаетесь задать вопрос...",
                          "Да когда же это кончится?! У меня дел полно по управлению делами города, а ты все вопросы пытаешься задать!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Не сейчас, не место и не время..."), "Да, верно... Но не сейчас, позже...",
                      "Задам, задам... Только позже...", "Извините, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l1 = "Месье, я нашел в джунглях труп бандита, убитого индейцами. На теле кроме прочего были вот эти серьги - явно привезенные из Европы. Может, они принадлежали кому-то из знатных граждан вашего города?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "Я прибыл по приказу генерал-губернатора Филиппа де Пуанси чтобы принять командование над снаряженным вами фрегатом.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "Я готов принять в эскадру фрегат.";
                link.l1.go = "patria_2";
			}
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Дайте поглядеть поближе... Невероятно! Это просто невероятно, Шарль! Это серьги моей жены. Я сам их ей подарил перед отъездом в колонии. Они исчезли несколько месяцев назад при загадочных обстоятельствах. Я так и знал, что они были украдены!\nШарль, я очень рад, что вы пришли прямо ко мне, а не стали сбывать эту дорогую мне вещь лавочникам. Я в долгу не останусь. Как я слышал, вы собираетесь приобрести корабль? Раз вы решили приобщиться к морскому делу, то вам несомненно потребуется карта нашего архипелага. Вот, возьмите ее. Уверен, она не раз вам пригодится!";
			link.l1 = "Спасибо, Ваша Светлость!";
			link.l1.go = "Sharlie_junglejew_1";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "jewelry25", 1);
			GiveItem2Character(pchar, "map_bad"); 
			AddQuestRecord("SharlieE", "2");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
		break;
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Корабль готов, но у вас нет места для него. Уменьшите вашу эскадру и возвращайтесь, и я сразу передам вам фрегат.";
				link.l1 = "Хорошо.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Да, конечно, корабль готов к выходу в море. Капитан осведомлен и будет выполнять все ваши распоряжения.";
				link.l1 = "Тогда мы отправляемся в путь. До свидания, Ваша Светлость.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Отлично. Принимайте. Капитан осведомлен и будет выполнять все ваши распоряжения.";
			link.l1 = "Тогда мы отправляемся в путь. До свидания, Ваша Светлость.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateMrt(); // присоединяем фрегат
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

