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
            if (CheckAttribute(pchar, "questTemp.Regata.Breach") || GetCompanionQuantity(pchar) > 1 || sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_LUGGER || pchar.Ship.Name != "Сaнта-Kатepина")
            {
                dialog.text = "Хм... Вы нарушили правила регаты и я вынужден вас дисквалифицировать. Увы! В дальнейшем заплыве вы не участвуете. Я уже подготовил депешу в Порт-Рояль.";
                link.l1 = "Эх... жаль! Ладно, ничего не поделаешь - вы оказались бдительны. До свидания!";
                link.l1.go = "exit";
                DeleteAttribute(pchar, "questTemp.Regata");
                pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
            }
            else
            {
                pchar.questTemp.Regata.FirstTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime()); //истратил ГГ в часах на 1 переход
                dialog.text = "Так, отмечаем: капитан " + GetFullName(pchar) + ", корабль - " + pchar.Ship.Name + "... Затрачено времени от старта регаты в часах - " + sti(pchar.questTemp.Regata.FirstTransitionTime) + ". Всё, ваш результат зафиксирован, можете продолжать путь.";
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
            if (pchar.questTemp.Regata.AdversaryFirstTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FirstTransitionTime))
            {
                n++;
                sName = pchar.questTemp.Regata.AdversaryName.(sTemp);     //имя ближайшего противника
                sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp); //его корабль
            }
        }
        if (n == 1)
        {
            dialog.text = "Вы на первом месте. Поздравляю! Так держать!";
            link.l1 = "Спасибо!";
            link.l1.go = "exit";
        }
        else
        {
            if (n == 6)
            {
                dialog.text = "Вы на последнем месте. Вам следует поторопиться!";
                link.l1 = "Уже бегу!";
                link.l1.go = "exit";
            }
            else
            {
                if (n == 2)
                {
                    dialog.text = "Вы на втором месте. Перед вами только " + sName + " на корабле " + sShip + ". Думаю, вы вполне сможете его обогнать.";
                    link.l1 = "Спасибо! Буду стараться!";
                    link.l1.go = "exit";
                }
                else
                {
                    dialog.text = "Вы на " + n + " месте. Ваш ближайший соперник впереди - " + sName + " на корабле " + sShip + ".";
                    link.l1 = "Спасибо!";
                    link.l1.go = "exit";
                }
            }
        }
        AddCharacterExpToSkill(pchar, "Sailing", 50); //навигация
        npchar.quest.regatatalk = "true";
        pchar.questTemp.Regata.Beliz = "true"; //отметка Белиза
        pchar.quest.Regata_Check1.win_condition.l1 = "location";
        pchar.quest.Regata_Check1.win_condition.l1.location = "Cuba1";
        pchar.quest.Regata_Check1.function = "RegataCheck"; //проверка 1
        pchar.quest.Regata_Check2.win_condition.l1 = "location";
        pchar.quest.Regata_Check2.win_condition.l1.location = "Cuba2";
        pchar.quest.Regata_Check2.function = "RegataCheck"; //проверка 2
        pchar.quest.Regata_Check.win_condition.l1 = "location";
        pchar.quest.Regata_Check.win_condition.l1.location = "Hispaniola2";
        pchar.quest.Regata_Check.function = "RegataCheck"; //проверка 3
        pchar.questTemp.Regata.AttackIsland = "Cuba1";
        pchar.questTemp.Regata.AttackNation = SPAIN;
        pchar.quest.Regata_Attack.win_condition.l1 = "location";
        pchar.quest.Regata_Attack.win_condition.l1.location = "Cuba1";
        pchar.quest.Regata_Attack.function = "RegataAttack_Lugger"; //первая засада у Сантьяго
        pchar.quest.Regata_Hunter.win_condition.l1 = "location";
        pchar.quest.Regata_Hunter.win_condition.l1.location = "Cuba2";
        pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter"; //ДУ у Гаваны
        pchar.questTemp.Regata.Town = "Portpax";
        pchar.quest.Regata_PU.win_condition.l1 = "locator";
        pchar.quest.Regata_PU.win_condition.l1.location = "Portpax_town";
        pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
        pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
        pchar.quest.Regata_PU.win_condition.l2 = "Night";
        pchar.quest.Regata_PU.function = "RegataPU_Open"; //вход в ПУ ночью
        break;
        //регата
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
