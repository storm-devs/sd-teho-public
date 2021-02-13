void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    int i, n, iTemp;
    string sTemp;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";

    switch (Dialog.CurrentNode)
    {
    case "First time":
        dialog.text = "";
        link.l1 = "";
        link.l1.go = "exit";
        break;

    //вестовой
    case "Regata_Cureer":
        dialog.text = "Добрый день. Вы - капитан " + GetFullName(pchar) + "?";
        link.l1 = "Да, это я. А в чем дело?";
        link.l1.go = "Regata_Cureer_1";
        break;

    case "Regata_Cureer_1":
        dialog.text = "У меня для вас письмо от губернатора Ямайки, сэра Эдварда Дойли.";
        link.l1 = "Ого! Не ожидал... И что же губернатор хочет от меня?";
        link.l1.go = "Regata_Cureer_2";
        break;

    case "Regata_Cureer_2":
        dialog.text = "Прочтите письмо, сэр. Но вкратце - вам предложено принять участие в регате, гонках на время, по архипелагу. Слухи о ваших способностях к быстрому передвижению в море не остались без внимания.";
        link.l1 = "Удивительно! Ну что же... прочту и подумаю.";
        link.l1.go = "Regata_Cureer_3";
        GiveItem2Character(pchar, "letter_open");
        ChangeItemDescribe("letter_open", "itmdescr_letter_open_Regata");
        AddQuestRecordInfo("RegataLetter", "1");
        break;

    case "Regata_Cureer_3":
        if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND)
        {
            dialog.text = "Также я должен обеспечить вам беспрепятственный вход в порт Порт-Рояла для прибытия на регату. Для этого я уполномочен выдать вам лицензию сроком на 30 дней. На этом моя миссия выполнена. До свидания, капитан!";
            link.l1 = "Спасибо, лицензия - это весьма кстати. До свидания!";
            link.l1.go = "Cureer_exit";
            GiveNationLicence(HOLLAND, 30);
        }
        else
        {
            dialog.text = "Хорошо. На этом моя миссия выполнена. До свидания, капитан!";
            link.l1 = "До свидания!";
            link.l1.go = "Cureer_exit";
        }
        break;

    case "Cureer_exit":
        chrDisableReloadToLocation = false;
        bDisableFastReload = false;
        DialogExit();
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
        pchar.questTemp.Regata.ToPortRoyal = "true";
        SetFunctionTimerCondition("RegataToPortRoyalTimeOver", 0, 0, 31, false);
        break;

    //распорядитель регаты
    case "Regata_Head":
        if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
        {
            dialog.text = "Добрый день. Вы участвуете в регате, как я понимаю?";
            link.l1 = "Именно так, сэр. Мое имя - " + GetFullName(pchar) + ". Я получил приглашение.";
            link.l1.go = "Regata_Head_1";
        }
        else
        {
            dialog.text = "Вы что-то хотели, сэр?";
            link.l1 = "Да нет, ничего. Я уже ухожу.";
            link.l1.go = "exit";
            NextDiag.TempNode = "Regata_Head";
        }
        break;

    case "Regata_Head_1":
        iTest = FindColony("PortRoyal");
        if (iTest != -1)
        {
            rColony = GetColonyByIndex(iTest);
        }
        ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok) //проверка на наличие корабля в порту
        {
            dialog.text = "Рад познакомиться, капитан " + GetFullName(pchar) + ". Итак, приступим. Первые условия вам должны были быть известны из письма, так? Регата проходит только на кораблях типа 'люггер' и только один в эскадре. Вы выполнили эти требования?";
            if ((GetCompanionQuantity(pchar) > 1) || sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_LUGGER)
            {
                link.l1 = "Еще не успел отдать необходимые распоряжения. Сейчас же сделаю это и вернусь к вам.";
                link.l1.go = "exit";
                NextDiag.TempNode = "Regata_Head_repeat";
            }
            else
            {
                link.l1 = "Да, так точно.";
                link.l1.go = "Regata_Head_2";
            }
        }
        else
        {
            dialog.text = "Вы прибыли на регату - а корабль ваш где? Я не получил никаких сведений о вашем судне из портового управления.";
            link.l1 = "Прошу прощения, сэр. Я немедленно приведу свой корабль в порт.";
            link.l1.go = "exit";
            NextDiag.TempNode = "Regata_Head_repeat";
        }
        break;

    case "Regata_Head_repeat":
        if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
        {
            iTest = FindColony("PortRoyal");
            if (iTest != -1)
            {
                rColony = GetColonyByIndex(iTest);
            }
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok) //проверка на наличие корабля в порту
            {
                dialog.text = "А, это опять вы. Ну, вы все сделали для выполнения условий?";
                if ((GetCompanionQuantity(pchar) > 1) || sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_LUGGER)
                {
                    link.l1 = "Еще не успел. Сейчас же сделаю это и вернусь к вам.";
                    link.l1.go = "exit";
                    NextDiag.TempNode = "Regata_Head_repeat";
                }
                else
                {
                    link.l1 = "Да, так точно.";
                    link.l1.go = "Regata_Head_2";
                }
            }
            else
            {
                dialog.text = "Капитан, пока я не увижу ваше судно на рейде, нам разговаривать не о чем. Вы это поняли наконец, или мне еще раз повторить?";
                link.l1 = "Прошу прощения, сэр. Я немедленно приведу свой корабль в порт.";
                link.l1.go = "exit";
                NextDiag.TempNode = "Regata_Head_repeat";
            }
        }
        else
        {
            dialog.text = "Вы что-то хотели, сэр?";
            link.l1 = "Да нет, ничего. Я уже ухожу.";
            link.l1.go = "exit";
            NextDiag.TempNode = "Regata_Head";
        }
        break;

    case "Regata_Head_2":
        dialog.text = "Отлично. Теперь далее. Как называется ваш корабль?";
        link.l1 = "'" + pchar.Ship.Name + "'.";
        link.l1.go = "Regata_Head_3";
        break;

    case "Regata_Head_3":
        dialog.text = "Поскольку регата организуется английскими властями, а также согласно устоявшихся правил, на время регаты имя вашего корабля меняется. Не пугайтесь, это касается всех участников.";
        link.l1 = "Менять имя кораблю - плохая примета, говорят.";
        link.l1.go = "Regata_Head_4";
        break;

    case "Regata_Head_4":
        dialog.text = "После регаты вернете имя обратно. Итак, ваш люггер теперь будет носить имя 'Сaнта-Kатepина'. Распорядитесь о визуальной смене названия вашего корабля.";
        link.l1 = "Я вас понял, сэр, сделаю.";
        link.l1.go = "Regata_Head_5";
        pchar.Ship.Name = "Сaнта-Kатepина";
        break;

    case "Regata_Head_5":
        dialog.text = "Теперь немного подробнее о регате. Слушайте внимательно, что я вам расскажу. Также я дам вам бумагу с правилами, чтобы вы не забыли. Итак\nРегата круговая, начинается в Порт-Рояле и заканчивается в Порт-Рояле. По пути вас ожидает пять переходов\nпервый: Порт-Рояль - Белиз, что на Западном Мейне\nвторой: Белиз - Порт-о-Пренс, что на Эспаньоле\nтретий: Порт-о-Пренс - Сент-Джонс, что на Антигуа\nчетвертый: Сент-Джонс - Бриджтаун, что на Барбадосе\nпятый, самый продолжительный - Бриджтаун - Порт-Рояль\nЯ понятно объяснил?";
        link.l1 = "Вполне, сэр.";
        link.l1.go = "Regata_Head_6";
        break;

    case "Regata_Head_6":
        dialog.text = "Замечательно. В каждом из названных мной промежуточных пунктов - Белиз, Порт-о-Пренс, Сент-Джонс и Бриджтаун, вы должны отметиться в портовом управлении - начальники портов являются контролерами регаты. Если вы не отметитесь хотя бы в одном из пунктов, или нарушите последовательность - вас дисквалифицируют\nЕсли вы прибудете ночью - не беспокойтесь, во время регаты будет установлено круглосуточное дежурство в портовых управлениях - просто подойдите и постучите в дверь - вам откроют.";
        link.l1 = "Это тоже понятно.";
        link.l1.go = "Regata_Head_7";
        break;

    case "Regata_Head_7":
        dialog.text = "Менять корабль и добавлять корабли в эскадру запрещено. Это будет проверяться в каждом промежуточном пункте, учтите.";
        link.l1 = "Учту. Как определяется победитель, и каковы награды?";
        link.l1.go = "Regata_Head_8";
        break;

    case "Regata_Head_8":
        dialog.text = "Победитель в регате только один - капитан, чей корабль вернется в Порт-Рояль первым. Награды весьма солидные. Победитель получает крупную денежную сумму - 250 000 песо. Также ему будет вручен комплект ценных призов.";
        link.l1 = "То есть, проигравшим не достается ничего?";
        link.l1.go = "Regata_Head_9";
        break;

    case "Regata_Head_9":
        dialog.text = "Совершенно верно. Добавлю: многие богатые, и не очень богатые жители английских колоний делают ставки на победителя регаты. Так вот, вы тоже можете сделать ставку... на свою победу, например. Обычно все капитаны так делают. В случае вашей победы денежный приз увеличится, и у вас будет дополнительный стимул. Ставки принимаю я\nБудете делать ставку на свою победу в регате?";
        link.l1 = "Ха! Конечно, буду. Сколько можно ставить?";
        link.l1.go = "Regata_rate";
        link.l2 = "Я подумаю. Может, и поставлю.";
        link.l2.go = "Regata_Head_10";
        break;

    case "Regata_Head_10":
        if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
        {
            dialog.text = "Думайте. До начала регаты вы можете прийти ко мне и сделать ставку.";
            link.l1 = "Хорошо. Когда старт регаты?";
            link.l1.go = "Regata_Head_11";
            DeleteAttribute(pchar, "questTemp.Regata.Rate");
            pchar.questTemp.Regata.Ratenext = "true";
        }
        else
        {
            dialog.text = "Думайте. До начала регаты вы можете прийти ко мне и сделать ставку.";
            link.l1 = "Хорошо.";
            link.l1.go = "exit";
        }
        break;

    case "Regata_Head_11":
        CreateRegataAdversaries();
        dialog.text = "Через 3 дня, в 12 часов. Вы должны быть на пирсе. У вас будет пять противников\n" + pchar.questTemp.Regata.AdversaryName.a + ", на корабле '" + pchar.questTemp.Regata.AdversaryShipName.a + "'\n" + pchar.questTemp.Regata.AdversaryName.b + ", на корабле '" + pchar.questTemp.Regata.AdversaryShipName.b + "'\n" + pchar.questTemp.Regata.AdversaryName.c + ", на корабле '" + pchar.questTemp.Regata.AdversaryShipName.c + "'\n" + pchar.questTemp.Regata.AdversaryName.d + ", на корабле '" + pchar.questTemp.Regata.AdversaryShipName.d + "'\n" + pchar.questTemp.Regata.AdversaryName.e + ", на корабле '" + pchar.questTemp.Regata.AdversaryShipName.e + "'\nВсе весьма опытные капитаны. Вот, вроде и все. Возьмите эту бумагу, в ней записаны все правила, чтобы вы не забыли чего. А теперь - до встречи на старте!";
        link.l1 = "До свидания, сэр.";
        if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND)
            link.l1.go = "Regata_Head_13";
        else
            link.l1.go = "Regata_Head_12";
        break;

    case "Regata_Head_12":
        DialogExit();
        pchar.quest.RegataToPortRoyalTimeOver.over = "yes"; //снять таймер
        SetFunctionTimerCondition("Regata_SetTime", 0, 0, 3, false);
        pchar.quest.Regata_Lost.win_condition.l1 = "Timer";
        pchar.quest.Regata_Lost.win_condition.l1.date.hour = 13.0;
        pchar.quest.Regata_Lost.win_condition.l1.date.day = GetAddingDataDay(0, 0, 3);
        pchar.quest.Regata_Lost.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
        pchar.quest.Regata_Lost.win_condition.l1.date.year = GetAddingDataYear(0, 0, 3);
        pchar.quest.Regata_Lost.function = "Regata_Lost";
        pchar.quest.Regata_Start.win_condition.l1 = "Timer";
        pchar.quest.Regata_Start.win_condition.l1.date.hour = 12.0;
        pchar.quest.Regata_Start.win_condition.l1.date.day = GetAddingDataDay(0, 0, 3);
        pchar.quest.Regata_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
        pchar.quest.Regata_Start.win_condition.l1.date.year = GetAddingDataYear(0, 0, 3);
        pchar.quest.Regata_Start.win_condition.l2 = "locator";
        pchar.quest.Regata_Start.win_condition.l2.location = "Portroyal_town";
        pchar.quest.Regata_Start.win_condition.l2.locator_group = "reload";
        pchar.quest.Regata_Start.win_condition.l2.locator = "reload1_back";
        pchar.quest.Regata_Start.function = "Regata_Start";
        AddQuestRecordInfo("RegataRules", "1");
        NextDiag.CurrentNode = "Regata_Prepare";
        DeleteAttribute(pchar, "questTemp.Regata.Begin");
        pchar.questTemp.Regata.Prepare = "true";
        break;

    case "Regata_Head_13":
        dialog.text = "Подождите! Для свободного посещения английских и французских портов я выдаю вам лицензию сроком на 30 дней - регата не продлится больше месяца. Пожалуйста, получите.";
        link.l1 = "Спасибо!";
        link.l1.go = "Regata_Head_12";
        GiveNationLicence(HOLLAND, 30);
        break;

    case "Regata_rate":
        dialog.text = "Сколько вы готовы поставить?";
        link.l1 = "";
        Link.l1.edit = 4;
        link.l1.go = "Regata_rate_1";
        link.l2 = "Пожалуй, мне еще надо подумать.";
        link.l2.go = "Regata_Head_10";
        break;

    case "Regata_rate_1":
        int iQty = sti(dialogEditStrings[4]);
        pchar.questTemp.Regata.Rate = sti(iQty);
        if (iQty < 10000)
        {
            dialog.text = "Сэр, не смешите. Ну что за мелочность? Я даже не буду возиться с такой ничтожной суммой.";
            link.l1 = "Прошу прощения... Давайте пересмотрим размер ставки.";
            link.l1.go = "Regata_rate";
            break;
        }
        if (iQty > 100000)
        {
            dialog.text = "Сэр, правила не позволяют мне принимать такие ставки. Уменьшите ее размер до разумной величины.";
            link.l1 = "Жаль... Давайте пересмотрим сумму.";
            link.l1.go = "Regata_rate";
            break;
        }
        dialog.text = "" + iQty + "? Хорошая ставка. Я готов ее принять. Ваши деньги, сэр?";
        if (makeint(Pchar.money) >= sti(pchar.questTemp.Regata.Rate))
        {
            link.l1 = "Пожалуйста, получите.";
            link.l1.go = "Regata_rate_2";
        }
        link.l2 = "У меня сейчас недостаточно денег. Я приду позже и сделаю ставку. И еще подумаю, может, поменяю сумму.";
        link.l2.go = "Regata_Head_10";
        break;

    case "Regata_rate_2":
        AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.Rate));
        pchar.questTemp.Regata.Advantage = sti(pchar.questTemp.Regata.Rate) * (1.5 + frand(1.5)); // dlc
        dialog.text = "Отлично! Теперь вам нужно прийти первым - и выигрыш ваш. Его размер может быть разным - в зависимости от того, сколько людей поставят на вас.";
        if (!CheckAttribute(pchar, "questTemp.Regata.Ratenext"))
        {
            link.l1 = "Понятно. Когда старт регаты?";
            link.l1.go = "Regata_Head_11";
        }
        else
        {
            link.l1 = "Понятно. Жду старта. До свидания!";
            link.l1.go = "exit";
            DeleteAttribute(pchar, "questTemp.Regata.Ratenext");
            NextDiag.TempNode = "Regata_Prepare";
        }
        break;

    case "Regata_Prepare":
        dialog.text = "А, это опять вы, капитан " + GetFullName(pchar) + "? По какому вопросу пожаловали?";
        if (!CheckAttribute(pchar, "questTemp.Regata.Rate"))
        {
            link.l1 = "Я хочу сделать ставку на свою победу.";
            link.l1.go = "Regata_rate";
        }
        link.l2 = "Да нет, ничего особенного, просто решил поприветствовать вас.";
        link.l2.go = "exit";
        NextDiag.TempNode = "Regata_Prepare";
        break;

    //старт регаты
    case "Regata_CitMan":
        dialog.text = RandPhraseSimple(LinkRandPhrase("Капитан, вы первый раз участвуете в регате? Вот что я вам скажу: будьте осторожны. Соперники могут организовать вам неприятный сюрприз...", "Капитан, я поставил на вас. Не разочаруйте меня!", "Капитан, в портах следования регаты жители могут предложить купить у них что-нибудь. Это часто оказывается полезным. Имейте это в виду."), LinkRandPhrase("Счастливого плавания, капитан!", "Капитан, проявляйте бдительность: у испанских островов кастильцы частенько ведут охоту на люггеры участников регаты.", "Я слышал, что в пунктах следования разные темные личности предлагают капитанам регаты свои 'услуги'. Воспользоваться ими, или нет - дело, конечно, ваше."));
        link.l1 = "Да-да, конечно...";
        link.l1.go = "exit";
        NextDiag.TempNode = "Regata_CitMan";
        break;

    case "Regata_CitWom":
        dialog.text = LinkRandPhrase("Капитан, мы с мужем поставили на вас десять тысяч. Не подведите нас!", "Капитан! Желаю вам удачи!", "Ах, вы такой отважный, и такой мужественный, капитан...");
        link.l1 = "...";
        link.l1.go = "exit";
        NextDiag.TempNode = "Regata_CitWom";
        break;

    case "Regata_CitHorse":
        dialog.text = LinkRandPhrase("Хей, морячок! Помаши красотке на прощание! Я тебя жду, когда вернешься!", "Хи-и-и, моряк, соленый морячок! Мадам сказала, что отдаст меня победителю регаты на неделю бесплатно... Постарайся выиграть, ты такой милашка!", "Когда вернешься, красавчик, не забудь заглянуть к нам - обслужим по высшему разряду!");
        link.l1 = "Хорошо, дорогуша.";
        link.l1.go = "exit";
        NextDiag.TempNode = "Regata_CitHorse";
        break;

    case "Regata_Prepare_1":
        if (sti(environment.time) < 12.0)
        {
            dialog.text = "Капитан, регата стартует в 12 часов. Можете пока погулять - мы готовим торжественную часть. Приходите к полудню - ваши соперники тоже прибудут к этому времени.";
            link.l1 = "Я и моя команда полностью подготовлены, сэр! Жду старта...";
            link.l1.go = "exit";
        }
        else
        {
            dialog.text = "Вот и вы, капитан. Занимайте место на пирсе и ожидайте объявления старта регаты.";
            link.l1 = "Я и моя команда полностью подготовлены, сэр! Жду старта...";
            link.l1.go = "exit";
        }
        NextDiag.TempNode = "Regata_Prepare_1";
        break;

    case "Regata_Start":
        dialog.text = "Итак, джентльмены, вы все собрались. Я объявляю парусную регату открытой. Правила вы знаете. Побеждает тот, чей корабль вернется в Порт-Рояль первым. Дамы и господа, пожелаем нашим отважным капитанам удачи!\nДжентльмены! Вы готовы? На старт! Внимание! Марш!!";
        link.l1 = "...";
        link.l1.go = "Regata_Start_1";
        break;

    case "Regata_Start_1":
        DialogExit();
        PlaySound("people fight\mushketshot.wav");
        log_info("Регата стартовала! На корабль! Курс - на Белиз!");
        for (i = 1; i <= 5; i++)
        {
            sld = characterFromId("Regata_Cap_F" + i);
            LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
        }
        Island_SetReloadEnableGlobal("Jamaica", false);                     //на остров нельзя
        SetFunctionTimerCondition("ReturnJamaicaNorm", 0, 0, 1, false);     //таймер на возврат нормы
        LocatorReloadEnterDisable("Portroyal_town", "reload1_back", false); //откроем выход в море
        DeleteAttribute(pchar, "questTemp.Regata.Prepare");
        pchar.questTemp.Regata.Go = "true";
        pchar.questTemp.Regata.Town = "Beliz";
        pchar.quest.Regata_PU.win_condition.l1 = "locator";
        pchar.quest.Regata_PU.win_condition.l1.location = "Beliz_town";
        pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
        pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
        pchar.quest.Regata_PU.win_condition.l2 = "Night";
        pchar.quest.Regata_PU.function = "RegataPU_Open"; //вход в ПУ ночью
        //ситуации
        pchar.quest.Regata_ShYarder.win_condition.l1 = "location";
        pchar.quest.Regata_ShYarder.win_condition.l1.location = "Beliz_town";
        pchar.quest.Regata_ShYarder.function = "RegataShipyarder";
        sld = characterFromId("Beliz_shipyarder");
        LAi_RemoveLoginTime(sld);
        break;
    //старт регаты

    //верфист с парусами
    case "Regata_Shipyarder":
        dialog.text = "Здравствуйте, капитан! Как мне известно, вы принимаете участие в карибской регате...";
        link.l1 = "Да, это так. Новости по архипелагу, и правда, разносятся быстрее ветра.";
        link.l1.go = "Regata_Shipyarder_1";
        break;

    case "Regata_Shipyarder_1":
        dialog.text = "Что верно, то верно, капитан. У меня для вас есть предложение, связанное с регатой и вашим кораблем.";
        link.l1 = "Хех! Интересно. Слушаю вас внимательно, мистер.";
        link.l1.go = "Regata_Shipyarder_2";
        break;

    case "Regata_Shipyarder_2":
        dialog.text = "Регата проводится на люггерах, сэр. А у меня как раз есть комплект парусов на люггер из хлопка самого высокого качества. Эти паруса позволят увеличить набор скорости вашим кораблем и дадут преимущество перед вашими соперниками во времени\nЯ готов вам их продать, если вы, конечно, желаете купить.";
        link.l1 = "Сколько вы хотите за эти паруса?";
        link.l1.go = "Regata_Shipyarder_3";
        break;

    case "Regata_Shipyarder_3":
        dialog.text = "Всего лишь 15 000 песо. Согласитесь, это небольшая цена для такой вещи, да еще в такой ситуации.";
        if (makeint(Pchar.money) >= 15000)
        {
            link.l1 = "Согласен! Я покупаю у вас новые паруса на свой люггер. Вот деньги. Будьте любезны доставить их на мой корабль, пока я иду отмечаться в портовое управление.";
            link.l1.go = "Regata_Shipyarder_4";
        }
        link.l2 = "Нет у меня таких денег. Так что купить ваши паруса не получится.";
        link.l2.go = "Regata_Shipyarder_exit";
        break;

    case "Regata_Shipyarder_4":
        AddMoneyToCharacter(pchar, -15000);
        dialog.text = "Будет сделано, сэр! Вы не пожалеете о своем приобретении. Кроме того, эти паруса выкрашены в замечательный голубой цвет - ваш люггер будет смотреться очень нарядно.";
        link.l1 = "Вот и славно! Ну, я отправляюсь, а вы займитесь парусами.";
        link.l1.go = "Shipyarder_exit";
        for (i = 1; i <= 5; i++)
        {
            if (i == 1)
                sTemp = "a";
            if (i == 2)
                sTemp = "b";
            if (i == 3)
                sTemp = "c";
            if (i == 4)
                sTemp = "d";
            if (i == 5)
                sTemp = "e";
            pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)) + 12; //выиграл 12 часов у всех
            log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)));
        }
        RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = 3;
        SetSailsColor(Pchar, 5);
        break;

    case "Regata_Shipyarder_exit":
        dialog.text = "Жаль, очень жаль. Ну, хозяин - барин. До свидания, капитан.";
        link.l1 = "Всего доброго!";
        link.l1.go = "Shipyarder_exit";
        pchar.questTemp.Regata.AdversarySecondTransition.Time.d = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.d) - 16; //четвертый соперник выиграл 16 часов
        log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.e));
        break;

    case "Shipyarder_exit":
        DialogExit();
        LAi_SetActorType(npchar);
        LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "Beliz_Shipyard", "sit", "sit1", "ReturnRegataSYNorm", 5);
        break;
    //верфист с парусами

    //контрики с пушками
    case "Regata_Contra":
        dialog.text = "Здравствуйте, капитан " + GetFullName(pchar) + ". У нас к вам есть разговор... точнее, деловое предложение.";
        link.l1 = "Хм. Интересно, а откуда вы меня знаете?";
        link.l1.go = "Regata_Contra_1";
        break;

    case "Regata_Contra_1":
        dialog.text = "Капитан, ну это же проще простого. Идет регата, вы ее участник - как нам не знать вас!";
        link.l1 = "Понятно. Ну, выкладывайте, что там у вас.";
        link.l1.go = "Regata_Contra_2";
        break;

    case "Regata_Contra_2":
        if (sti(pchar.questTemp.Regata.Index != 1))
        {
            sTemp = pchar.questTemp.Regata.ContraIndex;
            dialog.text = "Нам известно, что перед вами находится еще один участник регаты - " + pchar.questTemp.Regata.AdversaryName.(sTemp) + " на корабле " + pchar.questTemp.Regata.AdversaryShipName.(sTemp) + ". Он вышел из порта совсем недавно, и скоро будет проходить мимо бухты Гонаив.";
        }
        else
        {
            dialog.text = "Нам известно, что за вами буквально по пятам идет еще один участник регаты - " + pchar.questTemp.Regata.AdversaryName.b + " на корабле " + pchar.questTemp.Regata.AdversaryShipName.b + ". Он с часа на час войдет в порт.";
        }
        link.l1 = "Вы хорошо осведомлены.";
        link.l1.go = "Regata_Contra_3";
        break;

    case "Regata_Contra_3":
        if (sti(pchar.questTemp.Regata.Index != 1))
            sTemp = "а вы тем временем опредите его и займете его место";
        else
            sTemp = "а вы тем временем уйдете далеко вперед";
        dialog.text = "Безусловно. Теперь к сути дела. Мы предлагаем вам помощь на возмездной основе. Зная о маршруте регаты, мы сняли со своего корабля и установили на мысе за бухтой Гонаив четыре орудия. Любой корабль регаты будет огибать этот мыс\nПушки заряжены книппелями. Если мы с вами договоримся, мы просигналим нашим друзьям у орудий, и они несколькими залпами превратят паруса вашего соперника в рваные тряпки. Он потеряет время на починку, " + sTemp + ".";
        link.l1 = "Сколько вы хотите за эту услугу?";
        link.l1.go = "Regata_Contra_4";
        link.l2 = "Нет. Я не намерен применять для победы подобные методы. Вы не за того меня приняли. Всего доброго, джентльмены.";
        link.l2.go = "Regata_Contra_exit";
        break;

    case "Regata_Contra_exit":
        dialog.text = "Ну, капитан, как знаете. Прощайте.";
        link.l1 = "За инфорацию про мыс спасибо. Буду держаться от него подальше!";
        link.l1.go = "Contra_exit";
        ChangeCharacterComplexReputation(pchar, "nobility", 3);
        break;

    case "Regata_Contra_4":
        if (sti(pchar.questTemp.Regata.Index != 1))
            iTemp = 50000;
        else
            iTemp = 30000;
        dialog.text = "Да сущие пустяки. Всего " + iTemp + " песо. А ваш соперник потеряет как минимум два дня после нашей... операции, ха-ха!";
        if (makeint(Pchar.money) >= iTemp)
        {
            link.l1 = "Хех! Вы говорите дело, джентльмены! Я готов заплатить вам. Но какие гарантии, что вы сделаете работу? И что мой корабль не обстреляете, когда я мыс проходить буду?";
            link.l1.go = "Regata_Contra_5";
        }
        link.l2 = "Нет у меня таких денег. Так что помощью вашей воспользоваться не придется.";
        link.l2.go = "Regata_Contra_exit";
        break;

    case "Regata_Contra_5":
        dialog.text = "Капитан, мы контрабандисты, а не какие-нибудь бродяги. Мы - люди честные... в своем деле. Или вы никогда нашими услугами не пользовались и не знаете, что мы не обманываем? Даю вам слово. Можете быть уверены.";
        link.l1 = "Хорошо, вот ваши деньги.";
        link.l1.go = "Regata_Contra_6";
        break;

    case "Regata_Contra_6":
        ChangeCharacterComplexReputation(pchar, "nobility", -3);
        dialog.text = "Вы останетесь довольны этой сделкой, капитан. Ну, а мы сейчас дадим сигнал, и ваш соперник еще не скоро сможет развить приличную скорость. Удачи!";
        link.l1 = "И вам того же...";
        link.l1.go = "Contra_exit";
        if (sti(pchar.questTemp.Regata.Index != 1))
        {
            AddMoneyToCharacter(pchar, -50000);
            sTemp = pchar.questTemp.Regata.ContraIndex;
            pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp)) + 48; //задержка на 48 часов
            log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp)));
        }
        else
        {
            AddMoneyToCharacter(pchar, -30000);
            pchar.questTemp.Regata.AdversaryThirdTransition.Time.b = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b) + 36; //задержка на 36 часов
            log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b));
        }
        break;

    case "Contra_exit":
        DialogExit();
        for (i = 1; i <= 2; i++)
        {
            sld = characterFromId("RegataContra_" + i);
            LAi_SetActorType(sld);
            LAi_ActorRunToLocation(sld, "quest", "quest2", "none", "", "", "", 10.0);
        }
        break;
    //контрики с пушками

    //падре
    case "Regata_Padre":
        pchar.questTemp.Regata.BranderName = GenerateRandomNameToShip(ENGLAND);
        dialog.text = "Здравствуй, сын мой. Я пришел поприветствовать тебя, а также смиренно спросить: не желаешь ли ты, как верный слуга Англии и Господа нашего, внести посильную лепту в приходскую казну нашей церкви?";
        link.l1 = "Падре, люди делают пожертвования по зову своей души, а не по принуждению. У меня складываетя такое впечатление, что все на архипелаге решили, что раз капитан участвует в регате - значит, его нужно обобрать...";
        link.l1.go = "Regata_Padre_exit";
        link.l2 = "Конечно, святой отец. Какая сумма пожертвования будет достаточной?";
        link.l2.go = "Regata_Padre_1";
        break;

    case "Regata_Padre_1":
        dialog.text = "Сколько позволяет тебе твое желание и твои возможности, сын мой. Наш приход будет рад даже маленькой денежной сумме.";
        Link.l1.edit = 4;
        link.l1 = "";
        link.l1.go = "Regata_Padre_2";
        break;

    case "Regata_Padre_2":
        iTemp = sti(dialogEditStrings[4]);
        if (iTemp <= 0 || sti(pchar.money) < iTemp)
        {
            dialog.text = "Нехорошо так поступать, сын мой. Все мы грешны - не забывай о душе и о том, что тебе придется предстать перед Создателем... и, возможно, очень скоро.";
            link.l1 = "Я не нуждаюсь в нравоучениях, святой отец. До свидания.";
            link.l1.go = "Padre_exit";
            ChangeCharacterComplexReputation(pchar, "nobility", -3);
            break;
        }
        if (iTemp > 0 && iTemp <= 1000) //ничего не скажет
        {
            dialog.text = "От лица нашего прихода благодарю тебя за этот скромный дар.";
            link.l1 = "Не за что, святой отец.";
            link.l1.go = "Padre_exit";
            AddMoneyToCharacter(pchar, -iTemp);
        }
        if (iTemp > 1000 && iTemp <= 5000) //1 категория - намекнет
        {
            dialog.text = "От лица нашего прихода благодарю тебя за этот дар. И в благодарность я хочу предупредить тебя, сын мой: нехорошие люди затеяли против тебя недоброе. Будь осторожен в море!";
            link.l1 = "Падре, против меня ежедневно затевается что-то недоброе... Однако спасибо вам за ваше беспокойство о моей судьбе.";
            link.l1.go = "Padre_exit";
            AddMoneyToCharacter(pchar, -iTemp);
        }
        if (iTemp > 5000 && iTemp <= 10000) //2 категория - скажет
        {
            dialog.text = "От лица нашего прихода благодарю тебя за этот дар. И в благодарность я хочу предупредить тебя, сын мой: нехорошие люди затеяли против тебя недоброе. Я слышал, как эти мерзкие богоотступники договаривались потопить твой корабль при выходе из нашего порта\nОни уже снарядили судно и готовятся тебя атаковать. Будь осторожен, сын мой, эти заблудшие души не шутили - следует ожидать нападения. Ступай с моим благословением!";
            link.l1 = "Спасибо, святой отец. Я буду внимателен.";
            link.l1.go = "Padre_exit";
            AddMoneyToCharacter(pchar, -iTemp);
        }
        if (iTemp > 10000) //3 категория - расскажет полностью
        {
            dialog.text = "Ты очень щедр, сын мой. Скромность, подобающая слугам Господа нашего, не позволяет мне принять всю сумму, которой ты готов пожертвовать ради нашей церкви. Я возьму только 10 000 песо\nИ в благодарность я хочу предупредить тебя, сын мой: нехорошие люди затеяли против тебя недоброе. Я слышал, как эти мерзкие богоотступники договаривались потопить твой корабль при выходе из нашего порта\nОни снарядили люггер, под названием '" + pchar.questTemp.Regata.BranderName + "', и намереваются атаковать тебя, под английским флагом, чтобы ты не понял, что к чему. Будь осторожен, сын мой, эти заблудшие души не шутили - следует ожидать нападения\nУничтожь их - я заранее отпускаю тебе этот грех. Ступай с моим благословением! Я буду молиться за тебя, сын мой.";
            link.l1 = "Спасибо, святой отец. Я буду внимателен. Если эти мерзавцы осмелятся - я отправлю их прямиком в ад!";
            link.l1.go = "Padre_exit";
            AddMoneyToCharacter(pchar, -10000);
            ChangeCharacterComplexReputation(pchar, "nobility", 2);
        }
        break;

    case "Regata_Padre_exit":
        dialog.text = "Не гневайся, сын мой. Гнев - это грех. Если ты не желаешь пожертвовать на благо церкви - то это твое решение и твое право. Ступай с миром, сын мой.";
        link.l1 = "Всего доброго, святой отец.";
        link.l1.go = "Padre_exit";
        ChangeCharacterComplexReputation(pchar, "nobility", -1);
        break;

    case "Padre_exit":
        DialogExit();
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "SentJons_church", "barmen", "stay", "ReturnRegataPadreNorm", 5);
        break;

    case "Regata_Spyglass":
        dialog.text = "Здравствуйте, капитан! Меня зовут " + npchar.name + ", и я бы хотела...";
        link.l1 = "...предложить вам кое-что... Правильно, девушка?";
        link.l1.go = "Regata_Spyglass_1";
        break;

    case "Regata_Spyglass_1":
        dialog.text = "Ну конечно же, капитан! А чему вы удивляетесь? Вы - моряк видный, участвуете в регате - конечно, все хотят вам что-нибудь продать, необходимое в морском деле.";
        link.l1 = "Ладно, красавица, уговорила. Что там у тебя?";
        link.l1.go = "Regata_Spyglass_2";
        break;

    case "Regata_Spyglass_2":
        if (drand(11) > 10) //отличная труба
        {
            pchar.questTemp.Regata.Spy = "spyglass4";
            sTemp = "отличная подзорная труба";
            pchar.questTemp.Regata.SpyPrice = 20000;
            pchar.questTemp.Regata.SpyIndex = 12; //выигрыш - 12 часов
        }
        else
        {
            if (drand(11) < 6) //обычная труба
            {
                pchar.questTemp.Regata.Spy = "spyglass2";
                sTemp = "обычная подзорная труба";
                pchar.questTemp.Regata.SpyPrice = 1800;
                pchar.questTemp.Regata.SpyIndex = 4; //выигрыш - 4 часа
            }
            else //хорошая труба - как пригодится
            {
                pchar.questTemp.Regata.Spy = "spyglass3";
                sTemp = "хорошая подзорная труба";
                pchar.questTemp.Regata.SpyPrice = 10000;
                pchar.questTemp.Regata.SpyIndex = 8; //выигрыш - 8 часов
            }
        }
        dialog.text = "Вот, посмотрите. Она мне досталась от отца, он тоже был моряком, как и вы. Мне она не нужна, а вам может пригодиться. И прошу я за нее всего лишь " + FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice)) + ".";
        if (sti(pchar.money) >= sti(pchar.questTemp.Regata.SpyPrice))
        {
            link.l1 = "Так-так... " + sTemp + "! Очень интересно. Пожалуй, я куплю ее у вас. В том числе, и за ваши красивые глаза. Вы хотите за нее " + FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice)) + "? Пожалуйста, получите.";
            link.l1.go = "Regata_Spyglass_3";
        }
        link.l2 = "Хм... " + sTemp + "? Нет, девушка, извините, но мне эта вещь не нужна. У меня уже есть подзорная труба, и весьма неплохая. Так что... увы!";
        link.l2.go = "Regata_Spyglass_exit";
        break;

    case "Regata_Spyglass_3":
        AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.SpyPrice));
        GiveItem2Character(pchar, pchar.questTemp.Regata.Spy);
        dialog.text = "Благодарю вас, капитан. Надеюсь, эта вещь вам хорошо послужит. Рада, что она оказалась вам полезной. Удачи в регате!";
        link.l1 = "Спасибо, " + npchar.name + "! До свидания.";
        link.l1.go = "Spyglass_exit";
        for (i = 1; i <= 5; i++)
        {
            if (i == 1)
                sTemp = "a";
            if (i == 2)
                sTemp = "b";
            if (i == 3)
                sTemp = "c";
            if (i == 4)
                sTemp = "d";
            if (i == 5)
                sTemp = "e";
            pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)) + sti(pchar.questTemp.Regata.SpyIndex); //купил трубу - выиграл время
            log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
        }
        break;

    case "Regata_Spyglass_exit":
        dialog.text = "Жаль, очень жаль, капитан. А я надеялась, что она вам пригодится. Ну, попробую продать ее кому-нибудь еще. До свидания!";
        link.l1 = "До свидания, " + npchar.name + ".";
        link.l1.go = "Spyglass_exit";
        pchar.questTemp.Regata.AdversaryFourthTransition.Time.c = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.c) - sti(pchar.questTemp.Regata.SpyIndex); //третий соперник выиграл время
        break;

    case "Spyglass_exit":
        DialogExit();
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10);
        bDisableFastReload = false;
        chrDisableReloadToLocation = false;
        break;

    case "Regata_SiegeOfficer":
        dialog.text = "Здравствуйте, капитан. Вы ведь участник скоростной регаты? Так?";
        link.l1 = "Да. А в чем дело, офицер?";
        link.l1.go = "Regata_SiegeOfficer_1";
        break;

    case "Regata_SiegeOfficer_1":
        dialog.text = "Вы, наверное, в курсе, что нашу колонию осадили испанцы. Именно по этому вопросу с вами хотел бы поговорить наш губернатор. Не откажите в любезности нанести ему визит, прямо сейчас - дело очень срочное, я бы сказал - безотлагательное.";
        link.l1 = "Хм... Конечно, я отправлюсь к его светлости немедленно, хотя и не понимаю, какое я могу иметь отношение к военным действиям.";
        link.l1.go = "Regata_SiegeOfficer_2";
        break;

    case "Regata_SiegeOfficer_2":
        dialog.text = "Самое прямое, капитан. Давайте не будем терять времени и пройдем в резиденцию. Следуйте за мной.";
        link.l1 = "Да, конечно, офицер. Отправляемся.";
        link.l1.go = "Regata_SiegeOfficer_3";
        break;

    case "Regata_SiegeOfficer_3":
        DialogExit();
        LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Bridgetown_townhall", "goto", "governor1", "RegataSiegeHover", -1);
        break;

    case "Regata_SiegeOfficer_4":
        dialog.text = "Сэр! Я готов препроводить гражданское население вам на корабль. Мы отправляемся?";
        link.l1 = "Да, конечно. Отплываем немедленно. Доставляйте людей к шлюпкам.";
        link.l1.go = "Regata_SiegeOfficer_5";
        break;

    case "Regata_SiegeOfficer_5":
        DialogExit();
        LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "RegataSiegeOpen", -1);
        for (i = 1; i <= 9; i++)
        {
            sld = characterFromId("RegataBridgWom_" + i);
            LAi_SetActorType(sld);
            LAi_ActorGoToLocation(sld, "quest", "quest1", "none", "", "", "", 30);
        }
        break;

    case "Regata_SiegeOfficer_6":
        dialog.text = "Отбились... Очевидно, что этот шлюп - курьер эскадры, а эти кастильские негодяи - разведывательный отряд. Капитан, помогите мне довести женщин до пещеры - не исключено, что это не единственный испанский отряд.";
        link.l1 = "Хорошо. Немедля отправляемся в путь!";
        link.l1.go = "Regata_SiegeOfficer_7";
        break;

    case "Regata_SiegeOfficer_7":
        DialogExit();
        sld = characterFromId("SiegeOfficer");
        LAi_ActorFollowEverywhere(sld, "", -1);
        pchar.quest.Regata_Siege3.win_condition.l1 = "location";
        pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
        pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
        break;

    case "Regata_SiegeOfficer_8":
        dialog.text = "Спасибо вам огромное за помощь, капитан! Если бы не вы, и не ваша отвага... Вы настоящий герой - невзирая на опасности, пренебрегая своими личными целями, блестяще выполнили операцию. Я тут подумал по дороге... есть возможность отблагодарить вас  - ведь вы участвуете в регате.";
        link.l1 = "Очень интересно. Что за возможность?";
        link.l1.go = "Regata_skiper";
        break;

    case "Regata_Hovernor":
        dialog.text = "Здравствуйте, капитан " + GetFullName(pchar) + ". Очень хорошо, что вы пришли. Нашему городу нужна ваша помощь.";
        link.l1 = "Сэр, если речь идет про напавшую на вашу колонию испанскую военную эскадру, то я не представляю, в чем будет выражаться моя помощь. Я командую люггером, а не линейным кораблем...";
        link.l1.go = "Regata_Hovernor_1";
        break;

    case "Regata_Hovernor_1":
        dialog.text = "Выслушайте меня, капитан, и вы все поймете. Мы попали в очень сложное положение. Город с моря осаждает испанская эскадра, и вот-вот начнет решающий бой с фортом. Кроме того, испанцы высадили на маяке десантную групиировку из нескольких сотен человек и блокировали выходы из города в джунгли, видимо, для того, чтобы атаковать нас с двух сторон - с моря и суши\nГарнизон форта готовится к обороне с моря, а солдат в городе недостаточно - мы не можем снять блокаду с суши... Все мужское население, способное носить оружие, мобилизовано, и все готовы к решающей схватке, но у нас в городе не только мужчины\nВ Бриджтауне остались почти сто душ женского населения. Вы представляете, что с ними будет, если мы не сможем отстоять колонию и испанцы захватят город? Думаю, подробно рассказывать вам не нужно.";
        link.l1 = "Сэр, это все понятно, но чем я могу вам помочь? Чего вы хотите от меня? Чтобы я вступил в бой с линейными кораблями или записался со своей командой в городское ополчение?";
        link.l1.go = "Regata_Hovernor_2";
        break;

    case "Regata_Hovernor_2":
        switch (sti(Pchar.BaseNation))
        {
        case ENGLAND:
            sTemp = "Вы же англичанин, помогите спасти английских мирных граждан, тем более - женщин!" break;
        case FRANCE:
            sTemp = "Вы же француз, по сути - наш союзник, помогите спасти английских мирных граждан, тем более - женщин!" break;
        case SPAIN:
            sTemp = "Я знаю, вы испанец, и там в море - ваши соотечественники, но вы участвуете в ангийской регате под английским флагом. Да и разве вы считаете правильным воевать против мирного населения, против женщин? Помогите им!" break;
        case HOLLAND:
            sTemp = "Я знаю, вы голландец, и наши страны враждуют, но вы участвуете в ангийской регате под английским флагом. Да и разве вы считаете правильным воевать против мирного населения, против женщин? Помогите им!" break;
        }
        dialog.text = "Ни то, ни другое. Я прошу вас только об одном: вывезите на своем корабле из города женщин и детей. Их немного, примерно сто человек. Доставьте их на мыс Гаррисон, вместе с лейтенантом Махойни, а он проведет их в глубь острова и укроет в пещере\nУверен, что испанцы не станут их разыскивать. У меня совершенно нет кораблей - все, что имелись, были потоплены испанской эскадрой. У меня одна надежда на вас. Вам потребуется всего один рейс, они все разместятся в трюме вашего корабля, пусть и с большим перегрузом - вы успеете до атаки. Линейные корабли не смогут догнать ваш люггер, да и не станут этого делать\nМне больше некого просить. " + sTemp + "";
        link.l1 = "Сэр, извините, но мой корабль перегружен, и не выдержит такого количества пассажиров, даже в два рейса. Любое случайное ядро, даже упавшее рядом, отправит мой корабль вместе с вашими женщинами на дно. Простите, но я ничем не могу вам помочь.";
        link.l1.go = "Regata_Hovernor_exit";
        link.l2 = "Конечно, сэр. Я помогу вам. Честь моряка просто обязывает меня это сделать.";
        link.l2.go = "Regata_Hovernor_3";
        break;

    case "Regata_Hovernor_3":
        dialog.text = "Я рад, что вы согласились. Вы настоящий солдат. Лейтенант Махойни займется доставкой пассажирок на ваш корабль. И да поможет вам Бог!";
        link.l1 = "Спасибо, сэр. Не будем терять драгоценное время!";
        link.l1.go = "Regata_Hovernor_4";
        break;

    case "Regata_Hovernor_wait":
        dialog.text = "Поторопитесь, капитан! Время не ждет.";
        link.l1 = "Уже отплываю!";
        link.l1.go = "exit";
        NextDiag.TempNode = "Regata_Hovernor_wait";
        break;

    case "Regata_Hovernor_exit":
        dialog.text = "Я просто поражен... Вы не хотите даже попытаться? Ну что же, это ваше право. Я не могу ничего от вас требовать. Будь вы простым капитаном, я бы не колеблясь конфисковал ваше судно ради спасения сотни женщин, но... вы находитесь под протекцией генерал-губернатора английских колоний как участник регаты\nЯ надеялся на вашу совесть и просчитался. Ступайте, и да смилуется Господь над вашей душой в день Страшного Суда!";
        link.l1 = "Прощайте, сэр.";
        link.l1.go = "Hovernor_exit";
        break;

    case "Hovernor_exit":
        DialogExit();
        pchar.questTemp.Regata.AdversaryFifthTransition.Time.e = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.e) - 36; //пятый противник выиграл 36 часов
        ChangeCharacterComplexReputation(pchar, "nobility", -8);
        ChangeCharacterNationReputation(pchar, ENGLAND, -5);
        //вертаем губера в норму
        npchar.Dialog.Filename = "Common_Mayor.c";
        npchar.dialog.currentnode = "First time";
        //удаляем лейтенанта
        sld = characterFromId("SiegeOfficer");
        sld.lifeday = 0;
        //открываем ворота и выход в море
        bDisableFastReload = false;
        LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
        LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
        LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
        LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
        LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
        //остров в норму
        n = FindIsland("Barbados");
        DeleteAttribute(Islands[n], "DontSetShipInPort");
        //осаду снимем через 5 дней
        SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
        for (i = 1; i <= 9; i++) //девок счистим
        {
            sld = characterFromId("RegataBridgWom_" + i);
            sld.lifeday = 0; // patch-7
            LAi_CharacterDisableDialog(sld);
        }
        break;

    case "Regata_Hovernor_4":
        DialogExit();
        NextDiag.CurrentNode = "Regata_Hovernor_wait";
        sld = characterFromId("SiegeOfficer");
        LAi_SetActorType(sld);
        LAi_ActorGoToLocation(sld, "reload", "reload2", "Bridgetown_town", "goto", "goto4", "", 10);
        pchar.quest.Regata_evacuation.win_condition.l1 = "location";
        pchar.quest.Regata_evacuation.win_condition.l1.location = "Bridgetown_town";
        pchar.quest.Regata_evacuation.function = "RegataSiegeEvacuation";
        break;

    case "Regata_BridgWom":
        dialog.text = "Испанцы наступают! Господи, смилуйся над нами!";
        link.l1 = "...";
        link.l1.go = "exit";
        NextDiag.TempNode = "Regata_BridgWom";
        break;

    case "Regata_BridgWom_1":
        dialog.text = "Лейтенант Махойни погиб... какой кошмар. Он был отважным офицером. Капитан, вы проведете нас в пещеру? Только доведите, а дальше мы сами о себе позаботимся.";
        link.l1 = "Конечно. Следуйте за мной!";
        link.l1.go = "Regata_BridgWom_2";
        break;

    case "Regata_BridgWom_2":
        DialogExit();
        for (i = 1; i <= 9; i++)
        {
            sld = characterFromId("RegataBridgWom_" + i);
            LAi_SetActorType(sld);
            LAi_ActorFollowEverywhere(sld, "", -1);
        }
        pchar.quest.Regata_Siege3.win_condition.l1 = "location";
        pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
        pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
        break;

    case "Regata_BridgWom_3":
        dialog.text = "Вот мы и на месте... Спасибо вам огромное, капитан! Вы просто спасли всех нас! Я тут подумала по дороге... есть возможность отблагодарить вас  - ведь вы участвуете в регате?";
        link.l1 = "Да, участвую. И что это за возможность?";
        link.l1.go = "Regata_skiper";
        break;

    case "Regata_skiper":
        pchar.questTemp.Regata.Name = GetFullName(npchar);
        dialog.text = "Ваш путь лежит в Порт-Рояль? Самый короткий путь - через Кюрасао. Вернитесь в Бриджтаун. Там найдите человека по имени Вудро Доггерти - он старый моряк и опытный лоцман. Он как свои пять пальцев знает воды между Барбадосом и Кюрасао и проведет ваш корабль кратчайшим путем\nВы сэкономите на этом время, столь необходимое вам для победы. Найти Вудро вы скорее всего сможете в церкви. Скажете, что вас прислал" + NPCharSexPhrase(NPChar, "", "а") + " " + GetFullName(npchar) + " - он вам не откажет. Высадите его потом в Порт-Рояле - он все равно туда собирался.";
        link.l1 = "Очень хорошо! Толковый лоцман мне и впрямь пригодится. Ну, а на теперь - прощайте. Мне пора отправляться в обратный путь.";
        link.l1.go = "Regata_skiper_1";
        break;

    case "Regata_skiper_1":
        dialog.text = "До свидания, капитан! Удачи вам!";
        link.l1 = "Может, еще встретимся...";
        link.l1.go = "Regata_skiper_2";
        break;

    case "Regata_skiper_2":
        DialogExit();
        ChangeCharacterComplexReputation(pchar, "nobility", 10);
        ChangeCharacterNationReputation(pchar, ENGLAND, 10);
        LAi_SetStayType(npchar);
        LAi_CharacterDisableDialog(npchar);
        npchar.lifeday = 0; // patch-8
        for (i = 1; i <= 9; i++)
        {
            sld = characterFromId("RegataBridgWom_" + i);
            LAi_SetStayType(sld);
            LAi_CharacterDisableDialog(sld);
            sld.lifeday = 0; // patch-8
        }
        //вертаем губера в норму
        sld = characterFromId("Bridgetown_Mayor");
        sld.Dialog.Filename = "Common_Mayor.c";
        sld.dialog.currentnode = "First time";
        //открываем ворота и выход в море
        LocatorReloadEnterDisable("Shore4", "boat", false);
        LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
        LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
        LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
        LocatorReloadEnterDisable("Barbados_cave", "reload1", false);
        bQuestDisableMapEnter = false;
        //осаду снимем через 5 дней
        SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
        RegataSiegeSkiper(); //поставим Вудро в церковь
        break;

    case "Regata_SiegeSkiper":
        dialog.text = "Здравствуйте. Вы что-то хотели?";
        link.l1 = "Вас зовут Вудро Доггерти, правильно?";
        link.l1.go = "Regata_SiegeSkiper_1";
        break;

    case "Regata_SiegeSkiper_1":
        dialog.text = "Да, это так. Чем могу служить?";
        link.l1 = "Мне известно, что вы опытный штурман и хорошо знаете воды между Барбадосом и Кюрасао. Также мне известно, что вам нужно в Порт-Рояль. Я - участник регаты, мне предстоит последний переход как раз до Порт-Рояля, и я хочу попросить вас войти в мою команду в качестве штурмана и лоцмана на этот переход.";
        link.l1.go = "Regata_SiegeSkiper_2";
        break;

    case "Regata_SiegeSkiper_2":
        dialog.text = "Очень интересно... А почему вы считаете, что я пойду на ваш корабль?";
        link.l1 = "Ну, потому что я узнал это от человека по имени " + pchar.questTemp.Regata.Name + ", с уверением, что вы мне не откажете. И потому что я, как-никак, оказал услугу городу Бриджтаун в этот трудный момент...";
        link.l1.go = "Regata_SiegeSkiper_3";
        break;

    case "Regata_SiegeSkiper_3": //а тут - как уж свезет
        if (drand(2) != 2)
        {
            dialog.text = "От " + pchar.questTemp.Regata.Name + "? Это, конечно, всё проясняет. Хорошо, капитан, я помогу проложить вам кратчайший путь от Бриджтауна до Порт-Рояля. Вы отправляетесь прямо сейчас?";
            link.l1 = "Да, конечно. Судно готово к отплытию.";
            link.l1.go = "Regata_SiegeSkiper_4";
        }
        else
        {
            dialog.text = "От " + pchar.questTemp.Regata.Name + "? Ну, тогда понятно. Но, капитан, к сожалению я не могу покинуть мой город в это опасное время. Как солдат, оказавший нам бескорыстную помощь, вы должны это понимать\nЯ не хочу, чтобы потом люди шептались у меня за спиной, мол, Вудро сбежал из города перед решающей битвой с испанцами. Я остаюсь и буду защищать мой город. Не обессудьте, капитан.";
            link.l1 = "Это ваше окончательное решение? Но я же помог вашей колонии...";
            link.l1.go = "Regata_SiegeSkiper_6";
        }
        break;

    case "Regata_SiegeSkiper_4":
        dialog.text = "Тогда не будем терять времени. Я захвачу из дома вещи и выдвигаюсь на ваш корабль.";
        link.l1 = "Матросы встретят вас на пирсе и доставят на 'Санта-Катерину'. Спасибо, Вудро!";
        link.l1.go = "SiegeSkiper_hire";
        break;

    case "Regata_SiegeSkiper_6":
        dialog.text = "Капитан, регата - это спорт, а осада испанцами моего города - это жизнь. Я никуда с вами не поплыву. И повторюсь - вы должны меня понять как никто другой - вам известны понятия 'честь' и 'долг'. Это мое окончательное решение и менять его я не намерен.";
        link.l1 = "Что же... Очень жаль. Прощайте, Вудро.";
        link.l1.go = "SiegeSkiper_exit";
        break;

    case "SiegeSkiper_exit":
        DialogExit();
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
        npchar.lifeday = 0;
        break;

    case "SiegeSkiper_hire":
        chrDisableReloadToLocation = true; //закрыть локацию
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
        npchar.quest.OfficerPrice = sti(pchar.rank) * 500;
        Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
        npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
        npchar.loyality = 25;
        npchar.Dialog.Filename = "Enc_Officer_dialog.c";
        AddDialogExitQuestFunction("LandEnc_OfficerHired");
        NextDiag.CurrentNode = NextDiag.TempNode;
        //пересчитываем время пятого перехода
        for (i = 1; i <= 5; i++)
        {
            if (i == 1)
                sTemp = "a";
            if (i == 2)
                sTemp = "b";
            if (i == 3)
                sTemp = "c";
            if (i == 4)
                sTemp = "d";
            if (i == 5)
                sTemp = "e";
            pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp)) + 18 + (rand(18)); //выигрыш до 1.5 суток
            log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
        }
        SetFunctionTimerCondition("SiegeSkiperOver", 0, 0, 15, false); //чтобы не присвоил офицера
        DialogExit();
        break;

    case "Regata_Finish":
        iTest = FindColony("Portroyal");
        if (iTest != -1)
        {
            rColony = GetColonyByIndex(iTest);
            sFrom_sea = rColony.from_sea;
        }
        ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok) //проверка на наличие корабля в порту
        {
            //снимаем запреты
            bQuestDisableMapEnter = false;                 //открыть карту
            DeleteAttribute(pchar, "GenQuest.CannotWait"); //можно мотать время
            if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Bridgetown") || GetCompanionQuantity(pchar) > 1 || sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_LUGGER || pchar.Ship.Name != "Сaнта-Kатepина")
            {
                dialog.text = "Вы нарушили правила регаты, на самом последнем этапе. Ваш результат дисквалифицирован. Мне больше нечего вам сказать, капитан.";
                link.l1 = "Эх... жаль! Ладно, ничего не поделаешь - вы оказались бдительны. Прощайте!";
                link.l1.go = "exit";
                npchar.lifeday = 1;
                DeleteAttribute(pchar, "questTemp.Regata");
            }
            else
            {
                n = 1;
                for (i = 1; i <= 5; i++)
                {
                    if (i == 1)
                        sTemp = "a";
                    if (i == 2)
                        sTemp = "b";
                    if (i == 3)
                        sTemp = "c";
                    if (i == 4)
                        sTemp = "d";
                    if (i == 5)
                        sTemp = "e";
                    if (pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FifthTransitionTime))
                        n++;
                    pchar.questTemp.Regata.Result = n; //место в регате
                }
                if (n == 1)
                {
                    dialog.text = "Капитан " + GetFullName(pchar) + ", поздравляю вас с победой! Вы затратили на регату " + sti(pchar.questTemp.Regata.FifthTransitionTime) + " часов, оставив позади всех противников. Это отличный результат!";
                    link.l1 = "Спасибо за лестный отзыв, сэр!";
                    link.l1.go = "First_result";
                }
                else
                {
                    if (n == 6)
                    {
                        dialog.text = "Капитан, увы - но ваш результат последний - вы затратили на регату " + sti(pchar.questTemp.Regata.FifthTransitionTime) + " часов. Не огорчайтесь, у вас были действительно сильные противники.";
                        link.l1 = "Я не огорчаюсь, сэр. Я рад, что участвовал в регате и опробовал свои силы.";
                        link.l1.go = "Other_result";
                    }
                    else
                    {
                        dialog.text = "Капитан, вы заняли " + n + " место. Поздравляю с успешным прохождением маршрута, вы показали достойное время - " + sti(pchar.questTemp.Regata.FifthTransitionTime) + " часов. И хоть вы и не выиграли, я все равно поздравляю вас!";
                        link.l1 = "Я не огорчаюсь, сэр. Я рад, что показал неплохой результат в этом сложном противостоянии.";
                        link.l1.go = "Other_result";
                    }
                }
            }
            Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("SiegeSkiper");
            sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
            CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
            RemovePassenger(Pchar, sld);
            DeleteAttribute(sld, "Payment");
            DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX"); //удаляем из офицеров
            log_info("Вудро Доггерти сошел на берег");
            pchar.quest.SiegeSkiperOver.over = "yes"; //снять таймер
        }
        else
        {
            dialog.text = "Сэр, позвольте спросить - где ваш корабль? Я что-то его не наблюдаю...";
            link.l1 = "Прошу прощения, сэр. Я немедленно приведу свой корабль в порт.";
            link.l1.go = "exit";
            NextDiag.TempNode = "Regata_Finish";
        }
        break;

    case "First_result":
        if (CheckAttribute(pchar, "questTemp.Regata.Rate"))
            sTemp = "Потом зайдите ко мне в кабинет - я выдам выигрыш по вашей ставке.";
        else
            sTemp = "А если бы вы сделали ставку на свою победу, как я вам предлагал - получили бы еще и выигрыш.";
        dialog.text = "Завтра явитесь к генерал-губернатору - он вручит вам призы за регату - положенные деньги в размере 250 000 песо и ценные подарки. " + sTemp + " Не покидайте город - согласно традиции, если победитель не является за призами в течение недели, они передаются в городскую казну.";
        link.l1 = "Я все понял, сэр. Буду завтра на приеме!";
        link.l1.go = "First_result_1";
        break;

    case "First_result_1":
        DialogExit();
        //npchar.lifeday = 7;
        Achievment_SetStat(pchar, 9, 1);
        npchar.dialog.currentnode = "Other_result_repeat";
        pchar.questTemp.Regata.Win = "true";
        pchar.quest.Regata_Final.win_condition.l1 = "Timer";
        pchar.quest.Regata_Final.win_condition.l1.date.hour = 6.0;
        pchar.quest.Regata_Final.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
        pchar.quest.Regata_Final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
        pchar.quest.Regata_Final.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
        pchar.quest.Regata_Final.function = "RegataFinal";
        SetFunctionTimerCondition("RegataFinalOver", 0, 0, 8, false); //таймер не снимаем - через 8 дней подчистится все автоматически
        // слухи
        AddSimpleRumour("А, так это вы - легендарный капитан, победитель парусной регаты! Очень приятно вас видеть!", ENGLAND, 60, 10);
        AddSimpleRumour("Ха, да это же не кто иной, как повелитель ветра и волн, покоритель морских просторов, победитель парусной регаты! Мое вам уважение...", ENGLAND, 60, 10);
        AddSimpleRumour("О, сам великий мореплаватель, король ветра и моря, победитель парусной регаты почтил наш город своим визитом! Мы рады вам, капитан!", ENGLAND, 60, 10);
        AddSimpleRumour("О, да мне посчастливилось беседовать с настоящей живой легендой, капитаном, способным за три дня пересечь архипелаг даже при встречном ветре, победителем парусной регаты! Мое почтение, капитан!", ENGLAND, 60, 10);
        AddSimpleRumour("А, так это вы - легендарный капитан, победитель парусной регаты! Очень приятно вас видеть!", FRANCE, 60, 10);
        AddSimpleRumour("Ха, да это же не кто иной, как повелитель ветра и волн, покоритель морских просторов, победитель парусной регаты! Мое вам уважение...", FRANCE, 60, 10);
        AddSimpleRumour("О, сам великий мореплаватель, король ветра и моря, победитель парусной регаты почтил наш город своим визитом! Мы рады вам, капитан!", FRANCE, 60, 10);
        AddSimpleRumour("О, да мне посчастливилось беседовать с настоящей живой легендой, капитаном, способным за три дня пересечь архипелаг даже при встречном ветре, победителем парусной регаты! Мое почтение, капитан!", FRANCE, 60, 10);
        // экспа
        AddComplexSeaExpToScill(2000, 300, 300, 0, 500, 500, 0);
        AddCharacterExpToSkill(pchar, "Leadership", 2000); //авторитет
        AddCharacterExpToSkill(pchar, "Fortune", 1000);    //везение
        AddCharacterExpToSkill(pchar, "Sneak", 300);       //скрытность
        ChangeCharacterComplexReputation(pchar, "authority", 10);
        ChangeCharacterComplexReputation(pchar, "fame", 15);
        ChangeOfficersLoyality("good_all", 3);
        break;

    case "Other_result":
        dialog.text = "Приятно слышать этот достойный ответ. Удачи вам, капитан!";
        link.l1 = "Прощайте, сэр.";
        link.l1.go = "Other_result_1";
        break;

    case "Other_result_1":
        DialogExit();
        npchar.dialog.currentnode = "Other_result_repeat";
        SetFunctionTimerCondition("RegataFinalOver", 0, 0, 1, false);
        // экспа
        AddComplexSeaExpToScill(500, 100, 100, 0, 100, 100, 0);
        AddCharacterExpToSkill(pchar, "Leadership", 200); //авторитет
        AddCharacterExpToSkill(pchar, "Fortune", 100);    //везение
        AddCharacterExpToSkill(pchar, "Sneak", 100);      //скрытность
        ChangeCharacterComplexReputation(pchar, "authority", 1);
        ChangeCharacterComplexReputation(pchar, "fame", 1);
        break;

    case "Other_result_repeat":
        dialog.text = "Вы что-то еще хотели, капитан?";
        link.l1 = "Да нет, ничего.";
        link.l1.go = "exit";
        NextDiag.TempNode = "Other_result_repeat";
        break;

    case "Give_advantage":
        dialog.text = "А-а, вот и вы, уважаемый " + GetFullName(pchar) + ". Рад вас видеть. Вы пришли за вашим выигрышем? Он подготовлен.";
        link.l1 = "Приятно это слышать! Каков же размер моего дополнительного приза?";
        link.l1.go = "Give_advantage_1";
        break;

    case "Give_advantage_1":
        dialog.text = "С учетом сделанных ставок, ваш выигрыш составляет " + FindRussianMoneyString(makeint(pchar.questTemp.Regata.Advantage)) + ". Пожалуйста, получите. Поздравляю еще раз с победой!";
        link.l1 = "Спасибо!";
        link.l1.go = "Give_advantage_2";
        break;

    case "Give_advantage_2":
        AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Regata.Advantage));
        dialog.text = "Безусловно, ваша популярность среди жителей Порт-Рояля выросла. Думаю, вы вполне сможете это заметить... правда, память у людей короткая, увы. Так что купайтесь в лучах славы, пока они еще яркие!";
        link.l1 = "Интересные вещи вы говорите, сэр... Посмотрим, каково это - принимать ванны из лучей славы. До свидания! Рад был с вами познакомиться!";
        link.l1.go = "exit";
        NextDiag.TempNode = "Other_result_repeat";
        break;

    case "Regata_CitMan_1":
        if (CheckAttribute(pchar, "questTemp.Regata"))
        {
            if (CheckAttribute(pchar, "questTemp.Regata.Result"))
            {
                if (sti(pchar.questTemp.Regata.Result) == 1)
                {
                    dialog.text = "Поздравляю с победой, капитан! Великолепный результат!";
                    link.l1 = "Спасибо!";
                    link.l1.go = "exit";
                }
                else
                {
                    dialog.text = "Не расстраивайтесь, капитан. Победить в регате - сложно, и даже просто участие в ней принесло вам почет!";
                    link.l1 = "Не переживайте за меня. Я доволен своим результатом.";
                    link.l1.go = "exit";
                }
            }
            else
            {
                dialog.text = "С прибытием, капитан! Сейчас вам надо отметится у сэра Стивенсона.";
                link.l1 = "Понятно. Иду к нему!";
                link.l1.go = "exit";
            }
        }
        else
        {
            dialog.text = "Эх, капитан, что же вы так оплошали, да на самом последнем этапе!";
            link.l1 = "Да уж, ничего не скажешь...";
            link.l1.go = "exit";
        }
        NextDiag.TempNode = "Regata_CitMan_1";
        break;

    case "Regata_CitWom_1":
        if (CheckAttribute(pchar, "questTemp.Regata"))
        {
            if (CheckAttribute(pchar, "questTemp.Regata.Result"))
            {
                if (sti(pchar.questTemp.Regata.Result) == 1)
                {
                    dialog.text = "Поздравляю с победой, капитан! Великолепный результат!";
                    link.l1 = "Спасибо!";
                    link.l1.go = "exit";
                }
                else
                {
                    dialog.text = "Не расстраивайтесь, капитан. Победить в регате - сложно, и даже просто участие в ней принесло вам почет!";
                    link.l1 = "Не переживайте за меня. Я доволен своим результатом.";
                    link.l1.go = "exit";
                }
            }
            else
            {
                dialog.text = "С прибытием, капитан! Сейчас вам надо отметится у сэра Стивенсона.";
                link.l1 = "Понятно. Иду к нему!";
                link.l1.go = "exit";
            }
        }
        else
        {
            dialog.text = "Эх, капитан, что же вы так оплошали, да на самом последнем этапе!";
            link.l1 = "Да уж, ничего не скажешь...";
            link.l1.go = "exit";
        }
        NextDiag.TempNode = "Regata_CitWom_1";
        break;

    case "Regata_CitHorse_1":
        if (CheckAttribute(pchar, "questTemp.Regata"))
        {
            if (CheckAttribute(pchar, "questTemp.Regata.Result"))
            {
                if (sti(pchar.questTemp.Regata.Result) == 1)
                {
                    dialog.text = "Поздравляю с победой, капитан! Великолепный результат!";
                    link.l1 = "Спасибо!";
                    link.l1.go = "exit";
                }
                else
                {
                    dialog.text = "Не расстраивайтесь, капитан. Победить в регате - сложно, и даже просто участие в ней принесло вам почет!";
                    link.l1 = "Не переживайте за меня. Я доволен своим результатом.";
                    link.l1.go = "exit";
                }
            }
            else
            {
                dialog.text = "С прибытием, капитан! Сейчас вам надо отметится у сэра Стивенсона.";
                link.l1 = "Понятно. Иду к нему!";
                link.l1.go = "exit";
            }
        }
        else
        {
            dialog.text = "Эх, капитан, что же вы так оплошали, да на самом последнем этапе!";
            link.l1 = "Да уж, ничего не скажешь...";
            link.l1.go = "exit";
        }
        NextDiag.TempNode = "Regata_CitHorse_1";
        break;

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;
    }
}

void CreateRegataAdversaries()
{
    string sTemp;
    for (int i = 0; i <= 4; i++)
    {
        if (i == 0)
            sTemp = "a";
        if (i == 1)
            sTemp = "b";
        if (i == 2)
            sTemp = "c";
        if (i == 3)
            sTemp = "d";
        if (i == 4)
            sTemp = "e";
        pchar.questTemp.Regata.AdversaryName.(sTemp) = GenerateRandomName_Generator(i, "man");
        pchar.questTemp.Regata.AdversaryShipName.(sTemp) = GenerateRandomNameToShip(ENGLAND);
        pchar.questTemp.Regata.AdversarySpeed.(sTemp) = 0.4 + frand(0.9);
        log_testinfo(FindRussianDaysString(stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp))));
    }
}