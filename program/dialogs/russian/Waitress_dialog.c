// диалог официантки
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c ";
                         if (LoadSegment(NPChar.FileDialog2))
    {
        ProcessCommonDialog(NPChar, Link, NextDiag);
        UnloadSegment(NPChar.FileDialog2);
    }
    // вызов диалога по городам <--
    switch (Dialog.CurrentNode)
    {
    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    case "First time":
        //--> Jason Цена чахотки
        if (sti(pchar.rank) > 6 && npchar.location == "PortSpein_tavern" && !CheckAttribute(npchar, "quest.Consumption"))
        {
            dialog.text = "Что вам угодно, сеньор? Простите, я немного... ох...";
            link.l1 = "Сударыня, что за печаль на вашем прекрасном личике? А это - никак слезы? Что с вами?";
            link.l1.go = "Consumption";
            break;
        }
        //<-- Цена чахотки

        // Addon-2016 Jason, французские миниквесты (ФМК) Порт Пренс
        if (npchar.location == "PortPax_tavern" && CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin")
        {
            PlaySound("VOICE\Russian\Enc_RapersGirl_1.wav");
            dialog.text = "Месье! Месье, помогите! Убивают!";
            link.l1 = "А?.. Кого убивают? Где? Что за шутки, милочка?";
            link.l1.go = "FMQP";
            break;
        }
        NextDiag.TempNode = "First time";
        if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
        {
            if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
            {
                dialog.text = "Я просила, чтобы ты ждал меня наверху. Не стоит маячить здесь, не привлекай внимания...";
                link.l1 = "Хорошо, не буду тебя подставлять...";
                link.l1.go = "exit";
            }
            if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
            {
                dialog.text = "Я здесь новенькая, так что не загружайте меня работой, прошу вас. Я не освоилась еще на новом месте...";
                link.l1 = "А где официантка, что работала до тебя? " + pchar.questTemp.different.FackWaitress.Name + ", кажется...";
                link.l1.go = "Love_IDN";
            }
            if (pchar.questTemp.different == "FackWaitress_facking")
            {
                dialog.text = "Заходи еще, дорогой. Будет время - развлечемся еще...";
                link.l1 = "Обязательно!";
                link.l1.go = "exit";
            }
            if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
            {
                dialog.text = "Я вас не знаю, не приставайте ко мне...";
                link.l1 = "Где мои деньги?!!";
                link.l1.go = "Love_IDN_1";
            }
            break;
        }
        switch (Rand(4))
        {
        case 0:
            dialog.text = "Прости, " + GetSexPhrase("красавчик", "красавица") + ", я занята. Хороший день для таверны - не всегда хороший день для разговора!";
            link.l1 = "...";
            link.l1.go = "exit";
            break;

        case 1:
            dialog.text = "Пожалуйста, капитан, не устраивайте дебошей! После них так трудно наводить порядок!";
            link.l1 = "" + GetSexPhrase("Кхм... Вроде и не собирался.", "Я что, похожа на дебоширку?") + "";
            link.l1.go = "exit";
            break;

        case 2:
            if (drand(1) == 0) // Addon-2016 Jason
            {
                dialog.text = "" + GetSexPhrase("О, капитан! Вы хотели бы попасть в мои объятья сегодня? Я не люблю хвастаться, но ...", "Присаживайтесь, капитан. Настоящей морской волчице здесь всегда рады.") + "";
                link.l1 = "" + GetSexPhrase("Увы, сейчас я спешу! Давай в другой раз!", "Cпасибо, милашка.") + "";
                link.l1.go = "exit";
                bool bOk = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"));                                                                                                           // 291112
                if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && PChar.sex != "woman" && pchar.GenQuest.EncGirl != "HorseToTavern" && !bOk && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // Addon-2016 Jason
                {
                    link.l2 = "С превеликим удовольствием, крошка!";
                    link.l2.go = "Love_1";
                }
            }
            else
            {
                dialog.text = "Присаживайтесь, капитан. Выпейте рому, сыграйте в карты и кости. Настоящему морскому волку здесь всегда рады.";
                link.l1 = "Cпасибо, милашка.";
                link.l1.go = "exit";
            }
            break;

        case 3:
            dialog.text = "Если вы хотите что-либо заказать - обратитесь, пожалуйста, к хозяину. Он стоит за стойкой.";
            link.l1 = "Спасибо за совет.";
            link.l1.go = "exit";
            break;

        case 4:
            dialog.text = "Если вы хотите как следует отдохнуть и поправить здоровье - снимите комнату на ночь. Ночевка в общей зале вряд ли прибавит вам сил.";
            link.l1 = "Благодарю.";
            link.l1.go = "exit";
            break;
        }
        link.l9 = "Я хочу задать тебе пару вопросов.";
        link.l9.go = "quests"; //(перессылка в файл города)
        break;

    case "Love_1":
        dialog.text = "Тогда слушай внимательно. Сними комнату у нас в таверне. Иди туда и жди меня. Я незаметно проскочу к тебе попозже...";
        link.l1 = "Хе! Все сделаю, дорогуша! Жду!";
        link.l1.go = "exit";
        pchar.questTemp.different = "FackWaitress_toRoom";
        SetTimerFunction("WaitressFack_null", 0, 0, 1); //освобождаем разрешалку на миниквесты на след. день
        //Шанс, что ограбят, если рендом выпадет на 0. он же делитель сколько она вытащит из кармана
        pchar.questTemp.different.FackWaitress.Kick = dRand(2);            // Addon-2016 Jason
        pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //запомним имя официантки
        pchar.questTemp.different.FackWaitress.City = npchar.city;
        //делаем клона официантки
        sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false, "citizen"));
        sld.name = npchar.name;
        sld.lastname = npchar.lastname;
        sld.dialog.Filename = "Quest\ForAll_dialog.c";
        sld.dialog.currentnode = "Waitress";
        Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
        Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
        Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
        ChangeCharacterComplexReputation(pchar, "nobility", -1);
        break;

    case "Love_IDN":
        dialog.text = "Она здесь больше не работает, уволилась... Простите, у меня много дел.";
        link.l1 = "Хорошо...";
        link.l1.go = "exit";
        break;

    case "Love_IDN_1":
        dialog.text = "Вот что, похотливый кобель. Я не знаю, где твои деньги! А будешь приставать ко мне - вызову стражу, и ты сегодня же окажешься в тюрьме!";
        link.l1 = "Ладно, не надо стражу... Сам дурак.";
        link.l1.go = "Love_IDN_2";
        break;

    case "Love_IDN_2":
        dialog.text = "Вот именно, что сам дурак. Впредь будешь умней и порядочней.";
        link.l1 = "М-да, постараюсь...";
        link.l1.go = "exit";
        break;

    case "without_money":
        NextDiag.TempNode = "first time";
        dialog.text = "Вы очнулись?";
        link.l1 = "М-м-м.";
        link.l1.go = "without_money_2";
        break;

    case "without_money_2":
        dialog.text = "Вам плохо? Болит голова?";
        link.l1 = "Где я, черт возьми?";
        link.l1.go = "without_money_3";
        break;

    case "without_money_3":
        dialog.text = "Так вы ничего не помните? Даже то, как вас ограбили?";
        link.l1 = "Что? Ох... моя голова... Кто посмел?!";
        link.l1.go = "without_money_4";
        break;

    case "without_money_4":
        dialog.text = "Откуда мне знать? Пришли, пригрозили убить, обшарили карманы и ушли.";
        link.l2 = "Ладно, что пропало, то пропало.";
        link.l2.go = "exit";
        break;

    //--> Jason Цена чахотки
    case "Consumption":
        npchar.quest.Consumption = "true";
        dialog.text = "Ничего, сеньор... спасибо, вы так добры, но я...(рыдает)";
        link.l1 = "Тебя обидели? Успокойся, милочка, и расскажи все по порядку. Может, я смогу тебе помочь.";
        link.l1.go = "Consumption_1";
        break;

    case "Consumption_1":
        dialog.text = "Нет-нет, сеньор, ничего такого... Простите мою несдержанность, просто... Мой брат – они говорят, что он умер, но я не верю! Я не знаю, чему верить, но сердцем чувствую – он в большой беде. А ведь кроме Анджело у меня никого не осталось, с тех пор как наши родители...(рыдает)";
        link.l1 = "Успокойся, прошу тебя. Что случилось с твоим братом?";
        link.l1.go = "Consumption_2";
        break;

    case "Consumption_2":
        dialog.text = "Сеньор... не поймите меня неправильно, но какое вам, такому солидному капитану, дело до скромной девушки из таверны? Мне даже нечего посулить вам за возможные хлопоты...";
        link.l1 = "В общем-то, да. Бескорыстность - не мой порок, так что мужайтесь – все мы теряем близких. Как говорят во Франции – такова жизнь...";
        link.l1.go = "exit";
        link.l2 = "Женщине всегда найдется, чем отблагодарить мужчину... хе-хе. Просто расскажи мне, в чем дело, и прекрати, наконец, рыдать.";
        link.l2.go = "Consumption_3_1";
        link.l3 = "Юная сеньорита, разве ты не знаешь, что церковь учит протягивать ближним руку помощи? Я попробую помочь тебе, если это будет в моих силах, конечно.";
        link.l3.go = "Consumption_3_2";
        break;

    case "Consumption_3_1":
        if (sti(pchar.reputation.nobility) > 36)
        {
            dialog.text = "Это что - намек? Простите, я, видимо, ошиблась, заведя с вами этот разговор! Прощайте, 'кабальеро'.";
            link.l1 = "Как пожелаешь, дорогуша.";
            link.l1.go = "exit";
        }
        else
        {
            dialog.text = "Ну что же... Вы, по крайней мере, честны в своих запросах. Обещаю, если вы найдете Анджело, или узнаете, что с ним случилось – вы получите то, что просите, ради моего брата...";
            link.l1 = "Милая сеньорита, с тобой необыкновенно приятно иметь дело... Теперь – давай перейдем непосредственно к истории вашего брата.";
            link.l1.go = "Consumption_4";
            npchar.quest.Consumption.sex = "true";
        }
        break;

    case "Consumption_3_2":
        dialog.text = "Вы, должно быть, шутите? Желаете помочь мне просто так?";
        link.l1 = "Плох тот мужчина, что пройдет спокойно мимо женщины в слезах. Не беспокойтесь – я правда хочу помочь. Что именно произошло с Анджело?";
        link.l1.go = "Consumption_4";
        break;

    case "Consumption_4":
        dialog.text = "Хорошо, сеньор. Мой брат, он... ох, мне сложно сдерживать слезы, простите... Мы едва сводили концы с концами, возможно, из-за моей... скромности на работе, и Анджело подался к местным дельцам. Решил, что его рыбацкая лодка принесет больше, провозя что-то в обход портовой таможни.";
        link.l1 = "Проще говоря, твой брат стал обычным контрабандистом, так?";
        link.l1.go = "Consumption_5";
        break;

    case "Consumption_5":
        dialog.text = "Нет, сеньор, вы не поняли... он не такой совсем! Он это из-за меня сделал! Чтобы мне, ну... не пришлось подрабатывать здесь, сами понимаете, как. Мы были в долгах, и он пошел на это ради моей чести. А потом его поймали. И все бы ничего, я даже заняла еще денег на штраф... Но мне сказали, что Анджело умер.";
        link.l1 = "Сказали? Кто сказал? И почему вы этому не верите? Он умер в тюрьме?";
        link.l1.go = "Consumption_6";
        break;

    case "Consumption_6":
        dialog.text = "Да. Комендант, когда я пришла вчера и принесла деньги на залог, сказал, что Анджело унесла чахотка. Представляете – он попал туда совершенно здоровым, и менее чем за две недели в этих камерах умер! Мне... мне даже не дали взглянуть на тело, сказали, что зараженных заключенных хоронят прямо в заливе у форта, сразу же после смерти, чтобы избежать распространения болезни.";
        link.l1 = "Эпидемия? Звучит вполне убедительно. Вы просто не хотите в это верить, или у вас есть более весомые причины?";
        link.l1.go = "Consumption_7";
        break;

    case "Consumption_7":
        dialog.text = "Нет... нет!(рыдает) Я понимаю, это звучит глупо, но я уверена, что почувствовала, если бы он... Понимаете, Анджело был сильным, крепким - настоящий моряк. Но есть и еще кое-что\nМой дед умер от чахотки, когда я была еще ребенком, и он, в свои дряхлые годы, продержался несколько лет с этим ужасным кашлем. Я знаю, каково это – чахотка не убивает в считанные дни, поверьте!";
        link.l1 = "Хм... Вы заразили меня своими сомнениями – что-то здесь действительно не вяжется. Не могу ничего обещать, но я попробую узнать больше.";
        link.l1.go = "Consumption_8";
        break;

    case "Consumption_8":
        dialog.text = "Даже это обещание – больше, чем я смела надеяться! Вы так добры, сеньор! Я буду ждать здесь!";
        link.l1 = "Эх, юность! От горя до веселья - один порыв... Верни мою руку, красавица, и я отправлюсь на поиски.";
        link.l1.go = "Consumption_9";
        break;

    case "Consumption_9":
        DialogExit();
        npchar.dialog.filename = "Quest\LineMiniQuests\Consumption.c";
        npchar.dialog.currentnode = "First time";
        pchar.questTemp.Consumption = "begin";
        AddQuestRecord("Consumption", "1");
        break;
    //<-- Цена чахотки

    // Addon-2016 Jason, французские миниквесты (ФМК) Порт Пренс
    case "FMQP":
        dialog.text = "Это не шутки, месье! Наверху! Наверху, в комнате - два негодяя убивают благородного джентльмена! Помогите, капитан, вы один тут при оружии!";
        link.l1 = "Беги на улицу, зови стражников! Я наверх!!";
        link.l1.go = "FMQP_1";
        link.l2 = "Дорогуша, ты, кажется, перепутала меня со стражником. Если кого-то убивают - надо звать патрульных.";
        link.l2.go = "FMQP_exit";
        break;

    case "FMQP_exit":
        dialog.text = "А-а-а, стража, на помощь!!";
        link.l1 = "...";
        link.l1.go = "FMQP_exit_1";
        break;

    case "FMQP_exit_1":
        DialogExit();
        chrDisableReloadToLocation = false;
        DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
        LocatorReloadEnterDisable("Portpax_town", "reload4_back", true);
        SetFunctionTimerCondition("FMQP_Remove", 0, 0, 1, false);
        break;

    case "FMQP_1":
        DialogExit();
        LAi_SetActorType(npchar);
        LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
        pchar.quest.FMQP_room.win_condition.l1 = "locator";
        pchar.quest.FMQP_room.win_condition.l1.location = "Portpax_tavern";
        pchar.quest.FMQP_room.win_condition.l1.locator_group = "reload";
        pchar.quest.FMQP_room.win_condition.l1.locator = "reload2_back";
        pchar.quest.FMQP_room.function = "FMQP_InRoom";
        break;
    }
}