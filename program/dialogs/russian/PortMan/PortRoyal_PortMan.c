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

        if (pchar.questTemp.Slavetrader == "FindRatJamaica")
        {
            link.l1 = "Добрый день. У вас не отмечался капитан Франсуа Гонтьер, прибывший из Порто Белло? У него корвет по имени '" + pchar.questTemp.Slavetrader.ShipName + "'.";
            link.l1.go = "Jamaica_ratPP_1";
        }

        break;

    case "Jamaica_ratPP_1":
        dialog.text = NPCStringReactionRepeat("Нет. Франсуа Гонтьер не отмечался, и корвет '" + pchar.questTemp.Slavetrader.ShipName + "' в порт Порт-Рояля не заходил.", "Вы уже " + GetSexPhrase("спрашивали", "спрашивали") + " об этом, я вам ответил.", "Я же говорю тебе, вы уже " + GetSexPhrase("спрашивали", "спрашивали") + " об этом Гонтьере.", "Я прошу вас не мешать мне работать!", "block", 0, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat("Ясно. Будем искать дальше...", "Хм, ну да...", "Да, точно, " + GetSexPhrase("спрашивал", "спрашивала") + "...", "Извините, " + npchar.name + "...", npchar, Dialog.CurrentNode);
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
