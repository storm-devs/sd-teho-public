
void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag, forName;
    string sTemp, sGem, sTitle;
    int iTemp;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
    case "First time":
        dialog.text = "Не о чем говорить.";
        link.l1 = "Ладно...";
        link.l1.go = "exit";
        NextDiag.TempNode = "First time";
        break;

    case "CitizenNotBlade":
        if (LoadedLocation.type == "town")
        {
            dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнаженным клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
            link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
        }
        else
        {
            dialog.text = NPCharSexPhrase(NPChar, "Острожней на поворотах, " + GetSexPhrase("приятель", "подруга") + ", когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда " + GetSexPhrase("мужчины", "всякие тут") + " ходят передо мной с оружием на изготовку. Это меня пугает...");
            link.l1 = RandPhraseSimple("Понял" + GetSexPhrase("", "а") + ".", "Убираю.");
        }

        link.l1.go = "exit";
        break;

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    //--------------------------- квест официантки --------------------------------
    //грабитель
    case "WaitressBerglar":
        dialog.text = "Давай, приятель, выворачивай карманы.";
        link.l1 = "Чего?!";
        link.l1.go = "WaitressBerglar_1";
        break;
    case "WaitressBerglar_1":
        dialog.text = "Того! Давай быстрей, без разговоров. Не люблю я этого...";
        link.l1 = "Вот это подстава!! А " + pchar.questTemp.different.FackWaitress.Name + " с тобой в паре работает, что ли?";
        link.l1.go = "WaitressBerglar_2";
        break;
    case "WaitressBerglar_2":
        dialog.text = "В паре, в паре... Выворачивай карманы, не то зарежу ведь!";
        link.l1 = "Черта с два! За свои карманы я сам кого хочешь зарежу...";
        link.l1.go = "WaitressBerglar_fight";
        link.l2 = "Забирай, паршивец! Но это вам так просто с рук не сойдет...";
        link.l2.go = "WaitressBerglar_take";
        break;
    case "WaitressBerglar_take":
        dialog.text = "Конечно, не сойдет, кто же спорит? Ну, прощай дружище. И помни - не такой ты красавец, чтобы на тебя официантки с ходу вешались. Впредь будешь умней!";
        link.l1 = "Это точно!..";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("WaitressFack_outRoom");
        break;
    case "WaitressBerglar_fight":
        dialog.text = "Ну, как знаешь...";
        link.l1 = "Знаю, знаю, приятель...";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("WaitressFack_fight");
        break;
    //официантка
    case "Waitress":
        dialog.text = "А вот и я! Не соскучился, красавчик?";
        link.l1 = "Не успел...";
        link.l1.go = "Waitress_1";
        break;
    case "Waitress_1":
        dialog.text = "Ну, тогда не будем терять времени!";
        link.l1 = "Хе, согласен!";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("WaitressFack_fack");
        break;

    //--------------------------- догнать кэпа, потерявшего судовой журнал --------------------------------
    //встретил в городе
    case "PortmansCap":
        dialog.text = "Здравствуйте. Меня зовут " + GetFullName(npchar) + ". Я капитан " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Acc")) + " '" + npchar.Ship.name + "'.";
        link.l1 = "Отлично! Наконец-то я тебя наш" + GetSexPhrase("ел", "ла") + "...";
        link.l1.go = "PortmansCap_1";
        break;
    case "PortmansCap_1":
        dialog.text = "Наш" + GetSexPhrase("ел", "ла") + "?!";
        link.l1 = "Ага. В общем, я привез" + GetSexPhrase("", "ла") + " тебе твой судовой журнал. Который ты забыл у начальника порта " + XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen") + ".";
        link.l1.go = "PortmansCap_2";
        break;
    case "PortmansCap_2":
        dialog.text = "Дьявол, так вот где я его 'посеял'! Да уж, эта пропажа чуть было не привела к бунту на корабле...";
        link.l1 = "Ну, все хорошо, что хорошо кончается. Забирай свой журнал и давай поговорим о моем гонораре за труды.";
        link.l1.go = "PortmansCap_3";
        break;
    case "PortmansCap_3":
        if (sti(npchar.quest.stepsQty) == 1)
        {
            dialog.text = "Новый журнал я еще не завел, как раз собирался, поэтому заплачу максимум из того, что могу себе позволить. " + FindRussianMoneyString(sti(npchar.quest.money)) + " и немного моих личных драгоценностей.";
            link.l1 = "Ну, неплохо. Забирай свой журнал.";
            link.l1.go = "PortmansCap_4";
        }
        else
        {
            if (sti(npchar.quest.stepsQty) < 5)
            {
                npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
                dialog.text = "Хм, ты знаешь, я уже завел новый журнал. Тем не менее, старый журнал мне нужен еще, необходимо все перенести в новый. Так что я могу забрать его за " + FindRussianMoneyString(sti(npchar.quest.money)) + ". и немного моих личных драгоценностей.";
                link.l1 = "Ну что же, договорились. Забирай свой журнал!";
                link.l1.go = "PortmansCap_4";
            }
            else
            {
                dialog.text = "Так я завел новый журнал уже. И все записи старого по памяти перенес туда, два дня сидел и писал. Так что мне старый журнал теперь попросту не нужен. И ничего заплатить за него я не могу.";
                link.l1 = "Вообще ничего? Что я, зря за тобой гонял" + GetSexPhrase("ся", "ась") + "?";
                link.l1.go = "PortmansCap_5";
            }
        }
        break;
    case "PortmansCap_4":
        dialog.text = "Спасибо тебе. Ну, всего хорошего, " + GetSexPhrase("приятель", "подруга") + ".";
        link.l1 = "И тебе того же...";
        link.l1.go = "exit";
        sTemp = "Timer_" + npchar.id;
        pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
        npchar.LifeDay = 2;               // через пару дней снимаем кэпа
        SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
        group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
        sld = characterFromId(npchar.quest.firstCity + "_PortMan");
        sTitle = sld.id + "PortmansBook_Delivery";
        AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Dat"));
        AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
        CloseQuestHeader(sTitle);
        sGem = pchar.questTemp.PortmansJornal.gem;
        TakeNItems(pchar, sGem, 12 + drand(10));
        DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
        DeleteAttribute(sld, "quest.PortmansJornal");
        sld.quest = ""; //освобождаем личный флаг квеста для портмана
        AddCharacterExpToSkill(pchar, "Repair", makeint(400 / sti(npchar.quest.stepsQty)));
        AddMoneyToCharacter(pchar, sti(npchar.quest.money));
        ChangeCharacterComplexReputation(pchar, "nobility", 2);
        TakeItemFromCharacter(pchar, "PortmansBook");
        NextDiag.TempNode = "PortmansCap_inDeck_over";
        break;
    case "PortmansCap_5":
        dialog.text = "Хе, если уж взял" + GetSexPhrase("ся", "ась") + " догонять, то надо быть расторопней.";
        link.l1 = "Гм, тоже верно... Ну ладно, забирай свой журнал просто так.";
        link.l1.go = "exit";
        sTemp = "Timer_" + npchar.id;
        pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
        npchar.LifeDay = 2;               // через пару дней снимаем кэпа
        SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
        group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
        sld = characterFromId(npchar.quest.firstCity + "_PortMan");
        sTitle = sld.id + "PortmansBook_Delivery";
        AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Dat"));
        AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
        CloseQuestHeader(sTitle);
        DeleteAttribute(sld, "quest.PortmansJornal");
        sld.quest = ""; //освобождаем личный флаг квеста для портмана
        AddCharacterExpToSkill(pchar, "Repair", makeint(200 / sti(npchar.quest.stepsQty)));
        TakeItemFromCharacter(pchar, "PortmansBook");
        NextDiag.TempNode = "PortmansCap_inDeck_over";
        break;
    //догнал в море
    case "PortmansCap_inDeck":
        if (isBadReputation(pchar, 20))
        {
            dialog.text = "Приветствую тебя на палубе моего судна. Честно говоря, я уж, было, испугался - решил, что это Одноглазый Стид Хантер решил поохотиться за мной...";
            link.l1 = "Де нет, приятель, сегодня я добр" + GetSexPhrase("ый", "ая") + ". Я разыскивал" + GetSexPhrase("", "а") + " тебя, чтобы помочь.";
        }
        else
        {
            dialog.text = "Приветствую тебя на моей палубе! Что ты хотел" + GetSexPhrase("", "а") + "?";
            link.l1 = "Разыскивал" + GetSexPhrase("", "а") + " тебя, приятель. Еле нагнал" + GetSexPhrase("", "а") + "...";
        }
        link.l1.go = "PortmansCap_inDeck_1";
        break;
    case "PortmansCap_inDeck_1":
        dialog.text = "Разыскивал" + GetSexPhrase("", "а") + "? А зачем?";
        link.l1 = "Ты забыл свой судовой журнал у начальника порта " + XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen") + ". Журнал у меня! Поэтому и разыскивал" + GetSexPhrase("", "а") + ", чтобы отдать.";
        link.l1.go = "PortmansCap_inDeck_2";
        break;
    case "PortmansCap_inDeck_2":
        if (sti(npchar.quest.stepsQty) == 1)
        {
            dialog.text = "Черт, так, значит, вот где я его потерял!.. Это ценная услуга, " + GetSexPhrase("дружище, ", "") + "нет слов. А то я чуть капитанского статуса не лишился... Большое тебе спасибо.";
            link.l1 = "Как насчет вознаграждения?";
            link.l1.go = "PortmansCap_inDeck_3";
        }
        else
        {
            if (sti(npchar.quest.stepsQty) < 5)
            {
                npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
                dialog.text = "Черт, так, значит, вот где я его потерял!.. Спасибо тебе, конечно, но дело в том, что ты долго меня искал" + GetSexPhrase("", "а") + ", и я уже завел новый. Однако, перенести кое-что мне оттуда нужно, поэтому я заберу журнал у тебя. Но много заплатить не могу...";
                link.l1 = "А сколько можешь?";
                link.l1.go = "PortmansCap_inDeck_3";
            }
            else
            {
                dialog.text = "Черт, так, значит, вот где я его потерял!.. Спасибо тебе, конечно, но дело в том, что ты долго меня искал" + GetSexPhrase("", "а") + ", и я уже завел новый. Старые записи перенес по памяти, так что мне он не нужен.";
                link.l1 = "Что, вообще тебе старый журнал не нужен? Совсем?";
                link.l1.go = "PortmansCap_inDeck_5";
            }
        }
        break;
    case "PortmansCap_inDeck_3":
        dialog.text = "Я готов выплатить тебе " + FindRussianMoneyString(sti(npchar.quest.money)) + " и дать впридачу немного своих личных драгоценностей. Это все, что я могу себе позволить.";
        link.l1 = "Ну, хорошо. Вот твой журнал.";
        link.l1.go = "PortmansCap_inDeck_4";
        break;
    case "PortmansCap_inDeck_4":
        dialog.text = "Спасибо еще раз. Прощай, " + GetSexPhrase("дружище, ", "") + "и будь здоров" + GetSexPhrase("", "а") + ".";
        link.l1 = "И тебе здоровья.";
        link.l1.go = "exit";
        npchar.LifeDay = 30; // через десять дней снимаем кэпа
        SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
        npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
        sld = characterFromId(npchar.quest.firstCity + "_PortMan");
        sTitle = sld.id + "PortmansBook_Delivery";
        AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
        AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
        CloseQuestHeader(sTitle);
        sGem = pchar.questTemp.PortmansJornal.gem;
        TakeNItems(pchar, sGem, 12 + drand(10));
        DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
        DeleteAttribute(sld, "quest.PortmansJornal");
        sld.quest = ""; //освобождаем личный флаг квеста для портмана
        AddCharacterExpToSkill(pchar, "Sailing", makeint(200 / sti(npchar.quest.stepsQty)));
        AddMoneyToCharacter(pchar, sti(npchar.quest.money));
        ChangeCharacterComplexReputation(pchar, "nobility", 5);
        TakeItemFromCharacter(pchar, "PortmansBook");
        npchar.DeckDialogNode = "PortmansCap_inDeck_over";
        NextDiag.TempNode = "PortmansCap_inDeck_over";
        break;
    case "PortmansCap_inDeck_5":
        dialog.text = "Абсолютно" + GetSexPhrase(", дружище", "") + ". Ты слишком долго меня искал" + GetSexPhrase("", "а") + ", нужно было поторопиться.";
        link.l1 = "Хех, нужно было не терять журнала, тогда и я бы не мотал" + GetSexPhrase("ся", "ась") + " без толку. Ну да ладно, забирай свой журнал даром, мне он тоже не нужен.";
        link.l1.go = "exit";
        npchar.LifeDay = 30; // через десять дней снимаем кэпа
        SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
        npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
        sld = characterFromId(npchar.quest.firstCity + "_PortMan");
        sTitle = sld.id + "PortmansBook_Delivery";
        AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
        AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
        CloseQuestHeader(sTitle);
        DeleteAttribute(sld, "quest.PortmansJornal");
        sld.quest = ""; //освобождаем личный флаг квеста для портмана
        AddCharacterExpToSkill(pchar, "Sailing", makeint(100 / sti(npchar.quest.stepsQty)));
        TakeItemFromCharacter(pchar, "PortmansBook");
        npchar.DeckDialogNode = "PortmansCap_inDeck_over";
        NextDiag.TempNode = "PortmansCap_inDeck_over";
        break;
    case "PortmansCap_inDeck_over":
        dialog.text = "Вроде, все решили уже.";
        link.l1 = "Да, это верно...";
        link.l1.go = "exit";
        NextDiag.TempNode = "PortmansCap_inDeck_over";
        break;
    //--------------------------- розыск украденного корабля --------------------------------
    case "SeekCap_inDeck":
        dialog.text = "Приветствую. Что тебе нужно у меня на корабле?";
        link.l1 = "Да так, новостями обменяться хотел" + GetSexPhrase("", "а") + ". Может, что продается у тебя...";
        link.l1.go = "SeekCap_inDeck_1";
        break;
    case "SeekCap_inDeck_1":
        dialog.text = "Ничего не продается, и новостей у меня нет. И вообще, честно говоря, твое присутствие у меня на палубе нежелательно. Надеюсь, ясно выразился?";
        link.l1 = "Да куда уж ясней... Ну ладно, бывай, дружище.";
        link.l1.go = "exit";
        NextDiag.TempNode = "SeekCap_inDeck_over";
        sld = characterFromId(npchar.quest.cribCity + "_PortMan");
        sTitle = sld.id + "Portmans_SeekShip";
        AddQuestRecordEx(sTitle, "Portmans_SeekShip", "4");
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"));
        AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
        break;
    case "SeekCap_inDeck_over":
        dialog.text = "Сказал же, что тебе тут делать нечего!";
        link.l1 = "Понятно...";
        link.l1.go = "exit";
        NextDiag.TempNode = "SeekCap_inDeck_over";
        break;
    //абордаж
    case "SeekCap":
        dialog.text = "Зачем ты напал" + GetSexPhrase("", "а") + " на нас?!!";
        link.l1 = "Я долж" + GetSexPhrase("ен", "на") + " вернуть корабль его владельцу.";
        link.l1.go = "SeekCap_1";
        break;
    case "SeekCap_1":
        dialog.text = "Какому владельцу?! Я и есть владелец!";
        link.l1 = "Нет, это не так. Кто владеет кораблем - и я сам" + GetSexPhrase("", "а") + " не знаю, но я знаю, что корабль украден со стоянки одного из портов. Я долж" + GetSexPhrase("ен", "на") + " его вернуть на место.";
        link.l1.go = "SeekCap_2";
        break;
    case "SeekCap_2":
        dialog.text = "Дьявол! Ну, для меня еще не все потеряно. Я все-таки попытаюсь отправить тебя на тот свет...";
        link.l1 = "Ну, попытайся...";
        link.l1.go = "SeekCap_3";
        break;
    case "SeekCap_3":
        LAi_SetCurHPMax(npchar);
        QuestAboardCabinDialogExitWithBattle("");
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //-------------------------------------------поисковый генератор горожан--------------------------------------
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    case "SCQ_exit":
        DialogExit();
        npchar.lifeDay = 0;
        LAi_CharacterDisableDialog(npchar);
        break;

    case "SCQ_exit_clear":
        sld = characterFromId(npchar.quest.SeekCap.capId); //капитан
        sld.lifeDay = 0;
        Map_ReleaseQuestEncounter(sld.id);
        string sGroup = "SeekCapShip_" + sld.index;
        group_DeleteGroup(sGroup);
        sTemp = "SCQ_" + sld.index;
        pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
        sTemp = "SCQ_" + npchar.index;
        pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
        npchar.lifeDay = 0;
        LAi_CharacterDisableDialog(npchar);
        DialogExit();
        break;

        //--------------------------------------------поисковые квесты дворян---------------------------------------------

    case "SCQ_Nobleman":
        dialog.text = "Здравствуйте, " + GetAddress_Form(NPChar) + ". Как я вижу, вы капитан собственного корабля. Меня зовут " + GetFullName(npchar) + ", и я хочу предложить вам одно дело.";
        link.l1 = RandPhraseSimple("Прошу меня простить, но я очень спешу.", "Извините, но в данный момент у меня нет возможности вас выслушать.");
        link.l1.go = "SCQ_exit";
        link.l2 = "Внимательно вас слушаю, сударь.";
        link.l2.go = "SCQ_Nobleman_1";
        break;

    case "SCQ_Nobleman_1":
        switch (sti(npchar.quest.SeekCap.numQuest))
        {
        case 0: //вариант А
            if (sti(pchar.reputation.nobility) < 35)
            {
                dialog.text = "Суть вот в чем. " + SelectNB_battleText() + "\nУ меня нет ни времени, ни возможности разыскать его в открытом море или на архипелаге, а в нашей колонии он, конечно, не показывается. Вы, наверное, уже догадываетесь, что я хочу вам предложить?";
                link.l1 = LinkRandPhrase("Вероятно, найти этого человека и доставить его к вам?", "Наверное, разыскать негодяя и привести к вам?", "Думаю, речь пойдет о розыске и доставке к вам этого человека?");
                link.l1.go = "SCQ_NM_battle";
            }
            else //вариант В
            {
                SelectNB_prisonerText(npchar);
                dialog.text = "Суть вот в чем. " + npchar.quest.text + "\nУ меня нет ни времени, ни возможности разыскать его в открытом море или на архипелаге, а в нашей колонии он, конечно, не показывается. Вы, наверное, уже догадываетесь, что я хочу вам предложить?";
                link.l1 = LinkRandPhrase("Вероятно, найти этого человека и доставить его к вам?", "Наверное, разыскать негодяя и привести к вам?", "Думаю, речь пойдет о розыске и доставке к вам этого человека?");
                link.l1.go = "SCQ_NM_prisoner"
            }
            break;

        case 1: //вариант С
            SelectNB_peaceText(npchar);
            dialog.text = "Дело вот в чем. Оказывается, " + npchar.quest.text + ", служит сейчас в нашем военном флоте, он капитан корабля. И даже не знает, что я тоже живу на Карибах!\nЯ бы очень хотел с ним встретится, но у меня нет ни времени, ни возможности разыскать его в открытом море или на архипелаге...";
            link.l1 = "Я так понимаю, что вы хотите, чтобы я разыскал этого капитана и сообщил ему о вас?";
            link.l1.go = "SCQ_NM_peace";
            break;
        }
        break;

    case "SCQ_NM_battle": //вариант А
        dialog.text = "Не совсем так. Найти, но ко мне доставлять не нужно. Просто убейте его и всех дел. Утопите вместе с его дрянным кораблем, застрелите, заколите шпагой - мне абсолютно все равно, лишь бы эта пакость перестала осквернять мир своим присутствием. Награда будет щедрой.";
        link.l1 = "Ха! Ну, это можно устроить. Назовите мне имя этого капитана и корыто, на котором он ходит.";
        link.l1.go = "SCQ_NM_battle_1";
        break;

    case "SCQ_NM_battle_1":
        npchar.quest.SeekCap = "NM_battle";            //личный флаг на квест
        SetSeekCapCitizenParam(npchar, rand(HOLLAND)); //любая нация кроме пиратов
        dialog.text = "Капитана зовут " + npchar.quest.SeekCap.capName + ". Ходит на " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + " с именем '" + npchar.quest.SeekCap.shipName + "'. Недавно был замечен в порту города " + XI_ConvertString("Colony" + npchar.quest.Qcity) + ". Я заплачу вам за эту работу " + FindRussianMoneyString(sti(npchar.quest.money)) + " в золотых дублонах.";
        link.l1 = "Большего знать и не нужно. Я буду очень внимательно смотреть по сторонам. Так что как только встречу вашего недруга - ему конец.";
        link.l1.go = "SCQ_NM_battle_2";
        link.l2 = "Этого недостаточно для того, чтобы я занялся таким делом.";
        link.l2.go = "SCQ_exit_clear";
        break;

    case "SCQ_NM_battle_2":
        dialog.text = "Я рад, что мы нашли общий язык. Буду ждать вашего возвращения.";
        link.l1 = "Где вас будет проще всего найти? Давайте заранее договоримся, чтобы я не тратил свое время еще и на ваши розыски.";
        link.l1.go = "SCQ_NM_battle_3";
        break;

    case "SCQ_NM_battle_3":
        dialog.text = "Каждый день я хожу на утреннюю службу. Так что вы сможете меня найти в любой день с восьми до десяти утра в нашей церкви.";
        link.l1 = "Хорошо, договорились! Думаю, результат не заставит себя долго ждать.";
        link.l1.go = "exit";
        DeleteAttribute(npchar, "LifeDay");
        DeleteAttribute(npchar, "talker");
        DeleteAttribute(npchar, "CityType"); //удалить признак фантома, иначе - пустые города
        LAi_SetLoginTime(npchar, 8.0, 10.0);
        pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
        npchar.location = npchar.city + "_church";
        npchar.location.locator = "goto2";
        pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
        pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
        pchar.quest.SeekShip_Stay.Idx = npchar.index;
        NextDiag.TempNode = "SCQ_NM_result";
        sTitle = npchar.city + "SCQ_NM_battle";
        ReOpenQuestHeader(sTitle);
        AddQuestRecordEx(sTitle, "SCQ_NM_battle", "1");
        AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
        AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony" + npchar.quest.Qcity));
        AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
        AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
        AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        break;

    case "SCQ_NM_prisoner": //вариант В
        dialog.text = "Именно так. Найти и привести его ко мне, и чтобы ни один волос не упал с его головы - я сам лично хочу им заняться. Награда будет щедрой.";
        link.l1 = "Ну, если вы назовете корабль, на котором он служит, имя капитана этого корабля, и, конечно, как зовут вашего недруга - то я могу попробовать разыскать его.";
        link.l1.go = "SCQ_NM_prisoner_1";
        break;

    case "SCQ_NM_prisoner_1":
        npchar.quest.SeekCap = "NM_prisoner";          //личный флаг на квест
        SetSeekCapCitizenParam(npchar, rand(HOLLAND)); //любая нация кроме пиратов
        makearef(forName, npchar.quest.SeekCap);
        forName.nation = sti(npchar.nation);
        forName.sex = "man";
        forName.name = GenerateRandomName(sti(npchar.nation), "man");
        dialog.text = "Негодяя зовут " + npchar.quest.SeekCap.name + ". Служит на " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + " с названием '" + npchar.quest.SeekCap.shipName + "', под началом капитана по имени " + npchar.quest.SeekCap.capName + ". Не так давно этот корабль видели в порту города " + XI_ConvertString("Colony" + npchar.quest.Qcity) + ". Я заплачу вам за эту работу " + FindRussianMoneyString(sti(npchar.quest.money)) + " в золотых дублонах.";
        link.l1 = "Большего знать и не нужно. Я буду очень внимательно смотреть по сторонам. Так что как только встречу вашего недруга - ему конец.";
        link.l1.go = "SCQ_NM_prisoner_2";
        link.l2 = "Этого недостаточно для того, чтобы я занялся таким делом.";
        link.l2.go = "SCQ_exit_clear";
        break;

    case "SCQ_NM_prisoner_2":
        dialog.text = "Я рад, что мы нашли общий язык. Буду ждать вашего возвращения.";
        link.l1 = "Где вас будет проще всего найти? Давайте заранее договоримся, чтобы я не тратил свое время еще и на ваши розыски.";
        link.l1.go = "SCQ_NM_prisoner_3";
        break;

    case "SCQ_NM_prisoner_3":
        dialog.text = "Каждый день я хожу на утреннюю службу. Так что вы сможете меня найти в любой день с восьми до десяти утра в нашей церкви.";
        link.l1 = "Хорошо, договорились! Думаю, результат не заставит себя долго ждать.";
        link.l1.go = "exit";
        DeleteAttribute(npchar, "LifeDay");
        DeleteAttribute(npchar, "talker");
        DeleteAttribute(npchar, "CityType"); //удалить признак фантома, иначе - пустые города
        LAi_SetLoginTime(npchar, 8.0, 10.0);
        pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
        npchar.location = npchar.city + "_church";
        npchar.location.locator = "goto2";
        pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
        pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
        pchar.quest.SeekShip_Stay.Idx = npchar.index;
        NextDiag.TempNode = "SCQ_NM_result";
        sTitle = npchar.city + "SCQ_NM_prisoner";
        ReOpenQuestHeader(sTitle);
        AddQuestRecordEx(sTitle, "SCQ_NM_prisoner", "1");
        AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
        AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony" + npchar.quest.Qcity));
        AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
        AddQuestUserData(sTitle, "sName1", npchar.quest.SeekCap.name);
        AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
        AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        break;

    case "SCQ_NM_peace": //вариант С
        dialog.text = "Именно! Найдите его и сообщите, что я живу в этом городе. Пусть он при случае обязательно навестит меня. Вот это будет встреча! Если вы сделаете это - я не поскуплюсь на достойную награду.";
        link.l1 = "Ну что же... Могу попытаться. Назовите мне имя этого капитана и корабль, на котором он служит.";
        link.l1.go = "SCQ_NM_peace_1";
        break;

    case "SCQ_NM_peace_1":
        npchar.quest.SeekCap = "NM_peace";                  //личный флаг на квест
        SetSeekCapCitizenParam(npchar, sti(npchar.nation)); //нация = нации квестодателя
        dialog.text = "Капитана зовут " + npchar.quest.SeekCap.capName + ". Служит на " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + " с именем '" + npchar.quest.SeekCap.shipName + "'. Недавно его видели в порту города " + XI_ConvertString("Colony" + npchar.quest.Qcity) + ". Я заплачу вам за эту работу " + FindRussianMoneyString(sti(npchar.quest.money)) + " в золотых дублонах.";
        link.l1 = "Очень хорошо! Думаю, что смогу разыскать вашего друга достаточно быстро.";
        link.l1.go = "SCQ_NM_peace_2";
        link.l2 = "Этого недостаточно для того, чтобы я занялся таким делом.";
        link.l2.go = "SCQ_exit_clear";
        break;

    case "SCQ_NM_peace_2":
        dialog.text = "Я рад, что мы нашли общий язык. Буду ждать вашего возвращения.";
        link.l1 = "Где вас будет проще всего найти? Давайте заранее договоримся, чтобы я не тратил свое время еще и на ваши розыски.";
        link.l1.go = "SCQ_NM_peace_3";
        break;

    case "SCQ_NM_peace_3":
        dialog.text = "Каждый день я хожу на вечернюю службу. Так что вы сможете меня найти в любой день с шести до восьми вечера в нашей церкви.";
        link.l1 = "Хорошо, договорились! Думаю, результат не заставит себя долго ждать.";
        link.l1.go = "exit";
        DeleteAttribute(npchar, "LifeDay");
        DeleteAttribute(npchar, "talker");
        DeleteAttribute(npchar, "CityType"); //удалить признак фантома, иначе - пустые города
        LAi_SetLoginTime(npchar, 18.0, 20.0);
        pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
        npchar.location = npchar.city + "_church";
        npchar.location.locator = "goto2";
        pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
        pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
        pchar.quest.SeekShip_Stay.Idx = npchar.index;
        NextDiag.TempNode = "SCQ_NM_result";
        sTitle = npchar.city + "SCQ_NM_peace";
        ReOpenQuestHeader(sTitle);
        AddQuestRecordEx(sTitle, "SCQ_NM_peace", "1");
        AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
        AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony" + npchar.quest.Qcity));
        AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
        AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
        AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        break;

    //--> разговор на суше, вариант А
    case "NM_battleCap":
        dialog.text = "Ну? Что вам угодно, сударь?";
        link.l1 = "Вас зовут капитан " + GetFullName(npchar) + ", не так ли?";
        link.l1.go = "NM_battleCap_1";
        break;

    case "NM_battleCap_1":
        dialog.text = "Да. А в чем дело-то?";
        link.l1 = "Вами очень интересуется один человек, " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]) + ". Не припоминаете, а?";
        link.l1.go = "NM_battleCap_2";
        link.l2 = "Я слышал, у вас в трюме полно красного дерева, а я занимаюсь его закупкой. Не продадите?";
        link.l2.go = "NM_battleCap_4";
        break;

    case "NM_battleCap_2":
        dialog.text = "Впервые слышу это имя. Вероятно, вы что-то напутали, сударь. Позвольте мне пройти!";
        link.l1 = "Хм. Ну ладно, извините...";
        link.l1.go = "NM_battleCap_exit";
        link.l2 = "Да? Ну, зато он очень хорошо помнит ваше имя. И он очень просил вернуть вам долг...";
        link.l2.go = "NM_battleCap_3";
        break;

    case "NM_battleCap_3":
        dialog.text = "Какой еще долг? Это вы о чем?";
        link.l1 = "Долг чести!";
        link.l1.go = "NM_battleCap_fight";
        break;

    case "NM_battleCap_4":
        dialog.text = "Вы ошиблись. Никаким деревом я не торгую. Позвольте мне пройти!";
        link.l1 = "Хм. Ну ладно, извините...";
        link.l1.go = "NM_battleCap_exit";
        break;

    case "NM_battleCap_exit":
        DialogExit();
        NextDiag.TempNode = "NM_battleDeck_exit";
        npchar.DeckDialogNode = "NM_battleDeck_exit";
        break;

    case "NM_battleCap_fight":
        NextDiag.TempNode = "NM_battleDeck_exit";
        npchar.DeckDialogNode = "NM_battleDeck_exit";
        LAi_group_Attack(NPChar, Pchar);
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

    //--> разговор на суше и палубе одинаковый, вариант В
    case "NM_prisonerCap":
        dialog.text = "Ну? Что вам угодно, сударь?";
        link.l1 = "Вас зовут капитан " + GetFullName(npchar) + ", не так ли?";
        link.l1.go = "NM_prisonerCap_1";
        break;

    case "NM_prisonerCap_1":
        sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]; //квестодатель
        dialog.text = "Да. А в чем дело-то?";
        link.l1 = "У вас в команде служит человек по имени " + sld.quest.SeekCap.name + "?";
        link.l1.go = "NM_prisonerCap_2";
        break;

    case "NM_prisonerCap_2":
        sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]; //квестодатель
        dialog.text = "Верно. Это один из моих офицеров. Так вы скажете, наконец, к чему все эти расспросы?";
        link.l1 = "Конечно. Я разыскиваю этого человека по поручению властей " + XI_ConvertString("Colony" + sld.city + "Gen") + ". Он " + sld.quest.text1 + ", и я уполномочен арестовать его и доставить в город " + XI_ConvertString("Colony" + sld.city) + ". Я прошу вас оказать мне в этом содействие.";
        link.l1.go = "NM_prisonerCap_3";
        break;

    case "NM_prisonerCap_3":
        if (sti(npchar.reputation.nobility) > 41)
        {
            dialog.text = "Да что вы такое говорите! И этот человек служит у меня в команде? Вот это да! Я немедленно распоряжусь доставить его на ваше судно.";
            link.l1 = "Не утруждайте себя излишними заботами, " + GetAddress_FormToNPC(NPChar) + ". Я пришлю барку к вашему судну и мы сами его заберем.";
            link.l1.go = "NM_prisonerCap_good";
        }
        else
        {
            dialog.text = "Да неужели? Знаете, сударь, мне плевать на его прошлое. Оно меня не касается. И вы вообще - кто такой? О каких полномочиях вы мне тут говорите? Я не собираюсь выдавать своих офицеров ни вам, ни кому бы то ни было. И более к этому разговору я возвращаться не желаю. Всего доброго!";
            link.l1 = "Хм. Это вы зря... Очень зря!";
            link.l1.go = "NM_prisonerCap_bad";
        }
        break;

    case "NM_prisonerCap_good":
        dialog.text = "Хорошо. Так и поступим.";
        link.l1 = "Тогда я отправляюсь на свой корабль.";
        link.l1.go = "NM_prisonerCap_good_1";
        break;

    case "NM_prisonerCap_good_1":
        DialogExit();
        NextDiag.CurrentNode = "NM_prisonerDeck_exit";
        npchar.DeckDialogNode = "NM_prisonerDeck_exit";
        npchar.quest.release = "true";
        sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
        ref chr = GetCharacter(NPC_GenerateCharacter(npchar.quest.SeekCap + "_" + npchar.quest.cribCity, "citiz_" + (rand(9) + 21), "man", "man", 5, sti(npchar.nation), -1, false, "citizen"));
        chr.name = sld.quest.SeekCap.name;
        chr.lastname = "";
        //pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(chr);
        //SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
        AddPassenger(pchar, chr, false); //добавить пассажира
        SetCharacterRemovable(chr, false);
        log_info(sld.quest.SeekCap.name + " помещен на ваш корабль под стражу");
        PlaySound("interface\notebook.wav");
        sTemp = "SCQ_" + npchar.index;
        pchar.quest.(sTemp).win_condition.l1 = "MapEnter";
        pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
        //DoQuestFunctionDelay("SCQ_seekCapIsDeath", 0.5); // 170712
        AddCharacterExpToSkill(pchar, "Fortune", 200); //везение
        break;

    case "NM_prisonerCap_bad":
        DialogExit();
        NextDiag.CurrentNode = "NM_prisonerDeck_exit";
        npchar.DeckDialogNode = "NM_prisonerDeck_exit";
        npchar.quest.mustboarding = "true";
        sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]; //квестодатель
        sTitle = sld.City + "SCQ_" + sld.quest.SeekCap;
        AddQuestRecordEx(sTitle, "SCQ_" + sld.quest.SeekCap, "6");
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        break;

    case "NM_prisonerDeck_exit":
        dialog.text = "Мы ведь уже все решили по вопросу с моим офицером, так, капитан?";
        link.l1 = "...";
        link.l1.go = "exit";
        NextDiag.TempNode = "NM_prisonerDeck_exit";
        break;

    //--> разговор на суше и палубе одинаковый, вариант C
    case "NM_peaceCap":
        dialog.text = "Добрый день. Что вам угодно, сударь?";
        link.l1 = "Вас зовут капитан " + GetFullName(npchar) + ", не так ли?";
        link.l1.go = "NM_peaceCap_1";
        break;

    case "NM_peaceCap_1":
        sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity); //квестодатель
        dialog.text = "Именно так. У вас ко мне какое-то дело?";
        link.l1 = "Да. Вас разыскивает человек по имени " + GetFullName(sld) + ". Он сказал, что " + sld.quest.text1 + ". Он очень хочет, чтобы вы как можно быстрее нанесли ему визит. Он живет в " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Dat") + ".";
        link.l1.go = "NM_peaceCap_2";
        break;

    case "NM_peaceCap_2":
        dialog.text = "Ха! Так что, он тоже подался в Новый Свет? Тогда мне действительно стоит навеcтить его... При первом же удобном случае я отправлюсь в " + XI_ConvertString("Colony" + npchar.quest.cribCity) + ". Спасибо за информацию, сударь!";
        link.l1 = "Не за что. Все мои труды будут оплачены вашим другом. Удачи, " + GetAddress_FormToNPC(NPChar) + "!";
        link.l1.go = "NM_peaceCap_3";
        break;

    case "NM_peaceCap_3":
        DialogExit();
        NextDiag.CurrentNode = "NM_peaceCap_exit";
        npchar.DeckDialogNode = "NM_peaceCap_exit";
        sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
        AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Acc"));
        sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity); //квестодатель
        sld.quest.SeekCap = sld.quest.SeekCap + "over";               //дополняем флаг квест до 'выполнен'
        //удаляем запись в базе кэпов
        makearef(forName, NullCharacter.capitainBase);
        DeleteAttribute(forName, npchar.id);
        break;

    case "NM_peaceCap_exit":
        dialog.text = "Рад был с вами познакомиться, " + GetAddress_Form(NPChar) + "!";
        link.l1 = "Я тоже, капитан.";
        link.l1.go = "exit";
        NextDiag.TempNode = "NM_peaceCap_exit";
        break;

    //--> встреча на палубе, вариант А
    case "NM_battleDeck":
        dialog.text = "Приветствую, " + GetAddress_Form(NPChar) + ". Чем обязан вашему визиту?";
        link.l1 = "Я слышал, у вас в трюме полно красного дерева, а я занимаюсь его закупкой. Не продадите?";
        link.l1.go = "NM_battleDeck_1";
        break;

    case "NM_battleDeck_1":
        dialog.text = "Вы ошиблись. Никаким деревом я не торгую. И вообще, ваш визит кажется мне довольно странным. Думаю, вам лучше покинуть мое судно!";
        link.l1 = "Хорошо-хорошо, я просто спросил. Всего доброго.";
        link.l1.go = "exit";
        NextDiag.TempNode = "NM_battleDeck_exit";
        npchar.DeckDialogNode = "NM_battleDeck_exit";
        sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
        AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
        break;

    case "NM_battleDeck_exit":
        dialog.text = "Не нарывайтесь на неприятности, сударь! Кажется, мы с вами уже все выяснили!";
        link.l1 = "...";
        link.l1.go = "exit";
        NextDiag.TempNode = "NM_battleDeck_exit";
        break;

        //--> абордаж, вариант А
    case "NM_battleBoard":
        sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
        dialog.text = "Аргх! Зачем ты напал на мой корабль, каналья?";
        link.l1 = "Я пришел, чтобы передать тебе привет из города " + XI_ConvertString("Colony" + npchar.quest.cribCity) + ", от человека по имени " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]) + ". Надеюсь, теперь-то тебе всё понятно?";
        link.l1.go = "NM_battleBoard_1";
        break;

    case "NM_battleBoard_1":
        dialog.text = "Невероятно! Значит, мне терять нечего...";
        link.l1 = "Это точно! Поднимай шпагу!";
        link.l1.go = "NM_battleBoard_2";
        break;

    case "NM_battleBoard_2":
        DialogExit();
        LAi_SetCurHPMax(npchar);
        QuestAboardCabinDialogFree();
        LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

        //--> абордаж, вариант В
    case "NM_prisonerBoard":
        sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]; //квестодатель
        dialog.text = "Аргх! Зачем ты напал на мой корабль, каналья?";
        if (CheckAttribute(npchar, "quest.mustboarding"))
        {
            link.l1 = "А что, не догадываешься? Я же по-хорошему просил тебя выдать мне своего негодяя-офицера. Теперь я сам его возьму, без твоего согласия!";
            link.l1.go = "NM_prisonerBoard_1";
        }
        else
        {
            link.l1 = "У тебя на корабле в команде служит негодяй по имени " + sld.quest.SeekCap.name + ". Его очень жаждут увидеть власти города " + XI_ConvertString("Colony" + npchar.quest.cribCity) + ". Он будет схвачен и помещен на мое судно.";
            link.l1.go = "NM_prisonerBoard_1";
        }
        break;

    case "NM_prisonerBoard_1":
        dialog.text = "И ты только ради этого устроил резню на моем судне? Мерзавец! У меня еще остались силы... Я прикончу тебя!";
        link.l1 = "Ну-ну, попробуй...";
        link.l1.go = "NM_prisonerBoard_2";
        break;

    case "NM_prisonerBoard_2":
        DialogExit();
        LAi_SetCurHPMax(npchar);
        pchar.GenQuest.mustboarding = "true"; //ставим этот флаг для завершения квеста
        QuestAboardCabinDialogFree();
        LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_GivePrisoner");
        AddDialogExitQuest("MainHeroFightModeOn");
        pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
        pchar.GenQuest.CitizSeekCap.nation = npchar.nation;       //нацию для нпс
        pchar.GenQuest.CitizSeekCap.sex = "man";
        pchar.GenQuest.CitizSeekCap.ani = "man";
        pchar.GenQuest.CitizSeekCap.model = "citiz_" + (rand(9) + 21);    //модель для нпс
        pchar.GenQuest.CitizSeekCap.PrisonerCity = npchar.quest.cribCity; //исходный город для нпс
        sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
        pchar.GenQuest.CitizSeekCap.PrisonerName = sld.quest.SeekCap.name; //имя и фамилию для нпс
        pchar.GenQuest.CitizSeekCap.PrisonerLastname = "";
        AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
        break;

    //--> результаты квестов дворян
    case "SCQ_NM_result":
        dialog.text = "Ну, что скажете, капитан? Есть какие-нибудь результаты по моему делу?";
        link.l1 = "Пока нет. Но я работаю над этим.";
        link.l1.go = "exit";
        switch (npchar.quest.SeekCap)
        {
        case "NM_battleover": //сдача квеста, вариант А
            dialog.text = "Ну, что скажете, капитан? Есть какие-нибудь результаты по моему делу?";
            link.l1 = "Есть. И, думаю, они вам понравятся. " + npchar.quest.SeekCap.capName + " мертв, а его " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName)) + " на дне.";
            link.l1.go = "SCQ_NM_result_A1";
            break;

        case "NM_prisonerover": //сдача квеста, вариант B
            dialog.text = "Ну, что скажете, капитан? Есть какие-нибудь результаты по моему делу?";
            link.l1 = "Есть. И, думаю, они вам понравятся. " + npchar.quest.SeekCap.Name + " сидит в каюте моего корабля под стражей.";
            link.l1.go = "SCQ_NM_result_B1";
            break;

        case "NM_peaceover": //сдача квеста, вариант C
            dialog.text = "А-а, вот и вы. Рад вас видеть. Я уже знаю, что вы выполнили мое поручение!";
            link.l1 = "Ваш друг нанес вам визит?";
            link.l1.go = "SCQ_NM_result_C1";
            break;
        }
        break;

    case "SCQ_NM_result_A1":
        dialog.text = "Отлично! Я сразу понял, что на вас можно положиться в таком деле. Вот, держите ваше золото. Вы его честно заработали.";
        link.l1 = "Благодарю. Если у вас появятся еще недруги - обращайтесь.";
        link.l1.go = "SCQ_exit";
        sTemp = "SCQ_" + npchar.index;
        pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
        TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
        Log_Info("Вы получили " + FindRussianDublonString(sti(npchar.quest.dublon)) + "");
        PlaySound("interface\important_item.wav");
        sTitle = npchar.city + "SCQ_NM_battle";
        CloseQuestHeader(sTitle);
        ChangeCharacterComplexReputation(pchar, "nobility", -1);
        ChangeCharacterComplexReputation(pchar, "authority", 1);
        OfficersReaction("bad");
        ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
        AddComplexSeaExpToScill(100, 50, 50, 50, 50, 50, 0);
        AddCharacterExpToSkill(pchar, "Leadership", 100); //авторитет
        AddCharacterExpToSkill(pchar, "Fortune", 50);     //везение
        break;

    case "SCQ_NM_result_B1":
        dialog.text = "Отлично! Я немедленно распоряжусь прислать своих людей к вашему судну, чтобы забрать его. Теперь-то он уже никуда не уйдет! Вот, держите ваше золото. Вы его честно заработали.";
        link.l1 = "Благодарю. Если у вас появятся еще недруги - обращайтесь.";
        link.l1.go = "SCQ_exit";
        sTemp = "SCQ_" + npchar.index;
        pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
        TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
        Log_Info("Вы получили " + FindRussianDublonString(sti(npchar.quest.dublon)) + "");
        PlaySound("interface\important_item.wav");
        sTitle = npchar.city + "SCQ_NM_prisoner";
        CloseQuestHeader(sTitle);
        sld = characterFromId("NM_prisoner_" + npchar.City);
        RemovePassenger(pchar, sld); // 170712
        //ReleasePrisoner(sld);
        sld.lifeday = 0;
        ChangeCharacterComplexReputation(pchar, "authority", 1);
        ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
        AddCharacterExpToSkill(pchar, "Sailing", 100);    //навигация
        AddCharacterExpToSkill(pchar, "Leadership", 150); //авторитет
        break;

    case "SCQ_NM_result_C1":
        dialog.text = "Да, он был здесь, и рассказал про встречу с вами. Вот, держите ваше золото. Вы его честно заработали.";
        link.l1 = "Благодарю. Всего доброго, сударь!";
        link.l1.go = "SCQ_exit";
        sTemp = "SCQ_" + npchar.index;
        pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
        sld = characterFromId(npchar.quest.SeekCap.capId);
        sld.lifeday = 0;
        Map_ReleaseQuestEncounter(sld.id);
        sGroup = "SeekCapShip_" + sld.index;
        group_DeleteGroup(sGroup);
        sTemp = "SecondTimer_" + sld.id;
        pchar.quest.(sTemp).over = "yes"; //снимаем возможный таймер на выход в море
        sTemp = "SCQ_" + sld.index;
        pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
        TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
        Log_Info("Вы получили " + FindRussianDublonString(sti(npchar.quest.dublon)) + "");
        PlaySound("interface\important_item.wav");
        sTitle = npchar.city + "SCQ_NM_peace";
        CloseQuestHeader(sTitle);
        ChangeCharacterComplexReputation(pchar, "nobility", 1);
        OfficersReaction("good");
        ChangeCharacterComplexReputation(pchar, "authority", 1);
        ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
        AddCharacterExpToSkill(pchar, "Sailing", 100);    //навигация
        AddCharacterExpToSkill(pchar, "Leadership", 200); //авторитет
        AddCharacterExpToSkill(pchar, "Fortune", 50);     //везение
        break;
        //<-- поисковые квесты дворян

    //========= квесты мужиков ===========
    case "SCQ_man":
        dialog.text = LinkRandPhrase("Здравствуйте, капитан. Хочу просить вас помочь мне.",
                                     "Капитан! Не окажете мне услугу? Дело в том, что я нуждаюсь в помощи.",
                                     "Капитан, я прошу вас о помощи!");
        link.l1 = RandPhraseSimple("Я занят" + GetSexPhrase("", "а") + ", не сегодня!", "В данный момент у меня нет времени вас выслушивать.");
        link.l1.go = "SCQ_exit";
        link.l2 = RandPhraseSimple("Что у вас стряслось?", "Излагайте суть проблемы. Возможно, я сумею помочь.");
        link.l2.go = "SCQ_man_1";
        break;
    case "SCQ_exit":
        //минус один шанс, что следующий квестодатель сам заговорит
        sld = &locations[FindLocation(npchar.location)];
        if (sti(sld.questSeekCap) > 0)
            sld.questSeekCap = sti(sld.questSeekCap) - 1;
        npchar.lifeDay = 0;
        LAi_CharacterDisableDialog(npchar);
        DialogExit();
        break;
    case "SCQ_exit_clear":
        //минус один шанс, что следующий квестодатель сам заговорит
        sld = &locations[FindLocation(npchar.location)];
        if (sti(sld.questSeekCap) > 0)
            sld.questSeekCap = sti(sld.questSeekCap) - 1;
        sld = characterFromId(npchar.quest.SeekCap.capId); //капитан
        sld.lifeDay = 0;
        Map_ReleaseQuestEncounter(sld.id);
        sGroup = "SeekCapShip_" + sld.index;
        group_DeleteGroup(sGroup);
        sTemp = "SCQ_" + sld.index;
        pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
        sTemp = "SCQ_" + npchar.index;
        pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
        npchar.lifeDay = 0;
        LAi_CharacterDisableDialog(npchar);
        DialogExit();
        break;
    //выбираем квест
    case "SCQ_man_1":
        switch (npchar.quest.SeekCap.numQuest)
        {
        case "0":
            dialog.text = "Год назад один капитан взялся доставить меня " + XI_ConvertString("Colony" + SelectNotEnemyColony(NPChar) + "Acc") + ". Но на борту его корабля я был брошен в трюм, а потом продан в рабство. Из этой переделки я выбрался с огромным трудом, несколько раз находился на грани жизни и смерти... В общем, я хочу напомнить моему 'другу', что я еще жив.";
            link.l1 = "В смысле? Точнее опишите, что вы желаете.";
            link.l1.go = "SCQ_Slave";
            break;
        case "1":
            dialog.text = "Дело в том, что у меня похитили жену. Один капитан, пират по слухам, ухлестывал тут за ней, как только мог. Жена одно время даже не выходила из дома, настолько он был назойлив. Я пытался привлечь городские власти к этой проблеме - безрезультатно. И вот дождались, называется...";
            link.l1 = "Чего дождались?";
            link.l1.go = "SCQ_RapeWife";
            break;
        case "2":
            dialog.text = "Вы знаете, я ищу своего земляка, с которым три года назад мы отправились сюда из Старого света в поисках новой жизни. Так случилось, что в дороге мы потеряли друг друга. Но недавно я узнал, что мой земляк стал торговым капитаном! Я пытался его найти, но сам с этим справиться не могу.";
            link.l1 = "Почему? Множество капитанов, включая меня, могут доставить вас куда угодно.";
            link.l1.go = "SCQ_Friend";
            break;
        }
        break;
    // квест бывшего раба, которого негодяй-кэп взял в плен
    case "SCQ_Slave":
        dialog.text = "Я хочу, чтобы вы нашли его и отправили на тот свет. Я настолько хочу отомстить, что просто кушать не могу...";
        link.l1 = "Понятно... Думаю, что смогу вам помочь при случае. Назовите мне имя капитана и корабль, на котором он ходит.";
        link.l1.go = "SCQ_Slave_1";
        link.l2 = "Извините, меня это не интересует.";
        link.l2.go = "SCQ_exit";
        break;
    case "SCQ_Slave_1":
        npchar.quest.SeekCap = "manSlave"; //личный флаг ситизена на квест
        SetSeekCapCitizenParam(npchar, PIRATE);
        dialog.text = "Капитана зовут " + npchar.quest.SeekCap.capName + ". Ходит на " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + " с именем '" + npchar.quest.SeekCap.shipName + "'. Я заплачу вам за эту работу " + FindRussianMoneyString(sti(npchar.quest.money)) + " и все свои личные драгоценности.";
        link.l1 = "Ясно. Ну что же, я буду внимател" + GetSexPhrase("ен", "ьна") + " при передвижениях по Карибскому морю. Если встречу этого кэпа, то ему крышка...";
        link.l1.go = "SCQ_Slave_2";
        link.l2 = "За такие деньги я и пальцем не пошевельну. Ищи дурака в другом месте.";
        link.l2.go = "SCQ_exit_clear";
        break;
    case "SCQ_Slave_2":
        dialog.text = "Фуф-ф, это то, что я так жаждал услышать!.. О-о, уже и кушать могу! Надо бы перекусить...";
        link.l1 = "Давай, приятель. Как выполню работу - найду тебя здесь, в городе.";
        link.l1.go = "SCQ_Slave_3";
        break;
    case "SCQ_Slave_3":
        dialog.text = "Хорошо, я буду ждать вас в местной церкви. Тогда и рассчитаюсь с вами.";
        link.l1 = "Хорошо.";
        link.l1.go = "exit";
        //==> ставим квестодателя в церковь
        pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
        npchar.location = npchar.city + "_church";
        npchar.location.locator = "goto2";
        pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
        pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
        pchar.quest.SeekShip_Stay.Idx = npchar.index;
        NextDiag.TempNode = "SCQ_manResult";
        sTitle = npchar.city + "SCQ_manSlave";
        ReOpenQuestHeader(sTitle);
        AddQuestRecordEx(sTitle, "SCQ_manSlave", "1");
        AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
        AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
        AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
        AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
        break;
    //пират похитил жену у ситизена
    case "SCQ_RapeWife":
        dialog.text = "Мое относительное бездействие привело к печальным результатам. Этот мерзавец похитил мою жену и увез ее на своем корабле в море. Я прошу вас найти этого негодяя!";
        link.l1 = "Хм, ну и зачем мне ссориться с коллегами?";
        link.l1.go = "SCQ_RapeWife_1";
        break;
    case "SCQ_RapeWife_1":
        npchar.quest.SeekCap = "manRapeWife"; //личный флаг ситизена на квест
        SetSeekCapCitizenParam(npchar, PIRATE);
        makearef(forName, npchar.quest.SeekCap);
        forName.nation = npchar.nation;
        forName.sex = "woman";
        SetRandomNameToCharacter(forName);  //npchar.quest.SeekCap.name - имя жены ситизена
        forName.lastname = npchar.lastname; //фамилия как и у мужа есно
        dialog.text = "Я небогат, но с радостью отдам все, что у меня есть! Если вы освободите мою жену и доставите ее ко мне, то я заплачу вам " + FindRussianMoneyString(sti(npchar.quest.money)) + " и отдам все свои личные драгоценности.";
        link.l1 = "Хм, ну что же, я готов" + GetSexPhrase("", "а") + " заняться этим делом. Как зовут этого любвеобильного кэпа, какой у него корабль? Да, и как зовут вашу жену?";
        link.l1.go = "SCQ_RapeWife_2";
        link.l2 = "Нет, приятель, за такие деньги я не возьмусь за это дело. Сожалею...";
        link.l2.go = "SCQ_exit_clear";
        break;
    case "SCQ_RapeWife_2":
        dialog.text = "Ее зовут " + npchar.quest.SeekCap.name + ". Мерзавца-капитана зовут " + npchar.quest.SeekCap.capName + ", плавает он на " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + " с именем '" + npchar.quest.SeekCap.shipName + "'.";
        link.l1 = "Плавают известные продукты жизнедеятельности человека, приятель. А капитаны - ходят...";
        link.l1.go = "SCQ_RapeWife_3";
        break;
    case "SCQ_RapeWife_3":
        dialog.text = "Да-да, конечно, извините! Я ведь не моряк, так что сами понимаете...";
        link.l1 = "Да все нормально, не переживайте. В общем, теперь ожидайте меня с результатами поисков.";
        link.l1.go = "SCQ_RapeWife_4";
        break;
    case "SCQ_RapeWife_4":
        dialog.text = "Спасибо вам огромное! Я буду ждать вас в местной церкви. Только я умоляю вас - быстрее. Я очень опасаюсь за жену...";
        link.l1 = "Сделаю все, что смогу. Ждите.";
        link.l1.go = "exit";
        //==> ставим квестодателя в церковь
        pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
        npchar.location = npchar.city + "_church";
        npchar.location.locator = "goto2";
        pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
        pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
        pchar.quest.SeekShip_Stay.Idx = npchar.index;
        NextDiag.TempNode = "SCQ_manResult";
        sTitle = npchar.city + "SCQ_manRapeWife";
        ReOpenQuestHeader(sTitle);
        AddQuestRecordEx(sTitle, "SCQ_manRapeWife", "1");
        AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся", "ась"));
        AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
        AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
        AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        AddQuestUserData(sTitle, "sName2", npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname);
        AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся", "ась"));
        break;
    //поиски земляка
    case "SCQ_Friend":
        dialog.text = "Дело в том, что мой земляк так и не обзавелся здесь недвижимостью. Его дом - это его корабль. Поэтому мне очень сложно его отловить, он постоянно в движении. А я не могу позволить себе тратить время на бесполезные путешествия, я вынужден зарабатывать себе на жизнь.";
        link.l1 = "Если у вас нет денег, то я ничем не смогу вам помочь...";
        link.l1.go = "SCQ_Friend_1";
        break;
    case "SCQ_Friend_1":
        npchar.quest.SeekCap = "manFriend"; //личный флаг ситизена на квест
        SetSeekCapCitizenParam(npchar, sti(npchar.nation));
        dialog.text = "Я могу заплатить вам за работу " + FindRussianMoneyString(sti(npchar.quest.money)) + " и отдам все свои личные драгоценности. Это все, что я могу себе позволить на данный момент.";
        link.l1 = "Сумма меня устраивает, я готов" + GetSexPhrase("", "а") + " взяться за это дело. Вы, кстати, можете пойти ко мне пассажиром, тогда вам не придется ездить к земляку, когда он будет найден.";
        link.l1.go = "SCQ_Friend_2";
        link.l2 = "Это слишком мало для меня. Так что поищите кого-нибудь другого для этого дела.";
        link.l2.go = "SCQ_exit_clear";
        break;
    case "SCQ_Friend_2":
        dialog.text = "Нет, я, пожалуй, останусь здесь. Неизвестно, сколько продлятся поиски, и у меня может просто не хватить денег. А здесь у меня есть работа.";
        link.l1 = "Понимаю. Ну что же, теперь расскажите мне, кто ваш друг и какой у него корабль.";
        link.l1.go = "SCQ_Friend_3";
        break;
    case "SCQ_Friend_3":
        dialog.text = "Его зовут " + npchar.quest.SeekCap.capName + ". Насколько мне известно, он имеет " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")) + " с именем '" + npchar.quest.SeekCap.shipName + "'.";
        link.l1 = "Ясно. Ну что же, как только встречу вашего земляка, то обязательно расскажу ему, что вы его ищете.";
        link.l1.go = "SCQ_Friend_4";
        break;
    case "SCQ_Friend_4":
        dialog.text = "Спасибо вам. Я буду ждать вашего прибытия в местной церкви. Полагаю, что деньги мне нужно будет отдать после того, как работа будет выполнена.";
        link.l1 = "Конечно. Ну, всего хорошего, ожидайте результата поисков.";
        link.l1.go = "exit";
        //==> ставим квестодателя в церковь
        pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
        npchar.location = npchar.city + "_church";
        npchar.location.locator = "goto2";
        pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
        pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
        pchar.quest.SeekShip_Stay.Idx = npchar.index;
        NextDiag.TempNode = "SCQ_manResult";
        sTitle = npchar.city + "SCQ_manFriend";
        ReOpenQuestHeader(sTitle);
        AddQuestRecordEx(sTitle, "SCQ_manFriend", "1");
        AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся", "ась"));
        AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
        AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
        AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        AddQuestUserData(sTitle, "sSex", GetSexPhrase("ел", "ла"));
        AddQuestUserData(sTitle, "sSex1", GetSexPhrase("", "а"));
        break;

    // --- результаты мужских квестов ---
    case "SCQ_manResult":
        dialog.text = "Здравствуйте, капитан. Есть какие-нибудь результаты по моему делу?";
        link.l1 = "Напомни, что там у тебя?..";
        link.l1.go = "SCQ_manResult_exit";
        switch (npchar.quest.SeekCap)
        {
        case "manSlaveover":
            dialog.text = "По вашему виду догадываюсь, что я наконец-то отомщен. Это так?";
            link.l1 = "Именно. " + npchar.quest.SeekCap.capName + " мертв, а его " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName)) + " на дне.";
            link.l1.go = "SCQR_manSlave";
            break;
        case "manRapeWifeover":
            dialog.text = "Вы разыскали мою жену! Это правда?!";
            link.l1 = "Правда. Она у меня на корабле в качестве пассажира. Можете ее забирать, если " + npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname + " и есть ваша жена...";
            link.l1.go = "SCQR_manRapeWife";
            break;
        case "manFriendover":
            dialog.text = "Здравствуйте, капитан. Вы нашли моего земляка?";
            link.l1 = "Наш" + GetSexPhrase("ел", "ла") + " и рассказал" + GetSexPhrase("", "а") + ", что вы его ждете здесь. Так что все вышло удачно.";
            link.l1.go = "SCQR_manFriend";
            break;
        }
        break;
    case "SCQ_manResult_exit":
        switch (npchar.quest.SeekCap)
        {
        case "manSlave":
            dialog.text = "Как, вы забыли, что я нанял вас отомстить капитану по имени " + npchar.quest.SeekCap.capName + " за год, проведенный мной в рабстве?!";
            link.l1 = "Да ничего я не забыл" + GetSexPhrase("", "а") + ". Занимаюсь этим, жди.";
            link.l1.go = "exit";
            break;
        case "manRapeWife":
            dialog.text = "Ушам не верю! Вы забыли, что обещали мне разыскать и освободить мою жену? Ее похитил пират по имени " + npchar.quest.SeekCap.capName + "!";
            link.l1 = "Не забыл" + GetSexPhrase("", "а") + " я о твоей жене. Просто розыски пока не принесли результата. Все это не так просто, жди...";
            link.l1.go = "exit";
            break;
        case "manFriend":
            dialog.text = "Подождите... Вы что, забыли о своем обещании найти моего земляка, торгового капитана по имени " + npchar.quest.SeekCap.capName + "?";
            link.l1 = "Не забыл" + GetSexPhrase("", "а") + ", но пока не наш" + GetSexPhrase("ел", "ла") + ". Жди...";
            link.l1.go = "exit";
            break;
        }
        break;

    case "SCQR_manSlave":
        dialog.text = "Превосходно, я в вас не ошибался! Итак, как мы и договаривались, вот ваши " + FindRussianMoneyString(sti(npchar.quest.money)) + " и драгоценности. Спасибо за труд.";
        link.l1 = "Хм, да не за что...";
        link.l1.go = "SCQ_exit";
        sTemp = "SCQ_" + npchar.index;
        pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
        AddMoneyToCharacter(pchar, sti(npchar.quest.money));
        TakeNItems(pchar, npchar.quest.gem, 10 + drand(8));
        sTitle = npchar.city + "SCQ_manSlave";
        CloseQuestHeader(sTitle);
        break;
    case "SCQR_manRapeWife":
        dialog.text = "Боже мой, вы буквально вернули меня к жизни! Извольте получить свои " + FindRussianMoneyString(sti(npchar.quest.money)) + " и драгоценности. И знайте, что мы будем молиться за вас до конца жизни!";
        link.l1 = "Молитесь, я не против.";
        link.l1.go = "SCQ_exit";
        sld = characterFromId("manRapeWife_" + npchar.City);
        RemovePassenger(pchar, sld);
        sld.lifeDay = 0;
        sTemp = "SCQ_" + npchar.index;
        pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
        AddMoneyToCharacter(pchar, sti(npchar.quest.money));
        TakeNItems(pchar, npchar.quest.gem, 12 + drand(8));
        sTitle = npchar.city + "SCQ_manRapeWife";
        CloseQuestHeader(sTitle);
        break;
    case "SCQR_manFriend":
        dialog.text = "Отлично!.. Вот то, что я вам обещал - " + FindRussianMoneyString(sti(npchar.quest.money)) + " и драгоценности. И спасибо вам, капитан.";
        link.l1 = "Не за что, дружище. Прощай...";
        link.l1.go = "SCQ_exit";
        sTemp = "SCQ_" + npchar.index;
        pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
        AddMoneyToCharacter(pchar, sti(npchar.quest.money));
        TakeNItems(pchar, npchar.quest.gem, 8 + drand(8));
        sTitle = npchar.city + "SCQ_manFriend";
        CloseQuestHeader(sTitle);
        break;
    //========= квесты баб ===========
    case "SCQ_woman":
        dialog.text = LinkRandPhrase("Здравствуйте, капитан. Я хотела попросить вас об одном одолжении.",
                                     "Капитан! Помогите женщине, будьте так добры...",
                                     "Капитан, не откажите " + GetSexPhrase("даме", "мне") + " в помощи.");
        link.l1 = RandPhraseSimple("Я занят" + GetSexPhrase("", "а") + ", красавица, не сегодня!", "Прошу прощения, " + GetAddress_FormToNPC(NPChar) + ", но в данный момент я не имею времени...");
        link.l1.go = "SCQ_exit";
        link.l2 = RandPhraseSimple("Что у вас стряслось, " + GetAddress_FormToNPC(NPChar) + "?", "Излагайте суть проблемы, " + GetAddress_FormToNPC(NPChar) + ". Я постараюсь вам помочь.");
        link.l2.go = "SCQ_woman_1";
        break;
    //выбираем квест
    case "SCQ_woman_1":
        switch (npchar.quest.SeekCap.numQuest)
        {
        case "0":
            dialog.text = "Мой муж занимается коммерцией - доставляет грузы торговцам по всей округе. Так вот, он ушел в море уже больше трех месяцев назад, и до сих пор не вернулся!";
            link.l1 = "Вы думаете, с ним что-то случилось?";
            link.l1.go = "SCQ_Hasband";
            break;
        case "1":
            dialog.text = "" + GetSexPhrase("Капитан, вот смотрю я на вас и вижу бравого капитана, отменного головореза", "Капитан, я вижу вы сильная и отважная женщина, любого мужика за пояс заткнете") + "...";
            link.l1 = "Это вы к чему, " + GetAddress_FormToNPC(NPChar) + "?";
            link.l1.go = "SCQ_Revenge";
            break;
        case "2":
            dialog.text = "Капитан, помогите мне, умоляют вас! Мой муж попал к пиратам! Вы можете спасти его?";
            link.l1 = "Подождите, что-то я не очень понимаю, кто к кому попал...";
            link.l1.go = "SCQ_Pirates";
            break;
        }
        break;

    //жещина разыскивает мужа-торговца
    case "SCQ_Hasband":
        dialog.text = "Не знаю, но очень надеюсь, что он просто занят по работе. Хотя мог бы отправить весточку, знает ведь, что я волнуюсь!";
        link.l1 = "В море сейчас неспокойно, всякое может случиться...";
        link.l1.go = "SCQ_Hasband_1";
        break;
    case "SCQ_Hasband_1":
        npchar.quest.SeekCap = "womanHasband"; //личный флаг ситизена на квест
        SetSeekCapCitizenParam(npchar, sti(npchar.nation));
        dialog.text = "Вот! Вы понимаете, о чем я говорю. По виду вы " + GetSexPhrase("капитан бравый", "девушка бравая") + ", поэтому я и хотела попросить вас о том, чтобы вы нашли моего мужа. За это я готова заплатить вам " + FindRussianMoneyString(sti(npchar.quest.money)) + " и отдам свои драгоценности.";
        link.l1 = "Хорошо. Если я встречу вашего мужа в море или где-нибудь еще, то сообщу ему о вашем беспокойстве. И скажите мне, как зовут вашего супруга и что у него за корабль.";
        link.l1.go = "SCQ_Hasband_2";
        link.l2 = "Такие деньги меня не интересуют. К сожалению, я вынужден" + GetSexPhrase("", "а") + " отказаться...";
        link.l2.go = "SCQ_exit_clear";
        break;
    case "SCQ_Hasband_2":
        dialog.text = "Его зовут " + npchar.quest.SeekCap.capName + ". А работает он на " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + " с именем '" + npchar.quest.SeekCap.shipName + "'.";
        link.l1 = "Понятно. Ну что же, теперь ожидайте. И постарайтесь находиться преимущественно в церки, чтобы я не искал" + GetSexPhrase("", "а") + " вас по городу...";
        link.l1.go = "exit";
        //==> ставим квестодателя в церковь
        pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
        npchar.location = npchar.city + "_church";
        npchar.location.locator = "goto2";
        pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
        pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
        pchar.quest.SeekShip_Stay.Idx = npchar.index;
        NextDiag.TempNode = "SCQ_womanResult";
        sTitle = npchar.city + "SCQ_womanHasband";
        ReOpenQuestHeader(sTitle);
        AddQuestRecordEx(sTitle, "SCQ_womanHasband", "1");
        AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
        AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
        AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        break;
    //месть отвергнутой женщины
    case "SCQ_Revenge":
        dialog.text = "" + GetSexPhrase("Это я к тому, любезный, что я хочу нанять вас по прямому назначению, так сказать... ", "Я хочу, чтобы вы помогли мне. Надеюсь, что вы меня поймете, как женщина. ") + "Мне порядком досадил один капитан, я желаю, чтобы он умер.";
        link.l1 = "О-хо-хо! Вот это да! И что же он вам сделал, этот несчастный?";
        link.l1.go = "SCQ_Revenge_1";
        break;
    case "SCQ_Revenge_1":
        dialog.text = "Этот мерзавец обманул меня. Он делал вид, что я ему нравлюсь, даже ухаживал за мной. А оказалось, что ему нужно кое-что от моего мужа! И когда этот проходимец получил кредит, вдруг оказалось, что ничего такого он не имел в виду...";
        link.l1 = "Хм, а может, и имел?..";
        link.l1.go = "SCQ_Revenge_2";
        break;
    case "SCQ_Revenge_2":
        dialog.text = "Я что, по-вашему, дура?! Не умею отличить ухаживания от пустой болтовни?";
        link.l1 = "Да нет, что вы...";
        link.l1.go = "SCQ_Revenge_3";
        break;
    case "SCQ_Revenge_3":
        dialog.text = "Он просто воспользовался мной, этот мерзавец! Никогда ему этого не прощу!..";
        link.l1 = "Хм... " + GetSexPhrase("а", "да, мужчины на это способны. Но,") + " может, вы остынете? Ну, пройдет день-другой, и все изменится...";
        link.l1.go = "SCQ_Revenge_4";
        break;
    case "SCQ_Revenge_4":
        dialog.text = "Изменится?! " + GetSexPhrase("Да вы моралист какой-то, а не пират", "Видимо, вы никогда не бывали в такой ситуации! Ну да, кто бы рискнул... а я всего лишь слабая женщина...") + "!";
        link.l1 = "" + GetSexPhrase("Ну что вы! ", "") + "Я просто хочу знать, насколько ваши намерения серьезны.";
        link.l1.go = "SCQ_Revenge_5";
        break;
    case "SCQ_Revenge_5":
        dialog.text = "Черт возьми, " + GetSexPhrase("вы просто не знаете, что такое месть отвергнутой женщины", "вы же женщина, и должны понимать, каково это - быть отвергнутой! Я хочу отомстить") + "!..";
        link.l1 = "" + GetSexPhrase("Это верно, как-то не довелось", "Ну, знаете, некоторые просто поплачут и все") + "...";
        link.l1.go = "SCQ_Revenge_6";
        break;
    case "SCQ_Revenge_6":
        dialog.text = "" + GetSexPhrase("Считайте, что вам повезло. Отвергнутая и обманутая в своих ожиданиях женщина - это фурия, дьявол в юбке! Нет ничего, способного смягчить ее гнев", "А вот я не такая. И нет ничего, что может смягчить мой гнев") + "!\nТак что я хочу, чтобы вы убили его лично. А перед смертью он должен узнать, кто все это организовал...";
        link.l1 = "Хм, даже не знаю что сказать... И сколько вы готовы за это заплатить?";
        link.l1.go = "SCQ_Revenge_7";
        break;
    case "SCQ_Revenge_7":
        npchar.quest.SeekCap = "womanRevenge"; //личный флаг ситизена на квест
        SetSeekCapCitizenParam(npchar, PIRATE);
        dialog.text = "Все, что у меня есть. Я отдам вам мои драгоценности и " + FindRussianMoneyString(sti(npchar.quest.money)) + "! Устроит?";
        link.l1 = "Ну что же, мне это интересно. Расскажите мне, кто ваш обидчик, капитаном какого корабля он является?";
        link.l1.go = "SCQ_Revenge_8";
        link.l2 = "" + GetSexPhrase("Пожалуй, я проявлю мужскую солидарность. ", "") + "Извините, без меня...";
        link.l2.go = "SCQ_exit_clear";
        break;
    case "SCQ_Revenge_8":
        dialog.text = "Этого негодяя зовут " + npchar.quest.SeekCap.capName + ", он является капитаном " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Acc")) + " с именем '" + npchar.quest.SeekCap.shipName + "'.";
        link.l1 = "Считайте, что ваш заказ принят к исполнению, " + GetAddress_FormToNPC(NPChar) + ". А теперь ждите меня в местной церкви. Надеюсь, теперь вас хоть немного отпустит...";
        link.l1.go = "exit";
        //==> ставим квестодателя в церковь
        pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
        npchar.location = npchar.city + "_church";
        npchar.location.locator = "goto2";
        pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
        pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
        pchar.quest.SeekShip_Stay.Idx = npchar.index;
        NextDiag.TempNode = "SCQ_womanResult";
        sTitle = npchar.city + "SCQ_womanRevenge";
        ReOpenQuestHeader(sTitle);
        AddQuestRecordEx(sTitle, "SCQ_womanRevenge", "1");
        AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
        AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
        AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
        AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
        AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся", "ась"));
        AddQuestUserData(sTitle, "sSex1", GetSexPhrase("ен", "на"));
        AddQuestUserData(sTitle, "sSex2", GetSexPhrase("", "а"));
        break;
    //муж женщины попал в плен к пиратам
    case "SCQ_Pirates":
        dialog.text = "Сейчас я вам объясню. Дело в том, мой муж, совершенно обычный человек, был захвачен пиратами! Они убивали всех, никого не щадили...";
        link.l1 = "Значит, капитан посмел оказать сопротивление. Если бы они сдались, никого бы не тронули.";
        link.l1.go = "SCQ_Pirates_1";
        break;
    case "SCQ_Pirates_1":
        dialog.text = "Может быть, но мой муж тут совершенно ни при чем. Он был простым пассажиром на этом корабле. Так вот, чтобы спасти свою жизнь, ему пришлось сказать, что он сказочно богат. Пираты его пощадили, и даже не бросили в трюм.";
        link.l1 = "А откуда вы знаете?";
        link.l1.go = "SCQ_Pirates_2";
        break;
    case "SCQ_Pirates_2":
        dialog.text = "Мужу удалось отправить мне письмо, где он пишет, что с ним все в порядке. Его держат в каюте, не как других пленников.";
        link.l1 = "И что вы намерены делать? Так долго продолжаться не может. Рано или поздно пираты его раскусят.";
        link.l1.go = "SCQ_Pirates_3";
        break;
    case "SCQ_Pirates_3":
        dialog.text = "Вы ведь тоже пират? Да-да, я знаю... Умоляю вас, помогите нам, спасите моего мужа! В письме он описал пиратский корабль и назвал имя капитана. Вам ведь будет достаточно просто найти его!";
        link.l1 = "Не так это и просто, как вам кажется. Все пленники - законный приз захватившего корабль кэпа. Да и не могу я сделать это за короткий срок.";
        link.l1.go = "SCQ_Pirates_4";
        break;
    case "SCQ_Pirates_4":
        dialog.text = "Но вы же можете попытаться! К тому же, время на поиски есть. Мой муж далеко не дурак, он назвался негоциантом из Старого света, так что пираты не требуют за него денег немедленно - ехать за ними очень далеко. Если вы освободите его, то я отдам вам все, что у меня есть!";
        link.l1 = "И что у вас есть?";
        link.l1.go = "SCQ_Pirates_5";
        break;
    case "SCQ_Pirates_5":
        npchar.quest.SeekCap = "womanPirates"; //личный флаг ситизена на квест
        SetSeekCapCitizenParam(npchar, PIRATE);
        dialog.text = "Немного, " + FindRussianMoneyString(sti(npchar.quest.money)) + " и все мои драгоценности... Но я буду молиться за вашу душу до конца жизни!";
        link.l1 = "Да уж, действительно немного... Ну да ладно, я готов" + GetSexPhrase("", "а") + " помочь вам при случае.";
        link.l1.go = "SCQ_Pirates_6";
        link.l2 = "Сожалею, но это слишком мало для того, чтобы я напал" + GetSexPhrase("", "а") + " на своего коллегу, члена Берегового братства.";
        link.l2.go = "SCQ_exit_clear";
        break;
    case "SCQ_Pirates_6":
        dialog.text = "Спасибо вам, спасибо!!";
        link.l1 = "Если все получится, тогда и будете благодарить, а пока не стоит. Расскажите-ка лучше, как зовут вашего мужа и все, что вы знаете об этих пиратах.";
        link.l1.go = "SCQ_Pirates_7";
        break;
    case "SCQ_Pirates_7":
        makearef(forName, npchar.quest.SeekCap);
        forName.nation = npchar.nation;
        forName.sex = "man";
        SetRandomNameToCharacter(forName);  //npchar.quest.SeekCap.name - имя жены ситизена
        forName.lastname = npchar.lastname; //фамилия как и у жены есно
        dialog.text = "Мужа зовут " + GetFullName(forName) + ". Капитана пиратов зовут " + npchar.quest.SeekCap.capName + ", он промышляет на " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + " с именем '" + npchar.quest.SeekCap.shipName + "'.";
        link.l1 = "Ясно. Ну что же, теперь ожидайте и надейтесь, что мне повезет с поисками. Постарайтесь находиться в церкви, чтобы я мог" + GetSexPhrase("", "ла") + " вас там быстро найти.";
        link.l1.go = "exit";
        //==> ставим квестодателя в церковь
        pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
        npchar.location = npchar.city + "_church";
        npchar.location.locator = "goto2";
        pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
        pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
        pchar.quest.SeekShip_Stay.Idx = npchar.index;
        NextDiag.TempNode = "SCQ_womanResult";
        sTitle = npchar.city + "SCQ_womanPirates";
        ReOpenQuestHeader(sTitle);
        AddQuestRecordEx(sTitle, "SCQ_womanPirates", "1");
        AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
        AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
        AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
        AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        AddQuestUserData(sTitle, "sName2", GetFullName(forName));
        AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся", "ась"));
        AddQuestUserData(sTitle, "sSex1", GetSexPhrase("", "а"));
        break;
    // --- результаты женских квестов ---
    case "SCQ_womanResult":
        dialog.text = "Ой, капитан, я так рада вас видеть! Расскажите мне быстрей, что вы узнали по моему делу?";
        link.l1 = "Хм, напомните, " + GetAddress_FormToNPC(NPChar) + ", о каком деле идет речь?";
        link.l1.go = "SCQ_womanResult_exit";
        switch (npchar.quest.SeekCap)
        {
        case "womanHasbandover":
            dialog.text = "Ах, капитан, я получила письмо от мужа! В нем он пишет, что вы нашли его.";
            link.l1 = "Да, все верно, " + GetAddress_FormToNPC(NPChar) + ". Ваш муж, " + npchar.quest.SeekCap.capName + ", жив и здоров. Он просто заработался...";
            link.l1.go = "SCQR_womanHasband";
            break;
        case "womanRevengeover":
            dialog.text = "Что скажете, капитан? Вы сделали то, о чем я вас просила? Капитан " + npchar.quest.SeekCap.capName + " мертв?";
            link.l1 = "Да, он мертв, " + GetAddress_FormToNPC(NPChar) + ". Перед смертью он узнал, кто стал причиной его смерти. Последнее, что он слышал в этой жизни - ваше имя.";
            link.l1.go = "SCQR_womanRevenge";
            break;
        case "womanPiratesover":
            dialog.text = "Вы все-таки освободили моего мужа! Умоляю вас, скажите мне, это так?!!";
            link.l1 = "Да, сейчас он находится у меня на корабле. Можете его забирать, если " + npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname + " и есть ваш муж...";
            link.l1.go = "SCQR_womanPirates";
            break;
        }
        break;
    case "SCQ_womanResult_exit":
        switch (npchar.quest.SeekCap)
        {
        case "womanHasband":
            dialog.text = "Вы что, забыли, что обещали мне найти моего мужа? Его зовут " + npchar.quest.SeekCap.capName + "!";
            link.l1 = "О-о, да, конечно... Ничего я не забыл" + GetSexPhrase("", "а") + ", просто я пока так и не сумел" + GetSexPhrase("", "а") + " его разыскать.";
            link.l1.go = "exit";
            break;
        case "womanRevenge":
            dialog.text = "Я что-то не поняла! Вы забыли, что должны отправить на тот свет моего обидчика, капитана по имени " + npchar.quest.SeekCap.capName + "?!";
            link.l1 = "Ну что вы, " + GetAddress_FormToNPC(NPChar) + ", ни в коем разе. Ваш заказ в работе, ожидайте...";
            link.l1.go = "exit";
            break;
        case "womanPirates":
            dialog.text = "Господи, капитан, вы забыли, что обещали вызволить моего мужа из плена?!";
            link.l1 = "Я ничего не забыл" + GetSexPhrase("", "а") + ", работаю над этим. Ждите, " + GetAddress_FormToNPC(NPChar) + " " + npchar.lastname + ".";
            link.l1.go = "exit";
            break;
        }
        break;

    case "SCQR_womanHasband":
        dialog.text = "Боже мой, как я вам благодарна! Да, кстати, вот ваши " + FindRussianMoneyString(sti(npchar.quest.money)) + ". И еще раз спасибо!";
        link.l1 = "Хм, да не за что...";
        link.l1.go = "SCQ_exit";
        sTemp = "SCQ_" + npchar.index;
        pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
        AddMoneyToCharacter(pchar, sti(npchar.quest.money));
        TakeNItems(pchar, npchar.quest.gem, 8 + drand(8));
        sTitle = npchar.city + "SCQ_womanHasband";
        CloseQuestHeader(sTitle);
        break;
    case "SCQR_womanRevenge":
        dialog.text = "Отлично! Ну что же, вот ваши " + FindRussianMoneyString(sti(npchar.quest.money)) + " и драгоценности. Прощайте.";
        link.l1 = "Прощайте...";
        link.l1.go = "SCQ_exit";
        sTemp = "SCQ_" + npchar.index;
        pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
        AddMoneyToCharacter(pchar, sti(npchar.quest.money));
        TakeNItems(pchar, npchar.quest.gem, 10 + drand(8));
        TakeNItems(pchar, "jewelry47", rand(3));
        TakeNItems(pchar, "jewelry43", rand(3));
        TakeNItems(pchar, "jewelry41", rand(3));
        TakeNItems(pchar, "jewelry48", rand(3));
        TakeNItems(pchar, "jewelry51", rand(3));
        TakeNItems(pchar, "jewelry46", rand(3));
        TakeNItems(pchar, "jewelry49", rand(3));
        TakeNItems(pchar, "jewelry40", rand(3));
        sTitle = npchar.city + "SCQ_womanRevenge";
        CloseQuestHeader(sTitle);
        break;
    case "SCQR_womanPirates":
        dialog.text = "Конечно, это он!!! Господи, капитан, как же я вам благодарна! Вот ваши " + FindRussianMoneyString(sti(npchar.quest.money)) + ". Я буду молиться за вас каждый день, пока жива!";
        link.l1 = "Это приятно, молитесь...";
        link.l1.go = "SCQ_exit";
        sld = characterFromId("womanPirates_" + npchar.City);
        RemovePassenger(pchar, sld);
        sld.lifeDay = 0;
        sTemp = "SCQ_" + npchar.index;
        pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
        AddMoneyToCharacter(pchar, sti(npchar.quest.money));
        TakeNItems(pchar, npchar.quest.gem, 12 + drand(8));
        sTitle = npchar.city + "SCQ_womanPirates";
        CloseQuestHeader(sTitle);
        break;
    //========= разыскиваемый капитан-работорговец ===========
    case "CitizCap": //встреча на суше
        switch (npchar.quest.SeekCap)
        {
        case "manSlave":
            dialog.text = "Приветствую коллегу. Что ты хотел" + GetSexPhrase(", дружище", "а, подруга") + "?";
            link.l1 = "Тебя зовут " + GetFullName(npchar) + ", не так ли?";
            link.l1.go = "CCmanSlave";
            break;
        }
        break;
    case "CCmanSlave":
        dialog.text = "Да, это верно!";
        link.l1 = "Тогда тебе не повезло. Я сейчас назову тебе одно имя, а ты постарайся вспомнить этого человека. " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]) + ". Не припоминаешь?";
        link.l1.go = "CCmanSlave_1";
        break;
    case "CCmanSlave_1":
        dialog.text = "Хм, припоминаю...";
        link.l1 = "Так вот, он очень на тебя обижен, приятель. Так что пришло время рассчитаться за то, что ты продал свободного человека в рабство.";
        link.l1.go = "CCmanSlave_2";
        break;
    case "CCmanSlave_2":
        dialog.text = "Рассчитаться?! Это ты о чем?";
        link.l1 = "О том, что я прикончу тебя прямо здесь.";
        link.l1.go = "CCmanSlave_3";
        break;
    case "CCmanSlave_3":
        dialog.text = "Ты подумай, " + GetSexPhrase("дружище", "подруга") + ", ради кого ты стараешься! Это же совершенно ничтожный человечишка. Ему самое место - на плантациях тростника!";
        link.l1 = "Ну, не тебе места распределять. Так что придется ответить за содеянное!";
        link.l1.go = "CCmanSlave_4";
        break;
    case "CCmanSlave_4":
        dialog.text = "Хо! Ну что же, отвечу, как умею!";
        link.l1 = "Давай-давай...";
        link.l1.go = "CCmanSlave_fight";
        break;
    case "CCmanSlave_fight":
        NextDiag.TempNode = "CitizCap_inDeck_exit";
        npchar.DeckDialogNode = "CitizCap_inDeck_exit";
        LAi_group_Attack(NPChar, Pchar);
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

    case "CitizCap_inDeck": //встреча на палубе
        dialog.text = "Что тебе нужно у меня на палубе?";
        link.l1 = "Хочу спросить тебя, не занимаешься ли ты извозом пассажиров?";
        link.l1.go = "CitizCap_inDeck_1";
        break;
    case "CitizCap_inDeck_1":
        dialog.text = "А тебе какое дело?";
        link.l1 = "Да просто так спрашиваю...";
        link.l1.go = "CitizCap_inDeck_2";
        break;
    case "CitizCap_inDeck_2":
        dialog.text = "Просто так... Слушай, убирайся-ка ты отсюда, пока даю тебе такую возможность. Не нравишься ты мне!";
        link.l1 = "Ладно, ладно, не кипятись. Уже ухожу...";
        link.l1.go = "exit";
        NextDiag.TempNode = "CitizCap_inDeck_exit";
        npchar.DeckDialogNode = "CitizCap_inDeck_exit";
        sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
        AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
        break;
    case "CitizCap_inDeck_exit":
        dialog.text = "Поговорили уже, не нарывайся!";
        link.l1 = "Да я не нарываюсь.";
        link.l1.go = "exit";
        NextDiag.TempNode = "CitizCap_inDeck_exit";
        break;
    //========= разыскиваемый кэп, похитивший чужую жену ===========
    case "RapeWifeCap": //встреча на суше
        sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
        dialog.text = "Приветствую коллегу! Ты что-то хотел" + GetSexPhrase(", дружище", "а, подруга") + ",?";
        link.l1 = "Я хотел" + GetSexPhrase("", "а") + " узнать, не ты ли забрал из " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen") + " женщину, по имени " + GetFullName(sld) + "?";
        link.l1.go = "RapeWifeCap_1";
        break;
    case "RapeWifeCap_1":
        dialog.text = "Хех, так и есть, она у меня в каюте! Хороша, чертовка!.. А зачем ты спрашиваешь?";
        link.l1 = "Приятель, эта дама замужем. Ты похитил замужнюю женщину!";
        link.l1.go = "RapeWifeCap_2";
        break;
    case "RapeWifeCap_2":
        dialog.text = "Ну и что с того? Она мне нравится, и дело с концом. И я не позволю какому-то оборванцу вмешиваться в наши отношения только потому, что он ее муж, видите ли!..";
        link.l1 = "Позволю себе заметить, что Береговое Братство такие вот фортеля не поощряет.";
        link.l1.go = "RapeWifeCap_3";
        break;
    case "RapeWifeCap_3":
        dialog.text = "Ты что, мораль мне тут читать надумал" + GetSexPhrase("", "а") + "? Береговое Братство к этому делу никакого отношения не имеет, так что твои разговоры ни к чему не приведут. Она моя, и точка!";
        link.l1 = "Не заводись, я просто поинтересовал" + GetSexPhrase("ся", "ась") + "... Прощай.";
        link.l1.go = "exit";
        NextDiag.TempNode = "RapeWifeCap_exit";
        npchar.DeckDialogNode = "RapeWifeCap_exit";
        sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
        AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
        break;
    case "RapeWifeCap_exit":
        dialog.text = "Поговорили уже о женщинах. Больше не желаю это обсуждать!";
        link.l1 = "Ладно...";
        link.l1.go = "exit";
        NextDiag.TempNode = "RapeWifeCap_exit";
        break;
    case "RapeWifeCap_inDeck": //встреча на палубе
        sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
        dialog.text = "Рад приветствовать коллегу у себя на палубе! Что ты хотел" + GetSexPhrase("", "а") + " обсудить со мной, " + GetSexPhrase("дружище", "подруга") + "?";
        link.l1 = "Я хотел" + GetSexPhrase("", "а") + " узнать, не ты ли забрал из " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen") + " женщину, по имени " + GetFullName(sld) + "?";
        link.l1.go = "RapeWifeCap_1";
        break;
    case "RapeWifeCap_inDeck_1":
        dialog.text = "Хех, так и есть, она у меня в каюте! Хороша, чертовка!.. А зачем ты спрашиваешь?";
        link.l1 = "Приятель, эта дама замужем. Ты похитил замужнюю женщину!";
        link.l1.go = "RapeWifeCap_inDeck_2";
        break;
    case "RapeWifeCap_inDeck_2":
        dialog.text = "Ну и что с того? Она мне нравится, и дело с концом. И я не позволю какому-то оборванцу вмешиваться в наши отношения только потому, что он ее муж, видите ли!..";
        link.l1 = "Позволю себе заметить, что Береговое Братство такие вот фортеля не поощряет.";
        link.l1.go = "RapeWifeCap_inDeck_3";
        break;
    case "RapeWifeCap_inDeck_3":
        dialog.text = "Ты что, мораль мне тут читать надумал" + GetSexPhrase("", "а") + "? Береговое Братство к этому делу никакого отношения не имеет, так что твои разговоры ни к чему не приведут. Она моя, и точка!";
        link.l1 = "Не заводись, я просто поинтересовал" + GetSexPhrase("ся", "ась") + "... В общем, бывай, приятель.";
        link.l1.go = "exit";
        NextDiag.TempNode = "RapeWifeCap_exit";
        npchar.DeckDialogNode = "RapeWifeCap_exit";
        sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
        AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
        break;
    case "RapeWifeCap_Board": //абордаж
        sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
        dialog.text = "Что тебе нужно, каналья?!!";
        link.l1 = "Я приш" + GetSexPhrase("ел", "ла") + " за женщиной, что ты украл у мужа. Вспомни " + XI_ConvertString("Colony" + npchar.quest.cribCity) + "! Ее зовут " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
        link.l1.go = "RapeWifeCap_Board_1";
        break;
    case "RapeWifeCap_Board_1":
        dialog.text = "Дьявол!! Тебе не видать ее как своих ушей!";
        link.l1 = "Ха, идиот!! Свои уши я вижу в зеркале! А твои сейчас обрежу...";
        link.l1.go = "RapeWifeCap_Board_2";
        break;
    case "RapeWifeCap_Board_2":
        LAi_SetCurHPMax(npchar);
        QuestAboardCabinDialogFree(); // важный метод
        LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
        pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
        pchar.GenQuest.CitizSeekCap.nation = npchar.nation;       //нацию для нпс
        pchar.GenQuest.CitizSeekCap.sex = "woman";
        pchar.GenQuest.CitizSeekCap.ani = "towngirl";
        pchar.GenQuest.CitizSeekCap.model = "women_" + (drand(3) + 7); //модель для нпс
        pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity;  //исходный город для нпс
        sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
        pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
        pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        break;
    //========= похищенная жена ===========
    case "manRapeWife_Board":
        dialog.text = "Кто вы?";
        link.l1 = "Здравствуйте. Я приш" + GetSexPhrase("ел", "ла") + " за вами по поручению вашего мужа. Теперь, когда вы свободны, мне нужно отвезти вас к нему.";
        link.l1.go = "manRapeWife_Board_1";
        break;
    case "manRapeWife_Board_1":
        dialog.text = "Неужели это не сон?! Это правда?!";
        link.l1 = "Чистейшая правда, " + GetAddress_FormToNPC(NPChar) + ".";
        link.l1.go = "manRapeWife_Board_2";
        break;
    case "manRapeWife_Board_2":
        dialog.text = "Слава Господу Всемогущему!!! Я готова, давайте быстрей уйдем отсюда!";
        link.l1 = "Хорошо, " + GetAddress_FormToNPC(NPChar) + ", готовьтесь к возвращению домой, к мужу.";
        link.l1.go = "exit";
        //уберем жену из каюты
        npchar.location = "none";
        npchar.location.locator = "";
        LAi_SetPlayerType(pchar);
        AddPassenger(pchar, npchar, false);
        SetCharacterRemovable(npchar, false);
        sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
        sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
        sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
        AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Acc"));
        break;
    //========= разыскиваемый земляк-торговый кэп ===========
    case "FriendCap": //встреча на суше
        dialog.text = "Здравствуйте! Рад приветствовать коллегу на суше...";
        link.l1 = TimeGreeting() + " А я наш" + GetSexPhrase("ел", "ла") + " вас по делу.";
        link.l1.go = "FriendCap_1";
        break;
    case "FriendCap_1":
        dialog.text = "Слушаю вас внимательно.";
        link.l1 = "Дело в том, что вас ищет ваш земляк, с которым вы отправились сюда из Старого света. " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]) + ", знакомое имя?";
        link.l1.go = "FriendCap_2";
        break;
    case "FriendCap_2":
        dialog.text = "Ха, еще бы! А где он живет?";
        link.l1 = "В " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Dat") + ". Я предлагал" + GetSexPhrase("", "а") + " ему отправиться со мной, но он отказался. Просит вас заехать к нему.";
        link.l1.go = "FriendCap_3";
        break;
    case "FriendCap_3":
        dialog.text = "Конечно, я это сделаю. Большое вам спасибо!.. Вы знаете, по вашему виду я сказал бы, что вы пират!";
        link.l1 = "Так и есть. Но я сегодня добр" + GetSexPhrase("ый", "ая") + ", так что тебе не о чем беспокоится. Всего хорошего.";
        link.l1.go = "exit";
        NextDiag.TempNode = "FriendCap_exit";
        npchar.DeckDialogNode = "FriendCap_exit";
        sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
        AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Acc"));
        sTemp = "SecondTimer_" + npchar.id;
        pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
        npchar.lifeDay = 0;
        sTemp = "SCQ_" + npchar.index;
        pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
        sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
        sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
        //удаляем запись в базе кэпов
        makearef(forName, NullCharacter.capitainBase);
        DeleteAttribute(forName, npchar.id);
        break;
    case "FriendCap_exit":
        dialog.text = "Все нормально, без проблем? Извините, я немного переживаю...";
        link.l1 = "Все в порядке, приятель.";
        link.l1.go = "exit";
        NextDiag.TempNode = "FriendCap_exit";
        break;
    case "FriendCap_inDeck": //встреча на палубе
        dialog.text = TimeGreeting() + ". Что вам нужно от меня? Я всего лишь торговый капитан, и...";
        link.l1 = "Я знаю, приятель. Не нервничай так, говорят, это вредно для здоровья. Я к тебе по делу.";
        link.l1.go = "FriendCap_inDeck_1";
        break;
    case "FriendCap_inDeck_1":
        dialog.text = "По какому делу?";
        link.l1 = "Тебя ищет твой земляк " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]) + ". Знаешь такого?";
        link.l1.go = "FriendCap_inDeck_2";
        break;
    case "FriendCap_inDeck_2":
        dialog.text = "О-о-о, нашелся все-таки! Очень хорошо... Вы меня извините за грубый прием, я, знаете ли, грешным делом подумал, что вы пират.";
        link.l1 = "Так и есть. Но тебе пока ничего не угрожает. Меня просили передать тебе сообщение, что я и сделал" + GetSexPhrase("", "а") + ". Твой земляк, кстати, живет и работает в " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Dat") + ".";
        link.l1.go = "FriendCap_inDeck_3";
        break;
    case "FriendCap_inDeck_3":
        dialog.text = "Вот это да!.. Вы - " + GetSexPhrase("благородный человек", "благородная девушка") + ". Спасибо вам!";
        link.l1 = "Не за что. Прощай и будь здоров, приятель.";
        link.l1.go = "exit";
        NextDiag.TempNode = "FriendCap_exit";
        npchar.DeckDialogNode = "FriendCap_exit";
        sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
        AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Acc"));
        npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
        sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
        sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
        //удаляем запись в базе кэпов
        makearef(forName, NullCharacter.capitainBase);
        DeleteAttribute(forName, npchar.id);
        break;
    //========= разыскиваемый муж-торговец ===========
    case "HasbandCap": //встреча на суше
        dialog.text = "Здравствуйте. Вы что-то хотели?";
        link.l1 = "Вас зовут " + GetFullName(npchar) + ", не так ли?";
        link.l1.go = "HasbandCap_1";
        break;
    case "HasbandCap_1":
        dialog.text = "Да, это я.";
        link.l1 = "Это, конечно, звучит глупо, но ваша жена просила меня передать, что очень за вас волнуется.";
        link.l1.go = "HasbandCap_2";
        break;
    case "HasbandCap_2":
        dialog.text = "Ха! Ну, это понятно... Вообще-то я настолько закрутился с работой, что мне не до нее сейчас. Выгодные предложения следуют одни за другими, я не могу упускать возможную выгоду только потому, что моя жена волнуется.";
        link.l1 = "Это конечно, но вы могли хотя бы написать ей, что с вами все в порядке.";
        link.l1.go = "HasbandCap_3";
        break;
    case "HasbandCap_3":
        dialog.text = "Да, вы правы. Немедленно ей отпишу!.. Спасибо вам огромное за участие в наших семейных делах!";
        link.l1 = "Не за что, дружище.";
        link.l1.go = "exit";
        NextDiag.TempNode = "HasbandCap_inDeck_exit";
        npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
        sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
        AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
        sTemp = "SecondTimer_" + npchar.id;
        pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
        npchar.lifeDay = 0;
        sTemp = "SCQ_" + npchar.index;
        pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
        sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
        sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
        //удаляем запись в базе кэпов
        makearef(forName, NullCharacter.capitainBase);
        DeleteAttribute(forName, npchar.id);
        break;
    case "HasbandCap_inDeck": //встреча на палубе
        dialog.text = "Здравствуйте. Чему обязан за честь видеть вас у себя на корабле?";
        link.l1 = "Вас зовут " + GetFullName(npchar) + ", не так ли?";
        link.l1.go = "HasbandCap_inDeck_1";
        break;
    case "HasbandCap_inDeck_1":
        dialog.text = "Да, это я.";
        link.l1 = "Это, конечно, звучит глупо, но ваша жена просила меня передать, что очень за вас волнуется.";
        link.l1.go = "HasbandCap_inDeck_2";
        break;
    case "HasbandCap_inDeck_2":
        dialog.text = "Фу, черт! А я, честно говоря, испугался - решил, что это знаменитый охотник за призами - Одноглазый Стид Хантер за мной увязался. Ну, хорошо, что ошибся...\nВы знаете, я настолько закрутился с работой, что мне не до нее сейчас. Выгодные предложения следуют одни за другими, я не могу упускать возможную выгоду только потому, что моя жена волнуется.";
        link.l1 = "Это конечно, но вы могли хотя бы написать ей, что с вами все в порядке.";
        link.l1.go = "HasbandCap_inDeck_3";
        break;
    case "HasbandCap_inDeck_3":
        dialog.text = "Да, вы правы. Я это обязательно сделаю в первом же порту на разгрузке... Спасибо вам огромное за участие в наших семейных делах!";
        link.l1 = "Не за что, дружище.";
        link.l1.go = "exit";
        NextDiag.TempNode = "HasbandCap_inDeck_exit";
        npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
        sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
        AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
        npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
        sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
        sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
        //удаляем запись в базе кэпов
        makearef(forName, NullCharacter.capitainBase);
        DeleteAttribute(forName, npchar.id);
        break;
    case "HasbandCap_inDeck_exit":
        dialog.text = "Еще раз примите мою благодарность...";
        link.l1 = "Да не стоит, все в порядке.";
        link.l1.go = "exit";
        NextDiag.TempNode = "HasbandCap_inDeck_exit";
        break;
    //========= разыскиваемый капитан-обманщик ===========
    case "RevengeCap": //встреча на суше
        dialog.text = "Рад видеть вас в этом городишке, капитан. Вам что-то нужно от меня?";
        link.l1 = "" + GetSexPhrase("Знаете, капитан... Фуф, даже не знаю, как это сказать!", "Да, нужно.") + "";
        link.l1.go = "RevengeCap_1";
        break;
    case "RevengeCap_1":
        dialog.text = "" + GetSexPhrase("Говорите, как есть.", "Интересно, и что же?") + "";
        link.l1 = "" + GetSexPhrase("Хм, так и поступлю... В общем, у", "У") + " меня к вам вопрос. Вы знакомы с дамой по имени " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]) + "?";
        link.l1.go = "RevengeCap_2";
        break;
    case "RevengeCap_2":
        dialog.text = "Хех, ну да, знаком. Имел несчастие общаться с ней. Вздорная дура, могу вам сказать...";
        link.l1 = "Гм... Так вот, эта вздорная дура наняла меня убить вас" + GetSexPhrase(", дружище. Вот так-то..", "") + ".";
        link.l1.go = "RevengeCap_3";
        break;
    case "RevengeCap_3":
        dialog.text = "Ну, это уже просто смешно...";
        link.l1 = "" + GetSexPhrase("Если бы не было так грустно... Сожалею, но за вашу", "Ничего смешного в этом нет. За вашу") + " голову назначена награда. И я намерен" + GetSexPhrase("", "а") + " ее получить.";
        link.l1.go = "RevengeCap_4";
        break;
    case "RevengeCap_4":
        dialog.text = "Хо-хо!.. Вы не шутите, капитан?";
        link.l1 = "" + GetSexPhrase("Нет, друг мой...", "Даже не думала!") + "";
        link.l1.go = "RevengeCap_5";
        break;
    case "RevengeCap_5":
        dialog.text = "" + GetSexPhrase("Да какой ты мне друг, идиот?! Ты и капитаном-то назваться не можешь. Так, прихвостень на побегушках у вздорной фурии", "Черт возьми! Одна вздорная фурия наняла другую! Что же это за дела такие творятся?") + "!";
        link.l1 = "" + GetSexPhrase("Вот как?!", "Ты использовал ее в своих корыстных целях, так что нечего удивляться тому, что она решила отомстить.") + "";
        link.l1.go = "RevengeCap_6";
        break;
    case "RevengeCap_6":
        dialog.text = "" + GetSexPhrase("Ну а как ты хотел, чтобы я тебя называл? Хоть как назови, суть-то не изменится...", "Женская солидарность, да?!") + "";
        link.l1 = "" + GetSexPhrase("", "Знаешь, пожалуй, и это тоже. ") + "Доставай свой клинок!";
        link.l1.go = "RevengeCap_7";
        break;
    case "RevengeCap_7":
        NextDiag.TempNode = "RevengeCapCap_exit";
        npchar.DeckDialogNode = "RevengeCapCap_exit";
        npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
        LAi_group_Attack(NPChar, Pchar);
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        break;
    case "RevengeCapCap_exit":
        dialog.text = "С тобой у меня уже был разговор. " + GetSexPhrase("Пошел вон, прохвост", "Убирайся, злыдня") + "...";
        link.l1 = "" + GetSexPhrase("Прохвост", "Злыдня") + "?! Ну ладно...";
        link.l1.go = "exit";
        NextDiag.TempNode = "RevengeCapCap_exit";
        break;
    case "RevengeCap_inDeck": //встреча на палубе
        dialog.text = "Рад видеть вас у меня на палубе, капитан. Зачем пожаловали?";
        link.l1 = "У меня к вам вопрос. Вы знакомы с дамой по имени " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]) + "?";
        link.l1.go = "RevengeCap_inDeck_1";
        break;
    case "RevengeCap_inDeck_1":
        dialog.text = "Хех, ну да, знаком. Имел несчастие общаться с ней. Вздорная дура, могу вам сказать...";
        link.l1 = "Хех, так вот эта вздорная дура наняла меня убить вас" + GetSexPhrase(", дружище. Вот так-то..", "") + ".";
        link.l1.go = "RevengeCap_inDeck_2";
        break;
    case "RevengeCap_inDeck_2":
        dialog.text = "Хи-хи... Капитан, не смешите меня. Если у вас больше нет ко мне дел, то прощайте.";
        link.l1 = "Ну что же, прощайте. Но имейте в виду то, что я вам сказал" + GetSexPhrase("", "а") + ".";
        link.l1.go = "RevengeCap_inDeck_3";
        break;
    case "RevengeCap_inDeck_3":
        dialog.text = "Обязательно, капитан, как же иначе?!";
        link.l1 = "Всего хорошего.";
        link.l1.go = "exit";
        NextDiag.TempNode = "RevengeCapCap_inDeck_exit";
        npchar.DeckDialogNode = "RevengeCapCap_inDeck_exit";
        npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
        break;
    case "RevengeCapCap_inDeck_exit":
        dialog.text = "Я больше не хочу говорить на эту тему, капитан. Это смешно.";
        link.l1 = "Ну, как знаете...";
        link.l1.go = "exit";
        NextDiag.TempNode = "RevengeCapCap_exit";
        break;
    case "RevengeCap_board": //абордаж
        dialog.text = "Что происходит, черт возьми?! Зачем вы напали на мой корабль?!";
        link.l1 = "По поручению " + GetSexPhrase("некой дамы,", "женщины") + " по имени " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]) + ". Эта особа вам знакома?";
        link.l1.go = "RevengeCap_board_1";
        break;
    case "RevengeCap_board_1":
        dialog.text = "Дьявол!!! Поверить не могу..." + GetSexPhrase("", " Одна злобная фурия наняла другую!") + "";
        link.l1 = "" + GetSexPhrase("А придется.", "Пришло тебе время ответить за свои подлые делишки!") + "";
        link.l1.go = "RevengeCap_board_2";
        break;
    case "RevengeCap_board_2":
        dialog.text = "Ну что же, я так просто умирать не намерен. За разговор спасибо, он прибавил мне сил. " + GetSexPhrase("Но прихвостня ", "И подружку ") + "этой фурии я хочу все-таки отправить на тот свет!";
        link.l1 = "Попробуйте, что я еще могу сказать?..";
        link.l1.go = "RevengeCap_board_3";
        break;
    case "RevengeCap_board_3":
        LAi_SetCurHPMax(npchar);
        //==> флаг квеста сменим у оригинального кэпа
        characters[sti(npchar.baseCapIdx)].quest.SeekCap = "womanRevengeFight";
        QuestAboardCabinDialogFree(); // важный метод
        LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        break;
    //========= вызволение мужа из пиратских затрюмков =========
    case "PiratesCap_inDeck": //встреча на палубе
        sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
        dialog.text = "Рад видеть вас у меня на палубе. Я чем-то могу помочь вам?";
        link.l1 = "Наверное, да. Я ищу человека, по имени " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
        link.l1.go = "PiratesCap_1";
        break;
    case "PiratesCap_inDeck_1":
        dialog.text = "Этот человек - мой пленник, и я планирую получить за него хороший выкуп.";
        link.l1 = "Я хочу его получить.";
        link.l1.go = "PiratesCap_inDeck_2";
        break;
    case "PiratesCap_inDeck_2":
        dialog.text = "Сожалею, но это невозможно. Если это все, то я прошу вас покинуть мой корабль.";
        link.l1 = "Хорошо, капитан, как скажете.";
        link.l1.go = "exit";
        NextDiag.TempNode = "PiratesCapCap_exit";
        npchar.DeckDialogNode = "PiratesCapCap_exit";
        sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
        AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
        break;
    case "PiratesCapCap_exit":
        dialog.text = "Мы уже говорили о моем пленнике. Ничего не изменилось.";
        link.l1 = "Понятно...";
        link.l1.go = "exit";
        break;
    case "PiratesCap": //встреча на суше
        sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
        dialog.text = "Приветствую, капитан. Я чем-то могу вам помочь?";
        link.l1 = "Наверное, да. Я ищу человека, по имени " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
        link.l1.go = "PiratesCap_1";
        break;
    case "PiratesCap_1":
        dialog.text = "Этот человек - мой пленник, и я планирую получить за него хороший выкуп.";
        link.l1 = "Я хочу его получить.";
        link.l1.go = "PiratesCap_2";
        break;
    case "PiratesCap_2":
        dialog.text = "Сожалею, но это невозможно.";
        link.l1 = "Жаль...";
        link.l1.go = "exit";
        NextDiag.TempNode = "PiratesCapCap_exit";
        npchar.DeckDialogNode = "PiratesCapCap_exit";
        sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
        AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
        break;
    case "PiratesCap_Board": //абордаж
        sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
        dialog.text = "Дьявол! Какого черта?!!";
        link.l1 = "Мне нужен твой пленник, по имени " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
        link.l1.go = "PiratesCap_Board_1";
        break;
    case "PiratesCap_Board_1":
        dialog.text = "Ха! Ну уж нет, только через мой труп...";
        link.l1 = "Как вам будет угодно.";
        link.l1.go = "PiratesCap_Board_2";
        break;
    case "PiratesCap_Board_2":
        LAi_SetCurHPMax(npchar);
        QuestAboardCabinDialogFree(); // важный метод
        LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
        pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap;      //флаг квеста для нпс
        pchar.GenQuest.CitizSeekCap.nation = npchar.nation;            //нацию для нпс
        pchar.GenQuest.CitizSeekCap.model = "citiz_" + (rand(9) + 11); //модель для нпс
        pchar.GenQuest.CitizSeekCap.sex = "man";
        pchar.GenQuest.CitizSeekCap.ani = "man";
        pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
        sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
        pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
        pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        break;
    //========= пленный муж ===========
    case "womanPirates_Board":
        dialog.text = "Кто вы?";
        link.l1 = "Я капитан " + GetFullName(pchar) + ". Вы не волнуйтесь, я приш" + GetSexPhrase("ел", "ла") + " за вами для того, чтобы отвезти к жене.";
        link.l1.go = "womanPirates_Board_1";
        break;
    case "womanPirates_Board_1":
        dialog.text = "Черт возьми, неужели это не сон?!";
        link.l1 = "Уверяю вас, это не сон... Ну что же, дело сделано, теперь уходим отсюда.";
        link.l1.go = "exit";
        //уберем мужа из каюты
        npchar.location = "none";
        npchar.location.locator = "";
        LAi_SetPlayerType(pchar);
        AddPassenger(pchar, npchar, false);
        SetCharacterRemovable(npchar, false);
        sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
        sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
        sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
        AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
        AddQuestUserData(sTitle, "sName", GetFullName(npchar));
        AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Acc"));
        break;

    case "plantation_slave":
        if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && findsubstr(npchar.id, "Slave_", 0) != -1)
        {
            dialog.text = RandPhraseSimple(RandPhraseSimple("Я так устал - просто с ног валюсь.", "Нет больше сил так жить!"), RandPhraseSimple("Эта работа слишком тяжелая для меня.", "Надсмотрщики уже не оставили живого места на моей шкуре!"));
            link.l1 = RandPhraseSimple("Сочувствую, приятель.", "Мне жаль тебя.");
            link.l1.go = "exit";
        }
        break;

    //=====================================================================================================================================
    // Warship, 25.05.11. && Jason 10.02.12 Серия миниквестов "Дело чести" -->
    //=====================================================================================================================================
    case "AffairOfHonor_1":
        LAi_CharacterDisableDialog(NPChar);

        if (LoadedLocation.type == "tavern")
        {
            // "Честь мундира".
            if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor"))
            {
                dialog.text = "О, капитан, выпейте со мной, я угощаю!";
                link.l1 = "С удовольствием.";
                link.l1.go = "AffairOfHonor_CoatHonor_1";
                PChar.QuestTemp.AffairOfHonor.CoatHonor = true;
                break;
            }
        }
        else
        {
            if (NPChar.sex == "man")
            {
                // "Невольник чести".
                if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.HonorSlave"))
                {
                    dialog.text = "Здравствуйте, капитан. Вы ведь капитан, и, судя по выправке, возможно даже военный?\nДа, да, вам-то уж наверняка известно как пользоваться шпагой, в отличие от моего непутевого сына, который, к тому же, рискует завтра поутру умереть... И все из-за этого похотливого мерзавца, положившего глаз на небезразличную моему бедному сыну даму!";
                    link.l1 = "Да, я и правда - капитан, и моя шпага не раз выручала меня, но что вам угодно? Объяснитесь!";
                    link.l1.go = "AffairOfHonor_HonorSlave_1";
                    PChar.QuestTemp.AffairOfHonor.HonorSlave = true;
                    break;
                }

                // "Красотка и пират".
                if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.BeautifulPirate"))
                {
                    dialog.text = "Здравствуйте, капитан. Позвольте поинтересоваться – вы, случайно, не пират? Хотя нет, конечно же, нет! Вы не пират. Пираты - они ужасно выглядят, и еще ужаснее ведут себя, а запах...";
                    link.l1 = "Что такого вам успели сделать пираты?";
                    link.l1.go = "AffairOfHonor_BeautifulPirate_1";
                    PChar.QuestTemp.AffairOfHonor.BeautifulPirate = true;
                    break;
                }

                // "Заносчивый нахал".
                if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Jackanapes"))
                {
                    //if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "FortFrance")
                    //{
                    // Jason: что за чудное условие? Типа - столица? Кроме Гаваны, квест более нигде не выпадет - остальные города непригодны априори. Убираю. Неразумно ограничивать одним городом.
                    dialog.text = "Эй, вы! Да – вы, скажите, где вас обучали манерам? Какого дьявола вы торчите здесь посреди дороги и мешаете мне пройти? Нет, вы поглядите, что за невежа! Я к вам обращаюсь! Дорогу!.. Понаехали тут!";
                    link.l1 = "Сударь, я, право, не желал быть вам помехой. Простите.";
                    link.l1.go = "AffairOfHonor_Exit";
                    link.l2 = "Сударь, полегче! Иначе вы рискуете не попасть туда, куда так спешите.";
                    link.l2.go = "AffairOfHonor_Jackanapes_1";
                    PChar.QuestTemp.AffairOfHonor.Jackanapes = true;
                    break;
                    //}
                }

                // "Волки и овцы".
                if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.WolvesAndSheeps"))
                {
                    dialog.text = "Здравствуйте, капитан. У меня к вам просьба, в выполнении которой вы не сможете мне отказать, если вы честный человек\nИтак, сразу к делу: примерно с месяц тому у нас в таверне остановился какой-то дворянин. Ну, остановился и ладно, только дворянин этот оказался на деле самый что ни на есть дебошир и негодяй! А теперь еще и убийца!";
                    link.l1 = "Если бы он убил безвинного человека, то сейчас наверняка уже гнил бы в казематах, ожидая суда и справедливого наказания. Разве не так?";
                    link.l1.go = "AffairOfHonor_WolvesAndSheeps_1";
                    PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps = true;
                    break;
                }

                // "Трусливый фехтовалщик".
                if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer"))
                {
                    dialog.text = "Капитан, постойте, прошу вас. Вы, судя по вашей выправке, гораздо лучше чем я разбираетесь во всех тонкостях искусства владения шпагой, поэтому я и собираюсь просить вас выполнить одно поручение, которое не в состоянии выполнить сам.";
                    link.l1 = "Весьма занятно. И что же такое вы мне собираетесь предложить?";
                    link.l1.go = "AffairOfHonor_CowardFencer_1";
                    PChar.QuestTemp.AffairOfHonor.CowardFencer = true;
                    break;
                }

                // "Божий суд".
                if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.GodJudgement"))
                {
                    dialog.text = "Постойте, прошу вас! Стойте... Не согласитесь ли вы помочь мне, несчастному, в одном деле, которое требует вмешательства такого бравого военного офицера, как вы?\nДело в том, что я повздорил из-за местных плантаций винограда со своим соседом, который, к слову говоря, подозревается в связях с контрабандистами. Да, да, а может и с пиратами, говорю я вам, иначе откуда у него внезапно появилось бы столько денег?\nЕще какой-то год назад он не имел средств на починку своего баркаса, а теперь претендует на мои виноградники, слышите – мои!..";
                    link.l1 = "Мне нет до этого никакого дела. Прощайте.";
                    link.l1.go = "exit";
                    link.l2 = "Позвольте, а куда смотрит местная власть?";
                    link.l2.go = "AffairOfHonor_GodJudgement_1";
                    PChar.QuestTemp.AffairOfHonor.GodJudgement = true;
                    break;
                }
            }
            else
            {
                // "Навязчивый кавалер".
                if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Cavalier"))
                {
                    dialog.text = "Капитан, капитан, прошу – защитите честь невинной девушки!";
                    link.l1 = "У меня нет на это времени, красотка. Поищи кого-нибудь еще...";
                    link.l1.go = "AffairOfHonor_Exit";
                    link.l2 = "Что случилось, девушка? Да не дрожи ты так! Рассказывай!";
                    link.l2.go = "AffairOfHonor_Cavalier_1";
                    PChar.QuestTemp.AffairOfHonor.Cavalier = true;
                    break;
                }
            }
        }

        dialog.text = "Явный баг. И откуда он только мог взяться? Сообщите об этом Warship'у, он все исправит.";
        link.l1 = RandSwear();
        link.l1.go = "exit";
        break;

    case "AffairOfHonor_Exit":
        ChangeCharacterComplexReputation(PChar, "nobility", -2);
        NextDiag.CurrentNode = "First time";
        DialogExit();
        break;

    case "AffairOfHonor_Cavalier_1":
        dialog.text = "Капитан, меня уже довольно долго преследует один из офицеров нашего гарнизона с недвусмысленными намеками и предложениями. Слышали бы вы, какие непристойные слухи он распространяет, пытаясь очернить меня в глазах горожан!\nК сожалению, у меня нет знакомых и друзей, способных защитить мое честное имя! Я в отчаянии! О, Боже, а вот и он! Помогите мне!";
        link.l1 = "Не волнуйся, я не дам тебя в обиду!";
        link.l1.go = "exit";
        int Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 12;
        int Scl = 30 + 2 * sti(pchar.rank);
        sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_Cavalier_Man", GetRandQuestSoldierModel(sti(NPChar.nation)), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
        // Jason: дохляки нам не нужны - делаем кулфайтера
        FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_12", "blade_14"), RandPhraseSimple("pistol6", "pistol5"), "bullet", Scl * 3);
        float Mft = MOD_SKILL_ENEMY_RATE / 20;
        sld.MultiFighter = 1.0 + Mft; // мультифайтер
        ChangeCharacterAddressGroup(sld, PChar.location, "goto", FindNearestFreeLocator("goto"));
        LAi_SetActorType(sld);
        LAi_ActorDialog(sld, PChar, "", -1, 5);
        LAi_SetImmortal(sld, true); // Еще успеем.
        sld.dialog.filename = "Quest\ForAll_dialog.c";
        sld.dialog.currentnode = "AffairOfHonor_Cavalier_2";
        PChar.QuestTemp.AffairOfHonor.Cavalier.Started = true;
        DisableAllExits(true);
        break;

    case "AffairOfHonor_Cavalier_2":
        dialog.text = "А, вот и вы, сударыня! Что, очередной поклонник, как я погляжу? Когда же вы угомонитесь, наконец? Наверное, никогда... Ступайте работать в бордель, там вам самое место...";
        link.l1 = "Офицер, прекратите оскорбления сами, иначе я заставлю вас это сделать!";
        link.l1.go = "AffairOfHonor_Cavalier_2a";
        break;

    case "AffairOfHonor_Cavalier_2a":
        dialog.text = "Хм... Кто это тут у нас? А-а, просоленный морем отважный капитан баркаса, так? И что вы сделаете, морской... лев?";
        link.l1 = "Эта дама - моя подруга! А для вас у меня найдется удар перчаткой по лицу!";
        link.l1.go = "AffairOfHonor_Cavalier_3";
        break;

    case "AffairOfHonor_Cavalier_3":
        dialog.text = "Что?! Вы собираетесь вызвать меня на дуэль из-за этой...";
        link.l1 = "Довольно! Жду вас через два часа у маяка. И не забудьте прихватить с собой шпагу!";
        link.l1.go = "AffairOfHonor_Cavalier_4";
        break;

    case "AffairOfHonor_Cavalier_4":
        DialogExit();
        DeleteAttribute(npchar, "LifeDay");
        DisableAllExits(false);
        LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
        Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
        LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
        SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
        // Jason: отсрочка на 2 часа как договаривались
        SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour() + 2, false);
        ReOpenQuestHeader("AffairOfHonor");
        AddQuestRecord("AffairOfHonor", "1");
        break;

    case "AffairOfHonor_Cavalier_5":
        dialog.text = "Ах, я все знаю, сударь! Вы даже не представляете, как я вам благодарна! Да хранит вас Господь! ";
        link.l1 = "Я рад, что оказался рядом и смог вам помочь. Будьте счастливы!";
        link.l1.go = "exit";
        ChangeCharacterComplexReputation(PChar, "nobility", 7);
        ChangeCharacterComplexReputation(pchar, "authority", 1);
        ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
        ChangeOfficersLoyality("good_all", 1);
        AddComplexSelfExpToScill(50, 50, 50, 50);
        AddCharacterExpToSkill(pchar, "Leadership", 300);
        AddCharacterExpToSkill(pchar, "Fortune", 100);
        npchar.lifeday = 0;
        LAi_CharacterDisableDialog(NPChar);
        break;

    case "AffairOfHonor_Cavalier_6":
        dialog.text = "Ах, вы ничуть не лучше остальных, оставьте меня!";
        link.l1 = "...";
        link.l1.go = "exit";
        LAi_CharacterDisableDialog(NPChar);
        break;

    case "AffairOfHonor_HonorSlave_1":
        sTemp = "";
        if (FindLocation(NPChar.city + "_brothel") != -1)
            sTemp = "или борделе ";
        dialog.text = "Ох, " + GetAddress_Form(NPChar) + "... Не смею надеяться, но возможно, на этот раз ваша шпага выручит и нашу семью?\nКак я и говорил, мой сын - он не дуэлянт, а тем временем завтра на рассвете ему предстоит драться. Ах, если бы здесь не была замешана дама и честь имени\nНо он не мог не принять этот вызов и теперь обречен, понимаете? Я в отчаянии, ведь это мой единственный сын и наследник, поэтому я прошу вас – заколите негодяя, бросившего вызов моему сыну раньше, чем наступит утро, и я не останусь в долгу, уж поверьте!\nВы найдете мерзавца в таверне " + sTemp + "– там, где и привыкли проводить время такие подонки, как он... Умоляю вас...";
        link.l1 = "Любезный, мне совершенно нет дела ни до вас, ни до вашего сына. Дайте пройти!";
        link.l1.go = "exit";
        link.l2 = "Хм. Вот значит как! Хорошо, посмотрим, что из этого выйдет...";
        link.l2.go = "AffairOfHonor_HonorSlave_1a";
        break;

    case "AffairOfHonor_HonorSlave_1a":
        dialog.text = "Вы правда поможете мне и моему бедному сыну? О, " + GetAddress_Form(NPChar) + "! Я буду молиться за вас и вашу удачу!";
        link.l1 = "Думаю, это мне не повредит...  Ждите!";
        link.l1.go = "AffairOfHonor_HonorSlave_2";
        break;

    case "AffairOfHonor_HonorSlave_2":
        DialogExit();
        Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 8;
        Scl = 30 + 2 * sti(pchar.rank);
        sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_HonorSlave_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
        // Jason: дохляки нам не нужны - делаем кулфайтера
        FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_04", "blade_06"), RandPhraseSimple("pistol1", "pistol5"), "bullet", Scl * 3);
        Mft = MOD_SKILL_ENEMY_RATE / 20;
        sld.MultiFighter = 1.0 + Mft; // мультифайтер
        if (rand(1) == 0 || FindLocation(NPChar.city + "_brothel") == -1 || CheckAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor"))
        {
            FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
            ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
            LAi_SetSitType(sld);
        }
        else
        {
            ChangeCharacterAddressGroup(sld, NPChar.city + "_brothel", "goto", "goto3");
            LAi_SetCitizenType(sld);
        }
        LAi_SetImmortal(sld, true); // Еще успеем.
        sld.dialog.filename = "Quest\ForAll_dialog.c";
        sld.dialog.currentnode = "AffairOfHonor_HonorSlave_3";
        SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
        PChar.QuestTemp.AffairOfHonor.HonorSlave.Started = true;
        ReOpenQuestHeader("AffairOfHonor");
        AddQuestRecord("AffairOfHonor", "3");
        break;

    case "AffairOfHonor_HonorSlave_3":
        dialog.text = "Что вам угодно, черт возьми? Я отдыхаю, и не хочу чтобы мне мешали. Тут полно свободных мест и свободных ушей, так что оставьте меня в покое, сударь!";
        link.l1 = "Тем не менее, придется отложить свой отдых до лучших времен.";
        link.l1.go = "AffairOfHonor_HonorSlave_3a";
        break;

    case "AffairOfHonor_HonorSlave_3a":
        dialog.text = "Что?! Да кто ты такой, чтобы указывать мне, что делать?!";
        link.l1 = "Ты забыл меня, а? А вот я тебя - нет!.. И я считаю, что такие мерзавцы, как ты, лишь понапрасну оскверняют нашу землю своим присутствием!";
        link.l1.go = "AffairOfHonor_HonorSlave_3b";
        break;

    case "AffairOfHonor_HonorSlave_3b":
        dialog.text = "А?! Моряк, да ты, похоже, пьян в стельку! Я тебя впервые вижу! Но я не намерен терпеть подобное! Даю тебе последний шанс спасти свою жалкую жизнь! Немедленно извинись, селедка копченая, и я так и быть, забуду твои дерзкие слова!";
        link.l1 = "Извиняются перед достойными людьми, а не перед грязными свиньями!";
        link.l1.go = "AffairOfHonor_HonorSlave_4";
        break;

    case "AffairOfHonor_HonorSlave_4":
        dialog.text = "Ах вот как! Ты нарываешься, вошь гальюнная?";
        link.l1 = "Я заткну эти слова тебе в глотку, крысеныш! Жду тебя на маяке через два часа, и не забудь прихватить с собой ржавую железку, которую таскаешь у себя на поясе!";
        link.l1.go = "AffairOfHonor_HonorSlave_5";
        break;

    case "AffairOfHonor_HonorSlave_5":
        dialog.text = "Ха! Я буду там!";
        link.l1 = "До скорой встречи!";
        link.l1.go = "AffairOfHonor_HonorSlave_6";
        break;

    case "AffairOfHonor_HonorSlave_6":
        DialogExit();
        LAi_CharacterDisableDialog(NPChar);
        Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
        LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
        // Jason: отсрочка на 2 часа как договаривались
        SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour() + 2, false);
        AddQuestRecord("AffairOfHonor", "3_1");
        break;

    case "AffairOfHonor_HonorSlave_7":
        dialog.text = "О, это вы! Если вы живы, то я смею предположить, что...";
        link.l1 = "Да, я жив, а ваш сын завтра утром может никуда не спешить.";
        link.l1.go = "AffairOfHonor_HonorSlave_8";
        break;

    case "AffairOfHonor_HonorSlave_8":
        dialog.text = "Какой хороший сегодня день! Пойду, обрадую супругу!\nКапитан, само провидение прислало вас нам на помощь. Вот, возьмите эти деньги вместе с бесконечной благодарностью от всего нашего семейства!";
        link.l1 = "Спасибо!";
        link.l1.go = "exit";
        iTemp = 50 + drand(5) * 10;
        TakeNItems(pchar, "gold_dublon", iTemp);
        Log_Info("Вы получили " + FindRussianDublonString(iTemp) + "");
        PlaySound("interface\important_item.wav");
        ChangeCharacterComplexReputation(pchar, "authority", 1);
        ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
        AddComplexSelfExpToScill(50, 50, 50, 50);
        AddCharacterExpToSkill(pchar, "Leadership", 200);
        AddCharacterExpToSkill(pchar, "Fortune", 50);
        npchar.lifeday = 0;
        LAi_CharacterDisableDialog(NPChar);
        break;

    case "AffairOfHonor_HonorSlave_9":
        dialog.text = "Прочь, убийца детей!";
        link.l1 = "...";
        link.l1.go = "exit";
        LAi_CharacterDisableDialog(NPChar);
        break;

    case "AffairOfHonor_BeautifulPirate_1":
        dialog.text = "Мне? Слава Господу – ничего, но вот моей сестре повезло гораздо меньше. Она прислуживает в таверне\nИ все бы ничего, но в последнее время повадился заглядывать в нашу таверну один капер грозного вида. Ну вылитый пират! Его судно стоит на рейде вот уже с неделю, не меньше. И мало того, что всю эту неделю он пьет, цепляется к посетителям и грозит расправой каждому, кто попробует помешать ему, так теперь еще и сестра говорит мне, что он хвалился украсть ее и увезти черт знает куда на своем корабле, если она откажется выполнять его похотливые предложения!\nЯ не знаю, что делать! Властям безразлична судьба какой-то там служанки, а мы, мирные обыватели, боимся этого капера. Помогите нам поставить негодяя на место, прошу вас!";
        link.l1 = "У меня нет времени успокаивать пьяниц по тавернам. Обратитесь к коменданту, это его работа.";
        link.l1.go = "exit";
        link.l2 = "Гм... Грозный капер? Хорошо, я разберусь, в чем там дело.";
        link.l2.go = "AffairOfHonor_BeautifulPirate_1a";
        break;

    case "AffairOfHonor_BeautifulPirate_1a":
        dialog.text = "Ах, спасибо, капитан! Я уверен, что он вас послушает, как моряк моряка! Сделайте так, чтобы он отстал от моей сестры раз и навсегда! Мы небогаты, но не останемся в долгу!";
        link.l1 = "Ладно-ладно... уже иду улаживать ваши проблемы. Ждите!";
        link.l1.go = "AffairOfHonor_BeautifulPirate_1_1";
        break;

    case "AffairOfHonor_BeautifulPirate_1_1":
        DialogExit();
        NextDiag.CurrentNode = "AffairOfHonor_BeautifulPirate_r";
        npchar.lifeday = 3;
        Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 12;
        Scl = 25 + 3 * sti(pchar.rank);
        Mft = MOD_SKILL_ENEMY_RATE / 15;
        sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_BeautifulPirate_Man", "mercen_" + (rand(9) + 1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
        // Jason: дохляки нам не нужны - делаем кулфайтера
        FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_10", "blade_13"), RandPhraseSimple("pistol6", "pistol4"), "bullet", Scl * 3);
        sld.MultiFighter = 1.0 + Mft; // мультифайтер
        FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
        ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
        LAi_SetSitType(sld);
        LAi_SetImmortal(sld, true); // Еще успеем.
        sld.dialog.filename = "Quest\ForAll_dialog.c";
        sld.dialog.currentnode = "AffairOfHonor_BeautifulPirate_2";
        SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
        PChar.QuestTemp.AffairOfHonor.BeautifulPirate.Started = true;
        ReOpenQuestHeader("AffairOfHonor");
        AddQuestRecord("AffairOfHonor", "5");
        break;

    case "AffairOfHonor_BeautifulPirate_r":
        dialog.text = "Ну как? Вы уже говорили с этим пиратом? Он оставит нас в покое?";
        link.l1 = "Ждите. Я работаю над этим.";
        link.l1.go = "exit";
        NextDiag.TempNode = "AffairOfHonor_BeautifulPirate_r";
        break;

    case "AffairOfHonor_BeautifulPirate_2":
        dialog.text = "Что надо? Не видишь, я развлекаюсь!";
        link.l1 = "Так-так... Значит, это и есть повелитель пивных кружек, похититель девушек, гроза городка собственной персоной, как я понимаю? А за городом, допустим, у маяка, на дуэли, вы так же храбры и решительны, как здесь в таверне?";
        link.l1.go = "AffairOfHonor_BeautifulPirate_2a";
        DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
        SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
        break;

    case "AffairOfHonor_BeautifulPirate_2a":
        dialog.text = "О-хо-хо! Да ты, я посмотрю, герой! Ладно, братишка, я сегодня добрый, так что прощаю тебя. Сходи-ка, купи мне пару пинт эля!";
        link.l1 = "Ты мне не братишка!.. Повторяю для особо непонятливых: на дуэли ты так же храбр, как и за столом?";
        link.l1.go = "AffairOfHonor_BeautifulPirate_3";
        break;

    case "AffairOfHonor_BeautifulPirate_3":
        dialog.text = "Это что, вызов?! Тебе скучно и хочется подраться? Хорошо, раз ты так этого добиваешься, я прогуляюсь к маяку и там выпущу тебе кишки, а потом вернусь сюда и разнесу эту чертову таверну вдребезги!";
        link.l1 = "Посмотрим, не разойдутся ли слова с делом!";
        link.l1.go = "AffairOfHonor_BeautifulPirate_4";
        break;

    case "AffairOfHonor_BeautifulPirate_4":
        DialogExit();
        LAi_CharacterDisableDialog(NPChar);
        Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
        LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
        SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
        break;

    case "AffairOfHonor_BeautifulPirate_5":
        dialog.text = "Ну как? Вы уже говорили с этим пиратом? Он оставит нас в покое? Сестра сказала, что он ушел из таверны и не вернулся...";
        link.l1 = "Поговорил. Он оказался грубым малым, но мои аргументы оказались убедительными. Вашей сестре больше ничего не угрожает.";
        link.l1.go = "AffairOfHonor_BeautifulPirate_6";
        break;

    case "AffairOfHonor_BeautifulPirate_6":
        dialog.text = "Всё?.. Мы можем вздохнуть спокойно? Спасибо огромное, капитан! А где... где этот негодяй?";
        link.l1 = "Он... у себя на корабле. Он решил выйти в море с первым же приливом.";
        link.l1.go = "AffairOfHonor_BeautifulPirate_7";
        break;

    case "AffairOfHonor_BeautifulPirate_7":
        dialog.text = "Вы оказали огромную услугу всем честным жителям нашей колонии! Вот, возьмите вознаграждение за вашу помощь. Оно скромное, но кроме него вы получите любовь и уважение всех моих знакомых, а их, поверьте, немало!";
        link.l1 = "Благодарствую! Удачи вам и вашей сестре. Желаю ей поскорее выйти замуж за достойного человека. Прощайте!";
        link.l1.go = "exit";
        iTemp = 50 + drand(5) * 10;
        AddMoneyToCharacter(pchar, iTemp * 100);
        ChangeCharacterComplexReputation(pchar, "authority", 1);
        ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
        AddComplexSelfExpToScill(50, 50, 50, 50);
        AddCharacterExpToSkill(pchar, "Leadership", 200);
        AddCharacterExpToSkill(pchar, "Fortune", 50);
        npchar.lifeday = 0;
        LAi_CharacterDisableDialog(NPChar);
        break;

    case "AffairOfHonor_Jackanapes_1":
        dialog.text = "Неужели? И как же вы планируете мне помешать?";
        link.l1 = "Шпагой - единственным способом, подходящим для такого наглеца, как вы.";
        link.l1.go = "AffairOfHonor_Jackanapes_1_1";
        break;

    case "AffairOfHonor_Jackanapes_1_1":
        dialog.text = "Прекрасно! Я жду вас через два часа у маяка, где у вас появится такая возможность.";
        link.l1 = "Отлично! Я буду непременно.";
        link.l1.go = "AffairOfHonor_Jackanapes_1_2";
        break;

    case "AffairOfHonor_Jackanapes_1_2":
        DialogExit();
        PChar.QuestTemp.AffairOfHonor.Jackanapes.Started = true;
        Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
        LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
        NPChar.id = "AffairOfHonor_Jackanapes_Man";
        LAi_SetImmortal(NPChar, true); // Еще успеем.
        SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
        // Jason: отсрочка на 2 часа как договаривались
        SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour() + 2, false);
        ReOpenQuestHeader("AffairOfHonor");
        AddQuestRecord("AffairOfHonor", "7");
        break;

    case "AffairOfHonor_Jackanapes_2":
        dialog.text = "Прочь с дороги, трус!";
        link.l1 = "...";
        link.l1.go = "exit";
        LAi_CharacterDisableDialog(NPChar);
        break;

    case "AffairOfHonor_WolvesAndSheeps_1":
        dialog.text = "Капитан, он не так прост, этот негодяй. Том, мой давний друг Том, безвинно погиб на дуэли от его руки, обвиненный в шулерстве за карточным столом! Все по закону, как говорит губернатор...";
        link.l1 = "Хм... Твой друг виноват сам – вместо того, чтобы жульничать в картах, нашел бы лучше себе работу.";
        link.l1.go = "AffairOfHonor_WolvesAndSheeps_2";
        break;

    case "AffairOfHonor_WolvesAndSheeps_2":
        dialog.text = "Да? А что вы скажете на то, что таких вот шулеров, как Том, за последние пару недель у нас в городке оказалось уже четверо? И все норовят обмануть именно нашего дворянина? Так вот что я вам скажу: шулер-то и есть сам этот дворянчик, уж поверьте мне на слово. А если не верите – проверьте сами.";
        link.l1 = "Проверить? Нет, я не люблю карточные игры. Без меня.";
        link.l1.go = "exit";
        link.l2 = "Пожалуй, я так и поступлю... Уж очень странной выглядит эта история.";
        link.l2.go = "AffairOfHonor_WolvesAndSheeps_3";
        break;

    case "AffairOfHonor_WolvesAndSheeps_3":
        dialog.text = "Капитан, я и несколько моих друзей собрали сумму денег, которую с удовольствием выплатим тому, кто сможет вывести этого господина на чистую воду и отомстить за все его злодеяния. Я буду ждать вас в городе, чтобы отдать вам ваше вознаграждение, когда вы выполните мою просьбу.";
        link.l1 = "Я сделаю это, если ваши слова окажутся правдой.";
        link.l1.go = "AffairOfHonor_WolvesAndSheeps_4";
        break;

    case "AffairOfHonor_WolvesAndSheeps_4":
        DialogExit();
        PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps.Started = true;
        npchar.lifeday = 3;
        // Jason: дохляки нам не нужны - делаем кулфайтера
        Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 10;
        Scl = 30 + 2 * sti(pchar.rank);
        Mft = MOD_SKILL_ENEMY_RATE / 20;
        sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_WolvesAndSheeps_Man", "citiz_" + (rand(9) + 1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
        FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_08", "blade_09"), RandPhraseSimple("pistol1", "pistol5"), "bullet", Scl * 3);
        sld.MultiFighter = 1.0 + Mft; // мультифайтер
        sld.skill.Fortune = 1;
        sld.Default = NPChar.city + "_tavern";
        sld.Default.group = "sit";
        sld.Default.ToLocator = "sit_front1";
        LAi_SetSitType(sld);
        ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_base1");
        LAi_SetImmortal(sld, true); // Еще успеем.
        sld.dialog.filename = "Quest\ForAll_dialog.c";
        sld.dialog.currentnode = "AffairOfHonor_WolvesAndSheeps_5";
        SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
        ReOpenQuestHeader("AffairOfHonor");
        AddQuestRecord("AffairOfHonor", "9");
        break;

    case "AffairOfHonor_WolvesAndSheeps_5":
        dialog.text = "Мое почтение, сударь! В вас сразу виден благородный господин и, возможно... игрок? Не желаете ли составить мне партию?";
        link.l1 = "Согласен! Обсудим ставки. Что скажете про 50 монет?";
        link.l1.go = "AffairOfHonor_WolvesAndSheeps_6";
        break;

    case "AffairOfHonor_WolvesAndSheeps_6":
        if (sti(PChar.money) < 200)
        {
            dialog.text = "Ты шутишь? У тебя ведь денег нет!";
            link.l1 = "И вправду...";
            link.l1.go = "exit";
            NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_5";
        }
        else
        {
            dialog.text = "Я рад уже самой возможности сыграть, а то с этими местными невежами я стал уже забывать, как выглядят карты.";
            link.l1 = "Ну что же, тогда сдавайте.";
            link.l1.go = "exit";
            PChar.QuestTemp.friend_in_tavern = NPChar.id;
            AddDialogExitQuest("alc");
            DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
            SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
            NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_7";
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        }
        break;

    case "AffairOfHonor_WolvesAndSheeps_7":
        dialog.text = "Итак, играем по 50 монет.";
        link.l1 = "...";
        link.l1.go = "AffairOfHonor_WolvesAndSheeps_8";
        PChar.GenQuest.Cards.npcharIdx = NPChar.index;
        PChar.GenQuest.Cards.iRate = 50;
        PChar.GenQuest.Cards.SitType = true;
        break;

    case "AffairOfHonor_WolvesAndSheeps_8":
        NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_9";
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        LaunchCardsGame();
        break;

    case "AffairOfHonor_WolvesAndSheeps_9":
        dialog.text = "Позвольте, что это?.. Не может быть! Сударь, вы – шулер! Верните мне нечестно выигранные вами деньги!";
        link.l1 = "Для такого обвинения необходимо иметь веские доказательства, " + GetAddress_FormToNPC(NPChar) + "! Или вы их предъявите мне здесь и сейчас, или извольте ответить за клевету, как и положено – на дуэли!";
        link.l1.go = "AffairOfHonor_WolvesAndSheeps_10";
        break;

    case "AffairOfHonor_WolvesAndSheeps_10":
        dialog.text = "Ах, вот вы как? Хорошо – дуэль! Сегодня, через два часа, у маяка!";
        link.l1 = "Решено!";
        link.l1.go = "AffairOfHonor_WolvesAndSheeps_11";
        break;

    case "AffairOfHonor_WolvesAndSheeps_11":
        AddDialogExitQuest("exit_sit");
        DialogExit();
        LAi_CharacterDisableDialog(NPChar);
        Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
        LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
        // Jason: отсрочка на 2 часа как договаривались
        SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour() + 2, false);
        break;

    case "AffairOfHonor_WolvesAndSheeps_12":
        dialog.text = "Какие новости, капитан?";
        link.l1 = "Вы оказались правы – я тоже получил обвинение в шулерстве, после чего и заколол обманщика на дуэли.";
        link.l1.go = "AffairOfHonor_WolvesAndSheeps_13";
        break;

    case "AffairOfHonor_WolvesAndSheeps_13":
        dialog.text = "Вот видите, видите, я знал! Спасибо вам от меня и моих друзей! Вот ваша награда, капитан.";
        link.l1 = "Благодарю вас.";
        link.l1.go = "exit";
        iTemp = 50 + drand(5) * 10;
        AddMoneyToCharacter(pchar, iTemp * 100);
        ChangeCharacterComplexReputation(pchar, "authority", 1);
        ChangeCharacterComplexReputation(PChar, "nobility", 2);
        ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
        AddComplexSelfExpToScill(50, 50, 50, 50);
        AddCharacterExpToSkill(pchar, "Leadership", 200);
        AddCharacterExpToSkill(pchar, "Fortune", 200);
        npchar.lifeday = 0;
        LAi_CharacterDisableDialog(NPChar);
        break;

    case "AffairOfHonor_CowardFencer_1":
        dialog.text = "Я уже говорил вам, что прибыл сюда в надежде получить место учителя фехтования? Нет? Так вот, у здешнего губернатора открыта вакансия учителя для его племянника, и я хотел занять это место, благо мне известны основы этого искусства, хоть самому и не доводилось применять его на практике\nЯ был уже практически принят на должность, но тут оказалось, что у местного торговца появились неприятности в лице какого-то устрашающего вида проходимца, и губернатор, с целью проверки моих профессиональных качеств, поручил мне уладить это дельце.";
        link.l1 = "Так и улаживайте, раз это ваша забота. Всего хорошего.";
        link.l1.go = "exit";
        link.l2 = "И что же нужно этому проходимцу от торговца, а вам от меня?";
        link.l2.go = "AffairOfHonor_CowardFencer_1_1";
        break;

    case "AffairOfHonor_CowardFencer_1_1":
        dialog.text = "Я думаю, что проходимец тот – наемник, а у наемника что за нужда? Старые долги, возможно, или иные счеты... Но видно сразу – настроен он решительно и сам по себе торговца в покое не оставит. А вас я и хотел просить как раз помочь торговцу, освободив его от неприятного общества, а тем самым и мне выполнить поручение губернатора\nМне очень нужно это место, а сам прогнать наемника я, боюсь, буду не в силах. Прошу вас, помогите, и я отдам вам все свои сбережения, иначе мне с позором придется покинуть город!";
        link.l1 = "Хорошо, хорошо, я помогу... учитель боевых искусств...";
        link.l1.go = "AffairOfHonor_CowardFencer_1_2";
        break;

    case "AffairOfHonor_CowardFencer_1_2":
        DialogExit();
        npchar.lifeday = 3;
        // Jason: дохляки нам не нужны - делаем кулфайтера
        Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 15;
        Scl = 30 + 3 * sti(pchar.rank);
        Mft = MOD_SKILL_ENEMY_RATE / 15;
        sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_CowardFencer_Man", "mercen_" + (rand(7) + 23), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
        FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_06", "blade_10"), RandPhraseSimple("pistol4", "pistol6"), "bullet", Scl * 3 + 70);
        sld.MultiFighter = 1.0 + Mft; // мультифайтер
        LAi_SetCitizenType(sld);
        ChangeCharacterAddressGroup(sld, NPChar.city + "_store", "goto", "goto3");
        LAi_SetImmortal(sld, true); // Еще успеем.
        sld.dialog.filename = "Quest\ForAll_dialog.c";
        sld.dialog.currentnode = "AffairOfHonor_CowardFencer_2";
        SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
        PChar.QuestTemp.AffairOfHonor.CowardFencer.Started = true;
        ReOpenQuestHeader("AffairOfHonor");
        AddQuestRecord("AffairOfHonor", "11");
        break;

    case "AffairOfHonor_CowardFencer_2":
        dialog.text = "Что хочешь? Не видишь, что я занят?!";
        link.l1 = "Так это вы не даете покоя этому уважаемому торговцу и занимаетесь вымогательством?";
        link.l1.go = "AffairOfHonor_CowardFencer_3";
        DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
        SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
        break;

    case "AffairOfHonor_CowardFencer_3":
        dialog.text = "Ба! Еще один защитник? Дешевле выйдет заплатить мне, чем ежедневно нанимать охрану. Простым убийством, в отличие от выбивания долгов, я занимаюсь с большой неохотой, поэтому если вы такой герой, приходите сегодня к маяку и там, на дуэли, мы посмотрим кто кого, а если нет – убирайтесь и не мешайте мне окончить дело.";
        link.l1 = "Договорились! Я буду вас ждать с нетерпением.";
        link.l1.go = "AffairOfHonor_CowardFencer_4";
        break;

    case "AffairOfHonor_CowardFencer_4":
        DialogExit();
        Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
        LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
        SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
        LAi_CharacterDisableDialog(NPChar);
        break;

    case "AffairOfHonor_CowardFencer_4_1":
        dialog.text = "Да вы оказывается трус похлеще моего...";
        link.l1 = "Что есть, то есть.";
        link.l1.go = "exit";
        LAi_CharacterDisableDialog(NPChar);
        break;

    case "AffairOfHonor_CowardFencer_5":
        dialog.text = "Какие новости, капитан?";
        link.l1 = "Наемник мертв. Надеюсь место теперь ваше?";
        link.l1.go = "AffairOfHonor_CowardFencer_6";
        break;

    case "AffairOfHonor_CowardFencer_6":
        dialog.text = "О, капитан, я вам премного благодарен! Возьмите вашу награду, а я поспешу к губернатору с докладом!";
        link.l1 = "Прощайте... учитель.";
        link.l1.go = "exit";
        ChangeCharacterComplexReputation(pchar, "authority", 1);
        ChangeCharacterComplexReputation(PChar, "nobility", 2);
        ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
        AddComplexSelfExpToScill(60, 60, 60, 60);
        AddCharacterExpToSkill(pchar, "Leadership", 200);
        AddCharacterExpToSkill(pchar, "Fortune", 200);
        npchar.lifeday = 0;
        LAi_CharacterDisableDialog(NPChar);
        GiveItem2Character(pchar, "chest");
        Log_Info("Вы получили сундук с дублонами");
        PlaySound("interface\important_item.wav");
        break;

    case "AffairOfHonor_CoatHonor_1":
        LAi_CharacterEnableDialog(NPChar);
        NextDiag.TempNode = "AffairOfHonor_CoatHonor_2";
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        PChar.QuestTemp.friend_in_tavern = npchar.id;
        AddDialogExitQuest("alc");
        break;

    case "AffairOfHonor_CoatHonor_2":
        dialog.text = "Еще по одной?";
        link.l1 = "Давайте.";
        link.l1.go = "AffairOfHonor_CoatHonor_2_1";
        break;

    case "AffairOfHonor_CoatHonor_2_1":
        dialog.text = "И еще!..";
        link.l1 = "Постойте! Да куда же вы так торопитесь?";
        link.l1.go = "AffairOfHonor_CoatHonor_2_2";
        break;

    case "AffairOfHonor_CoatHonor_2_2":
        dialog.text = "К черту вопросы! Выпьем!";
        link.l1 = "Хорошо, но после вы мне все-таки расскажете что с вами случилось?";
        link.l1.go = "AffairOfHonor_CoatHonor_2_3";
        break;

    case "AffairOfHonor_CoatHonor_2_3":
        dialog.text = "Вам правда интересно? Тогда слушайте, пока я еще могу говорить! Через пару дней я уже ничего не расскажу, потому что буду мертв... Да, мертв! А всему виной ром. Много рома и этот... этот офицер, которого сам дьявол, как видно, принес в тот вечер на мою голову!\nКонечно, если бы я не выпил тогда столько, то не ввязался бы в ссору с первой шпагой этого гарнизона, да и, пожалуй, всего города. Но что теперь? Я обречен, я пропал, я труп! Как глупо...";
        link.l1 = "Да, глупо. Но теперь вы наверняка будете вести себя умнее, если, конечно, останетесь в живых. Прощайте.";
        link.l1.go = "AffairOfHonor_CoatHonor_Exit";
        link.l2 = "Не менее глупо продолжать напиваться. Наверняка есть какой-либо выход!";
        link.l2.go = "AffairOfHonor_CoatHonor_2_4";
        break;

    case "AffairOfHonor_CoatHonor_2_4":
        dialog.text = "Какой? Дезертировать, потеряв честное имя и мундир офицера, или умереть самому, не дожидаясь, пока меня прирежут как свинью? Что вы мне посоветуете?";
        link.l1 = "Ни то, ни другое. Я вам помогу и попробую сделать так, что ваш противник не сможет нанести вам вреда к сроку, назначенному для дуэли. Где мне искать его?";
        link.l1.go = "AffairOfHonor_CoatHonor_2_5";
        break;

    case "AffairOfHonor_CoatHonor_2_5":
        dialog.text = "Вы серьезно? Вы сделаете это! О, клянусь честью, я в долгу не останусь!\nА найти его можно в городе. Тут живет его любовница, о которой неоднократно слышали все офицеры гарнизона, но ее адрес мне неизвестен, к сожалению...";
        link.l1 = "Этого достаточно. Ждите меня здесь. Пойду, пообщаюсь с вашей... первой шпагой.";
        link.l1.go = "AffairOfHonor_CoatHonor_3";
        break;

    case "AffairOfHonor_CoatHonor_Exit":
        DialogExit();
        AddDialogExitQuest("exit_sit");
        NextDiag.CurrentNode = NextDiag.TempNode;
        break;

    case "AffairOfHonor_CoatHonor_3":
        AddDialogExitQuest("exit_sit");
        NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_Next";
        DialogExit();
        SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 2, false);
        PChar.QuestTemp.AffairOfHonor.CoatHonor.Started = true;
        PChar.QuestTemp.AffairOfHonor.CoatHonor.CityId = NPChar.city;
        PChar.QuestTemp.AffairOfHonor.CoatHonor.NeedGenerateDuelMan = true;
        ReOpenQuestHeader("AffairOfHonor");
        AddQuestRecord("AffairOfHonor", "13");
        npchar.lifeday = 2;
        break;

    case "AffairOfHonor_CoatHonor_Next":
        dialog.text = "Какие вести вы мне несете, сударь? Добрые, или... не очень?";
        link.l1 = "Пока никаких. Ждите. Все будет хорошо.";
        link.l1.go = "exit";
        NextDiag.TempNode = "AffairOfHonor_CoatHonor_Next";
        break;

    case "AffairOfHonor_CoatHonor_Final":
        dialog.text = "Какие вести вы мне несете, сударь? Добрые, или... не очень?";
        link.l1 = "Всё разрешилось. Ваш возможный противник больше никому не сможет причинить вреда... Можете спать спокойно. Но, надеюсь, вы извлечете из случившегося уроки и более не будете задираться с незнакомыми людьми?";
        link.l1.go = "AffairOfHonor_CoatHonor_Final_1";
        break;

    case "AffairOfHonor_CoatHonor_Final_1":
        dialog.text = "Вы не шутите? Я... я вам крайне признателен, " + GetAddress_Form(NPChar) + "! Вот, возьмите всё, что у меня есть. Это мое жалование, отдаю всё до последнего гроша!\nУрок, говорите? Да, черт побери, вы правы! Более такого не повторится.";
        link.l1 = "Вот и славно. Прощайте, сударь...";
        link.l1.go = "AffairOfHonor_CoatHonor_Final_2";
        break;

    case "AffairOfHonor_CoatHonor_Final_2":
        DialogExit();
        npchar.lifeday = 0;
        NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_End";
        TakeNItems(pchar, "purse3", 1);
        Log_Info("Вы получили кошель дублонов");
        PlaySound("interface\important_item.wav");
        ChangeCharacterComplexReputation(pchar, "authority", 1);
        ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
        AddComplexSelfExpToScill(50, 50, 50, 50);
        AddCharacterExpToSkill(pchar, "Leadership", 200);
        AddCharacterExpToSkill(pchar, "Fortune", 50);
        break;

    case "AffairOfHonor_CoatHonor_End":
        dialog.text = "Еще раз большое спасибо, " + GetAddress_Form(NPChar) + ", за вашу помощь!";
        link.l1 = "Всегда пожалуйста...";
        link.l1.go = "exit";
        NextDiag.TempNode = "AffairOfHonor_CoatHonor_End";
        break;

    case "AffairOfHonor_CoatHonor_4":
        dialog.text = "Эй, какого черта?! Что вы делаете в покоях моей дамы? Убирайтесь отсюда немедленно, иначе я выставлю вас силой!";
        link.l1 = "Я хожу там, где мне вздумается, и не намерен отдавать отчет вам о своих действиях! Силой? Ну что же, попробуйте!";
        link.l1.go = "AffairOfHonor_CoatHonor_5";
        break;

    case "AffairOfHonor_CoatHonor_5":
        dialog.text = "Вот это наглость! Неслыханно! Сударь, вы забываетесь! Немедленно покиньте этот дом, или, клянусь, вам придется горько пожалеть о том, что родились на этот свет!";
        link.l1 = "Сколько гонору! Как бы вам не пришлось пожалеть об этом, " + GetAddress_FormToNPC(NPChar) + "! ";
        link.l1.go = "AffairOfHonor_CoatHonor_6";
        break;

    case "AffairOfHonor_CoatHonor_6":
        dialog.text = "Ах, так? Берегитесь! Здесь, в этом доме, ваша смерть будет выглядеть обычным убийством, тогда как сегодня у маяка, где обычно решаются споры подобного рода, все будет честь по чести, и вы своей смертью не сможете навредить моему имени!\nЯ вызываю вас на дуэль, " + GetAddress_Form(NPChar) + " наглец! Вы ответите за свою дерзость! Итак, через два часа вас устроит?";
        link.l1 = "Вполне, " + GetAddress_FormToNPC(NPChar) + " зазнайка.";
        link.l1.go = "AffairOfHonor_CoatHonor_7";
        break;

    case "AffairOfHonor_CoatHonor_7":
        dialog.text = "Тогда потрудитесь явиться в указанное время. У вас есть еще немного времени - как раз успеете заказать у нашего священника панихиду.";
        link.l1 = "По вам? Думаю, много чести. Увидимся на маяке!";
        link.l1.go = "AffairOfHonor_CoatHonor_8";
        break;

    case "AffairOfHonor_CoatHonor_8":
        DialogExit();
        Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
        LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
        // Jason: отсрочка на 2 часа как договаривались
        SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour() + 2, false);
        DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
        SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
        NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_9";
        LAi_SetWarriorType(npchar); // 140313
        break;

    case "AffairOfHonor_CoatHonor_9":
        dialog.text = "Убирайтесь отсюда!";
        link.l1 = "...";
        link.l1.go = "exit";
        NextDiag.TempNode = "AffairOfHonor_CoatHonor_9";
        break;

    case "AffairOfHonor_GodJudgement_1":
        dialog.text = "Вы имеете в виду губернатора? Ха! 'Божий суд' - вот что мне сказал губернатор в ответ на мои жалобы! Дуэль! Как вам это нравится? Я, тихий миролюбивый плантатор, и какой-нибудь приятель-головорез моего соседа\nКакая же это дуэль? Это убийство! А вы, несомненно, разбираетесь в делах такого рода. Поэтому я и прошу вас выступить моим представителем на предстоящей дуэли. Поверьте – я в долгу не останусь.";
        link.l1 = "Когда должен состояться поединок?";
        link.l1.go = "AffairOfHonor_GodJudgement_1_1";
        break;

    case "AffairOfHonor_GodJudgement_1_1":
        dialog.text = "Сегодня до полуночи у маяка. Так вы поможете мне?";
        link.l1 = "Хорошо, так и быть - помогу. Ждите меня в городе!";
        link.l1.go = "AffairOfHonor_GodJudgement_1_2";
        break;

    case "AffairOfHonor_GodJudgement_1_2":
        DialogExit();
        PChar.QuestTemp.AffairOfHonor.GodJudgement.Started = true;
        PChar.QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest = true;
        PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId = NPChar.city;
        Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
        LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
        SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
        SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
        npchar.lifeday = 3;
        // Jason: дохляки нам не нужны - делаем кулфайтера
        Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 12;
        Scl = 30 + 2 * sti(pchar.rank);
        Mft = MOD_SKILL_ENEMY_RATE / 20;
        sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man", "pirate_" + (rand(9) + 1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
        FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_05", "blade_07"), RandPhraseSimple("pistol1", "pistol5"), "bullet", Scl * 3);
        sld.MultiFighter = 1.0 + Mft; // мультифайтер
        LAi_SetImmortal(sld, true);   // Еще успеем.
        sld.dialog.filename = "Quest\ForAll_dialog.c";
        ReOpenQuestHeader("AffairOfHonor");
        AddQuestRecord("AffairOfHonor", "15");
        break;

    case "AffairOfHonor_GodJudgement_2":
        dialog.text = "Рассказывайте, как все прошло? Мы... простите, вы победили?";
        link.l1 = "Вам будет полезно знать, что на месте дуэли была устроена засада. Вероятно, этот ваш сосед решил перестраховаться и, на всякий случай, пригласил вместо одного представителя нескольких, да еще и отъявленных головорезов. Но, к счастью, я достаточно неплохо владею оружием.";
        link.l1.go = "AffairOfHonor_GodJudgement_3";
        break;

    case "AffairOfHonor_GodJudgement_3":
        dialog.text = "Так вот каков мерзавец мой сосед! Теперь-то, я надеюсь, у губернатора не будет повода отказать мне в просьбе взять под стражу этого негодяя! Спасибо вам! Вот ваша награда, а я поспешу в резиденцию.";
        link.l1 = "Прощайте.";
        link.l1.go = "exit";
        npchar.lifeday = 0;
        TakeNItems(pchar, "purse3", 1);
        TakeNItems(pchar, "purse" + (drand(2) + 1), 1);
        Log_Info("Вы получили два кошеля с дублонами");
        PlaySound("interface\important_item.wav");
        ChangeCharacterComplexReputation(pchar, "authority", 1);
        ChangeCharacterComplexReputation(PChar, "nobility", 3);
        ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
        AddComplexSelfExpToScill(50, 50, 50, 50);
        AddCharacterExpToSkill(pchar, "Leadership", 200);
        AddCharacterExpToSkill(pchar, "Fortune", 50);
        LAi_CharacterDisableDialog(NPChar);
        break;

    // Диалоги до боя -->
    case "AffairOfHonor_BeforeFight_1":
        dialog.text = "Жить без багов очень весело, потому они, сцуки, лезут непонять откуда и все портят.";
        link.l1 = "Да не боись, я сообщу команде разработчиков.";
        link.l1.go = "AffairOfHonor_BeforeFight_2";

        switch (AffairOfHonor_GetCurQuest())
        {
        case "Cavalier":
            dialog.text = "А вот и вы, прекрасно. Это мои друзья и секунданты. Приступим?";
            link.l1 = "Я к вашим услугам!";
            link.l1.go = "AffairOfHonor_BeforeFight_2";
            break;

        case "HonorSlave":
            dialog.text = "Все в сборе. Вы готовы?";
            link.l1 = "Да, можем начинать!";
            link.l1.go = "AffairOfHonor_BeforeFight_2";
            break;

        case "BeautifulPirate":
            dialog.text = "Ну, наконец-то! Я уж думал, что зря пришел в такую даль... Давайте закончим поскорее, ведь в таверне меня заждались красотка и ром!";
            link.l1 = "Уверен, вам больше не понадобится ни то, ни другое!";
            link.l1.go = "AffairOfHonor_BeforeFight_2" break;

        case "Jackanapes":
            dialog.text = "Вы все-таки пришли? Тем лучше! Начнем!";
            link.l1 = "Лучше бы вы не так спешили!";
            link.l1.go = "AffairOfHonor_BeforeFight_2" break;

        case "WolvesAndSheeps":
            dialog.text = "Сударь, вот мои секунданты. А теперь – приготовьтесь к смерти!";
            link.l1 = "Советую и вам это сделать!";
            link.l1.go = "AffairOfHonor_BeforeFight_2" break;

        case "CowardFencer":
            dialog.text = "Ну вот вы и пришли. Шпагу наголо, сударь!";
            link.l1 = "Извольте!";
            link.l1.go = "AffairOfHonor_BeforeFight_2" break;

        case "CoatHonor":
            dialog.text = "Отлично, все на месте... Сударь, к барьеру!";
            link.l1 = "Защищайтесь!";
            link.l1.go = "AffairOfHonor_BeforeFight_2" break;

        case "GodJudgement":
            dialog.text = "А это еще кто? Что-то, приятель, ты не слишком похож на простого горожанина...";
            link.l1 = "Это с вами мне придется драться на дуэли?!";
            link.l1.go = "AffairOfHonor_BeforeFight_2_1" break;
        }
        break;

    case "AffairOfHonor_BeforeFight_2_1":
        dialog.text = "Ха! Дуэль! Значит, ты здесь по нашему делу... Парни, зарежем его и отправимся за обещанной наградой. Убивай!";
        link.l1 = "Засада? Ну хорошо...";
        link.l1.go = "AffairOfHonor_BeforeFight_2";
        break;

    case "AffairOfHonor_BeforeFight_2":
        LAi_LocationFightDisable(LoadedLocation, false);
        AddDialogExitQuest("MainHeroFightModeOn");
        PChar.Quest.AffairOfHonor_KillChar.win_condition.l1 = "NPC_Death";
        PChar.Quest.AffairOfHonor_KillChar.win_condition.l1.character = "AffairOfHonor_" + AffairOfHonor_GetCurQuest() + "_Man";
        PChar.Quest.AffairOfHonor_KillChar.function = "AffairOfHonor_KillChar";
        if (dRand(1) == 0 && AffairOfHonor_GetCurQuest() != "CowardFencer" && AffairOfHonor_GetCurQuest() != "CoatHonor")
        {
            PChar.QuestTemp.AffairOfHonor.FightWithHelpers = true;
            Log_TestInfo("Секунданты будут сражаться");
        }
        // В квесте "Божий суд" всегда нападают.
        if (AffairOfHonor_GetCurQuest() == "GodJudgement")
        {
            Log_TestInfo("Глобальное месиво");
            sld = CharacterFromID("AffairOfHonor_Helper_1");
            LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
            LAi_SetImmortal(sld, false);
            sld = CharacterFromID("AffairOfHonor_Helper_2");
            LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
            LAi_SetImmortal(sld, false);
            iTemp = dRand(3);
            if (AffairOfHonor_GetCurQuest() == "GodJudgement")
            {
                for (i = 0; i < iTemp; i++)
                {
                    sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
                    SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
                    ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
                    LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
                }
            }
        }
        LAi_Group_MoveCharacter(NPChar, "AffairOfHonor_Enemies");
        LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);

        DialogExit();
        break;
    // <-- Диалоги до боя.

    // Диалоги после боя -->
    case "AffairOfHonor_AfterFight_1":
        if (CheckAttribute(PChar, "QuestTemp.AffairOfHonor.FightWithHelpers"))
        {
            dialog.text = "Неужели вы думали, что зарежете нашего друга и спокойно уберетесь прочь? К оружию!";
            link.l1 = "Этого и следовало ожидать от друзей такого ничтожества!";
            link.l1.go = "AffairOfHonor_AfterFight_FightWithHelpers";
            break;
        }
        if (AffairOfHonor_GetCurQuest() == "CoatHonor")
        {
            dialog.text = "Капитан, честь восстановлена, вы победили. Но позвольте дать вам добрый совет – исчезните как можно скорее из города и не показывайтесь здесь некоторое время...";
            link.l1 = "А в чем, собственно, дело?";
            link.l1.go = "AffairOfHonor_AfterFight_2_1";
        }
        else
        {
            dialog.text = "Все было по чести, а теперь позвольте нам забрать нашего товарища и уйти самим.";
            link.l1 = "Конечно, я вас не задерживаю.";
            link.l1.go = "AffairOfHonor_AfterFight_2";
        }
        break;

    case "AffairOfHonor_AfterFight_2_1":
        dialog.text = "А дело в том, что вы, сами того не зная, убили ординарца коменданта. И хотя убитый слыл дурным человеком, о смерти которого мало кто станет жалеть, комендант, однако, его любил и не простит смерть своего любимца.";
        link.l1 = "Спасибо за совет, я непременно им воспользуюсь. Прощайте.";
        link.l1.go = "AffairOfHonor_AfterFight_2";
        break;

    case "AffairOfHonor_AfterFight_2":
        DialogExit();
        LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
        LAi_ActorGoToLocation(CharacterFromID("AffairOfHonor_Helper_2"), "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
        if (AffairOfHonor_GetCurQuest() == "CoatHonor")
        {
            ChangeCharacterComplexReputation(PChar, "nobility", 5);
        }
        break;

    case "AffairOfHonor_AfterFight_FightWithHelpers":
        iTemp = dRand(3);
        AddDialogExitQuest("MainHeroFightModeOn");
        sld = CharacterFromID("AffairOfHonor_Helper_1");
        LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
        LAi_SetImmortal(sld, false);
        sld = CharacterFromID("AffairOfHonor_Helper_2");
        LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
        LAi_SetImmortal(sld, false);
        if (AffairOfHonor_GetCurQuest() == "GodJudgement")
        {
            for (i = 0; i < iTemp; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
                SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
                ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
                LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
            }
        }
        LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);

        DialogExit();
        break;
        // <-- Диалоги после боя.
        //=====================================================================================================================================
        // <-- Серия миниквестов "Дело чести".
        //=====================================================================================================================================
    }
}

