// Соломон Шнеур - старый еврей
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
        //--------------------------------------за Голландию------------------------------------------------
        if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
        {
            if (pchar.questTemp.HWIC.Holl == "AbbyFather")
            {
                dialog.text = "Молодой человек, ну что вы хотите от старого бедного еврея?";
                link.l1 = "Соломон, я хочу, чтобы вы постарались вспомнить, что это за остров, на котором вы спрятали свои сбережения. Я говорил с вашей дочерью. Мой командир - Лукас Роденбург - даёт мне полную свободу действий на благо вашей семьи. А сейчас самое важное для вас, как я понял - вернуть семейный капитал. Но без вашей помощи мне будет трудно это сделать...";
                link.l1.go = "SolomonBonanza";
                break;
            }
            if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
            {
                dialog.text = "Ох, это опять вы, молодой человек? Расскажете мне что-нибудь хорошее? Или опять будете мучать старого бедного еврея вопросами?";
                if (CheckCharacterItem(pchar, "SkullAztec"))
                {
                    link.l1 = "Я нашёл остров, хотя это было достаточно сложной задачей. Отыскал я также и ваш сундук с деньгами, и вот этот артефакт в виде черепа. Как я понял, это и есть тот череп деда, про который вы говорили.";
                    link.l1.go = "SolomonBonanza_2";
                }
                link.l2 = "Я нашёл остров, хотя это было достаточно сложной задачей. Отыскал я также и ваш сундук с деньгами. А вот черепов никаких в схроне не оказалось.";
                link.l2.go = "SolomonBonanza_3";
                link.l3 = "Да нет, пока ничего не расскажу и вопросов задавать тоже не буду.";
                link.l3.go = "exit";
                break;
            }
            if (pchar.questTemp.HWIC.Holl == "GiveLucasMoney" && GetQuestPastDayParam("questTemp.HWIC.Holl.LucasMoney") > 7)
            {
                dialog.text = "Ох, это опять вы, молодой человек? Расскажете мне что-нибудь хорошее? Или опять будете мучать старого бедного еврея вопросами?";
                link.l1 = "Я нашёл остров, хотя это было достаточно сложной задачей. Отыскал я также и ваши деньги. Вот, возьмите, пожалуйста.";
                link.l1.go = "SolomonBonanza_5";
                break;
            }
            dialog.text = "Здравствуйте, молодой человек. Ну что вы хотите от бедного старого еврея?";
            link.l1 = "Добрый день. Да нет, ничего, просто поздороваться решил.";
            link.l1.go = "exit";
            break;
        }
        //----------------------------------------за Англию-----------------------------------------------
        if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
        {
            if (pchar.questTemp.HWIC.Eng == "toAbigile")
            {
                dialog.text = "День добрый, молодой человек. Я вижу, что вы пришли неспроста... Вам что-то надо? Что я буду с этого иметь, кроме гембеля, конечно?";
                link.l1 = "Добрый день. Мне нужно поговорить с Абигайль.";
                link.l1.go = "Solomon_treasure";
                break;
            }
            dialog.text = "Здравствуйте, молодой человек. Ну что вы хотите от бедного старого еврея?";
            link.l1 = "Добрый день. Да нет, ничего, просто поздороваться решил.";
            link.l1.go = "exit";
            break;
        }
        //-----------------------------------------против всех-------------------------------------------------
        if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
        {
            if (pchar.questTemp.HWIC.Self == "toVillemstad")
            {
                dialog.text = "День добрый, молодой человек. Я вижу, что вы пришли неспроста... Вам за что-нибудь поговорить, или другое?";
                link.l1 = "Мне нужно поговорить с Абигайль. У меня для неё письмо.";
                link.l1.go = "Abigile_kidnap";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "AbigileNextDayOver")
            {
                dialog.text = "День добрый, молодой человек. Что вам нужно? Ещё одно письмо для моей дочери?";
                link.l1 = "Хм... нет. А где Абигайль?";
                link.l1.go = "Abigile_GoOver";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "SolomonHistory")
            {
                dialog.text = "Кхм... Молодой человек! Вы сейчас, кажется, ведёте речь о моих деньгах?";
                link.l1 = "Да, минхер. О деньгах, которые вы спрятали на неком острове, о котором ни вы, ни Абигайль даже не помните - ни где он, ни каков он.";
                link.l1.go = "Solomon_history";
                break;
            }
            if (pchar.questTemp.HWIC.Self == "SolomonHistoryAfter")
            {
                dialog.text = "Хорошо. Я действительно помню и этот флейт, и его капитана. Я даже как-то видел его в порту нашего города. Флейт называется 'Лейден', капитана звали... кажется, Тофф Келлер.";
                link.l1 = "Отлично! Зацепка есть, теперь главное - отыскать этого капитана.";
                link.l1.go = "Solomon_history_3";
                pchar.questTemp.HWIC.Self = "SolomonHistoryEnd";
                break;
            }
            dialog.text = "Ну что вы опять хотите от бедного старого еврея?";
            link.l1 = "Добрый день. Да нет, ничего, просто поздороваться решил.";
            link.l1.go = "exit";
            break;
        }
        dialog.text = "Здравствуйте, молодой человек. Ну что вы хотите от бедного старого еврея?";
        link.l1 = "Добрый день. Да нет, ничего, просто поздороваться решил.";
        link.l1.go = "exit";
        NextDiag.TempNode = "First time";
        break;

        //-----------------------------------------------За Голландию-----------------------------------
    case "SolomonBonanza":
        PlaySound("VOICE\Russian\hambit\Solomon Shneur-03.wav");
        dialog.text = "И что вы из-под меня хочете? Разве я похож на человека, который знает больше, чем на самом деле? Разве я мог подумать в тот страшный для меня день, что у клочка земли среди волн есть свои полнота и долговязость? Или как это называют те, кто хочет казаться умнее старого еврея?\nОстров как остров, не считая меня с Аби, ни одного приличного человека. То есть вообще никого. Посредине грот. Вот в нём я свой сундук спрятал, чтобы он не достался этому извергу. А в сундуке том всё, что нажито непосильными трудами. И наша семейная реликвия – драгоценный череп деда... Вы мне можете не поверить, но спаслись мы исключительно благодаря ему\nО-о-о, это древняя штучка. Боже ж ты мой! Как трудно на склоне лет начинать всё сначала! Если б вы знали, молодой человек! Если б в только могли себе на минуточку это представить!";
        link.l1 = "Ох... Ладно. Как я понял, большего, чем я уже знаю, я от вас не добьюсь. Придётся действовать самому. До свидания!";
        link.l1.go = "SolomonBonanza_1";
        break;

    case "SolomonBonanza_1":
        DialogExit();
        pchar.questTemp.HWIC.Holl = "AbbySeekIsland";
        pchar.quest.Joakim_meeteng.win_condition.l1 = "location";
        pchar.quest.Joakim_meeteng.win_condition.l1.location = "Villemstad_town";
        pchar.quest.Joakim_meeteng.function = "Create_Joakim";
        break;

    case "SolomonBonanza_2": //отдаем всё
        dialog.text = "О, молодой человек, огромное вам спасибо! Вы не просто вернули деньги - вы восстановили доброе имя семьи Шнеуров! Минхер Роденбург по праву может гордиться, что у него на службе такие капитаны, как вы. Череп я передам минхеру Роденбургу - он обещал заплатить за него приличную сумму... А вас я хочу лично отблагодарить - примите на память этот оберег.";
        link.l1 = "Я рад за вас. Спасибо вам за подарок!";
        link.l1.go = "SolomonBonanza_4";
        RemoveItems(PChar, "SkullAztec", 1);
        AddMoneyToCharacter(pchar, -200000);
        GiveItem2Character(pchar, "amulet_7");
        AddDialogExitQuestFunction("DeleteJoakimFromRoom");
        ChangeCharacterComplexReputation(pchar, "nobility", 5);
        SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
        break;

    case "SolomonBonanza_3":
        dialog.text = "О, молодой человек, огромное вам спасибо! Вы не просто вернули деньги - вы восстановили доброе имя семьи Шнеуров! А череп... да и Бог с ним! Лукас по праву может гордиться, что у него на службе такие капитаны, как вы. Я хочу вас отблагодарить - примите на память этот амулет.";
        link.l1 = "Я рад за вас. Спасибо вам за подарок!";
        link.l1.go = "SolomonBonanza_4";
        AddMoneyToCharacter(pchar, -200000);
        GiveItem2Character(pchar, "obereg_10");
        pchar.questTemp.HWIC.Holl.ScullnotReturn = "true"; //признак для Лукаса
        ChangeCharacterComplexReputation(pchar, "nobility", -8);
        break;

    case "SolomonBonanza_4":
        DialogExit();
        pchar.questTemp.HWIC.Holl = "AbbyLeavesMarried"; //теперь можно говорить с Аби
        AddQuestRecord("Holl_Gambit", "1-32");
        break;

    case "SolomonBonanza_5":
        dialog.text = "Да вы что? Что вы такое говорите, молодой человек? Это правда? Ну-ка, дайте мне на них взглянуть...";
        link.l1 = "Пожалуйста. Вот ваши деньги. Они вновь принадлежат вам и Абигайль. Правда, никакого черепа вашего деда я не нашёл.";
        link.l1.go = "SolomonBonanza_6";
        break;

    case "SolomonBonanza_6":
        AddMoneyToCharacter(pchar, -200000);
        GiveItem2Character(pchar, "amulet_7");
        dialog.text = "Ох, денежки... да-да, денежки-денежки... На мои монеты совсем не похожи... Но какая разница, не правда ли, молодой человек? Не отвечайте, я знаю, что правда... Большое вам спасибо, что вернули мои сбережения. Я хочу вас отблагодарить - примите этот оберег. И идите, обрадуйте Аби!";
        link.l1 = "Спасибо, Соломон.";
        link.l1.go = "SolomonBonanza_4";
        pchar.questTemp.HWIC.Holl.LucasMoney = "true"; //признак для Лукаса
        ChangeCharacterComplexReputation(pchar, "nobility", 1);
        break;

        //-------------------------------------------за Англию------------------------------------------------

    case "Solomon_treasure":
        dialog.text = "Ой, я вас умоляю! Минхер Роденбург без пяти минут мой зять. Чтоб он сдох, как он мне нравится! Стоит мне закричать караул и сюда сбегутся все солдаты гарнизона!";
        link.l1 = "Да кто ты такой, чёрт побери?!";
        link.l1.go = "Solomon_treasure_1";
        break;

    case "Solomon_treasure_1":
        dialog.text = "Слушайте сюда, капитан, я её родный папа Соломон. Сделайте мне красиво, верните мне мои деньги и череп её деда. Старый еврей, конечно, не такой умный, как вы, но даже он понимает, что вы чего-то хочете от его дочери\nВозможно, что вас кто-то послал, и, если это тот капитан, за которого я думаю, то я скажу Аби всё в лучшем виде, и пусть вас больше не волнует этих глупостей. А сейчас её нет дома, моя девочка в это время молится Богу за грехи грешников, подобных вам.";
        link.l1 = "Ох, Господи! И как только таких земля носит... Прощай, старый скряга.";
        link.l1.go = "Solomon_treasure_2";
        break;

    case "Solomon_treasure_2":
        DialogExit();
        AddQuestRecord("Holl_Gambit", "2-17");
        pchar.questTemp.HWIC.Eng = "AbigileInChurch";
        sld = characterFromId("Abigile");
        sld.greeting = "abigile_3";
        ChangeCharacterAddressGroup(sld, "Villemstad_church", "goto", "goto1"); //Аби в церковь
        break;

        //----------------------------------------------против всех---------------------------------------------

    case "Abigile_kidnap":
        dialog.text = "Письмо? Ой, я вас умоляю! Минхер Роденбург без пяти минут мой зять. Чтоб он сдох, как я от него в восторге!";
        link.l1 = "Послушайте, мне всё равно, кто ваш зять. Мне нужно передать это письмо Абигайль. Вы в конце концов скажете, где мне её найти? И вообще, кто вы?";
        link.l1.go = "Abigile_kidnap_1";
        break;

    case "Abigile_kidnap_1":
        dialog.text = "Кто я? Я её родный папа Соломон... А вот вы мне что-то не нравитесь, молодой человек.";
        link.l1 = "Ну, знаете, я бы забеспокоился, если бы вы вдруг заявили, что я вам нравлюсь... Вы продолжите и дальше нести чепуху, или всё-таки позовёте Абигайль? Повторяю ещё раз: я вестовой, я принёс письмо для вашей дочери!";
        link.l1.go = "Abigile_kidnap_2";
        break;

    case "Abigile_kidnap_2":
        dialog.text = "Отдайте письмо мне. Я передам его дочке.";
        link.l1 = "Сожалею, но у меня приказ вручить это послание только ей лично в руки. Про папу в моём приказе ничего не было. Так что я вынужден повторить вопрос - где я могу найти Абигайль?";
        link.l1.go = "Abigile_kidnap_3";
        break;

    case "Abigile_kidnap_3":
        dialog.text = "Молодой человек, стоит мне закричать караул, и сюда сбегутся все солдаты гарнизона, если вы будете столь настырны...";
        link.l1 = "О, Господи! И что? Я нарушил закон? Не будьте смешны, папаша!";
        link.l1.go = "Abigile_kidnap_4";
        break;

    case "Abigile_kidnap_4":
        DialogExit();
        sld = characterFromId("Abigile");
        ChangeCharacterAddressGroup(sld, "Villemstad_houseSP2", "reload", "reload1");
        LAi_SetActorType(sld);
        LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

    case "Abigile_GoOver":
        dialog.text = "Вы издеваетесь? Своим посланием вы взбудоражили мою бедную девочку... Она решила отправиться к этому... прохвосту, этому капитанишке! Уплыла она с острова на попутном судне. Ах, что же делать теперь старому еврею! Сделайте милость, молодой человек, покиньте мой дом!";
        link.l1 = "Вот это да... Не дождалась, видимо...";
        link.l1.go = "Abigile_GoOver_1";
        break;

    case "Abigile_GoOver_1":
        DialogExit();
        AddQuestRecord("Holl_Gambit", "3-69");
        CloseQuestHeader("Holl_Gambit");
        pchar.questTemp.HWIC.Self = "end";
        pchar.questTemp.HWIC.Detector = "self_fail";
        break;

    case "Solomon_history":
        PlaySound("VOICE\Russian\hambit\Solomon Shneur-03.wav");
        dialog.text = "Каков он? Остров как остров, не считая меня с Аби, ни одного приличного человека. То есть вообще никого. Посредине грот. Вот в нём я свой сундук и спрятал, чтобы он не достался этому извергу. А в сундуке том всё, что нажито непосильными трудами...";
        link.l1 = "Скажите, Соломон, может вы помните, как назывался тот флейт, о котором рассказала ваша дочь, и как звали капитана?";
        link.l1.go = "Solomon_history_1";
        break;

    case "Solomon_history_1":
        dialog.text = "Эм-м... Ну, не знаю. А вы, молодой человек, зачем вам всё это надо?";
        link.l1 = "Я просто хочу помочь вашей дочери, Соломон. Я ничего не обещаю, но хочу хотя бы попробовать. После того, как с ней обошёлся мой бывший командир, будь он неладен, я считаю себя... обязанным хоть как-то, хоть попытаться, оказать возможное содействие в обустройстве её дальнейшей жизни.";
        link.l1.go = "Solomon_history_2";
        break;

    case "Solomon_history_2":
        dialog.text = "Ну, если так...";
        link.l1 = "";
        link.l1.go = "Solomon_history_3";
        pchar.questTemp.HWIC.Self = "SolomonHistoryNext";
        break;

    case "Solomon_history_3":
        DialogExit();
        sld = characterFromId("Abigile");
        LAi_SetActorType(sld);
        LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

    case "Solomon_thanks":
        dialog.text = "Молодой человек! Постойте!";
        link.l1 = "Да, Соломон?";
        link.l1.go = "Solomon_thanks_1";
        break;

    case "Solomon_thanks_1":
        dialog.text = "Молодой человек! Я хочу поблагодарить вас за то, что вы сделали для меня и моей дочки. Вы просто спасли нас. Простите за то, как я принял вас в первый раз, и за то, что сомневался в вашем желании помочь. Простите старого еврея... И, скажите: кроме денег, вы ничего в гроте не находили?";
        link.l1 = "Нет, Соломон. Кроме денег ничего не было. Прямо в гроте мне пришлось выдержать бой с головорезами ван Берга - пирата, который потопил ваш корабль. Может, им что-то удалось похитить... А что там должно было быть?";
        link.l1.go = "Solomon_thanks_2";
        break;

    case "Solomon_thanks_2":
        dialog.text = "Да... неважно. Одна древняя реликвия. Да и Бог с ним, с этим раритетом! Молодой человек! Ещё хотел спросить...";
        link.l1 = "Да?";
        link.l1.go = "Solomon_thanks_3";
        break;

    case "Solomon_thanks_3":
        dialog.text = "Вы... это... ну, я узнал немного про вас. Вы в большом почёте у нашего губернатора, да и вообще, видный капитан. Скажу по секрету - вы нравитесь моей дочке. Она сама мне так сказала. Может... ну, вы подумаете? Аби очень хорошая девушка, уверяю вас.";
        link.l1 = "Эх, Соломон... Не все так просто. Да, ваша дочка - просто сокровище. Берегите её.";
        link.l1.go = "Solomon_thanks_4";
        break;

    case "Solomon_thanks_4":
        dialog.text = "Вы подумайте, молодой человек! Подумайте и возвращайтесь!";
        link.l1 = "До свидания, Соломон.";
        link.l1.go = "Solomon_thanks_5";
        break;

    case "Solomon_thanks_5":
        DialogExit();
        LocatorReloadEnterDisable("Villemstad_houseSp2", "reload1", false);
        AddQuestRecord("Holl_Gambit", "3-65");
        NextDiag.CurrentNode = "First time";
        break;

    case "Solomon_poor":
        dialog.text = "Э-эх... Иногда, молодой человек, невозможно начать жизнь сначала... Провести старость в нищете - что может быть хуже?";
        link.l1 = "Мне жаль, Соломон. Крепитесь.";
        link.l1.go = "exit";
        NextDiag.TempNode = "Solomon_poor";
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