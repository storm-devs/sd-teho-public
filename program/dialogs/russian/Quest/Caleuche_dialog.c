void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Явный баг. Сообщите об этом Jason'у, как и при каких обстоятельствах его получили.";
			link.l1 = "Обязательно сообщу!";
			link.l1.go = "exit";
		break;
		
		// шаман карибов Туттуатхапак
		case "Tuttuat":
			dialog.text = "Зачем твоя явиться мой хижина, белый человек? Туттуатхапак не мочь назвать тебя дорогой гость.";
			if (GetCharacterFreeItem(pchar, "mushket1") || GetCharacterFreeItem(pchar, "mushket2"))
			{
				link.l1 = "Здравствуй, великий шаман Туттуатхапак. Я пришёл к тебе за советом и помощью. Прими в знак моей дружбы в дар этот мушкет.";
				link.l1.go = "Tuttuat_1";
			}
			else
			{
				link.l1 = "Здравствуй, великий шаман Туттуатхапак. Я пришёл к тебе за советом и помощью.";
				link.l1.go = "Tuttuat_exit";
			}
		break;
		
		case "Tuttuat_exit":
			dialog.text = "Туттуатхапак не помогать белый человек. Белый люди - плохой люди. Они убивать и захватывать индеец, делать индеец раб. Туттуатхапак не давать совет белый человек. Твоя уходить.";
			link.l1 = "Гм...";
			link.l1.go = "Tuttuat_exit_1";
		break;
		
		case "Tuttuat_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat";
		break;
		
		case "Tuttuat_1":
			if (GetCharacterFreeItem(pchar, "mushket1")) sTemp = "mushket1";
			else sTemp = "mushket2";
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			Log_Info("Вы отдали "+XI_ConvertString(sTemp)+"");
			dialog.text = "Твоя знать, что подарить Туттуатхапак, белый человек. Туттуатхапак принимать твоя подношение. Он говорить. Какой совет твоя прийти получить от моя?";
			link.l1 = "Я слышал, что ты прибыл сюда из далеких мест на юге. У меня есть индейский амулет, и один знающий человек сказал, что ты сможешь помочь мне выяснить, как и для чего можно его применить.";
			link.l1.go = "Tuttuat_2";
		break;
		
		case "Tuttuat_2":
			dialog.text = "Показать моя этот амулет.";
			link.l1 = "Вот, возьми, великий шаман.";
			link.l1.go = "Tuttuat_3";
		break;
		
		case "Tuttuat_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(рассматривает)... Твоя человек сказать правда, белый человек. Этот амулет принадлежать предки моя народ, великий индеец чавин. Проклятый нечестивый бледнолицый пёс осквернить святилище и вывезти сюда. Этот пёс быть наказан Туттуатхапак.";
			link.l1 = "Ты лишил его рассудка, как я полагаю?";
			link.l1.go = "Tuttuat_4";
		break;
		
		case "Tuttuat_4":
			dialog.text = "Белый человек удивлять Туттуатхапак свой знание. Да, моя пожрать разум тот шелудивый пес. Он и его гнусный люди получить по заслуги.";
			link.l1 = "Ладно, не будем об этом... Скажи, шаман, для чего нужен этот амулет? Может, он защищает в бою, или отводит злые чары?";
			link.l1.go = "Tuttuat_5";
		break;
		
		case "Tuttuat_5":
			dialog.text = "Для твоя, белый капитан, этот амулет бесполезен. Твоя не мочь использовать его сила. Только великий шаманы наш племя знать, как пробудить амулет.";
			link.l1 = "Вот как... Получается, я проделал такой долгий путь напрасно. Но может, ты сумеешь пробудить силу этого амулета, великий шаман? Мы могли бы договориться...";
			link.l1.go = "Tuttuat_6";
		break;
		
		case "Tuttuat_6":
			dialog.text = "Даже если моя пробудить сила амулет, твоя не суметь удержать её долго. Но моя предложить сделка, белый человек.";
			link.l1 = "Какую сделку?";
			link.l1.go = "Tuttuat_7";
		break;
		
		case "Tuttuat_7":
			dialog.text = "Всего из святилище наш предки был вывезен три таких амулет. Они обладать разный свойства, но если они соединиться вместе, их мощь сильно-сильно возрасти. Найти и принести моя все три амулет, а моя за это вознаградить. Моя дать твоя сила, который твоя суметь удержать навсегда.";
			link.l1 = "Немного не понял... что за сила?";
			link.l1.go = "Tuttuat_8";
		break;
		
		case "Tuttuat_8":
			dialog.text = "Твоя всё узнать в свой время. Найти и принести моя все три амулет. Они быть на Карибы. Искать и найти. Твоя легко их узнать - они похож один на один. Идти, белый человек. Туттуатхапак ждать и просить духи помочь тебе.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_9";
		break;
		
		case "Tuttuat_9":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "ghostship"; 
			AddQuestRecord("Caleuche", "3");
			pchar.quest.Caleuche_ghostship.win_condition.l1 = "location";
			pchar.quest.Caleuche_ghostship.win_condition.l1.location = "Dominica";
			pchar.quest.Caleuche_ghostship.function = "Caleuche_PrepareGhostship";
		break;
		
		case "Tuttuat_10":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Идти, белый человек. Найти ещё два амулет.";
				link.l1 = "Уже нашел, великий шаман. Вот, смотри.";
				link.l1.go = "Tuttuat_33";
			}
			else
			{
				dialog.text = "Идти, белый человек. Найти два амулет.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_10_1";
			}
		break;
		
		case "Tuttuat_10_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
		break;
		
		case "Tuttuat_11":
			dialog.text = "Твоя снова здесь, белый человек? Твоя выглядеть так, как повстречаться свирепый ягуар джунгли.";
			link.l1 = "Хуже, великий шаман. Едва я вышел в море, как на меня напал корабль, битком набитый живыми скелетами! Их капитан неуязвим. Он отнял у меня амулет, чуть не убив при этом. А затем они утопили моё судно.";
			link.l1.go = "Tuttuat_12";
		break;
		
		case "Tuttuat_12":
			dialog.text = "Плохой новости, белый человек. Калеуче опять выйти на охота.";
			link.l1 = "Калеуче? Этот капитан-мертвяк назвал свой корабль 'Летящее сердце'. Ты знал о корабле-призраке? И ты ничего мне об этом не сказал? Да если бы я знал, что этот плавучий кошмар охотится за амулетом, я...";
			link.l1.go = "Tuttuat_13";
		break;
		
		case "Tuttuat_13":
			dialog.text = "Туттуатхапак видеть, белый капитан расстроен. Белый капитан должен успокоиться.";
			link.l1 = "Успокоиться?";
			link.l1.go = "Tuttuat_14";
		break;
		
		case "Tuttuat_14":
			dialog.text = "Да. Успокоиться и перестать кричать. Сказать моя, твоя ещё хотеть получить от моя большой сила, который остаться с твоя навсегда?";
			link.l1 = "Ну... хочу конечно. Но амулета-то у меня уже нет.";
			link.l1.go = "Tuttuat_15";
		break;
		
		case "Tuttuat_15":
			dialog.text = "Моя научить твоя, как забрать амулет у капитан Калеуче. Это быть нелегко. Но если твоя суметь сделать всё, то твоя получить его корабль военный трофей, найти ценный предметы, получить слава у твоя народ и моя награда.";
			link.l1 = "Чёрт возьми! Я с удовольствием поквитаюсь с этой высохшей образиной! Но как же я с ним управлюсь, если его ни сабля, ни пуля не берёт?";
			link.l1.go = "Tuttuat_16";
		break;
		
		case "Tuttuat_16":
			dialog.text = "Твоя готов слушать моя, белый капитан?";
			link.l1 = "Да, великий шаман.";
			link.l1.go = "Tuttuat_17";
		break;
		
		case "Tuttuat_17":
			dialog.text = "Когда моя отец быть ещё молодой воин, в земля мой народ прибыть отряд белый люди на корабле с имя 'Летящий сердце'. Они отправиться в горы, где древние легенды гласить, быть спрятан храм наши древний предки - храм люди-ягуары. Белый люди найти храм и золото, и осквернить древний святыня. Они вынести из святилище величайший сокровище чавинцы - нефритовый череп Юм Симиль, бога смерти и покровителя люди-ягуары\nБелый люди достигнуть свой корабль. Они решить вернуться назад храм, чтобы забрать ещё золото, но едва нога матрос ступить на пляж, как он умереть в страшный мучение. Юм Симиль проклясть команда и капитан. Они стать бессмертен, но не суметь больше никогда ступить на земля. Так они и плавать уже много-много зим, по календарь белый люди - полвек. Так появиться Калеуче\nИх тела износиться, плоть сгнить, но они оставаться живы. Если им отрубить рука или нога - она прирасти вновь. Если разрубить тело - оно соединиться. Если их корабль утонуть - они чинить его под вода, поднимать и плыть снова.";
			link.l1 = "Кошмар какой...";
			link.l1.go = "Tuttuat_18";
		break;
		
		case "Tuttuat_18":
			dialog.text = "Калеуче наводить ужас на моряки. Он нападать без видимый причина и нести неминуемый смерть. Он быть нечастый гость в Карибский море. Он любить плавать у берега мой родина. Моя думать - он хотеть снять проклятие. Но ему это не сделать никогда.";
			link.l1 = "Почему? А что нужно, чтобы снять проклятие?";
			link.l1.go = "Tuttuat_19";
		break;
		
		case "Tuttuat_19":
			dialog.text = "Нефритовый череп. Он надо вернуть в храм Юм Симиль, храм воины-ягуары. Есть несколько такой храм. Старейшины мой племя говорить, что один из них быть на маленький островок на Карибы. Вот почему Калеуче захаживать сюда. Как только череп оказаться храм - чары Юм Симиль уйти с команда и корабль, и они или умереть сами, или не суметь восстановить после повреждение сабля или пуля.";
			link.l1 = "Ха! Так может, они не хотят возвращать череп назад? Скажем, им неплохо живётся: бессмертные, неуязвимые... Да и как они это сделают - они же не могут ступить на землю!";
			link.l1.go = "Tuttuat_20";
		break;
		
		case "Tuttuat_20":
			dialog.text = "У них нет череп. Капитан выбросить его ещё на земля моих предки, когда возвращаться из святилище люди-ягуары. Нефрит не есть золото, он не нужен белый человек, а красивый зелёный камень в глаза череп он не суметь достать. Тогда он выкинуть череп. Его подобрать один матрос, и потому проклятье не коснуться он\nКогда матрос увидеть, что стать команда Калеуче, он бежать. Он быть наш деревня. Моя отец видеть тот матрос и череп Юм Симиль. А потом белый человек уйти вдоль берег на север вместе с череп.";
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				link.l1 = "Нефритовый череп с зелёными камнями в глазницах? Да я же держал его в своих руках, чёрт возьми! И я продал его какому-то португальцу... как его там... Мерриману, что ли... Да, он так и говорил - череп Юм Симиля! Он очень хотел получить его. Настолько, что заплатил за него полмиллиона песо!";
				link.l1.go = "Tuttuat_21_1";
			}
			else
			{
				link.l1 = "Нефритовый череп с зелёными камнями в глазницах? Я начинаю догадываться, что мне и его придётся найти? Так может он сгинул бесследно в сельве вместе с тем матросом полвека назад!";
				link.l1.go = "Tuttuat_21_2";
			}
		break;
		
		case "Tuttuat_21_1":
			dialog.text = "Моя знать, что череп быть на Карибы. Калеуче недаром появиться тут. Последние шесть лун его стать часто видеть у острова. Раньше он не бывать тут по много зим. Капитан Калеуче чувствовать, где есть артефакт люди-ягуары. Так он суметь найти и твоя корабль.";
			link.l1 = "Так, ладно. Что я должен сделать?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_21_2":
			dialog.text = "Череп должен быть здесь, на Карибы. Калеуче недаром появиться тут. Последние шесть лун его стать часто видеть у острова. Раньше он не бывать тут по много зим. Капитан Калеуче чувствовать, где есть артефакт люди-ягуары. Так он суметь найти и твоя корабль.";
			link.l1 = "Так, ладно. Что я должен сделать?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_22":
			dialog.text = "Твоя должен найти череп Юм Симиль. Твоя должен найти два амулет, про который мы говорить. Без них ничего не суметь сделать. Амулет дать тебе сила противостоять люди-ягуары.";
			link.l1 = "Противостоять людям-ягуарам? Это ты о чём сейчас?";
			link.l1.go = "Tuttuat_23";
		break;
		
		case "Tuttuat_23":
			dialog.text = "Храм, куда твоя должен отнести нефритовый череп, находиться на пустынный остров на Карибы. Он охраняться люди-ягуары. Без амулет твоя не суметь пройти мимо них. Люди-ягуары при жизнь быть свирепый воин, а после смерть стать почти непобедим. Им давать сила сам Юм Симиль.";
			link.l1 = "Опять нежить? Да что же это такое...";
			link.l1.go = "Tuttuat_24";
		break;
		
		case "Tuttuat_24":
			dialog.text = "Чему твоя удивляться, белый капитан? Юм Симиль - бог смерти, нефритовый череп Юм Симиль давать власть над живые и мертвые. С амулет твоя суметь пройти храм, оставить там череп, потом найти Калеуче, победить его капитан и забрать амулет, который он у тебя отобрать.";
			link.l1 = "А зачем капитану Калеуче нужны эти амулеты?";
			link.l1.go = "Tuttuat_25";
		break;
		
		case "Tuttuat_25":
			dialog.text = "Моя думать, что он хотеть попасть в храм люди-ягуары, и думать, что амулет помочь ему в поход туда. Но моя может ошибаться. Однако Калеуче всегда привлекать артефакты мой земля. Он плавать у берега остров с храм люди-ягуары, плавать у берега моя родина.";
			link.l1 = "И где же находится этот остров?";
			link.l1.go = "Tuttuat_26";
		break;
		
		case "Tuttuat_26":
			dialog.text = "Сначала твоя найти череп Юм Симиль и амулеты. Потом мы говорить об остров.";
			link.l1 = "Хорошо. Ты не дашь подсказку, где искать нефритовый череп?";
			link.l1.go = "Tuttuat_27";
		break;
		
		case "Tuttuat_27":
			dialog.text = "Моя не знать. Но он здесь, на Карибы. Как и амулеты. Искать. Спрашивать. Найти.";
			link.l1 = "Эх... Ладно, буду пробовать.";
			link.l1.go = "Tuttuat_28";
		break;
		
		case "Tuttuat_28":
			dialog.text = "Твоя быть осторожен, белый капитан. Калеуче чувствовать чавинский предметы. Когда твоя получить амулет, он твоя искать. Если найти - твоя бежать от него. Если он твоя настигнуть - второй раз твоя не выжить.";
			link.l1 = "Его проклятый корабль летит по ветру, как птица!.. Он раза в два быстрее всех кораблей, которые я только видел.";
			link.l1.go = "Tuttuat_29";
		break;
		
		case "Tuttuat_29":
			dialog.text = "Калеуче под проклятие - он сильно быстро двигаться. Трудно убежать. Твоя должен быть на корабль, который суметь уйти от Калеуче. Иначе твоя погибать. Как только твоя найти амулет - сразу везти его моя. Не возить амулет на корабль.";
			link.l1 = "Да это я уже понял. Хорошо, великий шаман. Спасибо за рассказ. Мне пора идти.";
			link.l1.go = "Tuttuat_31";
		break;
		
		case "Tuttuat_31":
			dialog.text = "Моя будет призывать духи твоя в помощь, чтобы они помочь спасти твоя от Калеуче.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_32";
		break;
		
		case "Tuttuat_32":
			DialogExit();
			LocatorReloadEnterDisable("Shore27", "boat", false);
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "mayak"; 
			AddQuestRecord("Caleuche", "6");
		break;
		
		case "Tuttuat_33":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("Вы отдали амулет");
			PlaySound("interface\important_item.wav");
			dialog.text = "(смотрит) Да, это он. Второй амулет чавинцы. Твоя молодец. Твоя нужно найти ещё один амулет.";
			link.l1 = "Я помню, шаман. Скоро он будет у тебя.";
			link.l1.go = "Tuttuat_34";
		break;
		
		case "Tuttuat_34":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
			AddQuestRecord("Caleuche", "22");
			if (!Caleuche_CheckAmulet())
			{
				if (GetCharacterIndex("Map_Caleuche") != -1)
				{
					sld = characterFromId("Map_Caleuche");
					sld.lifeday = 0;
					Map_ReleaseQuestEncounter("Map_Caleuche");
				}
			}
		break;
		
		case "Tuttuat_35":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Идти, белый человек. Найти ещё один амулет.";
				link.l1 = "Он уже у меня, великий шаман. Вот, смотри.";
				link.l1.go = "Tuttuat_36";
			}
			else
			{
				dialog.text = "Идти, белый человек. Найти ещё один амулет.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_35_1";
			}
		break;
		
		case "Tuttuat_35_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
		break;
		
		case "Tuttuat_36":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("Вы отдали амулет");
			PlaySound("interface\important_item.wav");
			dialog.text = "(смотрит) Да, это он. Третий амулет чавинцы. Твоя молодец. Твоя найти все нужный амулет, чтобы пройти через чавинави, слуги Юм Симиль, мертвый воины-ягуары.";
			link.l1 = "Теперь, как я понимаю - дело за нефритовым черепом?";
			link.l1.go = "Tuttuat_37";
		break;
		
		case "Tuttuat_37":
			dialog.text = "Твоя говорить правильно. Нефритовый череп Юм Симиль. Твоя должен отвезти его храм чавинцы. Тогда Калеуче терять свой сила навеки.";
			link.l1 = "Туттуатхапак, подскажи - где его искать? У тебя есть хоть какие-то предположения?";
			link.l1.go = "Tuttuat_38";
		break;
		
		case "Tuttuat_38":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "Нет. Твоя думать, где твоя последний раз видеть нефритовый череп. Кому отдать. Туда начать поиски.";
				link.l1 = "Хорошо, великий шаман. Я сделаю всё, что в моих силах.";
				link.l1.go = "Tuttuat_39";
			}
			else
			{
				dialog.text = "Череп Юм Симиль интересовать один белый колдун. Он его искать. Быть даже наш деревня. Моя слышать, что колдун жить в хижина на остров голландцы. Искать белый колдун на остров голландцы, и твоя мочь узнать что-то.";
				link.l1 = "Хорошо, великий шаман. Я сделаю всё, что в моих силах.";
				link.l1.go = "Tuttuat_39";
			}
		break;
		
		case "Tuttuat_39":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
			AddQuestRecord("Caleuche", "23");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul")) sTemp = "Начну с посещения Кюрасао - именно там я продал нефритовый череп Жоакиму Мерриману.";
			else sTemp = "Туттуатхапак сообщил, что нефритовым черепом интересовался какой-то 'белый колдун' и посоветовал искать на голландских островах. Кто бы это мог быть?";
			AddQuestUserData("Caleuche", "sText", sTemp);
			if (GetCharacterIndex("Map_Caleuche") != -1)
			{
				sld = characterFromId("Map_Caleuche");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter("Map_Caleuche");
			}
			pchar.questTemp.Caleuche = "skul";
			pchar.quest.Caleuche_villemstad.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstad.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Caleuche_villemstad.function = "Caleuche_CreateMonk";
		break;
		
		case "Tuttuat_40":
			dialog.text = "Идти, белый человек. Найти нефритовый череп Юм Симиль.";
			if (pchar.questTemp.Caleuche == "island")
			{
				link.l1 = "Он у меня, великий шаман. Взгляни.";
				link.l1.go = "Tuttuat_45";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Tuttuat_40_1";
			}
		break;
		
		case "Tuttuat_40_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_41":
			dialog.text = "Идти, белый человек. Найти нефритовый череп Юм Симиль.";
			link.l1 = "Боюсь, что мне не удастся этого сделать. Я нашёл колдуна, но в самый последний момент он выскользнул у меня из рук вместе с нефритовым черепом. Где он теперь - не имею даже малейшего представления.";
			link.l1.go = "Tuttuat_42";
		break;
		
		case "Tuttuat_42":
			dialog.text = "Очень плохо, белый человек. Теперь твоя не суметь пройти храм, не суметь победить Калеуче. Моя не сделать тебе подарок. Твоя уходить.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_43";
		break;
		
		case "Tuttuat_43":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_44";
		break;
		
		case "Tuttuat_44":
			dialog.text = "Твоя уходить, белый человек.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_44_1";
		break;
		
		case "Tuttuat_44_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_45":
			dialog.text = "(смотрит) Да, это он. Очень красивый. Но и очень страшный.";
			link.l1 = "Это точно... Но вот что интересно: я пересёк с нефритовым черепом всё Карибское море, от Кубы до Доминики, и Калеуче даже не попытался напасть. Я его вовсе не видел! Когда же я вёз тебе амулеты, этот чёртов призрак буквально загонял меня...";
			link.l1.go = "Tuttuat_46a";
		break;
		
		case "Tuttuat_46a":
			dialog.text = "Моя полагать - Калеуче бояться череп. Другой объяснение у моя нет. Наверное Юм Симиль сделать нефритовый череп смертельно опасный для капитан Калеуче, кроме основной проклятье. Наверно по этой причине капитан так хотеть захватить три амулеты предки мой народ, получить мудрость и научить своя управлять заклятье Юм Симиль...";
			link.l1 = "Получается - пока нефритовый череп у меня на судне, я могу не бояться атак Калеуче?";
			link.l1.go = "Tuttuat_46b";
		break;
		
		case "Tuttuat_46b":
			dialog.text = "Получаться, так, бледнолицый. Твоя сам убедиться это.";
			link.l1 = "Очень хорошо! Значит, я могу взять под командование корабль помощнее, и набрать побольше экипажа, чтобы устроить этому ходячему мертвяку достойный приём, когда заклятие спадёт с него, не опасаясь, что он перехватит меня раньше...";
			link.l1.go = "Tuttuat_46c";
		break;
		
		case "Tuttuat_46c":
			dialog.text = "";
			link.l1 = "...кстати, о заклятии. Куда я теперь должен отнести нефритовый череп?";
			link.l1.go = "Tuttuat_46";
		break;
		
		case "Tuttuat_46":
			dialog.text = "Твоя должен отнести его в храм чавинцы и завершить свой путь. Моя рассказать твоя немного, твоя готов слушать, белый человек?";
			link.l1 = "Мои уши всегда открыты для твоих слов, Туттуатхапак.";
			link.l1.go = "Tuttuat_47";
		break;
		
		case "Tuttuat_47":
			dialog.text = "Как говорить сказания моя предки, великий вождь чавинцы давным-давно, когда бледнолицый люди ещё не ступать на наш земля, построить большой-большой каноэ и отправить его с отряд воины в край многий острова. Отряд возглавлять сын великий вождь, также там быть и один из важный шаман. Они найти в край многий острова пустынный земля, высадить там, построить селение и большой храм Юм Симиль, какой уметь строить только наш древний предки\nНазад с благая весть об этом вернуться гонцы, но более никто не видеть ни сын вождь, ни важный шаман, ни воины. Остаться легенда, что они так и жить на этот остров, но самый мудрый из шаман предки говорить с духи и объявить, что на тот земля уже нет живой люди и над остров властвовать Юм Симиль\nКрай многий острова - это Карибы, белый человек. Храм Юм Симиль есть на один из остров, где не жить ни белый, ни индеец. Только слуги Юм Симиль, чавинави, всегда охранять пустынный коридоры храм.";
			link.l1 = "И где же находится этот остров?";
			link.l1.go = "Tuttuat_48";
		break;
		
		case "Tuttuat_48":
			dialog.text = "Из сказание моя понимать, что он малый, и находиться от остров с эта деревня по направление, который бледнолицые зовут 'север', на край великий вода, который твои братья звать 'океан'.";
			link.l1 = "Хм. На север от Доминики на границе с океаном? Чёрт возьми, да это же огромный участок моря! Как там искать маленький островок, о котором до сих пор никто не слышал?";
			link.l1.go = "Tuttuat_49";
		break;
		
		case "Tuttuat_49":
			dialog.text = "Моя не может быть точнее в указание этот остров. Но моя знать ещё один история. Твоя тоже мог слышать её от твоя братья. Около двадцати зим тому назад тот остров найти и посетить белый человек. Вместе с женщина и старик он проникнуть в храм Юм Симиль и унести оттуда шар восходящий солнце - могучий артефакт. У берега остров на корабль тот бледнолицый напасть Калеуче\nБледнолицый оказаться хитрый и ослепить капитан и команда Калеуче, направив на тот шар восходящий солнце. Проклятие Калеуче ослабеть и бледнолицый капитан суметь потопить его, но шар восходящий солнце раствориться навеки. Если твоя суметь найти этот бледнолицый - он рассказать твоя, где остров.";
			if (CheckAttribute(pchar, "questTemp.NatanStory")) link.l1 = "Ха! Кажется, я знаю, кто этот бледнолицый... Уж больно истории похожие. Калеуче был потоплен?";
			else link.l1 = "Хм. Так Калеуче был потоплен?";
			link.l1.go = "Tuttuat_50";
		break;
		
		case "Tuttuat_50":
			dialog.text = "Да, быть потоплен, но проклятие охранить их от смерть, и они починить свой корабль и снова отправиться в свой вечный поход.";
			link.l1 = "Так, ладно, с островом понятно, но что я должен делать в храме? Куда положить череп? Как справиться с воинами-ягуарами, которые его охраняют? Если это такие же чавинави, которых призывал этот колдун Мерриман, то лучше туда даже не соваться - они сильны, как десять солдат.";
			link.l1.go = "Tuttuat_51";
		break;
		
		case "Tuttuat_51":
			dialog.text = "Не такие же. Чавинави, который смог призвать белый колдун при помощь череп, намного слабей тех, который призывать сам Юм Симиль. Твоя даже не суметь нанести им урон, а они убить один удар.";
			link.l1 = "Постой, а как же тогда тот бледнолицый прошёл в храм и похитил артефакт?";
			link.l1.go = "Tuttuat_52";
		break;
		
		case "Tuttuat_52":
			dialog.text = "До прихода первый бледнолицый в храм его охранять духи мёртвый воины-предки, который когда-то прийти туда в далекий время. Бледнолицый суметь победить их - он быть сильный воин. Когда шар восходящий солнце быть украден, Юм Симиль разгневаться. Он наслать на бледнолицый кара огонь и земля, и чуть не разрушить храм, но бледнолицый суметь убежать вместе с артефакт. Теперь Юм Симиль призвать для охрана храм непобедимый воины-ягуары.";
			link.l1 = "Просто замечательно! И как же я туда теперь пройду?";
			link.l1.go = "Tuttuat_53";
		break;
		
		case "Tuttuat_53":
			dialog.text = "Моя помогать, белый человек. Моя дать два амулет чавинцы, который твоя мне принести. Моя беседовать с духи предки и зарядить амулет сила. Когда твоя надеть амулет, твоя суметь драться с воины-ягуары как с очень сильный, но обычный солдат. Амулет защитить твоя и наделить твоя оружие сила, способный нанести урон чавинави из храм.";
			link.l1 = "Ты уверен, что амулеты помогут мне?";
			link.l1.go = "Tuttuat_54";
		break;
		
		case "Tuttuat_54":
			dialog.text = "Моя знать. Моя говорить с предки. Моя великий шаман. Твоя верить мне. У твоя быть два амулет с собой. Один - защищать, второй - давать сила оружие. Один амулет твоя должен одеть. Какой - выбирать сам. Если на тебе не быть одет амулет - твоя погибнуть от палица воин-ягуар\nИ твоя помнить, что как только наступить полночь, Юм Симиль оживить все воины-ягуары, которых твоя убить. Твоя должен рассчитать время так, чтобы не сражаться с чавинави снова.";
			link.l1 = "Ясно.";
			link.l1.go = "Tuttuat_55";
		break;
		
		case "Tuttuat_55":
			dialog.text = "Твоя брать амулет. Вот они. Но твоя помнить, что сила амулет не быть вечна, и иссякнуть через один луна. Твоя помнить, моя говорить - твоя не суметь удержать сила амулет? Только великий шаман наш племя уметь это.";
			link.l1 = "Помню. Значит, у меня одна луна? Один месяц?";
			link.l1.go = "Tuttuat_56";
		break;
		
		case "Tuttuat_56":
			dialog.text = "Да. Когда твоя прийти в храм Юм Симиль, твоя должен найти святилище, а в нём - великий статуя кондор. Это самый важный место храм. Туда положить нефритовый череп Юм Симиль и проклятие падёт с Калеуче. И когда он снова напасть на твоя - твоя суметь победить его, как он быть обычный человек. А потом принести моя амулет, который он отнять у твоя, и получить награда.";
			link.l1 = "Кондор? Что это?";
			link.l1.go = "Tuttuat_57";
		break;
		
		case "Tuttuat_57":
			dialog.text = "Кондор - это большой птица, живущий горы мой родина. В память о родина, предки возвести в святилище великий статуя кондор.";
			link.l1 = "Ну что же, буду искать...";
			link.l1.go = "Tuttuat_58";
		break;
		
		case "Tuttuat_58":
			dialog.text = "Твоя быть осторожен. Кроме воины-ягуары, твоя найти в храм другой опасность.";
			link.l1 = "Какая опасность?";
			link.l1.go = "Tuttuat_59";
		break;
		
		case "Tuttuat_59":
			dialog.text = "Моя точно не знать. Твоя увидеть сам. Это мочь быть коварный ловушка. Или обман, чтобы запутать твоя. В святилище твоя пройти нелегко. Вход наверняка быть запечатан, и твоя должен суметь открыть его. Моя предки быть не только великий воин и шаман, но и великий строитель.";
			link.l1 = "Эх! Звучит пугающе, но где моя не пропадала! Не буду терять времени и выхожу в море!";
			link.l1.go = "Tuttuat_60";
		break;
		
		case "Tuttuat_60":
			dialog.text = "Ступать, белый воин. Моя призывать духи в помощь твоя в битва против воины-ягуары и Калеуче.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_61";
		break;
		
		case "Tuttuat_61":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
			Log_Info("Вы получили два амулета");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "kaleuche_amulet2");
			GiveItem2Character(pchar, "kaleuche_amulet3");
			// преобразуем амулеты
			ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_sword");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_shield");
			sld = ItemsFromID("kaleuche_amulet2");
			sld.picIndex = 13;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			sld = ItemsFromID("kaleuche_amulet3");
			sld.picIndex = 14;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			SetFunctionTimerCondition("Caleuche_TuttuatAmuletOver", 0, 0, 30, false); // таймер
			// делаем доступным Хаэль Роа
			n = FindIsland("KhaelRoa");
			Islands[n].visible = true;
			Island_SetReloadEnableGlobal(Islands[n].id, true);
			Islands[n].reload.l1.radius = 150.0;
			Islands[n].reload.l2.label = "Shore64_1";
			Islands[n].reload.l2.name = "reload_2";
			Islands[n].reload.l2.go = "";
			Islands[n].reload.l2.emerge = "";
			Islands[n].reload.l2.radius = 0.0;
			Islands[n].reload.l2.pic = 0;
			Islands[n].reload.l2.tex = "t1";
			pchar.questTemp.Caleuche = "khaelroa";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1 = "location";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1.location = "KhaelRoa_port";
			pchar.quest.Caleuche_khaelroa_arrive.function = "Caleuche_KhaelRoaArrive";
			AddQuestRecord("Caleuche", "34");
			if (CheckAttribute(pchar, "questTemp.NatanStory"))
			{
				pchar.questTemp.Caleuche.NatanInfo = "true";
				AddQuestUserData("Caleuche", "sText", "Но у меня есть зацепка: похоже, что белый капитан, побывавший в храме чавинцев, не кто иной, как мой добрый друг Натаниэль Хоук. Он говорил, что в Марун-Тауне у него есть карта этого острова. Надо навестить Натана.");
			}
			else AddQuestUserData("Caleuche", "sText", "Просто огромный кусок морского пространства, но делать нечего: надо прочесать указанный район.");
		break;
		
		case "Tuttuat_62":
			if (pchar.questTemp.Caleuche == "regard" && CheckCharacterItem(pchar, "kaleuche_amulet1") && CheckCharacterItem(pchar, "kaleuche_amulet2") && CheckCharacterItem(pchar, "kaleuche_amulet3")) 
			{
				dialog.text = "Моя говорить с духи. Твоя быть на остров в храм Юм Симиль. Ты найти Калеуче и амулет?";
				link.l1 = "Ты прав, великий шаман. Я нашёл остров, побывал в храме и оставил в нём нефритовый череп.";
				link.l1.go = "Tuttuat_63";
			}
			else
			{
				dialog.text = "Ступать, белый воин.";
				if (CheckAttribute(pchar, "questTemp.Caleuche.AmuletOver"))
				{
					link.l1 = "Туттуатхапак, тут такое дело... Я не успел отнести нефритовый череп в храм, а твои амулеты потеряли силу...";
					link.l1.go = "Tuttuat_82";
				}
				else
				{
					link.l1 = "...";
					link.l1.go = "Tuttuat_62_1";
				}
			}
		break;
		
		case "Tuttuat_62_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
		break;
		
		case "Tuttuat_63":
			pchar.quest.Caleuche_TuttuatAmuletOver.over = "yes"; //снять таймер
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet2")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet3")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "Твоя снять проклятие с Калеуче. Он найти твоя после этого?";
			link.l1 = "Да. Мы встретились прямо у острова. Я вступил с ним в бой и победил его. Теперь все три амулета у меня. Возьми их.";
			link.l1.go = "Tuttuat_64";
		break;
		
		case "Tuttuat_64":
			RemoveItems(pchar, "kaleuche_amulet1", 1);
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("Вы отдали три чавинских амулета");
			PlaySound("interface\important_item.wav");
			dialog.text = "Твоя большой и сильный воин, бледнолицый. Туттуатхапак не любить белый человек. Но моя уважать храбрый и умелый воин. Твоя сделать славный дело - избавить море от Калеуче. Твоя принести мне три амулет. Моя вознаградить твоя.";
			link.l1 = "Ты обещал что-то насчёт 'силы, которую я смогу удержать'?";
			link.l1.go = "Tuttuat_65";
		break;
		
		case "Tuttuat_65":
			dialog.text = "Твоя говорить правда. Я дать тебе этот сила. Никто на Карибы не знать секрет растения, который знать моя. Слушать же моя, бледнолицый! На мой родина расти целебный трава. Мы называть её 'мангароса'. Твоя слышать про такой трава?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa.Tell"))
			{
				link.l1 = "Да. Я держал в руках эту траву. Ей очень интересуются цыганки. А одна из них, знахарка Амелия, даже умеет делать из неё...";
				link.l1.go = "Tuttuat_66";
			}
			else
			{
				link.l1 = "Нет.";
				link.l1.go = "Tuttuat_66_1";
			}
		break;
		
		case "Tuttuat_66":
			dialog.text = "Моя слышать про травница с имя Амелия. Она мало уметь. Она не знать тайны мангароса. Только великий шаман моя родина, откуда на Карибы попасть этот трава, уметь раскрыть её истинный сила.";
			link.l1 = "Что за сила?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_66_1":
			dialog.text = "Этот трава расти на моя родина, но также встречаться и на Карибы. Это светло-зелёный высокий растение, с листья, как растопыренный пальцы ладонь, с приятный запах. Твоя легко узнать этот трава и не спутать его ни с чем. Моя знать тайный секреты этот трава и извлечь из она сила.";
			link.l1 = "Что за сила?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_67":
			dialog.text = "Моя уметь готовить из мангароса зелья. Очень сильный зелья, никто на Карибы, кроме моя, не уметь делать такой. Моя зелья делать человек навсегда сильней, ловчей, зорче, устойчивей, умней, красивей и удачливей. Моя сварить для твоя три зелье.";
			link.l1 = "Очень интересно!";
			link.l1.go = "Tuttuat_68";
		break;
		
		case "Tuttuat_68":
			dialog.text = "Твоя - великий воин, поэтому твоя нужней всего зелье, который повысит твой реакция в бой и выносливость в поход. А третий зелье твоя выбрать сам, когда моя сварить два первых. Но твоя должен принести для эти зелья мангароса, так как у моя её нет.";
			link.l1 = "Где лучше искать мангаросу?";
			link.l1.go = "Tuttuat_69";
		break;
		
		case "Tuttuat_69":
			dialog.text = "Мангароса - редкий трава на Карибы. Расти там, где мало люди ходить. Бестолковый люди срывать этот трава, сушить и курить её. Это великий глупость. Искать джунгли и бухты, укромный места, где не ходить глупый люди. Смотреть внимательней. На каждый зелье моя нужно пять стебель мангароса.";
			link.l1 = "Хорошо, великий шаман. Как только я отыщу достаточно мангаросы - я приду к тебе.";
			link.l1.go = "Tuttuat_70";
		break;
		
		case "Tuttuat_70":
			dialog.text = "Ступать, белый воин. Принести мангароса. Твоя не пожалеть. Моя зелье - лучший зелье. Моя говорить духи, чтобы они помочь твоя в поиски.";
			link.l1 = "Спасибо. До встречи!";
			link.l1.go = "Tuttuat_71";
		break;
		
		case "Tuttuat_71":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			pchar.questTemp.Caleuche = "mangarosa";
			pchar.questTemp.Caleuche.Mangarosa = 0;
			AddQuestRecord("Caleuche", "41");
		break;
		
		case "Tuttuat_72":
			dialog.text = "Твоя принести пять стебель мангароса для зелье?";
			if (GetCharacterItem(pchar, "cannabis7") >= 5)
			{
				link.l1 = "Да. Вот пять растений, которые тебе нужны.";
				link.l1.go = "Tuttuat_73";
			}
			link.l2 = "Пока нет, великий шаман. Но я весь в поисках...";
			link.l2.go = "Tuttuat_72_1";
		break;
		
		case "Tuttuat_72_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
		break;
		
		case "Tuttuat_73":
			RemoveItems(pchar, "cannabis7", 5);
			switch (sti(pchar.questTemp.Caleuche.Mangarosa))
			{
				case 0:
					dialog.text = "Очень хорошо. Приходить завтра, когда солнце скрыться за деревья. Я сварить для твоя зелье, которое повысить твой реакция и ловкость.";
					link.l1 = "Хорошо, шаман. Я приду завтра вечером.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 1;
				break;
				
				case 1:
					dialog.text = "Очень хорошо. Приходить завтра, когда солнце скрыться за деревья. Я сварить для твоя зелье, которое повысить твой выносливость.";
					link.l1 = "Хорошо, шаман. Я приду завтра вечером.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 2;
				break;
				
				case 2:
					dialog.text = "Очень хорошо. Какой зелье твоя выбирать? Зелье сила, зоркость, ум, красота, удача?";
					link.l1 = "Зелье силы.";
					link.l1.go = "Tuttuat_77_1";
					link.l2 = "Зелье зоркости.";
					link.l2.go = "Tuttuat_77_2";
					link.l3 = "Зелье ума.";
					link.l3.go = "Tuttuat_77_3";
					link.l4 = "Зелье красоты.";
					link.l4.go = "Tuttuat_77_4";
					link.l5 = "Зелье удачи.";
					link.l5.go = "Tuttuat_77_5";
				break;
			}
		break;
		
		case "Tuttuat_74":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1 = "Timer";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.hour  = 19.0;
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.function = "Caleuche_MangarosaPotion";
		break;
		
		case "Tuttuat_75":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Potion"))
			{
				sTemp = "";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1) sTemp = " Он сделать твоя движение быстрей, и твоя суметь сражаться лучше тонкий изящный оружие.";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2) sTemp = " Он сделать твоя выносливей в долгий поход, и твоя суметь сражаться лучше острый сабля.";
				dialog.text = "Зелье готово, бледнолицый воин. Твоя взять он."+sTemp+"";
				link.l1 = "Спасибо, великий шаман.";
				link.l1.go = "Tuttuat_76";
			}
			else
			{
				dialog.text = "Пока ещё рано, белый человек. Твоя приходить позже. Не мешать моя.";
				link.l1 = "Хорошо...";
				link.l1.go = "Tuttuat_75_1";
			}
		break;
		
		case "Tuttuat_75_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
		break;
		
		case "Tuttuat_76":
			if (sti(pchar.questTemp.Caleuche.Mangarosa) > 2)
			{
				dialog.text = "Моя сварить твоя все зелье, что обещать. Ты стать сильней. Твоя доволен?";
				link.l1 = "Да, великий шаман. Твоя награда была достойной.";
				link.l1.go = "Tuttuat_78";
			}
			else
			{
				dialog.text = "Когда твоя найти ещё пять стебель мангароса - приносить моя. Моя сварить твоя ещё один зелье.";
				link.l1 = "Я обязательно принесу ещё травы. До встречи!";
				link.l1.go = "Tuttuat_77";
			}
		break;
		
		case "Tuttuat_77":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1)
			{
				GiveItem2Character(pchar, "kaleuche_amulet1");
				ChangeItemDescribe("kaleuche_amulet1", "itmdescr_kaleuche_amulet1_potion");
				sld = ItemsFromID("kaleuche_amulet1");
				sld.name = "itmname_kaleuche_amulet1_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
			}
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2)
			{
				GiveItem2Character(pchar, "kaleuche_amulet2");
				ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_potion");
				sld = ItemsFromID("kaleuche_amulet2");
				sld.name = "itmname_kaleuche_amulet2_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
			}
		break;
		
		case "Tuttuat_77_1":
			dialog.text = "Приходить завтра как обычно. Моя сварить зелье, который сделать твоя сильней, и твоя суметь сражаться лучше большой топор.";
			link.l1 = "Хорошо.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 31;
		break;
		
		case "Tuttuat_77_2":
			dialog.text = "Приходить завтра как обычно. Моя сварить зелье, который сделать твоя зорче, и твоя суметь попадать лучше из огненный оружие.";
			link.l1 = "Хорошо.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 32;
		break;
		
		case "Tuttuat_77_3":
			dialog.text = "Приходить завтра как обычно. Моя сварить зелье, который сделать твоя умней, и твоя суметь прятаться лучше от враги.";
			link.l1 = "Хорошо.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 33;
		break;
		
		case "Tuttuat_77_4":
			dialog.text = "Приходить завтра как обычно. Моя сварить зелье, который сделать твоя красивей, и твоя суметь убеждать люди лучше.";
			link.l1 = "Хорошо.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 34;
		break;
		
		case "Tuttuat_77_5":
			dialog.text = "Приходить завтра как обычно. Моя сварить зелье, который сделать твоя удачливей, и будет больше хороший случай твоя жизнь.";
			link.l1 = "Хорошо.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 35;
		break;
		
		case "Tuttuat_78":
			dialog.text = "Моя рад, что твоя доволен мой искусство, искусство великий шаман.";
			link.l1 = "Скажи, Туттуатхапак, а зачем тебе нужны были эти три амулета? Мне просто интересно...";
			link.l1.go = "Tuttuat_79";
		break;
		
		case "Tuttuat_79":
			dialog.text = "Твоя уже ощутить силу двух этих амулет. Моя с помощь духи придать им сила, а все три амулет вместе даровать великий шаман мудрость и просвещение древний предки моя народ, великий индейцы чавин.";
			link.l1 = "Ясно. Ладно, спасибо ещё раз за отличные зелья. Ты действительно великий шаман. А теперь мне пора идти. Прощай, Туттуатхапак.";
			link.l1.go = "Tuttuat_80";
		break;
		
		case "Tuttuat_80":
			dialog.text = "Прощай, белый воин. Больше твоя не искать встреча с моя. Моя удаляться постигать мудрость предки. Да помочь твоя духи в твоя дела!";
			link.l1 = "...";
			link.l1.go = "Tuttuat_81";
		break;
		
		case "Tuttuat_81":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			GiveItem2Character(pchar, "kaleuche_amulet3");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_potion");
			sld = ItemsFromID("kaleuche_amulet3");
			sld.name = "itmname_kaleuche_amulet3_potion";
			sld.groupID = SPECIAL_ITEM_TYPE;
			sld.picIndex = 15;
			sld.picTexture = "ITEMS_35";
			sld.price = 0;
			sld.Weight = 1.0;
			sld.reaction = sti(pchar.questTemp.Caleuche.Mangarosa);
			sld.ItemType = "SUPPORT";
			i = sti(sld.reaction);
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet"+i+"_potion");
			AddQuestRecord("Caleuche", "42");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			DeleteAttribute(pchar, "questTemp.Caleuche.Mangarosa");
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
		break;
		
		case "Tuttuat_82":
			Log_Info("Вы отдали амулеты");
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			dialog.text = "Твоя огорчить моя, бледнолицый. Моя провести целый ритуал с духи предки, чтобы дать сила эти амулет, а ты потратить она зря. Моя огорчен. Твоя ступать. Туттуатхапак больше нечего сказать твоя.";
			link.l1 = "Как всё неудачно вышло... Прощай, шаман.";
			link.l1.go = "Tuttuat_83";
		break;
		
		case "Tuttuat_83":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Caleuche", "43");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			sld = ItemsFromID("SkullAztec");
			sld.price = 10000;
		break;

		// капитан Калеуче
		case "CaleucheCap":
			PlaySound("Types\skel.wav");
			dialog.text = "Бесполезно, моряк. Ты не сможешь меня одолеть. А все мои матросы, которых вы положили на палубе, ещё до восхода солнца соберут свои кости и восстанут вновь. Нас нельзя убить, ибо смерть покинула нас.";
			link.l1 = "Чёрт возьми! Так вы живые или мертвецы? Наверное, живые, потому что покойники обычно лежат тихо и не машут саблями. Кто ты такой и зачем напал на моё судно?";
			link.l1.go = "CaleucheCap_1";
		break;
		
		case "CaleucheCap_1":
			PlaySound("Reef\reef_01.wav");
			dialog.text = "Я - Бальтазар де Кордес, капитан корабля 'Летящее сердце'. Жалкие трусы, не знающие обо мне ничего, называют меня Ван дер Декеном, капитаном 'Летучего Голландца'. Но это не имеет значения... У тебя есть амулет, который я сейчас заберу. Он нужен мне! Я чувствую его! Великий амулет чавинцев, один из трёх, наконец-то он будет моим! Склонись передо мной, смертный!";
			link.l1 = "Амулет? Аргх!..";
			link.l1.go = "CaleucheCap_2";
		break;
		
		case "CaleucheCap_2":
			PlaySound("Types\skel.wav");
			DialogExit();
			npchar.MultiFighter = 4.0;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(pchar, 10, true, "Caleuche_GhostshipGetOut");
		break;
		
		case "CaleucheCap_3":
			dialog.text = "Я не могу поверить!.. Как же давно я не испытывал боли и не видел собственной крови!..";
			link.l1 = "На сей раз ты проиграл, Бальтазар де Кордес. Я узнал твою историю. Нефритовый череп возвращён в храм чавинцев, и проклятие Юм Симиля не тяготеет над тобой и твоей командой. Больше ты не вернёшь своих матросов к жизни.";
			link.l1.go = "CaleucheCap_4";
		break;
		
		case "CaleucheCap_4":
			dialog.text = "Может, ты считаешь себя избавителем? Нет! Бальтазар де Кордес дорого продаст даже остатки своей жизни!";
			link.l1 = "Последний поход 'Летящего сердца' закончится тут, у Хаэль Роа. И ты не сможешь поднять своё судно с дна морского, как двадцать пять лет назад.";
			link.l1.go = "CaleucheCap_5";
		break;
		
		case "CaleucheCap_5":
			dialog.text = "Двадцать пять лет прошло... а словно это было вчера... Я до сих пор помню сияние шара, ослепившее нас и расколовшее мой корабль. Это было первое и единственное поражение, которое потерпел 'Летящее сердце' и Бальтазар де Кордес... Скрестим же шпаги, капитан! Смерть в бою легка и весела!";
			link.l1 = "...";
			link.l1.go = "CaleucheCap_6";
		break;
		
		case "CaleucheCap_6":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Caleuche_ChangeShip");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// --> // наш матрос на берегу
		case "on_coast":
			dialog.text = "Ну наконец-то вы очнулись, кэп... Как самочувствие?";
			link.l1 = "Чёрт возьми, что произошло? Аргх, голова раскалывается...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Когда мы зашли в капитанскую каюту, вы лежали на полу без движения. Ребята подхватили вас и потащили на наш корабль, и вовремя, потому что мертвецы, что валялись на палубе, начали подниматься и снова взялись за сабли\nПресвятая Дева и все святые угодники! Мы быстро обрубили лини и отчалили от их корабля, но далеко уйти не успели: костлявые всадили в нас залп бортовой батареи, и наше судно в один миг превратилось в щепки. А затем они подняли паруса и в миг скрылись за горизонтом\nКорабль наш затонул, а все, кто выжил, добрались на лодке до берега. Мы прихватили ваш капитанский рундук из каюты. Там ведь много чего важного, да?";
			link.l1 = "Очень много. Спасибо, ребята, век не забуду.";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Мы вытащили вас в лодку, а потом и на берег. А вы валялись, что тот мертвяк...";
			link.l1 = "Я в долгу перед вами. Сколько я здесь лежал без сознания?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Сутки. Мы промыли и перевязали ваши раны, влили в рот лекарства и ром. Вы поправитесь, кэп.";
			link.l1 = "Обещаю, что не умру. Хотя чувствую себя на редкость паршиво...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Не сомневаюсь... Это был 'Летучий Голландец', кэп? Почему они на нас напали? И почему сразу не сделали ни одного выстрела, а после абордажа потопили одним залпом?";
			link.l1 = "Их капитану нужен был амулет, по поводу которого я ходил к Туттуатхапаку, индейскому шаману. Поэтому они и не потопили нас сразу. А как только главный мертвец забрал амулет, они и расправились с нами... Жуть какая! Корабль с командой живых мертвецов! Поверить невозможно...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Вот мы и повстречались с 'Летучим Голландцем'. В первой же колонии я пойду в церковь,  поставлю свечу из чистого воска за чудесное спасение, и буду молиться...";
			link.l1 = "Я, пожалуй, тоже. Но сейчас я пойду назад в деревню карибов. Я должен всё рассказать Туттуатхапаку. Этот проклятый корабль напал на нас из-за амулета! Надеюсь, краснокожий дьявол сможет объяснить мне, зачем он понадобился мертвецам.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Хорошо. Но берегите себя - ваши раны до сих пор сочатся кровью.";
			link.l1 = "Я буду осторожен. Обещаю. И - спасибо за то, что не бросили меня!";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "Как мы могли, кэп! Да мы за вас в огонь и воду, и хоть тысячу мертвяков порвём!";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		
		// Фергус Хупер
		case "fergus":
			dialog.text = "Эй! Я ещё не собрал достаточное количество змеиных кож, чтобы продавать их тебе, так что отвали!";
			link.l1 = "Хм... Ты - Фергус Хупер?";
			link.l1.go = "fergus_1";
		break;
		
		case "fergus_1":
			dialog.text = "Нет, меня зовут Туттуатхапак, и я прокляну тебя, если ты немедленно не исчезнешь. Так что поторопись, а не то ты...";
			link.l1 = "...сойдёшь с ума, подожжёшь свой корабль, тебя прирежет собственная матросня и заберёт твои вещи, ты это хотел сказать?";
			link.l1.go = "fergus_2";
		break;
		
		case "fergus_2":
			sld = characterFromId(pchar.questTemp.Caleuche.Amuletmaster);
			dialog.text = "Кхарх... чёрт тебя побери, кто ты такой? Откуда...";
			link.l1 = "У нас с тобой есть общий друг, Фергус. Он сейчас работает смотрителем маяка. Его зовут "+GetFullName(sld)+". Он и поведал мне твою историю и отправил меня к тебе. А шамана карибов Туттуатхапака я знаю лично, так что твоя шутка не удалась. Послушай, я не хочу ссориться. Я хочу купить у тебя одну вещь, и это не змеиные кожи.";
			link.l1.go = "fergus_3";
		break;
		
		case "fergus_3":
			dialog.text = "Хо, так ты знаешь моего старинного приятеля! Как он там? Не скис от скуки на своём маяке? Присаживайся, моряк, выпей со мной!";
			link.l1 = "Извини, Фергус, у меня действительно мало времени. Послушай, мне нужен индейский амулет, один из тех, которые ваш покойный капитан вывез из глубин Мэйна вместе с Туттуатхапаком. Я хорошо заплачу за него, а ты избавишься от опасной вещи.";
			link.l1.go = "fergus_4";
		break;
		
		case "fergus_4":
			dialog.text = "Почему это - опасной? Я не заметил, чтобы он приносил какой-либо вред.";
			link.l1 = "Не заметил, потому что ты больше не выходишь в море. У меня тоже был такой амулет до недавнего времени. За ними охотится корабль-призрак.";
			link.l1.go = "fergus_5";
		break;
		
		case "fergus_5":
			dialog.text = "Ты серьёзно, приятель? Это на тебя так знакомство с Туттуатхапаком повлияло? Смотри, кэп, этот краснокожий демон сожрёт твой разум...";
			link.l1 = "Можешь мне не верить, я бы на твоём месте и сам бы себе не поверил. Но я готов поклясться на Библии, что не лгу. Я чудом выжил после встречи с Калеуче.";
			link.l1.go = "fergus_6";
		break;
		
		case "fergus_6":
			dialog.text = "Калеуче?";
			link.l1 = "Ну, 'Летучим Голландцем'. Неважно. Продай мне этот амулет. Он всё равно не приносит пользы, я знаю.";
			link.l1.go = "fergus_7";
		break;
		
		case "fergus_7":
			dialog.text = "Насчёт этого ты прав. Бесполезная красивая безделушка. Послушай, моряк, я бы продал её тебе без разговоров, но вот в чём беда: его у меня украли вместе с остальным скарбом из моей лачуги, пока я охотился в джунглях. И случилось это совсем недавно, чуть больше месяца назад. Так что ничем помочь не могу.";
			link.l1 = "Кто украл?";
			link.l1.go = "fergus_8";
		break;
		
		case "fergus_8":
			dialog.text = "Ты что, думаешь, я бы так просто сидел тут, если бы знал, какая мразь обчистила моё жилище? В окрестностях Белиза появилась шайка разбойников и воров, и у них есть свои осведомители в городе. Во всяком случае, так считает комендант. Уверен, что именно эти подонки и обокрали меня.";
			link.l1 = "Комендант знает о бандитах и ничего не предпринимает?";
			link.l1.go = "fergus_9";
		break;
		
		case "fergus_9":
			dialog.text = "Предпринимает он что-то, или нет - я не знаю. Но вещички мои - тю-тю, и твой амулет вместе с ними. Можешь поискать бандитов, глядишь, у кого в кармане и отыщешь своё сокровище. Вряд ли они кому-то смогли его продать, торгашам он точно не нужен.";
			link.l1 = "Ясно. Ладно, загляну к коменданту. Бывай, Фергус!";
			link.l1.go = "fergus_10";
		break;
		
		case "fergus_10":
			DialogExit();
			AddQuestRecord("Caleuche", "9");
			pchar.questTemp.Caleuche.Bandos = "start"; 
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		// бандит в городе
		case "Beliz_townbandos":
			dialog.text = "Эй! Чего тебе? Я гостей не жду. Давай, проваливай!";
			link.l1 = "А чего так невежливо, сударь? Я хотел спросить, вы не...";
			link.l1.go = "Beliz_townbandos_1";
		break;
		
		case "Beliz_townbandos_1":
			dialog.text = "Ты что, не слышал? Выметайся, или я сам выставлю тебя за дверь!";
			link.l1 = "Кхм... А может, ты и есть тот, кто мне нужен? Уж больно ты нервничашь, приятель...";
			link.l1.go = "Beliz_townbandos_2";
		break;
		
		case "Beliz_townbandos_2":
			dialog.text = "Самый умный, да? Последний раз повторяю: или ты сам уберёшься, или я позову стражу и тебя отправят хлебать баланду!";
			link.l1 = "Хлебать баланду? Как интересно... Я всё больше и больше убеждаюсь в том, что я нашёл того, кого искал. Хорошо, я согласен. Давай позовём сюда стражу, а потом вместе пройдём в комендатуру. Я как раз оттуда, так что дорогу я запомнил... Стра-ажа! Стра-ажа! Сюда!!";
			link.l1.go = "Beliz_townbandos_3";
		break;
		
		case "Beliz_townbandos_3":
			dialog.text = "Ах ты, ищейка легавая, сейчас я тебя на стальной вертел насажу!";
			link.l1 = "Ого! Ну, давай, попробуй!";
			link.l1.go = "Beliz_townbandos_4";
		break;
		
		case "Beliz_townbandos_4":
			DialogExit();
			DeleteAttribute(npchar, "CityType");
			DeleteAttribute(npchar, "city"); // чтобы не было НЗГ
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_BelizTownbandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.Caleuche_letter.win_condition.l1 = "item";
			pchar.quest.Caleuche_letter.win_condition.l1.item = "kaleuche_letter";
			pchar.quest.Caleuche_letter.function = "Caleuche_FindLetter";
		break;
		
		// главарь лесных бандосов
		case "Beliz_forestbandos":
			dialog.text = "Эй, путник! Ха-ха-ха, добро пожаловать к нашему огоньку... Ужин, ночлег - пожалуйста, но за это придётся раскошелиться. А ну, готовься выворачивать карманы!";
			link.l1 = "Не торопись, приятель. Я к тебе пришёл по делу.";
			link.l1.go = "Beliz_forestbandos_1";
		break;
		
		case "Beliz_forestbandos_1":
			dialog.text = "По делу? Ха-ха-ха, твоё дело - отдать мне всё своё золотишко и серебришко, вот что!";
			link.l1 = "Хватит уже зубоскалить. Я принёс письмо из Белиза, которое ты наверняка ждёшь. Посыльный не поладил со стражей, вот и доверил мне дело.";
			link.l1.go = "Beliz_forestbandos_2";
		break;
		
		case "Beliz_forestbandos_2":
			dialog.text = "А ну, покажи!";
			link.l1 = "Держи...";
			link.l1.go = "Beliz_forestbandos_3";
		break;
		
		case "Beliz_forestbandos_3":
			Log_Info("Вы отдали записку");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "kaleuche_letter", 1);
			dialog.text = "(читает) Хм... странно всё это. Каким боком ты при делах оказался?";
			link.l1 = "Говорю же - замели братишку вашего, вот я и подвизался его работёнку выполнить. Денежек он посулил, сказал - не обидят кореша, накормят, обогреют, встретят ласково...";
			link.l1.go = "Beliz_forestbandos_4";
		break;
		
		case "Beliz_forestbandos_4":
			dialog.text = "Встретят ласково? Ладно, дружок, и обогреем тебя, и накормим, и приласкаем, и монет не пожалеем. Но и ты докажешь нам, что не ищейка легавая. Мы как раз на дело собираемся\nВ бухте недалече высадился купец, намерен он тайком в город проникнуть и товар кой-какой тихонько мимо таможни протащить. Вот мы с него пошлину-то и удержим. Пойдёшь с нами. Сабельку-то знаешь с какого конца держать?";
			link.l1 = "А доля с этой пошлины мне причитаться будет?";
			link.l1.go = "Beliz_forestbandos_5";
		break;
		
		case "Beliz_forestbandos_5":
			dialog.text = "Долю свою получишь, коли храбрость проявишь и жив останешься. Но не надейся, что будет легко - купец не один идёт, а с конвоем. И в путь нам уже пора - добыча на подходе. Ребята! Заряжай пистоли! Выступаем!";
			link.l1 = "...";
			link.l1.go = "Beliz_forestbandos_6";
		break;
		
		case "Beliz_forestbandos_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LocatorReloadEnterDisable(pchar.location, "reload2_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload3_back", true);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Beliz_forestbandos_"+i);	
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Beliz_ExitTown", "goto", "goto"+(rand(1)+1), "", 10.0);
			}
			DoQuestCheckDelay("OpenTheDoors", 12.0);
			pchar.quest.Caleuche_bandosrobb.win_condition.l1 = "location";
			pchar.quest.Caleuche_bandosrobb.win_condition.l1.location = "Beliz_ExitTown";
			pchar.quest.Caleuche_bandosrobb.function = "Caleuche_JungleBandosRobbery";
		break;
		
		case "Beliz_forestbandos_7":
			dialog.text = "А ты не трус, как я посмотрю. Молодец! Свою долю ты честно заработал. Как предпочитаешь: деньгами, или товаром?";
			link.l1 = "Деньгами.";
			link.l1.go = "Beliz_forestbandos_8_1";
			link.l2 = "Товаром.";
			link.l2.go = "Beliz_forestbandos_8_2";
		break;
		
		case "Beliz_forestbandos_8_1":
			Log_Info("Вы получили 100 дублонов");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Получай! И ещё возьми кошелёк за доставку письма.";
			link.l1 = "Благодарствую! Вот почаще бы так!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_8_2":
			Log_Info("Вы получили 30 бутылок рома");
			Log_Info("Вы получили 12 бутылок вина");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "potionrum", 30);
			TakeNItems(pchar, "potionwine", 12);
			dialog.text = "Получай! Не упейся до смерти, ха-ха-ха! И ещё возьми кошелёк за доставку письма.";
			link.l1 = "Благодарствую! Вот почаще бы так!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_9":
			Log_Info("Вы получили кошель");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "purse2", 1);
			dialog.text = "Ты кажешься мне неплохим парнем. Хочешь ещё пойти на дело? Как раз на то, весть о котором ты мне доставил?";
			link.l1 = "Конечно!";
			link.l1.go = "Beliz_forestbandos_10";
		break;
		
		case "Beliz_forestbandos_10":
			dialog.text = "Тогда приходи к пещере. Тут их две. Пройди в джунгли туда, где мы с тобой встретились, и топай по тропинке налево. Сбор через три дня у входа в пещеру, с полуночи до часу. Усёк? Хорошо себя покажешь - возьмём в нашу шайку. И смотри, не вздумай трепаться в городе - мигом порешим. У меня руки длинные.";
			link.l1 = "Что ты меня стращаешь, я всё понимаю, не маленький. Буду нем, как рыба. А через три дня жди меня - я обожаю легкие деньги!";
			link.l1.go = "Beliz_forestbandos_11";
		break;
		
		case "Beliz_forestbandos_11":
			dialog.text = "Хорошо, фрайерок. А теперь проваливай, пока стража не явилась. Да и мы канаем отсюда.";
			link.l1 = "Бывай, приятель...";
			link.l1.go = "Beliz_forestbandos_12";
		break;
		
		case "Beliz_forestbandos_12":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload2_back", false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload3_back", false);
			LocatorReloadEnterDisable("Beliz_CaveEntrance_2", "reload1_back", true); // закрываем пещеру
			SetFunctionTimerCondition("Caleuche_CaveOpen", 0, 0, 1, false); // таймер
			SetFunctionTimerCondition("Caleuche_BelizbandosClear", 0, 0, 4, false); // таймер
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			for (i=1; i<=6; i++)
			{
				if (GetCharacterIndex("Beliz_forestbandos_"+i) != -1)
				{
					sld = characterFromId("Beliz_forestbandos_"+i);	
					LAi_SetActorType(sld);
					LAi_group_MoveCharacter(sld, "TMP_FRIEND");
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "OpenTheDoors", 20.0);
				}
			}
			AddQuestRecord("Caleuche", "13");
			// костер
			ref location = &Locations[FindLocation("Beliz_Jungle_01")];
			DeleteAttribute(location, "fire");
			sld = ItemsFromID("fire");
			sld.shown = false;
			// пакуем схрон в пещере
			pchar.GenQuestBox.Beliz_Cave_2 = true;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.kaleuche_amulet2 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.suit4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse1 = 7; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse2 = 3; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potion2 = 10;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potionrum = 55;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.indian_3 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.obereg_4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.berserker_potion = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry2 = 15;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry3 = 33;
			// меняем флаг
			pchar.questTemp.Caleuche.Bandos = "know";
			SaveCurrentQuestDateParam("questTemp.Caleuche.belizbandos");
		break;
		
		// спалили бандосы в пещере
		case "Beliz_cavebandos":
			dialog.text = "Ах, ты, скотина! Никак решил в наших вещичках покопаться и присвоить их себе? Это тебе даром не пройдёт, червяк!";
			link.l1 = "Ты кого червяком назвал, мразь?!";
			link.l1.go = "Beliz_cavebandos_1";
		break;
		
		case "Beliz_cavebandos_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Beliz_cavebandos_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Beliz_cavebandos_3", "citiz_23", "man", "man", 30, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 30, 70, 70, "blade_10", "pistol1", "bullet", 150);
				ChangeCharacterAddressGroup(sld, pchar.location, "monsters", "monster16");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_CaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// капитан гарпии
		case "reginald":
			dialog.text = "Приветствую, коллега! Какими судьбами у меня на борту?";
			link.l1 = TimeGreeting()+", минхер Джексон. Рад, что наконец-то нашёл тебя.";
			link.l1.go = "reginald_1";
		break;
		
		case "reginald_1":
			dialog.text = "'Минхер Джексон', ха-ха! Да, я, признаться, уже скоро сам себя так называть буду. Работаю без отдыха на эту чёртову Компанию, будь она неладна... но деньги платят хорошие, очень хорошие, разрази меня гром!.. По какому делу пожаловал?";
			link.l1 = "Наш общий знакомый, смотритель маяка, сообщил мне, что у тебя есть старинный индейский амулет. Тебе он наверняка так и не пригодился, а мне вот очень даже нужен. Я хочу купить его у тебя.";
			link.l1.go = "reginald_2";
		break;
		
		case "reginald_2":
			dialog.text = "А, та чудная штуковина, о которой я справлялся у этого отставного боцмана! Ты прав, приятель, он мне так и не пригодился.";
			link.l1 = "Сколько ты за него хочешь?";
			link.l1.go = "reginald_3";
		break;
		
		case "reginald_3":
			dialog.text = "Понимаешь, тут такая проблема... Сейчас объясню. У меня его с собой нет. Поскольку я так и не нашёл ему применения, я положил его в сундук на берегу на хранение с моими прочими вещичками.";
			link.l1 = "Тогда понятно, почему ты до сих пор... впрочем, неважно. Давай отправимся вместе к твоему сундучку, и я куплю амулет. Всё просто. Где он у тебя?";
			link.l1.go = "reginald_4";
		break;
		
		case "reginald_4":
			dialog.text = "Вот как раз и не просто. Сундук мой находится на Барбадосе, в башне маяка, и заперт на надёжный замок, чтобы любители пошариться, где ни попадя, не покопались в моих вещах. А отправиться на Барбадос я с тобой не могу - извини, дружище, у меня контракт с голландцами, и я должен курсировать между Филипсбургом и Порт-Роялем строго по графику, а Барбадос от этого маршрута - чёрти где.";
			link.l1 = "И что же нам сделать? Понимаешь, мне действительно очень нужен этот амулет.";
			link.l1.go = "reginald_5";
		break;
		
		case "reginald_5":
			dialog.text = "Хм... Ну, есть один вариант. Я даю тебе ключ от моего сундука, и ты сам двигаешь на Барбадос. Но ты должен будешь выплатить мне денежную компенсацию за все вещички, что находятся в нём. Ты уж извини за недоверие, но сам понимаешь - я тебя впервые вижу.";
			link.l1 = "Сколько?";
			link.l1.go = "reginald_6";
		break;
		
		case "reginald_6":
			dialog.text = "Пятьсот золотых монет. И дешевле я не уступлю.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 500)
			{
				link.l1 = "По рукам! Вот твоё золото.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Хм. У меня сейчас нет столько дублонов.";
			link.l2.go = "reginald_7";
		break;
		
		case "reginald_7":
			dialog.text = "Тогда приходи, когда соберёшь. Раз нашёл меня один раз - значит, найдёшь и второй. Я ещё долго буду ходить между Синт-Маартеном и Ямайкой.";
			link.l1 = "Хорошо. Договорились.";
			link.l1.go = "reginald_8";
		break;
		
		case "reginald_8":
			DialogExit();
			NextDiag.CurrentNode = "reginald_9";
			npchar.DeckDialogNode = "reginald_9";
		break;
		
		case "reginald_9":
			dialog.text = "Снова ты, дружище? Принёс пятьсот монет?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 500)
			{
				link.l1 = "Да. Вот твое золото.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Пока нет, но я работаю над этим.";
			link.l2.go = "reginald_8";
		break;
		
		case "reginald_10":
			Log_Info("Вы отдали 500 дублонов");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "gold_dublon", 500);
			dialog.text = "Вот и славно! А вот твой ключ. И у меня к тебе будет огромная просьба: после того, как заберёшь всё, что в сундуке, оставь ключ в замке. Неохота что-то делать новый замок для сундука и ключ к нему.";
			link.l1 = "Хорошо.";
			link.l1.go = "reginald_11";
		break;
		
		case "reginald_11":
			dialog.text = "Тогда удачи, дружище! Счастливого пути!";
			link.l1 = "И тебе того же, минхер Джексон.";
			link.l1.go = "reginald_12";
		break;
		
		case "reginald_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			DeleteAttribute(pchar, "questTemp.Caleuche.Garpiya");
			DeleteAttribute(pchar, "questTemp.Garpiya");
			GiveItem2Character(pchar, "kaleuche_key"); 
			AddQuestRecord("Caleuche", "20");
			// сундук со схроном
			i = Findlocation("Mayak2");
			Locations[i].models.always.locators = "lighthouse_Blocators";
			locations[i].private1.key = "kaleuche_key";
			locations[i].private1.key.delItem = true;
			locations[i].private1.items.kaleuche_amulet3 = 1;
			locations[i].private1.items.pistol9 = 1;
			locations[i].private1.items.indian_6 = 1;
			locations[i].private1.items.map_barbados = 1;
			locations[i].private1.items.map_part2 = 1;
			locations[i].private1.items.jewelry22 = 5;
			locations[i].private1.items.jewelry17 = 6;
			locations[i].private1.items.jewelry12 = 3;
			locations[i].private1.items.jewelry16 = 2;
			locations[i].private1.items.jewelry20 = 7;
			locations[i].private1.items.jewelry53 = 11;
			locations[i].private1.items.mineral25 = 1;
			locations[i].private1.items.mineral21 = 1;
			locations[i].private1.items.mineral22 = 5;
			locations[i].private1.items.mineral26 = 1;
			locations[i].private1.items.mineral10 = 1;
			locations[i].private1.items.mineral3 = 10;
			pchar.quest.caleuche_amulet3.win_condition.l1 = "item";
			pchar.quest.caleuche_amulet3.win_condition.l1.item = "kaleuche_amulet3";
			pchar.quest.caleuche_amulet3.function = "Caleuche_ThirdAmuletFind";
		break;
		
		// монах в Виллемстаде
		case "monk_caleuche":
			dialog.text = "Здравствуйте, капитан "+GetFullName(pchar)+". Рад вас приветствовать в Виллемстаде.";
			link.l1 = "Добрый день, святой отец. Не помню, чтобы мы были с вами знакомы.";
			link.l1.go = "monk_caleuche_1";
		break;
		
		case "monk_caleuche_1":
			dialog.text = "Я навёл о вас справки в портовом управлении, когда ваш корабль встал на рейд. И думаю, что вас я могу просить о помощи.";
			link.l1 = "Очень интересно. И почему же именно я?";
			link.l1.go = "monk_caleuche_2";
		break;
		
		case "monk_caleuche_2":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "Потому что вы много сделали для Республики Свободных Провинций. Вы на хорошем счету в Компании, дружны с губернатором. Я уже обращался во все инстанции и получил пренебрежительный отказ, но надеюсь, что столь благородный человек, как вы, прислушается к скромной просьбе служителя Господа.";
			}
			else
			{
				dialog.text = "Потому что вы не на службе у нашего губернатора, не служите в Компании и не имеете близких дел с военными нашей колонии. В противном случае вы бы наверняка отмахнулись от меня, как от назойливой мухи, поскольку со своей просьбой я уже обращался во все инстанции и получил пренебрежительный отказ.";
			}
			link.l1 = "Хорошо. Что за просьба?";
			link.l1.go = "monk_caleuche_3";
		break;
		
		case "monk_caleuche_3":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Напротив резиденции губернатора есть дом. Проживающая там горожанка не так давно сдавала комнату внаём очень подозрительному типу, не местному, и не голландцу. Так вот, настоятель нашей церкви, отец "+sld.name+", узнал его\nЭто Жоаким Мерриман, португалец, обвинённый инквизицией в колдовстве и связях с нечистой силой. Он скрылся от преследования инквизиторов в Новом Свете. Испанцы многих неугодных им людей причисляют к еретикам и обвиняют в колдовстве, дабы отправить на костёр инквизиции, но это... тут они правы. Мерриман - чёрный колдун\nТак вот. Прожив немного в Виллемстаде, он исчез так же внезапно, как и появился. А спустя некоторое время женщина, сдававшая комнату Мерриману, перестала выходить из дома. Совсем! И не выходит до сих пор\nПри этом по ночам на втором этаже дома иногда мерцает красно-синий свет и раздаются подозрительные звуки. Отец "+sld.name+" обратился к коменданту. Тот отправил патруль из четырёх солдат, они посетили дом и никого не обнаружили: ни хозяйки дома, ни посторонних, ни чего-либо подозрительного\nНо странности не закончились. Хозяйка так и не появилась, а по ночам наверху всё мерцает этот адский свет. Кроме того, исчезли двое нищих. Я слышал на паперти их беседу - прослышав, что дом стоит без хозяев, они в дождливый день решили переночевать в нём. Больше их никто не видел.";
			link.l1 = "Как я полагаю, ваша просьба будет заключаться в том, чтобы пойти в этот дом и посмотреть, что там творится?";
			link.l1.go = "monk_caleuche_4";
		break;
		
		case "monk_caleuche_4":
			dialog.text = "Именно так, благородный господин. Выступите на стороне святой церкви. Комендант считает, что мы несём чушь - ведь патруль ничего не обнаружил в доме. Губернатор придерживается того же мнения. Обычным горожанам или всё равно, так как нет никаких явных угроз, или страшно туда соваться.";
			link.l1 = "Хм... Идти придётся ночью?";
			link.l1.go = "monk_caleuche_5";
		break;
		
		case "monk_caleuche_5":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Да, минхер. Днём там все тихо. Очень вас прошу. Отец "+sld.name+" отблагодарит и вознаградит вас за службу. Как только побываете ночью в этом вертепе - расскажите ему, что вы там обнаружили. Уверяю вас, наши опасения имеют под собой почву.";
			link.l1 = "Ладно. Я подумаю над тем, что вы мне сказали.";
			link.l1.go = "monk_caleuche_6";
		break;
		
		case "monk_caleuche_6":
			dialog.text = "Спасибо, капитан. Надеюсь, вы не откажете в моей просьбе. Ради веры, ради Христа. Благословляю вас.";
			link.l1 = "...";
			link.l1.go = "monk_caleuche_7";
		break;
		
		case "monk_caleuche_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "none", "", "", "", -1);
			AddQuestRecord("Caleuche", "24");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul")) sTemp = "посетить дом моего старого знакомца Жоакима Мерримана, в котором, по его словам, по ночам творятся странные вещи. Вспоминая тот особенный блеск в глазах Мерримана, когда тот смотрел на нефритовый череп, мне становится жутковато. Как-то мне совсем не улыбается идти ночью в его бывшее обиталище.";
			else sTemp = "посетить дом напротив резиденции, в котором снимал комнату некий Жоаким Мерриман. Судя по всему, это и есть тот самый белый колдун, о котором сообщил Туттуатхапак. По словам монаха, по ночам в доме творятся странные вещи. Как-то мне совсем не улыбается идти ночью в бывшее обиталище колдуна.";
			AddQuestUserData("Caleuche", "sText", sTemp);
			i = Findlocation("Villemstad_town");
			DeleteAttribute(&locations[i], "reload.l14.close_for_night");
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1.location = "Villemstad_houseSp1_room";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2 = "Hour";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.start.hour = 1.00;
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.finish.hour = 3.00;
			pchar.quest.Caleuche_villemstadhouse.function = "Caleuche_CreateJoakimSkel";
		break;
		
		// охотник у пещеры
		case "cavehunter":
			dialog.text = "Постой, приятель. Лучше тебе туда не ходить, если жизнь дорога.";
			link.l1 = "А что там такое?";
			link.l1.go = "cavehunter_1";
		break;
		
		case "cavehunter_1":
			dialog.text = "Поверь, тебе лучше не знать. Но там, за поворотом - сама смерть, и я готов присягнуть на Библии, что живым ты оттуда не вернёшься.";
			link.l1 = "Ну раз так... то не буду понапрасну искушать судьбу. Спасибо за предупреждение.";
			link.l1.go = "cavehunter_2";
		break;
		
		case "cavehunter_2":
			dialog.text = "Не за что. Держись от этой тропы подальше.";
			link.l1 = "...";
			link.l1.go = "cavehunter_3";
		break;
		
		case "cavehunter_3":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_4":
			dialog.text = "Держись от этой тропы подальше, приятель.";
			link.l1 = "Я помню...";
			link.l1.go = "cavehunter_4_1";
		break;
		
		case "cavehunter_4_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_5":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Ты уверен, что хочешь пойти туда?";
			link.l1 = "Абсолютно. Меня прислал отец "+sld.name+", настоятель церкви Гаваны. Я должен выяснить, что здесь происходит, и принять адекватные меры.";
			link.l1.go = "cavehunter_6";
		break;
		
		case "cavehunter_6":
			dialog.text = "Что здесь происходит?! Боюсь, у тебя задрожат поджилки, как только ты увидишь своими глазами, что здесь происходит.";
			link.l1 = "Это ты сообщил о том, что в пещере замечены ходячие мертвецы?";
			link.l1.go = "cavehunter_7";
		break;
		
		case "cavehunter_7":
			dialog.text = "Да, я. И лучше тебе поверить моим словам.";
			link.l1 = "Я верю. Я лично столкнулся с одной такой нечистью в Виллемстаде и уничтожил её. И сейчас я пойду туда и вырежу всю пакость, которая засела в пещере.";
			link.l1.go = "cavehunter_8";
		break;
		
		case "cavehunter_8":
			int icpy = GetOfficersQuantity(pchar);
			switch (icpy)
			{
				case 0:
					dialog.text = "И ты намерен сделать это в одиночку? Ты покойник, приятель. Ты даже не представляешь, сколько их там. Ступай, а я отправлюсь в церковь ставить свечу тебе за упокой.";
					link.l1 = "Не спеши хоронить меня раньше времени. И не такое видали.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 1:
					dialog.text = "И вы намерены сделать это вдвоём? Боюсь, далеко вы не пройдёте. Вы даже не представляете, сколько их там. Это самоубийство.";
					link.l1 = "Ты нас плохо знаешь, дружище. Отойди-ка в сторону, а мы вычистим гнездо этой нечисти.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 2:
					dialog.text = "И вы намерены сделать это втроём? Наверное, вы хорошие бойцы, раз решились на такое. Но боюсь, вам всё равно не управиться. Вы даже не представляете, сколько их там в гроте.";
					link.l1 = "Ты нас плохо знаешь, дружище. Отойди-ка в сторону, а мы вычистим гнездо этой нечисти.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 3:
					dialog.text = "А вы, похоже, ребята не промах. Но вы даже не представляете, сколько их там. В этом деле лишних людей быть не может. Я иду с вами, чёрт возьми, и буду отстреливать эту мерзость из своего мушкета!";
					link.l1 = "Ты храбрый парень, дружище. Я не откажусь от твоей помощи. Вперёд!";
					link.l1.go = "cavehunter_9";
				break;
			}
		break;
		
		case "cavehunter_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		break;
		
		case "cavehunter_9":
			DialogExit();
			npchar.quest.caleuche = true;
			npchar.dialog.currentnode = "cavehunter_10";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			// закрываем локаторы выхода
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload1_back", true);
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload3_back", true);
		break;
		
		case "cavehunter_10":
			dialog.text = "Вперёд! Уничтожим проклятую нечисть!";
			link.l1 = "...";
			link.l1.go = "cavehunter_10_1";
		break;
		
		case "cavehunter_10_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_10";
		break;
		
		case "cavehunter_11":
			dialog.text = "Ух, вот это бойня была! Сколько же здесь мертвяков пряталось! Теперь можно жить спокойно... Расскажи обо всём, что тут произошло, настоятелю, который тебя сюда отправил. Очень надеюсь, что после твоего доклада этим наконец займётся инквизиция. В конце-концов, нечисть - это по её части.";
			link.l1 = "Обязательно расскажу. Спасибо за помощь, дружище. Ты настоящий солдат. Удачи!";
			link.l1.go = "cavehunter_exit";
		break;
		
		// солдат в крипте при провале
		case "cryptguard":
			dialog.text = "Стой! Туда вход воспрещён!";
			link.l1 = "Э-э... А что там такое?";
			link.l1.go = "cryptguard_1";
		break;
		
		case "cryptguard_1":
			dialog.text = "Здесь был обнаружен опасный колдун. Входить в эту дверь могут только святые отцы и солдаты, сопровождающие их.";
			link.l1 = "Ясно. Колдуна схватили?";
			link.l1.go = "cryptguard_2";
		break;
		
		case "cryptguard_2":
			dialog.text = "Я не уполномочен отвечать на такие вопросы, сеньор. Вам лучше уйти.";
			link.l1 = "Хорошо, я понял. Всего доброго.";
			link.l1.go = "cryptguard_3";
		break;
		
		case "cryptguard_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Caleuche", "31");
			CloseQuestHeader("Caleuche");
			pchar.questTemp.Caleuche = "end";
		break;
		
		// чавинави-вождь
		case "Chavinavi":
			PlaySound("VOICE\Russian\TopChavinavi-01.wav");
			dialog.text = "Стой, человек! Ты находишься в самом сердце храма, и ты зашёл слишком далеко, чтобы повернуть назад.";
			link.l1 = "Кто ты?!";
			link.l1.go = "Chavinavi_1";
		break;
		
		case "Chavinavi_1":
			dialog.text = "Я - вождь чавинави, хранитель оплота и страж священных чертог. Ты не первый, кто вошёл в храм, но до тебя лишь один человек побывал в этом запретном месте. И лишь поэтому я снисхожу до разговора с тобой. Зачем ты пришёл сюда, бледнолицый?";
			link.l1 = "Я принёс в этот храм древнюю реликвию - нефритовый череп. Пятьдесят лет назад он был вывезен из индейского храма далеко в глубине материка. Я намеревался найти святилище и вернуть череп вашему богу.";
			link.l1.go = "Chavinavi_2";
		break;
		
		case "Chavinavi_2":
			dialog.text = "Мне странно слышать эти слова из твоих уст. Я не верю тебе. Вы, бледнолицые, всегда и всюду приходите для того, чтобы что-то забрать, но никогда - чтобы отдать.";
			link.l1 = "Я не лгу. Вернув нефритовый череп, я сниму проклятие, наложенное на капитана корабля-призрака, который терроризирует Карибское море, да и не только, сделаю его смертным и навсегда избавлю землю от этой напасти.";
			link.l1.go = "Chavinavi_3";
		break;
		
		case "Chavinavi_3":
			dialog.text = "Откуда тебе ведомо, бледнолицый, что наш бог снимет проклятие с презренного вора? Кто сообщил тебе об этом? Разве наш бог говорит с тобой?";
			link.l1 = "Нет, но я пришёл сюда по подсказке шамана по имени Туттуатхапак. Как он утверждал, череп - ключ к снятию заклятия, а этот храм на Карибах - единственный. И знаешь что, сейчас мне кажется, что он действительно говорит с духами предков. Может быть, даже с тобой, вождь воинов-ягуаров.";
			link.l1.go = "Chavinavi_4";
		break;
		
		case "Chavinavi_4":
			dialog.text = "Твои слова удивляют меня, бледнолицый, но я не могу окончательно поверить в то, что ты не лжёшь. Если ты действительно пришёл в этот храм, чтобы вернуть нашу реликвию, то твой шаман наверняка тебе сообщил подробности об этом месте, его создании, истории и обитателях\nЕсли это так, то тебе не составит труда ответить на все мои вопросы. И тогда я признаю твою искренность, и не только позволю пройти дальше, но более - награжу.";
			link.l1 = "Спрашивай!";
			link.l1.go = "question1";
		break;
		
		case "question1":
			PlaySound("VOICE\Russian\TopChavinavi-02.wav");
			dialog.text = "Я - вождь чавинави, воинов-ягуаров. Тысячу лет назад я был человеком, теперь же несу почётную службу в этих священных чертогах. Какой бог повелевает мной?";
			link.l1 = "Миктлантекутли.";
			link.l1.go = "question1_l";
			link.l2 = "Кукулькан.";
			link.l2.go = "question1_l";
			link.l3 = "Юм Симиль.";
			link.l3.go = "question1_r";
			link.l4 = "Инти.";
			link.l4.go = "question1_l";
			link.l5 = "Кавиль.";
			link.l5.go = "question1_l";
		break;
		
		case "question1_r":
			dialog.text = "До прихода вас, бледнолицых, вся эта земля, от великих снегов на севере до великих равнин на юге, принадлежала нам, разным братьям одной семьи...";
			link.l1 = "";
			link.l1.go = "question2";
		break;
		
		case "question1_l":
			dialog.text = "До прихода вас, бледнолицых, вся эта земля, от великих снегов на севере до великих равнин на юге, принадлежала нам, разным братьям одной семьи...";
			link.l1 = "";
			link.l1.go = "question2";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question2":
			dialog.text = "Какое племя индейцев воздвигло этот храм?";
			link.l1 = "Инки.";
			link.l1.go = "question2_l";
			link.l2 = "Чавин.";
			link.l2.go = "question2_r";
			link.l3 = "Майя.";
			link.l3.go = "question2_l";
			link.l4 = "Ацтеки.";
			link.l4.go = "question2_l";
			link.l5 = "Араваки.";
			link.l5.go = "question2_l";
		break;
		
		case "question2_r":
			dialog.text = "Наши народы развивались, постигали мудрость и покоряли новые леса, равнины и острова. Люди, построившие этот храм, прибыли из края лесов через Большую Воду...";
			link.l1 = "";
			link.l1.go = "question3";
		break;
		
		case "question2_l":
			dialog.text = "Наши народы развивались, постигали мудрость и покоряли новые леса, равнины и острова. Люди, построившие этот храм, прибыли из края лесов через Большую Воду...";
			link.l1 = "";
			link.l1.go = "question3";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question3":
			dialog.text = "Кто возглавлял славный отряд этих первопроходцев?";
			link.l1 = "Верховный вождь.";
			link.l1.go = "question3_l";
			link.l2 = "Верховный жрец.";
			link.l2.go = "question3_l";
			link.l3 = "Сын верховного вождя.";
			link.l3.go = "question3_r";
			link.l4 = "Сын верховного жреца.";
			link.l4.go = "question3_l";
			link.l5 = "У отряда не было командира.";
			link.l5.go = "question3_l";
		break;
		
		case "question3_r":
			dialog.text = "Индейцы - отважные воины и путешественники, поселившись на новой земле, не переставали любить и почитать свою родину. И в знак великой любви к земле предков они воздвигли в святилище храма статую птицы, символ родного края. Она за моей спиной...";
			link.l1 = "";
			link.l1.go = "question4";
		break;
		
		case "question3_l":
			dialog.text = "Индейцы - отважные воины и путешественники, поселившись на новой земле, не переставали любить и почитать свою родину. И в знак великой любви к земле предков они воздвигли в святилище храма статую птицы, символ родного края. Она за моей спиной...";
			link.l1 = "";
			link.l1.go = "question4";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question4":
			dialog.text = "Какое название носит эта птица?";
			link.l1 = "Альбатрос.";
			link.l1.go = "question4_l";
			link.l2 = "Орёл.";
			link.l2.go = "question4_l";
			link.l3 = "Гриф.";
			link.l3.go = "question4_l";
			link.l4 = "Рухх.";
			link.l4.go = "question4_l";
			link.l5 = "Кондор.";
			link.l5.go = "question4_r";
		break;
		
		case "question4_r":
			dialog.text = "Но годы процветания прошли, как угасает пламя лампады, и жизнь покинула остров. И только храм остался как вечное напоминание о величии древних индейцев. Последний шаман оставил на постаменте священный солнечный шар, дарующий силу храбрым и карающий нечестивцев. Его забрал тот, кто сумел пройти сюда до тебя...";
			link.l1 = "";
			link.l1.go = "question5";
		break;
		
		case "question4_l":
			dialog.text = "Но годы процветания прошли, как угасает пламя лампады, и жизнь покинула остров. И только храм остался как вечное напоминание о величии древних индейцев. Последний шаман оставил на постаменте священный солнечный шар, дарующий силу храбрым и карающий нечестивцев. Его забрал тот, кто сумел пройти сюда до тебя...";
			link.l1 = "";
			link.l1.go = "question5";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question5":
			dialog.text = "Как назывался этот священный шар?";
			link.l1 = "Шар солнечного сияния.";
			link.l1.go = "question5_l";
			link.l2 = "Шар солнечных лучей.";
			link.l2.go = "question5_l";
			link.l3 = "Шар полуденного солнца.";
			link.l3.go = "question5_l";
			link.l4 = "Шар восходящего солнца.";
			link.l4.go = "question5_r";
			link.l5 = "Шар заходящего солнца.";
			link.l5.go = "question5_l";
		break;
		
		case "question5_r":
			if (CheckAttribute(pchar, "questTemp.Caleuche.QuestionFail"))
			{
				PlaySound("VOICE\Russian\hambit\Chavinavy.wav");
				dialog.text = "Неправильные ответы свидетельствуют о том, что ты мне лгал, белый человек, и о том, что ты пришёл сюда с дурными намерениями. Ты сумел ускользнуть от стражей лабиринта и святилища, разгадать секрет механизма двери, но смертельного боя со мной тебе не миновать! Приготовься к смерти, бледнолицый!";
				link.l1 = "Ну, раз ты настаиваешь - посмотрим, какой ты был великий воин...";
				link.l1.go = "chavinavi_fight";
			}
			else
			{
				dialog.text = "Твои знания о моём народе и этом храме говорят в твою пользу, бледнолицый. Теперь я верю тебе. Ступай и выполни то, зачем сюда пришёл. Возложи священную реликвию на постамент перед кондором, там, где когда-то сиял шар восходящего солнца\nА затем возвращайся ко мне. Твоё почитание Юм Симиля и твой добровольный поступок по возврату украденного твоими братьями должны быть достойно вознаграждены.";
				link.l1 = "Спасибо за доверие, великий вождь.";
				link.l1.go = "chavinavi_exit";
			}
		break;
		
		case "question5_l":
			PlaySound("VOICE\Russian\hambit\Chavinavy.wav");
			dialog.text = "Неправильные ответы свидетельствуют о том, что ты мне лгал, белый человек, и о том, что ты пришёл сюда с дурными намерениями. Ты сумел ускользнуть от стражей лабиринта и святилища, разгадать секрет механизма двери, но смертельного боя со мной тебе не миновать! Приготовься к смерти, бледнолицый!";
			link.l1 = "Ну, раз ты настаиваешь - посмотрим, какой ты был великий воин...";
			link.l1.go = "chavinavi_fight";
		break;
		
		case "chavinavi_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_TopChavinaviDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "chavinavi_exit":
			DialogExit();
			sld = ItemsFromID("SkullAztec");
			sld.shown = "0";
			sld.useLocation = "treasure_alcove";
			sld.useLocator = "button01";
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "Chavinavi_5":
			PlaySound("VOICE\Russian\Complete.wav");
			dialog.text = "Ты выполнил, что обещал, бледнолицый. Я рад, что ты не оказался лжецом, как все твои братья. И я тоже сдержу слово. Вот, возьми мой подарок - символ мощи воинов-ягуаров. Сам Юм Симиль вложил в эту шкуру частицу своей силы!";
			link.l1 = "Ух ты! Какая красивая!";
			link.l1.go = "Chavinavi_6";
		break;
		
		case "Chavinavi_6":
			GiveItem2Character(pchar, "KhaelRoa_item");
			Log_Info("Вы получили шкуру ягуара");
			PlaySound("interface\important_item.wav");
			dialog.text = "Это не простая шкура. Как только ты накинешь её на себя, ты обретёшь силу воина-ягуара. Мощь твоего оружия, изрыгающего пламя и свинец, возрастёт многократно, и с его помощью ты сможешь усеять поле брани трупами своих врагов\nНо силу, заключенную Юм Симилем в эту шкуру, не сможет удержать ни один смертный. Как только ты высвободишь её, она будет сопровождать тебя лишь до следующей полуночи, а затем - иссякнет. Береги мой подарок, бледнолицый, и не растрать его силу на пустячную стычку.";
			link.l1 = "Спасибо! Я использую её лишь тогда, когда врагов будет столько, что бежать от них станет некуда.";
			link.l1.go = "Chavinavi_7";
		break;
		
		case "Chavinavi_7":
			dialog.text = "А теперь - ступай. Но предостереги своих братьев от попыток посягнуть на спокойствие этих священных чертогов. Воины-ягуары не знают ни жалости, ни пощады к бледнолицым.";
			link.l1 = "Прощай, вождь...";
			link.l1.go = "Chavinavi_8";
		break;
		
		case "Chavinavi_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
			}
			sld = ItemsFromID("KhaelRoa_item");
			sld.groupID	= ITEM_SLOT_TYPE;
			sld.ItemType = "ARTEFACT";
			sld.Type = ITEM_AMULET;
			sld.time = 2;
			sld.price = 5000;
			sld.Weight = 10.0;
			AddQuestRecord("Caleuche", "38");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeIndianRelation(10.0);
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}