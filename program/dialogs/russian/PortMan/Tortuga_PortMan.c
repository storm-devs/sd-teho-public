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

        if (pchar.questTemp.Slavetrader == "FindRatTortuga")
        {
            link.l1 = "Добрый день. Я ищу Франсуа Гонтьера. Его корвет '" + pchar.questTemp.Slavetrader.ShipName + "', должен был бросить якорь в вашей гавани.";
            link.l1.go = "Tortuga_ratP_1";
        }

        break;

    case "Tortuga_ratP_1":
        dialog.text = NPCStringReactionRepeat("Хм... Вынужден вас огорчить. Корвет '" + pchar.questTemp.Slavetrader.ShipName + "' к нам в порт не заходил, и Франсуа Гонтьен не отмечался.", "Вы уже " + GetSexPhrase("спрашивали", "спрашивали") + " об этом, я вам ответил.", "Я же говорю вам, вы уже " + GetSexPhrase("спрашивали", "спрашивали") + " об этом Гонтьере.", "Я прошу не мешать мне работать!", "block", 0, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat("Вот это да... И куда же он делся? Ладно, пойду поспрашиваю в городе.", "Хм, ну да...", "Да, точно, " + GetSexPhrase("спрашивал", "спрашивала") + "...", "Извините, " + npchar.name + "...", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
