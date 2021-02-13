// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
    case "quests":
        dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "М-да, позвольте угадаю... Опять ничего существенного?",
                                              "Послушайте, я финансами оперирую, а не на вопросы отвечаю...", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я " + GetSexPhrase("передумал", "передумала") + "...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                                           "Вы угадали, простите...", "Я понимаю...", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        //Цена чахотки
        if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
        {
            link.l1 = "Скажите, имя 'Хуан' вам что-нибудь говорит?";
            link.l1.go = "Consumption";
        }
        break;

    //Цена чахотки
    case "Consumption":
        dialog.text = "Не знаю. И не хочу знать. И вам не советую. А теперь, прошу прощения, но мне нужно возвращаться к делам. У вас, наверное, тоже есть дела? Займитесь ими.";
        link.l1 = "Ясно. Извините за беспокойство...";
        link.l1.go = "exit";
        pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan) + 1;
        if (sti(pchar.questTemp.Consumption.AskJuan) == 3)
        {
            pchar.quest.Consumption2.win_condition.l1 = "location";
            pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
            pchar.quest.Consumption2.function = "Consumption_CreateSergio";
        }
        npchar.quest.Consumption = "true";
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
