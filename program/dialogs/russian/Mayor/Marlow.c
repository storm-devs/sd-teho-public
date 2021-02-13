// Захария Марлоу, Черный Пастор, Пуэрто-Принсипе, Куба
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    string sLoc;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    // ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
            case "repeat":
                if (npchar.angry.name == "Firsttime")
                    Dialog.CurrentNode = "AngryRepeat_1";
                if (npchar.angry.name == "I_know_you_good")
                    Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    } //<-- блок angry

    switch (Dialog.CurrentNode)
    {
    case "First time":
        dialog.text = NPCStringReactionRepeat("" + GetSexPhrase("У тебя дело ко мне? Нет? Тогда вали отсюда!", "Ха, " + pchar.name + "! У тебя дело ко мне? Нет? Тогда не отвлекай меня.") + "",
                                              "Я кажется ясно выразился.", "Хотя я выразился и ясно, но ты продолжаешь отвлекать меня!",
                                              "Та-а-ак, это уже похоже на грубость, меня это утомило.", "repeat", 3, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat("Уже ухожу.",
                                           "Конечно, Пастор...",
                                           "Извини, Пастор...",
                                           "Ой...", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        NextDiag.TempNode = "First time";

        if (sti(pchar.GenQuest.Piratekill) > 20)
        {
            dialog.text = RandPhraseSimple("У тебя крыша поехала? Вообразил себя мясником? Все пираты злы на тебя, приятель, так что лучше тебе убраться отсюда побыстрее.", "Ты, приятель, похоже, из ума выжил. Руки чесались сильно? Теперь не обессудь - здесь тебе делать нечего. Вали отсюда побыстрее!");
            link.l1 = RandPhraseSimple("Послушай, я хочу исправить ситуацию...", "Помоги мне решить эту проблему...");
            link.l1.go = "pirate_town";
            break;
        }

        //--> Сага
        if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && !CheckAttribute(npchar, "quest.sharkbegin"))
        {
            link.l1 = "Я пытаюсь разыскать Акулу Додсона. Говорят, ты последний, кто видел его. Можешь как-то помочь мне в этом деле?";
            link.l1.go = "Shark";
        }
        if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax" && CheckCharacterItem(pchar, "witches_hammer"))
        {
            link.l1 = "Тебе не интересно получить от меня заветную книгу, что ты так резок?";
            link.l1.go = "book";
        }
        //<-- Сага
        //поручение капитана - выкуп
        if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
        {
            if (CheckAttribute(pchar, "GenQuest.CaptainComission.toMayor"))
            {
                link.l1 = "Я по поводу твоего пленника.";
                link.l1.go = "CapComission1";
                DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
            }
            if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
            {
                link.l1 = "Здравствуй, Пастор, я по поводу твоего поручения.";
                link.l1.go = "CapComission3";
            }
            if (CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar, "GenQuest.CaptainComission.vikupzaplatil"))
            { // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
                link.l1 = "Я по поводу твоего пленника.";
                link.l1.go = "CapComission6";
            }
        }
        break;

    case "shark":
        dialog.text = "Стивен Додсон? Не знаю, поможет ли тебе то, что я расскажу, поскольку Акула бесследно сгинул уже как несколько месяцев, и от него нет ни слуху, ни духу. Что и неудивительно - ведь он прикончил Блейза Шарпа, дискредитировав этим нелепым поступком своё имя и настроив против себя ряд влиятельных корсаров.";
        link.l1 = "У меня есть основания полагать, что Акула невиновен в гибели Шарпа. Доказать я этого не могу, но, возможно, сам Акула сможет это прояснить. Так ты скажешь мне про него хоть что-нибудь?";
        link.l1.go = "shark_1";
        break;

    case "shark_1":
        dialog.text = "Несколько месяцев назад Стивен явился ко мне и предложил очень странную сделку: он оставил мне в залог свой фрегат 'Фортуна' взамен на бриг с трюмами, полными продовольствия, на один месяц. Потом или бриг с деньгами за провиант, или фрегат остаётся у меня. Прошёл месяц - ни Акулы, ни моего брига, ни денег за товар\nКроме того, пришло известие о смерти Блейза, и то, что Акула подозревается в его убийстве. Ну и что я мог решить? Правильно! Что Стив попросту слинял от греха подальше. Его фрегат я продал какому-то англичанину по имени Вильям Патерсон, он был очень доволен покупкой и отвалил кучу дублонов\nТак что я полностью компенсировал свои потери и зла на Стива не держу. А что касается убийства Шарпа, так меня это особо и не касается, у меня своих забот полон рот.";
        link.l1 = "А ты не считаешь, что если бы он задумал слинять, то ему не нужен был бы твой бриг? У него же свой корабль был в сто раз лучше брига. По-моему, Акула что-то задумал, но, видимо, дела пошли не так как надо, раз не вернулся в срок.";
        link.l1.go = "shark_2";
        break;

    case "shark_2":
        dialog.text = "Как я тебе уже сказал, меня мало волнуют проблемы Додсона. Я всё сделал по уговору, а зачем ему понадобился мой бриг - это надо у него спросить, я его не принуждал к этому обмену.";
        link.l1 = "Ладно, оставим это. Ты, конечно, прав. Скажи, а куда Стивен направился на твоём бриге, ты не в курсе?";
        link.l1.go = "shark_3";
        break;

    case "shark_3":
        dialog.text = "А кто же его знает... Но есть у меня кое-какие догадки. Отбыв из нашей бухты, он взял курс на северо-запад, в сторону Мэйна. Там находится либо залив Гибели, печально известный тем, что окрестные джунгли буквально кишат дикими воинственными индейцами, либо, через Мексиканский залив - Новая Испания, с папистами и инквизицией\nЧто-то не верится, что он решился бы отправиться в эти места. Однако там, на северо-запад от Кубы, говорят, есть некое загадочное место, именуемое островом Справедливости. Многие считают это выдумкой, а вот я тебе скажу - я в это верю. И не потому, что я такой романтик, а потому что есть самые настоящие реальные люди, которые туда плавают на своих баркасах. Во всяком случае, раньше плавали.";
        link.l1 = "И что же это за люди?";
        link.l1.go = "shark_4";
        break;

    case "shark_4":
        dialog.text = "Буканьеры с Кубы. Грузили полные баркасы разделанных бычьих туш, брали курс на северо-запад, а спустя какое-то время возвращались назад, либо с карманами, полными денег, либо с редкими и ценными товарами.";
        link.l1 = "Очень интересно! И где же найти их, этих буканьеров?";
        link.l1.go = "shark_5";
        break;

    case "shark_5":
        dialog.text = "Ты у меня спрашиваешь? Поищи в лесах по всей Кубе. А если и найдёшь, то навряд ли они тебе вот так возьмут и расскажут - не станут они раскрывать свой источник заработка. Так что не трать время по-пустому, тем более, что их уже давно за этим занятием никто не видел\nКроме них, слыхал я про некие заметки, написанные испанским мореплавателем по фамилии Альворадо, который лично бывал на этом острове. Вот я и думаю: а не направился ли Стивен именно туда?";
        link.l1 = "Остров, про который никто не знает, который не обозначен на картах... Да уж. Неутешительные сведения.";
        link.l1.go = "shark_6";
        break;

    case "shark_6":
        dialog.text = "Я сразу сказал, что мой рассказ тебе навряд ли чем поможет. А зачем тебе вдруг понадобился Додсон?";
        link.l1 = "Мы с Лесным Дьяволом хотим предложить его кандидатуру на пост лидера Берегового братства. Как я уже сказал, есть серьезные основания полагать, что Блейза убил кто-то другой.";
        link.l1.go = "shark_7";
        break;

    case "shark_7":
        dialog.text = "Хех! Значит, Ян за него? Ну, ты знаешь законы: для избрания лидера Додсон должен получить голоса всех баронов.";
        link.l1 = "Знаю. Отсюда мой второй вопрос: ты проголосуешь за Стивена Додсона на выборах?";
        link.l1.go = "shark_8";
        break;

    case "shark_8":
        dialog.text = "Пускай он сначала вернётся... А вообще, мне всё равно, кто будет возглавлять Братство, лишь бы делал это толково и не лез в мои дела. Как я тебе уже говорил, у меня своих проблем по горло. Ты знаешь, сколько на нашем острове ведьм и колдунов? Нет? А я тебе скажу: легион! И кроме того, полно папистов из Сантьяго и Гаваны\nВот, кстати, о колдунах. Есть такая книга, трактат, называется 'Молот ведьм'. Я очень хочу получить эту книгу, но обязательно на английском языке, потому что то, что я встречал - латинский, немецкий и испанский переводы, не годятся, так как я не знаю этих языков. Привезёшь мне книгу - отдам свой голос за Додсона\nНо учти, что достать этот трактат для меня также взялся и Джекман, в обмен на голос в его пользу, и если он тебя опередит - то не обессудь.";
        link.l1 = "Хорошо, я это учту. Спасибо за то, что уделил время. До встречи!";
        link.l1.go = "shark_9";
        break;

    case "shark_9":
        DialogExit();
        pchar.questTemp.Saga.SharkHunt = "after_marlow";
        npchar.quest.sharkbegin = "true";
        AddQuestRecord("SharkHunt", "2");
        break;

    case "book":
        dialog.text = "Книгу? Я так понимаю, речь идёт о 'Молоте ведьм'?";
        link.l1 = "Ну конечно. Мне удалось разыскать её для тебя. Она на английском, как ты и просил.";
        link.l1.go = "book_1";
        break;

    case "book_1":
        dialog.text = "Хех, дружище, извини за грубый приём. Более не повторится... Дай мне взглянуть на это чудо!";
        link.l1 = "Конечно, пожалуйста.";
        link.l1.go = "book_2";
        break;

    case "book_2":
        RemoveItems(pchar, "witches_hammer", 1); // удалить трактат
        dialog.text = "Наконец-то! Трепещите, слуги ада! Я не оставлю вас в покое, пока эта рука способна держать...";
        link.l1 = "Я рад за тебя, Пастор. Так что насчёт твоего голоса в Совете?";
        link.l1.go = "book_3";
        break;

    case "book_3":
        dialog.text = "Как я тебе уже говорил - мне всё равно, кто станет главой. Уверен, Свенсон не выберет на эту роль никудышного кандидата. Так что свой голос я отдаю тебе. Делай с ним, что сочтёшь нужным. Вот мой осколок.";
        link.l1 = "Спасибо, Захария. Ещё увидимся!";
        link.l1.go = "book_4";
        break;

    case "book_4":
        GiveItem2Character(pchar, "splinter_zm"); // дать осколок
        DialogExit();
        NextDiag.CurrentNode = "I_know_you_good";
        AddQuestRecord("BarbTemptation", "27");
        if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm"))
            Saga_GiveCalendar();
        ChangeCharacterComplexReputation(pchar, "fame", 1);
        break;

    case "Exit":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        break;

    case "I_know_you_good":
        dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", рад тебя видеть! Зачем пожаловал" + GetSexPhrase("", "а") + " на этот раз?",
                                              "Ну что тебе ещё?", "Долго это будет продолжаться? Если тебе делать нечего, не отвлекай других!",
                                              "Ты " + GetSexPhrase("хороший капер", "хорошая девушка") + ", поэтому живи пока. Но общаться и разговаривать с тобой я больше не желаю.", "repeat", 10, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat("Да, собственно, просто так заглянул" + GetSexPhrase("", "а") + ", проведать. Ничего по делу нет.",
                                           "Ничего, просто так...",
                                           "Хорошо, Пастор, извини...",
                                           "Вот чёрт возьми, доиграл" + GetSexPhrase("ся", "ась") + "!!!", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        NextDiag.TempNode = "I_know_you_good";

        if (sti(pchar.GenQuest.Piratekill) > 20)
        {
            dialog.text = RandPhraseSimple("У тебя крыша поехала? Вообразил себя мясником? Все пираты злы на тебя, приятель, так что лучше тебе убраться отсюда побыстрее.", "Ты, приятель, похоже, из ума выжил. Руки чесались сильно? Теперь не обессудь - здесь тебе делать нечего. Вали отсюда побыстрее!");
            link.l1 = RandPhraseSimple("Послушай, я хочу исправить ситуацию...", "Помоги мне решить эту проблему...");
            link.l1.go = "pirate_town";
            break;
        }
        //поручение капитана - выкуп
        if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.toMayor"))
        {
            link.l1 = "Я по поводу твоего пленника.";
            link.l1.go = "CapComission1";
            DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
        }
        if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.toMayor"))
        {
            link.l1 = "Я по поводу твоего пленника.";
            link.l1.go = "CapComission1";
            DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
        }
        if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") //  правка лесник,новая проверка ,исключающая тут же сдачу задания
        {
            link.l1 = "Здравствуй, Захария, я по поводу твоего поручения.";
            link.l1.go = "CapComission3";
        }
        if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && CheckAttribute(pchar, "questTemp.LongHappy"))
        { // лесник . похититель  ( после ДЛС ДиС ,когда барбазона уже нет)
            link.l1 = "Я слышал, что ты занимаешься бизнесом, связанным с пленниками...";
            link.l1.go = "Marginpassenger";
        }
        break;

        //-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
    case "CapComission1":
        dialog.text = "Хо-хо. Ты думаешь, у меня только один пленник? Называй, кого конкретно имеешь в виду?";
        link.l1 = pchar.GenQuest.CaptainComission.SlaveName + ". Есть такой?";
        link.l1.go = "CapComission2";
        DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
        break;

    case "CapComission2":
        if (CheckAttribute(pchar, "GenQuest.CaptainComission.DaysLeft"))
        {
            dialog.text = "Был. Я его продал к чёртовой матери этому плантатору с Барбадоса - полковнику Бишопу, он заезжал на прошлой неделе.";
            link.l1 = "Вот чёрт...";
            link.l1.go = "CapComission2_1";
        }
        else
        {
            dialog.text = "А-а, ну наконец-то. Я уж было подумывал продать его к чёртовой матери этому плантатору с Барбадоса, он должен появиться у меня через неделю-другую... Ты выкуп привез" + GetSexPhrase("", "ла") + "?";
            link.l1 = "Слушай, тут такое дело... В общем, у меня нет таких денег. Но я готов" + GetSexPhrase("", "а") + " отработать.";
            link.l1.go = "CapComission2_2";
            if (makeint(pchar.money) > 150000)
            {
                link.l2 = "Хорошо, что не продал. Вот деньги - 150000 песо. Где я могу его забрать?" link.l2.go = "CapComission2_3";
            }
        }
        break;

    case "CapComission2_1":
        dialog.text = "Долго ты телил" + GetSexPhrase("ся", "ась") + "... А кстати, этот невольник к тебе каким боком? Я, помнится, его родственникам выкуп назначал.";
        link.l1 = "Да я по поручению этих родственников и приехал" + GetSexPhrase("", "а") + ".";
        link.l1.go = "CapComission2_11";
        break;

    case "CapComission2_11":
        dialog.text = "Ну, опоздал" + GetSexPhrase("", "а") + " ты - что я могу поделать?";
        link.l1 = "Слушай, а за сколько продал, если не секрет?";
        link.l1.go = "CapComission2_12";
        break;

    case "CapComission2_12":
        dialog.text = "Э-э, не секрет, конечно, но я тебе не скажу. А то смеяться будешь, ха-ха-ха-ха... Ну, бывай.";
        link.l1 = "Счастливо.";
        link.l1.go = "exit";
        AddQuestRecord("CaptainComission1", "10");
        AddQuestUserData("CaptainComission1", "sName", "Захария Марлоу"); //правка лесник.  в СЖ запись ниже не работает
        //AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
        CaptainComission_GenerateManager();
        break;

    case "CapComission2_2":
        if (rand(3) == 1)
        {
            dialog.text = "Ну, " + pchar.name + ", ты же знаешь, что так дела не делаются. Приходи с деньгами и получишь своего заморыша, хе-хе.";
            link.l1 = "Ну ладно, до встречи.";
            link.l1.go = "CapComission2_4";
        }
        else
        {
            dialog.text = "Гхм-гхм... Есть у меня одно дело... Даже не знаю, как начать... В общем, нужно пустить ко дну одного зарвавшегося пирата.";
            link.l1 = "А разве нельзя убрать его в джунглях?";
            link.l1.go = "CapComission2_2_1";
        }
        break;

    case "CapComission2_2_1":
        dialog.text = "Ну, понимаешь ли, так серьёзные дела не делаются... Мне не смерть его нужна, мне нужно отбить охоту у слишком ретивых разевать рот на мою часть добычи. Хотя, если он отправится к осьминогам - я не огорчусь.";
        link.l1 = "А почему тебе не послать за ним своих людей?";
        link.l1.go = "CapComission2_2_2";
        break;

    case "CapComission2_2_2":
        CaptainComission_GetRandomShore();
        pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
        pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
        pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
        sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
        dialog.text = "Хм... В общем некий " + GetName(NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " убедил часть пиратов что в нашем тайнике, близ " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + ", есть и их доля. Недавно они снялись с якоря, и на двух судах, '" + pchar.GenQuest.CaptainComission.ShipName1 + "' и '" + pchar.GenQuest.CaptainComission.ShipName2 + "', ушли к " + sLoc + ". Понимаешь теперь, почему я не могу поручить это дело своим людям?";
        link.l1 = "Понятно. И сколько у меня есть времени?";
        link.l1.go = "CapComission2_2_3";
        break;

    case "CapComission2_2_3":
        dialog.text = "Думаю, дней 12-15, не больше. Мне важно, чтоб они не успели добраться до тайника, иначе топить их с ценным грузом на борту не будет смысла. Уж лучше пусть везут его сюда.";
        link.l1 = "Хорошо, я берусь за это дело. Постараюсь успеть.";
        link.l1.go = "CapComission2_2_4";
        break;

    case "CapComission2_2_4":
        AddQuestRecord("CaptainComission1", "24");
        AddQuestUserData("CaptainComission1", "sName", "Захария Марлоу"); //правка
        //AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
        AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
        AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
        AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
        AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
        pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
        pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
        pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips";
        SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
        //pchar.GenQuest.CaptainComission.PirateShips = "sdatkwest";    // лесник - заменил проверку для сдачи сразу.
        DialogExit();
        break;

    case "CapComission2_3":
        dialog.text = "Не переживай. Мои люди доставят его к тебе на борт. А он тебе кто?";
        link.l1 = "Никто. Я выполняю поручение его родственника.";
        link.l1.go = "CapComission2_31";
        break;

    case "CapComission2_31":
        dialog.text = "А-а, это хорошо. А то я уж было расстроился, что продешевил, назначив такую низкую цену за твоего человека. Ха-ха-ха-ха... Ну, бывай.";
        link.l1 = "Счастливо.";
        link.l1.go = "CapComission2_32";
        break;

    case "CapComission2_32":
        AddQuestRecord("CaptainComission1", "9");
        AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
        AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
        AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
        addMoneyToCharacter(pchar, -150000);
        pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник
        DialogExit();
        AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
        break;

    case "CapComission2_4":
        if (!CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak"))
        {
            AddQuestRecord("CaptainComission1", "31");
            AddQuestUserData("CaptainComission1", "sName", "Захария Марлоу"); // лесник
                                                                              //AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает
        }
        pchar.GenQuest.CaptainComission.RepeatSpeak = true;
        DialogExit();
        break;

    case "CapComission3":
        dialog.text = "Ну что, " + GetFullName(pchar) + ", пустил" + GetSexPhrase("", "а") + " на дно моего приятеля?.. хе-хе-хе...";
        if (pchar.GenQuest.CaptainComission.PirateShips == "goaway")
        {
            link.l1 = "Нет. Я не успел" + GetSexPhrase("", "а") + " их догнать. И на обратном пути они мне не попадались.";
            link.l1.go = "CapComission4";
        }
        if (pchar.GenQuest.CaptainComission.PirateShips == "died")
        {
            link.l1 = "Да, как и договаривались - отправил" + GetSexPhrase("", "а") + " кормить акул.";
            link.l1.go = "CapComission5";
        }
        DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
        break;

    case "CapComission4":
        dialog.text = "Чёрт! Попадались - не попадались, какая теперь разница?.. Ну, и что ты предложишь дальше?";
        link.l1 = "Может, у тебя есть какое-нибудь поручение попроще?";
        link.l1.go = "CapComission4_1";
        link.l2 = "Слушай, " + NPChar.name + ", уступи мне этого пленника подешевле...";
        link.l2.go = "CapComission4_2";
        break;

    case "CapComission4_1":
        dialog.text = "Нет.";
        link.l1 = "...Ну, тогда счастливо оставаться...";
        link.l1.go = "CapComission4_3";
        break;

    case "CapComission4_2":
        dialog.text = "Подешевле?!! Только что из-за твоей нерасторопности я лишился своего тайника! И теперь я могу уступить его подороже! Забирай за 200000, если хочешь.";
        link.l1 = "Дорого это... Прощай...";
        link.l1.go = "CapComission4_4";
        if (sti(pchar.money) >= 200000)
        {
            link.l2 = "А чёрт, держи свои деньги.";
            link.l2.go = "CapComission4_5";
        }
        break;

    case "CapComission4_3":
        ChangeCharacterComplexReputation(pchar, "nobility", -2);
        AddQuestRecord("CaptainComission1", "27");
        AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "ла"));
        AddQuestUserData("CaptainComission1", "sName", "Марлоу"); // лесник
        //AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
        AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
        AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
        DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
        DialogExit();
        break;

    case "CapComission4_4":
        ChangeCharacterComplexReputation(pchar, "nobility", -2);
        AddQuestRecord("CaptainComission1", "28");
        AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
        AddQuestUserData("CaptainComission1", "sName", "Марлоу"); // правка    // лесник
        //AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
        AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
        AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
        DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
        DialogExit();
        break;

    case "CapComission4_5":
        dialog.text = "Можешь забрать заморыша...";
        link.l1 = "Счастливо оставаться.";
        link.l1.go = "CapComission4_6";
        break;

    case "CapComission4_6":
        addMoneyToCharacter(pchar, -200000);
        AddQuestRecord("CaptainComission1", "29");
        AddQuestUserData("CaptainComission1", "sName", "Марлоу");                                                                            // правки имени в сж лесник
        AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); // в сж не работате
        AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
        AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
        DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
        pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
        DialogExit();
        AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
        break;

    case "CapComission5":
        dialog.text = "Хо-хо! Вот это работа! Забирай своего заморыша и бывай здоров" + GetSexPhrase("", "а") + ".";
        link.l1 = "Спасибо. Счастливо оставаться.";
        link.l1.go = "CapComission5_1";
        break;

    case "CapComission5_1":
        AddQuestRecord("CaptainComission1", "34");
        AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
        AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
        AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
        DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
        DialogExit();
        AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
        break;

        /*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
             ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
            dialog.text = "Ты выкуп привез"+ GetSexPhrase("","ла") +"? Ведь я не шутил, когда сказал, что продам его плантаторам.";            
            link.l1 = "Слушай, "+ NPChar.name +", тут такое дело... В общем, у меня нет таких денег. Но я готов"+ GetSexPhrase("","а") +" отработать.";
            link.l1.go = "CapComission2_2";
            if(makeint(pchar.money) > 150000)
            {
                link.l2 = "Хорошо, что не продал. Вот деньги - 150000 песо. Где я могу его забрать?"
                link.l2.go = "CapComission2_3";
            }            
        break;*/
    case "CapComission6": // лесник . пусть шарль бабло ищет,или забить на пленника.
        dialog.text = "Ты выкуп привез" + GetSexPhrase("", "ла") + "? Ведь я не шутил, когда сказал, что продам его плантаторам.";
        link.l1 = "Пока нет денег, " + NPChar.name + ", но я работаю над этим.";
        link.l1.go = "exit";
        if (makeint(pchar.money) > 150000)
        {
            link.l2 = "Хорошо, что не продал. Вот деньги - 150000 песо. Где я могу его забрать?" link.l2.go = "CapComission2_3";
        }
        break;

        //--------------------------------------------Похититель------------------------------------------------------
    case "Marginpassenger":
        dialog.text = "А тебе-то какое дело до того, чем я занимаюсь, а чем нет? Не стоит отвлекать меня по пустякам..";
        link.l1 = "Я пришёл к тебе по делу, причём именно по этому делу.";
        link.l1.go = "Marginpassenger_1";
        break;

    case "Marginpassenger_1":
        dialog.text = "А-а, ну ладно. За кого ты привёз выкуп?";
        link.l1 = "Погоди. Я сюда пришёл не для того, чтобы выкупать, а для того, чтобы предложить тебе купить одного моего пленника. Ну, а ты потом cможешь получить за него выкуп.";
        link.l1.go = "Marginpassenger_2";
        break;

    case "Marginpassenger_2":
        dialog.text = "Хм. А зачем тебе понадобилось моё посредничество? Чего сам не хочешь получить денежки напрямую?";
        link.l1 = "Для меня в данном случае это опасно. Могут быть проблемы с властями.";
        link.l1.go = "Marginpassenger_3";
        break;

    case "Marginpassenger_3":
        dialog.text = "Кхе... Ну, хорошо. Кто он, твой пленник?";
        link.l1 = "Это " + pchar.GenQuest.Marginpassenger.Text + " " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.City + "Gen") + ".";
        link.l1.go = "Marginpassenger_4";
        break;

    case "Marginpassenger_4":
        int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon) * 2 * stf(pchar.GenQuest.Marginpassenger.Chance)) * 100;
        dialog.text = "Так-так... Если ты не врешь, то это может оказаться интересной сделкой. Пожалуй, я готов заплатить за этого человека " + iTemp + " песо, или, если хочешь, могу поделиться полезной информацией. Что тебе больше нравится.";
        link.l1 = "Давай лучше песо. Я уже вдоволь намаялся с этим делом, будь оно неладно...";
        link.l1.go = "Marginpassenger_money";
        link.l2 = "Ха! Лучше расскажи что-нибудь полезное. Уверен, ерунды ты мне не предложишь.";
        link.l2.go = "Marginpassenger_offer";
        break;

    case "Marginpassenger_money":
        dialog.text = "Деньги - так деньги. Вот, держи. Теперь это больше не твоя забота. Потрудись привести товар сюда.";
        link.l1 = "Он должен быть уже около городских ворот. Спасибо! Ты меня выручил.";
        link.l1.go = "Marginpassenger_money_1";
        break;

    case "Marginpassenger_money_1":
        iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon) * 2 * stf(pchar.GenQuest.Marginpassenger.Chance)) * 100;
        dialog.text = "Да всегда пожалуйста, привози ещё... Бывай!";
        link.l1 = "И тебе всего доброго...";
        link.l1.go = "exit";
        AddMoneyToCharacter(pchar, iTemp);
        sld = characterFromId("MarginPass");
        RemovePassenger(Pchar, sld);
        sld.lifeday = 0;
        AddQuestRecord("Marginpassenger", "12");
        AddQuestUserData("Marginpassenger", "sSum", iTemp);
        CloseQuestHeader("Marginpassenger");
        DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
        break;

    case "Marginpassenger_offer":
        pchar.GenQuest.Marginpassenger.Goods = GOOD_EBONY + rand(makeint(GOOD_MAHOGANY - GOOD_EBONY));
        pchar.GenQuest.Marginpassenger.GoodsQty = 200 + rand(10) * 10;
        switch (drand(1))
        {
        case 0: //бухта на южном мейне
            SelectSouthshore();
            while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore))
                SelectSouthshore(); // исправил окончание . лесник (строчка ниже)
            dialog.text = "Приятно иметь дело со сметливым человеком, парень! Теперь слушай: через несколько дней к " + XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore + "Abl") + " подойдёт испанская экспедиция из Мейна, с запасами ценной древесины, и будет ждать корабля, который должен прийти и забрать груз. Если за неделю ты успеешь туда добраться - у тебя будет шанс забрать весь товар себе\nНа твоём месте я бы уже бежал к своей посудине. И потрудись доставить пленника сюда.";
            link.l1 = "Благодарю! Древесина послужит хорошей компенсацией за мои мытарства! А мой пассажир уже должен быть где-то у городских ворот. Его к тебе приведут.";
            link.l1.go = "Marginpassenger_offer_1";
            break;

        case 1: //просто кораблик
            SelectSouthcity();
            pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
            dialog.text = "Приятно иметь дело со сметливым человеком, парень! Теперь слушай: приблизительно через неделю из " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity + "Gen") + " выйдет испанская баркентина '" + pchar.GenQuest.Marginpassenger.ShipName1 + "' с грузом ценной древесины и отправится в порт " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity1 + "Gen") + ". Если не будешь зевать, то запросто перехватишь её\nТы ещё здесь? На твоём месте я бы уже бежал к своей посудине. И потрудись доставить пленника сюда.";
            link.l1 = "Благодарю! Древесина послужит хорошей компенсацией за мои мытарства! А мой пассажир уже должен быть где-то у городских ворот. Его к тебе приведут.";
            link.l1.go = "Marginpassenger_offer_2";
            break;
        }
        sld = characterFromId("MarginPass");
        RemovePassenger(Pchar, sld);
        sld.lifeday = 0;
        pchar.GenQuest.Marginpassenger = "final";
        break;

    case "Marginpassenger_offer_1":
        DialogExit();
        AddQuestRecord("Marginpassenger", "13");
        AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore + "Abl")); //лесник - окончание в СЖ
        SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
        pchar.quest.Marginpassenger.win_condition.l1 = "location";
        pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
        pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
        break;

    case "Marginpassenger_offer_2":
        DialogExit();
        AddQuestRecord("Marginpassenger", "16");
        AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity + "Gen"));
        AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity1 + "Acc")); // лесник - окончание в СЖ
        AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
        SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5 + rand(2), false);
        break;

    // ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
    case "Man_FackYou":
        dialog.text = LinkRandPhrase("Грабёж среди бела дня!!! Это что же такое делается?! Ну, погоди, " + GetSexPhrase("приятель", "подруга") + "...", "Эй, ты чего это там копаешься?! Никак, вздумал" + GetSexPhrase("", "а") + " ограбить меня? Ну, тогда тебе конец...", "Постой, ты куда это полез" + GetSexPhrase("", "ла") + "? Да ты вор" + GetSexPhrase("", "овка") + ", оказывается! Ну, считай, что ты приплыл" + GetSexPhrase("", "а") + ", родн" + GetSexPhrase("ой", "ая") + "...");
        link.l1 = LinkRandPhrase("Дьявол!!", "Каррамба!!", "А-ать, черт!");
        link.l1.go = "PL_Q3_fight";
        break;

    // ======================== блок нод angry ===============>>>>>>>>>>>>>>>
    case "AngryRepeat_1":
        dialog.text = RandPhraseSimple("" + GetSexPhrase("Пошёл вон", "Убирайся") + " отсюда!", "Вон из моего дома!");
        link.l1 = "Ай...";
        link.l1.go = "AngryExitAgainWithOut";
        if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
        {
            if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
            {
                dialog.text = "Тебе не стоит отвлекать меня от дела пустыми обращениями. Впредь результат может быть более плачевным...";
                link.l1 = "Я понял" + GetSexPhrase("", "а") + ".";
                link.l1.go = NextDiag.TempNode;
                CharacterDelAngry(npchar);
            }
        }
        break;

    case "AngryRepeat_2":
        dialog.text = RandPhraseSimple("Ты меня изрядно утомил" + GetSexPhrase("", "а") + ", никакого общения.", "Я не хочу с тобой общаться, так что тебе лучше меня не беспокоить.");
        link.l1 = RandPhraseSimple("Ну как знаешь...", "Хм, ну что же...");
        link.l1.go = "AngryExitAgain";
        if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
        {
            if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
            {
                dialog.text = "Надеюсь, впредь ты не будешь утомлять меня пустыми разговорами, иначе мне придётся тебя убить. Признаюсь, мне это будет очень неприятно.";
                link.l1 = "Пастор, ты можешь быть уверен - не буду...";
                link.l1.go = NextDiag.TempNode;
                CharacterDelAngry(npchar);
            }
        }
        break;

    case "AngryExitAgain":
        DialogExit();
        DeleteAttribute(npchar, "angry.ok");
        break;

    case "AngryExitAgainWithOut":
        DialogExit();
        DeleteAttribute(npchar, "angry.ok");
        DoReloadCharacterToLocation("Puertoprincipe_town", "reload", "reload6");
        break;
    // <<<<<<<<<<<<============= блок нод angry =============================
    case "pirate_town":
        dialog.text = "Решить проблему? Да ты сам понимаешь, чего ты наворотил? В общем, принесёшь мне миллион песо - я уговорю ребят, чтобы они забыли твои 'подвиги'. Нет - можешь катиться на все четыре стороны.";
        if (sti(Pchar.money) >= 1000000)
        {
            link.l1 = "Хорошо, я готов заплатить.";
            link.l1.go = "pirate_town_pay";
        }
        link.l2 = "Я всё понял. Ухожу.";
        link.l2.go = "pirate_town_exit";
        break;

    case "pirate_town_exit":
        DialogExit();
        bDisableFastReload = true; //закрыть переход
        pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
        pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
        pchar.quest.pirate_in_town.function = "TownPirate_battle";
        break;

    case "pirate_town_pay":
        dialog.text = "Вот и славно! Считай, что свою репутацию ты восстановил. Но впредь, я надеюсь, ты больше не будешь делать таких мерзостей.";
        link.l1 = "Не буду. Уж очень дорого они обходятся. Прощай...";
        link.l1.go = "exit";
        AddMoneyToCharacter(pchar, -1000000);
        pchar.GenQuest.Piratekill = 0;
        break;
    }
}

void SelectSouthshore()
{
    switch (rand(6))
    {
    case 0:
        pchar.GenQuest.Marginpassenger.Shore = "shore37";
        break;
    case 1:
        pchar.GenQuest.Marginpassenger.Shore = "shore47";
        break;
    case 2:
        pchar.GenQuest.Marginpassenger.Shore = "shore48";
        break;
    case 3:
        pchar.GenQuest.Marginpassenger.Shore = "shore25";
        break;
    case 4:
        pchar.GenQuest.Marginpassenger.Shore = "shore21";
        break;
    case 5:
        pchar.GenQuest.Marginpassenger.Shore = "shore20";
        break;
    case 6:
        pchar.GenQuest.Marginpassenger.Shore = "shore19";
        break;
    }
}

void SelectSouthcity()
{
    switch (drand(2))
    {
    case 0:
        pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
        pchar.GenQuest.Marginpassenger.Southcity1 = "Havana";
        break;

    case 1:
        pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
        pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago";
        break;

    case 2:
        pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
        pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo";
        break;
    }
}