void SetSeekCapCitizenParam(ref npchar, int iNation)
{
    //создаем кэпов
    int Rank = sti(pchar.rank) + 5;
    if (Rank > 30)
        Rank = 30;
    ref sld = GetCharacter(NPC_GenerateCharacter("SeekCitizCap_" + npchar.index, "", "man", "man", Rank, iNation, -1, true, "soldier"));
    switch (npchar.quest.SeekCap)
    {
    case "NM_battle":
        SetShipToFantom(sld, "pirate", true);
        sld.Ship.Mode = "trade";
        SetCaptanModelByEncType(sld, "trade");
        sld.dialog.currentnode = "NM_battleCap";
        sld.DeckDialogNode = "NM_battleDeck";
        npchar.quest.money = (6 - sti(RealShips[sti(sld.Ship.Type)].Class)) * 8000 + sti(pchar.rank) * 500;
        npchar.quest.dublon = makeint(sti(npchar.quest.money) / 100);
        break;

    case "NM_prisoner":
        SetShipToFantom(sld, "pirate", true);
        sld.Ship.Mode = "trade";
        SetCaptanModelByEncType(sld, "trade");
        sld.dialog.currentnode = "NM_prisonerCap";
        sld.DeckDialogNode = "NM_prisonerCap";
        npchar.quest.money = (6 - sti(RealShips[sti(sld.Ship.Type)].Class)) * 10000 + sti(pchar.rank) * 600;
        npchar.quest.dublon = makeint(sti(npchar.quest.money) / 100);
        break;

    case "NM_peace":
        SetShipToFantom(sld, "pirate", true);
        sld.Ship.Mode = "war";
        SetCaptanModelByEncType(sld, "war");
        sld.dialog.currentnode = "NM_peaceCap";
        sld.DeckDialogNode = "NM_peaceCap";
        npchar.quest.money = (6 - sti(RealShips[sti(sld.Ship.Type)].Class)) * 6000 + sti(pchar.rank) * 400;
        npchar.quest.dublon = makeint(sti(npchar.quest.money) / 100);
        break;

    case "manSlave":
        SetShipToFantom(sld, "pirate", true);
        sld.Ship.Mode = "pirate";
        SetCaptanModelByEncType(sld, "pirate");
        sld.dialog.currentnode = "CitizCap";
        sld.DeckDialogNode = "CitizCap_inDeck";
        npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype) + 1) * 1000) + (sti(pchar.rank) * 500);
        break;

    case "manRapeWife":
        SetShipToFantom(sld, "pirate", true);
        sld.Ship.Mode = "pirate";
        SetCaptanModelByEncType(sld, "pirate");
        sld.dialog.currentnode = "RapeWifeCap";
        sld.DeckDialogNode = "RapeWifeCap_inDeck";
        npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype) + 1) * 1000) + (sti(pchar.rank) * 500);
        break;

    case "manFriend":
        SetShipToFantom(sld, "trade", true);
        sld.Ship.Mode = "trade";
        SetCaptanModelByEncType(sld, "trade");
        sld.dialog.currentnode = "FriendCap";
        sld.DeckDialogNode = "FriendCap_inDeck";
        npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype) + 1) * 1000) + (sti(pchar.rank) * 500);
        break;

    case "womanHasband":
        SetShipToFantom(sld, "trade", true);
        sld.Ship.Mode = "trade";
        SetCaptanModelByEncType(sld, "trade");
        sld.dialog.currentnode = "HasbandCap";
        sld.DeckDialogNode = "HasbandCap_inDeck";
        npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype) + 1) * 1000) + (sti(pchar.rank) * 500);
        break;

    case "womanRevenge":
        SetShipToFantom(sld, "pirate", true);
        sld.Ship.Mode = "pirate";
        SetCaptanModelByEncType(sld, "pirate");
        sld.dialog.currentnode = "RevengeCap";
        sld.DeckDialogNode = "RevengeCap_inDeck";
        npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype) + 1) * 1000) + (sti(pchar.rank) * 500);
        break;

    case "womanPirates":
        SetShipToFantom(sld, "pirate", true);
        sld.Ship.Mode = "pirate";
        SetCaptanModelByEncType(sld, "pirate");
        sld.dialog.currentnode = "PiratesCap";
        sld.DeckDialogNode = "PiratesCap_inDeck";
        npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype) + 1) * 1000) + (sti(pchar.rank) * 500);
        break;
    }
    sld.dialog.filename = "Quest\ForAll_dialog.c";
    DeleteAttribute(sld, "SinkTenPercent");
    DeleteAttribute(sld, "SaveItemsForDead");
    DeleteAttribute(sld, "DontClearDead");
    DeleteAttribute(sld, "AboardToFinalDeck");
    DeleteAttribute(sld, "SinkTenPercent");
    DeleteAttribute(sld, "DontRansackCaptain");
    sld.AlwaysSandbankManeuver = true;
    sld.AnalizeShips = true;       //анализировать вражеские корабли при выборе таска
    sld.DontRansackCaptain = true; //не сдаваться
    SetCharacterPerk(sld, "FastReload");
    SetCharacterPerk(sld, "HullDamageUp");
    SetCharacterPerk(sld, "SailsDamageUp");
    SetCharacterPerk(sld, "CrewDamageUp");
    SetCharacterPerk(sld, "CriticalShoot");
    SetCharacterPerk(sld, "LongRangeShoot");
    SetCharacterPerk(sld, "CannonProfessional");
    SetCharacterPerk(sld, "ShipDefenseProfessional");
    SetCharacterPerk(sld, "ShipTurnRateUp");
    SetCharacterPerk(sld, "ShipTurnRateUp");
    SetCharacterPerk(sld, "StormProfessional");
    SetCharacterPerk(sld, "SwordplayProfessional");
    SetCharacterPerk(sld, "AdvancedDefense");
    SetCharacterPerk(sld, "CriticalHit");
    SetCharacterPerk(sld, "Sliding");
    SetCharacterPerk(sld, "Tireless");
    SetCharacterPerk(sld, "HardHitter");
    SetCharacterPerk(sld, "GunProfessional");
    //в морскую группу кэпа
    string sGroup = "SeekCapShip_" + sld.index;
    Group_FindOrCreateGroup(sGroup);
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
    Group_AddCharacter(sGroup, sld.id);
    Group_SetGroupCommander(sGroup, sld.id);
    SetRandGeraldSail(sld, sti(sld.Nation));
    //записываем данные в структуры портмана и кэпа
    npchar.quest.SeekCap.capId = sld.id                                               //Id искомого кэпа
                                     npchar.quest.SeekCap.capName = GetFullName(sld); //имя искомого кэпа
    npchar.quest.SeekCap.shipName = sld.Ship.name;                                    //имя украденного корабля
    npchar.quest.SeekCap.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName;       //название украденного корабля
    //npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1)*1000)+(sti(pchar.rank)*500); //вознаграждение
    sld.quest = "InMap";                                            //личный флаг искомого кэпа
    sld.quest.SeekCap = npchar.quest.SeekCap;                       //запишем кэпу флаг квеста
    sld.quest.nation = iNation;                                     //запомним базовую нацию кэпа
    sld.city = SelectAnyColony(npchar.city);                        //определим колонию, откуда кэп-вор выйдет
    sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придет
    //Log_TestInfo("Разыскиваемый кэп " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity);
    sld.quest.cribCity = npchar.city; //город, где ошивается квестодатель
    npchar.quest.Qcity = sld.city;
    //==> на карту
    sld.mapEnc.type = "trade";
    //выбор типа кораблика на карте
    switch (npchar.quest.SeekCap)
    {
    case "NM_battle":
        sld.mapEnc.worldMapShip = "Galleon_red";
        break;
    case "NM_prisoner":
        sld.mapEnc.worldMapShip = "Galleon_red";
        break;
    case "NM_peace":
        sld.mapEnc.worldMapShip = "ranger";
        break;
    case "manSlave":
        sld.mapEnc.worldMapShip = "Galleon_red";
        break;
    case "manRapeWife":
        sld.mapEnc.worldMapShip = "Galleon_red";
        break;
    case "manFriend":
        sld.mapEnc.worldMapShip = "ranger";
        break;
    case "womanHasband":
        sld.mapEnc.worldMapShip = "ranger";
        break;
    case "womanRevenge":
        sld.mapEnc.worldMapShip = "Galleon_red";
        break;
    case "womanPirates":
        sld.mapEnc.worldMapShip = "Galleon_red";
        break;
    }
    sld.mapEnc.Name = XI_ConvertString(npchar.quest.SeekCap.shipTapeName) + " '" + npchar.quest.SeekCap.shipName + "'";
    int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city)) + 5; //дней доехать даем с запасом
    Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
    //прерывание на смерть кэпа
    string sTemp = "SCQ_" + sld.index;
    pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
    pchar.quest.(sTemp).win_condition.l1.character = sld.id;
    pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
    pchar.quest.(sTemp).CapId = sld.id;
    //прерывание на смерть квестодателя
    sTemp = "SCQ_" + npchar.index;
    pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
    pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
    pchar.quest.(sTemp).function = "SCQ_CitizenIsDeath";
    pchar.quest.(sTemp).CapId = sld.id;
    pchar.quest.(sTemp).CitizenId = npchar.id;
    //заносим Id кэпа в базу нпс-кэпов
    sTemp = sld.id;
    NullCharacter.capitainBase.(sTemp).quest = "citizen";                                           //идентификатор квеста
    NullCharacter.capitainBase.(sTemp).questGiver = npchar.id;                                      //запомним Id квестодателя для затирки в случае чего
    NullCharacter.capitainBase.(sTemp).Tilte1 = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap; //заголовок квестбука
    NullCharacter.capitainBase.(sTemp).Tilte2 = "SCQ_" + npchar.quest.SeekCap;                      //имя квеста в квестбуке
    NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string SelectNB_battleText()
{
    string sText;
    switch (drand(5))
    {
    case 0:
        sText = "Один мерзавец соблазнил мою сестру, воспользовавшись ее наивностью, а затем, наигравшись, преспокойно бросил. Я не мог оставить это деяние безнаказанным и вызвал негодяя на дуэль. Однако он струсил и сбежал в море на своем корабле" break;
    case 1:
        sText = "Один бесчестный негодяй проиграл мне в карты большую сумму денег, и, не желая отдавать, скрылся неведомо куда на своем корабле" break;
    case 2:
        sText = "Один проходимец взял у меня деньги в долг, затем отдал их в мое отсутствие слуге - а монеты оказались фальшивыми. Теперь он скрывается на своем корабле неведомо где" break;
    case 3:
        sText = "Один негодяй пытался опорочить мое имя, оклеветав меня перед губернатором. Однако обман был расрыт, и мерзавец сбежал в море на своем корабле" break;
    case 4:
        sText = "Я, по недосмотру, нанял счетоводом проходимца. Он совершил крупную растрату, купил корабль и скрылся неведомо куда" break;
    case 5:
        sText = "Мой бывший охранник выкрал из будуара жены шкатулку с драгоценностями и скрылся. Теперь я понял, откуда у его дружка появились деньги на покупку корабля" break;
    }
    return sText;
}

