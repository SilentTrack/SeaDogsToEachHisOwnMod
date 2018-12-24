// аббат Бенуа
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
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) // Addon 2016-1 Jason пиратская линейка 1
			{
				dialog.text = "Рад видеть тебя, сын мой. Ты пришел, чтобы вернуть мне займ?";
				if (GetCharacterItem(pchar, "gold_dublon") >= 100 && sti(pchar.money) >= 50000)
				{
					link.l1 = "Да, отче. Я готов отдать вам долг.";
					link.l1.go = "FastStart_7";
				}
				else
				{
					link.l1 = "Я все помню, отче. Прошу прощения за задержку - дела идут не лучшим образом, но в ближайшее время я рассчитаюсь, обещаю.";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
			{
				dialog.text = "Ты что-то хотел, сын мой?";
				link.l1 = "Да, отче. Я хочу увидеть своего брата, Мишеля де Монпе. Он сказал, что...";
				link.l1.go = "escape";
				break;
			}
			dialog.text = "Ты что-то хотел, сын мой?";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) // еще не виделись
			{
				link.l1 = "Да, отче. Мне нужна ваша помощь. Меня зовут "+GetFullName(pchar)+". Мне порекомендовал обратиться к вам мой брат, Мишель де Монпе.";
				link.l1.go = "FastStart";
			}
			if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) // еще не виделись
			{
				link.l1 = "Да, отче. Мне нужна ваша помощь. Меня зовут "+GetFullName(pchar)+". Мне порекомендовал обратиться к вам мой брат, Мишель де Монпе.";
				link.l1.go = "meet";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Да, отче. Для того, чтобы помочь Мишелю, мне нужен корабль. Но я только недавно прибыл на Карибы, и почти без гроша в кармане. Мой брат сказал мне, что вы можете ссудить мне некоторую сумму денег...";
				link.l1.go = "FastStart_2";
			}
			if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Да, отче. Мне нужна ваша помощь.";
				if (CheckAttribute(npchar, "quest.relation_info")) link.l1.go = "help";
				else link.l1.go = "help_start";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && GetCharacterItem(pchar, "gold_dublon") >= 100 && sti(pchar.money) >= 50000)
			{
				link.l2 = "Да, отче. Я готов отдать вам долг.";
				link.l2.go = "FastStart_7";
			}
			link.l9 = "Да нет, ничего, отче.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Benua_meeting":
			dialog.text = "Что привело тебя ко мне, сын мой?";
			link.l1 = "Здравствуйте, отче. Мне посоветовали обратиться к вам. Мое имя - Шарль де Мор. Я разыскиваю Мишеля де Монпе. Как мне известно, он должен быть где-то здесь, на Мартинике. Я... его брат.";
			link.l1.go = "Benua_meeting_1";			
		break;
		
		case "Benua_meeting_1":
			dialog.text = "Брат Мишеля де Монпе? Де Мор? Очень странно...";
			link.l1 = "Я понимаю ваши сомнения, отче. У нас просто разные фамилии. Мой отец - Анри де Монпе.";
			link.l1.go = "Benua_meeting_2";			
		break;
		
		case "Benua_meeting_2":
			dialog.text = "А-а, это все проясняет. Я лично знал Анри де Монпе. Повернись к свету, юноша... Точно! Ты действительно похож на него... Такой же взгляд, такой же благородный профиль! Я рад видеть сына Анри де Монпе в нашей обители\nЧто же до вопроса твоего, то я сообщу тебе, что Мишель - один из высокопоставленных членов Ордена мальтийских рыцарей, однако... с ним случилась беда. Приходи завтра утром, сын мой, я познакомлю тебя с одним человеком - думаю, он сможет проводить тебя к брату.";
			link.l1 = "Спасибо, отче! Я буду завтра утром.";
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
			dialog.text = "Сын мой, приходи завтра утром. Мне пока нечего сказать тебе более.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Benua_meeting_repeat";
		break;
		
		case "Benua_maltie":
			dialog.text = "Здравствуй, сын мой. Как я и обещал - нужный человек уже здесь и ждет тебя. Он готов провести тебя к твоему несчастному брату, да смилуется Господь над его судьбой...";
			link.l1 = "Где же этот человек, отче?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break;
		
		case "escape":
			dialog.text = "Да, Шарль, я в курсе. Но вынужден тебя огорчить. Мишеля здесь нет.";
			link.l1 = "Как нет?! Он же сказал, что будет ждать меня в церкви у вас! Отче, что случилось? Где мой брат?!";
			link.l1.go = "escape_1";
		break;
		
		case "escape_1":
			dialog.text = "Сын мой, твой брат был здесь и покинул мою скромную обитель глубокой ночью. Куда он отправился - мне неведомо. Но он оставил для тебя письмо.";
			link.l1 = "Невероятно... и это после того, что я сделал для него! Дайте же мне это письмо!";
			link.l1.go = "escape_2";
		break;
		
		case "escape_2":
			dialog.text = "Не горячись, Шарль. Вот это письмо. Прочти его, а потом... потом я хочу поговорить с тобой. Но сначала прочитай послание своего брата.";
			link.l1 = "Я сгораю от нетерпения!";
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
				dialog.text = "Я вижу, ты прочел письмо. Теперь я хочу сказать тебе кое-что, Шарль...";
				link.l1 = "Но... как же так? Что за ахинею он несет? Я знаю, что у моего брата есть странности, но на сумасшедшего он не похож!";
				link.l1.go = "escape_5";
			}
			else
			{
				dialog.text = "Сын мой, прочти письмо. Потом поговорим.";
				link.l1 = "Да, отче...";
				link.l1.go = "exit";
				NextDiag.TempNode = "escape_4";
			}
		break;
		
		case "escape_5":
			dialog.text = "Меня тоже удивил поступок твоего брата, Шарль. Более - я до сих пор пребываю в растерянности. Верный слуга Ордена и Отечества - и поступает как дезертир...";
			link.l1 = "Вы не догадываетесь о причинах этого странного поступка?";
			link.l1.go = "escape_6";
		break;
		
		case "escape_6":
			dialog.text = "Увы, но - нет. Но полагаю, что для этого есть мотивы, очень глубокие мотивы. Ибо чтобы отречься от всего своего прошлого, нужно иметь какую-то очень значительную причину. Я даже не могу представить, какую. Но я чувствую, что здесь замешано что-то крайне нехорошее... даже ужасное.";
			link.l1 = "Что именно, отче?";
			link.l1.go = "escape_7";
		break;
		
		case "escape_7":
			dialog.text = "Сын мой, священник видит не глазами, а сердцем. Я не могу объяснить тебе словами, но... твой брат задумал что-то скверное. Я никогда не думал, что мои уста смогут произнести такое, однако...";
			link.l1 = "Ну, в том, что мой брат что-то задумал - я не сомневаюсь. Я даже догадываюсь, что именно. Это 'что-то' лежит где-то, имеет желтый цвет и приятно позвякивает.";
			link.l1.go = "escape_8";
		break;
		
		case "escape_8":
			dialog.text = "Я не думаю, что жажда золота движет твоим братом. Сдается мне, что ему нужно нечто большее.";
			link.l1 = "Я многому научился от Мишеля и постиг его философию, так что могу допускать, что для него важно, а что нет. Но я учту ваши слова, святой отец.";
			link.l1.go = "escape_9";
		break;
		
		case "escape_9":
			dialog.text = "Благословляю тебя, сын мой. А теперь ступай. Да хранит тебя Господь!";
			link.l1 = "Спасибо, отче. До свидания!";
			link.l1.go = "escape_10";
		break;
		
		case "escape_10":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			pchar.questTemp.Sharlie = "escape";
			CloseQuestHeader("Sharlie");
			AddQuestRecord("Guardoftruth", "1");
			pchar.questTemp.Guardoftruth = "begin";
			// ставим пленного испанца
			sld = GetCharacter(NPC_GenerateCharacter("spa_baseprisoner", "q_spa_off_1", "man", "man", 30, SPAIN, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_13", "pistol1", "bullet", 150);
			sld.dialog.FileName = "Quest\Sharlie\Guardoftruth.c";
			sld.dialog.currentnode = "spa_prisoner";
			RemoveAllCharacterItems(sld, true);
			LAi_SetStayType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Fortfrance_dungeon", "quest", "quest1");
			LAi_CharacterDisableDialog(sld);//запрет диалога
		break;
		
		// уменьшение награды за голову
		case "meet":
			dialog.text = "Брат Мишеля де Монпе? Де Мор? Очень странно...";
			link.l1 = "Я понимаю ваши сомнения, отче. У нас просто разные фамилии. Мой отец - Анри де Монпе.";
			link.l1.go = "meet_1";			
		break;
		
		case "meet_1":
			dialog.text = "А-а, это все проясняет. Я лично знал Анри де Монпе. Повернись к свету, юноша... Точно! Ты действительно похож на него... Такой же взгляд, такой же благородный профиль! Я рад видеть сына Анри де Монпе в нашей обители\nЯ уже слышал, что Мишеля посещал некий человек, прибывший из Европы, но даже и представить себе не мог, что это - его брат. Надеюсь, что ты сможешь помочь Мишелю, у него сейчас трудные дни. Так что я могу сделать для тебя?";
			link.l1 = "Мишель сказал мне, что вы можете помочь в случае, если у меня возникнут проблемы с властями...";
			link.l1.go = "help_info";	
			npchar.quest.meet = true;
		break;
		
		case "help_info":
			dialog.text = "Это Мишель так сказал? Ясно... Что же, оказать определенную помощь в этом вопросе я смогу. У меня есть определенное влияние в обители Римской католической церкви здесь, на архипелаге, а также в голланских поселениях. Таким образом, я могу ходатайствовать за тебя перед властями Испании и Голландии. Безусловно, я не смогу просить о многом, и если твоя провинность будет велика - то сумею лишь снизить враждебное отношение к тебе\nДля полного примирения потребуется несколько ходатайств. Кроме того, ты должен будешь снабдить меня золотыми дублонами для уплаты пожертвований и дорожных издержек. Ну, и только с одной державой за раз, конечно. Если тебя такое устраивает - обращайся, будем разрешать твои беды.";
			link.l1 = "Спасибо! Приму к сведению.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "help_start":
			dialog.text = "Так что я могу сделать для тебя, сын мой? Говори, я слушаю.";
			link.l1 = "Мишель сказал мне, что вы можете помочь в случае, если у меня возникнут проблемы с властями...";
			link.l1.go = "help_info";
		break;
		
		case "help":
			dialog.text = "Чем я могу помочь, сын мой?";
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "У меня возникли неприятности с испанскими властями.";
				link.l1.go = "relation_spa";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "У меня возникли неприятности с голландскими властями.";
				link.l2.go = "relation_hol";
			}
			link.l9 = "Извините, я пока обойдусь своими силами.";
			link.l9.go = "exit";
		break;
		
		case "relation_spa": // patch-10
			pchar.GenQuest.BenuaNation = SPAIN;
			dialog.text = "Значит, благородные сеньоры жаждут увидеть тебя закованным в кандалы в казематах Гаваны...";
			link.l1 = "Именно так, отче...";
			link.l1.go = "relation";
		break;
		
		case "relation_hol":
			pchar.GenQuest.BenuaNation = HOLLAND;
			dialog.text = "Значит, предприимчивые негоцианты жаждут увидеть тебя закованным в кандалы в казематах Виллемстада...";
			link.l1 = "Именно так, отче...";
			link.l1.go = "relation";
		break;
		
		case "relation":
			rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
			if (rate <= 10)
			{
				dialog.text = "Да, эти слухи достигли и нашей церкви. Смогу я помочь твоей беде, это дело поправимое. Мне нужно двести пятьдесят золотых дублонов, чтобы уладить неприятности.";
				if (GetCharacterItem(pchar, "gold_dublon") >= 250)
				{
					link.l1 = "Отлично! Вот, держите золотые.";
					link.l1.go = "agree";
					iTotalTemp = 250;
				}
				link.l2 = "Тогда мне самое время отправиться за монетами.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate <= 20)
				{
					dialog.text = "Да, слухи о твоих 'подвигах' достигли и нашей церкви. Подмочил ты свою репутацию, сын мой, надо было быть осмотрительнее. Но помочь все же я сумею. Мне нужно пятьсот золотых дублонов, чтобы уладить неприятности.";
					if (GetCharacterItem(pchar, "gold_dublon") >= 500)
					{
						link.l1 = "Отлично! Вот, держите золотые.";
						link.l1.go = "agree";
						iTotalTemp = 500;
					}
					link.l2 = "Тогда мне самое время отправиться за монетами.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Да, сын мой, ты такой же отчаянный, как и твой брат... Это, вероятно, ваша родовая черта. Полностью ситуацию я исправить не смогу, но улучшить твое бедственное положение - думаю, сумею. А потом еще раз пожертвования сделаем, если пожелаешь. Мне нужно шестьсот золотых дублонов - и сразу начну решать твои проблемы.";
					if (GetCharacterItem(pchar, "gold_dublon") >= 600)
					{
						link.l1 = "Отлично! Вот, держите золотые.";
						link.l1.go = "agree";
						iTotalTemp = 600;
					}
					link.l2 = "Тогда мне самое время отправиться за монетами.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveItems(pchar, "gold_dublon", iTotalTemp);
			Log_Info("Вы отдали "+iTotalTemp+" дублонов");
			PlaySound("interface\important_item.wav");
			dialog.text = "Теперь ожидай не менее двух недель. Думаю, за это время я встречусь и переговорю с нужными людьми.";
			link.l1 = "Спасибо, отче! Буду ждать...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, 10+rand(5), false);
			pchar.GenQuest.BenuaNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
			npchar.quest.relation = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка 1
		case "FastStart":
			dialog.text = "Брат Мишеля де Монпе? Де Мор? Очень странно...";
			link.l1 = "Я понимаю ваши сомнения, отче. У нас просто разные фамилии. Мой отец - Анри де Монпе.";
			link.l1.go = "FastStart_1";			
		break;
		
		case "FastStart_1":
			dialog.text = "А-а, это все проясняет. Я лично знал Анри де Монпе. Повернись к свету, юноша... Точно! Ты действительно похож на него... Такой же взгляд, такой же благородный профиль! Я рад видеть сына Анри де Монпе в нашей обители. Надеюсь, что ты сможешь помочь Мишелю, у него сейчас трудные дни. Так что я могу сделать для тебя?";
			link.l1 = "Для того, чтобы помочь Мишелю, мне нужен корабль. Но я только недавно прибыл на Карибы, и почти без гроша в кармане. Мой брат сказал мне, что вы можете ссудить мне некоторую сумму денег...";
			link.l1.go = "FastStart_2";	
			npchar.quest.meet = true;
		break;
		
		case "FastStart_2":
			dialog.text = "Это Мишель так сказал?";
			link.l1 = "Отче, я понимаю ваши сомнения, но это действительно так. Чем быстрее я стану владельцем и капитаном судна, тем быстрее смогу выполнить задачу, поставленную де Пуанси и освободить брата из темницы.";
			link.l1.go = "FastStart_3";
		break;
		
		case "FastStart_3":
			dialog.text = "Я понял, сын мой. И слышу, что ты говоришь мне правду. Что же, ради Мишеля и ради твоего отца, я, конечно, помогу тебе. У меня есть личные сбережения, которые я завещал монастырю Сен-Пьера. Я готов передать их тебе на время, если это действительно поможет твоему брату. Пятьдесят тысяч песо и сто золотых дублонов - этого должно тебе хватить с лихвой.";
			link.l1 = "Спасибо, отче. Сколько времени у меня на возврат займа?";
			link.l1.go = "FastStart_4";
		break;
		
		case "FastStart_4":
			AddMoneyToCharacter(pchar, 50000);
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Я не буду тебя торопить. Полгода - срок, более, чем достаточный.";
			link.l1 = "Хорошо, святой отец. Еще раз благодарю вас!";
			link.l1.go = "FastStart_5";
		break;
		
		case "FastStart_5":
			dialog.text = "Ступай с моим благословением, сын мой.";
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
			dialog.text = "Прекрасно, сын мой. Надеюсь, эти деньги тебе пригодились.";
			link.l1 = "Еще как, отче! Спасибо.";
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