// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("¬се сплетни города "+ GetCityName(npchar.city) +" к вашим услугам. „то бы вы хотели узнать?",
                          "ћы только что поднимали это тему. ¬ы, веро€тно, запам€товали...", "—егодн€ вы уже третий раз говорите о каком-то вопросе...",
                          "„то ты "+ GetSexPhrase("заладил","заладила") +" как попугай одно и то же...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("«наешь, " + NPChar.name + ", как-нибудь в следующий раз.", "“очно, "+ GetSexPhrase("забыл","забыла") +" что-то...",
                      "ƒа уж, действительно в третий раз...", "ƒа уж...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince")
			{
				link.l1 = "—кажи, в вашу колонию в последнее врем€ не заходил галеон под названием '—анта-ћаргарита'? Ѕыть может, в качестве каперского приза?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "ƒружище, в нашу колонию вообще редко кто-то с призами заходит, а галеона с таким названием точно не было.  олони€ у нас маленька€, тиха€, все в основном занимаютс€ заготовкой и продажей бычьих туш.  аперы у нас особо не ошиваютс€ - бордел€ здесь нет, да и испанцы под боком. “ак что разыскивай свой галеон где-то в другом месте.";
			link.l1 = "ясно. —пасибо за совет!";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "7");
			pchar.questTemp.Guardoftruth = "tortuga";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

