// Элен Мак Артур - сомнительная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Вы что-то хотели?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "After_boarding":
			dialog.text = "Благодарю за помощь, капитан!";
			link.l1 = "Хм... Ты еще красивей, чем я тебя представлял по рассказам!";
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = "Черт бы побрал эту красоту! Из-за нее я чуть было не сыграла в ящик. Живой бы он меня с корвета не отпустил, только с ядром на шее, потому как слишком много знаю про этого ублюдка. Вчера он сказал, что устал ждать и намерен добиться от меня расположения вопреки моей воле\nТак что ты вовремя успел, кэп! Давай знакомиться. Меня зовут Элен Мак Артур. Отец с детства называл Румбой за веселый нрав, так это прозвище ко мне и приклеилось.";
			link.l1 = "Ну а меня зовут "+GetFullName(pchar)+". Вот уже несколько дней разыскиваю тебя по всему архипелагу по просьбе миссис Глэдис.";
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = "Как она?";
			link.l1 = "Сильно переживает за тебя. Впрочем, скоро ты ее увидишь, мы идем в Блювельд. По дороге расскажешь про свои злоключения подробнее...";
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = "Сказать по чести, "+pchar.name+", мне бы сейчас больше всего хотелось бы поесть и лечь спать. Я зверски устала за все эти кошмарные дни, проведенные на корабле этого изверга...";
			link.l1 = "Нет проблем, Элен. Я прикажу подать тебе еду и приготовить койку. Будь моей гостьей!";
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = "Еще раз от всего сердца благодарю тебя, мой капитан, за чудесное спасение. Ты обязательно должен навестить нас с матушкой. Наш домик тут совсем рядом. Вот он, налево от пирса в самом конце. И учти, "+pchar.name+", если ты исчезнешь, не простившись, никогда тебе этого не прощу, так и знай!";
			link.l1 = "Зайду обязательно!";
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // открыть кабинет Свенсона
			pchar.questTemp.Saga = "svenson";//идем к Свенсону
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			// закрыть город до беседы с Глэдис
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = "А вот и ты, мой капитан! Как я рада, "+pchar.name+", что ты решил наконец меня проведать. Я о многом хотела бы поговорить с тобой.";
			link.l1 = "Отложим этот разговор на некоторое время. Я должен кое-что выяснить, прежде чем смогу ответить на твои вопросы. А пока убедительно прошу не показываться на людях без особой необходимости. Надеюсь, твое ожидание будет недолгим. Верь мне и жди.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
		break;
		
		case "Helena_hire":
			dialog.text = "А вот и ты, мой капитан! По глазам вижу, у тебя есть новости для меня!";
			link.l1 = "Свенсон сказал, что ты рвешься ко мне в офицеры. Я очень рад твоему желанию - Глэдис говорила, что ты очень тоскуешь без моря. Добро пожаловать в мою команду, офицер Элен Мак Артур!";
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = "Свенсон сказал, что ты хочешь стать офицером на моем корабле. Я очень рад твоему желанию - Глэдис говорила, что ты очень тоскуешь без моря. Добро пожаловать в мою команду, офицер Элен Шарп!";
			link.l2.go = "Helena_hire_2";
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			dialog.text = "Есть, мой капитан! Но учти, я девушка гордая, могу за себя постоять и никаких вольностей не потерплю.";
			link.l1 = "Не волнуйся, у нас на корабле с этим строго. Кроме того, хочу добавить еще кое-что...";
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = "И что же это?";
			link.l1 = "Мы с Яном Свенсоном выяснили, что у тебя есть все права на наследование острова Исла Тесоро. Да, да, именно так, хотя на первый взгляд кажется невероятным. У меня есть половинка карты, которая поможет доказать это. Хотя с этим делом все не так просто, мы с мистером Свенсоном поможем тебе стать полноправной наследницей острова.";
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = ""+pchar.name+", ты серьезно? Нет, ты смеешься над бедной девушкой! Откуда у меня могут быть права на целый остров?";
			link.l1 = "Я абсолютно серьезен, Элен. Более того - намерен помочь тебе устроить твою жизнь. А сейчас - отправляемся в путь!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = "Как ты сказал? Элен Шарп? А почему Шарп?";
			link.l1 = "Элен, ты - дочь Беатрисс Шарп, и единственная наследница по линии Шарпов. Эта половинка карты, которую бережно хранила Глэдис все эти годы, является подтверждением твоих прав на остров Исла-Тесоро и Шарптаун. Но с этим делом все не так просто, и мы с мистером Свенсоном поможем тебе стать полноправной наследницей твоего деда.";
			link.l1.go = "Helena_hire_3";
		break;
		
		case "Helena_hire_3":
			dialog.text = "Ах... Бедная моя мама! Надеюсь когда-нибудь найти ее могилку и позаботиться о ней. Но... постой! Невероятно!";
			link.l1 = "Что такое, Элен?";
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = "Сбылось пророчество цыганки... Я только сейчас это поняла.";
			link.l1 = "Какое еще пророчество? О чем ты это сейчас?";
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+pchar.name+", ты, наверное, сочтешь меня наивной, но я все равно скажу тебе. Несколько лет назад цыганка на улице сказала мне: 'твоя судьба в руках того, кто не возьмет денег вдовы, вернет золото мертвеца и назовет имя матери'\nТогда я подумала, что это полная чушь. Но появился ты, и не только спас меня от позорной смерти, но и умудрился выполнить все три условия пророчества, о котором не мог ничего знать заранее!";
			link.l1 = "Судьба, говоришь... Что жe, вполне может быть и так. Я постараюсь не разочаровать тебя, а могилку твоей матери мы поищем вместе. А пока... Офицер Элен Шарп! Собирайся и не опаздывай к отплытию!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = "Есть, капитан!";
			link.l1 = "...";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2+rand(2), false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		//-->  консультации по морским сражениям в искушении барбазона
		case "sea_bomb":
			dialog.text = ""+pchar.name+"! У меня возникла одна идея...";
			link.l1 = ""+npchar.name+"? Тут вообще-то опасно, и я велел оставаться на корабле...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+", на этом корыте столько пороха, что взорвись он - и взлетит на воздух весь остров, так что разницы нет - на этом судне мы, или на нашем. Но ты выслушай меня!";
			link.l1 = "Ну? Что ты хотела сказать?";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "Корвет и фрегат. Они считают нас за своего... Валета. Мы можем этим воспользоваться. Сейчас возьмем пару самых больших бочек с порохом отсюда, приладим фитиль и поплывем к тем кораблям\nОни подпустят нас вплотную и мы незаметно скинем бочку рядом с одним из них, зажжем шнур и быстро слиняем. Главное - успеть подальше отойти. А потом понаблюдаем, как вражеское корыто взлетит к небесам... Что скажешь?";
			link.l1 = "Ну ты выдумщица! Хотя, твой план может сработать... Но только если нас не распознают.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Рискнем, "+pchar.name+"? Ведь с двумя кораблями нам будет трудно управиться, а так есть шанс...";
			link.l1 = "Хорошо. Так и сделаем! Ребята! Заберите три бочки с порохом на борт! И уходим! Ну у тебя и фантазия, "+npchar.name+"... Я бы не додумался.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = "Да, конечно. О чем пойдет речь?";
			link.l1 = "В бухте Сабу-Матила стоит корабль Джекмана, тяжелый фрегат 'Центурион'. Это судно принадлежало раньше Хоукам, кроме того, в каюте Джекмана должны быть важные документы и вещи... в общем, его нужно брать на абордаж.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Понятно. И ты сейчас думаешь, как ухитриться сделать это на нашем полакре? У них команды больше, чем у нас, и пушек тоже.";
			link.l1 = "Именно так. У Джекмана как минимум вдвое больше людей, и все отлично обучены - отборные наемники. Атаковать нахрапом, без артподготовки - полное безумие. Затяжная морская баталия тоже может обернуться не в нашу пользу. Вот я и ломаю голову - что бы такое придумать.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = "Ты не поверишь, "+pchar.name+", но я уже об этом думала и кое-что придумала! Они ведь нас пока еще не узнали - считают своим, как те два олуха, на Терксе... Можно повторить операцию.";
			link.l1 = "Элен! Я же только что сказал - фрегат нельзя топить, его нужно абордировать!";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Я все помню, "+pchar.name+". Топить не будем. Послушай: берем несколько пустых бочонков из-под рома, засыпаем туда порох, мелкую картечь и прилаживаем очень короткий фитиль. Затем подходим к борту фрегата и кидаем бочонки с нашим огненным ромом им на палубу.";
			link.l1 = "Ха! Ты думаешь, это получится?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "А почему нет? Борта у них выше, но два человека вполне забросят бочонок наверх. Крикнем - 'лови ром в подарок от Валета'! Пока они будут соображать, что да как - бочонки взорвутся.";
			link.l1 = "Картечь разлетится в стороны и буквально сметет всех, кто будет поблизости... Черт возьми, звучит заманчиво. Там целые толпы наемников слоняются по палубе от безделья! Они как раз и есть самые опасные.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Кинем не один бочонок, а штук пять в разные места. "+pchar.name+", у нас огромное преимущество - внезапность. Они ничего не подозревают! А потом сразу отходим от них подальше, чтобы не успели забросить абордажные крючья.";
			link.l1 = "Ну что же, попробуем. Главное - чтобы они не увидели раньше времени, что 'Марлин' уже не под командованием братца Джекмана... Черт возьми, это будет нелегко - к ним подобраться. Джекман не такой простак, как Упырь.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Рискнем, "+pchar.name+"! Если не получится - хуже не будет.";
			link.l1 = "Хуже не будет, это точно... Готовим фугасы, и к бою!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//<--  консультации по морским сражениям
		
	// --> разговор по итогам Саги
		case "result":
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // не друзья
			{
				dialog.text = "Ну что, мой капитан... Настало время нам с тобой проститься. Моя служба закончилась, и мне пора привыкать к роли хозяйки Исла-Тесоро. Надеюсь, я смогу стать достойной преемницей своего дяди. Благодарю тебя за помощь.";
				link.l1 = "Жаль, конечно, расставаться, но что же поделать. У тебя теперь есть дела поважнее, чем служба на моем судне.";
				link.l1.go = "result_1";
			}
			else
			{
				dialog.text = "Как странно, "+pchar.name+"! Я только что стала владелицей целого острова, но совсем не чувствую себя хозяйкой Исла Тесоро... Полагаю, новый глава Берегового братства управится с делами колонии куда лучше меня. Мне же будет достаточно просто ренты.";
				link.l1 = "Хм. Ты уверена, Элен? Подумай, у тебя же в собственности целый остров!";
				link.l1.go = "result_9";
			}
		break;
		
		case "result_1":
			dialog.text = "Ты прав... Мне тут удалось собрать немного золота - то, что я заработала на твоем корабле. Возьми его и не вздумай отказываться - я не хочу чувствовать себя твоим должником.";
			link.l1 = "Гм. Вообще-то...";
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = "Я понимаю, что ты хочешь сказать. Безусловно, твоя помощь была намного значительней этого сундука с монетами. Но это почти все, что у меня есть, а отблагодарить тебя я просто обязана. Бери, а если не возьмешь сам - я оставлю его у тебя в каюте.";
			link.l1 = "Ты что, сходишь на берег прямо сейчас? Может, тебя отвезти на Исла Тесоро?";
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			Log_Info("Вы получили сундук с дублонами");
			PlaySound("interface\important_item.wav");
			dialog.text = "Не стоит, "+pchar.name+". Я сама доберусь до своего острова. Некоторая сумма денег у меня есть, на первое время хватит... А хозяйке Исла Тесоро, я уверена, не придется беспокоиться о доходах.";
			link.l1 = "Ну что же - как скажешь. Желаю тебе удачи в твоей новой жизни.";
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = "Спасибо. Но это еще не все. Я вновь обрела отца, хотя и столь необычным образом. Фактически, он заплатил своим добрым именем английского дворянина за мое наследство, и меня это очень угнетает. На него объявлена охота, и я бы очень не хотела, чтобы ты, "+pchar.name+", принял в ней участие.";
			link.l1 = "Опомнись, Элен! Он же бандит и пират!";
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = "Пират? А ты-то кто? В первую очередь он мой отец! И мне, дочери бандита и пирата, глубоко плевать, что о нем думает английское правосудие. И если ты попробуешь причинить вред моему отцу, то я забуду все то хорошее, что ты успел для меня сделать. Учти, я тебя предупредила.";
			link.l1 = "Вот как? Вообще-то, девочка, можно было и повежливее. Что-то я не заметил от тебя критики по поводу моего пиратского поведения, когда я вытаскивал тебя из лап Донована, самым разбойничьм образом захватив его корвет!";
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = "Извини. Я погорячилась. Но мне все-таки хотелось бы остаться с тобой друзьями, что станет невозможным, если ты начнешь строить козни против моего отца.";
			link.l1 = "Я услышал тебя. Но более никогда не смей угрожать мне, Элен... Белтроп. За время службы на моем корабле ты должна была понять, что я не боюсь ни черта, ни морского дьявола. И тебя тоже не испугаюсь, поверь мне. А теперь - прощай. И не смотря ни на что, я желаю тебе удачи.";
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = "Спасибо. Возможно, еще когда-нибудь встретимся, "+pchar.name+"...";
			link.l1 = "А почему нет? На Исла Тесоро мне предстоит побывать еще не раз. Там и увидимся... Пока, Элен!";
			link.l1.go = "result_8";
		break;
		
		case "result_8": // Элен уходит, но ее не затираем
			DialogExit();
			RemovePassenger(pchar, npchar);
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
		break;
		
		case "result_9": // вот тут - ключевой момент, если игрок нашел Мэри - выбирай, какая девушка милее
			dialog.text = "Я уже подумала. "+pchar.name+", если ты позволишь, я бы и дальше хотела остаться у тебя на корабле. Рядом с тобой...";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "(выбрать Мэри) Элен! Ты, похоже, не понимаешь. Ты обеспечена до конца своих дней, и можешь не беспокоиться о будущем. У меня же впереди - война, закулисные интриги и полная неизвестность. Тебе нужно устраивать свою жизнь, а не связывать ее с авантюристом.";
				link.l1.go = "result_10";
				link.l2 = "(выбрать Элен) Я мог только мечтать об этом, Элен. Конечно, я не хочу терять тебя, но, возможно, тебе было бы лучше отправиться на Исла Тесоро. Кто знает, куда приведет меня моя судьба. У меня впереди - война, закулисные интриги и полная неизвестность.";
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = "Я мог только мечтать об этом, Элен. Конечно, я не хочу терять тебя, но, возможно, тебе было бы лучше отправиться на Исла Тесоро. Кто знает, куда приведет меня моя судьба. У меня впереди - война, закулисные интриги и полная неизвестность.";
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+pchar.name+"! Не лги мне. Ты просто не хочешь, чтобы... Скажи: это она? Та рыжая девчонка с Острова Погибших Кораблей? Да?";
			link.l1 = "Элен! Я в первую очередь думаю о тебе! Как ты этого не понимаешь?!";
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = "Я так и знала... И чем же она тебя так очаровала, а? Эх, "+pchar.name+"... Ну, раз ты так решил - то мне и впрямь больше ничего не остается, как отправиться на свой остров. Я не буду стоять между вами\nВ любом случае, огромное спасибо тебе за все, что ты для меня сделал. Ты - лучший из всех, кого я только знала. Ну а друзьями-то мы останемся?";
			link.l1 = "Конечно... Элен, мы с тобой еще не раз встретимся на Исла Тесоро. Тебя отвезти на твой остров?";
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = "Не надо. Я куплю себе корабль. За время службы у тебя я собрала сумму, достаточную для покупки и снаряжения шхуны. У меня снова будет моя 'Радуга'.";
			link.l1 = "Очень рад, Элен, что ты оказалась такой... хозяйственной. Но владелице Исла Тесоро не пристало ходить на шхуне - думаю, в скором времени ты обзаведешься собственным фрегатом.";
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = "Все возможно, "+pchar.name+". Ладно. Пойду на верфь, присматривать себе новый корабль, но сначала... поцелуй меня, на прощание. Пожалуйста...";
			link.l1 = "Элен...";
			link.l1.go = "result_14";
		break;
		
		case "result_14": // прощальный поцелуй
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 12.0);
			pchar.questTemp.LSC.Mary = "return"; // к Мэри
		break;
		
		case "result_15":
			dialog.text = "С первой же нашей встречи твоя судьба стала моей судьбой. Неужели ты до сих пор этого не понял, "+pchar.name+"? Я пойду с тобой хоть на край света!";
			link.l1 = "А твой отец? Лоуренс Белтроп? Ведь вышло так, что он оказался моим врагом...";
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = "Мой отец - Шон Мак Артур! Я любила его, и уже оплакала его смерть. Другого отца у меня нет и быть не может. А этот пират... я не хочу о нем даже говорить.";
			link.l1 = "Элен... Дорогая Элен!..";
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+", я давно хотела тебе сказать: ты - лучший, ты - удивительный! Ты столько сделал для меня, что мне жизни не хватит, чтобы отплатить за твое добро. Я хочу быть с тобой рядом. Всегда. И если ты этого захочешь, я стану твоей женой... Я люблю тебя.";
			link.l1 = "Мы будем вместе. Обещаю!"; // а куда же ты теперь денешься :)
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+pchar.name+", дорогой... Обними меня! Я так долго ждала этого момента!";
			link.l1 = "Элен, девочка моя...";
			link.l1.go = "result_19";
		break;
		
		case "result_19": // романтик-сцена
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! Это было просто... замечательно! Я никуда не хочу уходить... Давай останемся тут до утра. И пусть весь мир подождет!";
			link.l1 = "Пускай подождет, Элен!";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Следующим утром...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // показатель, что Элен - наша навсегда
		break;
		
	// -------------------------------------------- провалы саги ------------------------------------
		case "failcenturion":
			dialog.text = "Капитан! Джекман уничтожен... Это значит, что более ни с чьей стороны в адрес моей семьи угроз и опасностей нет?";
			link.l1 = "Да, Элен, это так. Но радости у меня мало - вместе с 'Центурионом' утонули документы и вещи, которые могли бы позволить нам найти могилу твоей мамы, и доказать твои права на Исла Тесоро. Эх... Теперь и Тортугу придется брать в одиночку...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = ""+pchar.name+", не огорчайся. Ну что же теперь поделать. А из-за меня точно не печалься - я прекрасно проживу и без этого острова. Спасибо тебе за все, что ты сделал для меня!";
			link.l1 = "Ты так говоришь, словно уходишь... да?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Да, мой капитан. Мне удалось отложить на твоей службе денег, достаточных для покупки и снаряжения шхуны. У меня снова будет моя 'Радуга'. Мы с тобой еще не раз увидимся в Блювельде, правда? Я возвращаюсь домой.";
			link.l1 = "Ну что же... удачи, Элен!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // к Мэри
			}
		break;
		
		case "late_l1":
			dialog.text = "Ну что же, мой капитан... Видимо, так и не удалось нам с тобой осуществить задуманное. Прощай. Я возвращаюсь домой. На заработанные у тебя деньги я куплю себе новую шхуну, так что еще, думаю, не раз увидимся в море!";
			link.l1 = "Удачи, Элен. Мне жаль, что все так неудачно вышло. Прощай.";
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = "Капитан! Джекман уничтожен... Это значит, что более ни с чьей стороны в адрес моей семьи угроз и опасностей нет?";
			link.l1 = "Да, Элен, это так. Но радости у меня мало - я потерял очень много времени, и Исла Тесоро теперь - английская колония. И ты теперь без положенного наследства, и мне придется брать Тортугу самому...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+", что там сказал адвокат?";
			link.l1 = "Эх! Я потерял очень много времени, и Исла Тесоро теперь - английская колония. И ты теперь без положенного наследства, и мне придется брать Тортугу самому... Увы, но мы проиграли.";
			link.l1.go = "failcenturion_1";
		break;
	// <-- провалы Саги
		
		// секс - Элен соглашается не всегда (голова болит, а что вы хотели? :)) и сама не требует секса
		case "cabin_sex":
			if (drand(4) == 0) // вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", я себя что-то совсем неважно чувствую. Не обижайся, пожалуйста. Давай не сегодня...",""+pchar.name+", дорогой, я так устала за последние несколько дней. Честно говоря, мне хочется просто поспать. Не обижайся. Давай в другой раз.");
				link.l1 = RandPhraseSimple("Ну хорошо...","Не обижаюсь. Как скажешь...");
				link.l1.go = "sex_exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", я с радостью поддерживаю твое предложение! Идем!",""+pchar.name+", ну конечно же не возражаю! Идем!");
				link.l1 = RandPhraseSimple("Ты моя умничка...","Ты - просто прелесть, Элен...");
				link.l1.go = "cabin_sex_go";
			}
		break;
		
		case "sex_exit":
			DialogExit();
			npchar.quest.daily_sex = true;
			SetFunctionTimerCondition("Helena_SexReady", 0, 0, 1, false);
		break;
		
		case "cabin_sex_go":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Helena_LoveSex", 1.0);
			NextDiag.CurrentNode = "sex_after";
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("Все было отлично, "+pchar.name+"!..","Ты как всегда на высоте, дорогой...");
			link.l1 = RandPhraseSimple("Я рад, что ты осталась довольна...","Мне с тобой очень хорошо, Элен...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.daily_sex = true;
			SetFunctionTimerCondition("Helena_SexReady", 0, 0, 1, false);
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", я всегда этому рада... Но сейчас немного не время - нужно отловить этого прохвоста Тибо, пока он не скрылся где-нибудь.";
				link.l1 = "Ты как всегда права, моя девочка...";
				link.l1.go = "exit";
				break;
			}
			if (drand(4) == 0) // вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", я себя что-то совсем неважно чувствую. Не обижайся, пожалуйста. Давай не сегодня...",""+pchar.name+", дорогой, я так устала за последние несколько дней. Честно говоря, мне хочется просто поспать. Не обижайся. Давай в другой раз.");
				link.l1 = RandPhraseSimple("Ну хорошо...","Не обижаюсь. Как скажешь...");
				link.l1.go = "sex_exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", я с радостью поддержу твое предложение! Идем!",""+pchar.name+", ну конечно же не возражаю! Идем!");
				link.l1 = RandPhraseSimple("Ты моя умничка...","Ты - просто прелесть, Элен...");
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			DoQuestCheckDelay("Helena_LoveSex", 1.5);
			NextDiag.CurrentNode = "sex_after";
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Да, "+pchar.name+"?","Да, мой капитан?","Слушаю тебя, "+pchar.name+"...");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Элен, я собираюсь отправиться в старый индейский город Тайясаль. Не буду скрывать: это крайне опасное путешествие, и более того - необычное: через телепортационный истукан. Ты... пойдешь со мной?";
				Link.l4.go = "tieyasal";
			}
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Элен, я хочу с тобой посоветоваться.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Элен, у меня для тебя есть распоряжение...";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex"))
			{
				Link.l2 = RandPhraseSimple("Элен, может, останемся в каюте вдвоем... на ближайшие пару часов? Ты не против?","Дорогая, может, проведем следующие несколько часов тет-а-тет? Ты не против?");
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && !CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				Link.l2 = RandPhraseSimple("Элен, может, снимен комнату и останемся там вдвоем... на ближайшие пару часов? Ты не против?","Дорогая, может, проведем следующие несколько часов тет-а-тет? Снимем комнату... Ты не против?");
				Link.l2.go = "room_sex";
			}
			link.l9 = "Пока ничего, Элен.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
		break;
		
		case "stay_follow":
            dialog.Text = "Какие будут приказания?";
            Link.l1 = "Стой здесь!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Следуй за мной и не отставай!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.bulletNum") && sti(NPChar.chr_ai.bulletNum) > 1)
				{
					Link.l3 = "Нужно изменить тип боеприпаса для твоего огнестрельного оружия.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Выбор типа боеприпаса:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, sBullet);
			LAi_GunSetUnload(NPChar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Будет сделано, капитан!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Будет сделано, капитан!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "Вот ты где спрятался! Насилу тебя нашла... Ну ты дал жару, мой капитан! Такого забега по крышам и прыжка с головокружительной высоты мне еще не доводилось видеть! У меня чуть сердце не выпрыгнуло из груди! Ты однажды доведешь меня своими выходками до удара, дорогой... О, так ты тут не один? Кто эта девушка?";
			link.l1 = "Это Кэтрин Фокс, дочь полковника Фокса, командира 'морских лис'. Мы отвезем ее на Антигуа.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Как интересно! Добро пожаловать на борт, мисс Фокс... А теперь быстрее грузимся в шлюпку - надо убираться отсюда.";
			link.l1 = "Ты умничка, Элен! И что бы я без тебя делал?.. Кэтрин, следуй за мной!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Ну наконец-то ты очнулся, мой дорогой... Как ты себя чувствуешь? Ты очень напугал меня.";
			link.l1 = "Элен... Милая, что произошло? Аргх, голова раскалывается...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Когда мы зашли в капитанскую каюту, ты лежал на полу без движения. У меня чуть сердце не остановилось! Ребята подхватили тебя и потащили на наш корабль, и вовремя, потому что эти ужасные скелеты, что валялись на палубе, начали подниматься и снова взялись за сабли\nЭто просто кошмар! Их нельзя одолеть! Мы быстро обрубили лини и отчалили от их корабля, но далеко уйти не успели: негодяи всадили в нас залп бортовой батареи, и наше судно в один миг превратилось в щепки. А затем они подняли паруса и в мгновение ока скрылись за горизонтом\nКорабль наш затонул, а все, кто выжил, добрались на лодке до берега. Я смогла прихватить твой капитанский рундук из каюты с твоими вещами. Там ведь много чего важного, я знаю.";
			link.l1 = "Ты умничка, Элен... Что бы я без тебя делал?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Я вытащила тебя в лодку, а потом и на берег. А ты был словно мертвый, только сердце едва билось. У меня до сих пор руки дрожат...";
			link.l1 = "Спасибо, моя милая. Я в долгу перед тобой. Сколько я здесь валялся без сознания?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Сутки. Я промыла и перевязала тебе раны, влила в рот лекарства и ром. Ты просто обязан теперь выздороветь!";
			link.l1 = "Обещаю, что не умру, моя дорогая. Хотя чувствую себя на редкость паршиво...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Не сомневаюсь... Это был 'Летучий Голландец', да? Почему они на нас напали? И почему сразу не сделали ни одного выстрела, а после абордажа потопили одним залпом?";
			link.l1 = "Их капитану нужен был амулет, по поводу которого я ходил к Туттуатхапаку, индейскому шаману. Поэтому они и не потопили нас сразу. А как только главный мертвец забрал амулет, они и расправились с нами... Жуть какая! Корабль с командой живых мертвецов! Поверить невозможно...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Вот мы и повстречались с 'Летучим Голландцем'. В первой же колонии я пойду в церковь,  поставлю свечу из чистого воска за наше спасение, и буду молиться...";
			link.l1 = "Знаешь, Элен, я, пожалуй, тоже. Но сейчас мы пойдем назад в деревню карибов. Я должен всё рассказать Туттуатхапаку. Этот проклятый корабль напал на нас из-за амулета! Надеюсь, краснокожий дьявол сможет объяснить мне, зачем он понадобился мертвецам.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Хорошо. Но тебе нужно беречь себя - твои раны до сих пор сочатся кровью.";
			link.l1 = "Но ты же поможешь мне исцелиться, моя девочка? И, Элен: я люблю тебя...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = "Я тебя тоже, дорогой...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", я как-то сказала тебе, что наши судьбы теперь едины. Твоя судьба - моя судьба. Когда мы отправляемся?";
			link.l1 = "Значит, ты согласна, моя умничка... Я очень рад. А когда выдвигаться - я скажу немного позже. Пока нам нужно подготовиться.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Я готова в любой момент, мой капитан! С тобой - хоть на край света!";
			link.l1 = "Спасибо, любимая...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// на Исла Тесоро
		case "islatesoro":
			dialog.text = "О, "+pchar.name+"! Рада тебя видеть! Какими судьбами на Исла Тесоро?";
			link.l1 = "Да все как обычно - по делам. И, конечно, не забыл тебя проведать, Элен...";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}