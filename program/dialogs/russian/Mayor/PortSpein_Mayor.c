// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
    case "quests":
        dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Что вы хотели? Спрашивайте.", "Я слушаю вас, что за вопрос?"), "Второй раз за день вы пытаетесь задать ворпос...", "В третий раз за день вы опять пытаетесь задать вопрос...",
                                              "Да когда же это кончится?! У меня полно работы по управлению делами города, а ты всё вопросы пытаешься задать!", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал" + GetSexPhrase("", "а") + "...", "Не сейчас, не место и не время..."), "Да, верно... Но не сейчас, позже...",
                                           "Задам, задам... Только позже...", "Извините, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
        {
            link.l1 = "Ваша светлость, в апреле 1654 года в вашу колонию заходил фрегат под командованием капитана Мигеля Дичозо. Он потом исчез. Не припоминаете ничего связанного с ним? Может, Дичозо заходил к вам, беседовал...";
            link.l1.go = "guardoftruth";
        }
        break;

    case "guardoftruth":
        dialog.text = "Да, припоминаю... был такой человек. Но никаких подробностей, связанных с ним, не помню. Как пришёл, так и ушёл. Ничем помочь не могу.";
        link.l1 = "Ясно. Простите за беспокойство!..";
        link.l1.go = "exit";
        npchar.quest.guardoftruth = "true";
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
