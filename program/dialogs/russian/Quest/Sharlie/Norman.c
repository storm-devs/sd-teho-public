// Абрахам Норман
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    int i, iTemp;
    string sTemp;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
    case "First time":
        dialog.text = "Ты что-то хотел?";
        link.l1 = "Да нет, ничего.";
        link.l1.go = "exit";
        NextDiag.TempNode = "First time";
        break;

    case "norman_us":
        if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
        {
            dialog.text = LinkRandPhrase("Что тебе, дружок? Иди своей дорогой, занимайся делами-делишками, а от меня отстань.", "Привет-привет, паренек. Гуляешь? Вот и гуляй себе дальше, и отстань от дядюшки Абрахама. Он тоже гуляет, морским воздухом дышит.", "Здравствуй, парнишка. Хочешь поболтать? Но вот ведь незадача: я не в настроении разговаривать. Так что поищи себе другого собеседника. Зайди в таверну, рому выпей...");
            link.l1 = "Послушай, Абрахам, ты не встречал недавно на Исла Тесоро человека по имени Мигель Дичозо? Он тут вроде известная птица.";
            link.l1.go = "tieyasal";
            break;
        }
        dialog.text = NPCStringReactionRepeat(LinkRandPhrase("Что тебе, дружок? Иди своей дорогой, занимайся делами-делишками, а от меня отстань.", "Привет-привет, паренек. Гуляешь? Вот и гуляй себе дальше, и отстань от дядюшки Абрахама. Он тоже гуляет, морским воздухом дышит.", "Здравствуй, парнишка. Хочешь поболтать? Но вот ведь незадача: я не в настроении разговаривать. Так что поищи себе другого собеседника. Зайди в таверну, рому выпей..."), LinkRandPhrase("Морячок, ты туго соображаешь? Я вроде ясно объяснил.", "Парень, иди проспись. А то, видать, слышишь плоховато.", "Паренек, ты что - дурачок? Я же вроде доступно все расписал."), "Приятель, не доводи до греха. Я столько сухопутных крыс на своем веку перерезал, что одной больше, одной меньше - уже неважно.", "Ну все, ты меня достал. Теперь или доставай свою ржавую саблю, или беги со всех ног. Второе - вернее...", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat("Хорошо, приятель. Не буду тебе мешать.", "Да-да, я понял. Просто вспомнил тут...", "Ух, да ты, видать - Гроза морей! Ладно, ухожу.", "Что?!", npchar, Dialog.CurrentNode);
        link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
        NextDiag.TempNode = "norman_us";
        break;

    case "norman_fes":
        if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
        {
            dialog.text = LinkRandPhrase("Что тебе, дружок? Иди своей дорогой, занимайся делами-делишками, а от меня отстань.", "Привет-привет, паренек. Гуляешь? Вот и гуляй себе дальше, и отстань от дядюшки Абрахама. Он тоже гуляет, морским воздухом дышит.", "Здравствуй, парнишка. Хочешь поболтать? Но вот ведь незадача: я не в настроении разговаривать. Так что поищи себе другого собеседника. Зайди в таверну, рому выпей...");
            link.l1 = "Послушай, Абрахам, ты не встречал недавно на Исла Тесоро человека по имени Мигель Дичозо? Он тут вроде известная птица.";
            link.l1.go = "tieyasal";
            break;
        }
        switch (drand(5))
        {
        case 0:
            dialog.text = "Стоять! Я губернатор этого острова. Ты что, не веришь мне?!";
            link.l1 = "Конечно верю! Кто же не знает губернатора Исла-Тесоро...";
            link.l1.go = "norman_fes0_fight";
            link.l2 = "Ха, ты еще адмиралом назовись, вот тогда точно поверю!";
            link.l2.go = "norman_fes0_peace";
            break;

        case 1:
            dialog.text = "Руки по швам! Перед тобой адмирал Барбариго! Ты что, не узнал мою знаменитую саблю?";
            link.l1 = "Виноват, господин адмирал! Впредь буду внимательнее.";
            link.l1.go = "norman_fes1_peace";
            link.l2 = "Сабля у тебя знатная. Жаль, дураку досталась.";
            link.l2.go = "norman_fes1_fight";
            break;

        case 2:
            dialog.text = "Я, видите ли, здесь в изгнании, жду новостей от генерала Монка. Прошу не разглашать мое королевское инкогнито. У разведки Кромвеля длинные уши.";
            link.l1 = "Конечно, Ваше Величество. Никто не узнает, что Карл II прячется в Вест-Индии.";
            link.l1.go = "norman_fes2_fight";
            link.l2 = "Ну а я тогда - римский папа Иннокентий X.";
            link.l2.go = "norman_fes2_peace";
            break;

        case 3:
            dialog.text = "Куда ты пропал, Блейз? Я ищу тебя второй день. Ты совсем забыл своего папу Николаса!";
            link.l1 = "Не до тебя, отец! Дел по горло.";
            link.l1.go = "norman_fes3_peace";
            link.l2 = "Вы обознались, уважаемый. Меня зовут " + GetFullName(pchar) + ".";
            link.l2.go = "norman_fes3_fight";
            break;

        case 4:
            dialog.text = "Т-с-с... Я Дэви Джонс. Скажи, ты боишься смерти?";
            link.l1 = "Конечно, мистер Джонс, особенно с похмелья.";
            link.l1.go = "norman_fes4_fight";
            link.l2 = "Ста смертям не бывать, а одной не миновать.";
            link.l2.go = "norman_fes4_peace";
            break;

        case 5:
            dialog.text = "Я пьесу новую закончить тороплюсь. Ты должен мне помочь продолжить фразу 'Быть, иль не быть?!'";
            link.l1 = "Вот, в чем единственный вопрос! Сносить ли нам и впредь обиды свысока...";
            link.l1.go = "norman_fes5_fight";
            link.l2 = "Конечно 'пить', но я не удивлюсь, когда в борделе подцеплю заразу!";
            link.l2.go = "norman_fes5_peace";
            break;
        }
        break;

    case "norman_fes0_fight":
        dialog.text = "Какой к дьяволу 'Тесоро'?! Ты бы его еще Бермудами обозвал! Запомни, в честь меня этот остров называется Норман-Айленд. Придется поучить тебя географии...";
        link.l1 = "Э! Да ты чего?!";
        link.l1.go = "fight";
        NextDiag.TempNode = "norman_fight_again";
        break;

    case "norman_fes0_peace":
        dialog.text = "Ты прав, матрос. На самом деле я адмирал Барбариго, но это строго между нами. Готовься к походу, скоро выступаем. Это тебе пригодится.";
        link.l1 = "Премного благодарен!";
        link.l1.go = "norman_fes0_exit";
        break;

    case "norman_fes0_exit":
        DialogExit();
        NextDiag.CurrentNode = "norman_fes_again";
        PlaySound("interface\important_item.wav");
        if (GetDataDay() == 12)
        {
            GiveItem2Character(pchar, "pistol2");
            Log_Info("Вы получили трехствольный дробовик");
        }
        else
        {
            if (GetDataDay() == 23 && GetDataMonth() == 2)
            {
                GiveItem2Character(pchar, "mushket1");
                Log_Info("Вы получили фитильный мушкет");
            }
            else
            {
                GiveItem2Character(pchar, "cartridge");
                Log_Info("Вы получили бумажный патрон");
            }
        }
        break;

    case "norman_fes1_fight":
        dialog.text = "Сейчас посмотрим, кто из нас дурак. Защищайся!";
        link.l1 = "Ты что, серьезно?!";
        link.l1.go = "fight";
        NextDiag.TempNode = "norman_fight_again";
        break;

    case "norman_fes1_peace":
        dialog.text = "То-то же! На вот, выпей за мое здоровье.";
        link.l1 = "Есть, адмирал!";
        link.l1.go = "norman_fes1_exit";
        break;

    case "norman_fes1_exit":
        DialogExit();
        NextDiag.CurrentNode = "norman_fes_again";
        PlaySound("interface\important_item.wav");
        if (GetDataDay() == 13)
        {
            GiveItem2Character(pchar, "gold_dublon");
            Log_Info("Вы получили золотой дублон");
        }
        else
        {
            if (GetDataDay() == 1 && GetDataMonth() == 4)
            {
                GiveItem2Character(pchar, "chest");
                Log_Info("Вы получили сундучок с дублонами");
            }
            else
            {
                AddMoneyToCharacter(pchar, 5);
            }
        }
        break;

    case "norman_fes2_fight":
        dialog.text = "Я же просил не разглашать мое имя! Теперь придется убрать тебя, как опасного свидетеля...";
        link.l1 = "Только этого мне не хватало!";
        link.l1.go = "fight";
        NextDiag.TempNode = "norman_fight_again";
        break;

    case "norman_fes2_peace":
        dialog.text = "Простите, Ваше Преосвященство! Не признал я вас в этом обличии. Соблаговолите принять скромный дар от истинного католика.";
        link.l1 = "Маразм крепчал...";
        link.l1.go = "norman_fes2_exit";
        break;

    case "norman_fes2_exit":
        DialogExit();
        NextDiag.CurrentNode = "norman_fes_again";
        PlaySound("interface\important_item.wav");
        if (GetDataDay() == 14)
        {
            GiveItem2Character(pchar, "amulet_10");
            Log_Info("Вы получили амулет 'Чудотворец'");
        }
        else
        {
            if (GetDataDay() == 25 && GetDataMonth() == 12)
            {
                GiveItem2Character(pchar, "totem_04");
                Log_Info("Вы получили талисман 'Клеврет'");
            }
            else
            {
                GiveItem2Character(pchar, "Mineral3");
                Log_Info("Вы получили восковую свечу");
            }
        }
        break;

    case "norman_fes3_fight":
        dialog.text = "Все ко мне! Я поймал лазутчика, похожего на моего сына! Его наверняка подослал Томас, чтобы выбить мне второй глаз!";
        link.l1 = "Отвали от меня, придурок!";
        link.l1.go = "fight";
        NextDiag.TempNode = "norman_fight_again";
        break;

    case "norman_fes3_peace":
        dialog.text = "Ты устал и плохо выглядишь, сынок. На-ка вот, подлечись.";
        link.l1 = "Спасибо!";
        link.l1.go = "norman_fes3_exit";
        break;

    case "norman_fes3_exit":
        DialogExit();
        NextDiag.CurrentNode = "norman_fes_again";
        PlaySound("interface\important_item.wav");
        if (GetDataDay() == 15)
        {
            GiveItem2Character(pchar, "potion4");
            Log_Info("Вы получили микстуру");
        }
        else
        {
            if (GetDataDay() == 19 && GetDataMonth() == 6)
            {
                GiveItem2Character(pchar, "talisman8");
                Log_Info("Вы получили оберег 'Скорпион'");
            }
            else
            {
                GiveItem2Character(pchar, "potion1");
                Log_Info("Вы получили лечебную эссенцию")
            }
        }
        break;

    case "norman_fes4_fight":
        dialog.text = "Ее не надо бояться, дружок. Смотри, умирать совсем не страшно...";
        link.l1 = "А ты, похоже, не шутишь!";
        link.l1.go = "fight";
        NextDiag.TempNode = "norman_fight_again";
        break;

    case "norman_fes4_peace":
        dialog.text = "Стало быть, не боишься. Я так и знал. Вот тебе за храбрость!";
        link.l1 = "Забавный ты старик, однако...";
        link.l1.go = "norman_fes4_exit";
        break;

    case "norman_fes4_exit":
        DialogExit();
        NextDiag.CurrentNode = "norman_fes_again";
        PlaySound("interface\important_item.wav");
        if (GetDataDay() == 17)
        {
            GiveItem2Character(pchar, "cirass6");
            Log_Info("Вы получили жилет бретера");
        }
        else
        {
            if (GetDataDay() == 1 && GetDataMonth() == 1)
            {
                GiveItem2Character(pchar, "cirass3");
                Log_Info("Вы получили парадную кирасу");
            }
            else
            {
                GiveItem2Character(pchar, "Mineral18");
                Log_Info("Вы получили табак");
            }
        }
        break;

    case "norman_fes5_fight":
        dialog.text = "Хреновый ты поэт, матрос, быть может, твой клинок проворней языка?";
        link.l1 = "Карамба! А сабля-то у тебя отнюдь не бутафорская!";
        link.l1.go = "fight";
        NextDiag.TempNode = "norman_fight_again";
        break;

    case "norman_fes5_peace":
        dialog.text = "Ух ты! Как у тебя складно получилось! Это тебе за фантазию!";
        link.l1 = "Если что, обращайся.";
        link.l1.go = "norman_fes5_exit";
        break;

    case "norman_fes5_exit":
        DialogExit();
        NextDiag.CurrentNode = "norman_fes_again";
        PlaySound("interface\important_item.wav");
        PlaySound("interface\important_item.wav");
        if (GetDataDay() == 16)
        {
            GiveItem2Character(pchar, "potionrum");
            Log_Info("Вы получили бутылку рома");
        }
        else
        {
            if (GetDataDay() == 28 && GetDataMonth() == 11)
            {
                GiveItem2Character(pchar, "totem_01");
                Log_Info("Вы получили тотем 'Луженая глотка'");
            }
            else
            {
                GiveItem2Character(pchar, "Mineral17");
                Log_Info("Вы получили стеклянный флакон");
            }
        }
        break;

    case "norman_fight_again":
        dialog.text = "А-а, я тебя узнал! Ха-ха!";
        link.l1 = "Опять...";
        link.l1.go = "fight";
        break;

    case "norman_fes_again":
        dialog.text = "Все-все, приятель, поговорили-договорили, и ладно. Гуляй себе дальше.";
        link.l1 = "Как скажешь...";
        link.l1.go = "exit";
        NextDiag.TempNode = "norman_fes_again";
        break;

    case "tieyasal":
        dialog.text = "Дичозо? А зачем же тебе он понадобился, а?";
        link.l1 = "Ну нужен он мне. Просто нужен человек. Так ты видел его?";
        link.l1.go = "tieyasal_1";
        link.l2 = "Как - зачем? Мигель - мой старинный приятель, можно сказать - друг. Он должен...";
        link.l2.go = "tieyasal_2";
        link.l3 = "Хочу, чтобы он подогнал мне новую посудину, как сделал когда-то для Акулы Додсона.";
        link.l3.go = "tieyasal_3";
        if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
        {
            link.l4 = "Мигель Дичозо убил одного человека. Поэтому я и разыскиваю его.";
            link.l4.go = "tieyasal_4";
        }
        npchar.quest.Tieyasal = "true";
        break;

    case "tieyasal_1":
        dialog.text = "Просто нужен... просто-просто нужен! Мигель Дичозо - и просто нужен! Нет, не видал я его. Давно не видал. Ничем не помогу тебе, матросик.";
        link.l1 = "Гм... Ладно, пока.";
        link.l1.go = "exit";
        break;

    case "tieyasal_2":
        dialog.text = "Друг, значит, говоришь... Что-то тут друзей всяких немеряно развелось. Сейчас одним меньше станет...";
        link.l1 = "Э, старый, ты чего?";
        link.l1.go = "fight";
        NextDiag.TempNode = "norman_fight_again";
        break;

    case "tieyasal_3":
        dialog.text = "Да, на такие дела Дичозо мастер, что ни говори. Но я не знаю, где он. Был - да сплыл. Так что ступай к Алексусу, матросик, он сколотит тебе отличную лоханку.";
        link.l1 = "Хм... Спасибо за совет, приятель.";
        link.l1.go = "exit";
        break;

    case "tieyasal_4":
        dialog.text = "И кого же прикончил Дичозо, что ты занялся его поисками, а, дружище?";
        link.l1 = "";
        Link.l1.edit = 8;
        link.l1.go = "tieyasal_5";
        break;

    case "tieyasal_4_1":
        dialog.text = "В смысле - какого именно Шарпа он убил? Шарпов, знаешь ли, много.";
        link.l1 = "";
        Link.l1.edit = 8;
        link.l1.go = "tieyasal_5";
        break;

    case "tieyasal_5":
        sTemp = GetStrSmallRegister(dialogEditStrings[8]);
        if (sTemp == "блейз шарп" || sTemp == "блейза шарпа")
        {
            dialog.text = "Чш-ш-ш...(оглядывается) Так ты тоже считаешь, что Блейза Шарпа убил Дичозо?";
            link.l1 = "Ну да. У меня есть на то не просто подозрения, а доказательства. Записи в судовом журнале...";
            link.l1.go = "tieyasal_6";
            break;
        }
        if (sTemp == "шарп" || sTemp == "шарпа")
        {
            dialog.text = "C этого места поподробнее, матросик...";
            link.l1 = "В смысле - поподробнее?";
            link.l1.go = "tieyasal_4_1";
            break;
        }
        dialog.text = "А-а... Ну убил и убил. У нас тут знаешь сколько убивцев расхаживает? Да каждый первый встречный! Не, матросик, не видал я Дичозо уже давно. Ничем не помогу.";
        link.l1 = "Жаль...";
        link.l1.go = "exit";
        break;

    case "tieyasal_6":
        dialog.text = "Говори тише, приятель. Как там тебя зовут, а? Запамятовал я что-то...";
        link.l1 = "Капитан " + GetFullName(pchar) + ".";
        link.l1.go = "tieyasal_7";
        break;

    case "tieyasal_7":
        dialog.text = "Вот что, капитан " + pchar.name + ". Именно Дичозо убил беднягу Блейза. Я сам видел это, да-да. Но мне никто не поверил. Понимаешь, меня тут все считают чокнутым. Своим, но - чокнутым. А ведь когда-то я был лучшим абордажником в команде самого Николаса Шарпа! Эх, вот были времена! Но потом я потерял свои когти, копыто и линзу, и был списан на берег\nТак, о чем это я? Ах да! Все решили, что это сделал Акула, но это не так. Нет-нет. Там был акулий зуб, талисман Додсона, но это Дичозо его подбросил\nОн наверняка стащил его у Стивена, когда они вместе ходили в море добывать фрегат, 'Фортуну'. Мне не спалось той ночью, и я вышел погулять. И я видел, как Дичозо забрался через окно на второй этаж резиденции Шарпа, и как оттуда донесся хриплый крик и стон. И я видел, как Дичозо вылез назад, а с рукавов его камзола капала кровь\nМне не поверили, нет-нет. Потому что Дичозо не было на острове в тот день, а Акула - был. И зуб его нашли. А Дичозо был, точно был! Просто никто об этом не знал. Счастливчик очень хитрый и страшный человек...";
        link.l1 = "Ты не первый, кто назвал Дичозо 'Счастливчиком'. Почему? Это кличка?";
        link.l1.go = "tieyasal_8";
        break;

    case "tieyasal_8":
        dialog.text = "Ты что, паренек, не знаешь испанского? 'Дичозо' с языка папистов - 'счастливый'. Счастливчик Мигель, Мигель Счастливчик, вот как это называется.";
        link.l1 = "Мигель Счастливчик?.. Хм. Что-то это мне напоминает. Вот только не могу понять - что. Такое знакомое сочетание...";
        link.l1.go = "tieyasal_9";
        break;

    case "tieyasal_9":
        dialog.text = "Но хоть он и Дичозо, я не думаю, что он - испанец. Нет-нет, не испанец. Хотя и похож.";
        link.l1 = "А кто же он? Англичанин, француз?";
        link.l1.go = "tieyasal_10";
        break;

    case "tieyasal_10":
        dialog.text = "Я не об этом, матросик... Ой, прости - капитан. Да, по-хранцузски Дичозо шпарит знатно, не хуже тебя. И по-англицки тоже. Однако в его жилах течет индейская кровь. Я таких много повидал в своей жизни. Это явно не видно, но он полукровка. Я тебе точно говорю.";
        link.l1 = "А по-индейски он не говорит?";
        link.l1.go = "tieyasal_11";
        break;

    case "tieyasal_11":
        dialog.text = "А пес его разберет. Может, и говорит. Хотя - точно, говорит! Он постоянно вворачивал фразы на непонятном языке, и делал при этом страшно ученый вид и раздувал щеки. Вот, например, скажет что-то вроде: когито эрго сум! А потом выкатит глаза и смотрит за реакцией матросиков. Или вот так он часто восклицал: аут цезар, аут нихил! Он еще много чего лопотал, да я не помню всего.";
        link.l1 = "Это не индейский язык. Это латынь. Латынь... Латынь?! Черт возьми!!";
        link.l1.go = "tieyasal_12";
        break;

    case "tieyasal_12":
        dialog.text = "Ты чего запрыгал, парень? Чего орешь? Никак змея укусила? Где она?";
        link.l1 = "Да как же я сразу-то не догадался! Все лежало на поверхности! Латынь! Мигель... Мишель Счастливчик!!";
        link.l1.go = "tieyasal_13";
        break;

    case "tieyasal_13":
        dialog.text = "Прекрати, наконец, вопить - люди смотрят. Что с тобой, матросик... прости - капитан?";
        link.l1 = "Я знаю, кто есть Мигель Дичозо на самом деле. Он действительно не испанец. Он француз! Да как же я был слеп!";
        link.l1.go = "tieyasal_14";
        break;

    case "tieyasal_14":
        dialog.text = "Не-е, дружочек, он не хранцуз. Я тебе говорю - полукровка. Его белый папашка обрюхатил индианочку, из араваков или мискито, из карибов или даже ица, а от нее и появился на свет Божий Мигель Дичозо. Ты этого не видишь, а я вижу. У него в глазах написано...";
        link.l1 = "Оставим вопрос о его происхождении. Где он, Абрахам?! Он был тут?!";
        link.l1.go = "tieyasal_15";
        break;

    case "tieyasal_15":
        dialog.text = "Тс-с... Да, он был тут. Но он ушел. Его сейчас нет на Исла Тесоро.";
        link.l1 = "Зачем он сюда приходил? Какой у него корабль?";
        link.l1.go = "tieyasal_16";
        break;

    case "tieyasal_16":
        dialog.text = "Корабль у него - галеон. Большой военный галеон. А зачем он был тут... ходил, вынюхивал что-то, расспрашивал. Но я подслушал его разговоры, да-да! Он искал какого-то Шарля де Мора. Да, вот так и говорил - Шарля де Мора. Стой, так это же ты - Шарль де Мор! Так он тебя искал, дружочек.";
        link.l1 = "А ты не знаешь, зачем?";
        link.l1.go = "tieyasal_17";
        break;

    case "tieyasal_17":
        dialog.text = "Ну уж точно не для того, чтобы выпить с тобой рому. Он давал наущения схватить тебя. Да-да, схватить! Ты в опасности, капитан!";
        link.l1 = "Не сомневаюсь...";
        link.l1.go = "tieyasal_18";
        break;

    case "tieyasal_18":
        dialog.text = "А ты? Зачем ты его ищешь? О, понимаю, понимаю: чтобы убить его! Убей его, убей мерзавца! Отомсти за Блейза Шарпа! Блейз был отличным парнем. Я помню его еще ребенком - весь в Николаса.";
        link.l1 = "Куда отправился Дичозо?";
        link.l1.go = "tieyasal_19";
        break;

    case "tieyasal_19":
        dialog.text = "Он собирался в Блювельд. Сказал, что Шарля де Мора следует искать под крылышком у Лесного Дьявола. Но он оставил здесь своих людей... стой, тебя ведь уже заметили!";
        link.l1 = "Кто заметил?";
        link.l1.go = "tieyasal_20";
        break;

    case "tieyasal_20":
        dialog.text = "Люди Дичозо. Он приказал караулить тебя здесь. О, я знаю, знаю! Будь внимателен, капитан: у рифов Исла Тесоро стоят корабли, и стоят они по твою душу. Капитан их очень хитер. Не дай себя обмануть.";
        link.l1 = "Я постараюсь...";
        link.l1.go = "tieyasal_21";
        break;

    case "tieyasal_21":
        dialog.text = "И еще: вот, возьми мою саблю. Бери-бери, она тебе понадобится. Это сторта самого капитана Барбариго, да-да. Отличный клинок. Лучший на архипелаге. Не стесняйся, бери. Блейз Шарп должен быть отомщен!";
        link.l1 = "Ну, спасибо, Абрахам.";
        link.l1.go = "tieyasal_22";
        break;

    case "tieyasal_22":
        RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
        RemoveItems(npchar, "blade_29", 1);
        sTemp = GetBestGeneratedItem("blade_29");
        GiveItem2Character(pchar, sTemp);
        sld = ItemsFromID(sTemp);
        sld.Balance = 1.0;
        GiveItem2Character(npchar, "blade_19");
        EquipCharacterbyItem(npchar, "blade_19");
        Log_Info("Вы получили сторту Барбариго");
        PlaySound("interface\important_item.wav");
        dialog.text = "А теперь иди. Иди, ибо за тобой следят. Делай умный вид. Или глупый. Неважно. Но будь осторожен!";
        link.l1 = "Спасибо, дружище. Ты даже не представляешь, как мне помог. Удачи!";
        link.l1.go = "tieyasal_23";
        break;

    case "tieyasal_23":
        DialogExit();
        pchar.questTemp.Tieyasal.MigelKnow = "true";
        AddQuestRecord("Tieyasal", "4");
        pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
        pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
        pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
        pchar.questTemp.Tieyasal = "islatesoro";
        break;

    case "fight":
        iTemp = 20 - sti(GetCharacterItem(npchar, "potion2"));
        TakeNItems(npchar, "potion2", iTemp);
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
        LAi_group_Attack(NPChar, Pchar);
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;
    }
}