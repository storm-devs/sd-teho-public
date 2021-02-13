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
        if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten1")
        {
            link.l1 = "В ваш порт не так давно прибывал галеон 'Восхитительный' под французским флагом. Капитан - Гай Марше. Не подскажете, куда он отправился далее? Может, отметился как-то у вас?";
            link.l1.go = "guardoftruth";
        }
        break;

    case "guardoftruth":
        dialog.text = "Галеон 'Восхитительный'? Как же, помню. Он заключил с нами договор на доставку партии паприки в Бриджтаун, что на Барбадосе. А что-то случилось?";
        link.l1 = "Нет, просто Гай - мой друг, и мне очень хочется его увидеть.";
        link.l1.go = "guardoftruth_1";
        break;

    case "guardoftruth_1":
        dialog.text = "Тогда отправляйтесь на Барбадос. Хотя навряд ли вы там его застанете - прошло уже много времени. Но хотя бы справитесь в тамошнем портовом управлении о нём.";
        link.l1 = "Спасибо! Вы мне очень помогли.";
        link.l1.go = "guardoftruth_2";
        break;

    case "guardoftruth_2":
        DialogExit();
        AddQuestRecord("Guardoftruth", "12");
        pchar.questTemp.Guardoftruth = "barbados";
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
