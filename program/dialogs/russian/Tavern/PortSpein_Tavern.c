// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
    case "quests":
        dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос, " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                                              "Опять вопросы будем задавать?", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я " + GetSexPhrase("передумал", "передумала") + "...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                                           "Да уж, действительно в третий раз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        //Цена чахотки
        if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin" && sti(pchar.money) >= 3000)
        {
            link.l1 = "Я слышал, что в вашем форте свирепствует чахотка, как думаешь, это не перекинется на город?";
            link.l1.go = "Consumption";
        }
        if (CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.Commandant") && pchar.questTemp.Consumption == "begin")
        {
            link.l1 = "А что ты можешь сказать о коменданте форта?";
            link.l1.go = "Consumption_8";
        }
        if (!CheckAttribute(npchar, "quest.Consumption_1") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
        {
            link.l1 = "Скажи, имя 'Хуан' тебе что-нибудь говорит?";
            link.l1.go = "Consumption_12";
        }
        if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
        {
            link.l1 = "Послушай, в апреле 1654 года в ваш порт заходил фрегат под командованием капитана Мигеля Дичозо. Он потом исчез. Ничего не расскажешь на эту тему?";
            link.l1.go = "guardoftruth";
        }
        break;

    //--> Цена чахотки
    case "Consumption":
        dialog.text = "Комендант утверждает, что опасности нет. Разве что только для тех, кого угораздило попасть в казематы, или – для тех, кто слишком любопытен. Я не из таких, уж простите.";
        link.l1 = "Да неужели? Хозяин портовой таверны не желает прислушиваться к сплетням – это что-то новенькое! Может быть, звон песо вернет тебе любознательность?";
        link.l1.go = "Consumption_1";
        break;

    case "Consumption_1":
        dialog.text = "Серебро, оно, конечно, заманчиво, но собственная шкура как-то милее. Может вам, господин хороший, о чем другом порассказать? Я же завсегда с радостью – только намекните!";
        link.l1 = "Значит, вот так вопрос стоит... Хорошо – в этом кошеле три тысячи, и мы с тобой мило побеседуем о погоде, по рукам?";
        link.l1.go = "Consumption_2";
        break;

    case "Consumption_2":
        AddMoneyToCharacter(pchar, -3000);
        dialog.text = "Ох и настойчивый же вы, сеньор. Только запомните – не было этого разговора.(шепчет) Я уже не раз слышал за последний год, как люди сгорают от чахотки в наших тюрьмах. Кто-то винит власти, кто-то Бога или Дьявола, но большинство лишь диву дается – как быстро уносит жизни эта проклятущая болезнь. Бывает, здорового человека посадят, а через неделю-другую - уж и нет его. Раз, и все...";
        link.l1 = "Однако... Целый год, говоришь? И что, никто ничего так и не предпринял?";
        link.l1.go = "Consumption_3";
        break;

    case "Consumption_3":
        dialog.text = "А кому оно надо то, сеньор? До тех, кто в тюрьме, никому дела то и нет – отбросы общества, как говорят чистоплюи в бархате. Был в городе один доктор, что в тюрьме работал – вроде как пытался как-то лечить этих бедняг, но и сам вскоре умер – заразился видать - и все\nСейчас комендант просто туда никого не пускает, а властям и наплевать – меньше расходов на кормежку.";
        link.l1 = "Занятно, но чем эта болезнь, запертая за надежными стенами, тебя так пугает, что мы шепчем, словно монашки о сладости греха?";
        link.l1.go = "Consumption_4";
        break;

    case "Consumption_4":
        dialog.text = "Сложно сказать, но был тут один тип. Контрабандой промышлял, и угодил в мешок почти на полгода, пока его не выкупили дружки. Ну, знаете - золотишка кому надо отмеряли, подождали, сколько сказали, и парень вышел. Да только с тех пор он малость 'не в фарватере' был...";
        link.l1 = "То есть 'грот заполоскало'?";
        link.l1.go = "Consumption_5";
        break;

    case "Consumption_5":
        dialog.text = "Вроде как. Никакого толку с него уже дружкам не было – сидел и напивался день за днем, словно забыть что-то хотел. А как напьется, что еле языком ворочает, начинал нести что-то про чахотку, которая, мол, людей забирает в тишине\nИменно так - 'забирает в тишине', он говорил. И, по словам его, выходило, что 'чахотка' та – самое жуткое, что с человеком в камерах случиться может.";
        link.l1 = "Ну нес пьяница всякую чепуху, что в том такого?";
        link.l1.go = "Consumption_6";
        break;

    case "Consumption_6":
        if (CheckAttribute(pchar, "questTemp.Consumption.Commandant"))
        {
            dialog.text = "Ничего, если не смотреть на то, что он становился смелее и говорил все чаще, а потом – раз, и все. Ножом по горлу и в канаву... а кто, да за что – мне безразлично.";
            link.l1 = "А что ты можешь сказать о коменданте?";
            link.l1.go = "Consumption_8";
        }
        else
        {
            dialog.text = "Ничего, если не смотреть на то, что он становился смелее и говорил все чаще, а потом – раз, и все. Ножом по горлу и в канаву... а кто, да за что – мне безразлично.(повышает голос) Да, такие уж тут берега, сеньор, глядеть надо в оба – шторма налетают с Больших Антил в мгновение ока - раз, и все! Доброго ветра, сеньор, спасибо что поговорили!";
            link.l1 = "Шторма... да. И тебе спасибо.";
            link.l1.go = "Consumption_7";
        }
        pchar.questTemp.Consumption.Contra = "true";
        break;

    case "Consumption_7":
        DialogExit();
        npchar.quest.Consumption = "true";
        AddQuestRecord("Consumption", "2");
        break;

    case "Consumption_8":
        dialog.text = "А что о нем говорить? Полковник, прибыл из Европы пару лет назад, получив это место. Вроде бы как был понижен там, в Старом Свете, за какие-то махинации. Не знаю, правда ли – но слухи ходили первое время. Впрочем, о ком их не ходит, да?";
        link.l1 = "Махинации, говоришь... Интересно. Что-нибудь еще?";
        link.l1.go = "Consumption_9";
        break;

    case "Consumption_9":
        dialog.text = "Ну, как вам сказать... Полковник производит впечатление человека, всерьез озабоченного собственной безопасностью. У нас, конечно, места не самые тихие – пираты, разбойники, а, бывает, и индейцы заплывают поохотиться – но сеньор комендант никуда не выходит без пары-тройки солдат\nА весь свой особняк, здесь, в городе, превратил в небольшую крепость – вооружил всю прислугу, и запрещает им открывать ставни.";
        link.l1 = "Но ведь днем он на службе в тюрьме, так?";
        link.l1.go = "Consumption_10";
        break;

    case "Consumption_10":
        dialog.text = "Да, а особняк стоит, словно в ожидании осады или вторжения. Впрочем, сеньор комендант вообще не часто в него возвращается – видимо, в настоящей крепости ему спокойнее, хе-хе.";
        link.l1 = "Благодарю, ты мне очень помог. До встречи, " + npchar.name + "!";
        link.l1.go = "Consumption_11";
        break;

    case "Consumption_11":
        DialogExit();
        if (CheckAttribute(npchar, "quest.Consumption"))
            AddQuestRecord("Consumption", "4");
        else
            AddQuestRecord("Consumption", "5");
        DeleteAttribute(pchar, "questTemp.Consumption.Commandant");
        pchar.questTemp.Consumption = "current";
        break;

    case "Consumption_12":
        dialog.text = "Хуан? Который из них? Тут их много – обычно к имени прибавляют фамилию, или, хотя бы прозвище...";
        link.l1 = "Мне только что подумалось... Возможно, прозвище его 'Чахотка', не слыхал?";
        link.l1.go = "Consumption_13";
        break;

    case "Consumption_13":
        dialog.text = "Боже мой, вы опять об этом! Нет, слава Богу, не слышал, клянусь! А теперь, давайте сменим тему, прошу!";
        link.l1 = "Хорошо-хорошо, только не волнуйся ты так...";
        link.l1.go = "exit";
        pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan) + 1;
        if (sti(pchar.questTemp.Consumption.AskJuan) == 3)
        {
            pchar.quest.Consumption2.win_condition.l1 = "location";
            pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
            pchar.quest.Consumption2.function = "Consumption_CreateSergio";
        }
        npchar.quest.Consumption_1 = "true";
        break;
        //<-- Цена чахотки

    case "guardoftruth":
        dialog.text = "Помню такого. Он сам заходил в мою таверну, правда, ничего не рассказывал. Просто выпил немного рома, пошушукался с посетителями и ушел. Очень был мрачный и суровый, весь в напряжении, словно в ожидании какой-то невзгоды\nДа и команда на том фрегате была под стать ему - все как один из наемников, угрюмые, хмурые, и эфесы сабель все поглаживали. Поговаривали, что на том фрегате были полные трюмы золота и драгоценных каменьев, но я не верю в подобные сказки - ценные грузы перевозят обычно в составе больших караванов\nПостояли они тут день - и ушли. В Европу собирались. А больше ничего я про них и не знаю.";
        link.l1 = "Понятно. Ну, хоть что-то...";
        link.l1.go = "exit";
        npchar.quest.guardoftruth = "true";
        AddQuestRecord("Guardoftruth", "40");
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}