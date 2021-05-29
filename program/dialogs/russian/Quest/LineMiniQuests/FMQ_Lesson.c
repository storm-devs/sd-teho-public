// Addon-2016 Jason, французские миниквесты (ФМК) Последний урок
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
		
		case "greguar":
			PlaySound("VOICE\Russian\QuestMan03.wav");
			pchar.quest.FMQL_delete_guide.over = "yes";
			if (CheckAttribute(pchar, "questTemp.HWIC") || pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "О, "+GetFullName(pchar)+"! Вас не узнать и вы делаете успехи! Наслышан, очень наслышан. Вы быстро учитесь, месье, приятно видеть, когда твои уроки не пропадают даром. Успехов вам и дальше, рад был повидаться!";
				link.l1 = "Месье Валинье, какая встреча! Мои скромные успехи - такая же ваша заслуга, как и моя. Мне тоже очень приятно видеть вас в Сен-Пьере. Удачи!";
				link.l1.go = "greguar_exit_1";
			}
			else
			{
				dialog.text = "О, "+GetFullName(pchar)+"! Я вас ждал! Вас не узнать и вы делаете успехи! Наслышан, очень наслышан. Вы быстро учитесь, месье, приятно видеть, когда твои уроки не пропадают даром.";
				link.l1 = "Месье Валинье, какая встреча! Мои скромные успехи - такая же ваша заслуга, как и моя. Вы меня ждали? Дайте догадаюсь - у вас ко мне деловое предложение?";
				link.l1.go = "greguar_1";
			}
		break;
		
		case "greguar_1":
			dialog.text = "Верно. Буду краток, поскольку время не терпит. Итак: голландская коронная эскадра, следовавшая из Бразилии на Кюрасао с грузом стратегических товаров для Вест-Индской торговой Компании, попала в засаду англичан между Тринидадом и материком. Один флейт Компании сумел выскользнуть из боя и причалить к берегу в бухте Бока де ла Сьерпе, и тем самым спас свой груз. Ненадолго. Их атаковало местное племя индейцев\nПо моей информации, голландцев всех вырезали, а груз был унесен в деревню. Индейцы захватили голландское оружие, но понесли серьезные потери. Это наш шанс! Англичане с голландцами всё еще бодаются друг с другом в том районе, и им не до потерянного флейта. Пока что... У вас есть корабль и люди. Мы можем проскочить, высадиться и добить индейцев. Груз крайне ценен и его приличное количество\nЯ высадил там небольшую экспедицию для разведки - все те же проблемы с деньгами, и на большее я не смог выделить ресурсов. У меня есть надежный покупатель, к вашим услугам моя шпага и отряд наемников на берегу. Добычу делим пополам. У нас есть неделя. Вы в деле?";
			link.l1 = "Простите меня, месье, но я не готов. Я только что из тяжелого похода и не смогу подготовиться за такой короткий срок. Даже в этом Богом забытом регионе человек не может иметь всё.";
			link.l1.go = "greguar_exit";
			link.l2 = "Похоже, это серьезное дело, сулящее недурственные барыши! Я с вами. Не будем медлить!";
			link.l2.go = "greguar_2";
		break;
		
		case "greguar_exit":
			dialog.text = "Жаль. Ну дело ваше. Удачи вам, месье, а я все-таки отправлюсь туда. Надо ведь попытаться, верно? Прощайте.";
			link.l1 = "Удачи, месье Валинье!";
			link.l1.go = "greguar_exit_1";
		break;
		
		case "greguar_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 20.0);
		break;
		
		case "greguar_2":
			dialog.text = "Правильное решение, мой друг! Вперед, деньги вам не помешают, верно? Кстати, как поживает ваш брат?";
			link.l1 = "Деньги никогда не помешают, это верно. Мишель? Мой брат здоров, но скучает. Завидую ему иногда... Отплываем!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_Begin");
		break;
		
		case "greguar_3":
			PlaySound("VOICE\Russian\QuestMan02.wav");
			dialog.text = "Это было просто! Салаги, уцелевшие после драки с голландцами. Пора продвигаться вглубь материка, мой отряд где-то там!";
			link.l1 = "Слишком просто... Не спешите радоваться, месье Валинье. Лучше посмотрите во-он туда...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_SecondCoastBattle");
		break;
		
		case "greguar_4":
			dialog.text = "Черт бы их побрал этих краснокожих! Они нас чуть не смяли! Ну теперь уж точно, у них в деревне остались только женщины и дети! Вперед!";
			link.l1 = "Я бы не был так уверен в этом... Выдвигаемся!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_GoToJungle");
		break;
		
		case "greguar_5":
			PlaySound("VOICE\Russian\MiddPirate04.wav");
			dialog.text = "То есть? Мы с голландцами должны были перебить их всех!";
			link.l1 = "";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_7":
			dialog.text = "Бежать? Вы с ума сошли! Мы же почти у цели! Вы испугались кучки раскрашенных дикарей?";
			link.l1 = "";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_9":
			dialog.text = "Последнее дело, капитан. Я намереваюсь вернуться в Европу. Я разочарован! В вас, в этих трусливых молодчиках и в этом проклятом месте!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			DialogExit();
			DoQuestReloadToLocation("shore18", "goto", "goto8", "FMQL_JungleExit");
		break;
		
		case "greguar_11":
			PlaySound("VOICE\Russian\MiddPirate04.wav");
			dialog.text = "Фух! Мы сделали это!";
			link.l1 = "Но какой ценой! Вы посмотрите - полегли почти все из нашего отряда. Надо уходить, Грегуар, нет никаких гарантий, что в логове карибов нас не ждут еще бойцы. Да и нет людей, чтобы забрать груз. ";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "Карамба!! Как это ни печально, но вы правы, "+pchar.name+": даже если дикарей больше нет, мы не утащим груз до высадки голландцев или англичан. А так хорошо все начиналось! Уходим! Будь проклят этот злосчастный берег!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_13":
			PlaySound("VOICE\Russian\QuestMan02.wav");
			dialog.text = "Фух! Мы сделали это! Отличная работа, "+pchar.name+"! Теперь вперед, в логовище дикарей, за товарами! Больше нас уже никто не остановит!";
			link.l1 = "Поторопимся! Англичане и голландцы скоро выяснят, кто из них сильнее, и тогда нам несдобровать. Вперед!";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			DialogExit();
			DoQuestCheckDelay("FMQL_RunToGrabbing", 1.0);
		break;
		
		case "greguar_15":
			PlaySound("VOICE\Russian\QuestMan01.wav");
			dialog.text = "Мы славно потрудились, "+pchar.name+". Теперь дело за малым - выгодно продать товар, да так, чтобы таможня ничего не заподозрила. У меня есть верный покупатель, он будет ждать нас сегодня на пляже Ламантен в полночь. Офицеров не берите, и раньше полуночи там не ошивайтесь: покупатель - человек нервный.";
			link.l1 = "Дело что надо... Груз надо продавать, и делать это безопасно, иначе за контрабанду мой долг Пуанси еще вырастет. Хорошо, буду сегодня в полночь в указанном месте.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.quest.FMQL_goods_timer.win_condition.l1 = "Timer";
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQL_goods_timer.function = "FMQL_MeetingOnLamanten";
			AddQuestRecord("FMQ_Lesson", "7");
			LAi_LocationDisableOfficersGen("Shore38", true); // may-16
			LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], true);
			locations[FindLocation("Shore38")].DisableEncounters = true;
		break;
		
		case "greguar_17":
			PlaySound("VOICE\Russian\Master_01.wav");
			dialog.text = "Все готово, товары сгружены, порученцы клиента прибыли. Идемте договариваться.";
			link.l1 = "...";
			link.l1.go = "greguar_18";
		break;
		
		case "greguar_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("FMQL_contra_"+i);
				if (i == 2) LAi_CharacterEnableDialog(sld);
			}
		break;
		
		case "greguar_19":
			dialog.text = "Сюрприз, ублюдки!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_LookOnGuards");
		break;
		
		case "greguar_20":
			PlaySound("VOICE\Russian\OliverTrast01.wav");
			dialog.text = "Ай да Джонни, ай молодец! Отлично! Вы что-то хотите сказать, "+pchar.name+"?";
			link.l1 = "Нет. Точнее, да! Какого черта?!";
			link.l1.go = "greguar_21";
		break;
		
		case "greguar_21":
			dialog.text = "Не передразнивайте покойника, месье. Где ваши манеры?.. Деньги получены, груз при мне и моих друзьях. Я не стал их посылать на тот пляж, это было бы расточительством. Особенно посылать туда Джонни. Этот тот краснокожий парень с кулевриной в руках. Джонни не очень любил своё племя, знаете ли.";
			link.l1 = "Так... И что теперь? Убьете и меня?";
			link.l1.go = "greguar_22";
		break;
		
		case "greguar_22":
			dialog.text = "Стоило бы. Но я сентиментален. Уходите и берите четверть денег. Груз и все остальное остается при мне. И не пытайтесь играть в героя, это не те джунгли на материке. Шансов у вас нет.";
			link.l1 = "И куда делись ваше благородство и манеры? Не ожидал от вас такого, Грегуар. Я ухожу, но это было очень поучительно.";
			link.l1.go = "greguar_23";
			link.l2 = "В героя играть не буду. Я просто вас всех убью. Тебя первым, потом обезьяну с гранатометом, а потом и этих девочек.";
			link.l2.go = "greguar_25";
		break;
		
		case "greguar_23":
			dialog.text = "На этом пляже нет ни благородных, ни бандитов, месье! Есть только пять человек, большая пушка и жертва. Такое здесь происходит постоянно, но вы сделали единственный правильный выбор. Мое почтение. А вы знаете, что на вашем месте могли бы быть два других человека? Почти таких же, как вы? Но вы здесь, а они нет, и мне кажется, что они погибнут из-за этого.";
			link.l1 = "Я не понимаю...";
			link.l1.go = "greguar_24";
		break;
		
		case "greguar_24":
			dialog.text = "Потом поймете. Они не получили свой последний урок. А вы - да. И не благодарите. Прощайте, месье. Добро пожаловать на Карибы!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_PeaceFinal");
		break;
		
		case "greguar_25":
			dialog.text = "Вы не самый способный ученик. Ну что же... каждому - свое.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_BattleOnBeach");
		break;
		
		case "mercen":
			PlaySound("VOICE\Russian\pirat_guard_4.wav");
			dialog.text = "Вы чертовски вовремя! Мы еле избежали орды карибов, они бежали в вашем направлении и, судя по вашему виду, вы с ними уже познакомились. Логово карибов в двух шагах, но наши проблемы только начинаются.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper":
			PlaySound("VOICE\Russian\pirat_guard_4.wav");
			dialog.text = ""+GetFullName(pchar)+"! И вы здесь! И почему я не удивлен! Вы чертовски вовремя, мой друг. Мы еле избежали орды карибов, они бежали в вашем направлении и, судя по вашему виду, вы с ними уже познакомились.";
			link.l1 = "Проспер! А вот я удивлен! Опять дырявите индейцев? Надеюсь, у Селины всё хорошо?";
			link.l1.go = "prosper_1";
		break;
		
		case "prosper_1":
			dialog.text = "Черт меня дернул ввязаться в эту историю - не знаю, увидит ли меня моя дочь снова. Селина? Сидит дома и всё вздыхает о вас! У хлыщей с Мартиники, похоже, теперь нет даже шансов... Вы знаете, я даже уже не жалею, что купил этот мушкет. Хорошая вещь, надежная. И лишний повод поучаствовать в самоубийственном предприятии, хотя, с вашим появлением, оно стало чуть менее самоубийственным. Логово карибов в двух шагах, но наши проблемы только начинаются.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper_2":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_3":
			dialog.text = "Почти всех. Наш разведчик словил пулю, но добрался до берлоги карибов. Сюда идет вождь со своей охраной! И у них голландские мушкеты. Их больше нас, и они в ярости. Вождь - лучший боец племени, а его люди - те еще дьяволы. Надо срочно решать, что делать: дать бой или бежать. Второе мне нравится больше, если быть честным.";
			link.l1 = "";
			link.l1.go = "prosper_4";
		break;
		
		case "prosper_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_5":
			dialog.text = "Вы не видели их, уважаемый! У этих 'дикарей' - мушкеты, и они на удивление хорошо ими пользуются! Их явно в свое время кто-то обучил! Не вам говорить мне о трусости!";
			link.l1 = "Так, давайте все успокоимся и решим, что делать. Время еще есть.";
			link.l1.go = "prosper_6";
		break;
		
		case "prosper_6":
			int n = 0;
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("FMQL_sailor_"+i) != -1) n++;
			}
			dialog.text = "Слушаю ваши предложения, "+pchar.name+".";
			if (n > 2 && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 30)
			{
				link.l1 = "Мы дадим бой, парни! Там, за холмом, нас ждут деньги и товары! Мы здесь ради них, и мы не уйдем. Какая-то кучка краснокожих дикарей, пусть даже с мушкетами, нас не остановит! Давайте похороним этих ублюдков и закончим работу! У нас достаточно людей, и у нас есть шанс застать их врасплох. Устроим засаду. Четверо бойцов встретят их огнем с флангов на подходе, а мы заляжем тут. Проредим их и добьем. Разом и все вместе!";
				link.l1.go = "prosper_8";
			}
			else
			{
				if (n > 0)
				{
					link.l1 = "Мы дадим бой, парни! Там, за холмом, нас ждут деньги и товары! Мы здесь ради них, и мы не уйдем. Какая-то кучка краснокожих дикарей, пусть даже с мушкетами, нас не остановит! Давайте похороним этих ублюдков и закончим работу!";
					link.l1.go = "prosper_7";
				}
				else
				{
					link.l1 = "Силы слишком неравны, а за спиной еще голландцы и англичане. Мы должны уходить - не вижу смысла сложить здесь головы. В следующий раз дело будет наше. Не последний поход же!";
					link.l1.go = "prosper_9";
				}
			}
		break;
		
		case "prosper_9":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_7":
			DialogExit();
			pchar.questTemp.FMQL = "battle";
			AddDialogExitQuestFunction("FMQL_PrepareAttack");
		break;
		
		case "prosper_8":
			DialogExit();
			pchar.questTemp.FMQL = "sneak";
			AddDialogExitQuestFunction("FMQL_PrepareSneakAttack");
		break;
		
		case "prosper_9x":
			PlaySound("VOICE\Russian\pirat_guard_2.wav");
			dialog.text = "Мы живы и мы дома! Клянусь, c меня хватит приключений... на пару месяцев, ха-ха! Пойду к своей Селине, заглядывайте к нам, "+pchar.name+". И смотрите - будьте осторожней.";
			link.l1 = "Не могу обещать, что загляну, Проспер. Но могу обещать быть осторожным. Удачи!";
			link.l1.go = "prosper_10";
		break;
		
		case "prosper_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
		break;
		
		case "prosper_11":
			pchar.quest.FMQL_prosper_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			PlaySound("VOICE\Russian\pirat_guard_4.wav");
			dialog.text = "Я же предупреждал вас, капитан: будьте осторожны! Я подозревал, что этот негодяй затевает недоброе.";
			link.l1 = "Проспер! Спасибо! Как ты узнал?";
			link.l1.go = "prosper_12";
		break;
		
		case "prosper_12":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.FMQL.PirateDead")) sTemp = "Жаль этого парня, хоть и пират.";
			dialog.text = "Джонни проболтался. Это тот краснокожий на песке. Он зашел в бордель и попытался снять девку. Ему отказали, ну он и начал орать, мол, скоро будет богат, только сначала сходит в джунгли и с дружками грохнет какого-то капитана. Я все сразу понял и бросился к вашему офицеру, который тоже успел прославиться на весь город. "+sTemp+" Я у вас в долгу, "+pchar.name+", так что не благодарите.";
			link.l1 = "И все же благодарю тебя, Проспер! Тут было слишком жарко... Хочешь пойти ко мне в команду? Мне нужен такой офицер, как ты. Верных людей сложно найти, а верных стрелков еще сложнее.";
			link.l1.go = "prosper_13";
		break;
		
		case "prosper_13":
			dialog.text = "Нет, друг мой. У меня есть обязательства перед дочерью. Она заставила меня поклясться, что я завяжу с этими авантюрами. Эта была последняя. Жаль, черт побери, но дочь свою я люблю больше всего на свете. Прощайте, "+pchar.name+". И... Селина о вас постоянно говорит. Может, зайдете к нам как-нибудь?";
			link.l1 = "Может и зайду, как знать... Прощайте, Проспер! Мир вашему дому... (сам себе) Урок усвоен, месье Грегуар. Как ты там сказал? Каждому - свое? Надо запомнить.";
			link.l1.go = "prosper_14";
		break;
		
		case "prosper_14":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "15");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "contra":
			dialog.text = "Вы кто такие, черт побери?!";
			link.l1 = "Мы с товаром. Не интересно?";
			link.l1.go = "contra_1";
		break;
		
		case "contra_1":
			dialog.text = "Хе-хе. Очень интересно. Моему заказчику так особенно. Какой улов?";
			link.l1 = ""+FindRussianQtyString(sti(pchar.questTemp.FMQL.Sanl))+" бакаута, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Silk))+" шелка, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Rope))+" канатов и "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Oil))+" смол.";
			link.l1.go = "contra_2";
		break;
		
		case "contra_2":// Addon 2016-1 Jason пиратская линейка
			iTotalTemp = 2200*sti(pchar.questTemp.FMQL.Sanl)+1600*sti(pchar.questTemp.FMQL.Silk)+1000*sti(pchar.questTemp.FMQL.Rope)+900*sti(pchar.questTemp.FMQL.Oil);
			dialog.text = "Отлично. Бакаут - 2200 песо за штуку, смолы - 900 песо за бочонок, шелк - 1600 песо за рулон, канаты - 1000 песо за бухту. Всего это получается... так-так... "+iTotalTemp+" песо. По рукам?";
			link.l1 = "По рукам!";
			link.l1.go = "contra_3";
		break;
		
		case "contra_3":
			LAi_Fade("", "");
			FMQL_CreateGuidesWarriors();
			dialog.text = "Превосходно! Приносите еще. Голландцы всегда будут рады подбросить краснокожим еще подарок... А это еще что за гости? Какого черта?!";
			link.l1 = "";
			link.l1.go = "contra_4";
		break;
		
		case "contra_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_19";
			AddMoneyToCharacter(sld, iTotalTemp);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FMQL_beach":
			pchar.quest.FMQL_pirate_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			dialog.text = "Да, кэп. Не зря я пропил отплытие.";
			link.l1 = "Ты? Откуда?! Как?!";
			link.l1.go = "FMQL_beach_1";
		break;
		
		case "FMQL_beach_1":
			dialog.text = "Простите, кэп. После этой истории с индейцами мне надо было выпить. А там еще была эта девка, за сто песо я снял комнату, а она, она...";
			link.l1 = "Стащила твои деньги?";
			link.l1.go = "FMQL_beach_2";
		break;
		
		case "FMQL_beach_2":
			sld = CharacterFromID("FMQL_Prosper");
			dialog.text = "Нет! Влюбилась! Проклятье, надо было валить оттуда! Но тут врывается ваш знакомый и орет, что эта падаль, компаньон бывший, хочет вас облапошить и грохнуть.";
			if (LAi_GetCharacterHP(sld) > 0)
			{
				link.l1 = "Молодчина, Проспер...";
				link.l1.go = "FMQL_beach_3";
			}
			else
			{
				link.l1 = "Проспер... Прости меня. Я позабочусь о твоей дочери. Урок усвоен, месье Грегуар... Как ты там сказал? Каждому - свое? Надо запомнить.";
				link.l1.go = "FMQL_beach_3";
			}
		break;
		
		case "FMQL_beach_3":
			dialog.text = "Уходим, кэп?";
			link.l1 = "Да. Спасибо за службу. Больше не пей, мы спасем тебя от той красотки. Уходим.";
			if (CheckAttribute(pchar, "questTemp.FMQL.ProsperDead")) link.l1.go = "FMQL_beach_5";
			else link.l1.go = "FMQL_beach_4";
		break;
		
		case "FMQL_beach_4": // Проспер жив
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload_sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			sld = CharacterFromID("FMQL_Prosper");
			sld.Dialog.currentnode = "prosper_11";
			sld.MusketerDistance = 20;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
		break;
		
		case "FMQL_beach_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			if (sti(pchar.money) >= 20000) DoQuestFunctionDelay("FMQL_MoneyForSelina", 0.5);
			else
			{
				pchar.quest.FMQL_money_20k.win_condition.l1 = "Money";
				pchar.quest.FMQL_money_20k.win_condition.l1.value = 20000;
				pchar.quest.FMQL_money_20k.win_condition.l1.operation = ">=";
				pchar.quest.FMQL_money_20k.function = "FMQL_MoneyForSelina";
			}
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "10");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
