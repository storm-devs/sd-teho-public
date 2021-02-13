// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    switch (Dialog.CurrentNode)
    {
    case "quests":
        dialog.text = RandPhraseSimple("Какие вопросы?", "Что вам угодно?");
        link.l1 = RandPhraseSimple("Я передумал...", "Сейчас мне не о чем говорить");
        link.l1.go = "exit";
        break;

    //******************** французская линейка ***************************
    case "work_1": // работа на благо короны - линейка нации
        if (CheckAttribute(npchar, "notQuestLine"))
        {
            dialog.text = "К сожалению, я не могу предоставить вам работу. Вы не тот человек, кому я хотел бы доверить свои дела. До свидания.";
            link.l1 = "Вот это да...";
            link.l1.go = "exit";
            break;
        }
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
