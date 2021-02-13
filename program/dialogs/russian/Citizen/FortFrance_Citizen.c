// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
    case "quests":
        dialog.text = RandPhraseSimple("Какие вопросы?", "Что вам угодно?");
        link.l1 = RandPhraseSimple("Я " + GetSexPhrase("передумал", "передумала") + "...", "Сейчас мне не о чем говорить");
        link.l1.go = "exit";
        //Бремя гасконца
        if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && !CheckAttribute(npchar, "quest.Sharlie"))
        {
            link.l1 = "Извините, " + GetAddress_FormToNPC(NPChar) + " вы не знаете, где я могу найти человека - Мишеля де Монпе? Он должен быть где-то у вас в городе.";
            link.l1.go = "Sharlie";
        }
        if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "findskiper" && !CheckAttribute(npchar, "quest.Sharlie1"))
        {
            link.l1 = "Послушайте, " + GetAddress_FormToNPC(NPChar) + ", тут такое дело... Я ищу штурмана на свой корабль - может, знаете подходящего человека в вашем городе?";
            link.l1.go = "Sharlie_1";
        }
        //Бремя гасконца
        break;

    case "info":
        // заменить на описание неких НПС, по квестам
        dialog.text = "Я что, работаю на тайную агентурную сеть для " + NationNameGenitive(sti(NPChar.nation)) + "?";
        link.l1 = "Ну ладно... тогда пока.";
        link.l1.go = "exit";
        link.l2 = "Тогда другой вопрос";
        link.l2.go = "new question";
        break;

    case "town":
        // заменить на описание как пройти, по квестам
        dialog.text = "Я вам что справочная? Не знаю. Ничего не ведаю.";

        link.l1 = "Вот бестолочь! Пока.";
        link.l1.go = "exit";
        link.l2 = "Тогда другой вопрос";
        link.l2.go = "new question";
        break;

    //--> Бремя гасконца
    case "Sharlie":
        if (sti(pchar.questTemp.Sharlie.Citcount) == 3)
        {
            dialog.text = "Хм... Вижу, вы в нашем городе приезжий, раз совершенно без опаски ведёте подобные расспросы... Я советую вам их прекратить, не то накличете беду на свою голову. А насчёт вашего вопроса... поговорите с аббатом Бенуа. Вы сможете найти его в церкви.";
            link.l1 = "Спасибо!";
            link.l1.go = "exit";
            AddDialogExitQuest("Sharlie_SetBenua");
        }
        else
        {
            dialog.text = LinkRandPhrase("Нет, это имя мне ничего не говорит.", "Ничем не могу вам помочь. Мне пора идти, до свидания.", "Увы, но я впервые слышу это имя. Так что...");
            link.l1 = "Понятно... Прошу прощения за беспокойство.";
            link.l1.go = "exit";
            pchar.questTemp.Sharlie.Citcount = sti(pchar.questTemp.Sharlie.Citcount) + 1;
            npchar.quest.Sharlie = "true";
        }
        break;

    case "Sharlie_1":
        dialog.text = LinkRandPhrase("Нет, никаких штурманов я не знаю.", "Без малейшего понятия. Мне пора идти, до свидания.", "Увы, но ничем не могу помочь. Так что...");
        link.l1 = "Понятно. Извините...";
        link.l1.go = "exit";
        npchar.quest.Sharlie1 = "true";
        npchar.dialog.currentnode = "first time";
        break;
        //<-- Бремя Гасконца
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}