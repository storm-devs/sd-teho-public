// boal 25/04/04 общий диалог церковь
#include "DIALOGS\russian\Rumours\Common_rumours.c" //homo 25/06/06
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c ";
                         if (LoadSegment(NPChar.FileDialog2))
    {
        ProcessCommonDialog(NPChar, Link, NextDiag);
        UnloadSegment(NPChar.FileDialog2);
    }

    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag); //homo 16/06/06

    string iDay, iMonth, lastspeak_date, eggStr;
    string sTemp, sTitle;

    iDay = environment.date.day;
    iMonth = environment.date.month;
    lastspeak_date = iday + " " + iMonth;
    int iMoneyToCharacter;

    if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }

    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {
        npchar.quest.BadMeeting = "";
    }
    if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
    {
        npchar.quest.GhostShipMonth = "";
    }

    if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
    {
        NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
    }

    if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
    {
        NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
    }

    if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
    {
        NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
    }

    if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
    {
        NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
    }

    switch (Dialog.CurrentNode)
    {
    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    case "fight":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        LAi_group_Attack(NPChar, Pchar);
        break;

    case "First time":
        if (LAi_grp_playeralarm > 0)
        {
            dialog.text = NPCharRepPhrase(pchar,
                                          LinkRandPhrase("" + GetSexPhrase("Сын мой", "Дочь моя") + ", к сожалению, я не могу дать тебе убежища. Беги!", "Вся городская стража рыщет по городу в поисках тебя, " + GetSexPhrase("сын мой", "дочь моя") + ". Церковь открыта для страждущих, но я не могу предоставить тебе убежища...", "" + GetSexPhrase("Сын мой", "Дочь моя") + ", тебе надо бежать! Прошу тебя, не медли с этим!"),
                                          LinkRandPhrase("Что ты делаешь в церкви, падшая душа? Я требую, чтобы ты удалил" + GetSexPhrase("ся", "ась") + " немедленно, пока солдаты не ворвались и не устроили здесь резню!", "Немедленно покинь храм, безбожни" + GetSexPhrase("к", "ца") + "! Я не заступлюсь за так" + GetSexPhrase("ого", "ую") + ", как ты!", "Немедленно покинь храм Божий! Мне не нужны здесь убийства!!"));
            link.l1 = NPCharRepPhrase(pchar,
                                      RandPhraseSimple("Да ладно тебе, падре...", "Да не нужна мне твоя помощь..."),
                                      LinkRandPhrase("Святой отец, лучше не путайся под ногами...", "Уйду, не беспокойся...", "Падре, не суетись, не до тебя, ей богу"));
            link.l1.go = "fight";
            break;
        }
        if (npchar.quest.BadMeeting != lastspeak_date)
        {
            if (!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_2.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && NPChar.location != "Minentown_church" && rand(5) == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // 280313
            {
                dialog.text = "...вечно гореть им в геенне огненной! Не видать им...";
                link.l1 = RandPhraseSimple("Гм! Не помешал" + GetSexPhrase("", "а") + ", падре?", "Вот это спич!");
                link.l1.go = "GenQuest_Church_2_Start_1";
                NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
                break;
            }
            if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
            {
                Dialog.Text = "" + GetSexPhrase("Сын мой", "Дочь моя") + ", я рад снова видеть вас!";
                link.l1 = "И я рад" + GetSexPhrase("", "а") + " видеть вас в добром здравии, отец " + NPChar.name + "...";
                link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
                break;
            }
            if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
            {
                Dialog.Text = "" + GetSexPhrase("Сын мой", "Дочь моя") + "! Рад снова видеть тебя в добром здравии и хорошем настроении. Видимо, Бог способствовал счастливому завершению нашего дела?";
                link.l1 = "Да, " + RandPhraseSimple("падре", "святой отец") + ", хоть в мои паруса и не всегда дул попутный ветер, хоть я и потратил" + GetSexPhrase("", "а") + " несколько больше времени, сил и денег, но в итоге ваше поручение выполнено.";
                link.l1.go = "GenQuest_Church_1_Complete_1";
                break;
            }
            Dialog.Text = "Добро пожаловать под сень святой обители, " + GetSexPhrase("сын мой", "дочь моя") + ".";
            link.l1 = "Здравствуйте, святой отец.";
            link.l1.go = "node_3";
            Link.l2 = "Ты мне не отец, и не смей так больше обращаться.";
            Link.l2.go = "node_2";
            NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date; // Если не дал сегодня, то токо на след день.
        }
        else
        {
            Dialog.Text = "Покинь храм Господа, богохульни" + GetSexPhrase("к", "ца") + "! Нам с тобой не о чем говорить!";
            Link.l1 = "Не очень-то и хотелось.";
            Link.l1.go = "exit";
        }
        NextDiag.TempNode = "First time";
        break;

    case "node_2":
        dialog.text = "Ах, ты богохульни" + GetSexPhrase("к", "ца") + "! А ну прочь отсюда, дабы не осквернять своим присутствием храм Божий!";
        link.l1 = "Да я и так не собирал" + GetSexPhrase("ся", "ась") + " здесь задерживаться.";
        link.l1.go = "exit";
        ChangeCharacterComplexReputation(pchar, "nobility", -0.25);
        npchar.quest.BadMeeting = lastspeak_date;
        break;

    case "node_3":
        dialog.text = "Да благословит Господь вас и дела ваши... Вы пришли ко мне с какой-то целью?";
        link.l1 = RandPhraseSimple("Я хочу внести пожертвования.", "Хочу пожертвовать на благое дело.");
        link.l1.go = "donation";
        link.l2 = RandPhraseSimple("Думаю, настало время исповеди.", "Мне нужно покаяться, " + RandPhraseSimple("падре.", "святой отец."));
        link.l2.go = "ispoved";
        link.l3 = RandPhraseSimple("У меня к вам дело, " + RandPhraseSimple("падре.", "святой отец."),
                                   "Я прибыл" + GetSexPhrase("", "а") + " по делу, " + RandPhraseSimple("падре.", "святой отец."));
        link.l3.go = "work";

        //--> Сага
        // Картахена, Чика Гонсалес
        if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && pchar.location == "Cartahena_church" && sti(pchar.money) >= 1000)
        {
            link.l4 = "Я хочу заказать молебен за упокой души одной сeньоры.";
            link.l4.go = "saga";
        }
        // поиски исцеления от заклятий
        if (CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location != "Bridgetown_church" && !CheckAttribute(npchar, "quest.seektreatment"))
        { // все церкви, кроме Бриджтауна
            link.l4 = "Святой отец, я нуждаюсь в помощи. Я тяжело болен. На меня наложены гнусные языческие заклятия. Прошу вас, помогите мне!";
            link.l4.go = "seektreatment";
        }
        if (CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location == "Bridgetown_church")
        { // попал в Бриджтаун
            link.l4 = "Святой отец, я нуждаюсь в помощи. Я тяжело болен. На меня наложены гнусные языческие заклятия. Прошу вас, помогите мне!";
            link.l4.go = "findtreatment";
        }
        if (CheckAttribute(pchar, "questTemp.Saga.JessFindTreatment") && pchar.location == "Bridgetown_church")
        { // пришел в Бриджтаун по направлению
            link.l4 = "Святой отец, я нуждаюсь в помощи. Я тяжело болен. На меня наложены гнусные языческие заклятия. Мне сказали, что именно вы сможете мне помочь. Прошу вас...";
            link.l4.go = "findtreatment";
        }
        // исцеление от заклятий Джесс
        if (CheckAttribute(pchar, "questTemp.Saga.JessTreatment") && pchar.location == "Bridgetown_church")
        {
            link.l4 = "Святой отец, я нуждаюсь в помощи. Я тяжело болен. На меня наложены гнусные языческие заклятия. Меня отправила к вам... Джессика Роуз. Она сказала, что вы поможете мне.";
            link.l4.go = "treatment";
        }
        if (CheckAttribute(npchar, "quest.candle"))
        {
            link.l4 = "Я по поводу свечей...";
            link.l4.go = "candle";
        }
        if (CheckAttribute(npchar, "quest.prayer") && GetNpcQuestPastDayParam(npchar, "prayer_date") >= 1 && stf(environment.time) >= 22.0)
        {
            link.l4 = "Я готов приступить к молитвам, святой отец.";
            link.l4.go = "prayer";
        }
        //<-- Сага

        // Warship, 30.05.11. Миниквест из дел чести "Божий суд".
        if (CheckAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest") && AffairOfHonor_GetCurQuest() == "GodJudgement" &&
            NPChar.city == PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId)
        {
            link.l5 = "Страшные вещи творятся, Святой Отец.";
            link.l5.go = "AffairOfHonor_GodJudgement_1";
        }

        link.l6 = "Извините, мне пора идти.";
        link.l6.go = "exit";
        break;

    case "AffairOfHonor_GodJudgement_1":
        dialog.text = "Не беспокойся, сын мой. Господь увидит твои страдания и поможет тебе. Всегда носи с собой крест для укрепления веры.";
        Link.l1 = "Благодарю вас, Святой Отец.";
        Link.l1.go = "exit";
        AddItems(PChar, "amulet_3", 15);
        DeleteAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest");
        break;

        // Jason-------------------------------------------------Сага----------------------------------------------
        //--> Чика Гонсалес
    case "saga":
        dialog.text = "Я со смирением исполню вашу волю за 1000 песо.";
        Link.l1 = "Пожалуйста, святой отец, вот монеты.";
        Link.l1.go = "saga_1";
        break;

    case "saga_1":
        AddMoneyToCharacter(pchar, -1000);
        dialog.text = "Благодарю, сын мой. Как зовут сеньору, о душе которой я должен молиться?";
        Link.l1 = "Ее зовут Чика Гонзалес. Она уроженка вашего города и отошла в мир иной много лет тому назад.";
        Link.l1.go = "saga_2";
        break;

    case "saga_2":
        dialog.text = "Странно... Неужели с Альваресом что-то случилось, и он попросил вас об этой услуге?";
        Link.l1 = "А кто такой этот Альварес, и что странного в моей просьбе?";
        Link.l1.go = "saga_3";
        break;

    case "saga_3":
        dialog.text = "Ну как же! Каждый месяц смотритель нашего маяка Альварес на протяжении двух десятков лет заказывает молебен за упокой души этой синьоры. Никому кроме него до сих пор не было никакого дела до синьоры Гонзалес. И тут приходите вы. Вот я и подумал\nВпрочем, это не мое дело. Конечно, я с радостью и смирением исполню ваше желание помочь заблудшей душе найти успокоение и дорогу в небеса обетованные.";
        Link.l1 = "Благодарю вас, святой отец.";
        Link.l1.go = "saga_4";
        break;

    case "saga_4":
        DialogExit();
        AddQuestRecord("Saga", "15");
        Saga_SetOrtega();
        pchar.questTemp.Saga = "ortega";
        pchar.quest.Saga_Gonsales1.over = "yes"; //снять возможное прерывание
        if (GetCharacterIndex("SagaGonsalesB") != -1)
        {
            sld = characterFromId("SagaGonsalesB");
            sld.lifeday = 0;
        }
        break;
    // <-- Чика Гонсалес

    // --> исцеление от заклятий
    case "treatment":
        dialog.text = "Джессика? Я помню её. Несчастная грешница. Разве она не умерла?";
        link.l1 = "Она умерла, святой отец. Уже умерла... упокой Господи её душу. Но она уверила, что вы поможете мне.";
        link.l1.go = "treatment_1";
        DeleteAttribute(pchar, "questTemp.Saga.JessTreatment");
        break;

    case "treatment_1":
        dialog.text = "Кто наложил на тебя эти заклятия, сын мой? Отвечай мне честно.";
        link.l1 = "Она... она сама. Джессика.";
        link.l1.go = "treatment_2";
        break;

    case "treatment_2":
        dialog.text = "Господи, храни нас! Я так и думал. Познание языческих обрядов способно ввергнуть в пучину тьмы и более сильную душу... Она действительно умерла, или... не совсем?";
        link.l1 = "Вы невероятно проницательны, святой отец. Теперь - совсем...";
        link.l1.go = "treatment_3";
        break;

    case "treatment_3":
        dialog.text = "Я исповедовал эту бедную грешницу, и не один раз. Ненависть разрушила её изнутри. Я знал, что она задумала. Я пытался её остановить, наставить на путь истинный, но усилия мои оказались тщетны. Я предупреждал об ужасной опасности и последствиях, которые несут нечестивые обряды...";
        link.l1 = "Да, святой отец. То, что мне довелось увидеть, было воистину ужасно. Но как мне исцелиться?";
        link.l1.go = "treatment_4";
        break;

    case "treatment_4":
        dialog.text = "Молитвой, сын мой. Святой очищающей молитвой в нашем храме. Ты должен будешь молиться очень долго, причем не только за себя. Ты должен будешь также молиться и за неё.";
        link.l1 = "За Джессику?";
        link.l1.go = "treatment_5";
        break;

    case "treatment_5":
        dialog.text = "Да. За себя и за неё. Чтобы никто тебе не мешал, тебе надлежит прийти сюда в десять часов вечера. Молиться придётся всю ночь. Ты должен принести двадцать толстых восковых свечей, и провести в молитве время до тех пор, пока они не сгорят полностью.";
        link.l1 = "И после этого я исцелюсь?";
        link.l1.go = "treatment_6";
        break;

    case "treatment_6":
        dialog.text = "Всё в руках Господа, сын мой. Я научу тебя молитвам и оставлю Священное Писание. Сила святой молитвы разрушит нечестивые заклятия, поразившие тебя и... очистит душу несчастной Джессики.";
        if (GetCharacterItem(pchar, "mineral3") >= 20)
        {
            link.l1 = "У меня есть с собой двадцать восковых свечей. Я готов остаться в храме и начать молиться.";
            link.l1.go = "treatment_9";
        }
        else
        {
            link.l1 = "У меня пока нет с собой двадцати свечей. Я принесу их!";
            link.l1.go = "treatment_7";
        }
        break;

    case "treatment_7":
        dialog.text = "Хорошо, сын мой. Я буду ждать тебя. Не теряй времени!";
        link.l1 = "Я скоро буду...";
        link.l1.go = "treatment_8";
        break;

    case "treatment_8":
        DialogExit();
        npchar.quest.candle = "true";
        break;

    case "candle":
        dialog.text = "Ты принес двадцать свечей, сын мой?";
        if (GetCharacterItem(pchar, "mineral3") >= 20)
        {
            link.l1 = "Да, святой отец. У меня есть с собой двадцать восковых свечей. Я готов остаться в храме и начать молиться.";
            link.l1.go = "treatment_9";
            DeleteAttribute(npchar, "quest.candle");
        }
        else
        {
            link.l1 = "Пока нет. Но я обязательно принесу их.";
            link.l1.go = "exit";
        }
        break;

    case "treatment_9":
        dialog.text = "Очень хорошо, сын мой. Давай мне их и приходи завтра после деcяти вечера. Я научу тебя нужным молитвам и оставлю тебя в церкви на ночь.";
        link.l1 = "Хорошо, святой отец. До завтра!";
        link.l1.go = "treatment_10";
        break;

    case "treatment_10":
        DialogExit();
        RemoveItems(pchar, "mineral3", 20);
        LAi_RemoveLoginTime(npchar);
        LAi_SetLoginTime(npchar, 6.0, 22.99);
        npchar.quest.prayer = "true";
        SaveCurrentNpcQuestDateParam(npchar, "prayer_date");
        break;

    case "prayer":
        dialog.text = "Я подготовил тексты молитв для тебя, сын мой. Также я оставляю тебе Священное Писание и твои двадцать свечей. Зажги свечи и молись. Молись без остановки, за своё исцеление и за душу бедной грешницы Джессики. Если ты что-то забудешь, или не поймёшь - молись, как сможешь сам, ибо Господу важно твоё чистое желание.";
        link.l1 = "Хорошо, святой отец. Я всё понял.";
        link.l1.go = "prayer_1";
        break;

    case "prayer_1":
        dialog.text = "Я вернусь утром, сын мой. Я тоже буду молиться...";
        link.l1 = "Спасибо, святой отец.";
        link.l1.go = "prayer_2";
        break;

    case "prayer_2":
        DialogExit();
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_BarbadosTreatment", -1);
        chrDisableReloadToLocation = true; //закрыть локацию
        break;

    case "seektreatment":
        dialog.text = "Какие языческие заклятия поразили тебя, сын мой?";
        link.l1 = "Я не знаю, как они называются. У меня слабость, вялость, совсем не могу бегать и мне тяжело сражаться.";
        link.l1.go = "seektreatment_1";
        break;

    case "seektreatment_1":
        if (sti(pchar.questTemp.Saga.JessSeekTreatment) == 3)
        {
            dialog.text = "Я слышал о таких... Их принесли в наш мир нечестивые колдуны краснокожих безбожников. Лучше всего тебе обратиться к настоятелю церкви Бриджтауна - он посвятил несколько лет своей жизни изучению влияния разрушительных чар индейцев на тела и души христиан.";
            link.l1 = "Он сможет помочь мне?!";
            link.l1.go = "seektreatment_4";
        }
        else
        {
            dialog.text = "Я слышал о таких... Их принесли в наш мир нечестивые колдуны краснокожих безбожников. К сожалению, я могу лишь посоветовать тебе больше времени проводить в молитвах, сын мой, и уповать на милость Господа нашего.";
            link.l1 = "Неужели ничего нельзя сделать, святой отец?! Я до конца своих дней останусь... таким?";
            link.l1.go = "seektreatment_2";
        }
        break;

    case "seektreatment_2":
        dialog.text = "Не отчаивайся, сын мой. Господь услышит тебя и ниспошлет помощь. Но также я тебе посоветую поспрашивать в других святых обителях - возможно, кто-то из священников больше знает о том, как снять языческие чары...";
        link.l1 = "Спасибо, святой отец. Я обойду хоть все церкви на архипелаге, но излечусь!";
        link.l1.go = "seektreatment_3";
        break;

    case "seektreatment_3":
        dialog.text = "Ступай, сын мой, и да хранит тебя Господь.";
        link.l1 = "До свидания, падре.";
        link.l1.go = "exit";
        npchar.quest.seektreatment = "true";
        pchar.questTemp.Saga.JessSeekTreatment = sti(pchar.questTemp.Saga.JessSeekTreatment) + 1;
        break;

    case "seektreatment_4":
        dialog.text = "Помочь тебе может только Господь и ты сам, сын мой. Святой отец лишь научит тебя, что и как ты должен делать. Ступай к нему.";
        link.l1 = "Спасибо, падре! Вы меня спасли... Немедленно отправляюсь на Барбадос!";
        link.l1.go = "seektreatment_5";
        break;

    case "seektreatment_5":
        dialog.text = "Ступай, и да хранит тебя Господь.";
        link.l1 = "До свидания, святой отец.";
        link.l1.go = "exit";
        DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment");
        pchar.questTemp.Saga.JessFindTreatment = "true";
        break;

    case "findtreatment":
        dialog.text = "Какие языческие заклятия поразили тебя, сын мой? Позволь предположить: ты не можешь бегать, сабля для тебя слишком тяжела, а движения твои - вялы?";
        link.l1 = "Как вы догадались, святой отец?!";
        link.l1.go = "findtreatment_1";
        break;

    case "findtreatment_1":
        dialog.text = "Глядя на то, какой поступью ты подошел ко мне, сын мой, понять было нетрудно. Господи, помилуй нас, грешных... Отвечай мне честно, сын мой: кто наложил на тебя эти заклятия?";
        link.l1 = "Вам нужно имя, святой отец?";
        link.l1.go = "findtreatment_2";
        break;

    case "findtreatment_2":
        dialog.text = "Если ты знаешь его - то назови имя.";
        link.l1 = "Ее звали... Джессика Роуз.";
        link.l1.go = "findtreatment_3";
        break;

    case "findtreatment_3":
        dialog.text = "Господи, храни нас! Познание языческих обрядов способно ввергнуть в пучину тьмы и более сильную душу... Что сталось с ней, с этой несчастной?";
        link.l1 = "Она умерла, святой отец.";
        link.l1.go = "findtreatment_4";
        break;

    case "findtreatment_4":
        dialog.text = "Она действительно умерла, или... не совсем?";
        link.l1 = "Вы невероятно проницательны, святой отец. Теперь - совсем...";
        link.l1.go = "treatment_3";
        DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment"); // если было
        DeleteAttribute(pchar, "questTemp.Saga.JessFindTreatment"); // если было
        break;
    //<-- Сага

    // Church GenQuest_2 -->
    case "GenQuest_Church_2_Start_1":
        dialog.text = "...и милости Божьей! Да поглотит их души мрак вселенский за прегрешения...";
        link.l1 = LinkRandPhrase("Святой отец", "Падре", "Отче") + ", не слишком ли вы усердствуете? Так недолго и удар получить.";
        link.l1.go = "GenQuest_Church_2_Start_2";
        link.l2 = RandPhraseSimple("О-о... Не буду вам мешать...", "Я, кажется, не вовремя - пойду, пожалуй...");
        link.l2.go = "exit";
        break;

    case "GenQuest_Church_2_Start_2":
        dialog.text = "О, " + GetSexPhrase("сын мой", "дочь моя") + ", совершено ужасное кощунство, позорнейшее из преступлений! Обокрасть церковь!!! Да это всё равно, что запустить свои грязные лапы прямо в карман Господу!";
        link.l1 = "Ах, вот оно что!.. И как же это случилось?";
        link.l1.go = "GenQuest_Church_2_Start_3";
        link.l2 = LinkRandPhrase("Это всё, конечно, печально, но я, пожалуй, пойду...", "Сочувствую, падре, но мне уже пора...", "Наверное вы слишком понадеялись на Господа, нужно было замки ставить покрепче. Пойду я, пожалуй...");
        link.l2.go = "exit";
        break;

    case "GenQuest_Church_2_Start_3":
        dialog.text = "Какие-то мерзавцы под покровом ночи вынесли всё, что было собрано паствой! И жертвенную чашу прихватили, безбожники!";
        link.l1 = "Да уж, времена... Но, я надеюсь, вы предприняли какие-то шаги по горячим следам?";
        link.l1.go = "GenQuest_Church_2_Start_4";
        break;

    case "GenQuest_Church_2_Start_4":
        dialog.text = "О да! Конечно!! Я отлучил богомерзких грабителей от церкви! А сейчас предаю их души анафеме.";
        link.l1 = "Не сомневаюсь, что это самая действенная мера. Но я имел" + GetSexPhrase("", "а") + " в виду нечто более практичное. Организовать погоню, к примеру.";
        link.l1.go = "GenQuest_Church_2_Start_5";
        break;

    case "GenQuest_Church_2_Start_5":
        dialog.text = "Ах, " + GetSexPhrase("сын мой", "дочь моя") + ", что может простой священник, связанный обетом непротивления злу? Эти негодяи наверняка уже далеко отсюда - пропивают в тавернах  награбленное, или предаются разврату и беспутству в объятиях блудниц! Надеюсь, там им и придет конец!";
        link.l1 = RandPhraseSimple("Хм, я уверен" + GetSexPhrase("", "а") + ", что такой исход гораздо привлекательнее, нежели болтаться на рее. Впрочем, не буду вам мешать. Всего доброго.", "Хм, ну раз всем нам рано или поздно суждено отправиться к праотцам - от такого исхода и я бы не отказал" + GetSexPhrase("ся", "ась") + ". Впрочем, мне уже пора. Желаю успехов в вашем нелёгком труде.");
        link.l1.go = "exit";
        link.l2 = LinkRandPhrase("Святой отец", "Падре", "Отче") + ", но ведь я никакими обетами не связан" + GetSexPhrase("", "а") + ", и с готовностью помогу Господу приблизить час возмездия.";
        link.l2.go = "GenQuest_Church_2_Start_5_1";
        break;

    case "GenQuest_Church_2_Start_5_1": //выше - выход из диалога без подтверждения - странно, однако
        dialog.text = "Я буду молиться за тебя, сын мой! Иди и воздай этим мошенникам по заслугам!";
        link.l1 = "Можете не сомневаться, " + RandPhraseSimple("падре.", "святой отец.");
        link.l1.go = "GenQuest_Church_2_Start_6";
        break;

    case "GenQuest_Church_2_Start_6":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        PChar.GenQuest.ChurchQuest_2.StartQuest = true;
        PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City; // Город, в котором спрашиваем
        PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
        PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; // На каком острове опрашиваем бандюков
        PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
        PChar.GenQuest.ChurchQuest_2.AskPeople = true;
        PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
        PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
        PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank) + 8) * 543 + 3210;
        PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount) / 3);
        sQuestTitle = NPChar.City + "ChurchGenQuest2";
        ReOpenQuestHeader(sQuestTitle);
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
        AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
        AddQuestUserData(sQuestTitle, "sName", NPChar.name);
        break;

    case "GenQuest_Church_2_Thief_2":
        dialog.text = "Ну, разве всеблагой Создатель нашлёт мор и глад на неразумных детей своих, дабы покарать за грехи их тяжкие...";
        link.l1 = "Например, за гордыню, или, допустим, алчность... Что это вы так побледнели, Падре?";
        link.l1.go = "GenQuest_Church_2_Thief_3";
        break;

    case "GenQuest_Church_2_Thief_3":
        if (rand(1) == 0) // Священник искренне раскаивается...
        {
            dialog.text = "Господи Иисусе... помилуй мя, грешного... Вы нашли... грабителей? Вы их убили?";
            link.l1 = "Или возьмём десять заповедей, которые известны каждому доброму христианину с младенчества: не убий, не укради, не произноси лжесвидетельства против ближнего своего. Разве может нарушить их богобоязненный человек? А уж тем более, духовный пастырь?!..";
            link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
        }
        else
        {
            dialog.text = "Здесь очень душно... Так вы нашли грабителей? Вы их убили?..";
            link.l1 = "Или возьмём десять заповедей, которые известны каждому доброму христианину с младенчества: не убий, не укради, не произноси лжесвидетельства против ближнего своего. Разве может нарушить их богобоязненный человек? А уж тем более, духовный пастырь?!..";
            link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
        }
        break;

    case "GenQuest_Church_2_Thief_4_1_1":
        dialog.text = "" + GetSexPhrase("Сын мой, сударь", "Дочь моя, сударыня") + "... Господи прости... такие деньги, такое искушение... слаб человек, слаб! Не устоял... Места себе не находил... Непрестанно возносил молитвы, исполнял епитимию, соблюдал строгий пост... умерщвлял плоть и, недостойный, просил небеса об одном лишь - чтобы живы остались те несчастные, которых ввёл во грех, движимый алчностью...";
        link.l1 = LinkRandPhrase("Святой Отец", "Падре", "Отче") + ", успокойтесь. Главное, что они никому ничего не рассказали... и не расскажут. Кстати, они добровольно отдали мне чашу для причастия, которую я вам и привез" + GetSexPhrase("", "ла") + ".";
        link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
        break;

    case "GenQuest_Church_2_Thief_4_1_2":
        dialog.text = "Благодарю тебя, Боже! Услышаны молитвы недостойного раба, оступившегося грешника, погрязшего в скверне и пороке...";
        link.l1 = "Оступиться может каждый... Однако, видя ваше искреннее раскаяние, я скажу так: человек вы неплохой, и священник хороший. Если вы пойдёте под суд, никому от этого пользы не будет. А уж оставаться или нет на службе Господу, это вы решите сами в ваших с Ним беседах...";
        link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
        break;

    case "GenQuest_Church_2_Thief_4_1_3":
        if (rand(1) == 0) // Священник хочет всучить ГГ бабло
        {
            dialog.text = "" + GetSexPhrase("Сын мой", "Дочь моя") + "... Со слезами раскаяния и благодарности принимаю от вас чашу. Чистота и благородство вашей души потрясли меня. От всего сердца благословляю вас и умоляю принять это скромное вознаграждение в размере " + FindRussianMoneyString(iMoneyToCharacter) + "... Надеюсь, оно окупит ваши расходы?";
            // ГГ не берет деньги. Плюсанем репу
            link.l1 = "Это лишнее, отец " + NPChar.name + ". Я и так небед" + GetSexPhrase("ен", "на") + ", а эти деньги используйте на благо ваших прихожан.";
            link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
            // ГГ берет деньги
            link.l2 = "Благодарю, " + LinkRandPhrase("святой отец", "падре", "отче") + ", этого вполне достаточно.";
            link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
        }
        else
        {
            dialog.text = "" + GetSexPhrase("Сын мой", "Дочь моя") + "... Со слезами раскаяния и благодарности принимаю от вас чашу, как знак Божьей милости и прощения. Чистота и благородство вашей души потрясли меня. От всего сердца благословляю вас!";
            link.l1 = "Спасибо за благословение, " + LinkRandPhrase("падре", "отче") + ".";
            link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
            link.l1 = "Благословение, конечно, дело нужное, но неплохо бы подкрепить его чем-то более материальным, так как в дороге я понёс" + GetSexPhrase("", "ла") + " немалые траты...";
            link.l1.go = "GenQuest_Church_2_Thief_4_1_6";
        }
        ChurchGenQuest2_RemoveCup();
        break;

    case "GenQuest_Church_2_Thief_4_1_4":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        ChangeCharacterComplexReputation(PChar, "nobility", 3);
        sQuestTitle = NPChar.City + "ChurchGenQuest2";
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
        AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("cя", "ась"));
        AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
        CloseQuestHeader(sQuestTitle);
        DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
        NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
        break;

    case "GenQuest_Church_2_Thief_4_1_5":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
        ChangeCharacterComplexReputation(PChar, "nobility", -2);
        sQuestTitle = NPChar.City + "ChurchGenQuest2";
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
        AddQuestUserData(sQuestTitle, "sName", NPChar.name);
        CloseQuestHeader(sQuestTitle);
        DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
        NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
        break;

    case "GenQuest_Church_2_Thief_4_1_6":
        iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
        dialog.text = "Ох, дитя моё, совсем забыл... Надеюсь, эта скромная лепта в размере " + FindRussianMoneyString(iMoneyToCharacter) + " окупит Ваши расходы?";
        link.l1 = "Да, " + LinkRandPhrase("падре", "отче") + ", спасибо.";
        link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
        break;

    case "GenQuest_Church_2_Thief_4_1_6_1":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        ChangeCharacterComplexReputation(PChar, "nobility", -2);
        AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
        sQuestTitle = NPChar.City + "ChurchGenQuest2";
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
        AddQuestUserData(sQuestTitle, "sName", NPChar.name);
        CloseQuestHeader(sQuestTitle);
        DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
        NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
        break;

    case "GenQuest_Church_2_Thief_4_2_1":
        dialog.text = "Я не понимаю ваших намёков, " + GetSexPhrase("сын мой", "дочь моя") + ", о чём это вы говорите?!";
        link.l1 = "Я говорю о страшных вещах, которые способна сотворить с человеком жадность. И об этой чаше для причастия, которую я получил" + GetSexPhrase("", "а") + " от оборванцев, якобы ограбивших вашу церковь... Вы что-то хотели сказать?";
        link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
        break;

    case "GenQuest_Church_2_Thief_4_2_2":
        dialog.text = "Я скажу, дитя моё, что вы весьма непочтительны с лицом духовного звания, и что вы можете об этом пожалеть. А эту чашу я впервые вижу, но если вы желаете пожертвовать её в пользу прихода, то...";
        link.l1 = "Полегче, падре, вы её не получите, пока не объяснитесь.";
        link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
        break;

    case "GenQuest_Church_2_Thief_4_2_3":
        if (rand(1) == 0) // Просто несколько разные варианты диалога
        {
            dialog.text = "Что я должен вам объяснять?! Вы же " + GetSexPhrase("умный человек", "умная девушка") + ", и сами должны понимать - всё, что наговорили эти проходимцы о том, что я их якобы нанял - это всё наглая ложь! Господь покарает этих безбожников не только за кощунство, но и за лжесвидетельство!";
            link.l1 = "Оставьте Господа в покое! Откуда вы знаете, что сказали мне те несчастные, на которых вы меня натравили? Может, я убил" + GetSexPhrase("", "а") + " их прежде, чем они успели поведать о ваших гнусных делишках?";
            link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
        }
        else
        {
            dialog.text = "Мне не о чем с вами говорить, вы не выполнили обязательства, взятого перед лицом Господа, сквернословите в храме, пытаетесь шантажировать священника, потрясая церковной утварью, которую заполучили неизвестно каким путём! И благодарите Бога, что я не зову послушников, чтобы задержать вас с поличным!";
            link.l1 = "Что ж... я вижу, вы погрязли в грехе настолько, что не боитесь людского суда. Но есть Высший Суд, перед которым все мы рано или поздно предстанем. Возьмите вашу 'церковную утварь' и подумайте о том, достойны ли вы прикасаться к ней, отец " + NPChar.name + ".";
            link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
            link.l2 = "Простите мои сомнения, святой отец, ибо сердце человеческое слабо, а душа в смятении. Возьмите чашу и благословите меня.";
            link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
        }
        break;

    case "GenQuest_Church_2_Thief_4_2_4_1":
        dialog.text = "Э-э-э... " + GetSexPhrase("Сын мой... Сударь... Господин", "Дочь моя... Сударыня... Госпожа") + " " + PChar.name + "... я готов пойти вам навстречу... рассмотреть наши разногласия.... компенсировать ваши дорожные расходы вот этой скромной суммой в размере " + FindRussianMoneyString(iMoneyToCharacter) + "... конечно, в том случае, если вы не станете вмешивать в это дело посторонних...";
        // При этом варианте репу плюсуем
        link.l1 = "Я никого не собираюсь вмешивать. Забирайте чашу! И не думайте, что я возьму золото, которое вы тайком таскаете из карманов ваших прихожан!";
        link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_1";
        // При этом - минусуем
        link.l2 = "Я никого не собираюсь вмешивать. Возьмите чашу! Это золото я беру лишь потому, что потратил" + GetSexPhrase("", "а") + " на вас слишком много времени и денег, но ничто не компенсирует моё глубокое разочарование в вас!";
        link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_2";
        break;

    case "GenQuest_Church_2_Thief_4_2_4_1_1":
        DialogExit();
        iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
        NextDiag.CurrentNode = NextDiag.TempNode;
        ChangeCharacterComplexReputation(PChar, "nobility", -2);
        AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
        ChurchGenQuest2_RemoveCup();
        sQuestTitle = NPChar.City + "ChurchGenQuest2";
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
        AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ен", "на"));
        AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("", "а"));
        AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("", "ла"));
        AddQuestUserData(sQuestTitle, "sName", NPChar.name);
        AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoneyToCharacter));
        CloseQuestHeader(sQuestTitle);
        DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
        NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
        break;

    case "GenQuest_Church_2_Thief_4_2_4_1_2":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        ChangeCharacterComplexReputation(PChar, "nobility", 3);
        ChurchGenQuest2_RemoveCup();
        sQuestTitle = NPChar.City + "ChurchGenQuest2";
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
        AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
        CloseQuestHeader(sQuestTitle);
        DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
        NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
        break;

    case "GenQuest_Church_2_Thief_4_2_4_2_1":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        ChurchGenQuest2_RemoveCup();
        ChangeCharacterComplexReputation(PChar, "nobility", 3);
        sQuestTitle = NPChar.City + "ChurchGenQuest2";
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
        AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ен", "на"));
        AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("", "а"));
        AddQuestUserData(sQuestTitle, "sName", NPChar.name);
        CloseQuestHeader(sQuestTitle);
        DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
        NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
        break;

    case "GenQuest_Church_2_Thief_4_2_4_2_2":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        ChurchGenQuest2_RemoveCup();
        sQuestTitle = NPChar.City + "ChurchGenQuest2";
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
        AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ся", "ась"));
        AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
        CloseQuestHeader(sQuestTitle);
        DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
        NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
        break;

    case "GenQuest_Church_2_Finally_Complete_1":
        // ничего не принесли священнику.
        if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All"))
        {
            link.l1 = "Известия неутешительные, " + LinkRandPhrase("святой отец", "падре", "отче") + ": грабители оказались столь коварны и изворотливы, что мне не удалось вернуть церковное золото...";
            link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
            break;
        }
        // Принесли священнику только чашу.
        if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
        {
            link.l1 = "Известия неутешительные, " + LinkRandPhrase("святой отец", "падре", "отче") + ": мне удалось настичь похитителей, но моим единственным трофеем оказалась вот эта чаша для причастия.";
            link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
            ChurchGenQuest2_RemoveCup();
            break;
        }
        // Принесли священнику и деньги и чашу.
        if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
        {
            if (sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
            {
                link.l1 = "Уверен" + GetSexPhrase("", "а") + ", что известия вас обрадуют - я примерно наказал" + GetSexPhrase("", "а") + " грабителей и забрал" + GetSexPhrase("", "а") + " у них приходские деньги, а также вот эту чашу для причастия.";
                link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
            }
            // Деньги можно заныкать.
            link.l2 = LinkRandPhrase("Святой отец", "Падре", "Отче") + ", я принёс" + GetSexPhrase("", "ла") + " дурные вести... Мне пришлось потратить много времени, сил и средств, чтобы выследить мерзавцев, но, когда я всё-таки добрал" + GetSexPhrase("ся", "ась") + " до них, оказалось, что они успели пропить и промотать всё, кроме вот этой чаши для причастия...";
            link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
            ChurchGenQuest2_RemoveCup();
            break;
        }
        // Священник - вор.
        if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
        {
            dialog.text = "Ах, " + GetSexPhrase("сын мой", "дочь моя") + ", да что могло со мной случиться? Это ваш путь полон опасностей и тревог, а моя мирная келья - предел раздумий и молитв - как тихий остров в бушующем океане человеческих страстей...";
            link.l1 = "Неужели ничто не в силах поколебать покой вашего блаженного уединения?";
            link.l1.go = "GenQuest_Church_2_Thief_2";
            break;
        }
        // Короткий вариант прохождения квеста.
        if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
        {
            if (sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
            {
                link.l1 = "Уверен" + GetSexPhrase("", "а") + ", что известия вас обрадуют - я примерно наказал" + GetSexPhrase("", "а") + " грабителей и привёз" + GetSexPhrase("", "ла") + " приходские деньги.";
                link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
            }
            // Деньги можно заныкать.
            link.l2 = LinkRandPhrase("Святой отец", "Падре", "Отче") + "... Я вынужден" + GetSexPhrase("", "а") + " вас огорчить. Я преследовал" + GetSexPhrase("", "а") + " грабителей по всему архипелагу, преодолел" + GetSexPhrase("", "а") + " множество опасностей и преград, почти разорил" + GetSexPhrase("ся", "ась") + " и в конце-концов настиг" + GetSexPhrase("", "ла") + " их, но увы... они уже успели промотать церковные деньги.";
            link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
        }
        break;

    case "GenQuest_Church_2_Finally_Complete_1_3_1": // ГГ решил заныкать деньги...
        if (rand(1) == 0)                            // Священник верит ГГ но не дает денег...
        {
            if (rand(4) == 3) // Более "мягкий" исход событий.
            {
                dialog.text = "Ох, " + GetSexPhrase("сын мой", "дочь моя") + ". Ваши слова повергли меня в глубокую скорбь, но не в отчаяние, ибо отчаяние - смертный грех! Господь насылает на нас очередное испытание, чтобы укрепить нашу веру.";
                link.l1 = "Аминь, святой отец...";
                link.l1.go = "exit";
                sQuestTitle = NPChar.City + "ChurchGenQuest2";
                AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
                AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
                CloseQuestHeader(sQuestTitle);
                ChangeCharacterComplexReputation(PChar, "nobility", -2);
                DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
                NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
            }
            else
            {
                dialog.text = "" + GetSexPhrase("Сын мой", "Дочь моя") + ", не лги духовному пастырю своему.";
                link.l1 = "Мне жаль, отче, но, клянусь всеми святыми - я говорю правду...";
                link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
            }
        }
        else
        {
            // Священник дает деньги ГГ...
            iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
            dialog.text = "Ох, " + GetSexPhrase("сын мой", "дочь моя") + ". Ваши слова повергли меня в глубокую скорбь, но не в отчаяние, ибо отчаяние - смертный грех! Господь насылает на нас очередное испытание, чтобы укрепить нашу веру. Однако ваши усилия и затраты должны быть вознаграждены, хоть и не принесли плодов. Возьмите эту небольшую сумму - " + FindRussianMoneyString(iMoneyToCharacter) + " -  и продолжайте ваш праведный путь!";
            link.l1 = "Э-хм!... Спасибо, падре, я направлю эти деньги на богоугодное дело.";
            link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
            link.l2 = LinkRandPhrase("Святой отец", "Падре", "Отче") + "... вы ставите меня в неловкое положение. Я не могу принять от вас вознаграждение за невыполненную работу, лучше обновите на эти деньги алтарь.";
            link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
        }
        break;

    case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
        if (rand(6) == 3)
        {
            dialog.text = "Хорошо, я тебе верю, " + GetSexPhrase("сын мой", "дочь моя") + ". Господь подвергает нас очередному испытанию, чтобы укрепить нашу веру.";
            link.l1 = "Аминь...";
            link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1" break;
        }
        dialog.text = "Презренн" + GetSexPhrase("ый", "ая") + ", неужели ты думал" + GetSexPhrase("", "а") + ", что способ" + GetSexPhrase("ен", "на") + " обмануть Господа нашего? Будь ты проклят" + GetSexPhrase("", "а") + "! Убирайся прочь и помни, что эти деньги не принесут тебе никакой пользы!";
        link.l1 = "Как же так!.. падре!..";
        link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
        break;

    case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        sQuestTitle = NPChar.City + "ChurchGenQuest2";
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
        AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
        CloseQuestHeader(sQuestTitle);
        AddCharacterExpToSkill(PChar, "Sneak", 20);
        ChangeCharacterComplexReputation(PChar, "nobility", -3);
        DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
        NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
        break;

    case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        sQuestTitle = NPChar.City + "ChurchGenQuest2";
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
        AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
        CloseQuestHeader(sQuestTitle);
        ChangeCharacterComplexReputation(PChar, "nobility", -6);
        AddCharacterExpToSkill(PChar, "Leadership", -50);
        AddCharacterExpToSkill(PChar, "Fortune", -70);
        AddCharacterExpToSkill(PChar, "Sneak", 20);
        DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
        npchar.quest.BadMeeting = lastspeak_date;
        NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
        break;

    case "GenQuest_Church_2_Finally_Complete_1_4_1":
        if (rand(1) == 0) // Поверил.
        {
            dialog.text = "Ох, " + GetSexPhrase("сын мой", "дочь моя") + ". Ваши слова повергли меня в глубокую скорбь, но не в отчаяние, ибо отчаяние - смертный грех! Господь насылает на нас очередное испытание, чтобы укрепить нашу веру.";
            link.l1 = "Аминь, святой отец...";
            link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; // Переход сюда, т.к. одно и тоже.
        }
        else
        {
            dialog.text = "Да, это та самая чаша, которая пропала вместе с деньгами... Но... если вы добыли её, то почему не вернули и деньги? Там была немалая сумма, и простые мошенники не могли её так скоро потратить... " + GetSexPhrase("Сын мой", "Дочь моя") + ", помните, что нет худшего греха, нежели лгать своему духовному пастырю, да ещё и лжесвидетельствовать во храме, перед ликом Господа!!";
            link.l1 = "Отец " + NPChar.name + ", я чуть жизни не лишил" + GetSexPhrase("ся", "ась") + ", добывая эту вазу, думал" + GetSexPhrase("", "а") + " обрадовать вас, пусть не монетами, так хоть утварью. Я уже не говорю о своих расходах на это предприятие!";
            link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
        }
        break;

    case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
        dialog.text = "Подите прочь, судар" + GetSexPhrase("ь", "ыня") + ", и благодарите Создателя, который наградил меня мягким сердцем, ибо лишь по этой причине вы ещё не объявлены вор" + GetSexPhrase("ой", "овкой") + " и мошенни" + GetSexPhrase("ком", "цей") + "!";
        link.l1 = "Как же так?! " + LinkRandPhrase("святой отец", "падре", "отче") + "!..";
        link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
        break;

    case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        ChangeCharacterComplexReputation(PChar, "nobility", -5);
        sQuestTitle = NPChar.City + "ChurchGenQuest2";
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
        AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ся", "ась"));
        CloseQuestHeader(sQuestTitle);
        DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
        NPChar.quest.BadMeeting = lastspeak_date;
        NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
        break;

    case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
        DialogExit();
        iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
        NextDiag.CurrentNode = NextDiag.TempNode;
        ChangeCharacterComplexReputation(PChar, "nobility", -2);
        AddMoneyToCharacter(PChar, iMoneyToCharacter);
        sQuestTitle = NPChar.City + "ChurchGenQuest2";
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
        AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
        CloseQuestHeader(sQuestTitle);
        DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
        NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
        break;

    case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        ChangeCharacterComplexReputation(PChar, "nobility", -1);
        sQuestTitle = NPChar.City + "ChurchGenQuest2";
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
        AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
        CloseQuestHeader(sQuestTitle);
        DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
        NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
        break;

    case "GenQuest_Church_2_Finally_Complete_1_1_1":
        dialog.text = "Ох, " + GetSexPhrase("сын мой", "дочь моя") + ". Ваши слова повергли меня в глубокую скорбь, но не в отчаяние, ибо отчаяние - смертный грех! Господь насылает на нас очередное испытание, чтобы укрепить нашу веру.";
        link.l1 = "Аминь, святой отец...";
        link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
        break;

    case "GenQuest_Church_2_Finally_Complete_1_1_2":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        ChangeCharacterComplexReputation(PChar, "nobility", -2);
        sQuestTitle = NPChar.City + "ChurchGenQuest2";
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
        CloseQuestHeader(sQuestTitle);
        DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
        NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
        break;

    case "GenQuest_Church_2_Finally_Complete_1_2_1":
        dialog.text = "Боже, благодарю Тебя! Вы послужили орудием Господа, дитя моё! Я знал, что Отец наш небесный направит вас верным путём и не оставит своей помощью! Я непрестанно молился, и вот...";
        link.l1 = "Вообще-то, в таких делах больше пользы от оружия, чем от молитв, падре. Но, видимо, Бог действительно услышал ваши молитвы.";
        link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
        break;

    case "GenQuest_Church_2_Finally_Complete_1_2_2":
        dialog.text = "" + GetSexPhrase("Сын мой", "Дочь моя") + ", я хочу вознаградить вас по достоинству, ибо вы" + GetSexPhrase(", как истинный рыцарь Святой матери Церкви,", "") + " приложили все силы и преодо...";
        link.l1 = "Святой отец, вы слишком преувеличиваете мои скромные заслуги. Оставляю вас возносить хвалу Господу...";
        link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
        break;

    case "GenQuest_Church_2_Finally_Complete_1_2_3":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        ChangeCharacterComplexReputation(PChar, "nobility", 5);
        AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
        AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
        sQuestTitle = NPChar.City + "ChurchGenQuest2";
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
        AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
        AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
        CloseQuestHeader(sQuestTitle);
        DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
        NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
        break;
        // <-- квесты церкви

    case "donation":
        dialog.Text = "Конечно, " + GetSexPhrase("сын мой", "дочь моя") + ". Сколько ты желаешь пожертвовать Святой Церкви?";
        Link.l1 = "Простите, святой отец, но пожертвования не будет.";
        Link.l1.go = "No donation";
        if (makeint(PChar.money) >= 100)
        {
            Link.l2 = "Моя лепта будет скромной. Всего 100 песо.";
            Link.l2.go = "donation paid_100";
        }
        if (makeint(PChar.money) >= 1000)
        {
            Link.l3 = "1000 песо. Я думаю, этого хватит.";
            Link.l3.go = "donation paid_1000";
        }
        if (makeint(PChar.money) >= 5000)
        {
            Link.l4 = "Мне везёт с деньгами, поэтому я пожертвую 5000 песо.";
            Link.l4.go = "donation paid_5000";
        }
        //-->> квест пожертвования хозяйки борделя
        if (pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
        {
            Link.l5 = "Святой отец, я хочу сделать пожертвование не от себя. Я делаю это по поручению.";
            Link.l5.go = "HostessChurch";
        }
        //<<-- квест пожертвования хозяйки борделя
        break;

    case "No donation":
        dialog.Text = "Хм... Это ваше решение, и вы вправе его изменить. Но не забывайте, что это зачтется вам на Страшном Суде.";
        Link.l1 = "И не только это. Давайте лучше сменим тему.";
        Link.l1.go = "node_3";
        Link.l2 = "Извините, святой отец, мне пора.";
        Link.l2.go = "exit";
        break;

    case "donation paid_100":
        AddMoneyToCharacter(pchar, -100);
        pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
        dialog.Text = "От лица Святой Церкви благодарю вас, " + GetSexPhrase("сын мой", "дочь моя") + ", за ваш дар.";
        Link.l1 = "Мне надо поговорить с вами, святой отец.";
        Link.l1.go = "node_3";
        Link.l2 = "Извините, святой отец, мне пора.";
        Link.l2.go = "exit";
        AddDialogExitQuest("donation");
        break;

    case "donation paid_1000":
        AddMoneyToCharacter(pchar, -1000);
        pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
        dialog.Text = "От лица Святой Церкви благодарю вас, " + GetSexPhrase("сын мой", "дочь моя") + ", за ваш дар.";
        Link.l1 = "Мне надо поговорить с вами, святой отец.";
        Link.l1.go = "node_3";
        Link.l2 = "Извините, святой отец, мне пора.";
        Link.l2.go = "exit";
        AddDialogExitQuest("donation");
        break;

    case "donation paid_5000":
        AddMoneyToCharacter(pchar, -5000);
        pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
        dialog.Text = "От лица Святой Церкви благодарю вас, " + GetSexPhrase("сын мой", "дочь моя") + ", за ваш дар.";
        Link.l1 = "Мне надо поговорить с вами, святой отец.";
        Link.l1.go = "node_3";
        Link.l2 = "Извините, святой отец, мне пора.";
        Link.l2.go = "exit";
        AddDialogExitQuest("donation");
        break;

    case "ispoved":
        dialog.text = "Конечно же, " + GetSexPhrase("сын мой", "дочь моя") + ", я тебя слушаю.";
        link.l1 = "Я передумал" + GetSexPhrase("", "а") + ". Может быть в другой раз.";
        link.l1.go = "exit";
        link.l2 = "Я так греш" + GetSexPhrase("ен", "на") + ", святой отец. Чтобы перечислить все мои прегрешения, не хватит целого дня...";
        link.l2.go = "ispoved_1";
        break;

    case "ispoved_1":
        dialog.text = "Все мы грешны, дитя моё...";
        link.l1 = "Да, но на моей совести тяжким бременем лежит груз тысяч смертей. Я грабил" + GetSexPhrase("", "а") + " и топил" + GetSexPhrase("", "а") + " корабли...";
        link.l1.go = "ispoved_2";
        break;

    case "ispoved_2":
        dialog.text = "Я надеюсь, среди них не было таких, что ходили под флагом " + NationNameGenitive(sti(NPChar.nation)) + "?";
        link.l1 = "Нет, конечно, святой отец.";
        link.l1.go = "ispoved_3";
        link.l2 = "Всякие были, святой отец... всякие.";
        link.l2.go = "ispoved_4";
        break;

    case "ispoved_3":
        dialog.text = "Тогда Господь простит тебе эти грехи. Ибо век наш жесток, и уничтожая недругов своего государя, ты спасаешь жизни верных его подданных.";
        link.l1 = "Спасибо, святой отец, вы меня очень утешили... я пойду.";
        link.l1.go = "exit";
        break;

    case "ispoved_4":
        dialog.text = "Господь никогда не простит такого греха! Молись и кайся, кайся и молись! Одна тебе дорога - в монастырь!";
        link.l1 = "С монастырём придётся погодить. Не в этой жизни, по крайней мере. Прощайте...";
        link.l1.go = "exit";
        npchar.quest.BadMeeting = lastspeak_date;
        break;

    case "work":
        if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
        {
            dialog.text = "Сожалею, " + GetSexPhrase("сын мой", "дочь моя") + ", но сейчас все исповедальни заняты. Я буду рад выслушать твоё покаяние не раньше, чем через полчаса.";
            link.l1 = "Извините, " + RandPhraseSimple("падре", "святой отец") + ", это дело несколько иного характера. Отец " + PChar.GenQuest.ChurchQuest_1.PriestName + " из " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " некогда поделился с вами бесценными сокровищами своей богословской библиотеки, а сейчас поручил мне заехать за ними, если будет оказия.";
            link.l1.go = "GenQuest_Church_1_Dialog_1";
            DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
            break;
        }
        dialog.text = "Какое дело привело тебя, " + GetSexPhrase("сын мой", "дочь моя") + "?";
        link.l1 = "Я хотел" + GetSexPhrase("", "а") + " бы задать вам один вопрос, падре...";
        link.l1.go = "quests"; // ссылка к НПС
        link.l2 = RandPhraseSimple("Я хочу поговорить о работе на благо церкви " + NationNameGenitive(sti(NPChar.nation)) + ".",
                                   "Как идут дела в приходе, не нужна ли какая помощь?");
        link.l2.go = "prihod";
        if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
        {
            link.l3 = RandPhraseSimple("Святой отец", "Падре") + ", я хотел" + GetSexPhrase("", "а") + " бы поговорить с вами о финансовых вопросах."; //(пересылка в кредиты)
            link.l3.go = "LoanForAll";
        }
        // -->
        if (stf(pchar.Health.HP) < 60.0)
        {
            link.l4 = "Я нуждаюсь в исцелении.";
            link.l4.go = "healthAdd_1";
        }

        //квест мэра - на связь с нашим шпионом
        if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
        {
            link.l7 = RandPhraseSimple("Святой отец", "Падре") + ", я здесь по поручению одного человека. Его зовут губернатор " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".";
            link.l7.go = "IntelligenceForAll";
        }
        //--> Jason Церковная депеша
        if (CheckAttribute(pchar, "GenQuest.Monkletter") && npchar.city == pchar.GenQuest.Monkletter.City)
        {
            link.l10 = "Падре, я привёз для вас бумаги от монаха из города " + XI_ConvertString("Colony" + pchar.GenQuest.Monkletter.StartCity) + ".";
            link.l10.go = "Monkletter";
        }
        //<-- Церковная депеша
        //--> Jason Доставка молитвенников
        if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "go" && sti(npchar.nation) == sti(pchar.GenQuest.Churchbooks.Nation) && npchar.city != pchar.GenQuest.Churchbooks.StartCity)
        {
            link.l11 = "Падре, я прибыл из колонии " + XI_ConvertString("Colony" + pchar.GenQuest.Churchbooks.StartCity) + ". Местной церкви нужны молитвенники, и тамошний монах попросил меня обратиться за этим к вам.";
            link.l11.go = "Churchbooks";
        }
        if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "return" && npchar.city == pchar.GenQuest.Churchbooks.StartCity)
        {
            link.l11 = "Святой отец, я привёз молитвенники для вашего прихода.";
            link.l11.go = "Churchbooks_2";
        }
        //<-- Доставка молитвенников
        link.l99 = "Я передумал" + GetSexPhrase("", "а") + ", меня ждут дела.";
        link.l99.go = "exit";
        break;

    case "prihod":
        if (!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
        {
            dialog.text = "Это прекрасно. Однако в наши суровые дни, " + GetSexPhrase("сын мой", "дочь моя") + ", не каждый пришедший в храм способен принести пользу матери нашей Церкви.";
            link.l1 = LinkRandPhrase("Падре", "Святой отец", "Отец мой") + ", я истинно верующ" + GetSexPhrase("ий", "ая") + " христиан" + GetSexPhrase("ин", "ка") + ", и мои намерения послужить матери-Церкви - искренни." + GetSexPhrase(" Кто же станет её опорой, если не такие верные рыцари, как я?", "") + "";
            link.l1.go = "GenQuest_Church_1_Start_1";
            NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
        }
        else
        {
            NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date; // Если не дал сегодня, то токо на след день.
        }
        dialog.text = "У нас в приходе всё спокойно, " + GetSexPhrase("сын мой", "дочь моя") + ". Спасибо за предложение.";
        link.l2 = "Ну, раз всё хорошо, я пойду по своим делам.";
        link.l2.go = "exit";
        DeleteAttribute(npchar, "quest.add");
        NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date; // Если не дал сегодня, то токо на след день.
        break;

    // Church GenQuest_1 -->
    case "GenQuest_Church_1_Start_1":
        dialog.text = "Ну что ж, есть у меня одно деликатное поручение, исполнение которого потребует не только чистоты помыслов, но и немалой храбрости, а также тонкости ума...";
        link.l1 = LinkRandPhrase("Падре", "Святой отец", "Отец мой") + ", я буду счастлив" + GetSexPhrase("", "а") + " оказать вам любую услугу, даже если для этого мне придётся проскользнуть в саму преисподнюю! Не в церкви будь сказано.";
        link.l1.go = "GenQuest_Church_1_Start_2";
        break;

    case "GenQuest_Church_1_Start_2":
        PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
        Church_GenQuest1_InitStartParam(NPChar);
        dialog.text = "Вот как! Это хорошо... Но дело крайне деликатное... Некоторое время назад настоятель церкви " + PChar.GenQuest.ChurchQuest_1.ToName + " из " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + ", что на " + XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland + "Dat") + " попросил у меня на время несколько богословских трудов и древних рукописей из церковной библиотеки. Так как просьба была подкреплена требованием архиепископа не препятствовать распространению благостного света знаний, отказать я не мог, хотя и предполагал, что сложность морских путешествий не позволит ему вернуть рукописи в срок...\nНе могли бы вы поспособствовать разрешению этой проблемы?";
        link.l1 = "Боюсь, " + LinkRandPhrase("падре", "святой отец", "отец мой") + ", что не оправдаю вашего доверия. Дело слишком деликатное, и для его решения нужно быть изрядным дипломатом.";
        link.l1.go = "exit";
        link.l2 = LinkRandPhrase("Падре", "Святой отец", "Отец мой") + ", ваше поручение не представляется мне сложным. Я сегодня же отправлюсь в путь.";
        link.l2.go = "GenQuest_Church_1_Start_3";
        break;

    case "GenQuest_Church_1_Start_3": // Квест взят
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        PChar.GenQuest.ChurchQuest_1.StartQuest = true;
        PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
        PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
        PChar.GenQuest.ChurchQuest_1.AskOwner = true;
        sQuestTitle = NPChar.City + "ChurchGenQuest1";
        ReOpenQuestHeader(sQuestTitle);
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
        AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
        AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ся", "ась"));
        AddQuestUserData(sQuestTitle, "sName", NPChar.name);
        AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
        break;

    case "GenQuest_Church_1_Dialog_1":
        if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene")) // Сцена 2а
        {
            dialog.text = "О!.. Да... Действительно, припоминаю... Но, " + GetSexPhrase("сын мой", "дочь моя") + ", эти сокровища более духовны, нежели материальны, они принесли неизмеримую пользу моим прихожанам и могли бы приносить её впредь!";
            link.l1 = "Однако, " + LinkRandPhrase("падре", "святой отец", "отец мой") + ", души прихожан отца " + PChar.GenQuest.ChurchQuest_1.PriestName + " столь же нуждаются в спасении, а без этих трудов он лишён поддержки столпов теософии и вдохновения в своих проповедях.";
            link.l1.go = "GenQuest_Church_1_Dialog_1_1";
        }
        else // Сцена 2б-а и 2б-б
        {
            dialog.text = "О, да!.. Действительно... " + GetSexPhrase("Сын мой", "Дочь моя") + ", эти сокровища более духовны, нежели материальны, они принесли столько пользы моим прихожанам, что я, к стыду своему, несколько задержался с их возвращением владельцу...";
            link.l1 = "Именно, " + RandPhraseSimple("падре", "святой отец") + ", именно. Поэтому отец " + PChar.GenQuest.ChurchQuest_1.PriestName + " и поручил мне доставить эти книги лично ему в руки.";
            link.l1.go = "GenQuest_Church_1_Dialog_1_2";
        }
        break;

    case "GenQuest_Church_1_Dialog_1_1": // Сцена 2а
        dialog.text = "Я понимаю, дитя моё, но разве не возносим мы каждодневно молитву Господу: 'и прости нам, как мы прощаем должникам нашим'? А ведь церковь " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " неизмеримо богаче моего скромного прихода.";
        link.l1 = "Да, святой отец, вы правы, но в голову мне пришли другие библейские строки: 'не ищи лёгких путей, ибо на них подстерегает нас Диавол, и голос его тем вкрадчивей, а соблазн тем сильнее, чем легче путь!' А падре " + PChar.GenQuest.ChurchQuest_1.PriestName + " уже намеревался архиепископу доложить о вашей забывчивости, едва я его отговорил" + GetSexPhrase("", "а") + ", предложив свою помощь.";
        link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
        break;

    case "GenQuest_Church_1_Dialog_1_1_1":
        dialog.text = "А-а-архиепископу?! О такой мелочи!.. Ну зачем же, зачем же? Я и сам давно хотел отослать эти труды любезному брату моему во Христе, да как-то всё не попадалось надёжной оказии. Но в тебе, " + GetSexPhrase("сын мой", "дочь моя") + ", я узрел достойного слугу Божьего. Вот, вручаю книги и рукописи, доставь их отцу " + PChar.GenQuest.ChurchQuest_1.PriestName + " в целости и сохранности и присовокупи мою глубочайшую благодарность.";
        link.l1 = "Всенепременнейше присовокуплю, " + LinkRandPhrase("падре", "святой отец", "отче") + ". Всенепременнейше.";
        link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
        break;

    case "GenQuest_Church_1_Dialog_1_1_2":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
        sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
        AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
        // Предмет "рукопись" -->
        AddItems(PChar, "Bible", 1);                                                                                 // Даем рукописи
        items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";                                              // Меняем имя. Потом поменять обратно!
        ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible");                                                // Меняем дескрайб. Потом поменять обратно!
        items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
                                                                                                                     // <-- Предмет "рукопись"
        break;

    case "GenQuest_Church_1_Dialog_1_2": // Сцена 2б-а и 2б-б
        // Генерим кэпа -->
        sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "mercen_" + (rand(14) + 14), "man", "man", 15, NPChar.nation, -1, true, "quest"));
        FantomMakeCoolFighter(sld, 35, 40, 35, "blade_13", "pistol3", "grapeshot", 30);
        FantomMakeCoolSailor(sld, 7 + rand(2), "", CANNON_TYPE_CANNON_LBS16, 75, 70, 65);
        sld.Abordage.Enable = false;
        sld.ShipEnemyDisable = true; // флаг не обижаться на выстрелы
        LAi_SetImmortal(sld, true);
        sld.Dialog.FileName = "GenQuests_Dialog.c";
        sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
        Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
        Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
        Group_SetType("ChurchGenQuest1_CapGroup", "trade");
        Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
        Group_SetTaskNone("ChurchGenQuest1_CapGroup");
        Group_LockTask("ChurchGenQuest1_CapGroup");
        PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
        PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
        PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
        PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
        PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
        PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
        // <-- Генерим кэпа

        if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) // Сцена 2б-а
        {
            dialog.text = "Но, " + GetSexPhrase("сын мой", "дочь моя") + "... Дело в том, что на прошлой неделе мне довелось встретиться с капитаном судна '" + sld.Ship.Name + "', куда меня призвали для причащения умирающего матроса. К моей великой радости капитан " + GetFullName(sld) + " сообщил, что направляется в " + XI_ConvertString("Colony" + GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown)) + ". И хотя он не ручался за сроки, однако согласился помочь, уверив меня, что в порт " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " он непременно зайдёт. Конечно же, я воспользовался оказией, отослал книги с этим добрым человеком и вручил их дальнейшую судьбу Господу.";
            link.l1 = "Хм, а вы уверены, что этому капитану можно доверять?.. Достаточно ли он уразумел ценность вверенных ему трудов и важность возложенного поручения?";
            link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
        }
        else // Сцена 2б-б
        {
            dialog.text = "Ах, " + GetSexPhrase("сын мой", "дочь моя") + "! Вы опоздали буквально на несколько часов! Я уже отправил книги Отца " + PChar.GenQuest.ChurchQuest_1.PriestName + " с капитаном " + PChar.GenQuest.ChurchQuest_1.CapFullName + ". Утром этот богобоязненный человек пришёл на исповедь и обмолвился, что сегодня его судно отправляется в " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapColony) + ". И хотя господин капитан не ручался за сроки, однако согласился помочь, уверив меня, что в порт " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " он непременно зайдёт.";
            link.l1 = LinkRandPhrase("Падре", "Святой отец", "Отец мой") + "... а вы уверены, что этому капитану можно доверять?.. И ещё я хотел" + GetSexPhrase("", "а") + " бы узнать, как называется его судно.";
            link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
        }
        break;

    case "GenQuest_Church_1_Dialog_1_2_1": // 2б-а
        dialog.text = "Я верю людям, " + GetSexPhrase("сын мой", "дочь моя") + ", ведь все мы созданы по образу и подобию, и в каждой душе горит искра Божия!";
        link.l1 = "М-да. Это веский аргумент. Ну что ж... благословите меня, святой отец, и пожелайте удачи в поисках этого капитана.";
        link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
        break;

    case "GenQuest_Church_1_Dialog_1_2_1_1":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
        PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
        PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; // Полная инфа о кэпе
        sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
        AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
        AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
        break;

    case "GenQuest_Church_1_Dialog_1_2_2_1":
        dialog.text = "Нужно верить людям, " + GetSexPhrase("сын мой", "дочь моя") + ". А про корабль я, к сожалению, ничего сказать не могу.";
        link.l1 = "И вы отдали ценные рукописи капитану, даже не потрудившись узнать название его судна?!!";
        link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
        break;

    case "GenQuest_Church_1_Dialog_1_2_2_2":
        dialog.text = "Видите ли, " + GetSexPhrase("сын мой", "дочь моя") + ", капитан " + PChar.GenQuest.ChurchQuest_1.CapFullName + " очень богобоязненный че...";
        link.l1 = "Это я уже слышал" + GetSexPhrase("", "а") + ", " + LinkRandPhrase("падре", "святой отец", "отче") + ".";
        link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
        break;

    case "GenQuest_Church_1_Dialog_1_2_2_3":
        dialog.text = "Терпение, " + GetSexPhrase("молодой человек", "девушка") + "! Капитан " + PChar.GenQuest.ChurchQuest_1.CapFullName + " очень богобоязнен, а его судно до нынешнего дня называлось таким словом, что священнослужителю не потребно произносить его даже мысленно! Сегодня на исповеди я указал заблудшей душе на это упущение. Ибо, согласно Библии, чистота духа должна блюстись нами, грешными, пуще чистоты тела, ибо Господь наш преградил сквернословам путь в царствие небе...";
        link.l1 = "Я понял" + GetSexPhrase("", "а") + ", " + LinkRandPhrase("падре", "святой отец", "Отче") + ", я понял" + GetSexPhrase("", "а") + "! Богобоязненный капитан " + PChar.GenQuest.ChurchQuest_1.CapFullName + ", известный всем Карибам картёжник и пьяница, благодаря вашему внушению решился переименовать своё корыто?..";
        link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
        break;

    case "GenQuest_Church_1_Dialog_1_2_2_4":
        dialog.text = "Ты очень проницател" + GetSexPhrase("ен", "ьна") + ", " + GetSexPhrase("сын мой", "дочь моя") + ". Нового имени корабля я не знаю, но, несомненно, это будет нечто возвышенное.";
        link.l1 = "Ох, " + RandPhraseSimple("падре", "святой отец") + "... благодарю вас за всё. И помолитесь за мою грешную душу...";
        link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
        break;

    case "GenQuest_Church_1_Dialog_1_2_2_5":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
        PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
        sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
        AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
        break;

    case "GenQuest_Church_1_Complete_1":
        dialog.text = "Ах, дитя моё! Я истово молился, и вот всё разрешилось как нельзя лучше! За твою помощь и рвение, " + GetSexPhrase("сын мой", "дочь моя") + ", тебя несомненно ждут райские кущи и ангельское пе...";
        link.l1 = RandPhraseSimple("Падре", "Отче") + ", на свидание со Святым Петром я пока, слава Создателю, не собираюсь. А живым, кроме обещаний райской благодати, надобно много разных материальных вещей...";
        link.l1.go = "GenQuest_Church_1_Complete_2";
        break;

    case "GenQuest_Church_1_Complete_2":
        dialog.text = "Да-да, " + GetSexPhrase("сын мой", "дочь моя") + ", да-да. Я вознагражу тебя по достоинству. Вот, возьми это, и помни, что Бог наказывает тех неразумных, которые чрезмерно пекутся о благах земных и поклоняются желтому дьяволу!";
        link.l1 = "Благодарю, " + LinkRandPhrase("падре", "святой отец", "отец мой") + ". Возьмите ваши долгожданные книги и рукописи, и помолитесь за мою грешную душу... Прощайте";
        link.l1.go = "GenQuest_Church_1_Complete_3";
        break;

    case "GenQuest_Church_1_Complete_3":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        RemoveItems(PChar, "Bible", 1);
        items[FindItem("Bible")].Name = "itmname_bible";
        BackItemDescribe("Bible");
        DeleteAttribute(items[FindItem("Bible")], "City");
        ChangeCharacterComplexReputation(PChar, "nobility", 5);
        AddCharacterExpToSkill(PChar, "Leadership", 50); // Бонус в авторитет
        AddCharacterExpToSkill(PChar, "Fortune", 50);    // Бонус в удачу
        TakeNItems(pchar, "chest", 3 + drand(1));
        PlaySound("interface\important_item.wav");
        sQuestTitle = NPChar.City + "ChurchGenQuest1";
        characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
        Group_DeleteGroup("ChurchGenQuest1_CapGroup");                  // Трем кэпа
        PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = true; // Завершаем, если вдруг осталось
        AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
        AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
        AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
        AddQuestUserData(sQuestTitle, "sSumm", FindRussianMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm)));
        CloseQuestHeader(sQuestTitle);
        DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
        NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
        break;
        // <-- Church GenQuest_1

    case "healthAdd_1":
        if (GetHealthMaxNum(pchar) == 6) // отлично
        {
            dialog.text = "Здоровье твоё " + GetHealthNameMaxSmall(pchar) + ", а раны заживут сами. Нужно просто избегать кровопролития и поберечь своё здоровье.";
            link.l1 = "Спасибо, обнадёжили. Постараюсь некоторое время не ввязываться в драки.";
            link.l1.go = "exit";
        }
        else
        {
            dialog.text = "Здоровье твоё " + GetHealthNameMaxSmall(pchar) + ", и хоть раны заживут сами, тебе не помешает его поправить.";
            link.l1 = "Что для этого нужно?";
            link.l1.go = "healthAdd_2";
        }
        link.l2 = "А почему вообще моё здоровье портится?";
        link.l2.go = "healthAdd_info";
        break;

    case "healthAdd_info":
        dialog.text = "Очень просто, " + GetSexPhrase("сын мой", "дочь моя") + ", ты получаешь урон, когда тебя ранят. Это не проходит бесследно, здоровье твоё подрывается каждой раной, и в результате ты становишься слаб" + GetSexPhrase("", "а") + " и фехтовать уже не в силах.\n Команда твоя, видя слабость вожака, теряет к тебе уважение. Но зато ты делаешься более осторожным и умение защиты временно увеличивается. Своевременный отдых и минимизация ранений помогут оставаться всегда полным сил.";
        link.l1 = "Спасибо, вы меня просветили.";
        link.l1.go = "exit";
        break;

    case "healthAdd_2":
        dialog.text = "Молитвы и отказ от насилия, " + GetSexPhrase("сын мой", "дочь моя") + ". Тогда Господь вернёт тебе утерянное тобой.";
        link.l1 = "А вы не могли бы помолится за меня?";
        link.l1.go = "healthAdd_3";
        link.l2 = "То есть - никак? Хм.. обнадежили, спасибо.";
        link.l2.go = "exit";
        break;

    case "healthAdd_3":
        if (npchar.quest.HealthMonth != iMonth)
        {
            dialog.text = "Я? Пожалуй, это возможно. Но тебе придется внести подаяние в наш приход.";
            link.l1 = pcharrepphrase("Сколько?", "С радостью! Каков его размер?");
            link.l1.go = "healthAdd_4";
            link.l2 = "Я уж как-нибудь сам" + GetSexPhrase("", "а") + "...";
            link.l2.go = "exit";
        }
        else
        {
            dialog.text = "" + GetSexPhrase("Сын мой", "Дочь моя") + ", я уже молюсь о твоём благополучии. Молитвы займут всё моё время до конца месяца.";
            link.l1 = "Спасибо, " + RandPhraseSimple("падре.", "святой отец.");
            link.l1.go = "exit";
        }
        break;

    case "healthAdd_4":
        dialog.text = "Сто тысяч песо будет вполне достаточной платой за чудо исцеления.";
        link.l1 = pcharrepphrase("Сколько!!! Да вы в своём уме?! Я заплачу такую сумму, когда разграблю пару церквей.", "Для меня это слишком много. Видно правду говорят - здоровье за деньги не купишь.");
        link.l1.go = "exit";
        if (sti(pchar.Money) >= 100000)
        {
            link.l2 = "Я соглас" + GetSexPhrase("ен", "на") + "!";
            link.l2.go = "healthAdd_5";
        }
        break;

    case "healthAdd_5":
        AddMoneyToCharacter(pchar, -100000);
        AddCharacterMaxHealth(pchar, 4); // можно не проверять, тк явно меньше 51
        npchar.quest.HealthMonth = iMonth;
        dialog.text = "Хорошо. Твоё здоровье немного улучшится. Но тебе нужно избегать стычек и беречь себя, иначе эффект сойдет на нет. Мне нужно целый месяц провести в молитвах о твоем бренном теле.";
        link.l1 = "Спасибо. Если что, я зайду через месяц снова.";
        link.l1.go = "exit";
        break;

    //квест пожертвования хозяйки борделя
    case "HostessChurch":
        dialog.text = "И кто же эта добрая душа, что жертвует?";
        link.l1 = "Хм... Это хозяйка местного борделя.";
        link.l1.go = "HostessChurch_call";
        link.l2 = "Я бы предпоч" + GetSexPhrase("ел", "ла") + " не называть имен. Ведь может же быть анонимное пожертвование!";
        link.l2.go = "HostessChurch_notCall";
        pchar.questTemp.different = "HostessChurch_return"; //флаг на возвращение
        break;

    case "HostessChurch_call":
        if (isBadReputation(pchar, 5))
        {
            if (rand(100) < GetCharacterSkill(pchar, "Fortune")) //рендом вешаем на удачу
            {
                dialog.text = "Сам" + GetSexPhrase("", "а") + " грешни" + GetSexPhrase("к", "ца") + ", еще за грешницу и просишь? О своей душе подумал" + GetSexPhrase("", "а") + " бы лучше, ведь все мы перед Господом предстанем!";
                link.l1 = "Это точно. Надеюсь, Господь будет милостив ко мне... Так как насчёт пожертвования?";
                link.l1.go = "HostessChurch_ok";
            }
            else
            {
                dialog.text = "Изыди, сатана!!! Забирай свои нечестивые деньги и убирайся отсюда!";
                link.l1 = "Святой отец, как же так?! Мы к вам со всей душой, а вы...";
                link.l1.go = "HostessChurch_bad";
            }
        }
        else
        {
            if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) //рендом вешаем на харизму
            {
                dialog.text = "Я рад, что ты помогаешь грешникам обрести путь к Господу нашему. За это тебе воздастся на небесах!";
                link.l1 = "Это было бы здорово! Так что насчёт пожертвования?";
                link.l1.go = "HostessChurch_ok";
            }
            else
            {
                dialog.text = "Я не могу принять деньги, добытые во грехе. Верни их этой блуднице, " + GetSexPhrase("сын мой", "дочь моя") + ". Через деньги пути к Господу не отыскать.";
                link.l1 = "Очень жаль, что вы отвергаете ее. Очень жаль...";
                link.l1.go = "HostessChurch_bad_1";
            }
        }
        break;

    case "HostessChurch_notCall":
        if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
        {
            dialog.text = "Взять эти деньги, даже не зная, от кого они...";
            link.l1 = "Да, падре, именно так. Примите пожертвование от чистого сердца!";
            link.l1.go = "HostessChurch_ok_1";
        }
        else
        {
            dialog.text = "Взять эти деньги, даже не зная, от кого они? Ты с ума сош" + GetSexPhrase("ел", "ла") + "?! А вдруг, на этих деньгах - кровь!!";
            link.l1 = "Святой отец, на всех деньгах - кровь...";
            link.l1.go = "HostessChurch_bad_2";
        }
        break;

    case "HostessChurch_ok":
        dialog.text = "Я принимаю его, " + GetSexPhrase("сын мой", "дочь моя") + ". Пойди, передай это блуднице.";
        link.l1 = "Хорошо, падре. Спасибо.";
        link.l1.go = "exit";
        AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
        AddCharacterExpToSkill(pchar, "Fortune", 20);
        //флаг удачная или неудачная попытка дачи
        characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
        break;

    case "HostessChurch_ok_1":
        dialog.text = "Я принимаю его, " + GetSexPhrase("сын мой", "дочь моя") + ". Можешь передать подающему.";
        link.l1 = "Хорошо, падре. Спасибо.";
        link.l1.go = "exit";
        AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
        AddCharacterExpToSkill(pchar, "Fortune", 20);
        //флаг удачная или неудачная попытка дачи
        characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
        break;

    case "HostessChurch_bad":
        dialog.text = "Убирайся, исчадие ада!!! И не смей показываться мне на глаза!";
        link.l1 = "Хех, ну хорошо.";
        link.l1.go = "exit";
        AddCharacterExpToSkill(pchar, "Leadership", 50);
        npchar.quest.BadMeeting = lastspeak_date;
        //флаг удачная или неудачная попытка дачи
        characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
        break;

    case "HostessChurch_bad_1":
        dialog.text = "Таково моё решение. Иди с миром, " + GetSexPhrase("сын мой", "дочь моя") + ".";
        link.l1 = "Прощайте, падре.";
        link.l1.go = "exit";
        AddCharacterExpToSkill(pchar, "Leadership", 30);
        //флаг удачная или неудачная попытка дачи
        characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
        break;

    case "HostessChurch_bad_2":
        dialog.text = "Это ты так думаешь, нечестив" + GetSexPhrase("ец", "ая") + "! Убирайся из храма и не показывайся мне на глаза!";
        link.l1 = "Так? Да пожалуйста, уйду...";
        link.l1.go = "exit";
        AddCharacterExpToSkill(pchar, "Leadership", 40);
        npchar.quest.BadMeeting = lastspeak_date;
        //флаг удачная или неудачная попытка дачи
        characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
        break;

    //--> Jason Церковная депеша
    case "Monkletter":
        if (CheckAttribute(pchar, "GenQuest.Monkletter.Late"))
        {
            dialog.text = "Я уже потерял надежду когда-либо увидеть эти бумаги. Почему твой путь был столь долгим, сын мой?";
            link.l1 = "Меня задержали непредвиденные обстоятельства, святой отец.";
            link.l1.go = "Monkletter_1";
        }
        else
        {
            dialog.text = "Я ждал эти бумаги, сын мой. Благодарю тебя за оперативную доставку. Прими от меня в награду эти несколько золотых и моё благословение.";
            link.l1 = "Спасибо, святой отец. Был рад помочь святой церкви!";
            link.l1.go = "Monkletter_3";
        }
        break;

    case "Monkletter_1":
        dialog.text = "Все мы под Богом ходим, сын мой... Человек предполагает, а Господь располагает. Давай мне эти бумаги и ступай с миром.";
        link.l1 = "Вот, возьмите, падре. Всего доброго!";
        link.l1.go = "Monkletter_2";
        break;

    case "Monkletter_2":
        DialogExit();
        RemoveItems(PChar, "letter_church", 1); //заменить на нужный
        AddQuestRecord("Monkletter", "2");
        CloseQuestHeader("Monkletter");
        ChangeCharacterComplexReputation(pchar, "nobility", -1);
        DeleteAttribute(pchar, "GenQuest.Monkletter");
        break;

    case "Monkletter_3":
        dialog.text = "Ступай с Богом, сын мой. Да хранит тебя Всевышний на твоем пути!";
        link.l1 = "До свидания, святой отец.";
        link.l1.go = "Monkletter_4";
        break;

    case "Monkletter_4":
        pchar.quest.Monkletter_Over.over = "yes"; //снять таймер
        DialogExit();
        RemoveItems(PChar, "letter_church", 1); //заменить на нужный
        AddQuestRecord("Monkletter", "3");
        CloseQuestHeader("Monkletter");
        TakeNItems(pchar, "gold_dublon", 10 + rand(5));
        ChangeCharacterComplexReputation(pchar, "nobility", 1);
        ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
        AddCharacterExpToSkill(pchar, "Leadership", 50);
        AddCharacterExpToSkill(pchar, "Fortune", 50);
        DeleteAttribute(pchar, "GenQuest.Monkletter");
        break;
    //<-- Церковная депеша

    //--> Jason Доставить молитвенники
    case "Churchbooks":
        dialog.text = "Тебя послали взять у нас молитвенники для церкви " + XI_ConvertString("Colony" + pchar.GenQuest.Churchbooks.StartCity + "Gen") + "? Хорошо. У меня есть упаковка с тремя десятками молитвенников. Возьми её, сын мой.";
        link.l1 = "Благодарю, падре. До свидания!";
        link.l1.go = "Churchbooks_1";
        break;

    case "Churchbooks_1":
        dialog.text = "Да охранит тебя Господь на твоем пути! Ступай с миром...";
        link.l1 = "...";
        link.l1.go = "exit";
        AddQuestRecord("Churchbooks", "2");
        pchar.GenQuest.Churchbooks = "return";
        GiveItem2Character(pchar, "prayer_book"); //поставить соотв.предмет
        break;

    case "Churchbooks_2":
        if (CheckAttribute(pchar, "GenQuest.Churchbooks.Late"))
        {
            dialog.text = "Благодарю тебя за твою помощь, сын мой, хотя бы и прибывшую с опозданием.";
            link.l1 = "Меня задержали непредвиденные обстоятельства в пути, святой отец.";
            link.l1.go = "Churchbooks_3";
        }
        else
        {
            dialog.text = "Благодарю тебя за помощь, сын мой. Ты привез эти книги очень вовремя. Возьми в награду этот освященный оберег - он поможет тебе в час опасности.";
            link.l1 = "Спасибо, святой отец. Был рад помочь святой церкви!";
            link.l1.go = "Churchbooks_4";
        }
        break;

    case "Churchbooks_3":
        dialog.text = "На всё воля Господня, сын мой... Ступай с миром.";
        link.l1 = "До свидания, падре.";
        link.l1.go = "exit";
        RemoveItems(PChar, "prayer_book", 1); //заменить на нужный
        AddQuestRecord("Churchbooks", "3");
        CloseQuestHeader("Churchbooks");
        DeleteAttribute(pchar, "GenQuest.Churchbooks");
        break;

    case "Churchbooks_4":
        dialog.text = "Ступай с Богом, сын мой. Да охранит тебя Господь от всех бед на твоём пути!";
        link.l1 = "До свидания, святой отец.";
        link.l1.go = "Churchbooks_5";
        break;

    case "Churchbooks_5":
        pchar.quest.Churchbooks_Over.over = "yes"; //снять таймер patch-5
        DialogExit();
        RemoveItems(PChar, "prayer_book", 1); //заменить на нужный
        GiveItem2Character(pchar, pchar.GenQuest.Churchbooks.Item);
        Log_Info("Вы получили оберег '" + XI_ConvertString(pchar.GenQuest.Churchbooks.Item) + "'");
        AddQuestRecord("Churchbooks", "4");
        CloseQuestHeader("Churchbooks");
        ChangeCharacterComplexReputation(pchar, "nobility", 1);
        ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
        AddCharacterExpToSkill(pchar, "Leadership", 50);
        AddCharacterExpToSkill(pchar, "Fortune", 50);
        DeleteAttribute(pchar, "GenQuest.Churchbooks");
        break;
    }
}

