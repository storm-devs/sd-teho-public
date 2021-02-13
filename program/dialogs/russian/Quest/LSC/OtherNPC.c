// диалоги прочих НПС по квесту LSC
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    int i;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
    case "First time":
        dialog.text = "Вы что-то хотели?";
        link.l1 = "Да нет, ничего.";
        link.l1.go = "exit";
        NextDiag.TempNode = "First time";
        break;

    //-----------------------------------бандосы Акулы в трюме с припасами--------------------------------------
    case "PantryGuard":
        dialog.text = "О-хо-хо, посмотрите-ка ребята, кто к нам пожаловал! Не иначе, как вор, любитель полазить по чужим сундукам! Сюда, скорее! А ты, голубчик, даже не пытайся рыпаться и хвататься за свою железку - с такого расстояния я не промахнусь... Чад будет очень рад тебя видеть!";
        link.l1 = "Но я... я только попал сюда!..";
        link.l1.go = "PantryGuard_1";
        break;

    case "PantryGuard_1":
        dialog.text = "Вот тут ты прав, хо-хо! Попал ты конкретно, парень... Так попал, что наверное, уже не выберешься. А ну, сдай оружие и марш вперёд! Клетка на 'Тартарусе' давно тебя заждалась, ворюга!";
        link.l1 = "...";
        link.l1.go = "PantryGuard_2";
        break;

    case "PantryGuard_2":
        DialogExit();
        chrDisableReloadToLocation = false;
        SetLaunchFrameFormParam("Прошло несколько часов...", "", 0, 3);
        LaunchFrameForm();
        WaitDate("", 0, 0, 0, 7, 10); //крутим время
        RecalculateJumpTable();
        DoQuestFunctionDelay("LSC_GotoPrison", 3.0);
        break;

    case "CommonGuard":
        dialog.text = "Не вздумай стянуть что-нибудь отсюда. Я буду присматривать за тобой.";
        link.l1 = "Да пожалуйста, смотри.";
        link.l1.go = "exit";
        NextDiag.TempNode = "CommonGuard";
        break;

    case "ChadGuard":
        dialog.text = "Иди и делай то, что тебе Чад сказал. Нечего тут языком трепать!";
        link.l1 = "Да, иду, иду...";
        link.l1.go = "exit";
        NextDiag.TempNode = "ChadGuard";
        break;

    case "ChadGuard_Attack":
        dialog.text = "Эй! Ты чего это там, в сундук залез, что ли? Ах ты, мерзавец! Ну, теперь тебе конец!";
        link.l1 = "...";
        link.l1.go = "ChadGuard_Attack_1";
        break;

    case "ChadGuard_Attack_1":
        DialogExit();
        sld = characterFromId("Chimiset");
        LAi_SetActorType(sld);
        LAi_ActorAnimation(sld, "afraid", "", -1);
        for (i = 1; i <= 3; i++)
        {
            sld = CharacterFromID("ChadGuard_" + i);
            LAi_RemoveCheckMinHP(sld);
            LAi_SetWarriorType(sld);
            LAi_group_MoveCharacter(sld, "EnemyFight");
        }
        sld = characterFromId("Capper");
        LAi_SetWarriorType(sld);
        ChangeCharacterAddressGroup(sld, "Tartarusprison", "goto", "goto8");
        LAi_group_MoveCharacter(sld, "EnemyFight");
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck("EnemyFight", "LSC_ChadGuard_Die");
        AddDialogExitQuest("MainHeroFightModeOn");
        pchar.GenQuest.Notsearchbody = true; // запрет обыска трупов
        break;

    // ----------------------------------Марчелло Циклоп--------------------------------
    // если ждали в каюте
    case "Cabin":
        dialog.text = "Эй, ты что здесь делаешь, чёрт бы тебя побрал? Где Барбье?";
        link.l1 = "Наш друг Адольфо немного... заболел. Он не смог прийти на встречу, вот и попросил меня посидеть у него в каюте и дождаться вас.";
        link.l1.go = "Cabin_1";
        break;

    case "Cabin_A":
        dialog.text = "Эй, чего тебе здесь надо, чёрт бы тебя побрал?";
        link.l1 = "Наш друг Адольфо немного... заболел. Он не смог прийти на встречу, вот и попросил меня, так скажем, подменить его.";
        link.l1.go = "Cabin_1";
        break;

    case "Cabin_1":
        dialog.text = "Странно всё это... с утра был совершенно здоров - и вдруг заболел.";
        link.l1 = "Ну ты же знаешь, как это бывает. Внезапный приступ лихорадки - и всё...";
        link.l1.go = "Cabin_2";
        break;

    case "Cabin_2":
        dialog.text = "Ох, и не нравится же мне твоя рожа. Врёшь ты всё. Барбье никому бы не доверил эту встречу. Говори, мерзавец, что ты с ним сделал, и кто ты?";
        link.l1 = "Знаешь, ты тоже не красавец, если что. Я же тебе сказал, что Барбье заболел. Ты что, тупой, или не доходит с первого раза? Он должен был передать вам ключ, и...";
        link.l1.go = "Cabin_3";
        break;

    case "Cabin_3":
        DialogExit();
        sld = characterFromId("Mary");
        LAi_SetActorType(sld);
        LAi_CharacterEnableDialog(sld);
        LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

    // на Церес Смити - спасаем Мэри
    case "mary":
        dialog.text = "Чёрт возьми! Выследил...";
        link.l1 = "Да, гнусный убийца! Теперь тебе конец!";
        link.l1.go = "mary_1";
        break;

    case "mary_1":
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
        DialogExit();
        LAi_SetWarriorType(npchar);
        LAi_group_MoveCharacter(npchar, "EnemyFight");
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck("EnemyFight", "LSC_KillCyclop_CS");
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

    // посланник от Акулы по варианту N
    case "SharkCureer":
        dialog.text = "Ведь это же ты - " + GetFullName(pchar) + "?";
        link.l1 = "Да, я. А в чём дело?";
        link.l1.go = "SharkCureer_1";
        break;

    case "SharkCureer_1":
        dialog.text = "Меня послал Акула. Он просит тебя как можно скорее явиться к нему - какое-то важное дело.";
        link.l1 = "Что за спешка?.. Хорошо, я немедленно отправляюсь на 'Сан-Августин'.";
        link.l1.go = "SharkCureer_2";
        break;

    case "SharkCureer_2":
        // сюда можно поставить таймер на гибель Акулы, если не придет до конца суток
        DialogExit();
        LAi_SetActorType(npchar);
        npchar.lifeday = 0;
        LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
        sld = characterFromId("Dodson");
        sld.dialog.currentnode = "entrance_20"; // ноду Акуле
        break;

    // посланник от Акулы по варианту M
    case "SharkCureer_3":
        dialog.text = "Ведь это же ты - " + GetFullName(pchar) + "?";
        link.l1 = "Да, я. А в чём дело?";
        link.l1.go = "SharkCureer_4";
        break;

    case "SharkCureer_4":
        if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
        {
            dialog.text = "Уф, уже с ног сбился тебя искавши... Меня послали Акула и Лейтон Декстер. Они просят тебя как можно скорее явиться к ним на совещание. Разговор очень важный, так что поспеши.";
            link.l1 = "Вот как? Хорошо, я немедленно отправляюсь на 'Сан-Августин'.";
            link.l1.go = "SharkCureer_6";
        }
        else
        {
            dialog.text = "Уф, уже с ног сбился тебя искавши... Меня послал адмирал, Лейтон Декстер. Он просит тебя как можно скорее явиться к нему на совещание. Разговор очень важный, так что поспеши.";
            link.l1 = "Лейтон Декстер - адмирал?";
            link.l1.go = "SharkCureer_5";
        }
        break;

    case "SharkCureer_5":
        dialog.text = "Ну да. Как наш старпом, после смерти Акулы он автоматически стал адмиралом.";
        link.l1 = "Понятно. Хорошо, я немедленно отправляюсь на 'Сан-Августин'.";
        link.l1.go = "SharkCureer_6";
        break;

    case "SharkCureer_6":
        DialogExit();
        LAi_SetActorType(npchar);
        npchar.lifeday = 0;
        LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
        break;

    // тюремщик вместо Каппера
    case "Prisonboss":
        if (npchar.quest.meeting == "0")
        {
            dialog.text = "А-а, это ты... Я помню тебя - ты последний, кто разговаривал с Чимисетом. Не ты ли прикончил колдуна, а?";
            link.l1 = "Не неси чепухи. Ты прекрасно знаешь, что не я. Думаю, ты догадываешься, кто убийца.";
            link.l1.go = "meeting";
            npchar.quest.meeting = "1";
        }
        else
        {
            dialog.text = "Эх, ну скука же торчать здесь весь день! Дружище, принёс бы ты рому, колоду карт - сыграли бы...";
            link.l1 = "Извини, приятель, некогда мне. Может, позже.";
            link.l1.go = "exit";
        }
        NextDiag.TempNode = "Prisonboss";
        break;

    case "meeting":
        dialog.text = "Догадываться-то догадываюсь, но фактов никаких нет. Никто не видел, как убили черномазого. Однако по острову поползли слухи, что расправились с колдуном именно мы, люди Акулы, и что сделал это какой-то новичок по прямому приказу адмирала. Смекаешь, в чей огород камешек? Так что лучше к ривадос не суйся без крайней необходимости, особенно сейчас - злы они очень.";
        link.l1 = "Хорошо. Я приму это к сведению.";
        link.l1.go = "exit";
        NextDiag.TempNode = "Prisonboss";
        break;

    case "Prisonboss_M":
        dialog.text = "Эх, ну скука же торчать здесь весь день! Дружище, принёс бы ты рому, колоду карт - сыграли бы...";
        link.l1 = "Извини, приятель, некогда мне. Может, позже.";
        link.l1.go = "exit";
        NextDiag.TempNode = "Prisonboss_M";
        break;

    // заместитель Акселя в магазине
    case "AxelHelper":
        dialog.text = "Чего тебе, приятель?";
        link.l1 = "Хм. А что вы здесь делаете? Где Аксель?";
        link.l1.go = "AxelHelper_1";
        break;

    case "AxelHelper_1":
        dialog.text = "Аксель занят. Он сейчас у Дональда Гринспи, и пробудет у него до ночи. Так что если ты хотел что-то купить - отложи свое желание до завтрашнего утра. А я здесь присматриваю за магазином, чтобы никто ничего не украл, так что смотри...";
        link.l1 = "Понятно. И чего ему именно сегодня приспичило? Ладно, приду утром.";
        link.l1.go = "exit";
        NextDiag.TempNode = "AxelHelper_2";
        break;

    case "AxelHelper_2":
        dialog.text = NPCStringReactionRepeat("Я тебе уже всё сказал. Приходи завтра.",
                                              "Не утомляй меня, приятель. Проваливай!",
                                              "Не зли меня, недоносок!",
                                              "Пошёл вон!!", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat("Хорошо.",
                                           "Да понял я, понял.",
                                           "Не гавкай...",
                                           "Что?!", npchar, Dialog.CurrentNode);
        link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
        break;

    // мать Белого Мальчика - Агнес Кристиансен
    case "agnes":
        dialog.text = "Что вам угодно, минхер?";
        link.l1 = "Гм... Простите, госпожа. Не сочтите за наглость или невежливость, но я хочу у вас спросить: вам не знаком человек по имени Оле Кристиансен?";
        link.l1.go = "agnes_1";
        break;

    case "agnes_1":
        dialog.text = "Повторите ещё раз, что вы сейчас сказали... Оле Кристиансен? Оле?!";
        link.l1 = "Ну да. Ещё его называют 'Белый Мальчик', из-за особенного светлого цвета его волос. Так вы его знаете?";
        link.l1.go = "agnes_2";
        break;

    case "agnes_2":
        dialog.text = "Знаю ли я его?! Это мой сын, пропавший без вести около полутора десятка лет назад! Вы знаете где он, минхер? Ну скажите же мне - где он, что с ним?!";
        link.l1 = "Тише, тише, госпожа, не волнуйтесь так. С ним всё хорошо. Он у меня на корабле. Так что ему достаточно просто сойти на берег и прийти сюда.";
        link.l1.go = "agnes_3";
        break;

    case "agnes_3":
        dialog.text = "Ох... видать, Господь услышал мои молитвы и послал мне утешение на старости лет! Вы не представляете, как я переживала, когда он исчез! Ведь это я, я была во всём виновата! Где вы его нашли? Он ведь не простой ребенок, он... ну, вы, наверное, понимаете, о чём я.";
        link.l1 = "Понимаю. Да, он особенный. И с годами, видимо, не изменился. Судя по всему, он так и остался в своём детстве. Нашёл я его на одном острове. Мы случайно встретились. Он попросил у меня белую бусинку... тьфу ты чёрт!.. уже привык на языке Оле их называть - жемчужину.";
        link.l1.go = "agnes_4";
        break;

    case "agnes_4":
        dialog.text = "Жемчужину? О, Боже! Ведь это из-за них мой мальчик исчез, из-за того злосчастного жемчужного ожерелья, пропади оно пропадом!";
        link.l1 = "Это правда, что Оле... ушёл из дома, из-за того, что порвал вашу нитку с жемчугом?.. Госпожа, тише, только не плачьте!";
        link.l1.go = "agnes_5";
        break;

    case "agnes_5":
        dialog.text = "Да, это правда. Оле порвал моё ожерелье, прямо на пирсе, и весь жемчуг упал в воду. Я так сильно ругалась на него, и муж покойный... наказал мальчика. И Оле исчез на следующий день. Вы не представляете, как я себя казнила за это!..";
        link.l1 = "Оле все эти годы собирал жемчужины. Он называет их белыми бусинками. Собирал их для вас, чтобы вернуть. И, наконец, собрал, и попросил отвезти его домой. Никаких примет, кроме того, что его мама, то есть вы, живете в доме с красной крышей - не было. Но всё-таки мне удалось найти вас.";
        link.l1.go = "agnes_6";
        break;

    case "agnes_6":
        dialog.text = "Он собирал жемчуг?! О, Господи! Как же я перед ним виновата, перед моим несчастным мальчиком! Я... а он - собирал жемчужины! Ох!";
        link.l1 = "Госпожа, я думаю, лучше всего будет, если я пошлю сейчас за вашим сыном. Он очень хотел вернуться к вам. Он сказал, что вы обрадуетесь, когда увидите жемчуг. Но я думаю, что радоваться вы будете вовсе не из-за этого.";
        link.l1.go = "agnes_7";
        break;

    case "agnes_7":
        dialog.text = "Минхер... будьте так добры. Приведите ко мне моего Оле. Я так хочу обнять его и попросить прощения...";
        link.l1 = "Конечно, госпожа. Сейчас его приведут.";
        link.l1.go = "agnes_8";
        break;

    case "agnes_8":
        DialogExit();
        SetLaunchFrameFormParam("Прошел час...", "", 0, 5);
        LaunchFrameForm();
        WaitDate("", 0, 0, 0, 1, 10); //крутим время
        RecalculateJumpTable();
        DoQuestFunctionDelay("LSC_OleGoHome", 5.0);
        break;

    case "agnes_9":
        dialog.text = "";
        link.l1 = "Ну вот, госпожа, ваш сын - Оле Кристиансен. Вы его узнаёте?..";
        link.l1.go = "agnes_10";
        break;

    case "agnes_10": // перекидываем pchar
        DialogExit();
        LAi_SetActorType(pchar);
        LAi_ActorTurnToCharacter(pchar, characterFromID("Agnes"));
        ChangeShowIntarface();
        SetMainCharacterIndex(GetCharacterIndex("Agnes"));
        PChar = GetMainCharacter();
        LAi_SetPlayerType(PChar);
        sld = characterFromId("Ole");
        sld.dialog.currentnode = "home";
        LAi_SetActorType(sld);
        LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

    case "agnes_11":
        dialog.text = "Минхер... Простите, я не спросила вашего имени... " + pchar.name + "?";
        link.l1 = "" + GetFullName(pchar) + ", госпожа. Капитан " + GetFullName(pchar) + ".";
        link.l1.go = "agnes_12";
        break;

    case "agnes_12":
        dialog.text = "Капитан, вы не представляете, как я вам благодарна за моего сына! За то, что помогли ему, не бросили его и привели домой. Вы вернули меня к жизни! Теперь я всё сделаю для своего мальчика, отдам ему всю любовь, которую он недополучил за эти годы.";
        link.l1 = "Я рад за вас, госпожа. И за Оле тоже. Он хороший парень, и помог мне в трудной ситуации. У него доброе сердце. Я лично знаю человека, которого он спас от неминуемой смерти.";
        link.l1.go = "agnes_13";
        break;

    case "agnes_13":
        dialog.text = "Минхер, я настаиваю, чтобы вы пришли ко мне завтра, или в любой удобный для вас день. Я хочу отблагодарить вас за своего сына. Просто сейчас мне немного... ну, вы понимаете.";
        link.l1 = "Я понимаю, госпожа.";
        link.l1.go = "agnes_14";
        break;

    case "agnes_14":
        dialog.text = "Приходите завтра. Я сумею достойно вознаградить вас за то добро, что вы сделали для моего сына и для меня.";
        link.l1 = "Хорошо. Я обязательно навещу вас!";
        link.l1.go = "agnes_15";
        break;

    case "agnes_15":
        DialogExit();
        bDisableCharacterMenu = false;      //лоченые интерфейсы
        chrDisableReloadToLocation = false; //открыть локацию
        LAi_SetOwnerType(npchar);
        LocatorReloadEnterDisable("Marigo_town", "houseSp2", true);
        NextDiag.CurrentNode = "agnes_16";
        pchar.quest.LSC_Ole_return.win_condition.l1 = "Timer";
        pchar.quest.LSC_Ole_return.win_condition.l1.date.hour = 8.0;
        pchar.quest.LSC_Ole_return.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
        pchar.quest.LSC_Ole_return.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
        pchar.quest.LSC_Ole_return.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
        pchar.quest.LSC_Ole_return.function = "LSC_OleAgnesRegard";
        // удаляем Оле из пассажиров
        sld = characterFromId("Ole");
        RemovePassenger(Pchar, sld);
        DeleteAttribute(pchar, "GenQuest.Ole");
        DoQuestReloadToLocation("Marigo_town", "reload", "houseSp2", "");
        break;

    case "agnes_16":
        dialog.text = "Ах, вот и вы, минхер " + GetFullName(pchar) + "! Проходите, располагайтесь...";
        link.l1 = "Спасибо! Как Оле?";
        link.l1.go = "agnes_17";
        break;

    case "agnes_17":
        dialog.text = "Ох, вы не представляете, что вы сделали! Какой бальзам вы пролили на исстрадавшееся материнское сердце... Даже не представляете! Я в неоплатном долгу перед вами, и буду молиться за ваше здравие до конца своих дней.";
        link.l1 = "Вы вгоняете меня в краску, сударыня...";
        link.l1.go = "agnes_18";
        break;

    case "agnes_18":
        dialog.text = "Я всегда знала, что скромность - отличительная черта благородных людей... Я приготовила вам подарки в благодарность за ваш поступок. Да, да! И не смейте отказываться! Вот, берите... Во-первых, вот этот сундучок с дублонами. Во-вторых - вот этот заговорённый амулет, под названием 'Скарабей'\nОн принадлежал моему мужу, и он был бы рад узнать, что его ценность достанется не кому-нибудь, а благородному капитану, вернувшему мне сына. Мой муж был плотником, и никогда не расставался с этим перстнем. Как он говорил - 'работа спорится вдвое быстрей, если на палец надет Скарабей'\nНадеюсь, этот перстень теперь верой и правдой послужит вам, как служил когда-то моему покойному супругу. Вы достойны владеть им по праву!.. И в-третьих - мой портняжный набор. Очень хороший набор! С его помощью вы всегда сможете что угодно и скроить, и сшить.";
        link.l1 = "О! Это действительно очень ценные подарки для капитана! Благодарю, госпожа.";
        link.l1.go = "agnes_19";
        break;

    case "agnes_19":
        PlaySound("interface\important_item.wav");
        Log_Info("Вы получили сундук с дублонами");
        Log_Info("Вы получили оберег 'Скарабей'");
        Log_Info("Вы получили портняжный набор");
        GiveItem2Character(pchar, "chest");
        GiveItem2Character(pchar, "talisman7");
        GiveItem2Character(pchar, "tailor_tool");
        dialog.text = "И я хочу, чтобы вы знали - двери этого дома всегда открыты для вас, в любое время дня и ночи. Вы всегда найдёте здесь тарелку горячей вкусной еды, бутылку доброго вина и всё, что я ещё только смогу для вас сделать.";
        link.l1 = "Спасибо за тёплые слова, госпожа. Буду рад зайти к вам в гости, когда в очередной раз посещу Синт-Маартен.";
        link.l1.go = "agnes_20";
        break;

    case "agnes_20":
        dialog.text = "Обязательно заходите!";
        link.l1 = "А теперь мне пора. Позвольте откланяться. До свидания и удачи вам!";
        link.l1.go = "agnes_21";
        break;

    case "agnes_21":
        DialogExit();
        NextDiag.CurrentNode = "agnes_22";
        AddCharacterExpToSkill(pchar, "Fortune", 350);
        AddCharacterExpToSkill(pchar, "Leadership", 500);
        ChangeCharacterComplexReputation(pchar, "nobility", 10);
        ChangeCharacterComplexReputation(pchar, "authority", 4);
        break;

    case "agnes_22":
        dialog.text = "Ах, капитан " + GetFullName(pchar) + "! Как я рада вас видеть! Проходите, присаживайтесь, сейчас я вам чего-нибудь налью...";
        link.l1 = "Спасибо! Я зашёл просто с вами поздороваться, узнать, как дела. Рад, что у вас и Оле всё хорошо.";
        link.l1.go = "exit";
        NextDiag.TempNode = "agnes_22";
        break;

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

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
    }
}