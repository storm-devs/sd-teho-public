// старпом Акулы - Лейтон Декстер
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    int iTemp;
    string sTemp;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
    case "First time":
        if (npchar.quest.meeting == "0")
        {
            dialog.text = "Чего тебе, парень? По всем вопросам - к Акуле, он здесь заправляет.";
            link.l1 = "Ну а хоть поздороваться-то с тобой можно, или это запрещено правилами?";
            link.l1.go = "meeting";
            npchar.quest.meeting = "1";
        }
        else
        {
            if (CheckAttribute(npchar, "quest.map"))
            {
                link.l2 = "Лейтон, мне Акула сказал, что у тебя есть карта Острова. Не мог бы ты мне её продать?";
                link.l2.go = "map";
            }
            dialog.text = "А-а, " + GetFullName(pchar) + "! По какому делу явился, или опять просто поболтать? Если поболтать, в следующий раз тащи с собой бутылку рома, хе-хе.";
            link.l1 = "Да, никакого конкретного дела нет. А насчёт рома - приму к сведению.";
            link.l1.go = "exit";
        }
        NextDiag.TempNode = "First time";
        break;

    case "meeting":
        dialog.text = "Ха! Ты шутник, как я погляжу. Ладно... Меня зовут Лейтон Декстер, и я старпом Акулы, а нынче - его заместитель на этом треклятом Острове. В свободное от скуки время я занимаюсь продажей продовольствия и выколачиванием денег из этого бездельника Фацио.";
        link.l1 = "Ну а я - " + GetFullName(pchar) + ". Будем знакомы!";
        link.l1.go = "exit";
        NextDiag.TempNode = "First time";
        break;

    // Акула погиб по варианту N
    case "admiral":
        dialog.text = "Думаю, для тебя это не будет новостью. Стивен убит. К этому приложили руку нарвалы.";
        link.l1 = "Ты прав, новостью для меня это никак не может являться... Теперь ты - адмирал?";
        link.l1.go = "admiral_1";
        AddQuestRecord("SharkHunt", "28");
        CloseQuestHeader("SharkHunt");
        break;

    case "admiral_1":
        dialog.text = "Именно так. Чад переметнулся на сторону нарвалов, Стивен погиб - значит, я, как старпом, автоматически становлюсь адмиралом. У тебя возражения есть?";
        link.l1 = "Нет. Никаких возражений.";
        link.l1.go = "admiral_2";
        break;

    case "admiral_2":
        dialog.text = "Вот и славно. Так что по всем вопросам теперь обращайся ко мне.";
        link.l1 = "Ты как-то будешь мстить нарвалам за гибель Стивена?";
        link.l1.go = "admiral_3";
        break;

    case "admiral_3":
        dialog.text = "Ты имеешь в виду - развяжу ли я против них боевые действия? Нет. Существует куда более действенный способ наказать этих ублюдков. Я повышу для них цену на продовольствие в три раза. Пусть платят\nА если они вдруг решатся атаковать 'Сан-Августин' - тем хуже для них, мы обеспечим им достойный приём. Кроме того, я попробую продолжить переговоры с ривадос. Конечно, негритосам доверять нельзя, да и в обиде они на нас за своего колдуна, но любые проблемы решаемы.";
        link.l1 = "Понятно. Ладно, Лейтон, я пойду...";
        link.l1.go = "admiral_4";
        break;

    // нода пересечения
    case "admiral_4":
        dialog.text = "Погоди. Стивен рассказывал мне, что ты намерен как-то покинуть Остров, а затем вернуться сюда на корабле?";
        link.l1 = "Именно это я и собираюсь сделать.";
        link.l1.go = "admiral_5";
        break;

    case "admiral_5":
        dialog.text = "Тогда держи вот эту лоцию. Используя её, ты сможешь добраться сюда морским путём... в живом виде. То есть не сядешь на рифы, не будешь унесён течением и не утонешь в шторме\nБез этой лоции ты либо не найдёшь сюда дорогу, либо пополнишь кладбище кораблей внешнего кольца острова своим судном. Кроме того, учти: пройти через рифы может только судно с относительно небольшой осадкой, манёвренное и быстроходное. Люггер, шхуна, бригантина... в общем, не крупнее четвёртого класса. Мы добрались сюда на бриге\nИ Боже упаси тебя явиться на какой-нибудь калоше типа флейта или галеона, или на большом корабле - они просто не проскочат через рифы и благополучно отправятся на дно. Тут у нас даже линейные корабли есть, например, тот же 'Тартарус'.";
        link.l1 = "Спасибо! Это именно то, что нужно.";
        link.l1.go = "admiral_6";
        break;

    case "admiral_6":
        GiveItem2Character(pchar, "LSC_navigation_map");
        dialog.text = "И когда будешь возвращаться, не забудь заполнить доверху трюмы своего корабля провиантом - как ты понимаешь, я продам его здесь за очень хорошую цену. Лоцию никому не показывай - нечего светить нашу базу. Я дал тебе документ лишь потому, что Стивен сам собирался тебе его отдать, и потому что ты друг Яна Свенсона.";
        link.l1 = "Можешь не беспокоиться на этот счёт. Спасибо ещё раз и до встречи!";
        link.l1.go = "exit";
        NextDiag.TempNode = "Dexter_wait";
        AddQuestRecord("LSC", "5");
        CloseQuestHeader("SharkHunt");
        // убираем квестовые предметы
        sld = ItemsFromID("key_capper");
        sld.price = 10;
        if (CheckCharacterItem(pchar, "letter_chad"))
            RemoveItems(pchar, "letter_chad", 1);
        break;

    case "Dexter_wait":
        dialog.text = "Как успехи в поиске выхода с острова, " + pchar.name + "?";
        link.l1 = "Пока никак, Лейтон. Я работаю над этим.";
        link.l1.go = "exit";
        NextDiag.TempNode = "Dexter_wait";
        break;

    // Акула погиб по варианту M
    case "admiral_7":
        dialog.text = "Вот и ты, " + pchar.name + ". Мне нужно решить с тобой несколько вопросов.";
        link.l1 = "Как я понял, после смерти Стивена ты занял его место. Теперь ты - адмирал?";
        link.l1.go = "admiral_8";
        break;

    case "admiral_8":
        dialog.text = "Именно так. Как старпом Акулы, я автоматически становлюсь адмиралом Острова. У тебя есть какие-то возражения?";
        link.l1 = "Отнюдь. Это место принадлежит тебе по праву.";
        link.l1.go = "admiral_9";
        break;

    case "admiral_9":
        dialog.text = "Очень рад, что мы с тобой сразу нашли общий язык. Теперь по всем вопросам обращайся ко мне.";
        link.l1 = "Ты как-то будешь мстить нарвалам за гибель Стивена?";
        link.l1.go = "admiral_10";
        break;

    case "admiral_10":
        dialog.text = "Ты имеешь в виду - развяжу ли я против них боевые действия? Нет. Существует куда более действенный способ наказать этих ублюдков. Я повышу для них цену на продовольствие в три раза. Пусть платят\nА если они вдруг решатся атаковать 'Сан-Августин' - тем хуже для них, мы обеспечим им достойный приём. К тому же у нас теперь неплохие отношения с ривадос - нарвалы не рискнут рыпаться.";
        link.l1 = "Понятно. Ты что-то ещё хотел мне сказать? Или я могу идти?";
        link.l1.go = "admiral_4";
        break;

    case "plan":
        PlaySound("VOICE\Russian\LSC\Layton Dexter-07");
        dialog.text = "Конечно, есть. Существует единственно возможная тактика атаки нарвалов. Она, конечно, не идеальна, но альтернативы я не вижу. Размещаем нашу ударную группировку на 'Тартарусе', обеспечиваем её несколькими лодками. По сигналу наш десант выдвигается по воде в сторону 'Церес Смити'\nВ этот же момент бойцы ривадос, усиленные нашим вторым отрядом, атакуют 'Эсмеральду' со стороны 'Эвы' и 'Глории'. К тому моменту, когда бойцы будут теснить нарвалов к 'Сан-Габриэлю', наш десант заберётся на палубу 'Церес Смити' и нападёт на нарвалов с тыла - тогда они будут вынуждены либо воевать на два фронта, и мы их легко сомнём, либо уйдут в глухую оборону на 'Сан-Габриэле'\nВторое более вероятно, так как 'Сан-Габриэль' превращён нарвалами в настоящий бастион - взять его будет непросто. Итогом нашего нападения станет захват 'Эсмеральды' и 'Церес Смити', а вот 'Сан-Габриэлем' сходу овладеть не удастся, и, вероятно, придётся вести длительную осаду.";
        link.l1 = "";
        link.l1.go = "plan_1";
        break;

    case "plan_1": // ноду Акуле
        DialogExit();
        npchar.greeting = "dexter_1";
        sld = characterFromId("Dodson");
        sld.dialog.currentnode = "whyskey_final_3";
        LAi_SetActorType(sld);
        LAi_ActorSetSitMode(sld);
        LAi_CharacterEnableDialog(sld);
        LAi_ActorDialogNow(sld, pchar, "", -1);
        NextDiag.CurrentNode = "plan_2";
        break;

    case "plan_2":
        dialog.text = "Мы ждём результатов разговора с Дональдом Гринспи. Это очень важно, не теряй время попусту.";
        link.l1 = "Уже иду!";
        link.l1.go = "exit";
        NextDiag.TempNode = "plan_2";
        break;

    case "map":
        dialog.text = "Да, у меня есть карта. Хочешь купить? Пожалуйста. Двести дублонов на бочку - и она твоя.";
        link.l1 = "А в песо не пойдёт?";
        link.l1.go = "map_1";
        break;

    case "map_1":
        dialog.text = "Нет. Мне нужны дублоны. Так что даже не торгуйся.";
        if (GetCharacterItem(pchar, "gold_dublon") >= 200)
        {
            link.l1 = "Хорошо. Держи свое золото, я согласен.";
            link.l1.go = "map_2";
        }
        link.l2 = "Нет у меня сейчас столько дублонов. Возможно, позже...";
        link.l2.go = "exit";
        NextDiag.TempNode = "First time";
        break;

    case "map_2":
        RemoveItems(pchar, "gold_dublon", 200);
        PlaySound("interface\important_item.wav");
        Log_Info("Вы получили карту Острова Справедливости");
        GiveItem2Character(pchar, "map_LSC");
        dialog.text = "Отличная сделка, парень! Держи свою карту. А что до её стоимости - так я неделю ползал по этому треклятому Острову, пока нарисовал её. Так что ещё недорого продал.";
        link.l1 = "Это недорого? Ну-ну. Но всё равно - спасибо!";
        link.l1.go = "exit";
        NextDiag.TempNode = "First time";
        DeleteAttribute(npchar, "quest.map");
        break;

    // геймовер диким геймерам за издевательство над игрой
    case "LSC_GameOverPrison":
        dialog.text = "Стоять, псих! Да, Акула был прав - этот тип сошёл с ума. Столько людей пострадало из-за него... Вяжи его, ребята, хватаем все сразу, чтобы не дёрнулся! Его надо немедленно изолировать!";
        link.l1 = "...";
        link.l1.go = "LSC_GameOverPrison_1";
        break;

    case "LSC_GameOverPrison_1":
        DialogExit();
        DoQuestReloadToLocation("TartarusPrison", "quest", "prison4", "LSC_GameOverInPrison");
        break;

    case "return":
        dialog.text = "Стивен назначил меня адмиралом Острова вместо себя - как я понимаю, вы отбываете на Карибы вместе. Я остаюсь здесь и буду вести дела - терять такую отличную базу мы со Стивеном не намерены. Хочу тебе сказать, что ты здесь всегда желанный гость.";
        link.l1 = "Спасибо, Лейтон. Думаю, что я ещё не раз посещу Остров.";
        link.l1.go = "return_1";
        break;

    case "return_A":
        dialog.text = "А, мой старый знакомый " + GetFullName(pchar) + "! Ты всё-таки нашёл Остров по лоции Стивена? Очень, очень рад тебя видеть. Ты здесь всегда желанный гость.";
        link.l1 = "Спасибо, Лейтон. Думаю, что я ещё не раз посещу Остров.";
        link.l1.go = "return_1";
        break;

        int iTrade = GetSquadronGoods(pchar, GOOD_FOOD) - GetCrewQuantity(pchar);
        int iMoney = 0;
    case "return_1":
        dialog.text = "Очень хорошо. Да, ты случайно не забыл привезти нам провианта? Я готов купить его у тебя по двухкратной цене.";
        if (iTrade > 0)
        {
            link.l1 = "Да, я могу продать тебе некоторое количество провианта.";
            link.l1.go = "trade";
        }
        link.l2 = "К сожалению, сейчас мне нечего тебе продать.";
        link.l2.go = "return_2";
        npchar.quest.foodqty = 0; // предел затарки складов = 15 000
        break;

    case "return_2":
        dialog.text = "Жаль. В следующий раз не забудь захватить - я хорошо заплачу за него.";
        link.l1 = "Хорошо. Постараюсь не забыть...";
        link.l1.go = "exit";
        NextDiag.TempNode = "head";
        break;

    case "trade":
        dialog.text = "Сколько именно?";
        link.l1.edit = 4;
        link.l1 = "";
        link.l1.go = "trade_1";
        break;

    case "trade_1":
        iTemp = dialogEditStrings[4];
        int iMax = GetSquadronGoods(pchar, GOOD_FOOD) - GetCrewQuantity(pchar);
        if (iTemp <= 0 || iTemp > GetSquadronGoods(pchar, GOOD_FOOD))
        {
            dialog.text = "Чёрт возьми, да ты пьян, дружище... Иди проспись, а торговлей займёмся позже.";
            link.l1 = "Гм...";
            link.l1.go = "exit";
            break;
        }
        if (iTemp <= 50)
        {
            dialog.text = "Ради такого количества я даже свою задницу от стула не оторву. Привози больше!";
            link.l1 = "Гм...";
            link.l1.go = "exit";
            break;
        }
        if (iTemp > iMax)
        {
            dialog.text = "А как ты, дружище, собираешься выходить в море без еды на корабле? Оставь себе хотя бы " + FindRussianQtyString(GetCrewQuantity(pchar)) + ".";
            link.l1 = "Хм, как-то я не подумал.";
            link.l1.go = "exit";
            break;
        }
        iMoney = (50 + drand(5)) * iTemp;
        dialog.text = "" + FindRussianQtyString(iTemp) + "? Хорошо. Я заплачу тебе за товар " + FindRussianMoneyString(iMoney) + ". Устраивает?";
        link.l1 = "Конечно! Хорошая сделка!";
        link.l1.go = "trade_2";
        link.l2 = "Хм. Нет, пожалуй, я передумал продавать.";
        link.l2.go = "exit";
        NextDiag.TempNode = "head";
        break;

    case "trade_2":
        iTemp = dialogEditStrings[4];
        iMoney = (50 + drand(5)) * iTemp;
        AddMoneyToCharacter(pchar, iMoney);
        RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
        npchar.quest.foodqty = sti(npchar.quest.foodqty) + iTemp;
        if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
        {
            SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
            dialog.text = "Вот и славно! Теперь мои склады заполнены доверху. На ближайшие полгода необходимость в закупке провианта отпадает.";
            link.l1 = "Хорошо. Тогда следующую партию я привезу тебе через шесть месяцев.";
            link.l1.go = "exit";
            AddQuestRecord("LSC", "25");
        }
        else
        {
            dialog.text = "Вот и славно! Привози ещё.";
            link.l1 = "Обязательно!";
            link.l1.go = "exit";
        }
        NextDiag.TempNode = "head";
        break;

    case "head": // стандартный диалог Декстера-адмирала
        dialog.text = "А-а, " + GetFullName(pchar) + "! Рад тебя видеть! По какому делу пожаловал?";
        if (iTrade > 0 && sti(npchar.quest.foodqty) < 15000)
        {
            link.l1 = "Я хочу предложить тебе купить у меня некоторое количество провианта.";
            link.l1.go = "trade";
        }
        link.l2 = "Да собственно, ни по какому - зашёл с тобой поздороваться и узнать, как дела.";
        link.l2.go = "exit";
        NextDiag.TempNode = "head";
        break;

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;
    }
}