void ChurchGenQuest2_RemoveCup()
{
    RemoveItems(PChar, "Bible", 1);
    ref rItem = ItemsFromID("Bible");
    DeleteAttribute(rItem, "City");
    rItem.Weight = 2;
    rItem.Name = "itmname_Bible";
    rItem.picIndex = 6;
    rItem.picTexture = "ITEMS_9";
    BackItemDescribe("Bible");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
    string sColony = SelectNotEnemyColony(chr);
    PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
    PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
    PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].Island;
    PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;

    // Чтоб жизнь медом не казалась... Какие сцены будут в квесте, определяем в самом начале.
    int iRand = Rand(2);
    switch (iRand)
    {
    case "0":
        PChar.GenQuest.ChurchQuest_1 .2A_Scene = true;
        Log_TestInfo("Церковный генератор 1: ключевая сцена - 2А (просто забрать у священника рукописи).");
        break;

    case "1":
        PChar.GenQuest.ChurchQuest_1 .2BA_Scene = true;
        Log_TestInfo("Церковный генератор 1: ключевая сцена - 2Б-А (поиск кэпа. О нем есть полная инфа).");
        break;

    case "2": // Этот флаг уже не проверяем, т.к. если нет тех, что выше, по-любому есть этот
        PChar.GenQuest.ChurchQuest_1 .2BB_Scene = true;
        Log_TestInfo("Церковный генератор 1: ключевая сцена - 2Б-Б (поиск кэпа. Название шипа неизвестно.)");
        break;
    }
}