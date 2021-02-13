// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
    case "quests":
        dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                                              "Послушайте, если вы не по делам порта, то не стоит меня вопросами донимать.", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал" + GetSexPhrase("", "а") + "...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                                           "Да уж, действительно в третий раз...", "Извините, но портовые дела меня сейчас не интересуют.", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        if (pchar.questTemp.Slavetrader == "FindRatHavana")
        {
            link.l1 = "Здравствуйте. Я бы хотел" + GetSexPhrase("", "а") + " узнать, не останавливался ли в вашем порту корвет '" + pchar.questTemp.Slavetrader.ShipName + "', под командованием Франсуа Гонтьера?";
            link.l1.go = "Havana_ratP_1";
        }
        // калеуче
        if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
        {
            link.l1 = "Послушайте, к вам в порт не прибывал пассажиром человек по имени Жоаким Мерриман? Немолодой сеньор, португалец, носит усы и эспаньолку, с пронзительным взглядом?";
            link.l1.go = "caleuche";
        }
        // Addon 2016-1 Jason пиратская линейка
        if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && !CheckAttribute(npchar, "quest.Mtraxx"))
        {
            link.l1 = "Меня интересует судно 'Кантавро'. Я ищу его капитана, Эсберто Кабаньяса, по личному вопросу. Не можете мне чем-нибудь помочь?";
            link.l1.go = "mtraxx";
        }
        break;

    case "Havana_ratP_1":
        dialog.text = NPCStringReactionRepeat("Да, останавливался. Но уже ушёл от нас. Спросите о нем нашего трактирщика, капитан корвета снимал у него комнату в таверне.", "Вы уже " + GetSexPhrase("спрашивали", "спрашивали") + " об этом, я вам ответил.", "Я же говорю вам, вы уже " + GetSexPhrase("спрашивали", "спрашивали") + " об этом Гонтьере.", "Я прошу не мешать мне работать!", "block", 0, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat("Спасибо! Так и поступлю.", "Хм, ну да...", "Да, точно, " + GetSexPhrase("спрашивал", "спрашивала") + "...", "Извините, " + npchar.name + "...", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        break;

    // калеуче
    case "caleuche":
        dialog.text = "Не могу ничего сообщить вам об этом человеке. Может, и прибывал, но нигде не отмечался.";
        link.l1 = "Ясно. Жаль. Буду искать дальше...";
        link.l1.go = "exit";
        npchar.quest.caleuche = "true";
        break;

    // Addon 2016-1 Jason пиратская линейка
    case "mtraxx":
        dialog.text = "Посмотрим... Шхуна 'Кантавро' отбыла в плавание два дня назад. Цель - патрулирование... а вот где - не указано. Корабль военный, и место назначения известно только коменданту Гаваны и самому капитану. Желаете подробностей - обращайтесь в комендатуру, в форт, а я большего сообщить не могу - увы!";
        link.l1 = "Ясно. Спасибо и на этом...";
        link.l1.go = "exit";
        npchar.quest.Mtraxx = "true";
        AddQuestRecord("Roger_1", "5");
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
