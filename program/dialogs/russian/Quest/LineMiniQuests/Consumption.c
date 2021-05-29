// диалоги по квесту Цена чахотки
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Consumption == "final")
			{
				dialog.text = "Капитан! Вы выходили в море, я слышала! Что произошло, вы что-то узнали? Прошу вас, скажите, не томите!";
				if (CheckAttribute(pchar, "questTemp.Consumption.TakeMoney"))
				{//взял деньги
					link.l1 = "Нет, красавица, это был рейд по просьбе его светлости губернатора. Мне очень жаль, но Анджело действительно умер в казематах форта – теперь в этом нет сомнений. Крепитесь.";
					link.l1.go = "Waitress";
				}
				else
				{//убил Хуана
					if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
					{
						link.l1 = "Вы были правы, вашего брата похитили – комендант продавал узников как скот, работорговцу по прозвищу Чахотка. Но я нагнал его судно, и теперь он покоится на дне морском, а ваш брат Анджело сойдёт на берег в ближайшее время – у меня на борту не так много шлюпок, как пассажиров сегодня.";
						link.l1.go = "Waitress_2";
					}
					else
					{//отпустил Хуана
						link.l1 = "Вы были правы, вашего брата похитили – комендант продавал узников как скот, работорговцу по прозвищу Чахотка. Но я нагнал его судно, и, хоть не удалось уничтожить самого мерзавца, ваш брат спасён. Анджело сойдёт на берег в ближайшее время – у меня на борту не так много шлюпок, как пассажиров сегодня.";
						link.l1.go = "Waitress_2";
					}
					sld = characterFromId("ConAndjelo");
					sld.lifeday = 0;
					RemovePassenger(Pchar, sld);
				}
			}
			else
			{
				dialog.text = "Вам удалось узнать что-нибудь о судьбе Анджело, капитан?";
				link.l1 = "Пока нет. Но, думаю, новости скоро будут. Жди.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		case "without_moneysss": // лесник  если Гг нажрался..сволочь:D:D:D
		    dialog.text = "Сеньор, вы же пообещали найти моего брата, а сами в таверне напились!";
			link.l1 = "Оо..Да, точно..ик.. Успокойся, милашка, я уже п-пошёл искать...ик..кхе..";
			link.l1.go = "exit";
		break;
		
		case "Servant":
			dialog.text = "Добрый день, сеньор. Вы по какому делу?";
			link.l1 = "Я принёс депешу сеньору полковнику, но должен отдать её ему лично в руки.";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Тогда вам следует искать его в форте.";
			link.l1 = "Эта встреча слишком важна, и не для солдатских глаз и ушей. Возможно, я просто пришёл раньше, но я могу подождать полковника здесь. Поверьте, это очень важно!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < 20)
			{
				dialog.text = "Сеньор обычно предупреждает меня обо всех важных делах, требующих изменения распорядка... И знаете, о вашем он тоже, кажется, кое-что говорил...";
				link.l1 = "Да, и что же?";
				link.l1.go = "Servant_3";
			}
			else
			{
				dialog.text = "Ладно, я вам верю, и поверю ещё больше, если сеньор полковник появится и подтвердит ваши слова. Но знайте – до тех пор я с вас глаз не спущу.";
				link.l1 = "Смотрите сколько угодно...";
				link.l1.go = "Servant_4";
			}
		break;
		
		case "Servant_3":
			dialog.text = "Он говорил во всех таких случаях обращаться к гарнизонной страже. Но мы, наверное, справимся сами... Парни, сюда!";
			link.l1 = "Проклятье!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Servant_4":
			DialogExit();
			NextDiag.CurrentNode = "Servant_repeat";
			LAi_SetOwnerType(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Servant_repeat":
			dialog.text = "Ну, что вам ещё? Или вы решили отдать вашу депешу мне?";
			link.l1 = "Нет, пожалуй, я всё-таки дождусь полковника...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Servant_repeat";
		break;
		
		case "Servant_fight":
			int iRank = sti(pchar.rank)+5;
			int iScl = 15 + 2*sti(pchar.rank);
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true;
			for (i=9; i<=11; i++)
			{	
				sld = GetCharacter(NPC_GenerateCharacter("Conservant_"+i, "citiz_"+i, "man", "man", iRank, SPAIN, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "goto", "goto5");
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Consumption_AfterHouseFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//попытка залезть в сундук
		case "Man_FackYou":
			dialog.text = "Ах ты, ворюга! А быть может, шпион? Ребята, сюда, на помощь!";
			link.l1 = "А-ать, дьявол!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Sergio":
			dialog.text = "Прошу прощения, могу я с вами поговорить?";
			link.l1 = "Признаться, я немного спешу. Что вы хотели?";
			link.l1.go = "Sergio_1";
		break;
		
		case "Sergio_1":
			dialog.text = "Я слышал, как вы расспрашивали о человеке по имени Хуан, и о болезнях в нашей тюрьме...";
			link.l1 = "Так... и к чему это вы?";
			link.l1.go = "Sergio_2";
		break;
		
		case "Sergio_2":
			dialog.text = "Тише! Успокойтесь и не хватайтесь за шпагу! Мы на одной стороне! Я не знаю, что вам за дело до наших проблем, но этому пора положить конец. Я не могу больше молчать!";
			link.l1 = "Молчать? О чём? Вам что-то известно о чахотке?";
			link.l1.go = "Sergio_3";
		break;
		
		case "Sergio_3":
			dialog.text = "Мне известно многое, если не всё, и я вам это расскажу, но не здесь. Встретимся вечером: после отбоя, я, как фельдшер, могу спокойно покинуть форт. Встретимся за городскими воротами, и я всё объясню. Только прошу – прекратите расспросы, пока вы их не насторожили! Если вы уже этого не сделали... А теперь мне пора. Помните, после заката - за городскими воротами.";
			link.l1 = "Хорошо, я буду там. Эй! Постойте...";
			link.l1.go = "Sergio_4";
		break;
		
		case "Sergio_4":
			DialogExit();
			AddQuestRecord("Consumption", "8");
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption3.win_condition.l1 = "location";
			pchar.quest.Consumption3.win_condition.l1.location = "PortSpein_Exittown";
			pchar.quest.Consumption3.win_condition.l2 = "Hour";
			pchar.quest.Consumption3.win_condition.l2.start.hour = 0;
			pchar.quest.Consumption3.win_condition.l2.finish.hour = 3;
			pchar.quest.Consumption3.function = "Consumption_MeetSergio";
			pchar.quest.Consumption4.win_condition.l1 = "Timer";
			pchar.quest.Consumption4.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Consumption4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Consumption4.function = "Consumption_FailSergio";
			locations[FindLocation("PortSpein_Exittown")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("PortSpein_Exittown", true);//офицеров не пускать
		break;
		
		case "Sergio_5":
			dialog.text = "Слава Богу, вы пришли... Не замечали за собой слежки?";
			link.l1 = "А должен был? Что-то вы мне подозрительны, и уже не меньше сеньора коменданта, так что лучше переходите к делу... Что вам известно о Хуане?";
			link.l1.go = "Sergio_6";
		break;
		
		case "Sergio_6":
			dialog.text = "Моё имя - Сержио Сальдо. Я исполняю обязанности фельдшера в нашем форте и...";
			link.l1 = "Стойте! Вы это слышали?";
			link.l1.go = "Sergio_7";
		break;
		
		case "Sergio_7":
			dialog.text = "Что?! Где?";
			link.l1 = "Клянусь громом, мы здесь не одни... Ты кого с собой привёл, негодяй?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Consumption_CreateBandits");
		break;
		
		case "Bandit":
			dialog.text = "Заметил, гад! Ласко, давай, режь солдафона, а я займусь этим!";
			link.l1 = "...";
			link.l1.go = "Bandit_1";
		break;
		
		case "Bandit_1":
			DialogExit();
			sld = characterFromId("Sergio");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=3; i++)
			{	
				sld = characterFromId("Conbandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Conbandit_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Sergio_8":
			dialog.text = "Уберите оружие, всё кончено! Вы же видели – они пытались убить и меня тоже!";
			link.l1 = "Да, для предательства слишком изощрённо. Итак – вы не с ними... На чём мы остановились? Вы - тюремный врач?";
			link.l1.go = "Sergio_9";
		break;
		
		case "Sergio_9":
			dialog.text = "Да. Я исполняю обязанности тюремного врача – изучал медицину в молодости, а здесь мало образованных людей. Потому то я знаю то, что творится в тюрьме лучше, чем кто бы то ни было!";
			link.l1 = "И вы знаете, куда пропадают заключённые, якобы, умершие от болезни, чьих тел и похорон, никто не видит?";
			link.l1.go = "Sergio_10";
		break;
		
		case "Sergio_10":
			dialog.text = "Это всё полковник. Да-да, наш комендант – он продаёт их... просто продаёт, как скот, одному ловцу людей, по имени Хуан. Выбирает тех, кого никто не будет искать – бедняков, матросов со случайных кораблей. А потом, они 'скоропостижно умирают от чахотки' со всеми вытекающими...";
			link.l1 = "Значит, Хуан - это всё же человек! Что вы знаете о нём?";
			link.l1.go = "Sergio_11";
		break;
		
		case "Sergio_11":
			dialog.text = "Немного. В Старом Свете он промышлял в Марокко, подвизался с берберийскими пиратами, о чём сам постоянно вспоминает во время своих редких визитов. Там он и получил прозвище 'Чахотка'. За что – думать, если честно, не хочу\nПриезжает сюда раз в месяц и переправляет отобранных за этот срок заключённых себе на борт. Потом уплывает до следующего раза.";
			link.l1 = "'Чахотка'... И это меня ещё обвиняли в цинизме! Вот почему именно эта болезнь... А сеньор комендант мерзавец ещё тот, как я погляжу!";
			link.l1.go = "Sergio_12";
		break;
		
		case "Sergio_12":
			dialog.text = "Я так понимаю, вам нужен кто-то из пропавших заключённых – иначе, как бы вы узнали об этой истории, я прав? Если так, то вам нужно спешить – сегодняшняя ночь последняя в этом месяце. Я уже подписал бумаги о смерти ещё трёх человек, и, получив их, Хуан снимется с якоря завтра до полудня!";
			link.l1 = "Вы подписали что? Не совсем понимаю...";
			link.l1.go = "Sergio_13";
		break;
		
		case "Sergio_13":
			dialog.text = "Да, я вынужден был это сделать, как делаю уже несколько месяцев! Почему я и пришёл к вам, чтобы остановить это. Знаете, как умер доктор Пинеро, лечивший заключённых до меня?";
			link.l1 = "Кажется, мне говорили, что его унесла чахотка, да? Итак – вас заставляют. Логично, но почему никто ничего не рассказал властям?";
			link.l1.go = "Sergio_14";
		break;
		
		case "Sergio_14":
			dialog.text = "И кто поверит? У меня нет никаких доказательств, а тем солдатам, что якобы охраняют камеры в ночи погрузок, и 'хоронят умерших от болезни', щедро приплачивают, так что им плевать, пусть хоть карибам на провиант продают\nДо заключённых никому нет дела, и это сильная сторона плана сеньора коменданта. Но вы можете остановить это хотя бы на время, уничтожив Хуана!";
			link.l1 = "Как я понимаю, эти ребята на земле, были от него, да? Как мне его найти?";
			link.l1.go = "Sergio_15";
		break;
		
		case "Sergio_15":
			dialog.text = "Да скорее всего вы привлекли чьё-то внимание своими расспросами... Я же говорил вам быть осторожней! Но сейчас это уже неважно. Я не знаю ничего про корабль Хуана, но заключённых всегда отправляли на мыс Галера, что на севере острова. Полагаю, корабль работорговца неподалёку, и вы можете туда успеть – его посланцы сегодня сказали, что отплывают завтра в полдень.";
			if (!CheckCharacterItem(pchar, "letter_consumption"))
			{
				link.l1 = "Благодарю вас, Сержио, вы настоящий офицер, и поступили по чести. Я немедленно снимаюсь с якоря и найду это мерзкое судно, а вы возвращайтесь, пока вас не хватились в форте.";
				link.l1.go = "Sergio_16";
			}
			else
			{
				link.l1 = "Что же, это всё, что мне нужно знать. Надо немедленно сниматься с якорей, чтобы не пришлось искать Чахотку по всему Новому Свету. А вы пока изучите вот это.";
				link.l1.go = "Sergio_17";
			}
		break;
		
		case "Sergio_16":
			dialog.text = "Удачи вам, капитан! За меня не беспокойтесь – главное, чтобы это остановилось, хоть на время. Желаю удачи!";
			link.l1 = "Мои бортовые пушки отличное лекарство от хворей и гнусности, ещё до рассвета все пленные будут на берегу, а корабль Хуана на дне – клянусь!";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_17":
			RemoveItems(PChar, "letter_consumption", 1);
			Log_Info("Вы отдали письмо");
			PlaySound("interface\important_item.wav");
			dialog.text = "Что это? Тут имя полковника и монограмма 'Х'? Невероятно! Откуда у вас это?";
			link.l1 = "Лучше вам об этом не знать, но, я думаю, вы найдёте письму достойное применение.";
			link.l1.go = "Sergio_18";
		break;
		
		case "Sergio_18":
			dialog.text = "Найду, клянусь всеми святыми! Полковник попадёт на виселицу ещё до конца месяца! Уж теперь-то я об этом позабочусь!";
			link.l1 = "Боюсь, дело обойдётся просто должностным взысканием – не первым, как я понимаю, в его жизни. Может - просто пристрелить? Очень действенное средство... А теперь мне пора – не стоит заставлять Чахотку ждать.";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_19":
			DialogExit();
			AddQuestRecord("Consumption", "11");
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption5.win_condition.l1 = "location";
			pchar.quest.Consumption5.win_condition.l1.location = "Trinidad";
			pchar.quest.Consumption5.function = "Consumption_CreateJuan";
			pchar.quest.Consumption6.win_condition.l1 = "HardHour";
			pchar.quest.Consumption6.win_condition.l1.hour = 13;
			pchar.quest.Consumption6.function = "Consumption_FailJuan";
			// Сержио теперь наш друг и будет торговать смолами
			SetFunctionTimerCondition("Oil_PrepareSergio", 0, 0, 20, false); // таймер
		break;
		
		// генератор торговли смолами
		case "Sergio_20":
			dialog.text = "О, какая встреча! Сеньор "+GetFullName(pchar)+"! Рад вас видеть!";
			link.l1 = "Сеньор Сержио! Вот уж не ожидал? Как ваши дела? Как поживает господин комендант?";
			link.l1.go = "Sergio_21";
		break;
		
		case "Sergio_21":
			dialog.text = "Мои дела - неплохо, а вот господин комендант нашими общими стараниями отправился на рудник Лос-Текес - все его мерзкие махинации с Хуаном Чахоткой выплыли наружу.";
			link.l1 = "На рудник? Не может быть! Вот уж не ожидал такого торжества правосудия.";
			link.l1.go = "Sergio_22";
		break;
		
		case "Sergio_22":
			dialog.text = "Ах, оставьте, капитан... Он просто переведён с понижением - теперь он служит в гарнизоне, даже офицерского чина не лишили. Ну хоть Сан-Хосе избавился от этого подонка, и то хорошо.";
			link.l1 = "Ну, хоть так. Хотя я ожидал... несколько большего.";
			link.l1.go = "Sergio_23";
		break;
		
		case "Sergio_23":
			dialog.text = "Я тоже, но... впрочем, не будем больше об этом негодяе, он того не заслуживает. Сеньор, я как только прослышал, что ваш корабль входит в порт, сразу поспешил на пирс. У меня к вам есть дело.";
			link.l1 = "Даже так? Внимательно слушаю.";
			link.l1.go = "Sergio_24";
		break;
		
		case "Sergio_24":
			dialog.text = "Капитан, вы показались мне честным человеком, которому можно доверять. Также немаловажное значение имеет то, что вы - француз, и у вас есть свой корабль. Я предлагаю заключить торговое соглашение.";
			link.l1 = "Очень интересно! И какое же?";
			link.l1.go = "Sergio_25";
		break;
		
		case "Sergio_25":
			dialog.text = "Об этом лучше поговорить в другом месте, на маяке, в домике смотрителя. Он мой старинный друг, так что ему я доверяю. Приходите на маяк Сан-Хосе сегодня или завтра - я буду вас ждать. Предложение должно вас заинтересовать!";
			link.l1 = "Хорошо, сеньор Сержио. Я обязательно приду!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Oil_SergioRuntoMayak");
		break;
		
		case "Sergio_26":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Oil_SetSergioToMayakOver.over = "yes"; //снять прерывание
			dialog.text = "Ещё раз приветсвую, сеньор. Позвольте мне изложить вам суть дела.";
			link.l1 = "Внимательно вас слушаю.";
			link.l1.go = "Sergio_27";
		break;
		
		case "Sergio_27":
			dialog.text = "Как вам уже известно, я совмещаю основную службу с должностью врача. Почему так? Потому что я получил в Европе хорошее образование. Это же самое образование позволило мне, по прибытии на Тринидад из метрополии, не тратить всё своё свободное время на шлюх и выпивку, как это характерно для многих офицеров, а организовать экспедицию и отыскать на острове недалеко отсюда месторождение природных смол\nЗатем я узаконил свои права на данный участок суши и начал разработку при помощи чернокожих рабов. На данный момент моё месторождение смол способно давать приличные объемы означенного вещества. Вы должны быть в курсе, для чего применяются природные битумные смолы - для пропитки корпусов кораблей. Это делает их прочнее и устойчивее к износу\nТакой смолы, как на Тринидаде, нет более нигде и она является стратегическим товаром. Моё месторождение, конечно, не единственное на острове, но тем не менее губернатор и комендант форта обязали меня продавать все добытые смолы исключительно на нужды испанского флота\nБеда в том, что они платят мне за товар половину рыночной стоимости, а вывезти смолы за пределы Тринидада и продать где-то ещё я не могу. Вот я и хочу предложить вам приобретать смолу у меня. Это очень нужный товар, и его весьма непросто достать.";
			link.l1 = "Каковы условия нашего договора?";
			link.l1.go = "Sergio_28";
		break;
		
		case "Sergio_28":
			dialog.text = "В течение месяца я буду откладывать понемногу смолы для вас и сформирую партию в 60 бочек. Я прикинул - именно столько я смогу собрать за месяц, не возбудив подозрения властей. Давайте договоримся, что каждого пятого числа месяца я буду наведываться сюда, на маяк, и если вы решите приобрести смолы - то пожалуйста. Стоимость одной бочки смол - десять золотых дублонов\nДеньги за всю партию оплачиваете сразу, сразу всю и забираете. Если вы не пришли пятого числа - то я начинаю распродавать товар другим покупателям, либо сдаю губернатору. То есть, ничто вас не обязывает, сугубо ваше личное желание. По рукам?";
			link.l1 = "Неплохое предложение. Конечно, договорились!";
			link.l1.go = "Sergio_29";
		break;
		
		case "Sergio_29":
			dialog.text = "Замечательно. Тогда каждого пятого числа я буду распивать со своим старым другом-смотрителем бутылочку канарского, ожидая, что вы вдруг появитесь.";
			link.l1 = "Хорошо. Так и поступим.";
			link.l1.go = "Sergio_30";
		break;
		
		case "Sergio_30":
			dialog.text = "Я рад, что мы договорились. А теперь - до встречи, капитан!";
			link.l1 = "Удачи в вашем смоляном деле, сеньор.";
			link.l1.go = "Sergio_31";
		break;
		
		case "Sergio_31":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			pchar.questTemp.OilTrade = "true";
			pchar.quest.Oil_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.Oil_fail.win_condition.l1.character = "Sergio";
			pchar.quest.Oil_fail.function = "Oil_TradeFail";
			AddQuestRecord("Unique_Goods", "4");
		break;
		
		case "oil_trade":
			dialog.text = "Приветствую, сеньор капитан! Вы пришли за своей партией смол, как я полагаю?";
			link.l1 = "Так точно, сеньор Сержио. Всё готово?";
			link.l1.go = "oil_trade_1";
			link.l2 = "Сеньор Сержио, мне пока не до торговли. Возможно, немного позже.";
			link.l2.go = "oil_trade_exit";
		break;
		
		case "oil_trade_exit":
			DialogExit();
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "oil_trade_1":
			dialog.text = "Да. Шесть сотен дублонов при вас?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 600)
			{
				link.l1 = "Безусловно. Вот, возьмите ваши деньги.";
				link.l1.go = "oil_trade_2";
			}
			else
			{
				link.l1 = "Вот незадача, забыл деньги на корабле. Сейчас принесу!";
				link.l1.go = "oil_trade_exit";
			}
		break;
		
		case "oil_trade_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			RemoveItems(pchar, "gold_dublon", 600);
			Log_Info("Вы отдали 600 дублонов");
			PlaySound("interface\important_item.wav");
			dialog.text = "Приятно иметь с вами дело, капитан. Мои люди помогут погрузить бочки на ваш корабль.";
			link.l1 = "Спасибо!";
			link.l1.go = "oil_trade_3";
		break;
		
		case "oil_trade_3":
			dialog.text = "Договор остаётся в силе. Если желаете купить ещё партию - жду вас через месяц.";
			link.l1 = "Хорошо, Сержио. До встречи.";
			link.l1.go = "oil_trade_4";
		break;
		
		case "oil_trade_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			AddCharacterGoods(pchar, GOOD_OIL, 60);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
	// <-- генератор смол
		
		case "Juan_abordage":
			dialog.text = "Кто ты, дьявол тебя дери!?";
			link.l1 = "Моё имя – "+GetFullName(pchar)+", а тебя ждут черти, Чахотка, и получат, не сомневайся!";
			link.l1.go = "Juan_abordage_1";
		break;
		
		case "Juan_abordage_1":
			if (CheckAttribute(pchar, "questTemp.Consumption.House"))
			{
				dialog.text = "Этот корабль сейчас взлетит на воздух – запальный шнур в крюйт-камере уже горит, так зачем погибать всем? Давай опустим клинки, и ты успеешь убраться, а я выпрыгну за борт – до мыса Галера тут рукой подать. Если тебе нужно золото – бери! Пятьсот полновесных дублонов, и ты забудешь обо мне, а я о тебе?";
				link.l1 = "Золото? Я с самого начала ввязался в это дело не ради денег, Хуан. Прикончить такую мерзость как ты – сама по себе награда.";
				link.l1.go = "Juan_abordage_2";
				link.l2 = "Всего пятьсот дублонов? Да ты смеёшься надо мной, Чахотка - думаю, у тебя припрятано где-то здесь минимум вдвое больше... Выкладывай сейчас же тысячу дублонов и катись ко всем чертям – иначе...";
				link.l2.go = "Juan_abordage_3";
			}
			else
			{
				dialog.text = "Корабль сейчас взлетит на воздух, так что у меня будет солидная компания, как думаешь?";
				link.l1 = "Много болтаешь, Чахотка - к делу!";
				link.l1.go = "Juan_abordage_5";
			}
		break;
		
		case "Juan_abordage_2":
			dialog.text = "А ведь могли бы договориться... Эх!";
			link.l1 = "Ты хватал несчастных из их камер, где они не могли ни убежать, ни сопротивляться. Ты трус, Чахотка, и умрёшь сейчас.";
			link.l1.go = "Juan_abordage_5";
		break;
		
		case "Juan_abordage_3":
			dialog.text = "А у тебя есть хватка, приятель... держи, это всё, что у меня есть – небольшая плата за жизнь, если вдуматься, да?";
			link.l1 = "За твою жизнь я бы не дал и пистолетной пули, так что это самая выгодная моя сделка. Катись к чертям.";
			link.l1.go = "Juan_abordage_4";
			TakeNItems(pchar, "gold_dublon", 1000);
			Log_Info("Вы получили 1000 дублонов");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			OfficersReaction("bad");
			pchar.questTemp.Consumption.TakeMoney = "true"; //атрибут для диалога
		break;
		
		case "Juan_abordage_4":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "ConJuan_AfterFight_1", 10.0);
		break;
		
		case "Juan_abordage_5":
			dialog.text = "Жаль только, ты не успеешь спасти всех и прикончить меня, ведь так, а? Шнур горит и время тоже...";
			link.l1 = "Проклятье! Надо выводить людей... чёрт с тобой, мерзавец – ты своё получишь рано или поздно!";
			link.l1.go = "Juan_abordage_4";
			link.l2 = "А я всё же попробую...";
			link.l2.go = "Juan_abordage_6";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
			sld = GetCharacter(NPC_GenerateCharacter("ConAndjelo", "citiz_9", "man", "man", 5, SPAIN, -1, true, "quest"));
			sld.name = "Анджело";
			sld.lastname = "";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
		break;
		
		case "Juan_abordage_6":
			//LAi_SetCurHPMax(NPChar);
			//LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("ConJuan_AfterFight_2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Consumption.KillJuan = "true"; //атрибут для диалога
		break;
		
		case "Waitress":
			dialog.text = "Ах... У меня нет слов... Какой кошмар!";
			link.l1 = "Я ничего не смог сделать - увы! Мне жаль. Прощайте!";
			link.l1.go = "Waitress_1";
		break;
		
		case "Waitress_1":
			DialogExit();
			AddQuestRecord("Consumption", "16");
			Consumption_Close();
		break;
		
		case "Waitress_2":
			dialog.text = "Невероятно! Вы... вы его правда спасли? Не представляю, как мне вас благодарить!";
			if (CheckAttribute(npchar, "quest.Consumption.sex"))
			{
				link.l1 = "Красотка, я то, как раз, представляю. Но – моя часть уговора завершена, дело за малым.";
				link.l1.go = "Waitress_3";
			}
			link.l2 = "Я сделал то, что подсказывал мне долг - только и всего.";
			link.l2.go = "Waitress_5";
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan")) AddQuestRecord("Consumption", "18");
			else AddQuestRecord("Consumption", "17");
		break;
		
		case "Waitress_3":
			dialog.text = "Я... о Боже! Да, вы правы. Ради него, как я и обещала... Поднимайтесь в комнату – у нас не так много времени.";
			link.l1 = "Тогда поспешим!";
			link.l1.go = "Waitress_4";
		break;
		
		case "Waitress_4"://благодарность натурой
			DialogExit();
			LocatorReloadEnterDisable("PortSpein_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("PortSpein_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "PortSpein_tavern_upstairs", "goto", "goto3", "ConsumptionSexWaitress", -1);
			pchar.questTemp.Consumption.Sex = "true";
		break;
		
		case "Waitress_sex":
			dialog.text = "";
			link.l1 = "Ну что, малышка, давай повеселимся! Ведь у тебя сегодня действительно счастливый день...";
			link.l1.go = "Waitress_sex_1";
		break;
		
		case "Waitress_sex_1":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;
		
		case "Waitress_5":
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
			{
				dialog.text = "Вы настоящий рыцарь! Кабальеро! Вот, не сочтите за оскорбление, но я хочу, чтобы вы взяли их – я собрала эти деньги на выкуп за Анджело, но теперь это уже не важно! Не вздумайте отказываться – примите их!";
				link.l1 = "Что же, я буду помнить ваши глаза, сеньорита – они куда прекрасней, когда сверкают от счастья, а не от слёз. Я принимаю ваш дар. Прощайте и удачи вам и Анджело.";
				link.l1.go = "Waitress_6";
				AddMoneyToCharacter(pchar, 5000);
			}
			else
			{
				dialog.text = "Вы настоящий рыцарь! Кабальеро! Я расскажу всем! И буду помнить вас всегда-всегда!";
				link.l1 = "Что же, и я буду помнить ваши глаза сеньорита – они куда прекрасней, когда сверкают от счастья, а не от слёз. Пусть так будет и впредь. Прощайте!";
				link.l1.go = "Waitress_6";
			}
		break;
		
		case "Waitress_6":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			Consumption_Close();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}