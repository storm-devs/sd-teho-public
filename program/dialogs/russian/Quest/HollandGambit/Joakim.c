// Жоаким Мерриман - португальский сумрачный гений
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbySeekIsland" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "Добрый день! Меня зовут Жоаким Мерриман. А вы - капитан " + GetFullName(pchar) + "?";
					link.l1 = "Совершенно верно. Откуда вам известно моё имя? Не помню, чтобы я когда-либо встречался с вами.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					dialog.text = "Рад вас видеть, капитан. Судя по вашим блестящим глазам, вы готовы обрадовать меня? Череп Юм Симиля у вас?";
					link.l1 = "Да, сеньор Мерриман. Нужный вам артефакт у меня. Думаю, это именно он - от него так и веет древностью и какой-то скрытой силой.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "Вы что-то ещё хотели мне сказать, капитан?";
				link.l1 = "Нет, сеньор Мерриман. Я уже ухожу.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "JoakimMeeting" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "Добрый день! Меня зовут Жоаким Мерриман. А вы - капитан " + GetFullName(pchar) + "?";
					link.l1 = "Совершенно верно. Откуда вам известно моё имя? Не помню, чтобы я когда-либо встречался с вами.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					dialog.text = "Рад вас видеть, капитан. Судя по вашим блестящим глазам, вы готовы обрадовать меня? Череп Юм Симиля у вас?";
					link.l1 = "Да, сеньор Мерриман. Нужный вам артефакт у меня. Думаю, это именно он - от него так и веет древностью и какой-то скрытой силой.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "Вы что-то ещё хотели мне сказать, капитан?";
				link.l1 = "Нет, сеньор Мерриман. Я уже ухожу.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Добрый день. Вы что-то хотели от меня?";
			link.l1 = "Нет. Прошу меня извинить, я уже ухожу.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Landlady"://хозяйка дома
			dialog.text = "Если вы к сеньору Жоакиму, то поднимайтесь на второй этаж. Он у себя.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady";
		break;
		
		case "Landlady_1"://хозяйка дома
			dialog.text = "Если вы к сеньору Жоакиму, то его нет. Ушёл, а когда вернётся - не сказал.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_1";
		break;
		
		case "Landlady_2"://хозяйка дома
			dialog.text = "Если вы к сеньору Жоакиму, то его нет. Он больше здесь не живёт.";
			link.l1 = "Понятно.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_2";
		break;
		
		case "JoakimSeekSkull":
			PlaySound("VOICE\Russian\hambit\Joakim Merriman-01.wav");
			dialog.text = "Я просто навёл о вас справки, капитан. Понимаете, я учёный, занимаюсь изучением индейской культуры и этноса, и я бы хотел предложить вам одно невероятно выгодное для вас дело. Не откажете ли в любезности пройти ко мне в дом и в более спокойной обстановке обсудить детали моего предложения?";
			link.l1 = "Никогда не отказываюсь от выгодных деловых предложений. Давайте пройдём и побеседуем.";
			link.l1.go = "JoakimSeekSkull_1";
		break;
		
		case "JoakimSeekSkull_1":
			dialog.text = "Благодарю. Мой дом совсем недалеко отсюда. Следуйте за мной!";
			link.l1 = "...";
			link.l1.go = "JoakimSeekSkull_2";
		break;
		
		case "JoakimSeekSkull_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "Villemstad_houseSp1_room", "goto", "goto1", "JoakimInRoom", -1);
		break;
		
		case "JoakimSeekSkull_3":
			PlaySound("VOICE\Russian\hambit\Joakim Merriman-01.wav");
			dialog.text = "Ну вот, здесь мы можем спокойно поговорить. Вы были сейчас в гостях у моего соседа, Соломона Шнеура. Я как раз проходил мимо, и - не взыщите, капитан - оказался случайным слушателем вашего разговора с Соломоном. Ваша беседа меня чрезвычайно заинтересовала, и я позволил себе дерзость остановиться и дослушать её до конца.";
			link.l1 = "Хм. И что же такого интересного было в нашей беседе с этим старым евреем?";
			link.l1.go = "JoakimSeekSkull_4";
		break;
		
		case "JoakimSeekSkull_4":
			dialog.text = "Соломон - мой сосед, и частенько захаживает ко мне в гости. Я знаю о его злоключениях... впрочем, кто о них не знает! Он рассказал об этом уже всему Виллемстаду. Но ближе к делу. Старик наверняка упоминал вам о неком черепе, который хранится вместе с его деньгами на неизвестном острове. Он говорил вам о нём?";
			link.l1 = "Да, было такое. По правде сказать, я ничего не понял, что это за череп, какого деда... У меня вообще сложилось впечатление, что папаша Абигайль немного не в себе.";
			link.l1.go = "JoakimSeekSkull_5";
		break;
		
		case "JoakimSeekSkull_5":
			dialog.text = "Нет, капитан, Соломон абсолютно нормален, просто несколько... чудаковат. Череп действительно существует. Это древний артефакт, совершенно невероятным образом попавший в руки этого старого еврея. Нефритовый череп Юм Симиля! Я ищу его уже много лет, и наконец появилась надежда таки заполучить его, спустя столько времени\nВы отправляетесь на поиски острова, где Соломон спрятал свой семейный капитал. Там же должен быть и череп. Доставьте мне эту вещь, и я заплачу вам полмиллиона песо.";
			link.l1 = "Полмиллиона?! Вы шутите! Я в жизни не встречал вещей, стоящих такую кучу денег!";
			link.l1.go = "JoakimSeekSkull_6";
		break;
		
		case "JoakimSeekSkull_6":
			dialog.text = "Вы многого ещё не встречали в своей жизни, капитан... Ну так что? Моё предложение вас заинтересовало? Вы мне - нефритовый череп, я вам - пятьсот тысяч. По рукам?";
			link.l1 = "Хех, какие могут быть разговоры! Конечно, по рукам!";
			link.l1.go = "JoakimSeekSkull_7";
		break;
		
		case "JoakimSeekSkull_7":
			dialog.text = "Отлично, капитан. Приятно иметь дело с человеком, понимающим свою очевидную выгоду. Вы сможете найти меня в этом доме. Желаю вам удачи в поисках!";
			link.l1 = "Спасибо, сеньор Мерриман. Я не заставлю вас долго ждать.";
			link.l1.go = "exit";
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			AddDialogExitQuestFunction("CheckIslandCoordinates");//вот тут-то мы и проверим, есть ли у нас координаты острова, и далее будем исходить из результата.
		break;
		
		case "JoakimFindSkull":
			PlaySound("VOICE\Russian\hambit\Joakim Merriman-02.wav");
			dialog.text = "О, да! Вы действительно правы насчёт скрытой силы... Но довольно слов, дайте мне на него взглянуть - я весь дрожу от нетерпения.";
			link.l1 = "Вот, пожалуйста, держите. Надеюсь, я не ошибся?";
			link.l1.go = "JoakimFindSkull_1";
		break;
		
		case "JoakimFindSkull_1":
			RemoveItems(PChar, "SkullAztec", 1);
			dialog.text = "Ах, невероятно! Да, это он. Великолепно, капитан, просто великолепно! Наконец-то он у меня! Я столько лет ждал этого момента!";
			link.l1 = "Что насчёт обещанных денег, сеньор Мерриман?";
			link.l1.go = "JoakimFindSkull_2";
		break;
		
		case "JoakimFindSkull_2":
			AddMoneyToCharacter(pchar, 500000);
			dialog.text = "О, да, конечно! Вот ваши полмиллиона. Держите, вы их честно заработали.";
			link.l1 = "Благодарю... Хотя я бы никогда и не представил себе, что эта небольшая штучка может стоить целое состояние.";
			link.l1.go = "JoakimFindSkull_3";
		break;
		
		case "JoakimFindSkull_3":
			dialog.text = "Небольшая штучка? Хм... Это... впрочем, вас навряд ли заинтересует научный рассказ об истории и свойствах этого артефакта. Да и честно говоря, у меня сейчас нет времени на лекции, предстоит ещё столько дел\nСпасибо вам, капитан, ещё раз за проделанную работу. А теперь мы должны с вами проститься. Мне нужно отправляться в дорогу.";
			link.l1 = "Всего доброго, сеньор Мерриман. Может, ещё увидимся...";
			link.l1.go = "JoakimFindSkull_4";
		break;
		
		case "JoakimFindSkull_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Landlady");
			sld.Dialog.Filename = "Quest\HollandGambit\Joakim.c";
			sld.dialog.currentnode = "Landlady_2";
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
		break;
		
		case "JoakimSeekSkull_8":
			PlaySound("VOICE\Russian\hambit\Joakim Merriman-01.wav");
			dialog.text = "Ну вот, здесь мы можем спокойно поговорить. Капитан, как мне известно, вы близко знакомы с Абигайль Шнеур, дочерью моего соседа Соломона. Она уехала на вашем корабле, как я понимаю, к своему возлюбленному... но это неважно.";
			link.l1 = "Хм. К чему вы клоните, сеньор... Мерриман?";
			link.l1.go = "JoakimSeekSkull_9";
		break;
		
		case "JoakimSeekSkull_9":
			dialog.text = "Раз вы знакомы с Соломоном, то наверняка знакомы и с его историей о кораблекрушении и об утраченных богатствах, спрятанных им на неком необитаемом острове - он рассказал о своих злоключениях всему Виллемстаду...";
			link.l1 = "Ну, допустим, я действительно немного слышал об этом. Каким образом сия история может меня заитересовать? Мне абсолютно безразличны неудачи этого старого еврея.";
			link.l1.go = "JoakimSeekSkull_10";
		break;
		
		case "JoakimSeekSkull_10":
			dialog.text = "Вам Соломон не понравился? Уверяю, это совершенно безобидный чудаковатый тип... Впрочем, и Бог с ним. Перейдём непосредственно к сути моего предложения, или просьбы\nЯ общался с Соломоном с момента его прибытия на остров. И вы не представляете, каково же было моё удивление, когда я узнал, что этот старый еврей является владельцем древнейшего артефакта - нефритового черепа Юм Симиля, который я разыскиваю уже много лет! Этот выживший из ума старик спрятал его вместе со своими жалкими сбережениями на острове, местонахождения которого он теперь даже и вспомнить не может\nМне нужен этот артефакт. Привезите его мне, и я заплачу вам за него полмиллиона песо.";
			link.l1 = "Полмиллиона?! Вы шутите! Я в жизни не встречал вещей, стоящих такую кучу денег!";
			link.l1.go = "JoakimSeekSkull_11";
		break;
		
		case "JoakimSeekSkull_11":
			dialog.text = "Вы многого ещё не встречали в своей жизни... Ну так что? Моё предложение вас заинтересовало? Вы мне - нефритовый череп, я вам - пятьсот тысяч. Кроме того, отыскав схрон Соломона, вы сможете забрать впридачу и его деньги. Судя по словам старика, там должно быть порядка двухсот тысяч песо... По рукам, капитан?";
			link.l1 = "Хех, какие могут быть разговоры! Конечно, по рукам! Вот только как разыскать этот остров, если вы говорите, что Соломон не знает, где он находится?";
			link.l1.go = "JoakimSeekSkull_12";
		break;
		
		case "JoakimSeekSkull_12":
			dialog.text = "Поговорите с Абигайль. Может, она что-то помнит. Побеседуйте с Соломоном. Понимаете, если бы я знал, как найти этот остров, я бы не обращался к вам за помощью, а как-нибудь управился бы собственными силами.";
			link.l1 = "Это понятно. Прошу прощения за глупый вопрос. Конечно, это мои проблемы, как найти этот остров... Моя работа - ваша оплата.";
			link.l1.go = "JoakimSeekSkull_13";
		break;
		
		case "JoakimSeekSkull_13":
			dialog.text = "Именно так. Я рад, что мы друг друга поняли, капитан. Желаю вам удачи в поисках. Вы всегда сможете найти меня здесь, в этом доме.";
			link.l1 = "Постараюсь не заставить вас долго ждать, сеньор Мерриман. До свидания!";
			link.l1.go = "JoakimSeekSkull_14";
		break;
		
		case "JoakimSeekSkull_14":
			DialogExit();
			pchar.questTemp.HWIC.Self = "SeekAbiIsland";
			AddQuestRecord("Holl_Gambit", "3-55");
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", true);//закроем комнату Аби
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "First time";
		break;
		
		// калеуче
		case "caleuche":
			PlaySound("VOICE\Russian\LSC\Chymiset-03.wav");
			dialog.text = "Кровью врагов залиты жертвенные камни! Юм Симиль даровал мне силу - власть над мёртвыми! И с этой силой я стану властвовать и над живыми!";
			link.l1 = "Что ты затеял, Мерриман, чёрт бы тебя побрал? Зачем тебе эти армии из зомби? Ты что, решил сражаться против всего мира?";
			link.l1.go = "caleuche_1";
			CreateLocationParticles("large_smoke", "goto", "goto37", 0.5, 0, 0, "");
		break;
		
		case "caleuche_1":
			dialog.text = "Молчи, глупец! Суть моих замыслов останется тайной для тебя! Мои армии тьмы оккупируют все тёмные пещеры и подземелья архипелага. Мои аванпосты будут стоять у каждого поселения в ожидании сигнала. А когда время придёт, мой легион выступит в решающее сражение!\nНо тебе не дожить до этого момента, наивный человечишко, вообразивший себя героем! Ты вступил в святая святых - моё убежище, и ты не выйдешь отсюда живым!";
			link.l1 = "Это мы ещё посмотрим!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			PlaySound("Types\warrior04.wav");
			dialog.text = "Ха-ха-ха-ха, ты осмелился выступить против меня и моих слуг?! Так посмотри же на того, кто я есть на самом деле, и устрашись, червь!";
			link.l1 = "...";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			npchar.model = "Meriman_2";
			Characters_RefreshModel(npchar);
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			dialog.text = "";
			link.l1 = "А-а-а!! О, черт!!!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			PlaySound("VOICE\Russian\hambit\Joakim Merriman-04.wav");
			dialog.text = "Теперь ты понял, слизняк, кто перед тобой?! Сам Юм Симиль покровительствует мне! Я вырву, зажарю и сожру твою печень!!";
			link.l1 = "Тысяча акул!! Ну, держись, проклятый колдун! Я снесу тебе твою зеленую черепушку!!";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto37", "none", "", "", "Caleuche_MerrimanTeleport", -1);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto37");
			pchar.questTemp.Caleuche.Merriman_hide = "true";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Да ты "+ GetSexPhrase("вор, милейший! Стража, держи его","воровка! Стража, держи её") +"!!!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Держи "+ GetSexPhrase("вора","воровку") +"!!!", "Стража! Грабят!!! Держи "+ GetSexPhrase("вора","воровку") +"!!!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}