// Джон Мердок, он же Йохан ван Мерден, соратник Роденбурга
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    string sTemp;
    int iTemp;
    bool bOk;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
    case "First time":
        if (!CheckAttribute(pchar, "questTemp.HWIC.Self") && LAi_grp_playeralarm > 0)
        {
            dialog.text = "Не думаю, мистер, что вы выбрали удачное время для бесед. За вами гоняется гарнизон. Шли бы вы отсюда...";
            link.l1 = "Не переживай, долго я у тебя сидеть не буду.";
            link.l1.go = "exit";
            break;
        }
        // продажа алхимического набора, если провалил гамбит
        if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && !CheckAttribute(npchar, "quest.alchemy"))
        {
            bOk = (findsubstr(pchar.questTemp.HWIC.Detector, "_fail", 0) != -1) || (pchar.questTemp.HWIC.Detector == "eng_win_half");
            if (bOk)
            {
                dialog.text = "Приветствую, капитан. Не заинтересует ли вас одно занятное предложение?";
                link.l1 = "Я всегда был любознательным, так что выкладывайте - что за предложение?";
                link.l1.go = "alchemy";
                break;
            }
        }
        // Страж Истины
        if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok1")
        {
            dialog.text = "Добрый день. Рад видеть вас в моей аптеке. У меня есть лекарства от большинства хворей и недугов. Что вам предложить?";
            link.l1 = "Послушай, Джон, тут ходят слухи, что у тебя на втором этаже живёт кто-то...";
            link.l1.go = "guardoftruth";
            break;
        }
        //-----------------------------------------за Голландию------------------------------------------------
        if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
        {
            if (pchar.location.from_sea == "SentJons_town" && pchar.questTemp.HWIC.Holl == "toAntigua")
            {
                dialog.text = "Добрый день. Рад видеть вас в моей аптеке. У меня есть лекарства от большинства хворей и недугов. Что вам предложить?";
                link.l1 = "Здравствуйте, мистер Мердок. Я пришёл от Лукаса Роденбурга. Он командировал меня к вам по вопросу о Ричарде Флитвуде.";
                link.l1.go = "Knippel_exit";
                break;
            }
            if (pchar.questTemp.HWIC.Holl == "toAntigua")
            {
                dialog.text = "Добрый день. По какому вопросу вы пришли? Микстура от кашля, или порошок от поноса?";
                link.l1 = "Здравствуйте, мистер Мердок. Я пришёл от Лукаса Роденбурга. Он командировал меня к вам по вопросу о Ричарде Флитвуде.";
                link.l1.go = "Knippel";
                break;
            }
            if (pchar.questTemp.HWIC.Holl == "KillMerdok")
            {
                dialog.text = "Ага, вот и заявился наёмник Роденбурга... Эркюль, Лонгвэй! Сюда! К бою!";
                link.l1 = "А-а-ть!";
                link.l1.go = "Merdok_fight";
                break;
            }
            dialog.text = "Добрый день. Рад видеть вас в моей аптеке. У меня есть лекарства от большинства хворей и недугов. Что вам предложить?";
            link.l1 = "Пока что ничего, спасибо. Со здоровьем у меня всё в порядке.";
            link.l1.go = "exit";
            break;
        }
        //----------------------------------------------за Англию---------------------------------------------------
        if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "MerdokMeeteng")
        {
            dialog.text = "Привет, незваный гость. Ты не скрываешь лицо под маской и не торопишься напасть. Из чего я делаю вывод, что тебе нужно от бедного аптекаря что-то другое. Уж не микстура ли от поноса?";
            link.l1 = "Здравствуй и ты, Йохан ван Мерден. Я пришёл передать тебе привет от Эркюля Тонзага. Вижу, тебе знакомо это имя.";
            link.l1.go = "Merdok_talk";
            break;
        }
        //--------------------------------------------против всех--------------------------------------------------
        if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
        {
            if (pchar.questTemp.HWIC.Self == "HuntFleetwood")
            {
                dialog.text = "А, вот и ты... Ну как, встретился с Эркюлем?";
                link.l1 = "Да. Мы побеседовали и пришли к одному соглашению. Джон, я намерен помочь Эркюлю, и у меня к тебе есть несколько вопросов о Ричарде Флитвуде.";
                link.l1.go = "About_Fleetwood";
                break;
            }
            if (GetQuestPastDayParam("questTemp.Wait_Fleetwood") > 6 && pchar.questTemp.HWIC.Self == "WaitFleetwood")
            {
                dialog.text = "Приветствую! Рад тебя видеть, " + pchar.name + "!";
                link.l1 = "Здравствуй, Джон. Ты узнал что-нибудь о Флитвуде?";
                link.l1.go = "About_Fleetwood_9";
                pchar.quest.Wait_FleetwoodOver.over = "yes"; //снять таймер
                break;
            }
            if (pchar.questTemp.HWIC.Self == "HWICSelf_fail")
            {
                dialog.text = "А, вот и ты. Я когда тебе сказал прийти? В общем, ничего хорошего я тебе не скажу. Чарли Книппель съездил в Виллемстад, привёз оттуда одну девушку Ричарду, и они со дня на день отбывают с военной эскадрой в Англию. Так что.. до него тебе уже не добраться.";
                link.l1 = "Ясно. Эх, увлекся я другими делами и совсем про Ричарда позабыл. Ладно, бывай.";
                link.l1.go = "About_Fleetwood_17";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "AbigileOnShip")
            {
                dialog.text = "С возвращением, " + pchar.name + "! Что расскажешь? О Флитвуде никаких новостей нет, Чарли Книппель тоже ещё не вернулся с Кюрасао...";
                link.l1 = "И не вернется. Ни он, ни его бригантина.";
                link.l1.go = "Abigile";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "AbigileInHouse")
            {
                dialog.text = "А-а, какие у нас гости! Здравствуй, Чарли! Добрый день, мисс!";
                link.l1 = "Добрый день, Джон! Позволь тебе представить нашу дорогую гостью, невесту Ричарда - очаровательную Абигайль Шнеур.";
                link.l1.go = "Abigile_7_1";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "AbigileInRoom")
            {
                dialog.text = "Говори потише... Что ты намерен делать дальше?";
                link.l1 = "Дальше? Я бы отдохнул, но времени, к сожалению, нет. Дальше я намерен выманить Флитвуда из его норы, куда он запрятался, на свет Божий, и завершить дело, начатое Эркюлем.";
                link.l1.go = "Abigile_9";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "LetterToFleetwood")
            {
                dialog.text = "Всё, написал? Дай-ка гляну... У-ух... да, ты определенно жуткий тип, дружище! 'Если посланник не выйдет из дома через полчаса, или я увижу за ним слежку - через день ты получишь в коробке палец и ухо твоей любимой. Если же посланник вернётся с пустыми руками - то я отрежу Абигайль голову и пришлю тебе.' Ха-ха-ха! У тебя определенно талант!";
                link.l1 = "Я блефую, Джон. Я не стал бы убивать девушку в любом случае... Разве что только пришлось бы пожертвовать её пальчиком, но не более.";
                link.l1.go = "Abigile_15";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "FleetwoodAgree")
            {
                dialog.text = "Ну, как всё прошло? Вижу по горящим глазам, что тебе всё удалось!";
                link.l1 = "Да. Флитвуд написал ответ и принял мои условия. Ловушка захлопнулась. Теперь дело за малым.";
                link.l1.go = "Abigile_23";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "FleetwoodDied")
            {
                dialog.text = "А-а, с возвращением, мой друг! Ну, что расскажешь?";
                link.l1 = "Флитвуд мертв. Всё прошло по плану - он явился на остров, а я организовал засаду в бухте. Правда, он тоже оказался не лыком шит... Ух и бойня была! Но я жив, а он навсегда останется в этой бухте.";
                link.l1.go = "Abigile_27";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "MeetTonzag")
            {
                dialog.text = "" + pchar.name + ", у меня к тебе серьёзное предложение. Дело, о котором я поведу речь, будет очень опасным, но, видя как ты разделался с Флитвудом, уверен, что ты с этим справишься. У тебя действительно талант к подобного рода делам.";
                link.l1 = "Не скрою, я польщён, Джон. Продолжай.";
                link.l1.go = "Lucas";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "SeekAbiIsland")
            {
                dialog.text = "С возвращением, " + pchar.name + "! Порадуешь меня новостями?";
                link.l1 = "Теперь ты можешь спать спокойно, Джон. Лукас тебе более не угрожает. Он арестован и посажен в тюрьму, а в ближайшее время его отправят в Нидерланды, где будут судить за попытку захвата власти, покушение на убийство и за прочие грехи.";
                link.l1.go = "Lucas_10";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "VanbergDestroyed")
            {
                dialog.text = "Рад тебя видеть, " + pchar.name + "! Ты жив - это хороший знак. Есть новости?";
                link.l1 = "Да. С ван Бергом покончено. Как ты и сказал - он выследил меня и напал в самый неподходящий момент. Я с ним справился, правда, это было очень и очень нелегко.";
                link.l1.go = "Final";
                break;
            }
            dialog.text = "Ты что-то ещё хотел спросить?";
            link.l1 = "Нет, Джон, ничего. Я уже ухожу.";
            link.l1.go = "exit";
            break;
        }
        dialog.text = "Добрый день. Рад видеть вас в моей аптеке. У меня есть лекарства от большинства хворей и недугов. Что вам предложить?";
        link.l1 = "Пока что ничего, спасибо. Со здоровьем у меня всё в порядке.";
        link.l1.go = "exit";
        NextDiag.TempNode = "First time";
        break;

        //--------------------------------------------за Голландию-----------------------------------------------------
    case "Knippel_exit":
        dialog.text = "Я не понимаю о чём вы говорите, сэр. Какой Лукас Роденбург? Я не якшаюсь с голландцами, вы, вероятно, что-то напутали.";
        link.l1 = "Но как же! Минхер Роденбург отправил меня к вам...";
        link.l1.go = "Knippel_exit_1";
        break;

    case "Knippel_exit_1":
        dialog.text = "Я вам ещё раз говорю - я не знаю никакого минхера Роденбурга. У меня нет в друзьях или знакомых голландцев. Если у вас всё - покиньте мой дом и не мешайте мне работать.";
        link.l1 = "Ну дела...";
        link.l1.go = "exit";
        break;

    case "Knippel":
        dialog.text = "Так-так... Вы от минхера Роденбурга? Хорошо. Я вас слушаю.";
        link.l1 = "Мне необходимо организовать встречу с капитаном Флитвудом... в безлюдном месте. Я позаимствовал у Якоба ван Берга его знаменитый 'Мираж', который так нужен мистеру Флитвуду, и мне хотелось бы... невзначай довести до его сведения, что 'Мираж' в ближайшее время будет у берегов Доминики.";
        link.l1.go = "Knippel_1";
        break;

    case "Knippel_1":
        dialog.text = "Якоб отдал вам свой корабль? Презанятно... Как я понимаю, теперь вам нужен человек, который смог бы поведать мистеру Флитвуду, что 'Мираж' крейсирует у берегов Доминики, ибо сами вы, хе-хе, Ричарду об этом сказать не можете, по определенным причинам...";
        link.l1 = "Именно так. Минхер Роденбург рекомендовал по этому вопросу обратиться именно к вам.";
        link.l1.go = "Knippel_2";
        break;

    case "Knippel_2":
        dialog.text = "В таком случае вам нужен Чарли Книппель. Это большой друг мистера Флитвуда и его наушник. Поговорите с ним, и в разговоре упомяните всё, что хотите донести до Ричарда. Только будьте осторожны - Книппель хоть и простак по натуре, но далеко не дурак\nНайти его вы сможете в небольшом домике, больше похожем на рыбацкую хижину, недалеко от моря. Он должен быть там.";
        link.l1 = "Я всё понял. Спасибо, мистер Мердок. До свидания!";
        link.l1.go = "Knippel_3";
        break;

    case "Knippel_3":
        DialogExit();
        pchar.questTemp.HWIC.Holl = "toKnippel";
        AddQuestRecord("Holl_Gambit", "1-16");
        break;

    case "Merdok_fight":
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешим драться
        LAi_SetWarriorType(npchar);
        LAi_group_MoveCharacter(npchar, "EnemyFight");
        sld = characterFromId("Tonzag");
        PlaySound("VOICE\Russian\hambit\Ercule Tongzag-04.wav");
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        //а вот и китаец нарисовался
        sld = characterFromId("Longway");
        LAi_SetWarriorType(sld);
        FantomMakeCoolFighter(sld, 18, 40, 40, "blade_08", "pistol1", "bullet", 70);
        if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayEnemy")) //враг
        {
            ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
            LAi_group_MoveCharacter(sld, "EnemyFight");
            PlaySound("VOICE\Russian\hambit\Longway-02.wav");
        }
        if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayFriend")) //друг
        {
            LAi_warrior_DialogEnable(sld, true);
            sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
            sld.dialog.currentnode = "Longway_hire";
            ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
            PlaySound("VOICE\Russian\hambit\Longway-02.wav");
        }
        if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayNeutral"))
            sld.lifeday = 0; //нейтрал - просто нет
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattle");
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

        //-------------------------------------------------за Англию-----------------------------------------------------
    case "Merdok_talk":
        dialog.text = "Вот как? А я полагал, что бедняга Гастон уже давно в аду.";
        link.l1 = "Возможно. Я нашёл его голову в сундуке старого еврея на острове. Но он сумел передать тебе привет и сказал, что у нас с некоторых пор есть общий враг. А именно господин Роденбург, который не успокоится, пока ты не составишь Тонзагу компанию. Тонзаг сообщил, что у тебя есть важные для Лукаса бумаги, которые могли бы выманить его с Кюрасао.";
        link.l1.go = "Merdok_talk_1";
        break;

    case "Merdok_talk_1":
        dialog.text = "Он прав. Это мой архив, который не даёт Роденбургу покоя. Похоже, именно из-за него он ещё здесь. Дело в том, что ему обещано тёплое местечко в Совете директоров Компании. Если сведения из архива, в котором есть много интересного о прошлом и настоящем Лукаса, получат широкую огласку, его карьера будет закончена. Замена петли на плаху – это самая мягкая участь, которая ждала бы его в этом случае.";
        link.l1 = "Отдай мне свой архив и я позабочусь о нашем недруге.";
        link.l1.go = "Merdok_talk_2";
        break;

    case "Merdok_talk_2":
        dialog.text = "Я всё ещё жив только потому, что он у меня. Откуда мне знать, что ты не переметнулся к Лукасу?";
        link.l1 = "Тебе придётся поверить мне на слово, или умереть.";
        link.l1.go = "Merdok_talk_3";
        break;

    case "Merdok_talk_3":
        PlaySound("VOICE\Russian\hambit\John Mardock-07.wav");
        dialog.text = "Возможно я действительно скоро умру, но ты сдохнешь прямо сейчас! Лонгвэй, сюда!";
        link.l1 = "Ах, и китаец тоже тут...";
        link.l1.go = "Merdok_fightEng";
        break;

    case "Merdok_fightEng":
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешим драться
        LAi_SetWarriorType(npchar);
        LAi_group_MoveCharacter(npchar, "EnemyFight");
        sld = characterFromId("Longway");
        FantomMakeCoolFighter(sld, 20, 50, 50, "blade_08", "pistol1", "bullet", 80);
        LAi_SetWarriorType(sld);
        ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
        PlaySound("VOICE\Russian\hambit\Longway-02.wav");
        LAi_group_MoveCharacter(sld, "EnemyFight");
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattleEng");
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

        //----------------------------------------против всех-------------------------------------------------------
    case "MC_InHouse":
        PlaySound("VOICE\Russian\hambit\John Mardock-02.wav");
        dialog.text = "Ну, наконец вы встали на ноги. Я уже думал, это никогда не произойдет.";
        link.l1 = "Кхм... Добрый день. Кто вы? И, собственно, где я? И как сюда попал?";
        link.l1.go = "MC_InHouse_1";
        break;

    case "MC_InHouse_1":
        dialog.text = "Тише-тише, не надо задавать столько вопросов сразу, вам вредно волноваться. Меня зовут Джон Мердок, я аптекарь города Сент-Джонс. Вы потеряли сознание в стычке с охраной Флитвуда. Надо сказать, здорово вам всыпали... А притащил вас сюда, в мою аптеку, Эркюль, ну, а я залечил ваши раны своими снадобьями.";
        link.l1 = "Эркюль? Кто это? Это не тот ли человек, что пришёл мне на помощь на улице?";
        link.l1.go = "MC_InHouse_2";
        break;

    case "MC_InHouse_2":
        dialog.text = "Да, именно он. Кстати, он желает побеседовать с вами. Вам нужно будет встретиться с ним в городе, пройдя ночью через подземный ход, который начинается за дверью на первом этаже моего дома. Сейчас соваться на улицу вам нежелательно - кое-кто из команды Флитвуда запомнил вас и сможет опознать.";
        link.l1 = "Понятно... А где мой корабль?";
        link.l1.go = "MC_InHouse_3";
        break;

    case "MC_InHouse_3":
        if (pchar.Ship.Type == SHIP_NOTUSED)
        {
            dialog.text = "Ваш корабль был арестован, а команда разбежалась, кто куда. Увы.";
            link.l1 = "Эх, вот досада...";
        }
        else
        {
            dialog.text = "Стоит в порту, где и стоял.";
            link.l1 = "Это хорошо. А то я забеспокоился...";
        }
        link.l1.go = "MC_InHouse_4";
        break;

    case "MC_InHouse_4":
        dialog.text = "Вам надо встретиться с Эркюлем. Ночью выходите через подземелье в город. Он сам к вам подойдёт. А пока - отдыхайте, а мне пора вернуться к работе.";
        link.l1 = "Хорошо, Джон. И... спасибо за помощь и за лечение!";
        link.l1.go = "MC_InHouse_5";
        break;

    case "MC_InHouse_5":
        NextDiag.CurrentNode = "First time";
        DialogExit();
        npchar.greeting = "merdok_2";
        AddQuestRecord("Holl_Gambit", "3-12");
        pchar.questTemp.HWIC.Self = "MainBegin"; //новый флаг квеста
        sld = characterFromId("Bridgetown_tavernkeeper");
        sld.model = "barmen_3";
        sld.greeting = "barmen_1";
        sld.name = "Гарри";
        sld.lastname = "Флетчер";                                              //перерисуем бармена Бриджтауна
        LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", true);        //закрыть выход из аптеки через дверь
        LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);       //открыть подземелье из дома
        LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false); //открыть дом из подземелья
        pchar.quest.Tonzag_Meeting.win_condition.l1 = "location";
        pchar.quest.Tonzag_Meeting.win_condition.l1.location = "SentJons_town";
        pchar.quest.Tonzag_Meeting.win_condition.l2 = "Night";
        pchar.quest.Tonzag_Meeting.function = "TonzagMeeting";
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);
        break;

    case "About_Fleetwood":
        dialog.text = "О Флитвуде? Что ты хочешь о нём узнать?";
        link.l1 = "Всё. Абсолютно всё, что тебе известно. Сдаётся мне, что для тебя не секрет, для чего Эркюль прибыл на Антигуа. Я тоже в курсе событий, и действую на стороне Эркюля.";
        link.l1.go = "About_Fleetwood_1";
        break;

    case "About_Fleetwood_1":
        dialog.text = "Что я могу сказать о Флитвуде... Хороший боец, опытный моряк. Имеет в своём распоряжении бриг по имени 'Валькирия' - отличное судно, хочу отметить - с командой отборных морпехов. Враждует с Голландией в общем и с Голландской Вест-Индской Компанией в частности. Ограбил несчётное количество голландских торговых кораблей. Губернатор Кюрасао установил за его голову просто рекордную цену.";
        link.l1 = "Гм... Несколько необычно для офицера английского королевского флота...";
        link.l1.go = "About_Fleetwood_2";
        break;

    case "About_Fleetwood_2":
        dialog.text = "Да, это так. Он ходит по грани. Власти официально не признают его действий и открещиваются, но закулисно поощряют его разбои. У меня есть основание полагать, что он как-то связан с английской военной разведкой, а с этими ребятами шутки плохи.";
        link.l1 = "Серьезный господин... Это всё? Эркюль говорил про какого-то его подручного, Чарли... как его... Картечь, или Ядро?";
        link.l1.go = "About_Fleetwood_3";
        break;

    case "About_Fleetwood_3":
        dialog.text = "Книппеля? Да, есть такой. Чарли Книппель, отставной военный моряк, служил в английском флоте канониром. В настоящее время ведёт тихую жизнь на берегу. Глаза и уши Флитвуда в Сент-Джонсе, так что будь с ним осторожен и не вздумай расспрашивать его о Ричарде - вмиг окажешься в тюрьме.";
        link.l1 = "Понятно. Что-нибудь ещё интересное про Флитвуда расскажешь?";
        link.l1.go = "About_Fleetwood_4";
        break;

    case "About_Fleetwood_4":
        dialog.text = "Кумир всего женского населения Антигуа от шестнадцати до шестидесяти лет. Больше вроде мне и нечего о нем сказать... Ну, а что с ним сейчас произошло - думаю, знаешь. Лежит дома и зализывает раны.";
        link.l1 = "Послушай, Джон, может, у него есть какие-то особенности, слабые места...";
        link.l1.go = "About_Fleetwood_5";
        break;

    case "About_Fleetwood_5":
        dialog.text = "Что ты имеешь в виду?";
        link.l1 = "Ну, может, он любит играть в карты, или выпивает сильно, или по борделям ходит. Он женат?";
        link.l1.go = "About_Fleetwood_6";
        break;

    case "About_Fleetwood_6":
        dialog.text = "Холост. А что касается всего остального, что ты перечислил - этого за ним не водится.";
        link.l1 = "Понятно. Но может, что-то особенное всё-таки есть? Должно же быть и у него уязвимое место!";
        link.l1.go = "About_Fleetwood_7";
        break;

    case "About_Fleetwood_7":
        dialog.text = "Не знаю... Послушай, давай сделаем так: навести меня через недельку, а я за это время попробую собрать какую-нибудь информацию, касающуюся Флитвуда. Договорились?";
        link.l1 = "Договорились. Спасибо тебе, Джон! Буду через неделю.";
        link.l1.go = "About_Fleetwood_8";
        break;

    case "About_Fleetwood_8":
        DialogExit();
        pchar.questTemp.HWIC.Self = "WaitFleetwood";
        SaveCurrentQuestDateParam("questTemp.Wait_Fleetwood");
        SetFunctionTimerCondition("Wait_FleetwoodOver", 0, 0, 12, false); //чтобы не опаздывал
        LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", false);  //открыть выход из аптеки
        AddQuestRecord("Holl_Gambit", "3-14");
        break;

    case "About_Fleetwood_9":
        dialog.text = "Да, но к сожалению, немного, да и навряд ли тебе это пригодится.";
        link.l1 = "Рассказывай! Я весь внимание! Для меня важна каждая мелочь, лишь бы она касалась Флитвуда.";
        link.l1.go = "About_Fleetwood_10";
        break;

    case "About_Fleetwood_10":
        dialog.text = "Не так давно Ричард снял с неизвестного острова двух еврейских беженцев - отца и дочь, плывших в Виллемстад. Корабль, на котором они путешествовали, был потоплен неким пиратом. Флитвуд, с риском быть обнаруженным, отвёз их на Кюрасао. С этого момента прошло уже несколько месяцев. И теперь он посылает в Виллемстад своего верного пса Чарли Книппеля...";
        link.l1 = "Хм... И какая тут связь?";
        link.l1.go = "About_Fleetwood_11";
        break;

    case "About_Fleetwood_11":
        dialog.text = "Мне удалось узнать, что Чарли получил приказ привезти на Антигуа из Виллемстада некую девицу... еврейку по имени Абигайль Шнеур. Да-да, ту самую, с острова. Видать, за время путешествия до Виллемстада бравый Ричард влюбился в неё, раз посылает за ней в самое логово врагов своего наушника\nЭто всё. Не знаю, для чего тебе может пригодиться эта информация, но другой всё равно нет.";
        link.l1 = "Хм... Джон, но это же просто отлично! Ха-ха-ха! Значит, наш вояка влюблён... ну что же! Лучшего и придумать было нельзя. Спасибо! Джон, когда Книппель отправляется на Кюрасао?";
        link.l1.go = "About_Fleetwood_12";
        break;

    case "About_Fleetwood_12":
        dialog.text = "Он уже отправился. Вчера.";
        link.l1 = "Аргх! Какой у него корабль?";
        link.l1.go = "About_Fleetwood_13";
        break;

    case "About_Fleetwood_13":
        dialog.text = "Я знал, что ты это спросишь. Бригантина королевского флота Англии. Название - 'Зеекалф'.";
        link.l1 = "'Зеекалф'? А с каких это пор английские корабли называют такими именами? Стой, я понял!";
        link.l1.go = "About_Fleetwood_14";
        break;

    case "About_Fleetwood_14":
        dialog.text = "Ты быстро соображаешь... Её настоящее название - 'Ройял Мэри', но на этот рейс она стала 'Зеекалф'. И конечно же, будет идти под голландским флагом.";
        link.l1 = "Ты оказал мне неоценимую помощь, Джон. Я отправляюсь в путь. Скоро вернусь, и... мне понадобится твоя комната на втором этаже, где ты меня лечил.";
        link.l1.go = "About_Fleetwood_15";
        break;

    case "About_Fleetwood_15":
        dialog.text = "Что ты задумал?";
        link.l1 = "Я вернусь, и всё узнаешь. Пожелай мне удачи, Джон! Пока.";
        link.l1.go = "About_Fleetwood_16";
        break;

    case "About_Fleetwood_16":
        DialogExit();
        AddQuestRecord("Holl_Gambit", "3-16");
        pchar.questTemp.HWIC.Self = "HuntKnippel";
        SetFunctionTimerCondition("HuntKnippelOver", 0, 0, 10, false);
        pchar.quest.Hunt_Knippel.win_condition.l1 = "location";
        pchar.quest.Hunt_Knippel.win_condition.l1.location = "Curacao";
        pchar.quest.Hunt_Knippel.function = "CreateKnippelShip";
        LocatorReloadEnterDisable("SentJons_town", "houseH1", true); //закрыть хижину Чарли
        break;

    case "About_Fleetwood_17":
        DialogExit();
        AddQuestRecord("Holl_Gambit", "3-15");
        pchar.questTemp.HWIC.Self = "end";
        pchar.questTemp.HWIC.Detector = "self_fail";
        CloseQuestHeader("Holl_Gambit");
        break;

    case "Abigile":
        dialog.text = "Вот как? И откуда такая уверенность?";
        link.l1 = "Потому что Чарли на дне, кормит рыб. Я абордировал 'Зеекалф', а Книппеля собственноручно отправил к праотцам. Конечно, предварительно допросив с пристрастием... При нём оказалось письмо, которое позволило мне выдать себя за Книппеля в разговоре с Абигайль, ну, той девушкой, зазнобой нашего бравого Ричарда...";
        link.l1.go = "Abigile_1";
        break;

    case "Abigile_1":
        dialog.text = "Гхм... Лихо. Ты хочешь сказать что...";
        link.l1 = "Да. Я привёз её на Антигуа. Сейчас она у меня на корабле. Теперь у меня есть козырный туз в игре против Флитвуда! Он на многое пойдёт ради неё...";
        link.l1.go = "Abigile_2";
        break;

    case "Abigile_2":
        dialog.text = "Ты уверен? Может, всё не так радужно, как ты думаешь?";
        link.l1 = "Уверен. Из письма мне стало ясно, что папаша Абигайль противится её союзу с Ричардом из-за денег. Так вот, он решил заплатить её папашке - презанятный тип, скажу тебе - целых 200 000 песо! Скажи, много ли девушек на свете стоят таких денег?";
        link.l1.go = "Abigile_3";
        break;

    case "Abigile_3":
        dialog.text = "Хех! Я таких точно не встречал. " + pchar.name + ", ты настоящий злой гений. Каков твой дальнейший план?";
        link.l1 = "Я приведу девчонку сюда и мы поместим её в твою комнату. Ей я скажу, что Ричард ушёл в плавание и ещё не вернулся, так что придётся недельку погостить у нас. Она же до сих пор думает, что я Чарли Книппель...";
        link.l1.go = "Abigile_4";
        break;

    case "Abigile_4":
        dialog.text = "Занятно. Значит, ты решил содержать пленницу у меня дома? Гм...";
        link.l1 = "Джон, она голландская подданая. А это значит, что в Сент-Джонсе она никто и зовут её никак. Она даже пикнуть не посмеет, если что. Денег у неё нет ни гроша. Да и вообще, это ненадолго. С её помощью я выманю Флитвуда, а потом она будет уже не нужна.";
        link.l1.go = "Abigile_5";
        break;

    case "Abigile_5":
        dialog.text = "Надеюсь, ты не собираешься потом поступить с ней так же, как с Книппелем?";
        link.l1 = "Нет, конечно. Я хоть и злой гений, но с красивыми девушками не воюю. Да и с некрасивыми тоже. Если будет вести себя примерно, когда всё закончится, я отвезу её в Виллемстад к отцу.";
        link.l1.go = "Abigile_6";
        break;

    case "Abigile_6":
        dialog.text = "М-м... Значит, мне придётся за ней присматривать?";
        link.l1 = "Джон, я не настаиваю. Если ты категорически против - значит, она останется у меня на корабле. Но только тогда в целях безопасности придётся надеть на неё кандалы и бросить в трюм к крысам, а мне этого делать совсем не хочется.";
        link.l1.go = "Abigile_7";
        break;

    case "Abigile_7":
        dialog.text = "Да нет, вовсе не против. Конечно, приводи. Помочь тебе бороться против Флитвуда - я просто обязан. Приводи её, я подготовлю комнату.";
        link.l1 = "Спасибо, Джон. Я знал, что на тебя можно рассчитывать.";
        link.l1.go = "exit";
        pchar.questTemp.HWIC.Self = "AbigileInCabin";
        DoQuestCheckDelay("SetAbigileToCabin", 1.0); // fix 180812
        AddQuestRecord("Holl_Gambit", "3-24");
        //поставим табурет
        sld = ItemsFromID("lcheer");
        sld.shown = true;
        sld.startLocation = "SentJons_HouseF3";
        sld.startLocator = "goto2";
        break;

    case "Abigile_7_1":
        dialog.text = "О! Очень приятно. Рад приветствовать столь значительную и... столь прекрасную особу. Мисс, пожалуйста, поднимайтесь на второй этаж в комнату - там для вас уже накрыт ужин и расстелена постель. Уверен, вы хотите хорошенько выспаться после долгого путешествия.";
        link.l1 = "Да. Абигайль, конечно, устала после перехода из Виллемстада.";
        link.l1.go = "Abigile_8";
        break;

    case "Abigile_8":
        DialogExit();
        sld = characterFromId("Abigile");
        sld.dialog.currentnode = "Abigile_kidnapping_11";
        LAi_SetActorType(sld);
        LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

    case "Abigile_9":
        dialog.text = "У тебя уже есть план?";
        link.l1 = "Есть. Нужно написать угрожающее письмо Ричарду с требованием выкупа за Абигайль. Назначить встречу где-нибудь на необитаемом острове, например, на Терксе. А если не придёт - мол, вышлем ему его девочку по кускам.";
        link.l1.go = "Abigile_10";
        break;

    case "Abigile_10":
        dialog.text = "А к чему такие сложности с необитаемым островом?";
        link.l1 = "Так безопаснее. Я же не собираюсь тащить туда Абигайль и разменивать её на деньги. Мне нужен сам Флитвуд. На Антигуа он наверняка организует засаду, а на Терксе у него преимуществ не будет.";
        link.l1.go = "Abigile_11";
        break;

    case "Abigile_11":
        dialog.text = "Логично. Кто будет передавать письмо? Это очень опасный момент.";
        link.l1 = "Какой-нибудь посторонний человек. Например, пьяница из таверны. За пару монет на выпивку они и не такое сделают. А если Ричард убьет его в порыве гнева, ну... пришлём другого. Только вместе со вторым письмом придётся передать и какой-нибудь из пальчиков Аби. Отрезанный, конечно.";
        link.l1.go = "Abigile_12";
        break;

    case "Abigile_12":
        dialog.text = "" + pchar.name + "...";
        link.l1 = "Джон, не беспокойся. Я уверен, до этого дело не дойдёт. В общем, надо найти такого пьянчужку, а письмо я составлю прямо сейчас. У тебя есть бумага и чернила?";
        link.l1.go = "Abigile_13";
        break;

    case "Abigile_13":
        dialog.text = "Есть. И пьяница тоже есть. Рекомендую Джека Гаррисона. Каждый вечер он проводит время в таверне, накачиваясь ромом. Ты легко его найдёшь.";
        link.l1 = "Отлично! Давай письменные принадлежности - буду сочинять грозное послание Ричарду...";
        link.l1.go = "Abigile_14";
        break;

    case "Abigile_14":
        DialogExit();
        LAi_SetActorType(pchar);
        LAi_ActorGoToLocator(pchar, "goto", "goto2", "MC_writeLetter", -1);
        break;

    case "Abigile_15":
        dialog.text = "Когда ты намерен отдать письмо? Ты и впрямь будешь следить за передачей?";
        link.l1 = "Конечно. Ричард далеко не дурак, и на самом деле может установить слежку за посланцем. Хотя вряд ли. Во всякoм случае, я на это надеюсь. Я бы не хотел причинять боль этой милой девушке. Ну, пора разыскать твоего пьяницу. Джека... как его там?";
        link.l1.go = "Abigile_20";
        break;

    case "Abigile_20":
        dialog.text = "Джек Гаррисон его зовут. Обычно он в таверне вечером бывает. Будь острожен!";
        link.l1 = "Всё будет хорошо. Жди меня.";
        link.l1.go = "Abigile_22";
        break;

    case "Abigile_22":
        DialogExit();
        LAi_SetOwnerType(npchar);
        pchar.questTemp.HWIC.Self = "LetterToDrunkardGo";
        AddDialogExitQuestFunction("CreateDrunckardInTavern");
        AddQuestRecord("Holl_Gambit", "3-25");
        break;

    case "Abigile_23":
        dialog.text = "Ну, я бы так не сказал. Флитвуд хитёр и опасен. К тому же он опытный фехтовальщик и отличный моряк. Лёгкой добычей он никак не будет.";
        link.l1 = "А я и не ищу лёгких путей в жизни... Ладно, Джон, мне пора выдвигаться в путь. Кстати, ты говорил, что у нашего бравого вояки хороший кораблик?";
        link.l1.go = "Abigile_24";
        break;

    case "Abigile_24":
        dialog.text = "У него лучший бриг из всех, какие я когда-либо видел. А видел я немало, поверь мне.";
        link.l1 = "Вот и славно... Люблю хорошие корабли. Ну, я поднимаю якоря!";
        link.l1.go = "Abigile_26";
        break;

    case "Abigile_26":
        DialogExit();
        pchar.questTemp.HWIC.Self = "FleetwoodToIsland";
        pchar.quest.Fleetwood_meetingShore.win_condition.l1 = "location";
        pchar.quest.Fleetwood_meetingShore.win_condition.l1.location = "Shore56";
        pchar.quest.Fleetwood_meetingShore.function = "InTerksShore";
        AddQuestRecord("Holl_Gambit", "3-28");
        break;

    case "Abigile_27":
        int iVal = 0;
        for (i = 0; i < COMPANION_MAX; i++)
        {
            iTemp = GetCompanionIndex(PChar, i);
            if (iTemp > 0)
            {
                sld = GetCharacter(iTemp);
                if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA)
                    iVal = 1;
            }
        } //установили признак наличия Валькирии в эскадре.
        if (iVal != 0)
        {
            dialog.text = "У меня нет слов! Великолепная комбинация, отличная задумка и мастерское исполнение! Поздравляю, " + pchar.name + "! Ты ещё и его бриг себе захватил!";
            link.l1 = "Спасибо! А где Эркюль? Я бы хотел его увидеть. Во время нашей последней встречи он сказал, что я могу найти его через тебя.";
            link.l1.go = "Abigile_28";
        }
        else
        {
            dialog.text = "Отличная работа! Великолепная комбинация, отличная задумка и мастерское исполнение!  Поздравляю, " + pchar.name + "!";
            link.l1 = "Спасибо! А где Эркюль? Я бы хотел его увидеть. Во время нашей последней встречи он сказал, что я могу найти его через тебя.";
            link.l1.go = "Abigile_28";
        }
        break;

    case "Abigile_28":
        dialog.text = "Я жду Эркюля с часу на час. Он должен прийти через подземелье. А тебе нужно объясниться с девушкой. Она, похоже, уже начинает беспокоиться по поводу отсутствия Ричарда.";
        link.l1 = "Хорошо. Может, пора бы её и домой отправить?";
        link.l1.go = "Abigile_29";
        break;

    case "Abigile_29":
        dialog.text = "Погоди... У меня будет к тебе разговор. Но сначала пусть придёт Эркюль, а ты успокой Абигайль. Соври ей что-нибудь, как ты умеешь. Потом приходи в подземелье. Договорились?";
        link.l1 = "Договорились, Джон.";
        link.l1.go = "Abigile_30";
        break;

    case "Abigile_30":
        DialogExit();
        npchar.greeting = "merdok_4";
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload2", "SentJons_TownCave", "item", "berglar1", "", -1);
        pchar.questTemp.HWIC.Self = "AbigileLie";
        sld = characterFromId("Abigile");
        LAi_SetCitizenType(sld);
        AddQuestRecord("Holl_Gambit", "3-34");
        break;

    case "Lucas":
        dialog.text = "Но для начала пришло время раскрыть карты. Как ты уже понял, я не простой аптекарь. Мое настоящее имя - Йохан ван Мерден, и до недавнего времени я работал агентом по особым поручениям Голландской Вест-Индской торговой Компании, и был правой рукой её вице-директора Лукаса Роденбурга.";
        link.l1 = "Вот как! Интересно...";
        link.l1.go = "Lucas_1";
        break;

    case "Lucas_1":
        dialog.text = "Однако недавно всё переменилось. Лукас решил, что я ему больше не нужен, и, более того - опасен для него. Он решил выйти из игры, уехать в Голландию, а дабы обезопасить себя от призраков прошлого, зачистить все концы\nЯ думаю, что до сих пор жив только потому, что у меня есть архив, содержащий все сведения о преступной деятельности Лукаса, в частности, о корабле-призраке, который в действительности обычный пиратский корабль под командованием беспринципного мерзавца Якоба ван Берга, нанятого Роденбургом специально для уничтожения английских торговых кораблей. Ты слышал об этом судне\nИменно ван Берг пустил ко дну флейт, на котором плыли наша Абигайль и её отец. Абигайль тоже не простая фигура - я был несколько... удивлён, узнав, что она будет гостить в моём доме - её руки добивался не только Флитвуд, но и сам Роденбург...";
        link.l1 = "Так вот о каком зяте болтал чудаковатый папаша Абигайль!";
        link.l1.go = "Lucas_2";
        break;

    case "Lucas_2":
        dialog.text = "Да. Именно поэтому я предложил тебе пока не отвозить Абигайль в Виллемстад - возможно, это будет мой последний козырь против Роденбурга, хотя я не хочу её вмешивать в это дело - она славная девушка, и я не хотел бы делать ей больно. Хотя думаю, что в выборе между Абигайль и архивом Лукас всё равно выбрал бы мой архив\nВ общем, я предлагаю тебе... даже прошу тебя выступить на моей стороне против Лукаса Роденбурга и устранить его тем или иным путём. Награда будет соответствующей.";
        link.l1 = "Хм... не думаю, что это будет намного сложнее, чем с Флитвудом.";
        link.l1.go = "Lucas_3";
        break;

    case "Lucas_3":
        dialog.text = "Сложнее. Флитвуд, так или иначе, был одиночкой и действовал на свой страх и риск. Роденбург - вице-директор Компании, обладающей обширными связями, да и сам он - очень влиятельный человек, второе лицо после губернатора. Якоб ван Берг - тот самый пират - один из его агентов, опаснейший тип. Лукас постоянно находится в Виллемстаде, под охраной гвардейцев Компании, а они ничуть не хуже гвардейцев Флитвуда, с которыми тебе уже довелось познакомиться\nТак что это будет очень непростая игра.";
        link.l1 = "Принцип этой игры тот же - выманить тигра из логова на открытое место... У меня уже зреет план. Что ещё ты можешь рассказать о Лукасе?";
        link.l1.go = "Lucas_4";
        break;

    case "Lucas_4":
        dialog.text = "С большего, я уже всё рассказал. Кроме прочего, у него есть личное быстроходное судно под названием 'Мейфенг', капитан - преданный ему китаец Лонгвэй - доверенное лицо и исполнитель поручений. Тоже достаточно неприятный противник - в команде Лукаса дилетантов нет.";
        link.l1 = "Однако мы уже на старте имеем на руках козырь - твой архив. Раз он ему дороже девушки, на которой хотел жениться, значит, ради неразглашения информации, содержащейся в нём, он пойдёт на многое... Джон, архив действительно существует? Ты не блефуешь?";
        link.l1.go = "Lucas_5";
        break;

    case "Lucas_5":
        dialog.text = "Архив существует. И Лукас об этом знает. Ты уже что-то придумал?";
        link.l1 = "Да. Джон, раз ты был агентом Компании, ты должен кое-что знать.";
        link.l1.go = "Lucas_6";
        break;

    case "Lucas_6":
        dialog.text = "Что именно? Спрашивай.";
        link.l1 = "Мне нужно перехватить корабль Компании. Желательно одиночный, типа курьера. Можешь что-нибудь сказать по этому поводу?";
        link.l1.go = "Lucas_7";
        break;

    case "Lucas_7":
        dialog.text = "Хм... Подобной информацией я не располагаю. Хотя подожди! Я точно знаю, что раз в месяц одно военное судно компании совершает скоростной переход между Филипсбургом и Виллемстадом, и обратно. На нём перевозится деловая корреспонденция Компании. Это бригантина, называется 'Хооп'\nОбычно она выходит из Филипсбурга где-то в эти дни каждого месяца, возможно, даже сегодня, или завтра.";
        link.l1 = "Отлично! Значит, мне нужно отправляться к берегам Сент-Кристофера - морской путь на Кюрасао проходит именно там...";
        link.l1.go = "Lucas_8";
        break;

    case "Lucas_8":
        dialog.text = "Удачи, " + pchar.name + ". Не буду расспрашивать тебя о деталях твоего плана. Буду ждать твоего возвращения!";
        link.l1 = "Всё будет хорошо, Джон. Береги девушку, не позволяй её обижать!";
        link.l1.go = "Lucas_9";
        break;

    case "Lucas_9":
        DialogExit();
        RemoveItems(PChar, "MC_Letter", 1);
        GiveItem2Character(pchar, "MC_Letter");
        ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter2");
        AddQuestRecordInfo("LetterToLucas", "1");
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);
        pchar.questTemp.HWIC.Self = "LetterToLucas";
        sld = characterFromId("Tonzag");
        sld.dialog.currentnode = "Tonzag_hired";
        LAi_SetActorType(sld);
        LAi_ActorDialog(sld, pchar, "", -1, 0);
        AddQuestRecord("Holl_Gambit", "3-36");
        //установим таймер на генерацию энкаунтера
        pchar.quest.HWIC_Cureer.win_condition.l1 = "Timer";
        pchar.quest.HWIC_Cureer.win_condition.l1.date.hour = sti(GetTime());
        pchar.quest.HWIC_Cureer.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
        pchar.quest.HWIC_Cureer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
        pchar.quest.HWIC_Cureer.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
        pchar.quest.HWIC_Cureer.function = "CreateHWICCureerOnMap";
        SetFunctionTimerCondition("HWICCureerOnMapOver", 0, 0, 16, false); //таймер
        break;

    case "Lucas_10":
        dialog.text = "Невероятно! Ушам не верю! Как это произошло?";
        link.l1 = "Я захватил курьера от имени Флитвуда отправил Лукасу письмо, в котором заявил, что захватил архив некого аптекаря из Сент-Джонса, и скоро доказательства всевозможных гнусностей станут известны как голландцам, так и англичанам. Я ожидал, что он начнёт охоту на меня, но вышло иначе.";
        link.l1.go = "Lucas_11";
        break;

    case "Lucas_11":
        dialog.text = "";
        link.l1 = "Лукас обвинил Матиаса Бека в измене и связи с англичанами, посадил его за решетку, а сам занял место губернатора. Капитана бригантины он, скорее всего, ликвидировал. Затем он приказал своему верному китайцу на 'Мейфенг' потопить корабль самого директора Компании, Питера Стайвесанта!";
        link.l1.go = "Lucas_12";
        break;

    case "Lucas_12":
        dialog.text = "Роденбург - решительный и жестокий человек. Но я даже не предполагал, что он способен пойти на такие крайности...";
        link.l1 = "Я захватил 'Мейфенг', Лонгвэя допросил. Он всё расссказал. Я нашёл Стайвесанта, предупредил его о замыслах Роденбурга, и вместе с ним отправился в Виллемстад. Там Стайвесант выпустил Бека и арестовал Лукаса. Теперь он в тюрьме.";
        link.l1.go = "Lucas_13";
        break;

    case "Lucas_13":
        dialog.text = "Хех! Дружище, ты просто талант... Тебе нужно делать карьеру в военном флоте и в политике - у тебя есть все шансы стать губернатором! Да, а что ты сделал с Лонгвэем?";
        link.l1 = "Отпустил. Он пошёл мне навстречу, и я не причинил ему вреда.";
        link.l1.go = "Lucas_14";
        break;

    case "Lucas_14":
        dialog.text = "Это хорошо. Лонгвэй - неплохой парень, в отличие от своего бывшего хозяина. Ну что же, " + pchar.name + ", ты отлично поработал. Я подготовлю твою награду, но мне потребуется некоторое время. А пока...";
        link.l1 = "Джон, есть, правда, одна ложка дёгтя в бочке меда. Лонгвэй, а затем и Роденбург, сказали, что на меня ведёт охоту Якоб ван Берг. Насколько это неприятно?";
        link.l1.go = "Lucas_15";
        break;

    case "Lucas_15":
        dialog.text = "Якоб ван Берг? Дружище, это очень и очень серьёзно. Ван Берг - беспощадный пират, опытный моряк и боец. Профессиональный охотник, можно сказать. Именно он уничтожал корабли англичан по приказу Роденбурга\nЕсли Лукас приказал ему найти тебя - следует готовится к неизбежной встрече. Да и мне нужно принимать меры предосторожности.";
        link.l1 = "Как мне найти этого ван Берга?";
        link.l1.go = "Lucas_16";
        break;

    case "Lucas_16":
        dialog.text = "Не знаю. Скорее всего - никак. О его местонахождении знали только два человека - Лукас и Лонгвэй. Ни у одного, ни у второго ты уже не спросишь. Просто будь начеку - он может появиться в любой момент. Да, рано я собрался спать спокойно\nЯ закрываю аптеку и перехожу на осадное положение. Вход в дом теперь - только через подземелье. Тебе нужно увезти отсюда девушку - здесь стало очень опасно.";
        link.l1 = "Не переживай, Джон. Пусть только объявится - а я уж как-нибудь разберусь и с ним. Где Абигайль?";
        link.l1.go = "Lucas_17";
        break;

    case "Lucas_17":
        dialog.text = "Она ушла в церковь. Мне жаль её. Она в последнее время совсем... расстроена.";
        link.l1 = "М-да. Неудивительно. Ладно, пришло время отвезти её назад, к отцу.";
        link.l1.go = "Lucas_18";
        break;

    case "Lucas_18":
        dialog.text = "Она очень хотела тебя видеть. Думаю, Аби будет сама просить тебя, чтобы ты вернул её домой.";
        link.l1 = "Ты называешь её Аби?";
        link.l1.go = "Lucas_19";
        break;

    case "Lucas_19":
        dialog.text = "Надо сказать, мы с ней... подружились. Я не жалею, что она жила у меня, и слава Богу, она никогда не узнает, с какой целью её сюда привезли.";
        link.l1 = "Понятно. Ладно, Джон, я пойду в церковь за Абигайль. А затем беру курс на Виллемстад.";
        link.l1.go = "Lucas_20";
        break;

    case "Lucas_20":
        DialogExit();
        sld = characterFromId("Abigile");
        ChangeCharacterAddressGroup(sld, "SentJons_church", "goto", "goto1"); //Аби - в церковь
        AddQuestRecord("Holl_Gambit", "3-56");
        pchar.questTemp.HWIC.Self = "AbiReturnHome";
        LocatorReloadEnterDisable("SentJons_town", "HouseF3", true); //закрыть аптеку
        break;

    case "Final":
        dialog.text = "Уф, ты сделал это! Поздравляю!";
        link.l1 = "Спасибо. Так что теперь, Джон, ты можешь жить спокойно.";
        link.l1.go = "Final_1";
        break;

    case "Final_1":
        dialog.text = "Да... Пожалуй, надо заканчивать с этими политическими играми и интригами. Теперь пришло время поговорить о твоей награде за выполненную работу.";
        link.l1 = "Ну что же, я не против.";
        link.l1.go = "Final_2";
        break;

    case "Final_2":
        dialog.text = "Я собираюсь отбыть с Кариб навсегда. В качестве благодарности за помощь, фактически - за спасение от Роденбурга, я отдаю тебе этот дом, мою аптеку, в твоё пользование. Теперь это твоё. Держи ключи.";
        link.l1 = "Вот это здорово! Я рад - у тебя очень уютный дом. И очень уютный погребок...";
        link.l1.go = "Final_3";
        break;

    case "Final_3":
        GiveItem2Character(pchar, "Drugstore_keys"); //ключ
        dialog.text = "Также прими эту скромную сумму денег - 100 000 песо и вот этот мушкет. Он верой и правдой служил мне когда-то - пусть послужит и тебе.";
        link.l1 = "Не откажусь!";
        link.l1.go = "Final_4";
        LocatorReloadEnterDisable("SentJons_town", "HouseF3", false);    //открыть аптеку
        LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", false); // открыть комнату
        pchar.quest.Jino_Door.win_condition.l1 = "locator";
        pchar.quest.Jino_Door.win_condition.l1.location = "SentJons_HouseF3";
        pchar.quest.Jino_Door.win_condition.l1.locator_group = "reload";
        pchar.quest.Jino_Door.win_condition.l1.locator = "reload4";
        pchar.quest.Jino_Door.function = "OpenRoomDoor"; //на локатор комнаты Джино
        Achievment_SetStat(pchar, 10, 1);
        break;

    case "Final_4":
        AddMoneyToCharacter(pchar, 100000);
        GiveItem2Character(pchar, "mushket2");
        dialog.text = "В комнате наверху ты найдёшь одного учёного молодого человека. Он - лучший фармацевт из всех, кого я знаю. Именно он сделал микстуры, которые поставили тебя на ноги буквально за несколько дней. Позаботься о его содержании - его знания компенсируют твои затраты с лихвой.";
        link.l1 = "Хорошо. Я позабочусь о нём.";
        link.l1.go = "Final_5";
        break;

    case "Final_5":
        dialog.text = "Ну, а теперь мы должны проститься. Я пойду в погребок, соберу свои вещи, а завтра меня уже не будет здесь - я отплываю с Антигуа. Я рад, что встретил тебя, и рад, что в этой игре ты оказался на моей стороне, а не на стороне моих врагов.";
        link.l1 = "Я тоже рад знакомству с тобой, Джон. Может, ещё встретимся...";
        link.l1.go = "Final_6";
        break;

    case "Final_6":
        dialog.text = "Это вряд ли. Ну, я пошёл собираться. Прощай, " + pchar.name + "!";
        link.l1 = "Прощай, Джон. Удачи тебе!";
        link.l1.go = "Final_7";
        break;

    case "Final_7":
        DialogExit();
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
        npchar.lifeday = 0;
        pchar.questTemp.HWIC.Self = "final";
        AddQuestRecord("Holl_Gambit", "3-64");
        CloseQuestHeader("Holl_Gambit");
        pchar.questTemp.HWIC.Detector = "self_win";
        break;

    // Страж Истины
    case "guardoftruth":
        dialog.text = "Ах, мистер, не слушайте вы этих вздорных разговоров! Никого там нет. Там моя лаборатория - микстуры готовятся...";
        link.l1 = "Джон, давай без шуток. Имя Джино Гвинейли тебе о чём-нибудь говорит?";
        link.l1.go = "guardoftruth_1";
        break;

    case "guardoftruth_1":
        dialog.text = "Кхм...";
        link.l1 = "Ага! По глазам вижу, что я прав... Значит, вот у кого он живёт и кому готовит свои зелья!";
        link.l1.go = "guardoftruth_2";
        break;

    case "guardoftruth_2":
        dialog.text = "Сударь, я ещё раз говорю - там никого нет...";
        link.l1 = "Оставим эти отговорки, Джон. Я не сделаю ничего плохого твоему алхимику, а вот если его найдёт отец Винсенто из Сантьяго - тут  поручиться не могу. А ведь инквизитор уже собирается направить своих ищеек на Антигуа...";
        link.l1.go = "guardoftruth_3";
        break;

    case "guardoftruth_3":
        dialog.text = "Что ты от него хочешь?";
        link.l1 = "Просто поговорить. Он владеет крайне важной для меня информацией. Обещаю, что не выдам его инквизиции и не сделаю ничего дурного.";
        link.l1.go = "guardoftruth_4";
        break;

    case "guardoftruth_4":
        dialog.text = "Джино - замечательный парень. Не верь ни слову о том, что на него наговорил этот отец Винсенто. И помни - я своего алхимика в обиду не дам. ";
        link.l1 = "Я пообещал. Тебе мало?";
        link.l1.go = "guardoftruth_5";
        break;

    case "guardoftruth_5":
        dialog.text = "Ступай наверх. Дверь отперта. Надеюсь, ты сдержишь слово.";
        link.l1 = "Будь уверен - сдержу.";
        link.l1.go = "guardoftruth_6";
        break;

    case "guardoftruth_6":
        DialogExit();
        pchar.questTemp.Guardoftruth = "jino1";
        AddQuestRecord("Guardoftruth", "36");
        LocatorReloadEnterDisable(pchar.location, "reload4", false);
        break;

    // алхимический набор
    case "alchemy":
        dialog.text = "Капитан, не хотите ли вы тоже немного приобщиться к искусству алхимии? Это вам может очень и очень пригодиться.";
        link.l1 = "Простите, но род моей деятельности несколько иной, я привык держать в руках саблю, а не колбы с пробирками.";
        link.l1.go = "alchemy_exit";
        link.l2 = "Хм. Как говорил мой братец - не стоит брезговать научиться делать что-либо собственными руками. Конечно, хочу. А что для этого нужно?";
        link.l2.go = "alchemy_1";
        npchar.quest.alchemy = true;
        break;

    case "alchemy_exit":
        dialog.text = "Как скажете. Было бы предложено...";
        link.l1 = "...";
        link.l1.go = "exit";
        break;

    case "alchemy_1":
        dialog.text = "Для этого вам нужно научиться смешивать зелья своими руками. Но у вас ничего не получится без алхимического набора. Вот, посмотрите в этот саквояж. В нем есть всё, что нужно начинающему алхимику - пробирки, колбы, реторты, перегонный куб, шпатели, стеклянные трубки, горелка и прочее...";
        link.l1 = "Очень интересно! И что же можно с его помощью изготовить?";
        link.l1.go = "alchemy_2";
        break;

    case "alchemy_2":
        dialog.text = "Ну, превратить свинец в золото у вас не получится, но смешать ингредиенты согласно рецептам и получить на выходе зелья и другие полезные предметы вы точно сможете.";
        link.l1 = "Рецептам?";
        link.l1.go = "alchemy_3";
        break;

    case "alchemy_3":
        dialog.text = "Ну да. Для того, чтобы приготовить собственное зелье или предмет, вы должны знать его рецепт. Рецепты вы можете купить у торговцев травами и амулетами, или найти где-либо ещё. Затем, изучив рецепт, вы должны собрать все нужные ингредиенты и выполнить действия в строгой последовательности, как указано в рецепте\nЕсли вы собираетесь приготовить зелье - вам потребуется пустой пузырёк, чтобы поместить туда приготовленное. Для нагревания используйте горелку, для взятия навесок веществ - шпатель, для простого кипячения - колбу, для испарения с конденсацией - перегонный куб\nТакже вам наверняка потребуется ступка и пестик для измельчения твёрдых компонентов, но эти предметы вы сможете приобрести у лоточников за приемлемую цену. Также вам может понадобиться тигель - для нагревания веществ до очень высоких температур - но лишнего тигеля у меня нет\nТак что если вам вдруг попадётся такая штука, берите даже не думая - пригодится. В общем, надо пробовать, пытаться - и всё получится. Компоненты - это как правило травы, спиртосодержащие жидкости, готовые зелья, минералы, а также вообще любые предметы.";
        link.l1 = "Очень занятно! Сколько вы хотите за этот набор?";
        link.l1.go = "alchemy_4";
        break;

    case "alchemy_4":
        dialog.text = "Двадцать тысяч песо. Это очень хороший набор, и он быстро окупится.";
        link.l1 = "Да вы что, смеётесь? Чемодан со стеклянной посудой по цене люггера? Нет уж, увольте.";
        link.l1.go = "alchemy_exit";
        if (sti(pchar.money) >= 20000)
        {
            link.l2 = "Я согласен. Думаю, будет интересно попробовать сварить что-нибудь своими руками.";
            link.l2.go = "alchemy_5";
        }
        break;

    case "alchemy_5":
        AddMoneyToCharacter(pchar, -20000);
        Log_Info("Вы получили набор алхимика");
        GiveItem2Character(pchar, "alchemy_tool");
        PlaySound("interface\important_item.wav");
        dialog.text = "Вы не пожалеете о покупке. Говорю вам это совершенно точно. Согласитесь, намного выгоднее самому варить зелья в нужном количестве, а не бегать по лоткам травников, скупая по одной штуке. Кроме того, купить-то можно далеко не всё.";
        link.l1 = "Будем учиться. Думаю, у меня всё получится!";
        link.l1.go = "alchemy_6";
        break;

    case "alchemy_6":
        DialogExit();
        PlaySound("interface\notebook.wav");
        Log_Info("Для создания собственных зелий и амулетов вы должны владеть навыком 'Алхимия'!");
        break;

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    //--> блок реагирования на попытку залезть в сундук
    case "Man_FackYou":
        dialog.text = LinkRandPhrase("Да ты " + GetSexPhrase("вор, милейший! Стража, держи его", "воровка! Стража, держи её") + "!!!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Держи " + GetSexPhrase("вора", "воровку") + "!!!", "Стража! Грабят!!! Держи " + GetSexPhrase("вора", "воровку") + "!!!");
        link.l1 = "А-ать, дьявол!!!";
        link.l1.go = "exit";
        LAi_group_Attack(NPChar, Pchar);
        break;
        //<-- блок реагирования на попытку залезть в сундук
    }
}