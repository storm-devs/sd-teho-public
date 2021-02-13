// диалог коменданта форта
void ProcessDialogEvent()
{
    int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
    int iTest;
    ref NPChar, sld, location;
    ref arItem;
    ref rColony;
    aref Link, NextDiag;
    string sTemp;
    float locx, locy, locz;
    bool ok;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    /*NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
    {
        ProcessCommonDialog(NPChar, Link, NextDiag);
        UnloadSegment(NPChar.FileDialog2);
    }*/
    // вызов диалога по городам <--

    switch (Dialog.CurrentNode)
    {
    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    case "fight":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        LAi_group_Attack(NPChar, Pchar);
        if (rand(3) != 1)
            SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

    case "NoMoreTalkExit":
        LAi_CharacterDisableDialog(npchar);
        DialogExit();
        break;

    case "First time":
        location = &Locations[FindLocation(pchar.location)];
        if (rand(4) == 4 && GetNpcQuestPastDayParam(location, "gun_date") > 365 && !CheckAttribute(pchar, "questTemp.PrisonGun"))
        {
            dialog.text = RandPhraseSimple(RandPhraseSimple("Послушайте, у меня к вам есть одно важное дело. Надеюсь, сумеете помочь...", "Капитан, а не заинтересует ли вас некоторое весьма прибыльное предложение?"), RandPhraseSimple("Я тут подумал, что вы могли бы нам помочь в одном весьма важном вопросе.", "Капитан, у меня к вам есть одно деликатное предложение, которое может быть выгодным для нас обоих."));
            link.l1 = "Излагайте, попробуем решить...";
            link.l1.go = "GiveTaskGun";
            location.quest.PrisonGun = "Target";
            SaveCurrentNpcQuestDateParam(location, "gun_date");
            break;
        }

        dialog.text = RandPhraseSimple("Я комендант форта. Что вам нужно здесь?", "Что вам нужно? Зачем вы явились в форт?");
        link.l1 = "Да ничего особенного, осматриваю город, знаете ли. Вот и забрёл сюда по случаю.";
        link.l1.go = "exit";
        //Jason --> мини-квест Дефицитный товар
        if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_ammo" && GetQuestPastDayParam("questTemp.Wine_bottle") < 5)
        {
            link.l11 = "У меня к вам дело, офицер. Думаю, вас это заинтересует. Один из ваших солдат, " + pchar.questTemp.Wine.SName + " пытался через моё посредничество купить вина в городе. Зная ваши порядки...";
            link.l11.go = "Wine_prison";
        }
        // <-- мини-квест Дефицитный товар
        // Карибские нравы
        if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "fraht" && NPChar.location == "portpax_ammo")
        {
            link.l11 = "Здравствуйте, офицер. Я прибыл из колонии Бас-Тер, от человека по имени Жерар Лекруа. В трюме моего корабля груз пороха и бомб для вас...";
            link.l11.go = "trial";
        }
        // Опасный груз -->
        if (pchar.location == "Cumana_Ammo")
        {
            if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
            {
                link.l2 = "Офицер, я вижу, у вас очень озабоченный вид. Могу я чем-то помочь?";
                link.l2.go = "zpq_prs1";
            }
            if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 50000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
            {
                link.l3 = "Спешу сообщить, что груз пороха доставлен. Судно готово встать под разгрузку.";
                link.l3.go = "zpq_ex";
            }
            if (pchar.questTemp.zpq == "begin")
            {
                link.l4 = "Хочу отказаться от нашего договора по доставке пороха. Это оказалось слишком хлопотно...";
                link.l4.go = "zpq_fld2";
            }
        }
        // <-- Опасный груз
        NextDiag.TempNode = "First time";
        break;

    // --> Орудия для форта
    case "GiveTaskGun":
        dialog.Text = LinkRandPhrase("Дело в том, что орудия нашего форта изрядно изношены. Казна, правда, выделила деньги на их замену, но где приобрести новые - я просто в замешательстве: в нашей колонии невозможно найти нужное мне количество. Вот я и подумал, что корабельные орудия с абордированных вами призов могли быть здесь очень кстати.", "Мне нужно заменить орудийную батарею форта. Деньги на это выделены, но, знаете ли... в нашей колонии невозможно приобрести необходимое количество.", "Мне пришло предписание заменить изношенные орудия форта, но с ними такая беда - нигде не могу собрать достаточного количества.");
        Link.l1 = "Хм, а можно подробнее - калибр, количество... цена, наконец.";
        Link.l1.go = "GiveTaskGun_1";
        pchar.questTemp.PrisonGun = true;
        SaveCurrentQuestDateParam("pchar.questTemp.PrisonGun");
        break;

    case "GiveTaskGun_1":
        GetGunType();
        pchar.questTemp.PrisonGun.Sum = makeint(sti(pchar.questTemp.PrisonGun.Price) * sti(pchar.questTemp.PrisonGun.Qty));
        pchar.questTemp.PrisonGun.Luck = rand(4);
        pchar.questTemp.PrisonGun.Id = npchar.location;
        dialog.Text = "Мне необходимы " + pchar.questTemp.PrisonGun.Text + ", в количестве ровно " + sti(pchar.questTemp.PrisonGun.Qty) + " штук. Заплатить готов золотыми дублонами, по " + sti(pchar.questTemp.PrisonGun.Price) + " за штуку. Всего это выйдет " + FindRussianDublonString(sti(pchar.questTemp.PrisonGun.Sum)) + ". Что скажете?.. Да, ещё одно - всю партию приму сразу, но не ранее, чем через месяц - деньги ещё в пути.";
        Link.l1 = RandPhraseSimple("Нет, офицер, не заинтересовало меня ваше предложение... Извините.", "Заманчиво, конечно, но я не возьмусь. Позвольте не объяснять своего решения...");
        Link.l1.go = "exit_gun";
        Link.l2 = RandPhraseSimple("Не скрою, предложение интересное. Считайте, что мы уже договорились.", "Пожалуй, возьмусь. Мне это не сложно, а выгода очевидна.");
        Link.l2.go = "GiveTaskGun_2";
        break;

    case "exit_gun":
        dialog.Text = "Очень жаль... очень жаль, капитан, я на вас рассчитывал. И-и... надеюсь, этот разговор не выйдет за пределы форта?";
        Link.l1 = "Это напоминание было излишним. Всего доброго.";
        Link.l1.go = "exit";
        DeleteAttribute(pchar, "questTemp.PrisonGun");
        NextDiag.TempNode = "First time";
        break;

    case "GiveTaskGun_2":
        dialog.Text = "Вот и по рукам. В сроках я вас не ограничиваю, но, всё же, постарайтесь не растягивать на полгода. И, надеюсь, вы понимаете, что дело конфиденциальное?";
        Link.l1 = "Понимаю. До встречи.";
        Link.l1.go = "exit";
        ReOpenQuestHeader("PrisonGun");
        AddQuestRecord("PrisonGun", "1");
        AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("ся", "ась"));
        AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
        AddQuestUserData("PrisonGun", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData("PrisonGun", "sQty", makeint(pchar.questTemp.PrisonGun.Qty));
        AddQuestUserData("PrisonGun", "sSum", makeint(pchar.questTemp.PrisonGun.Sum));
        AddQuestUserData("PrisonGun", "sText", pchar.questTemp.PrisonGun.Text);
        NextDiag.TempNode = "First time";
        break;

    case "CheckGun":
        if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") < 30)
        {
            dialog.Text = "Я же говорил вам явиться не раньше, чем через месяц!";
            Link.l1 = "Вот чёрт! Так закрутил" + GetSexPhrase("ся", "ась") + ", что потерял" + GetSexPhrase("", "а") + " счёт времени... Извините, приду позже, как и договаривались.";
            Link.l1.go = "exit";
            NextDiag.TempNode = "First time";
            break;
        }
        if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") > 180)
        {
            dialog.Text = "Гм... Знаете, с момента заключения нашего 'договора' прошло больше, чем полгода. Я уже приобрёл орудия. Или вы думали, что я буду ждать вас вечно?";
            Link.l1 = "Вот чёрт! Что же прикажете теперь с ними делать?";
            Link.l1.go = "TakeGun_late";
            break;
        }
        iGunGoods = pchar.questTemp.PrisonGun.Goods;
        amount = GetSquadronGoods(Pchar, iGunGoods) - sti(pchar.questTemp.PrisonGun.Qty);
        sTemp = sti(pchar.questTemp.PrisonGun.Qty);
        iTest = FindColony(NPChar.City); // город

        if (iTest != -1)
        {
            rColony = GetColonyByIndex(iTest);
        }
        ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
        {
            dialog.Text = "Да, вы готовы меня обрадовать?";
            if (amount < 0)
            {
                Link.l1 = "Нет, пока занимаюсь. Просто хотел убедиться, что наш уговор ещё в силе.";
                Link.l1.go = "exit";
            }
            else
            {
                Link.l1 = "Готов. Вся партия в трюме - " + sTemp + " штук, как и договаривались.";
                Link.l1.go = "TakeGun";
            }
        }
        else
        {
            dialog.text = "Что-то я не вижу в порту вашего корабля. Или вы предлагаете тащить пушки через джунгли? Пришвартуйтесь в нашей гавани и возвращайтесь.";
            link.l1 = "Мой корабль на другой стороне острова. Сейчас приведу его в порт.";
            link.l1.go = "exit";
        }
        break;

    case "TakeGun":
        if (pchar.questTemp.PrisonGun.Luck == 4)
        {
            dialog.Text = RandPhraseSimple("Мне право неловко, но я вынужден аннулировать наш уговор.  Нагрянула финансовая проверка, а вы же знаете, как они щепетильны в этих вопросах. Увы, но никак не получится, извините.", "Капитан, тут такое дело... в общем, нам прислали орудия из метрополии, и я, естественно, был вынужден их выкупить. Цены конечно грабительские, но... Извините, что подвёл вас, но я сам весьма огорчён.");
            Link.l1 = "Вот чёрт! Что же прикажете теперь делать?";
            Link.l1.go = "TakeGun_no";
        }
        else
        {
            dialog.Text = RandPhraseSimple("Отлично. Я сейчас же пришлю для выгрузки гарнизонный наряд.", "Великолепно. Солдаты помогут вашим людям с выгрузкой.");
            Link.l1 = "Вы оплату подготовили?";
            Link.l1.go = "TakeGun_1";
        }
        break;

    case "TakeGun_no":
        dialog.Text = "Не знаю. Продайте на верфи, оснастите какое-нибудь торговое судно, утопите... Право же не знаю. И я очень прошу вас, не распространяйтесь об этом деле.";
        Link.l1 = "Это же надо! У меня просто нет слов!";
        Link.l1.go = "exit";
        AddQuestRecord("PrisonGun", "3");
        CloseQuestHeader("PrisonGun");
        DeleteAttribute(pchar, "questTemp.PrisonGun");
        NextDiag.TempNode = "First time";
        break;

    case "TakeGun_late":
        dialog.Text = "Не знаю. Это ваши трудности. Продайте, выбросите, утопите - мне всё равно.";
        Link.l1 = "Эх, зря только время тратил...";
        Link.l1.go = "exit";
        AddQuestRecord("PrisonGun", "4");
        AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("ся", "ась"));
        AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
        CloseQuestHeader("PrisonGun");
        DeleteAttribute(pchar, "questTemp.PrisonGun");
        NextDiag.TempNode = "First time";
        break;

    case "TakeGun_1":
        iGunGoods = pchar.questTemp.PrisonGun.Goods;
        amount = sti(pchar.questTemp.PrisonGun.Qty);
        iTemp = sti(pchar.questTemp.PrisonGun.Sum);
        dialog.Text = "Конечно! Вот ваше золото. Пожалуйста, получите.";
        Link.l1 = "Благодарствую! С вами приятно иметь дело!";
        Link.l1.go = "TakeGun_2";
        TakeNItems(pchar, "gold_dublon", iTemp);
        Log_Info("Вы получили " + FindRussianDublonString(sti(pchar.questTemp.WPU.Escort.Money)) + "");
        PlaySound("interface\important_item.wav");
        RemoveCharacterGoods(Pchar, iGunGoods, amount);
        break;

    case "TakeGun_2":
        dialog.Text = "Взаимно. Вы мне очень помогли. И, прошу вас, пусть эта сделка останется между нами.";
        Link.l1 = "Ну, это само собой разумеется. Всего хорошего.";
        Link.l1.go = "exit";
        AddQuestRecord("PrisonGun", "2");
        AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("", "а"));
        CloseQuestHeader("PrisonGun");
        DeleteAttribute(pchar, "questTemp.PrisonGun");
        NextDiag.TempNode = "First time";
        break;
    // <-- орудия для форта

    //Jason --> мини-квест Дефицитный товар
    case "Wine_prison":
        dialog.text = "Что?! Я строжайше запретил выпивку на территории форта! Ну что же, он поплатится за это. Я вычту из его жалования 1000 песо, которые сейчас передам вам как вознаграждение за вашу бдительность, и отправлю на три дня на гауптвахту.";
        link.l1 = "Благодарю, " + GetAddress_FormToNPC(NPChar) + ". Пресекать подобные нарушения - наш общий долг.";
        link.l1.go = "exit";
        AddMoneyToCharacter(pchar, 1000);
        ChangeCharacterComplexReputation(pchar, "nobility", -1);
        DeleteAttribute(pchar, "questTemp.Wine.bottle");
        pchar.quest.Wine_Exchange.over = "yes"; //снять прерывание
        sld = characterFromId(pchar.questTemp.Wine.id);
        sld.lifeday = 0;
        CloseQuestHeader("Wine");
        NextDiag.TempNode = "First time";
        break;
    // <-- мини-квест Дефицитный товар

    // Карибские нравы
    case "trial":
        iTest = FindColony(NPChar.City); // город
        if (iTest != -1)
        {
            rColony = GetColonyByIndex(iTest);
        }
        ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
        {
            if (GetSquadronGoods(pchar, GOOD_BOMBS) < 2500 || GetSquadronGoods(pchar, GOOD_POWDER) < 2500)
            {
                dialog.text = "Хм. Но у вас же не весь груз! Как такое получилось?";
                link.l1 = "Чёрт побери! Прошу меня извинить - это мой недосмотр. Я немедленно докуплю нужное количество и сдам вам всю партию, как положено.";
                link.l1.go = "exit";
            }
            else
            {
                dialog.text = "Так, значит, это вы - наш курьер? Хорошо. Давайте сначала разберёмся с грузом, а потом уже получите дальнейшие указания.";
                link.l1 = "Давайте.";
                link.l1.go = "trial_1";
            }
        }
        else
        {
            dialog.text = "Что-то я не вижу в порту вашего корабля. Или вы предлагаете тащить груз через джунгли? Пришвартуйтесь в нашей гавани и возвращайтесь.";
            link.l1 = "Мой корабль на другой стороне острова. Сейчас приведу его в порт.";
            link.l1.go = "exit";
        }
        break;

    case "trial_1":
        pchar.quest.Trial_FrahtFail.over = "yes"; //снять таймер
        dialog.text = "Так, груз бомб и пороха в количестве 2500 штук каждого... Хорошо. Солдаты произведут выгрузку сами, ваши люди могут спокойно отдыхать. Получите оплату за фрахт - пять тысяч песо.";
        link.l1 = "Спасибо! Каковы мои дальнейшие действия? Месье Лекруа сказал...";
        link.l1.go = "trial_2";
        break;

    case "trial_2":
        AddMoneyToCharacter(pchar, 5000);
        RemoveCharacterGoods(pchar, GOOD_BOMBS, 2500);
        RemoveCharacterGoods(pchar, GOOD_POWDER, 2500);
        dialog.text = "Да-да, сейчас вы получите инструкции. Готовы меня выслушать внимательно?";
        link.l1 = "Безусловно, офицер.";
        link.l1.go = "trial_3";
        break;

    case "trial_3":
        dialog.text = "Значит, так. У Южного Мэйна, а точнее - у берегов испанской колонии Порто Белло, крейсирует наш военный корабль, фрегат 'Воинственный', под командованием капитана Флориана Шоке. Он подстерегает испанский тяжелый галеон, который должен выйти из Порто Белло через две недели\nПроблема заключается в том, что на нашем фрегате у полутора десятков орудий обнаружился дефект отливки, делающий пушки практически непригодными для ведения боя - они взорвутся после второго-третьего залпа. Испанский галеон, в итоге, превосходит 'Воинственный' и по числу абордажной команды, и по огневой мощи\nБез замены орудий Флориан Шоке будет вынужден отказаться от нападения и уйти ни с чем, а это крайне нежелательно. Ваша задача - спасти операцию, доставив на 'Воинственный' пятнадцать орудий, и не позднее, чем через четырнадцать суток.";
        link.l1 = "То есть, я должен принять на борт полтора десятка орудий, отправиться к Порто Белло, отыскать там фрегат 'Воинственный' и передать пушки капитану Флориану Шоке?";
        link.l1.go = "trial_4";
        break;

    case "trial_4":
        dialog.text = "Так точно. Вы всё правильно поняли. Вы готовы взяться за это дело?";
        link.l1 = "Что насчет оплаты?";
        link.l1.go = "trial_5";
        link.l2 = "Мне жаль, офицер, но я не хочу в это ввязываться. Прошу меня извинить.";
        link.l2.go = "trial_exit";
        break;

    case "trial_exit":
        dialog.text = "Это ваше право, хотя я рассчитывал на ваше согласие. Придется искать другого курьера, а времени практически не осталось... Я вас более не задерживаю, капитан.";
        link.l1 = "Всего доброго.";
        link.l1.go = "trial_exit_1";
        break;

    case "trial_exit_1":
        DialogExit();
        AddQuestRecord("Trial", "6");
        CloseQuestHeader("Trial");
        DeleteAttribute(pchar, "questTemp.Trial");
        break;

    case "trial_5":
        dialog.text = "Насчёт этого не переживайте. Флориан Шоке выплатит вам из корабельной казны двести золотых дублонов. Кроме того, я уверен, что он задействует вас и ваше судно для своих целей. С вашего согласия, конечно.";
        link.l1 = "Хорошо. Я берусь за это поручение! Где орудия?";
        link.l1.go = "trial_6";
        break;

    case "trial_6":
        dialog.text = "Я распоряжусь, чтобы солдаты немедленно погрузили их на ваш корабль. Поскорее отправляйтесь в путь, месье. Желаю удачи!";
        link.l1 = "Благодарю. Она мне точно не помешает, как и попутный ветер...";
        link.l1.go = "trial_7";
        break;

    case "trial_7":
        DialogExit();
        AddQuestRecord("Trial", "7");
        pchar.questTemp.Trial = "cannon";
        SetFunctionTimerCondition("Trial_CannonFail", 0, 0, 14, false); // таймер
        SetCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24) + 15);
        EnemyNationHunterOnMap(true); //запуск перехватчиков
        pchar.quest.Trial_cannon.win_condition.l1 = "location";
        pchar.quest.Trial_cannon.win_condition.l1.location = "Portobello";
        pchar.quest.Trial_cannon.function = "Trial_CreateFlorianFrigate";
        break;

    // Опасный груз -->
    case "zpq_prs1":
        if (!isBadReputation(pchar, 70))
        {
            dialog.text = "Хм, возможно-возможно... пожалуй, благодаря вашей хорошей репутации, рискну вам довериться. В противном случае, я бы даже не стал разговаривать на подобную тему. Дело в том, что нам нужна довольно большая партия непростого груза, так что вам понадобится судно с большим трюмом и готовность рисковать. И вы должны пообещать, что полученная информация останется закрытой для посторонних ушей\nЕсли вас смущает хотя бы одно из условий - скажите об этом сразу. Я думаю, вы меня понимаете...";
            link.l1 = "Достаточно интригующе звучит. И хоть я не догадываюсь, о каком грузе идёт речь, все же готов" + GetSexPhrase("", "а") + " рискнуть, если оплата будет достойной. В любом случае, я даю слово.";
            link.l1.go = "zpq_prs2";
            link.l2 = "Нет, пожалуй... Данное вам слово обяжет меня взяться за дело, которое уже представляется мне весьма сомнительным. Я не стану связываться с этим...";
            link.l2.go = "zpq_fld";
        }
        else
        {
            dialog.text = "Ваша репутация не позволяет мне вести с вами сколько-нибудь серьёзных дел. Прошу вас освободить помещение. Мы сами в состоянии решить свои проблемы.";
            link.l1 = "Ну что ж, решайте...";
            link.l1.go = "exit";
        }
        break;

    case "zpq_fld":
        dialog.text = "Ну, по крайней мере, вы отказались честно и не стали лукавить... Не смею вас задерживать.";
        link.l1 = "Прощайте.";
        link.l1.go = "exit";
        pchar.questTemp.zpq = "failed";
        break;

    case "zpq_fld2":
        dialog.text = "Хм, признаться, не ожидал я такого ретирования. Вынужден просить вас удалиться... И помните про обещание не разглашать полученную информацию.";
        link.l1 = "Прошу меня простить...";
        link.l1.go = "exit";
        ChangeCharacterComplexReputation(pchar, "nobility", -3);
        if (pchar.questTemp.zpq == "begin")
        {
            AddQuestRecord("zpq", "6");
            AddQuestUserData("zpq", "sSex", GetSexPhrase("", "а"));
            CloseQuestHeader("zpq");
        }
        pchar.questTemp.zpq = "failed";
        break;

    case "zpq_prs2":
        dialog.text = "Вот и великолепно. Дело в том, что недавний затяжной шторм подмочил изрядное количество орудийного пороха в арсеналах нашего форта. Надеюсь, вам не нужно объяснять в каком щекотливом положении мы оказались. В случае серьёзной осады, форт вряд ли сможет оказать достойный отпор, мы долго не продержимся.";
        link.l1 = "Теперь ясно, что за груз вам понадобился. И о каком количестве идёт речь?";
        link.l1.go = "zpq_prs3";
        break;

    case "zpq_prs3":
        dialog.text = "Нам нужно 50 000 картузов орудийного пороха. За всю партию я заплачу 300 000 песо... Это очень хорошая цена, сами понимаете. Наше положение вынуждает идти на подобные издержки, хотя мне стоило немалых усилий убедить в этом губернаторского казначея... Сезон штормов не даёт возможности воспользоваться штатными каналами снабжения, да и афишировать такой казус нам не с руки...";
        link.l1 = "Понятно... цена и впрямь хороша. Кстати, вы упомянули о каком-то риске.";
        link.l1.go = "zpq_prs4";
        break;

    case "zpq_prs4":
        dialog.text = "Я имел в виду, что такое количество пороха в трюме может быть очень опасным при транспортировке. На моей памяти было несколько случаев взрыва судов от случайной искры, а уж если в шторм попасть... При перевозке даже конвой держится подальше от такого потенциального брандера, ведь если что случится - всех в щепки разнесёт!..";
        link.l1 = "Ясно... Но я слова на ветер не бросаю - считайте, что заказ принят.";
        link.l1.go = "zpq_prs5";
        link.l2 = "Да уж, сеньор... Страшные вещи вы рассказываете... Что-то мне расхотелось в это ввязываться.";
        link.l2.go = "zpq_fld2";
        break;

    case "zpq_prs5":
        dialog.text = "Вот и прекрасно, я очень рад, что мы договорились. Рассчитаемся сразу же после доставки, можете насчет этого не волноваться\nГруз нужен не ранее, чем через неделю, как раз к этому времени вся сумма будет у меня. Хоть я понимаю, что собрать такую партию будет непросто, и ограничения по времени вам не даю, всё же постарайтесь не затягивать.";
        link.l1 = "Мне всё предельно ясно, сеньор. Приступаю немедленно.";
        link.l1.go = "zpq_prs5_ok";
        break;

    case "zpq_prs5_ok":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        pchar.questTemp.zpq = "begin";
        pchar.questTemp.zpq.time = 20;
        AddQuestRecord("zpq", "1");
        AddQuestUserData("zpq", "sSex", GetSexPhrase("", "а"));
        SaveCurrentQuestDateParam("pchar.questTemp.zpq");
        break;

    case "zpq_ex":
        dialog.text = "Ну наконец-то! Я уж подумал, что вы забыли о нашем договоре. Сейчас распоряжусь отрядить солдат для выгрузки. Обращение с порохом не терпит суеты, хе-хе!";
        link.l1 = "Это всё прекрасно, сеньор, но я вынужден" + GetSexPhrase("", "а") + " напомнить об оплате.";
        link.l1.go = "zpq_ex2";
        RemoveCharacterGoods(pchar, GOOD_POWDER, 50000);
        AddCharacterExpToSkill(pchar, "Sailing", 500);
        AddCharacterExpToSkill(pchar, "Fortune", 500);
        pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
        pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
        pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
        break;

    case "zpq_ex2":
        dialog.text = "Да-да, конечно. Вам сейчас же выплатят 150 000 песо, согласно нашему уговору.";
        link.l1 = "Вы, верно, шутите, сеньор?! Договор был на 300 000, и я не намерен" + GetSexPhrase("", "а") + " уступать ни единого песо!";
        link.l1.go = "zpq_ex3";
        link.l2 = "Я начинаю думать, что вы хотите меня обмануть, поэтому без своих 450 000 песо я отсюда не уйду!";
        link.l2.go = "zpq_ex4";
        link.l3 = "Хм... вижу, обстоятельства изменились. Что ж я готов" + GetSexPhrase("", "а") + " принять указанную сумму, чтоб не накалять обстановку.";
        link.l3.go = "zpq_ex5";
        break;

    case "zpq_ex3":
        if (GetSummonSkillFromName(pchar, "Leadership") > 50)
        {
            dialog.text = "Ах да-а... точно! 300 000 песо. Запамятовал, прошу меня простить. Возраст, знаете ли, уже не тот, склероз... Конечно, вот ваши деньги. Приятно было иметь с вами дело. А теперь прошу меня простить, дела ждут...";
            link.l1 = "Мне тоже приятно, сеньор. Всего вам хорошего.";
            link.l1.go = "exit";
            pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "2");
            AddQuestUserData("zpq", "sSex", GetSexPhrase("", "а"));
            CloseQuestHeader("zpq");
            pchar.questTemp.zpq.sum = 300000;
            AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
        }
        else
        {
            dialog.text = "Что-о?!! Забирай деньги и выметайся вон, иначе сгниёшь в наших казематах!";
            link.l1 = "Да вы, сеньор, оказывается лжец! Предлагаю по-хорошему отдать деньги, о которых мы договаривались или я забираю товар!";
            link.l1.go = "zpq_ex_agry";
            link.l2 = "Прошу меня простить... Хорошо, я возьму предлагаемую сумму, и мы разойдёмся.";
            link.l2.go = "zpq_ex5";
        }
        break;

    case "zpq_ex4":
        dialog.text = "Какая дерзость! Я ещё из ума не выжил и совершенно точно помню, что наш уговор был на 300 000 пе\n... Ах чёрт! тебе не удастся меня надуть!";
        link.l1 = "Не кипятитесь. Лучше подумайте о том, что у стен вашего форта стоит готовый брандер, доверху набитый порохом. Мне достаточно только свистнуть и от ваших укреплений одни руины останутся.";
        link.l1.go = "zpq_ex6";
        break;

    case "zpq_ex6":
        if (GetSummonSkillFromName(pchar, "Leadership") > 75)
        {
            dialog.text = "Гм-гм... веский аргумент. 450 000 песо, говорите? Вот, держите ваши деньги... А теперь прошу меня простить, дела ждут...";
            link.l1 = "Всего вам хорошего, сеньор. Прощайте.";
            link.l1.go = "exit";
            pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "5");
            CloseQuestHeader("zpq");
            pchar.questTemp.zpq.sum = 450000;
            AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
        }
        else
        {
            dialog.text = "Что?! Я боевой офицер! Ты кого пугать вздумал" + GetSexPhrase(", сопляк", "а, соплячка") + "?! Стража, взять е" + GetSexPhrase("го", "ё") + "!!";
            link.l1 = "Ну держитесь, крысы казематные...";
            link.l1.go = "zpq_ex_war";
        }
        break;

    case "zpq_ex5":
        dialog.text = "Прекрасно! Вы сделали правильный выбор. Получите деньги и прощайте. С вами приятно было иметь дело. Ха-ха-ха!";
        link.l1 = "Прощайте...";
        link.l1.go = "exit";
        pchar.questTemp.zpq = "completed";
        AddQuestRecord("zpq", "3");
        AddQuestUserData("zpq", "sSex", GetSexPhrase("", "а"));
        CloseQuestHeader("zpq");
        pchar.questTemp.zpq.sum = 150000;
        AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
        break;

    case "zpq_ex_agry":
        dialog.text = "Ах ты мерзав" + GetSexPhrase("ец", "ка") + "!! Стража, взять е" + GetSexPhrase("го", "ё") + "!!";
        link.l1 = "Аргх!! Придётся забрать деньги с твоего трупа...";
        link.l1.go = "zpq_ex_war";
        break;

    case "zpq_ex_war":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        LAi_SetFightMode(PChar, true);
        pchar.questTemp.zpq = "failed";
        AddQuestRecord("zpq", "4");
        CloseQuestHeader("zpq");
        pchar.questTemp.zpq.sum = 150000;
        AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum) * 2 + rand(5000)));
        GiveItem2Character(npchar, "blade_21");
        EquipCharacterbyItem(npchar, "blade_21");
        npchar.SaveItemsForDead = true;
        npchar.DontClearDead = true;
        npchar.cirassId = Items_FindItemIdx("cirass3");
        chrDisableReloadToLocation = true;
        string slai_group = GetNationNameByType(sti(npchar.nation)) + "_citizens";
        LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
        LAi_group_SetCheck(slai_group, "OpenTheDoors");
        AddSimpleRumour("Ну и дела у нас происходят!! Поговаривают, что в Кумане какой-то заключённый выбрался из казематов, перебил всю охрану форта, ограбил казну и был таков! Ну, дела-а!..", SPAIN, 5, 1);
        break;
        // <-- Опасный груз
    }
}

