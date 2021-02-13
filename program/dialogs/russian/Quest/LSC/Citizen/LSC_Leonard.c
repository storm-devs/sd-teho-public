// Леонард Маскетт - пьяница
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    int iPeso, iDubl;
    string sPeso, sDubl;

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
        // --> пей до дна
        if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_3") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.facio"))
        {
            dialog.text = "Приятель, ты как раз вовремя... Я хочу с тобой побеседовать... по одному делу. Важному делу.";
            link.l1 = "Вот как? Странно, ты похоже и не пьян вовсе. Что-то случилось? Как-то непривычно видеть тебя трезвым.";
            link.l1.go = "facio";
            break;
        }
        // <-- пей до дна
        if (npchar.quest.meeting == "0")
        {
            dialog.text = "А-а... ик! Здорово, приятель, коль не шутишь...";
            link.l1 = TimeGreeting() + ". Похоже, ты уже изрядно набрался, дружище.";
            link.l1.go = "meeting";
            npchar.quest.meeting = "1";
        }
        else
        {
            dialog.text = "А, " + GetFullName(pchar) + "! Ик! Что тебе надо?";
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
        dialog.text = "Иех! Набрался? Не-ет! Я пьян в стельку, и-ик! Да, Леонард Маскетт пьян, и это правильно!";
        link.l1 = "Любишь выпить? Да, меня зовут " + GetFullName(pchar) + ". Будем знакомы.";
        link.l1.go = "meeting_1";
        break;

    case "meeting_1":
        dialog.text = "Знакомы - так знакомы. Мы тут все, ик... знакомы.";
        link.l1 = "Ладно, вижу, тебе не до разговоров. Бывай!";
        link.l1.go = "exit";
        link.l2 = LinkRandPhrase("Что-нибудь интересное мне расскажешь?", "Что нового произошло на острове в последнее время?", "Не расскажешь ли последние сплетни?");
        link.l2.go = "rumours_LSC";
        link.l3 = "Я хочу задать тебе пару вопросов об острове.";
        link.l3.go = "int_quests"; //информационный блок
        NextDiag.TempNode = "First time";
        break;

    // --> пей до дна
    case "facio":
        dialog.text = "Да, дружище, я почти трезв. Это потому, что у меня есть важное дело, очень важное. И ты, кажется, вполне подходишь...";
        link.l1 = "Чего? Что ты там надумал? Давай выкладывай, не трать моё время попусту!";
        link.l1.go = "facio_1";
        npchar.quest.facio = "true";
        break;

    case "facio_1":
        dialog.text = "Приятель, ты хочешь подзаработать денег? Серебряных песо, золотых дублонов? Я скажу, как. Но ты должен войти со мной в долю - мы будем работать на пару.";
        link.l1 = "Заработать я всегда хочу. Однако всё зависит от того, что ты предложишь: я не на все дела подписываюсь, даже на сулящие приличные барыши.";
        link.l1.go = "facio_2";
        break;

    case "facio_2":
        dialog.text = "Дело, конечно, не очень чистое, но зато хорошо наживёмся... и накажем одного обнаглевшего типа. Он не обеднеет, у него и так денег полно. Все с ним делятся - пора бы и ему поделиться. Теперь скажи: как ты переносишь ром? Много ли сможешь выпить, прежде чем свалишься под стол?";
        link.l1 = "Ну, когда как. Не знаю, как-то не имею привычки напиваться в стельку... Ты когда-нибудь дойдёшь до сути своего предложения, или будешь без конца кота за хвост тянуть?";
        link.l1.go = "facio_3";
        break;

    case "facio_3":
        dialog.text = "Я уже начал излагать суть, просто ты пока не понял. Ладно. Объясняю конкретно. Есть у нас на Острове один мерзкий толстяк - Джузеппе Фацио. Пройдоха, каких свет не видывал. Обдирает и нарвалов, и ривадос, и прочих жителей. Я давно к нему присматриваюсь, и кое-что вызнал\nУ него в каюте на 'Каролине' есть два сундука: в одном он хранит всякие бумаги, а во втором - золотые и серебряные монеты. Оба сундука запираются на ключ, причём каждый - на свой. Толстяк никогда не расстаётся с этими ключами...";
        link.l1 = "Так, кажется, ты задумал ограбить Фацио? Я в этом участвовать не буду. И радуйся, что я не стану доносить на тебя, ибо это не в моих правилах. Хочешь залезть в сундук толстяка - ищи себе другого помощника.";
        link.l1.go = "facio_exit";
        link.l2 = "Ха! Интересно! Продолжай...";
        link.l2.go = "facio_4";
        break;

    case "facio_exit":
        dialog.text = "Зря, очень зря... Там целая куча золота, хватило бы на обоих. Ладно, бывай, раз не хочешь...";
        link.l1 = "Не хочу. Прощай.";
        link.l1.go = "exit";
        break;

    case "facio_4":
        dialog.text = "С палубы 'Каролины' в каюту ведут две двери. Одна из них всегда заперта. Так вот, ключ, отпирающий сундук с деньгами, открывает также и эту дверь. Уж не знаю, зачем так Фацио придумал, но это факт. Достаточно иметь всего один ключ, чтобы и проникнуть в каюту, и отпереть сундук. Логичный вопрос: как достать ключ? Так вот - у меня есть план\nОчень хороший план - в случае успеха Фацио даже не поймёт, как это случилось, и кто виноват. Спишут на таинственного воришку. Но для выполнения задуманного мне нужен помощник, причём с крепкой головой. Ты меня слушаешь?";
        link.l1 = "Очень внимательно. Продолжай.";
        link.l1.go = "facio_5";
        break;

    case "facio_5":
        dialog.text = "Фацио любит посидеть в таверне у Санчо и хорошенько выпить, однако его туша весит столько, что никакой ром не берёт. Поэтому он и придумал одно развлечение: пить на спор, кто кого перепьёт. Если ты предложишь ему это - он обязательно согласится\nИ вот тут-то и начинается самое весёлое. Ты заключаешь с ним пари, вы вечером идёте к Санчо, покупаете ром и начинаете пить кружку за кружкой, пока кто-то из вас первым не свалится. Если отрубишься ты - план провалится, ибо я не смогу всё сделать сам\nПоэтому я и спросил - крепкая ли у тебя голова. Если же тебе удастся довести Фацио до состояния поросячьего визга, считай - дело в шляпе. Я всё время буду рядом. Как только он вырубится - я вытащу у него ключ от 'Каролины'\nЗатем мы отведём толстяка к Санчо на кровать наверх, и пока он будет дрыхнуть - заберёмся в каюту 'Каролины', откроем сундук, заберём содержимое, закроем, и я верну ключ Фацио на место - ему в карман. Толстяк так и не поймёт, как его ограбили\nДостать и вернуть ключ я беру на себя, твоя задача - напоить Фацио и пробраться в каюту. Я буду стоять на стрёме, пока ты будешь копаться в его сундуке, и в случае чего - отвлеку внимание, а ты смоешься через кормовую галерею\nСодержимое сундука поделим пополам. Это будет справедливо. Ну как, готов попробовать?";
        link.l1 = "Отличный план! Конечно, будем пробовать!";
        link.l1.go = "facio_6";
        link.l2 = "Нет, приятель. Я пас. Боюсь, не сдюжу вылакать столько рома, чтобы уложить Фацио и остаться на ногах. Поищи себе другого напарника, покрепче.";
        link.l2.go = "facio_exit";
        break;

    case "facio_6":
        dialog.text = "Я рад, что не ошибся в тебе, парень. Теперь ступай к Фацио и договорись о встрече в таверне вечером, после девяти. Надеюсь, ты перепьёшь этого борова. Удачи и до встречи вечером!";
        link.l1 = "Я постараюсь... Пока!";
        link.l1.go = "facio_7";
        break;

    case "facio_7":
        DialogExit();
        NextDiag.CurrentNode = "facio_wait";
        pchar.questTemp.LSC.Drink = "begin";
        pchar.questTemp.LSC.Drink.Chance = drand(100); // итог бухалова
        if (CheckAttribute(pchar, "questTemp.CanDrink"))
            pchar.questTemp.LSC.Drink.Chance = sti(pchar.questTemp.LSC.Drink.Chance) + 50;
        SetFunctionTimerCondition("LSC_DrinkOver", 0, 0, 3, false); // 3 дня
        AddQuestRecord("LSC_Drink", "1");
        break;

    case "facio_wait":
        dialog.text = "Приятель, я рассчитываю на тебя. Напои этого толстяка...";
        link.l1 = "Да-да...";
        link.l1.go = "exit";
        NextDiag.TempNode = "facio_wait";
        break;

    case "result_0":
        dialog.text = "Всё, эта жирная свинья дрыхнет наверху. Ключ у меня. Ты держался молодцом - похоже, у тебя вообще ни в одном глазу!";
        link.l1 = "Ну, не скажи. Давно я так не накачивался. Слегка пошатывает... Ну что, идём?";
        link.l1.go = "result_win";
        break;

    case "result_1":
        dialog.text = "Всё, эта жирная свинья дрыхнет наверху. Ключ у меня. Ты держался молодцом - сумел-таки перепить этого борова...";
        link.l1 = "Сумел, но я давненько так не нажирался. Штормит сильно, голова кругом... Ну что, идём?";
        link.l1.go = "result_win";
        break;

    case "result_2":
        dialog.text = "Эх, дружище, всё-таки не потянул ты против этого толстяка... Жаль. Ну, да что поделаешь - хоть попытались...";
        link.l1 = "Ч-чёрт, воз-зьми, он просто какая-то... бездон-н-ная боч-чка. Аргх, мне надо пос-пать... Всё, про-валивай! Ик!..";
        link.l1.go = "result_fail";
        break;

    case "result_win":
        dialog.text = "Да. Идём! Следуй за мной к 'Каролине'! Ни на что не отвлекайся, времени в обрез!";
        link.l1 = "Пошли!";
        link.l1.go = "result_win_1";
        break;

    case "result_win_1":
        DialogExit();
        NextDiag.CurrentNode = "result_win_2";
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload6", "LostShipsCity_town", "reload", "reload39", "LSC_DrinkGotoCarolina", -1);
        AddQuestRecord("LSC_Drink", "3");
        break;

    case "result_win_2":
        pchar.quest.LSC_Drink1.over = "yes"; //снять таймер
        dialog.text = "Пришли. Держи ключ. Нужный сундук - слева от входа. Быстро перекладывай содержимое себе и линяй. Не забудь запереть его снова. Если увижу что подозрительное - постучу тебе в дверь три раза. В этом случае всё бросай и беги через кормовую галерею.";
        link.l1 = "Хорошо. Смотри в оба!";
        link.l1.go = "result_win_3";
        break;

    case "result_win_3":
        DialogExit();
        GiveItem2Character(pchar, "key_facioQ");
        NextDiag.CurrentNode = "result_grabbing";
        LAi_SetActorType(pchar);
        LAi_ActorGoToLocator(pchar, "reload", "reload25", "LSC_DrinkGotoCarolina_3", -1);
        break;

    case "result_grabbing":
        // считаем деньги и дублоны взятые из сундука
        iPeso = sti(pchar.money) - sti(pchar.questTemp.LSC.Drink.Money);
        iDubl = GetCharacterItem(pchar, "gold_dublon") - sti(pchar.questTemp.LSC.Drink.Dublon);
        if (iPeso <= 0)
            sPeso = "ни одного песо";
        else
            sPeso = "" + FindRussianMoneyString(iPeso) + "";
        if (iDubl <= 0)
            sDubl = "ни одного дублона";
        else
            sDubl = "" + iDubl + " дублонов";
        if (iPeso <= 10000 && iDubl <= 10)
            sTotalTemp = "Что за жалкие крохи... И ради этого мы рисковали? Эх... Ладно, делим, что есть.";
        else
        {
            if (iPeso <= 50000 && iDubl <= 100)
                sTotalTemp = "Я думал, там в разы больше... Риск того не стоил. Эх, ладно, делим, что есть.";
            else
            {
                if (iPeso <= 100000 && iDubl <= 300)
                    sTotalTemp = "Хм. Неплохо. Хотя должно было быть больше по моим расчётам. Ладно, давай делить.";
                else
                {
                    if (iPeso <= 150000 && iDubl <= 500)
                        sTotalTemp = "Отлично! Мы с тобой ловко сработали, напарник! Это целая куча монет! Давай делить!";
                    else
                    {
                        sTotalTemp = "Вот это да! Я даже не думал, что заначка этого толстяка так велика. Отличная работа, напарник! Теперь давай делить!";
                    }
                }
            }
        }
        dialog.text = "Ну наконец-то! Что тебе удалось добыть из сундука этого пройдохи? Показывай, я сгораю от нетерпения!";
        if (iPeso <= 0 && iDubl <= 0)
        {
            link.l1 = "У него там вообще ничего не было. Всякая дребедень - амулеты и прочая мелочь.";
            link.l1.go = "grabbing_0";
        }
        else
        {
            link.l1 = "Я взял в сундуке " + sPeso + " и " + sDubl + "";
            link.l1.go = "grabbing_1";
        }
        break;

    case "grabbing_0":
        dialog.text = "Не может быть! Получается, всё было зря... Наверное, этот гад переложил свою заначку во второй сундук. Эх! Ладно, давай ключ, отнесу его этому пьянице, пока он не хватился. Бывай, приятель...";
        link.l1 = "...";
        link.l1.go = "grabbing_exit";
        AddQuestRecord("LSC_Drink", "6");
        break;

    case "grabbing_1":
        dialog.text = sTotalTemp;
        link.l1 = "Давай поделим...";
        link.l1.go = "grabbing_part";
        break;

    case "grabbing_part":
        iPeso = makeint((sti(pchar.money) - sti(pchar.questTemp.LSC.Drink.Money)) / 2);
        iDubl = makeint((GetCharacterItem(pchar, "gold_dublon") - sti(pchar.questTemp.LSC.Drink.Dublon)) / 2);
        AddMoneyToCharacter(pchar, -iPeso);
        RemoveItems(pchar, "gold_dublon", iDubl);
        Log_Info("Вы отдали " + iDubl + " дублонов");
        PlaySound("interface\important_item.wav");
        dialog.text = "Так, а теперь давай мне ключ, отнесу его этому пьянице, пока он не хватился. Бывай, приятель...";
        link.l1 = "Удачи, дружище...";
        link.l1.go = "grabbing_exit";
        AddSimpleRumourCityTip("Фацио жаловался, что кто-то обчистил его сундук. Не иначе, как этот таинственный воришка постарался.", "LostShipsCity", 3, 1, "LSC", "");
        AddSimpleRumourCityTip("Слыхали - Джузеппе Фацио ограбили! Как раз тогда, когда он валялся пьяный в стельку после игры с вами.", "LostShipsCity", 3, 1, "LSC", "");
        AddSimpleRumourCityTip("Ну и крепкая же у тебя голова! Выпить столько рома и остаться на ногах! Это что-то...", "LostShipsCity", 3, 2, "LSC", "");
        AddQuestRecord("LSC_Drink", "5");
        break;

    case "grabbing_exit":
        DialogExit();
        RemoveItems(pchar, "key_facioQ", 1);
        int n = Findlocation("CarolineBank");
        locations[n].private2.QuestClosed = true;                    // запираем сундук
        LocatorReloadEnterDisable("CarolineBank", "reload1", false); // на галерею
        LAi_SetActorType(npchar);
        LAi_ActorRunToLocation(npchar, "reload", "reload38", "FleuronTavern", "goto", "goto2", "OpenTheDoors", 15.0);
        pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
        pchar.quest.LSC_Drink4.win_condition.l1.date.hour = sti(GetTime() + 5);
        pchar.quest.LSC_Drink4.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
        pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
        pchar.quest.LSC_Drink4.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
        pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
        break;

    case "result_fail":
        DialogExit();
        LAi_SetActorType(npchar);
        LAi_ActorRunToLocation(npchar, "reload", "reload1", "LostShipsCity_town", "goto", "goto05_2", "", 10);
        chrDisableReloadToLocation = false; //открыть локацию
        n = Findlocation("CarolineBank");
        locations[n].private2.QuestClosed = true; // запираем сундук
        pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
        pchar.quest.LSC_Drink4.win_condition.l1.date.hour = sti(GetTime() + 5);
        pchar.quest.LSC_Drink4.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
        pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
        pchar.quest.LSC_Drink4.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
        pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
        AddQuestRecord("LSC_Drink", "4");
        break;
        // <-- пей до дна

    case "":
        dialog.text = "";
        link.l1 = "";
        link.l1.go = "";
        break;

        //--------------------------------------- блок вопросов и ответов ---------------------------------------------
    case "int_quests":
        dialog.text = "Да что ты такое говоришь... ик! Слушаю...";
        if (!CheckAttribute(npchar, "quest.answer_1"))
        {
            link.l1 = "Как ты попал сюда?";
            link.l1.go = "ansewer_1";
        }
        if (!CheckAttribute(npchar, "quest.answer_2"))
        {
            link.l2 = "Ты что, постоянно пьёшь? Где же ты находишь деньги на выпивку?";
            link.l2.go = "ansewer_2";
        }
        if (!CheckAttribute(npchar, "quest.answer_3"))
        {
            link.l3 = "Что ты можешь сказать про жителей Острова?";
            link.l3.go = "ansewer_3";
        }
        if (!CheckAttribute(npchar, "quest.answer_4"))
        {
            link.l4 = "Ты бы хотел уехать отсюда назад, на Большую землю?";
            link.l4.go = "ansewer_4";
        }
        link.l10 = "Нет вопросов. Извините...";
        link.l10.go = "exit";
        break;

    case "ansewer_1":
        dialog.text = "Иех! Клянусь - не помню. Да-да, не помню, ик! Давно это было. Вышел я куда-то и зачем-то в море, и очутился тут. Ик!";
        link.l1 = "Гм... Ну-ну.";
        link.l1.go = "int_quests";
        npchar.quest.answer_1 = "true";
        break;

    case "ansewer_2":
        dialog.text = "Да, я пью... Пью, чёрт возьми, ибо больше мне делать нечего... Пойми, дружище, я конченый человек. И счастье у меня осталось одно - бутылка рома. И я буду пить. А деньги... хи-хи, а их много на ром и не надо. Да и покупать мне его тоже не надо\nЕсть тут одно местечко, где рома много, но туда надо добраться, поэтому я покупаю ром у Санчо только тогда, когда не в состоянии доплыть... ик! Т-сс, нет, куда - не скажу, хи-хи, даже и не спрашивай...";
        link.l1 = "Ясно...";
        link.l1.go = "int_quests";
        npchar.quest.answer_2 = "true";
        break;

    case "ansewer_3":
        dialog.text = "А что я могу, ик... про них сказать? Хорошие люди, со многими можно посидеть, поболтать. Вон, Джузеппе Фацио - такой важный человек, шишка местная, от золота сундуки ломятся - а тоже частенько привечает Леонарда, наливает ему в таверне. Правда, иногда просит что-то сделать, но это сущий пустяк, ик!\nХех, знал бы ты, сколько Фацио уже нагрёб дублонов, аха-ха! Можно весь остаток жизни благоденствовать в лучшем доме Кариб, ничего не делать, и пить самый лучший в мире ром. А он на Острове всё сидит. Всё мало ему, и мало...";
        link.l1 = "Понятно...";
        link.l1.go = "int_quests";
        npchar.quest.answer_3 = "true";
        SaveCurrentNpcQuestDateParam(npchar, "quest_date");
        break;

    case "ansewer_4":
        dialog.text = "Уехать? Ик! А зачем? Нет, не хочу, ни на большую, ни на малую. Там разве есть бесплатный ром? Нет, там его нет, ик! Значит, мне там делать нечего... Приятель, мне и тут хорошо. И скажу больше - ты поспрашивай на Острове, хочет ли кто-нибудь отсюда уехать. Кроме пары-тройки человек - никто, ик!";
        link.l1 = "Занятно...";
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
        dialog.text = LinkRandPhrase("Слушай, ты бы убрал оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как д'Артаньян, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это серьёзному мужчине...");
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