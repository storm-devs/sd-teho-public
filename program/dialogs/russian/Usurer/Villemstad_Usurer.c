// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
    case "quests":
        dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "М-да, позвольте угадаю... Опять ничего существенного?",
                                              "Послушайте, я финансами оперирую, а не на вопросы отвечаю...", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я " + GetSexPhrase("передумал", "передумала") + "...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                                           "Вы угадали, простите...", "Я понимаю...", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
        {
            link.l1 = "Минхер, у меня несколько необычное дело. Я знаю, что не так давно французский капер по имени Гай Марше продал вам две уникальные вещицы: золотой остензорий и золотое кадило. Я хочу их выкупить.";
            link.l1.go = "guardoftruth";
        }
        if (CheckAttribute(npchar, "quest.GOT_chest") && CheckCharacterItem(pchar, "chest"))
        {
            link.l1 = "Я принес вам сундучок с дублонами.";
            link.l1.go = "guardoftruth_3";
        }
        break;

    case "guardoftruth":
        dialog.text = "Как же, как же - помню их! Действительно, очень оригинальные, а главное - дорогие предметы. Но вы опоздали, капитан: у меня их нет. Я уже продал их.";
        link.l1 = "Невероятно! И кому же могла понадобится церковная утварь? Минхер, а кому вы их продали? Я хочу попытаться перекупить...";
        link.l1.go = "guardoftruth_1";
        npchar.quest.utensil = "true";
        break;

    case "guardoftruth_1":
        dialog.text = "Интересно, и зачем же мне выдавать вам имена своих клиентов?";
        if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "self_win")
        {
            link.l1 = "Может быть, потому, что я очень хороший друг губернатора Матиаса Бека и могу обратиться за подобной санкцией для вас к нему?";
            link.l1.go = "guardoftruth_2_1";
        }
        else
        {
            if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "holl_win")
            {
                link.l1 = "Может быть, потому что я на отличном счету в Голландской Вест-Индской Компании и оказал большую помощь всем без исключения голландским поселенцам на архипелаге?";
                link.l1.go = "guardoftruth_2_2";
            }
            else
            {
                link.l1 = "Может быть, потому, что я за нее заплачу?";
                link.l1.go = "guardoftruth_2_3";
                npchar.quest.GOT_chest = "true";
            }
        }
        break;

    case "guardoftruth_2_1":
        dialog.text = "Ах, точно - ведь вы же " + GetFullName(pchar) + ", друг самого губернатора, раскрывший преступный заговор Лукаса Роденбурга... Как же я мог упустить это из вида? Конечно, я расскажу вам.";
        link.l1 = "Тогда я внимательно слушаю.";
        link.l1.go = "guardoftruth_4";
        break;

    case "guardoftruth_2_2":
        dialog.text = "Ах, ну да, вы же " + GetFullName(pchar) + ", славный победитель пиратского 'корабля-призрака'. Как же я мог упустить это из вида? Конечно, я расскажу вам.";
        link.l1 = "Тогда я внимательно слушаю.";
        link.l1.go = "guardoftruth_4";
        break;

    case "guardoftruth_2_3":
        dialog.text = "Ну что же, за сундучок, доверху полный золотых дублонов, я, пожалуй, расскажу вам о тех, кто опередил вас с покупкой.";
        if (CheckCharacterItem(pchar, "chest"))
        {
            link.l1 = "Пожалуйста, держите. Уж больно дороги мне вещицы...";
            link.l1.go = "guardoftruth_3";
        }
        else
        {
            link.l1 = "Хорошо, я принесу вам то, что вы просите. Уж больно дороги мне вещицы...";
            link.l1.go = "exit";
        }
        break;

    case "guardoftruth_3":
        RemoveItems(pchar, "chest", 1);
        Log_Info("Вы отдали сундук с дублонами");
        PlaySound("interface\important_item.wav");
        dialog.text = "Прекрасно. В таком случае я готов поделиться с вами информацией.";
        link.l1 = "Я внимательно слушаю.";
        link.l1.go = "guardoftruth_4";
        DeleteAttribute(npchar, "quest.GOT_chest");
        break;

    case "guardoftruth_4":
        dialog.text = "Золотое кадило купил человек по имени Роланд Мозес, более известный как Ролли Колпак. Зачем уже этому мяснику понадобилась церковная вещь - ума не приложу, но он почему-то пришел от нее в неописуемый восторг... Кстати, с самим Ролли вы уже навряд ли встретитесь.";
        link.l1 = "Это еще почему?";
        link.l1.go = "guardoftruth_5";
        break;

    case "guardoftruth_5":
        dialog.text = "Потому что этот любитель щипать одиночных английских торговцев недавно попался на своей шхуне прямо в лапы полковнику Фоксу. Вы знаете кто это? ";
        link.l1 = "Еще бы! Командир 'морских лис' в Сент-Джонсе на Антигуа...";
        link.l1.go = "guardoftruth_6";
        break;

    case "guardoftruth_6":
        dialog.text = "Ну, тогда вы понимаете, почему мы с вами больше никогда не увидим беднягу Роланда. Полковник захватил его шхуну со всем выжившим экипажем и доставил в Сент-Джонс, где уже, вероятно, повязал каждому по пеньковому галстуку.";
        link.l1 = "Ясно. А остензорий?";
        link.l1.go = "guardoftruth_7";
        break;

    case "guardoftruth_7":
        dialog.text = "Остензорий приобрела совсем недавно сеньора Белинда де Риберо из Куманы. Очень знатная сеньора, родственница самого Фернандо де Вильегаса, губернатора Куманы. Как я понимаю - она хотела принести его в дар церкви.";
        link.l1 = "Сеньора Белинда де Риберо? Я смогу найти ее в Кумане, так?";
        link.l1.go = "guardoftruth_8";
        break;

    case "guardoftruth_8":
        dialog.text = "Безусловно. Она сама сказала, что из Виллемстада отправляется домой.";
        link.l1 = "Понятно. Спасибо, " + npchar.name + ", вы мне очень помогли!";
        link.l1.go = "guardoftruth_9";
        break;

    case "guardoftruth_9":
        dialog.text = "Всегда пожалуйста, минхер. Заходите еще!";
        link.l1 = "Богатых вам клиентов, с кошельками потолще и мозгами поскуднее... Ха-ха!";
        link.l1.go = "guardoftruth_10";
        break;

    case "guardoftruth_10":
        DialogExit();
        AddQuestRecord("Guardoftruth", "23");
        pchar.questTemp.Guardoftruth.Usurer = "true";
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}