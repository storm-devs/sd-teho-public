// диалог по городам
// Это мастер тюнинга
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    string sTemp;
    int amount, iSan, iOil, iSil, iRop;
    int iTemp, iSum; // 280912
    ref shTo;
    string s1;

    int Matherial1;
    int Matherial2;
    int Matherial3;
    int Matherial4;
    int HPPrice;

    if (sti(pchar.Ship.Type) != SHIP_NOTUSED)
    {
        int shipCurHP = sti(RealShips[sti(pchar.Ship.Type)].HP);
        int shipBaseHP = sti(RealShips[sti(pchar.Ship.Type)].BaseHP);
        int shipClass = sti(RealShips[sti(pchar.Ship.Type)].Class);
    }

    switch (Dialog.CurrentNode)
    {
    // -----------------------------------Диалог первый - первая встреча
    case "First time": // перехват основного диалога, только один раз
        if (NPChar.quest.meeting == "0")
        {
            Dialog.Text = "Кха... что за скверный климат... Меня зовут " + GetFullName(npchar) + ", и, дьявол меня побери, я лучший корабел на этих забытых Богом островах. Но эта сырость просто валит меня с ног...";
            Link.l1 = pcharrepphrase("Тысяча акул, только старческого брюзжания мне не хватало. Мое имя " + GetFullName(pchar) + ", думаю, вы обо мне слышали.",
                                     "Это не сырость, это старость, уважаемый. Меня зовут " + GetFullName(pchar) + ", думаю, вы обо мне слышали.");
            Link.l1.go = "node_1";
            npchar.quest.meeting = "1";
        }
        else // нужно, если по квестам будет сброс на  "First time"
        {
            dialog.text = "А, это опять вы, опять со своими проблемами... кха... кха.";
            link.l1 = pcharrepphrase("Вы правы, это опять я. Но давайте поговорим о делах, пока вы не отдали Богу душу.",
                                     "У вас хорошая память, а теперь, если позволите, давайте перейдем к более конкретным вопросам.");
            link.l1.go = "node_3";
            link.l2 = pcharrepphrase("Вы утомили меня своим брюзжанием. Прощайте.",
                                     "Мне пора, извините, что побеспокоил" + GetSexPhrase("", "а") + ".");
            link.l2.go = "exit";
        }
        NextDiag.TempNode = "Master_Ship";
        Dialog.CurrentNode = "Master_Ship";
        break;

    case "Master_Ship":
        //Jason ----------------------------------- Хронометр Алекса ------------------------------------------
        if (CheckAttribute(npchar, "quest.sextant") && CheckAttribute(pchar, "questTemp.AlexClock") && pchar.location == "Pirates_shipyard" && !CheckAttribute(npchar, "quest.clock"))
        {
            dialog.text = "А-а, капитан " + GetFullName(pchar) + "! Как хорошо, что вы ко мне зашли!";
            Link.l1 = "Похоже, мастер, я вам для чего-то понадобился, не иначе. Обычно вы куда менее любезны.";
            Link.l1.go = "clock_begin";
            break;
        }
        if (CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "clock" && pchar.location == "Pirates_shipyard")
        {
            dialog.text = "Вижу, вы вернулись не с пустыми руками, капитан! А что стало с... гостями?";
            Link.l1 = "Ушли. Я их попросил - и они ушли.";
            Link.l1.go = "clock_complete";
            break;
        }
        //<-- хронометр Алекса
        dialog.text = "А, это опять вы, опять со своими проблемами... кха... кха.";
        link.l1 = pcharrepphrase("Вы правы, это опять я. Но давайте поговорим о делах, пока вы не отдали Богу душу.",
                                 "У вас хорошая память, а теперь, если позволите, давайте перейдем к более конкретным вопросам.");
        link.l1.go = "node_3";
        link.l2 = pcharrepphrase("Вы утомили меня своим брюзжанием. Прощайте.",
                                 "Мне пора, извините, что побеспокоил" + GetSexPhrase("", "а") + ".");
        link.l2.go = "exit";
        NextDiag.TempNode = "Master_Ship";
        break;

    case "node_1":
        dialog.text = "Молодежь-молодежь, не дождешься от вас никакого почтения. Горячие головы, крепкие руки, что вам еще надо?";
        link.l1 = pcharrepphrase("Это верно. Но рано или поздно всему приходит конец, и похоже, ваше время уже близко...",
                                 "Что-то подсказывает мне, что вы в свои молодые годы тоже не отличались особым почтением к возрасту. Разве не так?");
        link.l1.go = "node_2";
        break;

    case "node_2":
        dialog.text = "Не перечь старшим, " + GetSexPhrase("щенок", "соплячка") + "!";
        link.l1 = pcharrepphrase("Ладно-ладно, не пыжтесь, а то удар хватит. Не хочу, чтоб меня обвинили в смерти лучшего корабела на Карибах. Давайте-ка лучше перейдем к делами.",
                                 "Я прощаю вам эту резкость, только из уважения к вашему возрасту. А теперь, если вы закончили, давайте лучше перейдем к делам.");
        link.l1.go = "node_3";
        link.l2 = pcharrepphrase("Все, с меня хватит нравоучений! Прощайте!",
                                 "Я вижу, общего языка мы не найдем. Прощайте.");
        link.l2.go = "exit";
        break;

    case "node_3":
        dialog.text = "Кха, кха... не дают старику покоя. Что вам опять от меня нужно, " + GetAddress_Form(NPChar) + "? ";
        link.l1 = pcharrepphrase("Мне надо воспользоваться услугами верфи.", "Я хочу воспользоваться услугами вашей верфи.");
        link.l1.go = "shipyard_dlg";
        Link.l2 = "У меня вопрос.";
        Link.l2.go = "quests"; //(пересылка в файл города)
        // -->
        if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
        {
            link.l3 = "Я хотел" + GetSexPhrase("", "а") + " бы поговорить с вами о делах финансовых.";
            link.l3.go = "LoanForAll"; //(перессылка в файл города)
        }
        link.l9 = pcharrepphrase("Черт, у меня есть пара неотложных дел, до свидания.", "Мне уже пора, извините.");
        link.l9.go = "exit";
        NextDiag.TempNode = "Master_Ship";
        break;

    case "shipyard_dlg":
        if ((shipBaseHP - shipCurHP > 0) && (shipClass < 6))
        {
            dialog.Text = "Могу предложить сделать капитальный ремонт корпуса вашего корыта. Здесь совершенно не умеют строить нормальные корабли - рассыпаются на раз...";
            Link.l1 = "Замечательно! У меня как раз есть такой кораблик, требующий ремонта. Может взглянете, что можно сделать?";
            Link.l1.go = "ship_repair_start";
        }
        else
        {
            dialog.Text = "Ну и чего же ты хочешь? Не томи старика...";
        }
        link.l2 = "Я хочу просто воспользоваться услугами верфи.";
        link.l2.go = "shipyard";
        link.l3 = "Мне нужны орудия на корабль.";
        link.l3.go = "Cannons";
        if (RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
        {
            link.l4 = "Хочу изменить внешний вид парусов.";
            link.l4.go = "SailsGerald";
        }
        if (RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_full"))
        {
            link.l50 = "У меня несколько... особенный корабль. Я бы хотел внести в его конструкцию парочку изменений.";
            link.l50.go = "FDM";
        }
        if (RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
        {
            link.l50 = "Я принес еще сундуков для реконструкции каюты.";
            link.l50.go = "FDM_cabin_pay";
        }
        link.l9 = pcharrepphrase("Черт, у меня есть пара неотложных дел, до свидания.", "Мне уже пора, извините.");
        Link.l9.go = "ship_tunning_not_now";
        break;

    case "ship_repair_again":
        if ((shipBaseHP - shipCurHP > 0) && (shipClass < 6))
        {
            dialog.Text = RandPhraseSimple("А... это опять вы... Снова решили свой кораблик поправить?",
                                           RandPhraseSimple("Приветствую известного капитан. Что, опять капремонт понадобился?",
                                                            "Эх... ни минуты покоя нет, не даете старику сосредоточиться.. Опять ремонт?"));
            Link.l1 = "Да. Есть такое дело. Может посмотрим, что можно сделать?";
            Link.l1.go = "ship_repair_start";
        }
        else
        {
            dialog.Text = "Ну и что у тебя опять случилось? Все покоя мне не даешь ...";
        }
        link.l2 = "Я хочу просто воспользоваться услугами верфи.";
        link.l2.go = "shipyard";
        link.l3 = "Мне нужны орудия на корабль.";
        link.l3.go = "Cannons";
        if (RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
        {
            link.l31 = "Хочу изменить внешний вид парусов.";
            link.l31.go = "SailsGerald";
        }
        if (RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_full"))
        {
            link.l50 = "У меня несколько... особенный корабль. Я бы хотел внести в его конструкцию парочку изменений.";
            link.l50.go = "FDM";
        }
        if (RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
        {
            link.l50 = "Я принес еще сундуков для реконструкции каюты.";
            link.l50.go = "FDM_cabin_pay";
        }
        Link.l4 = "У меня вопрос.";
        Link.l4.go = "quests"; //(пересылка в файл города)
        // -->
        if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
        {
            link.l5 = "Я хотел" + GetSexPhrase("", "а") + " бы поговорить с вами о делах финансовых.";
            link.l5.go = "LoanForAll"; //(пересылка в файл города)
        }
        Link.l9 = "Нет. Меня устраивает то, что есть";
        Link.l9.go = "ship_tunning_not_now_2";
        break;

    case "ship_tunning_not_now_2":
        dialog.Text = "Да ты, я погляжу, еще и думаешь! Далеко пойдешь! Приходи, когда решишься и не отвлекай меня по пустякам.";
        Link.l1 = RandPhraseSimple("Спасибо! Всего хорошего.", "Пока, мастер. Можно и без сарказма.");
        Link.l1.go = "ship_tunning_not_now";
        break;

    case "ship_repair_start":
        if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || Pchar.location.from_sea != "Pirates_town")
        {
            dialog.Text = "Корабль-то где? Что вы мне тут голову морочите?!";
            Link.l1 = "И то правда... что это я... Извиняюсь";
            Link.l1.go = "ship_tunning_not_now";
        }
        else
        {
            if (GetHour() == 13)
            {
                dialog.Text = "Я, конечно, трудоголик, но и у меня есть обеденное время. Приходите позже!";
                Link.l1 = "Понятно...";
                Link.l1.go = "ship_tunning_not_now";
            }
            else
            {
                if (makefloat(shipCurHP) / makefloat(shipBaseHP) < 0.10)
                {
                    dialog.Text = "Э-э-э... Корабль-то твой совсем разбит! Не возьмусь я за капитальный ремонт, и не проси. Если бы немного пораньше пришел...";
                    Link.l1 = "Понятно... Очень жаль...";
                    Link.l1.go = "ship_tunning_not_now";
                    break;
                }
                if (makefloat(shipCurHP) / makefloat(shipBaseHP) > 0.95)
                {
                    dialog.Text = "Не морочь мне голову. Твой корабль выглядит как новый - корпус практически целехонек, ремонтировать тут пока нечего.";
                    Link.l1 = "Понятно... Ну я потом как-нибудь зайду...";
                    Link.l1.go = "ship_tunning_not_now";
                    break;
                }
                s1 = "Так-так... посмотрим, что тут у нас есть... Ага, " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
                if (sti(RealShips[sti(Pchar.Ship.Type)].Stolen) == true && !CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning"))
                {
                    s1 = s1 + " Ба! Да корабль-то побывал не в одних руках. То-то он такой потертый. Патент корсарский у тебя есть? Ладно, шучу... к делу.";
                }
                dialog.Text = s1;
                Link.l1 = "Давайте посмотрим что можно сделать.";
                Link.l1.go = "ship_repair_HP";
                Link.l2 = "Постойте! Я передумал" + GetSexPhrase("", "а") + ".";
                Link.l2.go = "ship_tunning_not_now_2";
            }
        }
        break;

    case "ship_repair_HP":
        HPPrice = GetMaterialQtyRepair(pchar, 0);
        Matherial1 = GetMaterialQtyRepair(pchar, 1);
        Matherial2 = GetMaterialQtyRepair(pchar, 2);
        Matherial3 = GetMaterialQtyRepair(pchar, 3);
        Matherial4 = GetMaterialQtyRepair(pchar, 4);

        s1 = "Давайте посмотрим, что можно сделать. Корпус судна сейчас " + shipCurHP + ". Максимально возможное значение " + shipBaseHP;
        s1 = s1 + ". Для полного ремонта мне понадобится: бакаута - " + Matherial1 + ", смол - " + Matherial2 + ", корабельного шелка - " + Matherial3 + " канатов - " + Matherial4 + ".";
        s1 = s1 + " За работу возьму: " + HPPrice + " дублонов на рабочие расходы... Внуки давно зовут меня назад в Европу, не хочется, знаете ли, возвращаться с пустыми руками... Вот, пожалуй и всё. Ах да - деньги вперед.";
        dialog.Text = s1;
        Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
        if (CheckItemMyCabin("gold_dublon") >= HPPrice)
        {
            Link.l1.go = "ship_repair_HP_start_0";
        }
        else
        {
            Link.l1.go = "ship_repair_HP_start";
        }
        Link.l2 = "Нет. Меня это не устраивает.";
        Link.l2.go = "ship_tunning_not_now";
        break;

    case "ship_repair_HP_start_0":
        dialog.Text = "Да, об оплате: можно оплатить сразу, можно отправить посыльного на корабль за необходимой суммой. Как хочешь?";
        link.l1 = "Плачу немедленно.";
        link.l1.go = "ship_repair_HP_start";
        link.l2 = "Отправлю посыльного. Вроде завалялось у меня в сундуках немного золотишка...";
        link.l2.go = "ship_repair_HP_start_1";
        break;

    case "ship_repair_HP_start":
        amount = HPPrice;
        if (GetCharacterItem(pchar, "gold_dublon") >= amount)
        {
            TakeNItems(pchar, "gold_dublon", -amount);
            NPChar.Repair.Money = amount;
            NPChar.Repair.Matherial1 = Matherial1;
            NPChar.Repair.Matherial2 = Matherial2;
            NPChar.Repair.Matherial3 = Matherial3;
            NPChar.Repair.Matherial4 = Matherial4;
            NPChar.Repair.ShipType = Pchar.Ship.Type;
            NPChar.Repair.ShipName = RealShips[sti(Pchar.Ship.Type)].BaseName;
            NPChar.Repair.Delta = shipBaseHP - shipCurHP;

            NextDiag.TempNode = "ship_repair_HP_again";
            dialog.text = "Вот и славно. Жду материал.";
            link.l1 = "Побежал" + GetSexPhrase("", "а") + " за ними...";
            link.l1.go = "Exit";

            ReOpenQuestHeader("ShipRepair");
            AddQuestRecord("ShipRepair", "t1");
            AddQuestUserData("ShipRepair", "sText", "За свою работу по капитальному ремонту корпуса корабля " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + " мастер-корабел требует: бакаута - " + NPChar.Repair.Matherial1 + ", смол - " + NPChar.Repair.Matherial2 + ", корабельного шелка - " + NPChar.Repair.Matherial3 + " канатов - " + NPChar.Repair.Matherial4 + ". В качестве задатка было уплачено " + NPChar.Repair.Money + " дублонов... Говорит, что в Европу собрался - врёт, наверное, старый черт.");
        }
        else
        {
            NextDiag.TempNode = "ship_tunning_not_now";
            dialog.text = RandPhraseSimple("Не вижу задатка...", "Не морочь мне голову....");
            link.l1 = "Я позже зайду.";
            link.l1.go = "Exit";
        }
        break;

    case "ship_repair_HP_start_1":
        AddTimeToCurrent(0, 30);
        amount = HPPrice;
        GetItemMyCabin("gold_dublon", amount);

        NPChar.Repair.Money = amount;
        NPChar.Repair.Matherial1 = Matherial1;
        NPChar.Repair.Matherial2 = Matherial2;
        NPChar.Repair.Matherial3 = Matherial3;
        NPChar.Repair.Matherial4 = Matherial4;
        NPChar.Repair.ShipType = Pchar.Ship.Type;
        NPChar.Repair.ShipName = RealShips[sti(Pchar.Ship.Type)].BaseName;
        NPChar.Repair.Delta = shipBaseHP - shipCurHP;

        NextDiag.TempNode = "ship_repair_HP_again";
        dialog.text = "Вот и славно. Жду материал.";
        link.l1 = "Побежал" + GetSexPhrase("", "а") + " за ними...";
        link.l1.go = "Exit";

        ReOpenQuestHeader("ShipRepair");
        AddQuestRecord("ShipRepair", "t1");
        AddQuestUserData("ShipRepair", "sText", "За свою работу по капитальному ремонту корпуса корабля " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + " мастер-корабел требует: бакаута - " + NPChar.Repair.Matherial1 + ", смол - " + NPChar.Repair.Matherial2 + ", корабельного шелка - " + NPChar.Repair.Matherial3 + " канатов - " + NPChar.Repair.Matherial4 + ". В качестве задатка было уплачено " + NPChar.Repair.Money + " дублонов... Говорит, что в Европу собрался - врёт, наверное, старый черт.");

        break;

    case "ship_repair_HP_again":
        if (sti(NPChar.Repair.ShipType) == sti(Pchar.Ship.Type) && NPChar.Repair.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName)
        {
            NextDiag.TempNode = "ship_repair_HP_again";
            dialog.Text = "Работа ждет. Принес" + GetSexPhrase("", "ла") + ", что я просил?";
            Link.l1 = "Да. Кое-что удалось достать.";
            Link.l1.go = "ship_repair_HP_again_2";
            Link.l2 = "Нет. Еще добываю.";
            Link.l2.go = "Exit";
        }
        else
        {
            DeleteAttribute(NPChar, "Repair");
            NextDiag.TempNode = "ship_repair_again";
            dialog.Text = "Сдается мне, судар" + GetSexPhrase("ь", "ыня") + ", что вы поменяли корабль со времени нашего уговора. Придется все заново расчитывать...";
            Link.l1 = "Было дело. Обидно, что задаток пропал...";
            Link.l1.go = "Exit";
            AddQuestRecord("ShipRepait", "Lose");
            CloseQuestHeader("ShipRepair");
        }
        break;

    case "ship_repair_HP_again_2":
        checkMatherial_repair(Pchar, NPChar, GOOD_SANDAL, 1);
        checkMatherial_repair(Pchar, NPChar, GOOD_OIL, 2);
        checkMatherial_repair(Pchar, NPChar, GOOD_SHIPSILK, 3);
        checkMatherial_repair(Pchar, NPChar, GOOD_ROPES, 4);
        if (sti(NPChar.Repair.Matherial1) < 1 &&
            sti(NPChar.Repair.Matherial2) < 1 &&
            sti(NPChar.Repair.Matherial3) < 1 &&
            sti(NPChar.Repair.Matherial4) < 1)
        {
            NextDiag.TempNode = "ship_repair_again";
            dialog.text = "Все привез" + GetSexPhrase("", "ла") + ". Молодец! Начинаю работу...";
            link.l1 = "Жду.";
            link.l1.go = "ship_repair_HP_complite";
        }
        else
        {
            NextDiag.TempNode = "ship_repair_HP_again";
            dialog.Text = "Тебе осталось привезти: бакаута - " + sti(NPChar.Repair.Matherial1) + ", смол - " + sti(NPChar.Repair.Matherial2) + ", корабельного шелка - " + NPChar.Repair.Matherial3 + " канатов - " + NPChar.Repair.Matherial4 + ".";
            link.l1 = "Хорошо.";
            link.l1.go = "Exit";

            AddQuestRecord("ShipRepair", "t1");
            AddQuestUserData("ShipRepair", "sText", "Мне осталось довезти: бакаута - " + NPChar.Repair.Matherial1 + ", смол - " + NPChar.Repair.Matherial2 + ", корабельного шелка - " + NPChar.Repair.Matherial3 + " канатов - " + NPChar.Repair.Matherial4 + ".");
        }
        break;

    case "ship_repair_HP_complite":
        AddTimeToCurrent(6, 30);
        shTo = &RealShips[sti(Pchar.Ship.Type)];
        shTo.HP = sti(shTo.HP) + sti(NPChar.Repair.Delta);
        DeleteAttribute(NPChar, "Repair");

        pchar.ship.hp = GetCharacterShipHP(pchar);
        DeleteAttribute(pchar, "ship.hulls");
        DeleteAttribute(pchar, "ship.blots");

        NextDiag.TempNode = "node_3";
        dialog.Text = "... Вроде бы все... Гарантирую, что развалить этот кораблик теперь будет очень непросто!";
        Link.l1 = "Спасибо! Но с этим лучше не экспериментировать.";
        Link.l1.go = "Exit";
        AddQuestRecord("ShipRepair", "End");
        CloseQuestHeader("ShipRepair");
        break;

    ///////////////////////////////  квестовые ветки
    case "quests":
        dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "У себя на верфи, да и вообще в городе, я таких однообразно любознательных не видел.",
                                              "Ну что за вопросы? Мое дело - корабли строить, давайте этим и займемся.", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал" + GetSexPhrase("", "а") + "...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                                           "Хм, однако...", "Давайте...", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        if (!CheckAttribute(npchar, "Step_Door"))
        {
            link.l2 = "Послушай, я хочу пройти, а дверь закрыта...";
            link.l2.go = "Step_Door_1";
        }

        if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
        {
            link.l1 = "Хочу предложить сделку.";
            link.l1.go = "Al_ShipLetters_1"; // генератор  "Найденные документы"
            pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
        }
        if (CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "go") // 280912
        {
            link.l1 = "Я по поводу материалов для фрегата.";
            link.l1.go = "clock";
        }
        if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
        {
            link.l1 = "Послушай, " + npchar.name + ", ты не видел в последнее время на Исла Тесоро Мигеля Дичозо?";
            link.l1.go = "tieyasal";
        }
        break;
        //*************************** Генератор - "Найденные судовые документы" **************

    case "Al_ShipLetters_1":
        dialog.text = "Излагайте условия.";
        s1 = "У меня, по счастливой случайности, оказался абсолютно легальный пакет судовых документов, еще не заявленных в розыск.";
        s1 = s1 + "Судно на плаву и не исключено из реестра, не беспокойтесь. Просто разиня-владелец умудрился потерять эти бумаги...";
        link.l1 = s1;
        link.l1.go = "Al_ShipLetters_2";
        break;
    case "Al_ShipLetters_2":
        s1 = "Дайте-ка взглянуть! Действительно, отметки совсем свежие. Что же, удача Вам благоволит, судар" + GetSexPhrase("ь", "ыня") + "! ";
        s1 = s1 + "Мне как раз понадобился именно такой комплект, и я, в свою очередь предлагаю Вам " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " песо. Что скажете?";
        dialog.text = s1;
        link.l1 = "Воистину королевская щедрость! Конечно же я соглас" + GetSexPhrase("ен", "на") + "!";
        link.l1.go = "Al_ShipLetters_3";
        link.l2 = "Пожалуй, нет.";
        link.l2.go = "exit";
        break;
    case "Al_ShipLetters_3":
        TakeItemFromCharacter(pchar, "CaptainBook");
        addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5));
        ChangeCharacterComplexReputation(pchar, "nobility", -1);
        OfficersReaction("bad");
        pchar.questTemp.different = "free";
        pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
        AddQuestRecord("GiveShipLetters", "9");
        CloseQuestHeader("GiveShipLetters");
        DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

        //*************************** Открывание двери ***************************
    case "Step_Door_1":
        dialog.text = "Все верно. Чтобы здесь пройти, тебе надо заплатить мне 20000 монет. Не заплатишь - не открою, у меня здесь не проходной двор. Да и тебе там шляться не советую - не к добру...";
        if (sti(pchar.money) >= 20000)
        {
            link.l1 = "Вот твои деньги, открывай.";
            link.l1.go = "Step_Door_2";
        }
        else
        {
            link.l1 = "Нет у меня таких денег.";
            link.l1.go = "Step_Door_3";
        }
        link.l2 = "Вот еще! Платить за какую-то дверь.";
        link.l2.go = "exit";
        break;

    case "Step_Door_2":
        npchar.Step_Door = true; // fix
        dialog.text = "Проходи, дверь открыта. И не благодари!";
        link.l1 = "Да чего уж там, спасибо тебе, " + npchar.name + "...";
        link.l1.go = "exit";
        LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
        AddMoneyToCharacter(pchar, -20000);
        pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
        pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
        break;

    case "Step_Door_3":
        dialog.text = "Ну вот когда будут, тогда и приходи. А так и не уговаривай - бесполезно...";
        link.l1 = "Аргх, ну слов просто никаких нет!";
        link.l1.go = "exit";
        break;

        // ------------------------------------------- хронометр Алекса ----------------------------------------------// Addon-2016 Jason замена дублонов на песо везде
    case "clock_begin":
        dialog.text = "Ну-ну, не будьте столь суровы к старику... Мне действительно нужна ваша помощь, капитан.";
        link.l1 = "Выкладывайте, мастер, что у вас там стряслось.";
        link.l1.go = "clock_begin_1";
        break;

    case "clock_begin_1":
        sTotalTemp = "Стивен Додсон";
        if (pchar.questTemp.Alex.Clock == "terrax")
            sTotalTemp = "Маркус Тиракс";
        dialog.text = "Наш новый глава Берегового братства, " + sTotalTemp + ", заказал у меня корабль, фрегат. И поставил непростые задачи: корпус повышенной прочности в сочетании с хорошей скростью и маневренностью, плюс орудия максимально возможного калибра. Я понимаю, все-таки - 'адмиральский' корабль, но для выполнения подобного заказа нужны особые материалы. Вы, вероятно, слышали о таких\nМне нужен бакаут и смолы для крепкого корпуса и орудийных лафетов, корабельный шелк для парусов, чувствительных к малейшему дуновению ветра, специальные пеньковые канаты...";
        link.l1 = "Так скажите об этом главе Братства. Или опасаетесь, что " + sTotalTemp + " снимет с вас за это голову?";
        link.l1.go = "clock_begin_2";
        break;

    case "clock_begin_2":
        dialog.text = "Да я-то сказал... Просто у нашего нового главы сейчас нет ни времени, ни возможности раздобыть эти материалы. Вы же должны знать, какая это редкость. А без них построить фрегат с заявленными характеристиками я никак не смогу.";
        link.l1 = "И вы, вероятно, предлагаете мне подсуетиться с поиском материалов для корабля?";
        link.l1.go = "clock_begin_3";
        break;

    case "clock_begin_3":
        dialog.text = "Ну да. Вы же хороший друг нашего главы. " + sTotalTemp + " сам говорил, что многим вам обязан, и требует всяческого уважения к вам... Вот я и подумал: раз вы ему друг, то, быть может, возьметесь ему помочь? А заодно и мне: вы же понимаете, в каком я нелепом положении? Весь материал будет оплачен, " + sTotalTemp + " не скупится на золото.";
        link.l1 = "Я очень сожалею, мастер, но я сейчас занят не меньше, чем " + sTotalTemp + ". Боюсь, что сбор материалов может занять целую вечность. Так что лучше вы попросите кого-нибудь еще.";
        link.l1.go = "clock_exit";
        link.l2 = "Ну, раз заказчик корабля " + sTotalTemp + " - то конечно, попробую помочь. Все-таки мы и правда с ним друзья, а друзьям нужно помогать. Сколько вам нужно материалов?";
        link.l2.go = "clock_begin_4";
        break;

    case "clock_exit":
        dialog.text = "Жаль, очень жаль. Я надеялся на вас. Ну, как говорится, на 'нет' - и суда нет...";
        link.l1 = "...";
        link.l1.go = "exit";
        DeleteAttribute(pchar, "questTemp.AlexClock");
        break;

    case "clock_begin_4":
        dialog.text = "Мне не хватает 100 единиц бакаута, 150 бочонков смол, 110 рулонов корабельного шелка и 90 бухт пеньковых канатов. Как думаете, разыщете мне все это месяца за четыре? Больше я навряд ли смогу ждать.";
        link.l1 = "По крайней мере - попытаюсь. Что насчет оплаты?";
        link.l1.go = "clock_begin_5";
        break;

    case "clock_begin_5":
        dialog.text = "Расценки таковы: бакаут - 4000 песо за штуку, смолы - 1400 песо за бочонок, шелк - 2500 песо за рулон, канаты - 1500 песо за бухту. И если вы все мне привезете, получите полезный подарок от меня.";
        link.l1 = "Какой, интересно?";
        link.l1.go = "clock_begin_6";
        break;

    case "clock_begin_6":
        dialog.text = "А вы сначала привезите. Но уверяю: вещица полезная, и второй такой на Карибах, да и во всем мире, нет. Надеюсь, эта маленькая интрига подогреет ваш интерес к сбору материалов.";
        link.l1 = "Ух, ну хитрый же вы, мастер! Ладно, договорились.";
        link.l1.go = "clock_begin_7";
        break;

    case "clock_begin_7":
        dialog.text = "Я очень рад. Буду ждать вас с нетерпением.";
        link.l1 = "Надеюсь, это не займет слишком много времени...";
        link.l1.go = "clock_begin_8";
        break;

    case "clock_begin_8":
        DialogExit();
        pchar.questTemp.AlexClock = "go";
        npchar.quest.clock = "true";
        SetFunctionTimerCondition("AlexClock_Over", 0, 0, 122, false); // таймер
        AddQuestRecord("alex_clock", "1");
        // запоминаем переменные
        pchar.questTemp.AlexClock.Sandal = 100;
        pchar.questTemp.AlexClock.Oil = 150;
        pchar.questTemp.AlexClock.Shipsilk = 110;
        pchar.questTemp.AlexClock.Ropes = 90;
        break;

    case "clock":
        dialog.text = "Очень хорошо! Что вы привезли мне сегодня?";
        if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && !CheckAttribute(npchar, "quest.sandal"))
        {
            iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
            link.l1 = "Бакаут, в количестве " + FindRussianQtyString(iSan) + ".";
            link.l1.go = "sandal";
        }
        if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && !CheckAttribute(npchar, "quest.oil"))
        {
            iOil = GetSquadronGoods(pchar, GOOD_OIL);
            link.l2 = "Смолы, в количестве " + FindRussianQtyString(iOil) + ".";
            link.l2.go = "oil";
        }
        if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && !CheckAttribute(npchar, "quest.shipsilk"))
        {
            iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            link.l3 = "Корабельный шелк, в количестве " + FindRussianQtyString(iSil) + ".";
            link.l3.go = "shipsilk";
        }
        if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && !CheckAttribute(npchar, "quest.ropes"))
        {
            iRop = GetSquadronGoods(pchar, GOOD_ROPES);
            link.l4 = "Пеньковые канаты, в количестве " + FindRussianQtyString(iRop) + ".";
            link.l4.go = "ropes";
        }
        link.l5 = "Пока ничего. Просто хотел убедиться, что договор еще в силе.";
        link.l5.go = "exit";
        break;

    case "clock_1":
        if (CheckAttribute(npchar, "quest.sandal") && CheckAttribute(npchar, "quest.oil") && CheckAttribute(npchar, "quest.shipsilk") && CheckAttribute(npchar, "quest.ropes")) // все привез
        {
            dialog.text = "Великолепно! Все материалы и в нужном количестве - у меня. Огромное вам спасибо за помощь, капитан. Вы, право, меня выручили.";
            link.l1 = "Да всегда пожалуйста, мастер. Я тоже остался вполне доволен: и другу помог, и подзаработал неплохо. А теперь вернемся к разговору о вашей таинственной вещице, которую вы мне обещали.";
            link.l1.go = "clock_2";
        }
        else
        {
            dialog.text = "Еще чем-нибудь меня порадуете, капитан?";
            link.l1 = "Увы, пока это все. Ожидайте.";
            link.l1.go = "exit";
            link.l2 = "Да, у меня есть еще кое-что...";
            link.l2.go = "clock";
        }
        break;

    case "sandal": // бакаут
        amount = sti(pchar.questTemp.AlexClock.Sandal);
        iTemp = amount - iSan;
        if (iTemp > 0) // еще не все привез
        {
            iSum = 4000 * iSan;
            dialog.text = "Так-так. Мне еще необходимо " + FindRussianQtyString(amount) + " бакаута. Вы привезли " + FindRussianQtyString(iSan) + ". Значит, осталось довезти " + FindRussianQtyString(iTemp) + ". Итак, исходя из цены в 4000 песо, ваше вознаграждение составляет " + FindRussianMoneyString(iSum) + ". Извольте получить.";
            link.l1 = "Спасибо! Скоро будет и все остальное.";
            link.l1.go = "clock_1";
            RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
            pchar.questTemp.AlexClock.Sandal = iTemp; // столько осталось довезти
            AddQuestRecord("alex_clock", "2");
            AddQuestUserData("alex_clock", "sGood", "бакаута");
            AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
        }
        else
        {
            iSum = 4000 * amount;
            dialog.text = "Так-так. Мне еще необходимо " + FindRussianQtyString(amount) + " бакаута. Вы привезли " + FindRussianQtyString(iSan) + ". Значит, вопрос с бакаутом мы с вами закрыли! Итак, исходя из цены в 4000 песо, ваше вознаграждение составляет " + FindRussianMoneyString(iSum) + ". Извольте получить.";
            link.l1 = "Спасибо!";
            link.l1.go = "clock_1";
            RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
            npchar.quest.sandal = "true";
            AddQuestRecord("alex_clock", "3");
            AddQuestUserData("alex_clock", "sGood", "бакаута");
        }
        AddMoneyToCharacter(pchar, iSum);
        break;

    case "oil": // смолы
        amount = sti(pchar.questTemp.AlexClock.Oil);
        iTemp = amount - iOil;
        if (iTemp > 0) // еще не все привез
        {
            iSum = 1400 * iOil;
            dialog.text = "Так-так. Мне еще необходимо " + FindRussianQtyString(amount) + " смол. Вы привезли " + FindRussianQtyString(iOil) + ". Значит, осталось довезти " + FindRussianQtyString(iTemp) + ". Итак, исходя из цены в 1400 песо, ваше вознаграждение составляет " + FindRussianMoneyString(iSum) + ". Извольте получить.";
            link.l1 = "Спасибо! Скоро будет и все остальное.";
            link.l1.go = "clock_1";
            RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
            pchar.questTemp.AlexClock.Oil = iTemp; // столько осталось довезти
            AddQuestRecord("alex_clock", "2");
            AddQuestUserData("alex_clock", "sGood", "смол");
            AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
        }
        else
        {
            iSum = 1400 * amount;
            dialog.text = "Так-так. Мне еще необходимо " + FindRussianQtyString(amount) + " смол. Вы привезли " + FindRussianQtyString(iOil) + ". Значит, вопрос со смолами мы с вами закрыли! Итак, исходя из цены в 1400 песо, ваше вознаграждение составляет " + FindRussianMoneyString(iSum) + ". Извольте получить.";
            link.l1 = "Спасибо!";
            link.l1.go = "clock_1";
            RemoveCharacterGoods(pchar, GOOD_OIL, amount);
            npchar.quest.oil = "true";
            AddQuestRecord("alex_clock", "3");
            AddQuestUserData("alex_clock", "sGood", "смол");
        }
        AddMoneyToCharacter(pchar, iSum);
        break;

    case "shipsilk": // шелк
        amount = sti(pchar.questTemp.AlexClock.Shipsilk);
        iTemp = amount - iSil;
        if (iTemp > 0) // еще не все привез
        {
            iSum = 2600 * iSil;
            dialog.text = "Так-так. Мне еще необходимо " + FindRussianQtyString(amount) + " шелка. Вы привезли " + FindRussianQtyString(iSil) + ". Значит, осталось довезти " + FindRussianQtyString(iTemp) + ". Итак, исходя из цены в 2600 песо, ваше вознаграждение составляет " + FindRussianMoneyString(iSum) + ". Извольте получить.";
            link.l1 = "Спасибо! Скоро будет и все остальное.";
            link.l1.go = "clock_1";
            RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
            pchar.questTemp.AlexClock.Shipsilk = iTemp; // столько осталось довезти
            AddQuestRecord("alex_clock", "2");
            AddQuestUserData("alex_clock", "sGood", "шелка");
            AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
        }
        else
        {
            iSum = 2600 * amount;
            dialog.text = "Так-так. Мне еще необходимо " + FindRussianQtyString(amount) + " шелка. Вы привезли " + FindRussianQtyString(iSil) + ". Значит, вопрос с шелком мы с вами закрыли! Итак, исходя из цены в 2600 песо, ваше вознаграждение составляет " + FindRussianMoneyString(iSum) + ". Извольте получить.";
            link.l1 = "Спасибо!";
            link.l1.go = "clock_1";
            RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
            npchar.quest.shipsilk = "true";
            AddQuestRecord("alex_clock", "3");
            AddQuestUserData("alex_clock", "sGood", "шелка");
        }
        AddMoneyToCharacter(pchar, iSum);
        break;

    case "ropes": // канаты
        amount = sti(pchar.questTemp.AlexClock.Ropes);
        iTemp = amount - iRop;
        if (iTemp > 0) // еще не все привез
        {
            iSum = 1500 * iRop;
            dialog.text = "Так-так. Мне еще необходимо " + FindRussianQtyString(amount) + " канатов. Вы привезли " + FindRussianQtyString(iRop) + ". Значит, осталось довезти " + FindRussianQtyString(iTemp) + ". Итак, исходя из цены в 1500 песо, ваше вознаграждение составляет " + FindRussianMoneyString(iSum) + ". Извольте получить.";
            link.l1 = "Спасибо! Скоро будет и все остальное.";
            link.l1.go = "clock_1";
            RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
            pchar.questTemp.AlexClock.Ropes = iTemp; // столько осталось довезти
            AddQuestRecord("alex_clock", "2");
            AddQuestUserData("alex_clock", "sGood", "канатов");
            AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
        }
        else
        {
            iSum = 1500 * amount;
            dialog.text = "Так-так. Мне еще необходимо " + FindRussianQtyString(amount) + " канатов. Вы привезли " + FindRussianQtyString(iRop) + ". Значит, вопрос с канатами мы с вами закрыли! Итак, исходя из цены в 1500 песо, ваше вознаграждение составляет " + FindRussianMoneyString(iSum) + ". Извольте получить.";
            link.l1 = "Спасибо!";
            link.l1.go = "clock_1";
            RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
            npchar.quest.ropes = "true";
            AddQuestRecord("alex_clock", "3");
            AddQuestUserData("alex_clock", "sGood", "канатов");
        }
        AddMoneyToCharacter(pchar, iSum);
        break;

    case "clock_2":
        dialog.text = "Да-да... о моей вещице, конечно. М-м-м...";
        link.l1 = "Что такое, мастер? У вас очень озабоченный вид. Что-то не так? Какие-то проблемы?";
        link.l1.go = "clock_3";
        break;

    case "clock_3":
        dialog.text = "Именно так. Проблемы. И появились они совсем недавно. Черт бы побрал этих проклятых кладокопателей, принесло их на мою голову...";
        link.l1 = "Тише, тише, в вашем возрасте вредно так волноваться. Не дай Бог - удар хватит, кто потом фрегат для главы братства строить будет? Объясните спокойно, что за кладокопатели?";
        link.l1.go = "clock_4";
        break;

    case "clock_4":
        dialog.text = "Вон там, у моего стола - дверь. Она ведет прямиком в старое подземелье. Так вот, в этом подземелье, в одном из сундуков, я держу свой металлический ящик с предметами, которые были со мной, когда меня двадцать лет назад затянуло в эту проклятую воронку, и я очутился тут...";
        link.l1 = "Какую воронку? О чем вы?";
        link.l1.go = "clock_5";
        break;

    case "clock_5":
        dialog.text = "Ах, простите, кажется, я увлекся своими фантазиями. Старость - не радость, молодой человек. Извините... Но неважно. Важно то, что мой ящик с вашим подарком лежит сейчас в сундуке в подземелье, а по нему уже который день шляются какие-то темные личности. Они не из наших, не с Исла Тесоро\nХодят, вынюхивают, ковыряются в сундуках. Кладокопатели, которым кто-то сообщил, что здесь можно поживиться. Сюда, ко мне, они залезть навряд ли рискнут, но и я туда сунуться боюсь, понимаете? У них такие рожи, что...";
        link.l1 = "Ясно. Отпирайте вашу дверь - пойду, выкурю незваных гостей.";
        link.l1.go = "clock_6";
        break;

    case "clock_6":
        dialog.text = "Вот так просто - пойду выкурю? В одиночку? Вам не страшно?";
        link.l1 = "Меньше слов, больше дела, мастер. Отпирайте эту дверь, а остальное предоставьте мне. В каком сундуке вы держите свои вещи?";
        link.l1.go = "clock_7";
        break;

    case "clock_7":
        dialog.text = "Прямо по коридору есть целая куча пустых деревянных бочек. За ними на полу, в укромном месте, стоит небольшой сундучок. Я врезал в него замок, так что навряд ли эти проходимцы сумели запустить в него свои грязные лапы, если даже и отыскали. Вот, возьмите ключ.";
        link.l1 = "Это радует, что вы оказались столь предусмотрительны. Ждите меня здесь и никуда не уходите.";
        link.l1.go = "clock_8";
        break;

    case "clock_8":
        DialogExit();
        GiveItem2Character(pchar, "key3");
        bDisableFastReload = true; //закрыть переход
        LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", true);
        LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
        LAi_LocationDisableOfficersGen("Bermudes_Dungeon", true); //офицеров не пускать
        pchar.quest.Alex_Chest.win_condition.l1 = "location";
        pchar.quest.Alex_Chest.win_condition.l1.location = "Bermudes_Dungeon";
        pchar.quest.Alex_Chest.function = "AlexClock_Chest";
        pchar.quest.AlexClock_Over.over = "yes"; //снять прерывание
        pchar.questTemp.AlexClock = "chest";
        AddQuestRecord("alex_clock", "3");
        break;

    case "clock_complete":
        dialog.text = "Прямо так послушались и ушли?";
        link.l1 = "Прямо так. Они оказались вежливыми ребятами. Я им объяснил, что их присутствие пугает одного знаменитого корабела, и они из уважения к вашим сединам покинули подземелье. Можете спускаться туда без опаски.";
        link.l1.go = "clock_complete_1";
        break;

    case "clock_complete_1":
        dialog.text = "Ох, разыгрываете вы старика! Ладно. Дайте мне мой ящик, я отопру его и отдам ваш честно заработанный прибор.";
        link.l1 = "Пожалуйста, держите...";
        link.l1.go = "clock_complete_2";
        break;

    case "clock_complete_2":
        RemoveItems(pchar, "alexs_chest", 1);
        dialog.text = "Благодарствую!.. Так, откроем... Вот, держите. Это механический хронометр с автовзводом, таких у вас не сделает никто еще в ближайшие лет триста... ой, простите старика, опять я за свое. Я хотел сказать - второго такого хронометра нет во всем свете. Он способен отсчитывать мельчайшие доли минуты и не требует никакого обслуживания\nНикаких ваших песочных часов и никаких погрешностей! Только берегите его от ударов и не допускайте контакта с водой, особенно морской - загубите прибор безвозвратно. Пользоваться им элементарно просто.";
        link.l1 = "Вот это вещь! В жизни такого чуда не видел! Спасибо, мастер.";
        link.l1.go = "clock_complete_3";
        break;

    case "clock_complete_3":
        GiveItem2Character(pchar, "clock3");
        Log_Info("Вы получили механический хронометр с автовзводом");
        SetAlchemyRecipeKnown("sextant2");
        PlaySound("interface\important_item.wav");
        dialog.text = "На здоровье. Теперь вы всегда будете знать точно, который час. А вот откуда он у меня - и не спрашивайте, все равно не расскажу.";
        link.l1 = "У каждого есть свои тайны, так, мастер? Храните свою тайну, я не буду лезть вам в душу. Спасибо за подарок!";
        link.l1.go = "clock_complete_4";
        break;

    case "clock_complete_4":
        dialog.text = "И вам спасибо за помощь, капитан. Заглядывайте ко мне, не забывайте старого корабела.";
        link.l1 = "Вас забудешь... Я хотел сказать - обязательно, мастер Алексус. До свидания!";
        link.l1.go = "clock_complete_5";
        break;

    case "clock_complete_5":
        DialogExit();
        bDisableFastReload = false;
        LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
        LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
        LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", false);
        LAi_LocationDisableOfficersGen("Bermudes_Dungeon", false);
        AddQuestRecord("alex_clock", "5");
        CloseQuestHeader("alex_clock");
        DeleteAttribute(pchar, "questTemp.AlexClock");
        break;
        // <-- хронометр Алекса

    // город майя
    case "tieyasal":
        dialog.text = "А-а, мой старый знакомец Мигель! Как же, был, был. И снова все у меня выспрашивал, о том, о сем. Но как же я объясню ему, как устроено внутри радио, ежели он даже простого телеграфа в глаза не видел?";
        link.l1 = "Что?.. Вы это о чем сейчас, мастер?";
        link.l1.go = "tieyasal_1";
        break;

    case "tieyasal_1":
        dialog.text = "Ох, простите, молодой человек, я что-то увлекся. Hе обращайте внимания на мою болтовню... Любознательный наш Мигель, это да... Навестил меня, удовлетворил свое любопытство - и снова исчез. Вот только как три дня назад тому мы с ним беседовали.";
        link.l1 = "А сейчас Мигель где? Не подскажете?";
        link.l1.go = "tieyasal_2";
        break;

    case "tieyasal_2":
        dialog.text = "А кто же его знает. Может в Шарптауне дела справляет, а может уже и отбыл с Исла Тесоро.";
        link.l1 = "Ясно. Спасибо, мастер!";
        link.l1.go = "tieyasal_3";
        break;

    case "tieyasal_3":
        DialogExit();
        npchar.quest.tieyasal = "true";
        break;

    // Калеуче
    case "FDM":
        dialog.text = "А-а, 'корабль-призрак'! Вашим галеоном матери пугают непослушных детей. Нет чтобы затопить эту чертову посудину - далась она вам! Моряков в дрожь бросает, когда они видят ваше судно на горизонте... Так что вы хотите с ним сделать?";
        if (!CheckAttribute(npchar, "quest.FDM_cabin"))
        {
            link.l1 = "То, что от его внешнего вида трусливые мозгляки в штаны себе накладывают - это меня как раз устраивает. А вот внутреннее убранство каюты меня огорчает - там не убирались полвека, все покрылось плесенью и протухло. На кровати спать жутко - словно в гроб укладываешься. Хочу обстановку полностью обновить - труху и гниль выбросить, всё свежее поставить. Возьметесь, мастер?";
            link.l1.go = "FDM_cabin";
        }
        if (!CheckAttribute(npchar, "quest.FDM_sails"))
        {
            link.l2 = "Надоела эта древняя рванина, что болтается у меня вместо парусов. Ветер она ловит не хуже обычных полотнищ, но вид - просто омерзительный. Хочу нормальные белые паруса, как на всех кораблях. Сделаем, мастер?";
            link.l2.go = "FDM_sails";
        }
        break;

    case "FDM_cabin":
        dialog.text = "Отчего же не взяться? Возьмусь, конечно, чай, не безрукий. Галеон у вас огромный, так что могу даже перестроить его внутреннее обиталище по образу кают линейных кораблей. Или оставим стандартную каюту. Что выбираете?";
        link.l1 = "Давайте сделаем каюту, как на линейных кораблях! Чтобы все от зависти лопнули...";
        link.l1.go = "FDM_cabin_m";
        link.l2 = "Не вижу смысла в излишествах. Делаем стандартную.";
        link.l2.go = "FDM_cabin_s";
        break;

    case "FDM_cabin_m":
        dialog.text = "Очень хорошо. Тащите десять сундучков с дублонами - и за пять дней всё будет готово.";
        link.l1 = "Договорились.";
        link.l1.go = "FDM_cabin_m1";
        link.l2 = "Десять сундучков? Полторы тысячи дублонов? Кхм, я, пожалуй, еще подумаю, стоит ли эта каюта таких расходов...";
        link.l2.go = "exit";
        break;

    case "FDM_cabin_s":
        dialog.text = "Очень хорошо. Тащите семь сундучков с дублонами - и за пять дней всё будет готово.";
        link.l1 = "Договорились.";
        link.l1.go = "FDM_cabin_s1";
        link.l2 = "Семь сундучков? Больше тысячи дублонов? Кхм, я, пожалуй, еще подумаю, стоит ли эта каюта таких расходов...";
        link.l2.go = "exit";
        break;

    case "FDM_cabin_m1":
        iTemp = GetCharacterItem(pchar, "Chest");
        npchar.quest.FDM_cabin = 10;
        npchar.quest.FDM_cabin.type = "Cabin_Huge";
        dialog.text = "Вот и славно. Жду оплаты.";
        if (iTemp > 0)
        {
            link.l1 = "У меня есть с собой сундучки... Так, посмотрим... Вот, " + FindRussianQtyString(iTemp) + ".";
            link.l1.go = "FDM_cabin_pay";
        }
        else
        {
            link.l1 = "Пойду складывать дублоны в сундучки.";
            link.l1.go = "FDM_cabin_wait";
        }
        break;

    case "FDM_cabin_s1":
        iTemp = GetCharacterItem(pchar, "Chest");
        npchar.quest.FDM_cabin = 7;
        npchar.quest.FDM_cabin.type = "Cabin";
        dialog.text = "Вот и славно. Жду оплаты.";
        if (iTemp > 0)
        {
            link.l1 = "У меня есть с собой сундучки... Так, посмотрим... Вот, " + FindRussianQtyString(iTemp) + ".";
            link.l1.go = "FDM_cabin_pay";
        }
        else
        {
            link.l1 = "Пойду складывать дублоны в сундучки.";
            link.l1.go = "FDM_cabin_wait";
        }
        break;

    case "FDM_cabin_wait":
        DialogExit();
        npchar.quest.FDM_full = "cabin";
        break;

    case "FDM_cabin_pay":
        iTemp = GetCharacterItem(pchar, "Chest");
        amount = sti(npchar.quest.FDM_cabin) - iTemp;
        Log_Info("Вы передали мастеру Алексусу сундуки");
        PlaySound("interface\important_item.wav");
        if (amount <= 0) // всё принес
        {
            RemoveItems(pchar, "chest", sti(npchar.quest.FDM_cabin));
            dialog.text = "Так, вам нужно было принести сундучков - " + FindRussianQtyString(sti(npchar.quest.FDM_cabin)) + ", вы принесли - " + FindRussianQtyString(iTemp) + ". Итак, вопрос с оплатой мы закрыли. Теперь я приступаю к работе. А вы пока погуляйте и не беспокойтесь - всё будет сделано в лучшем виде.";
            link.l1 = "Хорошо...";
            link.l1.go = "FDM_cabin_do";
        }
        else
        {
            RemoveItems(pchar, "chest", iTemp);
            dialog.text = "Так, вам нужно было принести сундучков - " + FindRussianQtyString(sti(npchar.quest.FDM_cabin)) + ", вы принесли - " + FindRussianQtyString(iTemp) + ". Значит, вам осталось донести еще " + FindRussianQtyString(amount) + ".";
            link.l1 = "Хорошо, мастер.";
            link.l1.go = "FDM_cabin_wait";
            npchar.quest.FDM_cabin = amount;
        }
        break;

    case "FDM_cabin_do":
        DialogExit();
        SetLaunchFrameFormParam("Прошло 5 дней..." + NewStr() + "Мастер Алексус выполнил работу", "", 0, 5);
        WaitDate("", 0, 0, 5, 0, 10); //крутим время
        LaunchFrameForm();
        RefreshLandTime();
        RecalculateJumpTable();
        Whr_UpdateWeather();
        shTo = &RealShips[sti(Pchar.Ship.Type)];
        shTo.CabinType = npchar.quest.FDM_cabin.type;
        if (CheckAttribute(npchar, "quest.FDM_sails"))
            npchar.quest.FDM_full = "done";
        else
            DeleteAttribute(npchar, "quest.FDM_full");
        break;

    case "FDM_sails":
        dialog.text = "Сделаем, отчего же не сделать! Так-так... Это значит, нам надо полностью заменить все паруса - выбросить старье, поставить хлопковые, чистенькие и свеженькие. Площадь парусов у вас немаленькая, так что за материалы и за работу я попрошу сто тысяч песо. Устраивает?";
        if (sti(Pchar.money) >= 100000)
        {
            link.l1 = "Какие могут быть вопросы? Конечно, устраивает!";
            link.l1.go = "FDM_sails_do";
        }
        link.l2 = "Хм. Пожалуй, мне надо еще подумать...";
        link.l2.go = "exit";
        break;

    case "FDM_sails_do":
        AddMoneyToCharacter(pchar, -100000);
        dialog.text = "Вот и славно. Денежки вы заплатили - теперь я приступаю к работе. А вы пока погуляйте пару денечков и не беспокойтесь - всё будет сделано в лучшем виде.";
        link.l1 = "Хорошо...";
        link.l1.go = "FDM_sails_done";
        break;

    case "FDM_sails_done":
        DialogExit();
        SetLaunchFrameFormParam("Прошло 2 дня..." + NewStr() + "Мастер Алексус выполнил работу", "", 0, 5);
        WaitDate("", 0, 0, 2, 0, 10); //крутим время
        LaunchFrameForm();
        RefreshLandTime();
        RecalculateJumpTable();
        Whr_UpdateWeather();
        SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
        SetSailsColor(pchar, 0); //белый хлопковый парус
        npchar.quest.FDM_sails = "true";
        if (CheckAttribute(npchar, "quest.FDM_cabin"))
            npchar.quest.FDM_full = "done";
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

void checkMatherial_repair(ref Pchar, ref NPChar, int good, int goodType)
{
    int amount;
    string Matherial = "Matherial" + goodType;
    amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Repair.(Matherial));

    if (amount < 0)
    {
        amount = amount + sti(NPChar.Repair.(Matherial));
    }
    else
    {
        amount = sti(NPChar.Repair.(Matherial));
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Repair.(Matherial) = sti(NPChar.Repair.(Matherial)) - amount;
}

int GetMaterialQtyRepair(ref _chr, int MaterialNum)
{
    if (sti(_chr.Ship.Type) == SHIP_NOTUSED)
        return 0;

    int shipCurHP = sti(RealShips[sti(_chr.Ship.Type)].HP);
    int shipBaseHP = sti(RealShips[sti(_chr.Ship.Type)].BaseHP);
    int shipClass = sti(RealShips[sti(_chr.Ship.Type)].Class);
    int shipWeight = CWT2Tonnes(sti(RealShips[sti(_chr.Ship.Type)].Weight));
    int HPPrice = shipWeight * (1.2 - makefloat(shipCurHP) / makefloat(shipBaseHP));
    int modifier = (2 * MOD_SKILL_ENEMY_RATE) + sti(RealShips[sti(_chr.Ship.Type)].MinCrew) / 2 + 1;

    float fQuest = 1.0;
    if (CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip"))
    {
        fQuest = 1.3;
        HPPrice = HPPrice * 2;
    }

    int Matherial1 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (6 - shipClass) / 2) + rand(modifier);
    int Matherial2 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (6 - shipClass) / 2) + rand(modifier);
    int Matherial3 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (6 - shipClass) / 2) + rand(modifier);
    int Matherial4 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (6 - shipClass) / 2) + rand(modifier);

    if (MaterialNum == 0)
        return HPPrice;
    if (MaterialNum == 1)
        return Matherial1;
    if (MaterialNum == 2)
        return Matherial2;
    if (MaterialNum == 3)
        return Matherial3;
    if (MaterialNum == 4)
        return Matherial4;

    return 0;
}