void GetGunType()
{
    int iGunType;
    if (makeint(pchar.rank) < 6)
        iGunType = rand(1); //18&&24
    if (makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 15)
        iGunType = rand(2); //24&&32
    if (makeint(pchar.rank) >= 15 && makeint(pchar.rank) < 24)
        iGunType = rand(2) + 2; //32&&36&&42
    if (makeint(pchar.rank) >= 24)
        iGunType = 5 - rand(1); //36clv&&42
    int iAdd = makeint(GetSummonSkillFromName(pchar, SKILL_COMMERCE) / 20);

    switch (iGunType)
    {
    case 0:
        pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_24;
        pchar.questTemp.PrisonGun.Price = 28 + iAdd;
        pchar.questTemp.PrisonGun.Qty = sti(pchar.rank) * 5 + 25 + rand(sti(pchar.rank));
        pchar.questTemp.PrisonGun.Text = "пушки 24-го калибра";
        break;
    case 1:
        pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_18;
        pchar.questTemp.PrisonGun.Price = 25 + iAdd;
        pchar.questTemp.PrisonGun.Qty = sti(pchar.rank) * 5 + 25 + rand(sti(pchar.rank));
        pchar.questTemp.PrisonGun.Text = "кулеврины";
        break;
    case 2:
        pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_32;
        pchar.questTemp.PrisonGun.Price = 32 + iAdd;
        pchar.questTemp.PrisonGun.Qty = sti(pchar.rank) * 3 + 15 + rand(sti(pchar.rank));
        pchar.questTemp.PrisonGun.Text = "пушки 32-го калибра";
        break;
    case 3:
        pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_36;
        pchar.questTemp.PrisonGun.Price = 36 + iAdd;
        pchar.questTemp.PrisonGun.Qty = sti(pchar.rank) * 3 + 15 + rand(sti(pchar.rank));
        pchar.questTemp.PrisonGun.Text = "пушки 36-го калибра";
        break;
    case 4:
        pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_36;
        pchar.questTemp.PrisonGun.Price = 49 + iAdd;
        pchar.questTemp.PrisonGun.Qty = sti(pchar.rank) + 15 + rand(sti(pchar.rank));
        pchar.questTemp.PrisonGun.Text = "полные кулеврины";
        break;
    case 5:
        pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_42;
        pchar.questTemp.PrisonGun.Price = 40 + iAdd;
        pchar.questTemp.PrisonGun.Qty = sti(pchar.rank) + 20 + rand(sti(pchar.rank));
        pchar.questTemp.PrisonGun.Text = "пушки 42 калибра";
        break;
    }
}