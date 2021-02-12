// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "М-да, позвольте угадаю... Опять ничего существенного?",
                          "Послушайте, я финансами оперирую, а не на вопросы отвечаю...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Вы угадали, простите...", "Я понимаю...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Взгляните на эти серьги, месье. Я нашел их в кармане мертвого бандита в джунглях. Это явно работа хорошего ювелира, которого в этой глуши и быть не могло. Можете что-нибудь сказать о них?";
                link.l1.go = "Sharlie_junglejew";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
			{
				link.l1 = "Я знаю, что у вас есть должник по имени Фульк Делюк. Скажите, насколько велика его... провинность?";
                link.l1.go = "Sharlie";
			}	
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
			{
				link.l1 = "Я по поводу долга Фулька Делюка.";
                link.l1.go = "Sharlie_repeat";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
			{
				link.l1 = "Я выполнил ваше задание, месье. Вот ваш... испанский друг.";
                link.l1.go = "Sharlie_14";
			}
			//<-- Бремя гасконца
		break;
		
		case "Sharlie":
			dialog.text = "А вам-то какое дело до этого, позволю себе спросить?";
			link.l1 = "Мне нужен этот человек. Причем на свободе, а не за решеткой. А поскольку в тюрьме мне сообщили, что пока долг не будет возвращен вам, то его не выпустят, я заинтересован в погашении этого долга.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "А-а, это меняет дело. Я тоже заинтересован, чтобы мои деньги вернулись ко мне... Этот Фульк Делюк - странный тип. Он взял в долг относительно небольшую сумму денег - пять тысяч песо. Вернуть он ее не вернул и стал скрываться. В итоге - процентов набежало уже на размер суммы основного долга, и сам в тюрьму угодил.";
			link.l1 = "Стало быть, на сей день его долг составляет десять тысяч?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Десять тысяч четыреста пятьдесят песо, если быть точным, месье. Так что его свобода оценивается именно в эту сумму. Вы готовы оплатить мне ее? Я, пожалуй, удивлен...";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Не удивляйтесь. Вот деньги.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Хм... Сумма и впрямь приличная. Послушайте, месье, может, мы попробуем с вами договориться? Ну, например, у вас есть какое-то дело, которое я бы смог выполнить, а вы бы оценили мою услугу в эти десять с половиной тысяч...";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart")) link.l2.go = "Sharlie_5x";
			else link.l2.go = "Sharlie_5"; // Addon 2016-1 Jason пиратская линейка 1
		break;
		
		case "Sharlie_3":
			AddMoneyToCharacter(pchar, -10450);
			dialog.text = "Да, похоже этот моряк вам действительно нужен, раз вы готовы выложить за него такую сумму денег. Впрочем, это не мое дело, ведь так, месье? Возьмите его расписки - теперь вы обладаете правом на его долг и можете требовать свои монеты с него. Ну и, конечно, ходатайствовать о его освобождении из тюрьмы.";
			link.l1 = "Именно этого я и хотел. До свидания, "+npchar.name+"!";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			Log_Info("Вы получили долговые расписки");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Sharlie = "freeskiper";
		break;
		
		case "Sharlie_5x": // Addon 2016-1 Jason пиратская линейка 1
			dialog.text = "Услуга? Увы, но я не нуждаюсь в ваших услугах, по крайней мере - сейчас.";
			link.l1 = "Жаль. Что же, тогда я принесу деньги за Фулька. До встречи!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_5":
			dialog.text = "Услуга? Хм... Знаете, месье, еще вчера бы я ответил отрицательно, но теперь... да, у меня есть дело, выполнение которого я бы оценил в эту сумму, но предупреждаю: это опасно.";
			link.l1 = "Опасно для чего?";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "Для вашей драгоценной жизни, конечно. Так что подумайте, перед тем как дать согласие, готовы ли вы к такому.";
			link.l1 = "Сударь, мне не впервой смотреть в глаза опасностям разного рода. Так что давайте перейдем к описанию подробностей, и если для этого не нужно будет в одиночку вырезать гарнизон форта, возможно, я смогу выполнить то, о чем вы сейчас так загадочно намекаете.";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			dialog.text = "Хорошо. Тогда слушайте. Сегодня вечером из пиратского логова Ле Франсуа, что находится в восточной части нашего острова, выйдут несколько пиратов и отправятся в бухту Ле Марен. С ними будет пленник - испанский офицер, которого они собираются сдать за выкуп англичанам\nЭтот испанский офицер - замечательный специалист в фортификационном деле, и англичане намерены использовать его таланты в своих целях. За ним специально в бухту Ле Марен присылают военный корабль из Порт-Рояля\nОфицер - мой старинный знакомый, и я бы не хотел, чтобы он попал в плен к англичанам. Как вы понимаете, к официальным властям острова я обратиться не могу, поскольку мы с Испанией находимся в состоянии вражды\nБудь у меня побольше времени - я бы, конечно, нанял соответствующих людей для перехвата испанца... кхм, моего знакомого, но увы! Мне остатся только предложить это дело вам, а именно: отправиться в бухту Ле Марен и... убедить пиратов отдать вам пленника\nНе думаю, что они окажутся сговорчивыми, так что - решайте.";
			link.l1 = "Сколько будет пиратов в конвое испанца?";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			dialog.text = "Не знаю. Может, человека два, а может - три или четыре. Ну, так что скажете?";
			link.l1 = "Я уже сказал вам - мне не привыкать смотреть в лицо опасности, и я знаю, с какой стороны держать шпагу.";
			link.l1.go = "Sharlie_10";
			link.l2 = "Хм. Вы правы - дело опасное. Не буду я в одиночку нападать на отряд пиратов.";
			link.l2.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "Дело ваше. Если чувствуете, что не по плечу ноша - то лучше сразу отказаться. Тогда жду вас с деньгами в качестве уплаты долга Делюка.";
			link.l1 = "Хорошо. Я принесу деньги за него. До встречи!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_10":
			dialog.text = "Очень хорошо. Рад слышать это. Тогда вам следует отправляться в бухту Ле Марен - пираты будут там приблизительно с девяти вечера и до полуночи. Не прозевайте их! И не вздумайте идти в бухту на корабле - спугнете негодяев. Только по суше через джунгли!\nКогда освободите пленника, приведете его ко мне - дверь будет открыта даже ночью. Будьте осторожны и удачи вам!";
			link.l1 = "Спасибо! Удача мне точно понадобится...";
			if (CheckCharacterItem(pchar, "pistol1")) link.l1.go = "Sharlie_13";
			else link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Одну минуту! Вижу, у вас нет даже пистоля. Возьмите один из моих, и несколько зарядов к нему. Думаю, это вам пригодится.";
			link.l1 = "Да, эта штучка однозначно может понадобиться. Благодарю вас, сударь.";
			link.l1.go = "Sharlie_12";
		break;
		
		case "Sharlie_12":
			Log_Info("Вы получили строевой пистоль");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol1");
			TakeNItems(pchar, "bullet", 20);
			TakeNItems(pchar, "gunpowder", 20);
			dialog.text = "А теперь ступайте, и да поможет вам Бог!";
			link.l1 = "...";
			link.l1.go = "Sharlie_13";
		break;
		
		case "Sharlie_13":
			DialogExit();
			pchar.quest.Sharlie_captive.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_captive.win_condition.l1.hour = 21.00;
			pchar.quest.Sharlie_captive.function = "Captive_Timer";
			SetFunctionTimerCondition("Captive_CreatePiratesOver", 0, 0, 1, false);
			AddQuestRecord("SharlieD", "1");
			pchar.questTemp.Sharlie = "bankskiperfight";
			pchar.questTemp.Sharlie.Captive = "true";
			pchar.questTemp.Sharlie.Captive.Name = GetFullName(npchar);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "Sharlie_14":
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";
			ref sld = characterFromId("CaptiveSpain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 5.0);
			sld.lifeday = 0;
			SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			dialog.text = "Замечательно! Очень рад, что вам удалось успешно с этим справиться. Подробности дела, мне, пожалуй, лучше не знать, ведь так? Ну, а мой дорогой испанский гость может чувствовать себя у меня дома в безопасности...";
			link.l1 = "Что насчет долга Фулька Делюка?";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Да, конечно. Возьмите его расписки - теперь вы обладаете правом на его долг и можете требовать свои монеты с него. Ну и, конечно, ходатайствовать о его освобождении из тюрьмы. Я всё сделал, как обещал?";
			link.l1 = "Да, месье. Все строго согласно договору. А теперь разрешите откланяться.";
			link.l1.go = "Sharlie_4";
			AddQuestRecord("SharlieD", "7");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		break;
		
		case "Sharlie_repeat":
			dialog.text = "Итак, вы готовы заплатить за него долг?";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Да. Вот деньги.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "К сожалению, я еще не собрал нужной суммы...";
			link.l2.go = "exit";
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Хм. Похоже, вы правы - это дорогие серьги, и сделаны в Старом Свете, несомненно... Что я могу сказать? Я могу дать вам за них тридцать... нет, даже тридцать пять золотых дублонов. Соглашайтесь, дороже вам их не продать.";
			link.l1 = "Тридцать пять дублонов? Неплохая цена. Я согласен. Забирайте.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "Нет. Лучше я оставлю эту драгоценность себе.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("Вы отдали серьги");
			RemoveItems(pchar, "jewelry25", 1);
			TakeNItems(pchar, "gold_dublon", 35);
			AddQuestRecord("SharlieE", "3");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

