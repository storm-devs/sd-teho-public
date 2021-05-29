// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Явный баг. Сообщите Jason'у, как и при каких обстоятельствах его получили.";
			link.l1 = "Обязательно сообщу!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "girl":
			PlaySound("VOICE\Russian\Girls_1.wav");
			dialog.text = "Ой, здравствуйте, месье! Добро пожаловать на Тортугу! Нечасто нас посещают такие достойные капитаны, как вы...";
			link.l1 = "Приветсвую, мадемуазель. Спасибо за тёплый приём. Но как так? Мне казалось, что настолько значимую колонию французской короны должны регулярно удостаивать визитом люди много достойнее меня.";
			link.l1.go = "girl_1";
		break;
		
		case "girl_1":
			dialog.text = "Ах, месье... Вы недавно в наших краях, ведь так? Да что там говорить, такой благородный человек, как вы сам всё увидит. Вы даже не представляете, как сложно заполучить достойных мужчин на бал в губернаторском дворце. Может вы могли бы...";
			link.l1 = "Чем могу помочь такой прекрасной женщине?";
			link.l1.go = "girl_2";
		break;
		
		case "girl_2":
			dialog.text = "Хи-хи. Может вы заглянете к нам часам к шести вечера сегодня? В комнате для слуг жена губернатора регулярно устраивает неформальные вечера. Очень редко удаётся заполучить на такой вечер интересного собеседника. Вы придёте? Пожалуйста, приходите, мы будем вам так рады.";
			link.l1 = "Почту за честь, мадемуазель. Я обязательно загляну к вам.";
			link.l1.go = "girl_3";
			link.l2 = "Прошу меня простить, мадемуазель, но срочные дела не позволяют мне воспользоваться вашим приглашением.";
			link.l2.go = "girl_exit";
		break;
		
		case "girl_exit":
			dialog.text = "Очень жаль. Придётся найти другого... собеседника. Прощайте.";
			link.l1 = "Всего доброго.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			FMQT_ClearChest();
		break;
		
		case "girl_3":
			dialog.text = "Мы будем так рады! Спасибо вам! Обещаю, будет не скучно. Хи-хи. До встречи в шесть вечера!";
			link.l1 = "До встречи...";
			link.l1.go = "girl_4";
		break;
		
		case "girl_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_serveroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "1");
		break;
		
		case "girl_5":
			PlaySound("VOICE\Russian\Girls_1.wav");
			dialog.text = "Привет, красавчик! Редко такие видные мужчины заходят в наш порт.";
			link.l1 = "И тебе привет, красотка. Как видишь, один до вас всё-таки добрался. Дел - море, но ваш прекрасный остров наверняка может предложить достаточно развлечений для морского волка вроде меня.";
			link.l1.go = "girl_6";
		break;
		
		case "girl_6":
			dialog.text = "Хи-хи. О, да. Тортуге всегда есть что предложить. И мне тоже. Один моряк, нет, даже капитан, рассказал мне однажды, что ему удалось избежать верной смерти в море, оседлав морских черепах. Какой мужчина! А ты бы смог?";
			link.l1 = "Что бы смог?";
			link.l1.go = "girl_7";
		break;
		
		case "girl_7":
			dialog.text = "Хи-хи. Оседлать морских черепах.";
			link.l1 = "Разумеется. Я же капитан. Я могу. Рассказать?";
			link.l1.go = "girl_8";
		break;
		
		case "girl_8":
			dialog.text = "Чуть позже. Я работаю служанкой во дворце нашего губернатора. Приходи к шести вечера в будуар на втором этаже. Расскажешь нам с подругой о своих приключениях, хорошо?";
			link.l1 = "Хе-хе. С превеликим удовольствием, крошка. И покажу и расскажу. Буду к шести вечера у вас.";
			link.l1.go = "girl_9";
			link.l2 = "В будуар? У губернатора во дворце? Я пас, красотка, если захочешь моей компании, найди меня в таверне.";
			link.l2.go = "girl_exit_2";
		break;
		
		case "girl_exit_2":
			dialog.text = "Пф-ф. Ну и ладно, найду нам мужчину поинтересней. Прощай, кобель.";
			link.l1 = "Ищи-ищи, коза...";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_9":
			dialog.text = "Будем ждать с нетерпением!";
			link.l1 = "...";
			link.l1.go = "girl_10";
		break;
		
		case "girl_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_bedroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "2");
		break;
		
		case "wife":
			PlaySound("VOICE\Russian\Dama03.wav");
			dialog.text = "А вот и вы! Капитан "+GetFullName(pchar)+"! Я так рада вас видеть, ах, давно у меня в гостях не было такого благородного и достойного мужчины, как вы!";
			link.l1 = "Быть здесь в вашей компании - большая честь и удовольствие для меня, мадам. А где все остальные гости? Я рано?";
			link.l1.go = "wife_1";
		break;
		
		case "wife_1":
			dialog.text = "Нет нужды в других гостях сегодня. Давайте пить вино и общаться. Ах, вы знаете, как скучно и одиноко мне здесь! Это же деревня с пиратами! Пиратами! Наконец-то в нашем доме честный и утонченный человек! Ах, если бы только мой муж вёл дела с людьми ваших талантов и вашего полета! Пираты везде! А вы слышали о новом фасоне, который сейчас в моде при дворе Его Величества? Что вы вообще об этом думаете?";
			link.l1 = "О чём конкретно, простите? О пиратах? Или о фасонах?";
			link.l1.go = "wife_2";
		break;
		
		case "wife_2":
			dialog.text = "Вы так меня понимаете! Даже не верится. Можете себе представить, но мой муж даёт мне на жизнь жалкие крохи, хотя сам имеет со своих пиратов миллионы! Пираты! Я вынуждена заказывать платья прямо здесь, в этой дыре, но разве может дама моего статуса носить эти лохмотья! Как я хочу увидеть вживую эти фасоны из самого Парижа! Как вы думаете, я была бы в них прекрасна?";
			link.l1 = "Вы и так прекрасны, мадам. Вам не нужны фасоны из Парижа, это и так очевидно для всех мужчин этого замечательного острова.";
			link.l1.go = "wife_3";
		break;
		
		case "wife_3":
			dialog.text = "Вы так добры ко мне... Капитан, вынуждена вам признаться, но у меня беда. Вы же поможете несчастной женщине, правда?";
			link.l1 = "Конечно, мадам. Всё, что угодно.";
			link.l1.go = "wife_4";
		break;
		
		case "wife_4":
			PlaySound("VOICE\Russian\Dama02.wav");
			dialog.text = "Будьте осторожны, месье капитан, а то я могу потерять голову. Хи-хи. Как бы вам сказать... Мой муж не выделяет мне ни сантима последнее время, этот мерзавец водит к себе распутных женщин и совсем забыл про меня\nЯ точно знаю, что он хранит крошечную часть своих богатств в сундуке в своём кабинете. Это и мои деньги. По праву жены и по праву женщины. Помогите мне получить то, что мне причитается и будете вознаграждены... Золотом и... кто знает.";
			link.l1 = "Это... интересное предложение. Хорошо, мадам, я вам помогу. Где этот сундук и как его открыть?";
			link.l1.go = "wife_5";
			link.l2 = "Хорошо, красавица, я добуду содержимое сундука. Мы получим деньги и очень приятно проведём время. Какой мужчина от такого откажется? Где этот сундкук и как его открыть?";
			link.l2.go = "wife_6";
			link.l3 = "Простите, мадам, но честь не позволит мне сделать этого. Я вам сочувствую, вы заслуживаете большего, но вам придётся найти себе другого исполнителя.";
			link.l3.go = "wife_exit";
		break;
		
		case "wife_exit":
			dialog.text = "Жаль. В таком случае, нам больше не о чем говорить, месье. Уходите и запомните: вы сильно пожалеете, если расскажете об этом моему мужу!";
			link.l1 = "Всего доброго.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.FMQT.Common");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "4");
		break;
		
		case "wife_5":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "... Я не ожидала от вас такого... Сундук... Это потом, сначала нужно вернуть дубликат ключа, который оказался в руках мерзкого пирата. Он сейчас сидит в местном притоне и напивается, как животное. Поторопитесь и верните мне дубликат. Я буду вас ждать.";
			link.l1 = "Тогда не буду терять времени!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_6":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Вы не пожалеете об этом, капитан. И вы совершенно правы, какой мужчина от такого откажется? Сначала нужно вернуть дубликат ключа, который оказался в руках мерзкого пирата. Он сейчас сидит в местном притоне и напивается, как животное. Поторопитесь и верните мне дубликат. Я буду вас ждать.";
			link.l1 = "Тогда не буду терять времени!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_PirateInTavern", 10.0);
			pchar.quest.FMQT_late2.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late2.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQT_late2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late2.function = "FMQT_TavernTime";
			AddQuestRecord("FMQ_Tortuga", "6");
		break;
		
		case "wife_8":
			PlaySound("VOICE\Russian\Dama03.wav");
			dialog.text = "Капитан "+GetFullName(pchar)+"! Какой мужчина и у меня в будуаре! Удивлены? Гостей больше не ожидается. Хи-хи.";
			link.l1 = "Удивлён, мадам. Но я совершенно не против. Развлечёмся? Или у вас ко мне есть деловое предложение?";
			link.l1.go = "wife_9";
		break;
		
		case "wife_9":
			dialog.text = "Какой напор! Люблю прямых мужчин. У меня есть к вам предложение, капитан. Если справитесь, то я найду способ вас отблагодарить.";
			link.l1 = "Продолжайте.";
			link.l1.go = "wife_10";
		break;
		
		case "wife_10":
			dialog.text = "Ах... У моего мужа есть сундук с деньгами и всякими побрякушками. Я ненавижу его и я заслуживаю лучшей доли.";
			link.l1 = "Вы и так прекрасны, мадам. Вам не нужны фасоны из Парижа, это и так очевидно для всех мужчин этого прекрасного острова.";
			link.l1.go = "wife_11";
		break;
		
		case "wife_11":
			dialog.text = "Вы так добры ко мне... Капитан, вынуждена вам признаться, но у меня беда. Вы же поможете несчастной женщине, правда?";
			link.l1 = "Конечно, мадам. Всё, что угодно.";
			link.l1.go = "wife_12";
		break;
		
		case "wife_12":
			PlaySound("VOICE\Russian\Dama02.wav");
			dialog.text = "Будьте осторожны, месье капитан, а то я могу потерять голову. Хи-хи. Как бы вам сказать... Мой муж не выделяет мне ни сантима последнее время, этот мерзавец водит к себе распутных женщин и совсем забыл про меня\nЯ точно знаю, что он хранит крошечную часть своих богатств в сундуке в своём кабинете. Это и мои деньги. По праву жены и по праву женщины. Помогите мне получить то, что мне причитается и будете вознаграждены... Золотом и... кто знает.";
			link.l1 = "Хорошо. Сделаю. Где этот сундук и как его открыть?";
			link.l1.go = "wife_13";
			link.l2 = "Ха! Ради такой женщины, я сделаю это. Ты не пожалеешь, красотка. Мы получим деньги и очень приятно проведём время. Где этот сундкук и как его открыть?";
			link.l2.go = "wife_14";
			link.l3 = "Нет, красотка. Обчистить губернатора? Я таким не занимаюсь, а если и занимаюсь, то не в таком ключе. Поищи себе другого исполнителя.";
			link.l3.go = "wife_exit_2";
		break;
		
		case "wife_13":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "Ох... Вы мне нравитесь всё больше и больше... Сначала нужно вернуть дубликат ключа, который оказался в руках мерзкого пирата. Он сейчас сидит в местном притоне и напивается, как животное. Поторопитесь и верните мне дубликат. Я буду ждать.";
			link.l1 = "Тогда не буду тянуть кота за хвост!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_14":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Держи себя в руках, милый. Хи-хи.  Сначала нужно вернуть дубликат ключа, который оказался в руках мерзкого пирата. Он сейчас сидит в местном притоне и напивается, как животное. Поторопись и верни мне дубликат. Справишься?";
			link.l1 = "Сомневаешься? Не дрейфь! Я уже на пути в таверну.";
			link.l1.go = "wife_7";
		break;
		
		case "wife_exit_2":
			dialog.text = "Нахал! Прочь с глаз моих! И даже не думай рассказать об этом моему мужу! Ты пожалеешь!";
			link.l1 = "Пока, детка.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_15":
			PlaySound("VOICE\Russian\Dama03.wav");
			pchar.quest.FMQT_late3.over = "yes";
			dialog.text = "Капитан! Вы достали дубликат?";
			link.l1 = "Да. Он у меня. Где сундук?";
			link.l1.go = "wife_16";
		break;
		
		case "wife_16":
			dialog.text = "О, боже! Неужели этот мерзавец получит по заслугам! Вы невероятный человек, капитан! У вас большое будущее впереди, вы ведь это знаете? Забудьте про сундук. Я сама всё сделаю. Приходите завтра и вас ждёт награда. Вы не пожалеете, мой капитан...";
			link.l1 = "Хорошо. Будь по вашему. С нетерпением буду ждать завтрашнего дня.";
			link.l1.go = "wife_17";
			link.l2 = "Нет, я не хочу ждать, я занятой человек. Скажите, что надо сделать и я это сделаю. Я не могу позволить такой достойной женщине запачкать свои прекрасные ручки.";
			link.l2.go = "wife_18";
		break;
		
		case "wife_17":
			RemoveItems(pchar, "kaleuche_key", 1);
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			dialog.text = "Приходите сюда к шести вечера, мой рыцарь...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_Deceive");
		break;
		
		case "wife_18":
			dialog.text = "Вы уверены? Это может быть небезопасно. Зачем вам такой риск, мой капитан? Передумайте, молю вас!";
			link.l1 = "Хорошо. Будь по вашему. С нетерпением буду ждать завтрашнего дня.";
			link.l1.go = "wife_17";
			link.l2 = "Я твёрдо решил. Что нужно делать?";
			link.l2.go = "wife_19";
		break;
		
		case "wife_19":
			dialog.text = "Храбрец!.. Идите в кабинет моего мужа. В нём к одному из сундуков подойдёт этот дубликат. В кабинете никого не будет. Там, в сундуке... бриллианты. Много... Забирайте всё и возвращайтесь ко мне. Я буду ждать. Вы не обманете бедную женщину, я это знаю...";
			link.l1 = "Я скоро вернусь.";
			link.l1.go = "wife_20";
		break;
		
		case "wife_20":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Tortuga", "11");
			sld = &Locations[FindLocation("Tortuga_townhallRoom")];
			sld.private2.key = "kaleuche_key"; // допуск к сундуку
			pchar.questTemp.FMQT = "chest";
		break;
		
		case "wife_21":
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("VOICE\Russian\Dama01.wav");
			dialog.text = "Ох, капитан! Я.. Вы... Всё получилось? О, а это кто?! А-а!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_MercenAttackRoom");
		break;
		
		case "wife_22":
			dialog.text = "О, боже! Капитан, вы меня спасли! Вы... ты мой мужчина! Это был головорез моего мужа, он хотел убить тебя! Я умоляла его не делать этого! Ты ранен? Ты принёс бриллианты?";
			link.l1 = "Ха. Даже так? А ваш муж на редкость деликатный человек... Ну и чёрт с ним. Камешки у меня.";
			link.l1.go = "wife_23";
		break;
		
		case "wife_21x":
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("VOICE\Russian\Dama01.wav");
			dialog.text = "Ох, капитан! Я.. Вы... Всё получилось?";
			link.l1 = "Было одно небольшое недоразумение, но оно устранено. Вы что-то побледнели, мадам. Всё хорошо? Бриллианты у меня, это поднимет вам настроение, ведь правда?";
			link.l1.go = "wife_23";
		break;
		
		case "wife_23":
			dialog.text = "Слава Богу! Я отмщена! Мой рыцарь! Сколько там было?";
			if (GetCharacterItem(pchar, "jewelry2") >= 100)
			{
				link.l1 = "Ваш рыцарь вернулся из похода с хорошей добычей. И он оставит своей даме половину на лучшие фасоны из Парижа, как и обещал.";
				if (CheckAttribute(pchar, "questTemp.FMQT.Honour")) link.l1.go = "wife_25";
				else link.l1.go = "wife_26";
			}
			else
			{
				link.l1 = "Там было две сотни блестящих камушков - алмазов, но ты не получишь ни одного. Ты подослала ко мне наёмного убийцу, дрянь! И ты думаешь, я стану с тобой теперь делиться? А раскроешь рот - твой муженёк сразу узнает, что ты затевала. Так что сиди тихо...";
				link.l1.go = "wife_24";
			}
		break;
		
		case "wife_24":
			dialog.text = "Подлец! Негодяй! Это тебе даром не пройдёт!";
			link.l1 = "Ну-ну...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoJewelry");
		break;
		
		case "wife_25":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("Вы отдали 100 алмазов");
			PlaySound("interface\important_item.wav");
			dialog.text = "Вы не такой как... все остальные. Вы добиваетесь того, что хотите. У вас огромное будущее, вам надо спешить, но... Побудете со мной ещё немного? Нам никто не помешает, обещаю.";
			link.l1 = "Для такой женщины у меня всегда есть время. Откроем вино?..";
			link.l1.go = "wife_sex";
		break;
		
		case "wife_sex":
			DialogExit();
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
			DoQuestCheckDelay("PlaySex_1", 1.0);
		break;
		
		case "wife_26":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("Вы отдали 100 алмазов");
			PlaySound("interface\important_item.wav");
			dialog.text = "Думаю, я обойдусь и без них. Здесь есть на что потратить деньги. На Тортуге столько красивых и достойных мужчин... Спасибо за всё, капитан. И ни слова обо всём этом, иначе мой муж вас похоронит в канаве, хотя он не самый плохой человек, вы же знаете? Прощайте.";
			link.l1 = "Даже так. Поучительно. Прощайте, мадам, советую вам тоже молчать, потому что я не самый хороший человек. Но вы же и так об этом знаете?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoSex");
		break;
		
		case "wife_27":
			PlaySound("VOICE\Russian\Girls_2.wav");
			dialog.text = "Кто вы такой и что вам нужно в моей спальне?";
			link.l1 = "Гм... Мы же договаривались с вами о встерече сегодня, в шесть...";
			link.l1.go = "wife_28";
		break;
		
		case "wife_28":
			dialog.text = "Вы о чём, месье? Я замужняя женщина, и посторонним мужчинам встреч не назначаю! Немедленно покиньте мой будуар, иначе я позову мужа и стражу!";
			link.l1 = "Ах вот как мы запели! Ну ничего, твой муженёк обо всём узнает!";
			link.l1.go = "wife_29";
		break;
		
		case "wife_29":
			dialog.text = "Если вы немедленно не уберётесь, наглец, вас отправят в самую сырую и тёмную камеру подземелья Ля Роша! А ваши угрозы меня не волнуют. Вон!!";
			link.l1 = "...";
			link.l1.go = "wife_30";
		break;
		
		case "wife_30":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "FMQT_FinalFail");
		break;
		
		case "pirate":
			PlaySound("VOICE\Russian\tavern\Pyanici-03.wav");
			pchar.quest.FMQT_late2.over = "yes";
			FreeSitLocator("Tortuga_tavern", "sit_base2");
			dialog.text = "Ты кто? А, плевать. Не верь бабам, приятель. Даже самые тупые из них могут тебя утянуть на дно своими мани-мани-ик-пуляциями. Садись, выпьем!";
			link.l1 = "С удовольствием!";
			link.l1.go = "pirate_1x";
		break;
		
		case "pirate_1x":
			DialogExit();
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "sit", "sit_base2");
			LAi_SetSitType(pchar);
			npchar.Dialog.currentnode = "pirate_1";
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 2.0);
		break;
		
		case "pirate_1":
			PlaySound("VOICE\Russian\tavern\Pyanici-05.wav");
			dialog.text = "Чего уставился? Наливай!!";
			link.l1 = "За твоё здоровье!.. Послушай, приятель, тянуть не буду. Мне нужен дубликат, ты сам знаешь какой. Отдай его мне и разойдёмся: ты продолжишь пить, а я продолжу помогать дамам в беде.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "Забавно, а ты выглядишь умнее, чем есть на самом деле. Работаешь на эту стерву? А ты знаешь, кто её муж? Я тоже думал, что знаю. Левассер недавно послал своего раба Кампачо избить какого-то уважаемого торгаша за то, что тот не оказал должного внимания его жене. И эта баба меня завлекла своими прелестями и его дублонами\nДубликат существует. Я был неплохим медвежатником на родине и сделал слепок ключа. Если бы не дочка коменданта Лиона... я бы никогда не стал пиратом. К чёрту!";
			link.l1 = "Всё это очень печально, но давай к делу. Где дубликат?";
			link.l1.go = "pirate_3";
		break;
		
		case "pirate_3":
			dialog.text = "Ты меня не слушаешь?! Я больше не в деле! Мне хватило ума понять, чем это всё закончится! Когда мой корабль будет готов к отплытию, я свалю с этого острова навсегда. Хочешь дубликат? Заплати. И не жадничай, шансы таковы, что деньги тебе больше могут не понадобиться.";
			link.l1 = "Знаешь, а ты прав. Не хочется мне быть игрушкой женщины. Спасибо за совет, удачи в море!";
			link.l1.go = "pirate_4";
			link.l2 = "Платить? Тебе? Ты трус и мелкий вор. Лучше бы остался сидеть в этой дыре Лионе. Глядишь, местный комендант тебя бы пожалел и позволил бы забавляться с его дочуркой. А я тебя не пожалею. Отдавай дубликат, иначе поранишься.";
			link.l2.go = "pirate_5";
			link.l3 = "Сколько?";
			link.l3.go = "pirate_6";
		break;
		
		case "pirate_4":
			dialog.text = "Всё-таки мозгами тебя Господь не обделил. Правильное решение, дружище. Удачи. Надеюсь, ты однажды найдёшь себе настоящую, любящую женщину.";
			link.l1 = "Бывай, приятель...";
			link.l1.go = "pirate_exit";
		break;
		
		case "pirate_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay3");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "9");
		break;
		
		case "pirate_5":
			dialog.text = "Чт-о? Сдохни!";
			link.l1 = "Аргх!!";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_duel":
			DialogExit();
			LAi_SetSitType(npchar);
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(npchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
			i = makeint(MOD_SKILL_ENEMY_RATE/4);
			pchar.questTemp.FMQT = "duel";
			PChar.questTemp.duel.enemy = NPChar.id;
			if (MOD_SKILL_ENEMY_RATE > 2) PChar.questTemp.duel.enemyQty = i;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
		break;
		
		case "pirate_6":
			dialog.text = "Деловой ты человек, отдам тебе должное... Может, у тебя и получится. Пятьдесят дублонов. На стол.";
			link.l1 = "Пятьдесят дублонов? Тебе? Обойдёшься. Дубликат. На стол.";
			link.l1.go = "pirate_7";
			if (GetCharacterItem(pchar, "gold_dublon") >= 50)
			{
				link.l2 = "Многовато... Ладно. Держи.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Многовато... Ладно. Сейчас я принесу. Сиди, никуда не уходи!";
				link.l2.go = "pirate_wait";
			}
		break;
		
		case "pirate_wait":
			DialogExit();
			LAi_SetSitType(npchar);
			npchar.Dialog.currentnode = "pirate_dublon";
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay3");
			LAi_SetPlayerType(pchar);
		break;
		
		case "pirate_dublon":
			NextDiag.TempNode = "pirate_dublon"; // mitrokosta правка явного бага
			dialog.text = "Принёс пятьдесят дублонов?";
			link.l1 = "Знаешь, я подумал, что ты обойдёшься. Дубликат. На стол.";
			link.l1.go = "pirate_7";
			if (GetCharacterItem(pchar, "gold_dublon") >= 50)
			{
				link.l2 = "Да. Держи.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Уже несу!";
				link.l2.go = "exit";
			}
		break;
		
		case "pirate_7":
			dialog.text = "Потанцуем?";
			link.l1 = "...";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_8":
			RemoveItems(pchar, "gold_dublon", 50);
			Log_Info("Вы отдали 50 дублонов");
			PlaySound("interface\important_item.wav");
			dialog.text = "Отлично. Если твои мозги не подведут, то выйдешь из этого живым и с прибылью. Держи дубликат и совет. Совет бесплатный. Жёнушка нашего Левассера тупа, как пробка, но считает себя хитрой. Не доверяй ей. Держи себя в руках и следи за карманами в случае чего. Противник из неё никакой, просто будь осторожен и не вмешивай её мужа\nИ ещё, у неё в будуаре есть сундук. Открыть - пара пустяков. Там хранятся её побрякушки. Ты меня услышал. Удачи в море, брат.";
			link.l1 = "Бывай, приятель...";
			link.l1.go = "pirate_9";
		break;
		
		case "pirate_9":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay3");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "key";
			pchar.questTemp.FMQT.Caution = "true";
			FMQT_KeyNextDay();
			pchar.quest.FMQT_late3.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.FMQT_late3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late3.function = "FMQT_KeyTime";
			AddQuestRecord("FMQ_Tortuga", "10");
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
		break;
		
		case "mercen":
			PlaySound("VOICE\Russian\EvilPirates10.wav");
			dialog.text = "Каналья! Не ожидал... Чёртовы бабы! Говорил мне наставник - не связываться с такими, как она. Но работа есть работа. Я тебя всё же достану!";
			link.l1 = "Так-так, приятель... Похоже, она и меня поиметь решила, не скажу, что я удивлён. Зачем нам драться? Нужна работа? Она есть. Парень ты опытный, мне в команду такие нужны. Стол, койка, жалованье и честная доля добычи. Что скажешь?";
			if (sti(pchar.rank) > 5 && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 25 && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 25) link.l1.go = "mercen_1";
			else link.l1.go = "mercen_4";
		break;
		
		case "mercen_1":
			dialog.text = "А ты себе это позволить можешь, а, кэп? Язык у тебя подвешен, ничего не скажешь. Ладно, я в деле. Как твоя посудина называется?";
			link.l1 = ""+pchar.ship.name+". Добро пожаловать на борт!";
			link.l1.go = "mercen_2";
		break;
		
		case "mercen_2":
			dialog.text = "Хе-хе. А дельце неплохо провернулось. Дай этой стерве пинка от меня, кэп.";
			link.l1 = "...";
			link.l1.go = "mercen_3";
		break;
		
		case "mercen_3":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_MercenHire", 10.0);
			AddQuestRecord("FMQ_Tortuga", "17");
		break;
		
		case "mercen_4":
			dialog.text = "Сладко поёшь. Но недостаточно сладко для того, чтобы получить к себе на службу профессионала. Учти это в будущем. Если доживёшь.";
			link.l1 = "Ну попробуй. Только побыстрее, у меня свидание с дамой.";
			link.l1.go = "mercen_5";
			link.l2 = "Второго шанса не будет. У меня ещё куча дел, так что давай не будем дальше пачкать пол. Тебе не настолько хорошо платят за эту работу, чтобы подыхать ради местной шлюхи. Или тебе ещё даже не заплатили?";
			link.l2.go = "mercen_6";
		break;
		
		case "mercen_5":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQT_MercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "mercen_6":
			dialog.text = "Тут ты прав. ПОКА мне ещё никто не платил, и надо это исправить. Делай, что хочешь...";
			link.l1 = "...";
			link.l1.go = "mercen_7";
		break;
		
		case "mercen_7":
			DialogExit();
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("FMQ_Tortuga", "18");
			pchar.questTemp.FMQT.Roomfight = "true";
			FMQT_WifeFinalTalk();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