void SelectNB_prisonerText(ref npchar)
{
    switch (drand(5))
    {
    case 0:
        npchar.quest.text = "Один мерзавец соблазнил мою сестру, воспользовавшись ее наивностью, а затем, наигравшись, преспокойно бросил. Я не мог оставить это деяние безнаказанным и вызвал негодяя на дуэль. Однако он ухитрился устроиться корабельным плотником на одно судно и ушел в море";
        npchar.quest.text1 = "обесчестил женщину, а затем трусливо сбежал от дуэли";
        break;
    case 1:
        npchar.quest.text = "Один бесчестный негодяй проиграл мне в карты большую сумму денег, и, не желая отдавать, сбежал от меня в море, поступив на службу к одному капитану канониром";
        npchar.quest.text1 = "крупно проигрался в карты и не желает отдавать долг";
        break;
    case 2:
        npchar.quest.text = "Один проходимец взял у меня деньги в долг, затем отдал их в мое отсутствие слуге - а монеты оказались фальшивыми. Теперь он служит на одном корабле казначеем и скрывается от меня";
        npchar.quest.text1 = "фальшивомонетчик, совершивший преступление";
        break;
    case 3:
        npchar.quest.text = "Один негодяй пытался опорочить мое имя, оклеветав меня перед губернатором. Однако обман был расрыт, и мерзавец сбежал в море на одном корабле, устроившись на должность судового врача";
        npchar.quest.text1 = "клеветник и интриган, пытавшийся опорочить доброе имя одного их видных горожан";
        break;
    case 4:
        npchar.quest.text = "Я, по недосмотру, нанял счетоводом проходимца. Он совершил крупную растрату и сбежал на одном корабле, нанявшись квартирмейстером";
        npchar.quest.text1 = "обвиняется в растрате и присвоении чужих денег";
        break;
    case 5:
        npchar.quest.text = "Мой бывший охранник выкрал из будуара жены шкатулку с драгоценностями и скрылся. Как оказалось, он устроися офицером в абордажную роту на один корабль";
        npchar.quest.text1 = "банальный вор, по которому плачет тюрьма. Он украл драгоценности у своего работодателя";
        break;
    }
}

void SelectNB_peaceText(ref npchar)
{
    switch (drand(5))
    {
    case 0:
        npchar.quest.text = "мой старинный приятель, с которым мы были очень дружны в Старом Свете";
        npchar.quest.text1 = "он - ваш старый друг";
        break;
    case 1:
        npchar.quest.text = "человек, фактически заменивший мне в детстве родного отца";
        npchar.quest.text1 = "вы были ему в детстве за отца";
        break;
    case 2:
        npchar.quest.text = "мой сводный брат, покинувший Старый Свет еще в юности";
        npchar.quest.text1 = "вы - его сводный брат";
        break;
    case 3:
        npchar.quest.text = "человек, оказавший мне несколько лет назад в Старом Свете буквально неоценимую помощь";
        npchar.quest.text1 = "вы оказали ему когда-то помощь";
        break;
    case 4:
        npchar.quest.text = "муж моей сестры, с которым я был хорошо знаком в Старом Свете";
        npchar.quest.text1 = "вы - муж его сестры";
        break;
    case 5:
        npchar.quest.text = "мой друг, с которым мы вместе служили в одном полку в Старом Свете";
        npchar.quest.text1 = "вы служили в одном полку";
        break;
    }
}