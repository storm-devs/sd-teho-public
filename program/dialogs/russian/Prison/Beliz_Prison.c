// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
    case "quests":
        dialog.text = "Говорите, я слушаю.";
        link.l1 = "Я " + GetSexPhrase("ошибся", "ошиблась") + ". Прощайте.";
        link.l1.go = "Exit";
        // Калеуче
        if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "start")
        {
            link.l1 = "Я слышал, что в окрестностях Белиза появилась шайка воров и разбойников. И что они также промышляют в самом городе.";
            link.l1.go = "caleuche";
        }
        if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "know" && CheckAttribute(pchar, "questTemp.Caleuche.belizbandos") && GetQuestPastDayParam("questTemp.Caleuche.belizbandos") < 3)
        {
            link.l1 = "Я могу сообщить вам кое-что о банде.";
            link.l1.go = "caleuche_3";
        }
        if (CheckAttribute(pchar, "questTemp.Caleuche.BelizRegard"))
        {
            link.l1 = "Какие новости о банде? Вы взяли их у пещеры?";
            link.l1.go = "caleuche_7";
        }
        break;

    // Калеуче
    case "caleuche":
        dialog.text = "Ваши слухи вам не соврали. Эти бандиты стали нашей настоящей головной болью. Вы хотите что-то сообщить о них?";
        link.l1 = "Кроме того, что они украли важную для меня вещь - ничего. Я надеялся, что вы мне расскажете про них что-нибудь. Например, что кто-то из их шайки пойман и готов дать показания...";
        link.l1.go = "caleuche_1";
        break;

    case "caleuche_1":
        dialog.text = "Я вас разочарую, капитан. У нас нет о них никаких сведений кроме того, что они прячутся где-то в джунглях, а в городе у них есть сообщники. Вот и всё, что мне известно. Если узнаете больше - немедленно мне сообщите.";
        link.l1 = "Хорошо, офицер. Я обязательно так и сделаю.";
        link.l1.go = "caleuche_2";
        break;

    case "caleuche_2":
        DialogExit();
        AddQuestRecord("Caleuche", "10");
        pchar.questTemp.Caleuche.Bandos = "seek";
        break;

    case "caleuche_3":
        string sTime;
        if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 0)
            sTime = "через три дня";
        if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 1)
            sTime = "послезавтра";
        if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 2)
            sTime = "завтра";
        dialog.text = "Вы серьёзно, капитан? Выкладывайте, я внимательно слушаю.";
        link.l1 = "Я нашёл одного из их осведомителей в городе. От него мне удалось узнать, что их шайка готовится напасть на судно, которое дожно прибыть в бухту Четумаль. Сбор негодяев назначен " + sTime + " ночью у пещеры, что недалеко от Белиза, если в джунглях на развилке взять левее.";
        link.l1.go = "caleuche_4";
        break;

    case "caleuche_4":
        dialog.text = "У пещеры? Отличные вести. Я немедленно отдам приказ подготовить на мерзавцев засаду. Если вы не ошиблись, или ваш осведомитель не соврал, и мы возьмём подонков, я буду ходатайствовать за вас перед губернатором о награде.";
        link.l1 = "Спасибо! Я загляну к вам денька через три - как раз всё уже разрешится.";
        link.l1.go = "caleuche_5";
        break;

    case "caleuche_5":
        dialog.text = "Хорошо. Заходите.";
        link.l1 = "До встречи, офицер.";
        link.l1.go = "caleuche_6";
        break;

    case "caleuche_6":
        DialogExit();
        AddQuestRecord("Caleuche", "15");
        pchar.questTemp.Caleuche.Bandos = "comendant";
        pchar.questTemp.Caleuche.BelizChance = drand(3);
        SetFunctionTimerCondition("Caleuche_BelizRegard", 0, 0, 3, false); // таймер
        break;

    case "caleuche_7":
        if (sti(pchar.questTemp.Caleuche.BelizChance) < 3)
        {
            dialog.text = "Мы устроили мерзавцам теплый приём, ха-ха-ха! Накрыли банду в полном составе, вместе с главарём! Вы бы видели их изумлённые рожи! Они попытались оказать сопротивление, но были уничтожены мушкетным огнём и саблями наших бравых солдат.";
            link.l1 = "Отличные новости, офицер! Теперь граждане Белиза могут спать спокойно.";
            link.l1.go = "caleuche_12";
        }
        else
        {
            dialog.text = "Хм. Мои солдаты прождали всю ночь у пещеры, и никто так и не появился. Сержант был просто в ярости. Хорошо, что вы ему не попались на глаза.";
            link.l1 = "Чёрт побери! Не может быть! У какой пещеры была засада? Там их две!";
            link.l1.go = "caleuche_8";
        }
        break;

    case "caleuche_8":
        dialog.text = "У какой вы сказали, у той и устроили. На развилке в джунглях направо...";
        link.l1 = "Налево!! На развилке - на-ле-во! Я же говорил!";
        link.l1.go = "caleuche_9";
        break;

    case "caleuche_9":
        dialog.text = "Но я же точно помню, что вы сказали - направо!";
        link.l1 = "Я сказал - налево. Вы упустили банду по собственной же ошибке!";
        link.l1.go = "caleuche_10";
        break;

    case "caleuche_10":
        AddQuestRecord("Caleuche", "16");
        dialog.text = "Значит, вы мямлили себе под нос, а не говорили. У меня со слухом всё в порядке, и я...";
        link.l1 = "Я не желаю с вами спорить, офицер. Я искренне хотел помочь. Прощайте.";
        link.l1.go = "caleuche_11";
        break;

    case "caleuche_11":
        DialogExit();
        DeleteAttribute(pchar, "questTemp.Caleuche.BelizChance");
        DeleteAttribute(pchar, "questTemp.Caleuche.BelizRegard");
        break;

    case "caleuche_12":
        dialog.text = "Я доложил губернатору о вашей роли в уничтожении бандитов. Он высоко оценил ваш вклад и уполномочил меня выдать вам награду: денежную премию и трофейное ружьё. Извольте получить!";
        link.l1 = "Спасибо!";
        link.l1.go = "caleuche_13";
        break;

    case "caleuche_13":
        Log_Info("Вы получили сундук с дублонами");
        Log_Info("Вы получили аркебузу");
        PlaySound("interface\important_item.wav");
        AddQuestRecord("Caleuche", "17");
        GiveItem2Character(pchar, "chest");
        GiveItem2Character(pchar, "mushket3");
        dialog.text = "Благодарю за службу, капитан! Если бы все граждане были такими же предприимчивыми и сознательными, как вы, мы бы уже давно искоренили преступность. Всего доброго!";
        link.l1 = "До свидания, офицер. Удачи в вашей службе!";
        link.l1.go = "caleuche_11";
        ChangeCharacterComplexReputation(pchar, "nobility", 5);
        ChangeCharacterComplexReputation(pchar, "authority", 3);
        ChangeCharacterComplexReputation(pchar, "fame", 3);
        OfficersReaction("good");
        ChangeCharacterNationReputation(pchar, ENGLAND, 8);
        AddCharacterExpToSkill(pchar, "Leadership", 300); //авторитет
        AddCharacterExpToSkill(pchar, "Fortune", 200);    //везение
        AddCharacterExpToSkill(pchar, "Sneak", 200);      //скрытность
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
