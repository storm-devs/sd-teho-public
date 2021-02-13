// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
    case "quests":
        dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Что вы хотели? Спрашивайте.", "Я слушаю вас, что за вопрос?"), "Второй раз за день вы пытаетесь задать вопрос...", "В третий раз за день вы опять пытаетесь задать вопрос...",
                                              "Да когда же это кончится?! У меня полно работы по управлению делами города, а ты всё вопросы пытаешься задать!", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал" + GetSexPhrase("", "а") + "...", "Не сейчас, не место и не время..."), "Да, верно... Но не сейчас, позже...",
                                           "Задам, задам... Только позже...", "Извините, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        // Addon 2016-1 Jason пиратская линейка
        if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_8")
        {
            link.l1 = "Ваша светлость, я хочу сообщить информацию о проводящихся на Ямайке контрабандных сделках.";
            link.l1.go = "Mtraxx";
        }
        if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_12")
        {
            link.l1 = "Я бы хотел узнать результаты вашей операции по поводу контрабанды корабельного шёлка.";
            link.l1.go = "Mtraxx_4";
        }
        // Jason НСО
        if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_10_continue" && !CheckAttribute(npchar, "quest.slaveships"))
        {
            link.l1 = "Я прибыл по заданию генерал-губернатора Филиппа де Пуанси. В мою задачу входило доставить вам перехваченных у голландцев рабов, всё верно?";
            link.l1.go = "patria_Sl";
        }
        if (CheckAttribute(npchar, "quest.slaveships.wait") && GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000)
        {
            link.l1 = "Я привёз для вас рабов, как договаривались.";
            link.l1.go = "patria_Sl_2";
        }
        if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_start" && CheckAttribute(pchar, "questTemp.Patria.Curacao.DoilyReady"))
        {
            link.l1 = "Я прибыл по заданию генерал-губернатора Филиппа де Пуанси для участия в совместной экспедиции на Кюрасао против голландцев.";
            link.l1.go = "patria_Sl_4";
        }
        if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_wait" && GetCompanionQuantity(pchar) < 3)
        {
            link.l1 = "Моя эскадра уменьшена, можем отправляться в путь.";
            link.l1.go = "patria_Sl_6";
        }
        break;

    // Addon 2016-1 Jason пиратская линейка
    case "Mtraxx":
        dialog.text = "Очень интересно. Ну что же, давайте послушаем.";
        link.l1 = "Из достоверного источника мне стало известно, что уже в течение года, а то и больше, систематически, ежемесячно, между 10 и 15 числом, ночью, в бухте Портленд, некая голландская бригантина 'Утрехт' под английским флагом сгружает контрабандой корабельный шёлк крупными партиями.";
        link.l1.go = "Mtraxx_1";
        break;

    case "Mtraxx_1":
        dialog.text = "Вы уверены, что вашему источнику действительно можно верить?";
        link.l1 = "Я временами не уверен даже в себе, но человек, рассказавший мне об этом, вполне заслуживает доверия, и, к тому же, не имел резона лгать.";
        link.l1.go = "Mtraxx_2";
        break;

    case "Mtraxx_2":
        string sTemp = "этого";
        if (sti(pchar.questTemp.Mtraxx.month == 1))
            sTemp = "следующего";
        dialog.text = "Хорошо, капитан. То, что вы рассказали - весьма и весьма серьёзно, и я обязан это проверить, даже если ваш информатор ошибся или сказал неправду. Я вышлю береговой патруль в указанное вами время. И если ваша информация подтвердится - вы можете рассчитывать на вознаграждение, ибо такого рода сделки надо строжайшим образом пресекать.";
        link.l1 = "Я загляну к вам 16 числа " + sTemp + " месяца. Тогда уже наверняка всё прояснится.";
        link.l1.go = "Mtraxx_3";
        break;

    case "Mtraxx_3":
        DialogExit();
        pchar.questTemp.Mtraxx = "silk_11";
        int month = sti(pchar.questTemp.Mtraxx.month);
        pchar.quest.mtr_silk_smuggler.over = "yes";
        pchar.quest.mtr_silk_smuggler_over.over = "yes";
        pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1 = "Timer";
        pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.hour = 6;
        pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.day = 16;
        pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
        pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.year = GetAddingDataYear(0, month, 0);
        pchar.quest.mtr_silk_smuggler_patrol.function = "Mtraxx_SilkSmugglerPatrol";
        AddQuestRecord("Roger_2", "19");
        sTemp = "этого";
        if (sti(pchar.questTemp.Mtraxx.month == 1))
            sTemp = "следующего";
        AddQuestUserData("Headhunt", "sDate", sTemp);
        break;

    case "Mtraxx_4":
        dialog.text = "Переданная вами информация оказалась верной. Мы накрыли преступников за сделкой. Бригантина 'Утрехт' попыталась с боем уйти, но была потоплена нашим патрульным корветом. Покупатели товара - их было четверо - оказали сопротивление, один был убит, троим удалось сбежать в джунгли. Весь груз контрабанды - 80 рулонов корабельного шёлка - был передан в казну Порт-Ройяля\nИ хотя нам не удалось выяснить, кто из жителей Порт-Ройяля стоял за всем этим - убитого не опознали, а беглецов так и не нашли - я считаю операцию полностью успешной. Навряд ли мерзавцы осмелятся снова открыть свою лавочку. Вы оказали нам большую услугу, капитан, проявив сознательность и выдав мошенников. Вам за это полагается вознаграждение в размере 10 000 песо. Прошу, получите ваши деньги.";
        link.l1 = "Благодарю, ваша Светлость. Рад, что всё прошло как надо и негодяи получили по заслугам. А теперь позвольте откланяться.";
        link.l1.go = "Mtraxx_5";
        break;

    case "Mtraxx_5":
        DialogExit();
        pchar.questTemp.Mtraxx = "silk_13";
        AddQuestRecord("Roger_2", "20");
        AddMoneyToCharacter(pchar, 10000);
        ChangeCharacterComplexReputation(pchar, "nobility", 3);
        ChangeCharacterNationReputation(pchar, ENGLAND, 5);
        AddCharacterExpToSkill(pchar, "Leadership", 200);
        break;

    // Jason НСО
    case "patria_Sl":
        if (GetSquadronGoods(pchar, GOOD_SLAVES) < 500)
        {
            dialog.text = "Совершенно верно, капитан. Сколько рабов вы привезли?";
            link.l1 = "Я ещё веду эту операцию, просто хотел уточнить, всё ли верно. Скоро вернусь с результатами.";
            link.l1.go = "patria_Sl_wait";
            break;
        }
        dialog.text = "Совершенно верно, капитан. Сколько рабов вы привезли?";
        link.l1 = "" + FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SLAVES)) + ".";
        if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000)
            link.l1.go = "patria_Sl_2";
        else
            link.l1.go = "patria_Sl_1";
        break;

    case "patria_Sl_wait":
        DialogExit();
        npchar.quest.slaveships.wait = "true";
        break;

    case "patria_Sl_1":
        dialog.text = "Гм, шевалье де Пуанси обещал, что рабов будет не меньше 3000 штук...";
        link.l1 = "Всё верно. Это моя вина: часть невольников погибла при обстреле вражеского корабля, некоторые умерли в пути. Я исправлю свою оплошность и вернусь к вам. Всё будет сделано по договору.";
        link.l1.go = "patria_Sl_wait";
        break;

    case "patria_Sl_2":
        DeleteAttribute(npchar, "quest.slaveships.wait");
        dialog.text = "Отлично! С шевалье де Пуанси действительно можно вести дела. Передайте генерал-губернатору, что моя эскадра для атаки Кюрасао будет готова через месяц. Ещё месяц, но не больше, буду ждать его эскадру. Уверен, что он отправит ко мне вас для этого похода, так что скоро увидимся, месье де Мор.";
        link.l1 = "Буду рад очередной встрече, полковник. А сейчас позвольте откланяться.";
        link.l1.go = "patria_Sl_3";
        break;

    case "patria_Sl_3":
        DialogExit();
        npchar.quest.slaveships = "true";
        RemoveCharacterGoods(pchar, GOOD_SLAVES, GetSquadronGoods(pchar, GOOD_SLAVES));
        AddQuestRecord("Patria", "57");
        pchar.questTemp.Patria = "epizode_10_return";
        pchar.quest.Patria_SlaveShipsJamaicaTimeOver.over = "yes";              //снять таймер на доставку рабов
        SetFunctionTimerCondition("Patria_CuracaoDoilyReady", 0, 0, 30, false); // таймер на 1 месяц на готовность эскадры Дойли
        SetFunctionTimerCondition("Patria_CuracaoTimeOver", 0, 0, 62, false);   // таймер на 2 месяца на туда-обратно к Пуанси
        SaveCurrentQuestDateParam("questTemp.Patria.Curacao.Date");             // запоминаем дату
        // меняем отношение наций
        pchar.questTemp.Patria.Friend = "true";
        LaunchNationLegend();
        DeleteAttribute(pchar, "questTemp.Patria.Friend");
        DoQuestCheckDelay("sea_victory", 0.2);
        break;

    case "patria_Sl_4":
        dialog.text = "Я даже не сомневался, что это будете вы. Тем лучше! Наша эскадра готова. Линейный корабль 1 ранга и два корабля 4 ранга. Максимальный размер всей эскадры не должен превышать пяти кораблей.";
        if (GetCompanionQuantity(pchar) > 2)
        {
            link.l1 = "Тогда я поставлю лишние корабли на стоянку и оставлю только два. Как раз получится пять кораблей.";
            link.l1.go = "patria_Sl_5";
        }
        else
        {
            link.l1 = "Так и получится - не больше пяти. Можем отправляться в путь.";
            link.l1.go = "patria_Sl_6";
        }
        break;

    case "patria_Sl_5":
        DialogExit();
        pchar.questTemp.Patria = "epizode_11_wait";
        break;

    case "patria_Sl_6":
        dialog.text = "Отлично. Сейчас я объясню вам план, по которому мы будем действовать: возможно, вы захотите что-то изменить или добавить, тогда мы это обсудим.";
        link.l1 = "Слушаю вас внимательно, полковник.";
        link.l1.go = "patria_Sl_7";
        break;

    case "patria_Sl_7":
        dialog.text = "Захватывать Кюрасао нет смысла: это основная колония голландцев на архипелаге, и даже если мы сорвём их флаг с форта Виллемстада и водрузим английский или французский, удержать остров будет очень трудно: голландцы станут отбивать его со всей яростью, направляя военные эскадры. В общем, захват нецелесообразен, да и не нужен. Нам важно принудить Стайвесанта подписать договор на выгодных для нас и вас условиях, а для этого достаточно будет уничтожить основные защитные силы врага и поставить голландцев перед угрозой полного уничтожения колонии Виллемстад.";
        link.l1 = "Что это будет за договор?";
        link.l1.go = "patria_Sl_8";
        break;

    case "patria_Sl_8":
        dialog.text = "Договор был составлен совместно мной и шевалье де Пуанси. Он касается различных аспектов торговли, прекращения 'торговой войны' между Компанией и Англией, отказ Стайвесанта от любых притязаний на остров Синт-Маартен и прочие малоинтересные для вас политические пункты.";
        link.l1 = "Ясно.";
        link.l1.go = "patria_Sl_9";
        break;

    case "patria_Sl_9":
        dialog.text = "Действовать будем так: сначала всеми силами обрушиваемся на форт и уничтожаем его. Голландцы будут ожидать высадки десанта, но мы этого делать не станем - самые большие потери именно при взятии бастиона с моря. Вместо этого мы высадим штурмовые роты в двух точках острова: на мысе Санта-Мария и у лагуны Бланка, и двинемся по суше к городским воротам Виллемстада. Я приказал взять с собой на корабли полевую артиллерию - на Кюрасао нет труднопроходимых зарослей, и мы без особого труда сможем катить пушки на колёсах по земле\nПока голландцы будут соображать, что да как, мы возьмём город под прицел со стороны джунглей и отрежем возможность прислать подкрепление из форта по суше. После этого хорошенько обстреляем город поверх стен. Наверняка гарнизон форта попытается атаковать, но против полевых пушек и наших мушкетёров они ничего не смогут сделать, а свои фортовые орудия, если такие даже и останутся у них, они не смогут перетянуть в джунгли\nКроме того, наши корабли сымитируют подготовку к высадке десанта с моря - нагонят паники на противника. Через некоторое время, когда голландцы полностью осознают своё плачевное положение, мы запросим парламентёров для переговоров. Ваше мнение, капитан?";
        link.l1 = "Отличный план! Главное - не понадобится губить солдат под стенами бастиона.";
        link.l1.go = "patria_Sl_10";
        break;

    case "patria_Sl_10":
        dialog.text = "Я рад, что мои идеи вам понравились. Тогда выступаем!";
        link.l1 = "Вперёд!";
        link.l1.go = "patria_Sl_11";
        break;

    case "patria_Sl_11":
        DialogExit();
        chrDisableReloadToLocation = true;
        pchar.questTemp.Patria = "epizode_11_continue";
        AddQuestRecord("Patria", "60");
        pchar.quest.Patria_CuracaoTimeOver.over = "yes"; // снять таймер 2 месяца
        LAi_SetActorType(npchar);
        ChangeCharacterAddressGroup(npchar, "PortRoyal_townhall", "goto", "goto4");
        LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 7.0);
        Patria_CuracaoSail();
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
