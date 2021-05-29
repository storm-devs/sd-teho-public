// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Спрашивай, чего ты хочешь?",
                          "Мы только что поднимали эту тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушай, это магазин, здесь люди покупают что-то. Не отвлекай меня!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, "+ GetSexPhrase("забыл","забыла") +" что-то...",
                      "Да уж, действительно в третий раз...", "Гм, не буду...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
			if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
			{
				Link.l1 = "Послушайте, месье, я ищу работу. Ну, не то, чтобы поденным рабочим или грузчиком мешки из порта таскать, а выполнить какое-нибудь поручение, скажем. Вы не нуждаетесь в сторонней помощи?";
				Link.l1.go = "Sharlie_storehelper";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
			{
				Link.l1 = "Я выполнил ваше поручение. Мне удалось отыскать Гийома Лавуа.";
				Link.l1.go = "Sharlie_storehelper_2";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
			{
				Link.l1 = "Вот ваш новый помощник, месье. Знакомьтесь.";
				Link.l1.go = "Sharlie_storehelper_11";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
			{
				Link.l1 = "Это опять я, месье. Я пришёл за своей наградой.";
				Link.l1.go = "Sharlie_storehelper_13";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Посмотрите на эти серьги, месье. Я нашёл их на теле убитого бандита в джунглях. Это явно работа хорошего ювелира, которого в этой глуши и быть не могло. Можете что-нибудь сказать об этих серьгах?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца
		break;
		
		//--> Бремя гасконца
		case "Sharlie_storehelper":
			dialog.text = "Поручение? Хм. Пожалуй, у меня действительно будет для вас работа такого рода, как вы хотите. У меня пропал помощник, работавший на складе. Уже неделя, как его нет, и это, черт возьми, крайне неприятно, потому что мне приходится делать ещё и его работу, а я совершенно не успеваю\nЯ вас прошу, разыщите этого болвана и выясните, какого лешего он забросил работу, а ещё лучше - приведите его ко мне. За помощь я заплачу вам тысячу песо.";
			link.l1 = "Хорошо, я согласен. Как зовут вашего помощника и опишите его внешность, а также, какие у вас соображения - где его можно найти c наибольшей вероятностью?";
			link.l1.go = "Sharlie_storehelper_1";
			link.l2 = "Искать человека невесть где за какую-то жалкую тысячу? Вы должно быть, шутите!";
			link.l2.go = "Sharlie_storehelper_exit";
			npchar.quest.storehelper = "true";
		break;
		
		case "Sharlie_storehelper_exit":
			dialog.text = "Эй, месье, это же вы ищете работу, а не я? Не хотите - как хотите, я вас не принуждаю. Всего доброго.";
			link.l1 = "Гм...";
			link.l1.go = "exit";
		break;
		
		case "Sharlie_storehelper_1":
			dialog.text = "Зовут его Гийом Лавуа. Как выглядит? Тридцати пяти лет от роду, носит усы и бороду, обычно на нём длинный коричневый жилет и белая рубаха, и обязательно - треуголка, адмирал этакий, якорь ему в корму\nГде может быть? Ну уж точно не в Сен-Пьере - его нет в городе, я уже все ноги сбил, искавши и расспрашивавши горожан, так что можете не тратить тут время понапрасну. А шляться за городом у меня нет ни времени, ни желания.";
			link.l1 = "Ясно. Приступаю к поискам. Как только будет какой-то результат - немедленно сообщу.";
			link.l1.go = "exit";
			AddQuestRecord("SharlieA", "1");
			pchar.questTemp.Sharlie.Storehelper = "true";
			pchar.questTemp.Sharlie.Storehelper.Chance = rand(2);
			AddDialogExitQuestFunction("Sharlie_CreateStorehelper");
		break;
		
		case "Sharlie_storehelper_2":
			dialog.text = "Да? И где же он?";
			link.l1 = "Я нашёл его в Ле Франсуа. Он больше не будет работать на вас. Он так и сказал. А также добавил ещё много чего в ваш адрес... вам интересно послушать, что именно?";
			link.l1.go = "Sharlie_storehelper_3";
		break;
		
		case "Sharlie_storehelper_3":
			dialog.text = "Нет. Избавьте меня от этого... Вот незадача-то какая! И как же я теперь буду без помощника?";
			link.l1 = "Наймите другого. Или это действительно такая проблема, как сказал Гийом?";
			link.l1.go = "Sharlie_storehelper_4";
		break;
		
		case "Sharlie_storehelper_4":
			dialog.text = "Это действительно непросто. А что он сказал, этот бездельник?";
			link.l1 = "Ну, допустим, сейчас он явно не бездельничает, хе-хе. А сказал он, что никто во всем Сен-Пьере не пойдет к вам на службу, потому что... вы недостаточно платите своим работникам. Да, кстати, "+npchar.name+", с вас тысяча песо, как вы и обещали.";
			link.l1.go = "Sharlie_storehelper_5";
		break;
		
		case "Sharlie_storehelper_5":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Да пожалуйста, держите ваши деньги. Ха! Я мало плачу! Конечно, теперь мне понятно, почему я никого не могу нанять - этот негодяй распустил по городу гнусные слухи обо мне. Но что же мне делать? Я один не справляюсь\nМне нужно не спать полночи, чтобы сосчитать весь товар и ещё постоянно смотреть надо, чтобы никто ничего не стянул, вместо того, чтобы торговать! После прошлой погрузки я недосчитался пяти бочонков рома - я уверен, что грузчики 'по ошибке' прихватили их...";
			link.l1 = "Ну, я не знаю, что вам посоветовать. Ладно, всего доброго, мне пора.";
			link.l1.go = "Sharlie_storehelper_6";
		break;
		
		case "Sharlie_storehelper_6":
			dialog.text = "Стойте! Я думаю, вы сможете помочь мне. Раз вы сумели разыскать этого прохвоста, то, вполне возможно, у вас получится...";
			link.l1 = "Интересно, и что же я сумею сделать, если в этом городе вам никто не верит? Я здесь человек новый, и...";
			link.l1.go = "Sharlie_storehelper_7";
		break;
		
		case "Sharlie_storehelper_7":
			dialog.text = "Дайте мне сказать, месье. Вы были в Ле Франсуа. Я хочу попросить вас отправиться туда ещё раз и постараться нанять работника мне на склад там. Быть может, в этом пиратском поселке Гийом ещё не успел ославить мое имя\nРабота несложная - пересчитывать товар, поступающий на склад и уходящий со склада, и следить, чтобы никто ничего лишнего не прихватил. Ну, может, иногда за прилавком постоять, пока меня нет, но это за отдельную оплату\nСкажете, что я предоставлю жилье - комнату в задней части магазина, с кроватью и мебелью. Жалование - пятьсот песо в неделю. Месье, я собираюсь расширяться, у меня только-только начали налаживаться дела и без помощника мне никак нельзя, понимаете?";
			link.l1 = "Хм. Попробовать можно, хотя я не уверен... Сколько вы мне заплатите за работу?";
			link.l1.go = "Sharlie_storehelper_8";
		break;
		
		case "Sharlie_storehelper_8":
			dialog.text = "Это будет зависеть от того, какого работника вы наймёте. Чем более умелым он окажется, тем больше я заплачу за вашу услугу. Так будет справедливо, согласитесь.";
			link.l1 = "А вам не кажется, что вы сейчас заставляете меня играть втемную? Откуда мне знать, как вы оцените работника? Вы любого можете охарактеризовать как плохого и...";
			link.l1.go = "Sharlie_storehelper_9";
		break;
		
		case "Sharlie_storehelper_9":
			dialog.text = "Месье! Я, конечно, и в самом деле могу считаться скуповатым, но бесчестным меня назвать никто не сможет! Если я сказал, что оплачу ваш труд согласно результату - значит, так и будет. Поймите и меня тоже - вы ведь можете привести какого-нибудь бродягу-бездельника, который не то что работать не станет, но ещё и ограбит меня ночью!";
			link.l1 = "Ладно. Я согласен. Буду полагаться на ваше слово, "+npchar.name+". Не стоит более терять время, оно, как известно, - деньги.";
			link.l1.go = "Sharlie_storehelper_10";
		break;
		
		case "Sharlie_storehelper_10":
			DialogExit();
			AddQuestRecord("SharlieA", "3");
			pchar.quest.storehelper.win_condition.l1 = "Timer";
			pchar.quest.storehelper.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.storehelper.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.storehelper.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.storehelper.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.storehelper.function = "StorehelperOver";
			pchar.questTemp.Sharlie.Storehelper = "hire";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
		break;
		
		case "Sharlie_storehelper_11":
			dialog.text = "Вы отыскали мне работника? Прекрасно. Позвольте мне побеседовать с ним, и зайдите через часик за своим гонораром.";
			link.l1 = "Хорошо. Я буду у вас через один час.";
			link.l1.go = "Sharlie_storehelper_12";
		break;
		
		case "Sharlie_storehelper_12":
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Sharlie.Storehelper = "wait";
			DialogExit();
			pchar.quest.storehelper5.win_condition.l1 = "Timer";
			pchar.quest.storehelper5.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.storehelper5.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.storehelper5.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.storehelper5.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.storehelper5.function = "StorehelperFinal";
			AddQuestRecord("SharlieA", "5");
		break;
		
		case "Sharlie_storehelper_13":
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 3000);
					dialog.text = "Найденный вами работник вполне мне подходит, хотя бахвалится он больше, чем умеет реально делать. Но ничего, я эту дурь из него быстро выбью. Ваше вознаграждение составляет три тысячи песо. Получите, пожалуйста.";
					link.l1 = "Благодарю! Всего доброго, месье.";
					link.l1.go = "Sharlie_storehelper_14";
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 5000);
					dialog.text = "Вам удалось найти действительно ценного работника! Он даже лучше, чем этот негодяй Гийом. Я очень и очень вами доволен, сударь. Возьмите вашу награду - пять тысяч песо.";
					link.l1 = "Благодарю! Всего доброго, месье.";
					link.l1.go = "Sharlie_storehelper_14";
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 4000);
					dialog.text = "Вы нашли хорошего работника. И хотя все тонкости ему не известны, я уверен, он за пару недель их без труда освоит. Я доволен вами, сударь. Вот, возьмите награду - четыре тысячи песо.";
					link.l1 = "Благодарю! Всего доброго, месье.";
					link.l1.go = "Sharlie_storehelper_14";
				break;
			}
		break;
		
		case "Sharlie_storehelper_14":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			CloseQuestHeader("SharlieA");
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "А что тут скажешь? Великолепные серьги... Я могу дать вам за них... так-так... четыре тысячи песо. Больше вам навряд ли кто предложит. Согласны?";
			link.l1 = "По рукам! Забирайте.";
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
			AddMoneyToCharacter(pchar, 4000);
			AddQuestRecord("SharlieE", "4");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
		break;
		//<-- Бремя гасконца
	}
	UnloadSegment(NPChar.FileDialog2);
}

