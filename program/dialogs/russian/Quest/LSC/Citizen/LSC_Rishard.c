// Ришард Шамбон - контрабандист
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    float locx, locy, locz;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    ProcessCommonDialogRumors(NPChar, Link, NextDiag);

    switch (Dialog.CurrentNode)
    {
    case "First time":
        if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
        {
            dialog.text = "Я не желаю с тобой общаться. Ты нападаешь без причины на мирных граждан, провоцируешь их на драку. Уходи прочь!";
            link.l1 = "Гм...";
            link.l1.go = "exit";
            break;
        }
        // --> кольцо
        if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_2") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.ring"))
        {
            dialog.text = "О! Вот и ты, парень. А я уже было решил сам тебя разыскать. Ты мне нужен, дружище.";
            link.l1 = "Что-то ты сегодня подозрительно дружелюбен, Ришард. Ну, слушаю тебя.";
            link.l1.go = "ring";
            break;
        }
        // <-- кольцо
        if (npchar.quest.meeting == "0")
        {
            dialog.text = "Ну, чего тебе? Сказать честно - я не в настроении. Да и вообще я забыл, когда последний раз оно у меня было.";
            link.l1 = "Что, всё так плохо, приятель?";
            link.l1.go = "meeting";
            npchar.quest.meeting = "1";
        }
        else
        {
            dialog.text = "А, " + GetFullName(pchar) + "! " + TimeGreeting() + "! Ты что-то хотел?";
            link.l1 = LinkRandPhrase("Что-нибудь интересное мне расскажешь?", "Что нового произошло на острове в последнее время?", "Не расскажешь ли последние сплетни?");
            link.l1.go = "rumours_LSC";
            link.l2 = "Я хочу задать тебе пару вопросов об острове.";
            link.l2.go = "int_quests"; //информационный блок
            link.l5 = "Да просто решил узнать как у тебя дела. Ещё увидимся!";
            link.l5.go = "exit";
        }
        NextDiag.TempNode = "First time";
        break;

    case "meeting": // первая встреча
        dialog.text = "Плохо? Нет, не плохо. Просто я не в духе малость. Так чего ты хотел?";
        link.l1 = "Да просто познакомиться. Я тут недавно, вот, хожу по Острову, беседую с людьми.";
        link.l1.go = "meeting_1";
        break;

    case "meeting_1":
        dialog.text = "Да? Ну ладно. Я - Ришард Шамбон. Когда-то я занимался торговлей всякими ценными товарами, в том числе и запрещёнными, но последние десять лет я только и делаю, что ковыряюсь во внутренностях корабельных остовов, разыскивая всякий хлам и обменивая его на еду и золото.";
        link.l1 = "А я - " + GetFullName(pchar) + ", капитан собственного корабля...";
        link.l1.go = "meeting_2";
        break;

    case "meeting_2":
        dialog.text = "Ты наверное хотел сказать - бывший капитан, хе-хе?";
        link.l1 = "Ну, вообще-то мой корабль сейчас в Блювельде. А сюда я добрался на тартане.";
        link.l1.go = "meeting_3";
        break;

    case "meeting_3":
        dialog.text = "Да ну? Не может быть! И где же твоя тартана сейчас?";
        link.l1 = "Гм... На дне.";
        link.l1.go = "meeting_4";
        break;

    case "meeting_4":
        dialog.text = "А-а... А я-то уже подумал... Ладно, приятель, лучше я выпью рому...";
        link.l1 = "Удачи. Приятно было поболтать. Ещё увидимся!";
        link.l1.go = "exit";
        link.l2 = LinkRandPhrase("Что-нибудь интересное мне расскажешь?", "Что нового произошло на острове в последнее время?", "Не расскажешь ли последние сплетни?");
        link.l2.go = "rumours_LSC";
        link.l3 = "Я хочу задать тебе пару вопросов об острове.";
        link.l3.go = "int_quests"; //информационный блок
        NextDiag.TempNode = "First time";
        break;

    // Кольцо
    case "ring":
        dialog.text = "А что, разве я раньше был каким-то другим? Да ладно тебе, бывали у меня дни без настроения - у кого же их нет! Скажи мне лучше: ходят тут по Острову слухи, что ты выдающийся боец. Это так?";
        link.l1 = "Не знаю, кто там и что рассказывает про то, какой я боец. Однако я знаю, с какого конца держать шпагу, если ты об этом спрашиваешь.";
        link.l1.go = "ring_1";
        npchar.quest.ring = "true";
        break;

    case "ring_1":
        dialog.text = "Ясно. Вижу, слухи не лгут... Послушай, " + pchar.name + ", помнишь, я как-то тебе рассказывал про внешнее кольцо? Про то, что там можно пошариться и разыскать ценные вещички?";
        link.l1 = "Да вы тут все об этом внешнем кольце говорите... Причём одно и то же.";
        link.l1.go = "ring_2";
        break;

    case "ring_2":
        dialog.text = "А что же другое о нём говорить-то, ха-ха! Ладно. Довольно предисловий, перехожу к делу. (понижая голос) Мне удалось отыскать у внешнего кольца один хорошо сохранившийся корабль. Он стоит отдельно от других среди рифов, причем ровненько-ровненько, что редкость немалая\nКорабль большой - пинас. Прибило его к нам недавно, месяца два тому или немного больше. Пока никто из других жителей его не обнаружил, так что есть шанс неплохо поживиться, покопавшись в его трюме и каютах.";
        link.l1 = "Прекрасно, я рад за тебя. Ну а я-то тут причём? Или ты хочешь позвать меня с собой за компанию?";
        link.l1.go = "ring_3";
        break;

    case "ring_3":
        dialog.text = "Именно! Слушай дальше. У этого пинаса раздроблена носовая часть. Через пролом в корпусе в трюм забрались эти чёртовы крабы и устроили там настоящее гнездо. Пока они внутри - пробраться на корабль не получится, ибо как забраться на палубу из воды по гладкому борту - я не представляю\nСам я с крабами не справлюсь - признаюсь, я никогда не отличался талантами в фехтовании, а за последние годы и вовсе не притрагивался к оружию - нужды не было. Поэтому я и пришёл к тебе.";
        link.l1 = "То есть ты предлагаешь мне перебить крабов внутри этого корабля, так?";
        link.l1.go = "ring_4";
        break;

    case "ring_4":
        dialog.text = "Ну да. Мы заключаем с тобой соглашение: я показываю дорогу на корабль, а ты - ликвидируешь крабов. Всё найденное на корабле достанется нам двоим. Так будет справедливо - я нашёл судно, ты пробил дорогу.";
        link.l1 = "Нет, приятель, не заинтересовало меня твоё предложение. Драться в трюме полузатопленного корабля со стаей крабов ради сомнительных трофеев - это не по мне. Поищи другого рискового парня, который будет таскать для тебя каштаны из огня.";
        link.l1.go = "ring_exit";
        link.l2 = "Интересно... Я давно хотел побывать на внешнем кольце. По рукам! С крабами я разберусь.";
        link.l2.go = "ring_5";
        break;

    case "ring_exit":
        dialog.text = "Напрасно ты так... На кораблях внешнего кольца полно всякой всячины... Тем более, на этом судне ещё никто не был. Ладно, дело твоё. Бывай...";
        link.l1 = "Пока, приятель...";
        link.l1.go = "exit";
        break;

    case "ring_5":
        dialog.text = "Я рад, что не ошибся в тебе, дружище. У меня предчувствие, что мы найдём там много чего интересного...";
        link.l1 = "Посмотрим. Сколько в трюме крабов, ты не знаешь?";
        link.l1.go = "ring_6";
        break;

    case "ring_6":
        dialog.text = "Мне показалось, четыре, или пять... Ну, где-то так.";
        link.l1 = "Управимся. Когда идём?";
        link.l1.go = "ring_7";
        break;

    case "ring_7":
        dialog.text = "Давай завтра - сначала следует подготовиться, и тебе, и мне. Запасись лечебными микстурами у брата Юлиана - в челюстях крабов содержится яд. Осторожность не помешает. Встречаемся в восемь утра на 'косой палубе'. Знаешь, где это?";
        link.l1 = "Нет. Объясни.";
        link.l1.go = "ring_8";
        break;

    case "ring_8":
        dialog.text = "За 'Сан-Августином' из воды торчит обломок старого корабля. Его нос ушёл под воду, а корма задрана вверх - поэтому и называется 'косой палубой'. Добраться туда можно только вплавь. Удобнее всего войти в воду с 'Сан-Августина' под висячим мостиком, и обогнуть корабль с любой стороны. Оттуда и поплывём на внешнее кольцо.";
        link.l1 = "Хорошо. До встречи завтра!";
        link.l1.go = "ring_9";
        break;

    case "ring_repeat":
        dialog.text = "В восемь часов на 'косой палубе'...";
        link.l1 = "Да-да, я помню...";
        link.l1.go = "exit";
        NextDiag.TempNode = "ring_repeat";
        break;

    case "ring_9":
        DialogExit();
        NextDiag.CurrentNode = "ring_repeat";
        pchar.quest.LSC_Ring_Start.win_condition.l1 = "Timer";
        pchar.quest.LSC_Ring_Start.win_condition.l1.date.hour = 7.0;
        pchar.quest.LSC_Ring_Start.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
        pchar.quest.LSC_Ring_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
        pchar.quest.LSC_Ring_Start.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
        pchar.quest.LSC_Ring_Start.function = "LSC_RingStart"; // готовы
        pchar.quest.LSC_Ring_Over.win_condition.l1 = "Timer";
        pchar.quest.LSC_Ring_Over.win_condition.l1.date.hour = 10.0;
        pchar.quest.LSC_Ring_Over.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
        pchar.quest.LSC_Ring_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
        pchar.quest.LSC_Ring_Over.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
        pchar.quest.LSC_Ring_Over.function = "LSC_RingOver"; // опоздание
        AddQuestRecord("LSC_Ring", "1");
        break;

    case "ring_10":
        dialog.text = "Ага, вот и ты, дружище. Готов шинковать крабовый салат?";
        link.l1 = "Конечно!";
        link.l1.go = "ring_11";
        break;

    case "ring_11":
        dialog.text = "Очень хорошо. Теперь поверни голову в сторону внешнего кольца и смотри: видишь эти два корабельных обломка, торчащие из воды?";
        link.l1 = "Гм... Да, вижу.";
        link.l1.go = "ring_12";
        break;

    case "ring_12":
        dialog.text = "Теперь гляди между ними на внешнее кольцо. Видишь галеон в кольце с задранной носовой частью? Смотрит прямо на нас. Приглядись внимательнее.";
        link.l1 = "...";
        link.l1.go = "ring_look";
        break;

    case "ring_look":
        DialogExit();
        LAi_SetActorType(pchar);
        LAi_ActorTurnToLocator(pchar, "reload", "reload_ring");
        DoQuestCheckDelay("LSC_RingTalkLook", 6.0);
        break;

    case "ring_13":
        dialog.text = "";
        link.l1 = "Так, кажется, вижу... Да, нашёл!";
        link.l1.go = "ring_13a";
        break;

    case "ring_13a":
        dialog.text = "Нам туда. Плывем прямо, никуда не сворачивая, в направлении этого галеона. Как достигнем кольца - дальше я покажу дорогу, нужно будет пробраться на обратную сторону. Вход в трюм моего корабля - через пролом в носовой части. Скажу сразу: я туда не полезу, пока ты не почикаешь всех крабов.";
        link.l1 = "Мы с тобой уже об этом договорились вчера, я помню. Ты - показываешь корабль, я - уничтожаю крабов. Поплыли?";
        link.l1.go = "ring_14";
        break;

    case "ring_14":
        dialog.text = "Поплыли! Ты вперёд, я за тобой!";
        link.l1 = "...";
        link.l1.go = "ring_swim";
        break;

    case "ring_swim":
        DialogExit();
        LAi_SetActorType(npchar);
        LAi_ActorFollow(npchar, pchar, "", -1);
        LAi_SetImmortal(npchar, true);
        pchar.quest.LSC_Ring_enter.win_condition.l1 = "locator";
        pchar.quest.LSC_Ring_enter.win_condition.l1.location = "LostShipsCity_town";
        pchar.quest.LSC_Ring_enter.win_condition.l1.locator_group = "reload";
        pchar.quest.LSC_Ring_enter.win_condition.l1.locator = "reload_ring";
        pchar.quest.LSC_Ring_enter.function = "LSC_RingEnter";
        LSC_RingSetItems(); // раскладка итемзов
        AddQuestRecord("LSC_Ring", "3");
        break;

    case "ring_15":
        dialog.text = "Хех, ты молодец! Ловко разделался со всей этой пакостью!";
        link.l1 = "Кто-то говорил мне о 'четырех-пяти' крабах... Не напомнишь, кто это был?";
        link.l1.go = "ring_16";
        break;

    case "ring_16":
        dialog.text = "Дружище, я же не лазил в трюм их пересчитывать. Я смотрел снаружи, в пролом, и насчитал именно столько. Так что у меня и в мыслях не было тебе лгать.";
        link.l1 = "Ладно. Давай осматривать трюм, что ли...";
        link.l1.go = "ring_17";
        break;

    case "ring_17":
        dialog.text = "А как же! Ведь именно за этим мы сюда явились, не правда ли?";
        link.l1 = "Точно! Не будем терять времени...";
        link.l1.go = "ring_18";
        break;

    case "ring_18":
        DialogExit();
        NextDiag.CurrentNode = "ring_wait";
        LAi_SetWarriorType(npchar);
        LAi_warrior_DialogEnable(npchar, true);
        LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
        DoQuestCheckDelay("LSC_RingDialog", 60.0); // 1 минуту на пошариться
        npchar.quest.diagnode = "ring_19";
        AddQuestRecord("LSC_Ring", "4");
        break;

    case "ring_wait":
        dialog.text = "Погоди, дружище, я ещё не всё осмотрел, что хотел. Поройся получше, может, ещё что найдёшь.";
        link.l1 = "Хорошо...";
        link.l1.go = "exit";
        NextDiag.TempNode = "ring_wait";
        break;

    case "ring_19":
        dialog.text = "Пока ничего особенного. Жаль, особо ценных товаров нет: в бочках - провиант, в ящиках - копра. Хотя нашёлся ящик с бутылками дорогого вина. А у тебя что?";
        link.l1 = "Тоже ничего особенного. Несколько ящиков представляли интерес, остальное - как ты и сказал, солонина да копра.";
        link.l1.go = "ring_20";
        break;

    case "ring_20":
        dialog.text = "Маловато будет... Поднимаемся наверх, обыщем палубу и каюты.";
        link.l1 = "Пойдём.";
        link.l1.go = "ring_21";
        break;

    case "ring_21":
        DialogExit();
        chrDisableReloadToLocation = false;
        LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
        LAi_SetActorType(npchar);
        LAi_ActorFollowEverywhere(npchar, "", -1);
        pchar.quest.LSC_Ring_deck.win_condition.l1 = "ExitFromLocation";
        pchar.quest.LSC_Ring_deck.win_condition.l1.location = pchar.location;
        pchar.quest.LSC_Ring_deck.win_condition = "LSC_RingEnterDeck";
        for (i = 1; i <= 3; i++)
        {
            sld = ItemsFromID("purse" + i);
            sld.shown = true;
            sld.startLocation = "ExternalRingDeck";
            sld.startLocator = "item" + i;
        }
        break;

    case "ring_22":
        dialog.text = "Чёрт возьми! Ты только посмотри на это! Проклятая крабовая погань заползла и на палубу! Как они ухитрились?!";
        link.l1 = "Не трусь! Стой здесь и не шевелись, не привлекай их внимание. Сейчас я с этими тварями разберусь...";
        link.l1.go = "ring_23";
        break;

    case "ring_23":
        DialogExit();
        LAi_SetActorType(npchar);
        LAi_ActorRunToLocator(npchar, "reload", "reload1", "", -1);
        break;

    case "ring_24":
        dialog.text = "Ух! Недаром про тебя рассказывали, что ты великолепно владеешь оружием. Был бы я один - уже давно сиганул бы за борт...";
        link.l1 = "Слушай, и как ты только контрабандистом заделался в прошлом, а? Или ты всегда и от всех бегал?";
        link.l1.go = "ring_25";
        break;

    case "ring_25":
        dialog.text = "Дружище, во-первых, тогда я был моложе, сильнее и отчаяннее. Во-вторых, я же не наёмник, чтобы участвовать в войнах - я контрабандист, а мы всегда старались уклониться от стычек с солдатами. В третьих, я был больше по части парусов и румпеля, нежели шпаги и пистолета. Ну и в-четвёртых, за десять лет тихой жизни на Острове я совсем размяк\nТак что не суди меня строго. Давай лучше осмотрим палубу. Похоже, перед тем как попасть сюда, этот корабль побывал в серьёзном бою - смотри - проломы от ядер в бортах и палубе, бочки с порохом у пушек...";
        link.l1 = "Ты прав. Корабль был под обстрелом, это очевидно. Ладно, давай искать что-нибудь интересное.";
        link.l1.go = "ring_26";
        break;

    case "ring_26":
        dialog.text = "Угу. И надо поискать входы во внутренние помещения.";
        link.l1 = "Всё, не теряем времени. Встретишь краба - зови на помощь.";
        link.l1.go = "ring_27";
        break;

    case "ring_27":
        DialogExit();
        NextDiag.CurrentNode = "ring_wait";
        LAi_SetWarriorType(npchar);
        LAi_warrior_DialogEnable(npchar, true);
        LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
        DoQuestCheckDelay("LSC_RingDialog", 80.0); // 1.3 минуты на пошариться
        npchar.quest.diagnode = "ring_28";
        AddQuestRecord("LSC_Ring", "5");
        break;

    case "ring_28":
        dialog.text = "И снова ничего значительного... Нашел пару интересных мелочей, и всё. Но это нормально - на палубах ценностей обычно не бывает. Всё самое лучшее лежит в каютах. Вон там - вход в каюту капитана. Пойдём, пороемся там...";
        link.l1 = "Смотри аккуратнее - чёрт его знает, что там может скрываться. Может, лучше я пойду первым?";
        link.l1.go = "ring_29";
        break;

    case "ring_29":
        dialog.text = "Пойдём, " + pchar.name + ". Не всё же мне у тебя за спиной прятаться. И в самом деле - стыдно...";
        link.l1 = "Ну, пошли...";
        link.l1.go = "ring_30";
        break;

    case "ring_30":
        DialogExit();
        chrDisableReloadToLocation = true;
        LocatorReloadEnterDisable("ExternalRingDeck", "reload2", false);
        LAi_SetActorType(npchar);
        LAi_ActorRunToLocation(npchar, "reload", "reload2", "ExternalRingCabin1", "reload", "reload1", "OpenTheDoors", -1);
        pchar.quest.LSC_Ring_cabin.win_condition.l1 = "location";
        pchar.quest.LSC_Ring_cabin.win_condition.l1.location = "ExternalRingCabin1";
        pchar.quest.LSC_Ring_cabin.win_condition = "LSC_RingEnterCabin";
        sld = ItemsFromID("RingCapBook"); // кладем журнал 'Санта-Люсии'
        sld.shown = true;
        sld.startLocation = "ExternalRingCabin1";
        sld.startLocator = "item1";
        break;

    case "ring_31":
        dialog.text = "Кажется, мне повезло - не оказалось ни крабов, ни какой-либо прочей погани. А теперь перевернём всю эту каюту вверх дном - клянусь честью, я уже начинаю злиться: кроме двух десятков дублонов и всякой никчемной мелочевки я пока ничего не нашёл!";
        link.l1 = "Не заводись. Ты правильно сказал - все ценности хранятся в капитанской каюте. Ищем!";
        link.l1.go = "ring_32";
        break;

    case "ring_32":
        DialogExit();
        NextDiag.CurrentNode = "ring_wait";
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocator(npchar, "goto", "goto2", "LSC_RingSetToBarman", -1);
        DoQuestCheckDelay("LSC_RingDialog", 30.0); // 30 сек на пошариться
        npchar.quest.diagnode = "ring_33";
        break;

    case "ring_33":
        dialog.text = "Ха-ха! Как я и думал! Знаю я замашки этих торгашей - устраивать тайники и прятать там корабельную казну! Капитан этого пинаса был хитрый пройдоха, но меня не проведёшь! Смотри, что мне удалось добыть! Сам бы ты в жизни не нашёл этого схрона!";
        link.l1 = "Ну-ка, покажи!";
        link.l1.go = "ring_34";
        break;

    case "ring_34":
        dialog.text = "Сорок тысяч песо, два сундука с дублонами, мешочек изумрудов и куча драгоценностей! Богатенький был владелец... Ладно, это хотя бы окупит наши с тобой труды, хотя я рассчитывал на большее. Делим по-братски, напополам, как договаривались.";
        link.l1 = "Отлично, Ришард. Хоть что-то мы с тобой заработали!";
        link.l1.go = "ring_35";
        break;

    case "ring_35":
        TakeNItems(pchar, "jewelry4", 25);
        TakeNItems(pchar, "chest", 1);
        TakeNItems(pchar, "icollection", 1);
        AddMoneyToCharacter(pchar, 20000);
        Log_Info("Вы получили сундук с дублонами");
        Log_Info("Вы получили 25 изумрудов");
        Log_Info("Вы получили коллекцию драгоценностей");
        PlaySound("interface\important_item.wav");
        dialog.text = "Ну, а то, что каждый из нас нашёл в трюме и на палубе - оставим себе. Лады? В сундуках и шкафах что-нибудь полезное было?";
        link.l1 = "Несколько индейских побрякушек, амулетов, бумаги, прочая мелочь.";
        link.l1.go = "ring_36";
        break;

    case "ring_36":
        dialog.text = "Забери это себе. В конце-концов, ты выполнил самую опасную работу.";
        if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
        {
            link.l1 = "Хорошо. Но я нашёл кое-что ещё, по твоей части, искатель тайников. Вот, на столе лежал судовой журнал. История, содержащаяся в нём, очень печальная... но кое-чем она теперь касается и нас: где-то в трюме спрятан целый ящик золота! Прочти сам!";
            link.l1.go = "ring_41";
        }
        else
        {
            if (CheckCharacterItem(pchar, "RingCapBook")) // взял журнал
            {
                link.l1 = "Хорошо. Но я нашёл кое-что ещё - судовой журнал капитана этого корабля.";
                link.l1.go = "ring_38";
            }
            else
            {
                link.l1 = "Хорошо, я не возражаю против такого расклада, хе-хе. Ну что, пора возвращаться?";
                link.l1.go = "ring_37";
            }
        }
        break;

    case "ring_37":
        dialog.text = "Да. Про корабль никому не рассказывай - пусть будет нашей тайной. Копра, конечно, никому тут не нужна, а вот провиант пригодится нам самим. Не надо будет покупать у адмирала.";
        link.l1 = "Хорошо, так и сделаем. Надеюсь, другие найдут этот корабль не скоро. Уходим!";
        link.l1.go = "ring_cabin_exit";
        break;

    case "ring_38":
        dialog.text = "Ты его прочёл?";
        link.l1 = "Пока нет...";
        link.l1.go = "ring_39";
        break;

    case "ring_39":
        dialog.text = "Тогда давай читать! Там могут содержаться важные сведения. Да и просто интересно узанть, почему этот корабль оказался тут. Читай!";
        link.l1 = "Хм. Хорошо, сейчас почитаем...";
        link.l1.go = "ring_40";
        break;

    case "ring_40":
        DialogExit();
        NextDiag.CurrentNode = "book_wait";
        LAi_SetWarriorType(npchar);
        LAi_warrior_DialogEnable(npchar, true);
        LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
        break;

    case "book_wait":
        dialog.text = "Прочёл? Что там написано?";
        if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
        {
            link.l1 = "Тут написано такое... История очень печальная... но кое-чем она теперь касается и нас. В общем, это по твоей части, искатель тайников: где-то в трюме спрятан целый ящик золота! Прочти сам!";
            link.l1.go = "ring_41";
        }
        else
        {
            link.l1 = "Погоди. Сейчас прочту и расскажу...";
            link.l1.go = "exit";
            NextDiag.TempNode = "book_wait";
        }
        break;

    case "ring_41":
        dialog.text = "Да ты что?! " + pchar.name + ", я это... плохо читаю. Лучше расскажи мне в подробностях, что там написано, а?";
        link.l1 = "Вкратце: этот пинас пересекал Карибское море от Южного Мэйна в сторону Новой Испании. Капитан взял себе в жены принцессу-индианку из племён нижнего Ориноко, а она показала ему, где их люди делали жертвоприношения богам...";
        link.l1.go = "ring_42";
        break;

    case "ring_42":
        dialog.text = "";
        link.l1 = "Жертвоприношения были в виде золотых самородков. Наш отважный капитан, безусловно, разграбил этот золотой запас, и вместе со старпомом и квартирместером перенёс тайком от команды в трюм корабля, сложил в один из ящиков и присыпал копрой...";
        link.l1.go = "ring_43";
        break;

    case "ring_43":
        dialog.text = "";
        link.l1 = "Но, видно, грабёж священного индейского места не прошёл бесследно: корабль попал в мёртвый штиль, начала заканчиваться пресная вода, на корабле вспыхнула эпидемия лихорадки, напали пираты. Матросы обвинили во всём индианку, жену капитана, и потребовали выбросить её за борт. Кэп, конечно, отказался, и команда подняла бунт...";
        link.l1.go = "ring_44";
        break;

    case "ring_44":
        dialog.text = "";
        link.l1 = "Капитан проиграл этот бой. Последние записи - он заперся вместе с индианкой в каюте, отстреливаясь, а разъярённые матросы ломали дверь. На горизонте надвигался шторм... видимо, он-то и принёс пинас сюда. Как закончилась трагедия - ясно: девушку застрелили, а капитан, безусловно, был убит бунтовщиками.";
        link.l1.go = "ring_45";
        break;

    case "ring_45":
        dialog.text = "Хм. Действительно печально. Но ты не шутишь? В трюме спрятан целый ящик золота? Я не верю своим ушам! Но который из них? Пошли скорее в трюм! Я перерою каждый тюк, каждую бочку!";
        link.l1 = "Пойдём. Мне тоже не терпится приступить к поискам.";
        link.l1.go = "ring_seek_gold";
        break;

    case "ring_cabin_exit":
        DialogExit();
        chrDisableReloadToLocation = false;
        LocatorReloadEnterDisable("ExternalRingInside", "reload1", false);     // открываем выход
        LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход // patch-2
        DoQuestReloadToLocation("ExternalRingDeck", "reload", "reload2", "LSC_RingFinalStage");
        sld = ItemsFromID("RingCapBook");
        sld.shown = false; // убираем журнал
        AddQuestRecord("LSC_Ring", "6");
        break;

    case "ring_seek_gold":
        DialogExit();
        chrDisableReloadToLocation = false;
        LAi_SetActorType(npchar);
        LAi_ActorFollowEverywhere(npchar, "", -1);
        // ставим прерывание на локатор
        pchar.quest.LSC_Ring_gold.win_condition.l1 = "locator";
        pchar.quest.LSC_Ring_gold.win_condition.l1.location = "ExternalRingInside";
        pchar.quest.LSC_Ring_gold.win_condition.l1.locator_group = "quest";
        pchar.quest.LSC_Ring_gold.win_condition.l1.locator = "gold";
        pchar.quest.LSC_Ring_gold.win_condition = "LSC_RingFindGold";
        // подменяем состав бокса
        pchar.GenQuestBox.ExternalRingInside = true;
        pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 2522;
        AddQuestRecord("LSC_Ring", "7");
        break;

    case "ring_46":
        dialog.text = "Ха-ха! Мы нашли его! Оно действительно есть! Ты только посмотри, какая огромная куча! Целый ящик! Да тут не меньше пяти тысяч слитков! Никогда не видел такую груду золота!";
        link.l1 = "Поздравляю, компаньон. Наше предприятие, похоже, завершилось феноменальным успехом... Что делать с золотом будем?";
        link.l1.go = "ring_47";
        break;

    case "ring_47":
        dialog.text = "Как что? Поделим напополам!";
        link.l1 = "Это понятно. Где ты его хранить собираешься? Здесь оставишь, или перетаскивать куда будешь?";
        link.l1.go = "ring_48";
        break;

    case "ring_48":
        dialog.text = "Ха! Конечно, всё спрячу по своим тайникам, которые никто и никогда не найдёт. Я-то умею прятать! Давай сейчас половину золота переложим в бочку - это будет моя доля. И ещё до восхода солнца я её унесу с этого корабля\nА ты - делай со своей долей, что сочтёшь нужным. Но лучше тоже перепрячь, а то вдруг пропадёт - обвинишь меня в этом. Но сразу скажу: я - человек по-своему честный, и на твою долю даже не посмею покуситься. А вот другие, кто сюда придёт... могут и найти случайно.";
        link.l1 = "Хорошо. Я решу, что мне сделать со своим золотом. Давай перекладывать твою долю в бочку...";
        link.l1.go = "ring_49";
        break;

    case "ring_49":
        DialogExit();
        SetLaunchFrameFormParam("Прошло два часа..." + NewStr() + "Золото поделено!", "", 0, 5); //табличка
        WaitDate("", 0, 0, 0, 2, 10);
        LaunchFrameForm();
        RecalculateJumpTable();
        sld = characterFromId("LSC_Rishard");
        sld.quest.diagnode = "ring_50";
        DoQuestCheckDelay("LSC_RingDialog", 5.0);
        break;

    case "ring_50":
        dialog.text = "Вот и всё... Спасибо, " + pchar.name + ", что согласился пойти со мной на дело. Без тебя бы ничего не вышло. Теперь можно озадачиться постройкой тартаны, чтобы уплыть на архипелаг... а, ладно. Не буду думать об этом сегодня\nУ меня ещё очень много работы - перетаскать своё золото по безопасным местам. Пока, дружище, желаю удачно распорядиться своей долей!";
        link.l1 = "Пока, Ришард. Славный сегодня день выдался. Увидимся!";
        link.l1.go = "ring_51";
        break;

    case "ring_51":
        DialogExit();
        LocatorReloadEnterDisable("ExternalRingInside", "reload1", false);     // открываем выход
        LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход
        DoQuestCheckDelay("LSC_RingFinalStage", 0.5);
        DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
        AddQuestRecord("LSC_Ring", "8");
        break;
        //--------------------------------------- блок вопросов и ответов ---------------------------------------------
    case "int_quests":
        dialog.text = "Вопросы? Ох, ну давай, раз тебе это так необходимо...";
        if (!CheckAttribute(npchar, "quest.answer_1"))
        {
            link.l1 = "Как ты попал сюда?";
            link.l1.go = "ansewer_1";
        }
        if (!CheckAttribute(npchar, "quest.answer_2"))
        {
            link.l2 = "Ты бы хотел выбраться отсюда?";
            link.l2.go = "ansewer_2";
        }
        if (!CheckAttribute(npchar, "quest.answer_3"))
        {
            link.l3 = "А ты никогда не хотел примкнуть к одному из кланов? Например, к нарвалам?";
            link.l3.go = "ansewer_3";
        }
        if (!CheckAttribute(npchar, "quest.answer_4"))
        {
            link.l4 = "Так что, на кораблях внешнего кольца можно найти много чего интересного?";
            link.l4.go = "ansewer_4";
        }
        link.l10 = "Нет вопросов. Извините...";
        link.l10.go = "exit";
        break;

    case "ansewer_1":
        dialog.text = "Десять лет назад я с товарищами постоянно совершал переходы между Островом и Кубой на хорошо оснащённой тартане. Мы держали в тайне местонахождение Острова - сюда мы привозили туши быков и обменивали свежее мясо на товары из трюмов погибших кораблей и золото\nВот это было времечко! С провиантом здесь всегда было не ах - в основном сухари да солонина, поэтому за сочное мясо платили пряностями, стоящими в Европе целое состояние! За один рейс я зарабатывал столько, что мог скупить всех шлюх Тортуги в вечное пользование\nНо всему приходит конец, пришёл конец и нашей сытой жизни. В этих краях изменилась погода - штормы стали чаще и суровее, и всё опаснее было добираться до Острова. Некоторые мои соратники вышли из дела, но я и десяток храбрецов продолжали путешествия\nДо тех пор, пока нас в конце концов не разбило о рифы в двух милях от Острова. Как я сюда добрался вплавь по бурному морю - я и сам понять не могу до сих пор. Таким образом я и стал одним из тех, с кем раньше торговал.";
        link.l1 = "Интересная история...";
        link.l1.go = "int_quests";
        npchar.quest.answer_1 = "true";
        break;

    case "ansewer_2":
        dialog.text = "Ха! Я выберусь отсюда, чёрт побери! Но не сейчас. Что мне делать на Кубе? Друзей у меня не осталось, денег тоже не густо. Вот как только найду на внешнем кольце корабль с богатым грузом, или кучу золотых дублонов - сразу же начну строить лодку.";
        link.l1 = "Понятно...";
        link.l1.go = "int_quests";
        npchar.quest.answer_2 = "true";
        SaveCurrentNpcQuestDateParam(npchar, "quest_date");
        break;

    case "ansewer_3":
        dialog.text = "А зачем? Чтобы потом как дураку сутки через двое стоять в карауле навытяжку, гоняя всех, кто надумает сунуться на 'Сан-Габриэль'? Да и не горят они желанием посторонних к себе брать. Они же - потомственные островитяне, что ты... И негритосы ничем не лучше их. Нет, уж лучше я буду сам по себе.";
        link.l1 = "Ясно...";
        link.l1.go = "int_quests";
        npchar.quest.answer_3 = "true";
        break;

    case "ansewer_4":
        dialog.text = "А как же! Островитяне только с этого и живут. Знаешь, когда на Острове праздник? Когда к нам прибивает новый корабль. Но в любом случае, во внешнем кольце ещё очень много необследованных и невыпотрошенных лоханок, в трюмах которых можно найти ценные товары и золото\nНо сложность в том, что по внешнему кольцу практически невозможно ходить - всё стоит вкривь и вкось, а если запутаешься или поскользнёшься и неудачно упадешь - можешь свалиться в такое место, откуда самостоятельно не выбраться. И тогда тебе конец. Уже много людей так пропало.";
        link.l1 = "Хм... Занятно.";
        link.l1.go = "int_quests";
        npchar.quest.answer_4 = "true";
        break;
        // <-- блок вопросов и ответов

        //----------------------------------------- специальные реакции -----------------------------------------------
        //обнаружение ГГ в сундуках
    case "Man_FackYou":
        dialog.text = LinkRandPhrase("Что ты там копаешься, а? Да ты вор!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой!", "По сундукам шарить вздумал?! Тебе это даром не пройдёт!");
        link.l1 = "А-ать, дьявол!!!";
        link.l1.go = "fight";
        break;

    case "Woman_FackYou":
        dialog.text = "Ах, вот, значит, как?! По сундукам шарить вздумал?! Тебе это даром не пройдёт!";
        link.l1 = "Вот дура!..";
        link.l1.go = "exit_setOwner";
        LAi_group_Attack(NPChar, Pchar);
        break;

    case "fight":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        LAi_SetOwnerTypeNoGroup(npchar);
        LAi_group_Attack(NPChar, Pchar);
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

    case "exit_setOwner":
        LAi_SetOwnerTypeNoGroup(npchar);
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    //замечание по обнаженному оружию
    case "LSCNotBlade":
        dialog.text = LinkRandPhrase("Слушай, ты бы убрал оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как д'Артаньян, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это серьезному мужчине...");
        link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
        link.l1.go = "exit";
        NextDiag.TempNode = "First Time";
        break;

    case "CitizenNotBlade":
        if (loadedLocation.type == "town")
        {
            dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
            link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
        }
        else
        {
            dialog.text = NPCharSexPhrase(NPChar, "Острожней на поворотах, приятель, когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда мужчины ходят передо мной с оружием на изготовку. Это меня пугает...");
            link.l1 = RandPhraseSimple("Понял.", "Убираю.");
        }
        link.l1.go = "exit";
        NextDiag.TempNode = "First Time";
        break;
        // <-- специальные реакции

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;
    }
}