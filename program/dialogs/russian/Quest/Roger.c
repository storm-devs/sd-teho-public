// диалоги персонажей по пиратской линейке // Addon 2016-1 Jason пиратская линейка
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Что тебе надо?";
			link.l1 = "Пожалуй, я пойду...";
			link.l1.go = "exit";
		break;
		
		// Лопе Монторо
		case "Mtr_officer":
			if (pchar.questTemp.Mtraxx != "fail" && pchar.questTemp.Mtraxx == "jewelry_5")
			{
				pchar.quest.Mtraxx_JewelryHavanaOver.over = "yes"; //снять таймер
				dialog.text = "Каррамба, кто ты такой?!";
				link.l1 = "Здравствуйте, дон Лопе. Мы не знакомы, но ведь завязать знакомство никогда не поздно, так? Особенно при учёте того, что я буквально горю желанием помочь вам в вашей непростой ситуации...";
				link.l1.go = "Mtr_officer_1";
			}
			else
			{
				dialog.text = "Что тебе надо?";
				link.l1 = "Пожалуй, я пойду...";
				link.l1.go = "exit";
			}
		break;
		
		case "Mtr_officer_1":
            dialog.text = "Помочь? Мне? Вот уж чего не ожидал! А по какой причине у вас, сеньор, возникло столь горячее желание, не поведаете?";
			link.l1 = "Безусловно. Мне очень нужно найти вашего бывшего капитана, Эсберто Кабаньяса, и как можно быстрее... и желательно в его потаённом месте. Также я не огорчусь, если прибуду на это место до капитана Кабаньяса...";
			link.l1.go = "Mtr_officer_2";
		break;
		
		case "Mtr_officer_2":
            dialog.text = "Ха-ха-ха! Говорил же я этому ублюдку, чтобы не распускал свой болтливый язык! Голубой янтарь, речь о нём?";
			link.l1 = "Вы чрезвычайно догадливы, сударь.";
			link.l1.go = "Mtr_officer_3";
		break;
		
		case "Mtr_officer_3":
            dialog.text = "Тогда не будем терять времени. Я с удовольствием расскажу вам абсолютно всё, если вы найдёте способ вытащить меня отсюда. Вам известно, за что меня отправили сюда?";
			link.l1 = "В общих чертах - да.";
			link.l1.go = "Mtr_officer_4";
		break;
		
		case "Mtr_officer_4":
            dialog.text = "Я был пьян в стельку, когда натворил всё это. Мерзавец тавернщик, удавить его надо... И я ничего не помню. Сам узнал из рассказов, когда очнулся в трюме 'Кантавро'. И всё можно было решить простым выходом в море - алькальд и комендант были готовы смотреть в другую сторону, но... проклятый дон Эсберто буквально засунул меня за решётку. Вы думаете, он сделал это потому, что он такой правильный? Ха-ха, да этот мерзавец просто избавился от необходимости делиться добычей\nЭто я предположил, что янтаря под водой намного больше, чем было на пляже. Это я придумал способ, как его добыть. Мне за это полагалась солидная доля, но он... ах, мерзкое отродье! Впрочем, довольно. Ни алькальд, ни комендант, ни губернатор, дон де Толедо, не довольны тем, что я тут нахожусь. Если бы этот простолюдин со своей коровой не подняли на уши весь город... в общем, никто из них не будет чинить вам препятствий\nОбратитесь к губернатору. Представьтесь моим другом, скажите, что мы вместе воевали в Европе - я подтвержу. Кстати, как ваше имя?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "Mtr_officer_5";
		break;
		
		case "Mtr_officer_5":
            dialog.text = ""+GetFullName(pchar)+", замечательно. Идите к дону Диего де Толедо, спросите совета. Он не откажет. И помните, что у вас в распоряжении всего три дня, ибо потом пускаться в погоню за 'Кантавро' будет бессмысленно. Ступайте, и если я буду на свободе - вы получите всю необходимую информацию для того, чтобы обставить скотину Кабаньяса.";
			link.l1 = "Уже иду на приём к губернатору, дон Лопе. Ждите, я приложу все усилия для достижения нашей общей цели.";
			link.l1.go = "Mtr_officer_6";
		break;
		
		case "Mtr_officer_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_6";
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_1", "8");
			SetFunctionTimerCondition("Mtraxx_TimeclearPrison", 0, 0, 4, false); // таймер
		break;
		
		case "Mtr_officer_7":
			pchar.quest.Mtraxx_TimeclearPrison.over = "yes"; //снять таймер
            dialog.text = "Итак, барышник со своей клушей удовлетворились местью, а я прощаюсь с этими казематами. Благодарю, сеньор, вы выполнили свою часть сделки, теперь дело за мной.";
			link.l1 = "Я весь внимание!";
			link.l1.go = "Mtr_officer_8";
		break;
		
		case "Mtr_officer_8":
            dialog.text = "Тогда слушайте. Во время нашего прошлого патрулирования мы отклонились от маршрута из-за шторма и высадились на пляж у пустынных берегов западного Мэйна, недалеко от берега Москитов, для пополнения запаса воды. На одном маленьком пляже мы и нашли буквально россыпь голубого янтаря. Однако я разведал прибрежные воды и пришёл к выводу, что под водой находится целая куча этого минерала. Проблема была в том, что мы не могли долго задерживаться, а вести добычу из-под воды надо при помощи индейцев-ныряльщиков и специальных приспособлений в виде сачка - для вылавливания янтаря из водорослей\nВот мы и решили вернуться позже. В Гаване Эсберто купил пять баркасов, с которых индейцы будут нырять и орудовать сачками, также мы нашли опытных ныряльщиков из краснокожих. Дальше вы знаете - мерзавец кэп избавился от меня и вышел в море. Ищите его шхуну и баркасы у берега Москитов, и не теряйте времени: по моим подсчётам, у вас не больше пяти дней. Надеюсь, вы застанете скотину Кабаньяса за ловлей, отберёте весь янтарь, а его самого проткнёте вашей шпагой. Будьте осторожны: мой бывший кэп весьма искушён как в морском, так и в военном деле. Желаю удачи, сеньор.";
			link.l1 = "И вам того же, дон Лопе. Прощайте!";
			link.l1.go = "Mtr_officer_9";
		break;
		
		case "Mtr_officer_9":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_10";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Roger_1", "12");
			SetFunctionTimerCondition("Mtraxx_TimeclearGulf", 0, 0, 5, false); // таймер
			pchar.quest.mtr_jewelry_gulf.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_gulf.win_condition.l1.location = "Santacatalina";
			pchar.quest.mtr_jewelry_gulf.function = "Mtraxx_JewelryGulf";
			DeleteAttribute(pchar, "GenQuest.PrisonQuestLock");
		break;
		
		// Росарио Гусман
		case "Mtr_rosario":
            dialog.text = "Что вам угодно, сударь?";
			link.l1 = "Я к вам по поводу дона Монторо. Мы с ним давние знакомые, и я был крайне огорчён, узнав, в какую передрягу угодил бедолага Лопе... Его светлость дон Диего де Толедо отправил меня к вам, потому как вы уже пытались сделать что-то для освобождения нашего друга...";
			link.l1.go = "Mtr_rosario_1";
		break;
		
		case "Mtr_rosario_1":
            dialog.text = "Хм... сеньор, для меня это несколько... неожиданно, но я рад видеть друга Лопе Монторо! В последнее время ему постоянно не везло, а тут ещё и это...";
			link.l1 = "Скажите, как ему можно помочь? Негоже благородному идальго гнить среди отбросов общества!";
			link.l1.go = "Mtr_rosario_2";
		break;
		
		case "Mtr_rosario_2":
            dialog.text = "Я вижу человека дела! Помочь нашему несчастному Лопе достаточно просто, но в то же время и... не очень. Я побеседовал с торгашом, с которым Лопе на свою голову имел несчастье сцепиться. Я уговаривал его отозвать свою жалобу и поспособствовать мирному разрешению вопроса, и он согласился пойти навстречу за... сумму в размере пятиста золотых дублонов. Во столько он оценил 'страдания' своей жёнушки и свои собственные. К величайшему сожалению, такой суммой я не располагаю. Мне удалось найти всего половину - двести пятьдесят дублонов.";
			link.l1 = "То есть, если я смогу внести вам ещё двести пятьдесят дублонов, то дон Лопе выйдет на свободу?";
			link.l1.go = "Mtr_rosario_3";
		break;
		
		case "Mtr_rosario_3":
            dialog.text = "Да. Жадный сквалыга пообещал, что заверит весь город в том, что Лопе компенсировал ему моральный ущерб, и походатайствует перед губернатором об отзыве своей жалобы.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 250)
			{
				link.l1 = "У меня есть необходимая сумма прямо сейчас. Вот, возьмите, и пусть этот гнусный мещанин подавится.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "Я постараюсь их добыть как можно быстрее.";
			link.l2.go = "Mtr_rosario_5";
		break;
		
		case "Mtr_rosario_4":
			RemoveItems(pchar, "gold_dublon", 250);
			Log_Info("Вы отдали 250 дублонов");
			PlaySound("interface\important_item.wav");
            dialog.text = "Не верю своим ушам! Сеньор, вас послало само Провидение!";
			link.l1 = "Когда Лопе выйдет на свободу?";
			link.l1.go = "Mtr_rosario_8";
		break;
		
		case "Mtr_rosario_5":
            dialog.text = "Очень рад слышать это, сеньор. Вы настоящий друг Лопе и истинный дворянин.";
			link.l1 = "До встречи!";
			link.l1.go = "Mtr_rosario_6";
		break;
		
		case "Mtr_rosario_6":
            DialogExit();
			AddQuestRecord("Roger_1", "10");
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_7":
            dialog.text = "Вы принесли деньги за дона Лопе?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 250)
			{
				link.l1 = "Да, вот две с половиной сотни дублонов. Пусть этот гнусный мещанин подавится.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "Я ещё работаю над этим.";
			link.l2.go = "Mtr_rosario_7_1";
		break;
		
		case "Mtr_rosario_7_1":
            DialogExit();
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_8":
            dialog.text = "Сегодня вечером я отнесу деньги торгашу-проходимцу, и думаю, что завтра к полудню в тюрьму уже поступит приказ об освобождении нашего друга. Надеюсь, мы соберёмся все втроём немного позже отпраздновать это?";
			link.l1 = "Обязательно, дон Росарио. А сейчас мне пора идти. Увидимся!";
			link.l1.go = "Mtr_rosario_9";
		break;
		
		case "Mtr_rosario_9":
            DialogExit();
			AddQuestRecord("Roger_1", "11");
			npchar.lifeday = 1;
			npchar.dialog.currentnode = "Mtr_rosario_10";
			pchar.quest.mtr_prisoner.win_condition.l1 = "Timer";
			pchar.quest.mtr_prisoner.win_condition.l1.date.hour  = 12;
			pchar.quest.mtr_prisoner.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtr_prisoner.function = "Mtraxx_PrisonerFree";
		break;
		
		case "Mtr_rosario_10":
            dialog.text = "Скоро наш друг будет свободен!";
			link.l1 = "...";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Mtr_rosario_10";
		break;
		
		// Лысый Джеффри
		case "Jeffry":
			pchar.quest.Mtraxx_SilkCPVOver.over = "yes"; //снять прерывание
            dialog.text = "Эй, какого дьявола тебе понадобилось шариться по палубе моего судна? Я никого не звал в гости!";
			link.l1 = "Не шуми, Джеффри. Я от Тиракса по поводу корабельного шёлка.";
			link.l1.go = "Jeffry_1";
		break;
		
		case "Jeffry_1":
            dialog.text = "А-а, ну это меняет дело. Что он там задумал? Я уже перетёр с контрабандистами, они предлагают неплохую цену за товар...";
			link.l1 = "И сколько же они предложили, позволь полюбопытствовать?";
			link.l1.go = "Jeffry_2";
		break;
		
		case "Jeffry_2":
            dialog.text = "По тысяче триста песо за рулон. По-моему, недурственная цена.";
			link.l1 = "Тиракс хочет выручить за рулон не меньше двух десятков золотых. Да, именно дублонов. И озадачил меня вопросом найти такого покупателя.";
			link.l1.go = "Jeffry_3";
		break;
		
		case "Jeffry_3":
            dialog.text = "Ха-ха-ха, ну и повезло же тебе, парень! У Маркуса губа не дура! Ну, давай, ищи... я посмотрю, как это у тебя выйдет.";
			link.l1 = "Чего ржёшь, как армейский тяжеловоз на подъёме? Думаешь, я очень рад этой работе? Лучше бы помог чем-нибудь, подсказал бы чего...";
			link.l1.go = "Jeffry_4";
		break;
		
		case "Jeffry_4":
            dialog.text = "Ладно-ладно, не кипятись, приятель... Ты не виноват в причудах Тиракса, да и не ты один от них страдаешь. Да только чем же я тебе помогу? Товар в магазин не продашь, на таможне не покажешь - остаётся только контрабандистам. Кому ж ещё то, а? Сам подумай.";
			link.l1 = "Эх, да я с самой Эспаньолы об этом только и думаю... Ладно. Тиракс дал мне два месяца на поиск постоянного покупателя. Придётся хотя бы попробовать что-то сделать. А тебе приказал высадиться в ближайшей бухте на берег и заняться кренгованием и ремонтом судна.";
			link.l1.go = "Jeffry_5";
		break;
		
		case "Jeffry_5":
            dialog.text = "Два месяца?! Разрази меня гром! Впрочем, пёс с ним. 'Снэйк' и взаправду нуждается в очистке днища, а то скоро даже барк догнать не сможет. Эх, ну, держитесь, шлюхи французские, команда Лысого Джеффри остаётся в Капстервиле! Ну а тебе, дружище, удачи в твоих бесполезных поисках. Если ты всё же сумеешь найти идиота, готового платить цену Маркуса за этот треклятый шёлк - ты знаешь, где меня искать.";
			link.l1 = "Постой! Дай мне один рулон шёлка. Надо же показывать товар лицом.";
			link.l1.go = "Jeffry_6";
		break;
		
		case "Jeffry_6":
            dialog.text = "Нет проблем. Я пришлю на твою посудину шлюпкой.";
			link.l1 = "Хорошо. Ещё увидимся!";
			link.l1.go = "Jeffry_7";
		break;
		
		case "Jeffry_7":
            DialogExit();
			AddQuestRecord("Roger_2", "3");
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
			pchar.questTemp.Mtraxx = "silk_2";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			SetFunctionTimerCondition("Mtraxx_SilkTimeOver", 0, 0, 61, false); // таймер
		break;
		
		case "Jeffry_8":
            dialog.text = "Тебе что-то ещё от меня нужно, парень?";
			link.l1 = "Пока ничего, наверное...";
			link.l1.go = "Jeffry_8_1";
		break;
		
		case "Jeffry_8_1":
            DialogExit();
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
		break;
		
		case "Jeffry_9":
			pchar.quest.Mtraxx_SilkTimeOver.over = "yes";
            dialog.text = "Ну, как успехи, приятель?";
			link.l1 = "Отлично, дружище. Я нашёл покупателя на шёлк. Цена - 25 дублонов за рулон. Так что Тиракс будет доволен.";
			link.l1.go = "Jeffry_10";
		break;
		
		case "Jeffry_10":
            dialog.text = "Разрази меня гром! Ну ты и ловкий малый! И как тебе это удалось, а?";
			link.l1 = "Долгая история, Джеффри. Теперь слушай и запоминай: тебе надо прибыть между ближайшим 10 и 15 числом к Ямайке, на мыс Негрил. По ночам тебя будут ждать на берегу люди покупателя. Пароль - 'Лионский купец'. Всё запомнил? Повтори.";
			link.l1.go = "Jeffry_11";
		break;
		
		case "Jeffry_11":
            dialog.text = "Между 10 и 15 числами, ночью, Ямайка, мыс Негрил, пароль - 'Лионский купец'... Надо сказать казначею, чтобы записал, он у нас на судне один грамотей, ха-ха!";
			link.l1 = "Сто рулонов в трюме у тебя есть?";
			link.l1.go = "Jeffry_12";
		break;
		
		case "Jeffry_12":
            dialog.text = "Есть и больше.";
			link.l1 = "Отлично. Выходи в море. Не подведи меня!";
			link.l1.go = "Jeffry_13";
		break;
		
		case "Jeffry_13":
            dialog.text = "Не дрейфь, приятель, всё будет сделано, как надо.";
			link.l1 = "Удачи, Джеффри. Может, ещё увидимся.";
			link.l1.go = "Jeffry_14";
		break;
		
		case "Jeffry_14":
            DialogExit();
            AddQuestRecord("Roger_2", "22");
			pchar.questTemp.Mtraxx = "silk_14"; // к Тираксу
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_12";
			pchar.quest.mtraxx_hide_jeffry.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_hide_jeffry.function = "Mtraxx_SilkHideJeffry";
		break;
		
		case "Jeffry_15":
            dialog.text = "Хо, кого я вижу! Да это же хитрюга Чарли Принц собственной персоной! Здорово-здорово!";
			link.l1 = "Ха, Лысый Джеффри! Привет, приятель. Чарли Принц? Хех!..";
			link.l1.go = "Jeffry_15x";
		break;
		
		case "Jeffry_15x":
            dialog.text = "Что, впервой услышал своё второе имя? Так тебя теперь кличут в Ла Веге.";
			link.l1 = "Ну, Чарли - понятно, а почему 'Принц'?";
			link.l1.go = "Jeffry_15y";
		break;
		
		case "Jeffry_15y":
            dialog.text = "Да ты у нас один в Ла Веге благородный месье голубых кровей, ха-ха-ха!.. Как поживаешь? К Паскуале заходил? Затарился в рейс у этого четырёхглазого пройдохи?";
			link.l1 = "Да чтоб я хоть раз ещё что-нибудь купил в этом магазине!..";
			link.l1.go = "Jeffry_16";
		break;
		
		case "Jeffry_16":
            dialog.text = "Кха! И чем тебе старина Вуазье не угодил? Продал солонину по цене рома? Так это он умеет, ха-ха-ха!";
			link.l1 = "Хуже! Я по его наводке сначала еле нашёл голландский караван с чёрным деревом, потом с трудом взял торговца, затем два десятка крыс в трюме передушил, чтобы не погрызли товар, а этот жулик очкастый заплатил мне по сто пятьдесят песо за единицу товара. Сто пятьдесят песо за штуку чёрного дерева, Джеффри!";
			link.l1.go = "Jeffry_17";
		break;
		
		case "Jeffry_17":
            dialog.text = "Хочешь, я утешу тебя, приятель? Ты не один такой. Вуазье с десяток ребят окрутил. Тебе он ещё хорошо заплатил, другим и такого не доставалось. Я за его 'заказы' не берусь, даже если голяк полный. Да и другие парни тоже. Вот он и окучивает тех, кто не знает особенностей его 'торговли'.";
			link.l1 = "Спасибо, друг, мне стало гораздо легче от знания того, что я не один такой недотёпа!.. Ничего, на этот раз Вуазье перехитрил самого себя. Я ему этого так не оставлю - он заплатит гораздо дороже.";
			link.l1.go = "Jeffry_18";
		break;
		
		case "Jeffry_18":
            dialog.text = "Эй-эй-эй! Принц, ты это... не горячись. Четырёхглазый - свой человек, и если ты надумаешь его грабануть - проблемы от Маркуса тебе обеспечены. Скажи, это ведь Тиракс отправил тебя к Вуазье, так?";
			link.l1 = "Гм. Ну да...";
			link.l1.go = "Jeffry_19";
		break;
		
		case "Jeffry_19":
            dialog.text = "Так вот... (понижая голос) Поговаривают, что очкарик делится с Маркусом. Сечёшь? Потому флейты Вуазье или его самого никто из пиратов не рискнет даже пальцем тронуть. Но я тебе этого не говорил.";
			link.l1 = "Я учту это. Спасибо, что предупредил, Джеффри. Пока и удачи!";
			link.l1.go = "Jeffry_20";
		break;
		
		case "Jeffry_20":
            dialog.text = "И тебе попутного ветра, приятель.";
			link.l1 = "...";
			link.l1.go = "Jeffry_21";
		break;
		
		case "Jeffry_21":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 15.0);
			AddQuestRecord("Roger_4", "10");
			CloseQuestHeader("Roger_4");
			QuestSetCurrentNode("Terrax", "mtraxx_34"); // релиз-правка
			bDisableFastReload = false;
			pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират
		break;
		
		case "Jeffry_22":
            dialog.text = "Хо, Принц! А я-то недоумеваю: кто тут в джунглях фейерверк устроил! Грешным делом подумал на испанцев - целый отряд мушкетёров с собой взял.";
			link.l1 = "Джеффри?! И ты тут? Но как? Тоже купил карту сокровищ?";
			link.l1.go = "Jeffry_23";
		break;
		
		case "Jeffry_23":
            dialog.text = "Приятель, я на такую чепуху, как карты сокровищ, деньги не трачу. Мне принесли дневник одного путешественника, где подробно описывалась дорога к этим развалинам. Тут, в подземелье, должно быть золото, ещё со старых времён.";
			link.l1 = "Кто принёс дневник?";
			link.l1.go = "Jeffry_24";
		break;
		
		case "Jeffry_24":
            dialog.text = "Да нищеброд какой-то. На выпивку ему не хватало сотни песо. Мой казначей прочёл содержимое дневника, пересказал - ну я и решил проверить.";
			link.l1 = "Нищий этот на Тортуге обретался?";
			link.l1.go = "Jeffry_25";
		break;
		
		case "Jeffry_25":
            dialog.text = "Нет. На Барбадосе. Принц, ты что так взволновался?";
			link.l1 = "Не нравится мне всё это. Не верю я в чудесные совпадения. Неужели отец Камиллы вёл дневник? Не верю...";
			link.l1.go = "Jeffry_26";
		break;
		
		case "Jeffry_26":
            dialog.text = "Кто такая Камилла?";
			link.l1 = "Девка, продавшая мне за двести дублонов карту, ведущую сюда! На Тортуге!";
			link.l1.go = "Jeffry_27";
		break;
		
		case "Jeffry_27":
            dialog.text = "Хех... Принц, да не ломай ты голову. Пошли сокровища искать.";
			link.l1 = "А что их искать? Нашёл уже... Они дальше, ярусом ниже, в подземелье, в закутке за железной решёткой. Взламывать придётся. Но это не всё, Лысый! Тесак Пелли тоже был тут!";
			link.l1.go = "Jeffry_28";
		break;
		
		case "Jeffry_28":
            dialog.text = "Тесак? Вот это да! И где он?";
			link.l1 = "Внизу... лежит. Я встретил его у сокровищ. Он словно обезумел: начал кричать - 'всё моё, всё моё, никому не дам', а потом схватился за саблю и напал на меня со своими клевретами. Пришлось защищаться...";
			link.l1.go = "Jeffry_29";
		break;
		
		case "Jeffry_29":
            dialog.text = "Гм... Пелли вечно не везло с деньгами, а тут, видимо, увидел кучу золота и крыша поехала...";
			link.l1 = "Видимо... Джеффри, но это не самое главное, как ты не понимаешь! Мы все трое пришли в это подземелье! Все трое получили наводку! Ты считаешь, это просто так? Совпадение?";
			link.l1.go = "Jeffry_30";
		break;
		
		case "Jeffry_30":
            dialog.text = "Ты сокровища видел?";
			link.l1 = "Да. Собственными глазами. Несколько огромных сундуков с золотыми монетами и слитками.";
			link.l1.go = "Jeffry_31";
		break;
		
		case "Jeffry_31":
            dialog.text = "Ну так и что ты паришься, Принц? Вот если бы их не было - был бы другой разговор. Пошли, показывай, как пройти. Посмотрим, что там за решётка.";
			link.l1 = "Ладно... Идём.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionWithJeffry");
		break;
		
		case "Jeffry_32":
            dialog.text = "Да, есть на что посмотреть! Целая куча золота! Было от чего Тесаку голову потерять... Нам здорово повезло, Принц! Как думаешь - сколько здесь?";
			link.l1 = "Много. Точнее мы узнаем, когда сломаем решётку. Но для этого нужны инструменты и приспособления, а взять их можно только на корабле. Нужно возвращаться.";
			link.l1.go = "Jeffry_33";
		break;
		
		case "Jeffry_33":
            dialog.text = "Да, решётка крепкая, голыми руками её не возьмешь. Ты прав, приятель: нужно идти за инструментами. Хех! Возвращаемся!";
			link.l1 = "...";
			link.l1.go = "Jeffry_34";
		break;
		
		case "Jeffry_34":
            DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionJeffryMushketer", 0.1);
		break;
		
		case "Jeffry_35":
            dialog.text = RandSwear()+"Вот ведь где криворукий мазила!..";
			link.l1 = "Ах ты, гад!..";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionJeffryFight");
		break;
		
		// Билли Сипатый
		case "Billy":
			pchar.quest.Mtraxx_BillySeaTimeOver.over = "yes"; //снять таймер
			PlaySound("VOICE\Russian\citizen\Moryaki v Gorode-10.wav");
            dialog.text = "Поглоти меня акула, если на 'Летучей рыбе' такое случалось за последний год... у меня на палубе - гость! Какая нужда привела тебя, приятель, на мою обглоданную крабами малютку?";
			link.l1 = "Приветствую! Это тебя кличут Сипатым Билли?";
			link.l1.go = "Billy_1";
		break;
		
		case "Billy_1":
            dialog.text = "А что, по голосу трудно было догадаться, кэп? Да, я и есть Билли Сипатый, и когда-то при звуке моего голоса английские и испанские торговцы клали себе в штаны. Да, вот были времена!.. А теперь старый Билли доживает свой век у берегов своего любимого острова на своём драгоценном баркасе...";
			link.l1 = "Я к тебе по делу, Билли. Мне сказали, что ты знаешь всё, что творится у побережья Ямайки. Это так?";
			link.l1.go = "Billy_2";
		break;
		
		case "Billy_2":
            dialog.text = "Ну, раз говорят - значит, так оно и есть... Но ты не тяни краба за клешню - выкладывай, зачем явился?";
			link.l1 = "Хорошо. В Порт-Ройяле есть корабельных дел мастер. Он занимается улучшением корыт на скорость и ход в бейдевинд, для чего закупает редкий товар - корабельный шёлк. Так как свободная торговля этим материалом в Порт-Ройяле невозможна, он нашёл себе нелегального поставщика. Вот я и хочу разузнать - кто и как ему привозит шёлк?";
			link.l1.go = "Billy_3";
		break;
		
		case "Billy_3":
            dialog.text = "Хо-хо, так вот оно что! Работаешь на полковника Дойли, сынок?";
			link.l1 = "Начинается! Нет, я работаю с Маркусом Тираксом. А надо мне всё это потому, что Тиракс желает сотрудничества в плане купли-продажи шёлка, а шельма корабел боится иметь дело с незнакомыми людьми...";
			link.l1.go = "Billy_4";
		break;
		
		case "Billy_4":
            dialog.text = "О, так ты работаешь на хранителя Кодекса! Это меняет дело... если ты не врёшь, конечно. Впрочем, особой заботы до мастера дел корабельных мне нет: посадят одного - придёт другой. Меня больше волнует то, что моя старушка 'Летучая рыба' совсем прохудилась... Старый Билли устал латать прорехи в её парусе и вычёрпывать воду при свежем ветре\nПригони мне, сынок, из Порт-Ройяля новый баркас. И ещё к нему впридачу рулон того самого корабельного шёлка - Билли сделает из него отличный парус и сможет оставлять с носом таможенные патрули, хе-хе. А взамен я раскрою тебе все подробности того, как корабел получает шёлк. Билли знает!";
			link.l1 = "Тебе нужен новый баркас? Давай я дам тебе нужную сумму деньгами и сам его купишь. Дам с лихвой...";
			link.l1.go = "Billy_5";
		break;
		
		case "Billy_5":
            dialog.text = "Э-э, кэп, старому Билли вход в Порт-Ройял заказан. Меня слишком хорошо там помнят, и мне совсем не хочется сушиться на солнышке на пирсе или на каменной арке среди рифов. Так что, сынок, жду от тебя новенький баркас у мыса Негрил. И шёлк не забудь! Ждать тебя я буду три дня, считая сегодняшний. Если не придёшь послезавтра до полуночи - я отчаливаю.";
			link.l1 = "Хорошо, Билли. Будет тебе и новый баркас, и шёлк на парус. Я скоро вернусь.";
			link.l1.go = "Billy_6";
		break;
		
		case "Billy_6":
            dialog.text = "Билли будет ждать тебя на бережке, кэп. До скорого свидания!";
			link.l1 = "...";
			link.l1.go = "Billy_7";
		break;
		
		case "Billy_7":
            DialogExit();
			AddQuestRecord("Roger_2", "8");
			npchar.dialog.currentnode = "Billy_8";
			pchar.questTemp.Mtraxx = "silk_7";
			SetFunctionTimerCondition("Mtraxx_BillyTimeOver", 0, 0, 3, false); // таймер
			pchar.quest.mtr_billy_coast.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtr_billy_coast.win_condition.l1.location = pchar.location;
			pchar.quest.mtr_billy_coast.function = "Mtraxx_BillyOnCoast";
			locations[FindLocation("shore35")].DisableEncounters = true; //энкаутеры закрыть
			npchar.DontDeskTalk = true;
		break;
		
		case "Billy_8":
            dialog.text = "Как? Ты уже пригнал мне баркас?";
			link.l1 = "Шутник ты, Билли...";
			link.l1.go = "exit";
		break;
		
		case "Billy_9":
			PlaySound("VOICE\Russian\citizen\Moryaki v Gorode-07.wav");
            dialog.text = "Ну что, кэп, как там мой новый баркас с шёлковым парусом?";
			if(Companion_CheckShipType(SHIP_TARTANE) && GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0)
			{
				link.l1 = "Твой заказ выполнен, Сипатый. Баркас в бухте, рулон шёлка в его трюме. Можешь топить свою старую скорлупу.";
				link.l1.go = "Billy_11";
			}
			else
			{
				link.l1 = "Я ещё работаю над этим. Жди.";
				link.l1.go = "Billy_10";
			}
		break;
		
		case "Billy_10":
			DialogExit();
			npchar.dialog.currentnode = "Billy_9";
		break;
		
		case "Billy_11":
			pchar.quest.Mtraxx_BillyTimeOver.over = "yes"; //снять прерывание
            dialog.text = "Клянусь громом, это лучшая новость за последние три года в жизни старого Билли! Хех, по такому поводу не грех и к бутылочке приложиться...";
			link.l1 = "Это без меня. Так что там по поводу поставщиков шёлка?";
			link.l1.go = "Billy_12";
		break;
		
		case "Billy_12":
            dialog.text = "Жаль, а так бы промочили горло за мою новую 'Летучую рыбу'! Ну да ладно... Слушай внимательно, сынок\nВ середине каждого месяца, числа так десятого-пятнадцатого, ночью, в бухту Портленд прибывает одна и та же бригантина под английским флагом. Но не пить мне рому до конца дней, если это английское судно! Оно носит имя 'Утрехт', и прибывает с юго-востока, где находится голландский остров Кюрасао. Как ты сам понимаешь, кэп, это голландцы\nНа берегу их встречает одна и та же группа людей во главе со старшим мастером пройдохи корабела из Порт-Рояйля. Вот им-то матросы с бригантины и сгружают шёлк. Это точно шёлк - никакую другую материю голландцы не наматывают на стержни из пробки.";
			link.l1 = "И что - так каждый месяц и происходит?";
			link.l1.go = "Billy_13";
		break;
		
		case "Billy_13":
            dialog.text = "Да, сынок, за истекший год не было ни разу, чтобы бригантина не пришла на это рандеву. Так что если ты хочешь побеседовать с угрюмыми бородачами с 'Утрехта', или с мастеровым из города - карауль их у бухты Портленд с десятого по пятнадцатое каждого месяца по ночам - не прогадаешь, клянусь шёлковым парусом моего нового баркаса.";
			link.l1 = "Хех! Похоже, мои деньги были потрачены не зря. Удачи, Билли, да смотри, не попадись патрулю на своём новом судне, когда повезёшь контрабанду - я очень расстроюсь.";
			link.l1.go = "Billy_14";
		break;
		
		case "Billy_14":
            dialog.text = "Ха, старый Билли ещё не вышел в тираж, акулий зуб тебе в печёнку! А теперь бывай, кэп. Лёгкой добычи!";
			link.l1 = "Тебе того же, Билли!";
			link.l1.go = "Billy_15";
		break;
		
		case "Billy_15":
            DialogExit();
			npchar.lifeday = 0;
			pchar.questTemp.Mtraxx = "silk_8";
			chrDisableReloadToLocation = true;//закрыть локацию
			locations[FindLocation("shore35")].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			AddDialogExitQuestFunction("Mtraxx_BillyTakeShip");
			AddQuestRecord("Roger_2", "9");
			// ставим прерывание на 10-15 число
			int month = 0;
			pchar.questTemp.Mtraxx.month = 0;
			if (GetDataDay() > 12)
			{
				month = 1;
				pchar.questTemp.Mtraxx.month = 1;
			}
			int hour = 1+rand(2);
			int day = 13+rand(2);
			pchar.quest.mtr_silk_smuggler.win_condition.l1 = "Timer";
			pchar.quest.mtr_silk_smuggler.win_condition.l1.date.hour  = hour;
			pchar.quest.mtr_silk_smuggler.win_condition.l1.date.day   = day;
			pchar.quest.mtr_silk_smuggler.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
			pchar.quest.mtr_silk_smuggler.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
			pchar.quest.mtr_silk_smuggler.win_condition.l2 = "location";
			pchar.quest.mtr_silk_smuggler.win_condition.l2.location = "Jamaica";
			pchar.quest.mtr_silk_smuggler.function = "Mtraxx_SilkCreateSmuggler";
			// таймер
			pchar.quest.mtr_silk_smuggler_over.win_condition.l1 = "Timer";
			pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.hour  = hour+2;
			pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.day   = day;
			pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
			pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
			pchar.quest.mtr_silk_smuggler_over.function = "Mtraxx_SilkSmugglerOver";
		break;
		
		// мастеровой с верфи Порт-Рояля
		case "Mtr_acceptor_fight":
            LAi_group_Delete("EnemyFight");
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation("shore36")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mtr_acceptor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_SilkWrongTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Mtr_acceptor":
            dialog.text = "Эй, моряк, ты ведь только что прибыл на Ямайку, так?";
			link.l1 = "Хм. Ну да. А в чём собственно дело?";
			link.l1.go = "Mtr_acceptor_1";
		break;
		
		case "Mtr_acceptor_1":
            dialog.text = "С моря слышны звуки канонады, но в этой треклятой мгле ничего не разглядеть, даже в подзорную трубу. Что там происходило, не видал?";
			link.l1 = "А как же, видал. Какая-то бригантина сцепилась с английским патрульным корветом. Он так её разделывал, что голландец улепётывал во все лопатки, выбрасывая из трюмов груз.";
			link.l1.go = "Mtr_acceptor_2";
		break;
		
		case "Mtr_acceptor_2":
            dialog.text = "А с чего ты решил, что это голландец? Ни один из них, если он в здравом уме, конечно, не станет приближаться к Порт-Ройялю на такое расстояние...";
			link.l1 = "Да флаг-то был английский, но где ты видел английское судно с названием 'Утрехт'? Голландцы это были, приятель, и скорее всего контрабандисты. Видать, патруль их тут караулил, больно резво в атаку на них пошёл, без разговоров.";
			link.l1.go = "Mtr_acceptor_3";
		break;
		
		case "Mtr_acceptor_3":
            dialog.text = "Вот проклятие!.. Кхм...";
			link.l1 = "Похоже, эти новости тебя крепко расстроили...";
			link.l1.go = "Mtr_acceptor_4_1";
			link.l2 = "Ты ждал эту бригантину здесь?";
			link.l2.go = "Mtr_acceptor_7";
		break;
		
		case "Mtr_acceptor_4_1":
            dialog.text = "С чего это ты взял, приятель?";
			link.l1 = "Полно тебе. Я тебя знаю. Ты мастеровой с верфи Порт-Ройяля, и ждёшь товар с этой бригантины.";
			link.l1.go = "Mtr_acceptor_wrong";
			link.l2 = "У тебя на физиономии это написано.";
			link.l2.go = "Mtr_acceptor_4_2";
		break;
		
		case "Mtr_acceptor_wrong":
            dialog.text = "Аргх! Ребята, это переодетый патруль! Валим его и бежим!";
			link.l1 = "Карамба!! Ты не так...";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_4_2":
            dialog.text = "Грубишь, 'морской волк'? Ты это поаккуратнее в выражениях, а не то...";
			link.l1 = "Да хватит тебе уже. По тебе и в самом деле видно, что ты огорчён. Ты ждал этого голландца, что ли?";
			link.l1.go = "Mtr_acceptor_4_3";
			link.l2 = "А не то что? Ты меня жизни поучишь?";
			link.l2.go = "Mtr_acceptor_6";
		break;
		
		case "Mtr_acceptor_4_3":
            dialog.text = "А даже если и так, то тебе какое дело?";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l1 = "Да мне-то особого дела нет. Тебе его ждать здесь целую вечность, а не мне.";
				link.l1.go = "Mtr_acceptor_4_4";
			}
			link.l2 = "Самое прямое. Я знаю, что было в трюме бригантины. Корабельный шёлк. Ты ведь за ним сюда пришёл, я угадал?";
			link.l2.go = "Mtr_acceptor_wrong";
		break;
		
		case "Mtr_acceptor_4_4":
            dialog.text = "Кхм... Почему это - целую вечность?";
			link.l1 = "Да потому что раньше этого срока с дна морского не всплывают. Потопил твою бригантину корвет патрульный, приятель. Вот так-то. Но кому война, а кому и мать родна - вот мне сегодня повезло. Я неплохо заработаю на этом утонувшем голландце.";
			link.l1.go = "Mtr_acceptor_4_5";
		break;
		
		case "Mtr_acceptor_4_5":
            dialog.text = "Очень интересно, и каким образом?";
			link.l1 = "Да продам то, что он выбросил из своих трюмов, когда пытался уйти. Что-то утонуло, а вот дорогущий шёлк корабельный плавал, как г... кхм, пробка. Я его собрал, а завтра пойду в город и договорюсь о продаже. Вот уж никогда не знаешь, где найдёшь, где потеряешь, ха-ха-ха! Ладно, приятель, бывай, дела у меня.";
			link.l1.go = "Mtr_acceptor_4_6";
		break;
		
		case "Mtr_acceptor_4_6":
            dialog.text = "Стой!";
			link.l1 = "Карамба! Чего тебе ещё?";
			link.l1.go = "Mtr_acceptor_4_7";
		break;
		
		case "Mtr_acceptor_4_7":
            dialog.text = "Сколько ты собрал шёлка в море?";
			link.l1 = "А тебе какое дело? Это мой шёлк! Или ты ищейка губернаторская, а? Тогда я тебя...";
			link.l1.go = "Mtr_acceptor_4_8";
		break;
		
		case "Mtr_acceptor_4_8":
            dialog.text = "Да не хватайся ты за саблю, морячок. Не ищейка я, с верфи мы... Шёлк этот нам везли, да, как вижу, не довезли. Я куплю его у тебя, он мне позарез нужен.";
			link.l1 = "Вот как? Занятно... И почём купишь?";
			link.l1.go = "Mtr_acceptor_4_9";
		break;
		
		case "Mtr_acceptor_4_9":
			i = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "По две с половиной тысячи за рулон. Это очень хорошая цена, никто тебе больше не даст.";
			link.l1 = "Похоже, птица-удача повернулась ко мне клювом! Я собрал "+FindRussianQtyString(i)+". Деньги на бочку, и я отдам приказ свезти его на берег.";
			if (i > 80) link.l1.go = "Mtr_acceptor_4_11";
			else link.l1.go = "Mtr_acceptor_4_10";
		break;
		
		case "Mtr_acceptor_4_10":
            dialog.text = "По рукам!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilk");
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		case "Mtr_acceptor_4_11":
            dialog.text = "Хм... Йоахим должен был привезти восемьдесят рулонов - ты никак не мог подобрать в море столько шёлка... значит, ты или пытаешься надуть меня, или... ты сам шпик! Ребята, валим его и бежим!";
			link.l1 = "Карамба!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_5":
            dialog.text = "";
			link.l1 = "Хорошая сделка, дружище! Да что ты такой хмурый? Голландца потопили? Да и пёс с ним!";
			link.l1.go = "Mtr_acceptor_5_1";
		break;
		
		case "Mtr_acceptor_5_1":
            dialog.text = "Ага, как же... Это был наш постоянный поставщик. Где мы теперь шёлк брать будем? Нам вечно его не хватает, а всю торговлю им полковник Дойли держит под контролем. Эх...";
			link.l1 = "Хм... Братишка, а ведь я могу помочь тебе.";
			link.l1.go = "Mtr_acceptor_5_2";
		break;
		
		case "Mtr_acceptor_5_2":
            dialog.text = "Да ну?! И как же? Будешь возить нам каждый месяц по сотне рулонов шёлка?";
			link.l1 = "Я, наверное, нет, а вот Маркус Тиракс - да. Слыхал про такого?";
			link.l1.go = "Mtr_acceptor_5_3";
		break;
		
		case "Mtr_acceptor_5_3":
            dialog.text = "Кха! Ты что - пират?";
			link.l1 = "Нет, я просто веду с ним кое-какие делишки. И точно знаю, что Маркус постоянно 'получает' партии корабельного шёлка и продает их, но точно не по 2500 песо. А если ты ещё будешь платить ему не песо, а дублонами, по 25 золотых за рулон - он тебя завалит шёлком, не сомневайся.";
			link.l1.go = "Mtr_acceptor_5_4";
		break;
		
		case "Mtr_acceptor_5_4":
            dialog.text = "Очень интересно... Маркус Тиракс, говоришь?.. Дублонами?..";
			link.l1 = "Да не бойся ты, приятель, какая тебе разница, у кого товар покупать? Деньги не пахнут. А песо на дублоны обменяешь у ростовщика. Ну так что, замолвить за тебя словечко перед Тираксом? Я всё равно буду заходить в Ла Вегу.";
			link.l1.go = "Mtr_acceptor_5_5";
		break;
		
		case "Mtr_acceptor_5_5":
            dialog.text = "Хорошо. Давай попробуем с ним договориться. Условия такие: партия шёлка в сто рулонов, привозить сюда... нет, лучше на мыс Негрил, там безопаснее, каждый месяц между 10 и 15 числом, ночью. Пароль - 'Лионский купец'.";
			link.l1 = "Заметано, братишка. Ну и удачный же рейс выдался! Тиракс мне за такого покупателя дублончиков отсыпет, и не одну пригоршню! Ха-ха-ха! Ладно, мне пора. Жди в следующем месяце посудину от Тиракса. Привет семье!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
		break;
		
		case "Mtr_acceptor_6":
            dialog.text = "После того, как мы тебя поучим вежливости, учить жизни уже не понадобится.";
			link.l1 = "Строишь из себя крутого, плотник? Ладно, жди себе дальше свою бригантину. Только вряд ли дождёшься.";
			link.l1.go = "Mtr_acceptor_6_1";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Эй, учитель, сейчас мы посмотрим, кто кого поучит!";
				link.l2.go = "Mtr_acceptor_6_2";
			}
		break;
		
		case "Mtr_acceptor_6_1":
            dialog.text = "Плотник? Чёрт возьми, как ты догадался? Кха! А-ать, ребята, это переодетый патруль! Валим его и бежим!";
			link.l1 = "Карамба!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_6_2":
            dialog.text = "Отстань, рыбья чешуя, не до тебя сейчас. Проваливай!";
			link.l1 = "А чем ты так занят? Ждешь голландца? Впрочем - жди, жди, тебе ещё целую вечность ждать.";
			link.l1.go = "Mtr_acceptor_4_4";
		break;
		
		case "Mtr_acceptor_7":
            dialog.text = "С чего ты взял? Просто интересно стало, кто там пальбу устроил...";
			link.l1 = "Понятно. Но если ты всё-таки ждёшь именно эту бригантину, можешь идти домой. Не придёт она. Потопил её корвет патрульный. Я видел в трубу развязку боя.";
			link.l1.go = "Mtr_acceptor_7_1";
		break;
		
		case "Mtr_acceptor_7_1":
            dialog.text = "Да что ты заладил, как попугай? Мы никого не ждём, и...";
			link.l1 = "Послушай, да мне-то всё равно. Я не патруль из города, мне на твои дела наплевать, да и сам не ангел. Возишь контрабанду - вози себе на здоровье. Просто предупредил тебя. Удачи, приятель.";
			link.l1.go = "Mtr_acceptor_7_2";
		break;
		
		case "Mtr_acceptor_7_2":
            dialog.text = "Постой... Ты уверен, что 'Утрехт' потоплен?";
			link.l1 = "На все сто. Он пытался уйти, выбросил из трюмов весь товар - не пожалел даже дорогущего корабельного шёлка, но корвет по ветру быстрее идет. Нагнал он его и потопил. Кормит рыб твой голландец сейчас.";
			link.l1.go = "Mtr_acceptor_7_3";
		break;
		
		case "Mtr_acceptor_7_3":
            dialog.text = "Вот незадача... и что же нам теперь без шёлка делать? Карамба!..";
			link.l1 = "Так тебе шёлк корабельный нужен?";
			link.l1.go = "Mtr_acceptor_7_4";
		break;
		
		case "Mtr_acceptor_7_4":
            dialog.text = "А что, у тебя он есть на продажу?";
			link.l1 = "У меня нет, но я знаю человека, который ищет покупателя на этот товар. Постоянного покупателя. Ну и не скупого, конечно.";
			link.l1.go = "Mtr_acceptor_7_5";
		break;
		
		case "Mtr_acceptor_7_5":
            dialog.text = "Что за человек?";
			link.l1 = "Маркус Тиракс, барон Ла Веги. Он постоянно 'получает' партии корабельного шёлка и продает их. Думаю, и тебе продаст, если цена его устроит.";
			link.l1.go = "Mtr_acceptor_7_6";
		break;
		
		case "Mtr_acceptor_7_6":
            dialog.text = "Так ты пират?";
			link.l1 = "А тебе какое дело? Я в твои дела не лезу, а ты не лезь в мои. Хочешь - сведу тебя с Тираксом, если ты не трусишь. Нет - счастливо оставаться.";
			link.l1.go = "Mtr_acceptor_7_7";
		break;
		
		case "Mtr_acceptor_7_7":
            dialog.text = "Хорошо-хорошо, не кипятись. Хочу, конечно. Только тебе какая от этого выгода?";
			link.l1 = "Если ты предложишь хорошую цену за товар, я удержу с Маркуса кругленькую сумму за информацию о тебе. Так сколько ты готов платить?";
			link.l1.go = "Mtr_acceptor_7_8";
		break;
		
		case "Mtr_acceptor_7_8":
            dialog.text = "Двадцать пять дублонов золотом за рулон. Больше никто не заплатит, будь уверен.";
			link.l1 = "Двадцать пять золотых? Хм. Неплохо. Пожалуй, Тираксу придётся раскошелиться за такого покупателя. По рукам, я договорюсь с ним. Но если ты меня обманул с ценой - пеняй на себя.";
			link.l1.go = "Mtr_acceptor_7_9";
		break;
		
		case "Mtr_acceptor_7_9":
            dialog.text = "Не переживай, мы люди честные. Условия сделки такие: партия шёлка в сто рулонов, привозить сюда... нет, лучше на мыс Негрил - там безопаснее, каждый месяц между 10 и 15 числом, ночью. Пароль - 'Лионский купец'.";
			link.l1 = "Хорошо. Жди в следующем месяце первую партию.";
			link.l1.go = "Mtr_acceptor_7_10";
		break;
		
		case "Mtr_acceptor_7_10":
            dialog.text = "Передай Тираксу, что в первый раз может привезти больше - в этом месяце мы без товара остались.";
			link.l1 = "Передам. А теперь удачи и бывай, братишка.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		// Тесак Пелли
		case "Pelly":
            dialog.text = "Какими ветрами на борту моей посудины, приятель?";
			link.l1 = "Здорово, Тесак. Я от Маркуса Тиракса. Нас ждёт поход к Маракайбо.";
			link.l1.go = "Pelly_1";
		break;
		
		case "Pelly_1":
            dialog.text = "А-а, ну наконец-то. Значит, это ты - мой босс на это плавание. Хорошо. Как звать моего нового адмирала?";
			link.l1 = "Капитан "+GetFullName(pchar)+".";
			link.l1.go = "Pelly_2";
		break;
		
		case "Pelly_2":
            dialog.text = "Какие будут указания, адмирал "+GetFullName(pchar)+"?";
			link.l1 = "Отправляемся к озеру Маракайбо. Идём порознь. Я пойду в порт к испанцам, ты же не светись, в озеро входи ночью и отдай якорь в бухте Гуахира. Судно постарайся поставить неприметно, на берегу организуй маленький лагерь и жди. Когда надо - я сам к тебе приду, по морю или по суше. Будь наготове.";
			link.l1.go = "Pelly_3";
		break;
		
		case "Pelly_3":
            dialog.text = "Есть, сэр!";
			link.l1 = "Сколько времени тебе потребуется на путь к бухте Гуахира?";
			link.l1.go = "Pelly_4";
		break;
		
		case "Pelly_4":
            dialog.text = "М-м-м... Неделя, адмирал. День раньше, день позже, если не будет мёртвого штиля по пути.";
			link.l1 = "Хорошо. Тогда не будем терять времени. Встретимся в бухте Гуахира.";
			link.l1.go = "Pelly_5";
		break;
		
		case "Pelly_5":
            dialog.text = "Так точно, адмирал!";
			link.l1 = "...";
			link.l1.go = "Pelly_6";
		break;
		
		case "Pelly_6":
            DialogExit();
			AddQuestRecord("Roger_3", "3");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			Mtraxx_PlantContinue();
		break;
		
		case "Pelly_7":
            dialog.text = "Какие будут указания, адмирал?";
			link.l1 = "Пока никаких. Я работаю над нашим делом.";
			link.l1.go = "Pelly_wait";
			if (pchar.questTemp.Mtraxx == "plant_3")
			{
				link.l1 = "Приготовь на берегу большой сундук. В него мы будем собирать оружие для наших пленников.";
				link.l1.go = "Pelly_8";
			}
			if (pchar.questTemp.Mtraxx == "plant_8" && pchar.location.from_sea == "Shore37")
			{
				link.l1 = "Сворачивай лагерь, собирай штурмовой отряд. Выступаем в час ночи - операция назначена на три часа.";
				link.l1.go = "Pelly_11";
			}
		break;
		
		case "Pelly_wait":
             DialogExit();
			 npchar.dialog.currentnode = "Pelly_7";
		break;
		
		case "Pelly_8":
            dialog.text = "Хо! Мы устроим бунт на плантации, да, адмирал? Гром и молния! Ещё и золотишком разживёмся!..";
			link.l1 = "Сундук на берег, Тесак.";
			link.l1.go = "Pelly_9";
		break;
		
		case "Pelly_9":
            dialog.text = "Будет сделано, адмирал!";
			link.l1 = "...";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_10":
            DialogExit();
			npchar.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_4";
			pchar.questTemp.Mtraxx.Chest = "true";
			// подгружаем сундук в локу и меняем локаторы
			int n = Findlocation("Shore37");
			Locations[n].models.always.locators = "shore03_q_locators";
			locations[n].models.always.chest = "chest_quest";
			Locations[n].models.always.chest.locator.group = "box";
			Locations[n].models.always.chest.locator.name = "private1";
			Locations[n].models.always.chest.tech = "DLightModel";
			DoQuestReloadToLocation("Shore37", "goto", "goto5", "Mtraxx_PlantChestReady");
		break;
		
		case "Pelly_11":
            dialog.text = "Будет сделано, адмирал!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantPrepareMarch");
		break;
		
		case "Pelly_12":
            dialog.text = "Ребята к бою готовы, адмирал.";
			link.l1 = "Тогда вперёд!";
			link.l1.go = "Pelly_13";
		break;
		
		case "Pelly_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_14":
            dialog.text = "Адмирал, кажется, дружок Тиракса, которого мы должны были вытащить, того... это... дуба дал.";
			link.l1 = "Да я видел... что тут поделаешь - самим спасаться впору было, кто же знал, что охранники на плантации свирепее бульдогов голодных...";
			link.l1.go = "Pelly_15";
		break;
		
		case "Pelly_15":
            dialog.text = "Адмирал, Маркус, наверное, огорчится... Ты бы не ходил к нему сразу, а то не ровен час - зашибёт. Лучше затихарись. Ну, а я отчаливаю. И ты побыстрее уходи...";
			link.l1 = "Да уж...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantFailFinal");
		break;
		
		case "Pelly_16":
            dialog.text = "Адмирал, плохие новости. С востока прямо на нас движется испанская эскадра. Сбежать не успеем.";
			link.l1 = "Сколько их?";
			link.l1.go = "Pelly_17";
		break;
		
		case "Pelly_17":
            dialog.text = "Три судна. Много пушек. Дело - табак..."; // лесникПОСЛЕДНЕЕ
			link.l1 = "Это мы ещё посмотрим.";// Жан, ты отправляйся на борт к Тесаку. Тесак, поднимешь испанский флаг и на всех парусах прочь отсюда - глядишь, за торговца сойдёшь. А я пойду прямо на испанцев - отвлеку их от вас. Увидимся в Ла Веге у Тиракса.";
			link.l1.go = "Pelly_181";
		break;
		case "Pelly_181":
	    	DialogExit();
		   sld = characterFromId("Mrt_Rocur");
		   sld.Dialog.currentnode = "Pelly_182";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_182":
		   dialog.text = ""; 
		   link.l1 = "Жан, ты отправляйся на борт к Тесаку.";
		   link.l1.go = "Pelly_183"; 
		break;
		case "Pelly_183":
		     DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_18":
            dialog.text = "";//"Но...";
			link.l1 = "Тесак, поднимешь испанский флаг и на всех парусах прочь отсюда - глядишь, за торговца сойдёшь. А я пойду прямо на испанцев - отвлеку их от вас. Увидимся в Ла Веге у Тиракса.";//"Отставить! Тесак, за Жана Пикара отвечаешь головой перед Тираксом. Все на борт!";
			link.l1.go = "Pelly_19";
		break;
		
		case "Pelly_19":
            dialog.text = "Но...";
			link.l1 = "Отставить! Тесак, за Жана Пикара отвечаешь головой перед Тираксом. Все на борт!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantSeaEscape");
		break;
		
		case "Pelly_20":
            dialog.text = "Адмирал, какие будут распоряжения?";
			link.l1 = "Готовьтесь к бою. В атаку пойдём по моему приказу!";
			link.l1.go = "Pelly_21";
		break;
		
		case "Pelly_21":
            dialog.text = "Так точно, адмирал - по твоему приказу!";
			link.l1 = "...";
			link.l1.go = "Pelly_22";
		break;
		
		case "Pelly_22":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_23":
            dialog.text = "Хо! Здорово, Принц. Какими ветрами на Тортуге?";
			link.l1 = "Решаю очередную задачу для Маркуса, разрази меня гром. Послушай, Пол, почему фрукт, который живёт в этом доме, не пускает меня?";
			link.l1.go = "Pelly_24";
		break;
		
		case "Pelly_24":
            dialog.text = "Гаспар Златозубый? А дык он только проверенных людей пускает. А с новыми заводит знакомство только по рекомендации. Решил побрякушки сдать? Хочешь, замолвлю за тебя словечко...";
			link.l1 = "Так этот, Златозубый - принимает деньги и золотишко на хранение? И каков процент?";
			link.l1.go = "Pelly_25";
		break;
		
		case "Pelly_25":
            dialog.text = "Братишка, ты чего-то попутал. Гаспар ростовщичеством не занимается - это тебе "+GetFullName(characterFromId("Tortuga_usurer"))+" нужен. Златозубый скупает ювелирку - жемчуг, самоцветы, колечки, брошки, золотые и серебряные слитки... кстати, по неплохой цене, и не задаёт идиотских вопросов. Все пиратские кэпы у него пасутся.";
			link.l1 = "Так вот оно что... А мне сказали, что кое-какие кэпы у него песо да дублоны хранят, чтобы спокойней было...";
			link.l1.go = "Pelly_26";
		break;
		
		case "Pelly_26":
            dialog.text = "Ха-ха! Брехун тот, кто тебе это сказал! Поди и плюнь ему в бесстыжие глаза. Гаспар барыжит побрякушками, и сколько я его знаю - только этим всегда и занимался. Он и так как сыр в масле катается - зачем ему проблемы с чужими деньгами?";
			link.l1 = "Всё ясно. Спасибо, Тесак, удачи в море!";
			link.l1.go = "Pelly_27";
		break;
		
		case "Pelly_27":
            dialog.text = "И тебе того же, Принц.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookThird");
		break;
		
		case "Pelly_28":
            dialog.text = "Отыскал трёх птичек, Принц. Прятались в шкафах и под кроватью. Хороши милашки, как считаешь? Ха-ха-ха?!";
			link.l1 = "Недурны, весьма недурны, а главное - ухожены... и наверняка небезразличны его светлости дону Упрямцу.";
			link.l1.go = "Pelly_29";
		break;
		
		case "Pelly_29":
            DialogExit();
			sld = CharacterFromID("Mtr_CartahenaMayorClone");
			sld.dialog.currentnode = "CartahenaMayor_8";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Pelly_30":
            dialog.text = "Алле хагель! Какого дьявола ты тут шаришься, Принц?";
			link.l1 = "Тесак?! Вот уж не ожидал! Ты откуда?";
			link.l1.go = "Pelly_31";
		break;
		
		case "Pelly_31":
            dialog.text = "Нет, это ты откуда?! Везде, везде ты суёшься! Тиракс послал тебя за сокровищем рудокопов, так? Карамба, не успел я...";
			link.l1 = "Тиракс? Нет... Я купил карту у одной девки - по ней и пришёл сюда. Тебе она, наверное, продала дубликат карты - вот хитрая деваха! На Тортуге её встретил, да?.. Хех, вижу, что Камилла не обманула - тут целая груда золота!";
			link.l1.go = "Pelly_32";
		break;
		
		case "Pelly_32":
            dialog.text = "Да, чёрт возьми, здесь целая груда золота, но оно моё! Не твоё, и не Тиракса! Я первый его нашёл - мне оно и принадлежит! И неважно, откуда я про него узнал! Не твоё дело!";
			link.l1 = "Спокойно, Тесак, ты чего разошёлся? Глянь на эту кучу - тут точно не меньше миллиона, а скорее всего - больше. Нам обоим хватит!";
			link.l1.go = "Pelly_33";
		break;
		
		case "Pelly_33":
            dialog.text = "Тебе всегда достаётся больше всех, Принц! Но в этот раз ты просчитался - я не уступлю ни дублона. Только не в этот раз! Сокровища принадлежат мне по праву первого!";
			link.l1 = "Чёрт тебя дери, Пол, да что на тебя нашло? Неужели не договоримся? Даже половина этого золота - огромная сумма. Клянусь громом, у тебя никогда не бывало таких денег.";
			link.l1.go = "Pelly_34";
		break;
		
		case "Pelly_34":
            dialog.text = "Ты хочешь меня облапошить, Принц? Как бы не так! Я не отдам тебе ни монеты, ни единой гинеи! Ты опоздал!\nА-а, я понимаю, что ты задумал! Разрази тебя гром, тебе это не удастся!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionPellyFight");
		break;
		
		// Жан Пикар
		case "rocur":
            dialog.text = "Что тебе надо от меня?";
			link.l1 = "Приятель, я ищу Жана Пикара. Это случайно не ты?";
			link.l1.go = "rocur_1";
		break;
		
		case "rocur_1":
            dialog.text = "Случайно я. А вот твою рожу я что-то не припоминаю.";
			link.l1 = "Полегче, Жан. Я от Маркуса Тиракса. Мне поручено вытащить тебя отсюда.";
			link.l1.go = "rocur_2";
		break;
		
		case "rocur_2":
            dialog.text = "Маркус? Ч-ш-ш... Извини, дружище, не знал. Но об этом говорить здесь нельзя - надсмотрщики бдят, подлые... Ты, вижу, вхож к испанцам, так что дождись ночи и найди меня в одном из бараков. Там и поговорим. Всё, жду тебя...";
			link.l1 = "...";
			link.l1.go = "rocur_3";
		break;
		
		case "rocur_3":
            DialogExit();
			AddQuestRecord("Roger_3", "6");
			LAi_CharacterDisableDialog(npchar);
			Mtraxx_PlantMakeMaxRocurClone();
		break;
		
		case "rocur_4":
            dialog.text = "Ну вот, тут можно спокойно поговорить... Как твоё имя, братишка?";
			link.l1 = "Капитан "+GetFullName(pchar)+". Теперь рассказывай, как ты угодил в эту передрягу. Тиракс хочет это знать.";
			link.l1.go = "rocur_5";
		break;
		
		case "rocur_5":
            dialog.text = "Да подсел ко мне в таверне Виллемстада перец один... Предложил на дельце сходить вдвоём - голландских торговцев пощипать. У меня бригантина, у него - полакр. Настигли караван напротив Каракаса, захватили товар. Ночь как раз наступила. Легли в дрейф, начали добычу делить - тут откуда ни возьмись - испанский тяжёлый галеон из мрака выходит\nКомпаньон распустил паруса и - драпать, я, конечно, тоже - куда на потрёпанной бригантине против тяжёлого галеона. Испанец за мной увязался и догнал, каналья. Взяли на абордаж нас, кого не убили - загнали в трюм и продали сюда, на плантацию, как скот. Вот и вся история.";
			link.l1 = "Ясно. Как считаешь - испанец случайно натолкнулся на вас?";
			link.l1.go = "rocur_6";
		break;
		
		case "rocur_6":
            dialog.text = "А кто его знает. Караван торгашей недалеко от Мэйна проходил, могли кастильцы звуки канонады услышать. Вполне... Вот и явился, окаянный дон.";
			link.l1 = "Хм. Возможно. А напарника своего ты раньше встречал? Что за птица?";
			link.l1.go = "rocur_7";
		break;
		
		case "rocur_7":
            dialog.text = "Раньше не встречал. Представился как Игнасио Марко, капер на службе Англии. Выпили рому, разговорились. Серьёзным парнем он мне показался - вот и решили в поход сходить. Моряк опытный, сразу видать, и команда лихая, а полакр - просто загляденье, такие красавцы редко встречаются.";
			link.l1 = "Игнасио Марко? На службе Англии? Испанец?";
			link.l1.go = "rocur_8";
		break;
		
		case "rocur_8":
            dialog.text = "Португалец он, не испанец. А что до того, что с английским патентом? Среди нашего брата и испанцы встречаются, знаешь ли.";
			link.l1 = "Понятно. Ладно, давай будем решать, как тебя вызволить отсюда. У самого какие-нибудь предложения будут?";
			link.l1.go = "rocur_9";
		break;
		
		case "rocur_9":
            dialog.text = "Какими силами ты располагаешь?";
			link.l1 = "Мой корабль, баркентина и люди Тесака Пелли. Моё судно в порту Маракайбо, Тесак Пелли высадился в бухте Гуахира и разбил лагерь.";
			link.l1.go = "rocur_10";
		break;
		
		case "rocur_10":
            dialog.text = "Гм...";
			link.l1 = "А ты ожидал, что Тиракс пришлёт сюда линейный корабль?";
			link.l1.go = "rocur_11";
		break;
		
		case "rocur_11":
            dialog.text = "Я вообще ничего не ожидал. Я удивлён, что Маркус не забыл про меня.";
			link.l1 = "Как видишь - не забыл. Ну, есть идеи?";
			link.l1.go = "rocur_12";
		break;
		
		case "rocur_12":
            dialog.text = "Сбежать отсюда шансов нет - плантация очень хорошо охраняется, а за пределами на юг - дикие непроходимые джунгли. Штурмовать её ты тоже не сможешь - людей маловато, и форт в непосредственной близости. Тут же подкрепление к испанцам подоспеет.";
			link.l1 = "А ты и твои ребята изнутри не поможете? Ударите охранникам в спину.";
			link.l1.go = "rocur_13";
		break;
		
		case "rocur_13":
            dialog.text = "Чем? Голыми руками? Или ржавыми мачете?";
			link.l1 = "А если бы было оружие - помогли бы?";
			link.l1.go = "rocur_14";
		break;
		
		case "rocur_14":
            dialog.text = "Спрашиваешь! Конечно! Вот только где его взять, это оружие? На плантации строгий контроль - весь вносимый товар проверяется, а если увидят, что ты тащишь сюда связки сабель и мушкетов... забудь об этом.";
			link.l1 = "И всё-таки я буду рассматривать именно этот вариант. Как пронести оружие на плантацию - ещё обмозгуем. Сколько ребят, способных держать саблю, здесь наберётся?";
			link.l1.go = "rocur_15";
		break;
		
		case "rocur_15":
            dialog.text = "Человек тридцать будет.";
			link.l1 = "Значит, надо тридцать сабель... И пистолей бы тоже не помешало.";
			link.l1.go = "rocur_16";
		break;
		
		case "rocur_16":
            dialog.text = "Кэп, ты это сейчас серьёзно?";
			link.l1 = "Более чем. Я не шутки сюда шутить приехал. Что ещё из оружия?";
			link.l1.go = "rocur_17";
		break;
		
		case "rocur_17":
            dialog.text = "Ладно... Давай попытаемся хотя бы. Оружие нужно простое - не мастаки мои парни в изысканном фехтовании дорогими рапирами. Пистоли - обычные строевые. Если найдёшь фитильный мушкет или два - было бы недурственно: парочка моих парней умеет стрелять из таких. Пули, порох. Зелья целебные по две-три штуки на брата желательно...";
			link.l1 = "Ясно. Сабли и топоры можно просто взять из судового арсенала, а вот с остальным придётся повозиться. Как соберу всё необходимое - дам знать.";
			link.l1.go = "rocur_18";
		break;
		
		case "rocur_18":
            dialog.text = "Только не растяни на полгода, брат. А то все мои люди передохнут от непосильной работы. И для беседы приходи ночью сюда, как сегодня: днем на плантации - молчок.";
			link.l1 = "Хорошо, приятель. Держитесь, я постараюсь не затягивать. Бывай.";
			link.l1.go = "rocur_19";
		break;
		
		case "rocur_19":
            DialogExit();
			AddQuestRecord("Roger_3", "7");
			npchar.dialog.currentnode = "rocur_wait";
			pchar.questTemp.Mtraxx = "plant_3";
			pchar.quest.Mtraxx_PlantPrepareTimeOver.over = "yes"; //снять таймер
			SetFunctionTimerCondition("Mtraxx_SeekWeaponOver", 0, 0, 30, false); // таймер
		break;
		
		case "rocur_wait":
            dialog.text = "Какие новости, приятель? Собрал оружие?";
			if (pchar.questTemp.Mtraxx == "plant_5")
			{
				link.l1 = "Да. Сундук с оружием стоит в бухте Гуахира. Осталось найти способ пронести его на плантацию.";
				link.l1.go = "rocur_20";
			}
			else
			{
				link.l1 = "Я работаю над этим. Жди.";
				link.l1.go = "rocur_wait_1";
			}
		break;
		
		case "rocur_wait_1":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait";
		break;
		
		case "rocur_20":
            dialog.text = "Очень хорошо, кэп. А я уже подумал о том, как можно попробовать пронести оружие сюда.";
			link.l1 = "Рад, что ты не терял время даром. Выкладывай.";
			link.l1.go = "rocur_21";
		break;
		
		case "rocur_21":
            dialog.text = "На этой плантации производят сахар из сахарного тростника, а также выращивают какао-бобы. Готовый товар вывозят на кораблях через местного купца, но управляющий частенько сам заключает торговые сделки с заезжими торговцами - так выгоднее. Предложи управляющему приобрести его продукцию, но не за деньги, а в обмен на другой товар, причём сыпучий и который можно поставлять в ящиках: кофе, ваниль, копру. Торгуйся так, чтобы ему была выгодна эта негоция, но не переусердствуй - иначе вызовешь подозрения\nВот в одном-двух ящиках, среди товаров, ты и пронесёшь оружие. Обмен приурочь к вечеру, чтобы ящики, которые занесут твои люди на плантацию, были вынуждены остаться на ночь на улице. Ящики 'с секретом' пусть пометят условным знаком и поставят так, чтобы было легко добраться до их содержимого\nНу а ночной порой мы тихонечко ползком проберёмся к ним, а затем устроим кастильцам сюрприз. При поддержке твоих ребят, конечно.";
			link.l1 = "У тебя котелок знатно варит, братишка! Отличный план. Так и будем действовать.";
			link.l1.go = "rocur_22";
		break;
		
		case "rocur_22":
            dialog.text = "И ещё: предлагай только один вид товара: чем больше разных товаров, тем больше ящиков могут вскрыть для ознакомления, а это нам ни к чему, как ты понимаешь.";
			link.l1 = "Согласен. Выберу какой-то один тип. Кофе, ваниль, копра, говоришь?";
			link.l1.go = "rocur_23";
		break;
		
		case "rocur_23":
            dialog.text = "Да. На них управляющий скорее согласится, чем на фрукты или кожу. К тому же, они производятся в соседних колониях на Мэйне.";
			link.l1 = "Договорились. Как решу вопрос с управляющим - дам знать.";
			link.l1.go = "rocur_24";
		break;
		
		case "rocur_24":
            DialogExit();
			AddQuestRecord("Roger_3", "9");
			npchar.dialog.currentnode = "rocur_wait_2";
			pchar.questTemp.Mtraxx = "plant_6";
		break;
		
		case "rocur_wait_2":
            dialog.text = "Ступай, дружище, время дорого...";
			link.l1 = "";
			link.l1.go = "rocur_wait_3";
		break;
		
		case "rocur_wait_3":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait_2";
		break;
		
		case "rocur_25":
            dialog.text = "";
			link.l1 = "(вполголоса) Сделка заключена. Ящики будут на плантации завтра вечером. На нужных ящиках нарисуем букву W, на остальных - весь прочий алфавит. Готовь ребят. Атакуем перед рассветом, в три часа.";
			link.l1.go = "rocur_25x";
		break;
		
		case "rocur_25x":
            dialog.text = "Мы начнём по твоему сигналу...";
			link.l1 = "";
			link.l1.go = "rocur_26";
		break;
		
		case "rocur_26":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 3.0);
		break;
		
		case "rocur_27":
            dialog.text = "Наконец-то я снова вижу море! Уже и забыл как оно выглядит и как пахнет. Отличная работа, капитан! Я перед тобой в долгу.";
			link.l1 = "Сочтёмся как-нибудь... Грузимся в шлюпку и отчаливаем!";
			link.l1.go = "rocur_28";
		break;
		
		case "rocur_28":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "rocur_29":
            dialog.text = "Приветствую, "+pchar.name+". Рад тебя видеть снова, и рад тому, что мы отправимся в поход вместе. Дело предстоит непростое, но я уверен, что мы справимся.";
			link.l1 = "Привет, Жан. Внимательно слушаю тебя, что за поход?";
			link.l1.go = "rocur_30";
		break;
		
		case "rocur_30":
            dialog.text = "Маркус уже в курсе, сейчас расскажу и тебе. Пока я был в рабстве на плантации Маракайбо, я не только гнул спину под палящим солнцем, но и держал уши широко открытыми. Испанцы любят поболтать, особенно после пинты-другой рома... Так вот, на юго-восток от озера Маракайбо, среди джунглей, поднимаются два горных хребта, а между ними расположилось небольшое испанское поселение с длиннющим названием: Сантьяго-де-Лос-Кабальерос-де-Мерида. Будем звать его просто Мерида\nМаленький городок среди гор - кажется, что интересного? Однако горы вблизи этого городка оказались щедры на самоцветы. Из подслушанного разговора я понял, что жители Мериды нашли 'самоцветную жилу' - россыпь зелёных и жёлто-красных драгоценных камней. Это весьма ценные изумруды и опалы. Среди последних попадались и огненные опалы - дорогая и редкая разновидность\nТакже я понял, что поселенцы Мериды не торопятся сообщать о своей находке генерал-губернатору - думаю, понятно, почему. Однако эта история рано или поздно всё равно вылезет наружу, поэтому нам надо навестить Мериду раньше, чем это сделают офицеры испанских колониальных войск.";
			link.l1 = "Ты хочешь ограбить этот городок?";
			link.l1.go = "rocur_31";
		break;
		
		case "rocur_31":
            dialog.text = "Именно. Затерянное среди джунглей и гор поселение с маленьким гарнизоном - лёгкая добыча для отряда корсаров. К тому же, находясь вдали от моря, они даже не предполагают, что на них может напасть кто-то, кроме дикарей с копьями и луками.";
			link.l1 = "Насколько ты уверен, что в этом поселении действительно имеются добытые камни?";
			link.l1.go = "rocur_32";
		break;
		
		case "rocur_32":
            dialog.text = "Если наш поход окажется напрасным, я отправлюсь на твой корабль офицером или матросом и буду бесплатно драить палубу и рубиться в абордажах до тех пор, пока не отработаю свой долг тебе и Маркусу.";
			link.l1 = "Ясно... Как пройти в Мериду - тебе известно?";
			link.l1.go = "rocur_33";
		break;
		
		case "rocur_33":
            dialog.text = "Точный путь через джунгли мне, конечно, неизвестен, но мы наймём проводника из индейцев. Высадимся на южной оконечности озера Маракайбо, отыщем индейскую деревню и найдём в ней того, кто знает дорогу.";
			link.l1 = "...";
			link.l1.go = "rocur_34";
		break;
		
		case "rocur_34":
            DialogExit();
			sld = characterFromId("Terrax");
			sld.Dialog.currentnode = "mtraxx_38";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_35":
            dialog.text = "Капитан, ты извини, конечно, но какого чёрта мы до сих пор не в Мериде? А? Ты наплевал на наше общее дело! Мы с Лепреконом отправляемся дальше, но уже без тебя. Надеюсь, ещё успеем. А ты занимайся посторонними делами дальше - с Тираксом я объяснюсь. Вот, держи 50 000 песо за твою помощь в Маракайбо - я одолжил у друзей. А теперь прощай - жаль, я был о тебе лучшего мнения.";
			link.l1 = "Гм...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaTimeOverFail");
		break;
		
		case "rocur_36":
            dialog.text = "Вот мы и на месте. Дальше путь лежит через джунгли. Начнём с того, что найдём деревню индейцев и наймём проводника, знающего местность.";
			link.l1 = "Так и поступим. Люк, что можешь добавить или посоветовать?";
			link.l1.go = "rocur_37";
		break;
		
		case "rocur_37":
            DialogExit();
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_38":
            dialog.text = "С гарнизоном Мериды покончено. Внутри мы вряд ли столкнемся с серьёзным сопротивлением. Вперёд, в город!";
			link.l1 = "В атаку!!";
			link.l1.go = "rocur_39";
		break;
		
		case "rocur_39":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_ExitTown", "reload1_back", true);
			pchar.quest.mtraxx_merida_town.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_town.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_town.function = "Mtraxx_MeridaTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "16");
		break;
		
		case "rocur_40":
            dialog.text = "Всё! Больше желающих геройствовать не осталось. Теперь пора побеседовать с губернатором этого городишки. Надеюсь, он окажется сговорчивым, и нам не придётся прибегать к крайним мерам.";
			link.l1 = "Идём!.. Лепрекон! За мной!";
			link.l1.go = "rocur_41";
		break;
		
		case "rocur_41":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "gate_back", true);
			pchar.quest.mtraxx_merida_townhall.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_townhall.win_condition.l1.location = "Merida_townhall";
			pchar.quest.mtraxx_merida_townhall.function = "Mtraxx_MeridaTownhall";
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Roger_5", "17");
		break;
		
		case "rocur_42":
            dialog.text = ""+pchar.name+", всё отлично. Тут целая груда изумрудов и опалов. Как я и ожидал.";
			link.l1 = "Забирай всё и уходим отсюда. Пора отправляться в обратный путь.";
			link.l1.go = "rocur_43";
		break;
		
		case "rocur_43":
            DialogExit();
			chrDisableReloadToLocation = false;
			pchar.questTemp.Mtraxx = "merida_success";
			AddQuestRecord("Roger_5", "12");
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		case "rocur_44":
            dialog.text = "Отлично сработали, "+pchar.name+"! Пришло время делить добытое. Я уже всё подсчитал. В сундуке было почти две тысячи камешков: 1050 штук изумрудов, 732 штуки опалов и 189 штук огненных опалов. Тебе причитается третья часть: 350 изумрудов, 244 опала и 63 огненных опала. Держи, это твоя доля.";
			link.l1 = "Отлично!";
			link.l1.go = "rocur_45";
		break;
		
		case "rocur_45":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 350);
			TakeNItems(pchar, "jewelry16", 244);
			TakeNItems(pchar, "jewelry14", 63);
            dialog.text = "Теперь поговорим о моём долге перед тобой за освобождение из рабства в Маракайбо. Я понимаю, что ты изрядно на это потратился. Какую сумму компенсации ты считаешь справедливой? Я буду платить камнями из моей доли.";
			link.l1 = "Думаю, что трети от твоей доли будет вполне достаточно. Тебе тоже нужны деньги - нужно покупать и снаряжать корабль, платить команде...";
			link.l1.go = "rocur_46";
		break;
		
		case "rocur_46":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 116);
			TakeNItems(pchar, "jewelry16", 81);
			TakeNItems(pchar, "jewelry14", 21);
            dialog.text = "Спасибо, дружище. Я думал, что ты запросишь не меньше половины... Деньги мне и впрямь очень нужны сейчас. Вот, держи камни.";
			link.l1 = "Славный был поход, Жан! Теперь отправляемся назад, на Эспаньолу, к Тираксу.";
			link.l1.go = "rocur_47";
		break;
		
		case "rocur_47":
            DialogExit();
			chrDisableReloadToLocation = false;
			pchar.questTemp.Mtraxx = "merida_gohome";
			AddQuestRecord("Roger_5", "18");
			sld = characterFromId("Mrt_Rocur");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld); // релиз-правка
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Lepricon");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_40";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_merida_lavega.function = "Mtraxx_IgnasioKitty";
			// таймер на доплыть домой 40 дней
			SetFunctionTimerCondition("Mtraxx_MeridaReturnLate", 0, 0, 40, false);
			DeleteAttribute(pchar, "GenQuest.HunterLongPause");
		break;
		
		case "rocur_48":
            dialog.text = "О, какая встреча! Рад тебя видеть, "+pchar.name+". Как дела?";
			link.l1 = "Дела идут неплохо. Только что распутал историю с кладом погибшего недавно Рыжего Вульфа - отыскал его сокровища и неплохо заработал. А сейчас иду на Мартинику, повидать одного... общего знакомого. А ты к Тираксу?";
			link.l1.go = "rocur_49";
		break;
		
		case "rocur_49":
            dialog.text = "Да. Хочу побеседовать с ним насчёт Паскуале Вуазье. Маркус направил меня к нему, я выполнил поручение этого полубандита-полуторгаша, а он заплатил за работу какие-то гроши и ещё имел дерзость утверждать, что это хорошая плата. Я бы пригвоздил жулика к стенке магазина, но Тиракс просил не обижать его... вот пускай теперь решит вопрос со своим 'протеже'...";
			link.l1 = "Ну-ну... Ничего Маркус решать не станет. Очкастый с ним в доле.";
			link.l1.go = "rocur_50";
		break;
		
		case "rocur_50":
            dialog.text = "Ты серьёзно?";
			link.l1 = "Более чем, но я тебе этого не говорил, сечёшь? Не так давно Вуазье надул и меня, с чёрным деревом. По направлению от Тиракса. А на Исла Тесоро меня просветили, и предупредили, что кто наедет на четырёхглазого - будет иметь дело с Маркусом. Так что советую тебе забыть об этом, если не хочешь нажить серьёзных проблем. Ты не первый и не последний, кого они таким образом кинули.";
			link.l1.go = "rocur_51";
		break;
		
		case "rocur_51":
            dialog.text = "Так вот оно что... Так значит - ты тоже попался на эту удочку?";
			link.l1 = "Ну да. Я поначалу хотел припомнить очкастому его кидок, но когда узнал подробности, передумал. С Тираксом лучше не ссориться - себе дороже.";
			link.l1.go = "rocur_52";
		break;
		
		case "rocur_52":
            dialog.text = "А если бы предоставилась возможность отплатить так, чтобы никто не узнал - ты бы пошёл на это?";
			link.l1 = "Ха! Конечно. Только не представляю, как. Нападёшь на флейт Вуазье - твои же матросы по пьяни и разболтают. Не знаешь, что ли, как это бывает?";
			link.l1.go = "rocur_53";
		break;
		
		case "rocur_53":
            dialog.text = "Ты сейчас на Мартинику? Когда снова будешь в Ла Веге?";
			link.l1 = "Маркус дал мне три недели.";
			link.l1.go = "rocur_54";
		break;
		
		case "rocur_54":
            dialog.text = "Постарайся обернуться за две. Я тут подумаю немного... Приходи ровно через четырнадцать дней в бухту Гонаив, это на запад отсюда. Я буду ждать тебя там. Только не суйся в Ла Вегу, иди сразу.";
			link.l1 = "Смотрю, ты уже что-то задумал, хе-хе. Хорошо. Я постараюсь.";
			link.l1.go = "rocur_55";
		break;
		
		case "rocur_55":
            dialog.text = "Постарайся. До встречи!";
			link.l1 = "...";
			link.l1.go = "rocur_56";
		break;
		
		case "rocur_56":
            DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 10.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			ReOpenQuestHeader("Roger_4");
			AddQuestRecord("Roger_4", "11");
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.hour  = 1.0;
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2 = "location";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2.location = "Shore34";
			pchar.quest.mtraxx_pasq_gonaiv.function = "Mtraxx_PasqualeJanGonaiv";
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimer", 0, 0, 10, false); // правки прогона 3
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimeOver", 0, 0, 15, false);
			pchar.questTemp.Mtraxx.Pasquale.Grabbing = "true";
		break;
		
		case "rocur_57":
			if (pchar.location.from_sea != "Shore34")
			{
				dialog.text = RandSwear()+"Где твой корабль? Ты пешком из Ла Веги сюда, что ли, дотопал? Я же просил - не светиться и прийти скрытно. Эх, пропал теперь мой план. Тьфу!..";
				link.l1 = "Гм...";
				link.l1.go = "rocur_58";
			}
			if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "Вот и ты, "+pchar.name+". Молодец, что пришёл. Отошли на корабль своих быков - будем говорить с глазу на глаз. Лишние уши нам не нужны.";
				link.l1 = "Хорошо, сейчас прикажу им уйти.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "Вот и ты, "+pchar.name+". Молодец, что пришёл. У меня есть предложение для тебя. Готов выслушать?";
				link.l1 = "Конечно!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_58":
            DialogExit();
			Group_DelCharacter("RocurSeaGroup", "Mrt_Rocur");
			Group_DeleteGroup("RocurSeaGroup");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("Roger_4", "14");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_59":
            DialogExit();
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "rocur_60";
		break;
		
		case "rocur_60":
            if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "Говорю же - отправь прочь своих офицеров! Не будем при них...";
				link.l1 = "Да-да, я понял.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "Отлично. Теперь можно не опасаться, что нас подслушают. У меня есть предложение для тебя. Готов выслушать?";
				link.l1 = "Конечно!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_61":
            dialog.text = "Ты хорошо знаешь поселок Ла Веги?";
			link.l1 = "Ну... нормально. А что?";
			link.l1.go = "rocur_62";
		break;
		
		case "rocur_62":
            dialog.text = "Обращал внимание на двухэтажный дом справа от магазина? Он один такой большой, остальные - лачуги 'береговых братьев'.";
			link.l1 = "Это который всё время под замком? Знаю. А что с этим домом?";
			link.l1.go = "rocur_63";
		break;
		
		case "rocur_63":
            dialog.text = "Ты верно подметил - этот дом всё время заперт. Пока ты был в походе на Мартинику, в Ла Веге побывал наш друг Паскуале Вуазье. Гостил у Тиракса три дня. И проводили время они в этом доме. Веселились, ром распивали... я наблюдал.";
			link.l1 = "Интересно...";
			link.l1.go = "rocur_64";
		break;
		
		case "rocur_64":
            dialog.text = "А потом матросы Вуазье переносили какие-то свёртки, ящики и сундуки с корабля очкастого в этот дом. Затем Паскуале отбыл с Ла Веги. Ну а Маркус один раз в день наведывается туда, часа на два-три.";
			link.l1 = "Твои предположения?";
			link.l1.go = "rocur_65";
		break;
		
		case "rocur_65":
            dialog.text = "А что тут гадать? Этот дом - база Паскуале Вуазье в Ла Веге. Я подглядел в окно. Увидеть удалось немного, но я рассмотрел свёртки, бочонки, сундуки... Думаю, очкастому будет чем вернуть долги тебе и мне.";
			link.l1 = "Так-так... Хочешь проникнуть туда? А как же запертая дверь? Я помню: она крепкая, начнёшь ломать - весь посёлок сбежится, а на окнах решётки...";
			link.l1.go = "rocur_66";
		break;
		
		case "rocur_66":
            dialog.text = ""+pchar.name+", ты меня за салагу держишь? Вопрос с замком уже решён: я при помощи твердеющего на воздухе млечного сока одного дерева сделал слепок замочной скважины, а на Тортуге один умелец выковал по нему ключ. Обошлось в полсотни золотых, однако это мои проблемы.";
			link.l1 = "Хех! А чего же ты до сих пор сам туда не наведался, а решил обтяпать это дело со мной на пару?";
			link.l1.go = "rocur_67";
		break;
		
		case "rocur_67":
            dialog.text = "Вдвоём будет безопаснее. Одна голова хорошо, а две - лучше. И четыре глаза увидят больше, чем два.";
			link.l1 = "Ну да, чтобы ограбить Вуазье, нужно не меньше глаз, чем у него, ха-ха-ха!.. А как же Тиракс? Представляешь, что будет, если он нагрянет, когда мы будем копаться в вещичках Паскуале...";
			link.l1.go = "rocur_68";
		break;
		
		case "rocur_68":
            dialog.text = "Не нагрянет. По ночам Маркус всегда находится в своей резиденции. Туда он ходит ближе к концу дня, но до полуночи всегда возвращается к себе домой. Ну как, ты готов пойти в Ла Вегу следующей ночью? Вуазье с Тираксом вовек не догадаются, кто приложил к этому руку: ты ещё в походе на Мартинику, а я ушёл из Ла Веги неделю назад.";
			link.l1 = "С удовольствием наступлю на хвост этой очкастой сволочи. Но скажи, Жан: мы что, потащим на своем горбу сундуки и бочонки из этой халупы?";
			link.l1.go = "rocur_69";
		break;
		
		case "rocur_69":
            dialog.text = "Я уверен, там будут ценные вещи, которые мы сможем унести, не напрягая свой горб. Итак, мы идём?";
			link.l1 = "Да!";
			link.l1.go = "rocur_70";
		break;
		
		case "rocur_70":
            dialog.text = "Отлично, я не ошибся в тебе. Сейчас пока отдохнём, а ближе к полуночи выступим к Ла Веге.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNight");
		break;
		
		case "rocur_71":
            dialog.text = "Пора выступать. До рассвета мы должны сделать дело и покинуть Ла Вегу.";
			link.l1 = "Вперёд!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightMarch");
		break;
		
		case "rocur_72":
            dialog.text = "Ч-ш-ш... Теперь тихонечко, рысью, к дому Паскуале. Следуй за мной и не шуми.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightToHouse");
		break;
		
		case "rocur_73":
            dialog.text = "Смотри - сколько здесь всякой всячины. Приступаем. Осмотри вон тот сундук у входа, затем поднимайся наверх и обыщи комнату, а я хорошенько пороюсь тут: мне известны хитрости, как прячут ценные вещи среди хлама. Держи глаза и уши широко открытыми, не подходи к окнам и не шуми.";
			link.l1 = "Хорошо...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightInHouse");
		break;
		
		case "rocur_74":
            dialog.text = ""+pchar.name+", ну, что тут у тебя? Есть что интересное?";
			link.l1 = "Иди сюда и посмотри. Челюсть отпадёт, когда увидишь.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeJanSeeGirl");
		break;
		
		case "rocur_75":
            dialog.text = "Проклятие! Так вот к кому ходит Тиракс каждый день на пару часов! Тут не только склад очкастого, но и бордель.";
			link.l1 = "Похоже, её здесь держат как наложницу.";
			link.l1.go = "rocur_76";
		break;
		
		case "rocur_76":
            dialog.text = "Ясное дело. Только глянь на эту деваху - сразу видать, что из портовых 'подружек'... Не повезло нам. Придётся её убить.";
			link.l1 = "Да ну?";
			link.l1.go = "rocur_77";
		break;
		
		case "rocur_77":
            dialog.text = "Она видела наши физиономии и слышала твоё имя. Она всё выложит Тираксу, а что будет дальше - сам понимаешь. У нас с тобой нет выбора - она должна умолкнуть.";
			link.l1 = "Гм...";
			link.l1.go = "rocur_78";
		break;
		
		case "rocur_78":
            dialog.text = "Оставишь эту девку живой - сам будешь мёртвый. Что выбираешь?";
			link.l1 = "";
			link.l1.go = "rocur_79";
		break;
		
		case "rocur_79":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_80":
            dialog.text = "Даже не думай верить этой потаскухе. Завтра же Тиракс будет знать обо всём. Ты хочешь получить чёрную метку?";
			link.l1 = "Нет, не хочу. Но и убивать деваху тоже не хочу - она мне пригодится. Я заберу её отсюда.";
			link.l1.go = "rocur_81";
		break;
		
		case "rocur_81":
            dialog.text = "Будешь возить её на корабле? Не смеши! Она сбежит при первом удобном случае, а дальше - сам знаешь. Посмотри на её лоб - прожжёная прохиндейка и воровка. Зачем она тебе сдалась?";
			link.l1 = "Хм. Наверное, ты прав, Жан. Кончай её и пошли быстрей отсюда.";
			link.l1.go = "rocur_82";
			link.l2 = "Не собираюсь я девку на корабле держать. Есть у меня одно местечко, откуда она никогда не сбежит, и где сплетничать не с кем. Да и делом своим обычным там займётся... Будет у меня любовница бесплатная, хе-хе.";
			link.l2.go = "rocur_84";
		break;
		
		case "rocur_82":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto6", "", 5);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto7", "Mtraxx_PasqualeJanKillGirl", 5);
		break;
		
		case "rocur_83":
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
            dialog.text = "Вот и всё, теперь она уже точно ничего Тираксу не скажет...";
			link.l1 = "Хех...";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_84":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_85":
            dialog.text = "Добряк ты, "+pchar.name+". И охота тебе с этой шлюхой валандаться? Ладно, дело твоё. Следи за ней, чтобы рот не разинула, когда выходить будем.";
			link.l1 = "Разинет - закроем навеки.";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_86":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing.Chest")) sTemp = "Немного. Сундук с дублонами, горсть рубинов, карту Эспаньолы да бутылки с ромом.";
			else sTemp = "Вообще ничего ценного.";
            dialog.text = "Что тебе удалось найти?";
			link.l1 = sTemp;
			link.l1.go = "rocur_87";
		break;
		
		case "rocur_87":
			Log_Info("Вы получили две коллекции сокровищ");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 2);
            dialog.text = "У меня дела получше. Держи, вот твоя доля. Всё равно мне столько не донести до берега... Очкастый с нами расплатился сполна.";
			link.l1 = "Отлично! Ты молодец, Жан!";
			link.l1.go = "rocur_88";
		break;
		
		case "rocur_88":
            dialog.text = "А теперь сматываемся отсюда. Вперёд!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightOutHouse");
		break;
		
		case "rocur_89":
            dialog.text = "Превосходно. Всё прошло без шума и пыли. Теперь - назад, в бухту Гонаив.";
			link.l1 = "Идём!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightGulf");
		break;
		
		case "rocur_90":
            dialog.text = "Ну, "+pchar.name+", пришло время нам с тобой расходиться. Не уверен, пересечёмся ли ещё вновь, но знай: я был рад нашему знакомству.";
			link.l1 = "Ещё не раз увидимся в Ла Веге.";
			link.l1.go = "rocur_91";
		break;
		
		case "rocur_91":
            dialog.text = "Нет. Я больше не собираюсь работать с Тираксом. Выходка с Вуазье была последней каплей.";
			link.l1 = "Гхм... Плюнь на это. Мы же своё удержали сегодня с очкастого. А Тиракс подбрасывает выгодные дельца, разве нет? Я вот в прошлый раз заработал больше полумиллиона на кладе Рыжего Вульфа.";
			link.l1.go = "rocur_92";
		break;
		
		case "rocur_92":
            dialog.text = "Скажи пожалуйста, а тебе много пришлось потрудиться, чтобы найти этот клад?";
			link.l1 = "Ну... Помотался я по архипелагу изрядно, да и мозги напрячь пришлось. И без схваток не обошлось, конечно. Но результат того стоил, я считаю.";
			link.l1.go = "rocur_93";
		break;
		
		case "rocur_93":
            dialog.text = "А какова была доля Тиракса?";
			link.l1 = "Третья часть добычи. Двести пятьдесят тысяч, ну и ещё дублонов три сотни...";
			link.l1.go = "rocur_94";
		break;
		
		case "rocur_94":
            dialog.text = "А каким было его участие в этом деле? Что Маркус сделал сам, непосредственно?";
			link.l1 = "Гм... Дал мне журнал Рыжего Вульфа...";
			link.l1.go = "rocur_95";
		break;
		
		case "rocur_95":
            dialog.text = "И на этом его участие закончилось, как я понимаю. Так?";
			link.l1 = "Ну... но ведь без Маркуса я бы даже не узнал о капитане Вульфрике...";
			link.l1.go = "rocur_96";
		break;
		
		case "rocur_96":
            dialog.text = ""+pchar.name+", неужели ты не видишь, что Тиракс таскает каштаны из огня чужими руками? Думаешь, если бы он сам мог найти клад Рыжего Вульфа, он бы стал давать задание тебе? Клянусь громом, он сначала попытался сам, а когда не вышло - подрядил тебя. И он, просто сидя на стуле в Ла Веге и распивая ром со своим четырёхглазым дружком, получил четверть миллиона песо и триста дублонов. А ты решал задачу, неделями пропадал в море и рисковал жизнью в боях. Ты только вдумайся в это, "+pchar.name+"\nКогда мы ходили с тобой на Мериду - думаешь, Маркус дал нам в помощь свою шестерку Лепрекона потому, что этот старый лесник был так необходим? Люка присматривал за нами, чтобы ты да я ненароком не укрысили камешков и не надули Тиракса. Он получил третью часть, вообще ничего не делая. Дела, которые Маркус в состоянии обтяпать, он делает сам, или при помощи своих тесаков, лысых, лепреконов и прочих недоумков, которым платит гроши, а то, на что ему своих мозгов не хватает - поручает тебе да мне\nВспомни, какие задания ты получал, а заодно посиди и посчитай, сколько Тиракс поимел на тебе за просто так. С меня же довольно. Я ничего не должен ни Маркусу, ни тебе, ни кому-либо ещё. У меня есть отличный корвет и толковая команда. Дальше я буду работать сам. Отправляюсь на Ямайку и буду ходатайствовать о получении английского патента.";
			link.l1 = "Думаю, что насчёт Тиракса ты не вполне прав... Но я желаю тебе удачи, Жан! Надеюсь, у тебя всё получится на Ямайке.";
			link.l1.go = "rocur_97";
		break;
		
		case "rocur_97":
            dialog.text = "Получится. Тебе я тоже желаю удачи и советую подумать над моими словами. Ишачить на Маркуса - не лучший выбор для тебя. Бывай, брат. Попутного ветра!";
			link.l1 = "Легкой добычи!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeAddComplete");
		break;
		
		case "rocur_98":
            dialog.text = ""+pchar.name+", не подскажешь, почему мы так долго плутали по джунглям? Теперь поздно дёргаться... пропал мой план. Эх!.. Всё, бывай, приятель...";
			link.l1 = "Хех...";
			link.l1.go = "rocur_99";
		break;
		
		case "rocur_99":
            DialogExit();
		    LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			sld.lifeday = 0;
			Group_DeleteGroup("RocurSeaGroup");
			AddQuestRecord("Roger_4", "18");
			CloseQuestHeader("Roger_4");
		break;
		
		// Люк Лепрекон
		case "lepricon":
            dialog.text = "Приветствую, капитан "+GetFullName(pchar)+". Люк Лепрекон к твоим услугам! Маркус сказал, что мы отправляемся в джунгли Южного Мэйна.";
			link.l1 = "Именно так. Грузитесь в шлюпки, мы отправляемся в путь немедленно.";
			link.l1.go = "lepricon_1";
		break;
		
		case "lepricon_1":
            dialog.text = "Позволь прежде дать старому буканьеру пару советов, кэп. Раз мы идём в сельву - значит, как пить дать, встретимся с краснокожими. Возьми с собой вещички, которые могут их заинтересовать, на обмен или в подарок. Индейские воины обычно приходят в восторг от красивых пистолей, таких как дуэльный, даже если и не умеют из него стрелять. Ещё они восхищаются приборами, например - компасом или подзорной трубой, так как считают, что они заколдованы магией белых\nДля их женщин хороши незатейливые украшения да всякая чепуха, вроде зеркалец и гребешков. Ещё касательно огнестрельного оружия на случай схватки с краснокожими: лучше использовать тромбоны и аркебузы: картечь весьма эффективно действует на толпы не защищённых кирасами и кожаными жилетами индейцев.";
			link.l1 = "Хорошо, Люк. Я приму твои слова к сведению. Добро пожаловать на борт.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaSail");
		break;
		
		case "lepricon_2":
            dialog.text = "Как найдём поселение - сразу отправляйся к вождю. Преподнеси ему подарок - иначе ничего путного не добьёшься. Ну а потом, как разговоритесь - проси у него кого-нибудь знающего тропы в сельве и не боящегося путешествий. Я иду с вами, возникнут трудности - спрашивай, если смогу что посоветовать - помогу.";
			link.l1 = "Отправляемся! Жан, Люк - за мной!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaSeekVillage");
		break;
		
		case "lepricon_3":
            dialog.text = "Есть вопросы, капитан?";
			link.l1 = "Пока нет, Люк...";
			link.l1.go = "lepricon_3x";
			if (pchar.questTemp.Mtraxx == "merida_advice")
			{
				link.l1 = "Да! Я говорил с вождём, принёс ему подарок, затем он собрал своих краснокожих. Среди них есть те, кто знают дорогу к Мериде, но идти не хотят: все струсили. Боятся каких-то капонгов в лесу. Похоже, при одном слове 'капонг' у них трясутся поджилки. Краснокожий утверждает, что сами мы дорогу не найдём, а проводника нет. И вот что нам теперь делать, а?!";
				link.l1.go = "lepricon_4";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Potion") && GetCharacterItem(pchar, "potion3") >= 12)
			{
				link.l2 = "Я принёс склянки с противоядием.";
				if (GetCharacterItem(pchar, "potion3") > 42) link.l2.go = "lepricon_7";
				else link.l2.go = "lepricon_6";
			}
		break;
		
		case "lepricon_3x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		break;
		
		case "lepricon_4":
            dialog.text = "Хм. Кэп, трусость часто побеждается жадностью. Нужно посулить такую награду проводнику, чтобы он не устоял перед искушением... Знаешь что? Попробуй обходным путём: поговори с женщинами. Дари им подарки и спрашивай про мужей - глядишь, среди них найдётся нужный нам человек. Обещай ей горы бус и зеркалец за то, что её супруг отведёт нас к Мериде. Глядишь, соблазнится и уболтает муженька. Не скупись на обещания.";
			link.l1 = "Хех! Попробую, правда, не уверен, что из этого что-то выйдет...";
			link.l1.go = "lepricon_5";
		break;
		
		case "lepricon_5":
            dialog.text = "И ещё, кэп: со слов вождя, в пути мы можем столкнуться с враждебно настроенными индейцами. Живущие в сельве Южного Мэйна краснокожие смазывают своё оружие ядом, который добывают из слизи лягушек и плодов некоторых лиан. Так что если не хочешь, чтобы твои люди перемёрли как мухи даже от лёгких ран, нанесённых отравленным оружием, озаботься наличием противоядий\nЯ и мои люди всегда имеем с собой по полдюжины банок - жизнь в сельве научила. А вот твои пираты, что пойдут в поход... Принеси мне склянок с противоядием, а я раздам их и дам нужные наставления. По одной банке не таскай, приноси сразу все - не меньше дюжины, а лучше больше, и до того, как мы уйдём из этой деревни: потом недосуг возиться будет. Для себя и своих офицеров заготовь отдельно - чай, уже приходилось пользоваться.";
			link.l1 = "Хорошо. Противоядия будут.";
			link.l1.go = "lepricon_5x";
		break;
		
		case "lepricon_5x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		   pchar.questTemp.Mtraxx = "merida_hayamee";
		   pchar.questTemp.Mtraxx.Merida.Women = "true";
		   pchar.questTemp.Mtraxx.Merida.Potion = "true";
		   AddQuestRecord("Roger_5", "8");
		   sld = characterFromId("Hayamee");
		   LAi_CharacterEnableDialog(sld);
		  // LocatorReloadEnterDisable("Shore_ship3", "boat", false); 
		   bQuestDisableMapEnter = false;
		   DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");// выпустим в море
		   SetFunctionTimerCondition("Mtraxx_MeridaPotionLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "lepricon_6":
			i = GetCharacterItem(pchar, "potion3");
			RemoveItems(pchar, "potion3", i);
			pchar.questTemp.Mtraxx.Merida.Antidote = i;
            dialog.text = "Очень хорошо. Давай их мне, остальное - моя забота.";
			link.l1 = "Держи...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_7":
			RemoveItems(pchar, "potion3", 42);
			pchar.questTemp.Mtraxx.Merida.Antidote = 42;
            dialog.text = "Три с половиной дюжины будет достаточно. Остальное оставь себе - пригодится.";
			link.l1 = "Хорошо...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_8":
            DialogExit();
		    npchar.dialog.currentnode = "lepricon_3";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Potion");
		break;
		
		case "lepricon_9":
            dialog.text = "Кэп, твои индейцы - Хайами и Тагофа - не дождались, пока ты соизволишь принести им оговорённые подарки, и свалили куда-то в соседнюю деревню пить кашири и плясать танцы. Чую, с твоим подходом к делу мы до Мериды не доберёмся и через год. В общем, извини, конечно, но дальше всё будет происходить без тебя. Пикар возглавит экспедицию. Ты больше не в деле.";
			link.l1 = "Да и пёс с вами!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "19");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_10":
            dialog.text = "Кэп, ты вообще - чем занимаешься? Мы столько времени потеряли напрасно! Чую, с твоим подходом к делу мы до Мериды не доберёмся и через год. В общем, извини, конечно, но дальше всё будет происходить без тебя. Пикар возглавит экспедицию. Ты больше не в деле.";
			link.l1 = "Да и пёс с вами!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_11":
            dialog.text = "Кэп, ты за десять дней не смог найти досок и кожи? Маракайбо рядом, Виллемстад, в конце-концов! Мы столько времени потеряли напрасно! Чую, с твоим подходом к делу мы до Мериды не доберёмся и через год. В общем, извини, конечно, но дальше всё будет происходить без тебя. Пикар возглавит экспедицию. Ты больше не в деле.";
			link.l1 = "Да и пёс с вами!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_12":
            dialog.text = "Капитан, ты извини, конечно, но мне уже давно пора было быть в Ла Веге, как, впрочем, и тебе. Ты, похоже, просто забыл о моём существовании, как и о том, что Маркус ждёт тебя. В общем, я схожу на берег и сам доберусь до Эспаньолы, а ты занимайся своими делами дальше - с Тираксом я объяснюсь. Прощай - жаль, я был о тебе лучшего мнения.";
			link.l1 = "Гм...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaReturnFail");
		break;
		
		case "lepricon_13":
            dialog.text = "Итак, как я понимаю - подельнички перегрызлись. Не смогли поделить добычу, не так ли, Чарли Принц?";
			link.l1 = "Лепрекон? И ты... Впрочем, я не сильно удивлён. Да, жадные до золота ублюдки Тесак и Лысый наплевали на кодекс берегового братства и напали на меня.";
			link.l1.go = "lepricon_14";
		break;
		
		case "lepricon_14":
            dialog.text = "Да, вижу, тебе хорошо досталось, Принц. Выглядишь ты неважно. Похоже, едва на ногах держишься\nТак что ты там сказал насчёт кодекса? Я просвещу тебя: за время моей многолетней работы с Маркусом, хранителем этого самого кодекса, я столько раз видел, как 'братья' его нарушали, что и сосчитать не возьмусь. Нарушители получали чёрные метки, их высаживали на пустынные рифы с бутылкой рома и пистолетом с одним зарядом, даже пускали по доске, но находились всё новые и новые желающие\nНедаром говорят: если нельзя, но очень хочется, то можно. А особенно если никто не видит и не узнает.";
			link.l1 = "Ты тоже пришёл за сокровищем, Люка?";
			link.l1.go = "lepricon_15";
		break;
		
		case "lepricon_15":
            dialog.text = "Глупый вопрос. А что я, по-твоему, делаю так далеко от родной Эспаньолы среди этих развалин? Но я оказался хитрее вас: зная вашу гнилую пиратскую натуру, я просто подождал... как видишь, сделал правильно: ослеплённые золотом, вы вцепились друг другу в глотки, и в итоге остался всего один противник, усталый и раненый...";
			link.l1 = "Противник? Так-то ты 'соблюдаешь' кодекс своего патрона, Маркуса Тиракса! Как те, кого он пускал по доске?!";
			link.l1.go = "lepricon_16";
		break;
		
		case "lepricon_16":
            dialog.text = "В отличие от вас, на меня кодекс не распространяется. Я не пират. У меня даже нет корабля - чтобы добраться сюда, я зафрахтовал чужую посудину. Я буканьер в узком смысле этого слова: я охотник, добываю на Эспаньоле буйволов и делаю букан. Гнусные испанцы, которым мы, французские буканьеры, мешаем жить, заставили меня искать защиты и поддержки у Маркуса, и я помогаю ему за это в его делах\nНо я не пират, хотя в рукопашных схватках я и мои люди ничуть не хуже корсаров - ты сам это видел.";
			link.l1 = "Мы с тобой съели вместе фунт соли, Лепрекон. Вместе нюхали порох, прикрывали друг другу спины. Разве для тебя это пустой звук?";
			link.l1.go = "lepricon_17";
		break;
		
		case "lepricon_17":
            dialog.text = "Буду с тобой откровенным, Принц: ты никогда мне не нравился. Потому что ты выскочка. Ты просто наглый, распущенный юнец, любитель вина и падших женщин, провернувший под началом Тиракса несколько удачных прибыльных дел и вообразивший себя великим пиратом\nКроме того, в тебе видны задатки мясника. Неужели ты думаешь, что дикие бесчинства твоей команды в Картахене придали тебе веса среди берегового братства? Только среди таких же отморозков, как ты сам.";
			link.l1 = "Смешно слушать! Можно подумать, что ты сам ангел! Старый негодяй!";
			link.l1.go = "lepricon_18";
		break;
		
		case "lepricon_18":
            dialog.text = "Кажется, мы всё прояснили. Теперь пора заканчивать эту комедию. Черти в аду тебя уже заждались.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionLepriconFight");
		break;
		
		// Тагофа - проводник к Мериде
		case "tagofa":
            dialog.text = "Тагофа приветствует тебя, сын моря. Ты хочешь, чтобы я показал тебе путь к испанскому поселению в горах?";
			link.l1 = "Именно так. Смотрю, ты хорошо знаешь наш язык, в отличие от твоих соплеменников...";
			link.l1.go = "tagofa_1";
		break;
		
		case "tagofa_1":
            dialog.text = "Тагофе часто приходилось иметь дело с яланауи... Большую часть дороги нам предстоит пройти по реке. Вам понадобятся лодки. У вас они есть?";
			link.l1 = "А у вас? Мы бы взяли на время, под залог...";
			link.l1.go = "tagofa_2";
		break;
		
		case "tagofa_2":
            dialog.text = "Наша деревня маленькая, лодок мало, и те, что есть - годны только для ловли рыбы. Нужны хорошие лодки. Такие, как на ваших кораблях. И столько, чтобы туда поместились все ваши люди.";
			link.l1 = "Кхм... Это понадобится шесть шлюпок. Столько на корабле нет.";
			link.l1.go = "tagofa_3";
		break;
		
		case "tagofa_3":
            dialog.text = "Так сделайте их. Вы, белые, умеете на берегу ваши огромные корабли ремонтировать, что вам стоит смастерить несколько лодок.";
			link.l1 = "Хех, похоже, ты прав. Тагофа, проведи нас к этой реке - надеюсь, это недалеко?";
			link.l1.go = "tagofa_4";
		break;
		
		case "tagofa_4":
            dialog.text = "Недалеко. Следуй за мной.";
			link.l1 = "...";
			link.l1.go = "tagofa_5";
		break;
		
		case "tagofa_5":
           DialogExit();
		   npchar.dialog.currentnode = "tagofa_6";
		   LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_MeridaGotoRiver", 5.0);
		break;
		
		case "tagofa_6":
            dialog.text = "Вот река. Отсюда мы начнём свой путь. Готовьте лодки, и мы сразу отправимся.";
			link.l1 = "Ясно, Тагофа. Я скажу, когда всё будет готово.";
			link.l1.go = "tagofa_7";
		break;
		
		case "tagofa_7":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.dialog.currentnode = "tagofa_8";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.Mtraxx = "merida_boats";
			pchar.questTemp.Mtraxx.Boats = "true";
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
			// Лепрекона - гулять
			sld = characterFromId("Lepricon");
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SetFunctionTimerCondition("Mtraxx_MeridaBoatLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "tagofa_8":
            dialog.text = "Лодки готовы, белый вождь?";
			link.l1 = "Да. Мои люди сейчас в них разместятся и будут готовы к отплытию.";
			link.l1.go = "tagofa_9";
		break;
		
		case "tagofa_9":
            dialog.text = "Очень хорошо. Садись вместе со мной в первую лодку. Тагофа покажет путь.";
			link.l1 = "";
			link.l1.go = "tagofa_10";
		break;
		
		case "tagofa_10":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "Mtraxx_MeridaRiverTrip", -1);
			chrDisableReloadToLocation = true;
		break;
		
		case "tagofa_11":
            dialog.text = "Речной путь окончен. До испанского поселения осталось близко. Отсюда берёт бег тропа - нужно всё время следовать по ней. Не заблудимся. Мы обогнули по реке лес, в котором охотятся индейцы капонг, но тут тоже их владения. Надо быть осторожными.";
			link.l1 = "Не переживай. Мы порвём этих капонгов, если они только осмелятся высунуть свои раскрашенные физиономии.";
			link.l1.go = "tagofa_12";
		break;
		
		case "tagofa_12":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_warning.win_condition.l1 = "locator";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.location = "Serpentine2";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator_group = "quest";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator = "detector1";
			pchar.quest.mtraxx_merida_warning.function = "Mtraxx_MeridaWarning";
			chrDisableReloadToLocation = false;
		break;
		
		case "tagofa_13":
            dialog.text = "";
			link.l1 = "Эй! Тагофа! Посмотри сюда - что это такое стоит посреди дороги? Какая-то индейская штуковина.";
			link.l1.go = "tagofa_14";
		break;
		
		case "tagofa_14":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Serpentine2", "goto", "goto5");
			LAi_ActorGoToLocator(npchar, "quest", "quest1", "Mtraxx_MeridaWarning", -1);
		break;
		
		case "tagofa_15":
            dialog.text = "Это знак индейцев капонг. Предупреждение. Указывает - не ходить дальше. Капонги нас уже заметили.";
			link.l1 = "А что будет, если мы пойдём? Нападут на нас?";
			link.l1.go = "tagofa_16";
		break;
		
		case "tagofa_16":
            dialog.text = "Да, белый вождь. Нападут. Сразу атаковать они не решились - видать, вы грозно выглядите. Но знак поставили.";
			link.l1 = "Плевать на этот знак. Мы идём дальше. А если сунутся - получат по зубам. Отря-яд! Слушай мою команду! Приготовиться к бою! Внимательно смотреть по сторонам!";
			link.l1.go = "tagofa_17";
		break;
		
		case "tagofa_17":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_capong.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_capong.win_condition.l1.location = "Merida_jungle_01";
			pchar.quest.mtraxx_merida_capong.function = "Mtraxx_MeridaPrepareCapongAttack";
		break;
		
		case "tagofa_18":
            dialog.text = "Белый вождь и его люди сокрушили капонгов. Вы и правда сильные воины. Испанский город уже близко. За той длинной скалой тропа выходит в долину. Дальше вы увидите водопад. Пройдёте вперёд - и вы на месте. Тагофа к испанцам не пойдёт. Я буду ждать вас у водопада.";
			link.l1 = "Хорошо. Вперёд!";
			link.l1.go = "tagofa_19";
		break;
		
		case "tagofa_19":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_merida_exittown.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exittown.win_condition.l1.location = "Merida_ExitTown";
			pchar.quest.mtraxx_merida_exittown.function = "Mtraxx_MeridaExitTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "15");
		break;
		
		case "tagofa_20":
            dialog.text = "Вот мы и вернулись назад, белый вождь. Тагофа выполнил своё обещание.";
			link.l1 = "Благодарствую, Тагофа. Ты отлично справился с поставленной задачей.";
			link.l1.go = "tagofa_21";
		break;
		
		case "tagofa_21":
            dialog.text = "Тагофе пора идти. Хайами очень ждёт меня. Прощай, сын моря.";
			link.l1 = "Удачи, сын леса. Привет супруге!";
			link.l1.go = "tagofa_22";
		break;
		
		case "tagofa_22":
            DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_final.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_final.win_condition.l1.location = "Shore_ship3";
			pchar.quest.mtraxx_merida_final.function = "Mtraxx_MeridaFinal";
			ChangeIndianRelation(7.0);
		break;
		
		// дозорный у Мериды
		case "merida_guard":
            dialog.text = "Эй! Кто вы такие и что вам здесь нужно?";
			link.l1 = "Нам нужно попасть в Мериду и побеседовать с вашим губернатором, или кто там у вас вместо него...";
			link.l1.go = "merida_guard_1";
		break;
		
		case "merida_guard_1":
            dialog.text = "Мы не пускаем чужаков в Мериду. Уходите отсюда!";
			link.l1 = "Приятель, мы не для того двое суток гребли веслами по реке среди плавучих коряг и прорывались через толпу дикарей, чтобы сейчас развернуться и уйти. Повторяю: я хочу говорить с вашим деревенским старостой! И тогда, возможно, ваш посёлок останется в целости.";
			link.l1.go = "merida_guard_2";
		break;
		
		case "merida_guard_2":
            dialog.text = "Ты угрожаешь нам, ладрон?";
			link.l1 = "Как ты догадался? Да, угрожаю. Если мы не получим то, за чем пришли, мирным путём, то возьмём это силой.";
			link.l1.go = "merida_guard_3";
		break;
		
		case "merida_guard_3":
            dialog.text = "Тебе никогда не войти в Мериду, проклятый пират! Тревога, враг у ворот!";
			link.l1 = "...";
			link.l1.go = "merida_guard_4";
		break;
		
		case "merida_guard_4":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DoQuestFunctionDelay("Mtraxx_MeridaHouseGuards", 5.0);
		break;
		
		// мэр Мериды
		case "merida_head":
            dialog.text = "Проклятые ладроны!..";
			link.l1 = "Оставим эти излияния, сеньор. Мы сразу предложили решить вопрос миром, но ваш начальник стражи оказался весьма ретивым служакой... Так что всё то, что произошло на улицах Мериды, в значительной степени именно его вина.";
			link.l1.go = "merida_head_1";
		break;
		
		case "merida_head_1":
            dialog.text = "Что вам нужно, негодяи? Наш город мал, сюда почти никто не заглядывает, ни от генерал-губернатора, ни из метрополии. У нас нет ни золота, ни серебра, ни ценных товаров.";
			link.l1 = "Тогда как же вы ухитрились отгрохать себе такой особняк, ваше сиятельство? Да и сама Мерида не производит впечатления нищей деревушки.";
			link.l1.go = "merida_head_2";
		break;
		
		case "merida_head_2":
            dialog.text = "Все жители Мериды приложили много сил и труда, чтобы возвести наш город.";
			link.l1 = "Да ну? Впрочем, довольно разглагольствований. Я знаю, что вы нашли в окрестных горах россыпь изумрудов и опалов. Не прибедняйтесь, кабальеро. Вы богаты. И вам придётся поделиться с нами вашими находками.";
			link.l1.go = "merida_head_3";
		break;
		
		case "merida_head_3":
            dialog.text = "Изумруды? Опалы? Это не более, чем лживые россказни! Изумруды добывают далеко на запад отсюда, а опалы...";
			link.l1 = "Хватит врать, испанская собака! Ты, кажется, ещё не понял, с кем имеешь дело. Или мы получим все камни, или ваш чудесный городок превратится в горы пепла и углей, а оставшихся в живых жителей прикончат шныряющие по округе капонги. А с тобой будет разговор особый: примерим тебе испанские сапоги, зажжём фитили между пальцами... у нас много способов развязывать языки.";
			link.l1.go = "merida_head_4";
		break;
		
		case "merida_head_4":
            dialog.text = "";
			link.l1 = "Побледнел? То-то же. Ну? Где камни?";
			link.l1.go = "merida_head_5";
		break;
		
		case "merida_head_5":
            dialog.text = "Эти самоцветы - всё, что есть у жителей Мериды. Мы добывали их не один год, дробя камни в горах, отбиваясь от дикарей...";
			link.l1 = "И? Ты пытаешься меня разжалобить? Гони камни. А будешь упорствовать - не будет ни Мериды, ни её жителей. Мы ждём.";
			link.l1.go = "merida_head_6";
		break;
		
		case "merida_head_6":
            dialog.text = "Вам это так просто не сойдёт, гнусные бандиты, Бог всё видит и покарает вас, мерзавцы...";
			link.l1 = "Ещё одно оскорбление - и я отправлю своего человека за жаровней.";
			link.l1.go = "merida_head_7";
		break;
		
		case "merida_head_7":
            dialog.text = "Я отдам вам камни, если вы поклянётесь не трогать город и тех людей, кого вы ещё не убили.";
			link.l1 = "Я уже сказал тебе - меня не интересует твой город. Тащи самоцветы, и мы уходим отсюда.";
			link.l1.go = "merida_head_8";
		break;
		
		case "merida_head_8":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "Mtraxx_MeridaOpenChest", -1);
		break;
		
		case "merida_head_9":
            dialog.text = "Забирайте свою кровавую добычу и помните, что вы обрекли целый город на нищету.";
			link.l1 = "Ты серьёзно? Добудете себе ещё самоцветов, горы рядом и никуда не делись... Жан, иди, посмотри, что там в сундуке у дона.";
			link.l1.go = "merida_head_10";
		break;
		
		case "merida_head_10":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
		break;
		
		case "merida_head_sleep":
            dialog.text = "Ты обещал мирно покинуть город, после того, как получишь камни. Камни ты получил, а твои ладроны подожгли наши дома. Ты лжец и гнусный пират. Надеюсь, что пламя ада, которое тебя ждёт, будет таким же жарким.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep2");
		break;
		
		// капитан пинаса Китти
		case "kittycap":
            dialog.text = TimeGreeting()+", уважаемый. Чем обязан вашему визиту?";
			link.l1 = "Я от Тиракса. Мне приказано довести твоё судно до Бриджтауна. Ты готов?";
			link.l1.go = "kittycap_1";
		break;
		
		case "kittycap_1":
            dialog.text = "Ну наконец-то! Да, моя команда готова немедленно выйти в море.";
			link.l1 = "Отлично. Ставь паруса. Мы отправляемся!";
			link.l1.go = "kittycap_2";
		break;
		
		case "kittycap_2":
		    DialogExit();
            LAi_CharacterDisableDialog(npchar);
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			LAi_SetImmortal(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
		    pchar.quest.mtraxx_ignasio_sail.win_condition.l1 = "location";
			pchar.quest.mtraxx_ignasio_sail.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.mtraxx_ignasio_sail.function = "Mtraxx_IgnasioArrive";
			SetFunctionTimerCondition("Mtraxx_IgnasioTimeOver", 0, 0, 30, false);
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1 = "NPC_Death";
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1.character = "Mtr_KittyCap";
			pchar.quest.mtraxx_ignasio_sinkkitty.function = "Mtraxx_IgnasioKittySink";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "kittycap_3":
            dialog.text = "Спасибо за помощь, капитан! Под вашей защитой я чувствовал себя, как за стеной форта.";
			link.l1 = "Не за что, приятель. Всё будет оплачено Маркусом. Удачи!";
			link.l1.go = "kittycap_4";
		break;
		
		case "kittycap_4":
            DialogExit();
			npchar.lifeday = 0;
			RemoveCharacterCompanion(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			Mtraxx_IgnasioCreateMarko();
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		// Игнасио Марко
		case "ignasio":
            dialog.text = "Приветствую бравого капитана! Позвольте представиться - капер на службе Англии Игнасио Марко, владелец и капитан полакра 'Тореро'.";
			link.l1 = TimeGreeting()+", уважаемый. Капитан "+GetFullName(pchar)+" к вашим услугам. Чем могу быть полезен?";
			link.l1.go = "ignasio_1";
		break;
		
		case "ignasio_1":
            dialog.text = "О, я вас сразу узнал, месье "+GetFullName(pchar)+". Слухи о ваших... возможностях и покровителях не раз доносились до меня в самых разных частях архипелага. И я думаю, что вас бы заинтересовало моё предложение.";
			link.l1 = "Какое предложение?";
			link.l1.go = "ignasio_2";
		break;
		
		case "ignasio_2":
            dialog.text = "Давайте пойдём в таверну, и за кружкой рома я всё вам расскажу. Неудобно как-то посреди улицы...";
			link.l1 = "Хорошо... Идёмте!";
			link.l1.go = "ignasio_3";
		break;
		
		case "ignasio_3":
            DialogExit();
			FreeSitLocator("Bridgetown_tavern", "sit_front2");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Bridgetown_tavern", "sit", "sit_front2", "Mtraxx_IgnasioInTavern", -1);
		break;
		
		case "ignasio_4":
			LAi_SetSitType(pchar);
            dialog.text = "По кружечке, капитан?";
			link.l1 = "Без возражений!";
			link.l1.go = "ignasio_5";
		break;
		
		case "ignasio_5":
			LAi_Fade("", "");
            dialog.text = "Хех, а здесь и впрямь не разбавляют ром водой...";
			link.l1 = "И не подают тухлую рыбу, да-да. О чём вы хотели поговорить, сударь?";
			link.l1.go = "ignasio_6";
		break;
		
		case "ignasio_6":
            dialog.text = "Мне нравится ваша решительность, месье. Скажите, вы в курсе о противостоянии между Англией и Голландией, которое называют торговой войной?";
			link.l1 = "Ещё как в курсе. Имел удовольствие соприкоснуться с ней.";
			link.l1.go = "ignasio_7";
		break;
		
		case "ignasio_7":
            dialog.text = "Тогда объяснять долго не придётся. Являясь английским капером, я занимаю соответствующую сторону в этой войне. Вы же - работаете сами на себя и ещё на кое-кого, чьё имя я тут вслух упоминать не буду... то есть, вам должно быть всё равно, против кого вести боевые действия...";
			link.l1 = "Почти. С Францией я не воюю, уж увольте.";
			link.l1.go = "ignasio_8";
		break;
		
		case "ignasio_8":
            dialog.text = "Капитан, ну это само собой! Итак, к делу: между Кюрасао и Тринидадом находится один маленький необитаемый островок, не обозначенный на картах. С недавних пор, я бы сказал - совсем с недавних, туда повадились заходить голландские корабли и караваны для пополнения запасов воды и небольшого ремонта. Видимо, голландцы считают, что про этот островок известно только им, однако это не так, хе-хе\nПару дней назад там отдал якоря караван, который основательно потрепало штормом. Голландцы намерены отремонтировать на суше свои суда. Флагман лишился грот-мачты, так что застряли они надолго. Но вся соль состоит в том, что трюмы кораблей этой эскадры заполнены ценными товарами, включая серебро! Голландцы заняты починкой кораблей, часть команды находится на суше, считают, что в безопасности...";
			link.l1 = "А тут внезапно появляемся мы с вами, так?";
			link.l1.go = "ignasio_9";
		break;
		
		case "ignasio_9":
            dialog.text = "В точку, капитан. Одному мне этот караван не по зубам, а вот на пару с вами - другое дело. Ну как, рискнете? Корабль у меня отличный, матросы не лыком шиты, да и сам я не первый год на шканцах. Ваши способности тоже... внушают уважение.";
			link.l1 = "Сколько у нас времени?";
			link.l1.go = "ignasio_10";
		break;
		
		case "ignasio_10":
            dialog.text = "Достаточно, если не станем терять его попусту и отправимся в путь немедленно.";
			link.l1 = "Тогда запасаемся боеприпасами и оружием, капитан Игнасио Марко, и поднимаем паруса. Какое точное местоположение острова?";
			link.l1.go = "ignasio_11";
		break;
		
		case "ignasio_11":
            dialog.text = "12 градусов 40 минут северной широты, 64 градуса 11 минут западной долготы. Запомнили?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Isladecoche")) link.l1 = "Хех! Дежавю... Да, запомнил.";
			else link.l1 = "Да, запомнил.";
			link.l1.go = "ignasio_12";
		break;
		
		case "ignasio_12":
            dialog.text = "Я отправляюсь на свой 'Тореро'. Жду вас, капитан!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioAddMarko");
		break;
		
		case "ignasio_13":
            dialog.text = "Жаркая была схватка, да, капитан? Ну, теперь самое приятное: делим добытое. Половина мне и моим людям, половина - вам.";
			link.l1 = "Давайте...";
			link.l1.go = "ignasio_14";
		break;
		
		case "ignasio_14":
			LAi_Fade("", "");
			WaitDate("", 0, 0, 0, 3, 10); 
			pchar.questTemp.Mtraxx.Silver = GetSquadronGoods(pchar, GOOD_SILVER)-sti(pchar.questTemp.Mtraxx.Silver);
			pchar.questTemp.Mtraxx.Mahogany = GetSquadronGoods(pchar, GOOD_MAHOGANY)-sti(pchar.questTemp.Mtraxx.Mahogany);
			if (sti(pchar.questTemp.Mtraxx.Silver) < 100)
			{
				dialog.text = "Капитан, простите: это что? Где наше серебро? Вы утопили весь товар?";
				if (sti(pchar.questTemp.Mtraxx.Mahogany) < 200) 
				{
					link.l1 = "Э-э-м-м...";
					link.l1.go = "ignasio_15_1";
				}
				else
				{
					link.l1 = "С серебром какая-то ерунда вышла, но хоть красного дерева удалось захватить. Поделим его.";
					link.l1.go = "ignasio_15_11";
				}
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 300 && sti(pchar.questTemp.Mtraxx.Silver) > 100)
			{
				dialog.text = "Гхм... Маловато как-то. Я думал, будет больше...";
				link.l1 = "Ну уж сколько получилось.";
				link.l1.go = "ignasio_15_2";
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 700 && sti(pchar.questTemp.Mtraxx.Silver) > 300)
			{
				dialog.text = "Неплохо, неплохо... Хотя я думал, что побогаче добыча будет.";
				link.l1 = "Ну уж сколько получилось.";
				link.l1.go = "ignasio_15_3";
				break;
			}
            dialog.text = "Хорошая работа, месье. Добыча нам досталась весьма недурственная...";
			link.l1 = "Не могу с вами не согласиться, капитан.";
			link.l1.go = "ignasio_15_4";
		break;
		
		case "ignasio_15_1":
			dialog.text = "Похоже, у вас серьёзные проблемы с головой. Зря я с вами связался. Ребята! Уходим!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_11":
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
			dialog.text = "А больше ничего и не остаётся. С паршивой овцы хоть шерсти клок... Ребята! В шлюпки!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_2":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "Ладно, что добыли, то добыли. Расходимся.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_3":
            RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "Ладно, что добыли, то добыли. Расходимся. В любом случае, дельце было успешным, хе-хе.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_4":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "Плодотворное у нас получилось знакомство. Возможно, не в последний раз видимся, капитан!";
			link.l1 = "Ещё найдёте жирных купцов - не забудьте позвать меня, хе-хе...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_boarding":
            dialog.text = "Полагаю, это не случайная встреча, да, капитан?";
			link.l1 = "Ты не дурак, чтобы этого не понимать. За тобой должок тянется, за подставу. Какую - ты понимаешь. Да и за моего друга Жана Пикара, проданного по твоей милости на плантацию, тоже взыскать нужно... Ты проиграл, Игнасио, и я собираюсь вздёрнуть тебя на ноке рея. Но ты можешь облегчить свою участь...";
			link.l1.go = "ignasio_boarding_1";
		break;
		
		case "ignasio_boarding_1":
            dialog.text = "Даже интересно - что же может разжалобить тебя?";
			link.l1 = "Информация. Отправим тебя в трюм, а потом побеседуем о результатах твоей разведки в Гаване...";
			link.l1.go = "ignasio_boarding_2";
		break;
		
		case "ignasio_boarding_2":
            dialog.text = RandSwear()+" Этого я не ожидал... Даже не мечтай: Барбазон сразу поймёт, от кого ушли сведения Тираксу, и тогда мне не будет житья... А как Барбазон расправляется с теми, кто его предал - тебе лучше не знать. А я видел.";
			link.l1 = "Предпочитаешь виселицу?";
			link.l1.go = "ignasio_boarding_3";
		break;
		
		case "ignasio_boarding_3":
            dialog.text = "Предпочитаю умереть в бою. Защищайся!";
			link.l1 = "...";
			link.l1.go = "ignasio_boarding_4";
		break;
		
		case "ignasio_boarding_4":
            DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "spy_sailor":
            dialog.text = "Капитан! Капитан! Быстрее, на борт, уходим! Прямо на нас движется мощная испанская эскадра!";
			link.l1 = RandSwear()+"Этого следовало ожидать... Всё точно так же, как с Пикаром. Сколько испанцев и что за корабли, ты рассмотрел в трубу?";
			link.l1.go = "spy_sailor_1";
		break;
		
		case "spy_sailor_1":
            dialog.text = "Да, капитан. Три корабля. Флагман - тяжёлый галеон, остальные два - корвет и шебека.";
			link.l1 = "Все на борт! Может, ещё успеем скрыться.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioOurEscape");
		break;
		
		// индей-кариб в гроте Порто-Белло
		case "grot_canib":
            dialog.text = "Хайя! Проклятый яланауи явиться в наш лес! Убить его! Хайя!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekGrotFight");
		break;
		
		// бандит у пещеры Панамы
		case "cave_bandit":
            dialog.text = "Эй! Что ты тут шаришься? А-а, никак решил прихватить чужие вещички? Ну, пижон, сейчас мы тебя проучим!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekCaveFight");
		break;
		
		case "carpenter":
            dialog.text = "Эй! А ну стоять всем! Или шарахну картечью из пушки - всех положу, "+RandSwear()+"";
			link.l1 = "Мы стоим. Но только всех одним выстрелом ты не уложишь, приятель, а пока будете перезаряжать орудие - мы вас перережем. Так что давай лучше поговорим.";
			link.l1.go = "carpenter_1";
		break;
		
		case "carpenter_1":
            dialog.text = "Ты главный, что ли? Отвечай!";
			link.l1 = "Я капитан "+GetFullName(pchar)+". А ты, вероятно, замещаешь здесь Рыжего Вульфа, пока он в плавании?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
            dialog.text = "Что тебе здесь надо, капитан "+GetFullName(pchar)+"?! Мы никого в гости не приглашаем!";
			link.l1 = "Как твоё имя? Я хочу знать, с кем разговариваю.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
            dialog.text = "Родгар Янссен моё имя.";
			link.l1 = "Вижу, Родгар Янссен, ты не в курсе случившегося. Нет у тебя больше капитана. И корвета вашего тоже нет. Разбомбили испанцы вашу 'Фрейю' у берегов Эспаньолы, а всю команду перебили...";
			link.l1.go = "carpenter_4";
		break;
		
		case "carpenter_4":
            dialog.text = RandSwear()+" Вульфрик... Аргх, откуда мне знать, что ты не лжёшь?";
			link.l1 = "У меня судовой журнал твоего бывшего капитана! Мы выловили кое-какие вещички на месте гибели 'Фрейи'. Благодаря журналу я и нашёл этот остров и ваш... горд.";
			link.l1.go = "carpenter_5";
		break;
		
		case "carpenter_5":
            dialog.text = "Хех! Ты не ответил на вопрос: зачем вы сюда явились, на никому не известный остров?";
			link.l1 = "Врать не буду, приятель. Ходят слухи, что у Рыжего Вульфа припрятаны немалые сбережения, собранные за годы пиратской жизни. На его затонувшем корабле ничего не нашли, значит - сокровища в другом месте. Я считаю, что они тут, в вашем убежище. Вульфрику они уже не нужны - так пусть достанутся хорошим людям...";
			link.l1.go = "carpenter_6";
		break;
		
		case "carpenter_6":
            dialog.text = "Ха! Приятель, я тебя огорчу: ни я, ни кто-либо из команды, никогда не видел сокровищ Вульфа. Ни здесь, ни где-либо ещё. А спрашивать об этом у Вульфрика было опасно для жизни.";
			link.l1 = "Значит, придётся их поискать в вашем поселке. Глядишь - отыщутся. Так ты уберёшь свою пушку, или мне начинать штурм? У вас нет шансов, Родгар, если понадобится - я доставлю сюда пару орудий с корабля, и от вашего частокола останутся одни щепки.";
			link.l1.go = "carpenter_7";
		break;
		
		case "carpenter_7":
            dialog.text = "Прежде чем умереть, мы захватим с собой в ад немало твоих людей, а может и тебя!";
			link.l1 = "А смысл? У вас нет больше капитана, никто за вами не придёт. Даже если я уйду - вы просто передохнете здесь с голода через некоторое время... никто, кроме меня, не знает об этом острове!";
			link.l1.go = "carpenter_8";
		break;
		
		case "carpenter_8":
            dialog.text = "У тебя есть предложения?";
			link.l1 = "Да, есть. Отойди от пушки, Родгар, и успокой своих людей. Я клянусь тебе, что никого из вас не убью. Хочешь - пополните мою команду, не хочешь - могу вывезти с острова и высадить в населённом месте.";
			link.l1.go = "carpenter_9";
		break;
		
		case "carpenter_9":
            dialog.text = "Поклянись перед всеми своими людьми!";
			link.l1 = "Клянусь! Даю слово, что ни с кого из вас не упадёт и волоса.";
			link.l1.go = "carpenter_10";
		break;
		
		case "carpenter_10":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_11";
			LAi_SetActorType(npchar);
			LAi_ActorDialog(npchar, pchar, "", -1, 0);
			for (i=1; i<=2; i++) // 
			{
				sld = CharacterFromID("Islamona_fort_pirate_"+i);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "carpenter_11":
            dialog.text = "Капитан, надеюсь, ты сдержишь своё обещание.";
			link.l1 = "Я всегда держу слово. Сколько вас осталось?";
			link.l1.go = "carpenter_12";
		break;
		
		case "carpenter_12":
            dialog.text = "Все перед тобой. Трое. Остальные погибли в джунглях, когда решили атаковать вас. Я говорил им, но они не послушали...";
			link.l1 = "Ясно...";
			link.l1.go = "carpenter_13";
		break;
		
		case "carpenter_13":
            dialog.text = "Провизия подошла к концу. Мы уже начали охотиться на попугаев. 'Фрейя' давно должна была вернуться. Мы подозревали... теперь знаем.";
			link.l1 = "Благодарите Бога, что я занялся поисками сокровищ вашего капитана. Где он мог прятать их?";
			link.l1.go = "carpenter_14";
		break;
		
		case "carpenter_14":
            dialog.text = "Как я уже сказал - никто не видел его сокровищ. Хотя они есть: Вульфрик не транжирил деньги, всю добычу обращал в монету и золото, с командой делился хорошо, а свою долю хранил неведомо где. Никто бы не рискнул проследить за ним... были любопытные, но быстро не стало. Клянусь, я не знаю, где он прятал свои богатства. Можете обыскать весь посёлок.";
			link.l1 = "Это я и собираюсь сделать. Где дом Вульфрика?";
			link.l1.go = "carpenter_15";
		break;
		
		case "carpenter_15":
            dialog.text = "За частоколом слева. Единственное двухэтажное строение тут.";
			link.l1 = "Хорошо. Чем ты тут занимался?";
			link.l1.go = "carpenter_16";
		break;
		
		case "carpenter_16":
            dialog.text = "Я плотник, а эти двое - мои подручные. Мы кренговали и ремонтировали 'Фрейю' после походов. Мы сможем пригодиться в твоей команде.";
			link.l1 = "Понятно. Вы приняты на службу, подробности обсудим позже. А сейчас убирайте эту пушку с прохода, Родгар, и никуда не уходите из поселка. Я приступаю к поискам.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekInFort");
		break;
		
		case "carpenter_17":
            dialog.text = "Будут какие-то задания, кэп?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.WolfreekGord"))
			{
				link.l1 = "Да. Сокровища вашего капитана найдены. Надежно он их запрятал. Но меня не перехитрить!";
				link.l1.go = "carpenter_18";
				break;
			}
			link.l2 = "Родгар, ты и твои люди могут отремонтировать моё судно?";
			link.l2.go = "repair";
			link.l3 = "Родгар, я хочу оставить на острове один из своих кораблей.";
			if (CheckAttribute(npchar, "portman.info")) link.l3.go = "shipstock";
			else link.l3.go = "shipstock_info";
			if (sti(npchar.portman > 0))
			{
				link.l4 = "Родгар, я хочу забрать свой корабль обратно.";
				link.l4.go = "shipstockreturn";
			}
			if (!CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Послушай, нет ли здесь какого-нибудь пустого дома, который можно было бы оборудовать под склад товаров?";
				link.l5.go = "storadge";
			}
			if (CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Родгар, я хочу пройти на склад. Будь так любезен - отопри дверь.";
				link.l5.go = "storadge_3";
			}
			link.l99 = "Пока ничего...";
			link.l99.go = "carpenter_exit";
		break;
		
		case "carpenter_exit":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
		break;
		
		case "carpenter_18":
            dialog.text = "Поздравляю, кэп. Что будешь делать дальше? Уходим отсюда?";
			link.l1 = "Ты долго здесь, на острове, жил?";
			link.l1.go = "carpenter_19";
		break;
		
		case "carpenter_19":
            dialog.text = "Долго. Чай, уже больше года прошло с того момента, как Вульфрик поставил меня руководить тут плотницкими работами.";
			link.l1 = "Я решил, что негоже пропадать такой замечательной тайной базе. Теперь этот посёлок будет мой, как прежде - Рыжего Вульфа. Если хочешь, могу оставить тебя и твоих людей здесь. Будешь распоряжаться тут. Провизия, ром, лекарства - будут.";
			link.l1.go = "carpenter_20";
		break;
		
		case "carpenter_20":
            dialog.text = "Это было бы просто замечательно, капитан. Я уже сильно привык к жизни на берегу, на этом острове.";
			link.l1 = "Вот и хорошо. Кстати, как называется остров?";
			link.l1.go = "carpenter_21";
		break;
		
		case "carpenter_21":
            dialog.text = "Исла Мона, кэп.";
			link.l1 = "Исла Мона... Вполне возможно, мы построим здесь ещё несколько зданий... Но это позже. А пока - для тебя всё будет, как и прежде, только с другим капитаном.";
			link.l1.go = "carpenter_22";
		break;
		
		case "carpenter_22":
            dialog.text = "Договорились. Только береги себя, капитан.";
			link.l1 = "Само собой. Ладно, Родгар, удачи, мне пора в Ла Вегу.";
			link.l1.go = "carpenter_exit";
			npchar.portman = 0;
			AddDialogExitQuestFunction("Mtraxx_WolfreekComplete");
		break;
		
		case "repair":
			if (CheckSelfRepairConditions())
			{
				dialog.text = "Конечно, кэп!.. Нужны только доски и парусина, а работу мы сделаем. Ступай в бухту, где причалил, и прикажи матросам подготовить материалы.";
				link.l1 = "Хорошо, иду. И вы тоже не мешкайте.";
			link.l1.go = "repair_1";
			}
			else
			{
				dialog.text = "Кэп, мы, конечно, можем, но по-моему тебе не требуется ремонт.";
				link.l1 = "Я просто поинтересовался...";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		case "repair_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation(Pchar.location.from_sea, "reload", "sea", "Mtraxx_WolfreekRepairShore");
		break;
		
		case "shipstock_info":
			npchar.portman.info = "true";
            dialog.text = "Это можно сделать, кэп. Но есть некоторые ограничения: на Исла Моне всего два места, где можно безопасно держать на приколе судно неограниченное время. Так что стоянка возможна только для двух кораблей одновременно. Но зато твой корабль будет гарантированно в целости и сохранности. Второе: на судне не должно быть никого, кроме вахтенного офицера: наш остров невелик, и содержать здесь ораву матросов, как ты сам понимаешь, нельзя. И третье: мы не сможем поставить на хранение корабли первого класса: бухты для этого слишком малы.";
			link.l1 = "Всё ясно. Я готов передать тебе судно.";
			link.l1.go = "shipstock";
			link.l2 = "Я всё понял, пойду, подготовлю судно для постановки на якорь.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "shipstock":
			if (sti(npchar.portman) == 2)
			{
				dialog.text = "Кэп, на приколе уже стоит два твоих судна. Больше нет места.";
				link.l1 = "Ах да, точно, я и забыл.";
				link.l1.go = "carpenter_exit";
				break;
			}
			if (GetCompanionQuantity(pchar) < 2)
			{
				dialog.text = "Кэп, так у тебя всего один корабль в эскадре.";
				link.l1 = "Кхм... Пожалуй, надо пить меньше рому...";
				link.l1.go = "carpenter_exit";
				break;
			}
            dialog.text = "Какой именно корабль ты хочешь оставить?";
			for(i=1; i<COMPANION_MAX; i++)
			{
				int cn = GetCompanionIndex(PChar, i);
				if( cn > 0 )
				{
					ref chref = GetCharacter(cn);
					if (!GetRemovable(chref)) continue;

					attrL = "l"+i;
					Link.(attrL) = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "ShipStockMan_" + i;
				}
			}
			Link.l9 = "Стоп, я передумал.";
			Link.l9.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Посмотрим, что это за корабль...";
			Link.l1 = "Хорошо.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Посмотрим, что это за корабль...";
			Link.l1 = "Хорошо.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Посмотрим, что это за корабль...";
			Link.l1 = "Хорошо.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Посмотрим, что это за корабль...";
			Link.l1 = "Хорошо.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
			{
				dialog.text = "Кэп, я уже говорил - корабли первого класса на нашу стоянку поставить нельзя. Слишком велики.";
				Link.l1 = "Ах, да, точно, я и забыл.";
				Link.l1.go = "carpenter_exit";
				break;
			}
			if (sti(chref.Ship.Crew.Quantity) > 0)
			{
				dialog.text = "Кэп, на корабле должен быть только один вахтенный офицер и больше никого. Переведи команду на флагман.";
				Link.l1 = "Ах, да, точно, сейчас сделаем!";
				Link.l1.go = "carpenter_exit";
				break;
			}
			dialog.Text = "Итак, нам надо поставить на хранение "+XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName+"Acc")+" под названием '"+chref.Ship.Name+"'. Я всё правильно понял?";
			Link.l1 = "Да.";
			Link.l1.go = "ShipStock_3";
			Link.l2 = "Нет, я передумал.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_3":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
            chref.ShipInStockMan = NPChar.id;
			chref.ShipInStockMan.MoneyForShip = 0;
            chref.ShipInStockMan.AltDate = GetQuestBookDataDigit();
            SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date");
            RemoveCharacterCompanion(pchar, chref);
            chref.location = "";
            chref.location.group = "";
            chref.location.locator = "";
            npchar.portman = sti(npchar.portman)+1;
            pchar.ShipInStock = sti(pchar.ShipInStock)+1;
			dialog.text = "Хорошо, отгоним его в защищённую от ветров бухту. Заберёшь, когда понадобится.";
			Link.l1 = "Отлично!";
			Link.l1.go = "carpenter_exit";
		break;
		
		case "shipstockreturn":
            if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				dialog.text = "Какой именно корабль будешь забирать, кэп?";
				cn = 1;
				for (i=1; i<MAX_CHARACTERS; i++)
				{
					makeref(chref, Characters[i]);
					if (CheckAttribute(chref, "ShipInStockMan"))
					{
						if (chref.ShipInStockMan == NPChar.id)
						{
							attrL = "l"+cn;
							Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockManBack_" + i;
							cn++;
						}
					}
				}
				link.l9 = "Нет, я передумал. Пусть стоит на якорях дальше.";
				link.l9.go = "carpenter_exit";
			}
			else
			{
				dialog.text = "Кэп, твоя эскадра вряд ли вместит ещё одно судно.";
				link.l1 = "Хм. Ты прав.";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		 case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			dialog.Text = "Забираешь?";
			link.l1 = "Да.";
			link.l1.go = "ShipStockManBack2";
			link.l2 = "Нет, я, пожалуй, передумал - путь стоит дальше.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockManBack2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			npchar.portman = sti(npchar.portman)-1;
            pchar.ShipInStock = sti(pchar.ShipInStock)-1;
		break;
		
		case "storadge":
            dialog.text = "Все домики тут маленькие для такого дела, кэп, но вам это и не нужно. Имеется здоровенный сарай, почти как портовый пакгауз. Его отсюда плохо видно за пальмами. Вульфрик построил его с год назад или даже больше: фундамент из кирпичей, стены из брёвен, пол дощатый, крыша из сплетённых пальмовых листьев и просмоленной парусины. Надёжное строение: ни дождь, ни ветер - нипочём, и ворота запираются на замок\nПостроить построил, а использовал редко, и ни разу не смог заполнить даже на четверть. Сейчас стоит пустой. Пользуйся, если тебе это нужно, туда товара с десяти пинасов можно запихнуть, если до потолка укладывать. Ключ от ворот у меня, я открою. Пойдём смотреть?";
			link.l1 = "Конечно! А, кстати: как у вас с крысами на острове? Не сгрызут мой товар в этом сарае?";
			link.l1.go = "storadge_1";
		break;
		
		case "storadge_1":
            dialog.text = "Вульф сразу это предусмотрел: привёз с материка двух кошек. Правда, про котов для них он не подумал: теперь эти стервы мохнатые, как впадут в охоту - орут, проклятые, днями и ночами, но мышей и крыс ловят исправно. Так что можешь за сохранность груза не беспокоиться. Не промокнет и съеден не будет.";
			link.l1 = "Отлично! Я буду им пользоваться. Ключ держи у себя - так будет надёжнее. Ну, а теперь показывай свой хвалёный склад.";
			link.l1.go = "storadge_2";
		break;
		
		case "storadge_2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.city = "islamona";
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			npchar.MoneyForStorage = 0;
			npchar.storadge = true;
			LaunchStorage(29);
		break;
		
		case "storadge_3":
            dialog.text = "Конечно, кэп. Пошли, проведу тебя.";
			link.l1 = "...";
			link.l1.go = "storadge_4";
		break;
		
		case "storadge_4":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchStorage(29);
		break;
		
		// Мирабель
		case "mirabelle":
			PlaySound("VOICE\Russian\Girl_Q.wav");
            dialog.text = "Ой...";
			link.l1 = "Вот так номер... Девка!.. Ты откуда здесь взялась?";
			link.l1.go = "mirabelle_1";
		break;
		
		case "mirabelle_1":
			PlaySound("VOICE\Russian\Girl_Q.wav");
            dialog.text = "Ой...";
			link.l1 = "...";
			link.l1.go = "mirabelle_2";
		break;
		
		case "mirabelle_2":
            DialogExit();
			npchar.dialog.currentnode = "mirabelle_3";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_74";
			ChangeCharacterAddressGroup(sld, "LaVega_TwoFloorHouse", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		
		case "mirabelle_3":
			PlaySound("VOICE\Russian\other\RapersGirl-01.wav");
            dialog.text = "Сеньор! Сеньор "+pchar.name+", не убивайте меня, прошу! Я ничего не скажу Тираксу! Я ненавижу этого зверя! Умоляю вас, я буду молчать!";
			link.l1 = "...";
			link.l1.go = "mirabelle_4";
		break;
		
		case "mirabelle_4":
			DialogExit();
            npchar.dialog.currentnode = "mirabelle_5";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_80";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "mirabelle_5":
            dialog.text = "";
			link.l1 = "Эй, девка! Слышала? Пойдёшь со мной, или этот суровый парень пришьёт тебя.";
			link.l1.go = "mirabelle_6";
		break;
		
		case "mirabelle_6":
            dialog.text = "Пойду, сеньор, пойду, куда скажете пойду!";
			link.l1 = "Вот и славно. Рот держи на замке: если начнёшь кричать и звать на помощь Тиракса - я сам лично тебя убью. Как твоё имя?";
			link.l1.go = "mirabelle_7";
		break;
		
		case "mirabelle_7":
            dialog.text = "Мирабель...";
			link.l1 = "Будешь вести себя правильно, Мирабель, всё закончится для тебя хорошо. Ни на шаг от меня, и тише мыши.";
			link.l1.go = "mirabelle_8";
		break;
		
		case "mirabelle_8":
            dialog.text = "Клянусь, сеньор...";
			link.l1 = "...";
			link.l1.go = "mirabelle_9";
		break;
		
		case "mirabelle_9":
            DialogExit();
            npchar.dialog.currentnode = "mirabelle_10";
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_85";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
			pchar.questTemp.Mtraxx.Mirabella = "true";
		break;
		
		case "mirabelle_10":
			PlaySound("VOICE\Russian\Girl_Q.wav");
            dialog.text = "Сеньор?..";
			link.l1 = "Ты была умницей, малышка, хвалю. Сейчас мы пойдём на корабль, где ты отправишься под замок. Не бойся, не в трюм - в каюту. Не хватало только, чтобы ты сбежала и донесла на меня Тираксу.";
			link.l1.go = "mirabelle_11";
		break;
		
		case "mirabelle_11":
            dialog.text = "Я не сбегу, сеньор! И я никогда бы не пошла к Тираксу, я ненавижу его! Мерзавец!..";
			link.l1 = "Ого! И что же тебе он такого сделал?";
			link.l1.go = "mirabelle_12";
		break;
		
		case "mirabelle_12":
            dialog.text = "Много чего... Ненавижу его, ненавижу!..";
			link.l1 = "Ясно. Когда прибудем на место, будешь жить в приличном доме. И если не станешь меня сердить - тебя не обидят. Займёшься своим привычным делом, хе-хе. А теперь ступай в шлюпку... Мирабель.";
			link.l1.go = "mirabelle_13";
		break;
		
		case "mirabelle_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1.location = "Shore75";
			pchar.quest.mtraxx_pasq_mirabella.function = "Mtraxx_PasqualeMirabella";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1.location = "Shore77";
			pchar.quest.mtraxx_pasq_mirabella1.function = "Mtraxx_PasqualeMirabella";
			AddPassenger(pchar, npchar, false);//добавить пассажира
			SetCharacterRemovable(npchar, false);
			SetFunctionTimerCondition("Mtraxx_MirabellaSailOver", 0, 0, 30, false); // месяц на доплыть до Исла Моны
		break;
		
		case "mirabelle_14":
            dialog.text = "Мы пришли, сеньор?";
			link.l1 = "Да, милашка. Это мой посёлок и мой дом, ясно? Тут я хозяин. Об этом острове никто не знает, кроме меня, и здесь нет никого, кроме моих людей. Сам я здесь появляться буду не часто - много дел, так что будешь здесь жить и присматривать за моим домом. И смотри, делай это на совесть, чтобы всё было чисто и ухожено, не то отдам тебя Родгару и его плотникам. Можешь гулять в джунглях, на пляжах - сколько хочешь, все равно без корабля отсюда уйти нельзя.";
			link.l1.go = "mirabelle_15";
		break;
		
		case "mirabelle_15":
            dialog.text = "Мне некуда убегать, сеньор "+pchar.name+". У меня никого нет, и я никому не нужна. Разве что опять в бордель продадут...";
			link.l1 = "У очага есть люк в подполье, туда не лезь: не ровен час, упадёшь в пещеру и разобьёшься, или не сможешь назад выбраться и помрёшь с голоду. Жалко будет, что спасал тебя понапрасну.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_16":
            dialog.text = "Не буду лазить туда, сеньор...";
			link.l1 = "На втором этаже спальня. Иди за мной.";
			link.l1.go = "mirabelle_17";
		break;
		
		case "mirabelle_17":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1.location = "IslaMona_TwoFloorRoom";
			pchar.quest.mtraxx_islamona_mirabella1.function = "Mtraxx_PasqualeMirabellaRoom";
		break;
		
		case "mirabelle_18":
            dialog.text = "";
			link.l1 = "Вот. Я показал тебе весь дом. Ничуть не хуже, чем тот, в котором ты жила у Тиракса. Тебя всё устраивает, надеюсь?";
			link.l1.go = "mirabelle_19";
		break;
		
		case "mirabelle_19":
            dialog.text = "Да, сеньор. У вас отличный дом. Обещаю хорошо смотреть за ним в ваше отсутствие.";
			link.l1 = "Рад, что ты оказалась такой покладистой. Надеюсь, не притворяешься. Если же хитришь - пожалеешь об этом. Будешь хорошей девочкой и не станешь меня огорчать - буду с тобой ласков, обещаю. Чарли Принц слов на ветер не бросает!";
			link.l1.go = "mirabelle_20";
		break;
		
		case "mirabelle_20":
            dialog.text = "Спасибо, сеньор "+pchar.name+". Спасибо, что не позволили вашему... товарищу убить меня. Вы так добры ко мне...";
			link.l1 = "Хех, а ты забавная, крошка... И мордашка у тебя ничего такая, хоть с клеймом на лбу. Надеюсь, всё остальное тоже на месте... Ну, теперь покажи своему капитану, что ты умеешь. Расслабимся с тобой на пару часов после морской качки.";
			link.l1.go = "mirabelle_21";
		break;
		
		case "mirabelle_21":
            DialogExit();
			pchar.GenQuest.FrameLockEsc = true;
			bDisableCharacterMenu = true;
			ResetSound();
			WaitDate("", 0, 0, 0, 2, 30);
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex10.wav");
			LaunchFrameForm();
			AddCharacterHealth(pchar, 5);
			LAi_SetCurHPMax(pchar);
			DoQuestFunctionDelay("Mtraxx_PasqualeMirabellaSex", 12.0);
			ChangeCharacterAddressGroup(pchar, "IslaMona_TwoFloorRoom", "goto", "goto2");
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
		break;
		
		case "mirabelle_22":
            dialog.text = "Сеньор "+pchar.name+", вы такой милый... Вы настоящий благородный джентльмен. Наверное, недавно приехали из Европы...";
			link.l1 = "Не льсти мне, маленькая лгунья, я на такое не куплюсь. Хех, но ты и впрямь хороша, Мирабель! Тиракс знал, кого выбирать, хе-хе...";
			link.l1.go = "mirabelle_23";
		break;
		
		case "mirabelle_23":
            dialog.text = "Это не лесть. Вы на самом деле джентльмен. Только зачем-то притворяетесь грубым. М-м-м... Вы мне так понравились. Я буду ждать, когда вы приедете сюда снова.";
			link.l1 = "Ага, джентльмен... джентльмен удачи, ха-ха! Всё, малышка, пока, обживайся здесь.";
			link.l1.go = "mirabelle_24";
		break;
		
		case "mirabelle_24":
            dialog.text = "До свидания, сеньор.";
			link.l1 = "...";
			link.l1.go = "mirabelle_25";
		break;
		
		case "mirabelle_25":
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_26":
            dialog.text = TimeGreeting()+", сеньор "+pchar.name+"! Очень рада вас видеть. Как ваши дела?";
			link.l1 = RandSwear()+""+LinkRandPhrase("Ветер качает повешенных и разносит звон цепей, ха-ха!","Пятнадцать человек на сундук мертвеца! Йо-хо-хо, и бутылка рома!","Все семьдесят пять не вернулись домой - они потонули в пучине морской!")+" У Чарли Принца всё отлично, крошка.";
			link.l1.go = "mirabelle_26x";
			if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
			{
				link.l2 = "Малышка, как насчёт того, чтобы побаловать своего капитана?";
				link.l2.go = "mirabelle_sex";
			}
		break;
		
		case "mirabelle_26x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
		break;
		
		case "mirabelle_sex":
            dialog.text = "Для вас - всё что угодно, сеньор!";
			link.l1 = RandPhraseSimple("Кошки к борту!","На абордаж!");
			link.l1.go = "mirabelle_sex_1";
		break;
		
		case "mirabelle_sex_1":
            DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_27";
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestFunctionDelay("Mtraxx_MirabellaSex", 1.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "Mtraxx_MirabellaSex");
		break;
		
		case "mirabelle_27":
            dialog.text = "М-м-м... Сеньор, вы просто маг и волшебник! Надеюсь, вы тоже остались довольны? Я старалась.";
			link.l1 = "Ты была на высоте, крошка...";
			link.l1.go = "mirabelle_28";
		break;
		
		case "mirabelle_28":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_sleep":
            dialog.text = "Это неправда, неправда! Сеньор "+pchar.name+" хороший и добрый! Он просто притворяется злым пиратом! Ведь так, сеньор "+pchar.name+"?";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6_1");
		break;
		
		case "mirabelle_29":
            dialog.text = TimeGreeting()+", сеньор "+pchar.name+"! Очень рада вас видеть. Как ваши дела? Почему вы такой грустный?";
			link.l1 = "Привет, Мирабель. Почему ты решила, что грустный?";
			link.l1.go = "mirabelle_30";
		break;
		
		case "mirabelle_30":
            dialog.text = "Ну я же вижу. Вы не такой, как обычно. Хотите, я вас развеселю? Я скучала по вам. Пойдёмте!";
			link.l1 = "Погоди. Я хочу с тобой поговорить.";
			link.l1.go = "mirabelle_31";
		break;
		
		case "mirabelle_31":
            dialog.text = "Хорошо, сеньор, как скажете. Я вас слушаю.";
			link.l1 = "Расскажи, как ты попала к Тираксу. И почему у тебя на лбу клеймо вора. Не бойся, говори всё, как есть, я ничего плохого тебе не сделаю. Мне просто нужно знать твою историю.";
			link.l1.go = "mirabelle_32";
		break;
		
		case "mirabelle_32":
            dialog.text = "Ах, сеньор! Моя история короткая и неинтересная. Родилась я на Пуэрто-Рико, мой отец был белый джентльмен, а мать - индианка. Отца своего я никогда не видела. С детства работала в качестве прислуги, а когда стала взрослой девушкой - совершила глупость: украла у хозяев из шкатулки пару драгоценностей - у меня никогда не было своих украшений, а мне так хотелось. Конечно, кражу обнаружили, и выяснили, кто это сделал\nПотом был недолгий суд, меня высекли кнутом, отправили в форт Сан-Хуан, где выжгли это клеймо на лбу, и бросили в камеру. Там я пробыла недолго: один офицер договорился с начальником стражи, ночью мне одели мешок на голову и доставили на корабль, затем отвезли в Филипсбург на Синт-Маартен и продали в бордель мадам Йоханне за кошель золотых дублонов\nТам я жила, наверное, год, или больше. А потом, в один несчастный день, явились Тиракс и его мерзкий дружок, купец в очках.";
			link.l1 = "Паскуале Вуазье...";
			link.l1.go = "mirabelle_33";
		break;
		
		case "mirabelle_33":
            dialog.text = "Да-да, его звали сеньор Паскуале. Уж не знаю, чем я ему так приглянулась, но после их посещения Тиракс выкупил меня у мадам Йоханны, отвёз в Ла Вегу и запер меня в доме среди сундуков и свертков с товарами. Это были самые худшие дни в моей жизни, страшнее было только в тюрьме. Тиракс приходил ко мне почти каждый день, если не отправлялся в море, но это всё ничего, а самое ужасное происходило, когда к нему в гости приезжал сеньор Паскуале. Сеньор "+pchar.name+", можно я не буду про это рассказывать?\nСколько я там была - не знаю, у меня все дни в голове тогда перепутались. А потом однажды ночью пришли вы, сеньор, и забрали меня оттуда. Мне очень повезло, что вы оказались таким добрым.";
			link.l1 = "Добрым? Мирабель, я ведь сделал то же самое: отвёз тебя на остров и запер в доме...";
			link.l1.go = "mirabelle_34";
		break;
		
		case "mirabelle_34":
            dialog.text = "Нет, сеньор, это не так. Разве я заперта? Я хожу гулять каждый день. На вашем острове очень красиво и спокойно. А работы по дому разве много? Я привыкла делать такую. И вы, сеньор, не Тиракс, и не его дружок-купец. Я всегда рада вас видеть, вы такой молодой и красивый. И джентльмен...";
			link.l1 = "Мирабель, хочешь, я отвезу тебя в любой город? Денег дам на первое время. Куда тебя доставить? Выбирай любую колонию.";
			link.l1.go = "mirabelle_35";
		break;
		
		case "mirabelle_35":
            dialog.text = "Сеньор, вы хотите меня прогнать? Прошу вас, не надо!";
			link.l1 = "Гхм... Я думал, ты хочешь вернуться к обычной жизни...";
			link.l1.go = "mirabelle_36";
		break;
		
		case "mirabelle_36":
            dialog.text = "Ах, сеньор "+pchar.name+", а что меня там ждёт? Разве ж кто-то возьмёт замуж полукровку с клеймом на лбу? Только бандит какой-нибудь, вроде Тиракса, или того хуже. А то и вовсе - снова в бордель продадут. Не гоните меня. Я не хочу уезжать отсюда, мне нигде и никогда не было так хорошо и уютно, как здесь! Родгар и его парни - хорошие ребята, дружат со мной и не обижают. Мне весело с ними. По вечерам мы, бывает, разжигаем костер на пляже, и я танцую самбу. Прошу вас, сеньор, я буду все делать, что скажете, только позвольте мне остаться у вас!";
			link.l1 = "Хорошо, Мирабель, раз тебе так нравится здесь - оставайся. Просто знай, что ты не пленница, и всегда можешь попросить меня отвезти тебя отсюда.";
			link.l1.go = "mirabelle_37";
		break;
		
		case "mirabelle_37":
            dialog.text = "Дорогой милый сеньор, спасибо! Я никогда не стану просить вас об этом - я хочу остаться пленницей этого острова и вашей пленницей, хи-хи... Вы такой добрый и такой грустный сегодня! Не поёте песен, не ругаетесь, как обычно.";
			link.l1 = "Больше не будет ни песен, ни ругательств, Мирабель. Прости, что был груб с тобой раньше.";
			link.l1.go = "mirabelle_38";
		break;
		
		case "mirabelle_38":
            dialog.text = "Вы теперь будете всегда суровый и строгий, как английский лорд?.. Ах, сеньор, хотите, я для вас станцую самбу сегодня вечером у костра, и спою? Только для вас. А сейчас пойдёмте же со мной! От тоски нет лучше средства, чем любовь и ласка. Я соскучилась по вам.";
			link.l1 = "Ну хорошо, хорошо, девочка... Пойдём.";
			link.l1.go = "mirabelle_39";
		break;
		
		case "mirabelle_39":
            DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestFunctionDelay("Mtraxx_MirabellaSex", 1.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "Mtraxx_MirabellaSex");
		break;
		
		case "mirabelle_40":
            dialog.text = "Ах, сеньор "+pchar.name+", вы такой нежный сегодня. Вы такой милый, м-м-м... Вы остались довольны, мой дорогой капитан?";
			link.l1 = "Всё было просто замечательно, Мирабель.";
			link.l1.go = "mirabelle_41";
		break;
		
		case "mirabelle_41":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_42":
			bool bMary = GetCharacterIndex("Mary") != -1 && CheckAttribute(pchar, "questTemp.LSC.Mary_officer");
			bool bHelena = GetCharacterIndex("Helena") != -1 && CheckAttribute(pchar, "questTemp.Saga.Helena_officer");
            dialog.text = TimeGreeting()+", сеньор "+pchar.name+"! Как хорошо, что вы приехали! Очень рада вас видеть! Как ваши дела?";
			link.l1 = ""+LinkRandPhrase("И я рад тебя видеть, девочка.","Привет, Мирабель. Ты, как всегда - весела и красива, приятно посмотреть.","Здравствуй, красавица. Отлично выглядишь!")+" У меня всё идёт отлично. Надеюсь, что у тебя тоже всё хорошо.";
			link.l1.go = "mirabelle_42x";
			if (!bMary && !bHelena) // прогона 3
			{
			if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
			{
				link.l2 = "Мирабель, я уже успел соскучиться по тебе и твоим ласкам. Поцелуешь старого морского волка?";
				link.l2.go = "mirabelle_43";
			}
			}
		break;
		
		case "mirabelle_42x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		case "mirabelle_43":
            dialog.text = "Ах, мой милый капитан, я тоже скучала по вам и по вашим крепким объятиям! Пойдёмте же, я уже вся в нетерпении!";
			link.l1 = "...";
			link.l1.go = "mirabelle_39";
		break;
		
		// губернатор Картахены
		case "CartahenaMayor":
            dialog.text = "Проклятые ладроны! Ничего, наш гонец уже спешит к Порто-Белло. Скоро сюда прибудет наша эскадра, и...";
			link.l1 = TimeGreeting()+", ваша светлость. Рад видеть вас в добром здравии. Надеюсь, что ваш вид останется таким же цветущим и после того, как мы отбудем отсюда. На эскадру я бы на вашем месте не рассчитывал - более, чем на три дня, здесь мы не задержимся, а этого срока, как вы понимаете, недостаточно для того, чтобы благородные доны пришли Картахене на помощь. Так что давайте перейдём к делам.";
			link.l1.go = "CartahenaMayor_1";
		break;
		
		case "CartahenaMayor_1":
            dialog.text = "Вы уже перешли к делам! Посмотрите в окно, что творят на улицах и в домах ваши головорезы!";
			link.l1 = "Ох, ваша светлость, это ещё пустяки по сравнению с тем, что начнётся, если вы окажетесь несговорчивы. Надеюсь, вы понимаете, с кем имеете дело...";
			link.l1.go = "CartahenaMayor_2";
		break;
		
		case "CartahenaMayor_2":
            dialog.text = "Я знаю, на что способен отъявленный злодей и пират Чарли Принц! И знаю, кто им руководит! Придёт время - мы выжжем калёным железом ваше разбойничье гнездо на Эспаньоле! Выкуп? Сколько?";
			link.l1 = "О, не тратьте зря порох, дорогой губернатор! А лучше подготовьте двести пятьдесят тысяч песо.";
			link.l1.go = "CartahenaMayor_3";
		break;
		
		case "CartahenaMayor_3":
            dialog.text = "Двести пятьдесят тысяч?! Ваша наглость не имеет предела! Это грабёж!!";
			link.l1 = "Конечно, это грабёж. А что же ещё? Собирайте ваших купцов, ростовщиков и прочих обладателей толстой мошны, и ссыпайте ваши песо и дублоны в большой сундук. Иначе... мне придётся прибегнуть к мерам, которые будут вам не по вкусу.";
			link.l1.go = "CartahenaMayor_4";
		break;
		
		case "CartahenaMayor_4":
            dialog.text = "Проклятый пират! Мерзавец! Богоотступник!";
			link.l1 = "За ваши оскорбительные высказывания я увеличиваю выкуп до трехсот тысяч песо.";
			link.l1.go = "CartahenaMayor_5";
		break;
		
		case "CartahenaMayor_5":
            dialog.text = "Гореть тебе в аду, гнусный ладрон!..";
			link.l1 = "Триста пятьдесят тысяч песо. Желаете продолжить, или всё-таки прикусите язык?";
			link.l1.go = "CartahenaMayor_6";
		break;
		
		case "CartahenaMayor_6":
            dialog.text = "В городе нет таких денег!";
			link.l1 = "Вы лжёте. Этого просто не может быть. У вас запросто наберётся и миллион, но боюсь, на его сбор уйдёт слишком много времени, поэтому я буду добр и ограничусь названной суммой в триста пятьдесят тысяч песо.";
			link.l1.go = "CartahenaMayor_7";
		break;
		
		case "CartahenaMayor_7":
            dialog.text = "Ещё раз говорю тебе, Чарли Принц: нет в Картехене таких денег!";
			link.l1 = "Ох... Это начинает утомлять. Тесак! Обыщи жилые покои нашего несговорчивого губернатора и притащи сюда всех, кого найдёшь. Ищи хорошенько!.. А мы с вами пока подождём, ваша светлость...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaInResidence");
		break;
		
		case "CartahenaMayor_8":
            dialog.text = "";
			link.l1 = "Эй, сеньор Упрямец! Вы ещё не поменяли своего мнения насчёт наличия денежных средств в Картахене? О, что-то вы побледнели! Вам плохо? Нюхательной соли?";
			link.l1.go = "CartahenaMayor_9";
		break;
		
		case "CartahenaMayor_9":
            dialog.text = "";
			link.l1 = "Как я понимаю, эти две дамы - ваши супруга и дочь, дорогой губернатор? Третья девушка, судя по всему, горничная или служанка, вам на неё наверняка наплевать, поэтому мы её не тронем... а вот этими двумя нарядными красавицами вполне может заняться мой боевой товарищ Тесак. Они ему приглянулись, сеньор. Ну что? Идём собирать деньги, или как?";
			link.l1.go = "CartahenaMayor_10";
		break;
		
		case "CartahenaMayor_10":
            dialog.text = "Мне... мне потребуется время...";
			link.l1 = "Ага! Вот как мы заговорили?! И кто тут у нас мерзавец и негодяй, а? То, что мои молодчики бесчинствуют в городе среди простолюдинов - тебя не сподвигло на подвиги, а как дело дошло до твоих дамочек - засуетился? Торговаться со мной вздумал, canallа? Я покажу тебе, как перечить Чарли Принцу!";
			link.l1.go = "CartahenaMayor_10x";
		break;
		
		case "CartahenaMayor_10x":
            dialog.text = "";
			link.l1 = "Марш собирать выкуп - триста пятьдесят тысяч, и чтобы ни песо меньше. Даю тебе сутки. А мы пока расположимся здесь, разопьём бутылочку-другую вина в компании этих милых женщин... И поторопись, malditо, а то мы с Тесаком ненароком влюбимся в твоих красоток, и тогда тебе придётся выкупать ещё и их. Вперёд!!";
			link.l1.go = "CartahenaMayor_11";
		break;
		
		case "CartahenaMayor_11":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaResidenceWait", 5.0);
		break;
		
		case "CartahenaMayor_12":
			AddMoneyToCharacter(pchar, 350000);
            dialog.text = "Получи свои кровавые деньги, Чарли Принц, и отзови негодяев из города на корабли. Пусть они наконец прекратят грабежи и насилие...";
			link.l1 = "Вы собрали выкуп? Просто замечательно! Но вы опоздали на целый час, дорогой губернатор. И за этот час мы с Тесаком поняли, что нам будет очень скучно без этих красоток, которые были так добры к нам и любезно поддерживали светскую беседу...";
			link.l1.go = "CartahenaMayor_13";
		break;
		
		case "CartahenaMayor_13":
            dialog.text = "Ты... ты!..";
			link.l1 = "Ах, какой же вы нервный, ваша светлость. Уже и пошутить нельзя... Тесак! За мной!..";
			link.l1.go = "CartahenaMayor_14";
		break;
		
		case "CartahenaMayor_14":
            DialogExit();
			AddQuestRecord("Roger_9", "7");
			AddDialogExitQuestFunction("Mtraxx_CartahenaToFort");
		break;
		
		// Камилла
		case "camilla":
			PlaySound("VOICE\Russian\hambit\Girls_3.wav");
            dialog.text = "Ох, да это же сам Чарли Принц, знаменитый пират, гроза испанского южного Мэйна!";
			link.l1 = RandSwear()+"Хех, даже не думал, что я столь популярен на Тортуге. Как твоё имя, малышка?";
			link.l1.go = "camilla_1";
		break;
		
		case "camilla_1":
            dialog.text = "Меня зовут Камилла.";
			link.l1 = "Камилла... Знавал я одну Камиллу, ещё во Франции. Как давно это было!..";
			link.l1.go = "camilla_2";
		break;
		
		case "camilla_2":
			PlaySound("ambient\tavern\orijka_003.wav");
            dialog.text = "";
			link.l1 = "... буэ!.. Извини, красотка, Принц сегодня малость выпил. Так это... ты просто так подошла ко мне, или у тебя какое-то дело?";
			link.l1.go = "camilla_3";
		break;
		
		case "camilla_3":
            dialog.text = "Может, просто так, а может, и не просто. Может, и дело, а может, и нет...";
			link.l1 = "У меня сейчас голова треснет. Какая-то ты загадочная, деваха...";
			link.l1.go = "camilla_4";
		break;
		
		case "camilla_4":
            dialog.text = "В каждой девушке должна быть загадка.";
			link.l1 = "Кажется, ты хочешь, чтобы я эту загадку разгадал. Нет? Я мастер разгадывать девичьи загадки, клянусь громом! Может, пойдём в таверну, присядем, выпьем вина - я угощу тебя самым лучшим канарским!";
			link.l1.go = "camilla_5";
		break;
		
		case "camilla_5":
            dialog.text = "М-м-м... Мне нравятся крутые парни. Только пить вино внизу, среди пьяного сброда, я не стану. Сними комнату, там и выпьем, и поговорим.";
			link.l1 = RandSwear()+"Жгучая красотка! Следуй за мной!";
			link.l1.go = "camilla_6";
		break;
		
		case "camilla_6":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.location = "Tortuga_town";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator = "reload4_back";
			pchar.quest.mtraxx_retribution_tavern.function = "Mtraxx_RetributionToTavern";
		break;
		
		case "camilla_7":
			PlaySound("VOICE\Russian\hambit\Gr_officiant_1.wav");
            dialog.text = "Ну... Наливай, обхаживай даму!";
			link.l1 = "Конечно, милашечка!..";
			link.l1.go = "camilla_8";
		break;
		
		case "camilla_8":
			LAi_Fade("", "");
			PlaySound("ambient\tavern\krujki_005.wav");
			PlaySound("ambient\tavern\naliv_003.wav");
			PlaySound("ambient\tavern\glotok_001.wav");
			WaitDate("", 0, 0, 0, 1, 5);
            dialog.text = "М-м-м... Подумать только - я сижу наедине с самим Чарли Принцем, пью чудесное вино...";
			link.l1 = "Ты останешься довольна нашей встречей, обещаю! Чарли Принц щедр и ласков с дамами, которые ему не перечат. Ты ведь не будешь мне перечить, так?";
			link.l1.go = "camilla_9";
		break;
		
		case "camilla_9":
            dialog.text = "Хи-хи-хи... Ни в коем случае, дорогой. А твои обещания звучат заманчиво...";
			link.l1 = "Тогда не будем терять времени, красотка?..";
			link.l1.go = "camilla_10";
		break;
		
		case "camilla_10":
            dialog.text = "Просто обожаю настоящих мужчин!..";
			link.l1 = "...";
			link.l1.go = "camilla_11";
		break;
		
		case "camilla_11":
            DialogExit();
			pchar.GenQuest.FrameLockEsc = true;
			bDisableCharacterMenu = true;
			ResetSound();
			WaitDate("", 0, 0, 0, 2, 30);
			SetLaunchFrameFormParam("", "", 0, 5.1);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex2.wav");
			LaunchFrameForm();
			AddCharacterHealth(pchar, 3);
			LAi_SetCurHPMax(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionRoomSex", 5.1);
		break;
		
		case "camilla_12":
            dialog.text = "М-м-м...";
			link.l1 = "Ты осталась довольна, моя прелесть?";
			link.l1.go = "camilla_13";
		break;
		
		case "camilla_13":
            dialog.text = "Ещё бы!.. Тебе, надеюсь, тоже понравилось.";
			link.l1 = "Хех! У меня даже весь хмель из головы выветрился!";
			link.l1.go = "camilla_14";
		break;
		
		case "camilla_14":
            dialog.text = "Принц, у меня к тебе будет просьба. Выполнишь?";
			link.l1 = "Да хоть луну с неба, ха-ха! Выкладывай, что там у тебя?";
			link.l1.go = "camilla_15";
		break;
		
		case "camilla_15":
            dialog.text = "Мне нужно в Ла Вегу, к Тираксу. Сама я его побаиваюсь, а ты работаешь с ним. Свози меня к нему.";
			link.l1 = "О как! И зачем хранитель кодекса понадобился такой милой и хрупкой девице?";
			link.l1.go = "camilla_16";
		break;
		
		case "camilla_16":
            dialog.text = "Милая и хрупкая девица желает заработать денег. После смерти отца и братьев у неё осталось слишком мало средств. А Тиракс может ей помочь в этом.";
			link.l1 = "Да ну?! Интересно - как? Даст наводку на испанского торговца? Ха-ха!";
			link.l1.go = "camilla_17";
		break;
		
		case "camilla_17":
            dialog.text = "Грабить караваны и города - это по части крутых парней вроде тебя, милый, а у меня всё проще. Маркус собирает и скупает информацию. Информацию, используя которую, он зарабатывает деньги. У меня есть кое-что... Сама я никогда этого сделать не смогу, а вот Тиракс - сможет. А я получу с этого свой небольшой процент и буду довольна.";
			link.l1 = "Очень интересно! Расскажи мне - хоть о чём пойдёт речь.";
			link.l1.go = "camilla_18";
		break;
		
		case "camilla_18":
            dialog.text = "Гм...";
			link.l1 = "Да не переживай ты. Я, считай, правая рука Тиракса, и распутал не одно такое дельце по куцей информации, полученной Маркусом от кого-то со стороны. Если дело стоящее, тебе не понадобится никуда ездить - я сам куплю у тебя сведения. Ну?";
			link.l1.go = "camilla_19";
		break;
		
		case "camilla_19":
            dialog.text = "Ладно. Я расскажу тебе, но только в общих чертах! А конкретику ты получишь тогда, когда я получу деньги. Согласен, милый?";
			link.l1 = "Конечно, красотка. Чарли Принц не обманывает своих партнеров, ха-ха! Валяй, я слушаю.";
			link.l1.go = "camilla_20";
		break;
		
		case "camilla_20":
            dialog.text = "Мой отец был шкипером торговой шхуны. Однажды он каким-то образом узнал, что в джунглях Мэйна есть старый испанский посёлок шахтеров-золотодобытчиков. Это поселение было разрушено двадцать лет назад сильным землетрясением и ураганом, и было заброшено вместе со всем золотом, а тропы, ведущие к нему - завалены буреломом. Однако к руинам всё-таки остался один проход через сельву. Отец отправился туда\nВместе с двумя моими братьями и проводником он прошёл через джунгли и отыскал развалины посёлка, а в них - золото, добытое и переплавленное рудокопами двадцать лет назад. Много золота. Отец вернулся на берег к своей шхуне, чтобы собрать отряд и вынести сокровища, однако, к своему ужасу, корабля не обнаружил - видимо, старший помощник, воспользовавшись отсутствием капитана, подговорил команду и украл судно. Отец и братья остались на диком пустынном берегу\nОни смастерили лодку и поплыли вдоль берега, пытаясь достичь населённых мест, но... налетел шквал и лодка перевернулась. Мои братья погибли (всхлипывает), а отца выбросило на берег, где его нашли и спасли рыбаки. Он сумел вернуться домой, но прожил недолго - смерть сыновей подкосила его, да и пережитые лишения подорвали здоровье. Отец составил карту, как пройти к этому старому городу и отдал её мне\nСказал: мол, выйдешь замуж - пусть твой супруг отправится туда, и будете жить безбедно. Там золота, наверное, на миллион песо... Знать-то я знаю, да руки коротки: мне туда никогда не добраться, а после смерти родных жить как-то нужно. Да и мужу своему, если суждено такого найти, я никогда не позволю пойти в этот проклятый город - чтобы вдовой остаться. Нет! Такие дела под силу только очень сильным мужчинам с большими возможностями. Поэтому я и собираюсь к Тираксу.";
			link.l1 = "Сколько ты хочешь за эту карту?";
			link.l1.go = "camilla_21";
		break;
		
		case "camilla_21":
            dialog.text = "Две сотни дублонов. При учёте того, сколько там золота - это совсем небольшая цена. Тиракс согласится, я уверена. У него денег куры не клюют.";
			link.l1 = "Хех! А если всё это выдумка?";
			link.l1.go = "camilla_22";
		break;
		
		case "camilla_22":
            dialog.text = "Я похожа на самоубийцу? Пытаться надуть Тиракса? Дорогой, лучше жить в нищете, чем не жить вовсе. Так ты отвезёшь меня? Ну пожалуйста...";
			link.l1 = "Где эта карта? Покажешь её?";
			link.l1.go = "camilla_23";
		break;
		
		case "camilla_23":
            dialog.text = "Карта хранится у моего духовника в церкви, а покажу я её только в обмен на двести дублонов.";
			link.l1 = "Хорошо! Я куплю у тебя эту карту - проходимцы в тавернах и большие суммы заламывают за кота в мешке.";
			link.l1.go = "camilla_24";
		break;
		
		case "camilla_24":
            dialog.text = "Ты купишь её? Правда, милый? Как я рада, что не надо ехать в Ла Вегу! Честно - я боюсь Маркуса. Тебя, кстати, тоже, но немножко меньше.";
			link.l1 = "Такой сладкой малышке меня бояться нечего. Куда тебе принести дублоны?";
			link.l1.go = "camilla_25";
		break;
		
		case "camilla_25":
            dialog.text = "Давай договоримся: ты сможешь найти меня в любой день с десяти утра до часу дня в нашей церкви. Под сенью святого храма я буду чувствовать себя спокойнее. Там и совершим сделку.";
			link.l1 = "Ты всё равно опасаешься? Ха-ха! Да не трусь, Камилла: не обману я тебя. Ради каких-то жалких двухсот дублонов Чарли Принц не станет унижаться до такого.";
			link.l1.go = "camilla_26";
		break;
		
		case "camilla_26":
            dialog.text = "Вот и славно. Всё, жду тебя, милый, и спасибо за прекрасно проведённое время! Как хорошо, что я тебя встретила!";
			link.l1 = "Скоро увидимся, малышка.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionOutRoom");
		break;
		
		case "camilla_27":
			PlaySound("VOICE\Russian\hambit\Girls_3.wav");
            dialog.text = "Ну? Ты принёс деньги, дорогой?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 200)
			{
				link.l1 = "Да. Держи своё золото и давай мне карту.";
				link.l1.go = "camilla_28";
			}
			else
			{
				link.l1 = "Я как раз иду на корабль за ними.";
				link.l1.go = "camilla_27x";
			}
		break;
		
		case "camilla_27x":
            DialogExit();
			npchar.dialog.currentnode = "camilla_27";
		break;
		
		case "camilla_28":
			RemoveItems(pchar, "gold_dublon", 200);
			Log_Info("Вы отдали 200 дублонов");
			GiveItem2Character(pchar, "mapEnrico"); 
            dialog.text = "Спасибо, милый... Вот, бери. Клянусь памятью моего отца - карта верная.";
			link.l1 = "Хорошо, малышка. Как насчёт того, чтобы пойти и обмыть нашу выгодную сделку? Как в прошлый раз...";
			link.l1.go = "camilla_29";
		break;
		
		case "camilla_29":
            dialog.text = "Я бы с радостью, Принц, но сейчас я готовлюсь к исповеди у своего духовника, и мне положено полное воздержание от всех соблазнов. Давай в следующий раз.";
			link.l1 = "Ух, ты раззадориваешь меня, красотка. Ладно! Мне тоже некогда терять время: пора в море. Если сокровища по карте твоего папочки оправдают мои надежды, клянусь, я удвою сумму твоих 'процентов'.";
			link.l1.go = "camilla_30";
		break;
		
		case "camilla_30":
            dialog.text = "Ты так щедр, дорогой. Счастливого плавания!";
			link.l1 = "Йо-хо-хо!";
			link.l1.go = "camilla_31";
		break;
		
		case "camilla_31":
            DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_10", "2");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1.location = "shore10";
			pchar.quest.mtraxx_retribution_carataska.function = "Mtraxx_RetributionCarataska";
			pchar.questTemp.Mtraxx.Retribution = "carataska";
		break;
		
		case "camilla_sleep":
            dialog.text = "Твои мерзавцы убили моего отца и братьев. После твоего налета в Картахене не осталось, наверное, ни одной семьи, в которую не пришло бы горе\nНадеюсь, тебе сейчас в тёмном каменном мешке так же страшно, как было страшно жителям Картахены, когда твои нелюди резвились на улицах и в домах. Ты будешь гореть в аду, Чарли Принц.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep4");
		break;
		
		// дон Энрико - народный мститель
		case "enrico":
			PlaySound("VOICE\Russian\OliverTrast01.wav");
            dialog.text = "Мало что доставляет мне большее удовольствие, нежели наблюдать за тем, как пожирают друг друга пауки в банке!\nВыживает самый сильный и отвратительный. А затем остаётся лишь раздавить его...";
			link.l1 = "Аргх!.. Ты кто такой?!";
			link.l1.go = "enrico_1";
		break;
		
		case "enrico_1":
            dialog.text = "Я - дон Энрико. Английские негодяи зовут меня Фокс, голландские - Вос, французские - Ренар. Но я предпочитаю своё прозвище на родном испанском - Зорро. Я караю гнусных мерзавцев, причиняющих горе и страдания простым людям, тем, за которых больше некому заступиться\nСегодня свершился суд над мерзкими пиратами Маркуса Тиракса: Лысым Джеффри, Тесаком Пелли, Люком Лепреконом и Чарли Принцем, учинившим жестокую бойню в испанских городах Картахена и Мерида. Последний, пятый негодяй - Жан Красавчик, оказался прозорливее других и не явился...";
			link.l1 = "Что?!!";
			link.l1.go = "enrico_2";
		break;
		
		case "enrico_2":
            dialog.text = "Ты не дурак, Чарли Принц, хоть и законченный мерзавец. Я думаю, ты уже всё понял. При помощи мною составленных карт, дневников и писем, соблазнив сокровищами испанских золотодобытчиков, я заманил вас сюда, в эти подземелья, где вы, обуреваемые отвратительными качествами ваших кровожадных натур - алчностью, завистью, подлостью и беспринципностью - уничтожили один другого. Воистину - справедливое возмездие!";
			link.l1 = "Камилла... я должен был понять, что с этой девкой что-то не чисто!";
			link.l1.go = "enrico_3";
		break;
		
		case "enrico_3":
            dialog.text = "Девушка по имени Камилла жила спокойной жизнью в Картахене с отцом и братьями, готовилась выйти замуж, пока не явился ты, Чарли Принц, вместе с ордой своих головорезов. Твои пираты убили всех близких этой несчастной, и она поклялась сделать всё возможное, лишь бы виновника постигла самая суровая кара. Ей досталась трудная роль. Чтобы сыграть достоверно, Камилла пошла даже на то, чтобы разделить постель с негодяем, виновным в гибели её семьи. Я боюсь и представить себе, что она чувствовала при этом\nБедняжка потом несколько дней провела в церкви, молясь о прощении. Твои кровавые двести дублонов Камилла раздала в Картахене людям, наиболее пострадавшим от твоего набега. Теперь она ушла в монастырь... ты сломал ей жизнь, изверг! Вдумайся в это! Вдумайся в то, сколько десятков таких камилл, росит, изабелл ты оставил вдовами, скольких обесчестил. Сколько хуанов, педро, карлосов твои мерзавцы убили или искалечили\nВспомни ограбленную тобой Мериду! Вспомни, как ты обещал городскому главе просто уйти, а сам подло поджёг город!";
			link.l1 = "Я не хотел делать этого! Когда я вышел из резиденции, дома уже пылали. Я не отдавал приказа...";
			link.l1.go = "enrico_4";
		break;
		
		case "enrico_4":
            dialog.text = "Ты несёшь ответственность за все действия твоих пиратов. За все их убийства и насилия. Мертвецы висят на твоей шее, как мельничные жернова, и они утянут тебя в ад!";
			link.l1 = "Выходи из-за этой решётки! Ну? Сразись со мной! Ты же к этому ведёшь?";
			link.l1.go = "enrico_5";
		break;
		
		case "enrico_5":
            dialog.text = "Нет, Чарли Принц. Да не дергай ты своё оружие - это бесполезно... Я легко мог бы убить тебя, но быстрая смерть - слишком мягкое наказание для такого отпетого негодяя. Ты останешься здесь, в этих подземельях и шахтах, навсегда. Дверь, через которую ты сюда вошёл, заперта и надежно придавлена снаружи камнями. Вторая дверь, через которую уйду я, тоже будет заперта, а кроме того, она находится за крепкой стальной решёткой. И больше выходов отсюда нет\nВнизу есть вода, так что протянешь ты долго, пока голод не убьёт тебя. У тебя будет много времени подумать над своими поступками. Обреченный, один, в тишине и мраке подземелий, быть может, ты раскаешься в том зле, которое причинил людям, перед тем как умрёшь или сойдёшь с ума\nНу и напоследок сообщу тебе, что сокровище внизу - не настоящее. Это бутафория. Слитки - позолоченный свинец, а дублоны лежат россыпью поверх сундуков, заполненных камнями. Вы перегрызли друг другу глотки за пустышку, Принц. Достойная кончина для пиратов! А теперь - прощай. Молись, Чарли Принц, за свою грешную душу, если ещё не забыл, как это делать...";
			link.l1 = "Стой!..";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		
		case "mishelle_sleep":
            dialog.text = "Расскажи мне, брат - как ты превратился в такого негодяя? Когда я говорил тебе познакомиться с пиратами, я не имел в виду жечь города, убивать мирных поселенцев, издеваться над женщинами. Даже войну можно вести достойно и благородно\nТы позор нашей семьи. Хорошо, что отец не видит тебя: он умер бы со стыда, узнав, что его сын стал пиратом и бандитом!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep5");
		break;
		
		case "mishelle_sleep_1":
            dialog.text = "Брат! Брат!\nТы слышишь меня, брат?\nЗа одной из двух дверей есть проход. Дверь можно открыть. Ключ лежит совсем близко от тебя\nИщи его на ступеньках. На ступеньках!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep7");
		break;
		
		case "terrax_sleep":
            dialog.text = "Ха-ха-ха, привет, бравый головорез! Ты чего такой грустный? Море, золото, ром, девочки - чего тебе не хватает? Помнишь, что я сказал тебе в нашу первую встречу? Что мне нужны люди, не боящиеся нюхать порох и пускать ручейки красного цвета. Ты оправдал все мои надежды! Ты стал настоящим пиратом, Чарли Принц! Ха-ха-ха-ха!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_1";
		break;
		
		case "terrax_sleep_1":
            dialog.text = "Настоящим пиратом! Ха-ха-ха-ха!!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_2";
		break;
		
		case "terrax_sleep_2":
			Mtraxx_RetributionSleepSkeletons();
            dialog.text = "Уа-ха-ха-ха-ха-ха!!!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6");
		break;
	}
} 
