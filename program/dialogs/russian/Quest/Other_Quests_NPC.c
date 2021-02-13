void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag;
    string sTemp;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
    case "First time":
        dialog.text = "Что вам надо?";
        link.l1 = "Ничего.";
        link.l1.go = "exit";
        NextDiag.TempNode = "First time";
        break;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////----------------------------------------- работорговец -----------------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //--> пинас
    case "TakeShoreCap":
        dialog.text = "Ах ты каналья! Не ожидал" + GetSexPhrase("", "а") + "?";
        link.l1 = "Не ожидал" + GetSexPhrase("", "а") + " чего?";
        link.l1.go = "Node_1";
        break;

    case "Node_1":
        dialog.text = "Ха-ха! Рабов здесь нет! Ты ведь за ними явил" + GetSexPhrase("ся", "ась") + "?";
        link.l1 = "Ах ты... А я и думаю, откуда на торговом пинасе солдаты, да еще так много... Ловушка!!";
        link.l1.go = "Node_2";
        break;

    case "Node_2":
        dialog.text = "Да, мерзав" + GetSexPhrase("ец", "ка") + ", это ловушка. А я не торговец, а боевой офицер! И хотя бой ты выиграл" + GetSexPhrase("", "а") + ", тебе все равно не уйти от правосудия.";
        link.l1 = "Это почему же? Сейчас покончу с тобой, пущу твое корыто на дно - и никто ничего не узнает.";
        link.l1.go = "Node_3";
        break;

    case "Node_3":
        dialog.text = "Ошибаешься. Ваши темные делишки с местным ростовщиком раскрыты. Скоро об этом узнает генерал-губернатор, и вам не отвертеться от виселицы. Ну а я уж постараюсь, чтобы ты до нее не дожил" + GetSexPhrase("", "а") + ".";
        link.l1 = "Попробуй, ищейка губернаторская!";
        link.l1.go = "Node_4";
        break;

    case "Node_4":
        pchar.questTemp.Slavetrader = "TakeShoreCap_end"; //это состояние квеста для проверки у квестодателя
        AddQuestRecord("Slavetrader", "13");
        AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
        pchar.quest.Slavetrader_DieHard.over = "yes";
        pchar.quest.Slavetrader_AfterBattle.over = "yes";
        pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
        Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
        LAi_SetCurHPMax(NPChar);
        LAi_GetCharacterMaxEnergy(NPChar);
        QuestAboardCabinDialogExitWithBattle("");
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");

        break;

    case "Slave_arest":
        dialog.text = "" + GetFullName(pchar) + ", именем закона вы арестованы! Немедленно сдайте оружие и следуйте за нами!";
        link.l1 = "Что это значит, офицер? На каком основании?";
        link.l1.go = "Slave_arest_1";
        break;

    case "Slave_arest_1":
        dialog.text = "Не прикидывайтесь овечкой, капитан! Ваши грязные делишки раскрыты. А за резню, что вы учинили, и за потопленный корабль " + NationNameGenitive(sti(npchar.nation)) + ", вы будете болтаться на ноке рея!";
        link.l1 = "Ну раз так... то мне терять уже нечего, не так ли? Держитесь, псы!";
        link.l1.go = "Slave_arest_2";
        break;

    case "Slave_arest_2":
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
        LAi_SetWarriorTypeNoGroup(npchar);
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
        LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

    //--> крыса в доме
    case "Rat_bandos":
        dialog.text = "Эй! Что ты тут забыл" + GetSexPhrase("", "а") + "? Давай, вали отсюда!";
        link.l1 = "Что-то ты не очень любезен, милейший. Не здесь ли прячется эта крыса Гонтьер, а?";
        link.l1.go = "Node_rat_1";
        break;

    case "Node_rat_1":
        dialog.text = "Нет здесь никакого Гонтьера! Если это все, что ты хотел" + GetSexPhrase("", "а") + " узнать - убирайся!";
        link.l1 = "Сдается мне, что ты лжешь. Сейчас мы обыщем дом и посмотрим...";
        link.l1.go = "Node_rat_2";
        break;

    case "Node_rat_2":
        dialog.text = "А-ать! Франсуа! Беги! Ребята, ко мне, на помощь!";
        link.l1 = "Ах ты пес!";
        link.l1.go = "Node_rat_3";
        break;

    case "Node_rat_3":
        LAi_SetPlayerType(pchar);
        LAi_SetWarriorType(npchar);
        LAi_group_MoveCharacter(npchar, "EnemyFight");
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat1");
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

    case "Rat_lover":
        dialog.text = "Ай! Не трогайте меня!";
        link.l1 = "Где Франсуа Гонтьер? Отвечай, маленькая дрянь, или последуешь за своими дружками!";
        link.l1.go = "Rat_lover_1";
        break;

    case "Rat_lover_1":
        dialog.text = "Нет, нет, я все скажу! Он выпрыгнул в окно и убежал, видимо, на свой корабль.";
        link.l1 = "Какой корабль? В порту нет его корабля, я это знаю. Не лги мне, милочка, хуже будет...";
        link.l1.go = "Rat_lover_2";
        break;

    case "Rat_lover_2":
        dialog.text = "Я не лгу, клянусь! Он говорил, что пришвартовался у маленького островка, на котором маяк, а до города добрался на шлюпке... Он там! Не трогайте меня!";
        link.l1 = "Ладно, похоже ты не врешь. Сиди тихо и не дергайся. А вообще, знакомых надо с умом выбирать. Хотя, какой у тебя ум - по глазам вижу, дура-дурой.";
        link.l1.go = "Rat_lover_3";
        pchar.quest.Slavetrader_RatAttack.win_condition.l1 = "location";
        pchar.quest.Slavetrader_RatAttack.win_condition.l1.location = "Tortuga"; //отправляем в локацию
        pchar.quest.Slavetrader_RatAttack.function = "Slavetrader_RatCorvette";  //создание корвета
        SetFunctionTimerCondition("Slavetrader_RatCorvetteOver", 0, 0, 1, false);
        break;

    case "Rat_lover_3":
        LAi_SetPlayerType(pchar);
        SetCharacterRemovable(npchar, false);
        LAi_SetActorType(npchar);
        npchar.lifeday = 0;
        AddQuestRecord("Slavetrader", "21_9");
        DialogExit();
        break;

    //--> беглые рабы
    case "Slave_woman":
        dialog.text = "Пощадите! Пощадите! Мы сдаемся!";
        link.l1 = "Вот как? А ну, все живо марш на корабль в трюмы! Кто сделает неловкое движение - пристрелю на месте!";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("Slavetrader_Slavewoman");
        break;
        //<--работорговец

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////----------------------------------------- Генераторы -----------------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //--> Jason ------------------------ Сомнительное предложение -------------------------------------------
        int iCGood;
    case "Contraoffer_patrol":
        chrDisableReloadToLocation = false;
        iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
        pchar.GenQuest.Contraoffer.Trader.PatrolSumm = sti(pchar.GenQuest.Contraoffer.Trader.Summ) / 3;
        dialog.text = "Так-так... Вот вы оба и попались, голубчики. Разве вы не в курсе, что оборот " + GetGoodsNameAlt(iCGood) + " частными лицами в нашей колонии запрещен? Как все это понимать?";
        link.l1 = "Офицер, разве запрещен? Я впервые об этом слышу, честное слово. Это постановление приняли недавно, наверное?";
        link.l1.go = "Contraoffer_patrol_1";
        link.l2 = "Какой оборот " + GetGoodsNameAlt(iCGood) + "? Я не вижу " + GetGoodsNameAlt(iCGood) + ", офицер! Я вижу только вот эти блестящие монеты... И он видит только блестящие монеты. Может, вы и ваши солдаты тоже посмотрите на наши монеты? А " + GetGoodsNameAlt(iCGood) + " у нас нет...";
        link.l2.go = "Contraoffer_patrol_pay1";
        break;

    case "Contraoffer_patrol_1":
        if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > drand(120))
        {
            dialog.text = "Вы были не в курсе? Хм... похоже, вы не лжете. Но тем не менее, это так, и своими действиями вы нарушили закон. Я не буду арестовывать вас, но оштрафовать все-таки придется. Ну, а что делать с грузом - это будем решать со вторым участником сделки.";
            link.l1 = "И каков размер штрафа?";
            link.l1.go = "Contraoffer_patrol_pay2";
        }
        else
        {
            dialog.text = "Не мелите чепухи, капитан! Это известно всем и давно. Я арестую вас обоих за контрабанду, а товар будет конфискован.";
            link.l1 = "Офицер, я не привычен к казематам. Я люблю море... и сейчас намерен в него выйти. Но, вероятно, это придется сделать через ваш труп.";
            link.l1.go = "Contraoffer_patrol_fight";
            link.l2 = "Мне ничего не остается, как подчиниться. Но я правда не знал!";
            link.l2.go = "Contraoffer_patrol_jail";
        }
        break;

    case "Contraoffer_patrol_pay1":
        iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
        if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) > drand(120))
        {
            dialog.text = "Вот как... Ну что же, давайте посмотрим на ваши монеты... Тут прозвучала сумма в " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)) + ". Поскольку у нас теперь не двухсторонний, а трехсторонний договор, то я бы хотел увидеть " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm)) + ". Это с вас. Столько же и от второго участника сделки.";
            link.l1 = "Конечно, офицер. Вот мои блестящие монеты... А " + GetGoodsNameAlt(iCGood) + " тут нет, хе-хе, я же говорил.";
            link.l1.go = "Contraoffer_patrol_complete1";
            link.l2 = "Ого! У вас неумеренные аппетиты, офицер. Вы никогда не слышали поговорки 'большая ложка рот дерет'? Пожалуй, дешевле будет познакомить вас и ваших подчиненных с моей саблей.";
            link.l2.go = "Contraoffer_patrol_fight";
        }
        else
        {
            dialog.text = "Вы издеваетесь, капитан? Или пытаетесь предложить мне взятку? Вы арестованы! Взять его!";
            link.l1 = "Ну, раз на деньги вы смотреть не хотите, тогда взглянете на острие моей сабли!";
            link.l1.go = "Contraoffer_patrol_fight";
            link.l2 = "Мне ничего не остается сделать, как подчиниться. Но я же не знал...";
            link.l2.go = "Contraoffer_patrol_jail";
        }
        break;

    case "Contraoffer_patrol_complete1":
        dialog.text = "Да, действительно, вы правы... Кроме монет, я тут и впрямь ничего не вижу. Вы свободны, капитан, ступайте, а мы потолкуем с вашим партнером.";
        link.l1 = "Всего доброго, офицер. Не обижайте моего коллегу.";
        link.l1.go = "Contraoffer_patrol_complete";
        break;

    case "Contraoffer_patrol_pay2":
        dialog.text = "" + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm)) + ". И только потому, что я сегодня добрый.";
        link.l1 = "Спасибо, офицер. Я правда не знал... Вот, я готов оплатить штраф.";
        link.l1.go = "Contraoffer_patrol_complete2";
        link.l2 = "Сдается мне, офицер, что вы нечисты на руку. Уж больно велик назначенный вами штраф. Думаю, что эта колония только выиграет, если я избавлю ее от вашего присутствия.";
        link.l2.go = "Contraoffer_patrol_fight";
        break;

    case "Contraoffer_patrol_complete2":
        dialog.text = "Хорошо. Теперь можете идти. И прежде чем торговать, советую ознакомится со списком запрещенных к ввозу товаров, чтобы избежать повторения сегодняшней ситуации. Ступайте, теперь нам нужно заняться вторым участником сделки - он-то точно был в курсе, чем можно торговать, а чем нельзя.";
        link.l1 = "Всего доброго, офицер.";
        link.l1.go = "Contraoffer_patrol_complete";
        break;

    case "Contraoffer_patrol_complete":
        AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm));
        AddQuestRecord("Contraoffer", "6");
        CloseQuestHeader("Contraoffer");
        LAi_CharacterDisableDialog(npchar);
        DialogExit();
        break;

    case "Contraoffer_patrol_fight":
        AddQuestRecord("Contraoffer", "7");
        CloseQuestHeader("Contraoffer");
        ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -5);
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
        LAi_SetWarriorTypeNoGroup(npchar);
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
        LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

    case "Contraoffer_patrol_jail":
        dialog.text = "Комендант разберется, что вы знали, а чего не знали. Следуйте за мной!";
        link.l1 = "...";
        link.l1.go = "Contraoffer_patrol_jail_exit";
        break;

    case "Contraoffer_patrol_jail_exit":
        GoToPrison(pchar.GenQuest.Contraoffer.Trader.City, sti(pchar.GenQuest.Contraoffer.Trader.Summ), 7);
        DialogExit();
        AddQuestRecord("Contraoffer", "8");
        CloseQuestHeader("Contraoffer");
        pchar.GenQuest.Contraoffer.Jail = "true";
        break;
        //<-- Сомнительное предложение

        //Jason --> ----------------------------------- Неудачливый вор --------------------------------------------
    case "Device_poorman":
        dialog.text = "Добрый день. Вы что-то хотели?";
        link.l1 = "Да, приятель. Сдается, что ты и есть тот, кто мне нужен. Ведь это ты украл на местной верфи " + pchar.GenQuest.Device.Shipyarder.Type + "? Все улики ведут к тебе, так что не отпирайся.";
        link.l1.go = "Device_poorman_1";
        break;

    case "Device_poorman_1":
        switch (sti(pchar.GenQuest.Device.Shipyarder.Chance3))
        {
        case 0: //выбросил
            if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) != 1)
            {
                dialog.text = "Помилуйте, господин! Да, я стащил на верфи эту странную железку. Но я даже не смог ее никому продать - никому она оказалась не нужна. Я ее и выбросил. Пощадите, сударь, я просто очень хотел кушать... так бы я никогда не решился на кражу!";
                link.l1 = "Вот незадача... Да ты-то сам мне не нужен. Мне нужно найти " + pchar.GenQuest.Device.Shipyarder.Type + ". Говори, где выбросил?";
                link.l1.go = "Device_poorman_0_1";
            }
            else //просто отдаст
            {
                dialog.text = "Помилуйте, господин! Да, я стащил на верфи эту странную железку. Но я даже не смог ее никому продать - никому она оказалась не нужна. Я отдам ее вам. Вот, берите, только не трогайте меня и не сдавайте солдатам!";
                link.l1 = "Ладно, живи, воришка. Ты мне не нужен, мне нужен этот инструмент. Живо давай его сюда, а потом можешь проваливать на все четыре сторны!";
                link.l1.go = "Device_poorman_0_2";
            }
            break;
        case 1: //упирается, хитрый или храбрый
            dialog.text = "О чем вы говорите? Что за " + pchar.GenQuest.Device.Shipyarder.Type + "? Не понимаю!";
            link.l1 = "Вот сейчас обыщу тебя, тогда поймешь, о чем я говорю! Отдай лучше подобру-поздорову!";
            link.l1.go = "Device_poorman_1_1";
            break;
        case 2: //трусливый
            dialog.text = "Ой... Что за " + pchar.GenQuest.Device.Shipyarder.Type + "? Я... а что это вообще такое?";
            link.l1 = "Не прикидывайся дурачком и не пытайся дать тягу, все равно догоню. А сейчас мы проведем небольшой обыск...";
            link.l1.go = "Device_poorman_2_1";
            break;
        }
        break;

    case "Device_poorman_0_1": //идем на поиски
        dialog.text = "Да сразу за городскими воротами, у выхода в джунгли. Помилуйте, великодушный господин! Если она вам так нужна - забирайте ее, она там так и валяется, я уверен.";
        link.l1 = "Надо было бы заставить тебя самого пойти разыскать и принести, да боюсь, дольше потом тебя искать придется, чем " + pchar.GenQuest.Device.Shipyarder.Type + ". Сам найду. Но смотри: если солгал - из под земли достану!";
        link.l1.go = "exit";
        AddQuestRecord("Device", "3");
        string sCity = pchar.GenQuest.Device.Shipyarder.City + "_ExitTown";
        ref rItm = ItemsFromID("Tool");
        rItm.shown = true;
        rItm.startLocation = sCity;
        rItm.startLocator = "item" + (rand(14) + 1);
        Log_TestInfo("Девайс в локаторе " + rItm.startLocator);
        npchar.lifeday = 0;
        LAi_CharacterDisableDialog(npchar);
        break;

    case "Device_poorman_0_2": //получили девайс
        dialog.text = "Вот, забирайте. Спасибо, великодушный господин!";
        link.l1 = "Так, вроде оно, хе-хе. Всё, свободен! Гуляй. Да смотри в следующий раз, что стащить собираешься.";
        link.l1.go = "exit";
        TakeNItems(pchar, "Tool", 1);
        Log_Info("Вы получили украденный инструмент");
        PlaySound("interface\important_item.wav");
        AddQuestRecord("Device", "4");
        npchar.lifeday = 0;
        LAi_CharacterDisableDialog(npchar);
        break;

    case "Device_poorman_1_1":
        pchar.GenQuest.Device.Shipyarder.Poorsumm = 1000 + drand(1000);
        dialog.text = "Послушайте, вы случайно не об этом инструменте речь ведете? Если об этом, то это моя вещь, и я ее не крал! И отдавать вам ее просто так вот не намерен! Если хотите ее получить - заплатите мне " + FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)) + ".";
        link.l1 = "Хм... Хорошо. Я заплачу тебе. Вот деньги, и давай сюда " + pchar.GenQuest.Device.Shipyarder.Type + "!";
        link.l1.go = "Device_poorman_1_2";
        link.l2 = "Вот как? Ты что же, жалкий воришка, думаешь, я тебе поверил? А ну, давай сюда " + pchar.GenQuest.Device.Shipyarder.Type + ", живо, не то стражу позову - и мы все вместе сходим на верфь и разберемся, чей это инструмент на самом деле.";
        link.l2.go = "Device_poorman_1_3";
        link.l3 = "Ну и наглость! Вот что, мерзавец: или ты немедленно отдашь мне " + pchar.GenQuest.Device.Shipyarder.Type + ", или я проткну тебя своей шпагой и заберу инструмент с твоего трупа!";
        link.l3.go = "Device_poorman_1_4";
        break;

    case "Device_poorman_1_2":
        dialog.text = "Отличная сделка, капитан! Я думаю, мы оба в накладе не останемся, хе-хе... Забирайте.";
        link.l1 = "Меньше болтай языком, воришка! Не думай, что я тебе поверил, просто шум лишний поднимать неохота. Да и все равно тебе эти деньги во благо не пойдут. Всё, проваливай!";
        link.l1.go = "exit";
        AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Device.Shipyarder.Poorsumm));
        TakeNItems(pchar, "Tool", 1);
        Log_Info("Вы получили украденный инструмент");
        PlaySound("interface\important_item.wav");
        AddQuestRecord("Device", "5");
        AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)));
        AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
        npchar.lifeday = 0;
        LAi_CharacterDisableDialog(npchar);
        break;

    case "Device_poorman_1_3":
        if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0) //если мы в городе
        {
            dialog.text = "Нет! Не надо стражи! Я... я отдам вам этот проклятый инструмент. Вот, забирайте!";
            link.l1 = "Так-то лучше! А теперь можешь проваливать. Все равно дорога тебе одна - на виселицу, это лишь вопрос времени.";
            link.l1.go = "exit_device";
        }
        else //храбрый попался
        {
            dialog.text = "Капитан, какая стража? Тут только мы с вами. Ну, а раз вы так взъерепенились, то мне не остается ничего иного, как немножко вас успокоть... сталью моего клинка.";
            link.l1 = "Ты смеешь мне угрожать, мразь?";
            link.l1.go = "Device_poorman_fight";
        }
        break;

    case "Device_poorman_1_4":
        if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0) //если мы в городе
        {
            dialog.text = "Ай! Спасите! Убивают!";
            link.l1 = "Стой, собака!";
            link.l1.go = "exit";
            sld = characterFromId("Device_poorman");
            LAi_SetActorType(sld);
            LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
            sld.lifeday = 0;
            AddQuestRecord("Device", "7");
            CloseQuestHeader("Device");
            DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
        }
        else //храбрый попался
        {
            dialog.text = "Ну, капитан, это мы еще посмотрим, кто кого проткнет!";
            link.l1 = "Ты смеешь мне угрожать, мразь?";
            link.l1.go = "Device_poorman_fight";
        }
        break;

    case "Device_poorman_2_1":
        dialog.text = "Какой еще такой обыск? Помилуйте, благородный господин!";
        link.l1 = "Значит так: или ты мне сейчас добровольно отдаешь то, что украл с верфи, или я отведу тебя в комендатуру. Там ты все равно с этой вещью расстанешься, правда, после легкого прижигания пяток каленым железом. А может, еще и вздернут потом. Так что выбирай.";
        link.l1.go = "Device_poorman_2_2";
        link.l2 = "Живо гони сюда украденное, подонок, или я прикончу тебя на месте!";
        link.l2.go = "Device_poorman_2_3";
        break;

    case "Device_poorman_2_2":
        if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 2) //тут уж как повезет
        {
            dialog.text = "Ну, чтобы отвести меня в комендатуру, надо сначала догнать...";
            link.l1 = "Стой, собака!";
            link.l1.go = "exit";
            AddQuestRecord("Device", "7");
            sld = characterFromId("Device_poorman");
            LAi_SetActorType(sld);
            LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
            sld.lifeday = 0;
            CloseQuestHeader("Device");
            DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
        }
        else
        {
            dialog.text = "Не надо в комендатуру! Я сам отдам. Вот, держите, вы, наверно, это ищете. Все равно ее никому не продать...";
            link.l1 = "Эх, отвести бы тебя, висельника, в форт и сдать властям... Ладно, давай сюда инструмент и проваливай!";
            link.l1.go = "exit_device";
        }
        break;

    case "Device_poorman_2_3": //напугали
        dialog.text = "Ай! Не трогайте меня, я все отдам! Вот, забирайте!";
        link.l1 = "То-то же! Ступай, и если я тебя еще хоть раз увижу в этом городе - сдам коменданту. Проваливай!";
        link.l1.go = "exit_device";
        break;

    case "exit_device":
        npchar.lifeday = 0;
        TakeNItems(pchar, "Tool", 1);
        Log_Info("Вы получили украденный инструмент");
        PlaySound("interface\important_item.wav");
        AddQuestRecord("Device", "6");
        DialogExit();
        LAi_CharacterDisableDialog(npchar);
        break;

    case "Device_poorman_fight":
        chrDisableReloadToLocation = true;
        sld = characterFromId("Device_poorman");
        TakeNItems(sld, "Tool", 1);
        sld.SaveItemsForDead = true; // сохранять на трупе вещи
        sld.DontClearDead = true;    // не убирать труп через 200с
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        AddQuestRecord("Device", "8");
        AddComplexSelfExpToScill(30, 30, 30, 50);
        break;
        //<-- Неудачливый вор
        //-------------------------------------------почтовый генератор 2 уровня------------------------------------
    case "PostGopHunters":
        dialog.text = "Стой, приятель! Нам нужна вещь, которая сейчас у тебя. Отдай ее нам по добру, и ступай своей дорогой.";
        link.l1 = "Какая такая вещь? Не понимаю...";
        link.l1.go = "PostGopHunters_1";
        link.l2 = "Совсем обнаглели бродяги безродные... Ну, держитесь, подонки!";
        link.l2.go = "PostHunters_fight";
        break;

    case "PostGopHunters_1":
        dialog.text = "Не прикидывайся дурачком! Гони сюда пакет, и останешься цел. А иначе... мы снимем его с твоего трупа!";
        link.l1 = "Сила не на моей стороне... забирайте, ублюдки, у меня нет выхода.";
        link.l1.go = "PostGopHunters_2";
        link.l2 = "Попробуй, мразь трущобная!";
        link.l2.go = "PostHunters_fight";
        break;

    case "PostGopHunters_2":
        dialog.text = "Полегче с выражениями, приятель... Молодец, что не стал испытывать судьбу. Исход-то все равно был бы один, ха-ха! А так поживешь еще... Ну, бывай.";
        link.l1 = "...";
        link.l1.go = "exit_gophunter";
        break;

    case "PostProfHunters":
        dialog.text = "Постойте, " + GetAddress_Form(NPChar) + ", не спешите. У нас к вам дело.";
        link.l1 = "Какое дело? Мы, кажется, с вами не знакомы.";
        link.l1.go = "PostProfHunters_1";
        break;

    case "PostProfHunters_1":
        dialog.text = "Считайте, капитан, что уже познакомились. Теперь по сути. Вы сейчас получили в портовом управлении " + pchar.questTemp.WPU.Current.Add + " " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.City + "Gen") + ". Не пытайтесь отрицать, нам это достоверно известно - мы уже несколько дней ведем поиск этого документа.";
        link.l1 = "Теперь ясно. И что?";
        link.l1.go = "PostProfHunters_2";
        break;

    case "PostProfHunters_2":
        dialog.text = "Сейчас вы отдадите нам этот пакет и наше кратковременое знакомство завершится. И не пытайтесь геройствовать, кэп: мы намерены получить эти бумаги, даже если для этого потребуется драться с городским гарнизоном\nКак вы понимаете, в случае драки вы умрете первым. Так что отдайте документы и расстанемся друзьями.";
        link.l1 = "Сила не на моей стороне... забирайте, проклятые, у меня нет выхода.";
        link.l1.go = "PostProfHunters_3";
        link.l2 = "Вам не запугать меня - и не таких крутых в море видали! Ничего вы не получите.";
        link.l2.go = "PostProfHunters_4";
        break;

    case "PostProfHunters_3":
        dialog.text = "Я рад, что вы приняли разумное решение, капитан. Вы подвергли себя большой опасности, взявшись за это дело. Ну а теперь разрешите откланяться.";
        link.l1 = "...";
        link.l1.go = "exit_profhunter";
        break;

    case "PostProfHunters_4":
        dialog.text = "Ну, ты сам выбрал свою судьбу...";
        link.l1 = "...";
        link.l1.go = "PostHunters_fight";
        TraderHunterOnMap(); //если деремся - запускаем ДУ вдогонку
        break;

    case "PostHunters_fight":
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

    case "exit_gophunter":
        chrDisableReloadToLocation = false;
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
        RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
        for (i = 1; i <= 4; i++)
        {
            sld = characterFromId("PostHunters" + i);
            LAi_SetActorType(sld);
            LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
        }
        AddQuestRecord("Postcureer", "11");
        DialogExit();
        break;

    case "exit_profhunter":
        chrDisableReloadToLocation = false;
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
        RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
        for (i = 1; i <= 2; i++)
        {
            sld = characterFromId("PostHunters" + i);
            LAi_SetActorType(sld);
            LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
        }
        AddQuestRecord("Postcureer", "12");
        pchar.questTemp.WPU.Postcureer.fail = "true";
        DialogExit();
        break;

    case "PostAgent":
        bDisableFastReload = true;
        dialog.text = "Постойте, " + GetAddress_Form(NPChar) + ", не спешите. У меня к вам дело.";
        link.l1 = "Какое дело? Говорите быстрее, я спешу.";
        link.l1.go = "PostAgent_1";
        break;

    case "PostAgent_1":
        dialog.text = "То, что вы спешите - мне известно. А еще мне известно, что вы сейчас получили в портовом управлении " + pchar.questTemp.WPU.Current.Add + " " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.City + "Gen") + ". Вот об этих бумагах я и хочу с вами поговорить.";
        link.l1 = "А вот у меня нет желания обсуждать с незнакомыми людьми эту тему. Или вы желаете присвоить эти бумаги? Если вы только попытаетесь...";
        link.l1.go = "PostAgent_2";
        break;

    case "PostAgent_2":
        dialog.text = "Полноте, капитан! Я что, похож на банального грабителя с большой дороги? Я деловой человек, и представляю интересы " + NationNameGenitive(sti(pchar.questTemp.WPU.Postcureer.EnemyNation)) + ". Я хочу предложить вам весьма выгодную сделку - но только не здесь. Давайте пройдем в комнату таверны, и с глазу на глаз, в спокойной обстановке все обсудим. Это не займет много времени.";
        link.l1 = "Подозрительно всё это... Я не намерен иметь никаких дел с вами, сударь! Убирайтесь!";
        link.l1.go = "PostAgent_getout";
        link.l2 = "Хм... Ну, давайте посмотрим, что вы сможете мне предложить. Но даже и не пытайтесь напасть на меня. Пойдемте, я после вас.";
        link.l2.go = "PostAgent_3";
        break;

    case "PostAgent_getout":
        dialog.text = "Вы упрямый и тупой человек, капитан! Я предложил вам заработать, не пошевелив и пальцем. А вы... вы еще пожалеете об этом.";
        link.l1 = "Убирайтесь!!";
        link.l1.go = "PostAgent_getout_exit";
        break;

    case "PostAgent_3":
        dialog.text = "Замечательно! Следуйте за мной.";
        link.l1 = "...";
        link.l1.go = "exit";
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
        NextDiag.TempNode = "PostAgent_inTavern";
        sld = characterFromId("PostAgent");
        LAi_SetActorType(sld);
        LAi_ActorRunToLocation(sld, "reload", "reload4_back", pchar.questTemp.WPU.Postcureer.StartCity + "_tavern_upstairs", "goto", "goto1", "PostAgent_inTavern_Room", -1);
        break;

    case "PostAgent_getout_exit":
        bDisableFastReload = false;
        chrDisableReloadToLocation = false;
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
        sld = characterFromId("PostAgent");
        LAi_SetActorType(sld);
        LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10);
        pchar.questTemp.WPU.Postcureer.AgentIslandID = GetCharacterCurrentIslandId(pchar);
        pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
        pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.AgentIslandID;
        pchar.quest.Postcureer_Hunter.function = "PostcureerAgent_ShipAttack";
        AddQuestRecord("Postcureer", "13");
        DialogExit();
        break;

    case "PostAgent_inTavern":
        dialog.text = "Так, вот теперь можно спокойно поговорить.";
        link.l1 = "Ну, и что вы мне собрались предложить?";
        link.l1.go = "PostAgent_inTavern_1";
        break;

    case "PostAgent_inTavern_1":
        dialog.text = "Как я уже сказал, речь идет о бумагах, которые вы получили в портовом управлении. Мне нужно всего лишь снять с них копию и всех дел\nОригинал останется у вас, вы его отвезете адресату и получите свою награду. Никто ни о чем не узнает, а за возможность снять копию документа я вам неплохо заплачу.";
        link.l1 = "Позвольте... Но пакет запечатан. Вы не сможете снять копии, не сломав печать!";
        link.l1.go = "PostAgent_inTavern_2";
        break;

    case "PostAgent_inTavern_2":
        dialog.text = "Я ожидал этого вопроса. Сломать печать действительно придется, но не беспокойтесь - я восстановлю ее, после того как сниму копию. У меня есть дубликат нужного клише, и сургуч, конечно, тоже. Никто и не заметит, что пакет вскрывали.";
        link.l1 = "У вас есть поддельное клише портового управления " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + "?";
        link.l1.go = "PostAgent_inTavern_3";
        break;

    case "PostAgent_inTavern_3":
        pchar.questTemp.WPU.Postcureer.AgentMoney = sti(pchar.rank) * 3500;
        dialog.text = "Капитан, к чему эти вопросы? Да, есть, или вы думаете, я здесь в игрушки играю? Я предлагаю вам " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)) + " за возможность посмотреть эти бумаги, фактически - за просто так. Ну, так вы дадите наконец мне этот пакет?";
        link.l1 = "Держите. Только делайте все аккуратно!";
        link.l1.go = "PostAgent_inTavern_4";
        link.l2 = "Знаете что, я не буду с вами сотрудничать. Не нравится мне все это.";
        link.l2.go = "PostAgent_inTavern_getout";
        break;

    case "PostAgent_inTavern_4":
        dialog.text = "Не переживайте. Комар носа не подточит. Присядьте, отдохните. Это все займет у меня примерно час.";
        link.l1 = "Хорошо.";
        link.l1.go = "PostAgent_inTavern_5";
        break;

    case "PostAgent_inTavern_5":
        NextDiag.currentnode = "PostAgent_inTavern_6";
        RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
        pchar.questTemp.WPU.Postcureer.AgentChance = drand(4); //шанс, что раскроют обман - 20%
        DialogExit();
        AddDialogExitQuest("PostAgent_inTavern_Room_end");
        break;

    case "PostAgent_inTavern_getout":
        dialog.text = "Хм... не ожидал. Ну, раз вы такой упрямец, капитан, мне просто придется убить вас прямо здесь и забрать пакет бесплатно. Помолитесь напоследок, ибо клинком я владею не хуже, чем поддельными клише.";
        link.l1 = "Это тебе стоит помолиться, шпион!";
        link.l1.go = "PostAgent_inTavern_fight";
        break;

    case "PostAgent_inTavern_6":
        dialog.text = "Ну вот и все. Как я и говорил - все сделано в лучшем виде. Получите ваш пакет и обещанные " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)) + ". Ну, а теперь нам пора проститься. Всего доброго, капитан, рад, что мы нашли общий язык.";
        link.l1 = "Прощайте...";
        link.l1.go = "PostAgent_inTavern_7";
        break;

    case "PostAgent_inTavern_7":
        DialogExit();
        bDisableFastReload = false;
        chrDisableReloadToLocation = false;
        AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.AgentMoney));
        GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
        sld = characterFromID("PostAgent");
        LAi_SetActorType(sld);
        LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 2);
        AddQuestRecord("Postcureer", "15");
        AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)));
        break;

    case "PostAgent_inTavern_fight":
        bDisableFastReload = false;
        sld = characterFromID("PostAgent");
        LAi_group_MoveCharacter(sld, "EnemyFight");
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        AddQuestRecord("Postcureer", "16");
        break;
        //<-- почтовый генератор 2 уровня

        // --> --------------------------------- эскорт 2 уровень --------------------------------------------------
    case "DisasterCap":
        dialog.text = "Здравствуйте! Как же я рад вас видеть, как я рад!";
        link.l1 = "Добрый день. Хм, скажите, вы случаем не с корабля под названием '" + pchar.questTemp.WPU.Escort.ShipName + "'?";
        link.l1.go = "DisasterCap_1";
        break;

    case "DisasterCap_1":
        dialog.text = "О! А откуда вам известно про '" + pchar.questTemp.WPU.Escort.ShipName + "'? Да, я капитан этого корабля. Вернее, бывший капитан... Судно затонуло недалеко отсюда.";
        link.l1 = "А, ну вот я и нашел вас... Позвольте представиться - " + GetFullName(pchar) + ". Я прибыл сюда по просьбе начальника портового управления " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.StartCity + "Gen") + ". Он вкратце рассказал о злоключениях вашего каравана и отправил меня на розыск вашего корабля.";
        link.l1.go = "DisasterCap_2";
        break;

    case "DisasterCap_2":
        dialog.text = "Так вы - капитан спасательной экспедиции?";
        link.l1 = "Ну, что-то вроде того. В мою задачу входили поиски вашего корабля или неопровержимых доказательств его гибели. К сожалению, я получил не корабль, а доказательства, из уст его капитана ...м-м?";
        link.l1.go = "DisasterCap_3";
        break;

    case "DisasterCap_3":
        dialog.text = "Ох, простите, я не представился. Мое имя - " + GetFullName(npchar) + ". Вам уже известны некоторые обстоятельства того, как мы попали сюда? После того, как налетевший шторм разлучил наше судно с караваном, нас больше суток несло по волнам - корабль был неуправляем\nВ конце концов нас выбросило на рифы недалеко от этой бухты. Шторм не прекращался, и корабль развалился в считаные минуты. Спастись удалось не всем... лишь немногим более полусотни человек моей команды смогли достичь спасительного берега. Остальные лежат там, на дне. Мы каждый день молимся за их души...";
        link.l1 = "Примите мои соболезнования, капитан " + GetFullName(npchar) + ". Мне действительно очень жаль.";
        link.l1.go = "DisasterCap_4";
        break;

    case "DisasterCap_4":
        dialog.text = "Спасибо... Ну, а мы, выжившие, разбили на берегу лагерь и ждали помощи. Которая явилась в вашем лице. И вы прибыли очень вовремя, капитан! Потому что о нашем появлении пронюхали местные воинственные индейцы - мы уже дважды отбивали их атаки на наш бивак. Но долго мы против них продержаться не смогли бы - их сотни, а нас всего лишь пять десятков\nКроме того, опасность также грозит и с моря - наш дозорный уже три дня наблюдает за пиратским кораблем, крейсирующим в акватории острова - он явно разыскивает наше судно. Вы не встретили этого пирата, капитан, по пути сюда?";
        link.l1 = "Нет, не встречал.";
        link.l1.go = "DisasterCap_5";
        break;

    case "DisasterCap_5":
        dialog.text = "И слава Богу. Это один из тех, ну, которые напали нас тогда, до того кошмарного шторма. Он, как гиена, решил не упускать подраненую добычу, и явился вслед за нами сюда, к этому острову.";
        link.l1 = "Ясно. Ну, теперь надо решить, что мы будем делать.";
        link.l1.go = "DisasterCap_6";
        break;

    case "DisasterCap_6":
        dialog.text = "А что тут решать, капитан? Возьмите нас к себе на борт, и уберемся из этого ужасного места!";
        link.l1 = "Безусловно. Раз мне не удалось спасти корабль - надо по крайней мере спасти его команду. Сворачивайте лагерь, я прикажу прислать на берег шлюпки - и добро пожаловать!";
        link.l1.go = "DisasterCap_7";
        break;

    case "DisasterCap_7":
        PlaySound("people fight\rifle_fire1.wav");
        PlaySound("people fight\player_man_shoot_01.wav");
        dialog.text = "Спасибо, капитан! Нам не потребуется много времени. Постойте... Это еще за черт? А-ать, опять эти краснокожие дьяволы! Тревога! К бою!";
        link.l1 = "...";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("DisasterShipCrew_IndianAttack");
        break;

    case "DisasterCap_8":
        dialog.text = "Ух, отбились... Видите, капитан, я вам говорил: эта бухта - сущий ад. Это уже третья атака проклятых индеев! Нужно побыстрее уносить отсюда ноги, еще одно такое нападение - и вам уже будет некого спасать.";
        link.l1 = "Да уж, вы правы. Собирайте всех, кто остался в живых и быстро на корабль! Я распоряжусь, чтобы шлюпки выслали немедленно!";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("DisasterShipCrew_onBoard");
        AddQuestRecord("Escort", "38");
        AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
        AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
        AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore));
        break;
        // <-- эскорт 2 уровень

        //Jason --> -------------------------- Заносчивый аристократ ------------------------------------------------
    case "Badboy":
        dialog.text = "Ик... Чего тебе от меня надо? Проваливай, я не желаю с тобой разговаривать.";
        link.l1 = "Ты - " + pchar.GenQuest.Badboy.Brothel.Name + "?";
        link.l1.go = "Badboy_1";
        break;

    case "Badboy_1":
        dialog.text = "Да, это я. А какое тебе дело?";
        link.l1 = "А очень простое. Твои выходки уже утомили кое-кого в этом городе. Причем изрядно утомили. И, глядя сейчас на тебя, я понимаю, почему. В общем, или ноги твоей больше в местном борделе не будет, или считай, что ты обзавелся кучей неприятностей. Усек?";
        link.l1.go = "Badboy_2";
        break;

    case "Badboy_2":
        switch (sti(pchar.GenQuest.Badboy.Brothel.Type))
        {
        case 0: //или напугается, или будет быковать - от авторитета
            if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 30)
            {
                dialog.text = "Аргх! Ты... ты смеешь мне угрожать, скотина? Да я тебя сейчас наживлю на мою шпагу и поджарю, как на вертеле!";
                link.l1 = "Ну, держись, ублюдок!";
                link.l1.go = "Badboy_fight_1";
                NextDiag.currentnode = "Badboy_after_fight";
            }
            else
            {
                dialog.text = "Что? Да какие выходки? Не было никаких выходок. Ну напился, погулял в борделе пару раз. С кем не бывает... Хорошо-хорошо, обойдусь я больше без их услуг. Вы довольны? Даю слово.";
                link.l1 = "Надеюсь, ты отдаешь отчет своим словам и последствиям, которые наступят, если ты нарушишь данное обещание. Имей это в виду. А теперь - прощай.";
                link.l1.go = "exit";
                pchar.GenQuest.Badboy.Complete = "true";
                LAi_CharacterDisableDialog(npchar);
                npchar.lifeday = 0;
            }
            break;
        case 1: //дуэль за городом
            dialog.text = "Вы просто наглец, сударь! Я клянусь, что еще до исхода дня заставлю вас пожалеть об этих словах. Я вызываю вас на дуэль! Думаю, лучше провести ее с глазу на глаз... в тихом месте. Джунгли за городскими воротами как раз подойдут - встретимся через два часа!";
            link.l1 = "Отличная идея! По крайней мере, мне не надо будет беспокоиться, куда деть твой труп.";
            link.l1.go = "Badboy_duel";
            NextDiag.currentnode = "Badboy_duel_1";
            break;
        case 2: //призовет на помощь дружков
            dialog.text = "Что? Да какие выходки? Не было никаких выходок. Ну напился, погулял в борделе пару раз. С кем не бывает... Хорошо-хорошо, обойдусь я больше без их услуг. Вы довольны? Даю слово.";
            link.l1 = "Надеюсь, ты отдаешь отчет своим словам и последствиям, которые наступят, если ты нарушишь данное обещание. Имей это в виду. А теперь - прощай.";
            link.l1.go = "exit_continue";
            pchar.GenQuest.Badboy.Continue = "true";
            NextDiag.currentnode = "Badboy_friends";
            break;
        }
        break;

    case "Badboy_fight_1":
        chrDisableReloadToLocation = true;
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
        sld = characterFromId("Badboy");
        GetCharacterPos(pchar, &locx, &locy, &locz);
        ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        AddDialogExitQuest("MainHeroFightModeOn");
        LAi_SetCheckMinHP(npchar, 10.0, true, "Badboy_capture");
        DialogExit();
        break;

    case "Badboy_after_fight":
        dialog.text = "Остановись! Стой! Я сдаюсь! Пощади!";
        link.l1 = "Ага, вот как мы теперь запели!";
        link.l1.go = "Badboy_after_fight_1";
        break;

    case "Badboy_after_fight_1":
        dialog.text = "Умоляю, пощади! Я сделаю так, как ты скажешь! Больше я не появлюсь в этом борделе никогда!";
        link.l1 = "Такая поза больше пристала мрази, подобной тебе. Надеюсь, это послужит тебе уроком на всю оставшуюся жизнь. И веди себя в этом городе тише воды, ниже травы.";
        link.l1.go = "Badboy_exit";
        link.l2 = "Это точно. Больше ты там не появишься, потому что твои похождения закончатся здесь и сейчас.";
        link.l2.go = "Badboy_killed";
        pchar.GenQuest.Badboy.Complete = "true";
        break;

    case "Badboy_exit":
        LAi_SetPlayerType(pchar);
        chrDisableReloadToLocation = false;
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
        LAi_SetActorType(npchar);
        npchar.lifeday = 0;
        LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
        DialogExit();
        break;

    case "Badboy_killed":
        DialogExit();
        LAi_SetImmortal(npchar, false);
        LAi_ActorAnimation(pchar, "shot", "Badboy_killed_end", 2.2);
        break;

    case "Badboy_duel":
        chrDisableReloadToLocation = true;                                                                  //закрыть локацию
        LAi_LocationDisableOfficersGen(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown", true);             //офицеров не пускать
        locations[FindLocation(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown")].DisableEncounters = true; //энкаутеры закроем
        pchar.quest.BadboyDuelTimer.win_condition.l1 = "Timer";
        pchar.quest.BadboyDuelTimer.win_condition.l1.date.hour = sti(GetTime() + 2);
        pchar.quest.BadboyDuelTimer.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
        pchar.quest.BadboyDuelTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
        pchar.quest.BadboyDuelTimer.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
        pchar.quest.BadboyDuelTimer.function = "Badboy_duelstart";
        sld = characterFromId("Badboy");
        LAi_SetActorType(sld);
        GetCharacterPos(pchar, &locx, &locy, &locz);
        ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
        LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
        TakeNItems(sld, "jewelry5", rand(10));
        TakeNItems(sld, "jewelry3", rand(10));
        TakeNItems(sld, "jewelry1", rand(10));
        sld.money = 24560;
        sld.SaveItemsForDead = true; // сохранять на трупе вещи
        sld.DontClearDead = true;    // не убирать труп через 200с
        LAi_RemoveLoginTime(sld);    //удалить время логина
        SetFunctionTimerCondition("Badboy_duelOver", 0, 0, 1, false);
        DialogExit();
        break;

    case "Badboy_duel_1":
        dialog.text = "Ну, пора отправить тебя в ад, наглец! Помолись напоследок, только недолго...";
        link.l1 = "Меньше слов, больше дела, мерзавец!";
        link.l1.go = "Badboy_duel_2";
        break;

    case "Badboy_duel_2":
        chrDisableReloadToLocation = true;
        LAi_SetPlayerType(pchar);
        LAi_SetWarriorType(npchar);
        LAi_group_MoveCharacter(npchar, "EnemyFight");
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
        LAi_group_SetCheck("EnemyFight", "Badboy_die");
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

    case "exit_continue":
        sld = characterFromID("Badboy");
        LAi_RemoveLoginTime(sld); // patch-6
        LAi_SetActorType(sld);
        GetCharacterPos(pchar, &locx, &locy, &locz);
        ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
        LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
        DialogExit();
        break;

    case "Badboy_friends":
        dialog.text = "А вот и этот наглый мерзавец! Покажем ему, ребята, кто в этом городе настоящий хозяин!";
        link.l1 = "Ах ты, выродок! Ну, я тебя предупреждал. Сейчас ты и вся эта шпана отправитесь в ад!";
        link.l1.go = "Badboy_friends_fight";
        break;

    case "Badboy_friends_fight":
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        DeleteAttribute(pchar, "GenQuest.Badboy");
        break;
        //Jason <-- Заносчивый аристократ

        //Jason --> ------------------------------- Место под солнцем ----------------------------------------------
    case "Sunplace_Store":
        pchar.quest.SunplaceContinue_Over.over = "yes";
        dialog.text = "Здравствуйте. Что вам нужно?";
        link.l1 = "Ты ведь " + pchar.GenQuest.Sunplace.Trader.Enemyname + "? Ты не поверишь, хе-хе. Мне нужна твоя голова.";
        link.l1.go = "Sunplace_Store_1";
        link.l2 = "Хм... Да нет... Нет, ничего. Я, наверное, ошибся. Прошу меня извинить за беспокойство.";
        link.l2.go = "Sunplace_Store_exit";
        break;

    case "Sunplace_Store_1":
        dialog.text = "Что за дурацкие шутки, сударь? Немедля объяснитесь, или я...";
        link.l1 = "И что ты сделаешь, мещанская селедка? Ты насолил одному хорошему человеку, и он очень расстроен. Так что молись, но побыстрее, ибо медлить я не намерен.";
        link.l1.go = "Sunplace_Store_3";
        break;

    case "Sunplace_Store_3":
        dialog.text = "Вы что... вы что, сударь! Помогите! На помощь, кто-нибудь! Убивают!";
        link.l1 = "Лучше бы ты помолился - глядишь, в рай попал бы...";
        link.l1.go = "Sunplace_Store_fight";
        break;

    case "Sunplace_Store_exit":
        sld = CharacterFromID("SunplaceTrader");
        sld.lifeday = 0;
        AddQuestRecord("Sunplace", "9");
        CloseQuestHeader("Sunplace");
        DialogExit();
        DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
        NextDiag.currentnode = "Sunplace_Store_repeat";
        break;

    case "Sunplace_Store_repeat":
        dialog.text = "Это опять вы? Может скажете, что вы от меня хотите?";
        link.l1 = "Да нет, ничего.";
        link.l1.go = "exit";
        break;

    case "Sunplace_Store_fight":
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        sld = CharacterFromID("SunplaceTrader");
        LAi_SetImmortal(sld, false);
        LAi_SetActorType(sld);
        LAi_ActorAfraid(sld, Pchar, true);
        sld = characterFromId(pchar.GenQuest.Sunplace.Trader.CityT + "_trader");
        LAi_group_Attack(sld, Pchar);
        pchar.quest.Kill_SunplaceTrader.win_condition.l1 = "ExitFromLocation";
        pchar.quest.Kill_SunplaceTrader.win_condition.l1.location = pchar.location;
        pchar.quest.Kill_SunplaceTrader.function = "Kill_SunplaceTrader";
        break;
        // <-- место под солнцем

        //------------------------------------- киллеры Лиги-------------------------------------------------------
    case "LigaHunters":
        dialog.text = "";
        link.l1 = "А?! Что? Что вы здесь делаете, черт побери? Кто вас сюда впустил?";
        link.l1.go = "LigaHunters_1";
        break;

    case "LigaHunters_1":
        dialog.text = "Лиге нужна твоя жизнь, капитан...";
        link.l1 = "Что? А-ать, дьявол!!";
        link.l1.go = "LigaHunters_2";
        break;

    case "LigaHunters_2":
        DialogExit();
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
        for (i = 1; i <= 2; i++)
        {
            sld = characterFromId("LigaHunter_" + i);
            LAi_SetWarriorType(sld);
            LAi_group_MoveCharacter(sld, "EnemyFight");
        }
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck("EnemyFight", "LigaHunters_Dead");
        AddDialogExitQuest("MainHeroFightModeOn");
        break;
        // <-- киллеры Лиги

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    //замечание по обнаженному оружию от персонажей типа citizen
    case "CitizenNotBlade":
        if (loadedLocation.type == "town")
        {
            dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнаженным клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
            link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
            link.l1.go = "exit";
        }
        else
        {
            dialog.text = NPCharSexPhrase(NPChar, "Острожней на поворотах, " + GetSexPhrase("приятель", "подруга") + ", когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда " + GetSexPhrase("мужчины", "всякие тут") + " ходят передо мной с оружием на изготовку. Это меня пугает...");
            link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Не переживай, уже убираю...");
        }
        link.l1.go = "exit";
        NextDiag.TempNode = "First Time";
        if (npchar.id == "Device_poorman")
            NextDiag.TempNode = "Device_poorman";
        break;
    }
}
