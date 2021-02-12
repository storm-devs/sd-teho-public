// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Спрашивай, чего ты хочешь?",
                          "Мы только что поднимали это тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушай, это магазин, здесь люди покупают что-то. Не отвлекай меня!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, "+ GetSexPhrase("забыл","забыла") +" что-то...",
                      "Да уж, действительно в третий раз...", "Гм, не буду...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Послушай, "+npchar.name+", ты не видел в последнее время на Исла Тесоро Мигеля Дичозо?";
				link.l1.go = "tieyasal";
			}
			// Addon 2016-1 Jason пиратская линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_start")
			{
				link.l1 = ""+npchar.name+", я прибыл от Маркуса Тиракса. Он сказал, что вам нужен человек для работы.";
				link.l1.go = "mtraxx";
			}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_win")
			{
				link.l1 = ""+npchar.name+", 'Розбоом' найден и захвачен. Приступим к выгрузке товара и расчету?";
				link.l1.go = "mtraxx_5";
			}
		break;
				
		// город майя
		case "tieyasal":
			dialog.text = "Видел. Он закупал припасы на свой корабль у меня. Кстати, совсем недавно. Вы буквально на несколько дней разминулись. Кстати, быть может, он еще где-то в поселке. Я, знаешь ли, не шпионю за людьми. Поспрашивай еще, глядишь - отыщется твой дон.";
			link.l1 = "Понятно. Спасибо за сведения!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
			pchar.quest.Mtraxx_PasqualeLate.over = "yes";
            dialog.text = "Именно так! Очень хорошо, вы прибыли вовремя. Теперь излагаю суть дела...";
			link.l1 = "Внимательно вас слушаю.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
			string sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")));
            dialog.text = "В данный момент к нашим водам приближается голландский корабль из Виллемстада - "+sTemp+" под названием 'Розбоом' с трюмом, полным черного дерева, в сопровождении одного корабля охранения. Каким маршрутом он идет - через Синт-Маартен или через Эспаньолу - мне неведомо, но я точно знаю дату и координаты места, где этот караван встретится с третьим голландским кораблем, и под его охраной конвой двинется на север, в Европу\nВаша задача - найти голландцев в указанном мной месте, отбить 'Розбоом', захватить весь его груз и доставить мне. С вами рассчитаемся сразу же после доставки товара.";
			link.l1 = "Задача ясна. Место и день?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
			int i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
			int n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
            dialog.text = "Встреча голландцев назначена в следующем месте: "+sti(pchar.questTemp.Mtraxx.Crdn.degN)+" градусов "+i+" минут северной широты, "+sti(pchar.questTemp.Mtraxx.Crdn.degW)+" градусов "+n+" минут западной долготы. Это где-то на юг или юго-запад от Исла-Тесоро, я в этом плохо соображаю, вы моряк - разберетесь. Дата - через 5 дней, не считая сегодняшний.";
			link.l1 = "Сейчас все запишем... понятно. Ну, тогда не будем терять времени!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Удачи, капитан. Жду вас с товаром.";
			link.l1 = "...";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_convoy";
		   i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
           n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
		   AddQuestRecord("Roger_4", "3");
		   AddQuestUserData("Roger_4", "sShip", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")+ "Gen")));
		   AddQuestUserData("Roger_4", "sdegN", sti(pchar.questTemp.Mtraxx.Crdn.degN));
		   AddQuestUserData("Roger_4", "sminN", i);
		   AddQuestUserData("Roger_4", "sdegW", sti(pchar.questTemp.Mtraxx.Crdn.degW));
		   AddQuestUserData("Roger_4", "sminW", n);
		   SetFunctionTimerCondition("Mtraxx_PasqualeTimeConvoy", 0, 0, 6, false);
		   SetFunctionTimerCondition("Mtraxx_PasqualeConvoyOver", 0, 0, 7, false);
		break;
		
		case "mtraxx_5":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_EBONY);
			if (iTotalTemp < 1)
			{
				dialog.text = "Вы издеваетесь, молодой человек? В ваших трюмах нет ни одного центнера черного дерева! Вы меня нагло надули! Это вам даром не пройдет - я пожалуюсь Маркусу Тираксу! Убирайтесь вон!!";
				link.l1 = "Гм...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < makeint(sti(pchar.questTemp.Mtraxx.Crdn.Ebony)/4))
			{
				dialog.text = "Вы издеваетесь, молодой человек? В ваших трюмах жалкие крохи от того количества черного дерева, что было на 'Розбоом'! Вы меня нагло надули! Это вам даром не пройдет - я пожалуюсь Маркусу Тираксу! Убирайтесь вон!!";
				link.l1 = "Гм...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < sti(pchar.questTemp.Mtraxx.Crdn.Ebony)-20)
			{
				dialog.text = "На 'Розбоом' должно было быть не меньше "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.Crdn.Ebony))+" черного дерева. Почему вы привезли меньше?";
				link.l1 = "Так это - часть груза пришлось бросить в бою. И еще крысы сожрали, треклятые...";
				link.l1.go = "mtraxx_7";
				break;
			}
            dialog.text = "Очень хорошо. Сколько у вас товара? "+FindRussianQtyString(iTotalTemp)+"? Отлично! Я заплачу вам по 150 песо за единицу товара.";
			link.l1 = "По 150 песо? Но мне кажется, что это дерево стоит гораздо дороже...";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_6":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_angry";
		   DoQuestReloadToLocation("Pirates_town", "reload", "reload6", "");
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_7":
            dialog.text = "Крысы? Ну-ну... Впрочем, ладно. Я заплачу вам по 100 песо за единицу товара и можете быть свободны.";
			link.l1 = "Всего по 100 песо? Но это же грабеж!";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
			AddMoneyToCharacter(pchar, iTotalTemp*100);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "Грабеж - это по вашей части, капитан, а я просто торговец. Берите ваши деньги и прекратим эти споры - вы и так нажились на мне, сбыв где-то часть моего товара...";
			link.l1 = "Ну и черт с вами!";
			link.l1.go = "mtraxx_9";
		break;
		
		case "mtraxx_9":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_fail";
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_10":
            dialog.text = "Вам правильно кажется, капитан, но во-первых, попробуйте продать дороже награбленный товар - я посмотрю, сколько вам за него заплатят. Цена, предложенная вам, очень высока. Во-вторых, без моей наводки вы бы никогда не нашли этот караван, а там, кроме дерева, было наверняка что-то еще, но, заметьте - я не требую от вас более ничего. В-третьих, я похвалю вас перед Маркусом Тираксом, а это - поверьте - дорогого стоит. Ну и в-четвертых, должен же бедный торговец на что-то жить.";
			link.l1 = "Ух! Под градом таких аргументов я отступаю, "+npchar.name+". Приступим к расчету.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
			AddMoneyToCharacter(pchar, iTotalTemp*150);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "Вот и славно. Получите ваши деньги. Было приятно с вами работать. Заглядывайте, не забывайте. Удачи в море!";
			link.l1 = "И вам успехов в торговле...";
			link.l1.go = "mtraxx_12";
		break;
		
		case "mtraxx_12":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_complete";
		   AddQuestRecord("Roger_4", "9");
		   pchar.quest.mtr_pasq_fin.win_condition.l1 = "location";
		   pchar.quest.mtr_pasq_fin.win_condition.l1.location = "Pirates_town";
		   pchar.quest.mtr_pasq_fin.function = "Mtraxx_PasqualeJeffry";
		   bDisableFastReload = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}