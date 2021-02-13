// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
    {
    case "quests":
        //регата
        if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
        {
            dialog.text = "Что вам угодно? А-а, вы участник регаты! Так?";
            link.l1 = "Да, именно так, мистер. Мне нужно отметиться у вас согласно правил.";
            link.l1.go = "Regata_check";
            break;
        }
        //регата
        dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                                              "Послушайте, если вы не по делам порта, то не стоит меня вопросами донимать.", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал" + GetSexPhrase("", "а") + "...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                                           "Да уж, действительно в третий раз...", "Извините, но портовые дела меня сейчас не интересуют.", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        //Голландский гамбит
        if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
        {
            link.l1 = "Я направляюсь в Блювельд, паприку продавать. Скажите, мистер, нет ли у вас сейчас пассажиров до Блювельда? Ну, или до Порт-Рояля. Было бы неплохо подвезти, глядишь, покрыли бы убытки на оплату команде. Я и так её сократил до минимума, но всё равно, канальи, денег-то просят...";
            link.l1.go = "PortofficeDone";
        }
        // Страж Истины
        if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados")
        {
            link.l1 = "В портовом управлении Филипсбурга был зафрахтован галеон 'Восхитительный' под командованием Гая Марше. Он должен был привезти к вам груз паприки. Не подскажете, где мне найти капитана этого корабля?";
            link.l1.go = "guardoftruth";
        }
        // калеуче
        if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.garpiya"))
        {
            if (CheckAttribute(npchar, "questTemp.caleuche"))
            {
                link.l1 = "Я по поводу шебеки со странным названием.";
                link.l1.go = "caleuche_2";
            }
            else
            {
                link.l1 = "Я слышал, что в вашем порту часто бывает шебека капитана Джексона... или Джека. Вы не подскажете, где мне его разыскать?";
                link.l1.go = "caleuche";
            }
        }
        break;

    //Голландский гамбит
    case "PortofficeDone":
        dialog.text = "Пассажиров ни до Блювельда, ни до Порт-Рояля нет, к сожалению. Зайдите завтра, или послезавтра - может, появятся.";
        link.l1 = "Эх, жаль. Ладно, тогда до свидания.";
        link.l1.go = "exit";
        npchar.quest.HWICTalked = "true";
        pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter) + 1;
        AddQuestRecord("Holl_Gambit", "2-9");
        if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7)
        {
            AddQuestRecord("Holl_Gambit", "2-6");
            pchar.quest.GotoBridgetownOver.over = "yes"; //снять таймер
            pchar.questTemp.HWIC.Eng = "SeekVanBerg";
            pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
            pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
        }
        break;

    //регата
    case "Regata_check":
        iTest = FindColony(npchar.city);
        if (iTest != -1)
        {
            rColony = GetColonyByIndex(iTest);
            sFrom_sea = rColony.from_sea;
        }
        ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok) //проверка на наличие корабля в порту
        {
            pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
            if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Sentjons") || GetCompanionQuantity(pchar) > 1 || sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_LUGGER || pchar.Ship.Name != "Сaнта-Kатepина")
            {
                dialog.text = "Хм... Вы нарушили правила регаты и я вынужден вас дисквалифицировать. Увы! В дальнейшем заплыве вы не участвуете. Я уже подготовил депешу в Порт-Рояль.";
                link.l1 = "Эх... жаль! Ладно, ничего не поделаешь - вы оказались бдительны. До свидания!";
                link.l1.go = "exit";
                DeleteAttribute(pchar, "questTemp.Regata");
            }
            else
            {
                pchar.questTemp.Regata.FourthTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime()); //истратил ГГ в часах на 1+2+3+4 переход
                dialog.text = "Как вы заметили, капитан, у нас очень тревожная обстановка - город в осаде. Готовимся к атаке испанцев, мобилизуем все силы. Но регата продолжается\nТак, отмечаем: капитан " + GetFullName(pchar) + ", корабль - " + pchar.Ship.Name + "... Затрачено времени от старта регаты в часах - " + sti(pchar.questTemp.Regata.FourthTransitionTime) + ". Всё, ваш результат зафиксирован, можете продолжать путь.";
                link.l1 = "Скажите, а на каком я сейчас месте?";
                link.l1.go = "Regata_info";
            }
        }
        else
        {
            dialog.text = "Вы сами прибыли - а корабль ваш где? Что-то я его не вижу.";
            link.l1 = "Прошу прощения, сэр. Я немедленно приведу свой корабль в порт.";
            link.l1.go = "exit";
        }
        break;

    case "Regata_info":
        int n = 1;
        string sTemp, sName, sShip;
        for (int i = 1; i <= 5; i++)
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
            if (pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FourthTransitionTime))
            {
                n++;
                sName = pchar.questTemp.Regata.AdversaryName.(sTemp);     //имя ближайшего противника
                sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp); //его корабль
            }
        }
        if (n == 1)
        {
            dialog.text = "Ах, ну да... Простите, мне просто немного не до этого. Вы на первом месте. ";
            link.l1 = "Понятно, спасибо за информацию.";
            link.l1.go = "exit";
        }
        else
        {
            if (n == 6)
            {
                dialog.text = "Ах, ну да... Простите, мне просто немного не до этого. Вы на последнем месте.";
                link.l1 = "Понятно, спасибо за информацию.";
                link.l1.go = "exit";
            }
            else
            {
                if (n == 2)
                {
                    dialog.text = "Ах, ну да... Простите, мне просто немного не до этого. Вы на втором месте. Перед вами только " + sName + " на корабле " + sShip + ".";
                    link.l1 = "Понятно, спасибо за информацию.";
                    link.l1.go = "exit";
                }
                else
                {
                    dialog.text = "Ах, ну да... Простите, мне просто немного не до этого. Вы на " + n + " месте. Ваш ближайший соперник впереди - " + sName + " на корабле " + sShip + ".";
                    link.l1 = "Понятно, спасибо за информацию.";
                    link.l1.go = "exit";
                }
            }
        }
        AddCharacterExpToSkill(pchar, "Sailing", 50); //навигация
        AddCharacterExpToSkill(pchar, "Defence", 30); //защита
        AddCharacterExpToSkill(pchar, "Repair", 30);  //починка
        AddCharacterExpToSkill(pchar, "Fortune", 30); //везение
        AddCharacterExpToSkill(pchar, "Sneak", 30);   //скрытность
        npchar.quest.regatatalk = "true";
        pchar.questTemp.Regata.Bridgetown = "true"; //отметка Бриджтауна
        pchar.quest.Regata_Check1.win_condition.l1 = "location";
        pchar.quest.Regata_Check1.win_condition.l1.location = "Curacao";
        pchar.quest.Regata_Check1.function = "RegataCheck"; //проверка 1
        pchar.quest.Regata_Check2.win_condition.l1 = "location";
        pchar.quest.Regata_Check2.win_condition.l1.location = "Caracas";
        pchar.quest.Regata_Check2.function = "RegataCheck"; //проверка 2
        pchar.quest.Regata_Check3.win_condition.l1 = "location";
        pchar.quest.Regata_Check3.win_condition.l1.location = "PortoBello";
        pchar.quest.Regata_Check3.function = "RegataCheck"; //проверка 3
        pchar.quest.Regata_Check.win_condition.l1 = "location";
        pchar.quest.Regata_Check.win_condition.l1.location = "Jamaica";
        pchar.quest.Regata_Check.function = "RegataCheck"; //проверка 4
        pchar.questTemp.Regata.AttackIsland = "Curacao";
        pchar.questTemp.Regata.AttackNation = HOLLAND;
        pchar.quest.Regata_Attack.win_condition.l1 = "location";
        pchar.quest.Regata_Attack.win_condition.l1.location = "Curacao";
        pchar.quest.Regata_Attack.function = "RegataAttack_Brigantine";
        pchar.quest.Regata_Attack1.win_condition.l1 = "location";
        pchar.quest.Regata_Attack1.win_condition.l1.location = "Curacao";
        pchar.quest.Regata_Attack1.function = "RegataAttack_Corvette"; //третья засада
        pchar.quest.Regata_Hunter.win_condition.l1 = "location";
        pchar.quest.Regata_Hunter.win_condition.l1.location = "Barbados";
        pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter"; //ДУ у Барбадоса
        pchar.quest.Regata_Finish.win_condition.l1 = "location";
        pchar.quest.Regata_Finish.win_condition.l1.location = "Jamaica";
        pchar.quest.Regata_Finish.function = "RegataFinishSea";
        pchar.quest.Regata_Finish1.win_condition.l1 = "location";
        pchar.quest.Regata_Finish1.win_condition.l1.location = "Portroyal_town";
        pchar.quest.Regata_Finish1.function = "RegataFinishTown"; //финиш регаты
        //ситуации
        pchar.quest.Regata_Siege.win_condition.l1 = "location";
        pchar.quest.Regata_Siege.win_condition.l1.location = "Bridgetown_town";
        pchar.quest.Regata_Siege.function = "RegataSiegeOfficer"; //на квест по вывозу жителей
        break;
    //регата

    // Страж Истины
    case "guardoftruth":
        dialog.text = "Да, этот галеон прибывал к нам, разгрузился и через некоторое время покинул наш порт. Сведений о пункте назначения... гм... нет, ничего нет. Простите, но ничем помочь не могу.";
        link.l1 = "Ясно. Очень жаль... Буду искать дальше.";
        link.l1.go = "guardoftruth_1";
        break;

    case "guardoftruth_1":
        DialogExit();
        AddQuestRecord("Guardoftruth", "13");
        pchar.questTemp.Guardoftruth = "barbados1";
        break;

    // калеуче
    case "caleuche":
        dialog.text = "Сэр, мне нужно название судна. Ибо что Джексонов, что Джеков, у нас как грибов поганых. Знаете, сколько их через наш порт проходит? Так какое название?";
        link.l1 = "";
        Link.l1.edit = 2;
        link.l1.go = "caleuche_name";
        link.l2 = "Загвоздка в том, что я не знаю, как называется его лоханка. Имя такое странное, означает полуженщину-полуптицу, рожденную...";
        link.l2.go = "caleuche_1";
        break;

    case "caleuche_1":
        dialog.text = "Сударь, с байками и загадками - в таверну, а здесь серьёзное учреждение. Или скажите, как называется шебека этого вашего капитана, или не отнимайте моё время.";
        link.l1 = "Хорошо, я попытаюсь выяснить и вернусь к вам.";
        link.l1.go = "exit";
        npchar.questTemp.caleuche = "true";
        break;

    case "caleuche_2":
        dialog.text = "Ну? Вы выяснили? Слушаю вас.";
        link.l1 = "";
        Link.l1.edit = 2;
        link.l1.go = "caleuche_name";
        break;

    case "caleuche_name":
        if (GetStrSmallRegister(dialogEditStrings[2]) == "гарпия")
        {
            dialog.text = "'Гарпия'? Ну конечно, я знаю шебеку 'Гарпия', её капитана зовут Реджинальд Джексон. Но в Бриджтауне он давно уже не появляется. Я слышал, что его наняла на службу Голландская Вест-Индская Компания. Так что вам нужно в Виллемстад.";
            link.l1 = "Спасибо огромное! Вы мне очень помогли.";
            link.l1.go = "caleuche_3";
        }
        else
        {
            dialog.text = "Это мне ни о чем не говорит, к сожалению. Вы уверены, что ваш капитан бывал в Бриджтауне?";
            link.l1 = "Уверен. Ладно, надо ещё подумать, может, соображу...";
            link.l1.go = "exit";
        }
        break;

    case "caleuche_3":
        DialogExit();
        AddQuestRecord("Caleuche", "18");
        pchar.questTemp.Caleuche.Garpiya = "gwik";
        npchar.quest.garpiya = "true";
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
