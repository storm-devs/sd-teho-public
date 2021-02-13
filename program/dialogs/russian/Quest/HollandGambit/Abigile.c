// Абигайль Шнеур
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
    case "First time":
        if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
        {
            if (pchar.questTemp.HWIC.Holl == "AbbyInHouse")
            {
                dialog.text = "Здравствуйте, минхер. Рада вас видеть. Что привело вас в наше скромное жилище?";
                link.l1 = "Добрый день, Абигайль. Меня зовут " + GetFullName(pchar) + ". Я капитан, и служу на благо Республики Свободных Провинций в целом и Голландской Вест-Индской Компании в частности.";
                link.l1.go = "AbbyAndLucas";
                break;
            }
            if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
            {
                dialog.text = "Вы нашли деньги моего отца? Это правда? Ах, как же я счастлива... Быстрее идите к моему папе, он хочет с вами поговорить. Ступайте к нему, скорее!";
                link.l1 = "Уже иду, госпожа.";
                link.l1.go = "exit";
                break;
            }
            if (pchar.questTemp.HWIC.Holl == "AbbyLeavesMarried")
            {
                dialog.text = "Вы спасли нас от нищеты, капитан! Как же я вам благодарна! Теперь доброе имя семьи Шнеуров будет восстановлено.";
                link.l1 = "Это моя работа, Абигайль. Я надеюсь, более ничего не сдерживает вас от того, чтобы выйти замуж за моего патрона. Я думаю, он вполне доказал свои наиблагие намерения в отношении вас и вашей семьи.";
                link.l1.go = "AbbyAndLucas_8";
                break;
            }
            dialog.text = "Вы ещё что-то хотели мне сказать, капитан?";
            link.l1 = "Нет, госпожа. Я уже ухожу.";
            link.l1.go = "exit";
            break;
        }
        if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
        {
            if (pchar.questTemp.HWIC.Eng == "AbigileInChurch")
            {
                dialog.text = "Рада вас видеть, минхер. Какое дело привело вас к бедной девушке?";
                link.l1 = "Здравствуйте, Абигайль. Я пришёл от Ричарда Флитвуда...";
                link.l1.go = "Seek_Island";
                break;
            }
            dialog.text = "Вы ещё что-то хотели мне сказать, капитан?";
            link.l1 = "Нет, госпожа. Я уже ухожу.";
            link.l1.go = "exit";
            break;
        }
        if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
        {
            if (pchar.questTemp.HWIC.Self == "toVillemstad")
            {
                dialog.text = "Что здесь происходит? Что за шум? Папа, кто это?";
                link.l1 = "Здравствуйте, госпожа. Вы, как я понимаю, и есть Абигайль? Очень рад вас видеть! Простите мою дерзость, но я должен передать вам письмо от... но ваш отец мне не верит и просит покинуть дом. Уверяю, я действительно принес для вас послание и хочу вручить его вам.";
                link.l1.go = "Abigile_kidnapping";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "AbigileNextDay")
            {
                dialog.text = "Ах, вот и вы, Чарли. Я готова следовать за вами.";
                link.l1 = "Отправляемся в путь!";
                link.l1.go = "Abigile_kidnapping_7";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "AbigileInCabin")
            {
                dialog.text = "Мы уже в Сент-Джонсе, Чарли? Я скоро увижу Ричарда?";
                link.l1 = "Да, мисс, мы уже в Сент-Джонсе. Но Ричарда к сожалению нет в городе - по приказу губернатора он на своём корабле буквально два дня назад выдвинулся в патрульный рейд к берегам Барбадоса. Но не расстраивайтесь, он должен вернуться не позже, чем через неделю.";
                link.l1.go = "Abigile_kidnapping_8";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "AbigileLie")
            {
                dialog.text = "Чарли! Как я рада вас видеть! Скажите, есть ли вести от Ричарда?";
                link.l1 = "Увы, моя дорогая мисс. Ричард вынужден был задержаться в Бриджтауне - какие-то важные и очень секретные дела, что-то связанное с разведкой против голландцев. Вам же, наверное, Ричард рассказывал о своей службе?";
                link.l1.go = "Abigile_kidnapping_13";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "AbiReturnHome")
            {
                dialog.text = "Чарли! Это вы! Наконец вы вернулись!";
                link.l1 = "Здравствуйте, дорогая мисс. Рад вас видеть.";
                link.l1.go = "Abigile_return";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "AbiReturnHomeGo")
            {
                dialog.text = "Ах, наконец-то я дома! Как я рада снова видеть папу! Чарли, спасибо вам огромное за всё, что вы для меня сделали!";
                link.l1 = "Право, не стоит, дорогая мисс...";
                link.l1.go = "Abigile_return_6";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "SolomonHistoryNext")
            {
                dialog.text = "Папочка, если ты что-то помнишь - скажи это! Чарли - он... ему можно доверять. Возможно, кроме него, никто не сможет нам помочь!";
                link.l1 = "";
                link.l1.go = "Abigile_return_12";
                pchar.questTemp.HWIC.Self = "SolomonHistoryAfter";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "SolomonHistoryEnd")
            {
                dialog.text = "Я буду молиться за вас, Чарли! Скажите.. скажите, что вы сделате это! Что вы найдёте остров!";
                link.l1 = "Я сделаю всё, что будет в моих силах, дорогая мисс.";
                link.l1.go = "Abigile_return_13";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "final" || pchar.questTemp.HWIC.Self == "VanbergDestroyed")
            {
                dialog.text = "Ах, Чарли! Вы вернулись! Что скажете? Вы нашли остров?";
                if (makeint(Pchar.money) >= 200000)
                {
                    link.l1 = "Да, Аби. И остров, и деньги вашего отца. Я пришёл, чтобы вернуть их вам.";
                    link.l1.go = "Abigile_GiveMoney";
                }
                link.l2 = "Увы, мисс. Мне не удалось разыскать ни капитана Келлера, ни остров. Я сделал всё, что мог.";
                link.l2.go = "Abigile_NoMoney";
                break;
            }
            dialog.text = "Ах, это вы, Чарли! Вы что-то хотели спросить?";
            link.l1 = "Нет, ничего. Я уже ухожу.";
            link.l1.go = "exit";
            break;
        }
        dialog.text = "Добрый день. Вы что-то хотели?";
        link.l1 = "Нет, госпожа. Прошу меня извинить. До свидания.";
        link.l1.go = "exit";
        NextDiag.TempNode = "First time";
        break;

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

        //-------------------------------------------------за Голландию-----------------------------------------------
    case "AbbyAndLucas":
        dialog.text = "Очень приятно познакомиться, капитан " + GetFullName(pchar) + ". Я про вас слышала. Ведь это вы захватили пиратский корабль-призрак и доставили его в Виллемстад. Скажите, капитан, это правда... что этим кораблём командовал... Ричард Флитвуд?";
        link.l1 = "Именно так, госпожа. Мы все были буквально поражены. Подумать только - английский офицер на службе короля, уничтожающий собственных торговцев... И ведь каков негодяй: прикрываясь деяниями 'корабля-призрака', он обвинял в преступлениях Компанию и нападал на голландские суда!";
        link.l1.go = "AbbyAndLucas_1";
        break;

    case "AbbyAndLucas_1":
        dialog.text = "Мне тяжело это слышать, капитан... Я лично знала Ричарда Флитвуда, и никогда бы не подумала, что он...";
        link.l1 = "Госпожа, мне известна в общих чертах история вашего путешествия до Кюрасао из Ресифии, от моего патрона, Лукаса Роденбурга. Теперь всё стало на свои места. Флитвуд сначала потопил ваше судно, а потом вернулся и 'спас' вас с отцом с острова. Я читал судовой журнал этого пирата - он не побоялся доверить эту информацию бумаге...";
        link.l1.go = "AbbyAndLucas_2";
        break;

    case "AbbyAndLucas_2":
        dialog.text = "Какой кошмар... Значит, мой папа был прав. Он с самого начала говорил, что Ричард и есть тот пират. Хорошо, что всё разрешилось вовремя и не произошло непоправимого... ах, извините, капитан. Так что же нужно такому значительному человеку, как вы, от простой девушки?";
        link.l1 = "Абигайль, я пришёл к вам по одному очень непростому и деликатному вопросу. Прошу вас выслушать меня.";
        link.l1.go = "AbbyAndLucas_3";
        break;

    case "AbbyAndLucas_3":
        dialog.text = "Конечно, минхер. Я вас слушаю.";
        link.l1 = "Как я уже сказал, я служу Компании, и Лукас Роденбург - не только мой боевой командир, но также и хороший друг. И для него высшим счастьем явилось бы ваше одобрение его предложения руки и сердца. Я пришёл просить вас согласиться стать женой моего патрона. Ради вас он готов на всё!";
        link.l1.go = "AbbyAndLucas_4";
        break;

    case "AbbyAndLucas_4":
        dialog.text = "Ах, капитан! Кажется, я понимаю, почему минхер Роденбург сам не решался сделать это предложение... Мой бедный папа будет наверняка обрадован, но...";
        link.l1 = "Госпожа, я вижу, что вас что-то тревожит. Какая причина заставляет вас сомневаться в искренности чувств моего командира? Может, я смогу убедить вас в обратном?";
        link.l1.go = "AbbyAndLucas_5";
        break;

    case "AbbyAndLucas_5":
        dialog.text = "Капитан, я не сомневаюсь в искренности минхера Роденбурга. Лукас сделал для меня и моего папы столько всего... я даже не знаю, как бы мы смогли прожить без его покровительства. Но я прошу вас, поймите меня!\nМы ведь не были нищими, семья Шнеуров вполне могла гордиться своим состоянием... если бы не этот злосчастный пират. Я не могу слышать этих перешёптываний за спиной... Все жители этого городка убеждены, что меня интересуют только деньги минхера Роденбурга и ничего более. Ах, если бы только мой отец вспомнил, что это за остров! Он спрятал там все деньги нашей семьи, чтобы они не достались пиратам, погубившим моих сестер и брата!\nНо мой бедный отец не моряк, он просто не знает, где этот злополучный клочок земли. Поговорите с папой, капитан! Может, он вспомнит. Если бы вы только смогли найти этот остров и наши деньги!";
        link.l1 = "Хорошо, Абигайль. Я поговорю с вашим отцом. Может, ещё не все потеряно. Я сделаю всё, что будет только возможно.";
        link.l1.go = "AbbyAndLucas_6";
        break;

    case "AbbyAndLucas_6":
        dialog.text = "Спасибо, минхер. Я буду молиться за вас. Да поможет вам Господь!";
        link.l1 = "До свидания, Абигайль. Ждите меня с добрыми вестями.";
        link.l1.go = "AbbyAndLucas_7";
        break;

    case "AbbyAndLucas_7":
        DialogExit();
        AddQuestRecord("Holl_Gambit", "1-27");
        pchar.questTemp.HWIC.Holl = "AbbyFather";
        break;

    case "AbbyAndLucas_8":
        dialog.text = "О, да! Минхер Роденбург - благороднейший человек. Я без колебаний даю согласие и буду счастлива назвать его своим мужем.";
        link.l1 = "Тогда я считаю свою миссию выполненной. Позвольте откланяться, я должен поспешить к командиру и обрадовать его. И, госпожа: я искренне желаю вам счастья!";
        link.l1.go = "AbbyAndLucas_9";
        break;

    case "AbbyAndLucas_9":
        DialogExit();
        AddQuestRecord("Holl_Gambit", "1-33");
        pchar.questTemp.HWIC.Holl = "AbbyAgreeMarried"; //теперь к Лукасу
        break;

        //-------------------------------------------------за Англию-----------------------------------------
    case "Seek_Island":
        dialog.text = "От Ричарда?! Ах, минхер! Я слышала, что он был ранен. Это так, скажите мне?! С ним всё в порядке?";
        link.l1 = "Ричард жив и уже почти здоров. Остались некоторые проблемы со зрением, но он явно идет на поправку. Ричард предлагает вам уехать с ним в Англию, где вы сможете обвенчаться. Его командировка закончена, и он ждёт только вашего ответа.";
        link.l1.go = "Seek_Island_1";
        break;

    case "Seek_Island_1":
        dialog.text = "Ах, милый вестник, передайте Ричарду, что ради нашего счастья я была бы готова бежать с ним на край света. Но боюсь, что мой побег убьёт моего бедного отца. Я в отчаянии и не знаю, что мне делать. Если бы Ричард смог найти тот злосчастный остров и сундук с нашим семейным золотом... Возможно, это хоть как-то бы утешило папу.";
        link.l1 = "Хорошо... В мою задачу входило доставить вас на Антигуа. Значит, я найду этот остров, и этот сундук со всем его содержимым, и привезу его вам, а затем вы отправитесь со мной в Сент-Джонс к Ричарду.";
        link.l1.go = "Seek_Island_2";
        break;

    case "Seek_Island_2":
        dialog.text = "Ах, вы так великодушны! Спасибо вам огромное, капитан! Я буду молиться за вас! Ступайте, и да поможет вам Господь!";
        link.l1 = "Я не заставлю вас долго ждать, госпожа. До скорой встречи!";
        link.l1.go = "Seek_Island_3";
        break;

    case "Seek_Island_3":
        DialogExit();
        AddQuestRecord("Holl_Gambit", "2-18");
        pchar.questTemp.HWIC.Eng = "SeekIsland";
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload1", "Villemstad_houseSp2_bedroom", "goto", "goto1", "", -1); //Аби домой
        pchar.questTemp.HWIC_Coordinates = "true";                                                                  //атрибут координат на поиск острова через каюту
        break;

        //--------------------------------------------против всех------------------------------------------------
    case "Abigile_kidnapping":
        dialog.text = "Ох... Вы принесли письмо от него... да? Ах, папа, да что же вы такой несносный! Всюду вам страхи мерещатся! Минхер, прошу вас, идите за мной, я хочу поговорить с вами.";
        link.l1 = "Спасибо, благородная госпожа.";
        link.l1.go = "Abigile_kidnapping_1";
        break;

    case "Abigile_kidnapping_1":
        DialogExit();
        npchar.greeting = "abigile_3";
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "Abigile_Stay", -1);
        NextDiag.CurrentNode = "Abigile_kidnapping_2";
        pchar.questTemp.HWIC.Self = "AbigileTalk";
        break;

    case "Abigile_kidnapping_2":
        dialog.text = "Извините моего отца, минхер. Он добрый и хороший человек, просто... выпавшие на нашу долю несчастья надломили его.";
        link.l1 = "Всё в порядке, госпожа. Позвольте представиться - Чарли... Книппель. Я пришёл по приказу Ричарда Флитвуда, чтобы отвезти вас к нему. Вот, пожалуйста, прочтите это письмо.";
        link.l1.go = "Abigile_kidnapping_3";
        break;

    case "Abigile_kidnapping_3":
        RemoveItems(PChar, "NPC_Letter", 1);
        dialog.text = "Ах, Ричард...(читает). О, Боже! Он решил... решил подарить отцу все потерянные им деньги! Какое благородство! Милый Ричард! Минхер, вы - добрый вестник! Ричард - где он? Он на Кюрасао?";
        link.l1 = "Нет, госпожа. На Ричарда было совершено покушение, он получил серьёзное ранение. Он сейчас на Антигуа... вы не дочитали.";
        link.l1.go = "Abigile_kidnapping_4";
        break;

    case "Abigile_kidnapping_4":
        dialog.text = "Пресвятая Дева! Скажите, он в безопасности? Рана тяжёлая?";
        link.l1 = "Не волнуйтесь так, госпожа! Ричард не таков, чтобы дать себя вот так просто убить каким-то негодяям. Он уже идёт на поправку. А в мою задачу входит привезти вас к нему в Сент-Джонс, и чтобы ни один волосок не упал с вашей прелестной головки. Затем вы отбудете в Лондон... дочитайте письмо, благородная... леди.";
        link.l1.go = "Abigile_kidnapping_5";
        break;

    case "Abigile_kidnapping_5":
        dialog.text = "Леди? Ах, ну да...(читает). Чарли, я готова с вами отплыть. Мне нужен день, чтобы собрать свои вещи и объясниться с папой. Приходите завтра, и я поднимусь на ваш корабль.";
        link.l1 = "Хорошо, леди. Я буду завтра. И не беспокойтесь за себя - я и моя команда оградим вас от любых неприятностей в пути.";
        link.l1.go = "Abigile_kidnapping_6";
        break;

    case "Abigile_kidnapping_6":
        DialogExit();
        npchar.greeting = "abigile_2";
        NextDiag.CurrentNode = "First time";
        AddQuestRecord("Holl_Gambit", "3-22");
        pchar.quest.Abigile_Kidnap.win_condition.l1 = "Timer";
        pchar.quest.Abigile_Kidnap.win_condition.l1.date.hour = 7.0;
        pchar.quest.Abigile_Kidnap.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
        pchar.quest.Abigile_Kidnap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
        pchar.quest.Abigile_Kidnap.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
        pchar.quest.Abigile_Kidnap.win_condition.l2 = "location";
        pchar.quest.Abigile_Kidnap.win_condition.l2.location = "Villemstad_houseSp2";
        pchar.quest.Abigile_Kidnap.function = "AbigileGoToShip";
        pchar.questTemp.HWIC.Self = "AbigileWaitNextDay";
        SetFunctionTimerCondition("AbigileGoToShipOver", 0, 0, 3, false); //таймер 3 дня, ибо нефиг
        break;

    case "Abigile_kidnapping_7":
        DialogExit();
        chrDisableReloadToLocation = true;
        AddPassenger(pchar, npchar, false);
        SetCharacterRemovable(npchar, false);
        LAi_SetActorType(sld);
        LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SetAbigileToCabin", -1); //Аби в каюту к ГГ поставим
        AddQuestRecord("Holl_Gambit", "3-23");
        pchar.questTemp.HWIC.Self = "AbigileOnShip";
        pchar.quest.AbigileGoToShipOver.over = "yes";                    //снять таймер
        SetFunctionTimerCondition("RemoveAbigileOver", 0, 0, 30, false); //таймер на 1 месяц, ибо нефиг
        pchar.quest.Abigile_died.win_condition.l1 = "NPC_Death";
        pchar.quest.Abigile_died.win_condition.l1.character = "Abigile";
        pchar.quest.Abigile_died.function = "AbigileDied"; //специально для особо упоротых
        break;

    case "Abigile_kidnapping_8":
        dialog.text = "Ах, как жаль! Но я думаю, что я вполне в состоянии подождать ещё неделю, раз ждала столько времени до этого...";
        link.l1 = "Вы очень правильно сказали, мисс. Ну, а чтобы ожидание ваше не было столь тяжким в узких стенах каюты, я предлагаю вам пройти в дом моего друга - там для вас будет приготовлена вкусная еда и мягкая постель.";
        link.l1.go = "Abigile_kidnapping_9";
        break;

    case "Abigile_kidnapping_9":
        dialog.text = "Вы такой заботливый, Чарли. Спасибо вам. Я и впрямь неважно себя чувствую от этой постоянной качки.";
        link.l1 = "Следуйте за мной, дорогая леди!";
        link.l1.go = "Abigile_kidnapping_10";
        break;

    case "Abigile_kidnapping_10":
        DialogExit();
        LAi_SetActorType(npchar);
        LAi_ActorFollowEverywhere(npchar, "", -1);
        pchar.questTemp.HWIC.Self = "AbigileInHouse";
        break;

    case "Abigile_kidnapping_11":
        dialog.text = "Рада познакомиться, Джон. Спасибо за ваше гостеприимство, джентльмены!";
        link.l1 = "...";
        link.l1.go = "Abigile_kidnapping_12";
        break;

    case "Abigile_kidnapping_12":
        DialogExit();
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload3", "SentJons_HouseF3_Room2", "barmen", "bar1", "ContinueWithMerdok", -1);
        pchar.questTemp.HWIC.Self = "AbigileInRoom";
        NextDiag.CurrentNode = "First time";
        RemovePassenger(Pchar, npchar);
        pchar.quest.RemoveAbigileOver.over = "yes"; //снять таймер
        sld = characterFromId("Merdok");
        LAi_SetActorType(sld); //чтобы геймер сам с ним не заговорил
        break;

    case "Abigile_kidnapping_13":
        dialog.text = "Ах, Чарли, мы так мало виделись с Ричардом, что он мне почти ничего о себе и не рассказал толком.";
        link.l1 = "Ну, не думаю, что он бы стал это от вас скрывать... Мисс, Ричард - не просто капитан. Он агент английской разведки. Очень важная персона, выполняет задания английской короны, большей частью связанные с подрывом торговой деятельности голландских купцов на архипелаге.";
        link.l1.go = "Abigile_kidnapping_14" break;

    case "Abigile_kidnapping_14":
        dialog.text = "Да что вы такое говорите?!";
        link.l1 = "Да, мисс. Ваш жених и мой друг - большой человек... Я всегда гордился дружбой с ним, но в последнее время он стал очень скрытен, в том числе и со мной. Очевидно, он выполняет некое секретное поручение. Я очень расстроен, что выполнение этого задания не позволило ему встретиться с вами.";
        link.l1.go = "Abigile_kidnapping_15";
        break;

    case "Abigile_kidnapping_15":
        dialog.text = "Чарли, вы меня пугаете. Вы уверены, что с ним всё в порядке?";
        link.l1 = "Насчёт этого уверен полностью. Просто я... ну, немного не одобряю то, как он сейчас поступает с вами, хотя понимаю - служба есть служба и он не вправе отказать долгу, даже ради вас. ";
        link.l1.go = "Abigile_kidnapping_16";
        break;

    case "Abigile_kidnapping_16":
        dialog.text = "Ах, добрый Чарли... Я буду ждать Ричарда, сколько потребуется. Может, подскажете, где можно остановиться в Сент-Джонсе? Я не могу злоупотреблять более гостеприимством Джона.";
        link.l1 = "Да что вы такое говорите, леди! Вы своим присутствием оказываете нам честь, и не будь я Чарли Книппель, если я посмею отказать в крове и еде невесте моего друга и патрона!";
        link.l1.go = "Abigile_kidnapping_17";
        break;

    case "Abigile_kidnapping_17":
        dialog.text = "Чарли... Я действительно тронута вашим отношением ко мне. Я всего лишь простая девушка, и...";
        link.l1 = "Мисс! И думать забудьте о каких-то постоялых дворах. Я никогда себе не прощу, если вы окажетесь недовольны моей службой Ричарду и вам.";
        link.l1.go = "Abigile_kidnapping_18";
        break;

    case "Abigile_kidnapping_18":
        dialog.text = "Спасибо, Чарли. Я рада, что вы такой... хороший человек.";
        link.l1 = "Это мой долг, мисс. А теперь позвольте откланяться. Да, вы можете без опаски гулять по городу - вам же наверно одиноко в этом доме?";
        link.l1.go = "Abigile_kidnapping_19";
        break;

    case "Abigile_kidnapping_19":
        dialog.text = "Ну... Джон очень хороший и интересный собеседник. Он может часами рассказывать о своих порошках и микстурах, и всевозможных болезнях. Он вежливый и милый человек. Я хожу в церковь... но, конечно, я очень скучаю по Ричарду.";
        link.l1 = "Я думаю, он скоро вернется. Если вам что-то понадобится - Чарли Книппель всегда к вашим услугам.";
        link.l1.go = "Abigile_kidnapping_20";
        break;

    case "Abigile_kidnapping_20":
        DialogExit();
        pchar.questTemp.HWIC.Self = "MeetTonzag";
        pchar.quest.Meet_Tonzag.win_condition.l1 = "location";
        pchar.quest.Meet_Tonzag.win_condition.l1.location = "SentJons_TownCave";
        pchar.quest.Meet_Tonzag.function = "TonzagMeetingInDange";
        break;

    case "Abigile_return":
        dialog.text = "До меня доходили слухи о Ричарде... он исчез. Вы не знаете, что с ним, Чарли?";
        link.l1 = "Знаю, Абигайль. Простите... Ричард Флитвуд отбыл в Европу и более на Карибы не вернётся. Он получил то ли повышение, то ли перевод, то ли ещё что-то... в общем, после того, как он поступил с вами, я его не знаю и знать не хочу.";
        link.l1.go = "Abigile_return_1";
        break;

    case "Abigile_return_1":
        dialog.text = "Ах, я так и знала, что всё этим кончится... Надо было слушать папу... По крайней мере, он был бы счастлив, выйди я замуж за Лукаса Роденбурга.";
        link.l1 = "Ещё раз простите, меня мисс...";
        link.l1.go = "Abigile_return_2";
        break;

    case "Abigile_return_2":
        dialog.text = "За что, Чарли? Вы ни в чём не виноваты.";
        link.l1 = "За то, что скажу вам очередную неприятную новость: Лукас Роденбург арестован за попытку совершения переворота в Виллемстаде, будет отправлен в Нидерланды и отдан под суд. Я только что прибыл с Кюрасао. С учетом того, что он пытался убить директора Компании Питера Стайвесанта, да и уличён ещё как минимум в одном убийстве, приговор вряд ли будет мягким.";
        link.l1.go = "Abigile_return_3";
        break;

    case "Abigile_return_3":
        dialog.text = "О, Боже! Какой ужас! Чарли, это правда? Нет, скажите, что это не так!";
        link.l1 = "Увы. Дорогая мисс, добавлю более того: в результате расследования деятельности Лукаса было установлено, что пират, потопивший ваш флейт на пути в Виллемстад, выполнял приказы Роденбурга. Мне очень жаль, Абигайль, что сразу же после прибытия на архипелаг вы так близко столкнулись с обманщиками и негодяями.";
        link.l1.go = "Abigile_return_4";
        break;

    case "Abigile_return_4":
        dialog.text = "Ох... У меня нет слов. Я полностью уничтожена. Чарли... пожалуйста... Отвезите меня домой, в Виллемстад. Я хочу к папе...";
        link.l1 = "Конечно, дорогая мисс. Я сделал бы это и без вашей просьбы. К сожалению, в Сент-Джонсе вам больше делать нечего. Идите, соберите свои вещи, попрощайтесь с Джоном, и мы отправимся в путь.";
        link.l1.go = "Abigile_return_5";
        break;

    case "Abigile_return_5":
        DialogExit();
        AddQuestRecord("Holl_Gambit", "3-57");
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
        LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false); //откроем комнату Аби
        AddPassenger(pchar, npchar, false);
        SetCharacterRemovable(npchar, false);
        pchar.questTemp.HWIC.Self = "AbiReturnHomeGo";
        pchar.quest.AbiReturn_Home.win_condition.l1 = "location";
        pchar.quest.AbiReturn_Home.win_condition.l1.location = "Villemstad_town";
        pchar.quest.AbiReturn_Home.function = "AbiGoInVillemstad";
        break;

    case "Abigile_return_6":
        dialog.text = "Нет, Чарли, стоит. Если бы не вы и Джон - не знаю, что бы со мной было. Вы единственные достойные люди, кого я встретила на архипелаге.";
        link.l1 = "Гхм... Вы вгоняете меня в краску, Абигайль. Рад был вам помочь. И мне очень жаль, что всё так вышло.";
        link.l1.go = "Abigile_return_7";
        break;

    case "Abigile_return_7":
        dialog.text = "Знаете, Чарли, за время путешествия до Кюрасао я многое обдумала... Теперь всё произошедшее - Ричард Флитвуд, минхер Роденбург - кажется мне кошмарным сном, который наконец закончился. Я теперь снова с папой, и мы продолжим нормальную жизнь\nПравда, будет нелегко - у нас практически нет денег. Но мы справимся.";
        link.l1 = "Мисс, хотел как раз поговорить с вами на эту тему. Я... ну, поймите меня правильно - я хочу вам помочь.";
        link.l1.go = "Abigile_return_8";
        break;

    case "Abigile_return_8":
        dialog.text = "Помочь? Но чем, Чарли?";
        link.l1 = "От Ричарда я знаю историю вашего крушения и вашего спасения. Также я знаю, что ваш отец спрятал от пиратов свои сбережения на этом таинственном острове. Я хочу попробовать найти его.";
        link.l1.go = "Abigile_return_9";
        break;

    case "Abigile_return_9":
        dialog.text = "Ах, Чарли... Ни я, ни мой отец, не сможем даже приблизительно подсказать, где находится этот злосчастный остров. Мы же не моряки. Я была так напугана тогда, что ничего толком и не помню.";
        link.l1 = "Абигайль, постарайтесь вспомнить хоть какие-то факты, мелкие подробности. Может, что-то предшествовало нападению на вас пирата? Какой из себя этот остров?";
        link.l1.go = "Abigile_return_10";
        break;

    case "Abigile_return_10":
        dialog.text = "Остров... Остров и остров. Пляж, джунгли. Как везде. Вспомнила! Может, это вам поможет. Незадолго до нападения пирата мы встретили флейт какого-то торговца. Он был приглашён на наш корабль и отобедал с нашим капитаном. Мы тоже были там. Возможно, он знает, где этот остров.";
        link.l1 = "Уже что-то! Как назывался этот флейт, и как звали капитана?";
        link.l1.go = "Abigile_return_11";
        break;

    case "Abigile_return_11":
        dialog.text = "Я не помню, Чарли. Совершенно...";
        link.l1 = "Гм... Постарайтесь вспомнить, Аби!";
        link.l1.go = "Abigile_return_12";
        pchar.questTemp.HWIC.Self = "SolomonHistory";
        break;

    case "Abigile_return_12":
        DialogExit();
        sld = characterFromId("Solomon");
        sld.greeting = "solomon_1";
        LAi_SetActorType(sld);
        LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

    case "Abigile_return_13":
        dialog.text = "Мы будем ждать вас, Чарли. Вы - наша поледняя надежда. Я буду молиться за вас. Да поможет вам Господь!";
        link.l1 = "Я уже отправляюсь в путь. До свидания, Абигайль! До свидания, Соломон.";
        link.l1.go = "Abigile_return_14";
        break;

    case "Abigile_return_14":
        DialogExit();
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "ReturnAbiNormal", -1);
        pchar.questTemp.HWIC.Self = "SeekFleut";
        AddQuestRecord("Holl_Gambit", "3-58");
        break;

    case "Abigile_NoMoney":
        dialog.text = "Ах, какая жалость... Мы так надеялись, но... всё равно спасибо вам, Чарли, за то, что вы хотя бы попытались нам помочь. Видимо, такова судьба.";
        link.l1 = "Прощайте, Абигайль. Надеюсь, у вас всё наладится.";
        link.l1.go = "exit";
        npchar.dialog.currentnode = "Abigile_Poor";
        break;

    case "Abigile_GiveMoney":
        dialog.text = "Это... это правда? Вы действительно привезли нам потерянные деньги? О, Чарли!";
        link.l1 = "Да, правда. Они у меня. Я готов вам их вернуть прямо сейчас. Вот, возьмите. Они ваши.";
        link.l1.go = "Abigile_GiveMoney_1";
        break;

    case "Abigile_GiveMoney_1":
        AddMoneyToCharacter(pchar, -200000);
        pchar.quest.MakeAbiPoor.over = "yes"; //снять прерывание
        ChangeCharacterComplexReputation(pchar, "nobility", 10);
        dialog.text = "Как мне вас благодарить!? Как!?";
        link.l1 = "Не нужно никаких благодарностей, Аби. Это самое малое, что я смог для вас сделать. Теперь вы начнёте новую жизнь, без всяких флитвудов, роденбургов и прочих сомнительных личностей. Думаю, ваш отец найдёт способ, как приумножить этот капитал.";
        link.l1.go = "Abigile_GiveMoney_2";
        break;

    case "Abigile_GiveMoney_2":
        dialog.text = "Чарли... Вы столько для меня сделали, для меня и для моего бедного отца. Я уже даже привыкла, что вы есть в моей жизни. Я неустанно молилась за вас ежедневно. Вы - мой ангел-хранитель. Вас послал нашей семье сам Господь, хотите вы в это верить, или нет\nПрежде, чем вы уйдёте, я хочу, чтобы вы знали: двери этого дома открыты для вас в любое время дня и ночи. И... разрешите мне вас поцеловать, дорогой Чарли...";
        link.l1 = "Ну... да, конечно... Аби.";
        link.l1.go = "Abigile_GiveMoney_3";
        break;

    case "Abigile_GiveMoney_3":
        DialogExit();
        npchar.greeting = "abigile_1";
        PlayStereoOGG("music_romantic");
        SetLaunchFrameFormParam("", "", 0, 7);
        SetLaunchFrameFormPic("loading\inside\kiss.tga");
        LaunchFrameForm();
        DoQuestFunctionDelay("GoFromAbiRoom", 7.0);
        npchar.dialog.currentnode = "Abigile_AllRight";
        break;

    case "Abigile_Poor":
        dialog.text = "Рада вас видеть, Чарли. У нас всё по-прежнему... бедность - это так тяжело...";
        link.l1 = "Держитесь, мисс. Не падайте духом.";
        link.l1.go = "exit";
        NextDiag.TempNode = "Abigile_Poor";
        break;

    case "Abigile_AllRight":
        dialog.text = "Чарли! Это вы! Я рада вас видеть! Присядьте, отобедайте с нами.";
        link.l1 = "Я тоже рад вас видеть, Аби. И рад, что у вас всё хорошо.";
        link.l1.go = "exit";
        NextDiag.TempNode = "Abigile_AllRight";
        break;

    //--> блок реагирования на попытку залезть в сундук
    case "Woman_FackYou":
        dialog.text = "Ах, вот, значит, как?! Я вас пустила в дом как гост" + GetSexPhrase("я", "ью") + ", а вы по сундукам шарить вздумали?! Стража-а-а!!!";
        link.l1 = "Заткнись, дура...";
        link.l1.go = "exit";
        LAi_group_Attack(NPChar, Pchar);
        break;
        //<-- блок реагирования на попытку залезть в сундук
    }
}