void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, Diag;
    int i;
    string sTemp;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(Diag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
    case "exit":
        Diag.CurrentNode = Diag.TempNode;
        DialogExit();
        break;

    case "Exit_Fight":
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
        LAi_SetPlayerType(pchar);
        for (i = 1; i <= 3; i++)
        {
            if (GetCharacterIndex("GangMan_" + i) == -1)
                continue;
            sld = CharacterFromID("GangMan_" + i);
            LAi_SetImmortal(sld, false);
            LAi_SetWarriorType(sld);
            LAi_group_MoveCharacter(sld, "EnemyFight");
        }
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck("EnemyFight", "OpenTheDoors");

        if (pchar.GenQuest.EncGirl == "RapersTreasure")
        {
            LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
        }
        else
        {
            LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");
            sld = CharacterFromID("CangGirl");
            LAi_SetActorType(sld);
            LAi_ActorAfraid(sld, npchar, true);
        }
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

    case "exit_noFight":
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
        for (i = 1; i <= 3; i++)
        {
            if (GetCharacterIndex("GangMan_" + i) == -1)
                continue;
            sld = CharacterFromID("GangMan_" + i);
            LAi_SetActorType(sld);
            LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
            LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld) - 1, false, "LandEnc_RapersBeforeDialog");
        }
        sld = CharacterFromID("CangGirl");
        LAi_SetActorType(sld);
        LAi_ActorAfraid(sld, npchar, true);
        DialogExit();
        AddDialogExitQuest("OpenTheDoors");
        break;

    case "First time":
        for (i = 1; i <= 3; i++)
        {
            if (GetCharacterIndex("GangMan_" + i) == -1)
                continue;
            sld = CharacterFromID("GangMan_" + i);
            LAi_type_actor_Reset(sld);
            LAi_RemoveCheckMinHP(sld);
        }
        //            Diag.TempNode = "OnceAgain";
        if (pchar.GenQuest.EncGirl == "Begin_1")
        {
            dialog.text = LinkRandPhrase("Ш" + GetSexPhrase("ел", "ла") + " бы ты своей дорогой, " + GetSexPhrase("приятель", "подруга") + ". Она потом нас благодарить ещё будет.",
                                         "Убирайся отсюда! Не мешай джентльменам развлекаться.",
                                         "Не ввязывайся не в своё дело, " + GetSexPhrase("незнакомец", "деваха") + ". Подумаешь, мы чуть позабавимся!");
            link.l1 = LinkRandPhrase("Я не позволю этому совершиться!", "Бросьте своё дурное дело!", "Я не допущу насилия!");
            link.l1.go = "Node_Fight";
            link.l2 = RandPhraseSimple("Понял" + GetSexPhrase("", "а") + ", ухожу. Извините, что помешал" + GetSexPhrase("", "а") + ".", "Не смею вам мешать. Извините, что побеспокоил" + GetSexPhrase("", "а") + ".");
            link.l2.go = "Exit_NoFight";
            pchar.GenQuest.EncGirl = "Begin_11";
        }
        if (pchar.GenQuest.EncGirl == "Begin_2")
        {
            if (sti(pchar.rank) < 10)
            {
                dialog.text = LinkRandPhrase("Ш" + GetSexPhrase("ел", "ла") + " бы ты своей дорогой, " + GetSexPhrase("приятель", "подруга") + ". Она потом нас благодарить ещё будет.",
                                             "Убирайся отсюда! Не мешай джентльменам развлекаться.",
                                             "Не ввязывайся не в своё дело, " + GetSexPhrase("незнакомец", "деваха") + ". Подумаешь, мы чуть позабавимся!");
                link.l1 = LinkRandPhrase("Я не позволю этому совершиться!", "Бросьте своё дурное дело!", "Я не допущу насилия!");
                link.l1.go = "Node_Fight";
                link.l2 = RandPhraseSimple("Понял" + GetSexPhrase("", "а") + ", ухожу. Извините, что помешал" + GetSexPhrase("", "а") + ".", "Не смею вам мешать. Извините, что побеспокоил" + GetSexPhrase("", "а") + ".");
                link.l2.go = "Exit_NoFight";
                pchar.GenQuest.EncGirl = "Begin_11";
            }
            else
            {
                dialog.text = RandPhraseSimple("Эй, " + GetSexPhrase("незнакомец", "девушка") + ", зачем тебе неприятности? Это же известная в поселении персона. Мы с ней уже и расплатились. А она тебя увидала и улизнуть решила.",
                                               "Эй, " + GetSexPhrase("приятель", "подруга") + ", иди своей дорогой и не вмешивайся, куда тебя не просят. Мы девицу эту в кости выиграли, да она слишком резвая оказалась. Битый час за ней бегаем.");
                link.l1 = "Ничего не знаю, девчонку в обиду не дам!";
                link.l1.go = "Node_3";
                link.l2 = RandPhraseSimple("Вот в чём дело! А я чуть было не поверил" + GetSexPhrase("", "а") + "! Ну красавица даёт...", "А-а, ну это другое дело. Что ж, развлекайтесь, коль охота.");
                link.l2.go = "Exit_NoFight";
                pchar.GenQuest.EncGirl = "Begin_22";
            }
        }
        if (pchar.GenQuest.EncGirl == "Begin_3")
        {
            if (sti(pchar.rank) < 20)
            {
                dialog.text = "Иди, " + GetSexPhrase("мил-человек", "девушка") + ", своей дорогой. Без тебя разберёмся.";
                link.l1 = "Я не допущу насилия!";
                link.l1.go = "Node_5";
                pchar.GenQuest.EncGirl = "Begin_33";
            }
            else
            {
                dialog.text = RandPhraseSimple("Эй, " + GetSexPhrase("незнакомец", "девушка") + ", зачем тебе неприятности? Это же известная в поселении персона. Мы с ней уже и расплатились. А она тебя увидала и улизнуть решила.",
                                               "Эй, " + GetSexPhrase("приятель", "подруга") + ", иди своей дорогой и не вмешивайся, куда тебя не просят. Мы девицу эту в кости выиграли, да она слишком резвая оказалась. Битый час за ней бегаем.");
                link.l1 = "Ничего не знаю, девчонку в обиду не дам!";
                link.l1.go = "Node_3";
                link.l2 = RandPhraseSimple("Вот в чём дело! А я чуть было не поверил" + GetSexPhrase("", "а") + "! Ну красавица даёт...", "А-а, ну это другое дело. Что ж, развлекайтесь, коль охота.");
                link.l2.go = "Exit_NoFight";
                pchar.GenQuest.EncGirl = "Begin_22";
            }
        }
        break;

    case "Node_Fight":
        dialog.text = RandPhraseSimple("" + GetSexPhrase("Ох и не вовремя же ты погулять вышел...", "Что, решила геройствовать?") + " Вали е" + GetSexPhrase("го", "е") + ", ребята!", "Ах ты " + GetSexPhrase("слизняк", "дрянь") + "! Ты кому поперёк дороги становишься?! Режь е" + GetSexPhrase("го", "е") + "!");
        link.l1 = "И не таких грозных видали.";
        link.l1.go = "Exit_Fight";
        break;

    case "Node_3":
        pchar.GenQuest.EncGirl.price = 1100 * (rand(4) + 5) + 200 * sti(pchar.rank);
        dialog.text = "Да она обошлась нам в кругленькую сумму! Если ты так" + GetSexPhrase("ой", "ая") + " благородн" + GetSexPhrase("ый", "ая") + ", то можешь забирать её за " + sti(pchar.GenQuest.EncGirl.price) + " песо." + GetSexPhrase(" Покувыркаешься вволю, хе-хе..", "") + "";
        if (sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
        {
            link.l1 = RandPhraseSimple("Вот ваши деньги, я её забираю.", "Не скаль зубы. Я забираю девчонку, вот деньги.");
            link.l1.go = "Node_4";
        }
        link.l2 = LinkRandPhrase("Денег захотелось?! А сталь под ребро не желаешь?!",
                                 "Тебе развлечение, а девчонка от страха еле на ногах стоит!",
                                 "Ты кого обмануть пытаешься?! чучело лесное!");
        link.l2.go = "Node_Fight";
        break;

    case "Node_4": // бандюки уходят, девица остается - ГГ ее выкупил у бандюков
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
        AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price)));
        ChangeCharacterComplexReputation(pchar, "nobility", 7);
        //pchar.quest.LandEnc_RapersBadExit.over = "yes";
        sGlobalTemp = "Saved_CangGirl";
        pchar.GenQuest.EncGirl.Ransom = true;
        sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
        for (i = 1; i <= 3; i++)
        {
            if (GetCharacterIndex("GangMan_" + i) == -1)
                continue;
            sld = CharacterFromID("GangMan_" + i);
            LAi_SetImmortal(sld, true);
            LAi_SetActorType(sld);
            if (i == 1)
                LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
            else
                LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", 5.0);
        }
        DialogExit();
        AddDialogExitQuestFunction("EncGirl_Saved");
        break;

    case "Node_5":
        dialog.text = "Да чего ты ей веришь?! Какое насилие? Из дому она сбежала, весь день гоняемся - хозяин послал.";
        link.l1 = RandPhraseSimple("Вот как? Ну это меняет дело. Догоняйте свою беглянку.", "А-а, ну гоняйтесь, гоняйтесь. А мне тут по делам нужно...");
        link.l1.go = "Exit_NoFight";
        link.l2 = RandPhraseSimple("Ты эти сказки внукам будешь рассказывать, если доживёшь!", "Ты кого обмануть решил?!");
        link.l2.go = "Node_6";
        link.l3 = "Вот я сам" + GetSexPhrase("", "а") + " её домой и отведу, чтоб чего лишнего не вышло. Кто её родители?";
        link.l3.go = "Node_7";
        break;

    case "Node_6":
        dialog.text = "Ну, ты сам" + GetSexPhrase("", "а") + " на нож полез" + GetSexPhrase("", "ла") + ", теперь не обессудь...";
        link.l1 = "Кто бы говорил.";
        link.l1.go = "Exit_Fight";
        break;

    case "Node_7":
        sGlobalTemp = "Saved_CangGirl";
        if (pchar.GenQuest.EncGirl.city == "Panama")
            i = drand(2);
        else
            i = drand(3);
        switch (i)
        {
        case 0:
            pchar.GenQuest.EncGirl.FatherNom = "хозяин магазина";
            pchar.GenQuest.EncGirl.FatherGen = "хозяина магазина";
            pchar.GenQuest.EncGirl.Father = "store_keeper";
            break;
        case 1:
            pchar.GenQuest.EncGirl.FatherNom = "служит в портовом управлении";
            pchar.GenQuest.EncGirl.FatherGen = "служащего в портовом управлении";
            pchar.GenQuest.EncGirl.Father = "portman_keeper";
            break;
        case 2:
            pchar.GenQuest.EncGirl.FatherNom = "служит комендантом тюрьмы";
            pchar.GenQuest.EncGirl.FatherGen = "коменданта тюрьмы";
            pchar.GenQuest.EncGirl.Father = "fort_keeper";
            break;
        case 3:
            pchar.GenQuest.EncGirl.FatherNom = "хозяин верфи";
            pchar.GenQuest.EncGirl.FatherGen = "хозяина верфи";
            pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
            break;
        }
        dialog.text = "Её отец - " + pchar.GenQuest.EncGirl.FatherNom + ", что в поселении " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ". Только не подведи нас, а то нрав у него больно крутой - три шкуры спустит...";
        link.l1 = "Не волнуйтесь. Доставлю в лучшем виде.";
        link.l1.go = "Node_12";
        pchar.GenQuest.EncGirl = "toParents";
        break;

    case "Node_12":
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
        pchar.quest.LandEnc_RapersBadExit.over = "yes";
        ChangeCharacterComplexReputation(pchar, "nobility", 5);
        sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
        for (i = 1; i <= 3; i++)
        {
            if (GetCharacterIndex("GangMan_" + i) == -1)
                continue;
            sld = CharacterFromID("GangMan_" + i);
            LAi_SetActorType(sld);
            LAi_SetImmortal(sld, true);
            if (i == 1)
                LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
            else
                LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", 5.0);
            sld.lifeDay = 0;
        }
        DialogExit();
        AddDialogExitQuestFunction("EncGirl_Saved");
        break;

    case "Node_8":
        dialog.text = "Вот и снова встретились. А где твоя попутчица?.. Впрочем, она уже без надобности, раз ты здесь.";
        link.l1 = "Джентльмены, мне кажется, полученная вами сумма достаточна, чтоб оставить девчонку в покое.";
        link.l1.go = "Node_9";
        break;

    case "Node_9":
        if (drand(1) == 0)
        {
            pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
            pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;
        }
        else
        {
            pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);
            pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;
        }
        pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
        switch (drand(4))
        {
        case 0:
            sTemp = "ноги";
            break;
        case 1:
            sTemp = "руки";
            break;
        case 2:
            sTemp = "уха";
            break;
        case 3:
            sTemp = "носа";
            break;
        case 4:
            sTemp = "глаза";
            break;
        }
        dialog.text = "Что твоя сумма по сравнению с сокровищами " + GetName(pchar.GenQuest.EncGirl.PirateIdx, pchar.GenQuest.EncGirl.PirateName1, NAME_GEN) + "? " +
                      "Он был настолько скуп, что не выдал собственную дочку замуж, потому что не хотел тратиться на свадьбу...\nНо в его сундуках есть и наша доля! " +
                      GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.PirateName2, NAME_NOM) + " в одном из абордажей лишился " + sTemp + "! И что получил взамен? " +
                      "Жалкую горсть серебра?! Всю добычу " + GetName(pchar.GenQuest.EncGirl.PirateIdx, pchar.GenQuest.EncGirl.PirateName1, NAME_NOM) + " утаскивал к себе в тайник. Но теперь мы не намерены отступать! Показывай, где его сундуки!";
        link.l1 = "Хм, хоть я и не нанимал" + GetSexPhrase("ся", "ась") + " сторожить сокровища вашего капитана, но показать вам место не могу... Потому что сам" + GetSexPhrase("", "а") + " его не знаю.";
        link.l1.go = "Node_10";
        break;

    case "Node_10":
        dialog.text = "Ты лжешь!!! Я уже чувствую запах золота, который струится из этой пещеры! Показывай место, если не хочешь подохнуть!";
        link.l1 = "Вижу, мои слова тебя не убедили. Может, убедит клинок?";
        link.l1.go = "Node_11";
        break;

    case "Node_11":
        pchar.GenQuest.EncGirl = "RapersTreasure";
        dialog.text = "Ах ты " + GetSexPhrase("пес", "дрянь") + "! Прочь с дороги!...";
        link.l1 = "Аргх...";
        link.l1.go = "exit_fight";
        break;

    case "EncGirl_Berglar":
        dialog.text = "Здравствуй, уважаем" + GetSexPhrase("ый", "ая") + ". Жалобы на тебя поступают.";
        link.l1 = "От кого жалобы? От этой шалавы?";
        link.l1.go = "EncGirl_Berglar1";
        break;

    case "EncGirl_Berglar1":
        dialog.text = "Ты полегче в выражениях! Я свою сестрёнку обижать не позволю! Сначала в джунглях к ней приста" + GetSexPhrase("вал", "ла") + ", потом сюда " + GetSexPhrase("привёл непристойности предлагать", "затащила и обобрала") + ".";
        link.l1 = "Слушай, приятель, мне обязательно всё это выслушивать?";
        link.l1.go = "EncGirl_Berglar2";
        break;

    case "EncGirl_Berglar2":
        pchar.GenQuest.EncGirl.BerglarSum = makeint(sti(pchar.money) / 5) + 5000;
        if (sti(pchar.GenQuest.EncGirl.BerglarSum) > 250000)
            pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
        if (sti(pchar.GenQuest.EncGirl.BerglarSum) > 0)
        {
            dialog.text = "Нет. Скромная сумма в " + sti(pchar.GenQuest.EncGirl.BerglarSum) + " песо может избавить тебя от любых неприятностей.";
            if (sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.BerglarSum))
            {
                link.l1 = "Хм, однако недёшево нынче обходятся благородные поступки. Забирай...";
                link.l1.go = "EncGirl_Berglar3";
            }
            link.l2 = "Дешевле будет сделать в твоём брюхе дыру, чтоб не заслонял мне дорогу к выходу.";
            link.l2.go = "EncGirl_Berglar4";
        }
        else
        {
            dialog.text = "Нет. Но тебе придется вывернуть карманы, не то зарежу ведь!";
            link.l1 = "Забирай, паршивец! Но это тебе так просто с рук не сойдет...";
            link.l1.go = "EncGirl_Berglar3_1";
            link.l2 = "Проще будет сделать в твоём брюхе дыру, чтоб не заслонял мне дорогу к выходу.";
            link.l2.go = "EncGirl_Berglar4";
        }
        break;

    case "EncGirl_Berglar3":
        AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BerglarSum)));
        dialog.text = "Вот и славно. Скатертью дорога.";
        link.l1 = "Счастливо оставаться.";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("EncGirlFack_outRoom");
        break;

    case "EncGirl_Berglar3_1":
        dialog.text = "Конечно, не сойдет, кто же спорит? Ну, прощай, " + GetSexPhrase("дружище", "подруга") + "." + GetSexPhrase(" И помни - не такой ты красавец, чтобы на тебя девушки с ходу вешались. Впредь будешь умней!", "") + "";
        link.l1 = "" + GetSexPhrase("Это точно!..", "Давай уже, проваливай!") + "";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");
        break;

    case "EncGirl_Berglar4":
        dialog.text = "На вид " + GetSexPhrase("такой благородный человек", "такая воспитанная девушка") + ", а так некультурно выражаешься.";
        link.l1 = "Как умею...";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("EncGirlFack_fight");
        break;

    case "Node_2":
        dialog.text = "Ну, тогда пеняй на себя! Пощекочем е" + GetSexPhrase("го", "е") + " ребра сталью, ребята!";
        Link.l1 = "Помолитесь перед смертью!";
        Link.l1.go = "Exit_Fight";
        break;

    case "OnceAgain":
        Diag.TempNode = "OnceAgain";
        dialog.text = "Что, захотелось присоединиться? " + GetSexPhrase("Иди к черту - нам самим мало", "Иди отсюда, нам одной девки хватит") + "!";
        Link.l1 = "Раз так, не буду вам мешать.";
        Link.l1.go = "Exit_NoFight";
        Link.l2 = "Я не позволю насилию случиться на моих глазах!";
        Link.l2.go = "Node_2";
        break;
    }
}
